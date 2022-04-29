/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mipi_corner.c
  Version       : Initial Draft
  Author        :
  Created       :
  Description   :
  History       :
  1.Date        :
    Author      :
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <io.h>
#include <video/video_subsystem_addr.h>
#include <video/mipi/dphy/mipi_corner.h>

#ifndef _FPGA
#include <sysctl_clk.h>


unsigned int g_mipi_corner_initialized = 0;
void mipi_coner_init(void)
{
    unsigned int rdata, wdata;

    if(g_mipi_corner_initialized == 0)
    {
        sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB, 1);
        //MIPI_CORNER_CFG  0x92680000
        rdata =readl(VIDEO_SUBSYS_MIPI_CORNER_REG_BASE);
        wdata=rdata |0x8;
        writel(wdata, VIDEO_SUBSYS_MIPI_CORNER_REG_BASE);
        
        rdata =readl(VIDEO_SUBSYS_MIPI_CORNER_REG_BASE);
        wdata=rdata |0x4;
        writel(wdata, VIDEO_SUBSYS_MIPI_CORNER_REG_BASE);
        //MIPI_CORNER_STA 0x92680004
        rdata =readl(VIDEO_SUBSYS_MIPI_CORNER_REG_BASE+0x4);
        printf("MIPI_CORNER_STA =0x%x,data=0x%x\n",VIDEO_SUBSYS_MIPI_CORNER_REG_BASE+0x4,rdata);
        while((rdata & 0x10000) != 0x10000)
        {
          printf("MIPI_CORNER_STA =0x%x,data=0x%x\n",VIDEO_SUBSYS_MIPI_CORNER_REG_BASE+0x4,rdata);
          rdata =readl(VIDEO_SUBSYS_MIPI_CORNER_REG_BASE+0x4);
        } 

        g_mipi_corner_initialized = 1;
    }
}
#endif

