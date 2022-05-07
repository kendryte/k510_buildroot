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
//#include "video/isp/isp.h"
#include "video/isp/remap/isp_remap_drv.h"
#include "video/isp/remap/isp_remap_reg.h"

extern unsigned int  *reg_isp_2k_remap_base;
#define ISP_2K_DRV_REMAP_REG_CTX(pstCtx)	pstCtx = (S_ISP_REMAP_REGS_TYPE *)(reg_isp_2k_remap_base)

static REMAP_FILL_FUNC remap_fill_func[ISP_LINE_DRAW_AREA_MAX][REMAP_FUNC_MAX] =
{
    {ISP_REMAP_DRV_SET_FillInfo_0_00,ISP_REMAP_DRV_SET_FillInfo_1_00,ISP_REMAP_DRV_SET_FillData_0_00},
    {ISP_REMAP_DRV_SET_FillInfo_0_01,ISP_REMAP_DRV_SET_FillInfo_1_01,ISP_REMAP_DRV_SET_FillData_0_01},
    {ISP_REMAP_DRV_SET_FillInfo_0_02,ISP_REMAP_DRV_SET_FillInfo_1_02,ISP_REMAP_DRV_SET_FillData_0_02},
    {ISP_REMAP_DRV_SET_FillInfo_0_03,ISP_REMAP_DRV_SET_FillInfo_1_03,ISP_REMAP_DRV_SET_FillData_0_03},
    {ISP_REMAP_DRV_SET_FillInfo_0_04,ISP_REMAP_DRV_SET_FillInfo_1_04,ISP_REMAP_DRV_SET_FillData_0_04},
    {ISP_REMAP_DRV_SET_FillInfo_0_05,ISP_REMAP_DRV_SET_FillInfo_1_05,ISP_REMAP_DRV_SET_FillData_0_05},
    {ISP_REMAP_DRV_SET_FillInfo_0_06,ISP_REMAP_DRV_SET_FillInfo_1_06,ISP_REMAP_DRV_SET_FillData_0_06},
    {ISP_REMAP_DRV_SET_FillInfo_0_07,ISP_REMAP_DRV_SET_FillInfo_1_07,ISP_REMAP_DRV_SET_FillData_0_07},
    {ISP_REMAP_DRV_SET_FillInfo_0_08,ISP_REMAP_DRV_SET_FillInfo_1_08,ISP_REMAP_DRV_SET_FillData_0_08},
    {ISP_REMAP_DRV_SET_FillInfo_0_09,ISP_REMAP_DRV_SET_FillInfo_1_09,ISP_REMAP_DRV_SET_FillData_0_09},
    {ISP_REMAP_DRV_SET_FillInfo_0_10,ISP_REMAP_DRV_SET_FillInfo_1_10,ISP_REMAP_DRV_SET_FillData_0_10},
    {ISP_REMAP_DRV_SET_FillInfo_0_11,ISP_REMAP_DRV_SET_FillInfo_1_11,ISP_REMAP_DRV_SET_FillData_0_11},
    {ISP_REMAP_DRV_SET_FillInfo_0_12,ISP_REMAP_DRV_SET_FillInfo_1_12,ISP_REMAP_DRV_SET_FillData_0_12},
    {ISP_REMAP_DRV_SET_FillInfo_0_13,ISP_REMAP_DRV_SET_FillInfo_1_13,ISP_REMAP_DRV_SET_FillData_0_13},
    {ISP_REMAP_DRV_SET_FillInfo_0_14,ISP_REMAP_DRV_SET_FillInfo_1_14,ISP_REMAP_DRV_SET_FillData_0_14},
    {ISP_REMAP_DRV_SET_FillInfo_0_15,ISP_REMAP_DRV_SET_FillInfo_1_15,ISP_REMAP_DRV_SET_FillData_0_15},
    {ISP_REMAP_DRV_SET_FillInfo_0_16,ISP_REMAP_DRV_SET_FillInfo_1_16,ISP_REMAP_DRV_SET_FillData_0_16},
    {ISP_REMAP_DRV_SET_FillInfo_0_17,ISP_REMAP_DRV_SET_FillInfo_1_17,ISP_REMAP_DRV_SET_FillData_0_17},
    {ISP_REMAP_DRV_SET_FillInfo_0_18,ISP_REMAP_DRV_SET_FillInfo_1_18,ISP_REMAP_DRV_SET_FillData_0_18},
    {ISP_REMAP_DRV_SET_FillInfo_0_19,ISP_REMAP_DRV_SET_FillInfo_1_19,ISP_REMAP_DRV_SET_FillData_0_19},
    {ISP_REMAP_DRV_SET_FillInfo_0_20,ISP_REMAP_DRV_SET_FillInfo_1_20,ISP_REMAP_DRV_SET_FillData_0_20},
    {ISP_REMAP_DRV_SET_FillInfo_0_21,ISP_REMAP_DRV_SET_FillInfo_1_21,ISP_REMAP_DRV_SET_FillData_0_21},
    {ISP_REMAP_DRV_SET_FillInfo_0_22,ISP_REMAP_DRV_SET_FillInfo_1_22,ISP_REMAP_DRV_SET_FillData_0_22},
    {ISP_REMAP_DRV_SET_FillInfo_0_23,ISP_REMAP_DRV_SET_FillInfo_1_23,ISP_REMAP_DRV_SET_FillData_0_23},
    {ISP_REMAP_DRV_SET_FillInfo_0_24,ISP_REMAP_DRV_SET_FillInfo_1_24,ISP_REMAP_DRV_SET_FillData_0_24},
    {ISP_REMAP_DRV_SET_FillInfo_0_25,ISP_REMAP_DRV_SET_FillInfo_1_25,ISP_REMAP_DRV_SET_FillData_0_25},
    {ISP_REMAP_DRV_SET_FillInfo_0_26,ISP_REMAP_DRV_SET_FillInfo_1_26,ISP_REMAP_DRV_SET_FillData_0_26},
    {ISP_REMAP_DRV_SET_FillInfo_0_27,ISP_REMAP_DRV_SET_FillInfo_1_27,ISP_REMAP_DRV_SET_FillData_0_27},
    {ISP_REMAP_DRV_SET_FillInfo_0_28,ISP_REMAP_DRV_SET_FillInfo_1_28,ISP_REMAP_DRV_SET_FillData_0_28},
    {ISP_REMAP_DRV_SET_FillInfo_0_29,ISP_REMAP_DRV_SET_FillInfo_1_29,ISP_REMAP_DRV_SET_FillData_0_29},
    {ISP_REMAP_DRV_SET_FillInfo_0_30,ISP_REMAP_DRV_SET_FillInfo_1_30,ISP_REMAP_DRV_SET_FillData_0_30},
    {ISP_REMAP_DRV_SET_FillInfo_0_31,ISP_REMAP_DRV_SET_FillInfo_1_31,ISP_REMAP_DRV_SET_FillData_0_31},
};
/*
*
*/
static int  ISP_DRV_REMAP_DrawLineSet(ISP_PIPE_DOWN_STREAM_E pipe,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CTL_S *stRemapCtl)
{
    ISP_CHECK_POINTER(stRemapCtl);

    S_ISP_REMAP_REGS_TYPE *apstIspRemapReg = NULL;
    ISP_2K_DRV_REMAP_REG_CTX(apstIspRemapReg);    

    if( pipe == ISP_PIPE_MAIN_OUT)
        apstIspRemapReg =(void *)apstIspRemapReg + 0x400;
    else if( pipe == ISP_PIPE_DS0_OUT)
        apstIspRemapReg = apstIspRemapReg;
    else if( pipe == ISP_PIPE_DS1_OUT)      
        apstIspRemapReg = (void *)apstIspRemapReg +0x200;
    else
        printf("pipe no exist!\n");

    printf("IspRemap addr = 0x%x\n",apstIspRemapReg);
    unsigned int ErrCode = 0;
    if(DrawAreaNum > ISP_LINE_DRAW_AREA_31 || DrawAreaNum < ISP_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    if(stRemapCtl->LineDataSet)
    {
        U_ISP_FILL_DATA_AREA_0_CTRL     stIspFillData0;
        stIspFillData0.u32 = 0;
        stIspFillData0.bits.fill_value_cb = stRemapCtl->ValueCb;
        stIspFillData0.bits.fill_value_cr = stRemapCtl->ValueCr;
        stIspFillData0.bits.fill_value_y = stRemapCtl->ValueY;
        stIspFillData0.bits.Fill_alpha = stRemapCtl->ValueAlpha;
        remap_fill_func[DrawAreaNum][FILLDATA_0]((apstIspRemapReg+0x100),stIspFillData0.u32);
    }

    if(stRemapCtl->LineCtlSet)
    {      
        U_ISP_FILL_INFO_AREA_0_CTRL     stIspFillInfo0;
        stIspFillInfo0.u32 = 0;
        stIspFillInfo0.bits.h_line_b_en = stRemapCtl->HlineBottomEn;
        stIspFillInfo0.bits.h_line_u_en = stRemapCtl->HlineUpEn;
        stIspFillInfo0.bits.line_draw_en = stRemapCtl->LineDrawEn;
        stIspFillInfo0.bits.v_line_l_en = stRemapCtl->VlineLeftEn;
        stIspFillInfo0.bits.v_line_r_en = stRemapCtl->VlineRightEn;
        stIspFillInfo0.bits.line_start_pos_x = stRemapCtl->LineStartPosX;
        stIspFillInfo0.bits.line_end_pos_x = stRemapCtl->LineEndPosX;
        remap_fill_func[DrawAreaNum][FILLINFO_0](apstIspRemapReg,stIspFillInfo0.u32);

        U_ISP_FILL_INFO_AREA_1_CTRL     stIspFillInfo1;
        stIspFillInfo1.u32 = 0;
        stIspFillInfo1.bits.line_start_pos_y = stRemapCtl->LineStartPosY;
        stIspFillInfo1.bits.line_end_pos_y = stRemapCtl->LineEndPosY;
        stIspFillInfo1.bits.line_width_h = stRemapCtl->LineWidthH;
        stIspFillInfo1.bits.line_width_l = stRemapCtl->LineWidthL;
        remap_fill_func[DrawAreaNum][FILLINFO_1](apstIspRemapReg,stIspFillInfo1.u32);
    }
        
    return ErrCode;
}
/*
*
*/
int  ISP_DRV_SetRemap(ISP_PIPE_DOWN_STREAM_E pipe,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CTL_S *pstIspRemapCtl)
{
    ISP_CHECK_POINTER(pstIspRemapCtl);

    ISP_DRV_REMAP_DrawLineSet(pipe,DrawAreaNum,pstIspRemapCtl);

    return 0;
}
//debug
int ISP_DRV_GetRemapRegsVal(void)
{
    S_ISP_REMAP_REGS_TYPE *apstIspRemapReg = NULL;
    ISP_2K_DRV_REMAP_REG_CTX(apstIspRemapReg);

    ISP_REMAP_DRV_GET_RemapRegsVal(apstIspRemapReg);
    apstIspRemapReg = apstIspRemapReg + 0x200;
    ISP_REMAP_DRV_GET_RemapRegsVal(apstIspRemapReg);  
    apstIspRemapReg = apstIspRemapReg + 0x400;
    ISP_REMAP_DRV_GET_RemapRegsVal(apstIspRemapReg);
    return 0;
}
#if 0
/*
*
*/
int  ISP_DRV_SetRemap(ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_CONFIG_S *ispRemapInfo)
{
    ISP_CHECK_POINTER(ispRemapInfo);
    ISP_REMAP_CTL_S stRemapCtl;

    stRemapCtl.LineCtlSet = ispRemapInfo->LineCtlSet;
    stRemapCtl.LineDataSet = ispRemapInfo->LineDataSet;
    stRemapCtl.LineDrawEn = ispRemapInfo->LineDrawEn;
    stRemapCtl.HlineUpEn = ispRemapInfo->HlineUpEn;
    stRemapCtl.HlineBottomEn = ispRemapInfo->HlineBottomEn;
    stRemapCtl.VlineLeftEn = ispRemapInfo->VlineLeftEn;
    stRemapCtl.VlineRightEn = ispRemapInfo->VlineRightEn;
    stRemapCtl.LineStartPosX = ispRemapInfo->LineStartPosX;
    stRemapCtl.LineEndPosX = ispRemapInfo->LineEndPosX;
    stRemapCtl.LineStartPosY = ispRemapInfo->LineStartPosY;
    stRemapCtl.LineEndPosY = ispRemapInfo->LineEndPosY;
    stRemapCtl.LineWidthH = ispRemapInfo->LineWidthH;
    stRemapCtl.LineWidthL = ispRemapInfo->LineWidthL;
    //
    stRemapCtl.ValueY = ispRemapInfo->ValueY;
    stRemapCtl.ValueCb = ispRemapInfo->ValueCb;
    stRemapCtl.ValueCr = ispRemapInfo->ValueCr;
    stRemapCtl.ValueAlpha = ispRemapInfo->ValueAlpha;
    ISP_DRV_REMAP_DrawLineSet(DrawAreaNum,&stRemapCtl);
    return 0;
}
#endif
