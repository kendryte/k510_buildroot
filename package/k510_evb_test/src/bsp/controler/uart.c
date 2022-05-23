/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "platform.h"
#include "k510.h"
#include "uart.h"
#include <assert.h>

#define __UART_BRATE_CONST  16

volatile uart_t* const  uart[4] =
{
    (volatile uart_t*)UART0_BASE_ADDR,
    (volatile uart_t*)UART1_BASE_ADDR,
    (volatile uart_t*)UART2_BASE_ADDR,
    (volatile uart_t*)UART3_BASE_ADDR
};

uintptr_t uart_reset_addr[] = {
    0x97002058,
    0x9700205C,
    0x97002060,
    0x97002064,
};

void uart_reset(uart_device_number_t channel)
{
    writel(0x80000000, uart_reset_addr[channel]);
    writel(0x1, uart_reset_addr[channel]);
    while(!(readl(uart_reset_addr[channel]) & 0x80000000));
}

#define UART_INTERRUPT_SEND 0x02U
#define UART_INTERRUPT_RECEIVE 0x04U
#define UART_INTERRUPT_CHARACTER_TIMEOUT 0x0CU

typedef struct _uart_interrupt_instance
{
    plic_irq_callback_t callback;
    void *ctx;
} uart_interrupt_instance_t;

typedef struct _uart_instance
{
    uart_interrupt_instance_t uart_receive_instance;
    uart_interrupt_instance_t uart_send_instance;
    uint32_t uart_num;
} uart_instance_t;

uart_instance_t g_uart_instance[4];


static uart_device_number_t s_uart_debug_channel = UART_DEVICE_0;

static int uart_channel_putc(char c, uart_device_number_t channel)
{
    // while (uart[channel]->LSR & (1u << 5))
    while(((uart[channel]->LSR) & (1u << 6)) == 0)
    {
        continue;
    }
    uart[channel]->THR = c;
    return c & 0xff;
}

int uart_outbyte(int c)
{
	uart_channel_putc(c, s_uart_debug_channel);
	if (c =='\n')
		uart_channel_putc('\r', s_uart_debug_channel);
	return c;
}

int uart_puts(const char *s)
{
	int len = 0;

	while (*s) {
		uart_channel_putc(*s, s_uart_debug_channel);

		if (*s == '\n')
			uart_channel_putc('\r', s_uart_debug_channel);
		s++;
		len++;
	}
	return len;
}

void uart_debug_init(uart_device_number_t uart_channel, uint32_t baud_rate)
{
    s_uart_debug_channel = uart_channel;
	uart_configure(s_uart_debug_channel, baud_rate, 8, UART_STOP_1, UART_PARITY_NONE);
}

void uart_configure(uart_device_number_t channel, uint32_t baud_rate, uart_bitwidth_t data_width, uart_stopbit_t stopbit, uart_parity_t parity)
{
    uart_reset(channel);
    assert(data_width >= 5 && data_width <= 8);
    if (data_width == 5)
    {
        assert(stopbit != UART_STOP_2);
    }
    else
    {
        assert(stopbit != UART_STOP_1_5);
    }

    uint32_t stopbit_val = stopbit == UART_STOP_1 ? 0 : 1;
    uint32_t parity_val;
    switch (parity)
    {
        case UART_PARITY_NONE:
            parity_val = 0;
            break;
        case UART_PARITY_ODD:
            parity_val = 1;
            break;
        case UART_PARITY_EVEN:
            parity_val = 3;
            break;
        default:
            assert(!"Invalid parity");
            break;
    }

#ifdef _FPGA
    uint32_t freq = BUSFREQ;
#else
    uint32_t freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_UART0_SCLK + channel);
#endif
    uint32_t divisor = freq / baud_rate;
    uint8_t dlh = divisor >> 12;
    uint8_t dll = (divisor - (dlh << 12)) / __UART_BRATE_CONST;
    uint8_t dlf = divisor - (dlh << 12) - dll * __UART_BRATE_CONST;

    if(dlh == 0 && dll == 0)
    {
        dll = 1;
        dlf = 0;
    }

    /* Set UART registers */

    uart[channel]->LCR |= 1u << 7;
    uart[channel]->DLH = dlh;
    uart[channel]->DLL = dll;
    uart[channel]->DLF = dlf;
    uart[channel]->LCR = 0;
    uart[channel]->LCR = (data_width - 5) | (stopbit_val << 2) | (parity_val << 3);
    uart[channel]->LCR &= ~(1u << 7);
    uart[channel]->IER |= 0x5; /* 0x80 */; /* THRE */
    uart[channel]->FCR = UART_RECEIVE_FIFO_1 << 6 | UART_SEND_FIFO_8 << 4 | 0x1 << 3 | 0x1;
}

int uart_receive_data(uart_device_number_t channel, char *buffer, size_t buf_len)
{
    size_t i = 0;
    for(i = 0; i < buf_len; i++)
    {
        if(uart[channel]->LSR & 1)
            buffer[i] = (char)(uart[channel]->RBR & 0xff);
        else
            break;
    }
    return i;
}

volatile int g_write_count = 0;


int uart_send_data(uart_device_number_t channel, const char *buffer, size_t buf_len)
{
    g_write_count = 0;
    while(g_write_count < buf_len)
    {
        uart_channel_putc(*buffer++, channel);
        g_write_count++;
    }
    return g_write_count;
}

static int uart_irq_callback(void *param)
{
    uart_instance_t *uart_instance = (uart_instance_t *)param;
    uint32_t v_channel = uart_instance->uart_num;
    uint8_t v_int_status = uart[v_channel]->IIR & 0xF;

    if(v_int_status == UART_INTERRUPT_SEND)
    {
        if(uart_instance->uart_send_instance.callback != NULL)
            uart_instance->uart_send_instance.callback(uart_instance->uart_send_instance.ctx);
    } else if(v_int_status == UART_INTERRUPT_RECEIVE || v_int_status == UART_INTERRUPT_CHARACTER_TIMEOUT)
    {
        if(uart_instance->uart_receive_instance.callback != NULL)
            uart_instance->uart_receive_instance.callback(uart_instance->uart_receive_instance.ctx);
    }
    else
    {
        uart[v_channel]->USR = uart[v_channel]->USR;
    }
    return 0;
}

void uart_set_send_trigger(uart_device_number_t channel, uart_send_trigger_t trigger)
{
    uart[channel]->STET = trigger;
}

void uart_set_receive_trigger(uart_device_number_t channel, uart_receive_trigger_t trigger)
{
    uart[channel]->SRT = trigger;
}

void uart_irq_register(uart_device_number_t channel, uart_interrupt_mode_t interrupt_mode, plic_irq_callback_t uart_callback, void *ctx, uint32_t priority)
{
    if(interrupt_mode == UART_SEND)
    {
        uart[channel]->IER |= 0x2;
        g_uart_instance[channel].uart_send_instance.callback = uart_callback;
        g_uart_instance[channel].uart_send_instance.ctx = ctx;
    } else if(interrupt_mode == UART_RECEIVE)
    {
        uart[channel]->IER |= 0x1;
        g_uart_instance[channel].uart_receive_instance.callback = uart_callback;
        g_uart_instance[channel].uart_receive_instance.ctx = ctx;
    }
    g_uart_instance[channel].uart_num = channel;
    plic_set_priority(IRQN_UART0_INTERRUPT + channel, priority);
    plic_irq_register(IRQN_UART0_INTERRUPT + channel, uart_irq_callback, &g_uart_instance[channel]);
    plic_irq_enable(IRQN_UART0_INTERRUPT + channel);
}

void uart_irq_unregister(uart_device_number_t channel, uart_interrupt_mode_t interrupt_mode)
{
    if(interrupt_mode == UART_SEND)
    {
        uart[channel]->IER &= ~(0x2);
        g_uart_instance[channel].uart_send_instance.callback = NULL;
        g_uart_instance[channel].uart_send_instance.ctx = NULL;
    } else if(interrupt_mode == UART_RECEIVE)
    {
        uart[channel]->IER &= ~(0x1);
        g_uart_instance[channel].uart_receive_instance.callback = NULL;
        g_uart_instance[channel].uart_receive_instance.ctx = NULL;
    }
    if((uart[channel]->IER & 0x3) == 0)
    {
        plic_irq_unregister(IRQN_UART0_INTERRUPT + channel);
        plic_irq_disable(IRQN_UART0_INTERRUPT + channel);
    }
}

void uart_set_work_mode(uart_device_number_t uart_channel, uart_work_mode_t work_mode)
{
    volatile uart_tcr_t *tcr;
    switch(work_mode)
    {
        case UART_IRDA:
            uart[uart_channel]->MCR |= (1 << 6);
            break;
        case UART_RS485_FULL_DUPLEX:
            tcr = (uart_tcr_t *)&uart[uart_channel]->TCR;
            tcr->xfer_mode = 0;
            tcr->rs485_en = 1;
            break;
        case UART_RS485_HALF_DUPLEX:
            tcr = (uart_tcr_t *)&uart[uart_channel]->TCR;
            tcr->xfer_mode = 2;
            tcr->rs485_en = 1;
            uart[uart_channel]->DE_EN = 1;
            uart[uart_channel]->RE_EN = 1;
            break;
        default:
            uart[uart_channel]->MCR &= ~(1 << 6);
            uart[uart_channel]->TCR &= ~(1 << 0);
            break;
    }
}

void uart_set_rede_polarity(uart_device_number_t uart_channel, uart_rs485_rede_t rede, uart_polarity_t polarity)
{
    volatile uart_tcr_t *tcr = (uart_tcr_t *)&uart[uart_channel]->TCR;
    switch(rede)
    {
        case UART_RS485_DE:
            tcr->de_pol = polarity;
            break;
        case UART_RS485_RE:
            tcr->re_pol = polarity;
            break;
        default:
            tcr->de_pol = polarity;
            tcr->re_pol = polarity;
            break;
    }
}

void uart_set_rede_enable(uart_device_number_t uart_channel, uart_rs485_rede_t rede, bool enable)
{
    switch(rede)
    {
        case UART_RS485_DE:
            uart[uart_channel]->DE_EN = enable;
            break;
        case UART_RS485_RE:
            uart[uart_channel]->RE_EN = enable;
            break;
        default:
            uart[uart_channel]->DE_EN = enable;
            uart[uart_channel]->RE_EN = enable;
            break;
    }
}

void uart_set_det(uart_device_number_t uart_channel, uart_det_mode_t det_mode, size_t time)
{
    volatile uart_det_t *det = (uart_det_t *)&uart[uart_channel]->DET;
#ifdef _FPGA
    uint32_t freq = BUSFREQ;
#else
    uint32_t freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_UART0_SCLK + uart_channel);
#endif
    uint32_t v_clk_cnt = time * freq / 1e9 + 1;
    if(v_clk_cnt > 255)
        v_clk_cnt = 255;
    switch(det_mode)
    {
        case UART_DE_ASSERTION:
            det->de_assertion_time = v_clk_cnt;
            break;
        case UART_DE_DE_ASSERTION:
            det->de_de_assertion_time = v_clk_cnt;
            break;
        default:
            det->de_assertion_time = v_clk_cnt;
            det->de_de_assertion_time = v_clk_cnt;
            break;
    }
}

void uart_set_tat(uart_device_number_t uart_channel, uart_tat_mode_t tat_mode, size_t time)
{
    volatile uart_tat_t *tat = (uart_tat_t *)&uart[uart_channel]->TAT;
#ifdef _FPGA
    uint32_t freq = BUSFREQ;
#else
    uint32_t freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_UART0_SCLK + uart_channel);
#endif
    uint32_t v_clk_cnt = time * freq / 1e9 + 1;
    if(v_clk_cnt > 65536)
        v_clk_cnt = 65536;
    switch(tat_mode)
    {
        case UART_DE_TO_RE:
            tat->de_to_re = v_clk_cnt - 1;
            break;
        case UART_RE_TO_DE:
            tat->re_to_de = v_clk_cnt - 1;
            break;
        default:
            tat->de_to_re = v_clk_cnt - 1;
            tat->re_to_de = v_clk_cnt - 1;
            break;
    }
}

void uart_auto_flow_enable(uart_device_number_t uart_channel)
{
    uart[uart_channel]->MCR |= (1 << 5 | 1 << 1);
}

void uart_auto_flow_disable(uart_device_number_t uart_channel)
{
    uart[uart_channel]->MCR &= ~(1 << 5 | 1 << 1);
}
