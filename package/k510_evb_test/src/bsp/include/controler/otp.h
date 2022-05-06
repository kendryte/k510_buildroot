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
#ifndef __OTP_H__
#define __OTP_H__

#include <stdint.h>
#include <stdbool.h>
#include "platform.h"

/* otp controller */
#define OTP_CONTROLLER_BASE_ADDR (OTP_BASE_ADDR+0x8000)

#define OTP_DISABLE             0x0
#define OTP_ENABLE              0x1

#define OTP_MODE_STANDBY        0x0
#define OTP_MODE_STANDBY_DEP    0x2
#define OTP_MODE_READ           0x4
#define OTP_MODE_PROGRAM        0x8
    /* for test mode */
#define OTP_MODE_CHECK_INIT     0x10     /* check init data */
#define OTP_MODE_CHECK_PROMGRAM 0x20     /* check program data */
#define OTP_MODE_INIT_BUSY      0x80     /* init busy */

#define OTP_PROGRAM_SUCCESS     0x1
#define OTP_PROGRAM_PROCESS     0x0

#define OTP_NEED_NOTHING_INIT   0x0
#define OTP_INIT_PROCESS        0x2
#define OTP_INIT_SUCCESS        0x3

typedef enum
{
    OTP_SEL_AES,
    OTP_SEL_SHA256,
}OTP_SEL_CRYPTER_E;

typedef enum
{
    OTP_SEL_KEY_0,
    OTP_SEL_KEY_1,
    OTP_SEL_KEY_MAX
}OTP_SEL_KEY_E;

typedef struct
{
    /* read write register */
    volatile uint32_t enable;               /* 0x00 enable register, we should set enable register before modify mode register */
    volatile uint32_t mode;                 /* 0x04 otp mode register */
    volatile uint32_t test_row;             /* 0x08 test row enable register */

    /* read only register */
    volatile uint32_t mode_status;          /* 0x0c mode read register */
    volatile uint32_t write_ready;          /* 0x10 write ready address */
    volatile uint32_t program_err_flag;     /* 0x14 program error flag */
    volatile uint32_t program_err_addr;     /* 0x18 program error addr */
    volatile uint32_t program_err_data;     /* 0x1c program error data */
    volatile uint32_t init_done;            /* 0x20 otp initial done flag */

    /* read write register */
    volatile uint32_t aes_sha256_key_sel;   /* 0x24 aes key select */
}__attribute__((packed, aligned(4))) OTP_CTRL_S;

/* otp space */
#define OTP_DEFUALT_WORD_VALUE                  (0xffffffff)
/* otp total space */
#define OTP_TOTAL_SPACE_BYTES                   (32*1024)

/* 1K space */
#define OTP_BLOCK_DATA_1K_NUM                   (29)
#define OTP_BLOCK_DATA_1K_BYTES                 (1024)
#define OTP_BLOCK_DATA_1K_ADDR(n)               (OTP_BASE_ADDR+OTP_BLOCK_DATA_1K_BYTES*n)

/* 256 bytes space*/
#define OTP_BLOCK_DATA_256_NUM                  (4)
#define OTP_BLOCK_DATA_256_BYTES                (256)
#define OTP_BLOCK_DATA_256_ADDR(n)              (OTP_BLOCK_DATA_1K_ADDR(OTP_BLOCK_DATA_1K_NUM) + OTP_BLOCK_DATA_256_BYTES*n)

/* 128 bytes space*/
#define OTP_BLOCK_DATA_128_NUM                  (5)
#define OTP_BLOCK_DATA_128_BYTES                (128)
#define OTP_BLOCK_DATA_128_ADDR(n)              (OTP_BLOCK_DATA_256_ADDR(OTP_BLOCK_DATA_256_NUM)+OTP_BLOCK_DATA_128_BYTES*n)

/* product info */
#define OTP_BLOCK_PRODUCT_INFO_NUM              (4)
#define OTP_BLOCK_PRODUCT_INFO_BYTES            (16)
#define OTP_BLOCK_PRODUCT_INFO_ADDR(n)          (OTP_BLOCK_DATA_128_ADDR(OTP_BLOCK_DATA_128_NUM) + OTP_BLOCK_PRODUCT_INFO_BYTES*n)

/* patch info */
#define OTP_BLOCK_PATCH_NUM                     (3)
#define OTP_BLOCK_PATCH_CODE_BYTES              (4)
#define OTP_BLOCK_PATCH_LEN_BYTES               (4)
#define OTP_BLOCK_PATCH_SIGN_BYTES              (32)
#define OTP_BLOCK_PATCH_CODE_ADDR(n)            (OTP_BLOCK_PRODUCT_INFO_ADDR(OTP_BLOCK_PRODUCT_INFO_NUM) + \
                                                (OTP_BLOCK_PATCH_CODE_BYTES+OTP_BLOCK_PATCH_LEN_BYTES+OTP_BLOCK_PATCH_SIGN_BYTES)*n)
#define OTP_BLOCK_PATCH_LEN_ADDR(n)             (OTP_BLOCK_PATCH_CODE_ADDR(n) + OTP_BLOCK_PATCH_CODE_BYTES)
#define OTP_BLOCK_PATCH_SIGN_ADDR(n)            (OTP_BLOCK_PATCH_LEN_ADDR(n) + OTP_BLOCK_PATCH_LEN_BYTES)

/* iomux debug info */
#define OTP_BLOCK_UART_SELECT_BYTES             (4)
#define OTP_BLOCK_UART_RX_PIN_BYTES             (4)
#define OTP_BLOCK_UART_TX_PIN_BYTES             (4)
#define OTP_BLOCK_UART_SELECT_ADDR              (OTP_BLOCK_PATCH_CODE_ADDR(OTP_BLOCK_PATCH_NUM))
#define OTP_BLOCK_UART_RX_PIN_ADDR              (OTP_BLOCK_UART_SELECT_ADDR+OTP_BLOCK_UART_SELECT_BYTES)
#define OTP_BLOCK_UART_TX_PIN_ADDR              (OTP_BLOCK_UART_RX_PIN_ADDR+OTP_BLOCK_UART_RX_PIN_BYTES)

/* reserved 0 */
#define OTP_BLOCK_RESERVED_0_BYTES              (12)
#define OTP_BLOCK_RESERVED_0_ADDR               (OTP_BLOCK_UART_TX_PIN_ADDR+OTP_BLOCK_UART_TX_PIN_BYTES)

/* EMMC/SPI0 data line mode select */
#define OTP_BLOCK_SPI0_SDIO0_LINE_BYTES         (4)
#define OTP_BLOCK_SPI0_SDIO0_LINE_ADDR          (OTP_BLOCK_RESERVED_0_ADDR+OTP_BLOCK_RESERVED_0_BYTES)

/* reserved 1 */
#define OTP_BLOCK_RESERVED_1_BYTES              (4)
#define OTP_BLOCK_RESERVED_1_ADDR               (OTP_BLOCK_SPI0_SDIO0_LINE_ADDR+OTP_BLOCK_SPI0_SDIO0_LINE_BYTES)

/* sha256 sign */
#define OTP_BLOCK_SHA256_SIGN_BYTES             (32)
#define OTP_BLOCK_SHA256_SIGN_ADDR              (OTP_BLOCK_RESERVED_1_ADDR+OTP_BLOCK_RESERVED_1_BYTES)

/* sha256 default hash value*/
#define OTP_BLOCK_SHA256_HASH_NUM               (2)
#define OTP_BLOCK_SHA256_HASH_BYTES             (32)
#define OTP_BLOCK_SHA256_HASH_ADDR(n)           (OTP_BLOCK_SHA256_SIGN_ADDR+OTP_BLOCK_SHA256_SIGN_BYTES + OTP_BLOCK_SHA256_HASH_BYTES*n)

/* aes */
#define OTP_BLOCK_AES_KEY_NUM                   (2)
#define OTP_BLOCK_AES_KEY_BYTES                 (32)
#define OTP_BLOCK_AES_KEY_ADDR(n)               (OTP_BLOCK_SHA256_HASH_ADDR(OTP_BLOCK_SHA256_HASH_NUM) + OTP_BLOCK_AES_KEY_BYTES*n)

/* reserved for align*/
#define OTP_BLOCK_RESERVED_2_BYTES              (200)
#define OTP_BLOCK_RESERVED_2_ADDR               (OTP_BLOCK_AES_KEY_ADDR(OTP_BLOCK_AES_KEY_NUM))

/* rsa2048 key1 */
#define OTP_BLOCK_RSA2048_KEY0_BYTES            (64)
#define OTP_BLOCK_RSA2048_KEY0_ADDR             (OTP_BLOCK_RESERVED_2_ADDR + OTP_BLOCK_RESERVED_2_BYTES)

/* rsa2048 key2 */
#define OTP_BLOCK_RSA2048_KEY1_BYTES            (256)
#define OTP_BLOCK_RSA2048_KEY1_ADDR             (OTP_BLOCK_RSA2048_KEY0_ADDR + OTP_BLOCK_RSA2048_KEY0_BYTES)
/* end: 0x7DFF */

/* protect info */
typedef enum
{
    OTP_BLOCK_DATA_1K_0,
    OTP_BLOCK_DATA_1K_1,
    OTP_BLOCK_DATA_1K_2,
    OTP_BLOCK_DATA_1K_3,
    OTP_BLOCK_DATA_1K_4,
    OTP_BLOCK_DATA_1K_5,
    OTP_BLOCK_DATA_1K_6,
    OTP_BLOCK_DATA_1K_7,
    OTP_BLOCK_DATA_1K_8,
    OTP_BLOCK_DATA_1K_9,
    OTP_BLOCK_DATA_1K_10,
    OTP_BLOCK_DATA_1K_11,
    OTP_BLOCK_DATA_1K_12,
    OTP_BLOCK_DATA_1K_13,
    OTP_BLOCK_DATA_1K_14,
    OTP_BLOCK_DATA_1K_15,
    OTP_BLOCK_DATA_1K_16,
    OTP_BLOCK_DATA_1K_17,
    OTP_BLOCK_DATA_1K_18,
    OTP_BLOCK_DATA_1K_19,
    OTP_BLOCK_DATA_1K_20,
    OTP_BLOCK_DATA_1K_21,
    OTP_BLOCK_DATA_1K_22,
    OTP_BLOCK_DATA_1K_23,
    OTP_BLOCK_DATA_1K_24,
    OTP_BLOCK_DATA_1K_25,
    OTP_BLOCK_DATA_1K_26,
    OTP_BLOCK_DATA_1K_27,
    OTP_BLOCK_DATA_1K_28,
    OTP_BLOCK_DATA_256_0,
    OTP_BLOCK_DATA_256_1,
    OTP_BLOCK_DATA_256_2,
    OTP_BLOCK_DATA_256_3,
    OTP_BLOCK_DATA_128_0,
    OTP_BLOCK_DATA_128_1,
    OTP_BLOCK_DATA_128_2,
    OTP_BLOCK_DATA_128_3,
    OTP_BLOCK_DATA_128_4,
    OTP_BLOCK_PRODUCT_INFO0,
    OTP_BLOCK_PRODUCT_INFO1,
    OTP_BLOCK_PRODUCT_INFO2,
    OTP_BLOCK_PRODUCT_INFO3,
    OTP_BLOCK_PATCH_0,
    OTP_BLOCK_PATCH_1,
    OTP_BLOCK_PATCH_2,
    OTP_BLOCK_UART_INFO,
    OTP_BLOCK_RESERVED_0,
    OTP_BLOCK_SPI0_SDIO0_LINE,
    OTP_BLOCK_RESERVED_1,
    OTP_BLOCK_SHA256_SIGN,
    OTP_BLOCK_SHA256_HASH0,
    OTP_BLOCK_SHA256_HASH1,
    OTP_BLOCK_AES_KEY0,
    OTP_BLOCK_AES_KEY1,
    OTP_BLOCK_RESERVED_2,
    OTP_BLOCK_RSA2048_KEY0,
    OTP_BLOCK_RSA2048_KEY1,
    OTP_BLOCK_BLOCK_MAX,
}OTP_BLOCK_E;

/* write protect bits */
typedef struct
{
    volatile uint32_t   otp_block_data_1k[OTP_BLOCK_DATA_1K_NUM];               /* 29 */
    volatile uint32_t   otp_block_data_256[OTP_BLOCK_DATA_256_NUM];             /* 4 */
    volatile uint32_t   opt_block_data_128[OTP_BLOCK_DATA_128_NUM];             /* 5 */
    volatile uint32_t   otp_block_product_info[OTP_BLOCK_PRODUCT_INFO_NUM];     /* 4 */
    volatile uint32_t   otp_block_patch[OTP_BLOCK_PATCH_NUM];                   /* 3 */
    volatile uint32_t   otp_block_uart_info;                                    /* 1 */
    volatile uint32_t   otp_block_reserved_0;                                   /* 1 */
    volatile uint32_t   otp_block_spi0_sdio0_line;    /* for emmc/flash startup data lines */ /*1*/
    volatile uint32_t   otp_block_reserved_1;                                   /* 1 */
    volatile uint32_t   otp_block_sha256_sign;                                  /* 1 */
    volatile uint32_t   otp_block_sha256_hash[OTP_BLOCK_SHA256_HASH_NUM];       /* 2 */
    volatile uint32_t   otp_block_aes_key[OTP_BLOCK_AES_KEY_NUM];               /* 2 */
    volatile uint32_t   otp_block_reserved_2;                                   /* 1 */
    volatile uint32_t   otp_block_rsa2048_key0;                                 /* 1 */ /*57 e3*/
    volatile uint32_t   otp_block_rsa2048_key1;                                 /* 1 */ 
    volatile uint32_t   otp_block_reserved_3;                                   /* 1 */ /* e7*/
}__attribute__((packed, aligned(4))) OTP_WRITE_PROTECT_S;

/* write protect 32bits align */
#define OTP_WRITE_PROTECT_ADDR                  (OTP_BLOCK_RSA2048_KEY1_ADDR + OTP_BLOCK_RSA2048_KEY1_BYTES)

typedef struct
{
    //volatile uint32_t   otp_rsa2048_key[OTP_BLOCK_RSA2048_KEY_NUM];/*removed rsa key read protect, public key */
    volatile uint32_t   otp_sha256_hash[OTP_BLOCK_SHA256_HASH_NUM];
    volatile uint32_t   otp_aes_key[OTP_BLOCK_AES_KEY_NUM];
    volatile uint32_t   otp_reserved[2];
}__attribute__((packed, aligned(4))) OTP_READ_PROTECT_S;


#define OTP_READ_PROTECT_ADDR                   (OTP_WRITE_PROTECT_ADDR+sizeof(OTP_WRITE_PROTECT_S))

/* otp flags */
typedef enum
{
    OTP_FUNC_JTAG_DISABLE                       = 0,    /* 32'b0 for disable */
    OTP_FUNC_I2C2AXI_DISABLE                    = 1,    /* 32'b0 for disable */
    OTP_FUNC_TEST_EN_DISABLE                    = 2,    /* 32'b0 for disable */
    OTP_FUNC_FIRMWARE_AES_DECRYPT_DISABLE       = 3,    /* 32'b0 for disable */
    OTP_FUNC_PUF_TEST_MODE_DISABLE              = 4,    /* 32'b0 for disable */
    OTP_FUNC_REPAIR_MODE_ENABLE                 = 5,
    OTP_FUNC_ISP_DISABLE                        = 6,    /* 32'b0 for disable */
    OTP_FUNC_FIRMWARE_TRUST_SHA256_CHECKSUM     = 7,    /* !!!!32'b0 for enable!!!! */
    OTP_FUNC_TURBO_MODE_ENABLE                  = 8,    /* !!!!32'b0 for enable!!!! */
    OTP_FUNC_DEBUG_UART_DISABLE                 = 9,    /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_0                       = 10,    /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_1                       = 11,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_2                       = 12,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_3                       = 13,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_4                       = 14,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_5                       = 15,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_6                       = 16,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_7                       = 17,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_8                       = 18,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_9                       = 19,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_10                      = 20,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_11                      = 21,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_12                      = 22,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_13                      = 23,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_14                      = 24,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_15                      = 25,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_16                      = 26,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_17                      = 27,   /* 32'b0 for disable */
    OTP_FUNC_ROLLBACK_V_18                      = 28,   /* 32'b0 for disable */
    OTP_FUNC_MAX                                = 29,   /* 32'b0 for disable */
} OTP_FUNC_E;

typedef struct
{
    volatile uint32_t otp_func_flag[OTP_FUNC_MAX];
}OTP_FUNC_S;

#define OTP_FUNC_ADDR                           (OTP_READ_PROTECT_ADDR+sizeof(OTP_READ_PROTECT_S))

typedef enum
{
    OTP_BYPASS_STATUS                   = 0,
    OTP_MAX_STATUS                      = 1,
}OTP_STATUS_E;

typedef struct
{
    uint32_t otp_function_status[OTP_FUNC_MAX];
}__attribute__((packed, aligned(4))) OTP_FUNCTION_STATUS_S;

bool otp_get_status(OTP_STATUS_E eStatus);
bool otp_read_word(volatile uint32_t addr, uint32_t *buff, uint32_t len);
bool otp_write_word(uint32_t addr, uint32_t *buff, uint32_t len);
bool otp_get_block_write_protect(OTP_BLOCK_E block);
bool otp_set_block_write_protect(OTP_BLOCK_E block);
bool otp_get_block_read_protect(OTP_BLOCK_E block);
bool otp_set_block_read_protect(OTP_BLOCK_E block);
bool otp_get_func_flag(OTP_FUNC_E eFunc);
bool otp_set_func_flag(OTP_FUNC_E eFunc);
void otp_select_key(OTP_SEL_CRYPTER_E crypter, OTP_SEL_KEY_E key);
void otp_reset(void);

#endif
