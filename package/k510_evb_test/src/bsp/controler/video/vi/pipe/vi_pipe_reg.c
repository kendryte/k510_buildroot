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

#include "video/vi/pipe/vi_pipe_reg.h"
#include "video/isp_com.h"
//#include "video/vi/vi.h"

int VI_PIPE_DRV_SET_PipeCtrl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_CTRL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeCtrl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeCtrl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_CTRL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_CTRL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeCtrl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTimingCtrl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TIMING_CTRL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTimingCtrl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTimingCtrl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TIMING_CTRL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TIMING_CTRL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTimingCtrl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeSyncWidth(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_SYNC_WIDTH.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeSyncWidth: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeSyncWidth(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_SYNC_WIDTH stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_SYNC_WIDTH.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeSyncWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeImageSizeTotal(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_IMAGE_SIZE_TOTAL.u32 = uData;//0x149f0464;//
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeImageSizeTotal: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeImageSizeTotal(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_IMAGE_SIZE_TOTAL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_IMAGE_SIZE_TOTAL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeImageSizeTotal: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeImageSizeActive(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_IMAGE_SIZE_ACTIVE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeImageSizeActive: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeImageSizeActive(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_IMAGE_SIZE_ACTIVE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_IMAGE_SIZE_ACTIVE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeImageSizeActive: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeImageStart(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_IMAGE_START.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeImageStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeImageStart(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_IMAGE_START stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_IMAGE_START.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeImageStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeFrmBaseAddr0Y(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_FRM_BASE_ADDR0_Y.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeFrmBaseAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeFrmBaseAddr0Y(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_FRM_BASE_ADDR0_Y stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_FRM_BASE_ADDR0_Y.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeFrmBaseAddr0Y: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeFrmBaseAddr1Y(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_FRM_BASE_ADDR1_Y.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeFrmBaseAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeFrmBaseAddr1Y(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_FRM_BASE_ADDR1_Y stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_FRM_BASE_ADDR1_Y.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeFrmBaseAddr1Y: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeFrmBaseAddr0Uv(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_FRM_BASE_ADDR0_UV.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeFrmBaseAddr0Uv: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeFrmBaseAddr0Uv(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_FRM_BASE_ADDR0_UV stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_FRM_BASE_ADDR0_UV.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeFrmBaseAddr0Uv: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeFrmBaseAddr1Uv(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_FRM_BASE_ADDR1_UV.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeFrmBaseAddr1Uv: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeFrmBaseAddr1Uv(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_FRM_BASE_ADDR1_UV stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_FRM_BASE_ADDR1_UV.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeFrmBaseAddr1Uv: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeLineStride(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_LINE_STRIDE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeLineStride(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_LINE_STRIDE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_LINE_STRIDE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgDmaCtl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_DMA_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_PIPE_DRV_SET_PipeTpgDmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgDmaCtl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_DMA_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_DMA_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_PIPE_DRV_GET_PipeTpgDmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgCtl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgCtl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_CTL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgTof(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_TOF.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_PIPE_DRV_SET_PipeTpgTof: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgTof(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_TOF stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_TOF.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_PIPE_DRV_GET_PipeTpgTof: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgSizeTotal(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_SIZE_TOTAL.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgSizeTotal: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgSizeTotal(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_SIZE_TOTAL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_SIZE_TOTAL.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgSizeTotal: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgSizeActive(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_SIZE_ACTIVE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgSizeActive: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgSizeActive(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_SIZE_ACTIVE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_SIZE_ACTIVE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgSizeActive: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgStart(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_START.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgStart(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_START stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_START.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgFrmBaseAddr0Y(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR0_Y.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgFrmBaseAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgFrmBaseAddr0Y(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_FRM_BASE_ADDR0_Y stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR0_Y.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgFrmBaseAddr0Y: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgFrmBaseAddr1Y(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR1_Y.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgFrmBaseAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgFrmBaseAddr1Y(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_FRM_BASE_ADDR1_Y stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR1_Y.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgFrmBaseAddr1Y: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeTpgLineStride(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_TPG_LINE_STRIDE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeTpgLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeTpgLineStride(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_TPG_LINE_STRIDE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_TPG_LINE_STRIDE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeTpgLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeDmaCtrl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_DMA_MODE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeDmaCtrl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeDmaCtrl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
	U_VI_PIPE_DMA_MODE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_DMA_MODE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeDmaCtrl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeDmaErrorMode(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_DMA_ERROR_MODE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeDmaErrorMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeDmaErrorMode(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_DMA_ERROR_MODE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_DMA_ERROR_MODE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeDmaErrorMode: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeDmaRstReq(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_DMA_RST_REQ.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeDmaRstReq: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeDmaRstReq(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_DMA_RST_REQ stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_DMA_RST_REQ.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeDmaRstReq: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeConfigDone(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_CONFIG_DONE.u32 = uData;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_PipeConfigDone: 0x%08x\n", uData);
    #endif

    return 0;
}

int VI_PIPE_DRV_SET_IntPol(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    U_VI_PIPE_CONFIG_DONE stData;
    stData.u32 = pstRegs->VI_PIPE_CONFIG_DONE.u32;
    stData.bits.int_pol = uData;
    pstRegs->VI_PIPE_CONFIG_DONE.u32 = stData.u32;
    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_SET_IntPol: 0x%08x\n", stData.u32);
    #endif

    return 0;
}

int VI_PIPE_DRV_GET_PipeConfigDone(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_CONFIG_DONE stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_CONFIG_DONE.u32;

    #if VI_DEBUG_OPEN
        VI_PRINTF_FUNC("VI_DRV_GET_PipeConfigDone: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int VI_PIPE_DRV_SET_PipeIntCtl(S_VI_PIPE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VI_CHECK_POINTER(pstRegs);

    pstRegs->VI_PIPE_INT_CTL.u32 = uData;
    #if VI_DEBUG_OPEN
    //   VI_PRINTF_FUNC("VI_DRV_SET_PipeIntCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VI_PIPE_DRV_GET_PipeIntCtl(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    U_VI_PIPE_INT_CTL stData;
    VI_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->VI_PIPE_INT_CTL.u32;

    #if VI_DEBUG_OPEN
        //VI_PRINTF_FUNC("VI_DRV_GET_PipeIntCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*debug
*/
int VI_PIPE_DRV_GET_PipeRegsVal(S_VI_PIPE_REGS_TYPE *pstRegs)
{
    VI_CHECK_POINTER(pstRegs);

    #if VI_PIPE_DEBUG_OPEN
    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI00 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_0_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI01 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_1_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_1_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI02 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_0_2_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_0_2_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE CSI10 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_CSI_1_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_1_0_REG_BASE+i));
    }

    for(int i =0;i<0xA4;i=i+4)  //0x49c
    {
    	printf("VI PIPE DVP0 REG:Reg[0x%x]= 0x%x\n", VI_PIPE_DVP_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_DVP_0_REG_BASE+i));
    }
	#endif

	#if 0
    unsigned int stData;
    VI_PRINTF_FUNC("read VI_PIPE regs start!\n");    
  
    //
    stData = pstRegs->VI_PIPE_CTRL.u32;
    VI_PRINTF_FUNC("VI_PIPE_CTRL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TIMING_CTRL.u32;
    VI_PRINTF_FUNC("VI_PIPE_TIMING_CTRL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_SYNC_WIDTH.u32;
    VI_PRINTF_FUNC("VI_PIPE_SYNC_WIDTH: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_IMAGE_SIZE_TOTAL.u32;
    VI_PRINTF_FUNC("VI_PIPE_IMAGE_SIZE_TOTAL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_IMAGE_SIZE_ACTIVE.u32;
    VI_PRINTF_FUNC("VI_PIPE_IMAGE_SIZE_ACTIVE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_IMAGE_START.u32;
    VI_PRINTF_FUNC("VI_PIPE_IMAGE_START: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_FRM_BASE_ADDR0_Y.u32;
    VI_PRINTF_FUNC("VI_PIPE_FRM_BASE_ADDR0_Y: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_FRM_BASE_ADDR1_Y.u32;
    VI_PRINTF_FUNC("VI_PIPE_FRM_BASE_ADDR1_Y: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_FRM_BASE_ADDR0_UV.u32;
    VI_PRINTF_FUNC("VI_PIPE_FRM_BASE_ADDR0_UV: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_FRM_BASE_ADDR1_UV.u32;
    VI_PRINTF_FUNC("VI_PIPE_FRM_BASE_ADDR1_UV: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_LINE_STRIDE.u32;
    VI_PRINTF_FUNC("VI_PIPE_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_DMA_CTL.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_CTL.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_CTL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_TOF.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_TOF: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_SIZE_TOTAL.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_SIZE_TOTAL: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_SIZE_ACTIVE.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_SIZE_ACTIVE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_START.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_START: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR0_Y.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_FRM_BASE_ADDR0_Y: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_FRM_BASE_ADDR1_Y.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_FRM_BASE_ADDR1_Y: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_TPG_LINE_STRIDE.u32;
    VI_PRINTF_FUNC("VI_PIPE_TPG_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_DMA_MODE.u32;
    VI_PRINTF_FUNC("VI_PIPE_DMA_MODE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_DMA_ERROR_MODE.u32;
    VI_PRINTF_FUNC("VI_PIPE_DMA_ERROR_MODE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_DMA_RST_REQ.u32;
    VI_PRINTF_FUNC("VI_PIPE_DMA_RST_REQ: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_CONFIG_DONE.u32;
    VI_PRINTF_FUNC("VI_PIPE_CONFIG_DONE: 0x%08x\n", stData);

    stData = pstRegs->VI_PIPE_INT_CTL.u32;
    VI_PRINTF_FUNC("VI_PIPE_INT_CTL: 0x%08x\n", stData);

    VI_PRINTF_FUNC("read VI_PIPE regs end!\n");  
    #endif

    return 0;
}
