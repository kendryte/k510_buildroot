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
  File Name     : cv8788.c
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

#include "i2c/i2c_com.h"
#include "exctl_dev/dev_hw.h"
#include "isp_com.h"

#define I2C_DEVICE_NAME                 "/dev/i2c-1" 
#define CV8788_CHIP_ADDR                (0x3d)

static int i2c_fd = 0;
/**
 * @brief 
 * 
 */
void cv8788_i2c_init(void)
{
	i2c_fd = open(I2C_DEVICE_NAME, O_RDWR);
    if(i2c_fd < 0)
    {
         printf("open %s faild \n", I2C_DEVICE_NAME); 
    }

    if (ioctl(i2c_fd, I2C_SLAVE_FORCE, CV8788_CHIP_ADDR) < 0) 
    { 
        printf("oictl:setslave address failed/n");

    }
	//
    i2c_set(i2c_fd, 20, 2);

    msleep(5);
    Active_Cv8788_rstn();
    msleep(5);
    Release_Cv8788_rstn();
    msleep(5);
}
/**
 * @brief 
 * 
 * @param reg_addr 
 * @param reg_val 
 */
void cv8788_write(uint16_t reg_addr,uint8_t reg_val)
{
    uint8_t addr[2];
    addr[0] = (reg_addr>>8) & 0xff;
    addr[1] = reg_addr & 0xff;
    uint8_t val = reg_val;
    i2c_nbytes_write(i2c_fd,CV8788_CHIP_ADDR,&addr,2,&val,1);
}
/**
 * @brief 
 * 
 * @param reg 
 */
void cv8788_read(uint16_t reg_addr)
{
    uint8_t reg_val = 0;
    uint8_t addr[2];
    addr[0] = (reg_addr>>8) & 0xff;
    addr[1] = reg_addr & 0xff;

    i2c_nbytes_read(i2c_fd,CV8788_CHIP_ADDR,&addr,2,&reg_val,1);
    printf("reg is %x val is %x \n", reg_addr, reg_val);
}

/*
*
*/
unsigned int cv8788data[]=
{
    0x070000,
    0x080000,
    0x030000,
    0x040000,
    0x070080,
    0x0800f3,
    0x0c003a,
    0x0d0070,
    0x0e0040,
    0x0f0000,
    0x100000,
    0x110000,
    0x120000,
    0x130000,
    0x140000,
    0x1800ff,
    0x1900ff,
    0x1a0007,
    0x1b00ff,
    0x1c00ff,
    0x1d004f,
    0x1e0000,
    0x1f0004,
    0x290020,
    0x370000,
    0x3d0000,
    0x460002,
    0x4a0031,
    0x4b0000,
    0x4c00a2,
    0x4d0000,
    0x1001c0,
    0x110120,
    0x120152,
    0x130102,
    0x14011f,
    0x150118,
    0x160102,
    0x170142,
    0x1801f0,
    0x190100,
    0x800111,
    0x810104,
    0x820100,
    0x830100,
    0x8401f5,
    0x85014a,
    0x86010d,
    0x870100,
    0x8801c0,
    0x890100,
    0x8a0128,
    0x8b0100,
    0x8c0198,
    0x8d0108,
    0x8e0165,
    0x8f0104,
    0x90012c,
    0x910100,
    0x920105,
    0x930100,
    0x9401c0,
    0x950100,
    0x960140,
    0x970108,
    0x980129,
    0x990100,
    0x9a0161,
    0x9b0104,
    0x9c0100,
    0x9d0100,
    0x9e0100,
    0x9f0100,
    0xa00100,
    0xa10180,
    0xa20180,
    0xa30180,
    0xa40100,
    0xa50100,
    0xa60100,
    0xa70100,
    0xa80100,
    0xa90100,
    0xaa0100,
    0xab0100,
    0xac0100,
    0xad0100,
    0xb00100,
    0xc00107,
    0xc10100,
    0xc20100,
    0xc30110,
    0xc40111,
    0xc501e0,
    0xc60103,
    0xc70103,
    0xd00102,
    0xd10119,
    0xd20100,
    0xd30100,
    0xd40119,
    0xd50105,
    0xd60104,
    0xd70104,
    0xd80100,
    0xd90100,
    0xda0100,
    0xdb0101,
    0xdc0101,
    0xdd0101,
    0xe10100,
    0xe20101,
    0xe30100,
    0xe60100,
    0xe70100,
    0xe80100,
    0xe90101,
    0xea0184,
    0xeb010a,
    0xec0100,
    0xed0100,
    0xee0160,
    0xef0100,
    0xf00100,
    0xf10100,
    0xf20100,
    0xf30100,
    0xf40101,
    0xf50100,
    0xf60100,
    0xf80100,
    0xf90100,
    0xfa0110,
    0xfd0100,
    0x040200,
    0x050203,
    0x060200,
    0x0702cc,
    0x080254,
    0x0902a5,
    0x0a022a,
    0x100230,
    0x110284,
    0x120281,
    0x130200,
    0x140200,
    0x150252,
    0x160280,
    0x170288,
    0x180286,
    0x190268,
    0x1a0200,
    0x1b0200,
    0x1c0200,
    0x500280,
    0x510200,
    0x520200,
    0x530200,
    0x540200,
    0x550200,
    0xEE0100,
    0xEA0182,
    0xE90102,
    0xEB010D,
    0xED0183,
    0xED0112,
    0xED01b8,
    0xED0100,
    0xED0122,
    0xED0100,
    0xEE0140,
    0x1001C0,
    0x110120,
    0x120152,
    0x130102,
    0x14011F,
    0x150118,
    0x160102,
    0x170142,
    0x1801F0,
    0x190100,
    0x100230,
    0x150252,
    0x110284,
    0xEE0140,
    0xEA0184,
    0xE90101,
    0xEB010A,
    0xED0171,
    0xED0100,
    0xEE0160,
};
/*
*
*/
void cv8788Init(void)
{
	printf("cv8788Init\n");
    //
    cv8788_i2c_init();
    //
    int i,addr,data;
    for(i=0;i<sizeof(cv8788data)/4;i++)
    {
        addr = cv8788data[i] >> 8;
        data = cv8788data[i] & 0xff;
        cv8788_write(addr,data);       
        msleep(1);
    }        
	printf("Cv8788_I2cRd\n");
    //read back test
    cv8788_read(0x0800);
    cv8788_read(0xEA01);
    cv8788_read(0xE901);
    cv8788_read(0xEB01);
    cv8788_read(0xED01);
    cv8788_read(0xEE01); 
}