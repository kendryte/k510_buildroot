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
 * isp_3dnr_fbc_drv.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _ISP_3DNR_FBC_DRV_H_
#define _ISP_3DNR_FBC_DRV_H_

#include "isp_3dnr_fbc_reg.h"

typedef struct _ISP_FBC_CTL_S
{
    unsigned int  fbc_out_format_cfg;
}ISP_FBC_CTL_S;

typedef struct _ISP_FBC_SIZE_S
{  
	unsigned int fbc_input_height;
	unsigned int fbc_input_width;
}ISP_FBC_SIZE_S;

typedef struct _ISP_FBC_Y_BUF_S
{
	unsigned int fbc_y_data_buf_base0;
	unsigned int fbc_y_data_buf_base1;
	unsigned int fbc_y_data_stride;
	unsigned int fbc_y_data_wr_blen;
	unsigned int fbc_y_head_buf_base0;
	unsigned int fbc_y_head_buf_base1;
	unsigned int fbc_y_head_stride;
	unsigned int fbc_y_head_wr_blen;
} ISP_FBC_Y_BUF_S;

typedef struct _ISP_FBC_UV_BUF_S
{
	unsigned int fbc_uv_data_buf_base0;
	unsigned int fbc_uv_data_buf_base1;
	unsigned int fbc_uv_data_stride;
	unsigned int fbc_uv_data_wr_blen;
	unsigned int fbc_uv_head_buf_base0;
	unsigned int fbc_uv_head_buf_base1;
	unsigned int fbc_uv_head_stride;
	unsigned int fbc_uv_head_wr_blen;
	
} ISP_FBC_UV_BUF_S;

typedef struct _ISP_FBC_YL_BUF_S
{
	unsigned int fbc_yl_data_buf_base0;
	unsigned int fbc_yl_data_buf_base1;
	unsigned int fbc_yl_data_stride;
	unsigned int fbc_yl_data_wr_blen;
	unsigned int fbc_yl_head_buf_base0;
	unsigned int fbc_yl_head_buf_base1;
	unsigned int fbc_yl_head_stride;
	unsigned int fbc_yl_head_wr_blen;
	
} ISP_FBC_YL_BUF_S;

typedef struct _ISP_FBC_BUF_S
{
	ISP_FBC_Y_BUF_S		stIspFbcYBuf;
	ISP_FBC_UV_BUF_S	stIspFbcUVBuf;
	ISP_FBC_YL_BUF_S	stIspFbcYLBuf;	
} ISP_FBC_BUF_S;

typedef struct _ISP_FBC_ATTR_S
{
	ISP_FBC_CTL_S	stIspfbcCtl;
	ISP_FBC_SIZE_S  stIspfbcSize;
	ISP_FBC_BUF_S	stIspfbcBuf;	
} ISP_FBC_ATTR_S;
/*
*
*/
int Isp_Drv_Fbc_SetBuf(struct isp_device *isp,ISP_FBC_BUF_S *pstIspFbcBuf);
int Isp_Drv_Fbc_SetCtl(struct isp_device *isp,ISP_FBC_CTL_S *pstIspFbcCtl);
int Isp_Drv_Fbc_SetSize(struct isp_device *isp,ISP_FBC_SIZE_S *pstIspFbcSize);

#endif /*_ISP_3DNR_FBC_DRV_H_*/