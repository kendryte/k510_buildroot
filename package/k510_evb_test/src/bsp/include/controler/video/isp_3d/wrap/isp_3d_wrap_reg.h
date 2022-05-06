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

#ifndef _ISP_3D_WRAP_REG_DEF_H_
#define _ISP_3D_WRAP_REG_DEF_H_

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
        unsigned int    tof_dma_chl_sel                : 1  ; /* [3 ]  */
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

typedef struct _S_TOF_WRAP_REGS_TYPE
{
    volatile U_TOF_WRAP_CTL_SWRST               TOF_WRAP_CTL_SWRST;
    volatile U_TOF_WRAP_DMA_CTL_SWRST           TOF_WRAP_DMA_CTL_SWRST;
    volatile U_TOF_WRAP_CTL_MODE                TOF_WRAP_CTL_MODE;
    volatile U_TOF_WRAP_CTL_CLK_EN              TOF_WRAP_CTL_CLK_EN;
    volatile U_TOF_WRAP_CTL_DMA_EN              TOF_WRAP_CTL_DMA_EN;
    volatile U_TOF_WRAP_CTL_PIXEL_FORMAT_ISP    TOF_WRAP_CTL_PIXEL_FORMAT_ISP;
    volatile U_TOF_WRAP_CTL_PIXEL_FORMAT        TOF_WRAP_CTL_PIXEL_FORMAT;
    volatile U_TOF_WRAP_OUT_SIZE                TOF_WRAP_OUT_SIZE;
    volatile unsigned int                     reserved1[7];
    volatile U_TOF_WRAP_DMA_ARB_MODE            TOF_WRAP_DMA_ARB_MODE;
    volatile U_TOF_WRAP_DMA_WR_WEIGHT_0         TOF_WRAP_DMA_WR_WEIGHT_0;
    volatile U_TOF_WRAP_DMA_WR_WEIGHT_1         TOF_WRAP_DMA_WR_WEIGHT_1;
    volatile U_TOF_WRAP_DMA_RD_WEIGHT_0         TOF_WRAP_DMA_RD_WEIGHT_0;
    volatile U_TOF_WRAP_DMA_RD_WEIGHT_1         TOF_WRAP_DMA_RD_WEIGHT_1;
    volatile U_TOF_WRAP_DMA_WR_PRIORITY         TOF_WRAP_DMA_WR_PRIORITY;
    volatile U_TOF_WRAP_DMA_RD_PRIORITY         TOF_WRAP_DMA_RD_PRIORITY;
    volatile U_TOF_DMA_WR_CH_ID                 TOF_DMA_WR_CH_ID;
    volatile U_TOF_DMA_RD_CH_ID                 TOF_DMA_RD_CH_ID;
    volatile unsigned int                     reserved2[14];
    volatile U_TOF_WRAP_DEPTH_BUF0_BASE         TOF_WRAP_DEPTH_BUF0_BASE;
    volatile U_TOF_WRAP_DEPTH_BUF1_BASE         TOF_WRAP_DEPTH_BUF1_BASE;
    volatile U_TOF_WRAP_GRAY_BUF0_BASE          TOF_WRAP_GRAY_BUF0_BASE;
    volatile U_TOF_WRAP_GRAY_BUF1_BASE          TOF_WRAP_GRAY_BUF1_BASE;
    volatile U_TOF_WRAP_BUF_STRIDE              TOF_WRAP_BUF_STRIDE;
    volatile unsigned int                     reserved3[5];
    volatile U_TOF_WRAP_DMA_CH0_CFG             TOF_WRAP_DMA_CH0_CFG;
    volatile U_TOF_WRAP_DMA_CH1_CFG             TOF_WRAP_DMA_CH1_CFG;
    volatile U_TOF_WRAP_DMA_CH0_ERR_DEC_CFG     TOF_WRAP_DMA_CH0_ERR_DEC_CFG;
    volatile U_TOF_WRAP_DMA_CH1_ERR_DEC_CFG     TOF_WRAP_DMA_CH1_ERR_DEC_CFG;
    volatile U_TOF_WRAP_DMA_CH0_ERR_STATUS      TOF_WRAP_DMA_CH0_ERR_STATUS;
    volatile U_TOF_WRAP_DMA_CH1_ERR_STATUS      TOF_WRAP_DMA_CH1_ERR_STATUS;
    volatile U_TOF_WRAP_AXI_CTL                 TOF_WRAP_AXI_CTL;
    volatile U_TOF_WRAP_COFIG_DONE              TOF_WRAP_COFIG_DONE;
    volatile U_TOF_WRAP_INT_CTL                 TOF_WRAP_INT_CTL;
    volatile unsigned int                     reserved4[167];
    volatile U_TOF_VERSION                      TOF_VERSION;
    volatile U_TOF_RELEASE_INFO                 TOF_RELEASE_INFO;
    volatile unsigned int                     reserved5[30];
} S_TOF_WRAP_REGS_TYPE;

//S_TOF_WRAP_REGS_TYPE *pstRegs;

//#define TOF_WRAP_REG_ADDR(pstRegs,reg_name) container_of(pstRegs,S_TOF_WRAP_REGS_TYPE,reg_name)

int TOF_WRAP_DRV_SET_WrapCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCtlClkEn(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCtlMode(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCtlDmaEn(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCtlPixelFormatISP(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCtlPixelFormat(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapOutSize(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaArbMode(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaWrWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaWrWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaRdWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaRdWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaWrPriority(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaRdPriority(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_DmaWrChId(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_DmaRdChId(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh0Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh0ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh0ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh1Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh1ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDmaCh1ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDepthBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDepthBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapGrayBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapGrayBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapBufStride(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDepthBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapDepthBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapAxiCtl(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapCofigDone(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TOF_WRAP_DRV_SET_WrapIntCtl(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
//
int TOF_WRAP_DRV_GET_WrapCofigDone(S_TOF_WRAP_REGS_TYPE *pstRegs);
int TOF_WRAP_DRV_GET_WrapIntCtl(S_TOF_WRAP_REGS_TYPE *pstRegs);
int TOF_WRAP_DRV_GET_Version(S_TOF_WRAP_REGS_TYPE *pstRegs);
int TOF_WRAP_DRV_GET_ReleaseInfo(S_TOF_WRAP_REGS_TYPE *pstRegs);
//debug
int TOF_WRAP_DRV_GET_WrapRegsVal(S_TOF_WRAP_REGS_TYPE *pstRegs);
#endif  /*_ISP_3D_WRAP_REG_DEF_H_*/

