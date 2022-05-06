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
/**
 * @file
 * @brief      MUXPIN
 *
 *             MUXPIN supports the following features:
 *
 *             - Field Programmable GPIO Array (FPIOA)
 *
 *             - 110 LSIO with 256 functions
 *
 *             - Schmitt trigger
 *
 *             - Pull up and pull down
 *
 *             - Driving selector
 *
 *             - Static input and output
 *
 */

/*
 * NOTE: This file is automatic generated, do not edit directly.
 * Please edit the generator instead.
 */

#ifndef _DRIVER_MUXPIN_H
#define _DRIVER_MUXPIN_H

#include <stdint.h>
//#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
/* Pad number settings */
#define LSIO_FUNC_NUM_IO    (108)
#define MUXPIN_NUM_IO    (128)
#define MUXPIN_FUCTION_MASK  (0x0000FFFFU)
#define MUXPIN_IONUM_MASK    (0xFFFF0000U)

/* clang-format on */

/**
 * @brief      FPIOA IO functions
 *
 * @note       FPIOA pin function table
 *
 * | Function  | Name                             | Description                       |
 * |-----------|----------------------------------|-----------------------------------|
 * | 0         | SPI1_D0                          | SPI0 Data 0                       |
 * | 1         | SPI1_D1                          | SPI0 Data 1                       |
 * | 2         | SPI1_D2                          | SPI0 Data 2                       |
 * | 3         | SPI1_D3                          | SPI0 Data 3                       |
 * | 4         | SPI1_D4                          | SPI0 Data 4                       |
 * | 5         | SPI1_D5                          | SPI0 Data 5                       |
 * | 6         | SPI1_D6                          | SPI0 Data 6                       |
 * | 7         | SPI1_D7                          | SPI0 Data 7                       |
 * | 8         | SPI1_SS0                         | SPI0 Chip Select 0                |
 * | 9         | SPI1_SCLK                        | SPI0 Serial Clock                 |
 * | 10        | GPIO0                            | GPIO pin 0                        |
 * | 11        | GPIO1                            | GPIO pin 1                        |
 * | 12        | GPIO2                            | GPIO pin 2                        |
 * | 13        | GPIO3                            | GPIO pin 3                        |
 * | 14        | GPIO4                            | GPIO pin 4                        |
 * | 15        | GPIO5                            | GPIO pin 5                        |
 * | 16        | GPIO6                            | GPIO pin 6                        |
 * | 17        | GPIO7                            | GPIO pin 7                        |
 * | 18        | GPIO8                            | GPIO pin 8                        |
 * | 19        | GPIO9                            | GPIO pin 9                        |
 * | 20        | GPIO10                           | GPIO pin 10                       |
 * | 21        | GPIO11                           | GPIO pin 11                       |
 * | 22        | GPIO12                           | GPIO pin 12                       |
 * | 23        | GPIO13                           | GPIO pin 13                       |
 * | 24        | GPIO14                           | GPIO pin 14                       |
 * | 25        | GPIO15                           | GPIO pin 15                       |
 * | 26        | GPIO16                           | GPIO pin 16                       |
 * | 27        | GPIO17                           | GPIO pin 17                       |
 * | 28        | GPIO18                           | GPIO pin 18                       |
 * | 29        | GPIO19                           | GPIO pin 19                       |
 * | 30        | GPIO20                           | GPIO pin 20                       |
 * | 31        | GPIO21                           | GPIO pin 21                       |
 * | 32        | GPIO22                           | GPIO pin 22                       |
 * | 33        | GPIO23                           | GPIO pin 23                       |
 * | 34        | GPIO24                           | GPIO pin 24                       |
 * | 35        | GPIO25                           | GPIO pin 25                       |
 * | 36        | GPIO26                           | GPIO pin 26                       |
 * | 37        | GPIO27                           | GPIO pin 27                       |
 * | 38        | GPIO28                           | GPIO pin 28                       |
 * | 39        | GPIO29                           | GPIO pin 29                       |
 * | 40        | GPIO30                           | GPIO pin 30                       |
 * | 41        | GPIO31                           | GPIO pin 31                       |
 * | 42        | SPI2_D0                          | SPI1 Data 0                       |
 * | 43        | SPI2_D1                          | SPI1 Data 1                       |
 * | 44        | SPI2_D2                          | SPI1 Data 2                       |
 * | 45        | SPI2_D3                          | SPI1 Data 3                       |
 * | 46        | SPI2_D4                          | SPI1 Data 4                       |
 * | 47        | SPI2_D5                          | SPI1 Data 5                       |
 * | 48        | SPI2_D6                          | SPI1 Data 6                       |
 * | 49        | SPI2_D7                          | SPI1 Data 7                       |
 * | 50        | SPI2_SS0                         | SPI1 Chip Select 0                |
 * | 51        | SPI2_SCLK                        | SPI1 Serial Clock                 |
 * | 52        | SPI_SLAVE_RXD                    | SPI Slave RX data                 |
 * | 53        | SPI_SLAVE_TXD                    | SPI Slave TX data                 |
 * | 54        | SPI_SLAVE_SS                     | SPI Slave Select                  |
 * | 55        | SPI_SLAVE_SCLK                   | SPI Slave Serial Clock            |
 * | 56        | I2S2SCLK                         | I2S0 Serial Clock(BCLK)           |
 * | 57        | I2S2WS                           | I2S0 Word Select(LRCLK)           |
 * | 58        | I2S2IN_D0                        | I2S0 Serial Data Input 0          |
 * | 59        | I2S2IN_D1                        | I2S0 Serial Data Input 1          |
 * | 60        | I2S2IN_D2                        | I2S0 Serial Data Input 2          |
 * | 61        | I2S2IN_D3                        | I2S0 Serial Data Input 3          |
 * | 62        | I2S2OUT_D0                       | I2S0 Serial Data Output 0         |
 * | 63        | I2S2OUT_D1                       | I2S0 Serial Data Output 1         |
 * | 64        | I2S2OUT_D2                       | I2S0 Serial Data Output 2         |
 * | 65        | I2S2OUT_D3                       | I2S0 Serial Data Output 3         |
 * | 66        | I2C0_SCLK                        | I2C0 Serial Clock                 |
 * | 67        | I2C0_SDA                         | I2C0 Serial Data                  |
 * | 68        | I2C1_SCLK                        | I2C1 Serial Clock                 |
 * | 69        | I2C1_SDA                         | I2C1 Serial Data                  |
 * | 70        | I2C2_SCLK                        | I2C2 Serial Clock                 |
 * | 71        | I2C2_SDA                         | I2C2 Serial Data                  |
 * | 72        | I2C3_SCLK                        | I2C3 Serial Clock                 |
 * | 73        | I2C3_SDA                         | I2C3 Serial Data                  |
 * | 74        | I2C4_SCLK                        | I2C4 Serial Clock                 |
 * | 75        | I2C4_SDA                         | I2C4 Serial Data                  |
 * | 76        | I2C5_SCLK                        | I2C5 Serial Clock                 |
 * | 77        | I2C5_SDA                         | I2C5 Serial Data                  |
 * | 78        | I2C6_SCLK                        | I2C6 Serial Clock                 |
 * | 79        | I2C6_SDA                         | I2C6 Serial Data                  |
 * | 80        | UART0_CTS                        | UART1 Clear To Send               |
 * | 81        | UART0_DSR                        | UART1 Data Set Ready              |
 * | 82        | UART0_DCD                        | UART1 Data Carrier Detect         |
 * | 83        | UART0_RI                         | UART1 Ring Indicator              |
 * | 84        | UART0_SIN                        |                                   |
 * | 85        | UART0_SIR_IN                     | UART1 Serial Infrared Input       |
 * | 86        | UART0_DTR                        | UART1 Data Terminal Ready         |
 * | 87        | UART0_RTS                        | UART1 Request To Send             |
 * | 88        | UART0_OUT2                       | UART1 User-designated Output 2    |
 * | 89        | UART0_OUT1                       | UART1 User-designated Output 1    |
 * | 90        | UART0_SOUT                       |                                   |
 * | 91        | UART0_SIR_OUT                    | UART1 Serial Infrared Output      |
 * | 92        | UART0_BAUD                       | UART1 Transmit Clock Output       |
 * | 93        | UART0_RE                         | UART1 Receiver Output Enable      |
 * | 94        | UART0_DE                         | UART1 Driver Output Enable        |
 * | 95        | UART0_RS485_EN                   | UART1 RS485 Enable                |
 * | 96        | UART1_CTS                        | UART2 Clear To Send               |
 * | 97        | UART1_DSR                        | UART2 Data Set Ready              |
 * | 98        | UART1_DCD                        | UART2 Data Carrier Detect         |
 * | 99        | UART1_RI                         | UART2 Ring Indicator              |
 * | 100       | UART1_SIN                        |                                   |
 * | 101       | UART1_SIR_IN                     | UART2 Serial Infrared Input       |
 * | 102       | UART1_DTR                        | UART2 Data Terminal Ready         |
 * | 103       | UART1_RTS                        | UART2 Request To Send             |
 * | 104       | UART1_OUT2                       | UART2 User-designated Output 2    |
 * | 105       | UART1_OUT1                       | UART2 User-designated Output 1    |
 * | 106       | UART1_SOUT                       |                                   |
 * | 107       | UART1_SIR_OUT                    | UART2 Serial Infrared Output      |
 * | 108       | UART1_BAUD                       | UART2 Transmit Clock Output       |
 * | 109       | UART1_RE                         | UART2 Receiver Output Enable      |
 * | 110       | UART1_DE                         | UART2 Driver Output Enable        |
 * | 111       | UART1_RS485_EN                   | UART2 RS485 Enable                |
 * | 112       | UART2_CTS                        | UART3 Clear To Send               |
 * | 113       | UART2_DSR                        | UART3 Data Set Ready              |
 * | 114       | UART2_DCD                        | UART3 Data Carrier Detect         |
 * | 115       | UART2_RI                         | UART3 Ring Indicator              |
 * | 116       | UART2_SIN                        |                                   |
 * | 117       | UART2_SIR_IN                     | UART3 Serial Infrared Input       |
 * | 118       | UART2_DTR                        | UART3 Data Terminal Ready         |
 * | 119       | UART2_RTS                        | UART3 Request To Send             |
 * | 120       | UART2_OUT2                       | UART3 User-designated Output 2    |
 * | 121       | UART2_OUT1                       | UART3 User-designated Output 1    |
 * | 122       | UART2_SOUT                       |                                   |
 * | 123       | UART2_SIR_OUT                    | UART3 Serial Infrared Output      |
 * | 124       | UART2_BAUD                       | UART3 Transmit Clock Output       |
 * | 125       | UART2_RE                         | UART3 Receiver Output Enable      |
 * | 126       | UART2_DE                         | UART3 Driver Output Enable        |
 * | 127       | UART2_RS485_EN                   | UART3 RS485 Enable                |
 * | 128       | UART3_CTS                        | UART3 Clear To Send               |
 * | 129       | UART3_DSR                        | UART3 Data Set Ready              |
 * | 130       | UART3_DCD                        | UART3 Data Carrier Detect         |
 * | 131       | UART3_RI                         | UART3 Ring Indicator              |
 * | 132       | UART3_SIN                        |                                   |
 * | 133       | UART3_SIR_IN                     | UART3 Serial Infrared Input       |
 * | 134       | UART3_DTR                        | UART3 Data Terminal Ready         |
 * | 135       | UART3_RTS                        | UART3 Request To Send             |
 * | 136       | UART3_OUT2                       | UART3 User-designated Output 2    |
 * | 137       | UART3_OUT1                       | UART3 User-designated Output 1    |
 * | 138       | UART3_SOUT                       |                                   |
 * | 139       | UART3_SIR_OUT                    | UART3 Serial Infrared Output      |
 * | 140       | UART3_BAUD                       | UART3 Transmit Clock Output       |
 * | 141       | UART3_RE                         | UART3 Receiver Output Enable      |
 * | 142       | UART3_DE                         | UART3 Driver Output Enable        |
 * | 143       | UART3_RS485_EN                   | UART3 RS485 Enable                |
 * | 144       | CLK_SPI2                         | Clock SPI2                        |
 * | 145       | CLK_I2C2                         | Clock I2C2                        |
 * | 146       | AUDIO_OUT_TDM_FSYNC              | TDM OUT FSYNC, pull down on evb board  |
 * | 147       | AUDIO_IN0                        | audio data in                     |
 * | 148       | AUDIO_IN1                        | audio data in                     |
 * | 149       | AUDIO_IN2                        | audio data in                     |
 * | 150       | AUDIO_IN3                        | audio data in                     |
 * | 151       | AUDIO_IN4                        | audio data in                     |
 * | 152       | AUDIO_IN5                        | audio data in                     |
 * | 153       | AUDIO_IN6                        | audio data in                     |
 * | 154       | AUDIO_IN7                        | audio data in                     |
 * | 155       | AUDIO_IN8                        | audio data in                     |
 * | 156       | AUDIO_IN9                        | audio data in                     |
 * | 157       | AUDIO_IN10                       | audio data in                     |
 * | 158       | AUDIO_IN11                       | audio data in                     |
 * | 159       | AUDIO_IN12                       | audio data in                     |
 * | 160       | AUDIO_IN13                       | audio data in                     |
 * | 161       | AUDIO_IN14                       | audio data in                     |
 * | 162       | AUDIO_IN15                       | audio data in                     |
 * | 163       | AUDIO_OUT0                       | audio data out                    |
 * | 164       | AUDIO_OUT1                       | audio data out                    |
 * | 165       | AUDIO_OUT2                       | audio data out                    |
 * | 166       | AUDIO_OUT3                       | audio data out                    |
 * | 167       | AUDIO_OUT4                       | audio data out                    |
 * | 168       | AUDIO_OUT5                       | audio data out                    |
 * | 169       | AUDIO_OUT6                       | audio data out                    |
 * | 170       | AUDIO_OUT7                       | audio data out                    |
 * | 171       | AUDIO_OUT_I2S_SCLK_GATE          | audio i2s sclk output (for data in and data out)  |
 * | 172       | AUDIO_OUT_I2S_SCLK_EN            | not used                          |
 * | 173       | AUDIO_INOUT_I2S_WS               | audio i2s ws output (for data in and data out)  |
 * | 174       | AUDIO_IN_TDM_FSYNC               | TDM IN FSYNC                      |
 * | 175       | VAD_IN_DATA                      |                                   |
 * | 176       | VAD_FSYNC                        |                                   |
 * | 177       | VAD_DEV_SCLK                     |                                   |
 * | 178       | PWM_PINS_1_IO_PINS_PWM_0_O_OVAL  |                                   |
 * | 179       | PWM_PINS_1_IO_PINS_PWM_1_O_OVAL  |                                   |
 * | 180       | PWM_PINS_1_IO_PINS_PWM_2_O_OVAL  |                                   |
 * | 181       | PWM_PINS_1_IO_PINS_PWM_3_O_OVAL  |                                   |
 * | 182       | PWM_PINS_1_IO_PINS_PWM_4_O_OVAL  |                                   |
 * | 183       | PWM_PINS_1_IO_PINS_PWM_5_O_OVAL  |                                   |
 * | 184       | PWM_PINS_1_IO_PINS_PWM_6_O_OVAL  |                                   |
 * | 185       | PWM_PINS_1_IO_PINS_PWM_7_O_OVAL  |                                   |
 * | 186       | I2C2AXI_SCLK                     |                                   |
 * | 187       | I2C2AXI_SDA                      |                                   |
 * | 188       | AUDIO_OUT_TDM_SCLK               | TDM OUT SCLK                      |
 * | 189       | AUDIO_OUT_PDM_SCLK               | PDM OUT SCLK                      |
 * | 190       | AUDIO_IN_I2S_TDM_PDM_SCLK        | TDM or PDM in sclk                |
 * | 191       | LSRESV6                          |                                   |
 * | 192       | LSRESV7                          |                                   |
 * | 193       | LSRESV8                          |                                   |
 * | 194       | LSRESV9                          |                                   |
 * | 195       | LSRESV10                         |                                   |
 * | 196       | LSRESV11                         |                                   |
 * | 197       | LSRESV12                         |                                   |
 * | 198       | LSRESV13                         |                                   |
 * | 199       | LSRESV14                         |                                   |
 * | 200       | LSRESV15                         |                                   |
 * | 201       | LSRESV16                         |                                   |
 * | 202       | LSRESV17                         |                                   |
 * | 203       | LSRESV18                         |                                   |
 * | 204       | LSRESV19                         |                                   |
 * | 205       | LSRESV20                         |                                   |
 * | 206       | LSRESV21                         |                                   |
 * | 207       | LSRESV22                         |                                   |
 * | 208       | LSRESV23                         |                                   |
 * | 209       | LSRESV24                         |                                   |
 * | 210       | LSRESV25                         |                                   |
 * | 211       | LSRESV26                         |                                   |
 * | 212       | LSRESV27                         |                                   |
 * | 213       | LSRESV28                         |                                   |
 * | 214       | LSRESV29                         |                                   |
 * | 215       | LSRESV30                         |                                   |
 * | 216       | LSRESV31                         |                                   |
 * | 217       | LSRESV32                         |                                   |
 * | 218       | LSRESV33                         |                                   |
 * | 219       | LSRESV34                         |                                   |
 * | 220       | LSRESV35                         |                                   |
 * | 221       | LSRESV36                         |                                   |
 * | 222       | LSRESV37                         |                                   |
 * | 223       | LSRESV38                         |                                   |
 * | 224       | LSRESV39                         |                                   |
 * | 225       | LSRESV40                         |                                   |
 * | 226       | LSRESV41                         |                                   |
 * | 227       | LSRESV42                         |                                   |
 * | 228       | LSRESV43                         |                                   |
 * | 229       | LSRESV44                         |                                   |
 * | 230       | LSRESV45                         |                                   |
 * | 231       | LSRESV46                         |                                   |
 * | 232       | LSRESV47                         |                                   |
 * | 233       | LSRESV48                         |                                   |
 * | 234       | LSRESV49                         |                                   |
 * | 235       | LSRESV50                         |                                   |
 * | 236       | LSRESV51                         |                                   |
 * | 237       | LSRESV52                         |                                   |
 * | 238       | LSRESV53                         |                                   |
 * | 239       | LSRESV54                         |                                   |
 * | 240       | LSRESV55                         |                                   |
 * | 241       | LSRESV56                         |                                   |
 * | 242       | LSRESV57                         |                                   |
 * | 243       | LSRESV58                         |                                   |
 * | 244       | LSRESV59                         |                                   |
 * | 245       | LSRESV60                         |                                   |
 * | 246       | LSRESV61                         |                                   |
 * | 247       | LSRESV62                         |                                   |
 * | 248       | LSRESV63                         |                                   |
 * | 249       | LSRESV64                         |                                   |
 * | 250       | LSRESV65                         |                                   |
 * | 251       | LSRESV66                         |                                   |
 * | 252       | LSRESV67                         |                                   |
 * | 253       | LSRESV68                         |                                   |
 * | 254       | LSRESV69                         |                                   |
 * | 255       | LSRESV_MAX                       |                                   |
 * | 256       | BOOT_CTL1                        |                                   |
 * | 257       | BOOT_CTL0                        |                                   |
 * | 258       | JTAG_TCK                         |                                   |
 * | 259       | JTAG_TDI                         |                                   |
 * | 260       | JTAG_TDO                         |                                   |
 * | 261       | JTAG_TMS                         |                                   |
 * | 262       | JTAG_TRSTN                       |                                   |
 * | 263       | MMC0_CLK                         |                                   |
 * | 264       | MMC0_CMD                         |                                   |
 * | 265       | MMC0_DATA7                       |                                   |
 * | 266       | MMC0_DATA6                       |                                   |
 * | 267       | MMC0_DATA5                       |                                   |
 * | 268       | MMC0_DATA4                       |                                   |
 * | 269       | MMC0_DATA3                       |                                   |
 * | 270       | MMC0_DATA2                       |                                   |
 * | 271       | MMC0_DATA1                       |                                   |
 * | 272       | MMC0_DATA0                       |                                   |
 * | 273       | MMC1_CLK                         |                                   |
 * | 274       | MMC1_CMD                         |                                   |
 * | 275       | MMC1_DATA3                       |                                   |
 * | 276       | MMC1_DATA2                       |                                   |
 * | 277       | MMC1_DATA1                       |                                   |
 * | 278       | MMC1_DATA0                       |                                   |
 * | 279       | MMC2_CLK                         |                                   |
 * | 280       | MMC2_CMD                         |                                   |
 * | 281       | MMC2_DATA3                       |                                   |
 * | 282       | MMC2_DATA2                       |                                   |
 * | 283       | MMC2_DATA1                       |                                   |
 * | 284       | MMC2_DATA0                       |                                   |
 * | 285       | MMC_SLV_CLK                      |                                   |
 * | 286       | MMC_SLV_CMD                      |                                   |
 * | 287       | MMC_SLV_DATA3                    |                                   |
 * | 288       | MMC_SLV_DATA2                    |                                   |
 * | 289       | MMC_SLV_DATA1                    |                                   |
 * | 290       | MMC_SLV_DATA0                    |                                   |
 * | 291       | EMAC_TX_CLK_OUT                  | EMAC output tx clock              |
 * | 292       | EMAC_TX_CLK_IN                   | EMAC input tx clock               |
 * | 293       | EMAC_REF_OUT                     | EMAC RMII output ref clock        |
 * | 294       | EMAC_REF_IN                      | EMAC RMII input erf clock         |
 * | 295       | EMAC_RX_CLK_OUT                  | EMAC output rx clock              |
 * | 296       | EMAC_RX_CLK_IN                   | EMAC input rx clock               |
 * | 297       | EMAC_COL                         | EMAC Collision detect from the PHY  |
 * | 298       | EMAC_CRS                         | EMAC Carrier sense from the PHY   |
 * | 299       | EMAC_TX_ER                       | EMAC Transmit error signal to the PHY  |
 * | 300       | EMAC_RX_ER                       | EMAC Receive error signal from the PHY  |
 * | 301       | EMAC_MDC                         | EMAC Management data clock to pin  |
 * | 302       | EMAC_MDIO                        | EMAC Management data input/out pin  |
 * | 303       | EMAC_RX_CTL                      | EMAC Receive control signal from the PHY.  |
 * | 304       | EMAC_RX_DV                       | EMAC Receive control signal from the PHY.  |
 * | 305       | EMAC_TX_CTL                      | EMAC Transmit control signal to the PHY  |
 * | 306       | EMAC_TX_EN                       | EMAC Transmit enable to the PHY   |
 * | 307       | EMAC_RX_D3                       | EMAC Receive data from the PHY    |
 * | 308       | EMAC_RX_D2                       | EMAC Receive data from the PHY    |
 * | 309       | EMAC_RX_D1                       | EMAC Receive data from the PHY    |
 * | 310       | EMAC_RX_D0                       | EMAC Receive data from the PHY    |
 * | 311       | EMAC_TX_D3                       | EMAC Transmit data to the PHY     |
 * | 312       | EMAC_TX_D2                       | EMAC Transmit data to the PHY     |
 * | 313       | EMAC_TX_D1                       | EMAC Transmit data to the PHY     |
 * | 314       | EMAC_TX_D0                       | EMAC Transmit data to the PHY     |
 * | 315       | DVP_D0                           | DVP interface data input          |
 * | 316       | DVP_D1                           | DVP interface data input          |
 * | 317       | DVP_D2                           | DVP interface data input          |
 * | 318       | DVP_D3                           | DVP interface data input          |
 * | 319       | DVP_D4                           | DVP interface data input          |
 * | 320       | DVP_D5                           | DVP interface data input          |
 * | 321       | DVP_D6                           | DVP interface data input          |
 * | 322       | DVP_D7                           | DVP interface data input          |
 * | 323       | DVP_D8                           | DVP interface data input          |
 * | 324       | DVP_D9                           | DVP interface data input          |
 * | 325       | DVP_D10                          | DVP interface data input          |
 * | 326       | DVP_D11                          | DVP interface data input          |
 * | 327       | DVP_D12                          | DVP interface data input          |
 * | 328       | DVP_D13                          | DVP interface data input          |
 * | 329       | DVP_D14                          | DVP interface data input          |
 * | 330       | DVP_D15                          | DVP interface data input          |
 * | 331       | DVP_VSYNC                        | DVP interface VSYNC input         |
 * | 332       | DVP_HREF                         | DVP interface HSYNC input         |
 * | 333       | HSRESV21                         |                                   |
 * | 334       | DVP_PCLK                         | DVP interface clk input           |
 * | 335       | BT1120_OUT_DATA_D0               | BT1120 interface output Y data    |
 * | 336       | BT1120_OUT_DATA_D1               | BT1120 interface output Y data    |
 * | 337       | BT1120_OUT_DATA_D2               | BT1120 interface output Y data    |
 * | 338       | BT1120_OUT_DATA_D3               | BT1120 interface output Y data    |
 * | 339       | BT1120_OUT_DATA_D4               | BT1120 interface output Y data    |
 * | 340       | BT1120_OUT_DATA_D5               | BT1120 interface output Y data    |
 * | 341       | BT1120_OUT_DATA_D6               | BT1120 interface output Y data    |
 * | 342       | BT1120_OUT_DATA_D7               | BT1120 interface output Y data    |
 * | 343       | BT1120_OUT_DATA_C0               | BT1120 interface output C data    |
 * | 344       | BT1120_OUT_DATA_C1               | BT1120 interface output C data    |
 * | 345       | BT1120_OUT_DATA_C2               | BT1120 interface output C data    |
 * | 346       | BT1120_OUT_DATA_C3               | BT1120 interface output C data    |
 * | 347       | BT1120_OUT_DATA_C4               | BT1120 interface output C data    |
 * | 348       | BT1120_OUT_DATA_C5               | BT1120 interface output C data    |
 * | 349       | BT1120_OUT_DATA_C6               | BT1120 interface output C data    |
 * | 350       | BT1120_OUT_DATA_C7               | BT1120 interface output C data    |
 * | 351       | BT1120_OUT_CLK                   | BT1120 interface output CLK       |
 * | 352       | BT1120_OUT_VSYNC                 | BT1120 interface output VSYNC (Not necessary)  |
 * | 353       | BT1120_OUT_HSYNC                 | BT1120 interface output HSYNC (Not necessary)  |
 * | 354       | SPI0_CLK                         |                                   |
 * | 355       | SPI0_CS                          |                                   |
 * | 356       | SPI0_D0                          |                                   |
 * | 357       | SPI0_D1                          |                                   |
 * | 358       | SPI0_D2                          |                                   |
 * | 359       | SPI0_D3                          |                                   |
 * | 360       | SPI0_D4                          |                                   |
 * | 361       | SPI0_D5                          |                                   |
 * | 362       | SPI0_D6                          |                                   |
 * | 363       | SPI0_D7                          |                                   |
 * | 364       | HSRESV0                          |                                   |
 * | 365       | HSRESV1                          |                                   |
 * | 366       | HSRESV2                          |                                   |
 * | 367       | HSRESV3                          |                                   |
 * | 368       | HSRESV4                          |                                   |
 * | 369       | HSRESV5                          |                                   |
 * | 370       | HSRESV6                          |                                   |
 * | 371       | HSRESV7                          |                                   |
 * | 372       | HSRESV8                          |                                   |
 * | 373       | HSRESV9                          |                                   |
 * | 374       | HSRESV10                         |                                   |
 * | 375       | HSRESV11                         |                                   |
 * | 376       | HSRESV12                         |                                   |
 * | 377       | HSRESV13                         |                                   |
 * | 378       | HSRESV14                         |                                   |
 * | 379       | HSRESV15                         |                                   |
 * | 380       | HSRESV16                         |                                   |
 * | 381       | HSRESV17                         |                                   |
 * | 382       | HSRESV18                         |                                   |
 * | 383       | HSRESV19                         |                                   |
 * | 384       | DDR_BSR_TCK                      |                                   |
 * | 385       | DDR_BSR_TDI                      |                                   |
 * | 386       | DDR_BSR_TDO                      |                                   |
 * | 387       | DDR_BSR_TMS                      |                                   |
 * | 388       | DDR_BSR_TRSTN                    |                                   |
 * | 389       | HSRESV20                         |                                   |
 * | 390       | TEST_PIN0                        |                                   |
 * | 391       | TEST_PIN1                        |                                   |
 * | 392       | TEST_PIN2                        |                                   |
 * | 393       | TEST_PIN3                        |                                   |
 * | 394       | TEST_PIN4                        |                                   |
 * | 395       | TEST_PIN5                        |                                   |
 * | 396       | MAX                              |                                   |
 *
 * Any IO of FPIOA is a IO-function matrix.
 * The upper 32bit is IO number for high speed pin,
 * Because the high speed pin corresponds to a unique IO.
 * All IO have default reset function, after reset, re-configure
 * IO function is required.
 */

/* clang-format off */
typedef enum muxpin_function_e {
	FUNC_SPI1_D0                          = (0 << 16) | 0        ,	/*!< SPI0 Data 0                      */
	FUNC_SPI1_D1                          = (0 << 16) | 1        ,	/*!< SPI0 Data 1                      */
	FUNC_SPI1_D2                          = (0 << 16) | 2        ,	/*!< SPI0 Data 2                      */
	FUNC_SPI1_D3                          = (0 << 16) | 3        ,	/*!< SPI0 Data 3                      */
	FUNC_SPI1_D4                          = (0 << 16) | 4        ,	/*!< SPI0 Data 4                      */
	FUNC_SPI1_D5                          = (0 << 16) | 5        ,	/*!< SPI0 Data 5                      */
	FUNC_SPI1_D6                          = (0 << 16) | 6        ,	/*!< SPI0 Data 6                      */
	FUNC_SPI1_D7                          = (0 << 16) | 7        ,	/*!< SPI0 Data 7                      */
	FUNC_SPI1_SS0                         = (0 << 16) | 8        ,	/*!< SPI0 Chip Select 0               */
	FUNC_SPI1_SCLK                        = (0 << 16) | 9        ,	/*!< SPI0 Serial Clock                */
	FUNC_GPIO0                            = (0 << 16) | 10       ,	/*!< GPIO pin 0                       */
	FUNC_GPIO1                            = (0 << 16) | 11       ,	/*!< GPIO pin 1                       */
	FUNC_GPIO2                            = (0 << 16) | 12       ,	/*!< GPIO pin 2                       */
	FUNC_GPIO3                            = (0 << 16) | 13       ,	/*!< GPIO pin 3                       */
	FUNC_GPIO4                            = (0 << 16) | 14       ,	/*!< GPIO pin 4                       */
	FUNC_GPIO5                            = (0 << 16) | 15       ,	/*!< GPIO pin 5                       */
	FUNC_GPIO6                            = (0 << 16) | 16       ,	/*!< GPIO pin 6                       */
	FUNC_GPIO7                            = (0 << 16) | 17       ,	/*!< GPIO pin 7                       */
	FUNC_GPIO8                            = (0 << 16) | 18       ,	/*!< GPIO pin 8                       */
	FUNC_GPIO9                            = (0 << 16) | 19       ,	/*!< GPIO pin 9                       */
	FUNC_GPIO10                           = (0 << 16) | 20       ,	/*!< GPIO pin 10                      */
	FUNC_GPIO11                           = (0 << 16) | 21       ,	/*!< GPIO pin 11                      */
	FUNC_GPIO12                           = (0 << 16) | 22       ,	/*!< GPIO pin 12                      */
	FUNC_GPIO13                           = (0 << 16) | 23       ,	/*!< GPIO pin 13                      */
	FUNC_GPIO14                           = (0 << 16) | 24       ,	/*!< GPIO pin 14                      */
	FUNC_GPIO15                           = (0 << 16) | 25       ,	/*!< GPIO pin 15                      */
	FUNC_GPIO16                           = (0 << 16) | 26       ,	/*!< GPIO pin 16                      */
	FUNC_GPIO17                           = (0 << 16) | 27       ,	/*!< GPIO pin 17                      */
	FUNC_GPIO18                           = (0 << 16) | 28       ,	/*!< GPIO pin 18                      */
	FUNC_GPIO19                           = (0 << 16) | 29       ,	/*!< GPIO pin 19                      */
	FUNC_GPIO20                           = (0 << 16) | 30       ,	/*!< GPIO pin 20                      */
	FUNC_GPIO21                           = (0 << 16) | 31       ,	/*!< GPIO pin 21                      */
	FUNC_GPIO22                           = (0 << 16) | 32       ,	/*!< GPIO pin 22                      */
	FUNC_GPIO23                           = (0 << 16) | 33       ,	/*!< GPIO pin 23                      */
	FUNC_GPIO24                           = (0 << 16) | 34       ,	/*!< GPIO pin 24                      */
	FUNC_GPIO25                           = (0 << 16) | 35       ,	/*!< GPIO pin 25                      */
	FUNC_GPIO26                           = (0 << 16) | 36       ,	/*!< GPIO pin 26                      */
	FUNC_GPIO27                           = (0 << 16) | 37       ,	/*!< GPIO pin 27                      */
	FUNC_GPIO28                           = (0 << 16) | 38       ,	/*!< GPIO pin 28                      */
	FUNC_GPIO29                           = (0 << 16) | 39       ,	/*!< GPIO pin 29                      */
	FUNC_GPIO30                           = (0 << 16) | 40       ,	/*!< GPIO pin 30                      */
	FUNC_GPIO31                           = (0 << 16) | 41       ,	/*!< GPIO pin 31                      */
	FUNC_SPI2_D0                          = (0 << 16) | 42       ,	/*!< SPI1 Data 0                      */
	FUNC_SPI2_D1                          = (0 << 16) | 43       ,	/*!< SPI1 Data 1                      */
	FUNC_SPI2_D2                          = (0 << 16) | 44       ,	/*!< SPI1 Data 2                      */
	FUNC_SPI2_D3                          = (0 << 16) | 45       ,	/*!< SPI1 Data 3                      */
	FUNC_SPI2_D4                          = (0 << 16) | 46       ,	/*!< SPI1 Data 4                      */
	FUNC_SPI2_D5                          = (0 << 16) | 47       ,	/*!< SPI1 Data 5                      */
	FUNC_SPI2_D6                          = (0 << 16) | 48       ,	/*!< SPI1 Data 6                      */
	FUNC_SPI2_D7                          = (0 << 16) | 49       ,	/*!< SPI1 Data 7                      */
	FUNC_SPI2_SS0                         = (0 << 16) | 50       ,	/*!< SPI1 Chip Select 0               */
	FUNC_SPI2_SCLK                        = (0 << 16) | 51       ,	/*!< SPI1 Serial Clock                */
	FUNC_SPI_SLAVE_RXD                    = (0 << 16) | 52       ,	/*!< SPI Slave RX data                */
	FUNC_SPI_SLAVE_TXD                    = (0 << 16) | 53       ,	/*!< SPI Slave TX data                */
	FUNC_SPI_SLAVE_SS                     = (0 << 16) | 54       ,	/*!< SPI Slave Select                 */
	FUNC_SPI_SLAVE_SCLK                   = (0 << 16) | 55       ,	/*!< SPI Slave Serial Clock           */
	FUNC_I2S2SCLK                         = (0 << 16) | 56       ,	/*!< I2S0 Serial Clock(BCLK)          */
	FUNC_I2S2WS                           = (0 << 16) | 57       ,	/*!< I2S0 Word Select(LRCLK)          */
	FUNC_I2S2IN_D0                        = (0 << 16) | 58       ,	/*!< I2S0 Serial Data Input 0         */
	FUNC_I2S2IN_D1                        = (0 << 16) | 59       ,	/*!< I2S0 Serial Data Input 1         */
	FUNC_I2S2IN_D2                        = (0 << 16) | 60       ,	/*!< I2S0 Serial Data Input 2         */
	FUNC_I2S2IN_D3                        = (0 << 16) | 61       ,	/*!< I2S0 Serial Data Input 3         */
	FUNC_I2S2OUT_D0                       = (0 << 16) | 62       ,	/*!< I2S0 Serial Data Output 0        */
	FUNC_I2S2OUT_D1                       = (0 << 16) | 63       ,	/*!< I2S0 Serial Data Output 1        */
	FUNC_I2S2OUT_D2                       = (0 << 16) | 64       ,	/*!< I2S0 Serial Data Output 2        */
	FUNC_I2S2OUT_D3                       = (0 << 16) | 65       ,	/*!< I2S0 Serial Data Output 3        */
	FUNC_I2C0_SCLK                        = (0 << 16) | 66       ,	/*!< I2C0 Serial Clock                */
	FUNC_I2C0_SDA                         = (0 << 16) | 67       ,	/*!< I2C0 Serial Data                 */
	FUNC_I2C1_SCLK                        = (0 << 16) | 68       ,	/*!< I2C1 Serial Clock                */
	FUNC_I2C1_SDA                         = (0 << 16) | 69       ,	/*!< I2C1 Serial Data                 */
	FUNC_I2C2_SCLK                        = (0 << 16) | 70       ,	/*!< I2C2 Serial Clock                */
	FUNC_I2C2_SDA                         = (0 << 16) | 71       ,	/*!< I2C2 Serial Data                 */
	FUNC_I2C3_SCLK                        = (0 << 16) | 72       ,	/*!< I2C3 Serial Clock                */
	FUNC_I2C3_SDA                         = (0 << 16) | 73       ,	/*!< I2C3 Serial Data                 */
	FUNC_I2C4_SCLK                        = (0 << 16) | 74       ,	/*!< I2C4 Serial Clock                */
	FUNC_I2C4_SDA                         = (0 << 16) | 75       ,	/*!< I2C4 Serial Data                 */
	FUNC_I2C5_SCLK                        = (0 << 16) | 76       ,	/*!< I2C5 Serial Clock                */
	FUNC_I2C5_SDA                         = (0 << 16) | 77       ,	/*!< I2C5 Serial Data                 */
	FUNC_I2C6_SCLK                        = (0 << 16) | 78       ,	/*!< I2C6 Serial Clock                */
	FUNC_I2C6_SDA                         = (0 << 16) | 79       ,	/*!< I2C6 Serial Data                 */
	FUNC_UART0_CTS                        = (0 << 16) | 80       ,	/*!< UART1 Clear To Send              */
	FUNC_UART0_DSR                        = (0 << 16) | 81       ,	/*!< UART1 Data Set Ready             */
	FUNC_UART0_DCD                        = (0 << 16) | 82       ,	/*!< UART1 Data Carrier Detect        */
	FUNC_UART0_RI                         = (0 << 16) | 83       ,	/*!< UART1 Ring Indicator             */
	FUNC_UART0_SIN                        = (0 << 16) | 84       ,	/*!<                                  */
	FUNC_UART0_SIR_IN                     = (0 << 16) | 85       ,	/*!< UART1 Serial Infrared Input      */
	FUNC_UART0_DTR                        = (0 << 16) | 86       ,	/*!< UART1 Data Terminal Ready        */
	FUNC_UART0_RTS                        = (0 << 16) | 87       ,	/*!< UART1 Request To Send            */
	FUNC_UART0_OUT2                       = (0 << 16) | 88       ,	/*!< UART1 User-designated Output 2   */
	FUNC_UART0_OUT1                       = (0 << 16) | 89       ,	/*!< UART1 User-designated Output 1   */
	FUNC_UART0_SOUT                       = (0 << 16) | 90       ,	/*!<                                  */
	FUNC_UART0_SIR_OUT                    = (0 << 16) | 91       ,	/*!< UART1 Serial Infrared Output     */
	FUNC_UART0_BAUD                       = (0 << 16) | 92       ,	/*!< UART1 Transmit Clock Output      */
	FUNC_UART0_RE                         = (0 << 16) | 93       ,	/*!< UART1 Receiver Output Enable     */
	FUNC_UART0_DE                         = (0 << 16) | 94       ,	/*!< UART1 Driver Output Enable       */
	FUNC_UART0_RS485_EN                   = (0 << 16) | 95       ,	/*!< UART1 RS485 Enable               */
	FUNC_UART1_CTS                        = (0 << 16) | 96       ,	/*!< UART2 Clear To Send              */
	FUNC_UART1_DSR                        = (0 << 16) | 97       ,	/*!< UART2 Data Set Ready             */
	FUNC_UART1_DCD                        = (0 << 16) | 98       ,	/*!< UART2 Data Carrier Detect        */
	FUNC_UART1_RI                         = (0 << 16) | 99       ,	/*!< UART2 Ring Indicator             */
	FUNC_UART1_SIN                        = (0 << 16) | 100      ,	/*!<                                  */
	FUNC_UART1_SIR_IN                     = (0 << 16) | 101      ,	/*!< UART2 Serial Infrared Input      */
	FUNC_UART1_DTR                        = (0 << 16) | 102      ,	/*!< UART2 Data Terminal Ready        */
	FUNC_UART1_RTS                        = (0 << 16) | 103      ,	/*!< UART2 Request To Send            */
	FUNC_UART1_OUT2                       = (0 << 16) | 104      ,	/*!< UART2 User-designated Output 2   */
	FUNC_UART1_OUT1                       = (0 << 16) | 105      ,	/*!< UART2 User-designated Output 1   */
	FUNC_UART1_SOUT                       = (0 << 16) | 106      ,	/*!<                                  */
	FUNC_UART1_SIR_OUT                    = (0 << 16) | 107      ,	/*!< UART2 Serial Infrared Output     */
	FUNC_UART1_BAUD                       = (0 << 16) | 108      ,	/*!< UART2 Transmit Clock Output      */
	FUNC_UART1_RE                         = (0 << 16) | 109      ,	/*!< UART2 Receiver Output Enable     */
	FUNC_UART1_DE                         = (0 << 16) | 110      ,	/*!< UART2 Driver Output Enable       */
	FUNC_UART1_RS485_EN                   = (0 << 16) | 111      ,	/*!< UART2 RS485 Enable               */
	FUNC_UART2_CTS                        = (0 << 16) | 112      ,	/*!< UART3 Clear To Send              */
	FUNC_UART2_DSR                        = (0 << 16) | 113      ,	/*!< UART3 Data Set Ready             */
	FUNC_UART2_DCD                        = (0 << 16) | 114      ,	/*!< UART3 Data Carrier Detect        */
	FUNC_UART2_RI                         = (0 << 16) | 115      ,	/*!< UART3 Ring Indicator             */
	FUNC_UART2_SIN                        = (0 << 16) | 116      ,	/*!<                                  */
	FUNC_UART2_SIR_IN                     = (0 << 16) | 117      ,	/*!< UART3 Serial Infrared Input      */
	FUNC_UART2_DTR                        = (0 << 16) | 118      ,	/*!< UART3 Data Terminal Ready        */
	FUNC_UART2_RTS                        = (0 << 16) | 119      ,	/*!< UART3 Request To Send            */
	FUNC_UART2_OUT2                       = (0 << 16) | 120      ,	/*!< UART3 User-designated Output 2   */
	FUNC_UART2_OUT1                       = (0 << 16) | 121      ,	/*!< UART3 User-designated Output 1   */
	FUNC_UART2_SOUT                       = (0 << 16) | 122      ,	/*!<                                  */
	FUNC_UART2_SIR_OUT                    = (0 << 16) | 123      ,	/*!< UART3 Serial Infrared Output     */
	FUNC_UART2_BAUD                       = (0 << 16) | 124      ,	/*!< UART3 Transmit Clock Output      */
	FUNC_UART2_RE                         = (0 << 16) | 125      ,	/*!< UART3 Receiver Output Enable     */
	FUNC_UART2_DE                         = (0 << 16) | 126      ,	/*!< UART3 Driver Output Enable       */
	FUNC_UART2_RS485_EN                   = (0 << 16) | 127      ,	/*!< UART3 RS485 Enable               */
	FUNC_UART3_CTS                        = (0 << 16) | 128      ,	/*!< UART3 Clear To Send              */
	FUNC_UART3_DSR                        = (0 << 16) | 129      ,	/*!< UART3 Data Set Ready             */
	FUNC_UART3_DCD                        = (0 << 16) | 130      ,	/*!< UART3 Data Carrier Detect        */
	FUNC_UART3_RI                         = (0 << 16) | 131      ,	/*!< UART3 Ring Indicator             */
	FUNC_UART3_SIN                        = (0 << 16) | 132      ,	/*!<                                  */
	FUNC_UART3_SIR_IN                     = (0 << 16) | 133      ,	/*!< UART3 Serial Infrared Input      */
	FUNC_UART3_DTR                        = (0 << 16) | 134      ,	/*!< UART3 Data Terminal Ready        */
	FUNC_UART3_RTS                        = (0 << 16) | 135      ,	/*!< UART3 Request To Send            */
	FUNC_UART3_OUT2                       = (0 << 16) | 136      ,	/*!< UART3 User-designated Output 2   */
	FUNC_UART3_OUT1                       = (0 << 16) | 137      ,	/*!< UART3 User-designated Output 1   */
	FUNC_UART3_SOUT                       = (0 << 16) | 138      ,	/*!<                                  */
	FUNC_UART3_SIR_OUT                    = (0 << 16) | 139      ,	/*!< UART3 Serial Infrared Output     */
	FUNC_UART3_BAUD                       = (0 << 16) | 140      ,	/*!< UART3 Transmit Clock Output      */
	FUNC_UART3_RE                         = (0 << 16) | 141      ,	/*!< UART3 Receiver Output Enable     */
	FUNC_UART3_DE                         = (0 << 16) | 142      ,	/*!< UART3 Driver Output Enable       */
	FUNC_UART3_RS485_EN                   = (0 << 16) | 143      ,	/*!< UART3 RS485 Enable               */
	FUNC_CLK_SPI2                         = (0 << 16) | 144      ,	/*!< Clock SPI2                       */
	FUNC_CLK_I2C2                         = (0 << 16) | 145      ,	/*!< Clock I2C2                       */
	FUNC_AUDIO_OUT_TDM_FSYNC              = (0 << 16) | 146      ,	/*!< TDM OUT FSYNC, pull down on evb board */
	FUNC_AUDIO_IN0                        = (0 << 16) | 147      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN1                        = (0 << 16) | 148      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN2                        = (0 << 16) | 149      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN3                        = (0 << 16) | 150      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN4                        = (0 << 16) | 151      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN5                        = (0 << 16) | 152      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN6                        = (0 << 16) | 153      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN7                        = (0 << 16) | 154      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN8                        = (0 << 16) | 155      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN9                        = (0 << 16) | 156      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN10                       = (0 << 16) | 157      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN11                       = (0 << 16) | 158      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN12                       = (0 << 16) | 159      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN13                       = (0 << 16) | 160      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN14                       = (0 << 16) | 161      ,	/*!< audio data in                    */
	FUNC_AUDIO_IN15                       = (0 << 16) | 162      ,	/*!< audio data in                    */
	FUNC_AUDIO_OUT0                       = (0 << 16) | 163      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT1                       = (0 << 16) | 164      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT2                       = (0 << 16) | 165      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT3                       = (0 << 16) | 166      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT4                       = (0 << 16) | 167      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT5                       = (0 << 16) | 168      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT6                       = (0 << 16) | 169      ,	/*!< audio data out                   */
	FUNC_AUDIO_OUT7                       = (0 << 16) | 170      ,	/*!< audio data out                   */
	FUNC_AUDIO_INOUT_I2S_SCLK_GATE        = (0 << 16) | 171      ,	/*!< audio i2s sclk output (for data in and data out) */
	FUNC_AUDIO_OUT_I2S_SCLK_EN            = (0 << 16) | 172      ,	/*!< not used                         */
	FUNC_AUDIO_INOUT_I2S_WS               = (0 << 16) | 173      ,	/*!< audio i2s ws output (for data in and data out) */
	FUNC_AUDIO_IN_TDM_FSYNC               = (0 << 16) | 174      ,	/*!< TDM IN FSYNC                     */
	FUNC_VAD_IN_DATA                      = (0 << 16) | 175      ,	/*!<                                  */
	FUNC_VAD_FSYNC                        = (0 << 16) | 176      ,	/*!<                                  */
	FUNC_VAD_DEV_SCLK                     = (0 << 16) | 177      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_0_O_OVAL  = (0 << 16) | 178      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_1_O_OVAL  = (0 << 16) | 179      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_2_O_OVAL  = (0 << 16) | 180      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_3_O_OVAL  = (0 << 16) | 181      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_4_O_OVAL  = (0 << 16) | 182      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_5_O_OVAL  = (0 << 16) | 183      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_6_O_OVAL  = (0 << 16) | 184      ,	/*!<                                  */
	FUNC_PWM_PINS_1_IO_PINS_PWM_7_O_OVAL  = (0 << 16) | 185      ,	/*!<                                  */
	FUNC_I2C2AXI_SCLK                     = (0 << 16) | 186      ,	/*!<                                  */
	FUNC_I2C2AXI_SDA                      = (0 << 16) | 187      ,	/*!<                                  */
	FUNC_AUDIO_OUT_TDM_SCLK               = (0 << 16) | 188      ,	/*!< TDM OUT SCLK                     */
	FUNC_AUDIO_OUT_PDM_SCLK               = (0 << 16) | 189      ,	/*!< PDM OUT SCLK                     */
	FUNC_AUDIO_IN_TDM_PDM_SCLK            = (0 << 16) | 190      ,	/*!< TDM or PDM in sclk               */
	FUNC_LSRESV6                          = (0 << 16) | 191      ,	/*!<                                  */
	FUNC_LSRESV7                          = (0 << 16) | 192      ,	/*!<                                  */
	FUNC_LSRESV8                          = (0 << 16) | 193      ,	/*!<                                  */
	FUNC_LSRESV9                          = (0 << 16) | 194      ,	/*!<                                  */
	FUNC_LSRESV10                         = (0 << 16) | 195      ,	/*!<                                  */
	FUNC_LSRESV11                         = (0 << 16) | 196      ,	/*!<                                  */
	FUNC_LSRESV12                         = (0 << 16) | 197      ,	/*!<                                  */
	FUNC_LSRESV13                         = (0 << 16) | 198      ,	/*!<                                  */
	FUNC_LSRESV14                         = (0 << 16) | 199      ,	/*!<                                  */
	FUNC_LSRESV15                         = (0 << 16) | 200      ,	/*!<                                  */
	FUNC_LSRESV16                         = (0 << 16) | 201      ,	/*!<                                  */
	FUNC_LSRESV17                         = (0 << 16) | 202      ,	/*!<                                  */
	FUNC_LSRESV18                         = (0 << 16) | 203      ,	/*!<                                  */
	FUNC_LSRESV19                         = (0 << 16) | 204      ,	/*!<                                  */
	FUNC_LSRESV20                         = (0 << 16) | 205      ,	/*!<                                  */
	FUNC_LSRESV21                         = (0 << 16) | 206      ,	/*!<                                  */
	FUNC_LSRESV22                         = (0 << 16) | 207      ,	/*!<                                  */
	FUNC_LSRESV23                         = (0 << 16) | 208      ,	/*!<                                  */
	FUNC_LSRESV24                         = (0 << 16) | 209      ,	/*!<                                  */
	FUNC_LSRESV25                         = (0 << 16) | 210      ,	/*!<                                  */
	FUNC_LSRESV26                         = (0 << 16) | 211      ,	/*!<                                  */
	FUNC_LSRESV27                         = (0 << 16) | 212      ,	/*!<                                  */
	FUNC_LSRESV28                         = (0 << 16) | 213      ,	/*!<                                  */
	FUNC_LSRESV29                         = (0 << 16) | 214      ,	/*!<                                  */
	FUNC_LSRESV30                         = (0 << 16) | 215      ,	/*!<                                  */
	FUNC_LSRESV31                         = (0 << 16) | 216      ,	/*!<                                  */
	FUNC_LSRESV32                         = (0 << 16) | 217      ,	/*!<                                  */
	FUNC_LSRESV33                         = (0 << 16) | 218      ,	/*!<                                  */
	FUNC_LSRESV34                         = (0 << 16) | 219      ,	/*!<                                  */
	FUNC_LSRESV35                         = (0 << 16) | 220      ,	/*!<                                  */
	FUNC_LSRESV36                         = (0 << 16) | 221      ,	/*!<                                  */
	FUNC_LSRESV37                         = (0 << 16) | 222      ,	/*!<                                  */
	FUNC_LSRESV38                         = (0 << 16) | 223      ,	/*!<                                  */
	FUNC_LSRESV39                         = (0 << 16) | 224      ,	/*!<                                  */
	FUNC_LSRESV40                         = (0 << 16) | 225      ,	/*!<                                  */
	FUNC_LSRESV41                         = (0 << 16) | 226      ,	/*!<                                  */
	FUNC_LSRESV42                         = (0 << 16) | 227      ,	/*!<                                  */
	FUNC_LSRESV43                         = (0 << 16) | 228      ,	/*!<                                  */
	FUNC_LSRESV44                         = (0 << 16) | 229      ,	/*!<                                  */
	FUNC_LSRESV45                         = (0 << 16) | 230      ,	/*!<                                  */
	FUNC_LSRESV46                         = (0 << 16) | 231      ,	/*!<                                  */
	FUNC_LSRESV47                         = (0 << 16) | 232      ,	/*!<                                  */
	FUNC_LSRESV48                         = (0 << 16) | 233      ,	/*!<                                  */
	FUNC_LSRESV49                         = (0 << 16) | 234      ,	/*!<                                  */
	FUNC_LSRESV50                         = (0 << 16) | 235      ,	/*!<                                  */
	FUNC_LSRESV51                         = (0 << 16) | 236      ,	/*!<                                  */
	FUNC_LSRESV52                         = (0 << 16) | 237      ,	/*!<                                  */
	FUNC_LSRESV53                         = (0 << 16) | 238      ,	/*!<                                  */
	FUNC_LSRESV54                         = (0 << 16) | 239      ,	/*!<                                  */
	FUNC_LSRESV55                         = (0 << 16) | 240      ,	/*!<                                  */
	FUNC_LSRESV56                         = (0 << 16) | 241      ,	/*!<                                  */
	FUNC_LSRESV57                         = (0 << 16) | 242      ,	/*!<                                  */
	FUNC_LSRESV58                         = (0 << 16) | 243      ,	/*!<                                  */
	FUNC_LSRESV59                         = (0 << 16) | 244      ,	/*!<                                  */
	FUNC_LSRESV60                         = (0 << 16) | 245      ,	/*!<                                  */
	FUNC_LSRESV61                         = (0 << 16) | 246      ,	/*!<                                  */
	FUNC_LSRESV62                         = (0 << 16) | 247      ,	/*!<                                  */
	FUNC_LSRESV63                         = (0 << 16) | 248      ,	/*!<                                  */
	FUNC_LSRESV64                         = (0 << 16) | 249      ,	/*!<                                  */
	FUNC_LSRESV65                         = (0 << 16) | 250      ,	/*!<                                  */
	FUNC_LSRESV66                         = (0 << 16) | 251      ,	/*!<                                  */
	FUNC_LSRESV67                         = (0 << 16) | 252      ,	/*!<                                  */
	FUNC_LSRESV68                         = (0 << 16) | 253      ,	/*!<                                  */
	FUNC_LSRESV69                         = (0 << 16) | 254      ,	/*!<                                  */
	FUNC_LSRESV_MAX                       = (0 << 16) | 255      ,	/*!<                                  */
	FUNC_BOOT_CTL1                        = (0 << 16) | 256      ,	/*!<                                  */
	FUNC_BOOT_CTL0                        = (1 << 16) | 257      ,	/*!<                                  */
	FUNC_JTAG_TCK                         = (2 << 16) | 258      ,	/*!<                                  */
	FUNC_JTAG_TDI                         = (3 << 16) | 259      ,	/*!<                                  */
	FUNC_JTAG_TDO                         = (4 << 16) | 260      ,	/*!<                                  */
	FUNC_JTAG_TMS                         = (5 << 16) | 261      ,	/*!<                                  */
	FUNC_JTAG_TRSTN                       = (6 << 16) | 262      ,	/*!<                                  */
	FUNC_MMC0_CLK                         = (7 << 16) | 263      ,	/*!<                                  */
	FUNC_MMC0_CMD                         = (8 << 16) | 264      ,	/*!<                                  */
	FUNC_MMC0_DATA7                       = (9 << 16) | 265      ,	/*!<                                  */
	FUNC_MMC0_DATA6                       = (10 << 16) | 266      ,	/*!<                                  */
	FUNC_MMC0_DATA5                       = (11 << 16) | 267      ,	/*!<                                  */
	FUNC_MMC0_DATA4                       = (12 << 16) | 268      ,	/*!<                                  */
	FUNC_MMC0_DATA3                       = (13 << 16) | 269      ,	/*!<                                  */
	FUNC_MMC0_DATA2                       = (14 << 16) | 270      ,	/*!<                                  */
	FUNC_MMC0_DATA1                       = (15 << 16) | 271      ,	/*!<                                  */
	FUNC_MMC0_DATA0                       = (16 << 16) | 272      ,	/*!<                                  */
	FUNC_MMC1_CLK                         = (17 << 16) | 273      ,	/*!<                                  */
	FUNC_MMC1_CMD                         = (18 << 16) | 274      ,	/*!<                                  */
	FUNC_MMC1_DATA3                       = (19 << 16) | 275      ,	/*!<                                  */
	FUNC_MMC1_DATA2                       = (20 << 16) | 276      ,	/*!<                                  */
	FUNC_MMC1_DATA1                       = (21 << 16) | 277      ,	/*!<                                  */
	FUNC_MMC1_DATA0                       = (22 << 16) | 278      ,	/*!<                                  */
	FUNC_MMC2_CLK                         = (23 << 16) | 279      ,	/*!<                                  */
	FUNC_MMC2_CMD                         = (24 << 16) | 280      ,	/*!<                                  */
	FUNC_MMC2_DATA3                       = (25 << 16) | 281      ,	/*!<                                  */
	FUNC_MMC2_DATA2                       = (26 << 16) | 282      ,	/*!<                                  */
	FUNC_MMC2_DATA1                       = (27 << 16) | 283      ,	/*!<                                  */
	FUNC_MMC2_DATA0                       = (28 << 16) | 284      ,	/*!<                                  */
	FUNC_MMC_SLV_CLK                      = (23 << 16) | 285      ,	/*!<                                  */
	FUNC_MMC_SLV_CMD                      = (24 << 16) | 286      ,	/*!<                                  */
	FUNC_MMC_SLV_DATA3                    = (25 << 16) | 287      ,	/*!<                                  */
	FUNC_MMC_SLV_DATA2                    = (26 << 16) | 288      ,	/*!<                                  */
	FUNC_MMC_SLV_DATA1                    = (27 << 16) | 289      ,	/*!<                                  */
	FUNC_MMC_SLV_DATA0                    = (28 << 16) | 290      ,	/*!<                                  */
	FUNC_EMAC_TX_CLK_OUT                  = (29 << 16) | 291      ,	/*!< EMAC output tx clock             */
	FUNC_EMAC_TX_CLK_IN                   = (29 << 16) | 292      ,	/*!< EMAC input tx clock              */
	FUNC_EMAC_REF_OUT                     = (29 << 16) | 293      ,	/*!< EMAC RMII output ref clock       */
	FUNC_EMAC_REF_IN                      = (29 << 16) | 294      ,	/*!< EMAC RMII input erf clock        */
	FUNC_EMAC_RX_CLK_OUT                  = (30 << 16) | 295      ,	/*!< EMAC output rx clock             */
	FUNC_EMAC_RX_CLK_IN                   = (30 << 16) | 296      ,	/*!< EMAC input rx clock              */
	FUNC_EMAC_COL                         = (31 << 16) | 297      ,	/*!< EMAC Collision detect from the PHY */
	FUNC_EMAC_CRS                         = (32 << 16) | 298      ,	/*!< EMAC Carrier sense from the PHY  */
	FUNC_EMAC_TX_ER                       = (33 << 16) | 299      ,	/*!< EMAC Transmit error signal to the PHY */
	FUNC_EMAC_RX_ER                       = (34 << 16) | 300      ,	/*!< EMAC Receive error signal from the PHY */
	FUNC_EMAC_MDC                         = (35 << 16) | 301      ,	/*!< EMAC Management data clock to pin */
	FUNC_EMAC_MDIO                        = (36 << 16) | 302      ,	/*!< EMAC Management data input/out pin */
	FUNC_EMAC_RX_CTL                      = (37 << 16) | 303      ,	/*!< EMAC Receive control signal from the PHY. */
	FUNC_EMAC_RX_DV                       = (37 << 16) | 304      ,	/*!< EMAC Receive control signal from the PHY. */
	FUNC_EMAC_TX_CTL                      = (38 << 16) | 305      ,	/*!< EMAC Transmit control signal to the PHY */
	FUNC_EMAC_TX_EN                       = (38 << 16) | 306      ,	/*!< EMAC Transmit enable to the PHY  */
	FUNC_EMAC_RX_D3                       = (39 << 16) | 307      ,	/*!< EMAC Receive data from the PHY   */
	FUNC_EMAC_RX_D2                       = (40 << 16) | 308      ,	/*!< EMAC Receive data from the PHY   */
	FUNC_EMAC_RX_D1                       = (41 << 16) | 309      ,	/*!< EMAC Receive data from the PHY   */
	FUNC_EMAC_RX_D0                       = (42 << 16) | 310      ,	/*!< EMAC Receive data from the PHY   */
	FUNC_EMAC_TX_D3                       = (43 << 16) | 311      ,	/*!< EMAC Transmit data to the PHY    */
	FUNC_EMAC_TX_D2                       = (44 << 16) | 312      ,	/*!< EMAC Transmit data to the PHY    */
	FUNC_EMAC_TX_D1                       = (45 << 16) | 313      ,	/*!< EMAC Transmit data to the PHY    */
	FUNC_EMAC_TX_D0                       = (46 << 16) | 314      ,	/*!< EMAC Transmit data to the PHY    */
	FUNC_DVP_D0                           = (47 << 16) | 315      ,	/*!< DVP interface data input         */
	FUNC_DVP_D1                           = (48 << 16) | 316      ,	/*!< DVP interface data input         */
	FUNC_DVP_D2                           = (49 << 16) | 317      ,	/*!< DVP interface data input         */
	FUNC_DVP_D3                           = (50 << 16) | 318      ,	/*!< DVP interface data input         */
	FUNC_DVP_D4                           = (51 << 16) | 319      ,	/*!< DVP interface data input         */
	FUNC_DVP_D5                           = (52 << 16) | 320      ,	/*!< DVP interface data input         */
	FUNC_DVP_D6                           = (53 << 16) | 321      ,	/*!< DVP interface data input         */
	FUNC_DVP_D7                           = (54 << 16) | 322      ,	/*!< DVP interface data input         */
	FUNC_DVP_D8                           = (55 << 16) | 323      ,	/*!< DVP interface data input         */
	FUNC_DVP_D9                           = (56 << 16) | 324      ,	/*!< DVP interface data input         */
	FUNC_DVP_D10                          = (57 << 16) | 325      ,	/*!< DVP interface data input         */
	FUNC_DVP_D11                          = (58 << 16) | 326      ,	/*!< DVP interface data input         */
	FUNC_DVP_D12                          = (59 << 16) | 327      ,	/*!< DVP interface data input         */
	FUNC_DVP_D13                          = (60 << 16) | 328      ,	/*!< DVP interface data input         */
	FUNC_DVP_D14                          = (61 << 16) | 329      ,	/*!< DVP interface data input         */
	FUNC_DVP_D15                          = (62 << 16) | 330      ,	/*!< DVP interface data input         */
	FUNC_DVP_VSYNC                        = (63 << 16) | 331      ,	/*!< DVP interface VSYNC input        */
	FUNC_DVP_HREF                         = (64 << 16) | 332      ,	/*!< DVP interface HSYNC input        */
	FUNC_HSRESV21                         = (65 << 16) | 333      ,	/*!<                                  */
	FUNC_DVP_PCLK                         = (66 << 16) | 334      ,	/*!< DVP interface clk input          */
	FUNC_BT1120_OUT_DATA_D0               = (67 << 16) | 335      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D1               = (68 << 16) | 336      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D2               = (69 << 16) | 337      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D3               = (70 << 16) | 338      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D4               = (71 << 16) | 339      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D5               = (72 << 16) | 340      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D6               = (73 << 16) | 341      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_D7               = (74 << 16) | 342      ,	/*!< BT1120 interface output Y data   */
	FUNC_BT1120_OUT_DATA_C0               = (75 << 16) | 343      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C1               = (76 << 16) | 344      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C2               = (77 << 16) | 345      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C3               = (78 << 16) | 346      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C4               = (79 << 16) | 347      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C5               = (80 << 16) | 348      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C6               = (81 << 16) | 349      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_DATA_C7               = (82 << 16) | 350      ,	/*!< BT1120 interface output C data   */
	FUNC_BT1120_OUT_CLK                   = (83 << 16) | 351      ,	/*!< BT1120 interface output CLK      */
	FUNC_BT1120_OUT_VSYNC                 = (84 << 16) | 352      ,	/*!< BT1120 interface output VSYNC (Not necessary) */
	FUNC_BT1120_OUT_HSYNC                 = (85 << 16) | 353      ,	/*!< BT1120 interface output HSYNC (Not necessary) */
	FUNC_SPI0_CLK                         = (86 << 16) | 354      ,	/*!<                                  */
	FUNC_SPI0_CS                          = (87 << 16) | 355      ,	/*!<                                  */
	FUNC_SPI0_D0                          = (88 << 16) | 356      ,	/*!<                                  */
	FUNC_SPI0_D1                          = (89 << 16) | 357      ,	/*!<                                  */
	FUNC_SPI0_D2                          = (90 << 16) | 358      ,	/*!<                                  */
	FUNC_SPI0_D3                          = (91 << 16) | 359      ,	/*!<                                  */
	FUNC_SPI0_D4                          = (92 << 16) | 360      ,	/*!<                                  */
	FUNC_SPI0_D5                          = (93 << 16) | 361      ,	/*!<                                  */
	FUNC_SPI0_D6                          = (94 << 16) | 362      ,	/*!<                                  */
	FUNC_SPI0_D7                          = (95 << 16) | 363      ,	/*!<                                  */
	FUNC_HSRESV0                          = (96 << 16) | 364      ,	/*!<                                  */
	FUNC_HSRESV1                          = (97 << 16) | 365      ,	/*!<                                  */
	FUNC_HSRESV2                          = (98 << 16) | 366      ,	/*!<                                  */
	FUNC_HSRESV3                          = (99 << 16) | 367      ,	/*!<                                  */
	FUNC_HSRESV4                          = (100 << 16) | 368      ,	/*!<                                  */
	FUNC_HSRESV5                          = (101 << 16) | 369      ,	/*!<                                  */
	FUNC_HSRESV6                          = (102 << 16) | 370      ,	/*!<                                  */
	FUNC_HSRESV7                          = (103 << 16) | 371      ,	/*!<                                  */
	FUNC_HSRESV8                          = (104 << 16) | 372      ,	/*!<                                  */
	FUNC_HSRESV9                          = (105 << 16) | 373      ,	/*!<                                  */
	FUNC_HSRESV10                         = (106 << 16) | 374      ,	/*!<                                  */
	FUNC_HSRESV11                         = (107 << 16) | 375      ,	/*!<                                  */
	FUNC_HSRESV12                         = (108 << 16) | 376      ,	/*!<                                  */
	FUNC_HSRESV13                         = (109 << 16) | 377      ,	/*!<                                  */
	FUNC_HSRESV14                         = (110 << 16) | 378      ,	/*!<                                  */
	FUNC_HSRESV15                         = (111 << 16) | 379      ,	/*!<                                  */
	FUNC_HSRESV16                         = (112 << 16) | 380      ,	/*!<                                  */
	FUNC_HSRESV17                         = (113 << 16) | 381      ,	/*!<                                  */
	FUNC_HSRESV18                         = (114 << 16) | 382      ,	/*!<                                  */
	FUNC_HSRESV19                         = (115 << 16) | 383      ,	/*!<                                  */
	FUNC_DDR_BSR_TCK                      = (116 << 16) | 384      ,	/*!<                                  */
	FUNC_DDR_BSR_TDI                      = (117 << 16) | 385      ,	/*!<                                  */
	FUNC_DDR_BSR_TDO                      = (118 << 16) | 386      ,	/*!<                                  */
	FUNC_DDR_BSR_TMS                      = (119 << 16) | 387      ,	/*!<                                  */
	FUNC_DDR_BSR_TRSTN                    = (120 << 16) | 388      ,	/*!<                                  */
	FUNC_HSRESV20                         = (121 << 16) | 389      ,	/*!<                                  */
	FUNC_TEST_PIN0                        = (122 << 16) | 390      ,	/*!<                                  */
	FUNC_TEST_PIN1                        = (123 << 16) | 391      ,	/*!<                                  */
	FUNC_TEST_PIN2                        = (124 << 16) | 392      ,	/*!<                                  */
	FUNC_TEST_PIN3                        = (125 << 16) | 393      ,	/*!<                                  */
	FUNC_TEST_PIN4                        = (126 << 16) | 394      ,	/*!<                                  */
	FUNC_TEST_PIN5                        = (127 << 16) | 395      ,	/*!<                                  */
	FUNC_MAX                              = (255 << 16) | 396      ,	/*!<                                  */
} muxpin_function_t;
/* clang-format on */

/**
 * @brief      FPIOA pull settings
 *
 * @note       FPIOA pull settings description
 *
 * | PU  | PD  | Description                       |
 * |-----|-----|-----------------------------------|
 * | 0   | 0   | No Pull                           |
 * | 0   | 1   | Pull Down                         |
 * | 1   | 0   | Pull Up                           |
 * | 1   | 1   | Undefined                         |
 *
 */

/* clang-format off */
typedef enum muxpin_pull_e {
	MUXPIN_PULL_NONE,      /*!< No Pull */
	MUXPIN_PULL_DOWN,      /*!< Pull Down */
	MUXPIN_PULL_UP,        /*!< Pull Up */
	MUXPIN_PULL_MAX        /*!< Count of pull settings */
} muxpin_pull_t;
/* clang-format on */

/**
 * @brief      FPIOA driving settings
 *
 * @note       FPIOA driving settings description
 *             There are 16 kinds of driving settings
 *
 * @note       Low Level Output Current
 *
 * |DS[3:0] |Min(mA)|Typ(mA)|Max(mA)|
 * |--------|-------|-------|-------|
 * |0000    |3.2    |5.4    |8.3    |
 * |0001    |4.7    |8.0    |12.3   |
 * |0010    |6.3    |10.7   |16.4   |
 * |0011    |7.8    |13.2   |20.2   |
 * |0100    |9.4    |15.9   |24.2   |
 * |0101    |10.9   |18.4   |28.1   |
 * |0110    |12.4   |20.9   |31.8   |
 * |0111    |13.9   |23.4   |35.5   |
 *
 * @note       High Level Output Current
 *
 * |DS[3:0] |Min(mA)|Typ(mA)|Max(mA)|
 * |--------|-------|-------|-------|
 * |0000    |5.0    |7.6    |11.2   |
 * |0001    |7.5    |11.4   |16.8   |
 * |0010    |10.0   |15.2   |22.3   |
 * |0011    |12.4   |18.9   |27.8   |
 * |0100    |14.9   |22.6   |33.3   |
 * |0101    |17.4   |26.3   |38.7   |
 * |0110    |19.8   |30.0   |44.1   |
 * |0111    |22.3   |33.7   |49.5   |
 *
 */

/* clang-format off */
typedef enum muxpin_driving_e {
	MUXPIN_DRIVING_0,      /*!< 000 */
	MUXPIN_DRIVING_1,      /*!< 001 */
	MUXPIN_DRIVING_2,      /*!< 010 */
	MUXPIN_DRIVING_3,      /*!< 011 */
	MUXPIN_DRIVING_4,      /*!< 100 */
	MUXPIN_DRIVING_5,      /*!< 101 */
	MUXPIN_DRIVING_6,      /*!< 110 */
	MUXPIN_DRIVING_7,      /*!< 111 */
	MUXPIN_DRIVING_MAX     /*!< Count of driving settings */
} muxpin_driving_t;
/* clang-format on */

/**
 * @brief      FPIOA IO
 *
 *             FPIOA IO is the specific pin of the chip package. Every IO
 *             has a 32bit width register that can independently implement
 *             schmitt trigger, invert input, invert output, strong pull
 *             up, driving selector, static input and static output. And more,
 *             it can implement any pin of any peripheral devices.
 *
 * @note       FPIOA IO's register bits Layout
 *
 * | Bits      | Name     |Description                                        |
 * |-----------|----------|---------------------------------------------------|
 * | 31        | PAD_DI   | Read current IO's data input.                     |
 * | 30:24     | NA       | Reserved bits.                                    |
 * | 23:16     | LSIO_SEL | If IO_SEL is 0, use this to choose LSIO func      |
 * | 15:12     | NA       | Reserved bits.                                    |
 * | 11:10     | IO_SEL   | Use this to choose IO func                        |
 * |  9        | SL       | Slew rate control enable.                         |
 * |  8        | IO_MSC   | Output enable.It can disable or enable IO output. |
 * |  7        | IE_EN    | Input enable. It can disable or enable IO input.  |
 * |  6        | OE_EN    | Output enable.It can disable or enable IO output. |
 * |  5        | PU       | Pull enable.                                      |
 * |  4        | PD       | Pull select: 0 for pull down, 1 for pull up.      |
 * | 3:1       | DS       | Driving selector.                                 |
 * |  0        | ST       | Schmitt trigger.                                  |
 *
 */
typedef struct mux_config {
    uint32_t st : 1;
	/*!< Schmitt trigger. */
	uint32_t ds : 3;
	/*!< Driving selector. */
	uint32_t pd : 1;
	/*!< Pull down enable. 0 for nothing, 1 for pull down. */
	uint32_t pu : 1;
	/*!< Pull up enable. 0 for nothing, 1 for pull up. */
	uint32_t oe_en : 1;
	/*!< Static output enable. */
	uint32_t ie_en : 1;
	/*!< Static output enable. */
	uint32_t msc : 1;
	/*!< msc control bit. */
	uint32_t sl : 1;
	/*!< Slew rate control enable. */
	/*!< IO config setting. */
	uint32_t io_sel : 2;
	/*!< set io function mode. */
	uint32_t resv0 : 4;
	/*!< Reserved bits. */
	uint32_t lsio_sel : 8;
	/*!< if io function mode is lsio, set lsio function connection. */
	uint32_t resv1 : 7;
	/*!< Reserved bits. */
	uint32_t pad_di : 1;
	/*!< Read current IO's data input. */
} muxpin_config_t __attribute__((aligned(4)));

/**
 * @brief      FPIOA Object
 *
 *             FPIOA Object have 48 IO pin object and 256 bit input tie bits.
 *             All SPI arbitration signal will tie high by default.
 *
 * @note       FPIOA IO Pin RAM Layout
 *
 * | Address   | Name     |Description                     |
 * |-----------|----------|--------------------------------|
 *
 */
typedef struct _muxpin_t {
	muxpin_config_t io[MUXPIN_NUM_IO];
	/*!< FPIOA GPIO multiplexer io array */
} muxpin_t __attribute__((aligned(4)));

typedef enum muxpin_io_voltage_e
{
    MUXPIN_IO_VOLTAGE_1V8 = 0,
    MUXPIN_IO_VOLTAGE_3V3 = 1,
}muxpin_io_voltage_t;
/**
 * @brief      FPIOA object instanse
 */
extern volatile muxpin_t *const muxpin;

/**
 * @brief      Initialize FPIOA user custom default settings
 *
 * @note       This function will set all FPIOA pad registers to user-defined
 *             values from kconfig
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_init(void);

/**
 * @brief      Get IO configuration
 *
 * @param[in]  number  The IO number
 * @param      cfg     Pointer to struct of IO configuration for specified IO
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_get_config(int number, muxpin_config_t *cfg);

/**
 * @brief      Set IO configuration
 *
 * @param[in]  number  The IO number
 * @param[in]  cfg     Pointer to struct of IO configuration for specified IO
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_set_config(int number, muxpin_config_t *cfg);

/**
 * @brief      Set IO configuration with function number
 *
 * @note       The default IO configuration which bind to function number will
 *             set automatically
 *
 * @param[in]  number    The IO number, if high speed pin(function & 0xFFFF > 255), the number is ignored
 * @param[in]  function  The function enum number
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_set_function_raw(int number, muxpin_function_t function);

/**
 * @brief      Set only IO configuration with function number
 *
 * @note       The default IO configuration which bind to function number will
 *             set automatically
 *
 * @param[in]  number    The IO number, if high speed pin(function & 0xFFFF > 255), the number is ignored
 * @param[in]  function  The function enum number
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_set_function(int number, muxpin_function_t function);

/**
 * @brief      Set IO pull function
 *
 * @param[in]  number  The IO number
 * @param[in]  pull    The pull enum number
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_set_io_pull(int number, muxpin_pull_t pull);

/**
 * @brief      Get IO pull function
 *
 * @param[in]  number  The IO number
 *
 * @return     result
 *     - -1    Fail
 *     - Other The pull enum number
 */
int muxpin_get_io_pull(int number);

/**
 * @brief      Set IO driving
 *
 * @param[in]  number   The IO number
 * @param[in]  driving  The driving enum number
 *
 * @return     result
 *     - 0     Success
 *     - Other Fail
 */
int muxpin_set_io_driving(int number, muxpin_driving_t driving);

/**
 * @brief      Get IO driving
 *
 * @param[in]  number  The IO number
 *
 * @return     result
 *     - -1    Fail
 *     - Other The driving enum number
 */
int muxpin_get_io_driving(int number);

/**
 * @brief      Set io voltage
 *
 * @param[in]  number  The IO number
 *
 * @return     result
 *     - -1    Fail
 */
int muxpin_set_bank_voltage(int number,muxpin_io_voltage_t voltage);

/**
 * @brief      Get IO bank voltage
 *
 * @param[in]  number  The IO number
 *
 * @return     result 1v8 or 3v3
 */
muxpin_io_voltage_t muxpin_get_bank_voltage(int number);

void muxpin_default_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_MUXPIN_H */
