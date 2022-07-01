#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "kd_venc.h"
#include "kd_sys.h"

#define SHARE_MEMORY_DEV "/dev/k510-share-memory"
#define DEV_NAME_DDR "/dev/mem"
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)

typedef struct kdSAMPLE_CONTEXT_S
{
    VENC_TYPE_E             enType;
    FILE                    *inputFile;
    FILE                    *outputFile;
    KD_U32                  u32Width;
    KD_U32                  u32Height;
    KD_U32                  u32ChnNum;
    VENC_PROFILE_E          enProfile;
    KD_U32                  u32Level;
    PIXEL_FORMAT_E          enPixelFmt;
    VENC_RC_MODE_E          enRcMode;
    KD_U32                  u32Fps;
    KD_S32                  s32Qp;
    KD_U32                  u32GopLen;
    KD_U32                  u32Bitrate;
    KD_S32                  s32FdSharedMemory;
    KD_S32                  s32FdDdr;
} SAMPLE_CONTEXT_S;

typedef struct kdSHARED_MEMROY_ALLOC_ARGS {
    KD_U32      u32Size;
    KD_U32      u32Alignment;
    KD_U32      u32PhyAddr;
} SHARED_MEMROY_ALLOC_ARGS;

static void help()
{
    printf("-help: print the help info.\n");
    printf("-t: the encoder type, h264.\n");
    printf("-n: the encode channel number.\n");
    printf("-w: the encode picture width.\n");
    printf("-h: the encode picture height.\n");
    printf("-p: the encode profile, baseline/main/high/jpeg.\n");
    printf("-l: the encode level, 10...51, 51 is level5.1\n");
    printf("-i: the encode input file, xxx.yuv.\n");
    printf("-o: the encode stream file, xxx.264/xxx.jpg.\n");
    printf("-fmt: the encode frame pixel format, yuv420/nv12.\n");

    printf("-rc: the encode rate control type, cbr/vbr/fixqp.\n");
    printf("-fps: the encode frame rate.\n");
    printf("-qp: the encoder qp, 0...51.\n");
    printf("-goplen: the encoder gop size, 1...250.\n");
    printf("-bitrate: the encoder bit rate, for cbr it means constant bitrate, and for vbr it means max bitrate, up to 5Mbps.\n");
}

static KD_S32 parse_cmdline(int argc, char *argv[], SAMPLE_CONTEXT_S *pSampleCtx)
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            pSampleCtx->inputFile = fopen(argv[i+1], "r+b");
            if (pSampleCtx->inputFile == NULL)
            {
                printf("input file open failed.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            pSampleCtx->outputFile = fopen(argv[i+1], "w+b");
            if (pSampleCtx->outputFile == NULL)
            {
                printf("output file open failed.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (strcmp(argv[i+1], "h264") == 0)
            {
                pSampleCtx->enType = VENC_TYPE_H264;
            }
            else if (strcmp(argv[i+1], "jpeg") == 0)
            {
                pSampleCtx->enType = VENC_TYPE_JPEG;
            }
            else
            {
                printf("the type is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            pSampleCtx->u32ChnNum = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-w") == 0)
        {
            pSampleCtx->u32Width = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            pSampleCtx->u32Height = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            if (strcmp(argv[i+1], "baseline") == 0)
            {
                pSampleCtx->enProfile = VENC_PROFILE_BASELINE;
            }
            else if (strcmp(argv[i+1], "main") == 0)
            {
                pSampleCtx->enProfile = VENC_PROFILE_MAIN;
            }
            else if (strcmp(argv[i+1], "high") == 0)
            {
                pSampleCtx->enProfile = VENC_PROFILE_HIGH;
            }
            else if (strcmp(argv[i+1], "jpeg") == 0)
            {
                pSampleCtx->enProfile = VENC_PROFILE_JPEG;
            }
            else
            {
                printf("the profile is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            pSampleCtx->u32Level = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-fmt") == 0)
        {
            if (strcmp(argv[i+1], "yuv420") == 0)
            {
                pSampleCtx->enPixelFmt = PIXEL_FORMAT_YUV420;
            }
            else if (strcmp(argv[i+1], "yuv400") == 0)
            {
                pSampleCtx->enPixelFmt = PIXEL_FORMAT_YUV400;
            }
            else if (strcmp(argv[i+1], "nv12") == 0)
            {
                pSampleCtx->enPixelFmt = PIXEL_FORMAT_NV12;
            }
            else
            {
                printf("the pixel format is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-rc") == 0)
        {
            if (strcmp(argv[i+1], "cbr") == 0)
            {
                pSampleCtx->enRcMode = VENC_RC_MODE_CBR;
            }
            else if (strcmp(argv[i+1], "vbr") == 0)
            {
                pSampleCtx->enRcMode = VENC_RC_MODE_VBR;
            }
            else if (strcmp(argv[i+1], "fixqp") == 0)
            {
                pSampleCtx->enRcMode = VENC_RC_MODE_FIXQP;
            }
            else
            {
                printf("the rc mode is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-fps") == 0)
        {
            pSampleCtx->u32Fps = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-qp") == 0)
        {
            pSampleCtx->s32Qp = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-goplen") == 0)
        {
            pSampleCtx->u32GopLen = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-bitrate") == 0)
        {
            pSampleCtx->u32Bitrate = atoi(argv[i+1]);
        }
    }

    return 0;
}

static unsigned int allocMemory(KD_S32 fdSharedMemory, KD_U32 size)
{
    SHARED_MEMROY_ALLOC_ARGS  stSharedMem;

    stSharedMem.u32Size = (size + 0xfff) & (~0xfff);
    stSharedMem.u32Alignment = 4096;
    stSharedMem.u32PhyAddr = 0;

    if (ioctl(fdSharedMemory, SHARE_MEMORY_ALIGN_ALLOC, &stSharedMem) < 0)
    {
        printf("alloc frame memory failed.\n");
        return -1;
    }

    return stSharedMem.u32PhyAddr;
}

static int getFrameData(SAMPLE_CONTEXT_S *pSampleCtx, VIDEO_FRAME_INFO_S *pFrameInfo)
{
    if (pSampleCtx->inputFile == NULL)
    {
        printf("input file is invalid.\n");
        return -1;
    }

    KD_U32 u32FrameSize;

    if (pFrameInfo->enPixelFormat == PIXEL_FORMAT_YUV420 ||
        pFrameInfo->enPixelFormat == PIXEL_FORMAT_NV12)
    {
        u32FrameSize = pFrameInfo->u32Width * pFrameInfo->u32Height * 3 / 2;
    }

    size_t retSize = fread((void*)pFrameInfo->u64VirData, 1, u32FrameSize, pSampleCtx->inputFile);
    if (retSize == 0 || retSize < u32FrameSize)    
    {
        printf("the input file has not data to read, or the frame data is incomplete.\n");
        return -1;
    }

    return 0;
}

static int freeFrameBuffer(SAMPLE_CONTEXT_S *pSampleCtx, VIDEO_FRAME_INFO_S *pFrameInfo, SYS_INFO_S *pstSysInfo)
{
    KD_U32 u32FrameSize;
    if (pFrameInfo->enPixelFormat == PIXEL_FORMAT_NV12)
    {
        u32FrameSize = pFrameInfo->u32Width * pFrameInfo->u32Height * 3 / 2;
    }
    else
    {
        printf("the pixel format %d is not support.\n", pSampleCtx->enPixelFmt);
        return -1;
    }

    KD_RET kdRet = KD_MPI_SYS_Free(pstSysInfo, u32FrameSize, pFrameInfo->u64PhyData, pFrameInfo->u64VirData);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Free input buffer failed.\n");
        return -1;
    }
    
    return 0;
}

static int allocFrameBuffer(SAMPLE_CONTEXT_S *pSampleCtx, VIDEO_FRAME_INFO_S *pFrameInfo, SYS_INFO_S *pstSysInfo)
{
    KD_U32 u32FramePhyAddr;
    KD_U64 u64FrameVirAddr;
    KD_U32 u32FrameBufferSize;

    if (pSampleCtx->enPixelFmt == PIXEL_FORMAT_NV12)
    {
        u32FrameBufferSize = pSampleCtx->u32Width * pSampleCtx->u32Height * 3 /2;
    }
    else
    {
        printf("the pixel format %d is not support.\n", pSampleCtx->enPixelFmt);
        return -1;
    }

    KD_RET kdRet = KD_MPI_SYS_Alloc(pstSysInfo, u32FrameBufferSize, &u32FramePhyAddr, &u64FrameVirAddr);
    if (kdRet != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Alloc input buffer failed.\n");
        return -1;
    }

    pFrameInfo->u64PhyData = u32FramePhyAddr;
    pFrameInfo->u64VirData = u64FrameVirAddr;

    return 0;
}

int main(int argc, char *argv[])
{
    KD_S32 s32Ret = KD_SUCCESS;

    if (argc < 2 || strcmp(argv[1], "-help") == 0)
    {
        printf("the cmdline arguments is invalid, please check...\n");
        help();
        return 0;
    }

    SAMPLE_CONTEXT_S stSampleCtx;
    memset(&stSampleCtx, 0, sizeof(SAMPLE_CONTEXT_S));

    VENC_CHN_ATTR_S vencAttr;
    memset(&vencAttr, 0, sizeof(VENC_CHN_ATTR_S));

    if (parse_cmdline(argc, argv, &stSampleCtx) != 0)
    {
        printf("parse cmdline argument failed.\n");
        return -1;
    }

    VENC_CHN_ATTR_S stVencChnAttr;
    memset(&stVencChnAttr, 0, sizeof(VENC_CHN_ATTR_S));

    stVencChnAttr.stVencAttr.enType = stSampleCtx.enType;
    stVencChnAttr.stVencAttr.u32PicWidth = stSampleCtx.u32Width;
    stVencChnAttr.stVencAttr.u32PicHeight = stSampleCtx.u32Height;
    if (stSampleCtx.enType == VENC_TYPE_H264)
    {
        if (stSampleCtx.enProfile == VENC_PROFILE_JPEG)
        {
            printf("h264 type not support jpeg profile %d.\n", stSampleCtx.enProfile);
            return -1;
        }
        stVencChnAttr.stVencAttr.enProfile = stSampleCtx.enProfile;
        stVencChnAttr.stVencAttr.u32Level = stSampleCtx.u32Level;
        stVencChnAttr.stRcAttr.enRcMode = stSampleCtx.enRcMode;
        stVencChnAttr.stRcAttr.s32InitQp = stSampleCtx.s32Qp;
        switch (stSampleCtx.enRcMode)
        {
            case VENC_RC_MODE_CBR:
            {
                stVencChnAttr.stRcAttr.stAttrCbr.u32GopLen = stSampleCtx.u32GopLen;
                stVencChnAttr.stRcAttr.stAttrCbr.u32SrcFrameRate = stSampleCtx.u32Fps;
                stVencChnAttr.stRcAttr.stAttrCbr.u32DstFrameRate = stSampleCtx.u32Fps;
                stVencChnAttr.stRcAttr.stAttrCbr.u32BitRate = stSampleCtx.u32Bitrate;
                break;
            }
            case VENC_RC_MODE_VBR:
            {
                stVencChnAttr.stRcAttr.stAttrVbr.u32GopLen = stSampleCtx.u32GopLen;
                stVencChnAttr.stRcAttr.stAttrVbr.u32SrcFrameRate = stSampleCtx.u32Fps;
                stVencChnAttr.stRcAttr.stAttrVbr.u32DstFrameRate = stSampleCtx.u32Fps;
                stVencChnAttr.stRcAttr.stAttrVbr.u32MaxBitRate = stSampleCtx.u32Bitrate;
                break;
            }
            case VENC_RC_MODE_FIXQP:
            {
                stVencChnAttr.stRcAttr.stAttrFixQp.u32GopLen = stSampleCtx.u32GopLen;
                stVencChnAttr.stRcAttr.stAttrFixQp.u32SrcFrameRate = stSampleCtx.u32Fps;
                stVencChnAttr.stRcAttr.stAttrFixQp.u32DstFrameRate = stSampleCtx.u32Fps;
                break;
            }
            default:
            {
                printf("the rc mode %d is not supportted.\n", stSampleCtx.enRcMode);
                break;
            }
        }
    }
    else if (stSampleCtx.enType == VENC_TYPE_JPEG)
    {
        if (stSampleCtx.enProfile != VENC_PROFILE_JPEG)
        {
            printf("jpeg type not support h264 profile %d.\n", stSampleCtx.enProfile);
            return -1;
        }
        stVencChnAttr.stVencAttr.enProfile = stSampleCtx.enProfile;
        stVencChnAttr.stVencAttr.u32PicWidth = stSampleCtx.u32Width;
        stVencChnAttr.stVencAttr.u32PicHeight = stSampleCtx.u32Height;
    }
    else
    {
        printf("encode type %d is not supportted.\n", stSampleCtx.enType);
        return -1;
    }

    SYS_INFO_S stSysInfo;
    memset(&stSysInfo, 0, sizeof(SYS_INFO_S));

    s32Ret = KD_MPI_SYS_Init(&stSysInfo);
    if (s32Ret != KD_SUCCESS)
    {
        printf("KD_MPI_SYS_Init failed.\n");
        return -1;
    }

    s32Ret = KD_MPI_VENC_Init();
    if (s32Ret != KD_SUCCESS)
    {
        printf("chn %d encoder init failed.\n", 0);
        return -1;
    }

    KD_U32 u32ChnNum = 1;
    KD_U32 u32SendFrameNum = 0;
    KD_U32 u32RecvFrameNum = 0;
    if (stSampleCtx.u32ChnNum > 0)
        u32ChnNum = stSampleCtx.u32ChnNum;

    //now is only one channel and synchronous. TODO: support multichannel encode and asynchronous
    {
        s32Ret = KD_MPI_VENC_CreateChn(0, &stVencChnAttr);
        if (s32Ret != KD_SUCCESS)
        {
            printf("chn %d create failed.\n", 0);
            return -1;
        }

        VENC_RECV_PIC_PARAM_S stRecvParm;
        memset(&stRecvParm, 0, sizeof(VENC_RECV_PIC_PARAM_S));
        stRecvParm.s32RecvPicNum = -1;

        s32Ret = KD_MPI_VENC_StartRecvFrame(0, &stRecvParm);
        if (s32Ret != KD_SUCCESS)
        {
            printf("chn %d start recv frame failed.\n", 0);
            return -1;
        }

        VIDEO_FRAME_INFO_S frameInfo;
        memset(&frameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));
        frameInfo.enPixelFormat = stSampleCtx.enPixelFmt;
        frameInfo.u32Width = stSampleCtx.u32Width;
        frameInfo.u32Height = stSampleCtx.u32Height;

        if (allocFrameBuffer(&stSampleCtx, &frameInfo, &stSysInfo) != 0)
        {
            printf("alloc frame buffer failed.\n");
            return -1;
        }

        while (1)
        {
            if (getFrameData(&stSampleCtx, &frameInfo) != 0)
            {
                printf("no data to read.\n");
                break;
            }

            s32Ret = KD_MPI_VENC_SendFrame(0, &frameInfo, -1);
            if (s32Ret != KD_SUCCESS)
            {
                printf("chn %d sendframe failed.\n", 0);
                return -1;
            }
            u32SendFrameNum++;

            // TODO: multi thread
            VENC_STREAM_S stStream;
            memset(&stStream, 0, sizeof(VENC_STREAM_S));

            while (1)
            {
                s32Ret = KD_MPI_VENC_GetStream(0, &stStream);
                if (s32Ret != KD_SUCCESS)
                {
                    usleep(1000);
                    continue;
                }

                u32RecvFrameNum++;
                // write stream to output file
                fwrite(stStream.pu8Addr, 1, stStream.u32Len, stSampleCtx.outputFile);

                s32Ret = KD_MPI_VENC_ReleaseStream(0, &stStream);
                if (s32Ret != KD_SUCCESS)
                {
                    printf("chn %d release stream buffer failed.\n", 0);
                    return -1;
                }
                break;
            }
        }

        s32Ret = KD_MPI_VENC_StopRecvFrame(0);
        if (s32Ret != KD_SUCCESS)
        {
            printf("chn %d stop recv frame failed.\n", 0);
            return -1;
        }

        // destory
        if (freeFrameBuffer(&stSampleCtx, &frameInfo, &stSysInfo) != 0)
        {
            printf("free frame buffer failed.\n");
            return -1;
        }

        s32Ret = KD_MPI_VENC_DestroyChn(0);
        if (s32Ret != KD_SUCCESS)
        {
            printf("chn %d release stream buffer failed.\n", 0);
            return -1;
        }

        s32Ret = KD_MPI_VENC_Deinit();
        if (s32Ret != KD_SUCCESS)
        {
            printf("chn %d encoder deinit failed.\n", 0);
            return -1;
        }

        s32Ret = KD_MPI_SYS_Deinit(&stSysInfo);
        if (s32Ret != KD_SUCCESS)
        {
            printf("KD_MPI_SYS_Deinit failed.\n");
            return -1;
        }

        printf("total send %d frames, and receive %d streams.\n", u32SendFrameNum, u32RecvFrameNum);

        fclose(stSampleCtx.inputFile);
        fclose(stSampleCtx.outputFile);
    }

    return 0;
}