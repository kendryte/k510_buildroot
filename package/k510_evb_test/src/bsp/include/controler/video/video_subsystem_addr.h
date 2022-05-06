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
#ifndef _VIDEO_SUBSYSTEM_ADDR_DEF_H_
#define _VIDEO_SUBSYSTEM_ADDR_DEF_H_

#define CANAAN_ISP
//#define USE_GPIO_I2C

#ifdef CANAAN_ISP
#define VIDEO_SUBSYSTEM_BASE_ADDR   0x92600000
#define VI_BASE_ADDR                0x92620000  //addr range 0x00000~0x0ffff
#define ISP_4K_BASE_ADDR            0x92640000  //addr range 0x10000~0x1ffff
#define ISP_2K_BASE_ADDR            0x92650000  //addr range 0x20000~0x2ffff
#define ISP_R2K_BASE_ADDR           0x92660000  //addr range 0x30000~0x3ffff
#define ISP_3D_BASE_ADDR            0x92670000  //addr range 0x40000~0x4ffff
#define ISP_VO_BASE_ADDR            0x92700000  //addr range 0x50000~0x5ffff
#define ISP_DEV_BASE_ADDR           0x92600000  //addr range 0x60000~0x6ffff
#define ISP_EXTCTRL_BASE_ADDR       0x92600000  //addr range 0x70000~0x7ffff
#define CNDS_DSI_BASE_ADDR          0x92710000  //addr range 0x70000~0x7ffff
#define BT1120_BASE_ADDR            0x92730000 
#define TD_BASE_ADDR                0x92720000    //0x92730000 on previous release before 0429 ffinal
#define MFBC_BASE_ADDR              0x92630000
#define SYSCTL_BOOT_REG_BASE        0x97000000
#define SYSCTL_CLK_REG_BASE         0x97001000
#define SYSCTL_RST_REG_BASE         0x97002000
#define SYSCTL_PWR_REG_BASE         0x97003000

#define VIDEO_DSI_BASE_ADDR           0x92710000
#define VIDEO_TXDPHY_BASE_ADDR        0x92718000
#define VIDEO_RXDPHY_BASE           VIDEO_SUBSYSTEM_BASE_ADDR
#define VIDEO_SUBSYS_MIPI_CORNER_REG_BASE       0x92680000

#else
#define VIDEO_SUBSYSTEM_BASE_ADDR   0x92400000
#define VI_BASE_ADDR                0x92400000  //addr range 0x00000~0x0ffff
#define ISP_4K_BASE_ADDR            0x92410000  //addr range 0x10000~0x1ffff
#define ISP_2K_BASE_ADDR            0x92420000  //addr range 0x20000~0x2ffff
#define ISP_R2K_BASE_ADDR           0x92430000  //addr range 0x30000~0x3ffff
#define ISP_3D_BASE_ADDR            0x92440000  //addr range 0x40000~0x4ffff
#define ISP_VO_BASE_ADDR            0x92450000  //addr range 0x50000~0x5ffff
#define ISP_DEV_BASE_ADDR           0x92460000  //addr range 0x60000~0x6ffff
#define ISP_EXTCTRL_BASE_ADDR       0x92470000  //addr range 0x70000~0x7ffff
#define CNDS_DSI_BASE_ADDR          0x92480000  //addr range 0x70000~0x7ffff
#define BT1120_BASE_ADDR            0x92490000 
#define TD_BASE_ADDR                0x924A0000
#define MFBC_BASE_ADDR              0x924B0000
#endif

#define TOF_REG_BASE                        ISP_3D_BASE_ADDR
#define TOF_REG_WRAP_OFFSET                 0x00000000
#define TOF_REG_CORE_OFFSET                 0x00000400
#define TOF_REG_TABLE_OFFSET                0x00000800
#define TOF_REG_DS_OFFSET                   0x00003000

#define TOF_WRAP_REG_BASE                   (TOF_REG_BASE + TOF_REG_WRAP_OFFSET)
#define TOF_WRAP_REG_SIZE_ALIGN             0x0400

#define TOF_CORE_REG_BASE                   (TOF_REG_BASE + TOF_REG_CORE_OFFSET)
#define TOF_CORE_REG_SIZE_ALIGN             0x0400

#define TOF_TABLE_REG_BASE                  (TOF_REG_BASE + TOF_REG_TABLE_OFFSET)
#define TOF_TABLE_REG_SIZE_ALIGN            0x1f00

#define TOF_DS_REG_BASE                     (TOF_REG_BASE + TOF_REG_DS_OFFSET)
#define TOF_DS_REG_SIZE_ALIGN               0x1f00

#define TOF_MAX_DEV_NUM 1

#define MFBC_WRAP_BASE      (MFBC_BASE_ADDR + 0x0000)
#define MFBC_CORE_BASE      (MFBC_BASE_ADDR + 0x0100)

#define   TD_WRAP_BASE                 (TD_BASE_ADDR + (0x0000))
#define   TD_ROTATION_BASE             (TD_BASE_ADDR + (0x0080))
#define   TD_SCALER_MIXER_BASE         (TD_BASE_ADDR + (0x0800))
#define   TD_HSCALE_BASE               (TD_BASE_ADDR + (0x8800))
#define   TD_VSCALE_BASE               (TD_BASE_ADDR + (0x9400))

#define VI_REG_BASE                         VI_BASE_ADDR
#define VI_REG_SIZE_ALIGN                   0x0800
#define VI_PIPE_CSI_0_0_OFFSET              0x0400
#define VI_PIPE_CSI_0_1_OFFSET              0x0500
#define VI_PIPE_CSI_0_2_OFFSET              0x0500

#define VI_PIPE_CSI_1_0_OFFSET              (VI_REG_SIZE_ALIGN + 0x0400)
#define VI_PIPE_CSI_1_1_OFFSET              (VI_REG_SIZE_ALIGN + 0x0500)
#define VI_PIPE_CSI_1_2_OFFSET              (VI_REG_SIZE_ALIGN + 0x0500)

#define VI_PIPE_DVP_0_OFFSET                0x0600
#define VI_PIPE_DVP_1_OFFSET                (VI_REG_SIZE_ALIGN + 0x0600)

#define VI_WRAP_OFFSET                      0x0700


#define VI_PIPE_CSI_0_0_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_0_0_OFFSET)
#define VI_PIPE_CSI_0_1_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_0_1_OFFSET)
#define VI_PIPE_CSI_0_2_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_0_2_OFFSET)

#define VI_PIPE_CSI_1_0_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_1_0_OFFSET)
#define VI_PIPE_CSI_1_1_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_1_1_OFFSET)
#define VI_PIPE_CSI_1_2_REG_BASE            (VI_REG_BASE + VI_PIPE_CSI_1_2_OFFSET)

#define VI_PIPE_DVP_0_REG_BASE              (VI_REG_BASE + VI_PIPE_DVP_0_OFFSET)
#define VI_PIPE_DVP_1_REG_BASE              (VI_REG_BASE + VI_PIPE_DVP_1_OFFSET)

#define VI_WRAP_REG_BASE                    (VI_REG_BASE + VI_WRAP_OFFSET)


#define VI_MAX_DEV_NUM 						4
#define VI_MAX_DEV_PIPE_NUM 				3

typedef enum _VI_PIPE_ID
{
	VI_MIPI_CSI00_PIPE_ID,
	VI_MIPI_CSI01_PIPE_ID,
	VI_MIPI_CSI02_PIPE_ID,
	VI_MIPI_CSI10_PIPE_ID,
	VI_MIPI_CSI11_PIPE_ID,
	VI_MIPI_CSI12_PIPE_ID,
	VI_DVP_0_PIPE_ID,
	VI_DVP_1_PIPE_ID,
	VI_MAX_PIPE_NUM,
}VI_PIPE_ID;


#define   VO_CONFIG_CORE_BASE         (ISP_VO_BASE_ADDR + 0x0000)
#define   VO_CONFIG_LINE_BASE         (ISP_VO_BASE_ADDR + 0x0600)
#define   VO_HSCALE_BASE              (ISP_VO_BASE_ADDR + 0x8000)
#define   VO_VSCALE_BASE              (ISP_VO_BASE_ADDR + 0x8C00)
#define   VO_GAMMA_BASE               (ISP_VO_BASE_ADDR + 0xC000)
#endif /* _VIDEO_SUBSYSTEM_ADDR_DEF_H_ */
