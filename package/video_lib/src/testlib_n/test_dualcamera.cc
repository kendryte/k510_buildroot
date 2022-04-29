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
  File Name     : test_dualcamera.cc
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
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

#include "isp_com.h"
#include "isp_video.h"

/*******************************memory***************************************/
#define IMAGE_NAME1  "./Canaanlogo_1088x720_nv21_vflip.yuv"

#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)


#define MEMORY_TEST_BLOCK_NUM   20          /* 测试多少次申请释放 */
#define MEMORY_TEST_BLOCK_SIZE  4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */

#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"
#define MAP_MEMORY_DEV      "/dev/mem"

struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};


// share memory 
int *ds0_virtual_addr[MEMORY_TEST_BLOCK_NUM] = {0};
int fd_share_memory = -1;
int fd_mem_map = -1;
int isp_fd = -1;   
struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM] = {0};

//
struct video_isp_info
{
    ISP_PIPELINE_E isp_pipeline;
    //
    unsigned int total_width;
    unsigned int total_height;
    //
    unsigned int input_width;
    unsigned int input_height;
    //
    unsigned int output_width;
    unsigned int output_height;
    //
    unsigned int nr3d_en;
    unsigned int nr3d_addr;
    //
    unsigned int ldc_en;
    unsigned int ldc_addr;
    //
    unsigned int main_en;
    unsigned int main_addr;
    //
    unsigned int ds0_en; 
    unsigned int ds0put_width;
    unsigned int ds0put_height;
    unsigned int ds0_addr;  
    //
    unsigned int ds1_en; 
    unsigned int ds1put_width;
    unsigned int ds1put_height;
    unsigned int ds1_addr;
    unsigned int ds1_stride;  
    //
    unsigned int ds2_en; 
    unsigned int ds2put_width;
    unsigned int ds2put_height;
    unsigned int ds2_r_addr;
    unsigned int ds2_g_addr;
    unsigned int ds2_b_addr;
    DS2_RGB_TYPE ds2_rgb_type;
    unsigned int ds2_rgb_stride;
    //
    unsigned int vi_r_tpg_en;
    unsigned int vi_w_tpg_en;
    unsigned int vi_tpg_addr;    
};
//
struct video_vo_info
{
    //layer1
    unsigned int layer1_en;
    unsigned int layer1_width;
    unsigned int layer1_height;
    unsigned int layer1_yAddr0;
    unsigned int layer1_yAddr1; 
    //layer2
    unsigned int layer2_en;
    unsigned int layer2_width;
    unsigned int layer2_height;
    unsigned int layer2_yAddr0;
    unsigned int layer2_yAddr1;
    //osd0 
    unsigned int osd0_en;
    unsigned int osd0_width;
    unsigned int osd0_height;
    unsigned int osd0_rgb_type;    
    unsigned int osd0_yAddr0;
    unsigned int osd0_yAddr1; 
    //osd1
    unsigned int osd1_en; 
    unsigned int osd1_width;
    unsigned int osd1_height;
    unsigned int osd1_rgb_type;    
    unsigned int osd1_yAddr0;
    unsigned int osd1_yAddr1;
    unsigned int osd1_type;
    unsigned int osd1_rgb_rev; 
    //osd2 
    unsigned int osd2_en;
    unsigned int osd2_width;
    unsigned int osd2_height;
    unsigned int osd2_rgb_type;    
    unsigned int osd2_yAddr0;
    unsigned int osd2_yAddr1;
    unsigned int osd2_type;
    unsigned int osd2_rgb_rev;      
};
//
int set_vi_params(struct isp_pipeline_info *isp_pipeline,struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
	struct video_vi_info vi_info;
	vi_info.dphy_mode = 0;//TWO_LANES_MODE;
	vi_info.sony_mode = 0;//SONY_POL_MODE_DIS;

	struct vi_sensor_info *mipi0info = &vi_info.sensor_info[MIPI0];
	mipi0info->sensor_interface_en = isp_pipeline[MIPI0].pipeline_en;//1;//ENABLE;
	mipi0info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	mipi0info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	mipi0info->isp_pipeline = isp_info[F2K].isp_pipeline;//1;//ISP_F_2K;
    //
    struct vi_sensor_info *mipi1info = &vi_info.sensor_info[MIPI1];
	mipi1info->sensor_interface_en = isp_pipeline[MIPI1].pipeline_en;//1;//0;//DISABLE;
	mipi1info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	mipi1info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	mipi1info->isp_pipeline = isp_info[R2K].isp_pipeline;//1;//ISP_F_2K;
    //
	struct vi_sensor_info *dvp0info = &vi_info.sensor_info[DVP0]; 
	dvp0info->sensor_interface_en = isp_pipeline[DVP0].pipeline_en;//0;//1;//ENABLE;
	dvp0info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	dvp0info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	dvp0info->isp_pipeline = isp_info[R2K].isp_pipeline;//1;//ISP_F_2K;
    //
	struct vi_pipe_info *pipe00_info = &vi_info.pipe_info[CSI_00_PIPE];
	pipe00_info->win_mode_en = 1;//TRUE;	
	pipe00_info->input_ch_sel = 1;//MIPI_INPUT;
	pipe00_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    pipe00_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    pipe00_info->pixel_width = PIXEL_WIDTH_10BIT;//1;//PIXEL_WIDTH_12BIT;
	pipe00_info->data_out_timming_ctrl = 3;
	pipe00_info->sync_pulse_mode = 0;//0;
	pipe00_info->sen_mipi_clk_pol = 1;
	pipe00_info->sen_mipi_vsync_pol = 0;
	pipe00_info->sen_mipi_hsync_pol = 0;
	pipe00_info->sen_mipi_field_pol = 1;
	pipe00_info->isp_clk_pol = 1;
	pipe00_info->isp_vsync_pol = 1;
	pipe00_info->isp_hsync_pol = 1;
	pipe00_info->isp_field_pol = 1;
	//
    pipe00_info->tpg_w_en = isp_info[F2K].vi_w_tpg_en;//0;
    pipe00_info->tpg_r_en = isp_info[F2K].vi_r_tpg_en;//0;
    pipe00_info->total_width = isp_info[F2K].total_width;//isp_size->total_size.Width - 1;//2200;
	pipe00_info->total_height = isp_info[F2K].total_height;//isp_size->total_size.Height - 1;//1125;
    pipe00_info->in_width = isp_info[F2K].input_width;//isp_size->in_size.Width - 1;//1920;
	pipe00_info->in_height = isp_info[F2K].input_height;//isp_size->in_size.Height - 1;//1080;
    pipe00_info->w_st_width = 0x0;
	pipe00_info->w_st_height = 0x3fff;
    pipe00_info->r_st_width = 0x117;
	pipe00_info->r_st_height = 0x2c;
    pipe00_info->vi_pipe_w_addr_y0 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_y1 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv0 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv1 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y0 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y1 = isp_info[F2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_addr_stride = (pipe00_info->in_width*5/4+15)/16*16;
	pipe00_info->tof_mode_enable = 0;//DISABLE;
	pipe00_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe00_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
    //
	struct vi_pipe_info *pipe10_info = &vi_info.pipe_info[CSI_10_PIPE];
	pipe10_info->win_mode_en = 1;//TRUE;	
	pipe10_info->input_ch_sel = 1;//MIPI_INPUT;
	pipe10_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    pipe10_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    pipe10_info->pixel_width = PIXEL_WIDTH_10BIT;//1;//PIXEL_WIDTH_12BIT;
	pipe10_info->data_out_timming_ctrl = 3;
	pipe10_info->sync_pulse_mode = 0;//0;
	pipe10_info->sen_mipi_clk_pol = 1;
	pipe10_info->sen_mipi_vsync_pol = 0;
	pipe10_info->sen_mipi_hsync_pol = 0;
	pipe10_info->sen_mipi_field_pol = 1;
	pipe10_info->isp_clk_pol = 1;
	pipe10_info->isp_vsync_pol = 1;
	pipe10_info->isp_hsync_pol = 1;
	pipe10_info->isp_field_pol = 1;
	//
    pipe10_info->tpg_w_en = isp_info[R2K].vi_w_tpg_en;//0;
    pipe10_info->tpg_r_en = isp_info[R2K].vi_r_tpg_en;//0;
    pipe10_info->total_width = isp_info[R2K].total_width;//isp_size->total_size.Width - 1;//2200;
	pipe10_info->total_height = isp_info[R2K].total_height;//isp_size->total_size.Height - 1;//1125;
    pipe10_info->in_width = isp_info[R2K].input_width;//isp_size->in_size.Width - 1;//1920;
	pipe10_info->in_height = isp_info[R2K].input_height;//isp_size->in_size.Height - 1;//1080;
    pipe10_info->w_st_width = 0x0;
	pipe10_info->w_st_height = 0x3fff;
    pipe10_info->r_st_width = 0x117;
	pipe10_info->r_st_height = 0x2c;
    pipe10_info->vi_pipe_w_addr_y0 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_w_addr_y1 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_w_addr_uv0 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_w_addr_uv1 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_r_addr_y0 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_r_addr_y1 = isp_info[R2K].vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe10_info->vi_pipe_addr_stride = (pipe10_info->in_width*5/4+15)/16*16;
	pipe10_info->tof_mode_enable = 0;//DISABLE;
	pipe10_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe10_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
    //
    struct vi_pipe_info *dvp0_info = &vi_info.pipe_info[DVP_0_PIPE];
	dvp0_info->win_mode_en = 0;//FALSE;		
	dvp0_info->input_ch_sel = 0;//DVP_INPUT;
	dvp0_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    dvp0_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    dvp0_info->pixel_width = PIXEL_WIDTH_10BIT;//1;//PIXEL_WIDTH_10BIT;
	dvp0_info->data_out_timming_ctrl = 0;//CTRL_CYCLE_DELAY_1;
	dvp0_info->sync_pulse_mode = 1;//0;
	dvp0_info->sen_mipi_clk_pol = 1;//TRUE;
	dvp0_info->sen_mipi_vsync_pol = 1;//TRUE;
	dvp0_info->sen_mipi_hsync_pol = 1;//TRUE;
	dvp0_info->sen_mipi_field_pol = 1;//TRUE;
	dvp0_info->isp_clk_pol = 1;//TRUE;
	dvp0_info->isp_vsync_pol = 1;//TRUE;
	dvp0_info->isp_hsync_pol = 1;//TRUE;
	dvp0_info->isp_field_pol = 1;//TRUE;
    dvp0_info->tpg_w_en = isp_info[R2K].vi_w_tpg_en;//DISABLE;
    dvp0_info->tpg_r_en = isp_info[R2K].vi_r_tpg_en;//DISABLE;
    dvp0_info->total_width = isp_info[R2K].total_width;//2200;
	dvp0_info->total_height = isp_info[R2K].total_height;//1125;
    dvp0_info->in_width = isp_info[R2K].input_width;//1920;
	dvp0_info->in_height = isp_info[R2K].input_height;//1080;
    dvp0_info->w_st_width = 0x24f;//0x0;
	dvp0_info->w_st_height = 0x3fff;
    dvp0_info->r_st_width = 0x0;//0x117;
	dvp0_info->r_st_height = 0x0;//0x2c;
    dvp0_info->vi_pipe_w_addr_y0 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_y1 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_uv0 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_uv1 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_r_addr_y0 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_r_addr_y1 = isp_info[R2K].vi_tpg_addr;
    dvp0_info->vi_pipe_addr_stride = (dvp0_info->in_width*10/8+15)/16*16;
	dvp0_info->tof_mode_enable = 0;//DISABLE;
	dvp0_info->vi_pipe_tpg_tof_frm_num = 0x0;
	dvp0_info->vi_pipe_tpg_tof_frm_stride = 0x0;
    video_set_vi(&vi_info);
    return 0;
}
//
int set_isp_f2k_params(enum _SENSOR_TYPE sensor_type,struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    printf("set_isp_params\n");
    struct isp_common_info commoninfo;
    commoninfo.isp_out_sel = 0;//0:main_out 1;DS0_OUT;
    commoninfo.totalsize_width = isp_info->total_width;//2200;
    commoninfo.totalsize_height = isp_info->total_height;//1125;
    commoninfo.insize_width = isp_info->input_width;//1920;
    commoninfo.insize_height = isp_info->input_height;//1080;
    commoninfo.outsize_width = isp_info->output_width;//1920;
    commoninfo.outsize_height = isp_info->output_height;//1080;
    video_set_ispf2kcommon(sensor_type,&commoninfo);
    //
    struct isp_ds_info ds0_info;
    ds0_info.ds_en = isp_info->ds0_en;//1;
    ds0_info.ds_width = isp_info->ds0put_width;//1080;
    ds0_info.ds_height = isp_info->ds0put_height;//720;
    ds0_info.y_addr0 = isp_info->ds0_addr;//;
    ds0_info.y_addr1 = isp_info->ds0_addr;//;    
    video_set_ispf2kds0(sensor_type,&ds0_info);
    //
    struct isp_ds_info ds1_info;
    ds1_info.ds_en = isp_info->ds1_en;//1;
    ds1_info.ds_width = isp_info->ds1put_width;//1080;
    ds1_info.ds_height = isp_info->ds1put_height;// 720;
    ds1_info.y_addr0 = isp_info->ds1_addr;//;
    ds1_info.y_addr1 = isp_info->ds1_addr;//;
    ds1_info.stride  = isp_info->ds1_stride;  
    video_set_ispf2kds1(sensor_type,&ds1_info);
    //
    struct isp_ds2_info ds2_info;
    ds2_info.ds2_en = isp_info->ds2_en;//1;
    ds2_info.ds2_width = isp_info->ds2put_width;//320;
    ds2_info.ds2_height = isp_info->ds2put_height;//256;
    ds2_info.ds2_rgb_type = isp_info->ds2_rgb_type;//DS2_S_RGB;//DS2_ARGB;//;DS2_S_RGB
    ds2_info.stride = isp_info->ds2_rgb_stride;
    ds2_info.r_addr0 = isp_info->ds2_r_addr;//;
    ds2_info.r_addr1 = isp_info->ds2_r_addr;//;
    ds2_info.g_addr0 = isp_info->ds2_g_addr;//;
    ds2_info.g_addr1 = isp_info->ds2_g_addr;//; 
    ds2_info.b_addr0 = isp_info->ds2_b_addr;//;
    ds2_info.b_addr1 = isp_info->ds2_b_addr;//;  
    video_set_ispf2kds2(sensor_type,&ds2_info);

    return 0;
}
//
int set_isp_r2k_params(enum _SENSOR_TYPE sensor_type,struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    struct isp_common_info commoninfo;
    commoninfo.isp_out_sel = 0;//0:main_out 1;DS0_OUT;
    commoninfo.totalsize_width = isp_info->total_width;//2200;
    commoninfo.totalsize_height = isp_info->total_height;//1125;
    commoninfo.insize_width = isp_info->input_width;//1920;
    commoninfo.insize_height = isp_info->input_height;//1080;
    commoninfo.outsize_width = isp_info->output_width;//1920;
    commoninfo.outsize_height = isp_info->output_height;//1080;
    video_set_ispr2kcommon(sensor_type,&commoninfo);
    struct isp_ds_info ds0_info;
    ds0_info.ds_en = isp_info->ds0_en;//1;
    ds0_info.ds_width = isp_info->ds0put_width;//1080;
    ds0_info.ds_height = isp_info->ds0put_height;//720;
    ds0_info.y_addr0 = isp_info->ds0_addr;//;
    ds0_info.y_addr1 = isp_info->ds0_addr;//;    
    video_set_ispr2kds0(sensor_type,&ds0_info);
    struct isp_ds_info ds1_info;
    ds1_info.ds_en = isp_info->ds1_en;//1;
    ds1_info.ds_width = isp_info->ds1put_width;//1080;
    ds1_info.ds_height = isp_info->ds1put_height;// 720;
    ds1_info.y_addr0 = isp_info->ds1_addr;//;
    ds1_info.y_addr1 = isp_info->ds1_addr;//;
    ds1_info.stride  = isp_info->ds1_stride;  
    video_set_ispr2kds1(sensor_type,&ds1_info);
    struct isp_ds2_info ds2_info;
    ds2_info.ds2_en = isp_info->ds2_en;//1;
    ds2_info.ds2_width = isp_info->ds2put_width;//320;
    ds2_info.ds2_height = isp_info->ds2put_height;//256;
    ds2_info.ds2_rgb_type = isp_info->ds2_rgb_type;//DS2_S_RGB;//DS2_ARGB;//;DS2_S_RGB
    ds2_info.stride = isp_info->ds2_rgb_stride;
    ds2_info.r_addr0 = isp_info->ds2_r_addr;//;
    ds2_info.r_addr1 = isp_info->ds2_r_addr;//;
    ds2_info.g_addr0 = isp_info->ds2_g_addr;//;
    ds2_info.g_addr1 = isp_info->ds2_g_addr;//; 
    ds2_info.b_addr0 = isp_info->ds2_b_addr;//;
    ds2_info.b_addr1 = isp_info->ds2_b_addr;//;     
    video_set_ispr2kds2(sensor_type,&ds2_info);

    return 0;
}
//
int set_vo_hdmi_params(enum VO_OUT_IMGTYPE imgtype,struct video_vo_info *voInfo)
{
    ISP_CHECK_POINTER(voInfo);
    int v_offset = 0x2a;//14;
    int h_offset = 0xc6;//16;//46;
    struct vo_dispaly_info dispaly_info;
    dispaly_info.dispEnable = 1;
    dispaly_info.vo_out_imgtype = imgtype;//0;
    dispaly_info.xZoneCtl_start = 0xC6;
    dispaly_info.xZoneCtl_stop = 0x846;
    dispaly_info.yZoneCtl_start = 0x2A;
    dispaly_info.yZoneCtl_stop = 0x462;
    dispaly_info.SyncMode = 2;//VO_SYSTEM_MODE_1920x1080x30P;
    dispaly_info.vo_out_active_imgh = 1920;
    dispaly_info.vo_out_active_imgv = 1080;
    video_set_display(&dispaly_info);
    //
    struct vo_layer_info layer1_info;
    layer1_info.layerEn = voInfo->layer1_en;//1;
    layer1_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer1_info.endianuv = 2;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer1_info.uvswap = 1;
    //
    layer1_info.offset_hsize = 0;
    layer1_info.offset_vsize = 0;
    layer1_info.in_hsize = voInfo->layer1_width;
    layer1_info.in_vsize = voInfo->layer1_height;
    //		
    layer1_info.layer_x_start = h_offset;
    layer1_info.layer_y_start = v_offset;
    //
    layer1_info.layer_yAddr0 = voInfo->layer1_yAddr0;
    layer1_info.layer_yAddr1 = voInfo->layer1_yAddr1;
    video_set_volayer1(&layer1_info);
    //
    struct vo_layer_info layer2_info;
    layer2_info.layerEn = voInfo->layer2_en;//1;
    layer2_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer2_info.endianuv = 2;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer2_info.uvswap = 1;
    //
    layer2_info.offset_hsize = 0;
    layer2_info.offset_vsize = 0;
    layer2_info.in_hsize = voInfo->layer2_width;
    layer2_info.in_vsize = voInfo->layer2_height;
    //		
    layer2_info.layer_x_start = h_offset + 1200;
    layer2_info.layer_y_start = v_offset;
    //
    layer2_info.layer_yAddr0 = voInfo->layer2_yAddr0;
    layer2_info.layer_yAddr1 = voInfo->layer2_yAddr1;
    video_set_volayer2(&layer2_info);
    //
    struct vo_layer_osd_info osd0_info;
    osd0_info.osdEn = voInfo->osd0_en;//1;
    osd0_info.osdtype = 3;//OSD_RGB_32BIT;
    if( 0 == voInfo->osd0_rgb_type ) //DS2_S_RGB
    {
        osd0_info.osdtype = 1;//OSD_MONOCHROME_8BIT; 
    }
    osd0_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd0_info.rgbrev = 0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd0_info.width = voInfo->osd0_width;
    osd0_info.height = voInfo->osd0_height;
    //
    osd0_info.osd_x_start = h_offset;
    osd0_info.osd_y_start = v_offset + 800;
    //
    osd0_info.alp_addr0 = voInfo->osd0_yAddr0;
    osd0_info.alp_addr1 = voInfo->osd0_yAddr1;
    osd0_info.vlu_addr0 = voInfo->osd0_yAddr0;
    osd0_info.vlu_addr1 = voInfo->osd0_yAddr1;
    video_set_volayer4osd0(&osd0_info);
    //
    struct vo_layer_osd_info osd1_info;
    osd1_info.osdEn = voInfo->osd1_en;//1;
    osd1_info.osdtype = voInfo->osd1_type;//3;//OSD_RGB_32BIT;
    osd1_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd1_info.rgbrev = voInfo->osd1_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd1_info.width = voInfo->osd1_width;
    osd1_info.height = voInfo->osd1_height;
    //
    osd1_info.osd_x_start = h_offset+1280;
    osd1_info.osd_y_start = v_offset+500;
    //
    osd1_info.alp_addr0 = voInfo->osd1_yAddr0;
    osd1_info.alp_addr1 = voInfo->osd1_yAddr1;
    osd1_info.vlu_addr0 = voInfo->osd1_yAddr0;
    osd1_info.vlu_addr1 = voInfo->osd1_yAddr1;
    video_set_volayer5osd1(&osd1_info);
    //
    struct vo_layer_osd_info osd2_info;
    osd2_info.osdEn = voInfo->osd2_en;//1;
    osd2_info.osdtype = voInfo->osd2_type;//3;//OSD_RGB_32BIT;
    osd2_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd2_info.rgbrev = voInfo->osd2_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd2_info.width = voInfo->osd2_width;
    osd2_info.height = voInfo->osd2_height;
    //
    osd2_info.osd_x_start = h_offset+1080;
    osd2_info.osd_y_start = v_offset+600;;
    //
    osd2_info.alp_addr0 = voInfo->osd2_yAddr0;
    osd2_info.alp_addr1 = voInfo->osd2_yAddr1;
    osd2_info.vlu_addr0 = voInfo->osd2_yAddr0;
    osd2_info.vlu_addr1 = voInfo->osd2_yAddr1;
    video_set_volayer6osd2(&osd2_info);
    return 0;
}
//
int set_vo_dsi_params(enum VO_OUT_IMGTYPE imgtype,struct video_vo_info *voInfo)
{  
    ISP_CHECK_POINTER(voInfo);
    int v_offset = 44;//14;
    int h_offset = 0;//16;//46; 
    struct vo_dispaly_info dispaly_info;
    dispaly_info.dispEnable = 1;
    dispaly_info.vo_out_imgtype = imgtype;//0;

    dispaly_info.xZoneCtl_start = 0x2e;
    dispaly_info.xZoneCtl_stop = 0x465;
    dispaly_info.yZoneCtl_start = 0xe;
    dispaly_info.yZoneCtl_stop = 0x78d;
    dispaly_info.SyncMode = 8;//VO_SYSTEM_MODE_1080x1920x30P;
    dispaly_info.vo_out_active_imgh = 1080;
    dispaly_info.vo_out_active_imgv = 1920;
    video_set_display(&dispaly_info);
    //
    struct vo_layer_info layer1_info;
	layer1_info.layerEn = voInfo->layer1_en;//1;
	layer1_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer1_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer1_info.uvswap = 0;
    //
    layer1_info.offset_hsize = 0;
    layer1_info.offset_vsize = 0;
    layer1_info.in_hsize = voInfo->layer1_width;
    layer1_info.in_vsize = voInfo->layer1_height;
    //		
    layer1_info.layer_x_start = v_offset;
    layer1_info.layer_y_start = h_offset+10;
    //
    layer1_info.layer_yAddr0 = voInfo->layer1_yAddr0;
    layer1_info.layer_yAddr1 = voInfo->layer1_yAddr1;
    video_set_volayer1(&layer1_info);
    //
    struct vo_layer_info layer2_info;
	layer2_info.layerEn = voInfo->layer2_en;//1;
	layer2_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer2_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer2_info.uvswap = 0;
    //
    layer2_info.offset_hsize = 0;
    layer2_info.offset_vsize = 0;
    layer2_info.in_hsize = voInfo->layer2_width;
    layer2_info.in_vsize = voInfo->layer2_height;
    //		
    layer2_info.layer_x_start = v_offset;// + 400;
    layer2_info.layer_y_start = h_offset + 1200;//1200;
    //
    layer2_info.layer_yAddr0 = voInfo->layer2_yAddr0;
    layer2_info.layer_yAddr1 = voInfo->layer2_yAddr1;
    video_set_volayer2(&layer2_info);
    //
    struct vo_layer_osd_info osd0_info;
    osd0_info.osdEn = voInfo->osd0_en;//1;
    osd0_info.osdtype = 3;//OSD_RGB_32BIT;
    if( 0 == voInfo->osd0_rgb_type ) //DS2_S_RGB
    {
        osd0_info.osdtype = 1;//OSD_MONOCHROME_8BIT; 
    }
    osd0_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd0_info.rgbrev = 0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd0_info.width = voInfo->osd0_width;
    osd0_info.height = voInfo->osd0_height;
    //
    osd0_info.osd_x_start = v_offset;
    osd0_info.osd_y_start = h_offset + 730;
    //
    osd0_info.alp_addr0 = voInfo->osd0_yAddr0;
    osd0_info.alp_addr1 = voInfo->osd0_yAddr1;
    osd0_info.vlu_addr0 = voInfo->osd0_yAddr0;
    osd0_info.vlu_addr1 = voInfo->osd0_yAddr1;
    video_set_volayer4osd0(&osd0_info);
    //
    struct vo_layer_osd_info osd1_info;
    osd1_info.osdEn = voInfo->osd1_en;//1;
    osd1_info.osdtype = voInfo->osd1_type;//3;//OSD_RGB_32BIT;
    osd1_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd1_info.rgbrev = voInfo->osd1_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd1_info.width = voInfo->osd1_width;
    osd1_info.height = voInfo->osd1_height;
    //
    osd1_info.osd_x_start = v_offset;
    osd1_info.osd_y_start = h_offset+1460;
    //
    osd1_info.alp_addr0 = voInfo->osd1_yAddr0;
    osd1_info.alp_addr1 = voInfo->osd1_yAddr1;
    osd1_info.vlu_addr0 = voInfo->osd1_yAddr0;
    osd1_info.vlu_addr1 = voInfo->osd1_yAddr1;
    video_set_volayer5osd1(&osd1_info);
    //
    struct vo_layer_osd_info osd2_info;
    osd2_info.osdEn = voInfo->osd2_en;//1;
    osd2_info.osdtype = voInfo->osd2_type;//3;//OSD_RGB_32BIT;
    osd2_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd2_info.rgbrev = voInfo->osd2_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd2_info.width = voInfo->osd2_width;
    osd2_info.height = voInfo->osd2_height;
    //
    osd2_info.osd_x_start = v_offset+400;
    osd2_info.osd_y_start = h_offset+1200;
    //
    osd2_info.alp_addr0 = voInfo->osd2_yAddr0;
    osd2_info.alp_addr1 = voInfo->osd2_yAddr1;
    osd2_info.vlu_addr0 = voInfo->osd2_yAddr0;
    osd2_info.vlu_addr1 = voInfo->osd2_yAddr1;
    video_set_volayer6osd2(&osd2_info);       
    //
    return 0;
}


void fun_sig(int sig)
{
    int i = 0;

    if(sig == SIGINT)
    {

        ISP_REG_S reg_isp={0,0};
        reg_isp.id = ISP_2K_BASE_ADDR + 0x10 - VIDEO_SUBSYSTEM_BASE_ADDR;
        reg_isp.value = 0x00;
        //printf("isp_reg_writel:addr = 0x%x,data = 0x%x\n",addr,data);
        if (ioctl(isp_fd, ISP_CMD_WRITE_REG, &reg_isp) < 0)
        {
            printf("Call cmd ISP_CMD_WRITE_REG fail, reg addr = 0x%x\n", reg_isp.id);
        }
		
		reg_isp.id = ISP_R2K_BASE_ADDR + 0x10 - VIDEO_SUBSYSTEM_BASE_ADDR;
        reg_isp.value = 0x00;
        //printf("isp_reg_writel:addr = 0x%x,data = 0x%x\n",addr,data);
        if (ioctl(isp_fd, ISP_CMD_WRITE_REG, &reg_isp) < 0)
        {
            printf("Call cmd ISP_CMD_WRITE_REG fail, reg addr = 0x%x\n", reg_isp.id);
        }
        
        if (ioctl(isp_fd, ISP_CMD_ISP_RESET, 0) < 0)
        {
            printf("Call cmd ISP_CMD_ISP_RESET fail\n");
        } 
        
        //clse all plane
        video_close_all_plane(isp_fd);

        


        for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {

            if(ds0_virtual_addr[i])
                munmap(ds0_virtual_addr[i],allocAlignMem[i].size);
        }

        for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
            if(allocAlignMem[i].phyAddr != 0)
            {
                if(ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[i].phyAddr) < 0) {
                    printf("share memory  SHARE_MEMORY_FREE error!\r\n");
                }
            }
        }
        // 
        imx219_i2c_init(MIPI_CSI0_I2C);       
        imx219_close_sensor();
        //
        imx219_i2c_init(MIPI_CSI1_I2C); 
        imx219_close_sensor();
    }
    exit(0);
}
/**
 * @brief 
 * 
 */
static void cfg_noc_prior(void)
{
    system("devmem 0x970E00f4 32 0x00000000");
    system("devmem 0x970E00f8 32 0x00000000");
    system("devmem 0x970E00fc 32 0x0fffff00");
    system("devmem 0x970E0100 32 0x00000000");
    system("devmem 0x970E0104 32 0x00000000");
}
//
int main(int argc, char **argv)
{
    printf("test_videolib_n!!!!\n");
    
     
    //
    struct video_isp_info isp_info[2];
    struct video_vo_info voInfo;
    //
    unsigned int debug_en = 0;
    // wait crtl c signl
    signal(SIGINT, fun_sig);

    fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR);
    if(fd_share_memory < 0) {
        printf("open %s error!\r\n",SHARE_MEMORY_DEV);
        return 1 ;
    }
    //
    fd_mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (fd_mem_map < 0) {
        printf("CMEM: failed to open /dev/mem!");
        return 1;
    }
    /* 如果需要mmap映射,需要4K的整数倍 */
    unsigned int alloc_num = 0;
    /***************************************************************************
     * f2k memory alloc 
     ***************************************************************************/
    //f2k 3dnr
    isp_info[F2K].nr3d_en = 0;
    if(1 == isp_info[F2K].nr3d_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1536 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("d3nr share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("d3nr block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[F2K].nr3d_addr = allocAlignMem[alloc_num].phyAddr;
        printf("d3nr_addr =0x%x\n",isp_info[F2K].nr3d_addr);
    }
    //f2k ldc
    isp_info[F2K].ldc_en = 0;
    alloc_num++;
    if(1 == isp_info[F2K].ldc_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 2048 ;//MEMORY_TEST_BLOCK_SIZE; 0x400000*2
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ldc share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ldc block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        isp_info[F2K].ldc_addr = allocAlignMem[alloc_num].phyAddr;//isp_size.in_size.Width * isp_size.in_size.Height *20/8;
        printf("ldc_addr =0x%x\n",isp_info[F2K].ldc_addr);
    }
    //f2k main
    isp_info[F2K].main_en = 0;//0;
    alloc_num++;
    if(1 == isp_info[F2K].main_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[F2K].main_addr = allocAlignMem[alloc_num].phyAddr;//1920*1080*3/2;
        printf("main_out_addr =0x%x\n",isp_info[F2K].main_addr);
    }
    //f2k ds0
    isp_info[F2K].ds0_en = 1; 
    isp_info[F2K].ds0put_width = 1080;
    isp_info[F2K].ds0put_height = 720; 
    alloc_num++;  
    if(1 == isp_info[0].ds0_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds0 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds0 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[F2K].ds0_addr = allocAlignMem[alloc_num].phyAddr;//isp_addr.main_out_addr + isp_addr.main_stride * isp_size.out_size.Height *3/2;//1920*1080*3/2;
        printf("ds0_out_addr =0x%x\n",isp_info[F2K].ds0_addr);

        ds0_virtual_addr[0] = (int *)mmap(NULL,allocAlignMem[alloc_num].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[alloc_num].phyAddr);
        if(ds0_virtual_addr[0] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return  1;
        }
    }
    //f2k ds1 
    isp_info[F2K].ds1_en = 0; 
    isp_info[F2K].ds1put_width = 640;//1080;
    isp_info[F2K].ds1put_height = 480;//720; 
    isp_info[F2K].ds1_stride = (isp_info[F2K].ds1put_width+15)/16*16;
    alloc_num++;
    if( 1 == isp_info[F2K].ds1_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds1 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds1 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        
        isp_info[F2K].ds1_addr = allocAlignMem[alloc_num].phyAddr;//isp_addr.ds0_out_addr + isp_addr.ds0_stride * isp_size.ds0_size.Height *3/2;//1920*1080*3/2;
        printf("ds1_out_addr =0x%x\n",isp_info[F2K].ds1_addr);

    } 
    //f2k ds2
    isp_info[F2K].ds2_en = 1;
    isp_info[F2K].ds2put_width = 320;
    isp_info[F2K].ds2put_height = 256; 
    isp_info[F2K].ds2_rgb_type = DS2_S_RGB; //DS2_ARGB
    isp_info[F2K].ds2_rgb_stride = (isp_info[F2K].ds2put_width +15)/16*16;
    alloc_num++;
    if(1 == isp_info[F2K].ds2_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[F2K].ds2_r_addr = allocAlignMem[alloc_num].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;
        if( DS2_ARGB == isp_info[F2K].ds2_rgb_type)
        {
            isp_info[F2K].ds2_g_addr = isp_info[F2K].ds2_r_addr + isp_info[F2K].ds2_rgb_stride*2;
            isp_info[F2K].ds2_b_addr = isp_info[F2K].ds2_g_addr + isp_info[F2K].ds2_rgb_stride*3;
        }
        else if(DS2_S_RGB == isp_info[F2K].ds2_rgb_type)
        {
            isp_info[F2K].ds2_g_addr = isp_info[F2K].ds2_r_addr + isp_info[F2K].ds2_rgb_stride *isp_info[F2K].ds2put_height;
            isp_info[F2K].ds2_b_addr = isp_info[F2K].ds2_g_addr + isp_info[F2K].ds2_rgb_stride *isp_info[F2K].ds2put_height;            
        }
        printf("ds2_out_addr =0x%x\n",isp_info[F2K].ds2_r_addr);         
    }
    //vi tpg
    isp_info[F2K].vi_r_tpg_en  = 0;//1;//0;
    isp_info[F2K].vi_w_tpg_en  = 0;//1;//0;
    alloc_num++;
    if((1 == isp_info[R2K].vi_r_tpg_en)||(1 == isp_info[R2K].vi_w_tpg_en))
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("vi_tpg share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("vi_tpg block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        isp_info[F2K].vi_tpg_addr = allocAlignMem[alloc_num].phyAddr;   
    }
    /***************************************************************************
     * r2k memory alloc
     ***************************************************************************/
    //r2k ldc
    isp_info[R2K].ldc_en = 0;
    alloc_num++;
    if(1 == isp_info[R2K].ldc_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 2048 ;//MEMORY_TEST_BLOCK_SIZE; 0x400000*2
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ldc share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ldc block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        isp_info[R2K].ldc_addr = allocAlignMem[alloc_num].phyAddr;//isp_size.in_size.Width * isp_size.in_size.Height *20/8;
        printf("ldc_addr =0x%x\n",isp_info[R2K].ldc_addr);
    }
    //r2k main
    isp_info[R2K].main_en = 0;//0;
    alloc_num++;
    if(1 == isp_info[R2K].main_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[R2K].main_addr = allocAlignMem[alloc_num].phyAddr;//1920*1080*3/2;
        printf("main_out_addr =0x%x\n",isp_info[R2K].main_addr);
    }
    //ds0
    isp_info[R2K].ds0_en = 1; 
    isp_info[R2K].ds0put_width = 1080;//640;//1080;
    isp_info[R2K].ds0put_height = 720;//480;//720;
    alloc_num++;   
    if(1 == isp_info[R2K].ds0_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds0 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds0 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[R2K].ds0_addr = allocAlignMem[alloc_num].phyAddr;//isp_addr.main_out_addr + isp_addr.main_stride * isp_size.out_size.Height *3/2;//1920*1080*3/2;
        printf("ds0_out_addr =0x%x\n",isp_info[R2K].ds0_addr);
        ds0_virtual_addr[1] = (int *)mmap(NULL,allocAlignMem[alloc_num].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[alloc_num].phyAddr);
        if(ds0_virtual_addr[1] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return  1;
        }
    }
    //ds1 
    isp_info[R2K].ds1_en = 0; 
    isp_info[R2K].ds1put_width = 640;//1080;
    isp_info[R2K].ds1put_height = 480;//720; 
    isp_info[R2K].ds1_stride = (isp_info[R2K].ds1put_width+15)/16*16;
    alloc_num++;
    if( 1 == isp_info[R2K].ds1_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds1 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds1 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        
        isp_info[R2K].ds1_addr = allocAlignMem[alloc_num].phyAddr;//isp_addr.ds0_out_addr + isp_addr.ds0_stride * isp_size.ds0_size.Height *3/2;//1920*1080*3/2;
        printf("ds1_out_addr =0x%x\n",isp_info[R2K].ds1_addr);

    } 
    //ds2
    isp_info[R2K].ds2_en = 1;
    isp_info[R2K].ds2put_width = 320;
    isp_info[R2K].ds2put_height = 256; 
    isp_info[R2K].ds2_rgb_type = DS2_S_RGB; //DS2_ARGB
    isp_info[R2K].ds2_rgb_stride = (isp_info[R2K].ds2put_width +15)/16*16;
    alloc_num++;
    if(1 == isp_info[R2K].ds2_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        isp_info[R2K].ds2_r_addr = allocAlignMem[alloc_num].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;
        if( DS2_ARGB == isp_info[R2K].ds2_rgb_type)
        {
            isp_info[R2K].ds2_g_addr = isp_info[R2K].ds2_r_addr + isp_info[R2K].ds2_rgb_stride*2;
            isp_info[R2K].ds2_b_addr = isp_info[R2K].ds2_g_addr + isp_info[R2K].ds2_rgb_stride*3;
        }
        else if(DS2_S_RGB == isp_info[R2K].ds2_rgb_type)
        {
            isp_info[R2K].ds2_g_addr = isp_info[R2K].ds2_r_addr + isp_info[R2K].ds2_rgb_stride *isp_info[R2K].ds2put_height;
            isp_info[R2K].ds2_b_addr = isp_info[R2K].ds2_g_addr + isp_info[R2K].ds2_rgb_stride *isp_info[R2K].ds2put_height;            
        }
        printf("ds2_out_addr =0x%x\n",isp_info[R2K].ds2_r_addr);         
    }

    //vi tpg
    isp_info[R2K].vi_r_tpg_en  = 0;//1;//0;
    isp_info[R2K].vi_w_tpg_en  = 0;//1;//0;
    alloc_num++;
    if((1 == isp_info[R2K].vi_r_tpg_en)||(1 == isp_info[R2K].vi_w_tpg_en))
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("vi_tpg share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("vi_tpg block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }
        isp_info[R2K].vi_tpg_addr = allocAlignMem[alloc_num].phyAddr;   
    }
    /***************************************************************************
     * vo memory alloc
     ***************************************************************************/
   //vo osd1
    voInfo.osd1_en = 1;
    alloc_num++;
    if(1 == voInfo.osd1_en)
    {
        allocAlignMem[alloc_num].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[alloc_num].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[alloc_num].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[alloc_num]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return  1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[alloc_num].phyAddr,allocAlignMem[alloc_num].size,allocAlignMem[alloc_num].alignment);
        }

        voInfo.osd1_yAddr0 = allocAlignMem[alloc_num].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;

        printf("ds2_out_addr =0x%x\n",voInfo.osd1_yAddr0);

        //vo_osd_virtual_addr[0] = (int *)mmap(NULL,allocAlignMem[alloc_num].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[alloc_num].phyAddr);
        //if(vo_osd_virtual_addr[0] == MAP_FAILED) {
        //   printf("share memory  virtual_addr error!\r\n");
        //   return  1;
        //}
    }
    //
    FILE *logo_fd;
    logo_fd = fopen(IMAGE_NAME1, "rb");    //IMAGE_NAME   IMAGE_NAME1
    if(logo_fd == NULL)
    {
        printf("open %s failure, errno %d\n", IMAGE_NAME1, errno);
        return 1;
    }
    printf("open %s success \n",IMAGE_NAME1);

    int logo_ret = fread(ds0_virtual_addr[0],((isp_info[F2K].ds0put_width+15)/16*16)*isp_info[F2K].ds0put_height*3/2, 1, logo_fd); 
    if(logo_ret < 0)
    {
        printf("read logo_pic0 is failed logo_ret is %d \n", logo_ret);
        return 1;
    }
    //
    fseek(logo_fd, 0, SEEK_SET);
    logo_ret = fread(ds0_virtual_addr[1], ((isp_info[R2K].ds0put_width+15)/16*16)*isp_info[R2K].ds0put_height*3/2, 1, logo_fd); 
    if(logo_ret < 0)
    {
        printf("read  logo_pic1 is failed logo_ret is %d \n", logo_ret);
        return 1;
    }
    fclose(logo_fd);
    printf("read  canaan_logo_pic is success!\n");    
    //
    enum _LCD_TYPE lcd_type = HX8399;//ITI7807_LCD//AML550_LCD;//BT1120_DISPLAY;
    enum VO_OUT_IMGTYPE imgtype = VO_OUT_YUV_HDMI;
    struct isp_pipeline_info isp_pipeline[MAX_SENSOR_INTERFACE_NUM];
    //mipi0
    isp_pipeline[MIPI0].pipeline_en = 1;
    isp_pipeline[MIPI0].sensor_type = IMX219_SENSOR;//IMX219_SENSOR;//IMX385_SENSOR;
    isp_pipeline[MIPI0].isp_pipeline = ISP_F_2K;
    if(1 == isp_pipeline[MIPI0].pipeline_en)
    {
        isp_info[F2K].total_width = 3476;//3448;
        isp_info[F2K].total_height = 1166;
        isp_info[F2K].input_width = 1920;
        isp_info[F2K].input_height = 1080;
        isp_info[F2K].output_width = 1920;
        isp_info[F2K].output_height = 1080;
        isp_info[F2K].isp_pipeline = isp_pipeline[MIPI0].isp_pipeline;  
    }
    //mipi1
    isp_pipeline[MIPI1].pipeline_en = 1;//0;
    isp_pipeline[MIPI1].sensor_type = IMX219_SENSOR;//IMX219_SENSOR;//IMX385_SENSOR;
    isp_pipeline[MIPI1].isp_pipeline = ISP_R_2K;
    if(1 == isp_pipeline[MIPI1].pipeline_en)
    {
        isp_info[R2K].total_width = 3476;//3448;
        isp_info[R2K].total_height = 1166;
        isp_info[R2K].input_width = 1920;
        isp_info[R2K].input_height = 1080;
        isp_info[R2K].output_width = 1920;
        isp_info[R2K].output_height = 1080; 
        isp_info[R2K].isp_pipeline = isp_pipeline[MIPI1].isp_pipeline; 
    } 
    //dvp0
    isp_pipeline[DVP0].pipeline_en = 0;//1;
    isp_pipeline[DVP0].sensor_type = JFX23S_SENSOR;//JFX23S_SENSOR;
    isp_pipeline[DVP0].isp_pipeline = ISP_R_2K;
    if(1 == isp_pipeline[DVP0].pipeline_en)
    {
        isp_info[R2K].total_width = 2560;
        isp_info[R2K].total_height = 1125;
        isp_info[R2K].input_width = 1928;
        isp_info[R2K].input_height = 1088;
        isp_info[R2K].output_width = 1920;
        isp_info[R2K].output_height = 1080; 
        isp_info[R2K].isp_pipeline = isp_pipeline[DVP0].isp_pipeline; 
    } 
    //mipi csi
    if((1 == isp_pipeline[MIPI0].pipeline_en) || (1 == isp_pipeline[MIPI1].pipeline_en))
    {
        unsigned int csi0_pixel_width = PIXEL_WIDTH_12BIT;
        unsigned int csi1_pixel_width = PIXEL_WIDTH_12BIT;
        if( IMX219_SENSOR == isp_pipeline[MIPI0].sensor_type)
        {
            csi0_pixel_width = PIXEL_WIDTH_10BIT;
        }

        if( IMX219_SENSOR == isp_pipeline[MIPI1].sensor_type)
        {
            csi1_pixel_width = PIXEL_WIDTH_10BIT;
        }

        //video_set_mipicsi(MIPI_2x2LANE12_34,csi0_pixel_width,csi1_pixel_width);
        video_set_mipicsi(MIPI_2LANE12_RAW10,csi0_pixel_width,csi1_pixel_width);
    }
    //
    if(BT1120_DISPLAY == lcd_type)
    {
        imgtype = VO_OUT_YUV_HDMI;
        //bt1120
        struct hdmi_bt1120_info bt1120_info;
        bt1120_info.bt1120_en = 1;
        bt1120_info.bt_in_sel = SEL_VO;
        bt1120_info.img_hsize_total = 2200;
        bt1120_info.img_vsize_total = 1125;
        bt1120_info.img_hsize = 1920; 
        bt1120_info.img_vsize = 1080;  
        video_set_bt1120(&bt1120_info);
    }
    else
    {
        imgtype = VO_OUT_RGB_DSI;
    }
    //VI
    set_vi_params(&isp_pipeline[0],&isp_info[0]);

    //ISP
    if( 1 == isp_pipeline[MIPI0].pipeline_en)
    {
        set_isp_f2k_params(isp_pipeline[MIPI0].sensor_type,&isp_info[F2K]);
    }

    if( 1 == isp_pipeline[MIPI1].pipeline_en)
    {
        set_isp_r2k_params(isp_pipeline[MIPI1].sensor_type,&isp_info[R2K]);
    }

    if( 1 == isp_pipeline[DVP0].pipeline_en)
    {
        set_isp_r2k_params(isp_pipeline[DVP0].sensor_type,&isp_info[R2K]);
    }
    //
    voInfo.layer1_en = isp_info[F2K].ds0_en;
    voInfo.layer1_width = isp_info[F2K].ds0put_width;
    voInfo.layer1_height = isp_info[F2K].ds0put_height;
    voInfo.layer1_yAddr0= isp_info[F2K].ds0_addr;
    voInfo.layer1_yAddr1= isp_info[F2K].ds0_addr;
    // 
    voInfo.layer2_en = isp_info[R2K].ds0_en;
    voInfo.layer2_width = isp_info[R2K].ds0put_width;
    voInfo.layer2_height = isp_info[R2K].ds0put_height;
    voInfo.layer2_yAddr0= isp_info[R2K].ds0_addr;
    voInfo.layer2_yAddr1= isp_info[R2K].ds0_addr;
    //
    if(BT1120_DISPLAY == lcd_type)
    {
        set_vo_hdmi_params(imgtype,&voInfo);
    }
    else
    {
        set_vo_dsi_params(imgtype,&voInfo);
    } 
    //
    cfg_noc_prior();   
    //
    isp_fd = run_multi_video(&isp_pipeline[MIPI0],lcd_type,debug_en);
    // draw a test box
	frame_coordinate_info test;
	test.startx = 200;
	test.starty = 200;
	test.endx = 400;
	test.endy = 400;
    printf("----------------------------------------------- \n");
    while(1)
    {
       //video_draw_frame(1, 0, test);
       //printf("open draw_frame \n");
       //sleep(20);
        //draw_frame(0, 0, test);
        //printf("close draw_frame \n");
        //sleep(20);
    }
    //
    //debug(1,ISP_PIPE_MODE_F2K);
    //debug(1,ISP_PIPE_MODE_R2K);
}
