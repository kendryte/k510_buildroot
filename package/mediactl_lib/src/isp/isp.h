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

#include <linux/videodev2.h>

#include "../media/mediactl-priv.h"
#include "isp_com.h"
#include "vi.h"
#include "mipi_csi2.h"

enum _ISP_OUT_CHL_SEL{
    MAIN_OUT,
    DS0_OUT,
    DS1_OUT,
    DS2_OUT,
};

enum _ISP_IN_CH_MODE{
    BT656,
    BT1120_MIPI,
};
//wrap
struct isp_wrap_wdr_info
{
  //ISP_PIPE_WDR_MODE_E 	wdr_mode ;
  unsigned int    wdr_mode;
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
};

struct isp_wrap_3dnr_info
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
};

struct isp_wrap_ldc_info
{
   unsigned int   ldc_en;
   unsigned int   ldc_y_buf_base; 
   unsigned int   ldc_uv_buf_base; 
   unsigned int   ldc_line_stride; 
   unsigned int   ldc_frame_buf_size;     
};

struct isp_wrap_main_info
{
  unsigned int 	  main_out_en;
	struct image_size_s	main_size;
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
};

struct isp_wrap_ds0_info
{
  unsigned int 	  ds0_out_en;
  unsigned int 	  ds0_osd0_en ;   
  unsigned int 	  ds0_osd1_en ; 
  unsigned int 	  ds0_osd2_en ;
  unsigned int    pix_remap_out0_en;		 		
	struct image_size_s		  ds0_size;
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
};

struct isp_wrap_ds1_info
{
  unsigned int 	  ds1_out_en;
  unsigned int 	  ds1_osd0_en ;   
  unsigned int 	  ds1_osd1_en ; 
  unsigned int 	  ds1_osd2_en ;
  unsigned int    pix_remap_out1_en;		 		
	struct image_size_s		  ds1_size;
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
};

struct isp_wrap_ds2_info
{
  unsigned int 	  ds2_out_en;
  unsigned int 	  ds2_osd0_en ;   
  unsigned int 	  ds2_osd1_en ; 
  unsigned int 	  ds2_osd2_en ; 	 		
	struct image_size_s		  ds2_size;
  unsigned int    ds2_video_height;
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
};

struct isp_wrap_dma_info
{
	unsigned int    dma_wr_data_mode;
	unsigned int    dma_wr_out_swap;
};

struct isp_wrap_intcore_info
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
};
 
struct isp_wrap_intwr0_info
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
};

struct isp_wrap_intwr1_info
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
};

struct isp_wrap_intrd0_info
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
};

struct isp_wrap_int_info
{
  struct isp_wrap_intcore_info intCoreEn;
  struct isp_wrap_intwr0_info  intWr0En;
  struct isp_wrap_intwr1_info  intWr1En;
  struct isp_wrap_intrd0_info  intRd0En;    
};

struct isp_wrap_cfg_info
{
	unsigned int	              isp_out_sel;
	unsigned int                dvp_ch_mode;
  unsigned int                hist_3a_out_en;
	struct isp_wrap_wdr_info    wdrInfo;
	struct isp_wrap_3dnr_info   nr3dInfo;
	struct isp_wrap_ldc_info    ldcInfo;
	struct isp_wrap_main_info	  mainInfo;
	struct isp_wrap_ds0_info	  ds0Info;
	struct isp_wrap_ds1_info	  ds1Info;
	struct isp_wrap_ds2_info	  ds2Info;
};
//core
typedef enum _ISP_SYNC_POLARITY_E
{
	ISP_SYNC_POL_LOW = 0,
	ISP_SYNC_POL_HIGH = 1,
	ISP_SYNC_POL_BUTT,
} ISP_SYNC_POLARITY_E;

enum ISP_HSYNC_GEN_MODE_E
{
	HSYNC_BASE_ON_INPUT_GEN_BY_ISP = 0,
	HSYNC_BASE_ON_INPUT = 1,
	HSYNC_GEN_BY_ISP_IN_FIELD_BLANK = 2,
	HSYNC_GEN_BY_ISP = 3,
	ISP_HSYNC_BUTT
};

enum ISP_VSYNC_GEN_MODE_E
{
	VSYNC_GEN_BY_ISP = 0,
	VSYNC_BASE_ON_INPUT = 1,
	ISP_VSYNC_BUTT
};

enum ISP_VIDEO_FORMAT_E
{
	ISP_RGBRAW_DATA = 0,
	ISP_YUV_DATA = 1,
	ISP_VIDEO_FORMAT_BUTT
};

enum ISP_YUV_FOTMAT_E
{
    IN_YUV422,
    IN_YUV420,
};

enum ISP_RGB_OUTPUT_FOTMAT_E
{
    OUT_S_RGB,
    OUT_ARGB,
};

enum ISP_YUV422_PIXEL_ORDER_E
{
    YUYV,
    YVYU,
    UYVY,
    VYUY,
};

enum ISP_PIXEL_ORDER_E
{
    PIXEL_8,
    PIXEL_10,
    PIXEL_12,
    PIXEL_14,
    PIXEL_16,
    PIXEL_18,
    PIXEL_20,
    PIXEL_24,
};

enum ISP_AE_LOCK_STS_E
{
	AE_LOCK_32FRAME = 0,
	AE_LOCK_64FRAME = 1,
};

enum ISP_AE_WIN_SEL_E
{
	AE_WHOLE_PIC = 0,
	AE_CENTRL_AREA = 1,
  AE_CENTRL_WEIGHTED = 2,
};

enum ISP_AE_MD_SEL_E
{
	AE_NORMAL_MODE = 0,
	AE_BACKLIGHT_COMP = 1,
  AE_STRONGLIGHT_SUPP = 2,
};

enum ISP_AE_DN_SEL_E
{
	AE_DAY = 0,
	AE_NIGHT = 1,
};

enum ISP_AWB_SL_E
{
	AWB_HANDLE = 0,
	AWB_AUTO = 1,
};

enum ISP_AWB_WIN_SL_E
{
	AWB_FULL_IMG = 0,
	AWB_LMT_IMG = 1,
};

enum ISP_AWB_FB_MODE_E
{
	AWB_THROUGH_MODE = 0,
	AWB_FEEDBACK_MODE = 1,
};

enum ISP_WDR_OUT_SEL_E
{
	WDR_L_EX_OUT = 0,
	WDR_S_EX_OUT = 1,
};

enum ISP_WDR_2F_EX_RATIO_E
{
	WDR_EX_RATIO_16F = 0,
	WDR_EX_RATIO_32F = 1,
  WDR_EX_RATIO_64F = 2,
};

enum ISP_WDR_3F_EX_RATIO_E
{
	WDR_EX_RATIO_16_4 = 0,
	WDR_EX_RATIO_32_8 = 1,
  WDR_EX_RATIO_16_16 = 2,
};

enum ISP_WDR_STS_SEL_E
{
	WDR_S_EC_FRAME = 0,
	WDR_M_EC_FRAME = 1,
  WDR_L_EC_FRAME = 2,
};

enum ISP_OTC_YC_SEL_E
{
	OTC_Y_MSB_C_LSB = 0,
	OTC_C_MSB_Y_LSB = 1,
};

enum ISP_OTC_YUV422_FMT_E
{
	OTC_UV = 0,
	OTC_VU = 1,
};

enum ISP_OTC_POLARITY_E
{
	OTC_POSITIVE = 0,
	OTC_NEGATIVE = 1,
};

enum ISP_AF_STS_MD_E
{
	AF_FULL_IMG = 0,
	AF_IN_WINDOW = 1,
  AF_IN_75PER_WINDOW = 2,
  AF_IN_94PER_WINDOW = 3,
};

enum ISP_MFBC_OUT_E
{
	MFBC_OUT_422_EN = 0,
	MFBC_OUT_420_EN = 1,
};

struct crop_info_s{
	unsigned int    width_st;
	unsigned int    height_st;	
	unsigned int    width;
	unsigned int    height;	
};

struct win_size_s{
	unsigned int    v_start;
	unsigned int    h_start;	
	unsigned int    v_end;
	unsigned int    h_end;	
};
//itc
struct itc_info_s
{
 	unsigned int    hsync_pol;
	unsigned int    vsync_pol;
	unsigned int    hsync_input_timing;
	unsigned int    vsync_input_timing;   
	unsigned int    flip_ctl;         
  unsigned int    video_fmt_sel;
  struct image_size_s	total_size;
  struct crop_info_s  itc_size;
};
//tpg
struct tpg_info_s
{
  unsigned int    tpg_en;
	unsigned int    tpg_sel;
  unsigned int    bayer_mode_sel;  
  unsigned int    motion_mode_sel;    
  unsigned int    wdr_l_mul_data;  
  unsigned int    wdr_m_mul_data;  
  unsigned int    wdr_s_mul_data;
};
//blc
struct blc_info_s
{
	unsigned int    blc_en;     
  unsigned int    blc_offset; 
  unsigned int    blc_ratio;
};
//lsc
struct lsc_info_s
{
  unsigned int    lsc_en;           
  unsigned int    lsc_h_center;     
  unsigned int    lsc_v_center;     
  unsigned int    lsc_r_ratio;    
  unsigned int    lsc_g_ratio;  
  unsigned int    lsc_b_ratio;   
  unsigned int    lsc_ir_ratio; 
};
//ae
struct ae_info_s
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
	  struct win_size_s  ae_win_size;
    
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
};
//awb
struct awb_info_s
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
        
	  struct win_size_s	      awb_win_size; 
    
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
};
//wdr
struct wdr_Info_s
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
};
//csc
struct csc_info_s
{
	 unsigned int    csc_r2y[3][3];
};
//ADA
struct ada_info_s
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
     
	  struct win_size_s	      ada_win_size;
};
//rgbir
struct rgbir_info_s
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
};
//nr2d
struct nr2d_info_s
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
};
//nr3d
struct nr3d_info_s
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
};
//enh
struct enh_info_s
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
};
//post
struct post_info_s
{
    unsigned int    post_cont_ad_en;   
    unsigned int    post_luma_ad_en;   
    unsigned int    post_satu_ad_en;   
    unsigned int    cont_ad_intensity;    
    unsigned int    luma_ad_intensity;
    unsigned int    satu_ad_intensity; 
};
//otc
struct otc_info_s
{
    unsigned int    post_otc_en;  
    unsigned int    otc_yc_sel;        
    unsigned int    otc_uv_format_sel; 
    unsigned int    otc_hsync_pol_sel;
    unsigned int    otc_vsync_pol_sel;
	  struct crop_info_s 		  otc_out_size; 	 
};
//ldc
struct ldc_info_s
{
	  unsigned int    ldc_en;     
    unsigned int    ldc_arith_en;   
    unsigned int    ldc_req_freq;   
    
    unsigned int    ldc_stt_ln;
    unsigned int    ldc_h_center_pos;
    
    unsigned int    ldc_v_center_pos;
    unsigned int    ldc_rectify_cr; 
    
    unsigned int    ldc_rectify_cz; 
};
//af
struct af_info_s
{
  unsigned int    af_stat_en;          
  unsigned int    af_stat_mode_sel; 
	struct win_size_s		    af_win_size; 
};
//isp 3dnr fbcd
struct fbcd_buf_s
{
	unsigned int    data_buf_base0;
	unsigned int    data_buf_base1;	
	unsigned int    data_stride;
	unsigned int    data_wr_blen;
};
//fbc
struct fbc_info_s
{
  unsigned int    fbc_out_format_cfg;
    
	struct image_size_s	    fbc_input_size; 

	struct fbcd_buf_s      yDataBufInfo;
	struct fbcd_buf_s      yHeadBufInfo;

	struct fbcd_buf_s      uvDataBufInfo;
	struct fbcd_buf_s      uvHeadBufInfo;

	struct fbcd_buf_s      ylDataBufInfo;
	struct fbcd_buf_s      ylHeadBufInfo;
};
//fbd
struct fbd_info_s
{
  unsigned int    fbd_en;
  unsigned int    fbd_format_cfg;

	struct image_size_s	   fbd_input_size; 

	struct fbcd_buf_s      yDataBufInfo;
	struct fbcd_buf_s      yHeadBufInfo; 

	struct fbcd_buf_s      uvDataBufInfo;
	struct fbcd_buf_s      uvHeadBufInfo; 

	struct fbcd_buf_s      ylDataBufInfo;
	struct fbcd_buf_s      ylHeadBufInfo;
};

struct isp_core_cfg_info
{
//itc
	struct itc_info_s   itcInfo;
//tpg   
	struct tpg_info_s   tpgInfo;
//blc   
	struct blc_info_s   blcInfo;
//lsc    
	struct lsc_info_s   lscInfo;
//ae
	struct ae_info_s    aeInfo;
//awb
	struct awb_info_s   awbInfo;
//wdr
	struct wdr_Info_s   wdrInfo;
//csc
	struct csc_info_s   cscInfo;
//ada
	struct ada_info_s   adaInfo;
//rgbir
	struct rgbir_info_s rgbirInfo;
//nr2d
	struct nr2d_info_s  nr2dInfo;
//nr3d
	struct nr3d_info_s  nr3dInfo;
//enh
	struct enh_info_s   enhInfo;
//post ctrl
	struct post_info_s  postInfo;
//otc
	struct otc_info_s   otcInfo;
//ldc
	struct ldc_info_s   ldcInfo;
//af
	struct af_info_s    afInfo;
//fbc
  struct fbc_info_s   fbcInfo;
//fbd
  struct fbd_info_s   fbdInfo;    
};
//DS
struct isp_osd_info_s
{
  unsigned int    osd_enable;
  unsigned int    osd_type;      
  unsigned int    osd_alpha_tpye;
	struct image_size_s		  osd_size;
  unsigned int    osd_rgb_addr[2];    
  unsigned int    osd_alpha_addr[2];
  unsigned int    osd_stride;       
  unsigned int    osd_alpha_stride; 
	struct win_size_s		    osd_position_win;
  unsigned int    osd_dma_request_length;
  unsigned int    osd_dma_map;           
  unsigned int    osd_rgb_rev;           
  unsigned int    osd_global_alpha;       
  unsigned int    osd_swap_64;
  unsigned int    osd_outstanding_num;
  unsigned int    osd_bd_limit_en;
};

struct isp_ds_info_s
{
  unsigned int    scale_en;  
  unsigned int    vscale_filter_en;   
  unsigned int    hscale_filter_en;
	struct image_size_s		  ds_out_size;
  unsigned int    out_rgb_mode;
  unsigned int    out_rgb_en;  
  unsigned int    out_yuv_mode;
  unsigned int    out_uv_swap;
	struct isp_osd_info_s  osdInfo[3]; //ISP_DS_CH_OSD_NUM
};  
//
struct isp_ds_cfg_info
{
	struct image_size_s 	dsInSizeInfo;
	unsigned int          osd_rgb2yuv_coeff[3][4];
	unsigned int          osd_yuv2rgb_coeff[3][4];
	struct isp_ds_info_s	dsInfo[3]; //ISP_DS_CH_NUM
};
//remap
struct isp_remap_cfg_info
{
  unsigned int    DrawAreaNum;
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
};

struct isp_cfg_info
{
	struct isp_wrap_cfg_info  isp_wrap_cfg;
	struct isp_core_cfg_info  isp_core_cfg;
	struct isp_ds_cfg_info	  isp_ds_cfg;
};

struct isp_fbcd_cfg_info
{
  unsigned int fbcd_addr;
};
//
int mipicsi2_cfg(struct media_entity *entity,struct isp_csi2_info *mipi_csi2);
int isp_vi_cfg(struct media_entity *entity,struct vi_cfg_info *vi_cfg);
int isp_f2k_cfg(struct media_entity *entity,struct isp_cfg_info *isp_cfg,uint32_t phyAddr);
int isp_r2k_cfg(struct media_entity *entity,struct isp_cfg_info *isp_cfg,uint32_t phyAddr);
//
int sysctl_rst_mipicsi2(struct media_entity *entity);
int sysctl_rst_vi(struct media_entity *entity);
int sysctl_rst_f2k(struct media_entity *entity);
int sysctl_rst_r2k(struct media_entity *entity);
//
void print_csi2_info(struct isp_csi2_info *mipi_csi2);
void print_vi_info(struct vi_cfg_info *vi_cfg);
void print_isp_info(struct isp_cfg_info *isp_cfg);
#endif /*_ISP_H_*/