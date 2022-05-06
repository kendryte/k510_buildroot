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
#include "video/isp/mfbd/isp_mfbd_drv.h"
#include "video/isp/mfbd/isp_mfbd_reg.h"
//#include "video/isp/isp.h"

extern unsigned int   *reg_isp_2k_mfbd_base;
#define ISP_2K_DRV_MFBD_REG_CTX(pstCtx)	 pstCtx = (S_ISP_MFBD_REGS_TYPE *)(reg_isp_2k_mfbd_base)

static int ISP_DRV_MFBD_SetYBuf(ISP_MFBD_Y_BUF_S  *pstIspMfbdYBuf)
{
	ISP_CHECK_POINTER(pstIspMfbdYBuf);

    S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);


	U_ISP_MFBD_Y_DATA_BUF_BASE0 stYBuf0;
	stYBuf0.u32 = 0;
	stYBuf0.bits.mfbd_y_data_buf_base0 = pstIspMfbdYBuf->mfbd_y_data_buf_base0;
	ISP_MFBD_DRV_SET_MfbdYDataBufBase0(pstRegs, stYBuf0.u32);

	U_ISP_MFBD_Y_DATA_BUF_BASE1 stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.mfbd_y_data_buf_base1 = pstIspMfbdYBuf->mfbd_y_data_buf_base1;
	ISP_MFBD_DRV_SET_MfbdYDataBufBase1(pstRegs, stYBuf1.u32);

	U_ISP_MFBD_Y_DATA_LINE_STRIDE stYStride;
	stYStride.u32 = 0;
	stYStride.bits.mfbd_y_data_stride = pstIspMfbdYBuf->mfbd_y_data_stride;
	ISP_MFBD_DRV_SET_MfbdYDataLineStride(pstRegs, stYStride.u32);

	U_ISP_MFBD_Y_HEAD_BUF_BASE0 stYHeadBuf0;
	stYHeadBuf0.u32 = 0;
	stYHeadBuf0.bits.mfbd_y_head_buf_base0 = pstIspMfbdYBuf->mfbd_y_head_buf_base0;
	ISP_MFBD_DRV_SET_MfbdYHeadBufBase0(pstRegs, stYHeadBuf0.u32);

	U_ISP_MFBD_Y_HEAD_BUF_BASE1 stYHeadBuf1;
	stYHeadBuf1.u32 = 0;
	stYHeadBuf1.bits.mfbd_y_head_buf_base1 = pstIspMfbdYBuf->mfbd_y_head_buf_base1;
	ISP_MFBD_DRV_SET_MfbdYHeadBufBase1(pstRegs, stYHeadBuf1.u32);

	U_ISP_MFBD_Y_HEAD_LINE_STRIDE stYHeadStride;
	stYHeadStride.u32 = 0;
	stYHeadStride.bits.mfbd_y_head_stride = pstIspMfbdYBuf->mfbd_y_head_stride;
	ISP_MFBD_DRV_SET_MfbdYHeadLineStride(pstRegs, stYHeadStride.u32);
    return 0;
}

static int ISP_DRV_MFBD_SetUVBuf(ISP_MFBD_UV_BUF_S  *pstIspMfbdUVBuf)
{
	ISP_CHECK_POINTER(pstIspMfbdUVBuf);

	S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);


	U_ISP_MFBD_UV_DATA_BUF_BASE0 stUvBuf0;
	stUvBuf0.u32 = 0;
	stUvBuf0.bits.mfbd_uv_data_buf_base0 = pstIspMfbdUVBuf->mfbd_uv_data_buf_base0;
	ISP_MFBD_DRV_SET_MfbdUvDataBufBase0(pstRegs, stUvBuf0.u32);

	U_ISP_MFBD_UV_DATA_BUF_BASE1 stUvBuf1;
	stUvBuf1.u32 = 0;
	stUvBuf1.bits.mfbd_uv_data_buf_base1 = pstIspMfbdUVBuf->mfbd_uv_data_buf_base1;
	ISP_MFBD_DRV_SET_MfbdUvDataBufBase1(pstRegs, stUvBuf1.u32);

	U_ISP_MFBD_UV_DATA_LINE_STRIDE stUvStride;
	stUvStride.u32 = 0;
	stUvStride.bits.mfbd_uv_data_stride = pstIspMfbdUVBuf->mfbd_uv_data_stride;
	ISP_MFBD_DRV_SET_MfbdUvDataLineStride(pstRegs, stUvStride.u32);

	U_ISP_MFBD_UV_HEAD_BUF_BASE0 stUvHeadBuf0;
	stUvHeadBuf0.u32 = 0;
	stUvHeadBuf0.bits.mfbd_uv_head_buf_base0 = pstIspMfbdUVBuf->mfbd_uv_head_buf_base0;
	ISP_MFBD_DRV_SET_MfbdUvHeadBufBase0(pstRegs, stUvHeadBuf0.u32);

	U_ISP_MFBD_UV_HEAD_BUF_BASE1 stUvHeadBuf1;
	stUvHeadBuf1.u32 = 0;
	stUvHeadBuf1.bits.mfbd_uv_head_buf_base1 = pstIspMfbdUVBuf->mfbd_uv_head_buf_base1;
	ISP_MFBD_DRV_SET_MfbdUvHeadBufBase1(pstRegs, stUvHeadBuf1.u32);

	U_ISP_MFBD_UV_HEAD_LINE_STRIDE stUvHeadStride;
	stUvHeadStride.u32 = 0;
	stUvHeadStride.bits.mfbd_uv_head_stride = pstIspMfbdUVBuf->mfbd_uv_head_stride;
    ISP_MFBD_DRV_SET_MfbdUvHeadLineStride(pstRegs, stUvHeadStride.u32);

    return 0;
}

static int ISP_DRV_MFBD_SetYLBuf(ISP_MFBD_YL_BUF_S  *pstIspMfbdYLBuf)
{
	ISP_CHECK_POINTER(pstIspMfbdYLBuf);

	S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);

	U_ISP_MFBD_YL_DATA_BUF_BASE0 stYlBuf0;
	stYlBuf0.u32 = 0;
	stYlBuf0.bits.mfbd_yl_data_buf_base0 = pstIspMfbdYLBuf->mfbd_yl_data_buf_base0;
	ISP_MFBD_DRV_SET_MfbdYlDataBufBase0(pstRegs, stYlBuf0.u32);

	U_ISP_MFBD_YL_DATA_BUF_BASE1 stYlBuf1;
	stYlBuf1.u32 = 0;
	stYlBuf1.bits.mfbd_yl_data_buf_base1 = pstIspMfbdYLBuf->mfbd_yl_data_buf_base1;
	ISP_MFBD_DRV_SET_MfbdYlDataBufBase1(pstRegs, stYlBuf1.u32);

	U_ISP_MFBD_YL_DATA_LINE_STRIDE stYlStride;
	stYlStride.u32 = 0;
	stYlStride.bits.mfbd_yl_data_stride = pstIspMfbdYLBuf->mfbd_yl_data_stride;
	ISP_MFBD_DRV_SET_MfbdYlDataLineStride(pstRegs, stYlStride.u32);

	U_ISP_MFBD_YL_HEAD_BUF_BASE0 stYlHeadBuf0;
	stYlHeadBuf0.u32 = 0;
	stYlHeadBuf0.bits.mfbd_yl_head_buf_base0 = pstIspMfbdYLBuf->mfbd_yl_head_buf_base0;
	ISP_MFBD_DRV_SET_MfbdYlHeadBufBase0(pstRegs, stYlHeadBuf0.u32);

	U_ISP_MFBD_YL_HEAD_BUF_BASE1 stYlHeadBuf1;
	stYlHeadBuf1.u32 = 0;
	stYlHeadBuf1.bits.mfbd_yl_head_buf_base1 = pstIspMfbdYLBuf->mfbd_yl_head_buf_base1;
	ISP_MFBD_DRV_SET_MfbdYlHeadBufBase1(pstRegs, stYlHeadBuf1.u32);

	U_ISP_MFBD_YL_HEAD_LINE_STRIDE stYlHeadStride;
	stYlHeadStride.u32 = 0;
	stYlHeadStride.bits.mfbd_yl_head_stride = pstIspMfbdYLBuf->mfbd_yl_head_stride;
	ISP_MFBD_DRV_SET_MfbdYlHeadLineStride(pstRegs, stYlHeadStride.u32);

    return 0;
}
/*
*
*/
static int ISP_DRV_MFBD_SetBuf(ISP_MFBD_BUF_S *pstMfbdBuf)
{
	ISP_CHECK_POINTER(pstMfbdBuf);
    //
	ISP_MFBD_Y_BUF_S  *pstIspMfbdYBuf = &pstMfbdBuf->stIspMfbdYBuf;
    ISP_DRV_MFBD_SetYBuf(pstIspMfbdYBuf);
    //
	ISP_MFBD_UV_BUF_S  *pstIspMfbdUVBuf = &pstMfbdBuf->stIspMfbdUVBuf; 
    ISP_DRV_MFBD_SetUVBuf(pstIspMfbdUVBuf);
    //
	ISP_MFBD_YL_BUF_S  *pstIspMfbdYLBuf = &pstMfbdBuf->stIspMfbdYLBuf;
    ISP_DRV_MFBD_SetYLBuf(pstIspMfbdYLBuf);

	return 0;	
}
/*
*
*/
static int ISP_DRV_MFBD_SetCtl(ISP_MFBD_CTL_S *pstIspMfbdCtl)
{
	ISP_CHECK_POINTER(pstIspMfbdCtl);

	S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);

	U_ISP_MFBD_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.mfbd_en = pstIspMfbdCtl->mfbd_en;
	stCtl.bits.mfbd_format_cfg = pstIspMfbdCtl->mfbd_format_cfg;
	ISP_MFBD_DRV_SET_MfbdCtl(pstRegs, stCtl.u32);

	return 0;	
}
/*
*
*/
static int ISP_DRV_MFBD_SetSize(ISP_MFBD_SIZE_S	*pstIspMfbdSize)
{
	ISP_CHECK_POINTER(pstIspMfbdSize);

	S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);

	U_ISP_MFBD_INPUT_SIZE stInputSize;
	stInputSize.u32 = 0;
	stInputSize.bits.mfbd_input_height = pstIspMfbdSize->mfbd_input_height;
	stInputSize.bits.mfbd_input_width = pstIspMfbdSize->mfbd_input_width;
	ISP_MFBD_DRV_SET_MfbdInputSize(pstRegs, stInputSize.u32);

	return 0;	
}

int ISP_DRV_SetMFBD(ISP_MFBD_ATTR_S *pstIspMfbdAttr)
{
	ISP_CHECK_POINTER(pstIspMfbdAttr);

	ISP_MFBD_BUF_S *pstMfbdBuf = &pstIspMfbdAttr->stIspMfbdBuf;
	ISP_DRV_MFBD_SetBuf(pstMfbdBuf);

	ISP_MFBD_CTL_S *pstIspMfbdCtl = &pstIspMfbdAttr->stIspMfbdCtl;
	ISP_DRV_MFBD_SetCtl(pstIspMfbdCtl);

	ISP_MFBD_SIZE_S	*pstIspMfbdSize = &pstIspMfbdAttr->stIspMfbdSize;
	ISP_DRV_MFBD_SetSize(pstIspMfbdSize);
	return 0;
}

//DEBUG
int ISP_DRV_GetMFBDRegsVal(void)
{
	S_ISP_MFBD_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBD_REG_CTX(pstRegs);

	ISP_MFBD_DRV_GET_MfbdRegsVal(pstRegs);
	
	return 0;
}

#if 0
/*
*
*/
int ISP_DRV_SetMFBD(ISP_MFBD_CONFIG_S *ispMfbdInfo)
{
	ISP_CHECK_POINTER(ispMfbdInfo);
	ISP_MFBD_ATTR_S pstMfbdAttr;

	pstMfbdAttr.mfbd_en = ispMfbdInfo->mfbd_en;
	pstMfbdAttr.mfbd_format_cfg = ispMfbdInfo->mfbd_format_cfg;
	//
	pstMfbdAttr.mfbd_input_width = ispMfbdInfo->mfbd_input_size.Width;
	pstMfbdAttr.mfbd_input_height = ispMfbdInfo->mfbd_input_size.Height;
	//y
	pstMfbdAttr.mfbd_y_data_buf_base0 = ispMfbdInfo->yDataBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_y_data_buf_base1 = ispMfbdInfo->yDataBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_y_data_stride = ispMfbdInfo->yDataBufInfo.data_stride;
	//
	pstMfbdAttr.mfbd_y_head_buf_base0 = ispMfbdInfo->yHeadBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_y_head_buf_base1 = ispMfbdInfo->yHeadBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_y_head_stride = ispMfbdInfo->yHeadBufInfo.data_stride;
	//uv
	pstMfbdAttr.mfbd_uv_data_buf_base0 = ispMfbdInfo->uvDataBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_uv_data_buf_base1 = ispMfbdInfo->uvDataBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_uv_data_stride = ispMfbdInfo->uvDataBufInfo.data_stride;
	//
	pstMfbdAttr.mfbd_uv_head_buf_base0 = ispMfbdInfo->uvHeadBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_uv_head_buf_base1 = ispMfbdInfo->uvHeadBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_uv_head_stride = ispMfbdInfo->uvHeadBufInfo.data_stride;	
	//yl
	pstMfbdAttr.mfbd_yl_data_buf_base0 = ispMfbdInfo->ylDataBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_yl_data_buf_base1 = ispMfbdInfo->ylDataBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_yl_data_stride = ispMfbdInfo->ylDataBufInfo.data_stride;
	//
	pstMfbdAttr.mfbd_yl_head_buf_base0 = ispMfbdInfo->ylHeadBufInfo.data_buf_base0;
	pstMfbdAttr.mfbd_yl_head_buf_base1 = ispMfbdInfo->ylHeadBufInfo.data_buf_base1;
	pstMfbdAttr.mfbd_yl_head_stride = ispMfbdInfo->ylHeadBufInfo.data_stride;

	ISP_DRV_MFBD_SetDonfig(&pstMfbdAttr);	
	return 0;
}
#endif
