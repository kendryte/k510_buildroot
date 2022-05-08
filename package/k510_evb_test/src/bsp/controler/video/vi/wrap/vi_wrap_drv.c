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
#include "video/video_subsystem_addr.h"
//#include "vi/inc/vi.h"
#include "video/vi/wrap/vi_wrap_reg.h"
#include "video/vi/wrap/vi_wrap_drv.h"

unsigned int *reg_vi_wrap_base;
#define VI_DRV_WRAP_REG_CTX(pstCtx)     pstCtx = (S_VI_WRAP_REGS_TYPE *)(reg_vi_wrap_base)

int VI_DRV_WRAP_Remap(void)
{
	
	reg_vi_wrap_base = (unsigned int *)VI_WRAP_REG_BASE;

	return 0;
}

/*
*
*/
static void VI_DRV_WRAP_SetRst(VI_WRAP_RESET_CTL_S *pstRstCtl)
{
	VI_CHECK_POINTER(pstRstCtl);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;	
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_SWRST_CTL stData;
	stData.u32 = 0;
	stData.bits.csi_0_0_rst = pstRstCtl->csi_00_rst_en;//1;
	stData.bits.csi_0_1_rst = pstRstCtl->csi_01_rst_en;//1;
	stData.bits.csi_0_2_rst = pstRstCtl->csi_02_rst_en;//1;

	stData.bits.csi_1_0_rst = pstRstCtl->csi_10_rst_en;//1;
//	stData.bits.csi_1_1_rst = pstRestCtl->csi_11_rst_en;
//	stData.bits.csi_1_2_rst = pstRestCtl->csi_12_rst_en;
	stData.bits.dvp_0_rst = pstRstCtl->dvp_0_rst_en;//1;
//	stData.bits.dvp_1_rst = pstRestCtl->dvp_1_rst_en;
	
	stData.bits.axi_wr_ch_rst = pstRstCtl->axi_wr_ch_rst_en;//1;
	stData.bits.axi_rd_ch_rst = pstRstCtl->axi_rd_ch_rst_en;//1;
	//stData.u32 =0x3ff;
	VI_WRAP_DRV_SET_WrapSwrstCtl(apstWrapReg, stData.u32);
	return ;	
}
/*
*
*/
static int VI_DRV_WRAP_SetCtlMode(VI_WRAP_CSI_MODE_CTL_S *pstCsiModeCtl)
{
	VI_CHECK_POINTER(pstCsiModeCtl);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_CSI_MODE_CTL stData;	
	stData.u32 = 0;
	stData.bits.mipi_csi_0_mode = pstCsiModeCtl->mipi_csi_0_mode;
	stData.bits.mipi_csi_1_mode = pstCsiModeCtl->mipi_csi_1_mode;
	stData.bits.mipi_dphy_mode = pstCsiModeCtl->mipi_dphy_mode;
	stData.bits.mipi_csi01_dbg_sel = pstCsiModeCtl->mipi_csi01_dbg_sel;
	stData.bits.isp_2k_clk_sel = pstCsiModeCtl->isp_2k_clk_sel;
	stData.bits.isp_r_2k_clk_sel = pstCsiModeCtl->isp_r_2k_clk_sel;
	stData.bits.csi_0_sony_dol_en = pstCsiModeCtl->csi_0_sony_dol_en;
	stData.bits.tof_clk_sel = pstCsiModeCtl->tof_clk_sel;
	stData.bits.dvp_clk_0_mode = pstCsiModeCtl->dvp_clk_0_mode;
	
	//stData.u32 = 0x00000084;
	VI_WRAP_DRV_SET_WrapCsiModeCtl(apstWrapReg, stData.u32);

	return 0;	
}
/*
*
*/
static int VI_DRV_WRAP_SetIspChSel(VI_WRAP_ISP_CH_SEL_S *pstIspChSel)
{
	VI_CHECK_POINTER(pstIspChSel);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;	
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_ISP_CH_SEL stData;
	stData.u32 = 0;
	stData.bits.isp_4k_l_ch_sel = pstIspChSel->isp_4k_l_ch_sel;
	stData.bits.isp_4k_m_ch_sel = pstIspChSel->isp_4k_m_ch_sel;
	stData.bits.isp_4k_s_ch_sel = pstIspChSel->isp_4k_s_ch_sel;
	
	stData.bits.isp_2k_l_ch_sel = pstIspChSel->isp_2k_l_ch_sel;
	stData.bits.isp_2k_m_ch_sel = pstIspChSel->isp_2k_m_ch_sel;
	stData.bits.isp_2k_s_ch_sel = pstIspChSel->isp_2k_s_ch_sel;

	stData.bits.isp_r_2k_ch_sel = pstIspChSel->isp_r_2k_ch_sel;
	stData.bits.isp_3d_ch_sel = pstIspChSel->isp_3d_ch_sel;

	//stData.u32 = 0x06543210;
	VI_WRAP_DRV_SET_WrapIspChSel(apstWrapReg, stData.u32);
	return 0;	
}
/*
*
*/
static int VI_DRV_WRAP_SetClockCtl(VI_WRAP_CLOCK_CTL_S *pstClkCtl)
{
	VI_CHECK_POINTER(pstClkCtl);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_CLOCK_CTL stData;	
	stData.u32 = 0;
	stData.bits.csi_00_pixel_clk_en = pstClkCtl->csi_00_pixel_clk_en;
	stData.bits.csi_01_pixel_clk_en = pstClkCtl->csi_01_pixel_clk_en;
	stData.bits.csi_02_pixel_clk_en = pstClkCtl->csi_02_pixel_clk_en;
	
	stData.bits.csi_10_pixel_clk_en = pstClkCtl->csi_10_pixel_clk_en;
	stData.bits.csi_11_pixel_clk_en = pstClkCtl->csi_11_pixel_clk_en;
	stData.bits.csi_12_pixel_clk_en = pstClkCtl->csi_12_pixel_clk_en;

	stData.bits.csi_00_dma_clk_en = pstClkCtl->csi_00_dma_clk_en;
	stData.bits.csi_01_dma_clk_en = pstClkCtl->csi_01_dma_clk_en;
	stData.bits.csi_02_dma_clk_en = pstClkCtl->csi_02_dma_clk_en;
	
	stData.bits.csi_10_dma_clk_en = pstClkCtl->csi_10_dma_clk_en;
	stData.bits.csi_11_dma_clk_en = pstClkCtl->csi_11_dma_clk_en;
	stData.bits.csi_12_dma_clk_en = pstClkCtl->csi_12_dma_clk_en;

	stData.bits.dvp_0_pixel_clk_en = pstClkCtl->dvp_0_pixel_clk_en;
	stData.bits.dvp_0_dma_clk_en = pstClkCtl->dvp_0_dma_clk_en;

	stData.bits.dvp_1_pixel_clk_en = pstClkCtl->dvp_1_pixel_clk_en;
	stData.bits.dvp_1_dma_clk_en = pstClkCtl->dvp_1_dma_clk_en;

	stData.bits.axi_wr_ch_clk_en = pstClkCtl->axi_wr_ch_clk_en;
	stData.bits.axi_rd_ch_clk_en = pstClkCtl->axi_rd_ch_clk_en;

	//stData.u32 = 0xFFFFFFFF;
	VI_WRAP_DRV_SET_WrapClockCtl(apstWrapReg, stData.u32);
	return 0;
}
/*
*
*/
static int VI_DRV_WRAP_SetDmaAttr(VI_WRAP_DMA_ATTR_S *pstDmaAttr)
{
	VI_CHECK_POINTER(pstDmaAttr);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_DMA_ARB_MODE			stDmaArbMode;
	stDmaArbMode.u32 = 0;
	stDmaArbMode.bits.rd_dma_arb_mode = pstDmaAttr->stDmaArbMode.rd_dma_arb_mode;
	stDmaArbMode.bits.wr_dma_arb_mode = pstDmaAttr->stDmaArbMode.wr_dma_arb_mode;
	VI_WRAP_DRV_SET_WrapDmaArbMode(apstWrapReg, stDmaArbMode.u32);

	U_VI_WRAP_DMA_WR_PRIORITY		stWrChPriority;
	stWrChPriority.u32 = 0;
	stWrChPriority.bits.vi_dma_ch0_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch0_wr_priority;
	stWrChPriority.bits.vi_dma_ch1_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch1_wr_priority;
	stWrChPriority.bits.vi_dma_ch2_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch2_wr_priority;
	stWrChPriority.bits.vi_dma_ch3_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch3_wr_priority;
	stWrChPriority.bits.vi_dma_ch4_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch4_wr_priority;
	stWrChPriority.bits.vi_dma_ch5_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch5_wr_priority;
	stWrChPriority.bits.vi_dma_ch6_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch6_wr_priority;
	stWrChPriority.bits.vi_dma_ch7_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch7_wr_priority;
	VI_WRAP_DRV_SET_WrapDmaWrPriority(apstWrapReg, stWrChPriority.u32);

	U_VI_WRAP_DMA_RD_PRIORITY 		stRdChPriority;
	stRdChPriority.u32 = 0;
	stRdChPriority.bits.vi_dma_ch0_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch0_rd_priority;
	stRdChPriority.bits.vi_dma_ch1_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch1_rd_priority;
	stRdChPriority.bits.vi_dma_ch2_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch2_rd_priority;
	stRdChPriority.bits.vi_dma_ch3_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch3_rd_priority;
	stRdChPriority.bits.vi_dma_ch4_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch4_rd_priority;
	stRdChPriority.bits.vi_dma_ch5_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch5_rd_priority;
	stRdChPriority.bits.vi_dma_ch6_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch6_rd_priority;
	stRdChPriority.bits.vi_dma_ch7_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch7_rd_priority;
	VI_WRAP_DRV_SET_WrapDmaRdPriority(apstWrapReg, stRdChPriority.u32);

	U_VI_WRAP_DMA_WR_WEIGHT_0		stWrChWeight0;
	stWrChWeight0.u32 = 0;
	stWrChWeight0.bits.vi_dma_ch0_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch0_wr_weight;
	stWrChWeight0.bits.vi_dma_ch1_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch1_wr_weight;
	stWrChWeight0.bits.vi_dma_ch2_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch2_wr_weight;
	stWrChWeight0.bits.vi_dma_ch3_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch3_wr_weight;
	VI_WRAP_DRV_SET_WrapDmaWrWeight0(apstWrapReg, stWrChWeight0.u32);

	U_VI_WRAP_DMA_WR_WEIGHT_1		stWrChWeight1;
	stWrChWeight1.u32 = 0;
	stWrChWeight1.bits.vi_dma_ch4_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch4_wr_weight;
	stWrChWeight1.bits.vi_dma_ch5_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch5_wr_weight;
	stWrChWeight1.bits.vi_dma_ch6_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch6_wr_weight;
	stWrChWeight1.bits.vi_dma_ch7_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch7_wr_weight;
	VI_WRAP_DRV_SET_WrapDmaWrWeight1(apstWrapReg, stWrChWeight1.u32);

	U_VI_WRAP_DMA_RD_WEIGHT_0		stRdChWeight0;
	stRdChWeight0.u32 = 0;
	stRdChWeight0.bits.vi_dma_ch0_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch0_rd_weight;
	stRdChWeight0.bits.vi_dma_ch1_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch1_rd_weight;
	stRdChWeight0.bits.vi_dma_ch2_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch2_rd_weight;
	stRdChWeight0.bits.vi_dma_ch3_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch3_rd_weight;
	//stRdChWeight0.u32 = 0x01234567;
	VI_WRAP_DRV_SET_WrapDmaRdWeight0(apstWrapReg, stRdChWeight0.u32);

	U_VI_WRAP_DMA_RD_WEIGHT_1		stRdChWeight1;
	stRdChWeight1.u32 = 0;
	stRdChWeight1.bits.vi_dma_ch4_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch4_rd_weight;
	stRdChWeight1.bits.vi_dma_ch5_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch5_rd_weight;
	stRdChWeight1.bits.vi_dma_ch6_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch6_rd_weight;
	stRdChWeight1.bits.vi_dma_ch7_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch7_rd_weight;
	//stRdChWeight1.u32 = 0x01234567;
	VI_WRAP_DRV_SET_WrapDmaRdWeight1(apstWrapReg, stRdChWeight1.u32);	

	U_VI_WRAP_DMA_WR_CH_ID			stWriteChId;
	stWriteChId.u32 = 0;
	stWriteChId.bits.vi_dma_wr_ch0_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch0_id;
	stWriteChId.bits.vi_dma_wr_ch1_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch1_id;
	stWriteChId.bits.vi_dma_wr_ch2_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch2_id;
	stWriteChId.bits.vi_dma_wr_ch3_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch3_id;
	stWriteChId.bits.vi_dma_wr_ch4_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch4_id;
	stWriteChId.bits.vi_dma_wr_ch5_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch5_id;
	stWriteChId.bits.vi_dma_wr_ch6_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch6_id;
	stWriteChId.bits.vi_dma_wr_ch7_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch7_id;
	VI_WRAP_DRV_SET_WrapDmaWrChId(apstWrapReg, stWriteChId.u32);

	U_VI_WRAP_DMA_RD_CH_ID			stReadChId;
	stReadChId.u32 = 0;
	stReadChId.bits.vi_dma_rd_ch0_id = pstDmaAttr->stReadChId.vi_dma_rd_ch0_id;
	stReadChId.bits.vi_dma_rd_ch1_id = pstDmaAttr->stReadChId.vi_dma_rd_ch1_id;
	stReadChId.bits.vi_dma_rd_ch2_id = pstDmaAttr->stReadChId.vi_dma_rd_ch2_id;
	stReadChId.bits.vi_dma_rd_ch3_id = pstDmaAttr->stReadChId.vi_dma_rd_ch3_id;
	stReadChId.bits.vi_dma_rd_ch4_id = pstDmaAttr->stReadChId.vi_dma_rd_ch4_id;
	stReadChId.bits.vi_dma_rd_ch5_id = pstDmaAttr->stReadChId.vi_dma_rd_ch5_id;
	stReadChId.bits.vi_dma_rd_ch6_id = pstDmaAttr->stReadChId.vi_dma_rd_ch6_id;
	stReadChId.bits.vi_dma_rd_ch7_id = pstDmaAttr->stReadChId.vi_dma_rd_ch7_id;
	VI_WRAP_DRV_SET_WrapDmaRdChId(apstWrapReg, stReadChId.u32);
	
	return 0;
}
/*
*
*/
static int VI_DRV_WRAP_SetIntMask(void)
{	
	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WARP_INT_CTL stData;
	stData.u32 = 0x0; //zhudalei
	VI_WRAP_DRV_SET_WarpIntCtl(apstWrapReg,stData.u32);
	return 0;
}
/*
*
*/
static int VI_DRV_WRAP_SetCfgDone(VI_WRAP_CFG_DONE_S *pstWrapCfgDone)
{	
	VI_CHECK_POINTER(pstWrapCfgDone);

	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

	U_VI_WRAP_CONFIG_CTL stData;	
	stData.u32 = VI_WRAP_DRV_GET_WrapConfigCtl(apstWrapReg);
	stData.bits.vi_sens_reg_wr_protect = pstWrapCfgDone->vi_wrap_wp_clr;//1
	stData.bits.vi_wrap_config_done = pstWrapCfgDone->vi_wrap_config_done; //1;
	//stData.u32 = 0x00000001;
	VI_WRAP_DRV_SET_WrapConfigCtl(apstWrapReg, stData.u32);

	return 0;	
}
/*
*
*/
int VI_DRV_SetWrap(VI_WRAP_ATTR_S *pstViWrapAttr)
{
	VI_CHECK_POINTER(pstViWrapAttr);

	VI_WRAP_RESET_CTL_S *pstRstCtl = &pstViWrapAttr->stRestCtl;
	VI_DRV_WRAP_SetRst(pstRstCtl);

	VI_WRAP_CSI_MODE_CTL_S *pstCsiModeCtl = &pstViWrapAttr->stWrapCsiCtl;
	VI_DRV_WRAP_SetCtlMode(pstCsiModeCtl);

	VI_WRAP_ISP_CH_SEL_S *pstIspChSel = &pstViWrapAttr->stWrapIspChSel;
	VI_DRV_WRAP_SetIspChSel(pstIspChSel);

	VI_WRAP_CLOCK_CTL_S *pstClkCtl = &pstViWrapAttr->stWarpClockCtl;
	VI_DRV_WRAP_SetClockCtl(pstClkCtl);

	VI_WRAP_DMA_ATTR_S *pstDmaAttr = &pstViWrapAttr->stWrapDmaAttr;
	VI_DRV_WRAP_SetDmaAttr(pstDmaAttr);

	VI_DRV_WRAP_SetIntMask();

	VI_WRAP_CFG_DONE_S *pstWrapCfgDone = &pstViWrapAttr->stWrapCfgDone;
	VI_DRV_WRAP_SetCfgDone(pstWrapCfgDone);
	

	return 0;
}
/*
*debug
*/
unsigned int VI_DRV_WRAP_GetWrapRegsVal(void)
{
	S_VI_WRAP_REGS_TYPE *apstWrapReg = NULL;
	VI_DRV_WRAP_REG_CTX(apstWrapReg);

    VI_WRAP_DRV_GETWrapRegsVal(apstWrapReg);

	return 0;
}

