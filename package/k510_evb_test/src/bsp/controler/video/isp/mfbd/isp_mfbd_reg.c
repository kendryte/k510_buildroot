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
#include "video/isp/mfbd/isp_mfbd_reg.h"
//#include "video/isp/isp.h"


extern unsigned int  *reg_isp_2k_mfbd_base;

int ISP_MFBD_DRV_SET_MfbdCtl(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_CTL.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdCtl: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdCtl(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdCtl: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdInputSize(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_INPUT_SIZE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdInputSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdInputSize(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdInputSize: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//Y data
int ISP_MFBD_DRV_SET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//Y header
int ISP_MFBD_DRV_SET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}


int ISP_MFBD_DRV_SET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//UV data
int ISP_MFBD_DRV_SET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdUvDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//UV header
int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdUvHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdUvHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//YL data
int ISP_MFBD_DRV_SET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYlDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}
//YL header
int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadBufBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadBufBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

int ISP_MFBD_DRV_SET_MfbdYlHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    ISP_CHECK_POINTER(pstRegs);

    pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32 = uData;
    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int ISP_MFBD_DRV_GET_MfbdYlHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadLineStride: 0x%08x\n", stData.u32);
    #endif
    return stData.u32;
}

//debug
int ISP_MFBD_DRV_GET_MfbdRegsVal(S_ISP_MFBD_REGS_TYPE *pstRegs)
{

    ISP_CHECK_POINTER(pstRegs);
    unsigned int stData;
    #if ISP_MFBD_DEBUG_OPEN
    for(int i =0;i<0x68;i=i+4)  //0x49c
    {
    	printf("ISP MFBD REG:Reg[0x%x]= 0x%x\n", reg_isp_2k_mfbd_base+i, *(volatile unsigned int *)(reg_isp_2k_mfbd_base+i));
    }
	#endif
	#if 0
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs start!\n");   
    //
    stData = pstRegs->ISP_MFBD_CTL.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_CTL: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_INPUT_SIZE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_INPUT_SIZE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_DATA_BUF_BASE1: 0x%08x\n", stData);
  
    stData = pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_Y_HEAD_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_DATA_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_UV_HEAD_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_DATA_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_DATA_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_DATA_LINE_STRIDE: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_HEAD_BUF_BASE0: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_HEAD_BUF_BASE1: 0x%08x\n", stData);

    stData = pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32;
    ISP_PRINTF_FUNC("ISP_MFBD_YL_HEAD_LINE_STRIDE: 0x%08x\n", stData);
    //
    ISP_PRINTF_FUNC("read ISP_MFBC regs end!\n"); 
    #endif
    return 0; 
}

#if 0
int ISP_MFBD_DRV_SET_MfbdEn(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_CTL.u32;
    stData.bits.mfbd_en = uData;
    pstRegs->ISP_MFBD_CTL.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdEn: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdEn(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdEn: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_en;
}


int ISP_MFBD_DRV_SET_MfbdFormatCfg(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_CTL.u32;
    stData.bits.mfbd_format_cfg = uData;
    pstRegs->ISP_MFBD_CTL.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdFormatCfg: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdFormatCfg(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_CTL stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_CTL.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdFormatCfg: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_format_cfg;
}


int ISP_MFBD_DRV_SET_MfbdInputHeight(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_INPUT_SIZE.u32;
    stData.bits.mfbd_input_height = uData;
    pstRegs->ISP_MFBD_INPUT_SIZE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdInputHeight: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdInputHeight(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdInputHeight: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_input_height;
}


int ISP_MFBD_DRV_SET_MfbdInputWidth(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_INPUT_SIZE.u32;
    stData.bits.mfbd_input_width = uData;
    pstRegs->ISP_MFBD_INPUT_SIZE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdInputWidth: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdInputWidth(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_INPUT_SIZE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_INPUT_SIZE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdInputWidth: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_input_width;
}

#if 0
int ISP_MFBD_DRV_SET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32;
    stData.bits.mfbd_y_data_buf_base0 = uData;
    pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_data_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32;
    stData.bits.mfbd_y_data_buf_base1 = uData;
    pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_data_buf_base1;
}

#endif
int ISP_MFBD_DRV_SET_MfbdYDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32;
    stData.bits.mfbd_y_data_stride = uData;
    pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_data_stride;
}

#if 0
int ISP_MFBD_DRV_SET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32;
    stData.bits.mfbd_y_head_buf_base0 = uData;
    pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_head_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32;
    stData.bits.mfbd_y_head_buf_base1 = uData;
    pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_head_buf_base1;
}

#endif
int ISP_MFBD_DRV_SET_MfbdYHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbd_y_head_stride = uData;
    pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_Y_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_Y_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_y_head_stride;
}

#if 0
int ISP_MFBD_DRV_SET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32;
    stData.bits.mfbd_uv_data_buf_base0 = uData;
    pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_data_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32;
    stData.bits.mfbd_uv_data_buf_base1 = uData;
    pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_data_buf_base1;
}
#endif

int ISP_MFBD_DRV_SET_MfbdUvDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32;
    stData.bits.mfbd_uv_data_stride = uData;
    pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_data_stride;
}

#if 0
int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32;
    stData.bits.mfbd_uv_head_buf_base0 = uData;
    pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_head_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32;
    stData.bits.mfbd_uv_head_buf_base1 = uData;
    pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_head_buf_base1;
}
#endif

int ISP_MFBD_DRV_SET_MfbdUvHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbd_uv_head_stride = uData;
    pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdUvHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdUvHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_UV_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_UV_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdUvHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_uv_head_stride;
}
#if 0

int ISP_MFBD_DRV_SET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32;
    stData.bits.mfbd_yl_data_buf_base0 = uData;
    pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_data_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32;
    stData.bits.mfbd_yl_data_buf_base1 = uData;
    pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_data_buf_base1;
}

#endif
int ISP_MFBD_DRV_SET_MfbdYlDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32;
    stData.bits.mfbd_yl_data_stride = uData;
    pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlDataStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlDataStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_DATA_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_DATA_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlDataStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_data_stride;
}

#if 0
int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32;
    stData.bits.mfbd_yl_head_buf_base0 = uData;
    pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE0 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE0.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadBufBase0: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_head_buf_base0;
}


int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32;
    stData.bits.mfbd_yl_head_buf_base1 = uData;
    pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_BUF_BASE1 stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_BUF_BASE1.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadBufBase1: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_head_buf_base1;
}
#endif

int ISP_MFBD_DRV_SET_MfbdYlHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData)
{
    U_ISP_MFBD_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32;
    stData.bits.mfbd_yl_head_stride = uData;
    pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32 = stData.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_SET_MfbdYlHeadStride: 0x%08x\n", stData.u32);
    #endif
    return 0;
}


int ISP_MFBD_DRV_GET_MfbdYlHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs)
{
    U_ISP_MFBD_YL_HEAD_LINE_STRIDE stData;
    ISP_CHECK_POINTER(pstRegs);

    stData.u32 = pstRegs->ISP_MFBD_YL_HEAD_LINE_STRIDE.u32;

    #if ISP_DEBUG_OPEN
        ISP_PRINTF_FUNC("ISP_DRV_GET_MfbdYlHeadStride: 0x%08x\n", stData.u32);
    #endif
    return stData.bits.mfbd_yl_head_stride;
}
#endif



