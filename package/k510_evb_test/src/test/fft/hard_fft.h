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
/**
 * @file
 * @brief      Fast Fourier transform (FFT) algorithm accelerator
 */

/*
 * NOTE: This file is automatic generated, do not edit directly.
 * Please edit the generator instead.
 */

#ifndef _DRIVER_HARD_FFT_H
#define _DRIVER_HARD_FFT_H

#include <stdint.h>
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct complex {
    float real;
    float imag;
} complex;

typedef struct {
    int16_t I1;
    int16_t R1;
    int16_t I2;
    int16_t R2;
} fft_data;

typedef struct {
    float I1;
    float R1;
} fft_data32;

enum fft_point_e {
    FFT_N512,
    FFT_N256,
    FFT_N128,
    FFT_N64,
};

enum fft_mode_e {
    IFFT_MODE,
    FFT_MODE,
};

typedef enum {
    RIRI,
    RESERVED,
    RRRR,
    RR_II,
} fft_input_mode_e;

typedef enum {
    INPUT_64BIT,
    INPUT_32BIT,
} fft_data_mode_e;
/**
 * @brief      FFT algorithm accelerator register
 *
 * @note       FFT algorithm accelerator register table
 *
 * | Offset    | Name           | Description                         |
 * |-----------|----------------|-------------------------------------|
 * | 0x00      | fft_input_fifo | input data fifo                     |
 * | 0x08      | fft_ctrl       | fft ctrl reg                        |
 * | 0x10      | fifo_ctrl      | fifo ctrl                           |
 * | 0x18      | intr_mask      | interrupt mask                      |
 * | 0x20      | intr_clear     | interrupt clear                     |
 * | 0x28      | fft_status     | fft status reg                      |
 * | 0x30      | fft_status_raw | fft_status_raw                      |
 * | 0x38      | fft_output_fifo| fft_output_fifo                     |
 *
 */


/**
 * @brief      input data fifo
 *
 *             No. 0 Register (0x00)
 */
struct fft_fft_input_fifo_t {
    uint64_t fft_input_fifo;
} __attribute__((packed, aligned(8)));

/**
 * @brief      fft ctrl reg
 *
 *             No. 1 Register (0x08)
 */
struct fft_fft_ctrl_t {
    uint64_t fft_point : 3;
    uint64_t fft_mode : 1;
    uint64_t fft_shift : 9;
    uint64_t fft_enable : 1;
    uint64_t dma_send : 1;
    uint64_t fft_input_mode : 2;
    uint64_t fft_data_mode : 1;
    uint64_t reserved : 46;
} __attribute__((packed, aligned(8)));

/**
 * @brief      fifo ctrl
 *
 *             No. 2 Register (0x10)
 */
struct fft_fifo_ctrl_t {
    uint64_t resp_fifo_flush_n : 1;
    uint64_t cmd_fifo_flush_n : 1;
    uint64_t gs_fifo_flush_n : 1;
    uint64_t reserved : 61;
} __attribute__((packed, aligned(8)));

/**
 * @brief      interrupt mask
 *
 *             No. 3 Register (0x18)
 */
struct fft_intr_mask_t {
    uint64_t fft_done_mask : 1;
    uint64_t reserved : 63;
} __attribute__((packed, aligned(8)));

/**
 * @brief      interrupt clear
 *
 *             No. 4 Register (0x20)
 */
struct fft_intr_clear_t {
    uint64_t fft_done_clear;
} __attribute__((packed, aligned(8)));

/**
 * @brief      fft status reg
 *
 *             No. 5 Register (0x28)
 */
struct fft_fft_status_t {
    uint64_t fft_done_status;
} __attribute__((packed, aligned(8)));

/**
 * @brief      fft_status_raw
 *
 *             No. 6 Register (0x30)
 */
struct fft_fft_status_raw_t {
    uint64_t fft_done_status_raw;
} __attribute__((packed, aligned(8)));

/**
 * @brief      fft_output_fifo
 *
 *             No. 7 Register (0x38)
 */
struct fft_fft_output_fifo_t {
    uint64_t fft_output_fifo;
} __attribute__((packed, aligned(8)));


/**
 * @brief      Fast Fourier transform (FFT) algorithm accelerator object
 *
 *             A fast Fourier transform (FFT) algorithm computes the discrete
 *             Fourier transform (DFT) of a sequence, or its inverse (IFFT).
 *             Fourier analysis converts a signal from its original domain
 *             (often time or space) to a representation in the frequency
 *             domain and vice versa. An FFT rapidly computes such
 *             transformations by factorizing the DFT matrix into a product of
 *             sparse (mostly zero) factors.
 */
struct fft_t {
    struct fft_fft_input_fifo_t fft_input_fifo;
    /*!< No. 0 (0x00): input data fifo */
    struct fft_fft_ctrl_t fft_ctrl;
    /*!< No. 1 (0x08): fft ctrl reg */
    struct fft_fifo_ctrl_t fifo_ctrl;
    /*!< No. 2 (0x10): fifo ctrl */
    struct fft_intr_mask_t intr_mask;
    /*!< No. 3 (0x18): interrupt mask */
    struct fft_intr_clear_t intr_clear;
    /*!< No. 4 (0x20): interrupt clear */
    struct fft_fft_status_t fft_status;
    /*!< No. 5 (0x28): fft status reg */
    struct fft_fft_status_raw_t fft_status_raw;
    /*!< No. 6 (0x30): fft_status_raw */
    struct fft_fft_output_fifo_t fft_output_fifo;
    /*!< No. 7 (0x38): fft_output_fifo */
} __attribute__((packed, aligned(8)));

int fft_init(uint8_t point, uint8_t mode, uint16_t shift, uint8_t is_dma, fft_input_mode_e input_mode, fft_data_mode_e data_mode);
void reset_fft(void);
void enable_fft_int(void);
void clear_fft_int(void);
void fft_input_data(float *x, float *y, uint8_t point, fft_input_mode_e input_mode, fft_data_mode_e data_mode);
void fft_input_intdata(float *data, uint8_t point);

uint8_t fft_get_finish_flag(void);
void fft_get_result(float *x, float *y, uint8_t point, uint8_t mode);
int fft_test(uint32_t fft_n, float *input_real, float *input_image);
int ifft_test(uint32_t fft_n, float *input_real, float *input_image);

/**
 * @brief      Fast Fourier transform (FFT) algorithm accelerator object
 */
extern volatile struct fft_t *const fft;

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_FFT_H */
