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
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Device Specific Peripheral Registers structures
 ****************************************************************************/

#define __I                     volatile const	/* 'read only' permissions      */
#define __O                     volatile        /* 'write only' permissions     */
#define __IO                    volatile        /* 'read / write' permissions   */

/* k510 */
/*****************************************************************************
 * Memory Map
 ****************************************************************************/

#define _IO_(addr)              (addr)

/* k510 */
/* ax25mp and dsp*/
#define PLIC_MTIMER_BASE_ADDR 	    (0x9E000000U)
#define PLIC_SW_BASE_ADDR		    (0x9E400000U)
#define DEBUG_BASE_ADDR			    (0x9E800000U)
#define PLIC_BASE_ADDR      	    (0x9EC00000U)

/* ax25mp */
#define L2C_BASE_ADDR			    (0x9E900000U)

/* dsp */
#define DSP_ILM_BASE_ADDR			(0x00000000U)
#define DSP_DLM_BASE_ADDR			(0x00040000U)
#define DSP_ILM_SLAVE_BASE_ADDR		(0x99800000U)
#define DSP_DLM_SLAVE_BASE_ADDR		(0x99840000U)
#define DSP_FFT_BASE_ADDR           (0x9E000000U)
#define DSP_GEMV_BASE_ADDR			(0x9E900000U)

#define COMAHB_BASE_ADDR            (0x92000000U)
#define COMAPB_BASE_ADDR            (0x92400000U)

#define DDR_AHB_BASE_ADDR           (0x98000000U)

#define SRAM0_BASE_ADDR				(0x80000000U)
#define SRAM1_BASE_ADDR				(0x80100000U)

#define AES_BASE_ADDR               (0x91000000U)
#define SHA_BASE_ADDR               (0x91010000U)
#define OTP_BASE_ADDR               (0x91020000U)
#define RAS_BASE_ADDR               (0x91030000U)
#define ROM_BASE_ADDR               (0x91040000U)

#define USB_SLAVE_BASE_ADDR         (0x93060000U)
#define SD3_CONTROL_BASE_ADDR       (0x92400000U)

#define AI_BASE_BASE_ADDR			(0x92000000U)
// #define GNNE_BASE_ADDR           (0x92400000U)
// #define GEMM_BASE_ADDR			(0x92500000U)
#define ISP_BASE_ADDR               (0x92600000U)
#define DISPLAY_BASE_ADDR           (0x92700000U)
#define H264_BASE_ADDR              (0x92740000U)

#define SDHOST0_BASE_ADDR           (0x93000000U)
#define SDHOST1_BASE_ADDR           (0x93010000U)
#define SDHOST2_BASE_ADDR           (0x93020000U)
#define EMAC_BASE_ADDR              (0x93030000U)
#define PDMA_BASE_ADDR             (0x93040000U)
#define SDMA_BASE_ADDR            (0x93050000U)

#define GNNE_BASE_ADDR              (0x94000000U)

// #define USB2_BASE_ADDR              (0x94000000U)

#define UART0_BASE_ADDR     		(0x96000000U)
#define UART1_BASE_ADDR     		(0x96010000U)
#define UART2_BASE_ADDR     		(0x96020000U)
#define UART3_BASE_ADDR     		(0x96030000U)

// #define I2S0_BASE_ADDR      		(0x96030000U)
// #define I2S1_BASE_ADDR      		(0x96040000U)
#define I2S2_BASE_ADDR      		(0x96050000U)
#define AUDIO_BASE_ADDR				(0x96060000U)
// #define PDM_BASE_ADDR				(AUDIO_BASE_ADDR + 0x00U)
// #define TDM_BASE_ADDR      			(AUDIO_BASE_ADDR + 0xC8U)
#define SPI0_BASE_ADDR              (0x96080000U)
#define SPI1_BASE_ADDR              (0x96090000U)
#define SPI2_BASE_ADDR              (0x960A0000U)
#define SPI3_BASE_ADDR              (0x960B0000U)

#define SYSCTL_BASE_ADDR            (0x97000000U)
#define WDT0_BASE_ADDR              (0x97010000U)
#define WDT1_BASE_ADDR              (0x97020000U)
#define WDT2_BASE_ADDR              (0x97030000U)

#define IOMUX_BASE_ADDR             (0x97040000U)
#define GPIO_BASE_ADDR              (0x97050000U)
#define I2C0_BASE_ADDR              (0x97060000U)
#define I2C1_BASE_ADDR              (0x97070000U)
#define I2C2_BASE_ADDR              (0x97080000U)
#define I2C3_BASE_ADDR              (0x97090000U)
#define I2C4_BASE_ADDR              (0x970A0000U)
#define I2C5_BASE_ADDR              (0x970B0000U)
#define I2C6_BASE_ADDR              (0x970C0000U)
#define RTC_BASE_ADDR               (0x970D0000U)
#define MAILBOX_BASE_ADDR           (0x970E0000U)
#define PWM0_BASE_ADDR              (0x970F0000U)
#define PWM1_BASE_ADDR              (0x970F0040U)
#define VAD_BASE_ADDR               (0x97100000U)
#define TIMER_BASE_ADDR				(0x97200000U)

#define DDR_APB_BASE_ADDR           (0x98000000U)

#define AX25P_AXI_BASE_ADDR         (0x99800000U)

#define NIU_SERVICE_BASE_ADDR       (0x99900000U)


#define DSP_ILM_SIZE                (128 * 1024)
#define DSP_DLM_SIZE                (256 * 1024)

#ifdef __cplusplus
}
#endif

#endif	/* __PLATFORM_H__ */
