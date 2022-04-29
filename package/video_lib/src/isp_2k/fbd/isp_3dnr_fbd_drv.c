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
 * isp_3dnr_fbd.c
 *
 * CANAAN ISP - 3dnr Fbd module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_2k/fbd/isp_3dnr_fbd_drv.h"
#include "isp_2k/fbd/isp_3dnr_fbd_reg.h"

static int Isp_Drv_Fbd_SetYBuf(struct isp_device *isp,ISP_FBD_Y_BUF_S  *pstIspFbdYBuf)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstIspFbdYBuf);

	U_ISP_FBD_Y_DATA_BUF_BASE0 stYBuf0;
	stYBuf0.u32 = 0;
	stYBuf0.bits.fbd_y_data_buf_base0 = pstIspFbdYBuf->fbd_y_data_buf_base0;
	isp_reg_writel(isp,stYBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_DATA_BUF_BASE0);

	U_ISP_FBD_Y_DATA_BUF_BASE1 stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.fbd_y_data_buf_base1 = pstIspFbdYBuf->fbd_y_data_buf_base1;
	isp_reg_writel(isp,stYBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_DATA_BUF_BASE1);

	U_ISP_FBD_Y_DATA_LINE_STRIDE stYStride;
	stYStride.u32 = 0;
	stYStride.bits.fbd_y_data_stride = pstIspFbdYBuf->fbd_y_data_stride;
	isp_reg_writel(isp,stYStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_DATA_LINE_STRIDE);

	U_ISP_FBD_Y_HEAD_BUF_BASE0 stYHeadBuf0;
	stYHeadBuf0.u32 = 0;
	stYHeadBuf0.bits.fbd_y_head_buf_base0 = pstIspFbdYBuf->fbd_y_head_buf_base0;
	isp_reg_writel(isp,stYHeadBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_HEAD_BUF_BASE0);

	U_ISP_FBD_Y_HEAD_BUF_BASE1 stYHeadBuf1;
	stYHeadBuf1.u32 = 0;
	stYHeadBuf1.bits.fbd_y_head_buf_base1 = pstIspFbdYBuf->fbd_y_head_buf_base1;
	isp_reg_writel(isp,stYHeadBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_HEAD_BUF_BASE1);

	U_ISP_FBD_Y_HEAD_LINE_STRIDE stYHeadStride;
	stYHeadStride.u32 = 0;
	stYHeadStride.bits.fbd_y_head_stride = pstIspFbdYBuf->fbd_y_head_stride;
	isp_reg_writel(isp,stYHeadStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_Y_HEAD_LINE_STRIDE);
    return 0;
}

static int Isp_Drv_Fbd_SetUVBuf(struct isp_device *isp,ISP_FBD_UV_BUF_S *pstIspFbdUVBuf)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIspFbdUVBuf);

	U_ISP_FBD_UV_DATA_BUF_BASE0 stUvBuf0;
	stUvBuf0.u32 = 0;
	stUvBuf0.bits.fbd_uv_data_buf_base0 = pstIspFbdUVBuf->fbd_uv_data_buf_base0;
	isp_reg_writel(isp,stUvBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_DATA_BUF_BASE0);

	U_ISP_FBD_UV_DATA_BUF_BASE1 stUvBuf1;
	stUvBuf1.u32 = 0;
	stUvBuf1.bits.fbd_uv_data_buf_base1 = pstIspFbdUVBuf->fbd_uv_data_buf_base1;
	isp_reg_writel(isp,stUvBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_DATA_BUF_BASE1);

	U_ISP_FBD_UV_DATA_LINE_STRIDE stUvStride;
	stUvStride.u32 = 0;
	stUvStride.bits.fbd_uv_data_stride = pstIspFbdUVBuf->fbd_uv_data_stride;
	isp_reg_writel(isp,stUvStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_DATA_LINE_STRIDE);

	U_ISP_FBD_UV_HEAD_BUF_BASE0 stUvHeadBuf0;
	stUvHeadBuf0.u32 = 0;
	stUvHeadBuf0.bits.fbd_uv_head_buf_base0 = pstIspFbdUVBuf->fbd_uv_head_buf_base0;
	isp_reg_writel(isp,stUvHeadBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_HEAD_BUF_BASE0);

	U_ISP_FBD_UV_HEAD_BUF_BASE1 stUvHeadBuf1;
	stUvHeadBuf1.u32 = 0;
	stUvHeadBuf1.bits.fbd_uv_head_buf_base1 = pstIspFbdUVBuf->fbd_uv_head_buf_base1;
	isp_reg_writel(isp,stUvHeadBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_HEAD_BUF_BASE1);

	U_ISP_FBD_UV_HEAD_LINE_STRIDE stUvHeadStride;
	stUvHeadStride.u32 = 0;
	stUvHeadStride.bits.fbd_uv_head_stride = pstIspFbdUVBuf->fbd_uv_head_stride;
    isp_reg_writel(isp,stUvHeadStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_UV_HEAD_LINE_STRIDE);

    return 0;
}

static int Isp_Drv_Fbd_SetYLBuf(struct isp_device *isp,ISP_FBD_YL_BUF_S *pstIspFbdYLBuf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIspFbdYLBuf);

	U_ISP_FBD_YL_DATA_BUF_BASE0 stYlBuf0;
	stYlBuf0.u32 = 0;
	stYlBuf0.bits.fbd_yl_data_buf_base0 = pstIspFbdYLBuf->fbd_yl_data_buf_base0;
	isp_reg_writel(isp,stYlBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_DATA_BUF_BASE0);

	U_ISP_FBD_YL_DATA_BUF_BASE1 stYlBuf1;
	stYlBuf1.u32 = 0;
	stYlBuf1.bits.fbd_yl_data_buf_base1 = pstIspFbdYLBuf->fbd_yl_data_buf_base1;
	isp_reg_writel(isp,stYlBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_DATA_BUF_BASE1);

	U_ISP_FBD_YL_DATA_LINE_STRIDE stYlStride;
	stYlStride.u32 = 0;
	stYlStride.bits.fbd_yl_data_stride = pstIspFbdYLBuf->fbd_yl_data_stride;
	isp_reg_writel(isp,stYlStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_DATA_LINE_STRIDE);

	U_ISP_FBD_YL_HEAD_BUF_BASE0 stYlHeadBuf0;
	stYlHeadBuf0.u32 = 0;
	stYlHeadBuf0.bits.fbd_yl_head_buf_base0 = pstIspFbdYLBuf->fbd_yl_head_buf_base0;
	isp_reg_writel(isp,stYlHeadBuf0.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_HEAD_BUF_BASE0);

	U_ISP_FBD_YL_HEAD_BUF_BASE1 stYlHeadBuf1;
	stYlHeadBuf1.u32 = 0;
	stYlHeadBuf1.bits.fbd_yl_head_buf_base1 = pstIspFbdYLBuf->fbd_yl_head_buf_base1;
	isp_reg_writel(isp,stYlHeadBuf1.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_HEAD_BUF_BASE1);

	U_ISP_FBD_YL_HEAD_LINE_STRIDE stYlHeadStride;
	stYlHeadStride.u32 = 0;
	stYlHeadStride.bits.fbd_yl_head_stride = pstIspFbdYLBuf->fbd_yl_head_stride;
	isp_reg_writel(isp,stYlHeadStride.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_YL_HEAD_LINE_STRIDE);

    return 0;
}
/*
*
*/
int Isp_Drv_Fbd_SetBuf(struct isp_device *isp,ISP_FBD_BUF_S *pstFbdBuf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstFbdBuf);
    //
	ISP_FBD_Y_BUF_S  *pstIspFbdYBuf = &pstFbdBuf->stIspFbdYBuf;
    Isp_Drv_Fbd_SetYBuf(isp,pstIspFbdYBuf);
    //
	ISP_FBD_UV_BUF_S  *pstIspFbdUVBuf = &pstFbdBuf->stIspFbdUVBuf; 
    Isp_Drv_Fbd_SetUVBuf(isp,pstIspFbdUVBuf);
    //
	ISP_FBD_YL_BUF_S  *pstIspFbdYLBuf = &pstFbdBuf->stIspFbdYLBuf;
    Isp_Drv_Fbd_SetYLBuf(isp,pstIspFbdYLBuf);

	return 0;	
}
/*
*
*/
int Isp_Drv_Fbd_SetCtl(struct isp_device *isp,ISP_FBD_CTL_S *pstIspFbdCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIspFbdCtl);

	U_ISP_FBD_CTL stCtl;
	stCtl.u32 = 0;
	stCtl.bits.fbd_en = pstIspFbdCtl->fbd_en;
	stCtl.bits.fbd_format_cfg = pstIspFbdCtl->fbd_format_cfg;
	isp_reg_writel(isp,stCtl.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_CTL);

	return 0;	
}
/*
*
*/
int Isp_Drv_Fbd_SetSize(struct isp_device *isp,ISP_FBD_SIZE_S	*pstIspFbdSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIspFbdSize);

	U_ISP_FBD_INPUT_SIZE stInputSize;
	stInputSize.u32 = 0;
	stInputSize.bits.fbd_input_height = pstIspFbdSize->fbd_input_height;
	stInputSize.bits.fbd_input_width = pstIspFbdSize->fbd_input_width;
	isp_reg_writel(isp, stInputSize.u32,ISP_IOMEM_F2K_FBD,ISP_FBD_INPUT_SIZE);

	return 0;	
}
