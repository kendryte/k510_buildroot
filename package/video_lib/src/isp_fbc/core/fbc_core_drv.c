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
 * fbc_core_drv.c
 *
 * CANAAN ISP - isp mfbc core module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_fbc/isp_fbc.h"
#include "isp_fbc/core/fbc_core_reg.h"
#include "isp_fbc/core/fbc_core_drv.h"
/*
*
*/
static int Fbc_Drv_Core_SetYBuf(struct isp_device *isp,FBC_CORE_Y_BUF_S *pstYBuf)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstYBuf);

    U_FBC_Y_DATA_BASE_ADDR_0 y_uData0;
    y_uData0.bits.addr0 = pstYBuf->Addr0;
		isp_reg_writel(isp,y_uData0.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_DATA_BASE_ADDR_0);

    U_FBC_Y_DATA_BASE_ADDR_1 y_uData1;
    y_uData1.bits.addr1 = pstYBuf->Addr1;
		isp_reg_writel(isp,y_uData1.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_DATA_BASE_ADDR_1);

    U_FBC_Y_DATA_LINE_STRIDE y_stride;
    y_stride.bits.stride = pstYBuf->Stride;
		isp_reg_writel(isp,y_stride.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_DATA_LINE_STRIDE);

    U_FBC_Y_DATA_WR_BLENGTH wr_blen;
    wr_blen.bits.blen = pstYBuf->WrBlen;
		isp_reg_writel(isp,wr_blen.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_DATA_WR_BLENGTH);
    
    return 0;
}
/*
*
*/
static int Fbc_Drv_Core_SetYHeadBuf(struct isp_device *isp,FBC_CORE_Y_HEAD_BUF_S *pstYHeadBuf)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstYHeadBuf);

    U_FBC_Y_HEAD_DATA_BASE_ADDR_0  y_head_uData0; 
    y_head_uData0.bits.addr0 = pstYHeadBuf->Addr0;
    isp_reg_writel(isp,y_head_uData0.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_HEAD_DATA_BASE_ADDR_0); 

    U_FBC_Y_HEAD_DATA_BASE_ADDR_1  y_head_uData1;
    y_head_uData1.bits.addr1 = pstYHeadBuf->Addr1;
		isp_reg_writel(isp,y_head_uData1.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_HEAD_DATA_BASE_ADDR_1);  

    U_FBC_Y_HEAD_DATA_LINE_STRIDE  y_head_stride;
    y_head_stride.bits.stride = pstYHeadBuf->Stride;
		isp_reg_writel(isp,y_head_stride.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_HEAD_DATA_LINE_STRIDE);  
     
    U_FBC_Y_HEAD_DATA_WR_BLENGTH   wr_blen;
    wr_blen.bits.blen = pstYHeadBuf->WrBlen;
		isp_reg_writel(isp,wr_blen.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_Y_HEAD_DATA_WR_BLENGTH);    
    return 0;
}
/*
*
*/
static int Fbc_Drv_Core_SetUVBuf(struct isp_device *isp,FBC_CORE_UV_BUF_S *pstUVBuf)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstUVBuf);

    U_FBC_UV_DATA_BASE_ADDR_0  uv_addr0;
    uv_addr0.bits.addr0 = pstUVBuf->Addr0;
    isp_reg_writel(isp,uv_addr0.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_DATA_BASE_ADDR_0);

    U_FBC_UV_DATA_BASE_ADDR_1  uv_addr1;      
    uv_addr1.bits.addr1 = pstUVBuf->Addr1;
		isp_reg_writel(isp,uv_addr1.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_DATA_BASE_ADDR_1);

    U_FBC_UV_DATA_LINE_STRIDE  uv_stride;      
    uv_stride.bits.stride = pstUVBuf->Stride;
		isp_reg_writel(isp,uv_stride.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_DATA_LINE_STRIDE);

    U_FBC_UV_DATA_WR_BLENGTH wr_blen;
    wr_blen.bits.blen = pstUVBuf->WrBlen;  
		isp_reg_writel(isp,wr_blen.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_DATA_WR_BLENGTH);
    
    return 0;
}
/*
*
*/
static int Fbc_Drv_Core_SetUVHeadBuf(struct isp_device *isp,FBC_CORE_UV_HEAD_BUF_S *pstUVHeadBuf)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstUVHeadBuf);

    U_FBC_UV_HEAD_DATA_BASE_ADDR_0 uv_head_addr0;
    uv_head_addr0.bits.addr0 = pstUVHeadBuf->Addr0;
    isp_reg_writel(isp,uv_head_addr0.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_HEAD_DATA_BASE_ADDR_0);

    U_FBC_UV_HEAD_DATA_BASE_ADDR_1 uv_head_addr1;
    uv_head_addr1.bits.addr1 = pstUVHeadBuf->Addr1;
	  isp_reg_writel(isp,uv_head_addr1.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_HEAD_DATA_BASE_ADDR_1);

    U_FBC_UV_HEAD_DATA_LINE_STRIDE uv_head_stride; 
    uv_head_stride.bits.stride  = pstUVHeadBuf->Stride;
    isp_reg_writel(isp,uv_head_stride.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_HEAD_DATA_LINE_STRIDE);

    U_FBC_UV_HEAD_DATA_WR_BLENGTH wr_beln;
    wr_beln.bits.blen  = pstUVHeadBuf->WrBlen;
	  isp_reg_writel(isp,wr_beln.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_UV_HEAD_DATA_WR_BLENGTH);
    
    return 0;
}
/*
*
*/
int Fbc_Drv_Core_SetBuf(struct isp_device *isp,FBC_CORE_BUF_S  *pstMfbcBuf)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstMfbcBuf);

    FBC_CORE_Y_BUF_S *pstYBuf = &pstMfbcBuf->stYBuf;
    Fbc_Drv_Core_SetYBuf(isp,pstYBuf);

    FBC_CORE_Y_HEAD_BUF_S *pstYHeadBuf =&pstMfbcBuf->stYHeadBuf;
    Fbc_Drv_Core_SetYHeadBuf(isp,pstYHeadBuf);

    FBC_CORE_UV_BUF_S *pstUVBuf = &pstMfbcBuf->stUVBuf;
    Fbc_Drv_Core_SetUVBuf(isp,pstUVBuf);

    FBC_CORE_UV_HEAD_BUF_S *pstUVHeadBuf = &pstMfbcBuf->stUVHeadBuf;
    Fbc_Drv_Core_SetUVHeadBuf(isp,pstUVHeadBuf);
    return 0;
}
/*
*
*/
int Fbc_Drv_Core_SetSize(struct isp_device *isp,FBC_CORE_SIZE_S *pstSize)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstSize);

    U_FBC_INPUT_SIZE size_uData;
    size_uData.bits.width = pstSize->input_width;
    size_uData.bits.height = pstSize->input_height;    
		isp_reg_writel(isp,size_uData.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_INPUT_SIZE);
    return 0;
}
/*
*
*/
int Fbc_Drv_Core_SetCtl(struct isp_device *isp,unsigned int yuv420_en)
{
    ISP_CHECK_POINTER(isp);

    U_FBC_OUT_FORMAT format_uData;
    format_uData.bits.disable420 = yuv420_en;
	  isp_reg_writel(isp,format_uData.u32,ISP_IOMEM_FBC_CORE,FBC_CORE_OUT_FORMAT);

	return 0;
}
/*
*
*/
/*
int Fbc_Drv_Core_SetCore(struct isp_fbc_device *isp_mfbc,FBC_CORE_ATTR_S *mfbcCoreAttr)
{
    ISP_CHECK_POINTER(isp_mfbc);
    ISP_CHECK_POINTER(mfbcCoreAttr);

    FBC_CORE_BUF_S  *pstMfbcBuf = &mfbcCoreAttr->stMfbcBuf;
    Fbc_Drv_Core_SetBuf(isp,pstMfbcBuf);

    FBC_CORE_SIZE_S *pstSize = &mfbcCoreAttr->stMfbcSize;
    Fbc_Drv_Core_SetSize(isp,pstSize);

    unsigned int yuv420_en = mfbcCoreAttr->yuv420_en;
    Fbc_Drv_Core_SetCtl(isp,yuv420_en);
    return 0;
}
*/
