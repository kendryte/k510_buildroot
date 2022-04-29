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
 * isp_core_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _ISP_CORE_REG_H_
#define _ISP_CORE_REG_H_

#include "isp_com.h"

/*
*Image Timing Control
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hsync_pol                      : 1   ; /* [0 ]      */
        unsigned int    vsync_pol                      : 1   ; /* [1 ]      */
        unsigned int    hsync_input_timing             : 2   ; /* [3 ..2 ]  */
        unsigned int    vsync_input_timing             : 1   ; /* [4 ]      */
        unsigned int    mirror_ctl                     : 1   ; /* [5 ]      */
        unsigned int    video_format_ctl               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 25  ; /* [31..7 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ITC_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_height                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_HEIGHT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_width                    : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_WIDTH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_v_start                  : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_V_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_h_start                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_H_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_active_width             : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_ACTIVE_WIDTH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    image_active_height            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_IMAGE_ACTIVE_HEIGHT;
/*
* Test Pattern Control
*/ 
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bayer_mode_sel                 : 2   ; /* [1 ..0 ]  */
        unsigned int    motion_mode_sel                : 2   ; /* [3 ..2 ]  */
        unsigned int    test_pattern_sel               : 4   ; /* [7 ..4 ]  */
        unsigned int    test_pattern_en                : 1   ; /* [8 ]      */
        unsigned int    reserved0                      : 1   ; /* [9 ]      */
        unsigned int    wdr_l_mul_data                 : 2   ; /* [11..10]  */
        unsigned int    wdr_m_mul_data                 : 2   ; /* [13..12]  */
        unsigned int    wdr_s_mul_data                 : 2   ; /* [15..14]  */
        unsigned int    reserved1                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_TEST_CTL;
/*
*Black Level Correction
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blc_en                         : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_BLC_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blc_offset                     : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_BLC_OFFSET;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blc_ratio                      : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_BLC_RATIO;
/*
* Lens Shading Correction 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_en                         : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_h_center                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_H_CENTER;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_v_center                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_V_CENTER;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_red_ratio                  : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_R_RATIO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_green_ratio                : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_G_RATIO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_blue_ratio                 : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_B_RATIO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsc_ir_ratio                   : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LSC_IR_RATIO;
/*
*AUTO Exposure/Gain 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_as_en                       : 1   ; /* [0 ]      */
        unsigned int    ae_ag_en                       : 1   ; /* [1 ]      */
        unsigned int    ae_airis_en                    : 1   ; /* [2 ]      */
        unsigned int    reserved0                      : 1   ; /* [3 ]      */
        unsigned int    ae_enter_ls_sel                : 1   ; /* [4 ]      */
        unsigned int    ae_exit_ls_sel                 : 1   ; /* [5 ]      */
        unsigned int    reserved1                      : 2   ; /* [7 ..6 ]  */
        unsigned int    ae_win_mode_sel                : 2   ; /* [9 ..8 ]  */
        unsigned int    ae_back_light_mode_sel         : 2   ; /* [11..10]  */
        unsigned int    ae_day_change_en               : 1   ; /* [12]      */
        unsigned int    ae_day_change_sel              : 1   ; /* [13]      */
        unsigned int    reserved2                      : 18  ; /* [31..14]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_win_h_start                 : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_WIN_H_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_win_v_start                 : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_WIN_V_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_win_h_end                   : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_WIN_H_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_win_v_end                   : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_WIN_V_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_tar_bright                  : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_TAR_BR;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_tar_bright_range            : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_TAR_BR_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_l_ex_time                   : 16  ; /* [15..0 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_L_EX_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_m_ex_time                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_M_EX_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_s_ex_time                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_S_EX_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_agc                         : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_AGC;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_ad_shuttle_freq             : 4   ; /* [3 ..0 ]  */
        unsigned int    ae_ad_gain_freq                : 4   ; /* [7 ..4 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_ADJUST_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_adjust_step_max             : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_ADJUST_STEP_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_ex_value_max                : 16  ; /* [15..0 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_EX_VALUE_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_ex_value_mid                : 16  ; /* [15..0 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_EX_VALUE_MID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_ex_value_min                   : 16  ; /* [15..0 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_EX_VALUE_MIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_gain_value_max              : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_GAIN_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_gain_value_mid              : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_GAIN_MID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_gain_value_min              : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_GAIN_MIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_dn_switch_ad_step_max       : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_dn_switch_wait_time         : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_DN_SWITCH_WAIT_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_max_diff                   : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_DIFF_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_drv_signal_max             : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_DRV_SIGNAL_MAX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_coeff_distance             : 6   ; /* [5 ..0 ]  */
        unsigned int    reserved0                      : 26  ; /* [31..6 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_COEFF_DIS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_coeff_speed                : 6   ; /* [5 ..0 ]  */
        unsigned int    reserved0                      : 26  ; /* [31..6 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_COEFF_SPEED;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_coeff_acceleration         : 6   ; /* [5 ..0 ]  */
        unsigned int    reserved0                      : 26  ; /* [31..6 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_COEFF_ACCE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_drv_manual_value           : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_DRV_MANUAL_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ape_damp_manual_value          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_APE_DAMP_MANUAL_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_value_ready                 : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_VALUE_READY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_long_cur_ex                 : 16  ; /* [15..0 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_LONG_CUR_EX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_mid_cur_ex                  : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_MID_CUR_EX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_short_cur_ex                : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_SHORT_CUR_EX;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_digital_gain                : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_CUR_DIGITAL_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ave_brightness                 : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_CUR_AVE_BRIGHTNESS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_day_night_status            : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_CUR_DN_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_ex_status                   : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_EX_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_sum                         : 20  ; /* [19..0 ]  */
        unsigned int    reserved0                      : 12  ; /* [31..20]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_SUM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ae_pixel_sum                   : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AE_PIXEL_SUM;
/*
*AWB
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_d65_en                     : 1   ; /* [0 ]      */
        unsigned int    awb_ccm_en                     : 1   ; /* [1 ]      */
        unsigned int    awb_en                         : 1   ; /* [2 ]      */
        unsigned int    awb_mode_sel                   : 1   ; /* [3 ]      */
        unsigned int    awb_hist_mode_sel              : 1   ; /* [4 ]      */
        unsigned int    awb_veri_en                    : 1   ; /* [5 ]      */
        unsigned int    awb_fb_en                      : 1   ; /* [6 ]      */
        unsigned int    awb_value_save_en              : 1   ; /* [7 ]      */
        unsigned int    awb_ccm_adp_adjust_en          : 1   ; /* [8 ]      */
        unsigned int    awb_stab_en                    : 1   ; /* [9 ]      */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_d65_red_gain               : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_D65_RED_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_d65_blue_gain              : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_D65_BLUE_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_rr_coff                    : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_RR_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_rg_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_RG_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_rb_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_RB_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_gr_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_GR_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_gg_coff                    : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_GG_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_gb_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_GB_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_br_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_BR_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_bg_coff                    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_BG_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_bb_coff                    : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_BB_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ccm_correct_coff               : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CCM_CORRECT_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_win_h_start                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_WIN_H_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_win_v_start                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_WIN_V_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_win_h_end                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_WIN_H_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_win_v_end                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_WIN_V_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_correct_diff_th            : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_CORRECT_DIFF_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_color_changeres_time       : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RES_TIME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_historgram_th              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_HIST_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_gain_adjust            : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_GAIN_ADJUST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_green_gain_adjust          : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_GREEN_GAIN_ADJUST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_gain_adjust           : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_GAIN_ADJUST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_max_value              : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_MAX_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_max_value             : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_MAX_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_min_value              : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_MIN_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_min_value             : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_MIN_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_obj_value              : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_OBJ_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_obj_value             : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_OBJ_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_hist_value            : 21  ; /* [20..0 ]  */
        unsigned int    reserved0                      : 11  ; /* [31..21]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_HIST_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_hist_pixel            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_HIST_PIXEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_hist_value             : 21  ; /* [20..0 ]  */
        unsigned int    reserved0                      : 11  ; /* [31..21]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_HIST_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_hist_pixel             : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_HIST_PIXEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_bypass_blue_hist_value     : 21  ; /* [20..0 ]  */
        unsigned int    reserved0                      : 11  ; /* [31..21]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_bypass_blue_hist_pixel     : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_bypass_red_hist_value      : 21  ; /* [20..0 ]  */
        unsigned int    reserved0                      : 11  ; /* [31..21]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BYPASS_RED_HIST_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_bypass_red_hist_pixel      : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_red_value                  : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_RED_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_green_value                : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_GREEN_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_blue_value                 : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_BLUE_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_org_image_red_value        : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_ORG_RED_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_org_image_green_value      : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_ORG_GREEN_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    awb_org_image_blue_value       : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AWB_ORG_BLUE_VALUE;
/*
*wdr
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_fusion_en                  : 1   ; /* [0 ]      */
        unsigned int    wdr_frame_sel                  : 1   ; /* [1 ]      */
        unsigned int    wdr_adp_adjust_en              : 1   ; /* [2 ]      */
        unsigned int    wdr_stab_en                    : 1   ; /* [3 ]      */
        unsigned int    wdr_en                         : 1   ; /* [4 ]      */
        unsigned int    wdr_ghost_remove_en            : 1   ; /* [5 ]      */
        unsigned int    wdr_3frame_out_mode           : 1   ; /* [6 ]      */
        unsigned int    wdr_mode_sel                   : 1   ; /* [7 ]      */
        unsigned int    wdr_2frame_ex_ratio            : 2   ; /* [9 ..8 ]  */
        unsigned int    wdr_3frame_ex_ratio            : 2   ; /* [11..10]  */
        unsigned int    wdr_stat_img_sel               : 2   ; /* [13..12]  */
		unsigned int    wdr_ltm_data_sel			   : 1   ; /* [14 ]      */
		unsigned int    wdr_tz_data_sel			   	   : 1   ; /* [15 ]      */
		unsigned int    wdr_remove_purple_en		   : 1   ; /* [16 ]      */
        unsigned int    reserved0                      : 15  ; /* [31..17]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_over_ex_ratio_th1          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_OVER_EX_RATIO_TH1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_over_ex_ratio_th2          : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_OVER_EX_RATIO_TH2;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_fusion_ratio_th            : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_FUSION_RATIO_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_fusion_value1              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_FUSION_VALUE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdr_fusion_value2              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_WDR_FUSION_VALUE2;
/*
* CSC
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_00                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_00;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_01                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_01;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_02                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_02;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_10                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_10;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_11                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_11;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_12                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_12;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_20                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_20;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_21                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_21;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csc_r2y_22                     : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CSC_R2Y_22;
/*
*ADA
*/ 
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_rgb_gamma_en               : 1   ; /* [0 ]      */
        unsigned int    ada_yuv_gamma_en               : 1   ; /* [1 ]      */
        unsigned int    ada_adjust_en                  : 1   ; /* [2 ]      */
        unsigned int    ada_img_stab_en                : 1   ; /* [3 ]      */
        unsigned int    ada_ccr_en                     : 1   ; /* [4 ]      */
        unsigned int    ada_adp_en                     : 1   ; /* [5 ]      */
        unsigned int    ada_adp_ccr_en                 : 1   ; /* [6 ]      */
        unsigned int    ada_stat_mode_sel              : 2   ; /* [8 ..7 ]  */
        unsigned int    ada_enh_mode_sel               : 2   ; /* [10..9 ]  */
        unsigned int    reserved0                      : 21  ; /* [31..11]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_stat_max_value             : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_STAT_MAX_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_ad_stren_max_value         : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_AD_STREN_MAX_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_win_h_start                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_WIN_H_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_win_v_start                : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_WIN_V_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_win_h_end                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_WIN_H_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ada_win_v_end                  : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ADA_WIN_V_END;
/*
*RGBIR
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_en                       : 1   ; /* [0 ]      */
        unsigned int    rgbir_rtf_en                   : 1   ; /* [1 ]      */
        unsigned int    rgbir_rpc_en                   : 1   ; /* [2 ]      */
        unsigned int    rgbir_fusion_en                : 1   ; /* [3 ]      */
        unsigned int    rgbir_output_sel               : 1   ; /* [4 ]      */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_rpc_max_value            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_RPC_MAX_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_rpc_color_coff           : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_RPC_COLOR_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_rpc_luma_coff            : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_RPC_LUMA_COFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_rpc_th                   : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_RPC_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgbir_rpc_th1                  : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RGBIR_RPC_TH1;
/*
*2D Noise Reduction
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_pcf_en               : 1   ; /* [0 ]      */
        unsigned int    core_2dnr_raw_en               : 1   ; /* [1 ]      */
        unsigned int    core_2dnr_edge_en              : 1   ; /* [2 ]      */
        unsigned int    core_2dnr_bap_en               : 1   ; /* [3 ]      */
        unsigned int    core_2dnr_luma_en              : 1   ; /* [4 ]      */
        unsigned int    core_2dnr_chroma_en            : 1   ; /* [5 ]      */
        unsigned int    core_2dnr_pcf_adp_en           : 1   ; /* [6 ]      */
        unsigned int    core_2dnr_raw_adp_en           : 1   ; /* [7 ]      */
        unsigned int    core_2dnr_luma_adp_en          : 1   ; /* [8 ]      */
        unsigned int    core_2dnr_chroma_adp_en        : 1   ; /* [9 ]      */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_raw_intensity        : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_RAW_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_bap_intensity        : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_BAP_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_edge_intensity       : 10  ; /* [9 ..0 ]  */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_EDGE_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_luma_intensity       : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_LUMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_2dnr_chroma_intensity     : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_2DNR_CHROMA_INTENSITY;
/*
* 3D Noise Reduction 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_en                   : 1   ; /* [0 ]      */
        unsigned int    core_3dnr_pre_luma_en          : 1   ; /* [1 ]      */
        unsigned int    core_3dnr_pre_chroma_en        : 1   ; /* [2 ]      */
        unsigned int    core_3dnr_main_luma_en         : 1   ; /* [3 ]      */
        unsigned int    core_3dnr_main_chroma_en       : 1   ; /* [4 ]      */
        unsigned int    core_3dnr_post_luma_en         : 1   ; /* [5 ]      */
        unsigned int    core_3dnr_post_chroma_en       : 1   ; /* [6 ]      */
        unsigned int    core_3dnr_2d_luma_en           : 1   ; /* [7 ]      */
        unsigned int    core_3dnr_2d_chroma_en         : 1   ; /* [8 ]      */
        unsigned int    core_3dnr_wb_en                : 1   ; /* [9 ]      */
        unsigned int    core_3dnr_wb_sel               : 1   ; /* [10]      */
        unsigned int    reserved0                      : 1   ; /* [11]      */
        unsigned int    core_3dnr_adp_luma_en          : 1   ; /* [12]      */
        unsigned int    core_3dnr_adp_chroma_en        : 1   ; /* [13]      */
        unsigned int    reserved1                      : 18  ; /* [31..14]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_pre_luma_th          : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_PRE_LUMA_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_pre_luma_intensity   : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_PRE_LUMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_pre_chroma_intensity : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_PRE_CHROMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_mid_filter_th        : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_MID_FILTER_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_pre_mid_filter_th    : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_PRE_MID_FILTER_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_cur_mid_filter_th    : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_CUR_FILTER_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_low_pass_filter_th   : 9   ; /* [8 ..0 ]  */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_LOW_PASS_FILTER_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_luma_th              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_LUMA_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_min_value            : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_MIN_VALUE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_luma_intensity       : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_LUMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_chroma_intensity     : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_CHROMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_post_edge_th         : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_POST_EDGE_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_post_luma_intensity  : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_POST_LUMA_INTENSITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_3dnr_post_chroma_intensity : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_3DNR_POST_CHROMA_INTENSITY;
/*
*ENH
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enh_ltm_en                     : 1   ; /* [0 ]      */
        unsigned int    enh_sharp_en                   : 1   ; /* [1 ]      */
        unsigned int    enh_cc_en                      : 1   ; /* [2 ]      */
        unsigned int    enh_adp_ltm_en                 : 1   ; /* [3 ]      */
        unsigned int    enh_adp_sharp_en               : 1   ; /* [4 ]      */
        unsigned int    enh_adp_cc_en                  : 1   ; /* [5 ]      */
        unsigned int    reserved0                      : 26  ; /* [31..6 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ENH_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ltm_gain                       : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LTM_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ltm_th                         : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LTM_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enh_nr_th                      : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ENH_NR_TH;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enh_th1                        : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ENH_TH1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    enh_th2                        : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_ENH_TH2;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sharp_gain                     : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_SHARP_GAIN;
/*
*POSt Control
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otc_yc_sel                     : 1   ; /* [0 ]      */
        unsigned int    otc_uv_format_sel              : 1   ; /* [1 ]      */
        unsigned int    otc_hsync_pol_sel              : 1   ; /* [2 ]      */
        unsigned int    otc_vsync_pol_sel              : 1   ; /* [3 ]      */
        unsigned int    post_cont_ad_en                : 1   ; /* [4 ]      */
        unsigned int    post_luma_ad_en                : 1   ; /* [5 ]      */
        unsigned int    post_satu_ad_en                : 1   ; /* [6 ]      */
        unsigned int    post_otc_en                	   : 1   ; /* [7 ]      */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_POST_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cont_ad_intensity              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_CONT_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    luma_ad_intensity              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LUMA_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    satu_ad_intensity              : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_SATU_GAIN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otc_stt_vr                     : 12   ; /* [11 ..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_OTC_STT_VR;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otc_stt_hr                     : 13   ; /* [13 ..0 ]  */
        unsigned int    reserved0                      : 19  ; /* [31..13 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_OTC_STT_HR;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otc_height                     : 12   ; /* [11 ..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_OTC_HEIGHT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    otc_width                      : 12   ; /* [11 ..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_OTC_WIDTH;
/*
* LDC Control 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_en                         : 1   ; /* [0 ]      */
        unsigned int    ldc_arith_en                   : 1   ; /* [1 ]      */
        unsigned int    reserved0                      : 30  ; /* [31..2 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_req_freq                   : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 8   ; /* [15..8 ]  */
		unsigned int    ldc_stt_ln                     : 16  ; /* [31..61 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_REQ_FREQ;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_h_center_pos               : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_H_CENTER_POS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_v_center_pos               : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_V_CENTER_POS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_rectify_cr                 : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_RECTIFY_CR;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ldc_rectify_cz                 : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_LDC_RECTIFY_CZ;
/*
* ISP Table Control 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gamma_grb_table_cfg            : 1   ; /* [0 ]      */
        unsigned int    gamma_yuv_table_cfg            : 1   ; /* [1 ]      */
        unsigned int    wdr_l3_table_cfg               : 1   ; /* [2 ]      */
        unsigned int    wdr_m3_table_cfg               : 1   ; /* [3 ]      */
        unsigned int    wdr_s3_table_cfg               : 1   ; /* [4 ]      */
        unsigned int    wdr_l2_table_cfg               : 1   ; /* [5 ]      */
        unsigned int    wdr_s2_table_cfg               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 25  ; /* [31..7 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RAM_WR_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gamma_grb_table                : 1   ; /* [0 ]      */
        unsigned int    gamma_yuv_table                : 1   ; /* [1 ]      */
        unsigned int    wdr_l3_table                   : 1   ; /* [2 ]      */
        unsigned int    wdr_m3_table                   : 1   ; /* [3 ]      */
        unsigned int    wdr_s3_table                   : 1   ; /* [4 ]      */
        unsigned int    wdr_l2_table                   : 1   ; /* [5 ]      */
        unsigned int    wdr_s2_table                   : 1   ; /* [6 ]      */
        unsigned int    ram_ready_status               : 1   ; /* [7 ]      */
        unsigned int    hist_ready_status              : 1   ; /* [8 ]      */
        unsigned int    reserved0                      : 23  ; /* [31..9 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RAM_RD_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ram_ready_lock                 : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_RAM_READ_LOCK;
/*
*AF Statistics
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_en                     : 1   ; /* [0 ]      */
        unsigned int    af_stat_mode_sel               : 2   ; /* [2 ..1 ]  */
        unsigned int    reserved0                      : 29  ; /* [31..3 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_win_h_start            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_STAT_WIN_H_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_win_v_start            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_STAT_WIN_V_START;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_win_h_end              : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_STAT_WIN_H_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_win_v_end              : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_STAT_WIN_V_END;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_mid_frq_data                : 30  ; /* [29..0 ]  */
        unsigned int    reserved0                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_MID_FRQ_DATA;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_high_frq_data               : 30  ; /* [29..0 ]  */
        unsigned int    reserved0                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_HIGH_FRQ_DATA;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    af_stat_pixel_num              : 18  ; /* [17..0 ]  */
        unsigned int    reserved0                      : 14  ; /* [31..18]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_CORE_AF_STAT_PIXEL_NUM;

//itc
#define  ISP_CORE_ITC_CTL               		(0x0000)
#define  ISP_CORE_IMAGE_HEIGHT          		(0x0004)
#define  ISP_CORE_IMAGE_WIDTH           		(0x0008)
#define  ISP_CORE_IMAGE_V_START         		(0x000C)
#define  ISP_CORE_IMAGE_H_START         		(0x0010)
#define  ISP_CORE_IMAGE_ACTIVE_WIDTH    		(0x0014)
#define  ISP_CORE_IMAGE_ACTIVE_HEIGHT   		(0x0018)
//tpg	
#define  ISP_CORE_TEST_CTL              		(0x001C)
//blc		
#define  ISP_CORE_BLC_CTL               		(0x0020)
#define  ISP_CORE_BLC_OFFSET            		(0x0024)
#define  ISP_CORE_BLC_RATIO             		(0x0028)
//lsc		
#define  ISP_CORE_LSC_CTL               		(0x002C)
#define  ISP_CORE_LSC_H_CENTER          		(0x0030)
#define  ISP_CORE_LSC_V_CENTER          		(0x0034)
#define  ISP_CORE_LSC_R_RATIO           		(0x0038)
#define  ISP_CORE_LSC_G_RATIO           		(0x003C)
#define  ISP_CORE_LSC_B_RATIO           		(0x0040)
#define  ISP_CORE_LSC_IR_RATIO          		(0x0044)
//ae		
#define  ISP_CORE_AE_CTL                		(0x0050)
#define  ISP_CORE_AE_WIN_H_START        		(0x0054)
#define  ISP_CORE_AE_WIN_V_START        		(0x0058)
#define  ISP_CORE_AE_WIN_H_END          		(0x005C)
#define  ISP_CORE_AE_WIN_V_END          		(0x0060)
#define  ISP_CORE_AE_TAR_BR             		(0x0064)
#define  ISP_CORE_AE_TAR_BR_RANGE       		(0x0068)
#define  ISP_CORE_AE_L_EX_TIME          		(0x006C)
#define  ISP_CORE_AE_M_EX_TIME          		(0x0070)
#define  ISP_CORE_AE_S_EX_TIME          		(0x0074)
#define  ISP_CORE_AE_AGC                		(0x0078)
#define  ISP_CORE_AE_ADJUST_CTL         		(0x007C)
#define  ISP_CORE_AE_ADJUST_STEP_MAX    		(0x0080)
#define  ISP_CORE_AE_EX_VALUE_MAX       		(0x0084)
#define  ISP_CORE_AE_EX_VALUE_MID       		(0x0088)
#define  ISP_CORE_AE_EX_VALUE_MIN       		(0x008C)
#define  ISP_CORE_AE_GAIN_MAX           		(0x0090)
#define  ISP_CORE_AE_GAIN_MID           		(0x0094)
#define  ISP_CORE_AE_GAIN_MIN           		(0x0098)
#define  ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX  (0x009C)
#define  ISP_CORE_AE_DN_SWITCH_WAIT_TIME        (0x00A0)

#define  ISP_CORE_APE_DIFF_MAX                  (0x00AC)
#define  ISP_CORE_APE_DRV_SIGNAL_MAX            (0x00B0)
#define  ISP_CORE_APE_COEFF_DIS                 (0x00B4)
#define  ISP_CORE_APE_COEFF_SPEED               (0x00B8)
#define  ISP_CORE_APE_COEFF_ACCE                (0x00BC)
#define  ISP_CORE_APE_DRV_MANUAL_VALUE          (0x00C0)
#define  ISP_CORE_APE_DAMP_MANUAL_VALUE         (0x00C4)

#define  ISP_CORE_AE_VALUE_READY                (0x00D4)
#define  ISP_CORE_AE_LONG_CUR_EX                (0x00D8)
#define  ISP_CORE_AE_MID_CUR_EX                 (0x00DC)
#define  ISP_CORE_AE_SHORT_CUR_EX               (0x00E0)
#define  ISP_CORE_AE_CUR_DIGITAL_GAIN           (0x00E4)
#define  ISP_CORE_AE_CUR_AVE_BRIGHTNESS         (0x00E8)
#define  ISP_CORE_AE_CUR_DN_STATUS              (0x00EC)
#define  ISP_CORE_AE_EX_STATUS                  (0x00F0)
#define  ISP_CORE_AE_SUM                        (0x00F4)
#define  ISP_CORE_AE_PIXEL_SUM                  (0x00F8)
//awb
#define  ISP_CORE_AWB_CTL                       (0x0104)
#define  ISP_CORE_AWB_D65_RED_GAIN              (0x0108)
#define  ISP_CORE_AWB_D65_BLUE_GAIN             (0x010C)
#define  ISP_CORE_CCM_RR_COFF                   (0x0110)
#define  ISP_CORE_CCM_RG_COFF                   (0x0114)
#define  ISP_CORE_CCM_RB_COFF                   (0x0118)
#define  ISP_CORE_CCM_GR_COFF                   (0x011C)
#define  ISP_CORE_CCM_GG_COFF                   (0x0120)
#define  ISP_CORE_CCM_GB_COFF                   (0x0124)
#define  ISP_CORE_CCM_BR_COFF                   (0x0128)
#define  ISP_CORE_CCM_BG_COFF                   (0x012C)
#define  ISP_CORE_CCM_BB_COFF                   (0x0130)
#define  ISP_CORE_CCM_CORRECT_COFF              (0x0134)
#define  ISP_CORE_AWB_WIN_H_START               (0x0138)
#define  ISP_CORE_AWB_WIN_V_START               (0x013C)
#define  ISP_CORE_AWB_WIN_H_END                 (0x0140)
#define  ISP_CORE_AWB_WIN_V_END                 (0x0144)
#define  ISP_CORE_AWB_CORRECT_DIFF_TH           (0x0148)
#define  ISP_CORE_AWB_RES_TIME                  (0x014C)
#define  ISP_CORE_AWB_HIST_TH                   (0x0150)
#define  ISP_CORE_AWB_RED_GAIN_ADJUST           (0x0154)
#define  ISP_CORE_AWB_GREEN_GAIN_ADJUST         (0x0158)
#define  ISP_CORE_AWB_BLUE_GAIN_ADJUST          (0x015C)
#define  ISP_CORE_AWB_RED_MAX_VALUE             (0x0160)
#define  ISP_CORE_AWB_BLUE_MAX_VALUE            (0x0164)
#define  ISP_CORE_AWB_RED_MIN_VALUE             (0x0168)
#define  ISP_CORE_AWB_BLUE_MIN_VALUE            (0x016C)
#define  ISP_CORE_AWB_RED_OBJ_VALUE             (0x0170)
#define  ISP_CORE_AWB_BLUE_OBJ_VALUE            (0x0174)
#define  ISP_CORE_AWB_BLUE_HIST_VALUE           (0x017C)
#define  ISP_CORE_AWB_BLUE_HIST_PIXEL           (0x0180)
#define  ISP_CORE_AWB_RED_HIST_VALUE            (0x0184)
#define  ISP_CORE_AWB_RED_HIST_PIXEL            (0x0188)
#define  ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE    (0x018C)
#define  ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL    (0x0190)
#define  ISP_CORE_AWB_BYPASS_RED_HIST_VALUE     (0x0194)
#define  ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL     (0x0198)
#define  ISP_CORE_AWB_RED_VALUE                 (0x019C)
#define  ISP_CORE_AWB_GREEN_VALUE               (0x01A0)
#define  ISP_CORE_AWB_BLUE_VALUE                (0x01A4)
#define  ISP_CORE_AWB_ORG_RED_VALUE             (0x01A8)
#define  ISP_CORE_AWB_ORG_GREEN_VALUE           (0x01AC)
#define  ISP_CORE_AWB_ORG_BLUE_VALUE            (0x01B0)
//wdr
#define  ISP_CORE_WDR_CTL                       (0x01B8)
#define  ISP_CORE_WDR_OVER_EX_RATIO_TH1         (0x01BC)
#define  ISP_CORE_WDR_OVER_EX_RATIO_TH2         (0x01C0)
#define  ISP_CORE_WDR_FUSION_RATIO_TH           (0x01C4)
#define  ISP_CORE_WDR_FUSION_VALUE1             (0x01C8)
#define  ISP_CORE_WDR_FUSION_VALUE2             (0x01CC)
//csc
#define  ISP_CORE_CSC_R2Y_00                    (0x01D8)
#define  ISP_CORE_CSC_R2Y_01                    (0x01DC)
#define  ISP_CORE_CSC_R2Y_02                    (0x01E0)
#define  ISP_CORE_CSC_R2Y_10                    (0x01E4)
#define  ISP_CORE_CSC_R2Y_11                    (0x01E8)
#define  ISP_CORE_CSC_R2Y_12                    (0x01EC)
#define  ISP_CORE_CSC_R2Y_20                    (0x01F0)
#define  ISP_CORE_CSC_R2Y_21                    (0x01F4)
#define  ISP_CORE_CSC_R2Y_22                    (0x01F8)
//ada
#define  ISP_CORE_ADA_CTL                       (0x0204)
#define  ISP_CORE_ADA_STAT_MAX_VALUE            (0x0208)
#define  ISP_CORE_ADA_AD_STREN_MAX_VALUE        (0x020C)
#define  ISP_CORE_ADA_WIN_H_START               (0x0210)
#define  ISP_CORE_ADA_WIN_V_START               (0x0214)
#define  ISP_CORE_ADA_WIN_H_END                 (0x0218)
#define  ISP_CORE_ADA_WIN_V_END                 (0x021C)
//rgbir
#define  ISP_CORE_RGBIR_CTL                     (0x0230)
#define  ISP_CORE_RGBIR_RPC_MAX_VALUE           (0x0234)
#define  ISP_CORE_RGBIR_RPC_COLOR_COFF          (0x0238)
#define  ISP_CORE_RGBIR_RPC_LUMA_COFF           (0x023C)
#define  ISP_CORE_RGBIR_RPC_TH                  (0x0240)
#define  ISP_CORE_RGBIR_RPC_TH1                 (0x0244)
//2dnr
#define  ISP_CORE_2DNR_CTL                      (0x0258)
#define  ISP_CORE_2DNR_RAW_INTENSITY            (0x025C)
#define  ISP_CORE_2DNR_BAP_INTENSITY            (0x0260)
#define  ISP_CORE_2DNR_EDGE_INTENSITY           (0x0264)
#define  ISP_CORE_2DNR_LUMA_INTENSITY           (0x0268)
#define  ISP_CORE_2DNR_CHROMA_INTENSITY         (0x026C)
//3dnr
#define  ISP_CORE_3DNR_CTL                      (0x0278)
#define  ISP_CORE_3DNR_PRE_LUMA_TH              (0x027C)
#define  ISP_CORE_3DNR_PRE_LUMA_INTENSITY       (0x0280)
#define  ISP_CORE_3DNR_PRE_CHROMA_INTENSITY     (0x0284)
#define  ISP_CORE_3DNR_MID_FILTER_TH            (0x0288)
#define  ISP_CORE_3DNR_PRE_MID_FILTER_TH        (0x028C)
#define  ISP_CORE_3DNR_CUR_FILTER_TH            (0x0290)
#define  ISP_CORE_3DNR_LOW_PASS_FILTER_TH       (0x0294)
#define  ISP_CORE_3DNR_LUMA_TH                  (0x0298)
#define  ISP_CORE_3DNR_MIN_VALUE                (0x029C)
#define  ISP_CORE_3DNR_LUMA_INTENSITY           (0x02A0)
#define  ISP_CORE_3DNR_CHROMA_INTENSITY         (0x02A4)
#define  ISP_CORE_3DNR_POST_EDGE_TH             (0x02A8)
#define  ISP_CORE_3DNR_POST_LUMA_INTENSITY      (0x02AC)
#define  ISP_CORE_3DNR_POST_CHROMA_INTENSITY    (0x02B0)
//enh
#define  ISP_CORE_ENH_CTL                       (0x02BC)
#define  ISP_CORE_LTM_GAIN                      (0x02C0)
#define  ISP_CORE_LTM_TH                        (0x02C4)
#define  ISP_CORE_ENH_NR_TH                     (0x02C8)
#define  ISP_CORE_ENH_TH1                       (0x02CC)
#define  ISP_CORE_ENH_TH2                       (0x02D0)
#define  ISP_CORE_SHARP_GAIN                    (0x02D4)
//post
#define  ISP_CORE_POST_CTL                      (0x02E4)
#define  ISP_CORE_CONT_GAIN                     (0x02E8)
#define  ISP_CORE_LUMA_GAIN                     (0x02EC)
#define  ISP_CORE_SATU_GAIN                     (0x02F0)
//otc                                                
#define  ISP_CORE_OTC_STT_VR                    (0x02F4)
#define  ISP_CORE_OTC_STT_HR                    (0x02F8)
#define  ISP_CORE_OTC_HEIGHT                    (0x02FC)
#define  ISP_CORE_OTC_WIDTH                     (0x0300)
//ldc
#define  ISP_CORE_LDC_CTL                       (0x0304)
#define  ISP_CORE_LDC_REQ_FREQ                  (0x0308)
#define  ISP_CORE_LDC_H_CENTER_POS              (0x030C)
#define  ISP_CORE_LDC_V_CENTER_POS              (0x0310)
#define  ISP_CORE_LDC_RECTIFY_CR                (0x0314)
#define  ISP_CORE_LDC_RECTIFY_CZ                (0x0318)
//ram table
#define  ISP_CORE_RAM_WR_STATUS                 (0x0320)
#define  ISP_CORE_RAM_RD_STATUS                 (0x0324)
#define  ISP_CORE_RAM_READ_LOCK                 (0x0328)
//af
#define  ISP_CORE_AF_CTL                        (0x0340)
#define  ISP_CORE_AF_STAT_WIN_H_START           (0x0344)
#define  ISP_CORE_AF_STAT_WIN_V_START           (0x0348)
#define  ISP_CORE_AF_STAT_WIN_H_END             (0x034C)
#define  ISP_CORE_AF_STAT_WIN_V_END             (0x0350)
#define  ISP_CORE_AF_MID_FRQ_DATA               (0x035C)
#define  ISP_CORE_AF_HIGH_FRQ_DATA              (0x0360)
#define  ISP_CORE_AF_STAT_PIXEL_NUM             (0x0364)

#endif /*_ISP_CORE_REG_H_*/

