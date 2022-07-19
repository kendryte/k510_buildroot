/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <bits/types/struct_timeval.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdbool.h>

#include <linux/media.h>
#include <linux/types.h>
#include <linux/v4l2-mediabus.h>
#include <linux/v4l2-subdev.h>
#include <linux/videodev2.h>

#include "v4l2/v4l2subdev.h"
//#include "v4l2/v4l2.h"
#include "v4l2/tools.h"
#include "media/mediactl.h"
#include "media/mediactl-priv.h"

#include "isp/isp.h"

#include "media_ctl.h"
#include "linux/k510isp.h"
#include "isp/json_parse.h"

#define MEDIA_DEVICE	"/dev/media0"
#define ENTITY_DPHY		"K510 ISP DPHY"
#define ENTITY_CSI2		"K510 ISP CSI2"
#define ENTITY_VI		"K510 ISP VI"
#define ENTITY_F2K		"K510 ISP F2K"
#define ENTITY_R2K		"K510 ISP R2K"

// share memory 
struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};

#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)
#define MEMORY_TEST_BLOCK_NUM   10          /* 测试多少次申请释放 */
#define MEMORY_TEST_BLOCK_SIZE  4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */
int fd_share_memory = -1;
int fd_mem_map = -1;
#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"
#define MAP_MEMORY_DEV      "/dev/mem"
int *virtual_addr[MEMORY_TEST_BLOCK_NUM]= {0};
bool DualCamera_Sync = TRUE;
bool Sensor1_Sync = FALSE;
bool Awb_Sync_Init = TRUE;



struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM] = {0};
//
enum isp_pipeline
{
	ISP_F2K,
	ISP_R2K,
	ISP_3D,
	NO_ISP,
};

struct video_entity_info_s{
    unsigned int used;
    char video_entity_name[50];
    struct image_size_s video_size; 
	unsigned int video_out_format; 
};

struct isp_pipeline_s{
	unsigned int pipeline_en;
	char sensor_name[20];
	struct image_size_s total_size;
    struct image_size_s sensor_size;
	struct v4l2_mbus_framefmt format_in;
	struct v4l2_mbus_framefmt format_crop;
	struct v4l2_mbus_framefmt format_out;
	struct video_entity_info_s video_entity_info[4];
};

struct v4l_isp_device {
	struct isp_pipeline_s  isp_pipeline[2];
	//
	struct media_device *mdev;
	struct media_entity *sensor0;
	struct media_entity *sensor1;
	struct media_entity *dphy;
	struct media_entity *csi2;
	struct media_entity *vi;
	struct media_entity *f2k;
	struct media_entity *r2k;
	struct media_entity *video[10];
};

struct v4l_isp_device v4l_isp;
/*************************************************************************
 *
*************************************************************************/
/**
 * @brief Construct a new isp entity init object
 * 
 * @param isp 
 */
static int isp_entity_init(struct v4l_isp_device *isp)
{
	struct media_entity *entity;	
	unsigned int i;
	/* 
	 * Start by locating the three entities. The output video node is
	 * located by looking for a devnode connected to the VI.
	 */
	if( isp->isp_pipeline[ISP_F2K].pipeline_en == 1)
	{
		isp->sensor0 = media_get_entity_by_name(isp->mdev,isp->isp_pipeline[ISP_F2K].sensor_name,
					       strlen(isp->isp_pipeline[ISP_F2K].sensor_name));
		if (isp->sensor0 == NULL) {
			printf("%s error: unable to locate sensor0.\n",__func__);
			return -ENOENT;
		}
	}

	if( isp->isp_pipeline[ISP_R2K].pipeline_en == 1)
	{
		isp->sensor1 = media_get_entity_by_name(isp->mdev,isp->isp_pipeline[ISP_R2K].sensor_name,
					       strlen(isp->isp_pipeline[ISP_R2K].sensor_name));
		if (isp->sensor1 == NULL) {
			printf("%s error: unable to locate sensor1.\n",__func__);
			return -ENOENT;
		}
	}

	isp->csi2 = media_get_entity_by_name(isp->mdev, ENTITY_CSI2,
					     strlen(ENTITY_CSI2));
	if (isp->csi2 == NULL) {
		printf("%s error: unable to locate CSI2.\n",__func__);
		return -ENOENT;
	}

	isp->vi = media_get_entity_by_name(isp->mdev, ENTITY_VI,
					     strlen(ENTITY_VI));
	if (isp->vi == NULL) {
		printf("%s error: unable to locate VI.\n",__func__);
		return -ENOENT;
	}

	isp->f2k = media_get_entity_by_name(isp->mdev, ENTITY_F2K,
					     strlen(ENTITY_F2K));
	if (isp->f2k == NULL) {
		printf("%s error: unable to locate F2K.\n",__func__);
		return -ENOENT;
	}

	isp->r2k = media_get_entity_by_name(isp->mdev, ENTITY_R2K,
					     strlen(ENTITY_R2K));
	if (isp->r2k == NULL) {
		printf("%s error: unable to locate R2K.\n",__func__);
		return -ENOENT;
	}
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 */
static int isp_f2k_video_init(struct v4l_isp_device *isp)
{
	struct media_entity *entity;
	unsigned int i;
	unsigned int j;

	struct isp_pipeline_s  *isp_pipeline = &isp->isp_pipeline[ISP_F2K]; 
	for(j = 0;j<4;j++)
	{
		//printf("%s:%d,%s\n",__func__,isp_pipeline->video_entity_info[j].used,isp_pipeline->video_entity_info[j].video_entity_name);
		if(isp_pipeline->video_entity_info[j].used == 1)
		{
			isp->video[j+2] = media_get_entity_by_name(isp->mdev,isp_pipeline->video_entity_info[j].video_entity_name,
							       strlen(isp_pipeline->video_entity_info[j].video_entity_name));
			if (isp->video[j+2] == NULL) {
				printf("%s error: unable to locate video.\n",__func__);
				return -ENOENT;
			}
			//printf("%s:video entity (0x%x):locate entities OK!\n",__func__,isp->video[j+2]);

			//F2K
			for (i = 0; i < isp->f2k->info.links+1; ++i) { 
				//printf("links[%d]:0x%x,sink:0x%x,source:0x%x\n",i,isp->f2k->links[i],isp->f2k->links[i].sink,isp->f2k->links[i].source);
				entity = isp->f2k->links[i].sink->entity;
				//printf("%s:%d,media_entity_type:0x%x,0x%x\n",__func__,i,media_entity_type(entity),entity);
				if (media_entity_type(entity) == MEDIA_ENT_T_DEVNODE)
				{
					//printf("%s:MEDIA_ENT_T_DEVNODE\n",__func__);
					if(entity == isp->video[j+2])
					{
						printf("%s:entity(0x%x)isp->video(0x%x)\n",__func__,entity,isp->video[j+2]);
						break;
					}	
				}	
			}

			if (i == isp->f2k->info.links+1) { //2
				printf("%s error: unable to locate F2K output video node.\n",__func__);
				return -ENOENT;
			}

			isp->video[j+2] = entity;
		}
	}
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 */
static int isp_r2k_video_init(struct v4l_isp_device *isp)
{
	struct media_entity *entity;
	unsigned int i;
	unsigned int j;

	struct isp_pipeline_s  *isp_pipeline = &isp->isp_pipeline[ISP_R2K]; 
	for(j = 0;j<4;j++)
	{
		if(isp_pipeline->video_entity_info[j].used == 1)
		{
			isp->video[j+6] = media_get_entity_by_name(isp->mdev,isp_pipeline->video_entity_info[j].video_entity_name,
							       strlen(isp_pipeline->video_entity_info[j].video_entity_name));
			if (isp->video[j+6] == NULL) {
				printf("%s error: unable to locate video.\n",__func__);
				return -ENOENT;
			}
			//printf("%s:video entity (0x%x):locate entities OK!\n",__func__,isp->video[j+6]);

			//R2K
			for (i = 0; i < isp->r2k->info.links+1; ++i) { 
				//printf("links[%d]:0x%x,sink:0x%x,source:0x%x\n",i,isp->r2k->links[i],isp->r2k->links[i].sink,isp->r2k->links[i].source);
				entity = isp->r2k->links[i].sink->entity;
				//printf("%s:%d,media_entity_type:0x%x,0x%x\n",__func__,i,media_entity_type(entity),entity);
				if (media_entity_type(entity) == MEDIA_ENT_T_DEVNODE)
				{
					//printf("%s:MEDIA_ENT_T_DEVNODE\n",__func__);
					if(entity == isp->video[j+6])
					{
						printf("%s:entity(0x%x)isp->video(0x%x)\n",__func__,entity,isp->video[j+6]);
						break;
					}	
				}	
			}

			if (i == isp->r2k->info.links+1) { //2
				printf("%s error: unable to locate R2K output video node.\n",__func__);
				return -ENOENT;
			}

			isp->video[j+6] = entity;
		}
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 */
static int isp_setup_link(struct v4l_isp_device *isp)
{
	int ret;
	/* Enable the Sensor->vi->f2k -> memory links. */

	//	printf("isp->csi2->pads[CSI2_PAD_SOURCE0] =0x%x,&isp->vi->pads[VI_PAD_SINK_CSI0] =0x%x\n\n",&isp->csi2->pads[CSI2_PAD_SOURCE1],&isp->vi->pads[VI_PAD_SINK_CSI1]);
	ret = media_setup_link(isp->mdev, &isp->csi2->pads[CSI2_PAD_SOURCE0],
			       &isp->vi->pads[VI_PAD_SINK_CSI0], MEDIA_LNK_FL_ENABLED);
	if (ret < 0) {
		printf("%s error: unable to setup csi2 -> vi link.\n",__func__);
		return ret; 
	}

	//printf("isp->csi2->pads[CSI2_PAD_SOURCE1] =0x%x,&isp->vi->pads[VI_PAD_SINK_CSI1] =0x%x\n\n",&isp->csi2->pads[CSI2_PAD_SOURCE0],&isp->vi->pads[VI_PAD_SINK_CSI0]);
	ret = media_setup_link(isp->mdev, &isp->csi2->pads[CSI2_PAD_SOURCE1],
			       &isp->vi->pads[VI_PAD_SINK_CSI1], MEDIA_LNK_FL_ENABLED);
	if (ret < 0) {
		printf("%s error: unable to setup csi2 -> vi link.\n",__func__);
		return ret; 
	}

	//printf("%s:isp->sensor0->pads[0] =0x%x,&isp->csi2->pads[CSI2_PAD_SINK0] =0x%x\n",__func__,&isp->sensor0->pads[0],&isp->csi2->pads[CSI2_PAD_SINK0]);
	if( isp->isp_pipeline[ISP_F2K].pipeline_en == 1)
	{
		ret = media_setup_link(isp->mdev, &isp->sensor0->pads[0],
				       &isp->csi2->pads[CSI2_PAD_SINK0], MEDIA_LNK_FL_ENABLED);
		if (ret < 0) {
			printf("%s error: unable to setup sensor0 -> csi2 link.\n",__func__);
			return ret; 
		}

		//printf("isp->vi->pads[VI_PAD_SOURCE_F2K] =0x%x,&isp->f2k->pads[ISP_F2K_PAD_SINK] =0x%x\n\n",&isp->vi->pads[VI_PAD_SOURCE_F2K],&isp->f2k->pads[ISP_F2K_PAD_SINK]);
		ret = media_setup_link(isp->mdev, &isp->vi->pads[VI_PAD_SOURCE_F2K],
				       &isp->f2k->pads[ISP_F2K_PAD_SINK], MEDIA_LNK_FL_ENABLED);
		if (ret < 0) {
			printf("%s error: unable to setup vi -> f2k link.\n",__func__);
			return ret; 
		}
	}

	if( isp->isp_pipeline[ISP_R2K].pipeline_en == 1)
	{
		//printf("isp->sensor1->pads[0] =0x%x,&isp->csi2->pads[CSI2_PAD_SINK1] =0x%x\n",&isp->sensor1->pads[0],&isp->csi2->pads[CSI2_PAD_SINK1]);
		ret = media_setup_link(isp->mdev, &isp->sensor1->pads[0],
				       &isp->csi2->pads[CSI2_PAD_SINK1], MEDIA_LNK_FL_ENABLED);
		if (ret < 0) {
			printf("%s error: unable to setup sensor1 -> csi2 link.\n",__func__);
			return ret; 
		}

		//printf("isp->vi->pads[VI_PAD_SOURCE_R2K] =0x%x,&isp->r2k->pads[ISP_R2K_PAD_SINK] =0x%x\n\n",&isp->vi->pads[VI_PAD_SOURCE_R2K],&isp->r2k->pads[ISP_R2K_PAD_SINK]);
		ret = media_setup_link(isp->mdev, &isp->vi->pads[VI_PAD_SOURCE_R2K],
				       &isp->r2k->pads[ISP_R2K_PAD_SINK], MEDIA_LNK_FL_ENABLED);
		if (ret < 0) {
			printf("%s error: unable to setup vi -> r2k link.\n",__func__);
			return ret; 
		}
	}
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @param source_pad 
 * @return int 
 */
static int isp_f2k_video_link(struct v4l_isp_device *isp)
{
	int ret;
	unsigned int i = 0;
	struct isp_pipeline_s *isp_pipeline = &isp->isp_pipeline[ISP_F2K];

	for(i = 0; i< 4; i++)
	{
		if(isp_pipeline->video_entity_info[i].used == 1)
		{			
			ret = media_setup_link(isp->mdev, &isp->f2k->pads[ISP_F2K_PAD_MAIN_SOURCE + i],
					       &isp->video[i+2]->pads[0], MEDIA_LNK_FL_ENABLED);
			if (ret < 0) {
				printf("%s error: unable to setup F2K -> devnode link.\n",__func__);
				return ret;
			}
		}
	}
	printf("%s:media_setup_link setup!\n",__func__);
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @param source_pad 
 * @return int 
 */
static int isp_r2k_video_link(struct v4l_isp_device *isp)
{
	int ret;
	unsigned int i = 0;
	struct isp_pipeline_s *isp_pipeline = &isp->isp_pipeline[ISP_R2K];

	for(i = 0; i< 4; i++)
	{
		if(isp_pipeline->video_entity_info[i].used == 1)
		{			
			ret = media_setup_link(isp->mdev, &isp->r2k->pads[ISP_R2K_PAD_MAIN_SOURCE + i],
					       &isp->video[i+6]->pads[0], MEDIA_LNK_FL_ENABLED);
			if (ret < 0) {
				printf("%s error: unable to setup R2K -> devnode link.\n",__func__);
				return ret;
			}
		}
	}
	printf("%s:media_setup_link setup!\n",__func__);
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 * Configure formats. Retrieve the default format at the sensor output
 * and propagate it through the pipeline. As the VI will not perform
 * any cropping we can just apply the same format on all pads.
 * struct v4l2_mbus_framefmt {
 *	__u32			width;
 *	__u32			height;
 *	__u32			code;
 *	__u32			field;
 *	__u32			colorspace;
 *	__u16			ycbcr_enc;
 *	__u16			quantization;
 *	__u16			xfer_func;
 *	__u16			reserved[11];
 *	};
 */
static int isp_f2k_set_format(struct v4l_isp_device *isp)
{
	struct v4l2_mbus_framefmt format;
	struct isp_pipeline_s *isp_pipeline = &isp->isp_pipeline[ISP_F2K];
	int ret;
	unsigned int i = 0;
	//sensor
	ret = v4l2_subdev_get_format(isp->sensor0, &format, 0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);//V4L2_SUBDEV_FORMAT_TRY);
	if (ret < 0) {
		printf("%s error: get format on sensor0 output failed.\n",__func__);
		return ret;
	}
	//printf("%s :v4l2_subdev_set_format sensor(g) width:(%d),height:(%d)\n",__func__,format.width,format.height);

	memcpy(&isp_pipeline->format_in,&format,sizeof(struct v4l2_mbus_framefmt));
	isp_pipeline->format_in.width = isp_pipeline->sensor_size.width;//ACTIVE_WIDTH;//1080;
	isp_pipeline->format_in.height = isp_pipeline->sensor_size.height;//ACTIVE_HEIGHT;//1920
	ret = v4l2_subdev_set_format(isp->sensor0, &isp_pipeline->format_in, 0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",
			__func__,isp->sensor0->info.name, 0);
		return ret;
	}
	//printf("%s:v4l2_subdev_set_format sensor(s) width:(%d),height:(%d),code:(0x%x)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height,isp_pipeline->format_in.code);

	//csi2
	ret = v4l2_subdev_set_format(isp->csi2, &isp_pipeline->format_in, CSI2_PAD_SINK0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->csi2->info.name, 1);
		return ret;
	}
	//printf("%s:v4l2_subdev_set_format csi2(s) width:(%d),height:(%d),code:(0x%x)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height,isp_pipeline->format_in.code);

	ret = v4l2_subdev_set_format(isp->csi2, &isp_pipeline->format_in, CSI2_PAD_SOURCE0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->csi2->info.name, 1);
		return ret;
	}
	//printf("%s:v4l2_subdev_set_format csi2(s1) width:(%d),height:(%d)\n",__func__,
	//isp_pipeline->format_in.width,isp_pipeline->format_in.height);

	//vi
	ret = v4l2_subdev_set_format(isp->vi, &isp_pipeline->format_in, VI_PAD_SINK_CSI0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->vi->info.name, 1);
		return ret;
	}
	//printf("%s:v4l2_subdev_set_format vi(s) width:(%d),height:(%d)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height);
	

	ret = v4l2_subdev_set_format(isp->vi, &isp_pipeline->format_in, VI_PAD_SOURCE_F2K,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->vi->info.name, 1);
		return ret;
	}
	//printf("%s:v4l2_subdev_set_format vi(s1) width:(%d),height:(%d)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height);	


	//isp_pipeline->format_in.code =MEDIA_BUS_FMT_SRGGB12_1X12;//MEDIA_BUS_FMT_SRGGB10_1X10;
	ret = v4l2_subdev_set_format(isp->f2k, &isp_pipeline->format_in, ISP_F2K_PAD_SINK,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->f2k->info.name, 1);
		return ret;
	}

	//printf("%s:v4l2_subdev_set_format isp(s) width:(%d),height:(%d)\n",__func__,isp->format_in.width,isp->format_in.height);
	memcpy(&isp_pipeline->format_crop,&isp_pipeline->format_in,sizeof(struct v4l2_mbus_framefmt));
	//printf("%s:v4l2_subdev_set_format isp(s1) width:(%d),height:(%d)\n",__func__,isp->format_crop.width,isp->format_crop.height);
	memcpy(&isp_pipeline->format_out,&isp_pipeline->format_crop,sizeof(struct v4l2_mbus_framefmt));
	//isp->format_out.width = isp->video_width;//VIDEO_WIDTH;//1080;
	//isp->format_out.height = isp->video_height;//VIDEO_HEIGHT;//720;
	for(i = 0; i < 4; i++)
	{
		//printf("%s:%d,%d\n",__func__,i,isp_pipeline->video_entity_info[i].used);
		if(isp_pipeline->video_entity_info[i].used == 1)
		{
			isp_pipeline->format_out.width = isp_pipeline->video_entity_info[i].video_size.width;//VIDEO_WIDTH;//1080;
			isp_pipeline->format_out.height = isp_pipeline->video_entity_info[i].video_size.height;//VIDEO_HEIGHT;//720;
			if( isp_pipeline->video_entity_info[i].video_out_format == 1)
			{
				isp_pipeline->format_out.code = MEDIA_BUS_FMT_Y12_1X12; //MEDIA_BUS_FMT_UYVY8_1_5X8,MEDIA_BUS_FMT_VYUY8_1_5X8,MEDIA_BUS_FMT_YUYV8_1_5X8,MEDIA_BUS_FMT_YVYU8_1_5X8
				if(i == 3)
					isp_pipeline->format_out.code = MEDIA_BUS_FMT_ARGB8888_1X32;
			}
			else
			{
				isp_pipeline->format_out.code = MEDIA_BUS_FMT_YUYV8_2X8;//MEDIA_BUS_FMT_YVYU8_2X8,MEDIA_BUS_FMT_UYVY8_1X16,MEDIA_BUS_FMT_YUYV8_1X16,MEDIA_BUS_FMT_YVYU8_1X16,MEDIA_BUS_FMT_VYUY8_1X16,
				if(i == 3)
					isp_pipeline->format_out.code = MEDIA_BUS_FMT_RGB888_1X24;//MEDIA_BUS_FMT_RBG888_1X24,MEDIA_BUS_FMT_BGR888_1X24,MEDIA_BUS_FMT_BGR888_3X8,MEDIA_BUS_FMT_GBR888_1X24,MEDIA_BUS_FMT_RGB888_1X24
			}

			//printf("%s:isp_pipeline->format_out.width(%d),isp_pipeline->format_out.height(%d) isp_pipeline->format_out.code (0x%x)\n",__func__,isp_pipeline->format_out.width,isp_pipeline->format_out.height,isp_pipeline->format_out.code);
			ret = v4l2_subdev_set_format(isp->f2k, &isp_pipeline->format_out,ISP_F2K_PAD_MAIN_SOURCE + i,
						     V4L2_SUBDEV_FORMAT_ACTIVE);
			if (ret < 0) {
				printf("%s error: set format failed on %s:%u.\n",__func__,
					isp->vi->info.name, 1);
				return ret;
			}
		}
	}
	
	return 0;
}
/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 */
static int isp_r2k_set_format(struct v4l_isp_device *isp)
{
	struct v4l2_mbus_framefmt format;
	struct isp_pipeline_s *isp_pipeline = &isp->isp_pipeline[ISP_R2K];
	int ret;
	unsigned int i = 0;

	//sensor
	ret = v4l2_subdev_get_format(isp->sensor1, &format, 0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);//V4L2_SUBDEV_FORMAT_TRY);
	if (ret < 0) {
		printf("%s error: get format on sensor0 output failed.\n",__func__);
		return ret;
	}
	printf("%s :v4l2_subdev_set_format sensor(g) width:(%d),height:(%d)\n",__func__,format.width,format.height);

	memcpy(&isp_pipeline->format_in,&format,sizeof(struct v4l2_mbus_framefmt));
	isp_pipeline->format_in.width = isp_pipeline->sensor_size.width;//ACTIVE_WIDTH;//1080;
	isp_pipeline->format_in.height = isp_pipeline->sensor_size.height;//ACTIVE_HEIGHT;//1920	
	ret = v4l2_subdev_set_format(isp->sensor1, &isp_pipeline->format_in, 0,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",
			__func__,isp->sensor1->info.name, 0);
		return ret;
	}

//	printf("%s:v4l2_subdev_set_format sensor(s) width:(%d),height:(%d)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height);

	ret = v4l2_subdev_set_format(isp->csi2, &isp_pipeline->format_in, CSI2_PAD_SINK1,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->csi2->info.name, 1);
		return ret;
	}

	ret = v4l2_subdev_set_format(isp->csi2, &isp_pipeline->format_in, CSI2_PAD_SOURCE1,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->csi2->info.name, 1);
		return ret;
	}

	//vi
	//	isp_pipeline->format_in.width,isp_pipeline->format_in.height);
	ret = v4l2_subdev_set_format(isp->vi, &isp_pipeline->format_in, VI_PAD_SINK_CSI1,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("error: set format failed on %s:%u.\n",
			isp->vi->info.name, 1);
		return ret;
	}

	ret = v4l2_subdev_set_format(isp->vi, &isp_pipeline->format_in, VI_PAD_SOURCE_R2K,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->vi->info.name, 1);
		return ret;
	}

	//isp_pipeline->format_in.code = MEDIA_BUS_FMT_SRGGB10_1X10;
	ret = v4l2_subdev_set_format(isp->r2k, &isp_pipeline->format_in, ISP_R2K_PAD_SINK,
				     V4L2_SUBDEV_FORMAT_ACTIVE);
	if (ret < 0) {
		printf("%s error: set format failed on %s:%u.\n",__func__,
			isp->r2k->info.name, 1);
		return ret;
	}

	//printf("%s:v4l2_subdev_set_format isp(s) width:(%d),height:(%d)\n",__func__,isp_pipeline->format_in.width,isp_pipeline->format_in.height);
	memcpy(&isp_pipeline->format_crop,&isp_pipeline->format_in,sizeof(struct v4l2_mbus_framefmt));
	//printf("%s:v4l2_subdev_set_format isp(s1) width:(%d),height:(%d)\n",__func__,isp_pipeline->format_crop.width,isp_pipeline->format_crop.height);
	memcpy(&isp_pipeline->format_out,&isp_pipeline->format_crop,sizeof(struct v4l2_mbus_framefmt));
	for(i = 0; i < 4; i++)
	{
		if(isp_pipeline->video_entity_info[i].used == 1)
		{
			isp_pipeline->format_out.width = isp_pipeline->video_entity_info[i].video_size.width;//VIDEO_WIDTH;//1080;
			isp_pipeline->format_out.height = isp_pipeline->video_entity_info[i].video_size.height;//VIDEO_HEIGHT;//720;
			
			if( isp_pipeline->video_entity_info[i].video_out_format == 1)
			{
				isp_pipeline->format_out.code = MEDIA_BUS_FMT_Y12_1X12; //MEDIA_BUS_FMT_UYVY8_1_5X8,MEDIA_BUS_FMT_VYUY8_1_5X8,MEDIA_BUS_FMT_YUYV8_1_5X8,MEDIA_BUS_FMT_YVYU8_1_5X8
				if(i == 3)
					isp_pipeline->format_out.code = MEDIA_BUS_FMT_ARGB8888_1X32;
			}
			else
			{
				isp_pipeline->format_out.code = MEDIA_BUS_FMT_YUYV8_2X8;//MEDIA_BUS_FMT_YVYU8_2X8,MEDIA_BUS_FMT_UYVY8_1X16,MEDIA_BUS_FMT_YUYV8_1X16,MEDIA_BUS_FMT_YVYU8_1X16,MEDIA_BUS_FMT_VYUY8_1X16,
				if(i == 3)
					isp_pipeline->format_out.code = MEDIA_BUS_FMT_RGB888_1X24;//MEDIA_BUS_FMT_RBG888_1X24,MEDIA_BUS_FMT_BGR888_1X24,MEDIA_BUS_FMT_BGR888_3X8,MEDIA_BUS_FMT_GBR888_1X24,MEDIA_BUS_FMT_RGB888_1X24
			}

			printf("%s:isp_pipeline->format_out.width(%d),isp_pipeline->format_out.height(%d) isp_pipeline->format_out.code (0x%x)\n",__func__,isp_pipeline->format_out.width,isp_pipeline->format_out.height,isp_pipeline->format_out.code);
			ret = v4l2_subdev_set_format(isp->r2k, &isp_pipeline->format_out,ISP_R2K_PAD_MAIN_SOURCE + i,
						     V4L2_SUBDEV_FORMAT_ACTIVE);
			if (ret < 0) {
				printf("%s error: set format failed on %s:%u.\n",__func__,
					isp->vi->info.name, 1);
				return ret;
			}
		}
	}
	
	return 0;
}

#define ISP_CORE_AWB_CTL (0x0104)
#define ISP_CORE_AWB_HANDLE_MODE (0x03f7)
#define ISP_CORE_AWB_HANDLE_MODE_CHECK (0x0008)

/**
 * @brief
 *
 */
static int isp_awb_sync_init()
{
	int ret;
	struct k510isp_reg_val r2k_awb_reg_val,r2k_awb_reg_val_write;
	struct media_entity *pipe_f2k,*pipe_r2k;
	pipe_r2k = v4l_isp.r2k;

	r2k_awb_reg_val.reg_addr = ISP_CORE_AWB_CTL;
	r2k_awb_reg_val.reg_value = 0x0000;

	ret = v4l2_subdev_open(pipe_r2k);
	if (ret < 0)
		return ret;
	// get r2k awb ctl value
	ret = ioctl(pipe_r2k->fd,VIDIOC_K510ISP_R2K_CORE_REG_GET,&r2k_awb_reg_val);
	if (ret < 0)
	{
		printf("%s: ioctl(VIDIOC_K510ISP_R2K_CORE_REG_GET) failed ret(%d)\n", __func__,ret);
		v4l2_subdev_close(pipe_r2k);
		return ret;
	}
	// check r2k is handle mode or not, if auto mode then set to handle mode
	if ((r2k_awb_reg_val.reg_value & ISP_CORE_AWB_HANDLE_MODE_CHECK) == ISP_CORE_AWB_HANDLE_MODE_CHECK)
	{
		r2k_awb_reg_val_write.reg_addr = ISP_CORE_AWB_CTL;
		r2k_awb_reg_val_write.reg_value = r2k_awb_reg_val.reg_value & ISP_CORE_AWB_HANDLE_MODE;
		ret = ioctl(pipe_r2k->fd,VIDIOC_K510ISP_R2K_CORE_REG_SET,&r2k_awb_reg_val_write);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_R2K_CORE_REG_SET) failed ret(%d)\n", __func__,
				ret);
			v4l2_subdev_close(pipe_r2k);
			return ret;
		}
	}
	v4l2_subdev_close(pipe_r2k);
	return 0;
}

/**
 * @brief 
 * 
 * @param isp 
 * @return int 
 */
static int isp_pipeline_setup(struct v4l_isp_device *isp)
{
	/* Reset all links to make sure we're in a consistent, known state. */
	int ret = 0;

	ret = media_reset_links(isp->mdev);
	if (ret < 0) {
		printf("error: unable to reset links.\n");
		return ret;
	}

	/* Setup a Sensor -> VI -> F2K -> memory pipeline.*/
	//
	isp_entity_init(isp);
	//
	if( isp->isp_pipeline[ISP_F2K].pipeline_en == 1)
		isp_f2k_video_init(isp);
	if( isp->isp_pipeline[ISP_R2K].pipeline_en == 1)
		isp_r2k_video_init(isp);
	//
	isp_setup_link(isp);
	//
	if( isp->isp_pipeline[ISP_F2K].pipeline_en == 1)
	{
		isp_f2k_video_link(isp);
		//
		isp_f2k_set_format(isp);
	}

	if( isp->isp_pipeline[ISP_R2K].pipeline_en == 1)
	{
		isp_r2k_video_link(isp);
		//
		isp_r2k_set_format(isp);
	}

	
	if((isp->isp_pipeline[ISP_F2K].pipeline_en == 1)&&(isp->isp_pipeline[ISP_R2K].pipeline_en == 1)&&(DualCamera_Sync == TRUE))
	{
		Sensor1_Sync = TRUE;
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param isp_pipeline 
 * @param isp_cfg 
 */
void pipline_cfg(struct isp_pipeline_s *isp_pipeline,struct sensor_info *sensor)
{
	struct isp_wrap_cfg_info  *isp_wrap_cfg = &sensor->isp_cfg.isp_wrap_cfg;
	struct isp_core_cfg_info  *isp_core_cfg = &sensor->isp_cfg.isp_core_cfg;

	isp_pipeline->sensor_size.width = isp_core_cfg->itcInfo.itc_size.width;
	isp_pipeline->sensor_size.height = isp_core_cfg->itcInfo.itc_size.height;
	//
    isp_pipeline->format_in.width = isp_pipeline->sensor_size.width;		   
	isp_pipeline->format_in.height = isp_pipeline->sensor_size.height;
	//
	isp_pipeline->video_entity_info[0].used = isp_wrap_cfg->mainInfo.main_out_en;
	isp_pipeline->video_entity_info[0].video_size.width = isp_wrap_cfg->mainInfo.main_size.width;
	isp_pipeline->video_entity_info[0].video_size.height = isp_wrap_cfg->mainInfo.main_size.height;
	isp_pipeline->video_entity_info[0].video_out_format = isp_wrap_cfg->mainInfo.main_out_img_out_format;
	//
    isp_pipeline->format_crop.width = isp_pipeline->video_entity_info[0].video_size.width;
	isp_pipeline->format_crop.height = isp_pipeline->video_entity_info[0].video_size.height;
	//
    isp_pipeline->format_out.width = isp_pipeline->video_entity_info[0].video_size.width;
    isp_pipeline->format_out.height = isp_pipeline->video_entity_info[0].video_size.height;
    //
    isp_pipeline->video_entity_info[1].used = isp_wrap_cfg->ds0Info.ds0_out_en;
    isp_pipeline->video_entity_info[1].video_size.width = isp_wrap_cfg->ds0Info.ds0_size.width;
    isp_pipeline->video_entity_info[1].video_size.height = isp_wrap_cfg->ds0Info.ds0_size.height;
	isp_pipeline->video_entity_info[1].video_out_format = isp_wrap_cfg->ds0Info.ds0_out_img_out_format;
	//
    isp_pipeline->video_entity_info[2].used = isp_wrap_cfg->ds1Info.ds1_out_en;
    isp_pipeline->video_entity_info[2].video_size.width = isp_wrap_cfg->ds1Info.ds1_size.width;
    isp_pipeline->video_entity_info[2].video_size.height = isp_wrap_cfg->ds1Info.ds1_size.height;
	isp_pipeline->video_entity_info[2].video_out_format = isp_wrap_cfg->ds1Info.ds1_out_img_out_format;
	//
    isp_pipeline->video_entity_info[3].used = isp_wrap_cfg->ds2Info.ds2_out_en;
    isp_pipeline->video_entity_info[3].video_size.width = isp_wrap_cfg->ds2Info.ds2_size.width;
    isp_pipeline->video_entity_info[3].video_size.height = isp_wrap_cfg->ds2Info.ds2_video_height;//isp_wrap_cfg->ds2Info.ds2_size.height;
	isp_pipeline->video_entity_info[3].video_size.pitch = isp_wrap_cfg->ds2Info.ds2_size.pitch;//isp_wrap_cfg->ds2Info.ds2_size.height;
	isp_pipeline->video_entity_info[3].video_out_format = isp_wrap_cfg->ds2Info.ds2_out_img_out_format;
	//
	isp_pipeline->pipeline_en = 0;
	if( isp_pipeline->video_entity_info[0].used || isp_pipeline->video_entity_info[1].used || isp_pipeline->video_entity_info[2].used ||isp_pipeline->video_entity_info[3].used)
	{
		isp_pipeline->pipeline_en = 1;
	}
}
/**
 * @brief 
 * 
 */
static int  isp_share_memory_alloc(void)
{
    fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR);
    if(fd_share_memory < 0) {
        printf("open %s error!\r\n",SHARE_MEMORY_DEV);
        return 1 ;
    }

    allocAlignMem[0].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 3;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
    allocAlignMem[0].alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMem[0].phyAddr   = 0;

    if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[0]) < 0) {
        printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
        return 1;
    }
    else {
        printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[0].phyAddr,allocAlignMem[0].size,allocAlignMem[0].alignment);
    }

    allocAlignMem[1].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 3;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
    allocAlignMem[1].alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMem[1].phyAddr   = 0;

    if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[1]) < 0) {
        ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[0].phyAddr);
        printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
        return 1;
    }
    else {
        printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[1].phyAddr,allocAlignMem[1].size,allocAlignMem[1].alignment);
    }
    return 0;
}
/**
 * @brief 
 * 
 */
static void isp_share_memory_free(void)
{
	unsigned int i = 0;

    for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
        if(allocAlignMem[i].phyAddr != 0)
        {
            if(ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[i].phyAddr) < 0) {
                printf("share memory  SHARE_MEMORY_FREE error!\r\n");
            }
        }
    }

	close(fd_share_memory);
}

#if 0 
int mediactl_all_set_ae(enum isp_pipeline_e pipeline)
{
	int ret;
	struct k510isp_ae_stats ae_stats;
	struct media_entity *pipe;
	 
	if(ISP_F2K_PIPELINE == pipeline)
	{
		pipe = v4l_isp.f2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;


		ret = ioctl(pipe->fd,VIDIOC_K510ISP_F2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_F2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);
		//
		struct media_entity *sensor0 = v4l_isp.sensor0;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor0);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			control_s.id = V4L2_CID_EXPOSURE;
			control_s.value = ae_stats.ae_expl;
			ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor0);	  
				return ret;
			} 

			control_s.id = V4L2_CID_GAIN;
			control_s.value = ae_stats.ae_agco;
			ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor0);
				return ret;
			} 		
			v4l2_subdev_close(sensor0);
		}
	}

	if(ISP_R2K_PIPELINE == pipeline)
	{
		pipe = v4l_isp.r2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;


		ret = ioctl(pipe->fd,VIDIOC_K510ISP_R2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_R2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);
		//
		struct media_entity *sensor1 = v4l_isp.sensor1;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor1);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			control_s.id = V4L2_CID_EXPOSURE;
			control_s.value = ae_stats.ae_expl;
			ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor1);
				return ret;
			} 

			control_s.id = V4L2_CID_GAIN;
			control_s.value = ae_stats.ae_agco;
			ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor1);
				return ret;
			} 		
			v4l2_subdev_close(sensor1);
		}
	}
	
	return 0;
}
#else
int mediactl_all_set_ae(enum isp_pipeline_e pipeline)
{
	int ret;
	struct k510isp_ae_stats ae_stats;
	struct media_entity *pipe;
	 
	if(ISP_F2K_PIPELINE == pipeline)
	{
		pipe = v4l_isp.f2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;


		ret = ioctl(pipe->fd,VIDIOC_K510ISP_F2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_F2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);

		// no change
		static int expl = 0, agco = 0;
		if (expl == ae_stats.ae_expl && agco == ae_stats.ae_agco) {
			return ret;
		} else {
			expl = ae_stats.ae_expl;
			agco = ae_stats.ae_agco;
		}

		struct media_entity *sensor0 = v4l_isp.sensor0;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor0);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			control_s.id = V4L2_CID_EXPOSURE;
			control_s.value = ae_stats.ae_expl ;
			ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor0);	  
				return ret;
			} 

			control_s.id = V4L2_CID_GAIN;
			control_s.value = ae_stats.ae_agco;
			ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor0);
				return ret;
			} 		
			v4l2_subdev_close(sensor0);
		}
	}

	if(ISP_R2K_PIPELINE == pipeline)
	{
		pipe = v4l_isp.r2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;


		ret = ioctl(pipe->fd,VIDIOC_K510ISP_R2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_R2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);

		static int expl = 0, agco = 0;
		if (expl == ae_stats.ae_expl && agco == ae_stats.ae_agco) {
			return ret;
		} else {
			expl = ae_stats.ae_expl;
			agco = ae_stats.ae_agco;
		}

		struct media_entity *sensor1 = v4l_isp.sensor1;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor1);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			control_s.id = V4L2_CID_EXPOSURE;
			control_s.value = ae_stats.ae_expl;
			ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor1);
				return ret;
			} 

			control_s.id = V4L2_CID_GAIN;
			control_s.value = ae_stats.ae_agco;
			ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
					  ret);
				v4l2_subdev_close(sensor1);
				return ret;
			} 		
			v4l2_subdev_close(sensor1);
			// fprintf(stderr, "exp: %u\tagc: %u\n", ae_stats.ae_expl, ae_stats.ae_agco);
		}
	}
	
	return 0;
}

#endif
/**
 * @brief 
 * 
 */

#define F2K_AE_DEVICE           "/dev/f2k-ae"

void *run_f2k_ae_video(void *info)
{
    int fd ;
	int i = 0;
    fd_set fds;
    struct timeval tv;
    int r;
    int ret;

    printf("run_f2k_ae_video ------------------- start  \n");
    fd =  open(F2K_AE_DEVICE, O_RDWR);
    if (fd < 0) {
		printf("open %s error!\r\n", F2K_AE_DEVICE);
		return 1;
	}


    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    while (1) {
        /* Timeout. */
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        r = select(fd + 1, &fds, NULL, NULL, &tv);        
        if (-1 == r) {
            if (EINTR == errno)
                continue;
            //errno_exit("select");
            //done = true;
            printf("error: ae select failed with %d\n",errno);
            ret =  -1;
            break;
        }

        if (0 == r) {
            //done = true;
            printf("%s:ae select timeout\n",__func__);
            //exit(EXIT_FAILURE);
            ret =  -1;
            break;
        }

        //mediactl_set_ae();
#if 0
        if(Sensor1_Sync == FALSE)
		{
			ret = mediactl_set_ae_single(ISP_F2K_PIPELINE);
		}
		else
		{
			ret = mediactl_set_ae_sync(ISP_F2K_PIPELINE);
			ret = mediactl_set_awb_sync(ISP_F2K_PIPELINE);	
		}
#else

#if 0
		if(i == 0)
		{
			usleep(3950);
			mediactl_all_set_ae(ISP_F2K_PIPELINE);
		}
			
		i ++;
		if(i == 2)
		{
			i = 0;
		}
#else
		// char tmp;
		// read(fd, &tmp, 1);
		//usleep(3900);
		mediactl_all_set_ae(ISP_F2K_PIPELINE);
#endif

#endif
		
        /* EAGAIN - continue select loop. */
    }

    //printf("%s: camera %d fd(%d) mainloop end ret(%d)!\n", __func__,camera_seq,fd,ret);
    return ret;
}



#define R2K_AE_DEVICE           "/dev/r2k-ae"

void *run_r2k_ae_video(void *info)
{
    int fd ;

    fd_set fds;
    struct timeval tv;
    int r;
    int ret;
	int i = 0;

    printf("run_r2k_ae_video ------------------- start  \n");

    fd =  open(R2K_AE_DEVICE, O_RDWR);
    if (fd < 0) {
		printf("open %s error!\r\n", R2K_AE_DEVICE);
		return 1;
	}


    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    while (1) { 
        /* Timeout. */
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        r = select(fd + 1, &fds, NULL, NULL, &tv);        
        if (-1 == r) {
            if (EINTR == errno)
                continue;
            //errno_exit("select");
            //done = true;
            printf("error: ae select failed with %d\n",errno);
            ret =  -1;
            break;
        }

        if (0 == r) {
            //done = true;
            printf("%s:ae select timeout\n",__func__);
            //exit(EXIT_FAILURE);
            ret =  -1;
            break;
        }

        //mediactl_set_ae();
#if 0
        if(Sensor1_Sync == FALSE)
		{
			ret = mediactl_set_ae_single(ISP_R2K_PIPELINE);
		}
		else
		{
			ret = mediactl_set_ae_sync(ISP_F2K_PIPELINE);
			ret = mediactl_set_awb_sync(ISP_F2K_PIPELINE);	
		}
#else

#if 0
		if(i == 0)
		{
			usleep(3950);
			mediactl_all_set_ae(ISP_R2K_PIPELINE);
		}

		i ++;
		if(i == 2)
		{
			i = 0;
		}
#else
		//usleep(3900);
		mediactl_all_set_ae(ISP_R2K_PIPELINE);

#endif

#endif
        /* EAGAIN - continue select loop. */
    }
    //printf("%s: camera %d fd(%d) mainloop end ret(%d)!\n", __func__,camera_seq,fd,ret);
    return ret;
}


void run_all_ae_video(void *info)
{
    int fd[2];
	int i = 0;
    fd_set fds;
    struct timeval tv;
    int r;

    printf("run_all_ae_video ------------------- start  \n");

    fd[0] = open(F2K_AE_DEVICE, O_RDWR);
    if (fd[0] < 0) {
		printf("open %s error!\r\n", F2K_AE_DEVICE);
		return;
	}

	fd[1] = open(R2K_AE_DEVICE, O_RDWR);
    if (fd[1] < 0) {
		printf("open %s error!\r\n", F2K_AE_DEVICE);
		return;
	}

    FD_ZERO(&fds);
    FD_SET(fd[0], &fds);
	FD_SET(fd[1], &fds);
	int max_fd = (fd[0] > fd[1] ? fd[0] : fd[1]) + 1;
    while (1) {
		/*
		static time_t last_tm = 0;
		static uint32_t counter = 0;
		static uint32_t counter_last = 0;
		counter += 1;
		if (time(NULL) - last_tm) {
			fprintf(stderr, "select %d interrupts per second\n", counter - counter_last);
			last_tm = time(NULL);
			counter_last = counter;
		}
		*/

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;
		fd_set rfds = fds;
        r = select(max_fd, &rfds, NULL, NULL, &tv);
		if (r > 0) {
			if (FD_ISSET(fd[0], &rfds)) {
				struct timeval tv1, tv2;
				// gettimeofday(&tv1, NULL);
				mediactl_all_set_ae(ISP_F2K_PIPELINE);
				// gettimeofday(&tv2, NULL);
				// fprintf(stderr, "cam %d AE %ldus\n", 0, (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec));
			}
			if (FD_ISSET(fd[1], &rfds)) {
				struct timeval tv1, tv2;
				// gettimeofday(&tv1, NULL);
				mediactl_all_set_ae(ISP_R2K_PIPELINE);
				// gettimeofday(&tv2, NULL);
				// fprintf(stderr, "cam %d AE %ldus\n", 1, (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec));
			}
		} else if (r == -1) {
            if (EINTR == errno)
                continue;
            //errno_exit("select");
            //done = true;
            printf("error: ae select failed with %d\n",errno);
            break;
        } else if (r == 0) {
            //done = true;
            printf("%s:ae select timeout\n",__func__);
            //exit(EXIT_FAILURE);
            break;
        }

        //mediactl_set_ae();
#if 0
        if(Sensor1_Sync == FALSE)
		{
			ret = mediactl_set_ae_single(ISP_F2K_PIPELINE);
		}
		else
		{
			ret = mediactl_set_ae_sync(ISP_F2K_PIPELINE);
			ret = mediactl_set_awb_sync(ISP_F2K_PIPELINE);	
		}
#else

#if 0
		if(i == 0)
		{
			//usleep(3500);
			mediactl_all_set_ae(ISP_F2K_PIPELINE);
			mediactl_all_set_ae(ISP_R2K_PIPELINE);
		}
			
		i ++;
		if(i == 4)
		{
			i = 0;
		}
#else
		//usleep(3950);
		// mediactl_all_set_ae(ISP_R2K_PIPELINE);
		// mediactl_all_set_ae(ISP_F2K_PIPELINE);
	
#endif

#endif
		
        /* EAGAIN - continue select loop. */
    }

    //printf("%s: camera %d fd(%d) mainloop end ret(%d)!\n", __func__,camera_seq,fd,ret);
}

pthread_t isp_f2k_ae, isp_r2k_ae, isp_all_ae;

int mediactl_init(char *video_cfg_file,struct video_info *dev_info)
{
	int ret;
	struct isp_csi2_info mipi_csi2;
	struct vi_cfg_info vi_cfg;	
	memset(&v4l_isp, 0, sizeof v4l_isp);
	struct isp_pipeline_s *isp_pipeline = NULL;
	struct sensor_info sensor0;
	struct sensor_info sensor1;
	char *f2k_cfg_file = NULL;//f2k_cfg_file[50];
	char *r2k_cfg_file = NULL;//r2k_cfg_file[50];

	if( video_cfg_file != NULL)
	{

		printf("%s:%s\n",__func__,video_cfg_file);
		dofile_video_cfg(video_cfg_file,&vi_cfg,&sensor0,&sensor1,dev_info);
		dofile_csi2(video_cfg_file,&mipi_csi2);
		dofile_vi(video_cfg_file,&vi_cfg);
		f2k_cfg_file = &sensor0.sensor_cfg_file;
		r2k_cfg_file = &sensor1.sensor_cfg_file;
	}
	else
	{
		printf("%s:Error,no video_cfg_file!\n",__func__);
		return -1;
	}

	if((f2k_cfg_file != NULL)||(r2k_cfg_file != NULL))
	{

		if(f2k_cfg_file != NULL)
		{
			printf("%s:%s\n",__func__,f2k_cfg_file);

			dofile_isp(f2k_cfg_file,&sensor0);
			isp_pipeline = &v4l_isp.isp_pipeline[ISP_F2K];
			
			//
			sprintf(&isp_pipeline->sensor_name[0],"%s",&sensor0.sensor_name[0]);
			pipline_cfg(isp_pipeline,&sensor0);
			//
			vi_cfg.vi_pipe_cfg[0].total_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.width;
			vi_cfg.vi_pipe_cfg[0].total_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.height;
			vi_cfg.vi_pipe_cfg[0].in_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.width;
			vi_cfg.vi_pipe_cfg[0].in_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.height;
			vi_cfg.vi_pipe_cfg[1].total_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.width;
			vi_cfg.vi_pipe_cfg[1].total_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.height;
			vi_cfg.vi_pipe_cfg[1].in_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.width;
			vi_cfg.vi_pipe_cfg[1].in_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.height;
			vi_cfg.vi_pipe_cfg[2].total_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.width;
			vi_cfg.vi_pipe_cfg[2].total_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.total_size.height;
			vi_cfg.vi_pipe_cfg[2].in_size.width = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.width;
			vi_cfg.vi_pipe_cfg[2].in_size.height = sensor0.isp_cfg.isp_core_cfg.itcInfo.itc_size.height;
			//
			//isp_pipeline->pipeline_en = 1;
			sprintf(&isp_pipeline->video_entity_info[0].video_entity_name[0],"%s","CANAAN K510 ISP F2K output");
			sprintf(&isp_pipeline->video_entity_info[1].video_entity_name[0],"%s","CANAAN K510 ISP F2K_DS0 output");
			sprintf(&isp_pipeline->video_entity_info[2].video_entity_name[0],"%s","CANAAN K510 ISP F2K_DS1 output");
			sprintf(&isp_pipeline->video_entity_info[3].video_entity_name[0],"%s","CANAAN K510 ISP F2K_DS2 output");
			//
			//print_csi2_info(&mipi_csi2);
			//print_vi_info(&vi_cfg);
			//print_isp_info(&f2k_isp_cfg);
		}

		if(r2k_cfg_file != NULL)
		{
			printf("%s:%s\n",__func__,r2k_cfg_file);

			dofile_isp(r2k_cfg_file,&sensor1);
			isp_pipeline = &v4l_isp.isp_pipeline[ISP_R2K];
			//
			sprintf(&isp_pipeline->sensor_name[0],"%s",&sensor1.sensor_name[0]);
			pipline_cfg(isp_pipeline,&sensor1);
			//
			vi_cfg.vi_pipe_cfg[3].total_size.width = sensor1.isp_cfg.isp_core_cfg.itcInfo.total_size.width;
			vi_cfg.vi_pipe_cfg[3].total_size.height = sensor1.isp_cfg.isp_core_cfg.itcInfo.total_size.height;
			vi_cfg.vi_pipe_cfg[3].in_size.width = sensor1.isp_cfg.isp_core_cfg.itcInfo.itc_size.width;
			vi_cfg.vi_pipe_cfg[3].in_size.height = sensor1.isp_cfg.isp_core_cfg.itcInfo.itc_size.height;
			//
			//isp_pipeline->pipeline_en = 1;
			sprintf(&isp_pipeline->video_entity_info[0].video_entity_name[0],"%s","CANAAN K510 ISP R2K output");
			sprintf(&isp_pipeline->video_entity_info[1].video_entity_name[0],"%s","CANAAN K510 ISP R2K_DS0 output");
			sprintf(&isp_pipeline->video_entity_info[2].video_entity_name[0],"%s","CANAAN K510 ISP R2K_DS1 output");
			sprintf(&isp_pipeline->video_entity_info[3].video_entity_name[0],"%s","CANAAN K510 ISP R2K_DS2 output");
		}
	}
	else
	{
		printf("%s:Error,no f2k_cfg_file or no r2k_cfg_file!\n",__func__);
		return -1;
	}

	/* Open the media device and setup the capture pipeline. The pipeline
	 * topology is hardcoded to sensor -> dphy->csi2->f2k -> f2k output.
	 */
    int flags = 0; //0--close debug info ;1--open debug info
	v4l_isp.mdev = media_open(MEDIA_DEVICE, flags);
	if (v4l_isp.mdev == NULL) {
		printf("%s error: unable to open media device %s\n", __func__,MEDIA_DEVICE);
		return -1;
	}  
    //
	ret = isp_pipeline_setup(&v4l_isp);
	if (ret < 0) {
		printf("%s error: unable to setup pipeline\n", __func__);
		return -1;
	}
	//
#if 0
	ret = sysctl_rst_mipicsi2(v4l_isp.csi2);
	if (ret < 0) {
		printf("%s:error: unable to sysctl_rst_mipicsi2 %d\n",__func__,ret);
		return -1;
	}

	ret = sysctl_rst_vi(v4l_isp.vi);
	if (ret < 0) {
		printf("%s:error: unable to sysctl_rst_vi %d\n",__func__,ret);
		return -1;
	}

	ret = sysctl_rst_f2k(v4l_isp.f2k);
	if (ret < 0) {
		printf("%s:error: unable to sysctl_rst_f2k %d\n",__func__,ret);
		return -1;
	}

	ret = sysctl_rst_r2k(v4l_isp.r2k);	
	if (ret < 0) {
		printf("%s:error: unable to sysctl_rst_r2k %d\n",__func__,ret);
		return -1;
	}
#endif
	//
	if(isp_share_memory_alloc())
		return -1;
	//
	if( v4l_isp.isp_pipeline[ISP_F2K].pipeline_en == 1 )
	{
		ret = isp_f2k_cfg(v4l_isp.f2k,&sensor0.isp_cfg,allocAlignMem[0].phyAddr);
		if (ret < 0) {
			printf("%s:error: unable to f2k cfg video %d\n",__func__,ret);
			return -1;
		}
	}

	if( v4l_isp.isp_pipeline[ISP_R2K].pipeline_en == 1 )
	{
		ret = isp_r2k_cfg(v4l_isp.r2k,&sensor1.isp_cfg,allocAlignMem[1].phyAddr);
		if (ret < 0) {
			printf("%s:error: unable to r2k cfg video %d\n",__func__,ret);
			return -1;
		}		
	}
	//
	printf("%s:total_size.width(0x%x),total_size.height(0x%x)\n",__func__,vi_cfg.vi_pipe_cfg[0].total_size.width,vi_cfg.vi_pipe_cfg[0].total_size.height);
	//
	ret = isp_vi_cfg(v4l_isp.vi,&vi_cfg);
	if (ret < 0) {
		printf("%s:error: unable to isp vi cfg %d\n",__func__,ret);
		return -1;
	}
	//
	ret = mipicsi2_cfg(v4l_isp.csi2,&mipi_csi2);
	if (ret < 0) {
		printf("%s:error: unable to mipi_csi2 cfg %d\n",__func__,ret);
		return -1;
	}

#if 0
	if((v4l_isp.isp_pipeline[ISP_F2K].pipeline_en == 1) && ( v4l_isp.isp_pipeline[ISP_R2K].pipeline_en == 1 ))
	{
		pthread_create(&isp_all_ae,NULL,run_all_ae_video,NULL);
	}
	else if( v4l_isp.isp_pipeline[ISP_F2K].pipeline_en == 1 )
	{
		pthread_create(&isp_f2k_ae,NULL,run_f2k_ae_video,NULL);
	}
	else if( v4l_isp.isp_pipeline[ISP_R2K].pipeline_en == 1 )
	{
		pthread_create(&isp_r2k_ae,NULL,run_r2k_ae_video,NULL);
	}
#else
	if(v4l_isp.isp_pipeline[ISP_R2K].pipeline_en == 1 && v4l_isp.isp_pipeline[ISP_F2K].pipeline_en == 1) {
		pthread_create(&isp_all_ae, NULL, run_all_ae_video, NULL);
		//pthread_create(&isp_r2k_ae, NULL, run_r2k_ae_video, NULL);
		//pthread_create(&isp_f2k_ae, NULL, run_f2k_ae_video, NULL);
	} else if (v4l_isp.isp_pipeline[ISP_R2K].pipeline_en == 1) {
		pthread_create(&isp_r2k_ae, NULL, run_r2k_ae_video, NULL);
	} else if( v4l_isp.isp_pipeline[ISP_F2K].pipeline_en == 1 ) {
		pthread_create(&isp_f2k_ae, NULL, run_f2k_ae_video, NULL);
	}

#endif
	return 0;
}
/**
 * @brief 
 * 
 */
 int mediactl_set_ae(enum isp_pipeline_e pipeline)
{
	int ret;
#if 0
	if(Sensor1_Sync == FALSE)
	{
		ret = mediactl_set_ae_single(pipeline);
	}
	else
	{
		if(pipeline == ISP_F2K_PIPELINE)
		{
			ret = mediactl_set_ae_sync(pipeline);
			ret = mediactl_set_awb_sync(pipeline);
		}
	}
#endif
	return ret;
}


int mediactl_set_ae_single(enum isp_pipeline_e pipeline)
{
	int ret, i;
	struct k510isp_ae_stats ae_stats;
	struct media_entity *pipe;
	static unsigned int ET_sensor0 = 0;
	static unsigned int ET_sensor1 = 0;
	static unsigned int Gain_sensor0 = 0;
	static unsigned int Gain_sensor1 = 0;
	
	if(ISP_F2K_PIPELINE == pipeline)
	{
	
		pipe = v4l_isp.f2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;

		ret = ioctl(pipe->fd,VIDIOC_K510ISP_F2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_F2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);
		//
		struct media_entity *sensor0 = v4l_isp.sensor0;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor0);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			
			if (ae_stats.ae_expl != ET_sensor0)
			{
				control_s.id = V4L2_CID_EXPOSURE;
				control_s.value = ae_stats.ae_expl;
				ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor0);
					return ret;
				}
				ET_sensor0 = control_s.value;
			}

			if(ae_stats.ae_agco != Gain_sensor0)
			{
				control_s.id = V4L2_CID_GAIN;
				control_s.value = ae_stats.ae_agco;
				ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor0);
					return ret;
				}
				Gain_sensor0 = control_s.value;
			}
			v4l2_subdev_close(sensor0);
		}
	}

	if(ISP_R2K_PIPELINE == pipeline)
	{

		pipe = v4l_isp.r2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;

		ret = ioctl(pipe->fd,VIDIOC_K510ISP_R2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_R2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);
		//
		struct media_entity *sensor1 = v4l_isp.sensor1;
		if( ae_stats.ae_wren == 1)
		{
			ret = v4l2_subdev_open(sensor1);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;

			if (ae_stats.ae_expl != ET_sensor1)
			{
			
				control_s.id = V4L2_CID_EXPOSURE;
				control_s.value = ae_stats.ae_expl;
				ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor1);
					return ret;
				}
				ET_sensor1 = control_s.value;
			}
			
			if(ae_stats.ae_agco != Gain_sensor1)
			{
				control_s.id = V4L2_CID_GAIN;
				control_s.value = ae_stats.ae_agco;
				ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor1);
					return ret;
				} 		
				Gain_sensor1 = control_s.value;
			}
			v4l2_subdev_close(sensor1);
		}
	}
	
	return 0;
}

int mediactl_set_ae_sync(enum isp_pipeline_e pipeline)
{
	int ret;
	struct k510isp_ae_stats ae_stats;
	struct media_entity *pipe;
	static unsigned int ET_current = 0;
	static unsigned int Gain_current = 0;

	if(ISP_F2K_PIPELINE == pipeline)
	{
		pipe = v4l_isp.f2k;
		ret = v4l2_subdev_open(pipe);
		if (ret < 0)
			return ret;

		ret = ioctl(pipe->fd,VIDIOC_K510ISP_F2K_AE_STAT_REQ,&ae_stats);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_F2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(pipe);
			return ret;
		}
		//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
		v4l2_subdev_close(pipe);
		//
		if( ae_stats.ae_wren == 1)
		{
			//sensor0
			struct media_entity *sensor0 = v4l_isp.sensor0;
			ret = v4l2_subdev_open(sensor0);
			if (ret < 0)
				return ret;
			
			//sensor1
			struct media_entity *sensor1 = v4l_isp.sensor1;
			ret = v4l2_subdev_open(sensor1);
			if (ret < 0)
				return ret;

			struct v4l2_control  control_s;
			
			//Set ET		
			if(ae_stats.ae_expl != ET_current)
			{
				control_s.id = V4L2_CID_EXPOSURE;
				control_s.value = ae_stats.ae_expl;
				ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor1);
					return ret;
				} 
				
				ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor0);
					return ret;
				}
				ET_current = control_s.value;
			}
			//Set gain
			if(ae_stats.ae_agco != Gain_current)
			{
				control_s.id = V4L2_CID_GAIN;
				control_s.value = ae_stats.ae_agco;
				ret = ioctl(sensor1->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor1);
					return ret;
				}
				ret = ioctl(sensor0->fd,VIDIOC_S_CTRL,&control_s);
				if (ret < 0)
				{
					printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
						  ret);
					v4l2_subdev_close(sensor0);
					return ret;
				} 
				Gain_current = control_s.value;
			}
			v4l2_subdev_close(sensor1);
			v4l2_subdev_close(sensor0);	
		}
	}
	
	return 0;
}

int mediactl_set_awb_sync(enum isp_pipeline_e pipeline)
{
	int ret;
	struct k510isp_awb_sync_info awb_sync_info;
	static unsigned int awb_prev_frame_rgain = 0,awb_prev_frame_bgain = 0;
	struct media_entity *pipe_f2k,*pipe_r2k;
	pipe_f2k = v4l_isp.f2k;
	pipe_r2k = v4l_isp.r2k;

	if(Awb_Sync_Init)
	{
		isp_awb_sync_init();
		Awb_Sync_Init = FALSE;
	}

	if(ISP_F2K_PIPELINE == pipeline)
	{
		// get f2k awb ctl mode auto or handle
		ret = v4l2_subdev_open(pipe_f2k);
		if (ret < 0)
			return ret;

		ret = v4l2_subdev_open(pipe_r2k);
		if (ret < 0)
			return ret;

		// get f2k AWB GAIN VALUE
		ret = ioctl(pipe_f2k->fd,VIDIOC_K510ISP_F2K_AWB_VAL_GET,&awb_sync_info);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_K510ISP_F2K_AWB_VAL_GET) failed ret(%d)\n", __func__,ret);
			v4l2_subdev_close(pipe_f2k);
			return ret;
		}

		// if value change set f2k AWB GAIN VALUE to r2k
		if ((awb_sync_info.awb_ar != awb_prev_frame_rgain) || (awb_sync_info.awb_ab != awb_prev_frame_bgain))
		{
			if (ret < 0)
				return ret;
			ret = ioctl(pipe_r2k->fd,VIDIOC_K510ISP_R2K_AWB_VAL_SET,&awb_sync_info);
			if (ret < 0)
			{
				printf("%s: ioctl(VIDIOC_K510ISP_R2K_AWB_VAL_SET) failed ret(%d)\n", __func__,ret);
				v4l2_subdev_close(pipe_r2k);
				return ret;
			}
		}
		awb_prev_frame_rgain = awb_sync_info.awb_ar;
		awb_prev_frame_bgain = awb_sync_info.awb_ab;
		v4l2_subdev_close(pipe_f2k);
		v4l2_subdev_close(pipe_r2k);
	}
	return 0;
}

/**
 * @brief 
 * 
 */
void mediactl_exit(void)
{
	//
	isp_share_memory_free();
	//
	if (v4l_isp.mdev == NULL)
	{
		media_close(v4l_isp.mdev);
	}
/*
	pthread_kill(isp_f2k_ae, SIGALRM); 
	pthread_join(isp_f2k_ae, NULL);

	pthread_kill(isp_r2k_ae, SIGALRM); 
	pthread_join(isp_r2k_ae, NULL);
*/
	//
    system("sync");
    system("echo 1 > /proc/sys/vm/drop_caches");
    system("echo 2 > /proc/sys/vm/drop_caches");
    system("echo 3 > /proc/sys/vm/drop_caches");
}
/**
 * @brief 
 * 
 * @param addr 
 * @return unsigned int 
 */

unsigned int ISPRegRead(unsigned int addr)
{
    char result[64] = {0};
	char buf[64] = {0};
    char cmd[64] = {0};
    unsigned ret;
    FILE *fp = NULL;

    sprintf(cmd, "devmem 0x%08X\n", addr);

    if( (fp = popen(cmd, "r")) == NULL ) {
        printf("popen error!\n");
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        strcat(result, buf);
    }
    pclose(fp);
    // printf("result: %s\n", result);

    ret = strtol(result, NULL, 16);
    return ret;

}

unsigned int ISPRegWrite(unsigned int addr, unsigned int value)
{
    char cmd[64] = {0};
    unsigned ret;
    FILE *fp = NULL;

    sprintf(cmd, "devmem 0x%08X 32 0x%08X\n", addr, value);

    if( (fp = popen(cmd, "w")) == NULL ) {
        printf("popen error!\n");
        return -1;
    }
    pclose(fp);
    return 1;
}



