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
#ifndef _MIPI_REG_DEF_H_
#define _MIPI_REG_DEF_H_

#include "video/video_subsystem_addr.h"

#define   CSI_HOST_BASE        (VI_BASE_ADDR + 0x0000) //#ch0
#define   CSI_HOST_END         (VI_BASE_ADDR + 0x03F8)
#define   VI_MIPI_DVP0_BASE    (VI_BASE_ADDR + 0x0400) //#ch1
#define   VI_MIPI_DVP0_END     (VI_BASE_ADDR + 0x04FC)
#define   VI_MIPI_DVP1_BASE    (VI_BASE_ADDR + 0x0500) //#ch2
#define   VI_MIPI_DVP1_END     (VI_BASE_ADDR + 0x05FC)
#define   VI_MIPI_DVP2_BASE    (VI_BASE_ADDR + 0x0600) //#ch3
#define   VI_MIPI_DVP2_END     (VI_BASE_ADDR + 0x06FC)
#define   VI_WRAP_BASE         (VI_BASE_ADDR + 0x0700) //#ch8
#define   VI_WRAP_END          (VI_BASE_ADDR + 0x07F8)

#define   CSI_1_HOST_BASE      (VI_BASE_ADDR + 0x0800 +  0x0000 ) //#ch4
#define   CSI_1_HOST_END       (VI_BASE_ADDR + 0x0800 +  0x03F8 )
#define   VI_MIPI_1_DVP0_BASE  (VI_BASE_ADDR + 0x0800 +  0x0400 ) //#ch5
#define   VI_MIPI_1_DVP0_END   (VI_BASE_ADDR + 0x0800 +  0x04FC )
#define   VI_MIPI_1_DVP1_BASE  (VI_BASE_ADDR + 0x0800 +  0x0500 ) //#ch6
#define   VI_MIPI_1_DVP1_END   (VI_BASE_ADDR + 0x0800 +  0x05FC )
#define   VI_MIPI_1_DVP2_BASE  (VI_BASE_ADDR + 0x0800 +  0x0600 ) //#ch7
#define   VI_MIPI_1_DVP2_END   (VI_BASE_ADDR + 0x0800 +  0x06FC )
#define   MIPI_DPHY_BASE       (VI_BASE_ADDR + 0x0800 +  0x0700 ) //#ch9
#define   MIPI_DPHY_END        (VI_BASE_ADDR + 0x0800 +  0x07F8 )


//# vi wrap regsiter offset addr
#define   CTRL_SWRST_OFFSET          0x0
#define   CTRL_MODE_OFFSET           0x1
#define   ISP_SEL_OFFSET             0x2
#define   CTRL_CLK_ENABLE_OFFSET     0x3
#define   DMA_ARB_MODE_OFFST         0x8
#define   DMA_WEIGHT_WR0_OFFST       0x9
#define   DMA_WEIGHT_WR1_OFFST       0xa
#define   DMA_WEIGHT_RD0_OFFST       0xb
#define   DMA_WEIGHT_RD1_OFFST       0xc

#define   DMA_PRIORITY_WR_OFFST      0xd
#define   DMA_PRIORITY_RD_OFFST      0xE
#define   DMA_ID_WR_OFFST            0xf
#define   DMA_ID_RD_OFFST            0x10


//# vi  regsiter offset addr
#define   CTAL_ENABLE_OFFSET           0x0
#define   CTAL_ENABLE_BIT_MASK        (0xFF <<8)
#define   CTAL_POL_OFFSET              0x0
#define   CTAL_POL_BIT_MASK           (0xFF <<16)
#define   CTAL_MODE_OFFSET             0x0
#define   CTAL_MODE_BIT_MASK          (0xFF <<24)

#define   CTAL_PIXEL_FORMAT_OFFSET     0x1
#define   CTAL_PIXEL_FORMAT_BIT_MASK   (0xFF <<0)
#define   CTAL_ctrl_win_OFFSET         0x1
#define   CTAL_ctrl_win_BIT_MASK       (0xFF <<8)

#define   crtl_vsync_width_OFFSET       0x2
#define   crtl_vsync_width_BIT_MASK    (0x3FFF <<0)
#define   crtl_hsync_width_OFFSET       0x2
#define   crtl_hsync_width_BIT_MASK    (0x3FFF <<16)

#define   crtl_v_size_total_OFFSET     0x03
#define   crtl_v_size_total_BIT_MASK   (0x3FFF <<0)
#define   crtl_h_size_total_OFFSET     0x03
#define   crtl_h_size_total_BIT_MASK   (0x3FFF <<16)

#define   crtl_v_size_active_OFFSET     0x04
#define   crtl_v_size_active_BIT_MASK   (0x3FFF <<0)
#define   crtl_h_size_active_OFFSET     0x04
#define   crtl_h_size_active_BIT_MASK   (0x3FFF <<16)

#define   crtl_v_start_OFFSET     0x05
#define   crtl_v_start_BIT_MASK   (0x3FFF <<0)
#define   crtl_h_start_OFFSET     0x05
#define   crtl_h_start_BIT_MASK   (0x3FFF <<16)


#define   ctrl_frame_base_addr0_y_OFFSET  0x08
#define   ctrl_frame_base_addr1_y_OFFSET  0x09
#define   ctrl_frame_base_addr0_uv_OFFSET  0x0a
#define   ctrl_frame_base_addr1_uv_OFFSET  0x0b

#define   ctrl_hstride_y_OFFSET             0x0c
#define   ctrl_hstride_y_BIT_MASK           (0x3FFF <<0)
#define   ctrl_hstride_uv_OFFSET            0x0c
#define   ctrl_hstride_uv_BIT_MASK          (0x3FFF <<16)


#define   ctrl_tpg_enable_OFFSET            0x10

#define   ctrl_tpg_mode_OFFSET              0x11
#define   ctrl_tpg_mode_BIT_MASK            (0x7<<0)
#define   ctrl_tpg_ratio_OFFSET             0x11
#define   ctrl_tpg_ratio_BIT_MASK           (0x3FFF <<16)


#define   crtl_tpg_vsync_width_OFFSET       0x12
#define   crtl_tpg_vsync_width_BIT_MASK    (0x3FFF <<0)
#define   crtl_tpg_hsync_width_OFFSET       0x12
#define   crtl_tpg_hsync_width_BIT_MASK    (0x3FFF <<16)

#define   crtl_tpg_v_size_total_OFFSET     0x13
#define   crtl_tpg_v_size_total_BIT_MASK   (0x3FFF <<0)
#define   crtl_tpg_h_size_total_OFFSET     0x13
#define   crtl_tpg_h_size_total_BIT_MASK   (0x3FFF <<16)

#define   crtl_tpg_v_size_active_OFFSET     0x14
#define   crtl_tpg_v_size_active_BIT_MASK   (0x3FFF <<0)
#define   crtl_tpg_h_size_active_OFFSET     0x14
#define   crtl_tpg_h_size_active_BIT_MASK   (0x3FFF <<16)

#define   crtl_tpg_v_start_OFFSET     0x15
#define   crtl_tpg_v_start_BIT_MASK   (0x3FFF <<0)
#define   crtl_tpg_h_start_OFFSET     0x15
#define   crtl_tpg_h_start_BIT_MASK   (0x3FFF <<16)

#define   ctrl_tpg_frame_base_addr0_OFFSET  0x16
#define   ctrl_tpg_frame_base_addr1_OFFSET  0x17

#define   ctrl_tpg_hstride_OFFSET    0x18

#define   ctrl_dma_mode_OFFSET       0x1b

//# address define
//#-----------------------video_in_wrap---------------------------
#define   VI_WRAP_ADDR_HREG00     0x00
#define   VI_WRAP_ADDR_HREG01     0x01
#define   VI_WRAP_ADDR_HREG02     0x02
#define   VI_WRAP_ADDR_HREG03     0x03
#define   VI_WRAP_ADDR_HREG04     0x04
#define   VI_WRAP_ADDR_HREG05     0x05
#define   VI_WRAP_ADDR_HREG06     0x06
#define   VI_WRAP_ADDR_HREG07     0x07
#define   VI_WRAP_ADDR_HREG08     0x08
#define   VI_WRAP_ADDR_HREG09     0x09
#define   VI_WRAP_ADDR_HREG0A     0x0A
#define   VI_WRAP_ADDR_HREG0B     0x0B
#define   VI_WRAP_ADDR_HREG0C     0x0C
#define   VI_WRAP_ADDR_HREG0D     0x0D
#define   VI_WRAP_ADDR_HREG0E     0x0E
#define   VI_WRAP_ADDR_HREG0F     0x0F

#define   VI_WRAP_ADDR_HREG10      0x10
#define   VI_WRAP_ADDR_HREG11      0x11
#define   VI_WRAP_ADDR_HREG12      0x12
#define   VI_WRAP_ADDR_HREG13      0x13
#define   VI_WRAP_ADDR_HREG14      0x14
#define   VI_WRAP_ADDR_HREG15      0x15
#define   VI_WRAP_ADDR_HREG16      0x16
#define   VI_WRAP_ADDR_HREG17      0x17
#define   VI_WRAP_ADDR_HREG18      0x18
#define   VI_WRAP_ADDR_HREG19      0x19
#define   VI_WRAP_ADDR_HREG1A      0x1A
#define   VI_WRAP_ADDR_HREG1B      0x1B
#define   VI_WRAP_ADDR_HREG1C      0x1C
#define   VI_WRAP_ADDR_HREG1D      0x1D
#define   VI_WRAP_ADDR_HREG1E      0x1E
#define   VI_WRAP_ADDR_HREG1F      0x1F

#define   VI_WRAP_ADDR_HREG20      0x20
#define   VI_WRAP_ADDR_HREG21      0x21
#define   VI_WRAP_ADDR_HREG22      0x22
#define   VI_WRAP_ADDR_HREG23      0x23
#define   VI_WRAP_ADDR_HREG30      0x30
#define   VI_WRAP_ADDR_HREG31      0x31
#define   VI_WRAP_ADDR_HREG32      0x32
#define   VI_WRAP_ADDR_HREG33      0x33

//# default value define
//#------------------------
#define   VI_WRAP_DEFAULT_HREG00    0x0
#define   VI_WRAP_DEFAULT_HREG01    0x0
#define   VI_WRAP_DEFAULT_HREG02    0x76543210
#define   VI_WRAP_DEFAULT_HREG03    0x0
#define   VI_WRAP_DEFAULT_HREG04    0x0
#define   VI_WRAP_DEFAULT_HREG05    0x0
#define   VI_WRAP_DEFAULT_HREG06    0x0
#define   VI_WRAP_DEFAULT_HREG07    0x0

#define   VI_WRAP_DEFAULT_HREG08    0x0
#define   VI_WRAP_DEFAULT_HREG09    0x01010101
#define   VI_WRAP_DEFAULT_HREG0A    0x01010101
#define   VI_WRAP_DEFAULT_HREG0B    0x01234567
#define   VI_WRAP_DEFAULT_HREG0C    0x01234567
#define   VI_WRAP_DEFAULT_HREG0D    0x01234567
#define   VI_WRAP_DEFAULT_HREG0E    0x01234567
#define   VI_WRAP_DEFAULT_HREG0F    0x0
#define   VI_WRAP_DEFAULT_HREG10    0x0
#define   VI_WRAP_DEFAULT_HREG11    0x0
#define   VI_WRAP_DEFAULT_HREG12    0x0
#define   VI_WRAP_DEFAULT_HREG13    0x0
#define   VI_WRAP_DEFAULT_HREG14    0x0
#define   VI_WRAP_DEFAULT_HREG15    0x0
#define   VI_WRAP_DEFAULT_HREG16    0x0
#define   VI_WRAP_DEFAULT_HREG17    0x0
#define   VI_WRAP_DEFAULT_HREG18    0x0
#define   VI_WRAP_DEFAULT_HREG19    0x0
#define   VI_WRAP_DEFAULT_HREG1A    0x0
#define   VI_WRAP_DEFAULT_HREG1B    0x0
#define   VI_WRAP_DEFAULT_HREG1C    0x0
#define   VI_WRAP_DEFAULT_HREG1D    0x0
#define   VI_WRAP_DEFAULT_HREG1E    0x0
#define   VI_WRAP_DEFAULT_HREG1F    0x0

//#----------------- word address [--:2]
//#WIN/EMB(offset=0x00) ,RW
#define   VI_ADDR_HREG00         0x00
#define   VI_ADDR_HREG01         0x01
#define   VI_ADDR_HREG02         0x02
#define   VI_ADDR_HREG03         0x03
#define   VI_ADDR_HREG04         0x04
#define   VI_ADDR_HREG05         0x05
#define   VI_ADDR_HREG06         0x06
#define   VI_ADDR_HREG07         0x07
#define   VI_ADDR_HREG08         0x08
#define   VI_ADDR_HREG09         0x09
#define   VI_ADDR_HREG0A         0x0A
#define   VI_ADDR_HREG0B         0x0B
#define   VI_ADDR_HREG0C         0x0C
#define   VI_ADDR_HREG0D         0x0D
#define   VI_ADDR_HREG0E         0x0E
#define   VI_ADDR_HREG0F         0x0F
//#TPG (offset0x10) ,RW
#define   VI_ADDR_HREG10           0x10
#define   VI_ADDR_HREG11           0x11
#define   VI_ADDR_HREG12           0x12
#define   VI_ADDR_HREG13           0x13
#define   VI_ADDR_HREG14           0x14
#define   VI_ADDR_HREG15           0x15
#define   VI_ADDR_HREG16           0x16
#define   VI_ADDR_HREG17           0x17
#define   VI_ADDR_HREG18           0x18
#define   VI_ADDR_HREG19           0x19
#define   VI_ADDR_HREG1A           0x1A
#define   VI_ADDR_HREG1B           0x1B
#define   VI_ADDR_HREG1C           0x1C
#define   VI_ADDR_HREG1D           0x1D
#define   VI_ADDR_HREG1E           0x1E
#define   VI_ADDR_HREG1F           0x1F
//#RO/Function (offset=0x20)
#define   VI_ADDR_HREG20           0x20
#define   VI_ADDR_HREG21           0x21
#define   VI_ADDR_HREG22           0x22
#define   VI_ADDR_HREG23           0x23
#define   VI_ADDR_HREG24           0x24
#define   VI_ADDR_HREG25           0x25
#define   VI_ADDR_HREG26           0x26
#define   VI_ADDR_HREG27           0x27
#define   VI_ADDR_HREG28           0x28
#define   VI_ADDR_HREG29           0x29
#define   VI_ADDR_HREG2A           0x2A
#define   VI_ADDR_HREG2B           0x2B
#define   VI_ADDR_HREG2C           0x2C
#define   VI_ADDR_HREG2D           0x2D
#define   VI_ADDR_HREG2E           0x2E
#define   VI_ADDR_HREG2F           0x2F
//#RO/Debug (offset=0x30)
#define   VI_ADDR_HREG30          0x30
#define   VI_ADDR_HREG31          0x31
#define   VI_ADDR_HREG32          0x32
#define   VI_ADDR_HREG33          0x33
#define   VI_ADDR_HREG34          0x34
#define   VI_ADDR_HREG35          0x35
#define   VI_ADDR_HREG36          0x36
#define   VI_ADDR_HREG37          0x37
#define   VI_ADDR_HREG38          0x38
#define   VI_ADDR_HREG39          0x39
#define   VI_ADDR_HREG3A          0x3A
#define   VI_ADDR_HREG3B          0x3B
#define   VI_ADDR_HREG3C          0x3C
#define   VI_ADDR_HREG3D          0x3D
#define   VI_ADDR_HREG3E          0x3E
#define   VI_ADDR_HREG3F          0x3F

//# default value define
//#------------------------
//#WIN/EMB(offset=0x00) ,RW
#define   VI_DEFAULT_HREG00     0x0
#define   VI_DEFAULT_HREG01     0x0FFF0000
#define   VI_DEFAULT_HREG02     0x0
#define   VI_DEFAULT_HREG03     0x0
#define   VI_DEFAULT_HREG04     0x0
#define   VI_DEFAULT_HREG05     0x0
#define   VI_DEFAULT_HREG06     0x0
#define   VI_DEFAULT_HREG07     0x0
#define   VI_DEFAULT_HREG08     0x0
#define   VI_DEFAULT_HREG09     0x0
#define   VI_DEFAULT_HREG0A     0x0
#define   VI_DEFAULT_HREG0B     0x0
#define   VI_DEFAULT_HREG0C     0x0
#define   VI_DEFAULT_HREG0D     0x0
#define   VI_DEFAULT_HREG0E     0x0
#define   VI_DEFAULT_HREG0F     0x0
//#TPG (offset=0x10)
#define   VI_DEFAULT_HREG10     0x0
#define   VI_DEFAULT_HREG11     0x00000102  //#frame ratio of TPG
#define   VI_DEFAULT_HREG12     0x0
#define   VI_DEFAULT_HREG13     0x0
#define   VI_DEFAULT_HREG14     0x0
#define   VI_DEFAULT_HREG15     0x0
#define   VI_DEFAULT_HREG16     0x0
#define   VI_DEFAULT_HREG17     0x0
#define   VI_DEFAULT_HREG18     0x0
#define   VI_DEFAULT_HREG19     0x0
#define   VI_DEFAULT_HREG1A     0x0
#define   VI_DEFAULT_HREG1B     0x00000111
#define   VI_DEFAULT_HREG1C     0x01010101   //#error unit and threshold
#define   VI_DEFAULT_HREG1D     0x0
#define   VI_DEFAULT_HREG1E     0x0
#define   VI_DEFAULT_HREG1F     0x0



 //#============================================================================================================================
 // #  NOT USER DEFINABLE - do not change any thing bellow this point
 // #============================================================================================================================
 // # DEVICE CONFIGURATION STATUS
#define   CSI_RX_DEVICE_CONFIG_ADDR            0x000

//  # CONTROL
#define   CSI_RX_SOFT_RESET_ADDR               0x004
#define   CSI_RX_STATIC_CFG_ADDR               0x008
#define   CSI_RX_ERROR_BYPASS_CFG_ADDR         0x010

//  #INTERRUPTS
#define   CSI_RX_MONITOR_IRQS_ADDR             0x018
#define   CSI_RX_MONITOR_IRQS_MASK_ADDR        0x01C
#define   CSI_RX_INFO_IRQS_ADDR                0x020
#define   CSI_RX_INFO_IRQS_MASK_ADDR           0x024
#define   CSI_RX_ERROR_IRQS_ADDR               0x028
#define   CSI_RX_ERROR_IRQS_MASK_ADDR          0x02C

//  # DPHY
#define   CSI_RX_DPHY_LANE_CONTROL_ADDR        0x040
#define   CSI_RX_DPHY_LANE_CONFIG_ADDR         0x044
#define   CSI_RX_DPHY_STATUS_ADDR              0x048
#define   CSI_RX_DPHY_ERR_STATUS_IRQ_ADDR      0x04C
#define   CSI_RX_DPHY_ERR_IRQ_MASK_ADDR        0x050
#define   CSI_RX_DPHY_TEST_ADDR                0x054

 // # DEBUG
#define   CSI_RX_INTEGRATION_DEBUG_ADDR        0x060
#define   CSI_RX_ERROR_DEBUG_ADDR              0x074
#define   CSI_RX_TEST_GENERIC_ADDR             0x080

 // # ID_REG : Product ID & Version Numbers (hard-coded)
#define   CSI_RX_IDREG_ADDR                    0xFFC
#define   CSI_RX_IDREG_PRODUCT                 0x5022
#define   CSI_RX_IDREG_VERSION                 0x0200

//  # STREAM BASE Addresses (paddr[11:8]
#define   CSI_RX_STREAM0_BASE_ADDR            0x1
#define   CSI_RX_STREAM1_BASE_ADDR            0x2
#define   CSI_RX_STREAM2_BASE_ADDR            0x3
#define   CSI_RX_STREAM3_BASE_ADDR            0x4

//  # PER STREAM Addresses (paddr[7:0]
#define   CSI_RX_STREAM_CTRL_ADDR             0x00
#define   CSI_RX_STREAM_STATUS_ADDR           0x04
#define   CSI_RX_STREAM_DATA_CFG_ADDR         0x08
#define   CSI_RX_STREAM_CFG_ADDR              0x0C
#define   CSI_RX_STREAM_MONITOR_CTRL_ADDR     0x10
#define   CSI_RX_STREAM_MONITOR_FRAME_ADDR    0x14
#define   CSI_RX_STREAM_MONITOR_LB_ADDR       0x18
#define   CSI_RX_STREAM_TIMER_ADDR            0x1C
#define   CSI_RX_STREAM_FCC_CFG_ADDR          0x20
#define   CSI_RX_STREAM_FCC_CTRL_ADDR         0x24
#define   CSI_RX_STREAM_FIFO_FILL_LVL_ADDR    0x28

//  # ASF base address (paddr[11:8])
#define   CSI_RX_ASF_BASE_ADDR                0x900
//
void csi_host_RegWr(int stream_id,int addr,int data);
int  csi_host_RegRd(int stream_id,int addr);
void csi_1_host_RegWr(int stream_id,int addr,int data);
int  csi_1_host_RegRd(int stream_id,int addr);

#endif /*_MIPI_REG_DEF_H_*/
