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
  File Name     : kd_mem.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_SYS_H__
#define __KD_SYS_H__

#include "kd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kdSYS_INFO_S
{
    KD_S32  s32MemFd;
    KD_S32  s32MemMapFd;
} SYS_INFO_S;

KD_S32  KD_MPI_SYS_Init(SYS_INFO_S *pstSysInfo);

KD_S32  KD_MPI_SYS_Alloc(SYS_INFO_S *pstSysInfo, KD_U32 u32BufSize, KD_U32 *u32PhyAddr, KD_U64 *u64VirAddr);

KD_S32  KD_MPI_SYS_Free(SYS_INFO_S *pstSysInfo, KD_U32 u32BufSize, KD_U32 u32PhyAddr, KD_U64 u64VirAddr);

KD_S32  KD_MPI_SYS_Deinit(SYS_INFO_S *pstSysInfo);

#ifdef __cplusplus
}
#endif

#endif  // __KD_SYS_H__