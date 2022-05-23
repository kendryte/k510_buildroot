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
#ifndef _ISP_CORE_REG_DEF_H_
#define _ISP_CORE_REG_DEF_H_
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
        unsigned int    wdr_3_frame_out_mode           : 1   ; /* [6 ]      */
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

typedef struct
{
    volatile U_ISP_CORE_ITC_CTL                 ISP_CORE_ITC_CTL;
    volatile U_ISP_CORE_IMAGE_HEIGHT            ISP_CORE_IMAGE_HEIGHT;
    volatile U_ISP_CORE_IMAGE_WIDTH             ISP_CORE_IMAGE_WIDTH;
    volatile U_ISP_CORE_IMAGE_V_START           ISP_CORE_IMAGE_V_START;
    volatile U_ISP_CORE_IMAGE_H_START           ISP_CORE_IMAGE_H_START;
    volatile U_ISP_CORE_IMAGE_ACTIVE_WIDTH      ISP_CORE_IMAGE_ACTIVE_WIDTH;
    volatile U_ISP_CORE_IMAGE_ACTIVE_HEIGHT     ISP_CORE_IMAGE_ACTIVE_HEIGHT;
    volatile U_ISP_CORE_TEST_CTL                ISP_CORE_TEST_CTL;
    volatile U_ISP_CORE_BLC_CTL                 ISP_CORE_BLC_CTL;
    volatile U_ISP_CORE_BLC_OFFSET              ISP_CORE_BLC_OFFSET;
    volatile U_ISP_CORE_BLC_RATIO               ISP_CORE_BLC_RATIO;
    volatile U_ISP_CORE_LSC_CTL                 ISP_CORE_LSC_CTL;
    volatile U_ISP_CORE_LSC_H_CENTER            ISP_CORE_LSC_H_CENTER;
    volatile U_ISP_CORE_LSC_V_CENTER            ISP_CORE_LSC_V_CENTER;
    volatile U_ISP_CORE_LSC_R_RATIO             ISP_CORE_LSC_R_RATIO;
    volatile U_ISP_CORE_LSC_G_RATIO             ISP_CORE_LSC_G_RATIO;
    volatile U_ISP_CORE_LSC_B_RATIO             ISP_CORE_LSC_B_RATIO;
    volatile U_ISP_CORE_LSC_IR_RATIO            ISP_CORE_LSC_IR_RATIO;
    volatile unsigned int                     reserved0[2];
    volatile U_ISP_CORE_AE_CTL                  ISP_CORE_AE_CTL;
    volatile U_ISP_CORE_AE_WIN_H_START          ISP_CORE_AE_WIN_H_START;
    volatile U_ISP_CORE_AE_WIN_V_START          ISP_CORE_AE_WIN_V_START;
    volatile U_ISP_CORE_AE_WIN_H_END            ISP_CORE_AE_WIN_H_END;
    volatile U_ISP_CORE_AE_WIN_V_END            ISP_CORE_AE_WIN_V_END;
    volatile U_ISP_CORE_AE_TAR_BR               ISP_CORE_AE_TAR_BR;
    volatile U_ISP_CORE_AE_TAR_BR_RANGE         ISP_CORE_AE_TAR_BR_RANGE;
    volatile U_ISP_CORE_AE_L_EX_TIME            ISP_CORE_AE_L_EX_TIME;
    volatile U_ISP_CORE_AE_M_EX_TIME            ISP_CORE_AE_M_EX_TIME;
    volatile U_ISP_CORE_AE_S_EX_TIME            ISP_CORE_AE_S_EX_TIME;
    volatile U_ISP_CORE_AE_AGC                  ISP_CORE_AE_AGC;
    volatile U_ISP_CORE_AE_ADJUST_CTL           ISP_CORE_AE_ADJUST_CTL;
    volatile U_ISP_CORE_AE_ADJUST_STEP_MAX      ISP_CORE_AE_ADJUST_STEP_MAX;
    volatile U_ISP_CORE_AE_EX_VALUE_MAX         ISP_CORE_AE_EX_VALUE_MAX;
    volatile U_ISP_CORE_AE_EX_VALUE_MID         ISP_CORE_AE_EX_VALUE_MID;
    volatile U_ISP_CORE_AE_EX_VALUE_MIN         ISP_CORE_AE_EX_VALUE_MIN;
    volatile U_ISP_CORE_AE_GAIN_MAX             ISP_CORE_AE_GAIN_MAX;
    volatile U_ISP_CORE_AE_GAIN_MID             ISP_CORE_AE_GAIN_MID;
    volatile U_ISP_CORE_AE_GAIN_MIN             ISP_CORE_AE_GAIN_MIN;
    volatile U_ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX   ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX;
    volatile U_ISP_CORE_AE_DN_SWITCH_WAIT_TIME   ISP_CORE_AE_DN_SWITCH_WAIT_TIME;
    volatile unsigned int                     reserved1[2];
    volatile U_ISP_CORE_APE_DIFF_MAX            ISP_CORE_APE_DIFF_MAX;
    volatile U_ISP_CORE_APE_DRV_SIGNAL_MAX      ISP_CORE_APE_DRV_SIGNAL_MAX;
    volatile U_ISP_CORE_APE_COEFF_DIS           ISP_CORE_APE_COEFF_DIS;
    volatile U_ISP_CORE_APE_COEFF_SPEED         ISP_CORE_APE_COEFF_SPEED;
    volatile U_ISP_CORE_APE_COEFF_ACCE          ISP_CORE_APE_COEFF_ACCE;
    volatile U_ISP_CORE_APE_DRV_MANUAL_VALUE    ISP_CORE_APE_DRV_MANUAL_VALUE;
    volatile U_ISP_CORE_APE_DAMP_MANUAL_VALUE   ISP_CORE_APE_DAMP_MANUAL_VALUE;
    volatile unsigned int                     reserved2[3];
    volatile U_ISP_CORE_AE_VALUE_READY          ISP_CORE_AE_VALUE_READY;
    volatile U_ISP_CORE_AE_LONG_CUR_EX          ISP_CORE_AE_LONG_CUR_EX;
    volatile U_ISP_CORE_AE_MID_CUR_EX           ISP_CORE_AE_MID_CUR_EX;
    volatile U_ISP_CORE_AE_SHORT_CUR_EX         ISP_CORE_AE_SHORT_CUR_EX;
    volatile U_ISP_CORE_AE_CUR_DIGITAL_GAIN     ISP_CORE_AE_CUR_DIGITAL_GAIN;
    volatile U_ISP_CORE_AE_CUR_AVE_BRIGHTNESS   ISP_CORE_AE_CUR_AVE_BRIGHTNESS;
    volatile U_ISP_CORE_AE_CUR_DN_STATUS        ISP_CORE_AE_CUR_DN_STATUS;
    volatile U_ISP_CORE_AE_EX_STATUS            ISP_CORE_AE_EX_STATUS;
    volatile U_ISP_CORE_AE_SUM                  ISP_CORE_AE_SUM;
    volatile U_ISP_CORE_AE_PIXEL_SUM            ISP_CORE_AE_PIXEL_SUM;
    volatile unsigned int                     reserved3[2];
    volatile U_ISP_CORE_AWB_CTL                 ISP_CORE_AWB_CTL;
    volatile U_ISP_CORE_AWB_D65_RED_GAIN        ISP_CORE_AWB_D65_RED_GAIN;
    volatile U_ISP_CORE_AWB_D65_BLUE_GAIN       ISP_CORE_AWB_D65_BLUE_GAIN;
    volatile U_ISP_CORE_CCM_RR_COFF             ISP_CORE_CCM_RR_COFF;
    volatile U_ISP_CORE_CCM_RG_COFF             ISP_CORE_CCM_RG_COFF;
    volatile U_ISP_CORE_CCM_RB_COFF             ISP_CORE_CCM_RB_COFF;
    volatile U_ISP_CORE_CCM_GR_COFF             ISP_CORE_CCM_GR_COFF;
    volatile U_ISP_CORE_CCM_GG_COFF             ISP_CORE_CCM_GG_COFF;
    volatile U_ISP_CORE_CCM_GB_COFF             ISP_CORE_CCM_GB_COFF;
    volatile U_ISP_CORE_CCM_BR_COFF             ISP_CORE_CCM_BR_COFF;
    volatile U_ISP_CORE_CCM_BG_COFF             ISP_CORE_CCM_BG_COFF;
    volatile U_ISP_CORE_CCM_BB_COFF             ISP_CORE_CCM_BB_COFF;
    volatile U_ISP_CORE_CCM_CORRECT_COFF        ISP_CORE_CCM_CORRECT_COFF;
    volatile U_ISP_CORE_AWB_WIN_H_START         ISP_CORE_AWB_WIN_H_START;
    volatile U_ISP_CORE_AWB_WIN_V_START         ISP_CORE_AWB_WIN_V_START;
    volatile U_ISP_CORE_AWB_WIN_H_END           ISP_CORE_AWB_WIN_H_END;
    volatile U_ISP_CORE_AWB_WIN_V_END           ISP_CORE_AWB_WIN_V_END;
    volatile U_ISP_CORE_AWB_CORRECT_DIFF_TH     ISP_CORE_AWB_CORRECT_DIFF_TH;
    volatile U_ISP_CORE_AWB_RES_TIME            ISP_CORE_AWB_RES_TIME;
    volatile U_ISP_CORE_AWB_HIST_TH             ISP_CORE_AWB_HIST_TH;
    volatile U_ISP_CORE_AWB_RED_GAIN_ADJUST     ISP_CORE_AWB_RED_GAIN_ADJUST;
    volatile U_ISP_CORE_AWB_GREEN_GAIN_ADJUST   ISP_CORE_AWB_GREEN_GAIN_ADJUST;
    volatile U_ISP_CORE_AWB_BLUE_GAIN_ADJUST    ISP_CORE_AWB_BLUE_GAIN_ADJUST;
    volatile U_ISP_CORE_AWB_RED_MAX_VALUE       ISP_CORE_AWB_RED_MAX_VALUE;
    volatile U_ISP_CORE_AWB_BLUE_MAX_VALUE      ISP_CORE_AWB_BLUE_MAX_VALUE;
    volatile U_ISP_CORE_AWB_RED_MIN_VALUE       ISP_CORE_AWB_RED_MIN_VALUE;
    volatile U_ISP_CORE_AWB_BLUE_MIN_VALUE      ISP_CORE_AWB_BLUE_MIN_VALUE;
    volatile U_ISP_CORE_AWB_RED_OBJ_VALUE       ISP_CORE_AWB_RED_OBJ_VALUE;
    volatile U_ISP_CORE_AWB_BLUE_OBJ_VALUE      ISP_CORE_AWB_BLUE_OBJ_VALUE;
    volatile unsigned int                     reserved4[1];
    volatile U_ISP_CORE_AWB_BLUE_HIST_VALUE     ISP_CORE_AWB_BLUE_HIST_VALUE;
    volatile U_ISP_CORE_AWB_BLUE_HIST_PIXEL     ISP_CORE_AWB_BLUE_HIST_PIXEL;
    volatile U_ISP_CORE_AWB_RED_HIST_VALUE      ISP_CORE_AWB_RED_HIST_VALUE;
    volatile U_ISP_CORE_AWB_RED_HIST_PIXEL      ISP_CORE_AWB_RED_HIST_PIXEL;
    volatile U_ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE   ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE;
    volatile U_ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL   ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL;
    volatile U_ISP_CORE_AWB_BYPASS_RED_HIST_VALUE   ISP_CORE_AWB_BYPASS_RED_HIST_VALUE;
    volatile U_ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL   ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL;
    volatile U_ISP_CORE_AWB_RED_VALUE           ISP_CORE_AWB_RED_VALUE;
    volatile U_ISP_CORE_AWB_GREEN_VALUE         ISP_CORE_AWB_GREEN_VALUE;
    volatile U_ISP_CORE_AWB_BLUE_VALUE          ISP_CORE_AWB_BLUE_VALUE;
    volatile U_ISP_CORE_AWB_ORG_RED_VALUE       ISP_CORE_AWB_ORG_RED_VALUE;
    volatile U_ISP_CORE_AWB_ORG_GREEN_VALUE     ISP_CORE_AWB_ORG_GREEN_VALUE;
    volatile U_ISP_CORE_AWB_ORG_BLUE_VALUE      ISP_CORE_AWB_ORG_BLUE_VALUE;
    volatile unsigned int                     reserved5[1];
    volatile U_ISP_CORE_WDR_CTL                 ISP_CORE_WDR_CTL;
    volatile U_ISP_CORE_WDR_OVER_EX_RATIO_TH1   ISP_CORE_WDR_OVER_EX_RATIO_TH1;
    volatile U_ISP_CORE_WDR_OVER_EX_RATIO_TH2   ISP_CORE_WDR_OVER_EX_RATIO_TH2;
    volatile U_ISP_CORE_WDR_FUSION_RATIO_TH     ISP_CORE_WDR_FUSION_RATIO_TH;
    volatile U_ISP_CORE_WDR_FUSION_VALUE1       ISP_CORE_WDR_FUSION_VALUE1;
    volatile U_ISP_CORE_WDR_FUSION_VALUE2       ISP_CORE_WDR_FUSION_VALUE2;
    volatile unsigned int                     reserved6[2];
    volatile U_ISP_CORE_CSC_R2Y_00              ISP_CORE_CSC_R2Y_00;
    volatile U_ISP_CORE_CSC_R2Y_01              ISP_CORE_CSC_R2Y_01;
    volatile U_ISP_CORE_CSC_R2Y_02              ISP_CORE_CSC_R2Y_02;
    volatile U_ISP_CORE_CSC_R2Y_10              ISP_CORE_CSC_R2Y_10;
    volatile U_ISP_CORE_CSC_R2Y_11              ISP_CORE_CSC_R2Y_11;
    volatile U_ISP_CORE_CSC_R2Y_12              ISP_CORE_CSC_R2Y_12;
    volatile U_ISP_CORE_CSC_R2Y_20              ISP_CORE_CSC_R2Y_20;
    volatile U_ISP_CORE_CSC_R2Y_21              ISP_CORE_CSC_R2Y_21;
    volatile U_ISP_CORE_CSC_R2Y_22              ISP_CORE_CSC_R2Y_22;
    volatile unsigned int                     reserved7[2];
    volatile U_ISP_CORE_ADA_CTL                 ISP_CORE_ADA_CTL;
    volatile U_ISP_CORE_ADA_STAT_MAX_VALUE      ISP_CORE_ADA_STAT_MAX_VALUE;
    volatile U_ISP_CORE_ADA_AD_STREN_MAX_VALUE   ISP_CORE_ADA_AD_STREN_MAX_VALUE;
    volatile U_ISP_CORE_ADA_WIN_H_START         ISP_CORE_ADA_WIN_H_START;
    volatile U_ISP_CORE_ADA_WIN_V_START         ISP_CORE_ADA_WIN_V_START;
    volatile U_ISP_CORE_ADA_WIN_H_END           ISP_CORE_ADA_WIN_H_END;
    volatile U_ISP_CORE_ADA_WIN_V_END           ISP_CORE_ADA_WIN_V_END;
    volatile unsigned int                     reserved8[4];
    volatile U_ISP_CORE_RGBIR_CTL               ISP_CORE_RGBIR_CTL;
    volatile U_ISP_CORE_RGBIR_RPC_MAX_VALUE     ISP_CORE_RGBIR_RPC_MAX_VALUE;
    volatile U_ISP_CORE_RGBIR_RPC_COLOR_COFF    ISP_CORE_RGBIR_RPC_COLOR_COFF;
    volatile U_ISP_CORE_RGBIR_RPC_LUMA_COFF     ISP_CORE_RGBIR_RPC_LUMA_COFF;
    volatile U_ISP_CORE_RGBIR_RPC_TH            ISP_CORE_RGBIR_RPC_TH;
    volatile U_ISP_CORE_RGBIR_RPC_TH1           ISP_CORE_RGBIR_RPC_TH1;
    volatile unsigned int                     reserved9[4];
    volatile U_ISP_CORE_2DNR_CTL                ISP_CORE_2DNR_CTL;
    volatile U_ISP_CORE_2DNR_RAW_INTENSITY      ISP_CORE_2DNR_RAW_INTENSITY;
    volatile U_ISP_CORE_2DNR_BAP_INTENSITY      ISP_CORE_2DNR_BAP_INTENSITY;
    volatile U_ISP_CORE_2DNR_EDGE_INTENSITY     ISP_CORE_2DNR_EDGE_INTENSITY;
    volatile U_ISP_CORE_2DNR_LUMA_INTENSITY     ISP_CORE_2DNR_LUMA_INTENSITY;
    volatile U_ISP_CORE_2DNR_CHROMA_INTENSITY   ISP_CORE_2DNR_CHROMA_INTENSITY;
    volatile unsigned int                     reserved10[2];
    volatile U_ISP_CORE_3DNR_CTL                ISP_CORE_3DNR_CTL;
    volatile U_ISP_CORE_3DNR_PRE_LUMA_TH        ISP_CORE_3DNR_PRE_LUMA_TH;
    volatile U_ISP_CORE_3DNR_PRE_LUMA_INTENSITY   ISP_CORE_3DNR_PRE_LUMA_INTENSITY;
    volatile U_ISP_CORE_3DNR_PRE_CHROMA_INTENSITY   ISP_CORE_3DNR_PRE_CHROMA_INTENSITY;
    volatile U_ISP_CORE_3DNR_MID_FILTER_TH      ISP_CORE_3DNR_MID_FILTER_TH;
    volatile U_ISP_CORE_3DNR_PRE_MID_FILTER_TH   ISP_CORE_3DNR_PRE_MID_FILTER_TH;
    volatile U_ISP_CORE_3DNR_CUR_FILTER_TH      ISP_CORE_3DNR_CUR_FILTER_TH;
    volatile U_ISP_CORE_3DNR_LOW_PASS_FILTER_TH   ISP_CORE_3DNR_LOW_PASS_FILTER_TH;
    volatile U_ISP_CORE_3DNR_LUMA_TH            ISP_CORE_3DNR_LUMA_TH;
    volatile U_ISP_CORE_3DNR_MIN_VALUE          ISP_CORE_3DNR_MIN_VALUE;
    volatile U_ISP_CORE_3DNR_LUMA_INTENSITY     ISP_CORE_3DNR_LUMA_INTENSITY;
    volatile U_ISP_CORE_3DNR_CHROMA_INTENSITY   ISP_CORE_3DNR_CHROMA_INTENSITY;
    volatile U_ISP_CORE_3DNR_POST_EDGE_TH       ISP_CORE_3DNR_POST_EDGE_TH;
    volatile U_ISP_CORE_3DNR_POST_LUMA_INTENSITY   ISP_CORE_3DNR_POST_LUMA_INTENSITY;
    volatile U_ISP_CORE_3DNR_POST_CHROMA_INTENSITY   ISP_CORE_3DNR_POST_CHROMA_INTENSITY;
    volatile unsigned int                     reserved11[2];
    volatile U_ISP_CORE_ENH_CTL                 ISP_CORE_ENH_CTL;
    volatile U_ISP_CORE_LTM_GAIN                ISP_CORE_LTM_GAIN;
    volatile U_ISP_CORE_LTM_TH                  ISP_CORE_LTM_TH;
    volatile U_ISP_CORE_ENH_NR_TH               ISP_CORE_ENH_NR_TH;
    volatile U_ISP_CORE_ENH_TH1                 ISP_CORE_ENH_TH1;
    volatile U_ISP_CORE_ENH_TH2                 ISP_CORE_ENH_TH2;
    volatile U_ISP_CORE_SHARP_GAIN              ISP_CORE_SHARP_GAIN;
    volatile unsigned int                     reserved12[3];
    volatile U_ISP_CORE_POST_CTL                ISP_CORE_POST_CTL;
    volatile U_ISP_CORE_CONT_GAIN               ISP_CORE_CONT_GAIN;
    volatile U_ISP_CORE_LUMA_GAIN               ISP_CORE_LUMA_GAIN;
    volatile U_ISP_CORE_SATU_GAIN               ISP_CORE_SATU_GAIN;
    volatile U_ISP_CORE_OTC_STT_VR              ISP_CORE_OTC_STT_VR;
    volatile U_ISP_CORE_OTC_STT_HR              ISP_CORE_OTC_STT_HR;
    volatile U_ISP_CORE_OTC_HEIGHT              ISP_CORE_OTC_HEIGHT;
    volatile U_ISP_CORE_OTC_WIDTH               ISP_CORE_OTC_WIDTH;
    volatile U_ISP_CORE_LDC_CTL                 ISP_CORE_LDC_CTL;
    volatile U_ISP_CORE_LDC_REQ_FREQ            ISP_CORE_LDC_REQ_FREQ;
    volatile U_ISP_CORE_LDC_H_CENTER_POS        ISP_CORE_LDC_H_CENTER_POS;
    volatile U_ISP_CORE_LDC_V_CENTER_POS        ISP_CORE_LDC_V_CENTER_POS;
    volatile U_ISP_CORE_LDC_RECTIFY_CR          ISP_CORE_LDC_RECTIFY_CR;
    volatile U_ISP_CORE_LDC_RECTIFY_CZ          ISP_CORE_LDC_RECTIFY_CZ;
    volatile unsigned int                     reserved14[1];
    volatile U_ISP_CORE_RAM_WR_STATUS           ISP_CORE_RAM_WR_STATUS;
    volatile U_ISP_CORE_RAM_RD_STATUS           ISP_CORE_RAM_RD_STATUS;
    volatile U_ISP_CORE_RAM_READ_LOCK           ISP_CORE_RAM_READ_LOCK;
    volatile unsigned int                     reserved15[5];
    volatile U_ISP_CORE_AF_CTL                  ISP_CORE_AF_CTL;
    volatile U_ISP_CORE_AF_STAT_WIN_H_START     ISP_CORE_AF_STAT_WIN_H_START;
    volatile U_ISP_CORE_AF_STAT_WIN_V_START     ISP_CORE_AF_STAT_WIN_V_START;
    volatile U_ISP_CORE_AF_STAT_WIN_H_END       ISP_CORE_AF_STAT_WIN_H_END;
    volatile U_ISP_CORE_AF_STAT_WIN_V_END       ISP_CORE_AF_STAT_WIN_V_END;
    volatile unsigned int                     reserved16[2];
	
    volatile U_ISP_CORE_AF_MID_FRQ_DATA         ISP_CORE_AF_MID_FRQ_DATA;
    volatile U_ISP_CORE_AF_HIGH_FRQ_DATA        ISP_CORE_AF_HIGH_FRQ_DATA;
    volatile U_ISP_CORE_AF_STAT_PIXEL_NUM       ISP_CORE_AF_STAT_PIXEL_NUM;
    volatile unsigned int                     reserved17[38];
} S_ISP_CORE_REGS_TYPE;

int ISP_CORE_DRV_SET_CoreItcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageActiveWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreImageActiveHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreTestCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreBlcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreBlcOffset(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreBlcRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscHCenter(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscVCenter(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscRRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscGRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscBRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLscIrRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeTarBr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeTarBrRange(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeLExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeMExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeSExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeAgc(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeAdjustCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeExValueMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeExValueMid(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeExValueMin(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeGainMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeGainMid(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeGainMin(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeDnSwitchAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAeDnSwitchWaitTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeDiffMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeDrvSignalMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeCoeffDis(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeCoeffSpeed(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeCoeffAcce(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeDrvManualValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreApeDampManualValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbD65RedGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbD65BlueGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmRrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmRgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmRbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmGrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmGgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmGbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmBrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmBgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmBbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCcmCorrectCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbCorrectDiffTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbResTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbHistTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbRedGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbGreenGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbBlueGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbRedMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbBlueMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbRedMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAwbBlueMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrOverExRatioTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrOverExRatioTh2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrFusionRatioTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrFusionValue1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreWdrFusionValue2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y00(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y01(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y02(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y10(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y11(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y12(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y20(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y21(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreCscR2Y22(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaStatMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaAdStrenMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAdaWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirRpcMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirRpcColorCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirRpcLumaCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirRpcTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRgbirRpcTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrRawIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrBapIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrEdgeIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core2DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPreLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPreLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPreChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPreMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrCurFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrLowPassFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPostEdgeTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPostLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_Core3DnrPostChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreEnhCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLtmGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLtmTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreEnhNrTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreEnhTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreEnhTh2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreSharpGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CorePostCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreContGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLumaGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreSatuGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreOtcSttVr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreOtcSttHr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreOtcHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreOtcWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcReqFreq(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcHCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcVCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcRectifyCr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreLdcRectifyCz(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreRamWrStatus(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAfCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAfStatWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAfStatWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAfStatWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_CORE_DRV_SET_CoreAfStatWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_CORE_DRV_GET_CoreAeValueReady(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeLongCurEx(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeMidCurEx(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeShortCurEx(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeCurDigitalGain(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeCurAveBrightness(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeCurDnStatus(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeExStatus(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAeSum(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAePixelSum(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBlueObjValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBlueHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbRedHistValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbRedHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBypassBlueHistValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBypassBlueHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBypassRedHistValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBypassRedHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbRedValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbGreenValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbBlueValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbOrgRedValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbOrgGreenValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAwbOrgBlueValue(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CorePostCtl(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreRamRdStatus(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreRamReadLock(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAfMidFrqData(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAfHighFrqData(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreAfStatPixelNum(S_ISP_CORE_REGS_TYPE *pstRegs);
int ISP_CORE_DRV_GET_CoreEnhCtl(S_ISP_CORE_REGS_TYPE *pstRegs);
//debug
int ISP_CORE_DRV_GET_CoreRegsVal(S_ISP_CORE_REGS_TYPE *pstRegs);
#endif /*_ISP_CORE_REG_DEF_H_*/

