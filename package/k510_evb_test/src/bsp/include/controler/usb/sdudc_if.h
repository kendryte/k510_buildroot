/**********************************************************************
 * Copyright (C) 2014-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sdudc_if.h
 * Private declarations for USB Driver
 *
 ***********************************************************************/
#ifndef __UDC_INT_H__
#define __UDC_INT_H__
#include "cusbd_if.h"
#include "cusb_dma_if.h"
#include "byteorder.h"

/*Error constant*/
#define UDC_ESTALL 1
#define UDC_EUNHANDLED 2
#define UDC_EAUTOACK 3
#define UDC_ESHUTDOWN 4
#define UDC_ECONNRESET 5
#define UDC_EAGAIN 6
#define UDC_PRIV_BUFFER_SIZE 64

#ifndef ListHead
#define ListHead CUSBD_ListHead
#endif

typedef enum  {
    UDC_EP_FREE, /*endpoint exist in hardware and is not reserved yet*/
    UDC_EP_ALLOCATED, /*Endpoint is reserved for using*/
    UDC_EP_BUSY /*Endpoint is reserved for using and is actually in progress*/,
    UDC_EP_NOT_IMPLEMENTED  /*Endpoint not exist in hardware*/
} UdcEpState;

/* peripheral side ep0 states */
typedef enum  {
    UDC_EP0_STAGE_SETUP, /* idle, waiting for setup */
    UDC_EP0_STAGE_IN, /* IN data */
    UDC_EP0_STAGE_OUT, /* OUT data */
    UDC_EP0_STAGE_STATUSIN, /* (after OUT data) */
    UDC_EP0_STAGE_STATUSOUT, /* (after IN data) */
    UDC_EP0_STAGE_ACK  /* after zlp, before statusin */
} UdcEp0State;


typedef struct  {
    struct CUSBD_Ep usbEp;
    UdcEpState state;
    uint8_t hwEpNum;         /*hardware endpoint number */
    uint8_t isInEp;
    ListHead request; /*List of request associated with this endpoint */
    uint8_t iso_flag;
    void * channel;
    /*Statistic and debuging fields*/
    uint32_t requestsInList;
    uint8_t wedged;
} UdcEp;


typedef struct {
    CUSBD_Dev usbDev;
    UCRegs * regs;
    CUSBD_OBJ * udcDrv;
    CUSBD_Config cfg; //copy of OTG_Config info suplied to init
    CUSBD_Callbacks eventCallback; //pointer to event callback function (called in interrupt context)
    UdcEp in[16];   //+1 for ep0
    UdcEp out[16];
    UdcEp0State ep0State;
    /*DMA fields*/
    CUSBDMA_OBJ * dmaDrv;
    uint8_t isRemoteWakeup;
    uint8_t isSelfPowered;
    uint8_t deviceAddress;
    void * dmaController;
    CUSBDMA_Config dmaCfg;
    CUSBDMA_Callbacks dmaCallback;
    /*This should be set in USB RESET interrupt. If this will be set then during reset procedure
     * firmware will not release DMA channel for EP0 endpoint. EP0 endpoint should be always available in Device mode
     * so it cannot be released during USB RESET.*/
    uint8_t releasEp0Flag;
    /*Controller is configured and ready for working in Device Mode*/
    uint8_t isReady;
    /*Virtual pointer to private buffer*/
    uint8_t *privBuffAddr;
    /*DMA address for private buffer*/
    uintptr_t privBuffDma;
    /*Debuging and statistic*/
    uint8_t endpointInList;
    /*flag used by MQP for testing purpose*/
    uint8_t mqpTestSrp;
    /** Host Request Flag used by HNP polling*/
    uint8_t hostRequestFlag;
} UDC_Device;


typedef struct {
    struct CUSBD_Req request;
    UdcEp * ep;
    UDC_Device * dev;
    /*Send Zero Length Packet*/
    uint8_t zlp;
} UdcRequest;


#endif

