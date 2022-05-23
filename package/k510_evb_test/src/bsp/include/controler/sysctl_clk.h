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
#ifndef __SYSCTL_CLK_H__
#define __SYSCTL_CLK_H__

/* created by hukai */

#include <stdint.h>
#include <stdbool.h>
#include "platform.h"

#define SYSCTL_CLK_BASE_ADDR    (SYSCTL_BASE_ADDR + 0x1000)

typedef struct sysctl_clk {
    volatile uint32_t ax25m_clk_cfg;        /* 0x00 */
    volatile uint32_t ax25m_mtimer_clk_cfg; /* 0x04 */
    volatile uint32_t reserved0[2];         /* 0x08 0x0c*/
    volatile uint32_t ax25p_clk_cfg;        /* 0x10 */
    volatile uint32_t ax25p_mtimer_clk_cfg; /* 0x14 */
    volatile uint32_t reserved1[2];         /* 0x18 0x1c*/
    volatile uint32_t ai_gnne_aclk_cfg;     /* 0x20 */
    volatile uint32_t ai_sysclk_cfg;        /* 0x24 */
    volatile uint32_t gnne_sysclk_cfg;      /* 0x28 */
    volatile uint32_t reserved2[4];         /* 0x2c 0x30 0x34 0x38*/
    volatile uint32_t i2c2axi_cfg;          /* 0x3c */
    volatile uint32_t noc_clk_cfg;          /* 0x40 */
    volatile uint32_t reserved3[3];         /* 0x44 0x48 0x4c */
    volatile uint32_t peri_sys_bus_clk_cfg; /* 0x50 */
    volatile uint32_t peri_sys_bus_clk_en;  /* 0x54 */
    volatile uint32_t reserved4;            /* 0x58 */
    volatile uint32_t uart0_sclk_cfg;       /* 0x5c */
    volatile uint32_t uart1_sclk_cfg;       /* 0x60 */
    volatile uint32_t uart2_sclk_cfg;       /* 0x64 */
    volatile uint32_t uart3_sclk_cfg;       /* 0x68 */
    volatile uint32_t reserved5[1];         /* 0x6c */
    volatile uint32_t i2s2_sclk_cfg;        /* 0x70 */
    volatile uint32_t spi0_sclk_cfg;        /* 0x74 */
    volatile uint32_t spi1_sclk_cfg;        /* 0x78 */
    volatile uint32_t spi2_sclk_cfg;        /* 0x7c */
    volatile uint32_t spi3_sclk_cfg;        /* 0x80 */
    volatile uint32_t audif_sclk_cfg0;      /* 0x84 */
    volatile uint32_t audif_sclk_cfg1;      /* 0x88 */
    volatile uint32_t audif_devclk_cfg;     /* 0x8c */
    volatile uint32_t sec_sys_bus_clk;      /* 0x90 */
    volatile uint32_t sec_sys_bus_clk_en;   /* 0x94 */
    volatile uint32_t otp_clk_en;           /* 0x98 */
    volatile uint32_t reserved6[1];         /* 0x9c */
    volatile uint32_t sram_bus_clk_en;      /* 0xa0 */
    volatile uint32_t reserved7[3];         /* 0xa4 0xa8 0xac */
    volatile uint32_t soc_ctl_pclk_en;      /* 0xb0 */
    volatile uint32_t soc_i2c_pclk_en;      /* 0xb4 */
    volatile uint32_t i2c0_icclk_cfg;       /* 0xb8 */
    volatile uint32_t i2c1_icclk_cfg;       /* 0xbc */
    volatile uint32_t i2c2_icclk_cfg;       /* 0xc0 */
    volatile uint32_t i2c3_icclk_cfg;       /* 0xc4 */
    volatile uint32_t i2c4_icclk_cfg;       /* 0xc8 */
    volatile uint32_t i2c5_icclk_cfg;       /* 0xcc */
    volatile uint32_t i2c6_icclk_cfg;       /* 0xd0 */
    volatile uint32_t wdt0_tclk_cfg;        /* 0xd4 */
    volatile uint32_t wdt1_tclk_cfg;        /* 0xd8 */
    volatile uint32_t wdt2_tclk_cfg;        /* 0xdc */
    volatile uint32_t timer_tclk_src;       /* 0xe0 */
    volatile uint32_t timer_tclk_cfg0;      /* 0xe4 */
    volatile uint32_t timer_tclk_cfg1;      /* 0xe8 */
    volatile uint32_t vad_sclk_cfg;         /* 0xec */
    volatile uint32_t reserved8[4];         /* 0xf0 0xf4 0xf8 0xfc */
    volatile uint32_t stor_sys_bus_clk_en;  /* 0x100 */
    volatile uint32_t emac_trx_clk_cfg;     /* 0x104 */
    volatile uint32_t sd_card_clk_cfg;      /* 0x108 */
    volatile uint32_t sensor_clk_cfg;       /* 0x10c */
    volatile uint32_t isp_sys_pclk_en;      /* 0x110 */
    volatile uint32_t isp_sys_aclk_en;      /* 0x114 */
    volatile uint32_t disp_sys_pclk_en;     /* 0x118 */
    volatile uint32_t disp_sys_aclk_en;     /* 0x11c */
    volatile uint32_t tpg_pixel_clk_cfg;    /* 0x120 */
    volatile uint32_t csi0_pixel_clk_cfg;   /* 0x124 */
    volatile uint32_t csi1_pixel_clk_cfg;   /* 0x128 */
    volatile uint32_t csi2_pixel_clk_cfg;   /* 0x12c */
    volatile uint32_t csi3_pixel_clk_cfg;   /* 0x130 */
    volatile uint32_t disp_pixel_clk_cfg;   /* 0x134 */
    volatile uint32_t mfbc_clk_cfg;         /* 0x138 */
    volatile uint32_t csi0_sys_clk_cfg;     /* 0x13c */
    volatile uint32_t csi1_sys_clk_cfg;     /* 0x140 */
    volatile uint32_t csi2_sys_clk_cfg;     /* 0x144 */
    volatile uint32_t csi3_sys_clk_cfg;     /* 0x148 */
    volatile uint32_t dsi_sys_clk_cfg;      /* 0x14c */
    volatile uint32_t h264_aclk_en;         /* 0x150 */
    volatile uint32_t usb_clk_en;           /* 0x154 */
    volatile uint32_t mipi_txdphy_clk_en;   /* 0x158 */
    volatile uint32_t mipi_rxdphy_clk_en;   /* 0x15c */
    volatile uint32_t mem_ctl_cmd_fifo;     /* 0x160 */
    volatile uint32_t mem_ctl_cmd_fifo_state;/* 0x164 */
    volatile uint32_t mem_ctl_clk_cfg;      /* 0x168 */
    volatile uint32_t mem_ctl_dfs_cfg;      /* 0x16c */
} sysctl_clk_t;

/* App should consider i2s master clock. K510(i2s_slave) <--clock-- device(i2s master) */
typedef enum{
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /***********************************************ROOT******************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* clock root */
    /* sysctl_boot clk tree
       osc25m-----     ------>|-->pll0----->|--------->pll0      clk output--->to sysctl_clock module
                              |             |--div2--->pll0_div2 clk output--->to sysctl_clock module
                              |             |--div3--->pll0_div3 clk output--->to sysctl_clock module
                              |             |--div4--->pll0_div4 clk output--->to sysctl_clock module
                              |
                              |-->pll1----->|--------->pll1      clk output--->to sysctl_clock module
                              |             |--div2--->pll1_div2 clk output--->to sysctl_clock module
                              |             |--div3--->pll1_div3 clk output--->to sysctl_clock module
                              |             |--div4--->pll1_div4 clk output--->to sysctl_clock module
                              |
                              |-->pll2----->|--------->pll2      clk output--->to sysctl_clock module
                              |             |--div2--->pll2_div2 clk output--->to sysctl_clock module
                              |             |--div3--->pll2_div3 clk output--->to sysctl_clock module
                              |             |--div4--->pll2_div4 clk output--->to sysctl_clock module
                              |
                              |-->pll3----->|--------->pll3      clk output--->to sysctl_clock module
                              |             |--div2--->pll3_div2 clk output--->to sysctl_clock module
                              |             |--div3--->pll3_div3 clk output--->to sysctl_clock module
                              |             |--div4--->pll3_div4 clk output--->to sysctl_clock module
                              |
                              |----------------------------------------------->to sysctl_clock module

       osc32k----------------------------------------------------------------->to sysctl_clock module
    */
    SYSCTL_CLK_ROOT_OSC_IN0 = 0,    /* 25M */
    SYSCTL_CLK_ROOT_OSC_IN1,        /* 32K */
    SYSCTL_CLK_ROOT_PLL0,           /* 1G */
    SYSCTL_CLK_ROOT_PLL0_DIV_2,     /* 500M */
    SYSCTL_CLK_ROOT_PLL0_DIV_3,     /* 333M */
    SYSCTL_CLK_ROOT_PLL0_DIV_4,     /* 250M */
    SYSCTL_CLK_ROOT_PLL1,           /* 1.333G */
    SYSCTL_CLK_ROOT_PLL1_DIV_2,     /* 666M */
    SYSCTL_CLK_ROOT_PLL1_DIV_3,     /* 444M */
    SYSCTL_CLK_ROOT_PLL1_DIV_4,     /* 333M */
    SYSCTL_CLK_ROOT_PLL2,           /* 2.376G */
    SYSCTL_CLK_ROOT_PLL2_DIV_2,     /* 1.188G */
    SYSCTL_CLK_ROOT_PLL2_DIV_3,     /* 792M */
    SYSCTL_CLK_ROOT_PLL2_DIV_4,     /* 594M */
    SYSCTL_CLK_ROOT_PLL3,           /* 3.2G */
    SYSCTL_CLK_ROOT_PLL3_DIV_2,     /* 1.6G */
    SYSCTL_CLK_ROOT_PLL3_DIV_3,     /* 1.066G */
    SYSCTL_CLK_ROOT_PLL3_DIV_4,     /* 800M */
    SYSCTL_CLK_ROOT_MAX,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************AX25MP*******************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* ax25mp clock tree
                  +-+
      pll2_div3-->|M \         |---GATE--->core0 clk
           pll0-->|U |-->DIV-->|---GATE--->core1 clk
      pll2_div2-->|X /         |---GATE--->core0 data cache clk
                  +-+          |---GATE--->core1 data cache clk
                               |---GATE--->noc & mctl p0 axi clk

     1. ax25mp_src              --> MUX&DIV
     2. ax25mp_core0            --> core0 clk gate
     3. ax25mp_core1            --> core1 clk gate
     4. ax25mp_core0_dc         --> core0 data cache clk gate
     5. ax25mp_core1_dc         --> core1 data cache clk gate
     6. ax25mp_noc_mctl         --> ddr controller p0 & noc AXI clock (for AX25MP)
    */
    SYSCTL_CLK_AX25M_SRC,           /* default 500MHz ----> select pll0(1GHz), div 6/12 */


    SYSCTL_CLK_AX25M_CORE_0,
    SYSCTL_CLK_AX25M_CORE_1,        /* as same as core 0 */
    SYSCTL_CLK_AX25M_CORE_0_DC,     /* as same as core 0 */
    SYSCTL_CLK_AX25M_CORE_1_DC,     /* as same as core 0 */
    SYSCTL_CLK_AX25M_MCTL,          
    /* ax25m mtimer clock tree
                    +-+
      osc32k     -->|M \         
      osc25m_gate-->|U |-->DIV-->|---GATE--->ax25m mtimer clk
                    |X /
                    +-+
    */
    SYSCTL_CLK_AX25M_MTIMER,        /* defualt 1.25MHz ---> select OSC25M, div 20*/

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************AX25P********************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* ax25p clock tree
                  +-+
      pll2_div3-->|M \         |---GATE--->core clk
           pll0-->|U |-->DIV-->|---GATE--->local memory clk
                  |X /
                  +-+

     1. ax25p_src               --> MUX&DIV
     2. ax25p_core              --> core clk gate
     3. ax25p_lm                --> local memory gate
    */
    SYSCTL_CLK_AX25P_SRC,           /* mux&div */
    SYSCTL_CLK_AX25P_CORE,          /* gate */
    SYSCTL_CLK_AX25P_LM,            /* gate */

    /* ax25p mtimer clock tree
                    +-+
      osc32k     -->|M \         
      osc25m_gate-->|U |-->DIV-->|---GATE--->ax25p mtimer clk
                    |X /
                    +-+

     1. ax25p_mtimer            --> MUX&DIV&GATE
    */
    SYSCTL_CLK_AX25P_MTIMER,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************GNNE*********************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* gnne system clock tree
                  +-+
      pll0_div2-->|M \
                  |U |-->DIV-->|---GATE--->gnne system clk
      pll1_div2-->|X /
                  +-+

     1. gnne_sys_clk_mux_div_gate               --> MUX&DIV&GATE
    */
    SYSCTL_CLK_GNNE_SYS,
    /* gnne axi clock tree
                  +-+
      pll0_div2-->|M \         |---GATE--->gnne&noc axi clk
                  |U |-->DIV-->|
      pll1_div2-->|X /         |---GATE--->gnne mctl_p0 & noc axi clk
                  +-+

     1. gnne_axi_noc_mctl_p1_mux_div            --> MUX&DIV
     2. gnne_axi_noc_gate                       --> gnne axi noc gate
     3. gnne_noc_axi_mctl_p1_gate               --> gnne noc&mctl_p1 gate
    */
    SYSCTL_CLK_GNNE_AXI,
    SYSCTL_CLK_GNNE_AXI_NOC,
    SYSCTL_CLK_GNNE_AXI_MCTL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************NOC0*********************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* noc clk0 tree
                  +-+
      pll0_div2-->|M \         |---DIV1--->noc_clk0--->|----GATE--->peri dma axi clk
                  |U |-->DIV-->|                       |----GATE--->sys dma axi clk
      pll1_div2-->|X /         |                       |----GATE--->sram0 axi clk
                  +-+          |                       |----GATE--->sram1 axi clk
                               |                       |----GATE--->noc&mctl_p3 clk
                               |
                               |-DIV2->noc_clk0_div2-->|----GATE--->mctl_ahb_config
                               |                       |----GATE--->usb_ahb
                               |                       |----GATE--->sd_slv_ahb
                               |
                               |-DIV3->noc_clk0_div3-->|----GATE--->sd0-2_ahb
                               |                       |----GATE--->emca_ahb
                               |                       |----GATE--->peridma_ahb
                               |                       |----GATE--->sysdma_ahb
                               |
                               |-DIV4->noc_clk0_div4-->|----GATE--->wdt0-2_ahb
                                                       |----GATE--->timer_ahb
                                                       |----GATE--->rtc_ahb
                                                       |----GATE--->gpio_ahb
                                                       |----GATE--->iomux_ahb
                                                       |----GATE--->i2c0-6_ahb
                                                       |----GATE--->pwm_ahb
                                                       |----GATE--->mailbox_ahb
                                                       |----GATE--->vad_ahb

     1. noc_clk0_mux_div                        --> MUX&DIV&DIV1 noc_clk0(div1)
     2. noc_clk0_div2                           --> noc_clk0 div2
     3. noc_clk0_div2                           --> noc_clk0 div3
     4. noc_clk0_div4                           --> noc_clk0 div4

     5. peri_dma_axi_gate                       --> peri dma axi gate,              clk source noc_clk0_mux_div.
     6. sys_dma_axi_gate                        --> peri dma axi gate,              clk source noc_clk0_mux_div.
     7. sram0_axi_gate                          --> sram0 axi gate,                 clk source noc_clk0_mux_div.
     8. sram1_axi_gate                          --> sram1 axi gate,                 clk source noc_clk0_mux_div.
     9. noc_clk0_noc_axi_mctl_p3_gate           --> noc clock0 & mctl_p3 gate,      clk source noc_clk0_mux_div.

     10.mctl_noc_ahb_mctl_gate                  --> noc-ahb-mctl config bus gate,   clk source noc_clk0_div2.
     11.usb_ahb_gate                            --> noc-ahb-usb config bus gate,    clk source noc_clk0_div2.
     12.sd_slv_ahb_gate                         --> noc-ahb-sd-slv config bus gate, clk source noc_clk0_div2.

     13.sd0_ahb_gate                            --> noc-ahb-sd0 config bus gate,    clk source noc_clk0_div3.
     14.sd1_ahb_gate                            --> noc-ahb-sd1 config bus gate,    clk source noc_clk0_div3.
     15.sd2_ahb_gate                            --> noc-ahb-sd2 config bus gate,    clk source noc_clk0_div3.
     15.emac_ahb_gate                           --> noc-ahb-emac config bus gate,   clk source noc_clk0_div3.
     16.peri_dma_ahb_gate                       --> noc-ahb-peridma config bus gate,clk source noc_clk0_div3.
     17.sys_dma_ahb_gate                        --> noc-ahb-sysdma config bus gate, clk source noc_clk0_div3.

     18.wdt0_ahb_gate                           --> noc-apb-wdt0 config bus gate,   clk source noc_clk0_div4.
     19.wdt1_ahb_gate                           --> noc-apb-wdt1 config bus gate,   clk source noc_clk0_div4.
     20.wdt2_ahb_gate                           --> noc-apb-wdt2 config bus gate,   clk source noc_clk0_div4.
     21.timer_ahb_gate                          --> noc-apb-timer config bus gate,  clk source noc_clk0_div4.
     22.rtc_ahb_gate                            --> noc-apb-rtc config bus gate,    clk source noc_clk0_div4.
     23.gpio_ahb_gate                           --> noc-apb-gpio config bus gate,   clk source noc_clk0_div4.
     24.iomux_ahb_gate                          --> noc-apb-iomux config bus gate,  clk source noc_clk0_div4.
     25.i2c(0-6)_ahb_gate                       --> noc-apb-i2c config bus gate,    clk source noc_clk0_div4
     26.pwm_ahb_gate                            --> noc-apb-pwm config bus gate,    clk source noc_clk0_div4.
     27.mailbox_ahb_gate                        --> noc-apb-mailbox config bus gate,clk source noc_clk0_div4.
     28.vad_ahb_gate                            --> noc-apb-vad config bus gate,    clk source noc_clk0_div4.
    */
    SYSCTL_CLK_NOC_CLK_0,           /* defualt 500MHz ---> select pll0_div_2 */
    SYSCTL_CLK_NOC_CLK_0_DIV_2,
    SYSCTL_CLK_NOC_CLK_0_DIV_3,
    SYSCTL_CLK_NOC_CLK_0_DIV_4,

    SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI,
    SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI,
    SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI,
    SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI,
    SYSCTL_CLK_NOC_CLK_0_AXI_P3,

    SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB,

    SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB,
    SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB,

    SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB,
    SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB,


    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************NOC1*********************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* noc_clk1 tree
      pll0_div2---->DIV-------->|----GATE--->noc_clk1_axi_mctl_p2_clk_gate
                                |----GATE--->h264_axi_gate
                                |
                                |----noc_peri_apb_div-->|----GATE--->uart(0-3)_apb_gate
                                |                       |----GATE--->i2s_s_apb_gate
                                |                       |----GATE--->audio_apb_gate
                                |
                                |----noc_peri_ahb_div-->|----GATE--->spi_0-3_ahb_gate
                                |
                                |----GATE--->vo_axi_gate
                                |----GATE--->twod_axi_gate
                                |----GATE--->mfbc_axi_gate
                                |----GATE--->vi_axi_gate
                                |----GATE--->isp_f2k_axi_gate
                                |----GATE--->isp_r2k_axi_gate
                                |----GATE--->isp_tof_axi_gate
                                |
                                |
                                |---noc_clk1_div4-->|----GATE--->csi_0-3_apb_gate
                                                    |----GATE--->isp_f2k_apb_gate
                                                    |----GATE--->isp_r2k_apb_gate
                                                    |----GATE--->isp_tof_apb_gate
                                                    |----GATE--->mfbc_apb_gate
                                                    |----GATE--->mipi_corner_apb_gate
                                                    |----GATE--->vi_apb_gate
    */
    SYSCTL_CLK_NOC_CLK_1,           /* defualt 500MHz ---> select pll0_div_2 */
    SYSCTL_CLK_NOC_CLK_1_AXI_MCTL,
    SYSCTL_CLK_NOC_CLK_1_H264_AXI,
    SYSCTL_CLK_NOC_CLK_1_VO_AXI,
    SYSCTL_CLK_NOC_CLK_1_TWOD_AXI,
    SYSCTL_CLK_NOC_CLK_1_MFBC_AXI,
    SYSCTL_CLK_NOC_CLK_1_VI_AXI,
    SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI,
    SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI,
    SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI,

    SYSCTL_CLK_NOC_CLK_1_PERI_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB,
    SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB,

    SYSCTL_CLK_NOC_CLK_1_PERI_AHB,
    SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB,
    SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB,
    SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB,
    SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB,

    SYSCTL_CLK_NOC_CLK_1_DIV_4,
    SYSCTL_CLK_NOC_CLK_1_CSI_0_APB,
    SYSCTL_CLK_NOC_CLK_1_CSI_1_APB,
    SYSCTL_CLK_NOC_CLK_1_CSI_2_APB,
    SYSCTL_CLK_NOC_CLK_1_CSI_3_APB,
    SYSCTL_CLK_NOC_CLK_1_F2K_APB,
    SYSCTL_CLK_NOC_CLK_1_R2K_APB,
    SYSCTL_CLK_NOC_CLK_1_TOF_APB,
    SYSCTL_CLK_NOC_CLK_1_MFBC_APB,
    SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB,
    SYSCTL_CLK_NOC_CLK_1_VI_APB,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************DISPLAY*********************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* display system&apb clk tree

      pll1_div4--------->DIV--> display system clk---->|----GATE--->dsi_apb_clk
                                                       |----GATE--->dsi_system_clk
                                                       |----GATE--->vo_apb_clk
                                                       |----GATE--->twod_apb_clk
                                                       |----GATE--->bt1120_apb_clk

     1. display_sys_and_apb_clk_div             --> DIV
     2. dsi_apb_clk_gate                        --> dsi apb clk gate
     3. dsi_system_clk_gate                     --> dsi system clk gate
     4. vo_apb_clk_gate                         --> video out apb clk gate
     5. twod_apb_clk_gate
     6. bt1120_apb_clk_gate
    */
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV,
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB,
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM,
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB,
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB,
    SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************CSI SYS CLK**************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* csi0/1 system clk tree

      pll1_div4--------->DIV--> csi0 system clk
      pll1_div4--------->DIV--> csi1 system clk

    */
    SYSCTL_CLK_CSI_0_SYSTEM,
    SYSCTL_CLK_CSI_1_SYSTEM,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************CSI0 PIXEL***************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* csi0 clock tree
                    +-+
                    |M \         
      pll2_div4---->|U |-->DIV-->|---GATE--->csi0_pixel_clk
                    |X /
                    +-+

     1. csi0_pixel_clk                          --> DIV&GATE (only one parent)
    */
    SYSCTL_CLK_CSI_0_PIXEL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************CSI1 PIXEL***************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* csi1 clock tree
                    +-+
      pll2_div4---->|M \         
      pll2_div3---->|U |-->DIV-->|---GATE--->csi1_pixel_clk
      pll0     ---->|X /
      pll1     ---->+-+

     1. csi1_pixel_clk                          --> MUX&DIV&GATE
    */
    SYSCTL_CLK_CSI_1_PIXEL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************TPG PIXEL****************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* tpg clock tree
                    +-+
                    |M \         
      pll2_div4---->|U |-->DIV-->|---GATE--->tpg_pixel_clk
                    |X /
                    +-+

     1. tpg_pixel_clk                          --> DIV&GATE (only one parent)
    */
    SYSCTL_CLK_TPG_PIXEL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************DISPLAY PIXEL************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* display pixel clock tree
                    +-+
      pll2_div4---->|M \         
      pll2_div3---->|U |-->DIV-->|---GATE--->display_pixel_clk
      pll0     ---->|X /
      pll1     ---->+-+

     1. display_pixel_clk                       --> MUX&DIV&GATE
    */
    SYSCTL_CLK_DISPLAY_PIXEL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************AUDIO OUT SERIAL*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* audio out serial clock tree
      pll0_div0---->DIV---->GATE--->----INVERT--->audio clk out
    */
    SYSCTL_CLK_AUDIO_OUT_SERIAL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************AUDIO IN SERIAL CLK******************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* audio in serial clock tree
      pll0_div0---->DIV---->GATE--->----INVERT--->audio clk in
    */
    SYSCTL_CLK_AUDIO_IN_SERIAL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************SDIO MASTER(system clock)************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* audio in serial clock tree
      pll1_div3---->DIV---->GATE--->----INVERT--->audio clk in
    */
    /* sd master clk fixed div 5 
       pll0 --> fixed div 5--> sd master clk --> gate --> sd_0_master_clk
                                             --> gate --> sd_1_master_clk
                                             --> gate --> sd_2_master_clk
    */
    SYSCTL_CLK_SD_MASTER,
    SYSCTL_CLK_SD_MASTER_SD_0,
    SYSCTL_CLK_SD_MASTER_SD_1,
    SYSCTL_CLK_SD_MASTER_SD_2,


    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************MIPI CLOCK***************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* mipi clock tree 
                    +-+
      pll2_div2---->|M \
      pll1     ---->|U |-->DIV-->|--->GATE--->txphy_ref_clock
                    |X /         |--->GATE--->rxphy_ref_clock
                    +-+

     osc25m_gate--------------------->GATE--->txphy_pll_clock
   */
    SYSCTL_CLK_MIPI_REF,
    SYSCTL_CLK_MIPI_REF_TXPHY_REF,
    SYSCTL_CLK_MIPI_REF_RXPHY_REF,
    SYSCTL_CLK_MIPI_REF_TXPHY_PLL,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************SECURITY AHB CLOCK*******************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* security ahb (for config) clock tree
      pll1_div3---->DIV---->GATE--->|----GATE--->otp_ahb
                                    |----GATE--->rom_ahb
                                    |----GATE--->sha_ahb
                                    |----GATE--->aes_ahb
                                    |----GATE--->rsa_ahb
                                    |----GATE--->puf_ahb
    */
    /* secure ahb clock register addr:0x94*/
    SYSCTL_CLK_SEC_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_PUF_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_OTP_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_ROM_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_RSA_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_AES_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    SYSCTL_CLK_SHA_HCLK,        /* default 222MHz ---> pll_div_3(444MHz)  div 2 */
    /* OTP work(system) clock register addr:0x98*/

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************DDR controller core CLOCK************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* ddr controller core clock tree
                    +-+
      pll1--------->|M \         
      pll2_div2---->|U |-->DIV-->|---GATE--->mctl_ddrc_clk
      pll3_div3---->|X /
      pll3_div4---->+-+
    */
    SYSCTL_CLK_DDR_CONTROLLER_CORE,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************EMAC loopback clock******************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* emac loopback clk tree
       pll0_div4 --> DIV--> gate --> emac_loopback
    */
    SYSCTL_CLK_EMAC_LOOPBACK,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************UART system clock********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* uart0-3 system clock tree
                    +-+
      osc25m_gate-->|M \         
      pll1_div4---->|U |-->DIV-->|---GATE--->uart_X_system_clock
                    |X /
                    +-+
    */
    /* uart0 work(system) clock register addr:0x5c*/
    SYSCTL_CLK_UART0_SCLK,          /* defalut 25MHz --->OSC25M div 1 */
    /* uart1 work(system) clock register addr:0x60*/
    SYSCTL_CLK_UART1_SCLK,          /* defalut 25MHz --->OSC25M div 1 */
    /* uart2 work(system) clock register addr:0x64*/
    SYSCTL_CLK_UART2_SCLK,          /* defalut 25MHz --->OSC25M div 1 */
    /* uart3 work(system) clock register addr:0x68*/
    SYSCTL_CLK_UART3_SCLK,          /* defalut 25MHz --->OSC25M div 1 */


    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************SPI system clock*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* spi0-2 system clock tree
                    +-+
      osc25m_gate-->|M \         
      pll0       -->|U |-->DIV-->|---GATE--->spi_0.1.3_system_clock
                    |X /
                    +-+
    */
    /* spi3 system clock tree
       osc25m_gate----> DIV ----> GATE --->spi_3_system_clock
    */
    /* spi0 work(system) clock register addr:0x74*/
    SYSCTL_CLK_SPI0_SCLK,           /* default 3.125MHz--->OSC25M div 8*/
    SYSCTL_CLK_SPI1_SCLK,
    SYSCTL_CLK_SPI2_SCLK,
    SYSCTL_CLK_SPI3_SCLK,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************OTP system clock*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* otp system clock tree
       osc25m_gate----> fixed div(2) ----> GATE --->otp_system_clock
    */
    SYSCTL_CLK_OTP_SCLK,        /* default 12.5MHz --> OSC25M div 2(hardware fixed)*/

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************I2C system clock*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* i2c0-6 sclk tree 
                    +-+
      pll0_div4  -->|M \
      osc25m_gate-->|U |-->DIV-->|---GATE--->i2c_0_sclk
                    |X /
                    +-+
    */
    SYSCTL_CLK_I2C0_SCLK,
    SYSCTL_CLK_I2C1_SCLK,
    SYSCTL_CLK_I2C2_SCLK,
    SYSCTL_CLK_I2C3_SCLK,
    SYSCTL_CLK_I2C4_SCLK,
    SYSCTL_CLK_I2C5_SCLK,
    SYSCTL_CLK_I2C6_SCLK,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************WDT system clock*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* wdt0 sclk tree 
      osc25m_gate--------->DIV----->GATE--->wdt_0_sclk
    */
    /* wdt0 work(tick) clock register addr:0xd4*/
    SYSCTL_CLK_WDT0_TCLK,       /* default 0.757M ----> OSC25M div 33 */
    /* wdt1 work(tick) clock register addr:0xd8*/
    SYSCTL_CLK_WDT1_TCLK,       /* default 0.757M ----> OSC25M div 33 */
    /* wdt2 work(tick) clock register addr:0xdc*/
    SYSCTL_CLK_WDT2_TCLK,       /* default 0.757M ----> OSC25M div 33 */

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************VAD system clock*********************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* vad sclk tree
       osc25m_gate------>DIV------>GATE----->vad seiral(sample) clock ----> phase(invert or not)---> vad sclk
    */
    SYSCTL_CLK_VAD_TCLK,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************timer system clock*******************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* timer x system clock tree 
                    +-+
      osc25m_gate-->|M \
      osc32k     -->|U |--->DIV-->|---GATE(all timer)--->timer_x_tick_clk(system clock)
                    |X /
                    +-+
    */
    SYSCTL_CLK_TIMER0_TCLK,
    SYSCTL_CLK_TIMER1_TCLK,
    SYSCTL_CLK_TIMER2_TCLK,
    SYSCTL_CLK_TIMER3_TCLK,
    SYSCTL_CLK_TIMER4_TCLK,
    SYSCTL_CLK_TIMER5_TCLK,

    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /********************************************usb clock****************************************************/
    /*********************************************************************************************************/
    /*********************************************************************************************************/
    /* usb clock tree 
        osc25m_gate---->|--->GATE----->usb phy core clk

        osc32k          |--->GATE----->usb wakeup clk
    */
    SYSCTL_CLK_USB_PHY_CORE,
    SYSCTL_CLK_USB_WAKEUP,

    /* 孤立节点 输入时钟使能 */
    SYSCTL_CLK_I2SS_SCLK,

    SYSCTL_CLK_NODE_MAX,
}sysctl_clk_node_e;

typedef enum
{
    SYSCTL_CLK_MUL_CHANGEABLE = 0,
    SYSCTL_CLK_DIV_CHANGEABLE = 1,
    SYSCTL_CLK_MUL_DIV_CHANGEABLE = 2,
}sysctl_clk_mul_div_methord_e;

/* 25M, 32K and PLL0-3 API ,这6个时钟是根时钟 */
/* 获取锁相环 bypass状态, 如果是bypas，则锁相环输出的是25M OSC时钟 */
bool sysctl_boot_get_root_clk_bypass(sysctl_clk_node_e clk);
void sysctl_boot_set_root_clk_bypass(sysctl_clk_node_e clk, bool enable);

/* Enable pll, enable 25M clock&pll */
/* 打开或者关闭 root时钟 针对锁相环和25M时钟 */
bool sysctl_boot_get_root_clk_en(sysctl_clk_node_e clk);
void sysctl_boot_set_root_clk_en(sysctl_clk_node_e clk, bool enable);

/* 获取锁相环锁定状态 */
bool sysctl_boot_get_root_clk_lock(sysctl_clk_node_e clk);

/* 获取root时钟频率 */
uint32_t sysctl_boot_get_root_clk_freq(sysctl_clk_node_e clk);

/* 设置锁相环时钟频率 计算公式 pll_out_freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1) */
bool sysctl_boot_set_root_clk_freq(sysctl_clk_node_e clk, uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv);

/* 下面的API是针对时钟树的trunk和leaf节点, 换言之,就是支持除了OSC25M, OSC32K和PLL0-PPL3之外的其他时钟 */
/* 设置时钟数上叶子节点时钟源, 请根据时钟树来设置, 很多时钟节点只有一个时钟源，因此设置会返回false */
bool sysctl_clk_set_leaf_parent(sysctl_clk_node_e leaf, sysctl_clk_node_e parent);
/* 获取时钟树上叶子节点时钟源 */
sysctl_clk_node_e sysctl_clk_get_leaf_parent(sysctl_clk_node_e leaf);

/* 设置时钟节点enable,注意:只设置本时钟节点的enable，不会设置上游时钟的enable。
   同linux kernel的区别: linux kernel clock framework 会自动设置上游时钟的enable，测试代码没有kernel框架，因此只设置本节点时钟的enable */

void sysctl_clk_set_leaf_en(sysctl_clk_node_e leaf, bool enable);

/* 获取本时钟节点的enable状态 */
bool sysctl_clk_get_leaf_en(sysctl_clk_node_e leaf);

/* 获取本时钟节点的分频系数 */
bool sysctl_clk_set_leaf_div(sysctl_clk_node_e leaf, uint32_t numerator, uint32_t denominator);

/* 获取本时钟节点的分频系数 */
double sysctl_clk_get_leaf_div(sysctl_clk_node_e leaf);

/* 设置本时钟节点的相位 */
bool sysctl_clk_set_phase(sysctl_clk_node_e leaf, uint32_t degree);

/* 获取本时钟节点的相位 */
uint32_t sysctl_clk_get_phase(sysctl_clk_node_e leaf);

/* calc clock freqency */
/* 计算当前时钟节点的频率, 这个API会搜索整个时钟路径，从时钟源开始计算每一级的分频，最终得出当前时钟频率 */
uint32_t sysctl_clk_get_leaf_freq(sysctl_clk_node_e leaf);

/* 辅助计算函数，本函数会根据父节点时钟/实际需要输出的时钟/分频配置方法 计算出最合适的分频系数 */
int sysctl_clk_find_approximate(uint32_t mul_min, 
                                     uint32_t mul_max, 
                                     uint32_t div_min, 
                                     uint32_t div_max, 
                                     sysctl_clk_mul_div_methord_e method,
                                     unsigned long rate, 
                                     unsigned long parent_rate,
                                     uint32_t *div, 
                                     uint32_t *mul);
#endif
