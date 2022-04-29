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
 * vi_wrap_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _VI_WRAP_REG_H_
#define _VI_WRAP_REG_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csi_0_0_rst                    : 1   ; /* [0 ]      */
        unsigned int    csi_0_1_rst                    : 1   ; /* [1 ]      */
        unsigned int    csi_0_2_rst                    : 1   ; /* [2 ]      */
        unsigned int    csi_1_0_rst                    : 1   ; /* [3 ]      */
        unsigned int    csi_1_1_rst                    : 1   ; /* [4 ]      */
        unsigned int    csi_1_2_rst                    : 1   ; /* [5 ]      */
        unsigned int    dvp_0_rst                      : 1   ; /* [6 ]      */
        unsigned int    dvp_1_rst                      : 1   ; /* [7 ]      */
        unsigned int    axi_wr_ch_rst                  : 1   ; /* [8 ]      */
        unsigned int    axi_rd_ch_rst                  : 1   ; /* [9 ]      */
        unsigned int    reserved0                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_SWRST_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mipi_csi_0_mode                : 1   ; /* [0 ]      */
        unsigned int    mipi_csi_1_mode                : 1   ; /* [1 ]      */
        unsigned int    mipi_dphy_mode                 : 1   ; /* [2 ]      */
        unsigned int    mipi_csi01_dbg_sel             : 1   ; /* [3 ]      */
        unsigned int    isp_2k_clk_sel                 : 2   ; /* [5..4 ]   */
        unsigned int    isp_r_2k_clk_sel               : 2   ; /* [7..6 ]   */
        unsigned int    csi_0_sony_dol_en              : 1   ; /* [8 ]      */
        unsigned int    reserved0              		   : 3   ; /* [11..9 ]  */
        unsigned int    tof_clk_sel                    : 2   ; /* [13..12 ] */
        unsigned int    reserved1                      : 2   ; /* [15..14 ] */
        unsigned int    dvp_clk_0_mode                 : 1   ; /* [16 ]     */
		unsigned int    reserved2                      : 15  ; /* [31..17]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_CSI_MODE_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    isp_4k_l_ch_sel                : 4   ; /* [3 ..0 ]  */
        unsigned int    isp_4k_m_ch_sel                : 4   ; /* [7 ..4 ]  */
        unsigned int    isp_4k_s_ch_sel                : 4   ; /* [11..8 ]  */
        unsigned int    isp_2k_l_ch_sel                : 4   ; /* [15..12]  */
        unsigned int    isp_2k_m_ch_sel                : 4   ; /* [19..16]  */
        unsigned int    isp_2k_s_ch_sel                : 4   ; /* [23..20]  */
        unsigned int    isp_r_2k_ch_sel                : 4   ; /* [27..24]  */
        unsigned int    isp_3d_ch_sel                  : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_ISP_CH_SEL;


typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csi_00_pixel_clk_en            : 1   ; /* [0 ]      */
        unsigned int    csi_01_pixel_clk_en            : 1   ; /* [1 ]      */
        unsigned int    csi_02_pixel_clk_en            : 1   ; /* [2 ]      */
        unsigned int    csi_10_pixel_clk_en            : 1   ; /* [3 ]      */
        unsigned int    csi_11_pixel_clk_en            : 1   ; /* [4 ]      */
        unsigned int    csi_12_pixel_clk_en            : 1   ; /* [5 ]      */
        unsigned int    dvp_0_pixel_clk_en             : 1   ; /* [6 ]      */
        unsigned int    dvp_1_pixel_clk_en             : 1   ; /* [7 ]      */
        unsigned int    csi_00_dma_clk_en              : 1   ; /* [8 ]      */
        unsigned int    csi_01_dma_clk_en              : 1   ; /* [9 ]      */
        unsigned int    csi_02_dma_clk_en              : 1   ; /* [10]      */
        unsigned int    csi_10_dma_clk_en              : 1   ; /* [11]      */
        unsigned int    csi_11_dma_clk_en              : 1   ; /* [12]      */
        unsigned int    csi_12_dma_clk_en              : 1   ; /* [13]      */
        unsigned int    dvp_0_dma_clk_en               : 1   ; /* [14]      */
        unsigned int    dvp_1_dma_clk_en               : 1   ; /* [15]      */
        unsigned int    axi_wr_ch_clk_en               : 1   ; /* [16]      */
        unsigned int    axi_rd_ch_clk_en               : 1   ; /* [17]      */
        unsigned int    reserved0                      : 14  ; /* [31..18]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_CLOCK_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wr_dma_arb_mode                : 1   ; /* [0 ]      */
        unsigned int    rd_dma_arb_mode                : 1   ; /* [1 ]      */
        unsigned int    reserved0                      : 30  ; /* [31..2 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_ARB_MODE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch0_wr_weight           : 8   ; /* [7 ..0 ]  */
        unsigned int    vi_dma_ch1_wr_weight           : 8   ; /* [15..8 ]  */
        unsigned int    vi_dma_ch2_wr_weight           : 8   ; /* [23..16]  */
        unsigned int    vi_dma_ch3_wr_weight           : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_WR_WEIGHT_0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch4_wr_weight           : 8   ; /* [7 ..0 ]  */
        unsigned int    vi_dma_ch5_wr_weight           : 8   ; /* [15..8 ]  */
        unsigned int    vi_dma_ch6_wr_weight           : 8   ; /* [23..16]  */
        unsigned int    vi_dma_ch7_wr_weight           : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_WR_WEIGHT_1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch0_rd_weight           : 8   ; /* [7 ..0 ]  */
        unsigned int    vi_dma_ch1_rd_weight           : 8   ; /* [15..8 ]  */
        unsigned int    vi_dma_ch2_rd_weight           : 8   ; /* [23..16]  */
        unsigned int    vi_dma_ch3_rd_weight           : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_RD_WEIGHT_0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch4_rd_weight           : 8   ; /* [7 ..0 ]  */
        unsigned int    vi_dma_ch5_rd_weight           : 8   ; /* [15..8 ]  */
        unsigned int    vi_dma_ch6_rd_weight           : 8   ; /* [23..16]  */
        unsigned int    vi_dma_ch7_rd_weight           : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_RD_WEIGHT_1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch0_wr_priority         : 4   ; /* [3 ..0 ]  */
        unsigned int    vi_dma_ch1_wr_priority         : 4   ; /* [7 ..4 ]  */
        unsigned int    vi_dma_ch2_wr_priority         : 4   ; /* [11..8 ]  */
        unsigned int    vi_dma_ch3_wr_priority         : 4   ; /* [15..12]  */
        unsigned int    vi_dma_ch4_wr_priority         : 4   ; /* [19..16]  */
        unsigned int    vi_dma_ch5_wr_priority         : 4   ; /* [23..20]  */
        unsigned int    vi_dma_ch6_wr_priority         : 4   ; /* [27..24]  */
        unsigned int    vi_dma_ch7_wr_priority         : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_WR_PRIORITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_ch0_rd_priority         : 4   ; /* [3 ..0 ]  */
        unsigned int    vi_dma_ch1_rd_priority         : 4   ; /* [7 ..4 ]  */
        unsigned int    vi_dma_ch2_rd_priority         : 4   ; /* [11..8 ]  */
        unsigned int    vi_dma_ch3_rd_priority         : 4   ; /* [15..12]  */
        unsigned int    vi_dma_ch4_rd_priority         : 4   ; /* [19..16]  */
        unsigned int    vi_dma_ch5_rd_priority         : 4   ; /* [23..20]  */
        unsigned int    vi_dma_ch6_rd_priority         : 4   ; /* [27..24]  */
        unsigned int    vi_dma_ch7_rd_priority         : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_RD_PRIORITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_wr_ch0_id               : 4   ; /* [3 ..0 ]  */
        unsigned int    vi_dma_wr_ch1_id               : 4   ; /* [7 ..4 ]  */
        unsigned int    vi_dma_wr_ch2_id               : 4   ; /* [11..8 ]  */
        unsigned int    vi_dma_wr_ch3_id               : 4   ; /* [15..12]  */
        unsigned int    vi_dma_wr_ch4_id               : 4   ; /* [19..16]  */
        unsigned int    vi_dma_wr_ch5_id               : 4   ; /* [23..20]  */
        unsigned int    vi_dma_wr_ch6_id               : 4   ; /* [27..24]  */
        unsigned int    vi_dma_wr_ch7_id               : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_WR_CH_ID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_rd_ch0_id               : 4   ; /* [3 ..0 ]  */
        unsigned int    vi_dma_rd_ch1_id               : 4   ; /* [7 ..4 ]  */
        unsigned int    vi_dma_rd_ch2_id               : 4   ; /* [11..8 ]  */
        unsigned int    vi_dma_rd_ch3_id               : 4   ; /* [15..12]  */
        unsigned int    vi_dma_rd_ch4_id               : 4   ; /* [19..16]  */
        unsigned int    vi_dma_rd_ch5_id               : 4   ; /* [23..20]  */
        unsigned int    vi_dma_rd_ch6_id               : 4   ; /* [27..24]  */
        unsigned int    vi_dma_rd_ch7_id               : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_RD_CH_ID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_dma_y_wr_frm_counter_clear  : 1   ; /* [0 ]      */
        unsigned int    vi_dma_y_wr_fifo_err_counter_clear : 1   ; /* [1 ]      */
        unsigned int    vi_dma_y_wr_max_bw_info_clear  : 1   ; /* [2 ]      */
        unsigned int    vi_dma_y_wr_total_bw_info_clear : 1   ; /* [3 ]      */
        unsigned int    reserved0                      : 4   ; /* [7 ..4 ]  */
        unsigned int    vi_dma_uv_wr_frm_counter_clear : 1   ; /* [8 ]      */
        unsigned int    vi_dma_uv_wr_fifo_err_counter_clear : 1   ; /* [9 ]      */
        unsigned int    vi_dma_uv_wr_max_bw_info_clear : 1   ; /* [10]      */
        unsigned int    vi_dma_uv_wr_total_bw_info_clear : 1   ; /* [11]      */
        unsigned int    reserved1                      : 4   ; /* [15..12]  */
        unsigned int    vi_dma_raw_rd_frm_counter_clear : 1   ; /* [16]      */
        unsigned int    vi_dma_raw_rd_fifo_err_counter_clear : 1   ; /* [17]      */
        unsigned int    vi_dma_raw_rd_max_bw_info_clear : 1   ; /* [18]      */
        unsigned int    vi_dma_raw_rd_total_bw_info_clear : 1   ; /* [19]      */
        unsigned int    reserved2                      : 4   ; /* [23..20]  */
        unsigned int    vi_axi_wr_ch_rst_req           : 1   ; /* [24]      */
        unsigned int    vi_axi_rd_ch_rst_req           : 1   ; /* [25]      */
        unsigned int    reserved3                      : 2   ; /* [27..26]  */
        unsigned int    vi_axi_wr_ch_state             : 1   ; /* [28]      */
        unsigned int    vi_axi_rd_ch_state             : 1   ; /* [29]      */
        unsigned int    reserved4                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_DMA_AXI_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_wrap_config_done            : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 15  ; /* [15..1 ]  */
        unsigned int    vi_sens_reg_wr_protect         : 1   ; /* [16]      */
        unsigned int    vi_int_polarity                : 1   ; /* [17]      */
        unsigned int    reserved1                      : 14  ; /* [31..18]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WRAP_CONFIG_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    csi_0_host_int                 : 1   ; /* [0 ]      */
        unsigned int    csi_0_host_err_int             : 1   ; /* [1 ]      */
        unsigned int    csi_1_host_int                 : 1   ; /* [2 ]      */
        unsigned int    csi_1_host_err_int             : 1   ; /* [3 ]      */
        unsigned int    csi_0_ctrl_0_int               : 1   ; /* [4 ]      */
        unsigned int    csi_0_ctrl_1_int               : 1   ; /* [5 ]      */
        unsigned int    csi_0_ctrl_2_int               : 1   ; /* [6 ]      */
        unsigned int    dvp_0_ctrl_int                 : 1   ; /* [7 ]      */
        unsigned int    csi_1_ctrl_0_int               : 1   ; /* [8 ]      */
        unsigned int    csi_1_ctrl_1_int               : 1   ; /* [9 ]      */
        unsigned int    csi_1_ctrl_2_int               : 1   ; /* [10]      */
        unsigned int    dvp_1_ctrl_int                 : 1   ; /* [11]      */
        unsigned int    reserved0                      : 4   ; /* [15..12]  */
        unsigned int    csi_0_host_mask                : 1   ; /* [16]      */
        unsigned int    csi_0_host_err_mask            : 1   ; /* [17]      */
        unsigned int    csi_1_host_mask                : 1   ; /* [18]      */
        unsigned int    csi_1_host_err_mask            : 1   ; /* [19]      */
        unsigned int    csi_0_ctrl_0_mask              : 1   ; /* [20]      */
        unsigned int    csi_0_ctrl_1_mask              : 1   ; /* [21]      */
        unsigned int    csi_0_ctrl_2_mask              : 1   ; /* [22]      */
        unsigned int    dvp_0_ctrl_mask                : 1   ; /* [23]      */
        unsigned int    csi_1_ctrl_0_mask              : 1   ; /* [24]      */
        unsigned int    csi_1_ctrl_1_mask              : 1   ; /* [25]      */
        unsigned int    csi_1_ctrl_2_mask              : 1   ; /* [26]      */
        unsigned int    dvp_1_ctrl_mask                : 1   ; /* [27]      */
        unsigned int    reserved1                      : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_VI_WARP_INT_CTL;


#define  VI_WRAP_SWRST_CTL     		(0x0000)
#define  VI_WRAP_CSI_MODE_CTL     	(0x0004)
#define  VI_WRAP_ISP_CH_SEL     	(0x0008)
#define  VI_WRAP_CLOCK_CTL     		(0x000C)
									
#define  VI_WRAP_DMA_ARB_MODE     	(0x0020)
#define  VI_WRAP_DMA_WR_WEIGHT_0    (0x0024)
#define  VI_WRAP_DMA_WR_WEIGHT_1    (0x0028)
#define  VI_WRAP_DMA_RD_WEIGHT_0    (0x002C)
#define  VI_WRAP_DMA_RD_WEIGHT_1    (0x0030)
#define  VI_WRAP_DMA_WR_PRIORITY    (0x0034)
#define  VI_WRAP_DMA_RD_PRIORITY    (0x0038)
#define  VI_WRAP_DMA_WR_CH_ID     	(0x003C)
#define  VI_WRAP_DMA_RD_CH_ID     	(0x0040)
									
#define  VI_WRAP_DMA_AXI_CTL     	(0x0074)
#define  VI_WRAP_CONFIG_CTL     	(0x0078)
#define  VI_WARP_INT_CTL     		(0x007C)


#endif  /*_VI_WRAP_REG_H_*/

