#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <vector>
#include <linux/videodev2.h>

#include <nncase/runtime/host_runtime_tensor.h>
#include <nncase/runtime/interpreter.h>
#include <nncase/runtime/runtime_tensor.h>

#include "kd_vi.h"
#include "kd_vo.h"
#include "retinaface.h"


#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define SCREEN_DISPLAY_WIDTH 1080
#define SCREEN_DISPLAY_HEIGHT 1920

pthread_mutex_t mutexLock;
pthread_cond_t  mutexCond;

static KD_U32 u32Do = 0;

void help()
{
    printf("-help: print the help info.\n");
    printf("-kmodel: the face detect kmodel.\n");
    printf("-netLen: the face detect model resolution.\n");
    printf("-detectW: the face detect image width.\n");
    printf("-detectH: the face detect image height.\n");
    printf("-objThr: the face detect threshold.\n");
    printf("-nmsThr: the face detect nms threshold.\n");
}

typedef struct kdSUB_PIPE_INFO_S
{
    KD_S32              s32SubIdx;
    KD_CHAR             subDevName[128];
    PIXEL_FORMAT_E      enPixFmt;
    KD_U32              u32Width;
    KD_U32              u32Height;
} SUB_PIPE_INFO_S;

typedef struct kdSAMPLE_FACEDETECT_CONTEXT_S
{
    KD_CHAR             *kmodePath;
    KD_U32              u32NetLen;
    KD_U32              u32DetectWidth;
    KD_U32              u32DetectHeight;
    KD_FLOAT            f32ObjThr;
    KD_FLOAT            f32NmsThr;
    SUB_PIPE_INFO_S     s32FaceDetectInfo;
    SUB_PIPE_INFO_S     s32OriginPipeInfo;
    KD_U32              u32DetectDo;
} SAMPLE_FACEDETECT_CONTEXT_S;

static KD_S32 parse_cmdline(int argc, char *argv[], SAMPLE_FACEDETECT_CONTEXT_S *pstSampleFaceDetectCtx)
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-kmodel") == 0)
        {
            pstSampleFaceDetectCtx->kmodePath = argv[i+1];
        }
        else if (strcmp(argv[i], "-netLen") == 0)
        {
            pstSampleFaceDetectCtx->u32NetLen = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-detectW") == 0)
        {
            pstSampleFaceDetectCtx->u32DetectWidth = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-detectH") == 0)
        {
            pstSampleFaceDetectCtx->u32DetectHeight = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-objThr") == 0)
        {
            pstSampleFaceDetectCtx->f32ObjThr = atof(argv[i+1]);
        }
        else if (strcmp(argv[i], "-nmsThr") == 0)
        {
            pstSampleFaceDetectCtx->f32NmsThr = atof(argv[i+1]);
        }
        else
        {
            printf("the cmdline is error, please check...\n");
            help();
            return -1;
        }
    }

    return 0;
}

static void *faceDetectProc(void *args)
{
    KD_S32  kdRet = KD_SUCCESS;

    SAMPLE_FACEDETECT_CONTEXT_S *pstSampleCtx;
    pstSampleCtx = (SAMPLE_FACEDETECT_CONTEXT_S *)args;

    KD_CHAR     *kmodelPath = pstSampleCtx->kmodePath;
    KD_U32      u32NetLen = pstSampleCtx->u32NetLen;
    KD_U32      u32DetectPicWith = pstSampleCtx->u32DetectWidth;
    KD_U32      u32DetectPicHeight = pstSampleCtx->u32DetectHeight;
    KD_FLOAT    f32ObjThr = pstSampleCtx->f32ObjThr;
    KD_FLOAT    f32NmsThr = pstSampleCtx->f32NmsThr;
    KD_U32      u32chnOffset = u32DetectPicWith * u32DetectPicWith;

    retinaface rf(u32NetLen, f32ObjThr, f32NmsThr);
    rf.load_model(kmodelPath);
    rf.prepare_memory();

    pthread_mutex_lock(&mutexLock);

    VI_SUB_PIPE_ATTR_S stLayer1PipeAttr;
    memset(&stLayer1PipeAttr, 0, sizeof(VI_SUB_PIPE_ATTR_S));

    stLayer1PipeAttr.enPixFmt = pstSampleCtx->s32FaceDetectInfo.enPixFmt;
    strcpy(stLayer1PipeAttr.subDevName, pstSampleCtx->s32FaceDetectInfo.subDevName);
    stLayer1PipeAttr.u32Width = pstSampleCtx->s32FaceDetectInfo.u32Width;
    stLayer1PipeAttr.u32Height = pstSampleCtx->s32FaceDetectInfo.u32Height;

    KD_S32  s32Layer1PipeIdx = pstSampleCtx->s32FaceDetectInfo.s32SubIdx;
    kdRet = KD_MPI_VI_CreateSubPipe(s32Layer1PipeIdx, &stLayer1PipeAttr);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device enable failed.\n");
        return NULL;
    }

    kdRet = KD_MPI_VI_StartSubPipe(s32Layer1PipeIdx);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi sub pipe start failed.\n");
        return NULL;
    }

    VO_VIDEO_LAYER_ATTR_S stVoLayer1Attr;
	memset(&stVoLayer1Attr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stVoLayer1Attr.enPixelFormat = PIXEL_FORMAT_ARGB;
	stVoLayer1Attr.u32PicWidth = pstSampleCtx->s32OriginPipeInfo.u32Width;
	stVoLayer1Attr.u32PicHeight = pstSampleCtx->s32OriginPipeInfo.u32Height;
    stVoLayer1Attr.u32OffsetX = 0;
    stVoLayer1Attr.u32OffsetY = (SCREEN_DISPLAY_HEIGHT - stVoLayer1Attr.u32PicHeight) / 2;
    stVoLayer1Attr.u32Bpp = 32;

    VO_LAYER VoLayer1 = 1;
    kdRet = KD_MPI_VO_EnableVideoLayer(VoLayer1, &stVoLayer1Attr);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo layer enable failed.\n");
		return NULL;
	}

    pthread_mutex_unlock(&mutexLock);

    VIDEO_FRAME_INFO_S stLayer1Frame;
	memset(&stLayer1Frame, 0, sizeof(VIDEO_FRAME_INFO_S));
	stLayer1Frame.enPixelFormat = stVoLayer1Attr.enPixelFormat;
	stLayer1Frame.u32Width = stVoLayer1Attr.u32PicWidth;
	stLayer1Frame.u32Height = stVoLayer1Attr.u32PicHeight;
    stLayer1Frame.u32DataSize = stLayer1Frame.u32Width * stLayer1Frame.u32Height * 4;

	KD_U8 *pLayer1Buf = (KD_U8 *)malloc(stLayer1Frame.u32DataSize);
	stLayer1Frame.u64VirData = (KD_U64)pLayer1Buf;

    VIDEO_FRAME_INFO_S stFrameInfo;
    memset(&stFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));

    KD_S32 devId = 0;

    cv::Mat imgArgb;
    imgArgb = cv::Mat(stLayer1Frame.u32Height, stLayer1Frame.u32Width, CV_8UC4, pLayer1Buf);

    while (!pstSampleCtx->u32DetectDo)
    {
        kdRet = KD_MPI_VI_GetSubPipeFrame(s32Layer1PipeIdx, &stFrameInfo, -1);
        if (kdRet != KD_SUCCESS)
        {
            printf("sub pipe get vi frame failed.\n");
            continue;
        }
        
        memcpy((void *)rf.virtual_addr_input[0], (void *)stFrameInfo.u64VirData, stFrameInfo.u32DataSize);

        // R
        memset(rf.virtual_addr_input[0] + (u32DetectPicWith * u32DetectPicHeight), PADDING_R, (u32DetectPicWith - u32DetectPicHeight) * u32DetectPicWith);
        // G
        memset(rf.virtual_addr_input[0] + u32chnOffset + (u32DetectPicHeight * u32DetectPicWith), PADDING_G, (u32DetectPicWith - u32DetectPicHeight) * u32DetectPicWith);
        // B
        memset(rf.virtual_addr_input[0] + u32chnOffset * 2 + (u32DetectPicHeight * u32DetectPicWith), PADDING_B, (u32DetectPicWith - u32DetectPicHeight) * u32DetectPicWith);

        rf.set_input(0);
        rf.set_output();

        rf.run();

        rf.post_process();

        std::vector<box_t> validBox;
        std::vector<landmarks_t> validLandmarks;

        rf.get_final_box(validBox, validLandmarks);

        kdRet = KD_MPI_VI_ReleaseSubPipeFrame(s32Layer1PipeIdx, &stFrameInfo);
        if (kdRet != KD_SUCCESS)
        {
            printf("get vi frame failed.\n");
            break;
        }

        RECT_S rect;
        memset(&rect, 0, sizeof(RECT_S));

        imgArgb.setTo(cv::Scalar(0, 0, 0, 0));
        for (int i = 0; i < 32; i++)
        {
            rect.u32Index = i;
            rect.u32Enable = 0;
            kdRet = KD_MPI_VO_SetDrawRect(devId, &rect);
            if (kdRet != KD_SUCCESS)
            {
                printf("set draw attr failed.\n");
                break;
            }
        }

        KD_U32 u32ObjCnt = 0;
        KD_U32 offsetHeigth = (SCREEN_DISPLAY_HEIGHT - stLayer1Frame.u32Height) / 2;
        for (auto b : validBox)
        {
            if (u32ObjCnt < 32)
            {
                rect.u32Enable = 1;
                rect.u32Index = u32ObjCnt;

                landmarks_t l = validLandmarks[u32ObjCnt];
                for (int ll = 0; ll < 5; ll++)
                {
                    int x0 = l.points[2 * ll + 0] * stLayer1Frame.u32Width;
                    int y0 = l.points[2 * ll + 1] * u32DetectPicWith / u32DetectPicHeight * stLayer1Frame.u32Height;
                    cv::circle(imgArgb, cv::Point(x0, y0), 8, cv::Scalar(0, 0, 255, 255), -1);
                }

                KD_U32 x1 = (b.x + b.w / 2) * stLayer1Frame.u32Width;
                KD_U32 x0 = (b.x - b.w / 2) * stLayer1Frame.u32Width;
                KD_U32 y0 = (b.y - b.h / 2) * stLayer1Frame.u32Height * u32DetectPicWith / u32DetectPicHeight;
                KD_U32 y1 = (b.y + b.h / 2) * stLayer1Frame.u32Height * u32DetectPicWith / u32DetectPicHeight;
                x1 = max(0, min(x1, stLayer1Frame.u32Width));
                x0 = max(0, min(x0, stLayer1Frame.u32Width));
                y0 = max(0, min(y0, stLayer1Frame.u32Height));
                y1 = max(0, min(y1, stLayer1Frame.u32Height));

                rect.u32Left = x0;
                rect.u32Right = x1;
                rect.u32Top = y0 + offsetHeigth;
                rect.u32Bottom = y1 + offsetHeigth;
                kdRet = KD_MPI_VO_SetDrawRect(devId, &rect);
                if (kdRet != KD_SUCCESS)
                {
                    printf("set draw attr failed.\n");
                    break;
                }
            }
            u32ObjCnt += 1;
        }

        kdRet = KD_MPI_VO_SendFrame(VoLayer1, &stLayer1Frame);
		if (kdRet != KD_SUCCESS)
		{
			printf("send frame failed.\n");
			break;
		}

        pthread_mutex_lock(&mutexLock);
        pthread_cond_signal(&mutexCond);
        pthread_mutex_unlock(&mutexLock);
    }

    RECT_S rect;
    memset(&rect, 0, sizeof(RECT_S));
    for (int i = 0; i < 32; i++)
    {
        rect.u32Index = i;
        rect.u32Enable = 0;
        kdRet = KD_MPI_VO_SetDrawRect(devId, &rect);
        if (kdRet != KD_SUCCESS)
        {
            printf("set draw attr failed.\n");
            break;
        }
    }

    free(pLayer1Buf);

    return NULL;
}

KD_S32 sampleInit(SAMPLE_FACEDETECT_CONTEXT_S *pstSampleFaceDetectCtx, KD_S32 devId)
{
    KD_S32 kdRet = KD_SUCCESS;

    KD_MPI_VI_Init();
    KD_MPI_VO_Init();

    VI_DEV_ATTR_S stViDevAttr;
    memset(&stViDevAttr, 0, sizeof(VI_DEV_ATTR_S));

    kdRet = KD_MPI_VI_GetDevAttr(devId, &stViDevAttr);
    if (kdRet != KD_SUCCESS)
    {
        printf("set vi attribute failed.\n");
        return KD_FAILURE;
    }

    for (int subIdx = 0; subIdx < MAX_SUB_PIPE_NUM; subIdx++)
    {
        if (stViDevAttr.u32SubDevEnabled[subIdx] && !strcmp(stViDevAttr.subDevName[subIdx], "/dev/video5"))
        {
            pstSampleFaceDetectCtx->s32FaceDetectInfo.s32SubIdx = subIdx;
            pstSampleFaceDetectCtx->s32FaceDetectInfo.enPixFmt = stViDevAttr.enSubDevPixFmt[subIdx];
            strcpy(pstSampleFaceDetectCtx->s32FaceDetectInfo.subDevName, stViDevAttr.subDevName[subIdx]);
            pstSampleFaceDetectCtx->s32FaceDetectInfo.u32Height = stViDevAttr.u32SubDevHeight[subIdx];
            pstSampleFaceDetectCtx->s32FaceDetectInfo.u32Width = stViDevAttr.u32SubDevWidth[subIdx];
            printf("face indx = %d, width = %d, height = %d...\n", subIdx, pstSampleFaceDetectCtx->s32FaceDetectInfo.u32Width, pstSampleFaceDetectCtx->s32FaceDetectInfo.u32Height);
        }
        else if (stViDevAttr.u32SubDevEnabled[subIdx] && !strcmp(stViDevAttr.subDevName[subIdx], "/dev/video3"))
        {
            pstSampleFaceDetectCtx->s32OriginPipeInfo.s32SubIdx = subIdx;
            pstSampleFaceDetectCtx->s32OriginPipeInfo.enPixFmt = stViDevAttr.enSubDevPixFmt[subIdx];
            strcpy(pstSampleFaceDetectCtx->s32OriginPipeInfo.subDevName, stViDevAttr.subDevName[subIdx]);
            pstSampleFaceDetectCtx->s32OriginPipeInfo.u32Height = stViDevAttr.u32SubDevHeight[subIdx];
            pstSampleFaceDetectCtx->s32OriginPipeInfo.u32Width = stViDevAttr.u32SubDevWidth[subIdx];
            printf("orign indx = %d, width = %d, height = %d...\n", subIdx, pstSampleFaceDetectCtx->s32OriginPipeInfo.u32Width, pstSampleFaceDetectCtx->s32OriginPipeInfo.u32Height);
        }
    }

    kdRet = KD_MPI_VO_SetPubAttr(devId);
	if (kdRet != KD_SUCCESS)
	{
		printf("set public attribute failed.\n");
		return KD_FAILURE;
	}

    kdRet = KD_MPI_VO_Enable(devId);
	if (kdRet != KD_SUCCESS)
	{
		printf("vo device enable failed.\n");
		return KD_FAILURE;
	}

    return KD_SUCCESS;
}

KD_S32 sampleDeinit(SAMPLE_FACEDETECT_CONTEXT_S *pstSampleFaceDetectCtx, KD_S32 devId)
{
    KD_S32 kdRet = KD_SUCCESS;

    KD_S32 s32ViPipe1Id = pstSampleFaceDetectCtx->s32FaceDetectInfo.s32SubIdx;
    KD_S32 s32ViPipe2Id = pstSampleFaceDetectCtx->s32OriginPipeInfo.s32SubIdx;

    for (int i = 0; i < 2; i++)
    {
        KD_S32 pipeId = i == 0 ? s32ViPipe1Id : s32ViPipe2Id;

        kdRet = KD_MPI_VO_DisableVideoLayer(i);
        if (kdRet != KD_SUCCESS)
	    {
		    printf("vo disable failed.\n");
		    return -1;
	    }

        kdRet = KD_MPI_VI_StopSubPipe(pipeId);
        if (kdRet != KD_SUCCESS)
        {
            printf("vi device stop failed.\n");
            return KD_FAILURE;
        }

        kdRet = KD_MPI_VI_DestroySubPipe(pipeId);
        if (kdRet != KD_SUCCESS)
        {
            printf("vi device diable failed.\n");
            return KD_FAILURE;
        }
    }

    kdRet = KD_MPI_VO_Disable(devId);
	if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return KD_FAILURE;
	}

    KD_MPI_VI_Deinit();
    KD_MPI_VO_Deinit();

    return KD_SUCCESS;
}

static void signalHandler(int signal __attribute__((__unused__)))
{
	u32Do = 1;
}

int main(int argc, char **argv)
{
    KD_RET kdRet = KD_SUCCESS;

    if (argc < 2 || strcmp(argv[1], "-help") == 0)
    {
        printf("the cmdline arguments is invalid, please check...\n");
        help();
        return 0;
    }

    signal(SIGINT, signalHandler);

    SAMPLE_FACEDETECT_CONTEXT_S stSampleFaceDetectCtx;
    memset(&stSampleFaceDetectCtx, 0, sizeof(SAMPLE_FACEDETECT_CONTEXT_S));

    if (parse_cmdline(argc, argv, &stSampleFaceDetectCtx) != 0)
    {
        printf("parse cmdline argument failed.\n");
        return -1;
    }

    KD_S32 devId = 0;
    VO_LAYER VoBaseLayer = 0;
    KD_S32 s32BasePipeIdx;

    kdRet = sampleInit(&stSampleFaceDetectCtx, devId);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample init failed.\n");
        goto SAMPLE_DEINIT;
    }

    pthread_mutex_init(&mutexLock, NULL);
    pthread_cond_init(&mutexCond, NULL);

    pthread_t threadId;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&threadId, &attr, faceDetectProc, &stSampleFaceDetectCtx);

    pthread_mutex_lock(&mutexLock);

    VI_SUB_PIPE_ATTR_S stBasePipeAttr;
    memset(&stBasePipeAttr, 0, sizeof(VI_SUB_PIPE_ATTR_S));

    stBasePipeAttr.enPixFmt = stSampleFaceDetectCtx.s32OriginPipeInfo.enPixFmt;
    stBasePipeAttr.u32Width = stSampleFaceDetectCtx.s32OriginPipeInfo.u32Width;
    stBasePipeAttr.u32Height = stSampleFaceDetectCtx.s32OriginPipeInfo.u32Height;
    strcpy(stBasePipeAttr.subDevName, stSampleFaceDetectCtx.s32OriginPipeInfo.subDevName);

    s32BasePipeIdx = stSampleFaceDetectCtx.s32OriginPipeInfo.s32SubIdx;
    kdRet = KD_MPI_VI_CreateSubPipe(s32BasePipeIdx, &stBasePipeAttr);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device enable failed.\n");
        goto SAMPLE_DESTORY;
    }

    kdRet = KD_MPI_VI_StartSubPipe(s32BasePipeIdx);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi sub pipe start failed.\n");
        goto SAMPLE_DESTORY;
    }

    VO_VIDEO_LAYER_ATTR_S stVoBaseAttr;
	memset(&stVoBaseAttr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stVoBaseAttr.enPixelFormat = stSampleFaceDetectCtx.s32OriginPipeInfo.enPixFmt;
	stVoBaseAttr.u32PicWidth = stSampleFaceDetectCtx.s32OriginPipeInfo.u32Width;
	stVoBaseAttr.u32PicHeight = stSampleFaceDetectCtx.s32OriginPipeInfo.u32Height;
    stVoBaseAttr.u32OffsetX = 0;
    stVoBaseAttr.u32OffsetY = (SCREEN_DISPLAY_HEIGHT - stVoBaseAttr.u32PicHeight) / 2;
    stVoBaseAttr.u32Bpp = 8;

    kdRet = KD_MPI_VO_EnableVideoLayer(VoBaseLayer, &stVoBaseAttr);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo layer enable failed.\n");
		goto SAMPLE_DESTORY;
	}

    pthread_mutex_unlock(&mutexLock);

    VIDEO_FRAME_INFO_S stFrameInfo;
    memset(&stFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));

    while (!u32Do)
    {
        kdRet = KD_MPI_VI_GetSubPipeFrame(s32BasePipeIdx, &stFrameInfo, -1);
        if (kdRet != KD_SUCCESS)
        {
            printf("sub pipe get vi frame failed.\n");
            continue;
        }

        kdRet = KD_MPI_VO_SendFrame(VoBaseLayer, &stFrameInfo);
		if (kdRet != KD_SUCCESS)
		{
			printf("send frame failed.\n");
			continue;
		}

        pthread_mutex_lock(&mutexLock);
        pthread_cond_wait(&mutexCond, &mutexLock);
        pthread_mutex_unlock(&mutexLock);

        kdRet = KD_MPI_VO_FrameLayerSync(devId);
        if (kdRet != KD_SUCCESS)
		{
			printf("vo frame layer sync failed.\n");
			break;
		}

        kdRet = KD_MPI_VI_ReleaseSubPipeFrame(s32BasePipeIdx, &stFrameInfo);
        if (kdRet != KD_SUCCESS)
        {
            printf("get vi frame failed.\n");
            break;
        }
    }

SAMPLE_DESTORY:
    stSampleFaceDetectCtx.u32DetectDo = 1;

    pthread_join(threadId, NULL);

SAMPLE_DEINIT:
    kdRet = sampleDeinit(&stSampleFaceDetectCtx, devId);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return -1;
	}

    return 0;
}