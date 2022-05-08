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
#include "k510.h"
#include "interrupt.h"
#include <stdbool.h>
#include <wdt.h>

#ifdef _SIMU
#include "atomic.h"
extern uint32_t g_trap_status[2];
#endif

static plic_instance_t plic_instance[PLIC_NUM_CORES][IRQN_MAX];

static plic_instance_t wdt_instance[WDT_NUMBER_MAX];

void wdt_irq_register(wdt_number_t wdt_number, plic_irq_callback_t callback, void *ctx)
{
    /* Set user callback function */
    wdt_instance[wdt_number].callback = callback;
    /* Assign user context */
    wdt_instance[wdt_number].ctx = ctx;
}

void wdt_irq_unregister(wdt_number_t wdt_number)
{
    /* Set user callback function */
    wdt_instance[wdt_number].callback = NULL;
    /* Assign user context */
    wdt_instance[wdt_number].ctx = NULL;
}

void nmi_entry(void) __attribute__ ((interrupt ("machine") , aligned(4)));
void nmi_entry(void)
{
    for(uint32_t i = 0; i < WDT_NUMBER_MAX; i++)
    {
        if(wdt_get_status(i))
            if(wdt_instance[i].callback)
                wdt_instance[i].callback(wdt_instance[i].ctx);
    }
}

// void plic_mb_irq_enable(plic_irq_t irq_number, uint32_t enable)
// {
//     bool cpu_type = !is_dsp_type();
//     switch(irq_number)
//     {
//         case IRQN_UART0_INTERRUPT:
//             mb_set_int_enable(UART0_INTR_ADDR, enable, cpu_type);
//             break;
//         case IRQN_UART1_INTERRUPT:
//             mb_set_int_enable(UART1_INTR_ADDR, enable, cpu_type);
//             break;
//         case IRQN_UART2_INTERRUPT:
//             mb_set_int_enable(UART2_INTR_ADDR, enable, cpu_type);
//             break;
//         /* TODO */
//         default:
//             break;
//     }
// }

void plic_init(void)
{
    int i = 0;

    /* Get current core id */
    unsigned long core_id = read_coreid();

    for(i = 0; i < IRQN_MAX; i++)
    {
        /* Disable all interrupts for the current core. */
        // __nds__plic_disable_interrupt(i);
        __canaan__plic_disable_interrupt(i);

         /* Set priorities to zero. */
        __nds__plic_set_priority(i, 0);

        /* Clear PLIC instance for every cores */
        for(i = 0; i < IRQN_MAX; i++)
        {
            /* clang-format off */
            plic_instance[core_id][i] = (const plic_instance_t){
                .callback = NULL,
                .ctx      = NULL,
            };
            /* clang-format on */
        }
        /*
        * A successful claim will also atomically clear the corresponding
        * pending bit on the interrupt source. A target can perform a claim
        * at any time, even if the EIP is not set.
        */
        // __nds__plic_complete_interrupt(i);
        __canaan__plic_complete_interrupt(i);
    }

    /* Set the threshold to zero. */
    // __nds__plic_set_threshold(0);
    __canaan__plic_set_threshold(0);
}

int plic_irq_enable(plic_irq_t irq_number)
{
    /* Check parameters */
    if (PLIC_NUM_SOURCES < irq_number || 0 > irq_number)
        return -1;
    // __nds__plic_enable_interrupt(irq_number);
    __canaan__plic_enable_interrupt(irq_number);
    return 0;
}

int plic_irq_disable(plic_irq_t irq_number)
{
    /* Check parameters */
    if (PLIC_NUM_SOURCES < irq_number || 0 > irq_number)
        return -1;
    // __nds__plic_disable_interrupt(irq_number);
    __canaan__plic_disable_interrupt(irq_number);
    return 0;
}

int plic_set_priority(plic_irq_t irq_number, uint32_t priority)
{
    /* Check parameters */
    if (PLIC_NUM_SOURCES < irq_number || 0 > irq_number)
        return -1;
    /* Set interrupt priority by IRQ number */
    __nds__plic_set_priority(irq_number, priority);
    return 0;
}

void plic_irq_register(plic_irq_t irq, plic_irq_callback_t callback, void *ctx)
{
    /* Read core id */
    unsigned long core_id = read_coreid();
    /* Set user callback function */
    plic_instance[core_id][irq].callback = callback;
    /* Assign user context */
    plic_instance[core_id][irq].ctx = ctx;
}

void plic_irq_unregister(plic_irq_t irq)
{
    /* Just assign NULL to user callback function and context */
    plic_irq_register(irq, NULL, NULL);
}

__attribute__((weak)) void mext_interrupt(unsigned int irq_source)
{
    /* Enable interrupts in general to allow nested */
    // set_csr(NDS_MSTATUS, MSTATUS_MIE);
    /* Get current core id */
    uint64_t core_id = read_coreid();
    /* Do interrupt handler */
    if (plic_instance[core_id][irq_source].callback)
            plic_instance[core_id][irq_source].callback(plic_instance[core_id][irq_source].ctx);

    // __nds__plic_complete_interrupt(irq_source);
    __canaan__plic_complete_interrupt(irq_source);
}

void plic_interrupt_enable(void)
{
    /* Enable the Machine External interrupt bit in MIE. */
    set_csr(NDS_MIE, MIP_MEIP);
    /* Enable interrupts in general. */
    set_csr(NDS_MSTATUS, MSTATUS_MIE);
}

void plic_interrupt_disable(void)
{
    clear_csr(NDS_MIE, MIP_MEIP);
}

void interrupt_enable(void)
{
    /* Enable the Machine Timer/Sofware interrupt bit in MIE. */
    set_csr(NDS_MIE, MIP_MTIP | MIP_MSIP | MIP_MEIP);

    /* Enable interrupts in general. */
    set_csr(NDS_MSTATUS, MSTATUS_MIE);
}

void interrupt_disable(void)
{
    /* Disable interrupts in general. */
    clear_csr(NDS_MSTATUS, MSTATUS_MIE);
    /* Disable the Machine external, timer and software interrupts until setup is done */
    clear_csr(NDS_MIE, MIP_MEIP | MIP_MTIP | MIP_MSIP);
}

#ifdef _SIMU
#define VECTOR_ADD_TRAP_STATUS()    uint64_t v_coreid = read_coreid(); \
                                    g_trap_status[v_coreid]++;
                                    /* atomic_add(&g_trap_status[v_coreid], 1); */
#define VECTOR_SUB_TRAP_STATUS()    /* atomic_add(&g_trap_status[v_coreid], -1); */ g_trap_status[v_coreid]--;
#else
#define VECTOR_ADD_TRAP_STATUS()
#define VECTOR_SUB_TRAP_STATUS()
#endif

#define VECTOR_INTERRUPT_FUNCTION(num)  void __attribute__ ((interrupt)) entry_irq##num(void)                   \
                                        {                                                                       \
                                            VECTOR_ADD_TRAP_STATUS()                                            \
                                            NESTED_IRQ_ENTER();                                                 \
                                            if (plic_instance[0][num].callback)                                 \
                                                    plic_instance[0][num].callback(plic_instance[0][num].ctx);  \
                                            /*__nds__plic_complete_interrupt(num);*/                                \
                                            __canaan__plic_complete_interrupt(num);                             \
                                            NESTED_IRQ_EXIT();                                                  \
                                            VECTOR_SUB_TRAP_STATUS()                                            \
                                        }

VECTOR_INTERRUPT_FUNCTION(1)
VECTOR_INTERRUPT_FUNCTION(2)
VECTOR_INTERRUPT_FUNCTION(3)
VECTOR_INTERRUPT_FUNCTION(4)
VECTOR_INTERRUPT_FUNCTION(5)
VECTOR_INTERRUPT_FUNCTION(6)
VECTOR_INTERRUPT_FUNCTION(7)
VECTOR_INTERRUPT_FUNCTION(8)
VECTOR_INTERRUPT_FUNCTION(9)
VECTOR_INTERRUPT_FUNCTION(10)
VECTOR_INTERRUPT_FUNCTION(11)
VECTOR_INTERRUPT_FUNCTION(12)
VECTOR_INTERRUPT_FUNCTION(13)
VECTOR_INTERRUPT_FUNCTION(14)
VECTOR_INTERRUPT_FUNCTION(15)
VECTOR_INTERRUPT_FUNCTION(16)
VECTOR_INTERRUPT_FUNCTION(17)
VECTOR_INTERRUPT_FUNCTION(18)
VECTOR_INTERRUPT_FUNCTION(19)
VECTOR_INTERRUPT_FUNCTION(20)
VECTOR_INTERRUPT_FUNCTION(21)
VECTOR_INTERRUPT_FUNCTION(22)
VECTOR_INTERRUPT_FUNCTION(23)
VECTOR_INTERRUPT_FUNCTION(24)
VECTOR_INTERRUPT_FUNCTION(25)
VECTOR_INTERRUPT_FUNCTION(26)
VECTOR_INTERRUPT_FUNCTION(27)
VECTOR_INTERRUPT_FUNCTION(28)
VECTOR_INTERRUPT_FUNCTION(29)
VECTOR_INTERRUPT_FUNCTION(30)
VECTOR_INTERRUPT_FUNCTION(31)
VECTOR_INTERRUPT_FUNCTION(32)
VECTOR_INTERRUPT_FUNCTION(33)
VECTOR_INTERRUPT_FUNCTION(34)
VECTOR_INTERRUPT_FUNCTION(35)
VECTOR_INTERRUPT_FUNCTION(36)
VECTOR_INTERRUPT_FUNCTION(37)
VECTOR_INTERRUPT_FUNCTION(38)
VECTOR_INTERRUPT_FUNCTION(39)
VECTOR_INTERRUPT_FUNCTION(40)
VECTOR_INTERRUPT_FUNCTION(41)
VECTOR_INTERRUPT_FUNCTION(42)
VECTOR_INTERRUPT_FUNCTION(43)
VECTOR_INTERRUPT_FUNCTION(44)
VECTOR_INTERRUPT_FUNCTION(45)
VECTOR_INTERRUPT_FUNCTION(46)
VECTOR_INTERRUPT_FUNCTION(47)
VECTOR_INTERRUPT_FUNCTION(48)
VECTOR_INTERRUPT_FUNCTION(49)
VECTOR_INTERRUPT_FUNCTION(50)
VECTOR_INTERRUPT_FUNCTION(51)
VECTOR_INTERRUPT_FUNCTION(52)
VECTOR_INTERRUPT_FUNCTION(53)
VECTOR_INTERRUPT_FUNCTION(54)
VECTOR_INTERRUPT_FUNCTION(55)
VECTOR_INTERRUPT_FUNCTION(56)
VECTOR_INTERRUPT_FUNCTION(57)
VECTOR_INTERRUPT_FUNCTION(58)
VECTOR_INTERRUPT_FUNCTION(59)
VECTOR_INTERRUPT_FUNCTION(60)
VECTOR_INTERRUPT_FUNCTION(61)
VECTOR_INTERRUPT_FUNCTION(62)
VECTOR_INTERRUPT_FUNCTION(63)
VECTOR_INTERRUPT_FUNCTION(64)
VECTOR_INTERRUPT_FUNCTION(65)
VECTOR_INTERRUPT_FUNCTION(66)
VECTOR_INTERRUPT_FUNCTION(67)
VECTOR_INTERRUPT_FUNCTION(68)
VECTOR_INTERRUPT_FUNCTION(69)
VECTOR_INTERRUPT_FUNCTION(70)
VECTOR_INTERRUPT_FUNCTION(71)
VECTOR_INTERRUPT_FUNCTION(72)
VECTOR_INTERRUPT_FUNCTION(73)
VECTOR_INTERRUPT_FUNCTION(74)
VECTOR_INTERRUPT_FUNCTION(75)
VECTOR_INTERRUPT_FUNCTION(76)
VECTOR_INTERRUPT_FUNCTION(77)
VECTOR_INTERRUPT_FUNCTION(78)
VECTOR_INTERRUPT_FUNCTION(79)
VECTOR_INTERRUPT_FUNCTION(80)
VECTOR_INTERRUPT_FUNCTION(81)
VECTOR_INTERRUPT_FUNCTION(82)
VECTOR_INTERRUPT_FUNCTION(83)
VECTOR_INTERRUPT_FUNCTION(84)
VECTOR_INTERRUPT_FUNCTION(85)
VECTOR_INTERRUPT_FUNCTION(86)
VECTOR_INTERRUPT_FUNCTION(87)
VECTOR_INTERRUPT_FUNCTION(88)
VECTOR_INTERRUPT_FUNCTION(89)
VECTOR_INTERRUPT_FUNCTION(90)
VECTOR_INTERRUPT_FUNCTION(91)
VECTOR_INTERRUPT_FUNCTION(92)
VECTOR_INTERRUPT_FUNCTION(93)
VECTOR_INTERRUPT_FUNCTION(94)
VECTOR_INTERRUPT_FUNCTION(95)
VECTOR_INTERRUPT_FUNCTION(96)
VECTOR_INTERRUPT_FUNCTION(97)
VECTOR_INTERRUPT_FUNCTION(98)
VECTOR_INTERRUPT_FUNCTION(99)
VECTOR_INTERRUPT_FUNCTION(100)
VECTOR_INTERRUPT_FUNCTION(101)
VECTOR_INTERRUPT_FUNCTION(102)
VECTOR_INTERRUPT_FUNCTION(103)
VECTOR_INTERRUPT_FUNCTION(104)
VECTOR_INTERRUPT_FUNCTION(105)
VECTOR_INTERRUPT_FUNCTION(106)
VECTOR_INTERRUPT_FUNCTION(107)
VECTOR_INTERRUPT_FUNCTION(108)
VECTOR_INTERRUPT_FUNCTION(109)
VECTOR_INTERRUPT_FUNCTION(110)
VECTOR_INTERRUPT_FUNCTION(111)
VECTOR_INTERRUPT_FUNCTION(112)
VECTOR_INTERRUPT_FUNCTION(113)
VECTOR_INTERRUPT_FUNCTION(114)
VECTOR_INTERRUPT_FUNCTION(115)
VECTOR_INTERRUPT_FUNCTION(116)
VECTOR_INTERRUPT_FUNCTION(117)
VECTOR_INTERRUPT_FUNCTION(118)
VECTOR_INTERRUPT_FUNCTION(119)
VECTOR_INTERRUPT_FUNCTION(120)
VECTOR_INTERRUPT_FUNCTION(121)
VECTOR_INTERRUPT_FUNCTION(122)
VECTOR_INTERRUPT_FUNCTION(123)
VECTOR_INTERRUPT_FUNCTION(124)
VECTOR_INTERRUPT_FUNCTION(125)
VECTOR_INTERRUPT_FUNCTION(126)
VECTOR_INTERRUPT_FUNCTION(127)
VECTOR_INTERRUPT_FUNCTION(128)
