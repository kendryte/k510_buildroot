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
  File Name     : exctl_dev.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#include "dev_reg.h"
#include "dev_hw.h"
#include "i2c/i2c_com.h"
#include "isp_com.h"
#ifdef __cplusplus  
extern "C"{
#endif

/*
*
*/
void RegWr32(unsigned int addr, unsigned int data) 
{
#ifdef __LINUX__
//    printf("RegWr32 is start \n");
    reg_isp.id = addr - VIDEO_SUBSYSTEM_BASE_ADDR;
    reg_isp.value = data;
    if (ioctl(fd_isp, ISP_CMD_WRITE_REG, &reg_isp) < 0)
    {
        printf("Call cmd ISP_CMD_WRITE_REG fail, reg %u\n", reg_isp.id);
        return -1;
    }
//    printf("RegWr32 is end \n");
#else
    *(volatile unsigned int *)addr = data;
#endif
}
/*
*
*/
unsigned int RegRd32(unsigned int addr) 
{
#ifdef __LINUX__
    reg_isp.id = addr - VIDEO_SUBSYSTEM_BASE_ADDR;
    reg_isp.value = 0;
    if (ioctl(fd_isp, ISP_CMD_READ_REG, &reg_isp) < 0)
    {
        printf("Call cmd ISP_CMD_READ_REG fail, reg %u\n", reg_isp.id);
        return -1;
    }
    return reg_isp.value;
#else
    return *(volatile unsigned int *)addr;
#endif
}
/*
*
*/
void ExtCtlRegWr(unsigned int addr,unsigned int data)
{
    int offset_addr = EXTER_CTL_START + (addr <<2);
    RegWr32(offset_addr,data) ;
}
/*
*
*/
int ExtCtlRegRd(int addr)
{
    int offset_addr = EXTER_CTL_START +(addr <<2);
    return(RegRd32(offset_addr));
}
/*
*
*/
void DevRegWr(int addr,int data)
{
 int offset_addr = SENSOR_ADV7511CTRL_BASEADDR +(addr <<2);
 RegWr32(offset_addr,data) ;
}
/*
*
*/
int  DevRegRd(int addr)
{
    int offset_addr =0;
    offset_addr = SENSOR_ADV7511CTRL_BASEADDR +(addr <<2);
    return(RegRd32(offset_addr));
}
/*
*
*/
void AxibusRstnActive()
{
    ExtCtlRegWr(0x0,0x00);
}
/*
*
*/
void AxibusRstnRelease()
{
    ExtCtlRegWr(0x0,0x01);
}
/*
*
*/
void IspRstnActive()
{
    ExtCtlRegWr(0x01,0x00);
}
/*
*
*/
void IspRstnRelease()
{
    ExtCtlRegWr(0x01,0x01);
}
/*
*
*/
void VideoInRstnActive()
{
    ExtCtlRegWr(0x02,0x00);
}
/*
*
*/
void VideoInRstnRelease()
{
    ExtCtlRegWr(0x02,0x01);
}
/*
*
*/
void SensorRstnActive()
{
    ExtCtlRegWr(0x04,0x00);
}
void SensorRstnRelease()
{
    ExtCtlRegWr(0x04,0x01);
}
/*
*
*/
void VideoOutRstnActive()
{
    ExtCtlRegWr(0x05,0x00);
}
/*
*
*/
void VideoOutRstnRelease()
{
    ExtCtlRegWr(0x05,0x01);
}
/*
*
*/
int  SysIsReady()
{
    return(ExtCtlRegRd(0xff));
}

/*
*
*/
void  SysRstActive()
{
    printf("system is ready to Release rst_n\n");
#ifndef CANAAN_ISP
    AxibusRstnActive();
    msleep(1);
    IspRstnActive();
    msleep(1);
    VideoInRstnActive();
    msleep(1);
    VideoOutRstnActive();
    msleep(1);
#endif    
    printf("system rst_n  has all release\n");

}
/*
*
*/
void  SysRstnRelease()
{
#ifndef CANAAN_ISP

    while (SysIsReady() != 0x01 )
    {
        printf("%x\n",SysIsReady());
    }
    printf("system is ready to Release rst_n\n");
    AxibusRstnRelease();
    IspRstnRelease();
    VideoInRstnRelease();
    VideoOutRstnRelease();
#endif
    printf("system rst_n  has all release\n");

}
/*
*
*/
void  Dev_config_apb25MHZ(int byte_mode_config,int sensor_dev_addr,int dev_sel)
{
  DevRegWr(BYTE_MODE_CONFIG_OFFSET,byte_mode_config);
  DevRegWr(SENSOR_DEV_ADDR_OFFSET,sensor_dev_addr);
  int apb_clk_cnt = (10000/40);
  DevRegWr(I2C_CLK_PRIOD_OFFSET,apb_clk_cnt);
  DevRegWr(I2C_SEL_OFFSET,1<<dev_sel);
}
/*
*
*/
void  Set_manu(int enable)
{
#ifndef CANAAN_ISP
    DevRegWr(SENSOR_MANU_OP_OFFSET,enable);
#endif
}
/*
*
*/
void  Set_auto(int enable)
{
#ifndef CANAAN_ISP
    DevRegWr(SENSOR_AUTO_OP_OFFSET,enable);
#endif
}
/*
*
*/
void  Start_Config(int start_flag)
{
    DevRegWr(START_CONFIG_OFFSET,start_flag);
}
/*
*
*/
void Active_Cv8788_rstn(void)
{
    //use power-on reset on EVB for now
}
/*
*
*/
void Release_Cv8788_rstn(void)
{
    //use power-on reset on EVB for now   
}

#ifdef __cplusplus
} 
#endif
