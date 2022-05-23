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
#include "video/isp_com.h"
//#include "video/isp/isp.h"
#include "video/isp/core/isp_core_drv.h"
#include "video/isp/core/isp_core_reg.h"

extern  unsigned int  *reg_isp_2k_core_base;
#define ISP_2K_DRV_CORE_REG_CTX(pstCtx)	 pstCtx = (S_ISP_CORE_REGS_TYPE *)(reg_isp_2k_core_base)

/*
*  Image Timing Control 
*/
static int ISP_DRV_CORE_SetItcCtl(ISP_CORE_ITC_CTL_S *pstItcCtl)
{
	ISP_CHECK_POINTER(pstItcCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);
	
	U_ISP_CORE_ITC_CTL stData;
	stData.u32 = 0;
	stData.bits.hsync_pol = pstItcCtl->hsync_pol;
	stData.bits.vsync_pol = pstItcCtl->vsync_pol;
	stData.bits.hsync_input_timing = pstItcCtl->hsync_input_timing;
	stData.bits.vsync_input_timing = pstItcCtl->vsync_input_timing;
	stData.bits.mirror_ctl = pstItcCtl->mirror_ctl;
	stData.bits.video_format_ctl = pstItcCtl->video_format_ctl;
	
	ISP_CORE_DRV_SET_CoreItcCtl(apstIspCoreReg, stData.u32);
	return 0;
}
/*
*input image size
*/
static int ISP_DRV_CORE_SetImageAttr(ISP_CORE_IMAGE_ATTR_S *pstImgAttr)
{
	ISP_CHECK_POINTER(pstImgAttr);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_IMAGE_HEIGHT stHeight;
	stHeight.u32 = 0;
	stHeight.bits.image_height = pstImgAttr->image_height;
	ISP_CORE_DRV_SET_CoreImageHeight(apstIspCoreReg, stHeight.u32);

	U_ISP_CORE_IMAGE_WIDTH stWidth;
	stWidth.u32 = 0;
	stWidth.bits.image_width = pstImgAttr->image_width;
	ISP_CORE_DRV_SET_CoreImageWidth(apstIspCoreReg, stWidth.u32);

	U_ISP_CORE_IMAGE_V_START stVStart;
	stVStart.u32 = 0;
	stVStart.bits.image_v_start = pstImgAttr->image_v_start;
	ISP_CORE_DRV_SET_CoreImageVStart(apstIspCoreReg, stVStart.u32);

	U_ISP_CORE_IMAGE_H_START stHStart;
	stHStart.u32 = 0;
	stHStart.bits.image_h_start = pstImgAttr->image_h_start;
	ISP_CORE_DRV_SET_CoreImageHStart(apstIspCoreReg, stHStart.u32);

	U_ISP_CORE_IMAGE_ACTIVE_WIDTH stActWidth;
	stActWidth.u32 = 0;
	stActWidth.bits.image_active_width = pstImgAttr->image_active_width;
	ISP_CORE_DRV_SET_CoreImageActiveWidth(apstIspCoreReg, stActWidth.u32);

	U_ISP_CORE_IMAGE_ACTIVE_HEIGHT stActHeight;
	stActHeight.u32 = 0;
	stActHeight.bits.image_active_height = pstImgAttr->image_active_height;
	ISP_CORE_DRV_SET_CoreImageActiveHeight(apstIspCoreReg, stActHeight.u32);
	return 0;
}
/*
*Test Pattern Control
*/
static int ISP_DRV_CORE_SetTestCtl(ISP_CORE_TEST_CTL_S *pstTestCtl)
{
	ISP_CHECK_POINTER(pstTestCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);
	
	U_ISP_CORE_TEST_CTL stData;
	stData.u32 = 0;
	stData.bits.bayer_mode_sel = pstTestCtl->bayer_mode_sel;
	stData.bits.motion_mode_sel = pstTestCtl->motion_mode_sel;
	stData.bits.test_pattern_sel = pstTestCtl->test_pattern_sel;
	stData.bits.test_pattern_en = pstTestCtl->test_pattern_en;
	stData.bits.wdr_l_mul_data = pstTestCtl->wdr_l_mul_data;
	stData.bits.wdr_m_mul_data = pstTestCtl->wdr_m_mul_data;
	stData.bits.wdr_s_mul_data = pstTestCtl->wdr_s_mul_data;
	ISP_CORE_DRV_SET_CoreTestCtl(apstIspCoreReg, stData.u32);
	return 0;
}
/*
*Black Level Correction
*/
static int ISP_DRV_CORE_SetBlcCtl(ISP_CORE_BLC_CTL_S *pstBlcCtl)
{
	ISP_CHECK_POINTER(pstBlcCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);
	
	U_ISP_CORE_BLC_CTL stBlcCtl;
	stBlcCtl.u32 = 0;
	stBlcCtl.bits.blc_en = pstBlcCtl->blc_en;
	ISP_CORE_DRV_SET_CoreBlcCtl(apstIspCoreReg, stBlcCtl.u32);

	U_ISP_CORE_BLC_OFFSET stBlcOffset;
	stBlcOffset.u32 = 0;
	stBlcOffset.bits.blc_offset = pstBlcCtl->blc_offset;
	ISP_CORE_DRV_SET_CoreBlcOffset(apstIspCoreReg, stBlcOffset.u32);

	U_ISP_CORE_BLC_RATIO stBlcRatio;
	stBlcRatio.u32 = 0;
	stBlcRatio.bits.blc_ratio = pstBlcCtl->blc_ratio;
	ISP_CORE_DRV_SET_CoreBlcRatio(apstIspCoreReg, stBlcRatio.u32);
	return 0;
}
/*
* Lens Shading Correction
*/
static int ISP_DRV_CORE_SetLscCtl(ISP_CORE_LSC_CTL_S *pstLscCtl)
{
	ISP_CHECK_POINTER(pstLscCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_LSC_CTL stlscCtl;
	stlscCtl.u32 = 0;
	stlscCtl.bits.lsc_en = pstLscCtl->lsc_en;
	ISP_CORE_DRV_SET_CoreLscCtl(apstIspCoreReg, stlscCtl.u32 );

	U_ISP_CORE_LSC_H_CENTER stHCenter;
	stHCenter.u32 = 0;
	stHCenter.bits.lsc_h_center = pstLscCtl->lsc_h_center;
	ISP_CORE_DRV_SET_CoreLscHCenter(apstIspCoreReg, stHCenter.u32 );

	U_ISP_CORE_LSC_V_CENTER stVCenter;
	stVCenter.u32 = 0;
	stVCenter.bits.lsc_v_center = pstLscCtl->lsc_v_center;
	ISP_CORE_DRV_SET_CoreLscVCenter(apstIspCoreReg, stVCenter.u32);

	U_ISP_CORE_LSC_R_RATIO stRRatio;
	stRRatio.u32 = 0;
	stRRatio.bits.lsc_red_ratio = pstLscCtl->lsc_red_ratio;
	ISP_CORE_DRV_SET_CoreLscRRatio(apstIspCoreReg, stRRatio.u32);

	U_ISP_CORE_LSC_G_RATIO stGRatio;
	stGRatio.u32 = 0;
	stGRatio.bits.lsc_green_ratio = pstLscCtl->lsc_green_ratio;
	ISP_CORE_DRV_SET_CoreLscGRatio(apstIspCoreReg, stGRatio.u32);

	U_ISP_CORE_LSC_B_RATIO stBRatio;
	stBRatio.u32 = 0;
	stBRatio.bits.lsc_blue_ratio = pstLscCtl->lsc_blue_ratio;
	ISP_CORE_DRV_SET_CoreLscBRatio(apstIspCoreReg, stBRatio.u32);

	U_ISP_CORE_LSC_IR_RATIO stIrRatio;
	stIrRatio.u32 = 0;
	stIrRatio.bits.lsc_ir_ratio = pstLscCtl->lsc_ir_ratio;
	ISP_CORE_DRV_SET_CoreLscIrRatio(apstIspCoreReg, stIrRatio.u32);

	return 0;
}
/*
*AUTO Exposure/Gain 
*/
static int ISP_DRV_CORE_SetAeCtl(ISP_CORE_AE_CTL_S *pstAeCtl)
{
	ISP_CHECK_POINTER(pstAeCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_AE_CTL stAeCtl;
	stAeCtl.u32 = 0;
	stAeCtl.bits.ae_as_en = pstAeCtl->ae_as_en;
	stAeCtl.bits.ae_ag_en = pstAeCtl->ae_ag_en;
	stAeCtl.bits.ae_airis_en = pstAeCtl->ae_airis_en;
	stAeCtl.bits.ae_enter_ls_sel = pstAeCtl->ae_enter_ls_sel;
	stAeCtl.bits.ae_exit_ls_sel = pstAeCtl->ae_exit_ls_sel;
	stAeCtl.bits.ae_win_mode_sel = pstAeCtl->ae_win_mode_sel;
	stAeCtl.bits.ae_back_light_mode_sel = pstAeCtl->ae_back_light_mode_sel;
	stAeCtl.bits.ae_day_change_en = pstAeCtl->ae_day_change_en;
	stAeCtl.bits.ae_day_change_sel = pstAeCtl->ae_day_change_sel;
	ISP_CORE_DRV_SET_CoreAeCtl(apstIspCoreReg, stAeCtl.u32);

	U_ISP_CORE_AE_WIN_H_START stHStart;
	stHStart.u32 = 0;
	stHStart.bits.ae_win_h_start = pstAeCtl->ae_win_h_start;
	ISP_CORE_DRV_SET_CoreAeWinHStart(apstIspCoreReg, stHStart.u32);

	U_ISP_CORE_AE_WIN_V_START stVStart;
	stVStart.u32 = 0;
	stVStart.bits.ae_win_v_start = pstAeCtl->ae_win_v_start;
	ISP_CORE_DRV_SET_CoreAeWinVStart(apstIspCoreReg, stVStart.u32);

	U_ISP_CORE_AE_WIN_H_END stHEnd;
	stHEnd.u32 = 0;
	stHEnd.bits.ae_win_h_end = pstAeCtl->ae_win_h_end;
	ISP_CORE_DRV_SET_CoreAeWinHEnd(apstIspCoreReg, stHEnd.u32);

	U_ISP_CORE_AE_WIN_V_END stVEnd;
	stVEnd.u32 = 0;
	stVEnd.bits.ae_win_v_end = pstAeCtl->ae_win_v_end;
	ISP_CORE_DRV_SET_CoreAeWinVEnd(apstIspCoreReg, stVEnd.u32);

	U_ISP_CORE_AE_TAR_BR stTarBr;
	stTarBr.u32 = 0;
	stTarBr.bits.ae_tar_bright = pstAeCtl->ae_tar_bright;
	ISP_CORE_DRV_SET_CoreAeTarBr(apstIspCoreReg, stTarBr.u32);

	U_ISP_CORE_AE_TAR_BR_RANGE stTarBrRange;
	stTarBrRange.u32 = 0;
	stTarBrRange.bits.ae_tar_bright_range = pstAeCtl->ae_tar_bright_range;
	ISP_CORE_DRV_SET_CoreAeTarBrRange(apstIspCoreReg, stTarBrRange.u32);

	U_ISP_CORE_AE_L_EX_TIME stLExTime;
	stLExTime.u32 = 0;
	stLExTime.bits.ae_l_ex_time = pstAeCtl->ae_l_ex_time;
	ISP_CORE_DRV_SET_CoreAeLExTime(apstIspCoreReg, stLExTime.u32);

	U_ISP_CORE_AE_M_EX_TIME stMExTime;
	stMExTime.u32 = 0;
	stMExTime.bits.ae_m_ex_time = pstAeCtl->ae_m_ex_time;
	ISP_CORE_DRV_SET_CoreAeMExTime(apstIspCoreReg, stMExTime.u32);

	U_ISP_CORE_AE_S_EX_TIME stSExTime;
	stSExTime.u32 = 0;
	stSExTime.bits.ae_s_ex_time = pstAeCtl->ae_s_ex_time;
	ISP_CORE_DRV_SET_CoreAeSExTime(apstIspCoreReg, stSExTime.u32);

	U_ISP_CORE_AE_AGC stAgc;
	stAgc.u32 = 0;
	stAgc.bits.ae_agc = pstAeCtl->ae_agc;
	ISP_CORE_DRV_SET_CoreAeAgc(apstIspCoreReg, stAgc.u32);

	U_ISP_CORE_AE_ADJUST_CTL stAdCtl;
	stAdCtl.u32 = 0;
	stAdCtl.bits.ae_ad_shuttle_freq = pstAeCtl->ae_ad_shuttle_freq;
	stAdCtl.bits.ae_ad_gain_freq = pstAeCtl->ae_ad_gain_freq;
	ISP_CORE_DRV_SET_CoreAeAdjustCtl(apstIspCoreReg, stAdCtl.u32);

	U_ISP_CORE_AE_ADJUST_STEP_MAX stAdStepMax;
	stAdStepMax.u32 = 0;
	stAdStepMax.bits.ae_adjust_step_max = pstAeCtl->ae_adjust_step_max;
	ISP_CORE_DRV_SET_CoreAeAdjustStepMax(apstIspCoreReg, stAdStepMax.u32);

    U_ISP_CORE_AE_EX_VALUE_MAX stExValueMax;
	stExValueMax.u32 = 0;
	stExValueMax.bits.ae_ex_value_max = pstAeCtl->ae_ex_value_max;
	ISP_CORE_DRV_SET_CoreAeExValueMax(apstIspCoreReg, stExValueMax.u32);

	U_ISP_CORE_AE_EX_VALUE_MID stExValueMid;
	stExValueMid.u32 = 0;
	stExValueMid.bits.ae_ex_value_mid = pstAeCtl->ae_ex_value_mid;
	ISP_CORE_DRV_SET_CoreAeExValueMid(apstIspCoreReg, stExValueMid.u32);

	U_ISP_CORE_AE_EX_VALUE_MIN stExValueMin;
	stExValueMin.u32 = 0;
	stExValueMin.bits.ae_ex_value_min = pstAeCtl->ae_ex_value_min;
	ISP_CORE_DRV_SET_CoreAeExValueMin(apstIspCoreReg, stExValueMin.u32);

    U_ISP_CORE_AE_GAIN_MAX stGainMax;
	stGainMax.u32 = 0;
	stGainMax.bits.ae_gain_value_max = pstAeCtl->ae_gain_value_max;
	ISP_CORE_DRV_SET_CoreAeGainMax(apstIspCoreReg, stGainMax.u32);

	U_ISP_CORE_AE_GAIN_MID stGainMid;
	stGainMid.u32 = 0;
	stGainMid.bits.ae_gain_value_mid = pstAeCtl->ae_gain_value_mid;
	ISP_CORE_DRV_SET_CoreAeGainMid(apstIspCoreReg, stGainMid.u32);

	U_ISP_CORE_AE_GAIN_MIN stGainMin;
	stGainMin.u32 = 0;
	stGainMin.bits.ae_gain_value_min = pstAeCtl->ae_gain_value_min;
	ISP_CORE_DRV_SET_CoreAeGainMin(apstIspCoreReg, stGainMin.u32);

	U_ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX stDnAdStepMax;
	stDnAdStepMax.u32 = 0;
	stDnAdStepMax.bits.ae_dn_switch_ad_step_max = pstAeCtl->ae_dn_switch_ad_step_max;
	ISP_CORE_DRV_SET_CoreAeDnSwitchAdjustStepMax(apstIspCoreReg, stDnAdStepMax.u32);

	U_ISP_CORE_AE_DN_SWITCH_WAIT_TIME stDnWaitTime;
	stDnWaitTime.u32 = 0;
	stDnWaitTime.bits.ae_dn_switch_wait_time = pstAeCtl->ae_dn_switch_wait_time;
	ISP_CORE_DRV_SET_CoreAeDnSwitchWaitTime(apstIspCoreReg, stDnWaitTime.u32);

	U_ISP_CORE_APE_DIFF_MAX stApeDiffMax;
	stApeDiffMax.u32 = 0;
	stApeDiffMax.bits.ape_max_diff = pstAeCtl->ape_max_diff;
	ISP_CORE_DRV_SET_CoreApeDiffMax(apstIspCoreReg, stApeDiffMax.u32);

	U_ISP_CORE_APE_DRV_SIGNAL_MAX stDriveSignalMax;
	stDriveSignalMax.u32 = 0;
	stDriveSignalMax.bits.ape_drv_signal_max = pstAeCtl->ape_drv_signal_max;
	ISP_CORE_DRV_SET_CoreApeDrvSignalMax(apstIspCoreReg, stDriveSignalMax.u32);

	U_ISP_CORE_APE_COEFF_DIS stApeCoeffDis;
	stApeCoeffDis.u32 = 0;
	stApeCoeffDis.bits.ape_coeff_distance = pstAeCtl->ape_coeff_distance;
	ISP_CORE_DRV_SET_CoreApeCoeffDis(apstIspCoreReg, stApeCoeffDis.u32);

	U_ISP_CORE_APE_COEFF_SPEED stApeCoeffSpeed;
	stApeCoeffSpeed.u32 = 0;
	stApeCoeffSpeed.bits.ape_coeff_speed = pstAeCtl->ape_coeff_speed;
	ISP_CORE_DRV_SET_CoreApeCoeffSpeed(apstIspCoreReg, stApeCoeffSpeed.u32);

	U_ISP_CORE_APE_COEFF_ACCE stApeCoeffAcce;
	stApeCoeffAcce.u32 = 0;
	stApeCoeffAcce.bits.ape_coeff_acceleration = pstAeCtl->ape_coeff_acceleration;
	ISP_CORE_DRV_SET_CoreApeCoeffAcce(apstIspCoreReg, stApeCoeffAcce.u32);

	U_ISP_CORE_APE_DRV_MANUAL_VALUE stApeDriManValue;
	stApeDriManValue.u32 = 0;
	stApeDriManValue.bits.ape_drv_manual_value = pstAeCtl->ape_drv_manual_value;
	ISP_CORE_DRV_SET_CoreApeDrvManualValue(apstIspCoreReg, stApeDriManValue.u32);

	U_ISP_CORE_APE_DAMP_MANUAL_VALUE stDampManValue;
	stDampManValue.u32 = 0;
	stDampManValue.bits.ape_damp_manual_value = pstAeCtl->ape_damp_manual_value;
	ISP_CORE_DRV_SET_CoreApeDampManualValue(apstIspCoreReg, stDampManValue.u32);	
	return 0;
}
/**
 * @brief 
 * 
 * @return int 
 */
int ISP_DRV_CORE_GetAeLongCurEx(void)
{
	int data;
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	data = ISP_CORE_DRV_GET_CoreAeLongCurEx(apstIspCoreReg);

	return data;
}
/**
 * @brief 
 * 
 * @return int 
 */
int ISP_DRV_CORE_GetAeCurDigitalGain(void)
{
	int data;
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	data = ISP_CORE_DRV_GET_CoreAeCurDigitalGain(apstIspCoreReg);

	return data;
}
/**
 * @brief 
 * 
 * @param pAeSts 
 * @return int 
 */
int ISP_DRV_CORE_GetAeSts(ISP_CORE_AE_STS_S *pAeSts)
{
	ISP_CHECK_POINTER(pAeSts);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

  	U_ISP_CORE_AE_VALUE_READY          gtAeValueReady;
  	gtAeValueReady.u32 = ISP_CORE_DRV_GET_CoreAeValueReady(apstIspCoreReg);
  	pAeSts->ae_value_ready = gtAeValueReady.u32;

  	U_ISP_CORE_AE_LONG_CUR_EX          gtAeLongCurEX;
  	gtAeLongCurEX.u32 = ISP_CORE_DRV_GET_CoreAeLongCurEx(apstIspCoreReg);
  	pAeSts->ae_long_cur_ex = gtAeLongCurEX.u32;

  	U_ISP_CORE_AE_MID_CUR_EX           gtAeMidCurEX;
  	gtAeMidCurEX.u32 = ISP_CORE_DRV_GET_CoreAeMidCurEx(apstIspCoreReg);
  	pAeSts->ae_mid_cur_ex =  gtAeMidCurEX.u32;

  	U_ISP_CORE_AE_SHORT_CUR_EX         gtAeShortCurEX;
  	gtAeShortCurEX.u32 = ISP_CORE_DRV_GET_CoreAeShortCurEx(apstIspCoreReg);
  	pAeSts->ae_short_cur_ex =  gtAeShortCurEX.u32;

  	U_ISP_CORE_AE_CUR_DIGITAL_GAIN     gtAeCurDigitalGain;
  	gtAeCurDigitalGain.u32 = ISP_CORE_DRV_GET_CoreAeCurDigitalGain(apstIspCoreReg);
  	pAeSts->ae_digital_gain =  gtAeCurDigitalGain.u32;

  	U_ISP_CORE_AE_CUR_AVE_BRIGHTNESS   gtAeCurAvBrightness;
  	gtAeCurAvBrightness.u32 = ISP_CORE_DRV_GET_CoreAeCurAveBrightness(apstIspCoreReg);
  	pAeSts->ave_brightness =  gtAeCurAvBrightness.u32;

  	U_ISP_CORE_AE_CUR_DN_STATUS        gtAeCurDNStatus;
  	gtAeCurDNStatus.u32 = ISP_CORE_DRV_GET_CoreAeCurDnStatus(apstIspCoreReg);
  	pAeSts->ae_day_night_status =  gtAeCurDNStatus.u32;

  	U_ISP_CORE_AE_EX_STATUS            gtAeEXStatus;
  	gtAeEXStatus.u32 = ISP_CORE_DRV_GET_CoreAeExStatus(apstIspCoreReg);
  	pAeSts->ae_ex_status =  gtAeEXStatus.u32;

  	U_ISP_CORE_AE_SUM                  gtAgtAeShortCurEXeSum;
  	gtAgtAeShortCurEXeSum.u32 = ISP_CORE_DRV_GET_CoreAeSum(apstIspCoreReg);
  	pAeSts->ae_sum =  gtAgtAeShortCurEXeSum.u32;

  	U_ISP_CORE_AE_PIXEL_SUM            gtAePixelSum;
  	gtAePixelSum.u32 = ISP_CORE_DRV_GET_CoreAePixelSum(apstIspCoreReg);
  	pAeSts->ae_mid_cur_ex =  gtAePixelSum.u32;
  
  	return 0;
} 
/*
*AWB
*/
static int ISP_DRV_CORE_SetAwbCtl(ISP_CORE_AWB_CTL_S *pstAwbCtl)
{
	ISP_CHECK_POINTER(pstAwbCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_AWB_CTL stAwbCtl;
	stAwbCtl.u32 = 0;
	stAwbCtl.bits.awb_d65_en = pstAwbCtl->awb_d65_en;
	stAwbCtl.bits.awb_ccm_en = pstAwbCtl->awb_ccm_en;
	stAwbCtl.bits.awb_en = pstAwbCtl->awb_en;
	stAwbCtl.bits.awb_mode_sel = pstAwbCtl->awb_mode_sel;
	stAwbCtl.bits.awb_hist_mode_sel = pstAwbCtl->awb_hist_mode_sel;
	stAwbCtl.bits.awb_veri_en = pstAwbCtl->awb_veri_en;
	stAwbCtl.bits.awb_fb_en = pstAwbCtl->awb_fb_en;
	stAwbCtl.bits.awb_value_save_en = pstAwbCtl->awb_value_save_en;
	stAwbCtl.bits.awb_ccm_adp_adjust_en = pstAwbCtl->awb_ccm_adp_adjust_en;
	stAwbCtl.bits.awb_stab_en = pstAwbCtl->awb_stab_en;
	ISP_CORE_DRV_SET_CoreAwbCtl(apstIspCoreReg, stAwbCtl.u32);

	U_ISP_CORE_AWB_D65_RED_GAIN stD65RedGain;
	stD65RedGain.u32 = 0;
	stD65RedGain.bits.awb_d65_red_gain = pstAwbCtl->awb_d65_red_gain;
	ISP_CORE_DRV_SET_CoreAwbD65RedGain(apstIspCoreReg, stD65RedGain.u32);

	U_ISP_CORE_AWB_D65_BLUE_GAIN stD65BlueGain;
	stD65BlueGain.u32 = 0;
	stD65BlueGain.bits.awb_d65_blue_gain = pstAwbCtl->awb_d65_blue_gain;
	ISP_CORE_DRV_SET_CoreAwbD65BlueGain(apstIspCoreReg, stD65BlueGain.u32);

	U_ISP_CORE_CCM_RR_COFF stRrCoff;
	stRrCoff.u32 = 0;
	stRrCoff.bits.ccm_rr_coff = pstAwbCtl->ccm_rr_coff;
	ISP_CORE_DRV_SET_CoreCcmRrCoff(apstIspCoreReg, stRrCoff.u32);

	U_ISP_CORE_CCM_RG_COFF stRgCoff;
	stRgCoff.u32 = 0;
	stRgCoff.bits.ccm_rg_coff = pstAwbCtl->ccm_rg_coff;
	ISP_CORE_DRV_SET_CoreCcmRgCoff(apstIspCoreReg, stRgCoff.u32);

	U_ISP_CORE_CCM_RB_COFF stRboff;
	stRboff.u32 = 0;
	stRboff.bits.ccm_rb_coff = pstAwbCtl->ccm_rb_coff;
    ISP_CORE_DRV_SET_CoreCcmRbCoff(apstIspCoreReg, stRboff.u32);

	U_ISP_CORE_CCM_GR_COFF stGrCoff;
	stGrCoff.u32 = 0;
	stGrCoff.bits.ccm_gr_coff = pstAwbCtl->ccm_gr_coff;
	ISP_CORE_DRV_SET_CoreCcmGrCoff(apstIspCoreReg, stGrCoff.u32);

	U_ISP_CORE_CCM_GG_COFF stGgCoff;
	stGgCoff.u32 = 0;
	stGgCoff.bits.ccm_gg_coff = pstAwbCtl->ccm_gg_coff;
	ISP_CORE_DRV_SET_CoreCcmGgCoff(apstIspCoreReg, stGgCoff.u32);

	U_ISP_CORE_CCM_GB_COFF stGbCoff;
	stGbCoff.u32 = 0;
	stGbCoff.bits.ccm_gb_coff = pstAwbCtl->ccm_gb_coff;
	ISP_CORE_DRV_SET_CoreCcmGbCoff(apstIspCoreReg, stGbCoff.u32);

	U_ISP_CORE_CCM_BR_COFF stBrCoff;
	stBrCoff.u32 = 0;
	stBrCoff.bits.ccm_br_coff = pstAwbCtl->ccm_br_coff;
	ISP_CORE_DRV_SET_CoreCcmBrCoff(apstIspCoreReg, stBrCoff.u32);

	U_ISP_CORE_CCM_BG_COFF stBgCoff;
	stBgCoff.u32 = 0;
	stBgCoff.bits.ccm_bg_coff = pstAwbCtl->ccm_bg_coff;
	ISP_CORE_DRV_SET_CoreCcmBgCoff(apstIspCoreReg, stBgCoff.u32);

	U_ISP_CORE_CCM_BB_COFF stBbCoff;
	stBbCoff.u32 = 0;
	stBbCoff.bits.ccm_bb_coff = pstAwbCtl->ccm_bb_coff;
	ISP_CORE_DRV_SET_CoreCcmBbCoff(apstIspCoreReg, stBbCoff.u32);

	U_ISP_CORE_CCM_CORRECT_COFF stCorrCoff;
	stCorrCoff.u32 = 0;
	stCorrCoff.bits.ccm_correct_coff = pstAwbCtl->ccm_correct_coff;
	ISP_CORE_DRV_SET_CoreCcmCorrectCoff(apstIspCoreReg, stCorrCoff.u32);

	U_ISP_CORE_AWB_WIN_H_START stHStart;
	stHStart.u32 = 0;
	stHStart.bits.awb_win_h_start = pstAwbCtl->awb_win_h_start;
	ISP_CORE_DRV_SET_CoreAwbWinHStart(apstIspCoreReg, stHStart.u32);

    U_ISP_CORE_AWB_WIN_V_START stVStart;
	stVStart.u32 = 0;
	stVStart.bits.awb_win_v_start = pstAwbCtl->awb_win_v_start;
	ISP_CORE_DRV_SET_CoreAwbWinVStart(apstIspCoreReg, stVStart.u32);

	U_ISP_CORE_AWB_WIN_H_END stHEnd;
	stHEnd.u32 = 0;
	stHEnd.bits.awb_win_h_end = pstAwbCtl->awb_win_h_end;
	ISP_CORE_DRV_SET_CoreAwbWinHEnd(apstIspCoreReg, stHEnd.u32);

	U_ISP_CORE_AWB_WIN_V_END stVEnd;
	stVEnd.u32 = 0;
	stVEnd.bits.awb_win_v_end = pstAwbCtl->awb_win_v_end;
	ISP_CORE_DRV_SET_CoreAwbWinVEnd(apstIspCoreReg, stVEnd.u32);

    U_ISP_CORE_AWB_CORRECT_DIFF_TH stCorDiffTh;
	stCorDiffTh.u32 = 0;
	stCorDiffTh.bits.awb_correct_diff_th = pstAwbCtl->awb_correct_diff_th;
	ISP_CORE_DRV_SET_CoreAwbCorrectDiffTh(apstIspCoreReg, stCorDiffTh.u32);

	U_ISP_CORE_AWB_RES_TIME stResTime;
	stResTime.u32 = 0;
	stResTime.bits.awb_color_changeres_time = pstAwbCtl->awb_color_changeres_time;
	ISP_CORE_DRV_SET_CoreAwbResTime(apstIspCoreReg, stResTime.u32);

	U_ISP_CORE_AWB_HIST_TH stHistTh;
	stHistTh.u32 = 0;
	stHistTh.bits.awb_historgram_th = pstAwbCtl->awb_historgram_th;
	ISP_CORE_DRV_SET_CoreAwbHistTh(apstIspCoreReg, stHistTh.u32);

	U_ISP_CORE_AWB_RED_GAIN_ADJUST stRedGainAd;
	stRedGainAd.u32 = 0;
	stRedGainAd.bits.awb_red_gain_adjust = pstAwbCtl->awb_red_gain_adjust;
	ISP_CORE_DRV_SET_CoreAwbRedGainAdjust(apstIspCoreReg, stRedGainAd.u32);

	U_ISP_CORE_AWB_GREEN_GAIN_ADJUST stGreenGainAd;
	stGreenGainAd.u32 = 0;
	stGreenGainAd.bits.awb_green_gain_adjust = pstAwbCtl->awb_green_gain_adjust;
	ISP_CORE_DRV_SET_CoreAwbGreenGainAdjust(apstIspCoreReg, stGreenGainAd.u32);

	U_ISP_CORE_AWB_BLUE_GAIN_ADJUST stBlueGainAd;
	stBlueGainAd.u32 = 0;
	stBlueGainAd.bits.awb_blue_gain_adjust = pstAwbCtl->awb_blue_gain_adjust;
	ISP_CORE_DRV_SET_CoreAwbBlueGainAdjust(apstIspCoreReg, stBlueGainAd.u32);

	U_ISP_CORE_AWB_RED_MAX_VALUE stRedMaxValue;
	stRedMaxValue.u32 = 0;
	stRedMaxValue.bits.awb_red_max_value = pstAwbCtl->awb_red_max_value;
	ISP_CORE_DRV_SET_CoreAwbRedMaxValue(apstIspCoreReg, stRedMaxValue.u32);

	U_ISP_CORE_AWB_BLUE_MAX_VALUE stBlueMaxValue;
	stBlueMaxValue.u32 = 0;
	stBlueMaxValue.bits.awb_blue_max_value = pstAwbCtl->awb_blue_max_value;
	ISP_CORE_DRV_SET_CoreAwbBlueMaxValue(apstIspCoreReg, stBlueMaxValue.u32);

	U_ISP_CORE_AWB_RED_MIN_VALUE stRedMinValue;
	stRedMinValue.u32 = 0;
	stRedMinValue.bits.awb_red_min_value = pstAwbCtl->awb_red_min_value;
	ISP_CORE_DRV_SET_CoreAwbRedMinValue(apstIspCoreReg, stRedMinValue.u32);

	U_ISP_CORE_AWB_BLUE_MIN_VALUE stBlueMinValue;
	stBlueMinValue.u32 = 0;
	stBlueMinValue.bits.awb_blue_min_value = pstAwbCtl->awb_blue_min_value;
	ISP_CORE_DRV_SET_CoreAwbBlueMinValue(apstIspCoreReg, stBlueMinValue.u32);	

	return 0;
}

int ISP_DRV_CORE_GetAwbSts(ISP_CORE_AWB_STS_S *pAwbSts)
{
	ISP_CHECK_POINTER(pAwbSts);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);


 	U_ISP_CORE_AWB_BLUE_HIST_VALUE     gtAwbBHistVal;
  	gtAwbBHistVal.u32 = ISP_CORE_DRV_GET_CoreAwbBlueObjValue(apstIspCoreReg);
  	pAwbSts->awb_blue_hist_value = gtAwbBHistVal.u32;

  	U_ISP_CORE_AWB_BLUE_HIST_PIXEL     gtAwbBHistPix;
  	gtAwbBHistPix.u32 = ISP_CORE_DRV_GET_CoreAwbBlueHistPixel(apstIspCoreReg);
  	pAwbSts->awb_blue_hist_pixel = gtAwbBHistPix.u32;

  	U_ISP_CORE_AWB_RED_HIST_VALUE      gtAwbRHistVal;
  	gtAwbRHistVal.u32 = ISP_CORE_DRV_GET_CoreAwbRedHistValue(apstIspCoreReg);
  	pAwbSts->awb_red_hist_value = gtAwbRHistVal.u32;

  	U_ISP_CORE_AWB_RED_HIST_PIXEL      gtAwbRHistPix;
  	gtAwbRHistPix.u32 = ISP_CORE_DRV_GET_CoreAwbRedHistPixel(apstIspCoreReg);
  	pAwbSts->awb_red_hist_pixel = gtAwbRHistPix.u32;

  	U_ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE   gtAwbBYPassBHistVal;
  	gtAwbBYPassBHistVal.u32 = ISP_CORE_DRV_GET_CoreAwbBypassBlueHistValue(apstIspCoreReg);
  	pAwbSts->awb_bypass_blue_hist_value = gtAwbBYPassBHistVal.u32;

  	U_ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL   gtAwbBypassBHistPix;
  	gtAwbBypassBHistPix.u32 = ISP_CORE_DRV_GET_CoreAwbBypassBlueHistPixel(apstIspCoreReg);
  	pAwbSts->awb_bypass_blue_hist_pixel = gtAwbBypassBHistPix.u32;

  	U_ISP_CORE_AWB_BYPASS_RED_HIST_VALUE   gtAwbBYPASSRHistVal;
  	gtAwbBYPASSRHistVal.u32 = ISP_CORE_DRV_GET_CoreAwbBypassRedHistValue(apstIspCoreReg);
  	pAwbSts->awb_bypass_red_hist_value = gtAwbBYPASSRHistVal.u32;

  	U_ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL   gtAwbBypassRHistPix;
  	gtAwbBypassRHistPix.u32 = ISP_CORE_DRV_GET_CoreAwbBypassRedHistPixel(apstIspCoreReg);
  	pAwbSts->awb_bypass_red_hist_pixel = gtAwbBypassRHistPix.u32;

  	U_ISP_CORE_AWB_RED_VALUE           gtAwbRVal;
  	gtAwbRVal.u32 = ISP_CORE_DRV_GET_CoreAwbRedValue(apstIspCoreReg);
  	pAwbSts->awb_red_value = gtAwbRVal.u32;

  	U_ISP_CORE_AWB_GREEN_VALUE         gtAwbGVal;
  	gtAwbGVal.u32 = ISP_CORE_DRV_GET_CoreAwbGreenValue(apstIspCoreReg);
  	pAwbSts->awb_green_value = gtAwbGVal.u32;

  	U_ISP_CORE_AWB_BLUE_VALUE          gtAwbBVal;
  	gtAwbBVal.u32 = ISP_CORE_DRV_GET_CoreAwbBlueValue(apstIspCoreReg);
  	pAwbSts->awb_blue_value = gtAwbBVal.u32;

  	U_ISP_CORE_AWB_ORG_RED_VALUE       gtAwbORGRVal;
  	gtAwbORGRVal.u32 = ISP_CORE_DRV_GET_CoreAwbOrgRedValue(apstIspCoreReg);
  	pAwbSts->awb_org_image_red_value = gtAwbORGRVal.u32;

  	U_ISP_CORE_AWB_ORG_GREEN_VALUE     gtAwbORGGVal;
  	gtAwbORGGVal.u32 = ISP_CORE_DRV_GET_CoreAwbOrgGreenValue(apstIspCoreReg);
  	pAwbSts->awb_org_image_green_value = gtAwbORGGVal.u32;

  	U_ISP_CORE_AWB_ORG_BLUE_VALUE      gtAwbORGBVal;
  	gtAwbORGBVal.u32 = ISP_CORE_DRV_GET_CoreAwbOrgBlueValue(apstIspCoreReg);
  	pAwbSts->awb_org_image_blue_value = gtAwbORGBVal.u32;

  	return 0;
}
/*
*CSC
*/
static int ISP_DRV_CORE_SetCscCtl(ISP_CORE_CSC_CTL_S *pstCscCtl)
{
	ISP_CHECK_POINTER(pstCscCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_CSC_R2Y_00 st00;
	st00.u32 = 0;
	st00.bits.csc_r2y_00 = pstCscCtl->csc_r2y_00;
	ISP_CORE_DRV_SET_CoreCscR2Y00(apstIspCoreReg, st00.u32);

	U_ISP_CORE_CSC_R2Y_01 st01;
	st01.u32 = 0;
	st01.bits.csc_r2y_01 = pstCscCtl->csc_r2y_01;
	ISP_CORE_DRV_SET_CoreCscR2Y01(apstIspCoreReg, st01.u32);

	U_ISP_CORE_CSC_R2Y_02 st02;
	st02.u32 = 0;
	st02.bits.csc_r2y_02 = pstCscCtl->csc_r2y_02;
    ISP_CORE_DRV_SET_CoreCscR2Y02(apstIspCoreReg, st02.u32);

	U_ISP_CORE_CSC_R2Y_10 st10;
	st10.u32 = 0;
	st10.bits.csc_r2y_10 = pstCscCtl->csc_r2y_10;
    ISP_CORE_DRV_SET_CoreCscR2Y10(apstIspCoreReg, st10.u32);

	U_ISP_CORE_CSC_R2Y_11 st11;
	st11.u32 = 0;
	st11.bits.csc_r2y_11 = pstCscCtl->csc_r2y_11;
	ISP_CORE_DRV_SET_CoreCscR2Y11(apstIspCoreReg, st11.u32);

	U_ISP_CORE_CSC_R2Y_12 st12;
	st12.u32 = 0;
	st12.bits.csc_r2y_12 = pstCscCtl->csc_r2y_12;
	ISP_CORE_DRV_SET_CoreCscR2Y12(apstIspCoreReg, st12.u32);

	U_ISP_CORE_CSC_R2Y_20 st20;
	st20.u32 = 0;
	st20.bits.csc_r2y_20 = pstCscCtl->csc_r2y_20;
	ISP_CORE_DRV_SET_CoreCscR2Y20(apstIspCoreReg, st20.u32);

	U_ISP_CORE_CSC_R2Y_21 st21;
	st21.u32 = 0;
	st21.bits.csc_r2y_21 = pstCscCtl->csc_r2y_21;
	ISP_CORE_DRV_SET_CoreCscR2Y21(apstIspCoreReg, st21.u32);

	U_ISP_CORE_CSC_R2Y_22 st22;
	st22.u32 = 0;
	st22.bits.csc_r2y_22 = pstCscCtl->csc_r2y_22;
	ISP_CORE_DRV_SET_CoreCscR2Y22(apstIspCoreReg, st22.u32);

	return 0;
}
/*
* WDR
*/
static int ISP_DRV_CORE_SetWdrCtl(ISP_CORE_WDR_CTL_S *pstWdrCtl)
{
	ISP_CHECK_POINTER(pstWdrCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_WDR_CTL stWdrCtl;
	stWdrCtl.u32 = 0;
	stWdrCtl.bits.wdr_fusion_en = pstWdrCtl->wdr_fusion_en;
	stWdrCtl.bits.wdr_frame_sel = pstWdrCtl->wdr_frame_sel;
	stWdrCtl.bits.wdr_adp_adjust_en = pstWdrCtl->wdr_adp_adjust_en;
	stWdrCtl.bits.wdr_stab_en = pstWdrCtl->wdr_stab_en;
	stWdrCtl.bits.wdr_en = pstWdrCtl->wdr_en;
	stWdrCtl.bits.wdr_ghost_remove_en = pstWdrCtl->wdr_ghost_remove_en;
	stWdrCtl.bits.wdr_3_frame_out_mode = pstWdrCtl->wdr_3_frame_out_mode;
	stWdrCtl.bits.wdr_mode_sel = pstWdrCtl->wdr_mode_sel;
	stWdrCtl.bits.wdr_2frame_ex_ratio = pstWdrCtl->wdr_2frame_ex_ratio;
	stWdrCtl.bits.wdr_3frame_ex_ratio = pstWdrCtl->wdr_3frame_ex_ratio;
	stWdrCtl.bits.wdr_stat_img_sel = pstWdrCtl->wdr_stat_img_sel;
	stWdrCtl.bits.wdr_ltm_data_sel = pstWdrCtl->wdr_ltm_data_sel;
	stWdrCtl.bits.wdr_tz_data_sel = pstWdrCtl->wdr_tz_data_sel;
	stWdrCtl.bits.wdr_remove_purple_en = pstWdrCtl->wdr_remove_purple_en;
	ISP_CORE_DRV_SET_CoreWdrCtl(apstIspCoreReg, stWdrCtl.u32);

	U_ISP_CORE_WDR_OVER_EX_RATIO_TH1 stRatioTh1;
	stRatioTh1.u32 = 0;
	stRatioTh1.bits.wdr_over_ex_ratio_th1 = pstWdrCtl->wdr_over_ex_ratio_th1;
	ISP_CORE_DRV_SET_CoreWdrOverExRatioTh1(apstIspCoreReg, stRatioTh1.u32);

	U_ISP_CORE_WDR_OVER_EX_RATIO_TH2 stRatioTh2;
	stRatioTh2.u32 = 0;
	stRatioTh2.bits.wdr_over_ex_ratio_th2 = pstWdrCtl->wdr_over_ex_ratio_th2;
	ISP_CORE_DRV_SET_CoreWdrOverExRatioTh2(apstIspCoreReg, stRatioTh2.u32);

	U_ISP_CORE_WDR_FUSION_RATIO_TH stFusionRatio;
	stFusionRatio.u32 = 0;
	stFusionRatio.bits.wdr_fusion_ratio_th = pstWdrCtl->wdr_fusion_ratio_th;
	ISP_CORE_DRV_SET_CoreWdrFusionRatioTh(apstIspCoreReg, stFusionRatio.u32);

	U_ISP_CORE_WDR_FUSION_VALUE1 stFusionValue1;
	stFusionValue1.u32 = 0;
	stFusionValue1.bits.wdr_fusion_value1 = pstWdrCtl->wdr_fusion_value1;
	ISP_CORE_DRV_SET_CoreWdrFusionValue1(apstIspCoreReg, stFusionValue1.u32);

	U_ISP_CORE_WDR_FUSION_VALUE2 stFusionValue2;
	stFusionValue2.u32 = 0;
	stFusionValue2.bits.wdr_fusion_value2 = pstWdrCtl->wdr_fusion_value2;
	ISP_CORE_DRV_SET_CoreWdrFusionValue2(apstIspCoreReg, stFusionValue2.u32);	
	return 0;
}
/*
*ADA
*/
static int ISP_DRV_CORE_SetAdaCtl(ISP_CORE_ADA_CTL_S *pstAdaCtl)
{
	ISP_CHECK_POINTER(pstAdaCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_ADA_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.ada_rgb_gamma_en = pstAdaCtl->ada_rgb_gamma_en;
	stCtl.bits.ada_yuv_gamma_en = pstAdaCtl->ada_yuv_gamma_en;
	stCtl.bits.ada_adjust_en = pstAdaCtl->ada_adjust_en;
	stCtl.bits.ada_img_stab_en = pstAdaCtl->ada_img_stab_en;
	stCtl.bits.ada_ccr_en = pstAdaCtl->ada_ccr_en;
	stCtl.bits.ada_adp_en = pstAdaCtl->ada_adp_en;
	stCtl.bits.ada_adp_ccr_en = pstAdaCtl->ada_adp_ccr_en;
	stCtl.bits.ada_stat_mode_sel = pstAdaCtl->ada_stat_mode_sel;
	stCtl.bits.ada_enh_mode_sel = pstAdaCtl->ada_enh_mode_sel;
	ISP_CORE_DRV_SET_CoreAdaCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_ADA_STAT_MAX_VALUE stStatMax;
	stStatMax.u32 = 0;
	stStatMax.bits.ada_stat_max_value = pstAdaCtl->ada_stat_max_value;
	ISP_CORE_DRV_SET_CoreAdaStatMaxValue(apstIspCoreReg, stStatMax.u32);

	U_ISP_CORE_ADA_AD_STREN_MAX_VALUE stStrenMax;
	stStrenMax.u32 = 0;
	stStrenMax.bits.ada_ad_stren_max_value = pstAdaCtl->ada_ad_stren_max_value;
	ISP_CORE_DRV_SET_CoreAdaAdStrenMaxValue(apstIspCoreReg, stStrenMax.u32);

	U_ISP_CORE_ADA_WIN_H_START stHStart;
	stHStart.u32 = 0;
	stHStart.bits.ada_win_h_start = pstAdaCtl->ada_win_h_start;
	ISP_CORE_DRV_SET_CoreAdaWinHStart(apstIspCoreReg, stHStart.u32);

	U_ISP_CORE_ADA_WIN_V_START stVStart;
	stVStart.u32 = 0;
	stVStart.bits.ada_win_v_start = pstAdaCtl->ada_win_v_start;
	ISP_CORE_DRV_SET_CoreAdaWinVStart(apstIspCoreReg, stVStart.u32);

	U_ISP_CORE_ADA_WIN_H_END stHEnd;
	stHEnd.u32 = 0;
	stHEnd.bits.ada_win_h_end = pstAdaCtl->ada_win_h_end;
	ISP_CORE_DRV_SET_CoreAdaWinHEnd(apstIspCoreReg, stHEnd.u32);

	U_ISP_CORE_ADA_WIN_V_END stVEnd;
	stVEnd.u32 = 0;
	stVEnd.bits.ada_win_v_end = pstAdaCtl->ada_win_v_end;
	ISP_CORE_DRV_SET_CoreAdaWinVEnd(apstIspCoreReg, stVEnd.u32);
	return 0;
}
/*
*rgbir
*/
static int ISP_DRV_CORE_SetRgbIrCtl(ISP_CORE_RGBIR_CTL_S *pstRgbIrCtl)
{

	ISP_CHECK_POINTER(pstRgbIrCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_RGBIR_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.rgbir_en = pstRgbIrCtl->rgbir_en;
	stCtl.bits.rgbir_rtf_en = pstRgbIrCtl->rgbir_rtf_en;
	stCtl.bits.rgbir_rpc_en = pstRgbIrCtl->rgbir_rpc_en;
	stCtl.bits.rgbir_fusion_en = pstRgbIrCtl->rgbir_fusion_en;
	stCtl.bits.rgbir_output_sel = pstRgbIrCtl->rgbir_output_sel;
	ISP_CORE_DRV_SET_CoreRgbirCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_RGBIR_RPC_MAX_VALUE stMax;
	stMax.u32 = 0;
	stMax.bits.rgbir_rpc_max_value = pstRgbIrCtl->rgbir_rpc_max_value;
	ISP_CORE_DRV_SET_CoreRgbirRpcMaxValue(apstIspCoreReg, stMax.u32);

	U_ISP_CORE_RGBIR_RPC_COLOR_COFF stColorCoff;
	stColorCoff.u32 = 0;
	stColorCoff.bits.rgbir_rpc_color_coff = pstRgbIrCtl->rgbir_rpc_color_coff;
	ISP_CORE_DRV_SET_CoreRgbirRpcColorCoff(apstIspCoreReg, stColorCoff.u32);

	U_ISP_CORE_RGBIR_RPC_LUMA_COFF stLumaCoff;
	stLumaCoff.u32 = 0;
	stLumaCoff.bits.rgbir_rpc_luma_coff = pstRgbIrCtl->rgbir_rpc_luma_coff;
	ISP_CORE_DRV_SET_CoreRgbirRpcLumaCoff(apstIspCoreReg, stLumaCoff.u32);

	U_ISP_CORE_RGBIR_RPC_TH stTh;
	stTh.u32 = 0;
	stTh.bits.rgbir_rpc_th = pstRgbIrCtl->rgbir_rpc_th;
	ISP_CORE_DRV_SET_CoreRgbirRpcTh(apstIspCoreReg, stTh.u32);

	U_ISP_CORE_RGBIR_RPC_TH1 stTh1;
	stTh1.u32 = 0;
	stTh1.bits.rgbir_rpc_th1 = pstRgbIrCtl->rgbir_rpc_th1;
	ISP_CORE_DRV_SET_CoreRgbirRpcTh1(apstIspCoreReg, stTh1.u32);	

	return 0;
}
/*
* 2D Noise Reduction 
*/
static int ISP_DRV_CORE_Set2DnrCtl(ISP_CORE_2DNR_CTL_S *pst2DnrCtl)
{
	ISP_CHECK_POINTER(pst2DnrCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_2DNR_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.core_2dnr_pcf_en = pst2DnrCtl->core_2dnr_pcf_en;
	stCtl.bits.core_2dnr_raw_en = pst2DnrCtl->core_2dnr_raw_en;
	stCtl.bits.core_2dnr_edge_en = pst2DnrCtl->core_2dnr_edge_en;
	stCtl.bits.core_2dnr_bap_en = pst2DnrCtl->core_2dnr_bap_en;
	stCtl.bits.core_2dnr_luma_en = pst2DnrCtl->core_2dnr_luma_en;
	stCtl.bits.core_2dnr_chroma_en = pst2DnrCtl->core_2dnr_chroma_en;
	stCtl.bits.core_2dnr_pcf_adp_en = pst2DnrCtl->core_2dnr_pcf_adp_en;
	stCtl.bits.core_2dnr_raw_adp_en = pst2DnrCtl->core_2dnr_raw_adp_en;
	stCtl.bits.core_2dnr_luma_adp_en = pst2DnrCtl->core_2dnr_luma_adp_en;
	stCtl.bits.core_2dnr_chroma_adp_en = pst2DnrCtl->core_2dnr_chroma_adp_en;
	ISP_CORE_DRV_SET_Core2DnrCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_2DNR_RAW_INTENSITY stRawInte;
	stRawInte.u32 = 0;
	stRawInte.bits.core_2dnr_raw_intensity = pst2DnrCtl->core_2dnr_raw_intensity;
	ISP_CORE_DRV_SET_Core2DnrRawIntensity(apstIspCoreReg, stRawInte.u32);

	U_ISP_CORE_2DNR_BAP_INTENSITY stBapInte;
	stBapInte.u32 = 0;
	stBapInte.bits.core_2dnr_bap_intensity = pst2DnrCtl->core_2dnr_bap_intensity;
	ISP_CORE_DRV_SET_Core2DnrBapIntensity(apstIspCoreReg, stBapInte.u32);

	U_ISP_CORE_2DNR_EDGE_INTENSITY stEdgeInte;
	stEdgeInte.u32 = 0;
	stEdgeInte.bits.core_2dnr_edge_intensity = pst2DnrCtl->core_2dnr_edge_intensity;
	ISP_CORE_DRV_SET_Core2DnrEdgeIntensity(apstIspCoreReg, stEdgeInte.u32);

	U_ISP_CORE_2DNR_LUMA_INTENSITY stLumaInte;
	stLumaInte.u32 = 0;
	stLumaInte.bits.core_2dnr_luma_intensity = pst2DnrCtl->core_2dnr_luma_intensity;
	ISP_CORE_DRV_SET_Core2DnrLumaIntensity(apstIspCoreReg, stLumaInte.u32);

	U_ISP_CORE_2DNR_CHROMA_INTENSITY stChromaInte;
	stChromaInte.u32 = 0;
	stChromaInte.bits.core_2dnr_chroma_intensity = pst2DnrCtl->core_2dnr_chroma_intensity;
	ISP_CORE_DRV_SET_Core2DnrChromaIntensity(apstIspCoreReg, stChromaInte.u32);
	return 0;
}
/*
* 3D Noise Reduction 
*/
static int ISP_DRV_CORE_Set3DnrCtl(ISP_CORE_3DNR_CTL_S *pst3DnrCtl)
{
	ISP_CHECK_POINTER(pst3DnrCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_3DNR_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.core_3dnr_en = pst3DnrCtl->core_3dnr_en;
	stCtl.bits.core_3dnr_pre_luma_en = pst3DnrCtl->core_3dnr_pre_luma_en;
	stCtl.bits.core_3dnr_pre_chroma_en = pst3DnrCtl->core_3dnr_pre_chroma_en;
	stCtl.bits.core_3dnr_main_luma_en = pst3DnrCtl->core_3dnr_main_luma_en;
	stCtl.bits.core_3dnr_main_chroma_en = pst3DnrCtl->core_3dnr_main_chroma_en;
	stCtl.bits.core_3dnr_post_luma_en = pst3DnrCtl->core_3dnr_post_luma_en;
	stCtl.bits.core_3dnr_post_chroma_en = pst3DnrCtl->core_3dnr_post_chroma_en;
	stCtl.bits.core_3dnr_2d_luma_en = pst3DnrCtl->core_3dnr_2d_luma_en;
	stCtl.bits.core_3dnr_2d_chroma_en = pst3DnrCtl->core_3dnr_2d_chroma_en;
	stCtl.bits.core_3dnr_wb_en = pst3DnrCtl->core_3dnr_wb_en;
	stCtl.bits.core_3dnr_wb_sel = pst3DnrCtl->core_3dnr_wb_sel;
	stCtl.bits.core_3dnr_adp_luma_en = pst3DnrCtl->core_3dnr_adp_luma_en;
	stCtl.bits.core_3dnr_adp_chroma_en = pst3DnrCtl->core_3dnr_adp_chroma_en;
	ISP_CORE_DRV_SET_Core3DnrCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_3DNR_PRE_LUMA_TH stPreLumaTh;
	stPreLumaTh.u32 = 0;
	stPreLumaTh.bits.core_3dnr_pre_luma_th = pst3DnrCtl->core_3dnr_pre_luma_th;
	ISP_CORE_DRV_SET_Core3DnrPreLumaTh(apstIspCoreReg, stPreLumaTh.u32);

	U_ISP_CORE_3DNR_PRE_LUMA_INTENSITY stPreLumaInten;
	stPreLumaInten.u32 = 0;
	stPreLumaInten.bits.core_3dnr_pre_luma_intensity = pst3DnrCtl->core_3dnr_pre_luma_intensity;
	ISP_CORE_DRV_SET_Core3DnrPreLumaIntensity(apstIspCoreReg, stPreLumaInten.u32);

	U_ISP_CORE_3DNR_PRE_CHROMA_INTENSITY stPreChromaInten;
	stPreChromaInten.u32 = 0;
	stPreChromaInten.bits.core_3dnr_pre_chroma_intensity = pst3DnrCtl->core_3dnr_pre_chroma_intensity;
    ISP_CORE_DRV_SET_Core3DnrPreChromaIntensity(apstIspCoreReg, stPreChromaInten.u32);

	U_ISP_CORE_3DNR_MID_FILTER_TH stMidFilterTh;
	stMidFilterTh.u32 = 0;
	stMidFilterTh.bits.core_3dnr_mid_filter_th = pst3DnrCtl->core_3dnr_mid_filter_th;
	ISP_CORE_DRV_SET_Core3DnrMidFilterTh(apstIspCoreReg, stMidFilterTh.u32);

	U_ISP_CORE_3DNR_PRE_MID_FILTER_TH stPreMidFilterTh;
	stPreMidFilterTh.u32 = 0;
	stPreMidFilterTh.bits.core_3dnr_pre_mid_filter_th = pst3DnrCtl->core_3dnr_pre_mid_filter_th;
	ISP_CORE_DRV_SET_Core3DnrPreMidFilterTh(apstIspCoreReg, stPreMidFilterTh.u32);

	U_ISP_CORE_3DNR_CUR_FILTER_TH stCurFilterTh;
	stCurFilterTh.u32 = 0;
	stCurFilterTh.bits.core_3dnr_cur_mid_filter_th = pst3DnrCtl->core_3dnr_cur_mid_filter_th;
	ISP_CORE_DRV_SET_Core3DnrCurFilterTh(apstIspCoreReg, stCurFilterTh.u32);

	U_ISP_CORE_3DNR_LOW_PASS_FILTER_TH stLowFilterTh;
	stLowFilterTh.u32 = 0;
	stLowFilterTh.bits.core_3dnr_low_pass_filter_th = pst3DnrCtl->core_3dnr_low_pass_filter_th;
	ISP_CORE_DRV_SET_Core3DnrLowPassFilterTh(apstIspCoreReg, stLowFilterTh.u32);

	U_ISP_CORE_3DNR_LUMA_TH stLumaTh;
	stLumaTh.u32 = 0;
	stLumaTh.bits.core_3dnr_luma_th = pst3DnrCtl->core_3dnr_luma_th;
	ISP_CORE_DRV_SET_Core3DnrLumaTh(apstIspCoreReg, stLumaTh.u32);

	U_ISP_CORE_3DNR_MIN_VALUE stMinValue;
	stMinValue.u32 = 0;
	stMinValue.bits.core_3dnr_min_value = pst3DnrCtl->core_3dnr_min_value;
    ISP_CORE_DRV_SET_Core3DnrMinValue(apstIspCoreReg, stMinValue.u32);

	U_ISP_CORE_3DNR_LUMA_INTENSITY stLumaInten;
	stLumaInten.u32 = 0;
	stLumaInten.bits.core_3dnr_luma_intensity = pst3DnrCtl->core_3dnr_luma_intensity;
	ISP_CORE_DRV_SET_Core3DnrLumaIntensity(apstIspCoreReg, stLumaInten.u32);

	U_ISP_CORE_3DNR_CHROMA_INTENSITY stChromaInten;
	stChromaInten.u32 = 0;
	stChromaInten.bits.core_3dnr_chroma_intensity = pst3DnrCtl->core_3dnr_chroma_intensity;
	ISP_CORE_DRV_SET_Core3DnrChromaIntensity(apstIspCoreReg, stChromaInten.u32);

	U_ISP_CORE_3DNR_POST_EDGE_TH stPostEdge;
	stPostEdge.u32 = 0;
	stPostEdge.bits.core_3dnr_post_edge_th = pst3DnrCtl->core_3dnr_post_edge_th;
	ISP_CORE_DRV_SET_Core3DnrPostEdgeTh(apstIspCoreReg, stPostEdge.u32);

	U_ISP_CORE_3DNR_POST_LUMA_INTENSITY stPostLumaInten;
	stPostLumaInten.u32 = 0;
	stPostLumaInten.bits.core_3dnr_post_luma_intensity = pst3DnrCtl->core_3dnr_post_luma_intensity;
	ISP_CORE_DRV_SET_Core3DnrPostLumaIntensity(apstIspCoreReg, stPostLumaInten.u32);

	U_ISP_CORE_3DNR_POST_CHROMA_INTENSITY stPostChromaInten;
	stPostChromaInten.u32 = 0;
	stPostChromaInten.bits.core_3dnr_post_chroma_intensity = pst3DnrCtl->core_3dnr_post_chroma_intensity;
	ISP_CORE_DRV_SET_Core3DnrPostChromaIntensity(apstIspCoreReg, stPostChromaInten.u32);
	return 0;
}
/*
*ENH Control
*/
static int ISP_DRV_CORE_SetEnhLtmCtl(ISP_CORE_ENH_CTL_S *pstEnhCtl)
{
	ISP_CHECK_POINTER(pstEnhCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_ENH_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CoreEnhCtl(apstIspCoreReg);
	stCtl.bits.enh_ltm_en = pstEnhCtl->enh_ltm_en;
	stCtl.bits.enh_adp_ltm_en = pstEnhCtl->enh_adp_ltm_en;
	ISP_CORE_DRV_SET_CoreEnhCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_LTM_GAIN stLtmGain;
	stLtmGain.u32 = 0;
	stLtmGain.bits.ltm_gain = pstEnhCtl->ltm_gain;
	ISP_CORE_DRV_SET_CoreLtmGain(apstIspCoreReg, stLtmGain.u32);

	U_ISP_CORE_LTM_TH stLtmTh;
	stLtmTh.u32 = 0;
	stLtmTh.bits.ltm_th = pstEnhCtl->ltm_th;
	ISP_CORE_DRV_SET_CoreLtmTh(apstIspCoreReg, stLtmTh.u32);
	return 0;
}

static int ISP_DRV_CORE_SetEnhCCCtl(ISP_CORE_ENH_CTL_S *pstEnhCtl)
{
	ISP_CHECK_POINTER(pstEnhCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_ENH_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CoreEnhCtl(apstIspCoreReg);
	stCtl.bits.enh_cc_en = pstEnhCtl->enh_cc_en;
	stCtl.bits.enh_adp_cc_en = pstEnhCtl->enh_adp_cc_en;
	ISP_CORE_DRV_SET_CoreEnhCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_ENH_NR_TH stNrTh;
	stNrTh.u32 = 0;
	stNrTh.bits.enh_nr_th = pstEnhCtl->enh_nr_th;
	ISP_CORE_DRV_SET_CoreEnhNrTh(apstIspCoreReg, stNrTh.u32);

	U_ISP_CORE_ENH_TH1 stTh1;
	stTh1.u32 = 0;
	stTh1.bits.enh_th1 = pstEnhCtl->enh_th1;
	ISP_CORE_DRV_SET_CoreEnhTh1(apstIspCoreReg, stTh1.u32);

	U_ISP_CORE_ENH_TH2 stTh2;
	stTh2.u32 = 0;
	stTh2.bits.enh_th2 = pstEnhCtl->enh_th2;
	ISP_CORE_DRV_SET_CoreEnhTh2(apstIspCoreReg, stTh2.u32);
	return 0;
}

static int ISP_DRV_CORE_SetEnhSharpenCtl(ISP_CORE_ENH_CTL_S *pstEnhCtl)
{
	ISP_CHECK_POINTER(pstEnhCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_ENH_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CoreEnhCtl(apstIspCoreReg);
	stCtl.bits.enh_sharp_en = pstEnhCtl->enh_sharp_en;
	stCtl.bits.enh_adp_sharp_en = pstEnhCtl->enh_adp_sharp_en;
	ISP_CORE_DRV_SET_CoreEnhCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_SHARP_GAIN stSharpgain;
	stSharpgain.u32 = 0;
	stSharpgain.bits.sharp_gain = pstEnhCtl->sharp_gain;
	ISP_CORE_DRV_SET_CoreSharpGain(apstIspCoreReg, stSharpgain.u32);
	return 0;
}
/*
* POST Control 
*/
static int ISP_DRV_CORE_SetPostContCtl(ISP_CORE_POST_CTL_S *pstPostCtl)
{
	ISP_CHECK_POINTER(pstPostCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_POST_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CorePostCtl(apstIspCoreReg);
	stCtl.bits.post_cont_ad_en = pstPostCtl->post_cont_ad_en;
	ISP_CORE_DRV_SET_CorePostCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_CONT_GAIN stContGain;
	stContGain.u32 = 0;
	stContGain.bits.cont_ad_intensity = pstPostCtl->cont_ad_intensity;
	ISP_CORE_DRV_SET_CoreContGain(apstIspCoreReg, stContGain.u32);
	return 0;
}

static int ISP_DRV_CORE_SetPostLumaCtl(ISP_CORE_POST_CTL_S *pstPostCtl)
{
	ISP_CHECK_POINTER(pstPostCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_POST_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CorePostCtl(apstIspCoreReg);
	stCtl.bits.post_luma_ad_en = pstPostCtl->post_luma_ad_en;
	ISP_CORE_DRV_SET_CorePostCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_LUMA_GAIN stLumaTh;
	stLumaTh.u32 = 0;
	stLumaTh.bits.luma_ad_intensity = pstPostCtl->luma_ad_intensity;
	ISP_CORE_DRV_SET_CoreLumaGain(apstIspCoreReg, stLumaTh.u32);
	return 0;
}

static int ISP_DRV_CORE_SetPostSatuCtl(ISP_CORE_POST_CTL_S *pstPostCtl)
{
	ISP_CHECK_POINTER(pstPostCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_POST_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CorePostCtl(apstIspCoreReg);
	stCtl.bits.post_satu_ad_en = pstPostCtl->post_satu_ad_en;
	ISP_CORE_DRV_SET_CorePostCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_SATU_GAIN stSatuTh;
	stSatuTh.u32 = 0;
	stSatuTh.bits.satu_ad_intensity = pstPostCtl->satu_ad_intensity;
	ISP_CORE_DRV_SET_CoreSatuGain(apstIspCoreReg, stSatuTh.u32);
	return 0;
}
/*
* OTC 
*/
static int ISP_DRV_CORE_SetOtcCtl(ISP_CORE_OTC_CTL_S *pstOtcCtl)
{
	ISP_CHECK_POINTER(pstOtcCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_POST_CTL stCtl;
	stCtl.u32 = ISP_CORE_DRV_GET_CorePostCtl(apstIspCoreReg);
	stCtl.bits.post_otc_en = pstOtcCtl->post_otc_en;  
	stCtl.bits.otc_yc_sel = pstOtcCtl->otc_yc_sel;
	stCtl.bits.otc_uv_format_sel = pstOtcCtl->otc_uv_format_sel;
	stCtl.bits.otc_hsync_pol_sel = pstOtcCtl->otc_hsync_pol_sel;
	stCtl.bits.otc_vsync_pol_sel = pstOtcCtl->otc_vsync_pol_sel;
	ISP_CORE_DRV_SET_CorePostCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_OTC_STT_VR stOtcVr;
  	stOtcVr.u32 = 0;
  	stOtcVr.bits.otc_stt_vr = pstOtcCtl->otc_stt_vr;
  	ISP_CORE_DRV_SET_CoreOtcSttVr(apstIspCoreReg,stOtcVr.u32);

  	U_ISP_CORE_OTC_STT_HR stOtcHr;
  	stOtcHr.u32 = 0;
  	stOtcHr.bits.otc_stt_hr = pstOtcCtl->otc_stt_hr;
  	ISP_CORE_DRV_SET_CoreOtcSttHr(apstIspCoreReg, stOtcHr.u32);

  	U_ISP_CORE_OTC_HEIGHT stOtcHeight;
  	stOtcHeight.u32 = 0;
  	stOtcHeight.bits.otc_height = pstOtcCtl->otc_height;
  	ISP_CORE_DRV_SET_CoreOtcHeight(apstIspCoreReg,stOtcHeight.u32);

  	U_ISP_CORE_OTC_WIDTH  stOtcWidth;
  	stOtcWidth.u32 = 0;
  	stOtcWidth.bits.otc_width = pstOtcCtl->otc_width;
  	ISP_CORE_DRV_SET_CoreOtcWidth(apstIspCoreReg, stOtcWidth.u32);
	return 0;
}
/*
*LDC
*/
static int ISP_DRV_CORE_SetLdcCtl(ISP_CORE_LDC_CTL_S *pstLdcCtl)
{
	ISP_CHECK_POINTER(pstLdcCtl);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_LDC_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.ldc_en = pstLdcCtl->ldc_en;
	stCtl.bits.ldc_arith_en = pstLdcCtl->ldc_arith_en;
	ISP_CORE_DRV_SET_CoreLdcCtl(apstIspCoreReg, stCtl.u32);

	U_ISP_CORE_LDC_REQ_FREQ stReqFreq;
	stReqFreq.u32 = 0;
	stReqFreq.bits.ldc_req_freq = pstLdcCtl->ldc_req_freq;
	stReqFreq.bits.ldc_stt_ln = pstLdcCtl->ldc_stt_ln;
	ISP_CORE_DRV_SET_CoreLdcReqFreq(apstIspCoreReg, stReqFreq.u32);

	U_ISP_CORE_LDC_H_CENTER_POS stHCenterPos;
	stHCenterPos.u32 = 0;
	stHCenterPos.bits.ldc_h_center_pos = pstLdcCtl->ldc_h_center_pos;
	ISP_CORE_DRV_SET_CoreLdcHCenterPos(apstIspCoreReg, stHCenterPos.u32);

	U_ISP_CORE_LDC_V_CENTER_POS stVCenterPos;
	stVCenterPos.u32 = 0;
	stVCenterPos.bits.ldc_v_center_pos = pstLdcCtl->ldc_v_center_pos;
	ISP_CORE_DRV_SET_CoreLdcVCenterPos(apstIspCoreReg, stVCenterPos.u32);

	U_ISP_CORE_LDC_RECTIFY_CR stRecifyCr;
	stRecifyCr.u32 = 0;
	stRecifyCr.bits.ldc_rectify_cr = pstLdcCtl->ldc_rectify_cr;
	ISP_CORE_DRV_SET_CoreLdcRectifyCr(apstIspCoreReg, stRecifyCr.u32);

	U_ISP_CORE_LDC_RECTIFY_CZ stRecifyCz;
	stRecifyCz.u32 = 0;
	stRecifyCz.bits.ldc_rectify_cz = pstLdcCtl->ldc_rectify_cz;
	ISP_CORE_DRV_SET_CoreLdcRectifyCz(apstIspCoreReg, stRecifyCz.u32);
	return 0;
}
/*
* AF Statistics
*/
static int ISP_DRV_CORE_SetAfCtl(ISP_CORE_AF_CTL_S *pstAfCtl)
{
	ISP_CHECK_POINTER(pstAfCtl);
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_AF_CTL stAfCtl;
	stAfCtl.u32 = 0;
	stAfCtl.bits.af_stat_en = pstAfCtl->af_stat_en;
	stAfCtl.bits.af_stat_mode_sel = pstAfCtl->af_stat_mode_sel;
	ISP_CORE_DRV_SET_CoreAfCtl(apstIspCoreReg,stAfCtl.u32);

	U_ISP_CORE_AF_STAT_WIN_H_START stAfWinHStart;
	stAfWinHStart.u32 = 0;
	stAfWinHStart.bits.af_stat_win_h_start = pstAfCtl->af_stat_win_h_start;
	ISP_CORE_DRV_SET_CoreAfStatWinHStart(apstIspCoreReg,stAfWinHStart.u32);

	U_ISP_CORE_AF_STAT_WIN_V_START stAfWinVStart;
	stAfWinVStart.u32 = 0;
	stAfWinVStart.bits.af_stat_win_v_start = pstAfCtl->af_stat_win_v_start;
	ISP_CORE_DRV_SET_CoreAfStatWinVStart(apstIspCoreReg,stAfWinVStart.u32);

	U_ISP_CORE_AF_STAT_WIN_H_END stAfWinHEnd;
	stAfWinHEnd.u32 = 0;
	stAfWinHEnd.bits.af_stat_win_h_end = pstAfCtl->af_stat_win_h_end;	
	ISP_CORE_DRV_SET_CoreAfStatWinHEnd(apstIspCoreReg, stAfWinHEnd.u32);

	U_ISP_CORE_AF_STAT_WIN_V_END stAfWinVEnd;
	stAfWinVEnd.u32 = 0;
	stAfWinVEnd.bits.af_stat_win_v_end = pstAfCtl->af_stat_win_v_end;	
	ISP_CORE_DRV_SET_CoreAfStatWinVEnd(apstIspCoreReg, stAfWinVEnd.u32);

	return 0;
}	

int ISP_DRV_CORE_GetAfSts(ISP_CORE_AF_STS_S *pgtAfSts)
{
	ISP_CHECK_POINTER(pgtAfSts);

	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	U_ISP_CORE_AF_MID_FRQ_DATA         gtAfMidFrqData;
	gtAfMidFrqData.u32 = ISP_CORE_DRV_GET_CoreAfMidFrqData(apstIspCoreReg);
	pgtAfSts->af_mid_frq_data = gtAfMidFrqData.u32;

	U_ISP_CORE_AF_HIGH_FRQ_DATA        gtAfHighFrqData;
	gtAfHighFrqData.u32 = ISP_CORE_DRV_GET_CoreAfHighFrqData(apstIspCoreReg);
	pgtAfSts->af_high_frq_data = gtAfHighFrqData.u32;

	U_ISP_CORE_AF_STAT_PIXEL_NUM       gtAfStatPixelNum;
	gtAfStatPixelNum.u32 = ISP_CORE_DRV_GET_CoreAfStatPixelNum(apstIspCoreReg);	
	pgtAfSts->af_stat_pixel_num = gtAfStatPixelNum.u32;
	return 0;
}

int ISP_DRV_CORE_SetRamWrStatus(unsigned int data)
{
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	ISP_CORE_DRV_SET_CoreRamWrStatus(apstIspCoreReg,data);

	return 0;
}

int ISP_DRV_CORE_GetRamRdStatus(void)
{
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);
	printf("apstIspCoreReg = 0x%x\n",apstIspCoreReg);
	int isp_ram_ready = ISP_CORE_DRV_GET_CoreRamRdStatus(apstIspCoreReg);

	return isp_ram_ready;
}

int ISP_DRV_SetCore(ISP_CORE_ATRR_S *pstCoreAttr,SENSOR_TYPE sensor_type)
{
	ISP_CHECK_POINTER(pstCoreAttr);
	printf("ISP_DRV_SetCore start!\n");
	ISP_CORE_ITC_CTL_S *pstItcCtl = &pstCoreAttr->stItcCtl;
	ISP_DRV_CORE_SetItcCtl(pstItcCtl);

	ISP_CORE_IMAGE_ATTR_S *pstImgAttr = &pstCoreAttr->stImageAttr;
	ISP_DRV_CORE_SetImageAttr(pstImgAttr);

	ISP_CORE_TEST_CTL_S *pstTestCtl = &pstCoreAttr->stTestCtl;
	ISP_DRV_CORE_SetTestCtl(pstTestCtl);

	ISP_CORE_BLC_CTL_S *pstBlcCtl = &pstCoreAttr->stBlcCtl;
	ISP_DRV_CORE_SetBlcCtl(pstBlcCtl);

	ISP_CORE_LSC_CTL_S *pstLscCtl = &pstCoreAttr->stLscCtl;
	ISP_DRV_CORE_SetLscCtl(pstLscCtl);

	ISP_CORE_AE_CTL_S *pstAeCtl = &pstCoreAttr->stAeCtl;
	ISP_DRV_CORE_SetAeCtl(pstAeCtl);

	ISP_CORE_AWB_CTL_S *pstAwbCtl = &pstCoreAttr->stAwbCtl;
	ISP_DRV_CORE_SetAwbCtl(pstAwbCtl);

	ISP_CORE_CSC_CTL_S *pstCscCtl = &pstCoreAttr->stCscCtl;
	ISP_DRV_CORE_SetCscCtl(pstCscCtl);

	ISP_CORE_WDR_CTL_S *pstWdrCtl = &pstCoreAttr->stWdrCtl;
	ISP_DRV_CORE_SetWdrCtl(pstWdrCtl);

	ISP_CORE_ADA_CTL_S *pstAdaCtl  = &pstCoreAttr->stAdaCtl;
	ISP_DRV_CORE_SetAdaCtl(pstAdaCtl);

	ISP_CORE_RGBIR_CTL_S *pstRgbIrCtl = &pstCoreAttr->stRgbirCtl;
	ISP_DRV_CORE_SetRgbIrCtl(pstRgbIrCtl);

	ISP_CORE_2DNR_CTL_S *pst2DnrCtl = &pstCoreAttr->st2dnrCtl;
	ISP_DRV_CORE_Set2DnrCtl(pst2DnrCtl);

	ISP_CORE_3DNR_CTL_S *pst3DnrCtl = &pstCoreAttr->st3dnrCtl;
	ISP_DRV_CORE_Set3DnrCtl(pst3DnrCtl);

	ISP_CORE_ENH_CTL_S *pstEnhCtl = &pstCoreAttr->stEnhCtl;
	ISP_DRV_CORE_SetEnhLtmCtl(pstEnhCtl);
	ISP_DRV_CORE_SetEnhCCCtl(pstEnhCtl);
	ISP_DRV_CORE_SetEnhSharpenCtl(pstEnhCtl);	

	ISP_CORE_POST_CTL_S *pstPostCtl = &pstCoreAttr->stPostCtl;
	ISP_DRV_CORE_SetPostContCtl(pstPostCtl);
	ISP_DRV_CORE_SetPostLumaCtl(pstPostCtl);
	ISP_DRV_CORE_SetPostSatuCtl(pstPostCtl);

	ISP_CORE_OTC_CTL_S *pstOtcCtl = &pstCoreAttr->stOtcCtl;
	ISP_DRV_CORE_SetOtcCtl(pstOtcCtl);

	ISP_CORE_LDC_CTL_S *pstLdcCtl = &pstCoreAttr->stLdcCtl;
	ISP_DRV_CORE_SetLdcCtl(pstLdcCtl);

	ISP_CORE_AF_CTL_S *pstAfCtl = &pstCoreAttr->stAfCtl;
	ISP_DRV_CORE_SetAfCtl(pstAfCtl);
	printf("ISP_DRV_SetCore end!\n");
	return 0;
}

int ISP_DRV_GetCoreRegsVal(void)
{
	S_ISP_CORE_REGS_TYPE *apstIspCoreReg = NULL;
	ISP_2K_DRV_CORE_REG_CTX(apstIspCoreReg);

	ISP_CORE_DRV_GET_CoreRegsVal(apstIspCoreReg);

	return 0;
}

#if  0
/* 
*
*/
int ISP_DRV_SetCore(ISP_CORE_CONFIG_S *ispCoreInfo)
{
    ISP_CHECK_POINTER(ispCoreInfo);

	//ITC
    ISP_CORE_ITC_CTL_S pstItcCtl;
	ISP_ITC_CONFIG_S *itcInfo = &(ispCoreInfo->itcInfo);
    pstItcCtl.hsync_pol = 0;
    pstItcCtl.vsync_pol = 0;
    pstItcCtl.hsync_input_timing = 3;
    pstItcCtl.vsync_input_timing = 1;
    pstItcCtl.mirror_ctl = itcInfo->flip_ctl; //0
    pstItcCtl.video_format_ctl = itcInfo->video_fmt_sel;//0;
    ISP_DRV_CORE_SetItcCtl(&pstItcCtl);
	//IMAGE 
	ISP_CORE_IMAGE_ATTR_S pstImgAttr;
	pstImgAttr.image_width = itcInfo->total_img_size.Width -1 ;//InWidth - 1;
    pstImgAttr.image_height = itcInfo->total_img_size.Height - 1;//IntHeight - 1;
    pstImgAttr.image_v_start = itcInfo->itc_out_szie.Width_st;//0x2;
    pstImgAttr.image_h_start = itcInfo->itc_out_szie.Height_st;//0x3;
    pstImgAttr.image_active_width = itcInfo->itc_out_szie.Width;//OutWidth;
    pstImgAttr.image_active_height = itcInfo->itc_out_szie.Height;//OutHeight;
    ISP_DRV_CORE_SetImageAttr(&pstImgAttr);
	//TPG
	ISP_CORE_TEST_CTL_S pstTestCtl;
	ISP_TPG_CONFIG_S *tpgInfo = &(ispCoreInfo->tpgInfo);
	pstTestCtl.test_pattern_en = tpgInfo->tpg_en;
	if(1 == tpgInfo->tpg_en)
	{
		pstTestCtl.bayer_mode_sel = tpgInfo->bayer_mode_sel;//3;
		pstTestCtl.test_pattern_sel = tpgInfo->tpg_sel;
		pstTestCtl.motion_mode_sel = tpgInfo->motion_mode_sel;
		pstTestCtl.wdr_l_mul_data = tpgInfo->wdr_l_mul_data;
		pstTestCtl.wdr_m_mul_data = tpgInfo->wdr_m_mul_data;
		pstTestCtl.wdr_s_mul_data = tpgInfo->wdr_s_mul_data;
	}
    ISP_DRV_CORE_SetTestCtl(&pstTestCtl);
	//BLC
    ISP_CORE_BLC_CTL_S pstBlcCtl;
	ISP_BLC_CONFIG_S *blcInfo = &(ispCoreInfo->blcInfo);
    pstBlcCtl.blc_en = blcInfo->blc_en;//1;
	if( 1 == pstBlcCtl.blc_en)
	{
    	pstBlcCtl.blc_offset = blcInfo->blc_offset;//0;
    	pstBlcCtl.blc_ratio = blcInfo->blc_ratio;//0x100;
	}
    ISP_DRV_CORE_SetBlcCtl(&pstBlcCtl);
	//LSC
    ISP_CORE_LSC_CTL_S pstLscCtl;
	ISP_LSC_CONFIG_S *lscInfo = &(ispCoreInfo->lscInfo);
    pstLscCtl.lsc_en = lscInfo->lsc_en;//1;
	if( 1 == lscInfo->lsc_en)
	{
    	pstLscCtl.lsc_h_center = lscInfo->lsc_h_center;//0x3c0;
    	pstLscCtl.lsc_v_center = lscInfo->lsc_v_center;//0x21c;
    	pstLscCtl.lsc_red_ratio = lscInfo->lsc_r_ratio;//0x100;
    	pstLscCtl.lsc_green_ratio = lscInfo->lsc_g_ratio;//0x100;
    	pstLscCtl.lsc_blue_ratio = lscInfo->lsc_b_ratio;//0x100;
		if(RGBIR_SENSOR == ispCoreInfo->sensor_type)
		{
			pstLscCtl.lsc_ir_ratio = lscInfo->lsc_ir_ratio;
		}
	}
    ISP_DRV_CORE_SetLscCtl(&pstLscCtl);
	//AE
    ISP_CORE_AE_CTL_S pstAeCtl;
	ISP_AE_CONFIG_S	 *aeInfo = &(ispCoreInfo->adaInfo);
    pstAeCtl.ae_as_en = aeInfo->ae_as_en;//1;
    pstAeCtl.ae_ag_en = aeInfo->ae_ag_en;//1;
    pstAeCtl.ae_airis_en = aeInfo->ae_airis_en;//0;
    pstAeCtl.ae_enter_ls_sel = aeInfo->ae_enter_ls_sel;//1;
    pstAeCtl.ae_exit_ls_sel= aeInfo->ae_exit_ls_sel;//0;        
           

    pstAeCtl.ae_day_change_en = aeInfo->ae_day_change_en;//0;
    pstAeCtl.ae_day_change_sel = aeInfo->ae_day_change_sel;//0;
    
	pstAeCtl.ae_win_mode_sel = aeInfo->ae_win_mode_sel;//0;
    pstAeCtl.ae_back_light_mode_sel = aeInfo->ae_back_light_mode_sel;//1;	
    pstAeCtl.ae_win_h_start = aeInfo->ae_win_size.h_start;//0x1e0;
    pstAeCtl.ae_win_v_start = aeInfo->ae_win_size.v_start;//0x10e;
    pstAeCtl.ae_win_h_end = aeInfo->ae_win_size.h_end;//0x5a0;
    pstAeCtl.ae_win_v_end = aeInfo->ae_win_size.v_end;//0x32a;
    
    pstAeCtl.ae_tar_bright = aeInfo->ae_tar_bright;//0x50;
    pstAeCtl.ae_tar_bright_range = aeInfo->ae_tar_bright_range;//0x8;
    pstAeCtl.ae_l_ex_time = aeInfo->ae_l_ex_time;//0x100;
    pstAeCtl.ae_m_ex_time = aeInfo->ae_m_ex_time;//0x10;
    pstAeCtl.ae_s_ex_time = aeInfo->ae_s_ex_time;//0x1;
    
    pstAeCtl.ae_agc = aeInfo->ae_agc;//0x0;
    pstAeCtl.ae_ad_shuttle_freq = aeInfo->ae_ad_shuttle_freq;//0x1;
    pstAeCtl.ae_ad_gain_freq = aeInfo->ae_ad_gain_freq;//0;
    pstAeCtl.ae_adjust_step_max = aeInfo->ae_adjust_step_max;//0x11;
    pstAeCtl.ae_ex_value_max = aeInfo->ae_ex_value_max;//0x1000;
    pstAeCtl.ae_ex_value_mid = aeInfo->ae_ex_value_mid;//0x800;
    pstAeCtl.ae_ex_value_min = aeInfo->ae_ex_value_min;//0x100;
    pstAeCtl.ae_gain_value_max = aeInfo->ae_gain_value_max;//0x900;
    pstAeCtl.ae_gain_value_mid = aeInfo->ae_gain_value_mid;//0x200;
    pstAeCtl.ae_gain_value_min = aeInfo->ae_gain_value_min;//0x0;
    pstAeCtl.ae_dn_switch_ad_step_max = aeInfo->ae_dn_switch_ad_step_max;//0x200;
    pstAeCtl.ae_dn_switch_wait_time = aeInfo->ae_dn_switch_wait_time;//0xff;
    pstAeCtl.ape_max_diff = aeInfo->ape_max_diff;//0x0c;//0x80
    pstAeCtl.ape_drv_signal_max = aeInfo->ape_drv_signal_max;//0xf00;
    pstAeCtl.ape_coeff_distance = aeInfo->ape_coeff_distance;//0x0;
    pstAeCtl.ape_coeff_speed = aeInfo->ape_coeff_speed;//0x0;
    pstAeCtl.ape_coeff_acceleration = aeInfo->ape_coeff_acceleration;//0x0;
    pstAeCtl.ape_drv_manual_value = aeInfo->ape_drv_manual_value;//0xfff;
    pstAeCtl.ape_damp_manual_value = aeInfo->ape_damp_manual_value;//0x800;
    ISP_DRV_CORE_SetAeCtl(&pstAeCtl);
	//AWB
    ISP_CORE_AWB_CTL_S pstAwbCtl;
	ISP_AWB_CONFIG_S *awbInfo = &(ispCoreInfo->awbInfo);
    pstAwbCtl.awb_d65_en = awbInfo->awb_d65_en;//1;
    pstAwbCtl.awb_ccm_en = awbInfo->awb_ccm_en;//1;
    pstAwbCtl.awb_en = awbInfo->awb_en;//1;
    pstAwbCtl.awb_mode_sel = awbInfo->awb_mode_sel;//1;
    
    pstAwbCtl.awb_hist_mode_sel = awbInfo->awb_hist_mode_sel;//0;
    pstAwbCtl.awb_veri_en = awbInfo->awb_veri_en;//0;
    pstAwbCtl.awb_mode_sel = awbInfo->awb_mode_sel;//1;
    pstAwbCtl.awb_value_save_en = awbInfo->awb_value_save_en;//0;
    pstAwbCtl.awb_ccm_adp_adjust_en = awbInfo->awb_ccm_adp_adjust_en;//1;
    pstAwbCtl.awb_stab_en = awbInfo->awb_stab_en;//0;

    pstAwbCtl.awb_d65_red_gain = awbInfo->awb_d65_red_gain;//0x204;
    pstAwbCtl.awb_d65_blue_gain = awbInfo->awb_d65_blue_gain;//0x1e8;
    pstAwbCtl.ccm_rr_coff = awbInfo->ccm_coff[0][0];//0x160;
    pstAwbCtl.ccm_rg_coff = awbInfo->ccm_coff[0][1];//0x60;
    pstAwbCtl.ccm_rb_coff = awbInfo->ccm_coff[0][2];//0x04;
    pstAwbCtl.ccm_gr_coff = awbInfo->ccm_coff[1][0];//0x64;
    pstAwbCtl.ccm_gg_coff = awbInfo->ccm_coff[1][1];//0x1a0;
    pstAwbCtl.ccm_gb_coff = awbInfo->ccm_coff[1][2];//0x40;
    pstAwbCtl.ccm_br_coff = awbInfo->ccm_coff[2][0];//0x4;
    pstAwbCtl.ccm_bg_coff = awbInfo->ccm_coff[2][1];//0x40;
    pstAwbCtl.ccm_bb_coff = awbInfo->ccm_coff[2][2];//0x144;
    pstAwbCtl.ccm_correct_coff = awbInfo->ccm_coff;//0x104;
    pstAwbCtl.awb_win_h_start = awbInfo->awb_win_size.h_start;//0x0;
    pstAwbCtl.awb_win_v_start = awbInfo->awb_win_size.v_start;//0x0;
    pstAwbCtl.awb_win_h_end = awbInfo->awb_win_size.h_end;//0x77f;
    pstAwbCtl.awb_win_v_end = awbInfo->awb_win_size.v_end;//0x437;
    pstAwbCtl.awb_correct_diff_th = awbInfo->awb_correct_diff_th;//0x20;
    pstAwbCtl.awb_color_changeres_time = awbInfo->awb_color_changeres_time;//0x08;
    pstAwbCtl.awb_historgram_th = awbInfo->awb_historgram_th;//0x40;
    pstAwbCtl.awb_red_gain_adjust = awbInfo->awb_red_gain_adjust;//0x100;
    pstAwbCtl.awb_green_gain_adjust = awbInfo->awb_green_gain_adjust;//0x100;
    pstAwbCtl.awb_blue_gain_adjust = awbInfo->awb_blue_gain_adjust;//0x100;
    pstAwbCtl.awb_red_max_value = awbInfo->awb_red_max_value;//0x200;
    pstAwbCtl.awb_blue_max_value = awbInfo->awb_blue_max_value;//0x3ff;
    pstAwbCtl.awb_red_min_value = awbInfo->awb_red_min_value;//0x40;
    pstAwbCtl.awb_blue_min_value = awbInfo->awb_blue_min_value;//0x80;
    ISP_DRV_CORE_SetAwbCtl(&pstAwbCtl);
	//WDR
    ISP_CORE_WDR_CTL_S pstWdrCtl;
	ISP_WDR_CONFIG_S *wdrInfo = &(ispCoreInfo->wdrInfo);
    pstWdrCtl.wdr_fusion_en = wdrInfo->wdr_fusion_en;//0;
    pstWdrCtl.wdr_frame_sel = wdrInfo->wdr_frame_sel;//0;
    pstWdrCtl.wdr_adp_adjust_en = wdrInfo->wdr_adp_adjust_en;//0;
    pstWdrCtl.wdr_stab_en = wdrInfo->wdr_stab_en;//0;
    pstWdrCtl.wdr_en = wdrInfo->wdr_en;//0;
    pstWdrCtl.wdr_ghost_remove_en = wdrInfo->wdr_ghost_remove_en;//0;
    pstWdrCtl.wdr_mode_sel = wdrInfo->wdr_mode_sel;//0;
    pstWdrCtl.wdr_2frame_ex_ratio = wdrInfo->wdr_2frame_ex_ratio;//0;
    pstWdrCtl.wdr_3frame_ex_ratio = wdrInfo->wdr_3frame_ex_ratio;//0;
    pstWdrCtl.wdr_stat_img_sel = wdrInfo->wdr_stat_img_sel;//0;
    pstWdrCtl.wdr_over_ex_ratio_th1 = wdrInfo->wdr_over_ex_ratio_th1;//0x180;
    pstWdrCtl.wdr_over_ex_ratio_th2 = wdrInfo->wdr_over_ex_ratio_th2;//0x20;
    pstWdrCtl.wdr_fusion_ratio_th = wdrInfo->wdr_fusion_ratio_th;//0xc0;
    pstWdrCtl.wdr_fusion_value1 = wdrInfo->wdr_fusion_value1;//0x00;
    pstWdrCtl.wdr_fusion_value2 = wdrInfo->wdr_fusion_value2;//0xff;
    ISP_DRV_CORE_SetWdrCtl(&pstWdrCtl);
	//CSC
    ISP_CORE_CSC_CTL_S pstCscCtl;
	ISP_CSC_CONFIG_S *cscInfo = &(ispCoreInfo->cscInfo);
    pstCscCtl.csc_r2y_00 = cscInfo->csc_r2y[0][0];//0x99;
    pstCscCtl.csc_r2y_01 = cscInfo->csc_r2y[0][1];//0x13b;
    pstCscCtl.csc_r2y_02 = cscInfo->csc_r2y[0][2];//0x4b;
    pstCscCtl.csc_r2y_10 = cscInfo->csc_r2y[1][0];//0x12d;
    pstCscCtl.csc_r2y_11 = cscInfo->csc_r2y[1][1];//0x108;
    pstCscCtl.csc_r2y_12 = cscInfo->csc_r2y[1][2];//0x94;
    pstCscCtl.csc_r2y_20 = cscInfo->csc_r2y[2][0];//0x3a;
    pstCscCtl.csc_r2y_21 = cscInfo->csc_r2y[2][1];//0x33;
    pstCscCtl.csc_r2y_22 = cscInfo->csc_r2y[2][2];//0xdf;
    ISP_DRV_CORE_SetCscCtl(&pstCscCtl);
	//ADA
    ISP_CORE_ADA_CTL_S pstAdaCtl;
	ISP_ADA_CONFIG_S *adaInfo = &(ispCoreInfo->adaInfo);
    pstAdaCtl.ada_rgb_gamma_en = adaInfo->ada_rgb_gamma_en;//1;
    pstAdaCtl.ada_yuv_gamma_en = adaInfo->ada_yuv_gamma_en;//1;
    pstAdaCtl.ada_adjust_en = adaInfo->ada_adjust_en;//1;
    pstAdaCtl.ada_img_stab_en = adaInfo->ada_img_stab_en;//1;
    pstAdaCtl.ada_ccr_en = adaInfo->ada_ccr_en;//0;
    pstAdaCtl.ada_adp_en = adaInfo->ada_adp_en;//0;
    pstAdaCtl.ada_adp_ccr_en = adaInfo->ada_adp_ccr_en;//0;
 
    pstAdaCtl.ada_enh_mode_sel = adaInfo->ada_enh_mode_sel;//2;
    pstAdaCtl.ada_stat_max_value = adaInfo->ada_stat_max_value;//0x40;
    pstAdaCtl.ada_ad_stren_max_value = adaInfo->ada_ad_stren_max_value;//0x40;

    pstAdaCtl.ada_stat_mode_sel = adaInfo->ada_stat_mode_sel;//0;	
    pstAdaCtl.ada_win_h_start = adaInfo->ada_win_size.h_start;//0x0;
    pstAdaCtl.ada_win_v_start = adaInfo->ada_win_size.v_start;//0x0;
    pstAdaCtl.ada_win_h_end = adaInfo->ada_win_size.h_end;//0x77f;
    pstAdaCtl.ada_win_v_end = adaInfo->ada_win_size.v_end;//0x437;
    ISP_DRV_CORE_SetAdaCtl(&pstAdaCtl);
	//RGBIR
    ISP_CORE_RGBIR_CTL_S pstRgbIrCtl;
	ISP_RGBIR_CONFIG_S	*rgbirInfo = &(ispCoreInfo->rgbirInfo);
    pstRgbIrCtl.rgbir_en = rgbirInfo->rgbir_en;//0;
    pstRgbIrCtl.rgbir_rtf_en = rgbirInfo->rgbir_rtf_en;//0; 
    pstRgbIrCtl.rgbir_fusion_en = rgbirInfo->rgbir_fusion_en;//0;
    pstRgbIrCtl.rgbir_output_sel = rgbirInfo->rgbir_output_sel;//0;

    pstRgbIrCtl.rgbir_rpc_en = rgbirInfo->rgbir_rpc_en;//0;
    pstRgbIrCtl.rgbir_rpc_max_value = rgbirInfo->rgbir_rpc_max_value;//0x100;
    pstRgbIrCtl.rgbir_rpc_color_coff = rgbirInfo->rgbir_rpc_color_coff;//0x0;
    pstRgbIrCtl.rgbir_rpc_luma_coff = rgbirInfo->rgbir_rpc_luma_coff;//0x0;
    pstRgbIrCtl.rgbir_rpc_th = rgbirInfo->rgbir_rpc_th;//0x100;
    pstRgbIrCtl.rgbir_rpc_th1 = rgbirInfo->rgbir_rpc_th1;//0x100;
    ISP_DRV_CORE_SetRgbIrCtl(&pstRgbIrCtl);
	//2DNR
    ISP_CORE_2DNR_CTL_S pst2DnrCtl;
	ISP_NR2D_CONFIG_S *nr2dInfo = &(ispCoreInfo->nr2dInfo);
    pst2DnrCtl.core_2dnr_pcf_en = nr2dInfo->d2nr_pcf_en;//1;
    pst2DnrCtl.core_2dnr_raw_en = nr2dInfo->d2nr_raw_en;//1;
    pst2DnrCtl.core_2dnr_edge_en = nr2dInfo->d2nr_edge_en;//1;
    pst2DnrCtl.core_2dnr_bap_en = nr2dInfo->d2nr_bap_en;//1;
    
    pst2DnrCtl.core_2dnr_luma_en = nr2dInfo->d2nr_luma_en;//1;
    pst2DnrCtl.core_2dnr_chroma_en = nr2dInfo->d2nr_chroma_en;//1;
    pst2DnrCtl.core_2dnr_pcf_adp_en = nr2dInfo->d2nr_pcf_adp_en;//1;
    pst2DnrCtl.core_2dnr_raw_adp_en = nr2dInfo->d2nr_raw_adp_en;//1;
    
    pst2DnrCtl.core_2dnr_luma_adp_en = nr2dInfo->d2nr_luma_adp_en;//1;
    pst2DnrCtl.core_2dnr_chroma_adp_en = nr2dInfo->d2nr_chroma_adp_en;//1;
    
    pst2DnrCtl.core_2dnr_raw_intensity = nr2dInfo->d2nr_raw_intensity;//0x80;
    pst2DnrCtl.core_2dnr_bap_intensity = nr2dInfo->d2nr_bap_intensity;//0x1ff;
    pst2DnrCtl.core_2dnr_edge_intensity = nr2dInfo->d2nr_edge_intensity;//0x300;
    pst2DnrCtl.core_2dnr_luma_intensity = nr2dInfo->d2nr_luma_intensity;//0x80;
    pst2DnrCtl.core_2dnr_chroma_intensity = nr2dInfo->d2nr_chroma_intensity;//0x80;
    ISP_DRV_CORE_Set2DnrCtl(&pst2DnrCtl);
    //3DNR
    ISP_CORE_3DNR_CTL_S pst3DnrCtl;
	ISP_NR3D_CONFIG_S	*nr3dInfo = &(ispCoreInfo->nr3dInfo);
    pst3DnrCtl.core_3dnr_en = nr3dInfo->d3nr_en;//0;
    pst3DnrCtl.core_3dnr_pre_luma_en  = nr3dInfo->d3nr_pre_luma_en;//0;
    pst3DnrCtl.core_3dnr_pre_chroma_en = nr3dInfo->d3nr_pre_chroma_en;//0;
    pst3DnrCtl.core_3dnr_main_luma_en = nr3dInfo->d3nr_main_luma_en;//0;
    pst3DnrCtl.core_3dnr_main_chroma_en = nr3dInfo->d3nr_main_chroma_en;//0;
    pst3DnrCtl.core_3dnr_post_luma_en = nr3dInfo->d3nr_post_luma_en;//0;
    pst3DnrCtl.core_3dnr_post_chroma_en = nr3dInfo->d3nr_post_chroma_en;//0;
    pst3DnrCtl.core_3dnr_2d_luma_en = nr3dInfo->d3nr_2d_luma_en;//0;
    pst3DnrCtl.core_3dnr_2d_chroma_en = nr3dInfo->d3nr_2d_chroma_en;//0;
    pst3DnrCtl.core_3dnr_wb_en = nr3dInfo->d3nr_wb_en;//0;
    pst3DnrCtl.core_3dnr_wb_sel = nr3dInfo->d3nr_wb_sel;//0; 
    pst3DnrCtl.core_3dnr_adp_luma_en = nr3dInfo->d3nr_adp_luma_en;//0;
    pst3DnrCtl.core_3dnr_adp_chroma_en = nr3dInfo->d3nr_adp_chroma_en;//0;
    
    pst3DnrCtl.core_3dnr_pre_luma_th = nr3dInfo->d3nr_pre_luma_th;//0x40;      
    pst3DnrCtl.core_3dnr_pre_luma_intensity =nr3dInfo->d3nr_pre_luma_intensity;// 0x40;     
    pst3DnrCtl.core_3dnr_pre_chroma_intensity = nr3dInfo->d3nr_post_chroma_intensity;//0x20;
    pst3DnrCtl.core_3dnr_mid_filter_th = nr3dInfo->d3nr_mid_filter_th;//0x80;
    pst3DnrCtl.core_3dnr_pre_mid_filter_th = nr3dInfo->d3nr_pre_mid_filter_th;//0x8;  
    pst3DnrCtl.core_3dnr_cur_mid_filter_th = nr3dInfo->d3nr_cur_mid_filter_th;//0x80; 
    pst3DnrCtl.core_3dnr_low_pass_filter_th = nr3dInfo->d3nr_low_pass_filter_th;//0x80;
    pst3DnrCtl.core_3dnr_luma_th = nr3dInfo->d3nr_luma_th;//0x40;              
    pst3DnrCtl.core_3dnr_min_value = nr3dInfo->d3nr_min_value;//0x0;
    pst3DnrCtl.core_3dnr_luma_intensity = nr3dInfo->d3nr_luma_intensity;//0x80;
    pst3DnrCtl.core_3dnr_chroma_intensity = nr3dInfo->d3nr_chroma_intensity;//0x80;    
    pst3DnrCtl.core_3dnr_post_edge_th = nr3dInfo->d3nr_post_edge_th;//0x40;     
    pst3DnrCtl.core_3dnr_post_luma_intensity = nr3dInfo->d3nr_post_luma_intensity;//0x40;   
    pst3DnrCtl.core_3dnr_post_chroma_intensity = nr3dInfo->d3nr_post_chroma_intensity;//0x10;
    ISP_DRV_CORE_Set3DnrCtl(&pst3DnrCtl);
	//ENH
    ISP_CORE_ENH_CTL_S pstEnhCtl;
	ISP_ENH_CONFIG_S *enhInfo = &(ispCoreInfo->enhInfo);
    pstEnhCtl.enh_ltm_en = enhInfo->enh_ltm_en;//1;
    pstEnhCtl.enh_adp_ltm_en = enhInfo->enh_adp_ltm_en;//0;
    pstEnhCtl.ltm_gain = enhInfo->ltm_gain;//0xc0; 
    pstEnhCtl.ltm_th = enhInfo->ltm_th;//0x80;
	//
    pstEnhCtl.enh_cc_en = enhInfo->enh_cc_en;//0;
    pstEnhCtl.enh_adp_cc_en = enhInfo->enh_adp_cc_en;//1; 
	//
    pstEnhCtl.enh_sharp_en = enhInfo->enh_sharp_en;//1;	
    pstEnhCtl.enh_adp_sharp_en = enhInfo->enh_adp_sharp_en;//1;	
	if( 1 == pstEnhCtl.enh_sharp_en)
	{
    	pstEnhCtl.sharp_gain = enhInfo->sharp_gain;//0xc0;
	}
    pstEnhCtl.enh_nr_th = enhInfo->enh_nr_th;//0x08;	
    pstEnhCtl.enh_th1 = enhInfo->enh_th1;//0x80;
    pstEnhCtl.enh_th2 = enhInfo->enh_th2;//0x100;	
    ISP_DRV_CORE_SetEnhCtl(&pstEnhCtl);
	//POST CTL 
    ISP_CORE_POST_CTL_S pstPostCtl;
 	ISP_POST_CONFIG_S *postInfo = &(ispCoreInfo->postInfo);
    pstPostCtl.post_cont_ad_en = postInfo->post_cont_ad_en;//1; 
	if(	1 == pstPostCtl.post_cont_ad_en)  
	{
    	pstPostCtl.cont_ad_intensity = postInfo->cont_ad_intensity;//0x80;
	}
    pstPostCtl.post_luma_ad_en = postInfo->post_luma_ad_en;//1;
	if(	1 == pstPostCtl.post_luma_ad_en)  
	{
    	pstPostCtl.luma_ad_intensity = postInfo->luma_ad_intensity;//0x80;		
	}	   
    pstPostCtl.post_satu_ad_en = postInfo->post_satu_ad_en;//1; 
	if(	1 == pstPostCtl.satu_ad_intensity)  
	{
    	pstPostCtl.satu_ad_intensity = postInfo->satu_ad_intensity;//0x80;		
	}
    ISP_DRV_CORE_SetPostCtl(&pstPostCtl);
	//OTC
	ISP_CORE_OTC_CTL_S  pstOtcCtl;
	ISP_OTC_CONFIG_S	*otcInfo = &(ispCoreInfo->otcInfo);
	pstOtcCtl.post_otc_en = otcInfo->post_otc_en;
	if(1 == pstOtcCtl.post_otc_en)
	{
		pstOtcCtl.otc_width = otcInfo->otc_out_size.Width; 
		pstOtcCtl.otc_height = otcInfo->otc_out_size.Height;
		pstOtcCtl.otc_stt_hr = otcInfo->otc_out_size.Height_st;
		pstOtcCtl.otc_stt_vr = otcInfo->otc_out_size.Width_st;	
		pstOtcCtl.otc_yc_sel =otcInfo->otc_yc_sel;
		pstOtcCtl.otc_uv_format_sel =otcInfo->otc_uv_format_sel;	
		pstOtcCtl.otc_vsync_pol_sel = 0;
		pstOtcCtl.otc_hsync_pol_sel = 0;
    }		
	ISP_DRV_CORE_SetOtcCtl(&pstOtcCtl);
	//LDC
    ISP_CORE_LDC_CTL_S pstLdcCtl;
	ISP_LDC_CONFIG_S *ldcInfo = &(ispCoreInfo->ldcInfo);
	pstLdcCtl.ldc_en = ldcInfo->ldc_en;
	if( 1 == pstLdcCtl.ldc_en)
	{ 
		pstLdcCtl.ldc_arith_en=ldcInfo->ldc_arith_en;
		pstLdcCtl.ldc_h_center_pos=ldcInfo->ldc_h_center_pos;
		pstLdcCtl.ldc_v_center_pos=ldcInfo->ldc_v_center_pos;
		pstLdcCtl.ldc_stt_ln=ldcInfo->ldc_stt_ln;
		pstLdcCtl.ldc_req_freq=ldcInfo->ldc_req_freq;
		pstLdcCtl.ldc_rectify_cr=ldcInfo->ldc_rectify_cr;
		pstLdcCtl.ldc_rectify_cz=ldcInfo->ldc_rectify_cz;
	}
	ISP_DRV_CORE_SetLdcCtl(&pstLdcCtl);

	//AF
	ISP_CORE_AF_CTL_S  pstAfCtl;
	ISP_AF_CONFIG_S	*afInfo = &(ispCoreInfo->afInfo);
	pstAfCtl.af_stat_en = afInfo->af_stat_en;
	if(1 == pstAfCtl.af_stat_en)
	{ 
		pstAfCtl.af_stat_mode_sel =afInfo->af_stat_mode_sel;
		pstAfCtl.af_stat_win_h_start =afInfo->af_win_size.h_start;
		pstAfCtl.af_stat_win_h_end =afInfo->af_win_size.h_end;
		pstAfCtl.af_stat_win_v_start =afInfo->af_win_size.v_start;
		pstAfCtl.af_stat_win_v_end =afInfo->af_win_size.v_end;
	}
	ISP_DRV_CORE_SetAfCtpstAfCtll(&pstAfCtl);

    return 0;
}
#endif
