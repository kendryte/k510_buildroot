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
#ifndef _VI_PIPE_DRV_DEF_H_
#define _VI_PIPE_DRV_DEF_H_

#include "video/isp_com.h"
//#include "video/vi/vi.h"

//unsigned int  *reg_vi_pipe_base[8]  = {NULL};
//#define VI_DRV_PIPE_REG_CTX(pipeIndex, pstCtx)      { pstCtx = (S_VI_PIPE_REGS_TYPE *)(reg_vi_pipe_base[pipeIndex]);printf("pipeIndex = %d\n",pipeIndex);}

typedef struct _VI_PIPE_CTRL_S 
{
        unsigned char    win_mode_en;
        unsigned char    emb_en;
        unsigned char    hsync_vsync_out_en;
        unsigned char    sensor_input_swap_en;
    
        unsigned char    sen_mipi_clk_pol;
        unsigned char    sen_mipi_vsync_pol;
        unsigned char    sen_mipi_hsync_pol;
        unsigned char    sen_mipi_field_pol;
        
        unsigned char    isp_clk_pol;
        unsigned char    isp_vsync_pol;
        unsigned char    isp_hsync_pol;
        unsigned char    isp_field_pol;
        
        unsigned char    sync_source_sel;
        unsigned char    input_ch_sel;
        unsigned char    ch_mode_sel;
        unsigned char    emb_enable;
        
        unsigned char    emb_mode_sel;
        unsigned char    emb_ecc_mode_en;
        unsigned char    sync_code_remove_en;
        unsigned char    sync_code_ext_en;
}VI_PIPE_CTRL_S;

typedef struct _VI_PIPE_TIMING_CTRL_S  
{
        unsigned char    input_pixel_type;
        unsigned char    input_yuv_format;
        unsigned char    output_yuv_format;
        unsigned char    yuv_order;

        unsigned char    raw_pixel_width;
        unsigned char    data_out_timming_ctrl;
        unsigned char    sync_mode; 
        unsigned char    sync_pulse_mode;

        unsigned int     emb_timeout_set;
} VI_PIPE_TIMING_CTRL_S;

typedef struct _VI_PIPE_SYNC_WIDTH_S   
{
        unsigned  short    image_vsync_width;
        unsigned  short    image_hsync_width;
} VI_PIPE_SYNC_WIDTH_S;

typedef struct _VI_PIPE_IMAGE_SIZE_TOTAL_S
{
        unsigned  short    image_v_size_total;
        unsigned  short    image_h_size_total;
} VI_PIPE_IMAGE_SIZE_TOTAL_S;

typedef struct _VI_PIPE_IMAGE_SIZE_ACTIVE_S
{
        unsigned  short    image_v_size_active;
        unsigned  short    image_h_size_active;
} VI_PIPE_IMAGE_SIZE_ACTIVE_S;

typedef struct _VI_PIPE_IMAGE_START_S
{
        unsigned  short    image_v_start;
        unsigned  short    image_h_start;
} VI_PIPE_IMAGE_START_S;

typedef struct _VI_PIPE_IMAGE_ATTR_S
{
    VI_PIPE_IMAGE_SIZE_TOTAL_S  stImageSizeTotal;
    VI_PIPE_IMAGE_SIZE_ACTIVE_S stImageSizeActive;
    VI_PIPE_IMAGE_START_S       stImageStart;
}VI_PIPE_IMAGE_ATTR_S;

typedef struct _VI_PIPE_TPG_DMA_CTL_S
{
        unsigned int    dma_y_module_en     ;
        unsigned int    dma_uv_module_en    ;
        unsigned int    dma_tpg_read_en     ;
        unsigned int    sync_out_en         ;
        unsigned int    sw_triger_en        ;
        unsigned int    dma_wr_ch_err_dec_en;
        unsigned int    dma_rd_ch_err_dec_en;
} VI_PIPE_TPG_DMA_CTL_S;

typedef struct _VI_PIPE_BUF_S
{
    unsigned int                y_base_addr0;
    unsigned int                y_base_addr1;
    unsigned int                y_line_stride;
    unsigned int                uv_base_addr0;
    unsigned int                uv_base_addr1;
    unsigned int                uv_line_stride;
    VI_PIPE_TPG_DMA_CTL_S       stTpgDmaCtrl;
}VI_PIPE_BUF_S;

typedef struct _VI_PIPE_TPG_CTL_S
{
    unsigned int    tpg_en                    ; 
    unsigned int    tpg_frame_ratio_mode      ; 
    unsigned int    tpg_sync_timing_gen_mode  ; 
    unsigned int    tpg_frame_ratio_fast_slow ; 
} VI_PIPE_TPG_CTL_S;	

typedef struct _VI_PIPE_TPG_TOF_S
{
    unsigned int    vi_pipe_tpg_tof_frm_stride; 
    unsigned int    vi_pipe_tpg_tof_frm_num   ; 
    unsigned int    tof_mode_enable           ; 
} VI_PIPE_TPG_TOF_S;


typedef struct _VI_PIPE_TPG_SIZE_TOTAL_S
{
    unsigned int    tpg_vsize_total; 
    unsigned int    tpg_hsize_total; 

} VI_PIPE_TPG_SIZE_TOTAL_S;

typedef struct _VI_PIPE_TPG_SIZE_ACTIVE_S
{                                        
    unsigned int    tpg_vsize_active     ; 
    unsigned int    tpg_hsize_active     ;                   
} VI_PIPE_TPG_SIZE_ACTIVE_S;

typedef struct  _VI_PIPE_TPG_START_S                                  
{                                        
    unsigned int    tpg_v_start          ; 
    unsigned int    tpg_h_start          ; 
} VI_PIPE_TPG_START_S;

typedef struct  _VI_PIPE_TPG_IMAGE_ATTR_S
{
    VI_PIPE_TPG_SIZE_TOTAL_S    stTpgSizeTotal;
    VI_PIPE_TPG_SIZE_ACTIVE_S   stTpgSizeActive;
    VI_PIPE_TPG_START_S         stTpgStart;
}VI_PIPE_TPG_IMAGE_ATTR_S;

typedef struct _VI_PIPE_DMA_MODE_S
{
    unsigned int    dma_y_outstand        ; 
    unsigned int    dma_uv_outstand       ; 
    unsigned int    dma_raw_outstand      ; 
    unsigned int    dma_y_blen            ; 
    unsigned int    dma_uv_blen           ; 
    unsigned int    dma_raw_blen          ; 
    unsigned int    dma_y_uv_out_swap     ; 
    unsigned int    dma_int_line_num      ; 
} VI_PIPE_DMA_MODE_S;

typedef struct _VI_PIPE_TPG_BUF_S
{
    unsigned int                tpg_y_base_addr0;
    unsigned int                tpg_y_base_addr1;
    unsigned int                tpg_y_line_stride; 
    VI_PIPE_DMA_MODE_S          stPipeDmaMode;    
}VI_PIPE_TPG_BUF_S;

typedef struct _VI_PIPE_TPG_S
{
    VI_PIPE_BUF_S               stPipeBuf;
//    VI_PIPE_TPG_CTL_S           stPipeTpgCtl;
//    VI_PIPE_TPG_TOF_S           stPipeTpgTof;
    VI_PIPE_TPG_IMAGE_ATTR_S    stPipeTpgImage;
    VI_PIPE_TPG_BUF_S           stPipeTpgBuf;    
} VI_PIPE_TPG_S;


typedef struct _VI_PIPE_DMA_ERROR_MODE_S
{
    unsigned int    dma_wr_err_dec_unit   ; 
    unsigned int    dma_rd_err_dec_unit   ; 
    unsigned int    dma_wr_err_int_gen_th ; 
    unsigned int    dma_rd_err_int_gen_th ; 
} VI_PIPE_DMA_ERROR_MODE_S;

typedef struct _VI_PIPE_DMA_RST_REQ_S
{
    unsigned int    dma_y_wr_frm_cnt_clr       ; 
    unsigned int    dma_y_wr_fifo_err_cnt_clr  ; 
    unsigned int    dma_y_wr_bw_max_clr        ; 
    unsigned int    dma_y_wr_bw_total_clr      ; 

    unsigned int    dma_uv_wr_frm_cnt_clr      ; 
    unsigned int    dma_uv_wr_fifo_err_cnt_clr ; 
    unsigned int    dma_uv_wr_bw_max_clr       ; 
    unsigned int    dma_uv_wr_bw_total_clr     ; 

    unsigned int    dma_raw_rd_frm_cnt_clr     ; 
    unsigned int    dma_raw_rd_fifo_err_cnt_clr; 
    unsigned int    dma_raw_rd_bw_max_clr      ; 
    unsigned int    dma_raw_rd_bw_total_clr    ; 

    unsigned int    dma_y_wr_rst_req           ; 
    unsigned int    dma_uv_wr_rst_req          ; 
    unsigned int    dma_raw_rd_rst_req         ; 
 
    unsigned int    dma_y_wr_idle              ; 
    unsigned int    dma_uv_wr_idle             ; 
    unsigned int    dma_raw_rd_idle            ; 
} VI_PIPE_DMA_RST_REQ_S;

typedef struct _VI_PIPE_CONFIG_DONE_S
{
    unsigned char    pipe_config_done      ; 
    unsigned char    sens_reg_wr_protect   ; 
    unsigned char    int_pol               ; 
} VI_PIPE_CONFIG_DONE_S;

typedef struct _VI_PIPE_INT_CTL_S
{
    unsigned char    win_ctl_frame_end_int          ; 
    unsigned char    emb_ctl_frame_end_int          ; 
    unsigned char    emb_ctl_time_out_int           ; 
    unsigned char    tpg_ctl_frame_end_int          ; 
    unsigned char    dma_y_wr_frame_end_int         ; 
    unsigned char    dma_y_wr_ch_line_base_int      ; 
    unsigned char    dma_y_wr_ch_err_frame_end_int  ; 
    unsigned char    dma_y_wr_ch_err_immediate_int  ; 
    unsigned char    dma_uv_wr_ch_frame_end_int     ; 
    unsigned char    dma_uv_wr_ch_line_base_int     ; 
    unsigned char    dma_uv_wr_ch_err_frame_end_int ; 
    unsigned char    dma_uv_wr_ch_err_immediate_int ; 
    unsigned char    dma_raw_rd_ch_frame_end_int    ; 
    unsigned char    dma_raw_rd_ch_line_base_int    ; 
    unsigned char    dma_raw_rd_ch_err_frame_end_int;
    unsigned char    dma_raw_rd_ch_err_immediate_int;
    //       
    unsigned char    win_ctl_frame_end_mask         ; 
    unsigned char    emb_ctl_frame_end_mask         ; 
    unsigned char    emb_ctl_time_out_mask          ; 
    unsigned char    tpg_ctl_frame_end_mask         ; 
    unsigned char    dma_y_wr_frame_end_mask        ; 
    unsigned char    dma_y_wr_ch_line_base_mask     ; 
    unsigned char    dma_y_wr_ch_err_frame_end_mask ; 
    unsigned char    dma_y_wr_ch_err_immediate_mask ; 
    unsigned char    dma_uv_wr_ch_frame_end_mask    ; 
    unsigned char    dma_uv_wr_ch_line_base_mask    ; 
    unsigned char    dma_uv_wr_ch_err_frame_end_mask ;
    unsigned char    dma_uv_wr_ch_err_immediate_mask ;
    unsigned char    dma_raw_rd_ch_frame_end_mask   ; 
    unsigned char    dma_raw_rd_ch_line_base_mask   ; 
    unsigned char    dma_raw_rd_ch_err_frame_end_mask;   
    unsigned char    dma_raw_rd_ch_err_immediate_mask;  
} VI_PIPE_INT_CTL_S;

typedef struct _VI_PIPE_ATTR_S
{
    VI_PIPE_CTRL_S                      stPipeCtl;
    VI_PIPE_TIMING_CTRL_S               stTimingCtl;
    VI_PIPE_SYNC_WIDTH_S                stPipeSync;
    VI_PIPE_IMAGE_ATTR_S                stPipeImage;
    VI_PIPE_TPG_S                       stPipeTpg;
    VI_PIPE_TPG_CTL_S                   stPipeTpgCtl;
    VI_PIPE_TPG_TOF_S                   stPipeTpgTof;
    VI_PIPE_INT_CTL_S                   stIntCtl;
    VI_PIPE_CONFIG_DONE_S               stConfigDone;
} VI_PIPE_ATTR_S;

int VI_DRV_PIPE_Remap(void);
int VI_DRV_PIPE_InitPipeInterrupt(int s8Index, BOOL bIntrPolHigh, unsigned int uIntrCtlData);
unsigned int VI_DRV_PIPE_GetPipeIntSts(int s8Index);
int VI_DRV_PIPE_SetPipe(int s8Index,VI_PIPE_ATTR_S *pstVipipe);
//debug
unsigned int VI_DRV_PIPE_GetPipeRegsVal(int s8Index);
#endif /*_VI_PIPE_DRV_DEF_H_*/
