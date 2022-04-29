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
/******************************************************************************
  File Name     : vo_remap_reg.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _VO_REMAP_REG_H_
#define _VO_REMAP_REG_H_

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
//
#define  VO_REMAP_INFO_AREA_00_0_CTRL     (0x0000)
#define  VO_REMAP_INFO_AREA_00_1_CTRL     (0x0004)
#define  VO_REMAP_INFO_AREA_01_0_CTRL     (0x0008)
#define  VO_REMAP_INFO_AREA_01_1_CTRL     (0x000C)
#define  VO_REMAP_INFO_AREA_02_0_CTRL     (0x0010)
#define  VO_REMAP_INFO_AREA_02_1_CTRL     (0x0014)
#define  VO_REMAP_INFO_AREA_03_0_CTRL     (0x0018)
#define  VO_REMAP_INFO_AREA_03_1_CTRL     (0x001C)
#define  VO_REMAP_INFO_AREA_04_0_CTRL     (0x0020)
#define  VO_REMAP_INFO_AREA_04_1_CTRL     (0x0024)
#define  VO_REMAP_INFO_AREA_05_0_CTRL     (0x0028)
#define  VO_REMAP_INFO_AREA_05_1_CTRL     (0x002C)
#define  VO_REMAP_INFO_AREA_06_0_CTRL     (0x0030)
#define  VO_REMAP_INFO_AREA_06_1_CTRL     (0x0034)
#define  VO_REMAP_INFO_AREA_07_0_CTRL     (0x0038)
#define  VO_REMAP_INFO_AREA_07_1_CTRL     (0x003C)
#define  VO_REMAP_INFO_AREA_08_0_CTRL     (0x0040)
#define  VO_REMAP_INFO_AREA_08_1_CTRL     (0x0044)
#define  VO_REMAP_INFO_AREA_09_0_CTRL     (0x0048)
#define  VO_REMAP_INFO_AREA_09_1_CTRL     (0x004C)
#define  VO_REMAP_INFO_AREA_10_0_CTRL     (0x0050)
#define  VO_REMAP_INFO_AREA_10_1_CTRL     (0x0054)
#define  VO_REMAP_INFO_AREA_11_0_CTRL     (0x0058)
#define  VO_REMAP_INFO_AREA_11_1_CTRL     (0x005C)
#define  VO_REMAP_INFO_AREA_12_0_CTRL     (0x0060)
#define  VO_REMAP_INFO_AREA_12_1_CTRL     (0x0064)
#define  VO_REMAP_INFO_AREA_13_0_CTRL     (0x0068)
#define  VO_REMAP_INFO_AREA_13_1_CTRL     (0x006C)
#define  VO_REMAP_INFO_AREA_14_0_CTRL     (0x0070)
#define  VO_REMAP_INFO_AREA_14_1_CTRL     (0x0074)
#define  VO_REMAP_INFO_AREA_15_0_CTRL     (0x0078)
#define  VO_REMAP_INFO_AREA_15_1_CTRL     (0x007C)
#define  VO_REMAP_INFO_AREA_16_0_CTRL     (0x0080)
#define  VO_REMAP_INFO_AREA_16_1_CTRL     (0x0084)
#define  VO_REMAP_INFO_AREA_17_0_CTRL     (0x0088)
#define  VO_REMAP_INFO_AREA_17_1_CTRL     (0x008C)
#define  VO_REMAP_INFO_AREA_18_0_CTRL     (0x0090)
#define  VO_REMAP_INFO_AREA_18_1_CTRL     (0x0094)
#define  VO_REMAP_INFO_AREA_19_0_CTRL     (0x0098)
#define  VO_REMAP_INFO_AREA_19_1_CTRL     (0x009C)
#define  VO_REMAP_INFO_AREA_20_0_CTRL     (0x00A0)
#define  VO_REMAP_INFO_AREA_20_1_CTRL     (0x00A4)
#define  VO_REMAP_INFO_AREA_21_0_CTRL     (0x00A8)
#define  VO_REMAP_INFO_AREA_21_1_CTRL     (0x00AC)
#define  VO_REMAP_INFO_AREA_22_0_CTRL     (0x00B0)
#define  VO_REMAP_INFO_AREA_22_1_CTRL     (0x00B4)
#define  VO_REMAP_INFO_AREA_23_0_CTRL     (0x00B8)
#define  VO_REMAP_INFO_AREA_23_1_CTRL     (0x00BC)
#define  VO_REMAP_INFO_AREA_24_0_CTRL     (0x00C0)
#define  VO_REMAP_INFO_AREA_24_1_CTRL     (0x00C4)
#define  VO_REMAP_INFO_AREA_25_0_CTRL     (0x00C8)
#define  VO_REMAP_INFO_AREA_25_1_CTRL     (0x00CC)
#define  VO_REMAP_INFO_AREA_26_0_CTRL     (0x00D0)
#define  VO_REMAP_INFO_AREA_26_1_CTRL     (0x00D4)
#define  VO_REMAP_INFO_AREA_27_0_CTRL     (0x00D8)
#define  VO_REMAP_INFO_AREA_27_1_CTRL     (0x00DC)
#define  VO_REMAP_INFO_AREA_28_0_CTRL     (0x00E0)
#define  VO_REMAP_INFO_AREA_28_1_CTRL     (0x00E4)
#define  VO_REMAP_INFO_AREA_29_0_CTRL     (0x00E8)
#define  VO_REMAP_INFO_AREA_29_1_CTRL     (0x00EC) 
#define  VO_REMAP_INFO_AREA_30_0_CTRL     (0x00F0)
#define  VO_REMAP_INFO_AREA_30_1_CTRL     (0x00F4)
#define  VO_REMAP_INFO_AREA_31_0_CTRL     (0x00F8)
#define  VO_REMAP_INFO_AREA_31_1_CTRL     (0x00FC)

#define  VO_REMAP_DATA_AREA_00_0_CTRL     (0x0100) 
#define  VO_REMAP_DATA_AREA_01_0_CTRL     (0x0104) 
#define  VO_REMAP_DATA_AREA_02_0_CTRL     (0x0108) 
#define  VO_REMAP_DATA_AREA_03_0_CTRL     (0x010C) 
#define  VO_REMAP_DATA_AREA_04_0_CTRL     (0x0110) 
#define  VO_REMAP_DATA_AREA_05_0_CTRL     (0x0114) 
#define  VO_REMAP_DATA_AREA_06_0_CTRL     (0x0118) 
#define  VO_REMAP_DATA_AREA_07_0_CTRL     (0x011C) 
#define  VO_REMAP_DATA_AREA_08_0_CTRL     (0x0120) 
#define  VO_REMAP_DATA_AREA_09_0_CTRL     (0x0124) 
#define  VO_REMAP_DATA_AREA_10_0_CTRL     (0x0128) 
#define  VO_REMAP_DATA_AREA_11_0_CTRL     (0x012C) 
#define  VO_REMAP_DATA_AREA_12_0_CTRL     (0x0130) 
#define  VO_REMAP_DATA_AREA_13_0_CTRL     (0x0134) 
#define  VO_REMAP_DATA_AREA_14_0_CTRL     (0x0138) 
#define  VO_REMAP_DATA_AREA_15_0_CTRL     (0x013C) 
#define  VO_REMAP_DATA_AREA_16_0_CTRL     (0x0140) 
#define  VO_REMAP_DATA_AREA_17_0_CTRL     (0x0144) 
#define  VO_REMAP_DATA_AREA_18_0_CTRL     (0x0148) 
#define  VO_REMAP_DATA_AREA_19_0_CTRL     (0x014C)
#define  VO_REMAP_DATA_AREA_20_0_CTRL     (0x0150) 
#define  VO_REMAP_DATA_AREA_21_0_CTRL     (0x0154) 
#define  VO_REMAP_DATA_AREA_22_0_CTRL     (0x0158) 
#define  VO_REMAP_DATA_AREA_23_0_CTRL     (0x015C) 
#define  VO_REMAP_DATA_AREA_24_0_CTRL     (0x0160) 
#define  VO_REMAP_DATA_AREA_25_0_CTRL     (0x0164) 
#define  VO_REMAP_DATA_AREA_26_0_CTRL     (0x0168) 
#define  VO_REMAP_DATA_AREA_27_0_CTRL     (0x016C) 
#define  VO_REMAP_DATA_AREA_28_0_CTRL     (0x0170) 
#define  VO_REMAP_DATA_AREA_29_0_CTRL     (0x0174)    
#define  VO_REMAP_DATA_AREA_30_0_CTRL     (0x0178) 
#define  VO_REMAP_DATA_AREA_31_0_CTRL     (0x017C)
#define  VO_REMAP_FILL_CMD_CTRL           (0x0180)  
#endif /*_VO_REMAP_REG_H_*/