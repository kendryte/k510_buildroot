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
#include "platform.h"
#include "aes.h"

volatile aes_t *const aes = (volatile aes_t *)AES_BASE_ADDR;

static void aes_clk_init()
{
    // sysctl_clock_enable(SYSCTL_CLOCK_AES);
    // sysctl_reset(SYSCTL_RESET_AES);
}

static void aes_write_aad(uint32_t aad_data)
{
    aes->aes_aad_data = aad_data;
}

static void aes_write_text(uint32_t text_data)
{
    aes->aes_text_data = text_data;
}

static void gcm_write_tag(uint32_t *tag)
{
    aes->gcm_in_tag[0] = tag[3];
    aes->gcm_in_tag[1] = tag[2];
    aes->gcm_in_tag[2] = tag[1];
    aes->gcm_in_tag[3] = tag[0];
}

static uint32_t aes_get_data_in_flag(void)
{
    return aes->data_in_flag;
}

static uint32_t aes_get_data_out_flag(void)
{
    return aes->data_out_flag;
}

static uint32_t gcm_get_tag_in_flag(void)
{
    return aes->tag_in_flag;
}

static uint32_t aes_read_out_data(void)
{
    return aes->aes_out_data;
}

static uint32_t gcm_get_tag_chk(void)
{
    return aes->tag_chk;
}

static void gcm_clear_chk_tag(void)
{
    aes->tag_clear = 0;
}

static uint32_t gcm_check_tag(uint32_t *gcm_tag)
{
    while(!gcm_get_tag_in_flag())
        ;
    gcm_write_tag(gcm_tag);
    while(!gcm_get_tag_chk())
        ;
    if(gcm_get_tag_chk() == 0x2)
    {
        gcm_clear_chk_tag();
        return 1;
    } else
    {
        gcm_clear_chk_tag();
        return 0;
    }
}

void aes_input_bytes(const uint8_t *input_data, size_t input_data_len, aes_cipher_mode_t cipher_mode)
{
    size_t padding_len, uint32_num, uint8_num, remainder, i;
    uint32_t uint32_data;
    uint8_t uint8_data[4] = {0};

    padding_len = ((input_data_len + 15) / 16) * 16;
    uint32_num = input_data_len / 4;
    for(i = 0; i < uint32_num; i++)
    {
        uint32_data = *((uint32_t *)(&input_data[i * 4]));
        while(!aes_get_data_in_flag())
            ;
        aes_write_text(uint32_data);
    }
    uint8_num = 4 * uint32_num;
    remainder = input_data_len % 4;
    if(remainder)
    {
        switch(remainder)
        {
            case 1:
                uint8_data[0] = input_data[uint8_num];
                break;
            case 2:
                uint8_data[0] = input_data[uint8_num];
                uint8_data[1] = input_data[uint8_num + 1];
                break;
            case 3:
                uint8_data[0] = input_data[uint8_num];
                uint8_data[1] = input_data[uint8_num + 1];
                uint8_data[2] = input_data[uint8_num + 2];
                break;
            default:
                break;
        }
        uint32_data = *((uint32_t *)(&uint8_data[0]));
        while(!aes_get_data_in_flag())
            ;
        aes_write_text(uint32_data);
    }
    if((cipher_mode == AES_ECB) || (cipher_mode == AES_CBC))
    {
        uint32_num = (padding_len - input_data_len) / 4;
        for(i = 0; i < uint32_num; i++)
        {
            while(!aes_get_data_in_flag())
                ;
            aes_write_text(0);
        }
        uint32_num = padding_len / 4;
    }
}

static void aes_process_with_dma(dma_ch_t channel, uint8_t* input_data, uint32_t input_len, uint8_t* output_data, uint32_t output_len, aes_cipher_mode_t cipher_mode)
{
    aes->dma_sel = 1;
    peri_dma_cfg_t cfg = {
        .channel = channel,
        .dev_sel = AES_RX,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = FIXED_REG_ADDRESS,
        .buswidth = FOUR_BYTE,
        .dev_burst_len = 0,
        .line_size = output_len,
        .saddr = (void*)(&aes->aes_out_data),
        .daddr = (void*)output_data,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&cfg);
    peri_dma_start(channel);
    aes_input_bytes(input_data, input_len, cipher_mode);
    peri_dma_wait_done_or_timeout(channel);
    aes->dma_sel = 0;
}

static void process_less_80_bytes(uint8_t *input_data, uint8_t *output_data, size_t input_data_len, aes_cipher_mode_t cipher_mode)
{
    size_t padding_len, uint32_num, uint8_num, remainder, i;
    uint32_t uint32_data;
    uint8_t uint8_data[4] = {0};

    padding_len = ((input_data_len + 15) / 16) * 16;
    uint32_num = input_data_len / 4;
    for(i = 0; i < uint32_num; i++)
    {
        uint32_data = *((uint32_t *)(&input_data[i * 4]));
        while(!aes_get_data_in_flag())
            ;
        aes_write_text(uint32_data);
    }
    uint8_num = 4 * uint32_num;
    remainder = input_data_len % 4;
    if(remainder)
    {
        switch(remainder)
        {
            case 1:
                uint8_data[0] = input_data[uint8_num];
                break;
            case 2:
                uint8_data[0] = input_data[uint8_num];
                uint8_data[1] = input_data[uint8_num + 1];
                break;
            case 3:
                uint8_data[0] = input_data[uint8_num];
                uint8_data[1] = input_data[uint8_num + 1];
                uint8_data[2] = input_data[uint8_num + 2];
                break;
            default:
                break;
        }
        uint32_data = *((uint32_t *)(&uint8_data[0]));
        while(!aes_get_data_in_flag())
            ;
        aes_write_text(uint32_data);
    }
    if((cipher_mode == AES_ECB) || (cipher_mode == AES_CBC))
    {
        uint32_num = (padding_len - input_data_len) / 4;
        for(i = 0; i < uint32_num; i++)
        {
            while(!aes_get_data_in_flag())
                ;
            aes_write_text(0);
        }
        uint32_num = padding_len / 4;
    }
    for(i = 0; i < uint32_num; i++)
    {
        while(!aes_get_data_out_flag())
            ;
        *((uint32_t *)(&output_data[i * 4])) = aes_read_out_data();
    }
    if((cipher_mode == AES_GCM) && (remainder))
    {
        while(!aes_get_data_out_flag())
            ;
        *((uint32_t *)(&uint8_data[0])) = aes_read_out_data();
        switch(remainder)
        {
            case 1:
                output_data[uint32_num * 4] = uint8_data[0];
                break;
            case 2:
                output_data[uint32_num * 4] = uint8_data[0];
                output_data[(i * 4) + 1] = uint8_data[1];
                break;
            case 3:
                output_data[uint32_num * 4] = uint8_data[0];
                output_data[(i * 4) + 1] = uint8_data[1];
                output_data[(i * 4) + 2] = uint8_data[2];
                break;
            default:
                break;
        }
    }
}

void gcm_get_tag(uint8_t *gcm_tag)
{
    uint32_t uint32_tag;
    uint8_t i = 0;

    uint32_tag = aes->gcm_out_tag[3];
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 24) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 16) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 8) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag)&0xff);

    uint32_tag = aes->gcm_out_tag[2];
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 24) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 16) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 8) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag)&0xff);

    uint32_tag = aes->gcm_out_tag[1];
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 24) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 16) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 8) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag)&0xff);

    uint32_tag = aes->gcm_out_tag[0];
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 24) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 16) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag >> 8) & 0xff);
    gcm_tag[i++] = (uint8_t)((uint32_tag)&0xff);

    gcm_check_tag((uint32_t *)gcm_tag);
}

void aes_init(uint8_t *input_key, size_t input_key_len, uint8_t *iv, size_t iv_len, uint8_t *gcm_aad,
              aes_cipher_mode_t cipher_mode, aes_encrypt_sel_t encrypt_sel, size_t gcm_aad_len, size_t input_data_len)
{
    size_t remainder, uint32_num, uint8_num, i;
    uint32_t uint32_data;
    uint8_t uint8_data[4] = {0};
    size_t padding_len = input_data_len;
    aes_clk_init();
    if((cipher_mode == AES_ECB) || (cipher_mode == AES_CBC))
        padding_len = ((input_data_len + 15) / 16) * 16;
    aes->aes_endian |= 1;
    uint32_num = input_key_len / 4;
    for(i = 0; i < uint32_num; i++)
    {
        if(i < 4)
            aes->aes_key[i] = *((uint32_t *)(&input_key[input_key_len - (4 * i) - 4]));
        else
            aes->aes_key_ext[i - 4] = *((uint32_t *)(&input_key[input_key_len - (4 * i) - 4]));
    }

    uint32_num = iv_len / 4;
    for(i = 0; i < uint32_num; i++)
        aes->aes_iv[i] = *((uint32_t *)(&iv[iv_len - (4 * i) - 4]));

    aes->mode_ctl.kmode = input_key_len / 8 - 2; /* b'00:AES_128 b'01:AES_192 b'10:AES_256 b'11:RESERVED */
    aes->mode_ctl.cipher_mode = cipher_mode;
    aes->encrypt_sel = encrypt_sel;
    aes->gb_aad_num = gcm_aad_len - 1;
    aes->gb_pc_num = padding_len - 1;
    aes->gb_aes_en |= 1;

    if(cipher_mode == AES_GCM)
    {
        uint32_num = gcm_aad_len / 4;
        for(i = 0; i < uint32_num; i++)
        {
            uint32_data = *((uint32_t *)(&gcm_aad[i * 4]));
            while(!aes_get_data_in_flag())
                ;
            aes_write_aad(uint32_data);
        }
        uint8_num = 4 * uint32_num;
        remainder = gcm_aad_len % 4;
        if(remainder)
        {
            switch(remainder)
            {
                case 1:
                    uint8_data[0] = gcm_aad[uint8_num];
                    break;
                case 2:
                    uint8_data[0] = gcm_aad[uint8_num];
                    uint8_data[1] = gcm_aad[uint8_num + 1];
                    break;
                case 3:
                    uint8_data[0] = gcm_aad[uint8_num];
                    uint8_data[1] = gcm_aad[uint8_num + 1];
                    uint8_data[2] = gcm_aad[uint8_num + 2];
                    break;
                default:
                    break;
            }
            uint32_data = *((uint32_t *)(&uint8_data[0]));
            while(!aes_get_data_in_flag())
                ;
            aes_write_aad(uint32_data);
        }
    }
}

void aes_process(uint8_t *input_data, uint8_t *output_data, size_t input_data_len, aes_cipher_mode_t cipher_mode)
{
    size_t temp_len = 0;
    uint32_t i = 0;

    if(input_data_len >= 80)
    {
        for(i = 0; i < (input_data_len / 80); i++)
            process_less_80_bytes(&input_data[i * 80], &output_data[i * 80], 80, cipher_mode);
    }
    temp_len = input_data_len % 80;
    if(temp_len)
        process_less_80_bytes(&input_data[i * 80], &output_data[i * 80], temp_len, cipher_mode);
}

void aes_ecb128_hard_decrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_128, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_ECB);
}

void aes_ecb128_hard_encrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(input_key, AES_128, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_ECB);
}

void aes_ecb192_hard_decrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_192, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_ECB);
}

void aes_ecb192_hard_encrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(input_key, AES_192, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_ECB);
}

void aes_ecb256_hard_decrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_256, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_ECB);
}

void aes_ecb256_hard_encrypt(uint8_t *input_key, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(input_key, AES_256, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_ECB);
}

void aes_cbc128_hard_decrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_CBC);
}

void aes_cbc128_hard_encrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_CBC);
}

void aes_cbc192_hard_decrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_CBC);
}

void aes_cbc192_hard_encrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_CBC);
}

void aes_cbc256_hard_decrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process(input_data, output_data, padding_len, AES_CBC);
}

void aes_cbc256_hard_encrypt(cbc_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process(input_data, output_data, input_len, AES_CBC);
}

void aes_gcm128_hard_decrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm128_hard_encrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm192_hard_decrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm192_hard_encrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm256_hard_decrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm256_hard_encrypt(gcm_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process(input_data, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_cfb128_hard_decrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_cfb128_hard_encrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_cfb192_hard_decrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_cfb192_hard_encrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_cfb256_hard_decrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_cfb256_hard_encrypt(cfb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_CFB);
}

void aes_ofb128_hard_decrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ofb128_hard_encrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ofb192_hard_decrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ofb192_hard_encrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ofb256_hard_decrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ofb256_hard_encrypt(ofb_context_t *context, uint8_t *input_data, size_t input_len, uint8_t *output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0, input_len);
    aes_process(input_data, output_data, input_len, AES_OFB);
}

void aes_ecb128_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_128, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_ecb128_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_128, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_ecb192_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_192, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_ecb192_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_192, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_ecb256_hard_decrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_256, NULL, 0L, NULL, AES_ECB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_ecb256_hard_encrypt_dma(dma_ch_t channel, uint8_t* input_key, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(input_key, AES_256, NULL, 0L, NULL, AES_ECB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_ECB);
}

void aes_cbc128_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_cbc128_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_cbc192_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_cbc192_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_cbc256_hard_decrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_cbc256_hard_encrypt_dma(dma_ch_t channel, cbc_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    size_t padding_len = ((input_len + 15) / 16) * 16;
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CBC, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, padding_len, AES_CBC);
}

void aes_gcm128_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm128_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm192_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm192_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm256_hard_decrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_DECRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_gcm256_hard_encrypt_dma(dma_ch_t channel, gcm_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data, uint8_t *gcm_tag)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_96, context->gcm_aad,
             AES_GCM, AES_HARD_ENCRYPTION, context->gcm_aad_len, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_GCM);
    gcm_get_tag(gcm_tag);
}

void aes_cfb128_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_cfb128_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_cfb192_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_cfb192_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_cfb256_hard_decrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_cfb256_hard_encrypt_dma(dma_ch_t channel, cfb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_CFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_CFB);
}

void aes_ofb128_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}

void aes_ofb128_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_128, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}

void aes_ofb192_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}

void aes_ofb192_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_192, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}

void aes_ofb256_hard_decrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_DECRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}

void aes_ofb256_hard_encrypt_dma(dma_ch_t channel, ofb_context_t* context, uint8_t* input_data, size_t input_len, uint8_t* output_data)
{
    aes_init(context->input_key, AES_256, context->iv, IV_LEN_128, NULL, AES_OFB, AES_HARD_ENCRYPTION, 0L, input_len);
    aes_process_with_dma(channel, input_data, input_len, output_data, input_len, AES_OFB);
}