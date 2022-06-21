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
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h> 
#include <assert.h>
#include <errno.h>
#include "lib_twod.h"


uint32_t twod_creat_dump(int fd, uint32_t size)
{
    struct share_memory_alloc_align_args  allocAlignMem;

    allocAlignMem.size = (size + 0xfff) & (~0xfff);
    allocAlignMem.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMem.phyAddr = 0;

    if(ioctl(fd, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem) < 0)
    {
        printf("alloc_memory Error!\n");
        return -1;
    }
    printf("%s>phy_addr 0x%x, size %d\n", __FUNCTION__, allocAlignMem.phyAddr, allocAlignMem.size);

    return allocAlignMem.phyAddr;
}

void twod_free_mem(int fd, uint64_t phyaddr)
{
    if(ioctl(fd, SHARE_MEMORY_FREE, &phyaddr) < 0) {

        printf("share memory  SHARE_MEMORY_FREE error!\r\n");
    }
}

void twod_wait_vsync(int fd)
{
	struct pollfd twod_fd;

	twod_fd.fd  = fd;
    twod_fd.events = POLLIN;

	poll(&twod_fd, 1, -1);
    if(twod_fd.events==POLLIN) {
        printf("User: gnne complete\n");
    }
}



int twod_set_rot(int fd, struct td_image_info *src, struct td_image_info *des)
{
    struct td_info td_info;
    int ret = 0;
    memcpy(&td_info.src, src, sizeof(struct td_image_info));
    memcpy(&td_info.dsc, des, sizeof(struct td_image_info));

    td_info.mode = TWOD_ROT_270;//TWOD_ROT_90;

    if(ioctl(fd, KENDRYTE_TWOD_SET_DATA, &td_info) < 0) {
        printf("ERR: Gnne set pc err\n");
        ret = -1;
    }

    return ret;
}

int twod_set_scaler(int fd, struct td_image_info *src, struct td_image_info *des, int use_osd)
{
    struct td_info td_info;
    int ret = 0;
    memcpy(&td_info.src, src, sizeof(struct td_image_info));
    memcpy(&td_info.dsc, des, sizeof(struct td_image_info));

    if(use_osd == 0)
    {
        td_info.mode = TWOD_SCALE;
    }
    else
    {
        td_info.mode = TWOD_SCALE_OSD;
    }
    
    if(ioctl(fd, KENDRYTE_TWOD_SET_DATA, &td_info) < 0) {
        printf("ERR: Gnne set pc err\n");
        ret = -1;
    }
    return ret;
}

int twod_set_osd(int fd, struct td_image_info *osd)
{
    struct td_info td_info;
    int ret = 0;
    memcpy(&td_info.src, osd, sizeof(struct td_image_info));
 
    td_info.mode = TWOD_SET_OSD;

    if(ioctl(fd, KENDRYTE_TWOD_SET_DATA, &td_info) < 0) {
        printf("ERR: Gnne set pc err\n");
        ret = -1;
    }
    return ret;
}


int twod_rgb2yuv(int fd, struct td_image_info *src, struct td_image_info *des)
{
    struct td_info td_info;
    int ret = 0;

    memcpy(&td_info.src, src, sizeof(struct td_image_info));
    memcpy(&td_info.dsc, des, sizeof(struct td_image_info));
 
    td_info.mode = TWOD_ONLY_OSD;

    if(ioctl(fd, KENDRYTE_TWOD_SET_DATA, &td_info) < 0) {
        printf("ERR: Gnne set pc err\n");
        ret = -1;
    }
    return ret;
}


int twod_InvalidateCache(int fd, uint64_t phyAddr, void* vAddr, unsigned int size)
{
    struct memory_cache_sync_request request;

    //printf("%s>phyAddr 0x%x, vaddr %p, size %d\n", __FUNCTION__, phyAddr, vAddr, size);

    request.paddr = phyAddr;
    request.vaddr = (uint64_t)vAddr;
    request.size  = size;

    if(ioctl(fd, SHARE_MEMORY_INVAL_RANGE, &request) < 0)
    {
        printf("fd invalidate range op failure!\r\n");
        return -1;
    }

    return 0;
}

int twod_flashdateCache(int fd, uint64_t phyAddr, void* vAddr, unsigned int size)
{
    struct memory_cache_sync_request request = {};

    request.paddr = phyAddr;

    request.vaddr = (uint64_t)vAddr;

    request.size = size;

    if(ioctl(fd, SHARE_MEMORY_WB_RANGE, &request) < 0) {
        printf("rf wb range op failure!\r\n");
        return -1;
    }
}









