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
#include <sysctl_clk.h>
#include <video/mipi/dphy/mipi_corner.h>
#include <video/mipi/dphy/mipi_txdphy.h>

/*freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1)
Note: 25*NF/NR is output of vco, it has to be in range 720M~3.6G.
*/

void mipi_txdphy_set_pll(uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv)
{
    uint32_t wdata, rdata;
    uint32_t bwadj = fbdiv/2;

    //judge if vco output is beyond range.
    uint32_t vco = 25*(fbdiv+1)/(refdiv+1);
    if(vco < 720 || vco > 3600)
    {
        printf("Error: mipi txdphy pll vco is out of range!\n");
        return;    
    }

    //assert dphy reset
    wdata = readl(VIDEO_DSI_BASE_ADDR + 0x10); 
    wdata &= (~(1 << 20));       
    writel(wdata, VIDEO_DSI_BASE_ADDR + 0x10);

    //power-down mipi pll and reset pll
    wdata = (1 << 31) /*pll reset */
                | (1 << 30) /*pwr down */
                | (1 << 28) /*PLL fast-lock */
                | (1 << 27) /* ENSAT*/
                | (1 << 25) /* PLL Override*/
                | (outdiv << 21) /*PLL D */
                | (0 << 19) /*lane0_sel */
                | (1 << 17) /*lane1_sel */
                | (2 << 15) /*lane2_sel */
                | (3 << 13) /*lane3_sel */;
                    
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

    //set pll para
    wdata = (refdiv << 25) /* CLKR */
                | (fbdiv << 12) /* CLKF*/
                | (bwadj) /*BWADJ*/; 

    
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x4);
                
    //power-on mipi pll   
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
    wdata &= (~(1 << 30));
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

    //sleep 5us
    usleep(5);
    
    
    //de-assert pll reset 
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
    wdata &= (~(1 << 31));
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

    //wait for pll lock
    rdata = 0;
    while((rdata & 0x4) != 0x4)
    {
        rdata =readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
    }

    //de-assert dphy reset
    wdata = readl(VIDEO_DSI_BASE_ADDR + 0x10); 
    wdata |= (1 << 20);       
    writel(wdata, VIDEO_DSI_BASE_ADDR + 0x10);

}


void mipi_txdphy_init(void)
{
    uint32_t rdata, wdata;
    //enable display apb clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB, 1);

    //enable display axi clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VO_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    

    //enable display pix clk, default 148.5MHz
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISPLAY_PIXEL, 1);

    //enale dsi system clock
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM, 1);

    //init corner
    mipi_coner_init();

//    sysctl_boot_set_root_clk_freq(SYSCTL_CLK_ROOT_PLL2, 593, 24, 0);

    //enable txdphy rclk and ref clk            
    sysctl_clk_set_leaf_div(SYSCTL_CLK_MIPI_REF,1, 8);          // 148.5 

    printf("\n\n SYSCTL_CLK_MIPI_REF out clk freq is %d \r\n\n",sysctl_clk_get_leaf_freq(SYSCTL_CLK_MIPI_REF));
    
    sysctl_clk_set_leaf_en(SYSCTL_CLK_MIPI_REF_TXPHY_REF, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_MIPI_REF_TXPHY_PLL, 1);
    
    //de-assert dphy standby
    wdata        = 1 << 14;
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR);


    //init pll, default 891M
//    mipi_txdphy_set_pll(TXDPHY_PLL_891M_F, TXDPHY_PLL_891M_R, TXDPHY_PLL_891M_D);             //p60

    mipi_txdphy_set_pll(TXDPHY_PLL_445M_F, TXDPHY_PLL_445M_R, TXDPHY_PLL_445M_D);
    //default timing settings
    wdata = 0x0f5800c0;                //0x0f180080       0x0f5800a0                 0x0f5800c0
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_init_10M(void)
{
    uint32_t rdata, wdata;
    //enable display apb clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB, 1);

    //enable display axi clk
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_VO_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI, 1);
    

    //enable display pix clk, default 148.5MHz
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISPLAY_PIXEL, 1);

    //enale dsi system clock
    sysctl_clk_set_leaf_en(SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM, 1);

    //init corner
    mipi_coner_init();

    //enable txdphy rclk and ref clk            
    sysctl_clk_set_leaf_div(SYSCTL_CLK_MIPI_REF,1, 8);

    printf("\n\n SYSCTL_CLK_MIPI_REF out clk freq is %d \r\n\n",sysctl_clk_get_leaf_freq(SYSCTL_CLK_MIPI_REF));
    
    sysctl_clk_set_leaf_en(SYSCTL_CLK_MIPI_REF_TXPHY_REF, 1);
    sysctl_clk_set_leaf_en(SYSCTL_CLK_MIPI_REF_TXPHY_PLL, 1);
    
    //de-assert dphy standby
    wdata        = 1 << 14;
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR);


    //init pll, default 891M
    mipi_txdphy_set_pll(TXDPHY_PLL_891M_F, TXDPHY_PLL_891M_R, TXDPHY_PLL_891M_D);

    //default timing settings
    wdata = 0x0f180080;                //0x0f180080       0x0f1be080    
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_enlp(txdphy_lane_t lane)
{
    uint32_t wdata;
    if(lane >= TXDPHY_LANE_MAX)
        return;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0xf << 24));
    wdata |= (((1 << lane) & 0xf) << 24);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_tlpx(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 22));
    wdata |= ((level & 0x3) << 22);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_tlpxesc(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x7 << 19));
    wdata |= ((level & 0x7) << 19);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_tclkprep(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 11));
    wdata |= ((level & 0x3) << 11);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_tclkprzero(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 9));
    wdata |= ((level & 0x3) << 9);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_tclktail(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 7));
    wdata |= ((level & 0x3) << 7);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_thsprep(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 5));
    wdata |= ((level & 0x3) << 5);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_thsprzero(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 3));
    wdata |= ((level & 0x3) << 3);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}

void mipi_txdphy_set_thstrail(uint32_t level)
{
    uint32_t wdata;
    
    wdata = readl(VIDEO_TXDPHY_BASE_ADDR + 0xc);
    wdata &= (~(0x3 << 1));
    wdata |= ((level & 0x3) << 1);
    writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

}


