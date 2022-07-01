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
  File Name     : kd_vi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_VI_H__
#define __KD_VI_H__

#include "kd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SUB_PIPE_NUM 4

typedef struct kdVI_DEV_ATTR_S
{
    KD_CHAR         *subDevName[MAX_SUB_PIPE_NUM];
    KD_U32          u32SubDevEnabled[MAX_SUB_PIPE_NUM];
    KD_U32          u32SubDevWidth[MAX_SUB_PIPE_NUM];
    KD_U32          u32SubDevHeight[MAX_SUB_PIPE_NUM];
    PIXEL_FORMAT_E  enSubDevPixFmt[MAX_SUB_PIPE_NUM];
} VI_DEV_ATTR_S;

typedef struct kdVI_SUB_PIPE_ATTR_S
{
    KD_CHAR           subDevName[128];
    KD_U32            u32Width;
    KD_U32            u32Height;
    PIXEL_FORMAT_E    enPixFmt;
} VI_SUB_PIPE_ATTR_S;

KD_S32  KD_MPI_VI_Init();

KD_S32  KD_MPI_VI_GetDevAttr(VI_DEV ViDev, VI_DEV_ATTR_S *pstDevAttr);

KD_S32  KD_MPI_VI_CreateSubPipe(VI_PIPE ViPipe, const VI_SUB_PIPE_ATTR_S *pstSubPipeAttr);

KD_S32  KD_MPI_VI_StartSubPipe(VI_PIPE ViPipe);

KD_S32  KD_MPI_VI_StopSubPipe(VI_PIPE ViPipe);

KD_S32  KD_MPI_VI_GetSubPipeFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstVideoFrame, KD_S32 s32MilliSec);

KD_S32  KD_MPI_VI_ReleaseSubPipeFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstVideoFrame);

KD_S32  KD_MPI_VI_DestroySubPipe(VI_PIPE ViPipe);

KD_S32  KD_MPI_VI_Deinit();

#ifdef __cplusplus
}
#endif

#endif  // __KD_VI_H__