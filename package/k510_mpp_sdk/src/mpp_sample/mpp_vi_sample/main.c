#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kd_vi.h"

int main(int argc, char **argv)
{
    KD_RET kdRet = KD_SUCCESS;

    KD_MPI_VI_Init();

    VI_DEV_ATTR_S stViDevAttr;
    memset(&stViDevAttr, 0, sizeof(VI_DEV_ATTR_S));

    VI_DEV ViDev = 0;
    kdRet = KD_MPI_VI_GetDevAttr(ViDev, &stViDevAttr);
    if (kdRet != KD_SUCCESS)
    {
        printf("set vi attribute failed.\n");
        return -1;
    }

    VI_SUB_PIPE_ATTR_S stSubPipeAttr;
    memset(&stSubPipeAttr, 0, sizeof(VI_SUB_PIPE_ATTR_S));

    for (int subIdx = 0; subIdx < MAX_SUB_PIPE_NUM; subIdx++)
    {
        if (stViDevAttr.u32SubDevEnabled[subIdx])
        {
            KD_CHAR filename[128];
            
            stSubPipeAttr.enPixFmt = stViDevAttr.enSubDevPixFmt[subIdx];
            stSubPipeAttr.u32Width = stViDevAttr.u32SubDevWidth[subIdx];
            stSubPipeAttr.u32Height = stViDevAttr.u32SubDevHeight[subIdx];
            strcpy(stSubPipeAttr.subDevName, stViDevAttr.subDevName[subIdx]);

            KD_U32  u32Width = (stSubPipeAttr.u32Width + 0xf) & (~0xf);
            KD_U32  u32Height = stSubPipeAttr.u32Height;

            switch (stSubPipeAttr.enPixFmt)
            {
                case PIXEL_FORMAT_NV12:
                case PIXEL_FORMAT_YUV422SP:
                {
                    snprintf(filename, 128, "vi_subpipe%d_%dx%d.yuv", subIdx, u32Width, u32Height);
                    break;
                }
                case PIXEL_FORMAT_ARGB:
                {
                    snprintf(filename, 128, "vi_subpipe%d_%dx%d.argb", subIdx, u32Width, u32Height);
                    break;
                }
                case PIXEL_FORMAT_RGB888:
                {
                    snprintf(filename, 128, "vi_subpipe%d_%dx%d.rgb", subIdx, u32Width, u32Height);
                    break;
                }
                default:
                {
                    printf("pixel format not support.\n");
                    return -1;
                }
            }

            FILE *fpout = NULL;
            fpout = fopen(filename, "wb");
            if (fpout == NULL)
            {
                printf("the output file open failed.\n");
                return -1;
            }

            kdRet = KD_MPI_VI_CreateSubPipe(subIdx, &stSubPipeAttr);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi device enable failed.\n");
                goto SAMPLE_DESTORY;
            }

            kdRet = KD_MPI_VI_StartSubPipe(subIdx);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi sub pipe start failed.\n");
                goto SAMPLE_STOP;
            }

            VIDEO_FRAME_INFO_S stFrameInfo;
            memset(&stFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));

            for (int num = 0; num < 10; num++)
            {
                kdRet = KD_MPI_VI_GetSubPipeFrame(subIdx, &stFrameInfo, -1);
                if (kdRet != KD_SUCCESS)
                {
                    printf("sub pipe get vi frame failed.\n");
                    continue;
                }

                fwrite((KD_VOID *)stFrameInfo.u64VirData, 1, stFrameInfo.u32DataSize, fpout);

                kdRet = KD_MPI_VI_ReleaseSubPipeFrame(subIdx, &stFrameInfo);
                if (kdRet != KD_SUCCESS)
                {
                    printf("sub pipe release frame failed.\n");
                    break;
                }
            }

            fclose(fpout);

        SAMPLE_STOP:
            kdRet = KD_MPI_VI_StopSubPipe(subIdx);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi sub pipe stop failed.\n");
                return -1;
            }

        SAMPLE_DESTORY:
            kdRet = KD_MPI_VI_DestroySubPipe(subIdx);
            if (kdRet != KD_SUCCESS)
            {
                printf("vi sub pipe destory failed.\n");
                return -1;
            }
        }
    }

    kdRet = KD_MPI_VI_Deinit();
    if (kdRet != KD_SUCCESS)
    {
        printf("vi device deinit failed.\n");
        return -1;
    }

    return 0;
}