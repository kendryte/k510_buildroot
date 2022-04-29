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
 * isp_3d_core.c
 *
 * CANAAN ISP - 3d core module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_3d_core_drv.h"
#include "isp_3d_core_reg.h"

/*
*
*/
int TOF_Drv_Core_SetItcAttr(struct isp_device *isp,TOF_CORE_ITC_ATTR_S *pstItcAttr)
{
	ISP_CHECK_POINTER(isp);

	U_TOF_CORE_ITC_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_hsync_pol = pstItcAttr->hsync_pol;
	stData.bits.tof_vsync_pol = pstItcAttr->vsync_pol;
	stData.bits.tof_hsync_input_timing = pstItcAttr->hsync_input_timing;
	stData.bits.tof_vsync_input_timing = pstItcAttr->vsync_input_timing;
	stData.bits.tof_itc_sel = pstItcAttr->itc_sl;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_CTL);

	U_TOF_CORE_ITC_HEIGHT stHeight;
	stHeight.u32 = 0;
	stHeight.bits.tof_itc_height = pstItcAttr->tof_itc_height;
	isp_reg_writel(isp, stHeight.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_HEIGHT);

	U_TOF_CORE_ITC_WIDTH stWidth;
	stWidth.u32 = 0;
	stWidth.bits.tof_itc_width = pstItcAttr->tof_itc_width;
	isp_reg_writel(isp, stWidth.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_WIDTH);

	U_TOF_CORE_ITC_VSTART stVStart;
	stVStart.u32 = 0;
	stVStart.bits.tof_itc_vstart = pstItcAttr->tof_itc_v_start;
	isp_reg_writel(isp, stVStart.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_VSTART);

	U_TOF_CORE_ITC_HSTART stHStart;
	stHStart.u32 = 0;
	stHStart.bits.tof_itc_hstart = pstItcAttr->tof_itc_h_start;
	isp_reg_writel(isp, stHStart.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_HSTART);

	U_TOF_CORE_ITC_ACTIVE_WIDTH stActiveWidth;
	stActiveWidth.u32 = 0;
	stActiveWidth.bits.tof_itc_active_width = pstItcAttr->tof_itc_active_width;
	isp_reg_writel(isp, stActiveWidth.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_ACTIVE_WIDTH);

	U_TOF_CORE_ITC_ACTIVE_HEIGHT stActiveHeight;
	stActiveHeight.u32 = 0;
	stActiveHeight.bits.tof_itc_active_height = pstItcAttr->tof_itc_active_height;
	isp_reg_writel(isp, stActiveHeight.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_ACTIVE_HEIGHT);

	U_TOF_CORE_ITC_ACTIVE_START_LINE stActiveLine;
	stActiveLine.u32 = 0;
	stActiveLine.bits.tof_itc_active_start_line = pstItcAttr->tof_itc_active_start_line;
	isp_reg_writel(isp, stActiveLine.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_ITC_ACTIVE_START_LINE);

	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetSensorType(struct isp_device *isp,TOF_DRV_SENSOR_TYPE_E eSensorType)
{
	ISP_CHECK_POINTER(isp);
	if(eSensorType >= TOF_SENSOR_TYPE_BUTT)
	{
		TOF_PRINTF_FUNC("ISP Module: eSensorType = %d Unknow tof sensor type!\n",eSensorType);
		return -1;
	}

	U_TOF_CORE_SENSOR_SEL stData;
	stData.u32 = 0;
	stData.bits.tof_sensor_sel = eSensorType;
	isp_reg_writel(isp, stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_SENSOR_SEL);
	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetGenAttr(struct isp_device *isp,TOF_CORE_GEN_ATTR_S *pstGenAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstGenAttr);

	U_TOF_CORE_GEN_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_gray_sel = pstGenAttr->tof_gray_sel;
	stData.bits.tof_dm_sel = pstGenAttr->tof_dm_sel;
	stData.bits.tof_sensor_sel = pstGenAttr->tof_sensor_sel;
	stData.bits.tof_depth_pol_sel = pstGenAttr->tof_depth_pol_sel;
	stData.bits.tof_pwm_order_cfg = pstGenAttr->tof_pwm_order_cfg;
	stData.bits.tof_back_light_remove = 0;//1;
	stData.bits.tof_cwm_order_cfg = pstGenAttr->tof_cwm_order_cfg;

	isp_reg_writel(isp, stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_GEN_CTL);
	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetGrayThAttr(struct isp_device *isp,TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstGrayTHAttr);

	U_TOF_CORE_GRAY_TH stData;
	stData.u32 = 0;
	stData.bits.tof_gray_th = pstGrayTHAttr->tof_gray_th;
	isp_reg_writel(isp, stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_GRAY_TH);
	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetAECtl(struct isp_device *isp,TOF_CORE_AE_ATTR_S *pstAeAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstAeAttr);

	U_TOF_CORE_AE_CTL stAeAttr;
	stAeAttr.u32 = 0;
	stAeAttr.bits.tof_ae_as_en = pstAeAttr->ae_as_en;
	stAeAttr.bits.tof_ae_ag_en = pstAeAttr->ae_ag_en;
	stAeAttr.bits.tof_ae_airis_en = pstAeAttr->ae_airis_en;
	stAeAttr.bits.tof_ae_enter_lock_sel = pstAeAttr->ae_enter_lock_sel;
	stAeAttr.bits.tof_ae_exit_lock_sel = pstAeAttr->ae_exit_lock_sel;
	stAeAttr.bits.tof_ae_win_mode_sel = pstAeAttr->ae_win_mode_sel;
	stAeAttr.bits.tof_ae_back_light_mode_sel = pstAeAttr->ae_back_light_mode_sel;
	isp_reg_writel(isp, stAeAttr.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_CTL);

	U_TOF_CORE_AE_WIN_HSTART stHStart;
	stHStart.u32 = 0;
	stHStart.bits.tof_ae_win_hstart = pstAeAttr->ae_win_h_start;
	isp_reg_writel(isp, stHStart.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_WIN_HSTART);

	U_TOF_CORE_AE_WIN_VSTART stVStart;
	stVStart.u32 = 0;
	stVStart.bits.tof_ae_win_vstart = pstAeAttr->ae_win_v_start;
	isp_reg_writel(isp, stVStart.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_WIN_VSTART);

	U_TOF_CORE_AE_WIN_H_END stHEnd;
	stHEnd.u32 = 0;
	stHEnd.bits.tof_ae_win_h_end = pstAeAttr->ae_win_h_end;
	isp_reg_writel(isp, stHEnd.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_WIN_H_END);

	U_TOF_CORE_AE_WIN_V_END stVEnd;
	stVEnd.u32 = 0;
	stVEnd.bits.tof_ae_win_v_end = pstAeAttr->ae_win_v_end;
	isp_reg_writel(isp, stVEnd.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_WIN_V_END);

	U_TOF_CORE_AE_TAR_BRIGHT stTarBr;
	stTarBr.u32 = 0;
	stTarBr.bits.tof_ae_tar_bright = pstAeAttr->ae_tar_bright;
	isp_reg_writel(isp,stTarBr.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_TAR_BRIGHT);

	U_TOF_CORE_AE_TAR_BRIGHT_RANGE stTarBrRange;
	stTarBrRange.u32 = 0;
	stTarBrRange.bits.tof_ae_tar_bright_range = pstAeAttr->ae_tar_bright_range;
	isp_reg_writel(isp,stTarBrRange.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_TAR_BRIGHT_RANGE);

	U_TOF_CORE_AE_EX_TIME stExTime;
	stExTime.u32 = 0;
	stExTime.bits.tof_ae_ex_time = pstAeAttr->ae_ex_time;
	isp_reg_writel(isp,stExTime.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_EX_TIME);

	U_TOF_CORE_AE_AGC stAgc;
	stAgc.u32 = 0;
	stAgc.bits.tof_ae_agc = pstAeAttr->ae_agc;
	isp_reg_writel(isp,stAgc.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_AGC);

	U_TOF_CORE_AE_AD_FREQ stAdFreq;
	stAdFreq.u32 = 0;
	stAdFreq.bits.tof_ae_ad_freq = pstAeAttr->ae_ad_freq;
	isp_reg_writel(isp,stAdFreq.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_AD_FREQ);

	U_TOF_CORE_AE_AD_STEP_MAX stAdStepMax;
	stAdStepMax.u32 = 0;
	stAdStepMax.bits.tof_ae_ad_step_max = pstAeAttr->ae_ad_step_max;
	isp_reg_writel(isp,stAdStepMax.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_AD_STEP_MAX);

    U_TOF_CORE_AE_EX_VALUE_MAX stExValueMax;
	stExValueMax.u32 = 0;
	stExValueMax.bits.tof_ae_ex_value_max = pstAeAttr->ae_ex_value_max;
	isp_reg_writel(isp,stExValueMax.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_EX_VALUE_MAX);

	U_TOF_CORE_AE_EX_VALUE_MID stExValueMid;
	stExValueMid.u32 = 0;
	stExValueMid.bits.tof_ae_ex_value_mid = pstAeAttr->ae_ex_value_mid;
	isp_reg_writel(isp,stExValueMid.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_EX_VALUE_MID);

	U_TOF_CORE_AE_EX_VALUE_MIN stExValueMin;
	stExValueMin.u32 = 0;
	stExValueMin.bits.tof_ae_ex_value_min = pstAeAttr->ae_ex_value_min;
	isp_reg_writel(isp,stExValueMin.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_EX_VALUE_MIN);

    U_TOF_CORE_AE_GAIN_MAX stGainMax;
	stGainMax.u32 = 0;
	stGainMax.bits.tof_ae_gain_value_max = pstAeAttr->ae_gain_value_max;
	isp_reg_writel(isp,stGainMax.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_GAIN_MAX);

	U_TOF_CORE_AE_GAIN_MID stGainMid;
	stGainMid.u32 = 0;
	stGainMid.bits.tof_ae_gain_value_mid = pstAeAttr->ae_gain_value_mid;
	isp_reg_writel(isp,stGainMid.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_GAIN_MID);
	
	U_TOF_CORE_AE_GAIN_MIN stGainMin;
	stGainMin.u32 = 0;
	stGainMin.bits.tof_ae_gain_value_min = pstAeAttr->ae_gain_value_min;
	isp_reg_writel(isp,stGainMin.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_AE_GAIN_MIN);

	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetNr2dAttr(struct isp_device *isp,TOF_CORE_NR2D_ATTR_S *pstNr2dAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstNr2dAttr);

	U_TOF_CORE_2DNR_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_gray_dpc_en = pstNr2dAttr->tof_gray_dpc_en;
	stData.bits.tof_depth_dpc_en = pstNr2dAttr->tof_depth_dpc_en;
	stData.bits.tof_2dnr_gray_en = pstNr2dAttr->tof_2dnr_gray_en;
	stData.bits.tof_2dnr_depth_en = pstNr2dAttr->tof_2dnr_depth_en;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_2DNR_CTL);	
	
	U_TOF_CORE_2DNR_GRAY stGray;
	stGray.u32 = 0;
	stGray.bits.tof_2dnr_gray = pstNr2dAttr->tof_2dnr_gray;
	isp_reg_writel(isp,stGray.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_2DNR_GRAY);

	U_TOF_CORE_2DNR_DEPTH stDepth;
	stDepth.u32 = 0;
	stDepth.bits.tof_2dnr_depth = pstNr2dAttr->tof_2dnr_depth;
	isp_reg_writel(isp,stDepth.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_2DNR_DEPTH);

	return 0;
}
/*
*
*/
int TOF_Drv_Core_SetPostAttr(struct isp_device *isp,TOF_CORE_POST_ATTR_S *pstPostAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstPostAttr);

	U_TOF_CORE_POST_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_output_sel = pstPostAttr->tof_output_sel;
	stData.bits.tof_hsync_pol_sel = pstPostAttr->tof_hsync_pol_sel;
	stData.bits.tof_vsync_pol_sel = pstPostAttr->tof_vsync_pol_sel;
	stData.bits.tof_gray_gmma_en = pstPostAttr->tof_gray_gmma_en;
	stData.bits.tof_gray_cont_en = pstPostAttr->tof_gray_cont_en;
	stData.bits.tof_gray_luma_ad_en = pstPostAttr->tof_gray_luma_ad_en;
	stData.bits.tof_depth_cont_ad_en = pstPostAttr->tof_depth_cont_ad_en;//1;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_POST_CTL);

	U_TOF_CORE_CONT_GAIN stGrayCont;
	stGrayCont.u32 = 0;
	stGrayCont.bits.tof_cont_ad_intensity = pstPostAttr->tof_cont_ad_intensity;
	isp_reg_writel(isp, stGrayCont.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_CONT_GAIN);

	U_TOF_CORE_LUMA_GAIN stLumaCont;
	stLumaCont.u32 = 0;
	stLumaCont.bits.tof_luma_ad_intensity = pstPostAttr->tof_luma_ad_intensity;
	isp_reg_writel(isp,stLumaCont.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_LUMA_GAIN);

	U_TOF_CORE_SATU_GAIN stDepthCont;
	stDepthCont.u32 = 0;
	stDepthCont.bits.tof_satu_ad_intensity = pstPostAttr->tof_Depth_cont_ad_intensity;
	isp_reg_writel(isp,stDepthCont.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_SATU_GAIN);
	
	return 0;
}
/*
 *
 */
unsigned int TOF_Drv_Core_SetRamWrStatus(struct isp_device *isp)
{
	ISP_CHECK_POINTER(isp);

	U_TOF_CORE_RAM_WR_STATUS stData;
	stData.u32  = 0;
	stData.bits.gamma_grb_table_cfg = 1;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_CORE,TOF_CORE_RAM_WR_STATUS);

	return 0;
}
/*
 *
 */
unsigned int TOF_Drv_Core_FetRamRdStatus(struct isp_device *isp)
{
	ISP_CHECK_POINTER(isp);
	unsigned int udata;
//	U_TOF_CORE_RAM_WR_STATUS stData;
	udata = isp_reg_readl(isp,ISP_IOMEM_TOF_CORE,TOF_CORE_RAM_WR_STATUS);

	return udata;
}

