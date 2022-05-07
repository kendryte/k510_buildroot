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

