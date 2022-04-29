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
 * isp_wrap_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */


#ifndef _ISP_WRAP_REG_H_
#define _ISP_WRAP_REG_H_
/*
* reset 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int sw_3dnr_rst : 1;     /* [0 ]      */
        unsigned int wdr_2_frame_rst : 1; /* [1 ]      */
        unsigned int wdr_3_frame_rst : 1; /* [2 ]      */
        unsigned int ldc_rst : 1;         /* [3 ]      */
        unsigned int main_out_rst : 1;    /* [4 ]      */
        unsigned int ds0_out_rst : 1;     /* [5 ]      */
        unsigned int ds1_out_rst : 1;     /* [6 ]      */
        unsigned int ds2_out_rst : 1;     /* [7 ]      */
        unsigned int wrap_com_rst : 1;    /* [8 ]      */
        unsigned int wrap_cfg_rst : 1;    /* [9 ]      */
        unsigned int core_com_rst : 1;    /* [10]      */
        unsigned int core_cfg_rst : 1;    /* [11]      */
        unsigned int axi_wr_ch_rst : 1;   /* [12]      */
        unsigned int axi_rd_ch_rst : 1;   /* [13]      */
        unsigned int reserved0 : 18;      /* [31..14]  */
    } bits;                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_SWRST_CTL;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int y_3dnr_wr_ch_rst : 1;      /* [0 ]      */
        unsigned int uv_3dnr_wr_ch_rst : 1;     /* [1 ]      */
        unsigned int ldc_y_wr_ch_rst : 1;       /* [2 ]      */
        unsigned int ldc_uv_wr_ch_rst : 1;      /* [3 ]      */
        unsigned int wdr_raw_wr_ch_rst : 1;     /* [4 ]      */
        unsigned int reserved0 : 1;             /* [5 ]      */
        unsigned int main_out_y_wr_ch_rst : 1;  /* [6 ]      */
        unsigned int main_out_uv_wr_ch_rst : 1; /* [7 ]      */
        unsigned int y_3dnr_rd_ch_rst : 1;      /* [8 ]      */
        unsigned int uv_3dnr_rd_ch_rst : 1;     /* [9 ]      */
        unsigned int ldc_y_rd_ch_rst : 1;       /* [10]      */
        unsigned int ldc_uv_rd_ch_rst : 1;      /* [11]      */
        unsigned int wdr_raw_rd_ch_rst : 1;     /* [12]      */
        unsigned int reserved1 : 3;             /* [15..13]  */
        unsigned int ds0_out_y_wr_ch_rst : 1;   /* [16]      */
        unsigned int ds0_out_uv_wr_ch_rst : 1;  /* [17]      */
        unsigned int ds1_out_y_wr_ch_rst : 1;   /* [18]      */
        unsigned int ds1_out_uv_wr_ch_rst : 1;  /* [19]      */
        unsigned int ds2_out_r_wr_ch_rst : 1;   /* [20]      */
        unsigned int ds2_out_g_wr_ch_rst : 1;   /* [21]      */
        unsigned int ds2_out_b_wr_ch_rst : 1;   /* [22]      */
        unsigned int reserved2 : 1;             /* [23]      */
        unsigned int ds0_osd0_rd_ch_rst : 1;    /* [24]      */
        unsigned int ds0_osd1_rd_ch_rst : 1;    /* [25]      */
        unsigned int ds1_osd0_rd_ch_rst : 1;    /* [26]      */
        unsigned int ds1_osd1_rd_ch_rst : 1;    /* [27]      */
        unsigned int ds2_osd0_rd_ch_rst : 1;    /* [28]      */
        unsigned int ds2_osd1_rd_ch_rst : 1;    /* [29]      */
        unsigned int ds1_osd2_rd_ch_rst : 1;    /* [30]      */
        unsigned int ds2_osd2_rd_ch_rst : 1;    /* [31]      */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_SWRST_CTL;
/*
* ctl mode 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int external_out_ch_sel : 2;   /* [1 ..0 ]  */
        unsigned int dvp_input_ch_type : 1;     /* [2 ]      */
        unsigned int wdr_long_ch_mode : 1;      /* [3 ]      */
        unsigned int wdr_long_l2_buf_en : 1;    /* [4 ]      */
        unsigned int wdr_short_s1_buf_en : 1;   /* [5 ]      */
        unsigned int wdr_dynamic_switch_en : 1; /* [6 ]      */
        unsigned int reserved0 : 1;             /* [7 ]      */
        unsigned int wdr_long_l2_buf_depth : 5; /* [12..8 ]  */
        unsigned int reserved1 : 3;             /* [15..13]  */
        unsigned int nr3d_fbcd_en : 1;         /* [16]      */
        unsigned int nr3d_mv_out_en : 1;        /* [17]      */
        unsigned int hist_3a_out_en : 1;        /* [18]      */
        unsigned int reserved2 : 1;             /* [19]  */
        unsigned int pix_remap_main_en : 1;     /* [20]      */
        unsigned int pix_remap_out0_en : 1;     /* [21]      */
        unsigned int pix_remap_out1_en : 1;     /* [22]      */
        unsigned int reserved3 : 9;             /* [31..23]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_CTL_MODE;
/*
*clock ctrl
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int clk_3dnr_en : 1;            /* [0 ]      */
        unsigned int wdr_2_frame_clk_en : 1;     /* [1 ]      */
        unsigned int wdr_3_frame_clk_en : 1;     /* [2 ]      */
        unsigned int ldc_clk_en : 1;             /* [3 ]      */
        unsigned int main_out_clk_en : 1;        /* [4 ]      */
        unsigned int ds0_out_clk_en : 1;         /* [5 ]      */
        unsigned int ds1_out_clk_en : 1;         /* [6 ]      */
        unsigned int ds2_out_clk_en : 1;         /* [7 ]      */
        unsigned int wrap_com_clk_en : 1;        /* [8 ]      */
        unsigned int wrap_cfg_clk_en : 1;        /* [9 ]      */
        unsigned int core_com_clk_en : 1;        /* [10]      */
        unsigned int core_cfg_clk_en : 1;        /* [11]      */
        unsigned int axi_wr_ch_en : 1;           /* [12]      */
        unsigned int axi_rd_ch_en : 1;           /* [13]      */
        unsigned int reserved0 : 2;              /* [15..14]  */
        unsigned int ds0_out_y_ch_clk_en : 1;    /* [16]      */
        unsigned int ds0_out_uv_ch_clk_en : 1;   /* [17]      */
        unsigned int ds1_out_y_ch_clk_en : 1;    /* [18]      */
        unsigned int ds1_out_uv_ch_clk_en : 1;   /* [19]      */
        unsigned int ds2_out_r_ch_clk_en : 1;    /* [20]      */
        unsigned int ds2_out_g_ch_clk_en : 1;    /* [21]      */
        unsigned int ds2_out_b_ch_clk_en : 1;    /* [22]      */
        unsigned int reserved1 : 1;              /* [23]      */
        unsigned int ds_out0_osd0_ch_clk_en : 1; /* [24]      */
        unsigned int ds_out0_osd1_ch_clk_en : 1; /* [25]      */
        unsigned int ds_out1_osd0_ch_clk_en : 1; /* [26]      */
        unsigned int ds_out1_osd1_ch_clk_en : 1; /* [27]      */
        unsigned int ds_out2_osd0_ch_clk_en : 1; /* [28]      */
        unsigned int ds_out2_osd1_ch_clk_en : 1; /* [29]      */
        unsigned int ds_out0_osd2_ch_clk_en : 1; /* [30]      */
        unsigned int ds_out1_osd2_ch_clk_en : 1; /* [31]      */
    } bits;                                      /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_PIPE_CLK_CTL;
/*
*DMA enable
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int pipe_3dnr_dma_en : 1;     /* [0 ]      */
        unsigned int wdr_long_dma_en : 1;      /* [1 ]      */
        unsigned int wdr_short_dma_en : 1;     /* [2 ]      */
        unsigned int ldc_dma_en : 1;           /* [3 ]      */
        unsigned int main_out_dma_en : 1;      /* [4 ]      */
        unsigned int ds_out0_dma_en : 1;       /* [5 ]      */
        unsigned int ds_out1_dma_en : 1;       /* [6 ]      */
        unsigned int ds_out2_dma_en : 1;       /* [7 ]      */
        unsigned int reserved1 : 8;            /* [15..8 ]  */
        unsigned int ds_out0_y_ch_dma_en : 1;  /* [16]      */
        unsigned int ds_out0_uv_ch_dma_en : 1; /* [17]      */
        unsigned int ds_out1_y_ch_dma_en : 1;  /* [18]      */
        unsigned int ds_out1_uv_ch_dma_en : 1; /* [19]      */
        unsigned int ds_out2_r_ch_dma_en : 1;  /* [20]      */
        unsigned int ds_out2_g_ch_dma_en : 1;  /* [21]      */
        unsigned int ds_out2_b_ch_dma_en : 1;  /* [22]      */
        unsigned int reserved2 : 1;            /* [23]      */
        unsigned int ds0_osd0_ch_dma_en : 1;   /* [24]      */
        unsigned int ds0_osd1_ch_dma_en : 1;   /* [25]      */
        unsigned int ds1_osd0_ch_dma_en : 1;   /* [26]      */
        unsigned int ds1_osd1_ch_dma_en : 1;   /* [27]      */
        unsigned int ds2_osd0_ch_dma_en : 1;   /* [28]      */
        unsigned int ds2_osd1_ch_dma_en : 1;   /* [29]      */
        unsigned int ds0_osd2_ch_dma_en : 1;   /* [30]      */
        unsigned int ds1_osd2_ch_dma_en : 1;   /* [31]      */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_EN_CTL;
/*
*3dnr&wdr pixel format
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int y_3dnr_img_format : 1;   /* [0 ]  */
        unsigned int y_3dnr_yuv_in_format : 1;   /* [1 ]  */
        unsigned int y_3dnr_img_out_format : 1;   /* [2 ]  */
        unsigned int y_3dnr_yuv422_pxl_order : 2;   /* [4..3 ]  */
        unsigned int y_3dnr_pixel_width : 3;   /* [7..5 ]  */
        unsigned int uv_3dnr_img_format : 1;   /* [8 ]  */
        unsigned int uv_3dnr_yuv_in_format : 1;   /* [9 ]  */
        unsigned int uv_3dnr_img_out_format : 1;   /* [10 ]  */
        unsigned int uv_3dnr_yuv422_pxl_order : 2;   /* [12..11 ]  */
        unsigned int uv_3dnr_pixel_width : 3;   /* [15..13 ]  */
        unsigned int wdr_long_img_format : 1;   /* [16 ]  */
        unsigned int wdr_long_yuv_in_format : 1;   /* [17 ]  */
        unsigned int wdr_long_img_out_format : 1;   /* [18 ]  */
        unsigned int wdr_long_yuv422_pxl_order : 2;   /* [20..19 ]  */
        unsigned int wdr_long_pixel_width : 3;   /* [23..21 ]  */
        unsigned int reserved0 : 8;             /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_3DNR_WDR_FORMAT_CTL;
/*
*DS pixel format
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_out_img_format        :1;   /* [0 ]  */
        unsigned int main_out_yuv_in_format     :1;   /* [1 ]  */
        unsigned int main_out_img_out_format    :1;   /* [2 ]  */
        unsigned int main_out_yuv422_pxl_order  :2;   /* [4..3 ]  */
        unsigned int main_out_pixel_width       :3;   /* [7..5 ]  */
        unsigned int ds0_out_img_format         :1;   /* [8 ]  */
        unsigned int ds0_out_yuv_in_format      :1;   /* [9 ]  */
        unsigned int ds0_out_img_out_format     :1;   /* [10 ]  */
        unsigned int ds0_out_yuv422_pxl_order   :2;   /* [12..11 ]  */
        unsigned int ds0_out_pixel_width        :3;   /* [15..13 ]  */
        unsigned int ds1_out_img_format         :1;   /* [16 ]  */
        unsigned int ds1_out_yuv_in_format      :1;   /* [17 ]  */
        unsigned int ds1_out_img_out_format     :1;   /* [18 ]  */
        unsigned int ds1_out_yuv422_pxl_order   :2;   /* [20..19 ]  */
        unsigned int ds1_out_pixel_width        :3;   /* [23..21 ]  */        
        unsigned int ds2_out_img_format         :1;   /* [24 ]  */
        unsigned int ds2_out_yuv_in_format      :1;   /* [25 ]  */
        unsigned int ds2_out_img_out_format     :1;   /* [26 ]  */
        unsigned int ds2_out_yuv422_pxl_order   :2;   /* [28..27 ]  */
        unsigned int ds2_out_pixel_width        :3;   /* [32..29 ]  */ 
    } bits;              
    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_PIXEL_FORMAT_CTL;
/*
*DS out size
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_out_v_size : 14; /* [13..0 ]  */
        unsigned int reserved0 : 2;        /* [15..14]  */
        unsigned int main_out_h_size : 14; /* [29..16]  */
        unsigned int reserved1 : 2;        /* [31..30]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_OUT_SIZE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_out_v_size : 14; /* [13..0 ]  */
        unsigned int reserved0 : 2;       /* [15..14]  */
        unsigned int ds0_out_h_size : 14; /* [29..16]  */
        unsigned int reserved1 : 2;       /* [31..30]  */
    } bits;                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_OUT_SIZE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_out_v_size : 14; /* [13..0 ]  */
        unsigned int reserved0 : 2;       /* [15..14]  */
        unsigned int ds1_out_h_size : 14; /* [29..16]  */
        unsigned int reserved1 : 2;       /* [31..30]  */
    } bits;                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_OUT_SIZE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_out_v_size : 14; /* [13..0 ]  */
        unsigned int reserved0 : 2;       /* [15..14]  */
        unsigned int ds2_out_h_size : 14; /* [29..16]  */
        unsigned int reserved1 : 2;       /* [31..30]  */
    } bits;                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_OUT_SIZE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int buf_3dnr_size_mask : 16; /* [15..0 ]  */
        unsigned int ldc_buf_size_mask : 16;  /* [31..16]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_BUF_SIZE_MASK0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_buf_size_mask : 16; /* [15..0 ]  */
        unsigned int ds0_buf_size_mask : 16;  /* [31..16]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_BUF_SIZE_MASK1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_buf_size_mask : 16; /* [15..0 ]  */
        unsigned int ds2_buf_size_mask : 16; /* [31..16]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_BUF_SIZE_MASK2;
/*
*DMA ctrl
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_wr_arb_mode : 1; /* [0 ]      */
        unsigned int isp_dma_rd_arb_mode : 1; /* [1 ]      */
        unsigned int reserved0 : 30;          /* [31..2 ]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_ARB_MODE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch0_wr_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch1_wr_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch2_wr_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch3_wr_weight : 8; /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_WEIGHT_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch4_wr_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch5_wr_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch6_wr_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch7_wr_weight : 8; /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_WEIGHT_1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch0_rd_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch1_rd_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch2_rd_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch3_rd_weight : 8; /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_WEIGHT_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch4_rd_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch5_rd_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch6_rd_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch7_rd_weight : 8; /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_WEIGHT_1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch0_wr_priority : 4; /* [3 ..0 ]  */
        unsigned int isp_dma_ch1_wr_priority : 4; /* [7 ..4 ]  */
        unsigned int isp_dma_ch2_wr_priority : 4; /* [11..8 ]  */
        unsigned int isp_dma_ch3_wr_priority : 4; /* [15..12]  */
        unsigned int isp_dma_ch4_wr_priority : 4; /* [19..16]  */
        unsigned int isp_dma_ch5_wr_priority : 4; /* [23..20]  */
        unsigned int isp_dma_ch6_wr_priority : 4; /* [27..24]  */
        unsigned int isp_dma_ch7_wr_priority : 4; /* [31..28]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_PRIORITY_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch0_rd_priority : 4; /* [3 ..0 ]  */
        unsigned int isp_dma_ch1_rd_priority : 4; /* [7 ..4 ]  */
        unsigned int isp_dma_ch2_rd_priority : 4; /* [11..8 ]  */
        unsigned int isp_dma_ch3_rd_priority : 4; /* [15..12]  */
        unsigned int isp_dma_ch4_rd_priority : 4; /* [19..16]  */
        unsigned int isp_dma_ch5_rd_priority : 4; /* [23..20]  */
        unsigned int isp_dma_ch6_rd_priority : 4; /* [27..24]  */
        unsigned int isp_dma_ch7_rd_priority : 4; /* [31..28]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_PRIORITY_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_wr_ch0_id : 4; /* [3 ..0 ]  */
        unsigned int isp_dma_wr_ch1_id : 4; /* [7 ..4 ]  */
        unsigned int isp_dma_wr_ch2_id : 4; /* [11..8 ]  */
        unsigned int isp_dma_wr_ch3_id : 4; /* [15..12]  */
        unsigned int isp_dma_wr_ch4_id : 4; /* [19..16]  */
        unsigned int isp_dma_wr_ch5_id : 4; /* [23..20]  */
        unsigned int isp_dma_wr_ch6_id : 4; /* [27..24]  */
        unsigned int isp_dma_wr_ch7_id : 4; /* [31..28]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_DMA_WR_CH_ID_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_rd_ch0_id : 4; /* [3 ..0 ]  */
        unsigned int isp_dma_rd_ch1_id : 4; /* [7 ..4 ]  */
        unsigned int isp_dma_rd_ch2_id : 4; /* [11..8 ]  */
        unsigned int isp_dma_rd_ch3_id : 4; /* [15..12]  */
        unsigned int isp_dma_rd_ch4_id : 4; /* [19..16]  */
        unsigned int isp_dma_rd_ch5_id : 4; /* [23..20]  */
        unsigned int isp_dma_rd_ch6_id : 4; /* [27..24]  */
        unsigned int isp_dma_rd_ch7_id : 4; /* [31..28]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_DMA_RD_CH_ID_0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch8_wr_weight : 8;  /* [7 ..0 ]  */
        unsigned int isp_dma_ch9_wr_weight : 8;  /* [15..8 ]  */
        unsigned int isp_dma_ch10_wr_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch11_wr_weight : 8; /* [31..24]  */
    } bits;                                      /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_WEIGHT_2;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch12_wr_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch13_wr_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch14_wr_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch15_wr_weight : 8; /* [31..24]  */
    } bits;                                      /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_WEIGHT_3;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch8_rd_weight : 8;  /* [7 ..0 ]  */
        unsigned int isp_dma_ch9_rd_weight : 8;  /* [15..8 ]  */
        unsigned int isp_dma_ch10_rd_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch11_rd_weight : 8; /* [31..24]  */
    } bits;                                      /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_WEIGHT_2;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch12_rd_weight : 8; /* [7 ..0 ]  */
        unsigned int isp_dma_ch13_rd_weight : 8; /* [15..8 ]  */
        unsigned int isp_dma_ch14_rd_weight : 8; /* [23..16]  */
        unsigned int isp_dma_ch15_rd_weight : 8; /* [31..24]  */
    } bits;                                      /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_WEIGHT_3;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch8_wr_priority : 4;  /* [3 ..0 ]  */
        unsigned int isp_dma_ch9_wr_priority : 4;  /* [7 ..4 ]  */
        unsigned int isp_dma_ch10_wr_priority : 4; /* [11..8 ]  */
        unsigned int isp_dma_ch11_wr_priority : 4; /* [15..12]  */
        unsigned int isp_dma_ch12_wr_priority : 4; /* [19..16]  */
        unsigned int isp_dma_ch13_wr_priority : 4; /* [23..20]  */
        unsigned int isp_dma_ch14_wr_priority : 4; /* [27..24]  */
        unsigned int isp_dma_ch15_wr_priority : 4; /* [31..28]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_PRIORITY_1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_ch8_rd_priority : 4;  /* [3 ..0 ]  */
        unsigned int isp_dma_ch9_rd_priority : 4;  /* [7 ..4 ]  */
        unsigned int isp_dma_ch10_rd_priority : 4; /* [11..8 ]  */
        unsigned int isp_dma_ch11_rd_priority : 4; /* [15..12]  */
        unsigned int isp_dma_ch12_rd_priority : 4; /* [19..16]  */
        unsigned int isp_dma_ch13_rd_priority : 4; /* [23..20]  */
        unsigned int isp_dma_ch14_rd_priority : 4; /* [27..24]  */
        unsigned int isp_dma_ch15_rd_priority : 4; /* [31..28]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_PRIORITY_1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_wr_ch8_id : 4;  /* [3 ..0 ]  */
        unsigned int isp_dma_wr_ch9_id : 4;  /* [7 ..4 ]  */
        unsigned int isp_dma_wr_ch10_id : 4; /* [11..8 ]  */
        unsigned int isp_dma_wr_ch11_id : 4; /* [15..12]  */
        unsigned int isp_dma_wr_ch12_id : 4; /* [19..16]  */
        unsigned int isp_dma_wr_ch13_id : 4; /* [23..20]  */
        unsigned int isp_dma_wr_ch14_id : 4; /* [27..24]  */
        unsigned int isp_dma_wr_ch15_id : 4; /* [31..28]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_DMA_WR_CH_ID_1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_dma_rd_ch8_id : 4;  /* [3 ..0 ]  */
        unsigned int isp_dma_rd_ch9_id : 4;  /* [7 ..4 ]  */
        unsigned int isp_dma_rd_ch10_id : 4; /* [11..8 ]  */
        unsigned int isp_dma_rd_ch11_id : 4; /* [15..12]  */
        unsigned int isp_dma_rd_ch12_id : 4; /* [19..16]  */
        unsigned int isp_dma_rd_ch13_id : 4; /* [23..20]  */
        unsigned int isp_dma_rd_ch14_id : 4; /* [27..24]  */
        unsigned int isp_dma_rd_ch15_id : 4; /* [31..28]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_DMA_RD_CH_ID_1;
/*
*WDR/NR3D/LDC buffer
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int wdr_long_buf_base : 32; /* [31..0 ]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_WDR_LONG_BUF_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int wdr_long_line_stride : 13; /* [12..0 ]  */
        unsigned int reserved0 : 3;             /* [15..13]  */
        unsigned int wdr_long_buf_size : 16;    /* [31..16]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_WDR_LONG_SIZE_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int y_3dnr_buf_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_3DNR_Y_BUF_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int uv_3dnr_buf_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_3DNR_UV_BUF_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int y_3dnr_line_stride : 13;  /* [12..0 ]  */
        unsigned int reserved0 : 3;            /* [15..13]  */
        unsigned int uv_3dnr_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;            /* [31..29]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_3DNR_STRIDE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ldc_y_buf_base : 32; /* [31..0 ]  */
    } bits;                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_LDC_Y_BUF_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ldc_uv_buf_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_LDC_UV_BUF_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ldc_y_line_stride : 13;  /* [12..0 ]  */
        unsigned int reserved0 : 3;           /* [15..13]  */
        unsigned int ldc_uv_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;           /* [31..29]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_LDC_STRIDE;
/*
*main out buffer
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_y_buf0_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_Y_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_y_buf1_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_Y_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_uv_buf0_base : 32; /* [31..0 ]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_UV_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_uv_buf1_base : 32; /* [31..0 ]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_UV_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int main_y_line_stride : 13;  /* [12..0 ]  */
        unsigned int reserved0 : 3;            /* [15..13]  */
        unsigned int main_uv_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;            /* [31..29]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_MAIN_STRIDE;
/*
* Downsize CH0 BUFF Control
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_y_buf0_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_Y_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_y_buf1_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_Y_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_uv_buf0_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_UV_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_uv_buf1_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_UV_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_y_line_stride : 13;  /* [12..0 ]  */
        unsigned int reserved0 : 3;           /* [15..13]  */
        unsigned int ds0_uv_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;           /* [31..29]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS0_STRIDE;
/*
* Downsize CH1 BUFF Control
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_y_buf0_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_Y_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_y_buf1_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_Y_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_uv_buf0_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_UV_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_uv_buf1_base : 32; /* [31..0 ]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_UV_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds1_y_line_stride : 13;  /* [12..0 ]  */
        unsigned int reserved0 : 3;           /* [15..13]  */
        unsigned int ds1_uv_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;           /* [31..29]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS1_STRIDE;
/*
* Downsize CH2 BUFF Control
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_r_buf0_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_R_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_r_buf1_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_R_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_g_buf0_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_G_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_g_buf1_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_G_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_b_buf0_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_B_BUF0_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_b_buf1_base : 32; /* [31..0 ]  */
    } bits;                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_B_BUF1_BASE;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_r_line_stride : 13; /* [12..0 ]  */
        unsigned int reserved0 : 3;          /* [15..13]  */
        unsigned int ds2_g_line_stride : 13; /* [28..16]  */
        unsigned int reserved1 : 3;          /* [31..29]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_STRIDE0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds2_b_line_stride : 13; /* [12..0 ]  */
        unsigned int reserved0 : 19;         /* [31..13]  */
    } bits;                                  /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DS2_STRIDE1;
/*
*DMA ch0-15 Control 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int ch0_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch0_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch0_wr_burstl : 1;        /* [12]      */
        unsigned int ch0_rd_burstl : 1;        /* [13]      */
        unsigned int ch0_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch0_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch0_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch0_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch0_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
}U_ISP_WRAP_DMA_CH0_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch1_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch1_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch1_wr_burstl : 1;        /* [12]      */
        unsigned int ch1_rd_burstl : 1;        /* [13]      */
        unsigned int ch1_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch1_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch1_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch1_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch1_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH1_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch2_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch2_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch2_wr_burstl : 1;        /* [12]      */
        unsigned int ch2_rd_burstl : 1;        /* [13]      */
        unsigned int ch2_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch2_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch2_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch2_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch2_rd_err_dec_en : 1;    /* [29]      */
        //unsigned int reserved1 : 2;            /* [31..30]  */
        unsigned int ch2_wr_outst_en : 1;            /* [30]  */
        unsigned int ch2_rd_outst_en : 1;            /* [31]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH2_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch3_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch3_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch3_wr_burstl : 1;        /* [12]      */
        unsigned int ch3_rd_burstl : 1;        /* [13]      */
        unsigned int ch3_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch3_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch3_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch3_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch3_rd_err_dec_en : 1;    /* [29]      */
        //unsigned int reserved1 : 2;            /* [31..30]  */
        unsigned int ch3_wr_outst_en : 1;            /* [30]  */
        unsigned int ch3_rd_outst_en : 1;            /* [31]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH3_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch4_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch4_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch4_wr_burstl : 1;        /* [12]      */
        unsigned int ch4_rd_burstl : 1;        /* [13]      */
        unsigned int ch4_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch4_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch4_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch4_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch4_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH4_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch5_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch5_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch5_wr_burstl : 1;        /* [12]      */
        unsigned int ch5_rd_burstl : 1;        /* [13]      */
        unsigned int ch5_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch5_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch5_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch5_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch5_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH5_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch6_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch6_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch6_wr_burstl : 1;        /* [12]      */
        unsigned int ch6_rd_burstl : 1;        /* [13]      */
        unsigned int ch6_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch6_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch6_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch6_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch6_rd_err_dec_en : 1;    /* [29]      */
        //unsigned int reserved1 : 2;            /* [31..30]  */
        unsigned int ch6_wr_outst_en : 1;            /* [30]  */
        unsigned int ch6_rd_outst_en : 1;            /* [31]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH6_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch7_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch7_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch7_wr_burstl : 1;        /* [12]      */
        unsigned int ch7_rd_burstl : 1;        /* [13]      */
        unsigned int ch7_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch7_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch7_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch7_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch7_rd_err_dec_en : 1;    /* [29]      */
        //unsigned int reserved1 : 2;            /* [31..30]  */
        unsigned int ch7_wr_outst_en : 1;            /* [30]  */
        unsigned int ch7_rd_outst_en : 1;            /* [31]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH7_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch8_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch8_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch8_wr_burstl : 1;        /* [12]      */
        unsigned int ch8_rd_burstl : 1;        /* [13]      */
        unsigned int ch8_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch8_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch8_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch8_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch8_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH8_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch9_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch9_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;            /* [11..8 ]  */
        unsigned int ch9_wr_burstl : 1;        /* [12]      */
        unsigned int ch9_rd_burstl : 1;        /* [13]      */
        unsigned int ch9_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch9_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch9_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch9_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch9_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;            /* [31..30]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH9_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch10_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch10_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch10_wr_burstl : 1;        /* [12]      */
        unsigned int ch10_rd_burstl : 1;        /* [13]      */
        unsigned int ch10_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch10_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch10_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch10_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch10_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH10_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch11_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch11_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch11_wr_burstl : 1;        /* [12]      */
        unsigned int ch11_rd_burstl : 1;        /* [13]      */
        unsigned int ch11_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch11_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch11_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch11_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch11_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH11_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch12_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch12_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch12_wr_burstl : 1;        /* [12]      */
        unsigned int ch12_rd_burstl : 1;        /* [13]      */
        unsigned int ch12_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch12_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch12_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch12_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch12_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH12_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch13_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch13_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch13_wr_burstl : 1;        /* [12]      */
        unsigned int ch13_rd_burstl : 1;        /* [13]      */
        unsigned int ch13_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch13_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch13_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch13_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch13_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH13_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch14_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch14_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch14_wr_burstl : 1;        /* [12]      */
        unsigned int ch14_rd_burstl : 1;        /* [13]      */
        unsigned int ch14_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch14_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch14_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch14_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch14_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH14_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch15_wr_outst : 4;         /* [3 ..0 ]  */
        unsigned int ch15_rd_outst : 4;         /* [7 ..4 ]  */
        unsigned int reserved0 : 4;             /* [11..8 ]  */
        unsigned int ch15_wr_burstl : 1;        /* [12]      */
        unsigned int ch15_rd_burstl : 1;        /* [13]      */
        unsigned int ch15_y_uv_noncon_en : 1;   /* [14]      */
        unsigned int ch15_y_uv_swap_en : 1;     /* [15]      */
        unsigned int ch15_wr_int_line_num : 12; /* [27..16]  */
        unsigned int ch15_wr_err_dec_en : 1;    /* [28]      */
        unsigned int ch15_rd_err_dec_en : 1;    /* [29]      */
        unsigned int reserved1 : 2;             /* [31..30]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH15_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch0_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch0_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch0_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch0_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH0_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch1_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch1_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch1_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch1_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH1_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch2_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch2_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch2_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch2_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH2_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch3_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch3_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch3_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch3_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH3_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch4_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch4_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch4_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch4_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH4_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch5_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch5_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch5_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch5_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH5_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch6_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch6_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch6_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch6_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH6_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch7_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch7_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch7_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch7_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH7_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch8_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch8_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch8_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch8_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH8_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch9_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch9_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch9_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch9_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH9_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch10_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch10_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch10_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch10_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH10_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch11_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch11_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch11_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch11_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH11_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch12_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch12_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch12_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch12_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH12_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch13_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch13_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch13_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch13_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH13_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch14_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch14_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch14_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch14_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH14_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch15_wr_err_dec_unit : 8; /* [7 ..0 ]  */
        unsigned int ch15_rd_err_dec_unit : 8; /* [15..8 ]  */
        unsigned int ch15_wr_err_gen_thr : 8;  /* [23..16]  */
        unsigned int ch15_rd_err_gen_thr : 8;  /* [31..24]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH15_ERR_DEC_CFG;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch0_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch0_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch0_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch0_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch0_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch0_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch0_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH0_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch1_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch1_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch1_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch1_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch1_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch1_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch1_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH1_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch2_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch2_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch2_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch2_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch2_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch2_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch2_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH2_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch3_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch3_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch3_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch3_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch3_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch3_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch3_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH3_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch4_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch4_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch4_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch4_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch4_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch4_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch4_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH4_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch5_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch5_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch5_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch5_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch5_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch5_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch5_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH5_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch6_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch6_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch6_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch6_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch6_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch6_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch6_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH6_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch7_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch7_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch7_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch7_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch7_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch7_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch7_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH7_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch8_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch8_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch8_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch8_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch8_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch8_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch8_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH8_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch9_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;               /* [7 ..4 ]  */
        unsigned int ch9_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;               /* [15..12]  */
        unsigned int ch9_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;               /* [23..20]  */
        unsigned int ch9_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch9_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;               /* [27..26]  */
        unsigned int ch9_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch9_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;               /* [31..30]  */
    } bits;                                       /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH9_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch10_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch10_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch10_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch10_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch10_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch10_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch10_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH10_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch11_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch11_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch11_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch11_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch11_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch11_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch11_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH11_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch12_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch12_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch12_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch12_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch12_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch12_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch12_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH12_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch13_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch13_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch13_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch13_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch13_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch13_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch13_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH13_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch14_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch14_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch14_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch14_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch14_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch14_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch14_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH14_ERR_STATUS;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ch15_err_y_wr_status : 4;     /* [3 ..0 ]  */
        unsigned int reserved0 : 4;                /* [7 ..4 ]  */
        unsigned int ch15_err_uv_wr_status : 4;    /* [11..8 ]  */
        unsigned int reserved1 : 4;                /* [15..12]  */
        unsigned int ch15_err_raw_read_status : 4; /* [19..16]  */
        unsigned int reserved2 : 4;                /* [23..20]  */
        unsigned int ch15_err_wr_rst_req : 1;      /* [24]      */
        unsigned int ch15_err_rd_rst_req : 1;      /* [25]      */
        unsigned int reserved3 : 2;                /* [27..26]  */
        unsigned int ch15_err_wr_ch_state : 1;     /* [28]      */
        unsigned int ch15_err_rd_ch_state : 1;     /* [29]      */
        unsigned int reserved4 : 2;                /* [31..30]  */
    } bits;                                        /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_CH15_ERR_STATUS;
/*
* Ctrl Config 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int wrap_config_done_en : 1; /* [0 ]      */
        unsigned int reserved0 : 15;          /* [15..1 ]  */
        unsigned int sen_reg_pro_en : 1;      /* [16]      */
        unsigned int int_polarity : 1;        /* [17]      */
        unsigned int reserved1 : 14;          /* [31..18]  */
    } bits;                                   /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_CONFIG_DONE;
/*
* isp_core Intr
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int int_raw_in : 1;        /* [0 ]      */
        unsigned int int_3a : 1;            /* [1 ]      */
        unsigned int raw_int : 1;           /* [2 ]      */
        unsigned int rgb_int : 1;           /* [3 ]      */
        unsigned int yuv_int : 1;           /* [4 ]      */
        unsigned int ldc_int : 1;           /* [5 ]      */
        unsigned int main_out_int : 1;      /* [6 ]      */
        unsigned int isp_awb_int : 1;       /* [7 ]      */
        unsigned int isp_ae_int : 1;        /* [8 ]      */
        unsigned int isp_af_int : 1;        /* [9 ]      */
        unsigned int reserved0 :  6;        /* [15..10 ]  */
        unsigned int int_raw_in_mask : 1;    /* [17]      */
        unsigned int int_3a_mask : 1;       /* [17]      */
        unsigned int raw_int_mask : 1;      /* [18]      */
        unsigned int rgb_int_mask : 1;      /* [19]      */
        unsigned int yuv_int_mask : 1;      /* [20]      */
        unsigned int ldc_int_mask : 1;      /* [21]      */
        unsigned int main_out_int_mask : 1; /* [22]      */
        unsigned int isp_awb_int_mask : 1;       /* [23 ]      */
        unsigned int isp_ae_int_mask : 1;        /* [24 ]      */
        unsigned int isp_af_int_mask : 1;        /* [25 ]      */        
        unsigned int reserved1 : 6;        /* [31..26]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_CORE_INT_CTL;
/*
* dma_ch0-7W Intr 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int wr_3dnr_y_frm_end_int : 1;            /* [0 ]      */
        unsigned int wr_3dnr_y_line_base_int : 1;          /* [1 ]      */
        unsigned int wr_3dnr_y_err_frm_end_int : 1;        /* [2 ]      */
        unsigned int wr_3dnr_y_err_immediate_int : 1;      /* [3 ]      */
        unsigned int wr_3dnr_uv_frm_end_int : 1;           /* [4 ]      */
        unsigned int wr_3dnr_uv_line_base_int : 1;         /* [5 ]      */
        unsigned int wr_3dnr_uv_err_frm_end_int : 1;       /* [6 ]      */
        unsigned int wr_3dnr_uv_err_immediate_int : 1;     /* [7 ]      */
        unsigned int ldc_wr_y_frm_end_int : 1;             /* [8 ]      */
        unsigned int ldc_wr_y_line_base_int : 1;           /* [9 ]      */
        unsigned int ldc_wr_y_err_frm_end_int : 1;         /* [10]      */
        unsigned int ldc_wr_y_err_immediate_int : 1;       /* [11]      */
        unsigned int ldc_wr_uv_frm_end_int : 1;            /* [12]      */
        unsigned int ldc_wr_uv_line_base_int : 1;          /* [13]      */
        unsigned int ldc_wr_uv_err_frm_end_int : 1;        /* [14]      */
        unsigned int ldc_wr_uv_err_immediate_int : 1;      /* [15]      */
        unsigned int wdr_wr_raw_frm_end_int : 1;           /* [16]      */
        unsigned int wdr_wr_raw_line_base_int : 1;         /* [17]      */
        unsigned int wdr_wr_raw_err_frm_end_int : 1;       /* [18]      */
        unsigned int wdr_wr_raw_err_immediate_int : 1;     /* [19]      */
        unsigned int reserved0 : 4;                        /* [23..20]  */
        unsigned int main_out_wr_y_frm_end_int : 1;        /* [24]      */
        unsigned int main_out_wr_y_line_base_int : 1;      /* [25]      */
        unsigned int main_out_wr_y_err_frm_end_int : 1;    /* [26]      */
        unsigned int main_out_wr_y_err_immediate_int : 1;  /* [27]      */
        unsigned int main_out_wr_uv_frm_end_int : 1;       /* [28]      */
        unsigned int main_out_wr_uv_line_base_int : 1;     /* [29]      */
        unsigned int main_out_wr_uv_err_frm_end_int : 1;   /* [30]      */
        unsigned int main_out_wr_uv_err_immediate_int : 1; /* [31]      */
    } bits;                                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_INT_STATUS0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int wr_3dnr_y_frm_end_int_mask : 1;            /* [0 ]      */
        unsigned int wr_3dnr_y_line_base_int_mask : 1;          /* [1 ]      */
        unsigned int wr_3dnr_y_err_frm_end_int_mask : 1;        /* [2 ]      */
        unsigned int wr_3dnr_y_err_immediate_int_mask : 1;      /* [3 ]      */
        unsigned int wr_3dnr_uv_frm_end_int_mask : 1;           /* [4 ]      */
        unsigned int wr_3dnr_uv_line_base_int_mask : 1;         /* [5 ]      */
        unsigned int wr_3dnr_uv_err_frm_end_int_mask : 1;       /* [6 ]      */
        unsigned int wr_3dnr_uv_err_immediate_int_mask : 1;     /* [7 ]      */
        unsigned int ldc_wr_y_frm_end_int_mask : 1;             /* [8 ]      */
        unsigned int ldc_wr_y_line_base_int_mask : 1;           /* [9 ]      */
        unsigned int ldc_wr_y_err_frm_end_int_mask : 1;         /* [10]      */
        unsigned int ldc_wr_y_err_immediate_int_mask : 1;       /* [11]      */
        unsigned int ldc_wr_uv_frm_end_int_mask : 1;            /* [12]      */
        unsigned int ldc_wr_uv_line_base_int_mask : 1;          /* [13]      */
        unsigned int ldc_wr_uv_err_frm_end_int_mask : 1;        /* [14]      */
        unsigned int ldc_wr_uv_err_immediate_int_mask : 1;      /* [15]      */
        unsigned int wdr_wr_raw_frm_end_int_mask : 1;           /* [16]      */
        unsigned int wdr_wr_raw_line_base_int_mask : 1;         /* [17]      */
        unsigned int wdr_wr_raw_err_frm_end_int_mask : 1;       /* [18]      */
        unsigned int wdr_wr_raw_err_immediate_int_mask : 1;     /* [19]      */
        unsigned int reserved0 : 4;                             /* [23..20]  */
        unsigned int main_out_wr_y_frm_end_int_mask : 1;        /* [24]      */
        unsigned int main_out_wr_y_line_base_int_mask : 1;      /* [25]      */
        unsigned int main_out_wr_y_err_frm_end_int_mask : 1;    /* [26]      */
        unsigned int main_out_wr_y_err_immediate_int_mask : 1;  /* [27]      */
        unsigned int main_out_wr_uv_frm_end_int_mask : 1;       /* [28]      */
        unsigned int main_out_wr_uv_line_base_int_mask : 1;     /* [29]      */
        unsigned int main_out_wr_uv_err_frm_end_int_mask : 1;   /* [30]      */
        unsigned int main_out_wr_uv_err_immediate_int_mask : 1; /* [31]      */
    } bits;                                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_INT_MASK0;
/*
* dma_ch8-15W Intr 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_out_wr_y_frm_end_int : 1;        /* [0 ]      */
        unsigned int ds0_out_wr_y_line_base_int : 1;      /* [1 ]      */
        unsigned int ds0_out_wr_y_err_frm_end_int : 1;    /* [2 ]      */
        unsigned int ds0_out_wr_y_err_immediate_int : 1;  /* [3 ]      */
        unsigned int ds0_out_wr_uv_frm_end_int : 1;       /* [4 ]      */
        unsigned int ds0_out_wr_uv_line_base_int : 1;     /* [5 ]      */
        unsigned int ds0_out_wr_uv_err_frm_end_int : 1;   /* [6 ]      */
        unsigned int ds0_out_wr_uv_err_immediate_int : 1; /* [7 ]      */
        unsigned int ds1_out_wr_y_frm_end_int : 1;        /* [8 ]      */
        unsigned int ds1_out_wr_y_line_base_int : 1;      /* [9 ]      */
        unsigned int ds1_out_wr_y_err_frm_end_int : 1;    /* [10]      */
        unsigned int ds1_out_wr_y_err_immediate_int : 1;  /* [11]      */
        unsigned int ds1_out_wr_uv_frm_end_int : 1;       /* [12]      */
        unsigned int ds1_out_wr_uv_line_base_int : 1;     /* [13]      */
        unsigned int ds1_out_wr_uv_err_frm_end_int : 1;   /* [14]      */
        unsigned int ds1_out_wr_uv_err_immediate_int : 1; /* [15]      */
        unsigned int ds2_out_wr_r_frm_end_int : 1;        /* [16]      */
        unsigned int ds2_out_wr_r_line_base_int : 1;      /* [17]      */
        unsigned int ds2_out_wr_r_err_frm_end_int : 1;    /* [18]      */
        unsigned int ds2_out_wr_r_err_immediate_int : 1;  /* [19]      */
        unsigned int ds2_out_wr_g_frm_end_int : 1;        /* [20]      */
        unsigned int ds2_out_wr_g_line_base_int : 1;      /* [21]      */
        unsigned int ds2_out_wr_g_err_frm_end_int : 1;    /* [22]      */
        unsigned int ds2_out_wr_g_err_immediate_int : 1;  /* [23]      */
        unsigned int ds2_out_wr_b_frm_end_int : 1;        /* [24]      */
        unsigned int ds2_out_wr_b_line_base_int : 1;      /* [25]      */
        unsigned int ds2_out_wr_b_err_frm_end_int : 1;    /* [26]      */
        unsigned int ds2_out_wr_b_err_immediate_int : 1;  /* [27]      */
        unsigned int reserved0 : 4;                       /* [31..28]  */
    } bits;                                               /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_INT_STATUS1;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int ds0_out_wr_y_frm_end_mask : 1;        /* [0 ]      */
        unsigned int ds0_out_wr_y_line_base_mask : 1;      /* [1 ]      */
        unsigned int ds0_out_wr_y_err_frm_end_mask : 1;    /* [2 ]      */
        unsigned int ds0_out_wr_y_err_immediate_mask : 1;  /* [3 ]      */
        unsigned int ds0_out_wr_uv_frm_end_mask : 1;       /* [4 ]      */
        unsigned int ds0_out_wr_uv_line_base_mask : 1;     /* [5 ]      */
        unsigned int ds0_out_wr_uv_err_frm_end_mask : 1;   /* [6 ]      */
        unsigned int ds0_out_wr_uv_err_immediate_mask : 1; /* [7 ]      */
        unsigned int ds1_out_wr_y_frm_end_mask : 1;        /* [8 ]      */
        unsigned int ds1_out_wr_y_line_base_mask : 1;      /* [9 ]      */
        unsigned int ds1_out_wr_y_err_frm_end_mask : 1;    /* [10]      */
        unsigned int ds1_out_wr_y_err_immediate_mask : 1;  /* [11]      */
        unsigned int ds1_out_wr_uv_frm_end_mask : 1;       /* [12]      */
        unsigned int ds1_out_wr_uv_line_base_mask : 1;     /* [13]      */
        unsigned int ds1_out_wr_uv_err_frm_end_mask : 1;   /* [14]      */
        unsigned int ds1_out_wr_uv_err_immediate_mask : 1; /* [15]      */
        unsigned int ds2_out_wr_r_frm_end_mask : 1;        /* [16]      */
        unsigned int ds2_out_wr_r_line_base_mask : 1;      /* [17]      */
        unsigned int ds2_out_wr_r_err_frm_end_mask : 1;    /* [18]      */
        unsigned int ds2_out_wr_r_err_immediate_mask : 1;  /* [19]      */
        unsigned int ds2_out_wr_g_frm_end_mask : 1;        /* [20]      */
        unsigned int ds2_out_wr_g_line_base_mask : 1;      /* [21]      */
        unsigned int ds2_out_wr_g_err_frm_end_mask : 1;    /* [22]      */
        unsigned int ds2_out_wr_g_err_immediate_mask : 1;  /* [23]      */
        unsigned int ds2_out_wr_b_frm_end_mask : 1;        /* [24]      */
        unsigned int ds2_out_wr_b_line_base_mask : 1;      /* [25]      */
        unsigned int ds2_out_wr_b_err_frm_end_mask : 1;    /* [26]      */
        unsigned int ds2_out_wr_b_err_immediate_mask : 1;  /* [27]      */
        unsigned int reserved0 : 4;                        /* [31..28]  */
    } bits;                                                /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_WR_INT_MASK1;
/*
* dma_ch0-7RIntr 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int rd_3dnr_y_frm_end_int : 1;        /* [0 ]      */
        unsigned int rd_3dnr_y_line_base_int : 1;      /* [1 ]      */
        unsigned int rd_3dnr_y_err_frm_end_int : 1;    /* [2 ]      */
        unsigned int rd_3dnr_y_err_immediate_int : 1;  /* [3 ]      */
        unsigned int rd_3dnr_uv_frm_end_int : 1;       /* [4 ]      */
        unsigned int rd_3dnr_uv_line_base_int : 1;     /* [5 ]      */
        unsigned int rd_3dnr_uv_err_frm_end_int : 1;   /* [6 ]      */
        unsigned int rd_3dnr_uv_err_immediate_int : 1; /* [7 ]      */
        unsigned int ldc_rd_y_frm_end_int : 1;         /* [8 ]      */
        unsigned int ldc_rd_y_line_base_int : 1;       /* [9 ]      */
        unsigned int ldc_rd_y_err_frm_end_int : 1;     /* [10]      */
        unsigned int ldc_rd_y_err_immediate_int : 1;   /* [11]      */
        unsigned int ldc_rd_uv_frm_end_int : 1;        /* [12]      */
        unsigned int ldc_rd_uv_line_base_int : 1;      /* [13]      */
        unsigned int ldc_rd_uv_err_frm_end_int : 1;    /* [14]      */
        unsigned int ldc_rd_uv_err_immediate_int : 1;  /* [15]      */
        unsigned int wdr_rd_raw_frm_end_int : 1;       /* [16]      */
        unsigned int wdr_rd_raw_line_base_int : 1;     /* [17]      */
        unsigned int wdr_rd_raw_err_frm_end_int : 1;   /* [18]      */
        unsigned int wdr_rd_raw_err_immediate_int : 1; /* [19]      */
        unsigned int reserved0 : 12;                   /* [31..20]  */
    } bits;                                            /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_INT_STATUS0;

typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int rd_3dnr_y_frm_end_int_mask : 1;        /* [0 ]      */
        unsigned int rd_3dnr_y_line_base_int_mask : 1;      /* [1 ]      */
        unsigned int rd_3dnr_y_err_frm_end_int_mask : 1;    /* [2 ]      */
        unsigned int rd_3dnr_y_err_immediate_int_mask : 1;  /* [3 ]      */
        unsigned int rd_3dnr_uv_frm_end_int_mask : 1;       /* [4 ]      */
        unsigned int rd_3dnr_uv_line_base_int_mask : 1;     /* [5 ]      */
        unsigned int rd_3dnr_uv_err_frm_end_int_mask : 1;   /* [6 ]      */
        unsigned int rd_3dnr_uv_err_immediate_int_mask : 1; /* [7 ]      */
        unsigned int ldc_rd_y_frm_end_int_mask : 1;         /* [8 ]      */
        unsigned int ldc_rd_y_line_base_int_mask : 1;       /* [9 ]      */
        unsigned int ldc_rd_y_err_frm_end_int_mask : 1;     /* [10]      */
        unsigned int ldc_rd_y_err_immediate_int_mask : 1;   /* [11]      */
        unsigned int ldc_rd_uv_frm_end_int_mask : 1;        /* [12]      */
        unsigned int ldc_rd_uv_line_base_int_mask : 1;      /* [13]      */
        unsigned int ldc_rd_uv_err_frm_end_int_mask : 1;    /* [14]      */
        unsigned int ldc_rd_uv_err_immediate_int_mask : 1;  /* [15]      */
        unsigned int wdr_rd_raw_frm_end_int_mask : 1;       /* [16]      */
        unsigned int wdr_rd_raw_line_base_int_mask : 1;     /* [17]      */
        unsigned int wdr_rd_raw_err_frm_end_int_mask : 1;   /* [18]      */
        unsigned int wdr_rd_raw_err_immediate_int_mask : 1; /* [19]      */
        unsigned int reserved0 : 12;                        /* [31..20]  */
    } bits;                                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_DMA_RD_INT_MASK0;
/*
* AXI status 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int axi_wr_ch_rst_req : 1; /* [0 ]      */
        unsigned int axi_rd_ch_rst_req : 1; /* [1 ]      */
        unsigned int reserved0 : 1;         /* [2 ]      */
        unsigned int reserved1 : 5;         /* [7 ..3 ]  */
        unsigned int axi_wr_ch_state : 1;   /* [8 ]      */
        unsigned int axi_rd_ch_state : 1;   /* [9 ]      */
        unsigned int reserved2 : 22;        /* [31..10]  */
    } bits;                                 /* Define an unsigned member */

    unsigned int u32;
} U_ISP_WRAP_AXI_CTL;
/*
* version 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_version_minor : 4;    /* [3 ..0 ]  */
        unsigned int isp_version_major : 4;    /* [7 ..4 ]  */
        unsigned int isp_license_version : 8;  /* [15..8 ]  */
        unsigned int isp_wdr_l2_info : 1;      /* [16]      */
        unsigned int isp_wdr_s1_info : 1;      /* [17]      */
        unsigned int reserved0 : 6;            /* [23..18]  */
        unsigned int isp_main_output_info : 1; /* [24]      */
        unsigned int isp_ds0_output_info : 1;  /* [25]      */
        unsigned int isp_ds1_output_info : 1;  /* [26]      */
        unsigned int isp_ds2_output_info : 1;  /* [27]      */
        unsigned int reserved1 : 4;            /* [31..28]  */
    } bits;                                    /* Define an unsigned member */

    unsigned int u32;
} U_ISP_VERSION;
/*
* release window 
*/
typedef union {
    /* Define the struct bits */
    struct
    {
        unsigned int isp_release_day : 8;       /* [7 ..0 ]  */
        unsigned int isp_release_month : 8;     /* [15..8 ]  */
        unsigned int isp_release_year_low : 8;  /* [23..16]  */
        unsigned int isp_release_year_high : 8; /* [31..24]  */
    } bits;                                     /* Define an unsigned member */

    unsigned int u32;
} U_ISP_RELEASE_INFO;
//
#define  ISP_WRAP_SWRST_CTL     		(0x0000)
#define  ISP_WRAP_DMA_SWRST_CTL     	(0x0004)
#define  ISP_WRAP_CTL_MODE     			(0x0008)
#define  ISP_WRAP_PIPE_CLK_CTL     		(0x000C)
#define  ISP_WRAP_DMA_EN_CTL     		(0x0010)
#define  ISP_WRAP_3DNR_WDR_FORMAT_CTL   (0x0014)
#define  ISP_WRAP_PIXEL_FORMAT_CTL     	(0x0018)
#define  ISP_WRAP_MAIN_OUT_SIZE     	(0x001C)
#define  ISP_WRAP_DS0_OUT_SIZE     		(0x0020)
#define  ISP_WRAP_DS1_OUT_SIZE     		(0x0024)
#define  ISP_WRAP_DS2_OUT_SIZE     		(0x0028)
#define  ISP_WRAP_BUF_SIZE_MASK0    	(0x002C)
#define  ISP_WRAP_BUF_SIZE_MASK1    	(0x0030)
#define  ISP_WRAP_BUF_SIZE_MASK2    	(0x0034)

#define  ISP_WRAP_DMA_ARB_MODE     		(0x003C)
#define  ISP_WRAP_DMA_WR_WEIGHT_0     	(0x0040)
#define  ISP_WRAP_DMA_WR_WEIGHT_1     	(0x0044)
#define  ISP_WRAP_DMA_RD_WEIGHT_0     	(0x0048)
#define  ISP_WRAP_DMA_RD_WEIGHT_1     	(0x004C)
#define  ISP_WRAP_DMA_WR_PRIORITY_0     (0x0050)
#define  ISP_WRAP_DMA_RD_PRIORITY_0     (0x0054)
#define  ISP_DMA_WR_CH_ID_0     		(0x0058)
#define  ISP_DMA_RD_CH_ID_0     		(0x005C)
#define  ISP_WRAP_DMA_WR_WEIGHT_2     	(0x0060)
#define  ISP_WRAP_DMA_WR_WEIGHT_3     	(0x0064)
#define  ISP_WRAP_DMA_RD_WEIGHT_2     	(0x0068)
#define  ISP_WRAP_DMA_RD_WEIGHT_3     	(0x006C)
#define  ISP_WRAP_DMA_WR_PRIORITY_1     (0x0070)
#define  ISP_WRAP_DMA_RD_PRIORITY_1     (0x0074)
#define  ISP_DMA_WR_CH_ID_1     		(0x0078)
#define  ISP_DMA_RD_CH_ID_1     		(0x007C)
#define  ISP_WRAP_WDR_LONG_BUF_BASE     (0x0080)
#define  ISP_WRAP_WDR_LONG_SIZE_CFG     (0x0084)
#define  ISP_WRAP_3DNR_Y_BUF_BASE     	(0x0088)
#define  ISP_WRAP_3DNR_UV_BUF_BASE     	(0x008C)
#define  ISP_WRAP_3DNR_STRIDE     		(0x0090)
#define  ISP_WRAP_LDC_Y_BUF_BASE    	(0x0094)
#define  ISP_WRAP_LDC_UV_BUF_BASE     	(0x0098)
#define  ISP_WRAP_LDC_STRIDE     		(0x009C)
#define  ISP_WRAP_MAIN_Y_BUF0_BASE     	(0x00A0)
#define  ISP_WRAP_MAIN_Y_BUF1_BASE     	(0x00A4)
#define  ISP_WRAP_MAIN_UV_BUF0_BASE     (0x00A8)
#define  ISP_WRAP_MAIN_UV_BUF1_BASE     (0x00AC)
#define  ISP_WRAP_MAIN_STRIDE     		(0x00B0)
#define  ISP_WRAP_DS0_Y_BUF0_BASE    	(0x00B4)
#define  ISP_WRAP_DS0_Y_BUF1_BASE    	(0x00B8)
#define  ISP_WRAP_DS0_UV_BUF0_BASE     	(0x00BC)
#define  ISP_WRAP_DS0_UV_BUF1_BASE     	(0x00C0)
#define  ISP_WRAP_DS0_STRIDE     		(0x00C4)
#define  ISP_WRAP_DS1_Y_BUF0_BASE    	(0x00C8)
#define  ISP_WRAP_DS1_Y_BUF1_BASE    	(0x00CC)
#define  ISP_WRAP_DS1_UV_BUF0_BASE     	(0x00D0)
#define  ISP_WRAP_DS1_UV_BUF1_BASE     	(0x00D4)
#define  ISP_WRAP_DS1_STRIDE     		(0x00D8)
#define  ISP_WRAP_DS2_R_BUF0_BASE     	(0x00DC)
#define  ISP_WRAP_DS2_R_BUF1_BASE     	(0x00E0)
#define  ISP_WRAP_DS2_G_BUF0_BASE     	(0x00E4)
#define  ISP_WRAP_DS2_G_BUF1_BASE     	(0x00E8)
#define  ISP_WRAP_DS2_B_BUF0_BASE     	(0x00EC)
#define  ISP_WRAP_DS2_B_BUF1_BASE     	(0x00F0)
#define  ISP_WRAP_DS2_STRIDE0    		(0x00F4)
#define  ISP_WRAP_DS2_STRIDE1    		(0x00F8)

#define  ISP_WRAP_DMA_CH0_CFG     		(0x0100)
#define  ISP_WRAP_DMA_CH1_CFG     		(0x0104)
#define  ISP_WRAP_DMA_CH2_CFG     		(0x0108)
#define  ISP_WRAP_DMA_CH3_CFG     		(0x010C)
#define  ISP_WRAP_DMA_CH4_CFG     		(0x0110)
#define  ISP_WRAP_DMA_CH5_CFG     		(0x0114)
#define  ISP_WRAP_DMA_CH6_CFG     		(0x0118)
#define  ISP_WRAP_DMA_CH7_CFG     		(0x011C)
#define  ISP_WRAP_DMA_CH8_CFG     		(0x0120)
#define  ISP_WRAP_DMA_CH9_CFG     		(0x0124)
#define  ISP_WRAP_DMA_CH10_CFG    		(0x0128)
#define  ISP_WRAP_DMA_CH11_CFG    		(0x012C)
#define  ISP_WRAP_DMA_CH12_CFG    		(0x0130)
#define  ISP_WRAP_DMA_CH13_CFG    		(0x0134)
#define  ISP_WRAP_DMA_CH14_CFG    		(0x0138)
#define  ISP_WRAP_DMA_CH15_CFG    		(0x013C)
#define  ISP_WRAP_DMA_CH0_ERR_DEC_CFG   (0x0140)
#define  ISP_WRAP_DMA_CH1_ERR_DEC_CFG   (0x0144)
#define  ISP_WRAP_DMA_CH2_ERR_DEC_CFG   (0x0148)
#define  ISP_WRAP_DMA_CH3_ERR_DEC_CFG   (0x014C)
#define  ISP_WRAP_DMA_CH4_ERR_DEC_CFG   (0x0150)
#define  ISP_WRAP_DMA_CH5_ERR_DEC_CFG   (0x0154)
#define  ISP_WRAP_DMA_CH6_ERR_DEC_CFG   (0x0158)
#define  ISP_WRAP_DMA_CH7_ERR_DEC_CFG   (0x015C)
#define  ISP_WRAP_DMA_CH8_ERR_DEC_CFG   (0x0160)
#define  ISP_WRAP_DMA_CH9_ERR_DEC_CFG   (0x0164)
#define  ISP_WRAP_DMA_CH10_ERR_DEC_CFG  (0x0168)
#define  ISP_WRAP_DMA_CH11_ERR_DEC_CFG  (0x016C)
#define  ISP_WRAP_DMA_CH12_ERR_DEC_CFG  (0x0170)
#define  ISP_WRAP_DMA_CH13_ERR_DEC_CFG  (0x0174)
#define  ISP_WRAP_DMA_CH14_ERR_DEC_CFG  (0x0178)
#define  ISP_WRAP_DMA_CH15_ERR_DEC_CFG  (0x017C)
#define  ISP_WRAP_DMA_CH0_ERR_STATUS    (0x0180)
#define  ISP_WRAP_DMA_CH1_ERR_STATUS    (0x0184)
#define  ISP_WRAP_DMA_CH2_ERR_STATUS    (0x0188)
#define  ISP_WRAP_DMA_CH3_ERR_STATUS    (0x018C)
#define  ISP_WRAP_DMA_CH4_ERR_STATUS    (0x0190)
#define  ISP_WRAP_DMA_CH5_ERR_STATUS    (0x0194)
#define  ISP_WRAP_DMA_CH6_ERR_STATUS    (0x0198)
#define  ISP_WRAP_DMA_CH7_ERR_STATUS    (0x019C)
#define  ISP_WRAP_DMA_CH8_ERR_STATUS    (0x01A0)
#define  ISP_WRAP_DMA_CH9_ERR_STATUS    (0x01A4)
#define  ISP_WRAP_DMA_CH10_ERR_STATUS   (0x01A8)
#define  ISP_WRAP_DMA_CH11_ERR_STATUS   (0x01AC)
#define  ISP_WRAP_DMA_CH12_ERR_STATUS   (0x01B0)
#define  ISP_WRAP_DMA_CH13_ERR_STATUS   (0x01B4)
#define  ISP_WRAP_DMA_CH14_ERR_STATUS   (0x01B8)
#define  ISP_WRAP_DMA_CH15_ERR_STATUS   (0x01BC)

#define  ISP_WRAP_CONFIG_DONE     		(0x01D8)
#define  ISP_WRAP_CORE_INT_CTL     		(0x01DC)
#define  ISP_WRAP_DMA_WR_INT_STATUS0    (0x01E0)
#define  ISP_WRAP_DMA_WR_INT_MASK0     	(0x01E4)
#define  ISP_WRAP_DMA_WR_INT_STATUS1    (0x01E8)
#define  ISP_WRAP_DMA_WR_INT_MASK1     	(0x01EC)
#define  ISP_WRAP_DMA_RD_INT_STATUS0    (0x01F0)
#define  ISP_WRAP_DMA_RD_INT_MASK0     	(0x01F4)
#define  ISP_WRAP_AXI_CTL     			(0x01F8)

#define  ISP_VERSION     				(0x03C0)
#define  ISP_RELEASE_INFO     			(0x03C4)

#endif /*_ISP_WRAP_REG_H_*/
