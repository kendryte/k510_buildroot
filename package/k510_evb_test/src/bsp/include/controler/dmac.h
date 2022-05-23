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
#ifndef DRIVER_DMA_H
#define DRIVER_DMA_H

#include <stdint.h>
#include <stdbool.h>

typedef enum dma_channel {
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3, // system dma has only 4 channels
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7,
    DMA_CHANNEL_8,
    DMA_CHANNEL_9,
    DMA_CHANNEL_10,
    DMA_CHANNEL_11,
    DMA_CHANNEL_12,
    DMA_CHANNEL_13,
    DMA_CHANNEL_14,
    DMA_CHANNEL_15,
    DMA_CHANNEL_MAX
} dma_ch_t;

typedef enum dma_mode {
    LINE_MODE,
    RECT_MODE,
    LLT_MODE,
    DMA_MODE_MAX
} dma_mode_t;

typedef enum peri_dev_sel {
    UART0_TX        = 0,
    UART0_RX        = 1,
    UART1_TX        = 2,
    UART1_RX        = 3,
    UART2_TX        = 4,
    UART2_RX        = 5,
    SPI0_TX         = 6,
    SPI0_RX         = 7,
    SPI1_TX         = 8,
    SPI1_RX         = 9,
    SPI2_TX         = 0xa,
    SPI2_RX         = 0xb,
    SPI3_TX         = 0xc,
    SPI3_RX         = 0xd,
    I2S0_TX         = 0xe,
    I2S0_RX         = 0xf,
    I2S1_TX         = 0x10,
    I2S1_RX         = 0x11,
    UART3_TX        = 0x12,
    UART3_RX        = 0x13,
    I2C0_TX         = 0x14,
    I2C0_RX         = 0x15,
    I2C1_TX         = 0x16,
    I2C1_RX         = 0x17,
    I2C2_TX         = 0x18,
    I2C2_RX         = 0x19,
    AUDIF_OUT       = 0x1b,
    AUDIF_IN        = 0x1c,
    AUDIF_REF       = 0x1d,
    RESERVED        = 0x1e,
    VAD_RX          = 0x1F,
    SHA_TX          = 0x20,
    AES_TX          = 0x21,
    AES_RX          = 0x22,
    PERI_DEV_SEL_MAX
} peri_dev_sel_t;

typedef enum src_type {
    CONTINUOUS_ADDRESS,
    FIXED_REG_ADDRESS,
    SRC_TYPE_MAX
} src_type_t;

typedef enum dev_buswidth {
    ONE_BYTE,
    TWO_BYTE,
    FOUR_BYTE,
    DEV_BUSWIDTH_MAX
} dev_buswidth_t;

typedef enum endian {
    NO_REVERSE,
    REVERSE_2_BYTE,
    REVERSE_4_BYTE,
    REVERSE_8_BYTE,
    ENDIAN_MAX
} endian_t;

typedef struct line_mode_cfg {
    uint32_t line_size;
    const void* saddr;
    void* daddr;
    uint8_t fixed_word;
    uint8_t user_data_size;
    uint32_t user_data;
    endian_t endian;

} line_mode_cfg_t;

typedef struct rect_mode_cfg {
    uint32_t line_size;
    uint16_t line_num;
    uint16_t line_space;
    const void* saddr;
    void* daddr;
    uint8_t fixed_word;
    uint8_t user_data_size;
    uint32_t user_data;
    endian_t endian;
} rect_mode_cfg_t;

typedef struct llt_cfg {
    const void* saddr;
    void* daddr;
    uint32_t size;
    uint16_t entry;
    uint8_t channel;
    bool done;
    bool first;
} llt_cfg_t;

typedef struct llt_mode_cfg {
    uint8_t llt_saddr;
    uint8_t llt_len;
    uint8_t llt_grp_num;
    endian_t endian;
} llt_mode_cfg_t;

typedef struct sys_dma_cfg {
    dma_ch_t channel;
    dma_mode_t mode;
    union {
        const line_mode_cfg_t* line_mode_cfg;
        const rect_mode_cfg_t* rect_mode_cfg;
        const llt_mode_cfg_t* llt_mode_cfg;
    } cfg;
} sys_dma_cfg_t;

typedef struct peri_dma_cfg {
    dma_ch_t channel;
    peri_dev_sel_t dev_sel;
    dma_mode_t mode;
    src_type_t src_type;
    dev_buswidth_t buswidth;
    endian_t endian;
    uint8_t ch_priority;
    uint8_t dev_burst_len;
    uint16_t line_size;
    uint16_t line_num;
    uint16_t line_space;
    uint16_t dev_timeout;
    const void* saddr;
    void* daddr;
} peri_dma_cfg_t;

int sys_dma_config(const sys_dma_cfg_t* cfg);
void sys_dma_config_llt(const llt_cfg_t* llt_cfg);
void sys_dma_start(dma_ch_t channel);
void sys_dma_stop(dma_ch_t channel);
void sys_dma_pause(dma_ch_t channel);
void sys_dma_continue(dma_ch_t channel);
void sys_dma_wait_idle(dma_ch_t channel);
void sys_dma_wait_done(dma_ch_t channel);
void sys_dma_wait_half_done(dma_ch_t channel);
void sys_dma_wait_llt_event(dma_ch_t channel);
bool sys_dma_is_idle(dma_ch_t channel);

int peri_dma_config(const peri_dma_cfg_t* cfg);
void peri_dma_start(dma_ch_t channel);
void peri_dma_stop(dma_ch_t channel);
void peri_dma_pause(dma_ch_t channel);
void peri_dma_continue(dma_ch_t channel);
void peri_dma_wait_done_or_timeout(dma_ch_t channel);
bool peri_dma_is_done(dma_ch_t channel);
bool peri_dma_is_timeout(dma_ch_t channel);
uint32_t peri_dma_get_state0();
uint32_t peri_dma_get_state1();
void peri_dma_clear_int(uint8_t ch);
void peri_dma_clear_done(uint8_t ch);
void peri_dma_clear_half_done(uint8_t ch);
void peri_dma_clear_timeout(uint8_t ch);

#endif
