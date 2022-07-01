#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>
#include "kd_vo.h"

#define DRM_DEV_NAME_DEFAULT "/dev/dri/card0"

typedef struct kdSAMPLE_VO_CONTEXT_S
{
    FILE                *inputFile;
    PIXEL_FORMAT_E  	enInPixelFmt;
    KD_U32              u32InputPicWidth;
    KD_U32              u32InputPicHeight;
} SAMPLE_VO_CONTEXT_S;

static void help()
{
    printf("-help: print the help info.\n");
    printf("-i: the input source file, xxx.yuv.\n");
    printf("-inFmt: the input picture pixel format.\n");
    printf("-inputW: the input picture width.\n");
    printf("-inputH: the input picture height.\n");
}

static KD_S32 parse_cmdline(int argc, char *argv[], SAMPLE_VO_CONTEXT_S *pstSampelVoCtx)
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            pstSampelVoCtx->inputFile = fopen(argv[i+1], "r+b");
            if (pstSampelVoCtx->inputFile == NULL)
            {
                printf("input file open failed.\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-inFmt") == 0)
        {
            if (strcmp(argv[i+1], "nv12") == 0)
            {
                pstSampelVoCtx->enInPixelFmt = PIXEL_FORMAT_NV12;
            }
            else
            {
                printf("the input file pixel format is invalid, please check...\n");
                help();
                return -1;
            }
        }
        else if (strcmp(argv[i], "-inputW") == 0)
        {
            pstSampelVoCtx->u32InputPicWidth = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-inputH") == 0)
        {
            pstSampelVoCtx->u32InputPicHeight = atoi(argv[i+1]);
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

int main(int argc, char **argv)
{
	KD_RET kdRet = KD_SUCCESS;

    if (argc < 2 || strcmp(argv[1], "-help") == 0)
    {
        printf("the cmdline arguments is invalid, please check...\n");
        help();
        return 0;
    }

    SAMPLE_VO_CONTEXT_S stSampleVoCtx;
    memset(&stSampleVoCtx, 0, sizeof(SAMPLE_VO_CONTEXT_S));

    if (parse_cmdline(argc, argv, &stSampleVoCtx) != 0)
    {
        printf("parse cmdline argument failed.\n");
        return -1;
    }

    VO_DEV VoDev = 0;

	KD_MPI_VO_Init();

	kdRet = KD_MPI_VO_SetPubAttr(VoDev);
	if (kdRet != KD_SUCCESS)
	{
		printf("set public attribute failed.\n");
		return -1;
	}

	kdRet = KD_MPI_VO_Enable(VoDev);
	if (kdRet != KD_SUCCESS)
	{
		printf("vo device enable failed.\n");
		goto SAMPLE_DEV_DISABLE;
	}

    VO_VIDEO_LAYER_ATTR_S stVoBaseLayerAttr;
	memset(&stVoBaseLayerAttr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stVoBaseLayerAttr.enPixelFormat = stSampleVoCtx.enInPixelFmt;
	stVoBaseLayerAttr.u32PicWidth = stSampleVoCtx.u32InputPicWidth;
	stVoBaseLayerAttr.u32PicHeight = stSampleVoCtx.u32InputPicHeight;
    stVoBaseLayerAttr.u32OffsetX = 0;
    stVoBaseLayerAttr.u32OffsetY = 0;
    stVoBaseLayerAttr.u32Bpp = 8;

    VO_VIDEO_LAYER_ATTR_S stVoLayer1Attr;
	memset(&stVoLayer1Attr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stVoLayer1Attr.enPixelFormat = stSampleVoCtx.enInPixelFmt;
	stVoLayer1Attr.u32PicWidth = 880;
	stVoLayer1Attr.u32PicHeight = 500;
    stVoLayer1Attr.u32OffsetX = 100;
    stVoLayer1Attr.u32OffsetY = 150;
    stVoLayer1Attr.u32Bpp = 8;

    VO_LAYER VoBaseLayer = 0;
    kdRet = KD_MPI_VO_EnableVideoLayer(VoBaseLayer, &stVoBaseLayerAttr);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo base layer enable failed.\n");
		goto SAMPLE_LAYER_DISABLE;
	}

    VO_LAYER VoLayer1 = 1;
    kdRet = KD_MPI_VO_EnableVideoLayer(VoLayer1, &stVoLayer1Attr);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo base layer enable failed.\n");
		goto SAMPLE_LAYER_DISABLE;
	}

// base layer frame
    VIDEO_FRAME_INFO_S stBaseFrame;
	memset(&stBaseFrame, 0, sizeof(VIDEO_FRAME_INFO_S));
	stBaseFrame.enPixelFormat = stVoLayer1Attr.enPixelFormat;
	stBaseFrame.u32Width = stSampleVoCtx.u32InputPicWidth;
	stBaseFrame.u32Height = stSampleVoCtx.u32InputPicHeight;

    KD_U32 u32BaseFrameSize;
    u32BaseFrameSize = stBaseFrame.u32Width *  stBaseFrame.u32Height * 3 / 2;

	KD_U8 *pBasebuf = (KD_U8 *)malloc(u32BaseFrameSize);
	stBaseFrame.u64VirData = (KD_U64)pBasebuf;

// layer1 frame
    VIDEO_FRAME_INFO_S stLayer1Frame;
	memset(&stLayer1Frame, 0, sizeof(VIDEO_FRAME_INFO_S));
	stLayer1Frame.enPixelFormat = stVoLayer1Attr.enPixelFormat;
	stLayer1Frame.u32Width = stVoLayer1Attr.u32PicWidth;
	stLayer1Frame.u32Height = stVoLayer1Attr.u32PicHeight;

    KD_U32 u32Layer1FrameSize;
    u32Layer1FrameSize = stLayer1Frame.u32Width *  stLayer1Frame.u32Height * 3 / 2;

	KD_U8 *pLayer1Buf = (KD_U8 *)malloc(u32Layer1FrameSize);
	stLayer1Frame.u64VirData = (KD_U64)pLayer1Buf;

	for (int num = 0; num < 10; num++)
	{
		size_t retSize = fread(pBasebuf, 1, u32BaseFrameSize, stSampleVoCtx.inputFile);
		if (retSize == 0 || retSize < u32BaseFrameSize)
    	{
        	printf("input file has no data to read, or the frame data is incomplete.\n");
        	break;
    	}

		kdRet = KD_MPI_VO_SendFrame(VoBaseLayer, &stBaseFrame);
		if (kdRet != KD_SUCCESS)
		{
			printf("send frame failed.\n");
			continue;
		}

        stLayer1Frame.u64VirData = (KD_U64)pLayer1Buf;
        memset(pLayer1Buf, 128, u32Layer1FrameSize);
        kdRet = KD_MPI_VO_SendFrame(VoLayer1, &stLayer1Frame);
		if (kdRet != KD_SUCCESS)
		{
			printf("send frame failed.\n");
			continue;
		}

        kdRet = KD_MPI_VO_FrameLayerSync(VoDev);
        if (kdRet != KD_SUCCESS)
		{
			printf("vo frame layer sync failed.\n");
			goto SAMPLE_LAYER_DISABLE;
		}

		usleep(25000);
	}

SAMPLE_LAYER_DISABLE:
    kdRet = KD_MPI_VO_DisableVideoLayer(VoBaseLayer);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return -1;
	}

    kdRet = KD_MPI_VO_DisableVideoLayer(VoLayer1);
    if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return -1;
	}

SAMPLE_DEV_DISABLE:
	kdRet = KD_MPI_VO_Disable(VoDev);
	if (kdRet != KD_SUCCESS)
	{
		printf("vo disable failed.\n");
		return -1;
	}

	KD_MPI_VO_Deinit();

    free(pBasebuf);
    free(pLayer1Buf);
	
	return 0;
}
