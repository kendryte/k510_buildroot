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
/******************************************************************************
  File Name     : isp_fbc.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _FBC_H_
#define _FBC_H_

#include "isp_com.h"
#include "isp_fbc/wrap/fbc_wrap_drv.h"
#include "isp_fbc/core/fbc_core_drv.h"

struct isp_device;

#define FBC_CHECK_POINTER(ptr)\
    do {\
        if (NULL == ptr)\
        {\
            printf("MFBC Module: Null Pointer!\n");\
            return -1;\
        }\
    }while(0);

typedef struct _FBC_WRAP_INT_MASK_INFO_S
{
    unsigned int ydonemask;
    unsigned int uvdonemask;
    unsigned int headdonemask;
}FBC_WRAP_INT_MASK_INFO_S;

typedef struct _FBC_WRAP_INFO_S
{
    unsigned int FBC_chl_sel;
    FBC_WRAP_INT_MASK_INFO_S stIntMask;
}FBC_WRAP_INFO_S;
/*
*
*/
typedef struct _FBC_CORE_Y_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_Y_BUF_INFO_S;

typedef struct _FBC_CORE_Y_HEAD_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_Y_HEAD_BUF_INFO_S;

typedef struct _FBC_CORE_UV_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_UV_BUF_INFO_S;

typedef struct _FBC_CORE_UV_HEAD_BUF_INFO_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_UV_HEAD_BUF_INFO_S;

typedef struct _FBC_CORE_BUF_INFO_S
{
    FBC_CORE_Y_BUF_INFO_S          stYBufInfo;
    FBC_CORE_Y_HEAD_BUF_INFO_S     stYHeadBufInfo;
    FBC_CORE_UV_BUF_INFO_S         stUVBufInfo;
    FBC_CORE_UV_HEAD_BUF_INFO_S    stUVHeadBufInfo;
}FBC_CORE_BUF_INFO_S;

typedef struct _FBC_CORE_SIZE_INFO_S
{
    unsigned int                input_width;
    unsigned int                input_height;
}FBC_CORE_SIZE_INFO_S;

typedef struct _FBC_CORE_INFO_S
{
    unsigned char           yuv420_en;
    FBC_CORE_SIZE_INFO_S   stSizeInfo;     
    FBC_CORE_BUF_INFO_S    stBufInfo;
}FBC_CORE_INFO_S;
//
typedef struct _FBC_CTL_INFO_S
{
	unsigned int yuv420_en;
	unsigned int width;
	unsigned int height;
}FBC_CTL_INFO_S;

//
/* Sink and source MFBC pads */
#define FBC_PAD_SINK			0
#define FBC_PAD_SOURCE_MEM		1
#define FBC_PADS_NUM			2

#define ISP_FBC_NEVENTS  3

enum isp_fbc_input_entity {
	FBC_INPUT_NONE,
	FBC_INPUT_F4k,
    FBC_INPUT_F2k,
    FBC_INPUT_R2k,
};

enum isp_fbc_output_entity {
	FBC_OUTPUT_NONE,
	FBC_OUTPUT_MEM,
};
#ifdef _USE_V4L2
struct isp_fbc_fpc {
	void *addr;
	dma_addr_t dma;
	unsigned int fpnum;
};
#endif
struct isp_fbc_device {
    struct isp_device *isp;
#ifdef _USE_V4L2
	struct v4l2_device v4l2_dev;
	struct v4l2_async_notifier notifier;
	struct media_device media_dev;
	struct device *dev;
    unsigned int update;
    unsigned int shadow_update;

    struct isp_fbc_fpc fpc;
    struct isp_video video_out;

	enum isp_pipeline_stream_state state;
	spinlock_t lock;
	wait_queue_head_t wait;
	unsigned int stopping;
	bool running;
	struct mutex ioctl_lock;
#endif

};
/*
*
*/
#ifdef _USE_V4L2
int canaanisp_fbc_init(struct isp_device *isp);
void canaanisp_fbc_cleanup(struct isp_device *isp);
int canaanisp_fbc_register_entities(struct isp_fbc_device *isp_fbc,
	struct v4l2_device *vdev);
void canaanisp_fbc_unregister_entities(struct isp_fbc_device *isp_fbc);
#endif
#endif /*_FBC_H_*/
