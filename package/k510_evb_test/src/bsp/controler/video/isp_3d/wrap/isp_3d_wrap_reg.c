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
//#include "video/isp_3d/isp_3d.h"
#include "video/isp_com.h"
#include "video/isp_3d/wrap/isp_3d_wrap_reg.h"

int TOF_WRAP_DRV_SET_WrapCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_SWRST.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCtlSwrst: 0x%08x\n", uData);
    #endif
    return 0;
}

int TOF_WRAP_DRV_GET_WrapCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_SWRST stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_SWRST.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCtlSwrst: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CTL_SWRST.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCtlSwrst: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCtlSwrst(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CTL_SWRST stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CTL_SWRST.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCtlSwrst: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_WRAP_DRV_SET_WrapCtlMode(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_MODE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCtlMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapCtlMode(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_MODE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_MODE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCtlMode: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapCtlClkEn(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_CLK_EN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCtlClkEn: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapCtlClkEn(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_CLK_EN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_CLK_EN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCtlClkEn: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapCtlDmaEn(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_DMA_EN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCtlDmaEn: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapCtlDmaEn(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_DMA_EN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_DMA_EN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCtlDmaEn: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_WRAP_DRV_SET_WrapCtlPixelFormatISP(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_WRAP_DRV_SET_WrapCtlPixelFormatISP: 0x%08x\n", uData);
    #endif
    return 0;
}

int TOF_WRAP_DRV_GET_WrapCtlPixelFormatISP(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_PIXEL_FORMAT stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT_ISP.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_WRAP_DRV_SET_WrapCtlPixelFormatISP: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapCtlPixelFormat(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCtlPixelFormat: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapCtlPixelFormat(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_CTL_PIXEL_FORMAT stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCtlPixelFormat: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapOutSize(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_OUT_SIZE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapOutSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapOutSize(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_OUT_SIZE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_OUT_SIZE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapOutSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaArbMode(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_ARB_MODE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaArbMode(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_ARB_MODE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_ARB_MODE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaArbMode: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaWrWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_WR_WEIGHT_0.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaWrWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaWrWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_WR_WEIGHT_0 stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_WR_WEIGHT_0.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaWrWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaWrWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_WR_WEIGHT_1.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaWrWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaWrWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_WR_WEIGHT_1 stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_WR_WEIGHT_1.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaWrWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaRdWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_RD_WEIGHT_0.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaRdWeight0: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaRdWeight0(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_RD_WEIGHT_0 stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_RD_WEIGHT_0.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaRdWeight0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaRdWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_RD_WEIGHT_1.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaRdWeight1: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaRdWeight1(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_RD_WEIGHT_1 stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_RD_WEIGHT_1.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaRdWeight1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaWrPriority(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_WR_PRIORITY.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaWrPriority: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaWrPriority(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_WR_PRIORITY stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_WR_PRIORITY.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaWrPriority: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaRdPriority(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_RD_PRIORITY.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaRdPriority: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaRdPriority(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_RD_PRIORITY stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_RD_PRIORITY.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaRdPriority: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_DmaWrChId(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_DMA_WR_CH_ID.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_DmaWrChId: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_DmaWrChId(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_DMA_WR_CH_ID stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_DMA_WR_CH_ID.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_DmaWrChId: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_DmaRdChId(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_DMA_RD_CH_ID.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_DmaRdChId: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_DmaRdChId(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_DMA_RD_CH_ID stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_DMA_RD_CH_ID.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_DmaRdChId: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDepthBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DEPTH_BUF0_BASE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDepthBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDepthBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DEPTH_BUF0_BASE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DEPTH_BUF0_BASE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDepthBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDepthBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DEPTH_BUF1_BASE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDepthBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDepthBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DEPTH_BUF1_BASE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DEPTH_BUF1_BASE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDepthBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapGrayBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_GRAY_BUF0_BASE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapGrayBuf0Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapGrayBuf0Base(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_GRAY_BUF0_BASE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_GRAY_BUF0_BASE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapGrayBuf0Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapGrayBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_GRAY_BUF1_BASE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapGrayBuf1Base: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapGrayBuf1Base(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_GRAY_BUF1_BASE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_GRAY_BUF1_BASE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapGrayBuf1Base: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapBufStride(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_BUF_STRIDE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapBufStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapBufStride(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_BUF_STRIDE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_BUF_STRIDE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapBufStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh0Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH0_CFG.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh0Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh0Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH0_CFG stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH0_CFG.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh0Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh1Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH1_CFG.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh1Cfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh1Cfg(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH1_CFG stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH1_CFG.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh1Cfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh0ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH0_ERR_DEC_CFG.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh0ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh0ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH0_ERR_DEC_CFG stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH0_ERR_DEC_CFG.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh0ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh1ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH1_ERR_DEC_CFG.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh1ErrDecCfg: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh1ErrDecCfg(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH1_ERR_DEC_CFG stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH1_ERR_DEC_CFG.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh1ErrDecCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh0ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH0_ERR_STATUS.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh0ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh0ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH0_ERR_STATUS stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH0_ERR_STATUS.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh0ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapDmaCh1ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_DMA_CH1_ERR_STATUS.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapDmaCh1ErrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapDmaCh1ErrStatus(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_DMA_CH1_ERR_STATUS stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_DMA_CH1_ERR_STATUS.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapDmaCh1ErrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapAxiCtl(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_AXI_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapAxiCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapAxiCtl(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_AXI_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_AXI_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapAxiCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapCofigDone(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_COFIG_DONE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapCofigDone: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapCofigDone(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_COFIG_DONE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_COFIG_DONE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapCofigDone: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_WRAP_DRV_SET_WrapIntCtl(S_TOF_WRAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_WRAP_INT_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_SET_WrapIntCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_WRAP_DRV_GET_WrapIntCtl(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_WRAP_INT_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_WRAP_INT_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_WrapIntCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_WRAP_DRV_GET_Version(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_VERSION stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_VERSION.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_Version: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_WRAP_DRV_GET_ReleaseInfo(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    U_TOF_RELEASE_INFO stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_RELEASE_INFO.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRV_GET_ReleaseInfo: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//debug
int TOF_WRAP_DRV_GET_WrapRegsVal(S_TOF_WRAP_REGS_TYPE *pstRegs)
{
    TOF_CHECK_POINTER(pstRegs);
    unsigned int uData;
    unsigned int *addr;
    //
    #if TOF_WRAP_DEBUG_OPEN

    for(int i =0;i<0x388;i=i+4)  //0x49c
    {
    	printf("ISP 3D WRAP REG:Reg[0x%x]= 0x%x\n", TOF_WRAP_REG_BASE+i, *(volatile unsigned int *)(TOF_WRAP_REG_BASE+i));
    }
	#endif
	#if 0
    TOF_PRINTF_FUNC("read TOF_WRAP regs start!\n");

    uData = pstRegs->TOF_WRAP_CTL_SWRST.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_SWRST: 0x%p:0x%08x\n",&pstRegs->TOF_WRAP_CTL_SWRST,uData);

    uData = pstRegs->TOF_WRAP_DMA_CTL_SWRST.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CTL_SWRST: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_CTL_MODE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_SWRST: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_CTL_CLK_EN.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_CLK_EN: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_CTL_DMA_EN.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_DMA_EN: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT_ISP.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_PIXEL_FORMAT_ISP: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_CTL_PIXEL_FORMAT.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_CTL_PIXEL_FORMAT: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_OUT_SIZE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_OUT_SIZE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_ARB_MODE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_ARB_MODE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_WR_WEIGHT_0.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_WR_WEIGHT_0: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_WR_WEIGHT_1.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_WR_WEIGHT_1: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_RD_WEIGHT_0.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_RD_WEIGHT_0: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_RD_WEIGHT_1.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_RD_WEIGHT_1: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_WR_PRIORITY.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_WR_PRIORITY: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_RD_PRIORITY.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_RD_PRIORITY: 0x%08x\n",uData);

    uData = pstRegs->TOF_DMA_WR_CH_ID.u32;
    TOF_PRINTF_FUNC("TOF_DMA_WR_CH_ID: 0x%08x\n",uData);

    uData = pstRegs->TOF_DMA_RD_CH_ID.u32;
    TOF_PRINTF_FUNC("TOF_DMA_RD_CH_ID: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DEPTH_BUF0_BASE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DEPTH_BUF0_BASE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DEPTH_BUF1_BASE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DEPTH_BUF1_BASE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_GRAY_BUF0_BASE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_GRAY_BUF0_BASE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_GRAY_BUF1_BASE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_GRAY_BUF1_BASE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_BUF_STRIDE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_BUF_STRIDE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH0_CFG.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH0_CFG: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH1_CFG.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH1_CFG: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH0_ERR_DEC_CFG.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH0_ERR_DEC_CFG: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH1_ERR_DEC_CFG.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH1_ERR_DEC_CFG: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH0_ERR_STATUS.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH0_ERR_STATUS: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_DMA_CH1_ERR_STATUS.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_DMA_CH1_ERR_STATUS: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_AXI_CTL.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_AXI_CTL: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_COFIG_DONE.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_COFIG_DONE: 0x%08x\n",uData);

    uData = pstRegs->TOF_WRAP_INT_CTL.u32;
    TOF_PRINTF_FUNC("TOF_WRAP_INT_CTL: 0x%08x\n",uData);

    uData = pstRegs->TOF_VERSION.u32;
    TOF_PRINTF_FUNC("TOF_VERSION: 0x%08x\n",uData);

    uData = pstRegs->TOF_RELEASE_INFO.u32;
    TOF_PRINTF_FUNC("TOF_RELEASE_INFO: 0x%08x\n",uData);

    TOF_PRINTF_FUNC("read TOF_WRAP regs end!\n");
    #endif
    return 0;
}

