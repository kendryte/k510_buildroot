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
  File Name     : vo_core_reg.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _VO_CORE_REG_H_
#define _VO_CORE_REG_H_

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
        unsigned int mem_hsize                   : 32;
    } bits;    
    unsigned int u32; 
} U_VO_LAYER0_IMG_IN_MEM_HSIZE;

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

    struct 
    {
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

#define  VO_SOFT_RST_CTL                (0x0000)      
#define  VO_LOAD_CTL                    (0x0004)
#define  VO_DMA_SW_CTL                  (0x0008)
#define  VO_DMA_RD_CTL_OUT              (0x000C)
#define  VO_DMA_ARB_MODE                (0x0010)
#define  VO_DMA_WEIGHT_RD0              (0x0024)
#define  VO_DMA_WEIGHT_RD1              (0x0028)
#define  VO_DMA_WEIGHT_RD2              (0x002C)
#define  VO_DMA_WEIGHT_RD3              (0x0030)
#define  VO_DMA_PRIORITY_RD_0           (0x003C)
#define  VO_DMA_PRIORITY_RD_1           (0x0040)
#define  VO_DMA_ID_RD_0                 (0x004C)
#define  VO_DMA_ID_RD_1                 (0x0050)
//
#define  VO_LAYER0_LINE0_BD_CTL         (0x0080)
#define  VO_LAYER0_LINE1_BD_CTL         (0x0084)
#define  VO_LAYER0_LINE2_BD_CTL         (0x0088)
#define  VO_LAYER0_LINE3_BD_CTL         (0x008C)
#define  VO_LAYER1_BD_CTL               (0x0090)
#define  VO_LAYER2_BD_CTL               (0x0094)
#define  VO_LAYER3_BD_CTL               (0x0098)
#define  VO_LAYER4_BD_CTL               (0x009C)
#define  VO_LAYER5_BD_CTL               (0x00A0)
#define  VO_LAYER6_BD_CTL               (0x00A4)
//
#define  VO_DISP_XZONE_CTL              (0x00C0)
#define  VO_DISP_YZONE_CTL              (0x00C4)
#define  VO_LAYER0_XCTL                 (0x00C8)
#define  VO_LAYER0_YCTL                 (0x00CC)
#define  VO_LAYER1_XCTL                 (0x00D0)
#define  VO_LAYER1_YCTL                 (0x00D4)
#define  VO_LAYER2_XCTL                 (0x00D8)
#define  VO_LAYER2_YCTL                 (0x00DC)
#define  VO_LAYER3_XCTL                 (0x00E0)
#define  VO_LAYER3_YCTL                 (0x00E4)
#define  VO_LAYER4_XCTL                 (0x00E8)
#define  VO_LAYER4_YCTL                 (0x00EC)
#define  VO_LAYER5_XCTL                 (0x00F0)
#define  VO_LAYER5_YCTL                 (0x00F4)
#define  VO_LAYER6_XCTL                 (0x00F8)
#define  VO_LAYER6_YCTL                 (0x00FC)
#define  VO_DISP_HSYNC_CTL              (0x0100)
#define  VO_DISP_HSYNC1_CTL             (0x0104)
#define  VO_DISP_VSYNC1_CTL             (0x0108)
#define  VO_DISP_HSYNC2_CTL             (0x010C)
#define  VO_DISP_VSYNC2_CTL             (0x0110)
#define  VO_DISP_CTL                    (0x0114)
#define  VO_DISP_ENABLE                 (0x0118)
#define  VO_DISP_SIZE                   (0x011C)
//
#define  VO_LAYER0_CTL                  (0x0140)
#define  VO_LAYER0_SCALE_BLENTH         (0x0144)
#define  VO_LAYER0_IMG_IN_DAT_MODE      (0x0148)
#define  VO_LAYER0_BADDR0_Y             (0x014C)
#define  VO_LAYER0_BADDR0_UV            (0x0150)
#define  VO_LAYER0_BADDR1_Y             (0x0154)
#define  VO_LAYER0_BADDR1_UV            (0x0158)
#define  VO_LAYER0_IMG_IN_PIX_SZIE      (0x015C)
#define  VO_LAYER0_IMG_OUT_PIX_SZIE     (0x0160)
#define  VO_LAYER0_IMG_IN_STRIDE        (0x0164)
#define  VO_LAYER0_IMG_IN_MEM_HSIZE     (0x0168)
#define  VO_LAYER0_IMG_IN_OFFSET        (0x016C)
#define  reserved7                      (0x0170)
#define  VO_LAYER0_VSCALE_STEP          (0x0174)
#define  VO_LAYER0_VSCALE_ST            (0x0178)
#define  VO_LAYER0_HSCALE_STEP          (0x017C)
#define  VO_LAYER0_HSCALE_ST            (0x0180)
#define  VO_LAYER0_BASE_MODE            (0x0184)
#define  VO_LAYER0_MFBD_DATA_ADDR0_Y    (0x0188)
#define  VO_LAYER0_MFBD_HEAD_ADDR0_Y    (0x018C)
#define  VO_LAYER0_MFBD_DATA_STRIDE0_Y  (0x0190)
#define  VO_LAYER0_MFBD_HEAD_STRIDE0_Y  (0x0194)
#define  VO_LAYER0_MFBD_DATA_ADDR1_Y    (0x0198)
#define  VO_LAYER0_MFBD_HEAD_ADDR1_Y    (0x019C)
#define  VO_LAYER0_MFBD_DATA_STRIDE1_Y  (0x01A0)
#define  VO_LAYER0_MFBD_HEAD_STRIDE1_Y  (0x01A4)
#define  VO_LAYER0_MFBD_DATA_ADDR0_UV   (0x01A8)
#define  VO_LAYER0_MFBD_HEAD_ADDR0_UV   (0x01AC)
#define  VO_LAYER0_MFBD_DATA_STRIDE0_UV (0x01B0)
#define  VO_LAYER0_MFBD_HEAD_STRIDE0_UV (0x01B4)
#define  VO_LAYER0_MFBD_DATA_ADDR1_UV   (0x01B8)
#define  VO_LAYER0_MFBD_HEAD_ADDR1_UV   (0x01BC)
#define  VO_LAYER1_CTL                  (0x01C0)
#define  VO_LAYER1_IMG_IN_BADDR0_Y      (0x01C4)
#define  VO_LAYER1_IMG_IN_BADDR0_UV     (0x01C8)
#define  VO_LAYER1_IMG_IN_BADDR1_Y      (0x01CC)
#define  VO_LAYER1_IMG_IN_BADDR1_UV     (0x01D0)
#define  VO_LAYER1_IMG_IN_OFFSET        (0x01D4)
#define  VO_LAYER1_IMG_IN_BLENTH        (0x01D8)
#define  VO_LAYER1_IMG_IN_STRIDE        (0x01DC)
#define  VO_LAYER1_IMG_IN_PIX_SIZE      (0x01E0)
#define  VO_LAYER1_ADDR_SEL_MODE        (0x01E4)
#define  VO_LAYER0_MFBD_DATA_STRIDE1_UV (0x01E8)
#define  VO_LAYER0_MFBD_HEAD_STRIDE1_UV (0x01EC)
#define  VO_LAYER0_MFBD                 (0x01F0)
//
#define  VO_LAYER2_CTL                  (0x0200)
#define  VO_LAYER2_IMG_IN_BADDR0_Y      (0x0204)
#define  VO_LAYER2_IMG_IN_BADDR0_UV     (0x0208)
#define  VO_LAYER2_IMG_IN_BADDR1_Y      (0x020C)
#define  VO_LAYER2_IMG_IN_BADDR1_UV     (0x0210)
#define  VO_LAYER2_IMG_IN_OFFSET        (0x0214)
#define  VO_LAYER2_IMG_IN_BLENTH        (0x0218)
#define  VO_LAYER2_IMG_IN_STRIDE        (0x021C)
#define  VO_LAYER2_IMG_IN_PIX_SIZE      (0x0220)
#define  VO_LAYER2_ADDR_SEL_MODE        (0x0224)
//
#define  VO_LAYER3_CTL                  (0x0240)
#define  VO_LAYER3_IMG_IN_BADDR0_Y      (0x0244)
#define  VO_LAYER3_IMG_IN_BADDR0_UV     (0x0248)
#define  VO_LAYER3_IMG_IN_BADDR1_Y      (0x024C)
#define  VO_LAYER3_IMG_IN_BADDR1_UV     (0x0250)
#define  VO_LAYER3_IMG_IN_OFFSET        (0x0254)
#define  VO_LAYER3_IMG_IN_BLENTH        (0x0258)
#define  VO_LAYER3_IMG_IN_STRIDE        (0x025C)
#define  VO_LAYER3_IMG_IN_PIX_SIZE      (0x0260)
#define  VO_LAYER3_ADDR_SEL_MODE        (0x0264)
//
#define  VO_OSD0_INFO                   (0x0280)
#define  VO_OSD0_SIZE                   (0x0284)
#define  VO_DISP_OSD0_VLU_ADDR0         (0x0288)
#define  VO_DISP_OSD0_ALP_ADDR0         (0x028C)
#define  VO_DISP_OSD0_VLU_ADDR1         (0x0290)
#define  VO_DISP_OSD0_ALP_ADDR1         (0x0294)
#define  VO_OSD0_DMA_CTL                (0x0298)
#define  VO_OSD0_STRIDE                 (0x029C)
#define  VO_OSD0_ADDR_SEL_MODE          (0x02A0)
//
#define  VO_OSD1_INFO                   (0x02C0)
#define  VO_OSD1_SIZE                   (0x02C4)
#define  VO_DISP_OSD1_VLU_ADDR0         (0x02C8)
#define  VO_DISP_OSD1_ALP_ADDR0         (0x02CC)
#define  VO_DISP_OSD1_VLU_ADDR1         (0x02D0)
#define  VO_DISP_OSD1_ALP_ADDR1         (0x02D4)
#define  VO_OSD1_DMA_CTL                (0x02D8)
#define  VO_OSD1_STRIDE                 (0x02DC)
#define  VO_OSD1_ADDR_SEL_MODE          (0x02E0)
//
#define  VO_OSD2_INFO                   (0x0300)
#define  VO_OSD2_SIZE                   (0x0304)
#define  VO_DISP_OSD2_VLU_ADDR0         (0x0308)
#define  VO_DISP_OSD2_ALP_ADDR0         (0x030C)
#define  VO_DISP_OSD2_VLU_ADDR1         (0x0310)
#define  VO_DISP_OSD2_ALP_ADDR1         (0x0314)
#define  VO_OSD2_DMA_CTL                (0x0318)
#define  VO_OSD2_STRIDE                 (0x031C)
#define  VO_OSD2_ADDR_SEL_MODE          (0x0320)
//
#define  VO_OSD_RGB2YUV_CTL             (0x0340)
#define  VO_OSD_RGB2YUV_COEFF00         (0x0344)
#define  VO_OSD_RGB2YUV_COEFF01         (0x0348)
#define  VO_OSD_RGB2YUV_COEFF02         (0x034C)
#define  VO_OSD_RGB2YUV_COEFF03         (0x0350)
#define  VO_OSD_RGB2YUV_COEFF10         (0x0354)
#define  VO_OSD_RGB2YUV_COEFF11         (0x0358)
#define  VO_OSD_RGB2YUV_COEFF12         (0x035C)
#define  VO_OSD_RGB2YUV_COEFF13         (0x0360)
#define  VO_OSD_RGB2YUV_COEFF20         (0x0364)
#define  VO_OSD_RGB2YUV_COEFF21         (0x0368)
#define  VO_OSD_RGB2YUV_COEFF22         (0x036C)
#define  VO_OSD_RGB2YUV_COEFF23         (0x0370)
//
#define  VO_DISP_YUV2RGB_CTL            (0x0380)
#define  VO_DISP_YUV2RGB_COEFF00        (0x0384)
#define  VO_DISP_YUV2RGB_COEFF01        (0x0388)
#define  VO_DISP_YUV2RGB_COEFF02        (0x038C)
#define  VO_DISP_YUV2RGB_COEFF03        (0x0390)
#define  VO_DISP_YUV2RGB_COEFF10        (0x0394)
#define  VO_DISP_YUV2RGB_COEFF11        (0x0398)
#define  VO_DISP_YUV2RGB_COEFF12        (0x039C)
#define  VO_DISP_YUV2RGB_COEFF13        (0x03A0)
#define  VO_DISP_YUV2RGB_COEFF20        (0x03A4)
#define  VO_DISP_YUV2RGB_COEFF21        (0x03A8)
#define  VO_DISP_YUV2RGB_COEFF22        (0x03AC)
#define  VO_DISP_YUV2RGB_COEFF23        (0x03B0)
//
#define  VO_DISP_MIX_EN                 (0x03C0)
#define  VO_DISP_MIX_ALP0               (0x03C4)
#define  VO_DISP_MIX_ALP1               (0x03C8)
#define  VO_DISP_MIX_SEL                (0x03CC)
#define  VO_DISP_BACK_GROUD             (0x03D0)
#define  VO_DISP_DITH_CTL               (0x03D4)
#define  VO_DISP_CLUT_CTL               (0x03D8)
//
#define  VO_DISP_IRQ0_CTL               (0x03E0)
#define  VO_DISP_IRQ1_CTL               (0x03E4)
#define  VO_DISP_IRQ2_CTL               (0x03E8)
#define  VO_DISP_IRQ                    (0x03EC)
//
#define  VO_WB_DMA_CH_EN                (0x0400)
#define  VO_WB_MODE                     (0x0404)
#define  VO_WB_PIXEL_FORMAT_OUT         (0x0408)
#define  VO_WB_FRM_BASE_OUT_ADDR0_Y     (0x040C)
#define  VO_WB_FRM_BASE_OUT_ADDR0_UV    (0x0410)
#define  VO_WB_FRM_BASE_OUT_ADDR1_Y     (0x0414)
#define  VO_WB_FRM_BASE_OUT_ADDR1_UV    (0x0418)
#define  VO_WB_HSTRIDE_Y                (0x041C)
#define  VO_WB_HSTRIDE_UV               (0x0420)
#define  VO_WB_BUF_SIZE_OUT             (0x0424)
#define  VO_WB_V_SIZE_ACTIVE_OUT        (0x0428)
#define  VO_WB_H_SIZE_ACTIVE_OUT        (0x042C)
//
#define  VO_WB_CH0_DMA_MODE             (0x0440)
#define  VO_WB_CH0_ERR_UNIT             (0x0444)
#define  VO_WB_CH0_ERR_TH               (0x0448)
#define  VO_WB_CH0_INFO_CLR             (0x044C)
#define  VO_WB_CH0_RST_REQ              (0x0460)
#define  VO_WB_CH1_DMA_MODE             (0x0464)
#define  VO_WB_CH1_ERR_UNIT             (0x0468)
#define  VO_WB_CH1_ERR_TH               (0x046C)
#define  VO_WB_CH1_INFO_CLR             (0x0470)
#define  VO_WB_CH1_RST_REQ              (0x0474)
//
#define  VO_WB_Y_OUT_IDLE               (0x0484)
#define  VO_WB_UV_OUT_IDLE              (0x0488)
#define  VO_WB_Y_OUT_INT                (0x048C)
#define  VO_WB_UV_OUT_INT               (0x0490)
#define  VO_WB_Y_OUT_FUNC0              (0x0494)
#define  VO_WB_Y_OUT_FUNC1              (0x0498)
#define  VO_WB_UV_OUT_FUNC0             (0x049C)
#define  VO_WB_UV_OUT_FUNC1             (0x0500)

#endif /*_VO_CORE_REG_H_*/
