/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mipi_rxdphy.h
  Version       : Initial Draft
  Author        :
  Created       :
  Description   :
  History       :
  1.Date        :
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _MIPI_RXDPHY_DEF_H_
#define _MIPI_RXDPHY_DEF_H_

typedef enum
{
    RXDPHY_SPEED_MODE_2500M,
    RXDPHY_SPEED_MODE_1500M,
    RXDPHY_SPEED_MODE_MAX,
} rxdphy_speed_mode_t;

typedef enum
{
    RXDPHY_CHCFG_2X2,
    RXDPHY_CHCFG_1X4,
    RXDPHY_CHCFG_MAX,
} rxdphy_chcfg_t;


void mipi_rxdphy_init(rxdphy_speed_mode_t speed,rxdphy_chcfg_t chcfg);
unsigned int mipi_rxdphy_get_status(void);
unsigned int mipi_rxdphy_get_errstatus(void);
void mipi_rxdphy_standy(void);
void mipi_rxdphy_enable_deskew(void);
void mipi_rxdphy_disable_deskew(void);
void mipi_rxdphy_invert_lane(int lane);
void mipi_rxdphy_set_tclktermen(int enable);
void mipi_rxdphy_set_thstermen(int enable);
void mipi_rxdphy_set_thssettle(int value);
void mipi_rxdphy_settclkmiss(int value);
void mipi_rxdphy_set_tclksettle(int value);

#endif /*_MIPI_RXDPHY_DEF_H_*/
