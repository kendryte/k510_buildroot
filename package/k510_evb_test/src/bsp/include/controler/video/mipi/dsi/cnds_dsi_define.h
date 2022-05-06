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
/*
 * dsi_define.h
 *
 *  Created on: Dec 14, 2019
 *      Author: Administrator
 */

#ifndef CNDS_DSI_DEFINE_H_
#define CNDS_DSI_DEFINE_H_
//#include <VIDEO_SUBSYSTEM.h>
#include "video/video_subsystem_addr.h"
#define   CNDS_DSI_REG_START                CNDS_DSI_BASE_ADDR

#define   IP_CONF_OFFSET                    0x0   //0x148490D0 IP Configuration for Controller
#define   MCTL_MAIN_DATA_CTL_OFFSET         0x4   //0x00000000 Main Control - main control setting for datapath
#define   MCTL_MAIN_PHY_CTL_OFFSET          0x8   //0x00000000 Main control setting for the physical lanes and drive the static signals for DPHY clock lane
#define   MCTL_MAIN_EN_OFFSET               0xc   //0x00000000 Control start/stop of the DSI link
#define   MCTL_DPHY_CFG0_OFFSET             0x10  //0x00000600 DPHY Power and Reset Control
#define   MCTL_DPHY_TIMEOUT1_OFFSET         0x14  //0x00000000 Main DPHY time-out settings. To better understand the way this register is
                                                  //           used, please refer to Section : DSI checks (DC) - the counters are based on
                                                   //           tx_byte_hs_clk and NOT on sys_clk
#define   MCTL_DPHY_TIMEOUT2_OFFSET         0x18  //0x00000000 To better understand the way this register is used, please refer to Section : DSI
                                         //   checks (DC) - the counters are on tx_byte_hs_clk and not on sys_clk
#define   MCTL_ULPOUT_TIME_OFFSET           0x1c  //0x00000000 Specify time to leave ULP mode. The time-out is reached when the ulpout
                                          //   counter reaches 1000x xxx_ulpout_time and is based upon the system clock
#define   MCTL_3DVIDEO_CTL_OFFSET           0x20  //0x00000010 3D Video mode stream control
#define   MCTL_MAIN_STS_OFFSET              0x24  //0x00000000 Status of the DSI link
#define   MCTL_DPHY_ERR_OFFSET              0x28  //0x00000000 Errors reported from DPHY lanes - See description in DPHY inputs and
                                         //    outputs
#define   MCTL_LANE_STS_OFFSET              0x2c  //0x00000000 DPHY Lane and PLL status information
#define   DSC_MODE_CTL_OFFSET               0x30  //0x00000000 DSC Mode Control register
#define   DSC_CMD_SEND_OFFSET               0x34  //0x00000000 DSC Command Control register. Write one to perform PPS set transfer or
                                         //   Execute Queue commands
#define   DSC_PPS_WRDAT_OFFSET              0x38  //0x00000000 DSC PPS Write data to outgoing FIFO Buffer, byte 0 to 3; applicable to either
                                            //  Write or Read commands. Note that any writes to this register that exceed the
                                            //  programmed command payload size or the configured FIFO depth (whichever
                                            //  is smaller) will be ignored. Conversely, if the writes to this register are less than
                                            //  the programmed command payload size when the instruction to send theMIPI DSI v1.3.1
   										          //  Host Controller User Guide
                                            //  Doc No: IPG-DOC54-USR Rev 1.04 © 2018 Cadence Design Systems, Inc. Confidential Page 120
                                            //  payload is given, the command payload will contain data from the previous
                                            //  contents of the FIFO for all unwritten bytes, and will therefore be corrupt.
#define   DSC_MODE_STS_OFFSET               0x3c  //0x00000000 DSC Event Status Register
#define   MCTL_DPHY_SKEWCAL_TIMEOUT_OFFSET  0x40  //0x00000000 Used in conjunction with HS_SKEWCAL_TIMEOUT_EN from
                                            //   MCTL_MAIN_PHY_CTL to control periodic skew calibration
#define   CMD_MODE_CTL_OFFSET                0x70  //0x00000000 Command mode control
#define   CMD_MODE_CTL2_OFFSET               0x74  //0x007FF800 Command mode control
#define   CMD_MODE_STS_OFFSET                0x78  //0x00000000 Command Mode status
#define   DIRECT_CMD_SEND_OFFSET             0x80  //0x00000000 Direct_cmd_send is not a real register. When this address is written (whatever
                                            //  its value is), it signals to the link that a direct command has to be sent. It is
                                            //  then a write only register.No specific mechanism is implemented to prevent the
                                            //  application sending two direct commands back-to-back. It is then applications
                                            //  responsibility to verify the completion of a first direct command before starting
                                            //  another direct command.Interlacing of command or video with direct command
                                            //  is managed by the DSI link using the different arbiters (see Command and
                                            //  register arbiter (CRA) and Video/command arbiter (VCA))
#define   DIRECT_CMD_MAIN_SETTINGS_OFFSET    0x84  //0x00000000 Main control of the Direct Command function.
#define   DIRECT_CMD_STS_OFFSET              0x88  //0x00000000 Direct Command Status: To ensure that the observed status bits are coherent
                                            //   and applicable to the last command message sent, it is recommended to clear
                                            //   this register between accesses by writing to direct_cmd_clr, otherwise the
                                            //   status of the different commands is logically ORed, making it difficult to
                                            //   differentiate between the status of each message.
#define   DIRECT_CMD_RD_INIT_OFFSET          0x8c  //0x00000000 This register is not a real register - when written it stops the read command
                                            //   process by emptying the FIFO and by stopping the reception of the data (RP
                                            //   does not consider the data that it receives and the system waits for the D-PHY
                                            //   to return to Tx STOP state).
#define   DIRECT_CMD_WRDAT_OFFSET            0x90  //0x00000000 Write data to outgoing Direct Command FIFO, byte 0 to 3; applicable to either
                                            //  Write or Read commands. Note that any writes to this register that exceed the
                                            //  programmed command payload size or the configured FIFO depth (whichever
                                            //  is smaller) will be ignored. Conversely, if the writes to this register are less than
                                            //  the programmed command payload size when the instruction to send the
                                            //  payload is given, the command payload will contain data from the previous
                                            //  contents of the FIFO for all unwritten bytes, and will therefore be corrupt. Note
                                            //  also that values written to the FIFO which are intended for transmission of
                                            //  single parameter write transaction must set the MS bytes to zero to comply
                                            //  with DSI standard requirements.
#define   DIRECT_CMD_FIFO_RST_OFFSET        0x94  //0x00000000 Reset the write FIFO. This register is not a real register - when written it reset
                                           //   the FIFO pointer
#define   DIRECT_CMD_RDDAT_OFFSET           0xa0  //0x00000000 Data from incoming Direct Command receive path, byte 0 to 3. NOTE: SW
                                            //   must mask any bytes which are in excess of the actual message size (e.g. for
                                            //   a 2-byte message payload, take data from bytes [1:0] and mask off bytes [3:2])MIPI DSI v1.3.1 Host Controller User Guide
                                            //   Doc No: IPG-DOC54-USR Rev 1.04
                                            //   © 2018 Cadence Design Systems, Inc. Confidential Page 121
#define   DIRECT_CMD_RD_PROPERTY_OFFSET     0xa4  //0x00000000 read command characteristics
#define   DIRECT_CMD_RD_STS_OFFSET          0xa8  //0x00000000 Status of the read command received. It is recommended to clear
                                           //   direct_cmd_sts between two direct commands (at least between 2 read) in
                                           //   order to see coherent status
#define   VID_MAIN_CTL_OFFSET              0xb0   //0x80000000 Video mode main control
#define   VID_VSIZE1_OFFSET                0xb4   //0x00000000 Image vertical Sync and Blanking settings
#define   VID_VSIZE2_OFFSET                0xb8   //0x00000000 Image vertical active line setting
#define   VID_HSIZE1_OFFSET                0xc0   //0x00000000 Image horizontal sync and Blanking setting
#define   VID_HSIZE2_OFFSET                0xc4   //0x00000000 Image horizontal byte size setting
#define   VID_BLKSIZE1_OFFSET              0xcc   //0x00000000 blanking packet size
#define   VID_BLKSIZE2_OFFSET              0xd0   //0x00000000 Pulse Mode blanking packet size
#define   VID_PCK_TIME_OFFSET              0xd8   //0x00000000 Packet duration
#define   VID_DPHY_TIME_OFFSET             0xdc   //0x00000000 Time of D-PHY behavior for wakeup time and Line duration for LP during
                                                  //    horozontal blanking lines
#define   VID_ERR_COLOR1_OFFSET            0xe0   //0x00000000 error color (green and red)
#define   VID_ERR_COLOR2_OFFSET            0xe4   //0x00000000 error color (blue and padding)
#define   VID_VPOS_OFFSET                  0xe8   //0x00000000 vertical position
#define   VID_HPOS_OFFSET                  0xec   //0x00000000 Horizontal Position
#define   VID_MODE_STS_OFFSET              0xf0   //0x00000000 Video mode status and error reporting
#define   VID_VCA_SETTING1_OFFSET          0xf4   //0x00000000 VCA control register 1
#define   VID_VCA_SETTING2_OFFSET          0xf8   //0x00000000 VCA control register 2
#define   TVG_CTL_OFFSET                   0xfc   //0x00000000 Main control of the TVGMIPI DSI v1.3.1 Host Controller User Guide
                                                  //    Doc No: IPG-DOC54-USR Rev 1.04
                                                  //  © 2018 Cadence Design Systems, Inc. Confidential Page 122
#define   TVG_IMG_SIZE_OFFSET              0x100  //0x00000000 TVG Generated image size
#define   TVG_COLOR1_OFFSET                0x104  //0x00000000 Color 1 of the dummy frame G, R
#define   TVG_COLOR1_BIS_OFFSET            0x108  //0x00000000 Color 1 of the dummy frame , B
#define   TVG_COLOR2_OFFSET                0x10c  //0x00000000 Color 2 of the dummy frame, G, R
#define   TVG_COLOR2_BIS_OFFSET            0x110  //0x00000000 Color 2 of the dummy frame, B
#define   TVG_STS_OFFSET                   0x114  //0x00000000 TVG status register
#define   MCTL_MAIN_STS_CTL_OFFSET         0x130  //0x00000000 Controls the enabling and edge detection of main ctrl status bits EDGE = 0
                                                  //   captures the rising edge of the event, EDGE= 1 captures falling edge.
#define   CMD_MODE_STS_CTL_OFFSET           0x134 //0x00000000 Controls the enabling and edge detection of command status bits EDGE = 0
                                                 //   captures the rising edge of the event, EDGE= 1 captures falling edge.
#define   DIRECT_CMD_STS_CTL_OFFSET         0x138 //0x00000000 Controls the enabling and edge detection of Direct Command status bits
#define   DIRECT_CMD_RD_STS_CTL_OFFSET      0x13c //0x00000000 Controls the enabling and edge detection of read commands error
#define   VID_MODE_STS_CTL_OFFSET           0x140 //0x00000000 Control the enabling and edge detection of VSG status bits
#define   TVG_STS_CTL_OFFSET                0x144 //0x00000000 Control the enabling and edge detection of TVG status bits
#define   MCTL_DPHY_ERR_CTL1_OFFSET         0x148 //0x00000000 Controls the enabling and edge detection of the DPHY errors
#define   MCTL_DPHY_ERR_CTL2_OFFSET         0x14c //0x00000000 Controls he enabling and edge detection of the DPHY errors
#define   MCTL_MAIN_STS_CLR_OFFSET          0x150 //0x00000000 Main control status register clear function. These bits are spread across
                                                 //    different register banks. The exact use of the set and reset is described in the
                                                 //    section : Error and status bits. Write '1' to clear
#define   CMD_MODE_STS_CLR_OFFSET           0x154 //0x00000000 Command status register clear function. Write '1' to clear
#define   DIRECT_CMD_STS_CLR_OFFSET         0x158 //0x00000000 Direct command status register clear function. Write '1' to clear
#define   DIRECT_CMD_RD_STS_CLR_OFFSET      0x15c //0x00000000 Direct command read status register clear function. Write '1' to clear
#define   VID_MODE_STS_CLR_OFFSET           0x160 //0x00000000 VSG status register clear functionMIPI DSI v1.3.1 Host Controller User Guide
                                                 //    Doc No: IPG-DOC54-USR Rev 1.04
                                                 //    © 2018 Cadence Design Systems, Inc. Confidential Page 123
#define   TG_STS_CLR_OFFSET                 0x164 //0x00000000 TVG status register clear function. Write '1' to clear
#define   MCTL_DPHY_ERR_CLR_OFFSET          0x168 //0x00000000 D_PHY lanes output register clear function. Write '1' to clear
#define   MCTL_MAIN_STS_FLAG_OFFSET         0x170 //0x00000000 Main control status Flag registers. The use of these registers is related to
                                                  //    status and error bits management (and interrupt too). These bits are spread
                                                  //    across different register banks. The exact use of the flag bit is described in the
                                                  //    section : Error and status bits.
#define   CMD_MODE_STS_FLAG_OFFSET          0x174 //0x00000000 Command Mode status
#define   DIRECT_CMD_STS_FLAG_OFFSET        0x178 //0x00000000 Direct command mode status
#define   DIRECT_CMD_RD_STS_FLAG_OFFSET     0x17c //0x00000000 Direct command read status bits
#define   VID_MODE_STS_FLAG_OFFSET          0x180 //0x00000000 Video Mode status flag
#define   TG_STS_FLAG_OFFSET                0x184 //0x00000000 TVG status Flags
#define   MCTL_DPHY_ERR_FLAG_OFFSET         0x188 //0x00000000 Errors output from D_PHY lanes - flags error bit
#define   DPI_IRQ_EN_OFFSET                 0x1a0 //0x00000000 DPI interrupt enable
#define   DPI_IRQ_CLR_OFFSET                0x1a4 //0x00000000 DPI interrupt clear register
#define   DPI_IRQ_STS_OFFSET                0x1a8 //0x00000000 DPI interrupt status
#define   DPI_CFG_OFFSET                    0x1ac //0x00800000 DPI interface configuration information
#define   TEST_GENERIC_OFFSET               0x1f0 //0x00000000 Generic test control and status register
#define   ID_REG_OFFSET                     0x1fc //0xCADD5131 ID register for Controller
#define   ASF_INT_STATUS_OFFSET             0x200 //0x00000000 ASF Interrupt Status Register. This register indicates the source of ASF
                                           //   interrupts. The corresponding bit in the mask register must be clear for a bit to
                                           //   be set. If any bit is set in this register the asf_int_fatal or asf_int_nonfatal signal
                                           //   will be asserted. Writing to either raw or masked status registers, clear both
                                           //   registers. For test purposes, trigger signal interrupt event by writing to the ASF
                                           //   interrupt status test register.
#define   ASF_INT_RAW_STATUS_OFFSET         0x204 //0x00000000 ASF Interrupt Raw Status Register. A bit set in this raw register indicates a
                                           //   source of ASF fault in the corresponding feature. Writing to either raw or
                                           //   masked status registers, clear both registers. For test purposes, trigger signal
                                           //   interrupt event by writing to the ASF interrupt status test register.MIPI DSI v1.3.1 Host Controller User Guide
                                           //   Doc No: IPG-DOC54-USR Rev 1.04
                                           //   © 2018 Cadence Design Systems, Inc. Confidential Page 124
#define   ASF_INT_MASK_OFFSET               0x208 //0x0000007F The ASF interrupt mask register indicating which interrupt bits in the ASF
                                           //   interrupt status register are masked. All bits are set at reset. Clear the
                                           //   individual bit to enable the corresponding interrupt.
#define   ASF_INT_TEST_OFFSET               0x20c //0x00000000 The ASF interrupt test register emulate hardware even. Write one to individual
                                            //   bit to trigger single event in (masked and raw) status registers according to
                                            //   mask and will generate interrupt accordingly.
#define   ASF_FATAL_NONFATAL_SELECT_OFFSET  0x210 //0x0000007F The fatal or non-fatal interrupt register selects whether a fatal (asf_int_fatal) or
                                            //   non-fatal (asf_int_nonfatal) interrupt is triggered. If the bit of the event will be
                                            //   set to one then fatal interrupt (asf_int_fatal) will be triggered. Otherwise the
                                            //   non-fatal interrupt (asf_int_nonfatal) will be triggered.
#define   ASF_SRAM_CORR_FAULT_STATUS_OFFSET  0x220   //0x00000000 Status register for SRAM correctable fault. These fields are updated whenever
                                               //  asf_sram_corr_fault input is active.
#define   ASF_SRAM_UNCORR_FAULT_STATUS_OFFSET  0x224 //0x00000000 Status register for SRAM uncorrectable fault. These fields are updated
                                               //  whenever asf_sram_uncorr_fault input is active.
#define   ASF_SRAM_FAULT_STATS_OFFSET      0x228     //0x00000000 Statistics register for SRAM faults. Note that this register clears when software
                                               //  writes to any field.
#define   ASF_TRANS_TO_CTRL_OFFSET            0x230  //0x00000000 Control register to configure the ASF transaction timeout monitors.
#define   ASF_TRANS_TO_FAULT_MASK_OFFSET      0x234  //0x0000000F Control register to mask out ASF transaction timeout faults from triggering
                                               //  interrupts. On reset, all bits are set to mask out all sources. Clear the
                                               //  corresponding bit to enable the interrupt source. The width of this field is
                                               //  parameterisable and the bit definitions are implementation specific.
#define   ASF_TRANS_TO_FAULT_STATUS_OFFSET  0x238   //0x00000000 Status register for transaction timeouts fault. If a fault occurs the revelant
                                               //  status bit will be set to 1. Each bit can be cleared by software writing 1 to each
                                               //  bit.
#define   ASF_PROTOCOL_FAULT_MASK_OFFSET      0x240  //0x0000003F Control register to mask out ASF Protocol faults from triggering interrupts. On
                                               //  reset, all bits are set to mask out all sources. Clear the corresponding bit to
                                               //  enable the interrupt source. The width of this field is parameterisable and the
                                               //  bit definitions are implementation specific.
#define   ASF_PROTOCOL_FAULT_STATUS_OFFSET    0x244  //0x00000000    Status register for protocol faults. If a fault occurs the revelant stat

#endif /* CNDS_DSI_DEFINE_H_ */
