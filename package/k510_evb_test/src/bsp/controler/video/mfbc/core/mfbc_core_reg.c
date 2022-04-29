/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mfbc_core_reg.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : mfbc driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
//#include "video/mfbc/mfbc.h"
#include "video/isp_com.h"
#include "video/mfbc/core/mfbc_core_reg.h"

int MFBC_CORE_DRV_SET_InputSize(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_INPUT_SIZE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_InputSize: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_OutFormat(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_OUT_FORMAT.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_OutFormat: 0x%08x\n", uData);
    #endif
    return 0;
}
/*Y*/
int MFBC_CORE_DRV_SET_YDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_DATA_BASE_ADDR_0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YDataBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_DATA_BASE_ADDR_1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YDataBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_DATA_LINE_STRIDE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_DATA_WR_BLENGTH.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}
/*Y HEAD*/
int MFBC_CORE_DRV_SET_YHeadDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_HEAD_DATA_BASE_ADDR_0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YHeadDataBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YHeadDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_HEAD_DATA_BASE_ADDR_1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YHeadDataBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YHeadDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_HEAD_DATA_LINE_STRIDE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YHeadDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_YHeadDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_Y_HEAD_DATA_WR_BLENGTH.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_YHeadDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}
/*UV*/
int MFBC_CORE_DRV_SET_UVDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_DATA_BASE_ADDR_0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVDataBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_DATA_BASE_ADDR_1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVDataBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_DATA_LINE_STRIDE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_DATA_WR_BLENGTH.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}
/*UV HEAD*/
int MFBC_CORE_DRV_SET_UVHeadDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_HEAD_DATA_BASE_ADDR_0.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVHeadDataBase0: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVHeadDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_HEAD_DATA_BASE_ADDR_1.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVHeadDataBase1: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVHeadDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_HEAD_DATA_LINE_STRIDE.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVHeadDataLineStride: 0x%08x\n", uData);
    #endif
    return 0;
}

int MFBC_CORE_DRV_SET_UVHeadDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData)
{
    MFBC_CHECK_POINTER(pstRegs);

    pstRegs->MFBC_UV_HEAD_DATA_WR_BLENGTH.u32 = uData;
    #if MFBC_DEBUG_OPEN
        MFBC_PRINTF_FUNC("MFBC_CORE_DRV_SET_UVHeadDataWrBlen: 0x%08x\n", uData);
    #endif
    return 0;
}
//debug
int MFBC_CORE_DRV_GET_CoreRegsVal(S_MFBC_CORE_REGS_TYPE *pstRegs)
{
    MFBC_CHECK_POINTER(pstRegs);
    unsigned int uData;
    //
    #if MFBC_CORE_DEBUG_OPEN
    MFBC_PRINTF_FUNC("read MFBC_CORE regs start!\n");

    uData = pstRegs->MFBC_INPUT_SIZE.u32;
    MFBC_PRINTF_FUNC("MFBC_INPUT_SIZE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_OUT_FORMAT.u32;
    MFBC_PRINTF_FUNC("MFBC_OUT_FORMAT: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_DATA_BASE_ADDR_0.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_DATA_BASE_ADDR_0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_DATA_BASE_ADDR_1.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_DATA_BASE_ADDR_1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_DATA_LINE_STRIDE.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_DATA_LINE_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_DATA_WR_BLENGTH.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_DATA_WR_BLENGTH: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_HEAD_DATA_BASE_ADDR_0.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_HEAD_DATA_BASE_ADDR_0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_HEAD_DATA_BASE_ADDR_1.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_HEAD_DATA_BASE_ADDR_1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_HEAD_DATA_LINE_STRIDE.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_HEAD_DATA_LINE_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_Y_HEAD_DATA_WR_BLENGTH.u32;
    MFBC_PRINTF_FUNC("MFBC_Y_HEAD_DATA_WR_BLENGTH: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_DATA_BASE_ADDR_0.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_DATA_BASE_ADDR_0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_DATA_BASE_ADDR_1.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_DATA_BASE_ADDR_1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_DATA_LINE_STRIDE.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_DATA_LINE_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_DATA_WR_BLENGTH.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_DATA_WR_BLENGTH: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_HEAD_DATA_BASE_ADDR_0.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_HEAD_DATA_BASE_ADDR_0: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_HEAD_DATA_BASE_ADDR_1.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_HEAD_DATA_BASE_ADDR_1: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_HEAD_DATA_LINE_STRIDE.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_HEAD_DATA_LINE_STRIDE: 0x%08x\n", uData);

    uData = pstRegs->MFBC_UV_HEAD_DATA_WR_BLENGTH.u32;
    MFBC_PRINTF_FUNC("MFBC_UV_HEAD_DATA_WR_BLENGTH: 0x%08x\n", uData);

    MFBC_PRINTF_FUNC("read MFBC_CORE regs end!\n");
    #endif
    return 0;
}
