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

#ifndef _ISP_REMAP_REG_DEF_H_
#define _ISP_REMAP_REG_DEF_H_
/*
*CONTROL INFORMATION
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_end_pos_x                : 13  ; /* [12..0 ]  */
        unsigned int    line_draw_en                  : 1   ; /* [13]  */
        unsigned int    v_line_r_en                   : 1  ; /* [14]  */
        unsigned int    v_line_l_en                   : 1   ; /* [15]  */
        unsigned int    line_start_pos_x              : 13  ; /* [28..16 ]  */
        unsigned int    h_line_b_en                   : 1  ; /* [29 ]  */ 
        unsigned int    h_line_u_en                   : 1  ; /* [30 ]  */
        unsigned int    reserved0                     : 1  ; /* [31 ]  */   
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FILL_INFO_AREA_0_CTRL;


typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    line_end_pos_y                 : 13  ; /* [12..0 ]  */
        unsigned int    line_width_l                   : 3   ; /* [15..13]  */
        unsigned int    line_start_pos_y               : 13  ; /* [28..16]  */
        unsigned int    line_width_h                   : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FILL_INFO_AREA_1_CTRL;

/*
*DATA(ALPHA&YCBCR) 
*/

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fill_value_cr                   : 8  ; /* [7..0 ]  */
        unsigned int    fill_value_cb                   : 8   ; /* [15..8]  */
        unsigned int    fill_value_y                    : 8  ; /* [23..16]  */
        unsigned int    Fill_alpha                      : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FILL_DATA_AREA_0_CTRL;

typedef struct
{
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_00_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_00_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_01_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_01_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_02_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_02_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_03_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_03_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_04_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_04_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_05_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_05_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_06_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_06_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_07_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_07_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_08_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_08_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_09_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_09_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_10_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_10_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_11_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_11_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_12_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_12_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_13_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_13_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_14_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_14_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_15_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_15_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_16_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_16_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_17_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_17_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_18_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_18_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_19_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_19_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_20_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_20_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_21_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_21_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_22_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_22_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_23_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_23_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_24_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_24_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_25_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_25_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_26_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_26_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_27_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_27_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_28_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_28_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_29_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_29_1_CTRL; 
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_30_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_30_1_CTRL;
    volatile U_ISP_FILL_INFO_AREA_0_CTRL            ISP_FILL_INFO_AREA_31_0_CTRL;
    volatile U_ISP_FILL_INFO_AREA_1_CTRL            ISP_FILL_INFO_AREA_31_1_CTRL;
    //
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_00_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_01_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_02_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_03_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_04_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_05_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_06_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_07_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_08_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_09_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_10_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_11_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_12_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_13_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_14_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_15_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_16_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_17_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_18_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_19_0_CTRL;
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_20_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_21_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_22_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_23_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_24_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_25_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_26_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_27_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_28_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_29_0_CTRL;    
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_30_0_CTRL; 
    volatile U_ISP_FILL_DATA_AREA_0_CTRL            ISP_FILL_DATA_AREA_31_0_CTRL; 
} S_ISP_REMAP_REGS_TYPE;

int ISP_REMAP_DRV_SET_FillInfo_0_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_0_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillInfo_1_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
int ISP_REMAP_DRV_SET_FillData_0_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);
//debug
int ISP_REMAP_DRV_GET_RemapRegsVal(S_ISP_REMAP_REGS_TYPE *pstRegs);
#endif /* _ISP_REMAP_REG_DEF_H_*/