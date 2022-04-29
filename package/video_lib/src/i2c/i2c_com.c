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
  File Name     : i2c_com.c
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

#define I2C_DEFAULT_TIMEOUT     1
#define I2C_DEFAULT_RETRY       3

/**
 * @brief 
 * 
 * @param fd 
 * @param i2c_addr 
 * @param reg_addr 
 * @param addr_len 
 * @param reg_val 
 * @param val_len 
 * @return int 
 */

int i2c_nbytes_write(int fd, unsigned char i2c_addr,unsigned char *reg_addr,int addr_len,unsigned char *reg_val, int val_len)
{
    int ret = 0;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages;
    int i;
    packets.nmsgs = 1;
    packets.msgs = &messages;
    //
    messages.addr = i2c_addr;
    messages.flags = I2C_M_REV_DIR_ADDR;  //0 -write
    messages.len = addr_len + val_len; 
    //
    messages.buf = (unsigned char *)malloc(messages.len);
    if (NULL == messages.buf)
    {
        ret = -1;
        goto err;
    }
    //reg_addr
    for (i = 0; i < addr_len; i++)
    {
        messages.buf[i] = reg_addr[i];
    } 
    //reg_val
    for (i = 0; i < val_len; i++)
    {
        messages.buf[addr_len+i] = reg_val[i];
    }

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&packets);
    if (ret < 0){
        printf("write error!\n");
        return -1;
    }
err:
    free(messages.buf);
    return ret;            
}
/**
 * @brief 
 * 
 * @param fd 
 * @param i2c_addr 
 * @param reg_addr 
 * @param addr_len 
 * @param reg_val 
 * @param val_len 
 * @return int 
 */
int i2c_nbytes_read(int fd, unsigned char i2c_addr, unsigned char *reg_addr,int addr_len, unsigned char *reg_val, int val_len)
{
    int ret = 0;
    int i;
    unsigned char outbuf;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];
    //
    packets.nmsgs = 2;
    messages[0].addr = i2c_addr;
    messages[0].flags = 0;              
    messages[0].len = addr_len;                
    messages[0].buf = (unsigned char *)malloc(messages[0].len);
    if (NULL == messages[0].buf)
    {
        ret = -1;
        goto err;
    }
    //reg_addr
    for (i = 0; i < addr_len; i++)
    {
        messages[0].buf[i] = reg_addr[i];
    } 
    //
    messages[1].len = val_len;                       
    messages[1].addr = i2c_addr;                     
    messages[1].flags = I2C_M_RD;                
    messages[1].buf = reg_val;
    //
    packets.msgs = messages;
    ret = ioctl(fd, I2C_RDWR, (unsigned long)&packets); 
    if (ret < 0)
        ret = -1;

err:
    free(messages[0].buf);
    return ret;  
}
/**
 * @brief 
 * 
 * @param fd 
 * @param timeout 
 * @param retry 
 * @return int 
 */
int i2c_set(int fd, unsigned int timeout, unsigned int retry)
{
    if (fd == 0 )
        return -1;
    if (ioctl(fd, I2C_TIMEOUT, timeout ? timeout : I2C_DEFAULT_TIMEOUT) < 0)
        return -1;
    if (ioctl(fd, I2C_RETRIES, retry ? retry : I2C_DEFAULT_RETRY) < 0)
        return -1;
    return 0;
}