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
#include "video/isp/core/isp_core_reg.h"
//#include "video/isp/isp.h"

extern unsigned int  *reg_isp_2k_core_base;
/*
*Image Timing Control
*/
int ISP_CORE_DRV_SET_CoreItcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ITC_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreItcCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreItcCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ITC_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ITC_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreItcCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreImageHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_HEIGHT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageHeight: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreImageHeight(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_HEIGHT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_HEIGHT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreImageWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_WIDTH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageWidth: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreImageWidth(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_WIDTH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_WIDTH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreImageVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_V_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreImageVStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_V_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_V_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreImageHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_H_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreImageHStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_H_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_H_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreImageActiveWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_ACTIVE_WIDTH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageActiveWidth: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreImageActiveWidth(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_ACTIVE_WIDTH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_ACTIVE_WIDTH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageActiveWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreImageActiveHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_IMAGE_ACTIVE_HEIGHT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreImageActiveHeight: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreImageActiveHeight(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_IMAGE_ACTIVE_HEIGHT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_IMAGE_ACTIVE_HEIGHT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreImageActiveHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Test Pattern Control
*/ 
int ISP_CORE_DRV_SET_CoreTestCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_TEST_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreTestCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreTestCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_TEST_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_TEST_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreTestCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Black Level Correction
*/
int ISP_CORE_DRV_SET_CoreBlcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_BLC_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreBlcCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreBlcCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_BLC_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_BLC_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreBlcCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreBlcOffset(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_BLC_OFFSET.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreBlcOffset: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreBlcOffset(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_BLC_OFFSET stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_BLC_OFFSET.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreBlcOffset: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreBlcRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_BLC_RATIO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreBlcRatio: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreBlcRatio(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_BLC_RATIO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_BLC_RATIO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreBlcRatio: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* Lens Shading Correction 
*/
int ISP_CORE_DRV_SET_CoreLscCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreLscCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreLscHCenter(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_H_CENTER.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscHCenter: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscHCenter(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_H_CENTER stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_H_CENTER.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscHCenter: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLscVCenter(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_V_CENTER.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscVCenter: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscVCenter(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_V_CENTER stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_V_CENTER.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscVCenter: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLscRRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_R_RATIO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscRRatio: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscRRatio(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_R_RATIO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_R_RATIO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscRRatio: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLscGRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_G_RATIO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscGRatio: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscGRatio(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_G_RATIO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_G_RATIO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscGRatio: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLscBRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_B_RATIO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscBRatio: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscBRatio(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_B_RATIO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_B_RATIO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscBRatio: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLscIrRatio(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LSC_IR_RATIO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLscIrRatio: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLscIrRatio(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LSC_IR_RATIO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LSC_IR_RATIO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLscIrRatio: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*AUTO Exposure/Gain 
*/
int ISP_CORE_DRV_SET_CoreAeCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_WIN_H_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeWinHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_WIN_H_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_WIN_H_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeWinHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_WIN_V_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeWinVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_WIN_V_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_WIN_V_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeWinVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_WIN_H_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeWinHEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_WIN_H_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_WIN_H_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeWinHEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_WIN_V_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeWinVEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_WIN_V_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_WIN_V_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeWinVEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeTarBr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_TAR_BR.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeTarBr: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeTarBr(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_TAR_BR stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_TAR_BR.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeTarBr: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeTarBrRange(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_TAR_BR_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeTarBrRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeTarBrRange(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_TAR_BR_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_TAR_BR_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeTarBrRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeLExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_L_EX_TIME.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeLExTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeLExTime(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_L_EX_TIME stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_L_EX_TIME.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeLExTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeMExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_M_EX_TIME.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeMExTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeMExTime(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_M_EX_TIME stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_M_EX_TIME.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeMExTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeSExTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_S_EX_TIME.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeSExTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeSExTime(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_S_EX_TIME stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_S_EX_TIME.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeSExTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeAgc(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_AGC.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeAgc: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeAgc(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_AGC stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_AGC.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeAgc: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeAdjustCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_ADJUST_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeAdjustCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeAdjustCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_ADJUST_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_ADJUST_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeAdjustCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_ADJUST_STEP_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeAdjustStepMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_ADJUST_STEP_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_ADJUST_STEP_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeAdjustStepMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeExValueMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_EX_VALUE_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeExValueMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeExValueMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_EX_VALUE_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_EX_VALUE_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeExValueMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeExValueMid(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_EX_VALUE_MID.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeExValueMid: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeExValueMid(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_EX_VALUE_MID stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_EX_VALUE_MID.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeExValueMid: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeExValueMin(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_EX_VALUE_MIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeExValueMin: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAe_ExValueMin(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_EX_VALUE_MIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_EX_VALUE_MIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeExValueMin: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeGainMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_GAIN_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeGainMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeGainMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_GAIN_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_GAIN_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeGainMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeGainMid(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_GAIN_MID.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeGainMid: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeGainMid(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_GAIN_MID stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_GAIN_MID.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeGainMid: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeGainMin(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_GAIN_MIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeGainMin: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeGainMin(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_GAIN_MIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_GAIN_MIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeGainMin: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeDnSwitchAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeDnSwitchAdjustStepMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeDnSwitchAdjustStepMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeDnSwitchAdjustStepMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAeDnSwitchWaitTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AE_DN_SWITCH_WAIT_TIME.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAeDnSwitchWaitTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAeDnSwitchWaitTime(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_DN_SWITCH_WAIT_TIME stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_DN_SWITCH_WAIT_TIME.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeDnSwitchWaitTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeDiffMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_DIFF_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeDiffMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeDiffMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_DIFF_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_DIFF_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeDiffMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeDrvSignalMax(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_DRV_SIGNAL_MAX.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeDrvSignalMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeDrvSignalMax(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_DRV_SIGNAL_MAX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_DRV_SIGNAL_MAX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeDrvSignalMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeCoeffDis(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_COEFF_DIS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeCoeffDis: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeCoeffDis(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_COEFF_DIS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_COEFF_DIS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeCoeffDis: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeCoeffSpeed(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_COEFF_SPEED.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeCoeffSpeed: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeCoeffSpeed(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_COEFF_SPEED stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_COEFF_SPEED.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeCoeffSpeed: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeCoeffAcce(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_COEFF_ACCE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeCoeffAcce: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeCoeffAcce(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_COEFF_ACCE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_COEFF_ACCE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeCoeffAcce: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeDrvManualValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_DRV_MANUAL_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeDrvManualValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeDrvManualValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_DRV_MANUAL_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_DRV_MANUAL_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeDrvManualValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreApeDampManualValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_APE_DAMP_MANUAL_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreApeDampManualValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreApeDampManualValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_APE_DAMP_MANUAL_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_APE_DAMP_MANUAL_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreApeDampManualValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* onlu read
*/
int ISP_CORE_DRV_GET_CoreAeValueReady(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_VALUE_READY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_VALUE_READY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeValueReady: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeLongCurEx(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_LONG_CUR_EX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_LONG_CUR_EX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeLongCurEx: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeMidCurEx(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_MID_CUR_EX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_MID_CUR_EX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeMidCurEx: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeShortCurEx(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_SHORT_CUR_EX stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_SHORT_CUR_EX.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeShortCurEx: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeCurDigitalGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_CUR_DIGITAL_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_CUR_DIGITAL_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeCurDigitalGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeCurAveBrightness(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_CUR_AVE_BRIGHTNESS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_CUR_AVE_BRIGHTNESS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeCurAveBrightness: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeCurDnStatus(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_CUR_DN_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_CUR_DN_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeCurDnStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAeExStatus(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_EX_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_EX_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeExStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_GET_CoreAeSum(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_SUM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_SUM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAeSum: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAePixelSum(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AE_PIXEL_SUM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AE_PIXEL_SUM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAePixelSum: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*AWB
*/
int ISP_CORE_DRV_SET_CoreAwbCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbD65RedGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_D65_RED_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbD65RedGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbD65RedGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_D65_RED_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_D65_RED_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbD65RedGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbD65BlueGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_D65_BLUE_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbD65BlueGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbD65BlueGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_D65_BLUE_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_D65_BLUE_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbD65BlueGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmRrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_RR_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmRrCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmRrCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_RR_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_RR_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmRrCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmRgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_RG_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmRgCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmRgCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_RG_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_RG_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmRgCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmRbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_RB_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmRbCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmRbCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_RB_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_RB_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmRbCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmGrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_GR_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmGrCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmGrCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_GR_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_GR_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmGrCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmGgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_GG_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmGgCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmGgCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_GG_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_GG_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmGgCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmGbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_GB_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmGbCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmGbCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_GB_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_GB_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmGbCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmBrCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_BR_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmBrCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmBrCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_BR_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_BR_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmBrCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmBgCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_BG_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmBgCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmBgCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_BG_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_BG_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmBgCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmBbCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_BB_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmBbCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmBbCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_BB_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_BB_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmBbCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCcmCorrectCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CCM_CORRECT_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCcmCorrectCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCcmCorrectCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CCM_CORRECT_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CCM_CORRECT_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCcmCorrectCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_WIN_H_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbWinHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_WIN_H_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_WIN_H_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbWinHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_WIN_V_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbWinVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_WIN_V_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_WIN_V_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbWinVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_WIN_H_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbWinHEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_WIN_H_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_WIN_H_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbWinHEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_WIN_V_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbWinVEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_WIN_V_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_WIN_V_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbWinVEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbCorrectDiffTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_CORRECT_DIFF_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbCorrectDiffTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbCorrectDiffTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_CORRECT_DIFF_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_CORRECT_DIFF_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbCorrectDiffTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbResTime(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_RES_TIME.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbResTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbResTime(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RES_TIME stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RES_TIME.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbResTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbHistTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_HIST_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbHistTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbHistTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_HIST_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_HIST_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbHistTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbRedGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_RED_GAIN_ADJUST.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbRedGainAdjust: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbRedGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_GAIN_ADJUST stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_GAIN_ADJUST.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedGainAdjust: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbGreenGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_GREEN_GAIN_ADJUST.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbGreenGainAdjust: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbGreenGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_GREEN_GAIN_ADJUST stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_GREEN_GAIN_ADJUST.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbGreenGainAdjust: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbBlueGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_BLUE_GAIN_ADJUST.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbBlueGainAdjust: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbBlueGainAdjust(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_GAIN_ADJUST stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_GAIN_ADJUST.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueGainAdjust: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbRedMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_RED_MAX_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbRedMaxValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbRedMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_MAX_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_MAX_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedMaxValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbBlueMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_BLUE_MAX_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbBlueMaxValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbBlueMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_MAX_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_MAX_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueMaxValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbRedMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_RED_MIN_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbRedMinValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbRedMinValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_MIN_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_MIN_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedMinValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbBlueMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_BLUE_MIN_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbBlueMinValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbBlueMinValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_MIN_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_MIN_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueMinValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAwbRedObjValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AWB_RED_OBJ_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAwbRedObjValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAwbRedObjValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_OBJ_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_OBJ_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedObjValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* only read
*/
int ISP_CORE_DRV_GET_CoreAwbBlueObjValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_OBJ_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_OBJ_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueObjValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBlueHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_HIST_PIXEL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_HIST_PIXEL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueHistPixel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbRedHistValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_HIST_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_HIST_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedHistValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbRedHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_HIST_PIXEL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_HIST_PIXEL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedHistPixel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBypassBlueHistValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBypassBlueHistValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBypassBlueHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBypassBlueHistPixel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBypassRedHistValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BYPASS_RED_HIST_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BYPASS_RED_HIST_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBypassRedHistValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBypassRedHistPixel(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBypassRedHistPixel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbRedValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_RED_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_RED_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbRedValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbGreenValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_GREEN_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_GREEN_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbGreenValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbBlueValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_BLUE_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_BLUE_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbBlueValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbOrgRedValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_ORG_RED_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_ORG_RED_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbOrgRedValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbOrgGreenValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_ORG_GREEN_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_ORG_GREEN_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbOrgGreenValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAwbOrgBlueValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AWB_ORG_BLUE_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AWB_ORG_BLUE_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAwbOrgBlueValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*wdr
*/
int ISP_CORE_DRV_SET_CoreWdrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreWdrCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreWdrOverExRatioTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrOverExRatioTh1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreWdrOverExRatioTh1(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_OVER_EX_RATIO_TH1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrOverExRatioTh1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreWdrOverExRatioTh2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrOverExRatioTh2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreWdrOverExRatioTh2(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_OVER_EX_RATIO_TH2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrOverExRatioTh2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreWdrFusionRatioTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_FUSION_RATIO_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrFusionRatioTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreWdrFusionRatioTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_FUSION_RATIO_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_FUSION_RATIO_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrFusionRatioTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreWdrFusionValue1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_FUSION_VALUE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrFusionValue1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreWdrFusionValue1(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_FUSION_VALUE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_FUSION_VALUE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrFusionValue1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreWdrFusionValue2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_WDR_FUSION_VALUE2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreWdrFusionValue2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreWdrFusionValue2(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_WDR_FUSION_VALUE2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_WDR_FUSION_VALUE2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreWdrFusionValue2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*csc
*/
int ISP_CORE_DRV_SET_CoreCscR2Y00(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_00.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y00: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y00(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_00 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_00.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y01(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_01.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y01: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y01(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_01 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_01.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y02(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_02.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y02: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y02(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_02 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_02.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y10(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_10.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y10: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y10(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_10 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_10.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y11(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_11.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y11: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y11(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_11 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_11.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y12(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_12.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y12: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y12(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_12 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_12.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y20(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_20.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y20: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y20(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_20 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_20.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y21(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_21.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y21: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y21(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_21 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_21.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreCscR2Y22(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CSC_R2Y_22.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreCscR2Y22: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreCscR2Y22(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CSC_R2Y_22 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CSC_R2Y_22.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreCscR2Y22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*ADA
*/
int ISP_CORE_DRV_SET_CoreAdaCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaStatMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_STAT_MAX_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaStatMaxValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaStatMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_STAT_MAX_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_STAT_MAX_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaStatMaxValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaAdStrenMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_AD_STREN_MAX_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaAdStrenMaxValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaAdStrenMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_AD_STREN_MAX_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_AD_STREN_MAX_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaAdStrenMaxValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_WIN_H_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaWinHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_WIN_H_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_WIN_H_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaWinHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_WIN_V_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaWinVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_WIN_V_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_WIN_V_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaWinVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_WIN_H_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaWinHEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_WIN_H_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_WIN_H_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaWinHEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAdaWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ADA_WIN_V_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAdaWinVEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAdaWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ADA_WIN_V_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ADA_WIN_V_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAdaWinVEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*rgbir
*/
int ISP_CORE_DRV_SET_CoreRgbirCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreRgbirRpcMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_RPC_MAX_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirRpcMaxValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirRpcMaxValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_RPC_MAX_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_RPC_MAX_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirRpcMaxValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreRgbirRpcColorCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_RPC_COLOR_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirRpcColorCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirRpcColorCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_RPC_COLOR_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_RPC_COLOR_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirRpcColorCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreRgbirRpcLumaCoff(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_RPC_LUMA_COFF.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirRpcLumaCoff: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirRpcLumaCoff(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_RPC_LUMA_COFF stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_RPC_LUMA_COFF.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirRpcLumaCoff: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreRgbirRpcTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_RPC_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirRpcTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirRpcTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_RPC_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_RPC_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirRpcTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreRgbirRpcTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RGBIR_RPC_TH1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRgbirRpcTh1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRgbirRpcTh1(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RGBIR_RPC_TH1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RGBIR_RPC_TH1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRgbirRpcTh1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* 2D Noise Reduction 
*/
int ISP_CORE_DRV_SET_Core2DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core2DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_Core2DnrRawIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_RAW_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrRawIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core2DnrRawIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_RAW_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_RAW_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrRawIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_Core2DnrBapIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_BAP_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrBapIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_Core2DnrBapIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_BAP_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_BAP_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrBapIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core2DnrEdgeIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_EDGE_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrEdgeIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core2DnrEdgeIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_EDGE_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_EDGE_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrEdgeIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core2DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_LUMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrLumaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core2DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_LUMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_LUMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrLumaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core2DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_2DNR_CHROMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core2DnrChromaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core2DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_2DNR_CHROMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_2DNR_CHROMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core2DnrChromaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*3D Noise Reduction
*/
int ISP_CORE_DRV_SET_Core3DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPreLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_PRE_LUMA_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPreLumaTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPreLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_PRE_LUMA_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_PRE_LUMA_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPreLumaTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPreLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_PRE_LUMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPreLumaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPreLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_PRE_LUMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_PRE_LUMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPreLumaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPreChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_PRE_CHROMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPreChromaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPreChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_PRE_CHROMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_PRE_CHROMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPreChromaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_MID_FILTER_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrMidFilterTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_MID_FILTER_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_MID_FILTER_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrMidFilterTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPreMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_PRE_MID_FILTER_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPreMidFilterTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPreMidFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_PRE_MID_FILTER_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_PRE_MID_FILTER_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPreMidFilterTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrCurFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_CUR_FILTER_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrCurFilterTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrCurFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_CUR_FILTER_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_CUR_FILTER_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrCurFilterTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrLowPassFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_LOW_PASS_FILTER_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrLowPassFilterTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrLowPassFilterTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_LOW_PASS_FILTER_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_LOW_PASS_FILTER_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrLowPassFilterTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_LUMA_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrLumaTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrLumaTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_LUMA_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_LUMA_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrLumaTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrMinValue(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_MIN_VALUE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrMinValue: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrMinValue(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_MIN_VALUE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_MIN_VALUE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrMinValue: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_LUMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrLumaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_LUMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_LUMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrLumaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_CHROMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrChromaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_CHROMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_CHROMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrChromaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPostEdgeTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_POST_EDGE_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPostEdgeTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPostEdgeTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_POST_EDGE_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_POST_EDGE_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPostEdgeTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPostLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_POST_LUMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPostLumaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPostLumaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_POST_LUMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_POST_LUMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPostLumaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_Core3DnrPostChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_3DNR_POST_CHROMA_INTENSITY.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Core3DnrPostChromaIntensity: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_Core3DnrPostChromaIntensity(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_3DNR_POST_CHROMA_INTENSITY stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_3DNR_POST_CHROMA_INTENSITY.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Core3DnrPostChromaIntensity: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreEnhCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ENH_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreEnhCtl: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*ENH
*/
int ISP_CORE_DRV_GET_CoreEnhCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ENH_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ENH_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreEnhCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLtmGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LTM_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLtmGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLtmGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LTM_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LTM_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLtmGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLtmTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LTM_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLtmTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLtmTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LTM_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LTM_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLtmTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreEnhNrTh(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ENH_NR_TH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreEnhNrTh: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreEnhNrTh(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ENH_NR_TH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ENH_NR_TH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreEnhNrTh: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreEnhTh1(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ENH_TH1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreEnhTh1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreEnhTh1(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ENH_TH1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ENH_TH1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreEnhTh1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreEnhTh2(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_ENH_TH2.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreEnhTh2: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreEnhTh2(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_ENH_TH2 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_ENH_TH2.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreEnhTh2: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreSharpGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_SHARP_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreSharpGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreSharpGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_SHARP_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_SHARP_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreSharpGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*POST Control
*/
int ISP_CORE_DRV_SET_CorePostCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_POST_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CorePostCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CorePostCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_POST_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_POST_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CorePostCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreContGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_CONT_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreContGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreContGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_CONT_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_CONT_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreContGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLumaGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LUMA_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLumaGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLumaGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LUMA_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LUMA_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLumaGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreSatuGain(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_SATU_GAIN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreSatuGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreSatuGain(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_SATU_GAIN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_SATU_GAIN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreSatuGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*OTC
*/
int ISP_CORE_DRV_SET_CoreOtcSttVr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_OTC_STT_VR.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_SET_CoreOtcSttVr: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreOtcSttVr(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_OTC_STT_VR stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_OTC_STT_VR.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_GET_CoreOtcSttVr: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreOtcSttHr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_OTC_STT_HR.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_SET_CoreOtcSttHr: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreOtcSttHr(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_OTC_STT_HR stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_OTC_STT_HR.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_GET_CoreOtcSttHr: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreOtcHeight(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_OTC_HEIGHT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_SET_CoreOtcHeight: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreOtcHeight(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_OTC_HEIGHT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_OTC_HEIGHT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_GET_CoreOtcHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreOtcWidth(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_OTC_WIDTH.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_SET_CoreOtcWidth: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreOtcWidth(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_OTC_WIDTH stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_OTC_WIDTH.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_CORE_DRV_GET_CoreOtcWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*LDC
*/
int ISP_CORE_DRV_SET_CoreLdcCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLdcReqFreq(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_REQ_FREQ.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcReqFreq: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcReqFreq(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_REQ_FREQ stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_REQ_FREQ.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcReqFreq: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLdcHCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_H_CENTER_POS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcHCenterPos: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcHCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_H_CENTER_POS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_H_CENTER_POS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcHCenterPos: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLdcVCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_V_CENTER_POS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcVCenterPos: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcVCenterPos(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_V_CENTER_POS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_V_CENTER_POS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcVCenterPos: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLdcRectifyCr(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_RECTIFY_CR.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcRectifyCr: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcRectifyCr(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_RECTIFY_CR stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_RECTIFY_CR.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcRectifyCr: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreLdcRectifyCz(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_LDC_RECTIFY_CZ.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreLdcRectifyCz: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreLdcRectifyCz(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_LDC_RECTIFY_CZ stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_LDC_RECTIFY_CZ.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreLdcRectifyCz: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*ISP Table Control
*/
int ISP_CORE_DRV_SET_CoreRamWrStatus(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_RAM_WR_STATUS.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreRamWrStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreRamWrStatus(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RAM_WR_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RAM_WR_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRamWrStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreRamRdStatus(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RAM_RD_STATUS stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RAM_RD_STATUS.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRamRdStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreRamReadLock(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_RAM_READ_LOCK stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_RAM_READ_LOCK.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreRamReadLock: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*AF Statistics
*/
int ISP_CORE_DRV_SET_CoreAfCtl(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AF_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAfCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_CORE_DRV_GET_CoreAfCtl(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_SET_CoreAfStatWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AF_STAT_WIN_H_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAfStatWinHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAfStatWinHStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_STAT_WIN_H_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_STAT_WIN_H_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfStatWinHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAfStatWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AF_STAT_WIN_V_START.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAfStatWinVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAfStatWinVStart(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_STAT_WIN_V_START stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_STAT_WIN_V_START.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfStatWinVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAfStatWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AF_STAT_WIN_H_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAfStatWinHEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAfStatWinHEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_STAT_WIN_H_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_STAT_WIN_H_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfStatWinHEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_SET_CoreAfStatWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_CORE_AF_STAT_WIN_V_END.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_CoreAfStatWinVEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_CORE_DRV_GET_CoreAfStatWinVEnd(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_STAT_WIN_V_END stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_STAT_WIN_V_END.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfStatWinVEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAfMidFrqData(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_MID_FRQ_DATA stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_MID_FRQ_DATA.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfMidFrqData: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAfHighFrqData(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_HIGH_FRQ_DATA stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_HIGH_FRQ_DATA.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfHighFrqData: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_CORE_DRV_GET_CoreAfStatPixelNum(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    U_ISP_CORE_AF_STAT_PIXEL_NUM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_CORE_AF_STAT_PIXEL_NUM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_CoreAfStatPixelNum: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_CORE_DRV_GET_CoreRegsVal(S_ISP_CORE_REGS_TYPE *pstRegs)
{
    ISP_CHECK_POINTER(pstRegs);
    unsigned int stData;
    #if ISP_CORE_DEBUG_OPEN
    for(int i =0;i<0x32C;i=i+4)  //0x49c
    {
    	printf("ISP CORE REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_core_base+i, *(volatile unsigned int *)(reg_isp_2k_core_base+i));
    }
	#endif
	#if 0
    ISP_PRINTF_FUNC("read ISP_CORE regs start!\n");    
    //itc
    stData = pstRegs->ISP_CORE_ITC_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ITC_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_IMAGE_HEIGHT.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_HEIGHT: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_IMAGE_WIDTH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_WIDTH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_IMAGE_V_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_V_START: 0x%08x\n", stData);  

    stData = pstRegs->ISP_CORE_IMAGE_H_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_H_START: 0x%08x\n", stData);  

    stData = pstRegs->ISP_CORE_IMAGE_ACTIVE_WIDTH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_ACTIVE_WIDTH: 0x%08x\n", stData); 

    stData = pstRegs->ISP_CORE_IMAGE_ACTIVE_HEIGHT.u32;
    ISP_PRINTF_FUNC("ISP_CORE_IMAGE_ACTIVE_HEIGHT: 0x%08x\n", stData);
    //tpg
    stData = pstRegs->ISP_CORE_TEST_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_TEST_CTL: 0x%08x\n", stData);

    //tpg
    stData = pstRegs->ISP_CORE_BLC_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_BLC_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_BLC_OFFSET.u32;
    ISP_PRINTF_FUNC("ISP_CORE_BLC_OFFSET: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_BLC_RATIO.u32;
    ISP_PRINTF_FUNC("ISP_CORE_BLC_RATIO: 0x%08x\n", stData);
    //lsc
    stData = pstRegs->ISP_CORE_LSC_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_H_CENTER.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_H_CENTER: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_V_CENTER.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_V_CENTER: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_R_RATIO.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_R_RATIO: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_G_RATIO.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_G_RATIO: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_B_RATIO.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_B_RATIO: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LSC_IR_RATIO.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_IR_RATIO: 0x%08x\n", stData);
    //AE
	stData = pstRegs->ISP_CORE_AE_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_WIN_H_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_WIN_H_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_WIN_V_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_WIN_V_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_WIN_H_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_WIN_H_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_WIN_V_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_WIN_V_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_TAR_BR.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_TAR_BR: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_TAR_BR_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_TAR_BR_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_L_EX_TIME.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_L_EX_TIME: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_M_EX_TIME.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_M_EX_TIME: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_S_EX_TIME.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_S_EX_TIME: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_AGC.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_AGC: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_ADJUST_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_ADJUST_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_ADJUST_STEP_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_ADJUST_STEP_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_EX_VALUE_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_EX_VALUE_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_EX_VALUE_MID.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_EX_VALUE_MID: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_EX_VALUE_MIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_EX_VALUE_MIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_GAIN_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_GAIN_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_GAIN_MID.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_GAIN_MID: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_GAIN_MIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_GAIN_MIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_DN_SWITCH_ADJUST_STEP_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_DN_SWITCH_WAIT_TIME.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_DN_SWITCH_WAIT_TIME: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_DIFF_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_DIFF_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_DRV_SIGNAL_MAX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_DRV_SIGNAL_MAX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_COEFF_DIS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_COEFF_DIS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_COEFF_SPEED.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_COEFF_SPEED: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_COEFF_ACCE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_COEFF_ACCE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_DRV_MANUAL_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_DRV_MANUAL_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_APE_DAMP_MANUAL_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_APE_DAMP_MANUAL_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_VALUE_READY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_VALUE_READY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_LONG_CUR_EX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_LONG_CUR_EX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_MID_CUR_EX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_MID_CUR_EX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_SHORT_CUR_EX.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_SHORT_CUR_EX: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_CUR_DIGITAL_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_CUR_DIGITAL_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_CUR_AVE_BRIGHTNESS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_CUR_AVE_BRIGHTNESS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_CUR_DN_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_CUR_DN_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_EX_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_EX_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_SUM.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_SUM: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AE_PIXEL_SUM.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AE_PIXEL_SUM: 0x%08x\n", stData);

	//AWB
    stData = pstRegs->ISP_CORE_AWB_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_D65_RED_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_D65_RED_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_D65_BLUE_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_D65_BLUE_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_RR_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_RR_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_RG_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_RG_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_RB_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_RB_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_GR_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_GR_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_GG_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_GG_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_GB_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_GB_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_BR_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_BR_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_BG_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_BG_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_BB_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_BB_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CCM_CORRECT_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CCM_CORRECT_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_WIN_H_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_WIN_H_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_WIN_V_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_WIN_V_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_WIN_H_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_WIN_H_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_WIN_V_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_WIN_V_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_CORRECT_DIFF_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_CORRECT_DIFF_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RES_TIME.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RES_TIME: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_HIST_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_HIST_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_GAIN_ADJUST.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_GAIN_ADJUST: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_GREEN_GAIN_ADJUST.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_GREEN_GAIN_ADJUST: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_GAIN_ADJUST.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_GAIN_ADJUST: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_MAX_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_MAX_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_MAX_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_MAX_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_MIN_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_MIN_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_MIN_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_MIN_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_OBJ_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_OBJ_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_OBJ_VALUE.u32;    
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_OBJ_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_HIST_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_HIST_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_HIST_PIXEL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LSC_IR_RATIO: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_HIST_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_HIST_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_HIST_PIXEL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_HIST_PIXEL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BYPASS_BLUE_HIST_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BYPASS_BLUE_HIST_PIXEL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BYPASS_RED_HIST_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BYPASS_RED_HIST_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BYPASS_RED_HIST_PIXEL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_RED_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_RED_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_GREEN_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_GREEN_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_BLUE_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_BLUE_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_ORG_RED_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_ORG_RED_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_ORG_GREEN_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_ORG_GREEN_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AWB_ORG_BLUE_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AWB_ORG_BLUE_VALUE: 0x%08x\n", stData);
    //WDR
    stData = pstRegs->ISP_CORE_WDR_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH1.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_OVER_EX_RATIO_TH1: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_WDR_OVER_EX_RATIO_TH2.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_OVER_EX_RATIO_TH2: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_WDR_FUSION_RATIO_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_FUSION_RATIO_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_WDR_FUSION_VALUE1.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_FUSION_VALUE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_WDR_FUSION_VALUE2.u32;
    ISP_PRINTF_FUNC("ISP_CORE_WDR_FUSION_VALUE2: 0x%08x\n", stData);
    //CSC
    stData = pstRegs->ISP_CORE_CSC_R2Y_00.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_00: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_01.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_01: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_02.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_02: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_10.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_10: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_11.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_11: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_12.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_12: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_20.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_20: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_21.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_21: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CSC_R2Y_22.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CSC_R2Y_22: 0x%08x\n", stData);
    //ADA
    stData = pstRegs->ISP_CORE_ADA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ADA_STAT_MAX_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_STAT_MAX_VALUE: 0x%08x\n", stData);

    stData = pstRegs-> ISP_CORE_ADA_AD_STREN_MAX_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_AD_STREN_MAX_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ADA_WIN_H_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_WIN_H_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ADA_WIN_V_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_WIN_V_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ADA_WIN_H_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_WIN_H_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ADA_WIN_V_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ADA_WIN_V_END: 0x%08x\n", stData);
    //RGBIR
    stData = pstRegs->ISP_CORE_RGBIR_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RGBIR_RPC_MAX_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_RPC_MAX_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RGBIR_RPC_COLOR_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_RPC_COLOR_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RGBIR_RPC_LUMA_COFF.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_RPC_LUMA_COFF: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RGBIR_RPC_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_RPC_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RGBIR_RPC_TH1.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RGBIR_RPC_TH1: 0x%08x\n", stData);
    //2DNR
    stData = pstRegs->ISP_CORE_2DNR_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_2DNR_RAW_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_RAW_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_2DNR_BAP_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_BAP_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_2DNR_EDGE_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_EDGE_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_2DNR_LUMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_LUMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_2DNR_CHROMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_2DNR_CHROMA_INTENSITY: 0x%08x\n", stData);
    //3DNR
    stData = pstRegs->ISP_CORE_3DNR_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_PRE_LUMA_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_PRE_LUMA_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_PRE_LUMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_PRE_LUMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_PRE_CHROMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_PRE_CHROMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_MID_FILTER_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_MID_FILTER_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_PRE_MID_FILTER_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_PRE_MID_FILTER_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_CUR_FILTER_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_CUR_FILTER_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_LOW_PASS_FILTER_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_LOW_PASS_FILTER_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_LUMA_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_LUMA_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_MIN_VALUE.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_MIN_VALUE: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_LUMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_LUMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_CHROMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_CHROMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_POST_EDGE_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_POST_EDGE_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_POST_LUMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_POST_LUMA_INTENSITY: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_3DNR_POST_CHROMA_INTENSITY.u32;
    ISP_PRINTF_FUNC("ISP_CORE_3DNR_POST_CHROMA_INTENSITY: 0x%08x\n", stData);
    //ENH
    stData = pstRegs->ISP_CORE_ENH_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ENH_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LTM_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LTM_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LTM_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LTM_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ENH_NR_TH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ENH_NR_TH: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ENH_TH1.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ENH_TH1: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_ENH_TH2.u32;
    ISP_PRINTF_FUNC("ISP_CORE_ENH_TH2: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_SHARP_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_SHARP_GAIN: 0x%08x\n", stData);
    //POST
    stData = pstRegs->ISP_CORE_POST_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_POST_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_CONT_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_CONT_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LUMA_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LUMA_GAIN: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_SATU_GAIN.u32;
    ISP_PRINTF_FUNC("ISP_CORE_SATU_GAIN: 0x%08x\n", stData);
	//OTC
    stData = pstRegs->ISP_CORE_OTC_STT_VR.u32;
    ISP_PRINTF_FUNC("ISP_CORE_OTC_STT_VR: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_OTC_STT_HR.u32;
    ISP_PRINTF_FUNC("ISP_CORE_OTC_STT_HR: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_OTC_HEIGHT.u32;
    ISP_PRINTF_FUNC("ISP_CORE_OTC_HEIGHT: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_OTC_WIDTH.u32;
    ISP_PRINTF_FUNC("ISP_CORE_OTC_WIDTH: 0x%08x\n", stData);
	//LDC
    stData = pstRegs->ISP_CORE_LDC_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LDC_REQ_FREQ.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_REQ_FREQ: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LDC_H_CENTER_POS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_H_CENTER_POS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LDC_V_CENTER_POS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_V_CENTER_POS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LDC_RECTIFY_CR.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_RECTIFY_CR: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_LDC_RECTIFY_CZ.u32;
    ISP_PRINTF_FUNC("ISP_CORE_LDC_RECTIFY_CZ: 0x%08x\n", stData);
    //RAM
    stData = pstRegs->ISP_CORE_RAM_WR_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RAM_WR_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RAM_RD_STATUS.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RAM_RD_STATUS: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_RAM_READ_LOCK.u32;
    ISP_PRINTF_FUNC("ISP_CORE_RAM_READ_LOCK: 0x%08x\n", stData);
    //AF
    stData = pstRegs->ISP_CORE_AF_CTL.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_STAT_WIN_H_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_STAT_WIN_H_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_STAT_WIN_V_START.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_STAT_WIN_V_START: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_STAT_WIN_H_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_STAT_WIN_H_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_STAT_WIN_V_END.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_STAT_WIN_V_END: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_MID_FRQ_DATA.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_MID_FRQ_DATA: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_HIGH_FRQ_DATA.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_HIGH_FRQ_DATA: 0x%08x\n", stData);

    stData = pstRegs->ISP_CORE_AF_STAT_PIXEL_NUM.u32;
    ISP_PRINTF_FUNC("ISP_CORE_AF_STAT_PIXEL_NUM: 0x%08x\n", stData);

    ISP_PRINTF_FUNC("read ISP_CORE regs end!\n");

    #endif 
    return 0;
}
