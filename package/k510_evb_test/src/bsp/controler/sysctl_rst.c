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
#include <stdbool.h>
#include "platform.h"
#include "sleep.h"
#include "sysctl_rst.h"

/* created by hukai */

volatile sysctl_rst_t* sysctl_rst = (volatile sysctl_rst_t*)SYSCTL_RST_BASE_ADDR;

static bool sysctl_reset_hw_done(volatile uint32_t *reset_reg, uint8_t reset_bit, uint8_t done_bit)
{
    *reset_reg |= (1 << done_bit);      /* clear done bit */
    usleep(100);
    *reset_reg |= (1 << reset_bit);     /* set reset bit */
    usleep(100);
    /* check done bit */
    if(*reset_reg & (1 << done_bit))
        return true;
    else
        return false;
}

static bool sysctl_reset_sw_done(volatile uint32_t *reset_reg, uint8_t reset_bit, uint32_t reset_en)
{
    *reset_reg = (1 << reset_bit) | (1 << reset_en);     /* set reset bit */
    usleep(100);
    *reset_reg = (1 << reset_en);    /* clear reset bit */
    usleep(100);
    return true;
}

bool sysctl_reset(sysctl_reset_e reset)
{
    switch (reset) 
    {
        case SYSCTL_RESET_AX25P_CORE:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->ax25p_rst_ctl,0,30);
        case SYSCTL_RESET_AX25P_LOCAL_MEMORY:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->ax25p_rst_ctl,1,31);
        case SYSCTL_RESET_AI:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->ai_rst_ctl,0,31);
        case SYSCTL_RESET_GNNE:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->gnne_rst_ctl,0,31);

        case SYSCTL_RESET_I2C0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,0, 16);
        case SYSCTL_RESET_I2C1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,1, 17);
        case SYSCTL_RESET_I2C2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,2, 18);
        case SYSCTL_RESET_I2C3:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl1,0, 16);
        case SYSCTL_RESET_I2C4:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl1,1, 17);
        case SYSCTL_RESET_I2C5:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl1,2, 18);
        case SYSCTL_RESET_I2C6:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl1,3, 19);
        case SYSCTL_RESET_WDT0:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,3, 19);
        case SYSCTL_RESET_WDT1:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,4, 20);
        case SYSCTL_RESET_WDT2:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,5, 21);
        case SYSCTL_RESET_TIMER:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,6, 22);
        case SYSCTL_RESET_RTC:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,7, 23);
        case SYSCTL_RESET_GPIO:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,8, 24);
        case SYSCTL_RESET_IOMUX:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,9, 25);
        case SYSCTL_RESET_MAILBOX:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,10, 26);
        case SYSCTL_RESET_PWM:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,11, 27);
        case SYSCTL_RESET_VAD:
            return sysctl_reset_sw_done((volatile uint32_t *)&sysctl_rst->soc_ctl_rst_ctl0,11, 28);

        case SYSCTL_RESET_UART0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->uart0_rst_ctl,0,31);
        case SYSCTL_RESET_UART1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->uart1_rst_ctl,0,31);
        case SYSCTL_RESET_UART2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->uart2_rst_ctl,0,31);
        case SYSCTL_RESET_UART3:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->uart3_rst_ctl,0,31);
        case SYSCTL_RESET_I2S2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->i2s2_rst_ctl,0,31);
        case SYSCTL_RESET_SPI0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi0_rst_ctl,0,31);
        case SYSCTL_RESET_SPI1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi1_rst_ctl,0,31);
        case SYSCTL_RESET_SPI2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi2_rst_ctl,0,31);
        case SYSCTL_RESET_SPI3:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->spi3_rst_ctl,0,31);
        case SYSCTL_RESET_AUDIF:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->audif_rst_ctl,0,31);
        case SYSCTL_RESET_SHA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sha_rst_ctl,0,31);
        case SYSCTL_RESET_AES:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->aes_rst_ctl,0,31);
        case SYSCTL_RESET_RSA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->rsa_rst_ctl,0,31);
        case SYSCTL_RESET_ROM:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->rom_rst_ctl,0,31);
        case SYSCTL_RESET_OTP:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->otp_rst_ctl,0,31);
        case SYSCTL_RESET_PUF:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->otp_rst_ctl,0,31);
        case SYSCTL_RESET_SDC0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc0_rst_ctl,0,31);
        case SYSCTL_RESET_SDC1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc1_rst_ctl,0,31);
        case SYSCTL_RESET_SDC2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdc2_rst_ctl,0,31);
        case SYSCTL_RESET_PERI_DMA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->peri_dma_rst_ctl,0,31);
        case SYSCTL_RESET_SYS_DMA:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sys_dma_rst_ctl,0,31);
        case SYSCTL_RESET_EMAC:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->emac_rst_ctl,0,31);
        case SYSCTL_RESET_SDIO_SLAVE:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sdio_s_rst_ctl,0,31);
        case SYSCTL_RESET_MCTL:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->mctl_rst_ctl,0,31);
        case SYSCTL_RESET_SRAM0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sram0_rst_ctl,0,31);
        case SYSCTL_RESET_SRAM1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sram1_rst_ctl,0,31);
        case SYSCTL_RESET_ISP_F4K:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_f4k_rst_ctl,0,31);
        case SYSCTL_RESET_ISP_F2K:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_f2k_rst_ctl,0,31);
        case SYSCTL_RESET_ISP_R2K:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_r2k_rst_ctl,0,31);
        case SYSCTL_RESET_ISP_TOF:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->isp_tof_rst_ctl,0,31);
        case SYSCTL_RESET_CSI0:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->csi0_rst_ctl,0,31);
        case SYSCTL_RESET_CSI1:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->csi1_rst_ctl,0,31);
        case SYSCTL_RESET_CSI2:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->csi2_rst_ctl,0,31);
        case SYSCTL_RESET_CSI3:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->csi3_rst_ctl,0,31);
        case SYSCTL_RESET_SENSOR:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->sensor_rst_ctl,0,31);
        case SYSCTL_RESET_VI:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->vi_rst_ctl,0,31);
        case SYSCTL_RESET_MFBC:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->mfbc_rst_ctl,0,31);
        case SYSCTL_RESET_DSI:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->dsi_rst_ctl,0,31);
        case SYSCTL_RESET_BT1120:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->bt1120_rst_ctl,0,31);
        case SYSCTL_RESET_TWOD:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->twod_rst_ctl,0,31);
        case SYSCTL_RESET_VO:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->vo_rst_ctl,0,31);
        case SYSCTL_RESET_H264:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->h264_rst_ctl,0,31);
        case SYSCTL_RESET_USB:
            return sysctl_reset_hw_done((volatile uint32_t *)&sysctl_rst->usb_rst_ctl,0,31);
        default:
            return false;
    }
}

/* time = timx(x=0,1,2) * 2us, please see sys_ctl_reg.xlsx 
   tim0/1/2 for 3 step reset(clock toggle)
   tim1/2 for 2 step reset(clock gate)
*/
bool sysctl_set_reset_time(sysctl_reset_time_e reset, uint32_t tim0, uint32_t tim1, uint32_t tim2)
{
     switch (reset) {
        case SYSCTL_RESET_TIME_AX25M:
        {
            if((tim0 > 0x1F) || (tim1 > 0xF) || (tim2 > 0xF)) /* tim0 5 bits */
            {
                return false;
            }
            else
            {
                sysctl_rst->ax25m_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 12) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AX25P:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) || (tim2 > 0xF)) /* tim0 4 bits */
            {
                return false;
            }
            else
            {
                sysctl_rst->ax25p_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 12) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AI:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->ai_rst_tim = ((tim1 << 4) | (tim2 << 8) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_GNNE:
        {
            if((tim1 > 0xF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->gnne_rst_tim = ((tim1 << 4) | (tim2 << 8) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_PERI_SYS:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->peri_sys_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_UART:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->uart_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_I2S_SLAVE:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->i2s2_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SPI:
        {
            if((tim1 > 0x3F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->spi_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AUDIF:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->audif_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SEC_SYS:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sec_sys_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SHA:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sha_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_AES:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->aes_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_RSA:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->rsa_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_ROM:
        {
            if((tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->rom_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_OTP:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->otp_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_PUF:
        {
            if((tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->puf_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_STOR_SYS:
        {
            if((tim0 > 0xFF) || (tim1 > 0xFF) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->stor_sys_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SDCTL:
        {
            if((tim0 > 0x1F) || (tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sdctl_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DMAC:
        {
            if((tim1 > 7) || (tim2 > 7))
            {
                return false;
            }
            else
            {
                sysctl_rst->dmac_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_EMAC:
        {
            if((tim0 > 0xFF) || (tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->emac_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SDIO_SLAVE:
        {
            if((tim0 > 0xFF) || (tim1 > 0x1F) || (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sdio_s_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_MCTL:
        {
            if((tim0 > 0xF) || (tim1 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->mctl_rst_tim = ((tim0 << 0) | (tim1 << 8) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SRAM0:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sram0_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SRAM1:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sram1_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_ISP_SYS:
        {
            if((tim0 > 0xFF) || (tim1 > 0xFF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->isp_sys_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_ISP_MODULE:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->isp_module_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_CSI:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->csi_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_SENSOR:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->sensor_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_VI:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->vi_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_MFBC:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->mfbc_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        
        case SYSCTL_RESET_TIME_DISP_SYS:
        {
            if((tim0 > 0xFF) || (tim1 > 0xFF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->disp_sys_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_DSI:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->dsi_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_BT1120:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->bt1120_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_TWOD:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->twod_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_VO:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->vo_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_H264:
        {
            if((tim0 > 0xF) || (tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->h264_rst_tim = ((tim0 << 0) | (tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_RESET_TIME_USB:
        {
            if((tim1 > 0xF) | (tim2 > 0xF))
            {
                return false;
            }
            else
            {
                sysctl_rst->usb_rst_tim = ((tim1 << 8) | (tim2 << 16) | (1 << 24) | (1 << 25));
                return true;
            }
        }
        default:
            return false;
    }
}
