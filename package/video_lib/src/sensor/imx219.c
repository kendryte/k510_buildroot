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
/******************************************************************************
  File Name     : imx219.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h> 
#include <assert.h>

#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/i2c-dev.h>

#include <linux/i2c.h>

#include "sensor/sensor.h"
#include "i2c/i2c_com.h"
#include "exctl_dev/dev_hw.h"
#include "isp_com.h"

#define I2C_DEVICE_NAME0                 "/dev/i2c-0" 
#define I2C_DEVICE_NAME3                 "/dev/i2c-3"
#define IMX219_CHIP_ADDR                (0x10)

static int i2c_fd = 0;
/**
 * @brief 
 * 
 */
void imx219_i2c_init(enum _SENSOR_I2C i2c_num)
{
	printf("i2c_num = %d\n",i2c_num);
	if(MIPI_CSI0_I2C == i2c_num)
    {
	    i2c_fd = open(I2C_DEVICE_NAME0, O_RDWR);
        if(i2c_fd < 0)
        {
             printf("open %s faild \n", I2C_DEVICE_NAME0); 
        }
    }    
    else if(MIPI_CSI1_I2C == i2c_num)
    {
	    i2c_fd = open(I2C_DEVICE_NAME3, O_RDWR);
        if(i2c_fd < 0)
        {
             printf("open %s faild \n", I2C_DEVICE_NAME3); 
        }
    } 

    if (ioctl(i2c_fd, I2C_SLAVE_FORCE, IMX219_CHIP_ADDR) < 0) 
    { 
        printf("oictl:setslave address failed/n");

    }
	//
    i2c_set(i2c_fd, 20, 2);

    msleep(10);
    printf("imx219_i2c_init config done\n");
    /*sensor imx385 config start*/
    Release_imx385_fpga_reset_n();
}
/**
 * @brief 
 * 
 * @param reg_addr 
 * @param reg_val 
 */
void imx219_sensor_write(uint16_t reg_addr,uint8_t reg_val)
{
    uint8_t addr[2];
    addr[0] = (reg_addr >> 8) & 0xff;
    addr[1] = reg_addr & 0xff;
    uint8_t val = reg_val;
    i2c_nbytes_write(i2c_fd,IMX219_CHIP_ADDR,&addr,2,&val,1);
}
/**
 * @brief 
 * 
 * @param reg_addr 
 */
void imx219_sensor_read(uint16_t reg_addr)
{
    uint8_t reg_val = 0;
    uint8_t addr[2];
    addr[0] = (reg_addr >> 8) & 0xff;
    addr[1] = reg_addr & 0xff;

    i2c_nbytes_read(i2c_fd,IMX219_CHIP_ADDR,&addr,2,&reg_val,1);
    printf("reg is %x val is %x \n", reg_addr, reg_val);
}
/**
 * @brief 
 * 
 */
static const struct regval_list mode_1920_1080_regs[] = {
	{0x0100, 0x00}, //REG_MODE_SEL
	//Access command sequence
	{0x30eb, 0x05},
	{0x30eb, 0x0c},
	{0x300a, 0xff},
	{0x300b, 0xff},
	{0x30eb, 0x05},
	{0x30eb, 0x09},
	//
	{0x0114, 0x01}, //REG_CSI_LANE 01 -2lanes 03-4lanes
	{0x0128, 0x00}, //REG_DPHY_CTRL
	{0x012a, 0x18}, //REG_EXCK_FREQ_MSB
	{0x012b, 0x00}, //REG_EXCK_FREQ_LSB
	//
	//{0x0154,0x00},// FRAME_DURATION_A 
	//{0x0155,0x00},// COMP_ENABLE_A 
	//{0x0157,0x20},// ANA_GAIN_GLOBAL_A
	//{0x0158,0x00},// DIG_GAIN_GLOBAL_A [11:8]
	//{0x0159,0x20},// DIG_GAIN_GLOBAL_A [7:0] 
	//
	//{0x015A,0x00},// COARSE_INTEGRATION_TIME_A[15:8]
	//{0x015B,0x02},// COARSE_INTEGRATION_TIME_A[7:0]
	//{0x015D,0x00},// SENSOR_MODE_A XX 0x025D SENSOR_MODE_B X
	//
	{0x0160, 0x04},//FRM_LENGTH_A[15:8] 1166
	{0x0161, 0x8e},//FRM_LENGTH_A[7:0] 1166     
	{0x0162, 0x0d},//0x0d},//LINE_LENGTH_A[15:8] 3448
	{0x0163, 0x94},//0x78},//LINE_LENGTH_A[7:0]
	// 
	{0x0164, 0x02}, //X_ADD_STA_A[11:8] 
	{0x0165, 0xa8},//X_ADD_STA_A[7:0] 
	{0x0166, 0x0a}, //X_ADD_END_A[11:8] 
	{0x0167, 0x27}, //X_ADD_END_A[7:0] 
	//
	{0x0168, 0x02},//Y_ADD_STA_A[11:8] 
	{0x0169, 0xb4},//Y_ADD_STA_A[7:0] 
	{0x016a, 0x06},//Y_ADD_END_A[11:8] 
	{0x016b, 0xeb},//Y_ADD_END_A[7:0] 
	//
	{0x016c, 0x07},//x_output_size[11:8] 
	{0x016d, 0x80},//x_output_size[7:0]
	{0x016e, 0x04},//y_output_size[11:8] 
	{0x016f, 0x38},// y_output_size[7:0] 
	//
	{0x0170, 0x01},//X_ODD_INC_A
	{0x0171, 0x01},//Y_ODD_INC_A
	//
	//{0x0172, 0x01},//IMG_ORIENTATION_A
	//BINNING
	{0x0174, 0x00},//BINNING_MODE_H_A
	{0x0175, 0x00},//BINNING_MODE_V_A
	//{0x0176, 0x00},//BINNING_CAL_MODE_H_A
	//{0x0177, 0x00},//BINNING_CAL_MODE_V_A
	//
	//{0x0189,0x00},//ANA_GAIN_GLOBAL_SHORT_A
	//{0x018A,0x00},//COARSE_INTEG_TIME_SHORT_A 
	//{0x018B,0x00},//COARSE_INTEG_TIME_SHORT_A
	// 
	//{0x018C,0x00},//CSI_DATA_FORMAT_A [15:8]
	//{0x018D,0x00},//CSI_DATA_FORMAT_A [7:0]	
	//LSC
	//{0x0190,0x00},//LSC_ENABLE_A
	//{0x0191,0x00},//LSC_COLOR_MODE_A
	//{0x0192,0x00},//LSC_SELECT_TABLE_A 
	//{0x0193,0x00},//LSC_TUNING_ENABLE_A
	//{0x0194,0x00},//LSC_WHITE_BALANCE_RG_A[15:8]
	//{0x0195,0x00},//LSC_WHITE_BALANCE_RG_A[7:0]
	//{0x0198,0x00), //LSC_TUNING_COEF_R_A
	//{0x0199,0x00), //LSC_TUNING_COEF_GR_A 
	//{0x019A,0x00), //LSC_TUNING_COEF_GB_A 
	//{0x019B,0x00), //LSC_TUNING_COEF_B_A
	//{0x019C,0x00), //LSC_TUNING_R_A[12:8] 
	//{0x019D,0x00), //LSC_TUNING_R_A[7:0]
	//{0x019E,0x00), //LSC_TUNING_GR_A[12:8]
	//{0x019F,0x00), //LSC_TUNING_GR_A[7:0] 
	//{0x01A0,0x00), //LSC_TUNING_GB_A[12:8]
	//{0x01A1,0x00), //LSC_TUNING_GB_A[7:0] 
	//{0x01A2,0x00), //LSC_TUNING_B_A[12:8] 
	//{0x01A3,0x00), //LSC_TUNING_B_A[7:0]
	//{0x01A4,0x00), //LSC_KNOT_POINT_FORMAT_A
	//
	{0x0301, 0x05},//VTPXCK_DIV
	{0x0303, 0x01},//VTSYCK_DIV
	//
	{0x0304, 0x03},//PREPLLCK_VT_DIV
	{0x0305, 0x03},//PREPLLCK_OP_DIV
	//
	{0x0306, 0x00},//PLL_VT_MPY[10:8]
	{0x0307, 0x26},//0x25},//PLL_VT_MPY[7:0] 0x39
	//
	//{0x0309, 0x00},//OPPXCK_DIV
	//
	{0x030b, 0x01},//OPSYCK_DIV
	//
	{0x030c, 0x00},//PLL_OP_MPY[10:8] 
	{0x030d, 0x30},//PLL_OP_MPY[7:0] 0x72

	//{0x0157, 0x64},//analog gain
	//
	{0x0624, 0x07},
	{0x0625, 0x80},
	{0x0626, 0x04},
	{0x0627, 0x38},
	{0x455e, 0x00},
	{0x471e, 0x4b},
	{0x4767, 0x0f},
	{0x4750, 0x14},
	{0x4540, 0x00},
	{0x47b4, 0x14},
	{0x4713, 0x30},
	{0x478b, 0x10},
	{0x478f, 0x10},
	{0x4793, 0x10},
	{0x4797, 0x0e},
	{0x479b, 0x0e},
	{0x0157, 0x40},//analog gain
	{0x0158, 0x01},
	{0x0159, 0x00},
	{0x015a, 0x03},
	{0x015b, 0xe8},
	//
    {0x0100, 0x01}, //REG_MODE_SEL
    {0xffff, 0xff},
};

static const struct regval_list mode_1080_1920_regs[] = {
	{0x0100, 0x00}, //REG_MODE_SEL
	//Access command sequence
	{0x30eb, 0x05},
	{0x30eb, 0x0c},
	{0x300a, 0xff},
	{0x300b, 0xff},
	{0x30eb, 0x05},
	{0x30eb, 0x09},
	//
	{0x0114, 0x01}, //REG_CSI_LANE 01 -2lanes 03-4lanes
	{0x0128, 0x00}, //REG_DPHY_CTRL
	{0x012a, 0x18}, //REG_EXCK_FREQ_MSB
	{0x012b, 0x00}, //REG_EXCK_FREQ_LSB

	//
	//{0x0154,0x00},// FRAME_DURATION_A 
	//{0x0155,0x00},// COMP_ENABLE_A 
	//{0x0157,0x20},// ANA_GAIN_GLOBAL_A
	//{0x0158,0x00},// DIG_GAIN_GLOBAL_A [11:8]
	//{0x0159,0x20},// DIG_GAIN_GLOBAL_A [7:0] 
	//
	//{0x015A,0x00},// COARSE_INTEGRATION_TIME_A[15:8]
	//{0x015B,0x02},// COARSE_INTEGRATION_TIME_A[7:0]
	//{0x015D,0x00},// SENSOR_MODE_A XX 0x025D SENSOR_MODE_B X
	//
#if 0 
	{0x0160, 0x04},//FRM_LENGTH_A[15:8] 1166
	{0x0161, 0x8e},//FRM_LENGTH_A[7:0] 1166     
	{0x0162, 0x0d},//0x0d},//LINE_LENGTH_A[15:8] 3476
	{0x0163, 0x94},//0x78},//LINE_LENGTH_A[7:0]
#else
	{0x0160, 0x08},//FRM_LENGTH_A[15:8] 1166
	{0x0161, 0x98},//FRM_LENGTH_A[7:0] 1166     
	{0x0162, 0x0d},//0x0d},//LINE_LENGTH_A[15:8] 3476
	{0x0163, 0x94},//0x78},//LINE_LENGTH_A[7:0]
#endif
	// 

#if 0
	{0x0164, 0x02}, //X_ADD_STA_A[11:8] 
	{0x0165, 0xa8},//X_ADD_STA_A[7:0] 
	{0x0166, 0x0a}, //X_ADD_END_A[11:8] 
	{0x0167, 0x27}, //X_ADD_END_A[7:0] 
	//
	{0x0168, 0x02},//Y_ADD_STA_A[11:8] 
	{0x0169, 0xb4},//Y_ADD_STA_A[7:0] 
	{0x016a, 0x06},//Y_ADD_END_A[11:8] 
	{0x016b, 0xeb},//Y_ADD_END_A[7:0] 
	//
	{0x016c, 0x07},//x_output_size[11:8] 
	{0x016d, 0x80},//x_output_size[7:0]
	{0x016e, 0x04},//y_output_size[11:8] 
	{0x016f, 0x38},// y_output_size[7:0] 
#else
/*
	{0x0164, 0x02}, //X_ADD_STA_A[11:8] 			//216 (0xd8)
	{0x0165, 0xa8}, //X_ADD_STA_A[7:0] 
	{0x0166, 0x06}, //X_ADD_END_A[11:8] 			// 216 + 1080 - 1  = 1296 (0x510)
	{0x0167, 0xdf}, //X_ADD_END_A[7:0] 
	//
	{0x0168, 0x01},//Y_ADD_STA_A[11:8] 				// 492( 0x1ec)
	{0x0169, 0xec},//Y_ADD_STA_A[7:0] 
	{0x016a, 0x09},//Y_ADD_END_A[11:8] 				// 492 + 1920 - 1 =2411 (0x96b)
	{0x016b, 0x6b},//Y_ADD_END_A[7:0]

	{0x016c, 0x04},//x_output_size[11:8] 							// 1080 
	{0x016d, 0x38},//x_output_size[7:0]
	{0x016e, 0x07},//y_output_size[11:8] 							// 1920 
	{0x016f, 0x80},// y_output_size[7:0] 
*/

	{0x0164, 0x02}, //X_ADD_STA_A[11:8]    680 + 1080 - 1                      3476 * 2200
	{0x0165, 0xb4},//X_ADD_STA_A[7:0] 
	{0x0166, 0x06}, //X_ADD_END_A[11:8]  1771
	{0x0167, 0xeb}, //X_ADD_END_A[7:0] 
	
	//
	{0x0168, 0x01},//Y_ADD_STA_A[11:8] 
	{0x0169, 0x00},//Y_ADD_STA_A[7:0] 
	{0x016a, 0x08},//Y_ADD_END_A[11:8]  		2175	
	{0x016b, 0x7f},//Y_ADD_END_A[7:0] 
	//
	{0x016c, 0x04},//x_output_size[11:8] 
	{0x016d, 0x38},//x_output_size[7:0]
	{0x016e, 0x07},//y_output_size[11:8] 
	{0x016f, 0x80},// y_output_size[7:0] 

#endif
	//
	{0x0170, 0x01},//X_ODD_INC_A
	{0x0171, 0x01},//Y_ODD_INC_A
	//
	{0x0172, 0x00},//IMG_ORIENTATION_A
	//BINNING
	{0x0174, 0x00},//BINNING_MODE_H_A
	{0x0175, 0x00},//BINNING_MODE_V_A
	//{0x0176, 0x00},//BINNING_CAL_MODE_H_A
	//{0x0177, 0x00},//BINNING_CAL_MODE_V_A
	//
	//{0x0189,0x00},//ANA_GAIN_GLOBAL_SHORT_A
	//{0x018A,0x00},//COARSE_INTEG_TIME_SHORT_A 
	//{0x018B,0x00},//COARSE_INTEG_TIME_SHORT_A
	// 
	//{0x018C,0x00},//CSI_DATA_FORMAT_A [15:8]
	//{0x018D,0x00},//CSI_DATA_FORMAT_A [7:0]	
	//LSC
	//{0x0190,0x00},//LSC_ENABLE_A
	//{0x0191,0x00},//LSC_COLOR_MODE_A
	//{0x0192,0x00},//LSC_SELECT_TABLE_A 
	//{0x0193,0x00},//LSC_TUNING_ENABLE_A
	//{0x0194,0x00},//LSC_WHITE_BALANCE_RG_A[15:8]
	//{0x0195,0x00},//LSC_WHITE_BALANCE_RG_A[7:0]
	//{0x0198,0x00), //LSC_TUNING_COEF_R_A
	//{0x0199,0x00), //LSC_TUNING_COEF_GR_A 
	//{0x019A,0x00), //LSC_TUNING_COEF_GB_A 
	//{0x019B,0x00), //LSC_TUNING_COEF_B_A
	//{0x019C,0x00), //LSC_TUNING_R_A[12:8] 
	//{0x019D,0x00), //LSC_TUNING_R_A[7:0]
	//{0x019E,0x00), //LSC_TUNING_GR_A[12:8]
	//{0x019F,0x00), //LSC_TUNING_GR_A[7:0] 
	//{0x01A0,0x00), //LSC_TUNING_GB_A[12:8]
	//{0x01A1,0x00), //LSC_TUNING_GB_A[7:0] 
	//{0x01A2,0x00), //LSC_TUNING_B_A[12:8] 
	//{0x01A3,0x00), //LSC_TUNING_B_A[7:0]
	//{0x01A4,0x00), //LSC_KNOT_POINT_FORMAT_A
	//
	{0x0301, 0x05},//VTPXCK_DIV
	{0x0303, 0x01},//VTSYCK_DIV
	//
	{0x0304, 0x03},//PREPLLCK_VT_DIV
	{0x0305, 0x03},//PREPLLCK_OP_DIV
	//
#if 0 
	{0x0306, 0x00},//PLL_VT_MPY[10:8]
	{0x0307, 0x26},//0x25},//PLL_VT_MPY[7:0] 0x39
#else
	{0x0306, 0x00},//PLL_VT_MPY[10:8]
	{0x0307, 0x48},//0x25},//PLL_VT_MPY[7:0] 0x39
#endif
	//
	//{0x0309, 0x00},//OPPXCK_DIV
	//
	{0x030b, 0x01},//OPSYCK_DIV
	//
#if 0 
	{0x030c, 0x00},//PLL_OP_MPY[10:8] 
	{0x030d, 0x30},//PLL_OP_MPY[7:0] 0x72
#else
	{0x030c, 0x00},//PLL_OP_MPY[10:8] 
	{0x030d, 0x40},//PLL_OP_MPY[7:0] 0x72  0x56  0x51  0x40
#endif
//	{0x0157, 0x64},//analog gain
	//
	{0x0624, 0x07},
	{0x0625, 0x80},
	{0x0626, 0x04},
	{0x0627, 0x38},
	{0x455e, 0x00},
	{0x471e, 0x4b},
	{0x4767, 0x0f},
	{0x4750, 0x14},
	{0x4540, 0x00},
	{0x47b4, 0x14},
	{0x4713, 0x30},
	{0x478b, 0x10},
	{0x478f, 0x10},
	{0x4793, 0x10},
	{0x4797, 0x0e},
	{0x479b, 0x0e},
	{0x0157, 0x40},
	{0x0158, 0x01},
	{0x0159, 0x00},
	{0x015a, 0x03},
	{0x015b, 0xe8},

	//
    {0x0100, 0x01}, //REG_MODE_SEL
    {0xffff, 0xff},
};

void imx219_close_sensor(void)
{
	imx219_sensor_write(0x0100, 0x00);
}

static void imx219_1080_1920_p30_setting(void)
{
	int i = 0;
	while(mode_1080_1920_regs[i].addr != 0xffff)
	{
		imx219_sensor_write(mode_1080_1920_regs[i].addr,mode_1080_1920_regs[i].data);
		msleep(1);
		i++;
	}
}

static void imx219_rd_1080_1920_setting(void)
{
	int i = 0;
	while(mode_1080_1920_regs[i].addr != 0xffff)
	{
		imx219_sensor_read(mode_1080_1920_regs[i].addr);
		msleep(1);
		i++;
	}
}

void imx219_1080_1920_sensor_config(void)
{
    printf("Imx219_1080p30_init\n");
    imx219_1080_1920_p30_setting();
    imx219_rd_1080_1920_setting();
}

/**
 * @brief 
 * 
 */
static void imx219_1080p30_setting(void)
{
	int i = 0;
	while(mode_1920_1080_regs[i].addr != 0xffff)
	{
		imx219_sensor_write(mode_1920_1080_regs[i].addr,mode_1920_1080_regs[i].data);
		msleep(1);
		i++;
	}
}

/**
 * @brief 
 * 
 */
static void imx219_rd_setting(void)
{
	int i = 0;
	while(mode_1920_1080_regs[i].addr != 0xffff)
	{
		imx219_sensor_read(mode_1920_1080_regs[i].addr);
		msleep(1);
		i++;
	}
}
/**
 * @brief 
 * 
 */
void imx219_sensor_config(void)
{
    printf("Imx219_1080p30_init\n");
    imx219_1080p30_setting();
    imx219_rd_setting();
}
/**
 * @brief 
 * 
 */
void imx219_ae_dgain_cfg(unsigned int expl) 
{
    unsigned int shs1_cal;
    unsigned int shs1_low_byte;
    unsigned int shs1_high_byte;

    shs1_cal = 1166 - expl;
	if(shs1_cal < 1)
		shs1_cal = 1;
	if( shs1_cal > 1166 -3)
		shs1_cal = 1166 -3;
    shs1_low_byte = shs1_cal & 0xff;
    shs1_high_byte = (shs1_cal & 0xff00) >> 8;

    imx219_sensor_write(0x0159, shs1_low_byte);
    //msleep(1);
    imx219_sensor_write(0x0158, shs1_high_byte);
}
/**
 * @brief 
 * 
 */
void imx219_ae_again_cfg(unsigned int agc) 
{
    unsigned int agc_cal;
    unsigned int agc_low_byte;

    agc_cal = agc;// * 256;
    agc_low_byte = agc_cal & 0xff;

    //msleep(1);
    imx219_sensor_write(0x0157, agc_low_byte);
}
