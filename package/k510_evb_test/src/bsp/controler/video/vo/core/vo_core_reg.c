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
#include "video/vo/core/vo_core_reg.h"
/*
*WRAP
*/
int VO_CORE_DRV_SET_SoftRstCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_SOFT_RST_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaLoadCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaLoadCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LOAD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaLoadCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int VO_CORE_DRV_GET_DmaLoadCtl(S_VO_CORE_REGS_TYPE *pstRegs)
{
    VO_CHECK_POINTER(pstRegs);

    unsigned int uData = 0;
    uData = pstRegs->VO_LOAD_CTL.u32;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaLoadCtl: 0x%08x\n", uData);
    #endif
    return uData;
}

int VO_CORE_DRV_SET_DmaSwCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_SW_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaSwCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaRdCtlOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_RD_CTL_OUT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaRdCtlOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaArbMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_ARB_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaArbMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaWeightRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_WEIGHT_RD0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaWeightRD0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaWeightRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_WEIGHT_RD1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaWeightRD1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaWeightRD2(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_WEIGHT_RD2.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaWeightRD2: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaWeightRD3(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_WEIGHT_RD3.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaWeightRD3: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaPriorityRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_PRIORITY_RD_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaPriorityRD0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaPriorityRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_PRIORITY_RD_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaPriorityRD1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaIDRD0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_ID_RD_0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaIDRD0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DmaIDRD1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DMA_ID_RD_1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DmaIDRD1: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*core
*/
int VO_CORE_DRV_SET_Layer0Line0BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_LINE0_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0Line0BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0Line1BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_LINE1_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0Line1BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0Line2BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_LINE2_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0Line2BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0Line3BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_LINE3_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0Line3BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer4BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER4_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer4BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer5BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER5_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer5BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer6BDCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER6_BD_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer6BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VO_CORE_DRV_SET_Layer0XZoneCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_XZONE_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0XZoneCtl: 0x%08x\n", uData);
    #endif
    return 0;
}


int VO_CORE_DRV_SET_Layer0YZoneCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YZONE_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0YZoneCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer4XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER4_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer4XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer4YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER4_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer4YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer5XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER5_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer5XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer5YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER5_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer5YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer6XCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER6_XCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer6XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer6YCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER6_YCTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer6YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*DISP
*/
int VO_CORE_DRV_SET_DispHSyncCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_HSYNC_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispHSyncCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispHSync1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_HSYNC1_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispHSync1Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispVSync1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_VSYNC1_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispVSync1Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispHSync2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_HSYNC2_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispHSync2Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispVSync2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_VSYNC2_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispVSync2Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispEnable(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_ENABLE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispEnable: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int VO_CORE_DRV_GET_DispEnable(S_VO_CORE_REGS_TYPE *pstRegs)
{
    VO_CHECK_POINTER(pstRegs);
    U_VO_DISP_ENABLE uData;
    uData = pstRegs->VO_DISP_ENABLE;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_GET_DispEnable: 0x%08x\n", uData.u32);
    #endif
    return uData.u32;
}

int VO_CORE_DRV_SET_DispSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispSize: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*LAYER0
*/
int VO_CORE_DRV_SET_Layer0Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ScaleBLenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_SCALE_BLENTH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ScaleBLenth: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ImgInDatMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_IMG_IN_DAT_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ImgInDatMode: 0x%08x\n", uData);
    #endif
    return 0;
}


int VO_CORE_DRV_SET_Layer0BAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_BADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0BAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0BAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_BADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0BAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0BAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_BADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0BAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0BAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_BADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0BAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ImgInPix(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_IMG_IN_PIX_SZIE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ImgInPix: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ImgOutPix(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_IMG_OUT_PIX_SZIE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ImgOutPix: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_IMG_IN_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ImgInStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_IMG_IN_OFFSET.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0ImgInOffset: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*layer0 scaler
*/
int VO_CORE_DRV_SET_Layer0VScaleStep(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_VSCALE_STEP.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0VScaleStep: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0VScaleSt(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_VSCALE_ST.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0VScaleSt: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0HScaleStep(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_HSCALE_STEP.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0HScaleStep: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0HScaleSt(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_HSCALE_ST.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0HScaleSt: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0BaseMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_BASE_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0BaseMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*MFBD
*/
int VO_CORE_DRV_SET_Layer0MFBDDataAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_ADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_ADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDDataStride0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_STRIDE0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataStride0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadStride0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadStride0Y: 0x%08x\n", uData);
    #endif
    return 0;
}


int VO_CORE_DRV_SET_Layer0MFBDDataAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_ADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_ADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDDataStride1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_STRIDE1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataStride1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadStride1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadStride1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDDataAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_ADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_ADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDDataStride0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_STRIDE0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataStride0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadStride0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadStride0UV: 0x%08x\n", uData);
    #endif
    return 0;
}


int VO_CORE_DRV_SET_Layer0MFBDDataAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_ADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_ADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDDataStride1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_DATA_STRIDE1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDDataStride1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBDHeadStride1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBDHeadStride1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer0MFBD(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER0_MFBD.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer0MFBD: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*LAYER1
*/
int VO_CORE_DRV_SET_Layer1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_BADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInBAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_BADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInBAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_BADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInBAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_BADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInBAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_OFFSET.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInOffset: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_BLENTH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInBlenth: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_IMG_IN_PIX_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1ImgInPixSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer1AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER1_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer1AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*LAYER2
*/
int VO_CORE_DRV_SET_Layer2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_BADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInBAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_BADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInBAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_BADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInBAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_BADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInBAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_OFFSET.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInOffset: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_BLENTH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInBlenth: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_IMG_IN_PIX_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2ImgInPixSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer2AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER2_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer2AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}

/*
*LAYER3
*/
int VO_CORE_DRV_SET_Layer3Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInBAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_BADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInBAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInBAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_BADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInBAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInBAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_BADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInBAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInBAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_BADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInBAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInOffset(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_OFFSET.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInOffset: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInBlenth(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_BLENTH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInBlenth: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInStride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3ImgInPixSize(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_IMG_IN_PIX_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3ImgInPixSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_Layer3AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_LAYER3_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_Layer3AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}

/*
*osd0
*/
int VO_CORE_DRV_SET_OSD0Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD0_INFO.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD0Info: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD0Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD0_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD0Size: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD0VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD0_VLU_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD0VluAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD0AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD0_ALP_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD0AlpAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD0VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD0_VLU_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD0VluAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD0AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD0_ALP_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD0AlpAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD0DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD0_DMA_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD0DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD0Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD0_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD0AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD0_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD0AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*osd1
*/
int VO_CORE_DRV_SET_OSD1Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD1_INFO.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD1Info: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD1Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD1_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD1Size: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD1VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD1_VLU_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD1VluAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD1AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD1_ALP_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD1AlpAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD1VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD1_VLU_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD1VluAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD1AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD1_ALP_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD1AlpAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD1DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD1_DMA_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD1DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD1Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD1_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD1Stride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD1AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD1_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD1AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*osd2
*/
int VO_CORE_DRV_SET_OSD2Info(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD2_INFO.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD2Info: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD2Size(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD2_SIZE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD2Size: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD2VluAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD2_VLU_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD2VluAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD2AlpAddr0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD2_ALP_ADDR0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD2AlpAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD2VluAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD2_VLU_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD2VluAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispOSD2AlpAddr1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_OSD2_ALP_ADDR1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispOSD2AlpAddr1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD2DmaCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD2_DMA_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD2DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD2Stride(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD2_STRIDE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD2Stride: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSD2AddrSelMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD2_ADDR_SEL_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSD2AddrSelMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*RGB2YUV
*/
int VO_CORE_DRV_SET_OSDRGB2YUVCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int VO_CORE_DRV_GET_OSDRGB2YUVCtl(S_VO_CORE_REGS_TYPE *pstRegs)
{
    VO_CHECK_POINTER(pstRegs);
    U_VO_OSD_RGB2YUV_CTL  uData;

    uData = pstRegs->VO_OSD_RGB2YUV_CTL; 
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_GET_OSDRGB2YUVCtl: 0x%08x\n", uData.u32);
    #endif
    return uData.u32;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff00(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF00.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff01(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF01.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff02(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF02.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff03(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF03.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff10(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF10.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff11(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF11.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff12(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF12.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff13(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF13.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff20(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF20.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff21(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF21.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff22(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF22.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_OSDRGB2YUVCoeff23(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_OSD_RGB2YUV_COEFF23.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_OSDRGB2YUVCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*YUV2RGB
*/
int VO_CORE_DRV_SET_DispYUV2RGBCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff00(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF00.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff01(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF01.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff02(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF02.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff03(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF03.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff10(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF10.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff11(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF11.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff12(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF12.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff13(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF13.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff20(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF20.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff21(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF21.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff22(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF22.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispYUV2RGBCoeff23(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_YUV2RGB_COEFF23.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispYUV2RGBCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*MIX
*/
int VO_CORE_DRV_SET_DispMixEn(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_MIX_EN.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispMixEn: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispMixALP0(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_MIX_ALP0.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispMixALP0: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispMixALP1(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_MIX_ALP1.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispMixALP1: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispMixSel(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_MIX_SEL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispMixSel: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispBackGroud(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_BACK_GROUD.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispBackGroud: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispDithCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_DITH_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispDithCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispClutCtl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_CLUT_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispClutCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispIrq0Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_IRQ0_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispIrq0Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispIrq1Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_IRQ1_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispIrq1Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispIrq2Ctl(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_IRQ2_CTL.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispIrq2Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_DispIrq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_DISP_IRQ.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_DispIrq: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*WB
*/
int VO_CORE_DRV_SET_WbDmaCHEn(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_DMA_CH_EN.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbDmaCHEn: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbDmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbDmaMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbPixelFormatOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_PIXEL_FORMAT_OUT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbPixelFormatOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbFrmBaseOutAddr0Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_FRM_BASE_OUT_ADDR0_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbFrmBaseOutAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbFrmBaseOutAddr0UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_FRM_BASE_OUT_ADDR0_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbFrmBaseOutAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbFrmBaseOutAddr1Y(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_FRM_BASE_OUT_ADDR1_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbFrmBaseOutAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbFrmBaseOutAddr1UV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_FRM_BASE_OUT_ADDR1_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbFrmBaseOutAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbHStrideY(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_HSTRIDE_Y.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbHStrideY: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbHStrideUV(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_HSTRIDE_UV.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbHStrideUV: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbBufSizeOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_BUF_SIZE_OUT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbBufSizeOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbVSizeActiveOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_V_SIZE_ACTIVE_OUT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbVSizeActiveOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbHSizeActiveOut(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_H_SIZE_ACTIVE_OUT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbHSizeActiveOut: 0x%08x\n", uData);
    #endif
    return 0;
}

/*
* WB CH0
*/
int VO_CORE_DRV_SET_WbCh0DmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH0_DMA_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh0DmaMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh0ErrUnit(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH0_ERR_UNIT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh0ErrUnit: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh0ErrTh(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH0_ERR_TH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh0ErrTh: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh0InfoClr(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH0_INFO_CLR.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh0InfoClr: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh0RstReq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH0_RST_REQ.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh0RstReq: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
* WB CH1
*/
int VO_CORE_DRV_SET_WbCh1DmaMode(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH1_DMA_MODE.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh1DmaMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh1ErrUnit(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH1_ERR_UNIT.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh1ErrUnit: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh1ErrTh(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH1_ERR_TH.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh1ErrTh: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh1InfoClr(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH1_INFO_CLR.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh1InfoClr: 0x%08x\n", uData);
    #endif
    return 0;
}

int VO_CORE_DRV_SET_WbCh1RstReq(S_VO_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    VO_CHECK_POINTER(pstRegs);

    pstRegs->VO_WB_CH1_RST_REQ.u32 = uData;
    #if VO_DEBUG_OPEN
        VO_PRINTF_FUNC("VO_CORE_DRV_SET_WbCh1RstReq: 0x%08x\n", uData);
    #endif
    return 0;
}
//debug
int VO_CORE_DRV_GET_CoreRegsVal(S_VO_CORE_REGS_TYPE *pstRegs)
{
    VO_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if VO_CORE_DEBUG_OPEN
    for(int i =0;i<0x450;i=i+4)  //0x49c
    {
    	printf("VO REG:Reg[0x%x]= 0x%x\n", ISP_VO_BASE_ADDR+i, *(volatile unsigned int *)(ISP_VO_BASE_ADDR+i));
    }
	#endif

	#if 0
    VO_PRINTF_FUNC("read VO_CORE rotation regs start!\n");

    uData = pstRegs->VO_SOFT_RST_CTL.u32;
    VO_PRINTF_FUNC("VO_SOFT_RST_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LOAD_CTL.u32;
    VO_PRINTF_FUNC("VO_LOAD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_SW_CTL.u32;
    VO_PRINTF_FUNC("VO_DMA_SW_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_RD_CTL_OUT.u32;
    VO_PRINTF_FUNC("VO_DMA_RD_CTL_OUT: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_ARB_MODE.u32;
    VO_PRINTF_FUNC("VO_DMA_ARB_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_WEIGHT_RD0.u32;
    VO_PRINTF_FUNC("VO_DMA_WEIGHT_RD0: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_WEIGHT_RD1.u32;
    VO_PRINTF_FUNC("VO_DMA_WEIGHT_RD1: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_WEIGHT_RD2.u32;
    VO_PRINTF_FUNC("VO_DMA_WEIGHT_RD2: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_WEIGHT_RD3.u32;
    VO_PRINTF_FUNC("VO_DMA_WEIGHT_RD3: 0x%08x\n", uData);
    
    uData = pstRegs->VO_DMA_PRIORITY_RD_0.u32;
    VO_PRINTF_FUNC("VO_DMA_PRIORITY_RD_0: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_PRIORITY_RD_1.u32;
    VO_PRINTF_FUNC("VO_DMA_PRIORITY_RD_1: 0x%08x\n", uData);
    
    uData = pstRegs->VO_DMA_ID_RD_0.u32;
    VO_PRINTF_FUNC("VO_DMA_ID_RD_0: 0x%08x\n", uData);

    uData = pstRegs->VO_DMA_ID_RD_1.u32;
    VO_PRINTF_FUNC("VO_DMA_ID_RD_1: 0x%08x\n", uData);
    
    uData = pstRegs->VO_LAYER0_LINE0_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_LINE0_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_LINE1_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_LINE1_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_LINE2_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_LINE2_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_LINE3_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_LINE3_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER1_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER2_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER3_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER4_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER4_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER5_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER5_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER6_BD_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER6_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_XZONE_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_XZONE_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YZONE_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_YZONE_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER1_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER1_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER2_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER2_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER3_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER3_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER4_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER4_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER4_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER4_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER5_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER5_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER5_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER5_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER6_XCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER6_XCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER6_YCTL.u32;
    VO_PRINTF_FUNC("VO_LAYER6_YCTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_HSYNC_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_HSYNC_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_HSYNC1_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_HSYNC1_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_VSYNC1_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_VSYNC1_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_HSYNC2_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_HSYNC2_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_VSYNC2_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_VSYNC2_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_ENABLE.u32;
    VO_PRINTF_FUNC("VO_DISP_ENABLE: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_SIZE.u32;
    VO_PRINTF_FUNC("VO_DISP_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER0_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_SCALE_BLENTH.u32;
    VO_PRINTF_FUNC("VO_LAYER0_SCALE_BLENTH: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_IMG_IN_DAT_MODE.u32;
    VO_PRINTF_FUNC("VO_LAYER0_IMG_IN_DAT_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_BADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_BADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_BADDR0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_BADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_BADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_BADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_BADDR1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_BADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_IMG_IN_PIX_SZIE.u32;
    VO_PRINTF_FUNC("VO_LAYER0_IMG_IN_PIX_SZIE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_IMG_OUT_PIX_SZIE.u32;
    VO_PRINTF_FUNC("VO_LAYER0_IMG_OUT_PIX_SZIE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_IMG_IN_STRIDE.u32;
    VO_PRINTF_FUNC("VO_LAYER0_IMG_IN_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_IMG_IN_OFFSET.u32;
    VO_PRINTF_FUNC("VO_LAYER0_IMG_IN_OFFSET: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_VSCALE_STEP.u32;
    VO_PRINTF_FUNC("VO_LAYER0_VSCALE_STEP: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_VSCALE_ST.u32;
    VO_PRINTF_FUNC("VO_LAYER0_VSCALE_ST: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_HSCALE_STEP.u32;
    VO_PRINTF_FUNC("VO_LAYER0_HSCALE_STEP: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_HSCALE_ST.u32;
    VO_PRINTF_FUNC("VO_LAYER0_HSCALE_ST: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_BASE_MODE.u32;
    VO_PRINTF_FUNC("VO_LAYER0_BASE_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_ADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_ADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_ADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_ADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_STRIDE0_Y.u32 ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_STRIDE0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE0_Y.u32 ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_STRIDE0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_ADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_ADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_ADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_ADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_STRIDE1_Y.u32 ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_STRIDE1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE1_Y .u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_STRIDE1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_ADDR0_UV.u32  ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_ADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_ADDR0_UV.u32  ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_ADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_STRIDE0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_STRIDE0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_STRIDE0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_ADDR1_UV.u32  ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_ADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_ADDR1_UV.u32  ;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_ADDR1_UV: 0x%08x\n", uData);
    //layer1
    uData = pstRegs->VO_LAYER1_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER1_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_BADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_BADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_BADDR0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_BADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_BADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_BADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_BADDR1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_BADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_OFFSET.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_OFFSET: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_BLENTH.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_BLENTH: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_STRIDE.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_IMG_IN_PIX_SIZE.u32;
    VO_PRINTF_FUNC("VO_LAYER1_IMG_IN_PIX_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER1_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_LAYER1_ADDR_SEL_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_DATA_STRIDE1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_DATA_STRIDE1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD_HEAD_STRIDE1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD_HEAD_STRIDE1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER0_MFBD.u32;
    VO_PRINTF_FUNC("VO_LAYER0_MFBD: 0x%08x\n", uData);
    //layer2
    uData = pstRegs->VO_LAYER2_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER2_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_BADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_BADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_BADDR0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_BADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_BADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_BADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_BADDR1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_BADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_OFFSET.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_OFFSET: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_BLENTH.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_BLENTH: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_STRIDE.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_IMG_IN_PIX_SIZE.u32;
    VO_PRINTF_FUNC("VO_LAYER2_IMG_IN_PIX_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER2_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_LAYER2_ADDR_SEL_MODE: 0x%08x\n", uData);
    //
    uData = pstRegs->VO_LAYER3_CTL.u32;
    VO_PRINTF_FUNC("VO_LAYER3_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_BADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_BADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_BADDR0_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_BADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_BADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_BADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_BADDR1_UV.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_BADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_OFFSET.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_OFFSET: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_BLENTH.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_BLENTH: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_STRIDE.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_IMG_IN_PIX_SIZE.u32;
    VO_PRINTF_FUNC("VO_LAYER3_IMG_IN_PIX_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_LAYER3_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_LAYER3_ADDR_SEL_MODE: 0x%08x\n", uData);
    //osd0
    uData = pstRegs->VO_OSD0_INFO.u32;    
    VO_PRINTF_FUNC("VO_OSD0_INFO: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD0_SIZE.u32;
    VO_PRINTF_FUNC("VO_OSD0_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD0_VLU_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD0_VLU_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD0_ALP_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD0_ALP_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD0_VLU_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD0_VLU_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD0_ALP_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD0_ALP_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD0_DMA_CTL.u32;
    VO_PRINTF_FUNC("VO_OSD0_DMA_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD0_STRIDE.u32;
    VO_PRINTF_FUNC("VO_OSD0_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD0_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_OSD0_ADDR_SEL_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD1_INFO.u32;
    VO_PRINTF_FUNC("VO_OSD1_INFO: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD1_SIZE.u32;
    VO_PRINTF_FUNC("VO_OSD1_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD1_VLU_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD1_VLU_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD1_ALP_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD1_ALP_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD1_VLU_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD1_VLU_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD1_ALP_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD1_ALP_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD1_DMA_CTL.u32;
    VO_PRINTF_FUNC("VO_OSD1_DMA_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD1_STRIDE.u32;
    VO_PRINTF_FUNC("VO_OSD1_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD1_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_OSD1_ADDR_SEL_MODE: 0x%08x\n", uData);
    //osd2
    uData = pstRegs->VO_OSD2_INFO.u32;
    VO_PRINTF_FUNC("VO_OSD2_INFO: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD2_SIZE.u32;
    VO_PRINTF_FUNC("VO_OSD2_SIZE: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD2_VLU_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD2_VLU_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD2_ALP_ADDR0.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD2_ALP_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD2_VLU_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD2_VLU_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_OSD2_ALP_ADDR1.u32;
    VO_PRINTF_FUNC("VO_DISP_OSD2_ALP_ADDR1: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD2_DMA_CTL.u32;
    VO_PRINTF_FUNC("VO_OSD2_DMA_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD2_STRIDE.u32;
    VO_PRINTF_FUNC("VO_OSD2_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD2_ADDR_SEL_MODE.u32;
    VO_PRINTF_FUNC("VO_OSD2_ADDR_SEL_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_CTL.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF00.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF00: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF01.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF01: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF02.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF02: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF03.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF03: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF10.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF10: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF11.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF11: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF12.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF12: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF13.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF13: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF20.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF20: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF21.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF21: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF22.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF22: 0x%08x\n", uData);

    uData = pstRegs->VO_OSD_RGB2YUV_COEFF23.u32;
    VO_PRINTF_FUNC("VO_OSD_RGB2YUV_COEFF23: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF00.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF00: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF01.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF01: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF02.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF02: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF03.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF03: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF10.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF10: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF11.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF11: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF12.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF12: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF13.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF13: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF20.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF20: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF21.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF21: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF22.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF22: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_YUV2RGB_COEFF23.u32;
    VO_PRINTF_FUNC("VO_DISP_YUV2RGB_COEFF23: 0x%08x\n", uData);
    //mix
    uData = pstRegs->VO_DISP_MIX_EN.u32;    
    VO_PRINTF_FUNC("VO_DISP_MIX_EN: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_MIX_ALP0.u32;
    VO_PRINTF_FUNC("VO_DISP_MIX_ALP0: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_MIX_ALP1.u32;
    VO_PRINTF_FUNC("VO_DISP_MIX_ALP1: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_MIX_SEL.u32;
    VO_PRINTF_FUNC("VO_DISP_MIX_SEL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_BACK_GROUD.u32;
    VO_PRINTF_FUNC("VO_DISP_BACK_GROUD: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_DITH_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_DITH_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_CLUT_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_CLUT_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_IRQ0_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_IRQ0_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_IRQ1_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_IRQ1_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_IRQ2_CTL.u32;
    VO_PRINTF_FUNC("VO_DISP_IRQ2_CTL: 0x%08x\n", uData);

    uData = pstRegs->VO_DISP_IRQ.u32;
    VO_PRINTF_FUNC("VO_DISP_IRQ: 0x%08x\n", uData);
    //wb
    uData = pstRegs->VO_WB_DMA_CH_EN.u32;
    VO_PRINTF_FUNC("VO_WB_DMA_CH_EN: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_MODE.u32;
    VO_PRINTF_FUNC("VO_WB_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_PIXEL_FORMAT_OUT.u32;
    VO_PRINTF_FUNC("VO_WB_PIXEL_FORMAT_OUT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_FRM_BASE_OUT_ADDR0_Y.u32;
    VO_PRINTF_FUNC("VO_WB_FRM_BASE_OUT_ADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_FRM_BASE_OUT_ADDR0_UV.u32;
    VO_PRINTF_FUNC("VO_WB_FRM_BASE_OUT_ADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_FRM_BASE_OUT_ADDR1_Y.u32;
    VO_PRINTF_FUNC("VO_WB_FRM_BASE_OUT_ADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_FRM_BASE_OUT_ADDR1_UV.u32;
    VO_PRINTF_FUNC("VO_WB_FRM_BASE_OUT_ADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_HSTRIDE_Y.u32;
    VO_PRINTF_FUNC("VO_WB_HSTRIDE_Y: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_HSTRIDE_UV.u32;
    VO_PRINTF_FUNC("VO_WB_HSTRIDE_UV: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_BUF_SIZE_OUT.u32;
    VO_PRINTF_FUNC("VO_WB_BUF_SIZE_OUT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_V_SIZE_ACTIVE_OUT.u32;
    VO_PRINTF_FUNC("VO_WB_V_SIZE_ACTIVE_OUT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_H_SIZE_ACTIVE_OUT.u32;
    VO_PRINTF_FUNC("VO_WB_H_SIZE_ACTIVE_OUT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH0_DMA_MODE.u32;
    VO_PRINTF_FUNC("VO_WB_CH0_DMA_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH0_ERR_UNIT.u32;
    VO_PRINTF_FUNC("VO_WB_CH0_ERR_UNIT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH0_ERR_TH.u32;
    VO_PRINTF_FUNC("VO_WB_CH0_ERR_TH: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH0_INFO_CLR.u32; 
    VO_PRINTF_FUNC("VO_WB_CH0_INFO_CLR: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH0_RST_REQ.u32;
    VO_PRINTF_FUNC("VO_WB_CH0_RST_REQ: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH1_DMA_MODE.u32;
    VO_PRINTF_FUNC("VO_WB_CH1_DMA_MODE: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH1_ERR_UNIT.u32;
    VO_PRINTF_FUNC("VO_WB_CH1_ERR_UNIT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH1_ERR_TH.u32;
    VO_PRINTF_FUNC("VO_WB_CH1_ERR_TH: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH1_INFO_CLR.u32;
    VO_PRINTF_FUNC("VO_WB_CH1_INFO_CLR: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_CH1_RST_REQ.u32;
    VO_PRINTF_FUNC("VO_WB_CH1_RST_REQ: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_Y_OUT_IDLE.u32;
    VO_PRINTF_FUNC("VO_WB_Y_OUT_IDLE: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_UV_OUT_IDLE.u32;
    VO_PRINTF_FUNC("VO_WB_UV_OUT_IDLE: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_Y_OUT_INT.u32;
    VO_PRINTF_FUNC("VO_WB_Y_OUT_INT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_UV_OUT_INT.u32;
    VO_PRINTF_FUNC("VO_WB_UV_OUT_INT: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_Y_OUT_FUNC0.u32;
    VO_PRINTF_FUNC("VO_WB_Y_OUT_FUNC0: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_Y_OUT_FUNC1.u32;
    VO_PRINTF_FUNC("VO_WB_Y_OUT_FUNC1: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_UV_OUT_FUNC0.u32;
    VO_PRINTF_FUNC("VO_WB_UV_OUT_FUNC0: 0x%08x\n", uData);

    uData = pstRegs->VO_WB_UV_OUT_FUNC1.u32;
    VO_PRINTF_FUNC("VO_WB_UV_OUT_FUNC1: 0x%08x\n", uData);

    VO_PRINTF_FUNC("read VO_CORE rotation regs end!\n");
    #endif
    return 0;
}
