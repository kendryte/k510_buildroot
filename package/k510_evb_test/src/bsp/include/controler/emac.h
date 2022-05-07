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
#ifndef _EMAC_H
#define _EMAC_H
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "emac_regs_non_vm.h"
#include <math.h>
#include "interrupt.h"
#include <k510_log.h>

#define EMAC_WORK_TIMEOUT        5000

typedef struct emac_regs emac_t;

extern volatile emac_t* const  emac;

typedef struct
{
    /** b31:0 of octets transmitted */
    uint32_t octetsTxLo;
    /** b47:32 of octets transmitted */
    uint16_t octetsTxHi;
    uint32_t framesTx;
    uint32_t broadcastTx;
    uint32_t multicastTx;
    uint16_t pauseFrTx;
    uint32_t fr64byteTx;
    uint32_t fr65_127byteTx;
    uint32_t fr128_255byteTx;
    uint32_t fr256_511byteTx;
    uint32_t fr512_1023byteTx;
    uint32_t fr1024_1518byteTx;
    uint32_t fr1519_byteTx;
    uint16_t underrunFrTx;
    uint32_t singleCollFrTx;
    uint32_t multiCollFrTx;
    uint16_t excessCollFrTx;
    uint16_t lateCollFrTx;
    uint32_t deferredFrTx;
    uint16_t carrSensErrsTx;
    /** b31:0 of octets received */
    uint32_t octetsRxLo;
    /** b47:32 of octets received */
    uint16_t octetsRxHi;
    uint32_t framesRx;
    uint32_t broadcastRx;
    uint32_t multicastRx;
    uint16_t pauseFrRx;
    uint32_t fr64byteRx;
    uint32_t fr65_127byteRx;
    uint32_t fr128_255byteRx;
    uint32_t fr256_511byteRx;
    uint32_t fr512_1023byteRx;
    uint32_t fr1024_1518byteRx;
    uint32_t fr1519_byteRx;
    uint16_t undersizeFrRx;
    uint16_t oversizeFrRx;
    uint16_t jabbersRx;
    uint16_t fcsErrorsRx;
    uint16_t lenChkErrRx;
    uint16_t rxSymbolErrs;
    uint16_t alignErrsRx;
    uint32_t rxResourcErrs;
    uint16_t overrunFrRx;
    uint16_t ipChksumErrs;
    uint16_t tcpChksumErrs;
    uint16_t udpChksumErrs;
    uint16_t dmaRxPBufFlush;
} emac_stats_t;

typedef struct
{
    uint32_t word0;
    uint32_t word1;
} emac_bd_t;

typedef struct
{
    uint32_t word0;
    uint32_t word1;
    uint32_t word2;
    uint32_t word3;
} emac_bd_timestamp_t;

typedef struct
{
    /** base address of descriptor ring */
    emac_bd_t* bdBase;
    /** first available descriptor */
    emac_bd_t* bdHead;
    /** first descriptor waiting to be freed */
    emac_bd_t* bdTail;
    /** total number of descriptors */
    uint16_t descMax;
    /** number of descriptors that can accept buffers */
    uint16_t descFree;
    /** length of rx buffers, as a multiple of 64 bytes */
    uint32_t buflength;
    /** descriptor counter used by qTxBuf: stays at 0 until start 2nd desc of frame, then inc to 1, etc. */
    uint8_t descUsed;
    /** Queue number */
    uint8_t qNumber;
} emac_rxqueue_t;

typedef struct
{
    /** base address of descriptor ring */
    emac_bd_timestamp_t* bdBase;
    /** first available descriptor */
    emac_bd_timestamp_t* bdHead;
    /** first descriptor waiting to be freed */
    emac_bd_timestamp_t* bdTail;
    /** total number of descriptors */
    uint16_t descMax;
    /** number of descriptors that can accept buffers */
    uint16_t descFree;
    /** length of rx buffers, as a multiple of 64 bytes */
    uint32_t buflength;
    /** descriptor counter used by qTxBuf: stays at 0 until start 2nd desc of frame, then inc to 1, etc. */
    uint8_t descUsed;
    /** Queue number */
    uint8_t qNumber;
} emac_rxtsqueue_t;

typedef struct
{
    /** base address of descriptor ring */
    emac_bd_t* bdBase;
    /** first available descriptor */
    emac_bd_t* bdHead;
    /** first descriptor waiting to be freed */
    emac_bd_t* bdTail;
    /** first buffer of current frame */
    emac_bd_t* bd1stBuf;
    /** total number of descriptors */
    uint16_t descMax;
    /** number of descriptors that can accept buffers */
    uint16_t descFree;
    /** virt address corresponding to head BD */
    uintptr_t* vHead;
    /** end of virt address circular array */
    uintptr_t* vTail;
    /** pointer to virt addresses storage */
    uintptr_t* vAddrList;
    /** flag indicating stage of frame clean-up: set when about to clear first buffer of frame */
    uint8_t firstToFree;
    /** descriptor counter used by qTxBuf: stays at 0 until start 2nd desc of frame, then inc to 1, etc. */
    uint8_t descUsed;
    /** Queue number */
    uint8_t qNumber;
} emac_txqueue_t;

typedef struct
{
    /** base address of descriptor ring */
    emac_bd_timestamp_t* bdBase;
    /** first available descriptor */
    emac_bd_timestamp_t* bdHead;
    /** first descriptor waiting to be freed */
    emac_bd_timestamp_t* bdTail;
    /** first buffer of current frame */
    emac_bd_timestamp_t* bd1stBuf;
    /** total number of descriptors */
    uint16_t descMax;
    /** number of descriptors that can accept buffers */
    uint16_t descFree;
    /** virt address corresponding to head BD */
    uintptr_t* vHead;
    /** end of virt address circular array */
    uintptr_t* vTail;
    /** pointer to virt addresses storage */
    uintptr_t* vAddrList;
    /** flag indicating stage of frame clean-up: set when about to clear first buffer of frame */
    uint8_t firstToFree;
    /** descriptor counter used by qTxBuf: stays at 0 until start 2nd desc of frame, then inc to 1, etc. */
    uint8_t descUsed;
    /** Queue number */
    uint8_t qNumber;
} emac_txtsqueue_t;

/** struct for returning contents of the Tx Status register */
typedef struct
{
    uint8_t usedBitRead;
    uint8_t collisionOcc;
    uint8_t retryLimExc;
    uint8_t txActive;
    uint8_t txFrameErr;
    uint8_t txComplete;
    uint8_t txUnderRun;
    uint8_t lateCollision;
    uint8_t hRespNotOk;
    uint8_t txMacLockup;
    uint8_t txDmaLockup;
} emac_txstatus_t;

/** struct for MAC address */
typedef struct
{
    uint8_t byte[6];
} emac_macaddress_t;

/* Ethernet frame structs */
/* simplest form, with Type/Len after source address */
typedef struct
{
    emac_macaddress_t dest;
    emac_macaddress_t src;
    uint8_t typeLenMsb;     /* ensure MSB-first format */
    uint8_t typeLenLsb;
} emac_ethhead_t;

typedef struct
{
    uint32_t queue_number   : 4;
    uint32_t dstc_match     : 8;
    uint32_t udp_prot_match : 16;
    uint32_t dstc_enable    : 1;
    uint32_t udp_port_match_enable : 1;
    uint32_t drop_on_match  : 1;
    uint32_t reserved1      : 1;
} emac_screen_type1_t;

typedef struct
{
    uint32_t queue_number       : 4;
    uint32_t vlan_priority      : 3;
    uint32_t reserved7          : 1;
    uint32_t vlan_enable        : 1;
    uint32_t ethertype_reg_index: 3;
    uint32_t ethertype_enable   : 1;
    uint32_t compare_a          : 5;
    uint32_t compare_a_enable   : 1;
    uint32_t compare_b          : 5;
    uint32_t compare_b_enable   : 1;
    uint32_t compare_c          : 5;
    uint32_t compare_c_enable   : 1;
    uint32_t drop_on_match      : 1;
} emac_screen_type2_t;

/** enum defining offset for screener type 2 compare values. Note the offset is applied after the specified point, e.g. T2COMP_OFF_ETYPE denotes the ethertype field, so an offset of 12 bytes from this would be the source IP address in an IP header. */
typedef enum
{
    EMAC_T2COMP_OFF_SOF = 0U,
    EMAC_T2COMP_OFF_ETYPE = 1U,
    EMAC_T2COMP_OFF_IPHDR = 2U,
    EMAC_T2COMP_OFF_TCPUDP = 3U,
    EMAC_T2COMP_OFF_VID_C_TAG = 4U,
    EMAC_T2COMP_OFF_VID_S_TAG = 5U
} emac_screen_type2_offset_t;

/** struct for writing/reading screener Type 2 compare registers */
typedef struct
{
    /** Mask Value field (or 1st 16 bits of compare when disableMask set) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t compMask;
    /** Compare Value field (or 2nd 16 bits of compare when disableMask set) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t compValue;
    /** Offset value $RANGE $FROM 0 $TO 63 $TEST_SUBSET 4 $ */
    uint8_t offsetVal;
    /** Position in frame to apply offset */
    emac_screen_type2_offset_t offsetPosition;
    /** Disable mask value function, to extend compare value to 4 bytes. Set to 1 to disable mask. $RANGE $FROM 0 $TO 1 $ */
    uint8_t disableMask;
} emac_screen_type2_compare_t;

typedef enum
{
    EMAC_SCREEN_TYPE1_REG0,
    EMAC_SCREEN_TYPE1_REG1,
    EMAC_SCREEN_TYPE1_REG2,
    EMAC_SCREEN_TYPE1_REG3,
    EMAC_SCREEN_TYPE1_REG4,
    EMAC_SCREEN_TYPE1_REG5,
    EMAC_SCREEN_TYPE1_REG6,
    EMAC_SCREEN_TYPE1_REG7,
    EMAC_SCREEN_TYPE1_REG8,
    EMAC_SCREEN_TYPE1_REG9,
    EMAC_SCREEN_TYPE1_REG10,
    EMAC_SCREEN_TYPE1_REG11,
    EMAC_SCREEN_TYPE1_REG12,
    EMAC_SCREEN_TYPE1_REG13,
    EMAC_SCREEN_TYPE1_REG14,
    EMAC_SCREEN_TYPE1_REG15,
    EMAC_SCREEN_TYPE1_REGMAX,
} emac_screen_type1_num_t;

typedef enum
{
    EMAC_SCREEN_TYPE2_REG0,
    EMAC_SCREEN_TYPE2_REG1,
    EMAC_SCREEN_TYPE2_REG2,
    EMAC_SCREEN_TYPE2_REG3,
    EMAC_SCREEN_TYPE2_REG4,
    EMAC_SCREEN_TYPE2_REG5,
    EMAC_SCREEN_TYPE2_REG6,
    EMAC_SCREEN_TYPE2_REG7,
    EMAC_SCREEN_TYPE2_REG8,
    EMAC_SCREEN_TYPE2_REG9,
    EMAC_SCREEN_TYPE2_REG10,
    EMAC_SCREEN_TYPE2_REG11,
    EMAC_SCREEN_TYPE2_REG12,
    EMAC_SCREEN_TYPE2_REG13,
    EMAC_SCREEN_TYPE2_REG14,
    EMAC_SCREEN_TYPE2_REG15,
    EMAC_SCREEN_TYPE2_REGMAX,
} emac_screen_type2_num_t;

typedef enum
{
    EMAC_SCREEN_TYPE2_ETHERTYPE0,
    EMAC_SCREEN_TYPE2_ETHERTYPE1,
    EMAC_SCREEN_TYPE2_ETHERTYPE2,
    EMAC_SCREEN_TYPE2_ETHERTYPE3,
    EMAC_SCREEN_TYPE2_ETHERTYPE4,
    EMAC_SCREEN_TYPE2_ETHERTYPE5,
    EMAC_SCREEN_TYPE2_ETHERTYPE6,
    EMAC_SCREEN_TYPE2_ETHERTYPE7,
} emac_screen_type2_ethertype_t;

typedef enum
{
    EMAC_SCREEN_TYPE2_COMPARE0,
    EMAC_SCREEN_TYPE2_COMPARE1,
    EMAC_SCREEN_TYPE2_COMPARE2,
    EMAC_SCREEN_TYPE2_COMPARE3,
    EMAC_SCREEN_TYPE2_COMPARE4,
    EMAC_SCREEN_TYPE2_COMPARE5,
    EMAC_SCREEN_TYPE2_COMPARE6,
    EMAC_SCREEN_TYPE2_COMPARE7,
    EMAC_SCREEN_TYPE2_COMPARE8,
    EMAC_SCREEN_TYPE2_COMPARE9,
    EMAC_SCREEN_TYPE2_COMPARE10,
    EMAC_SCREEN_TYPE2_COMPARE11,
    EMAC_SCREEN_TYPE2_COMPARE12,
    EMAC_SCREEN_TYPE2_COMPARE13,
    EMAC_SCREEN_TYPE2_COMPARE14,
    EMAC_SCREEN_TYPE2_COMPARE15,
    EMAC_SCREEN_TYPE2_COMPAREMAX,
} emac_screen_type2_compare_num_t;

/* VLan tag form, with VLAN tag after source address */
typedef struct {
    emac_macaddress_t dest;
    emac_macaddress_t srce;
    uint8_t vLanTpIdMsb;     /* ensure MSB-first format */
    uint8_t vLanTpIdLsb;
    uint8_t vLanTciMsb;
    uint8_t vLanTciLsb;
} ethHdr2_t;

/* Stacked VLan tag form, with two VLAN tags after source address */
typedef struct {
    emac_macaddress_t dest;
    emac_macaddress_t srce;
    uint8_t vLan1TpIdMsb;     /* ensure MSB-first format */
    uint8_t vLan1TpIdLsb;
    uint8_t vLan1TciMsb;
    uint8_t vLan1TciLsb;
    uint8_t vLan2TpIdMsb;
    uint8_t vLan2TpIdLsb;
    uint8_t vLan2TciMsb;
    uint8_t vLan2TciLsb;
} ethHdr3_t;

/** IPv4 address */
typedef struct {
    uint8_t byte[4];    /* byte[0] for first, i.e. top-level field */
} emac_ipv4_addr_t;

/* IPv4 header */
typedef struct {
    uint8_t ihlVers;        /* = 0x54 */
    uint8_t dsCp;           /* lower 6 bits, ignoring ECN use of b6 & b7 */
    uint8_t lengthMsb;      /* min 20 for header only */
    uint8_t lengthLsb;
    uint16_t iD;            /* identification */
    uint16_t flgsFragOffset;
    uint8_t ttL;
    uint8_t prot;
    uint16_t hdrChksum;
    emac_ipv4_addr_t srcAddr;
    emac_ipv4_addr_t dstAddr;
} iPv4Hdr_t;

/* UDP header */
typedef struct {
    uint8_t srcPortMsb;        /* source port number */
    uint8_t srcPortLsb;
    uint8_t dstPortMsb;        /* destination port number */
    uint8_t dstPortLsb;
    uint8_t lengthMsb;         /* length inc. header */
    uint8_t lengthLsb;
    uint8_t chkSumMsb;         /* CRC of header+data */
    uint8_t chkSumLsb;
} udpHdr_t;

/* PTP frame, IPv4, 1588 v1 */
typedef struct {
    /* ethernet header */
    emac_macaddress_t dest;       /* bytes 0-5 */
    emac_macaddress_t srce;       /* bytes 6-11 */
    uint8_t typeLenMsb;         /* MSB = 0x08 */
    uint8_t typeLenLsb;         /* LSB = 0x00 */
    /* IP header */
    uint8_t ihlVers;            /* = 0x45     byte 14 */
    uint8_t dsCp;               /* byte 15 */
    uint8_t lengthMsb;          /* byte 16 */
    uint8_t lengthLsb;          /* byte 17 */
    uint16_t iD;                /* bytes 18-19 */
    uint16_t flgsFragOffset;    /* bytes 20-21 */
    uint8_t ttL;                /* byte 22 */
    uint8_t prot;               /* = 0x11, UDP   byte 23 */
    uint8_t hdrChksum[2];       /* bytes 24-25 */
    emac_ipv4_addr_t srcAddr;       /* bytes 26-29 */
    emac_ipv4_addr_t dstAddr;       /* = 0xE0000181/82/83/84) bytes 30-33 */
    /* UDP header */
    uint8_t srcPortMsb;         /* source port number   byte 34 */
    uint8_t srcPortLsb;         /* byte 35 */
    uint8_t dstPortMsb;         /* = 0x01   destination port number   byte 36 */
    uint8_t dstPortLsb;         /* = 0x3F      byte 37 */
    uint8_t udpLenMsb;          /* length inc. header    byte 38 */
    uint8_t udpLenLsb;          /* byte 39 */
    uint8_t chkSumMsb;          /* CRC of header+data     byte 40 */
    uint8_t chkSumLsb;          /* byte 41 */
    /* PTP message */
    uint8_t ptpVers[2];         /* version PTP  = 0x0001   bytes 42-43 */
    uint8_t netVers[2];         /* version network  bytes 44-45 */
    uint8_t subDom[16];         /* subdomain   bytes 46-61 */
    uint8_t msgTyp;             /* message type =0x01 for event, 0x02 for general  byte 62 */
    uint8_t srcTech;            /* source comms technology  byte 63 */
    uint8_t srcUuid[6];         /* source Uuid  byte 64-69 */
    uint8_t srcPort[2];         /* source port ID  bytes 70-71 */
    uint8_t seqId[2];           /* sequence ID    bytes 72-73 */
    uint8_t ptpCtrl;            /* = 0x00 for sync, 0x01 for dlyReq   byte 74 */
    uint8_t resvd3;             /* byte 75 */
    uint8_t flags[2];           /* bytes 76-77 */
    uint8_t resvd4[4];          /* bytes 78-81 */
    uint8_t timeSec[4];         /* timeStamp seconds   bytes 82-85 */
    uint8_t timeNsec[4];        /* timeStamp nanoseconds   bytes 86-89 */
    uint8_t padding[78];        /* fields for sync/delay_req formats   bytes 90-167 */
} emac_ptpV1Frame_t;

/* PTP Event message frame, IPv4, 1588 v2 */
typedef struct {
    /* ethernet header */
    emac_macaddress_t dest;       /* bytes 0-5 */
    emac_macaddress_t srce;       /* bytes 6-11 */
    uint8_t typeLenMsb;         /* MSB = 0x08 */
    uint8_t typeLenLsb;         /* LSB = 0x00 */
    /* IP header */
    uint8_t ihlVers;            /* = 0x45     byte 14 */
    uint8_t dsCp;               /* byte 15 */
    uint8_t lengthMsb;          /* byte 16 */
    uint8_t lengthLsb;          /* byte 17 */
    uint16_t iD;                /* bytes 18-19 */
    uint16_t flgsFragOffset;    /* bytes 20-21 */
    uint8_t ttL;                /* byte 22 */
    uint8_t prot;               /* = 0x11, UDP   byte 23 */
    uint8_t hdrChksum[2];       /* bytes 24-25 */
    emac_ipv4_addr_t srcAddr;       /* bytes 26-29 */
    emac_ipv4_addr_t dstAddr;       /* = 0xE0000181/82/83/84) bytes 30-33 */
    /* UDP header */
    uint8_t srcPortMsb;         /* source port number   byte 34 */
    uint8_t srcPortLsb;         /* byte 35 */
    uint8_t dstPortMsb;         /* = 0x01   destination port number   byte 36 */
    uint8_t dstPortLsb;         /* = 0x3F      byte 37 */
    uint8_t udpLenMsb;          /* length inc. header    byte 38 */
    uint8_t udpLenLsb;          /* byte 39 */
    uint8_t chkSumMsb;          /* CRC of header+data     byte 40 */
    uint8_t chkSumLsb;          /* byte 41 */
    /* PTP message header */
    uint8_t trSpec_MsgType;     /* transport-specific upper nibble, messageType lower nibble:
                                   00 for sync, 02 for Pdelay_req, 03 for Pdelay_resp  byte 42 */
    uint8_t ptpVers;            /* = 0x02   byte 43 */
    uint8_t msgLenMsb;          /* length of PTP message, =34 bytes + message after header  bytes 44-45 */
    uint8_t msgLenLsb;
    uint8_t domNum;             /* domain number    byte 46 */
    uint8_t resvd1;             /* byte 47 */
    uint8_t flagField[2];       /* bytes 48-49 */
    uint8_t correct[8];         /* correction field   bytes 50-57 */
    uint8_t resvd2[4];          /* bytes 58-61 */
    uint8_t srcPrtId[10];       /* source port identity   bytes 62-71 */
    uint8_t seqId[2];           /* sequence ID    bytes 72-73 */
    uint8_t control;            /* control, dep on msgType   byte 74 */
    uint8_t logMsgInt;          /* log message interval   byte 75 */
    /* PTP Event message */
    uint8_t timestamp[10];      /* origin/receive timestamp      bytes 76-85 */
    uint8_t reqPortId[10];      /* used for delay_resp/pdelay_resp formats   bytes 86-95*/
} emac_ptpV2Frame_t;

typedef struct {
    emac_macaddress_t dest;
    emac_macaddress_t srce;
    uint8_t typeLenMsb;     /* = 0x88 type: MAC control frame */
    uint8_t typeLenLsb;     /* = 0x08 */
    uint8_t opcodeMsb;      /* = 0x00 Pause opcode */
    uint8_t opcodeLsb;      /* = 0x01 */
    uint8_t pauseTimeMsb;
    uint8_t pauseTimeLsb;
    uint8_t padding[46];
} emac_pauseFr_t;

/* 32-bit word struct as bytes - MSByte first, ie. tx order */
typedef struct {
    uint8_t byte3;
    uint8_t byte2;
    uint8_t byte1;
    uint8_t byte0;
} emac_word32b_t;

/* basic TCP frame, IPv4 */
typedef struct {
    /* ethernet header */
    emac_macaddress_t dest;       /* bytes 0-5 */
    emac_macaddress_t srce;       /* bytes 6-11 */
    uint8_t     typeLenMsb;     /* MSB = 0x08   byte 12 */
    uint8_t     typeLenLsb;     /* LSB = 0x00   byte 13 */
    /* IP header */
    uint8_t     ihlVers;        /* = 0x45     byte 14 */
    uint8_t     dsCp;           /* byte 15 */
    uint8_t     frLengthMsb;    /* byte 16 */
    uint8_t     frLengthLsb;    /* byte 17 */
    uint8_t     idMsb;          /* byte 18 */
    uint8_t     idLsb;          /* byte 19 */
    uint8_t     flgsFrOffsMsb;  /* IP Flags, b7-b5, fragment offset MSB b4-b0  byte 20 */
    uint8_t     fragOffsLsb;    /* fragment offset LSB  byte 21 */
    uint8_t     ttL;            /* byte 22 */
    uint8_t     prot;           /* = 0x06, TCP   byte 23 */
    uint8_t     hdrChksumMsb;   /* byte 24 */
    uint8_t     hdrChksumLsb;   /* byte 25 */
    emac_ipv4_addr_t srcIpAddr;     /* byte 26-29 */
    emac_ipv4_addr_t dstIpAddr;     /* byte 30-33 */
    /* TCP header */
    uint8_t     srcPortMsb;     /* source port number  byte 34 */
    uint8_t     srcPortLsb;     /* source port number  byte 35 */
    uint8_t     dstPortMsb;     /* destination port number  byte 36 */
    uint8_t     dstPortLsb;     /* destination port number  byte 37 */
    emac_word32b_t   seqNum;         /* sequence number  bytes 38-41 */
    emac_word32b_t   ackNum;         /* ACK number       bytes 42-45 */
    uint8_t     datOffsFlgsMsb; /* TCP flags MSB (b1),  Data offset bits 7-4  byte 46 */
    uint8_t     tcpFlagsLsb;    /* TCP flags LSB   byte 47 */
    uint8_t     windowSizeMsb;  /* byte 48 */
    uint8_t     windowSizeLsb;  /* byte 49 */
    uint8_t     tcpChksumMsb;   /* byte 50 */
    uint8_t     tcpChksumLsb;   /* byte 51 */
    uint8_t     urgentPtrMsb;   /* byte 52 */
    uint8_t     urgentPtrLsb;   /* byte 53 */
} emac_tcpHeader_t;

/* basic UDP frame, IPv4 */
typedef struct {
    /* ethernet header */
    emac_macaddress_t dest;       /* bytes 0-5 */
    emac_macaddress_t srce;       /* bytes 6-11 */
    uint8_t     typeLenMsb;     /* MSB = 0x08 */
    uint8_t     typeLenLsb;     /* LSB = 0x00 */
    /* IP header */
    uint8_t     ihlVers;        /* = 0x45   byte 14 */
    uint8_t     dsCp;           /* byte 15 */
    uint8_t     frLengthMsb;    /* byte 16 */
    uint8_t     frLengthLsb;    /* byte 17 */
    uint8_t     idMsb;          /* byte 18 */
    uint8_t     idLsb;          /* byte 19 */
    uint8_t     flgsFrOffsMsb;  /* byte 20 */
    uint8_t     fragOffsLsb;    /* byte 21 */
    uint8_t     ttL;            /* byte 22 */
    uint8_t     prot;           /* = 0x11, UDP   byte 23 */
    uint8_t     hdrChksumMsb;   /* byte 24 */
    uint8_t     hdrChksumLsb;   /* byte 25 */
    emac_ipv4_addr_t srcIpAddr;     /* bytes 26-29 */
    emac_ipv4_addr_t dstIpAddr;     /* bytes 30-33 */
    /* UDP header */
    uint8_t     srcPortMsb;     /* source port number  byte 34 */
    uint8_t     srcPortLsb;     /* source port number  byte 35 */
    uint8_t     dstPortMsb;     /* destination port number  byte 36 */
    uint8_t     dstPortLsb;     /* destination port number  byte 37 */
    uint8_t     udpLengthMsb;   /* UDP header+data  byte 38 */
    uint8_t     udpLengthLsb;   /* UDP header+data  byte 39 */
    uint8_t     udpChksumMsb;   /* byte 40 */
    uint8_t     udpChksumLsb;   /* byte 41 */
} emac_udpHeader_t;

/* initTcpUdpHeader parameters - for UDP or TCP header */
typedef struct {
    emac_macaddress_t srcMac;
    emac_macaddress_t dstMac;
    uint16_t dataLen;
    uint16_t id;
    emac_ipv4_addr_t srcIpAddr;
    emac_ipv4_addr_t dstIpAddr;
    uint16_t srcPort;           /* TCP or UDP */
    uint16_t dstPort;           /* TCP or UDP */
    uint32_t seqNum;            /* TCP */
    uint32_t ackNum;            /* TCP */
    uint16_t flags;             /* TCP */
    uint16_t window;            /* TCP */
    uint16_t udpLength;         /* UDP */
    uint16_t udpChksum;         /* UDP */
} emac_tcpUdpParams_t;

/** Struct describing  time stamp data allocated in descriptor */
typedef struct
{
    /** TS valid - set to 1 if valid data stored */
    uint8_t tsValid;
    /** Timestamp nanoseconds[29:0] - word2/4[29:0] */
    uint32_t tsNanoSec;
    /** Timestamp seconds[1:0] from word2/4[31:30], seconds[5:2]from word3/5[5:2] */
    uint32_t tsSecs;
} emac_timestamp_data_t;

/**
 * Struct describing time launch time data allocated in descriptor.
 * It is used to specify on a per-frame basis the TSU time (launch time)
 * at which a frame is to be transmitted
*/
typedef struct
{
    /** Time launch time nanoseconds[29:0] - word2/4[29:0] */
    uint32_t nanoSecs;
    /** Time launch time seconds[1:0] word2/4[31:30] */
    uint32_t secs;
} emac_transmit_launchtime_t;

/* Tx buffer descriptor */
#define EMAC_TXBD_USED_BIT                      (1 << 31)
#define EMAC_TXBD_WRAP_BIT                      (1 << 30)
#define EMAC_TXBD_CRC_BIT                       (1 << 16)
#define EMAC_TXBD_LASTBUF_BIT                   (1 << 15)
#define EMAC_TXBD_BUFLEN_MASK                   (0x3FFFU)

/* Rx buffer descriptor */
#define EMAC_RXBD_WRAP_BIT                      (1 << 1)
#define EMAC_RXBD_USED_BIT                      (1 << 0)
#define EMAC_RXBD_EOF_BIT                       (1 << 15)
#define EMAC_RXBD_SOF_BIT                       (1 << 14)

/* Network control */
#define EMAC_LOOP_BACK                          (1 << 1)
#define EMAC_RX_ENABLE                          (1 << 2)
#define EMAC_TX_ENABLE                          (1 << 3)
#define EMAC_SMI_ENABLE                         (1 << 4)
#define EMAC_CLEAR_ALL_STATS                    (1 << 5)
#define EMAC_INC_ALL_STATS_REGS                 (1 << 6)
#define EMAC_STATS_WRITE_EN                     (1 << 7)
#define EMAC_BACK_PRESSURE                      (1 << 8)
#define EMAC_TX_START                           (1 << 9)
#define EMAC_TRANSMIT_HALT                      (1 << 10)
#define EMAC_TX_PAUSE_FRAME_REQ                 (1 << 11)
#define EMAC_TX_PAUSE_FRAME_ZERO                (1 << 12)
#define EMAC_STORE_RX_TS                        (1 << 15)
#define EMAC_PFC_ENABLE                         (1 << 16)
#define EMAC_TX_LPI_EN                          (1 << 19)
#define EMAC_ONE_STEP_SYNC_MODE                 (1 << 24)
#define EMAC_PFC_CTRL                           (1 << 25)
#define EMAC_OSS_CORRECTION_FIELD               (1 << 27)
#define EMAC_MII_ON_RGMII                       (1 << 28)

#define emac_tx_rx_enable()                     emac->network_control |= EMAC_TX_ENABLE | EMAC_RX_ENABLE
#define emac_tx_rx_disable()                    emac->network_control &= (~EMAC_TX_ENABLE & ~EMAC_RX_ENABLE)
#define emac_tx_enable()                        emac->network_control |= EMAC_TX_ENABLE
#define emac_tx_disable()                       emac->network_control &= ~EMAC_TX_ENABLE
#define emac_rx_enable()                        emac->network_control |= EMAC_RX_ENABLE
#define emac_rx_disable()                       emac->network_control &= ~EMAC_RX_ENABLE
#define emac_tx_start()                         emac->network_control |= EMAC_TX_START
#define emac_loopback_enable()                  emac->network_control |= EMAC_LOOP_BACK
#define emac_loopback_disable()                 emac->network_control &= ~EMAC_LOOP_BACK
#define emac_clear_all_stats()                  emac->network_control |= EMAC_CLEAR_ALL_STATS
#define emac_smi_enable()                       emac->network_control |= EMAC_SMI_ENABLE
#define emac_smi_disable()                      emac->network_control &= ~EMAC_SMI_ENABLE
#define emac_set_rgmii_mode()                   emac->network_control &= ~EMAC_MII_ON_RGMII
#define emac_set_mii_mode()                     emac->network_control |= EMAC_MII_ON_RGMII
#define emac_tx_halt()                          emac->network_control |= EMAC_TRANSMIT_HALT
#define emac_1588_oss_correction_enable()       emac->network_control |= EMAC_OSS_CORRECTION_FIELD
#define emac_1588_oss_correction_disable()      emac->network_control &= ~EMAC_OSS_CORRECTION_FIELD
#define emac_1588_one_step_mode_enable()        emac->network_control |= EMAC_ONE_STEP_SYNC_MODE
#define emac_1588_one_step_mode_disable()       emac->network_control &= ~EMAC_ONE_STEP_SYNC_MODE
#define emac_tx_lpi_enable()                    emac->network_control |= EMAC_TX_LPI_EN
#define emac_tx_lpi_disable()                   emac->network_control &= ~EMAC_TX_LPI_EN
#define emac_tx_pause()                         emac->network_control |= EMAC_TX_PAUSE_FRAME_REQ
#define emac_tx_zero_pause()                    emac->network_control |= EMAC_TX_PAUSE_FRAME_ZERO

/**
 * undef pfc pause
#define emac_pfc_pause_enable()                 emac->network_control |= EMAC_PFC_CTRL
#define emac_pfc_pause_disable()                emac->network_control &= ~EMAC_PFC_CTRL
#define emac_pfc_priority_pause_enable()        emac->network_control |= EMAC_PFC_ENABLE
#define emac_pfc_priority_pause_disable()       emac->network_control &= ~EMAC_PFC_ENABLE
*/
#define emac_get_pause_quantum()             (emac->pause_time & 0xFFFFU)

/* Network config */
#define EMAC_SPEED_100M                         (1 << 0)
#define EMAC_FULL_DUP                           (1 << 1)
#define EMAC_COPY_ALL_FRAME                     (1 << 4)
#define EMAC_NO_BROADCAST                       (1 << 5)
#define EMAC_MULTICAST_HASH_ENABLE              (1 << 6)
#define EMAC_UNICAST_HASH_ENABLE                (1 << 7)
#define EMAC_RECEIVE_1536_BYTE_FRAMES           (1 << 8)
#define EMAC_EXTERNAL_ADDRESS_MATCH_ENABLE      (1 << 9)
#define EMAC_GIGABIT_MODE                       (1 << 10)
#define EMAC_PCS_SELECT                         (1 << 11) /* should be 0 */
#define EMAC_RETRY_TEST                         (1 << 12)
#define EMAC_PAUSE_ENABLE                       (1 << 13)
#define EMAC_RECEIVE_BUFFER_OFFSET              (14)
#define EMAC_RECEIVE_BUFFER_OFFSET_MASK         (0x3U)
#define EMAC_LENGTH_FIELD_ERROR_FRAME_DISCARD   (1 << 16)
#define EMAC_FCS_REMOVE                         (1 << 17)
#define EMAC_MDC_CLOCK_DIVISION_OFFSET          (18)
#define EMAC_MDC_CLOCK_DIVISION_MASK            (0x7U)
#define EMAC_DATA_BUS_WIDTH                     (1 << 21)   // should be 1 to 64bit
#define EMAC_DISABLE_COPY_OF_PAUSE_FRAMES       (1 << 23)
#define EMAC_RECEIVE_CHECKSUM_OFFLOAD_ENABLE    (1 << 24)
#define EMAC_EN_HALF_DUPLEX_RX                  (1 << 25)
#define EMAC_IGNORE_RX_FCS                      (1 << 26)
#define EMAC_IPG_STRETCH_ENABLE                 (1 << 28)
#define EMAC_IGNORE_IPG_RX_ER                   (1 << 30)
#define EMAC_RECV_BAD_PREAMBLE                  (1 << 29)

#define emac_copy_all_frame()                   emac->network_config |= EMAC_COPY_ALL_FRAME
#define emac_copy_all_frame_disable()           emac->network_config &= ~EMAC_COPY_ALL_FRAME
#define emac_full_dup()                         emac->network_config |= EMAC_FULL_DUP
#define emac_half_dup()                         emac->network_config &= ~EMAC_FULL_DUP
#define emac_set_data_bus_width()               emac->network_config |= EMAC_DATA_BUS_WIDTH
#define emac_rx_bad_preamble_enable()           emac->network_config |= EMAC_RECV_BAD_PREAMBLE
#define emac_rx_bad_preamble_disable()          emac->network_config &= ~EMAC_RECV_BAD_PREAMBLE
#define emac_ignore_rx_fcs_enable()             emac->network_config |= EMAC_IGNORE_RX_FCS
#define emac_ignore_rx_fcs_disable()            emac->network_config &= ~EMAC_IGNORE_RX_FCS
#define emac_no_broadcast_enable()              emac->network_config |= EMAC_NO_BROADCAST
#define emac_no_broadcast_disable()             emac->network_config &= ~EMAC_NO_BROADCAST
#define emac_multicast_hash_enable()            emac->network_config |= EMAC_MULTICAST_HASH_ENABLE
#define emac_multicast_hash_disable()           emac->network_config &= ~EMAC_MULTICAST_HASH_ENABLE
#define emac_unicast_hash_enable()              emac->network_config |= EMAC_UNICAST_HASH_ENABLE
#define emac_unicast_hash_disable()             emac->network_config &= ~EMAC_UNICAST_HASH_ENABLE
#define emac_receive_1536_byte_enable()         emac->network_config |= EMAC_RECEIVE_1536_BYTE_FRAMES
#define emac_receive_1536_byte_disable()        emac->network_config &= ~EMAC_RECEIVE_1536_BYTE_FRAMES
#define emac_half_duplex_rx_enable()            emac->network_config |= EMAC_EN_HALF_DUPLEX_RX
#define emac_half_duplex_rx_disable()           emac->network_config &= ~EMAC_EN_HALF_DUPLEX_RX
#define emac_length_error_discard_enable()      emac->network_config |= EMAC_LENGTH_FIELD_ERROR_FRAME_DISCARD
#define emac_length_error_discard_disable()     emac->network_config &= ~EMAC_LENGTH_FIELD_ERROR_FRAME_DISCARD
#define emac_fcs_remove_enable()                emac->network_config |= EMAC_FCS_REMOVE
#define emac_fcs_remove_disable()               emac->network_config &= ~EMAC_FCS_REMOVE
#define emac_rx_checksum_offload_enable()       emac->network_config |= EMAC_RECEIVE_CHECKSUM_OFFLOAD_ENABLE
#define emac_rx_checksum_offload_disable()      emac->network_config &= ~EMAC_RECEIVE_CHECKSUM_OFFLOAD_ENABLE
#define emac_set_hash_bottom(addrbottom)        emac->hash_bottom = addrbottom
#define emac_set_hash_top(addrtop)              emac->hash_top = addrtop
#define emac_copy_pause_enable()                emac->network_config &= ~EMAC_DISABLE_COPY_OF_PAUSE_FRAMES
#define emac_copy_pause_disable()               emac->network_config |= EMAC_DISABLE_COPY_OF_PAUSE_FRAMES
#define emac_pause_enable()                     emac->network_config |= EMAC_PAUSE_ENABLE
#define emac_pause_disable()                    emac->network_config &= ~EMAC_PAUSE_ENABLE
#define emac_retry_test_enable()                emac->network_config |= EMAC_RETRY_TEST
#define emac_retry_test_disable()               emac->network_config &= ~EMAC_RETRY_TEST


/* Dma config */
#define EMAC_ENDIAN_SWAP                        (0x3 << 6)
#define EMAC_RX_BUF_SIZE_OFFSET                 (16)
#define EMAC_RX_BUF_SIZE_MASK                   (0xFFU)
#define EMAC_DMA_BURST_LENGTH_OFFSET            (0)
#define EMAC_DMA_BURST_LENGTH_MASK              (0x1FU)
#define EMAC_DMA_HDR_DATA_SPLITTING_EN          (1 << 5)
#define EMAC_TX_PBUF_TCP_EN                     (1 << 11)
#define EMAC_RX_BD_EXTENDED_MODE_EN             (1 << 28)
#define EMAC_TX_BD_EXTENDED_MODE_EN             (1 << 29)

#define emac_set_endian()                       emac->dma_config &= ~EMAC_ENDIAN_SWAP
#define emac_set_dma_burst_length(len)          emac->dma_config = ((emac->dma_config &                            \
                                                    ~(EMAC_DMA_BURST_LENGTH_MASK << EMAC_DMA_BURST_LENGTH_OFFSET)) \
                                                    | (len << EMAC_DMA_BURST_LENGTH_OFFSET))

#define emac_head_data_split_enable()           emac->dma_config |= EMAC_DMA_HDR_DATA_SPLITTING_EN
#define emac_head_data_split_disable()          emac->dma_config &= ~EMAC_DMA_HDR_DATA_SPLITTING_EN
#define emac_get_head_data_split()              ((emac->dma_config & EMAC_DMA_HDR_DATA_SPLITTING_EN) >> 5)

#define emac_tx_checksum_offload_enable()       emac->dma_config |= EMAC_TX_PBUF_TC_EN
#define emac_tx_checksum_offload_disable()      emac->dma_config &= ~EMAC_TX_PBUF_TC_EN

#define emac_rx_bd_entended_enable()            emac->dma_config |= EMAC_RX_BD_EXTENDED_MODE_EN
#define emac_rx_bd_entended_disable()           emac->dma_config &= ~EMAC_RX_BD_EXTENDED_MODE_EN

#define emac_tx_bd_entended_enable()            emac->dma_config |= EMAC_TX_BD_EXTENDED_MODE_EN
#define emac_tx_bd_entended_disable()           emac->dma_config &= ~EMAC_TX_BD_EXTENDED_MODE_EN


#if 0
#define emac_set_rx_buf_size(size)              emac->dma_config = ((emac->dma_config &                     \
                                                    ~(EMAC_RX_BUF_SIZE_MASK << EMAC_RX_BUF_SIZE_OFFSET))    \
                                                    | ((size >> 6) << EMAC_RX_BUF_SIZE_OFFSET))

#define emac_get_rx_buf_size()                  (((emac->dma_config >> EMAC_RX_BUF_SIZE_OFFSET) & EMAC_RX_BUF_SIZE_MASK) << 6)
#endif
/* Transmit status */
#define EMAC_TRANSMIT_GO                        (1 << 3)
#define EMAC_TRANSMIT_COMPLETE                  (1 << 5)

#define emac_transmit_is_complete()             (emac->transmit_status & EMAC_TRANSMIT_COMPLETE)
#define emac_clear_transmit_status()            emac->transmit_status = emac->transmit_status
#define emac_clear_transmit_complete()          emac->transmit_status |= EMAC_TRANSMIT_COMPLETE
#define emac_transmit_going()                   (emac->transmit_status & EMAC_TRANSMIT_GO)

/* Receive status */
#define EMAC_FRAME_RECEIVED                     (1 << 1)

#define emac_frame_is_received()                (emac->receive_status & EMAC_FRAME_RECEIVED)
#define emac_clear_receive_status()             emac->receive_status = emac->receive_status
#define emac_clear_frame_received()             emac->receive_status |= EMAC_FRAME_RECEIVED

/* Spec addr filter */
#define emac_disable_specaddr()         emac->spec_add1_bottom = 0U;    \
                                        emac->spec_add2_bottom = 0U;    \
                                        emac->spec_add3_bottom = 0U;    \
                                        emac->spec_add4_bottom = 0U;

#define emac_disable_specific_addr(num)         writel(0, (uintptr_t)(&emac->spec_add1_bottom) + num * 2)

/* Queue */
#define emac_disable_all_queue()            emac->transmit_q_ptr    |= 0x1;     \
                                            emac->transmit_q1_ptr   |= 0x1;     \
                                            emac->transmit_q2_ptr   |= 0x1;     \
                                            emac->receive_q_ptr     |= 0x1;     \
                                            emac->receive_q1_ptr    |= 0x1;     \
                                            emac->receive_q2_ptr    |= 0x1;

/* Interrupt */
#define emac_disable_all_interrupt()        emac->int_disable = 0xFFFFFFFFU;     \
                                            emac->int_q1_disable = 0xFFFFFFFFU;  \
                                            emac->int_q2_disable = 0xFFFFFFFFU;

#define emac_spec_type_disableall()         emac->spec_type1 &= ~(1 << 31); \
                                            emac->spec_type2 &= ~(1 << 31); \
                                            emac->spec_type3 &= ~(1 << 31); \
                                            emac->spec_type4 &= ~(1 << 31);

#define emac_set_stacked_vlan(match)        emac->stacked_vlan = match | (1 << 31)
#define emac_get_stacked_vlan()             (emac->stacked_vlan & 0xFFU)
#define emac_stacked_vlan_disable()         emac->stacked_vlan &= ~(1 << 31)

typedef enum
{
    EMAC_QUEUE_NUMBER0,
    EMAC_QUEUE_NUMBER1,
    EMAC_QUEUE_NUMBER2,
    EMAC_QUEUE_NUMBER_MAX,
} emac_queue_number_t;

typedef enum
{
    EMAC_SPEC_TYPE1,
    EMAC_SPEC_TYPE2,
    EMAC_SPEC_TYPE3,
    EMAC_SPEC_TYPE4,
} emac_spec_type_num_t;

/**********************************************************************
* Defines
**********************************************************************/
/**
 * General config.
 * @xmlonly <defstofollow>4</defstofollow> REMOVE_ME @endxmlonly
 * Max number of Rx priority queues supported by driver
*/
#define	EMAC_MAX_RX_QUEUES (3U)

/** Max number of Tx priority queues supported by driver */
#define	EMAC_MAX_TX_QUEUES (3U)

/** Allows en/disabling of events on all priority queues */
#define	EMAC_ALL_QUEUES (255U)

/** Max size of each Rx buffer descriptor list */
#define	EMAC_MAX_RBQ_LENGTH (1000U)

/** max size of each Tx buffer descriptor list */
#define	EMAC_MAX_TBQ_LENGTH (1000U)

#define	EMAC_RX_MAX_BUFFER_OFFSET 3U

/** Bit-flags to specify DMA endianism. @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly */
#define	EMAC_END_SWAP_DESC (0x01U)

#define	EMAC_END_SWAP_DATA (0x02U)

/** Bit-flags to specify DMA config register bits 24-27; see EMAC User Guide for details. @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly */
#define	EMAC_CFG_DMA_DISC_RXP (0x01U)

#define	EMAC_CFG_DMA_FRCE_RX_BRST (0x02U)

#define	EMAC_CFG_DMA_FRCE_TX_BRST (0x04U)

/**
 * Bit-flags to specify checksum offload operation.
 * @xmlonly <defstofollow>1</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_CFG_CHK_OFF_TX (0x01U)

#define	EMAC_CFG_CHK_OFF_RX (0x02U)

/**
 * Bit-flags for selecting interrupts to enable/disable/read.
 * @xmlonly <defstofollow>28</defstofollow> REMOVE_ME @endxmlonly
 * Frame has been transmitted successfully
*/
#define	EMAC_EV_TX_COMPLETE (0x00000001U)

/** Used bit set has been read in Tx descriptor list */
#define	EMAC_EV_TX_USED_READ (0x00000002U)

/** Tx underrun */
#define	EMAC_EV_TX_UNDERRUN (0x00000004U)

/** Retry limit exceeded or late collision */
#define	EMAC_EV_TX_RETRY_EX_LATE_COLL (0x00000008U)

/** Tx frame corruption */
#define	EMAC_EV_TX_FR_CORRUPT (0x00000010U)

/** Frame received successfully and stored */
#define	EMAC_EV_RX_COMPLETE (0x00000020U)

/** Used bit set has been read in Rx descriptor list */
#define	EMAC_EV_RX_USED_READ (0x00000040U)

/** Rx overrun error */
#define	EMAC_EV_RX_OVERRUN (0x00000080U)

/** DMA hresp not OK */
#define	EMAC_EV_HRESP_NOT_OK (0x00000100U)

/** PCS auto-negotiation link partner page received */
#define	EMAC_EV_PCS_LP_PAGE_RX (0x00000200U)

/** PCS auto-negotiation has completed */
#define	EMAC_EV_PCS_AN_COMPLETE (0x00000400U)

/** Link status change detected by PCS */
#define	EMAC_EV_PCS_LINK_CHANGE_DET (0x00000800U)

/** Pause frame transmitted */
#define	EMAC_EV_PAUSE_FRAME_TX (0x00001000U)

/** Pause time reaches zero or zeroq pause frame received */
#define	EMAC_EV_PAUSE_TIME_ZERO (0x00002000U)

/** Pause frame with non-zero quantum received */
#define	EMAC_EV_PAUSE_NZ_QU_RX (0x00004000U)

/** PTP delay_req frame transmitted */
#define	EMAC_EV_PTP_TX_DLY_REQ (0x00008000U)

/** PTP sync frame transmitted */
#define	EMAC_EV_PTP_TX_SYNC (0x00010000U)

/** PTP pdelay_req frame transmitted */
#define	EMAC_EV_PTP_TX_PDLY_REQ (0x00020000U)

/** PTP pdelay_resp frame transmitted */
#define	EMAC_EV_PTP_TX_PDLY_RSP (0x00040000U)

/** PTP delay_req frame received */
#define	EMAC_EV_PTP_RX_DLY_REQ (0x00080000U)

/** PTP sync frame received */
#define	EMAC_EV_PTP_RX_SYNC (0x00100000U)

/** PTP pdelay_req frame received */
#define	EMAC_EV_PTP_RX_PDLY_REQ (0x00200000U)

/** PTP pdelay_resp frame received */
#define	EMAC_EV_PTP_RX_PDLY_RSP (0x00400000U)

/** TSU seconds register increment */
#define	EMAC_EV_TSU_SEC_INC (0x00800000U)

/** TSU timer count match */
#define	EMAC_EV_TSU_TIME_MATCH (0x01000000U)

/** Management Frame Sent */
#define	EMAC_EV_MAN_FRAME (0x02000000U)

/** LPI indication status bit change received */
#define	EMAC_EV_LPI_CH_RX (0x04000000U)

/** Wake on LAN event received */
#define	EMAC_EV_WOL_RX (0x08000000U)

/** External input interrupt detected */
#define	EMAC_EV_EXT_INTR (0x10000000U)

/** RX lockup has been detected */
#define	EMAC_EV_RX_LOCKUP (0x40000000U)

/** TX lockup has been detected */
#define	EMAC_EV_TX_LOCKUP (0x80000000U)

/** Bit-flags for indicating functionality supported by the driver/EMAC @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly Large Segmentation Offload */
#define	EMAC_CAP_LSO (0x00000001U)

/** Receive Side Coalescing offload */
#define	EMAC_CAP_RSC (0x00000002U)

/** Receive Side Scaling offload */
#define	EMAC_CAP_RSS (0x00000004U)

/** Bit-flags for selecting Tx Status fields to reset. @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly */
#define	EMAC_TXS_USED_READ (0x0001U)

#define	EMAC_TXS_COLLISION (0x0002U)

#define	EMAC_TXS_RETRY_EXC (0x0004U)

#define	EMAC_TXS_FRAME_ERR (0x0010U)

#define	EMAC_TXS_TX_COMPLETE (0x0020U)

#define	EMAC_TXS_UNDERRUN (0x0040U)

#define	EMAC_TXS_LATE_COLL (0x0080U)

#define	EMAC_TXS_HRESP_ERR (0x0100U)

/** Bit-flags for selecting Tx-related q_status fields to reset. @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly */
#define	EMAC_TXSQ_TX_COMPLETE 16U

#define	EMAC_TXSQ_USED_BIT_READ 32U

#define	EMAC_TXSQ_BUFF_EX_MID 64U

#define	EMAC_TXSQ_RESP_ERR 128U

/**
 * Bit-flags for selecting Rx Status fields to reset.
 * @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_RXS_NO_BUFF (0x0001U)

#define	EMAC_RXS_FRAME_RX (0x0002U)

#define	EMAC_RXS_OVERRUN (0x0004U)

#define	EMAC_RXS_HRESP_ERR (0x0008U)

/**
 * Bit-flags for selecting Rx-related q_status fields to reset.
 * @xmlonly <defstofollow>3</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_RXSQ_FRAME_RX 1U

#define	EMAC_RXSQ_USED_BIT_READ 2U

#define	EMAC_RXSQ_RESP_ERR 4U

/** High bit error status triggered */
#define	EMAC_EV_PCS25G_BER 0x00000008U

/** Block lock for PCS frame was achieved */
#define	EMAC_EV_PCS25G_FEC_BLOCK_LOCK 0x00000100U

/** FEC uncorrectable error occurred */
#define	EMAC_EV_PCS25G_FEC_UNCORRECT 0x00010000U

/** FEC correctable error occurred */
#define	EMAC_EV_PCS25G_FEC_CORRECT 0x00100000U

/** All events for PCS25G */
#define	EMAC_EVSET_PCS25G_ALL_EVENTS 0x00110108U

/**
 * Transmit IP/TCP/UDP checksum generation offload errors
 * reported in Tx descriptor status.
 * @xmlonly <defstofollow>7</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_TXD_CHKOFF_NO_ERROR (0U)

#define	EMAC_TXD_CHKOFF_VLAN_HDR_ERR (1U)

#define	EMAC_TXD_CHKOFF_SNAP_HDR_ERR (2U)

#define	EMAC_TXD_CHKOFF_INVALID_IP (3U)

#define	EMAC_TXD_CHKOFF_INVALID_PKT (4U)

#define	EMAC_TXD_CHKOFF_PKT_FRAGMENT (5U)

#define	EMAC_TXD_CHKOFF_NON_TCP_UDP (6U)

#define	EMAC_TXD_CHKOFF_PREM_END_PKT (7U)

/**
 * Bit-flags to control queueTxBuf/qTxBuf behaviour.
 * @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly
 * Indicates last buffer in frame
*/
#define	EMAC_TXB_LAST_BUFF (0x01U)

/** EMAC will not calculate & insert frame CRC. */
#define	EMAC_TXB_NO_AUTO_CRC (0x02U)

/**
 * Prevents transmission being started automatically
 * after queueing the last buffer in the frame;
 * has no effect if EMAC_TXB_LAST_BUFF not also present.
*/
#define	EMAC_TXB_NO_AUTO_START (0x04U)

/** select TCP encapsulation for the current frame - must be set for first and second buffers in frame, ie header and first data buffers */
#define	EMAC_TXB_TCP_ENCAP (0x08U)

/** select UFO fragmentation for the current frame - only relevant for first buffer in frame, which includes the header only; Ignored if EMAC_TXB_TCP_ENCAP is set. */
#define	EMAC_TXB_UDP_ENCAP (0x10U)

/**
 * select auto sequence-number generation, based on the current value of
 * the EMAC sequence number counter for this stream
*/
#define	EMAC_TXB_TSO_AUTO_SEQ (0x20U)

/** Enable Transmit Launch Time */
#define	EMAC_TXB_ENABLE_TLT (0x40U)

/** Max length accepted by queueTxBuf */
#define	EMAC_TXD_LMASK (0x4000U - 1U)

/** TCP flags (standard, some used to control RSC) @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly */
#define	EMAC_TCP_FLG_FIN (0x0001U)

#define	EMAC_TCP_FLG_SYN (0x0002U)

#define	EMAC_TCP_FLG_RST (0x0004U)

#define	EMAC_TCP_FLG_PSH (0x0008U)

#define	EMAC_TCP_FLG_ACK (0x0010U)

#define	EMAC_TCP_FLG_URG (0x0020U)

/**
 * Bit-flags to control MDIO write/read operations.
 * @xmlonly <defstofollow>2</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_MDIO_FLG_CLAUSE_45 (0x01U)

#define	EMAC_MDIO_FLG_SET_ADDR (0x02U)

#define	EMAC_MDIO_FLG_INC_ADDR (0x04U)

/**
 * PFC Priority based pause frame support:
 * Maximum number of quantum priorities supported.
*/
#define	EMAC_QUANTA_PRIORITY_MAX 8U

/**
 * Bit-flags for selecting MMSL-related interrupts to enable/disable/read.
 * @xmlonly <defstofollow>5</defstofollow> REMOVE_ME @endxmlonly
*/
#define	EMAC_MMSL_EV_RCV_R_ERR (0x01U)

#define	EMAC_MMSL_EV_RCV_V_ERR (0x02U)

#define	EMAC_MMSL_EV_SMDS_ERR (0x04U)

#define	EMAC_MMSL_EV_SMDC_ERR (0x08U)

#define	EMAC_MMSL_EV_FR_COUNT_ERR (0x10U)

#define	EMAC_MMSL_EV_SMD_ERR (0x20U)

/** Maximum number of words allowed in a descriptor */
#define	EMAC_DESC_WORD_NUM_MAX 6U

/**
 *  @}
 */

#define	EMAC_EVSET_ALL_Q0_EVENTS (EMAC_EV_TX_COMPLETE|EMAC_EV_TX_USED_READ| EMAC_EV_TX_UNDERRUN|EMAC_EV_TX_FR_CORRUPT| EMAC_EV_TX_RETRY_EX_LATE_COLL| EMAC_EV_RX_COMPLETE|EMAC_EV_RX_USED_READ|EMAC_EV_RX_OVERRUN|EMAC_EV_HRESP_NOT_OK| EMAC_EV_PCS_LP_PAGE_RX|EMAC_EV_PCS_AN_COMPLETE|EMAC_EV_PCS_LINK_CHANGE_DET| EMAC_EV_PAUSE_FRAME_TX|EMAC_EV_PAUSE_TIME_ZERO|EMAC_EV_PAUSE_NZ_QU_RX| EMAC_EV_PTP_TX_DLY_REQ|EMAC_EV_PTP_TX_SYNC|EMAC_EV_PTP_TX_PDLY_REQ| EMAC_EV_PTP_TX_PDLY_RSP|EMAC_EV_PTP_RX_DLY_REQ|EMAC_EV_PTP_RX_SYNC| EMAC_EV_PTP_RX_PDLY_REQ|EMAC_EV_PTP_RX_PDLY_RSP| EMAC_EV_TSU_SEC_INC|EMAC_EV_TSU_TIME_MATCH| EMAC_EV_MAN_FRAME|EMAC_EV_LPI_CH_RX|EMAC_EV_WOL_RX| EMAC_EV_RX_LOCKUP|EMAC_EV_TX_LOCKUP| EMAC_EV_EXT_INTR )

#define	EMAC_EVSET_ALL_QN_EVENTS (EMAC_EV_TX_COMPLETE| EMAC_EV_TX_RETRY_EX_LATE_COLL| EMAC_EV_TX_FR_CORRUPT|EMAC_EV_RX_COMPLETE| EMAC_EV_RX_USED_READ|EMAC_EV_HRESP_NOT_OK)

#define	EMAC_EVSET_TX_RX_EVENTS (EMAC_EV_TX_COMPLETE|EMAC_EV_TX_USED_READ|EMAC_EV_TX_UNDERRUN| EMAC_EV_TX_RETRY_EX_LATE_COLL| EMAC_EV_TX_FR_CORRUPT|EMAC_EV_RX_COMPLETE| EMAC_EV_RX_USED_READ|EMAC_EV_RX_OVERRUN| EMAC_EV_HRESP_NOT_OK)


/**********************************************************************
* Defines
**********************************************************************/
/** Tx Descriptor flags/status - word 1 only */
#define	EMAC_TXD_LAST_BUF (1UL << 15U)

#define	EMAC_TXD_NO_AUTO_CRC (1UL << 16U)

#define	EMAC_TXD_UFO_ENABLE (1UL << 17U)

#define	EMAC_TXD_TSO_ENABLE (1UL << 18U)

#define	EMAC_TXD_AUTOSEQ_SEL (1UL << 19U)

#define	EMAC_TXD_CHKOFF_SHIFT 20U

#define	EMAC_TXD_CHKOFF_MASK (7UL << EMAC_TXD_CHKOFF_SHIFT)

#define	EMAC_TXD_TS_VALID (1UL << 23U)

#define	EMAC_TXD_STREAM_SHIFT 24U

#define	EMAC_TXD_STREAM_MASK (3UL << EMAC_TXD_STREAM_SHIFT)

#define	EMAC_TXD_LATE_COLL (1UL << 26U)

#define	EMAC_TXD_FR_CORR (1UL << 27U)

#define	EMAC_TXD_UNDERRUN (1UL << 28U)

#define	EMAC_TXD_RETRY_EXC (1UL << 29U)

#define	EMAC_TXD_WRAP (1UL << 30U)

#define	EMAC_TXD_USED (1UL << 31U)

/** MSS/MFS only used on word 1 of 2nd descriptor */
#define	EMAC_TXD_MSSMFS_SHIFT 16U

#define	EMAC_TXD_MSSMFS_MASK (0x3FFFUL << EMAC_TXD_MSSMFS_SHIFT)

#define	EMAC_TXD_LEN_MASK ((1UL << 14U) - 1U)

/** Rx Descriptor flags - word 0 */
#define	EMAC_RXD_USED (1UL << 0U)

#define	EMAC_RXD_WRAP (1UL << 1U)

#define	EMAC_RXD_TS_VALID (1UL << 2U)

#define	EMAC_RXD_ADDR_MASK (0xFFFFFFFCU)

#define	EMAC_RXD_ADDR_SHIFT 2U

/** Rx Descriptor flags/status - word 1 only */
#define	EMAC_RXD_LEN_MASK ((1UL << 13U) - 1U)

/** *** need to include bit 13 if jumbo frames enabled *** */
#define	EMAC_RXD_LEN13_FCS_STAT (1UL << 13U)

#define	EMAC_RXD_SOF (1UL << 14U)

#define	EMAC_RXD_EOF (1UL << 15U)

#define	EMAC_RXD_CFI (1UL << 16U)

#define	EMAC_RXD_VLAN_PRI_SHIFT 17U

#define	EMAC_RXD_VLAN_PRI_MASK (7UL << EMAC_RXD_VLAN_PRI_SHIFT)

/** if header-data splitting, these definitions are valid when not EOF: header buffer */
#define	EMAC_RXD_HDR (1UL << 16U)

/** end of header */
#define	EMAC_RXD_EOH (1UL << 17U)

/**
 * CRC error when reporting bad FCS
 * in bit 16 of word 1 of the receive buffer descriptor is enabled
 *
*/
#define	EMAC_RXD_CRC (1UL << 16U)

#define	EMAC_RXD_PRI_TAG (1UL << 20U)

#define	EMAC_RXD_VLAN_TAG (1UL << 21U)

/** either Type ID match register or (if Rx chksum offload enabled) checksum status */
#define	EMAC_RXD_TYP_IDR_CHK_STA_SHIFT 22U

#define	EMAC_RXD_TYP_IDR_CHK_STA_MASK (3UL << EMAC_RXD_TYP_IDR_CHK_STA_SHIFT)

/** either Type ID matched or (if Rx chksum offload enabled) SNAP encoded and no CFI */
#define	EMAC_RXD_TYP_MAT_SNP_NCFI (1UL << 24U)

#define	EMAC_RXD_SPEC_REG_SHIFT 25U

#define	EMAC_RXD_SPEC_REG_MASK (3UL << EMAC_RXD_SPEC_REG_SHIFT)

#define	EMAC_RXD_SPEC_ADD_MAT (1UL << 27U)

#define	EMAC_RXD_EXT_ADD_MAT (1UL << 28U)

#define	EMAC_RXD_UNI_HASH_MAT (1UL << 29U)

#define	EMAC_RXD_MULTI_HASH_MAT (1UL << 30U)

#define	EMAC_RXD_BROADCAST_DET (1UL << 31U)

/** For Tx/Rx time stamp extraction from descriptor words */
#define	EMAC_TS_NANO_SEC_MASK 0x3FFFFFFFU

#define	EMAC_TS_SEC0_SHIFT 30U

#define	EMAC_TS_SEC1_MASK 0x0FU

#define	EMAC_TS_SEC1_POS_SHIFT 2U

#define	EMAC_TS_SEC_WIDTH 6U

#define	EMAC_TS_SEC_TOP (1UL << EMAC_TS_SEC_WIDTH)

#define	EMAC_TS_SEC_MASK (EMAC_TS_SEC_TOP - 1U)

/** For Tx time launch time configuration in descriptor words */
#define	EMAC_TLT_NANO_SEC_MASK 0x3FFFFFFFU

#define	EMAC_TLT_SECS_SHIFT 30U

#define	EMAC_TLT_UTLT (1UL << 31U)

/** Offset of registers for Express MAC relative to Preemptive MAC. */
#define	EMAC_EXPRESS_MAC_REGS_OFFSET 0x1000U

/** Offset of registers for ASF relative to MAC registers */
#define	EMAC_ASF_REGS_OFFSET 0xE00U

#define	EMAC_RXD_EMPTY 0xFFAA0000U

#define	EMAC_PHY_ADDR_OP 0U

#define	EMAC_PHY_WRITE_OP 1U

#define	EMAC_PHY_CL22_READ_OP 2U

#define	EMAC_PHY_CL45_READ_INC_OP 2U

#define	EMAC_PHY_CL45_READ_OP 3U

/** Size required for two buffer descriptor word (in bytes). */
#define	EMAC_TWO_BD_WORD_SIZE 8U

/** Shift variable for number of bytes in a word */
#define	EMAC_BYTES_PER_WORD_SHIFT 2U

#define	EMAC_MIN_TXBD 1U

#define	EMAC_MIN_RXBD 1U

/** maximum index of screener type 2 register */
#define	EMAC_COMPARE_MAX_INDEX 31U

/** number of available speeds for high-speed mode */
#define	EMAC_HS_AVAILABLE_SPEEDS_NUM 6U

/** number of attemps of polling PCS25G synchronization */
#define	EMAC_PCS25G_MAX_POLLING_ATTEMPS 10U

/** time beetwen next sync polling attemp for PCS25G in nanoseconds */
#define	EMAC_PCS25G_POLLING_WAIT_NS 10U

/** Number of queues supported by EnST (always highest) */
#define	EMAC_TX_ENST_QUEUES 8U

#define SMI_MDIO_BUS_TIMEOUT    10000U

typedef enum
{
    EMAC_DMA_DBUR_LEN_1 = 1U,
    EMAC_DMA_DBUR_LEN_4 = 4U,
    EMAC_DMA_DBUR_LEN_8 = 8U,
    EMAC_DMA_DBUR_LEN_16 = 16U,
    EMAC_DMA_DBUR_LEN_256 = 0U
} emac_dmadatblen_t;

typedef enum
{
    EMAC_MDC_DIV_BY_8 = 0U,
    EMAC_MDC_DIV_BY_16 = 1U,
    EMAC_MDC_DIV_BY_32 = 2U,
    EMAC_MDC_DIV_BY_48 = 3U,
    EMAC_MDC_DIV_BY_64 = 4U,
    EMAC_MDC_DIV_BY_96 = 5U,
    EMAC_MDC_DIV_BY_128 = 6U,
    EMAC_MDC_DIV_BY_224 = 7U
} emac_mdcclkdiv_t;

typedef enum
{
    EMAC_MDIO_DEV_PMD_PMA = 1U,
    EMAC_MDIO_DEV_WIS = 2U,
    EMAC_MDIO_DEV_PCS = 3U,
    EMAC_MDIO_DEV_PHY_XS = 4U,
    EMAC_MDIO_DEV_DTE_XS = 5U
} emac_mdiodevtype_t;

typedef enum
{
    EMAC_IFSP_MII   = 0U,
    EMAC_IFSP_RMII  = 1U,
    EMAC_IFSP_RGMII = 2U
} emac_interface_t;

typedef enum
{
    EMAC_TX_TS_DISABLED = 0U,
    EMAC_TX_TS_PTP_EVENT_ONLY = 1U,
    EMAC_TX_TS_PTP_ALL = 2U,
    EMAC_TX_TS_ALL = 3U
} emac_txtsmode_t;

typedef enum
{
    EMAC_RX_TS_DISABLED = 0U,
    EMAC_RX_TS_PTP_EVENT_ONLY = 1U,
    EMAC_RX_TS_PTP_ALL = 2U,
    EMAC_RX_TS_ALL = 3U
} emac_rxtsmode_t;

/** Enum defining speed selection or indication */
typedef enum
{
    EMAC_IFSPEED_10M = 0U,
    EMAC_IFSPEED_100M = 1U,
    EMAC_IFSPEED_1000M = 2U,
} emac_ifspeed_t;

typedef enum
{
    EMAC_MDC_DIV_8,
    EMAC_MDC_DIV_16,
    EMAC_MDC_DIV_32,
    EMAC_MDC_DIV_48,
    EMAC_MDC_DIV_64,
    EMAC_MDC_DIV_96,
    EMAC_MDC_DIV_128,
    EMAC_MDC_DIV_224,
} emac_mdc_div_t;

/**
 * Configuration parameters passed to probe & init.
 * Note that only the first eight fields are required for the probe call;
 * all are required by init
*/
typedef struct
{
    /**
     * number of descriptors in each Tx
     * descriptor queue
    */
    uint16_t txQLen[EMAC_MAX_TX_QUEUES];
    /**
     * number of descriptors in each Rx
     * descriptor queue
    */
    uint16_t rxQLen[EMAC_MAX_RX_QUEUES];

    /**
     * sets endian swap for data buffers and descriptors
     * accesses: "OR'd combination of EMAC_END_SWAP_DESC
     * and EMAC_END_SWAP_DATA" $RANGE $FROM 0 $OR_MASK EMAC_END_SWAP_* $
    */
    uint8_t dmaEndianism;
    /**
     * events to enable on start, OR together bit-flags
     * defined in Interrupt control
    */
    uint32_t intrEnable;

    /** fixed burst length for DMA data transfers */
    emac_dmadatblen_t dmaDataBurstLen;
    /**
     * DMA config register bits 24, 25 & 26.
     * OR the following bit-flags to set corresponding bits -
     * EMAC_CFG_DMA_DISC_RXP,
     * EMAC_CFG_DMA_FRCE_RX_BRST,
     * EMAC_CFG_DMA_FRCE_TX_BRST $RANGE $FROM 0 $OR_MASK EMAC_CFG_DMA_* $
    */
    uint8_t dmaCfgFlags;
    /**
     * loopback enable
    */
    uint8_t loopBack;
    /**
     * copy all frames
     */
    uint8_t copyAllFrame;
    /**
     * when set frames with FCS/CRC
     * errors will not be rejected. FCS error statistics will still
     * be collected for frames with bad FCS and FCS status
     * will be recorded in frame's DMA descriptor. For normal
     * operation this bit must be set to zero.
     */
    uint8_t ignoreRxFcs;
    /**
     * set to 1 to initialise with MDIO enabled, or 0 to
     * disable
    */
    uint8_t enableMdio;
    /** divisor to generate MDC from pclk */
    emac_mdcclkdiv_t mdcPclkDiv;
    /** MII/GMII/RGMII/SGMII/BASE_X selection */
    emac_interface_t ifTypeSel;
    /** Speed selection */
    emac_ifspeed_t ifSpeedSel;
    /** full/half duplex operation */
    uint8_t fullDuplex;
    /** enable Rx in half-duplex while Tx */
    uint8_t enRxHalfDupTx;
    /** start-of-frame offset for writing Rx data (0 to 3 bytes) $RANGE $FROM 0 $TO EMAC_RX_MAX_BUFFER_OFFSET $ */
    uint8_t rxBufOffset;
    /** enable discard of frames with length field error */
    uint8_t rxLenErrDisc;
    /** disable copying Rx pause frames to memory */
    uint8_t disCopyPause;
    /** enable uni-direction Tx operation */
    uint8_t uniDirEnable;
    /**
     * enable checksum offload operation - OR bit-flags
     * to enable in Tx and/or Rx:
     * EMAC_CFG_CHK_OFF_TX,  EMAC_CFG_CHK_OFF_RX $RANGE $FROM 0 $OR_MASK EMAC_CFG_CHK_OFF_* $
    */
    uint8_t chkSumOffEn;
    /** enable Rx of frames up to 1536 bytes $RANGE $FROM 0 $TO 1 $ */
    uint8_t rx1536ByteEn;
    /** enable Rx frames with non-standard preamble $RANGE $FROM 0 $TO 1 $ */
    uint8_t enRxBadPreamble;
    /** ignore IPG rx_er (NetCfg b30) $RANGE $FROM 0 $TO 1 $ */
    uint8_t ignoreIpgRxEr;
    /**
     * replace CRC upper 16 bits with offset to UDP/TCP
     * header for Rx frames $RANGE $FROM 0 $TO 1 $
    */
    uint8_t storeUdpTcpOffset;
    /** enable pfc multiple quantum (8 different priorities) $RANGE $FROM 0 $TO 1 $ */
    uint8_t pfcMultiQuantum;
    /* QN interrupt priority */
    uint32_t qIrqPriority[3];
} emac_config_t;

typedef enum
{
    EMAC_SPEC_ADDRESS_1,
    EMAC_SPEC_ADDRESS_2,
    EMAC_SPEC_ADDRESS_3,
    EMAC_SPEC_ADDRESS_4,
    EMAC_SPEC_ADDRESS_MAX,
} emac_spec_addr_num_t;

typedef enum
{
    EMAC_SPEC_FILTER_DEST,
    EMAC_SPEC_FILTER_SRC,
} emac_spec_addr_filer_t;


/** struct for writing/reading 1588 timer */
typedef struct
{
    /** Upper 16 bits of seconds value */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value */
    uint32_t secsLower;
    /** Nanoseconds value (30 bits) $RANGE $FROM 0 $TO 1073741823 $TEST_SUBSET 4 $ */
    uint32_t nanosecs;
} emac_1588timerval_t;

/** struct for writing/reading TSU timer */
typedef struct
{
    /** Upper 16 bits of seconds value $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 4 $ */
    uint16_t secsUpper;
    /** Lower 32 bits of seconds value $RANGE $FROM 0 $TO 4294967295 $TEST_SUBSET 4 $ */
    uint32_t secsLower;
    /** Upper 22 bits of nanoseconds value $RANGE $FROM 0 $TO 4194303 $TEST_SUBSET 4 $ */
    uint32_t nanosecs;
} emac_tsutimerval_t;

/** struct for writing/reading the 1588 timer increment registers */
typedef struct
{
    /** Whole nanoseconds to increment timer each clock cycle $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t nanoSecsInc;
    /** Sub-nanoseconds to increment the timer (16 bits) $RANGE $FROM 0 $TO 65535 $TEST_SUBSET 32 $ */
    uint16_t subNsInc;
    /** Lower 8 bits of sub-nanoseconds to increment the timer $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t lsbSubNsInc;
    /** Number of increments before changing to alternative increment. If = 0 then never use alternative increment. $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t altIncCount;
    /** Alternative nanoseconds increment to apply $RANGE $FROM 0 $TO 255 $TEST_SUBSET 4 $ */
    uint8_t altNanoSInc;
} emac_timerincrement_t;

/* Q0 general interrupt */
#define EMAC_GENERAL_SMI_SEND                                               (1 << 0)
#define EMAC_GENERAL_RECEIVE_COMPLETE                                       (1 << 1)
#define EMAC_GENERAL_RX_USED_BIT_READ                                       (1 << 2)
#define EMAC_GENERAL_TX_USED_BIT_READ                                       (1 << 3)
#define EMAC_GENERAL_TRANSMIT_UNDER_RUN                                     (1 << 4)
#define EMAC_GENERAL_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION                 (1 << 5)
#define EMAC_GENERAL_AMBA_ERROR                                             (1 << 6)
#define EMAC_GENERAL_TRANSMIT_COMPLETE                                      (1 << 7)
#define EMAC_GENERAL_RECEIVE_OVERRUN                                        (1 << 10)
#define EMAC_GENERAL_RESP_NOT_OK                                            (1 << 11)
#define EMAC_GENERAL_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED       (1 << 12)
#define EMAC_GENERAL_PAUSE_TIME_ELAPSED_ZERO_PAUSE_QUANTUM_RECEIVED                                  (1 << 13)
#define EMAC_GENERAL_PAUSE_FRAME_TRANSMITTED                                (1 << 14)
#define EMAC_GENERAL_EXTERNAL_INTERRUPT                                     (1 << 15)
#define EMAC_GENERAL_PTP_DELAY_REQ_FRAME_RECEIVED                           (1 << 18)
#define EMAC_GENERAL_PTP_SYNC_FRAME_RECEIVED                                (1 << 19)
#define EMAC_GENERAL_PTP_DELAY_REQ_FRAME_TRANSMITTED                        (1 << 20)
#define EMAC_GENERAL_PTP_SYNC_FRAME_TRANSMITTED                             (1 << 21)
#define EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_RECEIVED                          (1 << 22)
#define EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_RECEIVED                         (1 << 23)
#define EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_TRANSMITTED                       (1 << 24)
#define EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_TRANSMITTED                      (1 << 25)
#define EMAC_GENERAL_TSU_SECONDS_REGISTER_INCREMENT                         (1 << 26)
#define EMAC_GENERAL_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE               (1 << 27)
#define EMAC_GENERAL_WOL_INTERRUPT                                          (1 << 28)
#define EMAC_GENERAL_TSU_TIMER_COMPARISON_INTERRUPT                         (1 << 29)
#define EMAC_GENERAL_RX_LOCKUP_DETECTED                                     (1 << 30)
#define EMAC_GENERAL_TX_LOCKUP_DETECTED                                     (1 << 31)


/**
 * "struct containing function pointers for event notification callbacks issued
 * by isr().
 * <para>Each call passes the driver's privateData (pD) pointer for instance
 * identification if necessary, and may also pass data related to the event.</para>"
*/
typedef struct
{
    plic_irq_callback_t smi_complete;
    void *smi_complete_ctx;
    plic_irq_callback_t rx_complete;
    void *rx_complete_ctx;
    plic_irq_callback_t rx_used_bit_read;
    void *rx_used_bit_read_ctx;
    plic_irq_callback_t tx_used_bit_read;
    void *tx_used_bit_read_ctx;
    plic_irq_callback_t transmit_under_run;
    void *transmit_under_run_ctx;
    plic_irq_callback_t limit_exceeded_late_collison;
    void *limit_exceeded_late_collison_ctx;
    plic_irq_callback_t amba_error;
    void *amba_error_ctx;
    plic_irq_callback_t tx_complete;
    void *tx_complete_ctx;
    plic_irq_callback_t rx_overrun;
    void *rx_overrun_ctx;
    plic_irq_callback_t resp_not_ok;
    void *resp_not_ok_ctx;
    plic_irq_callback_t pause_nonzero_received;
    void *pause_nonzero_received_ctx;
    plic_irq_callback_t pause_time_elapse;
    void *pause_time_elapse_ctx;
    plic_irq_callback_t pause_tx_transmitted;
    void *pause_tx_transmitted_ctx;
    plic_irq_callback_t external_interrupt;
    void *external_interrupt_ctx;
    plic_irq_callback_t ptp_dreq_received;
    void *ptp_dreq_received_ctx;
    plic_irq_callback_t ptp_sync_received;
    void *ptp_sync_received_ctx;
    plic_irq_callback_t ptp_dreq_tranmitted;
    void *ptp_dreq_tranmitted_ctx;
    plic_irq_callback_t ptp_sync_transmitted;
    void *ptp_sync_transmitted_ctx;
    plic_irq_callback_t ptp_pdreq_received;
    void *ptp_pdreq_received_ctx;
    plic_irq_callback_t ptp_pdresq_received;
    void *ptp_pdresq_received_ctx;
    plic_irq_callback_t ptp_pdreq_transmitted;
    void *ptp_pdreq_transmitted_ctx;
    plic_irq_callback_t ptp_pdresq_transmitted;
    void *ptp_pdresq_transmitted_ctx;
    plic_irq_callback_t tsu_second_increment;
    void *tsu_second_increment_ctx;
    plic_irq_callback_t lpi_status_changed;
    void *lpi_status_changed_ctx;
    plic_irq_callback_t wol_interrupt;
    void *wol_interrupt_ctx;
    plic_irq_callback_t tsu_timer_comparis_on;
    void *tsu_timer_comparis_on_ctx;
    plic_irq_callback_t rx_lockup;
    void *rx_lockup_ctx;
    plic_irq_callback_t tx_lockup;
    void *tx_lockup_ctx;
} emac_general_callback_t;

#define EMAC_QN_RECEIVE_COMPLETE                                (1 << 1)
#define EMAC_QN_RX_USED_BIT_READ                                (1 << 2)
#define EMAC_QN_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION          (1 << 5)
#define EMAC_QN_AMBA_ERROR                                      (1 << 6)
#define EMAC_QN_TRANSMIT_COMPLETE                               (1 << 7)
#define EMAC_QN_RESP_NOT_OK                                     (1 << 11)

typedef struct
{
    emac_queue_number_t qnum;
    plic_irq_callback_t rx_complete;
    void *rx_complete_ctx;
    plic_irq_callback_t rx_used_bit_read;
    void *rx_used_bit_read_ctx;
    plic_irq_callback_t limit_exceeded_late_collison;
    void *limit_exceeded_late_collison_ctx;
    plic_irq_callback_t amba_error;
    void *amba_error_ctx;
    plic_irq_callback_t tx_complete;
    void *tx_complete_ctx;
    plic_irq_callback_t resp_not_ok;
    void *resp_not_ok_ctx;
} emac_qn_callback_t;

#define emac_general_interrupt_enable_all()             emac->int_enable = 0xFFFFFFFFU
#define emac_q1_interrupt_enable_all()                  emac->int_q1_enable = 0xFFFFFFFFU
#define emac_q2_interrupt_enable_all()                  emac->int_q2_enable = 0xFFFFFFFFU

#define emac_general_interrupt_disable_all()             emac->int_disable = 0xFFFFFFFFU
#define emac_q1_interrupt_disable_all()                  emac->int_q1_disable = 0xFFFFFFFFU
#define emac_q2_interrupt_disable_all()                  emac->int_q2_disable = 0xFFFFFFFFU

#define emac_general_interrupt_clear_all()              emac->int_status = emac->int_status
#define emac_q1_interrupt_clear_all()                   emac->int_q1_status = emac->int_q1_status
#define emac_q2_interrupt_clear_all()                   emac->int_q2_status = emac->int_q2_status

#define emac_get_general_interrupt_mask()               (emac->int_mask)
#define emac_get_q1_interrupt_mask()                    (emac->int_q1_mask)
#define emac_get_q2_interrupt_mask()                    (emac->int_q2_mask)

/** Struct for writing/reading the Wake On LAN register */
typedef struct
{
    /** Least significant 16 bits of target IP address to match */
    uint32_t wolReqAddr : 16;
    /** Magic packet events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint32_t magPktEn : 1;
    /** ARP request events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint32_t arpEn : 1;
    /** Specific address 1 events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint32_t specAd1En : 1;
    /** Multicast hash events cause WOL assert (equal 1 means enabled) $RANGE $FROM 0 $TO 1 $ */
    uint32_t multiHashEn : 1;
} emac_wol_config_t;

/** Type of scheduling algorithm of transmit queue */
typedef enum
{
    EMAC_TX_SCHED_TYPE_FIXED = 0U,
    EMAC_TX_SCHED_TYPE_CBS = 1U,
    EMAC_TX_SCHED_TYPE_DWRR = 2U,
    EMAC_TX_SCHED_TYPE_ETS = 3U
} emac_txschedtype_t;

typedef enum
{
    EMAC_CBS_QA,
    EMAC_CBS_QB,
} emac_cbs_num_t;


/** time configuration of Enhancement for Scheduled Traffic */
typedef struct
{
    /** time at which queue the queue will start (whole seconds part) $RANGE $FROM 0 $TO 3 $TEST_SUBSET 7 $ */
    uint8_t startTimeS;
    /** time at which queue the queue will start (nanoseconds part) $RANGE $FROM 0 $TO 0x3FFFFFFF $TEST_SUBSET 7 $ */
    uint32_t startTimeNs;
    /** time in which the gate for a queue has to be open, expressed in bytes $RANGE $FROM 0 $TO 0x1FFFF $TEST_SUBSET 7 $ */
    uint32_t onTime;
    /** time in which the gate for a queue has to be closed, expressed in bytes $RANGE $FROM 0 $TO 0x1FFFF $TEST_SUBSET 7 $ */
    uint32_t offTime;
}  emac_enst_config_t;

extern emac_txqueue_t tx_queue[EMAC_QUEUE_NUMBER_MAX];
extern emac_rxqueue_t rx_queue[EMAC_QUEUE_NUMBER_MAX];

void rmii_input_ref_init(void);
void rmii_output_ref_init(void);
void rmii_io_init(void);
void rmii_io_out_init(void);
void mii_io_init(void);
void mii_clk_init(void);

void emac_set_rx_buf_size(uint32_t size, emac_queue_number_t qnum);
uint32_t emac_get_rx_buf_size(emac_queue_number_t qnum);
void emac_set_speed(emac_ifspeed_t speed);
void emac_read_stats();
void emac_tx_bd_info(emac_bd_t *tx_list, uint32_t tx_bd_num);
void emac_rx_bd_info(emac_bd_t *tx_list, uint32_t tx_bd_num);

int emac_smi_write(uint8_t phyaddr, uint8_t reg, uint16_t regval);
int emac_smi_read(uint8_t phyaddr, uint8_t reg, uint16_t *regval);

void emac_init(emac_config_t *config);
void emac_print_txstatus(void);
int emac_tx_wait_done(uint32_t timeout);
int emac_rx_wait_done(uint32_t timeout);

void emac_print_txdesclist(emac_txqueue_t *txqueue);
void emac_print_global_txdesclist(void);
int emac_txqueue_set_send_data(emac_txqueue_t *txqueue, uint8_t *data, uint32_t length, uint32_t flags);
int emac_txqueue_free_data(emac_txqueue_t *txqueue);
void emac_txqueue_init(emac_txqueue_t *txqueue, emac_bd_t *list, uint32_t bd_number, emac_queue_number_t qnumber);
void emac_txqueue_global_init(emac_bd_t *list, uint32_t bd_number, emac_queue_number_t qnumber);
int emac_transmit_data(emac_txqueue_t *txqueue, uint8_t *tx_buf, uint32_t tx_len, uint32_t send_flag);

void emac_print_rxdesclist(emac_rxqueue_t *rxqueue);
void emac_print_global_rxdesclist(void);
int emac_rxqueue_get_frame(emac_rxqueue_t *rxqueue, uint8_t *rxbuf, uint32_t rx_len);
void emac_rxqueue_init(emac_rxqueue_t *rxqueue, emac_bd_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber);
void emac_rxqueue_global_init(emac_bd_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber);

void emac_set_specific_addr(emac_spec_addr_num_t num, emac_macaddress_t *mac, emac_spec_addr_filer_t filter, uint8_t byte_mask);
void emac_set_addr1_mask(emac_macaddress_t *mac);

int emac_tx_rx_check(emac_txqueue_t *txqueue, emac_rxqueue_t *rxqueue, uint8_t *tx_buf, uint32_t tx_len,
                            uint8_t *rx_buf, uint32_t rx_buf_len, uint32_t send_flag);

void emac_stop(void);

void emac_set_mdc_clk_div(emac_mdc_div_t div);

void emac_set_spec_type(uint16_t type, emac_spec_type_num_t type_num);
void emac_spec_type_disable(emac_spec_type_num_t type_num);

void emac_screen_type1_disable_all(void);
void emac_set_screen_type1(emac_screen_type1_t *type1_cfg, emac_screen_type1_num_t num);
void emac_get_screen_type1(emac_screen_type1_t *type1_cfg, emac_screen_type1_num_t num);

void emac_screen_type2_disable_all(void);
void emac_set_screen_type2(emac_screen_type2_t *type2_cfg, emac_screen_type2_num_t num);
void emac_get_screen_type2(emac_screen_type2_t *type2_cfg, emac_screen_type2_num_t num);
void emac_set_screen_type2_ethertype(uint16_t ether_type, emac_screen_type2_ethertype_t num);
void emac_set_screen_type2_compare(emac_screen_type2_compare_t *type2_compare, emac_screen_type2_compare_num_t num);

void emac_set_1588timer(emac_1588timerval_t *time_val);
void emac_get_1588timer(emac_1588timerval_t *time_val);
void emac_set_1588timer_inc(emac_timerincrement_t *inc);
void emac_get_1588timer_inc(emac_timerincrement_t *inc);
void emac_set_tsutimer_compare(emac_tsutimerval_t *time_val);
void emac_get_tsutimer_compare(emac_tsutimerval_t *time_val);
void emac_adjust_1588timer(int nSecAdjust);

void emac_set_event_enable(uint32_t events, emac_queue_number_t queueNum);
void emac_set_event_disable(uint32_t events, emac_queue_number_t queueNum);

void emac_txqueue_timestamp_init(emac_txtsqueue_t *txqueue, emac_bd_timestamp_t *list, uint32_t bd_number, emac_queue_number_t qnumber);
void emac_rxqueue_timestamp_init(emac_rxtsqueue_t *rxqueue, emac_bd_timestamp_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber);
void emac_print_txtsdesclist(emac_txtsqueue_t *txqueue);
void emac_print_rxtsdesclist(emac_rxtsqueue_t *rxqueue);
void emac_set_desctimestamp_mode(emac_txtsmode_t txmode, emac_rxtsmode_t rxmode);
int emac_txtsqueue_set_send_data(emac_txtsqueue_t *txqueue, uint8_t *data, uint32_t length, uint32_t flags);

void rgmii_clk_init(void);
void rgmii_io_init(void);

void emac_interrupt_init(uint32_t q0_priority, uint32_t q1_priority, uint32_t q2_priority);
int emac_qn_irq_register(emac_queue_number_t qnum, uint32_t int_type, plic_irq_callback_t cb, void *ctx);
int emac_qn_irq_unsregister(emac_queue_number_t qnum, uint32_t int_type);
int emac_general_irq_register(uint32_t int_type, plic_irq_callback_t cb, void *ctx);
int emac_general_irq_unregister(uint32_t int_type);
void emac_interrupt_set_priority(emac_queue_number_t qnum, uint32_t priority);
void emac_interrupt_disable(emac_queue_number_t qnum);

void emac_wol_config(emac_wol_config_t *config);

void emac_set_txqueue_schedule(emac_queue_number_t qnum, emac_txschedtype_t schedtype);
void emac_set_cbs_idleslope(emac_queue_number_t qnum, uint32_t idleslope);

void emac_cbs_enable(emac_cbs_num_t num, uint32_t idleslope);
void emac_cbs_disable(emac_cbs_num_t num);

void emac_set_dwrr_weight(emac_queue_number_t qnum, uint8_t weight);
void emac_set_ets_band(emac_queue_number_t qnum, uint8_t band);

void emac_enst_enable(emac_queue_number_t qnum);
void emac_enst_disable(emac_queue_number_t qnum);
void emac_set_enst_config(emac_queue_number_t qnum, emac_enst_config_t *config);

void emac_set_pause_quantum(uint16_t value, uint8_t qpriority);

int emac_smi_clause45_write(uint8_t phyaddr, uint8_t reg, uint16_t regval);
int emac_smi_clause45_read(uint8_t phyaddr, uint8_t reg, uint16_t *regval);

void emac_reset(void);
#endif