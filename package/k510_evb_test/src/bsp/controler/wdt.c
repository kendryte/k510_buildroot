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
#include <k510.h>
#include "math.h"
#include "wdt.h"
#include <sysctl_clk.h>

volatile wdt_t *const wdt[3] =
    {
        (volatile wdt_t *)WDT0_BASE_ADDR,
        (volatile wdt_t *)WDT1_BASE_ADDR,
        (volatile wdt_t *)WDT2_BASE_ADDR,
    };

void wdt_enable(wdt_device_number_t id)
{
    wdt[id]->crr = WDT_CRR_MASK;
    wdt[id]->cr |= WDT_CR_ENABLE;
}

static void wdt_disable(wdt_device_number_t id)
{
    wdt[id]->crr = WDT_CRR_MASK;
    wdt[id]->cr &= (~WDT_CR_ENABLE);
}

void wdt_set_timeout(wdt_device_number_t id, uint8_t timeout)
{
    wdt[id]->torr = WDT_TORR_TOP(timeout);
}

void wdt_response_mode(wdt_device_number_t id, uint8_t mode)
{
    wdt[id]->cr &= (~WDT_CR_RMOD_MASK);
    wdt[id]->cr |= mode;
}

static uint64_t wdt_get_pclk(wdt_device_number_t id)
{
#ifdef _FPGA
    uint32_t clk_freq = BUSFREQ;
#else
    uint32_t clk_freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_WDT0_TCLK + id);
#endif

    return clk_freq;
}

static uint8_t wdt_get_top(wdt_device_number_t id, uint64_t timeout_ms)
{
    uint64_t wdt_clk = wdt_get_pclk(id);
    uint64_t ret = (timeout_ms * wdt_clk / 1000) >> 16;
    if(ret)
        ret = (uint32_t)log2(ret);
    if(ret > 0xf)
        ret = 0xf;
    return (uint8_t)ret;
}

void wdt_feed(wdt_device_number_t id)
{
    wdt[id]->crr = WDT_CRR_MASK;
}

void wdt_clear_interrupt(wdt_device_number_t id)
{
    wdt[id]->eoi = wdt[id]->eoi;
}

void wdt_start(wdt_device_number_t id, uint64_t time_out_ms, plic_irq_callback_t on_irq)
{
    // sysctl_reset(id ? SYSCTL_RESET_WDT1 : SYSCTL_RESET_WDT0);
    // sysctl_clock_set_threshold(id ? SYSCTL_THRESHOLD_WDT1 : SYSCTL_THRESHOLD_WDT0, 0);
    // sysctl_clock_enable(id ? SYSCTL_CLOCK_WDT1 : SYSCTL_CLOCK_WDT0);

    // plic_set_priority(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT, 1);
    // plic_irq_enable(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT);
    // plic_irq_register(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT, on_irq, NULL);

    wdt_response_mode(id, WDT_CR_RMOD_INTERRUPT);
    uint8_t m_top = wdt_get_top(id, time_out_ms);
    wdt_set_timeout(id, m_top);
    wdt_enable(id);
}

uint32_t wdt_init(wdt_device_number_t id, uint64_t time_out_ms, plic_irq_callback_t on_irq, void *ctx)
{
    // sysctl_reset(id ? SYSCTL_RESET_WDT1 : SYSCTL_RESET_WDT0);
    // sysctl_clock_set_threshold(id ? SYSCTL_THRESHOLD_WDT1 : SYSCTL_THRESHOLD_WDT0, 0);
    // sysctl_clock_enable(id ? SYSCTL_CLOCK_WDT1 : SYSCTL_CLOCK_WDT0);

    // plic_set_priority(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT, 1);
    // plic_irq_enable(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT);
    // plic_irq_register(id ? IRQN_WDT1_INTERRUPT : IRQN_WDT0_INTERRUPT, on_irq, ctx);

    wdt_response_mode(id, WDT_CR_RMOD_INTERRUPT);
    uint8_t m_top = wdt_get_top(id, time_out_ms);
    wdt_set_timeout(id, m_top);
    wdt_enable(id);
    return (1UL << (m_top + 16 + 1)) * 1000UL / wdt_get_pclk(id);
}

uint32_t wdt_configure(wdt_device_number_t id, uint64_t time_out_ms)
{
    wdt_response_mode(id, WDT_CR_RMOD_INTERRUPT);
    uint8_t m_top = wdt_get_top(id, time_out_ms);
    wdt_set_timeout(id, m_top);
    wdt_enable(id);
    return (1UL << (m_top + 16 + 1)) * 1000UL / wdt_get_pclk(id);
}

void wdt_stop(wdt_device_number_t id)
{
    wdt_disable(id);
}

uint32_t wdt_get_status(wdt_device_number_t id)
{
    return wdt[id]->stat;
}
