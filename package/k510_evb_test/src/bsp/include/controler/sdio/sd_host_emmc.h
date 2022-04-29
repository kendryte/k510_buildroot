#ifndef _SD_HOST_EMMC_H_
#define _SD_HOST_EMMC_H_

// eMMC modes
#define eMMC_MODE_SDR     0
#define eMMC_MODE_HS      1
#define eMMC_MODE_HS_DDR  0x11

void emmc_card_init ();
void emmc_select_card(uint32_t sd_card_rca);
void emmc_set_mode (uint8_t bit_width, uint8_t mode);

#endif /* _SD_HOST_EMMC_H_ */
