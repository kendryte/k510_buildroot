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
#ifndef _ISP_DS_DRV_DEF_H_
#define _ISP_DS_DRV_DEF_H_

//#include "video/isp/isp.h"

#define ISP_DS_CH_NUM 3
#define ISP_DS_CH_OSD_NUM 3

typedef struct _ISP_DS_INPUT_SIZE_S
{
    unsigned int    input_frame_height;
    unsigned int    input_frame_width; 
} ISP_DS_INPUT_SIZE_S;

typedef struct _ISP_DS_OSD_RGB2YUV_COEFF_S
{
    unsigned int    osd_rgb2yuv_coeff00;
    unsigned int    osd_rgb2yuv_coeff01;
    
    unsigned int    osd_rgb2yuv_coeff02;
    unsigned int    osd_rgb2yuv_coeff03;
    
    unsigned int    osd_rgb2yuv_coeff10;
    unsigned int    osd_rgb2yuv_coeff11;
    
    unsigned int    osd_rgb2yuv_coeff12;
    unsigned int    osd_rgb2yuv_coeff13;
    
    unsigned int    osd_rgb2yuv_coeff20;
    unsigned int    osd_rgb2yuv_coeff21;
    
    unsigned int    osd_rgb2yuv_coeff22;
    unsigned int    osd_rgb2yuv_coeff23;

} ISP_DS_OSD_RGB2YUV_COEFF_S;

typedef struct _ISP_DS_OSD_YUV2RGB_COEFF_S
{
    unsigned int    osd_yuv2rgb_coeff00;
    unsigned int    osd_yuv2rgb_coeff01;
    
    unsigned int    osd_yuv2rgb_coeff02;
    unsigned int    osd_yuv2rgb_coeff03;
    
    unsigned int    osd_yuv2rgb_coeff10;
    unsigned int    osd_yuv2rgb_coeff11;
    
    unsigned int    osd_yuv2rgb_coeff12;
    unsigned int    osd_yuv2rgb_coeff13;
    
    unsigned int    osd_yuv2rgb_coeff20;
    unsigned int    osd_yuv2rgb_coeff21;
    
    unsigned int    osd_yuv2rgb_coeff22;
    unsigned int    osd_yuv2rgb_coeff23;

} ISP_DS_OSD_YUV2RGB_COEFF_S;

typedef struct _ISP_DS_VSCALE_PARM_S
{
    unsigned int  vscale_dstep;    
    unsigned int   vscale_pstep;     
    unsigned int   vscale_filter_en;
    
    unsigned int   scale_en;        
         
} ISP_DS_VSCALE_PARM_S;

typedef struct _ISP_DS_HSCALE_PARM_S
{
    unsigned int   hscale_dstep;     
    unsigned int    hscale_pstep;     
    unsigned int    hscale_filter_en; 
} ISP_DS_HSCALE_PARM_S;

typedef struct _ISP_DS_SIZE_S
{
    unsigned int    frame_output_height;
    unsigned int    frame_output_width; 
} ISP_DS_SIZE_S;

typedef struct _ISP_DS_FORMAT_S
{
    unsigned int    out_rgb_mode;
    unsigned int    out_rgb_en;  
    unsigned int    out_yuv_mode;
    unsigned int    out_uv_swap;       
} ISP_DS_FORMAT_S;

typedef struct _ISP_DS_OSD_INFO_S
{
    unsigned int    osd_type;      
    unsigned int    osd_alpha_tpye;
    unsigned int    osd_enable;
    unsigned int    reserved0;              
} ISP_DS_OSD_INFO_S;

typedef struct _ISP_DS_OSD_SIZE_S
{
    unsigned int    osd_width;  
    unsigned int    osd_height; 
} ISP_DS_OSD_SIZE_S;

typedef struct _ISP_DS_OSD_BUF_S
{
    unsigned int    osd_rgb_addr0;    
    unsigned int    osd_alpha_addr0;  
    unsigned int    osd_rgb_addr1;    
    unsigned int    osd_alpha_addr1;  

    unsigned int    osd_stride;       
    unsigned int    osd_alpha_stride; 

    unsigned int    osd_position_start_x;
    unsigned int    osd_position_stop_x;      

    unsigned int    osd_position_start_y;
    unsigned int    osd_position_stop_y;      
}ISP_DS_OSD_BUF_S;

typedef struct _ISP_DS_OSD_DMA_CTL_S
{
    unsigned int    osd_dma_request_length;
    unsigned int    osd_dma_map;           
    unsigned int    osd_rgb_rev;           
    unsigned int    osd_global_alpha;       
    unsigned int    osd_swap_64;
    unsigned int    osd_outstanding_num;
    unsigned int    osd_bd_limit_en;
} ISP_DS_OSD_DMA_CTL_S;

typedef struct _ISP_DS_OSD_ATTR_S
{
    ISP_DS_OSD_INFO_S stOsdInfo;
    ISP_DS_OSD_SIZE_S stOsdSize;
    ISP_DS_OSD_BUF_S stOsdBuf;
    ISP_DS_OSD_DMA_CTL_S stOsdDmaCtl;
} ISP_DS_OSD_ATTR_S;

typedef struct _ISP_S_DS_ATTR_S
{
    ISP_DS_VSCALE_PARM_S stVscalePram;
    ISP_DS_HSCALE_PARM_S stHscalePram;
    ISP_DS_SIZE_S        stDsSize;
    ISP_DS_FORMAT_S      stDsFormat;
    ISP_DS_OSD_ATTR_S    stDsOsdAttr[ISP_DS_CH_OSD_NUM];
} ISP_S_DS_ATTR_S;

typedef struct _ISP_DS_ATTR_S
{
    ISP_DS_INPUT_SIZE_S stDsInputSize;
    ISP_DS_OSD_RGB2YUV_COEFF_S stDsOsdRgb2YuvCoeff;
    ISP_DS_OSD_YUV2RGB_COEFF_S stDsOsdYuv2RgbCoeff;
    ISP_S_DS_ATTR_S stSDsAttr[ISP_DS_CH_NUM];
} ISP_DS_ATTR_S;

/*
int ISP_DRV_DS_SetInputSize(ISP_DS_INPUT_SIZE_S *pstInputSize);
int ISP_DRV_DS_SetRgb2YuvCoff(ISP_DS_OSD_RGB2YUV_COEFF_S *pstCoff);
int ISP_DRV_DS_SetYuv2RgbCoff(ISP_DS_OSD_RGB2YUV_COEFF_S *pstCoff);
int ISP_DRV_DS_SetHscaleParam(unsigned int u8Index, ISP_DS_HSCALE_PARM_S *pstHscale);
int ISP_DRV_DS_SetVscaleParam(unsigned int u8Index, ISP_DS_VSCALE_PARM_S *pstVscale);
int ISP_DRV_DS_SetOutputSize(unsigned int u8Index, ISP_DS_SIZE_S *pstSize);
int ISP_DRV_DS_SetOutputFormat(unsigned int u8Index, ISP_DS_FORMAT_S *pstFormat);
int ISP_DRV_DS_SetDs0OsdAttr(unsigned int u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr);
int ISP_DRV_DS_SetDs1OsdAttr(unsigned int u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr);
int ISP_DRV_DS_SetDs2OsdAttr(unsigned int u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr);
void ISP_DRV_DS_SetCoeff(void);
*/
//int ISP_DRV_SetDs(unsigned int ispDevIndex,ISP_DS_ATTR_S *pstDsAttr);
int ISP_DRV_SetDs(ISP_DS_ATTR_S *pstDsAttr);
void ISP_DRV_DS_SetCoeff(void);
//debug
int ISP_DRV_GetDsRegsVal(void);
#endif /* _ISP_DS_DRV_DEF_H_ */
