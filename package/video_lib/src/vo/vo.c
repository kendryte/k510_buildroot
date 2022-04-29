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
  File Name     : vo.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include <string.h>
#include "isp_com.h"
#include "vo/vo.h"
#include "vo/core/vo_core_drv.h"
#include "vo/remap/vo_remap_drv.h"
#include "vo/table/vo_table_drv.h"

extern struct _VO_CORE_INFO_S hdmi_vo_info;
extern struct _VO_CORE_INFO_S dsi_vo_info;
/**********************************************************************************
 * 
 * *******************************************************************************/
/*
 * init
 */
static int Vo_Init(struct isp_vo_device *vo)
{
    VO_CHECK_POINTER(vo);
    struct isp_device *isp = to_isp_device(vo);

	unsigned int dispEnable = 0x0;
    Vo_Drv_Core_SetDispEn(isp,dispEnable);
	return 0;
}
/*
 * start
 */
static int Vo_Start(struct isp_vo_device *vo)
{
    VO_CHECK_POINTER(vo);
    struct isp_device *isp = to_isp_device(vo);

    VO_LOAD_CTL_S loadCtl;
    loadCtl.regfirstload = 1;
    loadCtl.regready = 1;
    Vo_Drv_Wrap_SetInit(isp,&loadCtl);
	return 0;
}
/*
 * wrap
 */
static int Vo_SetWrap(struct isp_vo_device *vo)
{
    VO_CHECK_POINTER(vo);
    struct isp_device *isp = to_isp_device(vo);
    //
    VO_SOFT_RST_CTL_S swRstCtl;
    swRstCtl.disp = 1;
    swRstCtl.vo   = 1;
    swRstCtl.apb  = 1;
    swRstCtl.core = 1;    
    Vo_Drv_Wrap_SetRst(isp,&swRstCtl);
    //
    VO_DMA_CTL_S dmaCtl;
	VO_DMA_SW_CTL_S  *sw_ctl=  &dmaCtl.sw_ctl;
    sw_ctl->reqrd  = 1;
    sw_ctl->reqwr  =1;
    //
	VO_DMA_ARB_MODE_S  *arb_mode=  &dmaCtl.arb_mode;
    arb_mode->wr_arb_mode = 0;
    arb_mode->rd_arb_mode = 0;
    //
	VO_DMA_WEIGHT_RD_S *weight_rd=  &dmaCtl.weight_rd;
    weight_rd->chl0=  0x1;
    weight_rd->chl1=  0x1;
    weight_rd->chl2=  0x1;
    weight_rd->chl3=  0x1;
    weight_rd->chl4=  0x1;
    weight_rd->chl5=  0x1;
    weight_rd->chl6=  0x1;
    weight_rd->chl7=  0x1;
    weight_rd->chl8 =  0x1;
    weight_rd->chl9 =  0x1;
    weight_rd->chl10=  0x1;
    weight_rd->chl11=  0x1;
    weight_rd->chl12=  0x1;
    weight_rd->chl13=  0x1;
    weight_rd->chl14=  0x1;
    weight_rd->chl15=  0x1;
    //
	VO_DMA_PRIORITY_RD_S *prior_rd=  &dmaCtl.prior_rd;
    prior_rd->chl0=  0x0;
    prior_rd->chl1=  0x1;
    prior_rd->chl2=  0x2;
    prior_rd->chl3=  0x3;
    prior_rd->chl4=  0x4;
    prior_rd->chl5=  0x5;
    prior_rd->chl6=  0x6;
    prior_rd->chl7=  0x7;
    prior_rd->chl8 =  0x8;
    prior_rd->chl9 =  0x9;
    prior_rd->chl10=  0xa;
    prior_rd->chl11=  0xb;
    prior_rd->chl12=  0xc;
    prior_rd->chl13=  0xd;
    prior_rd->chl14=  0xe;
    prior_rd->chl15=  0xf;
    //
	VO_DMA_ID_RD_S *id_rd=  &dmaCtl.id_rd;
    id_rd->chl0=  0x0;
    id_rd->chl1=  0x1;
    id_rd->chl2=  0x2;
    id_rd->chl3=  0x3;
    id_rd->chl4=  0x4;
    id_rd->chl5=  0x5;
    id_rd->chl6=  0x6;
    id_rd->chl7=  0x7;
    id_rd->chl8 =  0x8;
    id_rd->chl9 =  0x9;
    id_rd->chl10=  0xa;
    id_rd->chl11=  0xb;
    id_rd->chl12=  0xc;
    id_rd->chl13=  0xd;
    id_rd->chl14=  0xe;
    id_rd->chl15=  0xf;
    Vo_Drv_Wrap_SetDma(isp,&dmaCtl);
    //
    VO_BD_LAYER_CTL_S bdLayerCtl;
	VO_BD_CTL_S	*layer0_line0_bd_ctl = &bdLayerCtl.layer0_line0_bd_ctl;
    layer0_line0_bd_ctl->limiten = 1;
    layer0_line0_bd_ctl->outstand = 7;
    //    
	VO_BD_CTL_S	*layer0_line1_bd_ctl = &bdLayerCtl.layer0_line1_bd_ctl;
    layer0_line1_bd_ctl->limiten = 1;
    layer0_line1_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer0_line2_bd_ctl = &bdLayerCtl.layer0_line2_bd_ctl;
    layer0_line2_bd_ctl->limiten = 1;
    layer0_line2_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer0_line3_bd_ctl = &bdLayerCtl.layer0_line3_bd_ctl;
    layer0_line3_bd_ctl->limiten = 1;
    layer0_line3_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer1_bd_ctl = &bdLayerCtl.layer1_bd_ctl;
    layer1_bd_ctl->limiten = 1;
    layer1_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer2_bd_ctl = &bdLayerCtl.layer2_bd_ctl;
    layer2_bd_ctl->limiten = 1;
    layer2_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer3_bd_ctl = &bdLayerCtl.layer3_bd_ctl;
    layer3_bd_ctl->limiten = 1;
    layer3_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer4_bd_ctl = &bdLayerCtl.layer4_bd_ctl;
    layer4_bd_ctl->limiten = 1;
    layer4_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer5_bd_ctl = &bdLayerCtl.layer5_bd_ctl;
    layer5_bd_ctl->limiten = 1;
    layer5_bd_ctl->outstand = 7;
    //  
	VO_BD_CTL_S	*layer6_bd_ctl = &bdLayerCtl.layer6_bd_ctl;
    layer6_bd_ctl->limiten = 1;
    layer6_bd_ctl->outstand = 7;
    //
    Vo_Drv_Wrap_SetBDCtl(isp,&bdLayerCtl);
    return 0;
}
/*
 * core
 */
static void Vo_Core_SetDisp(struct isp_device *isp,VO_DISP_INFO_S *dispInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(dispInfo);

    VO_DISP_CTL_S dispCtl;
    //
    dispCtl.dispEnable = ~dispInfo->dispEnable;
    //
    VO_AREA_CTL_S  *xZoneCtl = &dispCtl.xZoneCtl;
    xZoneCtl->start = dispInfo->xZoneCtl_start;
    xZoneCtl->stop  = dispInfo->xZoneCtl_stop;//-1;
    //
    VO_AREA_CTL_S  *yZoneCtl = &dispCtl.yZoneCtl;
    yZoneCtl->start = dispInfo->yZoneCtl_start;
    yZoneCtl->stop  = dispInfo->yZoneCtl_stop;//-1;
    //
    VO_AREA_CTL_S  *dispHsyncCtl = &dispCtl.dispHsyncCtl;
    dispHsyncCtl->start = dispInfo->dispHsyncCtl_start;
    dispHsyncCtl->stop  = dispInfo->dispHsyncCtl_stop;
    //
    VO_AREA_CTL_S  *dispHsync1Ctl = &dispCtl.dispHsync1Ctl;
    dispHsync1Ctl->start = dispInfo->dispHsync1Ctl_start;
    dispHsync1Ctl->stop  = dispInfo->dispHsync1Ctl_stop;
    //
    VO_AREA_CTL_S  *dispVsync1Ctl = &dispCtl.dispVsync1Ctl;
    dispVsync1Ctl->start = dispInfo->dispVsync1Ctl_start;
    dispVsync1Ctl->stop  = dispInfo->dispVsync1Ctl_stop;
    //
    VO_AREA_CTL_S  *dispHsync2Ctl = &dispCtl.dispHsync2Ctl;
    dispHsync2Ctl->start = dispInfo->dispHsync2Ctl_start;
    dispHsync2Ctl->stop  = dispInfo->dispHsync2Ctl_stop;
    //
    VO_AREA_CTL_S  *dispVsync2Ctl = &dispCtl.dispVsync2Ctl;
    dispVsync2Ctl->start = dispInfo->dispVsync2Ctl_start;
    dispVsync2Ctl->stop  = dispInfo->dispVsync2Ctl_stop;
    //
    VO_DISP_CTL0_S *dispCtl0 = &dispCtl.dispCtl0;
    dispCtl0->framesyncdly = dispInfo->framesyncdly;
    dispCtl0->secndfoffset = dispInfo->secndfoffset;
    dispCtl0->vcntbit0     = dispInfo->vcntbit0;
    //
    VO_DISP_SIZE_S *dispSize = &dispCtl.dispSize; 
    dispSize->hsize = dispInfo->hsize;
    dispSize->vsize = dispInfo->vsize;
    //
    Vo_Drv_Core_SetDisp(isp,&dispCtl);

    return;
}
//layer0
static void Vo_Core_calc_scale(VO_LAYER0_SIZE_INFO_S *sizeInfo,VO_LAYER0_SCALE_INFO_S *scaleInfo)
{
    ISP_CHECK_POINTER(sizeInfo);
    ISP_CHECK_POINTER(scaleInfo);

    unsigned int InputWidth = sizeInfo->in_hsize;
    unsigned int  InputHeight = sizeInfo->in_vsize;
    unsigned int  OutputWidth = sizeInfo->out_hsize;
    unsigned int  OutputHeight = sizeInfo->out_vsize;

    scaleInfo->h_pstep = (InputWidth / OutputWidth);
    scaleInfo->h_dstep =((InputWidth % OutputWidth) * 65536 / OutputWidth);
    scaleInfo->h_pstep_st = 0;
    scaleInfo->v_pstep =(InputHeight / OutputHeight);
    scaleInfo->v_dstep =((InputHeight % OutputHeight) * 65536 / OutputHeight);
    scaleInfo->v_pstep_st = 0;
    return;
}
static void Vo_Core_SetLayer0(struct isp_device *isp,VO_LAYER0_INFO_S *layer0Info)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(layer0Info);

    VO_LAYER0_CTL_S layer0Ctl;
    layer0Ctl.layer0DispEn = layer0Info->layer0DispEn;
    layer0Ctl.layer0En = layer0Info->layer0En; 
    layer0Ctl.scalerBlen = layer0Info->scalerBlen; 
    //
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo  = &layer0Info->datModeInfo;
    VO_LAYER0_IMG_IN_DAT_MODE_S *imgInDatMode = &layer0Ctl.imgInDatMode; 
    imgInDatMode->datmode = datModeInfo->datmode;
    imgInDatMode->endianuv = datModeInfo->endianuv;
    imgInDatMode->endiany = datModeInfo->endiany;
    imgInDatMode->swi = datModeInfo->swi;
    //    
    VO_LAYER_AREA_INFO_S  *areaInfo = &layer0Info->areaInfo;
    VO_LAYER0_AREA_CTL_S  *areaCtl = &layer0Ctl.areaCtl;    
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop = areaInfo->xCtl_stop - 1;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop = areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S    *bufInfo = &layer0Info->bufInfo;
    VO_YUV_BUF_S          *yuvBuf = &layer0Ctl.yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride/8-1;
    yuvBuf->stride.vsize = bufInfo->vsize_stride-1;
    //
    VO_LAYER0_SCALE_INFO_S *scaleInfo = &layer0Info->scaleInfo;
    VO_LAYER0_SCALE_S     *scaleCtl = &layer0Ctl.scaleCtl;
    Vo_Core_calc_scale(&layer0Info->sizeInfo,scaleInfo);
    scaleCtl->hScaleCtl.dstep = scaleInfo->h_dstep;
    scaleCtl->hScaleCtl.pstep = scaleInfo->h_pstep;
    scaleCtl->hScaleCtl.pstep_st = scaleInfo->h_pstep_st;
    scaleCtl->vScaleCtl.dstep = scaleInfo->v_dstep;
    scaleCtl->vScaleCtl.pstep = scaleInfo->v_pstep;
    scaleCtl->vScaleCtl.pstep_st = scaleInfo->v_pstep_st;
    //
    VO_LAYER0_SIZE_INFO_S *sizeInfo = &layer0Info->sizeInfo;
    VO_LAYER0_SIZE_S      *sizeCtl = &layer0Ctl.sizeCtl;
    sizeCtl->imgInSize.hsize = sizeInfo->in_hsize - 1;
    sizeCtl->imgInSize.vsize = sizeInfo->in_vsize - 1;
    sizeCtl->imgOffset.hsize = sizeInfo->offset_hsize;
    sizeCtl->imgOffset.vsize = sizeInfo->offset_vsize;
    sizeCtl->imgOutSize.hsize = sizeInfo->out_hsize - 1;
    sizeCtl->imgOutSize.vsize = sizeInfo->out_vsize - 1;
    //
    VO_BASE_MODE_INFO_S   *baseModeInfo = &layer0Info->baseModeInfo;
    VO_BASE_MODE_S        *baseMode = &layer0Ctl.baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;
    //
    VO_LAYER0_MFBD_INFO_S *mfbdInfo = &layer0Info->mfbdInfo;
    VO_LAYER0_MFBD_CTL_S  *layer0MfbdCtl = &layer0Ctl.layer0MfbdCtl;
    layer0MfbdCtl->mfbd_en = mfbdInfo->mfbd_en;
    //y
    layer0MfbdCtl->mfbdYBuf.y_addr0 = mfbdInfo->y_addr0;
    layer0MfbdCtl->mfbdYBuf.y_addr1 = mfbdInfo->y_addr1;
    layer0MfbdCtl->mfbdYBuf.y_stride0 = mfbdInfo->y_stride0;
    layer0MfbdCtl->mfbdYBuf.y_stride1 = mfbdInfo->y_stride1;
    //y head
    layer0MfbdCtl->mfbdYHeadBuf.y_head_addr0 = mfbdInfo->y_head_addr0;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_addr1 = mfbdInfo->y_head_addr1;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_stride0 = mfbdInfo->y_head_stride0;
    layer0MfbdCtl->mfbdYHeadBuf.y_head_stride1 = mfbdInfo->y_head_stride1;
    //uv
    layer0MfbdCtl->mfbdUVBuf.uv_addr0 = mfbdInfo->uv_addr0;
    layer0MfbdCtl->mfbdUVBuf.uv_addr1 = mfbdInfo->uv_addr1;
    layer0MfbdCtl->mfbdUVBuf.uv_stride0 = mfbdInfo->uv_stride0;
    layer0MfbdCtl->mfbdUVBuf.uv_stride1 = mfbdInfo->uv_stride1;
    //uv head
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_addr0 = mfbdInfo->uv_head_addr0;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_addr1 = mfbdInfo->uv_head_addr1;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_stride0 = mfbdInfo->uv_head_stride0;
    layer0MfbdCtl->mfbdUVHeadBuf.uv_head_stride1 = mfbdInfo->uv_head_stride1;
    //
    Vo_Drv_Core_SetLayer0(isp,&layer0Ctl);
    return;
}
//layer1
static void Vo_Core_SetLayer1(struct isp_device *isp,VO_LAYER1_INFO_S *layer1Info)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(layer1Info);

    VO_LAYER1_CTL_S layer1Ctl;
    layer1Ctl.layer1DispEn = layer1Info->layer1DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer1Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer1Ctl.layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer1Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer1Ctl.areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop -1 ;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer1Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer1Ctl.yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride/8-1;
    yuvBuf->stride.vsize = bufInfo->vsize_stride-1;
    //
    VO_LAYER_SIZE_INFO_S *layer1SizeInfo = &layer1Info->layer1SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer1Ctl.sizeCtl;
    sizeCtl->imgInPixSize.hsize = layer1SizeInfo->in_hsize - 1;
    sizeCtl->imgInPixSize.vsize = layer1SizeInfo->in_vsize - 1;
    sizeCtl->imgOffset.hsize = layer1SizeInfo->offset_hsize;
    sizeCtl->imgOffset.vsize = layer1SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer1Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer1Ctl.imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer1Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer1Ctl.baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;

    Vo_Drv_Core_SetLayer1(isp,&layer1Ctl);
    return 0;
}
//layer2
static void Vo_Core_SetLayer2(struct isp_device *isp,VO_LAYER2_INFO_S *layer2Info)
{
    VO_CHECK_POINTER(layer2Info);
    VO_CHECK_POINTER(isp);

    VO_LAYER2_CTL_S layer2Ctl;
    layer2Ctl.layer2DispEn = layer2Info->layer2DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer2Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer2Ctl.layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer2Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer2Ctl.areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop-1;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer2Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer2Ctl.yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride/8-1;
    yuvBuf->stride.vsize = bufInfo->vsize_stride-1;
    //
    VO_LAYER_SIZE_INFO_S *layer2SizeInfo = &layer2Info->layer2SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer2Ctl.sizeCtl;
    sizeCtl->imgInPixSize.hsize = layer2SizeInfo->in_hsize - 1;
    sizeCtl->imgInPixSize.vsize = layer2SizeInfo->in_vsize - 1;
    sizeCtl->imgOffset.hsize = layer2SizeInfo->offset_hsize;  
    sizeCtl->imgOffset.vsize = layer2SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer2Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer2Ctl.imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer2Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer2Ctl.baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;

    Vo_Drv_Core_SetLayer2(isp,&layer2Ctl);
    return 0;
}
//layer3
static void Vo_Core_SetLayer3(struct isp_device *isp,VO_LAYER3_INFO_S *layer3Info)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(layer3Info);

    VO_LAYER3_CTL_S layer3Ctl;
    layer3Ctl.layer3DispEn = layer3Info->layer3DispEn;
    //
    VO_LAYER_INFO_S *layerInfo = &layer3Info->layerInfo;
    VO_LAYER_CTL_S     *layerCtl = &layer3Ctl.layerCtl;
    layerCtl->enable    = layerInfo->enable;
    layerCtl->yuv422en  = layerInfo->yuv422en;
    layerCtl->yuv420en  = layerInfo->yuv420en;
    layerCtl->endiany   = layerInfo->endiany;        
    layerCtl->endianuv  = layerInfo->endianuv;        
    layerCtl->uvswap    = layerInfo->uvswap;      
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer3Info->areaInfo;
    VO_AREA_S          *areaCtl = &layer3Ctl.areaCtl;
    areaCtl->xCtl.start = areaInfo->xCtl_start;
    areaCtl->xCtl.stop =  areaInfo->xCtl_stop-1;
    areaCtl->yCtl.start = areaInfo->yCtl_start;
    areaCtl->yCtl.stop =  areaInfo->yCtl_stop;
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer3Info->bufInfo;
    VO_YUV_BUF_S       *yuvBuf = &layer3Ctl.yuvBuf;
    yuvBuf->yAddr0 = bufInfo->yAddr0;
    yuvBuf->yAddr1 = bufInfo->yAddr1;
    yuvBuf->uvAddr0 = bufInfo->uvAddr0;
    yuvBuf->uvAddr1 = bufInfo->uvAddr1;
    yuvBuf->stride.hsize = bufInfo->hsize_stride/8-1;
    yuvBuf->stride.vsize = bufInfo->vsize_stride-1;
    //
    VO_LAYER_SIZE_INFO_S *layer3SizeInfo = &layer3Info->layer3SizeInfo; 
    VO_LAYER_SIZE_S    *sizeCtl = &layer3Ctl.sizeCtl; 
    sizeCtl->imgInPixSize.hsize = layer3SizeInfo->in_hsize - 1;
    sizeCtl->imgInPixSize.vsize = layer3SizeInfo->in_vsize - 1;
    sizeCtl->imgOffset.hsize = layer3SizeInfo->offset_hsize;  
    sizeCtl->imgOffset.vsize = layer3SizeInfo->offset_vsize;
    //
    VO_IMG_IN_BLENTH_INFO_S *imgInBlenthInfo = &layer3Info->imgInBlenthInfo;
    VO_IMG_IN_BLENTH_S *imgInBlen = &layer3Ctl.imgInBlen; 
    imgInBlen->blen = imgInBlenthInfo->blen;
    imgInBlen->voffset = imgInBlenthInfo->voffset;
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer3Info->baseModeInfo;
    VO_BASE_MODE_S     *baseMode = &layer3Ctl.baseMode;
    baseMode->base0mask = baseModeInfo->base0mask;
    baseMode->base1mask = baseModeInfo->base1mask;
    baseMode->mode = baseModeInfo->mode;

    Vo_Drv_Core_SetLayer3(isp,&layer3Ctl);
    return;
}
//osd0
static void Vo_Core_SetOsd0(struct isp_device *isp,VO_OSD0_INFO_S *osd0Info)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(osd0Info);

    VO_OSD0_CTL_S osd0Ctl;
    osd0Ctl.osdLayer4DispEn = osd0Info->osdLayer4DispEn;
    osd0Ctl.osdrgb2yuvEn = osd0Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd0Ctl.osdCtl;
    osdCtl->alphatpye = osd0Info->alphatpye;
    osdCtl->osdtype = osd0Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    VO_AREA_S       *osdArea = &osd0Ctl.osdArea;
    osdArea->xCtl.start = osd0AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd0AreaInfo->xCtl_stop-1;
    osdArea->yCtl.start = osd0AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd0AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd0SizeInfo = &osd0Info->osd0SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd0Ctl.osdSize;
    osdSize->width = osd0SizeInfo->width;
    osdSize->height= osd0SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd0BufInfo = &osd0Info->osd0BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd0Ctl.osdBuf;
    osdBuf->alp_addr0 = osd0BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd0BufInfo->alp_addr1;
    osdBuf->alpstride = osd0BufInfo->alpstride/8;
    osdBuf->vlu_addr0 = osd0BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd0BufInfo->vlu_addr1;
    osdBuf->osdstride = osd0BufInfo->osdstride/8;
    //
    VO_OSD_DMA_INFO_S    *osd0DmaInfo = &osd0Info->osd0DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd0Ctl.osdDmaCtl;
    osdDmaCtl->dmamap = osd0DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd0DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd0DmaInfo->rgbrev;
    //    
    VO_BASE_MODE_INFO_S  *osd0BaseModeInfo = &osd0Info->osd0BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd0Ctl.baseMode;    
    baseMode->base0mask = osd0BaseModeInfo->base0mask;
    baseMode->base1mask = osd0BaseModeInfo->base1mask;
    baseMode->mode = osd0BaseModeInfo->mode;

    Vo_Drv_Core_SetLayer4Osd0(isp,&osd0Ctl);
    return;
}
//osd1
static void Vo_Core_SetOsd1(struct isp_device *isp,VO_OSD1_INFO_S *osd1Info)
{
    VO_CHECK_POINTER(osd1Info);
    VO_CHECK_POINTER(isp);

    VO_OSD1_CTL_S osd1Ctl;
    osd1Ctl.osdLayer5DispEn = osd1Info->osdLayer5DispEn;
    osd1Ctl.osdrgb2yuvEn = osd1Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd1Ctl.osdCtl;
    osdCtl->alphatpye = osd1Info->alphatpye;
    osdCtl->osdtype = osd1Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    VO_AREA_S       *osdArea = &osd1Ctl.osdArea;
    osdArea->xCtl.start = osd1AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd1AreaInfo->xCtl_stop-1;
    osdArea->yCtl.start = osd1AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd1AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd1SizeInfo = &osd1Info->osd1SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd1Ctl.osdSize;
    osdSize->width = osd1SizeInfo->width;
    osdSize->height= osd1SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd1BufInfo = &osd1Info->osd1BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd1Ctl.osdBuf;
    osdBuf->alp_addr0 = osd1BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd1BufInfo->alp_addr1;
    osdBuf->alpstride = osd1BufInfo->alpstride/8;
    osdBuf->vlu_addr0 = osd1BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd1BufInfo->vlu_addr1;
    osdBuf->osdstride = osd1BufInfo->osdstride/8;
    //
    VO_OSD_DMA_INFO_S    *osd1DmaInfo = &osd1Info->osd1DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd1Ctl.osdDmaCtl;
    osdDmaCtl->dmamap = osd1DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd1DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd1DmaInfo->rgbrev;
    //    
    VO_BASE_MODE_INFO_S  *osd1BaseModeInfo = &osd1Info->osd1BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd1Ctl.baseMode;    
    baseMode->base0mask = osd1BaseModeInfo->base0mask;
    baseMode->base1mask = osd1BaseModeInfo->base1mask;
    baseMode->mode = osd1BaseModeInfo->mode;

    Vo_Drv_Core_SetLayer5Osd1(isp,&osd1Ctl);
    return;
}
//osd2
static void Vo_Core_SetOsd2(struct isp_device *isp,VO_OSD2_INFO_S *osd2Info)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(osd2Info);

    VO_OSD2_CTL_S osd2Ctl;
    osd2Ctl.osdLayer6DispEn = osd2Info->osdLayer6DispEn;
    osd2Ctl.osdrgb2yuvEn = osd2Info->osdrgb2yuvEn;
    //
    VO_OSD_CTL_S    *osdCtl = &osd2Ctl.osdCtl;
    osdCtl->alphatpye = osd2Info->alphatpye;
    osdCtl->osdtype = osd2Info->osdtype;
    //
    VO_LAYER_AREA_INFO_S *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    VO_AREA_S       *osdArea = &osd2Ctl.osdArea;
    osdArea->xCtl.start = osd2AreaInfo->xCtl_start;
    osdArea->xCtl.stop = osd2AreaInfo->xCtl_stop-1;
    osdArea->yCtl.start = osd2AreaInfo->yCtl_start;
    osdArea->yCtl.stop = osd2AreaInfo->yCtl_stop;
    //
    VO_OSD_SIZE_INFO_S   *osd2SizeInfo = &osd2Info->osd2SizeInfo;
    VO_OSD_SIZE_S   *osdSize = &osd2Ctl.osdSize;
    osdSize->width = osd2SizeInfo->width;
    osdSize->height= osd2SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S    *osd2BufInfo = &osd2Info->osd2BufInfo;
    VO_OSD_BUF_S    *osdBuf = &osd2Ctl.osdBuf;
    osdBuf->alp_addr0 = osd2BufInfo->alp_addr0;
    osdBuf->alp_addr1 = osd2BufInfo->alp_addr1;
    osdBuf->alpstride = osd2BufInfo->alpstride/8;
    osdBuf->vlu_addr0 = osd2BufInfo->vlu_addr0;
    osdBuf->vlu_addr1 = osd2BufInfo->vlu_addr1;
    osdBuf->osdstride = osd2BufInfo->osdstride/8;
    //
    VO_OSD_DMA_INFO_S    *osd2DmaInfo = &osd2Info->osd2DmaInfo;
    VO_OSD_DMA_CTL_S *osdDmaCtl = &osd2Ctl.osdDmaCtl;
    osdDmaCtl->dmamap = osd2DmaInfo->dmamap;
    osdDmaCtl->dmarequestlen = osd2DmaInfo->dmarequestlen;
    osdDmaCtl->rgbrev = osd2DmaInfo->rgbrev;
    //    
    VO_BASE_MODE_INFO_S  *osd2BaseModeInfo = &osd2Info->osd2BaseModeInfo;
    VO_BASE_MODE_S  *baseMode = &osd2Ctl.baseMode;    
    baseMode->base0mask = osd2BaseModeInfo->base0mask;
    baseMode->base1mask = osd2BaseModeInfo->base1mask;
    baseMode->mode = osd2BaseModeInfo->mode;

    Vo_Drv_Core_SetLayer6Osd2(isp,&osd2Ctl);
    return;
}
//Osd Rgb2Yuv
static void Vo_Core_SetOsdRgb2Yuv(struct isp_device *isp,VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(osdRgb2YuvInfo);
    
    VO_OSD_RGB2YUV_S osdRgb2Yuv;
    osdRgb2Yuv.osdrgb2yuv_coeff[0][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][0];
    osdRgb2Yuv.osdrgb2yuv_coeff[0][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][1];
    osdRgb2Yuv.osdrgb2yuv_coeff[0][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][2];
    osdRgb2Yuv.osdrgb2yuv_coeff[0][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[0][3];
    osdRgb2Yuv.osdrgb2yuv_coeff[1][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][0];
    osdRgb2Yuv.osdrgb2yuv_coeff[1][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][1];
    osdRgb2Yuv.osdrgb2yuv_coeff[1][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][2];
    osdRgb2Yuv.osdrgb2yuv_coeff[1][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[1][3];
    osdRgb2Yuv.osdrgb2yuv_coeff[2][0]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][0];
    osdRgb2Yuv.osdrgb2yuv_coeff[2][1]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][1];
    osdRgb2Yuv.osdrgb2yuv_coeff[2][2]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][2];
    osdRgb2Yuv.osdrgb2yuv_coeff[2][3]  =  osdRgb2YuvInfo->osdrgb2yuv_coeff[2][3];

    Vo_Drv_Core_SetRgb2Yuv(isp,&osdRgb2Yuv);
    return;
}
//Yuv2Rgb
static void Vo_Core_SetYuv2Rgb(struct isp_device *isp,VO_YUV2RGB_INFO_S *yuv2rgbInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(yuv2rgbInfo);

    VO_YUV2RGB_S yuv2rgb;
    yuv2rgb.yuv2rgb_ctl_en = yuv2rgbInfo->yuv2rgb_ctl_en;

    yuv2rgb.yuv2rgb_coeff[0][0] = yuv2rgbInfo->yuv2rgb_coeff[0][0];
    yuv2rgb.yuv2rgb_coeff[0][1] = yuv2rgbInfo->yuv2rgb_coeff[0][1];
    yuv2rgb.yuv2rgb_coeff[0][2] = yuv2rgbInfo->yuv2rgb_coeff[0][2];
    yuv2rgb.yuv2rgb_coeff[0][3] = yuv2rgbInfo->yuv2rgb_coeff[0][3];
    yuv2rgb.yuv2rgb_coeff[1][0] = yuv2rgbInfo->yuv2rgb_coeff[1][0];
    yuv2rgb.yuv2rgb_coeff[1][1] = yuv2rgbInfo->yuv2rgb_coeff[1][1];
    yuv2rgb.yuv2rgb_coeff[1][2] = yuv2rgbInfo->yuv2rgb_coeff[1][2];
    yuv2rgb.yuv2rgb_coeff[1][3] = yuv2rgbInfo->yuv2rgb_coeff[1][3];
    yuv2rgb.yuv2rgb_coeff[2][0] = yuv2rgbInfo->yuv2rgb_coeff[2][0];
    yuv2rgb.yuv2rgb_coeff[2][1] = yuv2rgbInfo->yuv2rgb_coeff[2][1];
    yuv2rgb.yuv2rgb_coeff[2][2] = yuv2rgbInfo->yuv2rgb_coeff[2][2];
    yuv2rgb.yuv2rgb_coeff[2][3] = yuv2rgbInfo->yuv2rgb_coeff[2][3];

    Vo_Drv_Core_SetYuv2Rgb(isp,&yuv2rgb);
    return; 
}
//Disp Mix
static void Vo_Core_SetDispMixCtl(struct isp_device *isp,VO_CORE_INFO_S *voCoreInfo)
{    
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(voCoreInfo);

    VO_DISP_MIX_INFO_S *dispMixCtlInfo = &voCoreInfo->dispMixCtlInfo;
    VO_CORE_ATTR_S    voCoreAttr;
    VO_DISP_MIX_CTL_S *dispMixCtl = &voCoreAttr.dispMixCtl;
    //
    VO_MIX_INFO_S        *layerMixInfo = &dispMixCtlInfo->layerMixInfo[0];
    VO_MIX_CTL_S         *layer0mix = &dispMixCtl->layer0mix;
    layer0mix->glben  =  layerMixInfo[0].glben;
    layer0mix->sel    =  layerMixInfo[0].sel;
    layer0mix->glbalp =  layerMixInfo[0].glbalp;
    //
    VO_MIX_CTL_S         *layer1mix = &dispMixCtl->layer1mix;
    layer1mix->glben  =  layerMixInfo[1].glben;
    layer1mix->sel    =  layerMixInfo[1].sel;
    layer1mix->glbalp =  layerMixInfo[1].glbalp;
    //
    VO_MIX_CTL_S         *layer2mix = &dispMixCtl->layer2mix;
    layer2mix->glben  =  layerMixInfo[2].glben;
    layer2mix->sel    =  layerMixInfo[2].sel;
    layer2mix->glbalp =  layerMixInfo[2].glbalp;
    //
    VO_MIX_CTL_S         *layer3mix = &dispMixCtl->layer3mix;
    layer3mix->glben  =  layerMixInfo[3].glben;
    layer3mix->sel    =  layerMixInfo[3].sel;
    layer3mix->glbalp =  layerMixInfo[3].glbalp;
    //
    VO_MIX_CTL_S         *layer4mix = &dispMixCtl->layer4mix;
    layer4mix->glben  =  layerMixInfo[4].glben;
    layer4mix->sel    =  layerMixInfo[4].sel;
    layer4mix->glbalp =  layerMixInfo[4].glbalp;
    //
    VO_MIX_CTL_S         *layer5mix = &dispMixCtl->layer5mix;
    layer5mix->glben  =  layerMixInfo[5].glben;
    layer5mix->sel    =  layerMixInfo[5].sel;
    layer5mix->glbalp =  layerMixInfo[5].glbalp;
    //
    VO_MIX_CTL_S         *layer6mix = &dispMixCtl->layer6mix;
    layer6mix->glben  =  layerMixInfo[6].glben;
    layer6mix->sel    =  layerMixInfo[6].sel;
    layer6mix->glbalp =  layerMixInfo[6].glbalp;
    // 
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &dispMixCtlInfo->dispBackGroudInfo;
    VO_DISP_BACK_GROUD_S *backGroud = &dispMixCtl->backGroud;	
    backGroud->y = dispBackGroudInfo->y;
    backGroud->u = dispBackGroudInfo->u;
    backGroud->v = dispBackGroudInfo->v;
    //    
    voCoreAttr.ditherctlen = voCoreInfo->ditherctlen;
    voCoreAttr.clutctlen = voCoreInfo->clutctlen;
    Vo_Drv_Core_SetMix(isp,&voCoreAttr);
    return;
}
//Disp iRQ
void Vo_Core_SetDispIrq(struct isp_device *isp,VO_DISP_IRQ_INFO_S *dispIrqInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(dispIrqInfo);
    //
    VO_DISP_IRQ_CTL_S dispIrqCtl;
    dispIrqCtl.en0 = dispIrqInfo->en0;
    dispIrqCtl.underrundcnt0 = dispIrqInfo->underrundcnt0;
    //
    dispIrqCtl.en1 = dispIrqInfo->en1;
    dispIrqCtl.underrundcnt1 = dispIrqInfo->underrundcnt1;
    //
    dispIrqCtl.en2 = dispIrqInfo->en2;
    dispIrqCtl.underrundcnt2 = dispIrqInfo->underrundcnt2;

    Vo_Drv_Core_SetInt(isp,&dispIrqCtl);
    return 0;
}
//WB
static void Vo_Core_SetWB(struct isp_device *isp,VO_WB_INFO_S *wbInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(wbInfo);

    VO_WB_CTL_S wbCtl;
    //
    wbCtl.wben = wbInfo->wb_en;
    wbCtl.inchmode = wbInfo->inchmode;
	wbCtl.buffersize = wbInfo->buffersize;
	wbCtl.v_size_out = wbInfo->v_size_out;
	wbCtl.h_size_out = wbInfo->h_size_out;
    //
    VO_WB_BUF_INFO_S *wbBufInfo = &wbInfo->wbBufInfo;
    VO_WB_BUF_S  *BufCtl = &wbCtl.BufCtl;
    BufCtl->yBufCtl.y_en = wbBufInfo->wbYInfo.y_en;
    BufCtl->yBufCtl.addr0 = wbBufInfo->wbYInfo.addr0;
    BufCtl->yBufCtl.addr1 = wbBufInfo->wbYInfo.addr1;
    BufCtl->yBufCtl.hstride = wbBufInfo->wbYInfo.hstride;
    BufCtl->uvBufCtl.uv_en = wbBufInfo->wbUVInfo.uv_en;
    BufCtl->uvBufCtl.addr0 = wbBufInfo->wbUVInfo.addr0;
    BufCtl->uvBufCtl.addr1 = wbBufInfo->wbUVInfo.addr1;
    BufCtl->uvBufCtl.hstride = wbBufInfo->wbUVInfo.hstride;
    //
    VO_WB_PIXEL_FORMAT_OUT_INFO_S *wbPixelFormatOutInfo = &wbInfo->wbPixelFormatOutInfo;
    VO_WB_PIXEL_FORMAT_OUT_S  *PixelFormatOut = &wbCtl.PixelFormatOut;
    PixelFormatOut->formatsel = wbPixelFormatOutInfo->formatsel;
    PixelFormatOut->inputformat = wbPixelFormatOutInfo->inputformat;
    PixelFormatOut->outputformat = wbPixelFormatOutInfo->outputformat;
    PixelFormatOut->pixelorder422 = wbPixelFormatOutInfo->pixelorder422;
    PixelFormatOut->rgbpixelwidth = wbPixelFormatOutInfo->rgbpixelwidth;
    //
    VO_WB_CH_INFO_S *ch0Info = &wbInfo->ch0Info;
    VO_WB_CH_CTL_S *ch0Ctl = &wbCtl.ch0Ctl;
    ch0Ctl->err_unit = ch0Info->err_unit;
    ch0Ctl->err_threshold = ch0Info->err_threshold;
    ch0Ctl->request = ch0Info->request;
    //
    ch0Ctl->dmaMode.blen = ch0Info->wbDmaInfo.blen;
    ch0Ctl->dmaMode.continuousmode = ch0Info->wbDmaInfo.continuousmode;
    ch0Ctl->dmaMode.errdetecten = ch0Info->wbDmaInfo.errdetecten;
    ch0Ctl->dmaMode.otnum = ch0Info->wbDmaInfo.otnum;
    ch0Ctl->dmaMode.swap = ch0Info->wbDmaInfo.swap;
    //
    ch0Ctl->infoClr.totalbw = ch0Info->wbInfoClr.totalbw;
    ch0Ctl->infoClr.maxbw = ch0Info->wbInfoClr.maxbw;
    ch0Ctl->infoClr.frmcntclear = ch0Info->wbInfoClr.frmcntclear;
    ch0Ctl->infoClr.fifoerrclear = ch0Info->wbInfoClr.fifoerrclear;
    //
    VO_WB_CH_INFO_S *ch1Info = &wbInfo->ch1Info;
    VO_WB_CH_CTL_S *ch1Ctl = &wbCtl.ch1Ctl;
    ch1Ctl->err_unit = ch1Info->err_unit;
    ch1Ctl->err_threshold = ch1Info->err_threshold;
    ch1Ctl->request = ch1Info->request;
    //
    ch1Ctl->dmaMode.blen = ch1Info->wbDmaInfo.blen;
    ch1Ctl->dmaMode.continuousmode = ch1Info->wbDmaInfo.continuousmode;
    ch1Ctl->dmaMode.errdetecten = ch1Info->wbDmaInfo.errdetecten;
    ch1Ctl->dmaMode.otnum = ch1Info->wbDmaInfo.otnum;
    ch1Ctl->dmaMode.swap = ch1Info->wbDmaInfo.swap;
    //
    ch1Ctl->infoClr.totalbw = ch1Info->wbInfoClr.totalbw;
    ch1Ctl->infoClr.maxbw = ch1Info->wbInfoClr.maxbw;
    ch1Ctl->infoClr.frmcntclear = ch1Info->wbInfoClr.frmcntclear;
    ch1Ctl->infoClr.fifoerrclear = ch1Info->wbInfoClr.fifoerrclear;

    Vo_Drv_Core_SetWB(isp,&wbCtl);
    return;
}
//
static void vo_print_CoreCfg(VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(voCoreInfo); 
    //
    VO_DISP_INFO_S  *dispInfo =  &voCoreInfo->dispInfo;
    printf("dispEnable:0x%x\n",dispInfo->dispEnable);
    printf("xZoneCtl_start:0x%x\n",dispInfo->xZoneCtl_start);
    printf("xZoneCtl_stop:0x%x\n",dispInfo->xZoneCtl_stop);
    printf("yZoneCtl_start:0x%x\n",dispInfo->yZoneCtl_start);
    printf("yZoneCtl_stop:0x%x\n",dispInfo->yZoneCtl_stop);
    printf("dispHsyncCtl_start:0x%x\n",dispInfo->dispHsyncCtl_start);
    printf("dispHsyncCtl_stop:0x%x\n",dispInfo->dispHsyncCtl_stop);
    printf("dispHsync1Ctl_start:0x%x\n",dispInfo->dispHsync1Ctl_start);
    printf("dispHsync1Ctl_stop:0x%x\n",dispInfo->dispHsync1Ctl_stop);
    printf("dispVsync1Ctl_start:0x%x\n",dispInfo->dispVsync1Ctl_start);
    printf("dispVsync1Ctl_stop:0x%x\n",dispInfo->dispVsync1Ctl_stop);
    printf("dispHsync2Ctl_start:0x%x\n",dispInfo->dispHsync2Ctl_start);
    printf("dispHsync2Ctl_stop:0x%x\n",dispInfo->dispHsync2Ctl_stop);
    printf("dispVsync2Ctl_start:0x%x\n",dispInfo->dispVsync2Ctl_start);
    printf("dispVsync2Ctl_stop):0x%x\n",dispInfo->dispVsync2Ctl_stop); 
    printf("vcntbit0    :0x%x\n",dispInfo->vcntbit0    );
    printf("secndfoffset:0x%x\n",dispInfo->secndfoffset);
    printf("framesyncdly:0x%x\n",dispInfo->framesyncdly);
    printf("hsize:0x%x\n",dispInfo->hsize);
    printf("vsize:0x%x\n",dispInfo->vsize);        
    //
    VO_LAYER0_INFO_S *layer0Info =  &voCoreInfo->layer0Info;
    printf("layer0DispE:0x%x\n",layer0Info->layer0DispEn);
    printf("layer0En:0x%x\n",layer0Info->layer0En); 
    printf("scalerBlen:0x%x\n",layer0Info->scalerBlen);
    //layer0
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo = &layer0Info->datModeInfo;
    printf("datmode :0x%x\n",datModeInfo->datmode );
    printf("endiany :0x%x\n",datModeInfo->endiany );
    printf("endianuv:0x%x\n",datModeInfo->endianuv);
    printf("swi:0x%x\n",datModeInfo->swi);
    //
    VO_LAYER_AREA_INFO_S    *areaInfo = &layer0Info->areaInfo;
    printf("xCtl_start:0x%x\n",areaInfo->xCtl_start);
    printf("xCtl_stop:0x%x\n",areaInfo->xCtl_stop);
    printf("yCtl_start:0x%x\n",areaInfo->yCtl_start);
    printf("yCtl_stop:0x%x\n",areaInfo->yCtl_stop);
    //
    VO_YUV_BUF_INFO_S       *buf0Info = &layer0Info->bufInfo;
    printf("yAddr0:0x%x\n",     buf0Info->yAddr0);
    printf("yAddr1:0x%x\n",     buf0Info->yAddr1);
    printf("uvAddr0:0x%x\n",    buf0Info->uvAddr0);
    printf("uvAddr1:0x%x\n",    buf0Info->uvAddr1);
    printf("hsize_stride:0x%x\n",buf0Info->hsize_stride);
    printf("vsize_stride:0x%x\n",buf0Info->vsize_stride);
    //
    VO_LAYER0_SCALE_INFO_S  *scaleInfo = &layer0Info->scaleInfo;
    printf("v_pstep:0x%x\n",scaleInfo->v_pstep);
    printf("v_dstep:0x%x\n",scaleInfo->v_dstep);
    printf("v_pstep_st:0x%x\n",scaleInfo->v_pstep_st);
    printf("h_pstep:0x%x\n",scaleInfo->h_pstep);
    printf("h_dstep:0x%x\n",scaleInfo->h_dstep);
    printf("h_pstep_st:0x%x\n",scaleInfo->h_pstep_st);
    //
    VO_LAYER0_SIZE_INFO_S   *sizeInfo = &layer0Info->sizeInfo;
    printf("offset_hsize:0x%x\n",sizeInfo->offset_hsize);
    printf("offset_vsize:0x%x\n",sizeInfo->offset_vsize);
    printf("in_hsize:0x%x\n",sizeInfo->in_hsize);
    printf("in_vsize:0x%x\n",sizeInfo->in_vsize);
    printf("out_hsize:0x%x\n",sizeInfo->out_hsize);
    printf("out_vsize:0x%x\n",sizeInfo->out_vsize);
    //
    VO_BASE_MODE_INFO_S *baseModeInfo = &layer0Info->baseModeInfo;
    printf("mode:0x%x\n",baseModeInfo->mode);
    printf("base0mask:0x%x\n",baseModeInfo->base0mask);
    printf("base1mask:0x%x\n",baseModeInfo->base1mask);
    printf("addrflag :0x%x\n",baseModeInfo->addrflag );
    //
    VO_LAYER0_MFBD_INFO_S   *mfbdInfo = &layer0Info->mfbdInfo;
    printf("mfbd_en:0x%x\n",mfbdInfo->mfbd_en);
    printf("y_addr0:0x%x\n",mfbdInfo->y_addr0);
    printf("y_stride0:0x%x\n",mfbdInfo->y_stride0);		
    printf("y_addr1:0x%x\n",mfbdInfo->y_addr1);
    printf("y_stride1:0x%x\n",mfbdInfo->y_stride1);
    printf("y_head_addr0:0x%x\n",mfbdInfo->y_head_addr0);
    printf("y_head_stride0:0x%x\n",mfbdInfo->y_head_stride0);
    printf("y_head_addr1:0x%x\n",mfbdInfo->y_head_addr1);
    printf("y_head_stride1:0x%x\n",mfbdInfo->y_head_stride1);
    printf("uv_addr0:0x%x\n",mfbdInfo->uv_addr0);
    printf("uv_stride0:0x%x\n",mfbdInfo->uv_stride0);
    printf("uv_addr1:0x%x\n",mfbdInfo->uv_addr1);
    printf("uv_stride1:0x%x\n",mfbdInfo->uv_stride1); 
    printf("uv_head_addr0:0x%x\n",mfbdInfo->uv_head_addr0);
    printf("uv_head_stride0:0x%x\n",mfbdInfo->uv_head_stride0);
    printf("uv_head_addr1:0x%x\n",mfbdInfo->uv_head_addr1);
    printf("uv_head_stride1:0x%x\n",mfbdInfo->uv_head_stride1); 

    //layer1
    VO_LAYER1_INFO_S *layer1Info =  &voCoreInfo->layer1Info;
    printf("layer1DispEn:0x%x\n",layer1Info->layer1DispEn);
    //
    VO_LAYER_INFO_S *layerInfo = &layer1Info->layerInfo;
    printf("enable  :0x%x\n",layerInfo->enable  );
    printf("yuv422en:0x%x\n",layerInfo->yuv422en);
    printf("yuv420en:0x%x\n",layerInfo->yuv420en);
    printf("endiany :0x%x\n",layerInfo->endiany );
    printf("endianuv:0x%x\n",layerInfo->endianuv);
    printf("uvswap  :0x%x\n",layerInfo->uvswap  );   
    //
    VO_LAYER_AREA_INFO_S *area1Info = &layer1Info->areaInfo;
    printf("xCtl_start:0x%x\n",area1Info->xCtl_start);
    printf("xCtl_stop:0x%x\n",area1Info->xCtl_stop);
    printf("yCtl_start:0x%x\n",area1Info->yCtl_start);
    printf("yCtl_stop:0x%x\n",area1Info->yCtl_stop);
    //
    VO_YUV_BUF_INFO_S *buf1Info = &layer1Info->bufInfo;
    printf("yAddr0:0x%x\n",     buf1Info->yAddr0);
    printf("yAddr1:0x%x\n",     buf1Info->yAddr1);
    printf("uvAddr0:0x%x\n",    buf1Info->uvAddr0);
    printf("uvAddr1:0x%x\n",    buf1Info->uvAddr1);
    printf("hsize_stride:0x%x\n",buf1Info->hsize_stride);
    printf("vsize_stride:0x%x\n",buf1Info->vsize_stride);
    //
    VO_LAYER_SIZE_INFO_S *layer1SizeInfo = &layer1Info->layer1SizeInfo;
    printf("offset_hsize:0x%x\n",layer1SizeInfo->offset_hsize);
    printf("offset_vsize:0x%x\n",layer1SizeInfo->offset_vsize);
    printf("in_hsize:0x%x\n",    layer1SizeInfo->in_hsize);
    printf("in_vsize:0x%x\n",    layer1SizeInfo->in_vsize);     
    //
    VO_IMG_IN_BLENTH_INFO_S *img1InBlenthInfo = &layer1Info->imgInBlenthInfo; 
    printf("blen   :0x%x\n",img1InBlenthInfo->blen   );
    printf("voffset:0x%x\n",img1InBlenthInfo->voffset);
    //
    VO_BASE_MODE_INFO_S *base1ModeInfo = &layer1Info->baseModeInfo; 
    printf("mode:0x%x\n",base1ModeInfo->mode);
    printf("base0mask:0x%x\n",base1ModeInfo->base0mask);
    printf("base1mask:0x%x\n",base1ModeInfo->base1mask);
    printf("addrflag :0x%x\n",base1ModeInfo->addrflag );

    //layer2
    VO_LAYER2_INFO_S *layer2Info =  &voCoreInfo->layer2Info;
    printf("layer2DispEn:0x%x\n",layer2Info->layer2DispEn);
    //
    VO_LAYER_INFO_S *layer2 = &layer2Info->layerInfo;
    printf("enable  :0x%x\n",layer2->enable   );
    printf("yuv422en:0x%x\n",layer2->yuv422en );
    printf("yuv420en:0x%x\n",layer2->yuv420en );
    printf("endiany :0x%x\n",layer2->endiany  );
    printf("endianuv:0x%x\n",layer2->endianuv );
    printf("uvswap  :0x%x\n",layer2->uvswap   );   
    //
    VO_LAYER_AREA_INFO_S *area2Info = &layer2Info->areaInfo;
    printf("xCtl_start:0x%x\n",area2Info->xCtl_start);
    printf("xCtl_stop:0x%x\n",area2Info->xCtl_stop);
    printf("yCtl_start:0x%x\n",area2Info->yCtl_start);
    printf("yCtl_stop:0x%x\n",area2Info->yCtl_stop);
    //
    VO_YUV_BUF_INFO_S *buf2Info = &layer2Info->bufInfo;
    printf("yAddr0:0x%x\n",     buf2Info->yAddr0);
    printf("yAddr1:0x%x\n",     buf2Info->yAddr1);
    printf("uvAddr0:0x%x\n",    buf2Info->uvAddr0);
    printf("uvAddr1:0x%x\n",    buf2Info->uvAddr1);
    printf("hsize_stride:0x%x\n",buf2Info->hsize_stride);
    printf("vsize_stride:0x%x\n",buf2Info->vsize_stride);
    //
    VO_LAYER_SIZE_INFO_S *layer2SizeInfo = &layer2Info->layer2SizeInfo; 
    printf("offset_hsize:0x%x\n",layer2SizeInfo->offset_hsize);
    printf("offset_vsize:0x%x\n",layer2SizeInfo->offset_vsize);
    printf("in_hsize:0x%x\n",    layer2SizeInfo->in_hsize);
    printf("in_vsize:0x%x\n",    layer2SizeInfo->in_vsize);   
    //
    VO_IMG_IN_BLENTH_INFO_S *img2InBlenthInfo = &layer2Info->imgInBlenthInfo;
    printf("blen   :0x%x\n",img2InBlenthInfo->blen   );
    printf("voffset:0x%x\n",img2InBlenthInfo->voffset);
    //
    VO_BASE_MODE_INFO_S *base2ModeInfo = &layer2Info->baseModeInfo; 
    printf("mode:0x%x\n",     base2ModeInfo->mode);
    printf("base0mask:0x%x\n",base2ModeInfo->base0mask);
    printf("base1mask:0x%x\n",base2ModeInfo->base1mask);
    printf("addrflag :0x%x\n",base2ModeInfo->addrflag );

    //layer3
    VO_LAYER3_INFO_S *layer3Info =  &voCoreInfo->layer3Info;
    printf("layer3DispEn:0x%x\n",layer3Info->layer3DispEn);
    //
    VO_LAYER_INFO_S         *layer3 =  &layer3Info->layerInfo;
    printf("enable  :0x%x\n",layer3->enable   );
    printf("yuv422en:0x%x\n",layer3->yuv422en );
    printf("yuv420en:0x%x\n",layer3->yuv420en );
    printf("endiany :0x%x\n",layer3->endiany  );
    printf("endianuv:0x%x\n",layer3->endianuv );
    printf("uvswap  :0x%x\n",layer3->uvswap   );    
    //*
    VO_LAYER_AREA_INFO_S    *area3Info =  &layer3Info->areaInfo;
    printf("xCtl_start:0x%x\n",area3Info->xCtl_start);
    printf("xCtl_stop:0x%x\n",area3Info->xCtl_stop);
    printf("yCtl_start:0x%x\n",area3Info->yCtl_start);
    printf("yCtl_stop:0x%x\n",area3Info->yCtl_stop);
    //*
    VO_YUV_BUF_INFO_S       *buf3Info =  &layer3Info->bufInfo;
    printf("yAddr0:0x%x\n",     buf3Info->yAddr0);
    printf("yAddr1:0x%x\n",     buf3Info->yAddr1);
    printf("uvAddr0:0x%x\n",    buf3Info->uvAddr0);
    printf("uvAddr1:0x%x\n",    buf3Info->uvAddr1);
    printf("hsize_stride:0x%x\n",buf3Info->hsize_stride);
    printf("vsize_stride:0x%x\n",buf3Info->vsize_stride);
    //*
    VO_LAYER_SIZE_INFO_S    *layer3SizeInfo =  &layer3Info->layer3SizeInfo;
    printf("offset_hsize:0x%x\n",layer3SizeInfo->offset_hsize);
    printf("offset_vsize:0x%x\n",layer3SizeInfo->offset_vsize);
    printf("in_hsize:0x%x\n",    layer3SizeInfo->in_hsize);
    printf("in_vsize:0x%x\n",    layer3SizeInfo->in_vsize);    
    //*
    VO_IMG_IN_BLENTH_INFO_S *img3InBlenthInfo =  &layer3Info->imgInBlenthInfo;
    printf("blen   :0x%x\n",img3InBlenthInfo->blen   );
    printf("voffset:0x%x\n",img3InBlenthInfo->voffset);
    //*
    VO_BASE_MODE_INFO_S     *base3ModeInfo =  &layer3Info->baseModeInfo; 
    printf("mode:0x%x\n",     base3ModeInfo->mode);
    printf("base0mask:0x%x\n",base3ModeInfo->base0mask);
    printf("base1mask:0x%x\n",base3ModeInfo->base1mask);
    printf("addrflag :0x%x\n",base3ModeInfo->addrflag );

    //osd0
    VO_OSD0_INFO_S   *osd0Info =  &voCoreInfo->osd0Info;
    printf("osdLayer4DispEn:0x%x\n",osd0Info->osdLayer4DispEn);
    printf("osdrgb2yuvEn:0x%x\n",   osd0Info->osdrgb2yuvEn);
    printf("osdtype:0x%x\n",        osd0Info->osdtype);
    printf("alphatpye:0x%x\n",      osd0Info->alphatpye);

    VO_LAYER_AREA_INFO_S   *osd0AreaInfo =  &osd0Info->osd0AreaInfo;
    printf("xCtl_start:0x%x\n",osd0AreaInfo->xCtl_start);
    printf("xCtl_stop:0x%x\n",osd0AreaInfo->xCtl_stop);
    printf("yCtl_start:0x%x\n",osd0AreaInfo->yCtl_start);
    printf("yCtl_stop:0x%x\n",osd0AreaInfo->yCtl_stop);

    VO_OSD_SIZE_INFO_S     *osd0SizeInfo =  &osd0Info->osd0SizeInfo;
    printf("width :0x%x\n",osd0SizeInfo->width);
    printf("height:0x%x\n",osd0SizeInfo->height); 

    VO_OSD_BUF_INFO_S      *osd0BufInfo =  &osd0Info->osd0BufInfo;
    printf("alp_addr0:0x%x\n",osd0BufInfo->alp_addr0);
    printf("alp_addr1:0x%x\n",osd0BufInfo->alp_addr1);
    printf("alpstride:0x%x\n",osd0BufInfo->alpstride);
    printf("vlu_addr0:0x%x\n",osd0BufInfo->vlu_addr0);
    printf("vlu_addr1:0x%x\n",osd0BufInfo->vlu_addr1);
    printf("osdstride:0x%x\n",osd0BufInfo->osdstride);

    VO_BASE_MODE_INFO_S    *osd0BaseModeInfo =  &osd0Info->osd0BaseModeInfo;
    printf("mode:0x%x\n",     osd0BaseModeInfo->mode);
    printf("base0mask:0x%x\n",osd0BaseModeInfo->base0mask);
    printf("base1mask:0x%x\n",osd0BaseModeInfo->base1mask);
    printf("addrflag :0x%x\n",osd0BaseModeInfo->addrflag );

    VO_OSD_DMA_INFO_S      *osd0DmaInfo =  &osd0Info->osd0DmaInfo; 
    printf("dmarequestlen:0x%x\n",osd0DmaInfo->dmarequestlen);
    printf("dmamap       :0x%x\n",osd0DmaInfo->dmamap       );
    printf("rgbrev       :0x%x\n",osd0DmaInfo->rgbrev       );
    //osd1
    VO_OSD1_INFO_S   *osd1Info =  &voCoreInfo->osd1Info;
    printf("osdLayer5DispEn:0x%x\n",osd1Info->osdLayer5DispEn);
    printf("osdrgb2yuvEn:0x%x\n",   osd1Info->osdrgb2yuvEn);
    printf("osdtype:0x%x\n",        osd1Info->osdtype);
    printf("alphatpye:0x%x\n",      osd1Info->alphatpye);

    VO_LAYER_AREA_INFO_S   *osd1AreaInfo =  &osd1Info->osd1AreaInfo;
    printf("xCtl_start:0x%x\n",osd1AreaInfo->xCtl_start);
    printf("xCtl_stop:0x%x\n",osd1AreaInfo->xCtl_stop);
    printf("yCtl_start:0x%x\n",osd1AreaInfo->yCtl_start);
    printf("yCtl_stop:0x%x\n",osd1AreaInfo->yCtl_stop);

    VO_OSD_SIZE_INFO_S     *osd1SizeInfo =  &osd1Info->osd1SizeInfo;
    printf("width :0x%x\n",osd1SizeInfo->width);
    printf("height:0x%x\n",osd1SizeInfo->height);  

    VO_OSD_BUF_INFO_S      *osd1BufInfo =  &osd1Info->osd1BufInfo;
    printf("alp_addr0:0x%x\n",osd1BufInfo->alp_addr0);
    printf("alp_addr1:0x%x\n",osd1BufInfo->alp_addr1);
    printf("alpstride:0x%x\n",osd1BufInfo->alpstride);
    printf("vlu_addr0:0x%x\n",osd1BufInfo->vlu_addr0);
    printf("vlu_addr1:0x%x\n",osd1BufInfo->vlu_addr1);
    printf("osdstride:0x%x\n",osd1BufInfo->osdstride);

    VO_BASE_MODE_INFO_S    *osd1BaseModeInfo =  &osd1Info->osd1BaseModeInfo;
    printf("mode:0x%x\n",     osd1BaseModeInfo->mode);
    printf("base0mask:0x%x\n",osd1BaseModeInfo->base0mask);
    printf("base1mask:0x%x\n",osd1BaseModeInfo->base1mask);
    printf("addrflag :0x%x\n",osd1BaseModeInfo->addrflag );

    VO_OSD_DMA_INFO_S      *osd1DmaInfo =  &osd1Info->osd1DmaInfo;
    printf("dmarequestlen:0x%x\n",osd1DmaInfo->dmarequestlen);
    printf("dmamap       :0x%x\n",osd1DmaInfo->dmamap       );
    printf("rgbrev       :0x%x\n",osd1DmaInfo->rgbrev       );
    //osd2
    VO_OSD2_INFO_S   *osd2Info =  &voCoreInfo->osd2Info;
    printf("osdLayer6DispEn:0x%x\n",osd2Info->osdLayer6DispEn);
    printf("osdrgb2yuvEn:0x%x\n",   osd2Info->osdrgb2yuvEn);
    printf("osdtype:0x%x\n",        osd2Info->osdtype);
    printf("alphatpye:0x%x\n",      osd2Info->alphatpye);

    VO_LAYER_AREA_INFO_S   *osd2AreaInfo=  &osd2Info->osd2AreaInfo;
    printf("xCtl_start:0x%x\n",osd2AreaInfo->xCtl_start);
    printf("xCtl_stop:0x%x\n",osd2AreaInfo->xCtl_stop);
    printf("yCtl_start:0x%x\n",osd2AreaInfo->yCtl_start);
    printf("yCtl_stop:0x%x\n",osd2AreaInfo->yCtl_stop);

    VO_OSD_SIZE_INFO_S     *osd2SizeInfo=  &osd2Info->osd2SizeInfo;
    printf("width :0x%x\n",osd2SizeInfo->width);
    printf("height:0x%x\n",osd2SizeInfo->height);  

    VO_OSD_BUF_INFO_S      *osd2BufInfo=  &osd2Info->osd2BufInfo;
    printf("alp_addr0:0x%x\n",osd2BufInfo->alp_addr0);
    printf("alp_addr1:0x%x\n",osd2BufInfo->alp_addr1);
    printf("alpstride:0x%x\n",osd2BufInfo->alpstride);
    printf("vlu_addr0:0x%x\n",osd2BufInfo->vlu_addr0);
    printf("vlu_addr1:0x%x\n",osd2BufInfo->vlu_addr1);
    printf("osdstride:0x%x\n",osd2BufInfo->osdstride);

    VO_BASE_MODE_INFO_S    *osd2BaseModeInfo=  &osd2Info->osd2BaseModeInfo;
    printf("mode:0x%x\n",     osd2BaseModeInfo->mode);
    printf("base0mask:0x%x\n",osd2BaseModeInfo->base0mask);
    printf("base1mask:0x%x\n",osd2BaseModeInfo->base1mask);
    printf("addrflag :0x%x\n",osd2BaseModeInfo->addrflag );

    VO_OSD_DMA_INFO_S      *osd2DmaInfo=  &osd2Info->osd2DmaInfo;
    printf("dmarequestlen:0x%x\n",osd2DmaInfo->dmarequestlen);
    printf("dmamap       :0x%x\n",osd2DmaInfo->dmamap       );
    printf("rgbrev       :0x%x\n",osd2DmaInfo->rgbrev       );
    //rgb3yuv
    VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo =  &voCoreInfo->osdRgb2YuvInfo;
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 4;j++)
    {
        printf("osdrgb2yuv_coeff[%d][%d]:0x%x\n",i,j,osdRgb2YuvInfo->osdrgb2yuv_coeff[i][j]);
    }
    //yuv2rgb
    VO_YUV2RGB_INFO_S   *yuv2rgbInfo =  &voCoreInfo->yuv2rgbInfo;  
    printf("yuv2rgb_ctl_en:0x%x\n",yuv2rgbInfo->yuv2rgb_ctl_en);
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 4;j++)
    {
        printf("yuv2rgb_coeff[%d][%d]:0x%x\n",i,j,yuv2rgbInfo->yuv2rgb_coeff[i][j]);
    }
    //
    VO_DISP_MIX_INFO_S  *dispMixCtlInfo =  &voCoreInfo->dispMixCtlInfo;
    VO_MIX_INFO_S *layerMixInfo = &dispMixCtlInfo->layerMixInfo[0];
    for(int i = 0;i<7;i++)
    {
        printf("glben[%d]:0x%x\n",i,layerMixInfo[i].glben);
        printf("glbalp[%d]:0x%x\n",i,layerMixInfo[i].glbalp);
        printf("sel[%d]:0x%x\n",i,layerMixInfo[i].sel);
    }
    VO_DISP_BACK_GROUD_INFO_S *dispBackGroudInfo = &dispMixCtlInfo->dispBackGroudInfo;
    printf("groud y:0x%x\n",dispBackGroudInfo->y);
    printf("groud u:0x%x\n",dispBackGroudInfo->u);
    printf("groud v:0x%x\n",dispBackGroudInfo->v);
    //
    printf("ditherctlen:0x%x\n",voCoreInfo->ditherctlen);
    printf("clutctlen:0x%x\n",voCoreInfo->clutctlen);
    return;
}
//
static int Vo_Remap_FillCmd(struct isp_device *isp,struct _VO_REMAP_CMD_INfO_S *cmd_info);
//
static int Vo_SetCore(struct isp_vo_device *vo,VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(vo);
    VO_CHECK_POINTER(voCoreInfo);

    struct isp_device *isp = to_isp_device(vo);
    //
    VO_DISP_INFO_S *dispInfo = &voCoreInfo->dispInfo;
    Vo_Core_SetDisp(isp,dispInfo);
    //
    VO_LAYER0_INFO_S *layer0Info = &voCoreInfo->layer0Info;
    Vo_Core_SetLayer0(isp,layer0Info);
    //
    VO_LAYER1_INFO_S *layer1Info =  &voCoreInfo->layer1Info;
    Vo_Core_SetLayer1(isp,layer1Info);
    //
    VO_LAYER2_INFO_S *layer2Info =  &voCoreInfo->layer2Info;
    Vo_Core_SetLayer2(isp,layer2Info);
    //
    VO_LAYER3_INFO_S *layer3Info = &voCoreInfo->layer3Info;
    Vo_Core_SetLayer3(isp,layer3Info);
    //
    VO_OSD0_INFO_S *osd0Info = &voCoreInfo->osd0Info;
    Vo_Core_SetOsd0(isp,osd0Info);
    //
    VO_OSD1_INFO_S *osd1Info = &voCoreInfo->osd1Info;
    Vo_Core_SetOsd1(isp,osd1Info);
    //
    VO_OSD2_INFO_S *osd2Info = &voCoreInfo->osd2Info;
    Vo_Core_SetOsd2(isp,osd2Info);
    //
    VO_OSD_RGB2YUV_INFO_S *osdRgb2YuvInfo = &voCoreInfo->osdRgb2YuvInfo;
    Vo_Core_SetOsdRgb2Yuv(isp,osdRgb2YuvInfo);
    //
    VO_YUV2RGB_INFO_S *yuv2rgbInfo = &voCoreInfo->yuv2rgbInfo;
    Vo_Core_SetYuv2Rgb(isp,yuv2rgbInfo); 
    //
    //VO_DISP_MIX_INFO_S *dispMixCtlInfo = &voCoreInfo->dispMixCtlInfo;
    //Vo_Core_SetDispMixCtl(isp,dispMixCtlInfo);
    Vo_Core_SetDispMixCtl(isp,voCoreInfo);
    //
    VO_DISP_IRQ_INFO_S *dispIrqInfo = &voCoreInfo->dispIrqInfo;
    Vo_Core_SetDispIrq(isp,dispIrqInfo);
    //
    //VO_WB_INFO_S *wbInfo = &voCoreInfo->wbInfo;
    //Vo_Core_SetWB(isp,wbInfo);
    //
    VO_REMAP_CMD_INfO_S *cmd_info = &voCoreInfo->remapcmdInfo; 
    Vo_Remap_FillCmd(isp,cmd_info);

    return 0;
}
//
static int Vo_VideoOut(struct isp_device *isp,VO_CORE_INFO_S *voCoreInfo)
{
    VO_CHECK_POINTER(isp);
    VO_CHECK_POINTER(voCoreInfo);
    struct isp_vo_device *vo = &isp->isp_vo;
    //
    Vo_Init(vo);
    //
    Vo_Table_init(vo);
    //
    Vo_SetWrap(vo);
    //
    Vo_SetCore(vo,voCoreInfo);
    //
    Vo_Start(vo);
    return 0;
}
//
int Vo_Out_Init(struct isp_device *isp)
{
    VO_CHECK_POINTER(isp);
    struct isp_vo_device *vo = &isp->isp_vo;

    VO_CORE_INFO_S *voCoreInfo = &vo->vo_core_info;
    //
    Vo_Init(vo);
    //
    Vo_Table_init(vo);
    //
    Vo_SetWrap(vo);
    //
    Vo_SetCore(vo,voCoreInfo);
    //
    Vo_Start(vo);
    return 0;
}
//
static void Vo_Core_GetHdmiCfg(VO_CORE_INFO_S *voCoreInfo,VO_ADDR_INFO *vo_addr,VO_SIZE_S *vo_size,OSD_INFO *osd1_info)
{
    ISP_CHECK_POINTER(voCoreInfo);
    ISP_CHECK_POINTER(vo_addr);
    ISP_CHECK_POINTER(vo_size);
    ISP_CHECK_POINTER(osd1_info);

    int v_offset = 0x2a;//14;
    int h_offset = 0xc6;//16;//46;
    //
    VO_DISP_INFO_S *dispInfo = &voCoreInfo->dispInfo;
    dispInfo->dispEnable    = 1;
    dispInfo->xZoneCtl_start= VIDEO_DISP_ZONE_X_START;
    dispInfo->xZoneCtl_stop = VIDEO_DISP_ZONE_X_STOP;
    dispInfo->yZoneCtl_start = VIDEO_DISP_ZONE_Y_START;
    dispInfo->yZoneCtl_stop = VIDEO_DISP_ZONE_Y_STOP;
    dispInfo->hsize = 0x898;
    dispInfo->vsize = 0x465;        

    //layer0
    VO_LAYER0_INFO_S *layer0Info = &voCoreInfo->layer0Info;
    layer0Info->layer0DispEn = 0;//vo_addr->layer2_en;//0;
    layer0Info->layer0En = 0;//vo_addr->layer2_en;//0;
    //
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo = &layer0Info->datModeInfo;
    datModeInfo->datmode = 0x8;
    datModeInfo->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    datModeInfo->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    datModeInfo->swi = 0;
    //
    VO_LAYER0_SIZE_INFO_S *sizeInfo = &layer0Info->sizeInfo;
    sizeInfo->offset_hsize = 0;
    sizeInfo->offset_vsize = 0;
    sizeInfo->in_hsize = vo_size->layer2_size.Width;
    sizeInfo->in_vsize = vo_size->layer2_size.Height;
    sizeInfo->out_hsize = vo_size->layer2_size.Width;
    sizeInfo->out_vsize = vo_size->layer2_size.Height;
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer0Info->areaInfo;
    areaInfo->xCtl_start = h_offset + 1200;
    areaInfo->xCtl_stop = areaInfo->xCtl_start + sizeInfo->out_hsize;
    areaInfo->yCtl_start = v_offset;
    areaInfo->yCtl_stop = areaInfo->yCtl_start + sizeInfo->out_vsize;    
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer0Info->bufInfo;
    bufInfo->hsize_stride = vo_addr->layer2_stride;
    bufInfo->yAddr0 = vo_addr->layer2_baseaddr;
    bufInfo->yAddr1 = vo_addr->layer2_baseaddr;
    bufInfo->uvAddr0 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * sizeInfo->in_vsize;
    bufInfo->uvAddr1 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * sizeInfo->in_vsize;
    bufInfo->vsize_stride = sizeInfo->in_vsize;
    //
    VO_LAYER0_MFBD_INFO_S *mfbdInfo = &layer0Info->mfbdInfo;
    mfbdInfo->mfbd_en = 0;

    //layer1
    VO_LAYER1_INFO_S *layer1Info = &voCoreInfo->layer1Info;
    layer1Info->layer1DispEn = vo_addr->layer1_en;//0;//vo_addr->layer1_en;
    layer1Info->layerInfo.enable = vo_addr->layer1_en;//0;//vo_addr->layer1_en;
    layer1Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer1Info->layerInfo.uvswap = 0;
    layer1Info->layerInfo.yuv420en = 1;
    layer1Info->layerInfo.yuv422en = 0;

    layer1Info->layer1SizeInfo.in_hsize = vo_size->layer1_size.Width;
    layer1Info->layer1SizeInfo.in_vsize = vo_size->layer1_size.Height;

    layer1Info->bufInfo.hsize_stride = vo_addr->layer1_stride;
    layer1Info->bufInfo.vsize_stride = vo_size->layer1_size.Height;
    layer1Info->bufInfo.yAddr0  = vo_addr->layer1_baseaddr;
    layer1Info->bufInfo.yAddr1  = vo_addr->layer1_baseaddr;
    layer1Info->bufInfo.uvAddr0 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;
    layer1Info->bufInfo.uvAddr1 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;

    layer1Info->areaInfo.xCtl_start = h_offset;
    layer1Info->areaInfo.xCtl_stop  = h_offset + vo_size->layer1_size.Width;
    layer1Info->areaInfo.yCtl_start = v_offset;
    layer1Info->areaInfo.yCtl_stop  = v_offset + vo_size->layer1_size.Height;
    //
    //layer2
    VO_LAYER2_INFO_S *layer2Info = &voCoreInfo->layer2Info;
    layer2Info->layer2DispEn = vo_addr->layer2_en;//0; //vo_addr->layer1_en;
    layer2Info->layerInfo.enable = vo_addr->layer2_en;//0;//vo_addr->layer1_en;
    
    layer2Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Info->layerInfo.uvswap = 0;
    layer2Info->layerInfo.yuv420en = 1;
    layer2Info->layerInfo.yuv422en = 0;

    layer2Info->layer2SizeInfo.in_hsize = vo_size->layer2_size.Width;
    layer2Info->layer2SizeInfo.in_vsize = vo_size->layer2_size.Height;

    layer2Info->bufInfo.hsize_stride = vo_addr->layer2_stride;
    layer2Info->bufInfo.vsize_stride = vo_size->layer2_size.Height;
    layer2Info->bufInfo.yAddr0  = vo_addr->layer2_baseaddr;
    layer2Info->bufInfo.yAddr1  = vo_addr->layer2_baseaddr;
    layer2Info->bufInfo.uvAddr0 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * vo_size->layer2_size.Height;
    layer2Info->bufInfo.uvAddr1 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * vo_size->layer2_size.Height;

    layer2Info->areaInfo.xCtl_start = h_offset + 1200;
    layer2Info->areaInfo.xCtl_stop  = h_offset + vo_size->layer2_size.Width;
    layer2Info->areaInfo.yCtl_start = v_offset;
    layer2Info->areaInfo.yCtl_stop  = v_offset + vo_size->layer2_size.Height;
    //layer3
    VO_LAYER3_INFO_S *layer3Info = &voCoreInfo->layer3Info;
    layer3Info->layer3DispEn = 0;//vo_addr->layer1_en;//
    layer3Info->layerInfo.enable = 0;//vo_addr->layer1_en;//

    layer3Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer3Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer3Info->layerInfo.uvswap = 0;
    layer3Info->layerInfo.yuv420en = 1;
    layer3Info->layerInfo.yuv422en = 0;

    layer3Info->layer3SizeInfo.in_hsize = vo_size->layer1_size.Width;
    layer3Info->layer3SizeInfo.in_vsize = vo_size->layer1_size.Height;

    layer3Info->bufInfo.hsize_stride = vo_addr->layer1_stride;
    layer3Info->bufInfo.vsize_stride = vo_size->layer1_size.Height;
    layer3Info->bufInfo.yAddr0  = vo_addr->layer1_baseaddr;
    layer3Info->bufInfo.yAddr1  = vo_addr->layer1_baseaddr;
    layer3Info->bufInfo.uvAddr0 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;
    layer3Info->bufInfo.uvAddr1 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;

    layer3Info->areaInfo.xCtl_start = h_offset;
    layer3Info->areaInfo.xCtl_stop  = h_offset + vo_size->layer1_size.Width;
    layer3Info->areaInfo.yCtl_start = v_offset;
    layer3Info->areaInfo.yCtl_stop  = v_offset + vo_size->layer1_size.Height;

    //osd0
    VO_OSD0_INFO_S  *osd0Info = &voCoreInfo->osd0Info;
    osd0Info->osdLayer4DispEn = vo_addr->osd0_en;//0;
    osd0Info->osdrgb2yuvEn = vo_addr->osd0_en;//1;

    osd0Info->osdtype  = OSD_RGB_32BIT;
    osd0Info->alphatpye = OSD_FIXED_VALUE;
    unsigned int osd0_stride = vo_addr->osd0_stride*4;
    if( DS2_S_RGB == vo_addr->osd0_rgb_type )
    {
        osd0_stride = vo_addr->osd0_stride;
        osd0Info->osdtype = OSD_MONOCHROME_8BIT; 
    }
    //
    VO_OSD_SIZE_INFO_S   *osd0SizeInfo = &osd0Info->osd0SizeInfo;
    osd0SizeInfo->width = vo_size->osd0_size.Width;
    osd0SizeInfo->height = vo_size->osd0_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    osd0AreaInfo->xCtl_start = h_offset;// + 1280;
    osd0AreaInfo->xCtl_stop = osd0AreaInfo->xCtl_start + osd0SizeInfo->width;
    osd0AreaInfo->yCtl_start = v_offset + 800;
    osd0AreaInfo->yCtl_stop = osd0AreaInfo->yCtl_start + osd0SizeInfo->height;

    //
    VO_OSD_BUF_INFO_S    *osd0BufInfo = &osd0Info->osd0BufInfo;
    osd0BufInfo->alpstride = osd0_stride; 
    osd0BufInfo->osdstride = osd0_stride; 
    osd0BufInfo->alp_addr0 = vo_addr->osd0_baseaddr;
    osd0BufInfo->alp_addr1 = vo_addr->osd0_baseaddr;
    osd0BufInfo->vlu_addr0 = vo_addr->osd0_baseaddr;
    osd0BufInfo->vlu_addr1 = vo_addr->osd0_baseaddr;                

    VO_OSD_DMA_INFO_S    *osd0DmaInfo = &osd0Info->osd0DmaInfo; 
    osd0DmaInfo->rgbrev = OSD_RGB_REV_B;//
    //osd1
    VO_OSD1_INFO_S  *osd1Info = &voCoreInfo->osd1Info;
    osd1Info->osdLayer5DispEn = vo_addr->osd1_en;//0;
    osd1Info->osdrgb2yuvEn = vo_addr->osd1_en;//1;

    osd1Info->osdtype   = osd1_info->osd1_type;
    osd1Info->alphatpye = OSD_FIXED_VALUE;
    //
    VO_OSD_SIZE_INFO_S *osd1SizeInfo = &osd1Info->osd1SizeInfo;
    osd1SizeInfo->width = vo_size->osd1_size.Width;
    osd1SizeInfo->height = vo_size->osd1_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    osd1AreaInfo->xCtl_start = h_offset+1280;
    osd1AreaInfo->xCtl_stop = osd1AreaInfo->xCtl_start + osd1SizeInfo->width;
    osd1AreaInfo->yCtl_start = v_offset+500;
    osd1AreaInfo->yCtl_stop = osd1AreaInfo->yCtl_start + osd1SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd1BufInfo  = &osd1Info->osd1BufInfo;
    osd1BufInfo->alpstride = vo_addr->osd1_stride; 
    osd1BufInfo->osdstride = vo_addr->osd1_stride;

    if(osd1_info->osd1_type == OSD_RGB_32BIT)
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride*4; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride*4;  
    }
    else if(osd1_info->osd1_type == OSD_RGB_24BIT)
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride*3; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride*3;  
    }
    else
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride;  
    }
    osd1BufInfo->alp_addr0 = vo_addr->osd1_baseaddr;
    osd1BufInfo->alp_addr1 = vo_addr->osd1_baseaddr;
    osd1BufInfo->vlu_addr0 = vo_addr->osd1_baseaddr;
    osd1BufInfo->vlu_addr1 = vo_addr->osd1_baseaddr;
    //
    VO_OSD_DMA_INFO_S *osd1DmaInfo = &osd1Info->osd1DmaInfo;
    osd1DmaInfo->rgbrev = osd1_info->osd1_rgb_rev;
    osd1DmaInfo->dmamap = osd1_info->osd1_dma_ctl;

    //osd2
    VO_OSD2_INFO_S  *osd2Info = &voCoreInfo->osd2Info;
    osd2Info->osdLayer6DispEn = vo_addr->osd1_en;//0;
    osd2Info->osdrgb2yuvEn = vo_addr->osd1_en;//1;

    osd2Info->osdtype   = osd1_info->osd1_type;
    osd2Info->alphatpye = OSD_FIXED_VALUE;
    //
    VO_OSD_SIZE_INFO_S *osd2SizeInfo = &osd2Info->osd2SizeInfo;
    osd2SizeInfo->width = vo_size->osd1_size.Width;
    osd2SizeInfo->height = vo_size->osd1_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    osd2AreaInfo->xCtl_start = h_offset+1080;
    osd2AreaInfo->xCtl_stop = osd2AreaInfo->xCtl_start + osd2SizeInfo->width;
    osd2AreaInfo->yCtl_start = v_offset+600;
    osd2AreaInfo->yCtl_stop = osd2AreaInfo->yCtl_start + osd2SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd2BufInfo  = &osd2Info->osd2BufInfo;
    osd2BufInfo->alpstride = vo_addr->osd1_stride; 
    osd2BufInfo->osdstride = vo_addr->osd1_stride;

    if(osd1_info->osd1_type == OSD_RGB_32BIT)
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride*4; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride*4;  
    }
    else if(osd1_info->osd1_type == OSD_RGB_24BIT)
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride*3; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride*3;  
    }
    else
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride;  
    }
    osd2BufInfo->alp_addr0 = vo_addr->osd1_baseaddr;
    osd2BufInfo->alp_addr1 = vo_addr->osd1_baseaddr;
    osd2BufInfo->vlu_addr0 = vo_addr->osd1_baseaddr;
    osd2BufInfo->vlu_addr1 = vo_addr->osd1_baseaddr;
    //
    VO_OSD_DMA_INFO_S *osd2DmaInfo = &osd2Info->osd2DmaInfo;
    osd2DmaInfo->rgbrev = osd1_info->osd1_rgb_rev;
    osd2DmaInfo->dmamap = osd1_info->osd1_dma_ctl;

    //
    voCoreInfo->clutctlen = 0;
    voCoreInfo->ditherctlen = 1;
    //
    VO_REMAP_CMD_INfO_S *remapcmdInfo = &voCoreInfo->remapcmdInfo;
    remapcmdInfo->image_active_h = 1920;
    remapcmdInfo->image_active_v = 1080;
    remapcmdInfo->vo_out_imgtype = 0; //rgb dsi
    return;
}
//
int Vo_VideoOut_Hdmi(struct isp_device *isp,VO_ADDR_INFO *vo_addr,VO_SIZE_S *vo_size,OSD_INFO *osd1_info)
{
    VO_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(vo_addr);
    ISP_CHECK_POINTER(vo_size);
    ISP_CHECK_POINTER(osd1_info);

    VO_CORE_INFO_S voCoreInfo;
    memcpy(&voCoreInfo,&hdmi_vo_info,sizeof(VO_CORE_INFO_S));

    Vo_Core_GetHdmiCfg(&voCoreInfo,vo_addr,vo_size,osd1_info);

    vo_print_CoreCfg(&voCoreInfo);

    Vo_VideoOut(isp,&voCoreInfo);

    return 0;
}
//
void Vo_Core_GetDsiCfg(VO_CORE_INFO_S *voCoreInfo,VO_ADDR_INFO *vo_addr,VO_SIZE_S *vo_size,OSD_INFO *osd1_info)
{
    ISP_CHECK_POINTER(voCoreInfo);
    ISP_CHECK_POINTER(vo_addr);
    ISP_CHECK_POINTER(vo_size);
    ISP_CHECK_POINTER(osd1_info);

    int v_offset = 14;//14;
    int h_offset = 16;//16;//46;
    //
    VO_DISP_INFO_S *dispInfo = &voCoreInfo->dispInfo;
    dispInfo->dispEnable    = 1;
    dispInfo->xZoneCtl_start= 0x2e;
    dispInfo->xZoneCtl_stop = 0x465;
    dispInfo->yZoneCtl_start = 0xe;
    dispInfo->yZoneCtl_stop = 0x78d;
    dispInfo->hsize = 0x53c;
    dispInfo->vsize = 0x7a6;        

    //layer0
    VO_LAYER0_INFO_S *layer0Info = &voCoreInfo->layer0Info;
    layer0Info->layer0DispEn = 0;//vo_addr->layer2_en;//0;
    layer0Info->layer0En = 0;//vo_addr->layer2_en;//0;
    //
    VO_LAYER0_DAT_MODE_INFO_S *datModeInfo = &layer0Info->datModeInfo;
    datModeInfo->datmode = 0x8;
    datModeInfo->endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    datModeInfo->endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    datModeInfo->swi = 0;
    //
    VO_LAYER0_SIZE_INFO_S *sizeInfo = &layer0Info->sizeInfo;
    sizeInfo->offset_hsize = 0;
    sizeInfo->offset_vsize = 0;
    sizeInfo->in_hsize = vo_size->layer2_size.Width;
    sizeInfo->in_vsize = vo_size->layer2_size.Height;
    sizeInfo->out_hsize = vo_size->layer2_size.Width;
    sizeInfo->out_vsize = vo_size->layer2_size.Height;
    //
    VO_LAYER_AREA_INFO_S *areaInfo = &layer0Info->areaInfo;
    areaInfo->xCtl_start = h_offset + 1200;
    areaInfo->xCtl_stop = areaInfo->xCtl_start + sizeInfo->out_hsize;
    areaInfo->yCtl_start = v_offset;
    areaInfo->yCtl_stop = areaInfo->yCtl_start + sizeInfo->out_vsize;    
    //
    VO_YUV_BUF_INFO_S *bufInfo = &layer0Info->bufInfo;
    bufInfo->hsize_stride = vo_addr->layer2_stride;
    bufInfo->yAddr0 = vo_addr->layer2_baseaddr;
    bufInfo->yAddr1 = vo_addr->layer2_baseaddr;
    bufInfo->uvAddr0 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * sizeInfo->in_vsize;
    bufInfo->uvAddr1 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * sizeInfo->in_vsize;
    bufInfo->vsize_stride = sizeInfo->in_vsize;
    //
    VO_LAYER0_MFBD_INFO_S *mfbdInfo = &layer0Info->mfbdInfo;
    mfbdInfo->mfbd_en = 0;

    //layer1
    VO_LAYER1_INFO_S *layer1Info = &voCoreInfo->layer1Info;
    layer1Info->layer1DispEn = vo_addr->layer1_en;//0;//vo_addr->layer1_en;
    layer1Info->layerInfo.enable = vo_addr->layer1_en;//0;//vo_addr->layer1_en;
    layer1Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer1Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer1Info->layerInfo.uvswap = 0;
    layer1Info->layerInfo.yuv420en = 1;
    layer1Info->layerInfo.yuv422en = 0;

    layer1Info->layer1SizeInfo.in_hsize = vo_size->layer1_size.Width;
    layer1Info->layer1SizeInfo.in_vsize = vo_size->layer1_size.Height;

    layer1Info->bufInfo.hsize_stride = vo_addr->layer1_stride;
    layer1Info->bufInfo.vsize_stride = vo_size->layer1_size.Height;
    layer1Info->bufInfo.yAddr0  = vo_addr->layer1_baseaddr;
    layer1Info->bufInfo.yAddr1  = vo_addr->layer1_baseaddr;
    layer1Info->bufInfo.uvAddr0 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;
    layer1Info->bufInfo.uvAddr1 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;

    layer1Info->areaInfo.xCtl_start = v_offset;
    layer1Info->areaInfo.xCtl_stop  = layer1Info->areaInfo.xCtl_start + vo_size->layer1_size.Width;
    layer1Info->areaInfo.yCtl_start = h_offset;
    layer1Info->areaInfo.yCtl_stop  = layer1Info->areaInfo.yCtl_start + vo_size->layer1_size.Height;
    //
    //layer2
    VO_LAYER2_INFO_S *layer2Info = &voCoreInfo->layer2Info;
    layer2Info->layer2DispEn = 0;//0; //vo_addr->layer2_en;
    layer2Info->layerInfo.enable = 0;//0;//vo_addr->layer2_en;
    
    layer2Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer2Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer2Info->layerInfo.uvswap = 0;
    layer2Info->layerInfo.yuv420en = 1;
    layer2Info->layerInfo.yuv422en = 0;

    layer2Info->layer2SizeInfo.in_hsize = vo_size->layer2_size.Width;
    layer2Info->layer2SizeInfo.in_vsize = vo_size->layer2_size.Height;

    layer2Info->bufInfo.hsize_stride = vo_addr->layer2_stride;
    layer2Info->bufInfo.vsize_stride = vo_size->layer2_size.Height;
    layer2Info->bufInfo.yAddr0  = vo_addr->layer2_baseaddr;
    layer2Info->bufInfo.yAddr1  = vo_addr->layer2_baseaddr;
    layer2Info->bufInfo.uvAddr0 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * vo_size->layer2_size.Height;
    layer2Info->bufInfo.uvAddr1 = vo_addr->layer2_baseaddr + vo_addr->layer2_stride * vo_size->layer2_size.Height;

    layer2Info->areaInfo.xCtl_start = h_offset + 1200;
    layer2Info->areaInfo.xCtl_stop  = layer2Info->areaInfo.xCtl_start  + vo_size->layer2_size.Width;
    layer2Info->areaInfo.yCtl_start = v_offset;
    layer2Info->areaInfo.yCtl_stop  = layer2Info->areaInfo.yCtl_start + vo_size->layer2_size.Height;
    //layer3
    VO_LAYER3_INFO_S *layer3Info = &voCoreInfo->layer3Info;
    layer3Info->layer3DispEn = 0;//vo_addr->layer1_en;//
    layer3Info->layerInfo.enable = 0;//vo_addr->layer1_en;//

    layer3Info->layerInfo.endiany = VO_VIDEO_LAYER_Y_ENDIAN_MODE1;
    layer3Info->layerInfo.endianuv = VO_VIDEO_LAYER_UV_ENDIAN_MODE2;
    layer3Info->layerInfo.uvswap = 0;
    layer3Info->layerInfo.yuv420en = 1;
    layer3Info->layerInfo.yuv422en = 0;

    layer3Info->layer3SizeInfo.in_hsize = vo_size->layer1_size.Width;
    layer3Info->layer3SizeInfo.in_vsize = vo_size->layer1_size.Height;

    layer3Info->bufInfo.hsize_stride = vo_addr->layer1_stride;
    layer3Info->bufInfo.vsize_stride = vo_size->layer1_size.Height;
    layer3Info->bufInfo.yAddr0  = vo_addr->layer1_baseaddr;
    layer3Info->bufInfo.yAddr1  = vo_addr->layer1_baseaddr;
    layer3Info->bufInfo.uvAddr0 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;
    layer3Info->bufInfo.uvAddr1 = vo_addr->layer1_baseaddr + vo_addr->layer1_stride * vo_size->layer1_size.Height;

    layer3Info->areaInfo.xCtl_start = h_offset;
    layer3Info->areaInfo.xCtl_stop  = h_offset + vo_size->layer1_size.Width;
    layer3Info->areaInfo.yCtl_start = v_offset;
    layer3Info->areaInfo.yCtl_stop  = v_offset + vo_size->layer1_size.Height;

    //osd0
    VO_OSD0_INFO_S  *osd0Info = &voCoreInfo->osd0Info;
    osd0Info->osdLayer4DispEn = vo_addr->osd0_en;//0;
    osd0Info->osdrgb2yuvEn = vo_addr->osd0_en;//1;

    osd0Info->osdtype  = OSD_RGB_32BIT;
    osd0Info->alphatpye = OSD_FIXED_VALUE;
    unsigned int osd0_stride = vo_addr->osd0_stride*4;
    if( DS2_S_RGB == vo_addr->osd0_rgb_type )
    {
        osd0_stride = vo_addr->osd0_stride;
        osd0Info->osdtype = OSD_MONOCHROME_8BIT; 
    }
    //
    VO_OSD_SIZE_INFO_S   *osd0SizeInfo = &osd0Info->osd0SizeInfo;
    osd0SizeInfo->width = vo_size->osd0_size.Width;
    osd0SizeInfo->height = vo_size->osd0_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd0AreaInfo = &osd0Info->osd0AreaInfo;
    osd0AreaInfo->xCtl_start = v_offset;// + 1280;
    osd0AreaInfo->xCtl_stop = osd0AreaInfo->xCtl_start + osd0SizeInfo->width;
    osd0AreaInfo->yCtl_start = h_offset+ 730;
    osd0AreaInfo->yCtl_stop = osd0AreaInfo->yCtl_start + osd0SizeInfo->height;

    //
    VO_OSD_BUF_INFO_S    *osd0BufInfo = &osd0Info->osd0BufInfo;
    osd0BufInfo->alpstride = osd0_stride; 
    osd0BufInfo->osdstride = osd0_stride; 
    osd0BufInfo->alp_addr0 = vo_addr->osd0_baseaddr;
    osd0BufInfo->alp_addr1 = vo_addr->osd0_baseaddr;
    osd0BufInfo->vlu_addr0 = vo_addr->osd0_baseaddr;
    osd0BufInfo->vlu_addr1 = vo_addr->osd0_baseaddr;                

    VO_OSD_DMA_INFO_S    *osd0DmaInfo = &osd0Info->osd0DmaInfo; 
    osd0DmaInfo->rgbrev = OSD_RGB_REV_B;//
    //osd1
    VO_OSD1_INFO_S  *osd1Info = &voCoreInfo->osd1Info;
    osd1Info->osdLayer5DispEn = vo_addr->osd1_en;//0;
    osd1Info->osdrgb2yuvEn = vo_addr->osd1_en;//1;

    osd1Info->osdtype   = osd1_info->osd1_type;
    osd1Info->alphatpye = OSD_FIXED_VALUE;
    //
    VO_OSD_SIZE_INFO_S *osd1SizeInfo = &osd1Info->osd1SizeInfo;
    osd1SizeInfo->width = vo_size->osd1_size.Width;
    osd1SizeInfo->height = vo_size->osd1_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd1AreaInfo = &osd1Info->osd1AreaInfo;
    osd1AreaInfo->xCtl_start = v_offset;
    osd1AreaInfo->xCtl_stop = osd1AreaInfo->xCtl_start + osd1SizeInfo->width;
    osd1AreaInfo->yCtl_start = h_offset+1460;
    osd1AreaInfo->yCtl_stop = osd1AreaInfo->yCtl_start + osd1SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd1BufInfo  = &osd1Info->osd1BufInfo;
    osd1BufInfo->alpstride = vo_addr->osd1_stride; 
    osd1BufInfo->osdstride = vo_addr->osd1_stride;

    if(osd1_info->osd1_type == OSD_RGB_32BIT)
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride*4; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride*4;  
    }
    else if(osd1_info->osd1_type == OSD_RGB_24BIT)
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride*3; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride*3;  
    }
    else
    {
        osd1BufInfo->alpstride = vo_addr->osd1_stride; 
        osd1BufInfo->osdstride = vo_addr->osd1_stride;  
    }
    osd1BufInfo->alp_addr0 = vo_addr->osd1_baseaddr;
    osd1BufInfo->alp_addr1 = vo_addr->osd1_baseaddr;
    osd1BufInfo->vlu_addr0 = vo_addr->osd1_baseaddr;
    osd1BufInfo->vlu_addr1 = vo_addr->osd1_baseaddr;
    //
    VO_OSD_DMA_INFO_S *osd1DmaInfo = &osd1Info->osd1DmaInfo;
    osd1DmaInfo->rgbrev = osd1_info->osd1_rgb_rev;
    osd1DmaInfo->dmamap = osd1_info->osd1_dma_ctl;

    //osd2
    VO_OSD2_INFO_S  *osd2Info = &voCoreInfo->osd2Info;
    osd2Info->osdLayer6DispEn = 0;//vo_addr->osd1_en;//0;
    osd2Info->osdrgb2yuvEn =  0;//vo_addr->osd1_en;//1;

    osd2Info->osdtype   = osd1_info->osd1_type;
    osd2Info->alphatpye = OSD_FIXED_VALUE;
    //
    VO_OSD_SIZE_INFO_S *osd2SizeInfo = &osd2Info->osd2SizeInfo;
    osd2SizeInfo->width = vo_size->osd1_size.Width;
    osd2SizeInfo->height = vo_size->osd1_size.Height;
    //
    VO_LAYER_AREA_INFO_S *osd2AreaInfo = &osd2Info->osd2AreaInfo;
    osd2AreaInfo->xCtl_start = h_offset+1080;
    osd2AreaInfo->xCtl_stop = osd2AreaInfo->xCtl_start + osd2SizeInfo->width;
    osd2AreaInfo->yCtl_start = v_offset+600;
    osd2AreaInfo->yCtl_stop = osd2AreaInfo->yCtl_start + osd2SizeInfo->height;
    //
    VO_OSD_BUF_INFO_S *osd2BufInfo  = &osd2Info->osd2BufInfo;
    osd2BufInfo->alpstride = vo_addr->osd1_stride; 
    osd2BufInfo->osdstride = vo_addr->osd1_stride;

    if(osd1_info->osd1_type == OSD_RGB_32BIT)
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride*4; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride*4;  
    }
    else if(osd1_info->osd1_type == OSD_RGB_24BIT)
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride*3; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride*3;  
    }
    else
    {
        osd2BufInfo->alpstride = vo_addr->osd1_stride; 
        osd2BufInfo->osdstride = vo_addr->osd1_stride;  
    }
    osd2BufInfo->alp_addr0 = vo_addr->osd1_baseaddr;
    osd2BufInfo->alp_addr1 = vo_addr->osd1_baseaddr;
    osd2BufInfo->vlu_addr0 = vo_addr->osd1_baseaddr;
    osd2BufInfo->vlu_addr1 = vo_addr->osd1_baseaddr;
    //
    VO_OSD_DMA_INFO_S *osd2DmaInfo = &osd2Info->osd2DmaInfo;
    osd2DmaInfo->rgbrev = osd1_info->osd1_rgb_rev;
    osd2DmaInfo->dmamap = osd1_info->osd1_dma_ctl;

    //
    voCoreInfo->clutctlen = 0;
    voCoreInfo->ditherctlen = 1;
    //
    VO_REMAP_CMD_INfO_S *remapcmdInfo = &voCoreInfo->remapcmdInfo;
    remapcmdInfo->image_active_h = 1080;
    remapcmdInfo->image_active_v = 1920;
    remapcmdInfo->vo_out_imgtype = 1; //rgb dsi
    
    return;
}
//
int Vo_VideoOut_Dsi(struct isp_device *isp,VO_ADDR_INFO *vo_addr,VO_SIZE_S *vo_size,OSD_INFO *osd1_info)
{
    VO_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(vo_addr);
    ISP_CHECK_POINTER(vo_size);
    ISP_CHECK_POINTER(osd1_info);

    VO_CORE_INFO_S voCoreInfo;
    memcpy(&voCoreInfo,&dsi_vo_info,sizeof(VO_CORE_INFO_S));

    Vo_Core_GetDsiCfg(&voCoreInfo,vo_addr,vo_size,osd1_info);

    // vo_print_CoreCfg(&voCoreInfo);

    Vo_VideoOut(isp,&voCoreInfo);

    return 0;
}
/*
*REMAP
*/
//
int Vo_Remap_FillCmd(struct isp_device *isp,struct _VO_REMAP_CMD_INfO_S *cmd_info)
{
    VO_REMAP_CTRL_FILL_CMD_S fillcmd;

    fillcmd.image_active_h = cmd_info->image_active_h - 1;//1080 - 1;
    fillcmd.image_active_v = cmd_info->image_active_v - 1;//1920 - 1;
    if( 1 == cmd_info->vo_out_imgtype)    
    {
        fillcmd.fill_en_rgb = 1;//1;
        fillcmd.fill_fill_en_yuv = 0;//0;        
    }
    else
    {
        fillcmd.fill_en_rgb = 0;//1;
        fillcmd.fill_fill_en_yuv = 1;//0;
    }

    Vo_Drv_Remap_FillCmd(isp,&fillcmd);
    return 0;
}
//
int Vo_Remap_DrawFrame(struct isp_device *isp,unsigned int draw_en,unsigned int backgroud_draw_en,unsigned int DrawAreaNum,frame_coordinate_info frame_coordinate)
{
    VO_CHECK_POINTER(isp);

    unsigned int  ErrCode = 0;
    if(DrawAreaNum > VO_LINE_DRAW_AREA_31 || DrawAreaNum < VO_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    VO_REMAP_CTRL_FILL_CTL_S fillCtlInfo;

    memset(&fillCtlInfo,0,sizeof(VO_REMAP_CTRL_FILL_CTL_S));

	fillCtlInfo.line_draw_en    = draw_en;//1;  //enable
	//x position
	fillCtlInfo.line_start_pos_x = frame_coordinate.startx;//frame_coordinate.startx*4;//256 ;
	fillCtlInfo.line_end_pos_x   = frame_coordinate.endx;//frame_coordinate.endx*4;//fillCtlInfo.LineStartPosX + 720;
	//background
	fillCtlInfo.v_line_r_en  = backgroud_draw_en;//0;//1;
	fillCtlInfo.v_line_l_en   = backgroud_draw_en;//0;//1;
	fillCtlInfo.h_line_b_en = backgroud_draw_en;//0;//1;
	fillCtlInfo.v_line_u_en     = backgroud_draw_en;//0;//1;
	//y position
	fillCtlInfo.line_start_pos_y = frame_coordinate.starty;//frame_coordinate.starty*3;//256;
	fillCtlInfo.line_end_pos_y   = frame_coordinate.endy;//frame_coordinate.endy*3;//256 + 240;
	//line width
	fillCtlInfo.line_width_l    = 5;//iLoop;
	fillCtlInfo.line_width_h    = 0;

	fillCtlInfo.fill_value_cr       = 226;//164;
	fillCtlInfo.fill_value_cb       = 104;//226;
	fillCtlInfo.fill_value_y        = 47;//120;
	fillCtlInfo.fill_alpha    = 0;

    ErrCode = Vo_Drv_Remap_DrawLineSet(isp,DrawAreaNum,&fillCtlInfo);

    return ErrCode;
}