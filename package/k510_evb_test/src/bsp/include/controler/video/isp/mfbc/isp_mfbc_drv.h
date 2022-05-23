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
#ifndef _ISP_MFBC_DRV_DEF_H_
#define _ISP_MFBC_DRV_DEF_H_

typedef struct _ISP_MFBC_CTL_S
{
    unsigned int  mfbc_out_format_cfg;
}ISP_MFBC_CTL_S;

typedef struct _ISP_MFBC_SIZE_S
{  
	unsigned int mfbc_input_height;
	unsigned int mfbc_input_width;
}ISP_MFBC_SIZE_S;

typedef struct _ISP_MFBC_Y_BUF_S
{
	unsigned int mfbc_y_data_buf_base0;
	unsigned int mfbc_y_data_buf_base1;
	unsigned int mfbc_y_data_stride;
	unsigned int mfbc_y_data_wr_blen;
	unsigned int mfbc_y_head_buf_base0;
	unsigned int mfbc_y_head_buf_base1;
	unsigned int mfbc_y_head_stride;
	unsigned int mfbc_y_head_wr_blen;
} ISP_MFBC_Y_BUF_S;

typedef struct _ISP_MFBC_UV_BUF_S
{
	unsigned int mfbc_uv_data_buf_base0;
	unsigned int mfbc_uv_data_buf_base1;
	unsigned int mfbc_uv_data_stride;
	unsigned int mfbc_uv_data_wr_blen;
	unsigned int mfbc_uv_head_buf_base0;
	unsigned int mfbc_uv_head_buf_base1;
	unsigned int mfbc_uv_head_stride;
	unsigned int mfbc_uv_head_wr_blen;
	
} ISP_MFBC_UV_BUF_S;

typedef struct _ISP_MFBC_YL_BUF_S
{
	unsigned int mfbc_yl_data_buf_base0;
	unsigned int mfbc_yl_data_buf_base1;
	unsigned int mfbc_yl_data_stride;
	unsigned int mfbc_yl_data_wr_blen;
	unsigned int mfbc_yl_head_buf_base0;
	unsigned int mfbc_yl_head_buf_base1;
	unsigned int mfbc_yl_head_stride;
	unsigned int mfbc_yl_head_wr_blen;
	
} ISP_MFBC_YL_BUF_S;

typedef struct _ISP_MFBC_BUF_S
{
	ISP_MFBC_Y_BUF_S	stIspMfbcYBuf;
	ISP_MFBC_UV_BUF_S	stIspMfbcUVBuf;
	ISP_MFBC_YL_BUF_S	stIspMfbcYLBuf;	
} ISP_MFBC_BUF_S;

typedef struct _ISP_MFBC_ATTR_S
{
	ISP_MFBC_CTL_S	stIspMfbcCtl;
	ISP_MFBC_SIZE_S stIspMfbcSize;
	ISP_MFBC_BUF_S	stIspMfbcBuf;	
} ISP_MFBC_ATTR_S;

//int ISP_DRV_MFBC_SetBuf(ISP_MFBC_ATTR_S *pstMfbcAttr);
//int ISP_DRV_MFBC_SetSize(ISP_MFBC_ATTR_S *pstMfbcAttr);
int ISP_DRV_SetMFBC(ISP_MFBC_ATTR_S *pstMfbcAttr);
//debug
int ISP_DRV_GetMFBCRegsVal(void);
#endif/*_ISP_MFBC_DRV_DEF_H_*/
