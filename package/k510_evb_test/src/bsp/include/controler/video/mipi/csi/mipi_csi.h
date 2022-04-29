#ifndef _MIPI_CSI_DEF_H_
#define _MIPI_CSI_DEF_H_

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_normal_30fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps_cs1(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps_cs1(void);
void cdns_mipi_reg_init_3840x2160_RAW12_mipi_4lane_OS8A10_noraml_10bit_7p5fps(void);
void csdn_opn8008_320x240_lane2_12bit(void);
void csdn_irs328c_224x172_lane2_12bit(void);
void cdns_mipi_reg_rd(void);
//
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_4lane_imx385_normal(void);
void csdn_imx385_1920x1080_lane2_12bit(void);
//
void csdn_opn8018_640x480_lane2_12bit(void);
void csdn_opn8018_640x480_lane4_12bit(void);
#endif /*_MIPI_CSI_DEF_H_*/
