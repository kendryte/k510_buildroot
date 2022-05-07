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
#ifndef _ISP_CORE_DRV_DEF_H_
#define _ISP_CORE_DRV_DEF_H_

#include "video/isp_com.h"

typedef struct _ISP_CORE_ITC_CTL_S
{
    unsigned int    hsync_pol;           
    unsigned int    vsync_pol;           
    unsigned int    hsync_input_timing;  
    unsigned int    vsync_input_timing;
    
    unsigned int    mirror_ctl;         
    unsigned int    video_format_ctl;   
        
} ISP_CORE_ITC_CTL_S;

typedef struct _ISP_CORE_IMAGE_ATTR_S
{
    unsigned int  image_height;       
    unsigned int  image_width;        
    unsigned int  image_v_start;      
    unsigned int  image_h_start;      
    unsigned int  image_active_width; 
    unsigned int  image_active_height; 
} ISP_CORE_IMAGE_ATTR_S;

typedef struct _ISP_CORE_TEST_CTL_S
{
    unsigned int    bayer_mode_sel;  
    unsigned int    motion_mode_sel; 
    unsigned int    test_pattern_sel;
    unsigned int    test_pattern_en;
    
    unsigned int    wdr_l_mul_data;  
    unsigned int    wdr_m_mul_data;  
    unsigned int    wdr_s_mul_data;  
  
} ISP_CORE_TEST_CTL_S;

typedef struct _ISP_CORE_BLC_CTL_S
{
    unsigned int     blc_en;     
    unsigned int    blc_offset; 
    unsigned int    blc_ratio;  
} ISP_CORE_BLC_CTL_S;

typedef struct _ISP_CORE_LSC_CTL_S
{
    unsigned int    lsc_en;           
    unsigned int    lsc_h_center;     
    unsigned int    lsc_v_center;     
    unsigned int    lsc_red_ratio;
    
    unsigned int    lsc_green_ratio;  
    unsigned int    lsc_blue_ratio;   
    unsigned int    lsc_ir_ratio;     
} ISP_CORE_LSC_CTL_S;

typedef struct _ISP_CORE_AE_CTL_S
{
    unsigned int       ae_as_en;              
    unsigned int       ae_ag_en;              
    unsigned int       ae_airis_en;           
    unsigned int       ae_enter_ls_sel;
    
    unsigned int       ae_exit_ls_sel;        
    unsigned int       ae_win_mode_sel;       
    unsigned int       ae_back_light_mode_sel;
    unsigned int       ae_day_change_en;    
    unsigned int       ae_day_change_sel;     
    
    unsigned int      ae_win_h_start;
    unsigned int      ae_win_v_start;
    unsigned int      ae_win_h_end;  
    unsigned int      ae_win_v_end;  
        
    unsigned int       ae_tar_bright;      
    unsigned int       ae_tar_bright_range;
        
    unsigned int      ae_l_ex_time;
    unsigned int      ae_m_ex_time;
    unsigned int      ae_s_ex_time;
        
    unsigned int      ae_agc;            
    unsigned int       ae_ad_shuttle_freq;
    unsigned int       ae_ad_gain_freq;
    
    unsigned int       ae_adjust_step_max;
        
    unsigned int      ae_ex_value_max;  
    unsigned int      ae_ex_value_mid;    
    unsigned int      ae_ex_value_min; 

    unsigned int      ae_gain_value_max;    
    unsigned int      ae_gain_value_mid;
    unsigned int      ae_gain_value_min;
    
    unsigned int      ae_dn_switch_ad_step_max;
    unsigned int       ae_dn_switch_wait_time;
    unsigned int       ape_max_diff;
    
    unsigned int      ape_drv_signal_max;    
        
    unsigned int       ape_coeff_distance;    
    unsigned int       ape_coeff_speed;       
    unsigned int       ape_coeff_acceleration;
        
    unsigned int      ape_drv_manual_value;  
    unsigned int      ape_damp_manual_value; 
} ISP_CORE_AE_CTL_S;

typedef struct _ISP_CORE_AE_STS_S
{ 
    unsigned int       ae_value_ready;
    unsigned int      ae_long_cur_ex;     
    unsigned int      ae_mid_cur_ex;      
    unsigned int      ae_short_cur_ex;    
    unsigned int      ae_digital_gain;    
        
    unsigned int       ave_brightness;     
    unsigned int       ae_day_night_status;
    unsigned int       ae_ex_status;       
   
    unsigned int        ae_sum;      
    unsigned int        ae_pixel_sum;
} ISP_CORE_AE_STS_S;

typedef struct _ISP_CORE_AWB_CTL_S
{
    unsigned int       awb_d65_en; 
    unsigned int       awb_ccm_en; 
    unsigned int       awb_en;     
    unsigned int       awb_mode_sel;
        
    unsigned int       awb_hist_mode_sel;
    unsigned int       awb_veri_en;      
    unsigned int       awb_fb_en;
    unsigned int       awb_value_save_en;
        
    unsigned int       awb_ccm_adp_adjust_en;
    unsigned int       awb_stab_en;          
    unsigned int      awb_d65_red_gain;
    
    unsigned int      awb_d65_blue_gain;
    unsigned int      ccm_rr_coff;
    
    unsigned int       ccm_rg_coff;
    unsigned int       ccm_rb_coff;
    unsigned int       ccm_gr_coff;
    unsigned int      ccm_gg_coff;
    unsigned int       ccm_gb_coff;
    unsigned int       ccm_br_coff;
    unsigned int       ccm_bg_coff;
    
    unsigned int      ccm_bb_coff;     
    unsigned int      ccm_correct_coff;
        
    unsigned int      awb_win_h_start;
    unsigned int      awb_win_v_start;
    unsigned int      awb_win_h_end;  
    unsigned int      awb_win_v_end;  
    
    unsigned int       awb_correct_diff_th;     
    unsigned int       awb_color_changeres_time;
    unsigned int       awb_historgram_th;
    
    unsigned int      awb_red_gain_adjust;     
    unsigned int      awb_green_gain_adjust;   
    unsigned int      awb_blue_gain_adjust;    
    unsigned int      awb_red_max_value;
    unsigned int      awb_blue_max_value;      
    unsigned int      awb_red_min_value;       
    
    unsigned int      awb_blue_min_value;
    unsigned int      awb_red_obj_value;
    unsigned int      awb_blue_obj_value;
} ISP_CORE_AWB_CTL_S;

typedef struct _ISP_CORE_AWB_STS_S
{
    unsigned int        awb_blue_hist_value;
    unsigned int      awb_blue_hist_pixel;
        
    unsigned int        awb_red_hist_value;        
    unsigned int      awb_red_hist_pixel;        
    unsigned int      awb_bypass_blue_hist_value;
        
    unsigned int      awb_bypass_blue_hist_pixel;
    unsigned int        awb_bypass_red_hist_value; 
    unsigned int      awb_bypass_red_hist_pixel;
    
    unsigned int      awb_red_value;
    unsigned int      awb_green_value;
    
    unsigned int      awb_blue_value;            
    unsigned int      awb_org_image_red_value; 
    
    unsigned int      awb_org_image_green_value;
    unsigned int      awb_org_image_blue_value;
} ISP_CORE_AWB_STS_S;

typedef struct _ISP_CORE_WDR_CTL_S
{
    unsigned int       wdr_fusion_en;      
    unsigned int       wdr_frame_sel;      
    unsigned int       wdr_adp_adjust_en;  
    unsigned int       wdr_stab_en;
    
    unsigned int       wdr_en;             
    unsigned int       wdr_ghost_remove_en; 
    unsigned int       wdr_3_frame_out_mode;
    unsigned int       wdr_mode_sel;
    
    unsigned int       wdr_2frame_ex_ratio;
    unsigned int       wdr_3frame_ex_ratio; 
    unsigned int       wdr_stat_img_sel;   
    unsigned int       wdr_ltm_data_sel;
    
    unsigned int       wdr_tz_data_sel;
    unsigned int       wdr_remove_purple_en;
    unsigned int       wdr_over_ex_ratio_th1;
    
    unsigned int       wdr_over_ex_ratio_th2;
    unsigned int       wdr_fusion_ratio_th;
    
    unsigned int       wdr_fusion_value1;  
    unsigned int       wdr_fusion_value2;
}ISP_CORE_WDR_CTL_S;

typedef struct _ISP_CORE_CSC_CTL_S
{
    unsigned int    csc_r2y_00;
    unsigned int    csc_r2y_01;
    unsigned int    csc_r2y_02;
    unsigned int    csc_r2y_10;
    unsigned int    csc_r2y_11;
    unsigned int    csc_r2y_12;
    unsigned int    csc_r2y_20;
    unsigned int    csc_r2y_21;
    unsigned int    csc_r2y_22;
} ISP_CORE_CSC_CTL_S;

typedef struct _ISP_CORE_ADA_CTL_S
{
    unsigned int       ada_rgb_gamma_en; 
    unsigned int       ada_yuv_gamma_en; 
    unsigned int       ada_adjust_en;    
    unsigned int       ada_img_stab_en;
    
    unsigned int       ada_ccr_en;       
    unsigned int       ada_adp_en;       
    unsigned int       ada_adp_ccr_en;   
    unsigned int       ada_stat_mode_sel;
        
    unsigned int       ada_enh_mode_sel;
    unsigned int       ada_stat_max_value; 
    unsigned int       ada_ad_stren_max_value;
     
    unsigned int      ada_win_h_start;
    unsigned int      ada_win_v_start;
    unsigned int      ada_win_h_end;  
    unsigned int      ada_win_v_end;  

} ISP_CORE_ADA_CTL_S;

typedef struct _ISP_CORE_RGBIR_CTL_S
{
    unsigned int    rgbir_en;        
    unsigned int    rgbir_rtf_en;    
    unsigned int    rgbir_rpc_en;    
    unsigned int    rgbir_fusion_en;
    
    unsigned int    rgbir_output_sel;
 
    unsigned int  rgbir_rpc_max_value; 
    unsigned int   rgbir_rpc_color_coff;
    unsigned int   rgbir_rpc_luma_coff; 
    
    unsigned int  rgbir_rpc_th;       
    unsigned int  rgbir_rpc_th1;      
} ISP_CORE_RGBIR_CTL_S;

typedef struct _ISP_CORE_2DNR_CTL_S
{
    unsigned int   core_2dnr_pcf_en;       
    unsigned int   core_2dnr_raw_en;       
    unsigned int   core_2dnr_edge_en;      
    unsigned int   core_2dnr_bap_en;       
    
    unsigned int   core_2dnr_luma_en;      
    unsigned int   core_2dnr_chroma_en;    
    unsigned int   core_2dnr_pcf_adp_en;   
    unsigned int   core_2dnr_raw_adp_en;   
    
    unsigned int   core_2dnr_luma_adp_en;  
    unsigned int   core_2dnr_chroma_adp_en;
    unsigned int   core_2dnr_raw_intensity;
    unsigned int  core_2dnr_bap_intensity;

    unsigned int  core_2dnr_edge_intensity;
    unsigned int   core_2dnr_luma_intensity;
    unsigned int   core_2dnr_chroma_intensity;
} ISP_CORE_2DNR_CTL_S;

typedef struct _ISP_CORE_3DNR_CTL_S
{
    unsigned int    core_3dnr_en;            
    unsigned int    core_3dnr_pre_luma_en;  
    unsigned int    core_3dnr_pre_chroma_en; 
    unsigned int    core_3dnr_main_luma_en;
    
    unsigned int    core_3dnr_main_chroma_en;
    unsigned int    core_3dnr_post_luma_en;  
    unsigned int    core_3dnr_post_chroma_en;
    unsigned int    core_3dnr_2d_luma_en;
    
    unsigned int    core_3dnr_2d_chroma_en;  
    unsigned int    core_3dnr_wb_en;         
    unsigned int    core_3dnr_wb_sel;
    unsigned int    core_3dnr_adp_luma_en;
    
    unsigned int    core_3dnr_adp_chroma_en;
    unsigned int    core_3dnr_pre_luma_th;        
    unsigned int    core_3dnr_pre_luma_intensity;   
    unsigned int    core_3dnr_pre_chroma_intensity;
    
    unsigned int   core_3dnr_mid_filter_th;
    unsigned int   core_3dnr_pre_mid_filter_th;    
    unsigned int   core_3dnr_cur_mid_filter_th;    
    unsigned int  core_3dnr_low_pass_filter_th;
    unsigned int   core_3dnr_luma_th;             
    unsigned int   core_3dnr_min_value;
    unsigned int   core_3dnr_luma_intensity;
    
    unsigned int   core_3dnr_chroma_intensity;    
    unsigned int   core_3dnr_post_edge_th;        
    unsigned int   core_3dnr_post_luma_intensity;  
    unsigned int   core_3dnr_post_chroma_intensity;

} ISP_CORE_3DNR_CTL_S;

typedef struct _ISP_CORE_ENH_CTL_S
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
    unsigned int   enh_th1;
    unsigned int   enh_th2;
    unsigned int    sharp_gain;     
} ISP_CORE_ENH_CTL_S;

typedef struct _ISP_CORE_POST_CTL_S
{ 
    unsigned int    post_cont_ad_en;   
    unsigned int    post_luma_ad_en;   
    unsigned int    post_satu_ad_en;   
//    unsigned int    post_otc_en;   
    unsigned int    cont_ad_intensity;
    
    unsigned int    luma_ad_intensity;
    unsigned int    satu_ad_intensity;

} ISP_CORE_POST_CTL_S;

typedef struct _ISP_CORE_OTC_CTL_S
{
    unsigned int    post_otc_en;  
    unsigned int    otc_yc_sel;        
    unsigned int    otc_uv_format_sel; 
    unsigned int    otc_hsync_pol_sel; 
    unsigned int    otc_vsync_pol_sel;
    
    unsigned int    otc_stt_vr;   
    unsigned int    otc_stt_hr;   
    unsigned int    otc_height;   
    unsigned int    otc_width;   
} ISP_CORE_OTC_CTL_S;

typedef struct _ISP_CORE_LDC_CTL_S
{
    unsigned int       ldc_en;          
    unsigned int       ldc_arith_en;   
    unsigned int       ldc_req_freq;   
    
    unsigned int      ldc_stt_ln;
    unsigned int      ldc_h_center_pos;
    
    unsigned int      ldc_v_center_pos;
    unsigned int      ldc_rectify_cr; 
    
    unsigned int      ldc_rectify_cz;    
} ISP_CORE_LDC_CTL_S;

typedef struct _ISP_CORE_AF_CTL_S
{
    unsigned int    af_stat_en;          
    unsigned int    af_stat_mode_sel; 

    unsigned int  af_stat_win_h_start;    
    unsigned int  af_stat_win_v_start; 
    unsigned int  af_stat_win_h_end;  
    unsigned int  af_stat_win_v_end;  

} ISP_CORE_AF_CTL_S;

typedef struct _ISP_CORE_AF_STS_S
{        
    unsigned int  af_mid_frq_data;    
    unsigned int  af_high_frq_data;   
    unsigned int  af_stat_pixel_num;  
} ISP_CORE_AF_STS_S;

typedef struct _ISP_CORE_RAM_WR_STATUS_S
{
    unsigned int    gamma_grb_table_cfg;
    unsigned int    gamma_yuv_table_cfg;

    unsigned int    wdr_l3_table_cfg;   
    unsigned int    wdr_m3_table_cfg;    
    unsigned int    wdr_s3_table_cfg; 

    unsigned int    wdr_l2_table_cfg;   
    unsigned int    wdr_s2_table_cfg;   
      
} ISP_CORE_RAM_WR_STATUS_S;

typedef struct _ISP_CORE_RAM_RD_STATUS_S
{
    unsigned int    gamma_grb_table;  
    unsigned int    gamma_yuv_table;  
    unsigned int    wdr_l3_table;     
    unsigned int    wdr_m3_table;
    
    unsigned int    wdr_s3_table;     
    unsigned int    wdr_l2_table;     
    unsigned int    wdr_s2_table;     
    unsigned int    ram_ready_status;
    
    unsigned int    hist_ready_status;
    unsigned int    ram_ready_lock;    
} ISP_CORE_RAM_RD_STATUS_S;

typedef struct _ISP_CORE_ATRR_S
{
    ISP_CORE_ITC_CTL_S stItcCtl;
    ISP_CORE_IMAGE_ATTR_S stImageAttr;
    ISP_CORE_TEST_CTL_S stTestCtl;
    ISP_CORE_BLC_CTL_S stBlcCtl;
    ISP_CORE_LSC_CTL_S stLscCtl;
    ISP_CORE_AE_CTL_S stAeCtl;
    ISP_CORE_AE_STS_S stAeSts;
    ISP_CORE_AWB_CTL_S stAwbCtl;
    ISP_CORE_AWB_STS_S stAwbSts;
    ISP_CORE_WDR_CTL_S stWdrCtl;
    ISP_CORE_CSC_CTL_S stCscCtl;
    ISP_CORE_ADA_CTL_S stAdaCtl;
    ISP_CORE_RGBIR_CTL_S stRgbirCtl;
    ISP_CORE_2DNR_CTL_S st2dnrCtl;
    ISP_CORE_3DNR_CTL_S st3dnrCtl;
    ISP_CORE_ENH_CTL_S stEnhCtl;
    ISP_CORE_POST_CTL_S stPostCtl;
    ISP_CORE_OTC_CTL_S  stOtcCtl;   
    ISP_CORE_LDC_CTL_S stLdcCtl;
    ISP_CORE_RAM_WR_STATUS_S stRamWrStatus;
    ISP_CORE_RAM_RD_STATUS_S stRamRdStatus;
    ISP_CORE_AF_CTL_S stAfCtl;
    ISP_CORE_AF_STS_S stAfSts;
} ISP_CORE_ATRR_S;

//
int ISP_DRV_CORE_GetAeSts(ISP_CORE_AE_STS_S *pAeSts);
int ISP_DRV_CORE_GetAwbSts(ISP_CORE_AWB_STS_S *pAwbSts);
int ISP_DRV_CORE_GetAfSts(ISP_CORE_AF_STS_S *pgtAfSts);;
int ISP_DRV_CORE_GetAeLongCurEx(void);
int ISP_DRV_CORE_GetAeCurDigitalGain(void);
//
int ISP_DRV_CORE_SetRamWrStatus(unsigned int data);
int ISP_DRV_CORE_GetRamRdStatus(void);
//
int ISP_DRV_SetCore(ISP_CORE_ATRR_S *pstCoreAttr,SENSOR_TYPE sensor_type);
//debug
int ISP_DRV_GetCoreRegsVal(void);
#endif /* _ISP_CORE_DRV_DEF_H_ */
