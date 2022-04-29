/*
 * Copyright (c) 2012-2019 Andes Technology Corporation
 * All rights reserved.
 *
 */
#include "core_v5.h"
#include "resume.h"

#define STKSHIFT 14
	.section .init

	.global reset_vector

reset_vector:
	/* Decide whether this is an NMI or cold reset */
#	csrr t0, mcause
#	bnez t0, nmi_handler

	.global _start
	.type _start,@function

_start:
#ifdef _RESUME
    csrr    t0, mhartid
	bnez	t0, 1f  /* Core0 */

    /* Add DDR resume code */

    li t0, RESUME_SP0_ADDR  /* Resume core0 sp */
    j 2f
1:  li t0, RESUME_SP1_ADDR  /* Resume core1 sp */
2:  lwu sp, 0(t0)
    li t0, RESUME_CODE_ADDR /* Resume code */
    lwu t0, 0(t0)
    jr t0                   /* Jump to resume */

#else
#ifdef _DSPONLY
	csrr t0, mmsc_cfg
	srli t0, t0, 12
	andi t0, t0, 1
	bnez t0, 2f
	li   t0, 0x80000000UL	/* DSP reset vector */
	li   t1, 0x97000108UL	/* DSP reset vector addr */
	sw   t0, 0(t1)
	li   t0, 0x97002014UL
	sw   zero, 0(t0)
1:  j    1b
2:
#endif

    li       t0, 4
# init_ras:
#     beqz t0, exit_init_ras
#     addi t0, t0, -1
#     jal     init_ras
# exit_init_ras:
    j 1f
.balign 8
    .global g_wake_up
g_wake_up:
      .dword 1
      .dword 0
1:
	/* Initialize global pointer */
	.option push
	.option norelax
	la gp, __global_pointer$
	.option pop

	/* Initialize stack pointer */
	/* get cpu id */
	la  tp, _stack
    csrr a0, mhartid

#if 0
	beqz a0, 1f
	jr zero
1:
#endif

    slli a0, a0, STKSHIFT
    sub sp, tp, a0

#ifdef __nds_execit
	/* Initialize EXEC.IT table */
	la t0, _ITB_BASE_
	csrw uitb, t0
#endif

#ifdef __riscv_flen
	/* Enable FPU */
	li t0, MSTATUS_FS
	csrrs t0, mstatus, t0

	/* Initialize FCSR */
	fscsr zero
#endif

	/* Initial machine trap-vector Base */
	# csrr t0, mmisc_ctl
	# andi t0, t0, 2
	csrr t0, mmsc_cfg
	srli t0, t0, 12
	andi t0, t0, 1
	bnez t0, 1f
	la t0, trap_entry
	j 2f
1:
	/* Enable vectored external PLIC interrupt */
	csrsi mmisc_ctl, 2
	la t0, __vectors
2:
	csrw mtvec, t0

	/* Do system low level setup. It must be a leaf function */
	call __platform_init

	/* System reset handler */
	call reset_handler

	/* Infinite loop, if returned accidently */
1:	j 1b

	.weak __platform_init
__platform_init:
	ret

	.weak nmi_handler
nmi_handler:
1:	j 1b

	.text

	.global default_irq_entry
	.align 2

default_irq_entry:
1:	j 1b

	.weak trap_handler
trap_handler:
1:	j 1b

	.macro INTERRUPT num
	.weak entry_irq\num
	.set entry_irq\num, default_irq_entry
	.long entry_irq\num
	.endm

	/* Vector table
	 * NOTE:
	 * The Vector Table base alignment requirement has to be :
	 * " 2^ceiling(log2(VECTOR_NUMINTRS)) x 4 " bytes
	 */
#define VECTOR_NUMINTRS         256
	.section .rodata

	.global __vectors
	.balign 1024

__vectors:
	/* Trap vector */
	.long trap_entry

	/* PLIC interrupt vector */
	.altmacro
	.set irqno, 1
	.rept VECTOR_NUMINTRS
	INTERRUPT %irqno
	.set irqno, irqno+1
	.endr
#endif