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
/*
 * cnds_dsi_test.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Administrator
 */
#include "video/mipi/dsi/cnds_dsi_define.h"
#include "video/mipi/dsi/cnds_dsi_hw.h"
#include <sleep.h>
#include <stdio.h>
#include <stdio.h>
#include <io.h>
#include "sysctl_clk.h"
#include "sysctl_rst.h"
/**
 * @brief 
 * 
 */
void wait_phy_pll_locked()
{
    while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x01) == 0x01)
          {     break;}
	 }
}
/**
 * @brief 
 * 
 */
 void wait_cklane_rdy()
{
    while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x02) == 0x02)
          {     break;}
    }
 }
/**
 * @brief 
 * 
 */
 void wait_dat1_rdy()
 {
    while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x04) == 0x04)
          {     break;}
    }
  }
/**
 * @brief 
 * 
 */
 void wait_dat2_rdy()
 {
    while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x08) == 0x08)
          {     break;}
    }
 }
/**
 * @brief 
 * 
 */
 void wait_dat3_rdy()
 {
    while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x10) == 0x10)
          {     break;}
    }
 }
/**
 * @brief 
 * 
 */
 void wait_dat4_rdy()
 {
     while (1)
	 {
         if ((DsiRegRd(MCTL_MAIN_STS_OFFSET) & 0x20) == 0x20)
          {     break;}
    }
 }
/**
 * @brief 
 * 
 */
void  dsc_cmd_send(int par, int data1, int data2)
{
        int cmd_sts =0;
        if(par == 0)
        {
//                DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
                DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01020500); //[24] cmd_lp_en  =1
                                                                                //[23:14] cmd_size  =cmd_size. 1 or 2           2
                                                                                //[13:8] cmd_head  =0x39
                                                                                //[3 ] cmd_longnotshort  =0x1
                                                                                //[2:0] cmd_nat : 3'b000:write command
                                                                                //                3'b001:read command
                                                                                //                3'b100:TE request
                                                                                //                3'b101:trigger request
                                                                                //                3'b110:BTA request
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,data1);// DATA
                DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
                while((cmd_sts & 0x02 )!= 0x02)
                {
                        cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
                }
                DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
         }
        else  if(par == 1)
        {
                //DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x02) //[1]enable  write_completed_en
                DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01011500); //[24] cmd_lp_en  =1
                                                                        //[23:14] cmd_size  =cmd_size. 1 or 2
                                                                        //[13:8] cmd_head  =0x39
                                                                        //[3 ] cmd_longnotshort  =0x1
                                                                        //[2:0] cmd_nat : 3'b000:write command
                                                                        //                3'b001:read command
                                                                        //                3'b100:TE request
                                                                        //                3'b101:trigger request
                                                                        //                3'b110:BTA request
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
                DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
                while((cmd_sts & 0x02) != 0x02)
                { 
                        cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
                }
                DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
        }
        else if(par == 2)
        {
                DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01023908); //[24] cmd_lp_en  =1              0x01023908
                                                                        //[23:14] cmd_size  =cmd_size. 1 or 2
                                                                        //[13:8] cmd_head  =0x39
                                                                        //[3 ] cmd_longnotshort  =0x1
                                                                        //[2:0] cmd_nat : 3'b000:write command
                                                                        //                3'b001:read command
                                                                        //                3'b100:TE request
                                                                        //                3'b101:trigger request
                                                                        //                3'b110:BTA request
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data2<<8)+data1));// DATA
                DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
                while((cmd_sts & 0x02 )!= 0x02)
                {  
                        cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);              
                }
                DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed

        }

}
/**
 * @brief 
 * 
 */
void dsc_cmd_read(int addr)
{
        int cmd_sts =0;
        int data = 0;
        int size;
        int err;
        int reg = 0;

        DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);
        DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);

        DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01010601);           //[24] cmd_lp_en  =1            0x01010601        
                                                                        //[23:16] cmd_size  =cmd_size. 1 or 2                   
                                                                        //[14:15] cmd_type  0 write  1 read                     1           
                                                                        //[13:8] cmd_head  =0x5                                 6            
                                                                        //[3 ] cmd_longnotshort  =0x1                           1
                                                                        //[2:0] cmd_nat : 3'b000:write command                  01
                                                                        //                3'b001:read command
                                                                        //                3'b100:TE request
                                                                        //                3'b101:trigger request
                                                                        //                3'b110:BTA request   
        
        DsiRegWr(DIRECT_CMD_WRDAT_OFFSET, addr);

        DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff); // cmd send   


        while((cmd_sts & 0x08 )!= 0x08)                                 //wait read success
        {  
                cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);              
        }

        err = DsiRegRd(DIRECT_CMD_RD_STS_OFFSET);                   //read err
        size = DsiRegRd(DIRECT_CMD_RD_PROPERTY_OFFSET);             // read size [16 - 23]   
        data = DsiRegRd(DIRECT_CMD_RDDAT_OFFSET);                   //read data ;

        printf("err is 0x%8x, size is 0x%8x, data is 0x%8x \n", err, size, data);

}
/**
 * @brief 
 * 
 */
void  aml_lcd_init()
{
        DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0);//0x02); //[1]enable  write_completed_en
        printf("lcd init 1\n");

        dsc_cmd_send(2,0xFF,0x01);       
        
        dsc_cmd_read(0x0d);

        printf("lcd init 2\n");
        
        dsc_cmd_send(2,0xFB,0x01);
        
        printf("lcd init 3\n");

        dsc_cmd_send(2,0xFF,0x02);
        printf("lcd init 4\n");

        dsc_cmd_send(2,0xFB,0x01);
        printf("lcd init 5\n");

        
        dsc_cmd_send(2,0xFF,0x03);

        printf("lcd init 6\n");
        dsc_cmd_send(2,0xFB,0x01);
        printf("lcd init 7\n");

        dsc_cmd_send(2,0xFF,0x04);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0xFF,0x05);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0xD7,0x31);
        dsc_cmd_send(2,0xD8,0x7E);
        //Delay(100);
#ifndef _SIMU        
        msleep(100);
#endif
        dsc_cmd_send(2,0xFF,0x00);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0xBA,0x03);
        dsc_cmd_send(2,0x36,0x00);
        dsc_cmd_send(2,0xB0,0x00);
        dsc_cmd_send(2,0xD3,0x08);
        dsc_cmd_send(2,0xD4,0x0E);
        dsc_cmd_send(2,0xD5,0x0F);
        dsc_cmd_send(2,0xD6,0x48);
        dsc_cmd_send(2,0xD7,0x00);
        dsc_cmd_send(2,0xD9,0x00);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0xFF,0xEE);
        dsc_cmd_send(2,0x40,0x00);
        dsc_cmd_send(2,0x41,0x00);
        dsc_cmd_send(2,0x42,0x00);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0xFF,0x01);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0x01,0x55);
        dsc_cmd_send(2,0x04,0x0C);
        dsc_cmd_send(2,0x05,0x3A);
        dsc_cmd_send(2,0x06,0x50);
        dsc_cmd_send(2,0x07,0xD0);
        dsc_cmd_send(2,0x0A,0x0F);
        dsc_cmd_send(2,0x0C,0x06);
        dsc_cmd_send(2,0x0D,0x7F);
        dsc_cmd_send(2,0x0E,0x7F);
        dsc_cmd_send(2,0x0F,0x70);
        dsc_cmd_send(2,0x10,0x63);
        dsc_cmd_send(2,0x11,0x3C);
        dsc_cmd_send(2,0x12,0x5C);
        dsc_cmd_send(2,0x13,0x5A);
        dsc_cmd_send(2,0x14,0x5A);
        dsc_cmd_send(2,0x15,0x60);
        dsc_cmd_send(2,0x16,0x15);
        dsc_cmd_send(2,0x17,0x15);
        dsc_cmd_send(2,0x23,0x00);
        dsc_cmd_send(2,0x24,0x00);
        dsc_cmd_send(2,0x25,0x00);
        dsc_cmd_send(2,0x26,0x00);
        dsc_cmd_send(2,0x27,0x00);
        dsc_cmd_send(2,0x28,0x00);
        dsc_cmd_send(2,0x44,0x00);
        dsc_cmd_send(2,0x45,0x00);
        dsc_cmd_send(2,0x46,0x00);
        dsc_cmd_send(2,0x5B,0xCA);
        dsc_cmd_send(2,0x5C,0x00);
        dsc_cmd_send(2,0x5D,0x00);
        dsc_cmd_send(2,0x5E,0x2D);
        dsc_cmd_send(2,0x5F,0x1B);
        dsc_cmd_send(2,0x60,0xD5);
        dsc_cmd_send(2,0x61,0xF7);
        dsc_cmd_send(2,0x6C,0xAB);
        dsc_cmd_send(2,0x6D,0x44);
        //dsc_cmd_send(2,0x6E,0x80);
        dsc_cmd_send(2,0xFF,0x05);
        dsc_cmd_send(2,0xFB,0x01);
        dsc_cmd_send(2,0x00,0x3F);
        dsc_cmd_send(2,0x01,0x3F);
        dsc_cmd_send(2,0x02,0x3F);
        dsc_cmd_send(2,0x03,0x3F);
        dsc_cmd_send(2,0x04,0x38);
        dsc_cmd_send(2,0x05,0x3F);
        dsc_cmd_send(2,0x06,0x3F);
        dsc_cmd_send(2,0x07,0x19);
        dsc_cmd_send(2,0x08,0x1D);
        dsc_cmd_send(2,0x09,0x3F);
        dsc_cmd_send(2,0x0A,0x3F);
        dsc_cmd_send(2,0x0B,0x1B);
        dsc_cmd_send(2,0x0C,0x17);
        dsc_cmd_send(2,0x0D,0x3F);
        dsc_cmd_send(2,0x0E,0x3F);
        dsc_cmd_send(2,0x0F,0x08);
        dsc_cmd_send(2,0x10,0x3F);
        dsc_cmd_send(2,0x11,0x10);
        dsc_cmd_send(2,0x12,0x3F);
        dsc_cmd_send(2,0x13,0x3F);
        dsc_cmd_send(2,0x14,0x3F);
        dsc_cmd_send(2,0x15,0x3F);
        dsc_cmd_send(2,0x16,0x3F);
        dsc_cmd_send(2,0x17,0x3F);
        dsc_cmd_send(2,0x18,0x38);
        dsc_cmd_send(2,0x19,0x18);
        dsc_cmd_send(2,0x1A,0x1C);
        dsc_cmd_send(2,0x1B,0x3F);
        dsc_cmd_send(2,0x1C,0x3F);
        dsc_cmd_send(2,0x1D,0x1A);
        dsc_cmd_send(2,0x1E,0x16);
        dsc_cmd_send(2,0x1F,0x3F);
        dsc_cmd_send(2,0x20,0x3F);
        dsc_cmd_send(2,0x21,0x3F);
        dsc_cmd_send(2,0x22,0x3F);
        dsc_cmd_send(2,0x23,0x06);
        dsc_cmd_send(2,0x24,0x3F);
        dsc_cmd_send(2,0x25,0x0E);
        dsc_cmd_send(2,0x26,0x3F);
        dsc_cmd_send(2,0x27,0x3F);
        dsc_cmd_send(2,0x54,0x06);
        dsc_cmd_send(2,0x55,0x05);
        dsc_cmd_send(2,0x56,0x04);
        dsc_cmd_send(2,0x58,0x03);
        dsc_cmd_send(2,0x59,0x1B);
        dsc_cmd_send(2,0x5A,0x1B);
        dsc_cmd_send(2,0x5B,0x01);
        dsc_cmd_send(2,0x5C,0x32);
        dsc_cmd_send(2,0x5E,0x18);
        dsc_cmd_send(2,0x5F,0x20);
        dsc_cmd_send(2,0x60,0x2B);
        dsc_cmd_send(2,0x61,0x2C);
        dsc_cmd_send(2,0x62,0x18);
        dsc_cmd_send(2,0x63,0x01);
        dsc_cmd_send(2,0x64,0x32);
        dsc_cmd_send(2,0x65,0x00);
        dsc_cmd_send(2,0x66,0x44);
        dsc_cmd_send(2,0x67,0x11);
        dsc_cmd_send(2,0x68,0x01);
        dsc_cmd_send(2,0x69,0x01);
        dsc_cmd_send(2,0x6A,0x04);
        dsc_cmd_send(2,0x6B,0x2C);
        dsc_cmd_send(2,0x6C,0x08);
        dsc_cmd_send(2,0x6D,0x08);
        dsc_cmd_send(2,0x78,0x00);
        dsc_cmd_send(2,0x79,0x00);
        dsc_cmd_send(2,0x7E,0x00);
        dsc_cmd_send(2,0x7F,0x00);
        dsc_cmd_send(2,0x80,0x00);
        dsc_cmd_send(2,0x81,0x00);
        dsc_cmd_send(2,0x8D,0x00);
        dsc_cmd_send(2,0x8E,0x00);
        dsc_cmd_send(2,0x8F,0xC0);
        dsc_cmd_send(2,0x90,0x73);
        dsc_cmd_send(2,0x91,0x10);
        dsc_cmd_send(2,0x92,0x07);
        dsc_cmd_send(2,0x96,0x11);
        dsc_cmd_send(2,0x97,0x14);
        dsc_cmd_send(2,0x98,0x00);
        dsc_cmd_send(2,0x99,0x00);
        dsc_cmd_send(2,0x9A,0x00);
        dsc_cmd_send(2,0x9B,0x61);
        dsc_cmd_send(2,0x9C,0x15);
        dsc_cmd_send(2,0x9D,0x30);
        dsc_cmd_send(2,0x9F,0x0F);
        dsc_cmd_send(2,0xA2,0xB0);
        dsc_cmd_send(2,0xA7,0x0A);
        dsc_cmd_send(2,0xA9,0x00);
        dsc_cmd_send(2,0xAA,0x70);
        dsc_cmd_send(2,0xAB,0xDA);
        dsc_cmd_send(2,0xAC,0xFF);
        dsc_cmd_send(2,0xAE,0xF4);
        dsc_cmd_send(2,0xAF,0x40);
        dsc_cmd_send(2,0xB0,0x7F);
        dsc_cmd_send(2,0xB1,0x16);
        dsc_cmd_send(2,0xB2,0x53);
        dsc_cmd_send(2,0xB3,0x00);
        dsc_cmd_send(2,0xB4,0x2A);
        dsc_cmd_send(2,0xB5,0x3A);
        dsc_cmd_send(2,0xB6,0xF0);
        dsc_cmd_send(2,0xBC,0x85);
        dsc_cmd_send(2,0xBD,0xF4);
        dsc_cmd_send(2,0xBE,0x33);
        dsc_cmd_send(2,0xBF,0x13);
        dsc_cmd_send(2,0xC0,0x77);
        dsc_cmd_send(2,0xC1,0x77);
        dsc_cmd_send(2,0xC2,0x77);
        dsc_cmd_send(2,0xC3,0x77);
        dsc_cmd_send(2,0xC4,0x77);
        dsc_cmd_send(2,0xC5,0x77);
        dsc_cmd_send(2,0xC6,0x77);
        dsc_cmd_send(2,0xC7,0x77);
        dsc_cmd_send(2,0xC8,0xAA);
        dsc_cmd_send(2,0xC9,0x2A);
        dsc_cmd_send(2,0xCA,0x00);
        dsc_cmd_send(2,0xCB,0xAA);
        dsc_cmd_send(2,0xCC,0x92);
        dsc_cmd_send(2,0xCD,0x00);
        dsc_cmd_send(2,0xCE,0x18);
        dsc_cmd_send(2,0xCF,0x88);
        dsc_cmd_send(2,0xD0,0xAA);
        dsc_cmd_send(2,0xD1,0x00);
        dsc_cmd_send(2,0xD2,0x00);
        dsc_cmd_send(2,0xD3,0x00);
        dsc_cmd_send(2,0xD6,0x02);
        dsc_cmd_send(2,0xED,0x00);
        dsc_cmd_send(2,0xEE,0x00);
        dsc_cmd_send(2,0xEF,0x70);
        dsc_cmd_send(2,0xFA,0x03);
        dsc_cmd_send(2,0xFF,0x00);

        ////page selection cmd start
        dsc_cmd_send(2,0xFF,0x01);
        dsc_cmd_send(2,0xFB,0x01);
        ////page selection cmd end
        ////R(+) MCR cmd
        dsc_cmd_send(2,0x75,0x00);
        dsc_cmd_send(2,0x76,0x00);
        dsc_cmd_send(2,0x77,0x00);
        dsc_cmd_send(2,0x78,0x2C);
        dsc_cmd_send(2,0x79,0x00);
        dsc_cmd_send(2,0x7A,0x4F);
        dsc_cmd_send(2,0x7B,0x00);
        dsc_cmd_send(2,0x7C,0x69);
        dsc_cmd_send(2,0x7D,0x00);
        dsc_cmd_send(2,0x7E,0x7F);
        dsc_cmd_send(2,0x7F,0x00);
        dsc_cmd_send(2,0x80,0x92);
        dsc_cmd_send(2,0x81,0x00);
        dsc_cmd_send(2,0x82,0xA3);
        dsc_cmd_send(2,0x83,0x00);
        dsc_cmd_send(2,0x84,0xB3);
        dsc_cmd_send(2,0x85,0x00);
        dsc_cmd_send(2,0x86,0xC1);
        dsc_cmd_send(2,0x87,0x00);
        dsc_cmd_send(2,0x88,0xF3);
        dsc_cmd_send(2,0x89,0x01);
        dsc_cmd_send(2,0x8A,0x1B);
        dsc_cmd_send(2,0x8B,0x01);
        dsc_cmd_send(2,0x8C,0x5A);
        dsc_cmd_send(2,0x8D,0x01);
        dsc_cmd_send(2,0x8E,0x8B);
        dsc_cmd_send(2,0x8F,0x01);
        dsc_cmd_send(2,0x90,0xD9);
        dsc_cmd_send(2,0x91,0x02);
        dsc_cmd_send(2,0x92,0x16);
        dsc_cmd_send(2,0x93,0x02);
        dsc_cmd_send(2,0x94,0x18);
        dsc_cmd_send(2,0x95,0x02);
        dsc_cmd_send(2,0x96,0x4E);
        dsc_cmd_send(2,0x97,0x02);
        dsc_cmd_send(2,0x98,0x88);
        dsc_cmd_send(2,0x99,0x02);
        dsc_cmd_send(2,0x9A,0xAC);
        dsc_cmd_send(2,0x9B,0x02);
        dsc_cmd_send(2,0x9C,0xDD);
        dsc_cmd_send(2,0x9D,0x03);
        dsc_cmd_send(2,0x9E,0x01);
        dsc_cmd_send(2,0x9F,0x03);
        dsc_cmd_send(2,0xA0,0x2E);
        dsc_cmd_send(2,0xA2,0x03);
        dsc_cmd_send(2,0xA3,0x3C);
        dsc_cmd_send(2,0xA4,0x03);
        dsc_cmd_send(2,0xA5,0x4C);
        dsc_cmd_send(2,0xA6,0x03);
        dsc_cmd_send(2,0xA7,0x5D);
        dsc_cmd_send(2,0xA9,0x03);
        dsc_cmd_send(2,0xAA,0x70);
        dsc_cmd_send(2,0xAB,0x03);
        dsc_cmd_send(2,0xAC,0x88);
        dsc_cmd_send(2,0xAD,0x03);
        dsc_cmd_send(2,0xAE,0xA8);
        dsc_cmd_send(2,0xAF,0x03);
        dsc_cmd_send(2,0xB0,0xC8);
        dsc_cmd_send(2,0xB1,0x03);
        dsc_cmd_send(2,0xB2,0xFF);
        ////R(-) MCR cmd
        dsc_cmd_send(2,0xB3,0x00);
        dsc_cmd_send(2,0xB4,0x00);
        dsc_cmd_send(2,0xB5,0x00);
        dsc_cmd_send(2,0xB6,0x2C);
        dsc_cmd_send(2,0xB7,0x00);
        dsc_cmd_send(2,0xB8,0x4F);
        dsc_cmd_send(2,0xB9,0x00);
        dsc_cmd_send(2,0xBA,0x69);
        dsc_cmd_send(2,0xBB,0x00);
        dsc_cmd_send(2,0xBC,0x7F);
        dsc_cmd_send(2,0xBD,0x00);
        dsc_cmd_send(2,0xBE,0x92);
        dsc_cmd_send(2,0xBF,0x00);
        dsc_cmd_send(2,0xC0,0xA3);
        dsc_cmd_send(2,0xC1,0x00);
        dsc_cmd_send(2,0xC2,0xB3);
        dsc_cmd_send(2,0xC3,0x00);
        dsc_cmd_send(2,0xC4,0xC1);
        dsc_cmd_send(2,0xC5,0x00);
        dsc_cmd_send(2,0xC6,0xF3);
        dsc_cmd_send(2,0xC7,0x01);
        dsc_cmd_send(2,0xC8,0x1B);
        dsc_cmd_send(2,0xC9,0x01);
        dsc_cmd_send(2,0xCA,0x5A);
        dsc_cmd_send(2,0xCB,0x01);
        dsc_cmd_send(2,0xCC,0x8B);
        dsc_cmd_send(2,0xCD,0x01);
        dsc_cmd_send(2,0xCE,0xD9);
        dsc_cmd_send(2,0xCF,0x02);
        dsc_cmd_send(2,0xD0,0x16);
        dsc_cmd_send(2,0xD1,0x02);
        dsc_cmd_send(2,0xD2,0x18);
        dsc_cmd_send(2,0xD3,0x02);
        dsc_cmd_send(2,0xD4,0x4E);
        dsc_cmd_send(2,0xD5,0x02);
        dsc_cmd_send(2,0xD6,0x88);
        dsc_cmd_send(2,0xD7,0x02);
        dsc_cmd_send(2,0xD8,0xAC);
        dsc_cmd_send(2,0xD9,0x02);
        dsc_cmd_send(2,0xDA,0xDD);
        dsc_cmd_send(2,0xDB,0x03);
        dsc_cmd_send(2,0xDC,0x01);
        dsc_cmd_send(2,0xDD,0x03);
        dsc_cmd_send(2,0xDE,0x2E);
        dsc_cmd_send(2,0xDF,0x03);
        dsc_cmd_send(2,0xE0,0x3C);
        dsc_cmd_send(2,0xE1,0x03);
        dsc_cmd_send(2,0xE2,0x4C);
        dsc_cmd_send(2,0xE3,0x03);
        dsc_cmd_send(2,0xE4,0x5D);
        dsc_cmd_send(2,0xE5,0x03);
        dsc_cmd_send(2,0xE6,0x70);
        dsc_cmd_send(2,0xE7,0x03);
        dsc_cmd_send(2,0xE8,0x88);
        dsc_cmd_send(2,0xE9,0x03);
        dsc_cmd_send(2,0xEA,0xA8);
        dsc_cmd_send(2,0xEB,0x03);
        dsc_cmd_send(2,0xEC,0xC8);
        dsc_cmd_send(2,0xED,0x03);
        dsc_cmd_send(2,0xEE,0xFF);
        ////G(+) MCR cmd
        dsc_cmd_send(2,0xEF,0x00);
        dsc_cmd_send(2,0xF0,0x00);
        dsc_cmd_send(2,0xF1,0x00);
        dsc_cmd_send(2,0xF2,0x2C);
        dsc_cmd_send(2,0xF3,0x00);
        dsc_cmd_send(2,0xF4,0x4F);
        dsc_cmd_send(2,0xF5,0x00);
        dsc_cmd_send(2,0xF6,0x69);
        dsc_cmd_send(2,0xF7,0x00);
        dsc_cmd_send(2,0xF8,0x7F);
        dsc_cmd_send(2,0xF9,0x00);
        dsc_cmd_send(2,0xFA,0x92);
        ////page selection cmd start
        dsc_cmd_send(2,0xFF,0x02);
        dsc_cmd_send(2,0xFB,0x01);
        ////page selection cmd end
        dsc_cmd_send(2,0x00,0x00);
        dsc_cmd_send(2,0x01,0xA3);
        dsc_cmd_send(2,0x02,0x00);
        dsc_cmd_send(2,0x03,0xB3);
        dsc_cmd_send(2,0x04,0x00);
        dsc_cmd_send(2,0x05,0xC1);
        dsc_cmd_send(2,0x06,0x00);
        dsc_cmd_send(2,0x07,0xF3);
        dsc_cmd_send(2,0x08,0x01);
        dsc_cmd_send(2,0x09,0x1B);
        dsc_cmd_send(2,0x0A,0x01);
        dsc_cmd_send(2,0x0B,0x5A);
        dsc_cmd_send(2,0x0C,0x01);
        dsc_cmd_send(2,0x0D,0x8B);
        dsc_cmd_send(2,0x0E,0x01);
        dsc_cmd_send(2,0x0F,0xD9);
        dsc_cmd_send(2,0x10,0x02);
        dsc_cmd_send(2,0x11,0x16);
        dsc_cmd_send(2,0x12,0x02);
        dsc_cmd_send(2,0x13,0x18);
        dsc_cmd_send(2,0x14,0x02);
        dsc_cmd_send(2,0x15,0x4E);
        dsc_cmd_send(2,0x16,0x02);
        dsc_cmd_send(2,0x17,0x88);
        dsc_cmd_send(2,0x18,0x02);
        dsc_cmd_send(2,0x19,0xAC);
        dsc_cmd_send(2,0x1A,0x02);
        dsc_cmd_send(2,0x1B,0xDD);
        dsc_cmd_send(2,0x1C,0x03);
        dsc_cmd_send(2,0x1D,0x01);
        dsc_cmd_send(2,0x1E,0x03);
        dsc_cmd_send(2,0x1F,0x2E);
        dsc_cmd_send(2,0x20,0x03);
        dsc_cmd_send(2,0x21,0x3C);
        dsc_cmd_send(2,0x22,0x03);
        dsc_cmd_send(2,0x23,0x4C);
        dsc_cmd_send(2,0x24,0x03);
        dsc_cmd_send(2,0x25,0x5D);
        dsc_cmd_send(2,0x26,0x03);
        dsc_cmd_send(2,0x27,0x70);
        dsc_cmd_send(2,0x28,0x03);
        dsc_cmd_send(2,0x29,0x88);
        dsc_cmd_send(2,0x2A,0x03);
        dsc_cmd_send(2,0x2B,0xA8);
        dsc_cmd_send(2,0x2D,0x03);
        dsc_cmd_send(2,0x2F,0xC8);
        dsc_cmd_send(2,0x30,0x03);
        dsc_cmd_send(2,0x31,0xFF);
        ////G(-) MCR cmd
        dsc_cmd_send(2,0x32,0x00);
        dsc_cmd_send(2,0x33,0x00);
        dsc_cmd_send(2,0x34,0x00);
        dsc_cmd_send(2,0x35,0x2C);
        dsc_cmd_send(2,0x36,0x00);
        dsc_cmd_send(2,0x37,0x4F);
        dsc_cmd_send(2,0x38,0x00);
        dsc_cmd_send(2,0x39,0x69);
        dsc_cmd_send(2,0x3A,0x00);
        dsc_cmd_send(2,0x3B,0x7F);
        dsc_cmd_send(2,0x3D,0x00);
        dsc_cmd_send(2,0x3F,0x92);
        dsc_cmd_send(2,0x40,0x00);
        dsc_cmd_send(2,0x41,0xA3);
        dsc_cmd_send(2,0x42,0x00);
        dsc_cmd_send(2,0x43,0xB3);
        dsc_cmd_send(2,0x44,0x00);
        dsc_cmd_send(2,0x45,0xC1);
        dsc_cmd_send(2,0x46,0x00);
        dsc_cmd_send(2,0x47,0xF3);
        dsc_cmd_send(2,0x48,0x01);
        dsc_cmd_send(2,0x49,0x1B);
        dsc_cmd_send(2,0x4A,0x01);
        dsc_cmd_send(2,0x4B,0x5A);
        dsc_cmd_send(2,0x4C,0x01);
        dsc_cmd_send(2,0x4D,0x8B);
        dsc_cmd_send(2,0x4E,0x01);
        dsc_cmd_send(2,0x4F,0xD9);
        dsc_cmd_send(2,0x50,0x02);
        dsc_cmd_send(2,0x51,0x16);
        dsc_cmd_send(2,0x52,0x02);
        dsc_cmd_send(2,0x53,0x18);
        dsc_cmd_send(2,0x54,0x02);
        dsc_cmd_send(2,0x55,0x4E);
        dsc_cmd_send(2,0x56,0x02);
        dsc_cmd_send(2,0x58,0x88);
        dsc_cmd_send(2,0x59,0x02);
        dsc_cmd_send(2,0x5A,0xAC);
        dsc_cmd_send(2,0x5B,0x02);
        dsc_cmd_send(2,0x5C,0xDD);
        dsc_cmd_send(2,0x5D,0x03);
        dsc_cmd_send(2,0x5E,0x01);
        dsc_cmd_send(2,0x5F,0x03);
        dsc_cmd_send(2,0x60,0x2E);
        dsc_cmd_send(2,0x61,0x03);
        dsc_cmd_send(2,0x62,0x3C);
        dsc_cmd_send(2,0x63,0x03);
        dsc_cmd_send(2,0x64,0x4C);
        dsc_cmd_send(2,0x65,0x03);
        dsc_cmd_send(2,0x66,0x5D);
        dsc_cmd_send(2,0x67,0x03);
        dsc_cmd_send(2,0x68,0x70);
        dsc_cmd_send(2,0x69,0x03);
        dsc_cmd_send(2,0x6A,0x88);
        dsc_cmd_send(2,0x6B,0x03);
        dsc_cmd_send(2,0x6C,0xA8);
        dsc_cmd_send(2,0x6D,0x03);
        dsc_cmd_send(2,0x6E,0xC8);
        dsc_cmd_send(2,0x6F,0x03);
        dsc_cmd_send(2,0x70,0xFF);
        ////B(+) MCR cmd
        dsc_cmd_send(2,0x71,0x00);
        dsc_cmd_send(2,0x72,0x00);
        dsc_cmd_send(2,0x73,0x00);
        dsc_cmd_send(2,0x74,0x2C);
        dsc_cmd_send(2,0x75,0x00);
        dsc_cmd_send(2,0x76,0x4F);
        dsc_cmd_send(2,0x77,0x00);
        dsc_cmd_send(2,0x78,0x69);
        dsc_cmd_send(2,0x79,0x00);
        dsc_cmd_send(2,0x7A,0x7F);
        dsc_cmd_send(2,0x7B,0x00);
        dsc_cmd_send(2,0x7C,0x92);
        dsc_cmd_send(2,0x7D,0x00);
        dsc_cmd_send(2,0x7E,0xA3);
        dsc_cmd_send(2,0x7F,0x00);
        dsc_cmd_send(2,0x80,0xB3);
        dsc_cmd_send(2,0x81,0x00);
        dsc_cmd_send(2,0x82,0xC1);
        dsc_cmd_send(2,0x83,0x00);
        dsc_cmd_send(2,0x84,0xF3);
        dsc_cmd_send(2,0x85,0x01);
        dsc_cmd_send(2,0x86,0x1B);
        dsc_cmd_send(2,0x87,0x01);
        dsc_cmd_send(2,0x88,0x5A);
        dsc_cmd_send(2,0x89,0x01);
        dsc_cmd_send(2,0x8A,0x8B);
        dsc_cmd_send(2,0x8B,0x01);
        dsc_cmd_send(2,0x8C,0xD9);
        dsc_cmd_send(2,0x8D,0x02);
        dsc_cmd_send(2,0x8E,0x16);
        dsc_cmd_send(2,0x8F,0x02);
        dsc_cmd_send(2,0x90,0x18);
        dsc_cmd_send(2,0x91,0x02);
        dsc_cmd_send(2,0x92,0x4E);
        dsc_cmd_send(2,0x93,0x02);
        dsc_cmd_send(2,0x94,0x88);
        dsc_cmd_send(2,0x95,0x02);
        dsc_cmd_send(2,0x96,0xAC);
        dsc_cmd_send(2,0x97,0x02);
        dsc_cmd_send(2,0x98,0xDD);
        dsc_cmd_send(2,0x99,0x03);
        dsc_cmd_send(2,0x9A,0x01);
        dsc_cmd_send(2,0x9B,0x03);
        dsc_cmd_send(2,0x9C,0x2E);
        dsc_cmd_send(2,0x9D,0x03);
        dsc_cmd_send(2,0x9E,0x3C);
        dsc_cmd_send(2,0x9F,0x03);
        dsc_cmd_send(2,0xA0,0x4C);
        dsc_cmd_send(2,0xA2,0x03);
        dsc_cmd_send(2,0xA3,0x5D);
        dsc_cmd_send(2,0xA4,0x03);
        dsc_cmd_send(2,0xA5,0x70);
        dsc_cmd_send(2,0xA6,0x03);
        dsc_cmd_send(2,0xA7,0x88);
        dsc_cmd_send(2,0xA9,0x03);
        dsc_cmd_send(2,0xAA,0xA8);
        dsc_cmd_send(2,0xAB,0x03);
        dsc_cmd_send(2,0xAC,0xC8);
        dsc_cmd_send(2,0xAD,0x03);
        dsc_cmd_send(2,0xAE,0xFF);
        ////B(-) MCR cmd
        dsc_cmd_send(2,0xAF,0x00);
        dsc_cmd_send(2,0xB0,0x00);
        dsc_cmd_send(2,0xB1,0x00);
        dsc_cmd_send(2,0xB2,0x2C);
        dsc_cmd_send(2,0xB3,0x00);
        dsc_cmd_send(2,0xB4,0x4F);
        dsc_cmd_send(2,0xB5,0x00);
        dsc_cmd_send(2,0xB6,0x69);
        dsc_cmd_send(2,0xB7,0x00);
        dsc_cmd_send(2,0xB8,0x7F);
        dsc_cmd_send(2,0xB9,0x00);
        dsc_cmd_send(2,0xBA,0x92);
        dsc_cmd_send(2,0xBB,0x00);
        dsc_cmd_send(2,0xBC,0xA3);
        dsc_cmd_send(2,0xBD,0x00);
        dsc_cmd_send(2,0xBE,0xB3);
        dsc_cmd_send(2,0xBF,0x00);
        dsc_cmd_send(2,0xC0,0xC1);
        dsc_cmd_send(2,0xC1,0x00);
        dsc_cmd_send(2,0xC2,0xF3);
        dsc_cmd_send(2,0xC3,0x01);
        dsc_cmd_send(2,0xC4,0x1B);
        dsc_cmd_send(2,0xC5,0x01);
        dsc_cmd_send(2,0xC6,0x5A);
        dsc_cmd_send(2,0xC7,0x01);
        dsc_cmd_send(2,0xC8,0x8B);
        dsc_cmd_send(2,0xC9,0x01);
        dsc_cmd_send(2,0xCA,0xD9);
        dsc_cmd_send(2,0xCB,0x02);
        dsc_cmd_send(2,0xCC,0x16);
        dsc_cmd_send(2,0xCD,0x02);
        dsc_cmd_send(2,0xCE,0x18);
        dsc_cmd_send(2,0xCF,0x02);
        dsc_cmd_send(2,0xD0,0x4E);
        dsc_cmd_send(2,0xD1,0x02);
        dsc_cmd_send(2,0xD2,0x88);
        dsc_cmd_send(2,0xD3,0x02);
        dsc_cmd_send(2,0xD4,0xAC);
        dsc_cmd_send(2,0xD5,0x02);
        dsc_cmd_send(2,0xD6,0xDD);
        dsc_cmd_send(2,0xD7,0x03);
        dsc_cmd_send(2,0xD8,0x01);
        dsc_cmd_send(2,0xD9,0x03);
        dsc_cmd_send(2,0xDA,0x2E);
        dsc_cmd_send(2,0xDB,0x03);
        dsc_cmd_send(2,0xDC,0x3C);
        dsc_cmd_send(2,0xDD,0x03);
        dsc_cmd_send(2,0xDE,0x4C);
        dsc_cmd_send(2,0xDF,0x03);
        dsc_cmd_send(2,0xE0,0x5D);
        dsc_cmd_send(2,0xE1,0x03);
        dsc_cmd_send(2,0xE2,0x70);
        dsc_cmd_send(2,0xE3,0x03);
        dsc_cmd_send(2,0xE4,0x88);
        dsc_cmd_send(2,0xE5,0x03);
        dsc_cmd_send(2,0xE6,0xA8);
        dsc_cmd_send(2,0xE7,0x03);
        dsc_cmd_send(2,0xE8,0xC8);
        dsc_cmd_send(2,0xE9,0x03);
        dsc_cmd_send(2,0xEA,0xFF);

        dsc_cmd_send(2,0xFF,0x00);
        dsc_cmd_send(2,0xFB,0x01);

        dsc_cmd_send(2,0x11,0x00);

#ifndef _SIMU        
        msleep(100);
#endif
        dsc_cmd_send(2,0x29,0x00);
#ifndef _SIMU
        msleep(100) ;
#endif
};


#if 1
void  dsc_cmd_send_4(int data1, int data2, int data3,int data4)
{
	int cmd_sts =0;
	DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01043908); //[24] cmd_lp_en  =1    0x01043908
															//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
															//[13:8] cmd_head  =0x39
															//[3 ] cmd_longnotshort  =0x1
															//[2:0] cmd_nat : 3'b000:write command
															//                3'b001:read command
															//                3'b100:TE request
															//                3'b101:trigger request
															//                3'b110:BTA request
															
	DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((data4<<24) + (data3<<16) + (data2<<8) + data1));// DATA
	DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{  
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}

void ILI7807_lcd_init(void)
{
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x01);			// write page 1	
	dsc_cmd_send(2, 0x42, 0x11);
	dsc_cmd_send(2, 0x43, 0xB2);		//VGH_CLP = 11.0V
        dsc_cmd_read(0x43);
	dsc_cmd_send(2, 0x44, 0x94);		//VGL_CLP = -7.0V
	dsc_cmd_send(2, 0x4A, 0x15);
	dsc_cmd_send(2, 0x4B, 0x15);
	dsc_cmd_send(2, 0x50, 0x73);		//GVDDP = 5.3V
	dsc_cmd_send(2, 0x51, 0x73);		//GVDDN = - 5.3V
	dsc_cmd_send(2, 0x5A, 0x33);		//LVD
	dsc_cmd_send(2, 0xA0, 0x10);
	dsc_cmd_send(2, 0xA2, 0x01);		//VCOM1 = - 0.35V
	dsc_cmd_send(2, 0xA3, 0x22);		//VCOM1 = - 0.35V
	dsc_cmd_send(2, 0xB3, 0x60);
	dsc_cmd_send(2, 0xB4, 0x60);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x01);			// write page 1
	dsc_cmd_send(2, 0x22, 0x06);
	dsc_cmd_send(2, 0x36, 0x00);
	dsc_cmd_send(2, 0x60, 0x0A);
	dsc_cmd_send(2, 0x64, 0x08);
	dsc_cmd_send(2, 0x6C, 0x45);		//PRC & PRCB
	dsc_cmd_send(2, 0x35, 0x22);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x07);			// write page 7
	dsc_cmd_send(2, 0x37, 0x00);
	dsc_cmd_send(2, 0x12, 0x22);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x08);			// write page 8 for GIP

	dsc_cmd_send(2, 0x09, 0x0e);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x06);			// write page 8 for GIP
	dsc_cmd_send(2, 0x00, 0x42);
	dsc_cmd_send(2, 0x01, 0x04);
	dsc_cmd_send(2, 0x02, 0x0B);
	dsc_cmd_send(2, 0x03, 0x03);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x00);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x00);
	dsc_cmd_send(2, 0x08, 0x81);
	dsc_cmd_send(2, 0x09, 0x05);
	dsc_cmd_send(2, 0x0a, 0x70);
	dsc_cmd_send(2, 0x0b, 0x00);
	dsc_cmd_send(2, 0x0c, 0x0B);
	dsc_cmd_send(2, 0x0d, 0x0B);
	dsc_cmd_send(2, 0x0e, 0x03);
	dsc_cmd_send(2, 0x0f, 0x03);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x12, 0x00);
	dsc_cmd_send(2, 0x13, 0x00);
	dsc_cmd_send(2, 0x14, 0x00);
	dsc_cmd_send(2, 0x15, 0x00);
	dsc_cmd_send(2, 0x31, 0x22);
	dsc_cmd_send(2, 0x32, 0x27);
	dsc_cmd_send(2, 0x33, 0x07);
	dsc_cmd_send(2, 0x34, 0x08);
	dsc_cmd_send(2, 0x35, 0x10);
	dsc_cmd_send(2, 0x36, 0x16);
	dsc_cmd_send(2, 0x37, 0x14);
	dsc_cmd_send(2, 0x38, 0x12);
	dsc_cmd_send(2, 0x39, 0x07);
	dsc_cmd_send(2, 0x3a, 0x07);
	dsc_cmd_send(2, 0x3b, 0x07);
	dsc_cmd_send(2, 0x3c, 0x28);
	dsc_cmd_send(2, 0x3d, 0x29);
	dsc_cmd_send(2, 0x3e, 0x2a);
	dsc_cmd_send(2, 0x3f, 0x07);
	dsc_cmd_send(2, 0x40, 0x07);
	dsc_cmd_send(2, 0x41, 0x22);
	dsc_cmd_send(2, 0x42, 0x27);
	dsc_cmd_send(2, 0x43, 0x07);
	dsc_cmd_send(2, 0x44, 0x09);
	dsc_cmd_send(2, 0x45, 0x11);
	dsc_cmd_send(2, 0x46, 0x17);
	dsc_cmd_send(2, 0x47, 0x15);
	dsc_cmd_send(2, 0x48, 0x13);
	dsc_cmd_send(2, 0x49, 0x07);
	dsc_cmd_send(2, 0x4a, 0x07);
	dsc_cmd_send(2, 0x4b, 0x07);
	dsc_cmd_send(2, 0x4c, 0x28);
	dsc_cmd_send(2, 0x4d, 0x29);
	dsc_cmd_send(2, 0x4e, 0x2a);
	dsc_cmd_send(2, 0x4f, 0x07);
	dsc_cmd_send(2, 0x50, 0x07);
	dsc_cmd_send(2, 0x61, 0x22);
	dsc_cmd_send(2, 0x62, 0x27);
	dsc_cmd_send(2, 0x63, 0x07);
	dsc_cmd_send(2, 0x64, 0x09);
	dsc_cmd_send(2, 0x65, 0x13);
	dsc_cmd_send(2, 0x66, 0x15);
	dsc_cmd_send(2, 0x67, 0x17);
	dsc_cmd_send(2, 0x68, 0x11);
	dsc_cmd_send(2, 0x69, 0x07);
	dsc_cmd_send(2, 0x6a, 0x07);
	dsc_cmd_send(2, 0x6b, 0x07);
	dsc_cmd_send(2, 0x6c, 0x28);
	dsc_cmd_send(2, 0x6d, 0x29);
	dsc_cmd_send(2, 0x6e, 0x2a);
	dsc_cmd_send(2, 0x6f, 0x07);
	
	dsc_cmd_send(2, 0x70, 0x07);
	dsc_cmd_send(2, 0x71, 0x22);
	dsc_cmd_send(2, 0x72, 0x27);
	dsc_cmd_send(2, 0x73, 0x07);
	dsc_cmd_send(2, 0x74, 0x08);
	dsc_cmd_send(2, 0x75, 0x12);
	dsc_cmd_send(2, 0x76, 0x14);
	dsc_cmd_send(2, 0x77, 0x16);
	dsc_cmd_send(2, 0x78, 0x10);
	dsc_cmd_send(2, 0x79, 0x07);
	dsc_cmd_send(2, 0x7a, 0x07);
	dsc_cmd_send(2, 0x7b, 0x07);
	dsc_cmd_send(2, 0x7c, 0x28);
	dsc_cmd_send(2, 0x7d, 0x29);
	dsc_cmd_send(2, 0x7e, 0x2a);
	dsc_cmd_send(2, 0x7f, 0x07);
	dsc_cmd_send(2, 0x80, 0x07);
	
	dsc_cmd_send(2, 0xd0, 0x01);
	
	dsc_cmd_send(2, 0xdb, 0x40);
	dsc_cmd_send(2, 0xdc, 0x04);
	dsc_cmd_send(2, 0xdd, 0x00);
	
	dsc_cmd_send(2, 0xa0, 0x13);
	dsc_cmd_send(2, 0xa1, 0x00);
	dsc_cmd_send(2, 0xa2, 0x05);
	dsc_cmd_send(2, 0xa3, 0x20);
	dsc_cmd_send(2, 0xa6, 0x00);
	dsc_cmd_send(2, 0xa7, 0x00);
	
	dsc_cmd_send(2, 0x97, 0x22);
	
	dsc_cmd_send(2, 0xD1, 0x01);
	dsc_cmd_send(2, 0xD2, 0x00);
	dsc_cmd_send(2, 0xDF, 0x00);
	dsc_cmd_send(2, 0xE5, 0x10);
	dsc_cmd_send(2, 0xE6, 0x00);
	dsc_cmd_send(2, 0xD6, 0x10);
	dsc_cmd_send(2, 0xD7, 0x20);
	dsc_cmd_send(2, 0xD8, 0x14);
	dsc_cmd_send(2, 0xD9, 0x00);
	dsc_cmd_send(2, 0xDA, 0x00);
	
	dsc_cmd_send(2, 0xB2, 0x00);
	dsc_cmd_send(2, 0xB3, 0x00);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x02);	 //page 02
	dsc_cmd_send(2, 0x00, 0x00);
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x0C);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);
	
	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);
	
	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x03);	// page3 
	dsc_cmd_send(2, 0x00, 0x00);	
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x00);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);
	
	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);
	
	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x04); // pagetr for 04
	dsc_cmd_send(2, 0x00, 0x00);
	dsc_cmd_send(2, 0x01, 0x30);
	dsc_cmd_send(2, 0x02, 0x00);
	dsc_cmd_send(2, 0x03, 0x4A);
	dsc_cmd_send(2, 0x04, 0x00);
	dsc_cmd_send(2, 0x05, 0x6F);
	dsc_cmd_send(2, 0x06, 0x00);
	dsc_cmd_send(2, 0x07, 0x8B);
	dsc_cmd_send(2, 0x08, 0x00);
	dsc_cmd_send(2, 0x09, 0xA1);
	dsc_cmd_send(2, 0x0A, 0x00);
	dsc_cmd_send(2, 0x0B, 0xB4);
	dsc_cmd_send(2, 0x0C, 0x00);
	dsc_cmd_send(2, 0x0D, 0xC5);
	dsc_cmd_send(2, 0x0E, 0x00);
	dsc_cmd_send(2, 0x0F, 0xD5);
	dsc_cmd_send(2, 0x10, 0x00);
	dsc_cmd_send(2, 0x11, 0xE2);
	dsc_cmd_send(2, 0x12, 0x01);
	dsc_cmd_send(2, 0x13, 0x10);
	dsc_cmd_send(2, 0x14, 0x01);
	dsc_cmd_send(2, 0x15, 0x34);
	dsc_cmd_send(2, 0x16, 0x01);
	dsc_cmd_send(2, 0x17, 0x6D);
	dsc_cmd_send(2, 0x18, 0x01);
	dsc_cmd_send(2, 0x19, 0x9A);
	dsc_cmd_send(2, 0x1A, 0x01);
	dsc_cmd_send(2, 0x1B, 0xE2);
	dsc_cmd_send(2, 0x1C, 0x02);
	dsc_cmd_send(2, 0x1D, 0x1B);
	dsc_cmd_send(2, 0x1E, 0x02);
	dsc_cmd_send(2, 0x1F, 0x1C);
	dsc_cmd_send(2, 0x20, 0x02);
	dsc_cmd_send(2, 0x21, 0x52);
	dsc_cmd_send(2, 0x22, 0x02);
	dsc_cmd_send(2, 0x23, 0x8F);
	dsc_cmd_send(2, 0x24, 0x02);
	dsc_cmd_send(2, 0x25, 0xB7);
	dsc_cmd_send(2, 0x26, 0x02);
	dsc_cmd_send(2, 0x27, 0xEC);
	dsc_cmd_send(2, 0x28, 0x03);
	dsc_cmd_send(2, 0x29, 0x0E);
	dsc_cmd_send(2, 0x2A, 0x03);
	dsc_cmd_send(2, 0x2B, 0x3A);
	dsc_cmd_send(2, 0x2C, 0x03);
	dsc_cmd_send(2, 0x2D, 0x47);
	dsc_cmd_send(2, 0x2E, 0x03);
	dsc_cmd_send(2, 0x2F, 0x55);
	dsc_cmd_send(2, 0x30, 0x03);
	dsc_cmd_send(2, 0x31, 0x65);
	dsc_cmd_send(2, 0x32, 0x03);
	dsc_cmd_send(2, 0x33, 0x76);
	dsc_cmd_send(2, 0x34, 0x03);
	dsc_cmd_send(2, 0x35, 0x8A);
	dsc_cmd_send(2, 0x36, 0x03);
	dsc_cmd_send(2, 0x37, 0xA3);
	dsc_cmd_send(2, 0x38, 0x03);
	dsc_cmd_send(2, 0x39, 0xC4);
	dsc_cmd_send(2, 0x3A, 0x03);
	dsc_cmd_send(2, 0x3B, 0xD1);
	
	dsc_cmd_send(2, 0x3C, 0x00);
	dsc_cmd_send(2, 0x3D, 0x30);
	dsc_cmd_send(2, 0x3E, 0x00);
	dsc_cmd_send(2, 0x3F, 0x4A);
	dsc_cmd_send(2, 0x40, 0x00);
	dsc_cmd_send(2, 0x41, 0x6F);
	dsc_cmd_send(2, 0x42, 0x00);
	dsc_cmd_send(2, 0x43, 0x8B);
	dsc_cmd_send(2, 0x44, 0x00);
	dsc_cmd_send(2, 0x45, 0xA1);
	dsc_cmd_send(2, 0x46, 0x00);
	dsc_cmd_send(2, 0x47, 0xB4);
	dsc_cmd_send(2, 0x48, 0x00);
	dsc_cmd_send(2, 0x49, 0xC5);
	dsc_cmd_send(2, 0x4A, 0x00);
	dsc_cmd_send(2, 0x4B, 0xD5);
	dsc_cmd_send(2, 0x4C, 0x00);
	dsc_cmd_send(2, 0x4D, 0xE2);
	dsc_cmd_send(2, 0x4E, 0x01);
	dsc_cmd_send(2, 0x4F, 0x10);
	dsc_cmd_send(2, 0x50, 0x01);
	dsc_cmd_send(2, 0x51, 0x34);
	dsc_cmd_send(2, 0x52, 0x01);
	dsc_cmd_send(2, 0x53, 0x6D);
	dsc_cmd_send(2, 0x54, 0x01);
	dsc_cmd_send(2, 0x55, 0x9A);
	dsc_cmd_send(2, 0x56, 0x01);
	dsc_cmd_send(2, 0x57, 0xE2);
	dsc_cmd_send(2, 0x58, 0x02);
	dsc_cmd_send(2, 0x59, 0x1B);
	dsc_cmd_send(2, 0x5A, 0x02);
	dsc_cmd_send(2, 0x5B, 0x1C);
	dsc_cmd_send(2, 0x5C, 0x02);
	dsc_cmd_send(2, 0x5D, 0x52);
	dsc_cmd_send(2, 0x5E, 0x02);
	dsc_cmd_send(2, 0x5F, 0x8F);
	dsc_cmd_send(2, 0x60, 0x02);
	dsc_cmd_send(2, 0x61, 0xB7);
	dsc_cmd_send(2, 0x62, 0x02);
	dsc_cmd_send(2, 0x63, 0xEC);
	dsc_cmd_send(2, 0x64, 0x03);
	dsc_cmd_send(2, 0x65, 0x0E);
	dsc_cmd_send(2, 0x66, 0x03);
	dsc_cmd_send(2, 0x67, 0x3A);
	dsc_cmd_send(2, 0x68, 0x03);
	dsc_cmd_send(2, 0x69, 0x47);
	dsc_cmd_send(2, 0x6A, 0x03);
	dsc_cmd_send(2, 0x6B, 0x55);
	dsc_cmd_send(2, 0x6C, 0x03);
	dsc_cmd_send(2, 0x6D, 0x65);
	dsc_cmd_send(2, 0x6E, 0x03);
	dsc_cmd_send(2, 0x6F, 0x76);
	dsc_cmd_send(2, 0x70, 0x03);
	dsc_cmd_send(2, 0x71, 0x8A);
	dsc_cmd_send(2, 0x72, 0x03);
	dsc_cmd_send(2, 0x73, 0xA3);
	dsc_cmd_send(2, 0x74, 0x03);
	dsc_cmd_send(2, 0x75, 0xC4);
	dsc_cmd_send(2, 0x76, 0x03);
	dsc_cmd_send(2, 0x77, 0xD1);
	
	dsc_cmd_send(2, 0x78, 0x01);
	dsc_cmd_send(2, 0x79, 0x01);
	
	dsc_cmd_send_4(0xFF, 0x78, 0x07, 0x00);
	
	dsc_cmd_send(2, 0x11, 0x00);
	msleep(150);
	dsc_cmd_send(2, 0x29, 0x00);
	msleep(50);
		
}
#endif
/**
 * @brief 
 * 
 */
void dsc_cmd_send_buff(uint8_t *buff, uint32_t len)
{
        uint32_t reg, val, val2;
        int cmd_sts;
        uint8_t i = 0;

        reg = 0x01003908 | (len << 16);                 //0x01003908
        DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,reg); //[24] cmd_lp_en  =1    0x01043908
                                                        //[23:14] cmd_size  cmd_size = len
                                                        //[13:8] cmd_head  =0x39
                                                        //[3 ] cmd_longnotshort  =0x1
                                                        //[2:0] cmd_nat : 3'b000:write command
                                                        //                3'b001:read command
                                                        //                3'b100:TE request
                                                        //                3'b101:trigger request
                                                        //                3'b110:BTA request
        val = len / 4;       
        for(i = 0; i < val; i++)
        {
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * i) + 3]<<24) + (buff[(4 * i) + 2]<<16) + (buff[(4 * i) + 1]<<8) + buff[(4 * i)]));// DATA  
        }
        val2 = len % 4;
        if(val2 == 1)
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,buff[(4 * val)]);// DATA
        else if(val2 == 2)
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) + 1]<<8) + buff[(4 * val)]));// DATA
        else if(val2 == 3)
                DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,((buff[(4 * val) + 2]<<16) + (buff[(4 * val) + 1]<<8) + buff[(4 * val)]));// DATA

        DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send
	while((cmd_sts & 0x02 )!= 0x02)
	{  
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}
/**
 * @brief 
 * 
 */
void dsc_cmd_send_short_pag(uint8_t val)
{
        uint8_t reg = 0;
        int cmd_sts;

       // reg = 0x01000500 | (val << 16);
        DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x01010500); //[24] cmd_lp_en  =1    0x01010500
															//[23:14] cmd_size  =cmd_size. 1 or 2   //write 4
															//[13:8] cmd_head  =0x39
															//[3 ] cmd_longnotshort  =0x0  short pkg
															//[2:0] cmd_nat : 3'b000:write command
															//                3'b001:read command
															//                3'b100:TE request
															//                3'b101:trigger request
															//                3'b110:BTA request
        DsiRegWr(DIRECT_CMD_WRDAT_OFFSET,val);                         // DATA            ???                                    
        
        DsiRegWr(DIRECT_CMD_SEND_OFFSET,0x00000); // cmd send

	while((cmd_sts & 0x02 )!= 0x02)
	{  
		cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
	}
	DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0x02); // clear write_completed
}
/**
 * @brief 
 * 
 */
void hx8399_c_init(void)
{
        uint8_t pag1[5] = {0xB9, 0xFF, 0x83, 0x99};                    
        uint8_t pag2[20] = {0xB1, 0x02, 0x04, 0x70, 0x90, 0x01, 0x32, 0x33, 0x11, 0x11, 0x4D, 0x57, 0x56, 0x73, 0x02, 0x02};           // 0x10
        uint8_t pag3[20] = {0xB2, 0x00, 0x80, 0x80, 0xAE, 0x05, 0x07, 0x5A, 0x11, 0x10, 0x10, 0x00};                     // 0c
        uint8_t pag4[50] = {0xB4, 0x00, 0xFF, 0x04, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x24, 0x02, 0x04, 0x09, 0x21, 0x03, 0x00, 0x00, 0x0A, 0x90, 0x88, 0x04, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x24, 0x02, 0x04, 0x08, 0x00, 0x00, 0x02, 0x88, 0x00, 0x08};
        uint8_t pag5[50] = {0xD3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x32, 0x10, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x05, 0x05, 0x13, 0x00, 0x00, 0x00, 0x05, 0x40, 0x00, 0x00, 0x00, 0x05, 0x20, 0x80};
        uint8_t pag6[50] = {0xD5, 0x00, 0x00, 0x21, 0x20, 0x19, 0x19, 0x18, 0x18, 0x00, 0x00, 0x01, 0x00, 0x18, 0x18, 0x03, 0x02, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x31, 0x30, 0x30, 0x2F, 0x2F};
        uint8_t pag7[50] = {0xD6, 0x40, 0x40, 0x20, 0x21, 0x18, 0x18, 0x19, 0x19, 0x40, 0x40, 0x02, 0x03, 0x18, 0x18, 0x00, 0x01, 0x19, 0x19, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x31, 0x31, 0x30, 0x30, 0x2F, 0x2F};
        uint8_t pag8[20] = {0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        uint8_t pag9[5] = {0xBD, 0x01};
        uint8_t pag10[20] = {0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        uint8_t pag11[5] = {0xBD, 0x02};
        uint8_t pag12[20] = {0xD8, 0xAA, 0xAE, 0xEA, 0xAA, 0xAA, 0xAE, 0xEA, 0xAA};
        uint8_t pag13[5] = {0xBD, 0x00};
        uint8_t pag14[60] = {0xE0, 0x01, 0x15, 0x22, 0x1E, 0x46, 0x51, 0x5E, 0x5A, 0x63, 0x6A, 0x71, 0x76, 0x7B, 0x82, 0x88, 0x8D, 0x92, 0x9C, 0xA0, 0xAB, 0xA2, 0xB5, 0xBD, 0x63, 0x61, 0x6E, 0x7A, 0x01, 0x15, 0x22, 0x1E, 0x46, 0x51, 0x5E, 0x5A, 0x63, 0x6A, 0x71, 0x76, 0x7B, 0x82, 0x89, 0x8E, 0x92, 0x9C, 0xA0, 0xAB, 0xA2, 0xB5, 0xBD, 0x63, 0x61, 0x6E, 0x7A};
        uint8_t pag15[5] = {0xC0, 0x25, 0x5A};
        uint8_t pag16[5] = {0xB6, 0x91, 0x91};
        uint8_t pag17[50] = {0xD2, 0x66};
        uint8_t pag18[50] = {0xCC, 0x08};
        uint8_t pag19[50] = {0x36, 0x08};

        dsc_cmd_send_buff(pag1, 4);           // access the extension commands.
        msleep(2);
        dsc_cmd_send_buff(pag2, 16);          //Set power related register
        msleep(2);
        dsc_cmd_send_buff(pag3, 12);          // Set display related register
        msleep(2);
        dsc_cmd_send_buff(pag4, 46);
        msleep(2);
        dsc_cmd_send_buff(pag5, 40);     
        msleep(2);                            
        dsc_cmd_send_buff(pag6, 33);
        msleep(2);
        dsc_cmd_send_buff(pag7, 33);
        msleep(2);
        dsc_cmd_send_buff(pag8, 17);        
        msleep(2);            
        dsc_cmd_send(2, 0xBD, 0x01);
	
        dsc_cmd_send_buff(pag10, 17);
        msleep(2);
        dsc_cmd_send(2, 0xBD, 0x02);
        msleep(2);
        dsc_cmd_send_buff(pag12, 9);
        msleep(2);
        dsc_cmd_send(2, 0xBD, 0x00);
        msleep(2);
        dsc_cmd_send_buff(pag14, 55);
        msleep(2);
        dsc_cmd_send_buff(pag15, 3);
        msleep(2);
        dsc_cmd_send_buff(pag16, 3);
        msleep(2);
        dsc_cmd_send(2, 0xD2, 0x66);
        msleep(2);
        dsc_cmd_send(2, 0xCC, 0x08);   //0xCC, 0x08  
        msleep(2);            
        dsc_cmd_send(2, 0x36, 0x08);  //0x36, 0x08
        msleep(2);

        dsc_cmd_send_short_pag(0x11);
        msleep(300);
        dsc_cmd_send_short_pag(0x29);
        msleep(100);

}


/**
 * @brief 
 * 
 */
void test(void)
{
        int i = 0;
        uint32_t reg = 0;
        uint32_t wdata;
        int cmd_sts =0;
#if 1
//        sysctl_reset(SYSCTL_RESET_DSI);

        /*****************reset d-phy*****************/
#if 1
        sleep(1);
        DsiRegWr(MCTL_DPHY_CFG0_OFFSET,0xf0600);                // dsi reset dphy

        wdata = 0xda036000;                                     // set d-phy
        writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);

        wdata = 0x3b01e;                                        // set d-phy
        writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x4);

        wdata = 0x9a036000;                                     // set d-phy
        writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0x8);            //0x92718000

#if 0        
        while((cmd_sts & 0x9a036000 )!= 0x9a036000)                             // ȡ0x88 Ƕȡ4  1 
        {
             cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x8);
        }

        while((cmd_sts & 0x08 )!= 0x08)                             // ȡ0x88 Ƕȡ4  1 
        {
             cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
        }

        while((cmd_sts & 0x08 )!= 0x00)                             // ȡ0x88 Ƕȡ4  1 
        {
             cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
        }        

        while((cmd_sts & 0x04 )!= 0x04)                             // ȡ0x88 Ƕȡ4  1 
        {
             cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
        } 

        while((cmd_sts & 0x04 )!= 0xf0600)                             // ȡ0x88 Ƕȡ4  1 
        {
             cmd_sts = readl(VIDEO_TXDPHY_BASE_ADDR + 0x14);
        }
#endif 

        //ǲҪȡ1_8014 ״̬0x04  0xf0600  

        sleep(1);
        DsiRegWr(MCTL_DPHY_CFG0_OFFSET, 0x1f0600);              // dsi reset dphy  
#if 1
        sleep(1);
        #ifndef _FPGA
        printf("before SYSCTL_DRV_Init\n");

//        SYSCTL_DRV_Init();
        
        printf("SYSCTL_DRV_Init done\n");
//        mipi_rxdphy_init(RXDPHY_SPEED_MODE_1500M, RXDPHY_CHCFG_1X4);
        printf("mipi_rxdphy_init done\n");

        mipi_txdphy_init();
//        mipi_txdphy_init_10M();

        printf("mipi_txdphy_init done\n");
        #endif

 //       VI_DRV_Init();
        
        printf("ISP_DRV_InitInterrupt done\n");
        //
/*
        VO_DRV_Init();
        
        TOF_DRV_Init();
        MFBC_DRV_Init();
        TD_DRV_Init();
        BT1120_DRV_Init();
        printf("BT1120_DRV_Init done\n");
*/      
#endif

#endif 

#if 0
        /**************config dsi****************************/

        wdata = 0xf180000;                                     // set d-phy
        writel(wdata, VIDEO_TXDPHY_BASE_ADDR + 0xc);

        DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET,0xafffb);                // dsi reset dphy   0x14 
        DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0xbfe7);                // dsi reset dphy     0x08
        DsiRegWr(MCTL_MAIN_EN_OFFSET,0x40f9);                // dsi reset dphy          0xc
        DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET,0xffff);                // dsi reset dphy    0x18
        DsiRegWr(MCTL_ULPOUT_TIME_OFFSET,0x3ab05);                // dsi reset dphy     0x1c
        DsiRegWr(VID_ERR_COLOR1_OFFSET,0xccaa);                // dsi reset dphy        0xe0
        DsiRegWr(VID_ERR_COLOR2_OFFSET,0xee55);                // dsi reset dphy        0xe4
        DsiRegWr(MCTL_DPHY_CFG0_OFFSET,0x1f0600);                // dsi reset dphy      0x10
        DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x23);                // dsi reset dphy      0x4

        DsiRegWr(DIRECT_CMD_STS_CTL_OFFSET,0x80);                // dsi reset dphy      0x138
        DsiRegWr(VID_VCA_SETTING2_OFFSET,0x17dc0000);                // dsi reset dphy  0xf8
        DsiRegWr(VID_VSIZE1_OFFSET,0x9145);                // dsi reset dphy            0xb4
        DsiRegWr(VID_VSIZE2_OFFSET,0x438);                // dsi reset dphy             0xb8
        DsiRegWr(VID_HSIZE1_OFFSET,0x6c002e);                // dsi reset dphy          0xc0
        DsiRegWr(VID_HSIZE2_OFFSET,0xea1680);                // dsi reset dphy          0xc4

        DsiRegWr(VID_BLKSIZE1_OFFSET,0xb400000);                // dsi reset dphy       0xcc
        DsiRegWr(VID_BLKSIZE2_OFFSET,0x17e2);                // dsi reset dphy          0xd0
        DsiRegWr(VID_PCK_TIME_OFFSET,0x5a2);                // dsi reset dphy           0xd8
        DsiRegWr(VID_DPHY_TIME_OFFSET,0x1e05fa);                // dsi reset dphy       0xdc
        DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x6e027);                // dsi reset dphy   0x4
        DsiRegWr(VID_MAIN_CTL_OFFSET,0x8218fe00);                // dsi reset dphy      0xb0

        DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0xe027);                // dsi reset dphy    0x4
        DsiRegWr(VID_MAIN_CTL_OFFSET,0x8218fe00);                // dsi reset dphy      0xb0
        DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x20003fe7);                // dsi reset dphy      0x08

//        DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x2003fe7);          // dsi reset dphy
        
        wait_phy_pll_locked();
        printf("phy pll locked ");

        wait_cklane_rdy();
        printf("cklane  is ready!!! ");
        wait_dat1_rdy();
        printf("dat1  is ready!!! ");
        wait_dat2_rdy();
        printf("dat2  is ready!!! ");
        wait_dat3_rdy();
        printf("dat3  is ready!!! ");
        wait_dat4_rdy();
        printf("dat4  is ready!!! ");


        DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x6e027);                // dsi reset dphy   0x4
        DsiRegWr(DIRECT_CMD_STS_CLR_OFFSET,0xffffffff);             // dsi reset dphy   0x158   
        DsiRegWr(DIRECT_CMD_RD_STS_CLR_OFFSET, 0xffffffff);         // dsi reset dphy   0x15c

        DsiRegWr(DIRECT_CMD_MAIN_SETTINGS_OFFSET,0x3010505);        // dsi reset dphy   0x84
        DsiRegWr(DIRECT_CMD_SEND_OFFSET,0xffffffff);                // dsi reset dphy   0x80

        
        while((cmd_sts & 0x04 )!= 0x04)                             // ȡ0x88 Ƕȡ4  1 
        {
                cmd_sts = DsiRegRd(DIRECT_CMD_STS_OFFSET);
        }

#endif 


#endif

#if 0
        for(i = 0; i < 127; i++)
        {

             reg = DsiRegRd(i * 4);          
             printf("reg 0x%04x is 0x%08x \n", i * 4, reg) ;  
        }
#endif      

#if 0
        printf("\n\n SYSCTL_CLK_MIPI_REF out clk freq is %d \r\n\n",sysctl_clk_get_leaf_freq(SYSCTL_CLK_MIPI_REF));
        sleep(1);

        DsiRegWr(DPI_IRQ_EN_OFFSET, 0); //enable dpi overflow int

        DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x3C17);    //[6]  lane1_ulp_en = 1
                                                               //[4]  clk_continuous  =1
                                                               //[2]  lane4_en =1
                                                               //[1]  lane3_en =1
                                                               //[0]  lane2_en =1
        DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET,0xed8afffb);
        DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET,0xf30fffff);
        DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x2e027); //[6] tvg_sel = 1  test video generator enabled   //default 0x27
                                                             //[5] vid_en = 1   enable the video stream generator
                                                             //[3:2] vid_if_select =2'b00  00:sdi;01:dpi??10:DSC
                                                             //[1] sdi_if_vid_mode = 1  select video mode
                                                             //[0] link_en = 1; // enable link
        DsiRegWr(MCTL_MAIN_EN_OFFSET,0x40f9);
                                                        //[15]   if3_en: enable dsc interface
                                                        //[14]   if2_en: enable dpi interface   =1
                                                        //[13]   if1_en: enable sdi interface
                                                        //[9]   lane1_ulp_req =1
                                                        //[7]   dat4_en
                                                        //[6]   dat3_en
                                                        //[5]   dat2_en
                                                        //[4]   dat1_en
                                                        //[3]   cklane_en


        //disable status detection
        unsigned int data = DsiRegRd(CMD_MODE_STS_CTL_OFFSET);
        printf("CMD_MODE_STS_CTL_OFFSET data 0x%x\n",data);
        data &= ~ (1 << 0); 
        DsiRegWr(CMD_MODE_STS_CTL_OFFSET,data );
                                                         

          wait_phy_pll_locked();
          printf("phy pll locked ");

          wait_cklane_rdy();
          printf("cklane  is ready!!! ");
          wait_dat1_rdy();
          printf("dat1  is ready!!! ");
          wait_dat2_rdy();
          printf("dat2  is ready!!! ");
          wait_dat3_rdy();
          printf("dat3  is ready!!! ");
          wait_dat4_rdy();
          printf("dat4  is ready!!! ");
         // will init lcd
          DsiRegWr(MCTL_ULPOUT_TIME_OFFSET,0x0003ab05);
#if 0
        for(i = 0; i < 127; i++)
        {

             reg = DsiRegRd(i * 4);          
             printf("reg 0x%04x is 0x%08x \n", i * 4, reg) ;  
        }
#endif 
#endif 
        sleep(5);
 //       aml_lcd_init();
//        ILI7807_lcd_init();

}
//b cnds_dsi_test.c:901
void dsi_init_1080x1920()
{

           int  HACT=1080;
           int  VACT=1920;
           int  HSA=20;
           int  HBP=20;
           int  HFP=220;
           int  VSA=5;
           int  VBP=8;
           int  VFP=5;
           int i = 0;
        uint32_t reg = 0;
/*
        for(i = 0; i < 127; i++)
        {

             reg = DsiRegRd(i * 4);          
             printf("reg 0x%04x is 0x%08x \n", i * 4, reg) ;  
        }
*/

         DsiRegWr(DPI_IRQ_EN_OFFSET, 0); //enable dpi overflow int
#if 1
         DsiRegWr(MCTL_MAIN_PHY_CTL_OFFSET,0x3C17);    //[6]  lane1_ulp_en = 1
                                                               //[4]  clk_continuous  =1
                                                               //[2]  lane4_en =1
                                                               //[1]  lane3_en =1
                                                               //[0]  lane2_en =1
          DsiRegWr(MCTL_DPHY_TIMEOUT1_OFFSET,0xed8afffb);
          DsiRegWr(MCTL_DPHY_TIMEOUT2_OFFSET,0xf30fffff);
          DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x2e027); //[6] tvg_sel = 1  test video generator enabled   //default 0x27
                                                             //[5] vid_en = 1   enable the video stream generator
                                                             //[3:2] vid_if_select =2'b00  00:sdi;01:dpi??10:DSC
                                                             //[1] sdi_if_vid_mode = 1  select video mode
                                                             //[0] link_en = 1; // enable link
          DsiRegWr(MCTL_MAIN_EN_OFFSET,0x40f9);
                                                         //[15]   if3_en: enable dsc interface
                                                         //[14]   if2_en: enable dpi interface   =1
                                                         //[13]   if1_en: enable sdi interface
                                                         //[9]   lane1_ulp_req =1
                                                         //[7]   dat4_en
                                                        //[6]   dat3_en
                                                        //[5]   dat2_en
                                                        //[4]   dat1_en
                                                        //[3]   cklane_en


        //disable status detection
        unsigned int data = DsiRegRd(CMD_MODE_STS_CTL_OFFSET);
        printf("CMD_MODE_STS_CTL_OFFSET data 0x%x\n",data);
        data &= ~ (1 << 0); 
        DsiRegWr(CMD_MODE_STS_CTL_OFFSET,data );
                                                         

        wait_phy_pll_locked();
        printf("phy pll locked ");

        wait_cklane_rdy();
        printf("cklane  is ready!!! ");
        wait_dat1_rdy();
        printf("dat1  is ready!!! ");
        wait_dat2_rdy();
        printf("dat2  is ready!!! ");
        wait_dat3_rdy();
        printf("dat3  is ready!!! ");
        wait_dat4_rdy();
        printf("dat4  is ready!!! ");
        // will init lcd
        DsiRegWr(MCTL_ULPOUT_TIME_OFFSET,0x0003ab05);
#ifndef _SIMU
          sleep(1);
#endif

//sleep(5);
 /*       
        for(i = 0; i < 127; i++)
        {

             reg = DsiRegRd(i * 4);          
             printf("reg 0x%04x is 0x%08x \n", i * 4, reg) ;  
        }
        */
 //       aml_lcd_init();
        //ILI7807_lcd_init();
        hx8399_c_init();
 #endif      
        test();
        sleep(5);
        printf("lcd init  ok!!! ");


         // DsiRegWr(MCTL_MAIN_DATA_CTL_OFFSET,0x27) //[6] tvg_sel = 1  test video generator enabled
                                                             //[5] vid_en = 1   enable the video stream generator
                                                             //[3:2] vid_if_select =2'b00  00:sdi;01:dpi??10:DSC
                                                             //[1] sdi_if_vid_mode = 1  select video mode
                                                             //[0] link_en = 1; // enable link

          DsiRegWr(TVG_IMG_SIZE_OFFSET,(VACT <<16) +HACT*3);
          DsiRegWr(TVG_COLOR1_OFFSET,(0<<12) +255)  ;  //[23:12] col1_green
                                                                  //[11:0]  col1_red
          DsiRegWr(TVG_COLOR1_BIS_OFFSET,0)  ; //[11:0]  col1_blue
          DsiRegWr(TVG_COLOR2_OFFSET,(0<<12) +0) ;   //[23:12] col2_green
                                                                  //[11:0]  col2_red
          DsiRegWr(TVG_COLOR2_BIS_OFFSET,255) ;  //[11:0]  col2_blue


          DsiRegWr(VID_VSIZE1_OFFSET,(VFP<<12)+(VBP<<6)+VSA);
                                                //[19:12] vfp_length
                                                //[11:6]  vbp_length
                                                //[5:0]   vsa_length
          DsiRegWr(VID_MODE_STS_CTL_OFFSET,0);//0xffffffff);
          DsiRegWr(VID_VSIZE2_OFFSET,VACT); //[12:0] vact_length
          DsiRegWr(VID_HSIZE1_OFFSET,((HBP*3-12)<<16)+(HSA*3-14));
                                                 //[31:16] hbp_length  =(dpi_hbp*24/8-12)
                                                 //[9:0]   hsa_length  =(dpi_hsa*24/8-14)

          DsiRegWr(VID_HSIZE2_OFFSET,((HFP*3-6)<<16)+(HACT*3));
                                                 //[26:16] hfp_length  =(dpi_hfp*24/8-6) >hss+hsa+hse+hbp
                                                 //[14:0] rgb_size
          DsiRegWr(VID_BLKSIZE2_OFFSET,(HSA+HBP+HFP+HACT)*3-20-(HSA*3-14));
                                                 //[14:0] blkline_pulse_pck = (dpi_hsa+dpi_hbp+dpi_hact+dpi_hfp)*24/8-20-((dpi_hsa*24/8)-14)=3342
                                                        //  (1080+20+15+72)*3-20= 3541
          DsiRegWr(VID_DPHY_TIME_OFFSET,(0x38<<17)+((HSA+HBP+HFP+HACT)*3/4)-((HSA*3-14)/4));
                                                   //[16:0] reg_line_duration =(line_total_)
                                                   //[27:17] reg_wakeup_time
          DsiRegWr(VID_VCA_SETTING1_OFFSET,(0x000000));
          DsiRegWr(VID_VCA_SETTING2_OFFSET,((HSA+HBP+HFP+HACT)*3-20-(HSA*3-14)-6)<<16);
                                                     //[31:16] max_line_limit = gen_blkline_pulse_pck-6;
          DsiRegWr(VID_MAIN_CTL_OFFSET,(0x1<<31)+(0x1<<25)+(0x0<<21)+(1<<20)+(1<<19)+(3<<14)+(0x3e<<8)+0); //0x1 << 21
                                                 //[31] vid_ignore_miss_vsync =1
                                                 //[26:25] recovery_mode
                                                 //[24:23] reg_blkeol_mode : same as reg_blkline_mode but using in burst mode
                                                 //[22:21] reg_blkline_mode : 1x: LP
                                                 //                            01: blanking packet
                                                 //                            00: null packet

                                                 //[20] sync_pulse_horizontal:syncs are pulse(1) or event(0)
                                                 //[19] sync_pulse_active :1
                                                 //[18] burst mode
                                                 //[17:14] vid_pixel_mode  0000: 16 bits RGB
                                                 //                        0001: 18 bits RGB
                                                 //                        0010: 18 bits RGB(loose)
                                                 //                        0011: 24 bits RGB
                                                 //                        0100: 30 bits RGB
                                                 //                        0101: 36 bits RGB
                                                 //                        1000: 12 bits YCbCr
                                                 //                        1001: 16 bits YCbCr
                                                 //                        1010: 20 bits YCbCr
                                                 //                        1011: 24 bits YCbCr
                                                 //                        1100: DSC Compressed
                                                 //[13:0] Header:  Datatype of RGB packets "0x3e  rgb24
                                                 //[1:0]  start mode:start_mode=0
          //DsiRegWr(TVG_CTL_OFFSET,(6<<5)+(2<<3)+0) ;//[7:5]tvg_stripe_size
                                                           //[4:3] tvg_mode 00:single color
                                                           //                01:reserved
                                                           //                10:verical  stripes
                                                           //                11:horizontal  stripes
                                                           //[2:1] tvg_stopmode  00: at the end of frame
                                                           //                     01: at the end of line
                                                          //                      1x: immediate
                                                          //[0]   tvg run
        for(i = 0; i < 127; i++)
        {

             reg = DsiRegRd(i * 4);          
             printf("reg 0x%04x is 0x%08x \n", i * 4, reg) ;  
        }
}


