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
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "lib_twod.h"

#define KENDRYTE_TD "/dev/twod"

#define IMAGE_NAME1 "./input.yuv"
#define IMAGE_NAME2 "./output.yuv"
#define IMAGE_NAME3 "./canaan_logo_320x240.argb"


struct buffer_object {
	uint32_t width;
	uint32_t height;
	uint32_t pitch;
	uint32_t handle;
	uint32_t size;
	uint32_t bpp;
	uint32_t format;

	uint32_t yrgb_addr; /* yrgb    mem addr         */
	uint32_t uv_addr; /* cb/cr   mem addr         */
	uint32_t *vaddr;

	uint32_t v_step;
	uint32_t v_st_pstep;
	uint32_t h_step;
	uint32_t h_st_pstep;
};

struct buffer_object buf[3]; // 定义两个buff
int fd_share_memory = -1;
int fd_mem_map = -1;

static int twod_create_fb(struct buffer_object *bo)
{
	uint32_t size = 0;

	size = bo->size;

	bo->yrgb_addr = twod_creat_dump(fd_share_memory, size);
	bo->uv_addr = bo->yrgb_addr + (bo->pitch * bo->height);
	bo->vaddr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,
			 fd_mem_map, bo->yrgb_addr);
}

#if 0
static void twod_set_src_picture(struct buffer_object *bo, uint32_t v_step, uint32_t h_step, uint32_t v_st_pstep, uint32_t h_st_pstep)
{
#if 1
	bo->width = 320 ;// 1080;
	bo->height = 352;//1920;
#else
	bo->width = 320;
	bo->height = 240;
#endif
	bo->pitch = bo->width;
	bo->bpp = 0;
	bo->size = bo->width * bo->height * 3 / 2 ;			// yuv420
	bo->format = TWOD_FORMAT_YUV420SP;
    bo->v_step = v_step;
    bo->h_step = h_step;
    bo->v_st_pstep = v_st_pstep;
    bo->h_st_pstep = h_st_pstep;
}
#else
static void twod_set_src_picture(struct buffer_object *bo)
{
#if 1
	bo->width = 320; // 320 ;// 1080;
	bo->height = 240; // 352;//1920;
#else
	bo->width = 320;
	bo->height = 240;
#endif
	bo->pitch = bo->width;
	bo->bpp = 0;
	bo->size = bo->width * bo->height * 3 / 2; // yuv420
	bo->format = TWOD_FORMAT_YUV420SP;
}

#endif

static void twod_set_osd_layer(struct buffer_object *bo)
{
	#if 1
	bo->width = 320;
	bo->height = 240;
#else
	bo->width = 240;
	bo->height = 320;
#endif
	bo->pitch = (bo->width * 4) >> 3;//bo->width;
	bo->bpp = 8;

	bo->size = bo->width * bo->height * 4; 
	bo->format = TWOD_FORMAT_ARGB8888;
}


void twod_set_scaler_step(struct buffer_object *src, struct buffer_object *des)
{
	float v_st_pstep, h_st_pstep;
	float src_width, src_height, des_width, des_height;
	uint32_t v_step, h_step;

	/*
	src_width = (float)src->width;
	des_width = (float)des->width;
	*/
	src_height = (float)src->height;
	des_height = (float)des->height;

	if (src->width >= des->width) {
		h_step = src->width / des->width;
		h_st_pstep =
			(((float)src->width / (float)des->width) - h_step) *
			65536;
		src->h_step = h_step + ((uint32_t)h_st_pstep << 16);

	} else {
		h_st_pstep = ((float)src->width / (float)des->width) * 65536;
		src->h_step = 0 + ((uint32_t)h_st_pstep << 16);
	}

	if (src->height >= des->height) {
		v_step = src->height / des->height;
		v_st_pstep =
			(((float)src->height / (float)des->height) - v_step) *
			65536;
		src->v_step = v_step + ((uint32_t)v_st_pstep << 16);

	} else {
		v_st_pstep = ((float)src->height / (float)des->height) * 65536;
		src->v_step = ((uint32_t)v_st_pstep << 16);
	}

	src->v_st_pstep = 0;
	src->h_st_pstep = 0;
}

static void twod_set_des_picture(struct buffer_object *bo)
{
#if 1
	bo->width = 320; // 800;//1280;//640;//720;//176;//640;
	bo->height = 240; // 600;//960  ;//480;//480;//144;//480;
#else
	bo->width = 240;
	bo->height = 320;
#endif
	bo->pitch = bo->width;
	bo->bpp = 8;
	bo->size = bo->pitch * bo->height * 3 / 2 ;			// yuv422
	bo->format = TWOD_FORMAT_YUV420SP;
}

void twod_config_scaler_image(struct td_image_info *td_info,
			      struct buffer_object *buf)
{
	td_info->act_w = buf->width;
	td_info->act_h = buf->height;
	td_info->pitch = buf->pitch;
	td_info->format = buf->format;
	td_info->yrgb_addr = buf->yrgb_addr;
	td_info->uv_addr = buf->uv_addr; 
	td_info->v_addr = 0;
	td_info->bpp = buf->bpp;
	td_info->v_step = buf->v_step;
	td_info->h_step = buf->h_step;
	td_info->v_st_pstep = buf->v_st_pstep;
	td_info->h_st_pstep = buf->h_st_pstep;
	td_info->x_offset = 0;
	td_info->y_offset = 0;

	printf("td_info->v_step is %x  td_info->h_step is %x \n",
	       td_info->v_step, td_info->h_step);
}

int main(void)
{
	struct td_image_info *src, *des, *osd;
	int fd;
	int ret = 0;
	FILE *fd1, *fd2, *fd3;
	src = malloc(sizeof(struct td_image_info));
	des = malloc(sizeof(struct td_image_info));
	osd = malloc(sizeof(struct td_image_info));

	fd_share_memory = open(SHARE_MEMORY_DEV, O_RDWR);
	if (fd_share_memory < 0) {
		printf("open %s error!\r\n", SHARE_MEMORY_DEV);
		return 1;
	}

	fd_mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
	if (fd_mem_map < 0) {
		printf("CMEM: failed to open /dev/mem!");
		return 1;
	}

	fd = open(KENDRYTE_TD, O_RDWR);
	if (fd < 0) {
		printf("open %s error!\r\n", KENDRTY_2D);
		return 1;
	}

	// set picture
	// twod_set_src_picture(&buf[0], 0xbbbb0000, 0x80000000, 0, 0);
	twod_set_src_picture(&buf[0]);
	twod_set_des_picture(&buf[1]);
	twod_set_osd_layer(&buf[2]);

	twod_set_scaler_step(&buf[0], &buf[1]);

	// creat fb
	twod_create_fb(&buf[0]); // src picture
	twod_create_fb(&buf[1]); // des picture
	twod_create_fb(&buf[2]); // des picture

	twod_config_scaler_image(src, &buf[0]);
	twod_config_scaler_image(des, &buf[1]);
	twod_config_scaler_image(osd, &buf[2]);

#if 0
	// write image
	// read image
	fd2 = fopen(IMAGE_NAME1, "rb");
	if (fd2 == NULL) {
		fd2 = fopen(IMAGE_NAME1, "wb");
		uint8_t yuv[1920 * 1080 * 3 / 2];
		uint8_t color = 0x10;
		int8_t step = 1;
		for (int i = 0; i < 1080; i++) {
			memset(yuv + 1920 * i, color, 1920);
			if (color == 0x10)
				step = 1;
			else if (color == 0xeb)
				step = -1;
			color += step;
		}
		memset(yuv + 1920 * 1080, 0x80, 1920 * 1080 / 2);
		fwrite(yuv, sizeof(yuv), 1, fd2);
		fclose(fd2);
		fd2 = fopen(IMAGE_NAME1, "rb");
		if (fd2 == NULL) {
			printf("open %s failure, errno %d\n", IMAGE_NAME1,
			       errno);
			return 1;
		}
	}
	printf("open %s success \n", IMAGE_NAME1);
#endif
	fd3 = fopen(IMAGE_NAME3, "rb");
	if (fd3 == NULL) {
		printf("open %s failure, errno %d\n", IMAGE_NAME3,
				errno);
		return 1;
	}
	printf("open %s success \n", IMAGE_NAME3);

	printf("buf[2].width is %d  buf[2].height is %d\n", buf[2].width,  buf[2].height);

	// get osd image
	ret = fread(buf[2].vaddr, (buf[2].width * buf[2].height) * 4, 1,
		    fd3); // 3110400 = 1080 * 1920 * 1.5
	if (ret <= 0) {
		printf("fread  picture_addr IMAGE_NAME3 is failed ret is %d \n", ret);
		return 1;
	}

	printf("read %s success \n", IMAGE_NAME3);

#if 0
	// get output image
	ret = fread(buf[0].vaddr, (buf[0].width * buf[0].height) * 3 / 2, 1,
		    fd2); // 3110400 = 1080 * 1920 * 1.5
	if (ret <= 0) {
		printf("fread  picture_addr is failed ret is %d \n", ret);
		return 1;
	}
#endif

	twod_flashdateCache(fd_share_memory, buf[0].yrgb_addr, buf[0].vaddr,
			    buf[0].size);

	twod_flashdateCache(fd_share_memory, buf[1].yrgb_addr, buf[1].vaddr,
			    buf[1].size);

	twod_set_osd(fd, osd);

	twod_rgb2yuv(fd, src, des);

	printf("wait vync \n");

	twod_wait_vsync(fd);

	twod_InvalidateCache(fd_share_memory, buf[1].yrgb_addr, buf[1].vaddr,
			     buf[1].size);

	fd1 = fopen(IMAGE_NAME2, "wb");
	if (fd1 == NULL) {
		printf("open %s failure, errno %d\n", IMAGE_NAME2, errno);
		return 1;
	}
	printf("open %s success \n", IMAGE_NAME2);

	ret = fwrite(buf[1].vaddr, (buf[1].width * buf[1].height) * 3 / 2, 1,
		     fd1); // 3110400 = 1080 * 1920 * 1.5
	if (ret <= 0) {
		printf("fwrite  picture_addr is failed ret is %d \n", ret);
		return 1;
	}

	printf("fwrite %s success \n", IMAGE_NAME2);

	close(fd);
	fclose(fd1);
///	fclose(fd2);

	free(src);
	free(des);
	free(osd);

	twod_free_mem(fd_share_memory, buf[0].yrgb_addr);
	twod_free_mem(fd_share_memory, buf[1].yrgb_addr);
	twod_free_mem(fd_share_memory, buf[2].yrgb_addr);
}