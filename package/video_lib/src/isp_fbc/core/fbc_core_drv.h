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

/*
 * fbc_core_drv.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _FBC_CORE_DRV_H_
#define _FBC_CORE_DRV_H_

typedef struct _FBC_CORE_Y_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_Y_BUF_S;

typedef struct _FBC_CORE_Y_HEAD_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_Y_HEAD_BUF_S;

typedef struct _FBC_CORE_UV_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_UV_BUF_S;

typedef struct _FBC_CORE_UV_HEAD_BUF_S
{
    unsigned int Addr0;
    unsigned int Addr1;
    unsigned int Stride;
    unsigned int WrBlen;
}FBC_CORE_UV_HEAD_BUF_S;

typedef struct _FBC_CORE_BUF_S
{
    FBC_CORE_Y_BUF_S          stYBuf;
    FBC_CORE_Y_HEAD_BUF_S     stYHeadBuf;
    FBC_CORE_UV_BUF_S         stUVBuf;
    FBC_CORE_UV_HEAD_BUF_S    stUVHeadBuf;
}FBC_CORE_BUF_S;

typedef struct _FBC_CORE_SIZE_S
{
    unsigned int                input_width;
    unsigned int                input_height;
}FBC_CORE_SIZE_S;

typedef struct _FBC_CORE_ATTR_S
{
    unsigned char              yuv420_en;
    FBC_CORE_SIZE_S            stFbcSize;
    FBC_CORE_BUF_S             stFbcBuf;
}FBC_CORE_ATTR_S;
/*
*core
*/
int Fbc_Drv_Core_SetBuf(struct isp_device *isp,FBC_CORE_BUF_S *pstFBCBuf);
int Fbc_Drv_Core_SetSize(struct isp_device *isp,FBC_CORE_SIZE_S *pstSize);
int Fbc_Drv_Core_SetCtl(struct isp_device *isp,unsigned int yuv420_en);
#endif /*_FBC_CORE_DRV_H_*/