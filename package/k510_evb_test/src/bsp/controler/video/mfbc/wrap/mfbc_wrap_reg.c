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
//#include "video/mfbc/mfbc.h"
#include "video/isp_com.h"
#include "video/mfbc/wrap/mfbc_wrap_reg.h"

int MFBC_WRAP_DRV_SET_SWRst(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_SW_RST.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_SWRst: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_OutSel(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_OUT_SEL.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_OutSel: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaArbMode(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_ARB_MODE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaWeightWr0(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_WEIGHT_WR0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaWeightWr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaWeightWr1(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_WEIGHT_WR1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaWeightWr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaWeightRd0(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_WEIGHT_RD0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaWeightRd0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaWeightRd1(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_WEIGHT_RD1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaWeightRd1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaPriorityWR(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_PRIORITY_WR.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaPriorityWR: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaPriorityRD(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_PRIORITY_RD.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaPriorityRD: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaIDWR(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_ID_WR.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaIDWR: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_DmaIDRD(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_DMA_ID_RD.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_DmaIDRD: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_CLK_EN(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_CLK_EN.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_CLK_EN: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_SET_CFG(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_CFG.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_CFG: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_WRAP_DRV_GET_CFG(S_MFBC_WRAP_REGS_TYPE *pstRegs)
{
    MFBC_CHECK_POINTER(pstRegs);

    unsigned int uData = 0;
    uData = pstRegs->MFBC_WRAP_CFG.u32;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_CFG: 0x%08x\n", uData);
    #endif
    return uData;
}

int MFBC_WRAP_DRV_SET_INT_MASK(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{

    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_WRAP_INT.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_SET_INT_MASK: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int MFBC_WRAP_DRV_GET_INT_STS(S_MFBC_WRAP_REGS_TYPE *pstRegs)
{
    unsigned int uData = 0;
    MFBC_CHECK_POINTER(pstRegs);

    uData = pstRegs->MFBC_WRAP_INT.u32;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_WRAP_DRV_GET_INT_STS: 0x%08x\n", uData);
    #endif
    return uData;
}
//debug
int MFBC_WRAP_DRV_GET_WrapRegsVal(S_MFBC_WRAP_REGS_TYPE *pstRegs)
{
    MFBC_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if MFBC_WRAP_DEBUG_OPEN
    MFBC_PRINTF_FUNC("read MFBC_WRAP regs start!\n");
    uData = pstRegs->MFBC_WRAP_SW_RST.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_SW_RST: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_OUT_SEL.u32;    
    MFBC_PRINTF_FUNC("MFBC_WRAP_OUT_SEL: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_CLK_EN.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_CLK_EN: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_ARB_MODE.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_ARB_MODE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_WEIGHT_WR0.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_WEIGHT_WR0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_WEIGHT_WR1.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_WEIGHT_WR1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_WEIGHT_RD0.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_WEIGHT_RD0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_WEIGHT_RD1.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_WEIGHT_RD1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_PRIORITY_WR.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_PRIORITY_WR: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_PRIORITY_RD.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_PRIORITY_RD: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_ID_WR.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_ID_WR: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_DMA_ID_RD.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_DMA_ID_RD: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_CFG.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_CFG: 0x%08x\n", uData);

    uData = pstRegs->MFBC_WRAP_INT.u32;
    MFBC_PRINTF_FUNC("MFBC_WRAP_INT: 0x%08x\n", uData);

    MFBC_PRINTF_FUNC("read MFBC_WRAP regs end!\n");
    #endif

    return 0;
}
