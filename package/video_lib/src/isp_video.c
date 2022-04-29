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
  File Name     : isp_video.c
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h> 
#include <assert.h>
#include <errno.h>

#include "video_subsystem.h"
#include "vi/vi.h"
#include "vi/vi_com.h"
#include "mipi/mipi.h"
#include "isp_2k/isp.h"
#include "isp_fbc/isp_fbc.h"
#include "vo/vo.h"
#include "vo/vo_com.h"
#include "bt1120/bt1120.h"
#include "isp_2k/table/isp_table_drv.h"
#include "isp_video.h"
#include "sensor/sensor.h"

#define DEV_NAME "/dev/test-isp"

struct isp_device isp;
int fd_isp;
int fd_i2c0;
//
/*******************************************************************************
 * mipi csi * 
 *******************************************************************************/
extern struct mipi_csi_cfg_info mipi_2x2lane12_34_raw12_cfg_info;
extern struct mipi_csi_cfg_info mipi_4lane_raw12_cfg_info;
extern struct mipi_csi_cfg_info mipi_2x2lane12_34_raw10_cfg_info;
extern struct mipi_csi_cfg_info mipi_4lane_raw10_cfg_info;

int video_set_mipicsi(enum csi_lane_mode lane_mode,unsigned int csi0_pixel_width,unsigned int csi1_pixel_width)
{
    struct isp_mipi_device *mipi = &isp.isp_mipi;
    struct mipi_csi_cfg_info *cfg_info = &mipi->csi_info;
    printf("video_set_mipicsi start!\n");

    switch(lane_mode)    
    {
        case MIPI_2LANE12_RAW12:
        case MIPI_2LANE34_RAW12:
        case MIPI_2x2LANE12_34_RAW12:
            memcpy((void*)cfg_info,(void*)&mipi_2x2lane12_34_raw12_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        case MIPI_4LANE_RAW12:
            memcpy((void*)cfg_info,(void*)&mipi_4lane_raw12_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        case MIPI_2LANE12_RAW10:
        case MIPI_2LANE34_RAW10:
        case MIPI_2x2LANE12_34_RAW10:
            memcpy((void*)cfg_info,(void*)&mipi_2x2lane12_34_raw10_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        case MIPI_4LANE_RAW10:
            memcpy((void*)cfg_info,(void*)&mipi_4lane_raw10_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        case MIPI_2x2LANE12_34:
            memcpy((void*)cfg_info,(void*)&mipi_2x2lane12_34_raw12_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        case MIPI_1x4LANE:
            memcpy((void*)cfg_info,(void*)&mipi_4lane_raw12_cfg_info,sizeof(struct mipi_csi_cfg_info));
            break;
        default:
            printf("error,no lane mode\n");
            break;   
    }
    unsigned int csi00_datatype;
    unsigned int csi10_datatype;
    if(PIXEL_WIDTH_8BIT == csi0_pixel_width)
    {
        csi00_datatype = MIPI_RAW8;
    }
    else if(PIXEL_WIDTH_10BIT == csi0_pixel_width)
    {
        csi00_datatype = MIPI_RAW10;
    }
    else if(PIXEL_WIDTH_12BIT == csi0_pixel_width)
    {
        csi00_datatype = MIPI_RAW12;
    }
    if(PIXEL_WIDTH_8BIT == csi1_pixel_width)
    {
        csi10_datatype = MIPI_RAW8;
    }
    else if(PIXEL_WIDTH_10BIT == csi1_pixel_width)
    {
        csi10_datatype = MIPI_RAW10;
    }
    else if(PIXEL_WIDTH_12BIT == csi1_pixel_width)
    {
        csi10_datatype = MIPI_RAW12;
    }
    cfg_info->csi00_datatype_select0 = csi00_datatype;
    cfg_info->csi01_datatype_select0 = csi00_datatype;
    cfg_info->csi02_datatype_select0 = csi00_datatype;
    cfg_info->csi10_datatype_select0 = csi10_datatype;
    return;  
}
/*******************************************************************************
 * vi * 
 *******************************************************************************/
int video_set_vi(struct video_vi_info *vi_info)
{
    ISP_CHECK_POINTER(vi_info); 
	struct vi_device *vi = &isp.isp_vi;
	//
	struct vi_wrap_cfg_info *wrap_info = &vi->vi_wrap_cfg;
	wrap_info->dphy_mode = vi_info->dphy_mode;//TWO_LANES_MODE;
	wrap_info->sony_mode = vi_info->sony_mode;//SONY_POL_MODE_DIS;
    //
	SENSOR_INFO *mipi0info = &wrap_info->sensor_info[MIPI0];
    struct vi_sensor_info  *sensor0_info= &vi_info->sensor_info[MIPI0];
	mipi0info->sensor_interface_en = sensor0_info->sensor_interface_en;//ENABLE;
	mipi0info->tpg_w_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->tpg_r_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->wdr_sensor_vendor = sensor0_info->wdr_sensor_vendor;//SONY_WDR_SENSOR;
	mipi0info->wdr_mode = sensor0_info->wdr_mode;//ISP_PIPE_WDR_NONE;
	mipi0info->mipi_mode = NORMAL_MODE;
	mipi0info->isp_pipeline = sensor0_info->isp_pipeline;//ISP_F_2K;
    //
    SENSOR_INFO *mipi1info = &wrap_info->sensor_info[MIPI1];
    struct vi_sensor_info  *sensor1_info= &vi_info->sensor_info[MIPI1];
	mipi1info->sensor_interface_en = sensor1_info->sensor_interface_en;//ENABLE;
	mipi1info->tpg_w_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	mipi1info->tpg_r_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	mipi1info->wdr_sensor_vendor = sensor1_info->wdr_sensor_vendor;//SONY_WDR_SENSOR;
	mipi1info->wdr_mode = sensor1_info->wdr_mode;//ISP_PIPE_WDR_NONE;
	mipi1info->mipi_mode = NORMAL_MODE;
	mipi1info->isp_pipeline = sensor1_info->isp_pipeline;//ISP_F_2K;
    //
	SENSOR_INFO *dvp0info = &wrap_info->sensor_info[DVP0];
    struct vi_sensor_info  *sensor2_info= &vi_info->sensor_info[DVP0];
	dvp0info->sensor_interface_en = sensor2_info->sensor_interface_en;//ENABLE;
	dvp0info->tpg_w_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	dvp0info->tpg_r_en = 0;//isp_addr->vi_tpg_en;//DISABLE;
	dvp0info->wdr_sensor_vendor = sensor2_info->wdr_sensor_vendor;//SONY_WDR_SENSOR;
	dvp0info->wdr_mode = sensor2_info->wdr_mode;//ISP_PIPE_WDR_NONE;
	dvp0info->mipi_mode = NORMAL_MODE;
	dvp0info->isp_pipeline = sensor2_info->isp_pipeline;//ISP_F_2K;

	//pipe00
	struct vi_pipe_cfg_info *pipe00info = &vi->vi_pipe_cfg[VI_MIPI_CSI00_PIPE_ID];
    struct vi_pipe_info *pipe00_info = &vi_info->pipe_info[VI_MIPI_CSI00_PIPE_ID];
	pipe00info->win_mode_en = pipe00_info->win_mode_en;//TRUE;	
	pipe00info->input_ch_sel = pipe00_info->input_ch_sel;//MIPI_INPUT;
	pipe00info->ch_mode_sel = pipe00_info->ch_mode_sel;//VI_MIPI_BT1120;
    pipe00info->pixel_type = pipe00_info->pixel_type;//SENSOR_INPUT_RAWRGB;
    pipe00info->yuv_in_format = VI_INPUT_YUV422;
    pipe00info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe00info->yuv422_order = VI_YUV422_YUYV;
    pipe00info->pixel_width = pipe00_info->pixel_width;//PIXEL_WIDTH_12BIT;
	pipe00info->data_out_timming_ctrl = pipe00_info->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_4;
	pipe00info->sync_pulse_mode = pipe00_info->sync_pulse_mode;//0;//0;
	pipe00info->sen_mipi_clk_pol = pipe00_info->sen_mipi_clk_pol;//TRUE;
	pipe00info->sen_mipi_vsync_pol = pipe00_info->sen_mipi_vsync_pol;//FALSE;
	pipe00info->sen_mipi_hsync_pol = pipe00_info->sen_mipi_hsync_pol;//FALSE;
	pipe00info->sen_mipi_field_pol = pipe00_info->sen_mipi_field_pol;//TRUE;
	pipe00info->isp_clk_pol = pipe00_info->isp_clk_pol;//TRUE;
	pipe00info->isp_vsync_pol = pipe00_info->isp_vsync_pol;//TRUE;
	pipe00info->isp_hsync_pol = pipe00_info->isp_hsync_pol;//TRUE;
	pipe00info->isp_field_pol = pipe00_info->isp_field_pol;//TRUE;
	//
    pipe00info->tpg_w_en = pipe00_info->tpg_w_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe00info->tpg_r_en = pipe00_info->tpg_r_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe00info->total_size.Width = pipe00_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe00info->total_size.Height = pipe00_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe00info->in_size.Width = pipe00_info->in_width;//isp_size->in_size.Width - 1;//1920;
	pipe00info->in_size.Height = pipe00_info->in_height;//isp_size->in_size.Height - 1;//1080;
    pipe00info->w_size_st.Width_st = pipe00_info->w_st_width;//0x0;
	pipe00info->w_size_st.Height_st = pipe00_info->w_st_height;//0x3fff;
    pipe00info->r_size_st.Width_st = pipe00_info->r_st_width;//0x117;
	pipe00info->r_size_st.Height_st = pipe00_info->r_st_height;//0x2c;
    pipe00info->vi_pipe_w_addr_y0 = pipe00_info->vi_pipe_w_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_w_addr_y1 = pipe00_info->vi_pipe_w_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_w_addr_uv0 = pipe00_info->vi_pipe_w_addr_uv0;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_w_addr_uv1 = pipe00_info->vi_pipe_w_addr_uv1;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_r_addr_y0 = pipe00_info->vi_pipe_r_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_r_addr_y1 = pipe00_info->vi_pipe_r_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe00info->vi_pipe_addr_stride = pipe00_info->vi_pipe_addr_stride;//isp_addr->vi_tpg_stride;
	pipe00info->tof_mode_enable = pipe00_info->tof_mode_enable;//DISABLE;
	pipe00info->vi_pipe_tpg_tof_frm_num = pipe00_info->vi_pipe_tpg_tof_frm_num;//0x3;
	pipe00info->vi_pipe_tpg_tof_frm_stride = pipe00_info->vi_pipe_tpg_tof_frm_stride;//0x10380;

	//pipe01
	struct vi_pipe_cfg_info *pipe01info = &vi->vi_pipe_cfg[VI_MIPI_CSI01_PIPE_ID];
    struct vi_pipe_info *pipe01_info = &vi_info->pipe_info[VI_MIPI_CSI01_PIPE_ID];
	pipe01info->win_mode_en = pipe01_info->win_mode_en;//TRUE;	
	pipe01info->input_ch_sel = pipe01_info->input_ch_sel;//MIPI_INPUT;
	pipe01info->ch_mode_sel = pipe01_info->ch_mode_sel;//VI_MIPI_BT1120;
    pipe01info->pixel_type = pipe01_info->pixel_type;//SENSOR_INPUT_RAWRGB;
    pipe01info->yuv_in_format = VI_INPUT_YUV422;
    pipe01info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe01info->yuv422_order = VI_YUV422_YUYV;
    pipe01info->pixel_width = pipe01_info->pixel_width;//PIXEL_WIDTH_12BIT;
	pipe01info->data_out_timming_ctrl = pipe01_info->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_4;
	pipe01info->sync_pulse_mode = pipe01_info->sync_pulse_mode;//0;//0;
	pipe01info->sen_mipi_clk_pol = pipe01_info->sen_mipi_clk_pol;//TRUE;
	pipe01info->sen_mipi_vsync_pol = pipe01_info->sen_mipi_vsync_pol;//FALSE;
	pipe01info->sen_mipi_hsync_pol = pipe01_info->sen_mipi_hsync_pol;//FALSE;
	pipe01info->sen_mipi_field_pol = pipe01_info->sen_mipi_field_pol;//TRUE;
	pipe01info->isp_clk_pol = pipe01_info->isp_clk_pol;//TRUE;
	pipe01info->isp_vsync_pol = pipe01_info->isp_vsync_pol;//TRUE;
	pipe01info->isp_hsync_pol = pipe01_info->isp_hsync_pol;//TRUE;
	pipe01info->isp_field_pol = pipe01_info->isp_field_pol;//TRUE;
	//
    pipe01info->tpg_w_en = pipe01_info->tpg_w_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe01info->tpg_r_en = pipe01_info->tpg_r_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe01info->total_size.Width = pipe01_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe01info->total_size.Height = pipe01_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe01info->in_size.Width = pipe01_info->in_width;//isp_size->in_size.Width - 1;//1920;
	pipe01info->in_size.Height = pipe01_info->in_height;//isp_size->in_size.Height - 1;//1080;
    pipe01info->w_size_st.Width_st = pipe01_info->w_st_width;//0x0;
	pipe01info->w_size_st.Height_st = pipe01_info->w_st_height;//0x3fff;
    pipe01info->r_size_st.Width_st = pipe01_info->r_st_width;//0x117;
	pipe01info->r_size_st.Height_st = pipe01_info->r_st_height;//0x2c;
    pipe01info->vi_pipe_w_addr_y0 = pipe01_info->vi_pipe_w_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_w_addr_y1 = pipe01_info->vi_pipe_w_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_w_addr_uv0 = pipe01_info->vi_pipe_w_addr_uv0;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_w_addr_uv1 = pipe01_info->vi_pipe_w_addr_uv1;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_r_addr_y0 = pipe01_info->vi_pipe_r_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_r_addr_y1 = pipe01_info->vi_pipe_r_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe01info->vi_pipe_addr_stride = pipe01_info->vi_pipe_addr_stride;//isp_addr->vi_tpg_stride;
	pipe01info->tof_mode_enable = pipe01_info->tof_mode_enable;//DISABLE;
	pipe01info->vi_pipe_tpg_tof_frm_num = pipe01_info->vi_pipe_tpg_tof_frm_num;//0x3;
	pipe01info->vi_pipe_tpg_tof_frm_stride = pipe01_info->vi_pipe_tpg_tof_frm_stride;//0x10380;

	//pipe02
	struct vi_pipe_cfg_info *pipe02info = &vi->vi_pipe_cfg[VI_MIPI_CSI02_PIPE_ID];
    struct vi_pipe_info *pipe02_info = &vi_info->pipe_info[VI_MIPI_CSI02_PIPE_ID];
	pipe02info->win_mode_en = pipe02_info->win_mode_en;//TRUE;	
	pipe02info->input_ch_sel = pipe02_info->input_ch_sel;//MIPI_INPUT;
	pipe02info->ch_mode_sel = pipe02_info->ch_mode_sel;//VI_MIPI_BT1120;
    pipe02info->pixel_type = pipe02_info->pixel_type;//SENSOR_INPUT_RAWRGB;
    pipe02info->yuv_in_format = VI_INPUT_YUV422;
    pipe02info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe02info->yuv422_order = VI_YUV422_YUYV;
    pipe02info->pixel_width = pipe02_info->pixel_width;//PIXEL_WIDTH_12BIT;
	pipe02info->data_out_timming_ctrl = pipe02_info->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_4;
	pipe02info->sync_pulse_mode = pipe02_info->sync_pulse_mode;//0;//0;
	pipe02info->sen_mipi_clk_pol = pipe02_info->sen_mipi_clk_pol;//TRUE;
	pipe02info->sen_mipi_vsync_pol = pipe02_info->sen_mipi_vsync_pol;//FALSE;
	pipe02info->sen_mipi_hsync_pol = pipe02_info->sen_mipi_hsync_pol;//FALSE;
	pipe02info->sen_mipi_field_pol = pipe02_info->sen_mipi_field_pol;//TRUE;
	pipe02info->isp_clk_pol = pipe02_info->isp_clk_pol;//TRUE;
	pipe02info->isp_vsync_pol = pipe02_info->isp_vsync_pol;//TRUE;
	pipe02info->isp_hsync_pol = pipe02_info->isp_hsync_pol;//TRUE;
	pipe02info->isp_field_pol = pipe02_info->isp_field_pol;//TRUE;
	//
    pipe02info->tpg_w_en = pipe02_info->tpg_w_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe02info->tpg_r_en = pipe02_info->tpg_r_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe02info->total_size.Width = pipe02_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe02info->total_size.Height = pipe02_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe02info->in_size.Width = pipe02_info->in_width;//isp_size->in_size.Width - 1;//1920;
	pipe02info->in_size.Height = pipe02_info->in_height;//isp_size->in_size.Height - 1;//1080;
    pipe02info->w_size_st.Width_st = pipe02_info->w_st_width;//0x0;
	pipe02info->w_size_st.Height_st = pipe02_info->w_st_height;//0x3fff;
    pipe02info->r_size_st.Width_st = pipe02_info->r_st_width;//0x117;
	pipe02info->r_size_st.Height_st = pipe02_info->r_st_height;//0x2c;
    pipe02info->vi_pipe_w_addr_y0 = pipe02_info->vi_pipe_w_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_w_addr_y1 = pipe02_info->vi_pipe_w_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_w_addr_uv0 = pipe02_info->vi_pipe_w_addr_uv0;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_w_addr_uv1 = pipe02_info->vi_pipe_w_addr_uv1;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_r_addr_y0 = pipe02_info->vi_pipe_r_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_r_addr_y1 = pipe02_info->vi_pipe_r_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe02info->vi_pipe_addr_stride = pipe02_info->vi_pipe_addr_stride;//isp_addr->vi_tpg_stride;
	pipe02info->tof_mode_enable = pipe02_info->tof_mode_enable;//DISABLE;
	pipe02info->vi_pipe_tpg_tof_frm_num = pipe02_info->vi_pipe_tpg_tof_frm_num;//0x3;
	pipe02info->vi_pipe_tpg_tof_frm_stride = pipe02_info->vi_pipe_tpg_tof_frm_stride;//0x10380;

	//pipe10
	struct vi_pipe_cfg_info *pipe10info = &vi->vi_pipe_cfg[VI_MIPI_CSI10_PIPE_ID];
    struct vi_pipe_info *pipe10_info = &vi_info->pipe_info[VI_MIPI_CSI10_PIPE_ID];
	pipe10info->win_mode_en = pipe10_info->win_mode_en;//TRUE;	
	pipe10info->input_ch_sel = pipe10_info->input_ch_sel;//MIPI_INPUT;
	pipe10info->ch_mode_sel = pipe10_info->ch_mode_sel;//VI_MIPI_BT1120;
    pipe10info->pixel_type = pipe10_info->pixel_type;//SENSOR_INPUT_RAWRGB;
    pipe10info->yuv_in_format = VI_INPUT_YUV422;
    pipe10info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe10info->yuv422_order = VI_YUV422_YUYV;
    pipe10info->pixel_width = pipe10_info->pixel_width;//PIXEL_WIDTH_12BIT;
	pipe10info->data_out_timming_ctrl = pipe10_info->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_4;
	pipe10info->sync_pulse_mode = pipe10_info->sync_pulse_mode;//0;//0;
	pipe10info->sen_mipi_clk_pol = pipe10_info->sen_mipi_clk_pol;//TRUE;
	pipe10info->sen_mipi_vsync_pol = pipe10_info->sen_mipi_vsync_pol;//FALSE;
	pipe10info->sen_mipi_hsync_pol = pipe10_info->sen_mipi_hsync_pol;//FALSE;
	pipe10info->sen_mipi_field_pol = pipe10_info->sen_mipi_field_pol;//TRUE;
	pipe10info->isp_clk_pol = pipe10_info->isp_clk_pol;//TRUE;
	pipe10info->isp_vsync_pol = pipe10_info->isp_vsync_pol;//TRUE;
	pipe10info->isp_hsync_pol = pipe10_info->isp_hsync_pol;//TRUE;
	pipe10info->isp_field_pol = pipe10_info->isp_field_pol;//TRUE;
	//
    pipe10info->tpg_w_en = pipe10_info->tpg_w_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe10info->tpg_r_en = pipe10_info->tpg_r_en;//isp_addr->vi_tpg_en;//DISABLE;
    pipe10info->total_size.Width = pipe10_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe10info->total_size.Height = pipe10_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe10info->in_size.Width = pipe10_info->in_width;//isp_size->in_size.Width - 1;//1920;
	pipe10info->in_size.Height = pipe10_info->in_height;//isp_size->in_size.Height - 1;//1080;
    pipe10info->w_size_st.Width_st = pipe10_info->w_st_width;//0x0;
	pipe10info->w_size_st.Height_st = pipe10_info->w_st_height;//0x3fff;
    pipe10info->r_size_st.Width_st = pipe10_info->r_st_width;//0x117;
	pipe10info->r_size_st.Height_st = pipe10_info->r_st_height;//0x2c;
    pipe10info->vi_pipe_w_addr_y0 = pipe10_info->vi_pipe_w_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_w_addr_y1 = pipe10_info->vi_pipe_w_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_w_addr_uv0 = pipe10_info->vi_pipe_w_addr_uv0;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_w_addr_uv1 = pipe10_info->vi_pipe_w_addr_uv1;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_r_addr_y0 = pipe10_info->vi_pipe_r_addr_y0;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_r_addr_y1 = pipe10_info->vi_pipe_r_addr_y1;//isp_addr->vi_tpg_baseaddr;
    pipe10info->vi_pipe_addr_stride = pipe10_info->vi_pipe_addr_stride;//isp_addr->vi_tpg_stride;
	pipe10info->tof_mode_enable = pipe10_info->tof_mode_enable;//DISABLE;
	pipe10info->vi_pipe_tpg_tof_frm_num = pipe10_info->vi_pipe_tpg_tof_frm_num;//0x3;
	pipe10info->vi_pipe_tpg_tof_frm_stride = pipe10_info->vi_pipe_tpg_tof_frm_stride;//0x10380;

	//dvp
	struct vi_pipe_cfg_info *dvppipeinfo = &vi->vi_pipe_cfg[VI_DVP_0_PIPE_ID];
    struct vi_pipe_info *dvppipe_info = &vi_info->pipe_info[VI_DVP_0_PIPE_ID];
	dvppipeinfo->win_mode_en = dvppipe_info->win_mode_en;//FALSE;		
	dvppipeinfo->input_ch_sel = dvppipe_info->input_ch_sel;//DVP_INPUT;
	dvppipeinfo->ch_mode_sel = dvppipe_info->ch_mode_sel;//VI_MIPI_BT1120;
    dvppipeinfo->pixel_type = dvppipe_info->pixel_type;//SENSOR_INPUT_RAWRGB;
    dvppipeinfo->yuv_in_format = VI_INPUT_YUV422;
    dvppipeinfo->yuv_out_format = VI_OUTPUT_YUV422;
    dvppipeinfo->yuv422_order = VI_YUV422_YUYV;
    dvppipeinfo->pixel_width = dvppipe_info->pixel_width;//PIXEL_WIDTH_10BIT;
	dvppipeinfo->data_out_timming_ctrl = dvppipe_info->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_1;
	dvppipeinfo->sync_pulse_mode = dvppipe_info->sync_pulse_mode;//1;//0;
	dvppipeinfo->sen_mipi_clk_pol = dvppipe_info->sen_mipi_clk_pol;//TRUE;
	dvppipeinfo->sen_mipi_vsync_pol = dvppipe_info->sen_mipi_vsync_pol;//TRUE;
	dvppipeinfo->sen_mipi_hsync_pol = dvppipe_info->sen_mipi_hsync_pol;//TRUE;
	dvppipeinfo->sen_mipi_field_pol = dvppipe_info->sen_mipi_field_pol;//TRUE;
	dvppipeinfo->isp_clk_pol = dvppipe_info->isp_clk_pol;//TRUE;
	dvppipeinfo->isp_vsync_pol = dvppipe_info->isp_vsync_pol;//TRUE;
	dvppipeinfo->isp_hsync_pol = dvppipe_info->isp_hsync_pol;//TRUE;
	dvppipeinfo->isp_field_pol = dvppipe_info->isp_field_pol;//TRUE;
	//
    dvppipeinfo->tpg_w_en = dvppipe_info->tpg_w_en;//isp_addr->vi_tpg_en;//DISABLE;
    dvppipeinfo->tpg_r_en = dvppipe_info->tpg_r_en;//isp_addr->vi_tpg_en;//DISABLE;
    dvppipeinfo->total_size.Width = dvppipe_info->total_width;//isp_size->total_size.Width - 1;//2200;
	dvppipeinfo->total_size.Height = dvppipe_info->total_height;//isp_size->total_size.Height - 1;//1125;
    dvppipeinfo->in_size.Width = dvppipe_info->in_width;//isp_size->in_size.Width - 1;//1920;
	dvppipeinfo->in_size.Height = dvppipe_info->in_height;//isp_size->in_size.Height - 1;//1080;
    dvppipeinfo->w_size_st.Width_st = dvppipe_info->w_st_width;//0x24f;//0x0;
	dvppipeinfo->w_size_st.Height_st = dvppipe_info->w_st_height;//0x3fff;
    dvppipeinfo->r_size_st.Width_st = dvppipe_info->r_st_width;//0x0;//0x117;
	dvppipeinfo->r_size_st.Height_st = dvppipe_info->r_st_height;//0x0;//0x2c;
    dvppipeinfo->vi_pipe_w_addr_y0 = dvppipe_info->vi_pipe_w_addr_y0;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_w_addr_y1 = dvppipe_info->vi_pipe_w_addr_y1;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_w_addr_uv0 = dvppipe_info->vi_pipe_w_addr_uv0;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_w_addr_uv1 = dvppipe_info->vi_pipe_w_addr_uv1;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_r_addr_y0 = dvppipe_info->vi_pipe_r_addr_y0;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_r_addr_y1 = dvppipe_info->vi_pipe_r_addr_y1;//isp_addr->vi_tpg_baseaddr;
    dvppipeinfo->vi_pipe_addr_stride = dvppipe_info->vi_pipe_addr_stride;//isp_addr->vi_tpg_stride;
	dvppipeinfo->tof_mode_enable = dvppipe_info->tof_mode_enable;//DISABLE;
	dvppipeinfo->vi_pipe_tpg_tof_frm_num = dvppipe_info->vi_pipe_tpg_tof_frm_num;//0x0;
	dvppipeinfo->vi_pipe_tpg_tof_frm_stride = dvppipe_info->vi_pipe_tpg_tof_frm_stride;//0x0;

    return 0; 
}
/*******************************************************************************
 * f2k * 
 *******************************************************************************/
extern struct _ISP_WRAP_CFG_INFO imx385_wrap_info;
extern struct _ISP_CORE_CFG_INFO imx385_core_info;
extern struct _ISP_DS_CFG_INFO imx385_ds_info;
extern struct _ISP_WRAP_CFG_INFO jfx23s_wrap_info;
extern struct _ISP_CORE_CFG_INFO jfx23s_core_info;
extern struct _ISP_DS_CFG_INFO jfx23s_ds_info;
extern struct _ISP_WRAP_CFG_INFO imx219_wrap_info;
extern struct _ISP_CORE_CFG_INFO imx219_core_info;
extern struct _ISP_DS_CFG_INFO imx219_ds_info;
unsigned int ispf2kfirstdone = 0;
/*
*must be used
*/
int video_set_ispf2kcommon(enum _SENSOR_TYPE sensor_type,struct isp_common_info *commoninfo)
{
    ISP_CHECK_POINTER(commoninfo);
    //
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    isp_f2k_wrap_info->isp_out_sel =  commoninfo->isp_out_sel;
    isp_f2k_wrap_info->dvp_ch_mode = BT1120_MIPI;
    //
    struct _ITC_INFO_S	*itcInfo = &isp_f2k_core_info->itcInfo;
    itcInfo->total_size.Width = commoninfo->totalsize_width;
    itcInfo->total_size.Height = commoninfo->totalsize_height;
    //itcInfo->itc_size.Width_st = 0x5;
    itcInfo->itc_size.Width = commoninfo->insize_width;
    //itcInfo->itc_size.Height_st = 0x2;
    itcInfo->itc_size.Height = commoninfo->insize_height;
    //
    struct _OTC_INFO_S *otcInfo = &isp_f2k_core_info->otcInfo;
    otcInfo->otc_out_size.Width_st = 0x4;
    otcInfo->otc_out_size.Width = commoninfo->outsize_width;
    otcInfo->otc_out_size.Height_st = 0x4;
    otcInfo->otc_out_size.Height = commoninfo->outsize_height;
    //
    isp_f2k_ds_info->dsInSizeInfo.Width = commoninfo->outsize_width;
    isp_f2k_ds_info->dsInSizeInfo.Height = commoninfo->outsize_height;

    return 0; 
}
/*
*
*/
int video_set_ispf2kmain0(enum _SENSOR_TYPE sensor_type,struct isp_main_info *main_info)
{
    ISP_CHECK_POINTER(main_info); 

    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }

    ISP_WRAP_MAIN_S	*mainInfo = &isp_f2k_wrap_info->mainInfo;
    mainInfo->main_out_en = main_info->main_en;
    mainInfo->main_pix_remap_en = 0;
    mainInfo->main_size.Width = main_info->width;
    mainInfo->main_size.Height = main_info->height;
    mainInfo->main_line_stride = calc_stride(main_info->width);//(main_info->width + 15)/16*16;//main_info->stride; 
    mainInfo->main_y_buf0_base = main_info->y_addr0;   
    mainInfo->main_y_buf1_base = main_info->y_addr1;
    mainInfo->main_uv_buf0_base= main_info->y_addr0 + mainInfo->main_line_stride * mainInfo->main_size.Height;   
    mainInfo->main_uv_buf1_base= main_info->y_addr1 + mainInfo->main_line_stride * mainInfo->main_size.Height;        

    return 0; 
}
/*
*
*/
int video_set_ispf2kds0(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds0_info)
{
    ISP_CHECK_POINTER(ds0_info); 

    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS0_S *ds0Info = &isp_f2k_wrap_info->ds0Info;
    ds0Info->ds0_out_en     = ds0_info->ds_en;
    ds0Info->ds0_osd0_en    = 0;   
    ds0Info->ds0_osd1_en    = 0; 
    ds0Info->ds0_osd2_en    = 0;
    ds0Info->pix_remap_out0_en = 0;		 	
    ds0Info->ds0_size.Width = ds0_info->ds_width; 
    ds0Info->ds0_size.Height = ds0_info->ds_height;
    ds0Info->ds0_line_stride = calc_stride(ds0Info->ds0_size.Width);//ds0_info->stride;
    ds0Info->ds0_y_buf0_base = ds0_info->y_addr0;   
    ds0Info->ds0_y_buf1_base = ds0_info->y_addr1;
    ds0Info->ds0_uv_buf0_base = ds0Info->ds0_y_buf0_base + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;   
    ds0Info->ds0_uv_buf1_base = ds0Info->ds0_y_buf1_base + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;      
   //
    ISP_DS_INFO_S *dsInfo = &isp_f2k_ds_info->dsInfo[0];
    dsInfo->scale_en = ds0_info->ds_en;
    dsInfo->vscale_filter_en = ds0_info->ds_en;  
    dsInfo->hscale_filter_en = ds0_info->ds_en;
    dsInfo->ds_out_size.Width = ds0_info->ds_width;
    dsInfo->ds_out_size.Height = ds0_info->ds_height;
    dsInfo->out_uv_swap = ds0_info->uv_swap;
    return 0; 
}
/*
*
*/
int video_set_ispf2kds1(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds1_info)
{
    ISP_CHECK_POINTER(ds1_info); 

    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS1_S *ds1Info = &isp_f2k_wrap_info->ds1Info;
    ds1Info->ds1_out_en     = ds1_info->ds_en;
    ds1Info->ds1_osd0_en    = 0;   
    ds1Info->ds1_osd1_en    = 0; 
    ds1Info->ds1_osd2_en    = 0;
    ds1Info->pix_remap_out1_en = 0;		 	
    ds1Info->ds1_size.Width = ds1_info->ds_width; 
    ds1Info->ds1_size.Height = ds1_info->ds_height;
    ds1Info->ds1_line_stride = ds1_info->stride;//calc_stride(ds1Info->ds1_size.Width);//ds1_info->stride;
    ds1Info->ds1_y_buf0_base = ds1_info->y_addr0;   
    ds1Info->ds1_y_buf1_base = ds1_info->y_addr1;
    ds1Info->ds1_uv_buf0_base = ds1Info->ds1_y_buf0_base + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;   
    ds1Info->ds1_uv_buf1_base = ds1Info->ds1_y_buf1_base + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;      
   //
    ISP_DS_INFO_S *dsInfo = &isp_f2k_ds_info->dsInfo[1];
    dsInfo->scale_en = ds1_info->ds_en;
    dsInfo->vscale_filter_en = ds1_info->ds_en;  
    dsInfo->hscale_filter_en = ds1_info->ds_en;
    dsInfo->ds_out_size.Width = ds1_info->ds_width;
    dsInfo->ds_out_size.Height = ds1_info->ds_height;
    dsInfo->out_uv_swap = ds1_info->uv_swap;
    return 0; 
}
/*
*
*/
int video_set_ispf2kds2(enum _SENSOR_TYPE sensor_type,struct isp_ds2_info *ds2_info)
{
    ISP_CHECK_POINTER(ds2_info); 
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS2_S	*ds2Info = &isp_f2k_wrap_info->ds2Info;
    ds2Info->ds2_out_en     = ds2_info->ds2_en;
    ds2Info->ds2_osd0_en    = 0;   
    ds2Info->ds2_osd1_en    = 0; 
    ds2Info->ds2_osd2_en    = 0;
    //ds2Info->pix_remap_out2_en = 0;		 	
    ds2Info->ds2_size.Width = ds2_info->ds2_width; 
    ds2Info->ds2_size.Height = ds2_info->ds2_height;
    ds2Info->ds2_out_img_out_format  = ds2_info->ds2_rgb_type;
    ds2Info->ds2_line_stride = ds2_info->stride;//calc_stride(ds2Info->ds2_size.Width);//ds2_info->stride;
    if( OUT_ARGB == ds2Info->ds2_out_img_out_format)
    {
        ds2Info->ds2_r_buf0_base = ds2_info->r_addr0;   
        ds2Info->ds2_r_buf1_base = ds2_info->r_addr1;
        ds2Info->ds2_g_buf0_base = ds2Info->ds2_r_buf0_base  + ds2Info->ds2_line_stride*2;   
        ds2Info->ds2_g_buf1_base = ds2Info->ds2_r_buf1_base  + ds2Info->ds2_line_stride*2;
        ds2Info->ds2_b_buf0_base = ds2Info->ds2_r_buf0_base  + ds2Info->ds2_line_stride*3;   
        ds2Info->ds2_b_buf1_base = ds2Info->ds2_r_buf1_base  + ds2Info->ds2_line_stride*3;
        ds2Info->ds2_line_stride = ds2Info->ds2_line_stride*4;  
    }
    else
    {
        ds2Info->ds2_r_buf0_base = ds2_info->r_addr0;   
        ds2Info->ds2_r_buf1_base = ds2_info->r_addr1;
        ds2Info->ds2_g_buf0_base = ds2_info->g_addr0;   
        ds2Info->ds2_g_buf1_base = ds2_info->g_addr1;
        ds2Info->ds2_b_buf0_base = ds2_info->b_addr0;   
        ds2Info->ds2_b_buf1_base = ds2_info->b_addr1;     
        ds2Info->ds2_line_stride = ds2Info->ds2_line_stride; 
    }
    //
    ISP_DS_INFO_S *dsInfo = &isp_f2k_ds_info->dsInfo[2];
    dsInfo->scale_en = ds2_info->ds2_en;
    dsInfo->vscale_filter_en = ds2_info->ds2_en;  
    dsInfo->hscale_filter_en = ds2_info->ds2_en;
    dsInfo->ds_out_size.Width = ds2_info->ds2_width;
    dsInfo->ds_out_size.Height = ds2_info->ds2_height;

    return 0; 
}
/*
*
*/
int video_set_ispf2krgbir(enum _SENSOR_TYPE sensor_type,struct isp_rgbir_info *rgbir_info)
{
    ISP_CHECK_POINTER(rgbir_info); 
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }

    //
    struct _RGBIR_INFO_S *rgbirInfo = &isp_f2k_core_info->rgbirInfo;
    rgbirInfo->rgbir_en = rgbir_info->rgbir_en;        
    rgbirInfo->rgbir_rtf_en = rgbir_info->rgbir_en;    
    rgbirInfo->rgbir_rpc_en = rgbir_info->rgbir_en;    
    rgbirInfo->rgbir_fusion_en = rgbir_info->rgbir_en;    
    return 0; 
}
/*
*
*/
int video_set_ispf2kldc(enum _SENSOR_TYPE sensor_type,struct isp_ldc_info *ldc_info)
{
    ISP_CHECK_POINTER(ldc_info); 
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    ISP_WRAP_LDC_S *ldcWrapInfo = &isp_f2k_wrap_info->ldcInfo;
    ldcWrapInfo->ldc_en  = ldc_info->ldc_en;
    ldcWrapInfo->ldc_line_stride = ldc_info->stride;
    ldcWrapInfo->ldc_y_buf_base = ldc_info->y_addr; 
    ldcWrapInfo->ldc_uv_buf_base = ldc_info->uv_addr;
    //
    struct _LDC_INFO_S	*ldcCoreInfo = &isp_f2k_core_info->ldcInfo;
    ldcCoreInfo->ldc_en  = ldc_info->ldc_en;     
    ldcCoreInfo->ldc_arith_en  = ldc_info->ldc_en;   
    ldcCoreInfo->ldc_req_freq  = ldc_info->ldc_req_freq;   
    ldcCoreInfo->ldc_stt_ln  = ldc_info->ldc_stt_ln;
    ldcCoreInfo->ldc_h_center_pos  = ldc_info->ldc_h_center_pos;
    ldcCoreInfo->ldc_v_center_pos  = ldc_info->ldc_v_center_pos;
    ldcCoreInfo->ldc_rectify_cr  = ldc_info->ldc_rectify_cr; 
    ldcCoreInfo->ldc_rectify_cz  = ldc_info->ldc_rectify_cz; 

    return 0; 
}
/*
*
*/
int video_set_ispf2kwdr(enum _SENSOR_TYPE sensor_type,struct isp_wdr_info *wdr_info)
{
    ISP_CHECK_POINTER(wdr_info); 
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }

    ISP_WRAP_WDR_S  *wdrInfo = &isp_f2k_wrap_info->wdrInfo;
    wdrInfo->wdr_mode = wdr_info->wdr_mode;
    //
    struct _WDR_INFO_S	*wdrcoreInfo = &isp_f2k_core_info->wdrInfo;
    if(ISP_PIPE_WDR_2_FRAME == wdr_info->wdr_mode)
    {
        wdrcoreInfo->wdr_fusion_en= TRUE; 
        wdrcoreInfo->wdr_adp_adjust_en= TRUE;
        wdrcoreInfo->wdr_stab_en= TRUE;
        wdrcoreInfo->wdr_en= TRUE;
        wdrcoreInfo->wdr_ghost_remove_en= FALSE;
        wdrcoreInfo->wdr_mode_sel= 0x0; 
        wdrcoreInfo->wdr_2frame_ex_ratio= 0x0;//0x2;
        wdrcoreInfo->wdr_3frame_ex_ratio= 0x0;
        wdrcoreInfo->wdr_remove_purple_en= TRUE;  
    }
    else if(ISP_PIPE_WDR_3_FRAME == wdr_info->wdr_mode)
    {
        wdrcoreInfo->wdr_fusion_en= TRUE;//FALSE;//TRUE; 
        wdrcoreInfo->wdr_adp_adjust_en= FALSE;//FALSE;//TRUE;
        wdrcoreInfo->wdr_stab_en= TRUE;//FALSE;//TRUE;
        wdrcoreInfo->wdr_en= TRUE;
        wdrcoreInfo->wdr_ghost_remove_en= FALSE;
        wdrcoreInfo->wdr_mode_sel= 0x1; 
        wdrcoreInfo->wdr_2frame_ex_ratio= 0x0;
        wdrcoreInfo->wdr_3frame_ex_ratio= 0x2;//0x0;//0x2;
        wdrcoreInfo->wdr_remove_purple_en= TRUE; 
    }
    else
    {
        wdrcoreInfo->wdr_fusion_en= FALSE; 
        wdrcoreInfo->wdr_adp_adjust_en= FALSE;
        wdrcoreInfo->wdr_stab_en= FALSE;
        wdrcoreInfo->wdr_en= FALSE;
        wdrcoreInfo->wdr_ghost_remove_en= FALSE;
        wdrcoreInfo->wdr_mode_sel= 0x0; 
        wdrcoreInfo->wdr_2frame_ex_ratio= 0x0;
        wdrcoreInfo->wdr_3frame_ex_ratio= 0x0;//0x0;//0x2;
        wdrcoreInfo->wdr_remove_purple_en= FALSE;  
    }
     
    wdrcoreInfo->wdr_frame_sel= 0x0;//0x01;//
    wdrcoreInfo->wdr_3frame_out_mode= 0x0;

    wdrcoreInfo->wdr_stat_img_sel= 0x2;//0x1;//0x0;
    wdrcoreInfo->wdr_ltm_data_sel= 0x1;//0x0;

    wdrcoreInfo->wdr_tz_data_sel= 0x1;//0x0;

    wdrcoreInfo->wdr_over_ex_ratio_th1= 0x180;//0x180;    
    wdrcoreInfo->wdr_over_ex_ratio_th2= 0x20;
    wdrcoreInfo->wdr_fusion_ratio_th= 0xc0; //0xc0
    wdrcoreInfo->wdr_fusion_value1= 0x40;//0x00;
    wdrcoreInfo->wdr_fusion_value2= 0x10;//0xff;//0x00;//

    return 0; 
}
/*
*
*/
int video_set_ispf2knr3d(enum _SENSOR_TYPE sensor_type,struct isp_nr3d_info *nr3d_info)
{
    ISP_CHECK_POINTER(nr3d_info); 
    struct isp_f2k_device *f2k = &isp.isp_f2k;
    struct _ISP_WRAP_CFG_INFO *isp_f2k_wrap_info = &f2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_f2k_core_info = &f2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_f2k_ds_info   = &f2k->isp_ds_cfg;
    //
    if( 0 == ispf2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_f2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_f2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_f2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispf2kfirstdone = 1;
    }
    //
    ISP_WRAP_3DNR_S *nr3dwrapInfo = &isp_f2k_wrap_info->nr3dInfo;
    nr3dwrapInfo->nr3d_en = nr3d_info->nr3d_en;
    nr3dwrapInfo->nr3d_fbcd_en = nr3d_info->nr3d_fbcd_en;

    nr3dwrapInfo->nr3d_y_buf_base = nr3d_info->y_addr; 
    nr3dwrapInfo->nr3d_y_line_stride = ((nr3d_info->width*12/8 +15)/16)*16;//nr3d_info->y_stride;
    nr3dwrapInfo->nr3d_uv_buf_base = nr3d_info->y_addr + nr3dwrapInfo->nr3d_y_line_stride * nr3d_info->height;//nr3d_info->uv_addr;
    nr3dwrapInfo->nr3d_uv_line_stride = calc_stride(nr3d_info->width);//nr3d_info->uv_stride;	
    //
    struct _NR3D_INFO_S	*nr3dcoreInfo = &isp_f2k_core_info->nr3dInfo;
    nr3dcoreInfo->d3nr_en = nr3d_info->nr3d_en;            
    nr3dcoreInfo->d3nr_pre_luma_en = nr3d_info->nr3d_en;  
    nr3dcoreInfo->d3nr_pre_chroma_en = nr3d_info->nr3d_en; 
    nr3dcoreInfo->d3nr_main_luma_en = nr3d_info->nr3d_en;
    nr3dcoreInfo->d3nr_main_chroma_en = nr3d_info->nr3d_en;
    nr3dcoreInfo->d3nr_post_luma_en = nr3d_info->nr3d_en;  
    nr3dcoreInfo->d3nr_post_chroma_en = nr3d_info->nr3d_en;
    nr3dcoreInfo->d3nr_2d_luma_en = nr3d_info->nr3d_en;
    nr3dcoreInfo->d3nr_2d_chroma_en = nr3d_info->nr3d_en;  
    nr3dcoreInfo->d3nr_adp_luma_en = nr3d_info->nr3d_en;
    nr3dcoreInfo->d3nr_adp_chroma_en = nr3d_info->nr3d_en;   
    //fbc
    struct _FBC_INFO_S *fbcInfo = &isp_f2k_core_info->fbcInfo;
    fbcInfo->fbc_out_format_cfg = NR3D_YUV422_ENABLE;    
	fbcInfo->fbc_input_size.Width = nr3d_info->width; 
    fbcInfo->fbc_input_size.Height = nr3d_info->height;

	struct _FBCD_BUF_S *yDataBufInfo = &fbcInfo->yDataBufInfo;
    yDataBufInfo->data_buf_base0 = nr3d_info->y_fbcd_addr0;
    yDataBufInfo->data_buf_base1 = nr3d_info->y_fbcd_addr1;
    yDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    yDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;   
	struct _FBCD_BUF_S *yHeadBufInfo = &fbcInfo->yHeadBufInfo;
    yHeadBufInfo->data_buf_base0 = yDataBufInfo->data_buf_base0 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    yHeadBufInfo->data_buf_base1 = yDataBufInfo->data_buf_base1 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    yHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    yHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;

	struct _FBCD_BUF_S *uvDataBufInfo = &fbcInfo->uvDataBufInfo;
    uvDataBufInfo->data_buf_base0 = yHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvDataBufInfo->data_buf_base1 = yHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    uvDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;
	struct _FBCD_BUF_S *uvHeadBufInfo = &fbcInfo->uvHeadBufInfo;
    uvHeadBufInfo->data_buf_base0 = yHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvHeadBufInfo->data_buf_base1 = yHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    uvHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;

	struct _FBCD_BUF_S *ylDataBufInfo = &fbcInfo->ylDataBufInfo;
    ylDataBufInfo->data_buf_base0 = yHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    ylDataBufInfo->data_buf_base1 = yHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    ylDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    ylDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;
	struct _FBCD_BUF_S *ylHeadBufInfo = &fbcInfo->ylHeadBufInfo;
    ylHeadBufInfo->data_buf_base0 = yHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    ylHeadBufInfo->data_buf_base1 = yHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    ylHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    ylHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;
    //fbd
    struct _FBD_INFO_S *fbdInfo = &isp_f2k_core_info->fbdInfo;
    fbdInfo->fbd_en = nr3d_info->nr3d_fbcd_en;
    fbdInfo->fbd_format_cfg = NR3D_YUV422_ENABLE;

	fbdInfo->fbd_input_size.Width = nr3d_info->width; 
    fbdInfo->fbd_input_size.Height = nr3d_info->height; 

	struct _FBCD_BUF_S *ydDataBufInfo = &fbdInfo->yDataBufInfo;
    ydDataBufInfo->data_buf_base0 = nr3d_info->y_fbcd_addr0;
    ydDataBufInfo->data_buf_base1 = nr3d_info->y_fbcd_addr1;
    ydDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    ydDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;
	struct _FBCD_BUF_S *ydHeadBufInfo = &fbdInfo->yHeadBufInfo;
    ydHeadBufInfo->data_buf_base0 = yDataBufInfo->data_buf_base0 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    ydHeadBufInfo->data_buf_base1 = yDataBufInfo->data_buf_base1 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    ydHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    ydHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;

	struct _FBCD_BUF_S *uvdDataBufInfo = &fbdInfo->uvHeadBufInfo;
    uvdDataBufInfo->data_buf_base0 = yHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvdDataBufInfo->data_buf_base1 = yHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvdDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    uvdDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;
	struct _FBCD_BUF_S *uvdHeadBufInfo = &fbdInfo->uvHeadBufInfo;
    uvdHeadBufInfo->data_buf_base0 = uvDataBufInfo->data_buf_base0 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvdHeadBufInfo->data_buf_base1 = uvDataBufInfo->data_buf_base1 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height;
    uvdHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    uvdHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;

	struct _FBCD_BUF_S *yldDataBufInfo = &fbdInfo->ylDataBufInfo;
    yldDataBufInfo->data_buf_base0 = uvHeadBufInfo->data_buf_base0 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;      
    yldDataBufInfo->data_buf_base1 = uvHeadBufInfo->data_buf_base1 + ISP_BUF_FBCD_HEAD_STRIDE * fbcInfo->fbc_input_size.Height;      
    yldDataBufInfo->data_stride = ISP_BUF_FBCD_STRIDE;
    yldDataBufInfo->data_wr_blen = ISP_BUF_FBCD_BLEN;
	struct _FBCD_BUF_S *yldHeadBufInfo = &fbdInfo->ylHeadBufInfo;
    yldHeadBufInfo->data_buf_base0 = ylDataBufInfo->data_buf_base0 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height; 
    yldHeadBufInfo->data_buf_base1 = ylDataBufInfo->data_buf_base1 + ISP_BUF_FBCD_STRIDE * fbcInfo->fbc_input_size.Height; 
    yldHeadBufInfo->data_stride = ISP_BUF_FBCD_HEAD_STRIDE;
    yldHeadBufInfo->data_wr_blen = ISP_BUF_FBCD_HEAD_BLEN;

    return 0; 
}
/*
*
*/
int video_set_ispf2kint(struct isp_int_info *intinfo)
{
    ISP_CHECK_POINTER(intinfo); 

    ISP_WRAP_INT_CORE_S intCoreEn;
    intCoreEn.int_raw_in_en = intinfo->raw_en;
    if((1 == intinfo->awb_en)||(1 == intinfo->ae_en)||(1 == intinfo->af_en)) 
    {
        intCoreEn.int_3a_en= 1; 
    }     
    intCoreEn.raw_int_en= intinfo->raw_en;     
    intCoreEn.rgb_int_en = intinfo->rgb_en;     
    intCoreEn.yuv_int_en = intinfo->yuv_en;     
    intCoreEn.ldc_int_en = intinfo->ldc_en;     
    intCoreEn.main_out_int_en = intinfo->main_en;
    intCoreEn.isp_awb_int_en = intinfo->awb_en; 
    intCoreEn.isp_ae_int_en = intinfo->ae_en;  
    intCoreEn.isp_af_int_en = intinfo->af_en;      
    isp_f2k_wrap_setIntCore(&isp,&intCoreEn);

    //
    ISP_WRAP_INT_WR0_S intWr0En;
    intWr0En.wr_3dnr_y_frm_end_int_en = intinfo->nr3d_en;
    intWr0En.wr_3dnr_uv_frm_end_int_en = intinfo->nr3d_en;
    intWr0En.ldc_wr_y_frm_end_int_en = intinfo->ldc_en;
    intWr0En.ldc_wr_uv_frm_end_int_en = intinfo->ldc_en; 
    intWr0En.wdr_wr_raw_frm_end_int_en = intinfo->wdr_en;
    intWr0En.main_out_wr_y_frm_end_int_en = intinfo->main_en;       
    intWr0En.main_out_wr_uv_frm_end_int_en = intinfo->main_en;      
    isp_f2k_wrap_setIntWr0(&isp,&intWr0En);

    //
    ISP_WRAP_INT_WR1_S intWr1En;
    intWr1En.ds0_out_wr_y_frm_end_en = intinfo->ds0_en;
    intWr1En.ds0_out_wr_uv_frm_end_en = intinfo->ds0_en; 
    intWr1En.ds1_out_wr_y_frm_end_en = intinfo->ds1_en; 
    intWr1En.ds1_out_wr_uv_frm_end_en = intinfo->ds1_en;
    intWr1En.ds2_out_wr_r_frm_end_en = intinfo->ds2_en; 
    intWr1En.ds2_out_wr_g_frm_end_en = intinfo->ds2_en; 
    intWr1En.ds2_out_wr_b_frm_end_en = intinfo->ds2_en;
    isp_f2k_wrap_setIntWr1(&isp,&intWr1En);

    //
    ISP_WRAP_INT_RD0_S intRd0En;
    intRd0En.rd_3dnr_y_frm_end_int_en = intinfo->nr3d_en;       
    intRd0En.rd_3dnr_uv_frm_end_int_en = intinfo->nr3d_en;      
    intRd0En.ldc_rd_y_frm_end_int_en = intinfo->ldc_en;        
    intRd0En.ldc_rd_uv_frm_end_int_en = intinfo->ldc_en;     
    intRd0En.wdr_rd_raw_frm_end_int_en = intinfo->wdr_en; 
  
    isp_f2k_wrap_setIntRd0(&isp,&intRd0En);


    return 0; 
}
//
int video_set_ispf2k(unsigned int addr, unsigned int data)
{
    isp_reg_writel(&isp,data,ISP_IOMEM_F2K_CORE,addr-ISP_F_2K_CORE_BASE);
    return 0;
}
//
unsigned int video_get_ispf2k(unsigned int addr)
{
    unsigned int data;
    data = isp_reg_readl(&isp,ISP_IOMEM_F2K_CORE,addr-ISP_F_2K_CORE_BASE);
    return data;
}
/*******************************************************************************
 * r2k * 
 *******************************************************************************/
//struct _ISP_WRAP_CFG_INFO isp_r2k_wrap_info;
//struct _ISP_CORE_CFG_INFO isp_r2k_core_info;
//struct _ISP_DS_CFG_INFO isp_r2k_ds_info;
unsigned int ispr2kfirstdone = 0;
/*
*
*/
int video_set_ispr2kcommon(enum _SENSOR_TYPE sensor_type,struct isp_common_info *commoninfo)
{
    ISP_CHECK_POINTER(commoninfo); 
    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }
    //
    isp_r2k_wrap_info->isp_out_sel =  commoninfo->isp_out_sel;
    isp_r2k_wrap_info->dvp_ch_mode = BT1120_MIPI;
    //
    struct _ITC_INFO_S	*itcInfo = &isp_r2k_core_info->itcInfo;
    itcInfo->total_size.Width = commoninfo->totalsize_width;
    itcInfo->total_size.Height = commoninfo->totalsize_height;
    //itcInfo->itc_size.Width_st = 0x5;
    itcInfo->itc_size.Width = commoninfo->insize_width;
    //itcInfo->itc_size.Height_st = 0x2;
    itcInfo->itc_size.Height = commoninfo->insize_height;
    //
    struct _OTC_INFO_S *otcInfo = &isp_r2k_core_info->otcInfo;
    otcInfo->otc_out_size.Width_st = 0x4;
    otcInfo->otc_out_size.Width = commoninfo->outsize_width;
    otcInfo->otc_out_size.Height_st = 0x4;
    otcInfo->otc_out_size.Height = commoninfo->outsize_height;
    //
    isp_r2k_ds_info->dsInSizeInfo.Width = commoninfo->outsize_width;
    isp_r2k_ds_info->dsInSizeInfo.Height = commoninfo->outsize_height;

    return 0; 
}
//
int video_set_ispr2kmain0(enum _SENSOR_TYPE sensor_type,struct isp_main_info *main_info)
{
    ISP_CHECK_POINTER(main_info); 
    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }

    ISP_WRAP_MAIN_S	*mainInfo = &isp_r2k_wrap_info->mainInfo;
    mainInfo->main_out_en = main_info->main_en;
    mainInfo->main_pix_remap_en = 0;
    mainInfo->main_size.Width = main_info->width;
    mainInfo->main_size.Height = main_info->height;
    mainInfo->main_line_stride = calc_stride(main_info->width);//(main_info->width + 15)/16*16;//main_info->stride; 
    mainInfo->main_y_buf0_base = main_info->y_addr0;   
    mainInfo->main_y_buf1_base = main_info->y_addr1;
    mainInfo->main_uv_buf0_base= main_info->y_addr0 + mainInfo->main_line_stride * mainInfo->main_size.Height;   
    mainInfo->main_uv_buf1_base= main_info->y_addr1 + mainInfo->main_line_stride * mainInfo->main_size.Height;

    return 0; 
}
/*
*
*/
int video_set_ispr2kds0(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds0_info)
{
    ISP_CHECK_POINTER(ds0_info); 
    struct isp_r2k_device *r2k= &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS0_S *ds0Info = &isp_r2k_wrap_info->ds0Info;
    ds0Info->ds0_out_en     = ds0_info->ds_en;
    ds0Info->ds0_osd0_en    = 0;   
    ds0Info->ds0_osd1_en    = 0; 
    ds0Info->ds0_osd2_en    = 0;
    ds0Info->pix_remap_out0_en = 0;		 	
    ds0Info->ds0_size.Width = ds0_info->ds_width; 
    ds0Info->ds0_size.Height = ds0_info->ds_height;
    ds0Info->ds0_line_stride = calc_stride(ds0Info->ds0_size.Width);//ds0_info->stride;
    ds0Info->ds0_y_buf0_base = ds0_info->y_addr0;   
    ds0Info->ds0_y_buf1_base = ds0_info->y_addr1;
    ds0Info->ds0_uv_buf0_base = ds0Info->ds0_y_buf0_base + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;   
    ds0Info->ds0_uv_buf1_base = ds0Info->ds0_y_buf1_base + ds0Info->ds0_line_stride * ds0Info->ds0_size.Height;      
   //
    ISP_DS_INFO_S *dsInfo = &isp_r2k_ds_info->dsInfo[0];
    dsInfo->scale_en = ds0_info->ds_en;
    dsInfo->vscale_filter_en = ds0_info->ds_en;  
    dsInfo->hscale_filter_en = ds0_info->ds_en;
    dsInfo->ds_out_size.Width = ds0_info->ds_width;
    dsInfo->ds_out_size.Height = ds0_info->ds_height;
    dsInfo->out_uv_swap = ds0_info->uv_swap;
    return 0; 
}
/*
*
*/
int video_set_ispr2kds1(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds1_info)
{
    ISP_CHECK_POINTER(ds1_info); 

    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS1_S *ds1Info = &isp_r2k_wrap_info->ds1Info;
    ds1Info->ds1_out_en     = ds1_info->ds_en;
    ds1Info->ds1_osd0_en    = 0;   
    ds1Info->ds1_osd1_en    = 0; 
    ds1Info->ds1_osd2_en    = 0;
    ds1Info->pix_remap_out1_en = 0;		 	
    ds1Info->ds1_size.Width = ds1_info->ds_width; 
    ds1Info->ds1_size.Height = ds1_info->ds_height;
    ds1Info->ds1_line_stride = ds1_info->stride;//(ds1Info->ds1_size.Width);//ds1_info->stride;
    ds1Info->ds1_y_buf0_base = ds1_info->y_addr0;   
    ds1Info->ds1_y_buf1_base = ds1_info->y_addr1;
    ds1Info->ds1_uv_buf0_base = ds1Info->ds1_y_buf0_base + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;   
    ds1Info->ds1_uv_buf1_base = ds1Info->ds1_y_buf1_base + ds1Info->ds1_line_stride * ds1Info->ds1_size.Height;      
   //
    ISP_DS_INFO_S *dsInfo = &isp_r2k_ds_info->dsInfo[1];
    dsInfo->scale_en = ds1_info->ds_en;
    dsInfo->vscale_filter_en = ds1_info->ds_en;  
    dsInfo->hscale_filter_en = ds1_info->ds_en;
    dsInfo->ds_out_size.Width = ds1_info->ds_width;
    dsInfo->ds_out_size.Height = ds1_info->ds_height;
    dsInfo->out_uv_swap = ds1_info->uv_swap;

    return 0; 
}
/*
*
*/
int video_set_ispr2kds2(enum _SENSOR_TYPE sensor_type,struct isp_ds2_info *ds2_info)
{
    ISP_CHECK_POINTER(ds2_info); 
    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }
    //
    ISP_WRAP_DS2_S	*ds2Info = &isp_r2k_wrap_info->ds2Info;
    ds2Info->ds2_out_en     = ds2_info->ds2_en;
    ds2Info->ds2_osd0_en    = 0;   
    ds2Info->ds2_osd1_en    = 0; 
    ds2Info->ds2_osd2_en    = 0;
    //ds2Info->pix_remap_out2_en = 0;		 	
    ds2Info->ds2_size.Width = ds2_info->ds2_width; 
    ds2Info->ds2_size.Height = ds2_info->ds2_height;
    ds2Info->ds2_out_img_out_format  = ds2_info->ds2_rgb_type;
    ds2Info->ds2_line_stride = ds2_info->stride;//calc_stride(ds2Info->ds2_size.Width);//ds2_info->stride;

    if( OUT_ARGB == ds2Info->ds2_out_img_out_format)
    {
        ds2Info->ds2_r_buf0_base = ds2_info->r_addr0;   
        ds2Info->ds2_r_buf1_base = ds2_info->r_addr1;
        ds2Info->ds2_g_buf0_base = ds2Info->ds2_r_buf0_base  + ds2Info->ds2_line_stride*2;   
        ds2Info->ds2_g_buf1_base = ds2Info->ds2_r_buf1_base  + ds2Info->ds2_line_stride*2;
        ds2Info->ds2_b_buf0_base = ds2Info->ds2_r_buf0_base  + ds2Info->ds2_line_stride*3;   
        ds2Info->ds2_b_buf1_base = ds2Info->ds2_r_buf1_base  + ds2Info->ds2_line_stride*3;
        ds2Info->ds2_line_stride = ds2Info->ds2_line_stride*4;  
    }
    else
    {
        ds2Info->ds2_r_buf0_base = ds2_info->r_addr0;   
        ds2Info->ds2_r_buf1_base = ds2_info->r_addr1;
        ds2Info->ds2_g_buf0_base = ds2_info->g_addr0;   
        ds2Info->ds2_g_buf1_base = ds2_info->g_addr1;
        ds2Info->ds2_b_buf0_base = ds2_info->b_addr0;   
        ds2Info->ds2_b_buf1_base = ds2_info->b_addr1;     
        ds2Info->ds2_line_stride = ds2Info->ds2_line_stride; 
    }
    //
    ISP_DS_INFO_S *dsInfo = &isp_r2k_ds_info->dsInfo[2];
    dsInfo->scale_en = ds2_info->ds2_en;
    dsInfo->vscale_filter_en = ds2_info->ds2_en;  
    dsInfo->hscale_filter_en = ds2_info->ds2_en;
    dsInfo->ds_out_size.Width = ds2_info->ds2_width;
    dsInfo->ds_out_size.Height = ds2_info->ds2_height;

    return 0; 
}
/*
*
*/
int video_set_ispr2krgbir(enum _SENSOR_TYPE sensor_type,struct isp_rgbir_info *rgbir_info)
{
    ISP_CHECK_POINTER(rgbir_info); 
    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }

    //
    struct _RGBIR_INFO_S *rgbirInfo = &isp_r2k_core_info->rgbirInfo;
    rgbirInfo->rgbir_en = rgbir_info->rgbir_en;        
    rgbirInfo->rgbir_rtf_en = rgbir_info->rgbir_en;    
    rgbirInfo->rgbir_rpc_en = rgbir_info->rgbir_en;    
    rgbirInfo->rgbir_fusion_en = rgbir_info->rgbir_en;   

    return 0; 
}
/*
*
*/
int video_set_ispr2kldc(enum _SENSOR_TYPE sensor_type,struct isp_ldc_info *ldc_info)
{
    ISP_CHECK_POINTER(ldc_info); 
    struct isp_r2k_device *r2k = &isp.isp_r2k;
    struct _ISP_WRAP_CFG_INFO *isp_r2k_wrap_info = &r2k->isp_wrap_cfg;
    struct _ISP_CORE_CFG_INFO *isp_r2k_core_info = &r2k->isp_core_cfg;
    struct _ISP_DS_CFG_INFO   *isp_r2k_ds_info   = &r2k->isp_ds_cfg;
    //
    if(0 == ispr2kfirstdone)
    {
        if(IMX385_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx385_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx385_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx385_ds_info,sizeof(struct _ISP_DS_CFG_INFO));
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&jfx23s_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&jfx23s_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&jfx23s_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            memcpy(isp_r2k_wrap_info,&imx219_wrap_info,sizeof(struct _ISP_WRAP_CFG_INFO));
            memcpy(isp_r2k_core_info,&imx219_core_info,sizeof(struct _ISP_CORE_CFG_INFO));
            memcpy(isp_r2k_ds_info,&imx219_ds_info,sizeof(struct _ISP_DS_CFG_INFO));            
        }
        ispr2kfirstdone = 1;
    }
    //
    ISP_WRAP_LDC_S *ldcWrapInfo = &isp_r2k_wrap_info->ldcInfo;
    ldcWrapInfo->ldc_en  = ldc_info->ldc_en;
    ldcWrapInfo->ldc_line_stride = ldc_info->stride;
    ldcWrapInfo->ldc_y_buf_base = ldc_info->y_addr; 
    ldcWrapInfo->ldc_uv_buf_base = ldc_info->uv_addr;
    //
    struct _LDC_INFO_S	*ldcCoreInfo = &isp_r2k_core_info->ldcInfo;
    ldcCoreInfo->ldc_en  = ldc_info->ldc_en;     
    ldcCoreInfo->ldc_arith_en  = ldc_info->ldc_en;   
    ldcCoreInfo->ldc_req_freq  = ldc_info->ldc_req_freq;   
    ldcCoreInfo->ldc_stt_ln  = ldc_info->ldc_stt_ln;
    ldcCoreInfo->ldc_h_center_pos  = ldc_info->ldc_h_center_pos;
    ldcCoreInfo->ldc_v_center_pos  = ldc_info->ldc_v_center_pos;
    ldcCoreInfo->ldc_rectify_cr  = ldc_info->ldc_rectify_cr; 
    ldcCoreInfo->ldc_rectify_cz  = ldc_info->ldc_rectify_cz; 

    return 0; 
}
/*
*
*/
int video_set_ispr2kint(struct isp_int_info *intinfo)
{
    ISP_CHECK_POINTER(intinfo); 

    ISP_WRAP_INT_CORE_S intCoreEn;
    intCoreEn.int_raw_in_en = intinfo->raw_en;
    if((1 == intinfo->awb_en)||(1 == intinfo->ae_en)||(1 == intinfo->af_en)) 
    {
        intCoreEn.int_3a_en= 1; 
    }     
    intCoreEn.raw_int_en= intinfo->raw_en;     
    intCoreEn.rgb_int_en = intinfo->rgb_en;     
    intCoreEn.yuv_int_en = intinfo->yuv_en;     
    intCoreEn.ldc_int_en = intinfo->ldc_en;     
    intCoreEn.main_out_int_en = intinfo->main_en;
    intCoreEn.isp_awb_int_en = intinfo->awb_en; 
    intCoreEn.isp_ae_int_en = intinfo->ae_en;  
    intCoreEn.isp_af_int_en = intinfo->af_en;      
    isp_r2k_wrap_setIntCore(&isp,&intCoreEn);

    //
    ISP_WRAP_INT_WR0_S intWr0En;
    intWr0En.wr_3dnr_y_frm_end_int_en = intinfo->nr3d_en;
    intWr0En.wr_3dnr_uv_frm_end_int_en = intinfo->nr3d_en;
    intWr0En.ldc_wr_y_frm_end_int_en = intinfo->ldc_en;
    intWr0En.ldc_wr_uv_frm_end_int_en = intinfo->ldc_en; 
    intWr0En.wdr_wr_raw_frm_end_int_en = intinfo->wdr_en;
    intWr0En.main_out_wr_y_frm_end_int_en = intinfo->main_en;       
    intWr0En.main_out_wr_uv_frm_end_int_en = intinfo->main_en;      
    isp_r2k_wrap_setIntWr0(&isp,&intWr0En);

    //
    ISP_WRAP_INT_WR1_S intWr1En;
    intWr1En.ds0_out_wr_y_frm_end_en = intinfo->ds0_en;
    intWr1En.ds0_out_wr_uv_frm_end_en = intinfo->ds0_en; 
    intWr1En.ds1_out_wr_y_frm_end_en = intinfo->ds1_en; 
    intWr1En.ds1_out_wr_uv_frm_end_en = intinfo->ds1_en;
    intWr1En.ds2_out_wr_r_frm_end_en = intinfo->ds2_en; 
    intWr1En.ds2_out_wr_g_frm_end_en = intinfo->ds2_en; 
    intWr1En.ds2_out_wr_b_frm_end_en = intinfo->ds2_en;
    isp_r2k_wrap_setIntWr1(&isp,&intWr1En);

    //
    ISP_WRAP_INT_RD0_S intRd0En;
    intRd0En.rd_3dnr_y_frm_end_int_en = intinfo->nr3d_en;       
    intRd0En.rd_3dnr_uv_frm_end_int_en = intinfo->nr3d_en;      
    intRd0En.ldc_rd_y_frm_end_int_en = intinfo->ldc_en;        
    intRd0En.ldc_rd_uv_frm_end_int_en = intinfo->ldc_en;     
    intRd0En.wdr_rd_raw_frm_end_int_en = intinfo->wdr_en; 
    isp_r2k_wrap_setIntRd0(&isp,&intRd0En);

    return 0; 
}
//
int video_set_ispr2k(unsigned int addr, unsigned int data)
{
    isp_reg_writel(&isp,data,ISP_IOMEM_R2K_CORE,addr-ISP_R2K_BASE_ADDR);
    return 0;
}
/*******************************************************************************
 * vo * 
 *******************************************************************************/
extern struct _VO_CORE_INFO_S hdmi_vo_info;
//struct _VO_CORE_INFO_S vo_core_info;
unsigned int vofirstdone = 0; 
/*
*
*/
int video_set_display(struct vo_dispaly_info *dispaly_info)
{
    ISP_CHECK_POINTER(dispaly_info); 
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_DISP_INFO_S *dispInfo = &vo_core_info->dispInfo;
    dispInfo->dispEnable    = dispaly_info->dispEnable ;//1;
    dispInfo->xZoneCtl_start= dispaly_info->xZoneCtl_start;//VIDEO_DISP_ZONE_X_START;
    dispInfo->xZoneCtl_stop = dispaly_info->xZoneCtl_stop;//VIDEO_DISP_ZONE_X_STOP;
    dispInfo->yZoneCtl_start = dispaly_info->yZoneCtl_start;//VIDEO_DISP_ZONE_Y_START;
    dispInfo->yZoneCtl_stop =  dispaly_info->yZoneCtl_stop;//VIDEO_DISP_ZONE_Y_STOP;

    switch(dispaly_info->SyncMode)
    {
        case VO_SYSTEM_MODE_1920x1080x30P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x32;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x465;
			dispInfo->hsize= 0x898; 
            break;
        case VO_SYSTEM_MODE_1920x1080x25P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x32;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x465;
			dispInfo->hsize= 0xa50;         
            break; 
        case VO_SYSTEM_MODE_1280x720x50P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x2ee;
			dispInfo->hsize= 0x7bc;         
            break; 
        case VO_SYSTEM_MODE_1280x720x60P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x2ee;
			dispInfo->hsize= 0x672; 
            break; 
        case VO_SYSTEM_MODE_1280x720x30P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x2ee;
			dispInfo->hsize= 0xce4;         
            break; 
        case VO_SYSTEM_MODE_1280x720x25P:
			dispInfo->dispHsyncCtl_start= 0x6;
			dispInfo->dispHsyncCtl_stop= 0x2d;
		
			dispInfo->dispHsync1Ctl_start= 0x6;
			dispInfo->dispHsync1Ctl_stop= 0x6;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x6;
		
			dispInfo->dispHsync2Ctl_start= 0x6;
			dispInfo->dispHsync2Ctl_stop= 0x6;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x6;
			//
			dispInfo->vsize= 0x2ee;
			dispInfo->hsize= 0xf78;  
            break;
        case VO_SYSTEM_MODE_1080x1920x30P:
			dispInfo->dispHsyncCtl_start= 0x5;
			dispInfo->dispHsyncCtl_stop= 0x25;
		
			dispInfo->dispHsync1Ctl_start= 0x1;
			dispInfo->dispHsync1Ctl_stop= 0x5;
			dispInfo->dispVsync1Ctl_start= 0x1;
			dispInfo->dispVsync1Ctl_stop= 0x1;
		
			dispInfo->dispHsync2Ctl_start= 0x1;
			dispInfo->dispHsync2Ctl_stop= 0x5;
			dispInfo->dispVsync2Ctl_start= 0x1;
			dispInfo->dispVsync2Ctl_stop= 0x1;
			//
			dispInfo->vsize= 0x7a6;
			dispInfo->hsize= 0x53c;  
            break; 
        default:
            printf("ERR_VO_ILLEGAL_PARAM!\n");
            break;     
    }

    //dispInfo->hsize = dispaly_info->hsize;//2200;//0x898;
    //dispInfo->vsize = dispaly_info->vsize;//1125;//0x465;
    //
    VO_REMAP_CMD_INfO_S *remapcmdInfo = &vo_core_info->remapcmdInfo;
    remapcmdInfo->vo_out_imgtype = dispaly_info->vo_out_imgtype;
    remapcmdInfo->image_active_h = dispaly_info->vo_out_active_imgh;
    remapcmdInfo->image_active_v = dispaly_info->vo_out_active_imgv;
    return 0;   
}
/*
*
*/
int video_set_volayer0(struct vo_layer0_info *layer0_info)
{
    ISP_CHECK_POINTER(layer0_info); 

    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_LAYER0_INFO_S *layer0Info = &vo_core_info->layer0Info;
    layer0Info->layer0DispEn = layer0_info->layerEn;
    layer0Info->layer0En = layer0_info->layerEn; 
    //
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo = &layer0Info->datModeInfo;
    if(IN_YUV420 == layer0_info->yuvmode)
    {
        datModeInfo->datmode = 8;
    }
    else
    {
        datModeInfo->datmode = 9 ;
    }
    datModeInfo->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    datModeInfo->endianuv = layer0_info->endianuv;
    datModeInfo->swi = layer0_info->uvswap;//0;
    //
    VO_LAYER0_SIZE_INFO_S *sizeInfo = &layer0Info->sizeInfo;
    sizeInfo->in_hsize = layer0_info->in_hsize;
    sizeInfo->in_vsize = layer0_info->in_vsize;
    sizeInfo->out_hsize = layer0_info->out_hsize;
    sizeInfo->out_vsize = layer0_info->out_vsize;
    //
    VO_LAYER_AREA_INFO_S  *areaInfo = &layer0Info->areaInfo;
    areaInfo->xCtl_start = layer0_info->layer_x_start;
    areaInfo->xCtl_stop  = areaInfo->xCtl_start + sizeInfo->out_hsize;
    areaInfo->yCtl_start = layer0_info->layer_y_start;
    areaInfo->yCtl_stop  = areaInfo->yCtl_start + sizeInfo->out_vsize;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer0Info->bufInfo;
    bufInfo->hsize_stride = calc_stride(sizeInfo->in_hsize);//layer0_info->layer_stride;
    bufInfo->vsize_stride = layer0_info->out_vsize;
    bufInfo->yAddr0 = layer0_info->layer_yAddr0;
    bufInfo->yAddr1 = layer0_info->layer_yAddr1;
    bufInfo->uvAddr0 = layer0_info->layer_yAddr0 + bufInfo->hsize_stride * sizeInfo->in_vsize;
    bufInfo->uvAddr1 = layer0_info->layer_yAddr1 + bufInfo->hsize_stride * sizeInfo->in_vsize; 
    //
    VO_LAYER0_MFBD_INFO_S   *fbdInfo = &layer0Info->mfbdInfo;
    fbdInfo->mfbd_en = layer0_info->fbd_en;
    fbdInfo->y_addr0 = layer0_info->fbd_y_addr0;	
    fbdInfo->y_addr1 = layer0_info->fbd_y_addr1;
    fbdInfo->y_stride0 = layer0_info->fbd_y_stride;
    fbdInfo->y_stride1 = layer0_info->fbd_y_stride;
    fbdInfo->y_head_addr0 = layer0_info->fbd_y_head_addr0;	
    fbdInfo->y_head_addr1 = layer0_info->fbd_y_head_addr1;
    fbdInfo->y_head_stride0 = layer0_info->fbd_y_head_stride;
    fbdInfo->y_head_stride1 = layer0_info->fbd_y_head_stride;
    fbdInfo->uv_addr0 = layer0_info->fbd_uv_addr0;
    fbdInfo->uv_addr1 = layer0_info->fbd_uv_addr1;
    fbdInfo->uv_stride0 = layer0_info->fbd_uv_stride;
    fbdInfo->uv_stride1 = layer0_info->fbd_uv_stride;
    fbdInfo->uv_head_addr0 = layer0_info->fbd_uv_head_addr0;
    fbdInfo->uv_head_addr1 = layer0_info->fbd_uv_head_addr1;
    fbdInfo->uv_head_stride0 = layer0_info->fbd_uv_head_stride;
    fbdInfo->uv_head_stride1 = layer0_info->fbd_uv_head_stride;

    return 0; 
}
/*
*
*/
int video_set_volayer1(struct vo_layer_info *layer1_info)
{
    ISP_CHECK_POINTER(layer1_info); 

    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_LAYER1_INFO_S *layer1Info = &vo_core_info->layer1Info;
    layer1Info->layer1DispEn = layer1_info->layerEn;//vo_addr->layer1_en;
    layer1Info->layerInfo.enable = layer1_info->layerEn;
    layer1Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Info->layerInfo.endianuv = layer1_info->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer1Info->layerInfo.uvswap = layer1_info->uvswap;//0;
    if(IN_YUV420 == layer1_info->yuvmode)
    {
        layer1Info->layerInfo.yuv420en = 1;
        layer1Info->layerInfo.yuv422en = 0;
    }    
    else
    {
        layer1Info->layerInfo.yuv420en = 0;
        layer1Info->layerInfo.yuv422en = 1;        
    }
    //
    layer1Info->layer1SizeInfo.in_hsize = layer1_info->in_hsize;
    layer1Info->layer1SizeInfo.in_vsize = layer1_info->in_vsize;
    //
    layer1Info->bufInfo.hsize_stride = calc_stride(layer1Info->layer1SizeInfo.in_hsize);//layer1_info->layer_stride;
    layer1Info->bufInfo.vsize_stride = layer1_info->in_vsize;
    layer1Info->bufInfo.yAddr0  = layer1_info->layer_yAddr0;
    layer1Info->bufInfo.yAddr1  = layer1_info->layer_yAddr1;
    layer1Info->bufInfo.uvAddr0 = layer1_info->layer_yAddr0 + layer1Info->bufInfo.hsize_stride * layer1Info->layer1SizeInfo.in_vsize;
    layer1Info->bufInfo.uvAddr1 = layer1_info->layer_yAddr1 + layer1Info->bufInfo.hsize_stride * layer1Info->layer1SizeInfo.in_vsize;
    //
    layer1Info->areaInfo.xCtl_start = layer1_info->layer_x_start;
    layer1Info->areaInfo.xCtl_stop  = layer1Info->areaInfo.xCtl_start + layer1Info->layer1SizeInfo.in_hsize;
    layer1Info->areaInfo.yCtl_start = layer1_info->layer_y_start;
    layer1Info->areaInfo.yCtl_stop  = layer1Info->areaInfo.yCtl_start + layer1Info->layer1SizeInfo.in_vsize;

    return 0;    
}
/*
*
*/
int video_set_volayer2(struct vo_layer_info *layer2_info)
{
    ISP_CHECK_POINTER(layer2_info); 
    
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_LAYER2_INFO_S *layer2Info = &vo_core_info->layer2Info;
    layer2Info->layer2DispEn = layer2_info->layerEn;//vo_addr->layer2_en;
    layer2Info->layerInfo.enable = layer2_info->layerEn;
    layer2Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Info->layerInfo.endianuv = layer2_info->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Info->layerInfo.uvswap = layer2_info->uvswap;//0;
    if(IN_YUV420 == layer2_info->yuvmode)
    {
        layer2Info->layerInfo.yuv420en = 1;
        layer2Info->layerInfo.yuv422en = 0;
    }    
    else
    {
        layer2Info->layerInfo.yuv420en = 0;
        layer2Info->layerInfo.yuv422en = 1;        
    }
    //
    layer2Info->layer2SizeInfo.in_hsize = layer2_info->in_hsize;
    layer2Info->layer2SizeInfo.in_vsize = layer2_info->in_vsize;
    //
    layer2Info->bufInfo.hsize_stride = calc_stride(layer2Info->layer2SizeInfo.in_hsize);//layer2_info->layer_stride;
    layer2Info->bufInfo.vsize_stride = layer2_info->in_vsize;
    layer2Info->bufInfo.yAddr0  = layer2_info->layer_yAddr0;
    layer2Info->bufInfo.yAddr1  = layer2_info->layer_yAddr1;
    layer2Info->bufInfo.uvAddr0 = layer2_info->layer_yAddr0 + layer2Info->bufInfo.hsize_stride * layer2Info->layer2SizeInfo.in_vsize;
    layer2Info->bufInfo.uvAddr1 = layer2_info->layer_yAddr1 + layer2Info->bufInfo.hsize_stride * layer2Info->layer2SizeInfo.in_vsize;
    //
    layer2Info->areaInfo.xCtl_start = layer2_info->layer_x_start;
    layer2Info->areaInfo.xCtl_stop  = layer2Info->areaInfo.xCtl_start + layer2Info->layer2SizeInfo.in_hsize;
    layer2Info->areaInfo.yCtl_start = layer2_info->layer_y_start;
    layer2Info->areaInfo.yCtl_stop  = layer2Info->areaInfo.yCtl_start + layer2Info->layer2SizeInfo.in_vsize;

    return 0;      
}
/*
*
*/
int video_set_volayer3(struct vo_layer_info *layer3_info)
{
    ISP_CHECK_POINTER(layer3_info); 
    
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_LAYER3_INFO_S *layer3Info = &vo_core_info->layer3Info;
    layer3Info->layer3DispEn = layer3_info->layerEn;//vo_addr->layer3_en;
    layer3Info->layerInfo.enable = layer3_info->layerEn;
    layer3Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer3Info->layerInfo.endianuv = layer3_info->endianuv;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer3Info->layerInfo.uvswap = layer3_info->uvswap;//0;
    if(IN_YUV420 == layer3_info->yuvmode)
    {
        layer3Info->layerInfo.yuv420en = 1;
        layer3Info->layerInfo.yuv422en = 0;
    }    
    else
    {
        layer3Info->layerInfo.yuv420en = 0;
        layer3Info->layerInfo.yuv422en = 1;        
    }
    //
    layer3Info->layer3SizeInfo.in_hsize = layer3_info->in_hsize;
    layer3Info->layer3SizeInfo.in_vsize = layer3_info->in_vsize;
    //
    layer3Info->bufInfo.hsize_stride = calc_stride(layer3Info->layer3SizeInfo.in_hsize);//layer3_info->layer_stride;
    layer3Info->bufInfo.vsize_stride = layer3_info->in_vsize;
    layer3Info->bufInfo.yAddr0  = layer3_info->layer_yAddr0;
    layer3Info->bufInfo.yAddr1  = layer3_info->layer_yAddr1;
    layer3Info->bufInfo.uvAddr0 = layer3_info->layer_yAddr0 + layer3Info->bufInfo.hsize_stride * layer3Info->layer3SizeInfo.in_vsize;
    layer3Info->bufInfo.uvAddr1 = layer3_info->layer_yAddr1 + layer3Info->bufInfo.hsize_stride * layer3Info->layer3SizeInfo.in_vsize;
    //
    layer3Info->areaInfo.xCtl_start = layer3_info->layer_x_start;
    layer3Info->areaInfo.xCtl_stop  = layer3Info->areaInfo.xCtl_start + layer3Info->layer3SizeInfo.in_hsize;
    layer3Info->areaInfo.yCtl_start = layer3_info->layer_y_start;
    layer3Info->areaInfo.yCtl_stop  = layer3Info->areaInfo.yCtl_start + layer3Info->layer3SizeInfo.in_vsize;

    return 0;    
}
/**
*
*/
int video_set_volayer4osd0(struct vo_layer_osd_info *osd0_info)
{
    ISP_CHECK_POINTER(osd0_info); 
    
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_OSD0_INFO_S *osd0Info = &vo_core_info->osd0Info;
    osd0Info->osdLayer4DispEn = osd0_info->osdEn;
    osd0Info->osdrgb2yuvEn = osd0_info->osdEn;
    osd0Info->osdtype   = osd0_info->osdtype;
    osd0Info->alphatpye = osd0_info->alphatpye;
    //
    VO_OSD_SIZE_INFO_S *osd0SizeInfo = &osd0Info->osd0SizeInfo;
    osd0SizeInfo->width = osd0_info->width;
    osd0SizeInfo->height = osd0_info->height;
    //
    VO_LAYER_AREA_INFO_S *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    osd0AreaInfo->xCtl_start = osd0_info->osd_x_start;
    osd0AreaInfo->xCtl_stop = osd0AreaInfo->xCtl_start + osd0SizeInfo->width;
    osd0AreaInfo->yCtl_start = osd0_info->osd_y_start;
    osd0AreaInfo->yCtl_stop = osd0AreaInfo->yCtl_start + osd0SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd0BufInfo = &osd0Info->osd0BufInfo;
    osd0BufInfo->alp_addr0 = osd0_info->alp_addr0;
    osd0BufInfo->alp_addr1 = osd0_info->alp_addr1;
    osd0BufInfo->vlu_addr0 = osd0_info->vlu_addr0;
    osd0BufInfo->vlu_addr1 = osd0_info->vlu_addr1;
    if(OSD_RGB_24BIT == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width)*3;//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width)*3;//osd0_info->osdstride;
    }
    else if(OSD_MONOCHROME_8BIT == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width);//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width);//osd0_info->osdstride;
    }
    else if(OSD_RGB_16BIT == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->osdstride;
    }
    else if(OSD_RGB_32BIT == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width)*4;//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width)*4;//osd0_info->osdstride;
    }
    else if(OSD_RGB_4444 == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->osdstride;
    }
    else if(OSD_RGB_1555 == osd0Info->osdtype)
    {
        osd0BufInfo->alpstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->alpstride;
        osd0BufInfo->osdstride = calc_stride(osd0SizeInfo->width)*2;//osd0_info->osdstride;
    }
    //
    VO_OSD_DMA_INFO_S *osd0DmaInfo = &osd0Info->osd0DmaInfo; 
    osd0DmaInfo->rgbrev = osd0_info->rgbrev;
    return 0;    
}
/*
*
*/
int video_set_volayer5osd1(struct vo_layer_osd_info *osd1_info)
{
    ISP_CHECK_POINTER(osd1_info); 
    
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_OSD1_INFO_S *osd1Info = &vo_core_info->osd1Info;
    osd1Info->osdLayer5DispEn = osd1_info->osdEn;
    osd1Info->osdrgb2yuvEn = osd1_info->osdEn;
    osd1Info->osdtype   = osd1_info->osdtype;
    osd1Info->alphatpye = osd1_info->alphatpye;
    //
    VO_OSD_SIZE_INFO_S *osd1SizeInfo = &osd1Info->osd1SizeInfo;
    osd1SizeInfo->width = osd1_info->width;
    osd1SizeInfo->height = osd1_info->height;
    //
    VO_LAYER_AREA_INFO_S *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    osd1AreaInfo->xCtl_start = osd1_info->osd_x_start;
    osd1AreaInfo->xCtl_stop = osd1AreaInfo->xCtl_start + osd1SizeInfo->width;
    osd1AreaInfo->yCtl_start =osd1_info->osd_y_start;
    osd1AreaInfo->yCtl_stop = osd1AreaInfo->yCtl_start + osd1SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd1BufInfo = &osd1Info->osd1BufInfo;
    osd1BufInfo->alp_addr0 = osd1_info->alp_addr0;
    osd1BufInfo->alp_addr1 = osd1_info->alp_addr1;

    osd1BufInfo->vlu_addr0 = osd1_info->vlu_addr0;
    osd1BufInfo->vlu_addr1 = osd1_info->vlu_addr1;
    if(OSD_RGB_24BIT == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width)*3;//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width)*3;//osd1_info->osdstride;
    }
    else if(OSD_MONOCHROME_8BIT == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width);//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width);//osd1_info->osdstride;
    }
    else if(OSD_RGB_16BIT == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->osdstride;
    }
    else if(OSD_RGB_32BIT == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width)*4;//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width)*4;//osd1_info->osdstride;
    }
    else if(OSD_RGB_4444 == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->osdstride;
    }
    else if(OSD_RGB_1555 == osd1Info->osdtype)
    {
        osd1BufInfo->alpstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->alpstride;
        osd1BufInfo->osdstride = calc_stride(osd1SizeInfo->width)*2;//osd1_info->osdstride;
    }
    //
    VO_OSD_DMA_INFO_S *osd1DmaInfo = &osd1Info->osd1DmaInfo; 
    osd1DmaInfo->rgbrev = osd1_info->rgbrev;
    return 0;    
}
/*
*
*/
int video_set_volayer6osd2(struct vo_layer_osd_info *osd2_info)
{
    ISP_CHECK_POINTER(osd2_info); 
    
    struct isp_vo_device *vo = &isp.isp_vo;
    struct _VO_CORE_INFO_S *vo_core_info = &vo->vo_core_info;
    if( 0 == vofirstdone)
    {
        memcpy(vo_core_info,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));
        vofirstdone = 1;
    }

    VO_OSD2_INFO_S *osd2Info = &vo_core_info->osd2Info;
    osd2Info->osdLayer6DispEn = osd2_info->osdEn;
    osd2Info->osdrgb2yuvEn = osd2_info->osdEn;
    osd2Info->osdtype   = osd2_info->osdtype;
    osd2Info->alphatpye = osd2_info->alphatpye;
    //
    VO_OSD_SIZE_INFO_S *osd2SizeInfo = &osd2Info->osd2SizeInfo;
    osd2SizeInfo->width = osd2_info->width;
    osd2SizeInfo->height = osd2_info->height;
    //
    VO_LAYER_AREA_INFO_S *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    osd2AreaInfo->xCtl_start = osd2_info->osd_x_start;
    osd2AreaInfo->xCtl_stop = osd2AreaInfo->xCtl_start + osd2SizeInfo->width;
    osd2AreaInfo->yCtl_start =osd2_info->osd_y_start;
    osd2AreaInfo->yCtl_stop = osd2AreaInfo->yCtl_start + osd2SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd2BufInfo = &osd2Info->osd2BufInfo;
    osd2BufInfo->alp_addr0 = osd2_info->alp_addr0;
    osd2BufInfo->alp_addr1 = osd2_info->alp_addr1;
    osd2BufInfo->vlu_addr0 = osd2_info->vlu_addr0;
    osd2BufInfo->vlu_addr1 = osd2_info->vlu_addr1;
    if(OSD_RGB_24BIT == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width)*3;//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width)*3;//osd2_info->osdstride;
    }
    else if(OSD_MONOCHROME_8BIT == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width);//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width);//osd2_info->osdstride;
    }
    else if(OSD_RGB_16BIT == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->osdstride;
    }
    else if(OSD_RGB_32BIT == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width)*4;//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width)*4;//osd2_info->osdstride;
    }
    else if(OSD_RGB_4444 == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->osdstride;
    }
    else if(OSD_RGB_1555 == osd2Info->osdtype)
    {
        osd2BufInfo->alpstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->alpstride;
        osd2BufInfo->osdstride = calc_stride(osd2SizeInfo->width)*2;//osd2_info->osdstride;
    }
    //
    VO_OSD_DMA_INFO_S *osd2DmaInfo = &osd2Info->osd2DmaInfo; 
    osd2DmaInfo->rgbrev = osd2_info->rgbrev;

    return 0;
}
/*
*
*/
int video_set_voint(struct vo_disp_irq_info *irq_info)
{
    ISP_CHECK_POINTER(irq_info); 

    VO_DISP_IRQ_INFO_S dispIrqInfo;
    dispIrqInfo.en0 = irq_info->vo_disp_irq0_en;
    dispIrqInfo.underrundcnt0  = 0;
    dispIrqInfo.en1= irq_info->vo_disp_irq1_en;
    dispIrqInfo.underrundcnt1  = 0;
    dispIrqInfo.en2 = irq_info->vo_disp_irq2_en;
    dispIrqInfo.underrundcnt2  = 0;
    Vo_Core_SetDispIrq(&isp,&dispIrqInfo);

    return 0;
}
/*
*
*/
int video_draw_frame(unsigned int draw_en,unsigned int DrawAreaNum,frame_coordinate_info frame_coordinate)
{   
    Vo_Remap_DrawFrame(&isp,draw_en,0, DrawAreaNum,frame_coordinate);
    return 0;
}
/************************************************************************************
 * bt1120
 * **********************************************************************************/
int video_set_bt1120(struct hdmi_bt1120_info *bt1120_info)
{
    struct isp_bt1120_device *bt1120 = &isp.isp_bt1120;
    printf("video_set_bt1120\n");
    struct bt1120_cfg_info *bt1120info = &bt1120->bt1120_info;
    bt1120info->bt1120_en = bt1120_info->bt1120_en;//1;
    bt1120info->bt_in_sel = bt1120_info->bt_in_sel;//SEL_VO;
    bt1120info->img_vsize_total = bt1120_info->img_vsize_total;//1125;
    bt1120info->img_hsize_total = bt1120_info->img_hsize_total;//2200;
    bt1120info->img_vsize = bt1120_info->img_vsize;//1080;
    bt1120info->img_hsize = bt1120_info->img_hsize;//1920;   
}
/************************************************************************************
 * sensor
 * **********************************************************************************/
void video_set_ae_dgain_cfg(unsigned int expl)
{
    imx219_ae_dgain_cfg(expl);
}

void video_set_ae_again_cfg(unsigned int agc)
{
    imx219_ae_again_cfg(agc);
}
/************************************************************************************
 * pipeline
 * **********************************************************************************/
/**
 * @brief 
 * 
 */
int run_video(enum _SENSOR_TYPE sensor_type, enum _SENSOR_MODE sensor_mode, enum _LCD_TYPE lcd_type,enum _ISP_PIPELINE_E isp_pipeline,unsigned int debug_en)
{
    /*open device node*/
    printf("run_video!!\n");
    fd_isp = open(DEV_NAME, O_RDWR | O_CLOEXEC);
    if (fd_isp < 0)
    {
        printf("Open %s Error!\n", DEV_NAME);
        return -1;
    }
    else
        printf("Open %S ok!\n", DEV_NAME);

    

    // reset isp 
    if (ioctl(fd_isp, ISP_CMD_ISP_RESET, 0) < 0)
    {
        printf("Call cmd ISP_CMD_ISP_RESET fail\n");
    }   

    //
/*
    printf("Open i2c0!!\n");
    fd_i2c0 = open(DEV_NAME_I2C0, O_RDWR);
    
    if (fd_i2c0 < 0)
    {
        printf("Open %s Error!\n", DEV_NAME_I2C0);
        return -1;
    }
    else
        printf("Open %s ok!\n", DEV_NAME_I2C0);
        

    unsigned char *mapI2C = mmap(NULL, 0x20000, PROT_READ|PROT_WRITE, MAP_SHARED, fd_i2c0, 0);
    if(mapI2C == NULL)
    {
        printf("i2c mmap failed\n");
        return -1;
    }
    i2c[0] = (i2c_t *)mapI2C;
    i2c[1] = (i2c_t *)(mapI2C + 0x10000);

    if (ioctl(fd_i2c0, I2C0_CMD_TEST, 4) < 0)
    {
        printf("Call cmd ISP_CMD_WRITE_REG fail, reg %u\n", reg_isp.id);
        return -1;
    }
    
    printf("i2c0 reg tar = 0x%x\n", i2c[0]->tar);
    printf("i2c1 reg tar = 0x%x\n", i2c[1]->tar);
    i2c[0]->tar = 0x12;
    i2c[1]->tar = 0x23;
    printf("test i2c0 reg tar = 0x%x\n", i2c[0]->tar);
    printf("test i2c1 reg tar = 0x%x\n", i2c[1]->tar);    
*/
    //
    isp.mmio_base[ISP_IOMEM_CSI0_HOST] = CSI_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_CSI1_HOST] = CSI1_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_MIPI_DPHY] = MIPI_DPHY_BASE;
    isp.mmio_base[ISP_IOMEM_MIPI_CORNER] = MIPI_CORNER_BASE;
	isp.mmio_base[ISP_IOMEM_VI_WRAP] = VI_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI00] = VI_PIPE_CSI_0_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI01] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI02] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI10] = VI_PIPE_CSI_1_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI11] = VI_PIPE_CSI_1_1_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI12] = VI_PIPE_CSI_1_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP0] = VI_PIPE_DVP_0_REG_BASE;	
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP1] = VI_PIPE_DVP_1_REG_BASE;		
	isp.mmio_base[ISP_IOMEM_F2K_WRAP] = ISP_F_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE] = ISP_F_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE_TABLE] = ISP_F_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBC] = ISP_F_2K_FBC_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBD] = ISP_F_2K_FBD_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_DS] = ISP_F_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT0_REMAP] = ISP_F_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT1_REMAP] = ISP_F_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_MAIN_REMAP] = ISP_F_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_WRAP] = ISP_R_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE] = ISP_R_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE_TABLE] = ISP_R_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_DS] = ISP_R_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT0_REMAP] = ISP_R_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT1_REMAP] = ISP_R_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_MAIN_REMAP] = ISP_R_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_WRAP] = TOF_WRAP_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_CORE] = TOF_CORE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_TABLE] = TOF_TABLE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_FBC_WRAP] = FBC_WRAP_BASE;
    isp.mmio_base[ISP_IOMEM_FBC_CORE] = FBC_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_CORE] = VO_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_REMAP] = VO_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_VO_HSCALE] = VO_HSCALE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_VSCALE] = VO_VSCALE_BASE;
    isp.mmio_base[ISP_IOMEM_VO_GAMMA] = VO_GAMMA_BASE; 
    isp.mmio_base[ISP_IOMEM_BT1120] = BT1120_BASE_ADDR; 
    printf("struct isp_device addr = 0x%x,vi = 0x%x,mmio_base = 0x%x\n",&isp,&isp.isp_vi,isp.mmio_base[ISP_IOMEM_VI_WRAP]);


//    open_camera_power();

    // 
    if( lcd_type == BT1120_DISPLAY)  
    {
        bt1120_Init(&isp);
    }
    else if(lcd_type == AML550_LCD)
    {
//        aml550_power_on_seq();
//        aml550_22v_power_en();
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
        }
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
    //    
    }
    else if(lcd_type == ITI7807_LCD)
    {
//        aml550_power_on_seq();
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_ILI7807_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_ILI7807_INIT fail\n");
        }   
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
//        sleep(1);
//        aml550_22v_power_en();  
    }
    else if(lcd_type == HX8399)
    {
//        aml550_power_on_seq();
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_HX8399_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_HX8399_INIT fail\n");
        }   
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
//        sleep(1);
//        aml550_22v_power_en();  
    }  

    /*reset whole video system start*/
    fpga_system_init(0);

    /*********open camera power******************/
    /*reset whole video system end*/    
    if(IMX385_SENSOR == sensor_type)
    {
        imx385_i2c_init(MIPI_CSI0_I2C);
    }
    else if(JFX23S_SENSOR == sensor_type)
    {
//        hmdi_init_dvp();
        jfx23s_i2c_init(DVP_I2C);
    }
    else if(IMX219_SENSOR == sensor_type)
    {
        imx219_i2c_init(MIPI_CSI0_I2C);
    }
    //
    if(ISP_F_2K == isp_pipeline)
    {
        Isp_f2k_Init(&isp);
        //
        video_in_Init(&isp);
        //
        if(IMX385_SENSOR == sensor_type)
        {
            mipi_csi_init(&isp);
            imx385_sensor_config();
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
            jxf23s_sensor_config();
            //jxs23s_sensor_15fps_config();
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            mipi_csi_init(&isp);

            if(sensor_mode == IMX219_1920_1080)
            {
                
                imx219_sensor_config();
            }
            else
            {
                imx219_1080_1920_sensor_config();
            }          
        }
        //
        sleep(1);
        isp_f2k_core_table_init(&isp);
        sleep(1);
    }
    else if (ISP_R_2K == isp_pipeline)
    {
        Isp_r2k_Init(&isp);
        video_in_Init(&isp);
        if(IMX385_SENSOR == sensor_type)
        {
            mipi_csi_init(&isp);
            imx385_sensor_config();
        }
        else if(JFX23S_SENSOR == sensor_type)
        {
//            jxf23s_sensor_config(); //30FPS
            jxf23s_sensor_config();
        }
        else if(IMX219_SENSOR == sensor_type)
        {
            mipi_csi_init(&isp);
            if(sensor_mode == IMX219_1920_1080)
            {
                imx219_sensor_config();
            }
            else
            {
                imx219_1080_1920_sensor_config();
            }  
//            imx219_sensor_config();
        }
        sleep(1);
        isp_r2k_core_table_init(&isp);
        sleep(1);
    }    
    //
    Vo_Out_Init(&isp);
    //
    if( BT1120_DISPLAY == lcd_type)  
    {
        cv8788Init();
    }
    //
    debug(debug_en,ISP_PIPE_MODE_F2K);
    return  fd_isp;
}
/**
 * @brief 
 * * 
 * 
 * @param isp_pipeline 
 * @param lcd_type 
 * @return int 
 */
int run_multi_video(struct isp_pipeline_info *isp_pipeline,enum _LCD_TYPE lcd_type,unsigned int debug_en)
{
    printf("run_multi_video!!\n");
    fd_isp = open(DEV_NAME, O_RDWR | O_CLOEXEC);
    if (fd_isp < 0)
    {
        printf("Open %s Error!\n", DEV_NAME);
        return -1;
    }
    else
        printf("Open %S ok!\n", DEV_NAME);

    // reset isp 
    if (ioctl(fd_isp, ISP_CMD_ISP_RESET, 0) < 0)
    {
        printf("Call cmd ISP_CMD_ISP_RESET fail\n");
    }  

    isp.mmio_base[ISP_IOMEM_CSI0_HOST] = CSI_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_CSI1_HOST] = CSI1_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_MIPI_DPHY] = MIPI_DPHY_BASE;
    isp.mmio_base[ISP_IOMEM_MIPI_CORNER] = MIPI_CORNER_BASE;
	isp.mmio_base[ISP_IOMEM_VI_WRAP] = VI_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI00] = VI_PIPE_CSI_0_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI01] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI02] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI10] = VI_PIPE_CSI_1_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI11] = VI_PIPE_CSI_1_1_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI12] = VI_PIPE_CSI_1_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP0] = VI_PIPE_DVP_0_REG_BASE;	
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP1] = VI_PIPE_DVP_1_REG_BASE;		
	isp.mmio_base[ISP_IOMEM_F2K_WRAP] = ISP_F_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE] = ISP_F_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE_TABLE] = ISP_F_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBC] = ISP_F_2K_FBC_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBD] = ISP_F_2K_FBD_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_DS] = ISP_F_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT0_REMAP] = ISP_F_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT1_REMAP] = ISP_F_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_MAIN_REMAP] = ISP_F_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_WRAP] = ISP_R_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE] = ISP_R_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE_TABLE] = ISP_R_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_DS] = ISP_R_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT0_REMAP] = ISP_R_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT1_REMAP] = ISP_R_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_MAIN_REMAP] = ISP_R_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_WRAP] = TOF_WRAP_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_CORE] = TOF_CORE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_TABLE] = TOF_TABLE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_FBC_WRAP] = FBC_WRAP_BASE;
    isp.mmio_base[ISP_IOMEM_FBC_CORE] = FBC_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_CORE] = VO_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_REMAP] = VO_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_VO_HSCALE] = VO_HSCALE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_VSCALE] = VO_VSCALE_BASE;
    isp.mmio_base[ISP_IOMEM_VO_GAMMA] = VO_GAMMA_BASE; 
    isp.mmio_base[ISP_IOMEM_BT1120] = BT1120_BASE_ADDR; 
    printf("struct isp_device addr = 0x%x,vi = 0x%x,mmio_base = 0x%x\n",&isp,&isp.isp_vi,isp.mmio_base[ISP_IOMEM_VI_WRAP]);
    if( lcd_type == BT1120_DISPLAY)  
    {
        bt1120_Init(&isp);
    }
    else if(lcd_type == AML550_LCD)
    {
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
        }
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
    }
    else if(lcd_type == ITI7807_LCD)
    {
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_ILI7807_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_ILI7807_INIT fail\n");
        }   
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
    }
    else if(lcd_type == HX8399)
    {
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_HX8399_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_HX8399_INIT fail\n");
        }   
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
    }  
    fpga_system_init(0);

    if(1 == isp_pipeline[MIPI0].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[MIPI0].isp_pipeline)
        {
            Isp_f2k_Init(&isp);         
        }
        else if( ISP_R_2K == isp_pipeline[MIPI0].isp_pipeline)
        {
            Isp_r2k_Init(&isp);          
        }
        else if(ISP_TOF == isp_pipeline[MIPI0].isp_pipeline)
        {
        }
    }
    if(1 == isp_pipeline[MIPI1].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[MIPI1].isp_pipeline)
        {
            Isp_f2k_Init(&isp);          
        }
        else if( ISP_R_2K == isp_pipeline[MIPI1].isp_pipeline)
        {
            Isp_r2k_Init(&isp);          
        }
        else if(ISP_TOF == isp_pipeline[MIPI1].isp_pipeline)
        {
        }        
    } 
    if(1 == isp_pipeline[DVP0].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[DVP0].isp_pipeline)
        {
            Isp_f2k_Init(&isp);          
        }
        else if( ISP_R_2K == isp_pipeline[DVP0].isp_pipeline)
        {
            Isp_r2k_Init(&isp);        
        }          
    }  
    video_in_Init(&isp);
    if((1 == isp_pipeline[MIPI0].pipeline_en)||(1 == isp_pipeline[MIPI1].pipeline_en))
    {
        mipi_csi_init(&isp);
    }
    if(1 == isp_pipeline[MIPI0].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[MIPI0].isp_pipeline)
        {
            if(IMX385_SENSOR == isp_pipeline[MIPI0].sensor_type)            
            {
                imx385_i2c_init(MIPI_CSI0_I2C);
                imx385_sensor_config();
            }
            else if(IMX219_SENSOR == isp_pipeline[MIPI0].sensor_type)
            {
                imx219_i2c_init(MIPI_CSI0_I2C);
            /*
                if(sensor_mode == IMX219_1920_1080)
                {
                    imx219_sensor_config();
                }
                else
                {
                    imx219_1080_1920_sensor_config();
                }  
           */
                imx219_sensor_config();
            }
            sleep(1);
            isp_f2k_core_table_init(&isp);
            sleep(1);            
        }
        else if( ISP_R_2K == isp_pipeline[MIPI0].isp_pipeline)
        {
            if(IMX385_SENSOR == isp_pipeline[MIPI0].sensor_type)
            {
                imx385_i2c_init(MIPI_CSI0_I2C);
                imx385_sensor_config();
            }
            else if(IMX219_SENSOR == isp_pipeline[MIPI0].sensor_type)
            {
                imx219_i2c_init(MIPI_CSI0_I2C);
            /*    
                if(sensor_mode == IMX219_1920_1080)
                {
                    imx219_sensor_config();
                }
                else
                {
                    imx219_1080_1920_sensor_config();
                } 
            */
                imx219_sensor_config();
            }
            sleep(1);
            isp_r2k_core_table_init(&isp);
            sleep(1);            
        }
        else if(ISP_TOF == isp_pipeline[MIPI0].isp_pipeline)
        {
        }
    }
    if(1 == isp_pipeline[MIPI1].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[MIPI1].isp_pipeline)
        {
            if(IMX385_SENSOR == isp_pipeline[MIPI1].sensor_type)
            {
                imx385_i2c_init(MIPI_CSI1_I2C);
                imx385_sensor_config();
            }
            else if(IMX219_SENSOR == isp_pipeline[MIPI1].sensor_type)
            {
                imx219_i2c_init(MIPI_CSI1_I2C);
            /*    
                if(sensor_mode == IMX219_1920_1080)
                {
                    imx219_sensor_config();
                }
                else
                {
                    imx219_1080_1920_sensor_config();
                }  
            */
                imx219_sensor_config();
            }
            sleep(1);
            isp_f2k_core_table_init(&isp);
            sleep(1);            
        }
        else if( ISP_R_2K == isp_pipeline[MIPI1].isp_pipeline)
        {
            if(IMX385_SENSOR == isp_pipeline[MIPI1].sensor_type)           
            {
                imx385_i2c_init(MIPI_CSI1_I2C);
                imx385_sensor_config();
            }
            else if(IMX219_SENSOR == isp_pipeline[MIPI1].sensor_type)
            {
                imx219_i2c_init(MIPI_CSI1_I2C);
            /*    
                if(sensor_mode == IMX219_1920_1080)
                {
                    imx219_sensor_config();
                }
                else
                {
                    imx219_1080_1920_sensor_config();
                } 
            */ 
                imx219_sensor_config();
            }
            sleep(1);
            isp_r2k_core_table_init(&isp);
            sleep(1);            
        }
        else if(ISP_TOF == isp_pipeline[MIPI1].isp_pipeline)
        {
        }        
    } 
    if(1 == isp_pipeline[DVP0].pipeline_en)
    {
        if( ISP_F_2K == isp_pipeline[DVP0].isp_pipeline)
        {
            if(JFX23S_SENSOR == isp_pipeline[DVP0].sensor_type)
            {
                jfx23s_i2c_init(DVP_I2C);
                jxf23s_sensor_config();
            }
            sleep(1);
            isp_f2k_core_table_init(&isp);
            sleep(1);            
        }
        else if( ISP_R_2K == isp_pipeline[DVP0].isp_pipeline)
        {
            if(JFX23S_SENSOR == isp_pipeline[DVP0].sensor_type)
            {
                jfx23s_i2c_init(DVP_I2C);
                jxf23s_sensor_config();
            }
            sleep(1);
            isp_r2k_core_table_init(&isp);
            sleep(1);            
        }          
    }    
    Vo_Out_Init(&isp);
    if( BT1120_DISPLAY == lcd_type)  
    {
        cv8788Init();
    }
    debug(debug_en,ISP_PIPE_MODE_R2K);

    return  fd_isp;
}


void video_close_all_plane(int fd)
{
    if (ioctl(fd, VIDEO_CLOSE_ALL_LAYER, 0) < 0)
    {
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
    }
    printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
}