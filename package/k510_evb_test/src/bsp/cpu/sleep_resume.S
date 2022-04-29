#include "core_v5.h"
#include "resume.h"

//# define SLL32    sllw
//# define STORE    sd
//# define LOAD     ld
# define LFREG flw
# define SFREG fsw
//# define LWU      lwu
//# define LOG_REGBYTES 3

#define REGBYTES (1 << LOG_REGBYTES)
#define PUSH(which) addi sp, sp, -REGBYTES; STORE which, 0(sp)
#define PUSH_FGPR(which) addi sp, sp, -REGBYTES; SFREG which, 0(sp)
#define PUSH_CSR(csr) addi sp, sp, -REGBYTES; csrr t0, csr; STORE t0, 0(sp)
#define POP(which)  LOAD which, 0(sp); addi sp, sp, REGBYTES
#define POP_FGPR(which) LFREG which, 0(sp); addi sp, sp, REGBYTES
#define POP_CSR(csr)  LOAD t0, 0(sp); addi sp, sp, REGBYTES; csrw csr, t0

.text
.global cpu_suspend2ram
.global cpu_resume

cpu_suspend2ram:
    # backup cpu register
    # store x1 ~ x31 to stack
    PUSH(x1)
    PUSH(x2)
    PUSH(x3)
    PUSH(x4)
    PUSH(x5)
    PUSH(x6)
    PUSH(x7)
    PUSH(x8)
    PUSH(x9)
    PUSH(x10)
    PUSH(x11)
    PUSH(x12)
    PUSH(x13)
    PUSH(x14)
    PUSH(x15)
    PUSH(x16)
    PUSH(x17)
    PUSH(x18)
    PUSH(x19)
    PUSH(x20)
    PUSH(x21)
    PUSH(x22)
    PUSH(x23)
    PUSH(x24)
    PUSH(x25)
    PUSH(x26)
    PUSH(x27)
    PUSH(x28)
    PUSH(x29)
    PUSH(x30)
    PUSH(x31)

    #Store f1 - f31 to back
    PUSH_FGPR(f0)
    PUSH_FGPR(f1)
    PUSH_FGPR(f2)
    PUSH_FGPR(f3)
    PUSH_FGPR(f4)
    PUSH_FGPR(f5)
    PUSH_FGPR(f6)
    PUSH_FGPR(f7)
    PUSH_FGPR(f8)
    PUSH_FGPR(f9)
    PUSH_FGPR(f10)
    PUSH_FGPR(f11)
    PUSH_FGPR(f12)
    PUSH_FGPR(f13)
    PUSH_FGPR(f14)
    PUSH_FGPR(f15)
    PUSH_FGPR(f16)
    PUSH_FGPR(f17)
    PUSH_FGPR(f18)
    PUSH_FGPR(f19)
    PUSH_FGPR(f20)
    PUSH_FGPR(f21)
    PUSH_FGPR(f22)
    PUSH_FGPR(f23)
    PUSH_FGPR(f24)
    PUSH_FGPR(f25)
    PUSH_FGPR(f26)
    PUSH_FGPR(f27)
    PUSH_FGPR(f28)
    PUSH_FGPR(f29)
    PUSH_FGPR(f30)
    PUSH_FGPR(f31)

    # Push RISC-V m-mode reg
    PUSH_CSR(mstatus)
    PUSH_CSR(misa)
    PUSH_CSR(medeleg)
    PUSH_CSR(mideleg)
    PUSH_CSR(mie)
    PUSH_CSR(mtvec)
    PUSH_CSR(mscratch)
    PUSH_CSR(mepc)
    PUSH_CSR(mcause)
    PUSH_CSR(mtval)
    PUSH_CSR(mip)
    PUSH_CSR(mcounteren)
    PUSH_CSR(mcountinhibit)

    # Push Andes m-mode reg
    #PUSH_CSR(milmb)
    #PUSH_CSR(mdlmb)
    #PUSH_CSR(mecc_code)
    #PUSH_CSR(mnvec)
    PUSH_CSR(mcache_ctl)
    PUSH_CSR(mcctlbeginaddr)
    PUSH_CSR(mcctlcommand)
    PUSH_CSR(mcctldata)
    #PUSH_CSR(mppib)
    #PUSH_CSR(mfiob)
    PUSH_CSR(mhsp_ctl)
    PUSH_CSR(msp_bound)
    PUSH_CSR(msp_base)
    PUSH_CSR(mxstatus)
    PUSH_CSR(mdcause)
    PUSH_CSR(mslideleg)
    #PUSH_CSR(msavestatus)
    #PUSH_CSR(msaveepc1)
    #PUSH_CSR(msavecause1)
    #PUSH_CSR(msaveepc2)
    #PUSH_CSR(msavecause2)
    #PUSH_CSR(msavedcause1)
    #PUSH_CSR(msavedcause2)
    PUSH_CSR(mpft_ctl)
    PUSH_CSR(mmisc_ctl)
    PUSH_CSR(mcounterwen)
    PUSH_CSR(mcounterinten)
    PUSH_CSR(mcountermask_m)
    PUSH_CSR(mcountermask_s)
    PUSH_CSR(mcountermask_u)
    PUSH_CSR(mcounterovf)
    #PUSH_CSR(mirq_entry)
    #PUSH_CSR(mintsel_jal)
    #PUSH_CSR(pushmcause)
    #PUSH_CSR(pushmepc)
    #PUSH_CSR(pushmxstatus)
##if __riscv_xlen == 64
#	PUSH_CSR(pmacfg0)
#	PUSH_CSR(pmacfg2)
##else
#	PUSH_CSR(pmacfg0)
#	PUSH_CSR(pmacfg1)
#	PUSH_CSR(pmacfg2)
#	PUSH_CSR(pmacfg3)
##endif
#	PUSH_CSR(pmaaddr0)
#	PUSH_CSR(pmaaddr1)
#	PUSH_CSR(pmaaddr2)
#	PUSH_CSR(pmaaddr3)
#	PUSH_CSR(pmaaddr4)
#	PUSH_CSR(pmaaddr5)
#	PUSH_CSR(pmaaddr6)
#	PUSH_CSR(pmaaddr7)
#	PUSH_CSR(pmaaddr8)
#	PUSH_CSR(pmaaddr9)
#	PUSH_CSR(pmaaddr10)
#	PUSH_CSR(pmaaddr11)
#	PUSH_CSR(pmaaddr12)
#	PUSH_CSR(pmaaddr13)
#	PUSH_CSR(pmaaddr14)
#	PUSH_CSR(pmaaddr15)

    # Push RISC-V s-mode reg
    PUSH_CSR(sstatus)
    #PUSH_CSR(sedeleg)
    #PUSH_CSR(sideleg)
    PUSH_CSR(sie)
    PUSH_CSR(stvec)
    PUSH_CSR(scounteren)
    PUSH_CSR(sscratch)
    PUSH_CSR(sepc)
    PUSH_CSR(scause)
    PUSH_CSR(stval)
    PUSH_CSR(sip)
    PUSH_CSR(satp)

    # Push Andes s-mode reg
    PUSH_CSR(slie)
    PUSH_CSR(slip)
    PUSH_CSR(sdcause)
    PUSH_CSR(scounterinten)
    PUSH_CSR(scountermask_m)
    PUSH_CSR(scountermask_s)
    PUSH_CSR(scountermask_u)
    PUSH_CSR(scounterovf)
    PUSH_CSR(scountinhibit)
    PUSH_CSR(scctldata)
    #PUSH_CSR(smisc_ctl)

    # Push pmp
//# if __riscv_xlen == 64
    PUSH_CSR(pmpcfg0)
    PUSH_CSR(pmpcfg2)
# #else
# 	PUSH_CSR(pmpcfg0)
# 	PUSH_CSR(pmpcfg1)
# 	PUSH_CSR(pmpcfg2)
# 	PUSH_CSR(pmpcfg3)
# #endif
    PUSH_CSR(pmpaddr0)
    PUSH_CSR(pmpaddr1)
    PUSH_CSR(pmpaddr2)
    PUSH_CSR(pmpaddr3)
    PUSH_CSR(pmpaddr4)
    PUSH_CSR(pmpaddr5)
    PUSH_CSR(pmpaddr6)
    PUSH_CSR(pmpaddr7)
    PUSH_CSR(pmpaddr8)
    PUSH_CSR(pmpaddr9)
    PUSH_CSR(pmpaddr10)
    PUSH_CSR(pmpaddr11)
    PUSH_CSR(pmpaddr12)
    PUSH_CSR(pmpaddr13)
    PUSH_CSR(pmpaddr14)
    PUSH_CSR(pmpaddr15)

    # store sp to sram0
    csrr t0, mhartid
    bnez t0, 1f			/* Core1 branch*/

    /* store cpu_resume point to sram0 */
    la t0, cpu_resume
    li t1, RESUME_CODE_ADDR
    sw t0, 0(t1)

    /* store core 0 reset vector  */
    li t1, AX25MP0_RESET_VECTOR
    /* store core0 sp */
    li t0, RESUME_SP0_ADDR
    j 2f
1:
    /* store core 1 reset vector  */
    li t1, AX25MP1_RESET_VECTOR
    /* store core1 sp */
    li t0, RESUME_SP1_ADDR
2:
    li t2, RESUME_BASE_ADDR		/* Cpu resume boot addr -> t2 */
    sw sp, 0(t0)
    sw t2, 0(t1)

    # li	t0, 0x20
    # li	t1, 3
    # csrr	t2, mhartid
    # add	t1, t1, t2
    # mul	t0, t0, t1
    # addi	t0, t0,	0x84
    # li	t1, SMU_BASE
    # add	t0, t0,	t1
    # sw	sp, 0(t0)

    # store reset vector
    # li	t0, 0x4
    # csrr	t1, mhartid
    # mul	t0, t0, t1
    # addi	t0, t0, 0x50
    # li	t1, SMU_BASE
    # add	t0, t0, t1
    # la	t1, cpu_resume
    # sw	t1, 0(t0)

    # flush dcache
    csrw	ucctlcommand, 0x6

    # disable d-cache
    csrrc	t0, mcache_ctl, 0x2

    # check if l2 exist
//    la	t0, has_l2
//    lw	t1, 0(t0)
//    li	t0, 1
//#	li	t0, 0xe0500000
//#	lw	t1, 0(t0)
//#	li	t0, -1
//    bne	t0, t1, no_l2

    # check if it is core 0
    csrr	t1, mhartid
    bnez	t1, no_l2

    # flush and disable l2 by core 0
    li	t0, 0x9E900000
    li	t2, 0x10
    mul	t1, t1, t2
    add	t1, t1, 0x40
    add	t0, t0, t1
    li	t1, 0x12
    sd	t1, 0(t0)

poll_l2_idle:
    # Polling L2 idle status for core0
    li	t0, 0x9E900080
    ld	t1, 0(t0)
    andi	t1, t1, 0xf
    bnez	t1, poll_l2_idle

    # disable L2
    li	t0, 0x9E900008
    ld	t1, 0(t0)
    srli	t1, t1, 1
    slli	t1, t1, 1
    sw	t1, 0(t0)
no_l2:
    wfi

test_sec:
    j test_sec

.align 2
cpu_resume:
    # Check if it come from NMI, go resume if not.
    csrr	t0, mcause
    beqz	t0, go_resume
cpu_hang:
    j	cpu_hang
go_resume:
    # load sp
    # li	t0, 0x20
    # li	t1, 3
    # csrr	t2, mhartid
    # add	t1, t1, t2
    # mul	t0, t0, t1
    # addi	t0, t0, 0x84
    # li	t1, SMU_BASE
    # add	t0, t0, t1
    # lw	sp, 0(t0)

    # resume cpu regisger
    # Pop pmp
    POP_CSR(pmpaddr15)
    POP_CSR(pmpaddr14)
    POP_CSR(pmpaddr13)
    POP_CSR(pmpaddr12)
    POP_CSR(pmpaddr11)
    POP_CSR(pmpaddr10)
    POP_CSR(pmpaddr9)
    POP_CSR(pmpaddr8)
    POP_CSR(pmpaddr7)
    POP_CSR(pmpaddr6)
    POP_CSR(pmpaddr5)
    POP_CSR(pmpaddr4)
    POP_CSR(pmpaddr3)
    POP_CSR(pmpaddr2)
    POP_CSR(pmpaddr1)
    POP_CSR(pmpaddr0)
## if __riscv_xlen == 64
    POP_CSR(pmpcfg2)
    POP_CSR(pmpcfg0)
# #else
#     POP_CSR(pmpcfg3)
#     POP_CSR(pmpcfg2)
#     POP_CSR(pmpcfg1)
#     POP_CSR(pmpcfg0)
# #endif
    # Pop Andes s-mode reg
    #POP_CSR(smisc_ctl)
    POP_CSR(scctldata)
    POP_CSR(scountinhibit)
    POP_CSR(scounterovf)
    POP_CSR(scountermask_u)
    POP_CSR(scountermask_s)
    POP_CSR(scountermask_m)
    POP_CSR(scounterinten)
    POP_CSR(sdcause)
    POP_CSR(slip)
    POP_CSR(slie)

    # Pop RISC-V s-mode reg
    POP_CSR(satp)
    POP_CSR(sip)
    POP_CSR(stval)
    POP_CSR(scause)
    POP_CSR(sepc)
    POP_CSR(sscratch)
    POP_CSR(scounteren)
    POP_CSR(stvec)
    POP_CSR(sie)
    #POP_CSR(sideleg)
    #POP_CSR(sedeleg)
    POP_CSR(sstatus)

    # Pop Andes m-mode reg
#	POP_CSR(pmaaddr15)
#	POP_CSR(pmaaddr14)
#	POP_CSR(pmaaddr13)
#	POP_CSR(pmaaddr12)
#	POP_CSR(pmaaddr11)
#	POP_CSR(pmaaddr10)
#	POP_CSR(pmaaddr9)
#	POP_CSR(pmaaddr8)
#	POP_CSR(pmaaddr7)
#	POP_CSR(pmaaddr6)
#	POP_CSR(pmaaddr5)
#	POP_CSR(pmaaddr4)
#	POP_CSR(pmaaddr3)
#	POP_CSR(pmaaddr2)
#	POP_CSR(pmaaddr1)
#	POP_CSR(pmaaddr0)
##if __riscv_xlen == 64
#	POP_CSR(pmacfg2)
#	POP_CSR(pmacfg0)
##else
#	POP_CSR(pmacfg3)
#	POP_CSR(pmacfg2)
#	POP_CSR(pmacfg1)
#	POP_CSR(pmacfg0)
##endif
    #POP_CSR(pushmxstatus)
    #POP_CSR(pushmepc)
    #POP_CSR(pushmcause)
    #POP_CSR(mintsel_jal)
    #POP_CSR(mirq_entry)
    POP_CSR(mcounterovf)
    POP_CSR(mcountermask_u)
    POP_CSR(mcountermask_s)
    POP_CSR(mcountermask_m)
    POP_CSR(mcounterinten)
    POP_CSR(mcounterwen)
    POP_CSR(mmisc_ctl)
    POP_CSR(mpft_ctl)
    #POP_CSR(msavedcause2)
    #POP_CSR(msavedcause1)
    #POP_CSR(msavecause2)
    #POP_CSR(msaveepc2)
    #POP_CSR(msavecause1)
    #POP_CSR(msaveepc1)
    #POP_CSR(msavestatus)
    POP_CSR(mslideleg)
    POP_CSR(mdcause)
    POP_CSR(mxstatus)
    POP_CSR(msp_base)
    POP_CSR(msp_bound)
    POP_CSR(mhsp_ctl)
    #POP_CSR(mfiob)
    #POP_CSR(mppib)
    POP_CSR(mcctldata)
    POP_CSR(mcctlcommand)
    POP_CSR(mcctlbeginaddr)
    POP_CSR(mcache_ctl)
    #POP_CSR(mnvec)
    #POP_CSR(mecc_code)
    #POP_CSR(mdlmb)
    #POP_CSR(milmb)

    # Pop RISC-V m-mode reg
    POP_CSR(mcountinhibit)
    POP_CSR(mcounteren)
    POP_CSR(mip)
    POP_CSR(mtval)
    POP_CSR(mcause)
    POP_CSR(mepc)
    POP_CSR(mscratch)
    POP_CSR(mtvec)
    POP_CSR(mie)
    POP_CSR(mideleg)
    POP_CSR(medeleg)
    POP_CSR(misa)
    POP_CSR(mstatus)

    #POP f0-f31
    POP_FGPR(f31)
    POP_FGPR(f30)
    POP_FGPR(f29)
    POP_FGPR(f28)
    POP_FGPR(f27)
    POP_FGPR(f26)
    POP_FGPR(f25)
    POP_FGPR(f24)
    POP_FGPR(f23)
    POP_FGPR(f22)
    POP_FGPR(f21)
    POP_FGPR(f20)
    POP_FGPR(f19)
    POP_FGPR(f18)
    POP_FGPR(f17)
    POP_FGPR(f16)
    POP_FGPR(f15)
    POP_FGPR(f14)
    POP_FGPR(f13)
    POP_FGPR(f12)
    POP_FGPR(f11)
    POP_FGPR(f10)
    POP_FGPR(f9)
    POP_FGPR(f8)
    POP_FGPR(f7)
    POP_FGPR(f6)
    POP_FGPR(f5)
    POP_FGPR(f4)
    POP_FGPR(f3)
    POP_FGPR(f2)
    POP_FGPR(f1)
    POP_FGPR(f0)

    # Pop x1~x31
    POP(x31)
    POP(x30)
    POP(x29)
    POP(x28)
    POP(x27)
    POP(x26)
    POP(x25)
    POP(x24)
    POP(x23)
    POP(x22)
    POP(x21)
    POP(x20)
    POP(x19)
    POP(x18)
    POP(x17)
    POP(x16)
    POP(x15)
    POP(x14)
    POP(x13)
    POP(x12)
    POP(x11)
    POP(x10)
    POP(x9)
    POP(x8)
    POP(x7)
    POP(x6)
    POP(x5)
    POP(x4)
    POP(x3)
    POP(x2)
    POP(x1)
    # li	t0, 0xe0500000
    # lw	t1, 0(t0)
    # li	t0, -1
    # beq	t0, t1, no_enable_l2

    csrr    t0, mhartid
    bnez	t0, no_enable_l2

    # enable L2
    li	t0, 0x9e900008
    lw	t1, 0(t0)
    ori	t1, t1, 0x1
    sw	t1, 0(t0)

no_enable_l2:
    # enable d-cache
    csrrs	t0, mcache_ctl, 0x2
    ret
