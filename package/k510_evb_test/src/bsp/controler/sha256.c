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
#include <string.h>
#include "platform.h"
#include "sha256.h"

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define BYTESWAP(x) ((ROTR((x), 8) & 0xff00ff00L) | (ROTL((x), 8) & 0x00ff00ffL))
#define BYTESWAP64(x) byteswap64(x)

volatile sha256_t *const sha256 = (volatile sha256_t *)SHA_BASE_ADDR;
static dma_ch_t channel = DMA_CHANNEL_0;
static peri_dma_cfg_t sha_dma_cfg = {
    .dev_sel = SHA_TX,
    .ch_priority = 1,
    .mode = LINE_MODE,
    .src_type = CONTINUOUS_ADDRESS,
    .buswidth = FOUR_BYTE,
    .dev_burst_len = 0,
    .line_size = 64,
    .dev_timeout = 0xFFF
};

static const uint8_t padding[64] =
    {
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static inline uint64_t byteswap64(uint64_t x)
{
    uint32_t a = (uint32_t)(x >> 32);
    uint32_t b = (uint32_t)x;
    return ((uint64_t)BYTESWAP(b) << 32) | (uint64_t)BYTESWAP(a);
}

void sha256_init(sha256_context_t *context, size_t input_len, sha256_cfg_t* cfg)
{
    sha256->sha_num_reg.sha_data_th = (uint32_t)((input_len + SHA256_BLOCK_LEN + 8) / SHA256_BLOCK_LEN);
    sha256->sha_function_reg_0.sha_endian = SHA256_BIG_ENDIAN;
    if (cfg->init_hash) {
        for (int i = 0; i < 8; ++i) {
            sha256->init_hash[i] = *(cfg->init_hash + i);
        }
    }
    sha256->sha_function_reg_0.sha_otp_en = cfg->opt_hash_en ? 1 : 0;
    sha256->double_sha = cfg->double_sha_en ? 1 : 0;
    sha256->sha_function_reg_1.dma_en = cfg->dma_en ? 1 : 0;
    sha256->sha_function_reg_0.sha_en = ENABLE_SHA;
    if (cfg->dma_en) {
        channel = cfg->dma_ch;
        sha_dma_cfg.channel = cfg->dma_ch;
        sha_dma_cfg.daddr = (void*)(&sha256->sha_data_in0);
    }
    context->total_len = 0L;
    context->buffer_len = 0L;
}

void sha256_update(sha256_context_t *context, const void *input, size_t input_len)
{
    const uint8_t *data = input;
    size_t buffer_bytes_left;
    size_t bytes_to_copy;
    uint32_t i;

    while(input_len)
    {
        buffer_bytes_left = SHA256_BLOCK_LEN - context->buffer_len;
        bytes_to_copy = buffer_bytes_left;
        if(bytes_to_copy > input_len)
            bytes_to_copy = input_len;
        memcpy(&context->buffer.bytes[context->buffer_len], data, bytes_to_copy);
        context->total_len += bytes_to_copy * 8L;
        context->buffer_len += bytes_to_copy;
        data += bytes_to_copy;
        input_len -= bytes_to_copy;
        if(context->buffer_len == SHA256_BLOCK_LEN)
        {
            if (sha256->sha_function_reg_1.dma_en) {
                sha_dma_cfg.saddr = (void*)(&context->buffer.words[0]);
                peri_dma_config(&sha_dma_cfg);
                peri_dma_start(channel);
                peri_dma_wait_done_or_timeout(channel);
            } else {
                for(i = 0; i < 16; i++)
                {
                    while(sha256->sha_function_reg_1.fifo_in_full)
                        ;
                    sha256->sha_data_in0 = context->buffer.words[i];
                }
            }
            context->buffer_len = 0L;
        }
    }
}

void sha256_final(sha256_context_t *context, uint8_t *output)
{
    size_t bytes_to_pad;
    size_t length_pad;
    uint32_t i;

    bytes_to_pad = 120L - context->buffer_len;
    if(bytes_to_pad > 64L)
        bytes_to_pad -= 64L;
    length_pad = BYTESWAP64(context->total_len);
    sha256_update(context, padding, bytes_to_pad);
    sha256_update(context, &length_pad, 8L);
    if(!sha256->double_sha)
        while(!(sha256->sha_function_reg_0.sha_en));
    else
        while(!(sha256->double_sha));
    if(output)
    {
        for(i = 0; i < SHA256_HASH_WORDS; i++)
        {
            *((uint32_t *)output) = sha256->sha_result[SHA256_HASH_WORDS - i - 1];
            output += 4;
        }
    }
}

void sha256_hard_calculate(const uint8_t* input, size_t input_len, uint8_t* output, sha256_cfg_t* cfg)
{
    sha256_context_t sha;
    sha256_init(&sha, input_len, cfg);
    sha256_update(&sha, input, input_len);
    sha256_final(&sha, output);
}
