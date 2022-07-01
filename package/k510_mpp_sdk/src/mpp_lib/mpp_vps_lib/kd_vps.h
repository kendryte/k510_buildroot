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
  File Name     : kd_vps.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_VPS_H__
#define __KD_VPS_H__

#include "kd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kdFRAME_RATE_CTRL_S
{
    KD_S32  s32SrcFrameRate;
    KD_S32  s32DstFrameRate;
} FRAME_RATE_CTRL_S;

typedef enum kdROTATION_E
{
    ROTATION_90 = 1,
    ROTATION_270 = 2,
    ROTATION_BUTT
} ROTATION_E;

typedef struct kdVPS_TASK_ATTR_S
{
    VIDEO_FRAME_INFO_S      stImgIn;
    VIDEO_FRAME_INFO_S      stImgOut;
    KD_U32                  reserved;
} VPS_TASK_ATTR_S;

typedef struct kdVPS_ADD_OSD_S
{
    KD_U32      reserved;
} VPS_ADD_OSD_S;

KD_S32  KD_MPI_VPS_Init(KD_S32 *s32MemFd);

KD_S32  KD_MPI_VPS_BeginJob(VPS_HANDLE *phHandle);

KD_S32  KD_MPI_VPS_AddScaleTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask);

KD_S32  KD_MPI_VGS_AddOsdTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, const VPS_ADD_OSD_S *pstVgsAddOsd);

KD_S32  KD_MPI_VPS_AddOsdTaskArray(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, const VPS_ADD_OSD_S pstVgsAddOsd[], KD_U32 u32ArraySize);

KD_S32  KD_MPI_VPS_AddRotationTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, ROTATION_E enRotationAngle);

KD_S32  KD_MPI_VPS_EndJob(VPS_HANDLE hHandle);

KD_S32  KD_MPI_VPS_CancelJob(VPS_HANDLE hHandle);

KD_S32  KD_MPI_VPS_DeInit();

#ifdef __cplusplus
}
#endif

#endif  // __KD_VPS_H__