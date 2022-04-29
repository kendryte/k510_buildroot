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
 * isp_r2k_ds_drv.c
 *
 * CANAAN ISP - DS module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_2k/ds/isp_ds_drv.h"
#include "isp_2k/ds/isp_ds_reg.h"

extern int ISP_DS_V_Coef_TABLE[128];
extern int ISP_DS_H_Coef_TABLE[192];
/*
*
*/
void Isp_Drv_R2k_Ds_SetInputSize(struct isp_device *isp,IMAGE_SIZE *inputsize)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(inputsize);

	U_ISP_DS_INPUT_SIZE udata;
	udata.u32 = 0;
	udata.bits.input_frame_width = inputsize->Width;
	udata.bits.input_frame_height = inputsize->Height;
	isp_reg_writel(isp,udata.u32,ISP_IOMEM_R2K_DS,ISP_DS_INPUT_SIZE);
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetRgb2YuvCoff(struct isp_device *isp,unsigned int *osd_rgb2yuv_coeff)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(osd_rgb2yuv_coeff);

	unsigned int i = 0;
	U_ISP_DS_OSD_RGB2YUV_COEFF stCoff;
	for(i = 0; i< 12; i++)
	{
		stCoff.u32 = 0;
		stCoff.bits.osd_rgb2yuv_coeff = osd_rgb2yuv_coeff[i];
		isp_reg_writel(isp,stCoff.u32,ISP_IOMEM_R2K_DS,ISP_DS_OSD_RGB2YUV_COEFF00 + 4*i);
	}
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetYuv2RgbCoff(struct isp_device *isp,unsigned int *osd_yuv2rgb_coeff)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(osd_yuv2rgb_coeff);

	unsigned int i = 0;
	U_ISP_DS_OSD_YUV2RGB_COEFF stCoff;
	for(i = 0; i< 12; i++)
	{
		stCoff.u32 = 0;
		stCoff.bits.osd_yuv2rgb_coeff = osd_yuv2rgb_coeff[i];
		isp_reg_writel(isp,stCoff.u32,ISP_IOMEM_R2K_DS,ISP_DS_OSD_YUV2RGB_COEFF00 + 4*i);
	}
}
/*
*
*/
static void Isp_Drv_R2k_Ds_SetHscaleParam(struct isp_device *isp,unsigned char Index,ISP_DS_HSCALE_PARM_S *Hscale)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(Hscale);

	if(Index == 0)
	{
        U_ISP_DS0_HSCALE_PARM stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_hscale_dstep = Hscale->hscale_dstep;
		stDs0.bits.ds0_hscale_pstep = Hscale->hscale_pstep;
		stDs0.bits.ds0_hscale_filter_en = Hscale->hscale_filter_en;
		isp_reg_writel(isp,stDs0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_HSCALE_PARM);
	}
	
	if(Index == 1)
	{
	    U_ISP_DS1_HSCALE_PARM stDs1;	
		stDs1.u32 = 0;
		stDs1.bits.ds1_hscale_dstep = Hscale->hscale_dstep;
		stDs1.bits.ds1_hscale_pstep = Hscale->hscale_pstep;
		stDs1.bits.ds1_hscale_filter_en = Hscale->hscale_filter_en;
		isp_reg_writel(isp,stDs1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_HSCALE_PARM);
	}
	
	if(Index == 2)
	{
        U_ISP_DS2_HSCALE_PARM stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_hscale_dstep = Hscale->hscale_dstep;
		stDs2.bits.ds2_hscale_pstep = Hscale->hscale_pstep;
		stDs2.bits.ds2_hscale_filter_en = Hscale->hscale_filter_en;
		isp_reg_writel(isp,stDs2.u32,ISP_IOMEM_R2K_DS,ISP_DS2_HSCALE_PARM);
	}
}
/*
*
*/
static void Isp_Drv_R2k_Ds_SetVscaleParam(struct isp_device *isp,unsigned char Index, ISP_DS_VSCALE_PARM_S *Vscale)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(Vscale);

	if(Index == 0)
	{
		U_ISP_DS0_VSCALE_PARM stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_vscale_dstep = Vscale->vscale_dstep;
		stDs0.bits.ds0_vscale_pstep = Vscale->vscale_pstep;
		stDs0.bits.ds0_vscale_filter_en = Vscale->vscale_filter_en;
		stDs0.bits.ds0_scale_en = Vscale->scale_en;
		isp_reg_writel(isp,stDs0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_VSCALE_PARM);
	}
	
	if(Index == 1)
	{
		U_ISP_DS1_VSCALE_PARM stDs1;
		stDs1.u32 = 0;
		stDs1.bits.ds1_vscale_dstep = Vscale->vscale_dstep;
		stDs1.bits.ds1_vscale_pstep = Vscale->vscale_pstep;
		stDs1.bits.ds1_vscale_filter_en = Vscale->vscale_filter_en;
		stDs1.bits.ds1_scale_en = Vscale->scale_en;
		isp_reg_writel(isp,stDs1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_VSCALE_PARM);
	}
	
	if(Index == 2)
	{
		U_ISP_DS2_VSCALE_PARM stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_vscale_dstep = Vscale->vscale_dstep;
		stDs2.bits.ds2_vscale_pstep = Vscale->vscale_pstep;
		stDs2.bits.ds2_vscale_filter_en = Vscale->vscale_filter_en;
		stDs2.bits.ds2_scale_en = Vscale->scale_en;
		isp_reg_writel(isp,stDs2.u32,ISP_IOMEM_R2K_DS,ISP_DS2_VSCALE_PARM);
	}
	return 0;
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetOutputSize(struct isp_device *isp,unsigned char Index, IMAGE_SIZE *OutputSize)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(OutputSize);

	if(Index == 0)
	{
	    U_ISP_DS0_SIZE stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_frm_output_height = OutputSize->Height;
		stDs0.bits.ds0_frm_output_width  = OutputSize->Width;
		isp_reg_writel(isp,stDs0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_SIZE);
	}
	
	if(Index == 1)
	{
	    U_ISP_DS1_SIZE stDs1;
		stDs1.u32 = 0;
		stDs1.bits.ds1_frm_output_height = OutputSize->Height;
		stDs1.bits.ds1_frm_output_width = OutputSize->Width;
		isp_reg_writel(isp,stDs1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_SIZE);
	}
	
	if(Index == 2)
	{
	    U_ISP_DS2_SIZE stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_frm_output_height = OutputSize->Height;
		stDs2.bits.ds2_frm_output_width = OutputSize->Width;
		isp_reg_writel(isp,stDs2.u32,ISP_IOMEM_R2K_DS,ISP_DS2_SIZE);
	}
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetOutputFormat(struct isp_device *isp,unsigned char  Index, ISP_DS_FORMAT_S *Format)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(Format);

	if(Index == 0)
	{
	    U_ISP_DS0_FORMAT stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_out_rgb_mode = Format->out_rgb_mode;
		stDs0.bits.ds0_out_rgb_en = Format->out_rgb_en;
		stDs0.bits.ds0_out_yuv_mode = Format->out_yuv_mode;
		stDs0.bits.ds0_out_uv_swap = Format->out_uv_swap;
		isp_reg_writel(isp,stDs0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_FORMAT);
	}

	if(Index == 1)
	{
        U_ISP_DS1_FORMAT stDs1;
		stDs1.u32 = 1;
		stDs1.bits.ds1_out_rgb_mode = Format->out_rgb_mode;
		stDs1.bits.ds1_out_rgb_en = Format->out_rgb_en;
		stDs1.bits.ds1_out_yuv_mode = Format->out_yuv_mode;
		stDs1.bits.ds1_out_uv_swap = Format->out_uv_swap;
		isp_reg_writel(isp,stDs1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_FORMAT);
	}
	
	if(Index == 2)
	{
    	U_ISP_DS2_FORMAT stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_out_rgb_mode = Format->out_rgb_mode;
		stDs2.bits.ds2_out_rgb_en = Format->out_rgb_en;
		stDs2.bits.ds2_out_yuv_mode = Format->out_yuv_mode;
		stDs2.bits.ds2_out_uv_swap = Format->out_uv_swap;
		isp_reg_writel(isp,stDs2.u32,ISP_IOMEM_R2K_DS,ISP_DS2_FORMAT);
	}
}

static void Isp_Drv_R2k_Ds_SetDs0OsdAttr(struct isp_device *isp,unsigned char OsdIndex,ISP_DS_OSD_ATTR_S *OsdAttr)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(OsdAttr);

    if(OsdIndex == 0)
    {
    	U_ISP_DS0_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds0_osd0_type = OsdAttr->OsdInfo.osd_type;
        stOsd0Info.bits.ds0_osd0_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds0_osd0_enable = OsdAttr->OsdInfo.osd_enable;
        isp_reg_writel(isp,stOsd0Info.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_INFO);

    	U_ISP_DS0_OSD0_SIZE stOsd0Size;      
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds0_osd0_width = OsdAttr->OsdSize.Width;
        stOsd0Size.bits.ds0_osd0_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd0Size.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_SIZE);

    	U_ISP_DS0_OSD0_BUF_ADDR0 stOsd0Addr0;        
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds0_osd0_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd0Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_BUF_ADDR0);

    	U_ISP_DS0_OSD0_BUF_ADDR1 stOsd0Addr1;  
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds0_osd0_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd0Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_BUF_ADDR1);

    	U_ISP_DS0_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;      
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds0_osd0_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd0AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_ALPHA_BUF_ADDR0);

    	U_ISP_DS0_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds0_osd0_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd0AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_ALPHA_BUF_ADDR1);

    	U_ISP_DS0_OSD0_DMA_CTL stOsd0DmaCtl;  
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds0_osd0_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds0_osd0_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds0_osd0_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds0_osd0_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds0_osd0_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds0_osd0_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds0_osd0_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;
        isp_reg_writel(isp,stOsd0DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_DMA_CTL);

    	U_ISP_DS0_OSD0_STRIDE stOsd0Stride;  
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds0_osd0_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd0Stride.bits.ds0_osd0_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd0Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_STRIDE);

    	U_ISP_DS0_OSD0_X_RANGE stOsd0XRange;
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds0_osd0_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds0_osd0_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd0XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_X_RANGE);
        
    	U_ISP_DS0_OSD0_Y_RANGE stOsd0YRange;
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds0_osd0_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds0_osd0_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;        
        isp_reg_writel(isp,stOsd0YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD0_Y_RANGE);
    }
   
    if(OsdIndex == 1)
    {
    	U_ISP_DS0_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds0_osd1_type = OsdAttr->OsdInfo.osd_type;
        stOsd1Info.bits.ds0_osd1_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds0_osd1_enable = OsdAttr->OsdInfo.osd_enable;        
        isp_reg_writel(isp,stOsd1Info.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_INFO);

    	U_ISP_DS0_OSD1_SIZE stOsd1Size;  
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds0_osd1_width = OsdAttr->OsdSize.Width;
        stOsd1Size.bits.ds0_osd1_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd1Size.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_SIZE);

    	U_ISP_DS0_OSD1_BUF_ADDR0 stOsd1Addr0;   
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds0_osd1_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd1Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_BUF_ADDR0);
        
        U_ISP_DS0_OSD1_BUF_ADDR1 stOsd1Addr1;
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds0_osd1_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd1Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_BUF_ADDR1);

    	U_ISP_DS0_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0;   
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds0_osd1_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd1AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_ALPHA_BUF_ADDR0);

    	U_ISP_DS0_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds0_osd1_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd1AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_ALPHA_BUF_ADDR1);

    	U_ISP_DS0_OSD1_DMA_CTL stOsd1DmaCtl;   
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds0_osd1_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds0_osd1_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds0_osd1_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds0_osd1_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds0_osd1_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds0_osd1_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds0_osd1_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd1DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_DMA_CTL);
        
        U_ISP_DS0_OSD1_STRIDE stOsd1Stride;
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds0_osd1_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd1Stride.bits.ds0_osd1_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd1Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_STRIDE);

	    U_ISP_DS0_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds0_osd1_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds0_osd1_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd1XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_X_RANGE);
        
        U_ISP_DS0_OSD1_Y_RANGE stOsd1YRange;
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds0_osd1_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds0_osd1_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd1YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD1_Y_RANGE);
    }
 
    if(OsdIndex == 2)
    {
    	U_ISP_DS0_OSD2_INFO stOsd2Info; 
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds0_osd2_type = OsdAttr->OsdInfo.osd_type;
        stOsd2Info.bits.ds0_osd2_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds0_osd2_enable = OsdAttr->OsdInfo.osd_enable;        
        isp_reg_writel(isp,stOsd2Info.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_INFO);

    	U_ISP_DS0_OSD2_SIZE stOsd2Size; 
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds0_osd2_width = OsdAttr->OsdSize.Width;
        stOsd2Size.bits.ds0_osd2_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd2Size.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_SIZE);

    	U_ISP_DS0_OSD2_BUF_ADDR0 stOsd2Addr0;
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds0_osd2_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd2Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_BUF_ADDR0);

        U_ISP_DS0_OSD2_BUF_ADDR1 stOsd2Addr1;
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds0_osd2_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd2Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_BUF_ADDR1);

    	U_ISP_DS0_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0; 
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds0_osd2_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd2AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_ALPHA_BUF_ADDR0);

    	U_ISP_DS0_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds0_osd2_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd2AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_ALPHA_BUF_ADDR1);

    	U_ISP_DS0_OSD2_DMA_CTL stOsd2DmaCtl;
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds0_osd2_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds0_osd2_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds0_osd2_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds0_osd2_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds0_osd2_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds0_osd2_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds0_osd2_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd2DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_DMA_CTL);
        
    	U_ISP_DS0_OSD2_STRIDE stOsd2Stride;
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds0_osd2_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd2Stride.bits.ds0_osd2_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd2Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_STRIDE);

	    U_ISP_DS0_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds0_osd2_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds0_osd2_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp, stOsd2XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_X_RANGE);
        
    	U_ISP_DS0_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds0_osd2_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds0_osd2_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd2YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS0_OSD2_Y_RANGE);
    }
}

static void Isp_Drv_R2k_Ds_SetDs1OsdAttr(struct isp_device *isp,unsigned char OsdIndex,ISP_DS_OSD_ATTR_S *OsdAttr)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(OsdAttr);

    if(OsdIndex == 0)
    {
    	U_ISP_DS1_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds1_osd0_type = OsdAttr->OsdInfo.osd_type;
        stOsd0Info.bits.ds1_osd0_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds1_osd0_enable = OsdAttr->OsdInfo.osd_enable;
        isp_reg_writel(isp,stOsd0Info.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_INFO);

    	U_ISP_DS1_OSD0_SIZE stOsd0Size;   
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds1_osd0_width = OsdAttr->OsdSize.Width;
        stOsd0Size.bits.ds1_osd0_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd0Size.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_SIZE);

    	U_ISP_DS1_OSD0_BUF_ADDR0 stOsd0Addr0; 
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds1_osd0_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd0Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_BUF_ADDR0);

    	U_ISP_DS1_OSD0_BUF_ADDR1 stOsd0Addr1; 
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds1_osd0_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd0Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_BUF_ADDR1);

        U_ISP_DS1_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;    	
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds1_osd0_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd0AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_ALPHA_BUF_ADDR0);

    	U_ISP_DS1_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds1_osd0_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd0AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_ALPHA_BUF_ADDR1);

    	U_ISP_DS1_OSD0_DMA_CTL stOsd0DmaCtl;   
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds1_osd0_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds1_osd0_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds1_osd0_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds1_osd0_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds1_osd0_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds1_osd0_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds1_osd0_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd0DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_DMA_CTL);
        
    	U_ISP_DS1_OSD0_STRIDE stOsd0Stride;
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds1_osd0_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd0Stride.bits.ds1_osd0_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd0Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_STRIDE);

    	U_ISP_DS1_OSD0_X_RANGE stOsd0XRange;	
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds1_osd0_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds1_osd0_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd0XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_X_RANGE);
        
        U_ISP_DS1_OSD0_Y_RANGE stOsd0YRange;
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds1_osd0_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds1_osd0_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd0YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD0_Y_RANGE);
    }
   
    if(OsdIndex == 1)
    {
    	U_ISP_DS1_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds1_osd1_type = OsdAttr->OsdInfo.osd_type;
        stOsd1Info.bits.ds1_osd1_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds1_osd1_enable = OsdAttr->OsdInfo.osd_enable;        
        isp_reg_writel(isp,stOsd1Info.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_INFO);

    	U_ISP_DS1_OSD1_SIZE stOsd1Size;  
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds1_osd1_width = OsdAttr->OsdSize.Width;
        stOsd1Size.bits.ds1_osd1_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd1Size.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_SIZE);
        
    	U_ISP_DS1_OSD1_BUF_ADDR0 stOsd1Addr0;
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds1_osd1_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd1Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_BUF_ADDR0);

    	U_ISP_DS1_OSD1_BUF_ADDR1 stOsd1Addr1;
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds1_osd1_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd1Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_BUF_ADDR1);

    	
        U_ISP_DS1_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0;     
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds1_osd1_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd1AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_ALPHA_BUF_ADDR0);

	    U_ISP_DS1_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds1_osd1_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd1AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_ALPHA_BUF_ADDR1);

    	U_ISP_DS1_OSD1_DMA_CTL stOsd1DmaCtl;   
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds1_osd1_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds1_osd1_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds1_osd1_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds1_osd1_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds1_osd1_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds1_osd1_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds1_osd1_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd1DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_DMA_CTL);

    	U_ISP_DS1_OSD1_STRIDE stOsd1Stride;    
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds1_osd1_osd_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd1Stride.bits.ds1_osd1_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd1Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_STRIDE);

    	U_ISP_DS1_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds1_osd1_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds1_osd1_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd1XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_X_RANGE);

    	U_ISP_DS1_OSD1_Y_RANGE stOsd1YRange;     
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds1_osd1_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds1_osd1_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd1YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD1_Y_RANGE);
    }
   
    if(OsdIndex == 2)
    {
    	U_ISP_DS1_OSD2_INFO stOsd2Info;
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds1_osd2_type = OsdAttr->OsdInfo.osd_type;
        stOsd2Info.bits.ds1_osd2_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds1_osd2_enable = OsdAttr->OsdInfo.osd_enable;        
        isp_reg_writel(isp,stOsd2Info.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_INFO);

    	U_ISP_DS1_OSD2_SIZE stOsd2Size;
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds1_osd2_width = OsdAttr->OsdSize.Width;
        stOsd2Size.bits.ds1_osd2_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd2Size.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_SIZE);

    	U_ISP_DS1_OSD2_BUF_ADDR0 stOsd2Addr0;  
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds1_osd2_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd2Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_BUF_ADDR0);

    	U_ISP_DS1_OSD2_BUF_ADDR1 stOsd2Addr1;     
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds1_osd2_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd2Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_BUF_ADDR1);

    	U_ISP_DS1_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0;
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds1_osd2_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd2AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_ALPHA_BUF_ADDR0);

    	U_ISP_DS1_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds1_osd2_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd2AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_ALPHA_BUF_ADDR1);

    	U_ISP_DS1_OSD2_DMA_CTL stOsd2DmaCtl;   
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds1_osd2_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds1_osd2_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds1_osd2_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds1_osd2_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds1_osd2_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds1_osd2_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds1_osd2_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd2DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_DMA_CTL);
        
    	U_ISP_DS1_OSD2_STRIDE stOsd2Stride;
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds1_osd2_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd2Stride.bits.ds1_osd2_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd2Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_STRIDE);

	    U_ISP_DS1_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds1_osd2_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds1_osd2_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd2XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_X_RANGE);
        
    	U_ISP_DS1_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds1_osd2_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds1_osd2_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd2YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS1_OSD2_Y_RANGE);
    }
}

static void Isp_Drv_R2k_Ds_SetDs2OsdAttr(struct isp_device *isp,unsigned char OsdIndex,ISP_DS_OSD_ATTR_S *OsdAttr)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(OsdAttr);

    if(OsdIndex == 0)
    {
	    U_ISP_DS2_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds2_osd0_type = OsdAttr->OsdInfo.osd_type;
        stOsd0Info.bits.ds2_osd0_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds2_osd0_enable = OsdAttr->OsdInfo.osd_enable;        
        isp_reg_writel(isp,stOsd0Info.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_INFO);

    	U_ISP_DS2_OSD0_SIZE stOsd0Size; 
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds2_osd0_width = OsdAttr->OsdSize.Width;
        stOsd0Size.bits.ds2_osd0_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd0Size.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_SIZE);

    	U_ISP_DS2_OSD0_BUF_ADDR0 stOsd0Addr0;    
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds2_osd0_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd0Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_BUF_ADDR0);

    	U_ISP_DS2_OSD0_BUF_ADDR1 stOsd0Addr1;    	   
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds2_osd0_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd0Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_BUF_ADDR1);

        U_ISP_DS2_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;   
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds2_osd0_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd0AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_ALPHA_BUF_ADDR0);

    	U_ISP_DS2_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds2_osd0_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd0AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_ALPHA_BUF_ADDR1);
        
    	U_ISP_DS2_OSD0_DMA_CTL stOsd0DmaCtl;
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds2_osd0_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds2_osd0_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds2_osd0_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds2_osd0_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds2_osd0_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds2_osd0_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds2_osd0_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd0DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_DMA_CTL);

    	U_ISP_DS2_OSD0_STRIDE stOsd0Stride;
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds2_osd0_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd0Stride.bits.ds2_osd0_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd0Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_STRIDE);

    	U_ISP_DS2_OSD0_X_RANGE stOsd0XRange;
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds2_osd0_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds2_osd0_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd0XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_X_RANGE);

    	U_ISP_DS2_OSD0_Y_RANGE stOsd0YRange;    
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds2_osd0_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds2_osd0_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd0YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD0_Y_RANGE);
    }
   
    if(OsdIndex == 1)
    {
    	U_ISP_DS2_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds2_osd1_type = OsdAttr->OsdInfo.osd_type;
        stOsd1Info.bits.ds2_osd1_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds2_osd1_enable = OsdAttr->OsdInfo.osd_enable;                
        isp_reg_writel(isp,stOsd1Info.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_INFO);

    	U_ISP_DS2_OSD1_SIZE stOsd1Size; 
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds2_osd1_width = OsdAttr->OsdSize.Width;
        stOsd1Size.bits.ds2_osd1_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd1Size.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_SIZE);

    	U_ISP_DS2_OSD1_BUF_ADDR0 stOsd1Addr0;  
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds2_osd1_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd1Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_BUF_ADDR0);

    	U_ISP_DS2_OSD1_BUF_ADDR1 stOsd1Addr1;     
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds2_osd1_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd1Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_BUF_ADDR1);

    	U_ISP_DS2_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0; 
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds2_osd1_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd1AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_ALPHA_BUF_ADDR0);

    	U_ISP_DS2_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds2_osd1_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd1AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_ALPHA_BUF_ADDR1);

    	U_ISP_DS2_OSD1_DMA_CTL stOsd1DmaCtl;     
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds2_osd1_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds2_osd1_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds2_osd1_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds2_osd1_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds2_osd1_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds2_osd1_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds2_osd1_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds2_osd1_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;        
        isp_reg_writel(isp,stOsd1DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_DMA_CTL);

    	U_ISP_DS2_OSD1_STRIDE stOsd1Stride;  
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds2_osd1_osd_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd1Stride.bits.ds2_osd1_osd_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd1Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_STRIDE);

    	U_ISP_DS2_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds2_osd1_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds2_osd1_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd1XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_X_RANGE);

    	U_ISP_DS2_OSD1_Y_RANGE stOsd1YRange;     
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds2_osd1_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds2_osd1_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd1YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD1_Y_RANGE);
    }
  
    if(OsdIndex == 2)
    {
    	U_ISP_DS2_OSD2_INFO stOsd2Info;
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds2_osd2_type = OsdAttr->OsdInfo.osd_type;
        stOsd2Info.bits.ds2_osd2_alpha_tpye = OsdAttr->OsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds2_osd2_enable = OsdAttr->OsdInfo.osd_enable;                
        isp_reg_writel(isp,stOsd2Info.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_INFO);

    	U_ISP_DS2_OSD2_SIZE stOsd2Size; 
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds2_osd2_width = OsdAttr->OsdSize.Width;
        stOsd2Size.bits.ds2_osd2_height = OsdAttr->OsdSize.Height;
        isp_reg_writel(isp,stOsd2Size.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_SIZE);

    	U_ISP_DS2_OSD2_BUF_ADDR0 stOsd2Addr0;   
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds2_osd2_rgb_addr0 = OsdAttr->OsdBuf.osd_rgb_addr0;
        isp_reg_writel(isp,stOsd2Addr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_BUF_ADDR0);
        
    	U_ISP_DS2_OSD2_BUF_ADDR1 stOsd2Addr1; 
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds2_osd2_rgb_addr1 = OsdAttr->OsdBuf.osd_rgb_addr1;
        isp_reg_writel(isp,stOsd2Addr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_BUF_ADDR1);

    	U_ISP_DS2_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0; 
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds2_osd2_alpha_addr0 = OsdAttr->OsdBuf.osd_alpha_addr0;
        isp_reg_writel(isp,stOsd2AlphaAddr0.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_ALPHA_BUF_ADDR0);

    	U_ISP_DS2_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds2_osd2_alpha_addr1 = OsdAttr->OsdBuf.osd_alpha_addr1;
        isp_reg_writel(isp,stOsd2AlphaAddr1.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_ALPHA_BUF_ADDR1);

    	U_ISP_DS2_OSD2_DMA_CTL stOsd2DmaCtl;  
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds2_osd2_dma_request_length = OsdAttr->OsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds2_osd2_dma_map = OsdAttr->OsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds2_osd2_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds2_osd2_rgb_rev = OsdAttr->OsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds2_osd2_global_alpha = OsdAttr->OsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds2_osd2_swap_64 = OsdAttr->OsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds2_osd2_outstanding_num = OsdAttr->OsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds2_osd2_bd_limit_en = OsdAttr->OsdDmaCtl.osd_bd_limit_en;                
        isp_reg_writel(isp,stOsd2DmaCtl.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_DMA_CTL);

    	U_ISP_DS2_OSD2_STRIDE stOsd2Stride;   
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds2_osd2_stride = OsdAttr->OsdBuf.osd_stride >> 3;
        stOsd2Stride.bits.ds2_osd2_alpha_stride = OsdAttr->OsdBuf.osd_alpha_stride >> 3;
        isp_reg_writel(isp,stOsd2Stride.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_STRIDE);

    	U_ISP_DS2_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds2_osd2_start_x = OsdAttr->OsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds2_osd2_stop_x = OsdAttr->OsdBuf.osd_position_stop_x;
        isp_reg_writel(isp,stOsd2XRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_X_RANGE);
        
        U_ISP_DS2_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds2_osd2_start_y = OsdAttr->OsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds2_osd2_stop_y = OsdAttr->OsdBuf.osd_position_stop_y;
        isp_reg_writel(isp,stOsd2YRange.u32,ISP_IOMEM_R2K_DS,ISP_DS2_OSD2_Y_RANGE);
    }
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetVCoef(struct isp_device *isp,int a[],int num)
{
	ISP_CHECK_POINTER(isp);

    for (int i =0;i<num; i++)
    {
		isp_reg_writel(isp,a[i*2],ISP_IOMEM_R2K_DS,ISP_VSCALE_COFF_BASE+((i*2)<<2));
		isp_reg_writel(isp,a[i*2+1],ISP_IOMEM_R2K_DS,ISP_VSCALE_COFF_BASE+((i*2+1)<<2));
    }
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetHCoef0(struct isp_device *isp,int a[],int num)
{
    ISP_CHECK_POINTER(isp);

    for (int i =0;i<num; i++)
    {
 		isp_reg_writel(isp,a[i*3],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_0_BASE+((i*4)<<2));
		isp_reg_writel(isp,a[i*3+1],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_0_BASE+((i*4+1)<<2));
		isp_reg_writel(isp,a[i*3+2],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_0_BASE+((i*4+2)<<2));
    }

}
/*
*
*/
void Isp_Drv_R2k_Ds_SetHCoef1(struct isp_device *isp,int a[],int num)
{
    ISP_CHECK_POINTER(isp);

    for (int i =0;i<num; i++)
    {
 		isp_reg_writel(isp,a[i*3],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_1_BASE+((i*4)<<2));
		isp_reg_writel(isp,a[i*3+1],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_1_BASE+((i*4+1)<<2));
		isp_reg_writel(isp,a[i*3+2],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_1_BASE+((i*4+2)<<2));
    }

}
/*
*
*/
void Isp_Drv_R2k_Ds_SetHCoef2(struct isp_device *isp,int a[],int num)
{
    ISP_CHECK_POINTER(isp);

    for (int i =0;i<num; i++)
    {
 		isp_reg_writel(isp,a[i*3],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_2_BASE+((i*4)<<2));
		isp_reg_writel(isp,a[i*3+1],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_2_BASE+((i*4+1)<<2));
		isp_reg_writel(isp,a[i*3+2],ISP_IOMEM_R2K_DS,ISP_HSCALE_COFF_2_BASE+((i*4+2)<<2));
    }
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetscaleCoeff(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);

	Isp_Drv_R2k_Ds_SetVCoef(isp,ISP_DS_V_Coef_TABLE,64);
	Isp_Drv_R2k_Ds_SetHCoef0(isp,ISP_DS_H_Coef_TABLE,64);
	Isp_Drv_R2k_Ds_SetHCoef1(isp,ISP_DS_H_Coef_TABLE,64);
	Isp_Drv_R2k_Ds_SetHCoef2(isp,ISP_DS_H_Coef_TABLE,64);
}
/*
*
*/
void Isp_Drv_R2k_Ds_SetSingleDS(struct isp_device *isp,unsigned char Index,ISP_S_DS_ATTR_S *stDsAttr)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(stDsAttr);

    ISP_DS_HSCALE_PARM_S *Hscale = &stDsAttr->hscalePram;
	Isp_Drv_R2k_Ds_SetHscaleParam(isp,Index,Hscale);

    ISP_DS_VSCALE_PARM_S *Vscale = &stDsAttr->vscalePram;
    Isp_Drv_R2k_Ds_SetVscaleParam(isp,Index,Vscale);
	
    ISP_DS_SIZE_S *DsSize = &stDsAttr->dsOutSize;
	Isp_Drv_R2k_Ds_SetOutputSize(isp,Index,DsSize);
	
    ISP_DS_FORMAT_S *Format = &stDsAttr->DsFormat;	
	Isp_Drv_R2k_Ds_SetOutputFormat(isp,Index,Format);

    unsigned char  OsdIndex = 0;
    ISP_DS_OSD_ATTR_S *OsdAttr = &stDsAttr->DsOsdAttr[OsdIndex];
    Isp_Drv_R2k_Ds_SetDs0OsdAttr(isp,OsdIndex,OsdAttr);

    OsdIndex = 1;
    OsdAttr = &stDsAttr->DsOsdAttr[OsdIndex];
    Isp_Drv_R2k_Ds_SetDs1OsdAttr(isp,OsdIndex,OsdAttr);

    OsdIndex = 2;
    OsdAttr = &stDsAttr->DsOsdAttr[OsdIndex];
    Isp_Drv_R2k_Ds_SetDs2OsdAttr(isp,OsdIndex,OsdAttr);
}