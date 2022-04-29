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
/******************************************************************************
  File Name     : dev_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _DEF_DEV_REG_H_
#define _DEF_DEV_REG_H_

#include "video_subsystem.h"

#define   EXTER_CTL_START  ISP_EXTCTRL_BASE_ADDR
#define   SENSOR_ADV7511CTRL_BASEADDR  ISP_DEV_BASE_ADDR

#define    SENSOR_AUTO_OP_OFFSET      0x0
#define    SENSOR_MANU_OP_OFFSET      0x1
#define    SENSOR_UPDATE_REQ_OFFSET   0x2
#define    SENSOR_READ_REQ_OFFSET     0x3
#define    SENSOR_LATCH_OFFSET        0x4
#define    SENSOR_ADDR_OFFSET         0x5
#define    SENSOR_READ_DATA_OFFSET    0x6

#define   HDMI_UPDATE_REQ_OFFSET      0x7
#define   HDMI_READ_REQ_OFFSET        0x8
#define   HDMI_LATCH_OFFSET           0x9
#define   HDMI_ADDR_DATA_OFFSET       0xA
#define   HDMI_READ_DATA_OFFSET       0xB

#define   BYTE_MODE_CONFIG_OFFSET      31
#define   SENSOR_DEV_ADDR_OFFSET       32
#define   I2C_CLK_PRIOD_OFFSET         33
#define   I2C_SEL_OFFSET               34


#define   START_CONFIG_OFFSET          40
#define   HDMI_CONFIG_DONE_OFFSET      50
#endif /* _DEF_DEV_REG_H_ */
