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
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "vad.h"
#include "io.h"
#include "platform.h"
#include "dmac.h"
//#include "sysctl.h"
//#include "stdlib.h"
//#include "utils.h"

char data_string2[50];
volatile vad_t *const vad = (volatile vad_t *)VAD_BASE_ADDR;
volatile uint32_t *const dma_rx = (volatile uint32_t *)(VAD_BASE_ADDR + 0x14);

void vad_set_control(vad_control_reg_t control)
{
    vad->control_reg = control;
}

vad_control_reg_t vad_get_control(void)
{
    return vad->control_reg;
}

void vad_cfg_init(void)
{
    vad_control_reg_t control_reg_temp;

    control_reg_temp.vad_enable = 1;
    control_reg_temp.pdm_sel = 1;
    control_reg_temp.vad_intr_clr = 0;
    control_reg_temp.vad_out_stop = 0;
    control_reg_temp.vad_clk_dly = 0;

    control_reg_temp.pcm_mode = 0;
    control_reg_temp.i2s_chnl = 0;
    control_reg_temp.resv1 = 0;
    control_reg_temp.resv2 = 0;
    vad->control_reg = control_reg_temp;
}
/*
 * enable_flag: 1:enable, 0:disable
 */
void vad_enable(uint8_t enable_flag)
{
    control_reg_t u_control_reg;
    u_control_reg.reg_data = readl(&vad->control_reg);
    u_control_reg.control_reg.vad_enable = enable_flag;
    writel(u_control_reg.reg_data, &vad->control_reg);
    readl(&vad->control_reg);
}
/*
 * choose pdm or pcm 0:for pcm 1: for pdm
 */
void vad_select_source(uint8_t source)
{
    control_reg_t u_control_reg;

    u_control_reg.reg_data = readl(&vad->control_reg);
    u_control_reg.control_reg.pdm_sel = source;
    writel(u_control_reg.reg_data, &vad->control_reg);
    readl(&vad->control_reg);
}

/*
 * clear vad interrupt
 */
void vad_clear_intr(void)
{
    vad_control_reg_t control_reg_temp;
    control_reg_temp = vad->control_reg;
    control_reg_temp.vad_intr_clr = 1;
    vad->control_reg = control_reg_temp;
}

/*
 * stop vad out data
 */
void vad_stop_out_data(uint8_t flag)
{
    control_reg_t u_control_reg;

    u_control_reg.reg_data = readl(&vad->control_reg);
    u_control_reg.control_reg.vad_out_stop = flag;
    writel(u_control_reg.reg_data, &vad->control_reg);
}

/*
 * select pcm input data delay one clock
 */
void vad_pcm_delay_clock(uint8_t clock)
{
    control_reg_t u_control_reg;

    u_control_reg.reg_data = readl(&vad->control_reg);
    u_control_reg.control_reg.vad_clk_dly = clock;
    writel(u_control_reg.reg_data, &vad->control_reg);
}

/*
 * set parameter cfg 0
 */
void vad_set_parameter0(uint16_t win)
{
    parameter_cfg_0_t u_parameter_cfg_0;

    u_parameter_cfg_0.reg_data = readl(&vad->parameter_cfg_0);
    u_parameter_cfg_0.parameter_cfg_0.vf_win = win;
    writel(u_parameter_cfg_0.reg_data, &vad->parameter_cfg_0);
}

/*
 * set parameter cfg 1
 */
void vad_set_parameter1(uint8_t beta, uint8_t beta2, uint8_t rou, uint8_t alpha, uint8_t rethdabs)
{
    parameter_cfg_1_t u_parameter_cfg_1;

    u_parameter_cfg_1.reg_data = readl(&vad->parameter_cfg_1);
    u_parameter_cfg_1.parameter_cfg_1.vf_beta = beta;
    u_parameter_cfg_1.parameter_cfg_1.vf_beta2 = beta2;
    u_parameter_cfg_1.parameter_cfg_1.vf_rou = rou;
    u_parameter_cfg_1.parameter_cfg_1.vf_alpha = alpha;
    u_parameter_cfg_1.parameter_cfg_1.vf_rethdabs = rethdabs;
    // u_parameter_cfg_1.parameter_cfg_1.merge_fifo_th = merge_fifo_th;
    writel(u_parameter_cfg_1.reg_data, &vad->parameter_cfg_1);
}

/*
 * set parameter cfg 2
 */
void vad_set_parameter2(uint16_t pcm_fsync_high, uint16_t pcm_fsync_low)
{
    parameter_cfg_2_t u_parameter_cfg_2;

    u_parameter_cfg_2.reg_data = readl(&vad->parameter_cfg_2);
    u_parameter_cfg_2.parameter_cfg_2.pcm_fsync_high = pcm_fsync_high;
    u_parameter_cfg_2.parameter_cfg_2.pcm_fsync_low = pcm_fsync_low;
    writel(u_parameter_cfg_2.reg_data, &vad->parameter_cfg_2);
}

/*
 * set parameter cfg 3
 */
void vad_set_parameter3(uint16_t trgkeep)
{
    parameter_cfg_3_t u_parameter_cfg_3;

    u_parameter_cfg_3.reg_data = readl(&vad->parameter_cfg_3);
    u_parameter_cfg_3.parameter_cfg_3.vf_trgkeep = trgkeep;
    writel(u_parameter_cfg_3.reg_data, &vad->parameter_cfg_3);
}

/*
 * set parameter cfg 4
 */
void vad_set_parameter4(uint32_t thabs)
{
    parameter_cfg_4_t u_parameter_cfg_4;

    u_parameter_cfg_4.reg_data = readl(&vad->parameter_cfg_4);
    u_parameter_cfg_4.parameter_cfg_4.vf_thabs = thabs;
    writel(u_parameter_cfg_4.reg_data, &vad->parameter_cfg_4);
}

/*
 * get data
 */
uint32_t vad_get_data(void)
{
    data_out_reg_t u_data_out_reg;

    u_data_out_reg.reg_data = readl(&vad->data_out_reg);
    return u_data_out_reg.data_out_reg.vad2apb_data;
}

int peri_dma_vad_rx_test(uint32_t *rx_buff,uint32_t sum)
{
    peri_dma_cfg_t peri_tx_cfg = {
        .channel = DMA_CHANNEL_0,
        .dev_sel = VAD_RX,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = FIXED_REG_ADDRESS,
        .buswidth = FOUR_BYTE,
        .dev_burst_len = 0,
        .line_size = 4*sum,
        .saddr = (void*)dma_rx,
        .daddr = (void*)rx_buff,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&peri_tx_cfg);
    peri_dma_start(DMA_CHANNEL_0);
    peri_dma_wait_done_or_timeout(DMA_CHANNEL_0);
    return 0;
}