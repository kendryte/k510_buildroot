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
#include "video/isp/wrap/isp_wrap_reg.h"
//#include "video/isp/isp.h"
/*
* reset 
*/
int ISP_WRAP_DRV_SET_WrapSwrstCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_SWRST_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapSwrstCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapSwrstCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_SWRST_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_SWRST_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapSwrstCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaSwrstCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_SWRST_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaSwrstCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaSwrstCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_SWRST_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_SWRST_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaSwrstCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* ctl mode 
*/
int ISP_WRAP_DRV_SET_WrapModeCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_CTL_MODE.u32 = uData; //0x700004;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_WRAP_DRV_SET_WrapModeCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapModeCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_CTL_MODE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_CTL_MODE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_WRAP_DRV_GET_WrapModeCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*clock ctrl
*/
int ISP_WRAP_DRV_SET_WrapPipeClkCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_PIPE_CLK_CTL.u32 = uData;//0xff7f3fff;//uData;//0xff7f3fff;////0x3fff;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapPipeClkCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapPipeClkCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_PIPE_CLK_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_PIPE_CLK_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapPipeClkCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*DMA enable
*/
int ISP_WRAP_DRV_SET_WrapDmaEnCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_EN_CTL.u32 = uData;//0xff7f00f0;//0xff7f00f9;//uData;//0xff7f00f9;//
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaEnCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_WRAP_DRV_GET_WrapDmaEnCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_EN_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_EN_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaEnCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*3dnr&wdr pixel format
*/
int ISP_WRAP_DRV_SET_Wrap3DnrWdrFormatCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_3DNR_WDR_FORMAT_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Wrap3DnrWdrFormatCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_Wrap3DnrWdrFormatCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_3DNR_WDR_FORMAT_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_3DNR_WDR_FORMAT_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Wrap3DnrWdrFormatCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*DS pixel format
*/
int ISP_WRAP_DRV_SET_WrapPixelFormatCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_PIXEL_FORMAT_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapPixelFormatCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapPixelFormatCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_PIXEL_FORMAT_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_PIXEL_FORMAT_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapPixelFormatCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*DS out size
*/
int ISP_WRAP_DRV_SET_WrapMainOutSize(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_OUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainOutSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainOutSize(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_OUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_OUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainOutSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs0OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_OUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0OutSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_OUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_OUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0OutSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs1OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_OUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1OutSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_OUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_OUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1OutSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_OUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2OutSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2OutSize(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_OUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_OUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2OutSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapBufSizeMask0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_BUF_SIZE_MASK0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapBufSizeMask0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapBufSizeMask0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_BUF_SIZE_MASK0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_BUF_SIZE_MASK0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapBufSizeMask0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapBufSizeMask1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_BUF_SIZE_MASK1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapBufSizeMask1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapBufSizeMask1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_BUF_SIZE_MASK1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_BUF_SIZE_MASK1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapBufSizeMask1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapBufSizeMask2(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_BUF_SIZE_MASK2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapBufSizeMask2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapBufSizeMask2(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_BUF_SIZE_MASK2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_BUF_SIZE_MASK2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapBufSizeMask2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*DMA ctrl
*/
int ISP_WRAP_DRV_SET_WrapDmaArbMode(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_ARB_MODE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaArbMode(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_ARB_MODE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_ARB_MODE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaArbMode: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrWeight0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_WEIGHT_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrWeight0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_WEIGHT_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrWeight1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_WEIGHT_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrWeight1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_WEIGHT_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdWeight0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_WEIGHT_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdWeight0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_WEIGHT_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdWeight1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_WEIGHT_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdWeight1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_WEIGHT_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrPriority0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_PRIORITY_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrPriority0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrPriority0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_PRIORITY_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_PRIORITY_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrPriority0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdPriority0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_PRIORITY_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdPriority0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdPriority0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_PRIORITY_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_PRIORITY_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdPriority0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_DmaWrChId0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DMA_WR_CH_ID_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DmaWrChId0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_DmaWrChId0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_DMA_WR_CH_ID_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DMA_WR_CH_ID_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DmaWrChId0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_DmaRdChId0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DMA_RD_CH_ID_0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DmaRdChId0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_DmaRdChId0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_DMA_RD_CH_ID_0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DMA_RD_CH_ID_0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DmaRdChId0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrWeight2(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_WEIGHT_2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrWeight2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrWeight2(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_WEIGHT_2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrWeight2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrWeight3(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_WEIGHT_3.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrWeight3: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrWeight3(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_WEIGHT_3 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_3.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrWeight3: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdWeight2(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_WEIGHT_2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdWeight2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdWeight2(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_WEIGHT_2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdWeight2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdWeight3(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_WEIGHT_3.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdWeight3: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdWeight3(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_WEIGHT_3 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_3.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdWeight3: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrPriority1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_PRIORITY_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrPriority1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrPriority1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_PRIORITY_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_PRIORITY_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrPriority1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdPriority1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_PRIORITY_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdPriority1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdPriority1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_PRIORITY_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_PRIORITY_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdPriority1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_DmaWrChId1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DMA_WR_CH_ID_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DmaWrChId1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_DmaWrChId1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_DMA_WR_CH_ID_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DMA_WR_CH_ID_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DmaWrChId1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_DmaRdChId1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DMA_RD_CH_ID_1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DmaRdChId1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_DmaRdChId1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_DMA_RD_CH_ID_1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DMA_RD_CH_ID_1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DmaRdChId1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*WDR/NR3D/LDC buffer
*/
int ISP_WRAP_DRV_SET_WrapWdrLongBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_WDR_LONG_BUF_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapWdrLongBufBase: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapWdrLongBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_WDR_LONG_BUF_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_WDR_LONG_BUF_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapWdrLongBufBase: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapWdrLongSizeCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_WDR_LONG_SIZE_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapWdrLongSizeCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapWdrLongSizeCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_WDR_LONG_SIZE_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_WDR_LONG_SIZE_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapWdrLongSizeCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_Wrap3DnrYBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_3DNR_Y_BUF_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Wrap3DnrYBufBase: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_Wrap3DnrYBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_3DNR_Y_BUF_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_3DNR_Y_BUF_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Wrap3DnrYBufBase: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_Wrap3DnrUvBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_3DNR_UV_BUF_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Wrap3DnrUvBufBase: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_Wrap3DnrUvBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_3DNR_UV_BUF_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_3DNR_UV_BUF_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Wrap3DnrUvBufBase: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_Wrap3DnrStride(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_3DNR_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Wrap3DnrStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_Wrap3DnrStride(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_3DNR_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_3DNR_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Wrap3DnrStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapLdcYBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_LDC_Y_BUF_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapLdcYBufBase: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapLdcYBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_LDC_Y_BUF_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_LDC_Y_BUF_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapLdcYBufBase: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapLdcUvBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_LDC_UV_BUF_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapLdcUvBufBase: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapLdcUvBufBase(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_LDC_UV_BUF_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_LDC_UV_BUF_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapLdcUvBufBase: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapLdcStride(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_LDC_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapLdcStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapLdcStride(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_LDC_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_LDC_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapLdcStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*main out buffer
*/
int ISP_WRAP_DRV_SET_WrapMainYBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_Y_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainYBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainYBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_Y_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_Y_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainYBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapMainYBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_Y_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainYBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainYBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_Y_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_Y_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainYBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapMainUvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_UV_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainUvBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainUvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_UV_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_UV_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainUvBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapMainUvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_UV_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainUvBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainUvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_UV_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_UV_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainUvBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapMainStride(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_MAIN_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapMainStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapMainStride(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_MAIN_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_MAIN_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapMainStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Downsize CH0 BUFF Control
*/
int ISP_WRAP_DRV_SET_WrapDs0YBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_Y_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0YBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0YBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_Y_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_Y_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0YBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs0YBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_Y_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0YBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0YBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_Y_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_Y_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0YBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs0UvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_UV_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0UvBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0UvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_UV_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_UV_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0UvBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs0UvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_UV_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0UvBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0UvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_UV_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_UV_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0UvBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs0Stride(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS0_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs0Stride(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS0_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS0_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs0Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Downsize CH1 BUFF Control
*/
int ISP_WRAP_DRV_SET_WrapDs1YBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_Y_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1YBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1YBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_Y_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_Y_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1YBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs1YBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_Y_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1YBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1YBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_Y_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_Y_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1YBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs1UvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_UV_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1UvBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1UvBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_UV_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_UV_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1UvBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs1UvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_UV_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1UvBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1UvBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_UV_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_UV_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1UvBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs1Stride(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS1_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs1Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs1Stride(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS1_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS1_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs1Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Downsize CH2 BUFF Control
*/
int ISP_WRAP_DRV_SET_WrapDs2RBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_R_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2RBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2RBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_R_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_R_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2RBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2RBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_R_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2RBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2RBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_R_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_R_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2RBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2GBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_G_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2GBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2GBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_G_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_G_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2GBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2GBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_G_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2GBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2GBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_G_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_G_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2GBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2BBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_B_BUF0_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2BBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2BBuf0Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_B_BUF0_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_B_BUF0_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2BBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2BBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_B_BUF1_BASE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2BBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2BBuf1Base(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_B_BUF1_BASE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_B_BUF1_BASE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2BBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2Stride0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_STRIDE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2Stride0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2Stride0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_STRIDE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_STRIDE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2Stride0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDs2Stride1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DS2_STRIDE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDs2Stride1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDs2Stride1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DS2_STRIDE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DS2_STRIDE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDs2Stride1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*DMA ch0-15 Control 
*/
int ISP_WRAP_DRV_SET_WrapDmaCh0Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH0_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh0Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh0Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH0_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH0_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh0Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh1Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH1_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh1Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh1Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH1_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH1_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh1Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh2Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH2_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh2Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh2Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH2_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH2_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh2Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh3Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH3_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh3Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh3Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH3_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH3_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh3Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh4Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH4_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh4Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh4Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH4_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH4_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh4Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh5Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH5_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh5Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh5Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH5_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH5_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh5Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh6Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH6_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh6Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh6Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH6_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH6_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh6Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh7Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH7_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh7Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh7Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH7_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH7_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh7Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh8Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH8_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh8Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh8Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH8_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH8_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh8Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh9Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH9_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh9Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh9Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH9_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH9_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh9Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh10Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH10_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh10Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh10Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH10_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH10_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh10Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh11Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH11_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh11Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh11Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH11_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH11_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh11Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh12Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH12_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh12Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh12Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH12_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH12_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh12Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh13Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH13_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh13Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh13Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH13_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH13_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh13Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh14Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH14_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh14Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh14Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH14_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH14_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh14Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh15Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH15_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh15Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh15Cfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH15_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH15_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh15Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh0ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH0_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh0ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh0ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH0_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH0_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh0ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh1ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH1_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh1ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh1ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH1_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH1_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh1ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh2ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH2_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh2ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh2ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH2_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH2_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh2ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh3ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH3_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh3ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh3ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH3_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH3_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh3ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh4ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH4_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh4ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh4ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH4_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH4_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh4ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh5ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH5_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh5ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh5ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH5_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH5_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh5ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh6ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH6_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh6ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh6ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH6_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH6_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh6ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh7ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH7_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh7ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh7ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH7_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH7_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh7ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh8ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH8_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh8ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh8ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH8_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH8_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh8ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh9ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH9_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh9ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh9ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH9_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH9_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh9ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh10ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH10_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh10ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh10ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH10_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH10_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh10ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh11ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH11_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh11ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh11ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH11_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH11_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh11ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh12ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH12_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh12ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh12ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH12_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH12_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh12ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh13ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH13_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh13ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh13ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH13_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH13_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh13ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh14ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH14_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh14ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh14ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH14_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH14_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh14ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh15ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH15_ERR_DEC_CFG.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh15ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh15ErrDecCfg(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH15_ERR_DEC_CFG stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH15_ERR_DEC_CFG.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh15ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh0ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH0_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh0ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh0ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH0_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH0_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh0ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh1ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH1_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh1ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh1ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH1_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH1_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh1ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh2ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH2_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh2ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh2ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH2_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH2_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh2ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh3ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH3_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh3ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh3ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH3_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH3_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh3ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh4ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH4_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh4ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh4ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH4_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH4_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh4ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh5ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH5_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh5ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh5ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH5_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH5_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh5ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh6ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH6_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh6ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh6ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH6_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH6_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh6ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh7ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH7_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh7ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh7ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH7_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH7_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh7ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh8ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH8_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh8ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh8ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH8_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH8_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh8ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh9ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH9_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh9ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh9ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH9_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH9_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh9ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh10ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH10_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh10ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh10ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH10_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH10_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh10ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh11ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH11_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh11ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh11ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH11_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH11_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh11ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh12ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH12_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh12ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh12ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH12_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH12_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh12ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh13ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH13_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh13ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh13ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH13_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH13_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh13ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh14ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH14_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh14ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh14ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH14_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH14_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh14ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaCh15ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_CH15_ERR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaCh15ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaCh15ErrStatus(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_CH15_ERR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_CH15_ERR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaCh15ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Ctrl Config 
*/
int ISP_WRAP_DRV_SET_WrapConfigDone(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_CONFIG_DONE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapConfigDone: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapConfigDone(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_CONFIG_DONE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_CONFIG_DONE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapConfigDone: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* isp_core Intr
*/
int ISP_WRAP_DRV_SET_WrapCoreIntCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_CORE_INT_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapCoreIntCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapCoreIntCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_CORE_INT_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_CORE_INT_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapCoreIntCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* dma_ch0-7W Intr 
*/
int ISP_WRAP_DRV_SET_WrapDmaWrIntStatus0(S_ISP_WRAP_REGS_TYPE *pstRegs,unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_INT_STATUS0.u32 = uData;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_WRAP_DRV_SET_WrapDmaWrIntStatus0: 0x%08x\n",uData);
    #endif
    return 0;
}

int ISP_WRAP_DRV_GET_WrapDmaWrIntStatus0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_INT_STATUS0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_INT_STATUS0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrIntStatus0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrIntMask0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_INT_MASK0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrIntMask0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrIntMask0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_INT_MASK0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_INT_MASK0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrIntMask0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* dma_ch8-15W Intr 
*/
int ISP_WRAP_DRV_SET_WrapDmaWrIntStatus1(S_ISP_WRAP_REGS_TYPE *pstRegs,unsigned int udata)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_INT_STATUS1.u32 = udata;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_WRAP_DRV_SET_WrapDmaWrIntStatus1: 0x%08x\n",udata);
    #endif
    return 0;
}

int ISP_WRAP_DRV_GET_WrapDmaWrIntStatus1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_INT_STATUS1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_INT_STATUS1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrIntStatus1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaWrIntMask1(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_WR_INT_MASK1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaWrIntMask1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaWrIntMask1(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_WR_INT_MASK1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_WR_INT_MASK1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaWrIntMask1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* dma_ch0-7RIntr 
*/
int ISP_WRAP_DRV_SET_WrapDmaRdIntStatus0(S_ISP_WRAP_REGS_TYPE *pstRegs,unsigned int udata)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_INT_STATUS0.u32 = udata;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_WRAP_DRV_SET_WrapDmaRdIntStatus0: 0x%08x\n",udata);
    #endif
    return 0;
}

int ISP_WRAP_DRV_GET_WrapDmaRdIntStatus0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_INT_STATUS0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_INT_STATUS0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdIntStatus0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_WRAP_DRV_SET_WrapDmaRdIntMask0(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_DMA_RD_INT_MASK0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapDmaRdIntMask0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapDmaRdIntMask0(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_DMA_RD_INT_MASK0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_DMA_RD_INT_MASK0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapDmaRdIntMask0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* AXI status 
*/
int ISP_WRAP_DRV_SET_WrapAxiCtl(S_ISP_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_WRAP_AXI_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_WrapAxiCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_WRAP_DRV_GET_WrapAxiCtl(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_WRAP_AXI_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_WRAP_AXI_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_WrapAxiCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* version 
*/
int ISP_WRAP_DRV_GET_Version(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_VERSION stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_VERSION.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Version: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* release window 
*/
int ISP_WRAP_DRV_GET_ReleaseInfo(S_ISP_WRAP_REGS_TYPE *pstRegs)
{
    U_ISP_RELEASE_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_RELEASE_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_ReleaseInfo: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

//debug
int ISP_WRAP_DRV_GET_WrapRegsVal(S_ISP_WRAP_REGS_TYPE *pstRegs)
{

    ISP_CHECK_POINTER(pstRegs);

    #if ISP_WRAP_DEBUG_OPEN
    for(int i =0;i<0x3C8;i=i+4)  //0x49c
    {
    	printf("ISP WRAP REG:Reg[0x%x]= 0x%x\n", pstRegs+i, *(volatile unsigned int *)(pstRegs+i));
    }
	#endif
	#if 0
    unsigned int stData;
    //
    ISP_PRINTF_FUNC("read ISP_WRAP regs start!\n"); 
    //
    stData = pstRegs->ISP_WRAP_SWRST_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_SWRST_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_SWRST_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_SWRST_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_CTL_MODE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_CTL_MODE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_PIPE_CLK_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_PIPE_CLK_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_EN_CTL.u32;    
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_EN_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_3DNR_WDR_FORMAT_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_3DNR_WDR_FORMAT_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_PIXEL_FORMAT_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_PIXEL_FORMAT_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_OUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_OUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_OUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_OUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_OUT_SIZE.u32;    
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_OUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_OUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_OUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_BUF_SIZE_MASK0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_BUF_SIZE_MASK0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_BUF_SIZE_MASK1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_BUF_SIZE_MASK1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_BUF_SIZE_MASK2.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_BUF_SIZE_MASK2: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_ARB_MODE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_ARB_MODE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_WEIGHT_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_WEIGHT_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_WEIGHT_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_WEIGHT_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_PRIORITY_0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_PRIORITY_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_PRIORITY_0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_PRIORITY_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DMA_WR_CH_ID_0.u32;
    ISP_PRINTF_FUNC("ISP_DMA_WR_CH_ID_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DMA_RD_CH_ID_0.u32;
    ISP_PRINTF_FUNC("ISP_DMA_RD_CH_ID_0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_2.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_WEIGHT_2: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_WEIGHT_3.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_WEIGHT_3: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_2.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_WEIGHT_2: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_WEIGHT_3.u32;    
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_WEIGHT_3: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_PRIORITY_1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_PRIORITY_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_PRIORITY_1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_PRIORITY_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DMA_WR_CH_ID_1.u32;
    ISP_PRINTF_FUNC("ISP_DMA_WR_CH_ID_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DMA_RD_CH_ID_1.u32;
    ISP_PRINTF_FUNC("ISP_DMA_RD_CH_ID_1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_WDR_LONG_BUF_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_WDR_LONG_BUF_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_WDR_LONG_SIZE_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_WDR_LONG_SIZE_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_3DNR_Y_BUF_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_3DNR_Y_BUF_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_3DNR_UV_BUF_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_3DNR_UV_BUF_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_3DNR_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_3DNR_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_LDC_Y_BUF_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_LDC_Y_BUF_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_LDC_UV_BUF_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_LDC_UV_BUF_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_LDC_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_LDC_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_Y_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_Y_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_Y_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_Y_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_UV_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_UV_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_UV_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_UV_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_MAIN_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_MAIN_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_Y_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_Y_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_Y_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_Y_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_UV_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_UV_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_UV_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_UV_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS0_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS0_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_Y_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_Y_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_Y_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_Y_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_UV_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_UV_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_UV_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_UV_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS1_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS1_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_R_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_R_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_R_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_R_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_G_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_G_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_G_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_G_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_B_BUF0_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_B_BUF0_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_B_BUF1_BASE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_B_BUF1_BASE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_STRIDE0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_STRIDE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DS2_STRIDE1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DS2_STRIDE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH0_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH0_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH1_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH1_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH2_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH2_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH3_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH3_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH4_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH4_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH5_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH5_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH6_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH6_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH7_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH7_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH8_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH8_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH9_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH9_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH10_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH10_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH11_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH11_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH12_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH12_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH13_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH13_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH14_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH14_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH15_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH15_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH0_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH0_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH1_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH1_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH2_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH2_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH3_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH3_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH4_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH4_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH5_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH5_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH6_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH6_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH7_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH7_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH8_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH8_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH9_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH9_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH10_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH10_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH11_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH11_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH12_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH12_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH13_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH13_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH14_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH14_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH15_ERR_DEC_CFG.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH15_ERR_DEC_CFG: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH0_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH0_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH1_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH1_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH2_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH2_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH3_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH3_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH4_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH4_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH5_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH5_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH6_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH6_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH7_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH7_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH8_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH8_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH9_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH9_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH10_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH10_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH11_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH11_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH12_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH12_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH13_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH13_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH14_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH14_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_CH15_ERR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_CH15_ERR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_CONFIG_DONE.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_CONFIG_DONE: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_CORE_INT_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_CORE_INT_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_INT_STATUS0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_INT_STATUS0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_INT_MASK0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_INT_MASK0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_INT_STATUS1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_INT_STATUS1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_WR_INT_MASK1.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_WR_INT_MASK1: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_INT_STATUS0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_INT_STATUS0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_DMA_RD_INT_MASK0.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_DMA_RD_INT_MASK0: 0x%08x\n", stData);

    stData = pstRegs->ISP_WRAP_AXI_CTL.u32;
    ISP_PRINTF_FUNC("ISP_WRAP_AXI_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_VERSION.u32;
    ISP_PRINTF_FUNC("ISP_VERSION: 0x%08x\n", stData);

    stData = pstRegs->ISP_RELEASE_INFO.u32;
    ISP_PRINTF_FUNC("ISP_RELEASE_INFO: 0x%08x\n", stData);
    //
    ISP_PRINTF_FUNC("read ISP_WRAP regs end!\n");

    #endif
    return 0;
}
