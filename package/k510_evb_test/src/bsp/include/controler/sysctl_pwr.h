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
#ifndef __SYSCTL_PWR_H__
#define __SYSCTL_PWR_H__

/* created by hukai */

#include <stdint.h>
#include <stdbool.h>
#include "platform.h"

#define SYSCTL_PWR_BASE_ADDR   (SYSCTL_BASE_ADDR + 0x3000)

typedef struct
{
    volatile uint32_t ax25m_pwr_tim;    /* 0x00 */
    volatile uint32_t ax25m_lpi_tim;    /* 0x04 */
    volatile uint32_t ax25m_lpi_ctl;    /* 0x08 */
    volatile uint32_t ax25m_pwr_ctl;    /* 0x0c */
    volatile uint32_t ax25m_lpi_state;  /* 0x10 */
    volatile uint32_t ax25m_pwr_state;  /* 0x14 */
    volatile uint32_t ax25m_wfi_tim;    /* 0x18 */
    volatile uint32_t ax25m_reserved;   /* 0x1c */

    volatile uint32_t ax25p_pwr_tim;    /* 0x20 */
    volatile uint32_t ax25p_lpi_tim;    /* 0x24 */
    volatile uint32_t ax25p_lpi_ctl;    /* 0x28 */
    volatile uint32_t ax25p_pwr_ctl;    /* 0x2c */
    volatile uint32_t ax25p_lpi_state;  /* 0x30 */
    volatile uint32_t ax25p_pwr_state;  /* 0x34 */
    volatile uint32_t ax25p_wfi_tim;    /* 0x38 */
    volatile uint32_t ax25p_reserved;   /* 0x3c */

    volatile uint32_t ai_pwr_tim;       /* 0x40 */
    volatile uint32_t ai_lpi_tim;       /* 0x44 */
    volatile uint32_t ai_lpi_ctl;       /* 0x48 */
    volatile uint32_t ai_pwr_ctl;       /* 0x4c */
    volatile uint32_t ai_lpi_state;     /* 0x50 */
    volatile uint32_t ai_pwr_state;     /* 0x54 */
    volatile uint32_t ai_reserved[2];   /* 0x58 */

    volatile uint32_t gnne_pwr_tim;     /* 0x60 */
    volatile uint32_t gnne_lpi_tim;     /* 0x64 */
    volatile uint32_t gnne_lpi_ctl;     /* 0x68 */
    volatile uint32_t gnne_pwr_ctl;     /* 0x6c */
    volatile uint32_t gnne_lpi_state;   /* 0x70 */
    volatile uint32_t gnne_pwr_state;   /* 0x74 */
    volatile uint32_t gnne_reserved[2]; /* 0x78 */

    volatile uint32_t sec_pwr_tim;      /* 0x80 */
    volatile uint32_t sec_lpi_tim;      /* 0x84 */
    volatile uint32_t sec_lpi_ctl;      /* 0x88 */
    volatile uint32_t sec_pwr_ctl;      /* 0x8c */
    volatile uint32_t sec_lpi_state;    /* 0x90 */
    volatile uint32_t sec_pwr_state;    /* 0x94 */
    volatile uint32_t sec_reserved[2];  /* 0x98 */

    volatile uint32_t stor_pwr_tim;     /* 0xa0 */
    volatile uint32_t stor_lpi_tim;     /* 0xa4 */
    volatile uint32_t stor_lpi_ctl;     /* 0xa8 */
    volatile uint32_t stor_pwr_ctl;     /* 0xac */
    volatile uint32_t stor_lpi_state;   /* 0xb0 */
    volatile uint32_t stor_pwr_state;   /* 0xb4 */
    volatile uint32_t stor_reserved[2]; /* 0xb8 */

    volatile uint32_t peri_pwr_tim;     /* 0xc0 */
    volatile uint32_t peri_lpi_tim;     /* 0xc4 */
    volatile uint32_t peri_lpi_ctl;     /* 0xc8 */
    volatile uint32_t peri_pwr_ctl;     /* 0xcc */
    volatile uint32_t peri_lpi_state;   /* 0xd0 */
    volatile uint32_t peri_pwr_state;   /* 0xd4 */
    volatile uint32_t peri_reserved[2]; /* 0xd8 */

    volatile uint32_t mctl_pwr_tim0;    /* 0xe0 */
    volatile uint32_t mctl_pwr_tim1;    /* 0xe4 retention */
    volatile uint32_t mctl_lpi_tim;     /* 0xe8 */
    volatile uint32_t mctl_lpi_ctl;     /* 0xec */
    volatile uint32_t mctl_pwr_ctl;     /* 0xf0 */
    volatile uint32_t mctl_lpi_state;   /* 0xf4 */
    volatile uint32_t mctl_pwr_state;   /* 0xf8 */
    volatile uint32_t mctl_reserved;    /* 0xfc */

    volatile uint32_t sram0_pwr_tim;    /* 0x100 */
    volatile uint32_t sram0_lpi_tim;    /* 0x104 */
    volatile uint32_t sram0_lpi_ctl;    /* 0x108 */
    volatile uint32_t sram0_pwr_ctl;    /* 0x10c */
    volatile uint32_t sram0_lpi_state;  /* 0x110 */
    volatile uint32_t sram0_pwr_state;  /* 0x114 */
    volatile uint32_t sram0_reserved[2];/* 0x118 */

    volatile uint32_t sram1_pwr_tim;    /* 0x120 */
    volatile uint32_t sram1_lpi_tim;    /* 0x124 */
    volatile uint32_t sram1_lpi_ctl;    /* 0x128 */
    volatile uint32_t sram1_pwr_ctl;    /* 0x12c */
    volatile uint32_t sram1_lpi_state;  /* 0x130 */
    volatile uint32_t sram1_pwr_state;  /* 0x134 */
    volatile uint32_t sram1_reserved[10];/* 0x138 */

    volatile uint32_t disp_pwr_tim;     /* 0x160 */
    volatile uint32_t disp_lpi_tim;     /* 0x164 */
    volatile uint32_t disp_lpi_ctl;     /* 0x168 */
    volatile uint32_t disp_pwr_ctl;     /* 0x16c */
    volatile uint32_t disp_lpi_state;   /* 0x170 */
    volatile uint32_t disp_pwr_state;   /* 0x174 */
    volatile uint32_t disp_reserved[2]; /* 0x178 */

    volatile uint32_t h264_pwr_tim;     /* 0x180 */
    volatile uint32_t h264_lpi_tim;     /* 0x184 */
    volatile uint32_t h264_lpi_ctl;     /* 0x188 */
    volatile uint32_t h264_pwr_ctl;     /* 0x18c */
    volatile uint32_t h264_lpi_state;   /* 0x190 */
    volatile uint32_t h264_pwr_state;   /* 0x194 */
    volatile uint32_t h264_reserved[2]; /* 0x198 */

    volatile uint32_t usb_pwr_tim;      /* 0x1a0 */
    volatile uint32_t usb_lpi_tim;      /* 0x1a4 */
    volatile uint32_t usb_lpi_ctl;      /* 0x1a8 */
    volatile uint32_t usb_pwr_ctl;      /* 0x1ac */
    volatile uint32_t usb_lpi_state;    /* 0x1b0 */
    volatile uint32_t usb_pwr_state;    /* 0x1b4 */
    volatile uint32_t usb_reserved[2];  /* 0x1b8 */

    volatile uint32_t isp_pwr_tim;      /* 0x1c0 */
    volatile uint32_t isp_lpi_tim;      /* 0x1c4 */
    volatile uint32_t isp_lpi_ctl;      /* 0x1c8 */
    volatile uint32_t isp_pwr_ctl;      /* 0x1cc */
    volatile uint32_t isp_lpi_state;    /* 0x1d0 */
    volatile uint32_t isp_pwr_state;    /* 0x1d4 */
    volatile uint32_t isp_reserved[32]; /* 0x1d8-0x254 */

    /* repair power domain subsys sram erea */
    volatile uint32_t pwr_dom_grp_en;       /* 0x258 */
    volatile uint32_t pwr_dom_grp_sta;      /* 0x25c */

    volatile uint32_t ax25m_repair_tim;     /* 0x260 */
    volatile uint32_t ax25p_repair_tim;     /* 0x264 */
    volatile uint32_t gnne_repair_tim;      /* 0x268 */
    volatile uint32_t sram0_repair_tim;     /* 0x26c */
    volatile uint32_t sram1_repair_tim;     /* 0x270 */
    volatile uint32_t isp_sys_repair_tim;   /* 0x274 */
} sysctl_pwr_s;

typedef enum 
{
    SYSCTL_PD_AX25M,
    SYSCTL_PD_AX25P,
    SYSCTL_PD_AI,
    SYSCTL_PD_GNNE,
    SYSCTL_PD_SEC,
    SYSCTL_PD_STOR,
    SYSCTL_PD_PERI,
    SYSCTL_PD_MCTL,
    SYSCTL_PD_SRAM0,
    SYSCTL_PD_SRAM1,
    SYSCTL_PD_DISP,
    SYSCTL_PD_H264,
    SYSCTL_PD_USB,
    SYSCTL_PD_ISP,
    SYSCTL_PD_ISP_F4K,
    SYSCTL_PD_ISP_F2K,
    SYSCTL_PD_ISP_R2K,
    SYSCTL_PD_ISP_TOF,
    SYSCTL_PD_MAX,
} sysctl_pwr_domain_e;


typedef enum
{
    SYSCTL_PWR_ACK_TO_TIM,  /* idleReq to idleAck max time */
    SYSCTL_PWR_IDLE_TO_TIM, /* idleAck to idle max time */
    SYSCTL_PWR_IDLE_HD_TIM, /* idle hold tim, from idle to cancel idleReq min time */
    SYSCTL_PWR_ISO_SU_TIM,  /* isolation setup tim */
    SYSCTL_PWR_PD_HD_TIM,   /* power done hardware tim */
    SYSCTL_PWR_SU_TIM,      /* Power bringup tim */
    SYSCTL_PWR_RET_SU_TIM,  /* retention su tim */
    SYSCTL_PWR_RST_SU_TIM,  /* reset su tim */
    SYSCTL_PWR_WFI_TIM,     /* wait for interrupt tim*/
    SYSCTL_PWR_MAX_TIM,
}sysctl_pwr_tim_e;


bool sysctl_pwr_set_iso_su_tim(volatile uint32_t *reg, uint32_t iso_su_tim);
bool sysctl_pwr_set_pd_hd_tim(volatile uint32_t *reg, uint32_t pd_hd_tim);
bool sysctl_pwr_set_pwr_su_tim(volatile uint32_t *reg, uint32_t pwr_su_tim);
bool sysctl_pwr_set_ret_su_tim(volatile uint32_t *reg, uint32_t ret_su_tim);
bool sysctl_pwr_set_rst_su_tim(volatile uint32_t *reg, uint32_t rst_su_tim);
bool sysctl_pwr_set_ack_to_tim(volatile uint32_t *reg, uint32_t ack_to_tim);
bool sysctl_pwr_set_idle_to_tim(volatile uint32_t *reg, uint32_t idle_to_tim);
bool sysctl_pwr_set_idle_hd_tim(volatile uint32_t *reg, uint32_t idle_hd_tim);
bool sysctl_pwr_set_wfi_tim(volatile uint32_t *reg, uint32_t wfi_tim);
bool sysctl_pwr_set_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t tim_value);
bool sysctl_pwr_get_iso_su_tim(volatile uint32_t *reg, uint32_t *iso_su_tim);
bool sysctl_pwr_get_pd_hd_tim(volatile uint32_t *reg, uint32_t *pd_hd_tim);
bool sysctl_pwr_get_pwr_su_tim(volatile uint32_t *reg, uint32_t *pwr_su_tim);
bool sysctl_pwr_get_ret_su_tim(volatile uint32_t *reg, uint32_t *ret_su_tim);
bool sysctl_pwr_get_rst_su_tim(volatile uint32_t *reg, uint32_t *rst_su_tim);
bool sysctl_pwr_get_ack_to_tim(volatile uint32_t *reg, uint32_t *ack_to_tim);
bool sysctl_pwr_get_idle_to_tim(volatile uint32_t *reg, uint32_t *idle_to_tim);
bool sysctl_pwr_get_idle_hd_tim(volatile uint32_t *reg, uint32_t *idle_hd_tim);
bool sysctl_pwr_get_wfi_tim(volatile uint32_t *reg, uint32_t *wfi_tim);
bool sysctl_pwr_get_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t *tim_value);
bool sysctl_pwr_set_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool enable);
bool sysctl_pwr_get_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool *enable);
bool sysctl_pwr_set_auto_pwr(sysctl_pwr_domain_e powerdomain, bool enable);
bool sysctl_pwr_get_auto_pwr(sysctl_pwr_domain_e powerdomain, bool *enable);
bool sysctl_pwr_set_repair_enable(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_check_repair_done(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_set_lpi_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable);
bool sysctl_pwr_set_pwr_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable);
bool sysctl_pwr_set_power(sysctl_pwr_domain_e powerdomain, bool enable);

/* 使用下面两个API对SOC电源域进行上下点控制 */
bool sysctl_pwr_up(sysctl_pwr_domain_e powerdomain);
bool sysctl_pwr_off(sysctl_pwr_domain_e powerdomain);

#endif
