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
  File Name     : vo_core_drv.c
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#include "isp_com.h"
#include "video_subsystem.h"
#include "vo/vo.h"
#include "vo/core/vo_core_reg.h"
#include "vo/core/vo_core_drv.h"

/*
*
*/
int Vo_Drv_Wrap_SetRst(struct isp_device *isp,VO_SOFT_RST_CTL_S *swRstCtl)
{
    VO_CHECK_POINTER(swRstCtl);
    VO_CHECK_POINTER(isp);

 	U_VO_SOFT_RST_CTL  rst_udata;
    rst_udata.u32 = 0;
    rst_udata.bits.apb          = swRstCtl->apb;//1;
    rst_udata.bits.core         = swRstCtl->core;//1;
    rst_udata.bits.disp         = swRstCtl->disp;//1;
    rst_udata.bits.vo           = swRstCtl->vo;//1;
	isp_reg_writel(isp,rst_udata.u32,ISP_IOMEM_VO_CORE,VO_SOFT_RST_CTL);

    return 0;  
}
/*
*dma
*/
int Vo_Drv_Wrap_SetDma(struct isp_device *isp,VO_DMA_CTL_S *dmaCtl)
{
    VO_CHECK_POINTER(dmaCtl);
    VO_CHECK_POINTER(isp);

	U_VO_DMA_SW_CTL     sw_udata ;
    sw_udata.u32 = 0;
    sw_udata.bits.reqrd         = dmaCtl->sw_ctl.reqrd;
    sw_udata.bits.reqwr         = dmaCtl->sw_ctl.reqwr;
	isp_reg_writel(isp,sw_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_SW_CTL);

	//  U_VO_DMA_RD_CTL_OUT               rd_udata;
    //rd_udata.bits.rdrstrdy      = dmaCtl->rd_ctl_out.rdrstrdy;
    //rd_udata.bits.rdst          = dmaCtl->rd_ctl_out.rdst;
    //rd_udata.bits.wrrstrdy      = dmaCtl->rd_ctl_out.wrrstrdy;
    //rd_udata.bits.wrst          = dmaCtl->rd_ctl_out.wrst;
  	//VO_CORE_DRV_SET_DmaRdCtlOut(isp,rd_udata.u32);

	U_VO_DMA_ARB_MODE   arbmode_udata;
    arbmode_udata.u32 = 0;
    arbmode_udata.bits.rd_arb_mode= dmaCtl->arb_mode.rd_arb_mode;
    arbmode_udata.bits.wr_arb_mode= dmaCtl->arb_mode.wr_arb_mode;
	isp_reg_writel(isp,arbmode_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_ARB_MODE);

	U_VO_DMA_WEIGHT_RD0               weightrd0_udata;
    weightrd0_udata.u32 = 0;
    weightrd0_udata.bits.chl0   = dmaCtl->weight_rd.chl0;
    weightrd0_udata.bits.chl1   = dmaCtl->weight_rd.chl1;
    weightrd0_udata.bits.chl2   = dmaCtl->weight_rd.chl2;
    weightrd0_udata.bits.chl3   = dmaCtl->weight_rd.chl3;
	isp_reg_writel(isp,weightrd0_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_WEIGHT_RD0);


	U_VO_DMA_WEIGHT_RD1               weightrd1_udata;
    weightrd1_udata.u32 = 0;
    weightrd1_udata.bits.chl4   = dmaCtl->weight_rd.chl4;
    weightrd1_udata.bits.chl5   = dmaCtl->weight_rd.chl5;
    weightrd1_udata.bits.chl6   = dmaCtl->weight_rd.chl6;
    weightrd1_udata.bits.chl7   = dmaCtl->weight_rd.chl7;
	isp_reg_writel(isp,weightrd1_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_WEIGHT_RD1);

	U_VO_DMA_WEIGHT_RD2               weightrd2_udata;
    weightrd2_udata.u32 = 0;
    weightrd2_udata.bits.chl8   = dmaCtl->weight_rd.chl8;
    weightrd2_udata.bits.chl9   = dmaCtl->weight_rd.chl9;
    weightrd2_udata.bits.chl10   = dmaCtl->weight_rd.chl10;
    weightrd2_udata.bits.chl11   = dmaCtl->weight_rd.chl11;
	isp_reg_writel(isp,weightrd2_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_WEIGHT_RD2);

	U_VO_DMA_WEIGHT_RD3               weightrd3_udata;
    weightrd3_udata.u32 = 0;
    weightrd3_udata.bits.chl12   = dmaCtl->weight_rd.chl12;
    weightrd3_udata.bits.chl13   = dmaCtl->weight_rd.chl13;
    weightrd3_udata.bits.chl14   = dmaCtl->weight_rd.chl14;
    weightrd3_udata.bits.chl15   = dmaCtl->weight_rd.chl15;
	isp_reg_writel(isp,weightrd3_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_WEIGHT_RD3);

	U_VO_DMA_PRIORITY_RD_0            priorrd0_udata;
    priorrd0_udata.u32 = 0;
    priorrd0_udata.bits.chl0     = dmaCtl->prior_rd.chl0;
    priorrd0_udata.bits.chl1     = dmaCtl->prior_rd.chl1;
    priorrd0_udata.bits.chl2     = dmaCtl->prior_rd.chl2;
    priorrd0_udata.bits.chl3     = dmaCtl->prior_rd.chl3;
    priorrd0_udata.bits.chl4     = dmaCtl->prior_rd.chl4;
    priorrd0_udata.bits.chl5     = dmaCtl->prior_rd.chl5;
    priorrd0_udata.bits.chl6     = dmaCtl->prior_rd.chl6;
    priorrd0_udata.bits.chl7     = dmaCtl->prior_rd.chl7;
	isp_reg_writel(isp,priorrd0_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_PRIORITY_RD_0);

	U_VO_DMA_PRIORITY_RD_1            priorrd1_udata;
    priorrd1_udata.u32 = 0;
    priorrd1_udata.bits.chl8     = dmaCtl->prior_rd.chl8;
    priorrd1_udata.bits.chl9     = dmaCtl->prior_rd.chl9;
    priorrd1_udata.bits.chl10    = dmaCtl->prior_rd.chl10;
    priorrd1_udata.bits.chl11    = dmaCtl->prior_rd.chl11;
    priorrd1_udata.bits.chl12    = dmaCtl->prior_rd.chl12;
    priorrd1_udata.bits.chl13    = dmaCtl->prior_rd.chl13;
    priorrd1_udata.bits.chl14    = dmaCtl->prior_rd.chl14;
    priorrd1_udata.bits.chl15    = dmaCtl->prior_rd.chl15;
	isp_reg_writel(isp,priorrd1_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_PRIORITY_RD_1);   

	U_VO_DMA_ID_RD_0                  idrd0_udata;
    idrd0_udata.u32 = 0;
    idrd0_udata.bits.chl0        = dmaCtl->id_rd.chl0;
    idrd0_udata.bits.chl1        = dmaCtl->id_rd.chl1;
    idrd0_udata.bits.chl2        = dmaCtl->id_rd.chl2;
    idrd0_udata.bits.chl3        = dmaCtl->id_rd.chl3;
    idrd0_udata.bits.chl4        = dmaCtl->id_rd.chl4;
    idrd0_udata.bits.chl5        = dmaCtl->id_rd.chl5;
    idrd0_udata.bits.chl6        = dmaCtl->id_rd.chl6;
    idrd0_udata.bits.chl7        = dmaCtl->id_rd.chl7;
	isp_reg_writel(isp,idrd0_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_ID_RD_0);

	U_VO_DMA_ID_RD_1                  idrd1_udata;
    idrd1_udata.u32 = 0;
    idrd1_udata.bits.chl8        = dmaCtl->id_rd.chl8;
    idrd1_udata.bits.chl9        = dmaCtl->id_rd.chl9;
    idrd1_udata.bits.chl10       = dmaCtl->id_rd.chl10;
    idrd1_udata.bits.chl11       = dmaCtl->id_rd.chl11;
    idrd1_udata.bits.chl12       = dmaCtl->id_rd.chl12;
    idrd1_udata.bits.chl13       = dmaCtl->id_rd.chl13;
    idrd1_udata.bits.chl14       = dmaCtl->id_rd.chl14;
    idrd1_udata.bits.chl15       = dmaCtl->id_rd.chl15;
	isp_reg_writel(isp,idrd1_udata.u32,ISP_IOMEM_VO_CORE,VO_DMA_ID_RD_1);

    return 0;
}
/*
*
*/
int Vo_Drv_Wrap_SetFirstCfgDone(struct isp_device *isp,VO_LOAD_CTL_S *loadCtl)
{
    VO_CHECK_POINTER(loadCtl);
    VO_CHECK_POINTER(isp);

	U_VO_LOAD_CTL                     load_udata;
    load_udata.u32 = 0;
    load_udata.bits.regfirstload= loadCtl->regfirstload ;//1;
    load_udata.bits.regready    = loadCtl->regready;//1;
	isp_reg_writel(isp,load_udata.u32,ISP_IOMEM_VO_CORE,VO_LOAD_CTL);

    return 0;
}
/*
*
*/
int Vo_Drv_Wrap_SetCfgDone(struct isp_device *isp,VO_LOAD_CTL_S *loadCtl)
{
    VO_CHECK_POINTER(loadCtl);
    VO_CHECK_POINTER(isp);

	U_VO_LOAD_CTL    load_udata;    
    load_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_LOAD_CTL);
    load_udata.bits.regready    = loadCtl->regready;//1;
	isp_reg_writel(isp,load_udata.u32,ISP_IOMEM_VO_CORE,VO_LOAD_CTL);

    return 0;
}
/*
*
*/
int Vo_Drv_Wrap_SetBDCtl(struct isp_device *isp,VO_BD_LAYER_CTL_S *bdLayerCtl)
{
    VO_CHECK_POINTER(bdLayerCtl);
    VO_CHECK_POINTER(isp);

	U_VO_LAYER0_LINE0_BD_CTL          line0_udata;
    line0_udata.u32 = 0;
    line0_udata.bits.limiten    = bdLayerCtl->layer0_line0_bd_ctl.limiten;
    line0_udata.bits.outstand   = bdLayerCtl->layer0_line0_bd_ctl.outstand;
	isp_reg_writel(isp,line0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_LINE0_BD_CTL);

	U_VO_LAYER0_LINE1_BD_CTL          line1_udata;
    line1_udata.u32 = 0;
    line1_udata.bits.limiten    = bdLayerCtl->layer0_line1_bd_ctl.limiten;
    line1_udata.bits.outstand   = bdLayerCtl->layer0_line1_bd_ctl.outstand;    
	isp_reg_writel(isp,line1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_LINE1_BD_CTL);

	U_VO_LAYER0_LINE2_BD_CTL          line2_udata;
    line2_udata.u32 = 0;
    line2_udata.bits.limiten    = bdLayerCtl->layer0_line2_bd_ctl.limiten;
    line2_udata.bits.outstand   = bdLayerCtl->layer0_line2_bd_ctl.outstand;    
	isp_reg_writel(isp,line2_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_LINE2_BD_CTL);
      
	U_VO_LAYER0_LINE3_BD_CTL          line3_udata;
    line3_udata.u32 = 0;
    line3_udata.bits.limiten    = bdLayerCtl->layer0_line3_bd_ctl.limiten;
    line3_udata.bits.outstand   = bdLayerCtl->layer0_line3_bd_ctl.outstand;
	isp_reg_writel(isp,line3_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_LINE3_BD_CTL);

	U_VO_LAYER1_BD_CTL                bd_udata;
    bd_udata.u32 = 0;
    bd_udata.bits.limiten        = bdLayerCtl->layer1_bd_ctl.limiten;
    bd_udata.bits.outstand        = bdLayerCtl->layer1_bd_ctl.outstand;
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_BD_CTL);

    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = bdLayerCtl->layer2_bd_ctl.limiten;
    bd_udata.bits.outstand      = bdLayerCtl->layer2_bd_ctl.outstand;
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_BD_CTL);
    
    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = bdLayerCtl->layer3_bd_ctl.limiten;
    bd_udata.bits.outstand      = bdLayerCtl->layer3_bd_ctl.outstand;
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_BD_CTL);

    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = bdLayerCtl->layer4_bd_ctl.limiten;
    bd_udata.bits.outstand      = bdLayerCtl->layer4_bd_ctl.outstand;    
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER4_BD_CTL);

    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = bdLayerCtl->layer5_bd_ctl.limiten;
    bd_udata.bits.outstand      = bdLayerCtl->layer5_bd_ctl.outstand;    
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER5_BD_CTL);

    bd_udata.u32 = 0;
    bd_udata.bits.limiten       = bdLayerCtl->layer6_bd_ctl.limiten;
    bd_udata.bits.outstand      = bdLayerCtl->layer6_bd_ctl.outstand;    
	isp_reg_writel(isp,bd_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER6_BD_CTL);

    return 0;
}
/*
*
*/
int Vo_Drv_Wrap_SetInit(struct isp_device *isp,VO_LOAD_CTL_S *loadCtl)
{
	VO_CHECK_POINTER(loadCtl);
    VO_CHECK_POINTER(isp);

	Vo_Drv_Wrap_SetFirstCfgDone(isp,loadCtl);

	return 0;
}

/*
*
*/
int Vo_Drv_Core_SetDispEn(struct isp_device *isp,unsigned int dispEnable)
{
    VO_CHECK_POINTER(isp);

    U_VO_DISP_ENABLE en_udata;
    en_udata.u32 = 0;
    en_udata.u32 =  dispEnable;
    isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetDisp(struct isp_device *isp,VO_DISP_CTL_S *dispCtl)
{
    VO_CHECK_POINTER(dispCtl);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_XZONE_CTL               xzone_udata;
    xzone_udata.u32 = 0;
    xzone_udata.bits.start      = dispCtl->xZoneCtl.start;
    xzone_udata.bits.stop       = dispCtl->xZoneCtl.stop;
  	isp_reg_writel(isp,xzone_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_XZONE_CTL);

	U_VO_DISP_YZONE_CTL               yzone_udata;
    yzone_udata.u32 = 0;
    yzone_udata.bits.start      = dispCtl->yZoneCtl.start;
    yzone_udata.bits.stop       = dispCtl->yZoneCtl.stop;
	isp_reg_writel(isp,yzone_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YZONE_CTL);

	U_VO_DISP_HSYNC_CTL               hsync_udata;
    hsync_udata.u32 = 0;
    hsync_udata.bits.start      = dispCtl->dispHsyncCtl.start;
    hsync_udata.bits.stop       = dispCtl->dispHsyncCtl.stop;
	isp_reg_writel(isp,hsync_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_HSYNC_CTL);

	U_VO_DISP_HSYNC1_CTL              hsync1_udata;
    hsync1_udata.u32 = 0;
    hsync1_udata.bits.start      = dispCtl->dispHsync1Ctl.start;
    hsync1_udata.bits.stop       = dispCtl->dispHsync1Ctl.stop;    
	isp_reg_writel(isp,hsync1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_HSYNC1_CTL);

	U_VO_DISP_VSYNC1_CTL              vsync1_udata;
    vsync1_udata.u32 = 0;
    vsync1_udata.bits.start      = dispCtl->dispVsync1Ctl.start;
    vsync1_udata.bits.stop       = dispCtl->dispVsync1Ctl.stop;    
	isp_reg_writel(isp,vsync1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_VSYNC1_CTL);

	U_VO_DISP_HSYNC2_CTL              hsync2_udata;
    hsync2_udata.u32 = 0;
    hsync2_udata.bits.start      = dispCtl->dispHsync2Ctl.start;
    hsync2_udata.bits.stop       = dispCtl->dispHsync2Ctl.stop;      
	isp_reg_writel(isp,hsync2_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_HSYNC2_CTL);

	U_VO_DISP_VSYNC2_CTL              vsync2_udata;
    vsync2_udata.u32 = 0;
    vsync2_udata.bits.start      = dispCtl->dispVsync2Ctl.start;
    vsync2_udata.bits.stop       = dispCtl->dispVsync2Ctl.stop;     
	isp_reg_writel(isp,vsync2_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_VSYNC2_CTL);

	U_VO_DISP_CTL                     ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.bits.framesyncdly  = dispCtl->dispCtl0.framesyncdly;
    ctl_udata.bits.secndfoffset  = dispCtl->dispCtl0.secndfoffset;
    ctl_udata.bits.vcntbit0      = dispCtl->dispCtl0.vcntbit0;
    isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_CTL);

	U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = 0;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.disable        = dispCtl->dispEnable;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

	U_VO_DISP_SIZE                    size_udata;
    size_udata.u32 = 0;
    size_udata.bits.hsize        = dispCtl->dispSize.hsize;
    size_udata.bits.vsize        = dispCtl->dispSize.vsize;
	isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_SIZE);

    return 0;
}
/*
*layer0
*/
int Vo_Drv_Core_SetLayer0MfbdYBuf(struct isp_device *isp,VO_LAYER0_MFBD_Y_BUF_S *mfbdYBuf)
{
    VO_CHECK_POINTER(mfbdYBuf);
    VO_CHECK_POINTER(isp);

	U_VO_LAYER0_MFBD_DATA_ADDR0_Y     y0_udata;
    y0_udata.u32 = 0;
    y0_udata.bits.addr              = mfbdYBuf->y_addr0;
	isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_ADDR0_Y);

	U_VO_LAYER0_MFBD_DATA_ADDR1_Y     y1_udata;
    y1_udata.u32 = 0;
    y1_udata.bits.addr              = mfbdYBuf->y_addr1;
	isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_ADDR1_Y);

	U_VO_LAYER0_MFBD_DATA_STRIDE0_Y   ystride0_udata;
    ystride0_udata.u32 = 0;
    ystride0_udata.bits.stride      = mfbdYBuf->y_stride0;
    isp_reg_writel(isp,ystride0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_STRIDE0_Y);

	U_VO_LAYER0_MFBD_DATA_STRIDE1_Y   ystride1_udata;
    ystride1_udata.u32 = 0;
    ystride1_udata.bits.stride      = mfbdYBuf->y_stride1;
	isp_reg_writel(isp,ystride1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_STRIDE1_Y);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetLayer0MfbdYHeadBuf(struct isp_device *isp,VO_LAYER0_MFBD_Y_HEAD_BUF_S  *mfbdYHeadBuf)
{
    VO_CHECK_POINTER(mfbdYHeadBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_MFBD_HEAD_ADDR0_Y     yhead0_udata;
    yhead0_udata.u32 = 0;
    yhead0_udata.bits.addr          = mfbdYHeadBuf->y_head_addr0;
   isp_reg_writel(isp,yhead0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_ADDR0_Y);

    U_VO_LAYER0_MFBD_HEAD_ADDR1_Y     yhead1_udata;
    yhead1_udata.u32 = 0;
    yhead1_udata.bits.addr          = mfbdYHeadBuf->y_head_addr1;
	isp_reg_writel(isp,yhead1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_ADDR1_Y);


    U_VO_LAYER0_MFBD_HEAD_STRIDE0_Y   yheadstride0_udata;
    yheadstride0_udata.u32 = 0;
    yheadstride0_udata.bits.stride  = mfbdYHeadBuf->y_head_stride0;
	isp_reg_writel(isp,yheadstride0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_STRIDE0_Y);

    U_VO_LAYER0_MFBD_HEAD_STRIDE1_Y   yheadstride1_udata;
    yheadstride1_udata.u32 = 0;
    yheadstride1_udata.bits.stride  = mfbdYHeadBuf->y_head_stride1;
	isp_reg_writel(isp,yheadstride1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_STRIDE1_Y);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetLayer0MfbdUVBuf(struct isp_device *isp,VO_LAYER0_MFBD_UV_BUF_S *mfbdUVBuf)
{
    VO_CHECK_POINTER(mfbdUVBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_MFBD_DATA_ADDR0_UV    uv0_udata;
    uv0_udata.u32 = 0;
    uv0_udata.bits.addr             = mfbdUVBuf->uv_addr0;
	isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_ADDR0_UV);

    U_VO_LAYER0_MFBD_DATA_ADDR1_UV    uv1_udata;
    uv1_udata.u32 = 0;
    uv1_udata.bits.addr             = mfbdUVBuf->uv_addr1;
	isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_ADDR1_UV);

    U_VO_LAYER0_MFBD_DATA_STRIDE0_UV  uvstride0_udata;
    uvstride0_udata.u32 = 0;
    uvstride0_udata.bits.stride     = mfbdUVBuf->uv_stride0;
	isp_reg_writel(isp,uvstride0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_STRIDE0_UV);
    
    U_VO_LAYER0_MFBD_DATA_STRIDE1_UV  uvstride1_udata;
    uvstride1_udata.u32 = 0;
    uvstride1_udata.bits.stride     = mfbdUVBuf->uv_stride1;
	isp_reg_writel(isp,uvstride1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_DATA_STRIDE1_UV);

    return 0;  
}
/*
*
*/
int Vo_Drv_Core_SetLayer0MfbdUVHeadBuf(struct isp_device *isp,VO_LAYER0_MFBD_UV_HEAD_BUF_S *mfbdUVHeadBuf)
{
    VO_CHECK_POINTER(mfbdUVHeadBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_MFBD_HEAD_ADDR0_UV    uvhead0_udata;
    uvhead0_udata.u32 = 0;
    uvhead0_udata.bits.addr         = mfbdUVHeadBuf->uv_head_addr0;
	isp_reg_writel(isp,uvhead0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_ADDR0_UV);

    U_VO_LAYER0_MFBD_HEAD_ADDR1_UV    uvhead1_udata;
    uvhead1_udata.u32 = 0;
    uvhead1_udata.bits.addr         = mfbdUVHeadBuf->uv_head_addr0;
	isp_reg_writel(isp,uvhead1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_ADDR1_UV);

    U_VO_LAYER0_MFBD_HEAD_STRIDE0_UV  uvheadstride0_udata;
    uvheadstride0_udata.u32 = 0;
    uvheadstride0_udata.bits.stride = mfbdUVHeadBuf->uv_head_stride0;
	isp_reg_writel(isp,uvheadstride0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_STRIDE0_UV);

    U_VO_LAYER0_MFBD_HEAD_STRIDE1_UV  uvheadstride1_udata;
    uvheadstride1_udata.u32 = 0;
    uvheadstride1_udata.bits.stride = mfbdUVHeadBuf->uv_head_stride1;
	isp_reg_writel(isp,uvheadstride1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD_HEAD_STRIDE1_UV);

    return 0;  
}
/*
*
*/
int Vo_Drv_Core_SetLayer0Mfbd(struct isp_device *isp,VO_LAYER0_MFBD_CTL_S *layer0MfbdCtl)
{
    VO_CHECK_POINTER(layer0MfbdCtl);
    VO_CHECK_POINTER(isp);

    VO_LAYER0_MFBD_Y_BUF_S *mfbdYBuf = &layer0MfbdCtl->mfbdYBuf;
    Vo_Drv_Core_SetLayer0MfbdYBuf(isp,mfbdYBuf);

    VO_LAYER0_MFBD_Y_HEAD_BUF_S  *mfbdYHeadBuf = &layer0MfbdCtl->mfbdYHeadBuf;
    Vo_Drv_Core_SetLayer0MfbdYHeadBuf(isp,mfbdYHeadBuf);

    VO_LAYER0_MFBD_UV_BUF_S *mfbdUVBuf = &layer0MfbdCtl->mfbdUVBuf;
    Vo_Drv_Core_SetLayer0MfbdUVBuf(isp,mfbdUVBuf);

    VO_LAYER0_MFBD_UV_HEAD_BUF_S *mfbdUVHeadBuf = &layer0MfbdCtl->mfbdUVHeadBuf;
    Vo_Drv_Core_SetLayer0MfbdUVHeadBuf(isp,mfbdUVHeadBuf);

    U_VO_LAYER0_MFBD                  mfbden_udata;
    mfbden_udata.u32 = 0;
    mfbden_udata.bits.en              = layer0MfbdCtl->mfbd_en;
	isp_reg_writel(isp,mfbden_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_MFBD);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetLayer0Area(struct isp_device *isp,VO_LAYER0_AREA_CTL_S  *areaCtl)
{
    VO_CHECK_POINTER(areaCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_XCTL                  xctl_udata;
    xctl_udata.u32 = 0;
    xctl_udata.bits.start       = areaCtl->xCtl.start;
    xctl_udata.bits.stop        = areaCtl->xCtl.stop;
  	isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_XCTL);
 
    U_VO_LAYER0_YCTL                  yctl_udata;
    yctl_udata.u32 = 0;
    yctl_udata.bits.start       = areaCtl->yCtl.start;
    yctl_udata.bits.stop        = areaCtl->yCtl.stop;
	isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_YCTL);

    return 0; 
};

int Vo_Drv_Core_SetLayer0Buf(struct isp_device *isp,VO_YUV_BUF_S  *yuvBuf)
{
    VO_CHECK_POINTER(yuvBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_BADDR0_Y              y0_udata;
    y0_udata.u32 = 0;
    y0_udata.bits.addr          = yuvBuf->yAddr0;
	isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_BADDR0_Y);

    U_VO_LAYER0_BADDR0_UV             uv0_udata;
    uv0_udata.u32 = 0;
    uv0_udata.bits.addr         = yuvBuf->uvAddr0;
	isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_BADDR0_UV);

    U_VO_LAYER0_BADDR1_Y              y1_udata;
    y1_udata.u32 = 0;
    y1_udata.bits.addr          = yuvBuf->yAddr1;
	isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_BADDR1_Y);

    U_VO_LAYER0_BADDR1_UV             uv1_udata;
    uv1_udata.u32 = 0;
    uv1_udata.bits.addr         = yuvBuf->uvAddr1;
	isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_BADDR1_UV);

    U_VO_LAYER0_IMG_IN_STRIDE         stride_udata;
    stride_udata.u32 = 0; 
    stride_udata.bits.hsize     = yuvBuf->stride.hsize;
    stride_udata.bits.vsize     = yuvBuf->stride.vsize;
	isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_IN_STRIDE);

    U_VO_LAYER0_IMG_IN_MEM_HSIZE    hsize_udata;
    hsize_udata.u32  = 0;
    hsize_udata.bits.mem_hsize = 1;
    isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_IN_MEM_HSIZE);
    return 0;
}

int Vo_Drv_Core_SetLayer0Size(struct isp_device *isp,VO_LAYER0_SIZE_S  *sizeCtl)
{
    VO_CHECK_POINTER(sizeCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_IMG_IN_PIX_SZIE       imginsize_udata;
    imginsize_udata.u32 = 0;
    imginsize_udata.bits.hsize  = sizeCtl->imgInSize.hsize;
    imginsize_udata.bits.vsize  = sizeCtl->imgInSize.vsize;
	isp_reg_writel(isp,imginsize_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_IN_PIX_SZIE);
   
    U_VO_LAYER0_IMG_OUT_PIX_SZIE      imgoutsize_udata;
    imgoutsize_udata.u32 = 0;
    imgoutsize_udata.bits.hsize = sizeCtl->imgOutSize.hsize;
    imgoutsize_udata.bits.vsize = sizeCtl->imgOutSize.vsize;
	isp_reg_writel(isp,imgoutsize_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_OUT_PIX_SZIE); 

    
    U_VO_LAYER0_IMG_IN_OFFSET         offset_udata;
    offset_udata.u32 = 0;
    offset_udata.bits.hoffset   = sizeCtl->imgOffset.hsize;
    offset_udata.bits.voffset   = sizeCtl->imgOffset.vsize;
	isp_reg_writel(isp,offset_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_IN_OFFSET);

    return 0;
};

int Vo_Drv_Core_SetLayer0Scaler(struct isp_device *isp,VO_LAYER0_SCALE_S  *scaleCtl)
{
    VO_CHECK_POINTER(scaleCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER0_VSCALE_STEP           vstep_udata;
    vstep_udata.u32 = 0;
    vstep_udata.bits.dstep      = scaleCtl->vScaleCtl.dstep;
    vstep_udata.bits.pstep      = scaleCtl->vScaleCtl.pstep;
	isp_reg_writel(isp,vstep_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_VSCALE_STEP);
   
    U_VO_LAYER0_VSCALE_ST             vst_udata;
    vst_udata.u32 = 0;
    vst_udata.bits.pstep        = scaleCtl->vScaleCtl.pstep_st;
	isp_reg_writel(isp,vst_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_VSCALE_ST);
   
    U_VO_LAYER0_HSCALE_STEP           hstep_udata;
    hstep_udata.u32 = 0;
    hstep_udata.bits.dstep      = scaleCtl->hScaleCtl.dstep;
    hstep_udata.bits.pstep      = scaleCtl->hScaleCtl.pstep;    
	isp_reg_writel(isp,hstep_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_HSCALE_STEP);
    
    U_VO_LAYER0_HSCALE_ST             hst_udata;
    hst_udata.u32 = 0;
    hst_udata.bits.pstep        = scaleCtl->hScaleCtl.pstep_st;
	isp_reg_writel(isp,hst_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_HSCALE_ST);

    return 0;
}

int Vo_Drv_Core_SetLayer0(struct isp_device *isp,VO_LAYER0_CTL_S  *layer0Ctl)
{
    VO_CHECK_POINTER(layer0Ctl);
    VO_CHECK_POINTER(isp);

    VO_LAYER0_AREA_CTL_S  *areaCtl = &layer0Ctl->areaCtl;
    Vo_Drv_Core_SetLayer0Area(isp,areaCtl);

    U_VO_LAYER0_CTL                   ctl_udata;
    ctl_udata.bits.enable       = layer0Ctl->layer0En;
	isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_CTL);

    U_VO_LAYER0_SCALE_BLENTH          blen_udata;
    blen_udata.bits.blen        = layer0Ctl->scalerBlen;
	isp_reg_writel(isp,blen_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_SCALE_BLENTH);

    U_VO_LAYER0_IMG_IN_DAT_MODE       datMode_udata;
    datMode_udata.u32 =0;
    datMode_udata.bits.datmode  = layer0Ctl->imgInDatMode.datmode;
    datMode_udata.bits.endianuv = layer0Ctl->imgInDatMode.endianuv;
    datMode_udata.bits.endiany  = layer0Ctl->imgInDatMode.endiany;
    datMode_udata.bits.swi      = layer0Ctl->imgInDatMode.swi;
	isp_reg_writel(isp,datMode_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_IMG_IN_DAT_MODE);

    VO_YUV_BUF_S  *yuvBuf = &layer0Ctl->yuvBuf;
    Vo_Drv_Core_SetLayer0Buf(isp,yuvBuf);

    VO_LAYER0_SIZE_S  *sizeCtl = &layer0Ctl->sizeCtl;
    Vo_Drv_Core_SetLayer0Size(isp,sizeCtl);

    VO_LAYER0_SCALE_S  *scaleCtl = &layer0Ctl->scaleCtl;
    Vo_Drv_Core_SetLayer0Scaler(isp,scaleCtl);
    
    U_VO_LAYER0_BASE_MODE             basemode_udata;
    //basemode_udata.bits.addrflag= layer0Ctl->baseMode.addrflag;
    basemode_udata.bits.base0mask= layer0Ctl->baseMode.base0mask;
    basemode_udata.bits.base1mask= layer0Ctl->baseMode.base1mask;
    basemode_udata.bits.mode     = layer0Ctl->baseMode.mode;
	isp_reg_writel(isp,basemode_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER0_BASE_MODE);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer0en            = layer0Ctl->layer0DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

    VO_LAYER0_MFBD_CTL_S *layer0MfbdCtl = &layer0Ctl->layer0MfbdCtl;
    if( 1 == layer0MfbdCtl->mfbd_en)
    {
        Vo_Drv_Core_SetLayer0Mfbd(isp,layer0MfbdCtl);
    }
    
    return 0;
}
/*
*layer1
*/
int Vo_Drv_Core_SetLayer1Area(struct isp_device *isp,VO_AREA_S *areaCtl)
{
    VO_CHECK_POINTER(areaCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER1_XCTL                  xctl_udata;
    xctl_udata.bits.start        = areaCtl->xCtl.start;
    xctl_udata.bits.stop         = areaCtl->xCtl.stop;
    isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_XCTL);

    U_VO_LAYER1_YCTL                  yctl_udata;
    yctl_udata.bits.start        = areaCtl->yCtl.start;
    yctl_udata.bits.stop         = areaCtl->yCtl.stop;    
    isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_YCTL);

    return 0;
};

int Vo_Drv_Core_SetLayer1Buf(struct isp_device *isp,VO_YUV_BUF_S  *yuvBuf)
{
    VO_CHECK_POINTER(yuvBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER1_IMG_IN_BADDR0_Y       y0_udata;
    y0_udata.bits.addr           = yuvBuf->yAddr0;
    isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_BADDR0_Y);

    U_VO_LAYER1_IMG_IN_BADDR0_UV      uv0_udata;
    uv0_udata.bits.addr          = yuvBuf->uvAddr0;
    isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_BADDR0_UV);

    U_VO_LAYER1_IMG_IN_BADDR1_Y       y1_udata;
    y1_udata.bits.addr           = yuvBuf->yAddr1;
    isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_BADDR1_Y);

    U_VO_LAYER1_IMG_IN_BADDR1_UV      uv1_udata;
    uv1_udata.bits.addr          = yuvBuf->uvAddr1;
    isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_BADDR1_UV);

    U_VO_LAYER1_IMG_IN_STRIDE         stride_udata;
    stride_udata.bits.hsize      = yuvBuf->stride.hsize;
    stride_udata.bits.vsize      = yuvBuf->stride.vsize;
    isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_STRIDE);

    return 0;
};

int Vo_Drv_Core_SetLayer1Size(struct isp_device *isp,VO_LAYER_SIZE_S  *sizeCtl)
{
    VO_CHECK_POINTER(sizeCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER1_IMG_IN_OFFSET         offset_udata;
    offset_udata.bits.hoffset    = sizeCtl->imgOffset.hsize;
    offset_udata.bits.voffset    = sizeCtl->imgOffset.vsize;
    isp_reg_writel(isp,offset_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_OFFSET);

    U_VO_LAYER1_IMG_IN_PIX_SIZE       size_udata;
    size_udata.bits.hsize        = sizeCtl->imgInPixSize.hsize;
    size_udata.bits.vsize        = sizeCtl->imgInPixSize.vsize;
    isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_PIX_SIZE);

    return 0;
};

int Vo_Drv_Core_SetLayer1(struct isp_device *isp,VO_LAYER1_CTL_S *layer1Ctl)
{
    VO_CHECK_POINTER(layer1Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S *areaCtl = &layer1Ctl->areaCtl;
    Vo_Drv_Core_SetLayer1Area(isp,areaCtl);

	U_VO_LAYER1_CTL                   ctl_udata;
	ctl_udata.u32                = 0;
    ctl_udata.bits.enable        = layer1Ctl->layerCtl.enable;
    ctl_udata.bits.endianuv      = layer1Ctl->layerCtl.endianuv;
    ctl_udata.bits.endiany       = layer1Ctl->layerCtl.endiany;
    ctl_udata.bits.uvswap        = layer1Ctl->layerCtl.uvswap;
    ctl_udata.bits.yuv420en      = layer1Ctl->layerCtl.yuv420en;
    ctl_udata.bits.yuv422en      = layer1Ctl->layerCtl.yuv422en;     
    isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_CTL);

    VO_YUV_BUF_S  *yuvBuf  = &layer1Ctl->yuvBuf;
    Vo_Drv_Core_SetLayer1Buf(isp,yuvBuf);

    U_VO_LAYER1_IMG_IN_BLENTH         blen_udata;
    blen_udata.bits.blen         = layer1Ctl->imgInBlen.blen;
    blen_udata.bits.voffset      = layer1Ctl->imgInBlen.voffset;
    isp_reg_writel(isp,blen_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_IMG_IN_BLENTH);

    VO_LAYER_SIZE_S  *sizeCtl = &layer1Ctl->sizeCtl;
    Vo_Drv_Core_SetLayer1Size(isp,sizeCtl);

    U_VO_LAYER1_ADDR_SEL_MODE         selmode_udata;
//    selmode_udata.bits.addrflag  = layer1Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = layer1Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = layer1Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = layer1Ctl->baseMode.mode;
    isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER1_ADDR_SEL_MODE);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer1en            = layer1Ctl->layer1DispEn;    
    isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

    return 0;
}
/*
*Layer2
*/
int Vo_Drv_Core_SetLayer2Area(struct isp_device *isp,VO_AREA_S  *areaCtl)
{
    VO_CHECK_POINTER(areaCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER2_XCTL                  xctl_udata;
    xctl_udata.bits.start        = areaCtl->xCtl.start;
    xctl_udata.bits.stop         = areaCtl->xCtl.stop;  
    isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_XCTL);

    U_VO_LAYER2_YCTL                  yctl_udata;
    yctl_udata.bits.start        = areaCtl->yCtl.start;
    yctl_udata.bits.stop         = areaCtl->yCtl.stop;   
    isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_YCTL);

    return 0;
}

int Vo_Drv_Core_SetLayer2Buf(struct isp_device *isp,VO_YUV_BUF_S  *yuvBuf)
{
    VO_CHECK_POINTER(yuvBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER2_IMG_IN_BADDR0_Y       y0_udata;
    y0_udata.bits.addr           = yuvBuf->yAddr0;
    isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_BADDR0_Y);

    U_VO_LAYER2_IMG_IN_BADDR0_UV      uv0_udata;
    uv0_udata.bits.addr           = yuvBuf->uvAddr0;
    isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_BADDR0_UV);

    U_VO_LAYER2_IMG_IN_BADDR1_Y       y1_udata;
    y1_udata.bits.addr           = yuvBuf->yAddr1;
    isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_BADDR1_Y);

    U_VO_LAYER2_IMG_IN_BADDR1_UV      uv1_udata;
    uv1_udata.bits.addr           = yuvBuf->uvAddr1;
    isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_BADDR1_UV);

    U_VO_LAYER2_IMG_IN_STRIDE         stride_udata;
    stride_udata.bits.hsize       = yuvBuf->stride.hsize;
    stride_udata.bits.vsize       = yuvBuf->stride.vsize;
    isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_STRIDE);

    return 0;
}

int Vo_Drv_Core_SetLayer2Size(struct isp_device *isp,VO_LAYER_SIZE_S  *sizeCtl)
{
    VO_CHECK_POINTER(sizeCtl);
    VO_CHECK_POINTER(isp);

	U_VO_LAYER2_IMG_IN_OFFSET         offset_udata;
    offset_udata.bits.hoffset     = sizeCtl->imgOffset.hsize;
    offset_udata.bits.voffset     = sizeCtl->imgOffset.vsize;
    isp_reg_writel(isp,offset_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_OFFSET);

	U_VO_LAYER2_IMG_IN_PIX_SIZE       size_udata;
    size_udata.bits.hsize         = sizeCtl->imgInPixSize.hsize;
    size_udata.bits.vsize         = sizeCtl->imgInPixSize.vsize;
    isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_PIX_SIZE);

    return 0;
}

int Vo_Drv_Core_SetLayer2(struct isp_device *isp,VO_LAYER2_CTL_S *layer2Ctl)
{
    VO_CHECK_POINTER(layer2Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S  *areaCtl = &layer2Ctl->areaCtl;
    Vo_Drv_Core_SetLayer2Area(isp,areaCtl);

	U_VO_LAYER2_CTL                   ctl_udata;
	ctl_udata.u32                = 0;
    ctl_udata.bits.enable        = layer2Ctl->layerCtl.enable;
    ctl_udata.bits.endianuv      = layer2Ctl->layerCtl.endianuv;
    ctl_udata.bits.endiany       = layer2Ctl->layerCtl.endiany;
    ctl_udata.bits.uvswap         = layer2Ctl->layerCtl.uvswap;
    ctl_udata.bits.yuv420en      = layer2Ctl->layerCtl.yuv420en;
    ctl_udata.bits.yuv422en      = layer2Ctl->layerCtl.yuv422en;     
    isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_CTL);
 
    VO_YUV_BUF_S  *yuvBuf = &layer2Ctl->yuvBuf;
    Vo_Drv_Core_SetLayer2Buf(isp,yuvBuf);

	U_VO_LAYER2_IMG_IN_BLENTH         blen_udata;
    blen_udata.bits.blen          = layer2Ctl->imgInBlen.blen;
    blen_udata.bits.voffset       = layer2Ctl->imgInBlen.voffset;
    isp_reg_writel(isp,blen_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_IMG_IN_BLENTH);

    VO_LAYER_SIZE_S  *sizeCtl = &layer2Ctl->sizeCtl;
    Vo_Drv_Core_SetLayer2Size(isp,sizeCtl);

	U_VO_LAYER2_ADDR_SEL_MODE         selmode_udata;
    //selmode_udata.bits.addrflag  = layer2Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = layer2Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = 1;//layer2Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = layer2Ctl->baseMode.mode;    
    isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER2_ADDR_SEL_MODE);

	U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer2en            = layer2Ctl->layer2DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

    return 0;
}
/*
*Layer3
*/
int Vo_Drv_Core_SetLayer3Area(struct isp_device *isp,VO_AREA_S *areaCtl)
{
    VO_CHECK_POINTER(areaCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER3_XCTL                  xctl_udata;
    xctl_udata.bits.start       = areaCtl->xCtl.start;
    xctl_udata.bits.stop      = areaCtl->xCtl.stop;
    isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_XCTL);

    U_VO_LAYER3_YCTL                  yctl_udata;
    yctl_udata.bits.start       = areaCtl->yCtl.start;
    yctl_udata.bits.stop       = areaCtl->yCtl.stop;    
    isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_YCTL);

    return 0;
};

int Vo_Drv_Core_SetLayer3Buf(struct isp_device *isp,VO_YUV_BUF_S *yuvBuf)
{
    VO_CHECK_POINTER(yuvBuf);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER3_IMG_IN_BADDR0_Y       y0_udata;
    y0_udata.bits.addr           = yuvBuf->yAddr0;
    isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_BADDR0_Y);

    U_VO_LAYER3_IMG_IN_BADDR0_UV      uv0_udata;
    uv0_udata.bits.addr          = yuvBuf->uvAddr0;
    isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_BADDR0_UV);

    U_VO_LAYER3_IMG_IN_BADDR1_Y       y1_udata;
    y1_udata.bits.addr           = yuvBuf->yAddr1;
    isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_BADDR1_Y);

    U_VO_LAYER3_IMG_IN_BADDR1_UV      uv1_udata;
    uv1_udata.bits.addr          = yuvBuf->uvAddr1;
    isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_BADDR1_UV);

    U_VO_LAYER3_IMG_IN_STRIDE         stride_udata;
    stride_udata.bits.hsize      = yuvBuf->stride.hsize;
    stride_udata.bits.vsize      = yuvBuf->stride.vsize;
    isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_STRIDE);

    return 0;
};

int Vo_Drv_Core_SetLayer3Size(struct isp_device *isp,VO_LAYER_SIZE_S  *sizeCtl)
{
    VO_CHECK_POINTER(sizeCtl);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER3_IMG_IN_OFFSET         offset_udata;
    offset_udata.bits.hoffset    = sizeCtl->imgOffset.hsize;
    offset_udata.bits.voffset    = sizeCtl->imgOffset.vsize;
    isp_reg_writel(isp,offset_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_OFFSET);

    U_VO_LAYER3_IMG_IN_PIX_SIZE       size_udata;
    size_udata.bits.hsize        = sizeCtl->imgInPixSize.hsize;
    size_udata.bits.vsize        = sizeCtl->imgInPixSize.vsize;
    isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_PIX_SIZE);

    return 0;
};

int Vo_Drv_Core_SetLayer3(struct isp_device *isp,VO_LAYER3_CTL_S *layer3Ctl)
{
    VO_CHECK_POINTER(layer3Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S *areaCtl = &layer3Ctl->areaCtl;
    Vo_Drv_Core_SetLayer3Area(isp,areaCtl);

    U_VO_LAYER3_CTL                   ctl_udata;
    ctl_udata.u32                = 0;
    ctl_udata.bits.enable        = layer3Ctl->layerCtl.enable;
    ctl_udata.bits.endianuv      = layer3Ctl->layerCtl.endianuv;
    ctl_udata.bits.endiany       = layer3Ctl->layerCtl.endiany;
    ctl_udata.bits.uvswap        = layer3Ctl->layerCtl.uvswap;
    ctl_udata.bits.yuv420en      = layer3Ctl->layerCtl.yuv420en;
    ctl_udata.bits.yuv422en      = layer3Ctl->layerCtl.yuv422en;
    isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_CTL);

    VO_YUV_BUF_S *yuvBuf = &layer3Ctl->yuvBuf;
    Vo_Drv_Core_SetLayer3Buf(isp,yuvBuf);

    U_VO_LAYER3_IMG_IN_BLENTH         blen_udata;
    blen_udata.bits.blen         = layer3Ctl->imgInBlen.blen;
    blen_udata.bits.voffset      = layer3Ctl->imgInBlen.voffset;
    isp_reg_writel(isp,blen_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_IMG_IN_BLENTH);

    VO_LAYER_SIZE_S  *sizeCtl = &layer3Ctl->sizeCtl;
    Vo_Drv_Core_SetLayer3Size(isp,sizeCtl);

    U_VO_LAYER3_ADDR_SEL_MODE         selmode_udata;
    //selmode_udata.bits.addrflag  = layer3Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = layer3Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = layer3Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = layer3Ctl->baseMode.mode;     
    isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER3_ADDR_SEL_MODE);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer3en            = layer3Ctl->layer3DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);

    return 0;
}
/*
*Layer4Osd0
*/
int Vo_Drv_Core_SetLayer4Osd0Area(struct isp_device *isp,VO_AREA_S  *osdArea)
{
    VO_CHECK_POINTER(osdArea);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER4_XCTL                  xctl_udata;
    xctl_udata.u32 = 0;
    xctl_udata.bits.start       = osdArea->xCtl.start;
    xctl_udata.bits.stop        = osdArea->xCtl.stop;
	isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER4_XCTL);

    U_VO_LAYER4_YCTL                  yctl_udata;
    yctl_udata.u32 = 0;
    yctl_udata.bits.start       = osdArea->yCtl.start;
    yctl_udata.bits.stop        = osdArea->yCtl.stop;    
	isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER4_YCTL); 

    return 0;
}

int Vo_Drv_Core_SetLayer4Osd0Buf(struct isp_device *isp,VO_OSD_BUF_S *osdBuf)
{
    VO_CHECK_POINTER(osdBuf);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_OSD0_VLU_ADDR0          vlu0_udata;
    vlu0_udata.u32 = 0;
    vlu0_udata.bits.addr        = osdBuf->vlu_addr0;
	isp_reg_writel(isp,vlu0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD0_VLU_ADDR0);

    U_VO_DISP_OSD0_ALP_ADDR0          alp0_udata;
    alp0_udata.u32 = 0;
    alp0_udata.bits.addr        = osdBuf->alp_addr0;
	isp_reg_writel(isp,alp0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD0_ALP_ADDR0);

    U_VO_DISP_OSD0_VLU_ADDR1          vlu1_udata;
    vlu1_udata.u32 = 0;
    vlu1_udata.bits.addr        = osdBuf->vlu_addr1;
	isp_reg_writel(isp,vlu1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD0_VLU_ADDR1);

    U_VO_DISP_OSD0_ALP_ADDR1          alp1_udata;
    alp1_udata.u32 = 0;
    alp1_udata.bits.addr        = osdBuf->alp_addr1;
	isp_reg_writel(isp,alp1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD0_ALP_ADDR1);

    U_VO_OSD0_STRIDE                  stride_udata;
    stride_udata.u32 = 0;
    stride_udata.bits.alpstride = osdBuf->alpstride;
    stride_udata.bits.osdstride = osdBuf->osdstride;
	isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD0_STRIDE);

    return 0;
}

int Vo_Drv_Core_SetLayer4Osd0(struct isp_device *isp,VO_OSD0_CTL_S *osd0Ctl)
{
    VO_CHECK_POINTER(osd0Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S  *osdArea = &osd0Ctl->osdArea;
    Vo_Drv_Core_SetLayer4Osd0Area(isp,osdArea);

    U_VO_OSD0_INFO                    info_udata;
    info_udata.u32 = 0;
    info_udata.bits.alphatpye   = osd0Ctl->osdCtl.alphatpye;
    info_udata.bits.osdtype     = osd0Ctl->osdCtl.osdtype;
	isp_reg_writel(isp,info_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD0_INFO);

    U_VO_OSD0_SIZE                    size_udata;
    size_udata.u32 = 0;
    size_udata.bits.width       = osd0Ctl->osdSize.width;
    size_udata.bits.height      = osd0Ctl->osdSize.height;
	isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD0_SIZE);

    VO_OSD_BUF_S *osdBuf = &osd0Ctl->osdBuf;
    Vo_Drv_Core_SetLayer4Osd0Buf(isp,osdBuf);

    U_VO_OSD0_DMA_CTL                 dma_udata;
    dma_udata.u32 = 0;
    dma_udata.bits.dmamap       = osd0Ctl->osdDmaCtl.dmamap;
    dma_udata.bits.dmarequestlen= osd0Ctl->osdDmaCtl.dmarequestlen;
    dma_udata.bits.rgbrev       = osd0Ctl->osdDmaCtl.rgbrev;
	isp_reg_writel(isp,dma_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD0_DMA_CTL);

    U_VO_OSD0_ADDR_SEL_MODE           selmode_udata;
    selmode_udata.u32 = 0;
    //selmode_udata.bits.addrflag  = osd0Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = osd0Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = osd0Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = osd0Ctl->baseMode.mode;  
	isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD0_ADDR_SEL_MODE);

    U_VO_OSD_RGB2YUV_CTL              ctl_udata;
    ctl_udata.u32 = 0;
    ctl_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);
    ctl_udata.bits.osd0en        = osd0Ctl->osdrgb2yuvEn;
	isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = 0;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer4en       = osd0Ctl->osdLayer4DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    return 0;
}
/*
*Layer5Osd1
*/
int Vo_Drv_Core_SetLayer5Osd1Area(struct isp_device *isp,VO_AREA_S *osdArea)
{
    VO_CHECK_POINTER(osdArea);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER5_XCTL                  xctl_udata;
    xctl_udata.bits.start       = osdArea->xCtl.start;
    xctl_udata.bits.stop        = osdArea->xCtl.stop;  
	isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER5_XCTL);
   
    U_VO_LAYER5_YCTL                  yctl_udata;
    yctl_udata.bits.start       = osdArea->yCtl.start;
    yctl_udata.bits.stop        = osdArea->yCtl.stop;    
	isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER5_YCTL);

    return 0;
}

int Vo_Drv_Core_SetLayer5Osd1Buf(struct isp_device *isp,VO_OSD_BUF_S *osdBuf)
{
    VO_CHECK_POINTER(osdBuf);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_OSD1_VLU_ADDR0          vlu0_udata;
    vlu0_udata.bits.addr        = osdBuf->vlu_addr0;
	isp_reg_writel(isp,vlu0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD1_VLU_ADDR0);

    U_VO_DISP_OSD1_ALP_ADDR0          alp0_udata;
    alp0_udata.bits.addr        = osdBuf->alp_addr0;
	isp_reg_writel(isp,alp0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD1_ALP_ADDR0);

    U_VO_DISP_OSD1_VLU_ADDR1          vlu1_udata;
    vlu1_udata.bits.addr        = osdBuf->vlu_addr1;
	isp_reg_writel(isp,vlu1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD1_VLU_ADDR1);

    U_VO_DISP_OSD1_ALP_ADDR1          alp1_udata;
    alp1_udata.bits.addr        = osdBuf->alp_addr1;
	isp_reg_writel(isp,alp1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD1_ALP_ADDR1);

    U_VO_OSD1_STRIDE                  stride_udata;
    stride_udata.bits.alpstride = osdBuf->alpstride;
    stride_udata.bits.osdstride = osdBuf->osdstride;    
    isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD1_STRIDE);

    return 0;
}

int Vo_Drv_Core_SetLayer5Osd1(struct isp_device *isp,VO_OSD1_CTL_S *osd1Ctl)
{
    VO_CHECK_POINTER(osd1Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S *osdArea = &osd1Ctl->osdArea;
    Vo_Drv_Core_SetLayer5Osd1Area(isp,osdArea);

    U_VO_OSD1_INFO                    info_udata;
    info_udata.bits.alphatpye   = osd1Ctl->osdCtl.alphatpye;
    info_udata.bits.osdtype     = osd1Ctl->osdCtl.osdtype;    
	isp_reg_writel(isp,info_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD1_INFO);

    U_VO_OSD1_SIZE                    size_udata;
    size_udata.bits.width       = osd1Ctl->osdSize.width;
    size_udata.bits.height      = osd1Ctl->osdSize.height;    
	isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD1_SIZE);

    VO_OSD_BUF_S *osdBuf = &osd1Ctl->osdBuf;
    Vo_Drv_Core_SetLayer5Osd1Buf(isp,osdBuf);

    U_VO_OSD1_DMA_CTL                 dma_udata;
    dma_udata.bits.dmamap       = osd1Ctl->osdDmaCtl.dmamap;
    dma_udata.bits.dmarequestlen= osd1Ctl->osdDmaCtl.dmarequestlen;
    dma_udata.bits.rgbrev       = osd1Ctl->osdDmaCtl.rgbrev;    
	isp_reg_writel(isp,dma_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD1_DMA_CTL);

    U_VO_0SD1_ADDR_SEL_MODE           selmode_udata;
    //selmode_udata.bits.addrflag  = osd1Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = osd1Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = osd1Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = osd1Ctl->baseMode.mode;
	isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD1_ADDR_SEL_MODE); 

    U_VO_OSD_RGB2YUV_CTL              ctl_udata;
    ctl_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);
    ctl_udata.bits.osd1en        = osd1Ctl->osdrgb2yuvEn;
	isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer5en            = osd1Ctl->osdLayer5DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);    
    return 0;
}
/*
*Layer6Osd2
*/
int Vo_Drv_Core_SetLayer6Osd2Area(struct isp_device *isp,VO_AREA_S *osdArea)
{
    VO_CHECK_POINTER(osdArea);
    VO_CHECK_POINTER(isp);

    U_VO_LAYER6_XCTL                  xctl_udata;
    xctl_udata.bits.start       = osdArea->xCtl.start;
    xctl_udata.bits.stop        = osdArea->xCtl.stop;   
	isp_reg_writel(isp,xctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER6_XCTL);  

    U_VO_LAYER6_YCTL                  yctl_udata;
    yctl_udata.bits.start       = osdArea->yCtl.start;
    yctl_udata.bits.stop        = osdArea->yCtl.stop;
	isp_reg_writel(isp,yctl_udata.u32,ISP_IOMEM_VO_CORE,VO_LAYER6_YCTL);
    return 0;
}

int Vo_Drv_Core_SetLayer6Osd2Buf(struct isp_device *isp,VO_OSD_BUF_S *osdBuf)
{
    VO_CHECK_POINTER(osdBuf);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_OSD2_VLU_ADDR0          vlu0_udata;
    vlu0_udata.bits.addr        = osdBuf->vlu_addr0;
	isp_reg_writel(isp,vlu0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD2_VLU_ADDR0);

    U_VO_DISP_OSD2_ALP_ADDR0          alp0_udata;
    alp0_udata.bits.addr        = osdBuf->alp_addr0;
	isp_reg_writel(isp,alp0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD2_ALP_ADDR0); 

    U_VO_DISP_OSD2_VLU_ADDR1          vlu1_udata;
    vlu1_udata.bits.addr        = osdBuf->vlu_addr1;
	isp_reg_writel(isp,vlu1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD2_VLU_ADDR1);   

    U_VO_DISP_OSD2_ALP_ADDR1          alp1_udata;
    alp1_udata.bits.addr        = osdBuf->alp_addr1;
	isp_reg_writel(isp,alp1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_OSD2_ALP_ADDR1);

    U_VO_OSD2_STRIDE                  stride_udata;
    stride_udata.bits.alpstride = osdBuf->alpstride;
    stride_udata.bits.osdstride = osdBuf->osdstride;
	isp_reg_writel(isp,stride_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD2_STRIDE);

    return 0;
}

int Vo_Drv_Core_SetLayer6Osd2(struct isp_device *isp,VO_OSD2_CTL_S *osd2Ctl)
{
    VO_CHECK_POINTER(osd2Ctl);
    VO_CHECK_POINTER(isp);

    VO_AREA_S *osdArea = &osd2Ctl->osdArea;
    Vo_Drv_Core_SetLayer6Osd2Area(isp,osdArea);

    U_VO_OSD2_INFO                    info_udata;
    info_udata.bits.alphatpye   = osd2Ctl->osdCtl.alphatpye;
    info_udata.bits.osdtype     = osd2Ctl->osdCtl.osdtype;
	isp_reg_writel(isp,info_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD2_INFO);

    U_VO_OSD2_SIZE                    size_udata;
    size_udata.bits.width       = osd2Ctl->osdSize.width;
    size_udata.bits.height      = osd2Ctl->osdSize.height;
	isp_reg_writel(isp,size_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD2_SIZE);

    VO_OSD_BUF_S *osdBuf = &osd2Ctl->osdBuf;
    Vo_Drv_Core_SetLayer6Osd2Buf(isp,osdBuf);

    U_VO_OSD2_DMA_CTL                 dma_udata;
    dma_udata.bits.dmamap       = osd2Ctl->osdDmaCtl.dmamap;
    dma_udata.bits.dmarequestlen= osd2Ctl->osdDmaCtl.dmarequestlen;
    dma_udata.bits.rgbrev       = osd2Ctl->osdDmaCtl.rgbrev;
	isp_reg_writel(isp,dma_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD2_DMA_CTL);

    U_VO_OSD2_ADDR_SEL_MODE           selmode_udata;
    //selmode_udata.bits.addrflag  = osd2Ctl->baseMode.addrflag;
    selmode_udata.bits.base0mask = osd2Ctl->baseMode.base0mask;
    selmode_udata.bits.base1mask = osd2Ctl->baseMode.base1mask;
    selmode_udata.bits.mode      = osd2Ctl->baseMode.mode;      
	isp_reg_writel(isp,selmode_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD2_ADDR_SEL_MODE);

    U_VO_OSD_RGB2YUV_CTL              ctl_udata;
    ctl_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);
    ctl_udata.bits.osd2en        = osd2Ctl->osdrgb2yuvEn;
	isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_CTL);

    U_VO_DISP_ENABLE                  en_udata;
    en_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    en_udata.bits.layer6en       = osd2Ctl->osdLayer6DispEn;    
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_ENABLE);
    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetRgb2Yuv(struct isp_device *isp,VO_OSD_RGB2YUV_S *osdRgb2Yuv)
{
    VO_CHECK_POINTER(osdRgb2Yuv);
    VO_CHECK_POINTER(isp);

    U_VO_OSD_RGB2YUV_COEFF00          c00_udata;
    c00_udata.bits.c00          = osdRgb2Yuv->osdrgb2yuv_coeff[0][0];
	isp_reg_writel(isp,c00_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF00);

    U_VO_OSD_RGB2YUV_COEFF01          c01_udata;
    c01_udata.bits.c01          = osdRgb2Yuv->osdrgb2yuv_coeff[0][1];
	isp_reg_writel(isp,c01_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF01);

    U_VO_OSD_RGB2YUV_COEFF02          c02_udata;
    c02_udata.bits.c02          = osdRgb2Yuv->osdrgb2yuv_coeff[0][2];
	isp_reg_writel(isp,c02_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF02);

    U_VO_OSD_RGB2YUV_COEFF03          c03_udata;
    c03_udata.bits.c03          = osdRgb2Yuv->osdrgb2yuv_coeff[0][3];
    isp_reg_writel(isp,c03_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF03);

    U_VO_OSD_RGB2YUV_COEFF10          c10_udata;
    c10_udata.bits.c10          = osdRgb2Yuv->osdrgb2yuv_coeff[1][0];
    isp_reg_writel(isp,c10_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF10);

    U_VO_OSD_RGB2YUV_COEFF11          c11_udata;
    c11_udata.bits.c11          = osdRgb2Yuv->osdrgb2yuv_coeff[1][1];
	isp_reg_writel(isp,c11_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF11);

    U_VO_OSD_RGB2YUV_COEFF12          c12_udata;
    c12_udata.bits.c12          = osdRgb2Yuv->osdrgb2yuv_coeff[1][2];
	isp_reg_writel(isp,c12_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF12);

    U_VO_OSD_RGB2YUV_COEFF13          c13_udata;
    c13_udata.bits.c13          = osdRgb2Yuv->osdrgb2yuv_coeff[1][3];
	isp_reg_writel(isp,c13_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF13);

    U_VO_OSD_RGB2YUV_COEFF20          c20_udata;
    c20_udata.bits.c20          = osdRgb2Yuv->osdrgb2yuv_coeff[2][0];
	isp_reg_writel(isp,c20_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF20);

    U_VO_OSD_RGB2YUV_COEFF21          c21_udata;
    c21_udata.bits.c21          = osdRgb2Yuv->osdrgb2yuv_coeff[2][1];
	isp_reg_writel(isp,c21_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF21);

    U_VO_OSD_RGB2YUV_COEFF22          c22_udata;
    c22_udata.bits.c22          = osdRgb2Yuv->osdrgb2yuv_coeff[2][2];
	isp_reg_writel(isp,c22_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF22);

    U_VO_OSD_RGB2YUV_COEFF23          c23_udata;
    c23_udata.bits.c23          = osdRgb2Yuv->osdrgb2yuv_coeff[2][3];
	isp_reg_writel(isp,c23_udata.u32,ISP_IOMEM_VO_CORE,VO_OSD_RGB2YUV_COEFF23);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetYuv2Rgb(struct isp_device *isp,VO_YUV2RGB_S  *yuv2rgb)
{
    VO_CHECK_POINTER(yuv2rgb);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_YUV2RGB_CTL             ctl_udata;
    ctl_udata.bits.en             = yuv2rgb->yuv2rgb_ctl_en;
    isp_reg_writel(isp,ctl_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_CTL);

    U_VO_DISP_YUV2RGB_COEFF00         c00_udata;
    c00_udata.bits.c00            = yuv2rgb->yuv2rgb_coeff[0][0];
    isp_reg_writel(isp,c00_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF00);

    U_VO_DISP_YUV2RGB_COEFF01         c01_udata;
    c01_udata.bits.c01            = yuv2rgb->yuv2rgb_coeff[0][1];
    isp_reg_writel(isp,c01_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF01);

    U_VO_DISP_YUV2RGB_COEFF02         c02_udata;
    c02_udata.bits.c02            = yuv2rgb->yuv2rgb_coeff[0][2];
    isp_reg_writel(isp,c02_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF02);

    U_VO_DISP_YUV2RGB_COEFF03         c03_udata;
    c03_udata.bits.c03            = yuv2rgb->yuv2rgb_coeff[0][3];
    isp_reg_writel(isp,c03_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF03);

    U_VO_DISP_YUV2RGB_COEFF10         c10_udata;
    c10_udata.bits.c10            = yuv2rgb->yuv2rgb_coeff[1][0];
    isp_reg_writel(isp,c10_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF10);

    U_VO_DISP_YUV2RGB_COEFF11         c11_udata;
    c11_udata.bits.c11            = yuv2rgb->yuv2rgb_coeff[1][1];
    isp_reg_writel(isp,c11_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF11);

    U_VO_DISP_YUV2RGB_COEFF12         c12_udata;
    c12_udata.bits.c12            = yuv2rgb->yuv2rgb_coeff[1][2];
    isp_reg_writel(isp,c12_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF12);

    U_VO_DISP_YUV2RGB_COEFF13         c13_udata;
    c13_udata.bits.c13            = yuv2rgb->yuv2rgb_coeff[1][3];
    isp_reg_writel(isp,c13_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF13);

    U_VO_DISP_YUV2RGB_COEFF20         c20_udata;
    c20_udata.bits.c20            = yuv2rgb->yuv2rgb_coeff[2][0];
    isp_reg_writel(isp,c20_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF20);

    U_VO_DISP_YUV2RGB_COEFF21         c21_udata;
    c21_udata.bits.c21            = yuv2rgb->yuv2rgb_coeff[2][1];
    isp_reg_writel(isp,c21_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF21);

    U_VO_DISP_YUV2RGB_COEFF22         c22_udata;
    c22_udata.bits.c22            = yuv2rgb->yuv2rgb_coeff[2][2];
    isp_reg_writel(isp,c22_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF22);

    U_VO_DISP_YUV2RGB_COEFF23         c23_udata;
    c23_udata.bits.c23            = yuv2rgb->yuv2rgb_coeff[2][3];
    isp_reg_writel(isp,c23_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_YUV2RGB_COEFF23);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetMix(struct isp_device *isp,VO_CORE_ATTR_S *voCoreAttr)
{
    VO_CHECK_POINTER(voCoreAttr);
    VO_CHECK_POINTER(isp);

    VO_DISP_MIX_CTL_S *dispMixCtl = &voCoreAttr->dispMixCtl;
    U_VO_DISP_MIX_EN                  en_udata;
    en_udata.bits.layer0glben       = dispMixCtl->layer0mix.glben;
    en_udata.bits.layer1glben       = dispMixCtl->layer1mix.glben;
    en_udata.bits.layer2glben       = dispMixCtl->layer2mix.glben;
    en_udata.bits.layer3glben       = dispMixCtl->layer3mix.glben;
    en_udata.bits.layer4glben       = dispMixCtl->layer4mix.glben;
    en_udata.bits.layer5glben       = dispMixCtl->layer5mix.glben;
    en_udata.bits.layer6glben       = dispMixCtl->layer6mix.glben;
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_MIX_EN);

    U_VO_DISP_MIX_ALP0                alp0_udata;
    alp0_udata.bits.layer0glbalp    = dispMixCtl->layer0mix.glbalp;
    alp0_udata.bits.layer1glbalp    = dispMixCtl->layer1mix.glbalp;
    alp0_udata.bits.layer2glbalp    = dispMixCtl->layer2mix.glbalp;
    alp0_udata.bits.layer3glbalp    = dispMixCtl->layer3mix.glbalp;
    isp_reg_writel(isp,alp0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_MIX_ALP0);

    U_VO_DISP_MIX_ALP1                alp1_udata;
    alp1_udata.bits.layer4glbalp    = dispMixCtl->layer4mix.glbalp;
    alp1_udata.bits.layer5glbalp    = dispMixCtl->layer5mix.glbalp;
    alp1_udata.bits.layer6glbalp    = dispMixCtl->layer6mix.glbalp;    
    isp_reg_writel(isp,alp1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_MIX_ALP1);

	U_VO_DISP_MIX_SEL                 sel_udata;
    sel_udata.bits.layer0sel        = dispMixCtl->layer0mix.sel;
    sel_udata.bits.layer1sel        = dispMixCtl->layer1mix.sel;
    sel_udata.bits.layer2sel        = dispMixCtl->layer2mix.sel;
    sel_udata.bits.layer3sel        = dispMixCtl->layer3mix.sel;
    sel_udata.bits.layer4sel        = dispMixCtl->layer4mix.sel;
    sel_udata.bits.layer5sel        = dispMixCtl->layer5mix.sel;
    sel_udata.bits.layer6sel        = dispMixCtl->layer6mix.sel;
    isp_reg_writel(isp,sel_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_MIX_SEL);

	U_VO_DISP_BACK_GROUD              backgroud_udata;
    backgroud_udata.bits.y          = dispMixCtl->backGroud.y;
    backgroud_udata.bits.u          = dispMixCtl->backGroud.u;
    backgroud_udata.bits.v          = dispMixCtl->backGroud.v;
    isp_reg_writel(isp,backgroud_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_BACK_GROUD);

	U_VO_DISP_DITH_CTL                dith_udata;
    dith_udata.u32 = 0;
    dith_udata.bits.en              = voCoreAttr->ditherctlen;
    isp_reg_writel(isp,dith_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_DITH_CTL);

	U_VO_DISP_CLUT_CTL                clut_udata;
    clut_udata.u32 = 0;
    clut_udata.bits.en              = voCoreAttr->clutctlen;
    isp_reg_writel(isp,clut_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_CLUT_CTL);

    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetInt(struct isp_device *isp,VO_DISP_IRQ_CTL_S *dispIrqCtl)
{
    VO_CHECK_POINTER(dispIrqCtl);
    VO_CHECK_POINTER(isp);

    U_VO_DISP_IRQ0_CTL                irq0_udata;
    irq0_udata.bits.en              = dispIrqCtl->en0;
	isp_reg_writel(isp,irq0_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_IRQ0_CTL);

    U_VO_DISP_IRQ1_CTL                irq1_udata;
    irq1_udata.bits.en              = dispIrqCtl->en1;
	isp_reg_writel(isp,irq1_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_IRQ1_CTL);

    U_VO_DISP_IRQ2_CTL                irq2_udata;
    irq2_udata.bits.en              = dispIrqCtl->en2;
	isp_reg_writel(isp,irq2_udata.u32,ISP_IOMEM_VO_CORE,VO_DISP_IRQ2_CTL);
    return 0;
}
/*
*
*/
int Vo_Drv_Core_SetWBBuf(struct isp_device *isp,VO_WB_BUF_S *BufCtl)
{
    VO_CHECK_POINTER(BufCtl);
    VO_CHECK_POINTER(isp);

    U_VO_WB_FRM_BASE_OUT_ADDR0_Y      y0_udata;
    y0_udata.u32 = 0;
    y0_udata.bits.addr              = BufCtl->yBufCtl.addr0;
	isp_reg_writel(isp,y0_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_FRM_BASE_OUT_ADDR0_Y);

    U_VO_WB_FRM_BASE_OUT_ADDR0_UV     uv0_udata;
    uv0_udata.u32 = 0;
    uv0_udata.bits.addr             = BufCtl->uvBufCtl.addr0;
	isp_reg_writel(isp,uv0_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_FRM_BASE_OUT_ADDR0_UV);
  
    U_VO_WB_FRM_BASE_OUT_ADDR1_Y      y1_udata;
    y1_udata.u32 = 0;
    y1_udata.bits.addr              = BufCtl->yBufCtl.addr1;
	isp_reg_writel(isp,y1_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_FRM_BASE_OUT_ADDR1_Y);
     
    U_VO_WB_FRM_BASE_OUT_ADDR1_UV     uv1_udata;
    uv1_udata.u32 = 0;
    uv1_udata.bits.addr             = BufCtl->uvBufCtl.addr1;
	isp_reg_writel(isp,uv1_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_FRM_BASE_OUT_ADDR1_UV);

    U_VO_WB_HSTRIDE_Y                 ystride_udata;
    ystride_udata.u32 = 0;
    ystride_udata.bits.out          = BufCtl->yBufCtl.hstride;
	isp_reg_writel(isp,ystride_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_HSTRIDE_Y);
   
    U_VO_WB_HSTRIDE_UV                uvstride_udata;
    uvstride_udata.u32 = 0;
    uvstride_udata.bits.out         = BufCtl->uvBufCtl.hstride;
	isp_reg_writel(isp,uvstride_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_HSTRIDE_UV);

    return 0;
}

int Vo_Drv_Core_SetWBCh0(struct isp_device *isp,VO_WB_CH_CTL_S  *ch0Ctl)
{
    VO_CHECK_POINTER(ch0Ctl);
    VO_CHECK_POINTER(isp);

    U_VO_WB_CH0_DMA_MODE              ch0mode_udata;
    ch0mode_udata.u32 = 0;
    ch0mode_udata.bits.blen         = ch0Ctl->dmaMode.blen;
    ch0mode_udata.bits.continuousmode = ch0Ctl->dmaMode.continuousmode;
    ch0mode_udata.bits.errdetecten         = ch0Ctl->dmaMode.blen;
    ch0mode_udata.bits.otnum        = ch0Ctl->dmaMode.otnum;
    ch0mode_udata.bits.swap         = ch0Ctl->dmaMode.swap;
	isp_reg_writel(isp,ch0mode_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH0_DMA_MODE);
   
    U_VO_WB_CH0_ERR_UNIT              ch0unit_udata;
    ch0unit_udata.u32 = 0;
    ch0unit_udata.bits.unit         = ch0Ctl->err_unit;  
    isp_reg_writel(isp,ch0unit_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH0_ERR_UNIT);

    U_VO_WB_CH0_ERR_TH                ch0th_udata;
    ch0th_udata.u32 = 0;
    ch0th_udata.bits.threshold      = ch0Ctl->err_threshold;
	isp_reg_writel(isp,ch0th_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH0_ERR_TH);
    
    U_VO_WB_CH0_INFO_CLR              ch0clr_udata;
    ch0clr_udata.u32 = 0;
    ch0clr_udata.bits.fifoerrclear  = ch0Ctl->infoClr.fifoerrclear;
    ch0clr_udata.bits.frmcntclear   = ch0Ctl->infoClr.frmcntclear;
    ch0clr_udata.bits.maxbw         = ch0Ctl->infoClr.maxbw;
    ch0clr_udata.bits.totalbw       = ch0Ctl->infoClr.totalbw;
	isp_reg_writel(isp,ch0clr_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH0_INFO_CLR);
    
    U_VO_WB_CH0_RST_REQ               ch0req_udata;
    ch0req_udata.u32 = 0;
    ch0req_udata.bits.request       = ch0Ctl->request;
	isp_reg_writel(isp,ch0req_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH0_RST_REQ);

    return 0;
}

int Vo_Drv_Core_SetWBCh1(struct isp_device *isp,VO_WB_CH_CTL_S *ch1Ctl)
{
    VO_CHECK_POINTER(ch1Ctl);
    VO_CHECK_POINTER(isp);

    U_VO_WB_CH1_DMA_MODE              ch1mode_udata;
    ch1mode_udata.u32 = 0;
    ch1mode_udata.bits.otnum        = ch1Ctl->dmaMode.otnum;
    ch1mode_udata.bits.blen         = ch1Ctl->dmaMode.blen;
    ch1mode_udata.bits.datamode     = ch1Ctl->dmaMode.continuousmode;
    ch1mode_udata.bits.swap         = ch1Ctl->dmaMode.swap;
    ch1mode_udata.bits.errdetecten  = ch1Ctl->dmaMode.errdetecten;   
	isp_reg_writel(isp,ch1mode_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH1_DMA_MODE);
  
    U_VO_WB_CH1_ERR_UNIT              ch1unit_udata;
    ch1unit_udata.u32 = 0;
    ch1unit_udata.bits.unit         = ch1Ctl->err_unit;
	isp_reg_writel(isp,ch1unit_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH1_ERR_UNIT);
     
    U_VO_WB_CH1_ERR_TH                ch1th_udata;
    ch1th_udata.u32 = 0;
    ch1th_udata.bits.threshold      = ch1Ctl->err_threshold;
	isp_reg_writel(isp,ch1th_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH1_ERR_TH);
     
    U_VO_WB_CH1_INFO_CLR              ch1clr_udata;
    ch1clr_udata.u32 = 0;
    ch1clr_udata.bits.fifoerrclear  = ch1Ctl->infoClr.fifoerrclear;
    ch1clr_udata.bits.frmcntclear   = ch1Ctl->infoClr.frmcntclear;
    ch1clr_udata.bits.maxbw         = ch1Ctl->infoClr.maxbw;
    ch1clr_udata.bits.totalbw       = ch1Ctl->infoClr.totalbw;    
	isp_reg_writel(isp,ch1clr_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH1_INFO_CLR);
    
    U_VO_WB_CH1_RST_REQ               ch1req_udata;
    ch1req_udata.u32 = 0;
    ch1req_udata.bits.request       = ch1Ctl->request;
	isp_reg_writel(isp,ch1req_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_CH1_RST_REQ);

    return 0;
}

int Vo_Drv_Core_SetWB(struct isp_device *isp,VO_WB_CTL_S *wbCtl)
{
    VO_CHECK_POINTER(wbCtl);
    VO_CHECK_POINTER(isp);
 
    U_VO_WB_MODE                    mode_udata;
    mode_udata.u32 = 0;
    mode_udata.bits.inchmode        = wbCtl->inchmode;
	isp_reg_writel(isp,mode_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_MODE);

    U_VO_WB_PIXEL_FORMAT_OUT          format_udata;
    format_udata.u32 = 0;
    format_udata.bits.formatsel     = wbCtl->PixelFormatOut.formatsel;
    format_udata.bits.inputformat   = wbCtl->PixelFormatOut.inputformat;
    format_udata.bits.outputformat  = wbCtl->PixelFormatOut.outputformat;
    format_udata.bits.pixelorder422 = wbCtl->PixelFormatOut.pixelorder422;
    format_udata.bits.rgbpixelwidth = wbCtl->PixelFormatOut.rgbpixelwidth;
	isp_reg_writel(isp,format_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_PIXEL_FORMAT_OUT);
        
    VO_WB_BUF_S *BufCtl = &wbCtl->BufCtl;
    Vo_Drv_Core_SetWBBuf(isp,BufCtl);
   
    U_VO_WB_BUF_SIZE_OUT              bufsize_udata;
    bufsize_udata.u32  = 0;
    bufsize_udata.bits.loop         = wbCtl->buffersize;
	isp_reg_writel(isp,bufsize_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_BUF_SIZE_OUT);
      
    U_VO_WB_V_SIZE_ACTIVE_OUT         vsize_udata;
    vsize_udata.u32 = 0;
    vsize_udata.bits.active         = wbCtl->v_size_out;
	isp_reg_writel(isp,vsize_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_V_SIZE_ACTIVE_OUT);
   
    U_VO_WB_H_SIZE_ACTIVE_OUT         hsize_udata;
    hsize_udata.u32 = 0;
    hsize_udata.bits.active         = wbCtl->h_size_out;
	isp_reg_writel(isp,hsize_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_H_SIZE_ACTIVE_OUT); 

    VO_WB_CH_CTL_S *ch0Ctl = &wbCtl->ch0Ctl;
    Vo_Drv_Core_SetWBCh0(isp,ch0Ctl);

    VO_WB_CH_CTL_S *ch1Ctl = &wbCtl->ch1Ctl;
    Vo_Drv_Core_SetWBCh1(isp,ch1Ctl);

    U_VO_WB_DMA_CH_EN               en_udata;
    en_udata.u32 = 0x0;
    en_udata.bits.wben              = wbCtl->wben;
	isp_reg_writel(isp,en_udata.u32,ISP_IOMEM_VO_CORE,VO_WB_DMA_CH_EN);
    
    return 0;
}
