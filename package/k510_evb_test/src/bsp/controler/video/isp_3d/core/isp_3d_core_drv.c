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
#include "video/video_subsystem_addr.h"
//#include "video/isp_3d/isp_3d.h"
#include "video/isp_3d/core/isp_3d_core_reg.h"
#include "video/isp_3d/core/isp_3d_core_drv.h"

unsigned int *reg_tof_core_base;
#define TOF_DRV_CORE_REG_CTX(pstCtx)     pstCtx = (S_TOF_CORE_REGS_TYPE *)(reg_tof_core_base)
/*
*
*/
int TOF_DRV_Core_Remap(void)
{
	reg_tof_core_base = (unsigned int*)TOF_CORE_REG_BASE;

	return SUCCESS;
}
/*
*
*/
static int TOF_DRV_CORE_SetItcAttr(TOF_CORE_ITC_ATTR_S *pstItcAttr)
{
	TOF_CHECK_POINTER(pstItcAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_ITC_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_hsync_pol = pstItcAttr->hsync_pol;
	stData.bits.tof_vsync_pol = pstItcAttr->vsync_pol;
	stData.bits.tof_hsync_input_timing = pstItcAttr->hsync_input_timing;
	stData.bits.tof_vsync_input_timing = pstItcAttr->vsync_input_timing;
	stData.bits.tof_itc_sel = pstItcAttr->itc_sl;
	TOF_CORE_DRV_SET_CoreItcCtl(apstTofCoreReg, stData.u32);

	U_TOF_CORE_ITC_HEIGHT stHeight;
	stHeight.u32 = 0;
	stHeight.bits.tof_itc_height = pstItcAttr->tof_itc_height;
	TOF_CORE_DRV_SET_CoreItcHeight(apstTofCoreReg, stHeight.u32);

	U_TOF_CORE_ITC_WIDTH stWidth;
	stWidth.u32 = 0;
	stWidth.bits.tof_itc_width = pstItcAttr->tof_itc_width;
	TOF_CORE_DRV_SET_CoreItcWidth(apstTofCoreReg, stWidth.u32);

	U_TOF_CORE_ITC_VSTART stVStart;
	stVStart.u32 = 0;
	stVStart.bits.tof_itc_vstart = pstItcAttr->tof_itc_v_start;
	TOF_CORE_DRV_SET_CoreItcVStart(apstTofCoreReg, stVStart.u32);

	U_TOF_CORE_ITC_HSTART stHStart;
	stHStart.u32 = 0;
	stHStart.bits.tof_itc_hstart = pstItcAttr->tof_itc_h_start;
	TOF_CORE_DRV_SET_CoreItcHStart(apstTofCoreReg, stHStart.u32);

	U_TOF_CORE_ITC_ACTIVE_WIDTH stActiveWidth;
	stActiveWidth.u32 = 0;
	stActiveWidth.bits.tof_itc_active_width = pstItcAttr->tof_itc_active_width;
	TOF_CORE_DRV_SET_CoreItcActiveWidth(apstTofCoreReg, stActiveWidth.u32);

	U_TOF_CORE_ITC_ACTIVE_HEIGHT stActiveHeight;
	stActiveHeight.u32 = 0;
	stActiveHeight.bits.tof_itc_active_height = pstItcAttr->tof_itc_active_height;
	TOF_CORE_DRV_SET_CoreItcActiveHeight(apstTofCoreReg, stActiveHeight.u32);

	U_TOF_CORE_ITC_ACTIVE_START_LINE stActiveLine;
	stActiveLine.u32 = 0;
	stActiveLine.bits.tof_itc_active_start_line = pstItcAttr->tof_itc_active_start_line;
	TOF_CORE_DRV_SET_CoreItcActiveStartLine(apstTofCoreReg, stActiveLine.u32);

	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetSensorType( TOF_DRV_SENSOR_TYPE_E eSensorType )
{
	if(eSensorType >= TOF_SENSOR_TYPE_BUTT)
	{
		TOF_PRINTF_FUNC("ISP Module: eSensorType = %d Unknow tof sensor type!\n",eSensorType);
		return -1;
	}

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_SENSOR_SEL stData;
	stData.u32 = 0;
	stData.bits.tof_sensor_sel = eSensorType;
	TOF_CORE_DRV_SET_CoreSensorSel(apstTofCoreReg, stData.u32);
	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetGenAttr(TOF_CORE_GEN_ATTR_S *pstGenAttr)
{
	TOF_CHECK_POINTER(pstGenAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_GEN_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_gray_sel = pstGenAttr->tof_gray_sel;
	stData.bits.tof_dm_sel = pstGenAttr->tof_dm_sel;
	stData.bits.tof_sensor_sel = pstGenAttr->tof_sensor_sel;
	stData.bits.tof_depth_pol_sel = pstGenAttr->tof_depth_pol_sel;
	stData.bits.tof_pwm_order_cfg = pstGenAttr->tof_pwm_order_cfg;
	stData.bits.tof_back_light_remove = 0;//1;
	stData.bits.tof_cwm_order_cfg = pstGenAttr->tof_cwm_order_cfg;

	TOF_CORE_DRV_SET_CoreGenCtl(apstTofCoreReg, stData.u32);
	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetGrayThAttr(TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr)
{
	TOF_CHECK_POINTER(pstGrayTHAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_GRAY_TH stData;
	stData.u32 = 0;
	stData.bits.tof_gray_th = pstGrayTHAttr->tof_gray_th;
	TOF_CORE_DRV_SET_CoreGrayTHCtl(apstTofCoreReg, stData.u32);
	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetAECtl(TOF_CORE_AE_ATTR_S *pstAeAttr)
{
	TOF_CHECK_POINTER(pstAeAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_AE_CTL stAeAttr;
	stAeAttr.u32 = 0;
	stAeAttr.bits.tof_ae_as_en = pstAeAttr->ae_as_en;
	stAeAttr.bits.tof_ae_ag_en = pstAeAttr->ae_ag_en;
	stAeAttr.bits.tof_ae_airis_en = pstAeAttr->ae_airis_en;
	stAeAttr.bits.tof_ae_enter_lock_sel = pstAeAttr->ae_enter_lock_sel;
	stAeAttr.bits.tof_ae_exit_lock_sel = pstAeAttr->ae_exit_lock_sel;
	stAeAttr.bits.tof_ae_win_mode_sel = pstAeAttr->ae_win_mode_sel;
	stAeAttr.bits.tof_ae_back_light_mode_sel = pstAeAttr->ae_back_light_mode_sel;
	TOF_CORE_DRV_SET_CoreAeCtl(apstTofCoreReg, stAeAttr.u32);

	U_TOF_CORE_AE_WIN_HSTART stHStart;
	stHStart.u32 = 0;
	stHStart.bits.tof_ae_win_hstart = pstAeAttr->ae_win_h_start;
	TOF_CORE_DRV_SET_CoreAeWinHStart(apstTofCoreReg, stHStart.u32);

	U_TOF_CORE_AE_WIN_VSTART stVStart;
	stVStart.u32 = 0;
	stVStart.bits.tof_ae_win_vstart = pstAeAttr->ae_win_v_start;
	TOF_CORE_DRV_SET_CoreAeWinVStart(apstTofCoreReg, stVStart.u32);

	U_TOF_CORE_AE_WIN_H_END stHEnd;
	stHEnd.u32 = 0;
	stHEnd.bits.tof_ae_win_h_end = pstAeAttr->ae_win_h_end;
	TOF_CORE_DRV_SET_CoreAeWinHEnd(apstTofCoreReg, stHEnd.u32);

	U_TOF_CORE_AE_WIN_V_END stVEnd;
	stVEnd.u32 = 0;
	stVEnd.bits.tof_ae_win_v_end = pstAeAttr->ae_win_v_end;
	TOF_CORE_DRV_SET_CoreAeWinVEnd(apstTofCoreReg, stVEnd.u32);

	U_TOF_CORE_AE_TAR_BRIGHT stTarBr;
	stTarBr.u32 = 0;
	stTarBr.bits.tof_ae_tar_bright = pstAeAttr->ae_tar_bright;
	TOF_CORE_DRV_SET_CoreAeTarBright(apstTofCoreReg, stTarBr.u32);

	U_TOF_CORE_AE_TAR_BRIGHT_RANGE stTarBrRange;
	stTarBrRange.u32 = 0;
	stTarBrRange.bits.tof_ae_tar_bright_range = pstAeAttr->ae_tar_bright_range;
	TOF_CORE_DRV_SET_CoreAeTarBrightRange(apstTofCoreReg, stTarBrRange.u32);

	U_TOF_CORE_AE_EX_TIME stExTime;
	stExTime.u32 = 0;
	stExTime.bits.tof_ae_ex_time = pstAeAttr->ae_ex_time;
	TOF_CORE_DRV_SET_CoreAeExTime(apstTofCoreReg, stExTime.u32);

	U_TOF_CORE_AE_AGC stAgc;
	stAgc.u32 = 0;
	stAgc.bits.tof_ae_agc = pstAeAttr->ae_agc;
	TOF_CORE_DRV_SET_CoreAeAgc(apstTofCoreReg, stAgc.u32);

	U_TOF_CORE_AE_AD_FREQ stAdFreq;
	stAdFreq.u32 = 0;
	stAdFreq.bits.tof_ae_ad_freq = pstAeAttr->ae_ad_freq;
	TOF_CORE_DRV_SET_CoreAeAdFreq(apstTofCoreReg, stAdFreq.u32);

	U_TOF_CORE_AE_AD_STEP_MAX stAdStepMax;
	stAdStepMax.u32 = 0;
	stAdStepMax.bits.tof_ae_ad_step_max = pstAeAttr->ae_ad_step_max;
	TOF_CORE_DRV_SET_CoreAeAdStepMax(apstTofCoreReg, stAdStepMax.u32);

    U_TOF_CORE_AE_EX_VALUE_MAX stExValueMax;
	stExValueMax.u32 = 0;
	stExValueMax.bits.tof_ae_ex_value_max = pstAeAttr->ae_ex_value_max;
	TOF_CORE_DRV_SET_CoreAeExValueMax(apstTofCoreReg, stExValueMax.u32);

	U_TOF_CORE_AE_EX_VALUE_MID stExValueMid;
	stExValueMid.u32 = 0;
	stExValueMid.bits.tof_ae_ex_value_mid = pstAeAttr->ae_ex_value_mid;
	TOF_CORE_DRV_SET_CoreAeExValueMid(apstTofCoreReg, stExValueMid.u32);

	U_TOF_CORE_AE_EX_VALUE_MIN stExValueMin;
	stExValueMin.u32 = 0;
	stExValueMin.bits.tof_ae_ex_value_min = pstAeAttr->ae_ex_value_min;
	TOF_CORE_DRV_SET_CoreAeExValueMin(apstTofCoreReg, stExValueMin.u32);

    U_TOF_CORE_AE_GAIN_MAX stGainMax;
	stGainMax.u32 = 0;
	stGainMax.bits.tof_ae_gain_value_max = pstAeAttr->ae_gain_value_max;
	TOF_CORE_DRV_SET_CoreAeGainMax(apstTofCoreReg, stGainMax.u32);

	U_TOF_CORE_AE_GAIN_MID stGainMid;
	stGainMid.u32 = 0;
	stGainMid.bits.tof_ae_gain_value_mid = pstAeAttr->ae_gain_value_mid;
	TOF_CORE_DRV_SET_CoreAeGainMid(apstTofCoreReg, stGainMid.u32);
	
	U_TOF_CORE_AE_GAIN_MIN stGainMin;
	stGainMin.u32 = 0;
	stGainMin.bits.tof_ae_gain_value_min = pstAeAttr->ae_gain_value_min;
	TOF_CORE_DRV_SET_CoreAeGainMin(apstTofCoreReg, stGainMin.u32);

	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetNr2dAttr(TOF_CORE_NR2D_ATTR_S *pstNr2dAttr)
{
	TOF_CHECK_POINTER(pstNr2dAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_2DNR_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_gray_dpc_en = pstNr2dAttr->tof_gray_dpc_en;
	stData.bits.tof_depth_dpc_en = pstNr2dAttr->tof_depth_dpc_en;
	stData.bits.tof_2dnr_gray_en = pstNr2dAttr->tof_2dnr_gray_en;
	stData.bits.tof_2dnr_depth_en = pstNr2dAttr->tof_2dnr_depth_en;
	TOF_CORE_DRV_SET_Core2DnrCtl(apstTofCoreReg, stData.u32);	
	
	U_TOF_CORE_2DNR_GRAY stGray;
	stGray.u32 = 0;
	stGray.bits.tof_2dnr_gray = pstNr2dAttr->tof_2dnr_gray;
	TOF_CORE_DRV_SET_Core2DnrGray(apstTofCoreReg, stGray.u32);

	U_TOF_CORE_2DNR_DEPTH stDepth;
	stDepth.u32 = 0;
	stDepth.bits.tof_2dnr_depth = pstNr2dAttr->tof_2dnr_depth;
	TOF_CORE_DRV_SET_Core2DnrDepth(apstTofCoreReg, stDepth.u32);

	return 0;
}
/*
*
*/
static int TOF_DRV_CORE_SetPostAttr(TOF_CORE_POST_ATTR_S *pstPostAttr)
{
	TOF_CHECK_POINTER(pstPostAttr);

	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_POST_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_output_sel = pstPostAttr->tof_output_sel;
	stData.bits.tof_hsync_pol_sel = pstPostAttr->tof_hsync_pol_sel;
	stData.bits.tof_vsync_pol_sel = pstPostAttr->tof_vsync_pol_sel;
	stData.bits.tof_gray_gmma_en = pstPostAttr->tof_gray_gmma_en;
	stData.bits.tof_gray_cont_en = pstPostAttr->tof_gray_cont_en;
	stData.bits.tof_gray_luma_ad_en = pstPostAttr->tof_gray_luma_ad_en;
	stData.bits.tof_depth_cont_ad_en = pstPostAttr->tof_depth_cont_ad_en;//1;
	TOF_CORE_DRV_SET_CorePostCtl(apstTofCoreReg, stData.u32);

	U_TOF_CORE_CONT_GAIN stGrayCont;
	stGrayCont.u32 = 0;
	stGrayCont.bits.tof_cont_ad_intensity = pstPostAttr->tof_cont_ad_intensity;
	TOF_CORE_DRV_SET_CoreContGain(apstTofCoreReg, stGrayCont.u32);

	U_TOF_CORE_LUMA_GAIN stLumaCont;
	stLumaCont.u32 = 0;
	stLumaCont.bits.tof_luma_ad_intensity = pstPostAttr->tof_luma_ad_intensity;
	TOF_CORE_DRV_SET_CoreLumaGain(apstTofCoreReg, stLumaCont.u32);

	U_TOF_CORE_SATU_GAIN stDepthCont;
	stDepthCont.u32 = 0;
	stDepthCont.bits.tof_satu_ad_intensity = pstPostAttr->tof_Depth_cont_ad_intensity;
	TOF_CORE_DRV_SET_CoreSatuGain(apstTofCoreReg, stDepthCont.u32);
	
	return 0;
}
/*
 *
 */
int TOF_DRV_CORE_SetRamWrStatus(unsigned int data)
{
	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	U_TOF_CORE_RAM_WR_READY udata;
	udata.u32 = 0;
	udata.bits.gamma_grb_table_cfg = data;//1;
	TOF_CORE_DRV_SET_CoreRamWrStatus(apstTofCoreReg,udata.u32);

	return 0;
}
/*
 *
 */
unsigned int TOF_DRV_CORE_GetRamRdDone(void)
{
	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);	

	unsigned int udata = 0;
	udata = TOF_CORE_DRV_GET_CoreRamRdDone(apstTofCoreReg);

	return udata;
}
/*
 *
 */
int TOF_DRV_setCore(TOF_CORE_ATTR_S *tofCoreAttr)
{
	TOF_CHECK_POINTER(tofCoreAttr);

	TOF_CORE_ITC_ATTR_S *pstItcAttr =&tofCoreAttr->stItcAttr;
	TOF_DRV_CORE_SetItcAttr(pstItcAttr);

	TOF_DRV_SENSOR_TYPE_E eSensorType = tofCoreAttr->eSensorType;
	TOF_DRV_CORE_SetSensorType( eSensorType );

	TOF_CORE_GEN_ATTR_S *pstGenAttr =&tofCoreAttr->stGenAttr;
	TOF_DRV_CORE_SetGenAttr(pstGenAttr);

	TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr = &tofCoreAttr->stGrayTHAttr;
	TOF_DRV_CORE_SetGrayThAttr(pstGrayTHAttr);

	TOF_CORE_AE_ATTR_S *pstAeAttr =&tofCoreAttr->stAeAttr;
	TOF_DRV_CORE_SetAECtl(pstAeAttr);

	TOF_CORE_NR2D_ATTR_S *pstNr2dAttr = &tofCoreAttr->stNr2dAttr;
	TOF_DRV_CORE_SetNr2dAttr(pstNr2dAttr);

	TOF_CORE_POST_ATTR_S *pstPostAttr =&tofCoreAttr->stPostAttr;
	TOF_DRV_CORE_SetPostAttr(pstPostAttr);
	return 0;
}
/*
*DEBUG
*/
int TOF_DRV_GetCoreRegsVal(void)
{
	S_TOF_CORE_REGS_TYPE *apstTofCoreReg = NULL;
	TOF_DRV_CORE_REG_CTX(apstTofCoreReg);

	TOF_CORE_DRV_GET_CoreRegsVal(apstTofCoreReg);

	return 0;
}
