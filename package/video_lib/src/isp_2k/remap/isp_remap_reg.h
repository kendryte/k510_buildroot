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

/*
 * isp_remap_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _ISP_REMAP_REG_H_
#define _ISP_REMAP_REG_H_
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

//#define  ISP_F_2K_REMAP_BASE			  (ISP_F_2K_BASE_ADDR + 0x6000) 
//#define  ISP_F_2K_OUT0_REMAP_BASE		  (ISP_F_2K_BASE_ADDR + 0x6000) 
//#define  ISP_F_2K_OUT1_REMAP_BASE		  (ISP_F_2K_BASE_ADDR + 0x6200) 
//#define  ISP_F_2K_MAIN_REMAP_BASE		  (ISP_F_2K_BASE_ADDR + 0x6400) 
//#define  ISP_R_2K_REMAP_BASE			  (ISP_R_2K_BASE_ADDR + 0x6000)
//#define  ISP_R_2K_OUT0_REMAP_BASE		  (ISP_R_2K_BASE_ADDR + 0x6000) 
//#define  ISP_R_2K_OUT1_REMAP_BASE		  (ISP_R_2K_BASE_ADDR + 0x6200)
//#define  ISP_R_2K_MAIN_REMAP_BASE		  (ISP_R_2K_BASE_ADDR + 0x6400) 
//
#define  ISP_FILL_INFO_AREA_00_0_CTRL     (0x0000)
#define  ISP_FILL_INFO_AREA_00_1_CTRL     (0x0004)
#define  ISP_FILL_INFO_AREA_01_0_CTRL     (0x0008)
#define  ISP_FILL_INFO_AREA_01_1_CTRL     (0x000C)
#define  ISP_FILL_INFO_AREA_02_0_CTRL     (0x0010)
#define  ISP_FILL_INFO_AREA_02_1_CTRL     (0x0014)
#define  ISP_FILL_INFO_AREA_03_0_CTRL     (0x0018)
#define  ISP_FILL_INFO_AREA_03_1_CTRL     (0x001C)
#define  ISP_FILL_INFO_AREA_04_0_CTRL     (0x0020)
#define  ISP_FILL_INFO_AREA_04_1_CTRL     (0x0024)
#define  ISP_FILL_INFO_AREA_05_0_CTRL     (0x0028)
#define  ISP_FILL_INFO_AREA_05_1_CTRL     (0x002C)
#define  ISP_FILL_INFO_AREA_06_0_CTRL     (0x0030)
#define  ISP_FILL_INFO_AREA_06_1_CTRL     (0x0034)
#define  ISP_FILL_INFO_AREA_07_0_CTRL     (0x0038)
#define  ISP_FILL_INFO_AREA_07_1_CTRL     (0x003C)
#define  ISP_FILL_INFO_AREA_08_0_CTRL     (0x0040)
#define  ISP_FILL_INFO_AREA_08_1_CTRL     (0x0044)
#define  ISP_FILL_INFO_AREA_09_0_CTRL     (0x0048)
#define  ISP_FILL_INFO_AREA_09_1_CTRL     (0x004C)
#define  ISP_FILL_INFO_AREA_10_0_CTRL     (0x0050)
#define  ISP_FILL_INFO_AREA_10_1_CTRL     (0x0054)
#define  ISP_FILL_INFO_AREA_11_0_CTRL     (0x0058)
#define  ISP_FILL_INFO_AREA_11_1_CTRL     (0x005C)
#define  ISP_FILL_INFO_AREA_12_0_CTRL     (0x0060)
#define  ISP_FILL_INFO_AREA_12_1_CTRL     (0x0064)
#define  ISP_FILL_INFO_AREA_13_0_CTRL     (0x0068)
#define  ISP_FILL_INFO_AREA_13_1_CTRL     (0x006C)
#define  ISP_FILL_INFO_AREA_14_0_CTRL     (0x0070)
#define  ISP_FILL_INFO_AREA_14_1_CTRL     (0x0074)
#define  ISP_FILL_INFO_AREA_15_0_CTRL     (0x0078)
#define  ISP_FILL_INFO_AREA_15_1_CTRL     (0x007C)
#define  ISP_FILL_INFO_AREA_16_0_CTRL     (0x0080)
#define  ISP_FILL_INFO_AREA_16_1_CTRL     (0x0084)
#define  ISP_FILL_INFO_AREA_17_0_CTRL     (0x0088)
#define  ISP_FILL_INFO_AREA_17_1_CTRL     (0x008C)
#define  ISP_FILL_INFO_AREA_18_0_CTRL     (0x0090)
#define  ISP_FILL_INFO_AREA_18_1_CTRL     (0x0094)
#define  ISP_FILL_INFO_AREA_19_0_CTRL     (0x0098)
#define  ISP_FILL_INFO_AREA_19_1_CTRL     (0x009C)
#define  ISP_FILL_INFO_AREA_20_0_CTRL     (0x00A0)
#define  ISP_FILL_INFO_AREA_20_1_CTRL     (0x00A4)
#define  ISP_FILL_INFO_AREA_21_0_CTRL     (0x00A8)
#define  ISP_FILL_INFO_AREA_21_1_CTRL     (0x00AC)
#define  ISP_FILL_INFO_AREA_22_0_CTRL     (0x00B0)
#define  ISP_FILL_INFO_AREA_22_1_CTRL     (0x00B4)
#define  ISP_FILL_INFO_AREA_23_0_CTRL     (0x00B8)
#define  ISP_FILL_INFO_AREA_23_1_CTRL     (0x00BC)
#define  ISP_FILL_INFO_AREA_24_0_CTRL     (0x00C0)
#define  ISP_FILL_INFO_AREA_24_1_CTRL     (0x00C4)
#define  ISP_FILL_INFO_AREA_25_0_CTRL     (0x00C8)
#define  ISP_FILL_INFO_AREA_25_1_CTRL     (0x00CC)
#define  ISP_FILL_INFO_AREA_26_0_CTRL     (0x00D0)
#define  ISP_FILL_INFO_AREA_26_1_CTRL     (0x00D4)
#define  ISP_FILL_INFO_AREA_27_0_CTRL     (0x00D8)
#define  ISP_FILL_INFO_AREA_27_1_CTRL     (0x00DC)
#define  ISP_FILL_INFO_AREA_28_0_CTRL     (0x00E0)
#define  ISP_FILL_INFO_AREA_28_1_CTRL     (0x00E4)
#define  ISP_FILL_INFO_AREA_29_0_CTRL     (0x00E8)
#define  ISP_FILL_INFO_AREA_29_1_CTRL     (0x00EC) 
#define  ISP_FILL_INFO_AREA_30_0_CTRL     (0x00F0)
#define  ISP_FILL_INFO_AREA_30_1_CTRL     (0x00F4)
#define  ISP_FILL_INFO_AREA_31_0_CTRL     (0x00F8)
#define  ISP_FILL_INFO_AREA_31_1_CTRL     (0x00FC)

#define  ISP_FILL_DATA_AREA_00_0_CTRL     (0x0100) 
#define  ISP_FILL_DATA_AREA_01_0_CTRL     (0x0104) 
#define  ISP_FILL_DATA_AREA_02_0_CTRL     (0x0108) 
#define  ISP_FILL_DATA_AREA_03_0_CTRL     (0x010C) 
#define  ISP_FILL_DATA_AREA_04_0_CTRL     (0x0110) 
#define  ISP_FILL_DATA_AREA_05_0_CTRL     (0x0114) 
#define  ISP_FILL_DATA_AREA_06_0_CTRL     (0x0118) 
#define  ISP_FILL_DATA_AREA_07_0_CTRL     (0x011C) 
#define  ISP_FILL_DATA_AREA_08_0_CTRL     (0x0120) 
#define  ISP_FILL_DATA_AREA_09_0_CTRL     (0x0124) 
#define  ISP_FILL_DATA_AREA_10_0_CTRL     (0x0128) 
#define  ISP_FILL_DATA_AREA_11_0_CTRL     (0x012C) 
#define  ISP_FILL_DATA_AREA_12_0_CTRL     (0x0130) 
#define  ISP_FILL_DATA_AREA_13_0_CTRL     (0x0134) 
#define  ISP_FILL_DATA_AREA_14_0_CTRL     (0x0138) 
#define  ISP_FILL_DATA_AREA_15_0_CTRL     (0x013C) 
#define  ISP_FILL_DATA_AREA_16_0_CTRL     (0x0140) 
#define  ISP_FILL_DATA_AREA_17_0_CTRL     (0x0144) 
#define  ISP_FILL_DATA_AREA_18_0_CTRL     (0x0148) 
#define  ISP_FILL_DATA_AREA_19_0_CTRL     (0x014C)
#define  ISP_FILL_DATA_AREA_20_0_CTRL     (0x0150) 
#define  ISP_FILL_DATA_AREA_21_0_CTRL     (0x0154) 
#define  ISP_FILL_DATA_AREA_22_0_CTRL     (0x0158) 
#define  ISP_FILL_DATA_AREA_23_0_CTRL     (0x015C) 
#define  ISP_FILL_DATA_AREA_24_0_CTRL     (0x0160) 
#define  ISP_FILL_DATA_AREA_25_0_CTRL     (0x0164) 
#define  ISP_FILL_DATA_AREA_26_0_CTRL     (0x0168) 
#define  ISP_FILL_DATA_AREA_27_0_CTRL     (0x016C) 
#define  ISP_FILL_DATA_AREA_28_0_CTRL     (0x0170) 
#define  ISP_FILL_DATA_AREA_29_0_CTRL     (0x0174)    
#define  ISP_FILL_DATA_AREA_30_0_CTRL     (0x0178) 
#define  ISP_FILL_DATA_AREA_31_0_CTRL     (0x017C) 

#endif /* _ISP_REMAP_REG_H_*/