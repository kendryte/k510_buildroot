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
  File Name     : kd_vo.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_VO_H__
#define __KD_VO_H__

#include "kd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kdVO_VIDEO_LAYER_ATTR_S
{
    KD_U32              u32Bpp;
    KD_U32              u32OffsetX;
    KD_U32              u32OffsetY;
    KD_U32              u32PicWidth;
    KD_U32              u32PicHeight;
    PIXEL_FORMAT_E      enPixelFormat;
} VO_VIDEO_LAYER_ATTR_S;

typedef struct kdRECT_S
{
    KD_U32  u32Index;
    KD_U32  u32Enable;
    KD_U32  u32Left;
    KD_U32  u32Right;
    KD_U32  u32Top;
    KD_U32  u32Bottom;
} RECT_S;

KD_S32  KD_MPI_VO_Init();

KD_S32  KD_MPI_VO_SetPubAttr(VO_DEV VoDev);

KD_S32  KD_MPI_VO_Enable(VO_DEV VoDev);

KD_S32  KD_MPI_VO_EnableVideoLayer(VO_LAYER VoLayer, const VO_VIDEO_LAYER_ATTR_S *pstLayerAttr);

KD_S32  KD_MPI_VO_DisableVideoLayer(VO_LAYER VoLayer);

KD_S32  KD_MPI_VO_SendFrame(VO_LAYER VoLayer, VIDEO_FRAME_INFO_S *pstFrame);

KD_S32  KD_MPI_VO_SetDrawRect(VO_DEV VoDev, RECT_S *rect);

KD_S32  KD_MPI_VO_FrameLayerSync(VO_DEV VoDev);

KD_S32  KD_MPI_VO_Disable(VO_DEV VoDev);

KD_S32  KD_MPI_VO_Deinit();

#ifdef __cplusplus
}
#endif

#endif  // __KD_VO_H__