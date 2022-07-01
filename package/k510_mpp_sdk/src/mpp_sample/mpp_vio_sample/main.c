#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "kd_sys.h"
#include "kd_vi.h"
#include "kd_vo.h"
#include "kd_vps.h"

#define VI_DEV_NAME_DEFAULT 	"./vi_device.conf"
#define DRM_DEV_NAME_DEFAULT 	"/dev/dri/card0"

static int done = 0;

typedef enum kdTASK_TYPE_E
{
    TASK_TYPE_SCALE = 0,
    TASK_TYPE_ROTATION,
    TASK_TYPE_BUTT,
} TASK_TYPE_E;

typedef struct kdSAMPLE_VIO_CONTEXT_S
{
    PIXEL_FORMAT_E  	enInPixelFmt;
    KD_U32              u32InputPicWidth;
    KD_U32              u32InputPicHeight;
	TASK_TYPE_E         enVpsTaskType;
	KD_U32              u32OutputPicWidth;
    KD_U32              u32OutputPicHeight;
} SAMPLE_VIO_CONTEXT_S;

static void help()
{
    printf("-help: print the help info.\n");
	printf("-vpsType: the task type, scale or rotation.\n");
	printf("-vpsOutputW: the output picture width.\n");
    printf("-vpsOutputH: the output picture height.\n");
}

static KD_S32 parse_cmdline(int argc, char *argv[], SAMPLE_VIO_CONTEXT_S *pstSampelVioCtx)
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-vpsType") == 0)
        {
            if (strcmp(argv[i+1], "scale") == 0)
            {
                pstSampelVioCtx->enVpsTaskType = TASK_TYPE_SCALE;
            }
            else if (strcmp(argv[i+1], "rotation") == 0)
            {
                pstSampelVioCtx->enVpsTaskType = TASK_TYPE_ROTATION;
            }
            else
            {
                printf("the task type is not support.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-inFmt") == 0)
        {
            if (strcmp(argv[i+1], "nv12") == 0)
            {
                pstSampelVioCtx->enInPixelFmt = PIXEL_FORMAT_NV12;
            }
            else
            {
                printf("the input file pixel format is invalid, please check...\n");
                help();
                return -1;
            }
        }
		else if (strcmp(argv[i], "-vpsOutputW") == 0)
        {
            pstSampelVioCtx->u32OutputPicWidth = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-vpsOutputH") == 0)
        {
            pstSampelVioCtx->u32OutputPicHeight = atoi(argv[i+1]);
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

static int allocFrameBuffer(SAMPLE_VIO_CONTEXT_S *pstSampleVpsCtx, VPS_TASK_ATTR_S *pstVpsTaskAttr, SYS_INFO_S *pstSysInfo)
{
    KD_U32 u32InFramePhyAddr;
    KD_U32 u32OutFramePhyAddr;
    KD_U64 u64InFrameVirAddr;
    KD_U64 u64OutFrameVirAddr;
    KD_U32 u32InFrameSize;
    KD_U32 u32OutFrameSize;

    if (pstSampleVpsCtx->enInPixelFmt == PIXEL_FORMAT_NV12)
    {
        pstVpsTaskAttr->stImgIn.enPixelFormat = PIXEL_FORMAT_NV12;
        pstVpsTaskAttr->stImgIn.u32Width = pstSampleVpsCtx->u32InputPicWidth;
        pstVpsTaskAttr->stImgIn.u32Height = pstSampleVpsCtx->u32InputPicHeight;
        u32InFrameSize = pstSampleVpsCtx->u32InputPicWidth * pstSampleVpsCtx->u32InputPicHeight * 3 / 2;
    }
    //if (pstSampleVpsCtx->enOutPixelFmt == PIXEL_FORMAT_NV12)
    {
        pstVpsTaskAttr->stImgOut.enPixelFormat = PIXEL_FORMAT_NV12;
        pstVpsTaskAttr->stImgOut.u32Width = pstSampleVpsCtx->u32OutputPicWidth;
        pstVpsTaskAttr->stImgOut.u32Height = pstSampleVpsCtx->u32OutputPicHeight;
        u32OutFrameSize = pstSampleVpsCtx->u32OutputPicWidth * pstSampleVpsCtx->u32OutputPicHeight * 3 / 2;
    }

    KD_RET kdRet = KD_MPI_SYS_Alloc(pstSysInfo, u32InFrameSize, &u32InFramePhyAddr, &u64InFrameVirAddr);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Alloc input buffer failed.\n");
        return -1;
    }

    kdRet = KD_MPI_SYS_Alloc(pstSysInfo, u32OutFrameSize, &u32OutFramePhyAddr, &u64OutFrameVirAddr);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Alloc output buffer failed.\n");
        return -1;
    }

    pstVpsTaskAttr->stImgIn.u64PhyData = u32InFramePhyAddr;
    pstVpsTaskAttr->stImgIn.u64VirData = u64InFrameVirAddr;

    pstVpsTaskAttr->stImgOut.u64PhyData = u32OutFramePhyAddr;
    pstVpsTaskAttr->stImgOut.u64VirData = u64OutFrameVirAddr;

    return 0;
}

static int FreeFrameBuffer(SAMPLE_VIO_CONTEXT_S *pstSampleVpsCtx, VPS_TASK_ATTR_S *pstVpsTaskAttr, SYS_INFO_S *pstSysInfo)
{
    KD_U32 u32InFrameSize;
    KD_U32 u32OutFrameSize;

    if (pstSampleVpsCtx->enInPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32InFrameSize = pstSampleVpsCtx->u32InputPicWidth * pstSampleVpsCtx->u32InputPicHeight * 3 / 2;
    }
    // if (pstSampleVpsCtx->enOutPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32OutFrameSize = pstSampleVpsCtx->u32OutputPicWidth * pstSampleVpsCtx->u32OutputPicHeight * 3 / 2;
    }

    KD_RET kdRet = KD_MPI_SYS_Free(pstSysInfo, u32InFrameSize, pstVpsTaskAttr->stImgIn.u64PhyData, pstVpsTaskAttr->stImgIn.u64VirData);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Free input buffer failed.\n");
        return -1;
    }

    kdRet = KD_MPI_SYS_Free(pstSysInfo, u32OutFrameSize, pstVpsTaskAttr->stImgOut.u64PhyData, pstVpsTaskAttr->stImgOut.u64VirData);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Free output buffer failed.\n");
        return -1;
    }

    return 0;
}

static void signalHandler(int signal __attribute__((__unused__)))
{
	done = 1;
}

static int sampleVioSysInit(SYS_INFO_S *pstSysInfo)
{
    KD_S32 kdRet = KD_SUCCESS;

    kdRet = KD_MPI_SYS_Init(pstSysInfo);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Init failed.\n");
        return KD_FAILURE;
    }

    kdRet = KD_MPI_VI_Init();
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VI_Init failed.\n");
        return KD_FAILURE;
    }

    kdRet = KD_MPI_VPS_Init(&pstSysInfo->s32MemFd);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_Init failed.\n");
        return KD_FAILURE;
    }

	kdRet = KD_MPI_VO_Init();
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VO_Init failed.\n");
        return KD_FAILURE;
    }

    return kdRet;
}

static KD_S32 sampleViStart(KD_S32 devId, SAMPLE_VIO_CONTEXT_S *pstSampleVioCtx)
{
    KD_S32 kdRet = KD_SUCCESS;
    KD_S32 subPipeIdx = -1;

    VI_DEV_ATTR_S stViDevAttr;
    memset(&stViDevAttr, 0, sizeof(VI_DEV_ATTR_S));

    kdRet = KD_MPI_VI_GetDevAttr(devId, &stViDevAttr);
    if (kdRet != KD_SUCCESS)
    {
        printf("set vi attribute failed.\n");
        return KD_FAILURE;
    }

    VI_SUB_PIPE_ATTR_S stSubPipeAttr;
    memset(&stSubPipeAttr, 0, sizeof(VI_SUB_PIPE_ATTR_S));
    for (int subIdx = 0; subIdx < MAX_SUB_PIPE_NUM; subIdx++)
    {
        if (stViDevAttr.u32SubDevEnabled[subIdx])
        {
            stSubPipeAttr.enPixFmt = stViDevAttr.enSubDevPixFmt[subIdx];
            stSubPipeAttr.u32Width = stViDevAttr.u32SubDevWidth[subIdx];
            stSubPipeAttr.u32Height = stViDevAttr.u32SubDevHeight[subIdx];
            strcpy(stSubPipeAttr.subDevName, stViDevAttr.subDevName[subIdx]);

            pstSampleVioCtx->u32InputPicHeight = stSubPipeAttr.u32Height;
            pstSampleVioCtx->u32InputPicWidth = stSubPipeAttr.u32Width;
            pstSampleVioCtx->enInPixelFmt = PIXEL_FORMAT_NV12;

            kdRet = KD_MPI_VI_CreateSubPipe(subIdx, &stSubPipeAttr);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi device enable failed.\n");
                return KD_FAILURE;
            }

            kdRet = KD_MPI_VI_StartSubPipe(subIdx);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi sub pipe start failed.\n");
                return KD_FAILURE;
            }

            subPipeIdx = subIdx;
            break;
        }
    }

    return subPipeIdx;
}

static KD_S32 sampleVoStart(KD_S32 devId, KD_S32 VoLayer1, SAMPLE_VIO_CONTEXT_S *pstSampleVioCtx)
{
    KD_S32 kdRet = KD_SUCCESS;
    KD_U32 u32OutPhyAddr;
    KD_U64 u64OutVirAddr;

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

    VO_VIDEO_LAYER_ATTR_S stVoBaseLayerAttr;
	memset(&stVoBaseLayerAttr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stVoBaseLayerAttr.enPixelFormat = pstSampleVioCtx->enInPixelFmt;
	stVoBaseLayerAttr.u32PicWidth = pstSampleVioCtx->u32OutputPicWidth;
	stVoBaseLayerAttr.u32PicHeight = pstSampleVioCtx->u32OutputPicHeight;
    stVoBaseLayerAttr.u32OffsetX = 0;
    stVoBaseLayerAttr.u32OffsetY = 0;
    stVoBaseLayerAttr.u32Bpp = 8;

    kdRet = KD_MPI_VO_EnableVideoLayer(VoLayer1, &stVoBaseLayerAttr);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo base layer enable failed.\n");
		return KD_FAILURE;
	}

    return kdRet;
}

static KD_S32 sampleVpsEnable(KD_S32 *pVpsHandle, VPS_TASK_ATTR_S *pstVpsAttr, SYS_INFO_S *pstSysInfo, SAMPLE_VIO_CONTEXT_S *pstSampleVioCtx)
{
    KD_S32 kdRet = KD_SUCCESS;

    kdRet = KD_MPI_VPS_BeginJob(pVpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_BeginJob failed.\n");
        return KD_FAILURE;
    }

    if (allocFrameBuffer(pstSampleVioCtx, pstVpsAttr, pstSysInfo) != 0)
    {
        printf("allocFrameBuffer failed.\n");
        return KD_FAILURE;
    }

    return kdRet;
}

static KD_S32 sampleVpsEnd(KD_S32 vpsHandle, VPS_TASK_ATTR_S *pstVpsAttr, SYS_INFO_S *pstSysInfo, SAMPLE_VIO_CONTEXT_S *pstSampleVioCtx)
{
    KD_S32 kdRet = KD_SUCCESS;

    kdRet = KD_MPI_VPS_EndJob(vpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_EndJob faile.\n");
        return -1;
    }

    kdRet = KD_MPI_VPS_CancelJob(vpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_CancelJob faile.\n");
        return -1;
    }

    // free vps
    if (FreeFrameBuffer(pstSampleVioCtx, pstVpsAttr, pstSysInfo) != 0)
    {
        printf("FreeFrameBuffer failed.\n");
        return -1;
    }

	kdRet = KD_MPI_VPS_DeInit();
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_DeInit faile.\n");
        return -1;
    }
}

static KD_S32 sampleVoEnd(KD_S32 devId, KD_S32 VoLayer1)
{
    KD_S32 kdRet = KD_SUCCESS;

    kdRet = KD_MPI_VO_DisableVideoLayer(VoLayer1);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return KD_FAILURE;
	}

    kdRet = KD_MPI_VO_Disable(devId);
	if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return KD_FAILURE;
	}

	KD_MPI_VO_Deinit();

    return kdRet;
}

static KD_S32 sampleViEnd(KD_S32 s32SubPipeIdx)
{
    KD_U32 kdRet = KD_SUCCESS;

    kdRet = KD_MPI_VI_StopSubPipe(s32SubPipeIdx);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device stop failed.\n");
        return KD_FAILURE;
    }

    kdRet = KD_MPI_VI_DestroySubPipe(s32SubPipeIdx);
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device diable failed.\n");
        return KD_FAILURE;
    }

    kdRet = KD_MPI_VI_Deinit();
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device deinit failed.\n");
        return KD_FAILURE;
    }

    return kdRet;
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

    SAMPLE_VIO_CONTEXT_S stSampleVioCtx;
    memset(&stSampleVioCtx, 0, sizeof(SAMPLE_VIO_CONTEXT_S));

    if (parse_cmdline(argc, argv, &stSampleVioCtx) != 0)
    {
        printf("parse cmdline argument failed.\n");
        return -1;
    }

	signal(SIGINT, signalHandler);

	SYS_INFO_S stSysInfo;
    memset(&stSysInfo, 0, sizeof(SYS_INFO_S));

    kdRet = sampleVioSysInit(&stSysInfo);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample vio sys init failed.\n");
        return KD_FAILURE;
    }

    KD_S32 DevId = 0;
    int subPipeIndex = sampleViStart(DevId, &stSampleVioCtx);
    if (subPipeIndex < 0)
    {
        printf("sample vi start failed.\n");
        goto VI_OUT;
    }

    KD_S32 hVpsHandle = -1;
    VPS_TASK_ATTR_S stVpsTaskAttr;
    memset(&stVpsTaskAttr, 0, sizeof(VPS_TASK_ATTR_S));

    kdRet = sampleVpsEnable(&hVpsHandle, &stVpsTaskAttr, &stSysInfo, &stSampleVioCtx);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample vps enable failed.\n");
        goto VPS_OUT;
    }

    KD_S32 VoLayer1 = 0;
    kdRet = sampleVoStart(DevId, VoLayer1, &stSampleVioCtx);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample vo start failed.\n");
        goto ALL_OUT;
    }


    VIDEO_FRAME_INFO_S stFrameInfo;
    memset(&stFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));
    
    while (!done)
    {
        kdRet = KD_MPI_VI_GetSubPipeFrame(subPipeIndex, &stFrameInfo, -1);
        if (kdRet != KD_SUCCESS)
        {
            printf("get vi frame failed.\n");
            continue;
        }

		//to vps
		memcpy((void *)stVpsTaskAttr.stImgIn.u64VirData, (void *)stFrameInfo.u64VirData, stFrameInfo.u32DataSize);
		if (stSampleVioCtx.enVpsTaskType == TASK_TYPE_SCALE)
        {
            kdRet = KD_MPI_VPS_AddScaleTask(hVpsHandle, &stVpsTaskAttr);
            if (kdRet != KD_SUCCESS)
            {
                printf("KD_MPI_VPS_AddScaleTask faile.\n");
                goto ALL_OUT;
            }
        }

		// to vo
		kdRet = KD_MPI_VO_SendFrame(VoLayer1, &stVpsTaskAttr.stImgOut);
		if (kdRet != KD_SUCCESS)
		{
			printf("send frame failed.\n");
			continue;
		}
        kdRet = KD_MPI_VO_FrameLayerSync(DevId);
        if (kdRet != KD_SUCCESS)
		{
			printf("vo frame layer sync failed.\n");
			goto ALL_OUT;
		}


        kdRet = KD_MPI_VI_ReleaseSubPipeFrame(subPipeIndex, &stFrameInfo);
        if (kdRet != KD_SUCCESS)
        {
            printf("get vi frame failed.\n");
            break;
        }
    }

ALL_OUT:
    kdRet = sampleVoEnd(DevId, VoLayer1);
    if (kdRet != KD_SUCCESS)
    {
        printf("get vo end failed.\n");
        return -1;
    }

VPS_OUT:
    kdRet = sampleVpsEnd(hVpsHandle, &stVpsTaskAttr, &stSysInfo, &stSampleVioCtx);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample vps end failed.\n");
        return -1;
    }

    kdRet = KD_MPI_SYS_Deinit(&stSysInfo);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Deinit failed.\n");
        return -1;
    }

VI_OUT:
    kdRet = sampleViEnd(subPipeIndex);
    if (kdRet != KD_SUCCESS)
    {
        printf("sample vi end failed.\n");
        return -1;
    }

    return 0;
}