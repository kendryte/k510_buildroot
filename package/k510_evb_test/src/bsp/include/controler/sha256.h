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
#ifndef _SHA256_H
#define _SHA256_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "dmac.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ENABLE_SHA (0x1)
#define SHA256_BIG_ENDIAN (0x1)

#define SHA256_HASH_LEN 32
#define SHA256_HASH_WORDS 8
#define SHA256_BLOCK_LEN 64L

typedef struct _sha_num_reg
{
    /* sha data push threshold */
    uint32_t sha_data_th : 16;
    /* sha data push count */
    uint32_t sha_data_cnt : 16;
} __attribute__((packed, aligned(4))) sha_num_reg_t;

typedef struct _sha_function_reg_0
{
    /* write:SHA256 enable register. read:Calculation completed flag  */
    uint32_t sha_en : 1;
    uint32_t sha_otp_en : 1;
    uint32_t reserved00 : 6;
    /* SHA256 calculation overflow flag */
    uint32_t sha_overflow : 1;
    uint32_t reserved01 : 7;
    /* Endian setting; b'0:little endian b'1:big endian */
    uint32_t sha_endian : 1;
    uint32_t reserved02 : 15;
} __attribute__((packed, aligned(4))) sha_function_reg_0_t;

typedef struct _sha_function_reg_1
{
    /* Sha and DMA handshake signals enable.b'1:enable;b'0:disable */
    uint32_t dma_en : 1;
    uint32_t reserved10 : 7;
    /* b'1:sha256 fifo is full; b'0:not full */
    uint32_t fifo_in_full : 1;
    uint32_t reserved11 : 23;
} __attribute__((packed, aligned(4))) sha_function_reg_1_t;

typedef struct _sha256
{
    /* Calculated sha256 return value. */
    uint32_t sha_result[8];
    /* SHA256 input data from this register. */
    uint32_t sha_data_in0;
    uint32_t reverse0;
    sha_num_reg_t sha_num_reg;
    sha_function_reg_0_t sha_function_reg_0;
    uint32_t double_sha;    
    sha_function_reg_1_t sha_function_reg_1;
    uint32_t init_hash[8];
} __attribute__((packed, aligned(4))) sha256_t;

typedef struct _sha256_context
{
    size_t total_len;
    size_t buffer_len;
    union
    {
        uint32_t words[16];
        uint8_t bytes[64];
    } buffer;
} sha256_context_t;

typedef struct sha256_cfg
{
    uint32_t* init_hash;
    dma_ch_t dma_ch;
    bool opt_hash_en;
    bool double_sha_en;
    bool dma_en;
} sha256_cfg_t;

extern volatile sha256_t *const sha256;

/**
 * @brief       Init SHA256 calculation context
 *
 * @param[in]   context SHA256 context object
 *
 */
void sha256_init(sha256_context_t *context, size_t input_len, sha256_cfg_t* cfg);

/**
 * @brief       Called repeatedly with chunks of the message to be hashed
 *
 * @param[in]   context SHA256 context object
 * @param[in]   data_buf    data chunk to be hashed
 * @param[in]   buf_len    length of data chunk
 *
 */
void sha256_update(sha256_context_t *context, const void *input, size_t input_len);

/**
 * @brief       Finish SHA256 hash process, output the result.
 *
 * @param[in]   context SHA256 context object
 * @param[out]  output  The buffer where SHA256 hash will be output
 *
 */
void sha256_final(sha256_context_t *context, uint8_t *output);

/**
 * @brief       Simple SHA256 hash once.
 *
 * @param[in]   data      Data will be hashed
 * @param[in]   data_len  Data length
 * @param[out]  output    Output buffer
 *
 */
void sha256_hard_calculate(const uint8_t* input, size_t input_len, uint8_t* output, sha256_cfg_t* cfg);

#ifdef __cplusplus
}
#endif

#endif