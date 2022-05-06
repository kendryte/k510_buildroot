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
#include "video/isp/ds/isp_ds_reg.h"
//#include "video/isp/isp.h"

extern unsigned int  *reg_isp_2k_ds_base;
/*
* DS Control 
*/
int ISP_DS_DRV_SET_DsInputSize(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_INPUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsInputSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsInputSize(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsInputSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff00(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF00.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff00(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF00 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF00.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff01(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF01.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff01(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF01 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF01.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff02(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF02.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff02(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF02 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF02.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff03(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF03.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff03(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF03 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF03.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff03: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff10(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF10.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff10(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF10 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF10.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff11(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF11.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff11(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF11 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF11.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff12(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF12.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff12(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF12 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF12.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff13(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF13.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff13(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF13 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF13.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff13: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff20(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF20.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff20(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF20 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF20.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff21(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF21.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff21(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF21 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF21.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff22(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF22.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff22(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF22 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF22.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff23(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_RGB2YUV_COEFF23.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_DsOsdRgb2YuvCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_DsOsdRgb2YuvCoeff23(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_RGB2YUV_COEFF23 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF23.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_DsOsdRgb2YuvCoeff23: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff00(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF00.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff00(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF00 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF00.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff01(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF01.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff01(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF01 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF01.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff02(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF02.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff02(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF02 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF02.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff03(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF03.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff03(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF03 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF03.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff03: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff10(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF10.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff10(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF00 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF10.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff11(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF11.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff11(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF01 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF11.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff12(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF12.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff12(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF12 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF12.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff13(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF13.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff13(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF13 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF13.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff13: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff20(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF20.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff20(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF00 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF20.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff21(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF21.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff21(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF01 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF21.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff22(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF22.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff22(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF22 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF22.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff23(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS_OSD_YUV2RGB_COEFF23.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff23(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS_OSD_YUV2RGB_COEFF23 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF23.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DS_DRV_GET_DsOsdYuv2RgbCoeff23: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel0
*/
int ISP_DS_DRV_SET_Ds0VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_VSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0VscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_VSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_VSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0VscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_HSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0HscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_HSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_HSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0HscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_FORMAT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Format: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Format(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_FORMAT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Format: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel0 OSD0
*/
int ISP_DS_DRV_SET_Ds0Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_SET_Ds0Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}



int ISP_DS_DRV_SET_Ds0Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}



int ISP_DS_DRV_SET_Ds0Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD0_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd0YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD0_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD0_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd0YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*Output Channel0 OSD1
*/
int ISP_DS_DRV_SET_Ds0Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD1_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd1YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD1_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD1_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd1YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*Output Channel0 OSD2
*/
int ISP_DS_DRV_SET_Ds0Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds0Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds0Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS0_OSD2_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds0Osd2YRange: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_Ds0Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS0_OSD2_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS0_OSD2_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds0Osd2YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*Output Channel1
*/
int ISP_DS_DRV_SET_Ds1VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_VSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1VscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_VSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_VSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1VscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_HSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1HscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_HSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_HSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1HscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_FORMAT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Format: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Format(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_FORMAT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Format: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*Output Channel1 OSD0
*/
int ISP_DS_DRV_SET_Ds1Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD0_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd0YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD0_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD0_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd0YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel1 OSD1
*/
int ISP_DS_DRV_SET_Ds1Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD1_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd1YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD1_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD1_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd1YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel1 OSD2
*/
int ISP_DS_DRV_SET_Ds1Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds1Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS1_OSD2_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds1Osd2YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds1Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS1_OSD2_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS1_OSD2_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds1Osd2YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*Output Channel2
*/
int ISP_DS_DRV_SET_Ds2VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_VSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2VscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_DS_DRV_GET_Ds2VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_VSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_VSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2VscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_HSCALE_PARM.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2HscaleParm: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_HSCALE_PARM stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_HSCALE_PARM.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2HscaleParm: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_FORMAT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Format: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Format(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_FORMAT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Format: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel2 OSD0
*/
int ISP_DS_DRV_SET_Ds2Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD0_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd0YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD0_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD0_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd0YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel2 OSD1
*/
int ISP_DS_DRV_SET_Ds2Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1XRange: 0x%08x\n", uData);
    #endif
    return 0;
}



int ISP_DS_DRV_GET_Ds2Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD1_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd1YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD1_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD1_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd1YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*Output Channel2 OSD2
*/
int ISP_DS_DRV_SET_Ds2Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_INFO.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2Info: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_INFO stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_INFO.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2Info: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2Size: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2Size: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2BufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2BufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2AlphaBufAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_ALPHA_BUF_ADDR0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2AlphaBufAddr0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2BufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2BufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2AlphaBufAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_ALPHA_BUF_ADDR1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2AlphaBufAddr1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_DMA_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_DMA_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_DMA_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2DmaCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2Stride: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2Stride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_X_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2XRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_X_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_X_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2XRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_DS_DRV_SET_Ds2Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_DS2_OSD2_Y_RANGE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_Ds2Osd2YRange: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_DS_DRV_GET_Ds2Osd2YRange( S_ISP_DS_REGS_TYPE *pstRegs)
{
    U_ISP_DS2_OSD2_Y_RANGE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_DS2_OSD2_Y_RANGE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2YRange: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_DS_DRV_GET_DsRegsVal(S_ISP_DS_REGS_TYPE *pstRegs)
{
    ISP_CHECK_POINTER(pstRegs);
    unsigned int stData;
    #if ISP_DS_DEBUG_OPEN
    for(int i =0;i<0x368;i=i+4)  //0x49c
    {
    	printf("ISP DS REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_ds_base+i, *(volatile unsigned int *)(reg_isp_2k_ds_base+i));
    }
	#endif
	#if 0
    //
    ISP_PRINTF_FUNC("read ISP_DS regs start!\n"); 
    //
	stData = pstRegs->ISP_DS_INPUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS_INPUT_SIZE: 0x%08x\n", stData);
	//rgb2yuv
    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF00.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF00: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF01.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF01: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF02.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF02: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF03.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF03: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF10.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF10: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF11.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF11: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF12.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF12: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF13.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF13: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF20.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF20: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF21.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF21: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF22.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF22: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_RGB2YUV_COEFF23.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_RGB2YUV_COEFF23: 0x%08x\n", stData);
    //yuv2rgb
    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF00.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF00: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF01.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF01: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF02.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF02: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF03.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF03: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF10.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF10: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF11.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF11: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF12.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF12: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF13.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF13: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF20.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF20: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF21.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF21: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF22.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF22: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS_OSD_YUV2RGB_COEFF23.u32;
    ISP_PRINTF_FUNC("ISP_DS_OSD_YUV2RGB_COEFF23: 0x%08x\n", stData);
    //ds0
    stData = pstRegs->ISP_DS0_VSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DS0_VSCALE_PARM: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_HSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DS0_HSCALE_PARM: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_FORMAT.u32;
    ISP_PRINTF_FUNC("ISP_DS0_FORMAT: 0x%08x\n", stData);    
    //ds0 osd0
    stData = pstRegs->ISP_DS0_OSD0_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD0_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD0_Y_RANGE: 0x%08x\n", stData);
    //ds0 osd1
    stData = pstRegs->ISP_DS0_OSD1_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD1_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD1_Y_RANGE: 0x%08x\n", stData);
    //ds0 osd2
    stData = pstRegs->ISP_DS0_OSD2_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS0_OSD2_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS0_OSD2_Y_RANGE: 0x%08x\n", stData);
    //ds1
    stData = pstRegs->ISP_DS1_VSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DS1_VSCALE_PARM: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_HSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DS1_HSCALE_PARM: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_FORMAT.u32;
    ISP_PRINTF_FUNC("ISP_DS1_FORMAT: 0x%08x\n", stData);
    //ds1 osd0
    stData = pstRegs->ISP_DS1_OSD0_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD0_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD0_Y_RANGE: 0x%08x\n", stData);
    //ds1 osd1
    stData = pstRegs->ISP_DS1_OSD1_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD1_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD1_Y_RANGE: 0x%08x\n", stData);
    //ds1 0sd2
    stData = pstRegs->ISP_DS1_OSD2_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS1_OSD2_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS1_OSD2_Y_RANGE: 0x%08x\n", stData);

    //ds2
    stData = pstRegs->ISP_DS2_VSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DRV_GET_Ds2Osd2YRange: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_HSCALE_PARM.u32;
    ISP_PRINTF_FUNC("ISP_DS2_HSCALE_PARM: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_FORMAT.u32;
    ISP_PRINTF_FUNC("ISP_DS2_FORMAT: 0x%08x\n", stData);
    //ds2 osd0
    stData = pstRegs->ISP_DS2_OSD0_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD0_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD0_Y_RANGE: 0x%08x\n", stData);
    //ds2 osd1
    stData = pstRegs->ISP_DS2_OSD1_INFO.u32;    
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD1_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD1_Y_RANGE: 0x%08x\n", stData);
	//ds2 osd2
    stData = pstRegs->ISP_DS2_OSD2_INFO.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_INFO: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR0.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_ALPHA_BUF_ADDR0: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_ALPHA_BUF_ADDR1.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_ALPHA_BUF_ADDR1: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_DMA_CTL.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_DMA_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_X_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_X_RANGE: 0x%08x\n", stData);

    stData = pstRegs->ISP_DS2_OSD2_Y_RANGE.u32;
    ISP_PRINTF_FUNC("ISP_DS2_OSD2_Y_RANGE: 0x%08x\n", stData);
    //
    unsigned int index;
    for(index = 0;index < 256;index++)
    {
        stData = pstRegs->ISP_HSCALE_COFF_0_BASE[index];
        ISP_PRINTF_FUNC("ISP_HSCALE_COFF_0_BASE[%d]: 0x%08x\n", index,stData);

        stData = pstRegs->ISP_HSCALE_COFF_1_BASE[index];
        ISP_PRINTF_FUNC("ISP_HSCALE_COFF_1_BASE[%d]: 0x%08x\n",  index,stData);

        stData = pstRegs->ISP_HSCALE_COFF_2_BASE[index];
        ISP_PRINTF_FUNC("ISP_HSCALE_COFF_2_BASE[%d]: 0x%08x\n",  index,stData);

    }

    for(index = 0;index < 128;index++)
    {
        stData = pstRegs->ISP_VSCALE_COFF_BASE[index];
        ISP_PRINTF_FUNC("ISP_VSCALE_COFF_BASE[%d]: 0x%08x\n",  index,stData);
    }

    ISP_PRINTF_FUNC("read ISP_DS regs end!\n"); 
    #endif
    return 0;
}

