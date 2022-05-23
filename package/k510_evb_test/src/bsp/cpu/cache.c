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
#include "cache.h"
#include "core_v5.h"
#include "platform.h"
#include <assert.h>

volatile l2cache *ax25_l2cache = (volatile l2cache *)L2C_BASE_ADDR;

#define L2CACHE_GET_LINE_CMD        register uint64_t mhart = read_csr(NDS_MHARTID);                 \
                                    register uint64_t *pa_addr = (uint64_t *)L2CCTL_LINE_REG(mhart); \
                                    register uint64_t *command = (uint64_t *)L2CCTL_CMD_REG(mhart);

void l2cache_enable(void)
{
    unsigned int ctl_val = 0, prefetch = 3;
#if defined(_EVBLP4) || defined(_EVBLP3)
    unsigned int tram_ctl[2] = {1, 0};
    unsigned int dram_ctl[2] = {1, 0};
#else
    unsigned int tram_ctl[2] = {0, 0};
    unsigned int dram_ctl[2] = {0, 0};
#endif

    // ctl_val = ax25_l2cache->control;

    // if (!(ctl_val & L2_ENABLE))
    //     ctl_val |= L2_ENABLE;
    // else
    //     return;

    /* Instruction and data fetch prefetch depth */
    ctl_val &= ~(IPREPETCH_MSK);
    ctl_val |= (prefetch << IPREPETCH_OFF);

    ctl_val &= ~(DPREPETCH_MSK);
    ctl_val |= (prefetch << DPREPETCH_OFF);

    /* Set tag RAM and data RAM setup and output cycle */
    ctl_val &= ~(TRAMOCTL_MSK | TRAMICTL_MSK);
    ctl_val |= tram_ctl[0] << TRAMOCTL_OFF;
    ctl_val |= tram_ctl[1] << TRAMICTL_OFF;

    ctl_val &= ~(DRAMOCTL_MSK | DRAMICTL_MSK);
    ctl_val |= dram_ctl[0] << DRAMOCTL_OFF;
    ctl_val |= dram_ctl[1] << DRAMICTL_OFF;

    ax25_l2cache->control = ctl_val;

    ax25_l2cache->control = ctl_val | L2_ENABLE;;
}

// void l2cache_flush(void)
// {
//     uint64_t mhart = read_csr(NDS_MHARTID);
//     uint64_t *command = (uint64_t *)L2CCTL_CMD_REG(mhart);
//     *command = CCTL_L2_WBINVAL_ALL;
//     while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
// }

void l2cache_pa_handle(uint64_t addr, size_t len, uint32_t cmd)
{
    size_t align_len = (addr & 0x1F) + len;
    size_t cctl_count = align_len & 0x1F ? (align_len >> 5) + 1 : (align_len >> 5); //align 32B

    L2CACHE_GET_LINE_CMD;

    for(uint32_t i = 0; i < cctl_count; i++)
    {
        *pa_addr = addr + (i << 5);
        *command = cmd;
        while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
    }
}

inline void l2cache_pa_inval(uint64_t addr, size_t len)
{
    l2cache_pa_handle(addr, len, CCTL_L2_PA_INVAL);
}

inline void l2cache_pa_wb(uint64_t addr, size_t len)
{
    l2cache_pa_handle(addr, len, CCTL_L2_PA_WB);
}

inline void l2cache_pa_wbinval(uint64_t addr, size_t len)
{
    l2cache_pa_handle(addr, len, CCTL_L2_PA_WBINVAL);
}

void l2cache_ix_handle(uint8_t way, uint16_t set, uint32_t cmd)
{
    L2CACHE_GET_LINE_CMD;
    *pa_addr = L2_INDEX(way, set);
    *command = cmd;
    while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
}

__attribute__((always_inline)) inline void l2cache_handle_all(uint32_t cmd)
{
    L2CACHE_GET_LINE_CMD;
    for(register uint32_t i = 0; i < L2_SET_NUM; i++)
    {
        for(register uint32_t j = 0; j < L2_WAY_NUM; j++)
        {
            *pa_addr = L2_INDEX(j, i);
            *command = cmd;
            while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
        }
    }
}

__attribute__((always_inline)) inline void l2cache_inval_all(void)
{
    l2cache_handle_all(CCTL_L2_IX_INVAL);
}

__attribute__((always_inline)) inline void l2cache_wb_all(void)
{
    l2cache_handle_all(CCTL_L2_IX_WB);
}

__attribute__((always_inline)) inline void l2cache_wbinval_all(void)
{
    l2cache_handle_all(CCTL_L2_IX_WBINVAL);
}

/* write cache line */
void l2cache_write_data(uint8_t way, uint16_t set, uint64_t data[4], l2tag_type_t type)
{
    L2CACHE_GET_LINE_CMD;
    *pa_addr = L2_TGT_INDEX(way, set, type);
    for(uint32_t i = 0; i < 4; i++)
    {
        ax25_l2cache->tgt_write_data[i] = data[i];
    }
    *command = CCTL_L2_TGT_WRITE;
    while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
}

/* read cacheline */
void l2cache_read_data(uint8_t way, uint16_t set, uint64_t data[4], l2tag_type_t type)
{
    L2CACHE_GET_LINE_CMD;
    *pa_addr = L2_TGT_INDEX(way, set, type);
    *command = CCTL_L2_TGT_READ;
    while(ax25_l2cache->cctl_status & CCTL_STATUS_MSK(mhart));
    for(uint32_t i = 0; i < 4; i++)
    {
        data[i] = ax25_l2cache->tgt_read_data[i];
    }
}

// uint64_t l1cache_read_data(uint8_t way, uint8_t set, uint8_t dwcb, uint32_t cmd)
// {
//  l1cctl_set_addr(L1_INDEX(way, set, dwcb));
//  l1cctl_set_cmd(cmd);
//  return l1cctl_read_data();
// }
void l1cache_read_data(uint8_t way, uint8_t set, uint8_t dwcb, uint64_t *data, size_t len, uint32_t cmd)
{
    l1cctl_set_addr(L1_INDEX(way, set, dwcb));
    for(uint32_t i = 0; i < len; i++)
    {
        l1cctl_set_cmd(cmd);
        *data++ = l1cctl_read_data();
    }
}

// void l1cache_write_data(uint8_t way, uint8_t set, uint8_t dwcb, uint64_t data, uint32_t cmd)
// {
//  l1cctl_set_addr(L1_INDEX(way, set, dwcb));
//  l1cctl_set_data(data);
//  l1cctl_set_cmd(cmd);
// }
void l1cache_write_data(uint8_t way, uint8_t set, uint8_t dwcb, uint64_t *data, size_t len, uint32_t cmd)
{
    l1cctl_set_addr(L1_INDEX(way, set, dwcb));
    for(uint32_t i = 0; i < len; i++)
    {
        l1cctl_set_data(*data++);
        l1cctl_set_cmd(cmd);
    }
}

#define L1_CCTL_ALL(cmd)    for(uint32_t i = 0; i < L1_SET_NUM * L1_WAY_NUM; i++)       \
                            {                                                           \
                                l1cctl_set_cmd(cmd);                                    \
                            }

__attribute__((always_inline)) inline void l1cache_inval_all(l1cache_type_t l1type)
{
    if(l1type & L1_ICACHE)
    {
        l1cctl_set_addr(L1_INDEX(0, 0, 0));
        L1_CCTL_ALL(CCTL_L1I_IX_INVAL);
    }
    if(l1type & L1_DCACHE)
    {
        dcache_inval_all();
    }
}

void l1cache_va_handle(uint64_t addr, size_t len, uint32_t cmd)
{
    size_t align_len = (addr & 0x1F) + len;
    size_t cctl_count = align_len & 0x1F ? (align_len >> 5) + 1 : (align_len >> 5); //align 32B

    l1cctl_set_addr(addr);
    while(cctl_count--)
    {
        l1cctl_set_cmd(cmd);
    }
}

void l1cache_va_inval(uint64_t addr, size_t len, l1cache_type_t l1type)
{
    if(l1type & L1_ICACHE)
        l1cache_va_handle(addr, len, CCTL_L1I_VA_INVAL);
    if(l1type & L1_DCACHE)
        l1cache_va_handle(addr, len, CCTL_L1D_VA_INVAL);
}

__attribute__((always_inline)) inline void l1cache_va_wb(uint64_t addr, size_t len)
{
    l1cache_va_handle(addr, len, CCTL_L1D_VA_WB);
}

__attribute__((always_inline)) inline void l1cache_va_wbinval(uint64_t addr, size_t len)
{
    l1cache_va_handle(addr, len, CCTL_L1D_VA_WBINVAL);
}

__attribute__((always_inline)) inline void cache_enable(void)
{
    l1cache_disable();
    if(!is_dsp_type())
        l2cache_enable();
    l1cache_enable();
}

// __attribute__((always_inline)) inline void cache_disable(void)
// {
//     l1cache_disable();
//     if(!is_dsp_type())
//         l2cache_disable();
// }

// __attribute__((always_inline)) inline void cache_flush(void)
// {
//     l1cache_flush();
//     if(!is_dsp_type())
//         l2cache_flush();
// }

// __attribute__((always_inline)) inline void cache_flush_disable(void)
// {
//     l1cache_flush();
//     l1cache_disable();
//     if(!is_dsp_type())
//     {
//         l2cache_disable();
//         l2cache_flush();
//     }
// }

void cache_inval_all(l1cache_type_t l1type)
{
    l1cache_inval_all(l1type);
    if(!is_dsp_type())
        l2cache_inval_all();
}

void cache_wb_all(void)
{
    l1cache_wb_all();
    if(!is_dsp_type())
        l2cache_wb_all();
}

void cache_wbinval_all(void)
{
    l1cache_wbinval_all();
    if(!is_dsp_type())
        l2cache_flush();
}

void cache_inval(uint64_t va, uint64_t pa, size_t len, l1cache_type_t l1type)
{
    l1cache_va_inval(va, len, l1type);
    if(!is_dsp_type())
        l2cache_pa_inval(pa, len);
}

void cache_wb(uint64_t va, uint64_t pa, size_t len)
{
    l1cache_va_wb(va, len);
    if(!is_dsp_type())
        l2cache_pa_wb(pa, len);
}

void cache_wbinval(uint64_t va, uint64_t pa, size_t len)
{
    l1cache_va_wbinval(va, len);
    if(!is_dsp_type())
        l2cache_pa_wbinval(pa, len);
}