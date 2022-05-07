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

#include <video/mipi/dphy/mipi_rxdphy.h>
#ifndef _FPGA
#include <sysctl_clk.h>
void mipi_rxdphy_init(rxdphy_speed_mode_t speed,rxdphy_chcfg_t chcfg)
{
    unsigned int rdata, wdata = 0x0003a000;//0x0003a002;//0x0003a000;//0x0003a002;
    unsigned int dllrange = 208;

    //enable video apb clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_0_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_1_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_2_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_CSI_3_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_F2K_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_R2K_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VI_APB, 1);
    

    //enable video axi clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VI_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI, 1);   

    //enable sys clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_0_SYSTEM, 1); 
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_1_SYSTEM, 1);

    //enable pixel clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_0_PIXEL, 1); 
    sysctl_clk_set_leaf_en(SYSCTL_CLK_CSI_1_PIXEL, 1); 
    sysctl_clk_set_leaf_en(SYSCTL_CLK_TPG_PIXEL, 1); 

    //enable rxdphy ref clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_MIPI_REF_RXPHY_REF, 1);
 
    //init mipi corner
    mipi_coner_init();

    if(chcfg == RXDPHY_CHCFG_1X4)
        wdata |= 1; //one 4x1 mode

    if(speed == RXDPHY_SPEED_MODE_2500M)
    {
        wdata |= 1 << 2; //enable deskew
        dllrange = 124;
    }
    //wdata=0x0003a003;
    //wdata |=0x1<<15; //Tclk_term_en and Ths_term_en
    //wdata |=0x2<<13; //Ths_settle
    //wdata |=0x2<<11; //Tclk_miss
    //wdata |=0x2<<9; //Tclk_settle
    writel(wdata, VIDEO_RXDPHY_BASE);
    //writel((dllrange << 7) | (dllrange << 15), VIDEO_RXDPHY_BASE + 4); 
    writel((dllrange << 8) | (dllrange << 0), VIDEO_RXDPHY_BASE + 4);    
    printf("rxphy0 0x%x,0x%x\n",wdata,readl(VIDEO_RXDPHY_BASE));
    printf("rxphy4 0x%x,0x%x\n",(dllrange << 8) | (dllrange << 0),readl(VIDEO_RXDPHY_BASE+4));

}

unsigned int mipi_rxdphy_get_status(void)
{
    return readl(VIDEO_RXDPHY_BASE + 0x10);
}

unsigned int mipi_rxdphy_get_errstatus(void)
{
    return readl(VIDEO_RXDPHY_BASE + 0x14);
}

void mipi_rxdphy_standy(void)
{

}

void mipi_rxdphy_enable_deskew(void)
{

}

void mipi_rxdphy_disable_deskew(void)
{

}

void mipi_rxdphy_invert_lane(int lane)
{

}

void mipi_rxdphy_set_tclktermen(int enable)
{

}

void mipi_rxdphy_set_thstermen(int enable)
{

}

void mipi_rxdphy_set_thssettle(int value)
{

}

void mipi_rxdphy_settclkmiss(int value)
{

}

void mipi_rxdphy_set_tclksettle(int value)
{

}
#endif
