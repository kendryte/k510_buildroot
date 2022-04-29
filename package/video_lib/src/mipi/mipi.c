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
  File Name     : mipi.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include<string.h>

#include "mipi.h"
#include "isp_com.h"
#include "mipi/csi/mipi_csi_drv.h"

extern struct mipi_csi_cfg_info mipi_2x2lane12_34_raw12_cfg_info;
extern struct mipi_csi_cfg_info mipi_2x2lane12_34_raw10_cfg_info;
/**************************************************************************
 * 
 ***************************************************************************/

void printf_csi_cfg(struct mipi_csi_cfg_info *cfg_info)
{
    ISP_CHECK_POINTER(cfg_info);
    printf("sony_wdr:0x%x\n",cfg_info->csi0_sony_wdr);
    printf("lane_nb:0x%x\n",cfg_info->csi0_lane_nb);
    printf("dl0_map:0x%x\n",cfg_info->csi0_dl0_map);
    printf("dl1_map:0x%x\n",cfg_info->csi0_dl1_map);
    printf("dl2_map:0x%x\n",cfg_info->csi0_dl2_map);
    printf("dl3_map:0x%x\n",cfg_info->csi0_dl3_map);
    printf("crc:0x%x\n",cfg_info->csi0_crc);    
    printf("ecc:0x%x\n",cfg_info->csi0_ecc);    
    printf("data_id:0x%x\n",cfg_info->csi0_data_id);
    printf("0xdl0_enable:%x\n",cfg_info->csi0_dl0_enable);
    printf("0xdl1_enable:%x\n",cfg_info->csi0_dl1_enable);
    printf("0xdl2_enable:%x\n",cfg_info->csi0_dl2_enable);
    printf("0xdl3_enable:%x\n",cfg_info->csi0_dl3_enable);
    printf("cl_enable:0x%x\n",cfg_info->csi0_cl_enable  );
    printf("dl0_reset:0x%x\n",cfg_info->csi0_dl0_reset );
    printf("dl1_reset:0x%x\n",cfg_info->csi0_dl1_reset );
    printf("dl2_reset:0x%x\n",cfg_info->csi0_dl2_reset );
    printf("dl3_reset:0x%x\n",cfg_info->csi0_dl3_reset );
    printf("cl_reset :0x%x\n",cfg_info->csi0_cl_reset  ); 
    printf("csi00_start:0x%x\n",cfg_info->csi00_start);    
    printf("csi00_stop:0x%x\n",cfg_info->csi00_stop);     
    printf("csi00_abort:0x%x\n",cfg_info->csi00_abort);    
    printf("csi00_soft_rst:0x%x\n",cfg_info->csi00_soft_rst); 
    printf("csi00_datatype_select0:0x%x\n",cfg_info->csi00_datatype_select0);
    printf("csi00_enable_dt0:0x%x\n",cfg_info->csi00_enable_dt0      );
    printf("csi00_datatype_select1:0x%x\n",cfg_info->csi00_datatype_select1);
    printf("csi00_enable_dt1:0x%x\n",cfg_info->csi00_enable_dt1      );
    printf("csi00_vc_select:0x%x\n",cfg_info->csi00_vc_select       );
    printf("csi01_start:0x%x\n",cfg_info->csi01_start);    
    printf("csi01_stop:0x%x\n",cfg_info->csi01_stop);     
    printf("csi01_abort:0x%x\n",cfg_info->csi01_abort);    
    printf("csi01_soft_rst:0x%x\n",cfg_info->csi01_soft_rst);
    printf("csi01_datatype_select0:0x%x\n",cfg_info->csi01_datatype_select0);
    printf("csi01_enable_dt0:0x%x\n",cfg_info->csi01_enable_dt0      );
    printf("csi01_datatype_select1:0x%x\n",cfg_info->csi01_datatype_select1);
    printf("csi01_enable_dt1:0x%x\n",cfg_info->csi01_enable_dt1      );
    printf("csi01_vc_select:0x%x\n",cfg_info->csi01_vc_select       );
    printf("csi02_start:0x%x\n",cfg_info->csi02_start);    
    printf("csi02_stop:0x%x\n",cfg_info->csi02_stop);     
    printf("csi02_abort:0x%x\n",cfg_info->csi02_abort);    
    printf("csi02_soft_rst:0x%x\n",cfg_info->csi02_soft_rst);
    printf("csi02_datatype_select0:0x%x\n",cfg_info->csi02_datatype_select0);
    printf("csi02_enable_dt0:0x%x\n",cfg_info->csi02_enable_dt0      );
    printf("csi02_datatype_select1:0x%x\n",cfg_info->csi02_datatype_select1);
    printf("csi02_enable_dt1:0x%x\n",cfg_info->csi02_enable_dt1      );
    printf("csi02_vc_select:0x%x\n",cfg_info->csi02_vc_select       );
    printf("csi1_sony_wdr:0x%x\n",cfg_info->csi1_sony_wdr);
    printf("csi1_lane_nb:0x%x\n",cfg_info->csi1_lane_nb);
    printf("csi1_dl0_map:0x%x\n",cfg_info->csi1_dl0_map);
    printf("csi1_dl1_map:0x%x\n",cfg_info->csi1_dl1_map);
    printf("csi1_dl2_map:0x%x\n",cfg_info->csi1_dl2_map);
    printf("csi1_dl3_map:0x%x\n",cfg_info->csi1_dl3_map);
    printf("csi1_crc:0x%x\n",cfg_info->csi1_crc);    
    printf("csi1_ecc:0x%x\n",cfg_info->csi1_ecc);    
    printf("csi1_data_id:0x%x\n",cfg_info->csi1_data_id);
    printf("csi1_dl0_enable:0x%x\n",cfg_info->csi1_dl0_enable);
    printf("csi1_dl1_enable:0x%x\n",cfg_info->csi1_dl1_enable);
    printf("csi1_dl2_enable:0x%x\n",cfg_info->csi1_dl2_enable);
    printf("csi1_dl3_enable:0x%x\n",cfg_info->csi1_dl3_enable);
    printf("csi1_cl_enable:0x%x\n",cfg_info->csi1_cl_enable);
    printf("csi1_dl0_reset:0x%x\n",cfg_info->csi1_dl0_reset);
    printf("csi1_dl1_reset:0x%x\n",cfg_info->csi1_dl1_reset);
    printf("csi1_dl2_reset:0x%x\n",cfg_info->csi1_dl2_reset);
    printf("csi1_dl3_reset:0x%x\n",cfg_info->csi1_dl3_reset);
    printf("csi1_cl_reset :0x%x\n",cfg_info->csi1_cl_reset ); 
    printf("csi10_start:0x%x\n",cfg_info->csi10_start);    
    printf("csi10_stop:0x%x\n",cfg_info->csi10_stop);     
    printf("csi10_abort:0x%x\n",cfg_info->csi10_abort);    
    printf("csi10_soft_rst:0x%x\n",cfg_info->csi10_soft_rst);
    printf("csi10_datatype_select0:0x%x\n",cfg_info->csi10_datatype_select0);
    printf("csi10_enable_dt0:0x%x\n",cfg_info->csi10_enable_dt0      );
    printf("csi10_datatype_select1:0x%x\n",cfg_info->csi10_datatype_select1);
    printf("csi10_enable_dt1:0x%x\n",cfg_info->csi10_enable_dt1      );
    printf("csi10_vc_select:0x%x\n",cfg_info->csi10_vc_select       );
    return;
}
/*
*
*/
void mipi_csi_2lane_init(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    struct mipi_csi_cfg_info cfg_info;
    printf("mipi_csi_2lane_init start!\n");
    memcpy((void*)&cfg_info,(void*)&mipi_2x2lane12_34_raw12_cfg_info,sizeof(struct mipi_csi_cfg_info));
    Mipi_Csi_Drv_SetCfg(isp,&cfg_info);
    return;
}
/*
*
*/
void mipi_csi_2lane_raw10_init(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    struct mipi_csi_cfg_info cfg_info;
    printf("mipi_csi_2lane_init start!\n");
    memcpy((void*)&cfg_info,(void*)&mipi_2x2lane12_34_raw10_cfg_info,sizeof(struct mipi_csi_cfg_info));
    Mipi_Csi_Drv_SetCfg(isp,&cfg_info);
    return;
}
/*
*
*/
void mipi_csi_init(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    struct isp_mipi_device *mipi = &isp->isp_mipi;
    struct mipi_csi_cfg_info *cfg_info = &mipi->csi_info;
    Mipi_Csi_Drv_SetCfg(isp,cfg_info);
    return;
}