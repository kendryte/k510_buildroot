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
#ifndef _CACHE_H
#define _CACHE_H
#include "platform.h"
#include <stdint.h>
#include <stddef.h>
#include <core_v5.h>
typedef struct{
    volatile unsigned long  configure;
    volatile unsigned long  control;
    volatile unsigned long  hpm0;
    volatile unsigned long  hpm1;
    volatile unsigned long  hpm2;
    volatile unsigned long  hpm3;
    volatile unsigned long  error_status;
    volatile unsigned long  ecc_error;
    volatile unsigned long  cctl_command0;
    volatile unsigned long  cctl_access_line0;
    volatile unsigned long  cctl_command1;
    volatile unsigned long  cctl_access_line1;
    volatile unsigned long  cctl_command2;
    volatile unsigned long  cctl_access_line2;
    volatile unsigned long  cctl_command3;
    volatile unsigned long  cctl_access_line3;
    volatile unsigned long  cctl_status;
    volatile unsigned long  reserve0;
    volatile unsigned long  tgt_write_data[4];
    volatile unsigned long  tgt_read_data[4];
} l2cache;

volatile l2cache *ax25_l2cache;

/* Control Register */
#define L2_ENABLE   0x1
/* prefetch */
#define IPREPETCH_OFF   3
#define DPREPETCH_OFF   5
#define IPREPETCH_MSK   (3 << IPREPETCH_OFF)
#define DPREPETCH_MSK   (3 << DPREPETCH_OFF)
/* tag ram */
#define TRAMOCTL_OFF    8
#define TRAMICTL_OFF    10
#define TRAMOCTL_MSK    (3 << TRAMOCTL_OFF)
#define TRAMICTL_MSK    (1 << TRAMICTL_OFF)
/* data ram */
#define DRAMOCTL_OFF    11
#define DRAMICTL_OFF    13
#define DRAMOCTL_MSK    (3 << DRAMOCTL_OFF)
#define DRAMICTL_MSK    (1 << DRAMICTL_OFF)

/* CCTL Command Register */
#define L2CCTL_CMD_REG(hart)    (L2C_BASE_ADDR + 0x40 + (hart) * 0x10)
#define L2CCTL_LINE_REG(hart)   (L2C_BASE_ADDR + 0x48 + (hart) * 0x10)

#define CCTL_L2_IX_INVAL    0x00
#define CCTL_L2_IX_WB       0x01
#define CCTL_L2_IX_WBINVAL  0x02
#define CCTL_L2_PA_INVAL    0x08
#define CCTL_L2_PA_WB       0x09
#define CCTL_L2_PA_WBINVAL  0x0A
#define CCTL_L2_TGT_WRITE   0x10
#define CCTL_L2_TGT_READ    0x11
#define CCTL_L2_WBINVAL_ALL 0x12

#define L2_SET_NUM          (512)
#define L2_WAY_NUM          (16)
#define L2_CACHE_LINE_SIZE  (32)
#define L2_CACHE_SIZE       (256 * 1024)

#define L2_INDEX(way, set)              (((way & 0xF) << 28) | ((set & 0x7FFF) << 5))
#define L2_TGT_INDEX(way, set, type)    (((way & 0xF) << 28) | ((set & 0x7FFF) << 5) | ((type & 0x3) << 26))

/* CCTL Status Register */
#define CCTL_STATUS_MSK(hart)       (0xf << ((hart) * 4))
#define CCTL_STATUS_IDLE(hart)      (0 << ((hart) * 4))
#define CCTL_STATUS_PROCESS(hart)   (1 << ((hart) * 4))
#define CCTL_STATUS_ILLEGAL(hart)   (2 << ((hart) * 4))

typedef enum l2tag_type
{
    L2_TAG_RAM,
    L2_DATA_RAM,
} l2tag_type_t;

/* L1 cache */
#define NDS_ISET                0x7
#define NDS_IWAY                0x38
#define NDS_ISIZE               0x1C0
#define NDS_DSET                0x7
#define NDS_DWAY                0x38
#define NDS_DSIZE               0x1C0

#define L1_SET_NUM              (256)
#define L1_WAY_NUM              (4)
#define L1_CACHE_LINE_SIZE      (32)
#define L1_CACHE_SIZE           (32 * 1024)

/* AndeStar CCTL Register Bit Field */
/* CSR NDS_MCACHE_CTL */
#define CCTL_SUEN_MSK               (1ULL << (8))
/* CSR NDS_MMSC_CFG */
#define CCTLCSR_MSK             (1ULL << (16))
#define VCCTL_MSK               ((1ULL << (18)) | (1ULL << (19)))

typedef enum l1cache_type
{
    L1_ICACHE = 0x01,
    L1_DCACHE = 0x02,
    L1_IDCACHE = 0x03,
} l1cache_type_t;

/* AndeStar CCTL Command Machine mode */
/* Allow S/U mode */
#define CCTL_L1D_VA_INVAL           0
/* Allow S/U mode */
#define CCTL_L1D_VA_WB              1
/* Allow S/U mode */
#define CCTL_L1D_VA_WBINVAL         2
#define CCTL_L1D_VA_LOCK            3
#define CCTL_L1D_VA_UNLOCK          4
#define CCTL_L1D_WBINVAL_ALL        6
#define CCTL_L1D_WB_ALL             7
/* Allow S/U mode */
#define CCTL_L1I_VA_INVAL           8
#define CCTL_L1I_VA_LOCK            11
#define CCTL_L1I_VA_UNLOCK          12
#define CCTL_L1D_IX_INVAL           16
#define CCTL_L1D_IX_WB              17
#define CCTL_L1D_IX_WBINVAL         18
#define CCTL_L1D_IX_RTAG            19
#define CCTL_L1D_IX_RDATA           20
#define CCTL_L1D_IX_WTAG            21
#define CCTL_L1D_IX_WDATA           22
#define CCTL_L1D_INVAL_ALL          23
#define CCTL_L1I_IX_INVAL           24
#define CCTL_L1I_IX_RTAG            27
#define CCTL_L1I_IX_RDATA           28
#define CCTL_L1I_IX_WTAG            29
#define CCTL_L1I_IX_WDATA           30

#define USE_CCTL                0
#define BUF_SIZE                0x100

#define l1cctl_set_addr(addr) write_csr(NDS_MCCTLBEGINADDR, addr)
#define l1cctl_set_cmd(cmd) write_csr(NDS_MCCTLCOMMAND, cmd)
#define l1cctl_set_data(data) write_csr(NDS_MCCTLDATA, data)
#define l1cctl_read_data()  read_csr(NDS_MCCTLDATA)

#define dcache_wb_all()         l1cctl_set_cmd(CCTL_L1D_WB_ALL)
#define dcache_wbinval_all()    l1cctl_set_cmd(CCTL_L1D_WBINVAL_ALL)
#define dcache_inval_all()      l1cctl_set_cmd(CCTL_L1D_INVAL_ALL)

#define L1_INDEX(way, set, dwcb) (((way & 0x3) << 13) | ((set & 0xFF) << 5) | ((dwcb & 0x3) << 3))

#define l1cache_enable()        write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) | 0x3))
#define l1cache_disable()       write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) & ~0x3))
#define l1icache_enable()       write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) | 0x1))
#define l1icache_disable()      write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) & ~0x1))
#define l1dcache_enable()       write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) | 0x2))
#define l1dcache_disable()      write_csr(NDS_MCACHE_CTL, (read_csr(NDS_MCACHE_CTL) & ~0x2))

#define l1cache_flush()         do {                            \
                                    asm volatile ("fence.i");   \
                                    dcache_inval_all();         \
                                }while(0)

#define l1cache_wb_all()        dcache_wb_all()
#define l1cache_wbinval_all()   dcache_wbinval_all()

#define l2cache_disable()       ax25_l2cache->control &= ~0x1UL

#define l2cache_flush()\
do{\
    register uint64_t mhart = read_csr(NDS_MHARTID);\
    register uint64_t *command = (uint64_t *)L2CCTL_CMD_REG(mhart);\
    *command = CCTL_L2_WBINVAL_ALL;\
    while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));\
}while(0);

#define cache_flush()\
do{\
    l1cache_flush();\
    if(!is_dsp_type())\
        l2cache_flush();\
}while(0);

#define cache_disable()\
do{\
    l1cache_disable();\
    if(!is_dsp_type())\
        l2cache_disable();\
}while(0);

#define cache_flush_disable(void)\
do{\
    l1cache_flush();\
    l1cache_disable();\
    l1cache_inval_all(L1_ICACHE);\
    if(!is_dsp_type())\
    {\
        l2cache_disable();\
        l2cache_flush();\
    }\
}while(0);

void l1cache_inval_all(l1cache_type_t l1type);
void l1cache_va_inval(uint64_t addr, size_t len, l1cache_type_t l1type);
void l1cache_va_wb(uint64_t addr, size_t len);
void l1cache_va_wbinval(uint64_t addr, size_t len);
void l1cache_read_data(uint8_t way, uint8_t set, uint8_t dwcb, uint64_t *data, size_t len, uint32_t cmd);
void l1cache_write_data(uint8_t way, uint8_t set, uint8_t dwcb, uint64_t *data, size_t len, uint32_t cmd);

void l2cache_enable(void);
// void l2cache_flush(void);
void l2cache_inval_all(void);
void l2cache_wb_all(void);
void l2cache_wbinval_all(void);
void l2cache_pa_inval(uint64_t addr, size_t len);
void l2cache_pa_wb(uint64_t addr, size_t len);
void l2cache_pa_wbinval(uint64_t addr, size_t len);
void l2cache_write_data(uint8_t way, uint16_t set, uint64_t data[4], l2tag_type_t type);
void l2cache_read_data(uint8_t way, uint16_t set, uint64_t data[4], l2tag_type_t type);
void l2cache_ix_handle(uint8_t way, uint16_t set, uint32_t cmd);

/**
 * @brief    Enable L1 and L2 cache
 *
 */
void cache_enable(void);

/**
 * @brief    Disable L1 and L2 cache, unpredictable errors may occur
 *
 */
// void cache_disable(void);

/**
 * @brief    Write back and invalidate all cache(Icache Dcache L2)
 *
 */
// void cache_flush(void);

/**
 * @brief    Write back and invalidate all cache, then disable all cache
 *
 */
// void cache_flush_disable(void);

/**
 * @brief    Invalidate all cache
 *
 * @param    l1type         [Icache/Dcache/Icache and Dcache]
 */
void cache_inval_all(l1cache_type_t l1type);

/**
 * @brief    Write back Dcache and L2
 *
 */
void cache_wb_all(void);

/**
 * @brief    Write back and invalidate Dcache and L2
 *
 */
void cache_wbinval_all(void);

/**
 * @brief    Invalidate cache by address
 *
 * @param    va             [virtual address for L1, va = pa if mmu is disabled]
 * @param    pa             [physical address for L2]
 * @param    len            [invalid range]
 * @param    l1type         [Icache/Dcache/Icache and Dcache]
 */
void cache_inval(uint64_t va, uint64_t pa, size_t len, l1cache_type_t l1type);

/**
 * @brief    Write back Dcache and L2 by address
 *
 * @param    va             [virtual address for L1, va = pa if mmu is disabled]
 * @param    pa             [physical address for L2]
 * @param    len            [write back range]
 */
void cache_wb(uint64_t va, uint64_t pa, size_t len);

/**
 * @brief    Write back and invalidate  Dcache and L2 by address
 *
 * @param    va             [virtual address for L1, va = pa if mmu is disabled]
 * @param    pa             [physical address for L2]
 * @param    len            [write back and invalid range]
 */
void cache_wbinval(uint64_t va, uint64_t pa, size_t len);

#endif /* _ASM_V5_L2CACHE_H */
