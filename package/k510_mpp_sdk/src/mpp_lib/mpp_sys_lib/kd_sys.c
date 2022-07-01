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
  File Name     : kd_mem.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "kd_sys.h"
#include "kd_sys_log.h"

#define SHARE_MEMORY_DEV            "/dev/k510-share-memory"
#define MEMORY_MAP_DEV              "/dev/mem"
#define MEMORY_BLOCK_ALIGN          4096;

#define SHARE_MEMORY_ALIGN_ALLOC                    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE                           _IOWR('m', 3, unsigned long)

typedef struct kdSHARED_MEMORY_ALLOC_PARAM_S {
    KD_U32  u32Size;
    KD_U32  u32Align;
    KD_U32  u32PhyAddr;
} SHARED_MEMORY_ALLOC_PARAM_S;

KD_S32  KD_MPI_SYS_Init(SYS_INFO_S *pstSysInfo)
{
    initLog();

    pstSysInfo->s32MemFd = open(SHARE_MEMORY_DEV, O_RDWR);
    if (pstSysInfo->s32MemFd < 0)
    {
        KD_SYS_LOG_DEBUG("%s: sys init failed.\n", __func__);
        return KD_FAILURE;
    }

    pstSysInfo->s32MemMapFd = open(MEMORY_MAP_DEV, O_RDWR | O_SYNC);
    if (pstSysInfo->s32MemMapFd < 0)
    {
        KD_SYS_LOG_DEBUG("%s: sys init failed.\n", __func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_SYS_Alloc(SYS_INFO_S *pstSysInfo, KD_U32 u32BufSize, KD_U32 *u32PhyAddr, KD_U64 *pu64VirAddr)
{
    void *pVirAddr;

    SHARED_MEMORY_ALLOC_PARAM_S stAllocMemParam;
    memset(&stAllocMemParam, 0, sizeof(SHARED_MEMORY_ALLOC_PARAM_S));

    stAllocMemParam.u32Size = (u32BufSize + 0xfff) & (~0xfff);
    stAllocMemParam.u32Align = MEMORY_BLOCK_ALIGN;
    stAllocMemParam.u32PhyAddr = 0;

    if(ioctl(pstSysInfo->s32MemFd, SHARE_MEMORY_ALIGN_ALLOC, &stAllocMemParam) < 0)
    {
        KD_SYS_LOG_ERROR("%s: malloc memory  failed.\n", __func__);
        return KD_FAILURE;
    }

    *u32PhyAddr = stAllocMemParam.u32PhyAddr;

    pVirAddr = mmap(NULL, stAllocMemParam.u32Size, PROT_READ | PROT_WRITE, MAP_SHARED, pstSysInfo->s32MemMapFd, stAllocMemParam.u32PhyAddr);

    *pu64VirAddr = (KD_U64)pVirAddr;

    return KD_SUCCESS;
}

KD_S32  KD_MPI_SYS_Free(SYS_INFO_S *pstSysInfo, KD_U32 u32BufSize, KD_U32 u32PhyAddr, KD_U64 u64VirAddr)
{
    munmap((void*)u64VirAddr, u32BufSize);

    if (ioctl(pstSysInfo->s32MemFd, SHARE_MEMORY_FREE, &u32PhyAddr) < 0)
    {
        printf("free input memory failed.\n");
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_SYS_Deinit(SYS_INFO_S *pstSysInfo)
{
    if (pstSysInfo->s32MemFd > 0)
    {
        close(pstSysInfo->s32MemFd);
        pstSysInfo->s32MemFd = -1;
    }

    return KD_SUCCESS;
}