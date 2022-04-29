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
/******************************************************************************
  File Name     : main.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/



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

#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


#include "sensor/sensor.h"

#include "vi/vi.h"
#include "vi/vi_com.h"
#include "vo/vo.h"
#include "vo/vo_com.h"
#include "exctl_dev/dev_hw.h"
#include "mipi/mipi.h"
#include "bt1120/bt1120.h"


#include "isp_com.h"
#include "isp_2k/isp.h"
#include "isp_2k/isp_f2k.h"
#include "isp_2k/isp_r2k.h"
#include "isp_2k/table/isp_table_drv.h"

#define DEV_NAME "/dev/test-isp"
#define DEV_NAME_I2C0 "/dev/test-i2c0"

#define IMAGE_NAME  "./1080x1920_nv12.yuv"
#define IMAGE_NAME1  "./dump_wb_1080p.yuv"
#define IMAGE_NAME2  "./isp_ds0.yuv"
#define IMAGE_NAME3  "./isp_ds2.argb"
#define IMAGE_NAME4  "./Canaanlogo_640x480_argb8888_stride2560_rgb.bmp.argb"
#define IMAGE_NAME5  "./Canaanlogo_640x480_argb8888_stride2560_gbr.bmp.argb"
#define IMAGE_NAME6  "./Canaanlogo_640x480_rgb888_stride1920_rgb.bmp.argb"
#define IMAGE_NAME7  "./Canaanlogo_640x480_rgb888_stride1920_bgr.bmp.argb"
#define IMAGE_NAME8  "4-fram.yuv" //""input.yuv"  //"./1080x1920_nv12.yuv"
struct isp_device isp;
//unsigned int isp_addr =0;
unsigned int picture_addr = 0;

int fd_isp;
int fd_i2c0;
int fd_drm;
ISP_REG_S reg_isp={0,0};

struct i2c0_reg {
        unsigned int id;
        unsigned int value;
};

struct isp_dmabuf {
    int fd;
    unsigned int dma_addr;
};

#define msleep(x) usleep(1000*x)

struct isp_dmabuf dma_y;

/*******************************memory***************************************/
#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)


#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"
#define MAP_MEMORY_DEV      "/dev/mem"
struct share_memory_alloc_args {
    uint32_t size;
    uint32_t phyAddr;
};

struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};

#define MEMORY_TEST_BLOCK_NUM   11          /* 测试多少次申请释放 */
#define MEMORY_TEST_BLOCK_SIZE  4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */

struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM] = {0};

int fd_share_memory = -1;
int fd_mem_map = -1;
int ds2_mem_size = 0;
int ds2_r_addr[5];
int ds2_v_addr[5];
//int *ds_virtual_addr[5];
int *virtual_addr[MEMORY_TEST_BLOCK_NUM]= {0};;
int *ds_virtual_addr[MEMORY_TEST_BLOCK_NUM]= {0};;
int *vo_osd_virtual_addr[MEMORY_TEST_BLOCK_NUM] = {0};

struct memory_cache_sync_request OSD1layer5DisplayGnne = {0,0,0};
struct memory_cache_sync_request ispOutputForGnne = {0,0,0};
struct memory_cache_sync_request ispOutputForDisplay = {0,0,0};
struct memory_cache_sync_request OSD0layer4DisplayText = {0,0,0};
/*
*
*/
void imx385_1920x1080_normal_vi_isp_config(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    //InitIsp_1920x1080(isp_addr,isp_size);
	InitIsp_f2k_1920x1080_new(isp,isp_addr,isp_size,IMX385_SENSOR);         

    video_in_imx385_normal_12bit_new(isp,isp_addr,isp_size);
    
    mipi_csi_2lane_init(isp);
    return;
}
/**
 * @brief 
 * 
 * @param isp 
 * @param isp_addr 
 * @param isp_size 
 */
void imx219_1920x1080_normal_vi_isp_config(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    //InitIsp_1920x1080(isp_addr,isp_size);
	InitIsp_f2k_1920x1080_new(isp,isp_addr,isp_size,IMX219_SENSOR);         

    video_in_imx219_normal_10bit_new(isp,isp_addr,isp_size);
    
    mipi_csi_2lane_raw10_init(isp);
    return;
}
/**
 * @brief 
 * 
 * @param debug_en 
 * @param pipe 
 */
void debug(unsigned int debug_en,ISP_PIPE_MODE_E pipe)
{
    int jj =0;
    int i = 0;
    //RXDPHY
    unsigned int csi_data;
    if(debug_en == 1)
    {
        printf("RXDPHY:\n");
        while(jj<0x20)
        {
           csi_data = RegRd32(0x92600000+jj);//*(volatile unsigned int *)(VIDEO_RXDPHY_BASE+jj);
           printf("dphy_addr 0x%x = 0x%x\n",0x92600000 +jj,csi_data);
           jj=jj+4;
        }
        //CSI0
        printf("CSI0:\n");
        jj=0;
        while(jj<0x3f8)
        {
            csi_data = RegRd32(0x92620000 +jj);//*(volatile unsigned int *)(VI_BASE_ADDR +jj);
            printf("csi_addr 0x%x = 0x%x\n",0x92620000 +jj,csi_data);
            jj=jj+4;
        }

        printf("CSI1:\n");
        jj=0;
        while(jj<0x3f8)
        {
            csi_data = RegRd32(0x92620000 +0x800+jj);
            printf("csi1_addr 0x%x = 0x%x\n",0x92620000 +0x800+jj,csi_data);
            jj=jj+4;
        }  
        printf("MIPI CORNER:\n");
        csi_data = RegRd32(0x92680000);
        printf("mipicorner 0x%x = 0x%x\n",0x92680000,csi_data);
        csi_data = RegRd32(0x92680000+4 );
        printf("mipicorner 0x%x = 0x%x\n",0x92680000+4,csi_data);  
        printf("vo: \n");
        for(int i =0;i<0x4A0;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92700000 + i);
        	printf("VO REG:Reg[0x%x]= 0x%x\n", 0x92700000+i, csi_data);
        } 
        for(int i =0;i<0x184;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92700000 + 0x600 + i);
        	printf("VO REMAP REG:Reg[0x%x]= 0x%x\n", 0x92700000+0x600+i,csi_data);
        }
        printf("vi :\n");

        for(int i =0;i<0x80;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0700 + i);
        	printf("VI WRAP REG:Reg[0x%x]= 0x%x\n", 0x92620000 + 0x0700 + i, csi_data);//*(volatile unsigned int *)(VI_WRAP_REG_BASE+i));
        }

        for(int i =0;i<0xA4;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0400 + i);
        	printf("VI PIPE CSI00 REG:Reg[0x%x]= 0x%x\n", 0x92620000 + 0x0400 + i, csi_data);//*(volatile unsigned int *)(VI_PIPE_CSI_0_0_REG_BASE+i));
        }

        for(int i =0;i<0xA4;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0500 + i);
        	printf("VI PIPE CSI01 REG:Reg[0x%x]= 0x%x\n", 0x92620000 + 0x0500 + i, csi_data);//*(volatile unsigned int *)(VI_PIPE_CSI_0_1_REG_BASE+i));
        }

        for(int i =0;i<0xA4;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0500 + i);
        	printf("VI PIPE CSI02 REG:Reg[0x%x]= 0x%x\n", 0x92620000 + 0x0500 + i, csi_data); //*(volatile unsigned int *)(VI_PIPE_CSI_0_2_REG_BASE+i));
        }

        for(int i =0;i<0xA4;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0800 + 0x0400+ i);
        	printf("VI PIPE CSI10 REG:Reg[0x%x]= 0x%x\n", 0x92620000 + 0x0800 + 0x0400+ i, csi_data);//VI_PIPE_CSI_1_0_REG_BASE+i, *(volatile unsigned int *)(VI_PIPE_CSI_1_0_REG_BASE+i));
        }

        for(int i =0;i<0xA4;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92620000 + 0x0600 + i);
        	printf("VI PIPE DVP0 REG:Reg[0x%x]= 0x%x\n",0x92620000 + 0x0600 + i, csi_data); //*(volatile unsigned int *)(VI_PIPE_DVP_0_REG_BASE+i));
        }

        if(pipe == ISP_PIPE_MODE_F2K)
        {
            printf("isp f2k: \n");

            for(int i =0;i<0x3C8;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92650000 + 0x00000000 + i);
            	printf("ISP WRAP REG:Reg[0x%x]= 0x%x\n", 0x92650000 + 0x00000000 + i, csi_data);//*(volatile unsigned int *)(reg_isp_2k_wrap_base+i));
            }

            for(int i =0;i<0x32C;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92650000 + 0x00000400 + i);
            	printf("ISP CORE REG:Reg[0x%x]= 0x%x\n",0x92650000 + 0x00000400 + i, csi_data); //*(volatile unsigned int *)(reg_isp_2k_core_base+i));
            }

            for(int i =0;i<0x368;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92650000 + 0x00003000 + i);
            	printf("ISP DS REG:Reg[0x%x]= 0x%x\n", 0x92650000+0x3000+i, csi_data);
            }

            for(int i =0;i<0x70;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92650000 + 0x00005000 + i);
            	printf("ISP MFBC REG:Reg[0x%x]= 0x%x\n", 0x92650000 + 0x00005000 + i, csi_data);//*(volatile unsigned int *)(reg_isp_2k_mfbc_base+i));
            }
        }
        else if(pipe == ISP_PIPE_MODE_R2K)
        {
            printf("isp f2k: \n");
            
            for(int i =0;i<0x3C8;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92660000 + 0x00000000 + i);
            	printf("ISP WRAP REG:Reg[0x%x]= 0x%x\n", 0x92660000 + 0x00000000 + i, csi_data);//*(volatile unsigned int *)(reg_isp_2k_wrap_base+i));
            }

            for(int i =0;i<0x32C;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92660000 + 0x00000400 + i);
            	printf("ISP CORE REG:Reg[0x%x]= 0x%x\n",0x92660000 + 0x00000400 + i, csi_data); //*(volatile unsigned int *)(reg_isp_2k_core_base+i));
            }

            for(int i =0;i<0x368;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92660000 + 0x00003000 + i);
            	printf("ISP DS REG:Reg[0x%x]= 0x%x\n", 0x92660000+0x3000+i, csi_data);
            }

            for(int i =0;i<0x70;i=i+4)  //0x49c
            {
                csi_data =  RegRd32(0x92660000 + 0x00005000 + i);
            	printf("ISP MFBC REG:Reg[0x%x]= 0x%x\n", 0x92660000 + 0x00005000 + i, csi_data);//*(volatile unsigned int *)(reg_isp_2k_mfbc_base+i));
            }
        }


        printf("bt1120: \n");
        for(int i =0;i<=0x18;i=i+4)  //0x49c
        {
            csi_data =  RegRd32(0x92730000 + i);
        	printf("BT1120 REG:Reg[0x%x]= 0x%x\n", 0x92730000+i, csi_data);
        } 
    }
}
/*
*
*/
int draw_frame(unsigned int draw_en,unsigned int DrawAreaNum,frame_coordinate_info frame_coordinate)
{    
    return Vo_Remap_DrawFrame(&isp,draw_en,0,DrawAreaNum,frame_coordinate);
}
/*
*
*/
int isp_init(DS2_INFO *ds2_info, DS1_INFO *ds1_info, VO_OSD_INFO *vo_osd0_info, VO_OSD_INFO *vo_osd1_info, unsigned int draw_demo_en,unsigned int debug_enable,SENSOR_TYPE sensor_type,LCD_TYPE lcd_type)
{
//#ifdef __LINUX__

//    int manual_get = atoi(argv[1]);
    int i, j;
    FILE *fd, *fd2,*fd3,*fd4;
    ISP_PIPE_MODE_E pipe_mode;
    
    //unsigned int en = 1;
    //unsigned int width = 320;//800;//1080;//320;//1080;//960;;//640;//320;
    //unsigned int height = 240;//600;//720;//180;//240;//720;//480;//240;
    //unsigned int demo_en = 0;//1;
    //unsigned int debug_en = 1;//0;
    //SENSOR_TYPE use_sensor = IMX385_SENSOR;//JFX23S_SENSOR //IMX385_SENSOR     

    unsigned int en = ds2_info->ds2_en;
    unsigned int width = ds2_info->ds2_width;
    unsigned int height = ds2_info->ds2_height;
    unsigned int rgb_type =  ds2_info->ds2_rgb_type;
    unsigned int demo_en = draw_demo_en;  
    unsigned int debug_en = debug_enable; 
    unsigned int use_sensor = sensor_type;
    unsigned int vo_osd1_en = vo_osd1_info->osd_en;
    unsigned int vo_osd1_width = vo_osd1_info->osd_width;
    unsigned int vo_osd1_height = vo_osd1_info->osd_height; 
    OSD_INFO *osd1_info = &vo_osd1_info->osd_ctl;
    ISP_SIZE_S isp_size;
    if(JFX23S_SENSOR == use_sensor)
    {
        isp_size.total_size.Width = 2560;
        isp_size.total_size.Height = 1125;
        isp_size.in_size.Width = 1928;
        isp_size.in_size.Height = 1088;
    }
    else if(IMX385_SENSOR == use_sensor)
    {
        isp_size.total_size.Width = 2200;
        isp_size.total_size.Height = 1125;
        isp_size.in_size.Width = 1920;
        isp_size.in_size.Height = 1080;
    }
    else if(IMX219_SENSOR == use_sensor)
    {
        isp_size.total_size.Width = 3476;//3448;
        isp_size.total_size.Height = 1166;
        isp_size.in_size.Width = 1920;
        isp_size.in_size.Height = 1080;
    }

    isp_size.out_size.Width = 1920;
    isp_size.out_size.Height = 1080;
    isp_size.ds0_size.Width = 1080;//1080;
    isp_size.ds0_size.Height = 720;
    isp_size.ds1_size.Width = ds1_info->ds1_width;
    isp_size.ds1_size.Height = ds1_info->ds1_height;
    
    isp_size.ds2_size.Width = width;
    isp_size.ds2_size.Height = height;

    //
    int ret=0;
    unsigned char buff[200];
    //struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM];
    //int *virtual_addr[MEMORY_TEST_BLOCK_NUM];
    //int *ds_virtual_addr[MEMORY_TEST_BLOCK_NUM];

    /*********************memory********************/
    fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR);
    if(fd_share_memory < 0) {
        printf("open %s error!\r\n",SHARE_MEMORY_DEV);
        return -1;
    }
    //
    fd_mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (fd_mem_map < 0) {
        printf("CMEM: failed to open /dev/mem!");
        return -1;
    }
    /* 如果需要mmap映射,需要4K的整数倍 */
    //3dnr
    ISP_ADDR_INFO isp_addr;
    isp_addr.d3nr_en = 0;
    if(1 == isp_addr.d3nr_en)
    {
        allocAlignMem[0].size      = MEMORY_TEST_BLOCK_SIZE * 1536 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[0].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[0].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[0]) < 0) {
            printf("d3nr share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("d3nr block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[0].phyAddr,allocAlignMem[0].size,allocAlignMem[0].alignment);
        }

        isp_addr.d3nr_addr = allocAlignMem[0].phyAddr;
        isp_addr.d3nr_y_stride = 2048*3/2;//(isp_size.in_size.Width*3/2 +15)/16*16;   
        isp_addr.d3nr_uv_stride = 2048;//(isp_size.in_size.Width +15)/16*16;
        printf("d3nr_addr =0x%x,d3nr_y_stride = 0x%x,d3nr_uv_stride = 0x%x\n",isp_addr.d3nr_addr,isp_addr.d3nr_y_stride,isp_addr.d3nr_uv_stride);
    }
    //ldc
    isp_addr.ldc_en = 0;
    if(1 == isp_addr.ldc_en)
    {
        allocAlignMem[1].size      = MEMORY_TEST_BLOCK_SIZE * 2048 ;//MEMORY_TEST_BLOCK_SIZE; 0x400000*2
        allocAlignMem[1].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[1].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[1]) < 0) {
            printf("ldc share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ldc block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[1].phyAddr,allocAlignMem[1].size,allocAlignMem[1].alignment);
        }
        isp_addr.ldc_addr = allocAlignMem[1].phyAddr;//isp_size.in_size.Width * isp_size.in_size.Height *20/8;
        isp_addr.ldc_stride = (isp_size.out_size.Width +15)/16*16;
        printf("ldc_addr =0x%x,ldc_stride = 0x%x\n",isp_addr.ldc_addr,isp_addr.ldc_stride);
    }
    //main
    isp_addr.main_en = 0;//0;
    if(1 == isp_addr.main_en)
    {
        allocAlignMem[2].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[2].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[2].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[2]) < 0) {
            printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[2].phyAddr,allocAlignMem[2].size,allocAlignMem[2].alignment);
        }

        isp_addr.main_out_addr = allocAlignMem[2].phyAddr;//1920*1080*3/2;
        isp_addr.main_stride = (isp_size.out_size.Width +15)/16*16;
        printf("main_out_addr =0x%x,main_stride = 0x%x\n",isp_addr.main_out_addr,isp_addr.main_stride);
    }
    //ds0
    isp_addr.ds0_en = 1;    
    if(1 == isp_addr.ds0_en)
    {
        allocAlignMem[3].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 10;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[3].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[3].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[3]) < 0) {
            printf("ds0 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ds0 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[3].phyAddr,allocAlignMem[3].size,allocAlignMem[3].alignment);
        }

        isp_addr.ds0_out_addr = allocAlignMem[3].phyAddr;//isp_addr.main_out_addr + isp_addr.main_stride * isp_size.out_size.Height *3/2;//1920*1080*3/2;
        isp_addr.ds0_stride = (isp_size.ds0_size.Width +15)/16*16;
        printf("ds0_out_addr =0x%x,ds0_stride = 0x%x\n",isp_addr.ds0_out_addr,isp_addr.ds0_stride);

        virtual_addr[0] = mmap(NULL, allocAlignMem[3].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map, allocAlignMem[3].phyAddr);
        if(virtual_addr[0] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return -1;
        }

        ispOutputForDisplay.size = isp_addr.ds0_stride  * isp_size.ds0_size.Height * 3/2;
        ispOutputForDisplay.paddr = allocAlignMem[3].phyAddr;
        ispOutputForDisplay.vaddr = virtual_addr[0];


        allocAlignMem[10].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 10;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[10].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[10].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[10]) < 0) {
            printf("twod share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("twod block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[10].phyAddr,allocAlignMem[10].size,allocAlignMem[10].alignment);
        }        

    }
    //ds1
    
#if 0
    isp_addr.ds1_en = ds1_info->ds1_en;
    if( 1 == isp_addr.ds1_en)
    {
        allocAlignMem[4].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[4].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[4].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[4]) < 0) {
            printf("ds1 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ds1 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[4].phyAddr,allocAlignMem[4].size,allocAlignMem[4].alignment);
        }
        
        isp_addr.ds1_out_addr = allocAlignMem[4].phyAddr;//isp_addr.ds0_out_addr + isp_addr.ds0_stride * isp_size.ds0_size.Height *3/2;//1920*1080*3/2;
        isp_addr.ds1_stride = (isp_size.ds1_size.Width +15)/16*16;
        printf("ds1_out_addr =0x%x,ds0_stride = 0x%x\n",isp_addr.ds1_out_addr,isp_addr.ds1_stride);

    }
#else

    isp_addr.ds1_en = ds1_info->ds1_en;
    if( 1 == isp_addr.ds1_en)
    {
        
        isp_addr.ds1_out_addr = ds1_info->y_addr;
        isp_addr.ds1_stride = ds1_info->stride;

       
    }
#endif
    //ds2
    isp_addr.ds2_en = en;//1;
    isp_addr.ds2_rgb_type = rgb_type;

#if 0
    if(1 == isp_addr.ds2_en)
    {
        allocAlignMem[5].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[5].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[5].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[5]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[5].phyAddr,allocAlignMem[5].size,allocAlignMem[5].alignment);
        }

        isp_addr.ds2_out_r_addr = allocAlignMem[5].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;

        isp_addr.ds2_rgb_stride = (isp_size.ds2_size.Width +15)/16*16;
        printf("ds2_out_addr =0x%x,ds2_stride = 0x%x\n",isp_addr.ds2_out_r_addr,isp_addr.ds2_rgb_stride);

        ds_virtual_addr[0] = mmap(NULL,allocAlignMem[5].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[5].phyAddr);
        if(ds_virtual_addr[0] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return -1;
        }
        ispOutputForGnne.size = isp_addr.ds2_rgb_stride * isp_size.ds2_size.Height * 4;
        ispOutputForGnne.paddr = allocAlignMem[5].phyAddr;
        ispOutputForGnne.vaddr = ds_virtual_addr[0];
    }
#else
    if(1 == isp_addr.ds2_en)
    {

        isp_addr.ds2_rgb_stride = (isp_size.ds2_size.Width +15)/16*16;       
        isp_addr.ds2_out_r_addr = ds2_info->r_addr;
        isp_addr.ds2_out_g_addr = ds2_info->g_addr;
        isp_addr.ds2_out_b_addr = ds2_info->b_addr;

    }

#endif
    //vi tpg
    isp_addr.vi_tpg_en = 0;//1;//0;
    if(1 == isp_addr.vi_tpg_en)
    {
        allocAlignMem[6].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[6].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[6].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[6]) < 0) {
            printf("vi_tpg share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("vi_tpg block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[6].phyAddr,allocAlignMem[6].size,allocAlignMem[6].alignment);
        }
        isp_addr.vi_tpg_baseaddr = allocAlignMem[6].phyAddr;
        isp_addr.vi_tpg_stride = (isp_size.in_size.Width*3/2+15)/16*16;        
    }
    if(1 == vo_osd0_info->osd_en)
    {
        allocAlignMem[9].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[9].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[9].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[9]) < 0) {
            printf("OSD0 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("OSD0 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[9].phyAddr,allocAlignMem[9].size,allocAlignMem[9].alignment);
        }

        OSD0layer4DisplayText.vaddr = mmap(NULL,allocAlignMem[9].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[9].phyAddr);
        if(OSD0layer4DisplayText.vaddr == MAP_FAILED) {
           printf("share memory OSD0 error!\r\n");
           return -1;
        }
        OSD0layer4DisplayText.paddr = allocAlignMem[9].phyAddr;
        OSD0layer4DisplayText.size = vo_osd0_info->osd_width * vo_osd0_info->osd_height * 4;
    }
 
    unsigned int read_picture_en = 0;
    if(1 == read_picture_en)
    {
        /****************memory 1 for yuv picture**********/
        allocAlignMem[7].size      = MEMORY_TEST_BLOCK_SIZE *  1024;            // 1k * 4k = 16
        allocAlignMem[7].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[7].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[7]) < 0) {
            printf("share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[7].phyAddr,allocAlignMem[7].size,allocAlignMem[7].alignment);
        }

        picture_addr = allocAlignMem[7].phyAddr;

        virtual_addr[1] = mmap(NULL, allocAlignMem[7].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map, allocAlignMem[7].phyAddr);
        if(virtual_addr[1] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return -1;
        }

        for(j = 0; j < allocAlignMem[1].size/4; j ++) {
            virtual_addr[1][j] = j;
        }

        for(j = 0; j < allocAlignMem[1].size/4; j ++) {
            if(virtual_addr[1][j] != j) {
                printf("memory compare error!\r\n");
                return -1;
            }
        }


        fd = fopen(IMAGE_NAME1, "rb");    //IMAGE_NAME   IMAGE_NAME1
        if(fd == NULL)
        {
            printf("open %s failure, errno %d\n", IMAGE_NAME, errno);
            return -1;
        }
        printf("open success \n");

        ret = fread(virtual_addr[1], 3110400, 1, fd);    // 3110400 = 1080 * 1920 * 1.5
        if(ret <= 0)
        {
            printf("read  picture_addr is failed ret is %d \n", ret);
            return -1;
        }

        printf("read  picture_addr is success \n");
    }
  
   //vo osd1
    isp_addr.vo_osd1_en = vo_osd1_en;
    if(1 == isp_addr.vo_osd1_en)
    {
        allocAlignMem[8].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[8].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[8].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[8]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return -1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[8].phyAddr,allocAlignMem[8].size,allocAlignMem[8].alignment);
        }

        isp_addr.vo_osd1_addr = allocAlignMem[8].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;
        isp_addr.vo_osd1_stride = (vo_osd1_width +15)/16*16;
        printf("ds2_out_addr =0x%x,ds2_stride = 0x%x\n",isp_addr.vo_osd1_addr,isp_addr.vo_osd1_stride);

        vo_osd_virtual_addr[0] = mmap(NULL,allocAlignMem[8].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[8].phyAddr);
        if(vo_osd_virtual_addr[0] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return -1;
        }
        OSD1layer5DisplayGnne.size = isp_addr.vo_osd1_stride * vo_osd1_height * 4;
        OSD1layer5DisplayGnne.paddr = allocAlignMem[8].phyAddr;
        OSD1layer5DisplayGnne.vaddr = vo_osd_virtual_addr[0];
    }

    /*open device node*/
    printf("Open isp!!\n");
    fd_isp = open(DEV_NAME, O_RDWR | O_CLOEXEC);
    if (fd_isp < 0)
    {
        printf("Open %s Error!\n", DEV_NAME);
        return -1;
    }
    else
        printf("Open %S ok! fd_isp 0x%x\n", DEV_NAME, fd_isp);
    //
#if 0
    printf("Open i2c0!!\n");
    fd_i2c0 = open(DEV_NAME_I2C0, O_RDWR);
    
    if (fd_i2c0 < 0)
    {
        printf("Open %s Error!\n", DEV_NAME_I2C0);
        return fd_isp;
    }
    else
        printf("Open %s ok!\n", DEV_NAME_I2C0);
        

    unsigned char *mapI2C = mmap(NULL, 0x20000, PROT_READ|PROT_WRITE, MAP_SHARED, fd_i2c0, 0);
    if(mapI2C == NULL)
    {
        printf("i2c mmap failed\n");
        return fd_isp;
    }
    i2c[0] = (i2c_t *)mapI2C;
    i2c[1] = (i2c_t *)(mapI2C + 0x10000);

    if (ioctl(fd_i2c0, I2C0_CMD_TEST, 4) < 0)
    {
        printf("Call cmd ISP_CMD_WRITE_REG fail, reg %u\n", reg_isp.id);
        return fd_isp;
    }
    
    printf("i2c0 reg tar = 0x%x\n", i2c[0]->tar);
    printf("i2c1 reg tar = 0x%x\n", i2c[1]->tar);
    i2c[0]->tar = 0x12;
    i2c[1]->tar = 0x23;
    printf("test i2c0 reg tar = 0x%x\n", i2c[0]->tar);
    printf("test i2c1 reg tar = 0x%x\n", i2c[1]->tar); 
#endif
    //
    int enable_wdr = 0;
    int enable_3dnr = 0;
    unsigned int int_enable = 1;

    isp.mmio_base[ISP_IOMEM_CSI0_HOST] = CSI_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_CSI1_HOST] = CSI1_HOST_BASE;
	isp.mmio_base[ISP_IOMEM_MIPI_DPHY] = MIPI_DPHY_BASE;
    isp.mmio_base[ISP_IOMEM_MIPI_CORNER] = MIPI_CORNER_BASE;
	isp.mmio_base[ISP_IOMEM_VI_WRAP] = VI_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI00] = VI_PIPE_CSI_0_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI01] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI02] = VI_PIPE_CSI_0_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI10] = VI_PIPE_CSI_1_0_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI11] = VI_PIPE_CSI_1_1_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_CSI12] = VI_PIPE_CSI_1_2_REG_BASE;
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP0] = VI_PIPE_DVP_0_REG_BASE;	
	isp.mmio_base[ISP_IOMEM_VI_PIPE_DVP1] = VI_PIPE_DVP_1_REG_BASE;		
	isp.mmio_base[ISP_IOMEM_F2K_WRAP] = ISP_F_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE] = ISP_F_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_CORE_TABLE] = ISP_F_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBC] = ISP_F_2K_FBC_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_FBD] = ISP_F_2K_FBD_BASE;
	isp.mmio_base[ISP_IOMEM_F2K_DS] = ISP_F_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT0_REMAP] = ISP_F_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_OUT1_REMAP] = ISP_F_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_F2K_MAIN_REMAP] = ISP_F_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_WRAP] = ISP_R_2K_WRAP_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE] = ISP_R_2K_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_CORE_TABLE] = ISP_R_2K_CORE_TABLE_BASE;
	isp.mmio_base[ISP_IOMEM_R2K_DS] = ISP_R_2K_DS_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT0_REMAP] = ISP_R_2K_OUT0_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_OUT1_REMAP] = ISP_R_2K_OUT1_REMAP_BASE;
    isp.mmio_base[ISP_IOMEM_R2K_MAIN_REMAP] = ISP_R_2K_MAIN_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_WRAP] = TOF_WRAP_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_CORE] = TOF_CORE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_TOF_TABLE] = TOF_TABLE_REG_BASE;
	isp.mmio_base[ISP_IOMEM_FBC_WRAP] = FBC_WRAP_BASE;
    isp.mmio_base[ISP_IOMEM_FBC_CORE] = FBC_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_CORE] = VO_CORE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_REMAP] = VO_REMAP_BASE;
	isp.mmio_base[ISP_IOMEM_VO_HSCALE] = VO_HSCALE_BASE;
	isp.mmio_base[ISP_IOMEM_VO_VSCALE] = VO_VSCALE_BASE;
    isp.mmio_base[ISP_IOMEM_VO_GAMMA] = VO_GAMMA_BASE; 
    isp.mmio_base[ISP_IOMEM_BT1120] = BT1120_BASE_ADDR; 
    printf("struct isp_device addr = 0x%x,vi = 0x%x,mmio_base = 0x%x\n",&isp,&isp.isp_vi,isp.mmio_base[ISP_IOMEM_VI_WRAP]);
    
 //   open_camera_power();

    if( 1 == isp_addr.ds1_en)
    {
        int ds1_buf_cout = 20;
        // set ds 1
        if (ioctl(fd_isp, ISP_CMD_DS1_ADDR, isp_addr.ds1_out_addr) < 0)
        {
            printf("Call cmd ISP_CMD_DS1_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_ADDR succss \n");

        if (ioctl(fd_isp, ISP_CMD_DS1_BUFF_COUNT, ds1_buf_cout) < 0)
        {
            printf("Call cmd ISP_CMD_DS1_BUFF_COUNT fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_BUFF_COUNT succss \n");
       if (ioctl(fd_isp, ISP_CMD_SET_DS1_SIZE, 640 * 480) < 0)
        {
            printf("Call cmd ISP_CMD_SET_DS1_SIZE fail\n");
        }   
        printf("Call cmd ISP_CMD_SET_DS1_SIZE succss \n");
    }

    if(1 == isp_addr.ds0_en)
    {
        if (ioctl(fd_isp, ISP_CMD_DS0_SRC_ADDR, allocAlignMem[3].phyAddr) < 0)
        {
            printf("Call cmd ISP_CMD_DS0_SRC_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS0_SRC_ADDR succss \n");

        if (ioctl(fd_isp, ISP_CMD_DS1_DES_ADDR, allocAlignMem[10].phyAddr) < 0)
        {
            printf("Call cmd ISP_CMD_DS1_DES_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_DES_ADDR succss \n");
    }

 //   pthread_create(&pthreads, NULL, h264_test, fd_isp);

    //if (ioctl(fd_isp, ISP_CMD_SET_DS2BUF, &isp_addr.ds2_out_addr[0]) < 0)
    //{
    //    printf("Call cmd ISP_CMD_SET_DS2BUF fail, ds2_out_addr 0x%x\n",isp_addr.ds2_out_addr);
    //    return -1;
    //}
    //
    //mipi dsi
    if(lcd_type == AML550_LCD)
    {
//        aml550_power_on_seq();
//        aml550_22v_power_en();
        
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
        }
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
//        sleep(1);
        
    }
    else if(lcd_type == ITI7807_LCD)
    {
//        aml550_power_on_seq();
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_ILI7807_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_ILI7807_INIT fail\n");
        }   
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
 //       sleep(1);
 //       aml550_22v_power_en();  
    }
    else if(lcd_type == BT1120_DISPLAY)
    {
        struct bt1120_cfg_info bt1120_info;
        bt1120_info.bt1120_en = 1;
        bt1120_info.bt_in_sel = SEL_VO;
        bt1120_info.img_vsize_total = 1125;
        bt1120_info.img_hsize_total = 2200;
        bt1120_info.img_vsize = 1080;
        bt1120_info.img_hsize = 1920;        
        bt1120_Init_cfg(&isp,&bt1120_info);
    }
    else if(lcd_type == HX8399)
    {
  //      aml550_power_on_seq();
        if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_HX8399_INIT, 0) < 0)
        {
            printf("Call cmd ISP_CMD_MIPI_DSI_HX8399_INIT fail\n");
        }   
   //     printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
   //     sleep(1);
   //     aml550_22v_power_en();  
    }

    if(IMX385_SENSOR == use_sensor) 
    {
        /*reset whole video system start*/
        pipe_mode = ISP_PIPE_MODE_F2K;
        fpga_system_init(0);

        /*********open camera power******************/

#if 0
    if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
    {
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
    }
    printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
#endif
        /*reset whole video system end*/
        imx385_i2c_init(MIPI_CSI0_I2C);
        imx385_1920x1080_normal_vi_isp_config(&isp,&isp_addr,&isp_size);

        if(enable_wdr)
            imx385_2k_wdr_sensor_config();
        else
        {
            imx385_sensor_config();
        }
        //Imx385_init();
        //sleep(1);
		 msleep(50);
        isp_f2k_core_table_init(&isp);
		 msleep(50);
       // sleep(1);

    }
    /*sensor imx385 config end*/
    else if(JFX23S_SENSOR == use_sensor)
    {
        pipe_mode = ISP_PIPE_MODE_F2K;
		jfx23s_i2c_init(DVP_I2C);
 //       hmdi_init_dvp();
        //InitIsp2KWrap_TestJXF23S(&isp_addr,&isp_size,int_enable);
        InitIsp_f2k_1920x1080_new(&isp,&isp_addr,&isp_size,JFX23S_SENSOR);
        //video_in_jxf23s_rgbir_10bit_30fps();
        video_in_jxf23s_rgbir_10bit_30fps_new(&isp,&isp_addr,&isp_size);

		jxf23s_sensor_config();
        //jxs23s_sensor_15fps_config();
         msleep(50);
        isp_f2k_core_table_init(&isp);
         msleep(50);       
    }
    else if(IMX219_SENSOR == use_sensor) 
    {
        /*reset whole video system start*/
        pipe_mode = ISP_PIPE_MODE_F2K;
        fpga_system_init(0);

        /*********open camera power******************/

#if 0
    if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
    {
        printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
    }
    printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
#endif
        /*reset whole video system end*/
        imx219_i2c_init(MIPI_CSI0_I2C);
        imx219_1920x1080_normal_vi_isp_config(&isp,&isp_addr,&isp_size);

        imx219_sensor_config();
        //Imx385_init();
        //sleep(1);
		 msleep(50);
        isp_f2k_core_table_init(&isp);
		 msleep(50);
       // sleep(1);

    }   

    if(1 == debug_en)
    {
        fd2 = fopen(IMAGE_NAME2, "wb");    //IMAGE_NAME   IMAGE_NAME1
        if(fd2 == NULL)
        {
            printf("open %s failure, errno %d\n", IMAGE_NAME8, errno);
            return fd_isp;
        }
        printf("open %s success \n",IMAGE_NAME2);
    
        ret = fwrite(virtual_addr[0], isp_addr.ds0_stride * isp_size.ds0_size.Height*3/2, 1, fd2);    // 3110400 = 1080 * 1920 * 1.5
        if(ret <= 0)
        {
            printf("fwrite  picture_addr is failed ret is %d \n", ret);
            return fd_isp;
        }

#if 0
        if (ioctl(fd_isp, ISP_CMD_TWOD_TEST_ADDR, 0) < 0)
        {
            printf("Call cmd ISP_CMD_TWOD_TEST_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_TWOD_TEST_ADDR succss \n");



        fd_2d = open(KENDRTY_2D,O_RDWR);
        if(fd_2d < 0) {
            printf("open %s error!\r\n",KENDRTY_2D);
            return fd_isp;
        }
#endif
#if 0
        // set input addr zero
        if(ioctl(fd_2d, KENDRTY_2DROTATION_INPUT_ADDR, allocAlignMem[3].phyAddr) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_INPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // set output addr
        if(ioctl(fd_2d, KENDRTY_2DROTATION_OUTPUT_ADDR, allocAlignMem[10].phyAddr) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_OUTPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // start 
        if(ioctl(fd_2d, KENDRTY_2DROTATION_90, 0) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_90 error!\r\n");
            return fd_isp;
        }
#endif
#if 0
        // one
        if(ioctl(fd_2d, KENDRTY_2DROTATION_INPUT_ADDR, allocAlignMem[3].phyAddr + (1080 * 1920 * 3 / 2)) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_INPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // set output addr
        if(ioctl(fd_2d, KENDRTY_2DROTATION_OUTPUT_ADDR, allocAlignMem[10].phyAddr + (1080 * 1920 * 3 / 2) ) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_OUTPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // start 
        if(ioctl(fd_2d, KENDRTY_2DROTATION_90, 0) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_90 error!\r\n");
            return fd_isp;
        }
#endif

#if 0
        //two
        if(ioctl(fd_2d, KENDRTY_2DROTATION_INPUT_ADDR, allocAlignMem[3].phyAddr + ((1080 * 1920 * 3 / 2) * 2)) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_INPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // set output addr
        if(ioctl(fd_2d, KENDRTY_2DROTATION_OUTPUT_ADDR, allocAlignMem[10].phyAddr + ((1080 * 1920 * 3 / 2) * 2) ) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_OUTPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // start 
        if(ioctl(fd_2d, KENDRTY_2DROTATION_90, 0) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_90 error!\r\n");
            return fd_isp;
        }
#endif

#if 0
        //three
        if(ioctl(fd_2d, KENDRTY_2DROTATION_INPUT_ADDR, allocAlignMem[3].phyAddr + ((1080 * 1920 * 3 / 2) * 3) ) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_INPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // set output addr
        if(ioctl(fd_2d, KENDRTY_2DROTATION_OUTPUT_ADDR, allocAlignMem[10].phyAddr + ((1080 * 1920 * 3 / 2) * 3) ) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_OUTPUT_ADDR error!\r\n");
            return fd_isp;
        }

        // start 
        if(ioctl(fd_2d, KENDRTY_2DROTATION_90, 0) < 0) {
            printf("input share memory  KENDRTY_2DROTATION_90 error!\r\n");
            return fd_isp;
        }
#endif

#if 0 
        printf("fwrite  picture_addr is success ret is %d  allocAlignMem[3].phyAddr is %x \n", ret,  allocAlignMem[3].phyAddr);
   
        fd3 = fopen(IMAGE_NAME3, "wb");    //IMAGE_NAME   IMAGE_NAME1
        if(fd3 == NULL)
        {
            printf("open %s failure, errno %d\n", IMAGE_NAME3, errno);
            return fd_isp;
        }
        printf("open %s success \n",IMAGE_NAME3);
    
        ret = fwrite(ds_virtual_addr[0], isp_addr.ds2_rgb_stride * isp_size.ds2_size.Height*4, 1, fd3);    // 3110400 = 1080 * 1920 * 1.5
        if(ret <= 0)
        {
            printf("fwrite  picture_addr is failed ret is %d \n", ret);
            return fd_isp;
        }
        fclose(fd3);
#endif
    }


    //
   // aml550_power_on_seq();
   // //mipi dsi
   // if (ioctl(fd_isp, ISP_CMD_MIPI_DSI_INIT, 0) < 0)
   // {
   //     printf("Call cmd ISP_CMD_MIPI_DSI_INIT fail\n");
   // }
   // printf("Call cmd ISP_CMD_MIPI_DSI_INIT succss \n");
   // sleep(1);
   // aml550_22v_power_en();
    VO_SIZE_S  vo_size;
    //layer0
    vo_size.layer0_size.Width = 1280;//isp_size.out_size.Width;
    vo_size.layer0_size.Height = 720;//isp_size.out_size.Height;
    vo_size.layer0_out_size.Width = 1280;
    vo_size.layer0_out_size.Height = 720;
    //layer1
    vo_size.layer1_size.Width = isp_size.ds0_size.Width;
    vo_size.layer1_size.Height = isp_size.ds0_size.Height;
    //layer2  
    vo_size.layer2_size.Width = isp_size.ds1_size.Width;
    vo_size.layer2_size.Height = isp_size.ds1_size.Height;
    //layer3
    vo_size.layer3_size.Width = isp_size.ds1_size.Width;
    vo_size.layer3_size.Height = isp_size.ds1_size.Height;
    //osd0
    vo_size.osd0_size.Width = vo_osd0_info->osd_width;
    vo_size.osd0_size.Height = vo_osd0_info->osd_height;
    //osd1
    vo_size.osd1_size.Width = vo_osd1_width;
    vo_size.osd1_size.Height = vo_osd1_height;
    //osd2 
    vo_size.osd2_size.Width = isp_size.out_size.Width;
    vo_size.osd2_size.Height = isp_size.out_size.Height;
    VO_ADDR_INFO vo_addr;
    //layer0
    vo_addr.layer0_en = isp_addr.main_en;//1;
    vo_addr.layer0_baseaddr = isp_addr.main_out_addr;
    vo_addr.layer0_stride = isp_addr.main_stride;
    //layer1
    vo_addr.layer1_en = isp_addr.ds0_en;//0;         
    vo_addr.layer1_baseaddr = isp_addr.ds0_out_addr;//isp_addr.ds1_out_addr;//isp_addr.ds0_out_addr;  // change ds1  output 
    vo_addr.layer1_stride = isp_addr.ds0_stride;//isp_addr.ds1_stride;//isp_addr.ds0_stride;
    //layer2 
    vo_addr.layer2_en = isp_addr.ds1_en;//0;
    vo_addr.layer2_baseaddr = isp_addr.ds1_out_addr;
    vo_addr.layer2_stride = isp_addr.ds1_stride; 
    //layer3
    vo_addr.layer3_en = isp_addr.ds1_en;//0;
    vo_addr.layer3_baseaddr = isp_addr.ds1_out_addr;
    vo_addr.layer3_stride = isp_addr.ds1_stride;
    //osd0
    vo_addr.osd0_en = vo_osd0_info->osd_en;//0;//1;
    vo_addr.osd0_baseaddr = OSD0layer4DisplayText.paddr;
    vo_addr.osd0_stride = vo_size.osd0_size.Width;
    vo_addr.osd0_rgb_type = DS2_ARGB;
    //osd1
    vo_addr.osd1_en = isp_addr.vo_osd1_en;
    vo_addr.osd1_baseaddr = isp_addr.vo_osd1_addr;
    vo_addr.osd1_stride = isp_addr.vo_osd1_stride;
    //osd2 
    vo_addr.osd2_en = 0;
    vo_addr.osd2_baseaddr = isp_addr.ds2_out_r_addr;
    vo_addr.osd2_stride = isp_addr.ds2_rgb_stride;
    //
    if(lcd_type == BT1120_DISPLAY)
    {
        //InitDisplay_layer01080p_1080x720_hdmi(&vo_addr,&vo_size,osd1_info);
        //InitDisplay_720p50fps();
        Vo_VideoOut_Hdmi(&isp,&vo_addr,&vo_size,osd1_info);
        msleep(1000);
        cv8788Init();
    }
    else
    {
        //InitDisplay_layer01080p_1080x720(&vo_addr,&vo_size,osd1_info);
        Vo_VideoOut_Dsi(&isp,&vo_addr,&vo_size,osd1_info);
    }  

    //InitDisplay_layer01080p();
//    InitDisplay_720p50fps();
    //InitDisplay_720p50fps();     
   
     //while(1)
    if(demo_en == 1)
    {
        frame_coordinate_info frame_coordinate;
        frame_coordinate.startx = 100;//289;
        frame_coordinate.starty = 100;//200;
        frame_coordinate.endx = 400;//400;
        frame_coordinate.endy = 400;//400;
        draw_frame(1,0,frame_coordinate);
    }

    //writel(0,0x92650010);     //f2k
    debug(debug_en,pipe_mode);

    if( 1 == isp_addr.vo_osd1_en)
    {
        if(OSD_RGB_32BIT == osd1_info->osd1_type)
        {
            if(OSD_RGB_REV_B == osd1_info->osd1_rgb_rev)
            {
                fd4 = fopen(IMAGE_NAME4, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME4, errno);
                    return fd_isp;
                }
                printf("open %s success \n",IMAGE_NAME4);
            }
            else
            {
                fd4 = fopen(IMAGE_NAME5, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME5, errno);
                    return fd_isp;
                }
                printf("open %s success \n",IMAGE_NAME5);
            }  

            ret = fread(vo_osd_virtual_addr[0], isp_addr.vo_osd1_stride*vo_osd1_height*4, 1, fd4);    // 3110400 = 1080 * 1920 * 1.5
            if(ret <= 0)
            {
                printf("read  osd_pic is failed ret is %d \n", ret);
                return fd_isp;
            }

            printf("read  osd_pic is success \n");
        }

        if(OSD_RGB_24BIT == osd1_info->osd1_type)
        {
            if(OSD_RGB_REV_B == osd1_info->osd1_rgb_rev)
            {
                fd4 = fopen(IMAGE_NAME6, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME6, errno);
                    return fd_isp;
                }
                printf("open %s success \n",IMAGE_NAME6);
            }
            else
            {
                fd4 = fopen(IMAGE_NAME7, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME7, errno);
                    return fd_isp;
                }
                printf("open %s success \n",IMAGE_NAME7);
            }  

            ret = fread(vo_osd_virtual_addr[0], isp_addr.vo_osd1_stride*vo_osd1_height*3, 1, fd4);    // 3110400 = 1080 * 1920 * 1.5
            if(ret <= 0)
            {
                printf("read  osd_pic is failed ret is %d \n", ret);
                return fd_isp;
            }
    
            printf("read  osd_pic is success \n");
        }
    }

    return fd_isp;
}


void isp_exit(void)
{
    uint32_t i = 0;

    for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
        if(vo_osd_virtual_addr[i])
            munmap(vo_osd_virtual_addr[i],allocAlignMem[i].size);
    }

    for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
        if(virtual_addr[i])
            munmap(virtual_addr[i],allocAlignMem[i].size);
    }

    for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
        if(ds_virtual_addr[i])
            munmap(ds_virtual_addr[i],allocAlignMem[i].size);
    }

    printf("munmap success \n");


    for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
        if(allocAlignMem[i].phyAddr != 0)
        {
            if(ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[i].phyAddr) < 0) {
                printf("share memory  SHARE_MEMORY_FREE error!\r\n");
            }
        }
    }


}

