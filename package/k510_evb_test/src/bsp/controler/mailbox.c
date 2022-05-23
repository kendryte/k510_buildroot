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
#include "k510.h"
#include "mailbox.h"
#include "sleep.h"
#include "interrupt.h"

volatile mailbox_t* const mailbox = (volatile mailbox_t *)MAILBOX_BASE_ADDR;

// inline void mailbox_set_int_direction(maixbox_int_t int_type, mailbox_int_dir_t dir)
// {
//     writel(dir, (uintptr_t)(&mailbox->uart0_intr) + int_type * 4);
// }

inline uint32_t mailbox_get_state(mailbox_state_t state)
{
    return readl((uintptr_t)(&mailbox->usbc_otgstate) + state * 4);
}

inline void mailbox_set_usbc_phy_xcfg_range(mailbox_usb_phy_range_t range)
{
    mailbox->usbc_phy_xcfg_range = readl(&range);
}

inline void mailbox_set_other_ctrl(mailbox_other_ctrl_t ctrl, uint32_t val)
{
    if(ctrl < MAILBOX_DDR_WCOBUF_CTL)
    {
        writel(val, (uintptr_t)(&mailbox->emmc_boot_ctrl_00) + ctrl * 4);
    }
    else
    {
        writel(val, (uintptr_t)(&mailbox->ddr_wcobuf_ctl) + (ctrl - 100) * 4);
    }
}

inline uint32_t mailbox_get_other_ctrl(mailbox_other_ctrl_t ctrl)
{
    if(ctrl < MAILBOX_DDR_WCOBUF_CTL)
    {
        return readl((uintptr_t)(&mailbox->emmc_boot_ctrl_00) + ctrl * 4);
    }
    else
    {
        return readl((uintptr_t)(&mailbox->ddr_wcobuf_ctl) + (ctrl - 100) * 4);
    }
}

inline int mailbox_lock(mailbox_lock_number_t lock_num, uint32_t wait_us)
{
    int ret = 0;
    uintptr_t lock_reg = (uintptr_t)(&mailbox->mailbox_lock0) + 4 * lock_num;
    if(wait_us)
    {
        while(--wait_us)
        {
            if(readl(lock_reg))
                usleep(1);
            else
                break;
        }

        if(wait_us == 0)
            ret = -1;
    }
    else
    {
        while(readl(lock_reg));
    }

    return ret;
}

inline void mailbox_unlock(mailbox_lock_number_t lock_num)
{
    writel(0, ((uintptr_t)(&mailbox->mailbox_lock0) + 4 * lock_num));
}

static plic_instance_t mailbox_instance[MAILBOX_INT_NUMBERMAX];



static int mailbox_irq_callback(void *ctx)
{
    if(is_dsp_type())
    {
        for(uint32_t i = 0; i < MAILBOX_INT_NUMBERMAX; i++)
        {
            if(mailbox_cpu2dsp_get_int_status(i) > 0)
            {
                mailbox_cpu2dsp_clear_int(i);
                if(mailbox_instance[i].callback)
                {
                    mailbox_instance[i].callback(mailbox_instance[i].ctx);
                }
            }
        }
    }
    else
    {
        for(uint32_t i = 0; i < MAILBOX_INT_NUMBERMAX; i++)
        {
            if(mailbox_dsp2cpu_get_int_status(i) > 0)
            {
                mailbox_dsp2cpu_clear_int(i);
                if(mailbox_instance[i].callback)
                {
                    mailbox_instance[i].callback(mailbox_instance[i].ctx);
                }
            }
        }
    }
    return 0;
}

void mailbox_register_irq(mailbox_int_number_t int_num, plic_irq_callback_t cb, void *ctx, uint32_t priority)
{
    uint32_t irq_num = is_dsp_type() ? IRQN_CPU2DSP_INTERRUPT : IRQN_DSP2CPU_INTERRUPT;

    mailbox_instance[int_num].callback = cb;
    mailbox_instance[int_num].ctx = ctx;

    plic_set_priority(irq_num, priority);
    plic_irq_register(irq_num, mailbox_irq_callback, NULL);
    plic_irq_enable(irq_num);
}
