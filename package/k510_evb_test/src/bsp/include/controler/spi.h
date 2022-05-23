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
#ifndef DRIVER_SPI_H
#define DRIVER_SPI_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _spi_work_mode
{
    SPI_WORK_MODE_0,
    SPI_WORK_MODE_1,
    SPI_WORK_MODE_2,
    SPI_WORK_MODE_3,
} spi_work_mode_t;

typedef enum _spi_frame_format
{
    SPI_FF_STANDARD,
    SPI_FF_DUAL,
    SPI_FF_QUAD,
    SPI_FF_OCTAL
} spi_frame_format_t;

typedef enum _spi_instruction_address_trans_mode
{
    SPI_AITM_STANDARD,
    SPI_AITM_ADDR_STANDARD,
    SPI_AITM_AS_FRAME_FORMAT
} spi_instruction_address_trans_mode_t;

typedef enum _spi_transfer_mode
{
    SPI_TMOD_TRANS_RECV,
    SPI_TMOD_TRANS,
    SPI_TMOD_RECV,
    SPI_TMOD_EEROM
} spi_transfer_mode_t;

typedef enum _spi_device_num
{
    SPI_DEVICE_0,
    SPI_DEVICE_1,
    SPI_DEVICE_2,
    SPI_DEVICE_3,
    SPI_DEVICE_MAX,
} spi_device_num_t;

/* clang-format off */
typedef struct _spi
{
    /* SPI Control Register 0                                    (0x00)*/
    volatile uint32_t ctrlr0;
    /* SPI Control Register 1                                    (0x04)*/
    volatile uint32_t ctrlr1;
    /* SPI Enable Register                                       (0x08)*/
    volatile uint32_t ssienr;
    /* SPI Microwire Control Register                            (0x0c)*/
    volatile uint32_t mwcr;
    /* SPI Slave Enable Register                                 (0x10)*/
    volatile uint32_t ser;
    /* SPI Baud Rate Select                                      (0x14)*/
    volatile uint32_t baudr;
    /* SPI Transmit FIFO Threshold Level                         (0x18)*/
    volatile uint32_t txftlr;
    /* SPI Receive FIFO Threshold Level                          (0x1c)*/
    volatile uint32_t rxftlr;
    /* SPI Transmit FIFO Level Register                          (0x20)*/
    volatile uint32_t txflr;
    /* SPI Receive FIFO Level Register                           (0x24)*/
    volatile uint32_t rxflr;
    /* SPI Status Register                                       (0x28)*/
    volatile uint32_t sr;
    /* SPI Interrupt Mask Register                               (0x2c)*/
    volatile uint32_t imr;
    /* SPI Interrupt Status Register                             (0x30)*/
    volatile uint32_t isr;
    /* SPI Raw Interrupt Status Register                         (0x34)*/
    volatile uint32_t risr;
    /* SPI Transmit FIFO Overflow Interrupt Clear Register       (0x38)*/
    volatile uint32_t txoicr;
    /* SPI Receive FIFO Overflow Interrupt Clear Register        (0x3c)*/
    volatile uint32_t rxoicr;
    /* SPI Receive FIFO Underflow Interrupt Clear Register       (0x40)*/
    volatile uint32_t rxuicr;
    /* SPI Multi-Master Interrupt Clear Register                 (0x44)*/
    volatile uint32_t msticr;
    /* SPI Interrupt Clear Register                              (0x48)*/
    volatile uint32_t icr;
    /* SPI DMA Control Register                                  (0x4c)*/
    volatile uint32_t dmacr;
    /* SPI DMA Transmit Data Level                               (0x50)*/
    volatile uint32_t dmatdlr;
    /* SPI DMA Receive Data Level                                (0x54)*/
    volatile uint32_t dmardlr;
    /* SPI Identification Register                               (0x58)*/
    volatile uint32_t idr;
    /* SPI DWC_ssi component version                             (0x5c)*/
    volatile uint32_t ssic_version_id;
    /* SPI Data Register 0-36                                    (0x60 -- 0xec)*/
    volatile uint32_t dr[36];
    /* SPI RX Sample Delay Register                              (0xf0)*/
    volatile uint32_t rx_sample_delay;
    /* SPI SPI Control Register                                  (0xf4)*/
    volatile uint32_t spi_ctrlr0;
    /* reserved                                                  (0xf8)*/
    volatile uint32_t resv;
    /* SPI XIP Mode bits                                         (0xfc)*/
    volatile uint32_t xip_mode_bits;
    /* SPI XIP INCR transfer opcode                              (0x100)*/
    volatile uint32_t xip_incr_inst;
    /* SPI XIP WRAP transfer opcode                              (0x104)*/
    volatile uint32_t xip_wrap_inst;
    /* SPI XIP Control Register                                  (0x108)*/
    volatile uint32_t xip_ctrl;
    /* SPI XIP Slave Enable Register                             (0x10c)*/
    volatile uint32_t xip_ser;
    /* SPI XIP Receive FIFO Overflow Interrupt Clear Register    (0x110)*/
    volatile uint32_t xrxoicr;
    /* SPI XIP time out register for continuous transfers        (0x114)*/
    volatile uint32_t xip_cnt_time_out;
    volatile uint32_t endian;
} __attribute__((packed, aligned(4))) spi_t;
/* clang-format on */

extern volatile spi_t* const spi[4];

void spi_init(spi_device_num_t spi_num, uint32_t baud);

void spi_set_tmod(spi_device_num_t spi_num, uint32_t tmod);

void spi_send_data(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, const uint8_t *tx_buff, size_t tx_len);

void spi_receive_data(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, uint8_t *rx_buff, size_t rx_len);

void spi_receive_data_32bit(spi_device_num_t spi_num, const uint32_t *cmd_buff,
                               size_t cmd_len, uint8_t *rx_buff, size_t rx_len);

void spi_set_mode(spi_device_num_t spi_num, spi_frame_format_t format, uint8_t inst_width, uint8_t address_width, uint8_t wait_width);

void spi_send_data_dma(spi_device_num_t spi_num, uint8_t *tx_buff, size_t tx_len);

void spi_receive_data_dma(spi_device_num_t spi_num,  uint8_t *cmd_buff,
                                 size_t cmd_len, uint8_t *rx_buff, size_t rx_len);
#ifdef __cplusplus
}
#endif

#endif /* DRIVER_SPI_H */
    