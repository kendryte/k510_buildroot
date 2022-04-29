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
  File Name     : hdmi.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : isp.h
    Author      :
    Modification: Created file

******************************************************************************/
#include <stdio.h>

#include "isp_com.h"
//#include "isp_2k/isp.h"
#include "isp_2k/wrap/isp_wrap_drv.h"
#include "isp_2k/core/isp_core_drv.h"
#include "isp_2k/ds/isp_ds_drv.h"

extern ISP_WRAP_CFG_INFO imx385_wrap_info;
extern ISP_CORE_CFG_INFO imx385_core_info;
extern ISP_DS_CFG_INFO   imx385_ds_info;
extern ISP_WRAP_CFG_INFO jfx23s_wrap_info;
extern ISP_CORE_CFG_INFO jfx23s_core_info;
extern ISP_DS_CFG_INFO   jfx23s_ds_info;
/****************************************************************************
*wrap
*****************************************************************************/
//
void isp_r2k_wrap_SetComRst(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    ISP_WRAP_RST_CTL_S stRstCtl;
	  stRstCtl.sw_3dnr_rst = 1;    
	  stRstCtl.wdr_2_frame_rst = 1;
	  stRstCtl.wdr_3_frame_rst =1;
	  stRstCtl.ldc_rst = 1; 
	  stRstCtl.main_out_rst = 1;   
	  stRstCtl.ds0_out_rst = 1;    
	  stRstCtl.ds1_out_rst = 1;   
	  stRstCtl.ds2_out_rst = 1; 
	  stRstCtl.wrap_com_rst = 1;   
	  stRstCtl.wrap_cfg_rst = 1;   
	  stRstCtl.core_com_rst = 1;   
	  stRstCtl.core_cfg_rst = 1; 
	  stRstCtl.axi_wr_ch_rst = 1;  
	  stRstCtl.axi_rd_ch_rst = 1;     
    Isp_Drv_R2k_Wrap_SetPipeReset(isp,&stRstCtl);
}
//
void isp_r2k_wrap_SetDmaRst(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    ISP_WRAP_DMA_RST_CTL_S stDmaRstCtl;
    stDmaRstCtl.y_3dnr_wr_ch_rst = 1;     
    stDmaRstCtl.uv_3dnr_wr_ch_rst = 1;    
    stDmaRstCtl.ldc_y_wr_ch_rst = 1;      
    stDmaRstCtl.ldc_uv_wr_ch_rst = 1;     
    stDmaRstCtl.wdr_raw_wr_ch_rst = 1;    
    stDmaRstCtl.main_out_y_wr_ch_rst = 1; 
    stDmaRstCtl.main_out_uv_wr_ch_rst = 1;
    stDmaRstCtl.y_3dnr_rd_ch_rst = 1;     
    stDmaRstCtl.uv_3dnr_rd_ch_rst = 1;    
    stDmaRstCtl.ldc_y_rd_ch_rst = 1;      
    stDmaRstCtl.ldc_uv_rd_ch_rst = 1;     
    stDmaRstCtl.wdr_raw_rd_ch_rst = 1;    
    stDmaRstCtl.ds0_out_y_wr_ch_rst = 1;  
    stDmaRstCtl.ds0_out_uv_wr_ch_rst = 1; 
    stDmaRstCtl.ds1_out_y_wr_ch_rst = 1;  
    stDmaRstCtl.ds1_out_uv_wr_ch_rst = 1; 
    stDmaRstCtl.ds2_out_r_wr_ch_rst = 1;  
    stDmaRstCtl.ds2_out_g_wr_ch_rst = 1;  
    stDmaRstCtl.ds2_out_b_wr_ch_rst = 1;  
    stDmaRstCtl.ds0_osd0_rd_ch_rst = 1;   
    stDmaRstCtl.ds0_osd1_rd_ch_rst = 1;   
    stDmaRstCtl.ds1_osd0_rd_ch_rst = 1;   
    stDmaRstCtl.ds1_osd1_rd_ch_rst = 1;   
    stDmaRstCtl.ds2_osd0_rd_ch_rst = 1;   
    stDmaRstCtl.ds2_osd1_rd_ch_rst = 1;   
    stDmaRstCtl.ds1_osd2_rd_ch_rst = 1;   
    stDmaRstCtl.ds2_osd2_rd_ch_rst = 1;   
    Isp_Drv_R2k_Wrap_SetDmaReset(isp,&stDmaRstCtl);
}
//
void isp_r2k_wrap_SetPipeClkCtl(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    ISP_WRAP_PIPE_CLK_CTL_S pstPipeClkCtl;
    pstPipeClkCtl.wrap_com_clk_en = 1;
    pstPipeClkCtl.wrap_cfg_clk_en = 1;
    pstPipeClkCtl.core_com_clk_en = 1;
    pstPipeClkCtl.core_cfg_clk_en = 1;
    pstPipeClkCtl.axi_wr_ch_en = 1;   
    pstPipeClkCtl.axi_rd_ch_en = 1;    
	Isp_Drv_R2k_Wrap_SetComClkCtl(isp,&pstPipeClkCtl);
}
//
void isp_r2k_wrap_SetLdc(struct isp_device *isp,ISP_WRAP_LDC_S *ldcInfo)
{
    ISP_CHECK_POINTER(isp);
	  ISP_CHECK_POINTER(ldcInfo);

    ISP_WRAP_LDC_ATTR_S pstLdcAttr;
	  if( 1 == ldcInfo->ldc_en)
	  {
	  	pstLdcAttr.ldc_clk_en = 1;
	  	pstLdcAttr.ldc_dma_en = 1;
	  }
	  else
	  {
	  	pstLdcAttr.ldc_clk_en = 0;
	  	pstLdcAttr.ldc_dma_en = 0;
	  }	
    ISP_WRAP_LDC_BUF_S              *stLdcBuf = &pstLdcAttr.stLdcBuf;
    stLdcBuf->ldc_y_buf_base = ldcInfo->ldc_y_buf_base;//ISP_BUF_LDC_Y;
    stLdcBuf->ldc_uv_buf_base = ldcInfo->ldc_uv_buf_base;//ISP_BUF_LDC_UV;
    stLdcBuf->ldc_y_line_stride = ldcInfo->ldc_line_stride;//ISP_BUF_LDC_Y_STRIDE;
    stLdcBuf->ldc_uv_line_stride = ldcInfo->ldc_line_stride;//ISP_BUF_LDC_UV_STRIDE;
    Isp_Drv_R2k_Wrap_SetLdc(isp,&pstLdcAttr);
}
//
void isp_r2k_wrap_SetMainOut(struct isp_device *isp,ISP_WRAP_MAIN_S *mainInfo)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(mainInfo);
    ISP_WRAP_MAINOUT_ATTR_S pstMainOutAttr;
    pstMainOutAttr.main_out_clk_en = 1;
	if( 1 == mainInfo->main_out_en)
	{
		pstMainOutAttr.main_out_dma_en = 1;
		pstMainOutAttr.pix_remap_main_en = mainInfo->main_pix_remap_en;
	}
	else
	{
		//pstMainOutAttr.main_out_clk_en = 0;
		pstMainOutAttr.main_out_dma_en = 0;
        pstMainOutAttr.pix_remap_main_en = 0;
	}
    ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *stMainPixelFormat = &pstMainOutAttr.stMainPixelFormat;
	stMainPixelFormat->main_out_img_format = mainInfo->main_out_img_format;//ISP_YUV_DATA;
	stMainPixelFormat->main_out_img_out_format = mainInfo->main_out_img_out_format;//IN_YUV420;
	stMainPixelFormat->main_out_pixel_width = mainInfo->main_out_pxl_width;//PIXEL_8;
	stMainPixelFormat->main_out_yuv422_pxl_order = mainInfo->main_out_yuv422_pxl_order;//YUYV;
	stMainPixelFormat->main_out_yuv_in_format = mainInfo->main_out_yuv_in_format;//IN_YUV422;
    ISP_WRAP_MAIN_OUT_SIZE_S        *stMainOutSize = &pstMainOutAttr.stMainOutSize;
	stMainOutSize->main_out_h_size = mainInfo->main_size.Width - 1;
	stMainOutSize->main_out_v_size = mainInfo->main_size.Height - 1;
    ISP_WRAP_MAIN_BUF_S             *stMainBuf = &pstMainOutAttr.stMainBuf;
    stMainBuf->main_y_buf0_base = mainInfo->main_y_buf0_base;//ISP_BUF_MAIN_Y;
    stMainBuf->main_y_buf1_base = mainInfo->main_y_buf1_base;//ISP_BUF_MAIN_Y;
    stMainBuf->main_uv_buf0_base = mainInfo->main_uv_buf0_base;//ISP_BUF_MAIN_UV;
    stMainBuf->main_uv_buf1_base = mainInfo->main_uv_buf1_base;//ISP_BUF_MAIN_UV;
    stMainBuf->main_y_line_stride = mainInfo->main_line_stride;//SP_BUF_MAIN_Y_STRIDE;
    stMainBuf->main_uv_line_stride = mainInfo->main_line_stride;//ISP_BUF_MAIN_UV_STRIDE;
    Isp_Drv_R2k_Wrap_SetMainOut(isp,&pstMainOutAttr);
}
//
void isp_r2k_wrap_SetDs0Out(struct isp_device *isp,ISP_WRAP_DS0_S *ds0Info)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(ds0Info);
	unsigned int Width = ds0Info->ds0_size.Width;
	unsigned int Height = ds0Info->ds0_size.Height;
    ISP_WRAP_DS0OUT_ATTR_S pstDs0OutAttr;
    ISP_WRAP_DS0_CLK_CTL_S          *stDs0ClkCtl = &pstDs0OutAttr.stDs0ClkCtl;
    ISP_WRAP_DS0_DMA_EN_CTL_S       *stDs0DmaEn = &pstDs0OutAttr.stDs0DmaEn;

	stDs0ClkCtl->ds0_out_clk_en = 1;
	stDs0ClkCtl->ds0_out_y_ch_clk_en = 1;
	stDs0ClkCtl->ds0_out_uv_ch_clk_en = 1;

	if(1 == ds0Info->ds0_out_en)
	{
		stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 0;
		stDs0DmaEn->ds_out0_dma_en = 1;
		stDs0DmaEn->ds_out0_y_ch_dma_en = 1;
		stDs0DmaEn->ds_out0_uv_ch_dma_en = 1;
		stDs0DmaEn->ds0_osd0_ch_dma_en =0;
		stDs0DmaEn->ds0_osd1_ch_dma_en = 0;
		stDs0DmaEn->ds0_osd2_ch_dma_en = 0;
		if( 1 == ds0Info->ds0_osd0_en)
		{
			stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 1;
			stDs0DmaEn->ds0_osd0_ch_dma_en = 1;
		}
		if( 1 == ds0Info->ds0_osd1_en)
		{
			stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 1;
			stDs0DmaEn->ds0_osd1_ch_dma_en = 1;
		}
		if( 1 == ds0Info->ds0_osd2_en)
		{
			stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 1;
			stDs0DmaEn->ds0_osd2_ch_dma_en = 1;
		}
	}
	else
	{
		//stDs0ClkCtl->ds0_out_clk_en = 0;
		//stDs0ClkCtl->ds0_out_y_ch_clk_en = 0;
		//stDs0ClkCtl->ds0_out_uv_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd0_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd1_ch_clk_en = 0;
		stDs0ClkCtl->ds_out0_osd2_ch_clk_en = 0;
		stDs0DmaEn->ds_out0_dma_en = 0;	
		stDs0DmaEn->ds_out0_y_ch_dma_en =0;
		stDs0DmaEn->ds_out0_uv_ch_dma_en = 0;	
		stDs0DmaEn->ds0_osd0_ch_dma_en =0;
		stDs0DmaEn->ds0_osd1_ch_dma_en = 0;
		stDs0DmaEn->ds0_osd2_ch_dma_en = 0;
	}
    pstDs0OutAttr.pix_remap_out0_en = ds0Info->pix_remap_out0_en;
    ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *stDs0PixelFormat = &pstDs0OutAttr.stDs0PixelFormat;
	stDs0PixelFormat->ds0_out_img_format = ds0Info->ds0_out_img_format;//ISP_YUV_DATA;
	stDs0PixelFormat->ds0_out_img_out_format = ds0Info->ds0_out_img_out_format;//IN_YUV420;
	stDs0PixelFormat->ds0_out_pixel_width = ds0Info->ds0_out_pxl_width;//PIXEL_8;
	stDs0PixelFormat->ds0_out_yuv422_pxl_order = ds0Info->ds0_out_yuv422_pxl_order;//YUYV;
	stDs0PixelFormat->ds0_out_yuv_in_format = ds0Info->ds0_out_yuv_in_format;//IN_YUV422;
    ISP_WRAP_DS0_OUT_SIZE_S         *stDs0OutSize = &pstDs0OutAttr.stDs0OutSize;
	stDs0OutSize->ds0_out_h_size = Width - 1;
	stDs0OutSize->ds0_out_v_size = Height - 1;
    ISP_WRAP_DS0_BUF_S              *stDs0Buf = &pstDs0OutAttr.stDs0Buf;
    stDs0Buf->ds0_y_buf0_base = ds0Info->ds0_y_buf0_base;//ISP_BUF_DS0_Y;
    stDs0Buf->ds0_y_buf1_base = ds0Info->ds0_y_buf1_base;//ISP_BUF_DS0_Y;
    stDs0Buf->ds0_y_line_stride = ds0Info->ds0_line_stride;//(Width + 15)/16*16;//ISP_BUF_DS0_Y_STRIDE;
    stDs0Buf->ds0_uv_line_stride = ds0Info->ds0_line_stride;//(Width + 15)/16*16;//ISP_BUF_DS0_UV_STRIDE;	
    stDs0Buf->ds0_uv_buf0_base = ds0Info->ds0_uv_buf0_base;//ISP_BUF_DS0_Y + stDs0Buf->ds0_y_line_stride * Height;//ISP_BUF_DS0_UV;
    stDs0Buf->ds0_uv_buf1_base = ds0Info->ds0_uv_buf1_base;//ISP_BUF_DS0_Y + stDs0Buf->ds0_y_line_stride * Height;//ISP_BUF_DS0_UV;
    Isp_Drv_R2k_Wrap_SetDs0Out(isp,&pstDs0OutAttr);
}
//
void isp_r2k_wrap_SetDs1Out(struct isp_device *isp,ISP_WRAP_DS1_S *ds1Info)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(ds1Info);
    ISP_WRAP_DS1OUT_ATTR_S pstDs1OutAttr;
	unsigned int Width = ds1Info->ds1_size.Width;
	unsigned int Height = ds1Info->ds1_size.Height;
    ISP_WRAP_DS1_CLK_CTL_S          *stDs1ClkCtl = &pstDs1OutAttr.stDs1ClkCtl;
    ISP_WRAP_DS1_DMA_EN_CTL_S       *stDs1DmaEn = &pstDs1OutAttr.stDs1DmaEn;

	stDs1ClkCtl->ds1_out_clk_en  = 1;
	stDs1ClkCtl->ds1_out_y_ch_clk_en = 1;
	stDs1ClkCtl->ds1_out_uv_ch_clk_en = 1;
    
	if( 1 == ds1Info->ds1_out_en)	{

		stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
		stDs1DmaEn->ds_out1_dma_en = 1;
		stDs1DmaEn->ds_out1_y_ch_dma_en = 1;
		stDs1DmaEn->ds_out1_uv_ch_dma_en = 1;
		stDs1DmaEn->ds1_osd0_ch_dma_en = 0;
		stDs1DmaEn->ds1_osd1_ch_dma_en = 0;
		stDs1DmaEn->ds1_osd2_ch_dma_en = 0;
		if( 1 == ds1Info->ds1_osd0_en)
		{
			stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
			stDs1DmaEn->ds1_osd0_ch_dma_en = 1;
		}
		if( 1 == ds1Info->ds1_osd1_en)
		{
			stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
			stDs1DmaEn->ds1_osd1_ch_dma_en = 1;
		}
		if( 1 == ds1Info->ds1_osd2_en)
		{
			stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
			stDs1DmaEn->ds1_osd2_ch_dma_en = 1;
		}
	}
	else
	{
		//stDs1ClkCtl->ds1_out_clk_en  = 0;
		//stDs1ClkCtl->ds1_out_y_ch_clk_en = 0;
		//stDs1ClkCtl->ds1_out_uv_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd0_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd1_ch_clk_en = 0;
		stDs1ClkCtl->ds_out1_osd2_ch_clk_en = 0;
		stDs1DmaEn->ds_out1_dma_en = 0;
		stDs1DmaEn->ds_out1_y_ch_dma_en = 0;
		stDs1DmaEn->ds_out1_uv_ch_dma_en = 0;
		stDs1DmaEn->ds1_osd0_ch_dma_en = 0;
		stDs1DmaEn->ds1_osd1_ch_dma_en = 0;
		stDs1DmaEn->ds1_osd2_ch_dma_en = 0;
	}
    pstDs1OutAttr.pix_remap_out1_en = ds1Info->pix_remap_out1_en;
    ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *stDs1PixelFormat = &pstDs1OutAttr.stDs1PixelFormat;
	stDs1PixelFormat->ds1_out_img_format = ds1Info->ds1_out_img_format;//ISP_YUV_DATA;
	stDs1PixelFormat->ds1_out_img_out_format = ds1Info->ds1_out_img_out_format;//IN_YUV420;
	stDs1PixelFormat->ds1_out_pixel_width = ds1Info->ds1_out_pxl_width;//PIXEL_8;
	stDs1PixelFormat->ds1_out_yuv422_pxl_order = ds1Info->ds1_out_yuv422_pxl_order;//YUYV;
	stDs1PixelFormat->ds1_out_yuv_in_format = ds1Info->ds1_out_yuv_in_format;//IN_YUV422;
    ISP_WRAP_DS1_OUT_SIZE_S         *stDs1OutSize = &pstDs1OutAttr.stDs1OutSize;
	stDs1OutSize->ds1_out_h_size = ds1Info->ds1_size.Width - 1;
	stDs1OutSize->ds1_out_v_size = ds1Info->ds1_size.Height - 1;
    ISP_WRAP_DS1_BUF_S              *stDs1Buf = &pstDs1OutAttr.stDs1Buf;
    stDs1Buf->ds1_y_buf0_base = ds1Info->ds1_y_buf0_base;//ISP_BUF_DS1_Y;
    stDs1Buf->ds1_y_buf1_base = ds1Info->ds1_y_buf1_base;//ISP_BUF_DS1_Y;
    stDs1Buf->ds1_y_line_stride = ds1Info->ds1_line_stride;//(Width +15)/16*16;//ISP_BUF_DS1_Y_STRIDE;
    stDs1Buf->ds1_uv_line_stride = ds1Info->ds1_line_stride;//(Width +15)/16*16;//ISP_BUF_DS1_Y_STRIDE;	
    stDs1Buf->ds1_uv_buf0_base = ds1Info->ds1_uv_buf0_base;//ISP_BUF_DS1_Y + stDs1Buf->ds1_y_line_stride *Height;//ISP_BUF_DS1_UV;
    stDs1Buf->ds1_uv_buf1_base = ds1Info->ds1_uv_buf1_base;//ISP_BUF_DS1_Y + stDs1Buf->ds1_y_line_stride *Height;//ISP_BUF_DS1_UV;
    Isp_Drv_R2k_Wrap_SetDs1Out(isp,&pstDs1OutAttr);
}
//
void isp_r2k_wrap_SetDs2Out(struct isp_device *isp,ISP_WRAP_DS2_S *ds2Info)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(ds2Info);
	unsigned int Width = ds2Info->ds2_size.Width;
	unsigned int Height = ds2Info->ds2_size.Height;
    ISP_WRAP_DS2OUT_ATTR_S pstDs2OutAttr;
    ISP_WRAP_DS2_CLK_CTL_S          *stDs2ClkCtl = &pstDs2OutAttr.stDs2ClkCtl;
    ISP_WRAP_DS2_DMA_EN_CTL_S       *stDs2DmaEn = &pstDs2OutAttr.stDs2DmaEn;

	stDs2ClkCtl->ds2_out_clk_en = 1;
	stDs2ClkCtl->ds2_out_r_ch_clk_en = 1;
	stDs2ClkCtl->ds2_out_g_ch_clk_en = 1;
	stDs2ClkCtl->ds2_out_b_ch_clk_en = 1;

	if( 1 == ds2Info->ds2_out_en )
	{
		stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 0;
		stDs2DmaEn->ds_out2_dma_en = 1 ;
		stDs2DmaEn->ds_out2_r_ch_dma_en = 1;
		stDs2DmaEn->ds_out2_g_ch_dma_en = 1;
		stDs2DmaEn->ds_out2_b_ch_dma_en = 1;
		stDs2DmaEn->ds2_osd0_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd1_ch_dma_en = 0;
		if( 1 == ds2Info->ds2_osd0_en)
		{
			stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 1;
			stDs2DmaEn->ds2_osd0_ch_dma_en = 1;
		}
		if( 1 == ds2Info->ds2_osd1_en)
		{
			stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 1;
			stDs2DmaEn->ds2_osd1_ch_dma_en = 1;
		}
	}
	else
	{
		//stDs2ClkCtl->ds2_out_clk_en = 0;
		//stDs2ClkCtl->ds2_out_r_ch_clk_en = 0;
		//stDs2ClkCtl->ds2_out_g_ch_clk_en = 0;
		//stDs2ClkCtl->ds2_out_b_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd0_ch_clk_en = 0;
		stDs2ClkCtl->ds_out2_osd1_ch_clk_en = 0;
		stDs2DmaEn->ds_out2_dma_en = 0 ;
		stDs2DmaEn->ds_out2_r_ch_dma_en = 0;
		stDs2DmaEn->ds_out2_g_ch_dma_en = 0;
		stDs2DmaEn->ds_out2_b_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd0_ch_dma_en = 0;
		stDs2DmaEn->ds2_osd1_ch_dma_en = 0;
	}
    ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *stDs2PixelFormat = &pstDs2OutAttr.stDs2PixelFormat;
	stDs2PixelFormat->ds2_out_img_format = ds2Info->ds2_out_img_format;//ISP_RGBRAW_DATA;
	stDs2PixelFormat->ds2_out_img_out_format = ds2Info->ds2_out_img_out_format;//OUT_ARGB;     
	stDs2PixelFormat->ds2_out_pixel_width = ds2Info->ds2_out_pxl_width;//PIXEL_8;
	stDs2PixelFormat->ds2_out_yuv422_pxl_order = ds2Info->ds2_out_yuv422_pxl_order;//YUYV; //not need
	stDs2PixelFormat->ds2_out_yuv_in_format = ds2Info->ds2_out_yuv_in_format;//IN_YUV422; //not need
    ISP_WRAP_DS2_OUT_SIZE_S         *stDs2OutSize = &pstDs2OutAttr.stDs2OutSize;
	stDs2OutSize->ds2_out_h_size = ds2Info->ds2_size.Width - 1;
	stDs2OutSize->ds2_out_v_size = ds2Info->ds2_size.Height - 1;
    ISP_WRAP_DS2_BUF_S              *stDs2Buf = &pstDs2OutAttr.stDs2Buf;
	stDs2Buf->ds2_r_buf0_base = ds2Info->ds2_r_buf0_base;
	stDs2Buf->ds2_r_buf1_base = ds2Info->ds2_r_buf1_base;
	stDs2Buf->ds2_g_buf0_base = ds2Info->ds2_g_buf0_base;
	stDs2Buf->ds2_g_buf1_base = ds2Info->ds2_g_buf1_base;
	stDs2Buf->ds2_b_buf0_base = ds2Info->ds2_b_buf0_base;
	stDs2Buf->ds2_b_buf1_base = ds2Info->ds2_b_buf1_base;
    stDs2Buf->ds2_r_line_stride = ds2Info->ds2_line_stride;
    stDs2Buf->ds2_g_line_stride = ds2Info->ds2_line_stride;
    stDs2Buf->ds2_b_line_stride = ds2Info->ds2_line_stride;
	Isp_Drv_R2k_Wrap_SetDs2Out(isp,&pstDs2OutAttr);	
}
//
void isp_r2k_wrap_SetDmaConfig(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    ISP_WRAP_DMA_ATTR_S pstDmaAttr;
    unsigned int DmaChIndex = 0;
	ISP_WRAP_DMA_MODE_S *stDmaChMode = &pstDmaAttr.stDmaChMode;
    stDmaChMode->rd_dma_arb_mode = 0;//1;
    stDmaChMode->wr_dma_arb_mode = 0;//1;
    for(DmaChIndex=0; DmaChIndex<ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stDmaChMode->rd_dma_ch_id[DmaChIndex] = DmaChIndex;
        stDmaChMode->wr_dma_ch_id[DmaChIndex] = DmaChIndex;
        stDmaChMode->rd_dma_ch_weight[DmaChIndex] = 0x01;
        stDmaChMode->wr_dma_ch_weight[DmaChIndex] = 0x01;
        stDmaChMode->rd_dma_ch_priority[DmaChIndex] = ISP_DMA_CH_NUM-DmaChIndex-1;
        stDmaChMode->wr_dma_ch_priority[DmaChIndex] = ISP_DMA_CH_NUM-DmaChIndex-1;
	if(DmaChIndex < 8)
        {
        	stDmaChMode->rd_dma_ch_priority[DmaChIndex] = DmaChIndex;
        	stDmaChMode->wr_dma_ch_priority[DmaChIndex] = DmaChIndex;
        }
    }
	ISP_WRAP_DMA_CFG_S *stDmaCfg = &pstDmaAttr.stDmaCfg;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_outst = 1;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_outst = 1;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_burstl = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_burstl = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_int_line_num = 8;
        stDmaCfg->stDmaChcfg[DmaChIndex].wr_err_dec_en = 0;
        stDmaCfg->stDmaChcfg[DmaChIndex].rd_err_dec_en = 0;
        if((DmaChIndex > 5) && (DmaChIndex < 8))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 0;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }
        if((DmaChIndex > 7) && (DmaChIndex < 13))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }
        if((DmaChIndex > 12))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_noncon_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].y_uv_swap_en = 1;
        }
	if((DmaChIndex > 1) && (DmaChIndex < 4))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_outst = 14;
            stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_outst = 15;
            stDmaCfg->stDmaChcfg[DmaChIndex].wr_outst_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].rd_outst_en = 1;
        }
	if((DmaChIndex > 5) && (DmaChIndex < 8))
        {
            stDmaCfg->stDmaChcfg[DmaChIndex].wr_ch_outst = 6;
            stDmaCfg->stDmaChcfg[DmaChIndex].rd_ch_outst = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].wr_outst_en = 1;
            stDmaCfg->stDmaChcfg[DmaChIndex].rd_outst_en = 0;
        }
    }
    ISP_WRAP_DMA_ERR_DEC_CFG_S *stErrDecCfg = &pstDmaAttr.stErrDecCfg;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].wr_err_dec_unit = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].rd_err_dec_unit = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].wr_err_gen_thr = 1;
        stErrDecCfg->stDmaChErrDecCfg[DmaChIndex].rd_err_gen_thr = 1;
    }
	ISP_WRAP_DMA_ERR_STATUS_S *stErrStatus = &pstDmaAttr.stErrStatus;
    for(DmaChIndex=0; DmaChIndex < ISP_DMA_CH_NUM; DmaChIndex++)
    {
        stErrStatus->stDmaErrStatus[DmaChIndex].err_y_wr_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_uv_wr_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_raw_read_status = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_wr_rst_req = 0;
        stErrStatus->stDmaErrStatus[DmaChIndex].err_rd_rst_req = 0;
    }
    Isp_Drv_R2k_Wrap_SetDma(isp,&pstDmaAttr);
}
//
int isp_r2k_wrap_SetAxiCtl(struct isp_device *isp)
{
	ISP_CHECK_POINTER(isp);
    ISP_WRAP_AXI_CTL_S pstAxiCtl;
	pstAxiCtl.axi_wr_ch_rst_req = 1;
	pstAxiCtl.axi_rd_ch_rst_req = 1;
	pstAxiCtl.axi_wr_ch_rst_req = 1;
	pstAxiCtl.axi_rd_ch_state = 1;
    Isp_Drv_R2k_Wrap_SetAxiCtl(isp,&pstAxiCtl);
	return 0;
}
/*
*int mask
*/
int isp_r2k_wrap_SetIntMask(struct isp_device *isp)
{
	ISP_CHECK_POINTER(isp);
	ISP_WRAP_CORE_INT_CTL_S stCoreIntCtl;
    stCoreIntCtl.int_raw_in_mask= 1 ;  
    stCoreIntCtl.int_3a_mask= 1 ;      
    stCoreIntCtl.raw_int_mask= 1 ;     
    stCoreIntCtl.rgb_int_mask= 1 ;     
    stCoreIntCtl.yuv_int_mask= 1 ;     
    stCoreIntCtl.ldc_int_mask= 1 ;     
    stCoreIntCtl.main_out_int_mask= 1 ;
    stCoreIntCtl.isp_awb_int_mask= 1 ; 
    stCoreIntCtl.isp_ae_int_mask= 1 ;  
    stCoreIntCtl.isp_af_int_mask= 1 ; 
    Isp_Drv_R2k_Wrap_SetCoreIntCtlMask(isp,&stCoreIntCtl);
    ISP_WRAP_DMA_WR_INT_MASK0_S stDmaWRMask0;
    stDmaWRMask0.wr_3dnr_y_frm_end_int_mask= 1 ;    
    stDmaWRMask0.wr_3dnr_y_line_base_int_mask= 1 ;  
    stDmaWRMask0.wr_3dnr_y_err_frm_end_int_mask= 1 ;
    stDmaWRMask0.wr_3dnr_y_err_immediate_int_mask= 1 ;     
    stDmaWRMask0.wr_3dnr_uv_frm_end_int_mask= 1 ;   
    stDmaWRMask0.wr_3dnr_uv_line_base_int_mask= 1 ; 
    stDmaWRMask0.wr_3dnr_uv_err_frm_end_int_mask= 1 ;      
    stDmaWRMask0.wr_3dnr_uv_err_immediate_int_mask= 1 ;    
    stDmaWRMask0.ldc_wr_y_frm_end_int_mask= 1 ;     
    stDmaWRMask0.ldc_wr_y_line_base_int_mask= 1 ;   
    stDmaWRMask0.ldc_wr_y_err_frm_end_int_mask= 1 ; 
    stDmaWRMask0.ldc_wr_y_err_immediate_int_mask= 1 ;      
    stDmaWRMask0.ldc_wr_uv_frm_end_int_mask= 1 ;    
    stDmaWRMask0.ldc_wr_uv_line_base_int_mask= 1 ;  
    stDmaWRMask0.ldc_wr_uv_err_frm_end_int_mask= 1 ;
    stDmaWRMask0.ldc_wr_uv_err_immediate_int_mask= 1 ;     
    stDmaWRMask0.wdr_wr_raw_frm_end_int_mask= 1 ;   
    stDmaWRMask0.wdr_wr_raw_line_base_int_mask= 1 ; 
    stDmaWRMask0.wdr_wr_raw_err_frm_end_int_mask= 1 ;      
    stDmaWRMask0.wdr_wr_raw_err_immediate_int_mask= 1 ;    
    stDmaWRMask0.main_out_wr_y_frm_end_int_mask= 1 ;
    stDmaWRMask0.main_out_wr_y_line_base_int_mask= 1 ;     
    stDmaWRMask0.main_out_wr_y_err_frm_end_int_mask= 1 ;   
    stDmaWRMask0.main_out_wr_y_err_immediate_int_mask= 1 ; 
    stDmaWRMask0.main_out_wr_uv_frm_end_int_mask= 1 ;      
    stDmaWRMask0.main_out_wr_uv_line_base_int_mask= 1 ;    
    stDmaWRMask0.main_out_wr_uv_err_frm_end_int_mask= 1 ;  
    stDmaWRMask0.main_out_wr_uv_err_immediate_int_mask= 1 ;
    Isp_Drv_R2k_Wrap_SetDmaWRIntMask0(isp,&stDmaWRMask0);
    ISP_WRAP_DMA_WR_INT_MASK1_S stDmaWRMask1;
    stDmaWRMask1.ds0_out_wr_y_frm_end_mask= 1 ; 
    stDmaWRMask1.ds0_out_wr_y_line_base_mask= 1 ;      
    stDmaWRMask1.ds0_out_wr_y_err_frm_end_mask= 1 ;    
    stDmaWRMask1.ds0_out_wr_y_err_immediate_mask= 1 ;  
    stDmaWRMask1.ds0_out_wr_uv_frm_end_mask= 1 ;
    stDmaWRMask1.ds0_out_wr_uv_line_base_mask= 1 ;     
    stDmaWRMask1.ds0_out_wr_uv_err_frm_end_mask= 1 ;   
    stDmaWRMask1.ds0_out_wr_uv_err_immediate_mask= 1 ; 
    stDmaWRMask1.ds1_out_wr_y_frm_end_mask= 1 ; 
    stDmaWRMask1.ds1_out_wr_y_line_base_mask= 1 ;      
    stDmaWRMask1.ds1_out_wr_y_err_frm_end_mask= 1 ;    
    stDmaWRMask1.ds1_out_wr_y_err_immediate_mask= 1 ;  
    stDmaWRMask1.ds1_out_wr_uv_frm_end_mask= 1 ;
    stDmaWRMask1.ds1_out_wr_uv_line_base_mask= 1 ;     
    stDmaWRMask1.ds1_out_wr_uv_err_frm_end_mask= 1 ;   
    stDmaWRMask1.ds1_out_wr_uv_err_immediate_mask= 1 ; 
    stDmaWRMask1.ds2_out_wr_r_frm_end_mask= 1 ; 
    stDmaWRMask1.ds2_out_wr_r_line_base_mask= 1 ;      
    stDmaWRMask1.ds2_out_wr_r_err_frm_end_mask= 1 ;    
    stDmaWRMask1.ds2_out_wr_r_err_immediate_mask= 1 ;  
    stDmaWRMask1.ds2_out_wr_g_frm_end_mask= 1 ; 
    stDmaWRMask1.ds2_out_wr_g_line_base_mask= 1 ;      
    stDmaWRMask1.ds2_out_wr_g_err_frm_end_mask= 1 ;    
    stDmaWRMask1.ds2_out_wr_g_err_immediate_mask= 1 ;  
    stDmaWRMask1.ds2_out_wr_b_frm_end_mask= 1 ; 
    stDmaWRMask1.ds2_out_wr_b_line_base_mask= 1 ;      
    stDmaWRMask1.ds2_out_wr_b_err_frm_end_mask= 1 ;    
    stDmaWRMask1.ds2_out_wr_b_err_immediate_mask= 1 ; 
    Isp_Drv_R2k_Wrap_SetDmaWRIntMask1(isp,&stDmaWRMask1);
    ISP_WRAP_DMA_RD_INT_MASK0_S stDmaRDMask0;
    stDmaRDMask0.rd_3dnr_y_frm_end_int_mask= 1 ;
    stDmaRDMask0.rd_3dnr_y_line_base_int_mask= 1 ;     
    stDmaRDMask0.rd_3dnr_y_err_frm_end_int_mask= 1 ;   
    stDmaRDMask0.rd_3dnr_y_err_immediate_int_mask= 1 ; 
    stDmaRDMask0.rd_3dnr_uv_frm_end_int_mask= 1 ;      
    stDmaRDMask0.rd_3dnr_uv_line_base_int_mask= 1 ;    
    stDmaRDMask0.rd_3dnr_uv_err_frm_end_int_mask= 1 ;  
    stDmaRDMask0.rd_3dnr_uv_err_immediate_int_mask= 1 ;
    stDmaRDMask0.ldc_rd_y_frm_end_int_mask= 1 ; 
    stDmaRDMask0.ldc_rd_y_line_base_int_mask= 1 ;      
    stDmaRDMask0.ldc_rd_y_err_frm_end_int_mask= 1 ;    
    stDmaRDMask0.ldc_rd_y_err_immediate_int_mask= 1 ;  
    stDmaRDMask0.ldc_rd_uv_frm_end_int_mask= 1 ;
    stDmaRDMask0.ldc_rd_uv_line_base_int_mask= 1 ;     
    stDmaRDMask0.ldc_rd_uv_err_frm_end_int_mask= 1 ;   
    stDmaRDMask0.ldc_rd_uv_err_immediate_int_mask= 1 ; 
    stDmaRDMask0.wdr_rd_raw_frm_end_int_mask= 1 ;      
    stDmaRDMask0.wdr_rd_raw_line_base_int_mask= 1 ;    
    stDmaRDMask0.wdr_rd_raw_err_frm_end_int_mask= 1 ;  
    stDmaRDMask0.wdr_rd_raw_err_immediate_int_mask= 1 ;
    Isp_Drv_R2k_Wrap_SetDmaRDIntMask0(isp,&stDmaRDMask0);  
}
//
int isp_r2k_wrap_SetConfigDone(struct isp_device *isp)
{
	ISP_CHECK_POINTER(isp);
    ISP_WRAP_CONFIG_DONE_S pstConfigDone;
	pstConfigDone.int_polarity = 1;
	pstConfigDone.sen_reg_pro_en = 0;
	pstConfigDone.wrap_config_done_en = 1;
    Isp_Drv_R2k_Wrap_SetConfigdoneCtl(isp,&pstConfigDone);
	return 0;
}
//
void isp_r2k_wrap_GetCfg(ISP_WRAP_CFG_INFO *isp_wrap_cfg,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    ISP_CHECK_POINTER(isp_wrap_cfg);
    ISP_CHECK_POINTER(isp_addr);
    ISP_CHECK_POINTER(isp_size);
    //
	ISP_WRAP_LDC_S  *ldcInfo  = &isp_wrap_cfg->ldcInfo;
    ldcInfo->ldc_en             = isp_addr->ldc_en;
    ldcInfo->ldc_line_stride    = isp_addr->ldc_stride; 
    ldcInfo->ldc_y_buf_base     = isp_addr->ldc_addr; 
    ldcInfo->ldc_uv_buf_base    = isp_addr->ldc_addr + isp_addr->ldc_stride *isp_size->out_size.Height;
    //
	ISP_WRAP_MAIN_S	*mainInfo = &isp_wrap_cfg->mainInfo;
    mainInfo->main_out_en       = isp_addr->main_en;
    mainInfo->main_size.Width   = isp_size->out_size.Width;
    mainInfo->main_size.Height  = isp_size->out_size.Height;
    mainInfo->main_line_stride  = isp_addr->main_stride; 
    mainInfo->main_y_buf0_base  = isp_addr->main_out_addr;   
    mainInfo->main_y_buf1_base  = isp_addr->main_out_addr;
    mainInfo->main_uv_buf0_base = isp_addr->main_out_addr + mainInfo->main_line_stride * mainInfo->main_size.Height;   
    mainInfo->main_uv_buf1_base = isp_addr->main_out_addr + mainInfo->main_line_stride * mainInfo->main_size.Height; 

    //
	ISP_WRAP_DS0_S *ds0Info  = &isp_wrap_cfg->ds0Info;
    ds0Info->ds0_out_en         = isp_addr->ds0_en;
    ds0Info->ds0_osd0_en        = isp_addr->ds0_osd0_en;   
    ds0Info->ds0_osd1_en        = isp_addr->ds1_osd0_en; 
    ds0Info->ds0_osd2_en        = isp_addr->ds2_osd0_en;
    ds0Info->ds0_size.Width     = isp_size->ds0_size.Width;
    ds0Info->ds0_size.Height    = isp_size->ds0_size.Height; 
    ds0Info->ds0_line_stride    = isp_addr->ds0_stride;    
    ds0Info->ds0_y_buf0_base    = isp_addr->ds0_out_addr;   
    ds0Info->ds0_y_buf1_base    = isp_addr->ds0_out_addr;
    ds0Info->ds0_uv_buf0_base   = isp_addr->ds0_out_addr + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;   
    ds0Info->ds0_uv_buf1_base   = isp_addr->ds0_out_addr + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;  
    //
	ISP_WRAP_DS1_S *ds1Info  = &isp_wrap_cfg->ds1Info;
    ds1Info->ds1_out_en         = isp_addr->ds1_en;
    ds1Info->ds1_osd0_en        = isp_addr->ds1_osd0_en;   
    ds1Info->ds1_osd1_en        = isp_addr->ds1_osd1_en; 
    ds1Info->ds1_osd2_en        = isp_addr->ds1_osd2_en; 	
    ds1Info->ds1_size.Width     = isp_size->ds1_size.Width;
    ds1Info->ds1_size.Height    = isp_size->ds1_size.Height;
    ds1Info->ds1_line_stride    = isp_addr->ds1_stride;
    ds1Info->ds1_y_buf0_base    = isp_addr->ds1_out_addr;   
    ds1Info->ds1_y_buf1_base    = isp_addr->ds1_out_addr;
    ds1Info->ds1_uv_buf0_base   = isp_addr->ds1_out_addr + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;   
    ds1Info->ds1_uv_buf1_base   = isp_addr->ds1_out_addr + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;  
    //
	ISP_WRAP_DS2_S	*ds2Info  = &isp_wrap_cfg->ds2Info;
    ds2Info->ds2_out_en      = isp_addr->ds2_en;
    ds2Info->ds2_osd0_en     = isp_addr->ds2_osd0_en;   
    ds2Info->ds2_osd1_en     = isp_addr->ds2_osd1_en; 	
    ds2Info->ds2_size.Width  = isp_size->ds2_size.Width;
    ds2Info->ds2_size.Height = isp_size->ds2_size.Height;
    ds2Info->ds2_out_img_out_format  = isp_addr->ds2_rgb_type;
    if( OUT_ARGB == ds2Info->ds2_out_img_out_format)
    {
        ds2Info->ds2_r_buf0_base = isp_addr->ds2_out_r_addr;   
        ds2Info->ds2_r_buf1_base = isp_addr->ds2_out_r_addr;
        ds2Info->ds2_g_buf0_base = isp_addr->ds2_out_g_addr;//isp_addr->ds2_out_r_addr + isp_addr->ds2_rgb_stride*2;   
        ds2Info->ds2_g_buf1_base = isp_addr->ds2_out_g_addr;//isp_addr->ds2_out_r_addr + isp_addr->ds2_rgb_stride*2; 
        ds2Info->ds2_b_buf0_base = isp_addr->ds2_out_b_addr;//isp_addr->ds2_out_r_addr + isp_addr->ds2_rgb_stride*3;   
        ds2Info->ds2_b_buf1_base = isp_addr->ds2_out_b_addr;//isp_addr->ds2_out_r_addr + isp_addr->ds2_rgb_stride*3;      
        ds2Info->ds2_line_stride = isp_addr->ds2_rgb_stride*4;  
    }
    else
    { 

        ds2Info->ds2_r_buf0_base = isp_addr->ds2_out_r_addr;   
        ds2Info->ds2_r_buf1_base = isp_addr->ds2_out_r_addr;
        ds2Info->ds2_g_buf0_base = isp_addr->ds2_out_g_addr; //ds2Info->ds2_r_buf1_base + isp_addr->ds2_rgb_stride * ds2Info->ds2_size.ds2_rgb_stride;   // 320 * 240  
        ds2Info->ds2_g_buf1_base = isp_addr->ds2_out_g_addr; //ds2Info->ds2_r_buf1_base + isp_addr->ds2_rgb_stride * ds2Info->ds2_size.ds2_rgb_stride; 
        ds2Info->ds2_b_buf0_base = isp_addr->ds2_out_b_addr;//ds2Info->ds2_g_buf1_base + isp_addr->ds2_rgb_stride * ds2Info->ds2_size.ds2_rgb_stride;   
        ds2Info->ds2_b_buf1_base = isp_addr->ds2_out_b_addr;//ds2Info->ds2_g_buf1_base + isp_addr->ds2_rgb_stride * ds2Info->ds2_size.ds2_rgb_stride;      
        ds2Info->ds2_line_stride = isp_addr->ds2_rgb_stride;  
    }
}
//
void isp_r2k_print_wrapcfg(ISP_WRAP_CFG_INFO *isp_wrap_cfg)
{
    ISP_CHECK_POINTER(isp_wrap_cfg); 

    printf("isp_out_sel:0x%x\n",isp_wrap_cfg->isp_out_sel);
    printf("dvp_ch_mode:0x%x\n",isp_wrap_cfg->dvp_ch_mode);
    printf("hist_3a_out_en:0x%x\n",isp_wrap_cfg->hist_3a_out_en);
    //
    ISP_WRAP_LDC_S  *ldcInfo = &isp_wrap_cfg->ldcInfo;
    printf("ldc_en:0x%x\n",ldcInfo->ldc_en);
    printf("ldc_y_buf_base:0x%x\n",ldcInfo->ldc_y_buf_base); 
    printf("ldc_uv_buf_base:0x%x\n",ldcInfo->ldc_uv_buf_base); 
    printf("ldc_line_stride:0x%x\n",ldcInfo->ldc_line_stride); 
    printf("ldc_frame_buf_size:0x%x\n",ldcInfo->ldc_frame_buf_size);
    //
    ISP_WRAP_MAIN_S	*mainInfo = &isp_wrap_cfg->mainInfo;
    printf("main_out_en:0x%x\n",mainInfo->main_out_en);
    printf("Width:0x%x\n",mainInfo->main_size.Width);
    printf("Height:0x%x\n",mainInfo->main_size.Height);
    printf("main_pix_remap_en:0x%x\n",mainInfo->main_pix_remap_en);
    printf("main_out_img_format:0x%x\n",mainInfo->main_out_img_format);   
    printf("main_out_yuv_in_format:0x%x\n",mainInfo->main_out_yuv_in_format);   
    printf("main_out_img_out_format:0x%x\n",mainInfo->main_out_img_out_format);  
    printf("main_out_yuv422_pxl_order:0x%x\n",mainInfo->main_out_yuv422_pxl_order);
    printf("main_out_pxl_width:0x%x\n",mainInfo->main_out_pxl_width);	
    printf("main_y_buf0_base:0x%x\n",mainInfo->main_y_buf0_base);   
    printf("main_y_buf1_base:0x%x\n",mainInfo->main_y_buf1_base);
    printf("main_uv_buf0_base:0x%x\n",mainInfo->main_uv_buf0_base);   
    printf("main_uv_buf1_base:0x%x\n",mainInfo->main_uv_buf1_base); 
    printf("main_line_stride:0x%x\n",mainInfo->main_line_stride); 
    printf("main_frame_buf_size:0x%x\n",mainInfo->main_frame_buf_size);	
    //
    ISP_WRAP_DS0_S	*ds0Info = &isp_wrap_cfg->ds0Info;
    printf("ds0_out_en:0x%x\n",ds0Info->ds0_out_en);
    printf("ds0_osd0_en:0x%x\n",ds0Info->ds0_osd0_en );   
    printf("ds0_osd1_en:0x%x\n",ds0Info->ds0_osd1_en ); 
    printf("ds0_osd2_en :0x%x\n",ds0Info->ds0_osd2_en );
    printf("pix_remap_out0_en:0x%x\n",ds0Info->pix_remap_out0_en);		 	
    printf("Width:0x%x\n",ds0Info->ds0_size.Width);
    printf("Height:0x%x\n",ds0Info->ds0_size.Height);
    printf("ds0_out_img_format:0x%x\n",ds0Info->ds0_out_img_format);   
    printf("ds0_out_yuv_in_format:0x%x\n",ds0Info->ds0_out_yuv_in_format);   
    printf("ds0_out_img_out_format:0x%x\n",ds0Info->ds0_out_img_out_format);  
    printf("ds0_out_yuv422_pxl_order:0x%x\n",ds0Info->ds0_out_yuv422_pxl_order);
    printf("ds0_out_pxl_width:0x%x\n",ds0Info->ds0_out_pxl_width);	
    printf("ds0_y_buf0_base:0x%x\n",ds0Info->ds0_y_buf0_base);   
    printf("ds0_y_buf1_base:0x%x\n",ds0Info->ds0_y_buf1_base);
    printf("ds0_uv_buf0_base:0x%x\n",ds0Info->ds0_uv_buf0_base);   
    printf("ds0_uv_buf1_base:0x%x\n",ds0Info->ds0_uv_buf1_base);
    printf("ds0_line_stride:0x%x\n",ds0Info->ds0_line_stride);
    printf("ds0_frame_buf_size:0x%x\n",ds0Info->ds0_frame_buf_size);	     
    //
    ISP_WRAP_DS1_S	*ds1Info = &isp_wrap_cfg->ds1Info;
    printf("ds1_out_en:0x%x\n",ds1Info->ds1_out_en);
    printf("ds1_osd0_en:0x%x\n",ds1Info->ds1_osd0_en );   
    printf("ds1_osd1_en:0x%x\n",ds1Info->ds1_osd1_en ); 
    printf("ds1_osd2_en :0x%x\n",ds1Info->ds1_osd2_en );
    printf("pix_remap_out1_en:0x%x\n",ds1Info->pix_remap_out1_en);		 	
    printf("Width:0x%x\n",ds1Info->ds1_size.Width);
    printf("Height:0x%x\n",ds1Info->ds1_size.Height);
    printf("ds1_out_img_format:0x%x\n",ds1Info->ds1_out_img_format);   
    printf("ds1_out_yuv_in_format:0x%x\n",ds1Info->ds1_out_yuv_in_format);   
    printf("ds1_out_img_out_format:0x%x\n",ds1Info->ds1_out_img_out_format);  
    printf("ds1_out_yuv422_pxl_order:0x%x\n",ds1Info->ds1_out_yuv422_pxl_order);
    printf("ds1_out_pxl_width:0x%x\n",ds1Info->ds1_out_pxl_width);	
    printf("ds1_y_buf0_base:0x%x\n",ds1Info->ds1_y_buf0_base);   
    printf("ds1_y_buf1_base:0x%x\n",ds1Info->ds1_y_buf1_base);
    printf("ds1_uv_buf0_base:0x%x\n",ds1Info->ds1_uv_buf0_base);   
    printf("ds1_uv_buf1_base:0x%x\n",ds1Info->ds1_uv_buf1_base);
    printf("ds1_line_stride:0x%x\n",ds1Info->ds1_line_stride);
    printf("ds1_frame_buf_size:0x%x\n",ds1Info->ds1_frame_buf_size);	
    //
    ISP_WRAP_DS2_S	*ds2Info = &isp_wrap_cfg->ds2Info;
    printf("ds2_out_en:0x%x\n",ds2Info->ds2_out_en);
    printf("ds2_osd0_en :0x%x\n",ds2Info->ds2_osd0_en );   
    printf("ds2_osd1_en :0x%x\n",ds2Info->ds2_osd1_en ); 
    printf("ds2_osd2_en :0x%x\n",ds2Info->ds2_osd2_en ); 	 		
    printf("ds2_size:0x%x\n",ds2Info->ds2_size);
    printf("ds2_out_img_format:0x%x\n",ds2Info->ds2_out_img_format);   
    printf("ds2_out_yuv_in_format:0x%x\n",ds2Info->ds2_out_yuv_in_format);   
    printf("ds2_out_img_out_format:0x%x\n",ds2Info->ds2_out_img_out_format);  
    printf("ds2_out_yuv422_pxl_order:0x%x\n",ds2Info->ds2_out_yuv422_pxl_order);
    printf("ds2_out_pxl_width:0x%x\n",ds2Info->ds2_out_pxl_width);	
    printf("ds2_r_buf0_base:0x%x\n",ds2Info->ds2_r_buf0_base);   
    printf("ds2_r_buf1_base:0x%x\n",ds2Info->ds2_r_buf1_base);
    printf("ds2_g_buf0_base:0x%x\n",ds2Info->ds2_g_buf0_base);   
    printf("ds2_g_buf1_base:0x%x\n",ds2Info->ds2_g_buf1_base); 
    printf("ds2_b_buf0_base:0x%x\n",ds2Info->ds2_b_buf0_base);   
    printf("ds2_b_buf1_base:0x%x\n",ds2Info->ds2_b_buf1_base);      
    printf("ds2_line_stride:0x%x\n",ds2Info->ds2_line_stride); 
    printf("ds2_frame_buf_size:0x%x\n",ds2Info->ds2_frame_buf_size);	
    return;   
}
//
void isp_r2k_wrap_cfg(struct isp_r2k_device *r2k,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type)
{
	ISP_CHECK_POINTER(r2k);
    ISP_CHECK_POINTER(isp_addr);
    ISP_CHECK_POINTER(isp_size);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_WRAP_CFG_INFO  *isp_wrap_cfg =&r2k->isp_wrap_cfg;

    if( IMX385_SENSOR == sensor_type)
    {
        memcpy(isp_wrap_cfg,&imx385_wrap_info,sizeof(ISP_WRAP_CFG_INFO));    
    }
    else if(JFX23S_SENSOR == sensor_type)
    {
        memcpy(isp_wrap_cfg,&jfx23s_wrap_info,sizeof(ISP_WRAP_CFG_INFO));
    }

    isp_r2k_print_wrapcfg(isp_wrap_cfg);
    //
    isp_r2k_wrap_GetCfg(isp_wrap_cfg,isp_addr,isp_size);
    //
    isp_r2k_wrap_SetComRst(isp);
    //
    isp_r2k_wrap_SetDmaRst(isp);
    //
	unsigned int external_out_ch_sel = isp_wrap_cfg->isp_out_sel;
	Isp_Drv_R2k_Wrap_SetModeCtl_OutSel(isp,external_out_ch_sel);
    //
	unsigned int dvp_input_ch_type = isp_wrap_cfg->dvp_ch_mode;
	Isp_Drv_R2k_Wrap_SetModeCtl_DvpMode(isp,dvp_input_ch_type);
    //
    isp_r2k_wrap_SetPipeClkCtl(isp);
    //
	ISP_WRAP_LDC_S *ldcInfo = &isp_wrap_cfg->ldcInfo;
	isp_r2k_wrap_SetLdc(isp,ldcInfo);
    //
	ISP_WRAP_MAIN_S	*mainInfo = &isp_wrap_cfg->mainInfo;
	isp_r2k_wrap_SetMainOut(isp,mainInfo);
    //
	ISP_WRAP_DS0_S	  *ds0Info = &isp_wrap_cfg->ds0Info;
	isp_r2k_wrap_SetDs0Out(isp,ds0Info);
    //
	ISP_WRAP_DS1_S	  *ds1Info = &isp_wrap_cfg->ds1Info;
	isp_r2k_wrap_SetDs1Out(isp,ds1Info);
    //
	ISP_WRAP_DS2_S	  *ds2Info = &isp_wrap_cfg->ds2Info;

	isp_r2k_wrap_SetDs2Out(isp,ds2Info);
	//
	isp_r2k_wrap_SetDmaConfig(isp);
    //
	isp_r2k_wrap_SetAxiCtl(isp);
    //
	isp_r2k_wrap_SetIntMask(isp);
    //
	isp_r2k_wrap_SetConfigDone(isp);  
}
//
void isp_r2k_wrap_config(struct isp_r2k_device *r2k)
{
	ISP_CHECK_POINTER(r2k);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_WRAP_CFG_INFO  *isp_wrap_cfg =&r2k->isp_wrap_cfg;

    //
    isp_r2k_wrap_SetComRst(isp);
    //
    isp_r2k_wrap_SetDmaRst(isp);
    //
	unsigned int external_out_ch_sel = isp_wrap_cfg->isp_out_sel;
	Isp_Drv_R2k_Wrap_SetModeCtl_OutSel(isp,external_out_ch_sel);
    //
	unsigned int dvp_input_ch_type = isp_wrap_cfg->dvp_ch_mode;
	Isp_Drv_R2k_Wrap_SetModeCtl_DvpMode(isp,dvp_input_ch_type);
    //
    isp_r2k_wrap_SetPipeClkCtl(isp);
    //
	ISP_WRAP_LDC_S *ldcInfo = &isp_wrap_cfg->ldcInfo;
	isp_r2k_wrap_SetLdc(isp,ldcInfo);
    //
	ISP_WRAP_MAIN_S	*mainInfo = &isp_wrap_cfg->mainInfo;
	isp_r2k_wrap_SetMainOut(isp,mainInfo);
    //
	ISP_WRAP_DS0_S	  *ds0Info = &isp_wrap_cfg->ds0Info;
	isp_r2k_wrap_SetDs0Out(isp,ds0Info);
    //
	ISP_WRAP_DS1_S	  *ds1Info = &isp_wrap_cfg->ds1Info;
	isp_r2k_wrap_SetDs1Out(isp,ds1Info);
    //
	ISP_WRAP_DS2_S	  *ds2Info = &isp_wrap_cfg->ds2Info;

	isp_r2k_wrap_SetDs2Out(isp,ds2Info);
	//
	isp_r2k_wrap_SetDmaConfig(isp);
    //
	isp_r2k_wrap_SetAxiCtl(isp);
    //
	isp_r2k_wrap_SetIntMask(isp);
    //
	isp_r2k_wrap_SetConfigDone(isp);  
}
/****************************************************************************
*wrap int
*****************************************************************************/
int isp_r2k_wrap_setIntCore(struct isp_device *isp,ISP_WRAP_INT_CORE_S *intCoreEn)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(intCoreEn);
    ISP_WRAP_CORE_INT_CTL_S coreIntMask;
    coreIntMask.int_raw_in_mask = ~intCoreEn->int_raw_in_en;  
    coreIntMask.int_3a_mask = ~intCoreEn->int_3a_en;      
    coreIntMask.raw_int_mask = ~intCoreEn->raw_int_en;     
    coreIntMask.rgb_int_mask = ~intCoreEn->rgb_int_en;     
    coreIntMask.yuv_int_mask = ~intCoreEn->yuv_int_en;     
    coreIntMask.ldc_int_mask = ~intCoreEn->ldc_int_en;     
    coreIntMask.main_out_int_mask = ~intCoreEn->main_out_int_en;
    coreIntMask.isp_awb_int_mask = ~intCoreEn->isp_awb_int_en; 
    coreIntMask.isp_ae_int_mask = ~intCoreEn->isp_ae_int_en;  
    coreIntMask.isp_af_int_mask = ~intCoreEn->isp_af_int_en;  
	Isp_Drv_R2k_Wrap_SetCoreIntCtlMask(isp,&coreIntMask);
	return 0;
};
//
int isp_r2k_wrap_setIntWr0(struct isp_device *isp,ISP_WRAP_INT_WR0_S *intWr0En)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(intWr0En);
    ISP_WRAP_DMA_WR_INT_MASK0_S wrIntMask0;
    wrIntMask0.wr_3dnr_y_frm_end_int_mask = ~intWr0En->wr_3dnr_y_frm_end_int_en;    
    wrIntMask0.wr_3dnr_y_line_base_int_mask = ~intWr0En->wr_3dnr_y_line_base_int_en;  
    wrIntMask0.wr_3dnr_y_err_frm_end_int_mask = ~intWr0En->wr_3dnr_y_err_frm_end_int_en;
    wrIntMask0.wr_3dnr_y_err_immediate_int_mask = ~intWr0En->wr_3dnr_y_err_immediate_int_en;     
    wrIntMask0.wr_3dnr_uv_frm_end_int_mask = ~intWr0En->wr_3dnr_uv_frm_end_int_en;   
    wrIntMask0.wr_3dnr_uv_line_base_int_mask = ~intWr0En->wr_3dnr_uv_line_base_int_en; 
    wrIntMask0.wr_3dnr_uv_err_frm_end_int_mask = ~intWr0En->wr_3dnr_uv_err_frm_end_int_en;      
    wrIntMask0.wr_3dnr_uv_err_immediate_int_mask = ~intWr0En->wr_3dnr_uv_err_immediate_int_en;    
    wrIntMask0.ldc_wr_y_frm_end_int_mask = ~intWr0En->ldc_wr_y_frm_end_int_en;     
    wrIntMask0.ldc_wr_y_line_base_int_mask = ~intWr0En->ldc_wr_y_line_base_int_en;   
    wrIntMask0.ldc_wr_y_err_frm_end_int_mask = ~intWr0En->ldc_wr_y_err_frm_end_int_en; 
    wrIntMask0.ldc_wr_y_err_immediate_int_mask = ~intWr0En->ldc_wr_y_err_immediate_int_en;      
    wrIntMask0.ldc_wr_uv_frm_end_int_mask = ~intWr0En->ldc_wr_uv_frm_end_int_en;    
    wrIntMask0.ldc_wr_uv_line_base_int_mask = ~intWr0En->ldc_wr_uv_line_base_int_en;  
    wrIntMask0.ldc_wr_uv_err_frm_end_int_mask = ~intWr0En->ldc_wr_uv_err_frm_end_int_en;
    wrIntMask0.ldc_wr_uv_err_immediate_int_mask = ~intWr0En->ldc_wr_uv_err_immediate_int_en;     
    wrIntMask0.wdr_wr_raw_frm_end_int_mask = ~intWr0En->wdr_wr_raw_frm_end_int_en;   
    wrIntMask0.wdr_wr_raw_line_base_int_mask = ~intWr0En->wdr_wr_raw_line_base_int_en; 
    wrIntMask0.wdr_wr_raw_err_frm_end_int_mask = ~intWr0En->wdr_wr_raw_err_frm_end_int_en;      
    wrIntMask0.wdr_wr_raw_err_immediate_int_mask = ~intWr0En->wdr_wr_raw_err_immediate_int_en; 
    wrIntMask0.main_out_wr_y_frm_end_int_mask = ~intWr0En->main_out_wr_y_frm_end_int_en;
    wrIntMask0.main_out_wr_y_line_base_int_mask = ~intWr0En->main_out_wr_y_line_base_int_en;     
    wrIntMask0.main_out_wr_y_err_frm_end_int_mask = ~intWr0En->main_out_wr_y_err_frm_end_int_en;   
    wrIntMask0.main_out_wr_y_err_immediate_int_mask = ~intWr0En->main_out_wr_y_err_immediate_int_en; 
    wrIntMask0.main_out_wr_uv_frm_end_int_mask = ~intWr0En->main_out_wr_uv_frm_end_int_en;      
    wrIntMask0.main_out_wr_uv_line_base_int_mask = ~intWr0En->main_out_wr_uv_line_base_int_en;    
    wrIntMask0.main_out_wr_uv_err_frm_end_int_mask = ~intWr0En->main_out_wr_uv_err_frm_end_int_en;  
    wrIntMask0.main_out_wr_uv_err_immediate_int_mask = ~intWr0En->main_out_wr_uv_err_immediate_int_en;
	Isp_Drv_R2k_Wrap_SetDmaWRIntMask0(isp,&wrIntMask0);
	return 0;
}
//
int isp_r2k_wrap_setIntWr1(struct isp_device *isp,ISP_WRAP_INT_WR1_S *intWr1En)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(intWr1En);
    ISP_WRAP_DMA_WR_INT_MASK1_S wrIntMask1;
	wrIntMask1.ds0_out_wr_y_frm_end_mask = ~intWr1En->ds0_out_wr_y_frm_end_en;
	wrIntMask1.ds0_out_wr_y_line_base_mask = ~intWr1En->ds0_out_wr_y_line_base_en;     
	wrIntMask1.ds0_out_wr_y_err_frm_end_mask = ~intWr1En->ds0_out_wr_y_err_frm_end_en;   
	wrIntMask1.ds0_out_wr_y_err_immediate_mask = ~intWr1En->ds0_out_wr_y_err_immediate_en; 
	wrIntMask1.ds0_out_wr_uv_frm_end_mask = ~intWr1En->ds0_out_wr_uv_frm_end_en;      
	wrIntMask1.ds0_out_wr_uv_line_base_mask = ~intWr1En->ds0_out_wr_uv_line_base_en;    
	wrIntMask1.ds0_out_wr_uv_err_frm_end_mask = ~intWr1En->ds0_out_wr_uv_err_frm_end_en;  
	wrIntMask1.ds0_out_wr_uv_err_immediate_mask = ~intWr1En->ds0_out_wr_uv_err_immediate_en;
	wrIntMask1.ds1_out_wr_y_frm_end_mask = ~intWr1En->ds1_out_wr_y_frm_end_en;
	wrIntMask1.ds1_out_wr_y_line_base_mask = ~intWr1En->ds1_out_wr_y_line_base_en;     
	wrIntMask1.ds1_out_wr_y_err_frm_end_mask = ~intWr1En->ds1_out_wr_y_err_frm_end_en;   
	wrIntMask1.ds1_out_wr_y_err_immediate_mask = ~intWr1En->ds1_out_wr_y_err_immediate_en; 
	wrIntMask1.ds1_out_wr_uv_frm_end_mask = ~intWr1En->ds1_out_wr_uv_frm_end_en;      
	wrIntMask1.ds1_out_wr_uv_line_base_mask = ~intWr1En->ds1_out_wr_uv_line_base_en;    
	wrIntMask1.ds1_out_wr_uv_err_frm_end_mask = ~intWr1En->ds1_out_wr_uv_err_frm_end_en;  
	wrIntMask1.ds1_out_wr_uv_err_immediate_mask = ~intWr1En->ds1_out_wr_uv_err_immediate_en;
	wrIntMask1.ds2_out_wr_r_frm_end_mask = ~intWr1En->ds2_out_wr_r_frm_end_en;
	wrIntMask1.ds2_out_wr_r_line_base_mask = ~intWr1En->ds2_out_wr_r_line_base_en;     
	wrIntMask1.ds2_out_wr_r_err_frm_end_mask = ~intWr1En->ds2_out_wr_r_err_frm_end_en;   
	wrIntMask1.ds2_out_wr_r_err_immediate_mask = ~intWr1En->ds2_out_wr_r_err_immediate_en; 
	wrIntMask1.ds2_out_wr_g_frm_end_mask = ~intWr1En->ds2_out_wr_g_frm_end_en;
	wrIntMask1.ds2_out_wr_g_line_base_mask = ~intWr1En->ds2_out_wr_g_line_base_en;     
	wrIntMask1.ds2_out_wr_g_err_frm_end_mask = ~intWr1En->ds2_out_wr_g_err_frm_end_en;   
	wrIntMask1.ds2_out_wr_g_err_immediate_mask = ~intWr1En->ds2_out_wr_g_err_immediate_en; 
	wrIntMask1.ds2_out_wr_b_frm_end_mask = ~intWr1En->ds2_out_wr_b_frm_end_en;
	wrIntMask1.ds2_out_wr_b_line_base_mask = ~intWr1En->ds2_out_wr_b_line_base_en;     
	wrIntMask1.ds2_out_wr_b_err_frm_end_mask = ~intWr1En->ds0_out_wr_uv_err_frm_end_en;   
	wrIntMask1.ds2_out_wr_b_err_immediate_mask = ~intWr1En->ds0_out_wr_uv_err_immediate_en;   
	Isp_Drv_R2k_Wrap_SetDmaWRIntMask1(isp,&wrIntMask1);
	return 0;
}
//
int isp_r2k_wrap_setIntRd0(struct isp_device *isp,ISP_WRAP_INT_RD0_S *intRd0En)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(intRd0En);
    ISP_WRAP_DMA_RD_INT_MASK0_S rdIntMask0;
    rdIntMask0.rd_3dnr_y_frm_end_int_mask = ~intRd0En->rd_3dnr_y_frm_end_int_en;
    rdIntMask0.rd_3dnr_y_line_base_int_mask = ~intRd0En->rd_3dnr_y_line_base_int_en;     
    rdIntMask0.rd_3dnr_y_err_frm_end_int_mask = ~intRd0En->rd_3dnr_y_err_frm_end_int_en;   
    rdIntMask0.rd_3dnr_y_err_immediate_int_mask = ~intRd0En->rd_3dnr_y_err_immediate_int_en; 
    rdIntMask0.rd_3dnr_uv_frm_end_int_mask = ~intRd0En->rd_3dnr_uv_frm_end_int_en;      
    rdIntMask0.rd_3dnr_uv_line_base_int_mask = ~intRd0En->rd_3dnr_uv_line_base_int_en;    
    rdIntMask0.rd_3dnr_uv_err_frm_end_int_mask = ~intRd0En->rd_3dnr_uv_err_frm_end_int_en;  
    rdIntMask0.rd_3dnr_uv_err_immediate_int_mask = ~intRd0En->rd_3dnr_uv_err_immediate_int_en;
    rdIntMask0.ldc_rd_y_frm_end_int_mask = ~intRd0En->ldc_rd_y_frm_end_int_en; 
    rdIntMask0.ldc_rd_y_line_base_int_mask = ~intRd0En->ldc_rd_y_line_base_int_en;      
    rdIntMask0.ldc_rd_y_err_frm_end_int_mask = ~intRd0En->ldc_rd_y_err_frm_end_int_en;    
    rdIntMask0.ldc_rd_y_err_immediate_int_mask = ~intRd0En->ldc_rd_y_err_immediate_int_en;  
    rdIntMask0.ldc_rd_uv_frm_end_int_mask = ~intRd0En->ldc_rd_uv_frm_end_int_en;
    rdIntMask0.ldc_rd_uv_line_base_int_mask = ~intRd0En->ldc_rd_uv_line_base_int_en;     
    rdIntMask0.ldc_rd_uv_err_frm_end_int_mask = ~intRd0En->ldc_rd_uv_err_frm_end_int_en;   
    rdIntMask0.ldc_rd_uv_err_immediate_int_mask = ~intRd0En->ldc_rd_uv_err_immediate_int_en; 
    rdIntMask0.wdr_rd_raw_frm_end_int_mask = ~intRd0En->wdr_rd_raw_frm_end_int_en;      
    rdIntMask0.wdr_rd_raw_line_base_int_mask = ~intRd0En->wdr_rd_raw_line_base_int_en;    
    rdIntMask0.wdr_rd_raw_err_frm_end_int_mask = ~intRd0En->wdr_rd_raw_err_frm_end_int_en;  
    rdIntMask0.wdr_rd_raw_err_immediate_int_mask = ~intRd0En->wdr_rd_raw_err_immediate_int_en;
	Isp_Drv_R2k_Wrap_SetDmaRDIntMask0(isp,&rdIntMask0);
	return 0;
}
/*********************************************************************************
 * ISP CORE
**********************************************************************************/
//ITC
static int isp_r2k_core_SetItc(struct isp_device *isp,ITC_INFO_S *itcInfo)
{
	ISP_CHECK_POINTER(itcInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_ITC_CTL_S stItcCtl;
	stItcCtl.hsync_pol = itcInfo->hsync_pol;    
    stItcCtl.vsync_pol = itcInfo->vsync_pol;    
    stItcCtl.hsync_input_timing = itcInfo->hsync_input_timing;  
    stItcCtl.vsync_input_timing = itcInfo->vsync_input_timing;
    stItcCtl.mirror_ctl = itcInfo->flip_ctl;  
    stItcCtl.video_format_ctl = itcInfo->video_fmt_sel; 
    Isp_Drv_R2k_Core_SetItcCtl(isp,&stItcCtl);
	return 0;
}
//IMAGE
static int isp_r2k_core_SetImage(struct isp_device *isp,ITC_INFO_S *itcInfo)
{
	ISP_CHECK_POINTER(itcInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_IMAGE_ATTR_S stImgAttr;
    stImgAttr.image_height = itcInfo->total_size.Height - 1;
    stImgAttr.image_width = itcInfo->total_size.Width - 1; 
    stImgAttr.image_v_start = itcInfo->itc_size.Height_st;      
    stImgAttr.image_h_start = itcInfo->itc_size.Width_st;      
    stImgAttr.image_active_width = itcInfo->itc_size.Width; 
    stImgAttr.image_active_height = itcInfo->itc_size.Height;
    Isp_Drv_R2k_Core_SetImageAttr(isp,&stImgAttr);
	return 0;
}
//TPG
static int isp_r2k_core_SetTpgCtl(struct isp_device *isp,TPG_INFO_S *tpgInfo)
{
	ISP_CHECK_POINTER(tpgInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_TEST_CTL_S stTestCtl;
	stTestCtl.test_pattern_en = tpgInfo->tpg_en;
	stTestCtl.bayer_mode_sel = tpgInfo->bayer_mode_sel;
	stTestCtl.motion_mode_sel = tpgInfo->motion_mode_sel;
	stTestCtl.test_pattern_sel = tpgInfo->tpg_sel;
	stTestCtl.wdr_l_mul_data = tpgInfo->wdr_l_mul_data;
	stTestCtl.wdr_m_mul_data = tpgInfo->wdr_m_mul_data;
	stTestCtl.wdr_s_mul_data = tpgInfo->wdr_s_mul_data; 
    Isp_Drv_R2k_Core_SetTestCtl(isp,&stTestCtl);
	return 0;
}
//BLC
static int isp_r2k_core_SetBlcCtl(struct isp_device *isp,BLC_INFO_S *blcInfo)
{
	ISP_CHECK_POINTER(blcInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_BLC_CTL_S stBlcCtl;
	stBlcCtl.blc_en = blcInfo->blc_en;
	stBlcCtl.blc_offset = blcInfo->blc_offset;
	stBlcCtl.blc_ratio = blcInfo->blc_ratio;
    Isp_Drv_R2k_Core_SetBlcCtl(isp,&stBlcCtl);
	return 0;
}
//LSC
static int isp_r2k_core_SetLscCtl(struct isp_device *isp,LSC_INFO_S *lscInfo)
{
	ISP_CHECK_POINTER(lscInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_LSC_CTL_S stLscCtl;
    stLscCtl.lsc_en = lscInfo->lsc_en; 
    stLscCtl.lsc_h_center = lscInfo->lsc_h_center;     
    stLscCtl.lsc_v_center = lscInfo->lsc_v_center;
    stLscCtl.lsc_red_ratio = lscInfo->lsc_r_ratio;
    stLscCtl.lsc_green_ratio = lscInfo->lsc_g_ratio;  
    stLscCtl.lsc_blue_ratio = lscInfo->lsc_b_ratio;   
    stLscCtl.lsc_ir_ratio = lscInfo->lsc_ir_ratio;  
    Isp_Drv_R2k_Core_SetLscCtl(isp,&stLscCtl);
	return 0;
}
//AE
static int isp_r2k_core_SetAeCtl(struct isp_device *isp,AE_INFO_S *aeInfo)
{
	ISP_CHECK_POINTER(aeInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_AE_CTL_S stAeCtl;
    stAeCtl.ae_as_en = aeInfo->ae_as_en;       
    stAeCtl.ae_ag_en = aeInfo->ae_ag_en;       
    stAeCtl.ae_airis_en = aeInfo->ae_airis_en;    
    stAeCtl.ae_enter_ls_sel = aeInfo->ae_enter_ls_sel;
    stAeCtl.ae_exit_ls_sel = aeInfo->ae_exit_ls_sel; 
    stAeCtl.ae_win_mode_sel = aeInfo->ae_win_mode_sel;
    stAeCtl.ae_back_light_mode_sel = aeInfo->ae_back_light_mode_sel;
    stAeCtl.ae_day_change_en = aeInfo->ae_day_change_en;    
    stAeCtl.ae_day_change_sel = aeInfo->ae_day_change_sel;     
    stAeCtl.ae_win_h_start = aeInfo->ae_win_size.h_start;
    stAeCtl.ae_win_v_start = aeInfo->ae_win_size.v_start;
    stAeCtl.ae_win_h_end = aeInfo->ae_win_size.h_end;  
    stAeCtl.ae_win_v_end = aeInfo->ae_win_size.v_end;  
    stAeCtl.ae_tar_bright = aeInfo->ae_tar_bright;      
    stAeCtl.ae_tar_bright_range = aeInfo->ae_tar_bright_range;
    stAeCtl.ae_l_ex_time = aeInfo->ae_l_ex_time;
    stAeCtl.ae_m_ex_time = aeInfo->ae_m_ex_time;
    stAeCtl.ae_s_ex_time = aeInfo->ae_s_ex_time;
    stAeCtl.ae_agc = aeInfo->ae_agc;     
    stAeCtl.ae_ad_shuttle_freq = aeInfo->ae_ad_shuttle_freq;
    stAeCtl.ae_ad_gain_freq = aeInfo->ae_ad_gain_freq;
    stAeCtl.ae_adjust_step_max = aeInfo->ae_adjust_step_max;
    stAeCtl.ae_ex_value_max = aeInfo->ae_ex_value_max;  
    stAeCtl.ae_ex_value_mid = aeInfo->ae_ex_value_mid;    
    stAeCtl.ae_ex_value_min = aeInfo->ae_ex_value_min; 
    stAeCtl.ae_gain_value_max = aeInfo->ae_gain_value_max;    
    stAeCtl.ae_gain_value_mid = aeInfo->ae_gain_value_mid;
    stAeCtl.ae_gain_value_min = aeInfo->ae_gain_value_min;
    stAeCtl.ae_dn_switch_ad_step_max = aeInfo->ae_dn_switch_ad_step_max;
    stAeCtl.ae_dn_switch_wait_time = aeInfo->ae_dn_switch_wait_time;
    stAeCtl.ape_max_diff = aeInfo->ape_max_diff;
    stAeCtl.ape_drv_signal_max = aeInfo->ape_drv_signal_max;    
    stAeCtl.ape_coeff_distance = aeInfo->ape_coeff_distance;    
    stAeCtl.ape_coeff_speed = aeInfo->ape_coeff_speed;
    stAeCtl.ape_coeff_acceleration = aeInfo->ape_coeff_acceleration;
    stAeCtl.ape_drv_manual_value = aeInfo->ape_drv_manual_value;  
    stAeCtl.ape_damp_manual_value = aeInfo->ape_damp_manual_value;
    Isp_Drv_R2k_Core_SetAeCtl(isp,&stAeCtl);
	return 0;
}
//AWB
static int isp_r2k_core_SetAwbCtl(struct isp_device *isp,AWB_INFO_S *awbInfo)
{
	ISP_CHECK_POINTER(awbInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_AWB_CTL_S stAwbCtl;
    stAwbCtl.awb_d65_en = awbInfo->awb_d65_en; 
    stAwbCtl.awb_ccm_en = awbInfo->awb_ccm_en; 
    stAwbCtl.awb_en = awbInfo->awb_en;     
    stAwbCtl.awb_mode_sel = awbInfo->awb_mode_sel;
    stAwbCtl.awb_hist_mode_sel = awbInfo->awb_hist_mode_sel;
    stAwbCtl.awb_veri_en = awbInfo->awb_veri_en;      
    stAwbCtl.awb_mode_sel = awbInfo->awb_mode_sel;     
    stAwbCtl.awb_value_save_en = awbInfo->awb_value_save_en;
    stAwbCtl.awb_ccm_adp_adjust_en = awbInfo->awb_ccm_adp_adjust_en;
    stAwbCtl.awb_stab_en = awbInfo->awb_stab_en;   
    stAwbCtl.awb_d65_red_gain = awbInfo->awb_d65_red_gain;
    stAwbCtl.awb_d65_blue_gain = awbInfo->awb_d65_blue_gain;
    stAwbCtl.ccm_rr_coff = awbInfo->ccm_coff[0][0];
    stAwbCtl.ccm_rg_coff = awbInfo->ccm_coff[0][1];
    stAwbCtl.ccm_rb_coff = awbInfo->ccm_coff[0][2];
    stAwbCtl.ccm_gr_coff = awbInfo->ccm_coff[1][0];
    stAwbCtl.ccm_gg_coff = awbInfo->ccm_coff[1][1];
    stAwbCtl.ccm_gb_coff = awbInfo->ccm_coff[1][2];
    stAwbCtl.ccm_br_coff = awbInfo->ccm_coff[2][0];
    stAwbCtl.ccm_bg_coff = awbInfo->ccm_coff[2][1];
    stAwbCtl.ccm_bb_coff = awbInfo->ccm_coff[2][2];
    stAwbCtl.ccm_correct_coff = awbInfo->ccm_correct_coff;
    stAwbCtl.awb_win_h_start = awbInfo->awb_win_size.h_start;
    stAwbCtl.awb_win_v_start = awbInfo->awb_win_size.v_start;
    stAwbCtl.awb_win_h_end = awbInfo->awb_win_size.h_end;  
    stAwbCtl.awb_win_v_end = awbInfo->awb_win_size.v_end;  
    stAwbCtl.awb_correct_diff_th = awbInfo->awb_correct_diff_th;     
    stAwbCtl.awb_color_changeres_time = awbInfo->awb_color_changeres_time;
    stAwbCtl.awb_historgram_th = awbInfo->awb_historgram_th;
    stAwbCtl.awb_red_gain_adjust = awbInfo->awb_red_gain_adjust;     
    stAwbCtl.awb_green_gain_adjust = awbInfo->awb_green_gain_adjust;   
    stAwbCtl.awb_blue_gain_adjust = awbInfo->awb_blue_gain_adjust;
    stAwbCtl.awb_red_max_value = awbInfo->awb_red_max_value;
    stAwbCtl.awb_blue_max_value = awbInfo->awb_blue_max_value;      
    stAwbCtl.awb_red_min_value = awbInfo->awb_red_min_value;
    stAwbCtl.awb_blue_min_value = awbInfo->awb_blue_min_value;
    stAwbCtl.awb_red_obj_value = awbInfo->awb_red_obj_value;
    stAwbCtl.awb_blue_obj_value = awbInfo->awb_blue_obj_value;
    Isp_Drv_R2k_Core_SetAwbCtl(isp,&stAwbCtl);
	return 0;
}
//CSC
static int isp_r2k_core_SetCscCtl(struct isp_device *isp,CSC_INFO_S *cscInfo)
{
	ISP_CHECK_POINTER(cscInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_CSC_CTL_S stCscCtl;
    stCscCtl.csc_r2y_00 = cscInfo->csc_r2y[0][0];
    stCscCtl.csc_r2y_01 = cscInfo->csc_r2y[0][1];
    stCscCtl.csc_r2y_02 = cscInfo->csc_r2y[0][2];
    stCscCtl.csc_r2y_10 = cscInfo->csc_r2y[1][0];
    stCscCtl.csc_r2y_11 = cscInfo->csc_r2y[1][1];
    stCscCtl.csc_r2y_12 = cscInfo->csc_r2y[1][2];
    stCscCtl.csc_r2y_20 = cscInfo->csc_r2y[2][0];
    stCscCtl.csc_r2y_21 = cscInfo->csc_r2y[2][1];
    stCscCtl.csc_r2y_22 = cscInfo->csc_r2y[2][2];
    Isp_Drv_R2k_Core_SetCscCtl(isp,&stCscCtl);
	return 0;
}
//ADA
static int isp_r2k_core_SetAdaCtl(struct isp_device *isp,ADA_INFO_S *adaInfo)
{
	ISP_CHECK_POINTER(adaInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_ADA_CTL_S stAdaCtl;
    stAdaCtl.ada_rgb_gamma_en = adaInfo->ada_rgb_gamma_en; 
    stAdaCtl.ada_yuv_gamma_en = adaInfo->ada_yuv_gamma_en; 
    stAdaCtl.ada_adjust_en = adaInfo->ada_adjust_en;    
    stAdaCtl.ada_img_stab_en = adaInfo->ada_img_stab_en;
    stAdaCtl.ada_ccr_en = adaInfo->ada_ccr_en;
    stAdaCtl.ada_adp_en = adaInfo->ada_adp_en;
    stAdaCtl.ada_adp_ccr_en = adaInfo->ada_adp_ccr_en;   
    stAdaCtl.ada_stat_mode_sel = adaInfo->ada_stat_mode_sel;
    stAdaCtl.ada_enh_mode_sel = adaInfo->ada_enh_mode_sel;
    stAdaCtl.ada_stat_max_value = adaInfo->ada_stat_max_value; 
    stAdaCtl.ada_ad_stren_max_value = adaInfo->ada_ad_stren_max_value;
    stAdaCtl.ada_win_h_start = adaInfo->ada_win_size.h_start;
    stAdaCtl.ada_win_v_start = adaInfo->ada_win_size.v_start;
    stAdaCtl.ada_win_h_end = adaInfo->ada_win_size.h_end;  
    stAdaCtl.ada_win_v_end = adaInfo->ada_win_size.v_end; 
    Isp_Drv_R2k_Core_SetAdaCtl(isp,&stAdaCtl);
	return 0;
}
//RGBIR
static int isp_r2k_core_SetRgbirCtl(struct isp_device *isp,RGBIR_INFO_S *rgbirInfo)
{
	ISP_CHECK_POINTER(rgbirInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_RGBIR_CTL_S stRgbirCtl;
    stRgbirCtl.rgbir_en = rgbirInfo->rgbir_en; 
    stRgbirCtl.rgbir_rtf_en = rgbirInfo->rgbir_rtf_en;    
    stRgbirCtl.rgbir_rpc_en = rgbirInfo->rgbir_rpc_en;    
    stRgbirCtl.rgbir_fusion_en = rgbirInfo->rgbir_fusion_en;
    stRgbirCtl.rgbir_output_sel = rgbirInfo->rgbir_output_sel;
    stRgbirCtl.rgbir_rpc_max_value = rgbirInfo->rgbir_rpc_max_value; 
    stRgbirCtl.rgbir_rpc_color_coff = rgbirInfo->rgbir_rpc_color_coff;
    stRgbirCtl.rgbir_rpc_luma_coff = rgbirInfo->rgbir_rpc_luma_coff; 
    stRgbirCtl.rgbir_rpc_th = rgbirInfo->rgbir_rpc_th;
    stRgbirCtl.rgbir_rpc_th1 = rgbirInfo->rgbir_rpc_th1; 
    Isp_Drv_R2k_Core_SetRgbIrCtl(isp,&stRgbirCtl);
	return 0;
}
//2DNR
static int isp_r2k_core_Set2dnrCtl(struct isp_device *isp,NR2D_INFO_S *nr2dInfo)
{
	ISP_CHECK_POINTER(nr2dInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_2DNR_CTL_S st2dnrCtl;
    st2dnrCtl.core_2dnr_pcf_en = nr2dInfo->d2nr_pcf_en;
    st2dnrCtl.core_2dnr_raw_en = nr2dInfo->d2nr_raw_en;
    st2dnrCtl.core_2dnr_edge_en = nr2dInfo->d2nr_edge_en;      
    st2dnrCtl.core_2dnr_bap_en = nr2dInfo->d2nr_bap_en;
    st2dnrCtl.core_2dnr_luma_en = nr2dInfo->d2nr_luma_en;      
    st2dnrCtl.core_2dnr_chroma_en = nr2dInfo->d2nr_chroma_en;    
    st2dnrCtl.core_2dnr_pcf_adp_en = nr2dInfo->d2nr_pcf_adp_en;   
    st2dnrCtl.core_2dnr_raw_adp_en = nr2dInfo->d2nr_raw_adp_en;   
    st2dnrCtl.core_2dnr_luma_adp_en = nr2dInfo->d2nr_luma_adp_en;  
    st2dnrCtl.core_2dnr_chroma_adp_en = nr2dInfo->d2nr_chroma_adp_en;
    st2dnrCtl.core_2dnr_raw_intensity = nr2dInfo->d2nr_raw_intensity;
    st2dnrCtl.core_2dnr_bap_intensity = nr2dInfo->d2nr_bap_intensity;
    st2dnrCtl.core_2dnr_edge_intensity = nr2dInfo->d2nr_edge_intensity;
    st2dnrCtl.core_2dnr_luma_intensity = nr2dInfo->d2nr_luma_intensity;
    st2dnrCtl.core_2dnr_chroma_intensity = nr2dInfo->d2nr_chroma_intensity;
    Isp_Drv_R2k_Core_Set2DnrCtl(isp,&st2dnrCtl);
	return 0;
}
//ENH
static int isp_r2k_core_SetEnhCtl(struct isp_device *isp,ENH_INFO_S *enhInfo)
{
	ISP_CHECK_POINTER(enhInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_ENH_CTL_S stEnhCtl;
    stEnhCtl.enh_ltm_en = enhInfo->enh_ltm_en;
    stEnhCtl.enh_sharp_en = enhInfo->enh_sharp_en;     
    stEnhCtl.enh_cc_en = enhInfo->enh_cc_en; 
    stEnhCtl.enh_adp_ltm_en = enhInfo->enh_adp_ltm_en;    
    stEnhCtl.enh_adp_sharp_en = enhInfo->enh_adp_sharp_en; 
    stEnhCtl.enh_adp_cc_en = enhInfo->enh_adp_cc_en;    
    stEnhCtl.ltm_gain = enhInfo->ltm_gain;  
    stEnhCtl.ltm_th = enhInfo->ltm_th; 
    stEnhCtl.enh_nr_th = enhInfo->enh_nr_th; 
    stEnhCtl.enh_th1 = enhInfo->enh_th1;
    stEnhCtl.enh_th2 = enhInfo->enh_th2;
    stEnhCtl.sharp_gain = enhInfo->sharp_gain; 
    Isp_Drv_R2k_Core_SetEnhLtmCtl(isp,&stEnhCtl);
    Isp_Drv_R2k_Core_SetEnhCCCtl(isp,&stEnhCtl);
    Isp_Drv_R2k_Core_SetEnhSharpenCtl(isp,&stEnhCtl);
	return 0;
}
//POST
static int isp_r2k_core_SetPostCtl(struct isp_device *isp,POST_INFO_S *postInfo)
{
	ISP_CHECK_POINTER(postInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_POST_CTL_S stPostCtl;
    stPostCtl.post_cont_ad_en = postInfo->post_cont_ad_en;   
    stPostCtl.post_luma_ad_en = postInfo->post_luma_ad_en;   
    stPostCtl.post_satu_ad_en = postInfo->post_satu_ad_en;
    stPostCtl.cont_ad_intensity = postInfo->cont_ad_intensity;    
    stPostCtl.luma_ad_intensity = postInfo->luma_ad_intensity;
    stPostCtl.satu_ad_intensity = postInfo->satu_ad_intensity;
    Isp_Drv_R2k_Core_SetPostContCtl(isp,&stPostCtl);
    Isp_Drv_R2k_Core_SetPostLumaCtl(isp,&stPostCtl);
    Isp_Drv_R2k_Core_SetPostSatuCtl(isp,&stPostCtl);
	return 0;
}
//OTC
static int isp_r2k_core_SetOtcCtl(struct isp_device *isp,OTC_INFO_S *otcInfo)
{
	ISP_CHECK_POINTER(otcInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_OTC_CTL_S stOtcCtl;
    stOtcCtl.post_otc_en = otcInfo->post_otc_en;
   	stOtcCtl.otc_yc_sel = otcInfo->otc_yc_sel; 
   	stOtcCtl.otc_uv_format_sel = otcInfo->otc_uv_format_sel; 
   	stOtcCtl.otc_hsync_pol_sel = otcInfo->otc_hsync_pol_sel; 
   	stOtcCtl.otc_vsync_pol_sel = otcInfo->otc_vsync_pol_sel;    
   	stOtcCtl.otc_stt_vr = otcInfo->otc_out_size.Width_st;   
   	stOtcCtl.otc_stt_hr = otcInfo->otc_out_size.Height_st;   
   	stOtcCtl.otc_height = otcInfo->otc_out_size.Height;   
   	stOtcCtl.otc_width = otcInfo->otc_out_size.Width; 
    Isp_Drv_R2k_Core_SetOtcCtl(isp,&stOtcCtl);
	return 0;
}
//LDC
static int isp_r2k_core_SetLdcCtl(struct isp_device *isp,LDC_INFO_S *ldcInfo)
{
	ISP_CHECK_POINTER(ldcInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_LDC_CTL_S stLdcCtl;
    stLdcCtl.ldc_en = ldcInfo->ldc_en; 
    stLdcCtl.ldc_arith_en = ldcInfo->ldc_arith_en;   
    stLdcCtl.ldc_req_freq = ldcInfo->ldc_req_freq;
    stLdcCtl.ldc_stt_ln = ldcInfo->ldc_stt_ln;
    stLdcCtl.ldc_h_center_pos = ldcInfo->ldc_h_center_pos;
    stLdcCtl.ldc_v_center_pos = ldcInfo->ldc_v_center_pos;
    stLdcCtl.ldc_rectify_cr = ldcInfo->ldc_rectify_cr;
    stLdcCtl.ldc_rectify_cz = ldcInfo->ldc_rectify_cz; 
    Isp_Drv_R2k_Core_SetLdcCtl(isp,&stLdcCtl);
	return 0;
}
//AF
static int isp_r2k_core_SetAfCtl(struct isp_device *isp,AF_INFO_S *afInfo)
{
	ISP_CHECK_POINTER(afInfo);
	ISP_CHECK_POINTER(isp);
    ISP_CORE_AF_CTL_S stAfCtl;
	stAfCtl.af_stat_en = afInfo->af_stat_en; 
   	stAfCtl.af_stat_mode_sel= afInfo->af_stat_mode_sel; 
    stAfCtl.af_stat_win_h_start= afInfo->af_win_size.h_start;    
    stAfCtl.af_stat_win_v_start= afInfo->af_win_size.v_start; 
    stAfCtl.af_stat_win_h_end= afInfo->af_win_size.h_end;  
    stAfCtl.af_stat_win_v_end= afInfo->af_win_size.v_end;
    Isp_Drv_R2k_Core_SetAfCtl(isp,&stAfCtl);
	return 0;
}
//
void isp_r2k_core_GetCfg(ISP_CORE_CFG_INFO *isp_core_cfg,ISP_SIZE_S *isp_size)
{
    ISP_CHECK_POINTER(isp_core_cfg);
    ISP_CHECK_POINTER(isp_size);
    //
    isp_core_cfg->itcInfo.total_size.Width = isp_size->total_size.Width;
    isp_core_cfg->itcInfo.total_size.Height = isp_size->total_size.Height;
    //
    isp_core_cfg->itcInfo.itc_size.Width_st = 5;//2;
    isp_core_cfg->itcInfo.itc_size.Width = isp_size->in_size.Width;
    isp_core_cfg->itcInfo.itc_size.Height_st = 2;//3; 
    isp_core_cfg->itcInfo.itc_size.Height = isp_size->in_size.Height;
    //
    isp_core_cfg->otcInfo.otc_out_size.Width_st = 4;
    isp_core_cfg->otcInfo.otc_out_size.Width = isp_size->out_size.Width;
    isp_core_cfg->otcInfo.otc_out_size.Height_st = 4;
    isp_core_cfg->otcInfo.otc_out_size.Height = isp_size->out_size.Height;

    return;
}
//
void isp_r2k_print_corecfg(ISP_CORE_CFG_INFO *isp_core_cfg)
{
    ISP_CHECK_POINTER(isp_core_cfg);
    //itc
    ITC_INFO_S *itcInfo = &isp_core_cfg->itcInfo;
    printf("hsync_pol:0x%x\n",itcInfo->hsync_pol);
    printf("vsync_pol:0x%x\n",itcInfo->vsync_pol);
    printf("hsync_input_timing:0x%x\n",itcInfo->hsync_input_timing);
    printf("vsync_input_timing:0x%x\n",itcInfo->vsync_input_timing);
    printf("flip_ctl:0x%x\n",itcInfo->flip_ctl);  
    printf("video_fmt_sel:0x%x\n",itcInfo->video_fmt_sel);
    printf("Width:0x%x\n",itcInfo->total_size.Width);
    printf("Height:0x%x\n",itcInfo->total_size.Height);
    printf("Width_st:0x%x\n",itcInfo->itc_size.Width_st);
    printf("Width:0x%x\n",itcInfo->itc_size.Width);
    printf("Height_st:0x%x\n",itcInfo->itc_size.Height_st);
    printf("Height:0x%x\n",itcInfo->itc_size.Height);
    //tpg   
	TPG_INFO_S  *tpgInfo = &isp_core_cfg->tpgInfo;
    printf("tpg_en:0x%x\n",tpgInfo->tpg_en);
    printf("tpg_sel:0x%x\n",tpgInfo->tpg_sel);
    printf("bayer_mode_sel:0x%x\n",tpgInfo->bayer_mode_sel); 
    printf("motion_mode_sel:0x%x\n",tpgInfo->motion_mode_sel);
    printf("wdr_l_mul_data:0x%x\n",tpgInfo->wdr_l_mul_data); 
    printf("wdr_m_mul_data:0x%x\n",tpgInfo->wdr_m_mul_data); 
    printf("wdr_s_mul_data:0x%x\n",tpgInfo->wdr_s_mul_data);    
//blc   
	BLC_INFO_S  *blcInfo = &isp_core_cfg->blcInfo;
    printf("blc_en:0x%x\n",blcInfo->blc_en);    
    printf("blc_offset:0x%x\n",blcInfo->blc_offset);
    printf("blc_ratio:0x%x\n",blcInfo->blc_ratio);
//lsc   
	LSC_INFO_S  *lscInfo = &isp_core_cfg->lscInfo;
    printf("lsc_en:0x%x\n",lscInfo->lsc_en);      
    printf("lsc_h_center:0x%x\n",lscInfo->lsc_h_center);
    printf("lsc_v_center:0x%x\n",lscInfo->lsc_v_center);
    printf("lsc_r_ratio:0x%x\n",lscInfo->lsc_r_ratio); 
    printf("lsc_g_ratio:0x%x\n",lscInfo->lsc_g_ratio); 
    printf("lsc_b_ratio:0x%x\n",lscInfo->lsc_b_ratio); 
    printf("lsc_ir_ratio:0x%x\n",lscInfo->lsc_ir_ratio);
//ae
	AE_INFO_S   *aeInfo = &isp_core_cfg->aeInfo;
    printf("ae_as_en:0x%x\n",aeInfo->ae_as_en); 
    printf("ae_ag_en:0x%x\n",aeInfo->ae_ag_en);      
    printf("ae_airis_en:0x%x\n",aeInfo->ae_airis_en);      
    printf("ae_enter_ls_sel:0x%x\n",aeInfo->ae_enter_ls_sel); 
    printf("ae_exit_ls_sel:0x%x\n",aeInfo->ae_exit_ls_sel);     
    printf("ae_win_mode_sel:0x%x\n",aeInfo->ae_win_mode_sel);    
    printf("ae_back_light_mode_sel:0x%x\n",aeInfo->ae_back_light_mode_sel);
    printf("ae_day_change_en:0x%x\n",aeInfo->ae_day_change_en);    
    printf("ae_day_change_sel:0x%x\n",aeInfo->ae_day_change_sel);
    printf("ae_win_size.h_start:0x%x\n",aeInfo->ae_win_size.h_start);
    printf("ae_win_size.h_end:0x%x\n",aeInfo->ae_win_size.h_end);
    printf("ae_win_size.v_start:0x%x\n",aeInfo->ae_win_size.v_start);
    printf("ae_win_size.v_end:0x%x\n",aeInfo->ae_win_size.v_end);
    printf("ae_tar_bright:0x%x\n",aeInfo->ae_tar_bright);    
    printf("ae_tar_bright_range:0x%x\n",aeInfo->ae_tar_bright_range);     
    printf("ae_l_ex_time:0x%x\n",aeInfo->ae_l_ex_time);
    printf("ae_m_ex_time:0x%x\n",aeInfo->ae_m_ex_time);
    printf("ae_s_ex_time:0x%x\n",aeInfo->ae_s_ex_time);     
    printf("ae_agc:0x%x\n",aeInfo->ae_agc);
    printf("ae_ad_shuttle_freq:0x%x\n",aeInfo->ae_ad_shuttle_freq);
    printf("ae_ad_gain_freq:0x%x\n",aeInfo->ae_ad_gain_freq);    
    printf("ae_adjust_step_max:0x%x\n",aeInfo->ae_adjust_step_max);     
    printf("ae_ex_value_max:0x%x\n",aeInfo->ae_ex_value_max);  
    printf("ae_ex_value_mid:0x%x\n",aeInfo->ae_ex_value_mid);    
    printf("ae_ex_value_min:0x%x\n",aeInfo->ae_ex_value_min);     
    printf("ae_gain_value_max:0x%x\n",aeInfo->ae_gain_value_max);    
    printf("ae_gain_value_mid:0x%x\n",aeInfo->ae_gain_value_mid);
    printf("ae_gain_value_min:0x%x\n",aeInfo->ae_gain_value_min);    
    printf("ae_dn_switch_ad_step_max:0x%x\n",aeInfo->ae_dn_switch_ad_step_max);
    printf("ae_dn_switch_wait_time:0x%x\n",aeInfo->ae_dn_switch_wait_time);
    printf("ape_max_diff:0x%x\n",aeInfo->ape_max_diff);    
    printf("ape_drv_signal_max:0x%x\n",aeInfo->ape_drv_signal_max);    
    printf("ape_coeff_distance:0x%x\n",aeInfo->ape_coeff_distance);    
    printf("ape_coeff_speed:0x%x\n",aeInfo->ape_coeff_speed);    
    printf("ape_coeff_acceleration:0x%x\n",aeInfo->ape_coeff_acceleration);   
    printf("ape_drv_manual_value:0x%x\n",aeInfo->ape_drv_manual_value);  
    printf("ape_damp_manual_value:0x%x\n",aeInfo->ape_damp_manual_value); 
//awb
	AWB_INFO_S  *awbInfo = &isp_core_cfg->awbInfo;
    printf("awb_d65_en:0x%x\n",awbInfo->awb_d65_en); 
    printf("awb_ccm_en:0x%x\n",awbInfo->awb_ccm_en); 
    printf("awb_en:0x%x\n",awbInfo->awb_en);     
    printf("awb_mode_sel:0x%x\n",awbInfo->awb_mode_sel);
    printf("awb_hist_mode_sel:0x%x\n",awbInfo->awb_hist_mode_sel);
    printf("awb_veri_en:0x%x\n",awbInfo->awb_veri_en);      
    printf("awb_fb_en:0x%x\n",awbInfo->awb_fb_en);
    printf("awb_value_save_en:0x%x\n",awbInfo->awb_value_save_en);
    printf("awb_ccm_adp_adjust_en:0x%x\n",awbInfo->awb_ccm_adp_adjust_en);
    printf("awb_stab_en:0x%x\n",awbInfo->awb_stab_en); 
    printf("awb_d65_red_gain:0x%x\n",awbInfo->awb_d65_red_gain);
    printf("awb_d65_blue_gain:0x%x\n",awbInfo->awb_d65_blue_gain);
    printf("ccm_coff[0][0]:0x%x\n",awbInfo->ccm_coff[0][0]);
    printf("ccm_coff[0][1]:0x%x\n",awbInfo->ccm_coff[0][1]);
    printf("ccm_coff[0][2]:0x%x\n",awbInfo->ccm_coff[0][2]);
    printf("ccm_coff[1][0]:0x%x\n",awbInfo->ccm_coff[1][0]);
    printf("ccm_coff[1][1]:0x%x\n",awbInfo->ccm_coff[1][1]);
    printf("ccm_coff[1][2]:0x%x\n",awbInfo->ccm_coff[1][2]);
    printf("ccm_coff[2][0]:0x%x\n",awbInfo->ccm_coff[2][0]);
    printf("ccm_coff[2][1]:0x%x\n",awbInfo->ccm_coff[2][1]);
    printf("ccm_coff[2][2]:0x%x\n",awbInfo->ccm_coff[2][2]);
    printf("ccm_correct_coff:0x%x\n",awbInfo->ccm_correct_coff);
    printf("h_start:0x%x\n",awbInfo->awb_win_size.h_start); 
    printf("h_end:0x%x\n",awbInfo->awb_win_size.h_end); 
    printf("v_start:0x%x\n",awbInfo->awb_win_size.v_start); 
    printf("v_start:0x%x\n",awbInfo->awb_win_size.v_end); 
    printf("awb_correct_diff_th:0x%x\n",awbInfo->awb_correct_diff_th);     
    printf("awb_color_changeres_time:0x%x\n",awbInfo->awb_color_changeres_time);
    printf("awb_historgram_th:0x%x\n",awbInfo->awb_historgram_th);
    printf("awb_red_gain_adjust:0x%x\n",awbInfo->awb_red_gain_adjust);     
    printf("awb_green_gain_adjust:0x%x\n",awbInfo->awb_green_gain_adjust);   
    printf("awb_blue_gain_adjust:0x%x\n",awbInfo->awb_blue_gain_adjust);    
    printf("awb_red_max_value:0x%x\n",awbInfo->awb_red_max_value);
    printf("awb_blue_max_value:0x%x\n",awbInfo->awb_blue_max_value);      
    printf("awb_red_min_value:0x%x\n",awbInfo->awb_red_min_value);
    printf("awb_blue_min_value:0x%x\n",awbInfo->awb_blue_min_value);
    printf("awb_red_obj_value:0x%x\n",awbInfo->awb_red_obj_value);
    printf("awb_blue_obj_value:0x%x\n",awbInfo->awb_blue_obj_value);
//csc   
	CSC_INFO_S  *cscInfo = &isp_core_cfg->cscInfo;
    printf("csc_r2y[0][0]:0x%x\n",cscInfo->csc_r2y[0][0]);
    printf("csc_r2y[0][1]:0x%x\n",cscInfo->csc_r2y[0][1]);
    printf("csc_r2y[0][2]:0x%x\n",cscInfo->csc_r2y[0][2]);
    printf("csc_r2y[1][0]:0x%x\n",cscInfo->csc_r2y[1][0]);
    printf("csc_r2y[1][1]:0x%x\n",cscInfo->csc_r2y[1][1]);
    printf("csc_r2y[1][2]:0x%x\n",cscInfo->csc_r2y[1][2]);
    printf("csc_r2y[2][0]:0x%x\n",cscInfo->csc_r2y[2][0]);
    printf("csc_r2y[2][1]:0x%x\n",cscInfo->csc_r2y[2][1]);
    printf("csc_r2y[2][2]:0x%x\n",cscInfo->csc_r2y[2][2]);
//ada   
	ADA_INFO_S  *adaInfo = &isp_core_cfg->adaInfo;
    printf("ada_rgb_gamma_en:0x%x\n",adaInfo->ada_rgb_gamma_en); 
    printf("ada_yuv_gamma_en:0x%x\n",adaInfo->ada_yuv_gamma_en); 
    printf("ada_adjust_en:0x%x\n",adaInfo->ada_adjust_en);    
    printf("ada_img_stab_en:0x%x\n",adaInfo->ada_img_stab_en);
    printf("ada_ccr_en:0x%x\n",adaInfo->ada_ccr_en);
    printf("ada_adp_en:0x%x\n",adaInfo->ada_adp_en);
    printf("ada_adp_ccr_en:0x%x\n",adaInfo->ada_adp_ccr_en);   
    printf("ada_stat_mode_sel:0x%x\n",adaInfo->ada_stat_mode_sel);
    printf("ada_enh_mode_sel:0x%x\n",adaInfo->ada_enh_mode_sel);
    printf("ada_stat_max_value:0x%x\n",adaInfo->ada_stat_max_value); 
    printf("ada_ad_stren_max_value:0x%x\n",adaInfo->ada_ad_stren_max_value);
    printf("h_start:0x%x\n",adaInfo->ada_win_size.h_start);
    printf("h_end:0x%x\n",adaInfo->ada_win_size.h_end);
    printf("v_start:0x%x\n",adaInfo->ada_win_size.v_start);
    printf("v_end:0x%x\n",adaInfo->ada_win_size.v_end);
//rgbir
	RGBIR_INFO_S *rgbirInfo = &isp_core_cfg->rgbirInfo;
    printf("rgbir_en:0x%x\n",rgbirInfo->rgbir_en); 
    printf("rgbir_rtf_en:0x%x\n",rgbirInfo->rgbir_rtf_en);    
    printf("rgbir_rpc_en:0x%x\n",rgbirInfo->rgbir_rpc_en);    
    printf("rgbir_fusion_en:0x%x\n",rgbirInfo->rgbir_fusion_en);
    printf("rgbir_output_sel:0x%x\n",rgbirInfo->rgbir_output_sel);
    printf("rgbir_rpc_max_value:0x%x\n",rgbirInfo->rgbir_rpc_max_value); 
    printf("rgbir_rpc_color_coff:0x%x\n",rgbirInfo->rgbir_rpc_color_coff);
    printf("rgbir_rpc_luma_coff:0x%x\n",rgbirInfo->rgbir_rpc_luma_coff); 
    printf("rgbir_rpc_th:0x%x\n",rgbirInfo->rgbir_rpc_th);
    printf("rgbir_rpc_th1:0x%x\n",rgbirInfo->rgbir_rpc_th1);  
//nr2d
	NR2D_INFO_S *nr2dInfo = &isp_core_cfg->nr2dInfo;
    printf("d2nr_pcf_en:0x%x\n",nr2dInfo->d2nr_pcf_en);
    printf("d2nr_raw_en:0x%x\n",nr2dInfo->d2nr_raw_en);
    printf("d2nr_edge_en:0x%x\n",nr2dInfo->d2nr_edge_en);      
    printf("d2nr_bap_en:0x%x\n",nr2dInfo->d2nr_bap_en);
    printf("d2nr_luma_en:0x%x\n",nr2dInfo->d2nr_luma_en);      
    printf("d2nr_chroma_en:0x%x\n",nr2dInfo->d2nr_chroma_en);    
    printf("d2nr_pcf_adp_en:0x%x\n",nr2dInfo->d2nr_pcf_adp_en);   
    printf("d2nr_raw_adp_en:0x%x\n",nr2dInfo->d2nr_raw_adp_en);   
    printf("d2nr_luma_adp_en:0x%x\n",nr2dInfo->d2nr_luma_adp_en);  
    printf("d2nr_chroma_adp_en:0x%x\n",nr2dInfo->d2nr_chroma_adp_en);
    printf("d2nr_raw_intensity:0x%x\n",nr2dInfo->d2nr_raw_intensity);
    printf("d2nr_bap_intensity:0x%x\n",nr2dInfo->d2nr_bap_intensity);
    printf("d2nr_edge_intensity:0x%x\n",nr2dInfo->d2nr_edge_intensity);
    printf("d2nr_luma_intensity:0x%x\n",nr2dInfo->d2nr_luma_intensity);
    printf("d2nr_chroma_intensity:0x%x\n",nr2dInfo->d2nr_chroma_intensity);

//enh
	ENH_INFO_S  *enhInfo = &isp_core_cfg->enhInfo;
    printf("enh_ltm_en:0x%x\n",enhInfo->enh_ltm_en);      
    printf("enh_sharp_en:0x%x\n",enhInfo->enh_sharp_en);    
    printf("enh_cc_en:0x%x\n",enhInfo->enh_cc_en);
    printf("enh_adp_ltm_en:0x%x\n",enhInfo->enh_adp_ltm_en);
    printf("enh_adp_sharp_en:0x%x\n",enhInfo->enh_adp_sharp_en);
    printf("enh_adp_cc_en:0x%x\n",enhInfo->enh_adp_cc_en);   
    printf("ltm_gain:0x%x\n",enhInfo->ltm_gain);  
    printf("ltm_th:0x%x\n",enhInfo->ltm_th);    
    printf("enh_nr_th:0x%x\n",enhInfo->enh_nr_th); 
    printf("enh_th1:0x%x\n",enhInfo->enh_th1);
    printf("enh_th2:0x%x\n",enhInfo->enh_th2);
    printf("sharp_gain:0x%x\n",enhInfo->sharp_gain); 
//post ctrl
	POST_INFO_S *postInfo = &isp_core_cfg->postInfo;
    printf("post_cont_ad_en:0x%x\n",postInfo->post_cont_ad_en);  
    printf("post_luma_ad_en:0x%x\n",postInfo->post_luma_ad_en);  
    printf("post_satu_ad_en:0x%x\n",postInfo->post_satu_ad_en);  
    printf("cont_ad_intensity:0x%x\n",postInfo->cont_ad_intensity);
    printf("luma_ad_intensity:0x%x\n",postInfo->luma_ad_intensity);
    printf("satu_ad_intensity:0x%x\n",postInfo->satu_ad_intensity);
//otc
	OTC_INFO_S  *otcInfo = &isp_core_cfg->otcInfo;
    printf("post_otc_en:0x%x\n",otcInfo->post_otc_en);  
    printf("otc_yc_sel:0x%x\n",otcInfo->otc_yc_sel); 
    printf("otc_uv_format_sel:0x%x\n",otcInfo->otc_uv_format_sel); 
    printf("otc_hsync_pol_sel:0x%x\n",otcInfo->otc_hsync_pol_sel);
    printf("otc_vsync_pol_sel:0x%x\n",otcInfo->otc_vsync_pol_sel);
    printf("Width_st:0x%x\n",otcInfo->otc_out_size.Width_st);
    printf("Height_st:0x%x\n",otcInfo->otc_out_size.Height_st);
    printf("Width:0x%x\n",otcInfo->otc_out_size.Width);
    printf("Height:0x%x\n",otcInfo->otc_out_size.Height);
//ldc
	LDC_INFO_S  *ldcInfo = &isp_core_cfg->ldcInfo;
    printf("ldc_en:0x%x\n",ldcInfo->ldc_en);     
    printf("ldc_arith_en:0x%x\n",ldcInfo->ldc_arith_en);   
    printf("ldc_req_freq:0x%x\n",ldcInfo->ldc_req_freq);   
    printf("ldc_stt_ln:0x%x\n",ldcInfo->ldc_stt_ln);
    printf("ldc_h_center_pos:0x%x\n",ldcInfo->ldc_h_center_pos);
    printf("ldc_v_center_pos:0x%x\n",ldcInfo->ldc_v_center_pos);
    printf("ldc_rectify_cr:0x%x\n",ldcInfo->ldc_rectify_cr); 
    printf("ldc_rectify_cz:0x%x\n",ldcInfo->ldc_rectify_cz); 
//af
	AF_INFO_S *afInfo = &isp_core_cfg->afInfo;
    printf("af_stat_en:0x%x\n",afInfo->af_stat_en);  
    printf("af_stat_mode_sel:0x%x\n",afInfo->af_stat_mode_sel); 
    printf("af_win_size.h_start:0x%x\n",afInfo->af_win_size.h_start);
    printf("af_win_size.h_end:0x%x\n",afInfo->af_win_size.h_end);
    printf("af_win_size.v_start:0x%x\n",afInfo->af_win_size.v_start);
    printf("af_win_size.v_end:0x%x\n",afInfo->af_win_size.v_end);
    return;
}
//
void isp_r2k_core_cfg(struct isp_r2k_device *r2k,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type)
{
	ISP_CHECK_POINTER(r2k);
    ISP_CHECK_POINTER(isp_size);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_CORE_CFG_INFO	*isp_core_cfg =&r2k->isp_core_cfg;

    if(IMX385_SENSOR == sensor_type)
    {
       memcpy(isp_core_cfg,&imx385_core_info,sizeof(ISP_CORE_CFG_INFO));  
    }
    else if(JFX23S_SENSOR == sensor_type)
    {
        memcpy(isp_core_cfg,&jfx23s_core_info,sizeof(ISP_CORE_CFG_INFO));
    }

    isp_r2k_print_corecfg(isp_core_cfg);
    isp_r2k_core_GetCfg(isp_core_cfg,isp_size);
    //
	ITC_INFO_S	*itcInfo = &isp_core_cfg->itcInfo;
	isp_r2k_core_SetItc(isp,itcInfo);
    //
	isp_r2k_core_SetImage(isp,itcInfo);
    //
	TPG_INFO_S	*tpgInfo = &isp_core_cfg->tpgInfo;
	isp_r2k_core_SetTpgCtl(isp,tpgInfo);
    //
	BLC_INFO_S *blcInfo = &isp_core_cfg->blcInfo;
	isp_r2k_core_SetBlcCtl(isp,blcInfo);
    //
	LSC_INFO_S *lscInfo = &isp_core_cfg->lscInfo;
	isp_r2k_core_SetLscCtl(isp,lscInfo);
    //
	AE_INFO_S	*aeInfo = &isp_core_cfg->aeInfo;
	isp_r2k_core_SetAeCtl(isp,aeInfo);
	AWB_INFO_S  *awbInfo = &isp_core_cfg->awbInfo;
    //
	isp_r2k_core_SetAwbCtl(isp,awbInfo);
    //
	CSC_INFO_S	*cscInfo = &isp_core_cfg->cscInfo;
	isp_r2k_core_SetCscCtl(isp,cscInfo);
    //
	ADA_INFO_S  *adaInfo = &isp_core_cfg->adaInfo;
	isp_r2k_core_SetAdaCtl(isp,adaInfo);
	RGBIR_INFO_S	*rgbirInfo = &isp_core_cfg->rgbirInfo;
    //
	isp_r2k_core_SetRgbirCtl(isp,rgbirInfo);
    //
	NR2D_INFO_S	*nr2dInfo = &isp_core_cfg->nr2dInfo;
	isp_r2k_core_Set2dnrCtl(isp,nr2dInfo);
    //
	ENH_INFO_S *enhInfo= &isp_core_cfg->enhInfo;
	isp_r2k_core_SetEnhCtl(isp,enhInfo);
    //
	POST_INFO_S *postInfo= &isp_core_cfg->postInfo;
	isp_r2k_core_SetPostCtl(isp,postInfo);
    //
	OTC_INFO_S *otcInfo= &isp_core_cfg->otcInfo;
	isp_r2k_core_SetOtcCtl(isp,otcInfo);
    //
	LDC_INFO_S *ldcInfo= &isp_core_cfg->ldcInfo;
	isp_r2k_core_SetLdcCtl(isp,ldcInfo);
    //
	AF_INFO_S	*afInfo= &isp_core_cfg->afInfo;
	isp_r2k_core_SetAfCtl(isp,afInfo);
    return;
}
//
void isp_r2k_core_config(struct isp_r2k_device *r2k)
{
	ISP_CHECK_POINTER(r2k);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_CORE_CFG_INFO	*isp_core_cfg =&r2k->isp_core_cfg;
    //
	ITC_INFO_S	*itcInfo = &isp_core_cfg->itcInfo;
	isp_r2k_core_SetItc(isp,itcInfo);
    //
	isp_r2k_core_SetImage(isp,itcInfo);
    //
	TPG_INFO_S	*tpgInfo = &isp_core_cfg->tpgInfo;
	isp_r2k_core_SetTpgCtl(isp,tpgInfo);
    //
	BLC_INFO_S *blcInfo = &isp_core_cfg->blcInfo;
	isp_r2k_core_SetBlcCtl(isp,blcInfo);
    //
	LSC_INFO_S *lscInfo = &isp_core_cfg->lscInfo;
	isp_r2k_core_SetLscCtl(isp,lscInfo);
    //
	AE_INFO_S	*aeInfo = &isp_core_cfg->aeInfo;
	isp_r2k_core_SetAeCtl(isp,aeInfo);
	AWB_INFO_S  *awbInfo = &isp_core_cfg->awbInfo;
    //
	isp_r2k_core_SetAwbCtl(isp,awbInfo);
    //
	CSC_INFO_S	*cscInfo = &isp_core_cfg->cscInfo;
	isp_r2k_core_SetCscCtl(isp,cscInfo);
    //
	ADA_INFO_S  *adaInfo = &isp_core_cfg->adaInfo;
	isp_r2k_core_SetAdaCtl(isp,adaInfo);
	RGBIR_INFO_S	*rgbirInfo = &isp_core_cfg->rgbirInfo;
    //
	isp_r2k_core_SetRgbirCtl(isp,rgbirInfo);
    //
	NR2D_INFO_S	*nr2dInfo = &isp_core_cfg->nr2dInfo;
	isp_r2k_core_Set2dnrCtl(isp,nr2dInfo);
    //
	ENH_INFO_S *enhInfo= &isp_core_cfg->enhInfo;
	isp_r2k_core_SetEnhCtl(isp,enhInfo);
    //
	POST_INFO_S *postInfo= &isp_core_cfg->postInfo;
	isp_r2k_core_SetPostCtl(isp,postInfo);
    //
	OTC_INFO_S *otcInfo= &isp_core_cfg->otcInfo;
	isp_r2k_core_SetOtcCtl(isp,otcInfo);
    //
	LDC_INFO_S *ldcInfo= &isp_core_cfg->ldcInfo;
	isp_r2k_core_SetLdcCtl(isp,ldcInfo);
    //
	AF_INFO_S	*afInfo= &isp_core_cfg->afInfo;
	isp_r2k_core_SetAfCtl(isp,afInfo);
    return;
}
/****************************************************************************************
 *ISP DS
****************************************************************************************/
static void isp_r2k_ds_calc_scale(IMAGE_SIZE *in_size,IMAGE1_SIZE *ds_out_size,ISP_S_DS_ATTR_S *stDsAttr)
{
    ISP_CHECK_POINTER(stDsAttr);
    unsigned int InputWidth = in_size->Width;
    unsigned int  InputHeight = in_size->Height;
    unsigned int  OutputWidth = ds_out_size->Width;
    unsigned int  OutputHeight = ds_out_size->Height;
    stDsAttr->hscalePram.hscale_pstep = (InputWidth / OutputWidth);
    stDsAttr->hscalePram.hscale_dstep = ((InputWidth % OutputWidth) * 65536 / OutputWidth);
    stDsAttr->vscalePram.vscale_pstep = (InputHeight / OutputHeight);
    stDsAttr->vscalePram.vscale_dstep = ((InputHeight % OutputHeight) * 65536 / OutputHeight);
    return;
}
//
void isp_r2k_ds_SetInputSize(struct isp_device *isp,IMAGE_SIZE *dsInSizeInfo)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(dsInSizeInfo);
    IMAGE_SIZE inputsize;
    inputsize.Width = dsInSizeInfo->Width - 1;
    inputsize.Height = dsInSizeInfo->Height - 1;
    Isp_Drv_R2k_Ds_SetInputSize(isp,&inputsize);
}
//
void isp_r2k_ds_SetRgb2YuvCoff(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    unsigned int osd_rgb2yuv_coeff[3][4];
    osd_rgb2yuv_coeff[0][0]= 0x00000132;
    osd_rgb2yuv_coeff[0][1]= 0x00000259;
    osd_rgb2yuv_coeff[0][2]= 0x00000075;
    osd_rgb2yuv_coeff[0][3]= 0x00000000;
    osd_rgb2yuv_coeff[1][0]= 0x00000f50;
    osd_rgb2yuv_coeff[1][1]= 0x00000ea5;
    osd_rgb2yuv_coeff[1][2]= 0x0000020b;
    osd_rgb2yuv_coeff[1][3]= 0x00000080;
    osd_rgb2yuv_coeff[2][0]= 0x0000020b;
    osd_rgb2yuv_coeff[2][1]= 0x00000e4a;
    osd_rgb2yuv_coeff[2][2]= 0x00000fab;
    osd_rgb2yuv_coeff[2][3]= 0x00000080;
    Isp_Drv_R2k_Ds_SetRgb2YuvCoff(isp,osd_rgb2yuv_coeff);
}
//
void isp_r2k_ds_SetYuv2RgbCoff(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    unsigned int osd_yuv2rgb_coeff[3][4];
  	osd_yuv2rgb_coeff[0][0] = 0x00000400;
	osd_yuv2rgb_coeff[0][1] = 0x00000000;
	osd_yuv2rgb_coeff[0][2] = 0x000005a1;
	osd_yuv2rgb_coeff[0][3] = 0x00000f4c;
	osd_yuv2rgb_coeff[1][0] = 0x00000400;
	osd_yuv2rgb_coeff[1][1] = 0x00000e9e;
	osd_yuv2rgb_coeff[1][2] = 0x00000d22;
	osd_yuv2rgb_coeff[1][3] = 0x00000088;
	osd_yuv2rgb_coeff[2][0] = 0x00000400;
	osd_yuv2rgb_coeff[2][1] = 0x0000071e;
	osd_yuv2rgb_coeff[2][2] = 0x00000000;
	osd_yuv2rgb_coeff[2][3] = 0x00000f1c;
    Isp_Drv_R2k_Ds_SetYuv2RgbCoff(isp,osd_yuv2rgb_coeff);
}
//
void isp_r2k_ds_SetOSD(ISP_DS_OSD_ATTR_S *stDsOsdAttr,ISP_OSD_INFO_S *osdInfo)
{
    ISP_CHECK_POINTER(stDsOsdAttr);
    ISP_CHECK_POINTER(osdInfo);
    ISP_DS_OSD_INFO_S *stOsdInfo = &stDsOsdAttr->OsdInfo;
	stOsdInfo->osd_enable = osdInfo->osd_enable;
	stOsdInfo->osd_type = osdInfo->osd_type;
	stOsdInfo->osd_alpha_tpye = osdInfo->osd_alpha_tpye;
    IMAGE_SIZE *stOsdSize = &stDsOsdAttr->OsdSize;
	stOsdSize->Width = osdInfo->osd_size.Width;
	stOsdSize->Height = osdInfo->osd_size.Height;
    ISP_DS_OSD_BUF_S *stOsdBuf   = &stDsOsdAttr->OsdBuf;
	stOsdBuf->osd_rgb_addr0 = osdInfo->osd_rgb_addr[0];
	stOsdBuf->osd_rgb_addr1 =  osdInfo->osd_rgb_addr[1];
	stOsdBuf->osd_stride = osdInfo->osd_stride;
	stOsdBuf->osd_alpha_addr0 = osdInfo->osd_alpha_addr[0];
	stOsdBuf->osd_alpha_addr1 = osdInfo->osd_alpha_addr[1];
	stOsdBuf->osd_alpha_stride = osdInfo->osd_alpha_stride;
	stOsdBuf->osd_position_start_x = osdInfo->osd_position_win.h_start;
	stOsdBuf->osd_position_stop_x = osdInfo->osd_position_win.h_end;
	stOsdBuf->osd_position_start_y =osdInfo->osd_position_win.v_start;
	stOsdBuf->osd_position_stop_y = osdInfo->osd_position_win.v_end;
    ISP_DS_OSD_DMA_CTL_S *stOsdDmaCtl = &stDsOsdAttr->OsdDmaCtl;
	stOsdDmaCtl->osd_bd_limit_en = osdInfo->osd_bd_limit_en;
	stOsdDmaCtl->osd_dma_map = osdInfo->osd_dma_map;
	stOsdDmaCtl->osd_dma_request_length = osdInfo->osd_dma_request_length;
	stOsdDmaCtl->osd_global_alpha = osdInfo->osd_global_alpha;
	stOsdDmaCtl->osd_outstanding_num = osdInfo->osd_outstanding_num;
	stOsdDmaCtl->osd_rgb_rev = osdInfo->osd_rgb_rev;
	stOsdDmaCtl->osd_swap_64 = osdInfo->osd_swap_64;
    return;
}
//
void isp_r2k_ds_SetSingleDS(struct isp_device *isp,unsigned int u8Index,ISP_DS_CFG_INFO	*isp_ds_cfg)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(isp_ds_cfg);
    IMAGE_SIZE in_size;
    in_size.Width = isp_ds_cfg->dsInSizeInfo.Width;
    in_size.Height = isp_ds_cfg->dsInSizeInfo.Height;
    ISP_S_DS_ATTR_S stDsAttr;
    IMAGE_SIZE *dsOutSize = &stDsAttr.dsOutSize;
    ISP_DS_INFO_S *dsInfo = &isp_ds_cfg->dsInfo[u8Index];
    dsOutSize->Width = dsInfo->ds_out_size.Width - 1;
    dsOutSize->Height = dsInfo->ds_out_size.Height - 1;
    isp_r2k_ds_calc_scale(&in_size,&dsInfo->ds_out_size,&stDsAttr);
    stDsAttr.vscalePram.scale_en = dsInfo->scale_en;
    stDsAttr.vscalePram.vscale_filter_en = dsInfo->vscale_filter_en;
    stDsAttr.hscalePram.hscale_filter_en = dsInfo->hscale_filter_en;
    ISP_DS_FORMAT_S *stDsFormat = &stDsAttr.DsFormat;
    stDsFormat->out_rgb_en =  dsInfo->out_rgb_en;
    stDsFormat->out_rgb_mode =  dsInfo->out_rgb_mode;
    stDsFormat->out_yuv_mode =  dsInfo->out_yuv_mode;
    stDsFormat->out_uv_swap =  dsInfo->out_uv_swap;
    unsigned int osdIndex = 0;     
    ISP_DS_OSD_ATTR_S *stDsOsdAttr = &stDsAttr.DsOsdAttr[osdIndex];
    ISP_OSD_INFO_S *osdInfo = &dsInfo->osdInfo[osdIndex];
    isp_r2k_ds_SetOSD(stDsOsdAttr,osdInfo);
    osdIndex = 1;     
    stDsOsdAttr = &stDsAttr.DsOsdAttr[osdIndex];
    osdInfo = &dsInfo->osdInfo[osdIndex];
    isp_r2k_ds_SetOSD(stDsOsdAttr,osdInfo);
    osdIndex = 2;     
    stDsOsdAttr = &stDsAttr.DsOsdAttr[osdIndex];
    osdInfo = &dsInfo->osdInfo[osdIndex];
    isp_r2k_ds_SetOSD(stDsOsdAttr,osdInfo);
    Isp_Drv_R2k_Ds_SetSingleDS(isp,u8Index,&stDsAttr);
    return;
}
//
void isp_r2k_ds_GetCfg(ISP_DS_CFG_INFO *isp_ds_cfg,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    ISP_CHECK_POINTER(isp_ds_cfg);
    ISP_CHECK_POINTER(isp_addr);
    ISP_CHECK_POINTER(isp_size);
    //
    isp_ds_cfg->dsInSizeInfo.Width = isp_size->out_size.Width;
    isp_ds_cfg->dsInSizeInfo.Height = isp_size->out_size.Height;
    //DS0
    ISP_DS_INFO_S *dsInfo = &isp_ds_cfg->dsInfo[0];
    dsInfo->scale_en = isp_addr->ds0_en;
    dsInfo->vscale_filter_en = isp_addr->ds0_en;
    dsInfo->hscale_filter_en = isp_addr->ds0_en;
    dsInfo->ds_out_size.Width = isp_size->ds0_size.Width;
    dsInfo->ds_out_size.Height = isp_size->ds0_size.Height;
    //ds0 osd0
    ISP_OSD_INFO_S *osdInfo = &dsInfo->osdInfo[0];
    osdInfo->osd_enable = isp_addr->ds0_osd0_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds0_osd0_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds0_osd0_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds0_osd0_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds0_osd0_addr;
    osdInfo->osd_stride = isp_addr->ds0_osd0_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds0_osd0_stride;
    osdInfo->osd_size.Width = isp_size->ds0_osd0_size.Width;
    osdInfo->osd_size.Height = isp_size->ds0_osd0_size.Height;
    //ds0 osd1
    osdInfo = &dsInfo->osdInfo[1];
    osdInfo->osd_enable = isp_addr->ds0_osd1_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds0_osd1_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds0_osd1_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds0_osd1_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds0_osd1_addr;
    osdInfo->osd_stride = isp_addr->ds0_osd1_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds0_osd1_stride;
    osdInfo->osd_size.Width = isp_size->ds0_osd1_size.Width;
    osdInfo->osd_size.Height = isp_size->ds0_osd1_size.Height;
    //ds0 osd2
    osdInfo = &dsInfo->osdInfo[2];
    osdInfo->osd_enable = isp_addr->ds0_osd2_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds0_osd2_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds0_osd2_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds0_osd2_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds0_osd2_addr;
    osdInfo->osd_stride = isp_addr->ds0_osd2_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds0_osd2_stride;
    osdInfo->osd_size.Width = isp_size->ds0_osd2_size.Width;
    osdInfo->osd_size.Height = isp_size->ds0_osd2_size.Height;
    //DS1
    dsInfo = &isp_ds_cfg->dsInfo[1];
    dsInfo->scale_en = isp_addr->ds1_en;
    dsInfo->vscale_filter_en = isp_addr->ds1_en;
    dsInfo->hscale_filter_en = isp_addr->ds1_en;
    dsInfo->ds_out_size.Width = isp_size->ds1_size.Width;
    dsInfo->ds_out_size.Height = isp_size->ds1_size.Height;
    //ds1 osd0
    osdInfo = &dsInfo->osdInfo[0];
    osdInfo->osd_enable = isp_addr->ds1_osd0_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds1_osd0_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds1_osd0_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds1_osd0_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds1_osd0_addr;
    osdInfo->osd_stride = isp_addr->ds1_osd0_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds1_osd0_stride;
    osdInfo->osd_size.Width = isp_size->ds1_osd0_size.Width;
    osdInfo->osd_size.Height = isp_size->ds1_osd0_size.Height;
    //ds1 osd1
    osdInfo = &dsInfo->osdInfo[1];
    osdInfo->osd_enable = isp_addr->ds1_osd1_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds1_osd1_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds1_osd1_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds1_osd1_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds1_osd1_addr;
    osdInfo->osd_stride = isp_addr->ds1_osd1_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds1_osd1_stride;
    osdInfo->osd_size.Width = isp_size->ds1_osd1_size.Width;
    osdInfo->osd_size.Height = isp_size->ds1_osd1_size.Height;
    //ds1 osd2
    osdInfo = &dsInfo->osdInfo[2];
    osdInfo->osd_enable = isp_addr->ds1_osd2_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds1_osd2_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds1_osd2_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds1_osd2_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds1_osd2_addr;
    osdInfo->osd_stride = isp_addr->ds1_osd2_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds1_osd2_stride;
    osdInfo->osd_size.Width = isp_size->ds1_osd2_size.Width;
    osdInfo->osd_size.Height = isp_size->ds1_osd2_size.Height;
    //DS2
    dsInfo = &isp_ds_cfg->dsInfo[2];
    dsInfo->scale_en = isp_addr->ds2_en;
    dsInfo->vscale_filter_en = isp_addr->ds2_en;
    dsInfo->hscale_filter_en = isp_addr->ds2_en;
    dsInfo->out_rgb_en = isp_addr->ds2_en;
    dsInfo->ds_out_size.Width = isp_size->ds2_size.Width;
    dsInfo->ds_out_size.Height = isp_size->ds2_size.Height;
    //ds2 osd0
    osdInfo = &dsInfo->osdInfo[0];
    osdInfo->osd_enable = isp_addr->ds2_osd0_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds2_osd0_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds2_osd0_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds2_osd0_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds2_osd0_addr;
    osdInfo->osd_stride = isp_addr->ds2_osd0_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds2_osd0_stride;
    osdInfo->osd_size.Width = isp_size->ds2_osd0_size.Width;
    osdInfo->osd_size.Height = isp_size->ds2_osd0_size.Height;
    //ds2 osd1
    osdInfo = &dsInfo->osdInfo[1];
    osdInfo->osd_enable = isp_addr->ds2_osd1_en;
    osdInfo->osd_alpha_addr[0] = isp_addr->ds2_osd1_addr;
    osdInfo->osd_alpha_addr[1] = isp_addr->ds2_osd1_addr;
    osdInfo->osd_rgb_addr[0] = isp_addr->ds2_osd1_addr;
    osdInfo->osd_rgb_addr[1] = isp_addr->ds2_osd1_addr;
    osdInfo->osd_stride = isp_addr->ds2_osd1_stride;
    osdInfo->osd_alpha_stride = isp_addr->ds2_osd1_stride;
    osdInfo->osd_size.Width = isp_size->ds2_osd1_size.Width;
    osdInfo->osd_size.Height = isp_size->ds2_osd1_size.Height;

    return;
}
//
void isp_r2k_print_dscfg(ISP_DS_CFG_INFO *isp_ds_cfg)
{
    ISP_CHECK_POINTER(isp_ds_cfg);

    printf("dsInSizeInfo.Width;0x%x\n",isp_ds_cfg->dsInSizeInfo.Width);
    printf("dsInSizeInfo.Height:0x%x\n",isp_ds_cfg->dsInSizeInfo.Height);
    //
    printf("osd_rgb2yuv_coeff[0][0]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][0]);
    printf("osd_rgb2yuv_coeff[0][1]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][1]);
    printf("osd_rgb2yuv_coeff[0][2]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][2]);
    printf("osd_rgb2yuv_coeff[0][3]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][3]);
    printf("osd_rgb2yuv_coeff[1][0]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][0]);
    printf("osd_rgb2yuv_coeff[1][1]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][1]);
    printf("osd_rgb2yuv_coeff[1][2]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][2]);
    printf("osd_rgb2yuv_coeff[1][3]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][3]);
    printf("osd_rgb2yuv_coeff[2][0]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][0]);
    printf("osd_rgb2yuv_coeff[2][1]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][1]);
    printf("osd_rgb2yuv_coeff[2][2]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][2]);
    printf("osd_rgb2yuv_coeff[2][3]:0x%x\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][3]);
    //
    printf("osd_yuv2rgb_coeff[0][0]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][0]);
    printf("osd_yuv2rgb_coeff[0][1]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][1]);
    printf("osd_yuv2rgb_coeff[0][2]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][2]);
    printf("osd_yuv2rgb_coeff[0][3]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][3]);
    printf("osd_yuv2rgb_coeff[1][0]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][0]);
    printf("osd_yuv2rgb_coeff[1][1]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][1]);
    printf("osd_yuv2rgb_coeff[1][2]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][2]);
    printf("osd_yuv2rgb_coeff[1][3]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][3]);
    printf("osd_yuv2rgb_coeff[2][0]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][0]);
    printf("osd_yuv2rgb_coeff[2][1]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][1]);
    printf("osd_yuv2rgb_coeff[2][2]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][2]);
    printf("osd_yuv2rgb_coeff[2][3]:0x%x\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][3]);
    //ds0
    ISP_DS_INFO_S *dsInfo = &isp_ds_cfg->dsInfo[0];
    printf("scale_en:0x%x\n",dsInfo->scale_en); 
    printf("vscale_filter_en:0x%x\n",dsInfo->vscale_filter_en);
    printf("hscale_filter_en:0x%x\n",dsInfo->hscale_filter_en);
    printf("ds_out_size.Width:0x%x\n",dsInfo->ds_out_size.Width);
    printf("ds_out_size.Height:0x%x\n",dsInfo->ds_out_size.Height);
    printf("out_rgb_mode:0x%x\n",dsInfo->out_rgb_mode);
    printf("out_rgb_en:0x%x\n",dsInfo->out_rgb_en);  
    printf("out_yuv_mode:0x%x\n",dsInfo->out_yuv_mode);
    printf("out_uv_swap:0x%x\n",dsInfo->out_uv_swap);
    //ds0 osd0
    ISP_OSD_INFO_S *osdInfo = &dsInfo->osdInfo[0]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds0 osd1
    osdInfo = &dsInfo->osdInfo[1]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds0 osd2
    osdInfo = &dsInfo->osdInfo[2]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds1
    dsInfo = &isp_ds_cfg->dsInfo[1];
    printf("scale_en:0x%x\n",dsInfo->scale_en); 
    printf("vscale_filter_en:0x%x\n",dsInfo->vscale_filter_en);
    printf("hscale_filter_en:0x%x\n",dsInfo->hscale_filter_en);
    printf("ds_out_size.Width:0x%x\n",dsInfo->ds_out_size.Width);
    printf("ds_out_size.Height:0x%x\n",dsInfo->ds_out_size.Height);
    printf("out_rgb_mode:0x%x\n",dsInfo->out_rgb_mode);
    printf("out_rgb_en:0x%x\n",dsInfo->out_rgb_en);  
    printf("out_yuv_mode:0x%x\n",dsInfo->out_yuv_mode);
    printf("out_uv_swap:0x%x\n",dsInfo->out_uv_swap);
    //ds1 osd0
    osdInfo = &dsInfo->osdInfo[0]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds1 osd1
    osdInfo = &dsInfo->osdInfo[1]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds1 osd2
    osdInfo = &dsInfo->osdInfo[2]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds2
    dsInfo = &isp_ds_cfg->dsInfo[2];
    printf("scale_en:0x%x\n",dsInfo->scale_en); 
    printf("vscale_filter_en:0x%x\n",dsInfo->vscale_filter_en);
    printf("hscale_filter_en:0x%x\n",dsInfo->hscale_filter_en);
    printf("ds_out_size.Width:0x%x\n",dsInfo->ds_out_size.Width);
    printf("ds_out_size.Height:0x%x\n",dsInfo->ds_out_size.Height);
    printf("out_rgb_mode:0x%x\n",dsInfo->out_rgb_mode);
    printf("out_rgb_en:0x%x\n",dsInfo->out_rgb_en);  
    printf("out_yuv_mode:0x%x\n",dsInfo->out_yuv_mode);
    printf("out_uv_swap:0x%x\n",dsInfo->out_uv_swap);
    //ds2 osd0
    osdInfo = &dsInfo->osdInfo[0]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
    //ds2 osd1
    osdInfo = &dsInfo->osdInfo[1]; 
    printf("osd_enable:0x%x\n",osdInfo->osd_enable);
    printf("osd_type:0x%x\n",osdInfo->osd_type);      
    printf("osd_alpha_tpye:0x%x\n",osdInfo->osd_alpha_tpye);
    printf("osd_size.Width:0x%x\n",osdInfo->osd_size.Width);
    printf("osd_size.Height:0x%x\n",osdInfo->osd_size.Height);
    printf("osd_rgb_addr[0]:0x%x\n",osdInfo->osd_rgb_addr[0]);
    printf("osd_rgb_addr[1]:0x%x\n",osdInfo->osd_rgb_addr[1]);     
    printf("osd_alpha_addr[0]:0x%x\n",osdInfo->osd_alpha_addr[0]);
    printf("osd_alpha_addr[1]:0x%x\n",osdInfo->osd_alpha_addr[1]);
    printf("osd_stride:0x%x\n",osdInfo->osd_stride);       
    printf("osd_alpha_stride:0x%x\n",osdInfo->osd_alpha_stride); 
    printf("osd_position_win.h_start:0x%x\n",osdInfo->osd_position_win.h_start);
    printf("osd_position_win.h_end:0x%x\n",osdInfo->osd_position_win.h_end);
    printf("osd_position_win.v_start:0x%x\n",osdInfo->osd_position_win.v_start);
    printf("osd_position_win.v_end:0x%x\n",osdInfo->osd_position_win.v_end);
    printf("osd_dma_request_length:0x%x\n",osdInfo->osd_dma_request_length);
    printf("osd_dma_map:0x%x\n",osdInfo->osd_dma_map);           
    printf("osd_rgb_rev:0x%x\n",osdInfo->osd_rgb_rev);           
    printf("osd_global_alpha:0x%x\n",osdInfo->osd_global_alpha);       
    printf("osd_swap_64:0x%x\n",osdInfo->osd_swap_64);
    printf("osd_outstanding_num:0x%x\n",osdInfo->osd_outstanding_num);
    printf("osd_bd_limit_en:0x%x\n",osdInfo->osd_bd_limit_en);
 
    return;
}
//
void isp_r2k_ds_cfg(struct isp_r2k_device *r2k,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type)
{
	ISP_CHECK_POINTER(r2k);
    ISP_CHECK_POINTER(isp_addr);
    ISP_CHECK_POINTER(isp_size);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_DS_CFG_INFO	 *isp_ds_cfg =&r2k->isp_ds_cfg;
    //
    if(IMX385_SENSOR ==  sensor_type)
    {
        memcpy(isp_ds_cfg,&imx385_ds_info,sizeof(ISP_DS_CFG_INFO));
    }
    else if (JFX23S_SENSOR ==  sensor_type)
    {
        memcpy(isp_ds_cfg,&jfx23s_ds_info,sizeof(ISP_DS_CFG_INFO));
    }
    
    isp_r2k_print_dscfg(isp_ds_cfg);
    isp_r2k_ds_GetCfg(isp_ds_cfg,isp_addr,isp_size);
    //
    Isp_Drv_R2k_Ds_SetscaleCoeff(isp);
    //
    IMAGE_SIZE *dsInSizeInfo = &isp_ds_cfg->dsInSizeInfo;
    isp_r2k_ds_SetInputSize(isp,dsInSizeInfo);
    //
    isp_r2k_ds_SetRgb2YuvCoff(isp);
    //
    isp_r2k_ds_SetRgb2YuvCoff(isp);
    //
    unsigned int u8Index = 0;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);
    //
    u8Index = 1;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);
    //
    u8Index = 2;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);

    return;
}
//
void isp_r2k_ds_config(struct isp_r2k_device *r2k)
{
	ISP_CHECK_POINTER(r2k);

	struct isp_device *isp = to_isp_device(r2k);
    ISP_DS_CFG_INFO	 *isp_ds_cfg =&r2k->isp_ds_cfg;
    //
    Isp_Drv_R2k_Ds_SetscaleCoeff(isp);
    //
    IMAGE_SIZE *dsInSizeInfo = &isp_ds_cfg->dsInSizeInfo;
    isp_r2k_ds_SetInputSize(isp,dsInSizeInfo);
    //
    isp_r2k_ds_SetRgb2YuvCoff(isp);
    //
    isp_r2k_ds_SetRgb2YuvCoff(isp);
    //
    unsigned int u8Index = 0;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);
    //
    u8Index = 1;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);
    //
    u8Index = 2;
    isp_r2k_ds_SetSingleDS(isp,u8Index,isp_ds_cfg);

    return;
}
/****************************************************************************
*
*****************************************************************************/
void InitIsp_r2k_1920x1080_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size,enum _SENSOR_TYPE sensor_type)
{
    printf("InitIsp_r2k_1920x1080_new start\n");
    struct isp_r2k_device *isp_r2k = &isp->isp_r2k;

    isp_r2k_core_cfg(isp_r2k,isp_size,sensor_type);

    isp_r2k_ds_cfg(isp_r2k,isp_addr,isp_size,sensor_type);
   
    isp_r2k_wrap_cfg(isp_r2k,isp_addr,isp_size,sensor_type);

    printf("InitIsp_r2k_1920x1080_new end \n");
    return;
}
//
void Isp_r2k_Init(struct isp_device *isp)
{ 
    printf("Isp_r2k_Init start\n");
    struct isp_r2k_device *isp_r2k = &isp->isp_r2k;
    isp_r2k_core_config(isp_r2k);
    isp_r2k_ds_config(isp_r2k);
    isp_r2k_wrap_config(isp_r2k);
    printf("Isp_r2k_Init end \n");
    return;
}