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

#ifndef _VO_CORE_DRV_DEF_H_
#define _VO_CORE_DRV_DEF_H_
/*
*WRAP
*/
typedef  struct _VO_SOFT_RST_CTL_S
{
        unsigned int disp;
        unsigned int vo  ;
        unsigned int apb ;
        unsigned int core;
} VO_SOFT_RST_CTL_S;

typedef struct _VO_LOAD_CTL_S
{
        unsigned int regready;
        unsigned int regfirstload;
} VO_LOAD_CTL_S;

typedef struct _VO_DMA_SW_CTL_S
{
        unsigned int reqwr;
        unsigned int reqrd;      

} VO_DMA_SW_CTL_S;

typedef struct _VO_DMA_RD_CTL_OUT_S
{
        unsigned int wrst    ;
        unsigned int wrrstrdy;
        unsigned int rdst    ;
        unsigned int rdrstrdy;
} VO_DMA_RD_CTL_OUT_S;

typedef struct _VO_DMA_ARB_MODE_S
{
        unsigned int wr_arb_mode;
        unsigned int rd_arb_mode;
} VO_DMA_ARB_MODE_S;

typedef struct _VO_DMA_WEIGHT_RD_S
{
        unsigned int chl0;
        unsigned int chl1;
        unsigned int chl2;
        unsigned int chl3;
        unsigned int chl4;
        unsigned int chl5;
        unsigned int chl6;
        unsigned int chl7;
        unsigned int chl8 ;
        unsigned int chl9 ;
        unsigned int chl10;
        unsigned int chl11;
        unsigned int chl12;
        unsigned int chl13;
        unsigned int chl14;
        unsigned int chl15;
} VO_DMA_WEIGHT_RD_S;

typedef struct  VO_DMA_PRIORITY_RD_S   
{
        unsigned int chl0 ;
        unsigned int chl1 ;
        unsigned int chl2 ;
        unsigned int chl3 ;
        unsigned int chl4 ;
        unsigned int chl5 ;
        unsigned int chl6 ;
        unsigned int chl7 ;        
        unsigned int chl8 ;
        unsigned int chl9 ;
        unsigned int chl10;
        unsigned int chl11;
        unsigned int chl12;
        unsigned int chl13;
        unsigned int chl14;
        unsigned int chl15;   
} VO_DMA_PRIORITY_RD_S;

typedef struct _VO_DMA_ID_RD_S    
{
        unsigned int chl0 ;
        unsigned int chl1 ;
        unsigned int chl2 ;
        unsigned int chl3 ;
        unsigned int chl4 ;
        unsigned int chl5 ;
        unsigned int chl6 ;
        unsigned int chl7 ;        
        unsigned int chl8 ;
        unsigned int chl9 ;
        unsigned int chl10;
        unsigned int chl11;
        unsigned int chl12;
        unsigned int chl13;
        unsigned int chl14;
        unsigned int chl15;
} VO_DMA_ID_RD_S;

typedef struct _VO_DMA_CTL_S
{
	VO_DMA_SW_CTL_S     	sw_ctl;
	VO_DMA_RD_CTL_OUT_S 	rd_ctl_out;
	VO_DMA_ARB_MODE_S   	arb_mode;
	VO_DMA_WEIGHT_RD_S  	weight_rd;
	VO_DMA_PRIORITY_RD_S	prior_rd;
	VO_DMA_ID_RD_S      	id_rd;        
}VO_DMA_CTL_S;

typedef struct _VO_BD_CTL_S
{
        unsigned int limiten ;
        unsigned int outstand;
} VO_BD_CTL_S;

typedef struct _VO_BD_LAYER_CTL_S
{
	VO_BD_CTL_S		layer0_line0_bd_ctl;
	VO_BD_CTL_S		layer0_line1_bd_ctl;
	VO_BD_CTL_S		layer0_line2_bd_ctl;
	VO_BD_CTL_S		layer0_line3_bd_ctl;
	VO_BD_CTL_S		layer1_bd_ctl;
	VO_BD_CTL_S		layer2_bd_ctl;
	VO_BD_CTL_S		layer3_bd_ctl;
	VO_BD_CTL_S		layer4_bd_ctl;
	VO_BD_CTL_S		layer5_bd_ctl;
	VO_BD_CTL_S		layer6_bd_ctl; 
}VO_BD_LAYER_CTL_S;

typedef struct _VO_WRAP_ATTR_S
{
        VO_SOFT_RST_CTL_S       rstCtl;        
        VO_LOAD_CTL_S           loadCtl;
        VO_DMA_CTL_S            dmaCtl;
        VO_BD_LAYER_CTL_S       bdLayerCtl;
}VO_WRAP_ATTR_S;
/*
*CORE
*/
typedef struct _VO_AREA_CTL_S
{
        unsigned int start;
        unsigned int stop ;
}VO_AREA_CTL_S;

typedef struct _VO_DISP_CTL0_S
{
        unsigned int vcntbit0    ;
        unsigned int secndfoffset;
        unsigned int framesyncdly;  
} VO_DISP_CTL0_S;

typedef struct _VO_DISP_SIZE_S
{
        unsigned int hsize;
        unsigned int vsize;
} VO_DISP_SIZE_S;

typedef struct _VO_DISP_CTL_S
{
        unsigned int          dispEnable;
        VO_AREA_CTL_S         xZoneCtl;
        VO_AREA_CTL_S         yZoneCtl;
        VO_AREA_CTL_S         dispHsyncCtl;
        VO_AREA_CTL_S         dispHsync1Ctl;
        VO_AREA_CTL_S         dispVsync1Ctl;
        VO_AREA_CTL_S         dispHsync2Ctl;
        VO_AREA_CTL_S         dispVsync2Ctl;
        VO_DISP_CTL0_S        dispCtl0;
        VO_DISP_SIZE_S        dispSize;   
}VO_DISP_CTL_S;

typedef struct _VO_SIZE_S
{
        unsigned int hsize;
        unsigned int vsize;
} VO_SIZE_S;

typedef struct _VO_BASE_MODE_S
{
        unsigned int mode;
        unsigned int base0mask;
        unsigned int base1mask;
        unsigned int addrflag ;
} VO_BASE_MODE_S;
/*
*layer0
*/
typedef struct _VO_LAYER0_IMG_IN_DAT_MODE_S
{
        unsigned int datmode ;
        unsigned int endiany ;
        unsigned int endianuv;
        unsigned int swi; 
} VO_LAYER0_IMG_IN_DAT_MODE_S;

typedef struct _VO_LAYER0_SCALE_CTL_S
{
        unsigned int pstep;
        unsigned int dstep;
        unsigned int pstep_st;
} VO_LAYER0_SCALE_CTL_S;
/*
*MFBD
*/
typedef struct _VO_LAYER0_MFBD_Y_BUF_S
{
	unsigned int y_addr0;
	unsigned int y_stride0;		
	unsigned int y_addr1;
	unsigned int y_stride1;
}VO_LAYER0_MFBD_Y_BUF_S;

typedef struct _VO_LAYER0_MFBD_Y_HEAD_BUF_S
{
	unsigned int y_head_addr0;
	unsigned int y_head_stride0;		
	unsigned int y_head_addr1;
	unsigned int y_head_stride1;
}VO_LAYER0_MFBD_Y_HEAD_BUF_S;

typedef struct _VO_LAYER0_MFBD_UV_BUF_S
{
	unsigned int uv_addr0;
        unsigned int uv_stride0;
	unsigned int uv_addr1;
	unsigned int uv_stride1;        
}VO_LAYER0_MFBD_UV_BUF_S;

typedef struct _VO_LAYER0_MFBD_UV_HEAD_BUF_S
{
	unsigned int uv_head_addr0;
        unsigned int uv_head_stride0;
	unsigned int uv_head_addr1;
	unsigned int uv_head_stride1;
}VO_LAYER0_MFBD_UV_HEAD_BUF_S;

typedef struct _VO_LAYER0_MFBD_CTL_S
{
	unsigned int mfbd_en;
        VO_LAYER0_MFBD_Y_BUF_S          mfbdYBuf;
        VO_LAYER0_MFBD_Y_HEAD_BUF_S     mfbdYHeadBuf;
        VO_LAYER0_MFBD_UV_BUF_S         mfbdUVBuf;
        VO_LAYER0_MFBD_UV_HEAD_BUF_S    mfbdUVHeadBuf;
}VO_LAYER0_MFBD_CTL_S;
/*
*
*/
typedef struct _VO_YUV_BUF_S
{
    unsigned int  yAddr0;
    unsigned int  yAddr1;
    unsigned int  uvAddr0;
    unsigned int  uvAddr1;
    VO_SIZE_S     stride;
}VO_YUV_BUF_S;

typedef struct _VO_LAYER0_AREA_CTL_S
{
        VO_AREA_CTL_S         xCtl;
        VO_AREA_CTL_S         yCtl;
}VO_LAYER0_AREA_CTL_S;

typedef struct _VO_LAYER0_SIZE_S
{
        VO_SIZE_S             imgOffset;
        VO_SIZE_S             imgInSize;
        VO_SIZE_S             imgOutSize;
}VO_LAYER0_SIZE_S;

typedef struct _VO_LAYER0_SCALE_S
{
        VO_LAYER0_SCALE_CTL_S  hScaleCtl;
        VO_LAYER0_SCALE_CTL_S  vScaleCtl;
}VO_LAYER0_SCALE_S;

typedef struct _VO_LAYER0_CTL_S
{
    unsigned int          layer0DispEn;
    unsigned int          layer0En; 
    unsigned int          scalerBlen; 
    VO_LAYER0_IMG_IN_DAT_MODE_S imgInDatMode;     
    VO_LAYER0_AREA_CTL_S  areaCtl;
    VO_YUV_BUF_S          yuvBuf;
    VO_LAYER0_SCALE_S     scaleCtl;
    VO_LAYER0_SIZE_S      sizeCtl;
    VO_LAYER0_MFBD_CTL_S  layer0MfbdCtl;
    VO_BASE_MODE_S        baseMode;
}VO_LAYER0_CTL_S;
/*
*layer1
*/
typedef struct _VO_LAYER_CTL_S
{
        unsigned int enable   ;
        unsigned int yuv422en ;
        unsigned int yuv420en ;
        unsigned int endiany  ;        
        unsigned int endianuv ;        
        unsigned int uvswap   ; 
} VO_LAYER_CTL_S;

typedef struct _VO_IMG_IN_BLENTH_S
{
        unsigned int blen   ;        
        unsigned int voffset;
} VO_IMG_IN_BLENTH_S;

typedef struct _VO_AREA_S
{
        VO_AREA_CTL_S         xCtl;
        VO_AREA_CTL_S         yCtl;
}VO_AREA_S;

typedef struct _VO_LAYER_SIZE_S
{
        VO_SIZE_S             imgOffset;
        VO_SIZE_S             imgInPixSize;
}VO_LAYER_SIZE_S;

typedef struct _VO_LAYER1_CTL_S
{
        unsigned int          layer1DispEn;
        VO_LAYER_CTL_S        layerCtl; 
        VO_AREA_S             areaCtl;
        VO_YUV_BUF_S          yuvBuf;
        VO_LAYER_SIZE_S       sizeCtl;
        VO_IMG_IN_BLENTH_S    imgInBlen;
        VO_BASE_MODE_S        baseMode;
}VO_LAYER1_CTL_S;
/*
*layer2
*/
typedef struct _VO_LAYER2_CTL_S
{
        unsigned int          layer2DispEn;
        VO_LAYER_CTL_S        layerCtl; 
        VO_AREA_S             areaCtl;
        VO_YUV_BUF_S          yuvBuf;
        VO_LAYER_SIZE_S       sizeCtl;
        VO_IMG_IN_BLENTH_S    imgInBlen;
        VO_BASE_MODE_S        baseMode;
}VO_LAYER2_CTL_S;
/*
*layer3
*/
typedef struct _VO_LAYER3_CTL_S
{
        unsigned int          layer3DispEn;
        VO_LAYER_CTL_S        layerCtl; 
        VO_AREA_S             areaCtl;
        VO_YUV_BUF_S          yuvBuf;
        VO_LAYER_SIZE_S       sizeCtl;
        VO_IMG_IN_BLENTH_S    imgInBlen;
        VO_BASE_MODE_S        baseMode;
}VO_LAYER3_CTL_S;
/*
*OSD
*/
typedef struct _VO_OSD_CTL_S
{
        unsigned int osdtype  ;
        unsigned int alphatpye;
} VO_OSD_CTL_S;

typedef struct _VO_OSD_SIZE_S
{
        unsigned int width;
        unsigned int height; 
} VO_OSD_SIZE_S;

typedef struct _VO_OSD_DMA_CTL_S
{
        unsigned int dmarequestlen;
        unsigned int dmamap       ;
        unsigned int rgbrev       ;     
} VO_OSD_DMA_CTL_S;

typedef struct _VO_OSD_BUF_S
{
        unsigned int    alp_addr0;
        unsigned int    alp_addr1;
        unsigned int    alpstride;        
        unsigned int    vlu_addr0;
        unsigned int    vlu_addr1;
        unsigned int    osdstride;
}VO_OSD_BUF_S;
/*
*OSD0 INFO
*/
typedef struct _VO_OSD0_CTL_S
{
        unsigned int    osdLayer4DispEn;
        unsigned int    osdrgb2yuvEn;
        VO_OSD_CTL_S    osdCtl;
        VO_AREA_S       osdArea;
        VO_OSD_SIZE_S   osdSize;
        VO_OSD_BUF_S    osdBuf;
        VO_OSD_DMA_CTL_S osdDmaCtl;
        VO_BASE_MODE_S  baseMode;
}VO_OSD0_CTL_S;
/*
*OSD1 INFO
*/
typedef struct _VO_OSD1_CTL_S
{
        unsigned int    osdLayer5DispEn;
        unsigned int    osdrgb2yuvEn;
        VO_OSD_CTL_S    osdCtl;
        VO_AREA_S       osdArea;
        VO_OSD_SIZE_S   osdSize;
        VO_OSD_BUF_S    osdBuf;
        VO_OSD_DMA_CTL_S osdDmaCtl;
        VO_BASE_MODE_S  baseMode;
}VO_OSD1_CTL_S;
/*
*OSD2 INFO
*/
typedef struct _VO_OSD2_CTL_S
{
        unsigned int    osdLayer6DispEn;
        unsigned int    osdrgb2yuvEn;
        VO_OSD_CTL_S    osdCtl;
        VO_AREA_S       osdArea;
        VO_OSD_SIZE_S   osdSize;
        VO_OSD_BUF_S    osdBuf;
        VO_OSD_DMA_CTL_S osdDmaCtl;
        VO_BASE_MODE_S  baseMode;
}VO_OSD2_CTL_S;
/*
*
*/
typedef struct _VO_OSD_RGB2YUV_S
{     
	unsigned int osdrgb2yuv_coeff[3][4]; 
} VO_OSD_RGB2YUV_S;

typedef struct _VO_YUV2RGB_S
{
        unsigned int yuv2rgb_ctl_en;
	unsigned int yuv2rgb_coeff[3][4];
}VO_YUV2RGB_S;
/*
*MIX
*/
typedef struct _VO_MIX_CTL_S
{
        unsigned int glben;
        unsigned int glbalp;
        unsigned int sel;
}VO_MIX_CTL_S;

typedef struct _VO_DISP_BACK_GROUD_S
{
        unsigned int y;
        unsigned int u;
        unsigned int v;
} VO_DISP_BACK_GROUD_S;

typedef struct _VO_DISP_MIX_CTL_S
{
        VO_MIX_CTL_S          layer0mix;
        VO_MIX_CTL_S          layer1mix;
        VO_MIX_CTL_S          layer2mix;
        VO_MIX_CTL_S          layer3mix;
        VO_MIX_CTL_S          layer4mix;
        VO_MIX_CTL_S          layer5mix;
        VO_MIX_CTL_S          layer6mix;
        VO_DISP_BACK_GROUD_S  backGroud;
}VO_DISP_MIX_CTL_S;
/*
*INTERRUPT
*/
typedef struct _VO_DISP_IRQ_CTL_S
{
        unsigned int underrundcnt0;
        unsigned int en0;
        unsigned int underrundcnt1;
        unsigned int en1;
        unsigned int underrundcnt2;
        unsigned int en2;
} VO_DISP_IRQ_CTL_S;
/*
*DMA WRITE BACK
*/
typedef struct _VO_WB_Y_CTL_S
{
        unsigned int y_en ;
        unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}VO_WB_Y_CTL_S;

typedef struct _VO_WB_UV_CTL_S
{
        unsigned int uv_en ;
        unsigned int addr0;
	unsigned int addr1;
	unsigned int hstride;
}VO_WB_UV_CTL_S;

typedef struct _VO_WB_PIXEL_FORMAT_OUT_S
{
        unsigned int formatsel    ;
        unsigned int inputformat  ;
        unsigned int outputformat ;
        unsigned int pixelorder422;
        unsigned int rgbpixelwidth;
} VO_WB_PIXEL_FORMAT_OUT_S;

typedef struct _VO_WB_DMA_MODE_S
{
        unsigned int otnum         ;
        unsigned int blen          ;
        unsigned int continuousmode;
        unsigned int swap          ;
        unsigned int errdetecten   ;
} VO_WB_DMA_MODE_S;

typedef struct _VO_WB_INFO_CLR_S
{
        unsigned int frmcntclear ;
        unsigned int fifoerrclear;
        unsigned int maxbw       ;
        unsigned int totalbw     ;
} VO_WB_INFO_CLR_S;

typedef struct _VO_WB_CH_CTL_S
{ 
	unsigned int err_unit;
	unsigned int err_threshold;
	unsigned int request;
	VO_WB_DMA_MODE_S	dmaMode;
	VO_WB_INFO_CLR_S	infoClr;
}VO_WB_CH_CTL_S;

typedef struct _VO_WB_BUF_S
{
        VO_WB_Y_CTL_S            yBufCtl;
        VO_WB_UV_CTL_S           uvBufCtl;
}VO_WB_BUF_S;

typedef struct _VO_WB_CTL_S
{
        unsigned int              wben;
        unsigned int              inchmode;
	unsigned int              buffersize;
	unsigned int              v_size_out;
	unsigned int              h_size_out;
        VO_WB_BUF_S               BufCtl;
        VO_WB_PIXEL_FORMAT_OUT_S  PixelFormatOut;
        VO_WB_CH_CTL_S           ch0Ctl;
        VO_WB_CH_CTL_S           ch1Ctl;
}VO_WB_CTL_S;

typedef struct _VO_CORE_ATTR_S
{
        VO_DISP_CTL_S           dispCtl;
        VO_LAYER0_CTL_S         layer0Ctl;
        VO_LAYER1_CTL_S         layer1Ctl;
        VO_LAYER2_CTL_S         layer2Ctl;
        VO_LAYER3_CTL_S         layer3Ctl;
        VO_OSD0_CTL_S           osd0Ctl;
        VO_OSD1_CTL_S           osd1Ctl;
        VO_OSD2_CTL_S           osd2Ctl;
        VO_OSD_RGB2YUV_S        osdRgb2Yuv;
        VO_YUV2RGB_S            yuv2rgb;  
        VO_DISP_MIX_CTL_S       dispMixCtl;
        unsigned int            ditherctlen;
        unsigned int            clutctlen;
        VO_DISP_IRQ_CTL_S       dispIrqCtl;
        VO_WB_CTL_S             wbCtl;
}VO_CORE_ATTR_S;

int VO_DRV_Core_Remap(void );
int VO_DRV_SetInit(VO_LOAD_CTL_S *loadCtl);
int VO_DRV_SetDispEn(unsigned int dispEnable);
int VO_DRV_SetWrap(VO_WRAP_ATTR_S *voWrapAttr);
int VO_DRV_SetCore(VO_CORE_ATTR_S *voCoreAttr);
//DEBUG
int VO_DRV_GetCoreRegsVal(void);
#endif /*_VO_CORE_DRV_DEF_H_*/
