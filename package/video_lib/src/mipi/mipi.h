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
  File Name     : mipi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _DEF_MIPI_H_
#define _DEF_MIPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#define  Dl0_MAP    (0x1)
#define  Dl1_MAP    (0x2)
#define  Dl2_MAP    (0x3)
#define  Dl3_MAP    (0x4)

#define  MIPI_YUV422 (0x1E)
#define  MIPI_RAW8   (0x2A)
#define  MIPI_RAW10  (0x2B)
#define  MIPI_RAW12  (0x2C)

struct isp_dvice;
struct mipi_csi_cfg_info
{
    unsigned int    csi0_sony_wdr;
    unsigned int    csi0_lane_nb;
    unsigned int    csi0_dl0_map;
    unsigned int    csi0_dl1_map;
    unsigned int    csi0_dl2_map;
    unsigned int    csi0_dl3_map;
//
    unsigned int    csi0_crc;    
    unsigned int    csi0_ecc;    
    unsigned int    csi0_data_id;
//
    unsigned int    csi0_dl0_enable;
    unsigned int    csi0_dl1_enable;
    unsigned int    csi0_dl2_enable;
    unsigned int    csi0_dl3_enable;
    unsigned int    csi0_cl_enable  ;
    unsigned int    csi0_dl0_reset ;
    unsigned int    csi0_dl1_reset ;
    unsigned int    csi0_dl2_reset ;
    unsigned int    csi0_dl3_reset ;
    unsigned int    csi0_cl_reset  ; 
//
    unsigned int    csi00_start;    
    unsigned int    csi00_stop;     
    unsigned int    csi00_abort;    
    unsigned int    csi00_soft_rst; 
    unsigned int    csi00_datatype_select0;     
    unsigned int    csi00_enable_dt0      ;
    unsigned int    csi00_datatype_select1;   
    unsigned int    csi00_enable_dt1      ;
    unsigned int    csi00_vc_select       ;
//
    unsigned int    csi01_start;    
    unsigned int    csi01_stop;     
    unsigned int    csi01_abort;    
    unsigned int    csi01_soft_rst;
    unsigned int    csi01_datatype_select0;     
    unsigned int    csi01_enable_dt0      ;
    unsigned int    csi01_datatype_select1;   
    unsigned int    csi01_enable_dt1      ;
    unsigned int    csi01_vc_select       ; 
//
    unsigned int    csi02_start;    
    unsigned int    csi02_stop;     
    unsigned int    csi02_abort;    
    unsigned int    csi02_soft_rst;
    unsigned int    csi02_datatype_select0;     
    unsigned int    csi02_enable_dt0      ;
    unsigned int    csi02_datatype_select1;   
    unsigned int    csi02_enable_dt1      ;
    unsigned int    csi02_vc_select       ;
//
    unsigned int    csi1_sony_wdr;
    unsigned int    csi1_lane_nb;
    unsigned int    csi1_dl0_map;
    unsigned int    csi1_dl1_map;
    unsigned int    csi1_dl2_map;
    unsigned int    csi1_dl3_map;
//
    unsigned int    csi1_crc;    
    unsigned int    csi1_ecc;    
    unsigned int    csi1_data_id;
//
    unsigned int    csi1_dl0_enable;
    unsigned int    csi1_dl1_enable;
    unsigned int    csi1_dl2_enable;
    unsigned int    csi1_dl3_enable;
    unsigned int    csi1_cl_enable  ;
    unsigned int    csi1_dl0_reset ;
    unsigned int    csi1_dl1_reset ;
    unsigned int    csi1_dl2_reset ;
    unsigned int    csi1_dl3_reset ;
    unsigned int    csi1_cl_reset  ; 
//
    unsigned int    csi10_start;    
    unsigned int    csi10_stop;     
    unsigned int    csi10_abort;    
    unsigned int    csi10_soft_rst;
    unsigned int    csi10_datatype_select0;     
    unsigned int    csi10_enable_dt0      ;
    unsigned int    csi10_datatype_select1;   
    unsigned int    csi10_enable_dt1      ;
    unsigned int    csi10_vc_select       ;    
};

struct  isp_mipi_device{
    struct isp_device *isp;
    struct mipi_csi_cfg_info csi_info;
};
//
void mipi_csi_2lane_init(struct isp_device *isp);
void mipi_csi_init(struct isp_device *isp);
void mipi_csi_2lane_raw10_init(struct isp_device *isp);
//
void aml550_power_on_seq(void);
void aml550_22v_power_en(void);
#ifdef __cplusplus
}
#endif
#endif/*_DEF_MIPI_H_*/