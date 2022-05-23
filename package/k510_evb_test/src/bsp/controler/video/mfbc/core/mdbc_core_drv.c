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
//#include "video/mfbc/mfbc.h"
#include "video/mfbc/core/mfbc_core_reg.h"
#include "video/mfbc/core/mfbc_core_drv.h"

unsigned int  *reg_mfbc_core_base;
#define MFBC_DRV_CORE_REG_CTX(pstCtx)		pstCtx = (S_MFBC_CORE_REGS_TYPE *)(reg_mfbc_core_base)
/*
*
*/
int MFBC_DRV_Core_Remap(void)
{
	reg_mfbc_core_base  		  = (unsigned int *)(0x92630100);//MFBC_CORE_BASE;

    return 0;
}
/*
*
*/
static int MFBC_DRV_SetYBuf(MFBC_CORE_Y_BUF_S *pstYBuf)
{
    MFBC_CHECK_POINTER(pstYBuf);

    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    printf("MFBC CORE ADDR1 =0x%p\n",apstMfbcCoreReg);

    U_MFBC_Y_DATA_BASE_ADDR_0 y_uData0;
    y_uData0.u32 = 0;
    y_uData0.bits.addr0 = pstYBuf->Addr0;
		MFBC_CORE_DRV_SET_YDataBase0(apstMfbcCoreReg,y_uData0.u32);

    U_MFBC_Y_DATA_BASE_ADDR_1 y_uData1;
    y_uData1.u32 = 0;
    y_uData1.bits.addr1 = pstYBuf->Addr1;
		MFBC_CORE_DRV_SET_YDataBase1(apstMfbcCoreReg,y_uData1.u32);

    U_MFBC_Y_DATA_LINE_STRIDE y_stride;
    y_stride.u32 = 0;
    y_stride.bits.stride = pstYBuf->Stride;
		MFBC_CORE_DRV_SET_YDataLineStride(apstMfbcCoreReg,y_stride.u32);

    U_MFBC_Y_DATA_WR_BLENGTH wr_blen;
    wr_blen.u32 = 0;
    wr_blen.bits.blen = pstYBuf->WrBlen;
		MFBC_CORE_DRV_SET_YDataWrBlen(apstMfbcCoreReg,wr_blen.u32);
    
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetYHeadBuf(MFBC_CORE_Y_HEAD_BUF_S *pstYHeadBuf)
{
    MFBC_CHECK_POINTER(pstYHeadBuf);

    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    U_MFBC_Y_HEAD_DATA_BASE_ADDR_0  y_head_uData0; 
    y_head_uData0.u32 = 0;
    y_head_uData0.bits.addr0 = pstYHeadBuf->Addr0;
    MFBC_CORE_DRV_SET_YHeadDataBase0(apstMfbcCoreReg,y_head_uData0.u32); 

    U_MFBC_Y_HEAD_DATA_BASE_ADDR_1  y_head_uData1;
    y_head_uData1.u32 = 0;
    y_head_uData1.bits.addr1 = pstYHeadBuf->Addr1;
		MFBC_CORE_DRV_SET_YHeadDataBase1(apstMfbcCoreReg,y_head_uData1.u32);  

    U_MFBC_Y_HEAD_DATA_LINE_STRIDE  y_head_stride;
    y_head_stride.u32 = 0;
    y_head_stride.bits.stride = pstYHeadBuf->Stride;
		MFBC_CORE_DRV_SET_YHeadDataLineStride(apstMfbcCoreReg,y_head_stride.u32);  
     
    U_MFBC_Y_HEAD_DATA_WR_BLENGTH   wr_blen;
    wr_blen.u32 = 0;
    wr_blen.bits.blen = pstYHeadBuf->WrBlen;
		MFBC_CORE_DRV_SET_YHeadDataWrBlen(apstMfbcCoreReg,wr_blen.u32);    
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetUVBuf(MFBC_CORE_UV_BUF_S *pstUVBuf)
{
    MFBC_CHECK_POINTER(pstUVBuf);

    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    U_MFBC_UV_DATA_BASE_ADDR_0  uv_addr0;
    uv_addr0.u32 =0;
    uv_addr0.bits.addr0 = pstUVBuf->Addr0;
    MFBC_CORE_DRV_SET_UVDataBase0(apstMfbcCoreReg,uv_addr0.u32);

    U_MFBC_UV_DATA_BASE_ADDR_1  uv_addr1;
    uv_addr1.u32 = 0;
    uv_addr1.bits.addr1 = pstUVBuf->Addr1;
		MFBC_CORE_DRV_SET_UVDataBase1(apstMfbcCoreReg,uv_addr1.u32);

    U_MFBC_UV_DATA_LINE_STRIDE  uv_stride;
    uv_stride.u32 = 0;      
    uv_stride.bits.stride = pstUVBuf->Stride;
		MFBC_CORE_DRV_SET_UVDataLineStride(apstMfbcCoreReg,uv_stride.u32);

    U_MFBC_UV_DATA_WR_BLENGTH wr_blen;
    wr_blen.u32 = 0;
    wr_blen.bits.blen = pstUVBuf->WrBlen;  
		MFBC_CORE_DRV_SET_UVDataWrBlen(apstMfbcCoreReg,wr_blen.u32);
    
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetUVHeadBuf(MFBC_CORE_UV_HEAD_BUF_S *pstUVHeadBuf)
{
    MFBC_CHECK_POINTER(pstUVHeadBuf);

    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    U_MFBC_UV_HEAD_DATA_BASE_ADDR_0 uv_head_addr0;
    uv_head_addr0.u32 = 0;
    uv_head_addr0.bits.addr0 = pstUVHeadBuf->Addr0;
    MFBC_CORE_DRV_SET_UVHeadDataBase0(apstMfbcCoreReg,uv_head_addr0.u32);

    U_MFBC_UV_HEAD_DATA_BASE_ADDR_1 uv_head_addr1;
    uv_head_addr1.u32 = 0;
    uv_head_addr1.bits.addr1 = pstUVHeadBuf->Addr1;
	 MFBC_CORE_DRV_SET_UVHeadDataBase1(apstMfbcCoreReg,uv_head_addr1.u32);

    U_MFBC_UV_HEAD_DATA_LINE_STRIDE uv_head_stride; 
    uv_head_stride.u32 = 0;
    uv_head_stride.bits.stride  = pstUVHeadBuf->Stride;
    MFBC_CORE_DRV_SET_UVHeadDataLineStride(apstMfbcCoreReg,uv_head_stride.u32);

    U_MFBC_UV_HEAD_DATA_WR_BLENGTH wr_beln;
    wr_beln.u32 = 0;
    wr_beln.bits.blen  = pstUVHeadBuf->WrBlen;
	MFBC_CORE_DRV_SET_UVHeadDataWrBlen(apstMfbcCoreReg,wr_beln.u32);
    
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetBuf(MFBC_CORE_BUF_S  *pstMfbcBuf)
{
    MFBC_CHECK_POINTER(pstMfbcBuf);

    MFBC_CORE_Y_BUF_S *pstYBuf = &pstMfbcBuf->stYBuf;
    MFBC_DRV_SetYBuf(pstYBuf);

    MFBC_CORE_Y_HEAD_BUF_S *pstYHeadBuf =&pstMfbcBuf->stYHeadBuf;
    MFBC_DRV_SetYHeadBuf(pstYHeadBuf);

    MFBC_CORE_UV_BUF_S *pstUVBuf = &pstMfbcBuf->stUVBuf;
    MFBC_DRV_SetUVBuf(pstUVBuf);

    MFBC_CORE_UV_HEAD_BUF_S *pstUVHeadBuf = &pstMfbcBuf->stUVHeadBuf;
    MFBC_DRV_SetUVHeadBuf(pstUVHeadBuf);
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetSize(MFBC_CORE_SIZE_S *pstSize)
{
    MFBC_CHECK_POINTER(pstSize);

    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    U_MFBC_INPUT_SIZE size_uData;
    size_uData.bits.width = pstSize->input_width - 1;
    size_uData.bits.height = pstSize->input_height - 1;    
		MFBC_CORE_DRV_SET_InputSize(apstMfbcCoreReg,size_uData.u32);
    return 0;
}
/*
*
*/
static int MFBC_DRV_SetCtl( unsigned int yuv420_en)
{
    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);

    U_MFBC_OUT_FORMAT format_uData;
    format_uData.bits.disable420 = yuv420_en;
	  MFBC_CORE_DRV_SET_OutFormat(apstMfbcCoreReg,format_uData.u32);

	return 0;
}
/*
*
*/
int MFBC_DRV_SetCore(MFBC_CORE_ATTR_S *mfbcCoreAttr)
{
    MFBC_CHECK_POINTER(mfbcCoreAttr);

    MFBC_CORE_BUF_S  *pstMfbcBuf = &mfbcCoreAttr->stMfbcBuf;
    MFBC_DRV_SetBuf(pstMfbcBuf);

    MFBC_CORE_SIZE_S *pstSize = &mfbcCoreAttr->stMfbcSize;
    MFBC_DRV_SetSize(pstSize);

    unsigned int yuv420_en = mfbcCoreAttr->yuv420_en;
    MFBC_DRV_SetCtl( yuv420_en);
    return 0;
}
/*
*DEBUG
*/
int MFBC_DRV_GetCoreRegsVal(void)
{
    S_MFBC_CORE_REGS_TYPE *apstMfbcCoreReg = NULL;
    MFBC_DRV_CORE_REG_CTX(apstMfbcCoreReg);
    printf("zhudalei:MFBC CORE ADDR =0x%p\n",apstMfbcCoreReg);
	MFBC_CORE_DRV_GET_CoreRegsVal(apstMfbcCoreReg);

	return 0;
}
