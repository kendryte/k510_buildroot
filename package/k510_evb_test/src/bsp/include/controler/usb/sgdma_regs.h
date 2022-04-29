/**********************************************************************
 * Copyright (C) 2014-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sgdma_regs.h
 * Header file describing USB DMA SG controllers
 *
 ***********************************************************************/

#ifndef SGDMA_REGS_H
#define SGDMA_REGS_H

#ifdef  __cplusplus
extern "C" {
#endif

// set PRECISE_BURST_LENGTH to one above
#define PRECISE_BURST_LENGTH    0x10000000
#define TD_SIZE_MASK 0x00001FFFF


#define TD_SIZE                     12u
#define TD_DMULT_MAX_TRB_DATA_SIZE  65536u
#define TD_DMULT_MAX_TD_DATA_SIZE   (~1u)
#define TD_SING_MAX_TRB_DATA_SIZE   65536u
#define TD_SING_MAX_TD_DATA_SIZE    65536u

#define TD_PTR_SIZE             4

#define TD_DIRECTION_OUT        0u
#define TD_DIRECTION_IN         1u

#define TD_LITTLE_ENDIAN        0u
#define TD_BIG_ENDIAN           1u

// Transfer Descriptor flags
#define TD_TYPE_NORMAL          0x00000400L
#define TD_TYPE_LINK            0x00001800L
#define TDF_CYCLE_BIT           0x00000001L
#define TDF_TOGGLE_CYCLE_BIT    0x00000002L
#define TDF_INT_ON_SHORT_PACKET 0x00000004L
#define TDF_FIFO_MODE           0x00000008L
#define TDF_CHAIN_BIT           0x00000010L // Set automaticly by TD Generator
#define TDF_INT_ON_COMPLECTION  0x00000020L
#define TDF_STREAMID_VALID      0x00000200L

/* TRB isn't generating IOC and ISP interrupts*/
#define BUILD_NORMAL_TRB_NO_IOC(_trb, _data_ptr, _data_size, _stream_id) { \
    _trb.dmaAddr = cpuToLe32(_data_ptr); \
    _trb.dmaSize = cpuToLe32((_data_size) | PRECISE_BURST_LENGTH); \
    _trb.ctrl = cpuToLe32(((uint32_t) _stream_id << 16)| (TD_TYPE_NORMAL | TDF_CYCLE_BIT)); }

/* TRB isn't generating IOC and ISP interrupts with chain to next*/
#define BUILD_NORMAL_TRB_NO_IOC_CHAIN(_trb, _data_ptr, _data_size, _stream_id) { \
    _trb.dmaAddr = cpuToLe32(_data_ptr); \
    _trb.dmaSize = cpuToLe32(_data_size | PRECISE_BURST_LENGTH); \
    _trb.ctrl = cpuToLe32(((uint32_t) _stream_id << 16)| (TD_TYPE_NORMAL | TDF_CYCLE_BIT | TDF_CHAIN_BIT)); }

/* TRB generates IOC and ISP interrupts*/
#define BUILD_NORMAL_TRB(_trb, _data_ptr, _data_size, _stream_id) { \
    _trb.dmaAddr  = cpuToLe32(_data_ptr); \
    _trb.dmaSize = cpuToLe32((_data_size) | PRECISE_BURST_LENGTH); \
    _trb.ctrl = cpuToLe32(((uint32_t) _stream_id << 16)| (TD_TYPE_NORMAL | TDF_CYCLE_BIT | TDF_INT_ON_COMPLECTION | TDF_INT_ON_SHORT_PACKET)); }

#define BUILD_LINK_TRB(_trb, _target_ptr) { \
    _trb.dmaAddr  = cpuToLe32(((uintptr_t)_target_ptr)); \
    _trb.dmaSize = 0; \
    _trb.ctrl = cpuToLe32(TD_TYPE_LINK | TDF_CHAIN_BIT | TDF_CYCLE_BIT); }

#define BUILD_EMPTY_TRB(_trb) {\
    _trb.dmaAddr  = 0;\
    _trb.dmaSize = 0;\
    _trb.ctrl = 0; }

/*SFR maps*/
typedef struct {
    uint32_t conf;      /*address 0x400*/
    uint32_t sts;       /*address 0x404*/
    uint32_t reserved5[5];
    uint32_t ep_sel;    /*address 0x41C*/
    uint32_t traddr;    /*address 0x420*/
    uint32_t ep_cfg;    /*address 0x424*/
    uint32_t ep_cmd;    /*address 0x428*/
    uint32_t ep_sts;    /*address 0x42c*/
    uint32_t ep_sts_sid;/*address 0x430*/
    uint32_t ep_sts_en; /*address 0x434*/
    uint32_t drbl;      /*address 0x438*/
    uint32_t ep_ien;    /*address 0x43C*/
    uint32_t ep_ists;   /*address 0x440*/
} DmaRegs;

enum evx_dma_state {
    EVX_DMA_FREE, EVX_DMA_USED
};

//-----------------------------------------------------------------------------
// DMA_CONF - Global Configuration Register
//-----------------------------------------------------------------------------

// Flags
#define DMARF_RESET     0x00000001ul
#define DMARF_LENDIAN   0x00000020ul
#define DMARF_BENDIAN   0x00000040ul
#define DMARF_SWRST     0x00000080ul
#define DMARF_DSING     0x00000100ul
#define DMARF_DMULT     0x00000200ul

//-----------------------------------------------------------------------------
// DMA_STS - Global Status Register
//-----------------------------------------------------------------------------

// Flags
#define DMARF_DTRANS    0x00000008ul
#define DMARF_ENDIAN    0x00000080ul
#define DMARF_ENDIAN2   0x80000000ul

//-----------------------------------------------------------------------------
// DMA_EP_SEL - Endpoint Select Register
//-----------------------------------------------------------------------------
// Masks
#define DMARM_EP_NUM    0x0000000Ful
#define DMARM_EP_DIR    0x00000080ul
#define DMARM_EP_ADDR   (DMARM_EP_NUM | DMARM_EP_DIR)

// Defines
#define DMARV_EP_TX     1ul  /*IN endpoint for device and out endpoint for Host*/
#define DMARV_EP_RX     0ul

#define DMARD_EP_TX     0x80ul /*IN endpoint for device and out endpoint for Host*/
#define DMARD_EP_RX     0x00ul

//-----------------------------------------------------------------------------
// USB_EP_TRADDR - Endpoint transfer ring address Register
//-----------------------------------------------------------------------------
// Masks
#define DMARM_EP_TRADDR 0xFFFFFFFFul

//-----------------------------------------------------------------------------
// DMA_EP_CFG - Endpoint Configuration Register
//-----------------------------------------------------------------------------

// Flags
#define DMARF_EP_ENABLE     0x00000001ul
#define DMARF_EP_ENDIAN     0x00000080ul
#define DMARF_EP_DSING      0x00001000ul
#define DMARF_EP_DMULT      0x00002000ul

// Values
#define DMARV_EP_DISABLED   0ul
#define DMARV_EP_ENABLED    1ul
#define DMARV_EP_DSING      0x1000ul
#define DMARV_EP_DMULT      0x2000ul

#define DMARV_EP_LITTLE_ENDIAN 0ul
#define DMARV_EP_BIG_ENDIAN    1ul

// Masks
#define DMARM_EP_ENABLE     0x00000001ul
#define DMARM_EP_ENDIAN     0x00000080ul
#define DMARM_EP_DSING      0x00001000ul
#define DMARM_EP_DMULT      0x00002000ul

//-----------------------------------------------------------------------------
// DMA_EP_CMD - Endpoint Command Register
//-----------------------------------------------------------------------------

// Flags
#define DMARF_EP_EPRST      0x00000001ul
#define DMARF_EP_DRDY       0x00000040ul
#define DMARF_EP_DFLUSH     0x00000080ul

// Masks
//-----------------------------------------------------------------------------
// DMA_EP_STS - Endpoint Status Register
//-----------------------------------------------------------------------------

// Masks
#define DMARF_EP_IOC        0x00000004ul
#define DMARF_EP_ISP        0x00000008ul
#define DMARF_EP_DESCMIS    0x00000010ul
#define DMARF_EP_TRBERR     0x00000080ul
#define DMARF_EP_DBUSY      0x00000200ul
#define DMARF_EP_CCS        0x00000800ul
#define DMARF_EP_OUTSMM     0x00004000ul
#define DMARF_EP_ISOERR     0x00008000ul
#define DMARF_EP_DTRANS     0x80000000ul

//-----------------------------------------------------------------------------
// DMA_EP_STS_EN - Endpoint Status Register Enable
//-----------------------------------------------------------------------------

// Flags
#define DMARF_EP_DESCMISEN  0x00000010ul
#define DMARF_EP_TRBERREN   0x00000080ul
#define DMARF_EP_OUTSMMEN   0x00004000ul
#define DMARF_EP_ISOERREN   0x00008000ul

//-----------------------------------------------------------------------------
// DMA_DRBL - Doorbell Register
//-----------------------------------------------------------------------------

// Defines
#define DMARD_DRBL(EP_NUM_, EP_DIR_) \
    (1ul << (EP_NUM_) << ((EP_DIR_) ? 16 : 0))

//-----------------------------------------------------------------------------
// DMA_EP_IEN - Endpoints Interrupt Enable Register
//-----------------------------------------------------------------------------
// Defines
#define DMARD_EP_INTERRUPT_EN(EP_NUM_, EP_DIR_) \
    (1ul << (EP_NUM_) << ((EP_DIR_) ? 16 : 0))

#ifdef  __cplusplus
}
#endif

#endif  /* SGDMA_REGS_H */

