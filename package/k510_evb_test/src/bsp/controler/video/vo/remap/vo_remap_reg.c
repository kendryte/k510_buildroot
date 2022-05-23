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

//#include "video/vo/vo.h"
#include "video/isp_com.h"
#include "video/vo/remap/vo_remap_reg.h"
/*
*Area 00
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea00_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_00_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea00_0: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea00_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_00_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea00_1: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea00_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_00_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea00_0: 0x%04x\n", uData);
    #endif
    return 0;
}
/*
*Area 01
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea01_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_01_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea01_0: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea01_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_01_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea01_1: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea01_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_01_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea01_0: 0x%04x\n", uData);
    #endif
    return 0;
}
/*
*Area 02
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea02_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_02_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea02_0: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea02_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_02_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea02_1: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea02_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_02_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea02_0: 0x%04x\n", uData);
    #endif
    return 0;
}
/*
*Area 03
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea03_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_03_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea03_0: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea03_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_03_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea03_1: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea03_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_03_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea03_0: 0x%04x\n", uData);
    #endif
    return 0;
}
/*
*Area 04
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea04_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_04_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea04_0: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea04_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_04_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea04_1: 0x%04x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea04_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_04_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea04_0: 0x%04x\n", uData);
    #endif
    return 0;
}
/*
*Area 05
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea05_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_05_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea05_0: 0x%05x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea05_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_05_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea05_1: 0x%05x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea05_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_05_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea05_0: 0x%05x\n", uData);
    #endif
    return 0;
}
/*
*Area 06
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea06_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_06_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea06_0: 0x%06x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea06_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_06_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea06_1: 0x%06x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea06_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_06_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea06_0: 0x%06x\n", uData);
    #endif
    return 0;
}
/*
*Area 07
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea07_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_07_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea07_0: 0x%07x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea07_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_07_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea07_1: 0x%07x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea07_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_07_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea07_0: 0x%07x\n", uData);
    #endif
    return 0;
}
/*
*Area 08
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea08_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_08_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea08_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea08_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_08_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea08_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea08_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_08_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea08_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 09
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea09_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_09_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea09_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea09_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_09_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea09_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea09_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_09_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea09_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 10
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea10_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_10_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea10_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea10_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_10_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea10_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea10_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_10_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea10_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 11
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea11_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_11_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea11_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea11_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_11_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea11_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea11_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_11_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea11_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 12
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea12_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_12_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea12_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea12_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_12_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea12_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea12_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_12_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea12_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 13
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea13_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_13_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea13_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea13_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_13_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea13_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea13_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_13_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea13_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 14
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea14_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_14_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea14_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea14_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_14_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea14_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea14_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_14_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea14_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 15
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea15_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_15_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea15_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea15_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_15_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea15_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea15_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_15_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea15_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 16
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea16_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_16_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea16_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea16_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_16_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea16_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea16_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_16_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea16_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 17
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea17_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_17_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea17_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea17_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_17_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea17_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea17_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_17_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea17_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 18
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea18_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_18_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea18_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea18_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_18_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea18_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea18_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_18_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea18_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 19
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea19_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_19_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea19_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea19_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_19_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea19_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea19_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_19_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea19_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 20
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea20_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_20_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea20_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea20_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_20_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea20_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea20_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_20_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea20_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 21
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea21_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_21_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea21_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea21_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_21_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea21_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea21_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_21_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea21_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 22
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea22_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_22_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea22_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea22_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_22_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea22_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea22_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_22_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea22_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 23
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea23_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_23_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea23_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea23_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_23_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea23_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea23_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_23_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea23_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 24
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea24_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_24_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea24_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea24_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_24_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea24_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea24_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_24_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea24_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 25
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea25_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_25_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea25_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea25_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_25_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea25_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea25_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_25_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea25_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 26
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea26_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_26_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea26_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea26_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_26_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea26_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea26_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_26_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea26_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 27
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea27_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_27_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea27_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea27_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_27_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea27_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea27_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_27_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea27_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 28
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea28_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_28_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea28_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea28_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_28_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea28_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea28_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_28_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea28_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 29
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea29_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_29_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea29_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea29_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_29_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea29_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea29_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_29_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea29_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 30
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea30_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_30_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea30_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea30_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_30_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea30_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea30_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_30_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea30_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Area 31
*/
int VO_REMAP_DRV_SET_CtrlFillInfoArea31_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_31_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea31_0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillInfoArea31_1(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_INFO_AREA_31_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillInfoArea31_1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_REMAP_DRV_SET_CtrlFillDataArea31_0(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_DATA_AREA_31_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillDataArea31_0: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*cmd
*/
int VO_REMAP_DRV_SET_CtrlFillCmd(S_VO_REMAP_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->CTRL_FILL_CMD.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_REMAP_DRV_SET_CtrlFillCmd: 0x%08x\n", uData);
    #endif
    return 0;
}
//debug
int VO_REMAP_DRV_GET_RemapRegsVal(S_VO_REMAP_REGS_TYPE *pstRegs)
{
    VO_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if VO_REMAP_DEBUG_OPEN
    VO_PRINTF_FUNC("read VO_REMAP rotation regs start!\n");

    uData = pstRegs->CTRL_FILL_INFO_AREA_00_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_00_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_00_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_00_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_01_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_01_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_01_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_01_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_02_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_02_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_02_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_02_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_03_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_03_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_03_1.u32; 
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_03_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_04_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_04_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_04_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_04_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_05_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_05_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_05_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_05_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_06_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_06_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_06_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_06_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_07_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_07_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_07_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_07_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_08_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_08_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_08_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_08_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_09_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_09_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_09_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_09_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_10_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_10_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_10_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_10_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_11_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_11_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_11_1.u32; 
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_11_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_12_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_12_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_12_1.u32; 
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_12_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_13_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_13_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_13_1.u32; 
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_13_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_14_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_14_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_14_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_14_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_15_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_15_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_15_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_15_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_16_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_16_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_16_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_16_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_17_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_17_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_17_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_17_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_18_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_18_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_18_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_18_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_19_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_19_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_19_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_19_1: 0x%08x\n", uData);

	uData = pstRegs->CTRL_FILL_INFO_AREA_20_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_20_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_20_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_20_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_21_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_21_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_21_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_21_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_22_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_22_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_22_1.u32; 
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_22_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_23_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_23_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_23_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_23_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_24_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_24_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_24_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_24_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_25_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_25_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_25_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_25_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_26_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_26_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_26_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_26_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_27_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_27_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_27_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_27_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_28_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_28_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_28_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_28_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_29_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_29_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_29_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_29_1: 0x%08x\n", uData);

	uData = pstRegs->CTRL_FILL_INFO_AREA_30_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_30_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_30_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_30_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_31_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_31_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_INFO_AREA_31_1.u32;
    VO_PRINTF_FUNC("CTRL_FILL_INFO_AREA_31_1: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_00_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_00_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_01_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_01_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_02_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_02_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_03_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_03_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_04_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_04_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_05_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_05_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_06_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_06_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_07_0.u32;	
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_07_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_08_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_08_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_09_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_09_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_10_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_10_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_11_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_11_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_12_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_12_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_13_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_13_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_14_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_14_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_15_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_15_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_16_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_16_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_17_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_17_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_18_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_18_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_19_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_19_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_20_0.u32;    
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_20_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_21_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_21_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_22_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_22_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_23_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_23_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_24_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_24_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_25_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_25_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_26_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_26_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_27_0.u32;	
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_27_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_28_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_28_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_29_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_29_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_30_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_30_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_DATA_AREA_31_0.u32;
    VO_PRINTF_FUNC("CTRL_FILL_DATA_AREA_31_0: 0x%08x\n", uData);

    uData = pstRegs->CTRL_FILL_CMD.u32;
    VO_PRINTF_FUNC("CTRL_FILL_CMD: 0x%08x\n", uData);

    VO_PRINTF_FUNC("read VO_REMAP rotation regs end!\n");
    #endif
    return 0;
}
