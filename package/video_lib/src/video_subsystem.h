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
  File Name     : video_subsystem.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _VIDEO_SUBSYSTEM_H_
#define _VIDEO_SUBSYSTEM_H_

#define CANAAN_ISP
//#define USE_GPIO_I2C
//#define CANAAN_440
#define _F2K

#define   VIDEO_SUBSYSTEM_BASE_ADDR 0x92600000
#define   MIPI_DPHY_BASE            0x92620000
#define   VI_BASE_ADDR              0x92620000  //addr range 0x00000~0x0ffff
#define   ISP_4K_BASE_ADDR          0x92640000  //addr range 0x10000~0x1ffff
#define   ISP_2K_BASE_ADDR          0x92650000  //addr range 0x20000~0x2ffff
#define   ISP_R2K_BASE_ADDR         0x92660000  //addr range 0x30000~0x3ffff
#define   ISP_3D_BASE_ADDR          0x92670000  //addr range 0x40000~0x4ffff
#define   ISP_VO_BASE_ADDR          0x92700000  //addr range 0x50000~0x5ffff
#define   ISP_DEV_BASE_ADDR         0x92600000  //addr range 0x60000~0x6ffff
#define   ISP_EXTCTRL_BASE_ADDR     0x92600000  //addr range 0x70000~0x7ffff
#define   CNDS_DSI_BASE_ADDR        0x92710000  //addr range 0x70000~0x7ffff
#define   BT1120_BASE_ADDR          0x92730000 

#define   TD_BASE_ADDR              0x92720000    //0x92730000 on previous release before 0429 ffinal
#define   FBC_BASE_ADDR             0x92630000

#define   SYSCTL_BOOT_REG_BASE      0x97000000
#define   SYSCTL_CLK_REG_BASE       0x97001000
#define   SYSCTL_RST_REG_BASE       0x97002000
#define   SYSCTL_PWR_REG_BASE       0x97003000
//
#define   CSI_HOST_BASE             (VI_BASE_ADDR + 0x0000) //#ch0
#define   CSI_HOST_END              (VI_BASE_ADDR + 0x03F8)
#define   CSI1_HOST_BASE            (VI_BASE_ADDR + 0x0800 +  0x0000 ) //#ch4
#define   CSI1_HOST_END             (VI_BASE_ADDR + 0x0800 +  0x03F8 )
//#define   MIPI_DPHY_BASE            (VI_BASE_ADDR + 0x0800 +  0x0700 ) //#ch9
//#define   MIPI_DPHY_END             (VI_BASE_ADDR + 0x0800 +  0x07F8 )
#define   MIPI_CORNER_BASE          0x92680000
//
#define   VI_WRAP_BASE     			    (VI_BASE_ADDR + 0x0700)
#define   VI_REG_SIZE_ALIGN         0x0800
#define   VI_PIPE_CSI_0_0_OFFSET    0x0400
#define   VI_PIPE_CSI_0_1_OFFSET    0x0500
#define   VI_PIPE_CSI_0_2_OFFSET    0x0500
#define   VI_PIPE_CSI_1_0_OFFSET    (VI_REG_SIZE_ALIGN + 0x0400)
#define   VI_PIPE_CSI_1_1_OFFSET    (VI_REG_SIZE_ALIGN + 0x0500)
#define   VI_PIPE_CSI_1_2_OFFSET    (VI_REG_SIZE_ALIGN + 0x0500)
#define   VI_PIPE_DVP_0_OFFSET      0x0600
#define   VI_PIPE_DVP_1_OFFSET      (VI_REG_SIZE_ALIGN + 0x0600)
#define   VI_PIPE_CSI_0_0_REG_BASE  (VI_BASE_ADDR + VI_PIPE_CSI_0_0_OFFSET)
#define   VI_PIPE_CSI_0_1_REG_BASE  (VI_BASE_ADDR + VI_PIPE_CSI_0_1_OFFSET)
#define   VI_PIPE_CSI_0_2_REG_BASE  (VI_BASE_ADDR + VI_PIPE_CSI_0_2_OFFSET)
#define   VI_PIPE_CSI_1_0_REG_BASE  (VI_BASE_ADDR + VI_REG_SIZE_ALIGN +VI_PIPE_CSI_0_0_OFFSET)
#define   VI_PIPE_CSI_1_1_REG_BASE  (VI_BASE_ADDR + VI_REG_SIZE_ALIGN + VI_PIPE_CSI_0_1_OFFSET)
#define   VI_PIPE_CSI_1_2_REG_BASE  (VI_BASE_ADDR + VI_REG_SIZE_ALIGN + VI_PIPE_CSI_0_2_OFFSET)
#define   VI_PIPE_DVP_0_REG_BASE    (VI_BASE_ADDR + VI_PIPE_DVP_0_OFFSET)
#define   VI_PIPE_DVP_1_REG_BASE    (VI_BASE_ADDR + VI_REG_SIZE_ALIGN + VI_PIPE_DVP_0_OFFSET)
//
#define   ISP_F_2K_WRAP_BASE				(ISP_2K_BASE_ADDR + 0x0000)
#define   ISP_R_2K_WRAP_BASE				(ISP_R2K_BASE_ADDR + 0x0000)
//  
#define   ISP_F_2K_CORE_BASE        (ISP_2K_BASE_ADDR + 0x0400)
#define   ISP_F_2K_CORE_TABLE_BASE  (ISP_2K_BASE_ADDR + 0x0800)
#define   ISP_R_2K_CORE_BASE        (ISP_R2K_BASE_ADDR + 0x0400)
#define   ISP_R_2K_CORE_TABLE_BASE  (ISP_R2K_BASE_ADDR + 0x0800)
//  
#define   ISP_F_2K_DS_BASE          (ISP_2K_BASE_ADDR + 0x3000)
#define   ISP_R_2K_DS_BASE          (ISP_R2K_BASE_ADDR + 0x3000)
//  
#define   ISP_F_2K_FBC_BASE				  (ISP_2K_BASE_ADDR + 0x5000)
#define   ISP_F_2K_FBD_BASE				  (ISP_2K_BASE_ADDR + 0x5400)
#define   ISP_F_2K_REMAP_BASE			  (ISP_2K_BASE_ADDR + 0x6000) 
#define   ISP_F_2K_OUT0_REMAP_BASE	(ISP_2K_BASE_ADDR + 0x6000) 
#define   ISP_F_2K_OUT1_REMAP_BASE	(ISP_2K_BASE_ADDR + 0x6200) 
#define   ISP_F_2K_MAIN_REMAP_BASE	(ISP_2K_BASE_ADDR + 0x6400) 
#define   ISP_R_2K_REMAP_BASE			  (ISP_R2K_BASE_ADDR + 0x6000)
#define   ISP_R_2K_OUT0_REMAP_BASE	(ISP_R2K_BASE_ADDR + 0x6000) 
#define   ISP_R_2K_OUT1_REMAP_BASE	(ISP_R2K_BASE_ADDR + 0x6200)
#define   ISP_R_2K_MAIN_REMAP_BASE	(ISP_R2K_BASE_ADDR + 0x6400) 
//  
#define   TOF_REG_BASE              ISP_3D_BASE_ADDR
#define   TOF_REG_WRAP_OFFSET       0x00000000
#define   TOF_REG_CORE_OFFSET       0x00000400
#define   TOF_REG_TABLE_OFFSET      0x00000800
#define   TOF_REG_DS_OFFSET         0x00003000
  
#define   TOF_WRAP_REG_BASE         (TOF_REG_BASE + TOF_REG_WRAP_OFFSET)
#define   TOF_WRAP_REG_SIZE_ALIGN   0x0400
  
#define   TOF_CORE_REG_BASE         (TOF_REG_BASE + TOF_REG_CORE_OFFSET)
#define   TOF_CORE_REG_SIZE_ALIGN   0x0400
  
#define   TOF_TABLE_REG_BASE        (TOF_REG_BASE + TOF_REG_TABLE_OFFSET)
#define   TOF_TABLE_REG_SIZE_ALIGN  0x1f00
  
#define   TOF_DS_REG_BASE           (TOF_REG_BASE + TOF_REG_DS_OFFSET)
#define   TOF_DS_REG_SIZE_ALIGN     0x1f00

#define   FBC_WRAP_BASE             (FBC_BASE_ADDR + 0x0000)
#define   FBC_CORE_BASE             (FBC_BASE_ADDR + 0x0100)

#define   VO_CORE_BASE              (ISP_VO_BASE_ADDR + 0x0000)
#define   VO_REMAP_BASE             (ISP_VO_BASE_ADDR + 0x600)
#define   VO_CONFIG_LINE_CTL_BASE   (ISP_VO_BASE_ADDR + 0x600)
#define   VO_CONFIG_LINE_DATA_BASE  (ISP_VO_BASE_ADDR + 0x700)
#define   VO_HSCALE_BASE            (ISP_VO_BASE_ADDR + (0x8000))
#define   VO_HSCALE_END             (ISP_VO_BASE_ADDR + (0x83FF))
#define   VO_VSCALE_BASE            (ISP_VO_BASE_ADDR + (0x8C00))
#define   VO_VSCALE_END             (ISP_VO_BASE_ADDR + (0x8D7f))
#define   VO_GAMMA_BASE             (ISP_VO_BASE_ADDR + (0xC000))
#define   VO_GAMMA_END              (ISP_VO_BASE_ADDR + (0xCBFF))

#ifdef _F2K //CANAAN_440
#define ISP_BASE_ADDR  ISP_2K_BASE_ADDR
#else 
#define ISP_BASE_ADDR  ISP_R2K_BASE_ADDR
#endif

#endif /* _VIDEO_SUBSYSTEM_H_ */
