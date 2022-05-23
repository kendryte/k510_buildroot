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

#include "video/isp_com.h"
#include "video/video_subsystem_addr.h"
//#include "video/mfbc/mfbc.h"
#include "video/mfbc/wrap/mfbc_wrap_drv.h"
#include "video/mfbc/wrap/mfbc_wrap_reg.h"

unsigned int  *reg_mfbc_wrap_base;
#define MFBC_DRV_WRAP_REG_CTX(pstCtx)		pstCtx = (S_MFBC_WRAP_REGS_TYPE *)(reg_mfbc_wrap_base)
/*
*
*/
int MFBC_DRV_Wrap_Remap(void)
{
	reg_mfbc_wrap_base  		  = (unsigned int *)MFBC_WRAP_BASE;

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetWrapDma(MFBC_WRAP_DMA_S *pstDma)
{
    MFBC_CHECK_POINTER(pstDma);

    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_DMA_ARB_MODE   	arbmode_udata;
    arbmode_udata.u32 = 0;
    arbmode_udata.bits.wr_arb_mode = pstDma->arb_mode.arbmode_wr;
    arbmode_udata.bits.rd_arb_mode = pstDma->arb_mode.arbmode_rd;
 		MFBC_WRAP_DRV_SET_DmaArbMode(apstMfbcWrapReg,arbmode_udata.u32);

    U_MFBC_WRAP_DMA_WEIGHT_WR0 	weight_wr0_udata;
    weight_wr0_udata.u32 = 0;
    weight_wr0_udata.bits.ch0 = pstDma->weight_wr.weight_wr_ch0;
    weight_wr0_udata.bits.ch1 = pstDma->weight_wr.weight_wr_ch1;
    weight_wr0_udata.bits.ch2 = pstDma->weight_wr.weight_wr_ch2;
    weight_wr0_udata.bits.ch3 = pstDma->weight_wr.weight_wr_ch3;
		MFBC_WRAP_DRV_SET_DmaWeightWr0(apstMfbcWrapReg,weight_wr0_udata.u32);

    U_MFBC_WRAP_DMA_WEIGHT_WR1 	weight_wr1_udata;
    weight_wr1_udata.u32 = 0;
    weight_wr1_udata.bits.ch4 = pstDma->weight_wr.weight_wr_ch4;
    weight_wr1_udata.bits.ch5 = pstDma->weight_wr.weight_wr_ch5;
    weight_wr1_udata.bits.ch6 = pstDma->weight_wr.weight_wr_ch6;
    weight_wr1_udata.bits.ch7 = pstDma->weight_wr.weight_wr_ch7;
		MFBC_WRAP_DRV_SET_DmaWeightWr1(apstMfbcWrapReg,weight_wr1_udata.u32);

    U_MFBC_WRAP_DMA_WEIGHT_RD0 	weight_rd0_udata;
    weight_rd0_udata.u32 = 0;
    weight_rd0_udata.bits.ch0 = pstDma->weight_rd.weight_rd_ch0; 
    weight_rd0_udata.bits.ch1 = pstDma->weight_rd.weight_rd_ch1;
    weight_rd0_udata.bits.ch2 = pstDma->weight_rd.weight_rd_ch2;
    weight_rd0_udata.bits.ch3 = pstDma->weight_rd.weight_rd_ch3;
		MFBC_WRAP_DRV_SET_DmaWeightRd0(apstMfbcWrapReg,weight_rd0_udata.u32);

    U_MFBC_WRAP_DMA_WEIGHT_RD1 	weight_rd1_udata;
    weight_rd1_udata.u32 = 0;
    weight_rd1_udata.bits.ch4 = pstDma->weight_rd.weight_rd_ch4; 
    weight_rd1_udata.bits.ch5 = pstDma->weight_rd.weight_rd_ch5;
    weight_rd1_udata.bits.ch6 = pstDma->weight_rd.weight_rd_ch6;
    weight_rd1_udata.bits.ch7 = pstDma->weight_rd.weight_rd_ch7;
		MFBC_WRAP_DRV_SET_DmaWeightRd1(apstMfbcWrapReg,weight_rd1_udata.u32);

    U_MFBC_WRAP_DMA_PRIORITY_WR	prior_wr_udata;
    prior_wr_udata.u32 = 0;
    prior_wr_udata.bits.ch0 = pstDma->prior_wr.wr_ch0;
    prior_wr_udata.bits.ch1 = pstDma->prior_wr.wr_ch1;
    prior_wr_udata.bits.ch2 = pstDma->prior_wr.wr_ch2;
    prior_wr_udata.bits.ch3 = pstDma->prior_wr.wr_ch3;
    prior_wr_udata.bits.ch4 = pstDma->prior_wr.wr_ch4;
    prior_wr_udata.bits.ch5 = pstDma->prior_wr.wr_ch5;
    prior_wr_udata.bits.ch6 = pstDma->prior_wr.wr_ch6;
    prior_wr_udata.bits.ch7 = pstDma->prior_wr.wr_ch7;
		MFBC_WRAP_DRV_SET_DmaPriorityWR(apstMfbcWrapReg,prior_wr_udata.u32);

    U_MFBC_WRAP_DMA_PRIORITY_RD	prior_rd_udata;
    prior_rd_udata.u32 = 0;
    prior_rd_udata.bits.ch0 = pstDma->prior_rd.rd_ch0;
    prior_rd_udata.bits.ch1 = pstDma->prior_rd.rd_ch1;
    prior_rd_udata.bits.ch2 = pstDma->prior_rd.rd_ch2;
    prior_rd_udata.bits.ch3 = pstDma->prior_rd.rd_ch3;
    prior_rd_udata.bits.ch4 = pstDma->prior_rd.rd_ch4;
    prior_rd_udata.bits.ch5 = pstDma->prior_rd.rd_ch5;
    prior_rd_udata.bits.ch6 = pstDma->prior_rd.rd_ch6;
    prior_rd_udata.bits.ch7 = pstDma->prior_rd.rd_ch7;
		MFBC_WRAP_DRV_SET_DmaPriorityRD(apstMfbcWrapReg,prior_rd_udata.u32);

    U_MFBC_WRAP_DMA_ID_WR      id_wr_udata;
    id_wr_udata.u32 = 0;
    id_wr_udata.bits.ch0 = pstDma->wr_id.wr_ch0;
    id_wr_udata.bits.ch1 = pstDma->wr_id.wr_ch1;
    id_wr_udata.bits.ch2 = pstDma->wr_id.wr_ch2;
    id_wr_udata.bits.ch3 = pstDma->wr_id.wr_ch3;
    id_wr_udata.bits.ch4 = pstDma->wr_id.wr_ch4;
    id_wr_udata.bits.ch5 = pstDma->wr_id.wr_ch5;
    id_wr_udata.bits.ch6 = pstDma->wr_id.wr_ch6;
    id_wr_udata.bits.ch7 = pstDma->wr_id.wr_ch7;
		MFBC_WRAP_DRV_SET_DmaIDWR(apstMfbcWrapReg,id_wr_udata.u32);

    U_MFBC_WRAP_DMA_ID_RD      	id_rd_udata;
    id_rd_udata.u32 = 0;
    id_rd_udata.bits.ch0 = pstDma->rd_id.rd_ch0;
    id_rd_udata.bits.ch1 = pstDma->rd_id.rd_ch1;
    id_rd_udata.bits.ch2 = pstDma->rd_id.rd_ch2;
    id_rd_udata.bits.ch3 = pstDma->rd_id.rd_ch3;
    id_rd_udata.bits.ch4 = pstDma->rd_id.rd_ch4;
    id_rd_udata.bits.ch5 = pstDma->rd_id.rd_ch5;
    id_rd_udata.bits.ch6 = pstDma->rd_id.rd_ch6;
    id_rd_udata.bits.ch7 = pstDma->rd_id.rd_ch7;
		MFBC_WRAP_DRV_SET_DmaIDRD(apstMfbcWrapReg,id_rd_udata.u32);

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetRst(MFBC_WRAP_RST_S *pstRst)
{
    MFBC_CHECK_POINTER(pstRst);

    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_SW_RST 	rst_udata;
    rst_udata.u32 = 0;
    rst_udata.bits.ch0ywr = pstRst->ch0ywr;
    rst_udata.bits.ch1uvwr = pstRst->ch1uvwr;
    rst_udata.bits.ch2headwr = pstRst->ch2headwr;
    rst_udata.bits.axiwr   =  pstRst->axiwr;
    rst_udata.bits.axird   =  pstRst->axird;
    rst_udata.u32 = 0xffff;
		MFBC_WRAP_DRV_SET_SWRst(apstMfbcWrapReg,rst_udata.u32);

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetClkEn(MFBC_WRAP_CLK_EN_S *pstClkEn)
{
    MFBC_CHECK_POINTER(pstClkEn);

    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_CLK_EN 	clk_en_udata;
    clk_en_udata.u32 = 0;
    clk_en_udata.bits.ch0ywr = pstClkEn->ch0ywr;
    clk_en_udata.bits.ch1uvwr = pstClkEn->ch1uvwr;
    clk_en_udata.bits.ch2headwr = pstClkEn->ch2headwr;
    clk_en_udata.bits.axiwr = pstClkEn->axiwr;
    clk_en_udata.bits.axird = pstClkEn->axird;
    clk_en_udata.u32 =0xffffffff;
    MFBC_WRAP_DRV_CLK_EN(apstMfbcWrapReg,clk_en_udata.u32);

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetChlSel(unsigned int mfbc_chl_sel)
{
    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_OUT_SEL	sel_udata;
    sel_udata.u32 = 0;
    sel_udata.bits.mfbc_chl_sel = mfbc_chl_sel;
		MFBC_WRAP_DRV_SET_OutSel(apstMfbcWrapReg,sel_udata.u32);

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetIntMask(MFBC_WRAP_INT_MASK_S *pstIntMsk)
{
    MFBC_CHECK_POINTER(pstIntMsk);

    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_INT    	int_udata;
    int_udata.u32 = 0;
    int_udata.bits.ydonemask = pstIntMsk->ydonemask;
    int_udata.bits.uvdonemask = pstIntMsk->uvdonemask;
    int_udata.bits.headdonemask = pstIntMsk->headdonemask;
		MFBC_WRAP_DRV_SET_INT_MASK(apstMfbcWrapReg,int_udata.u32); 

    return 0;
}
/*
*
*/
int MFBC_DRV_SetCfgDone(MFBC_WRAP_CFG_DONE_S *pstCfgdDone)
{  
    MFBC_CHECK_POINTER(pstCfgdDone);

    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_CFG    	cfg_udata;
    cfg_udata.u32 = 0;
    cfg_udata.bits.done = pstCfgdDone->done;
    cfg_udata.bits.int_irq_pol =pstCfgdDone->int_irq_pol;
    cfg_udata.bits.wp_clr =pstCfgdDone->wp_clr;
		MFBC_WRAP_DRV_SET_CFG(apstMfbcWrapReg,cfg_udata.u32);

    return 0;
}

#if 0
int MFBC_DRV_SetCfgDone(void)
{  
    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);

    U_MFBC_WRAP_CFG    	cfg_udata;
    cfg_udata.u32 = MFBC_WRAP_DRV_GET_CFG(apstMfbcWrapReg);
    cfg_udata.bits.done = 1;
	MFBC_WRAP_DRV_SET_CFG(apstMfbcWrapReg,cfg_udata.u32);

    return 0;
}
#endif
/*
*
*/
int MFBC_DRV_SetWrap(MFBC_WRAP_ATTR_S *pstWrapAttr)
{    
    MFBC_CHECK_POINTER(pstWrapAttr);

    MFBC_WRAP_RST_S *pstRst = &pstWrapAttr->stSwRst;
    MFBC_DRV_SetRst(pstRst);

    MFBC_WRAP_DMA_S *pstDma = &pstWrapAttr->stDma;
    MFBC_DRV_SetWrapDma(pstDma);

    MFBC_WRAP_CLK_EN_S *pstClkEn = &pstWrapAttr->stClkEn;
    MFBC_DRV_SetClkEn(pstClkEn);

    unsigned int mfbc_chl_sel = pstWrapAttr->mfbc_chl_sel;
    MFBC_DRV_SetChlSel(mfbc_chl_sel);

    MFBC_WRAP_INT_MASK_S *pstIntMsk = &pstWrapAttr->stIntMsk;
    MFBC_DRV_SetIntMask(pstIntMsk);

    MFBC_WRAP_CFG_DONE_S *pstCfgdDone = &pstWrapAttr->stCfgdDone;
    MFBC_DRV_SetCfgDone(pstCfgdDone);
   
    return 0;
}
/*
*DEBUG
*/
int MFBC_DRV_GetWrapRegsVal(void)
{
    S_MFBC_WRAP_REGS_TYPE *apstMfbcWrapReg = NULL;
    MFBC_DRV_WRAP_REG_CTX(apstMfbcWrapReg);
    printf("zhudalei:MFBC WRAP ADDR =0x%p\n",apstMfbcWrapReg);
	  MFBC_WRAP_DRV_GET_WrapRegsVal(apstMfbcWrapReg);

	  return 0;
}
