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
  File Name     : Bt1120_Drv.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include "isp_com.h"
#include "bt1120/bt1120_reg.h"
#include "bt1120/bt1120_drv.h"
/*
*
*/
int Bt1120_Drv_SetSize(struct isp_device *isp,struct bt1120_ctrl_info *ctrl_info)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(ctrl_info);

    U_BT_CTRL_VBIT    stCtrlVbit; 
    stCtrlVbit.u32    = 0;
    stCtrlVbit.bits.bt_vbit_start  = ctrl_info->btCtrlVbit.bt_vbit_start;
    stCtrlVbit.bits.bt_vbit_end    = ctrl_info->btCtrlVbit.bt_vbit_end;
    isp_reg_writel(isp,stCtrlVbit.u32,ISP_IOMEM_BT1120,BT_CTRL_VBIT);  

    U_BT_CTRL_SAV     stCtrlSav; 
    stCtrlSav.u32     = 0;
    stCtrlSav.bits.bt_sav_start    = ctrl_info->bt_sav_start;
    isp_reg_writel(isp,stCtrlSav.u32,ISP_IOMEM_BT1120,BT_CTRL_SAV);  

    U_BT_IMAGE_SIZE_TOTAL stSizeTotal;
    stSizeTotal.u32    = 0;
    stSizeTotal.bits.img_hsize_total= ctrl_info->btSizeTotal.img_hsize_total;
    stSizeTotal.bits.img_vsize_total= ctrl_info->btSizeTotal.img_vsize_total;
    isp_reg_writel(isp,stSizeTotal.u32,ISP_IOMEM_BT1120,BT_IMAGE_SIZE_TOTAL);

    U_BT_IMAGE_SIZE_ACTIVE  stSizeActive;
    stSizeActive.u32   = 0;
    stSizeActive.bits.img_hsize_active= ctrl_info->btSizeActive.img_hsize_active;
    stSizeActive.bits.img_vsize_active= ctrl_info->btSizeActive.img_vsize_active;
    isp_reg_writel(isp,stSizeActive.u32,ISP_IOMEM_BT1120,BT_IMAGE_SIZE_ACTIVE);
    return 0;
}
/*
*
*/
int Bt1120_Drv_setCtl(struct isp_device *isp,struct bt1120_ctrl_info *ctrl_info)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(ctrl_info);
   
    U_BT_IN_SEL   stInSel;
    stInSel.u32  = 0;
    stInSel.bits.bt_in_sel  = ctrl_info->bt_in_sel;
    isp_reg_writel(isp,stInSel.u32,ISP_IOMEM_BT1120,BT_IN_SEL);

    U_BT_CTRL_MODE   stCtrlMode;
    stCtrlMode.u32                = 0;
    stCtrlMode.bits.crc_init_val  = ctrl_info->btCtrlMode.crc_init_val;
    stCtrlMode.bits.crc_order     = ctrl_info->btCtrlMode.crc_order;
    stCtrlMode.bits.yc_reorder    = ctrl_info->btCtrlMode.yc_reorder;
    isp_reg_writel(isp,stCtrlMode.u32,ISP_IOMEM_BT1120,BT_CTRL_MODE);

    U_BT_CONFIG_DONE stConfigDone;
    stConfigDone.u32 = 0;
    stConfigDone.bits.wp_clr        = ctrl_info->btConfigDone.wp_clr;
    isp_reg_writel(isp,stConfigDone.u32,ISP_IOMEM_BT1120,BT_CONFIG_DONE);
    return 0;
}
/*
*
*/
int Bt1120_Drv_EnBt(struct isp_device *isp,unsigned int enable,unsigned int config_done)
{
    ISP_CHECK_POINTER(isp);

    U_BT_CTRL_MODE   stCtrlMode;
    stCtrlMode.u32                = isp_reg_readl(isp,ISP_IOMEM_BT1120,BT_CTRL_MODE);
    stCtrlMode.bits.bt_en         = enable;
    isp_reg_writel(isp,stCtrlMode.u32,ISP_IOMEM_BT1120,BT_CTRL_MODE);

    U_BT_CONFIG_DONE stConfigDone;
    stConfigDone.u32              = isp_reg_readl(isp,ISP_IOMEM_BT1120,BT_CONFIG_DONE);
    stConfigDone.bits.config_done = config_done;//1;
    isp_reg_writel(isp,stConfigDone.u32,ISP_IOMEM_BT1120,BT_CONFIG_DONE);
        
    return 0;
}


