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
#include "io.h"
#include "i2s.h"

volatile i2s_t *const i2s_slave[1] =
{
    (volatile i2s_t *)I2S2_BASE_ADDR
};

static int i2s_slave_recv_channel_enable(i2s_device_number_t device_num,
                            i2s_channel_num_t channel_num, uint32_t enable)
{
    rer_t u_rer;

    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;
    u_rer.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].rer);
    u_rer.rer.rxchenx = enable;
    writel(u_rer.reg_data, &i2s_slave[device_num]->channel[channel_num].rer);
    return 0;
}

static int i2s_slave_transmit_channel_enable(i2s_device_number_t device_num,
    i2s_channel_num_t channel_num, uint32_t enable)
{
    ter_t u_ter;

    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    u_ter.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].ter);
    u_ter.ter.txchenx = enable;
    writel(u_ter.reg_data, &i2s_slave[device_num]->channel[channel_num].ter);
    return 0;
}

static void i2s_slave_receive_enable(i2s_device_number_t device_num, i2s_channel_num_t channel_num)
{
    irer_t u_irer;

    u_irer.reg_data = readl(&i2s_slave[device_num]->irer);
    u_irer.irer.rxen = 1;
    writel(u_irer.reg_data, &i2s_slave[device_num]->irer);
    /* Receiver block enable */

    i2s_slave_recv_channel_enable(device_num, channel_num, 1);
    /* Receive channel enable */
}

static void i2s_slave_transimit_enable(i2s_device_number_t device_num, i2s_channel_num_t channel_num)
{
    iter_t u_iter;

    u_iter.reg_data = readl(&i2s_slave[device_num]->iter);
    u_iter.iter.txen = 1;
    writel(u_iter.reg_data, &i2s_slave[device_num]->iter);
    /* Transmitter block enable */

    i2s_slave_transmit_channel_enable(device_num, channel_num, 1);
    /* Transmit channel enable */
}

static void i2s_slave_set_enable(i2s_device_number_t device_num, uint32_t enable)
{
    ier_t u_ier;

    u_ier.reg_data = readl(&i2s_slave[device_num]->ier);
    u_ier.ier.ien = enable;
    writel(u_ier.reg_data, &i2s_slave[device_num]->ier);
}

void i2s_slave_disable_block(i2s_device_number_t device_num, i2s_transmit_t rxtx_mode)
{
    irer_t u_irer;
    iter_t u_iter;

    if (rxtx_mode == I2S_RECEIVER)
    {
        u_irer.reg_data = readl(&i2s_slave[device_num]->irer);
        u_irer.irer.rxen = 0;
        writel(u_irer.reg_data, &i2s_slave[device_num]->irer);
        /* Receiver block disable */

        i2s_slave[device_num]->rxffr = 1;
    }
    else
    {
        u_iter.reg_data = readl(&i2s_slave[device_num]->iter);
        u_iter.iter.txen = 0;
        writel(u_iter.reg_data, &i2s_slave[device_num]->iter);
        /* Transmitter block disable */

        i2s_slave[device_num]->txffr = 1;
    }
}

void i2s_slave_enable_block(i2s_device_number_t device_num, i2s_transmit_t rxtx_mode)
{
    irer_t u_irer;
    iter_t u_iter;

    if (rxtx_mode == I2S_RECEIVER)
    {
        u_irer.reg_data = readl(&i2s_slave[device_num]->irer);
        u_irer.irer.rxen = 1;
        writel(u_irer.reg_data, &i2s_slave[device_num]->irer);
        /* Receiver block disable */
    }
    else
    {
        u_iter.reg_data = readl(&i2s_slave[device_num]->iter);
        u_iter.iter.txen = 1;
        writel(u_iter.reg_data, &i2s_slave[device_num]->iter);
        /* Transmitter block disable */
    }
}


static int i2s_slave_set_rx_word_length(i2s_device_number_t device_num,
               i2s_word_length_t word_length,
               i2s_channel_num_t channel_num)
{
    rcr_tcr_t u_rcr;

    if (word_length > RESOLUTION_32_BIT || word_length < IGNORE_WORD_LENGTH)
        return -1;
    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    u_rcr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].rcr);
    u_rcr.rcr_tcr.wlen = word_length;
    writel(u_rcr.reg_data, &i2s_slave[device_num]->channel[channel_num].rcr);
    return 0;
}

static int i2s_slave_set_tx_word_length(i2s_device_number_t device_num,
               i2s_word_length_t word_length,
               i2s_channel_num_t channel_num)
{
    rcr_tcr_t u_tcr;

    if (word_length > RESOLUTION_32_BIT || word_length < IGNORE_WORD_LENGTH)
        return -1;
    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    u_tcr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].tcr);
    u_tcr.rcr_tcr.wlen = word_length;
    writel(u_tcr.reg_data, &i2s_slave[device_num]->channel[channel_num].tcr);
    return 0;
}

static int i2s_slave_set_rx_threshold(i2s_device_number_t device_num,
             i2s_fifo_threshold_t threshold,
             i2s_channel_num_t channel_num)
{
    rfcr_t u_rfcr;

    if (threshold < TRIGGER_LEVEL_1 || threshold > TRIGGER_LEVEL_16)
        return -1;
    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    u_rfcr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].rfcr);
    u_rfcr.rfcr.rxchdt = threshold;
    writel(u_rfcr.reg_data, &i2s_slave[device_num]->channel[channel_num].rfcr);

    return 0;
}

static int i2s_slave_set_tx_threshold(i2s_device_number_t device_num,
             i2s_fifo_threshold_t threshold,
             i2s_channel_num_t channel_num)
{
    tfcr_t u_tfcr;

    if (threshold < TRIGGER_LEVEL_1 || threshold > TRIGGER_LEVEL_16)
        return -1;
    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    u_tfcr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].tfcr);
    u_tfcr.tfcr.txchet = threshold;
    writel(u_tfcr.reg_data, &i2s_slave[device_num]->channel[channel_num].tfcr);
    return 0;
}

static int i2s_slave_set_mask_interrupt(i2s_device_number_t device_num,
               i2s_channel_num_t channel_num,
               uint32_t rx_available_int, uint32_t rx_overrun_int,
               uint32_t tx_empty_int, uint32_t tx_overrun_int)
{
    imr_t u_imr;

    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;
    u_imr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].imr);

    if (rx_available_int == 1)
        u_imr.imr.rxdam = 1;
    else
        u_imr.imr.rxdam = 0;
    if (rx_overrun_int == 1)
        u_imr.imr.rxfom = 1;
    else
        u_imr.imr.rxfom = 0;

    if (tx_empty_int == 1)
        u_imr.imr.txfem = 1;
    else
        u_imr.imr.txfem = 0;
    if (tx_overrun_int == 1)
        u_imr.imr.txfom = 1;
    else
        u_imr.imr.txfom = 0;
    writel(u_imr.reg_data, &i2s_slave[device_num]->channel[channel_num].imr);
    return 0;
}

static int i2s_slave_transmit_dma_enable(i2s_device_number_t device_num, uint32_t enable)
{
    ccr_t u_ccr;

    if (device_num >= I2S_DEVICE_MAX)
        return -1;

    u_ccr.reg_data = readl(&i2s_slave[device_num]->ccr);
    u_ccr.ccr.dma_tx_en = enable;
    writel(u_ccr.reg_data, &i2s_slave[device_num]->ccr);

    return 0;
}

static int i2s_slave_receive_dma_enable(i2s_device_number_t device_num, uint32_t enable)
{
    ccr_t u_ccr;

    if (device_num >= I2S_DEVICE_MAX)
        return -1;

    u_ccr.reg_data = readl(&i2s_slave[device_num]->ccr);
    u_ccr.ccr.dma_rx_en = enable;
    writel(u_ccr.reg_data, &i2s_slave[device_num]->ccr);

    return 0;
}

int i2s_slave_receive_data(i2s_device_number_t device_num, i2s_channel_num_t channel_num, uint64_t *buf, size_t buf_len)
{
    uint32_t i = 0;
    isr_t u_isr;

    readl(&i2s_slave[device_num]->channel[channel_num].ror);
    /*clear over run*/

    for (i = 0; i < buf_len;)
    {
        u_isr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].isr);
        if (u_isr.isr.rxda == 1)
        {
            buf[i] = readl(&i2s_slave[device_num]->channel[channel_num].left_rxtx);
            buf[i] <<= 32;
            buf[i++] |= readl(&i2s_slave[device_num]->channel[channel_num].right_rxtx);
        }
    }
    return 0;
}

int i2s_slave_send_data(i2s_device_number_t device_num, i2s_channel_num_t channel_num, const uint8_t *pcm, size_t buf_len,
                  size_t single_length)
{
    isr_t u_isr;
    uint32_t left_buffer = 0;
    uint32_t right_buffer = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    if (channel_num < I2S_CHANNEL_0 || channel_num > I2S_CHANNEL_3)
        return -1;

    buf_len = buf_len / (single_length / 8) / 2; /* sample num */
    readl(&i2s_slave[device_num]->channel[channel_num].tor);
    /* read clear overrun flag */

    for (j = 0; j < buf_len;)
    {
        u_isr.reg_data = readl(&i2s_slave[device_num]->channel[channel_num].isr);
        if (u_isr.isr.txfe == 1)
        {
            switch(single_length)
            {
                case 16:
                    left_buffer = ((uint16_t *)pcm)[i++];
                    right_buffer = ((uint16_t *)pcm)[i++];
                    break;
                case 24:
                    left_buffer = 0;
                    left_buffer |= pcm[i++];
                    left_buffer |= pcm[i++] << 8;
                    left_buffer |= pcm[i++] << 16;
                    right_buffer = 0;
                    right_buffer |= pcm[i++];
                    right_buffer |= pcm[i++] << 8;
                    right_buffer |= pcm[i++] << 16;
                    break;
                case 32:
                    left_buffer = ((uint32_t *)pcm)[i++];
                    right_buffer = ((uint32_t *)pcm)[i++];
                    break;
                default:
                    left_buffer = pcm[i++];
                    right_buffer = pcm[i++];
                    break;
            }
            writel(left_buffer, &i2s_slave[device_num]->channel[channel_num].left_rxtx);
            writel(right_buffer, &i2s_slave[device_num]->channel[channel_num].right_rxtx);
            j++;
        }
    }
    return 0;
}

void i2s_slave_rx_channel_config(i2s_device_number_t device_num,
    i2s_channel_num_t channel_num,
    i2s_word_length_t word_length,
    i2s_word_select_cycles_t word_select_size,
    i2s_fifo_threshold_t trigger_level,
    i2s_work_mode_t word_mode)
{
    i2s_slave_recv_channel_enable(device_num, channel_num, 0);
    /* Receive channel disable */
#if 0
    writel(0, &i2s_slave[device_num]->channel[channel_num].ter);
    /* disable tx */
#endif
    writel(1, &i2s_slave[device_num]->channel[channel_num].rff);
    /* flash individual fifo */

    writel(1, &i2s_slave[device_num]->rxffr);
    /* flush tx fifo*/

    i2s_slave_set_rx_word_length(device_num, word_length, channel_num);
    /* Word buf_len is RESOLUTION_32_BIT */
#if 0
    i2s_slave_master_configure(device_num,
        word_select_size, NO_CLOCK_GATING, word_mode);
    /* word select size is 32 bits,no clock gating */
#endif
    i2s_slave_set_rx_threshold(device_num, trigger_level, channel_num);
    /* Interrupt trigger when FIFO level is 8 */

    readl(&i2s_slave[device_num]->channel[channel_num].ror);
    readl(&i2s_slave[device_num]->channel[channel_num].tor);

    i2s_slave_recv_channel_enable(device_num, channel_num, 1);
}

void i2s_slave_tx_channel_config(i2s_device_number_t device_num,
    i2s_channel_num_t channel_num,
    i2s_word_length_t word_length,
    i2s_word_select_cycles_t word_select_size,
    i2s_fifo_threshold_t trigger_level,
    i2s_work_mode_t word_mode)
{
#if 0
    writel(0, &i2s[device_num]->channel[channel_num].rer);
    /* disable rx */
#endif
    i2s_slave_transmit_channel_enable(device_num, channel_num, 0);
    /* Transmit channel disable */

    writel(1, &i2s_slave[device_num]->txffr);
    /* flush tx fifo */
    writel(1, &i2s_slave[device_num]->channel[channel_num].tff);
    /* flush individual fifo */

    i2s_slave_set_tx_word_length(device_num, word_length, channel_num);
    /* Word buf_len is RESOLUTION_16_BIT */
#if 0
    i2s_slave_master_configure(device_num, word_select_size, NO_CLOCK_GATING, word_mode);
#endif
    /* word select size is 16 bits,gating after 16 bit */
    i2s_slave_set_tx_threshold(device_num, trigger_level, channel_num);
    /* Interrupt trigger when FIFO level is 8 */

    i2s_slave_transmit_channel_enable(device_num, channel_num, 1);
}

void i2s_slave_init(i2s_device_number_t device_num, i2s_transmit_t rxtx_mode, uint32_t channel_mask, bool enable_dma)
{
    /*96k:5,44k:12,24k:23,22k:25 16k:35 sampling*/
    /*sample rate*32bit*2 =75MHz/((N+1)*2) */
    i2s_slave_set_enable(device_num, 1);

    if (rxtx_mode == I2S_TRANSMITTER)
    {
        for (int i=0; i<4; i++)
        {
            if ((channel_mask & 0x3) == 0x3)
            {
                i2s_slave_set_mask_interrupt(device_num, I2S_CHANNEL_0 + i, 1, 1, 1, 1);
                i2s_slave_transimit_enable(device_num, I2S_CHANNEL_0 + i);
            }
            else
            {
                i2s_slave_transmit_channel_enable(device_num, I2S_CHANNEL_0 + i, 0);
            }
            channel_mask >>= 2;
        }
        if(true == enable_dma)
            i2s_slave_transmit_dma_enable(device_num, 1);
        else
            i2s_slave_transmit_dma_enable(device_num, 0);
    }
    else
    {
        for (int i=0; i<4; i++)
        {
            if ((channel_mask & 0x3) == 0x3)
            {
                i2s_slave_set_mask_interrupt(device_num, I2S_CHANNEL_0 + i, 1, 1, 1, 1);
                i2s_slave_receive_enable(device_num, I2S_CHANNEL_0 + i);
            }
            else
            {
                i2s_slave_recv_channel_enable(device_num, I2S_CHANNEL_0 + i, 0);
            }
            channel_mask >>= 2;
        }
		if(true == enable_dma)
            i2s_slave_receive_dma_enable(device_num, 1);
        else
            i2s_slave_receive_dma_enable(device_num, 0);
    }
}


