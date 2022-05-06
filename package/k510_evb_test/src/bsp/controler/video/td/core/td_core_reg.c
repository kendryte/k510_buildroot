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
//#include "td/inc/td.h"
#include "video/isp_com.h"
#include "video/td/core/td_core_reg.h"

/*
*rotation
*/
int TD_CORE_DRV_SET_RotCmd(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_CMD.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotCmd: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotCtl(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotTimeOut(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_TIME_OUT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotTimeOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotImageSizeActive(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_IMAGE_SIZE_ACTIVE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotImageSizeActive: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrYSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_Y_SRC.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrYSrc: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrUSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_U_SRC.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrUSrc: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrVSrc(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_V_SRC.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrVSrc: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrYDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_Y_DES.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrYDes: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrUDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_U_DES.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrUDes: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotBaseAddrVDes(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_FRM_BASE_ADDR_V_DES.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotBaseAddrVDes: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotStrideY(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_STRIDE_Y.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotStrideY: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotStrideU(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_STRIDE_U.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotStrideU: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_RotStrideV(S_TD_ROTATION_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_ROT_STRIDE_V.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_RotStrideV: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*mix/scaler
*/
int TD_CORE_DRV_SET_SoftRstCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_SOFT_RST_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_SoftRstCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DmaSWCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DMA_SW_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DmaSWCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0Line0BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_LINE0_BD_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0Line0BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0Line1BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_LINE1_BD_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0Line1BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0Line2BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_LINE2_BD_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0Line2BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0Line3BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_LINE3_BD_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0Line3BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer4BDCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER4_BD_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer4BDCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0XZoneCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_XZONE_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0XZoneCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0YZoneCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YZONE_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0YZoneCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0XCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_XCTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0YCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_YCTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer4XCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER4_XCTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer4XCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer4YCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER4_YCTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer4YCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispHsyncCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_HSYNC_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispHsyncCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispVsyncCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_VSYNC_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispVsyncCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispEnable(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_ENABLE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispEnable: 0x%08x\n", uData);
    #endif
    return 0;
}

unsigned int TD_CORE_DRV_GET_DispEnable(S_TD_MIX_SCALER_REGS_TYPE *pstRegs)
{
    TD_CHECK_POINTER(pstRegs);
    unsigned int uData = 0;
    uData = pstRegs->TD_DISP_ENABLE.u32;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_GET_DispEnable: 0x%08x\n", uData);
    #endif
    return uData;
}

int TD_CORE_DRV_SET_DispSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_SIZE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispSize: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Layer0
*/
int TD_CORE_DRV_SET_Layer0Ctl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0Ctl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0ScaleBlenth(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_SCALE_BLENTH.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ScaleBlenth: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0ImgInDatMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_IMG_IN_DAT_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ImgInDatMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0BAddr0Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_BADDR0_Y.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0BAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0BAddr0UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_BADDR0_UV.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0BAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0ImgInPixSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_IMG_IN_PIX_SIZE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ImgInPixSize: 0x%08x\n", uData);
    #endif
    return 0;
}


int TD_CORE_DRV_SET_Layer0ImgOutPixSize(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_IMG_OUT_PIX_SIZE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ImgOutPixSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0ImgInStride(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_IMG_IN_STRIDE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ImgInStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0ImgInOffset(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_IMG_IN_OFFSET.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0ImgInOffset: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0VScaleStep(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_VSCALE_STEP.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0VScaleStep: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0VScaleST(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_VSCALE_ST.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0VScaleST: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0HScaleStep(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_HSCALE_STEP.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0HScaleStep: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Layer0HScaleST(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_HSCALE_ST.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Layer0HScaleST: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_BaseMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_LAYER0_BASE_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_BaseMode: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*osd0
*/
int TD_CORE_DRV_SET_Osd0Info(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD0_INFO.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0Info: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Osd0Size(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD0_SIZE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0Size: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Osd0VLUAddr0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_OSD0_VLU_ADDR0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0VLUAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Osd0ALPAddr0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_OSD0_ALP_ADDR0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0ALPAddr0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Osd0DmaCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD0_DMA_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0DmaCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_Osd0Stride(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD0_STRIDE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_Osd0Stride: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*RGB2YUV
*/
int TD_CORE_DRV_SET_OsdRGB2YUVCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff00(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF00.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff01(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF01.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff02(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF02.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff03(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF03.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff10(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF10.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff11(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF11.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff12(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF12.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff13(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF13.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff20(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF20.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff21(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF21.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff22(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF22.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_OsdRGB2YUVCoeff23(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_OSD_RGB2YUV_COEFF23.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_OsdRGB2YUVCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*YUV2RGB
*/
int TD_CORE_DRV_SET_DispYUV2RGBCtl(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_CTL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff00(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF00.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff00: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff01(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF01.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff01: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff02(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF02.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff02: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff03(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF03.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff03: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff10(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF10.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff10: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff11(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF11.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff11: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff12(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF12.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff12: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff13(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF13.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff13: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff20(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF20.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff20: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff21(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF21.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff21: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff22(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF22.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff22: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispYUV2RGBCoeff23(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_YUV2RGB_COEFF23.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispYUV2RGBCoeff23: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*mix
*/
int TD_CORE_DRV_SET_DispMixALP0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_MIX_ALP0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispMixALP0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispMixALP1(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_MIX_ALP1.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispMixALP1: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispMixSel(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_MIX_SEL.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispMixSel: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispBackGroud(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_BACK_GROUD.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispBackGroud: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*int
*/
int TD_CORE_DRV_SET_DispIRQ0(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_IRQ0.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispIRQ0: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispIRQ1(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_IRQ1.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispIRQ1: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispIRQ2(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_IRQ2.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispIRQ2: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_DispIRQ(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_DISP_IRQ.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_DispIRQ: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*WB
*/
int TD_CORE_DRV_SET_WBDmaWrEn(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_DMA_WR_EN.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBDmaWrEn: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBPixelFormatOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_PIXEL_FORMAT_OUT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBPixelFormatOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBFrmBaseOutAddr0Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_FRM_BASE_OUT_ADDR0_Y.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBFrmBaseOutAddr0Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBFrmBaseOutAddr1Y(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_FRM_BASE_OUT_ADDR1_Y.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBFrmBaseOutAddr1Y: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBFrmBaseOutAddr0UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_FRM_BASE_OUT_ADDR0_UV.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBFrmBaseOutAddr0UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBFrmBaseOutAddr1UV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_FRM_BASE_OUT_ADDR1_UV.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBFrmBaseOutAddr1UV: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBHStrideOutY(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_HSTRIDE_OUT_Y.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBHStrideOutY: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBHStrideOutUV(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_HSTRIDE_OUT_UV.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBHStrideOutUV: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBFrmBufSizeOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_FRM_BUF_SIZE_OUT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBFrmBufSizeOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBVSizeActiveOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_V_SIZE_ACTIVE_OUT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBVSizeActiveOut: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBHSizeActiveOut(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_H_SIZE_ACTIVE_OUT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBHSizeActiveOut: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Ch0
*/
int TD_CORE_DRV_SET_WBCh0DmaMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH0_DMA_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh0DmaMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh0ErrUnit(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH0_ERR_UNIT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh0ErrUnit: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh0ErrTH(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH0_ERR_TH.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh0ErrTH: 0x%08x\n", uData);
    #endif
    return 0;
}


int TD_CORE_DRV_SET_WBCh0InfoClr(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH0_INFO_CLR.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh0InfoClr: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh0RstReq(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH0_RST_REQ.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh0RstReq: 0x%08x\n", uData);
    #endif
    return 0;
}
/*
*Ch1
*/
int TD_CORE_DRV_SET_WBCh1DmaMode(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH1_DMA_MODE.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh1DmaMode: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh1ErrUnit(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH1_ERR_UNIT.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh1ErrUnit: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh1ErrTH(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH1_ERR_TH.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh1ErrTH: 0x%08x\n", uData);
    #endif
    return 0;
}


int TD_CORE_DRV_SET_WBCh1InfoClr(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH1_INFO_CLR.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh1InfoClr: 0x%08x\n", uData);
    #endif
    return 0;
}

int TD_CORE_DRV_SET_WBCh1RstReq(S_TD_MIX_SCALER_REGS_TYPE *pstRegs, unsigned int uData)
{
    TD_CHECK_POINTER(pstRegs);

    pstRegs->TD_WB_CH1_RST_REQ.u32 = uData;
    #if TD_DEBUG_OPEN
        TD_PRINTF_FUNC("TD_CORE_DRV_SET_WBCh1RstReq: 0x%08x\n", uData);
    #endif
    return 0;
}
//debug
int TD_CORE_DRV_GET_RotationRegsVal(S_TD_ROTATION_REGS_TYPE *pstRegs)
{
    TD_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if TD_CORE_DEBUG_OPEN
    TD_PRINTF_FUNC("read TD_CORE rotation regs start!\n");

    uData = pstRegs->TD_ROT_CMD.u32;
    TD_PRINTF_FUNC("TD_ROT_CMD: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_CTL.u32;    
    TD_PRINTF_FUNC("TD_ROT_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_TIME_OUT.u32;
    TD_PRINTF_FUNC("TD_ROT_TIME_OUT: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_IMAGE_SIZE_ACTIVE.u32;
    TD_PRINTF_FUNC("TD_ROT_IMAGE_SIZE_ACTIVE: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_Y_SRC.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_Y_SRC: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_U_SRC.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_U_SRC: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_V_SRC.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_V_SRC: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_Y_DES.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_Y_DES: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_U_DES.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_U_DES: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_FRM_BASE_ADDR_V_DES.u32;
    TD_PRINTF_FUNC("TD_ROT_FRM_BASE_ADDR_V_DES: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_STRIDE_Y.u32;
    TD_PRINTF_FUNC("TD_ROT_STRIDE_Y: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_STRIDE_U.u32;
    TD_PRINTF_FUNC("TD_ROT_STRIDE_U: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_STRIDE_V.u32;
    TD_PRINTF_FUNC("TD_ROT_STRIDE_V: 0x%08x\n", uData);

    uData = pstRegs->TD_ROT_STS.u32;
    TD_PRINTF_FUNC("TD_ROT_STS: 0x%08x\n", uData);

    TD_PRINTF_FUNC("read TD_CORE rotation regs end!\n");
    #endif
    return 0;
}

int TD_CORE_DRV_GET_MixScalerRegsVal(S_TD_MIX_SCALER_REGS_TYPE *pstRegs)
{
    TD_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if TD_CORE_DEBUG_OPEN
    TD_PRINTF_FUNC("read TD_CORE mix scaler regs start!\n");

    uData = pstRegs->TD_SOFT_RST_CTL.u32;
    TD_PRINTF_FUNC("TD_SOFT_RST_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DMA_SW_CTL.u32;
    TD_PRINTF_FUNC("TD_DMA_SW_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_LINE0_BD_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_LINE0_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_LINE1_BD_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_LINE1_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_LINE2_BD_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_LINE2_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_LINE3_BD_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_LINE3_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER4_BD_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER4_BD_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_XZONE_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_XZONE_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YZONE_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_YZONE_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_XCTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_XCTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_YCTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_YCTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER4_XCTL.u32;
    TD_PRINTF_FUNC("TD_LAYER4_XCTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER4_YCTL.u32;
    TD_PRINTF_FUNC("TD_LAYER4_YCTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_HSYNC_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_HSYNC_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_VSYNC_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_VSYNC_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_ENABLE.u32;
    TD_PRINTF_FUNC("TD_DISP_ENABLE: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_SIZE.u32;
    TD_PRINTF_FUNC("TD_DISP_SIZE: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_CTL.u32;
    TD_PRINTF_FUNC("TD_LAYER0_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_SCALE_BLENTH.u32;
    TD_PRINTF_FUNC("TD_LAYER0_SCALE_BLENTH: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_IMG_IN_DAT_MODE.u32;
    TD_PRINTF_FUNC("TD_LAYER0_IMG_IN_DAT_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_BADDR0_Y.u32;
    TD_PRINTF_FUNC("TD_LAYER0_BADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_BADDR0_UV.u32;
    TD_PRINTF_FUNC("TD_LAYER0_BADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_IMG_IN_PIX_SIZE.u32;
    TD_PRINTF_FUNC("TD_LAYER0_IMG_IN_PIX_SIZE: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_IMG_OUT_PIX_SIZE.u32;
    TD_PRINTF_FUNC("TD_LAYER0_IMG_OUT_PIX_SIZE: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_IMG_IN_STRIDE.u32;
    TD_PRINTF_FUNC("TD_LAYER0_IMG_IN_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_IMG_IN_OFFSET.u32;
    TD_PRINTF_FUNC("TD_LAYER0_IMG_IN_OFFSET: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_VSCALE_STEP.u32;    
    TD_PRINTF_FUNC("TD_LAYER0_VSCALE_STEP: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_VSCALE_ST.u32;
    TD_PRINTF_FUNC("TD_LAYER0_VSCALE_ST: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_HSCALE_STEP.u32;
    TD_PRINTF_FUNC("TD_LAYER0_HSCALE_STEP: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_HSCALE_ST.u32;
    TD_PRINTF_FUNC("TD_LAYER0_HSCALE_ST: 0x%08x\n", uData);

    uData = pstRegs->TD_LAYER0_BASE_MODE.u32;
    TD_PRINTF_FUNC("TD_LAYER0_BASE_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD0_INFO.u32;
    TD_PRINTF_FUNC("TD_OSD0_INFO: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD0_SIZE.u32;
    TD_PRINTF_FUNC("TD_OSD0_SIZE: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_OSD0_VLU_ADDR0.u32;
    TD_PRINTF_FUNC("TD_DISP_OSD0_VLU_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_OSD0_ALP_ADDR0.u32;
    TD_PRINTF_FUNC("TD_DISP_OSD0_ALP_ADDR0: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD0_DMA_CTL.u32;
    TD_PRINTF_FUNC("TD_OSD0_DMA_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD0_STRIDE.u32;
    TD_PRINTF_FUNC("TD_OSD0_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_CTL.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF00.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF00: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF01.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF01: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF02.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF02: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF03.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF03: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF10.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF10: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF11.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF11: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF12.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF12: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF13.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF13: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF20.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF20: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF21.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF21: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF22.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF22: 0x%08x\n", uData);

    uData = pstRegs->TD_OSD_RGB2YUV_COEFF23.u32;
    TD_PRINTF_FUNC("TD_OSD_RGB2YUV_COEFF23: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_CTL.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_CTL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF00.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF00: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF01.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF01: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF02.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF02: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF03.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF03: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF10.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF10: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF11.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF11: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF12.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF12: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF13.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF13: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF20.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF20: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF21.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF21: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF22.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF22: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_YUV2RGB_COEFF23.u32;
    TD_PRINTF_FUNC("TD_DISP_YUV2RGB_COEFF23: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_MIX_ALP0.u32;
    TD_PRINTF_FUNC("TD_DISP_MIX_ALP0: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_MIX_ALP1.u32;
    TD_PRINTF_FUNC("TD_DISP_MIX_ALP1: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_MIX_SEL.u32;
    TD_PRINTF_FUNC("TD_DISP_MIX_SEL: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_BACK_GROUD.u32;
    TD_PRINTF_FUNC("TD_DISP_BACK_GROUD: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_IRQ0.u32;
    TD_PRINTF_FUNC("TD_DISP_IRQ0: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_IRQ1.u32;
    TD_PRINTF_FUNC("TD_DISP_IRQ1: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_IRQ2.u32;
    TD_PRINTF_FUNC("TD_DISP_IRQ2: 0x%08x\n", uData);

    uData = pstRegs->TD_DISP_IRQ.u32;
    TD_PRINTF_FUNC("TD_DISP_IRQ: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_DMA_WR_EN.u32;
    TD_PRINTF_FUNC("TD_WB_DMA_WR_EN: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_MODE.u32;
    TD_PRINTF_FUNC("TD_WB_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_PIXEL_FORMAT_OUT.u32;
    TD_PRINTF_FUNC("TD_WB_PIXEL_FORMAT_OUT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_FRM_BASE_OUT_ADDR0_Y.u32;
    TD_PRINTF_FUNC("TD_WB_FRM_BASE_OUT_ADDR0_Y: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_FRM_BASE_OUT_ADDR1_Y.u32;
    TD_PRINTF_FUNC("TD_WB_FRM_BASE_OUT_ADDR1_Y: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_FRM_BASE_OUT_ADDR0_UV.u32;
    TD_PRINTF_FUNC("TD_WB_FRM_BASE_OUT_ADDR0_UV: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_FRM_BASE_OUT_ADDR1_UV.u32;
    TD_PRINTF_FUNC("TD_WB_FRM_BASE_OUT_ADDR1_UV: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_HSTRIDE_OUT_Y.u32;
    TD_PRINTF_FUNC("TD_WB_HSTRIDE_OUT_Y: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_HSTRIDE_OUT_UV.u32;    
    TD_PRINTF_FUNC("TD_WB_HSTRIDE_OUT_UV: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_FRM_BUF_SIZE_OUT.u32;
    TD_PRINTF_FUNC("TD_WB_FRM_BUF_SIZE_OUT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_V_SIZE_ACTIVE_OUT.u32;
    TD_PRINTF_FUNC("TD_WB_V_SIZE_ACTIVE_OUT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_H_SIZE_ACTIVE_OUT.u32;
    TD_PRINTF_FUNC("TD_WB_H_SIZE_ACTIVE_OUT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH0_DMA_MODE.u32;
    TD_PRINTF_FUNC("TD_WB_CH0_DMA_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH0_ERR_UNIT.u32;
    TD_PRINTF_FUNC("TD_WB_CH0_ERR_UNIT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH0_ERR_TH.u32;
    TD_PRINTF_FUNC("TD_WB_CH0_ERR_TH: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH0_INFO_CLR.u32;
    TD_PRINTF_FUNC("TD_WB_CH0_INFO_CLR: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH0_RST_REQ.u32;
    TD_PRINTF_FUNC("TD_WB_CH0_RST_REQ: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH1_DMA_MODE.u32;
    TD_PRINTF_FUNC("TD_WB_CH1_DMA_MODE: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH1_ERR_UNIT.u32;
    TD_PRINTF_FUNC("TD_WB_CH1_ERR_UNIT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH1_ERR_TH.u32;
    TD_PRINTF_FUNC("TD_WB_CH1_ERR_TH: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH1_INFO_CLR.u32;
    TD_PRINTF_FUNC("TD_WB_CH1_INFO_CLR: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_CH1_RST_REQ.u32;
    TD_PRINTF_FUNC("TD_WB_CH1_RST_REQ: 0x%08x\n", uData);
    
    uData = pstRegs->TD_WB_Y_OUT_IDLE.u32;
    TD_PRINTF_FUNC("TD_WB_Y_OUT_IDLE: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_UV_OUT_IDLE.u32;
    TD_PRINTF_FUNC("TD_WB_UV_OUT_IDLE: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_Y_OUT_INT.u32;
    TD_PRINTF_FUNC("TD_WB_Y_OUT_INT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_UV_OUT_INT.u32;
    TD_PRINTF_FUNC("TD_WB_UV_OUT_INT: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_Y_OUT_FUNC0.u32;
    TD_PRINTF_FUNC("TD_WB_Y_OUT_FUNC0: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_Y_OUT_FUNC1.u32;
    TD_PRINTF_FUNC("TD_WB_Y_OUT_FUNC1: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_UV_OUT_FUNC0.u32;
    TD_PRINTF_FUNC("TD_WB_UV_OUT_FUNC0: 0x%08x\n", uData);

    uData = pstRegs->TD_WB_UV_OUT_FUNC1.u32;
    TD_PRINTF_FUNC("TD_WB_UV_OUT_FUNC1: 0x%08x\n", uData); 

    TD_PRINTF_FUNC("read TD_CORE mix scaler regs end!\n");
    #endif
    return 0;
}
