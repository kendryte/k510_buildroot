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
