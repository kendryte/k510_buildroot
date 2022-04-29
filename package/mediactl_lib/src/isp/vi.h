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
/******************************************************************************
  File Name     : vi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file
******************************************************************************/
#ifndef _VI_H_
#define _VI_H_

#include "isp_com.h"
//
#define VI_WRAP_SW_RST_DIS        0
#define VI_WRAP_SW_RST_EN         1
//
#define F_CSI_0_CLK       0
#define F_CSI_1_CLK       1
#define F_DVP_0_CLK       2
#define F_DPG_CLK         3
//
#define R_TOF_CSI_1_CLK   0
#define R_TOF_CSI_0_CLK   1
#define R_TOF_DVP_0_CLK   2
#define R_TOF_DPG_CLK     3
//
#define CSI0_DEBUG_INFO   0
#define CSI1_DEBUG_INFO   1
//
#define DVP_RAISE_EGDE    0
#define DVP_FALLING_EDGE  1
//
#define VI_CLK_DIS        0
#define VI_CLK_EN         1
//
#define VI_DONE_WP_EN     0
#define VI_DONE_WP_DIS    1
//
#define VI_INT_DIS        0
#define VI_INT_EN         1
/*vi pipe*/
//
#define VI_DEV_MIPI       0
#define VI_DEV_MIPI_WDR   1
#define VI_DEV_DVP        2
#define VI_DEV_TOF        3
//
#define MIPI_RAW_SENSOR   0
#define DVP_RAW_SENSOR    1
#define DVP_YUV_SENSOR    2
#define VI_TOF_SENSOR     3
///
#define VI_INT_LOW_ACT    0
#define VI_INT_HIGH_ACT   1
//wrap 
typedef enum _DPHY_MODE_E
{
	TWO_LANES_MODE,
	FOUR_LANES_MODE,
}DPHY_MODE_E;
//
typedef enum _SONY_POL_MODE_E
{
	SONY_POL_MODE_DIS,
	SONY_POL_MODE_EN,	
}SONY_POL_MODE_E;
//
typedef enum _WDR_SENSOR_VENDOR_E
{
	SONY_WDR_SENSOR,
	OTHERS_WDR_SENSOR,
}WDR_SENSOR_VENDOR_E;
//
typedef enum _MIPI_CSI_DMOE_E
{
    NORMAL_MODE,
    DEBUG_MODE,
} MIPI_CSI_MODE_E;
//
//pipe
//
#define  EXTERNAL_SYNC   	   0
#define  INTERNAL_SYNC         1
//
#define  DVP_INPUT   	   	   0
#define  MIPI_INPUT            1
//
#define  VI_BT656   	   	   0
#define  VI_MIPI_BT1120        1
//
#define  EMB_DIS  	   	   	   0
#define  EMB_EN            	   1
//
#define  EMB_8BIT_656_MODE     0
#define  EMB_F_656_MODE        1
//
#define  SENSOR_INPUT_RAWRGB   0
#define  SENSOR_INPUT_YUV      1
//
#define  VI_INPUT_YUV422       0
#define  VI_INPUT_YUV420       1
//
#define  VI_OUTPUT_YUV422      0
#define  VI_OUTPUT_YUV420      1
//
#define  VI_YUV422_YUYV        0
#define  VI_YUV422_YVYU        1
#define  VI_YUV422_UYVY        2
#define  VI_YUV422_VYUY        3
//
#define  CTRL_CYCLE_DELAY_1    0
#define  CTRL_CYCLE_DELAY_2    1
#define  CTRL_CYCLE_DELAY_3    2
#define  CTRL_CYCLE_DELAY_4    3
//
#define  SYNC_V_VALID_H        0
#define  SYNC_V_SYNC_H         1
#define  VALID_V_VALID_H       2
#define  VALID_V_SYNC_H        3
#define  SYNC_V_DATA_EN        4
#define  VALID_V_DATA_EN       5
#define  VALID_V               6
#define  SYNC_V                7

typedef enum _VI_PIPE_WDR_MODE_E
{
	  VI_PIPE_WDR_NONE,
	  VI_PIPE_WDR_2_FRAME,
	  VI_PIPE_WDR_3_FRAME,
	  VI_PIPE_WDR_BUTT,
} VI_PIPE_WDR_MODE_E;

struct sensor_info_s
{
    unsigned int         sensor_interface_en;
    unsigned int 		 tpg_w_en;
    unsigned int 		 tpg_r_en;
	WDR_SENSOR_VENDOR_E  wdr_sensor_vendor;
	VI_PIPE_WDR_MODE_E   wdr_mode;
	MIPI_CSI_MODE_E      mipi_mode;
	ISP_PIPELINE_E		 isp_pipeline;
};
//
struct vi_wrap_cfg_info{
	DPHY_MODE_E	         dphy_mode;
	SONY_POL_MODE_E      sony_mode;
	struct sensor_info_s sensor_info[MAX_SENSOR_INTERFACE_NUM];
};
//
struct vi_pipe_cfg_info{
    unsigned int    win_mode_en;
	unsigned int    input_ch_sel;
	unsigned int    ch_mode_sel;
    unsigned int    pixel_type;
    unsigned int    yuv_in_format;
    unsigned int    yuv_out_format;
    unsigned int    yuv422_order;
    unsigned int    pixel_width;
    unsigned int    data_out_timming_ctrl;
    unsigned int    sync_pulse_mode;
    unsigned int    sen_mipi_clk_pol;
    unsigned int    sen_mipi_vsync_pol;
    unsigned int    sen_mipi_hsync_pol;
    unsigned int    sen_mipi_field_pol;
    unsigned int    isp_clk_pol;
    unsigned int    isp_vsync_pol;
    unsigned int    isp_hsync_pol;
    unsigned int    isp_field_pol;
    //TPG
    unsigned int    tpg_w_en;
    unsigned int    tpg_r_en;
    struct image_size_s total_size;
    struct image_size_s in_size;
    struct image_size_s   w_size_st;
    struct image_size_s   r_size_st;
    unsigned int    vi_pipe_w_addr_y0;
    unsigned int    vi_pipe_w_addr_y1;
    unsigned int    vi_pipe_w_addr_uv0;
    unsigned int    vi_pipe_w_addr_uv1;
    unsigned int    vi_pipe_r_addr_y0;
    unsigned int    vi_pipe_r_addr_y1;
    unsigned int    vi_pipe_addr_stride;
	//tof tpg   
	unsigned int    tof_mode_enable;
	unsigned int    vi_pipe_tpg_tof_frm_num;
	unsigned int    vi_pipe_tpg_tof_frm_stride;
};

struct VI_PIPE_INT_EN
{
    unsigned char    win_ctl_frame_end_en         ; 
    unsigned char    emb_ctl_frame_end_en         ; 
    unsigned char    emb_ctl_time_out_en          ; 
    unsigned char    tpg_ctl_frame_end_en         ; 
    unsigned char    dma_y_wr_frame_end_en        ; 
    unsigned char    dma_y_wr_ch_line_base_en     ; 
    unsigned char    dma_y_wr_ch_err_frame_end_en ; 
    unsigned char    dma_y_wr_ch_err_immediate_en ; 
    unsigned char    dma_uv_wr_ch_frame_end_en    ; 
    unsigned char    dma_uv_wr_ch_line_base_en    ; 
    unsigned char    dma_uv_wr_ch_err_frame_end_en ;
    unsigned char    dma_uv_wr_ch_err_immediate_en ;
    unsigned char    dma_raw_rd_ch_frame_end_en   ; 
    unsigned char    dma_raw_rd_ch_line_base_en   ; 
    unsigned char    dma_raw_rd_ch_err_frame_end_en;
    unsigned char    dma_raw_rd_ch_err_immediate_en;
};

struct vi_cfg_info
{
    struct vi_wrap_cfg_info  vi_wrap_cfg;
    struct vi_pipe_cfg_info  vi_pipe_cfg[8];
};

#endif /*_VI_H_*/