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
#include <k510.h>
#include <mailbox.h>
#include <interrupt.h>
#include <cache.h>

#define TAG "MAILBOX CPU2DSP INT TEST"

uint32_t int_status = 0;

volatile uint8_t* cpu_tx[8];
volatile uint8_t* cpu_rx[8];

#define SINGLE_DIR_CHAN_NUM     8
#define SHARE_MEM_START         0x087ffe00
#define MSG_SIZE                0x20
#define CPU_TX_CHAN_0           (SHARE_MEM_START)
#define CPU_TX_CHAN_1           (CPU_TX_CHAN_0 + MSG_SIZE)
#define CPU_TX_CHAN_2           (CPU_TX_CHAN_1 + MSG_SIZE)
#define CPU_TX_CHAN_3           (CPU_TX_CHAN_2 + MSG_SIZE)
#define CPU_TX_CHAN_4           (CPU_TX_CHAN_3 + MSG_SIZE)
#define CPU_TX_CHAN_5           (CPU_TX_CHAN_4 + MSG_SIZE)
#define CPU_TX_CHAN_6           (CPU_TX_CHAN_5 + MSG_SIZE)
#define CPU_TX_CHAN_7           (CPU_TX_CHAN_6 + MSG_SIZE)
#define CPU_RX_CHAN_0           (CPU_TX_CHAN_7 + MSG_SIZE)
#define CPU_RX_CHAN_1           (CPU_RX_CHAN_0 + MSG_SIZE)
#define CPU_RX_CHAN_2           (CPU_RX_CHAN_1 + MSG_SIZE)
#define CPU_RX_CHAN_3           (CPU_RX_CHAN_2 + MSG_SIZE)
#define CPU_RX_CHAN_4           (CPU_RX_CHAN_3 + MSG_SIZE)
#define CPU_RX_CHAN_5           (CPU_RX_CHAN_4 + MSG_SIZE)
#define CPU_RX_CHAN_6           (CPU_RX_CHAN_5 + MSG_SIZE)
#define CPU_RX_CHAN_7           (CPU_RX_CHAN_6 + MSG_SIZE) 

const unsigned int CPU_TX_ADDR[SINGLE_DIR_CHAN_NUM] = {
    CPU_TX_CHAN_0,
    CPU_TX_CHAN_1,
    CPU_TX_CHAN_2,
    CPU_TX_CHAN_3,
    CPU_TX_CHAN_4,
    CPU_TX_CHAN_5,
    CPU_TX_CHAN_6,
    CPU_TX_CHAN_7,
};

const unsigned int CPU_RX_ADDR[SINGLE_DIR_CHAN_NUM] = {
    CPU_RX_CHAN_0,
    CPU_RX_CHAN_1,
    CPU_RX_CHAN_2,
    CPU_RX_CHAN_3,
    CPU_RX_CHAN_4,
    CPU_RX_CHAN_5,
    CPU_RX_CHAN_6,
    CPU_RX_CHAN_7,
};

void processing_data(int index)
{
    int i;

    // for (i = 0; i < 32; i++)
    // {
    //     if (i % 8 == 0)
    //     {
    //         k510_logi("\r\n");
    //         k510_logi("channel %d dsp receive[%2d]: ", index, i);
    //     }
    //     k510_logi("%2d ", cpu_tx[index][i]);
    // }
    for (i = 0; i < 32; i++)
    {
        cpu_rx[index][i] = cpu_tx[index][i] + 4;
    }
    // for (i = 0; i < 32; i++)
    // {
    //     if (i % 8 == 0)
    //     {
    //         k510_logi("\r\n");
    //         k510_logi("channel %d dsp send[%2d]: ", index, i);
    //     }
    //     k510_logi("%2d ", cpu_rx[index][i]);
    // }
}

int mailbox_int_irq_on(void *ctx)
{
    for(uint32_t i = 0; i < MAILBOX_INT_NUMBERMAX; i++)
    {
        if((mailbox->cpu2dsp_int_status >> (i * 2)) & 0x3)
        {
            // k510_logi("%d MAILBOTX INT\n", i);
            int_status |= 1 << i;
            mailbox->cpu2dsp_int_clr = i;
            mailbox->cpu2dsp_int_clr = i;
            mailbox->cpu2dsp_int_clr = i;
            if (i < 8)
            {
                mailbox_dsp2cpu_send_int(i + 8);
                processing_data(i);
                mailbox_dsp2cpu_send_int(i);
            }
            else
            {
                /* cpu has received data */
            }
        }
    }
    return 0;
}

int main(void)
{

    int i;
    int m = 0;

    for (i = 0; i < SINGLE_DIR_CHAN_NUM; i++)
    {
        cpu_tx[i] = (volatile uint8_t*)CPU_TX_ADDR[i];
        cpu_rx[i] = (volatile uint8_t*)CPU_RX_ADDR[i];
    }

    /* disable cache */
    cache_disable();
    plic_interrupt_enable();
    plic_set_priority(IRQN_CPU2DSP_INTERRUPT, 1);
    plic_irq_register(IRQN_CPU2DSP_INTERRUPT, mailbox_int_irq_on, NULL);
    plic_irq_enable(IRQN_CPU2DSP_INTERRUPT);
    mailbox_cpu2dsp_int_enable();
    while(1)
    {
        // /* 一直在触发中断，直接写零 */
        // mailbox_dsp2cpu_send_int(0);
        // mailbox_dsp2cpu_send_int(1);
        // sleep(100);
        
        // processing_data(0);
        // mailbox_dsp2cpu_send_int(0);
        // sleep(3);
    }
}
