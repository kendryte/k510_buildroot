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
#include "video/isp_3d/core/isp_3d_core_reg.h"

int TOF_CORE_DRV_SET_CoreItcCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcHeight(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_HEIGHT.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcHeight: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcHeight(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_HEIGHT stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_HEIGHT.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcWidth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_WIDTH.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcWidth: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcWidth(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_WIDTH stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_WIDTH.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcVStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_VSTART.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcVStart(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_VSTART stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_VSTART.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcHStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_HSTART.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcHStart(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_HSTART stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_HSTART.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcActiveWidth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_ACTIVE_WIDTH.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcActiveWidth: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcActiveWidth(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_ACTIVE_WIDTH stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_ACTIVE_WIDTH.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcActiveWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcActiveHeight(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_ACTIVE_HEIGHT.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcActiveHeight: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcActiveHeight(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_ACTIVE_HEIGHT stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_ACTIVE_HEIGHT.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcActiveHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreItcActiveStartLine(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_ITC_ACTIVE_START_LINE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreItcActiveStartLine: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreItcActiveStartLine(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_ITC_ACTIVE_START_LINE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_ITC_ACTIVE_START_LINE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreItcActiveStartLine: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreSensorSel(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_SENSOR_SEL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreSensorSel: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreSensorSel(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_SENSOR_SEL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_SENSOR_SEL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreSensorSel: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreGenCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_GEN_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreGenCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreGenCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_GEN_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_GEN_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreGenCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_CORE_DRV_SET_CoreGrayTHCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_GRAY_TH.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_CORE_DRV_SET_CoreGrayTHCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreGrayTHCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_GEN_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_GRAY_TH.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_CORE_DRV_GET_CoreGrayTHCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_CORE_DRV_SET_CoreAeCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeWinHStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_WIN_HSTART.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeWinHStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeWinHStart(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_WIN_HSTART stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_WIN_HSTART.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeWinHStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeWinVStart(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_WIN_VSTART.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeWinVStart: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeWinVStart(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_WIN_VSTART stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_WIN_VSTART.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeWinVStart: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeWinHEnd(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_WIN_H_END.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeWinHEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeWinHEnd(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_WIN_H_END stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_WIN_H_END.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeWinHEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeWinVEnd(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_WIN_V_END.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeWinVEnd: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeWinVEnd(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_WIN_V_END stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_WIN_V_END.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeWinVEnd: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeTarBright(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_TAR_BRIGHT.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeTarBright: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeTarBright(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_TAR_BRIGHT stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_TAR_BRIGHT.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeTarBright: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeTarBrightRange(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_TAR_BRIGHT_RANGE.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeTarBrightRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeTarBrightRange(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_TAR_BRIGHT_RANGE stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_TAR_BRIGHT_RANGE.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeTarBrightRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeExTime(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_EX_TIME.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeExTime: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeExTime(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_EX_TIME stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_EX_TIME.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeExTime: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeAgc(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_AGC.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeAgc: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeAgc(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_AGC stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_AGC.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeAgc: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeAdFreq(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_AD_FREQ.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeAdFreq: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeAdFreq(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_AD_FREQ stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_AD_FREQ.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeAdFreq: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeAdStepMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_AD_STEP_MAX.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeAdStepMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeAdStepMax(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_AD_STEP_MAX stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_AD_STEP_MAX.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeAdStepMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeExValueMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_EX_VALUE_MAX.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeExValueMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeExValueMax(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_EX_VALUE_MAX stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_EX_VALUE_MAX.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeExValueMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeExValueMid(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_EX_VALUE_MID.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeExValueMid: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeExValueMid(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_EX_VALUE_MID stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_EX_VALUE_MID.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeExValueMid: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeExValueMin(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_EX_VALUE_MIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeExValueMin: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeExValueMin(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_EX_VALUE_MIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_EX_VALUE_MIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeExValueMin: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeGainMax(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_GAIN_MAX.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeGainMax: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeGainMax(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_GAIN_MAX stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_GAIN_MAX.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeGainMax: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeGainMid(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_GAIN_MID.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeGainMid: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeGainMid(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_GAIN_MID stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_GAIN_MID.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeGainMid: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeGainMin(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_GAIN_MIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeGainMin: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeGainMin(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_GAIN_MIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_GAIN_MIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeGainMin: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeValueReady(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_VALUE_READY.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeValueReady: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeValueReady(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_VALUE_READY stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_VALUE_READY.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeValueReady: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeLongCurEx(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_LONG_CUR_EX.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeLongCurEx: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeLongCurEx(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_LONG_CUR_EX stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_LONG_CUR_EX.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeLongCurEx: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeShortCurEx(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_SHORT_CUR_EX.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeShortCurEx: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeShortCurEx(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_SHORT_CUR_EX stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_SHORT_CUR_EX.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeShortCurEx: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeCurDigitalGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_CUR_DIGITAL_GAIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeCurDigitalGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeCurDigitalGain(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_CUR_DIGITAL_GAIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_CUR_DIGITAL_GAIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeCurDigitalGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeCurAveBrightness(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_CUR_AVE_BRIGHTNESS.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeCurAveBrightness: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeCurAveBrightness(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_CUR_AVE_BRIGHTNESS stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_CUR_AVE_BRIGHTNESS.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeCurAveBrightness: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeExStatus(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_EX_STATUS.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeExStatus: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeExStatus(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_EX_STATUS stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_EX_STATUS.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeExStatus: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAeSum(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_SUM.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAeSum: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAeSum(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_SUM stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_SUM.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAeSum: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreAePixelSum(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_AE_PIXEL_SUM.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreAePixelSum: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreAePixelSum(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_AE_PIXEL_SUM stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_AE_PIXEL_SUM.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreAePixelSum: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_Core2DnrCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_2DNR_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_Core2DnrCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_Core2DnrCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_2DNR_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_2DNR_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_Core2DnrCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_Core2DnrGray(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_2DNR_GRAY.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_Core2DnrGray: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_Core2DnrGray(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_2DNR_GRAY stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_2DNR_GRAY.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_Core2DnrGray: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_Core2DnrDepth(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_2DNR_DEPTH.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_Core2DnrDepth: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_Core2DnrDepth(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_2DNR_DEPTH stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_2DNR_DEPTH.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_Core2DnrDepth: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CorePostCtl(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_POST_CTL.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CorePostCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CorePostCtl(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_POST_CTL stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_POST_CTL.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CorePostCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreContGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_CONT_GAIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreContGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreContGain(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_CONT_GAIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_CONT_GAIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreContGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreLumaGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_LUMA_GAIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreLumaGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreLumaGain(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_LUMA_GAIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_LUMA_GAIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreLumaGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int TOF_CORE_DRV_SET_CoreSatuGain(S_TOF_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_SATU_GAIN.u32 = uData;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVSET_CoreSatuGain: 0x%08x\n", uData);
    #endif
    return 0;
}


int TOF_CORE_DRV_GET_CoreSatuGain(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    U_TOF_CORE_SATU_GAIN stData;
    TOF_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->TOF_CORE_SATU_GAIN.u32;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_DRVGET_CoreSatuGain: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int TOF_CORE_DRV_SET_CoreRamWrStatus(S_TOF_CORE_REGS_TYPE *pstRegs,unsigned int udata)
{
    TOF_CHECK_POINTER(pstRegs);

    pstRegs->TOF_CORE_RAM_WR_READY.u32 = udata;

    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_CORE_DRV_SET_CoreRamWrStatus: 0x%08x\n", udata);
    #endif
    return 0;
}

unsigned int TOF_CORE_DRV_GET_CoreRamRdDone(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    TOF_CHECK_POINTER(pstRegs);
    unsigned int  uData =0;
    uData = pstRegs->TOF_CORE_RAM_RD_DONE.u32;
    #if TOF_DEBUG_OPEN
        TOF_PRINTF_FUNC("TOF_CORE_DRV_GET_CoreRamRdDone: 0x%08x\n", uData);
    #endif
    return uData;
}
//debug
int TOF_CORE_DRV_GET_CoreRegsVal(S_TOF_CORE_REGS_TYPE *pstRegs)
{
    TOF_CHECK_POINTER(pstRegs);

    //
    #if TOF_CORE_DEBUG_OPEN
    for(int i =0;i<0x328;i=i+4)  //0x49c
    {
    	printf("ISP 3D CORE REG:Reg[0x%x]= 0x%x\n", TOF_CORE_REG_BASE+i, *(volatile unsigned int *)(TOF_CORE_REG_BASE+i));
    }

	#endif
	#if 0
    unsigned int uData;
    TOF_PRINTF_FUNC("read TOF_CORE regs start!\n");

    uData = pstRegs->TOF_CORE_ITC_CTL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_CTL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_HEIGHT.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_HEIGHT: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_WIDTH.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_WIDTH: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_VSTART.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_VSTART: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_HSTART.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_HSTART: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_ACTIVE_WIDTH.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_ACTIVE_WIDTH: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_ACTIVE_HEIGHT.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_ACTIVE_HEIGHT: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_ITC_ACTIVE_START_LINE.u32;
    TOF_PRINTF_FUNC("TOF_CORE_ITC_ACTIVE_START_LINE: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_SENSOR_SEL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_SENSOR_SEL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_GEN_CTL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_GEN_CTL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_GRAY_TH.u32;
    TOF_PRINTF_FUNC("TOF_CORE_GRAY_TH: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_CTL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_CTL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_WIN_HSTART.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_WIN_HSTART: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_WIN_VSTART.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_WIN_VSTART: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_WIN_H_END.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_WIN_H_END: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_WIN_V_END.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_WIN_V_END: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_TAR_BRIGHT.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_TAR_BRIGHT: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_TAR_BRIGHT_RANGE.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_TAR_BRIGHT_RANGE: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_EX_TIME.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_EX_TIME: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_AGC.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_AGC: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_AD_FREQ.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_AD_FREQ: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_AD_STEP_MAX.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_AD_STEP_MAX: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_EX_VALUE_MAX.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_EX_VALUE_MAX: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_EX_VALUE_MID.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_EX_VALUE_MID: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_EX_VALUE_MIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_EX_VALUE_MIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_GAIN_MAX.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_GAIN_MAX: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_GAIN_MID.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_GAIN_MID: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_GAIN_MIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_GAIN_MIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_VALUE_READY.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_VALUE_READY: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_LONG_CUR_EX.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_LONG_CUR_EX: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_SHORT_CUR_EX.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_SHORT_CUR_EX: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_CUR_DIGITAL_GAIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_CUR_DIGITAL_GAIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_CUR_AVE_BRIGHTNESS.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_CUR_AVE_BRIGHTNESS: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_EX_STATUS.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_EX_STATUS: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_SUM.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_SUM: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_AE_PIXEL_SUM.u32;
    TOF_PRINTF_FUNC("TOF_CORE_AE_PIXEL_SUM: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_2DNR_CTL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_2DNR_CTL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_2DNR_GRAY.u32;
    TOF_PRINTF_FUNC("TOF_CORE_2DNR_GRAY: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_2DNR_DEPTH.u32;
    TOF_PRINTF_FUNC("TOF_CORE_2DNR_DEPTH: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_POST_CTL.u32;
    TOF_PRINTF_FUNC("TOF_CORE_POST_CTL: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_CONT_GAIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_CONT_GAIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_LUMA_GAIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_LUMA_GAIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_SATU_GAIN.u32;
    TOF_PRINTF_FUNC("TOF_CORE_SATU_GAIN: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_RAM_WR_STATUS.u32;
    TOF_PRINTF_FUNC("TOF_CORE_RAM_WR_STATUS: 0x%08x\n", uData);

    uData = pstRegs->TOF_CORE_RAM_RD_STATUS.u32;
    TOF_PRINTF_FUNC("TOF_CORE_RAM_RD_STATUS: 0x%08x\n", uData);

    TOF_PRINTF_FUNC("read TOF_CORE regs end!\n");
    #endif
    return 0;
}
