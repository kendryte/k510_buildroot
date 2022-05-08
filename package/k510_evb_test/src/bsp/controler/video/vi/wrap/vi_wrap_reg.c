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
#include "video/vi/wrap/vi_wrap_reg.h"
//#include "video/vi/vi.h"
#include "video/isp_com.h"

int VI_WRAP_DRV_SET_WrapSwrstCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);
    pstRegs->VI_WRAP_SWRST_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapSwrstCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VI_WRAP_DRV_GET_WrapSwrstCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_SWRST_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_SWRST_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapSwrstCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int VI_WRAP_DRV_SET_WrapCsiModeCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_CSI_MODE_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapCsiModeCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapCsiModeCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_CSI_MODE_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_CSI_MODE_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapCsiModeCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapIspChSel(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_ISP_CH_SEL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapIspChSel: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapIspChSel(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_ISP_CH_SEL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_ISP_CH_SEL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapIspChSel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapClockCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_CLOCK_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapClockCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapClockCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_CLOCK_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_CLOCK_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapClockCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaArbMode(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_ARB_MODE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaArbMode(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_ARB_MODE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_ARB_MODE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaArbMode: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaWrWeight0(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_WR_WEIGHT_0.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaWrWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaWrWeight0(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_WR_WEIGHT_0 stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_WR_WEIGHT_0.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaWrWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaWrWeight1(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_WR_WEIGHT_1.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaWrWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaWrWeight1(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_WR_WEIGHT_1 stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_WR_WEIGHT_1.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaWrWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaRdWeight0(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_RD_WEIGHT_0.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaRdWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaRdWeight0(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_RD_WEIGHT_0 stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_RD_WEIGHT_0.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaRdWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaRdWeight1(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_RD_WEIGHT_1.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaRdWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaRdWeight1(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_RD_WEIGHT_1 stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_RD_WEIGHT_1.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaRdWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaWrPriority(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_WR_PRIORITY.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaWrPriority: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaWrPriority(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_WR_PRIORITY stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_WR_PRIORITY.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaWrPriority: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaRdPriority(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_RD_PRIORITY.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaRdPriority: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaRdPriority(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_RD_PRIORITY stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_RD_PRIORITY.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaRdPriority: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaWrChId(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_WR_CH_ID.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaWrChId: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaWrChId(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_WR_CH_ID stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_WR_CH_ID.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaWrChId: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaRdChId(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_RD_CH_ID.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaRdChId: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaRdChId(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_RD_CH_ID stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_RD_CH_ID.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaRdChId: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapDmaAxiCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_DMA_AXI_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapDmaAxiCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapDmaAxiCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_DMA_AXI_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_DMA_AXI_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapDmaAxiCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WrapConfigCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WRAP_CONFIG_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WrapConfigCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WrapConfigCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WRAP_CONFIG_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WRAP_CONFIG_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WrapConfigCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_WRAP_DRV_SET_WarpIntCtl(S_VI_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_WARP_INT_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_WarpIntCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_WRAP_DRV_GET_WarpIntCtl(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    U_VI_WARP_INT_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_WARP_INT_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_WarpIntCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*debug
*/
int VI_WRAP_DRV_GETWrapRegsVal(S_VI_WRAP_REGS_TYPE *pstRegs)
{
    VI_CHECK_POINTER(pstRegs);

    #if VI_WRAP_DEBUG_OPEN

    for(int i =0;i<0x80;i=i+4)  //0x49c
    {
    	printf("VI WRAP REG:Reg[0x%x]= 0x%x\n", VI_WRAP_REG_BASE+i, *(volatile unsigned int *)(VI_WRAP_REG_BASE+i));
    }
	#endif

	#if 0
    unsigned int stData;
    VI_PRINTF_FUNC("read VI_WRAP regs start!\n");    
  

    //
    stData = pstRegs->VI_WRAP_SWRST_CTL.u32;
    VI_PRINTF_FUNC("VI_WRAP_SWRST_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_CSI_MODE_CTL.u32;
    VI_PRINTF_FUNC("VI_WRAP_CSI_MODE_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_ISP_CH_SEL.u32;
    VI_PRINTF_FUNC("VI_WRAP_ISP_CH_SEL: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_CLOCK_CTL.u32;
    VI_PRINTF_FUNC("VI_WRAP_CLOCK_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_ARB_MODE.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_ARB_MODE: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_WR_WEIGHT_0.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_WR_WEIGHT_0: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_WR_WEIGHT_1.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_WR_WEIGHT_1: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_RD_WEIGHT_0.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_RD_WEIGHT_0: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_RD_WEIGHT_1.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_RD_WEIGHT_1: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_WR_PRIORITY.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_WR_PRIORITY: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_RD_PRIORITY.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_RD_PRIORITY: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_WR_CH_ID.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_WR_CH_ID: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_RD_CH_ID.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_RD_CH_ID: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_DMA_AXI_CTL.u32;
    VI_PRINTF_FUNC("VI_WRAP_DMA_AXI_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_WRAP_CONFIG_CTL.u32;
    VI_PRINTF_FUNC("VI_WRAP_CONFIG_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_WARP_INT_CTL.u32;
    VI_PRINTF_FUNC("VI_WARP_INT_CTL: 0x%08x\n", stData);

    VI_PRINTF_FUNC("read VI_WRAP regs end!\n");  
    #endif

    return 0;
}    

