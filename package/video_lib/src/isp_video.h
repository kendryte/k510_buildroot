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
  File Name     : isp_video.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/
#ifndef _ISP_VIDEO_H_
#define _ISP_VIDEO_H_

#ifdef __cplusplus  
extern "C"{
#endif

#include <stdint.h>

#define calc_stride(width)   (((width) + 15)/16*16)

typedef struct FRAME_COORDINATE{
	unsigned int startx;
	unsigned int endx;
	unsigned int starty;
	unsigned int endy;
}frame_coordinate_info;

typedef struct isp_reg{
    unsigned int id;
    unsigned int value;
}ISP_REG_S;

typedef enum _ISP_TABLE_NAME{
    RGB_GAMMA,
    YUV_GAMMA,
    WDR_L3,
    WDR_M3,
    WDR_S3,
    WDR_L2,
    WDR_S2,
    TABLE_MAX,
}ISP_TABLE;

typedef enum _DS2_RGB_TYPE
{
    DS2_S_RGB = 0,
    DS2_ARGB = 1,
}DS2_RGB_TYPE;
typedef enum
{
    DS_OUT0 = 0,
    DS_OUT1,
    DS_OUT2,
} DS_OUT;

typedef enum
{
    DS0_IRQ_ID = 1,
    DS1_IRQ_ID,
    DS2_IRQ_ID,

} ISP_IRQ;

struct ds_data {
    uint32_t addr;
    ISP_IRQ isp_irq_id;
};

typedef enum _ISP_PIPE_MODE_E
{
	ISP_PIPE_MODE_4K = 0,
	ISP_PIPE_MODE_F2K,
	ISP_PIPE_MODE_R2K,
	ISP_PIPE_MODE_TOF,
	ISP_PIPE_MODE_BUTT
}ISP_PIPE_MODE_E;

typedef enum _SENSOR_TYPE
{
    IMX385_SENSOR = 0,
    JFX23S_SENSOR = 1,
    TOF_SENSOR    = 2,
	IMX219_SENSOR = 3,
	OV5647_SENSOR = 4,
}SENSOR_TYPE;


typedef enum _SENSOR_MODE
{
    IMX219_1920_1080 = 0,
    IMX219_1080_1920 = 1,
}SENSOR_MODE;

typedef struct _DS2_INFO
{
    unsigned int ds2_en;
    unsigned int ds2_width;
    unsigned int ds2_height;
    DS2_RGB_TYPE ds2_rgb_type;

	unsigned int r_addr;
	unsigned int g_addr;
	unsigned int b_addr;

}DS2_INFO;

typedef struct _DS1_INFO
{
    unsigned int ds1_en;
    unsigned int ds1_width;
    unsigned int ds1_height;
    unsigned int y_addr;
//    unsigned int uv_addr;
    unsigned int stride;
}DS1_INFO;

//OSD
typedef enum _OSD_Layer_Type_E
{
    OSD_RGB_24BIT         = 0,
    OSD_MONOCHROME_8BIT   = 1,
    OSD_RGB_16BIT         = 2,
    OSD_RGB_32BIT         = 3,
    OSD_RGB_4444          = 4,
    OSD_RGB_1555            = 5,
}OSD_Layer_Type_E;

typedef enum _OSD_Alpha_Type_E
{
    OSD_FIXED_VALUE         = 0,  //Alpha data is a fixed value
    OSD_L2_ALPHA_ADDR       = 1,  //Alpha data is at alpha data block in L2_ALPHA_ADDR.
    OSD_INTERVAL_R          = 2,  //Alpha data interval is aligned with R channel of OSD
    OSD_INTERVAL_G          = 3,  //Alpha data interval is aligned with G channel of OSD
    OSD_INTERVAL_B          = 4,  //Alpha data interval is aligned with B channel of OSD
    OSD_INTERVAL_A          = 5   //Alpha data interval is aligned with Alpha Channel of OSD for OSD type is 3, 4, and 5
 }OSD_Alpha_Type_E;

typedef enum _OSD_Dma_Ctl_E
{
    OSD_ORIGINAL_ORDER     = 0,
    OSD_TWO_BIT_ENDIAN    = 2,
    OSD_LITTLE_ENDIAN      = 3,
 }OSD_Dma_Ctl_E;

typedef enum _OSD_Dma_RGB_Rev
{
    OSD_RGB_REV_R     = 0,
    OSD_RGB_REV_B     = 1,
    OSD_RGB_REV_NUM   = 2,
 }OSD_Dma_RGB_Rev;

typedef struct _OSD_INFO
{
    OSD_Layer_Type_E   osd1_type;
    OSD_Dma_Ctl_E      osd1_dma_ctl;
    OSD_Dma_RGB_Rev    osd1_rgb_rev;
}OSD_INFO;

typedef struct _VO_OSD_INFO
{
    unsigned int osd_en;
    unsigned int osd_width;
    unsigned int osd_height;
    OSD_INFO     osd_ctl;
}VO_OSD_INFO;

typedef enum _LCD_TYPE
{
    AML550_LCD = 0,
    ITI7807_LCD = 1,
    BT1120_DISPLAY = 2,
	HX8399 = 3,
	NO_SUPPORT_LCD,
}LCD_TYPE;

struct memory_cache_sync_request {
    size_t size;
    uint64_t vaddr;
    uint64_t paddr;
};

enum NR3D_FBC_FORMAT
{
    NR3D_YUV422_ENABLE,
    NR3D_YUV420_ENABLE,
};

enum VO_OUT_IMGTYPE
{
    VO_OUT_YUV_HDMI,
    VO_OUT_RGB_DSI,
};

enum isp_mem_resources {
	ISP_IOMEM_CSI0_HOST,
	ISP_IOMEM_CSI1_HOST,
	ISP_IOMEM_MIPI_DPHY,
	ISP_IOMEM_MIPI_CORNER,
	ISP_IOMEM_VI_WRAP,
	ISP_IOMEM_VI_PIPE_CSI00,
	ISP_IOMEM_VI_PIPE_CSI01,
	ISP_IOMEM_VI_PIPE_CSI02,
	ISP_IOMEM_VI_PIPE_CSI10,
	ISP_IOMEM_VI_PIPE_CSI11,
	ISP_IOMEM_VI_PIPE_CSI12,
	ISP_IOMEM_VI_PIPE_DVP0,	
	ISP_IOMEM_VI_PIPE_DVP1,		
	ISP_IOMEM_F2K_WRAP,
	ISP_IOMEM_F2K_CORE,
	ISP_IOMEM_F2K_CORE_TABLE,
	ISP_IOMEM_F2K_FBC,
	ISP_IOMEM_F2K_FBD,
	ISP_IOMEM_F2K_DS,
    ISP_IOMEM_F2K_MAIN_REMAP,
	ISP_IOMEM_F2K_OUT0_REMAP,
    ISP_IOMEM_F2K_OUT1_REMAP,
	ISP_IOMEM_R2K_WRAP,
	ISP_IOMEM_R2K_CORE,
	ISP_IOMEM_R2K_CORE_TABLE,
	ISP_IOMEM_R2K_DS,
	ISP_IOMEM_R2K_MAIN_REMAP,
    ISP_IOMEM_R2K_OUT0_REMAP,
    ISP_IOMEM_R2K_OUT1_REMAP,
	ISP_IOMEM_TOF_WRAP,
	ISP_IOMEM_TOF_CORE,
	ISP_IOMEM_TOF_TABLE,
	ISP_IOMEM_FBC_WRAP,
    ISP_IOMEM_FBC_CORE,
	ISP_IOMEM_VO_CORE,
	ISP_IOMEM_VO_REMAP,
	ISP_IOMEM_VO_HSCALE,
	ISP_IOMEM_VO_VSCALE,
	ISP_IOMEM_VO_GAMMA,	
	ISP_IOMEM_BT1120,
	ISP_IOMEM_LAST
};

enum BT1120_IN_SEL
{
    SEL_VO = 0,
    SEL_ISP_F_4K = 1,
    SEL_ISP_F_2K = 2,
    SEL_ISP_R_2K = 3,
    SEL_ISP_TOF =4,
};

typedef enum _ISP_PIPELINE_E
{
	ISP_F_4K,
	ISP_F_2K,
	ISP_R_2K,
	ISP_TOF,
}ISP_PIPELINE_E;
typedef enum _SENSOR_INTERFACE_E
{
	MIPI0,
	MIPI1,
	DVP0,
	MAX_SENSOR_INTERFACE_NUM,
}SENSOR_INTERFACE_E;

enum _SENSOR_I2C
{
    MIPI_CSI0_I2C,
    MIPI_CSI1_I2C,
    DVP_I2C,
};

struct isp_pipeline_info
{
    enum _SENSOR_TYPE sensor_type;
    enum _ISP_PIPELINE_E isp_pipeline;
    unsigned int pipeline_en;
};
enum ISP_PIPELINE_CFG_NUM
{
    F2K,
    R2K,
};

#define CSI_00_PIPE       0
#define CSI_01_PIPE       1
#define CSI_02_PIPE       2
#define CSI_10_PIPE       3
#define CSI_11_PIPE       4
#define CSI_12_PIPE       5
#define DVP_0_PIPE        6
#define DVP_1_PIPE        7
#define  PIXEL_WIDTH_8BIT      0
#define  PIXEL_WIDTH_10BIT     1
#define  PIXEL_WIDTH_12BIT     2
#define  PIXEL_WIDTH_14BIT     3
#define  PIXEL_WIDTH_16BIT     4
#define  PIXEL_WIDTH_18BIT     5
#define  PIXEL_WIDTH_20BIT     6
#define  PIXEL_WIDTH_24BIT     7
#define ISP_BUF_FBCD_BLEN          0x7
#define ISP_BUF_FBCD_HEAD_BLEN     0x3
#define ISP_BUF_FBCD_STRIDE        0x2000
#define ISP_BUF_FBCD_HEAD_STRIDE   0x100

/*********************************************************************
 *mipi 
*********************************************************************/
enum csi_lane_mode
{
    MIPI_2LANE12_RAW12,
    MIPI_2LANE34_RAW12,
    MIPI_4LANE_RAW12,
    MIPI_2LANE12_RAW10,
    MIPI_2LANE34_RAW10,
    MIPI_4LANE_RAW10,
    MIPI_2x2LANE12_34_RAW12,
    MIPI_2x2LANE12_34_RAW10,
    MIPI_2x2LANE12_34,
    MIPI_1x4LANE,
};
//
int video_set_mipicsi(enum csi_lane_mode lane_mode,unsigned int csi0_pixel_width,unsigned int csi1_pixel_width);
/*********************************************************************
 *vi 
*********************************************************************/
//
struct vi_sensor_info
{
    unsigned int    sensor_interface_en;
	unsigned int    wdr_sensor_vendor;
	unsigned int    wdr_mode;
	//unsigned int    mipi_mode;
	unsigned int    isp_pipeline;
};

struct vi_pipe_info
{
    	unsigned int    win_mode_en;
    	unsigned int    input_ch_sel;
    	unsigned int    ch_mode_sel;
    	unsigned int    pixel_type;
    	//unsigned int    yuv_in_format;
    	//unsigned int    yuv_out_format;
    	//unsigned int    yuv422_order;
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
    	unsigned int    tpg_w_en;
    	unsigned int    tpg_r_en;
    	unsigned int    total_width;
        unsigned int    total_height;
    	unsigned int    in_width;
        unsigned int    in_height;
    	unsigned int    w_st_width;
        unsigned int    w_st_height;
     	unsigned int    r_st_width;
        unsigned int    r_st_height;
    	unsigned int    vi_pipe_w_addr_y0;
    	unsigned int    vi_pipe_w_addr_y1;
    	unsigned int    vi_pipe_w_addr_uv0;
    	unsigned int    vi_pipe_w_addr_uv1;
    	unsigned int    vi_pipe_r_addr_y0;
    	unsigned int    vi_pipe_r_addr_y1;
    	unsigned int    vi_pipe_addr_stride;
    	unsigned int    tof_mode_enable;
    	unsigned int    vi_pipe_tpg_tof_frm_num;
    	unsigned int    vi_pipe_tpg_tof_frm_stride;
};

struct video_vi_info
{
	unsigned int    dphy_mode;
	unsigned int    sony_mode;
    struct vi_sensor_info  sensor_info[MAX_SENSOR_INTERFACE_NUM];
    struct vi_pipe_info    pipe_info[8]; //only use 0,1,2,3,6 pipe 
};
//
int video_set_vi(struct video_vi_info *vi_info);
/*********************************************************************
 *isp 
*********************************************************************/
struct isp_common_info
{
    unsigned int	isp_out_sel;
    unsigned int    totalsize_width;
    unsigned int    totalsize_height;
    unsigned int    insize_width;
    unsigned int    insize_height;
    unsigned int    outsize_width;
    unsigned int    outsize_height;
};
//
struct isp_main_info
{
    unsigned int    main_en;
    unsigned int    width;
    unsigned int    height;    
    unsigned int    y_addr0;
    unsigned int    y_addr1;
    //unsigned int    stride;
};
//
struct isp_ds_info
{
    unsigned int    ds_en;
    unsigned int    ds_width;
    unsigned int    ds_height;
    unsigned int    y_addr0;
    unsigned int    y_addr1;
    unsigned int    stride;
    unsigned int    uv_swap;
};
//
struct isp_ds2_info
{
    unsigned int    ds2_en;
    unsigned int    ds2_width;
    unsigned int    ds2_height;
    DS2_RGB_TYPE    ds2_rgb_type;
    unsigned int    r_addr0;
    unsigned int    r_addr1;
    unsigned int    g_addr0;
    unsigned int    g_addr1;
    unsigned int    b_addr0;
    unsigned int    b_addr1;
    unsigned int    stride;
};
//
struct isp_rgbir_info
{
    unsigned int    rgbir_en;
};
//
//
struct isp_ldc_info
{
    unsigned int    ldc_en;
    unsigned int    y_addr;
    unsigned int    uv_addr;
    unsigned int    stride;
    unsigned int    ldc_req_freq;   
    unsigned int    ldc_stt_ln;
    unsigned int    ldc_h_center_pos;
    unsigned int    ldc_v_center_pos;
    unsigned int    ldc_rectify_cr; 
    unsigned int    ldc_rectify_cz; 
};
//
struct isp_wdr_info
{
    unsigned int    wdr_mode;
};
//
struct isp_nr3d_info
{
    unsigned int    nr3d_en;
	unsigned int    nr3d_fbcd_en;
    unsigned int    width;
    unsigned int    height;
    unsigned int    y_addr;
    //unsigned int    y_stride;
    //unsigned int    uv_addr;
    //unsigned int    uv_stride;
    unsigned int    y_fbcd_addr0;
    unsigned int    y_fbcd_addr1;
    //unsigned int    fbcd_stride;	
};
//
struct isp_int_info
{
    unsigned int    raw_en;
    unsigned int    rgb_en;
    unsigned int    yuv_en;
    unsigned int    ae_en;
    unsigned int    af_en;
	unsigned int    awb_en;
    unsigned int    nr3d_en;
	unsigned int    ldc_en;
	unsigned int    wdr_en;     
    unsigned int    main_en;
    unsigned int    ds0_en;
	unsigned int    ds1_en;
	unsigned int    ds2_en; 
};
//f2k
int video_set_ispf2kcommon(enum _SENSOR_TYPE sensor_type,struct isp_common_info *commoninfo);
int video_set_ispf2kmain0(enum _SENSOR_TYPE sensor_type,struct isp_main_info *main_info);
int video_set_ispf2kds0(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds0_info);
int video_set_ispf2kds1(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds1_info);
int video_set_ispf2kds2(enum _SENSOR_TYPE sensor_type,struct isp_ds2_info *ds2_info);
int video_set_ispf2krgbir(enum _SENSOR_TYPE sensor_type,struct isp_rgbir_info *rgbir_info);
int video_set_ispf2kldc(enum _SENSOR_TYPE sensor_type,struct isp_ldc_info *ldc_info);
int video_set_ispf2kwdr(enum _SENSOR_TYPE sensor_type,struct isp_wdr_info *wdr_info);
int video_set_ispf2knr3d(enum _SENSOR_TYPE sensor_type,struct isp_nr3d_info *nr3d_info);
int video_set_ispf2kint(struct isp_int_info *intinfo);
int video_set_ispf2k(unsigned int addr,unsigned int data);
unsigned int video_get_ispf2k(unsigned int addr);
//r2k
int video_set_ispr2kcommon(enum _SENSOR_TYPE sensor_type,struct isp_common_info *commoninfo);
int video_set_ispr2kmain0(enum _SENSOR_TYPE sensor_type,struct isp_main_info *main_info);
int video_set_ispr2kds0(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds0_info);
int video_set_ispr2kds1(enum _SENSOR_TYPE sensor_type,struct isp_ds_info *ds1_info);
int video_set_ispr2kds2(enum _SENSOR_TYPE sensor_type,struct isp_ds2_info *ds2_info);
int video_set_ispr2krgbir(enum _SENSOR_TYPE sensor_type,struct isp_rgbir_info *rgbir_info);
int video_set_ispr2kldc(enum _SENSOR_TYPE sensor_type,struct isp_ldc_info *ldc_info);
int video_set_ispr2kint(struct isp_int_info *intinfo);
int video_set_ispr2k(unsigned int addr,unsigned int data);
/*********************************************************************
 *vo 
*********************************************************************/
struct vo_dispaly_info{
    unsigned int    dispEnable;
    unsigned int    xZoneCtl_start;
    unsigned int    xZoneCtl_stop;
    unsigned int    yZoneCtl_start;
    unsigned int    yZoneCtl_stop;
    unsigned int    SyncMode;
    //unsigned int    hsize;
    //unsigned int    vsize;
    unsigned int    vo_out_imgtype;
    unsigned int    vo_out_active_imgh;
    unsigned int    vo_out_active_imgv;
};

struct vo_layer0_info{
	unsigned int 	layerEn;
	unsigned int 	yuvmode;
    unsigned int    endianuv;
    unsigned int    uvswap;
	//
    unsigned int 	offset_hsize;
    unsigned int 	offset_vsize;
    unsigned int 	in_hsize;
    unsigned int 	in_vsize;
    unsigned int 	out_hsize;
    unsigned int 	out_vsize;		
	//
    unsigned int 	layer_x_start;
    unsigned int 	layer_x_stop;
    unsigned int 	layer_y_start;
    unsigned int 	layer_y_stop;
	//
    unsigned int 	layer_yAddr0;
    unsigned int 	layer_yAddr1;
    //unsigned int 	layer_uvAddr0;
    //unsigned int 	layer_uvAddr1;
    //unsigned int 	layer_stride;
	//fbd
	unsigned int    fbd_en;
	unsigned int 	fbd_y_addr0;
	unsigned int 	fbd_y_addr1;
	unsigned int 	fbd_y_stride;

	unsigned int 	fbd_y_head_addr0;
	unsigned int 	fbd_y_head_addr1;
	unsigned int 	fbd_y_head_stride;

	unsigned int 	fbd_uv_addr0;
	unsigned int 	fbd_uv_addr1;
    unsigned int 	fbd_uv_stride;

	unsigned int 	fbd_uv_head_addr0;
	unsigned int 	fbd_uv_head_addr1;
    unsigned int 	fbd_uv_head_stride;
};
//
struct vo_layer_info
{
	unsigned int 	layerEn;
	unsigned int 	yuvmode;  //yuv420/yuv422
    unsigned int    endianuv;
    unsigned int    uvswap;
    //
    unsigned int 	offset_hsize;
    unsigned int 	offset_vsize;
    unsigned int 	in_hsize;
    unsigned int 	in_vsize;
    //		
    unsigned int 	layer_x_start;
    //unsigned int 	layer_x_stop;
    unsigned int 	layer_y_start;
    //unsigned int 	layer_y_stop;
    //
    unsigned int 	layer_yAddr0;
    unsigned int 	layer_yAddr1;
    //unsigned int 	layer_uvAddr0;
    //unsigned int 	layer_uvAddr1;
    //unsigned int 	layer_stride;
};
//
struct vo_layer_osd_info
{
    unsigned int 	osdEn;
    unsigned int 	osdtype;
    unsigned int 	alphatpye;
	unsigned int 	rgbrev;
    //
    unsigned int 	width;
    unsigned int 	height;
    //
    unsigned int 	osd_x_start;
    //unsigned int 	osd_x_stop;
    unsigned int 	osd_y_start;
    //unsigned int 	osd_y_stop;
    //
    unsigned int    alp_addr0;
    unsigned int    alp_addr1;
    //unsigned int    alpstride;
    unsigned int    vlu_addr0;
    unsigned int    vlu_addr1;
    //unsigned int    osdstride;
};
//
struct vo_disp_irq_info{
    unsigned int   vo_disp_irq0_en;
    unsigned int   vo_disp_irq1_en;
    unsigned int   vo_disp_irq2_en;
};
//
int video_set_display(struct vo_dispaly_info *dispaly_info);
int video_set_volayer0(struct vo_layer0_info *layer0_info);
int video_set_volayer1(struct vo_layer_info *layer1_info);
int video_set_volayer2(struct vo_layer_info *layer2_info);
int video_set_volayer3(struct vo_layer_info *layer3_info);
int video_set_volayer4osd0(struct vo_layer_osd_info *osd0_info);
int video_set_volayer5osd1(struct vo_layer_osd_info *osd1_info);
int video_set_volayer6osd2(struct vo_layer_osd_info *osd2_info);
int video_set_voint(struct vo_disp_irq_info *irq_info);
int video_draw_frame(unsigned int draw_en,unsigned int DrawAreaNum,frame_coordinate_info frame_coordinate);
/*********************************************************************
 *bt1120
*********************************************************************/
struct hdmi_bt1120_info{
    unsigned int bt1120_en;
    unsigned int bt_in_sel;
    unsigned int img_vsize_total;
    unsigned int img_hsize_total;
    unsigned int img_vsize;
    unsigned int img_hsize;
  };
//
int video_set_bt1120(struct hdmi_bt1120_info *bt1120_info);
/*********************************************************************
 *pipeline
*********************************************************************/
//int run_video(enum _SENSOR_TYPE sensor_type,enum _LCD_TYPE lcd_type,enum _ISP_PIPELINE_E isp_pipeline,unsigned int debug_en);
int run_video(enum _SENSOR_TYPE sensor_type,enum _SENSOR_MODE sensor_mode, enum _LCD_TYPE lcd_type,enum _ISP_PIPELINE_E isp_pipeline,unsigned int debug_en);
int run_multi_video(struct isp_pipeline_info *isp_pipeline,enum _LCD_TYPE lcd_type,unsigned int debug_en);
void video_set_ae_dgain_cfg(unsigned int expl);
void video_set_ae_again_cfg(unsigned int agc);
void imx219_close_sensor(void);
void imx219_i2c_init(enum _SENSOR_I2C i2c_num);
void video_close_all_plane(int fd);
#ifdef __cplusplus
} 
#endif
#endif /*_ISP_VIDEO_H_*/