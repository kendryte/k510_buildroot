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
#ifndef _DRIVER_TDM_H
#define _DRIVER_TDM_H

#include <stdint.h>
#include <stddef.h>
// #include "platform.h"
// #include "io.h"
// #include "dmac.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _vad_control_reg
{
    uint32_t vad_enable: 1; /*vad module enable*/
    uint32_t pdm_sel: 1; /*choose pdm or pcm 0:for pcm 1: for pdm*/
    uint32_t vad_intr_clr: 1; /*clear vad interrupt */
    uint32_t vad_out_stop: 1; /*stop vad out data*/
    uint32_t vad_clk_dly: 1;/*select pcm input data delay one clock*/
    uint32_t resv1 : 3; /*Reserved bit, return 0s when read.*/
    uint32_t pcm_mode : 2; /*2'b00: tdm
                            2'b01: I2S philips standard mode
                            2'b10: I2S left justified mode
                            2'b11: I2S right justified mode*/
    uint32_t i2s_chnl : 1; /*1'b0: data in left channel
                             1'b1: data in right channel*/
    uint32_t resv2 : 21; /*Reserved bit, return 0s when read.*/

} __attribute__((packed, aligned(4))) vad_control_reg_t;

typedef union
{
    vad_control_reg_t control_reg;
    uint32_t reg_data;
}  __attribute__((packed, aligned(4))) control_reg_t;


typedef struct _vad_parameter_cfg_0
{
    uint32_t vf_win : 16;/*vf_win*/
    uint32_t resv : 16; /**/
} __attribute__((packed, aligned(4))) vad_parameter_cfg_0_t;

typedef union
{
    vad_parameter_cfg_0_t parameter_cfg_0;
    uint32_t reg_data;
} parameter_cfg_0_t;


typedef struct _vad_parameter_cfg_1
{
    uint32_t vf_beta : 5;/**/
    uint32_t vf_beta2 : 5;/**/
    uint32_t vf_rou : 3;/**/
    uint32_t vf_alpha : 2;/**/
    uint32_t vf_rethdabs : 3;/**/
    uint32_t merge_fifo_th : 4;/**/
    uint32_t resv : 10; /**/
} __attribute__((packed, aligned(4))) vad_parameter_cfg_1_t;

typedef union
{
    vad_parameter_cfg_1_t parameter_cfg_1;
    uint32_t reg_data;
} parameter_cfg_1_t;


typedef struct _vad_parameter_cfg_2
{
    uint32_t pcm_fsync_high : 10;//
    uint32_t pcm_fsync_low : 10;
    uint32_t resv : 12; /**/
} __attribute__((packed, aligned(4))) vad_parameter_cfg_2_t;

typedef union
{
    vad_parameter_cfg_2_t parameter_cfg_2;
    uint32_t reg_data;
} parameter_cfg_2_t;

typedef struct _vad_parameter_cfg_3
{
    uint32_t vf_trgkeep : 16;//
    uint32_t resv : 16; /**/
} __attribute__((packed, aligned(4))) vad_parameter_cfg_3_t;

typedef union
{
    vad_parameter_cfg_3_t parameter_cfg_3;
    uint32_t reg_data;
} parameter_cfg_3_t;


typedef struct _vad_data_out_reg
{
    uint32_t vad2apb_data : 32;//
} __attribute__((packed, aligned(4))) vad_data_out_reg_t;

typedef union
{
    vad_data_out_reg_t data_out_reg;
    uint32_t reg_data;
} __attribute__((packed, aligned(4))) data_out_reg_t;


typedef struct _vad_parameter_cfg_4
{
    uint32_t vf_thabs;//
} __attribute__((packed, aligned(4))) vad_parameter_cfg_4_t;

typedef union
{
    vad_parameter_cfg_4_t parameter_cfg_4;
    uint32_t reg_data;
} parameter_cfg_4_t;


typedef struct
{
    volatile vad_control_reg_t control_reg;     /* 0x00 */
    volatile uint32_t parameter_cfg_0;          /* 0x04 */
    volatile uint32_t parameter_cfg_1;          /* 0x08 */
    volatile uint32_t parameter_cfg_2;          /* 0x0c */
    volatile uint32_t parameter_cfg_3;          /* 0x10 */
    volatile uint32_t raw_data_out;             /* 0x14 */
    volatile uint32_t resv2;                    /* 0x18 */
    volatile uint32_t parameter_cfg_4;          /* 0x1c */
    volatile uint32_t resv3[45];                /* 0x20 - 0xD0 */
    volatile uint32_t data_out_reg;             /* 0xD4 */
    volatile uint32_t pdm_data_bit_scale;       /* 0xD8 */
    volatile uint32_t buf_ovrflw;               /* 0xDC */
}vad_t;

extern volatile vad_t *const vad;

#define vad_set_param0(win_cnt)             do{vad->parameter_cfg_0 = win_cnt;}while(0);
#define vad_set_param1(beta, beta2, rou, alpha, rethdabs)   do{vad->parameter_cfg_1 = beta << 0 | beta2 << 5 | \
                                                               rou << 10 | alpha << 13 | rethdabs << 15;}while(0);
#define vad_set_param2(fsync_low, fsync_high)   do{vad->parameter_cfg_2 = fsync_low << 0 | fsync_high << 10;}while(0);
#define vad_set_param3(trgkeep_cnt)         do{vad->parameter_cfg_3 = trgkeep_cnt;}while(0);

#define vad_int_clear()     do{writel(readl(&vad->control_reg) | 1 << 2, &vad->control_reg);}while(1);

void vad_cfg_init(void);

/*
 * enable_flag: 1:enable, 0:disable
 */
void vad_enable(uint8_t enable_flag);
/*
 * choose pdm or pcm 0:for pcm 1: for pdm
 */
void vad_select_source(uint8_t source);

/*
 * clear vad interrupt
 */
void vad_clear_intr(void);

/*
 * stop vad out data
 */
void vad_stop_out_data(uint8_t flag);

/*
 * select pcm input data delay one clock
 */
void vad_pcm_delay_clock(uint8_t clock);

/*
 * set parameter cfg 0
 */
void vad_set_parameter0(uint16_t win);

/*
 * set parameter cfg 1
 */
void vad_set_parameter1(uint8_t beta, uint8_t beta2, uint8_t rou, uint8_t alpha, uint8_t rethdabs);


/*
 * set parameter cfg 2
 */
void vad_set_parameter2(uint16_t pcm_fsync_high, uint16_t pcm_fsync_low);

/*
 * set parameter cfg 3
 */
void vad_set_parameter3(uint16_t trgkeep);

/*
 * set parameter cfg 4
 */
void vad_set_parameter4(uint32_t thabs);

/*
 * get data
 */
uint32_t vad_get_data(void);

int peri_dma_vad_rx_test(uint32_t *rx_buff,uint32_t sum);

void vad_set_control(vad_control_reg_t control);

vad_control_reg_t vad_get_control(void);

#ifdef __cplusplus
}
#endif

#endif
