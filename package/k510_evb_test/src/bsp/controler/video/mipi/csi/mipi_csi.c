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
#include "video/mipi/csi/mipi_csi_reg.h"
#include "video/mipi/csi/mipi_csi.h"

#if 0
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_normal_30fps()
{
     //#--------------------(1920x1080-RAW12bit):
     //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000011);//#0x004,softreset
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000000);//#0x004
     csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,      0x43210200);//#0x43_21_02_00 --2lane##0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
     csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,        0x00000007);//#0x010,error bypass

    // printf("CSI_RX_STATIC_CFG_ADDR :%x\n",csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR));
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

     csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00000013);//#0x040,dphy lane 0/1 and clock lane enable

     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

     //#stream 0
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     //printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start
    // printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0001AAC);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)

    // printf("CSI_RX_STREAM_DATA_CFG_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_DATA_CFG_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(0x0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(0x0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(0x0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode

     //#stream 1
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start
     csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0002AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode

     //#stream 2
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start
     csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0004AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode

     //#--------------------CSI_1 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000011);//#0x004,softreset
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000000);//#0x004
     csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,  0x21430200);//#0x008,phy, 4alnes enable
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,    0x00000007);//#0x010,error bypass

     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,    0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,    0x00000000);//#0x01C,monitor,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,    0x00000000);//#0x020,info,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,    0x00000000);//#0x024,info,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,    0x00000000);//#0x028,error,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,    0x00000000);//#0x02C,error,interrupt,mask

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,    0x0000001C);//#0x040,dphy lane 0/1 and clock lane enable

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,    0x00000000);//#0x04C,error,interrupt,status
     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,    0x00000000);//#0x050,error,interrupt,mask

     //#stream 0
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start
     csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00012AAC);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode

     //#stream 1
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start
     csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode

     //#stream 2
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start
     csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
}
#else

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_normal_30fps()
{
     //#--------------------(1920x1080-RAW12bit):
     //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000011);//#0x004,softreset
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000000);//#0x004
     csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,      0x43210200);//#0x43_21_02_00 --2lane##0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
     csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,        0x00000007);//#0x010,error bypass

    // printf("CSI_RX_STATIC_CFG_ADDR :%x\n",csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR));
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

     csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00013013);//0x00000013 #0x040,dphy lane 0/1 and clock lane enable

     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

     //#stream 0
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     //printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
    // printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0012AAC);//0x0001AAC#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)

    // printf("CSI_RX_STREAM_DATA_CFG_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_DATA_CFG_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(0x0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(0x0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(0x0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

     //#stream 1
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000000);//#0x100,start

     //#stream 2
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000000);//#0x100,start
#if 1
     //#--------------------CSI_1 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000011);//#0x004,softreset
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000000);//#0x004
     csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,  0x12430200);//#0x008,phy, 4alnes enable
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,    0x00000007);//#0x010,error bypass

     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,    0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,    0x00000000);//#0x01C,monitor,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,    0x00000000);//#0x020,info,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,    0x00000000);//#0x024,info,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,    0x00000000);//#0x028,error,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,    0x00000000);//#0x02C,error,interrupt,mask

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,    0x0001c01c);//#0x040,dphy lane 0/1 and clock lane enable

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,    0x00000000);//#0x04C,error,interrupt,status
     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,    0x00000000);//#0x050,error,interrupt,mask
     //#stream 0
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00001AAC);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start

     //#stream 1
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start

     //#stream 2
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start
#endif
}

#endif


void cdns_mipi_reg_rd(void)
{
    #if 0
     //#--------------------(1920x1080-RAW12bit):
     //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_host_RegRd(0xf, CSI_RX_SOFT_RESET_ADDR      );//#0x004,softreset
     csi_host_RegRd(0xf, CSI_RX_SOFT_RESET_ADDR      );//#0x004
     csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR      );//#0x43_21_02_00 --2lane##0x008,phy, 4alnes enable bit[15:1
     csi_host_RegRd(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR);//#0x010,error bypass

    // printf("CSI_RX_STATIC_CFG_ADDR :%x\n",csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR));
     csi_host_RegRd(0xf, CSI_RX_MONITOR_IRQS_ADDR        );//#0x018,monitor,interrupt,clear/read
     csi_host_RegRd(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   );//#0x01C,monitor,interrupt mask
     csi_host_RegRd(0xf, CSI_RX_INFO_IRQS_ADDR           );//#0x020,info,interrupt,clear/read
     csi_host_RegRd(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      );//#0x024,info,interrupt mask
     csi_host_RegRd(0xf, CSI_RX_ERROR_IRQS_ADDR          );//#0x028,error,interrupt,clear/read
     csi_host_RegRd(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     );//#0x02C,error,interrupt,mask

     csi_host_RegRd(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   );//#0x040,dphy lane 0/1 and clock lane enable

     csi_host_RegRd(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR );//#0x04C,error,interrupt,status
     csi_host_RegRd(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   );//#0x050,error,interrupt,mask

     //#stream 0
     csi_host_RegRd(0x0,CSI_RX_STREAM_CTRL_ADDR);//#0x100,soft reset
     //printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
    // printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegRd(0x0,CSI_RX_STREAM_DATA_CFG_ADDR);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12

    // printf("CSI_RX_STREAM_DATA_CFG_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_DATA_CFG_ADDR));
     csi_host_RegRd(0x0,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegRd(0x0,CSI_RX_STREAM_MONITOR_CTRL_ADDR);//#0x110,
     csi_host_RegRd(0x0,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_host_RegRd(0x0,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_host_RegRd(0x0,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_host_RegRd(0x0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_host_RegRd(0x0,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start

     //#stream 1
     csi_host_RegRd(1,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,soft reset
     csi_host_RegRd(1,CSI_RX_STREAM_DATA_CFG_ADDR    );//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegRd(1,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegRd(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR);//#0x110,
     csi_host_RegRd(1,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_host_RegRd(1,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_host_RegRd(1,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_host_RegRd(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_host_RegRd(1,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start

     //#stream 2
     csi_host_RegRd(2,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,soft reset
     csi_host_RegRd(2,CSI_RX_STREAM_DATA_CFG_ADDR    );//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegRd(2,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegRd(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,);//#0x110,
     csi_host_RegRd(2,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_host_RegRd(2,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_host_RegRd(2,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_host_RegRd(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_host_RegRd(2,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start
     //#--------------------CSI_1 channel-----------------------------------------------------------------------------------




     //#CDNS
     csi_1_host_RegRd(0xf, CSI_RX_SOFT_RESET_ADDR      );//#0x004,softreset
     csi_1_host_RegRd(0xf, CSI_RX_SOFT_RESET_ADDR      );//#0x004
     csi_1_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR      );//#0x008,phy, 4alnes enable
     csi_1_host_RegRd(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR );//#0x010,error bypass

     csi_1_host_RegRd(0xf, CSI_RX_MONITOR_IRQS_ADDR     );//#0x018,monitor,interrupt,clear/read
     csi_1_host_RegRd(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR);//#0x01C,monitor,interrupt mask
     csi_1_host_RegRd(0xf, CSI_RX_INFO_IRQS_ADDR        );//#0x020,info,interrupt,clear/read
     csi_1_host_RegRd(0xf, CSI_RX_INFO_IRQS_MASK_ADDR   );//#0x024,info,interrupt mask
     csi_1_host_RegRd(0xf, CSI_RX_ERROR_IRQS_ADDR       );//#0x028,error,interrupt,clear/read
     csi_1_host_RegRd(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR  );//#0x02C,error,interrupt,mask

     csi_1_host_RegRd(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR);//#0x040,dphy lane 0/1 and clock lane enable

     csi_1_host_RegRd(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR);//#0x04C,error,interrupt,status
     csi_1_host_RegRd(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR);//#0x050,error,interrupt,mask




     //#stream 0
     csi_1_host_RegRd(0,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,soft reset
     csi_1_host_RegRd(0,CSI_RX_STREAM_DATA_CFG_ADDR    );//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW1
     csi_1_host_RegRd(0,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegRd(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR);//#0x110,
     csi_1_host_RegRd(0,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_1_host_RegRd(0,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegRd(0,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_1_host_RegRd(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_1_host_RegRd(0,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start

     //#stream 1
     csi_1_host_RegRd(1,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,soft reset
     csi_1_host_RegRd(1,CSI_RX_STREAM_DATA_CFG_ADDR    );//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW1
     csi_1_host_RegRd(1,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegRd(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR);//#0x110,
     csi_1_host_RegRd(1,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_1_host_RegRd(1,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegRd(1,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_1_host_RegRd(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_1_host_RegRd(1,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start

     //#stream 2
     csi_1_host_RegRd(2,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,soft reset
     csi_1_host_RegRd(2,CSI_RX_STREAM_DATA_CFG_ADDR    );//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW1
     csi_1_host_RegRd(2,CSI_RX_STREAM_CFG_ADDR         );//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_1_host_RegRd(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR);//#0x110,
     csi_1_host_RegRd(2,CSI_RX_STREAM_TIMER_ADDR       );//#0x11c,counter of timer
     csi_1_host_RegRd(2,CSI_RX_STREAM_FCC_CFG_ADDR     );//#0x120,counter of frame start/end for interrupt
     csi_1_host_RegRd(2,CSI_RX_STREAM_FCC_CTRL_ADDR    );//#0x124,FCC enable frame counter capture
     csi_1_host_RegRd(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR);//#0x128,FIFO monitor mode
     csi_1_host_RegRd(2,CSI_RX_STREAM_CTRL_ADDR        );//#0x100,start
     #endif
}
/*
 * 
 */
#if 0
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR          ,      0x43211200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,      0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00013013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0011AAc);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start

    //stream 1
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0021AAc);//0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start

    //stream 2
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0044AAc);//0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start

}
#else
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps()
{
     //#--------------------(1920x1080-RAW12bit):
     //#--------------------CSI_0 channel-------------------------------------------------------------------------------
     //#CDNS
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000011);//#0x004,softreset
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000000);//#0x004
     csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,      0x43211200);//#0x43_21_02_00 --2lane##0x008,phy, 4aln
     csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,        0x00000007);//#0x010,error bypass

    // printf("CSI_RX_STATIC_CFG_ADDR :%x\n",csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR));
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

     csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00013013);//0x00000013 #0x040,dphy lane 0/1 and clock 

     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

     //#stream 0
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     //printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
    // printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0012AAc);//0x0011AAc);//0x0001AAC#0x108,VC=2'b00,datatype:1E(YUV422);

    // printf("CSI_RX_STREAM_DATA_CFG_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_DATA_CFG_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_f
     csi_host_RegWr(0x0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(0x0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interru
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(0x0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

     //#stream 1
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0022AAC);//0x0021AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B
     csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_ful
     csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

     //#stream 2
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0042AAC);//0x0041AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B
     csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_ful
     csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

     //#--------------------CSI_1 channel-------------------------------------------------------------------------------
     //#CDNS
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000011);//#0x004,softreset
     csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR           ,    0x00000000);//#0x004
     csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,  0x43211200);//#0x008,phy, 4alnes enable
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,    0x00000007);//#0x010,error bypass

     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,    0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,    0x00000000);//#0x01C,monitor,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,    0x00000000);//#0x020,info,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,    0x00000000);//#0x024,info,interrupt mask
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,    0x00000000);//#0x028,error,interrupt,clear/read
     csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,    0x00000000);//#0x02C,error,interrupt,mask

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,    0x0001c01c);//#0x040,dphy lane 0/1 and clock lane enable

     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,    0x00000000);//#0x04C,error,interrupt,status
     csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,    0x00000000);//#0x050,error,interrupt,mask
     //#stream 0
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00001AAC);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8)
     csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_
     csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interr
     csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000000);//#0x100,start

     //#stream 1
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8)
     csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_
     csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interr
     csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000000);//#0x100,start

     //#stream 2
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
     csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8)
     csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_
     csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
     csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interr
     csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
     csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
     csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000000);//#0x100,start

}
#endif

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps_cs1()
{


    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR          ,      0x43211200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,      0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00000013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0011AAc);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start

    //stream 1
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0021AAc);//0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start

    //stream 2
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//0x100,soft reset
    csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0044AAc);//0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//0x110,
    csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//0x11c,counter of timer
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//0x100,start
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,      0x00000011);//0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,      0x00000000);//0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR            ,      0x43211200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR  ,      0x00000007);//0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR      ,      0x00000000);//0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR ,      0x00000000);//0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR         ,      0x00000000);//0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR        ,      0x00000000);//0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR            ,      0x00000000);//0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR   ,      0x00000000);//0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR ,      0x00000013);//0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,    0x00000000);//0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR ,      0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,            0x0000010);//0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,        0x0011AAc);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,             0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,    0x0000000);//0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,               0x0000000);//0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,         0x0000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,        0x0000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,       0x0000000);//0x128,FIFO monitor mode
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,            0x0000001);//0x100,start

    //stream 1
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,            0x0000010);//0x100,soft reset
    csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,        0x0021AAc);//0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,             0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,    0x0000000);//0x110,
    csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,               0x0000000);//0x11c,counter of timer
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,         0x0000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,        0x0000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,       0x0000000);//0x128,FIFO monitor mode
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,            0x0000001);//0x100,start

    //stream 2
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,            0x0000010);//0x100,soft reset
    csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,        0x0044AAc);//0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,             0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,    0x0000000);//0x110,
    csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,               0x0000000);//0x11c,counter of timer
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,         0x0000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,        0x0000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,       0x0000000);//0x128,FIFO monitor mode
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,            0x0000001);//0x100,start

    }

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps()
{
    //#--------------------(1920x1080-RAW12bit):
    //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //#CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000011);//#0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000000);//#0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR          ,      0x43211200);//#0x43_21_02_00 --2lane//#//#0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,       0x00000007);//#0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00013013);//#0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

    //#stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0012AAc);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 1
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0022AAc);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 2
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0042AAc);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //#CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,    0x00000011);//#0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,    0x00000000);//#0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR              ,  0x43211200);//#0x008,phy, 4alnes enable
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,    0x00000007);//#0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,    0x00000000);//#0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,    0x00000000);//#0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,    0x00000000);//#0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,    0x00000000);//#0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,    0x00000000);//#0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,    0x00000000);//#0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,    0x0001C01C);//#0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,    0x00000000);//#0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,    0x00000000);//#0x050,error,interrupt,mask

    //#stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00012AAC);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start

    //#stream 1
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
    csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
    csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start

    //#stream 2
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000010);//#0x100,soft reset
    csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x00042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x00000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x00000000);//#0x110,
    csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x00000000);//#0x11c,counter of timer
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x00000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x00000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x00000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x00000001);//#0x100,start
};

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps_cs1()
{
    //#--------------------(1920x1080-RAW12bit):
    //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //#CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000011);//#0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR          ,      0x00000000);//#0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR          ,      0x43211200);//#0x43_21_02_00 --2lane//#//#0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,       0x00000007);//#0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00000013);//#0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

    //#stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0011AAc);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 1
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0021AAc);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 2
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0044AAc);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //#CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,      0x00000011);//#0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR            ,      0x00000000);//#0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR            ,      0x43211200);//#0x43_21_02_00 --2lane//#//#0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,       0x00000007);//#0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x00000013);//#0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

    //#stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0011AAc);//#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 1
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_1_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0021AAc);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_1_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

    //#stream 2
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
    csi_1_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0044AAc);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
    csi_1_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
    csi_1_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
    csi_1_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start
}
/*
*
*/
void csdn_opn8008_320x240_lane2_12bit(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x10);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x00013013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode


    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask




    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x00000013);//0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000010);//0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000001);//0x100,start
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x00000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x00000000);//0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x00000000);//0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x00000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x00000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x00000000);//0x128,FIFO monitor mode

}
/*
*
*/
void csdn_irs328c_224x172_lane2_12bit(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x00013013);//0x00000013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //stream 1
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00022AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //stream 2
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00042AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x21430200);//0x214302000x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x0001c01c);//0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000010);//0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x00000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x00000000);//0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x00000000);//0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x00000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x00000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x00000000);//0x128,FIFO monitor mode
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000001);//0x100,start

}
/*
*
*/
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_4lane_imx385_normal(void)
{
     //#--------------------(1920x1080-RAW12bit):
     //#--------------------CSI_0 channel-----------------------------------------------------------------------------------
     //#CDNS
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000011);//#0x004,softreset
     csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR         ,      0x00000000);//#0x004
     csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR             ,      0x43210400);//#0x43_21_02_00 --2lane##0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
     csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,        0x00000007);//#0x010,error bypass

    // printf("CSI_RX_STATIC_CFG_ADDR :%x\n",csi_host_RegRd(0xf, CSI_RX_STATIC_CFG_ADDR));
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR        ,      0x00000000);//#0x018,monitor,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,      0x00000000);//#0x01C,monitor,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR           ,      0x00000000);//#0x020,info,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR      ,      0x00000000);//#0x024,info,interrupt mask
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR          ,      0x00000000);//#0x028,error,interrupt,clear/read
     csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR     ,      0x00000000);//#0x02C,error,interrupt,mask

     csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,      0x0001f01f);//0x00000013 #0x040,dphy lane 0/1 and clock lane enable

     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,      0x00000000);//#0x04C,error,interrupt,status
     csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,      0x00000000);//#0x050,error,interrupt,mask

     //#stream 0
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     //printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
    // printf("CSI_RX_STREAM_CTRL_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_CTRL_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0012AAC);//0x0001AAC#0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)

    // printf("CSI_RX_STREAM_DATA_CFG_ADDR :%x\n",csi_host_RegRd(0x0, CSI_RX_STREAM_DATA_CFG_ADDR));
     csi_host_RegWr(0x0,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(0x0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(0x0,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(0x0,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(0x0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(0x0,CSI_RX_STREAM_CTRL_ADDR,              0x0000001);//#0x100,start

     //#stream 1
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0022AAC);//#0x108,VC=2'b01,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,              0x0000000);//#0x100,start

     //#stream 2
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000010);//#0x100,soft reset
     csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,          0x0042AAC);//#0x108,VC=2'b10,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
     csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR,               0x0000000);//#0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
     csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,      0x0000000);//#0x110,
     csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,             0x0000000);//#0x11c,counter of timer
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR,           0x0000000);//#0x120,counter of frame start/end for interrupt
     csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,          0x0000000);//#0x124,FCC enable frame counter capture
     csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,     0x0000000);//#0x128,FIFO monitor mode
     csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,              0x0000000);//#0x100,start
}
/*
*
*/
void csdn_imx385_1920x1080_lane2_12bit(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x00013013);//0x00000013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //stream 1
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(1,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00022AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(1,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(1,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(1,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(1,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(1,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(1,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //stream 2
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(2,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00042AAC);//0x0001AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(2,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(2,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(2,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(2,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(2,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(2,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x21430200);//0x214302000x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x0001c01c);//0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000010);//0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x00000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x00000000);//0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x00000000);//0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x00000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x00000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x00000000);//0x128,FIFO monitor mode
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000001);//0x100,start

}
/**
 * @brief 
 * 
 */
void csdn_opn8018_640x480_lane2_12bit(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x00013013);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x0012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start

    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_1 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_1_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_1_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x21430200);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_1_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x0001c01c);//0x040,dphy lane 0/1 and clock lane enable

    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_1_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000010);//0x100,soft reset
    csi_1_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x00000001);//0x100,start
    csi_1_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x00012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_1_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x00000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_1_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x00000000);//0x110,
    csi_1_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x00000000);//0x11c,counter of timer
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x00000000);//0x120,counter of frame start/end for interrupt
    csi_1_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x00000000);//0x124,FCC enable frame counter capture
    csi_1_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x00000000);//0x128,FIFO monitor mode

}
/**
 * @brief 
 * 
 */
void csdn_opn8018_640x480_lane4_12bit(void)
{
    //--------------------(1920x1080-RAW12bit):
    //--------------------CSI_0 channel-----------------------------------------------------------------------------------
    //CDNS
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000011);//0x004,softreset
    csi_host_RegWr(0xf, CSI_RX_SOFT_RESET_ADDR		  , 	   0x00000000);//0x004
    csi_host_RegWr(0xf, CSI_RX_STATIC_CFG_ADDR		  , 	   0x43210400);//0x43_21_02_00 --2lane////0x008,phy, 4alnes enable bit[15:12] reserved for Snoy_WDR
    csi_host_RegWr(0xf, CSI_RX_ERROR_BYPASS_CFG_ADDR    ,		0x00000007);//0x010,error bypass

    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_ADDR 	   ,	  0x00000000);//0x018,monitor,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_MONITOR_IRQS_MASK_ADDR   ,	  0x00000000);//0x01C,monitor,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_ADDR		   ,	  0x00000000);//0x020,info,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_INFO_IRQS_MASK_ADDR	   ,	  0x00000000);//0x024,info,interrupt mask
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_ADDR		   ,	  0x00000000);//0x028,error,interrupt,clear/read
    csi_host_RegWr(0xf, CSI_RX_ERROR_IRQS_MASK_ADDR	   ,	  0x00000000);//0x02C,error,interrupt,mask

    csi_host_RegWr(0xf, CSI_RX_DPHY_LANE_CONTROL_ADDR   ,	  0x0001f01f);//0x040,dphy lane 0/1 and clock lane enable

    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR ,	  0x00000000);//0x04C,error,interrupt,status
    csi_host_RegWr(0xf, CSI_RX_DPHY_ERR_IRQ_MASK_ADDR   ,	  0x00000000);//0x050,error,interrupt,mask

    //stream 0
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000010);//0x100,soft reset
    csi_host_RegWr(0,CSI_RX_STREAM_DATA_CFG_ADDR,		  0x0012AAC);//0x108,VC=2'b00,datatype:1E(YUV422);2A(RAW8);2B(RAW10);2C(RAW12)
    csi_host_RegWr(0,CSI_RX_STREAM_CFG_ADDR, 			  0x0000000);//0x10C,hsync_valid, 1 pixel/cycle;fifo mode_full line buffer
    csi_host_RegWr(0,CSI_RX_STREAM_MONITOR_CTRL_ADDR,	  0x0000000);//0x110,
    csi_host_RegWr(0,CSI_RX_STREAM_TIMER_ADDR,			  0x0000000);//0x11c,counter of timer
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CFG_ADDR, 		  0x0000000);//0x120,counter of frame start/end for interrupt
    csi_host_RegWr(0,CSI_RX_STREAM_FCC_CTRL_ADDR,		  0x0000000);//0x124,FCC enable frame counter capture
    csi_host_RegWr(0,CSI_RX_STREAM_FIFO_FILL_LVL_ADDR,	  0x0000000);//0x128,FIFO monitor mode
    csi_host_RegWr(0,CSI_RX_STREAM_CTRL_ADDR,			  0x0000001);//0x100,start
}
