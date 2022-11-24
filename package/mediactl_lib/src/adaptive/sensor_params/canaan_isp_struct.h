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

#ifndef __CANAAN_ISP_STRUCT_H__
#define __CANAAN_ISP_STRUCT_H__

#define ADAPTIVE_AE_ROUTE_STEPS 5 // real 5
#define ADAPTIVE_GAIN_ROUTE_STEPS 5 // real 7
#define ADAPTIVE_GAMMA_ROUTE_STEPS 2
#define ADAPTIVE_CCM_TEMPERATURE_NUM 6 // real 6
#define ADAPTIVE_IR_CUT_MODE_NUM 2
#define ADAPTIVE_COLOR_GREY_SWITCH_MODE_NUM 2
#define ADAPTIVE_GAMMA_CURVE_INDEX_NUM 256
#define ADAPTIVE_ADA_ROUTE_STEPS 5
#define ADAPTIVE_3A_SYNC_FOLLOW_DISABLE 0
#define ADAPTIVE_3A_SYNC_FOLLOW_F2K 1
#define ADAPTIVE_3A_SYNC_FOLLOW_R2K 2
#define ADAPTIVE_AWB_RANGE_NUM 2 // real 2
#define ADAPTIVE_CCM_COEFF_SATURATION_WEIGHT 512
#define ADAPTIVE_CCM_COEFF_SATURATION_WEIGHT_HALF 256

/* AE */

typedef struct {
    int nAeYTarget;
    int nAeYTargetRange;
} _AE_CTL_PARAM_T;

typedef struct {
    int nExposureTime;      /* 0 - 40000 us */
    int nExposureGain;      /* 256 - 8192; 1x is 256 */
    _AE_CTL_PARAM_T tAeCtlParam;
} ISP_AE_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    int nAntiFlickerSelect; /* 0: Anti_Flicker_None; 1: Anti_Flicker_50Hz; 2: Anti_Flicker_60Hz */
    ISP_AE_PARAM_T tAeParam[ADAPTIVE_AE_ROUTE_STEPS];
} ADAPTIVE_ISP_AE_PARAM_T;

/* Gain Range */

typedef struct {
    int nGain[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_AE_GAIN_PARAM_T;

/*
* BLC
* follow ae gain
*/

typedef struct {
    unsigned short nOffset;            /* default 220 */
} _BLC_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _BLC_CTL_PARAM_T tBlcCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_BLC_PARAM_T;

/*
* LSC
* follow ae gain
*/

typedef struct {
    unsigned short nLscRedRatio;
    unsigned short nLscGreenRatio;
    unsigned short nLscBlueRatio;
} _LSC_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _LSC_CTL_PARAM_T tLscCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_LSC_PARAM_T;

/*
* SHARPNESS
* follow ae gain
*/

typedef struct {
    unsigned short nSharpnessCore;
    unsigned short nSharpnessThres[2]; /* [0]: threshold0 [1]: threshold1 */
    unsigned short nSharpnessGain;     /* TBD */
} _SHARPNESS_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _SHARPNESS_CTL_PARAM_T tSharpnessCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_SHARPNESS_PARAM_T;

/*
* LTM
* follow ae gain
*/

typedef struct {
    unsigned short nLtmGain;
    unsigned short nLtmThres;
} _LTM_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _LTM_CTL_PARAM_T tLtmCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_LTM_PARAM_T;

/*
* 2D NR
* follow ae gain
*/

typedef struct {
    unsigned short nRawDomainIntensity;
    unsigned short n2dAdjacentPixIntensity;
    unsigned short n2dEdgeIntensity;
    unsigned short n2dLumaIntensit;
    unsigned short n2dChromaIntensity;
} _2D_DENOISE_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _2D_DENOISE_CTL_PARAM_T t2dNoiseCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_2D_DENOISE_PARAM_T;

/*
* 3D NR
* follow ae gain
*/

typedef struct {
    unsigned short nPre3dLumaThres;   /* dp thy */
    unsigned short nPre3dLumaIntensity;     /* dp thyp */
    unsigned short nPre3dChromaIntensity;    /* dp thcp */
    unsigned short nMain3dMiddleFilterThres; /*  */
    unsigned short nMain3dPrevFrameMidFilter;
    unsigned short nMain3dCurFrameMidFilterThres;
    unsigned short nMain3dLowPassFilterVal;
    unsigned short nMain3dLumaThres;
    unsigned short nMain3dMinimumVal;
    unsigned short nMain3dLumaIntensity; /* dm thyp */
    unsigned short nMain3dChromaIntensity; /* dm thcp */
    unsigned short nPost3dEdgeThreshold; /* db theg */
    unsigned short nPost3dLumaIntensity; /* db thyp */
    unsigned short nPost3dChromaIntensity; /* db thcp */
} _3D_DENOISE_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _3D_DENOISE_CTL_PARAM_T t3dNoiseCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_3D_DENOISE_PARAM_T;

/*
* WDR
* follow ae gain
*/

typedef struct {
    unsigned short nLghtTh[2]; /* Threshold of overexposure ratio [0] used for 3 frames mode; [1] used for 2 frames mode */
    unsigned short nFsTh; /* threshold of WDR fusion */
    unsigned short nFsK[2]; /* WDR image fusion handle value; [0] used for 3 frames mode; [1] used for 2 frames mode */
} _WDR_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _WDR_CTL_PARAM_T tWdrCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_WDR_PARAM_T;

/*
* CCM
* follow awb gain
*/

typedef struct {
    int nCtCcm[3][3]; /* [0][0]: Rr [0][1]: Rg [0][2]: Rb; [1][0]: Gr [1][1]: Gg [1][2]: Gb; [2][0]: Br [2][0]: Bg [2][0]: Bb*/
} _CCM_CTL_PARAM_T;

typedef struct {
    unsigned short nRGain;
    unsigned short nBGain;
    _CCM_CTL_PARAM_T tCcmCtlParam;
} ISP_CCM_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    ISP_CCM_PARAM_T tCcmParam[ADAPTIVE_CCM_TEMPERATURE_NUM];
} ADAPTIVE_ISP_CCM_PARAM_T;

/*
* AWB
* follow ae
*/

typedef struct {
    unsigned short nRGain[2]; /* [0]: Min; [1]: Max */
    unsigned short nBGain[2]; /* [0]: Min; [1]: Max */
} _AWB_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _AWB_CTL_PARAM_T tAwbCtlParam[ADAPTIVE_AE_ROUTE_STEPS];
} ADAPTIVE_ISP_AWB_PARAM_T;

/*
* GAMMA
* follow ae gain & exposure
*/

typedef struct {
    unsigned short nGammaCurve[ADAPTIVE_GAMMA_CURVE_INDEX_NUM];
} _GAMMA_CTL_PARAM_T;

typedef struct {
    int nEtGamma;
    int nGainGamma;
    _GAMMA_CTL_PARAM_T tGammaCtlParam;
} ISP_GAMMA_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    ISP_GAMMA_PARAM_T tGammaParam[ADAPTIVE_GAMMA_ROUTE_STEPS];
} ADAPTIVE_ISP_GAMMA_PARAM_T;

/*
* IR CUT
* follow ae gain & exposure
* callback from user
*/

typedef struct {
    unsigned short nHoldTime;
    unsigned short nIrCutMode;
} _IR_CUT_CTL_PARAM;

typedef struct {
    unsigned short nExposureTime;
    unsigned short nGain;
    _IR_CUT_CTL_PARAM tIrCutCtlParam;
    int nIrCutCtlMode; // ir cut auto/manual ctl mode 0 / 1
} ISP_IR_CUT_PARAM_T;

typedef struct {
    unsigned short nAutoSwitchEnable;    /* 0: disable 1: enable */
    ISP_IR_CUT_PARAM_T tIrCutParam[ADAPTIVE_IR_CUT_MODE_NUM];
} ADAPTIVE_ISP_IR_CUT_PARAM_T;

/*
* POST SATURATION
* follow ae gain
* need calc real saturation
*/

typedef struct {
    unsigned short nSaturationCoeff;
} _POST_SATURATION_CTL_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;    /* 0: disable 1: enable */
    _POST_SATURATION_CTL_PARAM_T tPostSaturationCtlParam[ADAPTIVE_GAIN_ROUTE_STEPS];
} ADAPTIVE_ISP_POST_SATURATION_PARAM_T;

/*
* COLOR BLACK WHITE MODE
* follow ae gain
*/

typedef struct {
    unsigned short nSaturation;
} _COLOR_GREY_CTL_PARAM;

typedef struct {
    int nExposureTime;
    int nGain;
    _COLOR_GREY_CTL_PARAM tColorGreyCsmCtlParam;
} ISP_COLOR_GREY_SWITCH_PARAM_T;

typedef struct {
    unsigned short nAutoSwitchEnable;    /* 0: disable 1: saturation convert mode */
    ISP_COLOR_GREY_SWITCH_PARAM_T tColorGreySwitchParam[ADAPTIVE_COLOR_GREY_SWITCH_MODE_NUM];
} ADAPTIVE_ISP_COLOR_GREY_SWITCH_PARAM_T;

/*
* ADA
* follow ae TO_CPU_Y_AV(gain & et max ae lock)
*/

typedef struct {
    unsigned short nAdaHistMax;
    unsigned short nAdaTtlMax;
} _ADA_CTL_PARAM;

typedef struct {
    unsigned short nAeYEverage;
    _ADA_CTL_PARAM tAdaCtlParam;
} ISP_ADA_PARAM_T;

typedef struct {
    unsigned short nAdaptiveEnable;
    ISP_ADA_PARAM_T tAdaParam[ADAPTIVE_ADA_ROUTE_STEPS];
} ADAPTIVE_ISP_ADA_PARAM_T;

typedef struct {
    float nFps;
    ADAPTIVE_ISP_AE_PARAM_T tAeParam;
    ADAPTIVE_ISP_AE_GAIN_PARAM_T tAeGainParam;
    ADAPTIVE_ISP_BLC_PARAM_T tBlcParam;
    ADAPTIVE_ISP_LSC_PARAM_T tLscParam;
    ADAPTIVE_ISP_SHARPNESS_PARAM_T tSharpnessParam;
    ADAPTIVE_ISP_LTM_PARAM_T tLtm_param;
    ADAPTIVE_ISP_2D_DENOISE_PARAM_T tNr2dParam;
    ADAPTIVE_ISP_3D_DENOISE_PARAM_T tNr3dParam;
    ADAPTIVE_ISP_WDR_PARAM_T tWdrParam;
    ADAPTIVE_ISP_CCM_PARAM_T tCcmParam;
    ADAPTIVE_ISP_AWB_PARAM_T tAwbParam;
    ADAPTIVE_ISP_GAMMA_PARAM_T tGammaParam;
    ADAPTIVE_ISP_IR_CUT_PARAM_T tIrCutParam; // TBD
    ADAPTIVE_ISP_POST_SATURATION_PARAM_T tSaturationParam;
    ADAPTIVE_ISP_COLOR_GREY_SWITCH_PARAM_T tColorGreySwitchParam;
    ADAPTIVE_ISP_ADA_PARAM_T tAdaParam;
} ADAPTIVE_ISP_PIPELINE_PARAM_T;

typedef struct {
    int nAeEvApplyFlag; // will ctl follow ae model
    int nAwbStatApplyFlag; // will ctl follow awb model
    int nUpdateFlag; // will ctl all model
} _PARAM_APPLY_FLAG_T;

typedef struct {
    int nAeGainWeight0; // weight of left interval(need 256 == 1.0)
    int nAeGainWeight1; // weight of right interval
    int nAeEvWeight0; // exposure time * gain weight
    int nAeEvWeight1; // exposure time * gain weight
    int nAeGainRange0;  // range of left interval
    int nAeGainRange1; // range of right interval
    int nAeEvRange0;
    int nAeEvRange1;
    unsigned short nSaturationWeight;
    unsigned short nGammaCurveSel; // gamma curve select
    unsigned short nColorGreySel; // color2grey or grey2color
    unsigned short nCtSel; // color temperature select
    unsigned short nIrCutSwitchSel; // ir cut mode
    unsigned short nAdaSel; // ada param select
} ADAPTIVE_ISP_WEIGHT_PARAM_T;

typedef struct {
    _BLC_CTL_PARAM_T tBlcCtlParam;
    _LSC_CTL_PARAM_T tLscCtlParam;
    _SHARPNESS_CTL_PARAM_T tSharpnessCtlParam;
    _LTM_CTL_PARAM_T tLtmCtlParam;
    _2D_DENOISE_CTL_PARAM_T t2dNrCtlParam;
    _3D_DENOISE_CTL_PARAM_T t3dNrCtlParam;
    _WDR_CTL_PARAM_T tWdrCtlParam;
    _GAMMA_CTL_PARAM_T tGammaCtlParam;
    _CCM_CTL_PARAM_T tCcmCtlParam;
    _AE_CTL_PARAM_T tAeCtlParam;
    _AWB_CTL_PARAM_T tAwbCtlParam;
    _COLOR_GREY_CTL_PARAM tColorGreyCtlParam;
    _IR_CUT_CTL_PARAM tIrCutCtlParam;
    _ADA_CTL_PARAM tAdaCtlParam;
    _POST_SATURATION_CTL_PARAM_T tPostSatuartionCtlParam;
    ADAPTIVE_ISP_WEIGHT_PARAM_T isp_weight;
    _PARAM_APPLY_FLAG_T param_flag;
} ADAPTIVE_ISP_CALC_PARAM_T;

typedef struct {
    /* ae stat */
    int nAeExposureTime;
    int nAeGain;
    /* awb stat */
    unsigned short nAwbRgain;
    unsigned short nAwbBgain;

    /* reserved */
    int nAeReadyWr;
    int nAeYEverage;
    int nReserved[2];
} ADAPTIVE_ISP_3A_STAT_T;

typedef struct {
	// post
    unsigned short nBrightnessVal; // luma gain step: 0 - 255, default 128
	unsigned short nContrastVal; // contrast gain coeff step: 0 - 255, default 128
    // 2dnr
    unsigned short n2dnrWeightStep_f_rawk; // 0 - 5, max_adap_2dnr / (5 - 0)
    unsigned short n2dnrWeightStep_f_ek; // 0 - 5, max_adap_2dnr / (5 - 0)
    unsigned short n2dnrWeightStep_f_yk; // 0 - 5, max_adap_2dnr / (5 - 0)
    unsigned short n2dnrWeightStep_p_rawk; // 6 - 10, (255 - max_adap_2dnr + 1) / (10 - 6 + 1)
    unsigned short n2dnrWeightStep_p_ek; // 6 - 10, (255 - max_adap_2dnr + 1) / (10 - 6 + 1)
    unsigned short n2dnrWeightStep_p_yk; // 6 - 10, (255 - max_adap_2dnr + 1) / (10 - 6 + 1)
    // ir cut
    unsigned short nIrCutLevelDay2Night; // 2 - 20
    unsigned short nIrCutLevelNight2Day; // 0 - 18
} ADAPTIVE_ISP_EX_MODEL_VAL_T;

typedef struct {
    /* itc ttl v */
    int nItcTtlV;

    /* ae range */
    int nMaxExpLine;
    int nMinExpLine;
    int nMaxGain;
    int nMinGain;
    /* saturation */
    unsigned short nDefaultSaturation;
    /* ccm coeff */
    unsigned short nRwgt;
    unsigned short nGwgt;
    unsigned short nBwgt;
    /* ccm normalization */
    unsigned short nSaturationRatio; // Ratio = 100% * (n + 521) / 512, need calib for different sensor
    unsigned short nCcmNl[2][3];
    unsigned short reserved[1];
} ADAPTIVE_IMG_TIMING_CFG_T;

#endif