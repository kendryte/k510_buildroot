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
 * isp_3d_wrap.c
 *
 * CANAAN ISP - isp 3d wrap module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_3d_wrap_drv.h"
#include "isp_3d_wrap_reg.h"
/*
*
*/
static unsigned int TOF_Drv_Wrap_SetPipeReset(struct isp_device *isp,TOF_WRAP_CTL_SWRST_S *stSwrst)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stSwrst);

	U_TOF_WRAP_CTL_SWRST stData;
	stData.u32 = 0;
	stData.bits.tof_wrap_com_pipe_rst = stSwrst->tof_wrap_com_pipe_rst;//1;
	stData.bits.tof_wrap_cfg_pipe_rst = stSwrst->tof_wrap_cfg_pipe_rst;//1;
	stData.bits.tof_core_com_pipe_rst = stSwrst->tof_core_com_pipe_rst;//1;
	stData.bits.tof_core_cfg_pipe_rst = stSwrst->tof_core_com_pipe_rst;//1;
	
	stData.bits.tof_out_depth_pipe_rst = stSwrst->tof_out_depth_pipe_rst;//1;
	stData.bits.tof_out_gray_pipe_rst =  stSwrst->tof_out_gray_pipe_rst;//1;
	stData.bits.tof_pixel_clk_pipe_rst = stSwrst->tof_pixel_clk_pipe_rst;//1;
	stData.bits.tof_pixel_div6_clk_pipe_rst =  stSwrst->tof_pixel_div6_clk_pipe_rst;//1;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_SWRST);

	return 0;
}

static unsigned int TOF_Drv_Wrap_SetDmaReset(struct isp_device *isp,TOF_WRAP_CTL_SWRST_S *stSwrst)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stSwrst);

	U_TOF_WRAP_DMA_CTL_SWRST stDmaData;
	stDmaData.u32 = 0;
	stDmaData.bits.tof_depth_dma_ch_rst =  stSwrst->tof_depth_dma_ch_rst;//1;
	stDmaData.bits.tof_gray_dma_ch_rst =  stSwrst->tof_gray_dma_ch_rst;//1;
	stDmaData.bits.tof_axi_wr_ch_rst =  stSwrst->tof_axi_wr_ch_rst;//1;
	stDmaData.bits.tof_axi_rd_ch_rst =  stSwrst->tof_axi_rd_ch_rst;//1;
	//stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stDmaData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_CTL_SWRST);

	return 0;
}

unsigned int TOF_Drv_Wrap_SetReset(struct isp_device *isp,TOF_WRAP_CTL_SWRST_S *stSwrst)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stSwrst);

	TOF_Drv_Wrap_SetPipeReset(isp,stSwrst);
	TOF_Drv_Wrap_SetDmaReset(isp,stSwrst);

	return 0;
}
/*
*
*/
unsigned int TOF_Drv_Wrap_SetCtlMode(struct isp_device *isp,TOF_WRAP_CTL_MODE_S *stMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stMode);

	U_TOF_WRAP_CTL_MODE ctlmode;
	ctlmode.u32 = 0;
	ctlmode.bits.tof_out_ch_sel			=  stMode->tof_out_ch_sel;//0;
	ctlmode.bits.tof_dvp_input_ch_type  =  stMode->tof_dvp_input_ch_type;//1; //fixed to 1'b1 for TOF sensor
	ctlmode.bits.tof_dma_chl_sel  =  stMode->tof_dma_chl_sel;
	
	isp_reg_writel(isp,ctlmode.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_MODE);
	return 0;
}
/*
*
*/
int  TOF_Drv_Wrap_SetPipeClkCtl(struct isp_device *isp,TOF_WRAP_CTL_CLK_EN_S *stClkEn)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stClkEn);
	
	U_TOF_WRAP_CTL_CLK_EN stData;
	stData.u32 = 0;
	stData.bits.tof_wrap_com_clk_en = stClkEn->tof_wrap_com_clk_en; //1;
	stData.bits.tof_wrap_cfg_clk_en = stClkEn->tof_wrap_cfg_clk_en; //1;
	stData.bits.tof_core_com_clk_en = stClkEn->tof_core_com_clk_en; //1;
	stData.bits.tof_core_cfg_clk_en = stClkEn->tof_core_cfg_clk_en; //1;

	stData.bits.tof_out_depth_clk_en = stClkEn->tof_out_depth_clk_en; //1;
	stData.bits.tof_out_gray_clk_en = stClkEn->tof_out_gray_clk_en; //1;
	stData.bits.tof_core_sensor_clk_en = stClkEn->tof_core_sensor_clk_en; //1;
	stData.bits.tof_axi_wr_clk_en = stClkEn->tof_axi_wr_clk_en; //1;
	stData.bits.tof_axi_rd_clk_en = stClkEn->tof_axi_rd_clk_en; //1;

	//stData.u32 = 0xffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_CLK_EN);
	return 0;
}
/*
*
*/
int  TOF_Drv_Wrap_SetCtlDmaEn(struct isp_device *isp,unsigned int tof_wrap_dma_out_en)
{
	ISP_CHECK_POINTER(isp);

	U_TOF_WRAP_CTL_DMA_EN dmaen;
	dmaen.bits.tof_wrap_dma_out_en = tof_wrap_dma_out_en;
	isp_reg_writel(isp,dmaen.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_DMA_EN);

	return 0;
}

int  TOF_Drv_Wrap_SetCtlPixelFormatISP(struct isp_device *isp,unsigned int ctrl_pixel_format_isp)
{
	ISP_CHECK_POINTER(isp);

	U_TOF_WRAP_CTL_PIXEL_FORMAT_ISP pixlformatisp;
    pixlformatisp.bits.ctrl_pixel_format_isp = ctrl_pixel_format_isp;
	isp_reg_writel(isp,pixlformatisp.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_PIXEL_FORMAT_ISP);

	return 0;
}

int  TOF_Drv_Wrap_SetPixelFormatOut(struct isp_device *isp,unsigned int tof_out_pixel_format)
{
	ISP_CHECK_POINTER(isp);

	U_TOF_WRAP_CTL_PIXEL_FORMAT pixelformat;
	pixelformat.bits.tof_out_pixel_format = tof_out_pixel_format;//1; //Fixed to 1鈥檅1 for TOF
	isp_reg_writel(isp,pixelformat.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_CTL_PIXEL_FORMAT);

	return 0;
}
/*
*
*/
int TOF_Drv_Wrap_SetOutSize(struct isp_device *isp,TOF_WRAP_OUT_SIZE_S *pstSize)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstSize);

	U_TOF_WRAP_OUT_SIZE stData;
	stData.u32 = 0;
	stData.bits.tof_out_v_size = pstSize->tof_out_v_size;
	stData.bits.tof_out_h_size = pstSize->tof_out_h_size;

	//stData.u32 = 0xffffffff;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_OUT_SIZE);
	return 0 ;
}
/*
*DMA
*/
static int TOF_Drv_Wrap_SetDmaArbMode(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_TOF_WRAP_DMA_ARB_MODE stData;
	stData.u32 = 0;
	stData.bits.tof_dma_wr_arb_mode = pstDmaMode->stDmaArbMode.tof_dma_wr_arb_mode;
	stData.bits.tof_dma_rd_arb_mode = pstDmaMode->stDmaArbMode.tof_dma_rd_arb_mode;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_ARB_MODE);
	return 0;
}

static int TOF_Drv_Wrap_SetDmaWeight(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_TOF_WRAP_DMA_WR_WEIGHT_0 stWrWeight0;
	stWrWeight0.u32 = 0;
	stWrWeight0.bits.tof_dma_ch0_wr_weight = pstDmaMode->wr_dma_ch_weight[0];
	stWrWeight0.bits.tof_dma_ch1_wr_weight = pstDmaMode->wr_dma_ch_weight[1];
	stWrWeight0.bits.tof_dma_ch2_wr_weight = pstDmaMode->wr_dma_ch_weight[2];
	stWrWeight0.bits.tof_dma_ch2_wr_weight = pstDmaMode->wr_dma_ch_weight[3];
	isp_reg_writel(isp,stWrWeight0.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_WR_WEIGHT_0);

	U_TOF_WRAP_DMA_WR_WEIGHT_1 stWrWeight1;
	stWrWeight1.u32 = 0;
	stWrWeight1.bits.tof_dma_ch4_wr_weight = pstDmaMode->wr_dma_ch_weight[4];
	stWrWeight1.bits.tof_dma_ch5_wr_weight = pstDmaMode->wr_dma_ch_weight[5];
	stWrWeight1.bits.tof_dma_ch6_wr_weight = pstDmaMode->wr_dma_ch_weight[6];
	stWrWeight1.bits.tof_dma_ch7_wr_weight = pstDmaMode->wr_dma_ch_weight[7];
	isp_reg_writel(isp,stWrWeight1.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_WR_WEIGHT_1);

	U_TOF_WRAP_DMA_RD_WEIGHT_0 stRdWeight0;
	stRdWeight0.u32 = 0;
	stRdWeight0.bits.tof_dma_ch0_rd_weight = pstDmaMode->rd_dma_ch_weight[0];
	stRdWeight0.bits.tof_dma_ch1_rd_weight = pstDmaMode->rd_dma_ch_weight[1];
	stRdWeight0.bits.tof_dma_ch2_rd_weight = pstDmaMode->rd_dma_ch_weight[2];
	stRdWeight0.bits.tof_dma_ch2_rd_weight = pstDmaMode->rd_dma_ch_weight[3];
	isp_reg_writel(isp,stRdWeight0.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_RD_WEIGHT_0);

	U_TOF_WRAP_DMA_RD_WEIGHT_1 stRdWeight1;
	stRdWeight1.u32 = 0;
	stRdWeight1.bits.tof_dma_ch4_rd_weight = pstDmaMode->rd_dma_ch_weight[4];
	stRdWeight1.bits.tof_dma_ch5_rd_weight = pstDmaMode->rd_dma_ch_weight[5];
	stRdWeight1.bits.tof_dma_ch6_rd_weight = pstDmaMode->rd_dma_ch_weight[6];
	stRdWeight1.bits.tof_dma_ch7_rd_weight = pstDmaMode->rd_dma_ch_weight[7];
	isp_reg_writel(isp,stRdWeight1.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_RD_WEIGHT_1);

	return 0;
}

static int TOF_Drv_Wrap_SetDmaPriority(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_TOF_WRAP_DMA_WR_PRIORITY stWrPriority;
	stWrPriority.u32 = 0;
	stWrPriority.bits.tof_dma_ch0_wr_priority = pstDmaMode->wr_dma_ch_priority[0];
	stWrPriority.bits.tof_dma_ch1_wr_priority = pstDmaMode->wr_dma_ch_priority[1];
	stWrPriority.bits.tof_dma_ch2_wr_priority = pstDmaMode->wr_dma_ch_priority[2];
	stWrPriority.bits.tof_dma_ch3_wr_priority = pstDmaMode->wr_dma_ch_priority[3];
	stWrPriority.bits.tof_dma_ch4_wr_priority = pstDmaMode->wr_dma_ch_priority[4];
	stWrPriority.bits.tof_dma_ch5_wr_priority = pstDmaMode->wr_dma_ch_priority[5];
	stWrPriority.bits.tof_dma_ch6_wr_priority = pstDmaMode->wr_dma_ch_priority[6];
	stWrPriority.bits.tof_dma_ch7_wr_priority = pstDmaMode->wr_dma_ch_priority[7];
	isp_reg_writel(isp,stWrPriority.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_WR_PRIORITY);

	U_TOF_WRAP_DMA_RD_PRIORITY stRdPriority;
	stRdPriority.u32 = 0;
	stRdPriority.bits.tof_dma_ch0_rd_priority = pstDmaMode->rd_dma_ch_priority[0];
	stRdPriority.bits.tof_dma_ch1_rd_priority = pstDmaMode->rd_dma_ch_priority[1];
	stRdPriority.bits.tof_dma_ch2_rd_priority = pstDmaMode->rd_dma_ch_priority[2];
	stRdPriority.bits.tof_dma_ch3_rd_priority = pstDmaMode->rd_dma_ch_priority[3];
	stRdPriority.bits.tof_dma_ch4_rd_priority = pstDmaMode->rd_dma_ch_priority[4];
	stRdPriority.bits.tof_dma_ch5_rd_priority = pstDmaMode->rd_dma_ch_priority[5];
	stRdPriority.bits.tof_dma_ch6_rd_priority = pstDmaMode->rd_dma_ch_priority[6];
	stRdPriority.bits.tof_dma_ch7_rd_priority = pstDmaMode->rd_dma_ch_priority[7];
	isp_reg_writel(isp,stRdPriority.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_RD_PRIORITY);

	return 0;
}

static int TOF_Drv_Wrap_SetDmaCHID(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_TOF_DMA_WR_CH_ID stWrChId;
	stWrChId.u32 = 0;
	stWrChId.bits.tof_dma_wr_ch0_id = pstDmaMode->wr_dma_ch_id[0];
	stWrChId.bits.tof_dma_wr_ch1_id = pstDmaMode->wr_dma_ch_id[1];
	stWrChId.bits.tof_dma_wr_ch2_id = pstDmaMode->wr_dma_ch_id[2];
	stWrChId.bits.tof_dma_wr_ch3_id = pstDmaMode->wr_dma_ch_id[3];
	stWrChId.bits.tof_dma_wr_ch4_id = pstDmaMode->wr_dma_ch_id[4];
	stWrChId.bits.tof_dma_wr_ch5_id = pstDmaMode->wr_dma_ch_id[5];
	stWrChId.bits.tof_dma_wr_ch6_id = pstDmaMode->wr_dma_ch_id[6];
	stWrChId.bits.tof_dma_wr_ch7_id = pstDmaMode->wr_dma_ch_id[7];
	isp_reg_writel(isp,stWrChId.u32,ISP_IOMEM_TOF_WRAP,TOF_DMA_WR_CH_ID);

	U_TOF_DMA_RD_CH_ID stRdChId;	
	stRdChId.u32 = 0;
	stRdChId.bits.tof_dma_rd_ch0_id = pstDmaMode->rd_dma_ch_id[0];
	stRdChId.bits.tof_dma_rd_ch1_id = pstDmaMode->rd_dma_ch_id[1];
	stRdChId.bits.tof_dma_rd_ch2_id = pstDmaMode->rd_dma_ch_id[2];
	stRdChId.bits.tof_dma_rd_ch3_id = pstDmaMode->rd_dma_ch_id[3];
	stRdChId.bits.tof_dma_rd_ch4_id = pstDmaMode->rd_dma_ch_id[4];
	stRdChId.bits.tof_dma_rd_ch5_id = pstDmaMode->rd_dma_ch_id[5];
	stRdChId.bits.tof_dma_rd_ch6_id = pstDmaMode->rd_dma_ch_id[6];
	stRdChId.bits.tof_dma_rd_ch7_id = pstDmaMode->rd_dma_ch_id[7];
	isp_reg_writel(isp,stRdChId.u32,ISP_IOMEM_TOF_WRAP,TOF_DMA_RD_CH_ID);

	return 0;
}

static int TOF_Drv_Wrap_SetDmaChCfg(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	U_TOF_WRAP_DMA_CH0_CFG stCh0Cfg;	
	stCh0Cfg.u32 = 0;//0x10008008;
    stCh0Cfg.bits.tof_ch0_wr_outst         = pstDmaMode->stDmaCh0Cfg.tof_wr_outst;
    stCh0Cfg.bits.tof_ch0_rd_outst         = pstDmaMode->stDmaCh0Cfg.tof_rd_outst;
    stCh0Cfg.bits.tof_ch0_wr_burstl        = pstDmaMode->stDmaCh0Cfg.tof_wr_burstl;
    stCh0Cfg.bits.tof_ch0_rd_burstl        = pstDmaMode->stDmaCh0Cfg.tof_rd_burstl;
    stCh0Cfg.bits.tof_ch0_y_uv_noncon_en   = pstDmaMode->stDmaCh0Cfg.tof_y_uv_noncon_en;
    stCh0Cfg.bits.tof_ch0_y_uv_swap_en     = pstDmaMode->stDmaCh0Cfg.tof_y_uv_swap_en;
    stCh0Cfg.bits.tof_ch0_wr_int_line_num  = pstDmaMode->stDmaCh0Cfg.tof_wr_int_line_num;
    stCh0Cfg.bits.tof_ch0_wr_err_dec_en    = pstDmaMode->stDmaCh0Cfg.tof_wr_err_dec_en;
    stCh0Cfg.bits.tof_ch0_rd_err_dec_en    = pstDmaMode->stDmaCh0Cfg.tof_rd_err_dec_en;

	isp_reg_writel(isp,stCh0Cfg.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_CH0_CFG);

	U_TOF_WRAP_DMA_CH1_CFG stCh1Cfg;
	stCh1Cfg.u32 = 0;//0x10008008;
    stCh1Cfg.bits.tof_ch1_wr_outst         = pstDmaMode->stDmaCh1Cfg.tof_wr_outst;
    stCh1Cfg.bits.tof_ch1_rd_outst         = pstDmaMode->stDmaCh1Cfg.tof_rd_outst;
    stCh1Cfg.bits.tof_ch1_wr_burstl        = pstDmaMode->stDmaCh1Cfg.tof_wr_burstl;
    stCh1Cfg.bits.tof_ch1_rd_burstl        = pstDmaMode->stDmaCh1Cfg.tof_rd_burstl;
    stCh1Cfg.bits.tof_ch1_y_uv_noncon_en   = pstDmaMode->stDmaCh1Cfg.tof_y_uv_noncon_en;
    stCh1Cfg.bits.tof_ch1_y_uv_swap_en     = pstDmaMode->stDmaCh1Cfg.tof_y_uv_swap_en;
    stCh1Cfg.bits.tof_ch1_wr_int_line_num  = pstDmaMode->stDmaCh1Cfg.tof_wr_int_line_num;
    stCh1Cfg.bits.tof_ch1_wr_err_dec_en    = pstDmaMode->stDmaCh1Cfg.tof_wr_err_dec_en;
    stCh1Cfg.bits.tof_ch1_rd_err_dec_en    = pstDmaMode->stDmaCh1Cfg.tof_rd_err_dec_en;
	isp_reg_writel(isp,stCh1Cfg.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_CH1_CFG);

	return 0;
}

static int TOF_Drv_Wrap_SetDmaChErrDecCfg(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);
	
	U_TOF_WRAP_DMA_CH0_ERR_DEC_CFG stCh0DecCfg;
	stCh0DecCfg.u32 =  0;//0x00011000;
    stCh0DecCfg.bits.tof_ch0_wr_err_dec_unit= pstDmaMode->stDmaCh0ErrCfg.tof_wr_err_dec_unit;
    stCh0DecCfg.bits.tof_ch0_rd_err_dec_unit= pstDmaMode->stDmaCh0ErrCfg.tof_rd_err_dec_unit;
    stCh0DecCfg.bits.tof_ch0_wr_err_gen_thr = pstDmaMode->stDmaCh0ErrCfg.tof_wr_err_gen_thr;
    stCh0DecCfg.bits.tof_ch0_rd_err_gen_thr = pstDmaMode->stDmaCh0ErrCfg.tof_rd_err_gen_thr;
	isp_reg_writel(isp,stCh0DecCfg.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_CH0_ERR_DEC_CFG);
	
	U_TOF_WRAP_DMA_CH1_ERR_DEC_CFG stCh1DecCfg;
	stCh1DecCfg.u32 =  0;//0x00000000;
    stCh1DecCfg.bits.tof_ch1_wr_err_dec_unit= pstDmaMode->stDmaCh1ErrCfg.tof_wr_err_dec_unit;
    stCh1DecCfg.bits.tof_ch1_rd_err_dec_unit= pstDmaMode->stDmaCh1ErrCfg.tof_rd_err_dec_unit;
    stCh1DecCfg.bits.tof_ch1_wr_err_gen_thr = pstDmaMode->stDmaCh1ErrCfg.tof_wr_err_gen_thr;
    stCh1DecCfg.bits.tof_ch1_rd_err_gen_thr = pstDmaMode->stDmaCh1ErrCfg.tof_rd_err_gen_thr;
	isp_reg_writel(isp,stCh1DecCfg.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DMA_CH1_ERR_DEC_CFG);
	return 0 ;
}

int TOF_Drv_Wrap_SetDma(struct isp_device *isp,TOF_WRAP_DMA_MODE_S *pstDmaMode)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaMode);

	TOF_Drv_Wrap_SetDmaArbMode(isp,pstDmaMode);

	TOF_Drv_Wrap_SetDmaWeight(isp,pstDmaMode);

	TOF_Drv_Wrap_SetDmaPriority(isp,pstDmaMode);

	TOF_Drv_Wrap_SetDmaCHID(isp,pstDmaMode);

	TOF_Drv_Wrap_SetDmaChCfg(isp,pstDmaMode);

	TOF_Drv_Wrap_SetDmaChErrDecCfg(isp,pstDmaMode);

	return 0;
}
/*
*
*/
int TOF_Drv_Wrap_SetBuf(struct isp_device *isp,TOF_WRAP_BUF_S *pstBuf)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstBuf);

	U_TOF_WRAP_DEPTH_BUF0_BASE stDepthBuf0;
	stDepthBuf0.u32 = 0;
	stDepthBuf0.bits.tof_depth_buf0_base = pstBuf->tof_depth_buf0_base;
	isp_reg_writel(isp,stDepthBuf0.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DEPTH_BUF0_BASE);

	U_TOF_WRAP_DEPTH_BUF1_BASE stDepthBuf1;
	stDepthBuf1.u32 = 0;
	stDepthBuf1.bits.tof_depth_buf1_base = pstBuf->tof_depth_buf1_base;
	isp_reg_writel(isp,stDepthBuf1.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_DEPTH_BUF1_BASE);

	U_TOF_WRAP_GRAY_BUF0_BASE stGrayBuf0;
	stGrayBuf0.u32 = 0;
	stGrayBuf0.bits.tof_gray_buf0_base = pstBuf->tof_gray_buf0_base;
	isp_reg_writel(isp,stGrayBuf0.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_GRAY_BUF0_BASE);

	U_TOF_WRAP_GRAY_BUF1_BASE stGrayBuf1;
	stGrayBuf1.u32 = 0;
	stGrayBuf1.bits.tof_gray_buf1_base = pstBuf->tof_gray_buf1_base;
	isp_reg_writel(isp,stGrayBuf1.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_GRAY_BUF1_BASE);	

	U_TOF_WRAP_BUF_STRIDE stBufStride;
	stBufStride.u32 = 0;
	stBufStride.bits.tof_depth_line_stride = pstBuf->tof_depth_line_stride;
	stBufStride.bits.tof_gray_line_stride = pstBuf->tof_gray_line_stride;
	isp_reg_writel(isp,stBufStride.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_BUF_STRIDE);

	return 0 ;
}
/*
*
*/
int TOF_Drv_Wrap_SetAxiCtl(struct isp_device *isp,TOF_WRAP_AXI_CTL_S *stAxiCtl)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stAxiCtl);

	U_TOF_WRAP_AXI_CTL stData;
	stData.u32 = 0;
	stData.bits.tof_axi_wr_swrst_ready = stAxiCtl->tof_axi_wr_swrst_ready;
	stData.bits.tof_axi_wr_ch_rst_req  = stAxiCtl->tof_axi_wr_ch_rst_req;
	stData.bits.tof_axi_rd_swrst_ready = stAxiCtl->tof_axi_rd_swrst_ready;
	stData.bits.tof_axi_rd_ch_rst_req  = stAxiCtl->tof_axi_rd_ch_rst_req;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_AXI_CTL);

	return 0;
}
/*
*
*/
int TOF_Drv_Wrap_SetConfigDone(struct isp_device *isp,TOF_WRAP_COFIG_DONE_S *stCfgDone)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stCfgDone);

	U_TOF_WRAP_COFIG_DONE stData;
	stData.u32 = isp_reg_readl(isp,ISP_IOMEM_TOF_WRAP,TOF_WRAP_COFIG_DONE);
	stData.bits.tof_int_polarity = stCfgDone->tof_int_polarity;
	stData.bits.tof_sen_reg_pro_en = stCfgDone->tof_sen_reg_pro_en;
	stData.bits.tof_wrap_config_done_en = stCfgDone->tof_wrap_config_done_en;//1;
	isp_reg_writel(isp,stData.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_COFIG_DONE);
	return 0;
}
/*
*
*/
int TOF_Drv_Wrap_SetInt(struct isp_device *isp,TOF_WRAP_INT_CTL_S *stIntMask)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stIntMask);	

	U_TOF_WRAP_INT_CTL  stIntCtl;
	stIntCtl.bits.tof_core_int_st_ae_out_msk = stIntMask->tof_core_int_st_ae_out_msk;
	stIntCtl.bits.tof_core_int_st_demo_out_msk = stIntMask->tof_core_int_st_demo_out_msk;
	stIntCtl.bits.tof_core_int_st_img_out_msk = stIntMask->tof_core_int_st_img_out_msk;
	stIntCtl.bits.tof_core_int_st_in_msk = stIntMask->tof_core_int_st_in_msk;
	stIntCtl.bits.tof_core_int_st_itc_out_msk = stIntMask->tof_core_int_st_itc_out_msk;
	stIntCtl.bits.tof_dma_wr_int_depth_frame_err_msk = stIntMask->tof_dma_wr_int_depth_frame_err_msk;
	stIntCtl.bits.tof_dma_wr_int_depth_frame_msk = stIntMask->tof_dma_wr_int_depth_frame_msk;
	stIntCtl.bits.tof_dma_wr_int_depth_imm_err_msk = stIntMask->tof_dma_wr_int_depth_imm_err_msk;
	stIntCtl.bits.tof_dma_wr_int_depth_line_msk = stIntMask->tof_dma_wr_int_depth_line_msk;
	stIntCtl.bits.tof_dma_wr_int_gray_frame_err_msk = stIntMask->tof_dma_wr_int_gray_frame_err_msk;
	stIntCtl.bits.tof_dma_wr_int_gray_frame_msk = stIntMask->tof_dma_wr_int_gray_frame_msk;
	stIntCtl.bits.tof_dma_wr_int_gray_imm_err_msk = stIntMask->tof_dma_wr_int_gray_imm_err_msk;
	stIntCtl.bits.tof_dma_wr_int_gray_line_msk = stIntMask->tof_dma_wr_int_gray_line_msk;
	isp_reg_writel(isp,stIntCtl.u32,ISP_IOMEM_TOF_WRAP,TOF_WRAP_INT_CTL);

	return 0;
}
