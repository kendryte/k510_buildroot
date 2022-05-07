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

#ifndef _VO_CORE_REG_DEF_H_
#define _VO_CORE_REG_DEF_H_

typedef union { /* VO_SOFT_RST_CTL */

    struct 
    {
        unsigned int disp                        : 1;
        unsigned int vo                          : 1;
        unsigned int apb                         : 1;
        unsigned int core                        : 1;
        unsigned int reserved0                   : 28;
    } bits;    
    unsigned int u32; 
} U_VO_SOFT_RST_CTL;

typedef union { /* VO_LoadCtl */

    struct 
    {
        unsigned int regready                    : 1;
        unsigned int reserved0                   : 3;
        unsigned int regfirstload                : 1;
        unsigned int reserved1                   : 27;
    } bits;    
    unsigned int u32; 
} U_VO_LOAD_CTL;

typedef union { /* VO_DmaSwCtl */

    struct 
    {
        unsigned int reqwr                       : 1;
        unsigned int reserved0                   : 3;
        unsigned int reqrd                       : 1;
        unsigned int reserved1                   : 27;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_SW_CTL;

typedef union { /* VO_DmaRdCtlOut */

    struct 
    {
        unsigned int wrst                        : 3;
        unsigned int wrrstrdy                    : 1;
        unsigned int rdst                        : 3;
        unsigned int rdrstrdy                    : 1;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_RD_CTL_OUT;

typedef union { /* VO_DmaARB */
    struct 
    {
        unsigned int wr_arb_mode                 : 1;
        unsigned int rd_arb_mode                 : 1;
        unsigned int reserved0                   : 30;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_ARB_MODE;

typedef union { /* VO_DMA_WEIGHT_RD0 */
    struct 
    {
        unsigned int chl0                        : 8;
        unsigned int chl1                        : 8;
        unsigned int chl2                        : 8;
        unsigned int chl3                        : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_WEIGHT_RD0;

typedef union { /* VO_DMA_WEIGHT_RD1 */
    struct 
    {
        unsigned int chl4                        : 8;
        unsigned int chl5                        : 8;
        unsigned int chl6                        : 8;
        unsigned int chl7                        : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_WEIGHT_RD1;

typedef union { /* VO_DMA_WEIGHT_RD2 */
    struct 
    {
        unsigned int chl8                        : 8;
        unsigned int chl9                        : 8;
        unsigned int chl10                       : 8;
        unsigned int chl11                       : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_WEIGHT_RD2;

typedef union { /* VO_DMA_WEIGHT_RD3 */
    struct 
    {
        unsigned int chl12                       : 8;
        unsigned int chl13                       : 8;
        unsigned int chl14                       : 8;
        unsigned int chl15                       : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DMA_WEIGHT_RD3;

typedef union { /* VO_DMA_PRIORITY_RD_0 */
    struct     
    {
        unsigned int chl0                       : 4;
        unsigned int chl1                       : 4;
        unsigned int chl2                       : 4;
        unsigned int chl3                       : 4;
        unsigned int chl4                       : 4;
        unsigned int chl5                       : 4;
        unsigned int chl6                       : 4;
        unsigned int chl7                       : 4;        
    } bits;    
    unsigned int u32; 
} U_VO_DMA_PRIORITY_RD_0;

typedef union { /* VO_DMA_PRIORITY_RD_1 */
    struct     
    {
        unsigned int chl8                       : 4;
        unsigned int chl9                       : 4;
        unsigned int chl10                      : 4;
        unsigned int chl11                      : 4;
        unsigned int chl12                      : 4;
        unsigned int chl13                      : 4;
        unsigned int chl14                      : 4;
        unsigned int chl15                      : 4;        
    } bits;    
    unsigned int u32; 
} U_VO_DMA_PRIORITY_RD_1;

typedef union { /* VO_DMA_ID_RD_0 */
    struct     
    {
        unsigned int chl0                       : 4;
        unsigned int chl1                       : 4;
        unsigned int chl2                       : 4;
        unsigned int chl3                       : 4;
        unsigned int chl4                       : 4;
        unsigned int chl5                       : 4;
        unsigned int chl6                       : 4;
        unsigned int chl7                       : 4;        
    } bits;    
    unsigned int u32; 
} U_VO_DMA_ID_RD_0;

typedef union { /* VO_DMA_ID_RD_1 */
    struct     
    {
        unsigned int chl8                       : 4;
        unsigned int chl9                       : 4;
        unsigned int chl10                      : 4;
        unsigned int chl11                      : 4;
        unsigned int chl12                      : 4;
        unsigned int chl13                      : 4;
        unsigned int chl14                      : 4;
        unsigned int chl15                      : 4;        
    } bits;    
    unsigned int u32; 
} U_VO_DMA_ID_RD_1;

typedef union { /* VO_Layer0Line0BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_LINE0_BD_CTL;

typedef union { /* VO_Layer0Line1BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_LINE1_BD_CTL;

typedef union { /* VO_Layer0Line2BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_LINE2_BD_CTL;

typedef union { /* VO_Layer0Line3BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_LINE3_BD_CTL;

typedef union { /* VO_Layer1BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_BD_CTL;

typedef union { /* VO_Layer2BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_BD_CTL;

typedef union { /* VO_Layer3BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_BD_CTL;

typedef union { /* VO_Layer4BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER4_BD_CTL;

typedef union { /* VO_Layer5BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER5_BD_CTL;

typedef union { /* VO_Layer6BdCtl */

    struct 
    {
        unsigned int limiten                     : 1;
        unsigned int reserved0                   : 7;
        unsigned int outstand                    : 5;
        unsigned int reserved1                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER6_BD_CTL;

typedef union { /* VO_DispXZone */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_XZONE_CTL;

typedef union { /* VO_DispYZone */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YZONE_CTL;

typedef union { /* VO_Layer0XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_XCTL;

typedef union { /* VO_Layer0YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_YCTL;

typedef union { /* VO_Layer1XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_XCTL;

typedef union { /* VO_Layer1YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_YCTL;

typedef union { /* VO_Layer2XCtl */

    struct
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_XCTL;

typedef union { /* VO_Layer2YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_YCTL;

typedef union { /* VO_Layer3XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_XCTL;

typedef union { /* VO_Layer3YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_YCTL;

typedef union { /* VO_Layer4XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER4_XCTL;

typedef union { /* VO_Layer4YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER4_YCTL;

typedef union { /* VO_Layer5XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER5_XCTL;

typedef union { /* VO_Layer5YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER5_YCTL;

typedef union { /* VO_Layer6XCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER6_XCTL;

typedef union { /* VO_Layer6YCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER6_YCTL;

typedef union { /* VO_DispHsyncCtl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_HSYNC_CTL;

typedef union { /* VO_DispHsync1Ctl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_HSYNC1_CTL;

typedef union { /* VO_DispVsync1Ctl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_VSYNC1_CTL;

typedef union { /* VO_DispHsync2Ctl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_HSYNC2_CTL;

typedef union { /* VO_DispVsync2Ctl */

    struct 
    {
        unsigned int start                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int stop                        : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_VSYNC2_CTL;

typedef union { /* VO_DispCtl */

    struct 
    {
        unsigned int vcntbit0                    : 1;
        unsigned int reserved0                   : 7;
        unsigned int secndfoffset                : 2;
        unsigned int reserved1                   : 6;
        unsigned int framesyncdly                : 8;
        unsigned int reserved2                   : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_CTL;

typedef union { /* VO_DispEnable */

    struct 
    {
        unsigned int layer0en                    : 1;
        unsigned int layer1en                    : 1;
        unsigned int layer2en                    : 1;
        unsigned int layer3en                    : 1;
        unsigned int layer4en                    : 1;
        unsigned int layer5en                    : 1;
        unsigned int layer6en                    : 1;
        unsigned int disable                     : 1;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_ENABLE;

typedef union { /* VO_DispSize */

    struct 
    {
        unsigned int hsize                       : 13;  //hsize ?
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;  //vsize ?
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_SIZE;

typedef union { /* VO_Layer0Ctl */

    struct {
        unsigned int enable                      : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_CTL;

typedef union { /* VO_Layer0ScaleBlenth */

    struct 
    {
        unsigned int blen                        : 4;
        unsigned int reserved0                   : 28;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_SCALE_BLENTH;

typedef union { /* VO_Layer0ImgInDatMode */

    struct 
    {
        unsigned int datmode                     : 5;
        unsigned int reserved0                   : 3;
        unsigned int endiany                     : 2;
        unsigned int reserved1                   : 2;
        unsigned int endianuv                    : 3;
        unsigned int reserved2                   : 9;
        unsigned int swi                         : 1;
        unsigned int reserved3                   : 7;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_IN_DAT_MODE;

typedef union { /* VO_LAYER0_BADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_BADDR0_Y;

typedef union { /* VO_LAYER0_BADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_BADDR0_UV;

typedef union { /* VO_LAYER0_BADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_BADDR1_Y;

typedef union { /* VO_LAYER0_BADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_BADDR1_UV;

typedef union { /* VO_Layer0ImgInPixSzie */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_IN_PIX_SZIE;

typedef union { /* VO_Layer0ImgOutPixSzie */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_OUT_PIX_SZIE;

typedef union { /* VO_Layer0ImgInStride */

    struct
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_IN_STRIDE;

typedef union { /* VO_Layer0ImgInOffset */

    struct 
    {
        unsigned int hoffset                     : 13;
        unsigned int reserved0                   : 3;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_IN_OFFSET;

typedef union { /* VO_Layer0VscaleStep */

    struct 
    {
        unsigned int pstep                       : 8;
        unsigned int reserved0                   : 8;
        unsigned int dstep                       : 16;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_VSCALE_STEP;

typedef union { /* VO_Layer0VscaleSt */

    struct 
    {
        unsigned int pstep                       : 16;
        unsigned int reserved0                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_VSCALE_ST;

typedef union { /* VO_Layer0HscaleStep */

    struct 
    {
        unsigned int pstep                       : 8;
        unsigned int reserved0                   : 8;
        unsigned int dstep                       : 16;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_HSCALE_STEP;

typedef union { /* VO_Layer0HscaleSt */

    struct 
    {
        unsigned int pstep                       : 16;
        unsigned int reserved0                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_HSCALE_ST;

typedef union { /* VO_Layer0BaseMode */

    struct 
    {
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
} U_VO_LAYER0_BASE_MODE;

typedef union { /*VO_LAYER0_MFBD_DATA_ADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_ADDR0_Y;

typedef union { /*VO_LAYER0_MFBD_HEAD_ADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_ADDR0_Y;

typedef union { /*VO_LAYER0_MFBD_DATA_STRIDE0_Y */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_STRIDE0_Y;

typedef union { /*VO_LAYER0_MFBD_HEAD_STRIDE0_Y */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_STRIDE0_Y;

typedef union { /*VO_LAYER0_MFBD_DATA_ADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_ADDR1_Y;

typedef union { /*VO_LAYER0_MFBD_HEAD_ADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_ADDR1_Y;

typedef union { /*VO_LAYER0_MFBD_DATA_STRIDE1_Y */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_STRIDE1_Y;

typedef union { /*VO_LAYER0_MFBD_HEAD_STRIDE1_Y */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_STRIDE1_Y;

typedef union { /*VO_LAYER0_MFBD_DATA_ADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_ADDR0_UV;

typedef union { /*VO_LAYER0_MFBD_HEAD_ADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_ADDR0_UV;

typedef union { /*VO_LAYER0_MFBD_DATA_STRIDE0_UV */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_STRIDE0_UV;

typedef union { /*VO_LAYER0_MFBD_HEAD_STRIDE0_UV */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_STRIDE0_UV;

typedef union { /*VO_LAYER0_MFBD_DATA_ADDR1_UV */

    struct {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_ADDR1_UV;

typedef union { /*VO_LAYER0_MFBD_HEAD_ADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_ADDR1_UV;

typedef union { /* VO_Layer1Ctl */

    struct 
    {
        unsigned int enable                      : 1;
        unsigned int reserved0                   : 3;
        unsigned int yuv422en                    : 1;
        unsigned int reserved1                   : 3;
        unsigned int yuv420en                    : 1;
        unsigned int reserved2                   : 3;
        unsigned int endiany                     : 2;
        unsigned int reserved3                   : 2;
        unsigned int endianuv                    : 3;
        unsigned int reserved4                   : 9;
        unsigned int uvswap                      : 1;
        unsigned int reserved5                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_CTL;

typedef union { /*VO_LAYER1_IMG_IN_BADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_BADDR0_Y;

typedef union { /*VO_LAYER1_IMG_IN_BADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_BADDR0_UV;

typedef union { /*VO_LAYER1_IMG_IN_BADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_BADDR1_Y;

typedef union { /*VO_LAYER1_IMG_IN_BADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_BADDR1_UV;

typedef union { /* VO_Layer1ImgInOffset */

    struct 
    {
        unsigned int hoffset                     : 13;
        unsigned int reserved0                   : 3;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_OFFSET;

typedef union { /* VO_Layer1ImgInBlenth */

    struct 
    {
        unsigned int blen                        : 4;
        unsigned int reserved0                   : 12;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_BLENTH;

typedef union { /* VO_Layer1ImgInStride */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_STRIDE;

typedef union { /* VO_Layer1ImgInPixSize */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER1_IMG_IN_PIX_SIZE;

typedef union { /* VO_Layer1BaseMode */

    struct 
    {
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
} U_VO_LAYER1_ADDR_SEL_MODE;

typedef union { /*VO_LAYER0_MFBD_DATA_STRIDE1_UV */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_DATA_STRIDE1_UV;

typedef union { /*VO_LAYER0_MFBD_HEAD_STRIDE1_UV */

    struct 
    {
        unsigned int stride                       : 15;
        unsigned int reserved0                    : 17;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD_HEAD_STRIDE1_UV;

typedef union { /* VO_Layer0Mfbd */

    struct {
        unsigned int en                          : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_MFBD;
/*
*LAYER2
*/
typedef union { /* VO_Layer2Ctl */

    struct 
    {
        unsigned int enable                      : 1;
        unsigned int reserved0                   : 3;
        unsigned int yuv422en                    : 1;
        unsigned int reserved1                   : 3;
        unsigned int yuv420en                    : 1;
        unsigned int reserved2                   : 3;
        unsigned int endiany                     : 2;
        unsigned int reserved3                   : 2;
        unsigned int endianuv                    : 3;
        unsigned int reserved4                   : 9;
        unsigned int uvswap                      : 1;
        unsigned int reserved5                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_CTL;

typedef union { /*VO_LAYER2_IMG_IN_BADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_BADDR0_Y;

typedef union { /*VO_LAYER2_IMG_IN_BADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_BADDR0_UV;

typedef union { /*VO_LAYER2_IMG_IN_BADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_BADDR1_Y;

typedef union { /*VO_LAYER2_IMG_IN_BADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_BADDR1_UV;

typedef union { /* VO_Layer2ImgInOffset */

    struct 
    {
        unsigned int hoffset                     : 13;
        unsigned int reserved0                   : 3;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_OFFSET;

typedef union { /* VO_Layer2ImgInBlenth */

    struct 
    {
        unsigned int blen                        : 4;
        unsigned int reserved0                   : 12;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_BLENTH;

typedef union { /* VO_Layer2ImgInStride */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_STRIDE;

typedef union { /* VO_Layer2ImgInPixSize */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER2_IMG_IN_PIX_SIZE;

typedef union { /* VO_Layer2BaseMode */

    struct 
    {
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
} U_VO_LAYER2_ADDR_SEL_MODE;
/*
*LAYER3
*/
typedef union { /* VO_Layer3Ctl */

    struct 
    {
        unsigned int enable                      : 1;
        unsigned int reserved0                   : 3;
        unsigned int yuv422en                    : 1;
        unsigned int reserved1                   : 3;
        unsigned int yuv420en                    : 1;
        unsigned int reserved2                   : 3;
        unsigned int endiany                     : 2;
        unsigned int reserved3                   : 2;
        unsigned int endianuv                    : 3;
        unsigned int reserved4                   : 9;
        unsigned int uvswap                      : 1;
        unsigned int reserved5                   : 3;        
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_CTL;

typedef union { /*VO_LAYER3_IMG_IN_BADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_BADDR0_Y;

typedef union { /*VO_LAYER3_IMG_IN_BADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_BADDR0_UV;

typedef union { /*VO_LAYER3_IMG_IN_BADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_BADDR1_Y;

typedef union { /*VO_LAYER3_IMG_IN_BADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_BADDR1_UV;

typedef union { /* VO_Layer3ImgInOffset */

    struct 
    {
        unsigned int hoffset                     : 13;
        unsigned int reserved0                   : 3;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_OFFSET;

typedef union { /* VO_Layer3ImgInBlenth */

    struct 
    {
        unsigned int blen                        : 4;
        unsigned int reserved0                   : 12;
        unsigned int voffset                     : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_BLENTH;

typedef union { /* VO_Layer3ImgInStride */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_STRIDE;

typedef union { /* VO_Layer3ImgInPixSize */

    struct 
    {
        unsigned int hsize                       : 13;
        unsigned int reserved0                   : 3;
        unsigned int vsize                       : 13;
        unsigned int reserved1                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER3_IMG_IN_PIX_SIZE;

typedef union { /* VO_Layer3BaseMode */

    struct 
    {
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
} U_VO_LAYER3_ADDR_SEL_MODE;
/*
*OSD0 INFO
*/
typedef union { /* VO_Osd0Info */

    struct 
    {
        unsigned int osdtype                     : 4;
        unsigned int alphatpye                   : 3;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD0_INFO;

typedef union { /* VO_Osd0Size */

    struct 
    {
        unsigned int width                       : 16;
        unsigned int height                      : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD0_SIZE;

typedef union { /*VO_DISP_OSD0_VLU_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD0_VLU_ADDR0;

typedef union { /*VO_DISP_OSD0_ALP_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD0_ALP_ADDR0;

typedef union { /*VO_DISP_OSD0_VLU_ADDR1 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD0_VLU_ADDR1;

typedef union { /*VO_DISP_OSD0_ALP_ADDR1 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD0_ALP_ADDR1;

typedef union { /* VO_Osd0DMACtl */

    struct 
    {
        unsigned int dmarequestlen               : 4;
        unsigned int dmamap                      : 2;
        unsigned int rgbrev                      : 1;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD0_DMA_CTL;

typedef union { /* VO_Osd0Stride */

    struct 
    {
        unsigned int osdstride                   : 16;
        unsigned int alpstride                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD0_STRIDE;

typedef union { /* VO_OSD0_ADDR_SEL_MODE */

    struct 
    {
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
} U_VO_OSD0_ADDR_SEL_MODE;
/*
*OSD1 info
*/
typedef union { /* VO_Osd1Info */
    struct 
    {
        unsigned int osdtype                     : 4;
        unsigned int alphatpye                   : 3;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD1_INFO;

typedef union { /* VO_Osd1Size */

    struct 
    {
        unsigned int width                       : 16;
        unsigned int height                      : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD1_SIZE;

typedef union { /*VO_DISP_OSD1_VLU_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD1_VLU_ADDR0;

typedef union { /*VO_DISP_OSD1_ALP_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD1_ALP_ADDR0;

typedef union { /*VO_DISP_OSD1_VLU_ADDR1 */

    struct 
    {  
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD1_VLU_ADDR1;

typedef union { /*VO_DISP_OSD1_ALP_ADDR1 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD1_ALP_ADDR1;

typedef union { /* VO_Osd1DMACtl */

    struct 
    {
        unsigned int dmarequestlen               : 4;
        unsigned int dmamap                      : 2;
        unsigned int rgbrev                      : 1;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD1_DMA_CTL;

typedef union { /* VO_Osd1Stride */

    struct 
    {
        unsigned int osdstride                   : 16;
        unsigned int alpstride                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD1_STRIDE;

typedef union { /* U_VO_0SD1_ADDR_SEL_MODE */

    struct 
    {
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
} U_VO_0SD1_ADDR_SEL_MODE;
/*
*OSD2 info
*/
typedef union { /* VO_Osd2Info */

    struct 
    {
        unsigned int osdtype                     : 4;
        unsigned int alphatpye                   : 3;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD2_INFO;

typedef union { /* VO_Osd2Size */

    struct 
    {
        unsigned int width                       : 16;
        unsigned int height                      : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD2_SIZE;

typedef union { /*VO_DISP_OSD2_VLU_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD2_VLU_ADDR0;

typedef union { /*VO_DISP_OSD2_ALP_ADDR0 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD2_ALP_ADDR0;

typedef union { /*VO_DISP_OSD2_VLU_ADDR1 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD2_VLU_ADDR1;

typedef union { /*VO_DISP_OSD2_ALP_ADDR1 */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_OSD2_ALP_ADDR1;

typedef union { /* VO_Osd2DMACtl */
    struct 
    {
        unsigned int dmarequestlen               : 4;
        unsigned int dmamap                      : 2;
        unsigned int rgbrev                      : 1;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_OSD2_DMA_CTL;

typedef union { /* VO_Osd2Stride */

    struct 
    {
        unsigned int osdstride                   : 16;
        unsigned int alpstride                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_OSD2_STRIDE;

typedef union { /* VO_OSD2_ADDR_SEL_MODE */

    struct 
    {
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
} U_VO_OSD2_ADDR_SEL_MODE;
/*
*OSD YUV2RGB
*/
typedef union { /* VO_OsdRGB2YUVCtl */

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
} U_VO_OSD_RGB2YUV_CTL;

typedef union { /* VO_OsdRGB2YUVCoeff00 */

    struct 
    {
        unsigned int c00                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF00;

typedef union { /* VO_OsdRGB2YUVCoeff01 */

    struct 
    {
        unsigned int c01                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF01;

typedef union { /* VO_OsdRGB2YUVCoeff02 */

    struct 
    {
        unsigned int c02                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF02;

typedef union { /* VO_OsdRGB2YUVCoeff03 */

    struct 
    {
        unsigned int c03                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF03;

typedef union { /* VO_OsdRGB2YUVCoeff10 */

    struct 
    {
        unsigned int c10                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF10;

typedef union { /* VO_OsdRGB2YUVCoeff11 */

    struct 
    {
        unsigned int c11                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF11;

typedef union { /* VO_OsdRGB2YUVCoeff12 */

    struct 
    {
        unsigned int c12                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF12;

typedef union { /* VO_OsdRGB2YUVCoeff13 */

    struct 
    {
        unsigned int c13                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF13;

typedef union { /* VO_OsdRGB2YUVCoeff20 */

    struct 
    {
        unsigned int c20                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF20;

typedef union { /* VO_OsdRGB2YUVCoeff21 */

    struct 
    {
        unsigned int c21                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF21;

typedef union { /* VO_OsdRGB2YUVCoeff22 */

    struct 
    {
        unsigned int c22                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF22;

typedef union { /* VO_OsdRGB2YUVCoeff23 */

    struct 
    {
        unsigned int c23                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_OSD_RGB2YUV_COEFF23;
/*
*OSD YUV2RGB
*/
typedef union { /* VO_DispYUV2RGBCtl */

    struct 
    {
        unsigned int en                          : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_CTL;

typedef union { /* VO_DispYUV2RGBCoeff00 */

    struct 
    {
        unsigned int c00                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF00;

typedef union { /* VO_DispYUV2RGBCoeff01 */

    struct 
    {
        unsigned int c01                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF01;

typedef union { /* VO_DispYUV2RGBCoeff02 */

    struct 
    {
        unsigned int c02                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF02;

typedef union { /* VO_DispYUV2RGBCoeff03 */

    struct 
    {
        unsigned int c03                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF03;

typedef union { /* VO_DispYUV2RGBCoeff10 */

    struct 
    {
        unsigned int c10                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF10;

typedef union { /* VO_DispYUV2RGBCoeff11 */

    struct 
    {
        unsigned int c11                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF11;

typedef union { /* VO_DispYUV2RGBCoeff12 */

    struct 
    {
        unsigned int c12                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF12;

typedef union { /* VO_DispYUV2RGBCoeff13 */

    struct 
    {
        unsigned int c13                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF13;

typedef union { /* VO_DispYUV2RGBCoeff20 */

    struct 
    {
        unsigned int c20                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF20;

typedef union { /* VO_DispYUV2RGBCoeff21 */

    struct 
    {
        unsigned int c21                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF21;

typedef union { /* VO_DispYUV2RGBCoeff22 */

    struct {
        unsigned int c22                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF22;

typedef union { /* VO_DispYUV2RGBCoeff23 */

    struct 
    {
        unsigned int c23                         : 12;
        unsigned int reserved0                   : 20;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_YUV2RGB_COEFF23;
/*
*MIX
*/
typedef union { /* VO_DispMixEn */

    struct 
    {
        unsigned int layer0glben                 : 1;
        unsigned int layer1glben                 : 1;
        unsigned int layer2glben                 : 1;
        unsigned int layer3glben                 : 1;
        unsigned int layer4glben                 : 1;
        unsigned int layer5glben                 : 1;
        unsigned int layer6glben                 : 1;
        unsigned int reserved0                   : 25;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_MIX_EN;

typedef union { /* VO_DispMixAlp0 */

    struct 
    {
        unsigned int layer0glbalp                : 8;
        unsigned int layer1glbalp                : 8;
        unsigned int layer2glbalp                : 8;
        unsigned int layer3glbalp                : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_MIX_ALP0;

typedef union { /* VO_DispMixAlp1 */

    struct {
        unsigned int layer4glbalp                : 8;
        unsigned int layer5glbalp                : 8;
        unsigned int layer6glbalp                : 8;
        unsigned int reserved0                   : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_MIX_ALP1;

typedef union { /* VO_DispMixSel */

    struct 
    {
        unsigned int layer0sel                   : 3;
        unsigned int reserved0                   : 1;
        unsigned int layer1sel                   : 3;
        unsigned int reserved1                   : 1;
        unsigned int layer2sel                   : 3;
        unsigned int reserved2                   : 1;
        unsigned int layer3sel                   : 3;
        unsigned int reserved3                   : 1;
        unsigned int layer4sel                   : 3;
        unsigned int reserved4                   : 1;
        unsigned int layer5sel                   : 3;
        unsigned int reserved5                   : 1;
        unsigned int layer6sel                   : 3;
        unsigned int reserved6                   : 5;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_MIX_SEL;

typedef union { /* VO_DispBackGroud */

    struct 
    {
        unsigned int y                           : 8;
        unsigned int u                           : 8;
        unsigned int v                           : 8;
        unsigned int reserved0                   : 8;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_BACK_GROUD;

typedef union { /* VO_DispDithCtl */

    struct 
    {
        unsigned int en                          : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_DITH_CTL;

typedef union { /* VO_DispClutCtl */

    struct {
        unsigned int en                          : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_CLUT_CTL;

typedef union { /* VO_DISP_IRQ0_CTL */

    struct 
    {
        unsigned int reserved0                   : 20;
        unsigned int en                          : 1;
        unsigned int reserved1                   : 11;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_IRQ0_CTL;

typedef union { /* VO_DISP_IRQ1_CTL */

    struct 
    {
        unsigned int vpos                        : 13;
        unsigned int reserved0                   : 7;
        unsigned int en                          : 1;
        unsigned int reserved1                   : 11;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_IRQ1_CTL;

typedef union { /* VO_DISP_IRQ2_CTL */

    struct 
    {
        unsigned int reserved0                   : 20;
        unsigned int en                          : 1;
        unsigned int reserved1                   : 11;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_IRQ2_CTL;

typedef union { /* VO_DispIRQ */

    struct 
    {
        unsigned int irq0                        : 1;
        unsigned int irq1                        : 1;
        unsigned int irq2                        : 1;
        unsigned int reserved0                   : 13;
        unsigned int underrun_cnt                : 8;
        unsigned int reserved1                   : 4;
        unsigned int addr_flag                   : 1;
        unsigned int reserved2                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_DISP_IRQ;
/*
*WB 
*/
typedef union { /* WB_DmaCh */

    struct 
    {
        unsigned int wben                        : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_DMA_CH_EN;

typedef union { /* WB_Mode */

    struct 
    {
        unsigned int reserved0                   : 2;
        unsigned int inchmode                    : 1;
        unsigned int reserved1                   : 29;
    } bits;    
    unsigned int u32; 
} U_VO_WB_MODE;

typedef union { /* VO_WB_PIXEL_FORMAT_OUT */

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
} U_VO_WB_PIXEL_FORMAT_OUT;

typedef union { /*VO_WB_FRM_BASE_OUT_ADDR0_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_WB_FRM_BASE_OUT_ADDR0_Y;

typedef union { /*VO_WB_FRM_BASE_OUT_ADDR0_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_WB_FRM_BASE_OUT_ADDR0_UV;

typedef union { /*VO_WB_FRM_BASE_OUT_ADDR1_Y */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_WB_FRM_BASE_OUT_ADDR1_Y;

typedef union { /*VO_WB_FRM_BASE_OUT_ADDR1_UV */

    struct 
    {
        unsigned int addr                        : 32;
    } bits;    
    unsigned int u32; 
} U_VO_WB_FRM_BASE_OUT_ADDR1_UV;

typedef union { /* WB_HstrideY */

    struct 
    {
        unsigned int out                         : 13;
        unsigned int reserved0                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_WB_HSTRIDE_Y;

typedef union { /* WB_HstrideUV */

    struct 
    {
        unsigned int out                         : 13;
        unsigned int reserved0                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_WB_HSTRIDE_UV;

typedef union { /* WB_BufSize */

    struct 
    {
        unsigned int loop                        : 16;
        unsigned int reserved0                   : 16;
    } bits;    
    unsigned int u32; 
} U_VO_WB_BUF_SIZE_OUT;

typedef union { /* WB_Vsize */

    struct 
    {
        unsigned int active                      : 13;
        unsigned int reserved0                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_WB_V_SIZE_ACTIVE_OUT;

typedef union { /* WB_Hsize */

    struct 
    {
        unsigned int active                      : 13;
        unsigned int reserved0                   : 19;
    } bits;    
    unsigned int u32; 
} U_VO_WB_H_SIZE_ACTIVE_OUT;
/*
*WB CH0
*/
typedef union { /* WB_WbCh0Dma */

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
} U_VO_WB_CH0_DMA_MODE;

typedef union { /* WB_WbCh0ErrUnit */

    struct 
    {
        unsigned int unit                        : 8;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH0_ERR_UNIT;

typedef union { /* WB_WbCh0ErrTh */

    struct 
    {
        unsigned int threshold                   : 8;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH0_ERR_TH;

typedef union { /* VO_WB_CH0_INFO_CLR */

    struct 
    {
        unsigned int frmcntclear                 : 1;
        unsigned int fifoerrclear                : 1;
        unsigned int maxbw                       : 1;
        unsigned int totalbw                     : 1;
        unsigned int reserved0                   : 28;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH0_INFO_CLR;

typedef union { /* WB_WbCh0Rst */

    struct 
    {
        unsigned int request                     : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH0_RST_REQ;
/*
*WB CH1
*/
typedef union { /* WB_WbCh1Dma */

    struct 
    {
        unsigned int otnum                       : 4;
        unsigned int reserved0                   : 8;
        unsigned int blen                        : 1;
        unsigned int reserved1                   : 1;
        unsigned int datamode                    : 1;
        unsigned int swap                        : 1;
        unsigned int reserved2                   : 12;
        unsigned int errdetecten                 : 1;
        unsigned int reserved3                   : 3;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH1_DMA_MODE;

typedef union { /* WB_WbCh1ErrUnit */

    struct 
    {
        unsigned int unit                        : 8;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH1_ERR_UNIT;

typedef union { /* WB_WbCh1ErrTh */

    struct 
    {
        unsigned int threshold                   : 8;
        unsigned int reserved0                   : 24;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH1_ERR_TH;

typedef union { /* WB_WbCh1Info */

    struct 
    {
        unsigned int frmcntclear                 : 1;
        unsigned int fifoerrclear                : 1;
        unsigned int maxbw                       : 1;
        unsigned int totalbw                     : 1;
        unsigned int reserved0                   : 28;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH1_INFO_CLR;

typedef union { /* WB_WbCh1Rst */

    struct 
    {
        unsigned int request                     : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_CH1_RST_REQ;

typedef union { /* WB_WbYOutIdle */

    struct 
    {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_Y_OUT_IDLE;

typedef union { /* WB_WbUVOutIdle */

    struct 
    {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_UV_OUT_IDLE;

typedef union { /* WB_WbYOutInt */

    struct 
    {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_Y_OUT_INT;

typedef union { /* WB_WbUVOutInt */

    struct 
    {
        unsigned int status                      : 1;
        unsigned int reserved0                   : 31;
    } bits;    
    unsigned int u32; 
} U_VO_WB_UV_OUT_INT;

typedef union { /* WB_WbYOutFunc0 */

    struct 
    {
        unsigned int frmcnt                      : 16;
        unsigned int buffererrcnt                : 16;
    } bits;    
    unsigned int u32; 
} U_VO_WB_Y_OUT_FUNC0;

typedef union { /* WB_WbYOutFunc1 */

    struct 
    {
        unsigned int maxbd                       : 8;
        unsigned int totalbd                     : 18;
        unsigned int reserved0                   : 4;
        unsigned int frmbasesel                  : 1;
        unsigned int dmabusy                     : 1;
    } bits;    
    unsigned int u32; 
} U_VO_WB_Y_OUT_FUNC1;

typedef union { /* WB_WbUVOutFunc0 */

    struct 
    {
        unsigned int frmcnt                      : 16;
        unsigned int buffererrcnt                : 16;
    } bits;    
    unsigned int u32; 
} U_VO_WB_UV_OUT_FUNC0;

typedef union { /* WB_WbUVOutFunc1 */

    struct 
    {
        unsigned int maxbd                       : 8;
        unsigned int totalbd                     : 18;
        unsigned int reserved0                   : 4;
        unsigned int frmbasesel                  : 1;
        unsigned int dmabusy                     : 1;
    } bits;    
    unsigned int u32; 
} U_VO_WB_UV_OUT_FUNC1;

typedef struct 
{
    volatile U_VO_SOFT_RST_CTL                 VO_SOFT_RST_CTL               ;
    volatile U_VO_LOAD_CTL                     VO_LOAD_CTL                   ;
    volatile U_VO_DMA_SW_CTL                   VO_DMA_SW_CTL                 ;
    volatile U_VO_DMA_RD_CTL_OUT               VO_DMA_RD_CTL_OUT             ;
    volatile U_VO_DMA_ARB_MODE                 VO_DMA_ARB_MODE               ;
    volatile unsigned int                      reserved0[4]                  ;
    volatile U_VO_DMA_WEIGHT_RD0               VO_DMA_WEIGHT_RD0             ;
    volatile U_VO_DMA_WEIGHT_RD1               VO_DMA_WEIGHT_RD1             ;
    volatile U_VO_DMA_WEIGHT_RD2               VO_DMA_WEIGHT_RD2             ;
    volatile U_VO_DMA_WEIGHT_RD3               VO_DMA_WEIGHT_RD3             ;
    volatile unsigned int                      reserved1[2]                  ;
    volatile U_VO_DMA_PRIORITY_RD_0            VO_DMA_PRIORITY_RD_0          ;
    volatile U_VO_DMA_PRIORITY_RD_1            VO_DMA_PRIORITY_RD_1          ;
    volatile unsigned int                      reserved2[2]                  ;
    volatile U_VO_DMA_ID_RD_0                  VO_DMA_ID_RD_0                ;
    volatile U_VO_DMA_ID_RD_1                  VO_DMA_ID_RD_1                ;
    volatile unsigned int                      reserved3[11]                   ;
    volatile U_VO_LAYER0_LINE0_BD_CTL          VO_LAYER0_LINE0_BD_CTL        ;
    volatile U_VO_LAYER0_LINE1_BD_CTL          VO_LAYER0_LINE1_BD_CTL        ;
    volatile U_VO_LAYER0_LINE2_BD_CTL          VO_LAYER0_LINE2_BD_CTL        ;
    volatile U_VO_LAYER0_LINE3_BD_CTL          VO_LAYER0_LINE3_BD_CTL        ;
    volatile U_VO_LAYER1_BD_CTL                VO_LAYER1_BD_CTL              ;
    volatile U_VO_LAYER2_BD_CTL                VO_LAYER2_BD_CTL              ;
    volatile U_VO_LAYER3_BD_CTL                VO_LAYER3_BD_CTL              ;
    volatile U_VO_LAYER4_BD_CTL                VO_LAYER4_BD_CTL              ;
    volatile U_VO_LAYER5_BD_CTL                VO_LAYER5_BD_CTL              ;
    volatile U_VO_LAYER6_BD_CTL                VO_LAYER6_BD_CTL              ;
    volatile unsigned int                      reserved4[6]                    ;
    volatile U_VO_DISP_XZONE_CTL               VO_DISP_XZONE_CTL             ;
    volatile U_VO_DISP_YZONE_CTL               VO_DISP_YZONE_CTL             ;
    volatile U_VO_LAYER0_XCTL                  VO_LAYER0_XCTL                ;
    volatile U_VO_LAYER0_YCTL                  VO_LAYER0_YCTL                ;
    volatile U_VO_LAYER1_XCTL                  VO_LAYER1_XCTL                ;
    volatile U_VO_LAYER1_YCTL                  VO_LAYER1_YCTL                ;
    volatile U_VO_LAYER2_XCTL                  VO_LAYER2_XCTL                ;
    volatile U_VO_LAYER2_YCTL                  VO_LAYER2_YCTL                ;
    volatile U_VO_LAYER3_XCTL                  VO_LAYER3_XCTL                ;
    volatile U_VO_LAYER3_YCTL                  VO_LAYER3_YCTL                ;
    volatile U_VO_LAYER4_XCTL                  VO_LAYER4_XCTL                ;
    volatile U_VO_LAYER4_YCTL                  VO_LAYER4_YCTL                ;
    volatile U_VO_LAYER5_XCTL                  VO_LAYER5_XCTL                ;
    volatile U_VO_LAYER5_YCTL                  VO_LAYER5_YCTL                ;
    volatile U_VO_LAYER6_XCTL                  VO_LAYER6_XCTL                ;
    volatile U_VO_LAYER6_YCTL                  VO_LAYER6_YCTL                ;
    volatile U_VO_DISP_HSYNC_CTL               VO_DISP_HSYNC_CTL             ;
    volatile U_VO_DISP_HSYNC1_CTL              VO_DISP_HSYNC1_CTL            ;
    volatile U_VO_DISP_VSYNC1_CTL              VO_DISP_VSYNC1_CTL            ;
    volatile U_VO_DISP_HSYNC2_CTL              VO_DISP_HSYNC2_CTL            ;
    volatile U_VO_DISP_VSYNC2_CTL              VO_DISP_VSYNC2_CTL            ;
    volatile U_VO_DISP_CTL                     VO_DISP_CTL                   ;
    volatile U_VO_DISP_ENABLE                  VO_DISP_ENABLE                ;
    volatile U_VO_DISP_SIZE                    VO_DISP_SIZE                  ;
    volatile unsigned int                      reserved5[8]                  ;
    volatile U_VO_LAYER0_CTL                   VO_LAYER0_CTL                 ;
    volatile U_VO_LAYER0_SCALE_BLENTH          VO_LAYER0_SCALE_BLENTH        ;
    volatile U_VO_LAYER0_IMG_IN_DAT_MODE       VO_LAYER0_IMG_IN_DAT_MODE     ;
    volatile U_VO_LAYER0_BADDR0_Y              VO_LAYER0_BADDR0_Y            ;
    volatile U_VO_LAYER0_BADDR0_UV             VO_LAYER0_BADDR0_UV           ;
    volatile U_VO_LAYER0_BADDR1_Y              VO_LAYER0_BADDR1_Y            ;
    volatile U_VO_LAYER0_BADDR1_UV             VO_LAYER0_BADDR1_UV           ;
    volatile U_VO_LAYER0_IMG_IN_PIX_SZIE       VO_LAYER0_IMG_IN_PIX_SZIE     ;
    volatile U_VO_LAYER0_IMG_OUT_PIX_SZIE      VO_LAYER0_IMG_OUT_PIX_SZIE    ;
    volatile U_VO_LAYER0_IMG_IN_STRIDE         VO_LAYER0_IMG_IN_STRIDE       ;
    volatile unsigned int                      reserved6                     ;    
    volatile U_VO_LAYER0_IMG_IN_OFFSET         VO_LAYER0_IMG_IN_OFFSET       ;
    volatile unsigned int                      reserved7                     ;
    volatile U_VO_LAYER0_VSCALE_STEP           VO_LAYER0_VSCALE_STEP         ;
    volatile U_VO_LAYER0_VSCALE_ST             VO_LAYER0_VSCALE_ST           ;
    volatile U_VO_LAYER0_HSCALE_STEP           VO_LAYER0_HSCALE_STEP         ;
    volatile U_VO_LAYER0_HSCALE_ST             VO_LAYER0_HSCALE_ST           ;
    volatile U_VO_LAYER0_BASE_MODE             VO_LAYER0_BASE_MODE           ;
    volatile U_VO_LAYER0_MFBD_DATA_ADDR0_Y     VO_LAYER0_MFBD_DATA_ADDR0_Y   ;
    volatile U_VO_LAYER0_MFBD_HEAD_ADDR0_Y     VO_LAYER0_MFBD_HEAD_ADDR0_Y   ;
    volatile U_VO_LAYER0_MFBD_DATA_STRIDE0_Y   VO_LAYER0_MFBD_DATA_STRIDE0_Y ;
    volatile U_VO_LAYER0_MFBD_HEAD_STRIDE0_Y   VO_LAYER0_MFBD_HEAD_STRIDE0_Y ;
    volatile U_VO_LAYER0_MFBD_DATA_ADDR1_Y     VO_LAYER0_MFBD_DATA_ADDR1_Y   ;
    volatile U_VO_LAYER0_MFBD_HEAD_ADDR1_Y     VO_LAYER0_MFBD_HEAD_ADDR1_Y   ;
    volatile U_VO_LAYER0_MFBD_DATA_STRIDE1_Y   VO_LAYER0_MFBD_DATA_STRIDE1_Y ;
    volatile U_VO_LAYER0_MFBD_HEAD_STRIDE1_Y   VO_LAYER0_MFBD_HEAD_STRIDE1_Y ;
    volatile U_VO_LAYER0_MFBD_DATA_ADDR0_UV    VO_LAYER0_MFBD_DATA_ADDR0_UV  ;
    volatile U_VO_LAYER0_MFBD_HEAD_ADDR0_UV    VO_LAYER0_MFBD_HEAD_ADDR0_UV  ;
    volatile U_VO_LAYER0_MFBD_DATA_STRIDE0_UV  VO_LAYER0_MFBD_DATA_STRIDE0_UV;
    volatile U_VO_LAYER0_MFBD_HEAD_STRIDE0_UV  VO_LAYER0_MFBD_HEAD_STRIDE0_UV;
    volatile U_VO_LAYER0_MFBD_DATA_ADDR1_UV    VO_LAYER0_MFBD_DATA_ADDR1_UV  ;
    volatile U_VO_LAYER0_MFBD_HEAD_ADDR1_UV    VO_LAYER0_MFBD_HEAD_ADDR1_UV  ;
    volatile U_VO_LAYER1_CTL                   VO_LAYER1_CTL                 ;
    volatile U_VO_LAYER1_IMG_IN_BADDR0_Y       VO_LAYER1_IMG_IN_BADDR0_Y     ;
    volatile U_VO_LAYER1_IMG_IN_BADDR0_UV      VO_LAYER1_IMG_IN_BADDR0_UV    ;
    volatile U_VO_LAYER1_IMG_IN_BADDR1_Y       VO_LAYER1_IMG_IN_BADDR1_Y     ;
    volatile U_VO_LAYER1_IMG_IN_BADDR1_UV      VO_LAYER1_IMG_IN_BADDR1_UV    ;
    volatile U_VO_LAYER1_IMG_IN_OFFSET         VO_LAYER1_IMG_IN_OFFSET       ;
    volatile U_VO_LAYER1_IMG_IN_BLENTH         VO_LAYER1_IMG_IN_BLENTH       ;
    volatile U_VO_LAYER1_IMG_IN_STRIDE         VO_LAYER1_IMG_IN_STRIDE       ;
    volatile U_VO_LAYER1_IMG_IN_PIX_SIZE       VO_LAYER1_IMG_IN_PIX_SIZE     ;
    volatile U_VO_LAYER1_ADDR_SEL_MODE         VO_LAYER1_ADDR_SEL_MODE       ;
    volatile U_VO_LAYER0_MFBD_DATA_STRIDE1_UV  VO_LAYER0_MFBD_DATA_STRIDE1_UV;
    volatile U_VO_LAYER0_MFBD_HEAD_STRIDE1_UV  VO_LAYER0_MFBD_HEAD_STRIDE1_UV;
    volatile U_VO_LAYER0_MFBD                  VO_LAYER0_MFBD                ;
    volatile unsigned int                      reserved8[3]                  ;
    volatile U_VO_LAYER2_CTL                   VO_LAYER2_CTL                 ;
    volatile U_VO_LAYER2_IMG_IN_BADDR0_Y       VO_LAYER2_IMG_IN_BADDR0_Y     ;
    volatile U_VO_LAYER2_IMG_IN_BADDR0_UV      VO_LAYER2_IMG_IN_BADDR0_UV    ;
    volatile U_VO_LAYER2_IMG_IN_BADDR1_Y       VO_LAYER2_IMG_IN_BADDR1_Y     ;
    volatile U_VO_LAYER2_IMG_IN_BADDR1_UV      VO_LAYER2_IMG_IN_BADDR1_UV    ;
    volatile U_VO_LAYER2_IMG_IN_OFFSET         VO_LAYER2_IMG_IN_OFFSET       ;
    volatile U_VO_LAYER2_IMG_IN_BLENTH         VO_LAYER2_IMG_IN_BLENTH       ;
    volatile U_VO_LAYER2_IMG_IN_STRIDE         VO_LAYER2_IMG_IN_STRIDE       ;
    volatile U_VO_LAYER2_IMG_IN_PIX_SIZE       VO_LAYER2_IMG_IN_PIX_SIZE     ;
    volatile U_VO_LAYER2_ADDR_SEL_MODE         VO_LAYER2_ADDR_SEL_MODE       ;
    volatile unsigned int                      reserved9[6]                  ;
    volatile U_VO_LAYER3_CTL                   VO_LAYER3_CTL                 ;
    volatile U_VO_LAYER3_IMG_IN_BADDR0_Y       VO_LAYER3_IMG_IN_BADDR0_Y     ;
    volatile U_VO_LAYER3_IMG_IN_BADDR0_UV      VO_LAYER3_IMG_IN_BADDR0_UV    ;
    volatile U_VO_LAYER3_IMG_IN_BADDR1_Y       VO_LAYER3_IMG_IN_BADDR1_Y     ;
    volatile U_VO_LAYER3_IMG_IN_BADDR1_UV      VO_LAYER3_IMG_IN_BADDR1_UV    ;
    volatile U_VO_LAYER3_IMG_IN_OFFSET         VO_LAYER3_IMG_IN_OFFSET       ;
    volatile U_VO_LAYER3_IMG_IN_BLENTH         VO_LAYER3_IMG_IN_BLENTH       ;
    volatile U_VO_LAYER3_IMG_IN_STRIDE         VO_LAYER3_IMG_IN_STRIDE       ;
    volatile U_VO_LAYER3_IMG_IN_PIX_SIZE       VO_LAYER3_IMG_IN_PIX_SIZE     ;
    volatile U_VO_LAYER3_ADDR_SEL_MODE         VO_LAYER3_ADDR_SEL_MODE       ;
    volatile unsigned int                      reserved10[6]                 ;
    volatile U_VO_OSD0_INFO                    VO_OSD0_INFO                  ;
    volatile U_VO_OSD0_SIZE                    VO_OSD0_SIZE                  ;
    volatile U_VO_DISP_OSD0_VLU_ADDR0          VO_DISP_OSD0_VLU_ADDR0        ;
    volatile U_VO_DISP_OSD0_ALP_ADDR0          VO_DISP_OSD0_ALP_ADDR0        ;
    volatile U_VO_DISP_OSD0_VLU_ADDR1          VO_DISP_OSD0_VLU_ADDR1        ;
    volatile U_VO_DISP_OSD0_ALP_ADDR1          VO_DISP_OSD0_ALP_ADDR1        ;
    volatile U_VO_OSD0_DMA_CTL                 VO_OSD0_DMA_CTL               ;
    volatile U_VO_OSD0_STRIDE                  VO_OSD0_STRIDE                ;
    volatile U_VO_OSD0_ADDR_SEL_MODE           VO_OSD0_ADDR_SEL_MODE         ;
    volatile unsigned int                      reserved11[7]                 ;
    volatile U_VO_OSD1_INFO                    VO_OSD1_INFO                  ;
    volatile U_VO_OSD1_SIZE                    VO_OSD1_SIZE                  ;
    volatile U_VO_DISP_OSD1_VLU_ADDR0          VO_DISP_OSD1_VLU_ADDR0        ;
    volatile U_VO_DISP_OSD1_ALP_ADDR0          VO_DISP_OSD1_ALP_ADDR0        ;
    volatile U_VO_DISP_OSD1_VLU_ADDR1          VO_DISP_OSD1_VLU_ADDR1        ;
    volatile U_VO_DISP_OSD1_ALP_ADDR1          VO_DISP_OSD1_ALP_ADDR1        ;
    volatile U_VO_OSD1_DMA_CTL                 VO_OSD1_DMA_CTL               ;
    volatile U_VO_OSD1_STRIDE                  VO_OSD1_STRIDE                ;
    volatile U_VO_0SD1_ADDR_SEL_MODE           VO_OSD1_ADDR_SEL_MODE         ;
    volatile unsigned int                      reserved12[7]                 ;
    volatile U_VO_OSD2_INFO                    VO_OSD2_INFO                  ;
    volatile U_VO_OSD2_SIZE                    VO_OSD2_SIZE                  ;
    volatile U_VO_DISP_OSD2_VLU_ADDR0          VO_DISP_OSD2_VLU_ADDR0        ;
    volatile U_VO_DISP_OSD2_ALP_ADDR0          VO_DISP_OSD2_ALP_ADDR0        ;
    volatile U_VO_DISP_OSD2_VLU_ADDR1          VO_DISP_OSD2_VLU_ADDR1        ;
    volatile U_VO_DISP_OSD2_ALP_ADDR1          VO_DISP_OSD2_ALP_ADDR1        ;
    volatile U_VO_OSD2_DMA_CTL                 VO_OSD2_DMA_CTL               ;
    volatile U_VO_OSD2_STRIDE                  VO_OSD2_STRIDE                ;
    volatile U_VO_OSD2_ADDR_SEL_MODE           VO_OSD2_ADDR_SEL_MODE         ;
    volatile unsigned int                      reserved13[7]                   ;
    volatile U_VO_OSD_RGB2YUV_CTL              VO_OSD_RGB2YUV_CTL            ;
    volatile U_VO_OSD_RGB2YUV_COEFF00          VO_OSD_RGB2YUV_COEFF00        ;
    volatile U_VO_OSD_RGB2YUV_COEFF01          VO_OSD_RGB2YUV_COEFF01        ;
    volatile U_VO_OSD_RGB2YUV_COEFF02          VO_OSD_RGB2YUV_COEFF02        ;
    volatile U_VO_OSD_RGB2YUV_COEFF03          VO_OSD_RGB2YUV_COEFF03        ;
    volatile U_VO_OSD_RGB2YUV_COEFF10          VO_OSD_RGB2YUV_COEFF10        ;
    volatile U_VO_OSD_RGB2YUV_COEFF11          VO_OSD_RGB2YUV_COEFF11        ;
    volatile U_VO_OSD_RGB2YUV_COEFF12          VO_OSD_RGB2YUV_COEFF12        ;
    volatile U_VO_OSD_RGB2YUV_COEFF13          VO_OSD_RGB2YUV_COEFF13        ;
    volatile U_VO_OSD_RGB2YUV_COEFF20          VO_OSD_RGB2YUV_COEFF20        ;
    volatile U_VO_OSD_RGB2YUV_COEFF21          VO_OSD_RGB2YUV_COEFF21        ;
    volatile U_VO_OSD_RGB2YUV_COEFF22          VO_OSD_RGB2YUV_COEFF22        ;
    volatile U_VO_OSD_RGB2YUV_COEFF23          VO_OSD_RGB2YUV_COEFF23        ;
    volatile unsigned int                      reserved14[3]                 ;
    volatile U_VO_DISP_YUV2RGB_CTL             VO_DISP_YUV2RGB_CTL           ;
    volatile U_VO_DISP_YUV2RGB_COEFF00         VO_DISP_YUV2RGB_COEFF00       ;
    volatile U_VO_DISP_YUV2RGB_COEFF01         VO_DISP_YUV2RGB_COEFF01       ;
    volatile U_VO_DISP_YUV2RGB_COEFF02         VO_DISP_YUV2RGB_COEFF02       ;
    volatile U_VO_DISP_YUV2RGB_COEFF03         VO_DISP_YUV2RGB_COEFF03       ;
    volatile U_VO_DISP_YUV2RGB_COEFF10         VO_DISP_YUV2RGB_COEFF10       ;
    volatile U_VO_DISP_YUV2RGB_COEFF11         VO_DISP_YUV2RGB_COEFF11       ;
    volatile U_VO_DISP_YUV2RGB_COEFF12         VO_DISP_YUV2RGB_COEFF12       ;
    volatile U_VO_DISP_YUV2RGB_COEFF13         VO_DISP_YUV2RGB_COEFF13       ;
    volatile U_VO_DISP_YUV2RGB_COEFF20         VO_DISP_YUV2RGB_COEFF20       ;
    volatile U_VO_DISP_YUV2RGB_COEFF21         VO_DISP_YUV2RGB_COEFF21       ;
    volatile U_VO_DISP_YUV2RGB_COEFF22         VO_DISP_YUV2RGB_COEFF22       ;
    volatile U_VO_DISP_YUV2RGB_COEFF23         VO_DISP_YUV2RGB_COEFF23       ;
    volatile unsigned int                      reserved15[3]                 ;
    volatile U_VO_DISP_MIX_EN                  VO_DISP_MIX_EN                ;
    volatile U_VO_DISP_MIX_ALP0                VO_DISP_MIX_ALP0              ;
    volatile U_VO_DISP_MIX_ALP1                VO_DISP_MIX_ALP1              ;
    volatile U_VO_DISP_MIX_SEL                 VO_DISP_MIX_SEL               ;
    volatile U_VO_DISP_BACK_GROUD              VO_DISP_BACK_GROUD            ;
    volatile U_VO_DISP_DITH_CTL                VO_DISP_DITH_CTL              ;
    volatile U_VO_DISP_CLUT_CTL                VO_DISP_CLUT_CTL              ;
    volatile unsigned int                      reserved16                      ;
    volatile U_VO_DISP_IRQ0_CTL                VO_DISP_IRQ0_CTL              ;
    volatile U_VO_DISP_IRQ1_CTL                VO_DISP_IRQ1_CTL              ;
    volatile U_VO_DISP_IRQ2_CTL                VO_DISP_IRQ2_CTL              ;
    volatile U_VO_DISP_IRQ                     VO_DISP_IRQ                   ;
    volatile unsigned int                      reserved17[4]                 ;
    volatile U_VO_WB_DMA_CH_EN                 VO_WB_DMA_CH_EN               ;
    volatile U_VO_WB_MODE                      VO_WB_MODE                ;
    volatile U_VO_WB_PIXEL_FORMAT_OUT          VO_WB_PIXEL_FORMAT_OUT        ;      
    volatile U_VO_WB_FRM_BASE_OUT_ADDR0_Y      VO_WB_FRM_BASE_OUT_ADDR0_Y    ;
    volatile U_VO_WB_FRM_BASE_OUT_ADDR0_UV     VO_WB_FRM_BASE_OUT_ADDR0_UV   ;
    volatile U_VO_WB_FRM_BASE_OUT_ADDR1_Y      VO_WB_FRM_BASE_OUT_ADDR1_Y    ;
    volatile U_VO_WB_FRM_BASE_OUT_ADDR1_UV     VO_WB_FRM_BASE_OUT_ADDR1_UV   ;
    volatile U_VO_WB_HSTRIDE_Y                 VO_WB_HSTRIDE_Y               ;
    volatile U_VO_WB_HSTRIDE_UV                VO_WB_HSTRIDE_UV              ;
    volatile U_VO_WB_BUF_SIZE_OUT              VO_WB_BUF_SIZE_OUT            ;
    volatile U_VO_WB_V_SIZE_ACTIVE_OUT         VO_WB_V_SIZE_ACTIVE_OUT       ;
    volatile U_VO_WB_H_SIZE_ACTIVE_OUT         VO_WB_H_SIZE_ACTIVE_OUT       ;
    volatile unsigned int                      reserved18[4]                 ;
    volatile U_VO_WB_CH0_DMA_MODE              VO_WB_CH0_DMA_MODE            ;
    volatile U_VO_WB_CH0_ERR_UNIT              VO_WB_CH0_ERR_UNIT            ;
    volatile U_VO_WB_CH0_ERR_TH                VO_WB_CH0_ERR_TH              ;
    volatile U_VO_WB_CH0_INFO_CLR              VO_WB_CH0_INFO_CLR            ;  
    volatile U_VO_WB_CH0_RST_REQ               VO_WB_CH0_RST_REQ             ;
    volatile unsigned int                      reserved19[4]                 ;
    volatile U_VO_WB_CH1_DMA_MODE              VO_WB_CH1_DMA_MODE            ;
    volatile U_VO_WB_CH1_ERR_UNIT              VO_WB_CH1_ERR_UNIT            ;
    volatile U_VO_WB_CH1_ERR_TH                VO_WB_CH1_ERR_TH              ;
    volatile U_VO_WB_CH1_INFO_CLR              VO_WB_CH1_INFO_CLR            ;
    volatile U_VO_WB_CH1_RST_REQ               VO_WB_CH1_RST_REQ             ;
    volatile unsigned int                      reserved20[3]                 ;
    volatile U_VO_WB_Y_OUT_IDLE                VO_WB_Y_OUT_IDLE              ;
    volatile U_VO_WB_UV_OUT_IDLE               VO_WB_UV_OUT_IDLE             ;
    volatile U_VO_WB_Y_OUT_INT                 VO_WB_Y_OUT_INT               ;
    volatile U_VO_WB_UV_OUT_INT                VO_WB_UV_OUT_INT              ;
    volatile U_VO_WB_Y_OUT_FUNC0               VO_WB_Y_OUT_FUNC0             ;
    volatile U_VO_WB_Y_OUT_FUNC1               VO_WB_Y_OUT_FUNC1             ;
    volatile U_VO_WB_UV_OUT_FUNC0              VO_WB_UV_OUT_FUNC0            ;
    volatile U_VO_WB_UV_OUT_FUNC1              VO_WB_UV_OUT_FUNC1            ;
} S_VO_CORE_REGS_TYPE;

int VO_CORE_DRV_SET_SoftRstCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaLoadCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int VO_CORE_DRV_GET_DmaLoadCtl(S_VO_CORE_REGS_TYPE *pstRegs);
int VO_CORE_DRV_SET_DmaSwCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaRdCtlOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaArbMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaWeightRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaWeightRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaWeightRD2(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaWeightRD3(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaPriorityRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaPriorityRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaIDRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DmaIDRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*core
*/
int VO_CORE_DRV_SET_Layer0Line0BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0Line1BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0Line2BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0Line3BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer4BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer5BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer6BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0XZoneCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0YZoneCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer4XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer4YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer5XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer5YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer6XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer6YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*DISP
*/
int VO_CORE_DRV_SET_DispHSyncCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispHSync1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispVSync1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispHSync2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispVSync2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int VO_CORE_DRV_GET_DispEnable(S_VO_CORE_REGS_TYPE *pstRegs);
int VO_CORE_DRV_SET_DispEnable(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*LAYER0
*/
int VO_CORE_DRV_SET_Layer0Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ScaleBLenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ImgInDatMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0BAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0BAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0BAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0BAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ImgInPix(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ImgOutPix(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*layer0 scaler
*/
int VO_CORE_DRV_SET_Layer0VScaleStep(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0VScaleSt(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0HScaleStep(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0HScaleSt(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0BaseMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*MFBD
*/
int VO_CORE_DRV_SET_Layer0MFBDDataAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataStride0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadStride0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataStride1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadStride1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataStride0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadStride0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDDataStride1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBDHeadStride1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer0MFBD(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*LAYER1
*/
int VO_CORE_DRV_SET_Layer1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer1AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*LAYER2
*/
int VO_CORE_DRV_SET_Layer2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer2AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*LAYER3
*/
int VO_CORE_DRV_SET_Layer3Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_Layer3AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*osd0
*/
int VO_CORE_DRV_SET_OSD0Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD0Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD0VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD0AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD0VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD0AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD0DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD0Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD0AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*osd1
*/
int VO_CORE_DRV_SET_OSD1Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD1Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD1VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD1AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD1VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD1AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD1DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD1Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD1AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*osd2
*/
int VO_CORE_DRV_SET_OSD2Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD2Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD2VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD2AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD2VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispOSD2AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD2DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD2Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSD2AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*RGB2YUV
*/
int VO_CORE_DRV_SET_OSDRGB2YUVCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int VO_CORE_DRV_GET_OSDRGB2YUVCtl(S_VO_CORE_REGS_TYPE *pstRegs);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff00(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff01(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff02(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff03(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff10(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff11(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff12(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff13(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff20(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff21(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff22(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_OSDRGB2YUVCoeff23(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*YUV2RGB
*/
int VO_CORE_DRV_SET_DispYUV2RGBCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff00(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff01(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff02(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff03(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff10(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff11(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff12(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff13(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff20(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff21(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff22(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispYUV2RGBCoeff23(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*MIX
*/
int VO_CORE_DRV_SET_DispMixEn(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispMixALP0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispMixALP1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispMixSel(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispBackGroud(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispDithCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispClutCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispIrq0Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispIrq1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispIrq2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_DispIrq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
*WB
*/
int VO_CORE_DRV_SET_WbDmaCHEn(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbDmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbPixelFormatOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbFrmBaseOutAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbFrmBaseOutAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbFrmBaseOutAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbFrmBaseOutAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbHStrideY(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbHStrideUV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbBufSizeOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbVSizeActiveOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbHSizeActiveOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
* WB CH0
*/
int VO_CORE_DRV_SET_WbCh0DmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh0ErrUnit(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh0ErrTh(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh0InfoClr(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh0RstReq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
/*
* WB CH1
*/
int VO_CORE_DRV_SET_WbCh1DmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh1ErrUnit(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh1ErrTh(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh1InfoClr(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int VO_CORE_DRV_SET_WbCh1RstReq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData);
//debug
int VO_CORE_DRV_GET_CoreRegsVal(S_VO_CORE_REGS_TYPE *pstRegs);
#endif /*_VO_CORE_REG_DEF_H_*/
