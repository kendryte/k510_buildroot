/*
 * cnds_dsi_test.h
 *
 *  Created on: Dec 14, 2019
 *      Author: Administrator
 */

#ifndef CNDS_DSI_TEST_H_
#define CNDS_DSI_TEST_H_
 void wait_phy_pll_locked();
 void wait_cklane_rdy();
 void wait_dat1_rdy();
 void wait_dat2_rdy();
 void wait_dat3_rdy();
 void wait_dat4_rdy();
void  dsc_cmd_send(int par, int data1, int data2);
void  aml_lcd_init();
void dsi_init_1080x1920();


#endif /* CNDS_DSI_TEST_H_ */
