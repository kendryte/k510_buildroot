/*
 * cnds_dsi_hw.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Administrator
 */
#include <io.h>
#include <stdlib.h>
#include "video/mipi/dsi/cnds_dsi_define.h"
#include "video/mipi/dsi/cnds_dsi_hw.h"
//#include "hw_dev/inc/ext_ctl_hw.h"

//#include <io_ms.h>
 void DsiRegWr(int addr,int data)
 {
     int offset_addr = CNDS_DSI_REG_START +(addr );
     //RegWr32(offset_addr,data) ;
     writel(data,offset_addr);
 }

 int  DsiRegRd(int addr)
 {
 	int offset_addr =0;
 	offset_addr = CNDS_DSI_REG_START +(addr );
 	//return(RegRd32(offset_addr));
 	return(readl(offset_addr));
 }
