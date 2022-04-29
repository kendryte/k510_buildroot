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
 * isp_3dnr_fbd_drv.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _ISP_3DNR_FBD_DRV_H_
#define _ISP_3DNR_FBD_DRV_H_

#include "isp_3dnr_fbd_reg.h"

typedef struct _ISP_FBD_CTL_S
{
    unsigned int  fbd_en;
    unsigned int  fbd_format_cfg;
}ISP_FBD_CTL_S;

typedef struct _ISP_FBD_SIZE_S
{
	unsigned int fbd_input_height;
	unsigned int fbd_input_width;
}ISP_FBD_SIZE_S;

typedef struct _ISP_FBD_Y_BUF_S
{
	unsigned int fbd_y_data_buf_base0;
	unsigned int fbd_y_data_buf_base1;
	unsigned int fbd_y_data_stride;
	unsigned int fbd_y_head_buf_base0;
	unsigned int fbd_y_head_buf_base1;
	unsigned int fbd_y_head_stride;
}ISP_FBD_Y_BUF_S;

typedef struct _ISP_FBD_UV_BUF_S
{
	unsigned int fbd_uv_data_buf_base0;
	unsigned int fbd_uv_data_buf_base1;
	unsigned int fbd_uv_data_stride;
	unsigned int fbd_uv_head_buf_base0;
	unsigned int fbd_uv_head_buf_base1;
	unsigned int fbd_uv_head_stride;
}ISP_FBD_UV_BUF_S;

typedef struct _ISP_FBD_YL_BUF_S
{
	unsigned int fbd_yl_data_buf_base0;
	unsigned int fbd_yl_data_buf_base1;
	unsigned int fbd_yl_data_stride;
	unsigned int fbd_yl_head_buf_base0;
	unsigned int fbd_yl_head_buf_base1;
	unsigned int fbd_yl_head_stride;
}ISP_FBD_YL_BUF_S;

typedef struct _ISP_FBD_BUF_S
{
	ISP_FBD_Y_BUF_S  	stIspFbdYBuf;
	ISP_FBD_UV_BUF_S 	stIspFbdUVBuf; 
	ISP_FBD_YL_BUF_S 	stIspFbdYLBuf;	
} ISP_FBD_BUF_S;

typedef struct _ISP_FBD_ATTR_S
{
	ISP_FBD_CTL_S		stIspFbdCtl;	
	ISP_FBD_SIZE_S		stIspFbdSize;
	ISP_FBD_BUF_S		stIspFbdBuf;	
} ISP_FBD_ATTR_S;
//
int Isp_Drv_Fbd_SetBuf(struct isp_device *isp,ISP_FBD_BUF_S *pstFbdBuf);
int Isp_Drv_Fbd_SetCtl(struct isp_device *isp,ISP_FBD_CTL_S *pstIspFbdCtl);
int Isp_Drv_Fbd_SetSize(struct isp_device *isp,ISP_FBD_SIZE_S *pstIspFbdSize);

#endif /*_ISP_3DNR_FBD_DRV_H_*/