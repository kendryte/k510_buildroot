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
  File Name     : bt1120_drv.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _BT1120_DRV_H_
#define _BT1120_DRV_H_

struct bt_ctrl_mode_s                       
{                                        
    unsigned int    bt_en       ;
    unsigned int    yc_reorder  ;
    unsigned int    crc_order   ;
    unsigned int    crc_init_val;
};  

struct bt_ctrl_vbit_s                        
{                                         
    unsigned int    bt_vbit_start;
    unsigned int    bt_vbit_end  ;       
};                     
										  
struct bt_image_size_total_s                             
{                                         
    unsigned int    img_vsize_total;
    unsigned int    img_hsize_total;
};                 
										 
struct  bt_image_size_active_s                          
{    
    unsigned int    img_vsize_active;                                     
    unsigned int    img_hsize_active;
};               
										 
struct  bt_config_done_s                             
{                                         
    unsigned int    config_done;
    unsigned int    wp_clr     ;    
};  

struct bt1120_ctrl_info
{
    unsigned int                   bt_in_sel;
    unsigned int                   bt_sav_start;
    struct bt_ctrl_mode_s          btCtrlMode;
    struct bt_ctrl_vbit_s          btCtrlVbit;
    struct bt_image_size_total_s   btSizeTotal;
    struct bt_image_size_active_s  btSizeActive;
    struct bt_config_done_s        btConfigDone;
};
//
int Bt1120_Drv_SetSize(struct isp_device *isp,struct bt1120_ctrl_info *ctrl_info);
int Bt1120_Drv_setCtl(struct isp_device *isp,struct bt1120_ctrl_info *ctrl_info);
int Bt1120_Drv_EnBt(struct isp_device *isp,unsigned int enable,unsigned int config_done);
#endif /*_BT1120_DRV_H_*/