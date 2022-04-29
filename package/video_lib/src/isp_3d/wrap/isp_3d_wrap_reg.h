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
 * isp_3d_wrap_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _ISP_3D_WRAP_REG_H_
#define _ISP_3D_WRAP_REG_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_wrap_com_pipe_rst          : 1   ; /* [0 ]      */
        unsigned int    tof_wrap_cfg_pipe_rst          : 1   ; /* [1 ]      */
        unsigned int    tof_core_com_pipe_rst          : 1   ; /* [2 ]      */
        unsigned int    tof_core_cfg_pipe_rst          : 1   ; /* [3 ]      */
        unsigned int    tof_out_depth_pipe_rst         : 1   ; /* [4 ]      */
        unsigned int    tof_out_gray_pipe_rst          : 1   ; /* [5 ]      */
        unsigned int    tof_pixel_clk_pipe_rst         : 1   ; /* [6 ]      */
        unsigned int    tof_pixel_div6_clk_pipe_rst    : 1   ; /* [7 ]      */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_CTL_SWRST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_depth_dma_ch_rst           : 1   ; /* [0 ]      */
        unsigned int    tof_gray_dma_ch_rst            : 1   ; /* [1 ]      */
        unsigned int    tof_axi_wr_ch_rst              : 1   ; /* [2 ]      */
        unsigned int    tof_axi_rd_ch_rst              : 1   ; /* [3 ]      */
        unsigned int    reserved0                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CTL_SWRST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_out_ch_sel                 : 2   ; /* [1 ..0 ]  */
        unsigned int    tof_dvp_input_ch_type          : 1   ; /* [2 ]      */
        unsigned int    tof_dma_chl_sel                      : 1  ; /* [3 ]  */
        unsigned int    reserved1                      : 28  ; /* [31..4 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_CTL_MODE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_wrap_com_clk_en            : 1   ; /* [0 ]      */
        unsigned int    tof_wrap_cfg_clk_en            : 1   ; /* [1 ]      */
        unsigned int    tof_core_com_clk_en            : 1   ; /* [2 ]      */
        unsigned int    tof_core_cfg_clk_en            : 1   ; /* [3 ]      */
        unsigned int    tof_out_depth_clk_en           : 1   ; /* [4 ]      */
        unsigned int    tof_out_gray_clk_en            : 1   ; /* [5 ]      */
        unsigned int    tof_core_sensor_clk_en         : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7 ]  	*/
        unsigned int    tof_axi_wr_clk_en              : 1   ; /* [8 ]      */
        unsigned int    tof_axi_rd_clk_en              : 1   ; /* [9 ]      */
        unsigned int    reserved1                      : 22  ; /* [31..10]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_CTL_CLK_EN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_wrap_dma_out_en            : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} /*
*
*/U_TOF_WRAP_CTL_DMA_EN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ctrl_pixel_format_isp            : 32   ; /* [31 ..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_CTL_PIXEL_FORMAT_ISP;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_out_pixel_format           : 8   ; /* [7 ..0 ]  */
        unsigned int    reserved0                      : 24  ; /* [31..8 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_CTL_PIXEL_FORMAT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_out_v_size                 : 14  ; /* [13..0 ]  */
        unsigned int    reserved0                      : 2   ; /* [15..14]  */
        unsigned int    tof_out_h_size                 : 14  ; /* [29..16]  */
        unsigned int    reserved1                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_OUT_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_rd_arb_mode            : 1   ; /* [0 ]      */
        unsigned int    tof_dma_wr_arb_mode            : 1   ; /* [1 ]      */
        unsigned int    reserved0                      : 30  ; /* [31..2 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_ARB_MODE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch0_wr_weight          : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_dma_ch1_wr_weight          : 8   ; /* [15..8 ]  */
        unsigned int    tof_dma_ch2_wr_weight          : 8   ; /* [23..16]  */
        unsigned int    tof_dma_ch3_wr_weight          : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_WR_WEIGHT_0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch4_wr_weight          : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_dma_ch5_wr_weight          : 8   ; /* [15..8 ]  */
        unsigned int    tof_dma_ch6_wr_weight          : 8   ; /* [23..16]  */
        unsigned int    tof_dma_ch7_wr_weight          : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_WR_WEIGHT_1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch0_rd_weight          : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_dma_ch1_rd_weight          : 8   ; /* [15..8 ]  */
        unsigned int    tof_dma_ch2_rd_weight          : 8   ; /* [23..16]  */
        unsigned int    tof_dma_ch3_rd_weight          : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_RD_WEIGHT_0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch4_rd_weight          : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_dma_ch5_rd_weight          : 8   ; /* [15..8 ]  */
        unsigned int    tof_dma_ch6_rd_weight          : 8   ; /* [23..16]  */
        unsigned int    tof_dma_ch7_rd_weight          : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_RD_WEIGHT_1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch0_wr_priority        : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_dma_ch1_wr_priority        : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_dma_ch2_wr_priority        : 4   ; /* [11..8 ]  */
        unsigned int    tof_dma_ch3_wr_priority        : 4   ; /* [15..12]  */
        unsigned int    tof_dma_ch4_wr_priority        : 4   ; /* [19..16]  */
        unsigned int    tof_dma_ch5_wr_priority        : 4   ; /* [23..20]  */
        unsigned int    tof_dma_ch6_wr_priority        : 4   ; /* [27..24]  */
        unsigned int    tof_dma_ch7_wr_priority        : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_WR_PRIORITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_ch0_rd_priority        : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_dma_ch1_rd_priority        : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_dma_ch2_rd_priority        : 4   ; /* [11..8 ]  */
        unsigned int    tof_dma_ch3_rd_priority        : 4   ; /* [15..12]  */
        unsigned int    tof_dma_ch4_rd_priority        : 4   ; /* [19..16]  */
        unsigned int    tof_dma_ch5_rd_priority        : 4   ; /* [23..20]  */
        unsigned int    tof_dma_ch6_rd_priority        : 4   ; /* [27..24]  */
        unsigned int    tof_dma_ch7_rd_priority        : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_RD_PRIORITY;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_wr_ch0_id              : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_dma_wr_ch1_id              : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_dma_wr_ch2_id              : 4   ; /* [11..8 ]  */
        unsigned int    tof_dma_wr_ch3_id              : 4   ; /* [15..12]  */
        unsigned int    tof_dma_wr_ch4_id              : 4   ; /* [19..16]  */
        unsigned int    tof_dma_wr_ch5_id              : 4   ; /* [23..20]  */
        unsigned int    tof_dma_wr_ch6_id              : 4   ; /* [27..24]  */
        unsigned int    tof_dma_wr_ch7_id              : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_DMA_WR_CH_ID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_dma_rd_ch0_id              : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_dma_rd_ch1_id              : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_dma_rd_ch2_id              : 4   ; /* [11..8 ]  */
        unsigned int    tof_dma_rd_ch3_id              : 4   ; /* [15..12]  */
        unsigned int    tof_dma_rd_ch4_id              : 4   ; /* [19..16]  */
        unsigned int    tof_dma_rd_ch5_id              : 4   ; /* [23..20]  */
        unsigned int    tof_dma_rd_ch6_id              : 4   ; /* [27..24]  */
        unsigned int    tof_dma_rd_ch7_id              : 4   ; /* [31..28]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_DMA_RD_CH_ID;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_depth_buf0_base            : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DEPTH_BUF0_BASE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_depth_buf1_base            : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DEPTH_BUF1_BASE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_gray_buf0_base             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_GRAY_BUF0_BASE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_gray_buf1_base             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_GRAY_BUF1_BASE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_depth_line_stride          : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    tof_gray_line_stride           : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_BUF_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch0_wr_outst               : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_ch0_rd_outst               : 4   ; /* [7 ..4 ]  */
        unsigned int    reserved0                      : 4   ; /* [11..8 ]  */
        unsigned int    tof_ch0_wr_burstl              : 1   ; /* [12]      */
        unsigned int    tof_ch0_rd_burstl              : 1   ; /* [13]      */
        unsigned int    tof_ch0_y_uv_noncon_en         : 1   ; /* [14]      */
        unsigned int    tof_ch0_y_uv_swap_en           : 1   ; /* [15]      */
        unsigned int    tof_ch0_wr_int_line_num        : 12  ; /* [27..16]  */
        unsigned int    tof_ch0_wr_err_dec_en          : 1   ; /* [28]      */
        unsigned int    tof_ch0_rd_err_dec_en          : 1   ; /* [29]      */
        unsigned int    reserved1                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH0_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch1_wr_outst               : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_ch1_rd_outst               : 4   ; /* [7 ..4 ]  */
        unsigned int    reserved0                      : 4   ; /* [11..8 ]  */
        unsigned int    tof_ch1_wr_burstl              : 1   ; /* [12]      */
        unsigned int    tof_ch1_rd_burstl              : 1   ; /* [13]      */
        unsigned int    tof_ch1_y_uv_noncon_en         : 1   ; /* [14]      */
        unsigned int    tof_ch1_y_uv_swap_en           : 1   ; /* [15]      */
        unsigned int    tof_ch1_wr_int_line_num        : 12  ; /* [27..16]  */
        unsigned int    tof_ch1_wr_err_dec_en          : 1   ; /* [28]      */
        unsigned int    tof_ch1_rd_err_dec_en          : 1   ; /* [29]      */
        unsigned int    reserved1                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH1_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch0_wr_err_dec_unit        : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_ch0_rd_err_dec_unit        : 8   ; /* [15..8 ]  */
        unsigned int    tof_ch0_wr_err_gen_thr         : 8   ; /* [23..16]  */
        unsigned int    tof_ch0_rd_err_gen_thr         : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH0_ERR_DEC_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch1_wr_err_dec_unit        : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_ch1_rd_err_dec_unit        : 8   ; /* [15..8 ]  */
        unsigned int    tof_ch1_wr_err_gen_thr         : 8   ; /* [23..16]  */
        unsigned int    tof_ch1_rd_err_gen_thr         : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH1_ERR_DEC_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch0_err_y_wr_status        : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_ch0_err_uv_wr_status       : 4   ; /* [11..8 ]  */
        unsigned int    reserved1                      : 4   ; /* [15..12]  */
        unsigned int    tof_ch0_err_raw_read_status    : 4   ; /* [19..16]  */
        unsigned int    reserved2                      : 4   ; /* [23..20]  */
        unsigned int    tof_ch0_err_wr_rst_req         : 1   ; /* [24]      */
        unsigned int    tof_ch0_err_rd_rst_req         : 1   ; /* [25]      */
        unsigned int    reserved3                      : 2   ; /* [27..26]  */
        unsigned int    tof_ch0_err_wr_tof_ch_state    : 1   ; /* [28]      */
        unsigned int    tof_ch0_err_rd_tof_ch_state    : 1   ; /* [29]      */
        unsigned int    reserved4                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH0_ERR_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_ch1_err_y_wr_status        : 4   ; /* [3 ..0 ]  */
        unsigned int    reserved0                      : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_ch1_err_uv_wr_status       : 4   ; /* [11..8 ]  */
        unsigned int    reserved1                      : 4   ; /* [15..12]  */
        unsigned int    tof_ch1_err_raw_read_status    : 4   ; /* [19..16]  */
        unsigned int    reserved2                      : 4   ; /* [23..20]  */
        unsigned int    tof_ch1_err_wr_rst_req         : 1   ; /* [24]      */
        unsigned int    tof_ch1_err_rd_rst_req         : 1   ; /* [25]      */
        unsigned int    reserved3                      : 2   ; /* [27..26]  */
        unsigned int    tof_ch1_err_wr_tof_ch_state    : 1   ; /* [28]      */
        unsigned int    tof_ch1_err_rd_tof_ch_state    : 1   ; /* [29]      */
        unsigned int    reserved4                      : 2   ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_DMA_CH1_ERR_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_axi_wr_ch_rst_req          : 1   ; /* [0 ]      */
        unsigned int    tof_axi_rd_ch_rst_req          : 1   ; /* [1 ]      */
        unsigned int    reserved0                      : 6   ; /* [7 ..2 ]  */
        unsigned int    tof_axi_wr_ch_state            : 1   ; /* [8 ]      */
        unsigned int    tof_axi_rd_ch_state            : 1   ; /* [9 ]      */
        unsigned int    reserved1                      : 6   ; /* [15..10]  */
        unsigned int    tof_axi_wr_status              : 3   ; /* [18..16]  */
        unsigned int    tof_axi_wr_swrst_ready         : 1   ; /* [19]      */
        unsigned int    tof_axi_rd_status              : 3   ; /* [22..20]  */
        unsigned int    tof_axi_rd_swrst_ready         : 1   ; /* [23]      */
        unsigned int    reserved2                      : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_AXI_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_wrap_config_done_en        : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 15  ; /* [15..1 ]  */
        unsigned int    tof_sen_reg_pro_en             : 1   ; /* [16]      */
        unsigned int    tof_int_polarity               : 1   ; /* [17]      */
        unsigned int    reserved1                      : 14  ; /* [31..18]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_COFIG_DONE;

typedef union
{
    /* Define the struct bits */
    struct
    {
    //    unsigned int    tof_int_clear                  : 16  ; /* [15..0 ]  */
    //    unsigned int    tof_int_mask                   : 16  ; /* [31..16]  */
          unsigned int    tof_core_int_st_in             : 1   ; /* [0 ]  */
          unsigned int    tof_core_int_st_itc_out        : 1   ; /* [1 ]  */
          unsigned int    tof_core_int_st_demo_out       : 1   ; /* [2 ]  */
          unsigned int    tof_core_int_st_ae_out         : 1   ; /* [3 ]  */
          unsigned int    tof_core_int_st_img_out        : 1   ; /* [4 ]  */
          unsigned int    reserved                       : 3   ; /* [7..5 ]  */
          unsigned int    tof_dma_wr_int_gray_frame      : 1   ; /* [8 ]  */
          unsigned int    tof_dma_wr_int_gray_line       : 1   ; /* [9 ]  */
          unsigned int    tof_dma_wr_int_gray_frame_err  : 1   ; /* [10 ]  */
          unsigned int    tof_dma_wr_int_gray_imm_err    : 1   ; /* [11 ]  */ 
          unsigned int    tof_dma_wr_int_depth_frame      : 1   ; /* [12 ]  */
          unsigned int    tof_dma_wr_int_depth_line       : 1   ; /* [13 ]  */
          unsigned int    tof_dma_wr_int_depth_frame_err  : 1   ; /* [14 ]  */
          unsigned int    tof_dma_wr_int_depth_imm_err    : 1   ; /* [15 ]  */ 
          unsigned int    tof_core_int_st_in_msk          : 1   ; /* [16 ]  */
          unsigned int    tof_core_int_st_itc_out_msk        : 1   ; /* [17 ]  */
          unsigned int    tof_core_int_st_demo_out_msk       : 1   ; /* [18 ]  */
          unsigned int    tof_core_int_st_ae_out_msk         : 1   ; /* [19 ]  */
          unsigned int    tof_core_int_st_img_out_msk       : 1   ; /* [20 ]  */
          unsigned int    reserved1                       : 3   ; /* [23..21]  */
          unsigned int    tof_dma_wr_int_gray_frame_msk      : 1   ; /* [24 ]  */
          unsigned int    tof_dma_wr_int_gray_line_msk       : 1   ; /* [25 ]  */
          unsigned int    tof_dma_wr_int_gray_frame_err_msk  : 1   ; /* [26 ]  */
          unsigned int    tof_dma_wr_int_gray_imm_err_msk    : 1   ; /* [27 ]  */ 
          unsigned int    tof_dma_wr_int_depth_frame_msk      : 1   ; /* [28 ]  */
          unsigned int    tof_dma_wr_int_depth_line_msk       : 1   ; /* [29 ]  */
          unsigned int    tof_dma_wr_int_depth_frame_err_msk  : 1   ; /* [30 ]  */
          unsigned int    tof_dma_wr_int_depth_imm_err_msk    : 1   ; /* [31 ]  */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_WRAP_INT_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_version_minor              : 4   ; /* [3 ..0 ]  */
        unsigned int    tof_version_major              : 4   ; /* [7 ..4 ]  */
        unsigned int    tof_license_version            : 8   ; /* [15..8 ]  */
        unsigned int    reserved0                      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_VERSION;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tof_release_day                : 8   ; /* [7 ..0 ]  */
        unsigned int    tof_release_month              : 8   ; /* [15..8 ]  */
        unsigned int    tof_release_year_low           : 8   ; /* [23..16]  */
        unsigned int    tof_release_year_high          : 8   ; /* [31..24]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_TOF_RELEASE_INFO;

//
#define  TOF_WRAP_CTL_SWRST     		(0x0000)
#define  TOF_WRAP_DMA_CTL_SWRST     	(0x0004)
#define  TOF_WRAP_CTL_MODE     			(0x0008)
#define  TOF_WRAP_CTL_CLK_EN    	    (0x000C)
#define  TOF_WRAP_CTL_DMA_EN    	    (0x0010)
#define  TOF_WRAP_CTL_PIXEL_FORMAT_ISP  (0x0014)
#define  TOF_WRAP_CTL_PIXEL_FORMAT      (0x0018)
#define  TOF_WRAP_OUT_SIZE     			(0x001C)
										
#define  TOF_WRAP_DMA_ARB_MODE     		(0x003C)
#define  TOF_WRAP_DMA_WR_WEIGHT_0     	(0x0040)
#define  TOF_WRAP_DMA_WR_WEIGHT_1     	(0x0044)
#define  TOF_WRAP_DMA_RD_WEIGHT_0     	(0x0048)
#define  TOF_WRAP_DMA_RD_WEIGHT_1     	(0x004C)
#define  TOF_WRAP_DMA_WR_PRIORITY     	(0x0050)
#define  TOF_WRAP_DMA_RD_PRIORITY     	(0x0054)
#define  TOF_DMA_WR_CH_ID     			(0x0058)
#define  TOF_DMA_RD_CH_ID     			(0x005C)
										
#define  TOF_WRAP_DEPTH_BUF0_BASE     	(0x0098)
#define  TOF_WRAP_DEPTH_BUF1_BASE     	(0x009C)
#define  TOF_WRAP_GRAY_BUF0_BASE     	(0x00A0)
#define  TOF_WRAP_GRAY_BUF1_BASE     	(0x00A4)
#define  TOF_WRAP_BUF_STRIDE     		(0x00A8)
										
#define  TOF_WRAP_DMA_CH0_CFG     		(0x00C0)
#define  TOF_WRAP_DMA_CH1_CFG     		(0x00C4)
#define  TOF_WRAP_DMA_CH0_ERR_DEC_CFG   (0x00C8)
#define  TOF_WRAP_DMA_CH1_ERR_DEC_CFG   (0x00CC)
#define  TOF_WRAP_DMA_CH0_ERR_STATUS    (0x00D0)
#define  TOF_WRAP_DMA_CH1_ERR_STATUS    (0x00D4)
#define  TOF_WRAP_AXI_CTL     			(0x00D8)
#define  TOF_WRAP_COFIG_DONE     		(0x00DC)
#define  TOF_WRAP_INT_CTL     			(0x00E0)
										
#define  TOF_VERSION     				(0x0380)
#define  TOF_RELEASE_INFO     			(0x0384)

#endif  /*_ISP_3D_WRAP_REG_H_*/

