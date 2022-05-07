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
//#include "video/td/td.h"
#include "video/isp_com.h"
#include "video/video_subsystem_addr.h"
#include "video/td/wrap/td_wrap_drv.h"
#include "video/td/wrap/td_wrap_reg.h"

unsigned int  *reg_td_wrap_base;
#define TD_DRV_WRAP_REG_CTX(pstCtx)	pstCtx = (S_TD_WRAP_REGS_TYPE *)(reg_td_wrap_base)
/*
*
*/
int TD_DRV_Wrap_Remap(void)
{
	  reg_td_wrap_base  		   = (unsigned int *)TD_WRAP_BASE; 
    return 0;
}
/*
*
*/
static int TD_DRV_SetWrapRst(TD_WRAP_SWRST_S *swrst)
{
    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

		U_TD_WRAP_SWRST          	    swrst_udata;
    swrst_udata.u32 = 0;
    swrst_udata.bits.mixerrw      = swrst->mixerrw ;//1;
    swrst_udata.bits.rotationrw   = swrst->rotationrw ;//1;
    swrst_udata.bits.axird        = swrst->axird ;//1;
    swrst_udata.bits.axiwr        = swrst->axiwr ;//1;
		TD_WRAP_DRV_SET_SWRst(apstTdWrapReg,  swrst_udata.u32);

    return 0;
}
/*
*
*/
static int TD_DRV_SetWrapClkEn(TD_WRAP_CLK_EN_S *clk_en)
{
    TD_CHECK_POINTER(clk_en);

    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

		U_TD_WRAP_CLK_EN         	    clken_udata;
    clken_udata.u32 = 0;
    clken_udata.bits.axiwr        = clk_en->axiwr;
    clken_udata.bits.axird        = clk_en->axird;        
    clken_udata.bits.ch0rd        = clk_en->ch0rd;
    clken_udata.bits.ch0wr        = clk_en->ch0wr;
    clken_udata.bits.ch1rd        = clk_en->ch1rd;
    clken_udata.bits.ch1wr        = clk_en->ch1wr;
    clken_udata.bits.ch2rd        = clk_en->ch2rd;
    clken_udata.bits.ch2wr        = clk_en->ch2wr;
    clken_udata.bits.ch3rd        = clk_en->ch3rd;
    clken_udata.bits.ch4rd        = clk_en->ch4rd;
    clken_udata.bits.ch5rd        = clk_en->ch5rd;
    TD_WRAP_DRV_SET_ClkEn(apstTdWrapReg,  clken_udata.u32);

    return 0;
}
/*
*
*/
static int TD_DRV_SetWrapDma(TD_WRAP_DMA_CTL_S *dma_ctl)
{
    TD_CHECK_POINTER(dma_ctl);

    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

		U_TD_WRAP_DMA_ARB_MODE   	    arbmode_udata;
    arbmode_udata.u32 =0;
    arbmode_udata.bits.rd         = dma_ctl->arb_mode.rd;
    arbmode_udata.bits.wr         = dma_ctl->arb_mode.wr;
		TD_WRAP_DRV_SET_DmaArbMode(apstTdWrapReg,  arbmode_udata.u32);

		U_TD_WRAP_DMA_WEIGHT_WR0 	    weightwr0_udata;
    weightwr0_udata.u32 = 0;
    weightwr0_udata.bits.ch0      = dma_ctl->weight_wr.ch0;
    weightwr0_udata.bits.ch1      = dma_ctl->weight_wr.ch1;
    weightwr0_udata.bits.ch2      = dma_ctl->weight_wr.ch2;
    weightwr0_udata.bits.ch3      = dma_ctl->weight_wr.ch3;
		TD_WRAP_DRV_SET_DmaWeightWR0(apstTdWrapReg,  weightwr0_udata.u32);

		U_TD_WRAP_DMA_WEIGHT_WR1 	    weightwr1_udata;
    weightwr1_udata.u32 = 0;
    weightwr1_udata.bits.ch4      = dma_ctl->weight_wr.ch4;
    weightwr1_udata.bits.ch5      = dma_ctl->weight_wr.ch5;
    weightwr1_udata.bits.ch6      = dma_ctl->weight_wr.ch6;
    weightwr1_udata.bits.ch7      = dma_ctl->weight_wr.ch7;
		TD_WRAP_DRV_SET_DmaWeightWR1(apstTdWrapReg,  weightwr1_udata.u32);

		U_TD_WRAP_DMA_WEIGHT_RD0 	    weightrd0_udata;
    weightrd0_udata.u32 = 0;
    weightrd0_udata.bits.ch0      = dma_ctl->weight_rd.ch0;
    weightrd0_udata.bits.ch1      = dma_ctl->weight_rd.ch1;
    weightrd0_udata.bits.ch2      = dma_ctl->weight_rd.ch2;
    weightrd0_udata.bits.ch3      = dma_ctl->weight_rd.ch3;
		TD_WRAP_DRV_SET_DmaWeightRD0(apstTdWrapReg,  weightrd0_udata.u32);

		U_TD_WRAP_DMA_WEIGHT_RD1 	    weightrd1_udata;
    weightrd1_udata.u32 = 0;
    weightrd1_udata.bits.ch4      = dma_ctl->weight_rd.ch4;
    weightrd1_udata.bits.ch5      = dma_ctl->weight_rd.ch5;
    weightrd1_udata.bits.ch6      = dma_ctl->weight_rd.ch6;
    weightrd1_udata.bits.ch7      = dma_ctl->weight_rd.ch7;
		TD_WRAP_DRV_SET_DmaWeightRD1(apstTdWrapReg,  weightrd1_udata.u32);

		U_TD_WRAP_DMA_PRIORITY_WR	    priorwr_udata;
    priorwr_udata.u32 = 0;
    priorwr_udata.bits.ch0        = dma_ctl->prior_wr.ch0;
    priorwr_udata.bits.ch1        = dma_ctl->prior_wr.ch1;
    priorwr_udata.bits.ch2        = dma_ctl->prior_wr.ch2;
    priorwr_udata.bits.ch3        = dma_ctl->prior_wr.ch3;
    priorwr_udata.bits.ch4        = dma_ctl->prior_wr.ch4;
    priorwr_udata.bits.ch5        = dma_ctl->prior_wr.ch5;
    priorwr_udata.bits.ch6        = dma_ctl->prior_wr.ch6;
    priorwr_udata.bits.ch7        = dma_ctl->prior_wr.ch7;
		TD_WRAP_DRV_SET_DmaPriorityWr(apstTdWrapReg,  priorwr_udata.u32);

		U_TD_WRAP_DMA_PRIORITY_RD	    priorrd_udata;
    priorrd_udata.u32 = 0;
    priorrd_udata.bits.ch0        = dma_ctl->prior_rd.ch0;
    priorrd_udata.bits.ch1        = dma_ctl->prior_rd.ch1;
    priorrd_udata.bits.ch2        = dma_ctl->prior_rd.ch2;
    priorrd_udata.bits.ch3        = dma_ctl->prior_rd.ch3;
    priorrd_udata.bits.ch4        = dma_ctl->prior_rd.ch4;
    priorrd_udata.bits.ch5        = dma_ctl->prior_rd.ch5;
    priorrd_udata.bits.ch6        = dma_ctl->prior_rd.ch6;
    priorrd_udata.bits.ch7        = dma_ctl->prior_rd.ch7;
		TD_WRAP_DRV_SET_DmaPriorityRd(apstTdWrapReg,  priorrd_udata.u32);

		U_TD_WRAP_DMA_ID_WR      	    idwr_udata;
    idwr_udata.u32 = 0;
    idwr_udata.bits.ch0        		= dma_ctl->id_wr.ch0;
    idwr_udata.bits.ch1        		= dma_ctl->id_wr.ch1;
    idwr_udata.bits.ch2        		= dma_ctl->id_wr.ch2;
    idwr_udata.bits.ch3        		= dma_ctl->id_wr.ch3;
    idwr_udata.bits.ch4        		= dma_ctl->id_wr.ch4;
    idwr_udata.bits.ch5        		= dma_ctl->id_wr.ch5;
    idwr_udata.bits.ch6        		= dma_ctl->id_wr.ch6;
    idwr_udata.bits.ch7        		= dma_ctl->id_wr.ch7;    
		TD_WRAP_DRV_SET_DmaIDWr(apstTdWrapReg,  idwr_udata.u32);

		U_TD_WRAP_DMA_ID_RD      	    idrd_udata;
    idrd_udata.u32 = 0;
    idrd_udata.bits.ch0        		= dma_ctl->id_rd.ch0;
    idrd_udata.bits.ch1        		= dma_ctl->id_rd.ch1;
    idrd_udata.bits.ch2        		= dma_ctl->id_rd.ch2;
    idrd_udata.bits.ch3        		= dma_ctl->id_rd.ch3;
    idrd_udata.bits.ch4        		= dma_ctl->id_rd.ch4;
    idrd_udata.bits.ch5        		= dma_ctl->id_rd.ch5;
    idrd_udata.bits.ch6        		= dma_ctl->id_rd.ch6;
    idrd_udata.bits.ch7        		= dma_ctl->id_rd.ch7; 
		TD_WRAP_DRV_SET_DmaIDRd(apstTdWrapReg,  idrd_udata.u32);

    return 0;
}
/*
*
*/
static int TD_DRV_SetWrapInt(TD_WRAP_INT_MASK_S *int_mask)
{
    TD_CHECK_POINTER(int_mask);

    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

		U_TD_WRAP_INT            	int_udata;
    int_udata.u32 =0;
    int_udata.bits.mixerdone_mask       = int_mask->mixerdone_mask;
    int_udata.bits.rotationdone_mask    = int_mask->rotationdone_mask;
    int_udata.bits.rotationtimeout_mask = int_mask->rotationtimeout_mask;
		TD_WRAP_DRV_SET_Int(apstTdWrapReg,  int_udata.u32);

    return 0;
}
/*
*
*/
int TD_DRV_SetWrapCfgDone(TD_WRAP_CFG_S  *cfg_done)
{
    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

		U_TD_WRAP_CFG            	cfg_udata;
    cfg_udata.u32 = 0;
    cfg_udata.u32  = TD_WRAP_DRV_GET_Cfg(apstTdWrapReg);
    cfg_udata.bits.done           = cfg_done->done;//1; 
		TD_WRAP_DRV_SET_Cfg(apstTdWrapReg,cfg_udata.u32);
    return 0;
}
/*
*wrap
*/
int TD_DRV_SetWrap(TD_WRAP_CTL_S *tdWrapCtl)
{
    TD_CHECK_POINTER(tdWrapCtl);

    TD_WRAP_SWRST_S *swrst = &tdWrapCtl->swrst;
    TD_DRV_SetWrapRst(swrst);

    TD_WRAP_CLK_EN_S *clk_en = &tdWrapCtl->clk_en;
    TD_DRV_SetWrapClkEn(clk_en);

    TD_WRAP_DMA_CTL_S *dma_ctl = &tdWrapCtl->dma_ctl;
    TD_DRV_SetWrapDma(dma_ctl);

    TD_WRAP_INT_MASK_S *int_mask = &tdWrapCtl->int_mask;
    TD_DRV_SetWrapInt(int_mask);

    TD_WRAP_CFG_S  *cfg_done = &tdWrapCtl->cfg_done;
    TD_DRV_SetWrapCfgDone(cfg_done);
    
    return 0;
}
/*
*DEBUG
*/
int TD_DRV_GetWrapRegsVal(void)
{
    S_TD_WRAP_REGS_TYPE *apstTdWrapReg = NULL;
    TD_DRV_WRAP_REG_CTX(apstTdWrapReg);

	TD_WRAP_DRV_GET_WrapRegsVal(apstTdWrapReg);

	return 0;
}
