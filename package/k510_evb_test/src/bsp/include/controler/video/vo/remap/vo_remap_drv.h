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

#ifndef _VO_REMAP_DRV_DEF_H_
#define _VO_REMAP_DRV_DEF_H_

#include "video/vo/remap/vo_remap_reg.h"


typedef enum 
{
    VO_LINE_DRAW_AREA_0              = 0,
    VO_LINE_DRAW_AREA_1              = 1,
    VO_LINE_DRAW_AREA_2              = 2,
    VO_LINE_DRAW_AREA_3              = 3,
    VO_LINE_DRAW_AREA_4              = 4,
    VO_LINE_DRAW_AREA_5              = 5,
    VO_LINE_DRAW_AREA_6              = 6,
    VO_LINE_DRAW_AREA_7              = 7,
    VO_LINE_DRAW_AREA_8              = 8,
    VO_LINE_DRAW_AREA_9              = 9,
    VO_LINE_DRAW_AREA_10             = 10,
    VO_LINE_DRAW_AREA_11             = 11,
    VO_LINE_DRAW_AREA_12             = 12,
    VO_LINE_DRAW_AREA_13             = 13,
    VO_LINE_DRAW_AREA_14             = 14,
    VO_LINE_DRAW_AREA_15             = 15,
    VO_LINE_DRAW_AREA_16             = 16,
    VO_LINE_DRAW_AREA_17             = 17,
    VO_LINE_DRAW_AREA_18             = 18,
    VO_LINE_DRAW_AREA_19             = 19,
    VO_LINE_DRAW_AREA_20             = 20,
    VO_LINE_DRAW_AREA_21             = 21,
    VO_LINE_DRAW_AREA_22             = 22,
    VO_LINE_DRAW_AREA_23             = 23,
    VO_LINE_DRAW_AREA_24             = 24,
    VO_LINE_DRAW_AREA_25             = 25,
    VO_LINE_DRAW_AREA_26             = 26,
    VO_LINE_DRAW_AREA_27             = 27,
    VO_LINE_DRAW_AREA_28             = 28,
    VO_LINE_DRAW_AREA_29             = 29,
    VO_LINE_DRAW_AREA_30             = 30,
    VO_LINE_DRAW_AREA_31             = 31,
    VO_LINE_DRAW_AREA_MAX            = 32,
} VO_DRV_LINE_DRAW_U;

typedef struct _VO_REMAP_CTRL_FILL_CTL_S
{
    unsigned int line_draw_en     ;
    unsigned int v_line_r_en      ;
    unsigned int v_line_l_en      ;
    unsigned int h_line_b_en      ;
    unsigned int v_line_u_en      ;
    unsigned int line_start_pos_x ;
    unsigned int line_end_pos_x	  ;
    unsigned int line_start_pos_y ;
    unsigned int line_end_pos_y	  ;		
    unsigned int line_width_l;
    unsigned int line_width_h;		
    unsigned int fill_value_cr;
    unsigned int fill_value_cb;
    unsigned int fill_value_y ;
    unsigned int fill_alpha ; 
} VO_REMAP_CTRL_FILL_CTL_S;

typedef struct _VO_REMAP_CTRL_FILL_CMD_S
{
    unsigned int image_active_h   ;
    unsigned int fill_en_rgb      ;
    unsigned int image_active_v   ;
    unsigned int fill_fill_en_yuv ;
} VO_REMAP_CTRL_FILL_CMD_S;

typedef struct _VO_REMAP_CTL_S
{
    VO_REMAP_CTRL_FILL_CMD_S   fillCmd;
    VO_REMAP_CTRL_FILL_CTL_S   fillCtl[VO_LINE_DRAW_AREA_MAX];          
} VO_REMAP_CTL_S;

enum{
    VO_FILLINFO_0,
    VO_FILLINFO_1,
    VO_FILLDATA_0,
    VO_REMAP_FUNC_MAX,
}VO_REMAP_FUNC_NUM;

typedef int (*VO_REMAP_FILL_FUNC) (S_VO_REMAP_REGS_TYPE*pstRegs, unsigned int uData);

int VO_DRV_DrawLine_Remap(void );
int VO_DRV_SetRemap(unsigned int draw_num,VO_REMAP_CTL_S *pstVoRemap);
//DEBUG
int VO_DRV_GetRemapRegsVal(void);
#endif /*_VO_REMAP_DRV_DEF_H_*/
