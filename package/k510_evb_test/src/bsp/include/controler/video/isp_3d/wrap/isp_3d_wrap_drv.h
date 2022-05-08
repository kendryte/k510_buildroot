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

#ifndef _ISP_3D_WRAP_DRV_DEF_H_
#define _ISP_3D_WRAP_DRV_DEF_H_

#define  TOF_DMA_CH_NUM  8

typedef struct _TOF_WRAP_CTL_SWRST_S
{
    unsigned int  tof_wrap_com_pipe_rst ;
    unsigned int  tof_wrap_cfg_pipe_rst ;
    unsigned int  tof_core_com_pipe_rst ;
    unsigned int  tof_core_cfg_pipe_rst ;
    unsigned int  tof_out_depth_pipe_rst;
    unsigned int  tof_out_gray_pipe_rst ;
    unsigned int  tof_pixel_clk_pipe_rst;
    unsigned int  tof_pixel_div6_clk_pipe_rst;
    unsigned int  tof_depth_dma_ch_rst;
    unsigned int  tof_gray_dma_ch_rst ;
    unsigned int  tof_axi_wr_ch_rst   ;
    unsigned int  tof_axi_rd_ch_rst   ;    
}TOF_WRAP_CTL_SWRST_S;

typedef struct _TOF_WRAP_CTL_MODE_S
{
    unsigned int    tof_out_ch_sel       ;
    unsigned int    tof_dvp_input_ch_type;
    unsigned int    tof_dma_chl_sel;
} TOF_WRAP_CTL_MODE_S;

typedef struct _TOF_WRAP_CTL_CLK_EN_S
{
    unsigned int    tof_wrap_com_clk_en   ;
    unsigned int    tof_wrap_cfg_clk_en   ;
    unsigned int    tof_core_com_clk_en   ;
    unsigned int    tof_core_cfg_clk_en   ;
    unsigned int    tof_out_depth_clk_en  ;
    unsigned int    tof_out_gray_clk_en   ;
    unsigned int    tof_core_sensor_clk_en;
    unsigned int    tof_axi_wr_clk_en     ;
    unsigned int    tof_axi_rd_clk_en     ;
} TOF_WRAP_CTL_CLK_EN_S;

typedef struct _TOF_WRAP_OUT_SIZE_S
{
    unsigned short    tof_out_v_size;
    unsigned short    tof_out_h_size;
} TOF_WRAP_OUT_SIZE_S;

typedef struct _TOF_WRAP_DMA_ARB_MODE_S
{
    unsigned char    tof_dma_rd_arb_mode;
    unsigned char    tof_dma_wr_arb_mode;
} TOF_WRAP_DMA_ARB_MODE_S;

typedef  struct _TOF_WRAP_DMA_CFG_S
{
    unsigned int    tof_wr_outst       ;
    unsigned int    tof_rd_outst       ;
    unsigned int    tof_wr_burstl      ;
    unsigned int    tof_rd_burstl      ;
    unsigned int    tof_y_uv_noncon_en ;
    unsigned int    tof_y_uv_swap_en   ;
    unsigned int    tof_wr_int_line_num;
    unsigned int    tof_wr_err_dec_en  ;
    unsigned int    tof_rd_err_dec_en  ;
} TOF_WRAP_DMA_CFG_S;
											   
typedef struct _TOF_WRAP_DMA_ERR_DEC_CFG_S                                 
{                                         
    unsigned int    tof_wr_err_dec_unit;
    unsigned int    tof_rd_err_dec_unit;
    unsigned int    tof_wr_err_gen_thr ;
    unsigned int    tof_rd_err_gen_thr ;
} TOF_WRAP_DMA_ERR_DEC_CFG_S; 

typedef struct _TOF_WRAP_DMA_MODE_S
{
    TOF_WRAP_DMA_ARB_MODE_S     stDmaArbMode;
    unsigned char               wr_dma_ch_weight[TOF_DMA_CH_NUM];
    unsigned char               rd_dma_ch_weight[TOF_DMA_CH_NUM];
    unsigned char               wr_dma_ch_priority[TOF_DMA_CH_NUM];
    unsigned char               rd_dma_ch_priority[TOF_DMA_CH_NUM];
    unsigned char               wr_dma_ch_id[TOF_DMA_CH_NUM];
    unsigned char               rd_dma_ch_id[TOF_DMA_CH_NUM];
    TOF_WRAP_DMA_CFG_S          stDmaCh0Cfg;
    TOF_WRAP_DMA_ERR_DEC_CFG_S  stDmaCh0ErrCfg;
    TOF_WRAP_DMA_CFG_S          stDmaCh1Cfg;
    TOF_WRAP_DMA_ERR_DEC_CFG_S  stDmaCh1ErrCfg;   
} TOF_WRAP_DMA_MODE_S;

typedef struct _TOF_WRAP_BUF_S
{

    unsigned int    tof_gray_buf0_base;
    unsigned int    tof_gray_buf1_base;
    
    unsigned int    tof_depth_buf0_base;
    unsigned int    tof_depth_buf1_base;
    
    unsigned short    tof_gray_line_stride;
    unsigned short    tof_depth_line_stride;
} TOF_WRAP_BUF_S;

typedef struct _TOF_WRAP_AXI_CTL_S
{
    unsigned int    tof_axi_wr_ch_rst_req ;
    unsigned int    tof_axi_rd_ch_rst_req ;
    unsigned int    tof_axi_wr_swrst_ready;
    unsigned int    tof_axi_rd_swrst_ready;
} TOF_WRAP_AXI_CTL_S;  

typedef struct _TOF_WRAP_COFIG_DONE_S
{
    unsigned int    tof_wrap_config_done_en;
    unsigned int    tof_sen_reg_pro_en     ;
    unsigned int    tof_int_polarity       ;
} TOF_WRAP_COFIG_DONE_S;

typedef struct _TOF_WRAP_INT_CTL_S
{
    unsigned int    tof_core_int_st_in_msk        ;
    unsigned int    tof_core_int_st_itc_out_msk   ;
    unsigned int    tof_core_int_st_demo_out_msk  ;
    unsigned int    tof_core_int_st_ae_out_msk    ;
    unsigned int    tof_core_int_st_img_out_msk   ;
    unsigned int    tof_dma_wr_int_gray_frame_msk ;
    unsigned int    tof_dma_wr_int_gray_line_msk  ;
    unsigned int    tof_dma_wr_int_gray_frame_err_msk ;
    unsigned int    tof_dma_wr_int_gray_imm_err_msk   ;
    unsigned int    tof_dma_wr_int_depth_frame_msk    ;
    unsigned int    tof_dma_wr_int_depth_line_msk     ;
    unsigned int    tof_dma_wr_int_depth_frame_err_msk;
    unsigned int    tof_dma_wr_int_depth_imm_err_msk  ; 
} TOF_WRAP_INT_CTL_S;

typedef struct _TOF_WRAP_ATTR_S
{
    TOF_WRAP_CTL_SWRST_S    stSwRst;
    TOF_WRAP_CTL_MODE_S     stMode;
    TOF_WRAP_CTL_CLK_EN_S   stClkEn;
    unsigned int            tof_wrap_dma_out_en;
    unsigned int            ctrl_pixel_format_isp;
    unsigned int            tof_out_pixel_format;
    TOF_WRAP_OUT_SIZE_S     stOutSize;
    TOF_WRAP_DMA_MODE_S     stDmaMode;
    TOF_WRAP_BUF_S          stBuf;
    TOF_WRAP_AXI_CTL_S      stAxiCtl;
    TOF_WRAP_COFIG_DONE_S   stCfgDone;
    TOF_WRAP_INT_CTL_S      stIntMask;
 
} TOF_WRAP_ATTR_S;

int TOF_DRV_Wrap_Remap(void);
int TOF_DRV_WRAP_SetInt(TOF_WRAP_INT_CTL_S *stIntMask);
int TOF_DRV_setWrap(TOF_WRAP_ATTR_S *tofWrapAttr);
//DEBUG
int TOF_DRV_GetWrapRegsVal(void);
#endif /*_ISP_3D_WRAP_DRV_DEF_H_*/
