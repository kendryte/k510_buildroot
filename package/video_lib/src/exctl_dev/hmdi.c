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
  File Name     : hdmi.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#include "exctl_dev/dev_reg.h"
#include "i2c/i2c_com.h"
#include "isp_com.h"

extern int fd_isp;
/*
*
*/
void Release_imx385_fpga_reset_n()
{
    if (ioctl(fd_isp, ISP_CMD_RLS_SENSOR_RST, 0) < 0)
    {
        printf("Call cmd ISP_CMD_RLS_SENSOR_RST fail\n");
    }

}
/*
*
*/
void  Active_imx385_fpga_reset_n()
{  
    if (ioctl(fd_isp, ISP_CMD_ACT_SENSOR_RST, 0) < 0)
    {
        printf("Call cmd ISP_CMD_ACT_SENSOR_RST fail\n");
    }
}
/*
*
*/
void fpga_system_init(int isJxf23s)
{
    SysRstActive();
    if(0 == isJxf23s)
    {
        Active_imx385_fpga_reset_n();
    }
    sleep(1);
    SysRstnRelease();

    return;

}
/*
*
*/
void Release_f23s_fpga_rst_n()
{
    if (ioctl(fd_isp, ISP_CMD_RLS_SENSOR_RST, 0) < 0)
    {
        printf("Call cmd ISP_CMD_RLS_SENSOR_RST fail\n");
    }
}
/*
*
*/
void Release_f23s_fpga_pwdn()
{
    if (ioctl(fd_isp, ISP_CMD_ACT_SENSOR_RST, 0) < 0)
    {
        printf("Call cmd ISP_CMD_ACT_SENSOR_RST fail\n");
    }
}

void Release_dvp_fpga_rst_n()
{

}
/*
*
*/
void Release_dvp_fpga_pwdn()
{
    if (ioctl(fd_isp, DVP_CMD_ACT_SENSOR_RST, 0) < 0)
    {
        printf("Call cmd ISP_CMD_ACT_SENSOR_RST fail\n");
    }
}

