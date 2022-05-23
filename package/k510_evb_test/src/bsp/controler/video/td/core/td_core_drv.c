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
//#include "td/inc/td.h"
#include "video/isp_com.h"
#include "video/video_subsystem_addr.h"
#include "video/td/core/td_core_drv.h"
#include "video/td/core/td_core_reg.h"

unsigned int  *reg_td_rot_base;
unsigned int  *reg_td_scaler_mix_base;

#define TD_DRV_ROTATION_REG_CTX(pstCtx)	pstCtx = (S_TD_ROTATION_REGS_TYPE *)(reg_td_rot_base)
#define TD_DRV_MIX_SCALER_REG_CTX(pstCtx)	pstCtx = (S_TD_MIX_SCALER_REGS_TYPE *)(reg_td_scaler_mix_base)
/*
*
*/
int TD_DRV_Core_Remap(void)
{
	reg_td_rot_base            = (unsigned int *)TD_ROTATION_BASE;
    reg_td_scaler_mix_base     = (unsigned int *)TD_SCALER_MIXER_BASE;
    return 0;
}
/*
*
*/
static int TD_DRV_SetRot(TD_ROT_ALL_CTL_S *rotAllCtl)
{
    TD_CHECK_POINTER(rotAllCtl);

    S_TD_ROTATION_REGS_TYPE *apstTdRotationReg = NULL;
    TD_DRV_ROTATION_REG_CTX(apstTdRotationReg);

	  U_TD_ROT_CMD                	cmd_udata;
    cmd_udata.u32 = 0;
    cmd_udata.bits.framestart   = rotAllCtl->rot_framestart;
	TD_CORE_DRV_SET_RotCmd(apstTdRotationReg,  cmd_udata.u32);

    U_TD_ROT_CTL                	ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.endianInEn  = rotAllCtl->rotCtl.endianInEn;
    ctl_udata.bits.endianOutEn = rotAllCtl->rotCtl.endianOutEn; 
    ctl_udata.bits.Inswap      = rotAllCtl->rotCtl.Inswap;
    ctl_udata.bits.otmaxrd     = rotAllCtl->rotCtl.otmaxrd;
    ctl_udata.bits.otmaxwr     = rotAllCtl->rotCtl.otmaxwr;
    ctl_udata.bits.Outswap     = rotAllCtl->rotCtl.Outswap;
    ctl_udata.bits.pixformat   = rotAllCtl->rotCtl.pixformat;
    ctl_udata.bits.rotmode     = rotAllCtl->rotCtl.rotmode;
	TD_CORE_DRV_SET_RotCtl(apstTdRotationReg,  ctl_udata.u32);

    U_TD_ROT_TIME_OUT           	time_udata;
    time_udata.u32 = 0;
    time_udata.bits.val        = rotAllCtl->timeout_val;
	TD_CORE_DRV_SET_RotTimeOut(apstTdRotationReg,  time_udata.u32);

    U_TD_ROT_IMAGE_SIZE_ACTIVE  	size_udata;
    size_udata.u32 = 0;
    size_udata.bits.hor        = rotAllCtl->imgSize.hor;
    size_udata.bits.ver		   = rotAllCtl->imgSize.ver;
	TD_CORE_DRV_SET_RotImageSizeActive(apstTdRotationReg,  size_udata.u32);
    //y
    U_TD_ROT_FRM_BASE_ADDR_Y_SRC	ysrc_udata;
    ysrc_udata.u32 = 0;
    ysrc_udata.bits.addr       = rotAllCtl->yBufCtl.y_src_addr;
	TD_CORE_DRV_SET_RotBaseAddrYSrc(apstTdRotationReg,  ysrc_udata.u32);

    U_TD_ROT_FRM_BASE_ADDR_Y_DES	ydes_udata;
    ydes_udata.u32 = 0;
    ydes_udata.bits.addr       = rotAllCtl->yBufCtl.y_des_addr;
	TD_CORE_DRV_SET_RotBaseAddrYDes(apstTdRotationReg,  ydes_udata.u32);

    U_TD_ROT_STRIDE_Y           	ystride_udata;
    ystride_udata.u32 = 0;
    ystride_udata.bits.src     = rotAllCtl->yBufCtl.src_stride;
    ystride_udata.bits.des     = rotAllCtl->yBufCtl.des_stride;
	TD_CORE_DRV_SET_RotStrideY(apstTdRotationReg,  ystride_udata.u32);
    //u
    U_TD_ROT_FRM_BASE_ADDR_U_SRC	usrc_udata;
    usrc_udata.u32 = 0;
    usrc_udata.bits.addr       = rotAllCtl->uBufCtl.u_src_addr;
		TD_CORE_DRV_SET_RotBaseAddrUSrc(apstTdRotationReg,  usrc_udata.u32);

    U_TD_ROT_FRM_BASE_ADDR_U_DES	udes_udata;
    udes_udata.u32 = 0;
    udes_udata.bits.addr       = rotAllCtl->uBufCtl.u_des_addr;
		TD_CORE_DRV_SET_RotBaseAddrUDes(apstTdRotationReg,  udes_udata.u32);

    U_TD_ROT_STRIDE_U           	ustride_udata;
    ustride_udata.u32 = 0;
    ustride_udata.bits.src     = rotAllCtl->uBufCtl.src_stride;
    ustride_udata.bits.des     = rotAllCtl->uBufCtl.des_stride;
		TD_CORE_DRV_SET_RotStrideU(apstTdRotationReg,  ustride_udata.u32);
    //v
    U_TD_ROT_FRM_BASE_ADDR_V_SRC	vsrc_udata;
    vsrc_udata.u32 = 0;
    vsrc_udata.bits.addr       = rotAllCtl->uBufCtl.u_src_addr;
		TD_CORE_DRV_SET_RotBaseAddrVSrc(apstTdRotationReg,  vsrc_udata.u32);

    U_TD_ROT_FRM_BASE_ADDR_V_DES	vdes_udata;
    vdes_udata.u32 = 0;
    vdes_udata.bits.addr       = rotAllCtl->vBufCtl.v_des_addr;    
		TD_CORE_DRV_SET_RotBaseAddrVDes(apstTdRotationReg,  vdes_udata.u32);

    U_TD_ROT_STRIDE_V           	vstride_udata;
    vstride_udata.u32 = 0;
    vstride_udata.bits.src     = rotAllCtl->vBufCtl.src_stride;
    vstride_udata.bits.des     = rotAllCtl->vBufCtl.des_stride;        
		TD_CORE_DRV_SET_RotStrideV(apstTdRotationReg,  vstride_udata.u32);
    return 0;
}
/*
*
*/
static int TD_DRV_SetDisp(TD_DISP_ALL_CTL_S *dispAllCtl)
{
    TD_CHECK_POINTER(dispAllCtl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);

    U_TD_DISP_XZONE_CTL            xzone_udata;
    xzone_udata.u32 = 0;
    xzone_udata.bits.start         = dispAllCtl->xZoneCtl.start;
    xzone_udata.bits.stop          = dispAllCtl->xZoneCtl.stop;
    TD_CORE_DRV_SET_Layer0XZoneCtl(apstTdMixScalerReg, xzone_udata.u32);

    U_TD_DISP_YZONE_CTL            yzone_udata;
    yzone_udata.u32 = 0;
    yzone_udata.bits.start         = dispAllCtl->yZoneCtl.start;
    yzone_udata.bits.stop          = dispAllCtl->yZoneCtl.stop;
    TD_CORE_DRV_SET_Layer0YZoneCtl(apstTdMixScalerReg, yzone_udata.u32);

    U_TD_DISP_HSYNC_CTL            hsync_udata;
    hsync_udata.u32 = 0;
    hsync_udata.bits.start         = dispAllCtl->hSyncCtl.start;
    hsync_udata.bits.stop          = dispAllCtl->hSyncCtl.stop;
    TD_CORE_DRV_SET_DispHsyncCtl(apstTdMixScalerReg, hsync_udata.u32);

    U_TD_DISP_VSYNC_CTL            vsync_udata;
    vsync_udata.u32 = 0;
    vsync_udata.bits.start        = dispAllCtl->vSyncCtl.start;
    vsync_udata.bits.stop         = dispAllCtl->vSyncCtl.stop;
		TD_CORE_DRV_SET_DispVsyncCtl(apstTdMixScalerReg, vsync_udata.u32);

    U_TD_DISP_CTL                  ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.vcntbit0       = dispAllCtl->dispCtl.vcntbit0;
    ctl_udata.bits.secndfoffset   = dispAllCtl->dispCtl.secndfoffset;
    ctl_udata.bits.framesyncdly   = dispAllCtl->dispCtl.framesyncdly;
    TD_CORE_DRV_SET_DispCtl(apstTdMixScalerReg, ctl_udata.u32);

    U_TD_DISP_SIZE                 size_udata;
    size_udata.u32 = 0;
    size_udata.bits.hsize         = dispAllCtl->dispSize.hsize;
    size_udata.bits.vsize         = dispAllCtl->dispSize.vsize;
    TD_CORE_DRV_SET_DispSize(apstTdMixScalerReg, size_udata.u32);

    U_TD_DISP_ENABLE               en_udata;
    en_udata.u32 = TD_CORE_DRV_GET_DispEnable(apstTdMixScalerReg);
    en_udata.bits.framestart      = dispAllCtl->framestart;
    TD_CORE_DRV_SET_DispEnable(apstTdMixScalerReg, en_udata.u32);
    return 0;
}
/*
*
*/
static int TD_DRV_SetLayer0Scaler(TD_LAYER0_CTL_S *layer0Ctl)
{
    TD_CHECK_POINTER(layer0Ctl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);

    U_TD_DISP_ENABLE               en_udata;
    en_udata.u32 = TD_CORE_DRV_GET_DispEnable(apstTdMixScalerReg);
    en_udata.bits.layer0en      = layer0Ctl->layer0en;
    en_udata.bits.layer0enhs    = layer0Ctl->layer0enhs;
    en_udata.bits.layer0Wenhs   = layer0Ctl->layer0Wenhs;
    TD_CORE_DRV_SET_DispEnable(apstTdMixScalerReg, en_udata.u32);

    U_TD_LAYER0_XCTL               xctl_udata;
    xctl_udata.u32 = 0;
    xctl_udata.bits.start       = layer0Ctl->layer0XCtl.start;
    xctl_udata.bits.stop        = layer0Ctl->layer0XCtl.stop;
    TD_CORE_DRV_SET_Layer0XCtl(apstTdMixScalerReg, xctl_udata.u32);

    U_TD_LAYER0_YCTL               yctl_udata; 
    yctl_udata.u32 = 0; 
    yctl_udata.bits.start       = layer0Ctl->layer0YCtl.start;
    yctl_udata.bits.stop        = layer0Ctl->layer0YCtl.stop;
    TD_CORE_DRV_SET_Layer0YCtl(apstTdMixScalerReg, yctl_udata.u32); 

    U_TD_LAYER0_LINE0_BD_CTL       line0_udata;
    line0_udata.u32 = 0;
    line0_udata.bits.limiten    = layer0Ctl->layer0Line0BDCtl.limiten;
    line0_udata.bits.outstand   = layer0Ctl->layer0Line0BDCtl.outstand;
    TD_CORE_DRV_SET_Layer0Line0BDCtl(apstTdMixScalerReg, line0_udata.u32);    
   
    U_TD_LAYER0_LINE1_BD_CTL       line1_udata;
    line1_udata.u32 = 0;
    line1_udata.bits.limiten    = layer0Ctl->layer0Line1BDCtl.limiten;
    line1_udata.bits.outstand   = layer0Ctl->layer0Line1BDCtl.outstand;    
    TD_CORE_DRV_SET_Layer0Line1BDCtl(apstTdMixScalerReg, line1_udata.u32);         
            
    U_TD_LAYER0_LINE2_BD_CTL       line2_udata;
    line2_udata.u32 = 0;
    line2_udata.bits.limiten    = layer0Ctl->layer0Line2BDCtl.limiten;
    line2_udata.bits.outstand   = layer0Ctl->layer0Line2BDCtl.outstand;    
    TD_CORE_DRV_SET_Layer0Line2BDCtl(apstTdMixScalerReg, line2_udata.u32);

    U_TD_LAYER0_LINE3_BD_CTL       line3_udata;
    line3_udata.u32 = 0;
    line3_udata.bits.limiten    = layer0Ctl->layer0Line3BDCtl.limiten;
    line3_udata.bits.outstand   = layer0Ctl->layer0Line3BDCtl.outstand;  
    TD_CORE_DRV_SET_Layer0Line3BDCtl(apstTdMixScalerReg, line3_udata.u32); 

    U_TD_LAYER0_CTL                ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.enable       = layer0Ctl->ctlen;
    TD_CORE_DRV_SET_Layer0Ctl(apstTdMixScalerReg, ctl_udata.u32);

    U_TD_LAYER0_SCALE_BLENTH       blen_udata;
    blen_udata.u32 = 0;
    blen_udata.bits.blen        = layer0Ctl->layer0Scalerblen;
    TD_CORE_DRV_SET_Layer0ScaleBlenth(apstTdMixScalerReg, blen_udata.u32);

    U_TD_LAYER0_IMG_IN_DAT_MODE    mode_udata;
    mode_udata.u32 = 0;
    mode_udata.bits.datmode     = layer0Ctl->imgInDatMode.datmode;
    mode_udata.bits.endianuv    = layer0Ctl->imgInDatMode.endianuv;
    mode_udata.bits.endiany     = layer0Ctl->imgInDatMode.endiany;
    mode_udata.bits.swapuv      = layer0Ctl->imgInDatMode.swapuv;
    TD_CORE_DRV_SET_Layer0ImgInDatMode(apstTdMixScalerReg, mode_udata.u32);

    U_TD_LAYER0_BADDR0_Y           y_udata;
    y_udata.u32 = 0;
    y_udata.bits.addr           = layer0Ctl->y_addr;
    TD_CORE_DRV_SET_Layer0BAddr0Y(apstTdMixScalerReg, y_udata.u32);

    U_TD_LAYER0_BADDR0_UV          uv_udata;
    uv_udata.u32 = 0;
    uv_udata.bits.addr          = layer0Ctl->uv_addr;
    TD_CORE_DRV_SET_Layer0BAddr0UV(apstTdMixScalerReg, uv_udata.u32);

    U_TD_LAYER0_IMG_IN_PIX_SIZE    insize_udata;
    insize_udata.u32 = 0;
    insize_udata.bits.hsize     = layer0Ctl->imgInSize.hsize;
    insize_udata.bits.vsize     = layer0Ctl->imgInSize.vsize;
    TD_CORE_DRV_SET_Layer0ImgInPixSize(apstTdMixScalerReg, insize_udata.u32);

    U_TD_LAYER0_IMG_OUT_PIX_SIZE   outsize_udata;
    outsize_udata.u32 = 0;
    outsize_udata.bits.hsize    = layer0Ctl->imgOutSize.hsize;
    outsize_udata.bits.vsize    = layer0Ctl->imgOutSize.vsize;
    TD_CORE_DRV_SET_Layer0ImgOutPixSize(apstTdMixScalerReg, outsize_udata.u32);

    U_TD_LAYER0_IMG_IN_STRIDE      stride_udata;
    stride_udata.u32 = 0;
    stride_udata.bits.hsize     = layer0Ctl->imgInStride.hsize;
    stride_udata.bits.vsize     = layer0Ctl->imgInStride.vsize;
    TD_CORE_DRV_SET_Layer0ImgInStride(apstTdMixScalerReg, stride_udata.u32); 

    U_TD_LAYER0_IMG_IN_OFFSET      offset_udata;
    offset_udata.u32 = 0;
    offset_udata.bits.hoffset   = layer0Ctl->imgInOffset.hsize;
    offset_udata.bits.voffset   = layer0Ctl->imgInOffset.vsize;
    TD_CORE_DRV_SET_Layer0ImgInOffset(apstTdMixScalerReg, offset_udata.u32);

    U_TD_LAYER0_VSCALE_STEP        vstep_udata;
    vstep_udata.u32 = 0;
    vstep_udata.bits.dstep      = layer0Ctl->vScaleCtl.dstep;
    vstep_udata.bits.pstep      = layer0Ctl->vScaleCtl.pstep;
    TD_CORE_DRV_SET_Layer0VScaleStep(apstTdMixScalerReg, vstep_udata.u32);

    U_TD_LAYER0_VSCALE_ST          vst_udata;
    vst_udata.u32 = 0;
    vst_udata.bits.pstep        = layer0Ctl->vScaleCtl.pstep_st;
    TD_CORE_DRV_SET_Layer0VScaleST(apstTdMixScalerReg, vst_udata.u32);

    U_TD_LAYER0_HSCALE_STEP        hstep_udata;
    hstep_udata.u32 = 0;
    hstep_udata.bits.dstep      = layer0Ctl->hScaleCtl.dstep;
    hstep_udata.bits.pstep      = layer0Ctl->hScaleCtl.pstep;
    TD_CORE_DRV_SET_Layer0HScaleStep(apstTdMixScalerReg, hstep_udata.u32);

    U_TD_LAYER0_HSCALE_ST          hst_udata;
    hst_udata.u32 = 0;
    hst_udata.bits.pstep        = layer0Ctl->hScaleCtl.pstep_st;
    TD_CORE_DRV_SET_Layer0HScaleST(apstTdMixScalerReg, hst_udata.u32);

    U_TD_LAYER0_BASE_MODE          basemode_udata;
    basemode_udata.u32 = 0;
    basemode_udata.bits.mode    = layer0Ctl->baseMode.mode; 
    basemode_udata.bits.addrflag= layer0Ctl->baseMode.addrflag; 
    basemode_udata.bits.base0mask= layer0Ctl->baseMode.base0mask;
    basemode_udata.bits.base0mask= layer0Ctl->baseMode.base1mask;
    TD_CORE_DRV_SET_BaseMode(apstTdMixScalerReg, basemode_udata.u32);
 
    return 0;
}
/*
*
*/
static int TD_DRV_SetLayer4Osd0(TD_LAYER4_OSD_CTL_S *layer4OsdCtl)
{
    TD_CHECK_POINTER(layer4OsdCtl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);  

    U_TD_DISP_ENABLE               en_udata;
    en_udata.u32 = TD_CORE_DRV_GET_DispEnable(apstTdMixScalerReg);
    en_udata.bits.layer4en      = layer4OsdCtl->layer4en;
    en_udata.bits.layer4enhs    = layer4OsdCtl->layer4enhs;
    en_udata.bits.layer4Wenhs   = layer4OsdCtl->layer4Wenhs;
    TD_CORE_DRV_SET_DispEnable(apstTdMixScalerReg, en_udata.u32);

    U_TD_LAYER4_BD_CTL             bd_udata;
    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = layer4OsdCtl->layer4BDCtl.limiten;
    bd_udata.bits.outstand      = layer4OsdCtl->layer4BDCtl.outstand;
    TD_CORE_DRV_SET_Layer4BDCtl(apstTdMixScalerReg, bd_udata.u32);

    U_TD_LAYER4_XCTL               xctl_udata;
    xctl_udata.u32 = 0;
    xctl_udata.bits.start       = layer4OsdCtl->layer4XCtl.start;
    xctl_udata.bits.stop        = layer4OsdCtl->layer4XCtl.stop;
    TD_CORE_DRV_SET_Layer4XCtl(apstTdMixScalerReg, xctl_udata.u32);

    U_TD_LAYER4_YCTL               yctl_udata;
    yctl_udata.u32 = 0;
    yctl_udata.bits.start       = layer4OsdCtl->layer4YCtl.start;
    yctl_udata.bits.stop        = layer4OsdCtl->layer4YCtl.stop;
    TD_CORE_DRV_SET_Layer4YCtl(apstTdMixScalerReg, yctl_udata.u32);

    U_TD_OSD0_INFO                 info_udata;
    info_udata.u32 = 0;
    info_udata.bits.alphatpye   = layer4OsdCtl->osd0Ctl.alphatpye;
    info_udata.bits.osdtype     = layer4OsdCtl->osd0Ctl.osdtype;
    TD_CORE_DRV_SET_Osd0Info(apstTdMixScalerReg, info_udata.u32);

    U_TD_OSD0_SIZE                 size_udata;
    size_udata.u32 = 0;
    size_udata.bits.width       = layer4OsdCtl->osd0Size.width;
    size_udata.bits.height      = layer4OsdCtl->osd0Size.height;
    TD_CORE_DRV_SET_Osd0Size(apstTdMixScalerReg, size_udata.u32);

    U_TD_DISP_OSD0_VLU_ADDR0       vlu_udata;
    vlu_udata.u32 = 0;
    vlu_udata.bits.addr         = layer4OsdCtl->osd0Addr.vlu_addr;
    TD_CORE_DRV_SET_Osd0VLUAddr0(apstTdMixScalerReg, vlu_udata.u32);

    U_TD_DISP_OSD0_ALP_ADDR0       alp_udata;
    alp_udata.u32 = 0;
    alp_udata.bits.addr         = layer4OsdCtl->osd0Addr.alp_addr;
    TD_CORE_DRV_SET_Osd0ALPAddr0(apstTdMixScalerReg, alp_udata.u32);

    U_TD_OSD0_DMA_CTL              dmactl_udata;
    dmactl_udata.u32 = 0;
    dmactl_udata.bits.dmamap    = layer4OsdCtl->osd0DmaCtl.dmamap;
    dmactl_udata.bits.dmarequestlen = layer4OsdCtl->osd0DmaCtl.dmarequestlen;
    dmactl_udata.bits.rgbrev    = layer4OsdCtl->osd0DmaCtl.rgbrev;
    TD_CORE_DRV_SET_Osd0DmaCtl(apstTdMixScalerReg, dmactl_udata.u32);

    U_TD_OSD0_STRIDE               stride_udata;
    stride_udata.u32 = 0;
    stride_udata.bits.alpstride = layer4OsdCtl->osd0Addr.alpstride;
    stride_udata.bits.osdstride = layer4OsdCtl->osd0Addr.osdstride;
    TD_CORE_DRV_SET_Osd0Stride(apstTdMixScalerReg, stride_udata.u32);
    //
    U_TD_OSD_RGB2YUV_CTL           ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.osd0en       = layer4OsdCtl->osdRgb2Yuv.osd0en;
    ctl_udata.bits.osd1en       = layer4OsdCtl->osdRgb2Yuv.osd1en;
    ctl_udata.bits.osd2en       = layer4OsdCtl->osdRgb2Yuv.osd2en;
    TD_CORE_DRV_SET_OsdRGB2YUVCtl(apstTdMixScalerReg, ctl_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF00       c00_udata;
    c00_udata.u32 = 0;
    c00_udata.bits.c00             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[0][0];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff00(apstTdMixScalerReg, c00_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF01       c01_udata;
    c01_udata.u32 = 0;
    c01_udata.bits.c01             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[0][1];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff01(apstTdMixScalerReg, c01_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF02       c02_udata;
    c02_udata.u32 = 0;
    c02_udata.bits.c02             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[0][2];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff02(apstTdMixScalerReg, c02_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF03       c03_udata;
    c03_udata.u32 = 0;
    c03_udata.bits.c03             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[0][3];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff03(apstTdMixScalerReg, c03_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF10       c10_udata;
    c10_udata.u32 = 0;
    c10_udata.bits.c10             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[1][0];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff10(apstTdMixScalerReg, c10_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF11       c11_udata;
    c11_udata.u32 = 0;
    c11_udata.bits.c11             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[1][1];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff11(apstTdMixScalerReg, c11_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF12       c12_udata;
    c12_udata.u32 = 0;
    c12_udata.bits.c12             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[1][2];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff12(apstTdMixScalerReg, c12_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF13       c13_udata;
    c13_udata.u32 = 0;
    c13_udata.bits.c13             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[1][3];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff13(apstTdMixScalerReg, c13_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF20       c20_udata;
    c20_udata.u32 = 0;
    c20_udata.bits.c20             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[2][0];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff20(apstTdMixScalerReg, c20_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF21       c21_udata;
    c21_udata.u32 = 0;
    c21_udata.bits.c21             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[2][1];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff21(apstTdMixScalerReg, c21_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF22       c22_udata;
    c22_udata.u32 = 0;
    c22_udata.bits.c22             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[2][2];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff22(apstTdMixScalerReg, c22_udata.u32);

    U_TD_OSD_RGB2YUV_COEFF23       c23_udata;
    c23_udata.u32 = 0;
    c23_udata.bits.c23             = layer4OsdCtl->osdRgb2Yuv.osdrgb2yuv_coeff[2][3];
    TD_CORE_DRV_SET_OsdRGB2YUVCoeff23(apstTdMixScalerReg, c23_udata.u32);
  
    return 0;
}
/*
*
*/
static int TD_DRV_SetYuv2Rgb(TD_YUV2RGB_S  *yuv2rgb)
{
    TD_CHECK_POINTER(yuv2rgb);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);  

    U_TD_DISP_YUV2RGB_CTL          ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.en          = yuv2rgb->yuv2rgb_ctl_en;
    TD_CORE_DRV_SET_DispYUV2RGBCtl(apstTdMixScalerReg,ctl_udata.u32);

    U_TD_DISP_YUV2RGB_COEFF00      c00_udata;
    c00_udata.u32 = 0;
    c00_udata.bits.c00         = yuv2rgb->yuv2rgb_coeff[0][0];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff00(apstTdMixScalerReg,c00_udata.u32);
	
  	U_TD_DISP_YUV2RGB_COEFF01      c01_udata;
    c01_udata.u32 = 0;
    c01_udata.bits.c01         = yuv2rgb->yuv2rgb_coeff[0][1];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff01(apstTdMixScalerReg,c01_udata.u32);

    U_TD_DISP_YUV2RGB_COEFF02      c02_udata;
    c02_udata.u32 = 0;
    c02_udata.bits.c02         = yuv2rgb->yuv2rgb_coeff[0][2];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff02(apstTdMixScalerReg,c02_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF03      c03_udata;
    c03_udata.u32 = 0;
    c03_udata.bits.c03         = yuv2rgb->yuv2rgb_coeff[0][3];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff03(apstTdMixScalerReg,c03_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF10      c10_udata;
    c10_udata.u32 = 0;
    c10_udata.bits.c10         = yuv2rgb->yuv2rgb_coeff[1][0];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff10(apstTdMixScalerReg,c10_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF11      c11_udata;
    c11_udata.u32 = 0;
    c11_udata.bits.c11         = yuv2rgb->yuv2rgb_coeff[1][1];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff11(apstTdMixScalerReg,c11_udata.u32);

		U_TD_DISP_YUV2RGB_COEFF12      c12_udata;
    c12_udata.u32 = 0;
    c12_udata.bits.c12         = yuv2rgb->yuv2rgb_coeff[1][2];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff12(apstTdMixScalerReg,c12_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF13      c13_udata;
    c13_udata.u32 = 0;
    c13_udata.bits.c13         = yuv2rgb->yuv2rgb_coeff[1][3];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff13(apstTdMixScalerReg,c13_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF20      c20_udata;
    c20_udata.u32 = 0;
    c20_udata.bits.c20         = yuv2rgb->yuv2rgb_coeff[2][0]; 
    TD_CORE_DRV_SET_DispYUV2RGBCoeff20(apstTdMixScalerReg,c20_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF21      c21_udata;
    c21_udata.u32 = 0;
    c21_udata.bits.c21         = yuv2rgb->yuv2rgb_coeff[2][1];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff21(apstTdMixScalerReg,c21_udata.u32);

	  U_TD_DISP_YUV2RGB_COEFF22      c22_udata;
    c22_udata.u32 = 0;
    c22_udata.bits.c22         = yuv2rgb->yuv2rgb_coeff[2][2];
    TD_CORE_DRV_SET_DispYUV2RGBCoeff22(apstTdMixScalerReg,c22_udata.u32);
    
	  U_TD_DISP_YUV2RGB_COEFF23      c23_udata;  
    c23_udata.u32 = 0;
    c23_udata.bits.c23         = yuv2rgb->yuv2rgb_coeff[2][3];        
    TD_CORE_DRV_SET_DispYUV2RGBCoeff23(apstTdMixScalerReg,c23_udata.u32);

    return 0;
}
/*
*
*/
static int TD_DRV_SetDispMix(TD_DISP_MIX_CTL_S *dispMixCtl)
{
    TD_CHECK_POINTER(dispMixCtl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);  

    U_TD_DISP_MIX_ALP0             alp0_udata;
    alp0_udata.u32 = 0;
    alp0_udata.bits.layer0glbalp    = dispMixCtl->layer0glbalp;
    TD_CORE_DRV_SET_DispMixALP0(apstTdMixScalerReg, alp0_udata.u32);

    U_TD_DISP_MIX_ALP1             alp1_udata;
    alp1_udata.u32 = 0;
    alp1_udata.bits.layer4glbalp    = dispMixCtl->layer4glbalp;
    TD_CORE_DRV_SET_DispMixALP1(apstTdMixScalerReg, alp1_udata.u32);

    U_TD_DISP_MIX_SEL              sel_udata;
    sel_udata.u32 = 0;
    sel_udata.bits.layer0sel        = dispMixCtl->layer0sel;
    sel_udata.bits.layer1sel        = dispMixCtl->layer1sel;
    TD_CORE_DRV_SET_DispMixSel(apstTdMixScalerReg, sel_udata.u32);

    U_TD_DISP_BACK_GROUD           groud_udata; 
    groud_udata.u32 = 0;
    groud_udata.bits.y              = dispMixCtl->backGroud.y;
    groud_udata.bits.u              = dispMixCtl->backGroud.u;
    groud_udata.bits.v              = dispMixCtl->backGroud.v;
    TD_CORE_DRV_SET_DispBackGroud(apstTdMixScalerReg, groud_udata.u32);
           
    return 0;
}
/*
*
*/
static int TD_DRV_SetInt(TD_DISP_IRQ_S *dispIrq)
{
    TD_CHECK_POINTER(dispIrq);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);

    U_TD_DISP_IRQ0                  irq0_udata;
    irq0_udata.u32 = 0;
    irq0_udata.bits.en              = dispIrq->irq0Ctl.en;
    TD_CORE_DRV_SET_DispIRQ0(apstTdMixScalerReg, irq0_udata.u32);

    U_TD_DISP_IRQ1                  irq1_udata;
    irq1_udata.u32 = 0;
    irq1_udata.bits.en              = dispIrq->irq1Ctl.en;
    TD_CORE_DRV_SET_DispIRQ1(apstTdMixScalerReg, irq1_udata.u32);

    U_TD_DISP_IRQ2                  irq2_udata;
    irq2_udata.u32 = 0;
    irq2_udata.bits.en              = dispIrq->irq2Ctl.en;
    TD_CORE_DRV_SET_DispIRQ2(apstTdMixScalerReg, irq2_udata.u32);

    return 0;
}
/*
*
*/
static int TD_DRV_SetWb(TD_WB_CTL_S *wbCtl)
{
    TD_CHECK_POINTER(wbCtl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);  

    U_TD_WB_DMA_WR_EN              en_udata;
    en_udata.u32 = 0;
    en_udata.bits.y_en          = wbCtl->yBuf.y_en;
    en_udata.bits.uv_en         = wbCtl->uvBuf.uv_en;
    TD_CORE_DRV_SET_WBDmaWrEn(apstTdMixScalerReg, en_udata.u32);

    U_TD_WB_MODE                   mode_udata;
    mode_udata.u32 = 0;
    mode_udata.bits.input       = wbCtl->input_mode;
    TD_CORE_DRV_SET_WBMode(apstTdMixScalerReg, mode_udata.u32);

    U_TD_WB_PIXEL_FORMAT_OUT       format_udata;
    format_udata.u32 = 0;
    format_udata.bits.formatsel = wbCtl->PixelFormatOut.formatsel;
    format_udata.bits.inputformat= wbCtl->PixelFormatOut.inputformat;
    format_udata.bits.outputformat= wbCtl->PixelFormatOut.outputformat;
    format_udata.bits.pixelorder422= wbCtl->PixelFormatOut.pixelorder422;
    format_udata.bits.rgbpixelwidth= wbCtl->PixelFormatOut.rgbpixelwidth;
    TD_CORE_DRV_SET_WBPixelFormatOut(apstTdMixScalerReg, format_udata.u32);

    U_TD_WB_FRM_BASE_OUT_ADDR0_Y   y0_udata;
    y0_udata.u32 = 0;
    y0_udata.bits.addr          = wbCtl->yBuf.addr0;
    TD_CORE_DRV_SET_WBFrmBaseOutAddr0Y(apstTdMixScalerReg, y0_udata.u32);

    U_TD_WB_FRM_BASE_OUT_ADDR1_Y   y1_udata;
    y1_udata.u32 = 0;
    y1_udata.bits.addr          = wbCtl->yBuf.addr1;
    TD_CORE_DRV_SET_WBFrmBaseOutAddr1Y(apstTdMixScalerReg, y1_udata.u32);

    U_TD_WB_FRM_BASE_OUT_ADDR0_UV  uv0_udata;
    uv0_udata.u32 = 0;
    uv0_udata.bits.addr         = wbCtl->uvBuf.addr0;
    TD_CORE_DRV_SET_WBFrmBaseOutAddr0UV(apstTdMixScalerReg, uv0_udata.u32);

    U_TD_WB_FRM_BASE_OUT_ADDR1_UV  uv1_udata;
    uv1_udata.u32 = 0;
    uv1_udata.bits.addr         = wbCtl->uvBuf.addr1;
    TD_CORE_DRV_SET_WBFrmBaseOutAddr1UV(apstTdMixScalerReg, uv1_udata.u32);

    U_TD_WB_HSTRIDE_OUT_Y          ystride_udata;
    ystride_udata.u32 = 0;
    ystride_udata.bits.hstride  = wbCtl->yBuf.hstride;
    TD_CORE_DRV_SET_WBHStrideOutY(apstTdMixScalerReg, ystride_udata.u32);

    U_TD_WB_HSTRIDE_OUT_UV         uvstride_udata;
    uvstride_udata.u32 = 0;
    uvstride_udata.bits.hstride = wbCtl->uvBuf.hstride;
    TD_CORE_DRV_SET_WBHStrideOutUV(apstTdMixScalerReg, uvstride_udata.u32);

    U_TD_WB_FRM_BUF_SIZE_OUT       bufsize_udata;
    bufsize_udata.u32 = 0;
    bufsize_udata.bits.buffersize = wbCtl->buffersize;
    TD_CORE_DRV_SET_WBFrmBufSizeOut(apstTdMixScalerReg, bufsize_udata.u32);

    U_TD_WB_V_SIZE_ACTIVE_OUT      vactivesize_udata;
    vactivesize_udata.u32 = 0;
    vactivesize_udata.bits.size = wbCtl->v_size_out;
    TD_CORE_DRV_SET_WBVSizeActiveOut(apstTdMixScalerReg, vactivesize_udata.u32);

    U_TD_WB_H_SIZE_ACTIVE_OUT      hactivesize_udata;
    hactivesize_udata.u32 = 0;
    hactivesize_udata.bits.size = wbCtl->h_size_out;
    TD_CORE_DRV_SET_WBHSizeActiveOut(apstTdMixScalerReg, hactivesize_udata.u32);

    U_TD_WB_CH0_DMA_MODE           ch0mode_udata;
    ch0mode_udata.u32 = 0;
    ch0mode_udata.bits.blen     = wbCtl->ch0Ctl.dmaMode.blen;
    ch0mode_udata.bits.continuousmode = wbCtl->ch0Ctl.dmaMode.continuousmode;
    ch0mode_udata.bits.errdetecten = wbCtl->ch0Ctl.dmaMode.errdetecten;
    ch0mode_udata.bits.otnum    = wbCtl->ch0Ctl.dmaMode.errdetecten;
    ch0mode_udata.bits.swap     = wbCtl->ch0Ctl.dmaMode.swap;
    TD_CORE_DRV_SET_WBCh0DmaMode(apstTdMixScalerReg, ch0mode_udata.u32);

    U_TD_WB_CH0_ERR_UNIT           ch0unit_udata;
    ch0unit_udata.u32 = 0;
    ch0unit_udata.bits.unit     = wbCtl->ch0Ctl.err_unit;
    TD_CORE_DRV_SET_WBCh0ErrUnit(apstTdMixScalerReg, ch0unit_udata.u32);

    U_TD_WB_CH0_ERR_TH             ch0th_udata;
    ch0th_udata.u32 = 0;
    ch0th_udata.bits.threshold  = wbCtl->ch0Ctl.err_unit;
    TD_CORE_DRV_SET_WBCh0ErrTH(apstTdMixScalerReg, ch0th_udata.u32);

    U_TD_WB_CH0_INFO_CLR           ch0clr_udata;
    ch0clr_udata.u32 = 0;
    ch0clr_udata.bits.fifoerrclear = wbCtl->ch0Ctl.infoClr.fifoerrclear;
    ch0clr_udata.bits.frmcntclear  = wbCtl->ch0Ctl.infoClr.frmcntclear;
    ch0clr_udata.bits.maxbw    = wbCtl->ch0Ctl.infoClr.maxbw;
    ch0clr_udata.bits.totalbw  = wbCtl->ch0Ctl.infoClr.totalbw;    
    TD_CORE_DRV_SET_WBCh0InfoClr(apstTdMixScalerReg, ch0clr_udata.u32);

    U_TD_WB_CH0_RST_REQ            ch0req_udata;
    ch0req_udata.u32 = 0;
    ch0req_udata.bits.request   = wbCtl->ch0Ctl.request;
    TD_CORE_DRV_SET_WBCh0RstReq(apstTdMixScalerReg, ch0req_udata.u32);

    U_TD_WB_CH1_DMA_MODE           ch1mode_udata;
    ch1mode_udata.u32 = 0;
    ch1mode_udata.bits.blen     = wbCtl->ch1Ctl.dmaMode.blen;
    ch1mode_udata.bits.continuousmode = wbCtl->ch1Ctl.dmaMode.continuousmode;
    ch1mode_udata.bits.errdetecten = wbCtl->ch1Ctl.dmaMode.errdetecten;
    ch1mode_udata.bits.otnum    = wbCtl->ch1Ctl.dmaMode.otnum;
    ch1mode_udata.bits.swap     = wbCtl->ch1Ctl.dmaMode.swap;
    TD_CORE_DRV_SET_WBCh1DmaMode(apstTdMixScalerReg, ch1mode_udata.u32);

    U_TD_WB_CH1_ERR_UNIT           ch1unit_udata;
    ch1unit_udata.u32 = 0;
    ch1unit_udata.bits.unit     = wbCtl->ch1Ctl.err_unit;
    TD_CORE_DRV_SET_WBCh1ErrUnit(apstTdMixScalerReg, ch1unit_udata.u32);

    U_TD_WB_CH1_ERR_TH             ch1th_udata;
    ch1th_udata.u32 = 0;
    ch1th_udata.bits.threshold  = wbCtl->ch1Ctl.err_threshold;
    TD_CORE_DRV_SET_WBCh1ErrTH(apstTdMixScalerReg, ch1th_udata.u32);

    U_TD_WB_CH1_INFO_CLR           ch1Ctl_udata;
    ch1Ctl_udata.u32 = 0;
    ch1Ctl_udata.bits.fifoerrclear = wbCtl->ch1Ctl.infoClr.fifoerrclear;
    ch1Ctl_udata.bits.frmcntclear  = wbCtl->ch1Ctl.infoClr.frmcntclear;
    ch1Ctl_udata.bits.maxbw    = wbCtl->ch1Ctl.infoClr.maxbw;
    ch1Ctl_udata.bits.totalbw  = wbCtl->ch1Ctl.infoClr.totalbw;
    TD_CORE_DRV_SET_WBCh1InfoClr(apstTdMixScalerReg, ch1Ctl_udata.u32);

    U_TD_WB_CH1_RST_REQ            ch1req_udata;
    ch1req_udata.u32 = 0;
    ch1req_udata.bits.request   = wbCtl->ch1Ctl.request;
    TD_CORE_DRV_SET_WBCh1RstReq(apstTdMixScalerReg, ch1req_udata.u32);

    return 0;
}
/*
*
*/
int TD_DRV_SetCore(TD_CORE_CTL_S *tdCoreCtl)
{
    TD_CHECK_POINTER(tdCoreCtl);

    TD_DRV_SetRot(&tdCoreCtl->rotAllCtl);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);    

    U_TD_SOFT_RST_CTL              softrst_udata;
    softrst_udata.u32 = 0;
    softrst_udata.bits.apb    = tdCoreCtl->rstCtl.apb;
    softrst_udata.bits.axi    = tdCoreCtl->rstCtl.axi;
    softrst_udata.bits.core   = tdCoreCtl->rstCtl.core;
    softrst_udata.bits.mix    = tdCoreCtl->rstCtl.mix;
    TD_CORE_DRV_SET_SoftRstCtl(apstTdMixScalerReg,softrst_udata.u32);
	
		U_TD_DMA_SW_CTL                dmasw_udata;
    dmasw_udata.u32 = 0;
    dmasw_udata.bits.reqrd    = tdCoreCtl->swCtl.reqrd;
    dmasw_udata.bits.reqwr    = tdCoreCtl->swCtl.reqwr;
    TD_CORE_DRV_SET_DmaSWCtl(apstTdMixScalerReg,dmasw_udata.u32);	

    TD_DRV_SetDisp(&tdCoreCtl->dispAllCtl);

    TD_DRV_SetLayer0Scaler(&tdCoreCtl->layer0Ctl);
    TD_DRV_SetLayer4Osd0(&tdCoreCtl->layer4OsdCtl);

    TD_DRV_SetYuv2Rgb(&tdCoreCtl->yuv2rgb);

    TD_DRV_SetDispMix(&tdCoreCtl->dispMixCtl);

    TD_DRV_SetInt(&tdCoreCtl->dispIrqCtl);

    TD_DRV_SetWb(&tdCoreCtl->wbCtl);
    
    return 0;
}
/*
*DEBUG
*/
int TD_DRV_GetCoreRegsVal(void)
{

    S_TD_ROTATION_REGS_TYPE *apstTdRotationReg = NULL;
    TD_DRV_ROTATION_REG_CTX(apstTdRotationReg);

    TD_CORE_DRV_GET_RotationRegsVal(apstTdRotationReg);

    S_TD_MIX_SCALER_REGS_TYPE *apstTdMixScalerReg = NULL;
    TD_DRV_MIX_SCALER_REG_CTX(apstTdMixScalerReg);

	TD_CORE_DRV_GET_MixScalerRegsVal(apstTdMixScalerReg);

  	return 0;
}
