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
 * vi_wrap_drv.c
 *
 * CANAAN ISP - vi wrap module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#include "isp_com.h"
#include "vi/vi.h"
#include "vi/vi_com.h"
#include "vi/wrap/vi_wrap_drv.h"
#include "vi/wrap/vi_wrap_reg.h"

/*
*
*/
void VI_DRV_WRAP_SetRst(struct isp_device *isp,VI_WRAP_RESET_CTL_S *pstRstCtl)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstRstCtl);

	U_VI_WRAP_SWRST_CTL stData;
	stData.udata = 0;
	stData.bits.csi_0_0_rst = pstRstCtl->csi_00_rst_en;//1;
	stData.bits.csi_0_1_rst = pstRstCtl->csi_01_rst_en;//1;
	stData.bits.csi_0_2_rst = pstRstCtl->csi_02_rst_en;//1;

	stData.bits.csi_1_0_rst = pstRstCtl->csi_10_rst_en;//1;
	//stData.bits.csi_1_1_rst = 1;//pstRestCtl->csi_11_rst_en;
	//stData.bits.csi_1_2_rst = 1;//pstRestCtl->csi_12_rst_en;
	stData.bits.dvp_0_rst = pstRstCtl->dvp_0_rst_en;//1;
	//stData.bits.dvp_1_rst = 1;//pstRestCtl->dvp_1_rst_en;
	
	stData.bits.axi_wr_ch_rst = pstRstCtl->axi_wr_ch_rst_en;//1;
	stData.bits.axi_rd_ch_rst = pstRstCtl->axi_rd_ch_rst_en;//1;
	//stData.udata =0x3ff;
	printf("struct isp_device 0x%x,VI_WRAP_SWRST_CTL = 0x%x\n",isp,stData.udata);
	isp_reg_writel(isp,stData.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_SWRST_CTL);
	return ;	
}
/*
*
*/
int VI_DRV_WRAP_SetCtlMode(struct isp_device *isp,VI_WRAP_CSI_MODE_CTL_S *pstCsiModeCtl)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstCsiModeCtl);

	U_VI_WRAP_CSI_MODE_CTL stData;	
	stData.udata = 0;
	stData.bits.mipi_csi_0_mode = pstCsiModeCtl->mipi_csi_0_mode;
	stData.bits.mipi_csi_1_mode = pstCsiModeCtl->mipi_csi_1_mode;
	stData.bits.mipi_dphy_mode = pstCsiModeCtl->mipi_dphy_mode;
	stData.bits.mipi_csi01_dbg_sel = pstCsiModeCtl->mipi_csi_1_mode;
	stData.bits.isp_2k_clk_sel = pstCsiModeCtl->isp_2k_clk_sel;
	stData.bits.isp_r_2k_clk_sel = pstCsiModeCtl->isp_r_2k_clk_sel;
	stData.bits.csi_0_sony_dol_en = pstCsiModeCtl->csi_0_sony_dol_en;
	stData.bits.tof_clk_sel = pstCsiModeCtl->tof_clk_sel;
	stData.bits.dvp_clk_0_mode = pstCsiModeCtl->dvp_clk_0_mode;
	
	//stData.udata = 0x00000084;
	isp_reg_writel(isp,stData.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_CSI_MODE_CTL);

	return 0;	
}
/*
*
*/
int VI_DRV_WRAP_SetIspChSel(struct isp_device *isp,VI_WRAP_ISP_CH_SEL_S *pstIspChSel)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIspChSel);

	U_VI_WRAP_ISP_CH_SEL stData;
	stData.udata = 0;
	stData.bits.isp_4k_l_ch_sel = pstIspChSel->isp_4k_l_ch_sel;
	stData.bits.isp_4k_m_ch_sel = pstIspChSel->isp_4k_m_ch_sel;
	stData.bits.isp_4k_s_ch_sel = pstIspChSel->isp_4k_s_ch_sel;
	
	stData.bits.isp_2k_l_ch_sel = pstIspChSel->isp_2k_l_ch_sel;
	stData.bits.isp_2k_m_ch_sel = pstIspChSel->isp_2k_m_ch_sel;
	stData.bits.isp_2k_s_ch_sel = pstIspChSel->isp_2k_s_ch_sel;

	stData.bits.isp_r_2k_ch_sel = pstIspChSel->isp_r_2k_ch_sel;
	stData.bits.isp_3d_ch_sel = pstIspChSel->isp_3d_ch_sel;

	//stData.udata = 0x76543210;
	isp_reg_writel(isp,stData.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_ISP_CH_SEL);
	return 0;	
}
/*
*
*/
int VI_DRV_WRAP_SetClockCtl(struct isp_device *isp,VI_WRAP_CLOCK_CTL_S *pstClkCtl)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstClkCtl);

	U_VI_WRAP_CLOCK_CTL stData;	
	stData.udata = 0;
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

	//stData.udata = 0xFFFFFFFF;
	isp_reg_writel(isp,stData.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_CLOCK_CTL);
	return 0;
}
/*
*
*/
int VI_DRV_WRAP_SetDmaAttr(struct isp_device *isp,VI_WRAP_DMA_ATTR_S *pstDmaAttr)
{
    ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstDmaAttr);

	U_VI_WRAP_DMA_ARB_MODE			stDmaArbMode;
	stDmaArbMode.udata = 0;
	stDmaArbMode.bits.rd_dma_arb_mode = pstDmaAttr->stDmaArbMode.rd_dma_arb_mode;
	stDmaArbMode.bits.wr_dma_arb_mode = pstDmaAttr->stDmaArbMode.wr_dma_arb_mode;	
	isp_reg_writel(isp,stDmaArbMode.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_ARB_MODE);

	U_VI_WRAP_DMA_WR_WEIGHT_0		stWrChWeight0;
	stWrChWeight0.udata = 0;
	stWrChWeight0.bits.vi_dma_ch0_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch0_wr_weight;
	stWrChWeight0.bits.vi_dma_ch1_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch1_wr_weight;
	stWrChWeight0.bits.vi_dma_ch2_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch2_wr_weight;
	stWrChWeight0.bits.vi_dma_ch3_wr_weight = pstDmaAttr->stWrChWeight0.vi_dma_ch3_wr_weight;
	//stWrChWeight0.udata =0x1010101;
	isp_reg_writel(isp,stWrChWeight0.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_WR_WEIGHT_0);

	U_VI_WRAP_DMA_WR_WEIGHT_1		stWrChWeight1;
	stWrChWeight1.udata = 0;
	stWrChWeight1.bits.vi_dma_ch4_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch4_wr_weight;
	stWrChWeight1.bits.vi_dma_ch5_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch5_wr_weight;
	stWrChWeight1.bits.vi_dma_ch6_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch6_wr_weight;
	stWrChWeight1.bits.vi_dma_ch7_wr_weight = pstDmaAttr->stWrChWeight1.vi_dma_ch7_wr_weight;
	//stWrChWeight1.udata =0x1010101;
	isp_reg_writel(isp,stWrChWeight1.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_WR_WEIGHT_1);

	U_VI_WRAP_DMA_RD_WEIGHT_0		stRdChWeight0;
	stRdChWeight0.udata = 0;
	stRdChWeight0.bits.vi_dma_ch0_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch0_rd_weight;
	stRdChWeight0.bits.vi_dma_ch1_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch1_rd_weight;
	stRdChWeight0.bits.vi_dma_ch2_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch2_rd_weight;
	stRdChWeight0.bits.vi_dma_ch3_rd_weight = pstDmaAttr->stRdChWeight0.vi_dma_ch3_rd_weight;
	//stRdChWeight0.udata = 0x1010101;
	isp_reg_writel(isp,stRdChWeight0.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_RD_WEIGHT_0);

	U_VI_WRAP_DMA_RD_WEIGHT_1		stRdChWeight1;
	stRdChWeight1.udata = 0;
	stRdChWeight1.bits.vi_dma_ch4_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch4_rd_weight;
	stRdChWeight1.bits.vi_dma_ch5_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch5_rd_weight;
	stRdChWeight1.bits.vi_dma_ch6_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch6_rd_weight;
	stRdChWeight1.bits.vi_dma_ch7_rd_weight = pstDmaAttr->stRdChWeight1.vi_dma_ch7_rd_weight;
	//stRdChWeight1.udata = 0x1010101;
	isp_reg_writel(isp,stRdChWeight1.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_RD_WEIGHT_1);

	U_VI_WRAP_DMA_WR_PRIORITY		stWrChPriority;
	stWrChPriority.udata = 0;
	stWrChPriority.bits.vi_dma_ch0_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch0_wr_priority;
	stWrChPriority.bits.vi_dma_ch1_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch1_wr_priority;
	stWrChPriority.bits.vi_dma_ch2_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch2_wr_priority;
	stWrChPriority.bits.vi_dma_ch3_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch3_wr_priority;
	stWrChPriority.bits.vi_dma_ch4_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch4_wr_priority;
	stWrChPriority.bits.vi_dma_ch5_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch5_wr_priority;
	stWrChPriority.bits.vi_dma_ch6_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch6_wr_priority;
	stWrChPriority.bits.vi_dma_ch7_wr_priority = pstDmaAttr->stWrChPriority.vi_dma_ch7_wr_priority;
	//stWrChPriority.udata = 0x1234567;
	isp_reg_writel(isp,stWrChPriority.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_WR_PRIORITY);

	U_VI_WRAP_DMA_RD_PRIORITY 		stRdChPriority;
	stRdChPriority.udata = 0;
	stRdChPriority.bits.vi_dma_ch0_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch0_rd_priority;
	stRdChPriority.bits.vi_dma_ch1_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch1_rd_priority;
	stRdChPriority.bits.vi_dma_ch2_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch2_rd_priority;
	stRdChPriority.bits.vi_dma_ch3_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch3_rd_priority;
	stRdChPriority.bits.vi_dma_ch4_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch4_rd_priority;
	stRdChPriority.bits.vi_dma_ch5_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch5_rd_priority;
	stRdChPriority.bits.vi_dma_ch6_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch6_rd_priority;
	stRdChPriority.bits.vi_dma_ch7_rd_priority = pstDmaAttr->stRdChPriority.vi_dma_ch7_rd_priority;
	//stRdChPriority.udata = 0x1234567;
	isp_reg_writel(isp,stRdChPriority.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_RD_PRIORITY);

	U_VI_WRAP_DMA_WR_CH_ID			stWriteChId;
	stWriteChId.udata = 0;
	stWriteChId.bits.vi_dma_wr_ch0_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch0_id;
	stWriteChId.bits.vi_dma_wr_ch1_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch1_id;
	stWriteChId.bits.vi_dma_wr_ch2_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch2_id;
	stWriteChId.bits.vi_dma_wr_ch3_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch3_id;
	stWriteChId.bits.vi_dma_wr_ch4_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch4_id;
	stWriteChId.bits.vi_dma_wr_ch5_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch5_id;
	stWriteChId.bits.vi_dma_wr_ch6_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch6_id;
	stWriteChId.bits.vi_dma_wr_ch7_id = pstDmaAttr->stWriteChId.vi_dma_wr_ch7_id;
	//stWriteChId.udata = 0x76543210;
	isp_reg_writel(isp,stWriteChId.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_WR_CH_ID);

	U_VI_WRAP_DMA_RD_CH_ID			stReadChId;
	stReadChId.udata = 0;
	stReadChId.bits.vi_dma_rd_ch0_id = pstDmaAttr->stReadChId.vi_dma_rd_ch0_id;
	stReadChId.bits.vi_dma_rd_ch1_id = pstDmaAttr->stReadChId.vi_dma_rd_ch1_id;
	stReadChId.bits.vi_dma_rd_ch2_id = pstDmaAttr->stReadChId.vi_dma_rd_ch2_id;
	stReadChId.bits.vi_dma_rd_ch3_id = pstDmaAttr->stReadChId.vi_dma_rd_ch3_id;
	stReadChId.bits.vi_dma_rd_ch4_id = pstDmaAttr->stReadChId.vi_dma_rd_ch4_id;
	stReadChId.bits.vi_dma_rd_ch5_id = pstDmaAttr->stReadChId.vi_dma_rd_ch5_id;
	stReadChId.bits.vi_dma_rd_ch6_id = pstDmaAttr->stReadChId.vi_dma_rd_ch6_id;
	stReadChId.bits.vi_dma_rd_ch7_id = pstDmaAttr->stReadChId.vi_dma_rd_ch7_id;
	//stReadChId.udata = 0x76543210;
	isp_reg_writel(isp,stReadChId.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_DMA_RD_CH_ID);
	
	return 0;
}
/*
*
*/
int VI_DRV_WRAP_SetIntEn(struct isp_device *isp,VI_WRAP_INT_EN_S *pstIntEn)
{	
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstIntEn);

	U_VI_WARP_INT_CTL			stIntCtl;
	stIntCtl.bits.csi_0_host_mask    	= ~pstIntEn->csi_0_host_int_en;	
	stIntCtl.bits.csi_0_host_err_mask	= ~pstIntEn->csi_0_host_err_int_en;	
	stIntCtl.bits.csi_1_host_mask    	= ~pstIntEn->csi_1_host_int_en;	
	stIntCtl.bits.csi_1_host_err_mask	= ~pstIntEn->csi_1_host_err_int_en;	
	stIntCtl.bits.csi_0_ctrl_0_mask  	= ~pstIntEn->csi_0_ctrl_0_int_en;	
	stIntCtl.bits.csi_0_ctrl_1_mask  	= ~pstIntEn->csi_0_ctrl_1_int_en;	
	stIntCtl.bits.csi_0_ctrl_2_mask  	= ~pstIntEn->csi_0_ctrl_2_int_en;	
	stIntCtl.bits.dvp_0_ctrl_mask    	= ~pstIntEn->dvp_0_ctrl_int_en;	
	stIntCtl.bits.csi_1_ctrl_0_mask  	= ~pstIntEn->csi_1_ctrl_0_int_en;	
	stIntCtl.bits.csi_1_ctrl_1_mask  	= ~pstIntEn->csi_1_ctrl_1_int_en;	
	stIntCtl.bits.csi_1_ctrl_2_mask  	= ~pstIntEn->csi_1_ctrl_2_int_en;	
	stIntCtl.bits.dvp_1_ctrl_mask    	= ~pstIntEn->dvp_1_ctrl_int_en;	
	return 0;
}
/*
*
*/
int VI_DRV_WRAP_SetCfgDone(struct isp_device *isp,VI_WRAP_CFG_DONE_S *pstWrapCfgDone)
{	
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstWrapCfgDone);

	U_VI_WRAP_CONFIG_CTL stData;	
	stData.udata = isp_reg_readl(isp,ISP_IOMEM_VI_WRAP,VI_WRAP_CONFIG_CTL);
	stData.bits.vi_sens_reg_wr_protect = pstWrapCfgDone->vi_wrap_wp_clr;//1
	stData.bits.vi_wrap_config_done = pstWrapCfgDone->vi_wrap_config_done; //1;
	//stData.udata = 0x00000001;
	isp_reg_writel(isp,stData.udata,ISP_IOMEM_VI_WRAP,VI_WRAP_CONFIG_CTL);

	return 0;	
}
