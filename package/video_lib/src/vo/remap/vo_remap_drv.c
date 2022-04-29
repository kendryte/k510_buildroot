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
  File Name     : vo_remap_drv.c
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/
#include "isp_com.h"
#include "video_subsystem.h"
#include "vo/vo.h"
#include "vo/remap/vo_remap_reg.h"
#include "vo/remap/vo_remap_drv.h"

/*
*
*/
const unsigned int remap_vo_addr_map[32][3] =
{
    {VO_REMAP_INFO_AREA_00_0_CTRL,VO_REMAP_INFO_AREA_00_1_CTRL,VO_REMAP_DATA_AREA_00_0_CTRL},
    {VO_REMAP_INFO_AREA_01_0_CTRL,VO_REMAP_INFO_AREA_01_1_CTRL,VO_REMAP_DATA_AREA_01_0_CTRL},
    {VO_REMAP_INFO_AREA_02_0_CTRL,VO_REMAP_INFO_AREA_02_1_CTRL,VO_REMAP_DATA_AREA_02_0_CTRL},
    {VO_REMAP_INFO_AREA_03_0_CTRL,VO_REMAP_INFO_AREA_03_1_CTRL,VO_REMAP_DATA_AREA_03_0_CTRL},
    {VO_REMAP_INFO_AREA_04_0_CTRL,VO_REMAP_INFO_AREA_04_1_CTRL,VO_REMAP_DATA_AREA_04_0_CTRL},
    {VO_REMAP_INFO_AREA_05_0_CTRL,VO_REMAP_INFO_AREA_05_1_CTRL,VO_REMAP_DATA_AREA_05_0_CTRL},
    {VO_REMAP_INFO_AREA_06_0_CTRL,VO_REMAP_INFO_AREA_06_1_CTRL,VO_REMAP_DATA_AREA_06_0_CTRL},
    {VO_REMAP_INFO_AREA_07_0_CTRL,VO_REMAP_INFO_AREA_07_1_CTRL,VO_REMAP_DATA_AREA_07_0_CTRL},
    {VO_REMAP_INFO_AREA_08_0_CTRL,VO_REMAP_INFO_AREA_08_1_CTRL,VO_REMAP_DATA_AREA_08_0_CTRL},
    {VO_REMAP_INFO_AREA_09_0_CTRL,VO_REMAP_INFO_AREA_09_1_CTRL,VO_REMAP_DATA_AREA_09_0_CTRL},
    {VO_REMAP_INFO_AREA_10_0_CTRL,VO_REMAP_INFO_AREA_10_1_CTRL,VO_REMAP_DATA_AREA_10_0_CTRL},
    {VO_REMAP_INFO_AREA_11_0_CTRL,VO_REMAP_INFO_AREA_11_1_CTRL,VO_REMAP_DATA_AREA_11_0_CTRL},
    {VO_REMAP_INFO_AREA_12_0_CTRL,VO_REMAP_INFO_AREA_12_1_CTRL,VO_REMAP_DATA_AREA_12_0_CTRL},
    {VO_REMAP_INFO_AREA_13_0_CTRL,VO_REMAP_INFO_AREA_13_1_CTRL,VO_REMAP_DATA_AREA_13_0_CTRL},
    {VO_REMAP_INFO_AREA_14_0_CTRL,VO_REMAP_INFO_AREA_14_1_CTRL,VO_REMAP_DATA_AREA_14_0_CTRL},
    {VO_REMAP_INFO_AREA_15_0_CTRL,VO_REMAP_INFO_AREA_15_1_CTRL,VO_REMAP_DATA_AREA_15_0_CTRL},
    {VO_REMAP_INFO_AREA_16_0_CTRL,VO_REMAP_INFO_AREA_16_1_CTRL,VO_REMAP_DATA_AREA_16_0_CTRL},
    {VO_REMAP_INFO_AREA_17_0_CTRL,VO_REMAP_INFO_AREA_17_1_CTRL,VO_REMAP_DATA_AREA_17_0_CTRL},
    {VO_REMAP_INFO_AREA_18_0_CTRL,VO_REMAP_INFO_AREA_18_1_CTRL,VO_REMAP_DATA_AREA_18_0_CTRL},
    {VO_REMAP_INFO_AREA_19_0_CTRL,VO_REMAP_INFO_AREA_19_1_CTRL,VO_REMAP_DATA_AREA_19_0_CTRL},
    {VO_REMAP_INFO_AREA_20_0_CTRL,VO_REMAP_INFO_AREA_20_1_CTRL,VO_REMAP_DATA_AREA_20_0_CTRL},
    {VO_REMAP_INFO_AREA_21_0_CTRL,VO_REMAP_INFO_AREA_21_1_CTRL,VO_REMAP_DATA_AREA_21_0_CTRL},
    {VO_REMAP_INFO_AREA_22_0_CTRL,VO_REMAP_INFO_AREA_22_1_CTRL,VO_REMAP_DATA_AREA_22_0_CTRL},
    {VO_REMAP_INFO_AREA_23_0_CTRL,VO_REMAP_INFO_AREA_23_1_CTRL,VO_REMAP_DATA_AREA_23_0_CTRL},
    {VO_REMAP_INFO_AREA_24_0_CTRL,VO_REMAP_INFO_AREA_24_1_CTRL,VO_REMAP_DATA_AREA_24_0_CTRL},
    {VO_REMAP_INFO_AREA_25_0_CTRL,VO_REMAP_INFO_AREA_25_1_CTRL,VO_REMAP_DATA_AREA_25_0_CTRL},
    {VO_REMAP_INFO_AREA_26_0_CTRL,VO_REMAP_INFO_AREA_26_1_CTRL,VO_REMAP_DATA_AREA_26_0_CTRL},
    {VO_REMAP_INFO_AREA_27_0_CTRL,VO_REMAP_INFO_AREA_27_1_CTRL,VO_REMAP_DATA_AREA_27_0_CTRL},
    {VO_REMAP_INFO_AREA_28_0_CTRL,VO_REMAP_INFO_AREA_28_1_CTRL,VO_REMAP_DATA_AREA_28_0_CTRL},
    {VO_REMAP_INFO_AREA_29_0_CTRL,VO_REMAP_INFO_AREA_29_1_CTRL,VO_REMAP_DATA_AREA_29_0_CTRL},
    {VO_REMAP_INFO_AREA_30_0_CTRL,VO_REMAP_INFO_AREA_30_1_CTRL,VO_REMAP_DATA_AREA_30_0_CTRL},
    {VO_REMAP_INFO_AREA_31_0_CTRL,VO_REMAP_INFO_AREA_31_1_CTRL,VO_REMAP_DATA_AREA_31_0_CTRL}
};
/*
*
*/
int Vo_Drv_Remap_FillCmd(struct isp_device *isp,VO_REMAP_CTRL_FILL_CMD_S *fillCmd)
{ 
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(fillCmd);

    U_VO_REMAP_CTRL_FILL_CMD    cmd_udata;
    cmd_udata.u32 = 0;
    cmd_udata.bits.image_active_h = fillCmd->image_active_h;
    cmd_udata.bits.image_active_v = fillCmd->image_active_v;
    cmd_udata.bits.fill_en_rgb = fillCmd->fill_en_rgb;
    cmd_udata.bits.fill_fill_en_yuv = fillCmd->fill_fill_en_yuv;    
    isp_reg_writel(isp, cmd_udata.u32,ISP_IOMEM_VO_REMAP,VO_REMAP_FILL_CMD_CTRL);

    return 0;
}
/*
*
*/
int Vo_Drv_Remap_DrawLineSet(struct isp_device *isp,VO_DRV_LINE_DRAW_U DrawAreaNum,VO_REMAP_CTRL_FILL_CTL_S *fillCtl)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(fillCtl);

    unsigned int ErrCode = 0;
    if(DrawAreaNum > VO_LINE_DRAW_AREA_31 || DrawAreaNum < VO_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_REMAP,remap_vo_addr_map[DrawAreaNum][VO_FILLINFO_0]);
    info0_udata.bits.line_draw_en     = fillCtl->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillCtl->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillCtl->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillCtl->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillCtl->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillCtl->line_start_pos_x;
    info0_udata.bits.line_end_pos_x   = fillCtl->line_end_pos_x;
    isp_reg_writel(isp, info0_udata.u32,ISP_IOMEM_VO_REMAP,remap_vo_addr_map[DrawAreaNum][VO_FILLINFO_0]);

	U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_REMAP,remap_vo_addr_map[DrawAreaNum][VO_FILLINFO_1]);
    info1_udata.bits.line_start_pos_y = fillCtl->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillCtl->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillCtl->line_width_h;
    info1_udata.bits.line_width_l     = fillCtl->line_width_l;
	isp_reg_writel(isp, info1_udata.u32,ISP_IOMEM_VO_REMAP,remap_vo_addr_map[DrawAreaNum][VO_FILLINFO_1]);

    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillCtl->fill_value_y;
    data_udata.bits.fill_value_cb     = fillCtl->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillCtl->fill_value_cr;
    data_udata.bits.fill_alpha        = fillCtl->fill_alpha;
	isp_reg_writel(isp, data_udata.u32,ISP_IOMEM_VO_REMAP,remap_vo_addr_map[DrawAreaNum][VO_FILLDATA_0]);

    return ErrCode;
}

