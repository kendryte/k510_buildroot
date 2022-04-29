/**********************************************************************
 * Copyright (C) 2014-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sduhc_if.h
 * Private declarations for CUSBH driver
 *
 ***********************************************************************/
#ifndef __SDUHC_IF_H__
#define __SDUHC_IF_H__
#include "cusbh_if.h"
#include "cusb_dma_if.h"
#include "sduc_regs.h"
#include "byteorder.h"
#include "cusbd_if.h"

/*Error constant*/
#define UHC_ESTALL 1
#define UHC_EUNHANDLED 2
#define UHC_EAUTOACK 3
#define UHC_ESHUTDOWN 4
#define UDC_ECONNRESET 5

#ifndef ListHead
#define ListHead CUSBH_ListHead
#endif

typedef enum {
    OTG_STATE_A_IDLE  = 0x0,
    OTG_STATE_A_WAIT_VRISE,
    OTG_STATE_A_WAIT_BCON,
    OTG_STATE_A_HOST,
    OTG_STATE_A_SUSPEND,
    OTG_STATE_A_PERIPHERAL,
    OTG_STATE_A_VBUS_ERR,
    OTG_STATE_A_WAIT_VFALL,
    OTG_STATE_B_IDLE = 0x10,
    OTG_STATE_B_PERIPHERAL,
    OTG_STATE_B_WAIT_ACON,
    OTG_STATE_B_HOST,
    OTG_STATE_B_HOST_2,
    OTG_STATE_B_SRP_INT1,
    OTG_STATE_B_SRP_INT2,
    OTG_STATE_B_DISCHRG1,
    OTG_STATE_B_DISCHRG2,
    OTG_STATE_UNKNOWN
} OtgState;

typedef enum {
    EP_FREE             /*endpoint exist in hardware and is not reserved yet*/,
    EP_ALLOCATED,       /*Endpoint is reserved for use*/
    EP_BUSY,            /*Endpoint is reserved for use and is actually in progress*/
    EP_NOT_IMPLEMENTED /*Endpoint not exists in hardware*/
} EpState;

/* peripheral side ep0 states */
typedef enum {
    UHC_EP0_STAGE_IDLE,     /* idle ready for sending setup packet */
    UHC_EP0_STAGE_SETUP,    /* setup packet sent*/
    UHC_EP0_STAGE_IN,       /* Wait for data IN completed*/
    UHC_EP0_STAGE_OUT,      /* Wait for data OUT completed */
    UHC_EP0_STAGE_STATUSIN, /* (after OUT data) */
    UHC_EP0_STAGE_STATUSOUT,/* (after IN data) */
    UHC_EP0_STAGE_ACK
} UhcEp0State;


typedef struct UhcEp {
    uint8_t name[255];
    /*Index of endpoint in table*/
    uint8_t hwEpNum;
    /*Number of hardware buffers*/
    uint8_t hwBuffers;
    /*Maximum packet size for hardware endpoint*/
    uint16_t hwMaxPacketSize;
    /*Direction o endpoint*/
    uint8_t isInEp;
    /*DMA channel for transmission*/
    void * channel;
    /*Hardware Host endpoint is configured to usbEpNum Peripheral endpoint*/
    uint8_t usbEpNum;
    /*Endpoint type*/
    uint8_t type;
    /*Currently Max Packet Size used for this endpoint */
    uint8_t usbPacketSize;
    /*currently scheduled transfer for peripheral endpoint*/
    EpState state;
    /*Currently scheduled USB Host Endpoint for this hardware endpoint*/
    CUSBH_Ep * scheduledUsbHEp;
    /*references counter*/
    uint8_t refCount;
} UhcEp;

/*Structure holding data for improving performance*/
typedef struct UhcHostEpPriv {
    /*node used for queuing this object in an appropriate queue*/
    ListHead node;
    /*Hardware Endpoint dedicated for specific transfer type*/
    UhcEp * genericHwEp;
    /*Actually used hwEndpoint. This can be different then genericHwEp*/
    UhcEp * currentHwEp;
    uint8_t epIsReady;
    uint8_t isIn;
    uint8_t type;
    uint8_t interval;
    uint8_t epNum;
    /*Function address*/
    uint8_t faddress;
    uint16_t maxPacketSize;

    /*For scheduling interrupt transfer*/
    uint32_t frame;
    /*Supporting Hub*/
    uint8_t hubAddress;
    uint8_t portAddres;
    uint8_t split;
    CUSBH_Ep * usbHEp;
	/*Only for ISOC*/
    uint8_t isocEpConfigured;
    /*If required transfer size exceed size of maximum number of bytes that can be transfered
     * by DMA then transfer has to be divided. This flag indicate that transfer has been finished.
     * In general this flag will be used in ADMA SINGLE*/
    uint8_t transferFinished;
} UhcHostEpPriv;

typedef void (*HsetPid1060wait)(uint32_t ms);

/*Constant describing which endpoints should be reserved for specific transfer type.
 * Others free endpoints can be used for any kind of transfer */
#define UHC_GENERIC_EP_CONTROLL 0x00
#define UHC_GENERIC_EP_BULK 0x01
#define UHC_GENERIC_EP_INT 0x02
#define UHC_GENERIC_EP_ISOC 0x03

#define UHC_VHUB_PORT_STAT_RESUME (1 << 31)

typedef struct {
    UCRegs * regs;
    CUSBH_OBJ * uhcHostDrv;
    /*holds configuration info passed to init function*/
    CUSBH_Config usbHostCfg;
    /*pointer to event callback functions (called in interrupt context)*/
    CUSBH_Callbacks usbHostCallback;
    //array of USB endpoints +1 for ep0
    UhcEp in[16];
    UhcEp out[16];
    uint32_t portStatus;
    /*Queue head for control endpoints*/
    ListHead ctrlHEpQueue;
    /*Queue head for Isochronous Host endpoints for direction IN*/
    ListHead isoInHEpQueue;
    /*Queue head for Isochronous Host endpoints for direction OUT*/
    ListHead isoOutHEpQueue;

    /*Queue head for Interrupt Host endpoints for direction IN*/
    ListHead intInHEpQueue;
    /*Queue head for Interrupt Host endpoints for direction OUT*/
    ListHead intOutHEpQueue;

    /*Queue head for Bulk Host endpoints for direction IN*/
    ListHead bulkInHEpQueue;
    /*Queue head for Bulk Host endpoints for direction OUT*/
    ListHead bulkOutHEpQueue;

    /*Current scheduled Host endpoint - used for Interrupt transfer */
    UhcHostEpPriv * intSchedHostEpPriv;

    /*Number of available endpoints*/
    uint8_t hwEpInCount;
    uint8_t hwEpOutCount;

    CH9_UsbSpeed speed;
    /*field hold last OTG state*/
    OtgState otgState;
    UhcEp0State ep0State;

    /**Field count VBUS ERROR events and is used to avoid
     * looping of IRQ caused by POWER fault.*/
    uint8_t vBusErrCnt;
    uint8_t isRemoteWakeup;
    uint8_t isSelfPowered;
    uint8_t deviceAddress;

    /*DMA fields*/
    CUSBDMA_OBJ * dmaDrv;
    void * dmaController;
    CUSBDMA_Config dmaCfg;
    CUSBDMA_Callbacks dmaCallback;
    /*USB Device*/
    CUSBD_OBJ * usbDevDrv;
    CUSBD_Callbacks usbDevCallback;
    void * usbDeviceController;
    uint8_t usbDeviceReadyToWork;
    /*if this flag is set then port controller is in reset state
     * This flag should be cleared in USBIR_RESET interrupt*/
    uint8_t port_resetting;
    /*for electrical test*/
    uint8_t hsetPid0106;
    HsetPid1060wait hsetPid0106wait;
} UHC_Controller;

char * sduhcDecodeOtgState(OtgState state);
uint32_t sduhcVHubControl(void *pD, CH9_UsbSetup * setup, uint8_t * buff);
void sduhcSetVbus(UHC_Controller * pD, uint8_t isOn);
void sduhcStart(void *privateData);
void sduhcResetEndpoint(UHC_Controller *pD);
CH9_UsbSpeed sduhcGetActualSpeed(UHC_Controller * pD);

#endif /*__SDUHC_IF_H__*/

