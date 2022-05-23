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
#include <string.h>
#include "sd_host_global.h"

uint32_t sd_card_rca;
card_info_t card_info;

#define check(func) { \
 int status = func;  \
 if (status){\
   printf("ERROR nr 0x%X, %s %d\n", status, __FILE__, __LINE__); \
   return (status);\
}}

void sd_host_set_clk(uint32_t freq_khz) {
  uint32_t sdclkfs;
  uint32_t dtcvval;

  sdclkfs = (SD_HOST_CLK / 2000) / freq_khz;
  dtcvval = 0xe ;

  IOWR_32_SRS(SD_REG_SRS11, (dtcvval << DTCV) | (sdclkfs<<SDCLKFS) | (1<<ICE) );

  while ((IORD_32_SRS(SD_REG_SRS11) & (1<<ICS)) == 0);

  IOWR_32_SRS(SD_REG_SRS11, (dtcvval << DTCV) | (sdclkfs<<SDCLKFS) | (1<<ICE) | (1<<SDCE) );
}

void sd_host_set_dlyvr(uint8_t addr, uint8_t data)
{
  uint32_t dlyrv_reg;

  dlyrv_reg = addr | (data << 8);
  IOWR_32_SRS(SD_REG_HRS4, dlyrv_reg); //set data and address
  dlyrv_reg |= (1<<24);
  IOWR_32_SRS(SD_REG_HRS4, dlyrv_reg); //send write request

  while (1) { // wait for acknowledge
    dlyrv_reg = IORD_32_SRS(SD_REG_HRS4);
    if ((dlyrv_reg >> 26) & 1)
      break;
  }

  dlyrv_reg &= ~(1<<24);
  IOWR_32_SRS(SD_REG_HRS4, dlyrv_reg); //clear write request

  while (1) { // wait for acknowledge to be cleared
    dlyrv_reg = IORD_32_SRS(SD_REG_HRS4);
    if (~(dlyrv_reg >> 26) & 1)
        break;
  }
}

void sd_host_init (uintptr_t host_base)
{
  SD_HOST_BASE = host_base;
  IOWR_32_SRS(SD_REG_SRS11, 0);

  IOWR_32_SRS(SD_REG_HRS0, (1<<0) ) ;

  while ((IORD_32_SRS(SD_REG_HRS0) & (1<<0)) == 1);

  IOWR_32_SRS(SD_REG_SRS10, 0<<BP);
  usleep(1);
  IOWR_32_SRS(SD_REG_SRS10, 1<<BP) ;

  usleep(2000);

  sd_host_set_clk(398);

  IOWR_32_SRS(SD_REG_SRS13, 0xffffffff);
}

void sd_host_send_cmd(uint32_t srs3, uint32_t cmd_arg) {
  uint32_t status = 0;

  IOWR_32_SRS (SD_REG_SRS12, 0xffffffff);
  IOWR_32_SRS (SD_REG_SRS2, cmd_arg);

  IOWR_32_SRS(SD_REG_SRS14, 0x00000000);
  IOWR_32_SRS (SD_REG_SRS3, srs3);

  do {
    status = IORD_32_SRS(SD_REG_SRS12);
  } while ((status & ((1<<CC) | (1<<EINT)) ) == 0);

  status &= 0xffff8000;
  if(status)
  {
      printf("Send CMD%d failed SRS12=0x%x\r\n", (srs3>>CI) & 0x3f, status);

      while(1);
  }
}

void sd_host_send_cmd_int(uint32_t srs3, uint32_t cmd_arg) {
  uint32_t status = 0;

  IOWR_32_SRS (SD_REG_SRS12, 0xffffffff);
  IOWR_32_SRS (SD_REG_SRS2, cmd_arg);

  IOWR_32_SRS(SD_REG_SRS14, (1<<CC) | (1<<TC) | (1<<EINT) | (1 << DINT));
  IOWR_32_SRS (SD_REG_SRS3, srs3);
}

void sd_host_card_pio_write(uint32_t sector,  uint32_t *sys_mem_addr, uint32_t block_cnt)
{
  uint32_t* buff = sys_mem_addr;
  uint32_t status;

  int i,j;

  IOWR_32_SRS (SD_REG_SRS1, SD_HOST_BLOCK_SIZE);

  for (j=0; j<block_cnt ; j++)
  {
    sd_host_send_cmd( ((24 << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) ), sector);

    while(((IORD_32_SRS(SD_REG_SRS9) >> BWE) & 0x01) == 0 );
    for (i=0; i<(SD_HOST_BLOCK_SIZE/4); i++)
    {
      IOWR_32_SRS (SD_REG_SRS8, buff[i]);
    }

    do {
      status = IORD_32_SRS(SD_REG_SRS12);
    } while ((status & (1<<TC) ) == 0);

    buff += SD_HOST_BLOCK_SIZE / 4;
    sector ++;
  }
}

void sd_host_card_pio_read(uint32_t sector, uint32_t *sys_mem_addr, uint32_t block_cnt)
{
  uint32_t *buff = (uint32_t *)sys_mem_addr;

  int i;
  uint32_t rdy = (1<<BRR);
	uint32_t mask = (1<<BRE);
  uint32_t stat;
  uint8_t cmd_index = 17;
  uint8_t transfer_done = 0;
  uint32_t block = 0;
  uint32_t *offs;
  uint32_t timeout = 100000;
  uint32_t mode = (1 << DTDS) | (1 << BCE);

  IOWR_32_SRS (SD_REG_SRS1, (block_cnt<<16) |SD_HOST_BLOCK_SIZE);

  if(block_cnt > 1)
  {
    cmd_index = 18;
    mode |= (1 << MSBS);
  }

  sd_host_send_cmd(((cmd_index << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) | mode), sector);
  IOWR_32_SRS(SD_REG_SRS12, 0x1);
  do {
      stat = IORD_32_SRS(SD_REG_SRS12);
      if(stat & (1<<EINT))
      {
        printf("read error\n");
        while(1);
      }
      if (!transfer_done && (stat & rdy)) {
        if (!(IORD_32_SRS(SD_REG_SRS9) & mask))
				  continue;
        IOWR_32_SRS(SD_REG_SRS12, rdy);
        for (i=0; i<SD_HOST_BLOCK_SIZE/4; i++)
        {
          offs = buff + i;
          *offs = IORD_32_SRS (SD_REG_SRS8);
        }
        buff += SD_HOST_BLOCK_SIZE/4;
        if (++block >= block_cnt) {
          transfer_done = 1;
          continue;
			  }
      }
      if (timeout-- > 0)
        usleep(10);
      else {
        printf("read timeout\n");
        while(1);
      }
  } while (!(stat & (1<<TC)));

  if(block_cnt > 1)
    sd_host_send_cmd(((12 << CI) | (3 << CRCCE) | (3 << RTS)), 0);
}

// ----------------------------------------------------------------------------
uint32_t sd_host_prepare_descriptors_local(unsigned char* desc_ptr, unsigned char* dma_start_addr, uint32_t bcnt){

  uint32_t* _desc_tab      = (uint32_t*)desc_ptr;             // descriptors table
  uint64_t _dma_addr       = (size_t)dma_start_addr;
  unsigned int _full_desc_cnt  = (bcnt*SD_HOST_BLOCK_SIZE)/(64*1024);  // number of full page (64kB) descriptors
  unsigned int _add_desc_cnt   = (bcnt*SD_HOST_BLOCK_SIZE)%(64*1024);  // additional data
 
  int i;
  printf("Enter SDHost_prepare_descriptors_local\n");
  printf("_desc_tab=%x\n",_desc_tab);
  printf("_dma_addr=%x\n",_dma_addr);
  printf("_full_desc_cnt=%x\n",_full_desc_cnt);
  printf("_add_desc_cnt=%x \n",_add_desc_cnt);
  if (SD_DESC_SIZE == 2) {
    IOWR_32_SRS (SD_REG_SRS15, IORD_32_SRS(SD_REG_SRS15) & ~(1 << 28) & ~(1 << 26)); // 32b mode, 16-bit LM
  } else {
    IOWR_32_SRS (SD_REG_SRS15, IORD_32_SRS(SD_REG_SRS15) | (1 << 29) | (1 << 28) & ~(1 << 26)); // 64b mode, 16-bit LM
  }
  printf("_full_desc_cnt=%x\n",_full_desc_cnt);
  for (i=0; i<_full_desc_cnt;i++) { // one desc = 64kB
    IOWR_32((_desc_tab + i*SD_DESC_SIZE + 0) , 0x00000021);  // VAL =1, ACT = TRAN |  0 -  7
    IOWR_32((_desc_tab + i*SD_DESC_SIZE + 1) , _dma_addr & 0xffffffff);
    if (SD_DESC_SIZE > 2)
      IOWR_32((_desc_tab + i*SD_DESC_SIZE + 2), _dma_addr >> 32);
    _dma_addr += 1024*64;  //64kB
  }
  printf("_add_desc_cnt=%x\n",_add_desc_cnt);
  if (_add_desc_cnt == 0) i--;
  else {
    IOWR_32((_desc_tab + i*SD_DESC_SIZE + 1),_dma_addr & 0xffffffff);
    if (SD_DESC_SIZE > 2)
      IOWR_32((_desc_tab + i*SD_DESC_SIZE + 2),_dma_addr >> 32);
  }
  printf("test point\n");
  IOWR_32((_desc_tab + i*SD_DESC_SIZE + 0),(_add_desc_cnt << 16) | 0x0023);  // VAL =1, END=1 ACT = TRAN
  IOWR_32_SRS (SD_REG_SRS22, (uint32_t)_desc_tab & 0xffffffff);
  IOWR_32_SRS (SD_REG_SRS23, (uint64_t)_desc_tab >> 32);
  return (uint32_t)((size_t)_desc_tab & 0xffffffff);
}