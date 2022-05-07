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
#include <string.h>
#include <stdio.h>
#include "platform.h"
#include "spi.h"
#include "dmac.h"

volatile spi_t *const spi[4] =
{
    (volatile spi_t *)SPI0_BASE_ADDR,
    (volatile spi_t *)SPI1_BASE_ADDR,
    (volatile spi_t *)SPI2_BASE_ADDR,
    (volatile spi_t *)SPI3_BASE_ADDR
};

static uint8_t dfs_offset = 0, frf_offset = 22, work_mode_offset = 8, tmod_offset = 10;

void spi_init(spi_device_num_t spi_num, uint32_t baud)
{
    volatile spi_t *spi_handle = spi[spi_num];
    spi_handle->baudr = baud;
    spi_handle->imr = 0x00;
    spi_handle->dmacr = 0x00;
    spi_handle->dmatdlr = 0x10;
    spi_handle->dmardlr = 0x00;
    spi_handle->ser = 0x00;
    spi_handle->ssienr = 0x00;
    spi_handle->ctrlr0 = (0 << work_mode_offset) | (0 << frf_offset) | ((8 - 1) << dfs_offset);
    spi_handle->spi_ctrlr0 = 0;
}

void spi_set_tmod(spi_device_num_t spi_num, uint32_t tmod)
{
    volatile spi_t *spi_handle = spi[spi_num];
    uint32_t org = spi_handle->ctrlr0 & (~(3 << tmod_offset));
    spi_handle->ctrlr0 = org | (tmod << tmod_offset);
}

void spi_send_data(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, const uint8_t *tx_buff, size_t tx_len)
{
    size_t index, fifo_len;
    spi_set_tmod(spi_num, SPI_TMOD_TRANS);
    volatile spi_t *spi_handle = spi[spi_num];
    spi_handle->ssienr = 0x01;
    spi_handle->ser = 1U;
    uint32_t i = 0;
    while(cmd_len)
    {
        fifo_len = 32 - spi_handle->txflr;
        fifo_len = fifo_len < cmd_len ? fifo_len : cmd_len;

        for(index = 0; index < fifo_len; index++)
            spi_handle->dr[0] = cmd_buff[i++];

        cmd_len -= fifo_len;
    }

    i = 0;
    while(tx_len)
    {
        fifo_len = 32 - spi_handle->txflr;
        fifo_len = fifo_len < tx_len ? fifo_len : tx_len;
        for(index = 0; index < fifo_len; index++)
            spi_handle->dr[0] = tx_buff[i++];
        tx_len -= fifo_len;
    }
    while((spi_handle->sr & 0x05) != 0x04)
        ;
    spi_handle->ser = 0x00;
    spi_handle->ssienr = 0x00;
}

void spi_receive_data(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, uint8_t *rx_buff, size_t rx_len)
{
    size_t index, fifo_len;
    if(cmd_len == 0)
        spi_set_tmod(spi_num, SPI_TMOD_RECV);
    else
        spi_set_tmod(spi_num, SPI_TMOD_EEROM);
    volatile spi_t *spi_handle = spi[spi_num];

    spi_handle->ctrlr1 = (uint32_t)(rx_len - 1);
    spi_handle->ssienr = 0x01;

    uint32_t i = 0;

    if(cmd_len == 0)
    {
        spi_handle->dr[0] = 0xffffffff;
        spi_handle->ser = 1U;
    }
    else
    {
        while(cmd_len)
        {
            fifo_len = 32 - spi_handle->txflr;
            fifo_len = fifo_len < cmd_len ? fifo_len : cmd_len;

            for(index = 0; index < fifo_len; index++)
                spi_handle->dr[0] = cmd_buff[i++];

            spi_handle->ser = 1U;
            cmd_len -= fifo_len;
        }
    }

    i = 0;
    while(rx_len)
    {
        fifo_len = spi_handle->rxflr;
        fifo_len = fifo_len < rx_len ? fifo_len : rx_len;
        for(index = 0; index < fifo_len; index++)
            rx_buff[i++] = (uint8_t)spi_handle->dr[0];
        rx_len -= fifo_len;
    }

    spi_handle->ser = 0x00;
    spi_handle->ssienr = 0x00;
}

//需要保证cmd和rx都为4x
void spi_receive_data_32bit(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, uint8_t *rx_buff, size_t rx_len)
{
    size_t index, fifo_len;
    cmd_len = cmd_len / 4;
    rx_len = rx_len / 4;

    if(cmd_len == 0)
        spi_set_tmod(spi_num, SPI_TMOD_RECV);
    else
        spi_set_tmod(spi_num, SPI_TMOD_EEROM);
    volatile spi_t *spi_handle = spi[spi_num];

    set_bit(&spi_handle->ctrlr0, 0x1f << dfs_offset, 31 << dfs_offset);
    spi_handle->ctrlr1 = (uint32_t)(rx_len - 1);
    spi_handle->ssienr = 0x01;

    uint32_t i = 0;

    if(cmd_len == 0)
    {
        spi_handle->dr[0] = 0xffffffff;
        spi_handle->ser = 1U;
    }
    else
    {
        while(cmd_len)
        {
            fifo_len = 32 - spi_handle->txflr;
            fifo_len = fifo_len < cmd_len ? fifo_len : cmd_len;
            uint32_t temp;
            for(index = 0; index < fifo_len; index++)
            {
                temp = ((cmd_buff[4*i+3]&0xff) 
                    | ((cmd_buff[4*i+2]&0xff) << 8)
                    | ((cmd_buff[4*i+1]&0xff) << 16)
                    | ((cmd_buff[4*i+0]&0xff) << 24));
                spi_handle->dr[0] = temp;
                i++;
            }

            spi_handle->ser = 1U;
            cmd_len -= fifo_len;
        }
    }

    i = 0;
    while(rx_len)
    {
        fifo_len = spi_handle->rxflr;
        fifo_len = fifo_len < rx_len ? fifo_len : rx_len;
        for(index = 0; index < fifo_len; index++)
        {
            uint32_t temp = spi_handle->dr[0];

            rx_buff[i++] = (temp & 0xff000000) >> 24;
            rx_buff[i++] = (temp & 0x00ff0000) >> 16;
            rx_buff[i++] = (temp & 0x0000ff00) >> 8;
            rx_buff[i++] = (temp & 0x000000ff) >> 0;
        }
        rx_len -= fifo_len;
    }

    spi_handle->ser = 0x00;
    spi_handle->ssienr = 0x00;
    set_bit(&spi_handle->ctrlr0, 0x1f << dfs_offset, 7 << dfs_offset);
}

void spi_set_mode(spi_device_num_t spi_num, spi_frame_format_t format, uint8_t inst_width, uint8_t address_width, uint8_t wait_width)
{
    volatile spi_t *spi_handle = spi[spi_num];
    /* SPI Quad Mode */
    uint32_t org = spi_handle->ctrlr0 & (~(3 << frf_offset));
    spi_handle->ctrlr0 = org | (format << frf_offset);

    /* TT1 / 16bit address / 8bit instruction / 0 wait cycle /Instruction and Address will be sent in Standard*/
    spi_handle->spi_ctrlr0 = (address_width << 2) | (inst_width << 8) | (wait_width << 11);
}

void spi_send_data_dma(spi_device_num_t spi_num, uint8_t *tx_buff, size_t tx_len)
{
#ifdef TEST_32BIT
    set_bit(&spi[spi_num]->ctrlr0, 0x1f << dfs_offset, 31 << dfs_offset);
#endif
    spi[spi_num]->dmacr = 0x2; /*enable dma transmit*/
    spi[spi_num]->ssienr = 0x01;

    peri_dma_cfg_t cfg0 = {
        .channel = DMA_CHANNEL_0,
        .dev_sel = SPI0_TX,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = CONTINUOUS_ADDRESS,
#ifdef TEST_32BIT
        .buswidth = FOUR_BYTE,
#else
        .buswidth = ONE_BYTE,
#endif
        .dev_burst_len = 0,
#ifdef TEST_32BIT
        .line_size = tx_len,
#else
        .line_size = tx_len,
#endif
        .saddr = tx_buff,
        .daddr = (void*)(&spi[spi_num]->dr[0]),
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&cfg0);
    spi[spi_num]->ser = 1;
    peri_dma_start(DMA_CHANNEL_0);
    peri_dma_wait_done_or_timeout(DMA_CHANNEL_0);

    // waiting for fifo to be empty and idle
    while ((spi[spi_num]->sr & 0x05) != 0x04)
        ;
    spi[spi_num]->ser = 0x00;
    spi[spi_num]->ssienr = 0x00;
    spi[spi_num]->dmacr = 0;
#ifdef TEST_32BIT
    set_bit(&spi[spi_num]->ctrlr0, 0x1f << dfs_offset, 7 << dfs_offset);
#endif

}

void spi_receive_data_dma(spi_device_num_t spi_num,  uint8_t *cmd_buff,
                                 size_t cmd_len, uint8_t *rx_buff, size_t rx_len)
{
    spi_set_tmod(spi_num, SPI_TMOD_EEROM);
#ifdef TEST_32BIT
    set_bit(&spi[spi_num]->ctrlr0, 0x1f << dfs_offset, 31 << dfs_offset);
    rx_len = rx_len/4;
#endif
    spi[spi_num]->ctrlr1 = (uint32_t)(rx_len - 1);
    spi[spi_num]->dmacr = 0x3;
    spi[spi_num]->ssienr = 0x01;

    peri_dma_cfg_t cfg0 = {
        .channel = DMA_CHANNEL_0,
        .dev_sel = SPI0_TX,
        .ch_priority = 5,
        .mode = LINE_MODE,
        .src_type = CONTINUOUS_ADDRESS,
#ifdef TEST_32BIT
        .buswidth = FOUR_BYTE,
#else
        .buswidth = ONE_BYTE,
#endif
        .dev_burst_len = 0,
        
#ifdef TEST_32BIT
        .line_size = cmd_len,
#else
        .line_size = cmd_len,
#endif
        .saddr = cmd_buff,
        .daddr = (void*)(&spi[spi_num]->dr[0]),
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&cfg0);

    peri_dma_cfg_t cfg1 = {
        .channel = DMA_CHANNEL_1,
        .dev_sel = SPI0_RX,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = FIXED_REG_ADDRESS,
#ifdef TEST_32BIT
        .buswidth = FOUR_BYTE,
#else
        .buswidth = ONE_BYTE,
#endif
        
        .dev_burst_len = 0,

#ifdef TEST_32BIT
        .line_size = rx_len<<2,
#else
        .line_size = rx_len,
#endif

        .saddr = (void*)(&spi[spi_num]->dr[0]),
        .daddr = rx_buff,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&cfg1);

    peri_dma_start(DMA_CHANNEL_1);
    peri_dma_start(DMA_CHANNEL_0);
    spi[spi_num]->ser = 1;
    peri_dma_wait_done_or_timeout(DMA_CHANNEL_0);
    peri_dma_wait_done_or_timeout(DMA_CHANNEL_1);

    spi[spi_num]->ser = 0x00;
    spi[spi_num]->ssienr = 0x00;
#ifdef TEST_32BIT
    set_bit(&spi[spi_num]->ctrlr0, 0x1f << dfs_offset, 7 << dfs_offset);
#endif
}
