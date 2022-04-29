/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mipi_txdphy.h
  Version       : Initial Draft
  Author        :
  Created       :
  Description   :
  History       :
  1.Date        :
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _MIPI_TXDPHY_DEF_H_
#define _MIPI_TXDPHY_DEF_H_

#define TXDPHY_PLL_891M_F           3563
#define TXDPHY_PLL_891M_R           24
#define TXDPHY_PLL_891M_D           3

#define TXDPHY_PLL_1782M_F          1781
#define TXDPHY_PLL_1782M_R          24
#define TXDPHY_PLL_1782M_D          0

#define TXDPHY_PLL_445M_F           1781
#define TXDPHY_PLL_445M_R           24
#define TXDPHY_PLL_445M_D           3

typedef enum
{
    TXDPHY_LANE_0 = 0,
    TXDPHY_LANE_1,
    TXDPHY_LANE_2,
    TXDPHY_LANE_3,
    TXDPHY_LANE_MAX,
} txdphy_lane_t;


void mipi_txdphy_set_pll(uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv);
void mipi_txdphy_init(void);
void mipi_txdphy_set_enlp(txdphy_lane_t lane);
void mipi_txdphy_set_tlpx(uint32_t level);
void mipi_txdphy_set_tlpxesc(uint32_t level);
void mipi_txdphy_set_tclkprep(uint32_t level);
void mipi_txdphy_set_tclkprzero(uint32_t level);
void mipi_txdphy_set_tclktail(uint32_t level);
void mipi_txdphy_set_thsprep(uint32_t level);
void mipi_txdphy_set_thsprzero(uint32_t level);
void mipi_txdphy_set_thstrail(uint32_t level);


#endif /*_MIPI_TXDPHY_DEF_H_*/
