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

#ifndef __ADAPTIVE_SETTING_H__
#define __ADAPTIVE_SETTING_H__

#define ADAPTIVE_WEIGHT_THRESHOLD 0 // 0 - 255
#define ADAPTIVE_GAMMA_DAY 0
#define ADAPTIVE_GAMMA_NIGHT 1
#define ADAPTIVE_COLOR_TO_GREY 0
#define ADAPTIVE_GREY_TO_COLOR 1
#define ADAPTIVE_COLOR_GREY_USE_CSM 1
#define ADAPTIVE_COLOR_GREY_USE_CCM 2
#define ADAPTIVE_IR_CUT_DAY_TO_NIGHT 0
#define ADAPTIVE_IR_CUT_NIGHT_TO_DAY 1
#define ADAPTIVE_EXPOSURE_LINE_V 1979
#define ADAPTIVE_ANTI_FLICKER_MODE_50Hz 1
#define ADAPTIVE_ANTI_FLICKER_MODE_60Hz 2
#define ADAPTIVE_ANTI_FLICKER_CORRECT_PRECENT 150
#define ADAPTIVE_ANTI_FLICKER_50Hz_PERIOD (1000000/(50 * 2))
#define ADAPTIVE_ANTI_FLICKER_60Hz_PERIOD (1000000/(60 * 2))
#define ADAPTIVE_ANTI_FLICKER_FPS 30
#define ADAPTIVE_UNIT_CONVERT 1000
#define ADAPTIVE_ET_LINE_OFFSET_RATE 0.50
#define ADAPTIVE_CORRECT_GAIN_OFFSET 384
#define ADAPTIVE_GAIN_MAX_CORRECT_OFFSET 8 // 256 * 0.03
#define ADAPTIVE_3A_SYNC_FOLLOW_SELECT 1 // need f2k & r2k sync stat is 1, 0: nothing 1 : follow f2k, 2 : follow r2k(can not work normaly, need fix ae_wren = 1)
#define ADAPTIVE_AE_EHN_MODE_NORMAL 0
#define ADAPTIVE_AE_EHN_MODE_BACKLIGHT 1
#define ADAPTIVE_AE_EHN_MODE_STRONG_LIGHT_SUPPRESSION 2
#define ADAPTIVE_IR_CUT_MAX_LEVEL 20
#define ADAPTIVE_IR_CUT_MIN_LEVEL 0

/* struct define */
typedef struct _ADAPTIVE_USER_ATTR_ISP_CTL_T {
	int nLscEnable; // 0: disable, 1: enable
	int nLdcEnable; // 0: disable, 1: enable
	int nAeEnable; // 0: manual ae, 1: auto ae
	int nAeEnhMode; // 0: normal, 1: ae back light compensation, 2: strong light suppression
	int nWdrEnable; // 0: normal, 1: linner-wdr enable
	int nAwbEnable; // 0: all disbale, 1: d65 gain enable, 2: ccm enable, ... 527:
	int nFlip; // 0: normal, 1: hflip, 2: vflip, 3: hvflip
	int nAntiflickerScl; // 0: disable, 1: 50Hz auto, 2: 50Hz force 3: 60Hz auto, 4: 60Hz force
	int nDefogEn; // 0: disable, 1: enable, will use isp ada and disable adaptive-ADA
    int nIrCutEnable; // 0: disable, 1: enable
    int nIrCutFilterType; // 0: day2night pcs, 1: night2day pcs
} ADAPTIVE_USER_ATTR_ISP_CTL_T;

typedef struct _ADAPTIVE_USER_ATTR_LIMIT_T {
	int nGainRange[2]; // gain range [0]: min, [1]: max
	int nEtRange[2]; // et range [0]: min, [1]: max
	int nCtScl; // color temperature
    int nIrCutSwMode; // 0: auto(default), 1: manual mode
} ADAPTIVE_USER_ATTR_LIMIT_T;

typedef struct _ADAPTIVE_USER_ATTR_WEIGHT_T {
	int nSaturationCoeff; // saturation user coeff step1: 0 - 50, step2: 50 - 100
	int nBrightnessCoeff; // luma gain user coeff step: 0 - 100, default 50
	int nContrastCoeff; // contrast gain user coeff step: 0 - 100, default 50
	int nSharpnessCoeff; // sharpness gain user coeff step: 0 - 100, default 50, final val = 50 * adap_sharp
	int n2dnrLevelCoeff; // 2dnr user coeff: step: 0 - 10, default 5
	/* ae param */
	int nAeBacklightCoeff;
	int nAeStronglightCoeff;
	int nWdrCoeff;
} ADAPTIVE_USER_ATTR_WEIGHT_T;

typedef struct _ADAPTIVE_USER_MENU_3A_T {
	int nCurGain; // current gain: 1~15.9906x, default 2x, over range will use min or max value
	int nCurExpTime; // current exposure time(us)
	int nCurWbRGain; //
	int nCurWbGGain; //
	int nCurWbBGain; //
} ADAPTIVE_USER_MENU_3A_T;

typedef struct _ADAP_USER_ATTR_PAGE_T
{
	int nWritten;
	int nAdaptiveUserAttrEnable;
	int nAdaptiveUserAeMode; // only use to ae auto/handle switch 0: sw, 1: hw
	int nAeSync; // only use for ae sync in dual camera & sw ae
	ADAPTIVE_USER_ATTR_ISP_CTL_T tUserAttrIspCtl;
	ADAPTIVE_USER_ATTR_LIMIT_T tUserAttrLimit;
	ADAPTIVE_USER_ATTR_WEIGHT_T tUserAttrWeight;
	ADAPTIVE_USER_MENU_3A_T tUserMenu3A;
} ADAPTIVE_ATTRIBUTE_PAGE_T; // Root Permission for whole adaptive function

typedef struct {
    // attr page ctl
	int nAttrPageEnFlag;
	// isp ctl
    int nAeEnhModeFlag;
	int nWdrEnableFlag;
	int nAeEnFlag;
    int nAwbEnableFlag;
    int nLdcEnableFlag;
    int nLscEnableFlag;
    int nFlipFlag;
	int nAntiflickerFlag;
	int nDefogFlag;
    // isp limit
    int nCtSclFlag;
    int nEtFlag;
    int nGainFlag;
    // isp weight
    int n2dnrFlag;
    int nBrightnessFlag;
    int nContrastFlag;
    int nSaturationFlag;
    int nSharpnessFlag;
	int nBackLightFlag;
	int nStrongLightFlag;
	int nWdrLevelFlag;
    // 3a manual
    int nCurExpFlag;
    int nCurGainFlag;
    int nRGainFlag;
    int nGGainFlag;
    int nBGainFlag;

	// sum
	int nSum;
} ADAPTIVE_ATTR_FLAG_T;

/* enum define */

enum weight_mode_e
{
	AE_GAIN_WEIGHT,
	AE_EV_WEIGHT,
};

enum ev_type_e
{
	EV_TYPE_GAMMA,
	EV_TYPE_COLOR_GREY_SWITCH,
	EV_TYPE_IR_CUT,
};

typedef struct
{
	// dynamic params
	ADAPTIVE_ISP_CALC_PARAM_T isp_adap_param;
	ADAPTIVE_ISP_3A_STAT_T isp_3a_stat; // will destory in the future
	// fix params
	ADAPTIVE_IMG_TIMING_CFG_T image_timing_cfg;
	// correct result
	ADAPTIVE_ISP_3A_STAT_T isp_3a_stat_correct;
	// ex model value
	ADAPTIVE_ISP_EX_MODEL_VAL_T isp_ex_val;

} ADAPTIVE_INIT_PARAM_T;

enum adaptive_isp_pipeline_e
{
	ADAP_ISP_F2K_PIPELINE,
	ADAP_ISP_R2K_PIPELINE,
	ADAP_ISP_TOF_PIPELINE
};

enum adap_callback_id
{
    ADAP_CALLBACK_ID_START = -1, // -1
    ADAP_CALLBACK_ID_BLC, // 0
    ADAP_CALLBACK_ID_LSC, // 1
    ADAP_CALLBACK_ID_SHARPNESS, // 2
    ADAP_CALLBACK_ID_LTM, // 3
    ADAP_CALLBACK_ID_2DNR, // 4
    ADAP_CALLBACK_ID_3DNR, // 5
    ADAP_CALLBACK_ID_WDR, // 6
    ADAP_CALLBACK_ID_CCM, // 7
    ADAP_CALLBACK_ID_AWB, // 8
    ADAP_CALLBACK_ID_GAMMA, // 9
    ADAP_CALLBACK_ID_IRCUT, // 10
    ADAP_CALLBACK_ID_SATURATION, // 11
    ADAP_CALLBACK_ID_COLOR2BW, // 12
    ADAP_CALLBACK_ID_ADA, // 13
    ADAP_CALLBACK_ID_END, // 14
};

enum ir_cut_mode_user_e {
	ADAPTIVE_USER_IR_CUT_NIGHT,
 	ADAPTIVE_USER_IR_CUT_DAY,
};

// static struct k510isp_reg_val adaptive_apply_rgb_gamma_table = {0x0400, 0x0};

typedef struct {
    char * cSensor0Name;
    char * cSensor1Name;
    ADAPTIVE_ISP_PIPELINE_PARAM_T * tAdapIspParamF2k;
    ADAPTIVE_ISP_PIPELINE_PARAM_T * tAdapIspParamR2k;
} ADAPTIVE_SENSOR_NAME_T;

typedef struct {
	int size;
 	ADAPTIVE_SENSOR_NAME_T *tAdaptiveSensorName;
} ADAPTIVE_SENSOR_NAME_S_T;

typedef union
{
    struct
    {
        unsigned int            : 5   ; /* [0 ..4 ]      */
        unsigned int mirror_ctl : 1   ; /* [5 ]      */
        unsigned int            : 26  ; /* [32..7 ]  */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_ITC_CTL_U;

typedef union
{
    struct
    {
        unsigned int            : 3   ; /* [0 1 2]      */
        unsigned int awb_handle : 1   ; /* [3 ]      */
        unsigned int            : 28  ; /* [4 .. 32]  */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_AWB_CTL_U;

typedef union
{
    struct
    {
        unsigned int            : 5   ; /* [0 1 2 3 4]      */
        unsigned int chroma_en  : 1   ; /* [5 ]      */
        unsigned int            : 26  ; /* [6 .. 31]  */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_2DNR_CTL_U;

typedef union
{
    struct
    {
        unsigned int auto_exp_en  : 1   ; /* [0]      */
        unsigned int auto_gain_en : 1   ; /* [1]      */
        unsigned int              : 6   ; /* [2 .. 7]      */
        unsigned int ae_win_sl    : 2   ; /* [8 9]      */
        unsigned int ae_md_sl     : 2   ; /* [10 11]      */
        unsigned int              : 20   ; /* [12 31 ]      */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_AE_CTL_U;

typedef union
{
    struct
    {
        unsigned int              : 5   ; /* [0 ... 4]  */
        unsigned int ada_adp_en   : 1   ; /* [5]     */
        unsigned int              : 3   ; /* [6 7 8]     */
        unsigned int ada_md_sl    : 2   ; /* [9 10]     */
        unsigned int              : 21  ; /* [11 31]    */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_DEFOG_CTL_U;

typedef union
{
	struct
	{
		unsigned int hflip : 1;
		unsigned int vflip : 1;
		unsigned int :30;
	} bits;
	unsigned int u32;
} FLIP_VAL_U;

typedef union
{
    struct
    {
        unsigned int attr_en_flag      : 1   ; /* [ 0  ] */
        unsigned int ae_sync_flag      : 1   ; /* [ 1  ] */
        unsigned int ehn_mode_flag     : 1   ; /* [ 2  ] */
        unsigned int ae_en_flag        : 1   ; /* [ 3  ] */
        unsigned int awb_en_flag       : 1   ; /* [ 4  ] */
        unsigned int lsc_en_flag       : 1   ; /* [ 5  ] */
        unsigned int ldc_en_flag       : 1   ; /* [ 6  ] */
        unsigned int flip_flag         : 1   ; /* [ 7  ] */
        unsigned int anti_flicker_flag : 1   ; /* [ 8  ] */
        unsigned int defog_en_flag     : 1   ; /* [ 9  ] */
        unsigned int wdr_en_flag       : 1   ; /* [ 10 ] */
        unsigned int ct_flag           : 1   ; /* [ 11 ] */
        unsigned int et_min_flag       : 1   ; /* [ 12 ] */
        unsigned int et_max_flag       : 1   ; /* [ 13 ] */
        unsigned int gain_min          : 1   ; /* [ 14 ] */
        unsigned int gain_max          : 1   ; /* [ 15 ] */
        unsigned int nr2d_flag         : 1   ; /* [ 16 ] */
        unsigned int bright_flag       : 1   ; /* [ 17 ] */
        unsigned int contrast_flag     : 1   ; /* [ 18 ] */
        unsigned int saturation_flag   : 1   ; /* [ 19 ] */
		unsigned int sharpness_flag    : 1   ; /* [ 20 ] */
		unsigned int backlight_flag    : 1   ; /* [ 21 ] */
		unsigned int stronglight_flag  : 1   ; /* [ 22 ] */
        unsigned int wdr_level_flag    : 1   ; /* [ 23 ] */
        unsigned int cur_exp_flag      : 1   ; /* [ 24 ] */
        unsigned int cur_gain_flag     : 1   ; /* [ 25 ] */
        unsigned int cur_r_gain_flag   : 1   ; /* [ 26 ] */
        unsigned int cur_g_gain_flag   : 1   ; /* [ 27 ] */
        unsigned int cur_b_gain_flag   : 1   ; /* [ 28 ] */
        unsigned int ir_cut_en_flag    : 1   ; /* [ 29 ] */
        unsigned int ir_cut_ctl_flag   : 1   ; /* [ 30 ] */
        unsigned int ir_cut_ft_type    : 1   ; /* [ 31 ] */
    } bits;
    unsigned int u32;
} ADAPTIVE_ATTR_STAT_FLAG_U;

typedef union
{
    struct
    {
        unsigned int gain_weight_0_flag      : 1   ; /* [ 0  ] */
        unsigned int gain_weight_1_flag      : 1   ; /* [ 1  ] */
        unsigned int ae_ev_weight_0_flag     : 1   ; /* [ 2  ] */
        unsigned int ae_ev_weight_1_flag     : 1   ; /* [ 3  ] */
        unsigned int saturation_weight_flag  : 1   ; /* [ 4  ] */
        unsigned int gain_range_0_flag       : 1   ; /* [ 5  ] */
        unsigned int gain_range_1_flag       : 1   ; /* [ 6  ] */
        unsigned int gamma_curve_flag        : 1   ; /* [ 7  ] */
        unsigned int color_grey_flag         : 1   ; /* [ 8  ] */
        unsigned int ct_flag                 : 1   ; /* [ 9  ] */
        unsigned int ae_ev_range_0_flag      : 1   ; /* [ 10 ] */
        unsigned int ae_ev_range_1_flag      : 1   ; /* [ 11 ] */
        unsigned int ir_cut_flag             : 1   ; /* [ 12 ] */
        unsigned int ada_flag                : 1   ; /* [ 13 ] */
        unsigned int reserved                : 18  ; /* [14 .. 31] */
    } bits;
    unsigned int u32;
} ADAPTIVE_ISP_WEIGHT_FLAG_U;

/* user callback function */
typedef int (* __AdapCallBack)(void *);

/* callback struct */
typedef struct __ADAP_CB_T
{
    __AdapCallBack pAcbfunc; // callback function
    int nSize; // such as sizeof(CB_IR_CUT_T), depth copy need
    enum adap_callback_id nAcbId; // callback moudel id, adap need know which use it
} ADAP_CB_T;

typedef struct __CB_IR_CUT_T
{
    int nIrCutCtl; // 0:day2night, 1: night2day
    int nSensor; // 0: sensor0, 1: sensor1
} CB_IR_CUT_T;

/* param check Range */
#define ADAPTIVE_PARAM_CHECK_AE_Y_TARGET 255
#define ADAPTIVE_PARAM_CHECK_BLC 4095
#define ADAPTIVE_PARAM_CHECK_LSC 511
#define ADAPTIVE_PARAM_CHECK_SHARPNESS_CORE_GAIN 255
#define ADAPTIVE_PARAM_CHECK_SHARPNESS_TH 4095
#define ADAPTIVE_PARAM_CHECK_LTM 255
#define ADAPTIVE_PARAM_CHECK_2DNR_RAWKL 255
#define ADAPTIVE_PARAM_CHECK_2DNR_JLTH 511
#define ADAPTIVE_PARAM_CHECK_2DNR_EGK 1023
#define ADAPTIVE_PARAM_CHECK_2DNR_YK 255
#define ADAPTIVE_PARAM_CHECK_2DNR_CK 255
#define ADAPTIVE_PARAM_CHECK_2DNR_CK_ENABLE_GAIN 768 // 3 * 256
#define ADAPTIVE_PARAM_CHECK_3DNR_DP_THY 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DP_THYP 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DP_THCP 255
#define ADAPTIVE_PARAM_CHECK_3DNR_MID_TH 255
#define ADAPTIVE_PARAM_CHECK_3DNR_MTP_TH 255
#define ADAPTIVE_PARAM_CHECK_3DNR_MTC_TH 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DM_YMK 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DM_THY 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DM_MIN 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DM_THW0 255
#define ADAPTIVE_PARAM_CHECK_3DNR_CHROMA_INTENSITY 255
#define ADAPTIVE_PARAM_CHECK_3DNR_EG_TH 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DB_THYP 255
#define ADAPTIVE_PARAM_CHECK_3DNR_DB_THCP 255
#define ADAPTIVE_PARAM_CHECK_WDR_LGHT_TH 4095
#define ADAPTIVE_PARAM_CHECK_WDR_FS_TH 255
#define ADAPTIVE_PARAM_CHECK_WDR_FS_KN 255
#define ADAPTIVE_PARAM_CHECK_CCM_WB_GAIN 1023
#define ADAPTIVE_PARAM_CHECK_CCM_RR_GG_BB 511
#define ADAPTIVE_PARAM_CHECK_CCM_RG_RB_GR_GB_BR_BG 256
#define ADAPTIVE_PARAM_CHECK_AWB 1023
#define ADAPTIVE_PARAM_CHECK_IMX219_EXP_TIME 33333
#define ADAPTIVE_PARAM_CHECK_IMX219_GAIN 4095

/* param check error code */
#define ADAPTIVE_CALLBACK_REG_SUCCESS (0)
#define ADAPTIVE_CALLBACK_REG_FAIL (-1)
#define ADAPTIVE_CALLBACK_FUNC_NULL (-2)
#define ADAPTIVE_CALLBACK_ID_OVER_RANGE (-3)
#define ADAPTIVE_CALLBACK_ID_NOT_MATCH (-4)

/* ir cut level error code */
#define ADAPTIVE_IR_CUT_SET_EV_SUCCESS (0)
#define ADAPTIVE_IR_CUT_SET_VAL_SUCCESS (0)
#define ADAPTIVE_IR_CUT_EV_LV_OVER_RANGE (-1)
#define ADAPTIVE_IR_CUT_EV_LV_DIFF_LESS_THAN_TWO (-2)
#define ADAPTIVE_IR_CUT_GET_EV_LV_FAILED (-3)
#define ADAPTIVE_IR_CUT_SET_EV_LV_FAILED (-4)
/* callback reg function */
int adaptive_cb_assign(ADAP_CB_T * acb);

/* lots of init functions */
int adaptive_setting_param_check(enum adaptive_isp_pipeline_e pipeline);
int adaptiet_convert_init(enum adaptive_isp_pipeline_e isp_pipeline, ADAPTIVE_IMG_TIMING_CFG_T image_timing_cfg);
int adaptive_calc_feture_init_from_reg(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);
int adaptive_param_flag_init(enum adaptive_isp_pipeline_e pipeline);
int adaptive_param_format_init(enum adaptive_isp_pipeline_e pipeline);

/* n: number of devices, ...  &(struct media_entity) f2k r2k sensor0 sensor1 */
int adaptive_device_init(int n, ...);

/* main functions */
int adaptive_user_attr_page_init(enum adaptive_isp_pipeline_e pipeline);
// int adaptive_user_attr_page_init(enum adaptive_isp_pipeline_e pipeline, struct isp_core_cfg_info * isp_core_cfg);
int adaptive_et_line_time_convert(enum adaptive_isp_pipeline_e isp_pipeline, int itc_ttl_v, int adap_exp_time);
int adaptive_select_moudel_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe, int adap_en, int size, struct k510isp_reg_val adap_param[]);
int adaptive_select_moudel_get(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe, int adap_en, int size, struct k510isp_reg_val adap_param[]);
int adaptive_select_gamma_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe, int adap_en);
int adaptive_ex_param_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);
int adaptive_attr_page_isp_moudel_apply(enum adaptive_isp_pipeline_e pipeline);
// int adaptive_mirror_flip_apply(enum adaptive_isp_pipeline_e pipeline, int adap_en, struct media_entity * pipe);
int adaptive_param_campare(enum adaptive_isp_pipeline_e pipeline, ADAPTIVE_ISP_WEIGHT_PARAM_T * cur_isp_weight);
/* callback */
int adaptive_callback_register(ADAP_CB_T * acb);

/* flip_level 0:normal, 1:hflip, 2:vflip, 3: hvflip */
int adaptive_mirror_flip_apply(enum adaptive_isp_pipeline_e pipeline, int flip_level);

/* ir cut */
int adap_ir_cut_ev_get(enum adaptive_isp_pipeline_e pipeline, enum ir_cut_mode_user_e ir_cut_mode);
int adap_ir_cut_ev_set(enum adaptive_isp_pipeline_e pipeline, enum ir_cut_mode_user_e ir_cut_mode, int level);
float adap_ir_cut_hold_time_get(enum adaptive_isp_pipeline_e pipeline, enum ir_cut_mode_user_e ir_cut_mode);
int adap_ir_cut_hold_time_set(enum adaptive_isp_pipeline_e pipeline, enum ir_cut_mode_user_e ir_cut_mode, float hold_time);
unsigned short adap_ir_cut_lv_calc(enum adaptive_isp_pipeline_e pipeline, int ev);
#endif