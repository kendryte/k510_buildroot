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
  File Name     : kd_vpss_common.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_VPS_COMMON_H__
#define __KD_VPS_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define KD_SUCCESS          0
#define KD_FAILURE          (-1)

typedef unsigned char   KD_U8;
typedef float           KD_F32;
typedef void            KD_VOID;

#define SHARE_MEMORY_DEV            "/dev/k510-share-memory"
#define DEV_NAME_DDR                "/dev/mem"
#define KDVPS_DEV                  "/dev/twod"
#define MEMORY_BLOCK_ALIGN          4096        /* align 4k for mmap */

#define KENDRYTE_TWOD_SET_DATA                     _IOWR('T', 3, unsigned long)
#define SHARE_MEMORY_INVAL_RANGE                   _IOWR('m', 5, unsigned long)
#define SHARE_MEMORY_WB_RANGE                      _IOWR('m', 6, unsigned long)

#ifdef __cplusplus
}
#endif

#endif // __KD_VPS_COMMON_H__