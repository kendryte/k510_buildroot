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
#ifndef _ISP_MFBD_DRV_DEF_H_
#define _ISP_MFBD_DRV_DEF_H_

typedef struct _ISP_MFBD_CTL_S
{
    unsigned int  mfbd_en;
    unsigned int  mfbd_format_cfg;
}ISP_MFBD_CTL_S;

typedef struct _ISP_MFBD_SIZE_S
{
	unsigned int mfbd_input_height;
	unsigned int mfbd_input_width;
}ISP_MFBD_SIZE_S;

typedef struct _ISP_MFBD_Y_BUF_S
{
	unsigned int mfbd_y_data_buf_base0;
	unsigned int mfbd_y_data_buf_base1;
	unsigned int mfbd_y_data_stride;
	unsigned int mfbd_y_head_buf_base0;
	unsigned int mfbd_y_head_buf_base1;
	unsigned int mfbd_y_head_stride;
}ISP_MFBD_Y_BUF_S;

typedef struct _ISP_MFBD_UV_BUF_S
{
	unsigned int mfbd_uv_data_buf_base0;
	unsigned int mfbd_uv_data_buf_base1;
	unsigned int mfbd_uv_data_stride;
	unsigned int mfbd_uv_head_buf_base0;
	unsigned int mfbd_uv_head_buf_base1;
	unsigned int mfbd_uv_head_stride;
}ISP_MFBD_UV_BUF_S;

typedef struct _ISP_MFBD_YL_BUF_S
{
	unsigned int mfbd_yl_data_buf_base0;
	unsigned int mfbd_yl_data_buf_base1;
	unsigned int mfbd_yl_data_stride;
	unsigned int mfbd_yl_head_buf_base0;
	unsigned int mfbd_yl_head_buf_base1;
	unsigned int mfbd_yl_head_stride;
}ISP_MFBD_YL_BUF_S;

typedef struct _ISP_MFBD_BUF_S
{
	ISP_MFBD_Y_BUF_S  	stIspMfbdYBuf;
	ISP_MFBD_UV_BUF_S 	stIspMfbdUVBuf; 
	ISP_MFBD_YL_BUF_S 	stIspMfbdYLBuf;	
} ISP_MFBD_BUF_S;

typedef struct _ISP_MFBD_ATTR_S
{
	ISP_MFBD_CTL_S		stIspMfbdCtl;	
	ISP_MFBD_SIZE_S		stIspMfbdSize;
	ISP_MFBD_BUF_S		stIspMfbdBuf;	
} ISP_MFBD_ATTR_S;

//int ISP_DRV_SetMFBD(ISP_MFBD_CONFIG_S *ispMfbdInfo);
//int ISP_DRV_MFBD_SetBuf(ISP_MFBD_ATTR_S *pstMfbdAttr);
//int ISP_DRV_MFBD_SetCtl(ISP_MFBD_ATTR_S *pstMfbdAttr);
int ISP_DRV_SetMFBD(ISP_MFBD_ATTR_S *pstIspMfbdAttr);
//DEBUG
int ISP_DRV_GetMFBDRegsVal(void);
#endif /*_ISP_MFBD_DRV_DEF_H_*/