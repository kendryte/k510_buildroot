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

#ifndef _ISP_REMAP_DRV_DEF_H_
#define _ISP_REMAP_DRV_DEF_H_

#include "video/isp_com.h"
#include "video/isp/remap/isp_remap_reg.h"

typedef enum 
{
    ISP_LINE_DRAW_AREA_0              = 0,
    ISP_LINE_DRAW_AREA_1              = 1,
    ISP_LINE_DRAW_AREA_2              = 2,
    ISP_LINE_DRAW_AREA_3              = 3,
    ISP_LINE_DRAW_AREA_4              = 4,
    ISP_LINE_DRAW_AREA_5              = 5,
    ISP_LINE_DRAW_AREA_6              = 6,
    ISP_LINE_DRAW_AREA_7              = 7,
    ISP_LINE_DRAW_AREA_8              = 8,
    ISP_LINE_DRAW_AREA_9              = 9,
    ISP_LINE_DRAW_AREA_10             = 10,
    ISP_LINE_DRAW_AREA_11             = 11,
    ISP_LINE_DRAW_AREA_12             = 12,
    ISP_LINE_DRAW_AREA_13             = 13,
    ISP_LINE_DRAW_AREA_14             = 14,
    ISP_LINE_DRAW_AREA_15             = 15,
    ISP_LINE_DRAW_AREA_16             = 16,
    ISP_LINE_DRAW_AREA_17             = 17,
    ISP_LINE_DRAW_AREA_18             = 18,
    ISP_LINE_DRAW_AREA_19             = 19,
    ISP_LINE_DRAW_AREA_20             = 20,
    ISP_LINE_DRAW_AREA_21             = 21,
    ISP_LINE_DRAW_AREA_22             = 22,
    ISP_LINE_DRAW_AREA_23             = 23,
    ISP_LINE_DRAW_AREA_24             = 24,
    ISP_LINE_DRAW_AREA_25             = 25,
    ISP_LINE_DRAW_AREA_26             = 26,
    ISP_LINE_DRAW_AREA_27             = 27,
    ISP_LINE_DRAW_AREA_28             = 28,
    ISP_LINE_DRAW_AREA_29             = 29,
    ISP_LINE_DRAW_AREA_30             = 30,
    ISP_LINE_DRAW_AREA_31             = 31,
    ISP_LINE_DRAW_AREA_MAX            = 32,
} ISP_DRV_LINE_DRAW_U;

typedef struct _ISP_REMAP_CTL_S
{ 
    unsigned int    LineCtlSet;
    unsigned int    LineDataSet;
    unsigned int    LineEndPosX;
    unsigned int    LineDrawEn;
    unsigned int    VlineRightEn;
    unsigned int    VlineLeftEn; 
    unsigned int    LineStartPosX;
    unsigned int    HlineBottomEn;
    unsigned int    HlineUpEn; 

    unsigned int    LineEndPosY;
    unsigned int    LineWidthL;
    unsigned int    LineStartPosY;
    unsigned int    LineWidthH;

    unsigned int    ValueCr;
    unsigned int    ValueCb; 
    unsigned int    ValueY;
    unsigned int    ValueAlpha;
} ISP_REMAP_CTL_S;

typedef int (*REMAP_FILL_FUNC) (S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData);

enum{
    FILLINFO_0,
    FILLINFO_1,
    FILLDATA_0,
    REMAP_FUNC_MAX,
}REMAP_FUNC_NUM;

//int  ISP_DRV_SetRemap(ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CONFIG_S *ispRemapInfo);
//int  ISP_DRV_REMAP_DrawLineSet(ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CTL_S *stRemapCtl);
int ISP_DRV_SetRemap(ISP_PIPE_DOWN_STREAM_E pipe,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CTL_S *pstIspRemapCtl);
//DEBUG
int ISP_DRV_GetRemapRegsVal(void);
#endif /*_ISP_REMAP_DRV_DEF_H_*/
