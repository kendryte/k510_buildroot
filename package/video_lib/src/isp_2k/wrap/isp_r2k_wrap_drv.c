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
 * isp_r2k_wrap_drv.c
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#include "isp_com.h"
#include "isp_2k/wrap/isp_wrap_drv.h"
#include "isp_2k/wrap/isp_wrap_reg.h"

/*
* reset 
*/
void Isp_Drv_R2k_Wrap_SetPipeReset(struct isp_device *isp,ISP_WRAP_RST_CTL_S *pstRstCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstRstCtl);

	U_ISP_WRAP_SWRST_CTL stData;
	stData.u32 = 0;
	stData.bits.sw_3dnr_rst = pstRstCtl->sw_3dnr_rst;    
	stData.bits.wdr_2_frame_rst = pstRstCtl->wdr_2_frame_rst;
	stData.bits.wdr_3_frame_rst =pstRstCtl->wdr_3_frame_rst;
	stData.bits.ldc_rst = pstRstCtl->ldc_rst; 
	
	stData.bits.main_out_rst = pstRstCtl->main_out_rst;   
	stData.bits.ds0_out_rst = pstRstCtl->ds0_out_rst;    
	stData.bits.ds1_out_rst = pstRstCtl->ds1_out_rst;   
	stData.bits.ds2_out_rst = pstRstCtl->ds2_out_rst; 
	
	stData.bits.wrap_com_rst = pstRstCtl->wrap_com_rst;   
	stData.bits.wrap_cfg_rst = pstRstCtl->wrap_com_rst;   
	stData.bits.core_com_rst = pstRstCtl->core_com_rst;   
	stData.bits.core_cfg_rst = pstRstCtl->core_cfg_rst; 
	
	stData.bits.axi_wr_ch_rst = pstRstCtl->axi_wr_ch_rst;  
	stData.bits.axi_rd_ch_rst = pstRstCtl->axi_rd_ch_rst;  
	//stData.u32 = 0x000fffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_SWRST_CTL);

}
/*
* DMA reset 
*/
void Isp_Drv_R2k_Wrap_SetDmaReset(struct isp_device *isp,ISP_WRAP_DMA_RST_CTL_S *pstDmaRstCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaRstCtl);

	U_ISP_WRAP_DMA_SWRST_CTL stData;	
	stData.u32 = 0;
	stData.bits.y_3dnr_wr_ch_rst = pstDmaRstCtl->y_3dnr_wr_ch_rst;     
	stData.bits.uv_3dnr_wr_ch_rst = pstDmaRstCtl->uv_3dnr_wr_ch_rst;    
	stData.bits.ldc_y_wr_ch_rst = pstDmaRstCtl->ldc_y_wr_ch_rst;      
	stData.bits.ldc_uv_wr_ch_rst = pstDmaRstCtl->ldc_uv_wr_ch_rst;     
	stData.bits.wdr_raw_wr_ch_rst = pstDmaRstCtl->wdr_raw_wr_ch_rst;    
	stData.bits.main_out_y_wr_ch_rst = pstDmaRstCtl->main_out_y_wr_ch_rst; 
	stData.bits.main_out_uv_wr_ch_rst= pstDmaRstCtl->main_out_uv_wr_ch_rst;
	stData.bits.y_3dnr_rd_ch_rst = pstDmaRstCtl->y_3dnr_rd_ch_rst;     
	stData.bits.uv_3dnr_rd_ch_rst = pstDmaRstCtl->uv_3dnr_rd_ch_rst;    
	stData.bits.ldc_y_rd_ch_rst = pstDmaRstCtl->ldc_y_rd_ch_rst;      
	stData.bits.ldc_uv_rd_ch_rst = pstDmaRstCtl->ldc_uv_rd_ch_rst;     
	stData.bits.wdr_raw_rd_ch_rst = pstDmaRstCtl->wdr_raw_rd_ch_rst;    
	stData.bits.ds0_out_y_wr_ch_rst = pstDmaRstCtl->ds0_out_y_wr_ch_rst;  
	stData.bits.ds0_out_uv_wr_ch_rst = pstDmaRstCtl->ds0_out_uv_wr_ch_rst; 
	stData.bits.ds1_out_y_wr_ch_rst = pstDmaRstCtl->ds1_out_y_wr_ch_rst;  
	stData.bits.ds1_out_uv_wr_ch_rst = pstDmaRstCtl->ds1_out_uv_wr_ch_rst; 
	stData.bits.ds2_out_r_wr_ch_rst = pstDmaRstCtl->ds2_out_r_wr_ch_rst;  
	stData.bits.ds2_out_g_wr_ch_rst = pstDmaRstCtl->ds2_out_g_wr_ch_rst;  
	stData.bits.ds2_out_b_wr_ch_rst = pstDmaRstCtl->ds2_out_b_wr_ch_rst;  
	stData.bits.ds0_osd0_rd_ch_rst = pstDmaRstCtl->ds0_osd0_rd_ch_rst;   
	stData.bits.ds0_osd1_rd_ch_rst = pstDmaRstCtl->ds0_osd1_rd_ch_rst;   
	stData.bits.ds1_osd0_rd_ch_rst = pstDmaRstCtl->ds1_osd0_rd_ch_rst;   
	stData.bits.ds1_osd1_rd_ch_rst = pstDmaRstCtl->ds1_osd1_rd_ch_rst;   
    stData.bits.ds2_osd0_rd_ch_rst = pstDmaRstCtl->ds2_osd0_rd_ch_rst;   
	stData.bits.ds2_osd1_rd_ch_rst = pstDmaRstCtl->ds2_osd1_rd_ch_rst;
    stData.bits.ds2_osd2_rd_ch_rst = pstDmaRstCtl->ds2_osd2_rd_ch_rst;   	
	//stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_SWRST_CTL);

}
/*
* ctl mode 
*/
int Isp_Drv_R2k_Wrap_SetModeCtl_OutSel(struct isp_device *isp,unsigned int external_out_ch_sel)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.external_out_ch_sel = external_out_ch_sel;   
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_DvpMode(struct isp_device *isp,unsigned int dvp_input_ch_type)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.dvp_input_ch_type = dvp_input_ch_type;    
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

static int Isp_Drv_R2k_Wrap_SetModeCtl_Wdr(struct isp_device *isp,ISP_WRAP_WDR_MODE_CTL_S *pstWdrModeCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrModeCtl);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.wdr_long_ch_mode = pstWdrModeCtl->wdr_long_ch_mode;    
	stData.bits.wdr_long_l2_buf_en = pstWdrModeCtl->wdr_long_l2_buf_en;  
	stData.bits.wdr_short_s1_buf_en = pstWdrModeCtl->wdr_short_s1_buf_en; 
	stData.bits.wdr_dynamic_switch_en = pstWdrModeCtl->wdr_dynamic_switch_en;
	stData.bits.wdr_long_l2_buf_depth = pstWdrModeCtl->wdr_long_l2_buf_depth;  
//	stData.u32 = 0x700004;	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_3dnr_fbcd_en(struct isp_device *isp,unsigned int nr3d_fbcd_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.nr3d_fbcd_en = nr3d_fbcd_en;
    //	stData.u32 = 0x700004;	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_3dnr_mv_en(struct isp_device *isp,unsigned int nr3d_mv_out_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.nr3d_mv_out_en = nr3d_mv_out_en; 
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_3a_out_en(struct isp_device *isp,unsigned int hist_3a_out_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.hist_3a_out_en = hist_3a_out_en;
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_remap_main_en(struct isp_device *isp,unsigned int pix_remap_main_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.pix_remap_main_en = pix_remap_main_en;
//	stData.u32 = 0x700004;

	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_remap_out0_en(struct isp_device *isp,unsigned int pix_remap_out0_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.pix_remap_out0_en = pix_remap_out0_en;
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetModeCtl_remap_out1_en(struct isp_device *isp,unsigned int pix_remap_out1_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	stData.bits.pix_remap_out1_en = pix_remap_out1_en;
//	stData.u32 = 0x700004;
	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CTL_MODE);
	return 0;
}
/*
*CLOCK CTRL
*/
void Isp_Drv_R2k_Wrap_SetComClkCtl(struct isp_device *isp,ISP_WRAP_PIPE_CLK_CTL_S *pstPipeClkCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstPipeClkCtl);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.wrap_com_clk_en = pstPipeClkCtl->wrap_com_clk_en;       
	stData.bits.wrap_cfg_clk_en = pstPipeClkCtl->wrap_cfg_clk_en;       
	stData.bits.core_com_clk_en = pstPipeClkCtl->core_com_clk_en;       
	stData.bits.core_cfg_clk_en = pstPipeClkCtl->core_cfg_clk_en;
	
	stData.bits.axi_wr_ch_en 	= pstPipeClkCtl->axi_wr_ch_en;          
	stData.bits.axi_rd_ch_en 	= pstPipeClkCtl->axi_rd_ch_en;        
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	
}

static void Isp_Drv_R2k_Wrap_Set3DnrClkCtl(struct isp_device *isp,signed int clk_3dnr_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.clk_3dnr_en = clk_3dnr_en;          
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	
}

static void Isp_Drv_R2k_Wrap_SetWdrClkCtl(struct isp_device *isp,ISP_WRAP_WDR_CLK_CTL_S *pstWdrClkCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrClkCtl);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.wdr_2_frame_clk_en = pstWdrClkCtl->wdr_2_frame_clk_en;    
	stData.bits.wdr_3_frame_clk_en = pstWdrClkCtl->wdr_3_frame_clk_en;	
      
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
}

static void Isp_Drv_R2k_Wrap_SetLdcClkCtl(struct isp_device *isp,unsigned int ldc_clk_en)
{
	ISP_CHECK_POINTER(isp);
	
	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.ldc_clk_en = ldc_clk_en;        
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
}

static void Isp_Drv_R2k_Wrap_SetMainClkCtl(struct isp_device *isp,unsigned int main_out_clk_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.main_out_clk_en = main_out_clk_en;          
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	return ;	
}

static void Isp_Drv_R2k_Wrap_SetDs0ClkCtl(struct isp_device *isp,ISP_WRAP_DS0_CLK_CTL_S *pstDs0ClkCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs0ClkCtl);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL); 
	stData.bits.ds0_out_clk_en          = pstDs0ClkCtl->ds0_out_clk_en;
	stData.bits.ds0_out_y_ch_clk_en 	= pstDs0ClkCtl->ds0_out_y_ch_clk_en;   
	stData.bits.ds0_out_uv_ch_clk_en 	= pstDs0ClkCtl->ds0_out_uv_ch_clk_en;
    stData.bits.ds_out0_osd0_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd0_ch_clk_en;
	stData.bits.ds_out0_osd1_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd1_ch_clk_en;
	stData.bits.ds_out0_osd2_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd2_ch_clk_en;          
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	return ;	
}

static void Isp_Drv_R2k_Wrap_SetDs1ClkCtl(struct isp_device *isp,ISP_WRAP_DS1_CLK_CTL_S *pstDs1ClkCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs1ClkCtl);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.ds1_out_clk_en 			= pstDs1ClkCtl->ds1_out_clk_en;  
 	stData.bits.ds1_out_y_ch_clk_en 	= pstDs1ClkCtl->ds1_out_y_ch_clk_en;   
	stData.bits.ds1_out_uv_ch_clk_en 	= pstDs1ClkCtl->ds1_out_uv_ch_clk_en;    
	stData.bits.ds_out1_osd0_ch_clk_en  = pstDs1ClkCtl->ds_out1_osd0_ch_clk_en;	
	stData.bits.ds_out1_osd1_ch_clk_en 	= pstDs1ClkCtl->ds_out1_osd1_ch_clk_en;
	stData.bits.ds_out1_osd2_ch_clk_en 	= pstDs1ClkCtl->ds_out1_osd2_ch_clk_en;
       
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetDs2ClkCtl(struct isp_device *isp,ISP_WRAP_DS2_CLK_CTL_S *pstDs2ClkCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs2ClkCtl);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);
	stData.bits.ds2_out_clk_en 			= pstDs2ClkCtl->ds2_out_clk_en; 
	stData.bits.ds2_out_r_ch_clk_en 	= pstDs2ClkCtl->ds2_out_r_ch_clk_en;   
	stData.bits.ds2_out_g_ch_clk_en 	= pstDs2ClkCtl->ds2_out_g_ch_clk_en;	
	stData.bits.ds2_out_b_ch_clk_en 	= pstDs2ClkCtl->ds2_out_b_ch_clk_en;
	stData.bits.ds_out2_osd0_ch_clk_en 	= pstDs2ClkCtl->ds_out2_osd0_ch_clk_en;
	stData.bits.ds_out2_osd1_ch_clk_en 	= pstDs2ClkCtl->ds_out2_osd1_ch_clk_en;       
	//stData.u32 = 0xffffffff;
	stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIPE_CLK_CTL);	
}
/*
*DMA EN
*/
static void Isp_Drv_R2k_Wrap_Set3dnrDmaEnCtl(struct isp_device *isp,unsigned int pipe_3dnr_dma_en)
{	
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);
	stData.bits.pipe_3dnr_dma_en = pipe_3dnr_dma_en;     
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetWdrDmaEnCtl(struct isp_device *isp,ISP_WRAP_WDR_DMA_EN_CTL_S *pstWdrDmaEn)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrDmaEn);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);

	stData.bits.wdr_long_dma_en = pstWdrDmaEn->wdr_long_dma_en;
	stData.bits.wdr_short_dma_en = pstWdrDmaEn->wdr_short_dma_en; 
 
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetLdcDmaEnCtl(struct isp_device *isp,unsigned int ldc_dma_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);
	stData.bits.ldc_dma_en = ldc_dma_en;    
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetMainDmaEnCtl(struct isp_device *isp,unsigned int main_out_dma_en)
{
	ISP_CHECK_POINTER(isp);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);
	stData.bits.main_out_dma_en = main_out_dma_en;     
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetDs0DmaEnCtl(struct isp_device *isp,ISP_WRAP_DS0_DMA_EN_CTL_S *pstDs0DMAEnCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs0DMAEnCtl);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);
	stData.bits.ds_out0_dma_en = pstDs0DMAEnCtl->ds_out0_dma_en;
    stData.bits.ds_out0_y_ch_dma_en = pstDs0DMAEnCtl->ds_out0_y_ch_dma_en; 
    stData.bits.ds_out0_uv_ch_dma_en = pstDs0DMAEnCtl->ds_out0_uv_ch_dma_en;
    stData.bits.ds0_osd0_ch_dma_en = pstDs0DMAEnCtl->ds0_osd0_ch_dma_en; 
	stData.bits.ds0_osd1_ch_dma_en = pstDs0DMAEnCtl->ds0_osd1_ch_dma_en;
	stData.bits.ds0_osd2_ch_dma_en = pstDs0DMAEnCtl->ds0_osd2_ch_dma_en;  	      
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetDs1DmaEnCtl(struct isp_device *isp,ISP_WRAP_DS1_DMA_EN_CTL_S *pstDs1DMAEnCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs1DMAEnCtl);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);
	stData.bits.ds_out1_dma_en = pstDs1DMAEnCtl->ds_out1_dma_en; 
    stData.bits.ds_out1_y_ch_dma_en = pstDs1DMAEnCtl->ds_out1_y_ch_dma_en; 
    stData.bits.ds_out1_uv_ch_dma_en = pstDs1DMAEnCtl->ds_out1_uv_ch_dma_en;
    stData.bits.ds1_osd0_ch_dma_en = pstDs1DMAEnCtl->ds1_osd0_ch_dma_en;  
    stData.bits.ds1_osd1_ch_dma_en = pstDs1DMAEnCtl->ds1_osd1_ch_dma_en;
	stData.bits.ds1_osd2_ch_dma_en = pstDs1DMAEnCtl->ds1_osd2_ch_dma_en;  	 	      
	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}

static void Isp_Drv_R2k_Wrap_SetDs2DmaEnCtl(struct isp_device *isp,ISP_WRAP_DS2_DMA_EN_CTL_S *pstDs2DMAEnCtl)
{	
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs2DMAEnCtl);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);    
    stData.bits.ds_out2_dma_en 			= pstDs2DMAEnCtl->ds_out2_dma_en;    
    stData.bits.ds_out2_r_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_r_ch_dma_en; 
    stData.bits.ds_out2_g_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_g_ch_dma_en; 
    stData.bits.ds_out2_b_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_b_ch_dma_en; 
    stData.bits.ds2_osd0_ch_dma_en 		= pstDs2DMAEnCtl->ds2_osd0_ch_dma_en;  
    stData.bits.ds2_osd1_ch_dma_en 		= pstDs2DMAEnCtl->ds2_osd1_ch_dma_en;  
 	//stData.u32 = 0xFF1F00F9;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_EN_CTL);	
}
/*
*3dnr format
*/
static int Isp_Drv_R2k_Wrap_Set3DnrFormatCtl(struct isp_device *isp,ISP_WRAP_3DNR_PIXEL_FORMAT_CTL_S *pst3DnrFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pst3DnrFormat);

    U_ISP_WRAP_3DNR_WDR_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_WDR_FORMAT_CTL);
	stData.bits.y_3dnr_img_format 			= pst3DnrFormat->y_3dnr_img_format;
	stData.bits.y_3dnr_img_out_format 		= pst3DnrFormat->y_3dnr_img_out_format;
	stData.bits.y_3dnr_pixel_width 			= pst3DnrFormat->y_3dnr_pixel_width;
	stData.bits.y_3dnr_yuv422_pxl_order 	= pst3DnrFormat->y_3dnr_yuv422_pxl_order;
	stData.bits.y_3dnr_yuv_in_format 		= pst3DnrFormat->y_3dnr_yuv_in_format;
	stData.bits.uv_3dnr_img_format 			= pst3DnrFormat->uv_3dnr_img_format;
	stData.bits.uv_3dnr_img_out_format 		= pst3DnrFormat->uv_3dnr_img_out_format;
	stData.bits.uv_3dnr_pixel_width 		= pst3DnrFormat->uv_3dnr_pixel_width;
	stData.bits.uv_3dnr_yuv422_pxl_order 	= pst3DnrFormat->uv_3dnr_yuv422_pxl_order;
	stData.bits.uv_3dnr_yuv_in_format 		= pst3DnrFormat->uv_3dnr_yuv_in_format;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_WDR_FORMAT_CTL);

	return 0;	
}
/*
*WDR
*/
static int Isp_Drv_R2k_Wrap_SetWdrFormatCtl(struct isp_device *isp,ISP_WRAP_WDR_PIXEL_FORMAT_CTL_S *pstWdrFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrFormat);

    U_ISP_WRAP_3DNR_WDR_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_WDR_FORMAT_CTL);
	stData.bits.wdr_long_img_format 		= pstWdrFormat->wdr_long_img_format;
	stData.bits.wdr_long_img_out_format 	= pstWdrFormat->wdr_long_img_out_format;
	stData.bits.wdr_long_pixel_width 		= pstWdrFormat->wdr_long_pixel_width;
	stData.bits.wdr_long_yuv422_pxl_order 	= pstWdrFormat->wdr_long_yuv422_pxl_order;
	stData.bits.wdr_long_yuv_in_format 		= pstWdrFormat->wdr_long_yuv_in_format;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_WDR_FORMAT_CTL);

	return 0;		
}
/*
*DS pixel format
*/
static int Isp_Drv_R2k_Wrap_SetMainPixelFormatCtl(struct isp_device *isp,ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *pstMainPixelFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstMainPixelFormat);

	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
    stData.bits.main_out_img_format = pstMainPixelFormat->main_out_img_format;   
    stData.bits.main_out_yuv_in_format = pstMainPixelFormat->main_out_yuv_in_format;   
    stData.bits.main_out_img_out_format = pstMainPixelFormat->main_out_img_out_format;  
    stData.bits.main_out_yuv422_pxl_order = pstMainPixelFormat->main_out_yuv422_pxl_order;
    stData.bits.main_out_pixel_width = pstMainPixelFormat->main_out_pixel_width; 
	//stData.u32 = 0x04050505;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDs0PixelFormatCtl(struct isp_device *isp,ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *pstDs0PixelFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs0PixelFormat);
	
	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
    stData.bits.ds0_out_img_format = pstDs0PixelFormat->ds0_out_img_format;   
    stData.bits.ds0_out_yuv_in_format = pstDs0PixelFormat->ds0_out_yuv_in_format;
    stData.bits.ds0_out_img_out_format = pstDs0PixelFormat->ds0_out_img_out_format;   
    stData.bits.ds0_out_yuv422_pxl_order = pstDs0PixelFormat->ds0_out_yuv422_pxl_order; 
    stData.bits.ds0_out_pixel_width = pstDs0PixelFormat->ds0_out_pixel_width;

	//stData.u32 = 0x04050505;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDs1PixelFormatCtl(struct isp_device *isp,ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *pstDs1PixelFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs1PixelFormat);
	
	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
    stData.bits.ds1_out_img_format = pstDs1PixelFormat->ds1_out_img_format;  
    stData.bits.ds1_out_yuv_in_format = pstDs1PixelFormat->ds1_out_yuv_in_format;
    stData.bits.ds1_out_img_out_format = pstDs1PixelFormat->ds1_out_img_out_format;   
    stData.bits.ds1_out_yuv422_pxl_order = pstDs1PixelFormat->ds1_out_yuv422_pxl_order; 
    stData.bits.ds1_out_pixel_width = pstDs1PixelFormat->ds1_out_pixel_width;    
	//stData.u32 = 0x04050505;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDs2PixelFormatCtl(struct isp_device *isp,ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *pstDs2PixelFormat)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs2PixelFormat);
	
	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
    stData.bits.ds2_out_img_format = pstDs2PixelFormat->ds2_out_img_format;  
    stData.bits.ds2_out_yuv_in_format = pstDs2PixelFormat->ds2_out_yuv_in_format; 
    stData.bits.ds2_out_img_out_format = pstDs2PixelFormat->ds2_out_img_out_format;   
    stData.bits.ds2_out_yuv422_pxl_order = pstDs2PixelFormat->ds2_out_yuv422_pxl_order; 
    stData.bits.ds2_out_pixel_width = pstDs2PixelFormat->ds2_out_pixel_width;
	//printf("pstDs2PixelFormat->ds2_out_img_out_format =0x%x\n",pstDs2PixelFormat->ds2_out_img_out_format);    
	//stData.u32 = 0x04050505;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_PIXEL_FORMAT_CTL);
	return 0;
}
/*
*DS out size
*/
static int Isp_Drv_R2k_Wrap_SetMainOutSize(struct isp_device *isp,ISP_WRAP_MAIN_OUT_SIZE_S *stMainOutSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stMainOutSize);
	
	U_ISP_WRAP_MAIN_OUT_SIZE stMainData;
	stMainData.u32 = 0;
	stMainData.bits.main_out_v_size = stMainOutSize->main_out_v_size;   
	stMainData.bits.main_out_h_size = stMainOutSize->main_out_h_size;    
	isp_reg_writel(isp,stMainData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_OUT_SIZE);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDs0OutSize(struct isp_device *isp,ISP_WRAP_DS0_OUT_SIZE_S *stDs0OutSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stDs0OutSize);

	U_ISP_WRAP_DS0_OUT_SIZE stDS0Data;
	stDS0Data.u32 = 0;
	stDS0Data.bits.ds0_out_v_size = stDs0OutSize->ds0_out_v_size;   
	stDS0Data.bits.ds0_out_h_size = stDs0OutSize->ds0_out_h_size;    
	isp_reg_writel(isp,stDS0Data.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_OUT_SIZE);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDs1OutSize(struct isp_device *isp,ISP_WRAP_DS1_OUT_SIZE_S *stDs1OutSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stDs1OutSize);

	U_ISP_WRAP_DS1_OUT_SIZE stDS1Data;
	stDS1Data.u32 = 0;
	stDS1Data.bits.ds1_out_v_size = stDs1OutSize->ds1_out_v_size;   
	stDS1Data.bits.ds1_out_h_size = stDs1OutSize->ds1_out_h_size;    
	isp_reg_writel(isp,stDS1Data.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_OUT_SIZE);

	return 0;	
}

static int Isp_Drv_R2k_Wrap_SetDs2OutSize(struct isp_device *isp,ISP_WRAP_DS2_OUT_SIZE_S *stDs2OutSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stDs2OutSize);

	U_ISP_WRAP_DS2_OUT_SIZE stDS2Data;
	stDS2Data.u32 = 0;
	stDS2Data.bits.ds2_out_v_size = stDs2OutSize->ds2_out_v_size;   
	stDS2Data.bits.ds2_out_h_size = stDs2OutSize->ds2_out_h_size;    
	isp_reg_writel(isp,stDS2Data.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_OUT_SIZE);	
	return 0;
}
/*
*DMA
 */
static int Isp_Drv_R2k_Wrap_SetDmaMode(struct isp_device *isp,ISP_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_ISP_WRAP_DMA_ARB_MODE stArbMode;
	stArbMode.u32 = 0;
	stArbMode.bits.isp_dma_wr_arb_mode = pstDmaMode->wr_dma_arb_mode;   
	stArbMode.bits.isp_dma_rd_arb_mode = pstDmaMode->wr_dma_arb_mode;    
	isp_reg_writel(isp,stArbMode.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_ARB_MODE);

	U_ISP_WRAP_DMA_WR_WEIGHT_0 stWrWeight0;
	stWrWeight0.u32 = 0;
	stWrWeight0.bits.isp_dma_ch0_wr_weight = pstDmaMode->wr_dma_ch_weight[0];   
	stWrWeight0.bits.isp_dma_ch1_wr_weight = pstDmaMode->wr_dma_ch_weight[1];   
	stWrWeight0.bits.isp_dma_ch2_wr_weight = pstDmaMode->wr_dma_ch_weight[2];   
	stWrWeight0.bits.isp_dma_ch3_wr_weight = pstDmaMode->wr_dma_ch_weight[3];   
	isp_reg_writel(isp,stWrWeight0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_WEIGHT_0);

	U_ISP_WRAP_DMA_WR_WEIGHT_1 stWrWeight1;
	stWrWeight1.u32 = 0;
	stWrWeight1.bits.isp_dma_ch4_wr_weight = pstDmaMode->wr_dma_ch_weight[4];   
	stWrWeight1.bits.isp_dma_ch5_wr_weight = pstDmaMode->wr_dma_ch_weight[5];   
	stWrWeight1.bits.isp_dma_ch6_wr_weight = pstDmaMode->wr_dma_ch_weight[6];   
	stWrWeight1.bits.isp_dma_ch7_wr_weight = pstDmaMode->wr_dma_ch_weight[7];   
	isp_reg_writel(isp,stWrWeight1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_WEIGHT_1);

	U_ISP_WRAP_DMA_WR_WEIGHT_2 stWrWeight2;
	stWrWeight2.u32 = 0;
	stWrWeight2.bits.isp_dma_ch8_wr_weight = pstDmaMode->wr_dma_ch_weight[8];   
	stWrWeight2.bits.isp_dma_ch9_wr_weight = pstDmaMode->wr_dma_ch_weight[9];   
	stWrWeight2.bits.isp_dma_ch10_wr_weight = pstDmaMode->wr_dma_ch_weight[10];   
	stWrWeight2.bits.isp_dma_ch11_wr_weight = pstDmaMode->wr_dma_ch_weight[11];  
	isp_reg_writel(isp,stWrWeight2.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_WEIGHT_2);

	U_ISP_WRAP_DMA_WR_WEIGHT_3 stWrWeight3;
	stWrWeight3.u32 = 0;
	stWrWeight3.bits.isp_dma_ch12_wr_weight = pstDmaMode->wr_dma_ch_weight[12];   
	stWrWeight3.bits.isp_dma_ch13_wr_weight = pstDmaMode->wr_dma_ch_weight[13];   
	stWrWeight3.bits.isp_dma_ch14_wr_weight = pstDmaMode->wr_dma_ch_weight[14];   
	stWrWeight3.bits.isp_dma_ch15_wr_weight = pstDmaMode->wr_dma_ch_weight[15]; 
	isp_reg_writel(isp,stWrWeight3.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_WEIGHT_3);

	U_ISP_WRAP_DMA_RD_WEIGHT_0 stRdWeight0;
	stRdWeight0.u32 = 0;
	stRdWeight0.bits.isp_dma_ch0_rd_weight = pstDmaMode->rd_dma_ch_weight[0];   
	stRdWeight0.bits.isp_dma_ch1_rd_weight = pstDmaMode->rd_dma_ch_weight[1];   
	stRdWeight0.bits.isp_dma_ch2_rd_weight = pstDmaMode->rd_dma_ch_weight[2];   
	stRdWeight0.bits.isp_dma_ch3_rd_weight = pstDmaMode->rd_dma_ch_weight[3];   
	isp_reg_writel(isp,stRdWeight0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_WEIGHT_0);

	U_ISP_WRAP_DMA_RD_WEIGHT_1 stRdWeight1;
	stRdWeight1.u32 = 0;
	stRdWeight1.bits.isp_dma_ch4_rd_weight = pstDmaMode->rd_dma_ch_weight[4];   
	stRdWeight1.bits.isp_dma_ch5_rd_weight = pstDmaMode->rd_dma_ch_weight[5];   
	stRdWeight1.bits.isp_dma_ch6_rd_weight = pstDmaMode->rd_dma_ch_weight[6];   
	stRdWeight1.bits.isp_dma_ch7_rd_weight = pstDmaMode->rd_dma_ch_weight[7];   
	isp_reg_writel(isp,stRdWeight1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_WEIGHT_1);

	U_ISP_WRAP_DMA_RD_WEIGHT_2 stRdWeight2;
	stRdWeight2.u32 = 0;
	stRdWeight2.bits.isp_dma_ch8_rd_weight = pstDmaMode->rd_dma_ch_weight[8];   
	stRdWeight2.bits.isp_dma_ch9_rd_weight = pstDmaMode->rd_dma_ch_weight[9];   
	stRdWeight2.bits.isp_dma_ch10_rd_weight = pstDmaMode->rd_dma_ch_weight[10];   
	stRdWeight2.bits.isp_dma_ch11_rd_weight = pstDmaMode->rd_dma_ch_weight[11];  
	isp_reg_writel(isp,stRdWeight2.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_WEIGHT_2);	

	U_ISP_WRAP_DMA_RD_WEIGHT_3 stRdWeight3;
	stRdWeight3.u32 = 0;
	stRdWeight3.bits.isp_dma_ch12_rd_weight = pstDmaMode->rd_dma_ch_weight[12];   
	stRdWeight3.bits.isp_dma_ch13_rd_weight = pstDmaMode->rd_dma_ch_weight[13];   
	stRdWeight3.bits.isp_dma_ch14_rd_weight = pstDmaMode->rd_dma_ch_weight[14];   
	stRdWeight3.bits.isp_dma_ch15_rd_weight = pstDmaMode->rd_dma_ch_weight[15]; 
	isp_reg_writel(isp,stRdWeight3.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_WEIGHT_3);

	U_ISP_WRAP_DMA_WR_PRIORITY_0 stWrPriority0;
	stWrPriority0.u32 = 0;
	stWrPriority0.bits.isp_dma_ch0_wr_priority = pstDmaMode->wr_dma_ch_priority[0];   
	stWrPriority0.bits.isp_dma_ch1_wr_priority = pstDmaMode->wr_dma_ch_priority[1];   
	stWrPriority0.bits.isp_dma_ch2_wr_priority = pstDmaMode->wr_dma_ch_priority[2];   
	stWrPriority0.bits.isp_dma_ch3_wr_priority = pstDmaMode->wr_dma_ch_priority[3]; 
	stWrPriority0.bits.isp_dma_ch4_wr_priority = pstDmaMode->wr_dma_ch_priority[4];   
	stWrPriority0.bits.isp_dma_ch5_wr_priority = pstDmaMode->wr_dma_ch_priority[5];   
	stWrPriority0.bits.isp_dma_ch6_wr_priority = pstDmaMode->wr_dma_ch_priority[6];   
	stWrPriority0.bits.isp_dma_ch7_wr_priority = pstDmaMode->wr_dma_ch_priority[7]; 
	isp_reg_writel(isp,stWrPriority0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_PRIORITY_0);

	U_ISP_WRAP_DMA_WR_PRIORITY_1 stWrPriority1;
	stWrPriority1.u32 = 0;
	stWrPriority1.bits.isp_dma_ch8_wr_priority = pstDmaMode->wr_dma_ch_priority[8];   
	stWrPriority1.bits.isp_dma_ch9_wr_priority = pstDmaMode->wr_dma_ch_priority[9];   
	stWrPriority1.bits.isp_dma_ch10_wr_priority = pstDmaMode->wr_dma_ch_priority[10];   
	stWrPriority1.bits.isp_dma_ch11_wr_priority = pstDmaMode->wr_dma_ch_priority[11]; 
	stWrPriority1.bits.isp_dma_ch12_wr_priority = pstDmaMode->wr_dma_ch_priority[12];   
	stWrPriority1.bits.isp_dma_ch13_wr_priority = pstDmaMode->wr_dma_ch_priority[13];   
	stWrPriority1.bits.isp_dma_ch14_wr_priority = pstDmaMode->wr_dma_ch_priority[14];   
	stWrPriority1.bits.isp_dma_ch15_wr_priority = pstDmaMode->wr_dma_ch_priority[15]; 
	isp_reg_writel(isp,stWrPriority1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_PRIORITY_1);

	U_ISP_WRAP_DMA_RD_PRIORITY_0 stRdPriority0;
	stRdPriority0.u32 = 0;
	stRdPriority0.bits.isp_dma_ch0_rd_priority = pstDmaMode->rd_dma_ch_priority[0];   
	stRdPriority0.bits.isp_dma_ch1_rd_priority = pstDmaMode->rd_dma_ch_priority[1];   
	stRdPriority0.bits.isp_dma_ch2_rd_priority = pstDmaMode->rd_dma_ch_priority[2];   
	stRdPriority0.bits.isp_dma_ch3_rd_priority = pstDmaMode->rd_dma_ch_priority[3]; 
	stRdPriority0.bits.isp_dma_ch4_rd_priority = pstDmaMode->rd_dma_ch_priority[4];   
	stRdPriority0.bits.isp_dma_ch5_rd_priority = pstDmaMode->rd_dma_ch_priority[5];   
	stRdPriority0.bits.isp_dma_ch6_rd_priority = pstDmaMode->rd_dma_ch_priority[6];   
	stRdPriority0.bits.isp_dma_ch7_rd_priority = pstDmaMode->rd_dma_ch_priority[7]; 
	isp_reg_writel(isp,stRdPriority0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_PRIORITY_0);

	U_ISP_WRAP_DMA_RD_PRIORITY_1 stRdPriority1;
	stRdPriority1.u32 = 0;
	stRdPriority1.bits.isp_dma_ch8_rd_priority = pstDmaMode->rd_dma_ch_priority[8];   
	stRdPriority1.bits.isp_dma_ch9_rd_priority = pstDmaMode->rd_dma_ch_priority[9];   
	stRdPriority1.bits.isp_dma_ch10_rd_priority = pstDmaMode->rd_dma_ch_priority[10];   
	stRdPriority1.bits.isp_dma_ch11_rd_priority = pstDmaMode->rd_dma_ch_priority[11]; 
	stRdPriority1.bits.isp_dma_ch12_rd_priority = pstDmaMode->rd_dma_ch_priority[12];   
	stRdPriority1.bits.isp_dma_ch13_rd_priority = pstDmaMode->rd_dma_ch_priority[13];   
	stRdPriority1.bits.isp_dma_ch14_rd_priority = pstDmaMode->rd_dma_ch_priority[14];   
	stRdPriority1.bits.isp_dma_ch15_rd_priority = pstDmaMode->rd_dma_ch_priority[15]; 
	isp_reg_writel(isp,stRdPriority1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_PRIORITY_1);

	U_ISP_DMA_WR_CH_ID_0 stWrChId0;
	stWrChId0.u32 = 0;
	stWrChId0.bits.isp_dma_wr_ch0_id = pstDmaMode->wr_dma_ch_id[0];   
	stWrChId0.bits.isp_dma_wr_ch1_id = pstDmaMode->wr_dma_ch_id[1];   
	stWrChId0.bits.isp_dma_wr_ch2_id = pstDmaMode->wr_dma_ch_id[2];   
	stWrChId0.bits.isp_dma_wr_ch3_id = pstDmaMode->wr_dma_ch_id[3]; 
	stWrChId0.bits.isp_dma_wr_ch4_id = pstDmaMode->wr_dma_ch_id[4];   
	stWrChId0.bits.isp_dma_wr_ch5_id = pstDmaMode->wr_dma_ch_id[5];   
	stWrChId0.bits.isp_dma_wr_ch6_id = pstDmaMode->wr_dma_ch_id[6];   
	stWrChId0.bits.isp_dma_wr_ch7_id = pstDmaMode->wr_dma_ch_id[7]; 
	isp_reg_writel(isp,stWrChId0.u32,ISP_IOMEM_R2K_WRAP,ISP_DMA_WR_CH_ID_0);

	U_ISP_DMA_WR_CH_ID_1 stWrChId1;
	stWrChId1.u32 = 0;
	stWrChId1.bits.isp_dma_wr_ch8_id = pstDmaMode->wr_dma_ch_id[8];   
	
	stWrChId1.bits.isp_dma_wr_ch9_id = pstDmaMode->wr_dma_ch_id[9];   
	stWrChId1.bits.isp_dma_wr_ch10_id = pstDmaMode->wr_dma_ch_id[10];   
	stWrChId1.bits.isp_dma_wr_ch11_id = pstDmaMode->wr_dma_ch_id[11]; 
	stWrChId1.bits.isp_dma_wr_ch12_id = pstDmaMode->wr_dma_ch_id[12];   
	stWrChId1.bits.isp_dma_wr_ch13_id = pstDmaMode->wr_dma_ch_id[13];   
	stWrChId1.bits.isp_dma_wr_ch14_id = pstDmaMode->wr_dma_ch_id[14];   
	stWrChId1.bits.isp_dma_wr_ch15_id = pstDmaMode->wr_dma_ch_id[15]; 
	isp_reg_writel(isp,stWrChId1.u32,ISP_IOMEM_R2K_WRAP,ISP_DMA_WR_CH_ID_1);

	U_ISP_DMA_RD_CH_ID_0 stRdChId0;
	stRdChId0.u32 = 0;
	stRdChId0.bits.isp_dma_rd_ch0_id = pstDmaMode->rd_dma_ch_id[0];   
	stRdChId0.bits.isp_dma_rd_ch1_id = pstDmaMode->rd_dma_ch_id[1];   
	stRdChId0.bits.isp_dma_rd_ch2_id = pstDmaMode->rd_dma_ch_id[2];   
	stRdChId0.bits.isp_dma_rd_ch3_id = pstDmaMode->rd_dma_ch_id[3]; 
	stRdChId0.bits.isp_dma_rd_ch4_id = pstDmaMode->rd_dma_ch_id[4];   
	stRdChId0.bits.isp_dma_rd_ch5_id = pstDmaMode->rd_dma_ch_id[5];   
	stRdChId0.bits.isp_dma_rd_ch6_id = pstDmaMode->rd_dma_ch_id[6];   
	stRdChId0.bits.isp_dma_rd_ch7_id = pstDmaMode->rd_dma_ch_id[7]; 
	isp_reg_writel(isp,stRdChId0.u32,ISP_IOMEM_R2K_WRAP,ISP_DMA_RD_CH_ID_0);

	U_ISP_DMA_RD_CH_ID_1 stRdChId1;
	stRdChId1.u32 = 0;
	stRdChId1.bits.isp_dma_rd_ch8_id = pstDmaMode->rd_dma_ch_id[8];   
	stRdChId1.bits.isp_dma_rd_ch9_id = pstDmaMode->rd_dma_ch_id[9];   
	stRdChId1.bits.isp_dma_rd_ch10_id = pstDmaMode->rd_dma_ch_id[10];   
	stRdChId1.bits.isp_dma_rd_ch11_id = pstDmaMode->rd_dma_ch_id[11]; 
	stRdChId1.bits.isp_dma_rd_ch12_id = pstDmaMode->rd_dma_ch_id[12];   
	stRdChId1.bits.isp_dma_rd_ch13_id = pstDmaMode->rd_dma_ch_id[13];   
	stRdChId1.bits.isp_dma_rd_ch14_id = pstDmaMode->rd_dma_ch_id[14];   
	stRdChId1.bits.isp_dma_rd_ch15_id = pstDmaMode->rd_dma_ch_id[15]; 
	isp_reg_writel(isp,stRdChId1.u32,ISP_IOMEM_R2K_WRAP,ISP_DMA_RD_CH_ID_1);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDmaCfgMode(struct isp_device *isp,ISP_WRAP_DMA_CFG_S *pstDmaCfg)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaCfg);

	U_ISP_WRAP_DMA_CH0_CFG stDmaCfg0;
	stDmaCfg0.u32 = 0;
	stDmaCfg0.bits.ch0_wr_outst = pstDmaCfg->stDmaChcfg[0].wr_ch_outst;
	stDmaCfg0.bits.ch0_rd_outst = pstDmaCfg->stDmaChcfg[0].rd_ch_outst;
	stDmaCfg0.bits.ch0_wr_burstl = pstDmaCfg->stDmaChcfg[0].wr_ch_burstl;
	stDmaCfg0.bits.ch0_rd_burstl = pstDmaCfg->stDmaChcfg[0].rd_ch_burstl;
	stDmaCfg0.bits.ch0_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[0].y_uv_noncon_en;
	stDmaCfg0.bits.ch0_y_uv_swap_en = pstDmaCfg->stDmaChcfg[0].y_uv_swap_en;
	stDmaCfg0.bits.ch0_wr_int_line_num = pstDmaCfg->stDmaChcfg[0].wr_int_line_num;
	stDmaCfg0.bits.ch0_wr_err_dec_en = pstDmaCfg->stDmaChcfg[0].wr_err_dec_en;
	stDmaCfg0.bits.ch0_rd_err_dec_en = pstDmaCfg->stDmaChcfg[0].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH0_CFG);

	U_ISP_WRAP_DMA_CH1_CFG stDmaCfg1;
	stDmaCfg1.u32 = 0;
	stDmaCfg1.bits.ch1_wr_outst = pstDmaCfg->stDmaChcfg[1].wr_ch_outst;
	stDmaCfg1.bits.ch1_rd_outst = pstDmaCfg->stDmaChcfg[1].rd_ch_outst;
	stDmaCfg1.bits.ch1_wr_burstl = pstDmaCfg->stDmaChcfg[1].wr_ch_burstl;
	stDmaCfg1.bits.ch1_rd_burstl = pstDmaCfg->stDmaChcfg[1].rd_ch_burstl;
	stDmaCfg1.bits.ch1_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[1].y_uv_noncon_en;
	stDmaCfg1.bits.ch1_y_uv_swap_en = pstDmaCfg->stDmaChcfg[1].y_uv_swap_en;
	stDmaCfg1.bits.ch1_wr_int_line_num = pstDmaCfg->stDmaChcfg[1].wr_int_line_num;
	stDmaCfg1.bits.ch1_wr_err_dec_en = pstDmaCfg->stDmaChcfg[1].wr_err_dec_en;
	stDmaCfg1.bits.ch1_rd_err_dec_en = pstDmaCfg->stDmaChcfg[1].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH1_CFG);

	U_ISP_WRAP_DMA_CH2_CFG stDmaCfg2;
	stDmaCfg2.u32 = 0;
	stDmaCfg2.bits.ch2_wr_outst = pstDmaCfg->stDmaChcfg[2].wr_ch_outst;
	stDmaCfg2.bits.ch2_rd_outst = pstDmaCfg->stDmaChcfg[2].rd_ch_outst;
	stDmaCfg2.bits.ch2_wr_burstl = pstDmaCfg->stDmaChcfg[2].wr_ch_burstl;
	stDmaCfg2.bits.ch2_rd_burstl = pstDmaCfg->stDmaChcfg[2].rd_ch_burstl;
	stDmaCfg2.bits.ch2_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[2].y_uv_noncon_en;
	stDmaCfg2.bits.ch2_y_uv_swap_en = pstDmaCfg->stDmaChcfg[2].y_uv_swap_en;
	stDmaCfg2.bits.ch2_wr_int_line_num = pstDmaCfg->stDmaChcfg[2].wr_int_line_num;
	stDmaCfg2.bits.ch2_wr_err_dec_en = pstDmaCfg->stDmaChcfg[2].wr_err_dec_en;
	stDmaCfg2.bits.ch2_rd_err_dec_en = pstDmaCfg->stDmaChcfg[2].rd_err_dec_en;
	stDmaCfg2.bits.ch2_wr_outst_en = pstDmaCfg->stDmaChcfg[2].wr_outst_en;
	stDmaCfg2.bits.ch2_rd_outst_en = pstDmaCfg->stDmaChcfg[2].rd_outst_en;
	//stDmaCfg2.u32 = 0xc0100088;
	isp_reg_writel(isp,stDmaCfg2.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH2_CFG);

	U_ISP_WRAP_DMA_CH3_CFG stDmaCfg3;
	stDmaCfg3.u32 = 0;
	stDmaCfg3.bits.ch3_wr_outst = pstDmaCfg->stDmaChcfg[3].wr_ch_outst;
	stDmaCfg3.bits.ch3_rd_outst = pstDmaCfg->stDmaChcfg[3].rd_ch_outst;
	stDmaCfg3.bits.ch3_wr_burstl = pstDmaCfg->stDmaChcfg[3].wr_ch_burstl;
	stDmaCfg3.bits.ch3_rd_burstl = pstDmaCfg->stDmaChcfg[3].rd_ch_burstl;
	stDmaCfg3.bits.ch3_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[3].y_uv_noncon_en;
	stDmaCfg3.bits.ch3_y_uv_swap_en = pstDmaCfg->stDmaChcfg[3].y_uv_swap_en;
	stDmaCfg3.bits.ch3_wr_int_line_num = pstDmaCfg->stDmaChcfg[3].wr_int_line_num;
	stDmaCfg3.bits.ch3_wr_err_dec_en = pstDmaCfg->stDmaChcfg[3].wr_err_dec_en;
	stDmaCfg3.bits.ch3_rd_err_dec_en = pstDmaCfg->stDmaChcfg[3].rd_err_dec_en;
	stDmaCfg3.bits.ch3_wr_outst_en = pstDmaCfg->stDmaChcfg[3].wr_outst_en;
	stDmaCfg3.bits.ch3_rd_outst_en = pstDmaCfg->stDmaChcfg[3].rd_outst_en;
	//stDmaCfg3.u32 = 0xc0100088;
	isp_reg_writel(isp,stDmaCfg3.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH3_CFG);

	U_ISP_WRAP_DMA_CH4_CFG stDmaCfg4;
	stDmaCfg4.u32 = 0;
	stDmaCfg4.bits.ch4_wr_outst = pstDmaCfg->stDmaChcfg[4].wr_ch_outst;
	stDmaCfg4.bits.ch4_rd_outst = pstDmaCfg->stDmaChcfg[4].rd_ch_outst;
	stDmaCfg4.bits.ch4_wr_burstl = pstDmaCfg->stDmaChcfg[4].wr_ch_burstl;
	stDmaCfg4.bits.ch4_rd_burstl = pstDmaCfg->stDmaChcfg[4].rd_ch_burstl;
	stDmaCfg4.bits.ch4_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[4].y_uv_noncon_en;
	stDmaCfg4.bits.ch4_y_uv_swap_en = pstDmaCfg->stDmaChcfg[4].y_uv_swap_en;
	stDmaCfg4.bits.ch4_wr_int_line_num = pstDmaCfg->stDmaChcfg[4].wr_int_line_num;
	stDmaCfg4.bits.ch4_wr_err_dec_en = pstDmaCfg->stDmaChcfg[4].wr_err_dec_en;
	stDmaCfg4.bits.ch4_rd_err_dec_en = pstDmaCfg->stDmaChcfg[4].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg4.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH4_CFG);

	U_ISP_WRAP_DMA_CH5_CFG stDmaCfg5;
	stDmaCfg5.u32 = 0;
	stDmaCfg5.bits.ch5_wr_outst = pstDmaCfg->stDmaChcfg[5].wr_ch_outst;
	stDmaCfg5.bits.ch5_rd_outst = pstDmaCfg->stDmaChcfg[5].rd_ch_outst;
	stDmaCfg5.bits.ch5_wr_burstl = pstDmaCfg->stDmaChcfg[5].wr_ch_burstl;
	stDmaCfg5.bits.ch5_rd_burstl = pstDmaCfg->stDmaChcfg[5].rd_ch_burstl;
	stDmaCfg5.bits.ch5_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[5].y_uv_noncon_en;
	stDmaCfg5.bits.ch5_y_uv_swap_en = pstDmaCfg->stDmaChcfg[5].y_uv_swap_en;
	stDmaCfg5.bits.ch5_wr_int_line_num = pstDmaCfg->stDmaChcfg[5].wr_int_line_num;
	stDmaCfg5.bits.ch5_wr_err_dec_en = pstDmaCfg->stDmaChcfg[5].wr_err_dec_en;
	stDmaCfg5.bits.ch5_rd_err_dec_en = pstDmaCfg->stDmaChcfg[5].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg5.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH5_CFG);

	U_ISP_WRAP_DMA_CH6_CFG stDmaCfg6;
	stDmaCfg6.u32 = 0;
	stDmaCfg6.bits.ch6_wr_outst = pstDmaCfg->stDmaChcfg[6].wr_ch_outst;
	stDmaCfg6.bits.ch6_rd_outst = pstDmaCfg->stDmaChcfg[6].rd_ch_outst;
	stDmaCfg6.bits.ch6_wr_burstl = pstDmaCfg->stDmaChcfg[6].wr_ch_burstl;
	stDmaCfg6.bits.ch6_rd_burstl = pstDmaCfg->stDmaChcfg[6].rd_ch_burstl;
	stDmaCfg6.bits.ch6_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[6].y_uv_noncon_en;
	stDmaCfg6.bits.ch6_y_uv_swap_en = pstDmaCfg->stDmaChcfg[6].y_uv_swap_en;
	stDmaCfg6.bits.ch6_wr_int_line_num = pstDmaCfg->stDmaChcfg[6].wr_int_line_num;
	stDmaCfg6.bits.ch6_wr_err_dec_en = pstDmaCfg->stDmaChcfg[6].wr_err_dec_en;
	stDmaCfg6.bits.ch6_rd_err_dec_en = pstDmaCfg->stDmaChcfg[6].rd_err_dec_en;
	stDmaCfg6.bits.ch6_wr_outst_en = pstDmaCfg->stDmaChcfg[6].wr_outst_en;
	stDmaCfg6.bits.ch6_rd_outst_en = pstDmaCfg->stDmaChcfg[6].rd_outst_en;
	isp_reg_writel(isp,stDmaCfg6.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH6_CFG);

	U_ISP_WRAP_DMA_CH7_CFG stDmaCfg7;
	stDmaCfg7.u32 = 0;
	stDmaCfg7.bits.ch7_wr_outst = pstDmaCfg->stDmaChcfg[7].wr_ch_outst;
	stDmaCfg7.bits.ch7_rd_outst = pstDmaCfg->stDmaChcfg[7].rd_ch_outst;
	stDmaCfg7.bits.ch7_wr_burstl = pstDmaCfg->stDmaChcfg[7].wr_ch_burstl;
	stDmaCfg7.bits.ch7_rd_burstl = pstDmaCfg->stDmaChcfg[7].rd_ch_burstl;
	stDmaCfg7.bits.ch7_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[7].y_uv_noncon_en;
	stDmaCfg7.bits.ch7_y_uv_swap_en = pstDmaCfg->stDmaChcfg[7].y_uv_swap_en;
	stDmaCfg7.bits.ch7_wr_int_line_num = pstDmaCfg->stDmaChcfg[7].wr_int_line_num;
	stDmaCfg7.bits.ch7_wr_err_dec_en = pstDmaCfg->stDmaChcfg[7].wr_err_dec_en;
	stDmaCfg7.bits.ch7_rd_err_dec_en = pstDmaCfg->stDmaChcfg[7].rd_err_dec_en;
	stDmaCfg7.bits.ch7_wr_outst_en = pstDmaCfg->stDmaChcfg[7].wr_outst_en;
	stDmaCfg7.bits.ch7_rd_outst_en = pstDmaCfg->stDmaChcfg[7].rd_outst_en;
	isp_reg_writel(isp,stDmaCfg7.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH7_CFG);

	U_ISP_WRAP_DMA_CH8_CFG stDmaCfg8;
	stDmaCfg8.u32 = 0;
	stDmaCfg8.bits.ch8_wr_outst = pstDmaCfg->stDmaChcfg[8].wr_ch_outst;
	stDmaCfg8.bits.ch8_rd_outst = pstDmaCfg->stDmaChcfg[8].rd_ch_outst;
	stDmaCfg8.bits.ch8_wr_burstl = pstDmaCfg->stDmaChcfg[8].wr_ch_burstl;
	stDmaCfg8.bits.ch8_rd_burstl = pstDmaCfg->stDmaChcfg[8].rd_ch_burstl;
	stDmaCfg8.bits.ch8_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[8].y_uv_noncon_en;
	stDmaCfg8.bits.ch8_y_uv_swap_en = pstDmaCfg->stDmaChcfg[8].y_uv_swap_en;
	stDmaCfg8.bits.ch8_wr_int_line_num = pstDmaCfg->stDmaChcfg[8].wr_int_line_num;
	stDmaCfg8.bits.ch8_wr_err_dec_en = pstDmaCfg->stDmaChcfg[8].wr_err_dec_en;
	stDmaCfg8.bits.ch8_rd_err_dec_en = pstDmaCfg->stDmaChcfg[8].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg8.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH8_CFG);

	U_ISP_WRAP_DMA_CH9_CFG stDmaCfg9;
	stDmaCfg9.u32 = 0;
	stDmaCfg9.bits.ch9_wr_outst = pstDmaCfg->stDmaChcfg[9].wr_ch_outst;
	stDmaCfg9.bits.ch9_rd_outst = pstDmaCfg->stDmaChcfg[9].rd_ch_outst;
	stDmaCfg9.bits.ch9_wr_burstl = pstDmaCfg->stDmaChcfg[9].wr_ch_burstl;
	stDmaCfg9.bits.ch9_rd_burstl = pstDmaCfg->stDmaChcfg[9].rd_ch_burstl;
	stDmaCfg9.bits.ch9_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[9].y_uv_noncon_en;
	stDmaCfg9.bits.ch9_y_uv_swap_en = pstDmaCfg->stDmaChcfg[9].y_uv_swap_en;
	stDmaCfg9.bits.ch9_wr_int_line_num = pstDmaCfg->stDmaChcfg[9].wr_int_line_num;
	stDmaCfg9.bits.ch9_wr_err_dec_en = pstDmaCfg->stDmaChcfg[9].wr_err_dec_en;
	stDmaCfg9.bits.ch9_rd_err_dec_en = pstDmaCfg->stDmaChcfg[9].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg9.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH9_CFG);

	U_ISP_WRAP_DMA_CH10_CFG stDmaCfg10;
	stDmaCfg10.u32 = 0;
	stDmaCfg10.bits.ch10_wr_outst = pstDmaCfg->stDmaChcfg[10].wr_ch_outst;
	stDmaCfg10.bits.ch10_rd_outst = pstDmaCfg->stDmaChcfg[10].rd_ch_outst;
	stDmaCfg10.bits.ch10_wr_burstl = pstDmaCfg->stDmaChcfg[10].wr_ch_burstl;
	stDmaCfg10.bits.ch10_rd_burstl = pstDmaCfg->stDmaChcfg[10].rd_ch_burstl;
	stDmaCfg10.bits.ch10_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[10].y_uv_noncon_en;
	stDmaCfg10.bits.ch10_y_uv_swap_en = pstDmaCfg->stDmaChcfg[10].y_uv_swap_en;
	stDmaCfg10.bits.ch10_wr_int_line_num = pstDmaCfg->stDmaChcfg[10].wr_int_line_num;
	stDmaCfg10.bits.ch10_wr_err_dec_en = pstDmaCfg->stDmaChcfg[10].wr_err_dec_en;
	stDmaCfg10.bits.ch10_rd_err_dec_en = pstDmaCfg->stDmaChcfg[10].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg10.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH10_CFG);

	U_ISP_WRAP_DMA_CH11_CFG stDmaCfg11;
	stDmaCfg11.u32 = 0;
	stDmaCfg11.bits.ch11_wr_outst = pstDmaCfg->stDmaChcfg[11].wr_ch_outst;
	stDmaCfg11.bits.ch11_rd_outst = pstDmaCfg->stDmaChcfg[11].rd_ch_outst;
	stDmaCfg11.bits.ch11_wr_burstl = pstDmaCfg->stDmaChcfg[11].wr_ch_burstl;
	stDmaCfg11.bits.ch11_rd_burstl = pstDmaCfg->stDmaChcfg[11].rd_ch_burstl;
	stDmaCfg11.bits.ch11_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[11].y_uv_noncon_en;
	stDmaCfg11.bits.ch11_y_uv_swap_en = pstDmaCfg->stDmaChcfg[11].y_uv_swap_en;
	stDmaCfg11.bits.ch11_wr_int_line_num = pstDmaCfg->stDmaChcfg[11].wr_int_line_num;
	stDmaCfg11.bits.ch11_wr_err_dec_en = pstDmaCfg->stDmaChcfg[11].wr_err_dec_en;
	stDmaCfg11.bits.ch11_rd_err_dec_en = pstDmaCfg->stDmaChcfg[11].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg11.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH11_CFG);

	U_ISP_WRAP_DMA_CH12_CFG stDmaCfg12;
	stDmaCfg12.u32 = 0;
	stDmaCfg12.bits.ch12_wr_outst = pstDmaCfg->stDmaChcfg[12].wr_ch_outst;
	stDmaCfg12.bits.ch12_rd_outst = pstDmaCfg->stDmaChcfg[12].rd_ch_outst;
	stDmaCfg12.bits.ch12_wr_burstl = pstDmaCfg->stDmaChcfg[12].wr_ch_burstl;
	stDmaCfg12.bits.ch12_rd_burstl = pstDmaCfg->stDmaChcfg[12].rd_ch_burstl;
	stDmaCfg12.bits.ch12_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[12].y_uv_noncon_en;
	stDmaCfg12.bits.ch12_y_uv_swap_en = pstDmaCfg->stDmaChcfg[12].y_uv_swap_en;
	stDmaCfg12.bits.ch12_wr_int_line_num = pstDmaCfg->stDmaChcfg[12].wr_int_line_num;
	stDmaCfg12.bits.ch12_wr_err_dec_en = pstDmaCfg->stDmaChcfg[12].wr_err_dec_en;
	stDmaCfg12.bits.ch12_rd_err_dec_en = pstDmaCfg->stDmaChcfg[12].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg12.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH12_CFG);

	U_ISP_WRAP_DMA_CH13_CFG stDmaCfg13;
	stDmaCfg13.u32 = 0;
	stDmaCfg13.bits.ch13_wr_outst = pstDmaCfg->stDmaChcfg[13].wr_ch_outst;
	stDmaCfg13.bits.ch13_rd_outst = pstDmaCfg->stDmaChcfg[13].rd_ch_outst;
	stDmaCfg13.bits.ch13_wr_burstl = pstDmaCfg->stDmaChcfg[13].wr_ch_burstl;
	stDmaCfg13.bits.ch13_rd_burstl = pstDmaCfg->stDmaChcfg[13].rd_ch_burstl;
	stDmaCfg13.bits.ch13_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[13].y_uv_noncon_en;
	stDmaCfg13.bits.ch13_y_uv_swap_en = pstDmaCfg->stDmaChcfg[13].y_uv_swap_en;
	stDmaCfg13.bits.ch13_wr_int_line_num = pstDmaCfg->stDmaChcfg[13].wr_int_line_num;
	stDmaCfg13.bits.ch13_wr_err_dec_en = pstDmaCfg->stDmaChcfg[13].wr_err_dec_en;
	stDmaCfg13.bits.ch13_rd_err_dec_en = pstDmaCfg->stDmaChcfg[13].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg13.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH13_CFG);

	U_ISP_WRAP_DMA_CH14_CFG stDmaCfg14;
	stDmaCfg14.u32 = 0;
	stDmaCfg14.bits.ch14_wr_outst = pstDmaCfg->stDmaChcfg[14].wr_ch_outst;
	stDmaCfg14.bits.ch14_rd_outst = pstDmaCfg->stDmaChcfg[14].rd_ch_outst;
	stDmaCfg14.bits.ch14_wr_burstl = pstDmaCfg->stDmaChcfg[14].wr_ch_burstl;
	stDmaCfg14.bits.ch14_rd_burstl = pstDmaCfg->stDmaChcfg[14].rd_ch_burstl;
	stDmaCfg14.bits.ch14_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[14].y_uv_noncon_en;
	stDmaCfg14.bits.ch14_y_uv_swap_en = pstDmaCfg->stDmaChcfg[14].y_uv_swap_en;
	stDmaCfg14.bits.ch14_wr_int_line_num = pstDmaCfg->stDmaChcfg[14].wr_int_line_num;
	stDmaCfg14.bits.ch14_wr_err_dec_en = pstDmaCfg->stDmaChcfg[14].wr_err_dec_en;
	stDmaCfg14.bits.ch14_rd_err_dec_en = pstDmaCfg->stDmaChcfg[14].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg14.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH14_CFG);

	U_ISP_WRAP_DMA_CH15_CFG stDmaCfg15;	
	stDmaCfg15.u32 = 0;
	stDmaCfg15.bits.ch15_wr_outst = pstDmaCfg->stDmaChcfg[15].wr_ch_outst;
	stDmaCfg15.bits.ch15_rd_outst = pstDmaCfg->stDmaChcfg[15].rd_ch_outst;
	stDmaCfg15.bits.ch15_wr_burstl = pstDmaCfg->stDmaChcfg[15].wr_ch_burstl;
	stDmaCfg15.bits.ch15_rd_burstl = pstDmaCfg->stDmaChcfg[15].rd_ch_burstl;
	stDmaCfg15.bits.ch15_y_uv_noncon_en = pstDmaCfg->stDmaChcfg[15].y_uv_noncon_en;
	stDmaCfg15.bits.ch15_y_uv_swap_en = pstDmaCfg->stDmaChcfg[15].y_uv_swap_en;
	stDmaCfg15.bits.ch15_wr_int_line_num = pstDmaCfg->stDmaChcfg[15].wr_int_line_num;
	stDmaCfg15.bits.ch15_wr_err_dec_en = pstDmaCfg->stDmaChcfg[15].wr_err_dec_en;
	stDmaCfg15.bits.ch15_rd_err_dec_en = pstDmaCfg->stDmaChcfg[15].rd_err_dec_en;
	isp_reg_writel(isp,stDmaCfg15.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH15_CFG);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDmaErrDecCfg(struct isp_device *isp,ISP_WRAP_DMA_ERR_DEC_CFG_S *pstDmaErrDec)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaErrDec);

	U_ISP_WRAP_DMA_CH0_ERR_DEC_CFG stDmaCfg0;	
	stDmaCfg0.u32 = 0;
	stDmaCfg0.bits.ch0_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[0].wr_err_dec_unit;
	stDmaCfg0.bits.ch0_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[0].rd_err_dec_unit;
	stDmaCfg0.bits.ch0_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[0].wr_err_gen_thr;
	stDmaCfg0.bits.ch0_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[0].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH0_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH1_ERR_DEC_CFG stDmaCfg1;
	stDmaCfg1.u32 = 0;
	stDmaCfg1.bits.ch1_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[1].wr_err_dec_unit;
	stDmaCfg1.bits.ch1_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[1].rd_err_dec_unit;
	stDmaCfg1.bits.ch1_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[1].wr_err_gen_thr;
	stDmaCfg1.bits.ch1_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[1].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH1_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH2_ERR_DEC_CFG stDmaCfg2;
	stDmaCfg2.u32 = 0;
	stDmaCfg2.bits.ch2_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[2].wr_err_dec_unit;
	stDmaCfg2.bits.ch2_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[2].rd_err_dec_unit;
	stDmaCfg2.bits.ch2_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[2].wr_err_gen_thr;
	stDmaCfg2.bits.ch2_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[2].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg2.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH2_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH3_ERR_DEC_CFG stDmaCfg3;
	stDmaCfg3.u32 = 0;
	stDmaCfg3.bits.ch3_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[3].wr_err_dec_unit;
	stDmaCfg3.bits.ch3_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[3].rd_err_dec_unit;
	stDmaCfg3.bits.ch3_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[3].wr_err_gen_thr;
	stDmaCfg3.bits.ch3_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[3].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg3.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH3_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH4_ERR_DEC_CFG stDmaCfg4;
	stDmaCfg4.u32 = 0;
	stDmaCfg4.bits.ch4_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[4].wr_err_dec_unit;
	stDmaCfg4.bits.ch4_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[4].rd_err_dec_unit;
	stDmaCfg4.bits.ch4_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[4].wr_err_gen_thr;
	stDmaCfg4.bits.ch4_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[4].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg4.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH4_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH5_ERR_DEC_CFG stDmaCfg5;
	stDmaCfg5.u32 = 0;
	stDmaCfg5.bits.ch5_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[5].wr_err_dec_unit;
	stDmaCfg5.bits.ch5_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[5].rd_err_dec_unit;
	stDmaCfg5.bits.ch5_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[5].wr_err_gen_thr;
	stDmaCfg5.bits.ch5_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[5].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg5.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH5_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH6_ERR_DEC_CFG stDmaCfg6;
	stDmaCfg6.u32 = 0;
	stDmaCfg6.bits.ch6_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[6].wr_err_dec_unit;
	stDmaCfg6.bits.ch6_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[6].rd_err_dec_unit;
	stDmaCfg6.bits.ch6_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[6].wr_err_gen_thr;
	stDmaCfg6.bits.ch6_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[6].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg6.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH6_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH7_ERR_DEC_CFG stDmaCfg7;
	stDmaCfg7.u32 = 0;
	stDmaCfg7.bits.ch7_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[7].wr_err_dec_unit;
	stDmaCfg7.bits.ch7_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[7].rd_err_dec_unit;
	stDmaCfg7.bits.ch7_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[7].wr_err_gen_thr;
	stDmaCfg7.bits.ch7_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[7].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg7.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH7_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH8_ERR_DEC_CFG stDmaCfg8;
	stDmaCfg8.u32 = 0;
	stDmaCfg8.bits.ch8_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[8].wr_err_dec_unit;
	stDmaCfg8.bits.ch8_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[8].rd_err_dec_unit;
	stDmaCfg8.bits.ch8_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[8].wr_err_gen_thr;
	stDmaCfg8.bits.ch8_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[8].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg8.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH8_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH9_ERR_DEC_CFG stDmaCfg9;
	stDmaCfg9.u32 = 0;
	stDmaCfg9.bits.ch9_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[9].wr_err_dec_unit;
	stDmaCfg9.bits.ch9_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[9].rd_err_dec_unit;
	stDmaCfg9.bits.ch9_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[9].wr_err_gen_thr;
	stDmaCfg9.bits.ch9_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[9].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg9.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH9_ERR_DEC_CFG);
	
	U_ISP_WRAP_DMA_CH10_ERR_DEC_CFG stDmaCfg10;	
	stDmaCfg10.u32 = 0;
	stDmaCfg10.bits.ch10_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[10].wr_err_dec_unit;
	stDmaCfg10.bits.ch10_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[10].rd_err_dec_unit;
	stDmaCfg10.bits.ch10_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[10].wr_err_gen_thr;
	stDmaCfg10.bits.ch10_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[10].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg10.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH10_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH11_ERR_DEC_CFG stDmaCfg11;
	stDmaCfg11.u32 = 0;
	stDmaCfg11.bits.ch11_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[11].wr_err_dec_unit;
	stDmaCfg11.bits.ch11_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[11].rd_err_dec_unit;
	stDmaCfg11.bits.ch11_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[11].wr_err_gen_thr;
	stDmaCfg11.bits.ch11_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[11].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg11.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH11_ERR_DEC_CFG);
	
	U_ISP_WRAP_DMA_CH12_ERR_DEC_CFG stDmaCfg12;
	stDmaCfg12.u32 = 0;
	stDmaCfg12.bits.ch12_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[12].wr_err_dec_unit;
	stDmaCfg12.bits.ch12_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[12].rd_err_dec_unit;
	stDmaCfg12.bits.ch12_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[12].wr_err_gen_thr;
	stDmaCfg12.bits.ch12_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[12].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg12.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH12_ERR_DEC_CFG);	

	U_ISP_WRAP_DMA_CH13_ERR_DEC_CFG stDmaCfg13;
	stDmaCfg13.u32 = 0;
	stDmaCfg13.bits.ch13_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[13].wr_err_dec_unit;
	stDmaCfg13.bits.ch13_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[13].rd_err_dec_unit;
	stDmaCfg13.bits.ch13_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[13].wr_err_gen_thr;
	stDmaCfg13.bits.ch13_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[13].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg13.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH13_ERR_DEC_CFG);

	U_ISP_WRAP_DMA_CH14_ERR_DEC_CFG stDmaCfg14;
	stDmaCfg14.u32 = 0;
	stDmaCfg14.bits.ch14_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[14].wr_err_dec_unit;
	stDmaCfg14.bits.ch14_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[14].rd_err_dec_unit;
	stDmaCfg14.bits.ch14_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[14].wr_err_gen_thr;
	stDmaCfg14.bits.ch14_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[14].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg14.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH14_ERR_DEC_CFG);	

	U_ISP_WRAP_DMA_CH15_ERR_DEC_CFG stDmaCfg15;
	stDmaCfg15.u32 = 0;
	stDmaCfg15.bits.ch15_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[15].wr_err_dec_unit;
	stDmaCfg15.bits.ch15_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[15].rd_err_dec_unit;
	stDmaCfg15.bits.ch15_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[15].wr_err_gen_thr;
	stDmaCfg15.bits.ch15_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[15].rd_err_gen_thr;
	isp_reg_writel(isp,stDmaCfg15.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH15_ERR_DEC_CFG);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetDmaErrStatus(struct isp_device *isp,ISP_WRAP_DMA_ERR_STATUS_S *pstErrStatus)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstErrStatus);

	U_ISP_WRAP_DMA_CH0_ERR_STATUS stDmaCfg0;	
	stDmaCfg0.u32 = 0;
	stDmaCfg0.bits.ch0_err_y_wr_status = pstErrStatus->stDmaErrStatus[0].err_y_wr_status;
	stDmaCfg0.bits.ch0_err_uv_wr_status = pstErrStatus->stDmaErrStatus[0].err_uv_wr_status;
	stDmaCfg0.bits.ch0_err_raw_read_status = pstErrStatus->stDmaErrStatus[0].err_raw_read_status;
	stDmaCfg0.bits.ch0_err_wr_rst_req = pstErrStatus->stDmaErrStatus[0].err_wr_rst_req;
	stDmaCfg0.bits.ch0_err_rd_rst_req = pstErrStatus->stDmaErrStatus[0].err_rd_rst_req;
	isp_reg_writel(isp,stDmaCfg0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH0_ERR_STATUS);

	U_ISP_WRAP_DMA_CH1_ERR_STATUS stDmaCfg1;
	stDmaCfg1.u32 = 0;
	stDmaCfg1.bits.ch1_err_y_wr_status = pstErrStatus->stDmaErrStatus[1].err_y_wr_status;
	stDmaCfg1.bits.ch1_err_uv_wr_status = pstErrStatus->stDmaErrStatus[1].err_uv_wr_status;
	stDmaCfg1.bits.ch1_err_raw_read_status = pstErrStatus->stDmaErrStatus[1].err_raw_read_status;
	stDmaCfg1.bits.ch1_err_wr_rst_req = pstErrStatus->stDmaErrStatus[1].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH1_ERR_STATUS);

	U_ISP_WRAP_DMA_CH2_ERR_STATUS stDmaCfg2;
	stDmaCfg2.u32 = 0;
	stDmaCfg2.bits.ch2_err_y_wr_status = pstErrStatus->stDmaErrStatus[2].err_y_wr_status;
	stDmaCfg2.bits.ch2_err_uv_wr_status = pstErrStatus->stDmaErrStatus[2].err_uv_wr_status;
	stDmaCfg2.bits.ch2_err_raw_read_status = pstErrStatus->stDmaErrStatus[2].err_raw_read_status;
	stDmaCfg2.bits.ch2_err_wr_rst_req = pstErrStatus->stDmaErrStatus[2].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg2.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH2_ERR_STATUS);

	U_ISP_WRAP_DMA_CH3_ERR_STATUS stDmaCfg3;	
	stDmaCfg3.u32 = 0;
	stDmaCfg3.bits.ch3_err_y_wr_status = pstErrStatus->stDmaErrStatus[3].err_y_wr_status;
	stDmaCfg3.bits.ch3_err_uv_wr_status = pstErrStatus->stDmaErrStatus[3].err_uv_wr_status;
	stDmaCfg3.bits.ch3_err_raw_read_status = pstErrStatus->stDmaErrStatus[3].err_raw_read_status;
	stDmaCfg3.bits.ch3_err_wr_rst_req = pstErrStatus->stDmaErrStatus[3].err_wr_rst_req;
    isp_reg_writel(isp,stDmaCfg3.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH3_ERR_STATUS);

	U_ISP_WRAP_DMA_CH4_ERR_STATUS stDmaCfg4;
	stDmaCfg4.u32 = 0;
	stDmaCfg4.bits.ch4_err_y_wr_status = pstErrStatus->stDmaErrStatus[4].err_y_wr_status;
	stDmaCfg4.bits.ch4_err_uv_wr_status = pstErrStatus->stDmaErrStatus[4].err_uv_wr_status;
	stDmaCfg4.bits.ch4_err_raw_read_status = pstErrStatus->stDmaErrStatus[4].err_raw_read_status;
	stDmaCfg4.bits.ch4_err_wr_rst_req = pstErrStatus->stDmaErrStatus[4].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg4.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH4_ERR_STATUS);

	U_ISP_WRAP_DMA_CH5_ERR_STATUS stDmaCfg5;
	stDmaCfg5.u32 = 0;
	stDmaCfg5.bits.ch5_err_y_wr_status = pstErrStatus->stDmaErrStatus[5].err_y_wr_status;
	stDmaCfg5.bits.ch5_err_uv_wr_status = pstErrStatus->stDmaErrStatus[5].err_uv_wr_status;
	stDmaCfg5.bits.ch5_err_raw_read_status = pstErrStatus->stDmaErrStatus[5].err_raw_read_status;
	stDmaCfg5.bits.ch5_err_wr_rst_req = pstErrStatus->stDmaErrStatus[5].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg5.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH5_ERR_STATUS);

	U_ISP_WRAP_DMA_CH6_ERR_STATUS stDmaCfg6;
	stDmaCfg6.u32 = 0;
	stDmaCfg6.bits.ch6_err_y_wr_status = pstErrStatus->stDmaErrStatus[6].err_y_wr_status;
	stDmaCfg6.bits.ch6_err_uv_wr_status = pstErrStatus->stDmaErrStatus[6].err_uv_wr_status;
	stDmaCfg6.bits.ch6_err_raw_read_status = pstErrStatus->stDmaErrStatus[6].err_raw_read_status;
	stDmaCfg6.bits.ch6_err_wr_rst_req = pstErrStatus->stDmaErrStatus[6].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg6.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH6_ERR_STATUS);

	U_ISP_WRAP_DMA_CH7_ERR_STATUS stDmaCfg7;
	stDmaCfg7.u32 = 0;
	stDmaCfg7.bits.ch7_err_y_wr_status = pstErrStatus->stDmaErrStatus[7].err_y_wr_status;
	stDmaCfg7.bits.ch7_err_uv_wr_status = pstErrStatus->stDmaErrStatus[7].err_uv_wr_status;
	stDmaCfg7.bits.ch7_err_raw_read_status = pstErrStatus->stDmaErrStatus[7].err_raw_read_status;
	stDmaCfg7.bits.ch7_err_wr_rst_req = pstErrStatus->stDmaErrStatus[7].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg7.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH7_ERR_STATUS);

	U_ISP_WRAP_DMA_CH8_ERR_STATUS stDmaCfg8;
	stDmaCfg8.u32 = 0;
	stDmaCfg8.bits.ch8_err_y_wr_status = pstErrStatus->stDmaErrStatus[8].err_y_wr_status;
	stDmaCfg8.bits.ch8_err_uv_wr_status = pstErrStatus->stDmaErrStatus[8].err_uv_wr_status;
	stDmaCfg8.bits.ch8_err_raw_read_status = pstErrStatus->stDmaErrStatus[8].err_raw_read_status;
	stDmaCfg8.bits.ch8_err_wr_rst_req = pstErrStatus->stDmaErrStatus[8].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg8.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH8_ERR_STATUS);

	U_ISP_WRAP_DMA_CH9_ERR_STATUS stDmaCfg9;
	stDmaCfg9.u32 = 0;
	stDmaCfg9.bits.ch9_err_y_wr_status = pstErrStatus->stDmaErrStatus[9].err_y_wr_status;
	stDmaCfg9.bits.ch9_err_uv_wr_status = pstErrStatus->stDmaErrStatus[9].err_uv_wr_status;
	stDmaCfg9.bits.ch9_err_raw_read_status = pstErrStatus->stDmaErrStatus[9].err_raw_read_status;
	stDmaCfg9.bits.ch9_err_wr_rst_req = pstErrStatus->stDmaErrStatus[9].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg9.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH9_ERR_STATUS);
	
	U_ISP_WRAP_DMA_CH10_ERR_STATUS stDmaCfg10;
	stDmaCfg10.u32 = 0;
	stDmaCfg10.bits.ch10_err_y_wr_status = pstErrStatus->stDmaErrStatus[10].err_y_wr_status;
	stDmaCfg10.bits.ch10_err_uv_wr_status = pstErrStatus->stDmaErrStatus[10].err_uv_wr_status;
	stDmaCfg10.bits.ch10_err_raw_read_status = pstErrStatus->stDmaErrStatus[10].err_raw_read_status;
	stDmaCfg10.bits.ch10_err_wr_rst_req = pstErrStatus->stDmaErrStatus[10].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg10.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH10_ERR_STATUS);

	U_ISP_WRAP_DMA_CH11_ERR_STATUS stDmaCfg11;
	stDmaCfg11.u32 = 0;
	stDmaCfg11.bits.ch11_err_y_wr_status = pstErrStatus->stDmaErrStatus[11].err_y_wr_status;
	stDmaCfg11.bits.ch11_err_uv_wr_status = pstErrStatus->stDmaErrStatus[11].err_uv_wr_status;
	stDmaCfg11.bits.ch11_err_raw_read_status = pstErrStatus->stDmaErrStatus[11].err_raw_read_status;
	stDmaCfg11.bits.ch11_err_wr_rst_req = pstErrStatus->stDmaErrStatus[11].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg11.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH11_ERR_STATUS);	

	U_ISP_WRAP_DMA_CH12_ERR_STATUS stDmaCfg12;
	stDmaCfg12.u32 = 0;
	stDmaCfg12.bits.ch12_err_y_wr_status = pstErrStatus->stDmaErrStatus[12].err_y_wr_status;
	stDmaCfg12.bits.ch12_err_uv_wr_status = pstErrStatus->stDmaErrStatus[12].err_uv_wr_status;
	stDmaCfg12.bits.ch12_err_raw_read_status = pstErrStatus->stDmaErrStatus[12].err_raw_read_status;
	stDmaCfg12.bits.ch12_err_wr_rst_req = pstErrStatus->stDmaErrStatus[12].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg12.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH12_ERR_STATUS);

	U_ISP_WRAP_DMA_CH13_ERR_STATUS stDmaCfg13;
	stDmaCfg13.u32 = 0;
	stDmaCfg13.bits.ch13_err_y_wr_status = pstErrStatus->stDmaErrStatus[13].err_y_wr_status;
	stDmaCfg13.bits.ch13_err_uv_wr_status = pstErrStatus->stDmaErrStatus[13].err_uv_wr_status;
	stDmaCfg13.bits.ch13_err_raw_read_status = pstErrStatus->stDmaErrStatus[13].err_raw_read_status;
	stDmaCfg13.bits.ch13_err_wr_rst_req = pstErrStatus->stDmaErrStatus[13].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg13.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH13_ERR_STATUS);

	U_ISP_WRAP_DMA_CH14_ERR_STATUS stDmaCfg14;
	stDmaCfg14.u32 = 0;
	stDmaCfg14.bits.ch14_err_y_wr_status = pstErrStatus->stDmaErrStatus[14].err_y_wr_status;
	stDmaCfg14.bits.ch14_err_uv_wr_status = pstErrStatus->stDmaErrStatus[14].err_uv_wr_status;
	stDmaCfg14.bits.ch14_err_raw_read_status = pstErrStatus->stDmaErrStatus[14].err_raw_read_status;
	stDmaCfg14.bits.ch14_err_wr_rst_req = pstErrStatus->stDmaErrStatus[14].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg14.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH14_ERR_STATUS);	

	U_ISP_WRAP_DMA_CH15_ERR_STATUS stDmaCfg15;
	stDmaCfg15.u32 = 0;
	stDmaCfg15.bits.ch15_err_y_wr_status = pstErrStatus->stDmaErrStatus[15].err_y_wr_status;
	stDmaCfg15.bits.ch15_err_uv_wr_status = pstErrStatus->stDmaErrStatus[15].err_uv_wr_status;
	stDmaCfg15.bits.ch15_err_raw_read_status = pstErrStatus->stDmaErrStatus[15].err_raw_read_status;
	stDmaCfg15.bits.ch15_err_wr_rst_req = pstErrStatus->stDmaErrStatus[15].err_wr_rst_req;
	isp_reg_writel(isp,stDmaCfg15.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_CH15_ERR_STATUS);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetDma(struct isp_device *isp,ISP_WRAP_DMA_ATTR_S *pstDmaAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaAttr);

	ISP_WRAP_DMA_MODE_S *pstDmaMode = &(pstDmaAttr->stDmaChMode);
	Isp_Drv_R2k_Wrap_SetDmaMode(isp,pstDmaMode);

	ISP_WRAP_DMA_CFG_S *pstDmaCfg = &(pstDmaAttr->stDmaCfg);
	Isp_Drv_R2k_Wrap_SetDmaCfgMode(isp,pstDmaCfg);

	ISP_WRAP_DMA_ERR_DEC_CFG_S *pstDmaErrDec = &(pstDmaAttr->stErrDecCfg);
	Isp_Drv_R2k_Wrap_SetDmaErrDecCfg(isp,pstDmaErrDec);

	ISP_WRAP_DMA_ERR_STATUS_S *pstErrStatus = &(pstDmaAttr->stErrStatus);
	Isp_Drv_R2k_Wrap_SetDmaErrStatus(isp,pstErrStatus);

	return 0;
}
/*
*buf
*/
int Isp_Drv_R2k_Wrap_SetwdrBuf(struct isp_device *isp,ISP_WRAP_WDR_BUF_S *pstWdrBuf)
{	
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrBuf);

    U_ISP_WRAP_WDR_LONG_BUF_BASE stWdrBuf;
	stWdrBuf.u32 = 0x00F80000;
	isp_reg_writel(isp,stWdrBuf.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_WDR_LONG_BUF_BASE);
	//0x21
    U_ISP_WRAP_WDR_LONG_SIZE_CFG stWdrSize;
	stWdrSize.u32 = 0x00011000;
	isp_reg_writel(isp,stWdrSize.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_WDR_LONG_SIZE_CFG);

	return 0;	
}

int Isp_Drv_R2k_Wrap_Set3dnrBuf(struct isp_device *isp,ISP_WRAP_3DNR_BUF_S *pst3dnrBuf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pst3dnrBuf);

	U_ISP_WRAP_3DNR_Y_BUF_BASE stYbufBase;
	stYbufBase.u32 = 0;
	stYbufBase.bits.y_3dnr_buf_base = pst3dnrBuf->y_3dnr_buf_base;
	isp_reg_writel(isp,stYbufBase.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_Y_BUF_BASE);

	U_ISP_WRAP_3DNR_UV_BUF_BASE stUvbufBase;
	stUvbufBase.u32 = 0;
	stUvbufBase.bits.uv_3dnr_buf_base = pst3dnrBuf->uv_3dnr_buf_base;
	isp_reg_writel(isp,stUvbufBase.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_UV_BUF_BASE);

	U_ISP_WRAP_3DNR_STRIDE stStride;
	stStride.u32 = 0;
	stStride.bits.y_3dnr_line_stride = pst3dnrBuf->y_3dnr_line_stride;
	stStride.bits.uv_3dnr_line_stride = pst3dnrBuf->uv_3dnr_line_stride;
	isp_reg_writel(isp,stStride.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_3DNR_STRIDE);
	
	return 0;
}

int Isp_Drv_R2k_Wrap_SetLdcBuf(struct isp_device *isp,ISP_WRAP_LDC_BUF_S *pstLdcBuf)
{	
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstLdcBuf);

	U_ISP_WRAP_LDC_Y_BUF_BASE stYbufBase;
	stYbufBase.u32 = 0;
	stYbufBase.bits.ldc_y_buf_base = pstLdcBuf->ldc_y_buf_base;
	isp_reg_writel(isp,stYbufBase.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_LDC_Y_BUF_BASE);

	U_ISP_WRAP_LDC_UV_BUF_BASE stUvbufBase;
	stUvbufBase.u32 = 0;
	stUvbufBase.bits.ldc_uv_buf_base = pstLdcBuf->ldc_uv_buf_base;
	isp_reg_writel(isp,stUvbufBase.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_LDC_UV_BUF_BASE);

	U_ISP_WRAP_LDC_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ldc_y_line_stride = pstLdcBuf->ldc_y_line_stride;
	stStride.bits.ldc_uv_line_stride = pstLdcBuf->ldc_uv_line_stride;
	isp_reg_writel(isp,stStride.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_LDC_STRIDE);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetMainBuf(struct isp_device *isp,ISP_WRAP_MAIN_BUF_S *pstMainBuf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstMainBuf);

	U_ISP_WRAP_MAIN_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.main_y_buf0_base = pstMainBuf->main_y_buf0_base;
	isp_reg_writel(isp,stYbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_Y_BUF0_BASE);

	U_ISP_WRAP_MAIN_Y_BUF1_BASE stYbufBase1;		
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.main_y_buf1_base = pstMainBuf->main_y_buf1_base;
	isp_reg_writel(isp,stYbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_Y_BUF1_BASE);

	U_ISP_WRAP_MAIN_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.main_uv_buf0_base = pstMainBuf->main_uv_buf0_base;
	isp_reg_writel(isp,stUvbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_UV_BUF0_BASE);

	U_ISP_WRAP_MAIN_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.main_uv_buf1_base = pstMainBuf->main_uv_buf1_base;
	isp_reg_writel(isp,stUvbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_UV_BUF1_BASE);

	U_ISP_WRAP_MAIN_STRIDE stStride;
	stStride.u32 = 0;
	stStride.bits.main_y_line_stride = pstMainBuf->main_y_line_stride;
	stStride.bits.main_uv_line_stride = pstMainBuf->main_uv_line_stride;
	isp_reg_writel(isp,stStride.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_MAIN_STRIDE);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetDs0Buf(struct isp_device *isp,ISP_WRAP_DS0_BUF_S *pstDs0Buf)
{	
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs0Buf);

	U_ISP_WRAP_DS0_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.ds0_y_buf0_base = pstDs0Buf->ds0_y_buf0_base;
	isp_reg_writel(isp,stYbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_Y_BUF0_BASE);
	
	U_ISP_WRAP_DS0_Y_BUF1_BASE stYbufBase1;
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.ds0_y_buf1_base = pstDs0Buf->ds0_y_buf1_base;
	isp_reg_writel(isp,stYbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_Y_BUF1_BASE);

	U_ISP_WRAP_DS0_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.ds0_uv_buf0_base = pstDs0Buf->ds0_uv_buf0_base;
	isp_reg_writel(isp,stUvbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_UV_BUF0_BASE);

	U_ISP_WRAP_DS0_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.ds0_uv_buf1_base = pstDs0Buf->ds0_uv_buf1_base;
	isp_reg_writel(isp,stUvbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_UV_BUF1_BASE);

	U_ISP_WRAP_DS0_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ds0_y_line_stride = pstDs0Buf->ds0_y_line_stride;
	stStride.bits.ds0_uv_line_stride = pstDs0Buf->ds0_uv_line_stride;	
	isp_reg_writel(isp,stStride.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS0_STRIDE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetDs1Buf(struct isp_device *isp,ISP_WRAP_DS1_BUF_S *pstDs1Buf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs1Buf);

	U_ISP_WRAP_DS1_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.ds1_y_buf0_base = pstDs1Buf->ds1_y_buf0_base;
	isp_reg_writel(isp,stYbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_Y_BUF0_BASE);
	
	U_ISP_WRAP_DS1_Y_BUF1_BASE stYbufBase1;
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.ds1_y_buf1_base = pstDs1Buf->ds1_y_buf1_base;
	isp_reg_writel(isp,stYbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_Y_BUF1_BASE);

	U_ISP_WRAP_DS1_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.ds1_uv_buf0_base = pstDs1Buf->ds1_uv_buf0_base;
	isp_reg_writel(isp,stUvbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_UV_BUF0_BASE);

	U_ISP_WRAP_DS1_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.ds1_uv_buf1_base = pstDs1Buf->ds1_uv_buf1_base;
	isp_reg_writel(isp,stUvbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_UV_BUF1_BASE);	

	U_ISP_WRAP_DS1_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ds1_y_line_stride = pstDs1Buf->ds1_y_line_stride;
	stStride.bits.ds1_uv_line_stride = pstDs1Buf->ds1_uv_line_stride;	
	isp_reg_writel(isp,stStride.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS1_STRIDE);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetDs2Buf(struct isp_device *isp,ISP_WRAP_DS2_BUF_S *pstDs2Buf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs2Buf);

	U_ISP_WRAP_DS2_R_BUF0_BASE stRbufBase0;
	stRbufBase0.u32 = 0;
	stRbufBase0.bits.ds2_r_buf0_base = pstDs2Buf->ds2_r_buf0_base;
	isp_reg_writel(isp,stRbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_R_BUF0_BASE);

	U_ISP_WRAP_DS2_R_BUF1_BASE stRbufBase1;
	stRbufBase1.u32 = 0;
	stRbufBase1.bits.ds2_r_buf1_base = pstDs2Buf->ds2_r_buf1_base;
	isp_reg_writel(isp,stRbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_R_BUF1_BASE);	

	U_ISP_WRAP_DS2_G_BUF0_BASE stGbufBase0;
	stGbufBase0.u32 = 0;
	stGbufBase0.bits.ds2_g_buf0_base = pstDs2Buf->ds2_g_buf0_base;
	isp_reg_writel(isp,stGbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_G_BUF0_BASE);

	U_ISP_WRAP_DS2_G_BUF1_BASE stGbufBase1;
	stGbufBase1.u32 = 0;
	stGbufBase1.bits.ds2_g_buf1_base = pstDs2Buf->ds2_g_buf1_base;
	isp_reg_writel(isp,stGbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_G_BUF1_BASE);

	U_ISP_WRAP_DS2_B_BUF0_BASE stBbufBase0;
	stBbufBase0.u32 = 0;
	stBbufBase0.bits.ds2_b_buf0_base = pstDs2Buf->ds2_b_buf0_base;
	isp_reg_writel(isp,stBbufBase0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_B_BUF0_BASE);

	U_ISP_WRAP_DS2_B_BUF1_BASE stBbufBase1;
	stBbufBase1.u32 = 0;
	stBbufBase1.bits.ds2_b_buf1_base = pstDs2Buf->ds2_b_buf1_base;
	isp_reg_writel(isp,stBbufBase1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_B_BUF1_BASE);

	U_ISP_WRAP_DS2_STRIDE0 stStride0;	
	stStride0.u32 = 0;
	stStride0.bits.ds2_r_line_stride = pstDs2Buf->ds2_r_line_stride;
	stStride0.bits.ds2_g_line_stride = pstDs2Buf->ds2_g_line_stride;
	isp_reg_writel(isp,stStride0.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_STRIDE0);

	U_ISP_WRAP_DS2_STRIDE1 stStride1;
	stStride1.u32 = 0;
	stStride1.bits.ds2_b_line_stride = pstDs2Buf->ds2_b_line_stride;
	isp_reg_writel(isp,stStride1.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DS2_STRIDE1);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetAxiCtl(struct isp_device *isp,ISP_WRAP_AXI_CTL_S *pstAxiCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstAxiCtl);

	U_ISP_WRAP_AXI_CTL stData;
	stData.u32 = 0;
	stData.bits.axi_wr_ch_rst_req = pstAxiCtl->axi_wr_ch_rst_req;   
	stData.bits.axi_rd_ch_rst_req = pstAxiCtl->axi_rd_ch_rst_req;    
	stData.bits.axi_wr_ch_state = pstAxiCtl->axi_wr_ch_state;
	stData.bits.axi_rd_ch_state = pstAxiCtl->axi_rd_ch_state;    
	//stData.u32 = 0x00000F74;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_AXI_CTL);
	return 0;
}

int Isp_Drv_R2k_Wrap_SetConfigdoneCtl(struct isp_device *isp,ISP_WRAP_CONFIG_DONE_S *pstConfigDone)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstConfigDone);

    U_ISP_WRAP_CONFIG_DONE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CONFIG_DONE);
	stData.bits.wrap_config_done_en = pstConfigDone->wrap_config_done_en;//1;
	stData.bits.int_polarity        = pstConfigDone->int_polarity;//1
	stData.bits.sen_reg_pro_en      = pstConfigDone->sen_reg_pro_en;//0
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CONFIG_DONE);

	return 0;
}
/*
*INT
*/
int Isp_Drv_R2k_Wrap_SetCoreIntCtlMask(struct isp_device *isp,ISP_WRAP_CORE_INT_CTL_S *pstCoreIntCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstCoreIntCtl);

	U_ISP_WRAP_CORE_INT_CTL stData;
	stData.u32 = 0xffff0000;
 	stData.bits.int_raw_in_mask = pstCoreIntCtl->int_raw_in_mask;    
    stData.bits.int_3a_mask = pstCoreIntCtl->int_3a_mask;        
    stData.bits.raw_int_mask = pstCoreIntCtl->raw_int_mask;        
    stData.bits.rgb_int_mask = pstCoreIntCtl->rgb_int_mask;      
    stData.bits.yuv_int_mask = pstCoreIntCtl->yuv_int_mask;      
    stData.bits.ldc_int_mask = pstCoreIntCtl->ldc_int_mask;      
    stData.bits.main_out_int_mask = pstCoreIntCtl->main_out_int_mask; 
    stData.bits.isp_awb_int_mask = pstCoreIntCtl->isp_awb_int_mask; 
    stData.bits.isp_ae_int_mask = pstCoreIntCtl->isp_ae_int_mask;   
    stData.bits.isp_af_int_mask = pstCoreIntCtl->isp_af_int_mask; 
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_CORE_INT_CTL);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetDmaWRIntMask0(struct isp_device *isp,ISP_WRAP_DMA_WR_INT_MASK0_S *pstDmaWRIntMask0)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaWRIntMask0);

	U_ISP_WRAP_DMA_WR_INT_MASK0 stData;
	stData.u32 = 0xFFFFFFFF;
    stData.bits.wr_3dnr_y_frm_end_int_mask = pstDmaWRIntMask0->wr_3dnr_y_frm_end_int_mask;            
    stData.bits.wr_3dnr_y_line_base_int_mask = pstDmaWRIntMask0->wr_3dnr_y_line_base_int_mask;          
    stData.bits.wr_3dnr_y_err_frm_end_int_mask = pstDmaWRIntMask0->wr_3dnr_y_err_frm_end_int_mask;        
    stData.bits.wr_3dnr_y_err_immediate_int_mask = pstDmaWRIntMask0->wr_3dnr_y_err_immediate_int_mask;      
    stData.bits.wr_3dnr_uv_frm_end_int_mask = pstDmaWRIntMask0->wr_3dnr_uv_frm_end_int_mask;           
    stData.bits.wr_3dnr_uv_line_base_int_mask = pstDmaWRIntMask0->wr_3dnr_uv_line_base_int_mask;         
    stData.bits.wr_3dnr_uv_err_frm_end_int_mask = pstDmaWRIntMask0->wr_3dnr_uv_err_frm_end_int_mask;       
    stData.bits.wr_3dnr_uv_err_immediate_int_mask = pstDmaWRIntMask0->wr_3dnr_uv_err_immediate_int_mask;     
    stData.bits.ldc_wr_y_frm_end_int_mask = pstDmaWRIntMask0->ldc_wr_y_frm_end_int_mask;             
    stData.bits.ldc_wr_y_line_base_int_mask = pstDmaWRIntMask0->ldc_wr_y_line_base_int_mask;           
    stData.bits.ldc_wr_y_err_frm_end_int_mask = pstDmaWRIntMask0->ldc_wr_y_err_frm_end_int_mask;         
    stData.bits.ldc_wr_y_err_immediate_int_mask = pstDmaWRIntMask0->ldc_wr_y_err_immediate_int_mask;       
    stData.bits.ldc_wr_uv_frm_end_int_mask = pstDmaWRIntMask0->ldc_wr_uv_frm_end_int_mask;            
    stData.bits.ldc_wr_uv_line_base_int_mask = pstDmaWRIntMask0->ldc_wr_uv_line_base_int_mask;          
    stData.bits.ldc_wr_uv_err_frm_end_int_mask = pstDmaWRIntMask0->ldc_wr_uv_err_frm_end_int_mask;        
    stData.bits.ldc_wr_uv_err_immediate_int_mask = pstDmaWRIntMask0->ldc_wr_uv_err_immediate_int_mask;      
    stData.bits.wdr_wr_raw_frm_end_int_mask = pstDmaWRIntMask0->wdr_wr_raw_frm_end_int_mask;           
    stData.bits.wdr_wr_raw_line_base_int_mask = pstDmaWRIntMask0->wdr_wr_raw_line_base_int_mask;         
    stData.bits.wdr_wr_raw_err_frm_end_int_mask = pstDmaWRIntMask0->wdr_wr_raw_err_frm_end_int_mask;       
    stData.bits.wdr_wr_raw_err_immediate_int_mask = pstDmaWRIntMask0->wdr_wr_raw_err_immediate_int_mask;                     
    stData.bits.main_out_wr_y_frm_end_int_mask = pstDmaWRIntMask0->main_out_wr_y_frm_end_int_mask;        
    stData.bits.main_out_wr_y_line_base_int_mask = pstDmaWRIntMask0->main_out_wr_y_line_base_int_mask;      
    stData.bits.main_out_wr_y_err_frm_end_int_mask = pstDmaWRIntMask0->main_out_wr_y_err_frm_end_int_mask;    
    stData.bits.main_out_wr_y_err_immediate_int_mask = pstDmaWRIntMask0->main_out_wr_y_err_immediate_int_mask;  
    stData.bits.main_out_wr_uv_frm_end_int_mask = pstDmaWRIntMask0->main_out_wr_uv_frm_end_int_mask;       
    stData.bits.main_out_wr_uv_line_base_int_mask = pstDmaWRIntMask0->main_out_wr_uv_line_base_int_mask;     
    stData.bits.main_out_wr_uv_err_frm_end_int_mask = pstDmaWRIntMask0->main_out_wr_uv_err_frm_end_int_mask;   
    stData.bits.main_out_wr_uv_err_immediate_int_mask = pstDmaWRIntMask0->main_out_wr_uv_err_immediate_int_mask; 	
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_INT_MASK0);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetDmaWRIntMask1(struct isp_device *isp,ISP_WRAP_DMA_WR_INT_MASK1_S *pstDmaWRIntMask1)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaWRIntMask1);

	U_ISP_WRAP_DMA_WR_INT_MASK1 stData;
	stData.u32 = 0xFFFFFFFF;
    stData.bits.ds0_out_wr_y_frm_end_mask = pstDmaWRIntMask1->ds0_out_wr_y_frm_end_mask;       
    stData.bits.ds0_out_wr_y_line_base_mask = pstDmaWRIntMask1->ds0_out_wr_y_line_base_mask;     
    stData.bits.ds0_out_wr_y_err_frm_end_mask = pstDmaWRIntMask1->ds0_out_wr_y_err_frm_end_mask;   
    stData.bits.ds0_out_wr_y_err_immediate_mask = pstDmaWRIntMask1->ds0_out_wr_y_err_immediate_mask; 
    stData.bits.ds0_out_wr_uv_frm_end_mask = pstDmaWRIntMask1->ds0_out_wr_uv_frm_end_mask;      
    stData.bits.ds0_out_wr_uv_line_base_mask = pstDmaWRIntMask1->ds0_out_wr_uv_line_base_mask;    
    stData.bits.ds0_out_wr_uv_err_frm_end_mask = pstDmaWRIntMask1->ds0_out_wr_uv_err_frm_end_mask;  
    stData.bits.ds0_out_wr_uv_err_immediate_mask = pstDmaWRIntMask1->ds0_out_wr_uv_err_immediate_mask;
    stData.bits.ds1_out_wr_y_frm_end_mask = pstDmaWRIntMask1->ds1_out_wr_y_frm_end_mask;       
    stData.bits.ds1_out_wr_y_line_base_mask = pstDmaWRIntMask1->ds1_out_wr_y_line_base_mask;     
    stData.bits.ds1_out_wr_y_err_frm_end_mask = pstDmaWRIntMask1->ds1_out_wr_y_err_frm_end_mask;   
    stData.bits.ds1_out_wr_y_err_immediate_mask = pstDmaWRIntMask1->ds1_out_wr_y_err_immediate_mask; 
    stData.bits.ds1_out_wr_uv_frm_end_mask = pstDmaWRIntMask1->ds1_out_wr_uv_frm_end_mask;      
    stData.bits.ds1_out_wr_uv_line_base_mask = pstDmaWRIntMask1->ds1_out_wr_uv_line_base_mask;    
    stData.bits.ds1_out_wr_uv_err_frm_end_mask = pstDmaWRIntMask1->ds1_out_wr_uv_err_frm_end_mask;  
    stData.bits.ds1_out_wr_uv_err_immediate_mask = pstDmaWRIntMask1->ds1_out_wr_uv_err_immediate_mask;
    stData.bits.ds2_out_wr_r_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_r_frm_end_mask;       
    stData.bits.ds2_out_wr_r_line_base_mask = pstDmaWRIntMask1->ds2_out_wr_r_line_base_mask;     
    stData.bits.ds2_out_wr_r_err_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_r_err_frm_end_mask;   
    stData.bits.ds2_out_wr_r_err_immediate_mask = pstDmaWRIntMask1->ds2_out_wr_r_err_immediate_mask; 
    stData.bits.ds2_out_wr_g_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_g_frm_end_mask;       
    stData.bits.ds2_out_wr_g_line_base_mask = pstDmaWRIntMask1->ds2_out_wr_g_line_base_mask;     
    stData.bits.ds2_out_wr_g_err_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_g_err_frm_end_mask;   
    stData.bits.ds2_out_wr_g_err_immediate_mask = pstDmaWRIntMask1->ds2_out_wr_g_err_immediate_mask; 
    stData.bits.ds2_out_wr_b_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_b_frm_end_mask;       
    stData.bits.ds2_out_wr_b_line_base_mask = pstDmaWRIntMask1->ds2_out_wr_b_line_base_mask;     
    stData.bits.ds2_out_wr_b_err_frm_end_mask = pstDmaWRIntMask1->ds2_out_wr_b_err_frm_end_mask;   
    stData.bits.ds2_out_wr_b_err_immediate_mask = pstDmaWRIntMask1->ds2_out_wr_b_err_immediate_mask;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_WR_INT_MASK1);

	return 0;
}

int Isp_Drv_R2k_Wrap_SetDmaRDIntMask0(struct isp_device *isp,ISP_WRAP_DMA_RD_INT_MASK0_S *pstDmaRDIntMask0)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaRDIntMask0);

	U_ISP_WRAP_DMA_RD_INT_MASK0 stData;
	stData.u32 = 0xFFFFFFFF;
	stData.bits.rd_3dnr_y_frm_end_int_mask = pstDmaRDIntMask0->rd_3dnr_y_frm_end_int_mask;        
    stData.bits.rd_3dnr_y_line_base_int_mask = pstDmaRDIntMask0->rd_3dnr_y_line_base_int_mask;      
    stData.bits.rd_3dnr_y_err_frm_end_int_mask = pstDmaRDIntMask0->rd_3dnr_y_err_frm_end_int_mask;    
    stData.bits.rd_3dnr_y_err_immediate_int_mask = pstDmaRDIntMask0->rd_3dnr_y_err_immediate_int_mask;  
    stData.bits.rd_3dnr_uv_frm_end_int_mask = pstDmaRDIntMask0->rd_3dnr_uv_frm_end_int_mask;       
    stData.bits.rd_3dnr_uv_line_base_int_mask = pstDmaRDIntMask0->rd_3dnr_uv_line_base_int_mask;     
    stData.bits.rd_3dnr_uv_err_frm_end_int_mask = pstDmaRDIntMask0->rd_3dnr_uv_err_frm_end_int_mask;   
    stData.bits.rd_3dnr_uv_err_immediate_int_mask = pstDmaRDIntMask0->rd_3dnr_uv_err_immediate_int_mask; 
    stData.bits.ldc_rd_y_frm_end_int_mask = pstDmaRDIntMask0->ldc_rd_y_frm_end_int_mask;         
    stData.bits.ldc_rd_y_line_base_int_mask = pstDmaRDIntMask0->ldc_rd_y_line_base_int_mask;       
    stData.bits.ldc_rd_y_err_frm_end_int_mask = pstDmaRDIntMask0->ldc_rd_y_err_frm_end_int_mask;     
    stData.bits.ldc_rd_y_err_immediate_int_mask = pstDmaRDIntMask0->ldc_rd_y_err_immediate_int_mask;   
    stData.bits.ldc_rd_uv_frm_end_int_mask = pstDmaRDIntMask0->ldc_rd_uv_frm_end_int_mask;        
    stData.bits.ldc_rd_uv_line_base_int_mask = pstDmaRDIntMask0->ldc_rd_uv_line_base_int_mask;      
    stData.bits.ldc_rd_uv_err_frm_end_int_mask = pstDmaRDIntMask0->ldc_rd_uv_err_frm_end_int_mask;    
    stData.bits.ldc_rd_uv_err_immediate_int_mask = pstDmaRDIntMask0->ldc_rd_uv_err_immediate_int_mask;  
    stData.bits.wdr_rd_raw_frm_end_int_mask = pstDmaRDIntMask0->wdr_rd_raw_frm_end_int_mask;       
    stData.bits.wdr_rd_raw_line_base_int_mask = pstDmaRDIntMask0->wdr_rd_raw_line_base_int_mask;     
    stData.bits.wdr_rd_raw_err_frm_end_int_mask = pstDmaRDIntMask0->wdr_rd_raw_err_frm_end_int_mask;   
    stData.bits.wdr_rd_raw_err_immediate_int_mask = pstDmaRDIntMask0->wdr_rd_raw_err_immediate_int_mask; 
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_R2K_WRAP,ISP_WRAP_DMA_RD_INT_MASK0);

	return 0;
}

static int Isp_Drv_R2k_Wrap_SetIntMask(struct isp_device *isp,ISP_WRAP_INT_CTL_S *stIntCtl)
{
	ISP_CHECK_POINTER(stIntCtl);

	ISP_WRAP_CORE_INT_CTL_S *pstCoreIntCtl = &stIntCtl->stCoreIntCtl;
	Isp_Drv_R2k_Wrap_SetCoreIntCtlMask(isp,pstCoreIntCtl);

	ISP_WRAP_DMA_WR_INT_MASK0_S *pstDmaWRIntMask0 = &stIntCtl->stDmaWRMask0;
	Isp_Drv_R2k_Wrap_SetDmaWRIntMask0(isp,pstDmaWRIntMask0);

	ISP_WRAP_DMA_WR_INT_MASK1_S *pstDmaWRIntMask1 = &stIntCtl->stDmaWRMask1;
	Isp_Drv_R2k_Wrap_SetDmaWRIntMask1(isp,pstDmaWRIntMask1);

	ISP_WRAP_DMA_RD_INT_MASK0_S *pstDmaRDIntMask0 =  &stIntCtl->stDmaRDMask0;
	Isp_Drv_R2k_Wrap_SetDmaRDIntMask0(isp,pstDmaRDIntMask0);

	return 0;
}
/*
*wdr
*/
int Isp_Drv_R2k_Wrap_SetWdr(struct isp_device *isp,ISP_WRAP_WDR_ATTR_S *pstWdrAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstWdrAttr);

	ISP_WRAP_WDR_MODE_CTL_S *pstWdrModeCtl = &pstWdrAttr->stWdrModeCtl;
	Isp_Drv_R2k_Wrap_SetModeCtl_Wdr(isp,pstWdrModeCtl);

	ISP_WRAP_WDR_CLK_CTL_S *pstWdrClkCtl = &pstWdrAttr->stWdrClkCtl ;
	Isp_Drv_R2k_Wrap_SetWdrClkCtl(isp,pstWdrClkCtl);

	ISP_WRAP_WDR_DMA_EN_CTL_S *pstWdrDmaEn = &pstWdrAttr->stWdrDmaEn;
	Isp_Drv_R2k_Wrap_SetWdrDmaEnCtl(isp,pstWdrDmaEn);

	ISP_WRAP_WDR_PIXEL_FORMAT_CTL_S *pstWdrPixelFormat = &pstWdrAttr->stWdrPixelFormat;
	Isp_Drv_R2k_Wrap_SetWdrFormatCtl(isp,pstWdrPixelFormat);
	
	ISP_WRAP_WDR_BUF_S *pstWdrBuf = &pstWdrAttr->stWdrBuf;
	Isp_Drv_R2k_Wrap_SetwdrBuf(isp,pstWdrBuf);

	return 0;
}
/*
*3dnr
*/
int Isp_Drv_R2k_Wrap_Set3Dnr(struct isp_device *isp,ISP_WRAP_3DNR_ATTR_S *pst3DnrAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pst3DnrAttr);

	unsigned int nr3d_fbcd_en = pst3DnrAttr->nr3d_fbcd_en;
	Isp_Drv_R2k_Wrap_SetModeCtl_3dnr_fbcd_en(isp,nr3d_fbcd_en);

	unsigned int nr3d_mv_out_en = pst3DnrAttr->nr3d_mv_out_en;
	Isp_Drv_R2k_Wrap_SetModeCtl_3dnr_mv_en(isp,nr3d_mv_out_en);

	unsigned int clk_3dnr_en = pst3DnrAttr->clk_3dnr_en;
	Isp_Drv_R2k_Wrap_Set3DnrClkCtl(isp,clk_3dnr_en);

	unsigned int pipe_3dnr_dma_en = pst3DnrAttr->pipe_3dnr_dma_en;
	Isp_Drv_R2k_Wrap_Set3dnrDmaEnCtl(isp,pipe_3dnr_dma_en);

	ISP_WRAP_3DNR_PIXEL_FORMAT_CTL_S *pst3DnrPixelFormat = &pst3DnrAttr->st3DnrPixelFormat;
	Isp_Drv_R2k_Wrap_Set3DnrFormatCtl(isp,pst3DnrPixelFormat);

	ISP_WRAP_3DNR_BUF_S *pst3dnrBuf = &pst3DnrAttr->st3dnrBuf;
	Isp_Drv_R2k_Wrap_Set3dnrBuf(isp,pst3dnrBuf);

	return 0;
}
/*
*ldc
*/
int Isp_Drv_R2k_Wrap_SetLdc(struct isp_device *isp,ISP_WRAP_LDC_ATTR_S *pstLdcAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstLdcAttr);

	unsigned int ldc_clk_en = pstLdcAttr->ldc_clk_en;
	Isp_Drv_R2k_Wrap_SetLdcClkCtl(isp,ldc_clk_en);

	unsigned int ldc_dma_en = pstLdcAttr->ldc_dma_en;
	Isp_Drv_R2k_Wrap_SetLdcDmaEnCtl(isp,ldc_dma_en);

	ISP_WRAP_LDC_BUF_S *pstLdcBuf  = &pstLdcAttr->stLdcBuf;
	Isp_Drv_R2k_Wrap_SetLdcBuf(isp,pstLdcBuf);

	return 0;
}
/*
*main out
*/
int Isp_Drv_R2k_Wrap_SetMainOut(struct isp_device *isp,ISP_WRAP_MAINOUT_ATTR_S *pstMainOutAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstMainOutAttr);

	unsigned int main_out_clk_en = pstMainOutAttr->main_out_clk_en;
	Isp_Drv_R2k_Wrap_SetMainClkCtl(isp,main_out_clk_en);

	unsigned int main_out_dma_en = pstMainOutAttr->main_out_dma_en;
	Isp_Drv_R2k_Wrap_SetMainDmaEnCtl(isp,main_out_dma_en);

	unsigned int pix_remap_main_en = pstMainOutAttr->pix_remap_main_en;
	Isp_Drv_R2k_Wrap_SetModeCtl_remap_main_en(isp,pix_remap_main_en);

	ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *pstMainPixelFormat = &pstMainOutAttr->stMainPixelFormat;
	Isp_Drv_R2k_Wrap_SetMainPixelFormatCtl(isp,pstMainPixelFormat);

	ISP_WRAP_MAIN_OUT_SIZE_S *pstMainOutSize = &pstMainOutAttr->stMainOutSize;
	Isp_Drv_R2k_Wrap_SetMainOutSize(isp,pstMainOutSize);

	ISP_WRAP_MAIN_BUF_S *pstMainBuf = &pstMainOutAttr->stMainBuf;
	Isp_Drv_R2k_Wrap_SetMainBuf(isp,pstMainBuf);

	return 0;
}
/*
*out0
*/
int Isp_Drv_R2k_Wrap_SetDs0Out(struct isp_device *isp,ISP_WRAP_DS0OUT_ATTR_S *pstDs0OutAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs0OutAttr);

	ISP_WRAP_DS0_CLK_CTL_S *pstDs0ClkCtl = &pstDs0OutAttr->stDs0ClkCtl;
	Isp_Drv_R2k_Wrap_SetDs0ClkCtl(isp,pstDs0ClkCtl);

	ISP_WRAP_DS0_DMA_EN_CTL_S *pstDs0DMAEnCtl = &pstDs0OutAttr->stDs0DmaEn;
	Isp_Drv_R2k_Wrap_SetDs0DmaEnCtl(isp,pstDs0DMAEnCtl);

	unsigned int pix_remap_out0_en = pstDs0OutAttr->pix_remap_out0_en;
	Isp_Drv_R2k_Wrap_SetModeCtl_remap_out0_en(isp,pix_remap_out0_en);

	ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *pstDs0PixelFormat = &pstDs0OutAttr->stDs0PixelFormat;
	Isp_Drv_R2k_Wrap_SetDs0PixelFormatCtl(isp,pstDs0PixelFormat);


	ISP_WRAP_DS0_OUT_SIZE_S *stDs0OutSize = &pstDs0OutAttr->stDs0OutSize;
	Isp_Drv_R2k_Wrap_SetDs0OutSize(isp,stDs0OutSize);

	ISP_WRAP_DS0_BUF_S *pstDsBuf = &pstDs0OutAttr->stDs0Buf;
	Isp_Drv_R2k_Wrap_SetDs0Buf(isp,pstDsBuf);

	return 0;
}
/*
*out1
*/
int Isp_Drv_R2k_Wrap_SetDs1Out(struct isp_device *isp,ISP_WRAP_DS1OUT_ATTR_S *pstDs1OutAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs1OutAttr);

	ISP_WRAP_DS1_CLK_CTL_S *pstDs1ClkCtl = &pstDs1OutAttr->stDs1ClkCtl;
	Isp_Drv_R2k_Wrap_SetDs1ClkCtl(isp,pstDs1ClkCtl);

	ISP_WRAP_DS1_DMA_EN_CTL_S *pstDs1DMAEnCtl = &pstDs1OutAttr->stDs1DmaEn;
	Isp_Drv_R2k_Wrap_SetDs1DmaEnCtl(isp,pstDs1DMAEnCtl);

	unsigned int pix_remap_out1_en = pstDs1OutAttr->pix_remap_out1_en;
	Isp_Drv_R2k_Wrap_SetModeCtl_remap_out1_en(isp,pix_remap_out1_en);

	ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *pstDs1PixelFormat = &pstDs1OutAttr->stDs1PixelFormat;
	Isp_Drv_R2k_Wrap_SetDs1PixelFormatCtl(isp,pstDs1PixelFormat);

	ISP_WRAP_DS1_OUT_SIZE_S *stDs1OutSize = &pstDs1OutAttr->stDs1OutSize;
	Isp_Drv_R2k_Wrap_SetDs1OutSize(isp,stDs1OutSize);

	ISP_WRAP_DS1_BUF_S *pstDsBuf = &pstDs1OutAttr->stDs1Buf;
	Isp_Drv_R2k_Wrap_SetDs1Buf(isp,pstDsBuf);

	return 0;
}
/*
*out2
*/
int Isp_Drv_R2k_Wrap_SetDs2Out(struct isp_device *isp,ISP_WRAP_DS2OUT_ATTR_S *pstDs2OutAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDs2OutAttr);

	ISP_WRAP_DS2_CLK_CTL_S *pstDs2ClkCtl = &pstDs2OutAttr->stDs2ClkCtl;
	Isp_Drv_R2k_Wrap_SetDs2ClkCtl(isp,pstDs2ClkCtl);

	ISP_WRAP_DS2_DMA_EN_CTL_S *pstDs2DMAEnCtl = &pstDs2OutAttr->stDs2DmaEn;
	Isp_Drv_R2k_Wrap_SetDs2DmaEnCtl(isp,pstDs2DMAEnCtl);

	ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *pstDs2PixelFormat = &pstDs2OutAttr->stDs2PixelFormat;
	Isp_Drv_R2k_Wrap_SetDs2PixelFormatCtl(isp,pstDs2PixelFormat);

	ISP_WRAP_DS2_OUT_SIZE_S *stDs2OutSize = &pstDs2OutAttr->stDs2OutSize;
	Isp_Drv_R2k_Wrap_SetDs2OutSize(isp,stDs2OutSize);

	ISP_WRAP_DS2_BUF_S *pstDs2Buf = &pstDs2OutAttr->stDs2Buf;
	Isp_Drv_R2k_Wrap_SetDs2Buf(isp,pstDs2Buf);

	return 0;
}
