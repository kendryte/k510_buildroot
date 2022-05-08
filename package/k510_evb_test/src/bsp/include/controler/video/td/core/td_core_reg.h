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

#ifndef _TD_CORE_REG_DEF_H_
#define _TD_CORE_REG_DEF_H_

/*
* ROTATION
*/
typedef union { /* TD_RotCmd */
   
    struct 
    {
        unsigned int framestart                  : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_ROT_CMD;

typedef union { /* TD_RotCtl */
   
    struct 
    {
        unsigned int rotmode                     : 2;
        unsigned int reserved0                   : 2;
        unsigned int pixformat                   : 2;
        unsigned int reserved1                   : 2;
        unsigned int Inswap                      : 1;
        unsigned int endianInEn                  : 1;
        unsigned int Outswap                     : 1;
        unsigned int endianOutEn                 : 1;
        unsigned int reserved2                   : 4;
        unsigned int otmaxrd                     : 6;
        unsigned int reserved3                   : 2;
        unsigned int otmaxwr                     : 6;
        unsigned int reserved4                   : 2;
    } bits;     
    unsigned int u32;
} U_TD_ROT_CTL;

typedef union { /* TD_RotTimeOut */
   
    struct 
    {
        unsigned int val                         : 16;
        unsigned int reserved                    : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_TIME_OUT;

typedef union { /* TD_RotImageSizeActive */
   
    struct 
    {
        unsigned int hor                         : 16;
        unsigned int ver                         : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_IMAGE_SIZE_ACTIVE;

typedef union { /* TD_ROT_FRM_BASE_ADDR_Y_SRC */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_Y_SRC;

typedef union { /* TD_ROT_FRM_BASE_ADDR_U_SRC */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_U_SRC;

typedef union { /* TD_ROT_FRM_BASE_ADDR_V_SRC */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_V_SRC;

typedef union { /* TD_ROT_FRM_BASE_ADDR_Y_DES */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_Y_DES;

typedef union { /* TD_ROT_FRM_BASE_ADDR_U_DES */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_U_DES;

typedef union { /* TD_ROT_FRM_BASE_ADDR_V_DES */
   
    struct 
    {
        unsigned int addr                        : 32;
    } bits;     
    unsigned int u32;
} U_TD_ROT_FRM_BASE_ADDR_V_DES;

typedef union { /* TD_RotStrideY */
   
    struct 
    {
        unsigned int src                         : 16;
        unsigned int des                         : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_STRIDE_Y;

typedef union { /* TD_RotStrideU */
   
    struct 
    {
        unsigned int src                         : 16;
        unsigned int des                         : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_STRIDE_U;

typedef union { /* TD_RotStrideV */
   
    struct 
    {
        unsigned int src                         : 16;
        unsigned int des                         : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_STRIDE_V;

typedef union { /* TD_RotSt */   
    struct
    {
        unsigned int frameend                    : 1;
        unsigned int done                        : 3;
        unsigned int reserved0                   : 4;
        unsigned int dmard                       : 3;
        unsigned int reserved1                   : 1;
        unsigned int dmawr                       : 3;
        unsigned int reserved2                   : 1;
        unsigned int cyclecnt                    : 16;
    } bits;     
    unsigned int u32;
} U_TD_ROT_STS;


/*
*Scaler/Mixer
*/
typedef union { /* TD_SoftRstCtl */
   
    struct 
    {
        unsigned int mix                         : 1;
        unsigned int axi                         : 1;
        unsigned int apb                         : 1;
        unsigned int core                        : 1;
        unsigned int reserved0                   : 28;
    } bits;     
    unsigned int u32;
} U_TD_SOFT_RST_CTL;

typedef union { /* TD_DmaSwCtl */   
    struct 
    {
        unsigned int reqwr                       : 1;
        unsigned int reserved0                   : 3;
        unsigned int reqrd                       : 1;
        unsigned int reserved1                   : 27;
    } bits;     
    unsigned int u32;
} U_TD_DMA_SW_CTL;

typedef union { /* TD_Layer0Line0BdCtl */
   
    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_LINE0_BD_CTL;

typedef union { /* TD_Layer0Line1BdCtl */
   
    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_LINE1_BD_CTL;

typedef union { /* TD_Layer0Line2BdCtl */
   
    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_LINE2_BD_CTL;

typedef union { /* TD_Layer0Line3BdCtl */
   
    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_LINE3_BD_CTL;

typedef union { /* TD_Layer4BdCtl */
   
    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER4_BD_CTL;
/*
*AREA/SIZE CONTROL
*/
typedef union { /* TD_DispXZone */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_XZONE_CTL;

typedef union { /* TD_DispYZone */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YZONE_CTL;

typedef union { /* TD_Layer0XCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_XCTL;

typedef union { /* TD_Layer0YCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_YCTL;

typedef union { /* TD_Layer4XCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER4_XCTL;

typedef union { /* TD_Layer4YCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER4_YCTL;

typedef union { /* TD_DispHsyncCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_HSYNC_CTL;

typedef union { /* TD_DispVsyncCtl */
   
    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_VSYNC_CTL;

typedef union { /* TD_DispCtl */
   
    struct 
    {
        unsigned int vcntbit0                    : 1;
        unsigned int reserved0                   : 7;
        unsigned int secndfoffset                : 1;
        unsigned int reserved1                   : 7;
        unsigned int framesyncdly                : 8;
        unsigned int reserved2                   : 8;
    } bits;     
    unsigned int u32;
} U_TD_DISP_CTL;

typedef union { /* TD_DispEnable */
   
    struct 
    {
        unsigned int layer0en                    : 1;
        unsigned int layer0enhs                  : 1;
        unsigned int layer0Wenhs                 : 1;
        unsigned int reserved0                   : 1;
        unsigned int layer4en                    : 1;
        unsigned int layer4enhs                  : 1;
        unsigned int layer4Wenhs                 : 1;
        unsigned int framestart                  : 1;
        unsigned int reserved1                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_DISP_ENABLE;

typedef union { /* TD_DispSize */
   
    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_SIZE;

typedef union { /* TD_Layer0Ctl */
   
    struct 
    {
        unsigned int enable                      : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_CTL;

typedef union { /* TD_Layer0ScaleBlenth */
   
    struct 
    {
        unsigned int blen                        : 4;
        unsigned int reserved0                   : 28;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_SCALE_BLENTH;

typedef union { /* TD_Layer0ImgInDatMode */
   
    struct 
    {
        unsigned int datmode                     : 5;
        unsigned int reserved0                   : 3;
        unsigned int endiany                     : 2;
        unsigned int reserved1                   : 2;
        unsigned int endianuv                    : 3;
        unsigned int reserved2                   : 9;
        unsigned int swapuv                      : 1;
        unsigned int reserved3                   : 7;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_IMG_IN_DAT_MODE;

typedef union{ /*TD_LAYER0_BADDR0_Y*/
    struct 
    {
        unsigned int addr                       : 32;
    } bits;
    unsigned int u32;
}U_TD_LAYER0_BADDR0_Y;

typedef union{ /*TD_LAYER0_BADDR0_UV*/
    struct 
    {
        unsigned int addr                       : 32;
    } bits;
    unsigned int u32;
}U_TD_LAYER0_BADDR0_UV;

typedef union { /* TD_Layer0ImgInPixSzie */
   
    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_IMG_IN_PIX_SIZE;

typedef union { /* TD_Layer0ImgOutPixSzie */
   
    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_IMG_OUT_PIX_SIZE;

typedef union { /* TD_Layer0ImgInStride */
   
    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_IMG_IN_STRIDE;

typedef union { /* TD_Layer0ImgInOffset */
   
    struct 
    {
        unsigned int hoffset                     : 13;
        unsigned int reserved0                   : 3;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_IMG_IN_OFFSET;

typedef union { /* TD_Layer0VscaleStep */
   
    struct 
    {
        unsigned int pstep                       : 8;
        unsigned int reserved0                   : 8;
        unsigned int dstep                       : 16;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_VSCALE_STEP;

typedef union { /* TD_Layer0VscaleSt */
   
    struct 
    {
        unsigned int pstep                       : 16;
        unsigned int reserved0                   : 16;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_VSCALE_ST;

typedef union { /* TD_Layer0HscaleStep */
   
    struct 
    {
        unsigned int pstep                       : 8;
        unsigned int reserved0                   : 8;
        unsigned int dstep                       : 16;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_HSCALE_STEP;

typedef union { /* TD_Layer0HscaleSt */
   
    struct {
        unsigned int pstep                       : 16;
        unsigned int reserved0                   : 16;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_HSCALE_ST;

typedef union { /* TD_Layer0BaseMode */
   
    struct {
        unsigned int mode                        : 1;
        unsigned int reserved0                   : 3;
        unsigned int base0mask                   : 1;
        unsigned int reserved1                   : 3;
        unsigned int base1mask                   : 1;
        unsigned int reserved2                   : 3;
        unsigned int addrflag                    : 1;
        unsigned int reserved3                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_LAYER0_BASE_MODE;
/*
*LAYER4 (OSD0)
*/
typedef union { /* TD_Osd0Info */
   
    struct {
        unsigned int osdtype                     : 4;
        unsigned int alphatpye                   : 3;
        unsigned int reserved0                   : 25;
    } bits;     
    unsigned int u32;
} U_TD_OSD0_INFO;

typedef union { /* TD_Osd0Size */
   
    struct {
        unsigned int width                       : 16;
        unsigned int height                      : 16;
    } bits;     
    unsigned int u32;
} U_TD_OSD0_SIZE;

typedef union{ /*TD_DISP_OSD0_VLU_ADDR0*/
    struct 
    {
        unsigned int addr                       : 32;
    } bits;
    unsigned int u32;
}U_TD_DISP_OSD0_VLU_ADDR0;

typedef union{ /*TD_DISP_OSD0_ALP_ADDR0*/
    struct 
    {
        unsigned int addr                       : 32;
    } bits;
    unsigned int u32;
}U_TD_DISP_OSD0_ALP_ADDR0;

typedef union { /* TD_Osd0DMACtl */
   
    struct 
    {
        unsigned int dmarequestlen               : 4;
        unsigned int dmamap                      : 2;
        unsigned int rgbrev                      : 1;
        unsigned int reserved0                   : 25;
    } bits;     
    unsigned int u32;
} U_TD_OSD0_DMA_CTL;

typedef union { /* TD_Osd0Stride */
   
    struct 
    {
        unsigned int osdstride                   : 16;
        unsigned int alpstride                   : 16;
    } bits;     
    unsigned int u32;
} U_TD_OSD0_STRIDE;

typedef union { /* TD_OsdRGB2YUVCtl */
   
    struct 
    {
        unsigned int osd0en                      : 1;
        unsigned int reserved0                   : 7;
        unsigned int osd1en                      : 1;
        unsigned int reserved1                   : 7;
        unsigned int osd2en                      : 1;
        unsigned int reserved2                   : 15;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_CTL;

typedef union { /* TD_OsdRGB2YUVCoeff00 */
   
    struct {
        unsigned int c00                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF00;

typedef union { /* TD_OsdRGB2YUVCoeff01 */
   
    struct {
        unsigned int c01                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF01;

typedef union { /* TD_OsdRGB2YUVCoeff02 */
   
    struct 
    {
        unsigned int c02                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF02;

typedef union { /* TD_OsdRGB2YUVCoeff03 */
   
    struct 
    {
        unsigned int c03                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF03;

typedef union { /* TD_OsdRGB2YUVCoeff10 */
   
    struct {
        unsigned int c10                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF10;

typedef union { /* TD_OsdRGB2YUVCoeff11 */
   
    struct 
    {
        unsigned int c11                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF11;

typedef union { /* TD_OsdRGB2YUVCoeff12 */
   
    struct 
    {
        unsigned int c12                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF12;

typedef union { /* TD_OsdRGB2YUVCoeff13 */
   
    struct 
    {
        unsigned int c13                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF13;

typedef union { /* TD_OsdRGB2YUVCoeff20 */
   
    struct {
        unsigned int c20                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF20;

typedef union { /* TD_OsdRGB2YUVCoeff21 */
   
    struct {
        unsigned int c21                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF21;

typedef union { /* TD_OsdRGB2YUVCoeff22 */
   
    struct 
    {
        unsigned int c22                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF22;

typedef union { /* TD_OsdRGB2YUVCoeff23 */
   
    struct 
    {
        unsigned int c23                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_OSD_RGB2YUV_COEFF23;

typedef union { /* TD_DispYUV2RGBCtl */
   
    struct 
    {
        unsigned int en                          : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_CTL;

typedef union { /* TD_DispYUV2RGBCoeff00 */
   
    struct 
    {
        unsigned int c00                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF00;

typedef union { /* TD_DispYUV2RGBCoeff01 */
   
    struct 
    {
        unsigned int c01                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF01;

typedef union { /* TD_DispYUV2RGBCoeff02 */
   
    struct 
    {
        unsigned int c02                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF02;

typedef union { /* TD_DispYUV2RGBCoeff03 */
   
    struct 
    {
        unsigned int c03                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF03;

typedef union { /* TD_DispYUV2RGBCoeff10 */
   
    struct 
    {
        unsigned int c10                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF10;

typedef union { /* TD_DispYUV2RGBCoeff11 */
   
    struct 
    {
        unsigned int c11                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF11;

typedef union { /* TD_DispYUV2RGBCoeff12 */
   
    struct 
    {
        unsigned int c12                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF12;

typedef union { /* TD_DispYUV2RGBCoeff13 */
   
    struct 
    {
        unsigned int c13                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF13;

typedef union { /* TD_DispYUV2RGBCoeff20 */
   
    struct 
    {
        unsigned int c20                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF20;

typedef union { /* TD_DispYUV2RGBCoeff21 */
   
    struct 
    {
        unsigned int c21                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF21;

typedef union { /* TD_DispYUV2RGBCoeff22 */
   
    struct 
    {
        unsigned int c22                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF22;

typedef union { /* TD_DispYUV2RGBCoeff23 */
   
    struct 
    {
        unsigned int c23                         : 12;
        unsigned int reserved0                   : 20;
    } bits;     
    unsigned int u32;
} U_TD_DISP_YUV2RGB_COEFF23;
/*
*MIXER OUTPUT
*/
typedef union { /* TD_DispMixAlp0 */
   
    struct 
    {
        unsigned int layer0glbalp                : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_DISP_MIX_ALP0;

typedef union { /* TD_DispMixAlp1 */
   
    struct 
    {
        unsigned int layer4glbalp                : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_DISP_MIX_ALP1;

typedef union { /* TD_DispMixSel */
   
    struct 
    {
        unsigned int layer0sel                   : 3;
        unsigned int reserved0                   : 13;
        unsigned int layer1sel                   : 3;
        unsigned int reserved1                   : 13;
    } bits;     
    unsigned int u32;
} U_TD_DISP_MIX_SEL;

typedef union { /* TD_DispBackGroud */
   
    struct 
    {
        unsigned int y                           : 8;
        unsigned int u                           : 8;
        unsigned int v                           : 8;
        unsigned int reserved0                   : 8;
    } bits;     
    unsigned int u32;
} U_TD_DISP_BACK_GROUD;

/*
*INTERRUPT
*/
typedef union { /* TD_DispIRQ0 */
   
    struct 
    {
        unsigned int reserved0                     : 20;
        unsigned int en                            : 1;
        unsigned int reserved1                     : 11;
    } bits;     
    unsigned int u32;
} U_TD_DISP_IRQ0;

typedef union { /* TD_DispIRQ1 */
   
    struct 
    {
        unsigned int underrundcnt                : 13;
        unsigned int reserved0                   : 7;
        unsigned int en                          : 1;
        unsigned int reserved1                   : 11;
    } bits;     
    unsigned int u32;
} U_TD_DISP_IRQ1;

typedef union { /* TD_DispIRQ2 */
   
    struct 
    {
        unsigned int reserved0                   : 20;
        unsigned int en                          : 1;
        unsigned int reserved1                   : 11;
    } bits;     
    unsigned int u32;
} U_TD_DISP_IRQ2;

typedef union { /* TD_DispIRQ */
   
    struct 
    {
        unsigned int irq0                        : 1;
        unsigned int irq0ctl                     : 1;
        unsigned int irq1                        : 1;
        unsigned int reserved0                   : 13;
        unsigned int underrun                    : 8;
        unsigned int reserved1                   : 4;
        unsigned int addrflag                    : 1;
        unsigned int reserved2                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_DISP_IRQ;
/*
*DMA WRITE BACK
*/
typedef union { /* TD_WbDma */
   
    struct {
        unsigned int y_en                        : 1;
        unsigned int uv_en                       : 1;
        unsigned int reserved0                   : 30;
    } bits;     
    unsigned int u32;
} U_TD_WB_DMA_WR_EN;

typedef union { /* TD_WbMode */
   
    struct 
    {
        unsigned int reserved0                   : 2;
        unsigned int input                       : 1;
        unsigned int reserved1                   : 29;
    } bits;     
    unsigned int u32;
} U_TD_WB_MODE;

typedef union { /* TD_WbPixel */
   
    struct 
    {
        unsigned int formatsel                   : 1;
        unsigned int inputformat                 : 1;
        unsigned int outputformat                : 1;
        unsigned int pixelorder422               : 2;
        unsigned int rgbpixelwidth               : 3;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_WB_PIXEL_FORMAT_OUT;

typedef union { /* TD_WB_FRM_BASE_OUT_ADDR0_Y */
   
    struct 
    {
        unsigned int addr                         : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_FRM_BASE_OUT_ADDR0_Y;

typedef union { /* TD_WB_FRM_BASE_OUT_ADDR1_Y */
   
    struct 
    {
        unsigned int addr                         : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_FRM_BASE_OUT_ADDR1_Y;

typedef union { /* TD_WB_FRM_BASE_OUT_ADDR0_UV */
   
    struct 
    {
        unsigned int addr                         : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_FRM_BASE_OUT_ADDR0_UV;

typedef union { /* TD_WB_FRM_BASE_OUT_ADDR1_UV */
   
    struct 
    {
        unsigned int addr                         : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_FRM_BASE_OUT_ADDR1_UV;

typedef union { /* TD_WB_HSTRIDE_OUT_Y */
   
    struct 
    {
        unsigned int hstride                     : 13;
        unsigned int reserved0                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_WB_HSTRIDE_OUT_Y;

typedef union { /* U_TD_WB_HSTRIDE_OUT_UV */
   
    struct 
    {
        unsigned int hstride                     : 13;
        unsigned int reserved0                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_WB_HSTRIDE_OUT_UV;

typedef union { /* TD_WB_FRM_BUF_SIZE_OUT */
   
    struct 
    {
        unsigned int buffersize                  : 16;
        unsigned int reserved0                   : 16;
    } bits;     
    unsigned int u32;
} U_TD_WB_FRM_BUF_SIZE_OUT;

typedef union { /* TD_WB_V_SIZE_ACTIVE_OUT */
   
    struct 
    {
        unsigned int size                        : 13;
        unsigned int reserved0                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_WB_V_SIZE_ACTIVE_OUT;

typedef union { /* TD_WB_H_SIZE_ACTIVE_OUT */
   
    struct 
    {
        unsigned int size                        : 13;
        unsigned int reserved0                   : 19;
    } bits;     
    unsigned int u32;
} U_TD_WB_H_SIZE_ACTIVE_OUT;

typedef union { /* TD_WB_CH0_DMA_MODE */
   
    struct 
    {
        unsigned int otnum                       : 4;
        unsigned int reserved0                   : 8;
        unsigned int blen                        : 1;
        unsigned int reserved1                   : 1;
        unsigned int continuousmode              : 1;
        unsigned int swap                        : 1;
        unsigned int reserved2                   : 12;
        unsigned int errdetecten                 : 1;
        unsigned int reserved3                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH0_DMA_MODE;

typedef union { /* TD_WbCh0ErrUnit */
   
    struct 
    {
        unsigned int unit                        : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH0_ERR_UNIT;

typedef union { /* TD_WbCh0ErrTh */
   
    struct 
    {
        unsigned int threshold                   : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH0_ERR_TH;

typedef union { /* U_TD_WB_CH0_INFO_CLR */
   
    struct 
    {
        unsigned int frmcntclear                 : 1;
        unsigned int fifoerrclear                : 1;
        unsigned int maxbw                       : 1;
        unsigned int totalbw                     : 1;
        unsigned int reserved0                   : 28;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH0_INFO_CLR;

typedef union { /* TD_WbCh0Rst */
   
    struct 
    {
        unsigned int request                     : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH0_RST_REQ;

typedef union { /* TD_WbCh1Dma */
   
    struct 
    {
        unsigned int otnum                       : 4;
        unsigned int reserved0                   : 8;
        unsigned int blen                        : 1;
        unsigned int reserved1                   : 1;
        unsigned int continuousmode              : 1;
        unsigned int swap                        : 1;
        unsigned int reserved2                   : 12;
        unsigned int errdetecten                 : 1;
        unsigned int reserved3                   : 3;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH1_DMA_MODE;

typedef union { /* TD_WbCh1ErrUnit */
   
    struct 
    {
        unsigned int unit                        : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH1_ERR_UNIT;

typedef union { /* TD_WbCh1ErrTh */
   
    struct 
    {
        unsigned int threshold                   : 8;
        unsigned int reserved0                   : 24;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH1_ERR_TH;

typedef union { /* TD_WbCh1Info */
   
    struct 
    {
        unsigned int frmcntclear                 : 1;
        unsigned int fifoerrclear                : 1;
        unsigned int maxbw                       : 1;
        unsigned int totalbw                     : 1;
        unsigned int reserved0                   : 28;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH1_INFO_CLR;

typedef union { /* TD_WbCh1Rst */
   
    struct 
    {
        unsigned int request                     : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_CH1_RST_REQ;

typedef union { /* TD_WbYOutIdle */
   
    struct {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_Y_OUT_IDLE;

typedef union { /* TD_WbUVOutIdle */
   
    struct {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_UV_OUT_IDLE;

typedef union { /* TD_WbYOutInt */
   
    struct {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_Y_OUT_INT;

typedef union { /* TD_WbUVOutInt */
   
    struct {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;     
    unsigned int u32;
} U_TD_WB_UV_OUT_INT;

typedef union { /* TD_WbYOutFunc0 */
   
    struct {
        unsigned int frmcnt                      : 16;
        unsigned int buffererrcnt                : 16;
    } bits;     
    unsigned int u32;
} U_TD_WB_Y_OUT_FUNC0;

typedef union { /* TD_WbYOutFunc1 */
   
    struct {
        unsigned int maxbd                       : 8;
        unsigned int totalbd                     : 18;
        unsigned int reserved0                   : 4;
        unsigned int frmbasesel                  : 1;
        unsigned int dmabusy                     : 1;
    } bits;     
    unsigned int u32;
} U_TD_WB_Y_OUT_FUNC1;

typedef union { /* TD_WbUVOutFunc0 */
   
    struct {
        unsigned int frmcnt                      : 16;
        unsigned int buffererrcnt                : 16;
    } bits;     
    unsigned int u32;
} U_TD_WB_UV_OUT_FUNC0;

typedef union { /* TD_WbUVOutFunc1 */
   
    struct {
        unsigned int maxbd                       : 8;
        unsigned int totalbd                     : 18;
        unsigned int reserved0                   : 4;
        unsigned int frmbasesel                  : 1;
        unsigned int dmabusy                     : 1;
    } bits;     
    unsigned int u32;
} U_TD_WB_UV_OUT_FUNC1;

typedef struct 
{    
    volatile U_TD_ROT_CMD                		TD_ROT_CMD;
    volatile U_TD_ROT_CTL                		TD_ROT_CTL;
    volatile U_TD_ROT_TIME_OUT           		TD_ROT_TIME_OUT;
    volatile U_TD_ROT_IMAGE_SIZE_ACTIVE  		TD_ROT_IMAGE_SIZE_ACTIVE;
    volatile U_TD_ROT_FRM_BASE_ADDR_Y_SRC		TD_ROT_FRM_BASE_ADDR_Y_SRC;
    volatile U_TD_ROT_FRM_BASE_ADDR_U_SRC		TD_ROT_FRM_BASE_ADDR_U_SRC;
    volatile U_TD_ROT_FRM_BASE_ADDR_V_SRC		TD_ROT_FRM_BASE_ADDR_V_SRC;
    volatile U_TD_ROT_FRM_BASE_ADDR_Y_DES		TD_ROT_FRM_BASE_ADDR_Y_DES;
    volatile U_TD_ROT_FRM_BASE_ADDR_U_DES		TD_ROT_FRM_BASE_ADDR_U_DES;
    volatile U_TD_ROT_FRM_BASE_ADDR_V_DES		TD_ROT_FRM_BASE_ADDR_V_DES;
    volatile U_TD_ROT_STRIDE_Y           		TD_ROT_STRIDE_Y;
    volatile U_TD_ROT_STRIDE_U           		TD_ROT_STRIDE_U;
    volatile U_TD_ROT_STRIDE_V           		TD_ROT_STRIDE_V;
    volatile unsigned int                       reserved0[3];
    volatile U_TD_ROT_STS                       TD_ROT_STS;
} S_TD_ROTATION_REGS_TYPE;

typedef struct 
{
    volatile U_TD_SOFT_RST_CTL              TD_SOFT_RST_CTL;
    volatile unsigned int                   reserved0;
    volatile U_TD_DMA_SW_CTL                TD_DMA_SW_CTL;
    volatile unsigned int                   reserved1[29];
    volatile U_TD_LAYER0_LINE0_BD_CTL       TD_LAYER0_LINE0_BD_CTL;
    volatile U_TD_LAYER0_LINE1_BD_CTL       TD_LAYER0_LINE1_BD_CTL;
    volatile U_TD_LAYER0_LINE2_BD_CTL       TD_LAYER0_LINE2_BD_CTL;
    volatile U_TD_LAYER0_LINE3_BD_CTL       TD_LAYER0_LINE3_BD_CTL;
    volatile unsigned int                   reserved2[3];
    volatile U_TD_LAYER4_BD_CTL             TD_LAYER4_BD_CTL;
    volatile unsigned int                   reserved3[8];
    volatile U_TD_DISP_XZONE_CTL            TD_DISP_XZONE_CTL;
    volatile U_TD_DISP_YZONE_CTL            TD_DISP_YZONE_CTL;
    volatile U_TD_LAYER0_XCTL               TD_LAYER0_XCTL;
    volatile U_TD_LAYER0_YCTL               TD_LAYER0_YCTL;
    volatile unsigned int                   reserved4[6];
    volatile U_TD_LAYER4_XCTL               TD_LAYER4_XCTL;
    volatile U_TD_LAYER4_YCTL               TD_LAYER4_YCTL;
    volatile unsigned int                   reserved5[4];
    volatile U_TD_DISP_HSYNC_CTL            TD_DISP_HSYNC_CTL;
    volatile U_TD_DISP_VSYNC_CTL            TD_DISP_VSYNC_CTL;
    volatile unsigned int                   reserved6[3];
    volatile U_TD_DISP_CTL                  TD_DISP_CTL;
    volatile U_TD_DISP_ENABLE               TD_DISP_ENABLE;
    volatile U_TD_DISP_SIZE                 TD_DISP_SIZE;
    volatile unsigned int                   reserved7[8];
    volatile U_TD_LAYER0_CTL                TD_LAYER0_CTL;
    volatile U_TD_LAYER0_SCALE_BLENTH       TD_LAYER0_SCALE_BLENTH;
    volatile U_TD_LAYER0_IMG_IN_DAT_MODE    TD_LAYER0_IMG_IN_DAT_MODE;
    volatile U_TD_LAYER0_BADDR0_Y           TD_LAYER0_BADDR0_Y;
    volatile U_TD_LAYER0_BADDR0_UV          TD_LAYER0_BADDR0_UV;
    volatile unsigned int                   reserved8[2];
    volatile U_TD_LAYER0_IMG_IN_PIX_SIZE    TD_LAYER0_IMG_IN_PIX_SIZE;
    volatile U_TD_LAYER0_IMG_OUT_PIX_SIZE   TD_LAYER0_IMG_OUT_PIX_SIZE;
    volatile U_TD_LAYER0_IMG_IN_STRIDE      TD_LAYER0_IMG_IN_STRIDE;
    volatile unsigned int                   reserved9;
    volatile U_TD_LAYER0_IMG_IN_OFFSET      TD_LAYER0_IMG_IN_OFFSET;
    volatile unsigned int                   reserved10;
    volatile U_TD_LAYER0_VSCALE_STEP        TD_LAYER0_VSCALE_STEP;
    volatile U_TD_LAYER0_VSCALE_ST          TD_LAYER0_VSCALE_ST;
    volatile U_TD_LAYER0_HSCALE_STEP        TD_LAYER0_HSCALE_STEP;
    volatile U_TD_LAYER0_HSCALE_ST          TD_LAYER0_HSCALE_ST;
    volatile U_TD_LAYER0_BASE_MODE          TD_LAYER0_BASE_MODE;
    volatile unsigned int                   reserved11[62];
    volatile U_TD_OSD0_INFO                 TD_OSD0_INFO;
    volatile U_TD_OSD0_SIZE                 TD_OSD0_SIZE;
    volatile U_TD_DISP_OSD0_VLU_ADDR0       TD_DISP_OSD0_VLU_ADDR0;
    volatile U_TD_DISP_OSD0_ALP_ADDR0       TD_DISP_OSD0_ALP_ADDR0;
    volatile unsigned int                   reserved12[2];
    volatile U_TD_OSD0_DMA_CTL              TD_OSD0_DMA_CTL;
    volatile U_TD_OSD0_STRIDE               TD_OSD0_STRIDE;
    volatile unsigned int                   reserved13[40];
    volatile U_TD_OSD_RGB2YUV_CTL           TD_OSD_RGB2YUV_CTL;
    volatile U_TD_OSD_RGB2YUV_COEFF00       TD_OSD_RGB2YUV_COEFF00;
    volatile U_TD_OSD_RGB2YUV_COEFF01       TD_OSD_RGB2YUV_COEFF01;
    volatile U_TD_OSD_RGB2YUV_COEFF02       TD_OSD_RGB2YUV_COEFF02;
    volatile U_TD_OSD_RGB2YUV_COEFF03       TD_OSD_RGB2YUV_COEFF03;
    volatile U_TD_OSD_RGB2YUV_COEFF10       TD_OSD_RGB2YUV_COEFF10;
    volatile U_TD_OSD_RGB2YUV_COEFF11       TD_OSD_RGB2YUV_COEFF11;
    volatile U_TD_OSD_RGB2YUV_COEFF12       TD_OSD_RGB2YUV_COEFF12;
    volatile U_TD_OSD_RGB2YUV_COEFF13       TD_OSD_RGB2YUV_COEFF13;
    volatile U_TD_OSD_RGB2YUV_COEFF20       TD_OSD_RGB2YUV_COEFF20;
    volatile U_TD_OSD_RGB2YUV_COEFF21       TD_OSD_RGB2YUV_COEFF21;
    volatile U_TD_OSD_RGB2YUV_COEFF22       TD_OSD_RGB2YUV_COEFF22;
    volatile U_TD_OSD_RGB2YUV_COEFF23       TD_OSD_RGB2YUV_COEFF23;
    volatile unsigned int                   reserved14[4];
    volatile U_TD_DISP_YUV2RGB_CTL          TD_DISP_YUV2RGB_CTL;
    volatile U_TD_DISP_YUV2RGB_COEFF00      TD_DISP_YUV2RGB_COEFF00;
    volatile U_TD_DISP_YUV2RGB_COEFF01      TD_DISP_YUV2RGB_COEFF01;
    volatile U_TD_DISP_YUV2RGB_COEFF02      TD_DISP_YUV2RGB_COEFF02;
    volatile U_TD_DISP_YUV2RGB_COEFF03      TD_DISP_YUV2RGB_COEFF03;
    volatile U_TD_DISP_YUV2RGB_COEFF10      TD_DISP_YUV2RGB_COEFF10;
    volatile U_TD_DISP_YUV2RGB_COEFF11      TD_DISP_YUV2RGB_COEFF11;
    volatile U_TD_DISP_YUV2RGB_COEFF12      TD_DISP_YUV2RGB_COEFF12;
    volatile U_TD_DISP_YUV2RGB_COEFF13      TD_DISP_YUV2RGB_COEFF13;
    volatile U_TD_DISP_YUV2RGB_COEFF20      TD_DISP_YUV2RGB_COEFF20;
    volatile U_TD_DISP_YUV2RGB_COEFF21      TD_DISP_YUV2RGB_COEFF21;
    volatile U_TD_DISP_YUV2RGB_COEFF22      TD_DISP_YUV2RGB_COEFF22;
    volatile U_TD_DISP_YUV2RGB_COEFF23      TD_DISP_YUV2RGB_COEFF23;
    volatile unsigned int                   reserved15[4];
    volatile U_TD_DISP_MIX_ALP0             TD_DISP_MIX_ALP0;
    volatile U_TD_DISP_MIX_ALP1             TD_DISP_MIX_ALP1;
    volatile U_TD_DISP_MIX_SEL              TD_DISP_MIX_SEL;
    volatile U_TD_DISP_BACK_GROUD           TD_DISP_BACK_GROUD;
    volatile unsigned int                   reserved16[3];
    volatile U_TD_DISP_IRQ0                 TD_DISP_IRQ0;
    volatile U_TD_DISP_IRQ1                 TD_DISP_IRQ1;
    volatile U_TD_DISP_IRQ2                 TD_DISP_IRQ2;
    volatile U_TD_DISP_IRQ                  TD_DISP_IRQ;
    volatile unsigned int                   reserved17[4];
    volatile U_TD_WB_DMA_WR_EN              TD_WB_DMA_WR_EN;
    volatile U_TD_WB_MODE                   TD_WB_MODE;
    volatile U_TD_WB_PIXEL_FORMAT_OUT       TD_WB_PIXEL_FORMAT_OUT;
    volatile U_TD_WB_FRM_BASE_OUT_ADDR0_Y   TD_WB_FRM_BASE_OUT_ADDR0_Y;
    volatile U_TD_WB_FRM_BASE_OUT_ADDR1_Y   TD_WB_FRM_BASE_OUT_ADDR1_Y;
    volatile U_TD_WB_FRM_BASE_OUT_ADDR0_UV  TD_WB_FRM_BASE_OUT_ADDR0_UV;
    volatile U_TD_WB_FRM_BASE_OUT_ADDR1_UV  TD_WB_FRM_BASE_OUT_ADDR1_UV;
    volatile U_TD_WB_HSTRIDE_OUT_Y          TD_WB_HSTRIDE_OUT_Y;
    volatile U_TD_WB_HSTRIDE_OUT_UV         TD_WB_HSTRIDE_OUT_UV;
    volatile U_TD_WB_FRM_BUF_SIZE_OUT       TD_WB_FRM_BUF_SIZE_OUT;
    volatile U_TD_WB_V_SIZE_ACTIVE_OUT      TD_WB_V_SIZE_ACTIVE_OUT;
    volatile U_TD_WB_H_SIZE_ACTIVE_OUT      TD_WB_H_SIZE_ACTIVE_OUT;
    volatile unsigned int                   reserved18[4];
    volatile U_TD_WB_CH0_DMA_MODE           TD_WB_CH0_DMA_MODE;
    volatile U_TD_WB_CH0_ERR_UNIT           TD_WB_CH0_ERR_UNIT;
    volatile U_TD_WB_CH0_ERR_TH             TD_WB_CH0_ERR_TH;
    volatile U_TD_WB_CH0_INFO_CLR           TD_WB_CH0_INFO_CLR;
    volatile U_TD_WB_CH0_RST_REQ            TD_WB_CH0_RST_REQ;
    volatile U_TD_WB_CH1_DMA_MODE           TD_WB_CH1_DMA_MODE;
    volatile U_TD_WB_CH1_ERR_UNIT           TD_WB_CH1_ERR_UNIT;
    volatile U_TD_WB_CH1_ERR_TH             TD_WB_CH1_ERR_TH;
    volatile U_TD_WB_CH1_INFO_CLR           TD_WB_CH1_INFO_CLR;
    volatile U_TD_WB_CH1_RST_REQ            TD_WB_CH1_RST_REQ;
    volatile unsigned int                   reserved20[7];
    volatile U_TD_WB_Y_OUT_IDLE             TD_WB_Y_OUT_IDLE;
    volatile U_TD_WB_UV_OUT_IDLE            TD_WB_UV_OUT_IDLE;
    volatile U_TD_WB_Y_OUT_INT              TD_WB_Y_OUT_INT;
    volatile U_TD_WB_UV_OUT_INT             TD_WB_UV_OUT_INT;
    volatile U_TD_WB_Y_OUT_FUNC0            TD_WB_Y_OUT_FUNC0;
    volatile U_TD_WB_Y_OUT_FUNC1            TD_WB_Y_OUT_FUNC1;
    volatile U_TD_WB_UV_OUT_FUNC0           TD_WB_UV_OUT_FUNC0;
    volatile U_TD_WB_UV_OUT_FUNC1           TD_WB_UV_OUT_FUNC1;    
}S_TD_MIX_SCALER_REGS_TYPE;

/*
*rotation
*/
int TD_CORE_DRV_SET_RotCmd(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotCtl(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotTimeOut(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotImageSizeActive(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrYSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrUSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrVSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrYDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrUDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotBaseAddrVDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotStrideY(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotStrideU(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_RotStrideV(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData);
/*
*mix/scaler
*/
int TD_CORE_DRV_SET_SoftRstCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DmaSWCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0Line0BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0Line1BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0Line2BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0Line3BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer4BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0XZoneCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0YZoneCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0XCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0YCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer4XCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer4YCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispHsyncCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispVsyncCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispEnable(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*Layer0
*/
int TD_CORE_DRV_SET_Layer0Ctl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ScaleBlenth(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ImgInDatMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0BAddr0Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0BAddr0UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ImgInPixSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ImgOutPixSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ImgInStride(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0ImgInOffset(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0VScaleStep(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0VScaleST(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0HScaleStep(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Layer0HScaleST(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_BaseMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*osd0
*/
int TD_CORE_DRV_SET_Osd0Info(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Osd0Size(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Osd0VLUAddr0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Osd0ALPAddr0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Osd0DmaCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_Osd0Stride(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*RGB2YUV
*/
int TD_CORE_DRV_SET_OsdRGB2YUVCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff00(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff01(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff02(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff03(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff10(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff11(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff12(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff13(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff20(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff21(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff22(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_OsdRGB2YUVCoeff23(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*YUV2RGB
*/
int TD_CORE_DRV_SET_DispYUV2RGBCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff00(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff01(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff02(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff03(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff10(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff11(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff12(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff13(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff20(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff21(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff22(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispYUV2RGBCoeff23(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*mix
*/
int TD_CORE_DRV_SET_DispMixALP0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispMixALP1(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispMixSel(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispBackGroud(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*int
*/
int TD_CORE_DRV_SET_DispIRQ0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispIRQ1(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispIRQ2(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_DispIRQ(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*WB
*/
int TD_CORE_DRV_SET_WBDmaWrEn(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBPixelFormatOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBFrmBaseOutAddr0Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBFrmBaseOutAddr1Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBFrmBaseOutAddr0UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBFrmBaseOutAddr1UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBHStrideOutY(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBHStrideOutUV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBFrmBufSizeOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBVSizeActiveOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBHSizeActiveOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*Ch0
*/
int TD_CORE_DRV_SET_WBCh0DmaMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh0ErrUnit(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh0ErrTH(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh0InfoClr(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh0RstReq(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
/*
*Ch1
*/
int TD_CORE_DRV_SET_WBCh1DmaMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh1ErrUnit(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh1ErrTH(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh1InfoClr(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
int TD_CORE_DRV_SET_WBCh1RstReq(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData);
//
unsigned int TD_CORE_DRV_GET_DispEnable(S_TD_MIX_SCALER_REGS_TYPE *pstRegs);
//DEBUG
int TD_CORE_DRV_GET_RotationRegsVal(S_TD_ROTATION_REGS_TYPE *pstRegs);
int TD_CORE_DRV_GET_MixScalerRegsVal(S_TD_MIX_SCALER_REGS_TYPE *pstRegs);
#endif /*_TD_CORE_REG_DEF_H_*/
