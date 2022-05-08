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
#ifndef NOC_BANDWIDTH_H
#define NOC_BANDWIDTH_H
#include <stdint.h>

#define PROBE_MCTLP0_ADDR               (NIU_SERVICE_BASE_ADDR + 0x1000)
#define PROBE_MCTLP1_ADDR               (NIU_SERVICE_BASE_ADDR + 0x2000)
#define PROBE_MCTLP2_ADDR               (NIU_SERVICE_BASE_ADDR + 0x3000)
#define PROBE_MCTLP3_ADDR               (NIU_SERVICE_BASE_ADDR + 0x4000)


typedef enum PROBE_MCTLPX_IDX
{
    PROBE_MCTLP0		= 0x0,
    PROBE_MCTLP1		= 0x1,
    PROBE_MCTLP2		= 0x2,
    PROBE_MCTLP3		= 0x3
} probe_mctlpx_idx_t;

typedef struct mctlpx_filters {
    volatile uint32_t Filters_x_RouteIdBase;
    volatile uint32_t Filters_x_RouteIdMask;
    volatile uint32_t Filters_x_AddrBase_Low;
    volatile uint32_t Reserved_01[1];
    volatile uint32_t Filters_x_WindowSize;
    volatile uint32_t Reserved_02_03[2];
    volatile uint32_t Filters_x_Opcode;
    volatile uint32_t Filters_x_Status;
    volatile uint32_t Filters_x_Length;
    volatile uint32_t Filters_x_Urgency;
    volatile uint32_t Filters_x_UserBase;
    volatile uint32_t Filters_x_UserMask;
    volatile uint32_t Reserved_04_05[2];
} mctlpx_filters_t;

typedef struct mctlpx_counters {
    volatile uint32_t Counters_x_Src;
    volatile uint32_t Counters_x_AlarmMode;
    volatile uint32_t Counters_x_Val;
    volatile uint32_t Reserved_01_02[2];
} mctlpx_counters_t;


typedef struct probe_mctlpx_main_probe {
    volatile uint32_t Id_CoreId;		/* 0x0000 */
    volatile uint32_t Id_RevisionId;		/* 0x0004 */
    volatile uint32_t MainCtl;			/* 0x0008 */
    volatile uint32_t CfgCtl;			/* 0x000c */
    volatile uint32_t Reserved_00[1];		/* 0x0010 */
    volatile uint32_t FilterLut;		/* 0x0014 */
    volatile uint32_t TraceAlarmEn;		/* 0x0018 */
    volatile uint32_t TraceAlarmStatus;		/* 0x001c */
    volatile uint32_t TraceAlarmClr;		/* 0x0020 */
    volatile uint32_t StatPeriod;		/* 0x0024 */
    volatile uint32_t StatGo;			/* 0x0028 */
    volatile uint32_t StatAlarmMin;		/* 0x002c */
    volatile uint32_t StatAlarmMax;		/* 0x0030 */
    volatile uint32_t StatAlarmStatus;		/* 0x0034 */
    volatile uint32_t StatAlarmClr;		/* 0x0038 */
    volatile uint32_t StatAlarmEn;		/* 0x003c */
    volatile uint32_t Reserved_01[1];		/* 0x0040 */
    mctlpx_filters_t filters_0_3[4];		/* 0x0044 0x0130 */
    volatile uint32_t Reserved_22[1];		/* 0x0134 */
    mctlpx_counters_t counters_0_7[8];		/* 0x0138 0x01D4 */
} probe_mctlpx_main_probe_t;

typedef enum InitFlow
{
    STORAHBM_EMACAHBM		= 0x00,          // Flow:/spec/storAHBm/I/emacAHBm
    STORAHBM_SDC0AHBM		= 0x01,          // Flow:/spec/storAHBm/I/sdc0AHBm
    STORAHBM_SDC1AHBM		= 0x02,          // Flow:/spec/storAHBm/I/sdc1AHBm
    STORAHBM_SDC2AHBM		= 0x03,          // Flow:/spec/storAHBm/I/sdc2AHBm
    USBAHBM_SD3AHBM		= 0x04,          // Flow:/spec/usbAHBm/I/sd3AHBm  
    USBAHBM_USBAHBM		= 0x05,          // Flow:/spec/usbAHBm/I/usbAHBm  
    AIDATAAXIM			= 0x06,          // Flow:/spec/aiDataAXIm/I/0     
    AX25MAXIM			= 0x07,          // Flow:/spec/ax25mAXIm/I/0      
    AX25PAXIM			= 0x08,          // Flow:/spec/ax25pAXIm/I/0      
    DISPLAYAXIM			= 0x09,          // Flow:/spec/displayAXIm/I/0    
    GNNEAXIM			= 0x0A,          // Flow:/spec/gnneAXIm/I/0       
    H264AXIM			= 0x0B,          // Flow:/spec/h264AXIm/I/0       
    I2C2AXIM			= 0x0C,          // Flow:/spec/i2c2AXIm/I/0       
    ISPAXIM_3DTOF		= 0x0D,          // Flow:/spec/ispAXIm_3DTOF/I/0  
    ISPAXIM_F2K			= 0x0E,          // Flow:/spec/ispAXIm_F2K/I/0    
    ISPAXIM_MFCB		= 0x0F,          // Flow:/spec/ispAXIm_MFBC/I/0   
    ISPAXIM_R2K			= 0x10,          // Flow:/spec/ispAXIm_R2K/I/0    
    ISPAXIM_VI			= 0x11,          // Flow:/spec/ispAXIm_VI/I/0     
    PDMAAXIM			= 0x12,          // Flow:/spec/pdmaAXIm/I/0       
    SDMAAXIM			= 0x13,          // Flow:/spec/sdmaAXIm/I/0       
    TWODAXIM			= 0x14           // Flow:/spec/twodAXIm/I/0 
} InitFlow_t;

typedef enum TargFlow
{
    MCTLAXI0S			= 0x34,          // Flow:/spec/mctlAXI0s/T/0
    MCTLAXI1S			= 0x35,          // Flow:/spec/mctlAXI1s/T/0     
    MCTLAXI2S			= 0x36,          // Flow:/spec/mctlAXI2s/T/0     
    MCTLAXI3S			= 0x37,          // Flow:/spec/mctlAXI3s/T/0     
    RAM0AXIS			= 0x38,          // Flow:/spec/ram0AXIs/T/0      
    RAM1AXIS			= 0x39           // Flow:/spec/ram1AXIs/T/0
} TargFlow_t;

#define PROBE_MCTLP0_ID_COREID		0x04C9DF06
#define PROBE_MCTLP0_ID_REVISIONID	0xB085B900
#define PROBE_MCTLP1_ID_COREID		0x59669906
#define PROBE_MCTLP1_ID_REVISIONID	0xB085B900
#define PROBE_MCTLP2_ID_COREID		0xDD60C606
#define PROBE_MCTLP2_ID_REVISIONID	0xB085B900
#define PROBE_MCTLP3_ID_COREID		0xC2B1C606
#define PROBE_MCTLP3_ID_REVISIONID	0xB085B900

#define MAINCTL_ERREN				0x1
#define MAINCTL_TRACEEN				(0x1 << 1)
#define MAINCTL_PAYLOADEN			(0x1 << 2)
#define MAINCTL_STATEN				(0x1 << 3)
#define MAINCTL_ALARMEN				(0x1 << 4)
#define MAINCTL_STATCONDDIMP			(0x1 << 5)
#define MAINCTL_INTRUSIVEMODE			(0x1 << 6)
#define MAINCTL_FILTBYTEALWAYSCHAINABLEEN	(0x1 << 7)

#define CFGCTL_GLOBALEN				0x1
#define CFGCTL_ACTIVE				(0x1 << 1)

#define FILTERS_X_OPCODE_RDEN			0x1
#define FILTERS_X_OPCODE_WREN			(0x1 << 1)
#define FILTERS_X_OPCODE_LOCKEN			(0x1 << 2)
#define FILTERS_X_OPCODE_URGEN			(0x1 << 3)

#define FILTERS_X_STATUS_REQEN			0x1
#define FILTERS_X_STATUS_RSPEN			(0x1 << 1)


typedef enum Counters_M_Src
{
    OFF				= 0x0,		/* Counter disabled */
    CYCLE			= 0x1,		/* Probe clock cycles */
    IDLE			= 0x2,		/* Idle cycles during which no packet data is observed */
    XFER			= 0x3,		/* Transfer cycles during which packet data is transferred */
    BUSY			= 0x4,		/* Busy cycles during which the packet data is made available by the
						   transmitting agent but the receiving agent is not ready to receive it */
    WAIT			= 0x5,		/* Wait cycles during a packet in which the transmitting agent suspends
						   the transfer of packet data */
    PKT				= 0x6,		/* Packets */
    LUT				= 0x7,		/* Packets selected by the LUT */
    BYTE			= 0x8,		/* Total number of payload bytes */
    PRESS0			= 0x9,		/* Clock cycles with pressure level > 0 */
    PRESS1			= 0xA,		/* Clock cycles with pressure level > 1 */
    PRESS2			= 0xB,		/* Clock cycles with pressure level > 2 */
    FILT0			= 0xC,		/* Packets selected by Filter 0 */
    FILT1			= 0xD,		/* Packets selected by Filter 1 */
    FILT2			= 0xE,		/* Packets selected by Filter 2 */
    FILT3			= 0xF,		/* Packets selected by Filter 3 */
    CHAIN			= 0x10,		/* Carry from counter 2m to counter 2m + 1 */
    LUT_BYTE_EN			= 0x11,		/* Enabled payload byte in packets selected by the LUT */
    LUT_BYTE			= 0x12,		/* Total number of payload bytes in packets selected by the LUT */
    FILT_BYTE_EN		= 0x13,		/* Enabled payload byte in packets selected by the associated filter */
    FILT_BYTE			= 0x14		/* Total number of payload bytes in packets selected by the associated
						   filter */
} Counters_M_Src_t;

#define SEQID_OFFSET			0
#define TARG_SUBRANGE_OFFSET		6
#define TARG_FLOW_OFFSET		7
#define INIT_FLOW_OFFSET		13


#define FILTERS_M_ROUTEIDMASK		0xFFF
#define FILTERS_M_ROUTEIDMASK_OFFSET	TARG_SUBRANGE_OFFSET

#define FILTER_M_LENGTH			0xF

#define FILTER_0_INUSE 0x1
#define FILTER_1_INUSE (0x1 << 1)
#define FILTER_2_INUSE (0x1 << 2)
#define FILTER_3_INUSE (0x1 << 3)


typedef enum PROBE_STATUS {
        PROBE_IDLE = 0,
        PROBE_INUSE = 1
}probe_status_t;

struct probe_mctlpx_stat {
        probe_status_t probe_stat;
        unsigned int filters_inuse;
        unsigned int stat_period;
        unsigned int clk_freq;
        unsigned long cpu_cycles;
        unsigned int counters[8];

};

extern struct probe_mctlpx_stat probe_mctlpx_status[4];

/* configure probe_mctlpx_main_probe according to the initflow parameter.
 *
 * Please note: if you configure more than 1 flow in one mctl port, for example:
 * at first you configure DISPLAYAXIM,  and then configure ISPAXIM_R2K, both of the
 * operation will use the probe_mctlp2_main_probe,  the parameters such as
 * startaddr, windowsize and stat_period will be configured two times, and therefor,
 * only the last time you configured for ISPAXIM_R2K will be applied when you enable it.
 *
 * @initflow:           initflow to set, InitFlow_t type, invalid value is not accepted
 * @startaddr:          start address to set for the probe to monitor
 * @windowsize:         windowsize to set for the probe to minotor, with the startaddr
 * 			parameter to specify which address access will be monitored
 * @stat_period:        period to statistics
 *
 * return value:        mctl port index(value from 0 to 3) for success, -1 for failure
 *
 * */
extern probe_mctlpx_idx_t noc_probe_mctl_cfg(InitFlow_t initflow, unsigned int startaddr, unsigned int windowsize, unsigned int stat_period);


/* enable probe_mctlpx_main_probe to start statistics.
 *
 * @port_idx:        mctl port index, which is return by noc_probe_mctl_cfg.
 *
 * */
extern void noc_probe_mctlpx_enable(probe_mctlpx_idx_t port_idx);


/* disable probe_mctlpx_main_probe to stop statistics.
 *
 * @port_idx:        mctl port index, which is return by noc_probe_mctl_cfg.
 *
 * */
extern void noc_probe_mctlpx_disable(probe_mctlpx_idx_t port_idx);


/* read counters for all mctl ports, if the counter for high 16bits warps, print the counters value and
 * calculate the bandwidth.
 * can be called in in loop with short sleep, for example usleep(10), for accuracy.
 *
 * */
extern void noc_probe_mctl_bandwidth();


/* get counters value according to the port index and the filter index.
 *
 * @port_idx:           mctl port index, which is return by noc_probe_mctl_cfg.
 * @filter_idx:         filter index,
 *
 * return value:        return value of total bytes of the filter
 *
 * */
extern unsigned int noc_probe_get_counter_val(probe_mctlpx_idx_t port_idx, unsigned int filter_idx);


#endif
