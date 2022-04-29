/*
 * K510isp_com.h
 *
 * canaan ISP - Generic video node
 *
 * Copyright (C) 2019-2021 Nokia Corporation
 *
 * Contacts: zhudalei <zhudalei@canaan-creative.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ISP_COM_H
#define _ISP_COM_H

#ifndef FALSE
#define FALSE       0
#endif

#ifndef TRUE
#define TRUE        1
#endif

#ifndef DISABLE
#define DISABLE     0
#endif

#ifndef ENABLE
#define ENABLE      1
#endif

struct image_size_s
{
    unsigned int width;
    unsigned int height;
};

typedef enum _VI_PIPE_ID
{
	VI_MIPI_CSI00_PIPE_ID,
	VI_MIPI_CSI01_PIPE_ID,
	VI_MIPI_CSI02_PIPE_ID,
	VI_MIPI_CSI10_PIPE_ID,
	VI_MIPI_CSI11_PIPE_ID,
	VI_MIPI_CSI12_PIPE_ID,
	VI_DVP_0_PIPE_ID,
	VI_DVP_1_PIPE_ID,
	VI_MAX_PIPE_NUM,
}VI_PIPE_ID;

typedef enum _ISP_PIPE_WDR_MODE_E
{
	  ISP_PIPE_WDR_NONE,
	  ISP_PIPE_WDR_2_FRAME,
	  ISP_PIPE_WDR_3_FRAME,
	  ISP_PIPE_WDR_BUTT,
}ISP_PIPE_WDR_MODE_E;

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
struct isp_irq_info
{
    unsigned int    raw_en;
    unsigned int    rgb_en;
    unsigned int    yuv_en;
    unsigned int    ae_en;
    unsigned int    af_en;
	unsigned int    awb_en;
    unsigned int    nr3d_w_en;
    unsigned int    nr3d_r_en;
    unsigned int    ldc_core_en;
	unsigned int    ldc_w_en;
    unsigned int    ldc_r_en;
	unsigned int    wdr_w_en;
    unsigned int    wdr_r_en;     
    unsigned int    main_core_en;
    unsigned int    main_dma_en;
    unsigned int    ds0_en;
	unsigned int    ds1_en;
	unsigned int    ds2_en; 
};

struct vi_irq_info
{
    unsigned int    tpg_r_en;
    unsigned int    tpg_w_en;
};

#ifndef NULL
#define NULL    ((void *)0)
#endif

#endif /*_ISP_COM_H*/