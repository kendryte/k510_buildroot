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
  File Name     : kd_venc.c
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
#include <unistd.h>
#include "kd_venc.h"
#include "enc_interface.h"
#include "kd_venc_log.h"
#include "kd_fifo.h"
#include "kd_venc_common.h"

#define VENC_MAX_CHN 8
#define MAX_VENC_WIDTH 2048
#define MAX_VENC_HEIGHT 2048
#define MIN_VENC_WIDTH 128
#define MIN_VENC_HEIGHT 64
#define MAX_JENC_WIDTH 8192
#define MAX_JENC_HEIGHT 8192

typedef struct kdVENC_HANDLE_S
{
    VENC_TYPE_E             enType;
    VENC_RC_MODE_E          enRcMode;
    KD_S32                  s32InitQp;
    VENC_ATTR_RC_CBR_S      stAttrCbr;
    VENC_ATTR_RC_VBR_S      stAttrVbr;
    VENC_ATTR_RC_FIXQP_S    stAttrFixQp;
    KD_U32                  u32PicWidth;
    KD_U32                  u32PicHeight;
    PIXEL_FORMAT_E          enPixelFormat;
    FIFO_S                  *pInputFifo;
    KD_U32                  u32RecvFrmNum;
    VENC_STATUS_S           stEncStatus;
} VENC_HANDLE_S;

static void *pChnInst[VENC_MAX_CHANNELS] = {0};
static VENC_HANDLE_S *pChnHandle[VENC_MAX_CHANNELS] = {NULL};
static pthread_t threadId;

static KD_RET VencAttributeCheck(VENC_CHN VeChn, const VENC_CHN_ATTR_S *pstAttr)
{
    if (pstAttr->stVencAttr.enType != VENC_TYPE_H264 && pstAttr->stVencAttr.enType != VENC_TYPE_JPEG)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d, the encode type %d is not support.", __func__, VeChn, pstAttr->stVencAttr.enType);
        return KD_FAILURE;
    }

    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    if (pstAttr->stVencAttr.enType == VENC_TYPE_H264)
    {
        if (pstAttr->stVencAttr.u32PicWidth < MIN_VENC_WIDTH || pstAttr->stVencAttr.u32PicWidth > MAX_VENC_WIDTH ||
            pstAttr->stVencAttr.u32PicHeight < MIN_VENC_HEIGHT || pstAttr->stVencAttr.u32PicHeight > MAX_VENC_HEIGHT)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type H264, it is not support the resolution %d * %d.\n", __func__, VeChn, pstAttr->stVencAttr.u32PicWidth, pstAttr->stVencAttr.u32PicHeight);
            return KD_FAILURE;
        }

        if (pstAttr->stVencAttr.u32PicWidth % 8 != 0 || pstAttr->stVencAttr.u32PicHeight % 8 != 0)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type H264, the resolution %d * %d should be aligned with 8.\n", __func__, VeChn, pstAttr->stVencAttr.u32PicWidth, pstAttr->stVencAttr.u32PicHeight);
            return KD_FAILURE;
        }

        if (pstAttr->stVencAttr.enProfile < VENC_PROFILE_BASELINE || pstAttr->stVencAttr.enProfile > VENC_PROFILE_HIGH)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type H264, the profile %d is not support.", __func__, pstAttr->stVencAttr.enProfile);
            return KD_FAILURE;
        }

        if (pstAttr->stVencAttr.u32Level < 10 || pstAttr->stVencAttr.u32Level > 51)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type H264, the level %d is not support.", __func__, pstAttr->stVencAttr.u32Level);
            return KD_FAILURE;
        }

        if (pstAttr->stRcAttr.enRcMode < VENC_RC_MODE_CBR || pstAttr->stRcAttr.enRcMode > VENC_RC_MODE_FIXQP)
        {
            KD_VENC_LOG_ERROR("%s: type H264, the rcMode %d is not support.", __func__, pstAttr->stRcAttr.enRcMode);
            return KD_FAILURE;
        }
    }
    else if (pstAttr->stVencAttr.enType == VENC_TYPE_JPEG)
    {
        if (pstAttr->stVencAttr.u32PicWidth < 0 || pstAttr->stVencAttr.u32PicWidth > MAX_JENC_WIDTH ||
            pstAttr->stVencAttr.u32PicHeight < 0 || pstAttr->stVencAttr.u32PicHeight > MAX_JENC_HEIGHT)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type JPEG, it is not support the resolution %d*%d.\n", __func__, VeChn, pstAttr->stVencAttr.u32PicWidth, pstAttr->stVencAttr.u32PicHeight);
            return KD_FAILURE;
        }

        if (pstAttr->stVencAttr.u32PicWidth % 16 != 0 || pstAttr->stVencAttr.u32PicHeight % 2 != 0)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type JPEG, the picWidth %d should aligned with 16, picHeight %d should aligned with 2.\n", __func__, VeChn, pstAttr->stVencAttr.u32PicWidth, pstAttr->stVencAttr.u32PicHeight);
            return KD_FAILURE;
        }

        if (pstAttr->stVencAttr.enProfile != VENC_PROFILE_JPEG)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d, type JPEG, the profile %d is not support.", __func__, VeChn, pstAttr->stVencAttr.enProfile);
            return KD_FAILURE;
        }
    }

    return KD_SUCCESS;
}

static KD_RET VencInputFrameCheck(VENC_CHN VeChn, const VIDEO_FRAME_INFO_S *pstFrame)
{
    if (pstFrame == NULL)
    {
        KD_VENC_LOG_ERROR("%s: pstFrame is null\n", __func__);
        return KD_FAILURE;
    }

    if (pChnHandle[VeChn]->enType == VENC_TYPE_H264)
    {
        if ( pstFrame->enPixelFormat != PIXEL_FORMAT_YUV420 &&
            pstFrame->enPixelFormat != PIXEL_FORMAT_NV12)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d the type H264 not support pixel format %d.\n", __func__, VeChn, pstFrame->enPixelFormat);
            return KD_FAILURE;
        }
    }
    else if (pChnHandle[VeChn]->enType == VENC_TYPE_JPEG)
    {
        if (pstFrame->enPixelFormat != PIXEL_FORMAT_YUV420 &&
            pstFrame->enPixelFormat != PIXEL_FORMAT_YUV400)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d the type JPEG not support pixel format %d.\n", __func__, VeChn, pstFrame->enPixelFormat);
            return KD_FAILURE;
        }
    }
    else
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d the type %d is not support.\n", __func__, VeChn, pChnHandle[VeChn]->enType);
        return KD_FAILURE;
    }

    if (pstFrame->u32Width != pChnHandle[VeChn]->u32PicWidth ||
        pstFrame->u32Height != pChnHandle[VeChn]->u32PicHeight)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d the input frame resolution %d*%d is not invalid.\n", __func__, VeChn, pstFrame->u32Width, pstFrame->u32Height);
        return KD_FAILURE;
    }

    if (!pstFrame->u64PhyData || !pstFrame->u64VirData)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d the data is null.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

static KD_S32 isChnReady()
{
    for (int i = 0; i < VENC_MAX_CHN; i++)
    {
        if (pChnHandle[i] != NULL && pChnHandle[i]->stEncStatus == ENCODER_START)
        {
            return KD_TRUE;
        }
    }

    return KD_FALSE;
}

static KD_S32 isAllChnDestroy()
{
    for (int i = 0; i < VENC_MAX_CHN; i++)
    {
        if (pChnHandle[i] != NULL && pChnHandle[i]->stEncStatus != ENCODER_DESTROY)
        {
            return KD_FALSE;
        }
    }

    return KD_TRUE;
}

void *encodeProcess(void)
{
    while (!isChnReady())
    {
        usleep(1000);
    }

    while (1)
    {
        for (int VeChn = 0; VeChn < VENC_MAX_CHN; VeChn++)
        {
            if (pChnHandle[VeChn] == NULL || pChnHandle[VeChn]->stEncStatus != ENCODER_START)
            {
                continue;
                usleep(1000);
            }

            VIDEO_FRAME_INFO_S stFrameInfo;
            memset(&stFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));
            KD_S32 kdRet = FifoPop(pChnHandle[VeChn]->pInputFifo, &stFrameInfo);
            if (kdRet == KD_VENC_BUF_EMPTY)
            {
                usleep(1000);
                continue;
            }
            else if (kdRet == KD_FAILURE)
            {
                KD_VENC_LOG_ERROR("%s: VeChn %d the input buffer queue pop error.\n", __func__, VeChn);
                return;
            }

            EncoderHandle *pHandle = (EncoderHandle *)pChnInst[VeChn];
            EncInputFrame inputFrame;
            memset(&inputFrame, 0, sizeof(EncInputFrame));
            inputFrame.width = stFrameInfo.u32Width;
            inputFrame.height = stFrameInfo.u32Height;
            inputFrame.stride = (stFrameInfo.u32Width + 0x1F) & (~0x1F);
            inputFrame.data = (unsigned char *)stFrameInfo.u64PhyData;
            

            if (Enc_ERR == VideoEncoder_EncodeOneFrame(pHandle, &inputFrame))
            {
                KD_VENC_LOG_ERROR("%s: VeChn %d encode one frame failed.\n", __func__, VeChn);
                return KD_FAILURE;
            }

            KD_VENC_LOG_INFO("Vechn = %d, thread encode frame success.\n", VeChn);
            // TODO: reuse inputbuffer
        }

        if (isAllChnDestroy())
        {
            KD_VENC_LOG_DEBUG("%s: the encode channel destoried.\n", __func__);
            break;
        }
    }
    
    return;
}

KD_S32 KD_MPI_VENC_Init()
{
    KD_RET kdRet = KD_SUCCESS;

    // init log
    initLog();

    // encode process
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&threadId, &attr, encodeProcess, NULL);

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_Deinit()
{
    for (KD_U32 VeChn = 0; VeChn < VENC_MAX_CHN; VeChn++)
    {
        if (pChnHandle[VeChn] != NULL && pChnHandle[VeChn]->stEncStatus != ENCODER_DESTROY)
        {
            KD_VENC_LOG_ERROR("%s: the encode channel %d has not been destoried.\n", __func__, VeChn);
            return KD_VENC_NOT_PERMIT;
        }
    }

    pthread_join(threadId, NULL);

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_CreateChn(VENC_CHN VeChn, const VENC_CHN_ATTR_S *pstAttr)
{
    KD_RET kdRet = KD_SUCCESS;

    if (pstAttr == NULL)
    {
        KD_VENC_LOG_ERROR("%s: pstAttr is null\n", __func__);
        return KD_FAILURE;
    }
    
    if (pChnHandle[VeChn] == NULL)
    {
        pChnHandle[VeChn] = (VENC_HANDLE_S *)calloc(1, sizeof(VENC_HANDLE_S));
        if (pChnHandle[VeChn] == NULL)
        {
            KD_VENC_LOG_ERROR("%s: VeChn %d the handle malloc failed.\n", __func__, VeChn);
            free(pChnHandle[VeChn]);
            return KD_FAILURE;
        }
    }
    else
    {
        KD_VENC_LOG_DEBUG("%s: VeChn %d the channel has created .\n", __func__, VeChn);
        return KD_SUCCESS;
    }
    
    // create input fifo
    pChnHandle[VeChn]->pInputFifo = FifoCreate(MAX_FIFO_SIZE);

    kdRet = VencAttributeCheck(VeChn, pstAttr);
    if (KD_FAILURE == kdRet)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d, the attribute is invalid.\n", __func__, VeChn);
        free(pChnHandle[VeChn]);
        return KD_FAILURE;
    }

    EncSettings stVencConfig;
    memset(&stVencConfig, 0, sizeof(EncSettings));
    stVencConfig.channel = VeChn;
    stVencConfig.width = pstAttr->stVencAttr.u32PicWidth;
    stVencConfig.height = pstAttr->stVencAttr.u32PicHeight;
    stVencConfig.profile = pstAttr->stVencAttr.enProfile;
    stVencConfig.level = pstAttr->stVencAttr.u32Level;

    if (pstAttr->stVencAttr.enType == VENC_TYPE_H264)
    {
        switch (pstAttr->stRcAttr.enRcMode)
        {
            case VENC_RC_MODE_CBR:
            {
                stVencConfig.rcMode = CBR;
                stVencConfig.gopLen = pstAttr->stRcAttr.stAttrCbr.u32GopLen;
                stVencConfig.FrameRate = pstAttr->stRcAttr.stAttrCbr.u32DstFrameRate;
                stVencConfig.BitRate = pstAttr->stRcAttr.stAttrCbr.u32BitRate;
                stVencConfig.MaxBitRate = pstAttr->stRcAttr.stAttrCbr.u32BitRate;

                memcpy(&pChnHandle[VeChn]->stAttrCbr, &pstAttr->stRcAttr.stAttrCbr, sizeof(VENC_ATTR_RC_CBR_S));
                break;
            }
            case VENC_RC_MODE_VBR:
            {
                stVencConfig.rcMode = VBR;
                stVencConfig.gopLen = pstAttr->stRcAttr.stAttrVbr.u32GopLen;
                stVencConfig.FrameRate = pstAttr->stRcAttr.stAttrVbr.u32DstFrameRate;
                stVencConfig.MaxBitRate = pstAttr->stRcAttr.stAttrVbr.u32MaxBitRate;

                memcpy(&pChnHandle[VeChn]->stAttrVbr, &pstAttr->stRcAttr.stAttrVbr, sizeof(VENC_ATTR_RC_VBR_S));
                break;
            }
            case VENC_RC_MODE_FIXQP:
            {
                stVencConfig.rcMode = CONST_QP;
                stVencConfig.FrameRate = pstAttr->stRcAttr.stAttrFixQp.u32DstFrameRate;
                stVencConfig.gopLen = pstAttr->stRcAttr.stAttrFixQp.u32GopLen;

                memcpy(&pChnHandle[VeChn]->stAttrFixQp, &pstAttr->stRcAttr.stAttrFixQp, sizeof(VENC_ATTR_RC_FIXQP_S));
                break;
            }
            default:
            {
                KD_VENC_LOG_ERROR("%s: VeChn %d, type H264, the rcMode %d is not support.\n", __func__, VeChn, pstAttr->stRcAttr.enRcMode);
                return KD_FAILURE;
            }
        }
        stVencConfig.SliceQP = pstAttr->stRcAttr.s32InitQp;
        stVencConfig.AspectRatio = ASPECT_RATIO_16_9;
        stVencConfig.FreqIDR = pstAttr->stRcAttr.stAttrVbr.u32GopLen;
    }

    pChnHandle[VeChn]->enType = pstAttr->stVencAttr.enType;
    pChnHandle[VeChn]->u32PicWidth = pstAttr->stVencAttr.u32PicWidth;
    pChnHandle[VeChn]->u32PicHeight = pstAttr->stVencAttr.u32PicHeight;
    pChnHandle[VeChn]->s32InitQp = pstAttr->stRcAttr.s32InitQp;

    pChnInst[VeChn] = VideoEncoder_Create(&stVencConfig);
    if (pChnInst[VeChn] == NULL)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d, Venc Instance create error.\n", __func__, VeChn);
        free(pChnHandle[VeChn]);
        return KD_FAILURE;
    }

    pChnHandle[VeChn]->stEncStatus = ENCODER_CREATED;

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_DestroyChn(VENC_CHN VeChn)
{
    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    if (KD_SUCCESS != FifoDestory(pChnHandle[VeChn]->pInputFifo))
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d input buffer queue destory failed.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    EncoderHandle *pHandle = (EncoderHandle *)pChnInst[VeChn];
    if (Enc_ERR == VideoEncoder_Destroy(pHandle))
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d destroy encoder failed.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    pChnHandle[VeChn]->stEncStatus = ENCODER_DESTROY;

    if (pChnHandle[VeChn] != NULL)
    {
        free(pChnHandle[VeChn]);
        pChnHandle[VeChn] = NULL;
    }

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_StartRecvFrame(VENC_CHN VeChn, const VENC_RECV_PIC_PARAM_S *pstRecvParam)
{
    KD_RET kdRet = KD_SUCCESS;

    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    pChnHandle[VeChn]->u32RecvFrmNum = pstRecvParam->s32RecvPicNum;

    pChnHandle[VeChn]->stEncStatus = ENCODER_START;

    return kdRet;
}

KD_S32 KD_MPI_VENC_StopRecvFrame(VENC_CHN VeChn)
{
    KD_RET kdRet = KD_SUCCESS;

    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    pChnHandle[VeChn]->stEncStatus = ENCODER_STOP;

    return kdRet;
}

KD_S32 KD_MPI_VENC_GetStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream)
{
    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    EncoderHandle *pHandle = (EncoderHandle *)pChnInst[VeChn];
    EncOutputStream outputStream;
    memset(&outputStream, 0, sizeof(EncOutputStream));

    VideoEncoder_GetStream(pHandle, &outputStream);
    if (outputStream.bufSize == 0)
    {
        KD_VENC_LOG_DEBUG("%s: VeChn %d get stream failed.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    pstStream->u32Len = outputStream.bufSize;
    pstStream->pu8Addr = outputStream.bufAddr;

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_ReleaseStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream)
{
    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    EncoderHandle *pHandle = (EncoderHandle *)pChnInst[VeChn];
    EncOutputStream outputStream;
    memset(&outputStream, 0, sizeof(EncOutputStream));

    outputStream.bufAddr = pstStream->pu8Addr;
    outputStream.bufSize = pstStream->u32Len;

    if (Enc_ERR == VideoEncoder_ReleaseStream(pHandle, &outputStream))
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d release stream failed.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32 KD_MPI_VENC_SendFrame(VENC_CHN VeChn, const VIDEO_FRAME_INFO_S *pstFrame, KD_S32 s32Millisec)
{
    KD_RET kdRet = KD_SUCCESS;

    if (VeChn < 0 || VeChn > VENC_MAX_CHN)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    if (pChnHandle[VeChn]->stEncStatus != ENCODER_START)
    {
        KD_VENC_LOG_ERROR("%s: VeChn %d the encoder has not started.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    if (pChnHandle[VeChn]->stEncStatus == ENCODER_STOP ||
        pChnHandle[VeChn]->stEncStatus == ENCODER_DESTROY)
    {
        KD_VENC_LOG_DEBUG("%s: VeChn %d the encoder has stopped.\n", __func__, VeChn);
        return KD_VENC_NOT_PERMIT;
    }

    kdRet = VencInputFrameCheck(VeChn, pstFrame);
    if (KD_FAILURE == kdRet)
    {
        KD_VENC_LOG_ERROR("%s; VeChn %d, the input frame is invalid.\n", __func__, VeChn);
        return KD_FAILURE;
    }

    KD_U32 u32Count = 0;

    while (KD_VENC_BUF_FULL == FifoPush(pChnHandle[VeChn]->pInputFifo, pstFrame))
    {
        if (s32Millisec <= -1)
        {
            continue;
        }
        else if (s32Millisec == 0)
        {
            KD_VENC_LOG_DEBUG("%s; VeChn %d, the input buffer queue is full.\n", __func__, VeChn);
            return KD_VENC_BUF_FULL;
        }
        else
        {
            if (u32Count >= s32Millisec)
            {
                KD_VENC_LOG_DEBUG("%s; VeChn %d, the input buffer queue is full.\n", __func__, VeChn);
                return KD_VENC_BUF_FULL;
            }
            usleep(1000);
            u32Count++;
        }
    }

    KD_VENC_LOG_INFO("push one frame into input queue\n");

    // EncoderHandle *pHandle = (EncoderHandle *)pChnInst[VeChn];
    // EncInputFrame inputFrame;
    // memset(&inputFrame, 0, sizeof(EncInputFrame));
    // inputFrame.width = pstFrame->u32Width;
    // inputFrame.height = pstFrame->u32Height;
    // inputFrame.stride = (pstFrame->u32Width + 0x1F) & (~0x1F);
    // inputFrame.data = (unsigned char *)pstFrame->u64PhyData;

    // if (Enc_ERR == VideoEncoder_EncodeOneFrame(pHandle, &inputFrame))
    // {
    //     KD_VENC_LOG_ERROR("%s: VeChn %d encode one frame failed.\n", __func__, VeChn);
    //     return KD_FAILURE;
    // }

    return KD_SUCCESS;
}
