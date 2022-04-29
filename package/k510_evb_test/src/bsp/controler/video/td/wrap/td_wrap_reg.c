/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : td_warp_reg_def.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : td driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
//#include "td/inc/td.h"
#include "video/isp_com.h"
#include "video/td/wrap/td_wrap_reg.h"

int TD_WRAP_DRV_SET_SWRst(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_SWRST.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_SWRst: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_ClkEn(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_CLK_EN.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_ClkEn: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaArbMode(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_ARB_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaWeightWR0(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_WEIGHT_WR0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaWeightWR0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaWeightWR1(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_WEIGHT_WR1.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaWeightWR1: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaWeightRD0(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_WEIGHT_RD0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaWeightRD0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaWeightRD1(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_WEIGHT_RD1.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaWeightRD1: 0x%08x\n", uData);
    #endif
    return 0;
}


int TD_WRAP_DRV_SET_DmaPriorityWr(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_PRIORITY_WR.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaPriorityWr: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaPriorityRd(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_PRIORITY_RD.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaPriorityRd: 0x%08x\n", uData);
    #endif
    return 0;
}


int TD_WRAP_DRV_SET_DmaIDWr(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_ID_WR.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaIDWr: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_DmaIDRd(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_DMA_ID_RD.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_DmaIDRd: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_WRAP_DRV_SET_Cfg(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_CFG.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int TD_WRAP_DRV_GET_Cfg(S_TD_WRAP_REGS_TYPE *pstRegs)
{
    TD_CHECK_POINTER(pstRegs);

    unsigned int uData = 0;
    uData = pstRegs->TD_WRAP_CFG.u32 ;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_Cfg: 0x%08x\n", uData);
    #endif
    return uData;
}

int TD_WRAP_DRV_SET_Int(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WRAP_INT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_WRAP_DRV_SET_Int: 0x%08x\n", uData);
    #endif
    return 0;
}
//debug
int TD_WRAP_DRV_GET_WrapRegsVal(S_TD_WRAP_REGS_TYPE *pstRegs)
{
    TD_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if TD_WRAP_DEBUG_OPEN
    TD_PRINTF_FUNC("read TD_WRAP regs start!\n"); 

    uData = pstRegs->TD_WRAP_SWRST.u32;
    TD_PRINTF_FUNC("TD_WRAP_SWRST: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_CLK_EN.u32;
    TD_PRINTF_FUNC("TD_WRAP_CLK_EN: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_ARB_MODE.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_ARB_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_WEIGHT_WR0.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_WEIGHT_WR0: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_WEIGHT_WR1.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_WEIGHT_WR1: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_WEIGHT_RD0.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_WEIGHT_RD0: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_WEIGHT_RD1.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_WEIGHT_RD1: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_PRIORITY_WR.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_PRIORITY_WR: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_PRIORITY_RD.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_PRIORITY_RD: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_ID_WR.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_ID_WR: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_DMA_ID_RD.u32;
    TD_PRINTF_FUNC("TD_WRAP_DMA_ID_RD: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_CFG.u32;
    TD_PRINTF_FUNC("TD_WRAP_CFG: 0x%08x\n", uData);

    uData = pstRegs->TD_WRAP_INT.u32;
    TD_PRINTF_FUNC("TD_WRAP_INT: 0x%08x\n", uData);

    TD_PRINTF_FUNC("read TD_WRAP regs end!\n");
    #endif
    return 0;
}
