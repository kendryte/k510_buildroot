/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mfbc_core_drv.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _MFBC_CORE_DRV_DEF_H_
#define _MFBC_CORE_DRV_DEF_H_

typedef struct _MFBC_CORE_Y_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_Y_BUF_S;

typedef struct _MFBC_CORE_Y_HEAD_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_Y_HEAD_BUF_S;

typedef struct _MFBC_CORE_UV_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_UV_BUF_S;

typedef struct _MFBC_CORE_UV_HEAD_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}MFBC_CORE_UV_HEAD_BUF_S;

typedef struct _MFBC_CORE_BUF_S
{
    MFBC_CORE_Y_BUF_S          stYBuf;
    MFBC_CORE_Y_HEAD_BUF_S     stYHeadBuf;
    MFBC_CORE_UV_BUF_S         stUVBuf;
    MFBC_CORE_UV_HEAD_BUF_S    stUVHeadBuf;
}MFBC_CORE_BUF_S;

typedef struct _MFBC_CORE_SIZE_S
{
    unsigned int                input_width;
    unsigned int                input_height;
}MFBC_CORE_SIZE_S;

typedef struct _MFBC_CORE_ATTR_S
{
    unsigned char               yuv420_en;
    MFBC_CORE_SIZE_S            stMfbcSize;
    MFBC_CORE_BUF_S             stMfbcBuf;
}MFBC_CORE_ATTR_S;

int MFBC_DRV_Core_Remap(void);
int MFBC_DRV_SetCore(MFBC_CORE_ATTR_S *mfbcCoreAttr);
//DEBUG
int MFBC_DRV_GetCoreRegsVal(void);
#endif /*_MFBC_CORE_DRV_DEF_H_*/
