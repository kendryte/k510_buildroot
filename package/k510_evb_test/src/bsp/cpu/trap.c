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
#include "interrupt.h"
#include "k510.h"

#ifdef _SIMU
#include "atomic.h"
uint32_t g_trap_status[2];
#endif

const char *fault_str[16] =
{
    "misaligned fetch",
    "fault fetch",
    "illegal instruction",
    "breakpoint",
    "misaligned load",
    "fault load",
    "misaligned store",
    "fault store",
    "handle u ecall",
    "handle s ecall",
    "reserved",
    "handle m ecall"
    "Instruction page fault",
    "Load page fault",
    "Reserved",
    "Store page fault",
};

/* Support PowerBrake (Performance Throttling) feature */
#define SUPPORT_PFT_ARCH    1

extern void mext_interrupt(unsigned int irq_source);

__attribute__((weak)) void bwei_handler(void)
{
    clear_csr(NDS_MIE, MIP_MTIP);
}

__attribute__((weak)) void mtime_handler(void)
{
    clear_csr(NDS_MIE, MIP_MTIP);
}

__attribute__((weak)) void mswi_handler(unsigned int irq_source)
{
    clear_csr(NDS_MIE, MIP_MSIP);
}

__attribute__((weak)) void syscall_handler(long n, long a0, long a1, long a2, long a3)
{
    if(n != 57) /* Exit */
    {
        k510_logce("syscall #%ld (a0:0x%lx,a1:0x%lx, a2:0x%lx, a3:0x%lx)\n", n, a0, a1, a2, a3);
    }
}

__attribute__((weak)) long except_handler(long cause, long epc)
{
    /* Unhandled Trap */
    k510_loge("\n{ ");
    if(cause == CAUSE_STACK_OVERFLOW)
    {
        k510_loge("Stack overflow");
    }
    else if(cause == CAUSE_STACK_UNDERFLOW)
    {
        k510_loge("Stack underflow");
    }
    else if(cause >= 0 && cause < 16)
    {
        k510_loge("%s", fault_str[cause]);
    }
    else
    {
        k510_loge("Unhanled Trap");
    }
    k510_loge(" } :> mcause = 0x%x, mepc = 0x%x mtval = 0x%x\n", (unsigned int)cause, (unsigned int)epc, (unsigned int)read_csr(NDS_MTVAL));
    exit(1);
    return epc;
}

void trap_entry(void) __attribute__ ((interrupt ("machine") , aligned(4)));
void trap_entry(void)
{
#ifdef _SIMU
    uint64_t v_coreid = read_coreid();
    // atomic_add(&g_trap_status[v_coreid], 1);
    g_trap_status[v_coreid]++;
#endif
    long mcause = read_csr(NDS_MCAUSE);
    long mepc = read_csr(NDS_MEPC);
    long mstatus = read_csr(NDS_MSTATUS);
#if SUPPORT_PFT_ARCH
    long mxstatus = read_csr(NDS_MXSTATUS);
#endif
#ifdef __riscv_32e
    /* Syscall num is passed in t0 (x5) for RV32E. */
    register long which asm("x5"), x10 asm("x10"), x11 asm("x11"), x12 asm("x12"), x13 asm("x13");
#else
    register long which asm("x17"), x10 asm("x10"), x11 asm("x11"), x12 asm("x12"), x13 asm("x13");
#endif

    /* Do your trap handling */
    if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_EXT)) {
        /* Machine-level interrupt from PLIC */
        // mext_interrupt(__nds__plic_claim_interrupt());
        mext_interrupt(__canaan__plic_claim_interrupt());
    } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_TIMER)) {
        /* Machine timer interrupt */
        mtime_handler();
        } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_SOFT)) {
        /* Machine SWI interrupt */
        mswi_handler(__nds__plic_sw_claim_interrupt());
        /* Machine SWI is connected to PLIC_SW source 1 */
        // __nds__plic_sw_complete_interrupt(1);
    }
    else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_BWEI)) {
        bwei_handler();
    } else if (!(mcause & MCAUSE_INT) && (((mcause & MCAUSE_CAUSE) == TRAP_M_ECALL) | ((mcause & MCAUSE_CAUSE) == TRAP_U_ECALL))) {
        /* Machine Syscal call */
        syscall_handler(which, x10, x11, x12, x13);
        mepc += 4;
    } else {
        /* Unhandled Trap */
        mepc = except_handler(mcause, mepc);
    }

    /* Restore CSR */
    clear_csr(NDS_MSTATUS, MSTATUS_MIE);

    write_csr(NDS_MSTATUS, mstatus);
    write_csr(NDS_MEPC, mepc);
#if SUPPORT_PFT_ARCH
    write_csr(NDS_MXSTATUS, mxstatus);
#endif
#ifdef _SIMU
    // atomic_add(&g_trap_status[v_coreid], -1);
    g_trap_status[v_coreid]--;
#endif
}
