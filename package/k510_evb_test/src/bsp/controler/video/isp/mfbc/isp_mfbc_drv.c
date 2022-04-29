
/******************************************************************************

  Copyright (C), 2020, canaan Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_mfbc_drv.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : isp driver interface
  History       :
  1.Date        : 
    Author      :zhudalei
    Modification: Created file

******************************************************************************/
#include "video/isp_com.h"
#include "video/isp/mfbc/isp_mfbc_drv.h"
#include "video/isp/mfbc/isp_mfbc_reg.h"
//#include "video/isp/isp.h"

extern unsigned int  *reg_isp_2k_mfbc_base;
#define ISP_2K_DRV_MFBC_REG_CTX(pstCtx)		pstCtx = (S_ISP_MFBC_REGS_TYPE *)(reg_isp_2k_mfbc_base)

static int ISP_DRV_MFBC_SetYBuf(ISP_MFBC_Y_BUF_S *pstIspMfbcYBuf)
{
	ISP_CHECK_POINTER(pstIspMfbcYBuf);

	S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

    U_ISP_MFBC_Y_DATA_BUF_BASE0 stYBuf0;
    stYBuf0.u32 = 0;
	stYBuf0.bits.mfbc_y_data_buf_base0 = pstIspMfbcYBuf->mfbc_y_data_buf_base0;
	ISP_MFBC_DRV_SET_MfbcYDataBufBase0(pstRegs, stYBuf0.u32);

	U_ISP_MFBC_Y_DATA_BUF_BASE1 stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.mfbc_y_data_buf_base1 = pstIspMfbcYBuf->mfbc_y_data_buf_base1;
	ISP_MFBC_DRV_SET_MfbcYDataBufBase1(pstRegs, stYBuf1.u32);

	U_ISP_MFBC_Y_DATA_LINE_STRIDE stYStride;
	stYStride.u32 = 0;
	stYStride.bits.mfbc_y_data_stride = pstIspMfbcYBuf->mfbc_y_data_stride;
	ISP_MFBC_DRV_SET_MfbcYDataLineStride(pstRegs, stYStride.u32);

	U_ISP_MFBC_Y_DATA_WR_BLEN stYWriteBlen;
	stYWriteBlen.u32 = 0;
	stYWriteBlen.bits.mfbc_y_data_wr_blen = pstIspMfbcYBuf->mfbc_y_data_wr_blen;
	ISP_MFBC_DRV_SET_MfbcYDataWrBlen(pstRegs, stYWriteBlen.u32);

	U_ISP_MFBC_Y_HEAD_BUF_BASE0 stYHeadBuf0;
	stYHeadBuf0.u32 = 0;
	stYHeadBuf0.bits.mfbc_y_head_buf_base0 = pstIspMfbcYBuf->mfbc_y_head_buf_base0;
	ISP_MFBC_DRV_SET_MfbcYHeadBufBase0(pstRegs, stYHeadBuf0.u32);

	U_ISP_MFBC_Y_HEAD_BUF_BASE1 stYHeadBuf1;
	stYHeadBuf1.u32 = 0;
	stYHeadBuf1.bits.mfbc_y_head_buf_base1 = pstIspMfbcYBuf->mfbc_y_head_buf_base1;
    ISP_MFBC_DRV_SET_MfbcYHeadBufBase1(pstRegs, stYHeadBuf1.u32);

	U_ISP_MFBC_Y_HEAD_LINE_STRIDE stYHeadStride;
	stYHeadStride.u32 = 0;
	stYHeadStride.bits.mfbc_y_head_stride = pstIspMfbcYBuf->mfbc_y_head_stride;
	ISP_MFBC_DRV_SET_MfbcYHeadLineStride(pstRegs, stYHeadStride.u32);

	U_ISP_MFBC_Y_HEAD_WR_BLEN stYHeadWriteBlen;
	stYHeadWriteBlen.u32 = 0;
	stYHeadWriteBlen.bits.mfbc_y_head_wr_blen = pstIspMfbcYBuf->mfbc_y_head_wr_blen;
	ISP_MFBC_DRV_SET_MfbcYHeadWrBlen(pstRegs, stYHeadWriteBlen.u32);

    return 0;
}

static int ISP_DRV_MFBC_SetUVBuf(ISP_MFBC_UV_BUF_S *pstIspMfbcUVBuf)
{
	ISP_CHECK_POINTER(pstIspMfbcUVBuf);

    S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

	U_ISP_MFBC_UV_DATA_BUF_BASE0 stUvBuf0;
	stUvBuf0.u32 = 0;
	stUvBuf0.bits.mfbc_uv_data_buf_base0 = pstIspMfbcUVBuf->mfbc_uv_data_buf_base0;
	ISP_MFBC_DRV_SET_MfbcUvDataBufBase0(pstRegs, stUvBuf0.u32);

	U_ISP_MFBC_UV_DATA_BUF_BASE1 stUvBuf1;	
	stUvBuf1.u32 = 0;
	stUvBuf1.bits.mfbc_uv_data_buf_base1 = pstIspMfbcUVBuf->mfbc_uv_data_buf_base1;
	ISP_MFBC_DRV_SET_MfbcUvDataBufBase1(pstRegs, stUvBuf1.u32);

	U_ISP_MFBC_UV_DATA_LINE_STRIDE stUvStride;	
	stUvStride.u32 = 0;
	stUvStride.bits.mfbc_uv_data_stride = pstIspMfbcUVBuf->mfbc_uv_data_stride;
	ISP_MFBC_DRV_SET_MfbcUvDataLineStride(pstRegs, stUvStride.u32);

	U_ISP_MFBC_UV_DATA_WR_BLEN stUvWriteBlen;
	stUvWriteBlen.u32 = 0;
	stUvWriteBlen.bits.mfbc_uv_data_wr_blen = pstIspMfbcUVBuf->mfbc_uv_data_wr_blen;
	ISP_MFBC_DRV_SET_MfbcUvDataWrBlen(pstRegs, stUvWriteBlen.u32);

	U_ISP_MFBC_UV_HEAD_BUF_BASE0 stUvHeadBuf0;
	stUvHeadBuf0.u32 = 0;
	stUvHeadBuf0.bits.mfbc_uv_head_buf_base0 = pstIspMfbcUVBuf->mfbc_uv_head_buf_base0;
	ISP_MFBC_DRV_SET_MfbcUvHeadBufBase0(pstRegs, stUvHeadBuf0.u32);

	U_ISP_MFBC_UV_HEAD_BUF_BASE1 stUvHeadBuf1;
	stUvHeadBuf1.u32 = 0;
	stUvHeadBuf1.bits.mfbc_uv_head_buf_base1 = pstIspMfbcUVBuf->mfbc_uv_head_buf_base1;
	ISP_MFBC_DRV_SET_MfbcUvHeadBufBase1(pstRegs, stUvHeadBuf1.u32);

	U_ISP_MFBC_UV_HEAD_LINE_STRIDE stUvHeadStride;		
	stUvHeadStride.u32 = 0;
	stUvHeadStride.bits.mfbc_uv_head_stride = pstIspMfbcUVBuf->mfbc_uv_head_stride;
	ISP_MFBC_DRV_SET_MfbcUvHeadLineStride(pstRegs, stUvHeadStride.u32);

	U_ISP_MFBC_UV_HEAD_WR_BLEN stUvHeadWriteBlen;
	stUvHeadWriteBlen.u32 = 0;
	stUvHeadWriteBlen.bits.mfbc_uv_head_wr_blen = pstIspMfbcUVBuf->mfbc_uv_head_wr_blen;
	ISP_MFBC_DRV_SET_MfbcUvHeadWrBlen(pstRegs, stUvHeadWriteBlen.u32);
    return 0;
}

static int ISP_DRV_MFBC_SetYLBuf(ISP_MFBC_YL_BUF_S	*pstIspMfbcYLBuf)
{
	ISP_CHECK_POINTER(pstIspMfbcYLBuf);

	S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

	U_ISP_MFBC_YL_DATA_BUF_BASE0 stYlBuf0;
	stYlBuf0.u32 = 0;
	stYlBuf0.bits.mfbc_yl_data_buf_base0 = pstIspMfbcYLBuf->mfbc_yl_data_buf_base0;
	ISP_MFBC_DRV_SET_MfbcYlDataBufBase0(pstRegs, stYlBuf0.u32);

	U_ISP_MFBC_YL_DATA_BUF_BASE1 stYlBuf1;
	stYlBuf1.u32 = 0;
	stYlBuf1.bits.mfbc_yl_data_buf_base1 = pstIspMfbcYLBuf->mfbc_yl_data_buf_base1;
	ISP_MFBC_DRV_SET_MfbcYlDataBufBase1(pstRegs, stYlBuf1.u32);

	U_ISP_MFBC_YL_DATA_LINE_STRIDE stYlStride;
	stYlStride.u32 = 0;
	stYlStride.bits.mfbc_yl_data_stride = pstIspMfbcYLBuf->mfbc_yl_data_stride;
	ISP_MFBC_DRV_SET_MfbcYlDataLineStride(pstRegs, stYlStride.u32);

	U_ISP_MFBC_YL_DATA_WR_BLEN stYlWriteBlen;
	stYlWriteBlen.u32 = 0;
	stYlWriteBlen.bits.mfbc_yl_data_wr_blen = pstIspMfbcYLBuf->mfbc_yl_data_wr_blen;
	ISP_MFBC_DRV_SET_MfbcYlDataWrBlen(pstRegs, stYlWriteBlen.u32);

	U_ISP_MFBC_YL_HEAD_BUF_BASE0 stYlHeadBuf0;
	stYlHeadBuf0.u32 = 0;
	stYlHeadBuf0.bits.mfbc_yl_head_buf_base0 = pstIspMfbcYLBuf->mfbc_yl_head_buf_base0;
	ISP_MFBC_DRV_SET_MfbcYlHeadBufBase0(pstRegs, stYlHeadBuf0.u32);

	U_ISP_MFBC_YL_HEAD_BUF_BASE1 stYlHeadBuf1;
	stYlHeadBuf1.u32 = 0;
	stYlHeadBuf1.bits.mfbc_yl_head_buf_base1 = pstIspMfbcYLBuf->mfbc_yl_head_buf_base1;
	ISP_MFBC_DRV_SET_MfbcYlHeadBufBase1(pstRegs, stYlHeadBuf1.u32);

	U_ISP_MFBC_YL_HEAD_LINE_STRIDE stYlHeadStride;
	stYlHeadStride.u32 = 0;
	stYlHeadStride.bits.mfbc_yl_head_stride = pstIspMfbcYLBuf->mfbc_yl_head_stride;
	ISP_MFBC_DRV_SET_MfbcYlHeadLineStride(pstRegs, stYlHeadStride.u32);	

	U_ISP_MFBC_YL_HEAD_WR_BLEN stYlHeadWriteBlen;	
	stYlHeadWriteBlen.u32 = 0;
	stYlHeadWriteBlen.bits.mfbc_yl_head_wr_blen = pstIspMfbcYLBuf->mfbc_yl_head_wr_blen;
	ISP_MFBC_DRV_SET_MfbcYlHeadWrBlen(pstRegs, stYlHeadWriteBlen.u32);

    return 0;
}
/*
*
*/
static int ISP_DRV_MFBC_SetBuf(ISP_MFBC_BUF_S *pstIspMfbcBuf)
{
	ISP_CHECK_POINTER(pstIspMfbcBuf);	

    //Y daya
	ISP_MFBC_Y_BUF_S *pstIspMfbcYBuf = &pstIspMfbcBuf->stIspMfbcYBuf;
    ISP_DRV_MFBC_SetYBuf(pstIspMfbcYBuf);
    //UV data
	ISP_MFBC_UV_BUF_S *pstIspMfbcUVBuf = &pstIspMfbcBuf->stIspMfbcUVBuf;
    ISP_DRV_MFBC_SetUVBuf(pstIspMfbcUVBuf);
    //YL data
	ISP_MFBC_YL_BUF_S *pstIspMfbcYLBuf  = &pstIspMfbcBuf->stIspMfbcYLBuf;
    ISP_DRV_MFBC_SetYLBuf(pstIspMfbcYLBuf);

	return 0;	
}
/*
*
*/
static int ISP_DRV_MFBC_SetCtl(ISP_MFBC_CTL_S	*pstIspMfbcCtl)
{
	ISP_CHECK_POINTER(pstIspMfbcCtl);	

	S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

	U_ISP_MFBC_OUT_FORMAT stOutFormat;
	stOutFormat.u32 = 0;
	stOutFormat.bits.mfbc_out_format_cfg = pstIspMfbcCtl->mfbc_out_format_cfg;
	ISP_MFBC_DRV_SET_MfbcOutFormat(pstRegs, stOutFormat.u32);

	return 0;	
}
/*
*
*/
static int ISP_DRV_MFBC_SetSize(ISP_MFBC_SIZE_S *pstIspMfbcSize)
{
	ISP_CHECK_POINTER(pstIspMfbcSize);	

	S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

	U_ISP_MFBC_INPUT_SIZE stInputSize;	
	stInputSize.u32 = 0;
	stInputSize.bits.mfbc_input_height = pstIspMfbcSize->mfbc_input_height;
	stInputSize.bits.mfbc_input_width = pstIspMfbcSize->mfbc_input_width;
	ISP_MFBC_DRV_SET_MfbcInputSize(pstRegs, stInputSize.u32);

	return 0;	
}

int ISP_DRV_SetMFBC(ISP_MFBC_ATTR_S *pstMfbcAttr)
{
	ISP_CHECK_POINTER(pstMfbcAttr);
 
	ISP_MFBC_BUF_S	*pstIspMfbcBuf = &pstMfbcAttr->stIspMfbcBuf;
	ISP_DRV_MFBC_SetBuf(pstIspMfbcBuf);

	ISP_MFBC_CTL_S	*pstIspMfbcCtl = &pstMfbcAttr->stIspMfbcCtl;	
	ISP_DRV_MFBC_SetCtl(pstIspMfbcCtl);
	
	ISP_MFBC_SIZE_S *pstIspMfbcSize = &pstMfbcAttr->stIspMfbcSize;
	ISP_DRV_MFBC_SetSize(pstIspMfbcSize);
	return 0;
}

int ISP_DRV_GetMFBCRegsVal(void)
{
	S_ISP_MFBC_REGS_TYPE *pstRegs = NULL;
	ISP_2K_DRV_MFBC_REG_CTX(pstRegs);

	ISP_MFBC_DRV_GET_MfbcRegsVal(pstRegs);

	return 0;
}
#if 0
/*
*
*/
int ISP_DRV_SetMFBC(ISP_MFBC_CONFIG_S *ispMfbcInfo)
{
	ISP_CHECK_POINTER(ispMfbcInfo);
	ISP_MFBC_ATTR_S pstMfbcAttr;

	pstMfbcAttr.mfbc_input_width = ispMfbcInfo->mfbc_input_size.Width;
	pstMfbcAttr.mfbc_input_height = ispMfbcInfo->mfbc_input_size.Height;
	pstMfbcAttr.mfbc_out_format_cfg = ispMfbcInfo->mfbc_out_format_cfg;
	//y
	pstMfbcAttr.mfbc_y_data_buf_base0 = ispMfbcInfo->yDataBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_y_data_buf_base1 = ispMfbcInfo->yDataBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_y_data_stride = ispMfbcInfo->yDataBufInfo.data_stride;
	pstMfbcAttr.mfbc_y_data_wr_blen = ispMfbcInfo->yDataBufInfo.data_wr_blen;
	//
	pstMfbcAttr.mfbc_y_head_buf_base0 = ispMfbcInfo->yHeadBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_y_head_buf_base1 = ispMfbcInfo->yHeadBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_y_head_stride = ispMfbcInfo->yHeadBufInfo.data_stride;
	pstMfbcAttr.mfbc_y_head_wr_blen = ispMfbcInfo->yHeadBufInfo.data_wr_blen;
	//uv
	pstMfbcAttr.mfbc_uv_data_buf_base0 = ispMfbcInfo->uvDataBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_uv_data_buf_base1 = ispMfbcInfo->uvDataBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_uv_data_stride = ispMfbcInfo->uvDataBufInfo.data_stride;
	pstMfbcAttr.mfbc_uv_data_wr_blen = ispMfbcInfo->uvDataBufInfo.data_wr_blen;
	//
	pstMfbcAttr.mfbc_uv_head_buf_base0 = ispMfbcInfo->uvHeadBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_uv_head_buf_base1 = ispMfbcInfo->uvHeadBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_uv_head_stride = ispMfbcInfo->uvHeadBufInfo.data_stride;
	pstMfbcAttr.mfbc_uv_head_wr_blen = ispMfbcInfo->uvHeadBufInfo.data_wr_blen;
	//yl
	pstMfbcAttr.mfbc_yl_data_buf_base0 = ispMfbcInfo->ylDataBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_yl_data_buf_base1 = ispMfbcInfo->ylDataBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_yl_data_stride = ispMfbcInfo->ylDataBufInfo.data_stride;
	pstMfbcAttr.mfbc_yl_data_wr_blen = ispMfbcInfo->ylDataBufInfo.data_wr_blen;
	//
	pstMfbcAttr.mfbc_yl_head_buf_base0 = ispMfbcInfo->ylHeadBufInfo.data_buf_base0;
	pstMfbcAttr.mfbc_yl_head_buf_base1 = ispMfbcInfo->ylHeadBufInfo.data_buf_base1;
	pstMfbcAttr.mfbc_yl_head_stride = ispMfbcInfo->ylHeadBufInfo.data_stride;
	pstMfbcAttr.mfbc_yl_head_wr_blen = ispMfbcInfo->ylHeadBufInfo.data_wr_blen;	

	ISP_DRV_MFBC_SetConfig(&pstMfbcAttr);
	
	return 0;
}
#endif
