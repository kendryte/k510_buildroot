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
#include "platform.h"
#include "dmac.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

#define PERI_DEV_SEL    0x260

typedef struct sdma {
    volatile uint32_t int_raw;
    volatile uint32_t int_en;
    volatile uint32_t int_state;
    volatile uint32_t ch_weight;
} sdma_t;

typedef struct sdma_ch {
    volatile uint32_t ch_ctl;
    volatile uint32_t ch_cfg0;
    volatile uint32_t ch_cfg1;
    volatile uint32_t ch_saddr;
    volatile uint32_t ch_daddr;
    volatile uint32_t ch_user_data;
    volatile uint32_t ch_llt_cfg;
    volatile uint32_t ch_state;
} sdma_ch_t;

typedef struct llt_entry {
    volatile uint32_t saddr;
    volatile uint32_t daddr;
    volatile uint32_t size;
    volatile uint32_t cfg;
} llt_entry_t;

typedef struct pdma {
    volatile uint32_t int_raw0;
    volatile uint32_t int_raw1;
    volatile uint32_t int_en0;
    volatile uint32_t int_en1;
    volatile uint32_t int_state0;
    volatile uint32_t int_state1;
} pdma_t;

typedef struct pdma_ch {
    volatile uint32_t ch_ctl;
    volatile uint32_t ch_cfg0;
    volatile uint32_t ch_cfg1;
    volatile uint32_t ch_saddr;
    volatile uint32_t ch_daddr;
    volatile uint32_t ch_dev_timeout;
    volatile uint32_t ch_state;
} pdma_ch_t;

typedef struct pdma_dev_sel {
    volatile uint32_t ch_dev_sel[16];
} pdma_dev_sel_t;

static volatile sdma_t* const sdma = (volatile sdma_t*)SDMA_BASE_ADDR;
static volatile pdma_t* const pdma = (volatile pdma_t*)PDMA_BASE_ADDR;

static volatile sdma_ch_t* const sdma_ch[] = {
    (volatile sdma_ch_t*)(SDMA_BASE_ADDR + 0x20),
    (volatile sdma_ch_t*)(SDMA_BASE_ADDR + 0x40),
    (volatile sdma_ch_t*)(SDMA_BASE_ADDR + 0x60),
    (volatile sdma_ch_t*)(SDMA_BASE_ADDR + 0x80),
};

static volatile pdma_ch_t* const pdma_ch[] = {
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x20),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x40),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x60),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x80),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0xA0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0xC0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0xE0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x100),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x120),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x140),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x160),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x180),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x1A0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x1C0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x1E0),
    (volatile pdma_ch_t*)(PDMA_BASE_ADDR + 0x200),
};

static volatile pdma_dev_sel_t* const pdma_ch_dev_sel = (volatile pdma_dev_sel_t*)(PDMA_BASE_ADDR + PERI_DEV_SEL);

#define set_bits(reg, mask, offset, val) do {   \
    (reg) &= ~((mask) << (offset));             \
    (reg) |= (val) << (offset);                 \
} while (0)

static void sys_dma_int_en(uint8_t ch, bool en)
{
    const uint32_t t[2][4] = {
        { 0xEEE, 0xDDD, 0xBBB, 0x777 },
        { 0x111, 0x222, 0x444, 0x888 }
    };
    if (en) {
        sdma->int_en |= t[1][ch];
    } else {
        sdma->int_en &= t[0][ch];
    }
}

static void sys_dma_clear_int(uint8_t ch)
{
    const uint32_t t[4] = { 0x111, 0x222, 0x444, 0x888 };
    sdma->int_raw |= t[ch];
}

static void peri_dma_int_en(uint8_t ch, bool en)
{
    if (en) {
        pdma->int_en0 |= (1 << (ch + 16) | 1 << ch);
        pdma->int_en1 |= 1 << ch;
    } else {
        pdma->int_en0 &= ~(1 << (ch + 16) | 1 << ch);
        pdma->int_en1 &= ~(1 << ch);
    }
}

void peri_dma_clear_int(uint8_t ch)
{
    pdma->int_raw0 = (1 << (ch + 16) | 1 << ch);
    pdma->int_raw1 = 1 << ch;
}

void peri_dma_clear_done(uint8_t ch)
{
    pdma->int_raw0 = (1 << ch);
}

void peri_dma_clear_half_done(uint8_t ch)
{
    pdma->int_raw0 = (1 << (ch + 16));
}

void peri_dma_clear_timeout(uint8_t ch)
{
    pdma->int_raw1 = (1 << ch);
}


int sys_dma_config(const sys_dma_cfg_t* cfg)
{
    uint8_t ch = cfg->channel;
    if (ch >= DMA_CHANNEL_4) return -1;

    while (!(sdma_ch[ch]->ch_state & 0x1))
        ;
    sys_dma_int_en(ch, false);
    sys_dma_clear_int(ch);
    if (cfg->mode == LINE_MODE) {
        set_bits(sdma_ch[ch]->ch_cfg0, 0xFFFFF, 0, cfg->cfg.line_mode_cfg->line_size);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 16, 0);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 18, cfg->cfg.line_mode_cfg->endian);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x1, 20, cfg->cfg.line_mode_cfg->fixed_word);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 24, cfg->cfg.line_mode_cfg->user_data_size);
        set_bits(sdma_ch[ch]->ch_saddr, 0xFFFFFFFF, 0, (uint32_t)cfg->cfg.line_mode_cfg->saddr);
        set_bits(sdma_ch[ch]->ch_daddr, 0xFFFFFFFF, 0, (uint32_t)cfg->cfg.line_mode_cfg->daddr);
        set_bits(sdma_ch[ch]->ch_user_data, 0xFFFFFFFF, 0, cfg->cfg.line_mode_cfg->user_data);
    }
    else if (cfg->mode == RECT_MODE) {
        set_bits(sdma_ch[ch]->ch_cfg0, 0xFFFFF, 0, cfg->cfg.rect_mode_cfg->line_size);
        set_bits(sdma_ch[ch]->ch_cfg0, 0x7FF, 20, cfg->cfg.rect_mode_cfg->line_num);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 16, 1);
        set_bits(sdma_ch[ch]->ch_cfg1, 0xFFFF, 0, cfg->cfg.rect_mode_cfg->line_space);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 18, cfg->cfg.rect_mode_cfg->endian);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x1, 20, cfg->cfg.rect_mode_cfg->fixed_word);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 24, cfg->cfg.rect_mode_cfg->user_data_size);
        set_bits(sdma_ch[ch]->ch_saddr, 0xFFFFFFFF, 0, (uint32_t)cfg->cfg.rect_mode_cfg->saddr);
        set_bits(sdma_ch[ch]->ch_daddr, 0xFFFFFFFF, 0, (uint32_t)cfg->cfg.rect_mode_cfg->daddr);
        set_bits(sdma_ch[ch]->ch_user_data, 0xFFFFFFFF, 0, cfg->cfg.rect_mode_cfg->user_data);
    }
    else {
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 16, 2);
        set_bits(sdma_ch[ch]->ch_cfg1, 0x3, 18, cfg->cfg.llt_mode_cfg->endian);
        sdma_ch[ch]->ch_llt_cfg = cfg->cfg.llt_mode_cfg->llt_saddr | 0x100 |
            (cfg->cfg.llt_mode_cfg->llt_len << 12) | 0x80000 |
            (cfg->cfg.llt_mode_cfg->llt_grp_num << 20) | 0x8000000;
    }
    return 0;
}

void sys_dma_config_llt(const llt_cfg_t* llt_cfg)
{
    volatile llt_entry_t* entry = (volatile llt_entry_t*)(SDMA_BASE_ADDR + 0x100 + (0x10 * llt_cfg->entry));
    entry->saddr = (uint32_t)llt_cfg->saddr;
    entry->daddr = (uint32_t)llt_cfg->daddr;
    entry->size = llt_cfg->size;
    entry->cfg = (llt_cfg->channel << 4) | (llt_cfg->first ? 2 : 0) | (llt_cfg->done ? 0 : 1);
}

void sys_dma_start(dma_ch_t channel)
{
	sys_dma_int_en(channel, true);
    sdma_ch[channel]->ch_ctl = 0x3;
}

void sys_dma_stop(dma_ch_t channel)
{
    sdma_ch[channel]->ch_ctl = 0x3 << 4;
}

void sys_dma_pause(dma_ch_t channel)
{
    sdma_ch[channel]->ch_ctl = 0x3 << 8;
}

void sys_dma_continue(dma_ch_t channel)
{
    sdma_ch[channel]->ch_ctl = 0x2 << 8;
}

void sys_dma_wait_idle(dma_ch_t channel)
{
    while(!(sdma_ch[channel]->ch_state & 0x1))
        ;
}

void sys_dma_wait_done(dma_ch_t channel)
{
    while(!(sdma->int_state & (0x1 << channel)))
        ;
    sdma->int_raw = 0x1 << channel;
}

void sys_dma_wait_half_done(dma_ch_t channel)
{
    while(!(sdma->int_state & (0x10 << channel)))
        ;
    sdma->int_raw = 0x10 << channel;
}

void sys_dma_wait_llt_event(dma_ch_t channel)
{
    while(!(sdma->int_state & (0x100 << channel)))
        ;
    sdma->int_raw = 0x100 << channel;
}

bool sys_dma_is_idle(dma_ch_t channel)
{
    return sdma_ch[channel]->ch_state & 0x1;
}

int peri_dma_config(const peri_dma_cfg_t* cfg)
{
    uint8_t ch = cfg->channel;
    if (ch >= DMA_CHANNEL_MAX) return -1;

    while (!(pdma_ch[ch]->ch_state & 0x1))
        ;
    peri_dma_int_en(ch, false);
    peri_dma_clear_int(ch);
    pdma_ch_dev_sel->ch_dev_sel[ch] = cfg->dev_sel;
    pdma_ch[ch]->ch_ctl = cfg->endian << 2;
    uint32_t cfg0 = cfg->src_type | (cfg->buswidth << 2) |
        (cfg->mode << 4) | ((cfg->ch_priority ? cfg->ch_priority : 1) << 8) |
        (cfg->dev_burst_len << 12);
    if (cfg->line_num)
        cfg0 |= cfg->line_num << 16;
    pdma_ch[ch]->ch_cfg0 = cfg0;
    pdma_ch[ch]->ch_cfg1 = cfg->line_size | (cfg->line_space << 16);
    pdma_ch[ch]->ch_saddr = (uint32_t)cfg->saddr;
    pdma_ch[ch]->ch_daddr = (uint32_t)cfg->daddr;
    if (cfg->dev_timeout)
        pdma_ch[ch]->ch_dev_timeout = cfg->dev_timeout;

    return 0;
}

void peri_dma_start(dma_ch_t channel)
{
    peri_dma_int_en(channel, true);
    pdma_ch[channel]->ch_ctl |= 0x3;
}

void peri_dma_stop(dma_ch_t channel)
{
    pdma_ch[channel]->ch_ctl |= 0x3 << 4;
}

void peri_dma_pause(dma_ch_t channel)
{
    pdma_ch[channel]->ch_ctl |= 0x3 << 8;
}

void peri_dma_continue(dma_ch_t channel)
{
    pdma_ch[channel]->ch_ctl |= 0x2 << 8;
}

void peri_dma_wait_done_or_timeout(dma_ch_t channel) 
{
    while (!((pdma->int_state0 >> channel) & 0x1) && !((pdma->int_state1 >> channel) & 0x1))
        ;
}

bool peri_dma_is_done(dma_ch_t channel)
{
    return (pdma->int_state0 >> channel) & 0x1;
}

bool peri_dma_is_timeout(dma_ch_t channel)
{
    return (pdma->int_state1 >> channel) & 0x1;
}

uint32_t peri_dma_get_state0()
{
    return pdma->int_state0;
}

uint32_t peri_dma_get_state1()
{
    return pdma->int_state1;
} 

#pragma GCC diagnostic pop
