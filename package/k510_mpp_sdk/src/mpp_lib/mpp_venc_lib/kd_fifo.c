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
  File Name     : kd_fifo.c
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
#include "kd_fifo.h"
#include "kd_venc_log.h"

FIFO_S *FifoCreate(KD_U32 count)
{
    FIFO_S *fifo = (FIFO_S *)calloc(1, sizeof(FIFO_S));
    if (!fifo)
    {
        KD_VENC_LOG_ERROR("input buffer fifo is null.");
        free(fifo);
        return KD_FAILURE;
    }

    fifo->size = count;
    fifo->first = 0;
    fifo->elements = 0;

    pthread_mutex_init(&fifo->fifoLock, NULL);

    return fifo;
}

KD_S32 FifoPush(FIFO_S *fifo, VIDEO_FRAME_INFO_S *pFrame)
{
    if (!fifo)
    {
        KD_VENC_LOG_ERROR("input buffer fifo is null.");
        return KD_FAILURE;
    }

    pthread_mutex_lock(&fifo->fifoLock);

    if (FifoIsFull(fifo))
    {
        KD_VENC_LOG_DEBUG("the fifo is full.\n");
        pthread_mutex_unlock(&fifo->fifoLock);
        return KD_VENC_BUF_FULL;
    }

    fifo->buffer[(fifo->first + fifo->elements) % fifo->size] = pFrame;
    fifo->elements++;
    
    pthread_mutex_unlock(&fifo->fifoLock);
    
    return KD_SUCCESS;
}

KD_S32 FifoPop(FIFO_S *fifo, VIDEO_FRAME_INFO_S *pFrame)
{
    if (!fifo)
    {
        KD_VENC_LOG_ERROR("input buffer fifo is null.");
        return KD_FAILURE;
    }

    pthread_mutex_lock(&fifo->fifoLock);

    if (FifoIsEmpty(fifo))
    {
        KD_VENC_LOG_DEBUG("the fifo is empty.\n");
        pthread_mutex_unlock(&fifo->fifoLock);
        return KD_VENC_BUF_EMPTY;
    }

    memcpy(pFrame, fifo->buffer[fifo->first], sizeof(VIDEO_FRAME_INFO_S));
    fifo->first = (fifo->first + 1) % fifo->size;
    fifo->elements--;

    pthread_mutex_unlock(&fifo->fifoLock);

    return KD_SUCCESS;
}

KD_S32 FifoIsEmpty(FIFO_S *fifo)
{
    if (!fifo)
    {
        KD_VENC_LOG_ERROR("input buffer fifo is null.");
        return KD_FAILURE;
    }

    if (fifo->elements == 0)
    {
        return KD_TRUE;
    }
    else
    {
        return KD_FALSE;
    }
}

KD_S32 FifoIsFull(FIFO_S *fifo)
{
    if (!fifo)
    {
        KD_VENC_LOG_ERROR("input buffer fifo is null.");
        return KD_FAILURE;
    }
    
    if (fifo->size == fifo->elements)
    {
        return KD_TRUE;
    }
    else
    {
        return KD_FALSE;
    }
}

KD_S32 FifoDestory(FIFO_S *fifo)
{
    pthread_mutex_destroy(&fifo->fifoLock);

    if (!fifo)
    {
        free(fifo);
        fifo = NULL;
    }

    return KD_SUCCESS;
}

