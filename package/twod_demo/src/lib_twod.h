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
#ifndef __LIB_TWOD_H__
#define __LIB_TWOD_H__


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <poll.h>


#define  KENDRYTE_TWOD_GET_VERSION                  _IOWR('T', 0, unsigned long)
#define  KENDRYTE_TWOD_ASYNC                        _IOWR('T', 1, unsigned long)
#define  KENDRYTE_TWOD_SYNC                         _IOWR('T', 2, unsigned long)
#define  KENDRYTE_TWOD_SET_DATA                     _IOWR('T', 3, unsigned long)

/*******************************memory***************************************/
#define SHARE_MEMORY_ALLOC                          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC                    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE                           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW                           _IOWR('m', 4, unsigned long)
#define SHARE_MEMORY_INVAL_RANGE                    _IOWR('m', 5, unsigned long)
#define SHARE_MEMORY_WB_RANGE                       _IOWR('m', 6, unsigned long)

#define MEMORY_TEST_BLOCK_ALIGN                     4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */

#define SHARE_MEMORY_DEV                            "/dev/k510-share-memory"
#define KENDRTY_2D                                  "/dev/kendrty_2d0"
#define MAP_MEMORY_DEV                              "/dev/mem"


enum TWOD_FORMAT {
    TWOD_FORMAT_Y = 0,
    TWOD_FORMAT_YUV420SP = 1,
    TWOD_FORMAT_YUV422SP = 2,
    TWOD_FORMAT_RGB888 = 3,
    TWOD_FORMAT_ARGB8888 = 4,
};
enum TWOD_MODE {
    TWOD_ROT_90 = 1,
    TWOD_ROT_270 = 2,
    TWOD_SCALE = 3,
};


struct share_memory_alloc_align_args {
    unsigned int size;
    unsigned int alignment;
    unsigned int phyAddr;
};


struct memory_cache_sync_request {
    size_t size;
    uint64_t vaddr;
    uint64_t paddr;
};


struct td_image_info {

    uint32_t yrgb_addr;      /* yrgb    mem addr         */
    uint32_t uv_addr;        /* cb/cr   mem addr         */
    uint32_t v_addr;         /* cr      mem addr         */
    uint32_t format;         //definition by 
    uint32_t bpp;           /*  8bit  16bit   32bit */
    uint32_t pitch;
    uint32_t v_step;
    uint32_t v_st_pstep;
    uint32_t h_step;
    uint32_t h_st_pstep;
    unsigned short act_w;
    unsigned short act_h;
    unsigned short x_offset;
    unsigned short y_offset;
    unsigned short vir_w;
    unsigned short vir_h;
    unsigned int alpha_swap;
    
};


struct td_info {
    struct td_image_info src;      // if rotattion src , if scale layer0
    struct td_image_info dsc;      // if rotattion src,  if scale osd0
    uint32_t mode;   

};


uint32_t twod_creat_dump(int fd, uint32_t size);
void twod_free_mem(int fd, uint64_t phyaddr);
void twod_wait_vsync(int fd);
int twod_set_rot(int fd, struct td_image_info *src, struct td_image_info *des);
int twod_set_scaler(int fd, struct td_image_info *src, struct td_image_info *des);
int twod_InvalidateCache(int fd, uint64_t phyAddr, void* vAddr, unsigned int size);
int twod_flashdateCache(int fd, uint64_t phyAddr, void* vAddr, unsigned int size);

#endif