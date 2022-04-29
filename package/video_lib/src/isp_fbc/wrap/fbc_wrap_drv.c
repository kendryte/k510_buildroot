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
 * fbc_wrap_drv.c
 *
 * CANAAN ISP - isp mfbc wrap module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "isp_fbc/isp_fbc.h"
#include "isp_fbc/wrap/fbc_wrap_drv.h"
#include "isp_fbc/wrap/fbc_wrap_reg.h"

/*
*dma
*/
int Fbc_Drv_Wrap_SetDma(struct isp_device *isp,FBC_WRAP_DMA_S *pstDma)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstDma);

    U_FBC_WRAP_DMA_ARB_MODE   	arbmode_udata;
    arbmode_udata.bits.wr_arb_mode = pstDma->arb_mode.arbmode_wr;
    arbmode_udata.bits.rd_arb_mode = pstDma->arb_mode.arbmode_rd;
		isp_reg_writel(isp,arbmode_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_ARB_MODE);

    U_FBC_WRAP_DMA_WEIGHT_WR0 	weight_wr0_udata;
    weight_wr0_udata.bits.ch0 = pstDma->weight_wr.weight_wr_ch0;
    weight_wr0_udata.bits.ch1 = pstDma->weight_wr.weight_wr_ch1;
    weight_wr0_udata.bits.ch2 = pstDma->weight_wr.weight_wr_ch2;
    weight_wr0_udata.bits.ch3 = pstDma->weight_wr.weight_wr_ch3;
		isp_reg_writel(isp,weight_wr0_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_WEIGHT_WR0);

    U_FBC_WRAP_DMA_WEIGHT_WR1 	weight_wr1_udata;
    weight_wr1_udata.bits.ch4 = pstDma->weight_wr.weight_wr_ch4;
    weight_wr1_udata.bits.ch5 = pstDma->weight_wr.weight_wr_ch5;
    weight_wr1_udata.bits.ch6 = pstDma->weight_wr.weight_wr_ch6;
    weight_wr1_udata.bits.ch7 = pstDma->weight_wr.weight_wr_ch7;
		isp_reg_writel(isp,weight_wr1_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_WEIGHT_WR1);

    U_FBC_WRAP_DMA_WEIGHT_RD0 	weight_rd0_udata;
    weight_rd0_udata.bits.ch0 = pstDma->weight_rd.weight_rd_ch0; 
    weight_rd0_udata.bits.ch1 = pstDma->weight_rd.weight_rd_ch1;
    weight_rd0_udata.bits.ch2 = pstDma->weight_rd.weight_rd_ch2;
    weight_rd0_udata.bits.ch3 = pstDma->weight_rd.weight_rd_ch3;  
		isp_reg_writel(isp,weight_rd0_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_WEIGHT_RD0);

    U_FBC_WRAP_DMA_WEIGHT_RD1 	weight_rd1_udata;
    weight_rd1_udata.bits.ch4 = pstDma->weight_rd.weight_rd_ch4; 
    weight_rd1_udata.bits.ch5 = pstDma->weight_rd.weight_rd_ch5;
    weight_rd1_udata.bits.ch6 = pstDma->weight_rd.weight_rd_ch6;
    weight_rd1_udata.bits.ch7 = pstDma->weight_rd.weight_rd_ch7;
		isp_reg_writel(isp,weight_rd1_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_WEIGHT_RD1);

    U_FBC_WRAP_DMA_PRIORITY_WR	prior_wr_udata;
    prior_wr_udata.bits.ch0 = pstDma->prior_wr.wr_ch0;
    prior_wr_udata.bits.ch1 = pstDma->prior_wr.wr_ch1;
    prior_wr_udata.bits.ch2 = pstDma->prior_wr.wr_ch2;
    prior_wr_udata.bits.ch3 = pstDma->prior_wr.wr_ch3;
    prior_wr_udata.bits.ch4 = pstDma->prior_wr.wr_ch4;
    prior_wr_udata.bits.ch5 = pstDma->prior_wr.wr_ch5;
    prior_wr_udata.bits.ch6 = pstDma->prior_wr.wr_ch6;
    prior_wr_udata.bits.ch7 = pstDma->prior_wr.wr_ch7;
		isp_reg_writel(isp,prior_wr_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_PRIORITY_WR);

    U_FBC_WRAP_DMA_PRIORITY_RD	prior_rd_udata;
    prior_rd_udata.bits.ch0 = pstDma->prior_rd.rd_ch0;
    prior_rd_udata.bits.ch1 = pstDma->prior_rd.rd_ch1;
    prior_rd_udata.bits.ch2 = pstDma->prior_rd.rd_ch2;
    prior_rd_udata.bits.ch3 = pstDma->prior_rd.rd_ch3;
    prior_rd_udata.bits.ch4 = pstDma->prior_rd.rd_ch4;
    prior_rd_udata.bits.ch5 = pstDma->prior_rd.rd_ch5;
    prior_rd_udata.bits.ch6 = pstDma->prior_rd.rd_ch6;
    prior_rd_udata.bits.ch7 = pstDma->prior_rd.rd_ch7;
		isp_reg_writel(isp,prior_rd_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_PRIORITY_RD);

    U_FBC_WRAP_DMA_ID_WR      id_wr_udata;
    id_wr_udata.bits.ch0 = pstDma->wr_id.wr_ch0;
    id_wr_udata.bits.ch1 = pstDma->wr_id.wr_ch1;
    id_wr_udata.bits.ch2 = pstDma->wr_id.wr_ch2;
    id_wr_udata.bits.ch3 = pstDma->wr_id.wr_ch3;
    id_wr_udata.bits.ch4 = pstDma->wr_id.wr_ch4;
    id_wr_udata.bits.ch5 = pstDma->wr_id.wr_ch5;
    id_wr_udata.bits.ch6 = pstDma->wr_id.wr_ch6;
    id_wr_udata.bits.ch7 = pstDma->wr_id.wr_ch7;
		isp_reg_writel(isp,id_wr_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_ID_WR);

    U_FBC_WRAP_DMA_ID_RD      	id_rd_udata;
    id_rd_udata.bits.ch0 = pstDma->rd_id.rd_ch0;
    id_rd_udata.bits.ch1 = pstDma->rd_id.rd_ch1;
    id_rd_udata.bits.ch2 = pstDma->rd_id.rd_ch2;
    id_rd_udata.bits.ch3 = pstDma->rd_id.rd_ch3;
    id_rd_udata.bits.ch4 = pstDma->rd_id.rd_ch4;
    id_rd_udata.bits.ch5 = pstDma->rd_id.rd_ch5;
    id_rd_udata.bits.ch6 = pstDma->rd_id.rd_ch6;
    id_rd_udata.bits.ch7 = pstDma->rd_id.rd_ch7;
		isp_reg_writel(isp,id_rd_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_DMA_ID_RD);

    return 0;
}
/*
*reset
*/
int Fbc_Drv_Wrap_SetRst(struct isp_device *isp,FBC_WRAP_RST_S *pstRst)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstRst);

    U_FBC_WRAP_SW_RST 	rst_udata;
    rst_udata.bits.ch0ywr = pstRst->ch0ywr;
    rst_udata.bits.ch1uvwr = pstRst->ch1uvwr;
    rst_udata.bits.ch2headwr = pstRst->ch2headwr;
    rst_udata.bits.axiwr   =  pstRst->axiwr;
    rst_udata.bits.axird   =  pstRst->axird;
		isp_reg_writel(isp,rst_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_SW_RST);

    return 0;
}
/*
*clk
*/
int Fbc_Drv_Wrap_SetClkEn(struct isp_device *isp,FBC_WRAP_CLK_EN_S *pstClkEn)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstClkEn);

    U_FBC_WRAP_CLK_EN 	clk_en_udata;
    clk_en_udata.bits.ch0ywr = pstClkEn->ch0ywr;
    clk_en_udata.bits.ch1uvwr = pstClkEn->ch1uvwr;
    clk_en_udata.bits.ch2headwr = pstClkEn->ch2headwr;
    clk_en_udata.bits.axiwr = pstClkEn->axiwr;
    clk_en_udata.bits.axird = pstClkEn->axird;
    isp_reg_writel(isp,clk_en_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_CLK_EN);

    return 0;
}
/*
*
*/
int Fbc_Drv_Wrap_SetChlSel(struct isp_device *isp,unsigned int fbc_chl_sel)
{
    ISP_CHECK_POINTER(isp);

    U_FBC_WRAP_OUT_SEL	sel_udata;
    sel_udata.bits.fbc_chl_sel = fbc_chl_sel;
		isp_reg_writel(isp,sel_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_OUT_SEL);

    return 0;
}
/*
*int mask
*/
int Fbc_Drv_Wrap_SetIntMask(struct isp_device *isp,FBC_WRAP_INT_MASK_S *pstIntMsk)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstIntMsk);

    U_FBC_WRAP_INT    	int_udata;
    int_udata.bits.ydonemask = pstIntMsk->ydonemask;
    int_udata.bits.uvdonemask = pstIntMsk->uvdonemask;
    int_udata.bits.headdonemask = pstIntMsk->headdonemask;
		isp_reg_writel(isp,int_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_INT); 

    return 0;
}
/*
*
*/
int Fbc_Drv_Wrap_SetCfgDone(struct isp_device *isp,FBC_WRAP_CFG_DONE_S *pstCfgdDone)
{  
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstCfgdDone);

    U_FBC_WRAP_CFG    	cfg_udata;
    cfg_udata.bits.done = pstCfgdDone->done;
    cfg_udata.bits.int_irq_pol =pstCfgdDone->int_irq_pol;
    cfg_udata.bits.wp_clr =pstCfgdDone->wp_clr;
		isp_reg_writel(isp,cfg_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_CFG);

    return 0;
}

/*
int Fbc_Drv_Wrap_SetCfgDone(struct isp_device *isp)
{  
    ISP_CHECK_POINTER(isp);

    U_FBC_WRAP_CFG    	cfg_udata;
    cfg_udata.u32 = isp_reg_readl(isp,ISP_IOMEM_FBC_WRAP,FBC_WRAP_CFG);
    cfg_udata.bits.done = 1;
	  
    isp_reg_writel(isp,cfg_udata.u32,ISP_IOMEM_FBC_WRAP,FBC_WRAP_CFG);

    return 0;
}
*/
/*
*
*/
/*
int Fbc_Drv_Wrap_SetWrap(struct isp_mfbc_device *isp_mfbc,FBC_WRAP_ATTR_S *pstWrapAttr)
{    
    ISP_CHECK_POINTER(isp_mfbc);
    ISP_CHECK_POINTER(pstWrapAttr);

    struct isp_device *isp = to_isp_device(isp_mfbc);

    FBC_WRAP_RST_S *pstRst = &pstWrapAttr->stSwRst;
    Fbc_Drv_Wrap_SetRst(pstRst);

    FBC_WRAP_DMA_S *pstDma = &pstWrapAttr->stDma;
    Fbc_Drv_Wrap_SetWrapDma(pstDma);

    FBC_WRAP_CLK_EN_S *pstClkEn = &pstWrapAttr->stClkEn;
    Fbc_Drv_Wrap_SetClkEn(pstClkEn);

    unsigned int mfbc_chl_sel = pstWrapAttr->mfbc_chl_sel;
    Fbc_Drv_Wrap_SetChlSel(mfbc_chl_sel);

    FBC_WRAP_INT_MASK_S *pstIntMsk = &pstWrapAttr->stIntMsk;
    Fbc_Drv_Wrap_SetIntMask(pstIntMsk);

    FBC_WRAP_CFG_DONE_S *pstCfgdDone = &pstWrapAttr->stCfgdDone;
    Fbc_Drv_Wrap_SetCfgDone(pstCfgdDone);
   
    return 0;
}
*/

