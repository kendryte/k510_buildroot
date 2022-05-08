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
#include <stdint.h>
#include "sd_host_emmc.h"
#include "sd_host_global.h"

void emmc_card_init ()
{
  uint32_t status;
  uint32_t timeout = 1000000;

  sd_host_send_cmd((0 << CI) | (0<<CRCCE) | (0<<RTS), 0x00000000);

  do {
    status = 0x00ff8000;
    status |= (1 << 7);  // 1.8V
    status |= (SD_ADDR_SECTOR_MODE << 30); // byte or sector address mode
    sd_host_send_cmd((1 << CI) | (2<<RTS), status);  // voltage and address mode

    status = IORD_32_SRS(SD_REG_SRS4);
    if(timeout-- == 0)
    {
      printf("CMD1 timeout\n");
    }
  } while ((status & 0x80000000) == 0);

  sd_host_send_cmd((2 << CI) | (0<<CRCCE) | (1<<RTS), 0x00000000);
  
  status = IORD_32_SRS(SD_REG_SRS4);

  sd_card_rca = 0x1234;
  sd_host_send_cmd((3 << CI) | (3<<CRCCE) | (2<<RTS), sd_card_rca << 16);
}

void emmc_select_card(uint32_t sd_card_rca)
{
  if (sd_card_rca == 0x0000)
  {
    sd_host_send_cmd((7 << CI) | (0<<CRCCE) | (0<<RTS), 0x0000);
  }
  else {
    sd_host_send_cmd((7 << CI) | (3<<CRCCE) | (2<<RTS), sd_card_rca << 16);
  }
}

void emmc_set_mode (uint8_t bit_width, uint8_t mode)
{
  /*
   *  bit_width:  1,4,8
   *  mode:
   *      0 - Standard mode   (0-26MHz)
   *      1 - High Speed mode (0-52MHz)
   *  For allowed confugrations see:
   *    eMMC5.0 JADEC standard, ch. 5.3.2 Bus Speed Modes (Table 4)
   */

  uint32_t status;
  uint32_t val;
  uint8_t _bit_width;
  uint8_t ddr_mode;

  _bit_width = bit_width & 0x0f;
  ddr_mode = mode & 0x10 ? 1 : 0;
  mode = mode & 0x0f;

  status = IORD_32_SRS(SD_REG_SRS10);
  status &= ~((1<<DTW) | (1<<EDTW));

  switch (_bit_width) {
    case 0x01: _bit_width = 0x00; break;
    case 0x04: _bit_width = 0x01; status |= (1<<DTW);  break;
    case 0x08: _bit_width = 0x02; status |= (1<<EDTW) | (1<<DTW); break;
    default: _bit_width = 0x01; status |= (1<<DTW);  break;
  }
  IOWR_32_SRS (SD_REG_SRS10, status);

  val = ((_bit_width << 8) | (183<<16) | (3 << 24)); //183 - BUS_WIDTH byte, 3 - ACCESS write byte
  sd_host_send_cmd((6 << CI) | (3<<CRCCE) | (3<<RTS), val);
  // response R1b - busy signal is transmitted on the DAT0 line
  do {
    status = IORD_32_SRS(SD_REG_SRS12);
  } while ((status & (1<<TC) ) == 0); 

  // Read card type
  // CMD8 - send ext csd
  IOWR_32_SRS (SD_REG_SRS1,  (7 << HDMABB) | (1 << BCCT) | 512);    // data size: 512B of EXT_CSD
  sd_host_send_cmd((8 << CI) | (1 << DPS) | (3 << CRCCE) | (2<<RTS) | (1<<DTDS), 0);

  while( ((IORD_32_SRS(SD_REG_SRS9) >> BRE ) & 0x01) == 0 ); // wait for BRE

  int i;

  for (i=0; i<(512/4); i++) {  // read 512B, 4B at once
    val = IORD_32_SRS(SD_REG_SRS8);

    if (i == 196/4) status = val & 0xff; // remember DEVICE_TYPE [196] register
  }

  if (((mode == eMMC_MODE_HS) && ((status & (3 << 0)) == 0)) ||
      ((mode == eMMC_MODE_HS) && ddr_mode && ((status & (3 << 2)) == 0)))
  {
      printf("Selected work mode is not supported by inserted card. DEVICE_TYPE[196]=0x%x...\r\n", status);

      while(1);
  }

  do {
    status = IORD_32_SRS(SD_REG_SRS12);
  } while ((status & (1<<TC) ) == 0); 

  val = ((mode << 8) | (185<<16) | (3 << 24)); //185 - HS_TIMING byte, 3 - ACCESS write byte
  sd_host_send_cmd((6 << CI) | (3<<CRCCE) | (3<<RTS), val);
  // response R1b - busy signal is transmitted on the DAT0 line
  do {
      status = IORD_32_SRS(SD_REG_SRS12);
  } while ((status & (1<<TC) ) == 0); 

  switch (mode) {
    case eMMC_MODE_SDR:     val = 0x01; break;
    case eMMC_MODE_HS:      val = ddr_mode ? 0x03 : 0x02; break; // HS DDR or SDR mode
    default:                val = 0x00; break; // disabled
  }
  IOWR_32_SRS(SD_REG_SRS11, 0);   // disable SDCE - it will be re-enabled when sd_host_set_clk is called
  usleep(10);
  IOWR_32_SRS (SD_REG_HRS6, val);

  if (mode == eMMC_MODE_HS)
    sd_host_set_clk(25000);
  else
    sd_host_set_clk(400);

  if (ddr_mode)
  {
    _bit_width |= (1<<2);
    val = ((_bit_width << 8) | (183<<16) | (3 << 24)); //183 - BUS_WIDTH byte, 3 - ACCESS write byte
    sd_host_send_cmd((6 << CI) | (3<<CRCCE) | (3<<RTS), val);
    // response R1b - busy signal is transmitted on the DAT0 line
    do {
      status = IORD_32_SRS(SD_REG_SRS12);
    } while ((status & (1<<TC) ) == 0);
  }
}
