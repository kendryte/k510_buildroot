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
  File Name     : common_params.c
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
#include "vi/vi_com.h"
#include "mipi/mipi.h"
#include "vo/vo.h"
/**
 * @brief 
 * 
 */
struct mipi_csi_cfg_info mipi_2x2lane12_34_raw12_cfg_info =
{
    0,//sony_wdr;
    2,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    0,//dl2_enable;
    0,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    0,//dl2_reset ;
    0,//dl3_reset ;
    1,//cl_reset  ; 
    1,//csi00_start;    
    0,//csi00_stop;     
    0,//csi00_abort;    
    1,//csi00_soft_rst; 
    MIPI_RAW12,//csi00_datatype_select0;
    1,//csi00_enable_dt0      ;
    MIPI_RAW8,//csi00_datatype_select1;
    0,//csi00_enable_dt1      ;
    1,//csi00_vc_select       ;
    1,//csi01_start;    
    0,//csi01_stop;     
    0,//csi01_abort;    
    1,//csi01_soft_rst;
    MIPI_RAW12,//csi01_datatype_select0;
    1,//csi01_enable_dt0      ;
    MIPI_RAW8,//csi01_datatype_select1;
    0,//csi01_enable_dt1      ;
    2,//csi01_vc_select       ;
    1,//csi02_start;    
    0,//csi02_stop;     
    0,//csi02_abort;    
    1,//csi02_soft_rst;
    MIPI_RAW12,//csi02_datatype_select0;
    1,//csi02_enable_dt0      ;
    MIPI_RAW8,//csi02_datatype_select1;
    0,//csi02_enable_dt1      ;
    4,//csi02_vc_select       ;
    //
    0,//sony_wdr;
    2,//lane_nb;
    Dl2_MAP,//dl0_map;
    Dl3_MAP,//dl1_map;
    Dl0_MAP,//dl2_map;
    Dl1_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    0,//dl0_enable;
    0,//dl1_enable;
    1,//dl2_enable;
    1,//dl3_enable;
    1,//cl_enable  ;
    0,//dl0_reset ;
    0,//dl1_reset ;
    1,//dl2_reset ;
    1,//dl3_reset ;
    1,//cl_reset  ; 
    1, //csi10_start;    
    0, //csi10_stop;     
    0, //csi10_abort;    
    1, //csi10_soft_rst;
    MIPI_RAW12,//csi10_datatype_select0;
    1,//csi10_enable_dt0      ;
    MIPI_RAW8,//csi10_datatype_select1;
    0,//csi10_enable_dt1      ;
    1,//csi10_vc_select       ;
};
//
struct mipi_csi_cfg_info mipi_4lane_raw12_cfg_info =
{
    0,//sony_wdr;
    4,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    1,//dl2_enable;
    1,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    1,//dl2_reset ;
    1,//dl3_reset ;
    1,//cl_reset  ; 
    1,//csi00_start;    
    0,//csi00_stop;     
    0,//csi00_abort;    
    1,//csi00_soft_rst; 
    MIPI_RAW12,//csi00_datatype_select0;
    1,//csi00_enable_dt0      ;
    MIPI_RAW8,//csi00_datatype_select1;
    0,//csi00_enable_dt1      ;
    1,//csi00_vc_select       ;
    1,//csi01_start;    
    0,//csi01_stop;     
    0,//csi01_abort;    
    1,//csi01_soft_rst;
    MIPI_RAW12,//csi01_datatype_select0;
    1,//csi01_enable_dt0      ;
    MIPI_RAW8,//csi01_datatype_select1;
    0,//csi01_enable_dt1      ;
    2,//csi01_vc_select       ;
    1,//csi02_start;    
    0,//csi02_stop;     
    0,//csi02_abort;    
    1,//csi02_soft_rst;
    MIPI_RAW12,//csi02_datatype_select0;
    1,//csi02_enable_dt0      ;
    MIPI_RAW8,//csi02_datatype_select1;
    0,//csi02_enable_dt1      ;
    4,//csi02_vc_select       ;
    //
    0,//sony_wdr;
    2,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    0,//dl2_enable;
    0,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    0,//dl2_reset ;
    0,//dl3_reset ;
    1,//cl_reset  ; 
    0, //csi10_start;    
    0, //csi10_stop;     
    0, //csi10_abort;    
    1, //csi10_soft_rst;
    MIPI_RAW12,//csi10_datatype_select0;
    1,//csi10_enable_dt0      ;
    MIPI_RAW8,//csi10_datatype_select1;
    0,//csi10_enable_dt1      ;
    1,//csi10_vc_select       ;
};
/*
*
*/
struct mipi_csi_cfg_info mipi_2x2lane12_34_raw10_cfg_info =
{
    0,//sony_wdr;
    2,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    0,//dl2_enable;
    0,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    0,//dl2_reset ;
    0,//dl3_reset ;
    1,//cl_reset  ; 
    1,//csi00_start;    
    0,//csi00_stop;     
    0,//csi00_abort;    
    1,//csi00_soft_rst; 
    MIPI_RAW10,//csi00_datatype_select0;
    1,//csi00_enable_dt0      ;
    MIPI_RAW8,//csi00_datatype_select1;
    0,//csi00_enable_dt1      ;
    1,//csi00_vc_select       ;
    1,//csi01_start;    
    0,//csi01_stop;     
    0,//csi01_abort;    
    1,//csi01_soft_rst;
    MIPI_RAW10,//csi01_datatype_select0;
    1,//csi01_enable_dt0      ;
    MIPI_RAW8,//csi01_datatype_select1;
    0,//csi01_enable_dt1      ;
    2,//csi01_vc_select       ;
    1,//csi02_start;    
    0,//csi02_stop;     
    0,//csi02_abort;    
    1,//csi02_soft_rst;
    MIPI_RAW10,//csi02_datatype_select0;
    1,//csi02_enable_dt0      ;
    MIPI_RAW8,//csi02_datatype_select1;
    0,//csi02_enable_dt1      ;
    4,//csi02_vc_select       ;
    //
    0,//sony_wdr;
    2,//lane_nb;
    Dl2_MAP,//dl0_map;
    Dl3_MAP,//dl1_map;
    Dl0_MAP,//dl2_map;
    Dl1_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    0,//dl0_enable;
    0,//dl1_enable;
    1,//dl2_enable;
    1,//dl3_enable;
    1,//cl_enable  ;
    0,//dl0_reset ;
    0,//dl1_reset ;
    1,//dl2_reset ;
    1,//dl3_reset ;
    1,//cl_reset  ; 
    1, //csi10_start;    
    0, //csi10_stop;     
    0, //csi10_abort;    
    1, //csi10_soft_rst;
    MIPI_RAW10,//csi10_datatype_select0;
    1,//csi10_enable_dt0      ;
    MIPI_RAW8,//csi10_datatype_select1;
    0,//csi10_enable_dt1      ;
    1,//csi10_vc_select       ;
};
//
struct mipi_csi_cfg_info mipi_4lane_raw10_cfg_info =
{
    0,//sony_wdr;
    4,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    1,//dl2_enable;
    1,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    1,//dl2_reset ;
    1,//dl3_reset ;
    1,//cl_reset  ; 
    1,//csi00_start;    
    0,//csi00_stop;     
    0,//csi00_abort;    
    1,//csi00_soft_rst; 
    MIPI_RAW10,//csi00_datatype_select0;
    1,//csi00_enable_dt0      ;
    MIPI_RAW8,//csi00_datatype_select1;
    0,//csi00_enable_dt1      ;
    1,//csi00_vc_select       ;
    1,//csi01_start;    
    0,//csi01_stop;     
    0,//csi01_abort;    
    1,//csi01_soft_rst;
    MIPI_RAW10,//csi01_datatype_select0;
    1,//csi01_enable_dt0      ;
    MIPI_RAW8,//csi01_datatype_select1;
    0,//csi01_enable_dt1      ;
    2,//csi01_vc_select       ;
    1,//csi02_start;    
    0,//csi02_stop;     
    0,//csi02_abort;    
    1,//csi02_soft_rst;
    MIPI_RAW10,//csi02_datatype_select0;
    1,//csi02_enable_dt0      ;
    MIPI_RAW8,//csi02_datatype_select1;
    0,//csi02_enable_dt1      ;
    4,//csi02_vc_select       ;
    //
    0,//sony_wdr;
    2,//lane_nb;
    Dl0_MAP,//dl0_map;
    Dl1_MAP,//dl1_map;
    Dl2_MAP,//dl2_map;
    Dl3_MAP,//dl3_map;
    1,//crc;    
    1,//ecc;    
    1,//data_id;
    1,//dl0_enable;
    1,//dl1_enable;
    0,//dl2_enable;
    0,//dl3_enable;
    1,//cl_enable  ;
    1,//dl0_reset ;
    1,//dl1_reset ;
    0,//dl2_reset ;
    0,//dl3_reset ;
    1,//cl_reset  ; 
    0, //csi10_start;    
    0, //csi10_stop;     
    0, //csi10_abort;    
    1, //csi10_soft_rst;
    MIPI_RAW10,//csi10_datatype_select0;
    1,//csi10_enable_dt0      ;
    MIPI_RAW8,//csi10_datatype_select1;
    0,//csi10_enable_dt1      ;
    1,//csi10_vc_select       ;
};
/*
/**
 * @brief 
 * 
 */
struct _VO_CORE_INFO_S dsi_vo_info =
{
    {
        1,//dispEnable;
        0x2e,//xZoneCtl_start;
        0x465,//xZoneCtl_stop;
        0xe,//yZoneCtl_start;
        0x78d,//yZoneCtl_stop;
        0x5,//dispHsyncCtl_start;
        0x25,//dispHsyncCtl_stop;
        0x1,//dispHsync1Ctl_start;
        0x5,//dispHsync1Ctl_stop;
        0x1,//dispVsync1Ctl_start;
        0x1,//dispVsync1Ctl_stop;
        0x1,//dispHsync2Ctl_start;
        0x5,//dispHsync2Ctl_stop;
        0x1,//dispVsync2Ctl_start;
        0x1,//dispVsync2Ctl_stop; 
        0,//vcntbit0    ;
        3,//secndfoffset;
        8,//framesyncdly;
        0x53c,//hsize;
        0x7a6,//vsize;    
    },//dispInfo;
    {
        0,//layer0DispEn;
        0,//layer0En; 
        0x7,//scalerBlen;
        //
        {
            0,//datmode ;
            0,//endiany ;
            0,//endianuv;
            0,//swi;            
        },//datModeInfo
        //
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo;
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo
        {
            0,//v_pstep;
            0,//v_dstep;
            0,//v_pstep_st;
            0,//h_pstep;
            0,//h_dstep;
            0,//h_pstep_st;
        },//scaleInfo
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
            0,//out_hsize;
            0,//out_vsize;
        },//sizeInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;
        {
            0,//mfbd_en;
            0,//y_addr0;
            0,//y_addr1;
            0,//y_stride0;	
            0,//y_stride1;
            0,//y_head_addr0;
            0,//y_head_addr1;
            0,//y_head_stride0;
            0,//y_head_stride1;
            0,//uv_addr0;
            0,//uv_addr1;
            0,//uv_stride0;
            0,//uv_stride1; 
            0,//uv_head_addr0;
            0,//uv_head_addr1;
            0,//uv_head_stride0;
            0,//uv_head_stride1;
        },//mfbdInfo
    },//layer0Info;
    {
        0,//layer1DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer1Info;
    {
        0,//layer2DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer2Info;
    {
        0,//layer3DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer3Info;
    {
        0,//osdLayer4DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd0Info;
    {
        0,//osdLayer5DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd1Info;
    {
        0,//osdLayer6DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd2Info;
    {
        0x00000132,//osdrgb2yuv_coeff[0][0]
        0x00000259,//osdrgb2yuv_coeff[0][1]
        0x00000075,//osdrgb2yuv_coeff[0][2]
        0x00000000,//osdrgb2yuv_coeff[0][3]
        0x00000f50,//osdrgb2yuv_coeff[1][0]
        0x00000ea5,//osdrgb2yuv_coeff[1][1]
        0x0000020b,//osdrgb2yuv_coeff[1][2]
        0x00000080,//osdrgb2yuv_coeff[1][3]
        0x0000020b,//osdrgb2yuv_coeff[2][0]
        0x00000e4a,//osdrgb2yuv_coeff[2][1]
        0x00000fab,//osdrgb2yuv_coeff[2][2]
        0x00000080,//osdrgb2yuv_coeff[2][3]
    },//osdRgb2YuvInfo osdrgb2yuv_coeff[3][4];;
    {
        1,//yuv2rgb_ctl_en;
        0x00000400,//yuv2rgb_coeff[0][0];
        0x00000000,//yuv2rgb_coeff[0][1];
        0x000005a1,//yuv2rgb_coeff[0][2];
        0x00000f4c,//yuv2rgb_coeff[0][3];
        0x00000400,//yuv2rgb_coeff[1][0];
        0x00000e9e,//yuv2rgb_coeff[1][1];
        0x00000d22,//yuv2rgb_coeff[1][2];
        0x00000088,//yuv2rgb_coeff[1][3];
        0x00000400,//yuv2rgb_coeff[2][0];
        0x0000071e,//yuv2rgb_coeff[2][1];
        0x00000000,//yuv2rgb_coeff[2][2];
        0x00000f1c,//yuv2rgb_coeff[2][3];
    },//yuv2rgbInfo;  
    {
        {
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_0,//sel;
            },//layer0
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_1,//sel;
            },//layer1
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_2,//sel;
            },//layer2
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_3,//sel;
            },//layer3
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_0,//sel;
            },//layer4osd0
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_1,//sel;
            },//layer4osd1
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_2,//sel;
            },//layer4osd2
        },
        {
            0x00,//0x80,//y;
            0x80,//u;
            0x80,//v;
        },
    },//dispMixCtlInfo;
    1,//ditherctlen;
    0,//clutctlen;
};
/*
*
*/
struct _VO_CORE_INFO_S hdmi_vo_info =
{
    {
        1,//dispEnable;
        0xc6,//xZoneCtl_start;
        0x845,//xZoneCtl_stop;
        0x2a,//yZoneCtl_start;
        0x461,//yZoneCtl_stop;
        0x6,//dispHsyncCtl_start;
        0x32,//dispHsyncCtl_stop;
        0x6,//dispHsync1Ctl_start;
        0x6,//dispHsync1Ctl_stop;
        0x1,//dispVsync1Ctl_start;
        0x6,//dispVsync1Ctl_stop;
        0x6,//dispHsync2Ctl_start;
        0x6,//dispHsync2Ctl_stop;
        0x1,//dispVsync2Ctl_start;
        0x6,//dispVsync2Ctl_stop; 
        0,//vcntbit0    ;
        3,//secndfoffset;
        8,//framesyncdly;
        0x898,//hsize;
        0x465,//vsize;    
    },//dispInfo;
    {
        0,//layer0DispEn;
        0,//layer0En; 
        0x7,//scalerBlen;
        //
        {
            0,//datmode ;
            0,//endiany ;
            0,//endianuv;
            0,//swi;            
        },//datModeInfo
        //
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo;
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo
        {
            0,//v_pstep;
            0,//v_dstep;
            0,//v_pstep_st;
            0,//h_pstep;
            0,//h_dstep;
            0,//h_pstep_st;
        },//scaleInfo
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
            0,//out_hsize;
            0,//out_vsize;
        },//sizeInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;
        {
            0,//mfbd_en;
            0,//y_addr0;
            0,//y_addr1;
            0,//y_stride0;	
            0,//y_stride1;
            0,//y_head_addr0;
            0,//y_head_addr1;
            0,//y_head_stride0;
            0,//y_head_stride1;
            0,//uv_addr0;
            0,//uv_addr1;
            0,//uv_stride0;
            0,//uv_stride1; 
            0,//uv_head_addr0;
            0,//uv_head_addr1;
            0,//uv_head_stride0;
            0,//uv_head_stride1;
        },//mfbdInfo
    },//layer0Info;
    {
        0,//layer1DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer1Info;
    {
        0,//layer2DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer2Info;
    {
        0,//layer3DispEn;
        {
            0,//enable   ;
            0,//yuv422en ;
            0,//yuv420en ;
            0,//endiany  ;
            0,//endianuv ;
            0,//uvswap   ;
        },//layerInfo;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//areaInfo
        {
            0,//yAddr0;
            0,//yAddr1;
            0,//uvAddr0;   
            0,//uvAddr1;
            0,//hsize_stride;
            0,//vsize_stride;
        },//bufInfo;
        {
            0,//offset_hsize;
            0,//offset_vsize;
            0,//in_hsize;
            0,//in_vsize;
        },//layer1SizeInfo      
        {
            0xf,//blen   ;
            0x0,//voffset;
        },//imgInBlenthInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },// baseModeInfo;    
    },//layer3Info;
    {
        0,//osdLayer4DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd0Info;
    {
        0,//osdLayer5DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd1Info;
    {
        0,//osdLayer6DispEn;
        0,//osdrgb2yuvEn;
        0,//osdtype  ;
        0,//alphatpye;
        {
            0,//xCtl_start;
            0,//xCtl_stop;
            0,//yCtl_start;
            0,//yCtl_stop;
        },//osd0AreaInfo;
        {
            0,//width;
            0,//height;
        },//osd0SizeInfo;
        {
            0,//alp_addr0;
            0,//alp_addr1;
            0,//alpstride;
            0,//vlu_addr0;
            0,//vlu_addr1;
            0,//osdstride;
        },//osd0BufInfo;
        {
            1,//mode;
            1,//base0mask;
            0,//base1mask;
            0,//addrflag ;
        },//osd0BaseModeInfo;
        {
            0xf,//dmarequestlen;
            OSD_ORIGINAL_ORDER,//dmamap       ;
            OSD_RGB_REV_R,//rgbrev       ;
        },// osd0DmaInfo 
    },//osd2Info;
    {
        0x00000132,//osdrgb2yuv_coeff[0][0]
        0x00000259,//osdrgb2yuv_coeff[0][1]
        0x00000075,//osdrgb2yuv_coeff[0][2]
        0x00000000,//osdrgb2yuv_coeff[0][3]
        0x00000f50,//osdrgb2yuv_coeff[1][0]
        0x00000ea5,//osdrgb2yuv_coeff[1][1]
        0x0000020b,//osdrgb2yuv_coeff[1][2]
        0x00000080,//osdrgb2yuv_coeff[1][3]
        0x0000020b,//osdrgb2yuv_coeff[2][0]
        0x00000e4a,//osdrgb2yuv_coeff[2][1]
        0x00000fab,//osdrgb2yuv_coeff[2][2]
        0x00000080,//osdrgb2yuv_coeff[2][3]
    },//osdRgb2YuvInfo osdrgb2yuv_coeff[3][4];;
    {
        1,//yuv2rgb_ctl_en;
        0x00000400,//yuv2rgb_coeff[0][0];
        0x00000000,//yuv2rgb_coeff[0][1];
        0x000005a1,//yuv2rgb_coeff[0][2];
        0x00000f4c,//yuv2rgb_coeff[0][3];
        0x00000400,//yuv2rgb_coeff[1][0];
        0x00000e9e,//yuv2rgb_coeff[1][1];
        0x00000d22,//yuv2rgb_coeff[1][2];
        0x00000088,//yuv2rgb_coeff[1][3];
        0x00000400,//yuv2rgb_coeff[2][0];
        0x0000071e,//yuv2rgb_coeff[2][1];
        0x00000000,//yuv2rgb_coeff[2][2];
        0x00000f1c,//yuv2rgb_coeff[2][3];
    },//yuv2rgbInfo;  
    {
        {
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_0,//sel;
            },//layer0
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_1,//sel;
            },//layer1
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_2,//sel;
            },//layer2
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_VIDEO_LAYER_3,//sel;
            },//layer3
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_0,//sel;
            },//layer4osd0
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_1,//sel;
            },//layer4osd1
            {
                1,//glben;
                0xff,//glbalp;
                VO_MIXER_OSD_LAYER_2,//sel;
            },//layer4osd2
        },
        {
            0x00,//0x80,//y;
            0x80,//u;
            0x80,//v;
        },
    },//dispMixCtlInfo;
    1,//ditherctlen;
    0,//clutctlen;
    {
        0,//underrundcnt0;
        0,//en0;
        0,//underrundcnt1;
        0,//en1;
        0,//underrundcnt2;
        0,//en2;  
    },
};
