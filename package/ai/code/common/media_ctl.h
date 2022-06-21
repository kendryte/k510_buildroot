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

int mediactl_init(char *video_cfg_file,struct video_info *dev_info);
void mediactl_exit(void);
int mediactl_set_ae(enum isp_pipeline_e pipeline);
int mediactl_set_ae_single(enum isp_pipeline_e pipeline);
int mediactl_set_ae_sync(enum isp_pipeline_e pipeline);

unsigned int mediactl_get_isp_modules(enum isp_pipeline_e pipeline,enum isp_modules module);
#ifdef __cplusplus
} 
#endif
#endif /*__MEDIACTL_H__*/
