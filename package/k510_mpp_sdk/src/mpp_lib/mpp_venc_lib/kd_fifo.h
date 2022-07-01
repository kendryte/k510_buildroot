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
  File Name     : kd_fifo.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_FIFO_H__
#define __KD_FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "kd_venc.h"

#define MAX_FIFO_SIZE   4

typedef struct kdFIFO_S
{
    VIDEO_FRAME_INFO_S      *buffer[MAX_FIFO_SIZE];
    KD_U32                  size;
    KD_U32                  first;
    KD_U32                  elements;
    pthread_mutex_t         fifoLock;
} FIFO_S;

FIFO_S  *FifoCreate(KD_U32 count);
KD_S32  FifoPush(FIFO_S *fifo, VIDEO_FRAME_INFO_S *pFrame);
KD_S32  FifoPop(FIFO_S *fifo, VIDEO_FRAME_INFO_S *pFrame);
KD_S32  FifoIsEmpty(FIFO_S *fifo);
KD_S32  FifoIsFull(FIFO_S *fifo);
KD_S32  FifoDestory(FIFO_S *fifo);

#ifdef __cplusplus
}
#endif

#endif // __KD_FIFO_H__