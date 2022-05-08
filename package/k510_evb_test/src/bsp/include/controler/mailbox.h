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
#ifndef _MAIL_BOX_H
#define _MAIL_BOX_H

#define MAILBOX_INT_RAW_EN      (1 << 16)
#define MAILBOX_INT_EN          (1 << 0)
#define MAILBOX_INT_RST         (1 << 1)

typedef struct _mailbox_t
{
    volatile uint32_t cpu2dsp_int_en;                       /* 0x000  CPU to DSP interrupt enable and module soft reset control */
    volatile uint32_t cpu2dsp_int_set;                      /* 0x004  Set bits in CPU2DSP_INT+1'b1 */
    volatile uint32_t cpu2dsp_int_clr;                      /* 0x008  Set bits in DSP2CPU_INT -1'b1 */
    volatile uint32_t cpu2dsp_int_status;                   /* 0x00C  CPU to DSP interrupr status(Overflow) */
    volatile uint32_t cpu2dsp_int_err_status;               /* 0x010  CPU to DSP interrupr err status */
    volatile uint32_t dsp2cpu_int_set;                      /* 0x014  Set bits in DSP2CPU_INT +1'b1 */
    volatile uint32_t dsp2cpu_int_clr;                      /* 0x018  Set bits in CPU2DSP_INT-1'b1 */
    volatile uint32_t dsp2cpu_int_en;                       /* 0x01C  DSP to CPU interrupt enable */
    volatile uint32_t dsp2cpu_int_status;                   /* 0x020  DSP to CPU interrupt status(Overflow) */
    volatile uint32_t dsp2cpu_int_err_status;               /* 0x024  dsp to cpu interrupr err status */
    volatile uint32_t emmc_boot_ctrl_00;                    /* 0x028  EMMC boot control register 0 */
    // volatile uint32_t reserve0;                             /* 0x02C  RTL err*/
    volatile uint32_t emmc_boot_ctrl_10;                    /* 0x02C  EMMC boot control 1 register */
    volatile uint32_t emmc_boot_addr_l0;                    /* 0x030  EMMC boot address low word */
    volatile uint32_t emmc_boot_addr_h0;                    /* 0x034  EMMC boot address high word */
    volatile uint32_t emmc_boot_block_ctrl0;                /* 0x038  EMMC boot block control register */
    volatile uint32_t emmc_boot_pow_clk_dly0;               /* 0x03C  power to clock delay */
    volatile uint32_t emmc_boot_clk_cmd_dly0;               /* 0x040  clock to command delay */
    volatile uint32_t cpu_dsp_cfg0;                         /* 0x044  Power mode cycle register */
    volatile uint32_t ethernet_ctrl;                        /* 0x048  EMAC control register */
    volatile uint32_t wdt0_ctrl;                            /* 0x04C  wdt 0 control register */
    volatile uint32_t wdt1_ctrl;                            /* 0x050  wdt 1 control register */
    volatile uint32_t wdt2_ctrl;                            /* 0x054  wdt 2 control register */
    volatile uint32_t usbc_wake_up_pin;                     /* 0x058   */
    volatile uint32_t usbc_otgstate;                        /* 0x05C   */
    volatile uint32_t usbc_downstrstate;                    /* 0x060   */
    volatile uint32_t usbc_upstrstate;                      /* 0x064   */
    volatile uint32_t usbc_utmidrvvbus;                     /* 0x068   */
    volatile uint32_t usbc_utmi_suspendm;                   /* 0x06C   */
    volatile uint32_t usbc_utmi_sleepm;                     /* 0x070   */
    volatile uint32_t usbc_utmiiddig;                       /* 0x074   */
    volatile uint32_t usbc_phy_debug_out;                   /* 0x078   */
    volatile uint32_t usbc_phy_xcfg_range;                  /* 0x07C   */
    volatile uint32_t usbc_phy_xcfgo;                       /* 0x080   */
    volatile uint32_t stor_emac_rgmii_link_status;          /* 0x084   */
    volatile uint32_t stor_emac_rgmii_speed;                /* 0x088   */
    volatile uint32_t stor_emac_rgmii_duplex_out;           /* 0x08C   */
    volatile uint32_t stor_emac_mdio_out;                   /* 0x090   */
    volatile uint32_t stor_emac_pfc_negotiate;              /* 0x094   */
    volatile uint32_t stor_emac_rx_pfc_paused;              /* 0x098   */
    volatile uint32_t stor_emac_wol;                        /* 0x09C   */
    volatile uint32_t stor_emac_tsu_timer_h_cnt;            /* 0x0A0   */
    volatile uint32_t stor_emac_tsu_timer_m_cnt;            /* 0x0A4   */
    volatile uint32_t stor_emac_tsu_timer_l_cnt;            /* 0x0A8   */
    volatile uint32_t stor_emac_tsu_timer_cmp_val;          /* 0x0AC   */
    volatile uint32_t mailbox_lock0;                        /* 0x0B0 lock reg 0 */
    volatile uint32_t mailbox_lock1;                        /* 0x0B4 lock reg 1 */
    volatile uint32_t mailbox_lock2;                        /* 0x0B8 lock reg 2 */
    volatile uint32_t mailbox_lock3;                        /* 0x0BC lock reg 3 */
    volatile uint32_t mailbox_lock4;                        /* 0x0C0 lock reg 4 */
    volatile uint32_t mailbox_lock5;                        /* 0x0C4 lock reg 5 */
    volatile uint32_t mailbox_lock6;                        /* 0x0C8 lock reg 6 */
    volatile uint32_t mailbox_lock7;                        /* 0x0CC lock reg 7 */
    volatile uint32_t mailbox_lock8;                        /* 0x0D0 lock reg 8 */
    volatile uint32_t mailbox_lock9;                        /* 0x0D4 lock reg 9 */
    volatile uint32_t mailbox_lock10;                       /* 0x0D8 lock reg 10 */
    volatile uint32_t mailbox_lock11;                       /* 0x0DC lock reg 11 */
    volatile uint32_t mailbox_lock12;                       /* 0x0E0 lock reg 12 */
    volatile uint32_t mailbox_lock13;                       /* 0x0E4 lock reg 13 */
    volatile uint32_t mailbox_lock14;                       /* 0x0E8 lock reg 14 */
    volatile uint32_t mailbox_lock15;                       /* 0x0EC lock reg 15 */
    volatile uint32_t ddr_wcobuf_ctl;                       /* 0x0F0 */
    volatile uint32_t qos_ctrl0;                            /* 0x0F4 */
    volatile uint32_t qos_ctrl1;                            /* 0x0F8 */
    volatile uint32_t qos_ctrl2;                            /* 0x0FC */
    volatile uint32_t qos_ctrl3;                            /* 0x100 */
    volatile uint32_t qos_ctrl4;                            /* 0x104 */
    volatile uint32_t noc_wr_bufferable_ctrl;               /* 0x108 */
    volatile uint32_t i2c2axi_spike_th;                     /* 0x10C */
    volatile uint32_t emmc_host_boot_ack;                   /* 0x110 */
    volatile uint32_t emmc_host_boot_done;                  /* 0x114 */
    volatile uint32_t emmc_host_boot_err;                   /* 0x118 */
    volatile uint32_t ssi_sleep;                            /* 0x11C */
    volatile uint32_t uart_lp_req_sclk;                     /* 0x120 */
    volatile uint32_t uart_lp_req_pclk;                     /* 0x124 */
    volatile uint32_t usb_phy_utmi_linestate;               /* 0x128 */
    volatile uint32_t usb_phy_debug_sel;                    /* 0x12C */
    volatile uint32_t usb_xcfgi_h;                          /* 0x130 */
    volatile uint32_t usb_xcfgi_m;                          /* 0x134 */
    volatile uint32_t usb_xcfgi_l;                          /* 0x138 */
    volatile uint32_t emac_tx_pause;                        /* 0x13C */
    volatile uint32_t emac_tx_pause_zero;                   /* 0x140 */
    volatile uint32_t emac_tx_pfc_sel;                      /* 0x144 */
    volatile uint32_t emac_tx_pfc_pause;                    /* 0x148 */
    volatile uint32_t emac_tx_pfc_pause_zero;               /* 0x14C */
    volatile uint32_t rtc_cfg_addr;                         /* 0x150 */

} mailbox_t;

typedef enum _mailbox_int
{
    MAILBOX_UART0_INTR,
    MAILBOX_UART1_INTR,
    MAILBOX_UART2_INTR,
    MAILBOX_UART3_INTR,
    MAILBOX_I2S2_SLV_INTR,
    MAILBOX_SPI0_CTRL_INTR,
    MAILBOX_RESERVE10,
    MAILBOX_RESERVE11,
    MAILBOX_RESERVE12,
    MAILBOX_RESERVE13,
    MAILBOX_SPI1_CTRL_INTR,
    MAILBOX_SPI2_CTRL_INTR,
    MAILBOX_SPI3_CTRL_INTR,
    MAILBOX_AUDIO_IN_INTR,
    MAILBOX_AUDIO_OUT_INTR,
    MAILBOX_I2C0_IC_INTR,
    MAILBOX_I2C1_IC_INTR,
    MAILBOX_I2C2_IC_INTR,
    MAILBOX_I2C3_IC_INTR,
    MAILBOX_I2C4_IC_INTR,
    MAILBOX_I2C5_IC_INTR,
    MAILBOX_I2C6_IC_INTR,
    MAILBOX_GPIO_GPIO_INTR,
    MAILBOX_SYSCTL_SYS_CTL_INTR,
    MAILBOX_RTC_OTICK_INTR,
    MAILBOX_RTC_OALARM_INTR,
    MAILBOX_PWM0_INTR,
    MAILBOX_PWM1_INTR,
    MAILBOX_PWM2_INTR,
    MAILBOX_PWM3_INTR,
    MAILBOX_VAD_INTR,
    MAILBOX_MAILBOX_TS_INTR,
    MAILBOX_DDR_CONTROLER_INTR,
    MAILBOX_SYS_DMA_INTR,
    MAILBOX_PERI_DMA_INTR,
    MAILBOX_NOC_FAULT_INTR,
} maixbox_int_t;

typedef enum _maixbox_int_dir
{
    MAILBOX_INT_NO_DSP          = 0x10000U,
    MAILBOX_INT_NO_CPU          = 0x20000U,
    MAILBOX_INT_NO_CPUDSP       = 0x30000U,
    MAILBOX_INT_TO_DSP          = 0x10001U,
    MAILBOX_INT_TO_CPU          = 0x20002U,
    MAILBOX_INT_TO_CPUDSP       = 0x30003U
} mailbox_int_dir_t;

typedef enum _mailbox_state
{
    MAILBOX_USBC_OTGSTATE = 0,
    MAILBOX_USBC_DOWNSTRSTATE,
    MAILBOX_USBC_UPSTRSTATE,
    MAILBOX_USBC_UTMIDRVVBUS,
    MAILBOX_USBC_UTMI_SUSPENDM,
    MAILBOX_USBC_UTMI_SLEEPM,
    MAILBOX_USBC_UTMIIDDIG,
    MAILBOX_USBC_PHY_DEBUG_OUT,
    MAILBOX_USBC_PHY_XCFG_RANGE,
    MAILBOX_USBC_PHY_XCFGO,
    MAILBOX_STOR_EMAC_RGMII_LINK_STATUS,
    MAILBOX_STOR_EMAC_RGMII_SPEED,
    MAILBOX_STOR_EMAC_RGMII_DUPLEX_OUT,
    MAILBOX_STOR_EMAC_MDIO_OUT,
    MAILBOX_STOR_EMAC_PFC_NEGOTIATE,
    MAILBOX_STOR_EMAC_RX_PFC_PAUSED,
    MAILBOX_STOR_EMAC_WOL,
    MAILBOX_STOR_EMAC_TSU_TIMER_H_CNT,
    MAILBOX_STOR_EMAC_TSU_TIMER_M_CNT,
    MAILBOX_STOR_EMAC_TSU_TIMER_L_CNT,
    MAILBOX_STOR_EMAC_TSU_TIMER_CMP_VAL,
} mailbox_state_t;

typedef struct
{
    uint32_t lock_range_min : 3;
    uint32_t reserve0 : 1;
    uint32_t lock_range_max : 3;
    uint32_t reserve1 : 1;
    uint32_t fine_tune_num : 3;
    uint32_t reserve2 : 1;
    uint32_t coarse_tune_num : 3;
    uint32_t reserve3 : 17;
}mailbox_usb_phy_range_t;

typedef enum
{
    MAILBOX_INT_NUMBER0,
    MAILBOX_INT_NUMBER1,
    MAILBOX_INT_NUMBER2,
    MAILBOX_INT_NUMBER3,
    MAILBOX_INT_NUMBER4,
    MAILBOX_INT_NUMBER5,
    MAILBOX_INT_NUMBER6,
    MAILBOX_INT_NUMBER7,
    MAILBOX_INT_NUMBER8,
    MAILBOX_INT_NUMBER9,
    MAILBOX_INT_NUMBER10,
    MAILBOX_INT_NUMBER11,
    MAILBOX_INT_NUMBER12,
    MAILBOX_INT_NUMBER13,
    MAILBOX_INT_NUMBER14,
    MAILBOX_INT_NUMBER15,
    MAILBOX_INT_NUMBERMAX,
}mailbox_int_number_t;

typedef enum
{
    MAILBOX_LOCK_NUMBER0,
    MAILBOX_LOCK_NUMBER1,
    MAILBOX_LOCK_NUMBER2,
    MAILBOX_LOCK_NUMBER3,
    MAILBOX_LOCK_NUMBER4,
    MAILBOX_LOCK_NUMBER5,
    MAILBOX_LOCK_NUMBER6,
    MAILBOX_LOCK_NUMBER7,
    MAILBOX_LOCK_NUMBER8,
    MAILBOX_LOCK_NUMBER9,
    MAILBOX_LOCK_NUMBER10,
    MAILBOX_LOCK_NUMBER11,
    MAILBOX_LOCK_NUMBER12,
    MAILBOX_LOCK_NUMBER13,
    MAILBOX_LOCK_NUMBER14,
    MAILBOX_LOCK_NUMBER15,
    MAILBOX_LOCK_NUMBERMAX,
}mailbox_lock_number_t;

typedef enum
{
    MAILBOX_EMMC_BOOT_CTRL_00 = 0,
    MAILBOX_EMMC_BOOT_CTRL_01,
    MAILBOX_EMMC_BOOT_CTRL_02,
    MAILBOX_EMMC_BOOT_CTRL_10,
    MAILBOX_EMMC_BOOT_CTRL_11,
    MAILBOX_EMMC_BOOT_CTRL_12,
    MAILBOX_EMMC_BOOT_ADDR_L0,
    MAILBOX_EMMC_BOOT_ADDR_L1,
    MAILBOX_EMMC_BOOT_ADDR_L2,
    MAILBOX_EMMC_BOOT_ADDR_H0,
    MAILBOX_EMMC_BOOT_ADDR_H1,
    MAILBOX_EMMC_BOOT_ADDR_H2,
    MAILBOX_EMMC_BOOT_BLOCK_CTRL0,
    MAILBOX_EMMC_BOOT_BLOCK_CTRL1,
    MAILBOX_EMMC_BOOT_BLOCK_CTRL2,
    MAILBOX_EMMC_BOOT_POW_CLK_DLY0,
    MAILBOX_EMMC_BOOT_POW_CLK_DLY1,
    MAILBOX_EMMC_BOOT_POW_CLK_DLY2,
    MAILBOX_EMMC_BOOT_CLK_CMD_DLY0,
    MAILBOX_EMMC_BOOT_CLK_CMD_DLY1,
    MAILBOX_EMMC_BOOT_CLK_CMD_DLY2,
    MAILBOX_RESERVE0,
    MAILBOX_RESERVE1,
    MAILBOX_RESERVE2,
    MAILBOX_CPU_DSP_CFG0,
    MAILBOX_ETHERNET_CTRL,
    MAILBOX_RESERVE3,
    MAILBOX_RESERVE4,
    MAILBOX_RESERVE5,
    MAILBOX_WDT0_CTRL,
    MAILBOX_WDT1_CTRL,
    MAILBOX_WDT2_CTRL,

    MAILBOX_DDR_WCOBUF_CTL = 100,
    MAILBOX_QOS_CTRL0,
    MAILBOX_QOS_CTRL1,
    MAILBOX_QOS_CTRL2,
    MAILBOX_QOS_CTRL3,
    MAILBOX_QOS_CTRL4,
    MAILBOX_NOC_WR_BUFFERABLE_CTRL,
    MAILBOX_I2C2AXI_SPIKE_TH,
    MAILBOX_SD0_HOST_BOOT_ACK,
    MAILBOX_SD0_HOST_BOOT_DONE,
    MAILBOX_SD0_HOST_BOOT_ERR,
    MAILBOX_SD1_HOST_BOOT_ACK,
    MAILBOX_SD1_HOST_BOOT_DONE,
    MAILBOX_SD1_HOST_BOOT_ERR,
    MAILBOX_SD2_HOST_BOOT_ACK,
    MAILBOX_SD2_HOST_BOOT_DONE,
    MAILBOX_SD2_HOST_BOOT_ERR,
    MAILBOX_SSI_SLEEP,
    MAILBOX_UART_LP_REQ_SCLK,
    MAILBOX_UART_LP_REQ_PCLK,
    MAILBOX_USB_PHY_UTMI_LINESTATE,
    MAILBOX_USB_PHY_DEBUG_SEL,
    MAILBOX_USB_XCFGI_H,
    MAILBOX_USB_XCFGI_M,
    MAILBOX_USB_XCFGI_L,
    MAILBOX_EMAC_TX_PAUSE,
    MAILBOX_EMAC_TX_PAUSE_ZERO,
    MAILBOX_EMAC_TX_PFC_SEL,
    MAILBOX_EMAC_TX_PFC_PAUSE,
    MAILBOX_EMAC_TX_PFC_PAUSE_ZERO,
} mailbox_other_ctrl_t;

extern volatile mailbox_t* const mailbox;

#define mailbox_int_reset_all()             do{mailbox->cpu2dsp_int_en |= MAILBOX_INT_RST; mailbox->cpu2dsp_int_en &= ~MAILBOX_INT_RST;}while(0);

#define mailbox_cpu2dsp_int_enable()        do{ mailbox->cpu2dsp_int_en = (0xFFFF << 16) | MAILBOX_INT_EN; } while(0);
#define mailbox_cpu2dsp_int_disable()       do{ mailbox->cpu2dsp_int_en = 0; }while(0);
//#define mailbox_cpu2dsp_int_reset()         do{ mailbox->cpu2dsp_int_en = MAILBOX_INT_RST; mailbox->cpu2dsp_int_en = 0; } while(0);
#define mailbox_cpu2dsp_send_int(num)       do{ mailbox->cpu2dsp_int_set = num; }while(0);
#define mailbox_cpu2dsp_clear_int(num)      do{ mailbox->cpu2dsp_int_clr = num; }while(0);
#define mailbox_cpu2dsp_get_status()        (mailbox->cpu2dsp_int_status)
#define mailbox_cpu2dsp_get_int_status(num) ((mailbox->cpu2dsp_int_status >> (num * 2)) & 0x3U)
#define mailbox_cpu2dsp_get_err()           (mailbox->cpu2dsp_int_err_status)
#define mailbox_cpu2dsp_get_underflow(num)  ((mailbox->cpu2dsp_int_err_status >> num) & 0x1U)
#define mailbox_cpu2dsp_get_overflow(num)   ((mailbox->cpu2dsp_int_err_status >> (num + 16)) & 0x1U)

#define mailbox_dsp2cpu_int_enable()        do{ mailbox->dsp2cpu_int_en = (0xFFFF << 16) | MAILBOX_INT_EN; } while(0);
#define mailbox_dsp2cpu_int_disable()       do{ mailbox->dsp2cpu_int_en = 0; }while(0);
//#define mailbox_dsp2cpu_int_reset()         do{ mailbox->dsp2cpu_int_en = MAILBOX_INT_RST; } while(0);
#define mailbox_dsp2cpu_send_int(num)       do{ mailbox->dsp2cpu_int_set = num; }while(0);
#define mailbox_dsp2cpu_clear_int(num)      do{ mailbox->dsp2cpu_int_clr = num; }while(0);
#define mailbox_dsp2cpu_get_status()        (mailbox->dsp2cpu_int_status)
#define mailbox_dsp2cpu_get_int_status(num) ((mailbox->dsp2cpu_int_status >> (num * 2)) & 0x3U)
#define mailbox_dsp2cpu_get_err()           (mailbox->dsp2cpu_int_err_status)
#define mailbox_dsp2cpu_get_underflow(num)  ((mailbox->dsp2cpu_int_err_status >> num) & 0x1U)
#define mailbox_dsp2cpu_get_overflow(num)   ((mailbox->dsp2cpu_int_err_status >> (num + 16)) & 0x1U)

void mailbox_set_int_direction(maixbox_int_t int_type, mailbox_int_dir_t dir);

uint32_t mailbox_get_state(mailbox_state_t state);
void mailbox_set_usbc_phy_xcfg_range(mailbox_usb_phy_range_t range);

void mailbox_set_other_ctrl(mailbox_other_ctrl_t ctrl, uint32_t val);
uint32_t mailbox_get_other_ctrl(mailbox_other_ctrl_t ctrl);

int mailbox_lock(mailbox_lock_number_t lock_num, uint32_t wait_us);
void mailbox_unlock(mailbox_lock_number_t lock_num);
#endif