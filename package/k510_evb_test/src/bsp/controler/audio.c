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
#include "audio.h"

volatile audio_out_reg_s *audio_out_reg = (volatile audio_out_reg_s *)(long)(AUDIO_BASE_ADDR+0xc00);
volatile audio_in_reg_s  *audio_in_reg  = (volatile audio_in_reg_s *)(long)(AUDIO_BASE_ADDR+0x400);

void audio_i2s_in_init()
{
    audio_in_reg->audio_in_agc_para_4.agc_bypass        = AUDIO_ENABLE;
}

void audio_pdm_in_init(uint32_t pdm_rx_num,
                            audio_in_pdm_edge_e pdm_rx_edge,
                            audio_in_align_e    pdm_rx_align,
                            uint32_t pdm_rx_tx_sample_freq)
{
    /* pmd in init 
       note: andio in 没有DMA使能寄存器,直接用CPU或者dma收发即可 
             dma门限设置成1
    */
    audio_in_reg->audio_in_agc_para_4.agc_bypass = AUDIO_ENABLE;
    audio_in_reg->audio_in_pdm_ch_conf.pdm_chl_num = pdm_rx_num;
    audio_in_reg->audio_in_pdm_ch_conf.pdm_pn_sel  = pdm_rx_edge;

    k510_logci("audio_in_reg->audio_in_pdm_ch_conf.pdm_chl_num = %d\r\n",audio_in_reg->audio_in_pdm_ch_conf.pdm_chl_num);
    k510_logci("audio_in_reg->audio_in_pdm_ch_conf.pdm_pn_sel = %d\r\n",audio_in_reg->audio_in_pdm_ch_conf.pdm_pn_sel);

    if(16000 == pdm_rx_tx_sample_freq)
    {
        audio_in_reg->audio_in_pdm_conf_1.ord_select = 1;

        audio_in_reg->audio_in_pdm_clk_spike.pdmin_clk_spike_cnt = 0;
        audio_in_reg->audio_in_pdm_clk_spike.pdmin_clk_spike_th = 0;

        audio_in_reg->audio_in_pdm_ch_spike.pdmin_ch0_spike_cnt = 0;
        audio_in_reg->audio_in_pdm_ch_spike.pdmin_ch0_spike_th = 0;
    }
    else if(44100 == pdm_rx_tx_sample_freq) //44.1K
    {
        audio_in_reg->audio_in_pdm_conf_1.ord_select = 0;
        audio_in_reg->audio_in_pdm_clk_spike.pdmin_clk_spike_cnt = 0;
        audio_in_reg->audio_in_pdm_clk_spike.pdmin_clk_spike_th = 0;

        audio_in_reg->audio_in_pdm_ch_spike.pdmin_ch0_spike_cnt = 0;
        audio_in_reg->audio_in_pdm_ch_spike.pdmin_ch0_spike_th = 0;
    }
    else
    {
        k510_logci("audio_pdm_in_init pdm_rx_tx_sample_freq error!\r\n");
        while(1);
    }

    audio_in_reg->audio_in_pdm_conf_0.hbf_enable = 1;
    audio_in_reg->audio_in_pdm_conf_0.mpf_enable = 1;
    audio_in_reg->audio_in_pdm_conf_0.pdm_in_endian = pdm_rx_align;
    audio_in_reg->audio_in_pdm_conf_0.pdm_fifo_clear = 0;
    audio_in_reg->audio_in_pdm_conf_0.pdm_dma_fifo_th = 1;

    audio_in_reg->audio_in_pdm_conf_0.pdm_enable = 1;
}

void audio_tdm_in_init(uint32_t tdm_io_num, uint32_t tdm_rx_num, audio_in_align_e tdm_rx_align)
{
    audio_in_reg->audio_in_tdm_ctl.tdm_enable                   = AUDIO_DISABLE;
    /*bypass agc*/
    audio_in_reg->audio_in_agc_para_4.agc_bypass                = AUDIO_ENABLE;

    audio_in_reg->audio_in_tdm_config.tdm_width_mode            = 1; /*24 bit*/
    audio_in_reg->audio_in_tdm_config.tdm_clk_dly               = 1; /* 麦克风在frame_sync下一拍出数据 */ //0
    audio_in_reg->audio_in_tdm_config.tdm_in_endian             = tdm_rx_align; /* left align */
    audio_in_reg->audio_in_tdm_config.tdm_dma_fifo_th           = 1;

    audio_in_reg->audio_in_tdm_channel_cfg0.io0_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io1_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io2_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io3_channel_num     = 0;

    audio_in_reg->audio_in_tdm_channel_cfg0.io4_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io5_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io6_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg0.io7_channel_num     = 0;

    audio_in_reg->audio_in_tdm_channel_cfg1.io8_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io9_channel_num     = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io10_channel_num    = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io11_channel_num    = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io12_channel_num    = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io13_channel_num    = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io14_channel_num    = 0;
    audio_in_reg->audio_in_tdm_channel_cfg1.io15_channel_num    = 0;

    audio_in_reg->audio_in_tdm_fsync_config.tdm_fsync_div_high  = 1;
    audio_in_reg->audio_in_tdm_ctl.tdm_intr                     = 0;

    if((tdm_io_num == 1) && (tdm_rx_num == 2))/*1 io 2 channel*/
    {
        audio_in_reg->audio_in_tdm_config.tdm_channel_mode          = 7; /*ionum l*/
        audio_in_reg->audio_in_tdm_channel_cfg0.io0_channel_num     = 2;
        audio_in_reg->audio_in_tdm_fsync_config.tdm_fsync_div_low   = 63;/* 2 channels 64bit*/
    }
    else if((tdm_io_num == 2) && (tdm_rx_num == 4)) /*2 io * 4 channel = 8 channel*/
    {
        audio_in_reg->audio_in_tdm_config.tdm_channel_mode          = 6; /*ionum 2*/
        audio_in_reg->audio_in_tdm_channel_cfg0.io0_channel_num     = 4;
        audio_in_reg->audio_in_tdm_channel_cfg0.io1_channel_num     = 4;
        audio_in_reg->audio_in_tdm_fsync_config.tdm_fsync_div_low   = 63+64;/* 4 channels 128 bit*/
    }
    else
    {
         k510_logci("please check io and ch config!\r\n");
         while(1);
    }

    audio_in_reg->audio_in_tdm_ctl.tdm_enable                   = AUDIO_ENABLE;
}

void audio_i2s_out_init(uint32_t word_len)
{
    audio_out_reg->audio_out_ctl.data_type              = (word_len == 24) ? AUDIO_OUT_TYPE_24BIT:AUDIO_OUT_TYPE_32BIT;
    audio_out_reg->audio_out_ctl.mode                   = AUDIO_OUT_MODE_I2S;      /* i2s/pdm/tdm mode */
    audio_out_reg->audio_out_ctl.enable                 = AUDIO_ENABLE;            /* enable audio out */
}

void audio_pdm_out_init(bool dma_enable,uint32_t ch_number,audio_out_pdm_edge_e edge, audio_sample_e sample)
{
    audio_out_reg->audio_out_ctl.enable             = AUDIO_DISABLE;                /* disable audio out */
    audio_out_reg->audio_out_ctl.data_type          = AUDIO_OUT_TYPE_24BIT;
    audio_out_reg->audio_out_ctl.loop_en            = AUDIO_DISABLE;                /* disable loopback */

    if(true == dma_enable)
    {
        k510_logci("pdm enable dma!\r\n");
        audio_out_reg->audio_out_ctl.dma_enable     = AUDIO_ENABLE;             /* enable dma */
    }
    else
    {
        k510_logci("pdm disable dma!\r\n");
        audio_out_reg->audio_out_ctl.dma_enable     = AUDIO_DISABLE;            /* disable dma */
    }
    audio_out_reg->audio_out_ctl.dma_threshold      = 1;
    audio_out_reg->audio_out_ctl.channel_num        = ch_number;                    /* channel */
    audio_out_reg->audio_out_ctl.mode               = AUDIO_OUT_MODE_PDM;       /* i2s/pdm/tdm mode */
    audio_out_reg->audio_out_ctl.fir2_out_bypass    = AUDIO_ENABLE;

    audio_out_reg->audio_out_fifo.ref_fifo_th = 0;
    audio_out_reg->audio_out_fifo.audio_fifo_clear = AUDIO_DISABLE;

    audio_out_reg->audio_out_pdm_conf.pcm_sync_en = 1;
    audio_out_reg->audio_out_pdm_conf.pdm_spike_th = 0x0;

    audio_out_reg->audio_out_filter.loop_fir_bypass = AUDIO_DISABLE;
    audio_out_reg->audio_out_filter.pdm_cic_filter_bypass = AUDIO_DISABLE;
    audio_out_reg->audio_out_filter.pdm_cic_mp_filter_bypass = AUDIO_DISABLE;
    audio_out_reg->audio_out_filter.pdm_hbf_filter_bypass = AUDIO_DISABLE;

    audio_out_reg->audio_out_pdm_conf.pdm_pn_sel        = edge;

    if(sample == AUDIO_SAMPLE_16K)
    {
        audio_out_reg->audio_out_pdm_conf.pdm_ord_sel   = AUDIO_PDM_OUT_CIC32;    /*cic 32 2.048MHz*/
    }
    else
    {
        audio_out_reg->audio_out_pdm_conf.pdm_ord_sel   = AUDIO_PDM_OUT_CIC16;    /*cic 16 2.8224MHz*/
    }
    /* enable pdm */

    audio_out_reg->pn_delay                             = 9;
    k510_logci("audio pdm out pn delay = %d\r\n",audio_out_reg->pn_delay);
    audio_out_reg->audio_out_ctl.enable                 = AUDIO_ENABLE;            /* enable audio out */
}

void audio_tdm_out_init(bool tx_dma_enable)
{
    //output
    audio_out_reg->audio_out_ctl.enable                         = AUDIO_DISABLE;                /* disable audio out */
    audio_out_reg->audio_out_ctl.align                          = 1;                            /* right align */
    audio_out_reg->audio_out_ctl.data_type                      = 0;                            /* 32 bit */
    audio_out_reg->audio_out_ctl.loop_en                        = AUDIO_DISABLE;                /* disable loopback */

    if(true == tx_dma_enable)
    {
        k510_logci("pcm enable dma!\r\n");
        audio_out_reg->audio_out_ctl.dma_enable                 = AUDIO_ENABLE;             /* enable dma */
    }
    else
    {
        k510_logci("pcm disable dma!\r\n");
        audio_out_reg->audio_out_ctl.dma_enable                 = AUDIO_DISABLE;            /* disable dma */
    }

    audio_out_reg->audio_out_ctl.dma_threshold                  = 1;
    audio_out_reg->audio_out_ctl.channel_num                    = 2;                        /* channel         2 */
    audio_out_reg->audio_out_ctl.mode                           = AUDIO_OUT_MODE_TDM;       /* i2s/pdm/tdm mode  */
    audio_out_reg->audio_out_ctl.fir2_out_bypass                = AUDIO_ENABLE;

    audio_out_reg->audio_out_fifo.ref_fifo_th                   = 0;
    audio_out_reg->audio_out_fifo.audio_fifo_clear              = AUDIO_DISABLE;

    audio_out_reg->audio_out_pdm_conf.pcm_sync_en               = 1;
    audio_out_reg->audio_out_pdm_conf.pdm_spike_th              = 0x0;

    audio_out_reg->audio_out_tdm_conf.frame_sync_total          = 64;    /* 64 cycles 2ch *32 bit = 64  64*/
    audio_out_reg->audio_out_tdm_conf.frame_sync_high           = 32;    /* frame sync 1 sclk           32*/

    audio_out_reg->audio_out_tdm_conf.frame_sclk_delay          = 0;    /* frame sync delay 1 sclk */

    audio_out_reg->audio_out_ctl.enable                         = AUDIO_ENABLE;            /* enable audio out */
}
