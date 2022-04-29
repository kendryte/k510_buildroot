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
#include <signal.h>
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

#include "isp_com.h"

#include <pthread.h>
#include <poll.h>

/*******************************memory***************************************/
#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)


#define MEMORY_TEST_BLOCK_NUM   10          /* 测试多少次申请释放 */
#define MEMORY_TEST_BLOCK_SIZE  4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */

#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"



struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};

int fd_share_memory = -1;
int isp_fd = -1;
struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM];



void fun_sig(int sig)
{
    if(sig == SIGINT)
    {
        printf("exit crtl -------------------------------------------------- c\n");

#if 1
        ISP_REG_S reg_isp={0,0};
        reg_isp.id = ISP_2K_BASE_ADDR + 0x10 - VIDEO_SUBSYSTEM_BASE_ADDR;
        reg_isp.value = 0x00;
        //printf("isp_reg_writel:addr = 0x%x,data = 0x%x\n",addr,data);
        if (ioctl(isp_fd, ISP_CMD_WRITE_REG, &reg_isp) < 0)
        {
            printf("Call cmd ISP_CMD_WRITE_REG fail, reg addr = 0x%x\n", reg_isp.id);
        }
        
        isp_exit();

        if(ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[0].phyAddr) < 0) {
            printf("share memory  SHARE_MEMORY_FREE error!\r\n");
        }
#endif
        imx219_close_sensor();
    }
    exit(0);
}

void *h264_test(void *arg)
{
    int ret = -1;
    struct pollfd isp_fds;//定义一个pollfd结构体gnne_fds
    int h264_cut = 0;
    int i = 0;
    struct ds_data h264;
    printf("start h264_test \n");

    isp_fds.fd  = fd_isp;
    isp_fds.events = POLLIN;

    while(1)
    {
        poll(&isp_fds, 1, -1);
        if(isp_fds.events==POLLIN) {

            ret = read(fd_isp, &h264, sizeof(h264));
            if(ret < 0)
            {
                printf("read fd error \n");
            }
//            vo_change_laye1_addr(h264.addr, h264.addr + (1080 *720));
            h264_cut ++ ;
            if(h264_cut == 60 + i)
            {
                i ++ ;
                if(i == 4)
                    i = 0;

                h264_cut = 0;
                printf("User: gnne completeh 264 addr is %x 264 addr id is %d \n", h264.addr, h264.isp_irq_id);
            }     
        }
    }  
}

int main(int argc, char **argv)
{
    FILE *fd4;

    int fd_share_memory = -1;
//    struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM];
    pthread_t pthreads;


    #define IMAGE_NAME4  "./Canaanlogo_640x480_argb8888_stride2560_rgb.bmp.argb"
    printf("isp demo!\n");

    signal(SIGINT, fun_sig);

    fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR);
    if(fd_share_memory < 0) {
        printf("open %s error!\r\n",SHARE_MEMORY_DEV);
        return 1 ;
    }

    DS2_INFO ds2_info;
    ds2_info.ds2_en = 1;
    ds2_info.ds2_width = 320;//640;//1080;//320;
    ds2_info.ds2_height = 256;//;//720;//180;
    ds2_info.ds2_rgb_type = DS2_S_RGB;//DS2_ARGB;//;DS2_S_RGB

    DS1_INFO ds1_info;
    ds1_info.ds1_en = 1;
    ds1_info.ds1_width = 1920;//640;//1080;//320;
    ds1_info.ds1_height = 1080;//;//720;//180;
    ds1_info.stride = ((1920) + 15) / 16 * 16;

	VO_OSD_INFO osd1_info;
    osd1_info.osd_en = 0;
    osd1_info.osd_width = 640;
    osd1_info.osd_height = 480;
    osd1_info.osd_ctl.osd1_type = OSD_RGB_32BIT;//OSD_RGB_24BIT;//OSD_RGB_32BIT;
    osd1_info.osd_ctl.osd1_rgb_rev = OSD_RGB_REV_R;//OSD_RGB_REV_R;//OSD_RGB_REV_B
    osd1_info.osd_ctl.osd1_dma_ctl = OSD_ORIGINAL_ORDER;
    VO_OSD_INFO osd0_info;
    osd0_info.osd_en = 0;
	unsigned int draw_demo_en = 1;
	unsigned int debug_enable = 0;//1;

    SENSOR_TYPE sensor_type = IMX219_SENSOR;//IMX219_SENSOR;//JFX23S_SENSOR;//IMX385_SENSOR;
    LCD_TYPE lcd_type = HX8399;//HX8399;//HX8399;//ITI7807_LCD; //AML550_LCD; //BT1120_DISPALY


    // Allocate memory for ds1
    allocAlignMem[0].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 14;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
    allocAlignMem[0].alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMem[0].phyAddr   = 0;
    
    if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[0]) < 0) {
        printf("ds1 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
        return -1;
    }
    else {
        printf("ds1 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[0].phyAddr,allocAlignMem[0].size,allocAlignMem[0].alignment);
    }
    ds1_info.y_addr = allocAlignMem[0].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;


    if(1 == ds2_info.ds2_en)
    {
        allocAlignMem[1].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[1].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[1].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[1]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[1].phyAddr,allocAlignMem[1].size,allocAlignMem[1].alignment);
        }

        ds2_info.r_addr = allocAlignMem[1].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;

        unsigned int ds2_stride = (ds2_info.ds2_width +15)/16*16;
        printf("ds2_out_addr =0x%x,ds2_stride = 0x%x\n",ds2_info.r_addr,ds2_stride);

        if(DS2_S_RGB == ds2_info.ds2_rgb_type)
        {
            ds2_info.g_addr = ds2_info.r_addr + ds2_stride * ds2_info.ds2_height;
            ds2_info.b_addr = ds2_info.g_addr + ds2_stride * ds2_info.ds2_height;
        }
        else
        {
            ds2_info.g_addr = ds2_info.r_addr + ds2_stride;
            ds2_info.b_addr = ds2_info.g_addr + ds2_stride;
        }        
    }

    isp_fd = isp_init(&ds2_info, &ds1_info, &osd0_info, &osd1_info, draw_demo_en, debug_enable, sensor_type, lcd_type);

    //pthread_create(&pthreads, NULL, h264_test, fd_isp);
	// print argb data
#if 0
	uint32_t img_addr = ai_get_buf_addr();
	uint8_t* pimg = (uint8_t*)(img_addr);
	printf("First Pixel:\n");
	for(uint32_t mm=0; mm<4; mm++)
	{
		printf("%d\t",  *(pimg + mm));
	}
#endif

#if 0
//        unsigned int jj = ai_get_buf_addr();
    uint8_t* pimg = (uint8_t*)ds_virtual_addr[0];

    printf("pimg = 0x%x\n",pimg);
    printf("pixel data = 0x%x\n", (uint8_t)(*pimg));
    for(uint32_t mm=0; mm<4; mm++)
    {
        printf("0x%x\n",  *(pimg + mm));
    }

    uint8_t* pimg1 = (uint8_t*)vo_osd_virtual_addr[0];


    printf("pimg1 = 0x%x\n",pimg1);
    printf("pixel data = 0x%x\n", (uint8_t)(*pimg1));
    for(uint32_t mm=0; mm<4; mm++)
    {
        printf("0x%x\n",  *(pimg1+ mm));
    }
#endif
	// draw a test box
	frame_coordinate_info test;
	test.startx = 200;
	test.starty = 200;
	test.endx = 400;
	test.endy = 400;
    printf("----------------------------------------------- \n");
    while(1)
    {
        draw_frame(1, 0, test);
        printf("open draw_frame \n");
        sleep(20);
        //draw_frame(0, 0, test);
        //printf("close draw_frame \n");
        //sleep(20);
    }
	
	return 0;
}
