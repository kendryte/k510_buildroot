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
  File Name     : imx385.c
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
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h> 
#include <assert.h>

#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/i2c-dev.h>

#include <linux/i2c.h>

#include "sensor/sensor.h"
#include "i2c/i2c_com.h"
#include "exctl_dev/dev_hw.h"
#include "isp_com.h"

#define I2C_DEVICE_NAME0                "/dev/i2c-0" 
#define JFX23S_CHIP_ADDR                (0x8c>>1)

static int i2c_fd = 0;
/**
 * @brief 
 * 
 */
void jfx23s_i2c_init(enum _SENSOR_I2C i2c_num)
{
    if( DVP_I2C == i2c_num)
    {
	    i2c_fd = open(I2C_DEVICE_NAME0, O_RDWR);
        if(i2c_fd < 0)
        {
             printf("open %s faild \n", I2C_DEVICE_NAME0); 
        }
    }

    if (ioctl(i2c_fd, I2C_SLAVE_FORCE, JFX23S_CHIP_ADDR) < 0) { 

        printf("oictl:setslave address failed/n");

    }
	//
    i2c_set(i2c_fd, 20, 2);

    msleep(10);
      
    Release_dvp_fpga_rst_n();
//    sleep(1);
    msleep(100);
    Release_dvp_fpga_pwdn();
    msleep(100);
//    sleep(1);
    return;
}
/**
 * @brief 
 * 
 * @param addr 
 * @param reg 
 */
void jxf23s_sensor_write(uint16_t reg_addr,uint8_t reg_val)
{
	unsigned char addr = (reg_addr>>8)&0xff;
	unsigned char val = reg_val;
	i2c_nbytes_write(i2c_fd,JFX23S_CHIP_ADDR,&addr,1,&val,1);
}
/**
 * @brief 
 * 
 * @param reg 
 */
void jxf23s_sensor_read(uint16_t reg_addr)
{
    uint8_t reg_val = 0;
	uint8_t addr = (reg_addr>>8)&0xff;
	i2c_nbytes_read(i2c_fd,JFX23S_CHIP_ADDR,&addr,1,&reg_val,1);
    printf("reg is %x val is %x \n", reg_addr, reg_val);
}
/**
 * @brief 
 * 
 */
void jxf23s_sensor_init(void)
{
	jxf23s_sensor_write(0x1200,0x40);
	msleep(1);
	jxf23s_sensor_write(0x0E00,0x11);
	msleep(1);
	jxf23s_sensor_write(0x0F00,0x14);
	msleep(1);
	jxf23s_sensor_write(0x1000,0x40);
	msleep(1);
	jxf23s_sensor_write(0x1100,0x80);
	msleep(1);
	jxf23s_sensor_write(0x0D00,0x50);
	msleep(1);
	jxf23s_sensor_write(0x5F00,0x42);
	msleep(1);
	jxf23s_sensor_write(0x6000,0x2B);
	msleep(1);
	jxf23s_sensor_write(0x5800,0x12);
	msleep(1);
	jxf23s_sensor_write(0x5700,0x60);
	msleep(1);
	jxf23s_sensor_write(0x9D00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2000,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2100,0x05);
	msleep(1);
	jxf23s_sensor_write(0x2200,0x65);
	msleep(1);
	jxf23s_sensor_write(0x2300,0x04);
	msleep(1);
	jxf23s_sensor_write(0x2400,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x2500,0x38);
	msleep(1);
	jxf23s_sensor_write(0x2600,0x43);
	msleep(1);
	jxf23s_sensor_write(0x2700,0x97);
	msleep(1);
	jxf23s_sensor_write(0x2800,0x19);
	msleep(1);
	jxf23s_sensor_write(0x2900,0x04);
	msleep(1);
	jxf23s_sensor_write(0x2C00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2D00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2E00,0x18);
	msleep(1);
	jxf23s_sensor_write(0x2F00,0x44);
	msleep(1);
	jxf23s_sensor_write(0x4100,0xC8);
	msleep(1);
	jxf23s_sensor_write(0x4200,0x13);
	msleep(1);
	jxf23s_sensor_write(0x4600,0x00);
	msleep(1);
	jxf23s_sensor_write(0x7600,0x60);
	msleep(1);
	jxf23s_sensor_write(0x7700,0x09);
	msleep(1);
	jxf23s_sensor_write(0x1D00,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x1E00,0x1F);
	msleep(1);
	jxf23s_sensor_write(0x6C00,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x2A00,0x88);
	msleep(1);
	jxf23s_sensor_write(0x2B00,0x24);
	msleep(1);
	jxf23s_sensor_write(0x3100,0x08);
	msleep(1);
	jxf23s_sensor_write(0x3200,0x4F);
	msleep(1);
	jxf23s_sensor_write(0x3300,0x20);
	msleep(1);
	jxf23s_sensor_write(0x3400,0x5E);
	msleep(1);
	jxf23s_sensor_write(0x3500,0x5E);
	msleep(1);
	jxf23s_sensor_write(0x3A00,0xAF);
	msleep(1);
	jxf23s_sensor_write(0x5600,0x32);
	msleep(1);
	jxf23s_sensor_write(0x5900,0xBF);
	msleep(1);
	jxf23s_sensor_write(0x5A00,0x04);
	msleep(1);
	jxf23s_sensor_write(0x8500,0x5A);
	msleep(1);
	jxf23s_sensor_write(0x8A00,0x04);
	msleep(1);
	jxf23s_sensor_write(0x8F00,0x90);
	msleep(1);
	jxf23s_sensor_write(0x9100,0x13);
	msleep(1);
	jxf23s_sensor_write(0x5B00,0xA0);
	msleep(1);
	jxf23s_sensor_write(0x5C00,0xF0);
	msleep(1);
	jxf23s_sensor_write(0x5D00,0xF4);
	msleep(1);
	jxf23s_sensor_write(0x5E00,0x1F);
	msleep(1);
	jxf23s_sensor_write(0x6200,0x04);
	msleep(1);
	jxf23s_sensor_write(0x6300,0x0F);
	msleep(1);
	jxf23s_sensor_write(0x6400,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x6600,0x44);
	msleep(1);
	jxf23s_sensor_write(0x6700,0x73);
	msleep(1);
	jxf23s_sensor_write(0x6900,0x7C);
	msleep(1);
	jxf23s_sensor_write(0x6A00,0x2B);
	msleep(1);
	jxf23s_sensor_write(0x7A00,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x4A00,0x05);
	msleep(1);
	jxf23s_sensor_write(0x7E00,0xCD);
	msleep(1);
	jxf23s_sensor_write(0x4900,0x10);
	msleep(1);
	jxf23s_sensor_write(0x5000,0x02);
	msleep(1);
	jxf23s_sensor_write(0x7B00,0x4A);
	msleep(1);
	jxf23s_sensor_write(0x7C00,0x0C);
	msleep(1);
	jxf23s_sensor_write(0x7F00,0x57);
	msleep(1);
	jxf23s_sensor_write(0x9000,0x00);
	msleep(1);
	jxf23s_sensor_write(0x8E00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x8C00,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x8D00,0xC7);
	msleep(1);
	jxf23s_sensor_write(0x8B00,0x01);
	msleep(1);
	jxf23s_sensor_write(0x0C00,0x40);
	msleep(1);
	jxf23s_sensor_write(0x6500,0x02);
	msleep(1);
	jxf23s_sensor_write(0x8000,0x02);
	msleep(1);
	jxf23s_sensor_write(0x8100,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x1900,0x20);
	msleep(1);
	jxf23s_sensor_write(0x1200,0x00);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x85);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x05);
	msleep(3);
}
/*
*
*/
void  jxf23s_sensor_init_15fps(void)
{
	jxf23s_sensor_write(0x1200,0x60);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x85);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x05);
	msleep(1);
	jxf23s_sensor_write(0x0E00,0x11);
	msleep(1);
	jxf23s_sensor_write(0x0F00,0x14);
	msleep(1);
	jxf23s_sensor_write(0x1000,0x24);
	msleep(1);
	jxf23s_sensor_write(0x1100,0x80);
	msleep(1);
	jxf23s_sensor_write(0x0D00,0xF0);
	msleep(1);
	jxf23s_sensor_write(0x5F00,0x41);
	msleep(1);
	jxf23s_sensor_write(0x6000,0x20);
	msleep(1);
	jxf23s_sensor_write(0x5800,0x12);
	msleep(1);
	jxf23s_sensor_write(0x5700,0x60);
	msleep(1);
	jxf23s_sensor_write(0x9D00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2000,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2100,0x05);
	msleep(1);
	jxf23s_sensor_write(0x2200,0x65);
	msleep(1);
	jxf23s_sensor_write(0x2300,0x04);
	msleep(1);
	jxf23s_sensor_write(0x2400,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x2500,0x38);
	msleep(1);
	jxf23s_sensor_write(0x2600,0x43);
	msleep(1);
	jxf23s_sensor_write(0x2700,0x98);
	msleep(1);
	jxf23s_sensor_write(0x2800,0x15);
	msleep(1);
	jxf23s_sensor_write(0x2900,0x04);
	msleep(1);
	jxf23s_sensor_write(0x2A00,0x8A);
	msleep(1);
	jxf23s_sensor_write(0x2B00,0x14);
	msleep(1);
	jxf23s_sensor_write(0x2C00,0x02);
	msleep(1);
	jxf23s_sensor_write(0x2D00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x2E00,0x14);
	msleep(1);
	jxf23s_sensor_write(0x2F00,0x44);
	msleep(1);
	jxf23s_sensor_write(0x4100,0xC5);
	msleep(1);
	jxf23s_sensor_write(0x4200,0x3B);
	msleep(1);
	jxf23s_sensor_write(0x4700,0x42);
	msleep(1);
	jxf23s_sensor_write(0x7600,0x60);
	msleep(1);
	jxf23s_sensor_write(0x7700,0x09);
	msleep(1);
	jxf23s_sensor_write(0x8000,0x41);
	msleep(1);
	jxf23s_sensor_write(0xAF00,0x22);
	msleep(1);
	jxf23s_sensor_write(0xAB00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x4600,0x00);
	msleep(1);
	jxf23s_sensor_write(0x1D00,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x1E00,0x1F);
	msleep(1);
	jxf23s_sensor_write(0x6C00,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x3100,0x08);
	msleep(1);
	jxf23s_sensor_write(0x3200,0x27);
	msleep(1);
	jxf23s_sensor_write(0x3300,0x60);
	msleep(1);
	jxf23s_sensor_write(0x3400,0x5E);
	msleep(1);
	jxf23s_sensor_write(0x3500,0x5E);
	msleep(1);
	jxf23s_sensor_write(0x3A00,0xAF);
	msleep(1);
	jxf23s_sensor_write(0x3B00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x3C00,0x48);
	msleep(1);
	jxf23s_sensor_write(0x3D00,0x5B);
	msleep(1);
	jxf23s_sensor_write(0x3E00,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x3F00,0xA8);
	msleep(1);
	jxf23s_sensor_write(0x4000,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x5600,0xB2);
	msleep(1);
	jxf23s_sensor_write(0x5900,0x9E);
	msleep(1);
	jxf23s_sensor_write(0x5A00,0x04);
	msleep(1);
	jxf23s_sensor_write(0x8500,0x4D);
	msleep(1);
	jxf23s_sensor_write(0x8A00,0x04);
	msleep(1);
	jxf23s_sensor_write(0x9100,0x13);
	msleep(1);
	jxf23s_sensor_write(0x9B00,0x03);
	msleep(1);
	jxf23s_sensor_write(0x9C00,0xE1);
	msleep(1);
	jxf23s_sensor_write(0xA900,0x78);
	msleep(1);
	jxf23s_sensor_write(0x5B00,0xB0);
	msleep(1);
	jxf23s_sensor_write(0x5C00,0x71);
	msleep(1);
	jxf23s_sensor_write(0x5D00,0xF6);
	msleep(1);
	jxf23s_sensor_write(0x5E00,0x14);
	msleep(1);
	jxf23s_sensor_write(0x6200,0x01);
	msleep(1);
	jxf23s_sensor_write(0x6300,0x0F);
	msleep(1);
	jxf23s_sensor_write(0x6400,0xC0);
	msleep(1);
	jxf23s_sensor_write(0x6500,0x02);
	msleep(1);
	jxf23s_sensor_write(0x6700,0x65);
	msleep(1);
	jxf23s_sensor_write(0x6600,0x04);
	msleep(1);
	jxf23s_sensor_write(0x6800,0x00);
	msleep(1);
	jxf23s_sensor_write(0x6900,0x7C);
	msleep(1);
	jxf23s_sensor_write(0x6A00,0x12);
	msleep(1);
	jxf23s_sensor_write(0x7A00,0x80);
	msleep(1);
	jxf23s_sensor_write(0x8200,0x21);
	msleep(1);
	jxf23s_sensor_write(0x8F00,0x91);
	msleep(1);
	jxf23s_sensor_write(0xAE00,0x30);
	msleep(1);
	jxf23s_sensor_write(0x1300,0x81);
	msleep(1);
	jxf23s_sensor_write(0x9600,0x04);
	msleep(1);
	jxf23s_sensor_write(0x4A00,0x05);
	msleep(1);
	jxf23s_sensor_write(0x7E00,0xCD);
	msleep(1);
	jxf23s_sensor_write(0x5000,0x02);
	msleep(1);
	jxf23s_sensor_write(0x4900,0x10);
	msleep(1);
	jxf23s_sensor_write(0xAF00,0x12);
	msleep(1);
	jxf23s_sensor_write(0x7B00,0x4A);
	msleep(1);
	jxf23s_sensor_write(0x7C00,0x08);
	msleep(1);
	jxf23s_sensor_write(0x7F00,0x57);
	msleep(1);
	jxf23s_sensor_write(0x9000,0x00);
	msleep(1);
	jxf23s_sensor_write(0x8C00,0xFF);
	msleep(1);
	jxf23s_sensor_write(0x8D00,0xC7);
	msleep(1);
	jxf23s_sensor_write(0x8E00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x8B00,0x01);
	msleep(1);
	jxf23s_sensor_write(0x0C00,0x00);
	msleep(1);
	jxf23s_sensor_write(0x8100,0x74);
	msleep(1);
	jxf23s_sensor_write(0x1900,0x20);
	msleep(1);
	jxf23s_sensor_write(0x1200,0x20);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x85);
	msleep(1);
	jxf23s_sensor_write(0x4800,0x05);
	msleep(3);
}
/**
 * @brief 
 * 
 */
void  jxf23s_sensor_Rd(void)
{
	jxf23s_sensor_read(0x1200);
	msleep(1);
	jxf23s_sensor_read(0x0E00);
	msleep(1);
	jxf23s_sensor_read(0x0F00);
	msleep(1);
	jxf23s_sensor_read(0x1000);
	msleep(1);
	jxf23s_sensor_read(0x1100);
	msleep(1);
	jxf23s_sensor_read(0x0D00);
	msleep(1);
	jxf23s_sensor_read(0x5F00);
	msleep(1);
	jxf23s_sensor_read(0x6000);
	msleep(1);
	jxf23s_sensor_read(0x5800);
	msleep(1);
	jxf23s_sensor_read(0x5700);
	msleep(1);
	jxf23s_sensor_read(0x9D00);
	msleep(1);
	jxf23s_sensor_read(0x2000);
	msleep(1);
	jxf23s_sensor_read(0x2100);
	msleep(1);
	jxf23s_sensor_read(0x2200);
	msleep(1);
	jxf23s_sensor_read(0x2300);
	msleep(1);
	jxf23s_sensor_read(0x2400);
	msleep(1);
	jxf23s_sensor_read(0x2500);
	msleep(1);
	jxf23s_sensor_read(0x2600);
	msleep(1);
	jxf23s_sensor_read(0x2700);
	msleep(1);
	jxf23s_sensor_read(0x2800);
	msleep(1);
	jxf23s_sensor_read(0x2900);
	msleep(1);
	jxf23s_sensor_read(0x2C00);
	msleep(1);
	jxf23s_sensor_read(0x2D00);
	msleep(1);
	jxf23s_sensor_read(0x2E00);
	msleep(1);
	jxf23s_sensor_read(0x2F00);
	msleep(1);
	jxf23s_sensor_read(0x4100);
	msleep(1);
	jxf23s_sensor_read(0x4200);
	msleep(1);
	jxf23s_sensor_read(0x4600);
	msleep(1);
	jxf23s_sensor_read(0x7600);
	msleep(1);
	jxf23s_sensor_read(0x7700);
	msleep(1);
	jxf23s_sensor_read(0x1D00);
	msleep(1);
	jxf23s_sensor_read(0x1E00);
	msleep(1);
	jxf23s_sensor_read(0x6C00);
	msleep(1);
	jxf23s_sensor_read(0x2A00);
	msleep(1);
	jxf23s_sensor_read(0x2B00);
	msleep(1);
	jxf23s_sensor_read(0x3100);
	msleep(1);
	jxf23s_sensor_read(0x3200);
	msleep(1);
	jxf23s_sensor_read(0x3300);
	msleep(1);
	jxf23s_sensor_read(0x3400);
	msleep(1);
	jxf23s_sensor_read(0x3500);
	msleep(1);
	jxf23s_sensor_read(0x3A00);
	msleep(1);
	jxf23s_sensor_read(0x5600);
	msleep(1);
	jxf23s_sensor_read(0x5900);
	msleep(1);
	jxf23s_sensor_read(0x5A00);
	msleep(1);
	jxf23s_sensor_read(0x8500);
	msleep(1);
	jxf23s_sensor_read(0x8A00);
	msleep(1);
	jxf23s_sensor_read(0x8F00);
	msleep(1);
	jxf23s_sensor_read(0x9100);
	msleep(1);
	jxf23s_sensor_read(0x5B00);
	msleep(1);
	jxf23s_sensor_read(0x5C00);
	msleep(1);
	jxf23s_sensor_read(0x5D00);
	msleep(1);
	jxf23s_sensor_read(0x5E00);
	msleep(1);
	jxf23s_sensor_read(0x6200);
	msleep(1);
	jxf23s_sensor_read(0x6300);
	msleep(1);
	jxf23s_sensor_read(0x6400);
	msleep(1);
	jxf23s_sensor_read(0x6600);
	msleep(1);
	jxf23s_sensor_read(0x6700);
	msleep(1);
	jxf23s_sensor_read(0x6900);
	msleep(1);
	jxf23s_sensor_read(0x6A00);
	msleep(1);
	jxf23s_sensor_read(0x7A00);
	msleep(1);
	jxf23s_sensor_read(0x4A00);
	msleep(1);
	jxf23s_sensor_read(0x7E00);
	msleep(1);
	jxf23s_sensor_read(0x4900);
	msleep(1);
	jxf23s_sensor_read(0x5000);
	msleep(1);
	jxf23s_sensor_read(0x7B00);
	msleep(1);
	jxf23s_sensor_read(0x7C00);
	msleep(1);
	jxf23s_sensor_read(0x7F00);
	msleep(1);
	jxf23s_sensor_read(0x9000);
	msleep(1);
	jxf23s_sensor_read(0x8E00);
	msleep(1);
	jxf23s_sensor_read(0x8C00);
	msleep(1);
	jxf23s_sensor_read(0x8D00);
	msleep(1);
	jxf23s_sensor_read(0x8B00);
	msleep(1);
	jxf23s_sensor_read(0x0C00);
	msleep(1);
	jxf23s_sensor_read(0x6500);
	msleep(1);
	jxf23s_sensor_read(0x8000);
	msleep(1);
	jxf23s_sensor_read(0x8100);
	msleep(1);
	jxf23s_sensor_read(0x1900);
	msleep(1);
	jxf23s_sensor_read(0x1200);
	msleep(1);
	jxf23s_sensor_read(0x4800);
	msleep(1);
	jxf23s_sensor_read(0x4800);
}
/**
 * @brief 
 * 
 */
void jxf23s_sensor_config(void)
{
    jxf23s_sensor_init();
    printf("jxs23s as been configed\n");
    jxf23s_sensor_Rd();
    return;
}
/**
 * @brief 
 * 
 */
void jxs23s_sensor_15fps_config(void)
{
	jxf23s_sensor_init_15fps();
    printf("jxs23s as been configed\n");
    jxf23s_sensor_Rd();
    return;
}