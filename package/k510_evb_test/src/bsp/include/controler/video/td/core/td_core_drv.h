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

#ifndef _TD_CORE_DRV_DEF_H_
#define _TD_CORE_DRV_DEF_H_

/*
* ROTATION
*/
typedef struct _TD_ROT_CTL_S
{
        unsigned int rotmode    ;
        unsigned int pixformat  ;
        unsigned int Inswap     ;
        unsigned int endianInEn ;
        unsigned int Outswap    ;
        unsigned int endianOutEn;
        unsigned int otmaxrd    ;
        unsigned int otmaxwr    ;
} TD_ROT_CTL_S;
 
typedef struct _TD_ROT_IMG_SIZE_S
{
        unsigned int hor;
        unsigned int ver;
} TD_ROT_IMG_SIZE_S;

typedef struct _TD_ROT_Y_S
{
	unsigned int y_src_addr;
        unsigned int src_stride;
	unsigned int y_des_addr;
        unsigned int des_stride;
} TD_ROT_Y_S;

typedef struct _TD_ROT_U_S
{
	unsigned int u_src_addr;
        unsigned int src_stride;
	unsigned int u_des_addr;
        unsigned int des_stride;
} TD_ROT_U_S;

typedef struct _TD_ROT_V_S
{
        unsigned int v_src_addr;
        unsigned int src_stride;      
        unsigned int v_des_addr;
        unsigned int des_stride;
} TD_ROT_V_S;

typedef struct _TD_ROT_ALL_CTL_S
{
        TD_ROT_CTL_S      rotCtl;
        TD_ROT_IMG_SIZE_S imgSize;
        TD_ROT_Y_S        yBufCtl;
        TD_ROT_U_S        uBufCtl;
        TD_ROT_V_S        vBufCtl;
	unsigned int      rot_framestart;
        unsigned int      timeout_val;
}TD_ROT_ALL_CTL_S;
/*
*Scaler/Mixer
*/
typedef struct _TD_SOFT_RST_CTL_S
{
        unsigned int mix ;
        unsigned int axi ;
        unsigned int apb ;
        unsigned int core;
} TD_SOFT_RST_CTL_S;

typedef struct _TD_DMA_SW_CTL_S
{
        unsigned int reqwr;
        unsigned int reqrd;
} TD_DMA_SW_CTL_S;

typedef struct _TD_BD_CTL_S
{
        unsigned int limiten  ;							   
        unsigned int outstand ;
} TD_BD_CTL_S;

typedef struct _TD_AREA_CTL_S
{
        unsigned int start;
        unsigned int stop ;
}TD_AREA_CTL_S;

typedef struct _TD_DISP_CTL_S
{
        unsigned int vcntbit0    ;
        unsigned int secndfoffset;
        unsigned int framesyncdly;
} TD_DISP_CTL_S;

typedef struct _TD_DISP_SIZE_S
{
        unsigned int hsize;
        unsigned int vsize;
} TD_DISP_SIZE_S;

typedef struct _TD_DISP_ALL_CTL_S
{
        unsigned int    framestart;
        TD_AREA_CTL_S   xZoneCtl;
        TD_AREA_CTL_S   yZoneCtl;
        TD_AREA_CTL_S   hSyncCtl;
        TD_AREA_CTL_S   vSyncCtl;
        TD_DISP_CTL_S   dispCtl;
        TD_DISP_SIZE_S  dispSize; 
}TD_DISP_ALL_CTL_S;

typedef struct _TD_LAYER0_IMG_IN_DAT_MODE_S
{
        unsigned int datmode ;
        unsigned int endiany ;
        unsigned int endianuv;
        unsigned int swapuv  ;
} TD_LAYER0_IMG_IN_DAT_MODE_S;

typedef struct _TD_LAYER0_SIZE_S
{
        unsigned int hsize;
        unsigned int vsize;
} TD_LAYER0_SIZE_S;

typedef struct _TD_LAYER0_SCALE_CTL_S
{
        unsigned int pstep;
        unsigned int dstep;
        unsigned int pstep_st;
} TD_LAYER0_SCALE_CTL_S;

typedef struct _TD_LAYER0_BASE_MODE_S
{
        unsigned int mode;
        unsigned int base0mask;
        unsigned int base1mask;
        unsigned int addrflag ;
} TD_LAYER0_BASE_MODE_S;

typedef struct _TD_LAYER0_CTL_S
{
        unsigned int                    ctlen;
        unsigned int                    layer0en    ;
        unsigned int                    layer0enhs  ;
        unsigned int                    layer0Wenhs ; 
        unsigned int                    layer0Scalerblen;
        TD_BD_CTL_S                     layer0Line0BDCtl;
        TD_BD_CTL_S                     layer0Line1BDCtl;
        TD_BD_CTL_S                     layer0Line2BDCtl;
        TD_BD_CTL_S                     layer0Line3BDCtl;  
        TD_AREA_CTL_S                   layer0XCtl;
        TD_AREA_CTL_S                   layer0YCtl;
        TD_LAYER0_IMG_IN_DAT_MODE_S     imgInDatMode;
        unsigned int                    y_addr;
        unsigned int                    uv_addr;
        TD_LAYER0_SIZE_S                imgInSize;
        TD_LAYER0_SIZE_S                imgOutSize;
        TD_LAYER0_SIZE_S                imgInStride;
        TD_LAYER0_SIZE_S                imgInOffset;
        TD_LAYER0_SCALE_CTL_S           vScaleCtl;
        TD_LAYER0_SCALE_CTL_S           hScaleCtl;
        TD_LAYER0_BASE_MODE_S           baseMode;
}TD_LAYER0_CTL_S;
/*
*LAYER4 (OSD0)
*/
typedef struct _TD_OSD0_CTL_S
{
        unsigned int osdtype  ;
        unsigned int alphatpye;
} TD_OSD0_CTL_S;

typedef struct _TD_OSD0_SIZE_S
{
        unsigned int width ;
        unsigned int height;
} TD_OSD0_SIZE_S;

typedef struct _TD_OSD0_DMA_CTL_S
{
        unsigned int dmarequestlen;
        unsigned int dmamap       ;
        unsigned int rgbrev       ;
} TD_OSD0_DMA_CTL_S;

typedef struct _TD_OSD0_ADDR_S
{
	unsigned int vlu_addr;
        unsigned int osdstride;
	unsigned int alp_addr;
        unsigned int alpstride;
} TD_OSD0_ADDR_S;

typedef struct _TD_OSD_RGB2YUV_S
{
        unsigned int osd0en;
        unsigned int osd1en;
        unsigned int osd2en;
	unsigned int osdrgb2yuv_coeff[3][4]; 
} TD_OSD_RGB2YUV_S;

typedef struct _TD_LAYER4_OSD_CTL_S
{
        unsigned int            layer4en;
        unsigned int            layer4enhs;
        unsigned int            layer4Wenhs;
        TD_BD_CTL_S             layer4BDCtl;
        TD_AREA_CTL_S           layer4XCtl;
        TD_AREA_CTL_S           layer4YCtl;
        TD_OSD0_CTL_S           osd0Ctl;
        TD_OSD0_SIZE_S          osd0Size;
        TD_OSD0_DMA_CTL_S       osd0DmaCtl;
        TD_OSD0_ADDR_S          osd0Addr;
        TD_OSD_RGB2YUV_S        osdRgb2Yuv;
}TD_LAYER4_OSD_CTL_S;

typedef struct _TD_YUV2RGB_S
{
        unsigned int yuv2rgb_ctl_en;
	unsigned int yuv2rgb_coeff[3][4];
}TD_YUV2RGB_S;
/*
*MIXER OUTPUT
*/
typedef struct TD_DISP_BACK_GROUD_S
{
        unsigned int y;
        unsigned int u;
        unsigned int v;
} TD_DISP_BACK_GROUD_S;

typedef struct _TD_DISP_MIX_CTL_S
{
        unsigned int layer0glbalp;
        unsigned int layer4glbalp;
        unsigned int layer0sel;        
        unsigned int layer1sel;   //osd0     
        TD_DISP_BACK_GROUD_S  backGroud;
}TD_DISP_MIX_CTL_S;

/*
*INTERRUPT
*/
typedef struct _TD_DISP_IRQ_CTL_S
{
        unsigned int underrundcnt;
        unsigned int en;
} TD_DISP_IRQ_CTL_S;

typedef struct _TD_DISP_IRQ_S
{
        TD_DISP_IRQ_CTL_S irq0Ctl;
        TD_DISP_IRQ_CTL_S irq1Ctl;
        TD_DISP_IRQ_CTL_S irq2Ctl;
} TD_DISP_IRQ_S;
/*
*DMA WRITE BACK
*/
typedef struct _TD_WB_Y_BUF_S
{
        unsigned int y_en ;
        unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}TD_WB_Y_BUF_S;

typedef struct _TD_WB_UV_BUF_S
{
        unsigned int uv_en ;
        unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}TD_WB_UV_BUF_S;

typedef struct _TD_WB_PIXEL_FORMAT_OUT_S
{
        unsigned int formatsel    ;
        unsigned int inputformat  ;
        unsigned int outputformat ;
        unsigned int pixelorder422;
        unsigned int rgbpixelwidth;
} TD_WB_PIXEL_FORMAT_OUT_S;

typedef struct _TD_WB_DMA_MODE_S
{
        unsigned int otnum         ;
        unsigned int blen          ;
        unsigned int continuousmode;
        unsigned int swap          ;
        unsigned int errdetecten   ;
} TD_WB_DMA_MODE_S;

typedef struct _TD_WB_INFO_CLR_S
{
        unsigned int frmcntclear ;
        unsigned int fifoerrclear;
        unsigned int maxbw       ;
        unsigned int totalbw     ;
} TD_WB_INFO_CLR_S;

typedef struct _TD_WB_CH_CTL_S
{ 
	unsigned int err_unit;
	unsigned int err_threshold;
	unsigned int request;
	TD_WB_DMA_MODE_S	dmaMode;
	TD_WB_INFO_CLR_S	infoClr;
}TD_WB_CH_CTL_S;
		
typedef struct _TD_WB_CTL_S
{
	unsigned int              wb_en;
        unsigned int              input_mode;
	unsigned int              buffersize;
	unsigned int              v_size_out;
	unsigned int              h_size_out;
	TD_WB_Y_BUF_S             yBuf;
	TD_WB_UV_BUF_S            uvBuf;
	TD_WB_PIXEL_FORMAT_OUT_S  PixelFormatOut;
	TD_WB_CH_CTL_S            ch0Ctl;
	TD_WB_CH_CTL_S            ch1Ctl;
}TD_WB_CTL_S;

typedef struct _TD_CORE_CTL_S
{
        TD_ROT_ALL_CTL_S          rotAllCtl;
        TD_SOFT_RST_CTL_S         rstCtl;
        TD_DMA_SW_CTL_S           swCtl;
//        TD_DISP_CTL_S             dispCtl;
        TD_DISP_ALL_CTL_S		  dispAllCtl;
        TD_LAYER0_CTL_S           layer0Ctl;
        TD_LAYER4_OSD_CTL_S       layer4OsdCtl;
        TD_YUV2RGB_S              yuv2rgb;
        TD_DISP_MIX_CTL_S         dispMixCtl;
        TD_DISP_IRQ_S             dispIrqCtl;
        TD_WB_CTL_S               wbCtl;
}TD_CORE_CTL_S;

int TD_DRV_Core_Remap(void);
int TD_DRV_SetCore(TD_CORE_CTL_S *tdCoreCtl); 
//DEBUG
int TD_DRV_GetCoreRegsVal(void);

#endif /*_TD_CORE_DRV_DEF_H_*/
