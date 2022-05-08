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
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "interrupt.h"

typedef struct _uart
{
    union
    {
        volatile uint32_t RBR;
        volatile uint32_t DLL;
        volatile uint32_t THR;
    };

    union
    {
        volatile uint32_t DLH;
        volatile uint32_t IER;
    };

    union
    {
        volatile uint32_t FCR;
        volatile uint32_t IIR;
    };

    volatile uint32_t LCR;
    volatile uint32_t MCR;
    volatile uint32_t LSR;
    volatile uint32_t MSR;

    volatile uint32_t SCR;
    volatile uint32_t LPDLL;
    volatile uint32_t LPDLH;

    volatile uint32_t reserved1[2];

    union
    {
        volatile uint32_t SRBR[16];
        volatile uint32_t STHR[16];
    };

    volatile uint32_t FAR;
    volatile uint32_t TFR;
    volatile uint32_t RFW;
    volatile uint32_t USR;
    volatile uint32_t TFL;
    volatile uint32_t RFL;
    volatile uint32_t SRR;
    volatile uint32_t SRTS;
    volatile uint32_t SBCR;
    volatile uint32_t SDMAM;
    volatile uint32_t SFE;
    volatile uint32_t SRT;
    volatile uint32_t STET;
    volatile uint32_t HTX;
    volatile uint32_t DMASA;
    volatile uint32_t TCR;
    volatile uint32_t DE_EN;
    volatile uint32_t RE_EN;
    volatile uint32_t DET;
    volatile uint32_t TAT;
    volatile uint32_t DLF;
    volatile uint32_t RAR;
    volatile uint32_t TAR;
    volatile uint32_t LCR_EXT;
    volatile uint32_t reserved2[9];
    volatile uint32_t CPR;
    volatile uint32_t UCV;
    volatile uint32_t CTR;
} uart_t;

typedef enum _uart_device_number
{
    UART_DEVICE_0,
    UART_DEVICE_1,
    UART_DEVICE_2,
    UART_DEVICE_3,
    UART_DEVICE_MAX,
} uart_device_number_t;

typedef enum _uart_bitwidth
{
    UART_BITWIDTH_5BIT = 5,
    UART_BITWIDTH_6BIT,
    UART_BITWIDTH_7BIT,
    UART_BITWIDTH_8BIT,
} uart_bitwidth_t;

typedef enum _uart_stopbit
{
    UART_STOP_1,
    UART_STOP_1_5,
    UART_STOP_2
} uart_stopbit_t;

typedef enum _uart_parity
{
    UART_PARITY_NONE,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
} uart_parity_t;

typedef enum _uart_interrupt_mode
{
    UART_SEND = 1,
    UART_RECEIVE = 2,
} uart_interrupt_mode_t;

typedef enum _uart_send_trigger
{
    UART_SEND_FIFO_0,
    UART_SEND_FIFO_4,
    UART_SEND_FIFO_8,
    UART_SEND_FIFO_16,
} uart_send_trigger_t;

typedef enum _uart_receive_trigger
{
    UART_RECEIVE_FIFO_1,
    UART_RECEIVE_FIFO_8,
    UART_RECEIVE_FIFO_16,
    UART_RECEIVE_FIFO_30,
} uart_receive_trigger_t;

typedef struct _uart_tcr
{
    uint32_t rs485_en : 1;
    uint32_t re_pol : 1;
    uint32_t de_pol : 1;
    uint32_t xfer_mode : 2;
    uint32_t reserve : 27;
} uart_tcr_t;

typedef enum _uart_work_mode
{
    UART_NORMAL,
    UART_IRDA,
    UART_RS485_FULL_DUPLEX,
    UART_RS485_HALF_DUPLEX,
} uart_work_mode_t;

typedef enum _uart_rs485_rede
{
    UART_RS485_DE,
    UART_RS485_RE,
    UART_RS485_REDE,
} uart_rs485_rede_t;

typedef enum _uart_polarity
{
    UART_LOW,
    UART_HIGH,
} uart_polarity_t;

typedef enum _uart_det_mode
{
    UART_DE_ASSERTION,
    UART_DE_DE_ASSERTION,
    UART_DE_ALL,
} uart_det_mode_t;

typedef struct _uart_det
{
    uint32_t de_assertion_time : 8;
    uint32_t reserve0 : 8;
    uint32_t de_de_assertion_time : 8;
    uint32_t reserve1 : 8;
} uart_det_t;

typedef enum _uart_tat_mode
{
    UART_DE_TO_RE,
    UART_RE_TO_DE,
    UART_TAT_ALL,
} uart_tat_mode_t;

typedef struct _uart_tat
{
    uint32_t de_to_re : 16;
    uint32_t re_to_de : 16;
} uart_tat_t;

extern volatile uart_t* const  uart[4];

void uart_configure(uart_device_number_t channel, uint32_t baud_rate, uart_bitwidth_t data_width, uart_stopbit_t stopbit, uart_parity_t parity);
void uart_debug_init(uart_device_number_t uart_channel, uint32_t baud_rate);
int uart_outbyte(int c);
int uart_puts(const char *s);

void uart_irq_register(uart_device_number_t channel, uart_interrupt_mode_t interrupt_mode, plic_irq_callback_t uart_callback, void *ctx, uint32_t priority);
void uart_irq_unregister(uart_device_number_t channel, uart_interrupt_mode_t interrupt_mode);
void uart_set_send_trigger(uart_device_number_t channel, uart_send_trigger_t trigger);
void uart_set_receive_trigger(uart_device_number_t channel, uart_receive_trigger_t trigger);
int uart_receive_data(uart_device_number_t channel, char *buffer, size_t buf_len);
int uart_send_data(uart_device_number_t channel, const char *buffer, size_t buf_len);

/**
 * @brief       Set uart work mode
 *
 * @param[in]   uart_channel        Uart index
 * @param[in]   work_mode           Work mode
                                    0:uart
                                    1: infrared
                                    2:full duplex rs485, control re and de manually
                                    3:half duplex rs485, control re and de automatically
 *
 */
void uart_set_work_mode(uart_device_number_t uart_channel, uart_work_mode_t work_mode);

/**
 * @brief       Set re or de driver enable polarity
 *
 * @param[in]   uart_channel        Uart index
 * @param[in]   rede                re or de
                                    0:de
                                    1:re
                                    2:de and re
 * @param[in]   polarity            Polarity
                                    0:signal is active low
                                    1:signal is active high
 *
 */
void uart_set_rede_polarity(uart_device_number_t uart_channel, uart_rs485_rede_t rede, uart_polarity_t polarity);

/**
 * @brief       Set rs485 de and re signal driver output enable
 *
 * @param[in]   uart_channel        Uart index
 * @param[in]   rede                0:de
                                    1:re
                                    2:de and re
 * @param[in]   enable              0:de-assert signal
                                    1:assert signal
 *
 */
void uart_set_rede_enable(uart_device_number_t uart_channel, uart_rs485_rede_t rede, bool enable);

/**
 * @brief       Set turn around time between switch of 're' and 'de' signals
 *
 * @param[in]   uart_channel        Uart index
 * @param[in]   tat_mode            0:de to re
                                    1:re to de
 * @param[in]   time                turn around time nanosecond
 *
 */
void uart_set_tat(uart_device_number_t uart_channel, uart_tat_mode_t tat_mode, size_t time);

/**
 * @brief       Set driver output enable time used to control de assertion and de-assertion timeing of 'de' signal
 *
 * @param[in]   uart_channel        Uart index
 * @param[in]   det_mode            0:de assertion
                                    1:de de-assertion
 * @param[in]   time                driver output enable time nanosecond
 *
 */
void uart_set_det(uart_device_number_t uart_channel, uart_det_mode_t det_mode, size_t time);

void uart_auto_flow_enable(uart_device_number_t uart_channel);

void uart_auto_flow_disable(uart_device_number_t uart_channel);

/*
 * Exported functions
 */
extern void uart_putc(int c);
extern int outbyte(int c);

#endif	// __UART_H__
