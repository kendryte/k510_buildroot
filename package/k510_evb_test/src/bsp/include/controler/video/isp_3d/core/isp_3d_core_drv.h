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

#ifndef _ISP_3D_CORE_DRV_DEF_H_
#define _ISP_3D_CORE_DRV_DEF_H_

typedef struct _TOF_CORE_ITC_ATTR_S
{    
    unsigned char    hsync_pol;
    unsigned char    vsync_pol;
    unsigned char    hsync_input_timing;
    unsigned char    vsync_input_timing;
    unsigned char    itc_sl;
    
    unsigned short   tof_itc_height;
    unsigned short   tof_itc_width;
    unsigned short   tof_itc_v_start;
    unsigned short   tof_itc_h_start;
    unsigned short   tof_itc_active_width;
    unsigned short   tof_itc_active_height;
    unsigned int     tof_itc_active_start_line;
} TOF_CORE_ITC_ATTR_S;

typedef enum _TOF_DRV_SENSOR_TYPE_E
{
    TOF_SENSOR_TYPE_TOF = 0,
    TOF_SENSOR_TYPE_INFRADE = 1,
    TOF_SENSOR_TYPE_BUTT
}TOF_DRV_SENSOR_TYPE_E;

typedef struct _TOF_CORE_GEN_ATTR_S
{
    unsigned char   tof_gray_sel;
    unsigned char   tof_dm_sel;
    unsigned char   tof_sensor_sel;
    unsigned char   tof_depth_pol_sel;
    unsigned short  tof_pwm_order_cfg;
    unsigned short  tof_cwm_order_cfg;
} TOF_CORE_GEN_ATTR_S;

typedef struct _TOF_CORE_GRAY_TH_ATTR_S
{
    unsigned int   tof_gray_th;
} TOF_CORE_GRAY_TH_ATTR_S;

typedef struct _TOF_CORE_AE_ATTR_S
{
    unsigned char       ae_as_en;
    unsigned char       ae_ag_en;
    unsigned char       ae_airis_en;
    unsigned char       ae_enter_lock_sel;

    unsigned char       ae_exit_lock_sel;
    unsigned char       ae_win_mode_sel;
    unsigned char       ae_back_light_mode_sel;
    unsigned char       reserved0;

    unsigned short      ae_win_h_start;
    unsigned short      ae_win_v_start;
    unsigned short      ae_win_h_end;
    unsigned short      ae_win_v_end;

    unsigned short      ae_tar_bright;
    unsigned short      ae_tar_bright_range;
    unsigned short      ae_ex_time;
    unsigned short      ae_agc;
    
    unsigned short      ae_ad_freq;
    unsigned short      ae_ad_step_max;

    unsigned short      ae_ex_value_max;
    unsigned short      ae_ex_value_mid;
    unsigned short      ae_ex_value_min;
    
    unsigned short      ae_gain_value_max;
    unsigned short      ae_gain_value_mid;
    unsigned short      ae_gain_value_min;

} TOF_CORE_AE_ATTR_S;


typedef struct _TOF_CORE_NR2D_ATTR_S
{
    unsigned char   tof_gray_dpc_en;
    unsigned char   tof_depth_dpc_en;
    unsigned char   tof_2dnr_gray_en;
    unsigned char   tof_2dnr_depth_en;
    unsigned short  tof_2dnr_gray;
    unsigned short  tof_2dnr_depth;
} TOF_CORE_NR2D_ATTR_S;

typedef struct _TOF_CORE_POST_ATTR_S
{
    unsigned char   tof_output_sel;
    unsigned char   tof_hsync_pol_sel;
    unsigned char   tof_vsync_pol_sel;
    unsigned char   tof_gray_gmma_en;
    unsigned char   tof_depth_cont_ad_en;
    
    unsigned char   tof_gray_cont_en;
    unsigned char   tof_gray_luma_ad_en;
    
    unsigned char   tof_cont_ad_intensity;
    unsigned char   tof_luma_ad_intensity;
    unsigned char   tof_Depth_cont_ad_intensity;
} TOF_CORE_POST_ATTR_S;

typedef struct _TOF_CORE_RAM_WR_STATUS_S
{
    unsigned char   gamma_grb_table_cfg;
} TOF_CORE_RAM_WR_STATUS_S;

typedef struct _TOF_CORE_RAM_RD_STATUS_S
{
    unsigned char   gamma_grb_table;
} TOF_CORE_RAM_RD_STATUS_S;

typedef struct _TOF_CORE_ATTR_S
{
    TOF_DRV_SENSOR_TYPE_E eSensorType;
    TOF_CORE_ITC_ATTR_S stItcAttr;
    TOF_CORE_GEN_ATTR_S stGenAttr;
    TOF_CORE_GRAY_TH_ATTR_S stGrayTHAttr;
    TOF_CORE_AE_ATTR_S stAeAttr;
    TOF_CORE_NR2D_ATTR_S stNr2dAttr;
    TOF_CORE_POST_ATTR_S stPostAttr;
} TOF_CORE_ATTR_S;

int TOF_DRV_Core_Remap(void);
int TOF_DRV_CORE_SetRamWrStatus(unsigned int data);
unsigned int TOF_DRV_CORE_GetRamRdDone(void);
int TOF_DRV_setCore(TOF_CORE_ATTR_S *tofCoreAttr);
//DEBUG
int TOF_DRV_GetCoreRegsVal(void);
#endif /*_ISP_3D_CORE_DRV_DEF_H_*/
