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
  File Name     : kd_vps.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include <poll.h>
#include "kd_vps.h"
#include "kd_vps_log.h"
#include "kd_vps_common.h"

#define MAX_VPS_JOB_NUM     8
#define MAX_TASK_NUM        3

typedef enum kdVPS_TASK_TYPE_E
{
    KD_SCALE_TASK = 1,
    KD_ROTATION_TASK,
    KD_TASK_BUTT,
} VPS_TASK_TYPE_E;

typedef enum kdVPS_JOB_STATUS_E
{
    KD_JOB_BEGIN = 1,
    KD_JOB_END,
    KD_JOB_BUTT,
} VPS_JOB_STATUS_E;

typedef struct kdVPS_SCALE_PARAM_S
{
    KD_U32      u32HorStep;
    KD_U32      u32VerStep;
    KD_U32      u32HorFracStep;
    KD_U32      u32VerFracStep;
} VPS_SCALE_PARAM_S;

typedef struct kdVPS_ROTATION_PARAM_S
{

} VPS_ROTATION_PARAM_S;

typedef struct kdTASK_PARAMETER_S
{
    VPS_TASK_TYPE_E             enTaskType;
    union
    {
        VPS_SCALE_PARAM_S       stScaleParam;
        VPS_ROTATION_PARAM_S    stRotationParam;
    };
} TASK_PARAMETER_S;

typedef struct stVPS_DATA_UNIT_S
{
    KD_U32              u32YrgbAddr;
    KD_U32              u32UvAddr;
    KD_U32              u32Vaddr;
    KD_U32              u32PixelFmt;
    KD_U32              u32Bpp;
    KD_U32              u32Pitch;
    KD_U32              u32VerStep;
    KD_U32              u32VerFracStep;
    KD_U32              u32HorStep;
    KD_U32              u32HorFracStep;
    KD_U16              u16ActWidth;
    KD_U16              u16ActHeight;
    KD_U16              u16HorOffset;
    KD_U16              u16VerOffset;
    KD_U16              u16VirWidth;
    KD_U16              u16VirHeight;
    KD_U32              u32AlphaSwap;
} VPS_DATA_UNIT_S;

typedef struct kdVPS_INFO_S
{
    VPS_DATA_UNIT_S     stSrcDataUnit;
    VPS_DATA_UNIT_S     stDesDataUnit;
    KD_U32              mode;
} VPS_INFO_S;

typedef struct kdVPS_HANDLE_S
{
    KD_U32              u32SrcWidth;
    KD_U32              u32SrcHeight;
    KD_U32              u32DesWidth;
    KD_U32              u32DesHeight;
    TASK_PARAMETER_S    stTaskInfoArray[MAX_TASK_NUM];
    KD_S32              s32TaskIdx;
    VPS_JOB_STATUS_E    enJobStatus;
} VPS_HANDLE_S;

typedef struct kdMemory_CACHE_REQUEST_S
{
    size_t  size;
    KD_U64  u64VirAddr;
    KD_U64  u64PhyAddr;
} Memory_CACHE_REQUEST_S;

static VPS_HANDLE_S *pVpsHandle[MAX_VPS_JOB_NUM] = {NULL};

static KD_S32   s32Handle = -1;
static KD_S32   s32SharedMemFd = -1;
static KD_S32   s32VpsFd = -1;

static KD_S32 flashDateCache(VPS_TASK_ATTR_S *pstTask)
{
    Memory_CACHE_REQUEST_S request = {};
    request.u64PhyAddr = pstTask->stImgIn.u64PhyData;
    request.u64VirAddr = pstTask->stImgIn.u64VirData;
    request.size = pstTask->stImgIn.u32Width * pstTask->stImgIn.u32Height * 3 / 2;

    if (ioctl(s32SharedMemFd, SHARE_MEMORY_WB_RANGE, &request) < 0)
    {
        KD_VPS_LOG_DEBUG("%S: falsh cache failed.\n", __func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

static KD_S32 InvalidCache(VPS_TASK_ATTR_S *pstTask)
{
    Memory_CACHE_REQUEST_S request = {};

    request.u64PhyAddr = pstTask->stImgOut.u64PhyData;
    request.u64VirAddr = pstTask->stImgOut.u64VirData;
    request.size = pstTask->stImgOut.u32Width * pstTask->stImgOut.u32Height * 3 / 2;

    if (ioctl(s32SharedMemFd, SHARE_MEMORY_INVAL_RANGE, &request) < 0)
    {
        KD_VPS_LOG_DEBUG("%s: invalid cache failed.\n", __func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

static KD_VOID waitProcessVsync()
{
    struct pollfd twoFd;
    twoFd.fd = s32VpsFd;
    twoFd.events = POLLIN;

    poll(&twoFd, 1, -1);
    if (twoFd.events == POLLIN)
    {
        KD_VPS_LOG_INFO("%s: wait sync complete.\n", __func__);
    }
    return KD_SUCCESS;
}

static KD_S32 setScaleStep(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask)
{
    KD_U32  u32SrcWidth, u32SrcHeight;
    KD_U32  u32DesWidth, u32DesHeight;
    KD_U32  u32HorStep, u32VerStep;
    KD_F32  f32HorFracStep, f32VerFracStep;

    KD_S32  s32TaskIdx = pVpsHandle[hHandle]->s32TaskIdx;

    if (pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].enTaskType != KD_SCALE_TASK)
    {
        KD_VPS_LOG_ERROR("%s: the task type is invalid.\n", __func__);
        return KD_FAILURE;
    }

    u32SrcWidth = pstTask->stImgIn.u32Width;
    u32SrcHeight = pstTask->stImgIn.u32Height;
    u32DesWidth = pstTask->stImgOut.u32Width;
    u32DesHeight = pstTask->stImgOut.u32Height;

    // set horizonal scale step
    if (pstTask->stImgIn.u32Width >= pstTask->stImgOut.u32Width)
    {
        u32HorStep = u32SrcWidth / u32DesWidth;
        f32HorFracStep = (((KD_F32)u32SrcWidth / (KD_F32)u32DesWidth) - u32HorStep) * 65536;
        pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32HorStep = u32HorStep + ((KD_U32)f32HorFracStep << 16);
    }
    else
    {
        f32HorFracStep = ((KD_F32)u32SrcWidth / (KD_F32)u32DesWidth) * 65536;
        pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32HorStep = (KD_U32)f32HorFracStep << 16;
    }

    // set vertical scale step
    if (u32SrcHeight >= u32DesHeight)
    {
        u32VerStep = u32SrcHeight / u32DesHeight;
        f32VerFracStep = (((KD_F32)u32SrcHeight / (KD_F32)u32DesHeight) - u32VerStep) * 65536;
        pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32VerStep = u32VerStep + ((KD_U32)f32VerFracStep << 16);
    }
    else
    {
        f32VerFracStep = ((KD_F32)u32SrcHeight / (KD_F32)u32DesHeight) * 65536;
        pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32VerStep = (KD_U32)f32VerFracStep << 16;
    }

    return KD_SUCCESS;
}

static KD_VOID setScaleConfig(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, VPS_DATA_UNIT_S *pstSrcDataUnit, VPS_DATA_UNIT_S *pstDesDataUnit)
{
    KD_U32  u32SrcWidth = pstTask->stImgIn.u32Width;
    KD_U32  u32SrcHeight = pstTask->stImgIn.u32Height;
    KD_U32  u32DesWidth = pstTask->stImgOut.u32Width;
    KD_U32  u32DesHeight = pstTask->stImgOut.u32Height;

    KD_S32  s32TaskIdx = pVpsHandle[hHandle]->s32TaskIdx;

    pstSrcDataUnit->u16ActWidth = u32SrcWidth;
    pstSrcDataUnit->u16ActHeight = u32SrcHeight;
    pstSrcDataUnit->u32PixelFmt = pstTask->stImgIn.enPixelFormat;
    pstSrcDataUnit->u32Pitch = u32SrcWidth;
    pstSrcDataUnit->u32YrgbAddr = pstTask->stImgIn.u64PhyData;
    pstSrcDataUnit->u32UvAddr = pstSrcDataUnit->u32YrgbAddr + (u32SrcWidth * u32SrcHeight);
    pstSrcDataUnit->u32Bpp = 0;
    pstSrcDataUnit->u32Vaddr = 0;
    pstSrcDataUnit->u32VerStep = pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32VerStep;
    pstSrcDataUnit->u32HorStep = pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].stScaleParam.u32HorStep;
    pstSrcDataUnit->u32VerFracStep = 0;
    pstSrcDataUnit->u32HorFracStep = 0;
    pstSrcDataUnit->u16HorOffset = 0;
    pstSrcDataUnit->u16VerOffset = 0;

    pstDesDataUnit->u16ActWidth = u32DesWidth;
    pstDesDataUnit->u16ActHeight = u32DesHeight;
    pstDesDataUnit->u32PixelFmt = pstTask->stImgOut.enPixelFormat;
    pstDesDataUnit->u32Pitch = u32DesWidth;
    pstDesDataUnit->u32YrgbAddr = pstTask->stImgOut.u64PhyData;
    pstDesDataUnit->u32UvAddr = pstDesDataUnit->u32YrgbAddr + (u32DesWidth * u32DesHeight);
    pstDesDataUnit->u32Bpp = 8;
    pstDesDataUnit->u32Vaddr = 0;
    pstDesDataUnit->u32VerStep = 0;
    pstDesDataUnit->u32HorStep = 0;
    pstDesDataUnit->u32VerFracStep = 0;
    pstDesDataUnit->u32HorFracStep = 0;
    pstDesDataUnit->u16HorOffset = 0;
    pstDesDataUnit->u16VerOffset = 0;
}

static KD_VOID setRotationConfig(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, VPS_DATA_UNIT_S *pstSrcDataUnit, VPS_DATA_UNIT_S *pstDesDataUnit)
{
    KD_U32 u32SrcWidth = pstTask->stImgIn.u32Width;
    KD_U32 u32SrcHeight = pstTask->stImgIn.u32Height;
    KD_U32 u32DesWidth = pstTask->stImgOut.u32Width;
    KD_U32 u32DesHeight = pstTask->stImgOut.u32Height;

    KD_S32 s32TaskIdx = pVpsHandle[hHandle]->s32TaskIdx;

    pstSrcDataUnit->u16ActWidth = u32SrcWidth;
    pstSrcDataUnit->u16ActHeight = u32SrcHeight;
    pstSrcDataUnit->u32PixelFmt = pstTask->stImgIn.enPixelFormat;
    pstSrcDataUnit->u32YrgbAddr = pstTask->stImgIn.u64PhyData;
    pstSrcDataUnit->u32UvAddr = pstSrcDataUnit->u32YrgbAddr + (u32SrcWidth * u32SrcHeight);
    pstSrcDataUnit->u32Vaddr = 0;
    pstSrcDataUnit->u32Bpp = 8;

    pstDesDataUnit->u16ActWidth = u32DesWidth;
    pstDesDataUnit->u16ActHeight = u32DesHeight;
    pstDesDataUnit->u32PixelFmt = pstTask->stImgOut.enPixelFormat;
    pstDesDataUnit->u32YrgbAddr = pstTask->stImgOut.u64PhyData;
    pstDesDataUnit->u32UvAddr = pstDesDataUnit->u32YrgbAddr + (u32DesWidth * u32DesHeight);
    pstDesDataUnit->u32Vaddr = 0;
    pstDesDataUnit->u32Bpp = 8;
}

KD_S32  KD_MPI_VPS_Init(KD_S32 *s32MemFd)
{
    initLog();

    s32SharedMemFd = *s32MemFd;
    if (s32SharedMemFd < 0)
    {
        s32SharedMemFd = open(SHARE_MEMORY_DEV, O_RDWR);
        if (s32SharedMemFd < 0)
        {
            KD_VPS_LOG_DEBUG("%s: vps init failed.\n", __func__);
            return KD_FAILURE;
        }
        *s32MemFd = s32SharedMemFd;
    }

    if (s32VpsFd < 0)
    {
        s32VpsFd = open(KDVPS_DEV, O_RDWR);
        if (s32VpsFd < 0)
        {
            KD_VPS_LOG_DEBUG("%s: vps init failed.\n", __func__);
            return KD_FAILURE;
        }
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_BeginJob(VPS_HANDLE *phHandle)
{
    s32Handle++;
    if (s32Handle >= MAX_VPS_JOB_NUM || s32Handle < 0)
    {
        KD_VPS_LOG_ERROR("%s: job number is out of range [0, 7].\n", __func__);
        return KD_FAILURE;
    }

    if (!pVpsHandle[s32Handle])
    {
        pVpsHandle[s32Handle] = (VPS_HANDLE_S *)calloc(1, sizeof(VPS_HANDLE_S));
        if (pVpsHandle[s32Handle] == NULL)
        {
            KD_VPS_LOG_ERROR("%s: vps job begin failed.\n", __func__);
            return KD_FAILURE;
        }
    }

    if (pVpsHandle[s32Handle]->enJobStatus == KD_JOB_BEGIN)
    {
        KD_VPS_LOG_DEBUG("%s: the job has begun.\n", __func__);
        return KD_SUCCESS;
    }

    pVpsHandle[s32Handle]->s32TaskIdx = -1;

    *phHandle = s32Handle;

    pVpsHandle[s32Handle]->enJobStatus = KD_JOB_BEGIN;

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_AddScaleTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask)
{
    KD_RET kdRet = KD_SUCCESS;

    if (!pVpsHandle[hHandle])
    {
        KD_VPS_LOG_ERROR("%s: the handle %d is no begin.\n", __func__, hHandle);
        return KD_FAILURE;
    }

    if (pVpsHandle[hHandle]->enJobStatus == KD_JOB_END)
    {
        KD_VPS_LOG_ERROR("%s: the job has been completed.\n", __func__);
        return KD_FAILURE;
    }

    pVpsHandle[hHandle]->s32TaskIdx++;

    KD_S32  s32TaskIdx = pVpsHandle[hHandle]->s32TaskIdx;
    pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].enTaskType = KD_SCALE_TASK;

    kdRet = setScaleStep(hHandle, pstTask);
    if (kdRet != KD_SUCCESS)
    {
        KD_VPS_LOG_ERROR("%s: scale task add failed.\n",__func__);
        return KD_FAILURE;
    }

    VPS_DATA_UNIT_S stSrcDataUnit;
    VPS_DATA_UNIT_S stDesDataUnit;

    memset(&stSrcDataUnit, 0, sizeof(VPS_DATA_UNIT_S));
    memset(&stDesDataUnit, 0, sizeof(VPS_DATA_UNIT_S));

    setScaleConfig(hHandle, pstTask, &stSrcDataUnit, &stDesDataUnit);

    kdRet = flashDateCache(pstTask);
    if (kdRet != KD_SUCCESS)
    {
        KD_VPS_LOG_DEBUG("%s: falsh cache failed.\n",__func__);
        return KD_FAILURE;
    }

    VPS_INFO_S stVpsInfo;
    memset(&stVpsInfo, 0, sizeof(VPS_INFO_S));

    memcpy(&stVpsInfo.stSrcDataUnit, &stSrcDataUnit, sizeof(VPS_DATA_UNIT_S));
    memcpy(&stVpsInfo.stDesDataUnit, &stDesDataUnit, sizeof(VPS_DATA_UNIT_S));

    stVpsInfo.mode = 3; // 3 is scale

    if (ioctl(s32VpsFd, KENDRYTE_TWOD_SET_DATA, &stVpsInfo) < 0)
    {
        KD_VPS_LOG_ERROR("%s: scaler process failed.\n", __func__);
        return KD_FAILURE;
    }

    waitProcessVsync();

    kdRet = InvalidCache(pstTask);
    if (kdRet != KD_SUCCESS)
    {
        KD_VPS_LOG_DEBUG("%s: invalid cache failed.\n",__func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VGS_AddOsdTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, const VPS_ADD_OSD_S *pstVgsAddOsd)
{
    // TODO: 
    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_AddOsdTaskArray(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, const VPS_ADD_OSD_S pstVgsAddOsd[], KD_U32 u32ArraySize)
{
    // TODO
    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_AddRotationTask(VPS_HANDLE hHandle, const VPS_TASK_ATTR_S *pstTask, ROTATION_E enRotationAngle)
{
    KD_RET kdRet = KD_SUCCESS;

    if (!pVpsHandle[hHandle])
    {
        KD_VPS_LOG_ERROR("%s: the handle %d is no begin.\n", __func__, hHandle);
        return KD_FAILURE;
    }

    if (pVpsHandle[s32Handle]->enJobStatus == KD_JOB_END)
    {
        KD_VPS_LOG_ERROR("%s: the job has been completed.\n", __func__);
        return KD_FAILURE;
    }

    pVpsHandle[hHandle]->s32TaskIdx++;

    KD_S32 s32TaskIdx = pVpsHandle[hHandle]->s32TaskIdx;
    pVpsHandle[hHandle]->stTaskInfoArray[s32TaskIdx].enTaskType = KD_ROTATION_TASK;

    VPS_DATA_UNIT_S stSrcDataUnit;
    VPS_DATA_UNIT_S stDesDataUnit;

    memset(&stSrcDataUnit, 0, sizeof(VPS_DATA_UNIT_S));
    memset(&stDesDataUnit, 0, sizeof(VPS_DATA_UNIT_S));

    setRotationConfig(hHandle, pstTask, &stSrcDataUnit, &stDesDataUnit);

    kdRet = flashDateCache(pstTask);
    if (kdRet != KD_SUCCESS)
    {
        KD_VPS_LOG_DEBUG("%s: falsh cache failed.\n",__func__);
        return KD_FAILURE;
    }

    VPS_INFO_S stVpsInfo;
    memset(&stVpsInfo, 0, sizeof(VPS_INFO_S));

    memcpy(&stVpsInfo.stSrcDataUnit, &stSrcDataUnit, sizeof(VPS_DATA_UNIT_S));
    memcpy(&stVpsInfo.stDesDataUnit, &stDesDataUnit, sizeof(VPS_DATA_UNIT_S));

    stVpsInfo.mode = enRotationAngle;

    if (ioctl(s32VpsFd, KENDRYTE_TWOD_SET_DATA, &stVpsInfo) < 0)
    {
        KD_VPS_LOG_DEBUG("%s: rotation process failed.\n", __func__);
        return KD_FAILURE;
    }

    waitProcessVsync();

    kdRet = InvalidCache(pstTask);
    if (kdRet != KD_SUCCESS)
    {
        KD_VPS_LOG_DEBUG("%s: invalid cache failed.\n",__func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_EndJob(VPS_HANDLE hHandle)
{
    if (!pVpsHandle[hHandle])
    {
        KD_VPS_LOG_ERROR("%s: the handle %d is no begin.\n", __func__, hHandle);
        return KD_FAILURE;
    }

    pVpsHandle[hHandle]->enJobStatus = KD_JOB_END;

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_CancelJob(VPS_HANDLE hHandle)
{
    if (!pVpsHandle[hHandle])
    {
        free(pVpsHandle[hHandle]);
        pVpsHandle[hHandle] = NULL;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VPS_DeInit()
{
    if (s32VpsFd > 0)
    {
        close(s32VpsFd);
    }

    return KD_SUCCESS;
}