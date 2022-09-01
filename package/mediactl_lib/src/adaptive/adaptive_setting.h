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

#define ADAPTIVE_WEIGHT_THRESHOLD 0.0
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

typedef struct _ADAPTIVE_USER_ATTR_ISP_CTL_T {
	int nBlcEnable; // 0: disable, 1: enable
	int nLscEnable; // 0: disable, 1: enable
	int nAeEnable; // 0: all disable, 1: exp enable, 2: gain enable, 3: exp & gain enable, ... 16183: all enable
	int nAwbEnable; // 0: all disbale, 1: d65 gain enable, 2: ccm enable, ... 527:
} ADAPTIVE_USER_ATTR_ISP_CTL_T;

typedef struct _ADAPTIVE_USER_ATTR_LIMIT_T {
	int nGainRange[2]; // gain range [0]: min, [1]: max
	int nEtRange[2]; // et range [0]: min, [1]: max
	int nCtScl; // color temperature
} ADAPTIVE_USER_ATTR_LIMIT_T;

typedef struct _ADAPTIVE_USER_ATTR_WEIGHT_T {
	int nSaturationCoeff; // saturation user coeff step1: 0 - 50, step2: 50 - 100
	int nBrightnessCoeff; // luma gain user coeff step: 0 - 100, default 50
	int nContrastCoeff; // contrast gain user coeff step: 0 - 100, default 50
	int nSharpnessCoeff; // sharpness gain user coeff step: 0 - 100, default 50, final val = 50 * adap_sharp
	int n2dnrLevelCoeff; // 2dnr user coeff: step: 0 - 10, default 5
} ADAPTIVE_USER_ATTR_WEIGHT_T;

typedef struct _ADAP_USER_ATTR_PAGE_T
{
	int nAdaptiveUserAttrEnable;
	ADAPTIVE_USER_ATTR_ISP_CTL_T tUserAttrIspCtl;
	ADAPTIVE_USER_ATTR_LIMIT_T tUserAttrLimit;
	ADAPTIVE_USER_ATTR_WEIGHT_T tUserAttrWeight;
} ADAPTIVE_ATTRIBUTE_PAGE_T; // Root Permission for whole adaptive function

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

static struct k510isp_reg_val fixd_f2k_init_reg_list[6] = {
	/* fix params */
	{ISP_CORE_ITC_TTL_V, 0x0}, // itc ttl v
	{ISP_CORE_AE_EX_VALUE_MAX, 0x0}, // max exp lines
	{ISP_CORE_AE_EX_VALUE_MIN, 0x0}, // min exp lines
	{ISP_CORE_AE_GAIN_MAX, 0x0}, // max gain
	{ISP_CORE_AE_GAIN_MIN, 0x0}, // min gain
	{ISP_CORE_SATU_GAIN, 0x0}, // min gain
};

static struct k510isp_reg_val fixd_r2k_init_reg_list[6] = {
	/* fix params */
	{ISP_CORE_ITC_TTL_V, 0x0}, // itc ttl v
	{ISP_CORE_AE_EX_VALUE_MAX, 0x0}, // max exp lines
	{ISP_CORE_AE_EX_VALUE_MIN, 0x0}, // min exp lines
	{ISP_CORE_AE_GAIN_MAX, 0x0}, // max gain
	{ISP_CORE_AE_GAIN_MIN, 0x0}, // min gain
	{ISP_CORE_SATU_GAIN, 0x0}, // min gain
};

static struct k510isp_reg_val dynamic_f2k_reg_list[5] = {

	/* dynamic param */
	{ISP_CORE_AE_VALUE_READY, 0x0}, // ae ready to be writen to sensor
	{ISP_CORE_AE_LONG_CUR_EX, 0x0}, // ae stat cur exposure time(lines)
	{ISP_CORE_AE_CUR_DIGITAL_GAIN, 0x0}, // ae stat cur gain
	{ISP_CORE_AWB_ORG_RED_VALUE, 0x0}, // awb stat red value
	{ISP_CORE_AWB_ORG_BLUE_VALUE, 0x0}, // awb stat blue value
};

// static struct k510isp_reg_val dynamic_r2k_reg_list[5] = {

// 	/* dynamic param */
// 	{ISP_CORE_AE_VALUE_READY, 0x0}, // ae ready to be writen to sensor
// 	{ISP_CORE_AE_LONG_CUR_EX, 0x0}, // ae stat cur exposure time(lines)
// 	{ISP_CORE_AE_CUR_DIGITAL_GAIN, 0x0}, // ae stat cur gain
// 	{ISP_CORE_AWB_RED_VALUE, 0x0}, // awb stat red value
// 	{ISP_CORE_AWB_BLUE_VALUE, 0x0}, // awb stat blue value
// };

static struct k510isp_reg_val adaptive_apply_blc[] = {

	/* follow ae gain */

	{ISP_CORE_BLC_OFFSET, 0x0}, // blc offset
};

static struct k510isp_reg_val adaptive_apply_lsc[] = {

	{ISP_CORE_LSC_R_RATIO, 0x0}, // lsc red ratio
	{ISP_CORE_LSC_G_RATIO, 0x0}, // lsc green ratio
	{ISP_CORE_LSC_B_RATIO, 0x0}, // lsc blue ratio
};

static struct k510isp_reg_val adaptive_apply_sharpness[] = {

	{ISP_CORE_ENH_NR_TH, 0x0}, // sharpness core
	{ISP_CORE_SHARP_GAIN, 0x0}, // sharpness gain
	{ISP_CORE_ENH_TH1, 0x0}, // sharpness threshold 1
	{ISP_CORE_ENH_TH2, 0x0}, // sharpness threshold 2
};

static struct k510isp_reg_val adaptive_apply_ltm[] = {

	{ISP_CORE_LTM_GAIN, 0x0}, // ltm gain
	{ISP_CORE_LTM_TH, 0x0}, // ltm threshold
};

static struct k510isp_reg_val adaptive_apply_2dnr[] = {

	{ISP_CORE_2DNR_RAW_INTENSITY, 0x0}, // 2dnr Raw Domain Intensity
	{ISP_CORE_2DNR_BAP_INTENSITY, 0x0}, // 2dnr Adjacent Pix Intensity
	{ISP_CORE_2DNR_EDGE_INTENSITY, 0x0}, // 2dnr Edge Intensity
	{ISP_CORE_2DNR_LUMA_INTENSITY, 0x0}, // 2dnr Luma Intensit
	{ISP_CORE_2DNR_CHROMA_INTENSITY, 0x0}, // 2dnr Chroma Intensity
};

static struct k510isp_reg_val adaptive_apply_3dnr[] = {

	{ISP_CORE_3DNR_PRE_LUMA_TH, 0x0}, // 3dnr Pre Luma Thres
	{ISP_CORE_3DNR_PRE_LUMA_INTENSITY, 0x0}, // 3dnr Pre Luma Intensity
	{ISP_CORE_3DNR_PRE_CHROMA_INTENSITY, 0x0}, // 3dnr Pre Chroma Intensity
	{ISP_CORE_3DNR_MID_FILTER_TH, 0x0}, // 3dnr Main Middle Filter Thres
	{ISP_CORE_3DNR_PRE_MID_FILTER_TH, 0x0}, // 3dnr Main Prev Frame Mid-Filter
	{ISP_CORE_3DNR_CUR_FILTER_TH, 0x0}, // 3dnr Main Cur Frame Mid-Filter Thres
	{ISP_CORE_3DNR_LOW_PASS_FILTER_TH, 0x0}, // 3dnr Main Low-Pass FilterVal
	{ISP_CORE_3DNR_LUMA_TH, 0x0}, // 3dnr Main Luma Thres
	{ISP_CORE_3DNR_MIN_VALUE, 0x0}, // 3dnr Main Minimum Val
	{ISP_CORE_3DNR_LUMA_INTENSITY, 0x0}, // 3dnr Main Luma Intensity
	{ISP_CORE_3DNR_CHROMA_INTENSITY, 0x0}, // 3dnr Main Chroma Intensity
	{ISP_CORE_3DNR_POST_EDGE_TH, 0x0}, // 3dnr Post Edge Threshold
	{ISP_CORE_3DNR_POST_LUMA_INTENSITY, 0x0}, // 3dnr Post Luma Intensity
	{ISP_CORE_3DNR_POST_CHROMA_INTENSITY, 0x0}, // 3dnr Post Chroma Intensity
};

static struct k510isp_reg_val adaptive_apply_wdr[] = {

	{ISP_CORE_WDR_OVER_EX_RATIO_TH1, 0x0}, // wdr LghtTh1
	{ISP_CORE_WDR_OVER_EX_RATIO_TH2, 0x0}, // wdr LghtTh2
	{ISP_CORE_WDR_FUSION_RATIO_TH, 0x0}, // Fs_Th
	{ISP_CORE_WDR_FUSION_VALUE1, 0x0}, // Fs_K1
	{ISP_CORE_WDR_FUSION_VALUE2, 0x0}, // Fs_K2
};

/* follow exposure value */

static struct k510isp_reg_val adaptive_apply_ae_target[] = {

	{ISP_CORE_AE_TAR_BR, 0x0}, // ae YTarget
	{ISP_CORE_AE_TAR_BR_RANGE, 0x0}, // ae YTarget Range
};

static struct k510isp_reg_val adaptive_apply_awb_range[] = {

	{ISP_CORE_AWB_RED_MIN_VALUE, 0x0}, // awb Rgain Min
	{ISP_CORE_AWB_RED_MAX_VALUE, 0x0}, // awb Rgain Max
	{ISP_CORE_AWB_BLUE_MIN_VALUE, 0x0}, // awb Bgain Min
	{ISP_CORE_AWB_BLUE_MAX_VALUE, 0x0}, // awb Bgain Max
};

static struct k510isp_reg_val adaptive_apply_ccm[] = {

	{ISP_CORE_CCM_RR_COFF, 0x0}, // ccm Rr
	{ISP_CORE_CCM_RG_COFF, 0x0}, // ccm Rg
	{ISP_CORE_CCM_RB_COFF, 0x0}, // ccm Rb
	{ISP_CORE_CCM_GR_COFF, 0x0}, // ccm Gr
	{ISP_CORE_CCM_GG_COFF, 0x0}, // ccm Gg
	{ISP_CORE_CCM_GB_COFF, 0x0}, // ccm Gb
	{ISP_CORE_CCM_BR_COFF, 0x0}, // ccm Br
	{ISP_CORE_CCM_BG_COFF, 0x0}, // ccm Bg
	{ISP_CORE_CCM_BB_COFF, 0x0}, // ccm Bb
};

static struct k510isp_reg_val adaptive_apply_ex_model[] = {

	{ISP_CORE_CONT_GAIN, 0x0}, // contrast gain
	{ISP_CORE_LUMA_GAIN, 0x0}, // luma gain
};

static struct k510isp_reg_val adaptive_apply_post_saturation[] = {
	{ISP_CORE_SATU_GAIN, 0x0}, // post saturation
};

static struct k510isp_reg_val adaptive_apply_color2bw[] = {

	/* color2grey use saturation mode */

	{ISP_CORE_SATU_GAIN, 0x0}, // post saturation
};

static struct k510isp_reg_val adaptive_apply_ada[] = {

	{ISP_CORE_ADA_STAT_MAX_VALUE, 0x0}, //
	{ISP_CORE_ADA_AD_STREN_MAX_VALUE, 0x0}, //
};

enum adaptive_isp_pipeline_e
{
	ADAP_ISP_F2K_PIPELINE,
	ADAP_ISP_R2K_PIPELINE,
	ADAP_ISP_TOF_PIPELINE
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

/* param check Range */

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
// TODO

/* lots of init functions */
int adaptive_setting_param_check(enum adaptive_isp_pipeline_e pipeline);
int adaptiet_convert_init(enum adaptive_isp_pipeline_e isp_pipeline, ADAPTIVE_IMG_TIMING_CFG_T image_timing_cfg);
int adaptive_calc_feture_init_from_reg(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);
int adaptive_param_flag_init(enum adaptive_isp_pipeline_e pipeline);
int adaptive_param_format_init(enum adaptive_isp_pipeline_e pipeline);

/* main functions */
int adaptive_user_attr_page_init(enum adaptive_isp_pipeline_e pipeline);
int adaptive_et_line_time_convert(enum adaptive_isp_pipeline_e isp_pipeline, int itc_ttl_v, float adap_exp_time);
int adaptive_select_moudel_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe, int adap_en, int size, struct k510isp_reg_val adap_param[]);
int adaptive_select_gamma_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe, int adap_en);
int adaptive_ex_param_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);

#endif