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
#include <stdio.h>
#include "sleep.h"
#include "sysctl_pwr.h"

/* created by hukai */

volatile sysctl_pwr_s* sysctl_pwr = (volatile sysctl_pwr_s*)SYSCTL_PWR_BASE_ADDR;

/********************************************************************************
* power on:
* 1. power on domain time (power switch cells)    --> pwr_su_tim  poweron
* 2. iso time (domain isolation)                  --> iso_su_tim  disable iso
* 3. retention time (retension)                   --> ret_su_tim  enable retetion
* 4. idle to ildeReq (inactive idle tim)          --> idle_hd_tim enable noc
********************************************************************************/

/********************************************************************************
* power off:
* 1. idleReq to idleAck time (lpi to noc)         --> ack_to_tim  noc
* 2. idleAck to idle time   (noc ack)             --> idle_to_tim noc
* 3. iso time (domain isolation)                  --> iso_su_tim  enable iso
* 4. retention time (retension)                   --> ret_su_tim  enable retetion
* 5. powr off domain time (power switch cells)    --> pd_hd_tim  poweroff
********************************************************************************/

/* iso su */
bool sysctl_pwr_set_iso_su_tim(volatile uint32_t *reg, uint32_t iso_su_tim)
{
    if((iso_su_tim > 0xF) || (NULL == reg))
        return false;
    else
    {
       *reg = (iso_su_tim << 0) | (1 << 24);
       return true;
    }
}

/* power off domain time (power switch cells) */
bool sysctl_pwr_set_pd_hd_tim(volatile uint32_t *reg, uint32_t pd_hd_tim)
{
    if((pd_hd_tim > 0xFF) || (NULL == reg))
        return false;
    else
    {
       *reg = (pd_hd_tim << 4) | (1 << 25);
       return true;
    }
}

/* power on domain time (power switch cells) bringup power */
bool sysctl_pwr_set_pwr_su_tim(volatile uint32_t *reg, uint32_t pwr_su_tim)
{
    if((pwr_su_tim > 0xFF) || (NULL == reg))
        return false;
    else
    {
       *reg = (pwr_su_tim << 12) | (1 << 26);
       return true;
    }
}


/* retention su */
bool sysctl_pwr_set_ret_su_tim(volatile uint32_t *reg, uint32_t ret_su_tim)
{
    if((ret_su_tim > 0xF) || (NULL == reg))
        return false;
    else
    {
       *reg = (ret_su_tim << 0) | (1 << 24);
       return true;
    }
}

/* reset su */
bool sysctl_pwr_set_rst_su_tim(volatile uint32_t *reg, uint32_t rst_su_tim)
{
    if((rst_su_tim > 0xF) || (NULL == reg))
        return false;
    else
    {
       *reg = (rst_su_tim << 4) | (1 << 25);
       return true;
    }
}


/* lpi idleReq to idleAck */
bool sysctl_pwr_set_ack_to_tim(volatile uint32_t *reg, uint32_t ack_to_tim)
{
    if((ack_to_tim > 0x1F) || (NULL == reg))
        return false;
    else
    {
       *reg = (ack_to_tim << 0) | (1 << 24);
       return true;
    }
}

/* lpi idleAck to idle */
bool sysctl_pwr_set_idle_to_tim(volatile uint32_t *reg, uint32_t idle_to_tim)
{
    if((idle_to_tim > 0x1F) || (NULL == reg))
        return false;
    else
    {
       *reg = (idle_to_tim << 8) | (1 << 25);
       return true;
    }
}

/* lpi idle to idelReq(inactive), idle min time */
bool sysctl_pwr_set_idle_hd_tim(volatile uint32_t *reg, uint32_t idle_hd_tim)
{
    if((idle_hd_tim > 0x3F) || (NULL == reg))
        return false;
    else
    {
       *reg = (idle_hd_tim << 16) | (1 << 26);
       return true;
    }
}

/* ax25mp or ax25p wait for interrupt time */
bool sysctl_pwr_set_wfi_tim(volatile uint32_t *reg, uint32_t wfi_tim)
{
    if((wfi_tim > 0xFFF) || (NULL == reg))
        return false;
    else
    {
       *reg = wfi_tim << 0;
       return true;
    }
}

bool sysctl_pwr_set_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t tim_value)
{
    volatile uint32_t *pwr_reg0 = NULL;
    volatile uint32_t *pwr_reg1 = NULL;
    volatile uint32_t *lpi_reg = NULL;
    volatile uint32_t *wfi_reg = NULL;

    if((powerdomain >= SYSCTL_PD_MAX) || (timtype >= SYSCTL_PWR_MAX_TIM))
        return false;

    switch(powerdomain)
    {
        case SYSCTL_PD_AX25M:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ax25m_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_wfi_tim;
            break;
        }
        case SYSCTL_PD_AX25P:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ax25p_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_wfi_tim;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ai_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ai_lpi_tim;
            break;
        }
        case SYSCTL_PD_GNNE:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->gnne_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->gnne_lpi_tim;
            break;
        }
        case SYSCTL_PD_SEC:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sec_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sec_lpi_tim;
            break;
        }
        case SYSCTL_PD_STOR:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->stor_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->stor_lpi_tim;
            break;
        }
        case SYSCTL_PD_PERI:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->peri_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->peri_lpi_tim;
            break;
        }
        case SYSCTL_PD_MCTL:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_tim0;
            pwr_reg1 = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_tim1;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->mctl_lpi_tim;
            break;
        }
        case SYSCTL_PD_SRAM0:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sram0_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sram0_lpi_tim;
            break;
        }
        case SYSCTL_PD_SRAM1:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sram1_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sram1_lpi_tim;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->disp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_tim;
            break;
        }
        case SYSCTL_PD_H264:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->h264_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->h264_lpi_tim;
            break;
        }
        case SYSCTL_PD_USB:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->usb_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->usb_lpi_tim;
            break;
        }
        case SYSCTL_PD_ISP:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->isp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->isp_lpi_tim;
            break;
        }
        default:
            return false;
    }

    switch(timtype)
    {
        case SYSCTL_PWR_ACK_TO_TIM:
            return sysctl_pwr_set_ack_to_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_IDLE_TO_TIM:
            return sysctl_pwr_set_idle_to_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_IDLE_HD_TIM:
            return sysctl_pwr_set_idle_hd_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_ISO_SU_TIM:
            return sysctl_pwr_set_iso_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_PD_HD_TIM:
            return sysctl_pwr_set_pd_hd_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_SU_TIM:
            return sysctl_pwr_set_pwr_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_RET_SU_TIM:
            return sysctl_pwr_set_ret_su_tim(pwr_reg1, tim_value);
        case SYSCTL_PWR_RST_SU_TIM:
            return sysctl_pwr_set_rst_su_tim(pwr_reg1, tim_value);
        case SYSCTL_PWR_WFI_TIM:
            return sysctl_pwr_set_wfi_tim(wfi_reg, tim_value);
        default:
            return false;
    }
}


/* iso su */
bool sysctl_pwr_get_iso_su_tim(volatile uint32_t *reg, uint32_t *iso_su_tim)
{
    if((NULL == reg) || (NULL == iso_su_tim))
        return false;

   *iso_su_tim = ((*reg) >> 0) & 0xF;
   return true;
}

/* power off domain time (power switch cells) */
bool sysctl_pwr_get_pd_hd_tim(volatile uint32_t *reg, uint32_t *pd_hd_tim)
{
   if((NULL == reg) || (NULL == pd_hd_tim))
       return false;

   *pd_hd_tim = ((*reg) >> 4) & 0xFF;
   return true;
}

/* power on domain time (power switch cells) bringup power */
bool sysctl_pwr_get_pwr_su_tim(volatile uint32_t *reg, uint32_t *pwr_su_tim)
{
   if((NULL == reg) || (NULL == pwr_su_tim))
       return false;

   *pwr_su_tim = ((*reg) >> 12) & 0xFF;
   return true;
}


/* retention su */
bool sysctl_pwr_get_ret_su_tim(volatile uint32_t *reg, uint32_t *ret_su_tim)
{
   if((NULL == reg) || (NULL == ret_su_tim))
       return false;

   *ret_su_tim = ((*reg) >> 0) & 0xF;
   return true;
}

/* reset su */
bool sysctl_pwr_get_rst_su_tim(volatile uint32_t *reg, uint32_t *rst_su_tim)
{
   if((NULL == reg) || (NULL == rst_su_tim))
       return false;

   *rst_su_tim = ((*reg) >> 4) & 0xF;
   return true;
}


/* lpi idleReq to idleAck */
bool sysctl_pwr_get_ack_to_tim(volatile uint32_t *reg, uint32_t *ack_to_tim)
{
   if((NULL == reg) || (NULL == ack_to_tim))
       return false;

   *ack_to_tim = ((*reg) >> 0) & 0x1F;
   return true;
}


/* lpi idleAck to idle */
bool sysctl_pwr_get_idle_to_tim(volatile uint32_t *reg, uint32_t *idle_to_tim)
{
   if((NULL == reg) || (NULL == idle_to_tim))
       return false;

   *idle_to_tim = ((*reg) >> 8) & 0x1F;
   return true;
}

/* lpi idle to idelReq(inactive), idle min time */
bool sysctl_pwr_get_idle_hd_tim(volatile uint32_t *reg, uint32_t *idle_hd_tim)
{
   if((NULL == reg) || (NULL == idle_hd_tim))
       return false;

   *idle_hd_tim = ((*reg) >> 16) & 0x3F;
   return true;
}

/* wait for interrupt time */
bool sysctl_pwr_get_wfi_tim(volatile uint32_t *reg, uint32_t *wfi_tim)
{
   if((NULL == reg) || (NULL == wfi_tim))
       return false;

   *wfi_tim = (*reg) & 0xFFF;
   return true;
}

bool sysctl_pwr_get_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t *tim_value)
{
    volatile uint32_t *pwr_reg0 = NULL;
    volatile uint32_t *pwr_reg1 = NULL;
    volatile uint32_t *lpi_reg = NULL;
    volatile uint32_t *wfi_reg = NULL;

    if((powerdomain >= SYSCTL_PD_MAX) || (timtype >= SYSCTL_PWR_MAX_TIM))
        return false;

    switch(powerdomain)
    {
        case SYSCTL_PD_AX25M:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ax25m_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_wfi_tim;
            break;
        }
        case SYSCTL_PD_AX25P:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ax25p_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_wfi_tim;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->ai_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ai_lpi_tim;
            break;
        }
        case SYSCTL_PD_GNNE:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->gnne_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->gnne_lpi_tim;
            break;
        }
        case SYSCTL_PD_SEC:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sec_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sec_lpi_tim;
            break;
        }
        case SYSCTL_PD_STOR:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->stor_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->stor_lpi_tim;
            break;
        }
        case SYSCTL_PD_PERI:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->peri_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->peri_lpi_tim;
            break;
        }
        case SYSCTL_PD_MCTL:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_tim0;
            pwr_reg1 = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_tim1;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->mctl_lpi_tim;
            break;
        }
        case SYSCTL_PD_SRAM0:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sram0_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sram0_lpi_tim;
            break;
        }
        case SYSCTL_PD_SRAM1:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->sram1_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->sram1_lpi_tim;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->disp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_tim;
            break;
        }
        case SYSCTL_PD_H264:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->h264_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->h264_lpi_tim;
            break;
        }
        case SYSCTL_PD_USB:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->usb_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->usb_lpi_tim;
            break;
        }
        case SYSCTL_PD_ISP:
        {
            pwr_reg0 = (volatile uint32_t *)&sysctl_pwr->isp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->isp_lpi_tim;
            break;
        }
        default:
            return false;
    }

    switch(timtype)
    {
        case SYSCTL_PWR_ACK_TO_TIM:
            return sysctl_pwr_get_ack_to_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_IDLE_TO_TIM:
            return sysctl_pwr_get_idle_to_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_IDLE_HD_TIM:
            return sysctl_pwr_get_idle_hd_tim(pwr_reg0, tim_value);
        case SYSCTL_PWR_ISO_SU_TIM:
            return sysctl_pwr_get_iso_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_PD_HD_TIM:
            return sysctl_pwr_get_pd_hd_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_SU_TIM:
            return sysctl_pwr_get_pwr_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_RET_SU_TIM:
            return sysctl_pwr_get_ret_su_tim(pwr_reg1, tim_value);
        case SYSCTL_PWR_RST_SU_TIM:
            return sysctl_pwr_get_rst_su_tim(pwr_reg1, tim_value);
        case SYSCTL_PWR_WFI_TIM:
            return sysctl_pwr_get_wfi_tim(wfi_reg,tim_value);
        default:
            return false;
    }
}

bool sysctl_pwr_set_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool enable)
{
    if(SYSCTL_PD_AX25M == powerdomain)
    {
        sysctl_pwr->ax25m_pwr_ctl = (true == enable) ? ((1 << 9) | (1 << 27)) : ((0 << 9) | (1 << 27));
        return true;
    }
    else if(SYSCTL_PD_AX25P == powerdomain)
    {
        sysctl_pwr->ax25p_pwr_ctl = (true == enable) ? ((1 << 9) | (1 << 27)) : ((0 << 9) | (1 << 27));
        return true;
    }
    else
    {
        return false;
    }
}

bool sysctl_pwr_get_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool *enable)
{
    if(SYSCTL_PD_AX25M == powerdomain)
    {
        if(sysctl_pwr->ax25m_pwr_ctl & (1 << 9))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else if(SYSCTL_PD_AX25P == powerdomain)
    {
        if(sysctl_pwr->ax25p_pwr_ctl & (1 << 9))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool sysctl_pwr_set_auto_pwr(sysctl_pwr_domain_e powerdomain, bool enable)
{
    if(SYSCTL_PD_AX25M == powerdomain)
    {
        sysctl_pwr->ax25m_pwr_ctl = (true == enable) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
        return true;
    }
    else if(SYSCTL_PD_AX25P == powerdomain)
    {
        sysctl_pwr->ax25p_pwr_ctl = (true == enable) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
        return true;
    }
    else
    {
        return false;
    }
}

bool sysctl_pwr_get_auto_pwr(sysctl_pwr_domain_e powerdomain, bool *enable)
{
    if(SYSCTL_PD_AX25M == powerdomain)
    {
        if(sysctl_pwr->ax25m_pwr_ctl & (1 << 8))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else if(SYSCTL_PD_AX25P == powerdomain)
    {
        if(sysctl_pwr->ax25p_pwr_ctl & (1 << 8))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else
    {
        return false;
    }
}


bool sysctl_pwr_set_repair_enable(sysctl_pwr_domain_e powerdomain)
{
    switch(powerdomain)
    {
        case SYSCTL_PD_AX25M:
            sysctl_pwr->pwr_dom_grp_en = (1 << 0) | (1 << 24);
            return true;
        case SYSCTL_PD_AX25P:
            sysctl_pwr->pwr_dom_grp_en = (1 << 1) | (1 << 25);
            return true;
        case SYSCTL_PD_SRAM0:
            sysctl_pwr->pwr_dom_grp_en = (1 << 2) | (1 << 26);
            return true;
        case SYSCTL_PD_SRAM1:
            sysctl_pwr->pwr_dom_grp_en = (1 << 3) | (1 << 27);
            return true;
        case SYSCTL_PD_GNNE:
            sysctl_pwr->pwr_dom_grp_en = (1 << 4) | (1 << 28);
            return true;
        case SYSCTL_PD_ISP:
            sysctl_pwr->pwr_dom_grp_en = (1 << 5) | (1 << 29);
            return true;
        default:
            return false;
    }
}


bool sysctl_pwr_check_repair_done(sysctl_pwr_domain_e powerdomain)
{
    switch(powerdomain)
    {
        case SYSCTL_PD_AX25M:
            return (sysctl_pwr->pwr_dom_grp_sta & (0 << 0)) ? true:false;
        case SYSCTL_PD_AX25P:
            return (sysctl_pwr->pwr_dom_grp_sta & (1 << 0)) ? true:false;
        case SYSCTL_PD_SRAM0:
            return (sysctl_pwr->pwr_dom_grp_sta & (2 << 0)) ? true:false;
        case SYSCTL_PD_SRAM1:
            return (sysctl_pwr->pwr_dom_grp_sta & (3 << 0)) ? true:false;
        case SYSCTL_PD_GNNE:
            return (sysctl_pwr->pwr_dom_grp_sta & (4 << 0)) ? true:false;
        case SYSCTL_PD_ISP:
            return (sysctl_pwr->pwr_dom_grp_sta & (5 << 0)) ? true:false;
        case SYSCTL_PD_MAX:
            return (sysctl_pwr->pwr_dom_grp_sta & (6 << 0)) ? true:false;
        default:
            return false;
    }
}

bool sysctl_pwr_set_lpi_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable)
{
    /* enable==true connect noc */
    *regctl = (true==enable) ? ((1 << 4) | (1 << 25)) : ((1 << 0) | (1 << 24));

    usleep(500);

    if(true == enable)
        return (*regsta & (1 << 4)) ? true:false;
    else
        return (*regsta & (1 << 0)) ? true:false;
}

bool sysctl_pwr_set_pwr_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable)
{
    /* enable==true power up */
    *regctl = (true==enable) ? ((1 << 4) | (1 << 25)) : ((1 << 0) | (1 << 24));

    usleep(500);

    if(regctl == &sysctl_pwr->mctl_pwr_state)
    {
        if(true == enable)
        {
            if(((*regsta) & 0xf) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(((*regsta) & 0xf) == 0x6)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
    }
    else
    {
        if(true == enable)
            return (*regsta & (1 << 4)) ? true:false;
        else
            return (*regsta & (1 << 0)) ? true:false;
    }
}

/*****************************************************************************************
*   powerdomain:power domain
*   enable:     true for powerup, false for poweroff
*****************************************************************************************/
bool sysctl_pwr_set_power(sysctl_pwr_domain_e powerdomain, bool enable)
{
    volatile uint32_t *pwr_ctl_reg = NULL;
    volatile uint32_t *pwr_sta_reg = NULL;

    switch(powerdomain)
    {
        case SYSCTL_PD_AX25M:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->ax25m_pwr_state;
            break;
        }
        case SYSCTL_PD_AX25P:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->ax25p_pwr_state;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_state;
            break;
        }
        case SYSCTL_PD_GNNE:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->gnne_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->gnne_pwr_state;
            break;
        }
        case SYSCTL_PD_SEC:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->sec_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->sec_pwr_state;
            break;
        }
        case SYSCTL_PD_STOR:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->stor_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->stor_pwr_state;
            break;
        }
        case SYSCTL_PD_PERI:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->peri_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->peri_pwr_state;
            break;
        }
        case SYSCTL_PD_MCTL:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->mctl_pwr_state;
            break;
        }
        case SYSCTL_PD_SRAM0:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->sram0_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->sram0_pwr_state;
            break;
        }
        case SYSCTL_PD_SRAM1:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->sram1_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->sram1_pwr_state;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->disp_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->disp_pwr_state;
            break;
        }
        case SYSCTL_PD_H264:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->h264_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->h264_pwr_state;
            break;
        }
        case SYSCTL_PD_USB:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->usb_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->usb_pwr_state;
            break;
        }
        case SYSCTL_PD_ISP:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->isp_pwr_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->isp_pwr_state;
            break;
        }
        default:
            return false;
    }

    /* repair powerdomain */
    if(true == enable) /* only powerup need repair */
    {
        (void)sysctl_pwr_set_repair_enable(powerdomain);
    }
    return sysctl_pwr_set_pwr_reg(pwr_ctl_reg,pwr_sta_reg,enable);
}

bool sysctl_pwr_up(sysctl_pwr_domain_e powerdomain)
{
    return sysctl_pwr_set_power(powerdomain,true);
}

bool sysctl_pwr_off(sysctl_pwr_domain_e powerdomain)
{
    return sysctl_pwr_set_power(powerdomain,false);
}
