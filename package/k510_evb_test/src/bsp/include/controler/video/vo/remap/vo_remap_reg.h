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

#ifndef _VO_REMAP_REG_DEF_H_
#define _VO_REMAP_REG_DEF_H_

typedef union { /* ctrl_fill_info_area_0_0 */

    struct 
    {
        unsigned int line_end_pos_x                    : 13;
        unsigned int line_draw_en                      : 1;
        unsigned int v_line_r_en                       : 1;
        unsigned int v_line_l_en                       : 1;
        unsigned int line_start_pos_x                  : 13;
        unsigned int h_line_b_en                       : 1;
        unsigned int v_line_u_en                       : 1;
        unsigned int reserved0                         : 1;
    } bits;    
    unsigned int u32; 
} U_VO_REMAP_CTRL_FILL_INFO_AREA_0;

typedef union { /* ctrl_fill_info_area_0_1 */

    struct 
    {
        unsigned int line_end_pos_y                    : 13;
        unsigned int line_width_l                      : 3;
        unsigned int line_start_pos_y                  : 13;
        unsigned int line_width_h                      : 3;
    } bits;    
    unsigned int u32; 
} U_VO_REMAP_CTRL_FILL_INFO_AREA_1;

typedef union { /* ctrl_fill_data_area_0_0 */

    struct 
    {
        unsigned int fill_value_cr                     : 8;
        unsigned int fill_value_cb                     : 8;
        unsigned int fill_value_y                      : 8;
        unsigned int fill_alpha                        : 8;
    } bits;    
    unsigned int u32; 
} U_VO_REMAP_CTRL_FILL_DATA_AREA_0;

typedef union { /* ctrl_fill_cmd */

    struct 
    {
        unsigned int image_active_h                     : 13;
        unsigned int reserved0                          : 2;
        unsigned int fill_en_rgb                        : 1;
        unsigned int image_active_v                     : 13;
        unsigned int reserved1                          : 2;
        unsigned int fill_fill_en_yuv                   : 1;
    } bits;    
    unsigned int u32; 
} U_VO_REMAP_CTRL_FILL_CMD;

typedef struct 
{
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_00_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_00_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_01_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_01_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_02_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_02_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_03_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_03_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_04_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_04_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_05_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_05_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_06_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_06_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_07_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_07_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_08_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_08_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_09_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_09_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_10_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_10_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_11_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_11_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_12_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_12_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_13_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_13_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_14_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_14_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_15_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_15_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_16_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_16_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_17_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_17_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_18_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_18_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_19_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_19_1;
	volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_20_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_20_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_21_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_21_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_22_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_22_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_23_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_23_1; 
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_24_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_24_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_25_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_25_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_26_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_26_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_27_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_27_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_28_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_28_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_29_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_29_1;
	volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_30_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_30_1;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_0           CTRL_FILL_INFO_AREA_31_0;
    volatile U_VO_REMAP_CTRL_FILL_INFO_AREA_1           CTRL_FILL_INFO_AREA_31_1;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_00_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_01_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_02_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_03_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_04_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_05_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_06_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_07_0;	
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_08_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_09_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_10_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_11_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_12_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_13_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_14_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_15_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_16_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_17_0;	
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_18_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_19_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_20_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_21_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_22_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_23_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_24_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_25_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_26_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_27_0;	
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_28_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_29_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_30_0;
    volatile U_VO_REMAP_CTRL_FILL_DATA_AREA_0           CTRL_FILL_DATA_AREA_31_0;
    volatile U_VO_REMAP_CTRL_FILL_CMD                   CTRL_FILL_CMD;
}S_VO_REMAP_REGS_TYPE;

int VO_REMAP_DRV_SET_CtrlFillInfoArea00_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea00_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea00_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea01_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea01_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea01_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea02_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea02_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea02_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea03_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea03_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea03_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea04_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea04_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea04_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea05_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea05_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea05_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea06_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea06_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea06_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea07_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea07_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea07_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea08_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea08_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea08_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea09_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea09_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea09_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea10_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea10_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea10_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea11_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea11_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea11_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea12_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea12_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea12_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea13_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea13_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea13_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea14_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea14_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea14_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea15_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea15_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea15_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea16_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea16_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea16_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea17_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea17_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea17_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea18_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea18_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea18_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea19_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea19_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea19_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea20_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea20_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea20_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea21_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea21_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea21_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea22_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea22_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea22_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea23_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea23_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea23_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea24_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea24_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea24_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea25_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea25_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea25_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea26_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea26_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea26_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea27_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea27_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea27_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea28_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea28_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea28_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea29_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea29_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea29_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea30_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea30_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea30_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea31_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillInfoArea31_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillDataArea31_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
int VO_REMAP_DRV_SET_CtrlFillCmd(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData);
//debug
int VO_REMAP_DRV_GET_RemapRegsVal(S_VO_REMAP_REGS_TYPE *pstRegs);
#endif /*_VO_REMAP_REG_DEF_H_*/