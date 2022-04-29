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
 * isp_r2k.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _ISP_R2K_H_
#define _ISP_R2K_H_

#ifdef _USE_V4L2
#include <linux/videodev2.h>
#endif

#include "isp_2k/isp.h"

#ifdef __cplusplus
extern "C" {
#endif

struct isp_device;

#define R2K_MIN_WIDTH		32
#define R2K_MIN_HEIGHT		32

/* Sink and source isp R2K pads */
#define ISP_R2K_PAD_SINK			0
#define ISP_R2K_PAD_MAIN_SOURCE		1
#define ISP_R2K_PAD_DS0_SOURCE		2
#define ISP_R2K_PAD_DS1_SOURCE		3
#define ISP_R2K_PAD_DS2_SOURCE		4
#define ISP_R2K_PADS_NUM			5

#define	ISP_R2K_NEVENTS				16

/* isp_r2k input media entity */
enum isp_r2k_input_entity {
	ISP_R2K_INPUT_NONE,
	ISP_R2K_INPUT_VI,
	ISP_R2K_INPUT_MEMORY,
};

/* isp_R2K output media entity */
enum isp_r2k_output_entity {
	ISP_R2K_OUTPUT_NONE,
	ISP_R2K_OUTPUT_FBC,
	ISP_R2K_OUTPUT_MEMORY,
};

#if 0
/*r2k device*/
struct isp_r2k_device{
	struct isp_device *isp;
#ifdef _USE_V4L2
	struct v4l2_subdev subdev;
	struct v4l2_mbus_framefmt formats[ISP_R2K_PADS_NUM];
	struct media_pad pads[ISP_R2K_PADS_NUM];

	enum isp_r2k_input_entity input;
	struct isp_video video_in;
	struct isp_video video_out;
	spinlock_t lock;
	wait_queue_head_t wait;
	struct mutex ioctl_lock;
#endif

	struct _ISP_WRAP_CFG_INFO *isp_wrap_cfg;
	struct _ISP_CORE_CFG_INFO *isp_core_cfg;
	struct _ISP_DS_CFG_INFO	  *isp_ds_cfg;
};
#endif
#ifdef _USE_V4L2
/* Function declarations */
int  isp_r2k_init(struct isp_device *isp);
void isp_r2k_cleanup(struct isp_device *isp);
int  isp_r2k_register_entities(struct isp_r2k_device *r2k,
			struct v4l2_device *vdev);
void isp_r2k_unregister_entities(struct isp_r2k_device *r2k);
void isp_r2k_isr(struct isp_r2k_device *r2k);
#endif


#ifdef __cplusplus
}
#endif

#endif /*_ISP_R2K_H_*/