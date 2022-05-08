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
#include "sd_host_sdio.h"
#include "sd_host_global.h"

void sd_card_init()
{
  uint32_t status;
  uint32_t timeout = 1000000;
  uint32_t buffer[4];
  uint64_t c_size, c_mult;

  sd_host_send_cmd((0 << CI), 0x00000000);

  // CMD8 - send interface condition
  sd_host_send_cmd( (8 << CI) | (3<<CRCCE) | (2<<RTS), 0x000001aa);
  status = IORD_32_SRS(SD_REG_SRS4);
  if (status != 0x000001aa) {
    printf("ERROR: SRS4 = 0x%x (should be 0x000001aa)\r\n", status);

    while(1);
  }

  // ACMD41 - CMD55 - R1 - CMD41 - R3 (until R3->ready)
  do {
    // CMD55 with response R1
    sd_host_send_cmd( (55 << CI) | (3<<CRCCE) | (2<<RTS), 0x00000000);

    // CMD41 with response R3
    sd_host_send_cmd( (41 << CI) | (0<<CRCCE) | (2<<RTS), 0x101f0000 | (1<<30) | (1<<24)); // OCR - supported voltage 2,8V - 3,3V + HCS + S18R - UHS1
    status = IORD_32_SRS(SD_REG_SRS4);
    if(timeout-- == 0)
    {
      printf("CMD41 timeout\n");
      while(1);
    }
  } while ((status & (1<<31)) == 0);
  card_info.high_capacity = ((status & 0x40000000) == 0x40000000);

  // CMD2 - get card ID
  sd_host_send_cmd((2 << CI) | (0<<CRCCE) | (1<<RTS), 0x00000000);
  status = IORD_32_SRS(SD_REG_SRS4);
  printf("SD Card ID = 0x%x\r\n", status);
  status = IORD_32_SRS(SD_REG_SRS5);
  printf("SD Card ID = 0x%x\r\n", status);
  status = IORD_32_SRS(SD_REG_SRS6);
  printf("SD Card ID = 0x%x\r\n", status);
  status = IORD_32_SRS(SD_REG_SRS7);
  printf("SD Card ID = 0x%x\r\n", status);

  // CMD3 - get card RCA
  sd_host_send_cmd((3 << CI) | (3<<CRCCE) | (2<<RTS), 0x00000000);

  status = IORD_32_SRS(SD_REG_SRS4);
  sd_card_rca = (status >> 16);
  printf("sd_card_rca=0x%x \n", sd_card_rca);
  printf("SD Card init completed\r\n");
#if 1
  sd_host_send_cmd((9 << CI) | (1<<CRCCE) | (1<<RTS), sd_card_rca << 16);
  buffer[0] = IORD_32_SRS(SD_REG_SRS4);
  buffer[1] = IORD_32_SRS(SD_REG_SRS5);
  buffer[2] = IORD_32_SRS(SD_REG_SRS6);
  buffer[3] = IORD_32_SRS(SD_REG_SRS7);

  for(int i=0; i<4; i++)
  {
    buffer[3 - i] <<= 8;
    if(i != 3)
    {
      buffer[3 - i] |= ((buffer[2 - i] >> 24) & 0xff);
    }
  }
  card_info.csd_structVer = (uint8_t)( buffer[3] >> 30 ) & 0x3U;
  
  card_info.read_bl_len = (buffer[2] >> (80 - 64)) & 0xf;//[83:80]
  card_info.write_bl_len = (buffer[0] >> (22 - 0)) & 0xf;//[25:22]
  card_info.sector_size = (buffer[1] >> (39 - 32)) & 0x7f;//[45:39]
  card_info.block_size = (1 << card_info.read_bl_len);
  if (card_info.high_capacity)
  {
      c_size = buffer[1] >> (48 - 32);    //[69:48]
      c_size |= ( buffer[2] & 0x3f ) << (64 - 48);
      c_mult = 8;
  }
  else
  {
      printf("Do not support Standard capacity SD Card.\r\n");
      printf("The Maximum Data Area size of Standard Capacity SD Card is 4,153,344 sectors (2028MB).\r\n");
  }

  card_info.capacity_user = (c_size + 1) << (c_mult + 2);
  card_info.capacity_user *= card_info.block_size;

  printf("high_capacity %d \r\n", card_info.high_capacity);
  printf("capacity_user %ld MB\r\n", card_info.capacity_user>>20);
  printf("csd_structVer %d\r\n", card_info.csd_structVer);
  printf("read_bl_len %d \r\n", card_info.read_bl_len);
  printf("write_bl_len %d \r\n", card_info.write_bl_len);
  printf("sector_size %d \r\n", card_info.sector_size);
  printf("block_size %d \r\n", card_info.block_size);
#endif
}

uint32_t sd_card_get_status(unsigned int sd_card_rca) {
  uint32_t _status;
  uint32_t _srs3;

  _srs3 = ((uint32_t) (0)) | ((13 << CI) | (3<<CRCCE) | (2<<RTS)) ;

  sd_host_send_cmd(_srs3 , sd_card_rca << 16);
  _status = IORD_32_SRS(SD_REG_SRS4);
  printf("SD card status = 0x%x\r\n", _status);

  return _status;
}

void  sd_card_read_state(unsigned int sd_card_rca) {
  unsigned char _status;
  char _str[10];

  _status = (sd_card_get_status(sd_card_rca) >> 9) & 0x0f;

  switch (_status) {
    case  0: strcpy(_str, "Idle");      break;
    case  1: strcpy(_str, "Ready");     break;
    case  2: strcpy(_str, "Ident");     break;
    case  3: strcpy(_str, "Stby");      break;
    case  4: strcpy(_str, "Tran");      break;
    case  5: strcpy(_str, "Data");      break;
    case  6: strcpy(_str, "Rcv");       break;
    case  7: strcpy(_str, "Prg");       break;
    case  8: strcpy(_str, "Dis");       break;
    case  9: strcpy(_str, "Btst");      break;
    case 10: strcpy(_str, "Slp");       break;
    default: strcpy(_str, "Reserved");  break;
  }

  printf("SD card state: %s\r\n", _str);
}

void sd_card_set_mode (uint8_t bit_width, uint8_t mode)
{
  /*
   *  bit_width:  1 or 4 (UHS-I mode support only 4 bit data transmission)
   *  mode:
   *      0 - Default mode / UHS-I SDR12
   *      1 - High Speed mode / UHS-I SDR25
   *      2 - UHS-I SDR50
   *      3 - UHS-I SDR104
   *      4 - UHS-I DDR50
   *  For supported modes check:
   *    SD Specifications, Part 1 PLS, V4.00
   *      chapter 3.9.2 UHS-I Card Types,
   *      Fig. 3-14 "UHS-I Card Type Modes of Operation"
   */

  uint32_t status;
  char _bit_width;

  switch (bit_width) {
    case 1: _bit_width = 0x00; break;  // bus width 1 = 2^0;
    case 4: _bit_width = 0x02; break;  // bus width 4 = 2^2;
    default: _bit_width = 0x00; break;
  }

  sd_host_send_cmd((55 << CI) | (3<<CRCCE) | (2<<RTS), sd_card_rca << 16);

  // CMD6 with response R1
  sd_host_send_cmd(( 6 << CI) | (3<<CRCCE) | (2<<RTS), _bit_width);

  status = IORD_32_SRS(SD_REG_SRS10);
  if (_bit_width > 0)
  {
    status |= (1<<DTW);  // enable DTW in SD host
  } else {
    status &= ~(1<<DTW); // disable DTW in SD host
  }
  IOWR_32_SRS (SD_REG_SRS10, status);

  IOWR_32_SRS (SD_REG_SRS1, 0x00017040);
  sd_host_send_cmd((6 << CI) | (1<<DPS) | (3<<CRCCE) | (2<<RTS) | (1<<DTDS) | 2, 0x80000000 | mode); //SFR
  for (int i=0; i<(512/32); i++) {
    while( ((IORD_32_SRS(SD_REG_SRS9) >> 11 ) & 0x01) == 0 ); //BRE
    status = IORD_32_SRS(SD_REG_SRS8);
    #if 0
    printf("DATA BLOCK[%d - %d] = 0x%x\r\n", 511 - (32*i+ 0), 511 - 7 - (32*i+ 0) , (status >>  0) & 0xff);
    printf("DATA BLOCK[%d - %d] = 0x%x\r\n", 511 - (32*i+ 8), 511 - 7 - (32*i+ 8) , (status >>  8) & 0xff);
    printf("DATA BLOCK[%d - %d] = 0x%x\r\n", 511 - (32*i+16), 511 - 7 - (32*i+16) , (status >> 16) & 0xff);
    printf("DATA BLOCK[%d - %d] = 0x%x\r\n", 511 - (32*i+24), 511 - 7 - (32*i+24) , (status >> 24) & 0xff);
    #endif
  }

  status = IORD_32_SRS(SD_REG_SRS10);
  if (mode>0) {
    status |= (1<<HSE);  // enable HSE in SD host
  } else {
    status &= ~(1<<HSE); // disable HSE in SD host
  }

  IOWR_32_SRS (SD_REG_SRS10, status);
}

void sd_card_select_card (uint32_t sd_card_rca)
{
  uint32_t status;

  if (sd_card_rca != 0x0000)
  {
    sd_host_send_cmd((7 << CI) | (3<<CRCCE) | (3<<RTS), sd_card_rca << 16);
    // response R1b - busy signal is transmitted on the DAT0 line

    do {
      status = IORD_32_SRS(SD_REG_SRS12);
    } while ((status & (1<<TC) ) == 0);
  }
  else {
    sd_host_send_cmd((7 << CI), 0x0000);
  }
}

void sdio_write_reg (uint8_t func_num, uint32_t reg_addr, uint32_t data)
{
  uint32_t _argument;

  _argument = data | (reg_addr << 9) | (func_num << 28) | (1 << 31);


  sd_host_send_cmd( (52 << CI) | (3<<CRCCE) | (2<<RTS), _argument);
}

uint8_t sdio_read_reg (uint8_t func_num, uint32_t reg_addr)
{
  uint32_t _status, _argument;

  _argument = (reg_addr << 9) | (func_num << 28);

  sd_host_send_cmd((52 << CI) | (3<<CRCCE) | (2<<RTS), _argument );
  _status = IORD_32_SRS(SD_REG_SRS4);

  return (_status & 0xff);
}

void sdio_card_init()
{
  uint32_t status;
  sd_host_send_cmd((0 << CI), 0x00000000);

  sd_host_send_cmd((5 << CI) | (0<<CRCCE) | (2<<RTS), 0x00000000);

  do {
    sd_host_send_cmd( (5 << CI) | (0<<CRCCE) | (2<<RTS), 0x01ffff00 ); // OCR, S18R = UHS1
    status = IORD_32_SRS(SD_REG_SRS4);
  } while ((status & (1<<31)) == 0);

  sd_host_send_cmd((3 << CI) | (3<<CRCCE) | (2<<RTS), 0x00000000 );

  status = IORD_32_SRS(SD_REG_SRS4);
  sd_card_rca = (status >> 16);
  printf("Card RCA number: 0x%x\r\n", sd_card_rca);
}

void sdio_pio_write (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t data_size)
{
  uint32_t* _buff = (uint32_t*) sys_mem_addr;
  uint32_t _status, _argument;

  int i;

  IOWR_32_SRS (SD_REG_SRS1, (1<<BCCT) | data_size);  // data size
  _argument = data_size | (reg_addr << 9) | (op_code << 26) | (func_num << 28) | (1 << 31);

  sd_host_send_cmd_int( ((53 << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) ), _argument);
  while( ((IORD_32_SRS(SD_REG_SRS9) >> BWE ) & 0x01) == 0 ); // wait for BWE
  for (i=0; i<(data_size/4); i++) {
    IOWR_32_SRS(SD_REG_SRS8, _buff[i]);  // send 4B of data
  }

  //do {
  //  _status = IORD_32_SRS(SD_REG_SRS12);
  //} while ((_status & (1<<TC) ) == 0); // exit loop when TC (transfer complete) flag is set to 1
}

void sdio_pio_read (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t data_size) {
  uint32_t* _buff = (uint32_t*) sys_mem_addr;
  uint32_t _status, _argument;

  int i;

  printf("data_size=%d\n",data_size);
  IOWR_32_SRS (SD_REG_SRS1, (1<<BCCT) | data_size);  // data size
  _argument = data_size | (reg_addr << 9) | (op_code << 26) | (func_num << 28);

  sd_host_send_cmd_int( ((53 << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) | (1 << DTDS)), _argument );
  //while( ((IORD_32_SRS(SD_REG_SRS9) >> BRE ) & 0x01) == 0 ); // wait for BRE
  //for (i=0; i<(data_size/4); i++) {
  //  _buff[i] = IORD_32_SRS (SD_REG_SRS8);  // send 4B of data
  //  sd_printf("_buff[%d]=%x\n",i,_buff[i]);
  //}
  //do {
  //  _status = IORD_32_SRS(SD_REG_SRS12);
  //} while ((_status & (1<<TC) ) == 0); // exit loop when TC (transfer complete) flag is set to 1

}

void sdio_dma_write (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t block_cnt, char use_adma2, char use_intr) {
  uint32_t _status, _argument;
  long _dma_addr;

  _dma_addr = (long)sys_mem_addr; // start address

  IOWR_32_SRS (SD_REG_SRS0, _dma_addr);  // system memory address
  IOWR_32_SRS (SD_REG_SRS1, (7 << HDMABB) | (block_cnt << BCCT) | SD_HOST_BLOCK_SIZE); // data size (block_cnt * SD_HOST_BLOCK_SIZE)

  // DMASEL = 0 - SDMA, DMASEL = 2 - ADMA2
  _status = IORD_32_SRS(SD_REG_SRS10);
  _status &= ~(3 << DMASEL);
  if (use_adma2 == 1) _status |= (2 << DMASEL); // ADMA2
  IOWR_32_SRS (SD_REG_SRS10, _status);        // DMASEL

  // Start transfer
  _status = ((53 << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) | (1 << MSBS) | (1 << DMAE));
  if (use_adma2 == 0) _status |= (1 << BCE);  // specified blocks count
  _argument = block_cnt | (reg_addr << 9) | (op_code << 26) | (1 << 27) | (func_num << 28) | (1 << 31);

  sd_host_send_cmd( _status, _argument );

  // xil_printf("_status = 0x%x\r\n", _status);
  //if (use_intr == 0) {
  //  do {
  //    _status = IORD_32_SRS(SD_REG_SRS12);
  //    if ( _status & (1<<DINT) ) {              //if DMAINT...
  //      _dma_addr = IORD_32_SRS(SD_REG_SRS0);
  //      IOWR_32_SRS (SD_REG_SRS12, (1<<DINT));  // clear DINT flag
  //      IOWR_32_SRS (SD_REG_SRS0, _dma_addr);   // resume transmission with new system address
  //    }
  //  } while ((_status & (1<<TC) ) == 0); // exit loop when TC (transfer complete) flag is set to 1
  //}
}

void sdio_dma_read (uint8_t func_num, uint32_t reg_addr, uint8_t op_code, uint8_t* sys_mem_addr, uint32_t block_cnt, char use_adma2, char use_intr) {
  uint32_t _status, _argument;
  long _dma_addr;

  _dma_addr = (long)sys_mem_addr; // start address

  IOWR_32_SRS (SD_REG_SRS0, _dma_addr);  // system memory address
  IOWR_32_SRS (SD_REG_SRS1, (7 << HDMABB) | (block_cnt << BCCT) | SD_HOST_BLOCK_SIZE); // data size (block_cnt * SD_HOST_BLOCK_SIZE)

  // DMASEL = 0 - SDMA, DMASEL = 2 - ADMA2
  _status = IORD_32_SRS(SD_REG_SRS10);
  _status &= ~(3 << DMASEL);
  if (use_adma2 == 1) _status |= (2 << DMASEL); // ADMA2
  IOWR_32_SRS (SD_REG_SRS10, _status);          // DMASEL

  // Start transfer - SRS3: direction read (CI, DTDS), CT|DPS|CICE|CRCE=00|1|1|1, Response type (RTS = 10b), MSMS=1, ACE | BCE| DMAE = 01|1|1
  _status = ((53 << CI) | (1 << DPS) | (3 << CRCCE) | (2 << RTS) | (1 << MSBS) | (1 << DTDS) | (1 << DMAE));
  if (use_adma2 == 0) _status |= (1 << BCE);  // specified blocks count
  _argument = block_cnt | (reg_addr << 9) | (op_code << 26) | (1 << 27) | (func_num << 28);

  sd_host_send_cmd( _status, _argument );

  //if (use_intr == 0) {
  //  do {
  //    _status = IORD_32_SRS(SD_REG_SRS12);
  //    if ( _status & (1<<DINT) ) {                //if DMAINT...
  //      _dma_addr = IORD_32_SRS(SD_REG_SRS0);
  //      // xil_printf("_dma_addr = 0x%x\r\n", _dma_addr);
  //      IOWR_32_SRS (SD_REG_SRS12, (1<<DINT));    // clear DINT flag
  //      IOWR_32_SRS (SD_REG_SRS0, _dma_addr);     // resume transmission
  //    }
  //  } while ((_status & (1<<TC) ) == 0); // exit loop when TC (transfer complete) flag is set to 1
  //}
}

int sdio_set_mode (char bit_width, char mode) {
  /*
   *  bit_width:  1 or 4 (UHS-I mode support only 4 bit data transmission)
   *  mode:
   *      0 - Default mode / UHS-I SDR12
   *      1 - High Speed mode / UHS-I SDR25
   *      2 - UHS-I SDR50
   *      3 - UHS-I SDR104
   *      4 - UHS-I DDR50
   */

  uint8_t _bit_width;
  uint32_t _status;


  printf("Set bit width to %d\r\n", bit_width);

  switch (bit_width) {
    case 1: _bit_width = 0x00; break;  // bus width 1 = 2^0;
    // case 2: _bit_width = 0x01; break;  // bus width 2 = 2^1;
    case 4: _bit_width = 0x02; break;  // bus width 4 = 2^2;
    // case 8: _bit_width = 0x03; break;  // bus width 8 = 2^3;
    default: printf("ERROR: wrong bit width selected\r\n"); return 1;
  }

  // set bus width
  sdio_write_reg(0, SDIO_CCCR_BUS_CTRL, (1 << SDIO_CCCR_F_CDD) | (_bit_width << SDIO_CCCR_F_BW)); // write to IO Enable register

  _status = IORD_32_SRS(SD_REG_SRS10);
  if (_bit_width>0) {
    _status |= (1<<DTW);  // enable DTW in SD host
  } else {
    _status &= ~(1<<DTW); // disable DTW in SD host
  }
  IOWR_32_SRS (SD_REG_SRS10, _status);

  printf("Set work mode: %d\r\n", mode);

  // set bus speed mode
  sdio_write_reg(0, SDIO_CCCR_SPEEDSEL, (mode << SDIO_CCCR_F_BSS)); // write to IO Enable register

  _status = IORD_32_SRS(SD_REG_SRS10);
  if (mode>0) {
    _status |= (1<<HSE);  // enable HSE in SD host
  } else {
    _status &= ~(1<<HSE); // disable HSE in SD host
  }
  IOWR_32_SRS (SD_REG_SRS10, _status);

  _status = IORD_32_SRS(SD_REG_SRS15);
  _status |= (mode << 16);
  IOWR_32_SRS (SD_REG_SRS15, _status);

  return 0;

}