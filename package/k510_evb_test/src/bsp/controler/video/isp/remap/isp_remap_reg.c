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
//#include "video/isp/isp.h"
#include "video/isp_com.h"
#include "video/isp/remap/isp_remap_reg.h"

extern unsigned int  *reg_isp_2k_remap_base;
/*
*CONTROL INFORMATION 00
*/
int ISP_REMAP_DRV_SET_FillInfo_0_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_00_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_00: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_00(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_00_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_00_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_00: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_00(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_00_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  00
*/
int ISP_REMAP_DRV_SET_FillData_0_00( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_00_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_00: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_00(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_00_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_00: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 01
*/
int ISP_REMAP_DRV_SET_FillInfo_0_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_01_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_01: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_01(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_01_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_01_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_01: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_01(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_01_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  01
*/
int ISP_REMAP_DRV_SET_FillData_0_01( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_01_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_01: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_01(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_01_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_01: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*CONTROL INFORMATION 02
*/
int ISP_REMAP_DRV_SET_FillInfo_0_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_02_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_02: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_02(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_02_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_02_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_02: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_02(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_02_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  02
*/
int ISP_REMAP_DRV_SET_FillData_0_02( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_02_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_02: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_02(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_02_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_02: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*CONTROL INFORMATION 03
*/
int ISP_REMAP_DRV_SET_FillInfo_0_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_03_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_03: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_03(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_03_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_03: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_03_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_03: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_03(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_03_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_03: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  03
*/
int ISP_REMAP_DRV_SET_FillData_0_03( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_03_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_03: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_03(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_03_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_03: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*CONTROL INFORMATION 04
*/
int ISP_REMAP_DRV_SET_FillInfo_0_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_04_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_04: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_04(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_04_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_04: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_04_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_04: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_04(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_04_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_04: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  04
*/
int ISP_REMAP_DRV_SET_FillData_0_04( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_04_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_04: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_04(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_04_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_04: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 05
*/
int ISP_REMAP_DRV_SET_FillInfo_0_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_05_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_05: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_05(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_05_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_05: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_05_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_05: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_05(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_05_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_05: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  05
*/
int ISP_REMAP_DRV_SET_FillData_0_05( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_05_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_05: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_05(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_05_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_05: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

/*
*CONTROL INFORMATION 06
*/
int ISP_REMAP_DRV_SET_FillInfo_0_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_06_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_06: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_06(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_06_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_06: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_06_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_06: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_06(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_06_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_06: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  06
*/
int ISP_REMAP_DRV_SET_FillData_0_06( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_06_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_06: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_06(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_06_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_06: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 07
*/
int ISP_REMAP_DRV_SET_FillInfo_0_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_07_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_07: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_07(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_07_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_07: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_07_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_07: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_07(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_07_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_07: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  07
*/
int ISP_REMAP_DRV_SET_FillData_0_07( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_07_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_07: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_07(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_07_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_07: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 08
*/
int ISP_REMAP_DRV_SET_FillInfo_0_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_08_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_08: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_08(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_08_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_08: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_08_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_08: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_08(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_08_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_08: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  08
*/
int ISP_REMAP_DRV_SET_FillData_0_08( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_08_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_08: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_08(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_08_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_08: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 09
*/
int ISP_REMAP_DRV_SET_FillInfo_0_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_09_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_09: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_09(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_09_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_09: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_09_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_09: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_09(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_09_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_09: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  09
*/
int ISP_REMAP_DRV_SET_FillData_0_09( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_09_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_09: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_09(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_09_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_09: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 10
*/
int ISP_REMAP_DRV_SET_FillInfo_0_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_10_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_10: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_10(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_10_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_10_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_10: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_10(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_10_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  10
*/
int ISP_REMAP_DRV_SET_FillData_0_10( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_10_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_10: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_10(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_10_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_10: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 11
*/
int ISP_REMAP_DRV_SET_FillInfo_0_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_11_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_11: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_11(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_11_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_11_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_11: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_11(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_11_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  11
*/
int ISP_REMAP_DRV_SET_FillData_0_11( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_11_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_11: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_11(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_11_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_11: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 12
*/
int ISP_REMAP_DRV_SET_FillInfo_0_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_12_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_12: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_12(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_12_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_12_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_12: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_12(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_12_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  12
*/
int ISP_REMAP_DRV_SET_FillData_0_12( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_12_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_12: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_12(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_12_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_12: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 13
*/
int ISP_REMAP_DRV_SET_FillInfo_0_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_13_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_13: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_13(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_13_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_13: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_13_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_13: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_13(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_13_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_13: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  13
*/
int ISP_REMAP_DRV_SET_FillData_0_13( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_13_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_13: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_13(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_13_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_13: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 14
*/
int ISP_REMAP_DRV_SET_FillInfo_0_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_14_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_14: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_14(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_14_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_14: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_14_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_14: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_14(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_14_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_14: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  14
*/
int ISP_REMAP_DRV_SET_FillData_0_14( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_14_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_14: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_14(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_14_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_14: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 15
*/
int ISP_REMAP_DRV_SET_FillInfo_0_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_15_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_15: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_15(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_15_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_15: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_15_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_15: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_15(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_15_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_15: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  15
*/
int ISP_REMAP_DRV_SET_FillData_0_15( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_15_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_15: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_15(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_15_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_15: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 16
*/
int ISP_REMAP_DRV_SET_FillInfo_0_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_16_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_16: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_16(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_16_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_16: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_16_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_16: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_16(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_16_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_16: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  16
*/
int ISP_REMAP_DRV_SET_FillData_0_16( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_16_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_16: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_16(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_16_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_16: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 17
*/
int ISP_REMAP_DRV_SET_FillInfo_0_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_17_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_17: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_17(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_17_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_17: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_17_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_17: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_17(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_17_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_17: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  17
*/
int ISP_REMAP_DRV_SET_FillData_0_17( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_17_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_17: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_17(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_17_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_17: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 18
*/
int ISP_REMAP_DRV_SET_FillInfo_0_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_18_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_18: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_18(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_18_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_18: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_18_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_18: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_18(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_18_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_18: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  18
*/
int ISP_REMAP_DRV_SET_FillData_0_18( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_18_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_18: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_18(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_18_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_18: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 19
*/
int ISP_REMAP_DRV_SET_FillInfo_0_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_19_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_19: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_19(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_19_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_19: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_19_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_19: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_19(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_19_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_19: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  19
*/
int ISP_REMAP_DRV_SET_FillData_0_19( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_19_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_19: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_19(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_19_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_19: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 20
*/
int ISP_REMAP_DRV_SET_FillInfo_0_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_20_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_20: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_20(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_20_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_20_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_20: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_20(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_20_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  20
*/
int ISP_REMAP_DRV_SET_FillData_0_20( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_20_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_20: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_20(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_20_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_20: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 21
*/
int ISP_REMAP_DRV_SET_FillInfo_0_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_21_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_21: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_21(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_21_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_21_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_21: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_21(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_21_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  21
*/
int ISP_REMAP_DRV_SET_FillData_0_21( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_21_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_21: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_21(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_21_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_21: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 22
*/
int ISP_REMAP_DRV_SET_FillInfo_0_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_22_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_22: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_22(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_22_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_22_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_22: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_22(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_22_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  22
*/
int ISP_REMAP_DRV_SET_FillData_0_22( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_22_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_22: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_22(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_22_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_22: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 23
*/
int ISP_REMAP_DRV_SET_FillInfo_0_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_23_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_23: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_23(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_23_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_23: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_23_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_23: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_23(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_23_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_23: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  23
*/
int ISP_REMAP_DRV_SET_FillData_0_23( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_23_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_23: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_23(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_23_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_23: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 24
*/
int ISP_REMAP_DRV_SET_FillInfo_0_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_24_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_24: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_24(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_24_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_24: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_24_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_24: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_24(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_24_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_24: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  24
*/
int ISP_REMAP_DRV_SET_FillData_0_24( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_24_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_24: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_24(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_24_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_24: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 25
*/
int ISP_REMAP_DRV_SET_FillInfo_0_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_25_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_25: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_25(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_25_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_25: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_25_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_25: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_25(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_25_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_25: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  25
*/
int ISP_REMAP_DRV_SET_FillData_0_25( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_25_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_25: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_25(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_25_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_25: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 26
*/
int ISP_REMAP_DRV_SET_FillInfo_0_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_26_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_26: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_26(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_26_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_26: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_26_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_26: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_26(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_26_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_26: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  26
*/
int ISP_REMAP_DRV_SET_FillData_0_26( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_26_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_26: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_26(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_26_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_26: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 27
*/
int ISP_REMAP_DRV_SET_FillInfo_0_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_27_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_27: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_27(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_27_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_27: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_27_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_27: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_27(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_27_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_27: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  27
*/
int ISP_REMAP_DRV_SET_FillData_0_27( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_27_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_27: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_27(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_27_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_27: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 28
*/
int ISP_REMAP_DRV_SET_FillInfo_0_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_28_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_28: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_28(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_28_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_28: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_28_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_28: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_28(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_28_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_28: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  28
*/
int ISP_REMAP_DRV_SET_FillData_0_28( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_28_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_28: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_28(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_28_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_28: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 29
*/
int ISP_REMAP_DRV_SET_FillInfo_0_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_29_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_29: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_29(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_29_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_29: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_29_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_29: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_29(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_29_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_29: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  29
*/
int ISP_REMAP_DRV_SET_FillData_0_29( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_29_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_29: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_29(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_29_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_29: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 30
*/
int ISP_REMAP_DRV_SET_FillInfo_0_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_30_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_30: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_30(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_30_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_30: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_30_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_30: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_30(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_30_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_30: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  30
*/
int ISP_REMAP_DRV_SET_FillData_0_30( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_30_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_30: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_30(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_30_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_30: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
*CONTROL INFORMATION 31
*/
int ISP_REMAP_DRV_SET_FillInfo_0_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_31_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_0_31: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_0_31(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_31_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_0_31: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_SET_FillInfo_1_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_INFO_AREA_31_1_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillInfo_1_31: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillInfo_1_31(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_INFO_AREA_1_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_INFO_AREA_31_1_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillInfo_1_31: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
/*
* DATA(ALPHA&YCBCR)  31
*/
int ISP_REMAP_DRV_SET_FillData_0_31( S_ISP_REMAP_REGS_TYPE*pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_FILL_DATA_AREA_31_0_CTRL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_SET_FillData_0_31: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_REMAP_DRV_GET_FillData_0_31(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    U_ISP_FILL_DATA_AREA_0_CTRL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_FILL_DATA_AREA_31_0_CTRL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_REMAP_DRV_GET_FillData_0_31: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_REMAP_DRV_GET_RemapRegsVal(S_ISP_REMAP_REGS_TYPE *pstRegs)
{
    ISP_CHECK_POINTER(pstRegs);
    unsigned int stData;
    #if ISP_REMAP_DEBUG_OPEN
    for(int i =0;i<0x180;i=i+4)  //0x49c
    {
    	printf("ISP REMAP REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_remap_base+i, *(volatile unsigned int *)(reg_isp_2k_remap_base+i));
    }
	#endif
	#if 0
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs start!\n");   
    //    
	stData = pstRegs->ISP_FILL_INFO_AREA_00_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_00_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_00_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_00_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_01_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_01_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_01_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_02_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_02_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_02_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_02_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_03_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_03_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_03_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_03_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_04_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_04_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_04_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_04_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_05_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_05_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_05_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_05_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_06_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_06_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_06_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_06_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_07_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_07_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_07_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_07_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_08_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_08_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_08_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_08_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_09_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_09_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_09_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_09_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_10_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_10_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_10_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_10_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_11_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_11_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_11_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_11_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_12_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_12_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_12_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_12_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_13_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_13_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_13_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_13_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_14_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_14_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_14_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_14_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_15_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_15_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_15_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_15_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_16_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_16_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_16_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_16_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_17_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_17_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_17_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_17_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_18_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_18_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_18_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_18_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_19_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_19_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_19_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_19_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_20_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_20_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_20_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_20_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_21_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_21_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_21_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_21_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_22_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_22_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_22_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_22_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_23_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_23_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_23_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_23_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_24_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_24_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_24_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_24_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_25_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_25_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_25_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_25_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_26_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_26_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_26_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_26_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_27_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_27_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_27_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_27_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_28_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_28_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_28_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_28_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_29_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_29_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_29_1_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_29_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_30_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_30_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_30_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_30_1_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_31_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_31_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_INFO_AREA_31_1_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_INFO_AREA_31_1_CTRL: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_FILL_DATA_AREA_00_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_00_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_01_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_01_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_02_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_02_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_03_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_03_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_04_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_04_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_05_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_05_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_06_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_06_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_07_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_07_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_08_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_08_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_09_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_09_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_10_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_10_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_11_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_11_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_12_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_12_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_13_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_13_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_14_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_14_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_15_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_15_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_16_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_16_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_17_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_17_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_18_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_18_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_19_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_19_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_20_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_20_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_21_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_21_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_22_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_22_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_23_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_23_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_24_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_24_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_25_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_25_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_26_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_26_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_27_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_27_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_28_0_CTRL.u32;
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_28_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_29_0_CTRL.u32;  
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_29_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_30_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_30_0_CTRL: 0x%08x\n", stData);

    stData = pstRegs->ISP_FILL_DATA_AREA_31_0_CTRL.u32; 
    ISP_PRINTF_FUNC("ISP_FILL_DATA_AREA_31_0_CTRL: 0x%08x\n", stData);
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs end!\n");
    #endif
    return 0;
}
