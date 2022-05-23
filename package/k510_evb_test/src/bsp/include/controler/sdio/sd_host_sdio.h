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
#ifndef _SD_HOST_SDIO_H_
#define _SD_HOST_SDIO_H_

// SDIO Card standard modes
#define SDIO_MODE_DS      0
#define SDIO_MODE_HS      1

#define SDIO_MODE_SDR12   0
#define SDIO_MODE_SDR25   1
#define SDIO_MODE_SDR50   2
#define SDIO_MODE_SDR104  3
#define SDIO_MODE_DDR50   4

#define SDIO_CCCR_IO_ENABLE 0x02
#define SDIO_CCCR_IO_READY  0x02
#define SDIO_CCCR_BUS_CTRL  0x07
#define SDIO_CCCR_F_BW      0
#define SDIO_CCCR_F_CDD     7
#define SDIO_CCCR_SPEEDSEL  0x13
#define SDIO_CCCR_F_SHS     0
#define SDIO_CCCR_F_BSS     1
#define SDIO_CCCR_UHS_SUPP  0x14

void sd_card_init();
int sdio_set_mode (char bit_width, char mode);
void sd_card_set_mode (uint8_t bit_width, uint8_t mode);
void sd_card_select_card (uint32_t sd_card_rca);
void sdio_write_reg (uint8_t func_num, uint32_t reg_addr, uint32_t data);
uint8_t sdio_read_reg (uint8_t func_num, uint32_t reg_addr);
void sdio_pio_write (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t data_size);

void sdio_pio_read (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t data_size);

void sdio_dma_write (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t block_cnt, char use_adma2, char use_intr);

void sdio_dma_read (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t block_cnt, char use_adma2, char use_intr);
#endif /* _SD_HOST_SDIO_H_ */
