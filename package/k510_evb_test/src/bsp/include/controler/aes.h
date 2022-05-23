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
#ifndef DRIVER_AES_H
#define DRIVER_AES_H

#include <stdint.h>
#include <stddef.h>

#include "dmac.h"
//#define OTP_KEY_TEST

typedef struct aes_mode_ctl
{
    /* [2:0]:000:cfb; 001:cbc,010:gcm,011:cfb,100:ofb*/
    uint32_t cipher_mode : 3;
    /* [4:3]:00:aes-128; 01:aes-192; 10:aes-256;11:reserved*/
    uint32_t kmode : 2;
    /* [10:5]:aes_endian */
    uint32_t aes_endian : 6;
    /* [13:11]:aes_stream_mode */
    uint32_t aes_stream_mode : 3;
    uint32_t reserved : 18;
} __attribute__((packed, aligned(4))) aes_mode_ctl_t;

typedef struct aes
{
    /* (0x00) customer key.1st~4th byte key */
    uint32_t aes_key[4];
    /* (0x10) 0: encryption; 1: decryption */
    uint32_t encrypt_sel;
    /* (0x14) aes mode reg */
    aes_mode_ctl_t mode_ctl;
    /* (0x18) Initialisation Vector. GCM support 96bit. CBC support 128bit */
    uint32_t aes_iv[4];
    /* (0x28) input data endian;1:little endian; 0:big endian */
    uint32_t aes_endian;
    /* (0x2c) calculate status. 1:finish; 0:not finish */
    uint32_t aes_finish;
    /* (0x30) aes out data to dma 0:cpu 1:dma */
    uint32_t dma_sel;
    /* (0x34) gcm Additional authenticated data number */
    uint32_t gb_aad_num;
    uint32_t reserved;
    /* (0x3c) aes plantext/ciphter text input data number */
    uint32_t gb_pc_num;
    /* (0x40) aes plantext/ciphter text input data */
    uint32_t aes_text_data;
    /* (0x44) Additional authenticated data */
    uint32_t aes_aad_data;
    /**
     * (0x48) [1:0],b'00:check not finish; b'01:check fail; b'10:check success;
     * b'11:reversed
     */
    uint32_t tag_chk;
    /* (0x4c) data can input flag. 1: data can input; 0 : data cannot input */
    uint32_t data_in_flag;
    /* (0x50) gcm input tag for compare with the calculate tag */
    uint32_t gcm_in_tag[4];
    /* (0x60) aes plantext/ciphter text output data */
    uint32_t aes_out_data;
    /* (0x64) aes module enable */
    uint32_t gb_aes_en;
    /* (0x68) data can output flag 1: data ready 0: data not ready */
    uint32_t data_out_flag;
    /* (0x6c) allow tag input when use gcm */
    uint32_t tag_in_flag;
    /* (0x70) clear tag_chk */
    uint32_t tag_clear;
    uint32_t gcm_out_tag[4];
    /* (0x84) customer key for aes-192 aes-256.5th~8th byte key */
    uint32_t aes_key_ext[4];
} aes_t;

extern volatile aes_t *const aes;

typedef enum aes_cipher_mode
{
    AES_ECB = 0,
    AES_CBC = 1,
    AES_GCM = 2,
    AES_CFB = 3,
    AES_OFB = 4,
    AES_CIPHER_MAX,
} aes_cipher_mode_t;

typedef enum aes_kmode
{
    AES_128 = 16,
    AES_192 = 24,
    AES_256 = 32,
} aes_kmode_t;

typedef enum aes_iv_len
{
    IV_LEN_96 = 12,
    IV_LEN_128 = 16,
} aes_iv_len_t;

#ifdef OTP_KEY_TEST
    typedef enum aes_encrypt_sel
    {
        AES_HARD_ENCRYPTION = 0 | 1 << 1,
        AES_HARD_DECRYPTION = 1 | 1 << 1,
    } aes_encrypt_sel_t;
#else
    typedef enum aes_encrypt_sel
    {
        AES_HARD_ENCRYPTION = 0,
        AES_HARD_DECRYPTION = 1,
    } aes_encrypt_sel_t;
#endif

typedef struct cbc_context
{
    uint8_t* input_key;
    uint8_t* iv;  // 128-bits
} cbc_context_t;

typedef struct gcm_context
{
    uint8_t* input_key;
    uint8_t* iv; // 96-bits
    uint8_t* gcm_aad;
    size_t gcm_aad_len;
} gcm_context_t;

typedef struct cfb_context
{
    uint8_t* input_key;
    uint8_t* iv;  // 128-bits
} cfb_context_t;

typedef struct ofb_context
{
    uint8_t* input_key;
    uint8_t* iv;  // 128-bits
} ofb_context_t;

void aes_init(uint8_t *input_key, size_t input_key_len, uint8_t *iv, size_t iv_len, uint8_t *gcm_aad,
              aes_cipher_mode_t cipher_mode, aes_encrypt_sel_t encrypt_sel, size_t gcm_aad_len, size_t input_data_len);

void aes_process(uint8_t *input_data, uint8_t *output_data, size_t input_data_len, aes_cipher_mode_t cipher_mode);
void aes_input_bytes(const uint8_t* input_data, size_t input_data_len, aes_cipher_mode_t cipher_mode);

void aes_ecb128_hard_decrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb128_hard_encrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb192_hard_decrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb192_hard_encrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb256_hard_decrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb256_hard_encrypt(uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_cbc128_hard_decrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc128_hard_encrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc192_hard_decrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc192_hard_encrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc256_hard_decrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc256_hard_encrypt(cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_gcm128_hard_decrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm128_hard_encrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm192_hard_decrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm192_hard_encrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm256_hard_decrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm256_hard_encrypt(gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void gcm_get_tag(uint8_t *gcm_tag);

void aes_cfb128_hard_decrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb128_hard_encrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb192_hard_decrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb192_hard_encrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb256_hard_decrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb256_hard_encrypt(cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_ofb128_hard_decrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb128_hard_encrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb192_hard_decrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb192_hard_encrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb256_hard_decrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb256_hard_encrypt(ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_ecb128_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb128_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb192_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb192_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb256_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ecb256_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_cbc128_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc128_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc192_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc192_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc256_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cbc256_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_gcm128_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm128_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm192_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm192_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm256_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);
void aes_gcm256_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag);

void aes_cfb128_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb128_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb192_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb192_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb256_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_cfb256_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

void aes_ofb128_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb128_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb192_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb192_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb256_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);
void aes_ofb256_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data);

#endif
