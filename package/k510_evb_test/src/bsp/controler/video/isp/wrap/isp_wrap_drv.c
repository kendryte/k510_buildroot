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
//#include "video/isp/isp.h"
#include "video/isp/wrap/isp_wrap_calc.h"
#include "video/isp/wrap/isp_wrap_drv.h"
#include "video/isp/wrap/isp_wrap_reg.h"

extern unsigned int *reg_isp_2k_wrap_base;
#define ISP_2K_DRV_WRAP_REG_CTX(pstCtx)	 pstCtx = (S_ISP_WRAP_REGS_TYPE *)(reg_isp_2k_wrap_base);
/*
* reset 
*/
static void ISP_DRV_WRAP_SetPipeReset(void)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);
	
	U_ISP_WRAP_SWRST_CTL stData;
	stData.u32 = 0;
	stData.bits.sw_3dnr_rst = 1;    
	stData.bits.wdr_2_frame_rst = 1;
	stData.bits.wdr_3_frame_rst =1;
	stData.bits.ldc_rst = 1; 
	
	stData.bits.main_out_rst = 1;   
	stData.bits.ds0_out_rst = 1;    
	stData.bits.ds1_out_rst = 1;   
	stData.bits.ds2_out_rst = 1; 
	
	stData.bits.wrap_com_rst = 1;   
	stData.bits.wrap_cfg_rst = 1;   
	stData.bits.core_com_rst = 1;   
	stData.bits.core_cfg_rst = 1; 
	
	stData.bits.axi_wr_ch_rst = 1;  
	stData.bits.axi_rd_ch_rst = 1;  
	//stData.u32 = 0x000fffff;
	ISP_WRAP_DRV_SET_WrapSwrstCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDmaReset(void)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_SWRST_CTL stData;	
	stData.u32 = 0;
	stData.bits.y_3dnr_wr_ch_rst = 1;     
	stData.bits.uv_3dnr_wr_ch_rst = 1;    
	stData.bits.ldc_y_wr_ch_rst = 1;      
	stData.bits.ldc_uv_wr_ch_rst = 1;     
	stData.bits.wdr_raw_wr_ch_rst = 1;    
	stData.bits.main_out_y_wr_ch_rst = 1; 
	stData.bits.main_out_uv_wr_ch_rst= 1;
	stData.bits.y_3dnr_rd_ch_rst = 1;     
	stData.bits.uv_3dnr_rd_ch_rst = 1;    
	stData.bits.ldc_y_rd_ch_rst = 1;      
	stData.bits.ldc_uv_rd_ch_rst = 1;     
	stData.bits.wdr_raw_rd_ch_rst = 1;    
	stData.bits.ds0_out_y_wr_ch_rst = 1;  
	stData.bits.ds0_out_uv_wr_ch_rst = 1; 
	stData.bits.ds1_out_y_wr_ch_rst = 1;  
	stData.bits.ds1_out_uv_wr_ch_rst = 1; 
	stData.bits.ds2_out_r_wr_ch_rst = 1;  
	stData.bits.ds2_out_g_wr_ch_rst = 1;  
	stData.bits.ds2_out_b_wr_ch_rst = 1;  
	stData.bits.ds0_osd0_rd_ch_rst = 1;   
	stData.bits.ds0_osd1_rd_ch_rst = 1;   
	stData.bits.ds1_osd0_rd_ch_rst = 1;   
	stData.bits.ds1_osd1_rd_ch_rst = 1;   
    stData.bits.ds2_osd0_rd_ch_rst = 1;   
	stData.bits.ds2_osd1_rd_ch_rst = 1;
    stData.bits.ds2_osd2_rd_ch_rst = 1;   	
	//stData.u32 = 0xffffffff;
	
	ISP_WRAP_DRV_SET_WrapDmaSwrstCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetReset(void)
{
	ISP_DRV_WRAP_SetPipeReset( );
	ISP_DRV_WRAP_SetDmaReset( );
}
/*
* ctl mode 
*/
static int ISP_DRV_WRAP_SetModeCtl_OutSel(unsigned int external_out_ch_sel)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.external_out_ch_sel = external_out_ch_sel;   
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_DvpMode(unsigned int dvp_input_ch_type)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.dvp_input_ch_type = dvp_input_ch_type;    
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_Wdr(ISP_WRAP_WDR_MODE_CTL_S *pstWdrModeCtl)
{
	ISP_CHECK_POINTER(pstWdrModeCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.wdr_long_ch_mode = pstWdrModeCtl->wdr_long_ch_mode;    
	stData.bits.wdr_long_l2_buf_en = pstWdrModeCtl->wdr_long_l2_buf_en;  
	stData.bits.wdr_short_s1_buf_en = pstWdrModeCtl->wdr_short_s1_buf_en; 
	stData.bits.wdr_dynamic_switch_en = pstWdrModeCtl->wdr_dynamic_switch_en;
	stData.bits.wdr_long_l2_buf_depth = pstWdrModeCtl->wdr_long_l2_buf_depth;  
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_3dnr_mfbcd_en(unsigned int nr3d_mfbcd_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.nr3d_mfbcd_en = nr3d_mfbcd_en;
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_3dnr_mv_en(unsigned int nr3d_mv_out_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.nr3d_mv_out_en = nr3d_mv_out_en; 
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_3a_out_en(unsigned int hist_3a_out_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.hist_3a_out_en = hist_3a_out_en;
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_remap_main_en(unsigned int pix_remap_main_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.pix_remap_main_en = pix_remap_main_en;
//	stData.u32 = 0x700004;

	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_remap_out0_en(unsigned int pix_remap_out0_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.pix_remap_out0_en = pix_remap_out0_en;
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetModeCtl_remap_out1_en(unsigned int pix_remap_out1_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_CTL_MODE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapModeCtl(apstWrapReg);
	stData.bits.pix_remap_out1_en = pix_remap_out1_en;
//	stData.u32 = 0x700004;
	
	ISP_WRAP_DRV_SET_WrapModeCtl(apstWrapReg, stData.u32);
	return 0;
}
/*
*CLOCK CTRL
*/
static void ISP_DRV_WRAP_SetComClkCtl(ISP_WRAP_PIPE_CLK_CTL_S *pstPipeClkCtl)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.wrap_com_clk_en = pstPipeClkCtl->wrap_com_clk_en;       
	stData.bits.wrap_cfg_clk_en = pstPipeClkCtl->wrap_cfg_clk_en;       
	stData.bits.core_com_clk_en = pstPipeClkCtl->core_com_clk_en;       
	stData.bits.core_cfg_clk_en = pstPipeClkCtl->core_cfg_clk_en;
	
	stData.bits.axi_wr_ch_en 	= pstPipeClkCtl->axi_wr_ch_en;          
	stData.bits.axi_rd_ch_en 	= pstPipeClkCtl->axi_rd_ch_en;        
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_Set3DnrClkCtl(unsigned int clk_3dnr_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.clk_3dnr_en = clk_3dnr_en;          
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetWdrClkCtl(ISP_WRAP_WDR_CLK_CTL_S *pstWdrClkCtl)
{
	ISP_CHECK_POINTER(pstWdrClkCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);

	stData.bits.wdr_2_frame_clk_en = pstWdrClkCtl->wdr_2_frame_clk_en;    
	stData.bits.wdr_3_frame_clk_en = pstWdrClkCtl->wdr_3_frame_clk_en;	
      
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetLdcClkCtl(unsigned int ldc_clk_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.ldc_clk_en = ldc_clk_en;        
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetMainClkCtl(unsigned int main_out_clk_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.main_out_clk_en = main_out_clk_en;          
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs0ClkCtl(ISP_WRAP_DS0_CLK_CTL_S *pstDs0ClkCtl)
{
	ISP_CHECK_POINTER(pstDs0ClkCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.ds0_out_clk_en 			= pstDs0ClkCtl->ds0_out_clk_en; 
	stData.bits.ds0_out_y_ch_clk_en 	= pstDs0ClkCtl->ds0_out_y_ch_clk_en;   
	stData.bits.ds0_out_uv_ch_clk_en 	= pstDs0ClkCtl->ds0_out_uv_ch_clk_en;
    stData.bits.ds_out0_osd0_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd0_ch_clk_en;
	stData.bits.ds_out0_osd1_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd1_ch_clk_en;
	stData.bits.ds_out0_osd2_ch_clk_en 	= pstDs0ClkCtl->ds_out0_osd2_ch_clk_en;          
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs1ClkCtl(ISP_WRAP_DS1_CLK_CTL_S *pstDs1ClkCtl)
{
	ISP_CHECK_POINTER(pstDs1ClkCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.ds1_out_clk_en 			= pstDs1ClkCtl->ds1_out_clk_en;  
 	stData.bits.ds1_out_y_ch_clk_en 	= pstDs1ClkCtl->ds1_out_y_ch_clk_en;   
	stData.bits.ds1_out_uv_ch_clk_en 	= pstDs1ClkCtl->ds1_out_uv_ch_clk_en;    
	stData.bits.ds_out1_osd0_ch_clk_en  = pstDs1ClkCtl->ds_out1_osd0_ch_clk_en;	
	stData.bits.ds_out1_osd1_ch_clk_en 	= pstDs1ClkCtl->ds_out1_osd1_ch_clk_en;
	stData.bits.ds_out1_osd2_ch_clk_en 	= pstDs1ClkCtl->ds_out1_osd2_ch_clk_en;
       
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs2ClkCtl(ISP_WRAP_DS2_CLK_CTL_S *pstDs2ClkCtl)
{
	ISP_CHECK_POINTER(pstDs2ClkCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_PIPE_CLK_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapPipeClkCtl(apstWrapReg);
	stData.bits.ds2_out_clk_en 			= pstDs2ClkCtl->ds2_out_clk_en; 
	stData.bits.ds2_out_r_ch_clk_en 	= pstDs2ClkCtl->ds2_out_r_ch_clk_en;   
	stData.bits.ds2_out_g_ch_clk_en 	= pstDs2ClkCtl->ds2_out_g_ch_clk_en;	
	stData.bits.ds2_out_b_ch_clk_en 	= pstDs2ClkCtl->ds2_out_b_ch_clk_en;
	stData.bits.ds_out2_osd0_ch_clk_en 	= pstDs2ClkCtl->ds_out2_osd0_ch_clk_en;
	stData.bits.ds_out2_osd1_ch_clk_en 	= pstDs2ClkCtl->ds_out2_osd1_ch_clk_en;       
	//stData.u32 = 0xffffffff;
	ISP_WRAP_DRV_SET_WrapPipeClkCtl(apstWrapReg, stData.u32);
	return ;	
}
/*
*DMA EN
*/
static void ISP_DRV_WRAP_Set3dnrDmaEnCtl(unsigned int pipe_3dnr_dma_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);
	stData.bits.pipe_3dnr_dma_en = pipe_3dnr_dma_en;     
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetWdrDmaEnCtl(ISP_WRAP_WDR_DMA_EN_CTL_S *pstWdrDmaEn)
{
	ISP_CHECK_POINTER(pstWdrDmaEn);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);

	stData.bits.wdr_long_dma_en = pstWdrDmaEn->wdr_long_dma_en;
	stData.bits.wdr_short_dma_en = pstWdrDmaEn->wdr_short_dma_en; 
 
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetLdcDmaEnCtl(unsigned int ldc_dma_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);
	stData.bits.ldc_dma_en = ldc_dma_en;    
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetMainDmaEnCtl(unsigned int main_out_dma_en)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);
	stData.bits.main_out_dma_en = main_out_dma_en;     
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs0DmaEnCtl(ISP_WRAP_DS0_DMA_EN_CTL_S *pstDs0DMAEnCtl)
{
	ISP_CHECK_POINTER(pstDs0DMAEnCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);
	stData.bits.ds_out0_dma_en = pstDs0DMAEnCtl->ds_out0_dma_en;
    stData.bits.ds_out0_y_ch_dma_en = pstDs0DMAEnCtl->ds_out0_y_ch_dma_en; 
    stData.bits.ds_out0_uv_ch_dma_en = pstDs0DMAEnCtl->ds_out0_uv_ch_dma_en;
    stData.bits.ds0_osd0_ch_dma_en = pstDs0DMAEnCtl->ds0_osd0_ch_dma_en; 
	stData.bits.ds0_osd1_ch_dma_en = pstDs0DMAEnCtl->ds0_osd1_ch_dma_en;
	stData.bits.ds0_osd2_ch_dma_en = pstDs0DMAEnCtl->ds0_osd2_ch_dma_en;  	      
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs1DmaEnCtl(ISP_WRAP_DS1_DMA_EN_CTL_S *pstDs1DMAEnCtl)
{
	ISP_CHECK_POINTER(pstDs1DMAEnCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);
	stData.bits.ds_out1_dma_en = pstDs1DMAEnCtl->ds_out1_dma_en; 
    stData.bits.ds_out1_y_ch_dma_en = pstDs1DMAEnCtl->ds_out1_y_ch_dma_en; 
    stData.bits.ds_out1_uv_ch_dma_en = pstDs1DMAEnCtl->ds_out1_uv_ch_dma_en;
    stData.bits.ds1_osd0_ch_dma_en = pstDs1DMAEnCtl->ds1_osd0_ch_dma_en;  
    stData.bits.ds1_osd1_ch_dma_en = pstDs1DMAEnCtl->ds1_osd1_ch_dma_en;
	stData.bits.ds1_osd2_ch_dma_en = pstDs1DMAEnCtl->ds1_osd2_ch_dma_en;  	 	      
	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}

static void ISP_DRV_WRAP_SetDs2DmaEnCtl(ISP_WRAP_DS2_DMA_EN_CTL_S *pstDs2DMAEnCtl)
{
	ISP_CHECK_POINTER(pstDs2DMAEnCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_EN_CTL stData;	
	stData.u32 = ISP_WRAP_DRV_GET_WrapDmaEnCtl(apstWrapReg);    
    stData.bits.ds_out2_dma_en 			= pstDs2DMAEnCtl->ds_out2_dma_en;    
    stData.bits.ds_out2_r_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_r_ch_dma_en; 
    stData.bits.ds_out2_g_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_g_ch_dma_en; 
    stData.bits.ds_out2_b_ch_dma_en 	= pstDs2DMAEnCtl->ds_out2_b_ch_dma_en; 
    stData.bits.ds2_osd0_ch_dma_en 		= pstDs2DMAEnCtl->ds2_osd0_ch_dma_en;  
    stData.bits.ds2_osd1_ch_dma_en 		= pstDs2DMAEnCtl->ds2_osd1_ch_dma_en;  
 	//stData.u32 = 0xFF1F00F9;
	ISP_WRAP_DRV_SET_WrapDmaEnCtl(apstWrapReg, stData.u32);
	return ;	
}
/*
*3dnr format
*/
static int ISP_DRV_WRAP_Set3DnrFormatCtl(ISP_WRAP_3DNR_PIXEL_FORMAT_CTL_S *pst3DnrFormat)
{
	ISP_CHECK_POINTER(pst3DnrFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_3DNR_WDR_FORMAT_CTL stData;
	stData.u32 = ISP_WRAP_DRV_GET_Wrap3DnrWdrFormatCtl(apstWrapReg);
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
	ISP_WRAP_DRV_SET_Wrap3DnrWdrFormatCtl(apstWrapReg,stData.u32);

	return 0;	
}
/*
*WDR
*/
static int ISP_DRV_WRAP_SetWdrFormatCtl(ISP_WRAP_WDR_PIXEL_FORMAT_CTL_S *pstWdrFormat)
{
	ISP_CHECK_POINTER(pstWdrFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_3DNR_WDR_FORMAT_CTL stData;
	stData.u32 = ISP_WRAP_DRV_GET_Wrap3DnrWdrFormatCtl(apstWrapReg);
	stData.bits.wdr_long_img_format 		= pstWdrFormat->wdr_long_img_format;
	stData.bits.wdr_long_img_out_format 	= pstWdrFormat->wdr_long_img_out_format;
	stData.bits.wdr_long_pixel_width 		= pstWdrFormat->wdr_long_pixel_width;
	stData.bits.wdr_long_yuv422_pxl_order 	= pstWdrFormat->wdr_long_yuv422_pxl_order;
	stData.bits.wdr_long_yuv_in_format 		= pstWdrFormat->wdr_long_yuv_in_format;
	ISP_WRAP_DRV_SET_Wrap3DnrWdrFormatCtl(apstWrapReg,stData.u32);

	return 0;		
}
/*
*DS pixel format
*/
static int ISP_DRV_WRAP_SetMainPixelFormatCtl(ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *pstMainPixelFormat)
{
	ISP_CHECK_POINTER(pstMainPixelFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = 0;
    stData.bits.main_out_img_format = pstMainPixelFormat->main_out_img_format;   
    stData.bits.main_out_yuv_in_format = pstMainPixelFormat->main_out_yuv_in_format;   
    stData.bits.main_out_img_out_format = pstMainPixelFormat->main_out_img_out_format;  
    stData.bits.main_out_yuv422_pxl_order = pstMainPixelFormat->main_out_yuv422_pxl_order;
    stData.bits.main_out_pixel_width = pstMainPixelFormat->main_out_pixel_width; 
	//stData.u32 = 0x04050505;
	ISP_WRAP_DRV_SET_WrapPixelFormatCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetDs0PixelFormatCtl(ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *pstDs0PixelFormat)
{
	ISP_CHECK_POINTER(pstDs0PixelFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapPixelFormatCtl(apstWrapReg);
    stData.bits.ds0_out_img_format = pstDs0PixelFormat->ds0_out_img_format;   
    stData.bits.ds0_out_yuv_in_format = pstDs0PixelFormat->ds0_out_yuv_in_format;
    stData.bits.ds0_out_img_out_format = pstDs0PixelFormat->ds0_out_img_out_format;   
    stData.bits.ds0_out_yuv422_pxl_order = pstDs0PixelFormat->ds0_out_yuv422_pxl_order; 
    stData.bits.ds0_out_pixel_width = pstDs0PixelFormat->ds0_out_pixel_width;    
	//stData.u32 = 0x04050505;
	ISP_WRAP_DRV_SET_WrapPixelFormatCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetDs1PixelFormatCtl(ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *pstDs1PixelFormat)
{
	ISP_CHECK_POINTER(pstDs1PixelFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapPixelFormatCtl(apstWrapReg);
    stData.bits.ds1_out_img_format = pstDs1PixelFormat->ds1_out_img_format;  
    stData.bits.ds1_out_yuv_in_format = pstDs1PixelFormat->ds1_out_yuv_in_format;
    stData.bits.ds1_out_img_out_format = pstDs1PixelFormat->ds1_out_img_out_format;   
    stData.bits.ds1_out_yuv422_pxl_order = pstDs1PixelFormat->ds1_out_yuv422_pxl_order; 
    stData.bits.ds1_out_pixel_width = pstDs1PixelFormat->ds1_out_pixel_width;    
	//stData.u32 = 0x04050505;
	ISP_WRAP_DRV_SET_WrapPixelFormatCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetDs2PixelFormatCtl(ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *pstDs2PixelFormat)
{
	ISP_CHECK_POINTER(pstDs2PixelFormat);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	

	U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapPixelFormatCtl(apstWrapReg);
    stData.bits.ds2_out_img_format = pstDs2PixelFormat->ds2_out_img_format;  
    stData.bits.ds2_out_yuv_in_format = pstDs2PixelFormat->ds2_out_yuv_in_format; 
    stData.bits.ds2_out_img_out_format = pstDs2PixelFormat->ds2_out_img_out_format;   
    stData.bits.ds2_out_yuv422_pxl_order = pstDs2PixelFormat->ds2_out_yuv422_pxl_order; 
    stData.bits.ds2_out_pixel_width = pstDs2PixelFormat->ds2_out_pixel_width;    
	//stData.u32 = 0x04050505;
	ISP_WRAP_DRV_SET_WrapPixelFormatCtl(apstWrapReg, stData.u32);
	return 0;
}
/*
*DS out size
*/
static int ISP_DRV_WRAP_SetMainOutSize(ISP_WRAP_MAIN_OUT_SIZE_S *stMainOutSize)
{
	ISP_CHECK_POINTER(stMainOutSize);	

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_MAIN_OUT_SIZE stMainData;
	stMainData.u32 = 0;
	stMainData.bits.main_out_v_size = stMainOutSize->main_out_v_size;   
	stMainData.bits.main_out_h_size = stMainOutSize->main_out_h_size;    
	ISP_WRAP_DRV_SET_WrapMainOutSize(apstWrapReg, stMainData.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDs0OutSize(ISP_WRAP_DS0_OUT_SIZE_S *stDs0OutSize)
{
	ISP_CHECK_POINTER(stDs0OutSize);	

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS0_OUT_SIZE stDS0Data;
	stDS0Data.u32 = 0;
	stDS0Data.bits.ds0_out_v_size = stDs0OutSize->ds0_out_v_size;   
	stDS0Data.bits.ds0_out_h_size = stDs0OutSize->ds0_out_h_size;    
	ISP_WRAP_DRV_SET_WrapDs0OutSize(apstWrapReg, stDS0Data.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDs1OutSize(ISP_WRAP_DS1_OUT_SIZE_S *stDs1OutSize)
{
	ISP_CHECK_POINTER(stDs1OutSize);	

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS1_OUT_SIZE stDS1Data;
	stDS1Data.u32 = 0;
	stDS1Data.bits.ds1_out_v_size = stDs1OutSize->ds1_out_v_size;   
	stDS1Data.bits.ds1_out_h_size = stDs1OutSize->ds1_out_h_size;    
	ISP_WRAP_DRV_SET_WrapDs1OutSize(apstWrapReg, stDS1Data.u32);

	return 0;	
}

static int ISP_DRV_WRAP_SetDs2OutSize(ISP_WRAP_DS2_OUT_SIZE_S *stDs2OutSize)
{
	ISP_CHECK_POINTER(stDs2OutSize);	

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS2_OUT_SIZE stDS2Data;
	stDS2Data.u32 = 0;
	stDS2Data.bits.ds2_out_v_size = stDs2OutSize->ds2_out_v_size;   
	stDS2Data.bits.ds2_out_h_size = stDs2OutSize->ds2_out_h_size;    
	ISP_WRAP_DRV_SET_WrapDs2OutSize(apstWrapReg, stDS2Data.u32);	
	return 0;
}
/*
*DMA
 */
static int ISP_DRV_WRAP_SetDmaMode(ISP_WRAP_DMA_MODE_S *pstDmaMode)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;

	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);	
	ISP_CHECK_POINTER(pstDmaMode);

	U_ISP_WRAP_DMA_ARB_MODE stArbMode;
	stArbMode.u32 = 0;
	stArbMode.bits.isp_dma_wr_arb_mode = pstDmaMode->wr_dma_arb_mode;   
	stArbMode.bits.isp_dma_rd_arb_mode = pstDmaMode->wr_dma_arb_mode;    
	ISP_WRAP_DRV_SET_WrapDmaArbMode(apstWrapReg, stArbMode.u32);

	U_ISP_WRAP_DMA_WR_WEIGHT_0 stWrWeight0;
	stWrWeight0.u32 = 0;
	stWrWeight0.bits.isp_dma_ch0_wr_weight = pstDmaMode->wr_dma_ch_weight[0];   
	stWrWeight0.bits.isp_dma_ch1_wr_weight = pstDmaMode->wr_dma_ch_weight[1];   
	stWrWeight0.bits.isp_dma_ch2_wr_weight = pstDmaMode->wr_dma_ch_weight[2];   
	stWrWeight0.bits.isp_dma_ch3_wr_weight = pstDmaMode->wr_dma_ch_weight[3];   
	ISP_WRAP_DRV_SET_WrapDmaWrWeight0(apstWrapReg, stWrWeight0.u32);

	U_ISP_WRAP_DMA_WR_WEIGHT_1 stWrWeight1;
	stWrWeight1.u32 = 0;
	stWrWeight1.bits.isp_dma_ch4_wr_weight = pstDmaMode->wr_dma_ch_weight[4];   
	stWrWeight1.bits.isp_dma_ch5_wr_weight = pstDmaMode->wr_dma_ch_weight[5];   
	stWrWeight1.bits.isp_dma_ch6_wr_weight = pstDmaMode->wr_dma_ch_weight[6];   
	stWrWeight1.bits.isp_dma_ch7_wr_weight = pstDmaMode->wr_dma_ch_weight[7];   
	ISP_WRAP_DRV_SET_WrapDmaWrWeight1(apstWrapReg, stWrWeight1.u32);

	U_ISP_WRAP_DMA_WR_WEIGHT_2 stWrWeight2;
	stWrWeight2.u32 = 0;
	stWrWeight2.bits.isp_dma_ch8_wr_weight = pstDmaMode->wr_dma_ch_weight[8];   
	stWrWeight2.bits.isp_dma_ch9_wr_weight = pstDmaMode->wr_dma_ch_weight[9];   
	stWrWeight2.bits.isp_dma_ch10_wr_weight = pstDmaMode->wr_dma_ch_weight[10];   
	stWrWeight2.bits.isp_dma_ch11_wr_weight = pstDmaMode->wr_dma_ch_weight[11];  
	ISP_WRAP_DRV_SET_WrapDmaWrWeight2(apstWrapReg, stWrWeight2.u32);

	U_ISP_WRAP_DMA_WR_WEIGHT_3 stWrWeight3;
	stWrWeight3.u32 = 0;
	stWrWeight3.bits.isp_dma_ch12_wr_weight = pstDmaMode->wr_dma_ch_weight[12];   
	stWrWeight3.bits.isp_dma_ch13_wr_weight = pstDmaMode->wr_dma_ch_weight[13];   
	stWrWeight3.bits.isp_dma_ch14_wr_weight = pstDmaMode->wr_dma_ch_weight[14];   
	stWrWeight3.bits.isp_dma_ch15_wr_weight = pstDmaMode->wr_dma_ch_weight[15]; 
	ISP_WRAP_DRV_SET_WrapDmaWrWeight3(apstWrapReg, stWrWeight3.u32);

	U_ISP_WRAP_DMA_RD_WEIGHT_0 stRdWeight0;
	stRdWeight0.u32 = 0;
	stRdWeight0.bits.isp_dma_ch0_rd_weight = pstDmaMode->rd_dma_ch_weight[0];   
	stRdWeight0.bits.isp_dma_ch1_rd_weight = pstDmaMode->rd_dma_ch_weight[1];   
	stRdWeight0.bits.isp_dma_ch2_rd_weight = pstDmaMode->rd_dma_ch_weight[2];   
	stRdWeight0.bits.isp_dma_ch3_rd_weight = pstDmaMode->rd_dma_ch_weight[3];   
	ISP_WRAP_DRV_SET_WrapDmaRdWeight0(apstWrapReg, stRdWeight0.u32);

	U_ISP_WRAP_DMA_RD_WEIGHT_1 stRdWeight1;
	stRdWeight1.u32 = 0;
	stRdWeight1.bits.isp_dma_ch4_rd_weight = pstDmaMode->rd_dma_ch_weight[4];   
	stRdWeight1.bits.isp_dma_ch5_rd_weight = pstDmaMode->rd_dma_ch_weight[5];   
	stRdWeight1.bits.isp_dma_ch6_rd_weight = pstDmaMode->rd_dma_ch_weight[6];   
	stRdWeight1.bits.isp_dma_ch7_rd_weight = pstDmaMode->rd_dma_ch_weight[7];   
	ISP_WRAP_DRV_SET_WrapDmaRdWeight1(apstWrapReg, stRdWeight1.u32);

	U_ISP_WRAP_DMA_RD_WEIGHT_2 stRdWeight2;
	stRdWeight2.u32 = 0;
	stRdWeight2.bits.isp_dma_ch8_rd_weight = pstDmaMode->rd_dma_ch_weight[8];   
	stRdWeight2.bits.isp_dma_ch9_rd_weight = pstDmaMode->rd_dma_ch_weight[9];   
	stRdWeight2.bits.isp_dma_ch10_rd_weight = pstDmaMode->rd_dma_ch_weight[10];   
	stRdWeight2.bits.isp_dma_ch11_rd_weight = pstDmaMode->rd_dma_ch_weight[11];  
	ISP_WRAP_DRV_SET_WrapDmaRdWeight2(apstWrapReg, stRdWeight2.u32);	

	U_ISP_WRAP_DMA_RD_WEIGHT_3 stRdWeight3;
	stRdWeight3.u32 = 0;
	stRdWeight3.bits.isp_dma_ch12_rd_weight = pstDmaMode->rd_dma_ch_weight[12];   
	stRdWeight3.bits.isp_dma_ch13_rd_weight = pstDmaMode->rd_dma_ch_weight[13];   
	stRdWeight3.bits.isp_dma_ch14_rd_weight = pstDmaMode->rd_dma_ch_weight[14];   
	stRdWeight3.bits.isp_dma_ch15_rd_weight = pstDmaMode->rd_dma_ch_weight[15]; 
	ISP_WRAP_DRV_SET_WrapDmaRdWeight3(apstWrapReg, stRdWeight3.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaWrPriority0(apstWrapReg, stWrPriority0.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaWrPriority1(apstWrapReg, stWrPriority1.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaRdPriority0(apstWrapReg, stRdPriority0.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaRdPriority1(apstWrapReg, stRdPriority1.u32);

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
	ISP_WRAP_DRV_SET_DmaWrChId0(apstWrapReg, stWrChId0.u32);

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
	ISP_WRAP_DRV_SET_DmaWrChId1(apstWrapReg, stWrChId1.u32);

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
	ISP_WRAP_DRV_SET_DmaRdChId0(apstWrapReg, stRdChId0.u32);

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
	ISP_WRAP_DRV_SET_DmaRdChId1(apstWrapReg, stRdChId1.u32);	
	return 0;
}

static int ISP_DRV_WRAP_SetDmaCfgMode(ISP_WRAP_DMA_CFG_S *pstDmaCfg)
{
	ISP_CHECK_POINTER(pstDmaCfg);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

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
	ISP_WRAP_DRV_SET_WrapDmaCh0Cfg(apstWrapReg, stDmaCfg0.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh1Cfg(apstWrapReg, stDmaCfg1.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh2Cfg(apstWrapReg, stDmaCfg2.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh3Cfg(apstWrapReg, stDmaCfg3.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh4Cfg(apstWrapReg, stDmaCfg4.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh5Cfg(apstWrapReg, stDmaCfg5.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh6Cfg(apstWrapReg, stDmaCfg6.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh7Cfg(apstWrapReg, stDmaCfg7.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh8Cfg(apstWrapReg, stDmaCfg8.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh9Cfg(apstWrapReg, stDmaCfg9.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh10Cfg(apstWrapReg, stDmaCfg10.u32);	

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
	ISP_WRAP_DRV_SET_WrapDmaCh11Cfg(apstWrapReg, stDmaCfg11.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh12Cfg(apstWrapReg, stDmaCfg12.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh13Cfg(apstWrapReg, stDmaCfg13.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh14Cfg(apstWrapReg, stDmaCfg14.u32);

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
	ISP_WRAP_DRV_SET_WrapDmaCh15Cfg(apstWrapReg, stDmaCfg15.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDmaErrDecCfg(ISP_WRAP_DMA_ERR_DEC_CFG_S *pstDmaErrDec)
{
	ISP_CHECK_POINTER(pstDmaErrDec);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_CH0_ERR_DEC_CFG stDmaCfg0;	
	stDmaCfg0.u32 = 0;
	stDmaCfg0.bits.ch0_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[0].wr_err_dec_unit;
	stDmaCfg0.bits.ch0_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[0].rd_err_dec_unit;
	stDmaCfg0.bits.ch0_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[0].wr_err_gen_thr;
	stDmaCfg0.bits.ch0_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[0].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh0ErrDecCfg(apstWrapReg, stDmaCfg0.u32);

	U_ISP_WRAP_DMA_CH1_ERR_DEC_CFG stDmaCfg1;
	stDmaCfg1.u32 = 0;
	stDmaCfg1.bits.ch1_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[1].wr_err_dec_unit;
	stDmaCfg1.bits.ch1_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[1].rd_err_dec_unit;
	stDmaCfg1.bits.ch1_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[1].wr_err_gen_thr;
	stDmaCfg1.bits.ch1_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[1].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh1ErrDecCfg(apstWrapReg, stDmaCfg1.u32);

	U_ISP_WRAP_DMA_CH2_ERR_DEC_CFG stDmaCfg2;
	stDmaCfg2.u32 = 0;
	stDmaCfg2.bits.ch2_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[2].wr_err_dec_unit;
	stDmaCfg2.bits.ch2_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[2].rd_err_dec_unit;
	stDmaCfg2.bits.ch2_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[2].wr_err_gen_thr;
	stDmaCfg2.bits.ch2_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[2].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh2ErrDecCfg(apstWrapReg, stDmaCfg2.u32);

	U_ISP_WRAP_DMA_CH3_ERR_DEC_CFG stDmaCfg3;
	stDmaCfg3.u32 = 0;
	stDmaCfg3.bits.ch3_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[3].wr_err_dec_unit;
	stDmaCfg3.bits.ch3_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[3].rd_err_dec_unit;
	stDmaCfg3.bits.ch3_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[3].wr_err_gen_thr;
	stDmaCfg3.bits.ch3_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[3].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh3ErrDecCfg(apstWrapReg, stDmaCfg3.u32);

	U_ISP_WRAP_DMA_CH4_ERR_DEC_CFG stDmaCfg4;
	stDmaCfg4.u32 = 0;
	stDmaCfg4.bits.ch4_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[4].wr_err_dec_unit;
	stDmaCfg4.bits.ch4_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[4].rd_err_dec_unit;
	stDmaCfg4.bits.ch4_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[4].wr_err_gen_thr;
	stDmaCfg4.bits.ch4_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[4].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh4ErrDecCfg(apstWrapReg, stDmaCfg4.u32);

	U_ISP_WRAP_DMA_CH5_ERR_DEC_CFG stDmaCfg5;
	stDmaCfg5.u32 = 0;
	stDmaCfg5.bits.ch5_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[5].wr_err_dec_unit;
	stDmaCfg5.bits.ch5_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[5].rd_err_dec_unit;
	stDmaCfg5.bits.ch5_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[5].wr_err_gen_thr;
	stDmaCfg5.bits.ch5_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[5].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh5ErrDecCfg(apstWrapReg, stDmaCfg5.u32);

	U_ISP_WRAP_DMA_CH6_ERR_DEC_CFG stDmaCfg6;
	stDmaCfg6.u32 = 0;
	stDmaCfg6.bits.ch6_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[6].wr_err_dec_unit;
	stDmaCfg6.bits.ch6_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[6].rd_err_dec_unit;
	stDmaCfg6.bits.ch6_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[6].wr_err_gen_thr;
	stDmaCfg6.bits.ch6_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[6].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh6ErrDecCfg(apstWrapReg, stDmaCfg6.u32);

	U_ISP_WRAP_DMA_CH7_ERR_DEC_CFG stDmaCfg7;
	stDmaCfg7.u32 = 0;
	stDmaCfg7.bits.ch7_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[7].wr_err_dec_unit;
	stDmaCfg7.bits.ch7_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[7].rd_err_dec_unit;
	stDmaCfg7.bits.ch7_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[7].wr_err_gen_thr;
	stDmaCfg7.bits.ch7_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[7].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh7ErrDecCfg(apstWrapReg, stDmaCfg7.u32);

	U_ISP_WRAP_DMA_CH8_ERR_DEC_CFG stDmaCfg8;
	stDmaCfg8.u32 = 0;
	stDmaCfg8.bits.ch8_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[8].wr_err_dec_unit;
	stDmaCfg8.bits.ch8_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[8].rd_err_dec_unit;
	stDmaCfg8.bits.ch8_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[8].wr_err_gen_thr;
	stDmaCfg8.bits.ch8_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[8].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh8ErrDecCfg(apstWrapReg, stDmaCfg8.u32);

	U_ISP_WRAP_DMA_CH9_ERR_DEC_CFG stDmaCfg9;
	stDmaCfg9.u32 = 0;
	stDmaCfg9.bits.ch9_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[9].wr_err_dec_unit;
	stDmaCfg9.bits.ch9_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[9].rd_err_dec_unit;
	stDmaCfg9.bits.ch9_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[9].wr_err_gen_thr;
	stDmaCfg9.bits.ch9_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[9].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh9ErrDecCfg(apstWrapReg, stDmaCfg9.u32);
	
	U_ISP_WRAP_DMA_CH10_ERR_DEC_CFG stDmaCfg10;	
	stDmaCfg10.u32 = 0;
	stDmaCfg10.bits.ch10_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[10].wr_err_dec_unit;
	stDmaCfg10.bits.ch10_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[10].rd_err_dec_unit;
	stDmaCfg10.bits.ch10_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[10].wr_err_gen_thr;
	stDmaCfg10.bits.ch10_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[10].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh10ErrDecCfg(apstWrapReg, stDmaCfg10.u32);

	U_ISP_WRAP_DMA_CH11_ERR_DEC_CFG stDmaCfg11;
	stDmaCfg11.u32 = 0;
	stDmaCfg11.bits.ch11_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[11].wr_err_dec_unit;
	stDmaCfg11.bits.ch11_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[11].rd_err_dec_unit;
	stDmaCfg11.bits.ch11_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[11].wr_err_gen_thr;
	stDmaCfg11.bits.ch11_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[11].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh11ErrDecCfg(apstWrapReg, stDmaCfg11.u32);
	
	U_ISP_WRAP_DMA_CH12_ERR_DEC_CFG stDmaCfg12;
	stDmaCfg12.u32 = 0;
	stDmaCfg12.bits.ch12_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[12].wr_err_dec_unit;
	stDmaCfg12.bits.ch12_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[12].rd_err_dec_unit;
	stDmaCfg12.bits.ch12_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[12].wr_err_gen_thr;
	stDmaCfg12.bits.ch12_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[12].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh12ErrDecCfg(apstWrapReg, stDmaCfg12.u32);	

	U_ISP_WRAP_DMA_CH13_ERR_DEC_CFG stDmaCfg13;
	stDmaCfg13.u32 = 0;
	stDmaCfg13.bits.ch13_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[13].wr_err_dec_unit;
	stDmaCfg13.bits.ch13_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[13].rd_err_dec_unit;
	stDmaCfg13.bits.ch13_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[13].wr_err_gen_thr;
	stDmaCfg13.bits.ch13_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[13].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh13ErrDecCfg(apstWrapReg, stDmaCfg13.u32);

	U_ISP_WRAP_DMA_CH14_ERR_DEC_CFG stDmaCfg14;
	stDmaCfg14.u32 = 0;
	stDmaCfg14.bits.ch14_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[14].wr_err_dec_unit;
	stDmaCfg14.bits.ch14_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[14].rd_err_dec_unit;
	stDmaCfg14.bits.ch14_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[14].wr_err_gen_thr;
	stDmaCfg14.bits.ch14_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[14].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh14ErrDecCfg(apstWrapReg, stDmaCfg14.u32);	

	U_ISP_WRAP_DMA_CH15_ERR_DEC_CFG stDmaCfg15;
	stDmaCfg15.u32 = 0;
	stDmaCfg15.bits.ch15_wr_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[15].wr_err_dec_unit;
	stDmaCfg15.bits.ch15_rd_err_dec_unit = pstDmaErrDec->stDmaChErrDecCfg[15].rd_err_dec_unit;
	stDmaCfg15.bits.ch15_wr_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[15].wr_err_gen_thr;
	stDmaCfg15.bits.ch15_rd_err_gen_thr = pstDmaErrDec->stDmaChErrDecCfg[15].rd_err_gen_thr;
	ISP_WRAP_DRV_SET_WrapDmaCh15ErrDecCfg(apstWrapReg, stDmaCfg15.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDmaErrStatus(ISP_WRAP_DMA_ERR_STATUS_S *pstErrStatus)
{
	ISP_CHECK_POINTER(pstErrStatus);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DMA_CH0_ERR_STATUS stDmaCfg0;	
	stDmaCfg0.u32 = 0;
	stDmaCfg0.bits.ch0_err_y_wr_status = pstErrStatus->stDmaErrStatus[0].err_y_wr_status;
	stDmaCfg0.bits.ch0_err_uv_wr_status = pstErrStatus->stDmaErrStatus[0].err_uv_wr_status;
	stDmaCfg0.bits.ch0_err_raw_read_status = pstErrStatus->stDmaErrStatus[0].err_raw_read_status;
	stDmaCfg0.bits.ch0_err_wr_rst_req = pstErrStatus->stDmaErrStatus[0].err_wr_rst_req;
	stDmaCfg0.bits.ch0_err_rd_rst_req = pstErrStatus->stDmaErrStatus[0].err_rd_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh0ErrStatus(apstWrapReg, stDmaCfg0.u32);

	U_ISP_WRAP_DMA_CH1_ERR_STATUS stDmaCfg1;
	stDmaCfg1.u32 = 0;
	stDmaCfg1.bits.ch1_err_y_wr_status = pstErrStatus->stDmaErrStatus[1].err_y_wr_status;
	stDmaCfg1.bits.ch1_err_uv_wr_status = pstErrStatus->stDmaErrStatus[1].err_uv_wr_status;
	stDmaCfg1.bits.ch1_err_raw_read_status = pstErrStatus->stDmaErrStatus[1].err_raw_read_status;
	stDmaCfg1.bits.ch1_err_wr_rst_req = pstErrStatus->stDmaErrStatus[1].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh1ErrStatus(apstWrapReg, stDmaCfg1.u32);

	U_ISP_WRAP_DMA_CH2_ERR_STATUS stDmaCfg2;
	stDmaCfg2.u32 = 0;
	stDmaCfg2.bits.ch2_err_y_wr_status = pstErrStatus->stDmaErrStatus[2].err_y_wr_status;
	stDmaCfg2.bits.ch2_err_uv_wr_status = pstErrStatus->stDmaErrStatus[2].err_uv_wr_status;
	stDmaCfg2.bits.ch2_err_raw_read_status = pstErrStatus->stDmaErrStatus[2].err_raw_read_status;
	stDmaCfg2.bits.ch2_err_wr_rst_req = pstErrStatus->stDmaErrStatus[2].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh2ErrStatus(apstWrapReg, stDmaCfg2.u32);

	U_ISP_WRAP_DMA_CH3_ERR_STATUS stDmaCfg3;	
	stDmaCfg3.u32 = 0;
	stDmaCfg3.bits.ch3_err_y_wr_status = pstErrStatus->stDmaErrStatus[3].err_y_wr_status;
	stDmaCfg3.bits.ch3_err_uv_wr_status = pstErrStatus->stDmaErrStatus[3].err_uv_wr_status;
	stDmaCfg3.bits.ch3_err_raw_read_status = pstErrStatus->stDmaErrStatus[3].err_raw_read_status;
	stDmaCfg3.bits.ch3_err_wr_rst_req = pstErrStatus->stDmaErrStatus[3].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh3ErrStatus(apstWrapReg, stDmaCfg3.u32);

	U_ISP_WRAP_DMA_CH4_ERR_STATUS stDmaCfg4;
	stDmaCfg4.u32 = 0;
	stDmaCfg4.bits.ch4_err_y_wr_status = pstErrStatus->stDmaErrStatus[4].err_y_wr_status;
	stDmaCfg4.bits.ch4_err_uv_wr_status = pstErrStatus->stDmaErrStatus[4].err_uv_wr_status;
	stDmaCfg4.bits.ch4_err_raw_read_status = pstErrStatus->stDmaErrStatus[4].err_raw_read_status;
	stDmaCfg4.bits.ch4_err_wr_rst_req = pstErrStatus->stDmaErrStatus[4].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh4ErrStatus(apstWrapReg, stDmaCfg4.u32);

	U_ISP_WRAP_DMA_CH5_ERR_STATUS stDmaCfg5;
	stDmaCfg5.u32 = 0;
	stDmaCfg5.bits.ch5_err_y_wr_status = pstErrStatus->stDmaErrStatus[5].err_y_wr_status;
	stDmaCfg5.bits.ch5_err_uv_wr_status = pstErrStatus->stDmaErrStatus[5].err_uv_wr_status;
	stDmaCfg5.bits.ch5_err_raw_read_status = pstErrStatus->stDmaErrStatus[5].err_raw_read_status;
	stDmaCfg5.bits.ch5_err_wr_rst_req = pstErrStatus->stDmaErrStatus[5].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh5ErrStatus(apstWrapReg, stDmaCfg5.u32);

	U_ISP_WRAP_DMA_CH6_ERR_STATUS stDmaCfg6;
	stDmaCfg6.u32 = 0;
	stDmaCfg6.bits.ch6_err_y_wr_status = pstErrStatus->stDmaErrStatus[6].err_y_wr_status;
	stDmaCfg6.bits.ch6_err_uv_wr_status = pstErrStatus->stDmaErrStatus[6].err_uv_wr_status;
	stDmaCfg6.bits.ch6_err_raw_read_status = pstErrStatus->stDmaErrStatus[6].err_raw_read_status;
	stDmaCfg6.bits.ch6_err_wr_rst_req = pstErrStatus->stDmaErrStatus[6].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh6ErrStatus(apstWrapReg, stDmaCfg6.u32);

	U_ISP_WRAP_DMA_CH7_ERR_STATUS stDmaCfg7;
	stDmaCfg7.u32 = 0;
	stDmaCfg7.bits.ch7_err_y_wr_status = pstErrStatus->stDmaErrStatus[7].err_y_wr_status;
	stDmaCfg7.bits.ch7_err_uv_wr_status = pstErrStatus->stDmaErrStatus[7].err_uv_wr_status;
	stDmaCfg7.bits.ch7_err_raw_read_status = pstErrStatus->stDmaErrStatus[7].err_raw_read_status;
	stDmaCfg7.bits.ch7_err_wr_rst_req = pstErrStatus->stDmaErrStatus[7].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh7ErrStatus(apstWrapReg, stDmaCfg7.u32);

	U_ISP_WRAP_DMA_CH8_ERR_STATUS stDmaCfg8;
	stDmaCfg8.u32 = 0;
	stDmaCfg8.bits.ch8_err_y_wr_status = pstErrStatus->stDmaErrStatus[8].err_y_wr_status;
	stDmaCfg8.bits.ch8_err_uv_wr_status = pstErrStatus->stDmaErrStatus[8].err_uv_wr_status;
	stDmaCfg8.bits.ch8_err_raw_read_status = pstErrStatus->stDmaErrStatus[8].err_raw_read_status;
	stDmaCfg8.bits.ch8_err_wr_rst_req = pstErrStatus->stDmaErrStatus[8].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh8ErrStatus(apstWrapReg, stDmaCfg8.u32);

	U_ISP_WRAP_DMA_CH9_ERR_STATUS stDmaCfg9;
	stDmaCfg9.u32 = 0;
	stDmaCfg9.bits.ch9_err_y_wr_status = pstErrStatus->stDmaErrStatus[9].err_y_wr_status;
	stDmaCfg9.bits.ch9_err_uv_wr_status = pstErrStatus->stDmaErrStatus[9].err_uv_wr_status;
	stDmaCfg9.bits.ch9_err_raw_read_status = pstErrStatus->stDmaErrStatus[9].err_raw_read_status;
	stDmaCfg9.bits.ch9_err_wr_rst_req = pstErrStatus->stDmaErrStatus[9].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh9ErrStatus(apstWrapReg, stDmaCfg9.u32);
	
	U_ISP_WRAP_DMA_CH10_ERR_STATUS stDmaCfg10;
	stDmaCfg10.u32 = 0;
	stDmaCfg10.bits.ch10_err_y_wr_status = pstErrStatus->stDmaErrStatus[10].err_y_wr_status;
	stDmaCfg10.bits.ch10_err_uv_wr_status = pstErrStatus->stDmaErrStatus[10].err_uv_wr_status;
	stDmaCfg10.bits.ch10_err_raw_read_status = pstErrStatus->stDmaErrStatus[10].err_raw_read_status;
	stDmaCfg10.bits.ch10_err_wr_rst_req = pstErrStatus->stDmaErrStatus[10].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh10ErrStatus(apstWrapReg, stDmaCfg10.u32);

	U_ISP_WRAP_DMA_CH11_ERR_STATUS stDmaCfg11;
	stDmaCfg11.u32 = 0;
	stDmaCfg11.bits.ch11_err_y_wr_status = pstErrStatus->stDmaErrStatus[11].err_y_wr_status;
	stDmaCfg11.bits.ch11_err_uv_wr_status = pstErrStatus->stDmaErrStatus[11].err_uv_wr_status;
	stDmaCfg11.bits.ch11_err_raw_read_status = pstErrStatus->stDmaErrStatus[11].err_raw_read_status;
	stDmaCfg11.bits.ch11_err_wr_rst_req = pstErrStatus->stDmaErrStatus[11].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh11ErrStatus(apstWrapReg, stDmaCfg11.u32);	

	U_ISP_WRAP_DMA_CH12_ERR_STATUS stDmaCfg12;
	stDmaCfg12.u32 = 0;
	stDmaCfg12.bits.ch12_err_y_wr_status = pstErrStatus->stDmaErrStatus[12].err_y_wr_status;
	stDmaCfg12.bits.ch12_err_uv_wr_status = pstErrStatus->stDmaErrStatus[12].err_uv_wr_status;
	stDmaCfg12.bits.ch12_err_raw_read_status = pstErrStatus->stDmaErrStatus[12].err_raw_read_status;
	stDmaCfg12.bits.ch12_err_wr_rst_req = pstErrStatus->stDmaErrStatus[12].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh12ErrStatus(apstWrapReg, stDmaCfg12.u32);

	U_ISP_WRAP_DMA_CH13_ERR_STATUS stDmaCfg13;
	stDmaCfg13.u32 = 0;
	stDmaCfg13.bits.ch13_err_y_wr_status = pstErrStatus->stDmaErrStatus[13].err_y_wr_status;
	stDmaCfg13.bits.ch13_err_uv_wr_status = pstErrStatus->stDmaErrStatus[13].err_uv_wr_status;
	stDmaCfg13.bits.ch13_err_raw_read_status = pstErrStatus->stDmaErrStatus[13].err_raw_read_status;
	stDmaCfg13.bits.ch13_err_wr_rst_req = pstErrStatus->stDmaErrStatus[13].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh13ErrStatus(apstWrapReg, stDmaCfg13.u32);

	U_ISP_WRAP_DMA_CH14_ERR_STATUS stDmaCfg14;
	stDmaCfg14.u32 = 0;
	stDmaCfg14.bits.ch14_err_y_wr_status = pstErrStatus->stDmaErrStatus[14].err_y_wr_status;
	stDmaCfg14.bits.ch14_err_uv_wr_status = pstErrStatus->stDmaErrStatus[14].err_uv_wr_status;
	stDmaCfg14.bits.ch14_err_raw_read_status = pstErrStatus->stDmaErrStatus[14].err_raw_read_status;
	stDmaCfg14.bits.ch14_err_wr_rst_req = pstErrStatus->stDmaErrStatus[14].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh14ErrStatus(apstWrapReg, stDmaCfg14.u32);	

	U_ISP_WRAP_DMA_CH15_ERR_STATUS stDmaCfg15;
	stDmaCfg15.u32 = 0;
	stDmaCfg15.bits.ch15_err_y_wr_status = pstErrStatus->stDmaErrStatus[15].err_y_wr_status;
	stDmaCfg15.bits.ch15_err_uv_wr_status = pstErrStatus->stDmaErrStatus[15].err_uv_wr_status;
	stDmaCfg15.bits.ch15_err_raw_read_status = pstErrStatus->stDmaErrStatus[15].err_raw_read_status;
	stDmaCfg15.bits.ch15_err_wr_rst_req = pstErrStatus->stDmaErrStatus[15].err_wr_rst_req;
	ISP_WRAP_DRV_SET_WrapDmaCh15ErrStatus(apstWrapReg, stDmaCfg15.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDma(ISP_WRAP_DMA_ATTR_S *pstDmaAttr)
{
	ISP_CHECK_POINTER(pstDmaAttr);

	ISP_WRAP_DMA_MODE_S *pstDmaMode = &(pstDmaAttr->stDmaChMode);
	ISP_DRV_WRAP_SetDmaMode(pstDmaMode);

	ISP_WRAP_DMA_CFG_S *pstDmaCfg = &(pstDmaAttr->stDmaCfg);
	ISP_DRV_WRAP_SetDmaCfgMode(pstDmaCfg);

	ISP_WRAP_DMA_ERR_DEC_CFG_S *pstDmaErrDec = &(pstDmaAttr->stErrDecCfg);
	ISP_DRV_WRAP_SetDmaErrDecCfg(pstDmaErrDec);

	ISP_WRAP_DMA_ERR_STATUS_S *pstErrStatus = &(pstDmaAttr->stErrStatus);
	ISP_DRV_WRAP_SetDmaErrStatus(pstErrStatus);

	return 0;
}
/*
*buf
*/
static int ISP_DRV_WRAP_SetwdrBuf(ISP_WRAP_WDR_BUF_S *pstWdrBuf)
{
	ISP_CHECK_POINTER(pstWdrBuf);
	
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);
	unsigned int u32Data = 0;

	u32Data = 0x00F80000;
	ISP_WRAP_DRV_SET_WrapWdrLongBufBase(apstWrapReg, u32Data);
	//0x21
	u32Data = 0x00011000;
	ISP_WRAP_DRV_SET_WrapWdrLongSizeCfg(apstWrapReg, u32Data);

	return 0;	
}

static int ISP_DRV_WRAP_Set3dnrBuf(ISP_WRAP_3DNR_BUF_S *pst3dnrBuf)
{
	ISP_CHECK_POINTER(pst3dnrBuf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_3DNR_Y_BUF_BASE stYbufBase;
	stYbufBase.u32 = 0;
	stYbufBase.bits.y_3dnr_buf_base = pst3dnrBuf->y_3dnr_buf_base;
	ISP_WRAP_DRV_SET_Wrap3DnrYBufBase(apstWrapReg, stYbufBase.u32);

	U_ISP_WRAP_3DNR_UV_BUF_BASE stUvbufBase;
	stUvbufBase.u32 = 0;
	stUvbufBase.bits.uv_3dnr_buf_base = pst3dnrBuf->uv_3dnr_buf_base;
	ISP_WRAP_DRV_SET_Wrap3DnrUvBufBase(apstWrapReg, stUvbufBase.u32);

	U_ISP_WRAP_3DNR_STRIDE stStride;
	stStride.u32 = 0;
	stStride.bits.y_3dnr_line_stride = pst3dnrBuf->y_3dnr_line_stride;
	stStride.bits.uv_3dnr_line_stride = pst3dnrBuf->uv_3dnr_line_stride;
	ISP_WRAP_DRV_SET_Wrap3DnrStride(apstWrapReg, stStride.u32);
	
	return 0;
}

static int ISP_DRV_WRAP_SetLdcBuf(ISP_WRAP_LDC_BUF_S *pstLdcBuf)
{
	ISP_CHECK_POINTER(pstLdcBuf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);


	U_ISP_WRAP_LDC_Y_BUF_BASE stYbufBase;
	stYbufBase.u32 = 0;
	stYbufBase.bits.ldc_y_buf_base = pstLdcBuf->ldc_y_buf_base;
	ISP_WRAP_DRV_SET_WrapLdcYBufBase(apstWrapReg, stYbufBase.u32);

	U_ISP_WRAP_LDC_UV_BUF_BASE stUvbufBase;
	stUvbufBase.u32 = 0;
	stUvbufBase.bits.ldc_uv_buf_base = pstLdcBuf->ldc_uv_buf_base;
	ISP_WRAP_DRV_SET_WrapLdcUvBufBase(apstWrapReg, stUvbufBase.u32);

	U_ISP_WRAP_LDC_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ldc_y_line_stride = pstLdcBuf->ldc_y_line_stride;
	stStride.bits.ldc_uv_line_stride = pstLdcBuf->ldc_uv_line_stride;
	ISP_WRAP_DRV_SET_WrapLdcStride(apstWrapReg, stStride.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetMainBuf(ISP_WRAP_MAIN_BUF_S *pstMainBuf)
{
	ISP_CHECK_POINTER(pstMainBuf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_MAIN_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.main_y_buf0_base = pstMainBuf->main_y_buf0_base;
	ISP_WRAP_DRV_SET_WrapMainYBuf0Base(apstWrapReg, stYbufBase0.u32);

	U_ISP_WRAP_MAIN_Y_BUF1_BASE stYbufBase1;		
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.main_y_buf1_base = pstMainBuf->main_y_buf1_base;
	ISP_WRAP_DRV_SET_WrapMainYBuf1Base(apstWrapReg, stYbufBase1.u32);

	U_ISP_WRAP_MAIN_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.main_uv_buf0_base = pstMainBuf->main_uv_buf0_base;
	ISP_WRAP_DRV_SET_WrapMainUvBuf0Base(apstWrapReg, stUvbufBase0.u32);

	U_ISP_WRAP_MAIN_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.main_uv_buf1_base = pstMainBuf->main_uv_buf1_base;
	ISP_WRAP_DRV_SET_WrapMainUvBuf1Base(apstWrapReg, stUvbufBase1.u32);

	U_ISP_WRAP_MAIN_STRIDE stStride;
	stStride.u32 = 0;
	stStride.bits.main_y_line_stride = pstMainBuf->main_y_line_stride;
	stStride.bits.main_uv_line_stride = pstMainBuf->main_uv_line_stride;
	ISP_WRAP_DRV_SET_WrapMainStride(apstWrapReg, stStride.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDs0Buf(ISP_WRAP_DS0_BUF_S *pstDs0Buf)
{
	ISP_CHECK_POINTER(pstDs0Buf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS0_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.ds0_y_buf0_base = pstDs0Buf->ds0_y_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs0YBuf0Base(apstWrapReg, stYbufBase0.u32);
	
	U_ISP_WRAP_DS0_Y_BUF1_BASE stYbufBase1;
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.ds0_y_buf1_base = pstDs0Buf->ds0_y_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs0YBuf1Base(apstWrapReg, stYbufBase1.u32);

	U_ISP_WRAP_DS0_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.ds0_uv_buf0_base = pstDs0Buf->ds0_uv_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs0UvBuf0Base(apstWrapReg, stUvbufBase0.u32);

	U_ISP_WRAP_DS0_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.ds0_uv_buf1_base = pstDs0Buf->ds0_uv_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs0UvBuf1Base(apstWrapReg, stUvbufBase1.u32);

	U_ISP_WRAP_DS0_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ds0_y_line_stride = pstDs0Buf->ds0_y_line_stride;
	stStride.bits.ds0_uv_line_stride = pstDs0Buf->ds0_uv_line_stride;	
	ISP_WRAP_DRV_SET_WrapDs0Stride(apstWrapReg, stStride.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetDs1Buf(ISP_WRAP_DS1_BUF_S *pstDs1Buf)
{
	ISP_CHECK_POINTER(pstDs1Buf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS1_Y_BUF0_BASE stYbufBase0;
	stYbufBase0.u32 = 0;
	stYbufBase0.bits.ds1_y_buf0_base = pstDs1Buf->ds1_y_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs1YBuf0Base(apstWrapReg, stYbufBase0.u32);
	
	U_ISP_WRAP_DS1_Y_BUF1_BASE stYbufBase1;
	stYbufBase1.u32 = 0;
	stYbufBase1.bits.ds1_y_buf1_base = pstDs1Buf->ds1_y_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs1YBuf1Base(apstWrapReg, stYbufBase1.u32);

	U_ISP_WRAP_DS1_UV_BUF0_BASE stUvbufBase0;
	stUvbufBase0.u32 = 0;
	stUvbufBase0.bits.ds1_uv_buf0_base = pstDs1Buf->ds1_uv_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs1UvBuf0Base(apstWrapReg, stUvbufBase0.u32);

	U_ISP_WRAP_DS1_UV_BUF1_BASE stUvbufBase1;
	stUvbufBase1.u32 = 0;
	stUvbufBase1.bits.ds1_uv_buf1_base = pstDs1Buf->ds1_uv_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs1UvBuf1Base(apstWrapReg, stUvbufBase1.u32);	

	U_ISP_WRAP_DS1_STRIDE stStride;	
	stStride.u32 = 0;
	stStride.bits.ds1_y_line_stride = pstDs1Buf->ds1_y_line_stride;
	stStride.bits.ds1_uv_line_stride = pstDs1Buf->ds1_uv_line_stride;	
	ISP_WRAP_DRV_SET_WrapDs1Stride(apstWrapReg, stStride.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetDs2Buf(ISP_WRAP_DS2_BUF_S *pstDs2Buf)
{
	ISP_CHECK_POINTER(pstDs2Buf);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_DS2_R_BUF0_BASE stRbufBase0;
	stRbufBase0.u32 = 0;
	stRbufBase0.bits.ds2_r_buf0_base = pstDs2Buf->ds2_r_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs2RBuf0Base(apstWrapReg, stRbufBase0.u32);

	U_ISP_WRAP_DS2_R_BUF1_BASE stRbufBase1;
	stRbufBase1.u32 = 0;
	stRbufBase1.bits.ds2_r_buf1_base = pstDs2Buf->ds2_r_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs2RBuf1Base(apstWrapReg, stRbufBase1.u32);	

	U_ISP_WRAP_DS2_G_BUF0_BASE stGbufBase0;
	stGbufBase0.u32 = 0;
	stGbufBase0.bits.ds2_g_buf0_base = pstDs2Buf->ds2_g_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs2GBuf0Base(apstWrapReg, stGbufBase0.u32);

	U_ISP_WRAP_DS2_G_BUF1_BASE stGbufBase1;
	stGbufBase1.u32 = 0;
	stGbufBase1.bits.ds2_g_buf1_base = pstDs2Buf->ds2_g_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs2GBuf1Base(apstWrapReg, stGbufBase1.u32);

	U_ISP_WRAP_DS2_B_BUF0_BASE stBbufBase0;
	stBbufBase0.u32 = 0;
	stBbufBase0.bits.ds2_b_buf0_base = pstDs2Buf->ds2_b_buf0_base;
	ISP_WRAP_DRV_SET_WrapDs2BBuf0Base(apstWrapReg, stBbufBase0.u32);

	U_ISP_WRAP_DS2_B_BUF1_BASE stBbufBase1;
	stBbufBase1.u32 = 0;
	stBbufBase1.bits.ds2_b_buf1_base = pstDs2Buf->ds2_b_buf1_base;
	ISP_WRAP_DRV_SET_WrapDs2BBuf1Base(apstWrapReg, stBbufBase1.u32);

	U_ISP_WRAP_DS2_STRIDE0 stStride0;	
	stStride0.u32 = 0;
	stStride0.bits.ds2_r_line_stride = pstDs2Buf->ds2_r_line_stride;
	stStride0.bits.ds2_g_line_stride = pstDs2Buf->ds2_g_line_stride;
	ISP_WRAP_DRV_SET_WrapDs2Stride0(apstWrapReg, stStride0.u32);

	U_ISP_WRAP_DS2_STRIDE1 stStride1;
	stStride1.u32 = 0;
	stStride1.bits.ds2_b_line_stride = pstDs2Buf->ds2_b_line_stride;
	ISP_WRAP_DRV_SET_WrapDs2Stride1(apstWrapReg, stStride1.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetAxiCtl(ISP_WRAP_AXI_CTL_S *pstAxiCtl)
{
	ISP_CHECK_POINTER(pstAxiCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_AXI_CTL stData;
	stData.u32 = 0;
	stData.bits.axi_wr_ch_rst_req = pstAxiCtl->axi_wr_ch_rst_req;   
	stData.bits.axi_rd_ch_rst_req = pstAxiCtl->axi_rd_ch_rst_req;    
	stData.bits.axi_wr_ch_state = pstAxiCtl->axi_wr_ch_state;
	stData.bits.axi_rd_ch_state = pstAxiCtl->axi_rd_ch_state;    
	//stData.u32 = 0x00000F74;
	ISP_WRAP_DRV_SET_WrapAxiCtl(apstWrapReg, stData.u32);
	return 0;
}

static int ISP_DRV_WRAP_SetConfigdoneCtl(ISP_WRAP_CONFIG_DONE_S *pstConfigDone)
{
	ISP_CHECK_POINTER(pstConfigDone);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	U_ISP_WRAP_CONFIG_DONE stData;
	stData.u32 = ISP_WRAP_DRV_GET_WrapConfigDone(apstWrapReg);
	stData.bits.wrap_config_done_en = pstConfigDone->wrap_config_done_en;//1;
	stData.bits.int_polarity        = pstConfigDone->int_polarity;//1
	stData.bits.sen_reg_pro_en      = pstConfigDone->sen_reg_pro_en;//0
	ISP_WRAP_DRV_SET_WrapConfigDone(apstWrapReg,stData.u32);

	return 0;
}
/*
*INT
*/
static int ISP_DRV_WRAP_SetCoreIntCtlMask(ISP_WRAP_CORE_INT_CTL_S *pstCoreIntCtl)
{
	ISP_CHECK_POINTER(pstCoreIntCtl);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

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
	ISP_WRAP_DRV_SET_WrapCoreIntCtl(apstWrapReg, stData.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDmaWRIntMask0(ISP_WRAP_DMA_WR_INT_MASK0_S *pstDmaWRIntMask0)
{
	ISP_CHECK_POINTER(pstDmaWRIntMask0);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

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
	ISP_WRAP_DRV_SET_WrapDmaWrIntMask0(apstWrapReg, stData.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDmaWRIntMask1(ISP_WRAP_DMA_WR_INT_MASK1_S *pstDmaWRIntMask1)
{
	ISP_CHECK_POINTER(pstDmaWRIntMask1);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

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
	ISP_WRAP_DRV_SET_WrapDmaWrIntMask1(apstWrapReg, stData.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetDmaRDIntMask0(ISP_WRAP_DMA_RD_INT_MASK0_S *pstDmaRDIntMask0)
{
	ISP_CHECK_POINTER(pstDmaRDIntMask0);

	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

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
	ISP_WRAP_DRV_SET_WrapDmaRdIntMask0(apstWrapReg, stData.u32);

	return 0;
}

static int ISP_DRV_WRAP_SetIntMask(ISP_WRAP_INT_CTL_S *stIntCtl)
{
	ISP_CHECK_POINTER(stIntCtl);

	ISP_WRAP_CORE_INT_CTL_S *pstCoreIntCtl = &stIntCtl->stCoreIntCtl;
	ISP_DRV_WRAP_SetCoreIntCtlMask(pstCoreIntCtl);

	ISP_WRAP_DMA_WR_INT_MASK0_S *pstDmaWRIntMask0 = &stIntCtl->stDmaWRMask0;
	ISP_DRV_WRAP_SetDmaWRIntMask0(pstDmaWRIntMask0);

	ISP_WRAP_DMA_WR_INT_MASK1_S *pstDmaWRIntMask1 = &stIntCtl->stDmaWRMask1;
	ISP_DRV_WRAP_SetDmaWRIntMask1(pstDmaWRIntMask1);

	ISP_WRAP_DMA_RD_INT_MASK0_S *pstDmaRDIntMask0 =  &stIntCtl->stDmaRDMask0;
	ISP_DRV_WRAP_SetDmaRDIntMask0(pstDmaRDIntMask0);

	return 0;
}
/*
*wdr
*/
static int ISP_DRV_WRAP_SetWdr(ISP_WRAP_WDR_ATTR_S *pstWdrAttr)
{
	ISP_CHECK_POINTER(pstWdrAttr);
	ISP_WRAP_WDR_MODE_CTL_S *pstWdrModeCtl = &pstWdrAttr->stWdrModeCtl;
	ISP_DRV_WRAP_SetModeCtl_Wdr(pstWdrModeCtl);

	ISP_WRAP_WDR_CLK_CTL_S *pstWdrClkCtl = &pstWdrAttr->stWdrClkCtl ;
	ISP_DRV_WRAP_SetWdrClkCtl(pstWdrClkCtl);

	ISP_WRAP_WDR_DMA_EN_CTL_S *pstWdrDmaEn = &pstWdrAttr->stWdrDmaEn;
	ISP_DRV_WRAP_SetWdrDmaEnCtl(pstWdrDmaEn);

	ISP_WRAP_WDR_PIXEL_FORMAT_CTL_S *pstWdrPixelFormat = &pstWdrAttr->stWdrPixelFormat;
	ISP_DRV_WRAP_SetWdrFormatCtl(pstWdrPixelFormat);
	
	ISP_WRAP_WDR_BUF_S *pstWdrBuf = &pstWdrAttr->stWdrBuf;
	ISP_DRV_WRAP_SetwdrBuf(pstWdrBuf);

	return 0;
}
/*
*3dnr
*/
static int ISP_DRV_WRAP_Set3Dnr(ISP_WRAP_3DNR_ATTR_S *pst3DnrAttr)
{
	ISP_CHECK_POINTER(pst3DnrAttr);

	unsigned int nr3d_mfbcd_en = pst3DnrAttr->nr3d_mfbcd_en;
	ISP_DRV_WRAP_SetModeCtl_3dnr_mfbcd_en(nr3d_mfbcd_en);

	unsigned int nr3d_mv_out_en = pst3DnrAttr->nr3d_mv_out_en;
	ISP_DRV_WRAP_SetModeCtl_3dnr_mv_en(nr3d_mv_out_en);

	unsigned int clk_3dnr_en = pst3DnrAttr->clk_3dnr_en;
	ISP_DRV_WRAP_Set3DnrClkCtl(clk_3dnr_en);

	unsigned int pipe_3dnr_dma_en = pst3DnrAttr->pipe_3dnr_dma_en;
	ISP_DRV_WRAP_Set3dnrDmaEnCtl(pipe_3dnr_dma_en);

	ISP_WRAP_3DNR_PIXEL_FORMAT_CTL_S *pst3DnrPixelFormat = &pst3DnrAttr->st3DnrPixelFormat;
	ISP_DRV_WRAP_Set3DnrFormatCtl(pst3DnrPixelFormat);

	ISP_WRAP_3DNR_BUF_S *pst3dnrBuf = &pst3DnrAttr->st3dnrBuf;
	ISP_DRV_WRAP_Set3dnrBuf(pst3dnrBuf);

	return 0;
}
/*
*ldc
*/
static int ISP_DRV_WRAP_SetLdc(ISP_WRAP_LDC_ATTR_S *pstLdcAttr)
{
	ISP_CHECK_POINTER(pstLdcAttr);

	unsigned int ldc_clk_en = pstLdcAttr->ldc_clk_en;
	ISP_DRV_WRAP_SetLdcClkCtl(ldc_clk_en);

	unsigned int ldc_dma_en = pstLdcAttr->ldc_dma_en;
	ISP_DRV_WRAP_SetLdcDmaEnCtl(ldc_dma_en);

	ISP_WRAP_LDC_BUF_S *pstLdcBuf  = &pstLdcAttr->stLdcBuf;
	ISP_DRV_WRAP_SetLdcBuf(pstLdcBuf);

	return 0;
}
/*
*main out
*/
static int ISP_DRV_WRAP_SetMainOut(ISP_WRAP_MAINOUT_ATTR_S *pstMainOutAttr)
{
	ISP_CHECK_POINTER(pstMainOutAttr);

	unsigned int main_out_clk_en = pstMainOutAttr->main_out_clk_en;
	ISP_DRV_WRAP_SetMainClkCtl(main_out_clk_en);

	unsigned int main_out_dma_en = pstMainOutAttr->main_out_dma_en;
	ISP_DRV_WRAP_SetMainDmaEnCtl(main_out_dma_en);

	unsigned int pix_remap_main_en = pstMainOutAttr->pix_remap_main_en;
	ISP_DRV_WRAP_SetModeCtl_remap_main_en(pix_remap_main_en);
	ISP_WRAP_MAIN_PIXEL_FORMAT_CTL_S *pstMainPixelFormat = &pstMainOutAttr->stMainPixelFormat;
	ISP_DRV_WRAP_SetMainPixelFormatCtl(pstMainPixelFormat);

	ISP_WRAP_MAIN_OUT_SIZE_S *pstMainOutSize = &pstMainOutAttr->stMainOutSize;
	ISP_DRV_WRAP_SetMainOutSize(pstMainOutSize);

	ISP_WRAP_MAIN_BUF_S *pstMainBuf = &pstMainOutAttr->stMainBuf;
	ISP_DRV_WRAP_SetMainBuf(pstMainBuf);

	return 0;
}
/*
*out0
*/
static int ISP_DRV_WRAP_SetDs0Out(ISP_WRAP_DS0OUT_ATTR_S *pstDs0OutAttr)
{
	ISP_CHECK_POINTER(pstDs0OutAttr);

	ISP_WRAP_DS0_CLK_CTL_S *pstDs0ClkCtl = &pstDs0OutAttr->stDs0ClkCtl;
	ISP_DRV_WRAP_SetDs0ClkCtl(pstDs0ClkCtl);

	ISP_WRAP_DS0_DMA_EN_CTL_S *pstDs0DMAEnCtl = &pstDs0OutAttr->stDs0DmaEn;
	ISP_DRV_WRAP_SetDs0DmaEnCtl(pstDs0DMAEnCtl);

	unsigned int pix_remap_out0_en = pstDs0OutAttr->pix_remap_out0_en;
	ISP_DRV_WRAP_SetModeCtl_remap_out0_en(pix_remap_out0_en);

	ISP_WRAP_DS0_PIXEL_FORMAT_CTL_S *pstDs0PixelFormat = &pstDs0OutAttr->stDs0PixelFormat;
	ISP_DRV_WRAP_SetDs0PixelFormatCtl(pstDs0PixelFormat);


	ISP_WRAP_DS0_OUT_SIZE_S *stDs0OutSize = &pstDs0OutAttr->stDs0OutSize;
	ISP_DRV_WRAP_SetDs0OutSize(stDs0OutSize);

	ISP_WRAP_DS0_BUF_S *pstDsBuf = &pstDs0OutAttr->stDs0Buf;
	ISP_DRV_WRAP_SetDs0Buf(pstDsBuf);

	return 0;
}
/*
*out1
*/
static int ISP_DRV_WRAP_SetDs1Out(ISP_WRAP_DS1OUT_ATTR_S *pstDs1OutAttr)
{
	ISP_CHECK_POINTER(pstDs1OutAttr);

	ISP_WRAP_DS1_CLK_CTL_S *pstDs1ClkCtl = &pstDs1OutAttr->stDs1ClkCtl;
	ISP_DRV_WRAP_SetDs1ClkCtl(pstDs1ClkCtl);

	ISP_WRAP_DS1_DMA_EN_CTL_S *pstDs1DMAEnCtl = &pstDs1OutAttr->stDs1DmaEn;
	ISP_DRV_WRAP_SetDs1DmaEnCtl(pstDs1DMAEnCtl);

	unsigned int pix_remap_out1_en = pstDs1OutAttr->pix_remap_out1_en;
	ISP_DRV_WRAP_SetModeCtl_remap_out1_en(pix_remap_out1_en);

	ISP_WRAP_DS1_PIXEL_FORMAT_CTL_S *pstDs1PixelFormat = &pstDs1OutAttr->stDs1PixelFormat;
	ISP_DRV_WRAP_SetDs1PixelFormatCtl(pstDs1PixelFormat);

	ISP_WRAP_DS1_OUT_SIZE_S *stDs1OutSize = &pstDs1OutAttr->stDs1OutSize;
	ISP_DRV_WRAP_SetDs1OutSize(stDs1OutSize);

	ISP_WRAP_DS1_BUF_S *pstDsBuf = &pstDs1OutAttr->stDs1Buf;
	ISP_DRV_WRAP_SetDs1Buf(pstDsBuf);

	return 0;
}
/*
*out2
*/
static int ISP_DRV_WRAP_SetDs2Out(ISP_WRAP_DS2OUT_ATTR_S *pstDs2OutAttr)
{
	ISP_CHECK_POINTER(pstDs2OutAttr);
	ISP_WRAP_DS2_CLK_CTL_S *pstDs2ClkCtl = &pstDs2OutAttr->stDs2ClkCtl;
	ISP_DRV_WRAP_SetDs2ClkCtl(pstDs2ClkCtl);

	ISP_WRAP_DS2_DMA_EN_CTL_S *pstDs2DMAEnCtl = &pstDs2OutAttr->stDs2DmaEn;
	ISP_DRV_WRAP_SetDs2DmaEnCtl(pstDs2DMAEnCtl);

	ISP_WRAP_DS2_PIXEL_FORMAT_CTL_S *pstDs2PixelFormat = &pstDs2OutAttr->stDs2PixelFormat;
	ISP_DRV_WRAP_SetDs2PixelFormatCtl(pstDs2PixelFormat);

	ISP_WRAP_DS2_OUT_SIZE_S *stDs2OutSize = &pstDs2OutAttr->stDs2OutSize;
	ISP_DRV_WRAP_SetDs2OutSize(stDs2OutSize);

	ISP_WRAP_DS2_BUF_S *pstDs2Buf = &pstDs2OutAttr->stDs2Buf;
	ISP_DRV_WRAP_SetDs2Buf(pstDs2Buf);

	return 0;
}
/*
*
*/
int ISP_DRV_SetWrap(ISP_WRAP_ATTR_S *pstWrapAttr)
{
	ISP_CHECK_POINTER(pstWrapAttr);

	ISP_DRV_WRAP_SetReset( );

	unsigned int external_out_ch_sel = pstWrapAttr->external_out_ch_sel;
	ISP_DRV_WRAP_SetModeCtl_OutSel(external_out_ch_sel);

	unsigned int dvp_input_ch_type = pstWrapAttr->dvp_input_ch_type;
	ISP_DRV_WRAP_SetModeCtl_DvpMode(dvp_input_ch_type);

	ISP_WRAP_PIPE_CLK_CTL_S *pstPipeClkCtl = &pstWrapAttr->stPipeClkCtl;
	ISP_DRV_WRAP_SetComClkCtl(pstPipeClkCtl);

	ISP_WRAP_WDR_ATTR_S *pstWdrAttr = &pstWrapAttr->stWdr;
	ISP_DRV_WRAP_SetWdr(pstWdrAttr);
	
	ISP_WRAP_3DNR_ATTR_S *pst3DnrAttr = &pstWrapAttr->st3Dnr;
	ISP_DRV_WRAP_Set3Dnr(pst3DnrAttr);

	ISP_WRAP_LDC_ATTR_S *pstLdcAttr = &pstWrapAttr->stLdc;
	ISP_DRV_WRAP_SetLdc(pstLdcAttr);

	ISP_WRAP_MAINOUT_ATTR_S *pstMainOutAttr = &pstWrapAttr->stMainOut;
	ISP_DRV_WRAP_SetMainOut(pstMainOutAttr);

	ISP_WRAP_DS0OUT_ATTR_S *pstDs0OutAttr = &pstWrapAttr->stDs0Out;
	ISP_DRV_WRAP_SetDs0Out(pstDs0OutAttr);

	ISP_WRAP_DS1OUT_ATTR_S *pstDs1OutAttr = &pstWrapAttr->stDs1Out;
	ISP_DRV_WRAP_SetDs1Out(pstDs1OutAttr);

	ISP_WRAP_DS2OUT_ATTR_S *pstDs2OutAttr = &pstWrapAttr->stDs2Out;
	ISP_DRV_WRAP_SetDs2Out(pstDs2OutAttr);

	ISP_WRAP_DMA_ATTR_S *pstDmaAttr = &pstWrapAttr->stDmaAttr;
	ISP_DRV_WRAP_SetDma(pstDmaAttr);

	ISP_WRAP_AXI_CTL_S *pstAxiCtl = &pstWrapAttr->stAxiCtl;
	ISP_DRV_WRAP_SetAxiCtl(pstAxiCtl);

	ISP_WRAP_INT_CTL_S *pstIntCtl = &pstWrapAttr->stIntCtl;
	ISP_DRV_WRAP_SetIntMask(pstIntCtl);

	ISP_WRAP_CONFIG_DONE_S *pstConfigDone = &pstWrapAttr->stConfigDone;
	ISP_DRV_WRAP_SetConfigdoneCtl(pstConfigDone);
	return 0;
}
/*
*
*/
int ISP_DRV_Init_IntCoreMask(unsigned int EnIntr)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapCoreIntCtl(apstWrapReg,EnIntr);
	return 0;
}
/*
*
*/
int ISP_DRV_Init_IntDmaWr0Mask(unsigned int EnIntr)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaWrIntMask0(apstWrapReg,EnIntr);
	return 0;
}
/*
*
*/
int ISP_DRV_Init_IntDmaWr1Mask(unsigned int EnIntr)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaWrIntMask1(apstWrapReg,EnIntr);
	return 0;
}
/*
*
*/
int ISP_DRV_Init_IntDmaRd0Mask(unsigned int EnIntr)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaRdIntMask0(apstWrapReg,EnIntr);
	return 0;
}
/*
*
*/
int ISP_DRV_GetIntCoreSts(void)
{
	int int_status;
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);
	//printf("apstWrapReg = 0x%x\n",apstWrapReg);
	int_status = ISP_WRAP_DRV_GET_WrapCoreIntCtl(apstWrapReg);

	return int_status;
}
/*
*
*/
int ISP_DRV_GetIntDmaWr0Sts(void)
{
	int int_status;
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	int_status = ISP_WRAP_DRV_GET_WrapDmaWrIntStatus0(apstWrapReg);

	return int_status;
}
/*
*
*/
int ISP_DRV_GetIntDmaWr1Sts(void)
{
	int int_status;
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	int_status = ISP_WRAP_DRV_GET_WrapDmaWrIntStatus1(apstWrapReg);

	return int_status;
}
/*
*
*/
int ISP_DRV_GetIntDmaRd0Sts(void)
{
	int int_status;
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	int_status = ISP_WRAP_DRV_GET_WrapDmaRdIntStatus0(apstWrapReg);

	return int_status;
}
/*
*
*/
int ISP_DRV_ClearIntCoreSts(int int_status)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapCoreIntCtl(apstWrapReg,int_status);

	return 0;
}
/*
*
*/
int ISP_DRV_ClearIntDmaWr0Sts(int int_status)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaWrIntStatus0(apstWrapReg,int_status);
	return 0;
}
/*
*
*/
int ISP_DRV_ClearIntDmaWr1Sts(int int_status)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaWrIntStatus1(apstWrapReg,int_status);
	return 0;
}
/*
*
*/
int ISP_DRV_ClearIntDmaRd0Sts(int int_status)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_SET_WrapDmaRdIntStatus0(apstWrapReg,int_status);
	return 0;
}
//debug
int ISP_DRV_GetWrapRegsVal(void)
{
	S_ISP_WRAP_REGS_TYPE *apstWrapReg = NULL;		
	ISP_2K_DRV_WRAP_REG_CTX(apstWrapReg);

	ISP_WRAP_DRV_GET_WrapRegsVal(apstWrapReg);

	return 0;
}
