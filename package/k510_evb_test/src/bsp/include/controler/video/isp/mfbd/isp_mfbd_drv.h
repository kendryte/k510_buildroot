/******************************************************************************

  Copyright (C), 2020, canaan Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_mfbd_drv.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : isp driver interface
  History       :
  1.Date        : 
    Author      : zhudalei
    Modification: Created file
******************************************************************************/
#ifndef _ISP_MFBD_DRV_DEF_H_
#define _ISP_MFBD_DRV_DEF_H_

typedef struct _ISP_MFBD_CTL_S
{
    unsigned int  mfbd_en;
    unsigned int  mfbd_format_cfg;
}ISP_MFBD_CTL_S;

typedef struct _ISP_MFBD_SIZE_S
{
	unsigned int mfbd_input_height;
	unsigned int mfbd_input_width;
}ISP_MFBD_SIZE_S;

typedef struct _ISP_MFBD_Y_BUF_S
{
	unsigned int mfbd_y_data_buf_base0;
	unsigned int mfbd_y_data_buf_base1;
	unsigned int mfbd_y_data_stride;
	unsigned int mfbd_y_head_buf_base0;
	unsigned int mfbd_y_head_buf_base1;
	unsigned int mfbd_y_head_stride;
}ISP_MFBD_Y_BUF_S;

typedef struct _ISP_MFBD_UV_BUF_S
{
	unsigned int mfbd_uv_data_buf_base0;
	unsigned int mfbd_uv_data_buf_base1;
	unsigned int mfbd_uv_data_stride;
	unsigned int mfbd_uv_head_buf_base0;
	unsigned int mfbd_uv_head_buf_base1;
	unsigned int mfbd_uv_head_stride;
}ISP_MFBD_UV_BUF_S;

typedef struct _ISP_MFBD_YL_BUF_S
{
	unsigned int mfbd_yl_data_buf_base0;
	unsigned int mfbd_yl_data_buf_base1;
	unsigned int mfbd_yl_data_stride;
	unsigned int mfbd_yl_head_buf_base0;
	unsigned int mfbd_yl_head_buf_base1;
	unsigned int mfbd_yl_head_stride;
}ISP_MFBD_YL_BUF_S;

typedef struct _ISP_MFBD_BUF_S
{
	ISP_MFBD_Y_BUF_S  	stIspMfbdYBuf;
	ISP_MFBD_UV_BUF_S 	stIspMfbdUVBuf; 
	ISP_MFBD_YL_BUF_S 	stIspMfbdYLBuf;	
} ISP_MFBD_BUF_S;

typedef struct _ISP_MFBD_ATTR_S
{
	ISP_MFBD_CTL_S		stIspMfbdCtl;	
	ISP_MFBD_SIZE_S		stIspMfbdSize;
	ISP_MFBD_BUF_S		stIspMfbdBuf;	
} ISP_MFBD_ATTR_S;

//int ISP_DRV_SetMFBD(ISP_MFBD_CONFIG_S *ispMfbdInfo);
//int ISP_DRV_MFBD_SetBuf(ISP_MFBD_ATTR_S *pstMfbdAttr);
//int ISP_DRV_MFBD_SetCtl(ISP_MFBD_ATTR_S *pstMfbdAttr);
int ISP_DRV_SetMFBD(ISP_MFBD_ATTR_S *pstIspMfbdAttr);
//DEBUG
int ISP_DRV_GetMFBDRegsVal(void);
#endif /*_ISP_MFBD_DRV_DEF_H_*/