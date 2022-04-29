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
 * mipi_csi2.h
 *
 * k510 ISP - Generic video node
 *
 * Contacts: zhudalei <zhudalei@canaan-creative.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _MIPI_CSI2_H_
#define _MIPI_CSI2_H_ 

#include "isp_com.h"
#include "isp.h"

/* This is not an exhaustive list */
enum isp_csi2_pix_formats {
	CSI2_PIX_FMT_OTHERS = 0,
	CSI2_PIX_FMT_YUV422_8BIT = 0x1e,
	CSI2_PIX_FMT_YUV422_8BIT_VP = 0x9e,
	CSI2_PIX_FMT_RAW10_EXP16 = 0xab,
	CSI2_PIX_FMT_RAW10_EXP16_VP = 0x12f,
	CSI2_PIX_FMT_RAW8 = 0x2a,
	CSI2_PIX_FMT_RAW8_DPCM10_EXP16 = 0x2aa,
	CSI2_PIX_FMT_RAW8_DPCM10_VP = 0x32a,
	CSI2_PIX_FMT_RAW8_VP = 0x12a,
	CSI2_USERDEF_8BIT_DATA1_DPCM10_VP = 0x340,
	CSI2_USERDEF_8BIT_DATA1_DPCM10 = 0x2c0,
	CSI2_USERDEF_8BIT_DATA1 = 0x40,
};

enum isp_csi2_irqevents {
	OCP_ERR_IRQ = 0x4000,
	SHORT_PACKET_IRQ = 0x2000,
	ECC_CORRECTION_IRQ = 0x1000,
	ECC_NO_CORRECTION_IRQ = 0x800,
	COMPLEXIO2_ERR_IRQ = 0x400,
	COMPLEXIO1_ERR_IRQ = 0x200,
	FIFO_OVF_IRQ = 0x100,
	CONTEXT7 = 0x80,
	CONTEXT6 = 0x40,
	CONTEXT5 = 0x20,
	CONTEXT4 = 0x10,
	CONTEXT3 = 0x8,
	CONTEXT2 = 0x4,
	CONTEXT1 = 0x2,
	CONTEXT0 = 0x1,
};

#define CSI2_PAD_SINK0		0
#define CSI2_PAD_SINK1		1
#define CSI2_PAD_SOURCE0	2
#define CSI2_PAD_SOURCE1	3
#define CSI2_PADS_NUM		4

#define CSI2_OUTPUT_VI0	    (1 << 0)
#define CSI2_OUTPUT_VI1	    (1 << 1)

#define  Dl0_MAP    (0x1)
#define  Dl1_MAP    (0x2)
#define  Dl2_MAP    (0x3)
#define  Dl3_MAP    (0x4)

#define  MIPI_YUV422 (0x1E)
#define  MIPI_RAW8   (0x2A)
#define  MIPI_RAW10  (0x2B)
#define  MIPI_RAW12  (0x2C)

struct isp_csi2_info
{
	unsigned int    csi0_used;
    unsigned int    csi0_sony_wdr;
    unsigned int    csi0_lane_nb;
    unsigned int    csi0_dl0_map;
    unsigned int    csi0_dl1_map;
    unsigned int    csi0_dl2_map;
    unsigned int    csi0_dl3_map;
//
    unsigned int    csi00_datatype_select0;     
    unsigned int    csi00_datatype_select1;   
    unsigned int    csi00_vc_select;
//
    unsigned int    csi01_datatype_select0; 
    unsigned int    csi01_datatype_select1;   
    unsigned int    csi01_vc_select; 
//
    unsigned int    csi02_datatype_select0;     
    unsigned int    csi02_datatype_select1;   
    unsigned int    csi02_vc_select;
//
	unsigned int    csi1_used;
    unsigned int    csi1_sony_wdr;
    unsigned int    csi1_lane_nb;
    unsigned int    csi1_dl0_map;
    unsigned int    csi1_dl1_map;
    unsigned int    csi1_dl2_map;
    unsigned int    csi1_dl3_map;
//
    unsigned int    csi10_datatype_select0;     
    unsigned int    csi10_datatype_select1;   
    unsigned int    csi10_vc_select;    
};

#endif /**/_MIPI_CSI2_H_