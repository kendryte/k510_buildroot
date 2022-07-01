#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "kd_vps.h"
#include "kd_sys.h"

typedef enum kdTASK_TYPE_E
{
    TASK_TYPE_SCALE = 0,
    TASK_TYPE_ROTATION,
    TASK_TYPE_BUTT,
} TASK_TYPE_E;

typedef struct kdSAMPLE_VPS_CONTEXT_S
{
    FILE                *inputFile;
    FILE                *outputFile;
    PIXEL_FORMAT_E      enInPixelFmt;
    PIXEL_FORMAT_E      enOutPixelFmt;
    KD_U32              u32InputPicWidth;
    KD_U32              u32InputPicHeight;
    KD_U32              u32OutputPicWidth;
    KD_U32              u32OutputPicHeight;
    TASK_TYPE_E         enTaskType;
} SAMPLE_VPS_CONTEXT_S;

static void help()
{
    printf("-help: print the help info.\n");
    printf("-i: the input source file, xxx.yuv/xxx.rgb.\n");
    printf("-type: the task type, scale or rotation.\n");
    printf("-inFmt: the input picture pixel format.\n");
    printf("-outFmt: the output picture pixel format.\n");
    printf("-inputW: the input picture width.\n");
    printf("-inputH: the input picture height.\n");
    printf("-o: the output file, xxx.yuv/xxx.rgb\n");
    printf("-outputW: the output picture width.\n");
    printf("-outputH: the output picture height.\n");
}

static KD_S32 parse_cmdline(int argc, char *argv[], SAMPLE_VPS_CONTEXT_S *pstSampelVpsCtx)
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            pstSampelVpsCtx->inputFile = fopen(argv[i+1], "r+b");
            if (pstSampelVpsCtx->inputFile == NULL)
            {
                printf("input file open failed.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            pstSampelVpsCtx->outputFile = fopen(argv[i+1], "w+b");
            if (pstSampelVpsCtx->outputFile == NULL)
            {
                printf("output file open failed.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-type") == 0)
        {
            if (strcmp(argv[i+1], "scale") == 0)
            {
                pstSampelVpsCtx->enTaskType = TASK_TYPE_SCALE;
            }
            else if (strcmp(argv[i+1], "rotation") == 0)
            {
                pstSampelVpsCtx->enTaskType = TASK_TYPE_ROTATION;
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
                pstSampelVpsCtx->enInPixelFmt = PIXEL_FORMAT_NV12;
            }
            else if (strcmp(argv[i+1], "yuv422sp") == 0)
            {
                pstSampelVpsCtx->enInPixelFmt = PIXEL_FORMAT_YUV422SP;
            }
            else if (strcmp(argv[i+1], "rgb") == 0)
            {
                pstSampelVpsCtx->enInPixelFmt = PIXEL_FORMAT_RGB888;
            }
            else
            {
                printf("the input file pixel format is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-outFmt") == 0)
        {
            if (strcmp(argv[i+1], "nv12") == 0)
            {
                pstSampelVpsCtx->enOutPixelFmt = PIXEL_FORMAT_NV12;
            }
            else if (strcmp(argv[i+1], "yuv422sp") == 0)
            {
                pstSampelVpsCtx->enOutPixelFmt = PIXEL_FORMAT_YUV422SP;
            }
            else if (strcmp(argv[i+1], "rgb") == 0)
            {
                pstSampelVpsCtx->enOutPixelFmt = PIXEL_FORMAT_RGB888;
            }
            else
            {
                printf("the output file pixel format is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-inputW") == 0)
        {
            pstSampelVpsCtx->u32InputPicWidth = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-inputH") == 0)
        {
            pstSampelVpsCtx->u32InputPicHeight = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-outputW") == 0)
        {
            pstSampelVpsCtx->u32OutputPicWidth = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-outputH") == 0)
        {
            pstSampelVpsCtx->u32OutputPicHeight = atoi(argv[i+1]);
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

static int getInFrameData(SAMPLE_VPS_CONTEXT_S *pstSampleVpsCtx, VPS_TASK_ATTR_S *pstVpsTaskAttr)
{
    if (pstSampleVpsCtx->inputFile == NULL)
    {
        printf("input file is invalid.\n");
        return -1;
    }

    KD_U32 u32FrameSize;
    if (pstSampleVpsCtx->enInPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32FrameSize = pstSampleVpsCtx->u32InputPicWidth *  pstSampleVpsCtx->u32InputPicHeight * 3 / 2;
    }

    size_t retSize = fread((void*)pstVpsTaskAttr->stImgIn.u64VirData, 1, u32FrameSize, pstSampleVpsCtx->inputFile);
    if (retSize == 0 || retSize < u32FrameSize)
    {
        printf("input file has no data to read, or the frame data is incomplete.\n");
        return -1;
    }

    return 0;
}

static int FreeFrameBuffer(SAMPLE_VPS_CONTEXT_S *pstSampleVpsCtx, VPS_TASK_ATTR_S *pstVpsTaskAttr, SYS_INFO_S *pstSysInfo)
{
    KD_U32 u32InFrameSize;
    KD_U32 u32OutFrameSize;

    if (pstSampleVpsCtx->enInPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32InFrameSize = pstSampleVpsCtx->u32InputPicWidth * pstSampleVpsCtx->u32InputPicHeight * 3 / 2;
    }
    if (pstSampleVpsCtx->enOutPixelFmt == PIXEL_FORMAT_NV12)
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

static int allocFrameBuffer(SAMPLE_VPS_CONTEXT_S *pstSampleVpsCtx, VPS_TASK_ATTR_S *pstVpsTaskAttr, SYS_INFO_S *pstSysInfo)
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
    if (pstSampleVpsCtx->enOutPixelFmt == PIXEL_FORMAT_NV12)
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

int main(int argc, char *argv[])
{
    KD_RET kdRet = KD_SUCCESS;

    if (argc < 2 || strcmp(argv[1], "-help") == 0)
    {
        printf("the cmdline arguments is invalid, please check...\n");
        help();
        return 0;
    }

    SAMPLE_VPS_CONTEXT_S stSampleVpsCtx;
    memset(&stSampleVpsCtx, 0, sizeof(SAMPLE_VPS_CONTEXT_S));

    if (parse_cmdline(argc, argv, &stSampleVpsCtx) != 0)
    {
        printf("parse cmdline argument failed.\n");
        return -1;
    }

    SYS_INFO_S stSysInfo;
    memset(&stSysInfo, 0, sizeof(SYS_INFO_S));

    kdRet = KD_MPI_SYS_Init(&stSysInfo);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Init failed.\n");
        return -1;
    }

    kdRet = KD_MPI_VPS_Init(&stSysInfo.s32MemFd);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_Init failed.\n");
        return -1;
    }

    VPS_HANDLE hVpsHandle = -1;
    kdRet = KD_MPI_VPS_BeginJob(&hVpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_BeginJob failed.\n");
        return -1;
    }

    VPS_TASK_ATTR_S stVpsTaskAttr;
    memset(&stVpsTaskAttr, 0, sizeof(VPS_TASK_ATTR_S));

    if (allocFrameBuffer(&stSampleVpsCtx, &stVpsTaskAttr, &stSysInfo) != 0)
    {
        printf("allocFrameBuffer failed.\n");
        return -1;
    }

    KD_U32 u32OutFrameSize;
    if (stSampleVpsCtx.enOutPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32OutFrameSize = stVpsTaskAttr.stImgOut.u32Width * stVpsTaskAttr.stImgOut.u32Height * 3 / 2;
    }

    for (int num = 0; num < 10; num++)
    {
        if (getInFrameData(&stSampleVpsCtx, &stVpsTaskAttr) != 0)
        {
            printf("getInFrameData failed.\n");
            break;
        }

        KD_U32 u32FrameSize = stSampleVpsCtx.u32InputPicWidth *  stSampleVpsCtx.u32InputPicHeight * 3 / 2;

        if (stSampleVpsCtx.enTaskType == TASK_TYPE_SCALE)
        {
            kdRet = KD_MPI_VPS_AddScaleTask(hVpsHandle, &stVpsTaskAttr);
            if (kdRet != KD_SUCCESS)
            {
                printf("KD_MPI_VPS_AddScaleTask faile.\n");
                return -1;
            }
        }
        else if (stSampleVpsCtx.enTaskType == TASK_TYPE_ROTATION)
        {
            kdRet = KD_MPI_VPS_AddRotationTask(hVpsHandle, &stVpsTaskAttr, ROTATION_90);
            if (kdRet != KD_SUCCESS)
            {
                printf("KD_MPI_VPS_AddRotationTask faile.\n");
                return -1;
            }
        }

        // write to output file
    
        fwrite((void*)stVpsTaskAttr.stImgOut.u64VirData, 1, u32OutFrameSize, stSampleVpsCtx.outputFile);
    }

    kdRet = KD_MPI_VPS_EndJob(hVpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_EndJob faile.\n");
        return -1;
    }

    kdRet = KD_MPI_VPS_CancelJob(hVpsHandle);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_VPS_CancelJob faile.\n");
        return -1;
    }

    if (FreeFrameBuffer(&stSampleVpsCtx, &stVpsTaskAttr, &stSysInfo) != 0)
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

    kdRet = KD_MPI_SYS_Deinit(&stSysInfo);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Deinit failed.\n");
        return -1;
    }

    return 0;
}