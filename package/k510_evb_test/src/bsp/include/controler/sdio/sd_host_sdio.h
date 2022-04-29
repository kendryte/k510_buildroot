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
