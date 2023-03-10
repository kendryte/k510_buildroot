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
#ifndef __MEDIACTL_H__
#define __MEDIACTL_H__

#ifdef __cplusplus
extern "C"{
#endif



enum  isp_pipeline_e
{
	ISP_F2K_PIPELINE,
	ISP_R2K_PIPELINE,
	ISP_TOF_PIPELINE
};

enum isp_modules
{
	ISP_TPG,
	ISP_BLC,
	ISP_LSC,
	ISP_AE,
	ISP_AWB,
	ISP_AWB_D65,
	ISP_AWB_CCM,
	ISP_WDR,
	ISP_RGB_GAMMA,
	ISP_YUV_GAMMA,
	ISP_ADA,
	ISP_ADA_SBZ,
	ISP_ADA_CCR,
	ISP_RGBIR,
	ISP_RAW_2DNR,
	ISP_YUV_Y_2DNR,
	ISP_YUV_UV_2DNR,
	ISP_3DNR,
	ISP_LTM,
	ISP_SHARP,
	ISP_CC,
	ISP_CTRST,
	ISP_LUMA,
	ISP_SATURATION,
	ISP_LDC,
	ISP_AF,
};

struct video_info
{
	unsigned int video_used;
	char *video_name[4];
	unsigned int enable[4];
	unsigned int video_width[4];
	unsigned int video_height[4];
	unsigned int video_out_format[4];
};

enum ae_select_e
{
	AE_SELECT_SW_MODE,
	AE_SELECT_HW_MODE,
};

enum adaptive_enable_select_e
{
	ADAPTIVE_SELECT_DISABLE,
	ADAPTIVE_SELECT_ENABLE,
};

enum ae_hist_mode_e
{
	AE_HIST_MODE_WHOLE_PICTURE,
	AE_HIST_MODE_CENTRAL_AERA,
};

typedef struct __AE_HIST_WINDOW_T
{
	int nHStart;
	int nVStart;
	int nHEnd;
	int nVEnd;
} AE_HIST_WINDOW_T;

enum isp_callback_id
{
    ISP_CALLBACK_ID_START = -1, // -1
    ISP_CALLBACK_ID_BLC, // 0
    ISP_CALLBACK_ID_LSC, // 1
    ISP_CALLBACK_ID_SHARPNESS, // 2
    ISP_CALLBACK_ID_LTM, // 3
    ISP_CALLBACK_ID_2DNR, // 4
    ISP_CALLBACK_ID_3DNR, // 5
    ISP_CALLBACK_ID_WDR, // 6
    ISP_CALLBACK_ID_CCM, // 7
    ISP_CALLBACK_ID_AWB, // 8
    ISP_CALLBACK_ID_GAMMA, // 9
    ISP_CALLBACK_ID_IRCUT, // 10
    ISP_CALLBACK_ID_SATURATION, // 11
    ISP_CALLBACK_ID_COLOR2BW, // 12
    ISP_CALLBACK_ID_ADA, // 13
    ISP_CALLBACK_ID_END, // 14
};

enum ir_cut_mode_e {
	USER_IR_CUT_NIGHT,
 	USER_IR_CUT_DAY,
};

/* user callback function */
typedef int (* __IspCallBack)(void *);

/* callback struct */
typedef struct __ISP_CB_T
{
    __IspCallBack pIspfunc; // callback function
    int nSize; // such as sizeof(CB_IR_CUT_T), depth copy need
    enum isp_callback_id nIcbId; // callback moudel id, adap need know which use it
} ISP_CB_T;

int mediactl_init(char *video_cfg_file,struct video_info *dev_info);
void mediactl_exit(void);
void mediactl_disable_ae(enum isp_pipeline_e pipeline);
int mediactl_rect(enum isp_pipeline_e pipeline, unsigned layer, unsigned area, unsigned x, unsigned y, unsigned width, unsigned height, unsigned line_width, unsigned color, unsigned border_mask);
int mediactl_set_ae(enum isp_pipeline_e pipeline);
int mediactl_set_ae_single(enum isp_pipeline_e pipeline);
int mediactl_set_ae_sync(enum isp_pipeline_e pipeline);
int mediactl_set_awb_sync(enum isp_pipeline_e pipeline);
int mediactl_sw_set_ae(enum isp_pipeline_e pipeline);
int mediactl_hw_set_ae(enum isp_pipeline_e pipeline);

int adaptive_enable(int scl);
int ae_select_init(int scl);
int anti_flicker_init(int scl);
int ae_enable_set(enum isp_pipeline_e pipeline, void * pipe);
/* AE HIST MODE API */
int ae_hist_mode_scl(enum isp_pipeline_e pipeline, enum ae_hist_mode_e ae_hist_mode, AE_HIST_WINDOW_T * hist_window);
/* attr page API */
int attr_page_params_setting(enum isp_pipeline_e pipeline, void * attr_page);
int attr_page_get_written_stat(enum isp_pipeline_e pipeline);
int isp_module_callback_register(ISP_CB_T * icb);
int isp_module_callback_ctl_stat(enum isp_pipeline_e pipeline, enum isp_callback_id cbid);
unsigned int mediactl_get_isp_modules(enum isp_pipeline_e pipeline,enum isp_modules module);
/* ir cut API */
int ir_cut_ev_get(enum isp_pipeline_e pipeline, enum ir_cut_mode_e ir_cut_mode);
int ir_cut_ev_set(enum isp_pipeline_e pipeline, enum ir_cut_mode_e ir_cut_mode, int level);
float ir_cut_hold_time_get(enum isp_pipeline_e pipeline, enum ir_cut_mode_e ir_cut_mode);
int ir_cut_hold_time_set(enum isp_pipeline_e pipeline, enum ir_cut_mode_e ir_cut_mode, float hold_time);

/* ae state get API */
int ae_y_average_get(enum isp_pipeline_e pipeline, unsigned int *value);

#ifdef __cplusplus
}
#endif
#endif /*__MEDIACTL_H__*/
