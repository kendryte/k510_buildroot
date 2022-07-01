/* Copyright 2022 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
  File Name     : kd_venc.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef __KD_VENC_H__
#define __KD_VENC_H__

#include "kd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KD_SUCCESS          0
#define KD_FAILURE          (-1)
#define KD_VENC_BUF_FULL    1
#define KD_VENC_BUF_EMPTY   2
#define KD_VENC_NOT_PERMIT  3
#define KD_VENC_NOT_SUPPORT 4

typedef enum kdVENC_RC_MODE_E
{
    VENC_RC_MODE_CBR = 0,
    VENC_RC_MODE_VBR,
    VENC_RC_MODE_FIXQP,
    VENC_RC_MODE_BUTT,
} VENC_RC_MODE_E;

typedef enum kdVENC_TYPE_E
{
    VENC_TYPE_H264 = 0,
    VENC_TYPE_JPEG,
    VENC_TYPE_BUTT,
} VENC_TYPE_E;

typedef enum kdVENC_PROFILE_E
{
    VENC_PROFILE_BASELINE = 0,
    VENC_PROFILE_MAIN,
    VENC_PROFILE_HIGH,
    VENC_PROFILE_JPEG,
    VENC_PROFILE_BUTT,
} VENC_PROFILE_E;

typedef struct kdVENC_ATTR_RC_CBR_S
{
    KD_U32      u32GopLen;
    KD_U32      u32SrcFrameRate;
    KD_U32      u32DstFrameRate;
    KD_U32      u32BitRate;
} VENC_ATTR_RC_CBR_S;

typedef struct kdVENC_ATTR_RC_VBR_S
{
    KD_U32      u32GopLen;
    KD_U32      u32SrcFrameRate;
    KD_U32      u32DstFrameRate;
    KD_U32      u32MaxBitRate;
} VENC_ATTR_RC_VBR_S;

typedef struct kdVENC_ATTR_RC_FIXQP_S
{
    KD_U32      u32GopLen;
    KD_U32      u32SrcFrameRate;
    KD_U32      u32DstFrameRate;
} VENC_ATTR_RC_FIXQP_S;

typedef struct kdVENC_ATTR_S
{
    VENC_TYPE_E     enType;
    KD_U32          u32BufSize;
    VENC_PROFILE_E  enProfile;
    KD_U32          u32Level;
    KD_U32          u32PicWidth;
    KD_U32          u32PicHeight;
} VENC_ATTR_S;

typedef struct kdVENC_RC_ATTR_S
{
    VENC_RC_MODE_E      enRcMode;
    KD_S32              s32InitQp;
    union
    {
        VENC_ATTR_RC_CBR_S   stAttrCbr;
        VENC_ATTR_RC_VBR_S   stAttrVbr;
        VENC_ATTR_RC_FIXQP_S stAttrFixQp;
    };
} VENC_RC_ATTR_S;

typedef struct kdVENC_CHN_ATTR_S
{
    VENC_ATTR_S     stVencAttr;
    VENC_RC_ATTR_S  stRcAttr;
} VENC_CHN_ATTR_S;

typedef struct kdVENC_RECV_PIC_PARAM_S
{
    KD_S32      s32RecvPicNum;
} VENC_RECV_PIC_PARAM_S;

typedef struct kdVENC_STREAM_S
{
    KD_U8       *pu8Addr;
    KD_U32      u32Len;
} VENC_STREAM_S;

KD_S32 KD_MPI_VENC_Init();

KD_S32 KD_MPI_VENC_CreateChn(VENC_CHN VeChn, const VENC_CHN_ATTR_S *pstAttr);

KD_S32 KD_MPI_VENC_DestroyChn(VENC_CHN VeChn);

KD_S32 KD_MPI_VENC_StartRecvFrame(VENC_CHN VeChn, const VENC_RECV_PIC_PARAM_S *pstRecvParam);

KD_S32 KD_MPI_VENC_StopRecvFrame(VENC_CHN VeChn);

KD_S32 KD_MPI_VENC_GetStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream);

KD_S32 KD_MPI_VENC_ReleaseStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream);

KD_S32 KD_MPI_VENC_SendFrame(VENC_CHN VeChn, const VIDEO_FRAME_INFO_S *pstFrame, KD_S32 s32Millisec);

KD_S32 KD_MPI_VENC_Deinit();

#ifdef __cplusplus
}
#endif

#endif // __KD_VENC_H__


