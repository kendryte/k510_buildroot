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

#ifndef __ADAPTIVE_PARAMS_SETTING_IMX219_F2K_H__
#define __ADAPTIVE_PARAMS_SETTING_IMX219_F2K_H__

#include "../canaan_isp_struct.h"

static ADAPTIVE_ISP_PIPELINE_PARAM_T adap_imx219_f2k =

{
    /* fps */
    30,
    {
    /* AE Parameters */

    // static ADAPTIVE_ISP_AE_PARAM_T ae_param = {
        /* nAdaptiveEnable */
        1,
        /* nAntiFlickerSelect */
        0, //0: disable 1: 50Hz 2: 60Hz
        /* tAeParam */
        {
            /* 0 */
            {
                /* nExposureTime */
                280, // 6000lux
                /* nExposureGain */
                512,
                /* ae ctl */
                {
                    /* nAeYTarget */
                    100,
                    /* nAeYTargetRange */
                    14,
                },
            },
            /* 1 */
            {
                /* nExposureTime */
                2630, // 2500lux
                /* nExposureGain */
                512,
                /* ae ctl */
                {
                    /* nAeYTarget */
                    100,
                    /* nAeYTargetRange */
                    14,
                },
            },
            /* 2 */
            {
                /* nExposureTime */
                12108, // 400lux
                /* nExposureGain */
                512,
                /* ae ctl */
                {
                    /* nAeYTarget */
                    90,
                    /* AE_YTarget_Range */
                    13,
                },
            },
            /* 3 */
            {
                /* nExposureTime */
                33333, // 100lux
                /* nExposureGain */
                1024,
                {
                    /* nAeYTarget */
                    80,
                    /* AE_YTarget_Range */
                    11,
                },
            },
            /* 4 */
            {
                /* nExposureTime */
                33333,
                /* nExposureGain */
                4095,
                {
                    /* nAeYTarget */
                    72,
                    /* AE_YTarget_Range */
                    10,
                },
            },
        },
    // };
    },

    /* AE gain */

    {
        {256, 768, 1024, 2048, 4095},
    },

    {
    /* BLC Parameters */

    // static ADAPTIVE_ISP_BLC_PARAM_T blc_param = {
        /* nAdaptiveEnable */
        1,
        /* blc param */
        {
            /* 0 */
            {240},
            /* 1 */
            {240},
            /* 2 */
            {224},
            /* 3 */
            {224},
            /* 4 */
            {224},
        },
    // };
    },

    {
    /* LSC Parameters */

    // static ADAPTIVE_ISP_LSC_PARAM_T lsc_param = {
        /* nAdaptiveEnable */
        1,
        /* lsc param */
        {
            /* 0 */
            {
                /* nLscRedRatio */
                10,
                /* nLscGreenRatio */
                6,
                /* nLscBlueRatio */
                6,
            },
            /* 1 */
            {
                /* nLscRedRatio */
                10,
                /* nLscGreenRatio */
                6,
                /* nLscBlueRatio */
                6,
            },
            /* 2 */
            {
                /* nLscRedRatio */
                10,
                /* nLscGreenRatio */
                6,
                /* nLscBlueRatio */
                6,
            },
            /* 3 */
            {
                /* nLscRedRatio */
                10,
                /* nLscGreenRatio */
                6,
                /* nLscBlueRatio */
                6,
            },
            /* 4 */
            {
                /* nLscRedRatio */
                10,
                /* nLscGreenRatio */
                6,
                /* nLscBlueRatio */
                6,
            },
        },
    // };
    },

    {
    /* SHARPNESS Parameters */

    // static ADAPTIVE_ISP_SHARPNESS_PARAM_T sharpness_param = {
        /* nAdaptiveEnable */
        1,
        /* sharpness param */
        {
            /* 0 */
            {
                /* nSharpnessCore */
                4,
                /* nSharpnessThres[2]; [0]: thres1 [1]: thres2 */
                {3840, 4095},
                /* nSharpnessGain */
                64,
            },
            /* 1 */
            {
                /* nSharpnessCore */
                4,
                /* nSharpnessThres[2]; [0]: thres1 [1]: thres2 */
                {3840, 4095},
                /* nSharpnessGain */
                64,
            },
            /* 2 */
            {
                /* nSharpnessCore */
                8,
                /* nSharpnessThres[2]; [0]: thres1 [1]: thres2 */
                {3840, 4095},
                /* nSharpnessGain */
                56,
            },
            /* 3 */
            {
                /* nSharpnessCore */
                8,
                /* nSharpnessThres[2]; [0]: thres1 [1]: thres2 */
                {3840, 4095},
                /* nSharpnessGain */
                48,
            },
            /* 4 */
            {
                /* nSharpnessCore */
                8,
                /* nSharpnessThres[2]; [0]: thres1 [1]: thres2 */
                {3840, 4095},
                /* nSharpnessGain */
                40,
            },
        },
    // };
    },

    {
    /* LTM Parameters */

    // static ADAPTIVE_ISP_LTM_PARAM_T ltm_param = {
        /* nAdaptiveEnable */
        1,
        {
            /* 0 */
            {
                /* nLtmGain */
                128,
                /* nLtmThres */
                128,
            },
            /* 1 */
            {
                /* nLtmGain */
                128,
                /* nLtmThres */
                128,
            },
            /* 2 */
            {
                /* nLtmGain */
                128,
                /* nLtmThres */
                128,
            },
            /* 3 */
            {
                /* nLtmGain */
                100,
                /* nLtmThres */
                128,
            },
            /* 4 */
            {
                /* nLtmGain */
                80,
                /* nLtmThres */
                128,
            },
        },
    // };
    },

    {
    /* 2D NR Parameters */

    // static ADAPTIVE_ISP_2D_DENOISE_PARAM_T nr2d_param = {
        /* nAdaptiveEnable */
        1,
        /* 2dnr */
        {
            /* 0 */
            {
                /* nRawDomainIntensity */
                16,
                /* n2dAdjacentPixIntensity */
                128,
                /* n2dEdgeIntensity */
                32,
                /* n2dLumaIntensity */
                32,
                /* n2dChromaIntensity */
                1,
            },
            /* 1 */
            {
                /* nRawDomainIntensity */
                16,
                /* n2dAdjacentPixIntensity */
                128,
                /* n2dEdgeIntensity */
                32,
                /* n2dLumaIntensit */
                32,
                /* n2dChromaIntensity */
                1,
            },
            /* 2 */
            {
                /* nRawDomainIntensity */
                16,
                /* n2dAdjacentPixIntensity */
                128,
                /* n2dEdgeIntensity */
                40,
                /* n2dLumaIntensit */
                48,
                /* n2dChromaIntensity */
                160,
            },
            /* 3 */
            {
                /* nRawDomainIntensity */
                16,
                /* n2dAdjacentPixIntensity */
                511,
                /* n2dEdgeIntensity */
                48,
                /* n2dLumaIntensit */
                64,
                /* n2dChromaIntensity */
                255,
            },
            /* 4 */
            {
                /* nRawDomainIntensity */
                16,
                /* n2dAdjacentPixIntensity */
                511,
                /* n2dEdgeIntensity */
                48,
                /* n2dLumaIntensit */
                64,
                /* n2dChromaIntensity */
                255,
            },
        },
    // };
    },

    {
    /* 3D NR Parameters */

    // static ADAPTIVE_ISP_3D_DENOISE_PARAM_T nr3d_param = {
        /* nAdaptiveEnable */
        1,
        /* 3dnr */
        {
            /* 0 */
            {
                /* nPre3dLumaThres */
                64,
                /* nPre3dLumaIntensity */
                64,
                /* nPre3dChromaIntensity */
                64,
                /* nMain3dMiddleFilterThres */
                128,
                /* nMain3dPrevFrameMidFilter */
                8,
                /* nMain3dCurFrameMidFilterThres */
                128,
                /* nMain3dLowPassFilterVal */
                60,
                /* nMain3dLumaThres */
                64,
                /* nMain3dMinimumVal */
                1,
                /* nMain3dLumaIntensity */
                128,
                /* nMain3dChromaIntensity */
                16,
                /* nPost3dEdgeThreshold */
                64,
                /* nPost3dLumaIntensity */
                64,
                /* nPost3dChromaIntensity */
                32,
            },

            /* 1 */
            {
                /* nPre3dLumaThres */
                64,
                /* nPre3dLumaIntensity */
                64,
                /* nPre3dChromaIntensity */
                64,
                /* nMain3dMiddleFilterThres */
                128,
                /* nMain3dPrevFrameMidFilter */
                8,
                /* nMain3dCurFrameMidFilterThres */
                128,
                /* nMain3dLowPassFilterVal */
                60,
                /* nMain3dLumaThres */
                64,
                /* nMain3dMinimumVal */
                0,
                /* nMain3dLumaIntensity */
                128,
                /* nMain3dChromaIntensity */
                16,
                /* nPost3dEdgeThreshold */
                64,
                /* nPost3dLumaIntensity */
                64,
                /* nPost3dChromaIntensity */
                32,
            },

            /* 2 */
            {
                /* nPre3dLumaThres */
                64,
                /* nPre3dLumaIntensity */
                64,
                /* nPre3dChromaIntensity */
                64,
                /* nMain3dMiddleFilterThres */
                128,
                /* nMain3dPrevFrameMidFilter */
                8,
                /* nMain3dCurFrameMidFilterThres */
                128,
                /* nMain3dLowPassFilterVal */
                60,
                /* nMain3dLumaThres */
                64,
                /* nMain3dMinimumVal */
                0,
                /* nMain3dLumaIntensity */
                128,
                /* nMain3dChromaIntensity */
                16,
                /* nPost3dEdgeThreshold */
                64,
                /* nPost3dLumaIntensity */
                64,
                /* nPost3dChromaIntensity */
                32,
            },

            /* 3 */
            {
                /* nPre3dLumaThres */
                64,
                /* nPre3dLumaIntensity */
                64,
                /* nPre3dChromaIntensity */
                64,
                /* nMain3dMiddleFilterThres */
                128,
                /* nMain3dPrevFrameMidFilter */
                8,
                /* nMain3dCurFrameMidFilterThres */
                128,
                /* nMain3dLowPassFilterVal */
                60,
                /* nMain3dLumaThres */
                64,
                /* nMain3dMinimumVal */
                0,
                /* nMain3dLumaIntensity */
                128,
                /* nMain3dChromaIntensity */
                16,
                /* nPost3dEdgeThreshold */
                64,
                /* nPost3dLumaIntensity */
                64,
                /* nPost3dChromaIntensity */
                32,
            },

            /* 4 */
            {
                /* nPre3dLumaThres */
                64,
                /* nPre3dLumaIntensity */
                64,
                /* nPre3dChromaIntensity */
                64,
                /* nMain3dMiddleFilterThres */
                128,
                /* nMain3dPrevFrameMidFilter */
                8,
                /* nMain3dCurFrameMidFilterThres */
                128,
                /* nMain3dLowPassFilterVal */
                60,
                /* nMain3dLumaThres */
                64,
                /* nMain3dMinimumVal */
                0,
                /* nMain3dLumaIntensity */
                128,
                /* nMain3dChromaIntensity */
                16,
                /* nPost3dEdgeThreshold */
                64,
                /* nPost3dLumaIntensity */
                64,
                /* nPost3dChromaIntensity */
                32,
            },
        },
    // };
    },

    {
    /* WDR Parameters */

    // static ADAPTIVE_ISP_WDR_PARAM_T wdr_param = {
        /* nAdaptiveEnable */
        0,
        /* wdr param */
        {
            /* 0 */
            {
                /* nLghtTh[2] */
                {384, 32},
                /* nFsTh */
                192,
                /* nFsK */
                {0, 0},
            },
            /* 0 */
            {
                /* nLghtTh[2] */
                {384, 32},
                /* nFsTh */
                192,
                /* nFsK */
                {0, 0},
            },
            /* 2 */
            {
                /* nLghtTh[2] */
                {384, 32},
                /* nFsTh */
                192,
                /* nFsK */
                {0, 0},
            },
            /* 3 */
            {
                /* nLghtTh[2] */
                {384, 32},
                /* nFsTh */
                192,
                /* nFsK */
                {0, 0},
            },
            /* 4 */
            {
                /* nLghtTh[2] */
                {384, 32},
                /* nFsTh */
                192,
                /* nFsK */
                {0, 0},
            },
        },
    // };
    },

    {
    /* CCM Parameters */

    // static ADAPTIVE_ISP_CCM_PARAM_T ccm_param = {
        /* nAdaptiveEnable */
        1,
        /* tCcmParam */
        {
            /* A */
            {
                /* nRGain */
                162,
                /* nBGain */
                449,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {311, 49, 6},
                        {62, 343, 26},
                        {16, 142, 414},
                    },
                },
            },
            /* U30 */
            {
                /* nRGain */
                156,
                /* nBGain */
                458,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {299, 39, 5},
                        {56, 336, 24},
                        {13, 126, 395},
                    },
                },
            },
            /* U35 */
            {
                /* nRGain */
                176,
                /* nBGain */
                402,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {287, 28, 3},
                        {50, 328, 22},
                        {9, 111, 376},
                    },
                },
            },
            /* TL84 */
            {
                /* nRGain */
                194,
                /* nBGain */
                360,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {259, 2, 1},
                        {37, 310, 17},
                        {1, 75, 332},
                    },
                },
            },
            /* D50 */
            {
                /* nRGain */
                234,
                /* nBGain */
                299,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {277, 19, 3},
                        {45, 322, 20},
                        {6, 98, 360},
                    },
                },
            },
            /* D65 */
            {
                /* nRGain */
                257,
                /* nBGain */
                269,
                /* tCcmCtlParam */
                {
                    /* nCtCcm[3][3] */
                    {
                        {259, 2, 1},
                        {37, 310, 17},
                        {1, 75, 332},
                    },
                },
            },
        },
    // };
    },

    {
    /* AWB */

    // static ADAPTIVE_ISP_AWB_PARAM_T awb_param = {
        /* nAdaptiveEnable */
        1,
        /* awb param */
        {
            /* 0 */
            {
            /* nRGain[2]; [0]: Min [1]: Max */
            {194, 247},
            /* nBGain[2]; [0]: Min [1]: Max */
            {275, 360},
            },
            /* 1 */
            {
            /* nRGain[2]; [0]: Min [1]: Max */
            {176, 257},
            /* nBGain[2]; [0]: Min [1]: Max */
            {269, 402},
            },
            /* 2 */
            {
            /* nRGain[2]; [0]: Min [1]: Max */
            {156, 257},
            /* nBGain[2]; [0]: Min [1]: Max */
            {269, 458},
            },
            /* 3 */
            {
            /* nRGain[2]; [0]: Min [1]: Max */
            {176, 257},
            /* nBGain[2]; [0]: Min [1]: Max */
            {269, 402},
            },
            /* 4 */
            {
            /* nRGain[2]; [0]: Min [1]: Max */
            {176, 257},
            /* nBGain[2]; [0]: Min [1]: Max */
            {269, 402},
            },
        },
    // };
    },

    {

    /* GAMMA Parameters */

    // static ADAPTIVE_ISP_GAMMA_PARAM_T gamma_param = {
        /* nAdaptiveEnable */
        1, // if 1 affect ae stablization
        /* tGammaParam */
        {
            /* Day */
            {
                /* nEtGamma */
                33333,
                /* nGainGamma */
                512,
                /* tGammaCtlParam */
                {
                    /* nGammaCurve */
                    {
                        0x000, 0xC05, 0x80B, 0x411, 0xC16, 0x01C, 0x421, 0x426, 0x02B, 0x82F, 0xC33, 0xC37, 0x83B, 0x03F, 0x442, 0x445,
                        0x048, 0xC4A, 0x44D, 0xC4F, 0x052, 0x454, 0x856, 0x858, 0x85A, 0x85C, 0x85E, 0x860, 0x862, 0x864, 0x466, 0x068,
                        0xC69, 0x86B, 0x46D, 0x06F, 0xC70, 0x872, 0x074, 0x875, 0x077, 0x878, 0x07A, 0x87B, 0x07D, 0x87E, 0xC7F, 0x081,
                        0x482, 0x883, 0xC84, 0x086, 0x487, 0x888, 0xC89, 0x08B, 0x48C, 0x88D, 0x88E, 0x88F, 0x890, 0x891, 0x892, 0x893,
                        0x894, 0x895, 0x896, 0x897, 0x898, 0x899, 0x89A, 0x89B, 0x89C, 0x89D, 0x89E, 0x49F, 0x0A0, 0xCA0, 0x8A1, 0x4A2,
                        0x0A3, 0xCA3, 0x8A4, 0x4A5, 0x0A6, 0xCA6, 0x8A7, 0x4A8, 0x0A9, 0xCA9, 0x8AA, 0x4AB, 0x0AC, 0xCAC, 0x8AD, 0x4AE,
                        0x0AF, 0xCAF, 0x8B0, 0x4B1, 0x0B2, 0xCB2, 0x8B3, 0x4B4, 0x0B5, 0xCB5, 0x4B6, 0xCB6, 0x4B7, 0xCB7, 0x4B8, 0xCB8,
                        0x4B9, 0xCB9, 0x4BA, 0xCBA, 0x4BB, 0xCBB, 0x4BC, 0xCBC, 0x4BD, 0xCBD, 0x4BE, 0xCBE, 0x4BF, 0xCBF, 0x4C0, 0xCC0,
                        0x4C1, 0xCC1, 0x4C2, 0xCC2, 0x4C3, 0xCC3, 0x4C4, 0xCC4, 0x4C5, 0xCC5, 0x4C6, 0xCC6, 0x4C7, 0xCC7, 0x4C8, 0xCC8,
                        0x4C9, 0xCC9, 0x4CA, 0xCCA, 0x4CB, 0xCCB, 0x4CC, 0xCCC, 0x4CD, 0xCCD, 0x4CE, 0xCCE, 0x4CF, 0xCCF, 0x4D0, 0xCD0,
                        0x4D1, 0xCD1, 0x4D2, 0xCD2, 0x4D3, 0xCD3, 0x4D4, 0xCD4, 0x4D5, 0xCD5, 0x4D6, 0xCD6, 0x4D7, 0xCD7, 0x4D8, 0xCD8,
                        0x4D9, 0xCD9, 0x4DA, 0xCDA, 0x4DB, 0xCDB, 0x4DC, 0xCDC, 0x4DD, 0xCDD, 0x4DE, 0xCDE, 0x4DF, 0xCDF, 0x4E0, 0xCE0,
                        0x4E1, 0xCE1, 0x4E2, 0xCE2, 0x4E3, 0xCE3, 0x4E4, 0xCE4, 0x4E5, 0xCE5, 0x4E6, 0xCE6, 0x4E7, 0xCE7, 0x4E8, 0xCE8,
                        0x4E9, 0xCE9, 0x4EA, 0xCEA, 0x4EB, 0xCEB, 0x4EC, 0xCEC, 0x4ED, 0xCED, 0x4EE, 0xCEE, 0x4EF, 0xCEF, 0x4F0, 0xCF0,
                        0x4F1, 0xCF1, 0x4F2, 0xCF2, 0x4F3, 0xCF3, 0x4F4, 0xCF4, 0x4F5, 0xCF5, 0x4F6, 0xCF6, 0x4F7, 0xCF7, 0x4F8, 0xCF8,
                        0x4F9, 0xCF9, 0x4FA, 0xCFA, 0x4FB, 0xCFB, 0x4FC, 0xCFC, 0x4FD, 0xCFD, 0x4FE, 0xCFE, 0x0FF, 0x4FF, 0x8FF, 0xCFF,
                    },
                },
            },
            /* Night */
            {
                /* nEtGamma */
                33333,
                /* nGainGamma */
                3072,
                /* tGammaCtlParam */
                {
                    /* nGammaCurve */
                    {
                        0x001, 0x814, 0x41C, 0x022, 0xC26, 0xC2A, 0x82E, 0xC31, 0x035, 0xC37, 0x83A, 0x43D, 0xC3F, 0x042, 0x444, 0x846,
                        0x848, 0x84A, 0x84C, 0x84E, 0x450, 0x052, 0xC53, 0x855, 0x457, 0x059, 0x85A, 0x05C, 0x85D, 0x05F, 0x860, 0x062,
                        0x863, 0x065, 0x866, 0xC67, 0x069, 0x46A, 0x86B, 0xC6C, 0x06E, 0x46F, 0x870, 0xC71, 0x073, 0x474, 0x875, 0xC76,
                        0x078, 0x479, 0x47A, 0x47B, 0x47C, 0x47D, 0x47E, 0x47F, 0x480, 0x481, 0x482, 0x483, 0x484, 0x485, 0x486, 0x487,
                        0x488, 0x489, 0x48A, 0x48B, 0x48C, 0x48D, 0x48E, 0x48F, 0x490, 0x491, 0x492, 0x493, 0x494, 0x495, 0x496, 0x497,
                        0x098, 0xC98, 0x899, 0x49A, 0x09B, 0xC9B, 0x89C, 0x49D, 0x09E, 0xC9E, 0x89F, 0x4A0, 0x0A1, 0xCA1, 0x8A2, 0x4A3,
                        0x0A4, 0xCA4, 0x8A5, 0x4A6, 0x0A7, 0xCA7, 0x8A8, 0x4A9, 0x0AA, 0xCAA, 0x8AB, 0x4AC, 0x0AD, 0xCAD, 0x8AE, 0x4AF,
                        0x0B0, 0xCB0, 0x8B1, 0x4B2, 0x0B3, 0xCB3, 0x8B4, 0x4B5, 0x0B6, 0xCB6, 0x8B7, 0x4B8, 0x0B9, 0xCB9, 0x8BA, 0x4BB,
                        0x0BC, 0xCBC, 0x8BD, 0x4BE, 0x0BF, 0xCBF, 0x8C0, 0x4C1, 0x0C2, 0xCC2, 0x8C3, 0x4C4, 0x0C5, 0xCC5, 0x8C6, 0x4C7,
                        0x0C8, 0xCC8, 0x8C9, 0x4CA, 0x0CB, 0x8CB, 0x0CC, 0x8CC, 0x0CD, 0x8CD, 0x0CE, 0x8CE, 0x0CF, 0x8CF, 0x0D0, 0x8D0,
                        0x0D1, 0x8D1, 0x0D2, 0x8D2, 0x0D3, 0x8D3, 0x0D4, 0x8D4, 0x0D5, 0x8D5, 0x0D6, 0x8D6, 0x0D7, 0x8D7, 0x0D8, 0x8D8,
                        0x0D9, 0x8D9, 0x0DA, 0x8DA, 0x0DB, 0x8DB, 0x0DC, 0x8DC, 0x0DD, 0x8DD, 0x0DE, 0x8DE, 0x0DF, 0x8DF, 0x0E0, 0x8E0,
                        0x0E1, 0x8E1, 0x0E2, 0x8E2, 0x0E3, 0x8E3, 0x0E4, 0x8E4, 0x0E5, 0x8E5, 0x0E6, 0x8E6, 0x0E7, 0x8E7, 0x0E8, 0x8E8,
                        0x0E9, 0x8E9, 0x0EA, 0x8EA, 0x0EB, 0x8EB, 0x0EC, 0x8EC, 0x0ED, 0x8ED, 0x0EE, 0x8EE, 0x0EF, 0x8EF, 0x0F0, 0x8F0,
                        0x0F1, 0x8F1, 0x0F2, 0x8F2, 0x0F3, 0x8F3, 0x0F4, 0x8F4, 0x0F5, 0x8F5, 0x0F6, 0x8F6, 0x0F7, 0x8F7, 0x0F8, 0x8F8,
                        0x0F9, 0x8F9, 0x0FA, 0x8FA, 0x0FB, 0x8FB, 0x0FC, 0x8FC, 0x0FD, 0x8FD, 0x0FE, 0x8FE, 0x0FF, 0x4FF, 0x8FF, 0xCFF,
                    },
                },
            },
        },
    // };
    },

    {
    // static ADAPTIVE_ISP_IR_CUT_PARAM_T ir_cut_param = {
        /* nAutoSwitchEnable */
        1,
        /* tIrCutParam */
        {
            /* Day2Night */
            {
                /* nExposureTime */
                30000,
                /* nGain */
                2048,
                /* tIrCutCtlParam */
                {
                    /* nHoldTime */
                    120,
                    /* nIrCutMode */
                    1,
                },
            },
            /* Night2Day */
            {
                /* nExposureTime */
                20000,
                /* nGain */
                512,
                /* tIrCutCtlParam */
                {
                    /* nHoldTime */
                    120,
                    /* nIrCutMode */
                    0,
                },
            },
        },
    // };
    },

    {
    /* POST SATURATION Parameters */

    // static ADAPTIVE_ISP_POST_SATURATION_PARAM_T saturation_param = {
        /* nAdaptiveEnable */
        1,
        /* post saturation param */
        {
            /* 0 */
            {100},
            /* 1 */
            {100},
            /* 2 */
            {100},
            /* 3 */
            {100},
            /* 4 */
            {90},
        },
    // };
    },

    {
    /* Color Black White Mode Parameters */

    // static ADAPTIVE_ISP_COLOR_GREY_SWI2CH_PARAM_T color_grey_switch_param = {
        /* nAutoSwitchEnable  */
        0, // use csm mode
        /* tColorGreySwitchParam */
        {
            /* Color2BW */
            {
                /* nExposureTime */
                33333,
                /* nGain */
                4095,
                /* tColorGreyCsmCtlParam*/
                {0},
            },
            /* BW2Color */
            {
                /* nExposureTime */
                33333,
                /* nGain */
                1536,
                /* tColorGreyCsmCtlParam*/
                {255},
            },
        },
    // };
    },

    {
    /* ADA Parameters */

    // static ADAPTIVE_ISP_ADA_PARAM_T ada_param = {
        /* nAdaptiveEnable */
        1, // 1: enable, 0: disable
        /* tAdaParam */
        {
            /* 0 */
            {
                /* nAeYEverage */
                60,
                /* tAdaCtlParam */
                {
                    /* nAdaHistMax */
                    128,
                    /* nAdaTtlMax */
                    255,
                },
            },
            /* 1 */
            {
                /* nAeYEverage */
                50,
                /* tAdaCtlParam */
                {
                    /* nAdaHistMax */
                    128,
                    /* nAdaTtlMax */
                    200,
                },
            },
            /* 2 */
            {
                /* nAeYEverage */
                40,
                /* tAdaCtlParam */
                {
                    /* nAdaHistMax */
                    128,
                    /* nAdaTtlMax */
                    128,
                },
            },
            /* 3 */
            {
                /* nAeYEverage */
                30,
                /* tAdaCtlParam */
                {
                    /* nAdaHistMax */
                    128,
                    /* nAdaTtlMax */
                    100,
                },
            },
            /* 4 */
            {
                /* nAeYEverage */
                20,
                /* tAdaCtlParam */
                {
                    /* nAdaHistMax */
                    128,
                    /* nAdaTtlMax */
                    90,
                },
            },
        },
    // };
    },
};

#endif
