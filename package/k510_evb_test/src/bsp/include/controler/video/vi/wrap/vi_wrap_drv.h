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
#ifndef _VI_WRAP_DRV_DEF_H_
#define _VI_WRAP_DRV_DEF_H_


typedef struct _VI_WRAP_RESET_CTL_S
{
        unsigned char    csi_00_rst_en;
        unsigned char    csi_01_rst_en;
        unsigned char    csi_02_rst_en;
        unsigned char    csi_10_rst_en;
		
        unsigned char    csi_11_rst_en;
        unsigned char    csi_12_rst_en;
        unsigned char    dvp_0_rst_en;
        unsigned char    dvp_1_rst_en;
		
        unsigned char    axi_wr_ch_rst_en;
        unsigned char    axi_rd_ch_rst_en;
}VI_WRAP_RESET_CTL_S;

typedef struct _VI_WRAP_CSI_MODE_CTL_S
{
        unsigned char    mipi_csi_0_mode;
        unsigned char    mipi_csi_1_mode;
        unsigned char    mipi_dphy_mode;
        unsigned char    mipi_csi01_dbg_sel;
		
   //     unsigned char    isp_4k_clk_sel;
        unsigned char    isp_2k_clk_sel;
        unsigned char    isp_r_2k_clk_sel;
        unsigned char    tof_clk_sel;
		
        unsigned char    csi_0_sony_dol_en;
        unsigned char    dvp_clk_0_mode;
} VI_WRAP_CSI_MODE_CTL_S;

typedef struct _VI_WRAP_ISP_CH_SEL_S
{
        unsigned char    isp_4k_l_ch_sel;
        unsigned char    isp_4k_m_ch_sel;
        unsigned char    isp_4k_s_ch_sel;
        unsigned char    isp_2k_l_ch_sel;
        unsigned char    isp_2k_m_ch_sel;
        unsigned char    isp_2k_s_ch_sel;
        unsigned char    isp_r_2k_ch_sel;
        unsigned char    isp_3d_ch_sel;
} VI_WRAP_ISP_CH_SEL_S;

typedef struct _VI_WRAP_CLOCK_CTL_S
{
        unsigned char    csi_00_pixel_clk_en;
        unsigned char    csi_01_pixel_clk_en;
        unsigned char    csi_02_pixel_clk_en;
        unsigned char    csi_10_pixel_clk_en;
        
        unsigned char    csi_11_pixel_clk_en;
        unsigned char    csi_12_pixel_clk_en;
        unsigned char    dvp_0_pixel_clk_en;
        unsigned char    dvp_1_pixel_clk_en;
        
        unsigned char    csi_00_dma_clk_en;
        unsigned char    csi_01_dma_clk_en;
        unsigned char    csi_02_dma_clk_en;
        unsigned char    csi_10_dma_clk_en;
        
        unsigned char    csi_11_dma_clk_en;
        unsigned char    csi_12_dma_clk_en;
        unsigned char    dvp_0_dma_clk_en;
        unsigned char    dvp_1_dma_clk_en;
        
        unsigned char    axi_wr_ch_clk_en;
        unsigned char    axi_rd_ch_clk_en;
}VI_WRAP_CLOCK_CTL_S;

typedef struct _VI_WRAP_DMA_ARB_MODE_S
{
        unsigned char    wr_dma_arb_mode;
        unsigned char    rd_dma_arb_mode;
} VI_WRAP_DMA_ARB_MODE_S;

typedef struct _VI_WRAP_DMA_WR_WEIGHT_0_S
{
        unsigned char    vi_dma_ch0_wr_weight;
        unsigned char    vi_dma_ch1_wr_weight;
        unsigned char    vi_dma_ch2_wr_weight;
        unsigned char    vi_dma_ch3_wr_weight;
} VI_WRAP_DMA_WR_WEIGHT_0_S;

typedef struct _VI_WRAP_DMA_WR_WEIGHT_1_S
{
        unsigned char    vi_dma_ch4_wr_weight;
        unsigned char    vi_dma_ch5_wr_weight;
        unsigned char    vi_dma_ch6_wr_weight;
        unsigned char    vi_dma_ch7_wr_weight;
} VI_WRAP_DMA_WR_WEIGHT_1_S;

typedef struct _VI_WRAP_DMA_RD_WEIGHT_0_S
{
        unsigned char    vi_dma_ch0_rd_weight;
        unsigned char    vi_dma_ch1_rd_weight;
        unsigned char    vi_dma_ch2_rd_weight;
        unsigned char    vi_dma_ch3_rd_weight;
} VI_WRAP_DMA_RD_WEIGHT_0_S;

typedef struct _VI_WRAP_DMA_RD_WEIGHT_1_S
{
        unsigned char    vi_dma_ch4_rd_weight;
        unsigned char    vi_dma_ch5_rd_weight;
        unsigned char    vi_dma_ch6_rd_weight;
        unsigned char    vi_dma_ch7_rd_weight;
}VI_WRAP_DMA_RD_WEIGHT_1_S;

typedef struct _VI_WRAP_DMA_WR_PRIORITY_S
{
        unsigned char    vi_dma_ch0_wr_priority;
        unsigned char    vi_dma_ch1_wr_priority;
        unsigned char    vi_dma_ch2_wr_priority;
        unsigned char    vi_dma_ch3_wr_priority;
        
        unsigned char    vi_dma_ch4_wr_priority;
        unsigned char    vi_dma_ch5_wr_priority;
        unsigned char    vi_dma_ch6_wr_priority;
        unsigned char    vi_dma_ch7_wr_priority;
} VI_WRAP_DMA_WR_PRIORITY_S;

typedef struct _VI_WRAP_DMA_RD_PRIORITY_S
{
        unsigned char    vi_dma_ch0_rd_priority;
        unsigned char    vi_dma_ch1_rd_priority;
        unsigned char    vi_dma_ch2_rd_priority;
        unsigned char    vi_dma_ch3_rd_priority;
        
        unsigned char    vi_dma_ch4_rd_priority;
        unsigned char    vi_dma_ch5_rd_priority;
        unsigned char    vi_dma_ch6_rd_priority;
        unsigned char    vi_dma_ch7_rd_priority;
} VI_WRAP_DMA_RD_PRIORITY_S;

typedef struct _VI_WRAP_DMA_WR_CH_ID_S
{
        unsigned char    vi_dma_wr_ch0_id;
        unsigned char    vi_dma_wr_ch1_id;
        unsigned char    vi_dma_wr_ch2_id;
        unsigned char    vi_dma_wr_ch3_id;
        
        unsigned char    vi_dma_wr_ch4_id;
        unsigned char    vi_dma_wr_ch5_id;
        unsigned char    vi_dma_wr_ch6_id;
        unsigned char    vi_dma_wr_ch7_id;
} VI_WRAP_DMA_WR_CH_ID_S;

typedef struct _VI_WRAP_DMA_RD_CH_ID_S
{
        unsigned char   vi_dma_rd_ch0_id;
        unsigned char   vi_dma_rd_ch1_id;
        unsigned char   vi_dma_rd_ch2_id;
        unsigned char   vi_dma_rd_ch3_id;
        unsigned char   vi_dma_rd_ch4_id;
        unsigned char   vi_dma_rd_ch5_id;
        unsigned char   vi_dma_rd_ch6_id;
        unsigned char   vi_dma_rd_ch7_id;
} VI_WRAP_DMA_RD_CH_ID_S;

typedef struct _VI_WRAP_DMA_ATTR_S 
{
    VI_WRAP_DMA_ARB_MODE_S          stDmaArbMode;
    VI_WRAP_DMA_WR_WEIGHT_0_S       stWrChWeight0;
    VI_WRAP_DMA_WR_WEIGHT_1_S       stWrChWeight1;
    VI_WRAP_DMA_RD_WEIGHT_0_S       stRdChWeight0;
    VI_WRAP_DMA_RD_WEIGHT_1_S       stRdChWeight1;
    VI_WRAP_DMA_WR_PRIORITY_S       stWrChPriority;
    VI_WRAP_DMA_RD_PRIORITY_S       stRdChPriority;
    VI_WRAP_DMA_WR_CH_ID_S          stWriteChId;
    VI_WRAP_DMA_RD_CH_ID_S          stReadChId; 
} VI_WRAP_DMA_ATTR_S;

typedef struct _VI_WRAP_CFG_DONE_S 
{
    unsigned int vi_wrap_config_done;
    unsigned int vi_wrap_wp_clr;
}VI_WRAP_CFG_DONE_S;

typedef struct _VI_WRAP_ATTR_S 
{
    VI_WRAP_RESET_CTL_S             stRestCtl;
    VI_WRAP_CSI_MODE_CTL_S          stWrapCsiCtl;
    VI_WRAP_ISP_CH_SEL_S            stWrapIspChSel;
    VI_WRAP_CLOCK_CTL_S             stWarpClockCtl;
    VI_WRAP_DMA_ATTR_S              stWrapDmaAttr;
    VI_WRAP_CFG_DONE_S              stWrapCfgDone;
} VI_WRAP_ATTR_S;

int VI_DRV_WRAP_Remap(void);
int VI_DRV_SetWrap(VI_WRAP_ATTR_S *pstViWrapAttr);
//debug
unsigned int VI_DRV_WRAP_GetWrapRegsVal(void);
#endif /*_VI_WRAP_DRV_DEF_H_*/
