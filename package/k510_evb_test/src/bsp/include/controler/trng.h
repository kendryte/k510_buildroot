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
#ifndef PUF_TRNG_H
#define PUF_TRNG_H
#include <stdint.h>

#define PUF_REGISTER_ADDR               (OTP_BASE_ADDR + 0xc200)

typedef struct _puf
{
    volatile uint32_t puf_reg_enable_addr;
    volatile uint32_t puf_reg_mode_addr;
    volatile uint32_t puf_reg_mode_en_addr;
    volatile uint32_t puf_reg_user_mode_only_addr;
    volatile uint32_t puf_reg_test_row_addr;
    volatile uint32_t puf_reg_mode_sta_addr;
    volatile uint32_t puf_reg_ip_lp_state_addr;
    volatile uint32_t puf_reg_trng_output_addr;
    volatile uint32_t puf_reg_trng_output_valid_addr;
    volatile uint32_t puf_reg_auto_repair_addr;
    volatile uint32_t puf_reg_quality_check_addr;
    volatile uint32_t puf_reg_enrollment_addr;
    volatile uint32_t puf_reg_uid_zeroization_addr;
    volatile uint32_t puf_reg_test_mode_lock_addr;
    volatile uint32_t puf_reg_puf_lock_addr;
    volatile uint32_t puf_reg_shuffle_read_addr;
    volatile uint32_t puf_reg_shuffle_write_addr;
    volatile uint32_t puf_reg_mode_check_error_addr;
    volatile uint32_t puf_reg_puf_en_addr;
    volatile uint32_t puf_reg_pif_en_addr;
    volatile uint32_t puf_reg_ptc_en_addr;
    volatile uint32_t puf_reg_pas_en_addr;
    volatile uint32_t puf_reg_palarmb_addr;
    volatile uint32_t puf_reg_mode_check_en_addr;
    volatile uint32_t puf_reg_mode_check_out_addr;
    volatile uint32_t puf_reg_trng_lp_en_addr;
    volatile uint32_t puf_reg_data_tamper_addr;
    volatile uint32_t puf_reg_pgm_wrerrflag_addr;
    volatile uint32_t puf_reg_pgm_wrerrdata_addr;
    volatile uint32_t puf_reg_pgm_wrerraddr_addr;
    volatile uint32_t puf_reg_pgm_busy_addr;
}puf_t;

typedef enum _puf_mode
{
    PUF_REG_MODE_IDLE                   = 0x00,                
    PUF_REG_MODE_STANDBY                = 0x01,
    PUF_REG_MODE_DEEP_STANDBY           = 0x02,
    PUF_REG_MODE_READ                   = 0x04,
    PUF_REG_MODE_PROGRAM                = 0x08,
    PUF_REG_MODE_TRNG_OUTPUT            = 0x10,
    PUF_REG_MODE_UID_ZEROIZATION_READ   = 0x20,
    PUF_REG_MODE_OFF_MARGIN_READ        = 0x80,
    PUF_REG_MODE_ON_MARGIN_READ         = 0x81,
    PUF_REG_MODE_AUTOREPAIR_READ        = 0x82,
    PUF_REG_MODE_PUF_QUALITY_CHECK      = 0x84,
    PUF_REG_MODE_PUF_ENROLLMENT         = 0x90,
    PUF_REG_MODE_TEST_MODE_LOCK         = 0x91,
    PUF_REG_MODE_PUF_LOCK               = 0x92,
    PUF_REG_MODE_SHUFFLE_READ_ENABLE    = 0x94,
    PUF_REG_MODE_SHUFFLE_WRITE_ENABLE   = 0x98
} puf_mode_t;

#define PUF_REG_ENABLE_ENABLE              0x00000001U
#define PUF_REG_ENABLE_DISABLE             0x00000000U

#define PUF_REG_MODE_EN_ENABLE              0x00000001U
#define PUF_REG_MODE_EN_DISABLE             0x00000000U

#define PUF_REG_PGM_BUSY                    0x00000001U
#define PUF_REG_PGM_READY                   0x00000000U

#define PUF_REG_TRNG_LP_ENABLE              0x00000001U
#define PUF_REG_TRNG_LP_DISABLE             0x00000000U


/**
 * @brief       Check programming status and errors
 *
 * @return      0:success
 *              -1:fail 
 */
int check_pgm_busy_error();

/**
 * @brief       Initialization mode register
 *
 * @param[in]   puf_mode    register mode
 * 
 * @return      0:success
 *              -1:fail 
 */
int puf_init(puf_mode_t puf_mode);

/**
 * @brief       Initialize low power mode
 *
 * @return      0:success
 *              -1:fail 
 */
int lp_puf_init();

/**
 * @brief       Disabled the puf
 *
 * @return      0:success
 *              -1:fail 
 */
int puf_disable();

/**
 * @brief       Check whether the value of TRNG is valid 
 *
 * @return      0:success
 *              -1:fail 
 */
int check_trng_valid();

/**
 * @brief       return trng number
 *
 * @return      trng number
 *               
 */
uint32_t get_trng();

/**
 * @brief       Enable trng lp mode 
 *
 * @return      0:success
 *              -1:fail 
 */
int trng_lp_en();

#endif