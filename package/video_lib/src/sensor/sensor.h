/******************************************************************************

  Copyright (C), 2021, Canaan Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sensor.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _SENSOR_H_
#define _SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "isp_video.h"

struct regval_list {
	unsigned short addr;
	unsigned char data;
};
//imx385
void imx385_i2c_init(enum _SENSOR_I2C i2c_num);
void imx385_2k_wdr_sensor_config(void);
void imx385_sensor_config(void);
//jfx23s
void jfx23s_i2c_init(enum _SENSOR_I2C i2c_num);
void jxf23s_sensor_config(void);
void jxs23s_sensor_15fps_config(void);
//imx219
void imx219_i2c_init(enum _SENSOR_I2C i2c_num);

void imx219_sensor_config(void);
void imx219_1080_1920_sensor_config(void);

void imx219_ae_dgain_cfg(unsigned int expl);
void imx219_ae_again_cfg(unsigned int agc);
void imx219_close_sensor(void);

void imx219_sensor_720p_config(void);
void imx219_sensor_720p60_config(void);

void imx219_sensor_rga_480p75_config(void);
void imx219_sensor_rga_480p120_config(void);

#ifdef __cplusplus
}
#endif

#endif /*_SENSOR_H_*/