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
 * isp_f2k_remap.c
 *
 * CANAAN ISP - remap module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_2k/remap/isp_remap_drv.h"
#include "isp_2k/remap/isp_remap_reg.h"
/*
*
*/
const unsigned int remap_f2k_addr_map[32][3] = {
    {ISP_FILL_INFO_AREA_00_0_CTRL,ISP_FILL_INFO_AREA_00_1_CTRL,ISP_FILL_DATA_AREA_00_0_CTRL},
    {ISP_FILL_INFO_AREA_01_0_CTRL,ISP_FILL_INFO_AREA_01_1_CTRL,ISP_FILL_DATA_AREA_01_0_CTRL},
    {ISP_FILL_INFO_AREA_02_0_CTRL,ISP_FILL_INFO_AREA_02_1_CTRL,ISP_FILL_DATA_AREA_02_0_CTRL},
    {ISP_FILL_INFO_AREA_03_0_CTRL,ISP_FILL_INFO_AREA_03_1_CTRL,ISP_FILL_DATA_AREA_03_0_CTRL},
    {ISP_FILL_INFO_AREA_04_0_CTRL,ISP_FILL_INFO_AREA_04_1_CTRL,ISP_FILL_DATA_AREA_04_0_CTRL},
    {ISP_FILL_INFO_AREA_05_0_CTRL,ISP_FILL_INFO_AREA_05_1_CTRL,ISP_FILL_DATA_AREA_05_0_CTRL},
    {ISP_FILL_INFO_AREA_06_0_CTRL,ISP_FILL_INFO_AREA_06_1_CTRL,ISP_FILL_DATA_AREA_06_0_CTRL},
    {ISP_FILL_INFO_AREA_07_0_CTRL,ISP_FILL_INFO_AREA_07_1_CTRL,ISP_FILL_DATA_AREA_07_0_CTRL},
    {ISP_FILL_INFO_AREA_08_0_CTRL,ISP_FILL_INFO_AREA_08_1_CTRL,ISP_FILL_DATA_AREA_08_0_CTRL},
    {ISP_FILL_INFO_AREA_09_0_CTRL,ISP_FILL_INFO_AREA_09_1_CTRL,ISP_FILL_DATA_AREA_09_0_CTRL},
    {ISP_FILL_INFO_AREA_10_0_CTRL,ISP_FILL_INFO_AREA_10_1_CTRL,ISP_FILL_DATA_AREA_10_0_CTRL},
    {ISP_FILL_INFO_AREA_11_0_CTRL,ISP_FILL_INFO_AREA_11_1_CTRL,ISP_FILL_DATA_AREA_11_0_CTRL},
    {ISP_FILL_INFO_AREA_12_0_CTRL,ISP_FILL_INFO_AREA_12_1_CTRL,ISP_FILL_DATA_AREA_12_0_CTRL},
    {ISP_FILL_INFO_AREA_13_0_CTRL,ISP_FILL_INFO_AREA_13_1_CTRL,ISP_FILL_DATA_AREA_13_0_CTRL},
    {ISP_FILL_INFO_AREA_14_0_CTRL,ISP_FILL_INFO_AREA_14_1_CTRL,ISP_FILL_DATA_AREA_14_0_CTRL},
    {ISP_FILL_INFO_AREA_15_0_CTRL,ISP_FILL_INFO_AREA_15_1_CTRL,ISP_FILL_DATA_AREA_15_0_CTRL},
    {ISP_FILL_INFO_AREA_16_0_CTRL,ISP_FILL_INFO_AREA_16_1_CTRL,ISP_FILL_DATA_AREA_16_0_CTRL},
    {ISP_FILL_INFO_AREA_17_0_CTRL,ISP_FILL_INFO_AREA_17_1_CTRL,ISP_FILL_DATA_AREA_17_0_CTRL},
    {ISP_FILL_INFO_AREA_18_0_CTRL,ISP_FILL_INFO_AREA_18_1_CTRL,ISP_FILL_DATA_AREA_18_0_CTRL},
    {ISP_FILL_INFO_AREA_19_0_CTRL,ISP_FILL_INFO_AREA_19_1_CTRL,ISP_FILL_DATA_AREA_19_0_CTRL},
    {ISP_FILL_INFO_AREA_20_0_CTRL,ISP_FILL_INFO_AREA_20_1_CTRL,ISP_FILL_DATA_AREA_20_0_CTRL},
    {ISP_FILL_INFO_AREA_21_0_CTRL,ISP_FILL_INFO_AREA_21_1_CTRL,ISP_FILL_DATA_AREA_21_0_CTRL},
    {ISP_FILL_INFO_AREA_22_0_CTRL,ISP_FILL_INFO_AREA_22_1_CTRL,ISP_FILL_DATA_AREA_22_0_CTRL},
    {ISP_FILL_INFO_AREA_23_0_CTRL,ISP_FILL_INFO_AREA_23_1_CTRL,ISP_FILL_DATA_AREA_23_0_CTRL},
    {ISP_FILL_INFO_AREA_24_0_CTRL,ISP_FILL_INFO_AREA_24_1_CTRL,ISP_FILL_DATA_AREA_24_0_CTRL},
    {ISP_FILL_INFO_AREA_25_0_CTRL,ISP_FILL_INFO_AREA_25_1_CTRL,ISP_FILL_DATA_AREA_25_0_CTRL},
    {ISP_FILL_INFO_AREA_26_0_CTRL,ISP_FILL_INFO_AREA_26_1_CTRL,ISP_FILL_DATA_AREA_26_0_CTRL},
    {ISP_FILL_INFO_AREA_27_0_CTRL,ISP_FILL_INFO_AREA_27_1_CTRL,ISP_FILL_DATA_AREA_27_0_CTRL},
    {ISP_FILL_INFO_AREA_28_0_CTRL,ISP_FILL_INFO_AREA_28_1_CTRL,ISP_FILL_DATA_AREA_28_0_CTRL},
    {ISP_FILL_INFO_AREA_29_0_CTRL,ISP_FILL_INFO_AREA_29_1_CTRL,ISP_FILL_DATA_AREA_29_0_CTRL},
    {ISP_FILL_INFO_AREA_30_0_CTRL,ISP_FILL_INFO_AREA_30_1_CTRL,ISP_FILL_DATA_AREA_30_0_CTRL},
    {ISP_FILL_INFO_AREA_31_0_CTRL,ISP_FILL_INFO_AREA_31_1_CTRL,ISP_FILL_DATA_AREA_31_0_CTRL}
};
/*
*
*/
int Isp_Drv_F2k_Remap_SetMainLine(struct isp_device *isp,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_ATTR_S *stRemapCtl)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(stRemapCtl);

    unsigned int ErrCode = 0;
    if(DrawAreaNum > ISP_LINE_DRAW_AREA_31 || DrawAreaNum < ISP_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }
    //
    U_ISP_FILL_DATA_AREA_0_CTRL     stIspFillData0;
    stIspFillData0.u32 = 0;
    stIspFillData0.bits.fill_value_cb = stRemapCtl->ValueCb;
    stIspFillData0.bits.fill_value_cr = stRemapCtl->ValueCr;
    stIspFillData0.bits.fill_value_y = stRemapCtl->ValueY;
    stIspFillData0.bits.Fill_alpha = stRemapCtl->ValueAlpha;
    isp_reg_writel(isp, stIspFillData0.u32,ISP_IOMEM_F2K_MAIN_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_0]);
 
    U_ISP_FILL_INFO_AREA_0_CTRL     stIspFillInfo0;
    stIspFillInfo0.u32 = 0;
    stIspFillInfo0.bits.h_line_b_en = stRemapCtl->HlineBottomEn;
    stIspFillInfo0.bits.h_line_u_en = stRemapCtl->HlineUpEn;
    stIspFillInfo0.bits.line_draw_en = stRemapCtl->LineDrawEn;
    stIspFillInfo0.bits.v_line_l_en = stRemapCtl->VlineLeftEn;
    stIspFillInfo0.bits.v_line_r_en = stRemapCtl->VlineRightEn;
    stIspFillInfo0.bits.line_start_pos_x = stRemapCtl->LineStartPosX;
    stIspFillInfo0.bits.line_end_pos_x = stRemapCtl->LineEndPosX;
    isp_reg_writel(isp, stIspFillInfo0.u32,ISP_IOMEM_F2K_MAIN_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_1]);

    U_ISP_FILL_INFO_AREA_1_CTRL     stIspFillInfo1;
    stIspFillInfo1.u32 = 0;
    stIspFillInfo1.bits.line_start_pos_y = stRemapCtl->LineStartPosY;
    stIspFillInfo1.bits.line_end_pos_y = stRemapCtl->LineEndPosY;
    stIspFillInfo1.bits.line_width_h = stRemapCtl->LineWidthH;
    stIspFillInfo1.bits.line_width_l = stRemapCtl->LineWidthL;
    isp_reg_writel(isp, stIspFillInfo1.u32,ISP_IOMEM_F2K_MAIN_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLDATA_0]);
        
    return ErrCode;
}
/*
*
*/
int  Isp_Drv_F2k_Remap_SetOut0Line(struct isp_device *isp,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_ATTR_S *stRemapCtl)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(stRemapCtl);

    unsigned int ErrCode = 0;
    if(DrawAreaNum > ISP_LINE_DRAW_AREA_31 || DrawAreaNum < ISP_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    U_ISP_FILL_DATA_AREA_0_CTRL     stIspFillData0;
    stIspFillData0.u32 = 0;
    stIspFillData0.bits.fill_value_cb = stRemapCtl->ValueCb;
    stIspFillData0.bits.fill_value_cr = stRemapCtl->ValueCr;
    stIspFillData0.bits.fill_value_y = stRemapCtl->ValueY;
    stIspFillData0.bits.Fill_alpha = stRemapCtl->ValueAlpha;
    isp_reg_writel(isp, stIspFillData0.u32,ISP_IOMEM_F2K_OUT0_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_0]);

    
    U_ISP_FILL_INFO_AREA_0_CTRL     stIspFillInfo0;
    stIspFillInfo0.u32 = 0;
    stIspFillInfo0.bits.h_line_b_en = stRemapCtl->HlineBottomEn;
    stIspFillInfo0.bits.h_line_u_en = stRemapCtl->HlineUpEn;
    stIspFillInfo0.bits.line_draw_en = stRemapCtl->LineDrawEn;
    stIspFillInfo0.bits.v_line_l_en = stRemapCtl->VlineLeftEn;
    stIspFillInfo0.bits.v_line_r_en = stRemapCtl->VlineRightEn;
    stIspFillInfo0.bits.line_start_pos_x = stRemapCtl->LineStartPosX;
    stIspFillInfo0.bits.line_end_pos_x = stRemapCtl->LineEndPosX;
    isp_reg_writel(isp, stIspFillInfo0.u32,ISP_IOMEM_F2K_OUT0_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_1]);

    U_ISP_FILL_INFO_AREA_1_CTRL     stIspFillInfo1;
    stIspFillInfo1.u32 = 0;
    stIspFillInfo1.bits.line_start_pos_y = stRemapCtl->LineStartPosY;
    stIspFillInfo1.bits.line_end_pos_y = stRemapCtl->LineEndPosY;
    stIspFillInfo1.bits.line_width_h = stRemapCtl->LineWidthH;
    stIspFillInfo1.bits.line_width_l = stRemapCtl->LineWidthL;
    isp_reg_writel(isp, stIspFillInfo1.u32,ISP_IOMEM_F2K_OUT0_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLDATA_0]);
       
    return ErrCode;
}
/*
*
*/
int  Isp_Drv_F2k_Remap_SetOut1Line(struct isp_device *isp,ISP_DRV_LINE_DRAW_U DrawAreaNum,ISP_REMAP_ATTR_S *stRemapCtl)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(stRemapCtl);

    unsigned int ErrCode = 0;
    if(DrawAreaNum > ISP_LINE_DRAW_AREA_31 || DrawAreaNum < ISP_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    U_ISP_FILL_DATA_AREA_0_CTRL     stIspFillData0;
    stIspFillData0.u32 = 0;
    stIspFillData0.bits.fill_value_cb = stRemapCtl->ValueCb;
    stIspFillData0.bits.fill_value_cr = stRemapCtl->ValueCr;
    stIspFillData0.bits.fill_value_y = stRemapCtl->ValueY;
    stIspFillData0.bits.Fill_alpha = stRemapCtl->ValueAlpha;
    isp_reg_writel(isp, stIspFillData0.u32,ISP_IOMEM_F2K_OUT1_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_0]);
       
    U_ISP_FILL_INFO_AREA_0_CTRL     stIspFillInfo0;
    stIspFillInfo0.u32 = 0;
    stIspFillInfo0.bits.h_line_b_en = stRemapCtl->HlineBottomEn;
    stIspFillInfo0.bits.h_line_u_en = stRemapCtl->HlineUpEn;
    stIspFillInfo0.bits.line_draw_en = stRemapCtl->LineDrawEn;
    stIspFillInfo0.bits.v_line_l_en = stRemapCtl->VlineLeftEn;
    stIspFillInfo0.bits.v_line_r_en = stRemapCtl->VlineRightEn;
    stIspFillInfo0.bits.line_start_pos_x = stRemapCtl->LineStartPosX;
    stIspFillInfo0.bits.line_end_pos_x = stRemapCtl->LineEndPosX;
    isp_reg_writel(isp, stIspFillInfo0.u32,ISP_IOMEM_F2K_OUT1_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLINFO_1]);

    U_ISP_FILL_INFO_AREA_1_CTRL     stIspFillInfo1;
    stIspFillInfo1.u32 = 0;
    stIspFillInfo1.bits.line_start_pos_y = stRemapCtl->LineStartPosY;
    stIspFillInfo1.bits.line_end_pos_y = stRemapCtl->LineEndPosY;
    stIspFillInfo1.bits.line_width_h = stRemapCtl->LineWidthH;
    stIspFillInfo1.bits.line_width_l = stRemapCtl->LineWidthL;
    isp_reg_writel(isp, stIspFillInfo1.u32,ISP_IOMEM_F2K_OUT1_REMAP,remap_f2k_addr_map[DrawAreaNum][FILLDATA_0]);
            
    return ErrCode;
}
