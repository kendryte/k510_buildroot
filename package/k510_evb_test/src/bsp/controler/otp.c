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
#include "core_v5.h"
#include "platform.h"
#include "sleep.h"
#include "sysctl_boot.h"
#include "sysctl_rst.h"
#include "otp.h"

volatile OTP_CTRL_S *otp_ctrl = (volatile OTP_CTRL_S *)(OTP_CONTROLLER_BASE_ADDR);

volatile OTP_WRITE_PROTECT_S *otp_write_protect = (volatile OTP_WRITE_PROTECT_S *)(OTP_WRITE_PROTECT_ADDR);
volatile OTP_READ_PROTECT_S *otp_read_protect = (volatile OTP_READ_PROTECT_S *)(OTP_READ_PROTECT_ADDR);
volatile OTP_FUNC_S *otp_func_enable_disable = (volatile OTP_FUNC_S *)(OTP_FUNC_ADDR);

bool otp_get_status(OTP_STATUS_E eStatus)
{
    if(OTP_BYPASS_STATUS == eStatus)
    {
        return sysctl_boot_get_otp_bypass();
    }
    else
    {
        return false;
    }
}

bool otp_read_word(volatile uint32_t addr, uint32_t *buff, uint32_t len)
{
    uint32_t wait_us;

    if(true == otp_get_status(OTP_BYPASS_STATUS))
    {
        return false;
    }

    /* otp enable */
    otp_ctrl->enable = OTP_ENABLE;
    otp_ctrl->test_row = 0;
    wait_us = 0;
    while(1)
    {
        if((OTP_NEED_NOTHING_INIT == otp_ctrl->init_done) || (OTP_INIT_SUCCESS == otp_ctrl->init_done))
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                otp_ctrl->enable = OTP_DISABLE;
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    /* set otp read */
    otp_ctrl->mode = OTP_MODE_READ;
    wait_us = 0;
    while(1)
    {
        if(OTP_MODE_READ == otp_ctrl->mode_status)
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                wait_us = 0;
                otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
                while(1)
                {
                    if((OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status) || (wait_us++ > 2000))
                    {
                        break;
                    }
                    else
                    {
                        usleep(1);
                    }
                }
                otp_ctrl->enable = OTP_DISABLE;
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    for(int i = 0; i < len; i ++)
    {
        buff[i] = *(uint32_t *)(long)(addr + 4*i);
    }
    
    otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
    wait_us = 0;
    while(1)
    {
        if(OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status)
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                otp_ctrl->enable = OTP_DISABLE;
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    otp_ctrl->enable = OTP_DISABLE;
    return true;
}

bool otp_write_word(uint32_t addr, uint32_t *buff, uint32_t len)
{
    uint32_t wait_us;

    if(true == otp_get_status(OTP_BYPASS_STATUS))
    {
        return false;
    }
    /* otp enable */
    otp_ctrl->enable = OTP_ENABLE;
    otp_ctrl->test_row = 0;
    wait_us = 0;
    while(1)
    {
        if((OTP_NEED_NOTHING_INIT == otp_ctrl->init_done) || (OTP_INIT_SUCCESS == otp_ctrl->init_done))
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    /* set otp program */
    otp_ctrl->mode = OTP_MODE_PROGRAM;
    wait_us = 0;
    while(1)
    {
        if(OTP_MODE_PROGRAM == otp_ctrl->mode_status)
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                wait_us = 0;
                otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
                while(1)
                {
                    if((OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status) || (wait_us++ > 2000))
                    {
                        break;
                    }
                    else
                    {
                        usleep(1);
                    }
                }
                otp_ctrl->enable = OTP_DISABLE;
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    /* wait for program success*/
    for(int i = 0; i < len; i++)
    {
        /* wait for ready */
        wait_us = 0;
        while(1)
        {
            if(OTP_PROGRAM_SUCCESS == otp_ctrl->write_ready)
            {
                break;
            }
            else
            {
                if(wait_us++ > 2000)
                {
                    wait_us = 0;
                    otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
                    while(1)
                    {
                        if((OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status) || (wait_us++ > 2000))
                        {
                            break;
                        }
                        else
                        {
                            usleep(1);
                        }
                    }
                    otp_ctrl->enable = OTP_DISABLE;
                    return false;
                }
                else
                {
                    usleep(1);
                }
            }
        }

        /* write data */
        *(uint32_t *)(long)(addr + 4*i) = buff[i];

        /* wait for program success*/
        wait_us = 0;
        while(1)
        {
            if(OTP_PROGRAM_SUCCESS == otp_ctrl->write_ready)
            {
                break;
            }
            else
            {
                if(wait_us++ > 2000)
                {
                    wait_us = 0;
                    otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
                    while(1)
                    {
                        if((OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status) || (wait_us++ > 2000))
                        {
                            break;
                        }
                        else
                        {
                            usleep(1);
                        }
                    }
                    otp_ctrl->enable = OTP_DISABLE;
                    return false;
                }
                else
                {
                    usleep(1);
                }
            }
        }
    }
    
    otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
    wait_us = 0;
    while(1)
    {
        if(OTP_MODE_STANDBY_DEP == otp_ctrl->mode_status)
        {
            break;
        }
        else
        {
            if(wait_us++ > 2000)
            {
                otp_ctrl->enable = OTP_DISABLE;
                return false;
            }
            else
            {
                usleep(1);
            }
        }
    }

    otp_ctrl->enable = OTP_DISABLE;
    return true;
}

bool otp_get_block_write_protect(OTP_BLOCK_E block)
{
    uint32_t protect_flag = OTP_DEFUALT_WORD_VALUE;

    uint32_t protect_addr;

    if((block >= OTP_BLOCK_DATA_1K_0) && (block <= OTP_BLOCK_DATA_1K_28))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_data_1k[block - OTP_BLOCK_DATA_1K_0];
    }
    else if((block >= OTP_BLOCK_DATA_256_0) && (block <= OTP_BLOCK_DATA_256_3))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_data_256[block - OTP_BLOCK_DATA_256_0];
    }
    else if((block >= OTP_BLOCK_DATA_128_0) && (block <= OTP_BLOCK_DATA_128_4))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->opt_block_data_128[block - OTP_BLOCK_DATA_128_0];
    }
    else if((block >= OTP_BLOCK_PRODUCT_INFO0) && (block <= OTP_BLOCK_PRODUCT_INFO3))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_product_info[block - OTP_BLOCK_PRODUCT_INFO0];
    }
    else if((block >= OTP_BLOCK_PATCH_0) && (block <= OTP_BLOCK_PATCH_2))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_patch[block - OTP_BLOCK_PATCH_0];
    }
    else if(OTP_BLOCK_UART_INFO == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_uart_info;
    }
    else if(OTP_BLOCK_RESERVED_0 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_0;
    }
    else if(OTP_BLOCK_SPI0_SDIO0_LINE == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_spi0_sdio0_line;
    }
    else if(OTP_BLOCK_RESERVED_1 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_1;
    }
    else if(OTP_BLOCK_SHA256_SIGN == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_sha256_sign;
    }
    else if((block >= OTP_BLOCK_SHA256_HASH0) && (block <= OTP_BLOCK_SHA256_HASH1))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_sha256_hash[block - OTP_BLOCK_SHA256_HASH0];
    }
    else if((block >= OTP_BLOCK_AES_KEY0) && (block <= OTP_BLOCK_AES_KEY1))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_aes_key[block - OTP_BLOCK_AES_KEY0];
    }
    else if(OTP_BLOCK_RESERVED_2 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_2;
    }
    else if(block == OTP_BLOCK_RSA2048_KEY0)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_rsa2048_key0;
    }
    else if(block == OTP_BLOCK_RSA2048_KEY1)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_rsa2048_key1;
    }
    else
    {
        return false;
    }

    /* read error */
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    /* already write protect */
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool otp_set_block_write_protect(OTP_BLOCK_E block)
{
    uint32_t protect_flag = OTP_DEFUALT_WORD_VALUE;

    uint32_t protect_addr;

    if((block >= OTP_BLOCK_DATA_1K_0) && (block <= OTP_BLOCK_DATA_1K_28))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_data_1k[block - OTP_BLOCK_DATA_1K_0];
    }
    else if((block >= OTP_BLOCK_DATA_256_0) && (block <= OTP_BLOCK_DATA_256_3))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_data_256[block - OTP_BLOCK_DATA_256_0];
    }
    else if((block >= OTP_BLOCK_DATA_128_0) && (block <= OTP_BLOCK_DATA_128_4))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->opt_block_data_128[block - OTP_BLOCK_DATA_128_0];
    }
    else if((block >= OTP_BLOCK_PRODUCT_INFO0) && (block <= OTP_BLOCK_PRODUCT_INFO3))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_product_info[block - OTP_BLOCK_PRODUCT_INFO0];
    }
    else if((block >= OTP_BLOCK_PATCH_0) && (block <= OTP_BLOCK_PATCH_2))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_patch[block - OTP_BLOCK_PATCH_0];
    }
    else if(OTP_BLOCK_UART_INFO == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_uart_info;
    }
    else if(OTP_BLOCK_RESERVED_0 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_0;
    }
    else if(OTP_BLOCK_SPI0_SDIO0_LINE == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_spi0_sdio0_line;
    }
    else if(OTP_BLOCK_RESERVED_1 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_1;
    }
    else if(OTP_BLOCK_SHA256_SIGN == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_sha256_sign;
    }
    else if((block >= OTP_BLOCK_SHA256_HASH0) && (block <= OTP_BLOCK_SHA256_HASH1))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_sha256_hash[block - OTP_BLOCK_SHA256_HASH0];
    }
    else if((block >= OTP_BLOCK_AES_KEY0) && (block <= OTP_BLOCK_AES_KEY1))
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_aes_key[block - OTP_BLOCK_AES_KEY0];
    }
    else if(OTP_BLOCK_RESERVED_2 == block)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_reserved_2;
    }
    else if(block == OTP_BLOCK_RSA2048_KEY0)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_rsa2048_key0;
    }
    else if(block == OTP_BLOCK_RSA2048_KEY1)
    {
        protect_addr = (uint32_t)(long)&otp_write_protect->otp_block_rsa2048_key1;
    }
    else
    {
        return false;
    }

    /* read error */
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    /* already write protect */
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }

    /* write protect */
    protect_flag = 0;
    (void)otp_write_word(protect_addr,&protect_flag,1);
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool otp_get_block_read_protect(OTP_BLOCK_E block)
{
    uint32_t protect_flag = OTP_DEFUALT_WORD_VALUE;
    uint32_t protect_addr;

    if(block == OTP_BLOCK_SHA256_HASH0)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_sha256_hash[0];
    else if(block == OTP_BLOCK_SHA256_HASH1)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_sha256_hash[1];
    else if(block == OTP_BLOCK_AES_KEY0)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_aes_key[0];
    else if(block == OTP_BLOCK_AES_KEY1)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_aes_key[1];
    else
        return false;

    /* read error */
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    /* already write protect */
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool otp_set_block_read_protect(OTP_BLOCK_E block)
{
    uint32_t protect_flag = OTP_DEFUALT_WORD_VALUE;
    uint32_t protect_addr;

    if(block == OTP_BLOCK_SHA256_HASH0)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_sha256_hash[0];
    else if(block == OTP_BLOCK_SHA256_HASH1)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_sha256_hash[1];
    else if(block == OTP_BLOCK_AES_KEY0)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_aes_key[0];
    else if(block == OTP_BLOCK_AES_KEY1)
        protect_addr = (uint32_t)(long)&otp_read_protect->otp_aes_key[1];
    else
        return false;

    /* read error */
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    /* already write protect */
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }

    /* write protect */
    protect_flag = ~OTP_DEFUALT_WORD_VALUE;
    (void)otp_write_word(protect_addr,&protect_flag,1);
    protect_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(protect_addr,&protect_flag,1))
    {
        return false;
    }
    if(OTP_DEFUALT_WORD_VALUE != protect_flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool otp_get_func_flag(OTP_FUNC_E eFunc)
{
    uint32_t func_flag = OTP_DEFUALT_WORD_VALUE;
    uint32_t func_addr;
    
    if(eFunc >= OTP_FUNC_MAX)
    {
        return false;
    }

    func_addr = (uint32_t)(long)&otp_func_enable_disable->otp_func_flag[eFunc];

    if(true != otp_read_word(func_addr, &func_flag,1))
    {
        return false;
    }
    else
    {
        if(OTP_DEFUALT_WORD_VALUE != func_flag)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool otp_set_func_flag(OTP_FUNC_E eFunc)
{
    uint32_t func_flag = OTP_DEFUALT_WORD_VALUE;
    uint32_t func_addr;

    if(eFunc >= OTP_FUNC_MAX)
    {
        return false;
    }

    func_addr = (uint32_t)(long)&otp_func_enable_disable->otp_func_flag[eFunc];

    if(true != otp_read_word(func_addr,&func_flag,1))
    {
        return false;
    }

    if(OTP_DEFUALT_WORD_VALUE != func_flag)
    {
        return true;
    }

    func_flag = ~OTP_DEFUALT_WORD_VALUE;
    (void)otp_write_word(func_addr,&func_flag,1);

    func_flag = OTP_DEFUALT_WORD_VALUE;
    if(true != otp_read_word(func_addr,&func_flag,1))
    {
        return false;
    }
    if(OTP_DEFUALT_WORD_VALUE != func_flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void otp_select_key(OTP_SEL_CRYPTER_E crypter, OTP_SEL_KEY_E key)
{
    if(OTP_SEL_AES == crypter)
    {
        if(key == OTP_SEL_KEY_0)
        {
            otp_ctrl->aes_sha256_key_sel &= ~(1 << 0);
        }
        else
        {
            otp_ctrl->aes_sha256_key_sel |= (1 << 0);
        }
    }
    else if(OTP_SEL_SHA256 ==crypter)
    {
        if(key == OTP_SEL_KEY_0)
        {
            otp_ctrl->aes_sha256_key_sel &= ~(1 << 4);
        }
        else
        {
            otp_ctrl->aes_sha256_key_sel |= (1 << 4);
        }
    }
    else
    {

    }
}

void otp_reset(void)
{
    if(true == otp_get_status(OTP_BYPASS_STATUS))
    {
        return;
    }
    otp_ctrl->mode = OTP_MODE_STANDBY_DEP;
    while(otp_ctrl->mode_status != OTP_MODE_STANDBY_DEP)
    {
    }
    otp_ctrl->enable = OTP_DISABLE;
    usleep(100);
    sysctl_reset(SYSCTL_RESET_OTP);
}
