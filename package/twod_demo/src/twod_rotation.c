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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "lib_twod.h"

#define KENDRYTE_TD "/dev/twod"

#define IMAGE_NAME1 "./input.yuv"

#define IMAGE_NAME2 "./output.yuv"


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
	uint32_t v_addr; /* cr      mem addr         */

	uint32_t *vaddr;
};

struct buffer_object buf[2]; // 定义两个buff
int fd_share_memory = -1;
int fd_mem_map = -1;

static int twod_create_fb(struct buffer_object *bo)
{
	uint32_t size = 0;

	size = bo->size;

	bo->yrgb_addr = twod_creat_dump(fd_share_memory, size);

	bo->vaddr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,
			 fd_mem_map, bo->yrgb_addr);
	return 0;
}

static void twod_set_src_picture(struct buffer_object *bo)
{
#if 1
	bo->width = 1920;
	bo->height = 1080;
#else
	bo->width = 320;
	bo->height = 240;
#endif
	bo->pitch = bo->width;
	bo->bpp = 8;
	bo->size = bo->width * bo->height * 3 / 2; // yuv420
	bo->format = TWOD_FORMAT_YUV420SP;
}

static void twod_set_des_picture(struct buffer_object *bo)
{
#if 1
	bo->width = 1080;
	bo->height = 1920;
#else
	bo->width = 240;
	bo->height = 320;
#endif
	bo->pitch = bo->width;
	bo->bpp = 8;
	bo->size = bo->width * bo->height * 3 / 2; // yuv420
	bo->format = TWOD_FORMAT_YUV420SP;
}

void twod_config_rotation_image(struct td_image_info *td_info,
				struct buffer_object *buf)
{
	td_info->act_w = buf->width;
	td_info->act_h = buf->height;
	td_info->pitch =  buf->pitch;
	td_info->format = buf->format;
	td_info->yrgb_addr = buf->yrgb_addr;
	td_info->uv_addr = buf->yrgb_addr + (buf->pitch * buf->height);
	td_info->v_addr = 0;
	td_info->bpp = buf->bpp;
}

int main(void)
{
	struct td_image_info *src, *des;
	int fd;
	int ret = 0;
	FILE *fd1, *fd2;
	src = malloc(sizeof(struct td_image_info));
	des = malloc(sizeof(struct td_image_info));

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
	twod_set_src_picture(&buf[0]);
	twod_set_des_picture(&buf[1]);

	// creat fb
	twod_create_fb(&buf[0]); // src picture
	twod_create_fb(&buf[1]); // des picture

	twod_config_rotation_image(src, &buf[0]);
	twod_config_rotation_image(des, &buf[1]);

	// write image
	//read image
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

	// get output image
	ret = fread(buf[0].vaddr, (buf[0].width * buf[0].height) * 3 / 2, 1,
		    fd2); // 3110400 = 1080 * 1920 * 1.5
	if (ret <= 0) {
		printf("fread  picture_addr is failed ret is %d \n", ret);
		return 1;
	}

	twod_flashdateCache(fd_share_memory, buf[0].yrgb_addr, buf[0].vaddr,
			    buf[0].size);

	twod_set_rot(fd, src, des);

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

	free(src);
	free(des);

	twod_free_mem(fd_share_memory, buf[0].yrgb_addr);
	twod_free_mem(fd_share_memory, buf[1].yrgb_addr);

	// release mem
}
