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
#include <stdlib.h>
#include <math.h>
#include "platform.h"
#include "sysctl_boot.h"
#include "sysctl_clk.h"

/* created by hukai */
/* please refer to the sysctl_clk.h file for API description */

#define OSC_CLOCK_FREQ_32K (32768)
#define OSC_CLOCK_FREQ_25M (25000000)

extern volatile sysctl_boot_t *sysctl_boot;
volatile sysctl_clk_t* sysctl_clk = (volatile sysctl_clk_t*)SYSCTL_CLK_BASE_ADDR;

/* if PLL bypass, the output clock is 25m clock. If there is no bypass, the clock comes from PLL */
bool sysctl_boot_get_root_clk_bypass(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((sysctl_boot->pll[0].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((sysctl_boot->pll[1].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((sysctl_boot->pll[2].cfg1 >> 19) & 0x1) ? true:false;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((sysctl_boot->pll[3].cfg1 >> 19) & 0x1) ? true:false;

        default:
            return false;
    }
}

/* if PLL bypass, the output clock is 25m clock. If there is no bypass, the clock comes from PLL */
void sysctl_boot_set_root_clk_bypass(sysctl_clk_node_e clk, bool enable)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            if(true == enable)  /* enable bypass */
                sysctl_boot->pll[0].cfg1 = ((1 << 19) | (1 << 28));
            else
                sysctl_boot->pll[0].cfg1 = ((0 << 19) | (1 << 28));
            return;

        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            if(true == enable)  /* enable bypass */
                sysctl_boot->pll[1].cfg1 = ((1 << 19) | (1 << 28));
            else
                sysctl_boot->pll[1].cfg1 = ((0 << 19) | (1 << 28));
            return;

        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            if(true == enable)  /* enable bypass */
                sysctl_boot->pll[2].cfg1 = ((1 << 19) | (1 << 28));
            else
                sysctl_boot->pll[2].cfg1 = ((0 << 19) | (1 << 28));
            return;

        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            if(true == enable)  /* enable bypass */
                sysctl_boot->pll[3].cfg1 = ((1 << 19) | (1 << 28));
            else
                sysctl_boot->pll[3].cfg1 = ((0 << 19) | (1 << 28));
            return;

        default:
            return;
    }
}

/* 
   Enable pll, enable 25M clock&pll, only when both 25m clock and PLL are enabled, can PLL output clock
*/
bool sysctl_boot_get_root_clk_en(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_OSC_IN0:
            return (0 == ((sysctl_boot->osc_25m_off >> 0) & 0x1)) ? true:false;
        case SYSCTL_CLK_ROOT_OSC_IN1:
            return true;
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((0 == ((sysctl_boot->osc_25m_off >> 0) & 0x1)) && (1 == ((sysctl_boot->pll[0].ctl >> 8) & 0x1))) ? true:false;
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((0 == ((sysctl_boot->osc_25m_off >> 0) & 0x1)) && (1 == ((sysctl_boot->pll[1].ctl >> 8) & 0x1))) ? true:false;
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((0 == ((sysctl_boot->osc_25m_off >> 0) & 0x1)) && (1 == ((sysctl_boot->pll[2].ctl >> 8) & 0x1))) ? true:false;
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((0 == ((sysctl_boot->osc_25m_off >> 0) & 0x1)) && (1 == ((sysctl_boot->pll[3].ctl >> 8) & 0x1))) ? true:false;
        default:
            return false;
    }
}

/* 
   Enable pll, enable 25M clock&pll, only when both 25m clock and PLL are enabled, can PLL output clock
*/
void sysctl_boot_set_root_clk_en(sysctl_clk_node_e clk, bool enable)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_OSC_IN0:
            if(true == enable)
                sysctl_boot->osc_25m_off = ((0 << 0) | (1 << 16));
            else
                sysctl_boot->osc_25m_off = ((1 << 0) | (1 << 16));
            return;
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            if(true == enable)
            {
                sysctl_boot->osc_25m_off = ((0 << 0) | (1 << 16));  /* pll is root clk, so need to enable 25M*/
                sysctl_boot->pll[0].ctl = ((1 << 8) | (1 << 26));   /* enable pll */
            }
            return;
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            if(true == enable)
            {
                sysctl_boot->osc_25m_off = ((0 << 0) | (1 << 16));  /* pll is root clk, so need to enable 25M*/
                sysctl_boot->pll[1].ctl = ((1 << 8) | (1 << 26));   /* enable pll */
            }
            return;
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            if(true == enable)
            {
                sysctl_boot->osc_25m_off = ((0 << 0) | (1 << 16));  /* pll is root clk, so need to enable 25M*/
                sysctl_boot->pll[2].ctl = ((1 << 8) | (1 << 26));   /* enable pll */
            }
            return;
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            if(true == enable)
            {
                sysctl_boot->osc_25m_off = ((0 << 0) | (1 << 16));  /* pll is root clk, so need to enable 25M*/
                sysctl_boot->pll[3].ctl = ((1 << 8) | (1 << 26));   /* enable pll */
            }
            return;
        default:
            return;
    }
}

/* PLL power supply */
/*
bool sysctl_boot_set_root_clk_pwrup(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            sysctl_boot->pll[0].ctl = (1 << 4)|(1 << 25);
            return true;
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
           sysctl_boot->pll[1].ctl = (1 << 4)|(1 << 25);
            return true;
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            sysctl_boot->pll[2].ctl = (1 << 4)|(1 << 25);
            return true;
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            sysctl_boot->pll[3].ctl = (1 << 4)|(1 << 25);
            return true;
        default:
            return false;
    }
}
*/
/* PLL power supply */
bool sysctl_boot_set_root_clk_pwroff(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            sysctl_boot->pll[0].ctl = (1 << 0)|(1 << 24);
            return true;
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
           sysctl_boot->pll[1].ctl = (1 << 0)|(1 << 24);
            return true;
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            sysctl_boot->pll[2].ctl = (1 << 0)|(1 << 24);
            return true;
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            sysctl_boot->pll[3].ctl = (1 << 0)|(1 << 24);
            return true;
        default:
            return false;
    }
}

/* check the lock state of PLL */
bool sysctl_boot_get_root_clk_lock(sysctl_clk_node_e clk)
{
    switch(clk)
    {
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
            return ((sysctl_boot->pll[0].state >> 0) & 0x1) ? true:false;
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
            return ((sysctl_boot->pll[1].state >> 0) & 0x1) ? true:false;
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
            return ((sysctl_boot->pll[2].state >> 0) & 0x1) ? true:false;
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
            return ((sysctl_boot->pll[3].state >> 0) & 0x1) ? true:false;
        default:
            return true;
    }
}

/* get PLL output frequency */
uint32_t sysctl_boot_get_root_clk_freq(sysctl_clk_node_e clk)
{
    uint32_t refdiv; /* refrence clock divide */
    uint32_t outdiv; /* output clock divide */
    uint32_t fbdiv;  /* feedback clock divide */
    uint32_t freq;

    switch (clk)
    {
        case SYSCTL_CLK_ROOT_OSC_IN0:
            return OSC_CLOCK_FREQ_25M;  /* 25MHz */
        case SYSCTL_CLK_ROOT_OSC_IN1:
            return OSC_CLOCK_FREQ_32K;  /* 32768 */
        case SYSCTL_CLK_ROOT_PLL0:
        case SYSCTL_CLK_ROOT_PLL0_DIV_2:
        case SYSCTL_CLK_ROOT_PLL0_DIV_3:
        case SYSCTL_CLK_ROOT_PLL0_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_25M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[0].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[0].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[0].cfg0 >> 0)  & 0xFFF;   /* bit 0~11 */
                freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL0:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL0_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL0_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }
        case SYSCTL_CLK_ROOT_PLL1:
        case SYSCTL_CLK_ROOT_PLL1_DIV_2:
        case SYSCTL_CLK_ROOT_PLL1_DIV_3:
        case SYSCTL_CLK_ROOT_PLL1_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_25M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[1].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[1].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[1].cfg0 >> 0)  & 0xFFF;   /* bit 0~11 */
                freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL1:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL1_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL1_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }
        case SYSCTL_CLK_ROOT_PLL2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_2:
        case SYSCTL_CLK_ROOT_PLL2_DIV_3:
        case SYSCTL_CLK_ROOT_PLL2_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_25M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[2].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[2].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[2].cfg0 >> 0)  & 0xFFF;   /* bit 0~11 */
                freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL2:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL2_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL2_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }
        case SYSCTL_CLK_ROOT_PLL3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_2:
        case SYSCTL_CLK_ROOT_PLL3_DIV_3:
        case SYSCTL_CLK_ROOT_PLL3_DIV_4:
        {
            if(true == sysctl_boot_get_root_clk_bypass(clk))
            {
                freq = OSC_CLOCK_FREQ_25M;
            }
            else
            {
                refdiv = (sysctl_boot->pll[3].cfg0 >> 16) & 0x3F;    /* bit 16~21 */
                outdiv = (sysctl_boot->pll[3].cfg0 >> 24) & 0xF;     /* bit 24~27 */
                fbdiv  = (sysctl_boot->pll[3].cfg0 >> 0)  & 0xFFF;   /* bit 0~11 */
                freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1);
            }
            switch(clk)
            {
                case SYSCTL_CLK_ROOT_PLL3:
                    return freq;
                case SYSCTL_CLK_ROOT_PLL3_DIV_2:
                    return freq/2;
                case SYSCTL_CLK_ROOT_PLL3_DIV_3:
                    return freq/3;
                default:
                    return freq/4;
            }
        }

        default:
            return 0;
    }
}

/*freq = (double)OSC_CLOCK_FREQ_25M * (double)(fbdiv+1) / (double)(refdiv+1) / (double)(outdiv+1)
  please configure the PLL frequency according to the above frequency division coefficient
  Note: when configuring, you can't configure yourself. For example, the PLL attached to CPU can't stop
  before configuring the PLL of CPU, switch the clock first and then configure it. After configuration, switch it back
*/
bool sysctl_boot_set_root_clk_freq(sysctl_clk_node_e clk, uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv)
{
    uint32_t id;
    uint32_t wait_us = 100;

    if(SYSCTL_CLK_ROOT_PLL0 == clk)
        id = 0;
    else if(SYSCTL_CLK_ROOT_PLL1 == clk)
        id = 1;
    else if(SYSCTL_CLK_ROOT_PLL2 == clk)
        id = 2;
    else if(SYSCTL_CLK_ROOT_PLL3 == clk)
        id = 3;
    else
        return false;

    /*1. poweroff pll*/
    (void)sysctl_boot_set_root_clk_pwroff(clk);

    /*2. config divide*/
    sysctl_boot->pll[id].cfg0 = ((fbdiv &  0xFFF) << 0) | ((refdiv &  0x3F) << 16) | ((outdiv & 0xF) << 24) | (1 << 28) | (1 << 29) | (1 << 30);

    /* 3. init pll. init will pwrup pll */
    sysctl_boot->pll[id].ctl = (1 << 4)|(1 << 25);

    /* 4. check lock status */
    while(1)
    {
        if(false == sysctl_boot_get_root_clk_lock(clk))
        {
            wait_us --;
            if(wait_us == 0)
                return false;
        }
        else
            return true;
    }
}

bool sysctl_clk_set_leaf_parent(sysctl_clk_node_e leaf, sysctl_clk_node_e parent)
{
    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
        {
            if(SYSCTL_CLK_ROOT_PLL2_DIV_3 == parent)
            {
                sysctl_clk->ax25m_clk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->ax25m_clk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL2_DIV_2 == parent)
            {
                sysctl_clk->ax25m_clk_cfg = ((2 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_AX25M_CORE_0:
        case SYSCTL_CLK_AX25M_CORE_1:
        case SYSCTL_CLK_AX25M_CORE_0_DC:
        case SYSCTL_CLK_AX25M_CORE_1_DC:
        case SYSCTL_CLK_AX25M_MCTL:
            return false;
        case SYSCTL_CLK_AX25M_MTIMER:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->ax25m_mtimer_clk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->ax25m_mtimer_clk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_SRC:
        {
            if(SYSCTL_CLK_ROOT_PLL2_DIV_3 == parent)
            {
                sysctl_clk->ax25p_clk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->ax25p_clk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_AX25P_CORE:
        case SYSCTL_CLK_AX25P_LM:
            return false;
        case SYSCTL_CLK_AX25P_MTIMER:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->ax25p_mtimer_clk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->ax25p_mtimer_clk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_2 == parent)
            {
                sysctl_clk->gnne_sysclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1_DIV_2 == parent)
            {
                sysctl_clk->gnne_sysclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_GNNE_AXI:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_2 == parent)
            {
                sysctl_clk->ai_gnne_aclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1_DIV_2 == parent)
            {
                sysctl_clk->ai_gnne_aclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_GNNE_AXI_NOC:
            return false;
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            return false;

        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_2 == parent)
            {
                sysctl_clk->noc_clk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1_DIV_2 == parent)
            {
                sysctl_clk->noc_clk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            return false;

        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            return false;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
            return false;  /*always pll0 div 2*/
        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:
        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            return false;

        /*---------------------------display------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            return false;

        /*---------------------------csi0/1_system_clk---------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
        case SYSCTL_CLK_CSI_1_SYSTEM:
            return false;   /*always pll1_div4*/

        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
            return false;   /*always pll2_div4*/

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
        {
            if(SYSCTL_CLK_ROOT_PLL2_DIV_4 == parent)
            {
                sysctl_clk->csi1_pixel_clk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL2_DIV_3 == parent)
            {
                sysctl_clk->csi1_pixel_clk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->csi1_pixel_clk_cfg = ((2 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1 == parent)
            {
                sysctl_clk->csi1_pixel_clk_cfg = ((3 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
            return false;

        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
        {
            if(SYSCTL_CLK_ROOT_PLL2_DIV_4 == parent)
            {
                sysctl_clk->disp_pixel_clk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL2_DIV_3 == parent)
            {
                sysctl_clk->disp_pixel_clk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->disp_pixel_clk_cfg = ((2 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1 == parent)
            {
                sysctl_clk->disp_pixel_clk_cfg = ((3 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            return false;               //always pll1_div3
        }

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            return false;               //always pll1_div3
        }

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
        {
            return false;               //always pll0
        }
        case SYSCTL_CLK_SD_MASTER_SD_0:
        {
            return false;               //always SYSCTL_CLK_SD_MASTER
        }
        case SYSCTL_CLK_SD_MASTER_SD_1:
        {
            return false;               //always SYSCTL_CLK_SD_MASTER
        }
        case SYSCTL_CLK_SD_MASTER_SD_2:
        {
            return false;               //always SYSCTL_CLK_SD_MASTER
        }

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
        {
            if(SYSCTL_CLK_ROOT_PLL2_DIV_2 == parent)
            {
                sysctl_clk->mipi_txdphy_clk_en = ((0 << 2) | (1 << 18));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL1 == parent)
            {
                sysctl_clk->mipi_txdphy_clk_en = ((1 << 2) | (1 << 18));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            return false;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            return false;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            return false;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
            return false; /* always pll1 div 3*/

        case SYSCTL_CLK_PUF_HCLK:
        case SYSCTL_CLK_OTP_HCLK:
        case SYSCTL_CLK_ROM_HCLK:
        case SYSCTL_CLK_RSA_HCLK:
        case SYSCTL_CLK_AES_HCLK:
        case SYSCTL_CLK_SHA_HCLK:
            return false; /* always SYSCTL_CLK_SEC_HCLK*/

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
        {
            switch(parent)
            {
                case SYSCTL_CLK_ROOT_PLL1:
                    sysctl_clk->mem_ctl_clk_cfg = (0 << 0) | (1 << 16);
                    return true;
                case SYSCTL_CLK_ROOT_PLL2_DIV_2:
                    sysctl_clk->mem_ctl_clk_cfg = (1 << 0) | (1 << 16);
                    return true;
                case SYSCTL_CLK_ROOT_PLL3_DIV_3:
                    sysctl_clk->mem_ctl_clk_cfg = (2 << 0) | (1 << 16);
                    return true;
                case SYSCTL_CLK_ROOT_PLL3_DIV_2:
                    sysctl_clk->mem_ctl_clk_cfg = (3 << 0) | (1 << 16);
                    return true;
                default:
                    return false;
            }
        }

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
            return false;                   //always pll0_div4

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART3_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->uart3_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->uart3_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_UART2_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->uart2_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->uart2_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_UART1_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->uart1_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->uart1_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_UART0_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->uart0_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->uart0_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->spi0_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->spi0_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_SPI1_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->spi1_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->spi1_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_SPI2_SCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->spi2_sclk_cfg = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_PLL0 == parent)
            {
                sysctl_clk->spi2_sclk_cfg = ((1 << 0) | (1 << 24));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_SPI3_SCLK:
            return false;   /*always osc25m*/

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
            return false; /* always SYSCTL_CLK_ROOT_OSC_IN0 25M*/

        /*---------------------------I2C system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c0_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c0_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C1_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c1_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c1_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C2_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c2_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c2_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C3_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c3_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c3_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C4_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c4_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c4_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C5_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c5_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c5_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_I2C6_SCLK:
        {
            if(SYSCTL_CLK_ROOT_PLL0_DIV_4 == parent)
            {
                sysctl_clk->i2c6_icclk_cfg = ((0 << 9) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->i2c6_icclk_cfg = ((1 << 9) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
        case SYSCTL_CLK_WDT1_TCLK:
        case SYSCTL_CLK_WDT2_TCLK:
            return false;           /*always osc25m*/

        /*---------------------------VAD system clock---------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
            return false;           /*always osc25m*/

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 0) | (1 << 24));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 0) | (1 << 24));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_TIMER1_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 4) | (1 << 25));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 4) | (1 << 25));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_TIMER2_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 8) | (1 << 26));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 8) | (1 << 26));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_TIMER3_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 12) | (1 << 27));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 12) | (1 << 27));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_TIMER4_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 16) | (1 << 28));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 16) | (1 << 28));
                return true;
            }
            else
                return false;
        }
        case SYSCTL_CLK_TIMER5_TCLK:
        {
            if(SYSCTL_CLK_ROOT_OSC_IN1 == parent)
            {
                sysctl_clk->timer_tclk_src = ((0 << 20) | (1 << 29));
                return true;
            }
            else if(SYSCTL_CLK_ROOT_OSC_IN0 == parent)
            {
                sysctl_clk->timer_tclk_src = ((1 << 20) | (1 << 29));
                return true;
            }
            else
                return false;
        }

        /*---------------------------usb clock----------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            return false;
        case SYSCTL_CLK_USB_WAKEUP:
            return false;

        default:
            return false;
    }
}

sysctl_clk_node_e sysctl_clk_get_leaf_parent(sysctl_clk_node_e leaf)
{
    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
        {
            switch((sysctl_clk->ax25m_clk_cfg >> 0) & 0x3)
            {
                case 0:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_3;
                case 1:
                    return SYSCTL_CLK_ROOT_PLL0;
                case 2:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_2;
                default:
                    return SYSCTL_CLK_ROOT_MAX;
            }
        }
        case SYSCTL_CLK_AX25M_CORE_0:
        case SYSCTL_CLK_AX25M_CORE_1:
        case SYSCTL_CLK_AX25M_CORE_0_DC:
        case SYSCTL_CLK_AX25M_CORE_1_DC:
        case SYSCTL_CLK_AX25M_MCTL:
            return SYSCTL_CLK_AX25M_SRC;
        case SYSCTL_CLK_AX25M_MTIMER:
        {
            if(0 == ((sysctl_clk->ax25m_mtimer_clk_cfg) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        case SYSCTL_CLK_AX25P_SRC:
        {
            if(sysctl_clk->ax25p_clk_cfg & 0x1)
            {
                return SYSCTL_CLK_ROOT_PLL0;
            }
            else
            {
                return SYSCTL_CLK_ROOT_PLL2_DIV_3;
            }
        }

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_CORE:
        case SYSCTL_CLK_AX25P_LM:
            return SYSCTL_CLK_AX25P_SRC;

        case SYSCTL_CLK_AX25P_MTIMER:
        {
            if(0 == ((sysctl_clk->ax25p_mtimer_clk_cfg) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
        {
            if(0 == (sysctl_clk->gnne_sysclk_cfg & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_2;
            else 
                return SYSCTL_CLK_ROOT_PLL1_DIV_2;
        }
        case SYSCTL_CLK_GNNE_AXI:
        {
            if(0 == (sysctl_clk->ai_gnne_aclk_cfg & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_2;
            else 
                return SYSCTL_CLK_ROOT_PLL1_DIV_2;
        }
        case SYSCTL_CLK_GNNE_AXI_NOC:
            return SYSCTL_CLK_GNNE_AXI;
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            return SYSCTL_CLK_GNNE_AXI;


        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:
        {
            if(0 == ((sysctl_clk->noc_clk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_2;
            else
                return SYSCTL_CLK_ROOT_PLL1_DIV_2;
        }
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            return SYSCTL_CLK_NOC_CLK_0;

        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            return SYSCTL_CLK_NOC_CLK_0;

        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            return SYSCTL_CLK_NOC_CLK_0_DIV_2;

        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            return SYSCTL_CLK_NOC_CLK_0_DIV_3;

        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            return SYSCTL_CLK_NOC_CLK_0_DIV_4;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
            return SYSCTL_CLK_ROOT_PLL0_DIV_2;  /*always pll0 div 2*/

        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
            return SYSCTL_CLK_NOC_CLK_1;

        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:
            return SYSCTL_CLK_NOC_CLK_1;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:
            return SYSCTL_CLK_NOC_CLK_1;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:
            return SYSCTL_CLK_NOC_CLK_1_PERI_APB;

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
            return SYSCTL_CLK_NOC_CLK_1;

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:
            return SYSCTL_CLK_NOC_CLK_1_PERI_AHB;

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:
            return SYSCTL_CLK_NOC_CLK_1;

        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            return SYSCTL_CLK_NOC_CLK_1_DIV_4;

        /*---------------------------DISPLAY------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
            return SYSCTL_CLK_ROOT_PLL1_DIV_4;

        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            return SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV;

        /*---------------------------csi0/1_system_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
        case SYSCTL_CLK_CSI_1_SYSTEM:
            return SYSCTL_CLK_ROOT_PLL1_DIV_4;   /*always pll1_div4*/

        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
            return SYSCTL_CLK_ROOT_PLL2_DIV_4;   /*always pll2_div4*/

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
        {
            switch((sysctl_clk->csi1_pixel_clk_cfg >> 9) & 0x3)
            {
                case 0:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_4;
                case 1:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_3;
                case 2:
                    return SYSCTL_CLK_ROOT_PLL0;
                default:
                    return SYSCTL_CLK_ROOT_PLL1;
            }
        }

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
            return SYSCTL_CLK_ROOT_PLL2_DIV_4;

        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
        {
            switch((sysctl_clk->disp_pixel_clk_cfg >> 9) & 0x3)
            {
                case 0:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_4;
                case 1:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_3;
                case 2:
                    return SYSCTL_CLK_ROOT_PLL0;
                default:
                    return SYSCTL_CLK_ROOT_PLL1;
            }
        }

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            return SYSCTL_CLK_ROOT_PLL0;              //always pll0_div0
        }

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            return SYSCTL_CLK_ROOT_PLL0;              //always pll0_div0
        }

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
        {
            return SYSCTL_CLK_ROOT_PLL0;                    //always pll0
        }
        case SYSCTL_CLK_SD_MASTER_SD_0:
        {
            return SYSCTL_CLK_SD_MASTER;                    //always SYSCTL_CLK_SD_MASTER
        }
        case SYSCTL_CLK_SD_MASTER_SD_1:
        {
            return SYSCTL_CLK_SD_MASTER;                    //always SYSCTL_CLK_SD_MASTER
        }
        case SYSCTL_CLK_SD_MASTER_SD_2:
        {
            return SYSCTL_CLK_SD_MASTER;                    //always SYSCTL_CLK_SD_MASTER
        }

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
        {
            if((sysctl_clk->mipi_txdphy_clk_en >> 2) & 0x1)
                return SYSCTL_CLK_ROOT_PLL1;
            else
                return SYSCTL_CLK_ROOT_PLL2_DIV_2;
        }
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            return SYSCTL_CLK_MIPI_REF;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            return SYSCTL_CLK_MIPI_REF;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            return SYSCTL_CLK_ROOT_OSC_IN0;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
        {
            return SYSCTL_CLK_ROOT_PLL1_DIV_3;
        }

        case SYSCTL_CLK_PUF_HCLK:
        case SYSCTL_CLK_OTP_HCLK:
        case SYSCTL_CLK_ROM_HCLK:
        case SYSCTL_CLK_RSA_HCLK:
        case SYSCTL_CLK_AES_HCLK:
        case SYSCTL_CLK_SHA_HCLK:
        {
            return SYSCTL_CLK_SEC_HCLK;
        }

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
        {
            switch((sysctl_clk->mem_ctl_clk_cfg >> 0) & 0x3)
            {
                case 0:
                    return SYSCTL_CLK_ROOT_PLL1;
                case 1:
                    return SYSCTL_CLK_ROOT_PLL2_DIV_2;
                case 2:
                    return SYSCTL_CLK_ROOT_PLL3_DIV_3;
                default:
                    return SYSCTL_CLK_ROOT_PLL3_DIV_2;
            }
        }

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
            return SYSCTL_CLK_ROOT_PLL0_DIV_4;                   //always pll0_div4

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART0_SCLK:
        {
            if(0 == ((sysctl_clk->uart0_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        }
        case SYSCTL_CLK_UART1_SCLK:
        {
            if(0 == ((sysctl_clk->uart1_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        }
        case SYSCTL_CLK_UART2_SCLK:
        {
            if(0 == ((sysctl_clk->uart2_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        }
        case SYSCTL_CLK_UART3_SCLK:
        {
            if(0 == ((sysctl_clk->uart3_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
        }

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
        {
            if(0 == ((sysctl_clk->spi0_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0;
        }
        case SYSCTL_CLK_SPI1_SCLK:
        {
            if(0 == ((sysctl_clk->spi1_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0;
        }
        case SYSCTL_CLK_SPI2_SCLK:
        {
            if(0 == ((sysctl_clk->spi2_sclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN0;
            else
                return SYSCTL_CLK_ROOT_PLL0;
        }
        case SYSCTL_CLK_SPI3_SCLK:
        {
            return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
        {
            return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------i2c system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
        {
            if(0 == ((sysctl_clk->i2c0_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C1_SCLK:
        {
            if(0 == ((sysctl_clk->i2c1_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C2_SCLK:
        {
            if(0 == ((sysctl_clk->i2c2_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C3_SCLK:
        {
            if(0 == ((sysctl_clk->i2c3_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C4_SCLK:
        {
            if(0 == ((sysctl_clk->i2c4_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C5_SCLK:
        {
            if(0 == ((sysctl_clk->i2c5_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_I2C6_SCLK:
        {
            if(0 == ((sysctl_clk->i2c6_icclk_cfg >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_PLL0_DIV_4;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
        case SYSCTL_CLK_WDT1_TCLK:
        case SYSCTL_CLK_WDT2_TCLK:
        {
            return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------VAD system clock---------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
        {
            return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 0) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_TIMER1_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 4) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_TIMER2_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 8) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_TIMER3_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 12) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_TIMER4_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 16) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }
        case SYSCTL_CLK_TIMER5_TCLK:
        {
            if(0 == ((sysctl_clk->timer_tclk_src >> 20) & 0x1))
                return SYSCTL_CLK_ROOT_OSC_IN1;
            else
                return SYSCTL_CLK_ROOT_OSC_IN0;
        }

        /*---------------------------usb clock----------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            return SYSCTL_CLK_ROOT_OSC_IN0;
        case SYSCTL_CLK_USB_WAKEUP:
            return SYSCTL_CLK_ROOT_OSC_IN1;

        default:
            return SYSCTL_CLK_ROOT_MAX;
    }
}

void sysctl_clk_set_leaf_en(sysctl_clk_node_e leaf, bool enable)
{
    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
            break;
        case SYSCTL_CLK_AX25M_CORE_0:
            sysctl_clk->ax25m_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_AX25M_CORE_1:
            sysctl_clk->ax25m_clk_cfg = (enable == true) ? ((1 << 9) | (1 << 27)) : ((0 << 9) | (1 << 27));
            break;
        case SYSCTL_CLK_AX25M_CORE_0_DC:
            sysctl_clk->ax25m_clk_cfg = (enable == true) ? ((1 << 10) | (1 << 28)) : ((0 << 10) | (1 << 28));
            break;
        case SYSCTL_CLK_AX25M_CORE_1_DC:
            sysctl_clk->ax25m_clk_cfg = (enable == true) ? ((1 << 11) | (1 << 29)) : ((0 << 11) | (1 << 29));
            break;
        case SYSCTL_CLK_AX25M_MCTL:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 9) | (1 << 20)) : ((0 << 9) | (1 << 20));
            break;
        /* AX25MP machine timer */
        case SYSCTL_CLK_AX25M_MTIMER:
            sysctl_clk->ax25m_mtimer_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_SRC:
            break;
        case SYSCTL_CLK_AX25P_CORE:
            sysctl_clk->ax25p_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_AX25P_LM:
            sysctl_clk->ax25p_clk_cfg = (enable == true) ? ((1 << 9) | (1 << 27)) : ((0 << 9) | (1 << 27));
            break;
        /* AX25MP machine timer */
        case SYSCTL_CLK_AX25P_MTIMER:
            sysctl_clk->ax25p_mtimer_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
            sysctl_clk->gnne_sysclk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_GNNE_AXI:
            break;
        case SYSCTL_CLK_GNNE_AXI_NOC:
            sysctl_clk->ai_gnne_aclk_cfg = (enable == true) ? ((1 << 9) | (1 << 27)) : ((0 << 9) | (1 << 27));
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 10) | (1 << 21)) : ((0 << 10) | (1 << 21));


        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:/*noc clk0 and clk1 cannot be gated*/
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            break;

        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
            sysctl_clk->sram_bus_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
            sysctl_clk->sram_bus_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 12) | (1 << 23)) : ((0 << 12) | (1 << 23));
            break;

        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 13) | (1 << 24)) : ((0 << 13) | (1 << 24));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
            sysctl_clk->usb_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 7) | (1 << 23)) : ((0 << 7) | (1 << 23));
            break;

        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            sysctl_clk->stor_sys_bus_clk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;

        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 6) | (1 << 22)) : ((0 << 6) | (1 << 22));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 9) | (1 << 25)) : ((0 << 9) | (1 << 25));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 8) | (1 << 24)) : ((0 << 8) | (1 << 24));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 7) | (1 << 23)) : ((0 << 7) | (1 << 23));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
            sysctl_clk->soc_i2c_pclk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
            sysctl_clk->soc_i2c_pclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
            sysctl_clk->soc_i2c_pclk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
            sysctl_clk->soc_i2c_pclk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 10) | (1 << 26)) : ((0 << 10) | (1 << 26));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 11) | (1 << 27)) : ((0 << 11) | (1 << 27));
            break;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            sysctl_clk->soc_ctl_pclk_en = (enable == true) ? ((1 << 12) | (1 << 28)) : ((0 << 12) | (1 << 28));
            break;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
            break;

        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 11) | (1 << 22)) : ((0 << 11) | (1 << 22));
            break;
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
            sysctl_clk->h264_aclk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
            sysctl_clk->disp_sys_aclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
            sysctl_clk->disp_sys_aclk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
            sysctl_clk->isp_sys_aclk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
            sysctl_clk->isp_sys_aclk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
            sysctl_clk->isp_sys_aclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
            sysctl_clk->isp_sys_aclk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:
            sysctl_clk->isp_sys_aclk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:
            break;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 10) | (1 << 26)) : ((0 << 10) | (1 << 26));
            break;

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 6) | (1 << 22)) : ((0 << 6) | (1 << 22));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 7) | (1 << 23)) : ((0 << 7) | (1 << 23));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 8) | (1 << 24)) : ((0 << 8) | (1 << 24));
            break;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:
            sysctl_clk->peri_sys_bus_clk_en = (enable == true) ? ((1 << 9) | (1 << 25)) : ((0 << 9) | (1 << 25));
            break;

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:
            break;

        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 6) | (1 << 22)) : ((0 << 6) | (1 << 22));
            break;
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 7) | (1 << 23)) : ((0 << 7) | (1 << 23));
            break;
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 10) | (1 << 26)) : ((0 << 10) | (1 << 26));
            break;
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
            sysctl_clk->mipi_rxdphy_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            sysctl_clk->isp_sys_pclk_en = (enable == true) ? ((1 << 8) | (1 << 24)) : ((0 << 8) | (1 << 24));
            break;

        /*---------------------------DISPLAY------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
            break;

        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
            sysctl_clk->disp_sys_pclk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
            sysctl_clk->dsi_sys_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
            sysctl_clk->disp_sys_pclk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
            sysctl_clk->disp_sys_pclk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            sysctl_clk->disp_sys_pclk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;

        /*---------------------------csi0_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
            sysctl_clk->csi0_sys_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------csi1_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_1_SYSTEM:
            sysctl_clk->csi1_sys_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
            sysctl_clk->csi0_pixel_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
            sysctl_clk->csi1_pixel_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
            sysctl_clk->tpg_pixel_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
            sysctl_clk->disp_pixel_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
            sysctl_clk->audif_sclk_cfg1 = (enable == true) ? ((1 << 20) | (1 << 25)) : ((0 << 20) | (1 << 25));
            break;

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
            sysctl_clk->audif_devclk_cfg = (enable == true) ? ((1 << 20) | (1 << 25)) : ((0 << 20) | (1 << 25));
            break;

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
            break;
        case SYSCTL_CLK_SD_MASTER_SD_0:
            sysctl_clk->sd_card_clk_cfg = (enable == true) ? ((1 << 0) | (1 << 24)) : ((0 << 0) | (1 << 24));
            break;
        case SYSCTL_CLK_SD_MASTER_SD_1:
            sysctl_clk->sd_card_clk_cfg = (enable == true) ? ((1 << 4) | (1 << 25)) : ((0 << 1) | (1 << 25));
            break;
        case SYSCTL_CLK_SD_MASTER_SD_2:
            sysctl_clk->sd_card_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 2) | (1 << 26));
            break;

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
            break;
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            sysctl_clk->mipi_txdphy_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            sysctl_clk->mipi_rxdphy_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            sysctl_clk->mipi_txdphy_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 6) | (1 << 22)) : ((0 << 6) | (1 << 22));
            break;
        case SYSCTL_CLK_PUF_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 5) | (1 << 21)) : ((0 << 5) | (1 << 21));
            break;
        case SYSCTL_CLK_OTP_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 4) | (1 << 20)) : ((0 << 4) | (1 << 20));
            break;
        case SYSCTL_CLK_ROM_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 3) | (1 << 19)) : ((0 << 3) | (1 << 19));
            break;
        case SYSCTL_CLK_RSA_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_AES_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;
        case SYSCTL_CLK_SHA_HCLK:
            sysctl_clk->sec_sys_bus_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
            sysctl_clk->mem_ctl_clk_cfg = (enable == true) ? ((1 << 8) | (1 << 19)) : ((0 << 8) | (1 << 19));
            break;

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
            sysctl_clk->emac_trx_clk_cfg = (enable == true) ? ((1 << 3) | (1 << 24)) : ((0 << 3) | (1 << 24));
            break;

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART0_SCLK:
            sysctl_clk->uart0_sclk_cfg = (enable == true) ? ((1 << 12) | (1 << 26)) : ((0 << 12) | (1 << 26));
            break;
        case SYSCTL_CLK_UART1_SCLK:
            sysctl_clk->uart1_sclk_cfg = (enable == true) ? ((1 << 12) | (1 << 26)) : ((0 << 12) | (1 << 26));
            break;
        case SYSCTL_CLK_UART2_SCLK:
            sysctl_clk->uart2_sclk_cfg = (enable == true) ? ((1 << 12) | (1 << 26)) : ((0 << 12) | (1 << 26));
            break;
        case SYSCTL_CLK_UART3_SCLK:
            sysctl_clk->uart3_sclk_cfg = (enable == true) ? ((1 << 12) | (1 << 26)) : ((0 << 12) | (1 << 26));
            break;

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
            sysctl_clk->spi0_sclk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_SPI1_SCLK:
            sysctl_clk->spi1_sclk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_SPI2_SCLK:
            sysctl_clk->spi2_sclk_cfg = (enable == true) ? ((1 << 8) | (1 << 26)) : ((0 << 8) | (1 << 26));
            break;
        case SYSCTL_CLK_SPI3_SCLK:
            sysctl_clk->spi3_sclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
            sysctl_clk->otp_clk_en = (enable == true) ? ((1 << 0) | (1 << 16)) : ((0 << 0) | (1 << 16));
            break;

        /*---------------------------i2c system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
            sysctl_clk->i2c0_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C1_SCLK:
            sysctl_clk->i2c1_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C2_SCLK:
            sysctl_clk->i2c2_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C3_SCLK:
            sysctl_clk->i2c3_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C4_SCLK:
            sysctl_clk->i2c4_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C5_SCLK:
            sysctl_clk->i2c5_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_I2C6_SCLK:
            sysctl_clk->i2c6_icclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
            sysctl_clk->wdt0_tclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_WDT1_TCLK:
            sysctl_clk->wdt1_tclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;
        case SYSCTL_CLK_WDT2_TCLK:
            sysctl_clk->wdt2_tclk_cfg = (enable == true) ? ((1 << 8) | (1 << 25)) : ((0 << 8) | (1 << 25));
            break;

        /*---------------------------VAD system clock---------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
            sysctl_clk->vad_sclk_cfg = (enable == true) ? ((1 << 18) | (1 << 25)) : ((0 << 18) | (1 << 25));
            break;

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
        case SYSCTL_CLK_TIMER1_TCLK:
        case SYSCTL_CLK_TIMER2_TCLK:
        case SYSCTL_CLK_TIMER3_TCLK:
        case SYSCTL_CLK_TIMER4_TCLK:
        case SYSCTL_CLK_TIMER5_TCLK:
            sysctl_clk->timer_tclk_cfg0 = (enable == true) ? ((1 << 24) | (1 << 29)) : ((0 << 24) | (1 << 29));
            break;

        /*------------------------------------usb clock-------------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            sysctl_clk->usb_clk_en = (enable == true) ? ((1 << 2) | (1 << 18)) : ((0 << 2) | (1 << 18));
            break;
        case SYSCTL_CLK_USB_WAKEUP:
            sysctl_clk->usb_clk_en = (enable == true) ? ((1 << 1) | (1 << 17)) : ((0 << 1) | (1 << 17));
            break;

        case SYSCTL_CLK_I2SS_SCLK:
            sysctl_clk->i2s2_sclk_cfg = (enable == true) ? ((1 << 21) | (1 << 27)) : ((0 << 21) | (1 << 27));
            break;

        default:
            break;
    }
}
bool sysctl_clk_get_leaf_en(sysctl_clk_node_e leaf)
{
    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
            return true;
        case SYSCTL_CLK_AX25M_CORE_0:
            return (0 == ((sysctl_clk->ax25m_clk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_AX25M_CORE_1:
            return (0 == ((sysctl_clk->ax25m_clk_cfg >> 9) & 0x1)) ? false: true;
        case SYSCTL_CLK_AX25M_CORE_0_DC:
            return (0 == ((sysctl_clk->ax25m_clk_cfg >> 10) & 0x1)) ? false: true; 
        case SYSCTL_CLK_AX25M_CORE_1_DC:
            return (0 == ((sysctl_clk->ax25m_clk_cfg >> 11) & 0x1)) ? false: true;
        case SYSCTL_CLK_AX25M_MTIMER:
            return (0 == ((sysctl_clk->ax25m_mtimer_clk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_AX25M_MCTL:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 9) & 0x1)) ? false:true;

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_SRC:
            return true;
        case SYSCTL_CLK_AX25P_CORE:
            return (0 == ((sysctl_clk->ax25p_clk_cfg >> 8) & 0x1)) ? false:true;
            break;
        case SYSCTL_CLK_AX25P_LM:
            return (0 == ((sysctl_clk->ax25p_clk_cfg >> 9) & 0x1)) ? false:true;
            break;
        case SYSCTL_CLK_AX25P_MTIMER:
            return (0 == ((sysctl_clk->ax25p_mtimer_clk_cfg >> 8) & 0x1)) ? false:true;

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
            return (0 == ((sysctl_clk->gnne_sysclk_cfg >> 8) & 0x1)) ? false:true;
        case SYSCTL_CLK_GNNE_AXI:
            return true;
        case SYSCTL_CLK_GNNE_AXI_NOC:
            return (0 == ((sysctl_clk->ai_gnne_aclk_cfg >> 9) & 0x1)) ? false:true;
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 10) & 0x1)) ? false:true;


        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:/*noc clk0 and clk1 cannot be gated*/
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            return true;

        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 4) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 5) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
            return (0 == ((sysctl_clk->sram_bus_clk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
            return (0 == ((sysctl_clk->sram_bus_clk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 12) & 0x1)) ? false:true;

        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 13) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
            return (0 == ((sysctl_clk->usb_clk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 7) & 0x1)) ? false:true;


        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 3) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 4) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            return (0 == ((sysctl_clk->stor_sys_bus_clk_en >> 5) & 0x1)) ? false:true;

        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 3) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 4) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 5) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 6) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 9) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 8) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 7) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
            return (0 == ((sysctl_clk->soc_i2c_pclk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
            return (0 == ((sysctl_clk->soc_i2c_pclk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
            return (0 == ((sysctl_clk->soc_i2c_pclk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
            return (0 == ((sysctl_clk->soc_i2c_pclk_en >> 3) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 10) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 11) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            return (0 == ((sysctl_clk->soc_ctl_pclk_en >> 12) & 0x1)) ? false:true;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
            return true;
        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 11) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
            return (0 == ((sysctl_clk->h264_aclk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
            return (0 == ((sysctl_clk->disp_sys_aclk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
            return (0 == ((sysctl_clk->disp_sys_aclk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
            return (0 == ((sysctl_clk->isp_sys_aclk_en >> 5) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
            return (0 == ((sysctl_clk->isp_sys_aclk_en >> 4) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
            return (0 == ((sysctl_clk->isp_sys_aclk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
            return (0 == ((sysctl_clk->isp_sys_aclk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:
            return (0 == ((sysctl_clk->isp_sys_aclk_en >> 3) & 0x1)) ? false:true;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:
            return true;

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 0) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 3) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 5) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 10) & 0x1)) ? false:true;

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
            return true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 6) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 7) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 8) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:
            return (0 == ((sysctl_clk->peri_sys_bus_clk_en >> 9) & 0x1)) ? false:true;

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:
            return true;

        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 4) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 5) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 6) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 7) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 1) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 2) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 3) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 10) & 0x1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
            return (0 == ((sysctl_clk->mipi_rxdphy_clk_en >> 1) & 1)) ? false:true;
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            return (0 == ((sysctl_clk->isp_sys_pclk_en >> 8) & 0x1)) ? false:true;

        /*---------------------------DISPLAY------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
           return true;

        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
            return (0 == ((sysctl_clk->disp_sys_pclk_en >> 2) & 1)) ? false:true;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
            return (0 == ((sysctl_clk->dsi_sys_clk_cfg >> 8) & 1)) ? false:true;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
            return (0 == ((sysctl_clk->disp_sys_pclk_en >> 1) & 1)) ? false:true;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
            return (0 == ((sysctl_clk->disp_sys_pclk_en >> 0) & 1)) ? false:true;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            return (0 == ((sysctl_clk->disp_sys_pclk_en >> 3) & 1)) ? false:true;

        /*---------------------------csi0_system_clk----------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
            return (0 == ((sysctl_clk->csi0_sys_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------csi1_system_clk----------------------------*/
        case SYSCTL_CLK_CSI_1_SYSTEM:
            return (0 == ((sysctl_clk->csi1_sys_clk_cfg >> 8) & 1)) ? false:true;
        
        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
            return (0 == ((sysctl_clk->csi0_pixel_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
            return (0 == ((sysctl_clk->csi1_pixel_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
            return (0 == ((sysctl_clk->tpg_pixel_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
            return (0 == ((sysctl_clk->disp_pixel_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
            return (0 == ((sysctl_clk->audif_sclk_cfg1 >> 20) & 1)) ? false:true;

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
            return (0 == ((sysctl_clk->audif_devclk_cfg >> 20) & 1)) ? false:true;

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
            return true;
        case SYSCTL_CLK_SD_MASTER_SD_0:
            return (0 == ((sysctl_clk->sd_card_clk_cfg >> 0) & 1)) ? false:true;
        case SYSCTL_CLK_SD_MASTER_SD_1:
            return (0 == ((sysctl_clk->sd_card_clk_cfg >> 4) & 1)) ? false:true;
        case SYSCTL_CLK_SD_MASTER_SD_2:
            return (0 == ((sysctl_clk->sd_card_clk_cfg >> 8) & 1)) ? false:true;

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
            return true;
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            return (0 == ((sysctl_clk->mipi_txdphy_clk_en >> 1) & 1)) ? false:true;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            return (0 == ((sysctl_clk->mipi_rxdphy_clk_en >> 0) & 1)) ? false:true;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            return (0 == ((sysctl_clk->mipi_txdphy_clk_en >> 0) & 1)) ? false:true;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 6) & 0x1)) ? false: true;
        case SYSCTL_CLK_PUF_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 5) & 0x1)) ? false: true;
        case SYSCTL_CLK_OTP_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 4) & 0x1)) ? false: true;
        case SYSCTL_CLK_ROM_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 3) & 0x1)) ? false: true;
        case SYSCTL_CLK_RSA_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 2) & 0x1)) ? false: true;
        case SYSCTL_CLK_AES_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 1) & 0x1)) ? false: true;
        case SYSCTL_CLK_SHA_HCLK:
            return (0 == ((sysctl_clk->sec_sys_bus_clk_en >> 0) & 0x1)) ? false: true;

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
            return (0 == ((sysctl_clk->mem_ctl_clk_cfg >> 8) & 0x1)) ? false: true;

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
            return (0 == ((sysctl_clk->emac_trx_clk_cfg >> 3) & 0x1)) ? false: true;

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART0_SCLK:
            return (0 == ((sysctl_clk->uart0_sclk_cfg >> 12) & 0x1)) ? false: true;
        case SYSCTL_CLK_UART1_SCLK:
            return (0 == ((sysctl_clk->uart1_sclk_cfg >> 12) & 0x1)) ? false: true;
        case SYSCTL_CLK_UART2_SCLK:
            return (0 == ((sysctl_clk->uart2_sclk_cfg >> 12) & 0x1)) ? false: true;
        case SYSCTL_CLK_UART3_SCLK:
            return (0 == ((sysctl_clk->uart3_sclk_cfg >> 12) & 0x1)) ? false: true;

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
            return (0 == ((sysctl_clk->spi0_sclk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_SPI1_SCLK:
            return (0 == ((sysctl_clk->spi1_sclk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_SPI2_SCLK:
            return (0 == ((sysctl_clk->spi2_sclk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_SPI3_SCLK:
            return (0 == ((sysctl_clk->spi3_sclk_cfg >> 8) & 0x1)) ? false: true;

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
            return (0 == ((sysctl_clk->otp_clk_en >> 0) & 0x1)) ? false: true;

        /*---------------------------i2c system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
            return (0 == ((sysctl_clk->i2c0_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C1_SCLK:
            return (0 == ((sysctl_clk->i2c1_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C2_SCLK:
            return (0 == ((sysctl_clk->i2c2_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C3_SCLK:
            return (0 == ((sysctl_clk->i2c3_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C4_SCLK:
            return (0 == ((sysctl_clk->i2c4_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C5_SCLK:
            return (0 == ((sysctl_clk->i2c5_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;
        case SYSCTL_CLK_I2C6_SCLK:
            return (0 == ((sysctl_clk->i2c6_icclk_cfg >> 8) & 0x1)) ? false: true;
            break;

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
            return (0 == ((sysctl_clk->wdt0_tclk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_WDT1_TCLK:
            return (0 == ((sysctl_clk->wdt1_tclk_cfg >> 8) & 0x1)) ? false: true;
        case SYSCTL_CLK_WDT2_TCLK:
            return (0 == ((sysctl_clk->wdt2_tclk_cfg >> 8) & 0x1)) ? false: true;

        /*---------------------------VAD system clock---------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
            return (0 == ((sysctl_clk->vad_sclk_cfg >> 18) & 0x1)) ? false: true;

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
        case SYSCTL_CLK_TIMER1_TCLK:
        case SYSCTL_CLK_TIMER2_TCLK:
        case SYSCTL_CLK_TIMER3_TCLK:
        case SYSCTL_CLK_TIMER4_TCLK:
        case SYSCTL_CLK_TIMER5_TCLK:
            return (0 == ((sysctl_clk->timer_tclk_cfg0 >> 24) & 0x1)) ? false: true;

        /*------------------------------------usb clock-------------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            return (0 == ((sysctl_clk->usb_clk_en >> 2) & 0x1)) ? false: true;
        case SYSCTL_CLK_USB_WAKEUP:
            return (0 == ((sysctl_clk->usb_clk_en >> 1) & 0x1)) ? false: true;

        case SYSCTL_CLK_I2SS_SCLK:
            return (0 == ((sysctl_clk->i2s2_sclk_cfg >> 21) & 0x1)) ? false: true;
        default:
            return true;
    }
}
/* freq = root_freq * numerator / denominator */
bool sysctl_clk_set_leaf_div(sysctl_clk_node_e leaf, uint32_t numerator, uint32_t denominator)
{
    if(denominator == 0)
        return false;

    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
        {
            if((numerator > 12) || (numerator < 1) || (denominator != 12) )
                return false;
            else
            {
                /* 12/12 --- 1/12 */
                sysctl_clk->ax25m_clk_cfg = (((12-numerator) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_AX25M_CORE_0:
        case SYSCTL_CLK_AX25M_CORE_1:
        case SYSCTL_CLK_AX25M_CORE_0_DC:
        case SYSCTL_CLK_AX25M_CORE_1_DC:
        case SYSCTL_CLK_AX25M_MCTL:
            return false;
        case SYSCTL_CLK_AX25M_MTIMER:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->ax25m_mtimer_clk_cfg = (((denominator- 1) << 2) | (1 << 25));
                return true;
            }
        }

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_SRC:
        {
            if((numerator > 6) || (numerator < 1) || (denominator != 6) )
                return false;
            else
            {
                /* 6/6 --- 1/6 */
                sysctl_clk->ax25p_clk_cfg = (((6-numerator) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_AX25P_CORE:
        case SYSCTL_CLK_AX25P_LM:
            return false;
        case SYSCTL_CLK_AX25P_MTIMER:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->ax25p_mtimer_clk_cfg = (((denominator- 1) << 2) | (1 << 25));
                return true;
            }
        }

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
        {
            if((numerator > 6) || (numerator < 1) || (denominator != 6))
                return false;
            else
            {
                /* 6/6 --- 1/6 */
                sysctl_clk->gnne_sysclk_cfg = (((6-numerator) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_GNNE_AXI:
        {
            if((numerator > 6) || (numerator < 1) || (denominator != 6))
                return false;
            else
            {
                /* 6/6 --- 1/6 */
                sysctl_clk->ai_gnne_aclk_cfg = (((6-numerator) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_GNNE_AXI_NOC:
            return false;
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            return false;

        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:
        {
            if((numerator > 6) || (numerator < 1) || (denominator != 6) )
                return false;
            else
            {
                /* 6/6 --- 1/6 */
                sysctl_clk->noc_clk_cfg = (((6-numerator) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            return false;

        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            return false;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            return false;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
        {
            if((numerator > 6) || (numerator < 1) || (denominator != 6) )
                return false;
            else
            {
                /* 6/6 --- 1/6 */
                sysctl_clk->noc_clk_cfg = (((6-numerator) << 8) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:

        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            return false;

        /*---------------------------DISPLAY------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 0 for 16/16*/
                sysctl_clk->disp_sys_pclk_en = (((denominator- 1) << 4) | (1 << 20));
                return true;
            }
        }
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
            return false;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
            return false;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
            return false;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
            return false;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            return false;

        /*---------------------------csi0_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 0 for 16/16*/
                sysctl_clk->csi0_sys_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------csi1_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_1_SYSTEM:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
               /* 1/1 --- 1/16 0 for 16/16*/
                sysctl_clk->csi1_sys_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 128))
                return false;
            else
            {
                /* 1/1 --- 1/128 0 for 128/128*/
                sysctl_clk->csi0_pixel_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 128))
                return false;
            else
            {
                /* 1/1 --- 1/128 0 for 128/128*/
                sysctl_clk->csi1_pixel_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 128))
                return false;
            else
            {
                /* 1/1 --- 1/128 0 for 128/128*/
                sysctl_clk->tpg_pixel_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 128))
                return false;
            else
            {
                /* 1/1 --- 1/128 0 for 128/128*/
                sysctl_clk->disp_pixel_clk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            if((numerator < 1) || (numerator > 0xff) || (denominator < 0x10) || (denominator > 0xfff))
                return false;
            if(numerator * 4 > denominator)         //The frequency division should be at least 4 times
                return false;

            sysctl_clk->audif_sclk_cfg1 = ((numerator << 12) | (denominator << 0) | (1 << 24));
            return true;
        }

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            if((numerator < 1) || (numerator > 0xff) || (denominator < 0x10) || (denominator > 0xfff))
                return false;
            if(numerator * 4 > denominator)         //The frequency division should be at least 4 times
                return false;
            sysctl_clk->audif_devclk_cfg = ((numerator << 12) | (denominator << 0) | (1 << 24));
            return true;
        }

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
            return false;                       //always div 5
        case SYSCTL_CLK_SD_MASTER_SD_0:
            return false;
        case SYSCTL_CLK_SD_MASTER_SD_1:
            return false;
        case SYSCTL_CLK_SD_MASTER_SD_2:
            return false;

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16)) /*1/1 - 1/16*/
                return false;
            sysctl_clk->mipi_txdphy_clk_en = (((denominator- 1) << 4) | (1 << 19));
            return true;
        }
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            return false;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            return false;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            return false;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
        {
            if((numerator > 8) || (numerator < 1) || (denominator != 8) )
                return false;
            else
            {
                /* 8/8 --- 1/8 */
                sysctl_clk->sec_sys_bus_clk = (((8-numerator) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_PUF_HCLK:
        case SYSCTL_CLK_OTP_HCLK:
        case SYSCTL_CLK_ROM_HCLK:
        case SYSCTL_CLK_RSA_HCLK:
        case SYSCTL_CLK_AES_HCLK:
        case SYSCTL_CLK_SHA_HCLK:
            return false; /* cannot div */

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
        {
            if((numerator != 1) || (denominator < 2) || (denominator > 4) )
                return false;
            else
            {
                /* 1/2 --- 1/4 */
                sysctl_clk->mem_ctl_clk_cfg = (((denominator-1) << 4) | (1 << 17));
                return true;
            }
        }

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
        {
            if((numerator != 1) || (denominator < 2) || (denominator > 128) )
                return false;
            else
            {
                /* 1/2 --- 1/128 */
                sysctl_clk->emac_trx_clk_cfg = (((denominator-1) << 10) | (1 << 31));
                return true;
            }
        }

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART0_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->uart0_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_UART1_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->uart1_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_UART2_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->uart2_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_UART3_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 32))
                return false;
            else
            {
                /* 1/1 --- 1/32 */
                sysctl_clk->uart3_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->spi0_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_SPI1_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->spi1_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_SPI2_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->spi2_sclk_cfg = (((denominator- 1) << 4) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_SPI3_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 16))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->spi3_sclk_cfg = (((denominator- 1) << 4) | (1 << 24));
                return true;
            }
        }

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
            return false; /* hareware div ,cannot be set by software */

        /*---------------------------i2c system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c0_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C1_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c1_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C2_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c2_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C3_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c3_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C4_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c4_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C5_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c5_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_I2C6_SCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/16 */
                sysctl_clk->i2c6_icclk_cfg = (((denominator- 1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->wdt0_tclk_cfg = (((denominator-1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_WDT1_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->wdt1_tclk_cfg = (((denominator-1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_WDT2_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->wdt2_tclk_cfg = (((denominator-1) << 0) | (1 << 24));
                return true;
            }
        }

        /*---------------------------VAD system clock---------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
        {
            if((numerator < 1) || (numerator > 0x3f) || (denominator < 0x20) || (denominator > 0xfff))
                return false;
            if(numerator * 4 > denominator)         //The frequency division should be at least 4 times
                return false;

            sysctl_clk->vad_sclk_cfg = ((numerator << 12) | (denominator << 0) | (1 << 24));
            return true;
        }

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg0 = (((denominator-1) << 0) | (1 << 25));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER1_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg0 = (((denominator-1) << 6) | (1 << 26));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER2_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg0 = (((denominator-1) << 12) | (1 << 27));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER3_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg0 = (((denominator-1) << 18) | (1 << 28));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER4_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg1 = (((denominator-1) << 0) | (1 << 24));
                return true;
            }
        }
        case SYSCTL_CLK_TIMER5_TCLK:
        {
            if((numerator != 1) || (denominator < 1) || (denominator > 64))
                return false;
            else
            {
                /* 1/1 --- 1/64 */
                sysctl_clk->timer_tclk_cfg1 = (((denominator-1) << 6) | (1 << 25));
                return true;
            }
        }

        /*------------------------------------usb clock-------------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            return false;
        case SYSCTL_CLK_USB_WAKEUP:
            return false;

        default:
            return false;
    }
}

double sysctl_clk_get_leaf_div(sysctl_clk_node_e leaf)
{
    switch(leaf)
    {
        /*---------------------------AX25MP------------------------------------*/
        case SYSCTL_CLK_AX25M_SRC:
            return (double)(12.0 - ((sysctl_clk->ax25m_clk_cfg >> 4) & 0xF)) / 12.0;
        case SYSCTL_CLK_AX25M_CORE_0:
        case SYSCTL_CLK_AX25M_CORE_1:
        case SYSCTL_CLK_AX25M_CORE_0_DC:
        case SYSCTL_CLK_AX25M_CORE_1_DC:
        case SYSCTL_CLK_AX25M_MCTL:
            return 1;
        case SYSCTL_CLK_AX25M_MTIMER:
            return 1.0/(double)(((sysctl_clk->ax25m_mtimer_clk_cfg >> 2) & 0x1F) + 1);

        /*---------------------------AX25P------------------------------------*/
        case SYSCTL_CLK_AX25P_SRC:
            return (double)(6.0 - ((sysctl_clk->ax25p_clk_cfg >> 4) & 0x7)) / 6.0;
        case SYSCTL_CLK_AX25P_CORE:
        case SYSCTL_CLK_AX25P_LM:
            return 1;
        case SYSCTL_CLK_AX25P_MTIMER:
            return 1.0/(double)(((sysctl_clk->ax25p_mtimer_clk_cfg >> 2) & 0x1F) + 1);

        /*---------------------------GNNE------------------------------------*/
        case SYSCTL_CLK_GNNE_SYS:
            return (double)(6.0 - ((sysctl_clk->gnne_sysclk_cfg >> 4) & 0x7)) / 6.0;
        case SYSCTL_CLK_GNNE_AXI:
            return (double)(6.0 - ((sysctl_clk->ai_gnne_aclk_cfg >> 4) & 0x7)) / 6.0;
        case SYSCTL_CLK_GNNE_AXI_NOC:
            return 1;
        case SYSCTL_CLK_GNNE_AXI_MCTL:
            return 1;

        /*---------------------------NOC0------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_0:
            return (double)(6.0 - ((sysctl_clk->noc_clk_cfg >> 4) & 0x7)) / 6.0;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2:
            return 2;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3:
            return 3;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4:
            return 4;
        case SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM0_AXI:
        case SYSCTL_CLK_NOC_CLK_0_SRAM1_AXI:
        case SYSCTL_CLK_NOC_CLK_0_AXI_P3:
            return 1;
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_MCTL_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB:
            return 1;
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_PERI_DMA_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_3_SYS_DMA_APB:
            return 1;
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_WDT_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_TIMER_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_RTC_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_GPIO_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_IOMUX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_0_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_1_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_2_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_3_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_4_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_5_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_I2C_6_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_PWM_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_MAILBOX_APB:
        case SYSCTL_CLK_NOC_CLK_0_DIV_4_VAD_APB:
            return 1;

        /*---------------------------NOC1------------------------------------*/
        case SYSCTL_CLK_NOC_CLK_1:
            return (double)(6.0 - ((sysctl_clk->noc_clk_cfg >> 8) & 0x7)) / 6.0;
        
        case SYSCTL_CLK_NOC_CLK_1_AXI_MCTL:
        case SYSCTL_CLK_NOC_CLK_1_H264_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VO_AXI:
        case SYSCTL_CLK_NOC_CLK_1_TWOD_AXI:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_AXI:
        case SYSCTL_CLK_NOC_CLK_1_VI_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI:
        case SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI:

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB:

        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_UART_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_I2S_S_APB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_APB_AUDIO_APB:

        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_0_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_1_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_2_AHB:
        case SYSCTL_CLK_NOC_CLK_1_PERI_AHB_SPI_3_AHB:
            return 1;

        case SYSCTL_CLK_NOC_CLK_1_DIV_4:
            return 4;

        case SYSCTL_CLK_NOC_CLK_1_CSI_0_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_1_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_2_APB:
        case SYSCTL_CLK_NOC_CLK_1_CSI_3_APB:
        case SYSCTL_CLK_NOC_CLK_1_F2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_R2K_APB:
        case SYSCTL_CLK_NOC_CLK_1_TOF_APB:
        case SYSCTL_CLK_NOC_CLK_1_MFBC_APB:
        case SYSCTL_CLK_NOC_CLK_1_MIPI_CORNER_APB:
        case SYSCTL_CLK_NOC_CLK_1_VI_APB:
            return 1;

        /*---------------------------DISPLAY------------------------------------*/
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV:
        {
            return 1.0 / (double)(((sysctl_clk->disp_sys_pclk_en >> 4) & 0xF) + 1);
        }
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_APB:
            return 1;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_DSI_SYSTEM:
            return 1;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_VO_APB:
            return 1;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_TWOD_APB:
            return 1;
        case SYSCTL_CLK_DISP_SYS_AND_APB_CLK_DIV_BT1120_APB:
            return 1;

        /*---------------------------csi0_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_0_SYSTEM:
        {
            return 1.0 / (double)(((sysctl_clk->csi0_sys_clk_cfg >> 0) & 0xF) + 1);
        }

        /*---------------------------csi1_system_clk-----------------------------*/
        case SYSCTL_CLK_CSI_1_SYSTEM:
        {
            return 1.0 / (double)(((sysctl_clk->csi1_sys_clk_cfg >> 0) & 0xF) + 1);
        }

        /*---------------------------csi0_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_0_PIXEL:
        {
            return 1.0 / (double)(((sysctl_clk->csi0_pixel_clk_cfg >> 0) & 0x7F) + 1);
        }

        /*---------------------------csi1_pixel_clk------------------------------*/
        case SYSCTL_CLK_CSI_1_PIXEL:
        {
            return 1.0 / (double)(((sysctl_clk->csi1_pixel_clk_cfg >> 0) & 0x7F) + 1);
        }

        /*---------------------------tpg_pixel_clk------------------------------*/
        case SYSCTL_CLK_TPG_PIXEL:
        {
            return 1.0 / (double)(((sysctl_clk->tpg_pixel_clk_cfg >> 0) & 0x7F) + 1);
        }
        /*---------------------------disp_pixel_clk------------------------------*/
        case SYSCTL_CLK_DISPLAY_PIXEL:
        {
            return 1.0 / (double)(((sysctl_clk->disp_pixel_clk_cfg >> 0) & 0x7F) + 1);
        }

        /*---------------------------audio_out_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            return (double)((sysctl_clk->audif_sclk_cfg1 >> 12) & 0xFF)/(double)((sysctl_clk->audif_sclk_cfg1 >> 0) & 0xFFF);
        }

        /*---------------------------audio_in_serial_clk------------------------------*/
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            return (double)((sysctl_clk->audif_devclk_cfg >> 12) & 0xFF)/(double)((sysctl_clk->audif_devclk_cfg >> 0) & 0xFFF);
        }

        /*---------------------------sd master/sd 0/1/2 clk------------------------------*/
        case SYSCTL_CLK_SD_MASTER:
            return 5;
        case SYSCTL_CLK_SD_MASTER_SD_0:
            return 1;
        case SYSCTL_CLK_SD_MASTER_SD_1:
            return 1;
        case SYSCTL_CLK_SD_MASTER_SD_2:
            return 1;

        /*---------------------------mipi clocks-----------------------------------------*/
        case SYSCTL_CLK_MIPI_REF:
        {
            return 1.0 / (double)(((sysctl_clk->mipi_txdphy_clk_en >> 4) & 0xF) + 1);
        }
        case SYSCTL_CLK_MIPI_REF_TXPHY_REF:
            return 1;
        case SYSCTL_CLK_MIPI_REF_RXPHY_REF:
            return 1;
        case SYSCTL_CLK_MIPI_REF_TXPHY_PLL:
            return 1;

        /*---------------------------security ahb clocks-----------------------------------------*/
        case SYSCTL_CLK_SEC_HCLK:
            return (double)(8.0 - ((sysctl_clk->sec_sys_bus_clk >> 0) & 0x7)) / 8.0;
        case SYSCTL_CLK_PUF_HCLK:
        case SYSCTL_CLK_OTP_HCLK:
        case SYSCTL_CLK_ROM_HCLK:
        case SYSCTL_CLK_RSA_HCLK:
        case SYSCTL_CLK_AES_HCLK:
        case SYSCTL_CLK_SHA_HCLK:
            return 1;

        /*---------------------------ddr controller core clocks-----------------------------------*/
        case SYSCTL_CLK_DDR_CONTROLLER_CORE:
        {
            return 1.0 / (double)(((sysctl_clk->mem_ctl_clk_cfg >> 4) & 0x3) + 1);
        }

        /*---------------------------emac loopback clock------------------------------------------*/
        case SYSCTL_CLK_EMAC_LOOPBACK:
        {
            return 1.0 / (double)(((sysctl_clk->emac_trx_clk_cfg >> 10) & 0x3F) + 1);
        }

        /*---------------------------uart system clock--------------------------------------------*/
        case SYSCTL_CLK_UART0_SCLK:
            return 1.0 / (double)(((sysctl_clk->uart0_sclk_cfg >> 4) & 0x1F) + 1);
        case SYSCTL_CLK_UART1_SCLK:
            return 1.0 / (double)(((sysctl_clk->uart1_sclk_cfg >> 4) & 0x1F) + 1);
        case SYSCTL_CLK_UART2_SCLK:
            return 1.0 / (double)(((sysctl_clk->uart2_sclk_cfg >> 4) & 0x1F) + 1);
        case SYSCTL_CLK_UART3_SCLK:
            return 1.0 / (double)(((sysctl_clk->uart3_sclk_cfg >> 4) & 0x1F) + 1);

        /*---------------------------spi system clock---------------------------------------------*/
        case SYSCTL_CLK_SPI0_SCLK:
            return 1.0 / (double)(((sysctl_clk->spi0_sclk_cfg >> 4) & 0xF) + 1);
        case SYSCTL_CLK_SPI1_SCLK:
            return 1.0 / (double)(((sysctl_clk->spi1_sclk_cfg >> 4) & 0xF) + 1);
        case SYSCTL_CLK_SPI2_SCLK:
            return 1.0 / (double)(((sysctl_clk->spi2_sclk_cfg >> 4) & 0xF) + 1);
        case SYSCTL_CLK_SPI3_SCLK:
            return 1.0 / (double)(((sysctl_clk->spi3_sclk_cfg >> 4) & 0xF) + 1);

        /*---------------------------OTP system clock---------------------------------------------*/
        case SYSCTL_CLK_OTP_SCLK:
            return 2; /* hareware div ,cannot be set by software. 25M/2=12.5M*/

        /*---------------------------i2c system clock---------------------------------------------*/
        case SYSCTL_CLK_I2C0_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c0_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C1_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c1_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C2_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c2_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C3_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c3_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C4_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c4_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C5_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c5_icclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_I2C6_SCLK:
            return 1.0 / (double)(((sysctl_clk->i2c6_icclk_cfg >> 0) & 0x3F) + 1);

        /*---------------------------wdt system clock---------------------------------------------*/
        case SYSCTL_CLK_WDT0_TCLK:
            return 1.0 / (double)(((sysctl_clk->wdt0_tclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_WDT1_TCLK:
            return 1.0 / (double)(((sysctl_clk->wdt1_tclk_cfg >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_WDT2_TCLK:
            return 1.0 / (double)(((sysctl_clk->wdt2_tclk_cfg >> 0) & 0x3F) + 1);

        /*---------------------------vad system clk-----------------------------------------------*/
        case SYSCTL_CLK_VAD_TCLK:
            return (double)((sysctl_clk->vad_sclk_cfg >> 12) & 0x3F)/(double)((sysctl_clk->vad_sclk_cfg >> 0) & 0xFFF);

        /*---------------------------timer0-5 system clock----------------------------------------*/
        case SYSCTL_CLK_TIMER0_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg0 >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_TIMER1_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg0 >> 6) & 0x3F) + 1);
        case SYSCTL_CLK_TIMER2_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg0 >> 12) & 0x3F) + 1);
        case SYSCTL_CLK_TIMER3_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg0 >> 18) & 0x3F) + 1);
        case SYSCTL_CLK_TIMER4_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg1 >> 0) & 0x3F) + 1);
        case SYSCTL_CLK_TIMER5_TCLK:
            return 1.0 / (double)(((sysctl_clk->timer_tclk_cfg1 >> 6) & 0x3F) + 1);

        /*------------------------------------usb clock-------------------------------------------*/
        case SYSCTL_CLK_USB_PHY_CORE:
            return 1;
        case SYSCTL_CLK_USB_WAKEUP:
            return 1;

        default:
            return 1;
    }
}

/* Set the clock phase. At present, it is only 0 degree (no inversion) or 180 degree (inversion) */
bool sysctl_clk_set_phase(sysctl_clk_node_e leaf, uint32_t degree)
{
    switch(leaf)
    {
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            if(0 == degree)
            {
                sysctl_clk->audif_sclk_cfg1 = ((0 << 21) | (1 << 26));
                return true;
            }
            else if(180 == degree)
            {
                sysctl_clk->audif_sclk_cfg1 = ((1 << 21) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            if(0 == degree)
            {
                sysctl_clk->audif_devclk_cfg = ((0 << 21) | (1 << 26));
                return true;
            }
            else if(180 == degree)
            {
                sysctl_clk->audif_devclk_cfg = ((1 << 21) | (1 << 26));
                return true;
            }
            else
            {
                return false;
            }
        }
        case SYSCTL_CLK_VAD_TCLK:
        {
            if(0 == degree)
            {
                sysctl_clk->vad_sclk_cfg = ((0 << 20) | (1 << 27));
                return true;
            }
            else if(180 == degree)
            {
                sysctl_clk->vad_sclk_cfg = ((1 << 20) | (1 << 27));
                return true;
            }
            else
            {
                return false;
            }
        }
        default:
            return false;
    }
}


uint32_t sysctl_clk_get_phase(sysctl_clk_node_e leaf)
{
    switch(leaf)
    {
        case SYSCTL_CLK_AUDIO_OUT_SERIAL:
        {
            if(0 == ((sysctl_clk->audif_sclk_cfg1 >> 21) & 0x1))
            {
                return 0;
            }
            else
            {
                return 180;
            }
        }
        case SYSCTL_CLK_AUDIO_IN_SERIAL:
        {
            if(0 == ((sysctl_clk->audif_devclk_cfg >> 21) & 0x1))
            {
                return 0;
            }
            else
            {
                return 180;
            }
        }
        case SYSCTL_CLK_VAD_TCLK:
        {
            if(0 == ((sysctl_clk->vad_sclk_cfg >> 20) & 0x1))
            {
                return 0;
            }
            else
            {
                return 180;
            }
        }
        default:
            return 0;       /* other clocks cannot set phase */
    }
}

uint32_t sysctl_clk_get_leaf_freq(sysctl_clk_node_e leaf)
{
    double div = 1.0;
    sysctl_clk_node_e node;

    node = leaf;

    /* calc leaf chain div */
    while(node > SYSCTL_CLK_ROOT_MAX)
    {
        div *= sysctl_clk_get_leaf_div(node);
        node = sysctl_clk_get_leaf_parent(node);
    }

    /* get root freq and calc leaf freq */
    return (uint32_t)(sysctl_boot_get_root_clk_freq(node) * div);
}

/* Find the approximate div and mul */
int sysctl_clk_find_approximate(uint32_t mul_min, 
                                     uint32_t mul_max, 
                                     uint32_t div_min, 
                                     uint32_t div_max, 
                                     sysctl_clk_mul_div_methord_e method,
                                     unsigned long rate, 
                                     unsigned long parent_rate,
                                     uint32_t *div, 
                                     uint32_t *mul)
{
    long abs_min;
    long abs_current;
    /* we used interger to instead of float */
    long perfect_divide;

    uint32_t a,b;
    int i = 0;
    int n = 0;
    unsigned long mul_ulong,div_ulong;

    switch(method) {

        case SYSCTL_CLK_MUL_CHANGEABLE: {
            perfect_divide = (long)((parent_rate*1000) / rate);
            abs_min = abs(perfect_divide - (long)(((long)div_max*1000)/(long)mul_min));

            for(i = mul_min + 1; i <= mul_max; i++) {
                abs_current = abs(perfect_divide - (long)((long)((long)div_max*1000)/(long)i));
                if(abs_min > abs_current ) {
                    abs_min = abs_current;
                    *mul = i;
                }
            }

            *div = div_min;
            break;
        } 
        /* only div can be changeable, 1/1,1/2,1/3...*/
        case SYSCTL_CLK_DIV_CHANGEABLE: {
            perfect_divide = (long)((parent_rate*1000) / rate);
            abs_min = abs(perfect_divide - (long)(((long)div_min*1000)/(long)mul_max));
            *div = div_min;

            for(i = div_min + 1; i <= div_max; i++) {
                abs_current = abs(perfect_divide - (long)((long)((long)i*1000)/(long)mul_max));
                if(abs_min > abs_current ) {
                    abs_min = abs_current;
                    *div = i;
                }
            }
            *mul = mul_min;
            break;
        }

        case SYSCTL_CLK_MUL_DIV_CHANGEABLE: {
            perfect_divide = parent_rate/rate;
            /*div/mul must > 4 */
            if((perfect_divide > (long)div_max/(long)mul_min) || (perfect_divide < 4)) {
                return -1;
            }

            /* calc greatest common divisor */
            a = rate;
            b = parent_rate;

            while(a != b) {
                if(a > b) {
                    a -= b;
                } else {
                    b -= a;
                }
            }

            *div = parent_rate/a;
            *mul = rate/b;

            /* calc mul 2^n */
            n = 0;
            i = 0;
            while(1) {
                if((mul_max >> i) > 0) {
                    n++;
                    i++;
                }
                else
                {
                    break;
                }
            }
            n++;

            div_ulong = (unsigned long)(*div) * (unsigned long)pow(2,n) / (unsigned long)(*mul);
            mul_ulong = (unsigned long)pow(2,n);

            while((div_ulong > div_max) || (mul_ulong > mul_max)) {
                div_ulong >>= 1;
                mul_ulong >>= 1;
            }

            *div = (uint32_t)div_ulong;
            *mul = (uint32_t)mul_ulong;

            if((*div < div_min) || (*mul < mul_min)) {
                return -2;
            }

            break;
        }

        default:{
            return -3;
        }
    }
    return 0;
}
