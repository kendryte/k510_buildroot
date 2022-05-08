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
//#include "video/bt1120/bt1120.h"
#include <video/isp_com.h>
#include "video/bt1120/bt1120_reg.h"
/*
*
*/
int BT1120_DRV_SET_InSel(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_IN_SEL.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_InSel: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
int BT1120_DRV_SET_CtlMode(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_CTRL_MODE.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_CtlMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
unsigned int BT1120_DRV_GET_CtlMode(S_BT1120_REGS_TYPE *pstRegs)
{
    BT1120_CHECK_POINTER(pstRegs);

    unsigned int uData = 0;
    uData = pstRegs->BT_CTRL_MODE.u32;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_GET_CtlMode: 0x%08x\n", uData);
    #endif
    return uData;
}
/*
*
*/
int BT1120_DRV_SET_CtlVBit(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_CTRL_VBIT.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_CtlVBit: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
int BT1120_DRV_SET_CtlSav(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_CTRL_SAV.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_CtlSav: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
int BT1120_DRV_SET_ImgSizeTotal(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_IMAGE_SIZE_TOTAL.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_ImgSizeTotal: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
int BT1120_DRV_SET_ImgSizeActive(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_IMAGE_SIZE_ACTIVE.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_ImgSizeActive: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
int BT1120_DRV_SET_ConfigDone(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData)
{
    BT1120_CHECK_POINTER(pstRegs);

    pstRegs->BT_CONFIG_DONE.u32 = uData;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_SET_ConfigDone: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*
*/
unsigned int BT1120_DRV_GET_ConfigDone(S_BT1120_REGS_TYPE *pstRegs)
{
    BT1120_CHECK_POINTER(pstRegs);
    unsigned int uData = 0;
    uData = pstRegs->BT_CONFIG_DONE.u32;
    #if BT1120_DEBUG_OPEN
        BT1120_PRINTF_FUNC("BT1120_DRV_GET_ConfigDone: 0x%08x\n", uData);
    #endif
    return uData;
}
