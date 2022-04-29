/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mipi_csi_reg.c
  Version       : Initial Draft
  Author        :
  Created       :
  Description   :
  History       :
  1.Date        :
    Author      :
    Modification: Created file

******************************************************************************/
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

