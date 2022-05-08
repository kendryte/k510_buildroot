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
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "video/mipi/csi/mipi_csi_reg.h"
//#include "hw_dev/inc/ext_ctl_hw.h"

void csi_host_RegWr(int stream_id,int addr,int data)
{
	int offset_addr =0;
	switch (stream_id)
	{
	   case 0: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM0_BASE_ADDR <<8) + addr;break;
	   case 1: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM1_BASE_ADDR <<8) + addr;break;
	   case 2: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM2_BASE_ADDR <<8) + addr;break;
	   case 3: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM3_BASE_ADDR <<8) + addr;break;
	   default: offset_addr = CSI_HOST_BASE + addr;break;
	}
	printf("csi_host_RegWr addr :0x%x data :0x%x\n",offset_addr,data);
	//printf("1<<8 :0x%x\n",(0x1 <<8));
	//RegWr32(offset_addr,data);
	writel(data, offset_addr);
}



int  csi_host_RegRd(int stream_id,int addr)
{
	int offset_addr =0;
	switch (stream_id)
	{
	   case 0: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM0_BASE_ADDR <<8) + addr;break;
	   case 1: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM1_BASE_ADDR <<8) + addr;break;
	   case 2: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM2_BASE_ADDR <<8) + addr;break;
	   case 3: offset_addr = CSI_HOST_BASE + (CSI_RX_STREAM3_BASE_ADDR <<8) + addr;break;
	   default: offset_addr = CSI_HOST_BASE + addr;break;
	}
//	printf("csi_host_RegRd addr :0x%x\n",offset_addr);
    //return(RegRd32(offset_addr));
	return(readl(offset_addr));
}

void csi_1_host_RegWr(int stream_id,int addr,int data)
{
	int offset_addr =0;
	switch (stream_id)
	{
	   case 0: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM0_BASE_ADDR <<8) + addr;break;
	   case 1: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM1_BASE_ADDR <<8) + addr;break;
	   case 2: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM2_BASE_ADDR <<8) + addr;break;
	   case 3: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM3_BASE_ADDR <<8) + addr;break;
	   default: offset_addr = CSI_1_HOST_BASE + addr;break;
	}
	printf("csi_1_host_RegWr addr :0x%x data :0x%x\n",offset_addr,data);
	//RegWr32(offset_addr,data) ;
	writel(data, offset_addr);
}



int  csi_1_host_RegRd(int stream_id,int addr)
{
	int offset_addr =0;
	switch (stream_id)
	{
	   case 0: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM0_BASE_ADDR <<8) + addr;break;
	   case 1: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM1_BASE_ADDR <<8) + addr;break;
	   case 2: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM2_BASE_ADDR <<8) + addr;break;
	   case 3: offset_addr = CSI_1_HOST_BASE + (CSI_RX_STREAM3_BASE_ADDR <<8) + addr;break;
	   default: offset_addr = CSI_1_HOST_BASE + addr;break;
	}
    return(RegRd32(offset_addr));
}

