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

#ifndef _ISP_3D_CORE_REG_DEF_H_
#define _ISP_3D_CORE_REG_DEF_H_

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
        unsigned int    reserved0                       : 1   ; /* [0 ]      */
        unsigned int    gamma_grb_table_cfg            : 1   ; /* [1 ]      */
        unsigned int    reserved1                      : 30  ; /* [31..2 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_CORE_RAM_WR_READY;

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
} U_TOF_CORE_RAM_RD_DONE;

typedef struct
{
    volatile U_TOF_CORE_ITC_CTL                 TOF_CORE_ITC_CTL;
    volatile U_TOF_CORE_ITC_HEIGHT              TOF_CORE_ITC_HEIGHT;
    volatile U_TOF_CORE_ITC_WIDTH               TOF_CORE_ITC_WIDTH;
    volatile U_TOF_CORE_ITC_VSTART               TOF_CORE_ITC_VSTART;
    volatile U_TOF_CORE_ITC_HSTART               TOF_CORE_ITC_HSTART;
    volatile U_TOF_CORE_ITC_ACTIVE_WIDTH        TOF_CORE_ITC_ACTIVE_WIDTH;
    volatile U_TOF_CORE_ITC_ACTIVE_HEIGHT       TOF_CORE_ITC_ACTIVE_HEIGHT;
    volatile U_TOF_CORE_ITC_ACTIVE_START_LINE     TOF_CORE_ITC_ACTIVE_START_LINE;
    volatile U_TOF_CORE_SENSOR_SEL              TOF_CORE_SENSOR_SEL;
    volatile U_TOF_CORE_GEN_CTL                 TOF_CORE_GEN_CTL;
    volatile U_TOF_CORE_GRAY_TH                 TOF_CORE_GRAY_TH;
    volatile unsigned int                       reserved0[9];
    volatile U_TOF_CORE_AE_CTL                  TOF_CORE_AE_CTL;
    volatile U_TOF_CORE_AE_WIN_HSTART            TOF_CORE_AE_WIN_HSTART;
    volatile U_TOF_CORE_AE_WIN_VSTART            TOF_CORE_AE_WIN_VSTART;
    volatile U_TOF_CORE_AE_WIN_H_END            TOF_CORE_AE_WIN_H_END;
    volatile U_TOF_CORE_AE_WIN_V_END            TOF_CORE_AE_WIN_V_END;
    volatile U_TOF_CORE_AE_TAR_BRIGHT           TOF_CORE_AE_TAR_BRIGHT;
    volatile U_TOF_CORE_AE_TAR_BRIGHT_RANGE     TOF_CORE_AE_TAR_BRIGHT_RANGE;
    volatile U_TOF_CORE_AE_EX_TIME              TOF_CORE_AE_EX_TIME;
    volatile unsigned int                       reserved1[1];
    volatile U_TOF_CORE_AE_AGC                  TOF_CORE_AE_AGC;
    volatile U_TOF_CORE_AE_AD_FREQ              TOF_CORE_AE_AD_FREQ;
    volatile U_TOF_CORE_AE_AD_STEP_MAX           TOF_CORE_AE_AD_STEP_MAX;
    volatile U_TOF_CORE_AE_EX_VALUE_MAX         TOF_CORE_AE_EX_VALUE_MAX;
    volatile U_TOF_CORE_AE_EX_VALUE_MID         TOF_CORE_AE_EX_VALUE_MID;
    volatile U_TOF_CORE_AE_EX_VALUE_MIN         TOF_CORE_AE_EX_VALUE_MIN;
    volatile U_TOF_CORE_AE_GAIN_MAX             TOF_CORE_AE_GAIN_MAX;
    volatile U_TOF_CORE_AE_GAIN_MID             TOF_CORE_AE_GAIN_MID;
    volatile U_TOF_CORE_AE_GAIN_MIN             TOF_CORE_AE_GAIN_MIN;
    volatile unsigned int                       reserved2[12];
    volatile U_TOF_CORE_AE_VALUE_READY          TOF_CORE_AE_VALUE_READY;
    volatile U_TOF_CORE_AE_LONG_CUR_EX          TOF_CORE_AE_LONG_CUR_EX;
    volatile U_TOF_CORE_AE_SHORT_CUR_EX         TOF_CORE_AE_SHORT_CUR_EX;
    volatile U_TOF_CORE_AE_CUR_DIGITAL_GAIN     TOF_CORE_AE_CUR_DIGITAL_GAIN;
    volatile U_TOF_CORE_AE_CUR_AVE_BRIGHTNESS   TOF_CORE_AE_CUR_AVE_BRIGHTNESS;
    volatile U_TOF_CORE_AE_EX_STATUS            TOF_CORE_AE_EX_STATUS;
    volatile U_TOF_CORE_AE_SUM                  TOF_CORE_AE_SUM;
    volatile U_TOF_CORE_AE_PIXEL_SUM            TOF_CORE_AE_PIXEL_SUM;
    volatile unsigned int                       reserved3[63];
    volatile U_TOF_CORE_2DNR_CTL                TOF_CORE_2DNR_CTL;
    volatile U_TOF_CORE_2DNR_GRAY               TOF_CORE_2DNR_GRAY;
    volatile U_TOF_CORE_2DNR_DEPTH              TOF_CORE_2DNR_DEPTH;
    volatile unsigned int                       reserved4[24];
    volatile U_TOF_CORE_POST_CTL                TOF_CORE_POST_CTL;
    volatile U_TOF_CORE_CONT_GAIN               TOF_CORE_CONT_GAIN;
    volatile U_TOF_CORE_LUMA_GAIN               TOF_CORE_LUMA_GAIN;
    volatile U_TOF_CORE_SATU_GAIN               TOF_CORE_SATU_GAIN;
    volatile unsigned int                       reserved5[47];
    volatile U_TOF_CORE_RAM_WR_READY            TOF_CORE_RAM_WR_READY;
    volatile U_TOF_CORE_RAM_RD_DONE             TOF_CORE_RAM_RD_DONE;
    volatile unsigned int                       reserved6[54];
} S_TOF_CORE_REGS_TYPE;


int TOF_CORE_DRV_SET_CoreItcCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcHeight(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcWidth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcVStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcHStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcActiveWidth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcActiveHeight(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreItcActiveStartLine(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreSensorSel(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreGenCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreGrayTHCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeWinHStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeWinVStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeWinHEnd(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeWinVEnd(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeTarBright(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeTarBrightRange(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeExTime(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeAgc(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeAdFreq(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeAdStepMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeExValueMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeExValueMid(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeExValueMin(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeGainMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeGainMid(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreAeGainMin(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_Core2DnrCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_Core2DnrGray(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_Core2DnrDepth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CorePostCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreContGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreLumaGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreSatuGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_CORE_DRV_SET_CoreRamWrStatus(S_TOF_CORE_REGS_TYPE *pstRegs,unsigned int udata);
unsigned int TOF_CORE_DRV_GET_CoreRamRdDone(S_TOF_CORE_REGS_TYPE *pstRegs);
//DEBUG
int TOF_CORE_DRV_GET_CoreRegsVal(S_TOF_CORE_REGS_TYPE *pstRegs);

#endif /*_ISP_3D_CORE_REG_DEF_H_*/

