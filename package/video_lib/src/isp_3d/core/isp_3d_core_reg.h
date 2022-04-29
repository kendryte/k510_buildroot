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

/*
 * isp_3d_core_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _ISP_3D_CORE_REG_H_
#define _ISP_3D_CORE_REG_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_hsync_pol                  : 1   ; /* [0 ]      */
        unsigned int    tof_vsync_pol                  : 1   ; /* [1 ]      */
        unsigned int    tof_hsync_input_timing         : 2   ; /* [3 ..2 ]  */
        unsigned int    tof_vsync_input_timing         : 1   ; /* [4 ]      */
        unsigned int    tof_itc_sel                    : 2   ; /* [6..5*/
        unsigned int    reserved0                      : 25  ; /* [31..7 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_height                 : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_HEIGHT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_width                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_WIDTH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_vstart                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_VSTART;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_hstart                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_HSTART;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_active_width           : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20   ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_ACTIVE_WIDTH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_active_height          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_ACTIVE_HEIGHT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_itc_active_start_line      : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_ITC_ACTIVE_START_LINE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_sensor_sel                 : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_SENSOR_SEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_gray_sel                   : 1   ; /* [0 ]      */
        unsigned int    tof_dm_sel                     : 1   ; /* [1 ]      */
        unsigned int    tof_sensor_sel                 : 1   ; /* [2 ]      */
        unsigned int    tof_depth_pol_sel              : 1   ; /* [3 ]      */
        unsigned int    tof_pwm_order_cfg              : 2   ; /* [5 ..4 ]  */
        unsigned int    tof_back_light_remove          : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7 ]      */
        unsigned int    tof_cwm_order_cfg              : 2   ; /* [9 ..8 ]  */
        unsigned int    reserved1                      : 22  ; /* [31..10 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_GEN_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_gray_th                    : 12   ; /* [11..0 ]      */
        unsigned int    reserved1                      : 20  ; /* [31..12 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_GRAY_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_as_en                   : 1   ; /* [0 ]      */
        unsigned int    tof_ae_ag_en                   : 1   ; /* [1 ]      */
        unsigned int    tof_ae_airis_en                : 1   ; /* [2 ]      */
        unsigned int    reserved0                      : 1   ; /* [3 ]      */
        unsigned int    tof_ae_enter_lock_sel          : 1   ; /* [4 ]      */
        unsigned int    tof_ae_exit_lock_sel           : 1   ; /* [5 ]      */
        unsigned int    reserved1                      : 2   ; /* [7 ..6 ]  */
        unsigned int    tof_ae_win_mode_sel            : 2   ; /* [9 ..8 ]  */
        unsigned int    tof_ae_back_light_mode_sel     : 2   ; /* [11..10]  */
        unsigned int    reserved2                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_win_hstart             : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_WIN_HSTART;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_win_vstart             : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_WIN_VSTART;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_win_h_end               : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_WIN_H_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_win_v_end               : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_WIN_V_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_tar_bright              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_TAR_BRIGHT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_tar_bright_range        : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_TAR_BRIGHT_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ex_time                 : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_EX_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_agc                     : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_AGC;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ad_freq                 : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 28   ; /* [31 ..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_AD_FREQ;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ad_step_max             : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_AD_STEP_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ex_value_max            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_EX_VALUE_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ex_value_mid            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_EX_VALUE_MID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ex_value_min            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_EX_VALUE_MIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_gain_value_max          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_GAIN_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_gain_value_mid      : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_GAIN_MID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_gain_value_min          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_GAIN_MIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_value_ready             : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_VALUE_READY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_long_cur_ex             : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_LONG_CUR_EX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_aehort_cur_ex            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_SHORT_CUR_EX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_digital_gain            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_CUR_DIGITAL_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_ave_brightness          : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_CUR_AVE_BRIGHTNESS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_extatus               : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_EX_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_aeum                     : 20  ; /* [19..0 ]  */
        unsigned int    reserved0                      : 12  ; /* [31..20]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_SUM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ae_pixelum               : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_AE_PIXEL_SUM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_gray_dpc_en                : 1   ; /* [0 ]      */
        unsigned int    tof_depth_dpc_en               : 1   ; /* [1 ]      */
        unsigned int    tof_2dnr_gray_en              : 1   ; /* [2 ]      */
        unsigned int    tof_2dnr_depth_en             : 1   ; /* [3 ]      */
        unsigned int    reserved0                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_2DNR_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_2dnr_gray                  : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_2DNR_GRAY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_2dnr_depth                 : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_2DNR_DEPTH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_output_sel                 : 2   ; /* [1 ..0 ]  */
        unsigned int    tof_hsync_pol_sel              : 1   ; /* [2 ]      */
        unsigned int    tof_vsync_pol_sel              : 1   ; /* [3 ]      */
        unsigned int    tof_gray_gmma_en               : 1   ; /* [4 ]      */
        unsigned int    tof_gray_cont_en               : 1   ; /* [5 ]      */
        unsigned int    tof_gray_luma_ad_en            : 1   ; /* [6 ]      */
        unsigned int    tof_depth_cont_ad_en           : 1   ; /* [7 ]      */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_POST_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_cont_ad_intensity          : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_CONT_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_luma_ad_intensity          : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_LUMA_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_satu_ad_intensity          : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_SATU_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gamma_grb_table_cfg            : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_RAM_WR_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gamma_grb_table                : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 8   ; /* [8 ..1 ]  */
        unsigned int    reserved1                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_RAM_RD_STATUS;


//ITC
#define  TOF_CORE_ITC_CTL     				(0x0000)
#define  TOF_CORE_ITC_HEIGHT     			(0x0004)
#define  TOF_CORE_ITC_WIDTH     			(0x0008)
#define  TOF_CORE_ITC_VSTART     			(0x000C)
#define  TOF_CORE_ITC_HSTART     			(0x0010)
#define  TOF_CORE_ITC_ACTIVE_WIDTH     		(0x0014)
#define  TOF_CORE_ITC_ACTIVE_HEIGHT     	(0x0018)
#define  TOF_CORE_ITC_ACTIVE_START_LINE  	(0x001C)
//
#define  TOF_CORE_SENSOR_SEL     			(0x0020)
#define  TOF_CORE_GEN_CTL     				(0x0024)
#define  TOF_CORE_GRAY_TH     				(0x0028)
//AE
#define  TOF_CORE_AE_CTL     				(0x0050)
#define  TOF_CORE_AE_WIN_HSTART     		(0x0054)
#define  TOF_CORE_AE_WIN_VSTART     		(0x0058)
#define  TOF_CORE_AE_WIN_H_END    			(0x005C)
#define  TOF_CORE_AE_WIN_V_END    			(0x0060)
#define  TOF_CORE_AE_TAR_BRIGHT     		(0x0064)
#define  TOF_CORE_AE_TAR_BRIGHT_RANGE     	(0x0068)
#define  TOF_CORE_AE_EX_TIME     			(0x006C)														   
#define  TOF_CORE_AE_AGC     				(0x0074)
#define  TOF_CORE_AE_AD_FREQ     			(0x0078)
#define  TOF_CORE_AE_AD_STEP_MAX    		(0x007C)
#define  TOF_CORE_AE_EX_VALUE_MAX     		(0x0080)
#define  TOF_CORE_AE_EX_VALUE_MID     		(0x0084)
#define  TOF_CORE_AE_EX_VALUE_MIN     		(0x0088)
#define  TOF_CORE_AE_GAIN_MAX     			(0x008C)
#define  TOF_CORE_AE_GAIN_MID     			(0x0090)
#define  TOF_CORE_AE_GAIN_MIN     			(0x0094)	
//													   
#define  TOF_CORE_AE_VALUE_READY     		(0x00C8)
#define  TOF_CORE_AE_LONG_CUR_EX     		(0x00CC)
#define  TOF_CORE_AE_SHORT_CUR_EX     		(0x00D0)
#define  TOF_CORE_AE_CUR_DIGITAL_GAIN     	(0x00D4)
#define  TOF_CORE_AE_CUR_AVE_BRIGHTNESS     (0x00D8)
#define  TOF_CORE_AE_EX_STATUS     			(0x00DC)
#define  TOF_CORE_AE_SUM     				(0x00F0)
#define  TOF_CORE_AE_PIXEL_SUM     			(0x00F4)
//2DNR												   
#define  TOF_CORE_2DNR_CTL     				(0x01E4)
#define  TOF_CORE_2DNR_GRAY     			(0x01E8)
#define  TOF_CORE_2DNR_DEPTH    			(0x01EC)
//POST												   
#define  TOF_CORE_POST_CTL     				(0x0254)
#define  TOF_CORE_CONT_GAIN     			(0x0258)
#define  TOF_CORE_LUMA_GAIN     			(0x025C)
#define  TOF_CORE_SATU_GAIN     			(0x0260)
//
#define  TOF_CORE_RAM_WR_STATUS     		(0x0320)
#define  TOF_CORE_RAM_RD_STATUS     		(0x0324)

#endif /*_ISP_3D_CORE_REG_H_*/

