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
  File Name     : bt1120.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include "video_subsystem.h"
#include "bt1120/bt1120_drv.h"
#include "bt1120/bt1120.h"
#include "isp_com.h"

/*
*
*/
static void bt1120_getCfg(struct bt1120_ctrl_info *ctrl_info,struct bt1120_cfg_info *bt1120_info)
{
    ISP_CHECK_POINTER(ctrl_info);
    ISP_CHECK_POINTER(bt1120_info);

    ctrl_info->bt_in_sel = bt1120_info->bt_in_sel;
    ctrl_info->bt_sav_start = bt1120_info->img_hsize_total - bt1120_info->img_hsize - 4 -1;//0x113;
    //
    struct bt_ctrl_mode_s *btCtrlMode = &ctrl_info->btCtrlMode;    
    btCtrlMode->bt_en        = bt1120_info->bt1120_en;
    btCtrlMode->yc_reorder   = 0;
    btCtrlMode->crc_order    = 0;
    btCtrlMode->crc_init_val = 1;
    //
    struct bt_ctrl_vbit_s *btCtrlVbit = &ctrl_info->btCtrlVbit;
    btCtrlVbit->bt_vbit_start = 0x0;
    btCtrlVbit->bt_vbit_end   = bt1120_info->img_vsize_total - bt1120_info->img_vsize - 1;//0x2c;
    //
    struct bt_image_size_total_s   *btSizeTotal = &ctrl_info->btSizeTotal;
    btSizeTotal->img_hsize_total = bt1120_info->img_hsize_total - 1;
    btSizeTotal->img_vsize_total = bt1120_info->img_vsize_total - 1;
    //
    struct bt_image_size_active_s  *btSizeActive = &ctrl_info->btSizeActive;
    btSizeActive->img_hsize_active = bt1120_info->img_hsize - 1;
    btSizeActive->img_vsize_active = bt1120_info->img_vsize - 1;
    //
    struct bt_config_done_s *btConfigDone = &ctrl_info->btConfigDone;
    btConfigDone->wp_clr = 1;
    btConfigDone->config_done = 1;

    return;
}
/*
*
*/
int bt1120_Init_cfg(struct isp_device *isp,struct bt1120_cfg_info *bt1120_info)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(bt1120_info);

    struct bt1120_ctrl_info ctrl_info;
    bt1120_getCfg(&ctrl_info,bt1120_info);
    //
    Bt1120_Drv_SetSize(isp,&ctrl_info);
    //
    Bt1120_Drv_setCtl(isp,&ctrl_info);
    //
    unsigned int enable = ctrl_info.btCtrlMode.bt_en;
    unsigned int config_done = ctrl_info.btConfigDone.config_done;
    Bt1120_Drv_EnBt(isp,enable,config_done);
    return 0;
}
/*
*
*/
int bt1120_Init(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    struct isp_bt1120_device *bt1120 = &isp->isp_bt1120;

    struct bt1120_cfg_info *bt1120_info = &bt1120->bt1120_info;

    struct bt1120_ctrl_info ctrl_info;
    bt1120_getCfg(&ctrl_info,bt1120_info);
    //
    Bt1120_Drv_SetSize(isp,&ctrl_info);
    //
    Bt1120_Drv_setCtl(isp,&ctrl_info);
    //
    unsigned int enable = ctrl_info.btCtrlMode.bt_en;
    unsigned int config_done = ctrl_info.btConfigDone.config_done;
    Bt1120_Drv_EnBt(isp,enable,config_done);
    return 0;
}