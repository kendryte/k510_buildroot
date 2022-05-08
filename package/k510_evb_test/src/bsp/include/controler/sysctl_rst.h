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
#ifndef __SYSCTL_RST_H__
#define __SYSCTL_RST_H__

/* created by hukai */

#include <stdint.h>
#include "stdbool.h"
#include "platform.h"

#define SYSCTL_RST_BASE_ADDR    (SYSCTL_BASE_ADDR + 0x2000)

typedef enum 
{
    SYSCTL_RESET_AX25P_CORE,
    SYSCTL_RESET_AX25P_LOCAL_MEMORY,
    SYSCTL_RESET_AI,
    SYSCTL_RESET_GNNE,
    SYSCTL_RESET_I2C0,
    SYSCTL_RESET_I2C1,
    SYSCTL_RESET_I2C2,
    SYSCTL_RESET_I2C3,
    SYSCTL_RESET_I2C4,
    SYSCTL_RESET_I2C5,
    SYSCTL_RESET_I2C6,
    SYSCTL_RESET_WDT0,
    SYSCTL_RESET_WDT1,
    SYSCTL_RESET_WDT2,
    SYSCTL_RESET_TIMER,
    SYSCTL_RESET_RTC,
    SYSCTL_RESET_GPIO,
    SYSCTL_RESET_IOMUX,
    SYSCTL_RESET_MAILBOX,
    SYSCTL_RESET_PWM,
    SYSCTL_RESET_VAD,
    SYSCTL_RESET_UART0,
    SYSCTL_RESET_UART1,
    SYSCTL_RESET_UART2,
    SYSCTL_RESET_UART3,
    SYSCTL_RESET_I2S2,
    SYSCTL_RESET_SPI0,
    SYSCTL_RESET_SPI1,
    SYSCTL_RESET_SPI2,
    SYSCTL_RESET_SPI3,
    SYSCTL_RESET_AUDIF,
    SYSCTL_RESET_SHA,
    SYSCTL_RESET_AES,
    SYSCTL_RESET_RSA,
    SYSCTL_RESET_ROM,
    SYSCTL_RESET_OTP,
    SYSCTL_RESET_PUF,
    SYSCTL_RESET_SDC0,
    SYSCTL_RESET_SDC1,
    SYSCTL_RESET_SDC2,
    SYSCTL_RESET_PERI_DMA,
    SYSCTL_RESET_SYS_DMA,
    SYSCTL_RESET_EMAC,
    SYSCTL_RESET_SDIO_SLAVE,
    SYSCTL_RESET_MCTL,
    SYSCTL_RESET_SRAM0,
    SYSCTL_RESET_SRAM1,
    SYSCTL_RESET_ISP_F4K,
    SYSCTL_RESET_ISP_F2K,
    SYSCTL_RESET_ISP_R2K,
    SYSCTL_RESET_ISP_TOF,
    SYSCTL_RESET_CSI0,
    SYSCTL_RESET_CSI1,
    SYSCTL_RESET_CSI2,
    SYSCTL_RESET_CSI3,
    SYSCTL_RESET_SENSOR,
    SYSCTL_RESET_VI,
    SYSCTL_RESET_MFBC,
    SYSCTL_RESET_DSI,
    SYSCTL_RESET_BT1120,
    SYSCTL_RESET_TWOD,
    SYSCTL_RESET_VO,
    SYSCTL_RESET_H264,
    SYSCTL_RESET_USB,
} sysctl_reset_e;

typedef enum{
    SYSCTL_RESET_TIME_AX25M,
    SYSCTL_RESET_TIME_AX25P,
    SYSCTL_RESET_TIME_AI,
    SYSCTL_RESET_TIME_GNNE,
    SYSCTL_RESET_TIME_PERI_SYS,
    SYSCTL_RESET_TIME_UART,
    SYSCTL_RESET_TIME_I2S_SLAVE,
    SYSCTL_RESET_TIME_SPI,
    SYSCTL_RESET_TIME_AUDIF,
    SYSCTL_RESET_TIME_SEC_SYS,
    SYSCTL_RESET_TIME_SHA,
    SYSCTL_RESET_TIME_AES,
    SYSCTL_RESET_TIME_RSA,
    SYSCTL_RESET_TIME_ROM,
    SYSCTL_RESET_TIME_OTP,
    SYSCTL_RESET_TIME_PUF,
    SYSCTL_RESET_TIME_STOR_SYS,
    SYSCTL_RESET_TIME_SDCTL,
    SYSCTL_RESET_TIME_DMAC,
    SYSCTL_RESET_TIME_EMAC,
    SYSCTL_RESET_TIME_SDIO_SLAVE,
    SYSCTL_RESET_TIME_MCTL,
    SYSCTL_RESET_TIME_SRAM0,
    SYSCTL_RESET_TIME_SRAM1,
    SYSCTL_RESET_TIME_ISP_SYS,
    SYSCTL_RESET_TIME_ISP_MODULE,
    SYSCTL_RESET_TIME_CSI,
    SYSCTL_RESET_TIME_SENSOR,
    SYSCTL_RESET_TIME_VI,
    SYSCTL_RESET_TIME_MFBC,
    SYSCTL_RESET_TIME_DISP_SYS,
    SYSCTL_RESET_TIME_DSI,
    SYSCTL_RESET_TIME_BT1120,
    SYSCTL_RESET_TIME_TWOD,
    SYSCTL_RESET_TIME_VO,
    SYSCTL_RESET_TIME_H264,
    SYSCTL_RESET_TIME_USB,
} sysctl_reset_time_e;

typedef struct{
    volatile uint32_t ax25m_rst_tim;    /* 0x00 */
    volatile uint32_t reserved0[3];     /* 0x04 0x08 0x0c */
    volatile uint32_t ax25p_rst_tim;    /* 0x10 */
    volatile uint32_t ax25p_rst_ctl;    /* 0x14 */
    volatile uint32_t reserved1[2];     /* 0x18 0x1c */
    volatile uint32_t ai_rst_tim;       /* 0x20 */
    volatile uint32_t ai_rst_ctl;       /* 0x24 */
    volatile uint32_t gnne_rst_tim;     /* 0x28 */
    volatile uint32_t gnne_rst_ctl;     /* 0x2c */
    volatile uint32_t reserved2[4];     /* 0x30 0x34 0x38 0x3c */
    volatile uint32_t soc_ctl_rst_ctl0; /* 0x40 */
    volatile uint32_t soc_ctl_rst_ctl1; /* 0x44 */
    volatile uint32_t reserved3[2];     /* 0x48 0x4c */
    volatile uint32_t peri_sys_rst_tim; /* 0x50 */
    volatile uint32_t uart_rst_tim;     /* 0x54 */
    volatile uint32_t uart0_rst_ctl;    /* 0x58 */
    volatile uint32_t uart1_rst_ctl;    /* 0x5c */
    volatile uint32_t uart2_rst_ctl;    /* 0x60 */
    volatile uint32_t uart3_rst_ctl;    /* 0x64 */
    volatile uint32_t i2s2_rst_tim;     /* 0x68 */
    volatile uint32_t i2s2_rst_ctl;     /* 0x6c i2s slave*/
    volatile uint32_t spi_rst_tim;      /* 0x70 */
    volatile uint32_t spi0_rst_ctl;     /* 0x74 */
    volatile uint32_t spi1_rst_ctl;     /* 0x78 */
    volatile uint32_t spi2_rst_ctl;     /* 0x7c */
    volatile uint32_t spi3_rst_ctl;     /* 0x80 */
    volatile uint32_t audif_rst_tim;    /* 0x84 */
    volatile uint32_t audif_rst_ctl;    /* 0x88 */
    volatile uint32_t sec_sys_rst_tim;  /* 0x8c */
    volatile uint32_t sha_rst_tim;      /* 0x90 */
    volatile uint32_t sha_rst_ctl;      /* 0x94 */
    volatile uint32_t aes_rst_tim;      /* 0x98 */
    volatile uint32_t aes_rst_ctl;      /* 0x9c */
    volatile uint32_t rsa_rst_tim;      /* 0xa0 */
    volatile uint32_t rsa_rst_ctl;      /* 0xa4 */
    volatile uint32_t rom_rst_tim;      /* 0xa8 */
    volatile uint32_t rom_rst_ctl;      /* 0xac */
    volatile uint32_t otp_rst_tim;      /* 0xb0 */
    volatile uint32_t otp_rst_ctl;      /* 0xb4 */
    volatile uint32_t puf_rst_tim;      /* 0xb8 */
    volatile uint32_t puf_rst_ctl;      /* 0xbc */
    volatile uint32_t stor_sys_rst_tim; /* 0xc0 */
    volatile uint32_t sdctl_rst_tim;    /* 0xc4 */
    volatile uint32_t sdc0_rst_ctl;     /* 0xc8 */
    volatile uint32_t sdc1_rst_ctl;     /* 0xcc */
    volatile uint32_t sdc2_rst_ctl;     /* 0xd0 */
    volatile uint32_t dmac_rst_tim;     /* 0xd4 */
    volatile uint32_t peri_dma_rst_ctl; /* 0xd8 */
    volatile uint32_t sys_dma_rst_ctl;  /* 0xdc */
    volatile uint32_t emac_rst_tim;     /* 0xe0 */
    volatile uint32_t emac_rst_ctl;     /* 0xe4 */
    volatile uint32_t sdio_s_rst_tim;   /* 0xe8 sdio slave */
    volatile uint32_t sdio_s_rst_ctl;   /* 0xec */
    volatile uint32_t mctl_rst_tim;     /* 0xf0 */
    volatile uint32_t mctl_rst_ctl;     /* 0xf4 */
    volatile uint32_t reserved4[2];     /* 0xf8 0xfc */
    volatile uint32_t sram0_rst_tim;    /* 0x100 */
    volatile uint32_t sram0_rst_ctl;    /* 0x104 */
    volatile uint32_t reserved5[2];     /* 0x108 0x10c */
    volatile uint32_t sram1_rst_tim;    /* 0x110 */
    volatile uint32_t sram1_rst_ctl;    /* 0x114 */
    volatile uint32_t isp_sys_rst_tim;  /* 0x118 */
    volatile uint32_t isp_module_rst_tim;   /* 0x11c */
    volatile uint32_t isp_f4k_rst_ctl;  /* 0x120 */
    volatile uint32_t isp_f2k_rst_ctl;  /* 0x124 */
    volatile uint32_t isp_r2k_rst_ctl;  /* 0x128 */
    volatile uint32_t isp_tof_rst_ctl;  /* 0x12c */
    volatile uint32_t csi_rst_tim;      /* 0x130 */
    volatile uint32_t csi0_rst_ctl;     /* 0x134 */
    volatile uint32_t csi1_rst_ctl;     /* 0x138 */
    volatile uint32_t csi2_rst_ctl;     /* 0x13c */
    volatile uint32_t csi3_rst_ctl;     /* 0x140 */
    volatile uint32_t sensor_rst_tim;   /* 0x144 */
    volatile uint32_t sensor_rst_ctl;   /* 0x148 */
    volatile uint32_t vi_rst_tim;       /* 0x14c */
    volatile uint32_t vi_rst_ctl;       /* 0x150 */
    volatile uint32_t mfbc_rst_tim;     /* 0x154 */
    volatile uint32_t mfbc_rst_ctl;     /* 0x158 */
    volatile uint32_t disp_sys_rst_tim; /* 0x15c */
    volatile uint32_t dsi_rst_tim;      /* 0x160 */
    volatile uint32_t dsi_rst_ctl;      /* 0x164 */
    volatile uint32_t bt1120_rst_tim;   /* 0x168 */
    volatile uint32_t bt1120_rst_ctl;   /* 0x16c */
    volatile uint32_t twod_rst_tim;     /* 0x170 */
    volatile uint32_t twod_rst_ctl;     /* 0x174 */
    volatile uint32_t vo_rst_tim;       /* 0x178 */
    volatile uint32_t vo_rst_ctl;       /* 0x17c */
    volatile uint32_t h264_rst_tim;     /* 0x180 */
    volatile uint32_t h264_rst_ctl;     /* 0x184 */
    volatile uint32_t usb_rst_tim;      /* 0x188 */
    volatile uint32_t usb_rst_ctl;      /* 0x18c */
} sysctl_rst_t;

/* 直接调用这个API复位即可 */
bool sysctl_reset(sysctl_reset_e reset);
bool sysctl_set_reset_time(sysctl_reset_time_e reset, uint32_t tim0, uint32_t tim1, uint32_t tim2);

#endif