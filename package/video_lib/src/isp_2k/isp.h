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
  File Name     : isp.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _ISP_H_
#define _ISP_H_

#ifdef __cplusplus
extern "C" {
#endif
//
#include "isp_com.h"
#include "isp_2k/isp_f2k.h"
#include "isp_2k/isp_r2k.h"

typedef enum _ISP_PIPE_WDR_MODE_E
{
	  ISP_PIPE_WDR_NONE,
	  ISP_PIPE_WDR_2_FRAME,
	  ISP_PIPE_WDR_3_FRAME,
	  ISP_PIPE_WDR_BUTT,
} ISP_PIPE_WDR_MODE_E;

typedef struct _IMAGE_SIZE{
	unsigned int Width;
	unsigned int Height;	
}IMAGE_SIZE;

typedef struct _ISP_SIZE_S
{
    IMAGE_SIZE total_size;
    IMAGE_SIZE in_size;
    IMAGE_SIZE out_size;
    IMAGE_SIZE ds0_size;
    IMAGE_SIZE ds0_osd0_size;
    IMAGE_SIZE ds0_osd1_size;
    IMAGE_SIZE ds0_osd2_size;
    IMAGE_SIZE ds1_size;
    IMAGE_SIZE ds1_osd0_size;
    IMAGE_SIZE ds1_osd1_size;
    IMAGE_SIZE ds1_osd2_size;
    IMAGE_SIZE ds2_size;
    IMAGE_SIZE ds2_osd0_size;
    IMAGE_SIZE ds2_osd1_size;
}ISP_SIZE_S;

typedef struct _ISP_ADDR_INFO
{
    //wdr
    unsigned int wdr_2f_en;
    unsigned int wdr_3f_en;
    //3dnr
    unsigned int d3nr_addr;
    unsigned int d3nr_y_stride;
    unsigned int d3nr_uv_stride;
    unsigned int d3nr_en;
    //ldc
    unsigned int ldc_addr;
    unsigned int ldc_stride;
    unsigned int ldc_en;
    //main
    unsigned int main_out_addr;
    unsigned int main_stride;
    unsigned int main_en;
    //ds0
    unsigned int ds0_out_addr;
    unsigned int ds0_stride;
    unsigned int ds0_en;
    //ds0 osd0
    unsigned int ds0_osd0_addr;
    unsigned int ds0_osd0_stride;
    unsigned int ds0_osd0_en;
    //ds0 osd1
    unsigned int ds0_osd1_addr;
    unsigned int ds0_osd1_stride;
    unsigned int ds0_osd1_en;
    //ds0 osd2
    unsigned int ds0_osd2_addr;
    unsigned int ds0_osd2_stride; 
    unsigned int ds0_osd2_en;
    //ds1     
    unsigned int ds1_out_addr;
    unsigned int ds1_stride;
    unsigned int ds1_en;
    //ds1 osd0
    unsigned int ds1_osd0_addr;
    unsigned int ds1_osd0_stride;
    unsigned int ds1_osd0_en;
    //ds1 osd1
    unsigned int ds1_osd1_addr;
    unsigned int ds1_osd1_stride;
    unsigned int ds1_osd1_en;
    //ds1 osd2
    unsigned int ds1_osd2_addr;
    unsigned int ds1_osd2_stride;
    unsigned int ds1_osd2_en;
    //ds2
    unsigned int ds2_out_r_addr;
    unsigned int ds2_out_g_addr;
    unsigned int ds2_out_b_addr;
    unsigned int ds2_rgb_stride;
    unsigned int ds2_rgb_type;//DS2_RGB_TYPE ds2_rgb_type;
    unsigned int ds2_en;
    //ds2 osd0
    unsigned int ds2_osd0_addr;
    unsigned int ds2_osd0_stride;
    unsigned int ds2_osd0_en; 
    //ds2 osd1
    unsigned int ds2_osd1_addr;
    unsigned int ds2_osd1_stride;
    unsigned int ds2_osd1_en;   
    //tpg
    unsigned int vi_tpg_baseaddr;
    unsigned int vi_tpg_stride;
    unsigned int vi_tpg_en;
    //vo osd0
    unsigned int vo_osd0_addr;
    unsigned int vo_osd0_stride;
    unsigned int vo_osd0_en;     
    //vo osd1
    unsigned int vo_osd1_addr;
    unsigned int vo_osd1_stride;
    unsigned int vo_osd1_en; 
    //vo osd2
    unsigned int vo_osd2_addr;
    unsigned int vo_osd2_stride;
    unsigned int vo_osd2_en;         
}ISP_ADDR_INFO;

typedef struct _VO_ADDR_INFO
{
    //layer0
    unsigned int layer0_baseaddr;
    unsigned int layer0_stride;
    unsigned int layer0_en;
    //layer1
    unsigned int layer1_baseaddr;
    unsigned int layer1_stride;
    unsigned int layer1_en;
    //layer2
    unsigned int layer2_baseaddr;
    unsigned int layer2_stride;
    unsigned int layer2_en;
    //layer3
    unsigned int layer3_baseaddr;
    unsigned int layer3_stride;
    unsigned int layer3_en;
    //osd0
    unsigned int osd0_baseaddr;
    unsigned int osd0_stride;
    unsigned int osd0_rgb_type;//DS2_RGB_TYPE osd0_rgb_type; 
    unsigned int osd0_en; 
    //osd1
    unsigned int osd1_baseaddr;
    unsigned int osd1_stride; 
    unsigned int osd1_en; 
    //osd2
    unsigned int osd2_baseaddr;
    unsigned int osd2_stride;
    unsigned int osd2_en; 
}VO_ADDR_INFO;


typedef struct _VO_SIZE_S
{
    IMAGE_SIZE layer0_size;
    IMAGE_SIZE layer0_out_size;
    IMAGE_SIZE layer1_size;
    IMAGE_SIZE layer2_size;
    IMAGE_SIZE layer3_size;
    IMAGE_SIZE osd0_size;
    IMAGE_SIZE osd1_size;
    IMAGE_SIZE osd2_size;
}VO_SIZE_S;

#if 0
typedef enum _ISP_OUT_CHL_SEL{
    MAIN_OUT,
    DS0_OUT,
    DS1_OUT,
    DS2_OUT,
}ISP_OUT_CHL_SEL;

typedef enum _ISP_IN_CH_MODE{
    BT656,
    BT1120_MIPI,
}ISP_IN_CH_MODE;
//wrap
typedef struct _ISP_WRAP_WDR_S
{
  //ISP_PIPE_WDR_MODE_E 	wdr_mode ;
  unsigned int    wdr_mode ;
	unsigned int    wdr_long_ch_mode; 	
	unsigned int 	  wdr_long_l2_buf_en;
  unsigned int    wdr_short_s1_buf_en; 
  unsigned int    wdr_dynamic_switch_en;
  unsigned int    wdr_long_l2_buf_depth;	
  unsigned int 	  wdr_long_img_format;   
  unsigned int 	  wdr_long_yuv_in_format;   
  unsigned int 	  wdr_long_img_out_format;  
  unsigned int 	  wdr_long_yuv422_pxl_order;
  unsigned int 	  wdr_long_pixel_width;
  unsigned int    wdr_buf_base;        
  unsigned int    wdr_line_stride;	
	unsigned int    wdr_frame_buf_size;		
}ISP_WRAP_WDR_S;

typedef struct _ISP_WRAP_3DNR_S
{
  unsigned int 	  nr3d_en ;
  unsigned int    nr3d_fbcd_en;
  unsigned int    nr3d_mv_out_en;
  unsigned int 	  nr3d_y_img_format; 
  unsigned int 	  nr3d_y_yuv_in_format;   
  unsigned int 	  nr3d_y_img_out_format;  
  unsigned int 	  nr3d_y_yuv422_pxl_order;
  unsigned int 	  nr3d_y_pixel_width; 
  unsigned int 	  nr3d_uv_img_format; 
  unsigned int 	  nr3d_uv_yuv_in_format;   
  unsigned int 	  nr3d_uv_mig_out_format;  
  unsigned int 	  nr3d_uv_yuv422_pxl_order;
  unsigned int 	  nr3d_uv_pixel_width;    
  unsigned int    nr3d_y_buf_base; 
  unsigned int    nr3d_uv_buf_base;        
  unsigned int    nr3d_y_line_stride;
  unsigned int    nr3d_uv_line_stride;
	unsigned int    nr3d_frame_buf_size;	
}ISP_WRAP_3DNR_S;

typedef struct _ISP_WRAP_LDC_S
{
   unsigned int   ldc_en;
   unsigned int   ldc_y_buf_base; 
   unsigned int   ldc_uv_buf_base; 
   unsigned int   ldc_line_stride; 
   unsigned int   ldc_frame_buf_size;     
}ISP_WRAP_LDC_S;

typedef struct _ISP_WRAP_MAIN_S
{
  unsigned int 	  main_out_en;
	IMAGE_SIZE		  main_size;
	unsigned int    main_pix_remap_en;
  unsigned int 	  main_out_img_format;   
  unsigned int 	  main_out_yuv_in_format;   
  unsigned int 	  main_out_img_out_format;  
  unsigned int 	  main_out_yuv422_pxl_order;
  unsigned int 	  main_out_pxl_width;	
  unsigned int    main_y_buf0_base;   
  unsigned int    main_y_buf1_base;
  unsigned int    main_uv_buf0_base;   
  unsigned int    main_uv_buf1_base;        
  unsigned int    main_line_stride; 
	unsigned int    main_frame_buf_size;	
}ISP_WRAP_MAIN_S;

typedef struct _ISP_WRAP_DS0_S
{
  unsigned int 	  ds0_out_en;
  unsigned int 	  ds0_osd0_en ;   
  unsigned int 	  ds0_osd1_en ; 
  unsigned int 	  ds0_osd2_en ;
  unsigned int    pix_remap_out0_en;		 		
	IMAGE_SIZE		  ds0_size;
  unsigned int 	  ds0_out_img_format;   
  unsigned int 	  ds0_out_yuv_in_format;   
  unsigned int 	  ds0_out_img_out_format;  
  unsigned int 	  ds0_out_yuv422_pxl_order;
  unsigned int    ds0_out_pxl_width;	
  unsigned int    ds0_y_buf0_base;   
  unsigned int    ds0_y_buf1_base;
  unsigned int    ds0_uv_buf0_base;   
  unsigned int    ds0_uv_buf1_base;       
  unsigned int    ds0_line_stride;
	unsigned int    ds0_frame_buf_size;	 
}ISP_WRAP_DS0_S;

typedef struct _ISP_WRAP_DS1_S
{
  unsigned int 	  ds1_out_en;
  unsigned int 	  ds1_osd0_en ;   
  unsigned int 	  ds1_osd1_en ; 
  unsigned int 	  ds1_osd2_en ;
  unsigned int    pix_remap_out1_en;		 		
	IMAGE_SIZE		  ds1_size;
  unsigned int 	  ds1_out_img_format;   
  unsigned int 	  ds1_out_yuv_in_format;   
  unsigned int 	  ds1_out_img_out_format;  
  unsigned int 	  ds1_out_yuv422_pxl_order;
  unsigned int    ds1_out_pxl_width;	
  unsigned int    ds1_y_buf0_base;   
  unsigned int    ds1_y_buf1_base;
  unsigned int    ds1_uv_buf0_base;   
  unsigned int    ds1_uv_buf1_base;  
  unsigned int    ds1_line_stride;
	unsigned int    ds1_frame_buf_size;	 
}ISP_WRAP_DS1_S;

typedef struct _ISP_WRAP_DS2_S
{
  unsigned int 	  ds2_out_en;
  unsigned int 	  ds2_osd0_en ;   
  unsigned int 	  ds2_osd1_en ; 
  unsigned int 	  ds2_osd2_en ; 	 		
	IMAGE_SIZE		  ds2_size;
  unsigned int 	  ds2_out_img_format;   
  unsigned int 	  ds2_out_yuv_in_format;   
  unsigned int 	  ds2_out_img_out_format;  
  unsigned int 	  ds2_out_yuv422_pxl_order;
  unsigned int    ds2_out_pxl_width;	
  unsigned int    ds2_r_buf0_base;   
  unsigned int    ds2_r_buf1_base;
  unsigned int    ds2_g_buf0_base;   
  unsigned int    ds2_g_buf1_base; 
  unsigned int    ds2_b_buf0_base;   
  unsigned int    ds2_b_buf1_base;      
  unsigned int    ds2_line_stride; 
	unsigned int    ds2_frame_buf_size;	
}ISP_WRAP_DS2_S;

typedef struct _ISP_WRAP_DMA_S
{
	unsigned int    dma_wr_data_mode;
	unsigned int    dma_wr_out_swap;
}ISP_WRAP_DMA_S;

typedef struct _ISP_WRAP_INT_CORE_S
{
  unsigned int    int_raw_in_en;  
  unsigned int    int_3a_en;      
  unsigned int    raw_int_en;     
  unsigned int    rgb_int_en;     
  unsigned int    yuv_int_en;     
  unsigned int    ldc_int_en;     
  unsigned int    main_out_int_en;
  unsigned int    isp_awb_int_en; 
  unsigned int    isp_ae_int_en;  
  unsigned int    isp_af_int_en;  
}ISP_WRAP_INT_CORE_S;
 
typedef struct _ISP_WRAP_INT_WR0_S
{    //
  unsigned int    wr_3dnr_y_frm_end_int_en;           
  unsigned int    wr_3dnr_y_line_base_int_en;         
  unsigned int    wr_3dnr_y_err_frm_end_int_en;       
  unsigned int    wr_3dnr_y_err_immediate_int_en;     
  unsigned int    wr_3dnr_uv_frm_end_int_en;          
  unsigned int    wr_3dnr_uv_line_base_int_en;        
  unsigned int    wr_3dnr_uv_err_frm_end_int_en;      
  unsigned int    wr_3dnr_uv_err_immediate_int_en;    
  unsigned int    ldc_wr_y_frm_end_int_en;            
  unsigned int    ldc_wr_y_line_base_int_en;          
  unsigned int    ldc_wr_y_err_frm_end_int_en;        
  unsigned int    ldc_wr_y_err_immediate_int_en;      
  unsigned int    ldc_wr_uv_frm_end_int_en;           
  unsigned int    ldc_wr_uv_line_base_int_en;         
  unsigned int    ldc_wr_uv_err_frm_end_int_en;       
  unsigned int    ldc_wr_uv_err_immediate_int_en;     
  unsigned int    wdr_wr_raw_frm_end_int_en;          
  unsigned int    wdr_wr_raw_line_base_int_en;        
  unsigned int    wdr_wr_raw_err_frm_end_int_en;      
  unsigned int    wdr_wr_raw_err_immediate_int_en;    
  //                
  unsigned int    main_out_wr_y_frm_end_int_en;       
  unsigned int    main_out_wr_y_line_base_int_en;     
  unsigned int    main_out_wr_y_err_frm_end_int_en;   
  unsigned int    main_out_wr_y_err_immediate_int_en; 
  unsigned int    main_out_wr_uv_frm_end_int_en;      
  unsigned int    main_out_wr_uv_line_base_int_en;    
  unsigned int    main_out_wr_uv_err_frm_end_int_en;  
  unsigned int    main_out_wr_uv_err_immediate_int_en;
}ISP_WRAP_INT_WR0_S;

typedef struct _ISP_WRAP_INT_WR1_S
{    //
  unsigned int    ds0_out_wr_y_frm_end_en;        
  unsigned int    ds0_out_wr_y_line_base_en;      
  unsigned int    ds0_out_wr_y_err_frm_end_en;    
  unsigned int    ds0_out_wr_y_err_immediate_en;  
  unsigned int    ds0_out_wr_uv_frm_end_en;       
  unsigned int    ds0_out_wr_uv_line_base_en;     
  unsigned int    ds0_out_wr_uv_err_frm_end_en;   
  unsigned int    ds0_out_wr_uv_err_immediate_en; 
  unsigned int    ds1_out_wr_y_frm_end_en;        
  unsigned int    ds1_out_wr_y_line_base_en;      
  unsigned int    ds1_out_wr_y_err_frm_end_en;    
  unsigned int    ds1_out_wr_y_err_immediate_en;  
  unsigned int    ds1_out_wr_uv_frm_end_en;       
  unsigned int    ds1_out_wr_uv_line_base_en;     
  unsigned int    ds1_out_wr_uv_err_frm_end_en;   
  unsigned int    ds1_out_wr_uv_err_immediate_en; 
  unsigned int    ds2_out_wr_r_frm_end_en;        
  unsigned int    ds2_out_wr_r_line_base_en;      
  unsigned int    ds2_out_wr_r_err_frm_end_en;    
  unsigned int    ds2_out_wr_r_err_immediate_en;  
  unsigned int    ds2_out_wr_g_frm_end_en;        
  unsigned int    ds2_out_wr_g_line_base_en;      
  unsigned int    ds2_out_wr_g_err_frm_end_en;    
  unsigned int    ds2_out_wr_g_err_immediate_en;  
  unsigned int    ds2_out_wr_b_frm_end_en;        
  unsigned int    ds2_out_wr_b_line_base_en;      
  unsigned int    ds2_out_wr_b_err_frm_end_en;    
  unsigned int    ds2_out_wr_b_err_immediate_en; 
}ISP_WRAP_INT_WR1_S;

typedef struct _ISP_WRAP_INT_RD0_S
{
  unsigned int    rd_3dnr_y_frm_end_int_en;       
  unsigned int    rd_3dnr_y_line_base_int_en;     
  unsigned int    rd_3dnr_y_err_frm_end_int_en;   
  unsigned int    rd_3dnr_y_err_immediate_int_en; 
  unsigned int    rd_3dnr_uv_frm_end_int_en;      
  unsigned int    rd_3dnr_uv_line_base_int_en;    
  unsigned int    rd_3dnr_uv_err_frm_end_int_en;  
  unsigned int    rd_3dnr_uv_err_immediate_int_en;
  unsigned int    ldc_rd_y_frm_end_int_en;        
  unsigned int    ldc_rd_y_line_base_int_en;      
  unsigned int    ldc_rd_y_err_frm_end_int_en;    
  unsigned int    ldc_rd_y_err_immediate_int_en;  
  unsigned int    ldc_rd_uv_frm_end_int_en;       
  unsigned int    ldc_rd_uv_line_base_int_en;     
  unsigned int    ldc_rd_uv_err_frm_end_int_en;   
  unsigned int    ldc_rd_uv_err_immediate_int_en; 
  unsigned int    wdr_rd_raw_frm_end_int_en;      
  unsigned int    wdr_rd_raw_line_base_int_en;    
  unsigned int    wdr_rd_raw_err_frm_end_int_en;  
  unsigned int    wdr_rd_raw_err_immediate_int_en;        

}ISP_WRAP_INT_RD0_S;

typedef struct _ISP_WRAP_INT_S
{
  ISP_WRAP_INT_CORE_S intCoreEn;
  ISP_WRAP_INT_WR0_S  intWr0En;
  ISP_WRAP_INT_WR1_S  intWr1En;
  ISP_WRAP_INT_RD0_S  intRd0En;    
}ISP_WRAP_INT_S;

typedef struct _ISP_WRAP_CFG_INFO
{
	unsigned int	    isp_out_sel;
	unsigned int      dvp_ch_mode;
  unsigned int      hist_3a_out_en;
	ISP_WRAP_WDR_S    wdrInfo;
	ISP_WRAP_3DNR_S   nr3dInfo;
	ISP_WRAP_LDC_S    ldcInfo;
	ISP_WRAP_MAIN_S	  mainInfo;
	ISP_WRAP_DS0_S	  ds0Info;
	ISP_WRAP_DS1_S	  ds1Info;
	ISP_WRAP_DS2_S	  ds2Info;
	ISP_WRAP_DMA_S    dmaInfo[16];
  //
  ISP_WRAP_INT_S    intmaskinfo;
} ISP_WRAP_CFG_INFO;
//core
typedef enum _ISP_SYNC_POLARITY_E
{
	ISP_SYNC_POL_LOW = 0,
	ISP_SYNC_POL_HIGH = 1,
	ISP_SYNC_POL_BUTT,
} ISP_SYNC_POLARITY_E;

typedef enum _ISP_HSYNC_GEN_MODE_E
{
	HSYNC_BASE_ON_INPUT_GEN_BY_ISP = 0,
	HSYNC_BASE_ON_INPUT = 1,
	HSYNC_GEN_BY_ISP_IN_FIELD_BLANK = 2,
	HSYNC_GEN_BY_ISP = 3,
	ISP_HSYNC_BUTT
} ISP_HSYNC_GEN_MODE_E;

typedef enum _ISP_VSYNC_GEN_MODE_E
{
	VSYNC_GEN_BY_ISP = 0,
	VSYNC_BASE_ON_INPUT = 1,
	ISP_VSYNC_BUTT
} ISP_VSYNC_GEN_MODE_E;

typedef enum _ISP_VIDEO_FORMAT_E
{
	ISP_RGBRAW_DATA = 0,
	ISP_YUV_DATA = 1,
	ISP_VIDEO_FORMAT_BUTT
} ISP_VIDEO_FORMAT_E;

typedef enum _ISP_YUV_FOTMAT_E
{
    IN_YUV422,
    IN_YUV420,
}ISP_YUV_FOTMAT_E;

typedef enum _ISP_RGB_OUTPUT_FOTMAT_E
{
    OUT_S_RGB,
    OUT_ARGB,
}ISP_RGB_OUTPUT_FOTMAT_E;

typedef enum _ISP_YUV422_PIXEL_ORDER_E
{
    YUYV,
    YVYU,
    UYVY,
    VYUY,
}ISP_YUV422_PIXEL_ORDER_E;

typedef enum _ISP_PIXEL_ORDER_E
{
    PIXEL_8,
    PIXEL_10,
    PIXEL_12,
    PIXEL_14,
    PIXEL_16,
    PIXEL_18,
    PIXEL_20,
    PIXEL_24,
}ISP_PIXEL_ORDER_E;

typedef enum _ISP_AE_LOCK_STS_E
{
	AE_LOCK_32FRAME = 0,
	AE_LOCK_64FRAME = 1,
} ISP_AE_LOCK_STS_E;

typedef enum _ISP_AE_WIN_SEL_E
{
	AE_WHOLE_PIC = 0,
	AE_CENTRL_AREA = 1,
  AE_CENTRL_WEIGHTED = 2,
} ISP_AE_WIN_SEL_E;

typedef enum _ISP_AE_MD_SEL_E
{
	AE_NORMAL_MODE = 0,
	AE_BACKLIGHT_COMP = 1,
  AE_STRONGLIGHT_SUPP = 2,
} ISP_AE_MD_SEL_E;

typedef enum _ISP_AE_DN_SEL_E
{
	AE_DAY = 0,
	AE_NIGHT = 1,
} ISP_AE_DN_SEL_E;

typedef enum _ISP_AWB_SL_E
{
	AWB_HANDLE = 0,
	AWB_AUTO = 1,
} ISP_AWB_SL_E;

typedef enum _ISP_AWB_WIN_SL_E
{
	AWB_FULL_IMG = 0,
	AWB_LMT_IMG = 1,
} ISP_AWB_WIN_SL_E;

typedef enum _ISP_AWB_FB_MODE_E
{
	AWB_THROUGH_MODE = 0,
	AWB_FEEDBACK_MODE = 1,
} ISP_AWB_FB_MODE_E;

typedef enum _ISP_WDR_OUT_SEL_E
{
	WDR_L_EX_OUT = 0,
	WDR_S_EX_OUT = 1,
} ISP_WDR_OUT_SEL_E;

typedef enum _ISP_WDR_2F_EX_RATIO_E
{
	WDR_EX_RATIO_16F = 0,
	WDR_EX_RATIO_32F = 1,
  WDR_EX_RATIO_64F = 2,
} ISP_WDR_2F_EX_RATIO_E;

typedef enum _ISP_WDR_3F_EX_RATIO_E
{
	WDR_EX_RATIO_16_4 = 0,
	WDR_EX_RATIO_32_8 = 1,
  WDR_EX_RATIO_16_16 = 2,
} ISP_WDR_3F_EX_RATIO_E;

typedef enum _ISP_WDR_STS_SEL_E
{
	WDR_S_EC_FRAME = 0,
	WDR_M_EC_FRAME = 1,
  WDR_L_EC_FRAME = 2,
}ISP_WDR_STS_SEL_E;

typedef enum _ISP_OTC_YC_SEL_E
{
	OTC_Y_MSB_C_LSB = 0,
	OTC_C_MSB_Y_LSB = 1,
}ISP_OTC_YC_SEL_E;

typedef enum _ISP_OTC_YUV422_FMT_E
{
	OTC_UV = 0,
	OTC_VU = 1,
}ISP_OTC_YUV422_FMT_E;

typedef enum _ISP_OTC_POLARITY_E
{
	OTC_POSITIVE = 0,
	OTC_NEGATIVE = 1,
}ISP_OTC_POLARITY_E;

typedef enum _ISP_AF_STS_MD_E
{
	AF_FULL_IMG = 0,
	AF_IN_WINDOW = 1,
  AF_IN_75PER_WINDOW = 2,
  AF_IN_94PER_WINDOW = 3,
}ISP_AF_STS_MD_E;

typedef enum _ISP_MFBC_OUT_E
{
	MFBC_OUT_422_EN = 0,
	MFBC_OUT_420_EN = 1,
}ISP_MFBC_OUT_E;

#if 0
typedef struct _IMAGE_SIZE{
	unsigned int Width;
	unsigned int Height;	
}IMAGE_SIZE;
#endif

typedef struct _CROP_SIZE{
	unsigned int    Width_st;
	unsigned int    Height_st;	
	unsigned int    Width;
	unsigned int    Height;	
}CROP_SIZE;

typedef struct _WIN_SIZE{
	unsigned int    v_start;
	unsigned int    h_start;	
	unsigned int    v_end;
	unsigned int    h_end;	
}WIN_SIZE;
//itc
typedef struct _ITC_INFO_S
{
 	unsigned int    hsync_pol;
	unsigned int    vsync_pol;
	unsigned int    hsync_input_timing;
	unsigned int    vsync_input_timing;   
	unsigned int    flip_ctl;         
  unsigned int    video_fmt_sel;
  struct _IMAGE_SIZE		  total_size;
  struct _CROP_SIZE       itc_size;
}ITC_INFO_S;
//tpg
typedef struct _TPG_INFO_S
{
  unsigned int    tpg_en;
	unsigned int    tpg_sel;
  unsigned int    bayer_mode_sel;  
  unsigned int    motion_mode_sel;    
  unsigned int    wdr_l_mul_data;  
  unsigned int    wdr_m_mul_data;  
  unsigned int    wdr_s_mul_data;
}TPG_INFO_S;
//blc
typedef struct _BLC_INFO_S
{
	unsigned int    blc_en;     
  unsigned int    blc_offset; 
  unsigned int    blc_ratio;
}BLC_INFO_S;
//lsc
typedef struct _LSC_INFO_S
{
  unsigned int    lsc_en;           
  unsigned int    lsc_h_center;     
  unsigned int    lsc_v_center;     
  unsigned int    lsc_r_ratio;    
  unsigned int    lsc_g_ratio;  
  unsigned int    lsc_b_ratio;   
  unsigned int    lsc_ir_ratio; 
}LSC_INFO_S;
//ae
typedef struct _AE_INFO_S
{ 
    unsigned int    ae_as_en; 
    unsigned int    ae_ag_en;      
    unsigned int    ae_airis_en;      
    unsigned int    ae_enter_ls_sel; 
    unsigned int    ae_exit_ls_sel;     
    unsigned int    ae_win_mode_sel;    
    unsigned int    ae_back_light_mode_sel;
    unsigned int    ae_day_change_en;    
    unsigned int    ae_day_change_sel;
	  struct _WIN_SIZE		    ae_win_size;
    
    unsigned int    ae_tar_bright;    
    unsigned int    ae_tar_bright_range;     
    unsigned int    ae_l_ex_time;
    unsigned int    ae_m_ex_time;
    unsigned int    ae_s_ex_time;     
    unsigned int    ae_agc;       
    unsigned int    ae_ad_shuttle_freq;
    unsigned int    ae_ad_gain_freq;    
    unsigned int    ae_adjust_step_max;     
    unsigned int    ae_ex_value_max;  
    unsigned int    ae_ex_value_mid;    
    unsigned int    ae_ex_value_min;     
    unsigned int    ae_gain_value_max;    
    unsigned int    ae_gain_value_mid;
    unsigned int    ae_gain_value_min;    
    unsigned int    ae_dn_switch_ad_step_max;
    unsigned int    ae_dn_switch_wait_time;
    unsigned int    ape_max_diff;    
    unsigned int    ape_drv_signal_max;    
    unsigned int    ape_coeff_distance;    
    unsigned int    ape_coeff_speed;    
    unsigned int    ape_coeff_acceleration;     
    unsigned int    ape_drv_manual_value;  
    unsigned int    ape_damp_manual_value; 
}AE_INFO_S;
//awb
typedef struct _AWB_INFO_S
{
    unsigned int    awb_d65_en; 
    unsigned int    awb_ccm_en; 
    unsigned int    awb_en;     
    unsigned int    awb_mode_sel;
        
    unsigned int    awb_hist_mode_sel;
    unsigned int    awb_veri_en;      
    unsigned int    awb_fb_en;
    unsigned int    awb_value_save_en;
        
    unsigned int    awb_ccm_adp_adjust_en;
    unsigned int    awb_stab_en; 
    unsigned int    awb_d65_red_gain;
    
    unsigned int    awb_d65_blue_gain;
    unsigned int    ccm_coff[3][3];
  
    unsigned int    ccm_correct_coff;
        
	  struct _WIN_SIZE	      awb_win_size; 
    
    unsigned int    awb_correct_diff_th;     
    unsigned int    awb_color_changeres_time;
    unsigned int    awb_historgram_th;
    
    unsigned int    awb_red_gain_adjust;     
    unsigned int    awb_green_gain_adjust;   
    unsigned int    awb_blue_gain_adjust;    
    unsigned int    awb_red_max_value;
    unsigned int    awb_blue_max_value;      
    unsigned int    awb_red_min_value;       
    
    unsigned int    awb_blue_min_value;
    unsigned int    awb_red_obj_value;
    unsigned int    awb_blue_obj_value;
}AWB_INFO_S;
//wdr
typedef struct _WDR_INFO_S
{
    unsigned int  wdr_fusion_en;      
    unsigned int  wdr_frame_sel;      
    unsigned int  wdr_adp_adjust_en;  
    unsigned int  wdr_stab_en;
    
    unsigned int  wdr_en;             
    unsigned int  wdr_ghost_remove_en; 
    unsigned int  wdr_3frame_out_mode;
    unsigned int  wdr_mode_sel;
    
    unsigned int  wdr_2frame_ex_ratio;
    unsigned int  wdr_3frame_ex_ratio; 
    unsigned int  wdr_stat_img_sel;   
    unsigned int  wdr_ltm_data_sel;
    
    unsigned int  wdr_tz_data_sel;
    unsigned int  wdr_remove_purple_en;
    unsigned int  wdr_over_ex_ratio_th1;
    
    unsigned int  wdr_over_ex_ratio_th2;
    unsigned int  wdr_fusion_ratio_th;
    
    unsigned int  wdr_fusion_value1;  
    unsigned int  wdr_fusion_value2;
}WDR_INFO_S;
//csc
typedef struct _CSC_INFO_S
{
	unsigned int    csc_r2y[3][3];
}CSC_INFO_S;
//ADA
typedef struct _ADA_INFO_S
{
    unsigned int    ada_rgb_gamma_en; 
    unsigned int    ada_yuv_gamma_en; 
    unsigned int    ada_adjust_en;    
    unsigned int    ada_img_stab_en;

    unsigned int    ada_ccr_en;       
    unsigned int    ada_adp_en;       
    unsigned int    ada_adp_ccr_en;   
    unsigned int    ada_stat_mode_sel;

    unsigned int    ada_enh_mode_sel;
    unsigned int    ada_stat_max_value; 
    unsigned int    ada_ad_stren_max_value;
     
	  struct _WIN_SIZE	      ada_win_size;
}ADA_INFO_S;
//rgbir
typedef struct _RGBIR_INFO_S
{
    unsigned int    rgbir_en;        
    unsigned int    rgbir_rtf_en;    
    unsigned int    rgbir_rpc_en;    
    unsigned int    rgbir_fusion_en;
    
    unsigned int    rgbir_output_sel;
 
    unsigned int    rgbir_rpc_max_value; 
    unsigned int    rgbir_rpc_color_coff;
    unsigned int    rgbir_rpc_luma_coff; 
    
    unsigned int    rgbir_rpc_th;       
    unsigned int    rgbir_rpc_th1;  
}RGBIR_INFO_S;
//nr2d
typedef struct _NR2D_INFO_S
{
    unsigned int    d2nr_pcf_en;       
    unsigned int    d2nr_raw_en;       
    unsigned int    d2nr_edge_en;      
    unsigned int    d2nr_bap_en;       
    
    unsigned int    d2nr_luma_en;      
    unsigned int    d2nr_chroma_en;    
    unsigned int    d2nr_pcf_adp_en;   
    unsigned int    d2nr_raw_adp_en;   
    
    unsigned int    d2nr_luma_adp_en;  
    unsigned int    d2nr_chroma_adp_en;
    unsigned int    d2nr_raw_intensity;
    unsigned int    d2nr_bap_intensity;

    unsigned int    d2nr_edge_intensity;
    unsigned int    d2nr_luma_intensity;
    unsigned int    d2nr_chroma_intensity;
}NR2D_INFO_S;
//nr3d
typedef struct _NR3D_INFO_S
{
    unsigned int    d3nr_en;            
    unsigned int    d3nr_pre_luma_en;  
    unsigned int    d3nr_pre_chroma_en; 
    unsigned int    d3nr_main_luma_en;
    
    unsigned int    d3nr_main_chroma_en;
    unsigned int    d3nr_post_luma_en;  
    unsigned int    d3nr_post_chroma_en;
    unsigned int    d3nr_2d_luma_en;
    
    unsigned int    d3nr_2d_chroma_en;  
    unsigned int    d3nr_wb_en;         
    unsigned int    d3nr_wb_sel;
    unsigned int    d3nr_adp_luma_en;
    
    unsigned int    d3nr_adp_chroma_en;
    unsigned int    d3nr_pre_luma_th;        
    unsigned int    d3nr_pre_luma_intensity;   
    unsigned int    d3nr_pre_chroma_intensity;
    
    unsigned int    d3nr_mid_filter_th;
    unsigned int    d3nr_pre_mid_filter_th;    
    unsigned int    d3nr_cur_mid_filter_th;    
    unsigned int    d3nr_low_pass_filter_th;
    unsigned int    d3nr_luma_th;             
    unsigned int    d3nr_min_value;
    unsigned int    d3nr_luma_intensity;
    
    unsigned int    d3nr_chroma_intensity;    
    unsigned int    d3nr_post_edge_th;        
    unsigned int    d3nr_post_luma_intensity;  
    unsigned int    d3nr_post_chroma_intensity;  
}NR3D_INFO_S;
//enh
typedef struct _ENH_INFO_S
{
    unsigned int    enh_ltm_en;       
    unsigned int    enh_sharp_en;     
    unsigned int    enh_cc_en;        
    unsigned int    enh_adp_ltm_en;
    
    unsigned int    enh_adp_sharp_en; 
    unsigned int    enh_adp_cc_en;    
    unsigned int    ltm_gain;  
    unsigned int    ltm_th;    
    
    unsigned int    enh_nr_th; 
    unsigned int   	enh_th1;
    unsigned int   	enh_th2;
    unsigned int    sharp_gain; 
}ENH_INFO_S;
//post
typedef struct _POST_INFO_S
{
    unsigned int    post_cont_ad_en;   
    unsigned int    post_luma_ad_en;   
    unsigned int    post_satu_ad_en;   
    unsigned int    cont_ad_intensity;    
    unsigned int    luma_ad_intensity;
    unsigned int    satu_ad_intensity; 
}POST_INFO_S;
//otc
typedef struct _OTC_INFO_S
{
    unsigned int    post_otc_en;  
    unsigned int    otc_yc_sel;        
    unsigned int    otc_uv_format_sel; 
    unsigned int    otc_hsync_pol_sel;
    unsigned int    otc_vsync_pol_sel;
	  struct _CROP_SIZE 		  otc_out_size; 	 
}OTC_INFO_S;
//ldc
typedef struct _LDC_INFO_S
{
	  unsigned int    ldc_en;     
    unsigned int    ldc_arith_en;   
    unsigned int    ldc_req_freq;   
    
    unsigned int    ldc_stt_ln;
    unsigned int    ldc_h_center_pos;
    
    unsigned int    ldc_v_center_pos;
    unsigned int    ldc_rectify_cr; 
    
    unsigned int    ldc_rectify_cz; 
}LDC_INFO_S;
//af
typedef struct _AF_INFO_S
{
  unsigned int    af_stat_en;          
  unsigned int    af_stat_mode_sel; 
	struct _WIN_SIZE		    af_win_size; 
} AF_INFO_S;
//isp 3dnr fbcd
typedef struct _FBCD_BUF_S
{
	unsigned int    data_buf_base0;
	unsigned int    data_buf_base1;	
	unsigned int    data_stride;
	unsigned int    data_wr_blen;
}FBCD_BUF_S;
//fbc
typedef struct _FBC_INFO_S
{
  unsigned int    fbc_out_format_cfg;
    
	struct _IMAGE_SIZE	    fbc_input_size; 

	struct _FBCD_BUF_S      yDataBufInfo;
	struct _FBCD_BUF_S      yHeadBufInfo;

	struct _FBCD_BUF_S      uvDataBufInfo;
	struct _FBCD_BUF_S      uvHeadBufInfo;

	struct _FBCD_BUF_S      ylDataBufInfo;
	struct _FBCD_BUF_S      ylHeadBufInfo;
} FBC_INFO_S;
//fbd
typedef struct _FBD_INFO_S
{
  unsigned int    fbd_en;
  unsigned int    fbd_format_cfg;

	struct _IMAGE_SIZE	    fbd_input_size; 

	struct _FBCD_BUF_S      yDataBufInfo;
	struct _FBCD_BUF_S      yHeadBufInfo; 

	struct _FBCD_BUF_S      uvDataBufInfo;
	struct _FBCD_BUF_S      uvHeadBufInfo; 

	struct _FBCD_BUF_S      ylDataBufInfo;
	struct _FBCD_BUF_S      ylHeadBufInfo;
} FBD_INFO_S;

typedef struct _ISP_CORE_CFG_INFO
{
//itc
	struct _ITC_INFO_S	    itcInfo;
//tpg   
	struct _TPG_INFO_S	    tpgInfo;
//blc   
	struct _BLC_INFO_S	    blcInfo;
//lsc   
	struct _LSC_INFO_S	    lscInfo;
//ae
	struct _AE_INFO_S		    aeInfo;
//awb
	struct _AWB_INFO_S	    awbInfo;
//wdr
	struct _WDR_INFO_S	    wdrInfo;
//csc
	struct _CSC_INFO_S	    cscInfo;
//ada
	struct _ADA_INFO_S	    adaInfo;
//rgbir
	struct _RGBIR_INFO_S	  rgbirInfo;
//nr2d
	struct _NR2D_INFO_S	    nr2dInfo;
//nr3d
	struct _NR3D_INFO_S	    nr3dInfo;
//enh
	struct _ENH_INFO_S	    enhInfo;
//post ctrl
	struct _POST_INFO_S	    postInfo;
//otc
	struct _OTC_INFO_S	    otcInfo;
//ldc
	struct _LDC_INFO_S	    ldcInfo;
//af
	struct _AF_INFO_S		    afInfo;
//fbc
  struct _FBC_INFO_S      fbcInfo;
//fbd
  struct _FBD_INFO_S      fbdInfo;    
}ISP_CORE_CFG_INFO;
//DS
typedef struct _ISP_OSD_INFO_S
{
  unsigned int    osd_enable;
  unsigned int    osd_type;      
  unsigned int    osd_alpha_tpye;
	IMAGE_SIZE		  osd_size;
  unsigned int    osd_rgb_addr[2];    
  unsigned int    osd_alpha_addr[2];
  unsigned int    osd_stride;       
  unsigned int    osd_alpha_stride; 
	WIN_SIZE		    osd_position_win;
  unsigned int    osd_dma_request_length;
  unsigned int    osd_dma_map;           
  unsigned int    osd_rgb_rev;           
  unsigned int    osd_global_alpha;       
  unsigned int    osd_swap_64;
  unsigned int    osd_outstanding_num;
  unsigned int    osd_bd_limit_en;
}ISP_OSD_INFO_S;

typedef struct _ISP_DS_INFO_S
{
  unsigned int    scale_en;
  //unsigned int    vscale_dstep;    
  //unsigned int    vscale_pstep;     
  unsigned int    vscale_filter_en;
  //unsigned int    hscale_dstep;     
  //unsigned int    hscale_pstep;     
  unsigned int    hscale_filter_en;
	IMAGE_SIZE		  ds_out_size;
  unsigned int    out_rgb_mode;
  unsigned int    out_rgb_en;  
  unsigned int    out_yuv_mode;
  unsigned int    out_uv_swap;
	ISP_OSD_INFO_S   osdInfo[3]; //ISP_DS_CH_OSD_NUM
}ISP_DS_INFO_S;  
//
typedef struct _ISP_DS_CFG_INFO
{
	IMAGE_SIZE 		      dsInSizeInfo;
	unsigned int        osd_rgb2yuv_coeff[3][4];
	unsigned int        osd_yuv2rgb_coeff[3][4];
	ISP_DS_INFO_S	      dsInfo[3]; //ISP_DS_CH_NUM
} ISP_DS_CFG_INFO;
//remap
typedef struct _ISP_REMAP_CFG_INFO
{
  unsigned int    LineCtlSet;
  unsigned int    LineDataSet;

  unsigned int    LineEndPosX;
  unsigned int    LineStartPosX;	
  unsigned int    LineStartPosY;
  unsigned int    LineEndPosY;

  unsigned int    LineDrawEn;
  unsigned int    VlineRightEn;
  unsigned int    VlineLeftEn; 
  unsigned int    HlineBottomEn;
  unsigned int    HlineUpEn; 

  unsigned int    LineWidthL; 
  unsigned int    LineWidthH;

  unsigned int    ValueCr;
  unsigned int    ValueCb; 
  unsigned int    ValueY;
  unsigned int    ValueAlpha;
} ISP_REMAP_CFG_INFO;
#endif
//
//void InitIsp_r2k_1920x1080_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type);
//
//void InitIsp_f2k_1920x1080_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type);
#ifdef __cplusplus
}
#endif
#endif /*_ISP_H_*/