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
#include <video/isp_com.h>
#include "video/isp/mfbc/isp_mfbc_reg.h"
//#include "video/isp/isp.h"

extern unsigned int  *reg_isp_2k_mfbc_base;

int ISP_MFBC_DRV_SET_MfbcInputSize(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_INPUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcInputSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcInputSize(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcInputSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcOutFormat(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_OUT_FORMAT.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcOutFormat: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcOutFormat(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_OUT_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_OUT_FORMAT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcOutFormat: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//Y data
int ISP_MFBC_DRV_SET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//Y header
int ISP_MFBC_DRV_SET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//UV data
int ISP_MFBC_DRV_SET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//UV header
int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//YL data
int ISP_MFBC_DRV_SET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//YL header
int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBC_DRV_SET_MfbcYlHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBC_DRV_GET_MfbcYlHeadWrBlen( S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//debug
int ISP_MFBC_DRV_GET_MfbcRegsVal(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    ISP_CHECK_POINTER(pstRegs);
    unsigned int stData;
    #if ISP_MFBC_DEBUG_OPEN
    for(int i =0;i<0x70;i=i+4)  //0x49c
    {
    	printf("ISP MFBC REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_mfbc_base+i, *(volatile unsigned int *)(reg_isp_2k_mfbc_base+i));
    }
	#endif
	#if 0
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs start!\n");   
    //
    stData = pstRegs->ISP_MFBC_INPUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_INPUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_OUT_FORMAT.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_OUT_FORMAT: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_DATA_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_DATA_WR_BLEN: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_HEAD_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_Y_HEAD_WR_BLEN: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_DATA_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_DATA_WR_BLEN: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_HEAD_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_UV_HEAD_WR_BLEN: 0x%08x\n", stData);
    //
    stData = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_DATA_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32;
     ISP_PRINTF_FUNC("ISP_MFBC_YL_DATA_WR_BLEN: 0x%08x\n", stData);
	//
    stData = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_HEAD_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32;
    ISP_PRINTF_FUNC("ISP_MFBC_YL_HEAD_WR_BLEN: 0x%08x\n", stData);
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs end!\n"); 
    #endif
    return 0;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcInputHeight(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_INPUT_SIZE.u32;
    stData.bits.mfbc_input_height = uData;
    pstRegs->ISP_MFBC_INPUT_SIZE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcInputHeight: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcInputHeight(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcInputHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_input_height;
}


 int ISP_MFBC_DRV_SET_MfbcInputWidth(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_INPUT_SIZE.u32;
    stData.bits.mfbc_input_width = uData;
    pstRegs->ISP_MFBC_INPUT_SIZE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcInputWidth: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcInputWidth(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcInputWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_input_width;
}


 int ISP_MFBC_DRV_SET_MfbcOutFormatCfg(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_OUT_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_OUT_FORMAT.u32;
    stData.bits.mfbc_out_format_cfg = uData;
    pstRegs->ISP_MFBC_OUT_FORMAT.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcOutFormatCfg: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcOutFormatCfg(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_OUT_FORMAT stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_OUT_FORMAT.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcOutFormatCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_out_format_cfg;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32;
    stData.bits.mfbc_y_data_buf_base0 = uData;
    pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_data_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32;
    stData.bits.mfbc_y_data_buf_base1 = uData;
    pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_data_buf_base1;
}
#endif

 int ISP_MFBC_DRV_SET_MfbcYDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32;
    stData.bits.mfbc_y_data_stride = uData;
    pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_data_stride;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32;
    stData.bits.mfbc_y_data_wr_blen = uData;
    pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_data_wr_blen;
}


 int ISP_MFBC_DRV_SET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32;
    stData.bits.mfbc_y_head_buf_base0 = uData;
    pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_head_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32;
    stData.bits.mfbc_y_head_buf_base1 = uData;
    pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_head_buf_base1;
}
#endif

 int ISP_MFBC_DRV_SET_MfbcYHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbc_y_head_stride = uData;
    pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_head_stride;
}
#if 0

 int ISP_MFBC_DRV_SET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_Y_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32;
    stData.bits.mfbc_y_head_wr_blen = uData;
    pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_Y_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_Y_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_y_head_wr_blen;
}


 int ISP_MFBC_DRV_SET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32;
    stData.bits.mfbc_uv_data_buf_base0 = uData;
    pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_data_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32;
    stData.bits.mfbc_uv_data_buf_base1 = uData;
    pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_data_buf_base1;
}

#endif
 int ISP_MFBC_DRV_SET_MfbcUvDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32;
    stData.bits.mfbc_uv_data_stride = uData;
    pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_data_stride;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32;
    stData.bits.mfbc_uv_data_wr_blen = uData;
    pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_data_wr_blen;
}


 int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32;
    stData.bits.mfbc_uv_head_buf_base0 = uData;
    pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_head_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32;
    stData.bits.mfbc_uv_head_buf_base1 = uData;
    pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_head_buf_base1;
}
#endif

 int ISP_MFBC_DRV_SET_MfbcUvHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbc_uv_head_stride = uData;
    pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_head_stride;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_UV_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32;
    stData.bits.mfbc_uv_head_wr_blen = uData;
    pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcUvHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_UV_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_UV_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcUvHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_uv_head_wr_blen;
}


 int ISP_MFBC_DRV_SET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32;
    stData.bits.mfbc_yl_data_buf_base0 = uData;
    pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_data_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32;
    stData.bits.mfbc_yl_data_buf_base1 = uData;
    pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_data_buf_base1;
}
#endif

 int ISP_MFBC_DRV_SET_MfbcYlDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32;
    stData.bits.mfbc_yl_data_stride = uData;
    pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlDataStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_data_stride;
}

#if 0
 int ISP_MFBC_DRV_SET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32;
    stData.bits.mfbc_yl_data_wr_blen = uData;
    pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_DATA_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_DATA_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlDataWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_data_wr_blen;
}


 int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32;
    stData.bits.mfbc_yl_head_buf_base0 = uData;
    pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_head_buf_base0;
}


 int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32;
    stData.bits.mfbc_yl_head_buf_base1 = uData;
    pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_head_buf_base1;
}

#endif
 int ISP_MFBC_DRV_SET_MfbcYlHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbc_yl_head_stride = uData;
    pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlHeadStride(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_head_stride;
}
#if 0

 int ISP_MFBC_DRV_SET_MfbcYlHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBC_YL_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32;
    stData.bits.mfbc_yl_head_wr_blen = uData;
    pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbcYlHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


 int ISP_MFBC_DRV_GET_MfbcYlHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs)
{
    U_ISP_MFBC_YL_HEAD_WR_BLEN stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBC_YL_HEAD_WR_BLEN.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbcYlHeadWrBlen: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbc_yl_head_wr_blen;
}
#endif
#endif




