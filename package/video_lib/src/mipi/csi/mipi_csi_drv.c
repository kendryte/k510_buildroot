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
  File Name     : mipi_csi_drv.c
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
#include "mipi/csi/mipi_csi_reg.h"
#include "mipi/csi/mipi_csi_drv.h"
/*
*
*/
void Mipi_Csi_Drv_SetCfg(struct isp_device *isp,struct mipi_csi_cfg_info *cfg_info)
{
    ISP_CHECK_POINTER(isp);
    //csi0
    U_CSI_RX_STREAM_SFT_RST csi0_sft_rst;
    csi0_sft_rst.udata = 0;
    csi0_sft_rst.bits.front = 1;
    csi0_sft_rst.bits.protocol = 1;
    isp_reg_writel(isp,csi0_sft_rst.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_SFT_RST);
//
    csi0_sft_rst.udata = 0;
    csi0_sft_rst.bits.front = 0;
    csi0_sft_rst.bits.protocol = 0;
    isp_reg_writel(isp,csi0_sft_rst.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_SFT_RST);
//
    U_CSI_RX_STREAM_STATIC_CFG csi0_static_cfg;
    csi0_static_cfg.udata = 0;    
    csi0_static_cfg.bits.lane_nb            = cfg_info->csi0_lane_nb;
    csi0_static_cfg.bits.sony_wdr           = cfg_info->csi0_sony_wdr;
    csi0_static_cfg.bits.dl0_map            = cfg_info->csi0_dl0_map;
    csi0_static_cfg.bits.dl1_map            = cfg_info->csi0_dl1_map;
    csi0_static_cfg.bits.dl2_map            = cfg_info->csi0_dl2_map;
    csi0_static_cfg.bits.dl3_map            = cfg_info->csi0_dl3_map;
    isp_reg_writel(isp,csi0_static_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_STATIC_CFG);
//
    U_CSI_RX_STREAM_ERR_BYPASS_CFG csi0_bypass_cfg;
    csi0_bypass_cfg.udata = 0;
    csi0_bypass_cfg.bits.crc = cfg_info->csi0_crc;    
    csi0_bypass_cfg.bits.ecc = cfg_info->csi0_ecc;    
    csi0_bypass_cfg.bits.data_id = cfg_info->csi0_ecc;  
    isp_reg_writel(isp,csi0_bypass_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_ERR_BYPASS_CFG);
//
    U_CSI_RX_STREAM_MONITOR_IRQS csi0_irqs_mon_info;
    csi0_irqs_mon_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_mon_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_MONITOR_IRQS);
//
    U_CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG  csi0_irqs_mon_mask_info;
    csi0_irqs_mon_mask_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_mon_mask_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG);          
//
    U_CSI_RX_STREAM_INFO_IRQS  csi0_irqs_info;
    csi0_irqs_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_INFO_IRQS); 
//
    U_CSI_RX_STREAM_INFO_IRQS_MASK_CFG  csi0_irqs_mask_info;
    csi0_irqs_mask_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_mask_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_INFO_IRQS_MASK_CFG);  
//
    U_CSI_RX_STREAM_ERROR_IRQS  csi0_irqs_err_info;
    csi0_irqs_err_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_err_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_ERROR_IRQS);                 
//   
    U_CSI_RX_STREAM_ERROR_IRQS_MASK_CFG  csi0_irqs_err_mask_info;
    csi0_irqs_err_mask_info.udata = 0;
    isp_reg_writel(isp,csi0_irqs_err_mask_info.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM_ERROR_IRQS_MASK_CFG);              
//
    U_CSI_RX_DPHY_LANE_CONTROL  csi0_lane_ctl;
    csi0_lane_ctl.udata = 0;
    csi0_lane_ctl.bits.dl0_enable = cfg_info->csi0_dl0_enable;
    csi0_lane_ctl.bits.dl1_enable = cfg_info->csi0_dl1_enable;
    csi0_lane_ctl.bits.dl2_enable = cfg_info->csi0_dl2_enable;
    csi0_lane_ctl.bits.dl3_enable = cfg_info->csi0_dl3_enable;
    csi0_lane_ctl.bits.cl_enable  = cfg_info->csi0_cl_enable;
    csi0_lane_ctl.bits.dl0_reset  = cfg_info->csi0_dl0_reset;
    csi0_lane_ctl.bits.dl1_reset  = cfg_info->csi0_dl1_reset;
    csi0_lane_ctl.bits.dl2_reset  = cfg_info->csi0_dl2_reset;
    csi0_lane_ctl.bits.dl3_reset  = cfg_info->csi0_dl3_reset;
    csi0_lane_ctl.bits.cl_reset   = cfg_info->csi0_cl_reset;     
    isp_reg_writel(isp,csi0_lane_ctl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_DPHY_LANE_CONTROL);
//
    U_CSI_RX_DPHY_ERR_STATUS_IRQ  csi0_status_irq;
    csi0_status_irq.udata = 0;
    isp_reg_writel(isp,csi0_status_irq.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_DPHY_ERR_STATUS_IRQ);
//
    U_CSI_RX_DPHY_ERR_IRQ_MASK  csi0_status_mask_irq;
    csi0_status_mask_irq.udata = 0;
    isp_reg_writel(isp,csi0_status_mask_irq.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_DPHY_ERR_IRQ_MASK);
//stream 0
    U_CSI_RX_STREAM_CTRL  csi00_ctrl;
    csi00_ctrl.udata = 0;
    //csi00_ctrl.bits.start = cfg_info->csi00_start;   
    //csi00_ctrl.bits.stop = cfg_info->csi00_stop;    
    csi00_ctrl.bits.soft_rst= cfg_info->csi00_soft_rst; 
    isp_reg_writel(isp,csi00_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_CTRL);

    U_CSI_RX_STREAM_DATA_CFG  csi00_data_cfg;
    csi00_data_cfg.udata = 0;
    csi00_data_cfg.bits.datatype_select0 = cfg_info->csi00_datatype_select0;   
    csi00_data_cfg.bits.enable_dt0       = cfg_info->csi00_enable_dt0;
    csi00_data_cfg.bits.datatype_select1 = cfg_info->csi00_datatype_select1;    
    csi00_data_cfg.bits.enable_dt1       = cfg_info->csi00_enable_dt1;
    csi00_data_cfg.bits.vc_select        = cfg_info->csi00_vc_select;
    isp_reg_writel(isp,csi00_data_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_DATA_CFG);

    U_CSI_RX_STREAM_CFG  csi00_cfg;
    csi00_cfg.udata = 0;
    isp_reg_writel(isp,csi00_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_CFG);

    U_CSI_RX_STREAM_MONITOR_CTRL  csi00_mon_ctrl;
    csi00_mon_ctrl.udata = 0;
    isp_reg_writel(isp,csi00_mon_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_MONITOR_CTRL);

    U_CSI_RX_STREAM_TIMER  csi00_timer;
    csi00_timer.udata = 0;
    isp_reg_writel(isp,csi00_timer.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_TIMER);

    U_CSI_RX_STREAM_FCC_CFG  csi00_fcc_cfg;
    csi00_fcc_cfg.udata = 0;
    isp_reg_writel(isp,csi00_fcc_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_FCC_CFG);

    U_CSI_RX_STREAM_FCC_CTRL  csi00_fcc_ctrl;
    csi00_fcc_ctrl.udata = 0;
    isp_reg_writel(isp,csi00_fcc_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_FCC_CTRL);

    U_CSI_RX_STREAM_FCC_FILL_LVL csi00_fcc_fill_lvl;
    csi00_fcc_fill_lvl.udata = 0;
    isp_reg_writel(isp,csi00_fcc_fill_lvl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_FCC_FILL_LVL);

    csi00_ctrl.udata = 0;
    csi00_ctrl.bits.start = cfg_info->csi00_start; 
    isp_reg_writel(isp,csi00_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM0_CTRL);
//stream 1
    U_CSI_RX_STREAM_CTRL  csi01_ctrl;
    csi01_ctrl.udata = 0;
    //csi01_ctrl.bits.start = cfg_info->csi01_start;   
    //csi01_ctrl.bits.stop = cfg_info->csi01_stop;    
    csi01_ctrl.bits.soft_rst= cfg_info->csi01_soft_rst; 
    isp_reg_writel(isp,csi01_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_CTRL);

    U_CSI_RX_STREAM_DATA_CFG  csi01_data_cfg;
    csi01_data_cfg.udata = 0;
    csi01_data_cfg.bits.datatype_select0 = cfg_info->csi01_datatype_select0;   
    csi01_data_cfg.bits.enable_dt0       = cfg_info->csi01_enable_dt0;
    csi01_data_cfg.bits.datatype_select1 = cfg_info->csi01_datatype_select1;    
    csi01_data_cfg.bits.enable_dt1       = cfg_info->csi01_enable_dt1;
    csi01_data_cfg.bits.vc_select        = cfg_info->csi01_vc_select;
    isp_reg_writel(isp,csi01_data_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_DATA_CFG);

    U_CSI_RX_STREAM_CFG  csi01_cfg;
    csi01_cfg.udata = 0;
    isp_reg_writel(isp,csi01_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_CFG);

    U_CSI_RX_STREAM_MONITOR_CTRL  csi01_mon_ctrl;
    csi01_mon_ctrl.udata = 0;
    isp_reg_writel(isp,csi01_mon_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_MONITOR_CTRL);

    U_CSI_RX_STREAM_TIMER  csi01_timer;
    csi01_timer.udata = 0;
    isp_reg_writel(isp,csi01_timer.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_TIMER);

    U_CSI_RX_STREAM_FCC_CFG  csi01_fcc_cfg;
    csi01_fcc_cfg.udata = 0;
    isp_reg_writel(isp,csi01_fcc_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_FCC_CFG);

    U_CSI_RX_STREAM_FCC_CTRL  csi01_fcc_ctrl;
    csi01_fcc_ctrl.udata = 0;
    isp_reg_writel(isp,csi01_fcc_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_FCC_CTRL);

    U_CSI_RX_STREAM_FCC_FILL_LVL csi01_fcc_fill_lvl;
    csi01_fcc_fill_lvl.udata = 0;
    isp_reg_writel(isp,csi01_fcc_fill_lvl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_FCC_FILL_LVL);

    csi01_ctrl.udata = 0;
    csi01_ctrl.bits.start = cfg_info->csi01_start; 
    isp_reg_writel(isp,csi01_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM1_CTRL);
//stream 2
    U_CSI_RX_STREAM_CTRL  csi02_ctrl;
    csi02_ctrl.udata = 0;
    //csi02_ctrl.bits.start = cfg_info->csi02_start;   
    //csi02_ctrl.bits.stop = cfg_info->csi02_stop;    
    csi02_ctrl.bits.soft_rst= cfg_info->csi02_soft_rst; 
    isp_reg_writel(isp,csi02_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_CTRL);

    U_CSI_RX_STREAM_DATA_CFG  csi02_data_cfg;
    csi02_data_cfg.udata = 0;
    csi02_data_cfg.bits.datatype_select0 = cfg_info->csi02_datatype_select0;   
    csi02_data_cfg.bits.enable_dt0       = cfg_info->csi02_enable_dt0;
    csi02_data_cfg.bits.datatype_select1 = cfg_info->csi02_datatype_select1;    
    csi02_data_cfg.bits.enable_dt1       = cfg_info->csi02_enable_dt1;
    csi02_data_cfg.bits.vc_select        = cfg_info->csi02_vc_select;
    isp_reg_writel(isp,csi02_data_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_DATA_CFG);

    U_CSI_RX_STREAM_CFG  csi02_cfg;
    csi02_cfg.udata = 0;
    isp_reg_writel(isp,csi02_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_CFG);

    U_CSI_RX_STREAM_MONITOR_CTRL  csi02_mon_ctrl;
    csi02_mon_ctrl.udata = 0;
    isp_reg_writel(isp,csi02_mon_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_MONITOR_CTRL);

    U_CSI_RX_STREAM_TIMER  csi02_timer;
    csi02_timer.udata = 0;
    isp_reg_writel(isp,csi02_timer.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_TIMER);

    U_CSI_RX_STREAM_FCC_CFG  csi02_fcc_cfg;
    csi02_fcc_cfg.udata = 0;
    isp_reg_writel(isp,csi02_fcc_cfg.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_FCC_CFG);

    U_CSI_RX_STREAM_FCC_CTRL  csi02_fcc_ctrl;
    csi02_fcc_ctrl.udata = 0;
    isp_reg_writel(isp,csi02_fcc_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_FCC_CTRL);

    U_CSI_RX_STREAM_FCC_FILL_LVL csi02_fcc_fill_lvl;
    csi02_fcc_fill_lvl.udata = 0;
    isp_reg_writel(isp,csi02_fcc_fill_lvl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_FCC_FILL_LVL);

    csi02_ctrl.udata = 0;
    csi02_ctrl.bits.start = cfg_info->csi02_start; 
    isp_reg_writel(isp,csi02_ctrl.udata,ISP_IOMEM_CSI0_HOST,CSI_RX_STREAM2_CTRL); 

    //csi1
    U_CSI_RX_STREAM_SFT_RST csi1_sft_rst;
    csi1_sft_rst.udata = 0;
    csi1_sft_rst.bits.front = 1;
    csi1_sft_rst.bits.protocol = 1;
    isp_reg_writel(isp,csi1_sft_rst.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_SFT_RST);
//
    csi1_sft_rst.udata = 0;
    csi1_sft_rst.bits.front = 0;
    csi1_sft_rst.bits.protocol = 0;
    isp_reg_writel(isp,csi1_sft_rst.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_SFT_RST);
//
    U_CSI_RX_STREAM_STATIC_CFG csi1_static_cfg;
    csi1_static_cfg.udata = 0;    
    csi1_static_cfg.bits.lane_nb            = cfg_info->csi1_lane_nb;
    csi1_static_cfg.bits.sony_wdr           = cfg_info->csi1_sony_wdr;
    csi1_static_cfg.bits.dl0_map            = cfg_info->csi1_dl0_map;
    csi1_static_cfg.bits.dl1_map            = cfg_info->csi1_dl1_map;
    csi1_static_cfg.bits.dl2_map            = cfg_info->csi1_dl2_map;
    csi1_static_cfg.bits.dl3_map            = cfg_info->csi1_dl3_map;
    isp_reg_writel(isp,csi1_static_cfg.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_STATIC_CFG);
//
    U_CSI_RX_STREAM_ERR_BYPASS_CFG csi1_bypass_cfg;
    csi1_bypass_cfg.udata = 0;
    csi1_bypass_cfg.bits.crc = cfg_info->csi1_crc;    
    csi1_bypass_cfg.bits.ecc = cfg_info->csi1_ecc;    
    csi1_bypass_cfg.bits.data_id = cfg_info->csi1_ecc;  
    isp_reg_writel(isp,csi1_bypass_cfg.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_ERR_BYPASS_CFG);
//
    U_CSI_RX_STREAM_MONITOR_IRQS csi1_irqs_mon_info;
    csi1_irqs_mon_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_mon_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_MONITOR_IRQS);
//
    U_CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG  csi1_irqs_mon_mask_info;
    csi1_irqs_mon_mask_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_mon_mask_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG);          
//
    U_CSI_RX_STREAM_INFO_IRQS  csi1_irqs_info;
    csi1_irqs_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_INFO_IRQS); 
//
    U_CSI_RX_STREAM_INFO_IRQS_MASK_CFG  csi1_irqs_mask_info;
    csi1_irqs_mask_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_mask_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_INFO_IRQS_MASK_CFG);  
//
    U_CSI_RX_STREAM_ERROR_IRQS  csi1_irqs_err_info;
    csi1_irqs_err_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_err_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_ERROR_IRQS);                 
//   
    U_CSI_RX_STREAM_ERROR_IRQS_MASK_CFG  csi1_irqs_err_mask_info;
    csi1_irqs_err_mask_info.udata = 0;
    isp_reg_writel(isp,csi1_irqs_err_mask_info.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM_ERROR_IRQS_MASK_CFG);              
//
    U_CSI_RX_DPHY_LANE_CONTROL  csi1_lane_ctl;
    csi1_lane_ctl.udata = 0;
    csi1_lane_ctl.bits.dl0_enable = cfg_info->csi1_dl0_enable;
    csi1_lane_ctl.bits.dl1_enable = cfg_info->csi1_dl1_enable;
    csi1_lane_ctl.bits.dl2_enable = cfg_info->csi1_dl2_enable;
    csi1_lane_ctl.bits.dl3_enable = cfg_info->csi1_dl3_enable;
    csi1_lane_ctl.bits.cl_enable  = cfg_info->csi1_cl_enable;
    csi1_lane_ctl.bits.dl0_reset  = cfg_info->csi1_dl0_reset;
    csi1_lane_ctl.bits.dl1_reset  = cfg_info->csi1_dl1_reset;
    csi1_lane_ctl.bits.dl2_reset  = cfg_info->csi1_dl2_reset;
    csi1_lane_ctl.bits.dl3_reset  = cfg_info->csi1_dl3_reset;
    csi1_lane_ctl.bits.cl_reset   = cfg_info->csi1_cl_reset;     
    isp_reg_writel(isp,csi1_lane_ctl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_DPHY_LANE_CONTROL);
//
    U_CSI_RX_DPHY_ERR_STATUS_IRQ  csi1_status_irq;
    csi1_status_irq.udata = 0;
    isp_reg_writel(isp,csi1_status_irq.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_DPHY_ERR_STATUS_IRQ);
//
    U_CSI_RX_DPHY_ERR_IRQ_MASK  csi1_status_mask_irq;
    csi1_status_mask_irq.udata = 0;
    isp_reg_writel(isp,csi1_status_mask_irq.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_DPHY_ERR_IRQ_MASK);
//stream 0
    U_CSI_RX_STREAM_CTRL  csi10_ctrl;
    csi10_ctrl.udata = 0;
    //csi10_ctrl.bits.start = cfg_info->csi10_start;   
    //csi10_ctrl.bits.stop = cfg_info->csi10_stop;    
    csi10_ctrl.bits.soft_rst= cfg_info->csi10_soft_rst; 
    isp_reg_writel(isp,csi10_ctrl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_CTRL);

    U_CSI_RX_STREAM_DATA_CFG  csi10_data_cfg;
    csi10_data_cfg.udata = 0;
    csi10_data_cfg.bits.datatype_select0 = cfg_info->csi10_datatype_select0;   
    csi10_data_cfg.bits.enable_dt0       = cfg_info->csi10_enable_dt0;
    csi10_data_cfg.bits.datatype_select1 = cfg_info->csi10_datatype_select1;    
    csi10_data_cfg.bits.enable_dt1       = cfg_info->csi10_enable_dt1;
    csi10_data_cfg.bits.vc_select        = cfg_info->csi10_vc_select;
    isp_reg_writel(isp,csi10_data_cfg.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_DATA_CFG);

    U_CSI_RX_STREAM_CFG  csi10_cfg;
    csi10_cfg.udata = 0;
    isp_reg_writel(isp,csi10_cfg.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_CFG);

    U_CSI_RX_STREAM_MONITOR_CTRL  csi10_mon_ctrl;
    csi10_mon_ctrl.udata = 0;
    isp_reg_writel(isp,csi10_mon_ctrl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_MONITOR_CTRL);

    U_CSI_RX_STREAM_TIMER  csi10_timer;
    csi10_timer.udata = 0;
    isp_reg_writel(isp,csi10_timer.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_TIMER);

    U_CSI_RX_STREAM_FCC_CFG  csi10_fcc_cfg;
    csi10_fcc_cfg.udata = 0;
    isp_reg_writel(isp,csi10_fcc_cfg.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_FCC_CFG);

    U_CSI_RX_STREAM_FCC_CTRL  csi10_fcc_ctrl;
    csi10_fcc_ctrl.udata = 0;
    isp_reg_writel(isp,csi10_fcc_ctrl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_FCC_CTRL);

    U_CSI_RX_STREAM_FCC_FILL_LVL csi10_fcc_fill_lvl;
    csi10_fcc_fill_lvl.udata = 0;
    isp_reg_writel(isp,csi10_fcc_fill_lvl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_FCC_FILL_LVL);

    csi10_ctrl.udata = 0;
    csi10_ctrl.bits.start = cfg_info->csi10_start; 
    isp_reg_writel(isp,csi10_ctrl.udata,ISP_IOMEM_CSI1_HOST,CSI_RX_STREAM0_CTRL);        
 
    return;
}