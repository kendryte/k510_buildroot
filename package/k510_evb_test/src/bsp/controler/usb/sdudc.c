/**********************************************************************
 * Copyright (C) 2014-2017 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sdudc.c
 * Function for handling USB Controller working in Device Mode.
 *
 ***********************************************************************/


#include "cdn_string.h"
#include "cdn_stdio.h"
#include "cdn_stdtypes.h"
#include "cdn_errno.h"

#include "log.h"
#include "cps.h"

#include "cusbd_if.h"
#include "cusb_ch9.h"
#include "cusb_dma_if.h"

#include "sduc_regs.h"
#include "sdudc_if.h"

#include "sduc_list.h"

#define DBG_CUSBD_ISR_MSG             0x00010000
#define DBG_CUSBD_INIT_EP_MSG         0x00020000
#define DBG_CUSBD_CONTROL_MSG         0x00040000
#define DBG_CUSBD_VERBOSE_CONTROL_MSG 0x00080000
#define DBG_CUSBD_BASIC_MSG           0x00100000
#define DBG_CUSBD_VERBOSE_MSG         0x00200000
#define DBG_CUSBD_ERR_MSG             0x00400000
#define DBG_NO_SILENT                 0x00000004

static void sdudcEp0Callback(UDC_Device *pD, UdcEp * udcEp,
        struct CUSBD_Req * usbRequest, uint8_t status);
static inline uint32_t sdudcEp0Enable(UDC_Device * pD, UdcEp * udcEp);

static void sdudcEpXCallback(UDC_Device *pD, UdcEp * udcEp,
        struct CUSBD_Req * usbRequest, uint32_t status);

static void sdudcDisconnect(UDC_Device *pD);

static uint32_t sdudcEpXSetHalt(UDC_Device *pD, struct CUSBD_Ep * usbEp,
        uint8_t value);

static uint32_t sdudcEpDisable(void *pD, struct CUSBD_Ep * usbEp);

static struct CUSBD_epOps sdudcEpOps;
/******************************************************************************
 * Private Driver functions and macros - local macros
 *****************************************************************************/
#define sdudcToCpu16(x) (x)
#define sdudcToCpu32(x) (x)

/******************************************************************************
 * Private Driver functions and macros - list management
 *****************************************************************************/
/**
 * list pointer to list in CUSB_Req structure.
 */
static inline struct CUSBD_Req * sdudcListGetUsbRequestEntry(ListHead * list) {
    return (struct CUSBD_Req *) ((uintptr_t) list
            - (uintptr_t) &(((struct CUSBD_Req *) 0)->list));
}

/* go through all element in list*/
#define listBrowsingRequest(iterator, head, member)     \
    for(iterator = sdudcListGetUsbRequestEntry((head)->next); \
            &iterator->list != (head);      \
            iterator = sdudcListGetUsbRequestEntry(iterator->list.next))

static inline UdcEp * sdudcUsbEpToUdcEp(struct CUSBD_Ep * usbEp) {
    return (UdcEp *) ((uintptr_t) usbEp - ((uintptr_t) &((UdcEp*) 0)->usbEp));
}

static inline struct CUSBD_Req * sdudcListToUsbRequest(ListHead *list) {
    return (struct CUSBD_Req *) ((uintptr_t) list
            - ((uintptr_t) &((struct CUSBD_Req*) 0)->list));
}

static inline UdcRequest * sdudcUsbRequestToUdcRequest(
        struct CUSBD_Req * request) {
    return (UdcRequest *) ((uintptr_t) request
            - ((uintptr_t) &((UdcRequest*) 0)->request));
}

/******************************************************************************
 * Private Driver functions and macros - Generic functions
 *****************************************************************************/
/**
 * Function returns error code and display information about error
 */
static inline uint32_t sdudcReturnError(uint32_t errorCode) {
    switch(errorCode) {
    case EINVAL:
        DbgMsg(DBG_CUSBD_ERR_MSG, 1, "ERROR: EINVAL%s\n", " ");
        break;
    case EBUSY:
        DbgMsg(DBG_CUSBD_ERR_MSG, 1, "ERROR: EBUSY%s\n", " ");
        break;
    default:
        DbgMsg(DBG_CUSBD_ERR_MSG, 1, "ERROR: error code: %d\n", errorCode);
    }

    return errorCode;
}

/**
 * Gets actual speed in that controller works
 */
static CH9_UsbSpeed sdudcGetActualSpeed(UDC_Device * pD) {
    uint8_t speed = CPS_UncachedRead8(&pD->regs->speedctrl) & ~UCM_SPEEDCTRL_HSDISABLE ;

    switch(speed) {
    case UCM_SPEEDCTRL_HS:
        return CH9_USB_SPEED_HIGH;
    case UCM_SPEEDCTRL_FS:
        return CH9_USB_SPEED_FULL;
    case UCM_SPEEDCTRL_LS:
        return CH9_USB_SPEED_LOW;
    default:
        return CH9_USB_SPEED_UNKNOWN;
    }
}

/**
 *  Function notifies the host that it should resume from its suspended state.
 */
static void udcUsbResume(void *privateData) {
    UDC_Device * pD = (UDC_Device *) privateData;
    uint8_t usbcs;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Initializing Remote wake-up%s\n"," ");
    usbcs = CPS_UncachedRead8(&pD->regs->usbcs);
    vDbgMsg(DBG_CUSBD_BASIC_MSG, 0, "usbcs[3]wakeup enable:0x%x\n",usbcs&0x8);
    usbcs |= UCM_USBCS_SIGRSUME;
    CPS_UncachedWrite8(&pD->regs->usbcs, usbcs);
}

/**
 * Initializes USB endpoint for default values
 */
static inline void sdudcInitDeviceEp(UDC_Device * pD, UdcEp * udcEp,
        uint8_t epNum, uint8_t isInEp) {
    udcEp->hwEpNum = epNum;
    udcEp->isInEp = isInEp;
    udcEp->state = UDC_EP_FREE;

    listInit(&udcEp->usbEp.epList);
    listInit(&udcEp->request);

    udcEp->requestsInList =0;

    snprintf(udcEp->usbEp.name, sizeof(udcEp->usbEp.name), "Ep%d%s", epNum, isInEp ? "in" : "out");

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Init Device endpoint: %s\n", udcEp->usbEp.name);
    if (!epNum) {
        udcEp->usbEp.maxPacket = pD->cfg.epIN[0].maxPacketSize;
        if (udcEp->isInEp == 1) { //For ep 0 is In EP
            pD->usbDev.ep0 = &udcEp->usbEp;
        }
        udcEp->usbEp.ops = &sdudcEpOps;
        /*For device mode Ep0 have to be enabled for all time*/
        sdudcEp0Enable(pD, udcEp);
        return;
    }
    if (isInEp) {
        if (pD->cfg.epIN[epNum].startBuf != 0)
            CPS_UncachedWrite16(&pD->regs->txstaddr[epNum - 1].addr,
                    pD->cfg.epIN[epNum].startBuf);
        CPS_UncachedWrite8(&pD->regs->ep[epNum - 1].txcon, 0x0);
        udcEp->usbEp.maxPacket = pD->cfg.epIN[epNum].maxPacketSize;
    } else {
        if (pD->cfg.epOUT[epNum].startBuf != 0)
            CPS_UncachedWrite16(&pD->regs->rxstaddr[epNum - 1].addr,
                    pD->cfg.epOUT[epNum].startBuf);
        CPS_UncachedWrite8(&pD->regs->ep[epNum - 1].rxcon, 0x0);
        udcEp->usbEp.maxPacket = pD->cfg.epOUT[epNum].maxPacketSize;
    }
    udcEp->usbEp.ops = &sdudcEpOps;
    udcEp->usbEp.address = isInEp ? (0x80 | epNum) : epNum;
    udcEp->usbEp.maxburst = 0;
    udcEp->usbEp.mult = 0;
    udcEp->usbEp.maxStreams = 0;

    pD->endpointInList++;
    listAddTail(&udcEp->usbEp.epList, &pD->usbDev.epList);
    return;
}

/**
 * Aborts USB endpoints, shutdown requests and release DMA channel
 */
static void sdudcAbortEndpoint(UDC_Device *pD, UdcEp *udcEp) {
    struct CUSBD_Req * usbRequest;
    UDC_Device * ctrl = (UDC_Device*)pD;

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Abort Device endpoint: %s, Dma channel: %p \n",
            udcEp->usbEp.name, udcEp->channel);

    /*For endpoint different than 0 firmware has to release DMA Channel*/
    if (udcEp->channel && udcEp->hwEpNum != 0) {
        pD->dmaDrv->channelRelease(pD->dmaController, udcEp->channel);
        udcEp->channel = NULL;
    }

    /*For Ep0 channel can be released only when pD->releasEp0Flag is not set
     * Software can't release DMA channel for ep0 after USB reset because firmware
     * has to be ready for handling SETUP packet. However device should release
     * DMA channel when device will be stopped or destroyed*/
    if (udcEp->hwEpNum == 0 && udcEp->channel) {
        if(ctrl->cfg.isDevice ||  pD->releasEp0Flag ==1)
            pD->dmaDrv->channelAbort(pD->dmaController, udcEp->channel);
        else {
            pD->dmaDrv->channelRelease(pD->dmaController, udcEp->channel);
            udcEp->channel = NULL;
        }
    }

    /*delete all request*/
    while (udcEp->request.next != &udcEp->request) {
        usbRequest = sdudcListGetUsbRequestEntry(udcEp->request.next);
        vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1,
                "Shutdown Request %p from epName: 0x%s\n",
                usbRequest, udcEp->usbEp.name);
        if (!udcEp->usbEp.address)
            sdudcEp0Callback(pD, udcEp, usbRequest, UDC_ESHUTDOWN);
        else
            sdudcEpXCallback(pD, udcEp, usbRequest, UDC_ESHUTDOWN);
    }

    udcEp->state = UDC_EP_FREE;
}

/**
 * Stop activity of USB Device. Disable all endpoints, delete all requests assigned
 * to endpoints and release DMA channels
 */
static void sdudcStopActivity(UDC_Device *pD) {
    uint8_t i;
    vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "USB Stop Activity %s\n", " ");

    for (i = 0; i < 16; i++) {
        UdcEp * udcEp = &pD->in[i];
        if (udcEp->state != UDC_EP_NOT_IMPLEMENTED)
            sdudcAbortEndpoint(pD, udcEp);
        udcEp = &pD->out[i];
        if (udcEp->state != UDC_EP_NOT_IMPLEMENTED)
            sdudcAbortEndpoint(pD, udcEp);
    }
}

/**
 * Function initialize all available hardware USB endpoints.
 * Information about available endpoints in hardware are received
 * from driver configuration (bufferingValue=0 - endpoint not exist)
 */
static inline void sdudcInitEndpoints(UDC_Device * pD) {
    CUSBD_Config * config = &pD->cfg;
    UdcEp * udcEp = NULL;
    uint8_t num = 0;

    listInit(&pD->usbDev.epList);

    for (num = 0; num < 16; num++) {
        udcEp = &pD->in[num];
        /*for ep0 driver use only pD->in[0] instance*/
        if (!num) {
            sdudcInitDeviceEp(pD, udcEp, num, 1); /*EP0 IN*/
            udcEp = &pD->out[num];
            sdudcInitDeviceEp(pD, udcEp, num, 0); /*EP0 OUT*/
            continue;
        }

        /*If bufferingValue != 0 then hardware endpoint is implemented*/
        if (config->epIN[num].bufferingValue) {
            sdudcInitDeviceEp(pD, udcEp, num, 1);
        } else {
            udcEp->state = UDC_EP_NOT_IMPLEMENTED;
            udcEp->hwEpNum = num;
        }

        udcEp = &pD->out[num];
        if (config->epOUT[num].bufferingValue) {
            sdudcInitDeviceEp(pD, udcEp, num, 0);
        } else {
            udcEp->state = UDC_EP_NOT_IMPLEMENTED;
            udcEp->hwEpNum = num;
        }
    }
}

/**
 * Function initialize controller for working in Device mode, reset
 * all interrupts and initialize all endpoints. After calling
 * this function controller will be ready for working (pD->isReady =1).
 *
 */
static void sdudcSetup(void * privateData) {
    UDC_Device * pD = (UDC_Device *) privateData;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Prepareing Device for operation%s\n", " ");

    pD->usbDev.sgSupported = 0;
    pD->usbDev.state = CH9_USB_STATE_NONE;
    pD->usbDev.maxSpeed = CH9_USB_SPEED_HIGH;

    snprintf(pD->usbDev.name, sizeof(pD->usbDev.name), "Cadence USB SD Driver version: %d", 1);
    pD->usbDev.speed = CH9_USB_SPEED_UNKNOWN;

    pD->usbDev.sgSupported = pD->cfg.dmaSupport;
    pD->usbDev.isOtg = pD->cfg.isOtg;

    /*Set default speed to FULL_SPEED*/
    pD->usbDev.speed = CH9_USB_SPEED_FULL; //This should be set in USB_RESET_IRQ

    sdudcInitEndpoints(pD);

    /*set default Ep0 Max Packet Size*/
    CPS_UncachedWrite8(&pD->regs->ep0maxpack, 0x40);

    /*disable all interrupt*/
    CPS_UncachedWrite16(&pD->regs->rxien, 0);
    CPS_UncachedWrite16(&pD->regs->txien, 0);

    /*Clear all interrupts*/
    CPS_UncachedWrite16(&pD->regs->rxirq, 0xFFFF);
    CPS_UncachedWrite16(&pD->regs->txirq, 0xFFFF);
    CPS_UncachedWrite8(&pD->regs->usbirq, 0xEF);

    CPS_UncachedWrite8(&pD->regs->speedctrl, 0x80);

    /*Reset all USB endpoints*/
    CPS_UncachedWrite8(&pD->regs->endprst, UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST
            | UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST);
    pD->isReady =1;
}

/**
 * Gets next CUSBD_Req object from list of requests associated with udcEp object.
 */
inline static struct CUSBD_Req *sdudcGetNexReq(UdcEp * udcEp) {
    ListHead * list = &udcEp->request;

    /*Check if list is empty*/
    if (list->next == list) {
        vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "No Request available for %s\n ",
                udcEp->usbEp.name);
        return NULL ;
    }

    /*Get container of list object*/
    return sdudcListToUsbRequest(list->next);
}

/**
 * Reset Driver.
 */
static void sdudcReset(UDC_Device *pD) {
	uint32_t i = 0;
    vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "USB Disable Device Activity %s\n", " ");

    if (pD->usbDev.speed != CH9_USB_SPEED_UNKNOWN)
        sdudcDisconnect(pD);

    pD->usbDev.aHnpSupport = 0;
    pD->usbDev.bHnpEnable = 0;
    pD->usbDev.isAPeripheral = 0;
    pD->usbDev.state = CH9_USB_STATE_DEFAULT;
    pD->hostRequestFlag = 0;

    pD->deviceAddress = 0;
    pD->ep0State = UDC_EP0_STAGE_SETUP;
    sdudcStopActivity(pD);
    /*Set new speed - wait some time for finishing reseting*/
    for(i = 0; i<1000; i++) {
        pD->usbDev.speed = sdudcGetActualSpeed(pD);
    	if(pD->usbDev.speed == CH9_USB_SPEED_HIGH)
    		return;
    }
}

/**
 * Notifies User Application about Disconnect event
 */
void sdudcDisconnect(UDC_Device *pD) {

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Disconnect USB Device drvier - callback %s\n", " ");
    pD->usbDev.speed = CH9_USB_SPEED_UNKNOWN;
    pD->usbDev.state = CH9_USB_STATE_NONE;
    if (pD->eventCallback.disconnect)
        pD->eventCallback.disconnect(pD);

}
/******************************************************************************
 * Private Driver functions and macros - Ep0 handling
 *****************************************************************************/
/**
 * Gets next CUSBD_Req object for EP0
 */
inline static struct CUSBD_Req * sdudcGetNextEp0Req(UDC_Device *pD) {
    return sdudcGetNexReq(&pD->in[0]);
}

/**
 * Gets and make first step of analyzing new SETUP packet
 */
inline static uint32_t sdudcGetSetup(UDC_Device * pD, CH9_UsbSetup * setup) {
    int8_t i = 0;
    struct CUSBD_Req * request = NULL;
    UdcRequest * udcRequest;

    CPS_UncachedWrite8(&pD->regs->ep0cs, UCDM_EP0CS_CHGSET);

    /*Read Setup packet from USB registers*/
    for (i = 0; i < 8; i++) {
        ((char*) setup)[i] = CPS_UncachedRead8(&pD->regs->setupdat[i]);
    }

    i = CPS_UncachedRead8(&pD->regs->ep0cs);

    if (i & UCDM_EP0CS_CHGSET) {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "Setup Flags Chang: Not Error %s\n", " ");
        /*Setup packet has been modified during reading.
         * Probably last Setup Request was SET_ADDRESS that
         * was acknowledgment by hardware
         * In this case function return ECANCELED but it is not error;
         **/
        return UDC_EAUTOACK;
    }

    /*IF UCDM_EP0CS_CHGSET is set firmware can't delete interrupt in order to
     * not loose new SETUP interrupt
     **/
    CPS_UncachedWrite8(&pD->regs->usbirq, UCDM_USBIR_SUDAV);

    vDbgMsg(DBG_CUSBD_CONTROL_MSG, 1,
            "Setup packet: req%02x.%02x v%04x, i%04x I%d\n",
            setup->bmRequestType, setup->bRequest, le16ToCpu(setup->wValue),
            le16ToCpu(setup->wIndex), le16ToCpu(setup->wLength));

    /*Check if previous request was finished*/
    request = sdudcGetNextEp0Req(pD);

    if (request) {
        udcRequest = sdudcUsbRequestToUdcRequest(request);
        /**Finish last Setup transaction*/
        vDbgMsg(DBG_CUSBD_CONTROL_MSG, 1,
                "Previous request has not been Finished but new was received%s\n", " ");
        sdudcEp0Callback(pD, udcRequest->ep, request, 0);
    }

    /*Indicate next stage of Setup Transaction*/
    if (setup->wLength) {
        if (setup->bmRequestType & CH9_USB_DIR_DEVICE_TO_HOST)
            pD->ep0State = UDC_EP0_STAGE_IN;
        else
            pD->ep0State = UDC_EP0_STAGE_OUT;
    } else
        pD->ep0State = UDC_EP0_STAGE_ACK;

    return 0;
}

/**
 * Function delete request from list for EP0 and notify about thie event
 * user application by calling complete callback
 */
static void sdudcEp0Callback(UDC_Device *pD, UdcEp * udcEp,
        struct CUSBD_Req * usbRequest, uint8_t status) {

    if ((pD == NULL) || (usbRequest == NULL) || (udcEp == NULL))
        return;

    pD->ep0State = UDC_EP0_STAGE_SETUP;

    /**Delete request from list of requests */
    listDelete(&usbRequest->list);
    udcEp->requestsInList--;

    if (usbRequest->status == EINPROGRESS) {
        /*Status for Ep0*/
        usbRequest->status = status;
    }

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Complete Req: %p with 0x%02x status for %s, ERIL %d\n",
            usbRequest, usbRequest->status, udcEp->usbEp.name, udcEp->requestsInList);
    if(usbRequest->complete) {
        usbRequest->complete(&udcEp->usbEp, usbRequest);
    }
}

/**
 * Handles Status Stage IN for Ep0
 */
inline static void sdudcEp0StageStatusIn(UDC_Device *pD) {
    UdcEp * udcEp = &pD->out[0];
    struct CUSBD_Req * request;

    request = sdudcGetNextEp0Req(pD);

    if(request)
        request->actual = pD->dmaDrv->getActualLength(pD->dmaController,
            udcEp->channel);
    pD->ep0State = UDC_EP0_STAGE_SETUP;

    CPS_UncachedWrite8(&pD->regs->ep0cs, UCDM_EP0CS_HSNAK);
    sdudcEp0Callback(pD, udcEp, request, 0);
}

/**
 * Handles Status Stage OUT for Ep0
 */
inline static void sdudcEp0StageStatusOut(UDC_Device *pD) {
    UdcEp * udcEp = &pD->in[0];
    struct CUSBD_Req * request;

    request = sdudcGetNextEp0Req(pD);

    if(request)
        request->actual = pD->dmaDrv->getActualLength(pD->dmaController,
                udcEp->channel);

    printf("++++++++++++++\n");
    CPS_UncachedWrite8(&pD->regs->ep0cs, UCDM_EP0CS_HSNAK);

    /*transfers handled internally (for example Get Status) do not have to use CUSB_Req */
    if (request)
        sdudcEp0Callback(pD, udcEp, request, 0);
    else
        pD->ep0State = UDC_EP0_STAGE_SETUP;
    return;
}

/**
 * Prepares Ep0 for transferring data.
 */
static inline uint32_t sdudcEp0Enable(UDC_Device * pD, UdcEp * udcEp) {
    UCRegs * regs;
    uint16_t tmp = 0;
    uint8_t epNum = 0;

    if (!pD || !udcEp)
        return sdudcReturnError(EINVAL);

    regs = pD->regs;

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Enable %s\n", udcEp->usbEp.name);
    if (udcEp->state != UDC_EP_FREE) {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "Error: Endpoint is busy%s\n", " ");
        return EBUSY;
    }

    epNum = udcEp->hwEpNum;

    if (!udcEp->isInEp) {
        tmp = CPS_UncachedRead16(&regs->rxien);
        /*disable out irq for Ep*/
        tmp &= ~(1 << epNum);
        CPS_UncachedWrite16(&regs->rxien, tmp);
        CPS_UncachedWrite8(&regs->ep0fifoctrl,  UCM_FIFOCTRL_IO_TX | UCM_FIFOCTRL_FIFOAUTO);
    } else {
        tmp = CPS_UncachedRead16(&regs->txien);
        /*disable out irq for Ep*/
        tmp &= ~(1 << epNum);
        CPS_UncachedWrite16(&regs->txien, tmp);
        CPS_UncachedWrite8(&regs->ep0fifoctrl,  UCM_FIFOCTRL_FIFOAUTO );
    }

    udcEp->usbEp.desc = NULL;
    udcEp->state = UDC_EP_ALLOCATED;

    if (pD->dmaController) {
        udcEp->channel = pD->dmaDrv->channelAlloc(pD->dmaController,
                udcEp->isInEp, epNum, 0);
        if(!udcEp->channel)
            vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "Error: Dma Channel not allocated%s\n", " ");
    }

    CPS_UncachedWrite8(&regs->ep0maxpack, 0x40);

    return 0;
}

/**
 * Disable Ep0 - aborts transfer associated with it
 */
static inline uint32_t sdudcEp0Disable(UDC_Device * pD, UdcEp * udcEp) {

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Disable Endpoint %s \n", udcEp->usbEp.name);

    sdudcAbortEndpoint(pD, udcEp);
    return 0;
}

/**
 * Sends data on EP0
 */
inline static void sdudcEp0DataSend(UDC_Device *pD) {
    UdcEp * udcEp = &pD->in[0];
    struct CUSBD_Req * request;
    CUSBDMA_OBJ * dmaDrv = pD->dmaDrv;
    uint32_t requestSize;
    uint32_t chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
            udcEp->channel);

    request = sdudcGetNextEp0Req(pD);
    if (!request)
        return;

    vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Send data on %s UDC_Req %p, USB_Req %p \n", 
        udcEp->usbEp.name, 
        sdudcUsbRequestToUdcRequest(request), 
        request);

    if (dmaDrv->getChannelStatus(pD->dmaController, udcEp->channel)
            >= CUSBDMA_STATUS_BUSY) {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "ERROR: transfer is pending now%s\n", " ");
        return;
    }
    requestSize = (request->length < chMaxLen) ? request->length : chMaxLen;

    vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
            "usbRequest %p, requestSize: %d, packetSize %d\n",
            request, requestSize, udcEp->usbEp.maxPacket);

    pD->ep0State = UDC_EP0_STAGE_STATUSOUT;

    dmaDrv->channelProgram(pD->dmaController, udcEp->channel,
            udcEp->usbEp.maxPacket, request->dma, requestSize, NULL, 0);
}

/**
 * Gets data from EP0
 */
inline static void sdudcEp0DataReceive(UDC_Device *pD) {
    UdcEp * udcEp = &pD->out[0];
    struct CUSBD_Req * request;
    CUSBDMA_OBJ * dmaDrv = pD->dmaDrv;
    uint32_t requestSize;    
    uint32_t chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
            udcEp->channel);

    request = sdudcGetNextEp0Req(pD);
    if (!request)
        return;

    vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Receive data on %s UDC_Req %p, USB_Req %p \n", 
        udcEp->usbEp.name, 
        sdudcUsbRequestToUdcRequest(request), 
        request);

    requestSize = (request->length < chMaxLen) ? request->length : chMaxLen;

    vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
            "usbRequest %p, requestSize: %d, packetSize %d\n",
            request, requestSize, udcEp->usbEp.maxPacket);

    pD->ep0State = UDC_EP0_STAGE_STATUSIN;

    dmaDrv->channelProgram(pD->dmaController, udcEp->channel,
            udcEp->usbEp.maxPacket, request->dma, requestSize, NULL, 0);
}

/**
 * Clear or Set stall for Endpoint (value = 1 - set stall, value=0 -clear stall)
 */
static uint32_t sdudcEp0SetHalt(UDC_Device *pD, struct CUSBD_Ep * usbEp,
        uint8_t value) {
    UdcEp * udcEp = NULL;

    if (!usbEp || !pD) {
        return sdudcReturnError(EINVAL);
    }

    udcEp = sdudcUsbEpToUdcEp(usbEp);

    //check if list is empty
    if (udcEp->request.next != &udcEp->request) {
        return sdudcReturnError(EBUSY);
    }

    switch (pD->ep0State) {
    case UDC_EP0_STAGE_IN:
    case UDC_EP0_STAGE_OUT:
    case UDC_EP0_STAGE_ACK:
    case UDC_EP0_STAGE_STATUSIN:
    case UDC_EP0_STAGE_STATUSOUT:
        pD->ep0State = UDC_EP0_STAGE_SETUP;
        break;
    default:
        return sdudcReturnError(EINVAL);;
    }
    return 0;
}

/**
 * Function handles Set Feature Request
 */
static uint32_t sdudcServiceSetFeatureReq(UDC_Device * pD, CH9_UsbSetup * setup) {
    uint8_t otgctrl;
    switch (setup->bmRequestType & CH9_REQ_RECIPIENT_MASK) {
    case CH9_USB_REQ_RECIPIENT_DEVICE:
        switch (setup->wValue) {
        case CH9_USB_FS_DEVICE_REMOTE_WAKEUP:
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Set Feature (DR) - Remote Wake-Up)%s\n", " ");
            pD->isRemoteWakeup = 1;
            break;
        case CH9_USB_FS_B_HNP_ENABLE:
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Set Feature (DR) - B HNP Enable%s\n", " ");

            /* If the device is not HNP capable, it shall return STALL,*/
            if (!pD->usbDev.isOtg){
                return sdudcReturnError(EINVAL);
            }
            pD->usbDev.bHnpEnable = 1;

            /* Driver set BUSREQ and BUSDROP because he has to be
             ready for working in b_host mode. */
            otgctrl = CPS_UncachedRead8(&pD->regs->otgctrl);
            otgctrl &= ~UCHM_OTGCTRL_ABUSDROP;
            otgctrl |= UCHM_OTGCTRL_BHNPEN | UCHM_OTGCTRL_BUSREQ;
            CPS_UncachedWrite8(&pD->regs->otgctrl, otgctrl);
            break;
        case CH9_USB_FS_A_HNP_SUPPORT:
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Set Feature (DR) -A HNP Support%s\n", " ");
            if (!pD->usbDev.isOtg) {
                return sdudcReturnError(EINVAL);
            }
            pD->usbDev.aHnpSupport = 1;
            break;
        case CH9_USB_FS_TEST_MODE:
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Set Feature (DR) - TEST MODE)%s\n", " ");
            if (pD->usbDev.speed != CH9_USB_SPEED_HIGH)
                return sdudcReturnError(EINVAL);
            if (setup->wIndex & 0xFF) {
                return sdudcReturnError(UDC_ESTALL);
            }

            switch (setup->wIndex >> 8) {
            case 1:
                /*TEST_J*/
            case 2:
                /*TEST_K*/
            case 3:
                /*TEST_SE0_NAK*/
            case 4:
                /*TEST_PACKET*/
            case 6:
            	/*otg_srp_reqd*/
            	pD->mqpTestSrp = 1;
            	break;
            case 7:
            	/*otg_hnp_reqd*/
            	pD->hostRequestFlag = 1;
            	break;

            default:
                return sdudcReturnError(UDC_ESTALL);
            }
            break;
        }
        break;
    case CH9_USB_REQ_RECIPIENT_INTERFACE:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Set Feature (IR)%s\n", " ");
        break;
    case CH9_USB_REQ_RECIPIENT_ENDPOINT:
        {
            uint8_t epNum = setup->wIndex & 0x0F;
            uint8_t isIn = setup->wIndex & CH9_USB_DIR_DEVICE_TO_HOST;
            UdcEp * udcEp;

            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Set Feature (ER) %s\n", " ");

            if (epNum == 0|| epNum > 15 || setup->wValue
                    != CH9_USB_FS_ENDPOINT_HALT)
                return sdudcReturnError(EINVAL);

            udcEp = isIn ? &pD->in[epNum] : &pD->out[epNum];

            if (!udcEp->usbEp.desc)
                return sdudcReturnError(EINVAL);

            sdudcEpXSetHalt(pD, &udcEp->usbEp, 1);
            break;
        }
    default:
        return sdudcReturnError(EINVAL);
    }
    return 0;
}

/**
 * Function handles Clear Feature Request
 */
static uint32_t sdudcServiceClearFeatureReq(UDC_Device * pD,
        CH9_UsbSetup * setup) {

    switch (setup->bmRequestType & CH9_REQ_RECIPIENT_MASK) {
    case CH9_USB_REQ_RECIPIENT_DEVICE:
    	if(setup->wValue == CH9_USB_FS_B_HNP_ENABLE){
    		uint8_t otgctrl;
            if (!pD->usbDev.isOtg){
                return sdudcReturnError(EINVAL);
            }
            pD->usbDev.bHnpEnable = 0;
            otgctrl = CPS_UncachedRead8(&pD->regs->otgctrl);
            otgctrl &= ~UCHM_OTGCTRL_BHNPEN;
            CPS_UncachedWrite8(&pD->regs->otgctrl, otgctrl);
    		break;
    	}

        if (setup->wValue != CH9_USB_FS_DEVICE_REMOTE_WAKEUP)
            return UDC_EUNHANDLED;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                "Clear Feature (DR) - Remote Wake-Up)%s\n",
                " ");
        pD->isRemoteWakeup = 0;
        return UDC_EAUTOACK;
        break;
    case CH9_USB_REQ_RECIPIENT_INTERFACE:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                "Clear Feature (IR)%s \n", " ");
        break;
    case CH9_USB_REQ_RECIPIENT_ENDPOINT:
        {
            uint8_t epNum = setup->wIndex & 0x7f;
            uint8_t isIn = setup->wIndex & CH9_USB_DIR_DEVICE_TO_HOST;
            UdcEp * udcEp;

            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Clear Feature (ER)%s ", " ");

            if (epNum == 0 || epNum > 15
                    || setup->wValue != CH9_USB_FS_ENDPOINT_HALT)
                return UDC_EUNHANDLED;

            udcEp = isIn ? &pD->in[epNum] : &pD->out[epNum];
            if (!udcEp->usbEp.desc)
                return sdudcReturnError(EINVAL);

            if(udcEp->wedged)
                break;
            sdudcEpXSetHalt(pD, &udcEp->usbEp, 0);
            break;
        }
    default:
        return UDC_EUNHANDLED;
    }
    return 0;
}

/**
 * Handle Setup packet for which firmware do not need send any data in Data Stage
 */
static uint32_t sdudcServiceSetupNoData(UDC_Device * pD, CH9_UsbSetup * setup) {

    if ((setup->bmRequestType & CH9_USB_REQ_TYPE_MASK)
            != CH9_USB_REQ_TYPE_STANDARD)
        return UDC_EUNHANDLED;

    switch (setup->bRequest) {
    case CH9_USB_REQ_SET_ADDRESS:
        pD->deviceAddress = setup->wValue & 0x7F;
        pD->usbDev.state = CH9_USB_STATE_ADDRESS;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Set Address: %d\n",
                pD->deviceAddress);
        return UDC_EAUTOACK;
        break;
    case CH9_USB_REQ_SET_FEATURE:
        return sdudcServiceSetFeatureReq(pD, setup);
        break;
    case CH9_USB_REQ_CLEAR_FEATURE:
        return sdudcServiceClearFeatureReq(pD, setup);
        break;
    }
    return UDC_EUNHANDLED;
}

/**
 * Setup packet handled by CUSBD driver
 */
static uint32_t sdudcServiceSetupRequest(UDC_Device * pD, CH9_UsbSetup * setup) {
    uint8_t epNum = 0;
    uint16_t len = 0;

    if ((setup->bmRequestType & CH9_USB_REQ_TYPE_MASK)  == CH9_USB_REQ_TYPE_STANDARD) {
        switch (setup->bRequest) {
        case CH9_USB_REQ_GET_STATUS:
            break;
        default:
            return UDC_EUNHANDLED;
        }
    } else {
        return UDC_EUNHANDLED;
    }

    pD->privBuffAddr[1] = 0;
    pD->privBuffAddr[0] = 0;

    switch (setup->bmRequestType & CH9_REQ_RECIPIENT_MASK) {
    case CH9_USB_REQ_RECIPIENT_DEVICE:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Status Request (DR)%s\n", " ");

        // OTG spec - GetStatus Command
        if(setup->wIndex == CH9_OTG_STATUS_SELECTOR){
        	pD->privBuffAddr[0] = pD->hostRequestFlag;
        } else {
            pD->privBuffAddr[0] =
                pD->isSelfPowered ? CH9_USB_STATUS_DEV_SELF_POWERED : 0;
            pD->privBuffAddr[0] |=
                pD->isRemoteWakeup ? CH9_USB_STATUS_DEV_REMOTE_WAKEUP : 0;
        }
        break;
    case CH9_USB_REQ_RECIPIENT_INTERFACE:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Status Request (IR)%s\n", " ");
        break;
    case CH9_USB_REQ_RECIPIENT_ENDPOINT:
        {
            uint8_t isIn = setup->wIndex & CH9_USB_DIR_DEVICE_TO_HOST;
            UdcEp * udcEp;
            uint8_t epcs;
            UCRegs * regs = pD->regs;
            epNum = setup->wIndex & 0x0f;

            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Status Request (ER)%s\n", " ");
            if (!epNum)
                break;

            udcEp = (isIn) ? &pD->in[epNum] : &pD->out[epNum];

            /*check if endpoint is enabled*/
            if (!udcEp->usbEp.desc)
                return EINVAL;

            if (isIn)
                epcs = CPS_UncachedRead8(&regs->ep[epNum - 1].txcon);
            else
                epcs = CPS_UncachedRead8(&regs->ep[epNum - 1].rxcon);

            pD->privBuffAddr[0] = (epcs & UCDM_CON_STALL) ? 1 : 0;
            break;
        }
    default:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                "Status Request - delegate (class or vendor)%s\n", " ");
        return UDC_EUNHANDLED;
        break;
    }

    /* fill up the fifo; caller updates csr0 */
    len = le16ToCpu(setup->wLength);

    if (len > 2)
        len = 2;

    pD->dmaDrv->channelProgram(pD->dmaController, pD->in[0].channel,
            pD->in[0].usbEp.maxPacket, pD->privBuffDma, len, NULL, 0);

    return 0;
}

/**
 *  Function handles Setup packets
 */
inline static void sdudcEp0StageSetup(UDC_Device *pD) {
    uint32_t retval;
    CH9_UsbSetup setup;

    retval = sdudcGetSetup(pD, &setup);

    pD->usbDev.speed = sdudcGetActualSpeed(pD);

    switch (pD->ep0State) {
    case UDC_EP0_STAGE_ACK:
        retval = sdudcServiceSetupNoData(pD, &setup);
        if (retval == UDC_EUNHANDLED) {
            break;
        } else if (retval == UDC_EAUTOACK) {
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Transfer completed: Status stage by hardware %s\n", " ");
        } else if (retval == 0) { /*Request wass handled*/
            CPS_UncachedWrite8(&pD->regs->ep0cs, UCDM_EP0CS_HSNAK);
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Setup transfer completed%s\n", " ");
        }
        /*Setup transfer has been completed*/
        pD->ep0State = UDC_EP0_STAGE_SETUP;

        break;
    case UDC_EP0_STAGE_IN:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Setup Data Stage IN%s\n", " ");

        retval = sdudcServiceSetupRequest(pD, &setup);
        /*if request handled*/
        if (retval == 0) {
            /*Change Setup stage to Status Out. It will be handled
             * in interrupt when data transfer has been finished */
            pD->ep0State = UDC_EP0_STAGE_STATUSOUT;
        }

        break;
    case UDC_EP0_STAGE_OUT:
        pD->regs->ep0Rxbc = 0x0;
        retval = UDC_EUNHANDLED;
        break;
    default:
        if(retval == UDC_EAUTOACK)
            return;
        retval = UDC_EUNHANDLED;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Forward request%s\n", " ");
        break;
    }

    if (retval == UDC_ESTALL) {

    } else if (retval == UDC_EUNHANDLED) {
        if (pD->eventCallback.setup)
            retval = pD->eventCallback.setup(pD, &setup);
        /*If returned value != 0 then set stall to EP0*/
        if(retval == 0x7FFF) {
            DbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Respond Delayed not finised yet%s\n", " ");
            return;
        }

        if (retval)
            retval = UDC_ESTALL;
    }

    if (retval == UDC_EUNHANDLED || retval == UDC_ESTALL) {
        uint8_t cs;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Request not handled - Send Stall %s\n", " ");
        cs = CPS_UncachedRead8(&pD->regs->ep0cs);
        cs |= UCDM_EP0CS_STALL;
        CPS_UncachedWrite8(&pD->regs->ep0cs, cs);
        pD->ep0State = UDC_EP0_STAGE_SETUP;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Setup transfer completed%s\n", " ");
    } else if (pD->ep0State == UDC_EP0_STAGE_ACK) { /*We have to send ACK b*/
        pD->ep0State = UDC_EP0_STAGE_SETUP;
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Setup transfer completed%s\n", " ");
        CPS_UncachedWrite8(&pD->regs->ep0cs, UCDM_EP0CS_HSNAK);
    }
}

static uint32_t sdudcEp0Irq(UDC_Device *pD) {

    switch (pD->ep0State) {
    case UDC_EP0_STAGE_IN:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "DATA Stage IN%s\n", " ");
        sdudcEp0DataSend(pD);
        break;
    case UDC_EP0_STAGE_OUT:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "DATA Stage Out%s \n", "");
        sdudcEp0DataReceive(pD);
        break;
    case UDC_EP0_STAGE_STATUSIN:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Status Stage IN %s\n", " ");
        sdudcEp0StageStatusIn(pD);
        break;
    case UDC_EP0_STAGE_STATUSOUT:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Status Stage OUT %s\n", " ");
        sdudcEp0StageStatusOut(pD);
        break;
    case UDC_EP0_STAGE_SETUP:
        vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "SETUP Stage%s\n", " ");
        sdudcEp0StageSetup(pD);
        break;
    default:
        {
            uint8_t reg = CPS_UncachedRead8(&pD->regs->usbcs);
            reg |= UCDM_EP0CS_STALL;
            vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "USB error %s\n", " ");
            CPS_UncachedWrite8(&pD->regs->usbcs, reg);
            break;
        }
    }

    return 0;
}

static uint32_t sdudcEp0Dequeue(UDC_Device * pD, UdcEp *udcEp, struct CUSBD_Req * req) {
    /*not needed*/
    return EINVAL;
}

static uint32_t sdudcEp0Queue(UDC_Device *pD, UdcEp *udcEp, struct CUSBD_Req * req) {
    UdcRequest *udcRequest;
    UCRegs * regs;
    if (!udcEp || !req || !pD)
        return EINVAL;

    regs = pD->regs;
    udcRequest = sdudcUsbRequestToUdcRequest(req);

    req->actual = 0;
    req->status = EINPROGRESS;

    udcRequest->ep = udcEp;

    //check if list of request is empty
    if (udcEp->request.next != &udcEp->request)
        return EBUSY;

    switch (pD->ep0State) {
    case UDC_EP0_STAGE_OUT:
    case UDC_EP0_STAGE_IN:
    case UDC_EP0_STAGE_ACK:
        break;
    default:
        return EINVAL;
        break;
    }

    /*Now we can add request to Ep0 request list*/
    listAddTail(&req->list, &udcEp->request);
    udcEp->requestsInList++;

    vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1, "Queue to %s (%s), length=%d, stage: %d\n",
            udcEp->usbEp.name, udcEp->isInEp ? "IN/TX" : "OUT/RX", req->length,
            pD->ep0State);

    switch (pD->ep0State) {
    case UDC_EP0_STAGE_OUT:
        sdudcEp0DataReceive(pD);
        break;
    case UDC_EP0_STAGE_IN:
        sdudcEp0DataSend(pD);
        break;
    case UDC_EP0_STAGE_ACK:
        if (req->length)
            return EINVAL;
        else {
            CPS_UncachedWrite8(&regs->ep0cs, UCDM_EP0CS_HSNAK);
            sdudcEp0Callback(pD, udcRequest->ep, req, 0);
            vDbgMsg(DBG_CUSBD_VERBOSE_CONTROL_MSG, 1,
                    "Control transfer Completed%s", " ");
        }
        break;
    case UDC_EP0_STAGE_STATUSOUT:
    case UDC_EP0_STAGE_STATUSIN:
    case UDC_EP0_STAGE_SETUP:
        /*do nothing*/
        break;
    }
    return 0;
}

/******************************************************************************
 * Private Driver functions and macros - EpX handling
 *****************************************************************************/
/**
 * Function delete request from list for EPX and notify about this event
 * user application by calling complete callback
 */
static void sdudcEpXCallback(UDC_Device *pD, UdcEp * udcEp,
        struct CUSBD_Req * usbRequest, uint32_t status) {

    /**Delete request from list of requests */
    listDelete(&usbRequest->list);

    udcEp->requestsInList--;

    usbRequest->status = status;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 0, "Complete Req: %p with 0x%02x status for %s, ERIL %d\n",
            usbRequest, usbRequest->status, udcEp->usbEp.name, udcEp->requestsInList);

    usbRequest->complete(&udcEp->usbEp, usbRequest);
}

/**
 * Start transfer for receiving data on endpoint different then EP0
 */
inline static void sdudcEpXDataReceive(UDC_Device *pD, UdcRequest * udcRequest) {
    UdcEp * udcEp = udcRequest->ep;
    struct CUSBD_Req * usbRequest = NULL;
    CUSBDMA_OBJ * dmaDrv = pD->dmaDrv;
    uint32_t requestSize = 0;
    uint8_t epType =0;
    uint32_t channelStatus;
    uint32_t chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
            udcEp->channel);

    epType = udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK;

    channelStatus = dmaDrv->getChannelStatus(pD->dmaController, udcEp->channel);
    if((channelStatus >= CUSBDMA_STATUS_BUSY && !pD->cfg.dmultEnabled) ||
    	(channelStatus >= CUSBDMA_STATUS_BUSY &&  ((epType != CH9_USB_EP_INTERRUPT)
		 && (epType != CH9_USB_EP_ISOCHRONOUS))))	{
        vDbgMsg(DBG_CUSBD_BASIC_MSG, 0, "transfer for %s is pending now\n",
                udcEp->usbEp.name);
        return;
    }

    usbRequest = &udcRequest->request;
    if ((usbRequest->actual < usbRequest->length) || udcRequest->zlp) {
        requestSize =
            ((usbRequest->length - usbRequest->actual) < chMaxLen) ? (usbRequest->length - usbRequest->actual): chMaxLen;

        vDbgMsg(DBG_CUSBD_BASIC_MSG, 1,
                "Transmit/IN %s  usbRequest %p, udcRequest %p, requestSize: 0x%x, packetSize 0x%x\n",
                udcEp->usbEp.name, usbRequest, udcRequest, requestSize,
                udcEp->usbEp.maxPacket);
        udcRequest->zlp = 0;
        dmaDrv->channelProgram(pD->dmaController, udcEp->channel,
                usbRequest->maxpacket, usbRequest->dma + usbRequest->actual,
                requestSize, NULL, 0);
    }
}

/**
 * Start transfer for sending data on endpoint different then EP0
 */
inline static void sdudcEpXDataSend(UDC_Device *pD, UdcRequest * udcRequest) {
    UdcEp * udcEp = udcRequest->ep;
    struct CUSBD_Req * usbRequest = NULL;
    CUSBDMA_OBJ * dmaDrv = pD->dmaDrv;
    uint32_t requestSize = 0;
    uint8_t epType;
    uint32_t channelStatus;
    uint32_t chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
            udcEp->channel);

    epType = udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK;
    channelStatus = dmaDrv->getChannelStatus(pD->dmaController, udcEp->channel);

    if((channelStatus >= CUSBDMA_STATUS_BUSY && !pD->cfg.dmultEnabled) ||
     	(channelStatus >= CUSBDMA_STATUS_BUSY &&  (epType != CH9_USB_EP_ISOCHRONOUS)
        && (epType != CH9_USB_EP_INTERRUPT)))	{
        vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "transfer for %s is pending now\n",
                udcEp->usbEp.name);
        return;
    }

    usbRequest = &udcRequest->request;
    requestSize =
        ((usbRequest->length - usbRequest->actual) < chMaxLen) ? (usbRequest->length - usbRequest->actual): chMaxLen;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1,
            "Transmit/IN %s  usbRequest %p, udcRequest %p, requestSize: 0x%x, packetSize 0x%x\n",
            udcEp->usbEp.name, usbRequest, udcRequest, requestSize,
            udcEp->usbEp.maxPacket);
    udcRequest->zlp = 0;
    dmaDrv->channelProgram(pD->dmaController, udcEp->channel,
            usbRequest->maxpacket, usbRequest->dma+usbRequest->actual, requestSize,
            NULL, 0);
}

inline static void sdudcEpXDataCallback(UDC_Device *pD, uint8_t epNum,
        uint8_t dir) {
    UdcEp * udcEp = NULL;
    struct CUSBD_Req * usbRequest = NULL;
    uint32_t actual_length =0;
    uint32_t chMaxLen =0;
    if (dir)
        udcEp = &pD->in[epNum];
    else
        udcEp = &pD->out[epNum];

    usbRequest = sdudcGetNexReq(udcEp);
    if (!usbRequest) {
        vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "%s queue is empty\n",
                udcEp->usbEp.name);
        return;
    }

    if (udcEp->channel) {
        actual_length = pD->dmaDrv->getActualLength(pD->dmaController,
                udcEp->channel);
        chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
                udcEp->channel);
        usbRequest->actual += actual_length;

    }

    if (usbRequest->actual == usbRequest->length || actual_length < chMaxLen ) {
         uint8_t epType;
        sdudcEpXCallback(pD, udcEp, usbRequest, 0);
    	

        //check if ep is EP0
        if (udcEp->usbEp.desc) {

       	    /**
    	    * For Isochronous transfers (DMULT mode) firmware hasn't to start next transfer from list because all transfers are linked in DMA module
    	    * and will be started automatically by this module
    	    */
       	    epType = (udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK);
            if ((epType == CH9_USB_EP_ISOCHRONOUS  || epType == CH9_USB_EP_INTERRUPT) && pD->cfg.dmultEnabled)
        	    return;

            usbRequest = sdudcGetNexReq(udcEp);
            /*Now this endpoint can be used for other transfer*/
            udcEp->state = UDC_EP_ALLOCATED;
            if (!usbRequest) {
                vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "%s queue is empty\n",
                        udcEp->usbEp.name);
                return;
            } else {
                udcEp->state = UDC_EP_BUSY;
                if (dir) {
                    sdudcEpXDataSend(pD,
                            sdudcUsbRequestToUdcRequest(usbRequest));
                } else {
                    sdudcEpXDataReceive(pD,
                            sdudcUsbRequestToUdcRequest(usbRequest));
                }
            }
        }
    } else {
        /*Continue transfer for this request*/
        if (dir) {
            sdudcEpXDataSend(pD,
                    sdudcUsbRequestToUdcRequest(usbRequest));
        } else {
            sdudcEpXDataReceive(pD,
                    sdudcUsbRequestToUdcRequest(usbRequest));
        }

    }
}

/**
 * Waits for clearing BUSY bit for IN[1..15] endpoint.
 * For OUT endpoints and for EP0 function return immediately.
 */
static uint32_t sdudcWaitForBusyBit(UDC_Device * pD, CUSBD_Ep * usbEp) {
    UdcEp * udcEp = sdudcUsbEpToUdcEp(usbEp);
    UCRegs *regs = pD->regs;
    uint8_t val = UCM_CS_BUSY;
    uint8_t buf =0;
    uint8_t bufflag = 0;

    if(!udcEp->isInEp || udcEp->hwEpNum ==0)
        return 0;

    buf= CPS_UncachedRead8(&regs->ep[udcEp->hwEpNum-1].txcon)  & UCM_CON_BUF;

    while((val & UCM_CS_BUSY) || (bufflag == 0) ) {
        val = CPS_UncachedRead8(&regs->ep[udcEp->hwEpNum-1].txcs);

        if(((val & UCM_CS_NPAK) >>  UCO_CS_NPAK) == buf || buf == 0)
        	bufflag =1;
		else
			bufflag =0;
    }

    return 0;
}

/**
 * Clear or Set stall for Endpoint (value = 1 - set stall, value=0 -clear stall)
 */
static uint32_t sdudcEpXSetHalt(UDC_Device *pD, struct CUSBD_Ep * usbEp,
        uint8_t value) {
    UdcEp * udcEp = sdudcUsbEpToUdcEp(usbEp);
    uint8_t epNum = udcEp->hwEpNum;
    uint8_t epType;
    UCRegs * regs;
    uint8_t conReg;
    UdcRequest * udcRequest = NULL;
    struct CUSBD_Req * usbRequest = NULL;
    uint32_t status = CUSBDMA_STATUS_ARMED;

    if (!usbEp)
        return EINVAL;

    epType = (udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK);

    if (epType == CH9_USB_EP_ISOCHRONOUS)
        return EINVAL;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "%s: %s stall\n", usbEp->name,
            value ? "set" : "clear");
    regs = pD->regs;

    usbRequest = sdudcGetNexReq(udcEp);
    if(!value) {
        udcEp->wedged = 0;
    }

    /*Before firmware set STALL for IN endpoint it has to wait for finishing started DMA transfer*/
    if(value && udcEp->isInEp && usbRequest && udcEp->state == UDC_EP_BUSY) {
        while(status == CUSBDMA_STATUS_ARMED) {
            //updates actual state of DMA channel
             status = pD->dmaDrv->getChannelStatus(pD->dmaController, udcEp->channel);
        }
        sdudcWaitForBusyBit(pD, usbEp);
    }

    if (udcEp->isInEp) {
        conReg = CPS_UncachedRead8(&regs->ep[epNum - 1].txcon);
        if (value) {
            CPS_UncachedWrite8(&regs->ep[epNum - 1].txcon, conReg | UCDM_CON_STALL);
            CPS_UncachedWrite8(&regs->endprst,  UCM_ENDPRST_IO_TX | epNum);
            CPS_UncachedWrite8(&regs->endprst, UCM_ENDPRST_IO_TX | epNum | UCM_ENDPRST_FIFORST);
        } else {
            /*Reset Endpoint (fifo and toggle bit*/
            CPS_UncachedWrite8(&regs->endprst, UCM_ENDPRST_IO_TX | epNum);
            CPS_UncachedWrite8(&regs->endprst,
                    UCM_ENDPRST_IO_TX | epNum
                    | UCM_ENDPRST_TOGRST);
           CPS_UncachedWrite8(&regs->ep[epNum - 1].txcon, conReg & ~UCDM_CON_STALL);
        }
    } else {
        conReg = CPS_UncachedRead8(&regs->ep[epNum - 1].rxcon);
        if (value) {
            CPS_UncachedWrite8(&regs->ep[epNum - 1].rxcon, conReg | UCDM_CON_STALL);
            CPS_UncachedWrite8(&regs->endprst,  epNum);
            CPS_UncachedWrite8(&regs->endprst, epNum | UCM_ENDPRST_FIFORST);
        } else {
            CPS_UncachedWrite8(&regs->endprst,  epNum);
            CPS_UncachedWrite8(&regs->endprst,  epNum | UCM_ENDPRST_TOGRST | UCM_ENDPRST_FIFORST );
            CPS_UncachedWrite8(&regs->ep[epNum - 1].rxcon, conReg & ~UCDM_CON_STALL);
        }
    }

// 为什么要发送呢？
    if (udcEp->state != UDC_EP_BUSY && !value && usbRequest) {
        udcRequest = sdudcUsbRequestToUdcRequest(usbRequest);
        if (udcEp->isInEp) {
            sdudcEpXDataSend(pD, udcRequest);
        } else
            sdudcEpXDataReceive(pD, udcRequest);
    }
    return 0;
}

/**
 * Enable USB endpoint.
 */
static inline uint32_t sdudcEpXEnable(UDC_Device * pD, UdcEp * udcEp,
        const CH9_UsbEndpointDescriptor * desc) {
    uint32_t status = EINVAL;
    UCRegs * regs = pD->regs;
    uint16_t tmp = 0;
    uint8_t type, iso = 0;
    uint8_t epNum = 0;
    uint32_t payload =0;

    if (!udcEp || !desc)
        return EINVAL;

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Enable Endpoint %s \n", udcEp->usbEp.name);

    if (udcEp->state != UDC_EP_FREE) {
        status = EBUSY;
        goto fail;
    }

    epNum = udcEp->hwEpNum;

    tmp = le16ToCpu(desc->wMaxPacketSize);
    if (!(tmp & 0x07ff)) {
    	status = EINVAL;
        goto fail;
    }

    payload = tmp & 0x07ff;

    type = desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK;
    switch (type) {
    case CH9_USB_EP_ISOCHRONOUS:
        type = UCM_CON_TYPE_ISOC;
        switch (tmp >> 11) {
        case 0:
            iso = UCM_CON_1_ISOD;
            break;
        case 1:
        	payload *=2;
            iso = UCM_CON_2_ISOD;
            break;
        case 2:
        	payload *=3;
            iso = UCM_CON_3_ISOD;
            break;
        }
        break;
    case CH9_USB_EP_BULK:
        type = UCM_CON_TYPE_BULK;
        break;
    case CH9_USB_EP_INTERRUPT:
        type = UCM_CON_TYPE_INT;
        break;
    }

    tmp &= 0x07ff;
    if (desc->bEndpointAddress & CH9_USB_DIR_DEVICE_TO_HOST) {
        if (!udcEp->isInEp) {
        	status = ENODEV;
            goto fail;
        }

        if (tmp > pD->cfg.epIN[epNum].maxPacketSize) {
        	status =  EINVAL;
            goto fail;
        }

        CPS_UncachedWrite16(&regs->txmaxpack[epNum - 1], tmp);
        CPS_UncachedWrite8(&regs->ep[epNum - 1].txcon,
                UCM_CON_VAL | type | iso
                | (pD->cfg.epIN[epNum].bufferingValue - 1));

        CPS_UncachedWrite8(&pD->regs->fifoctrl,
                (UCM_FIFOCTRL_FIFOAUTO | UCM_FIFOCTRL_IO_TX | epNum));

        /*Reset Endpoint (fifo and toggle bit*/
        CPS_UncachedWrite8(&regs->endprst, UCM_ENDPRST_IO_TX | epNum);
        CPS_UncachedWrite8(&regs->endprst,
                UCM_ENDPRST_IO_TX | epNum | UCM_ENDPRST_FIFORST
                | UCM_ENDPRST_TOGRST);
    } else {
        if (udcEp->isInEp) {
        	status = ENODEV;
            goto fail;
        }

        if (tmp > pD->cfg.epOUT[epNum].maxPacketSize) {
        	status = EINVAL;
            goto fail;
        }

        CPS_UncachedWrite16(&regs->rxmaxpack[epNum - 1], tmp);
        CPS_UncachedWrite8(&regs->ep[epNum - 1].rxcon,
                UCM_CON_VAL | type | iso
                | (pD->cfg.epIN[epNum].bufferingValue - 1));

        CPS_UncachedWrite8(&pD->regs->fifoctrl,
                (UCM_FIFOCTRL_FIFOAUTO | epNum));

        /*Reset Endpoint (fifo and toggle bit*/
        CPS_UncachedWrite8(&regs->endprst, epNum);
        CPS_UncachedWrite8(&regs->endprst,
                epNum | UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST);
    }

    if (pD->dmaController) {
        udcEp->channel = pD->dmaDrv->channelAlloc(pD->dmaController,
                udcEp->isInEp, epNum,  (type == UCM_CON_TYPE_ISOC)? 1 : 0);
    }

    if(type == UCM_CON_TYPE_ISOC) {
    	if(!pD->cfg.dmultEnabled) {
            uint8_t reg =  CPS_UncachedRead8(&regs->usbien);
            reg |= UCM_USBIR_SOF;
            /*Enable interrupt for sof. In each SOF Irq software call busInterval callback*/
            CPS_UncachedWrite8(&regs->usbien, reg);
    	}

        if(udcEp->isInEp) {
        //  CPS_UncachedWrite16(&regs->isoautoarm,  1 << epNum);
            CPS_UncachedWrite16(&regs->isoautodump,  0 << epNum);
            // CPS_UncachedWrite16(&regs->isodctrl,  1 << epNum);
        }
        // pD->dmaDrv->setMaxLength(pD->dmaController, udcEp->channel, payload);
        pD->dmaDrv->setMaxLength(pD->dmaController, udcEp->channel, tmp);
    }


    udcEp->state = UDC_EP_ALLOCATED;
    udcEp->usbEp.desc = desc;
    status = 0;
fail:
    return status;
}

static inline uint32_t sdudcEpXDisable(UDC_Device * pD, UdcEp * udcEp) {
    uint8_t tmp =0;

    vDbgMsg(DBG_CUSBD_INIT_EP_MSG, 1, "Disable Endpoint %s \n", udcEp->usbEp.name);

    /*start critical section*/
    tmp = udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK;

    /*Disable interrupt for sof. SOF IRQ should be enabled only for ISOC endpoints*/
    if(tmp == CH9_USB_EP_ISOCHRONOUS && !pD->cfg.dmultEnabled) {
        tmp =  CPS_UncachedRead8(&pD->regs->usbien);
        tmp &= ~UCM_USBIR_SOF;
        /*Disable interrupt for sof. SOF IRQ should be enabled only for ISOC endpoints*/
        CPS_UncachedWrite8(&pD->regs->usbien, tmp);
    }

    if (udcEp->isInEp) {
        tmp = CPS_UncachedRead8(&pD->regs->ep[udcEp->hwEpNum - 1].txcon);
        tmp &= ~UCM_CON_VAL; //mask for valid bit
        CPS_UncachedWrite8(&pD->regs->ep[udcEp->hwEpNum - 1].txcon, tmp);
    } else {
        tmp = CPS_UncachedRead8(&pD->regs->ep[udcEp->hwEpNum - 1].rxcon);
        tmp &= ~UCM_CON_VAL; //mask for valid bit
        CPS_UncachedWrite8(&pD->regs->ep[udcEp->hwEpNum - 1].rxcon, tmp);
    }
    sdudcAbortEndpoint(pD, udcEp);
    udcEp->usbEp.desc = 0;
    udcEp->state = UDC_EP_FREE;
    /*end critical section*/
    return 0;
}

/**
 * Add request to queue associated with appropriate USB endpoint
 */
uint32_t sdudcEpXQueue(UDC_Device *pD, UdcEp *udcEp, struct CUSBD_Req * req) {
    UdcRequest *udcRequest;
    printf("udcEp=%x %x %x \n", udcEp, req, pD);
    if (!udcEp || !req || !pD)
        return sdudcReturnError(EINVAL);

    printf("req->buf=%x \n", req->buf);
    if (req->buf == NULL )
        return sdudcReturnError(EINVAL);

    udcRequest = sdudcUsbRequestToUdcRequest(req);

    req->actual = 0;
    req->status = EINPROGRESS;

    if(req->length == 0)
        udcRequest->zlp = 1;

    udcRequest->ep = udcEp;

    /*Endpoint is not configured */
    if (udcEp->usbEp.desc == NULL ) {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1,
                "%s is disabled - can not queue request %p\n", udcEp->usbEp.name,
                req);
        return sdudcReturnError(EINVAL);
    }

    /*Now we can add request to EpX request list*/
    listAddTail(&req->list, &udcEp->request);

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Queue to %s (%s), length=%d\n",
            udcEp->usbEp.name, (udcEp->isInEp ? "IN/TX" : "OUT/RX"),
            req->length);

    /*If endpoint is not busy now and request list has only one element then we can
     * start transfer immediately */
    if ((udcEp->state == UDC_EP_ALLOCATED)
            && (&req->list == udcEp->request.next)) {
        /*From this moment endpoint is busy end reserved for transfer*/
        if (udcEp->isInEp) {
            if(!(CPS_UncachedRead8(&pD->regs->ep[udcEp->hwEpNum - 1].txcon) &  UCDM_CON_STALL)) {
                udcEp->state = UDC_EP_BUSY;
                sdudcEpXDataSend(pD, udcRequest);
            }
        } else
            if(!(CPS_UncachedRead8(&pD->regs->ep[udcEp->hwEpNum - 1].rxcon) &  UCDM_CON_STALL)) {
                udcEp->state = UDC_EP_BUSY;
                sdudcEpXDataReceive(pD, udcRequest);
            }

    } else if(udcEp->state == UDC_EP_BUSY && pD->cfg.dmultEnabled ) {
    	if((((udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK) == CH9_USB_EP_ISOCHRONOUS) ||
                ((udcEp->usbEp.desc->bmAttributes & CH9_USB_EP_TRANSFER_MASK) == CH9_USB_EP_INTERRUPT)) &&
    			pD->cfg.dmultEnabled) {
                 /*Preparing transfer chain for next request and link it in DMA module.
                 In this moment DMA probably has been already started.*/
    	        if (udcEp->isInEp) {
    	            sdudcEpXDataSend(pD, udcRequest);
    	        } else
    	            sdudcEpXDataReceive(pD, udcRequest);

    			return 0;

    	}
        vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Endpoint  %s (%s), now is BUSY- Transfer will be wiating in Queue\n",
                udcEp->usbEp.name, (udcEp->isInEp ? "IN/TX" : "OUT/RX"));
    }
    return 0;
}

/**
 * Dequeue USB request from queue.
 */
uint32_t sdudcEpXDequeue(UDC_Device *pD, UdcEp *udcEp, struct CUSBD_Req * req) {
    UdcRequest * udcRequest;
    struct CUSBD_Req * iterator;
    udcRequest = sdudcUsbRequestToUdcRequest(req);

    if (!udcEp || !req || !pD)
        return sdudcReturnError(EINVAL);

    /*Check if endpoint is properly for given request*/
    if (udcRequest->ep != udcEp) {
        return sdudcReturnError(EINVAL);
    }

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Dequeue request %p from  %s\n", req ,
            udcEp->usbEp.name);

    listBrowsingRequest(iterator, &udcEp->request, list)
    {
        if (req == iterator)
            break;
    }

    if (req != iterator) {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1, "request %p not queued to %s", req,
                udcEp->usbEp.name);
        return EINVAL;
    }

    if (udcEp->state == UDC_EP_BUSY) {
        pD->dmaDrv->channelAbort(pD->dmaController, udcEp->channel);
        udcEp->state = UDC_EP_ALLOCATED;
    }

    sdudcEpXCallback(pD, udcEp, req, UDC_ECONNRESET);
    return 0;
}

/**
 * This function has to be visible for host driver, so it can not be static
 * or has to be added to device API
 */
uint32_t udcGetPrivateSize(void) {
    return sizeof(UDC_Device);
}

/**
 * Function return content of mqpTestSrp field from UDC_Device object
 * Function used by MQP tester
 */
uint8_t getMQPTestSrpFlag(void * privateData) {
	return((UDC_Device*)privateData)->mqpTestSrp;
}

/**
 * Function clear content of mqpTestSrp field from UDC_Device object
 * Function used by MQP tester
 */
void clearMQPTestSrpFlag(void * privateData) {
	((UDC_Device*)privateData)->mqpTestSrp = 0;
}
/*****************************************************************************
 * Public Driver function
 *****************************************************************************/

static uint32_t sdudcProbe(CUSBD_Config * config, CUSBD_SysReq * sysReq) {
    CUSBDMA_OBJ * dmaDrv = NULL;
    CUSBDMA_Config dmaConfig;
    CUSBDMA_SysReq dmaSysReq;
    uint32_t res; // keeps result of operation on driver

    if ((config == NULL )|| (sysReq == NULL)) {
        return EINVAL;
    }

    if(config->dmaInterfaceWidth != CUSBD_DMA_32_WIDTH && config->dmaInterfaceWidth != CUSBD_DMA_64_WIDTH) {
        return EINVAL;
    }

    dmaConfig.regBase = config->regBase + 0x400;
    /*DMA mode for DMA will be set globally*/

    dmaDrv = CUSBDMA_GetInstance();
    res = dmaDrv->probe(&dmaConfig, &dmaSysReq);
    if(res) return res;

    sysReq->privDataSize = udcGetPrivateSize() + dmaSysReq.privDataSize;
    sysReq->trbMemSize = dmaSysReq.trbMemSize + UDC_PRIV_BUFFER_SIZE;

    return 0;
}

/**
 * This function cannot be static because it is used internally by CUSBH component.
 */
void sdudcCallbackTransfer(void * privateData, uint8_t epNum, uint8_t epDir) {
    UDC_Device * pD = (UDC_Device *) privateData;
    /* called with controller lock already held */
    if (!epNum) {
        sdudcEp0Irq(pD);
    } else {
        /* endpoints 1..15 */
        sdudcEpXDataCallback(pD, epNum, epDir);
    }
}

#ifdef USB_CONTROLLER_BYTE_SWAP
/**
 * Function set the correct endian byte order for SFRs access.
 * Little Endian byte order is a default value after reset.
 */
static void sdudcSetSFREndian(UCRegs * regs){
    volatile uint8_t test[4] = {1, 0, 0, 0 };
    volatile uint32_t volatile *test_ptr = (uint32_t*)test;

#define BIG_ENDIAN_MAGIC_NUMBER 0x01000000ul
    if(*test_ptr ==  BIG_ENDIAN_MAGIC_NUMBER) {
        CPS_UncachedWrite8(&regs->endian_sfr_cs,  UCRM_ENDIAN_SFR_CS_BENDIAN);
    }
}
#endif

static uint32_t sdudcInit(void *privateData, const CUSBD_Config* config,
        CUSBD_Callbacks* callbacks) {
    uint8_t usbcs = 0;
    UDC_Device * pD = NULL;
    CUSBDMA_OBJ * dmaDrv = NULL;
    CUSBDMA_Config dmaConfig;
    CUSBDMA_SysReq dmaSysReq;

    if ((privateData == NULL )|| (config == NULL) || (callbacks == NULL))
        return EINVAL;

    pD = (UDC_Device*)(privateData);

    memset(privateData, 0, (sizeof(UDC_Device)));

    pD->eventCallback = *callbacks;
    pD->cfg = *config;
    pD->regs = (UCRegs*) config->regBase;
    pD->udcDrv = CUSBD_GetInstance();

    /*Creating Dma Controller*/
    pD->dmaDrv = CUSBDMA_GetInstance();
    pD->dmaController = (void*) ((uintptr_t) privateData +udcGetPrivateSize());
    pD->dmaCfg.regBase = config->regBase + 0x400;
    pD->dmaCfg.trbAddr = config->trbAddr;
    pD->dmaCfg.trbDmaAddr = config->trbDmaAddr;

    dmaDrv = CUSBDMA_GetInstance();
    dmaDrv->probe(&dmaConfig, &dmaSysReq);

    pD->privBuffAddr = (uint8_t*)((uintptr_t)config->trbAddr + dmaSysReq.trbMemSize);
    pD->privBuffDma  = (uintptr_t)((uintptr_t)config->trbDmaAddr + dmaSysReq.trbMemSize);
#ifdef USB_CONTROLLER_BYTE_SWAP
    sdudcSetSFREndian(pD->regs);
#endif


    if(config->dmultEnabled) {
        pD->dmaCfg.dmaModeRx = 0xFFFF;
        pD->dmaCfg.dmaModeTx = 0xFFFF;
    } else {
        pD->dmaCfg.dmaModeRx = 0x0000;
        pD->dmaCfg.dmaModeTx = 0x0000;
    }
    /*This should be set only for One-role Device mode. For Dual role
     * controller this DMa callback and DMA initialization will be controller by HOST driver.
     * If Dual role device will work in DEVICE mode then HOST driver
     * redirect DMA completion to Device driver.*/
    if(config->isDevice) {
        pD->dmaCallback.complete = sdudcCallbackTransfer;

        pD->dmaDrv->init(pD->dmaController, &pD->dmaCfg, &pD->dmaCallback);
        pD->dmaDrv->setParentPriv(pD->dmaController, pD);
    }

    /*Set Disconnect USB controller*/
    usbcs = CPS_UncachedRead8(&pD->regs->usbcs);
    usbcs |= UCM_USBCS_DISCON | UCDM_USBCS_LPMNYET;
    CPS_UncachedWrite8(&pD->regs->usbcs, usbcs);

    sdudcSetup(pD);
    return 0;
}

static void sdudcDestroy(void *privateData) {
    UDC_Device * pD = (UDC_Device*) privateData;

    vDbgMsg(DBG_CUSBD_BASIC_MSG, 1, "Destroy Device Controller driver %s", " ");
    if (!privateData)
        return;
    CPS_UncachedWrite8(&pD->regs->usbcs, UCM_USBCS_DISCON);
    sdudcDisconnect(pD);
    sdudcStopActivity(privateData);
    pD->isReady =0;
}

static void sdudcStart(void *privateData) {
    UDC_Device * pD = (UDC_Device*) privateData;
    UCRegs * regs = NULL;
    uint8_t reg;

    if (!privateData)
        return;

    regs = pD->regs;
    if (!pD->cfg.isDevice) {
        if (pD->isReady)
            return;
        else
            sdudcSetup(pD);
    }

    reg = CPS_UncachedRead8(&regs->usbien);
    reg |= UCM_USBIR_URES | UCDM_USBIR_SUDAV /*| UCM_USBIR_SOF*/ | UCM_USBIR_SUSP | UCDM_USBIR_LPMIR;
    CPS_UncachedWrite8(&regs->usbien, reg);

    /*Set Connect USB controller*/
    reg = CPS_UncachedRead8(&pD->regs->usbcs);
    reg &= ~UCM_USBCS_DISCON;
    CPS_UncachedWrite8(&pD->regs->usbcs, reg);
    /*Host driver start DMA for isOTG configuration  */
    if(pD->cfg.isDevice)
        pD->dmaDrv->start(pD->dmaController);
    // pD->udcDrv->print_reg(pD);
    // pD->dmaDrv->print_reg(pD);
    // while(1);
}

static void sdudcStop(void *privateData) {
    UDC_Device * pD = NULL;
    UCRegs * regs = NULL;

    if (!privateData)
        return;

    pD = (UDC_Device*) privateData;

    if (!pD->isReady)
        return;

    regs = pD->regs;

    sdudcReset(pD);

    CPS_UncachedWrite8(&regs->usbien, 0);
    /*Host driver use DMA for OTG so we can't stop it*/
    if(pD->cfg.isDevice)
        pD->dmaDrv->stop(pD->dmaController);
    pD->isReady =0;
}
#define BASE_MAILBOX 0x970E0000U
#define MAILBOX_WAKEUP (BASE_MAILBOX+0x58)
/**
 * Generic ISR for CUSBD driver
 */
static void sdudcIsr(void *privateData) {
    UDC_Device * pD = NULL;
    UCRegs * usb_regs = NULL;
    uint8_t usbIrqV, usbIrqM;

    if (!privateData)
        return; // EINVAL;

    pD = (UDC_Device*) privateData;
    usb_regs = pD->regs;
    vDbgMsg(DBG_CUSBD_ISR_MSG , 1, "wakesrc = 0x%x\n", CPS_UncachedRead8(&usb_regs->usbcs));
    if(CPS_UncachedRead8(&usb_regs->usbcs) & UCM_USBCS_WAKESRC)
    {
        // *(uint32_t *)MAILBOX_WAKEUP = 0;
        udcUsbResume(pD);
    }
    
    usbIrqV = CPS_UncachedRead8(&usb_regs->usbirq);
    usbIrqM = CPS_UncachedRead8(&usb_regs->usbien);

    usbIrqV = usbIrqV & usbIrqM;

    if (!usbIrqV) {
        vDbgMsg(DBG_CUSBD_ISR_MSG , 1, "NO usbIrq%s\n", " ");
        goto DMA_IRQ;
    }

    vDbgMsg(DBG_CUSBD_ISR_MSG , 1, "SFR (usbirq & usbien) =  %02x\n", usbIrqV );

    if (usbIrqV & UCDM_USBIR_LPMIR) {
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: LPM%s\n", " ");
        //      lpm_callback(NULL );
        /* Clear the NYET bit */
        uint8_t usbcs = CPS_UncachedRead8(&pD->regs->usbcs);
        usbcs &= ~UCDM_USBCS_LPMNYET;
        CPS_UncachedWrite8(&pD->regs->usbcs, usbcs);
        CPS_UncachedWrite8(&usb_regs->usbirq, UCDM_USBIR_LPMIR);
        //      evx_set_clkgate(0x00);
    }

    if (usbIrqV & UCM_USBIR_URES) {
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: RESET%s\n", " ");
        /* Clearing interrupt bits */
        CPS_UncachedWrite8(&usb_regs->usbirq, UCM_USBIR_URES);
        /*Reset all but not release channel DMA for EP0*/
        pD->releasEp0Flag = 1;
        sdudcReset(pD);
        pD->releasEp0Flag = 0;
        pD->usbDev.state = CH9_USB_STATE_DEFAULT;
        if (pD->eventCallback.connect)
            pD->eventCallback.connect(pD);
    }

    /*This interrupt is not handled by firmware because Speed is checking by speedctrl SFR*/
    if (usbIrqV & UCM_USBIR_HSPPED) {
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: HighSpeed%s\n", " ");
        CPS_UncachedWrite8(&usb_regs->usbirq, UCM_USBIR_HSPPED);
        pD->usbDev.speed = CH9_USB_SPEED_HIGH;
    }

    if (usbIrqV & UCDM_USBIR_SUDAV) { /* setup packet interrupt */
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: SUDAV%s\n", " ");
        /* Sending request*/
        pD->ep0State =UDC_EP0_STAGE_SETUP;
        sdudcEp0Irq(pD);
    }

    /* SOF interrupt */
    if (usbIrqV & UCM_USBIR_SOF) {
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: SOF%s\n", " ");
        CPS_UncachedWrite8(&usb_regs->usbirq, UCM_USBIR_SOF);
        if(pD->eventCallback.busInterval)
            pD->eventCallback.busInterval(pD);
    }

    if (usbIrqV & UCDM_USBIR_SUTOK) {
        vDbgMsg(DBG_CUSBD_ISR_MSG, 1, "USBIRQ: SUTOK%s\n", " ");
        CPS_UncachedWrite8(&usb_regs->usbirq, UCDM_USBIR_SUTOK);
    }

    if (usbIrqV & UCM_USBIR_SUSP) {
        CPS_UncachedWrite8(&usb_regs->usbirq, UCM_USBIR_SUSP);
        vDbgMsg(DBG_CUSBD_ISR_MSG, 0, "USBIRQ1: SUSPEND%s\n", " ");
        CPS_UncachedWrite8(&pD->regs->clkgate, 0x1);
    }

DMA_IRQ:
    vDbgMsg(DBG_CUSBD_ISR_MSG , 1, "Generic CUSBD Interrupt%s\n", " ");
    if (pD->cfg.dmaSupport && pD->dmaDrv->isr) {
        vDbgMsg(DBG_CUSBD_ISR_MSG , 1, "Forward ISR to CUSBDMA ISR%s\n", " ");
        pD->dmaDrv->isr(pD->dmaController);
    } else {
        vDbgMsg(DBG_CUSBD_ERR_MSG, 1,
                "Error: CUSBD Driver support only DMA transfer. Switch on this option in configuration%s\n",
                " ");
    }

    return;
}

//endpoint operation
static uint32_t sdudcEpEnable(void *pD, struct CUSBD_Ep *usbEp,
        const CH9_UsbEndpointDescriptor * desc) {
    UdcEp * udcEp = NULL;

    if (!pD || !usbEp || !desc) {
        return EINVAL;
    }

    udcEp = sdudcUsbEpToUdcEp(usbEp);
    udcEp->wedged = 0;

    if (udcEp->hwEpNum)
        return sdudcEpXEnable(pD, udcEp, desc);
    else
        return sdudcEp0Enable(pD, udcEp);
}

static uint32_t sdudcEpDisable(void *pD, struct CUSBD_Ep * usbEp) {
    UDC_Device * ctrl = (UDC_Device*)pD;
    UdcEp * udcEp = NULL;

    if (!pD || !usbEp)
        return EINVAL;

    udcEp = sdudcUsbEpToUdcEp(usbEp);

    /*For OTG device should free DMA channel for EP0*/
    if(ctrl->cfg.isDevice) {
        if (udcEp->usbEp.address == 0)
            return EINVAL;
    }
    udcEp->wedged =0;
    if (udcEp->hwEpNum)
        return sdudcEpXDisable(pD, udcEp);
    else
        return sdudcEp0Disable(pD, udcEp);
}

static void sdudcFreeRequest(void *pD, struct CUSBD_Ep *ep, struct CUSBD_Req * req) {
    UdcRequest * udcRequest;
    UDC_Device *privateData = NULL;

    if (!pD || !ep || !req)
        return;

    privateData = (UDC_Device*)pD;
    udcRequest = sdudcUsbRequestToUdcRequest(req);

    if(privateData->eventCallback.usbRequestMemFree)
        privateData->eventCallback.usbRequestMemFree(pD, udcRequest);
    return;
}

static uint32_t sdudcEpAllocRequest(void *pD, struct CUSBD_Ep *ep,
        struct CUSBD_Req ** req) {
    UdcEp * udcEp = sdudcUsbEpToUdcEp(ep);
    UdcRequest *udcRequest = NULL;
    UDC_Device *privateData = NULL;
    if (!pD || !ep || !req)
        return EINVAL;

    privateData = (UDC_Device*)pD;

    if(privateData->eventCallback.usbRequestMemAlloc)
        udcRequest = privateData->eventCallback.usbRequestMemAlloc(pD, sizeof(*udcRequest));

    if (!udcRequest)
        return ENOMEM;

    memset(udcRequest, 0, sizeof(*udcRequest));
    *req = &udcRequest->request;

    listInit(&udcRequest->request.list);
    udcRequest->ep = udcEp;

    vDbgMsg(DBG_CUSBD_VERBOSE_MSG, 1, "Alloc Request %p epnum: %d \n", udcRequest,
            udcEp->hwEpNum);
    return 0;
}

static uint32_t sdudcEpQueue(void *pD, struct CUSBD_Ep *ep, struct CUSBD_Req * req) {
    UdcEp * udcEp;

    if (!ep || !req || !pD)
        return EINVAL;

    udcEp = sdudcUsbEpToUdcEp(ep);

    if (ep->address & CH9_USB_EP_NUMBER_MASK) {
        return sdudcEpXQueue((UDC_Device*) pD, udcEp, req);
    } else {
        return sdudcEp0Queue((UDC_Device*) pD, udcEp, req);
    }

}

static uint32_t sdudcEpDequeue(void *pD, struct CUSBD_Ep *ep, struct CUSBD_Req * req) {
    UdcEp * udcEp;

    if (!ep || !req || !pD)
        return EINVAL;

    udcEp = sdudcUsbEpToUdcEp(ep);

    if (ep->address) {
        return sdudcEpXDequeue((UDC_Device*) pD, udcEp, req);
    } else {
        return sdudcEp0Dequeue((UDC_Device*) pD, udcEp, req);
    }
    return 0;
}

static uint32_t sdudcEpSetHalt(void *pD, struct CUSBD_Ep *ep, uint8_t value) {
    if (!ep || !pD)
        return EINVAL;

    if (ep->address)
        sdudcEpXSetHalt(pD, ep, value);
    else
        sdudcEp0SetHalt(pD, ep, value);
    return 0;
}

static uint32_t sdudcEpSetWedge(void *pD, struct CUSBD_Ep * ep) {
    uint32_t err =0;
    UdcEp * udcEp;
    if (!ep || !pD)
        return EINVAL;

    udcEp = sdudcUsbEpToUdcEp(ep);
    udcEp->wedged = 1;
    err = sdudcEpSetHalt(pD, ep, 1);

    return err;
}

static uint32_t sdudcFifoStatus(void *pD, struct CUSBD_Ep * ep) {
    if (!ep || !pD)
        return EINVAL;
    return 0;
}

static void sdudcFifoFlush(void *pD, struct CUSBD_Ep * ep) {
    if (!ep || !pD)
        return;

    return;
}

static void sdudcGetDevInstance(void *pD, CUSBD_Dev ** dev) {
    UDC_Device * privateData = (UDC_Device *) pD;

    if(!pD || !dev)
        return;

    *dev = &privateData->usbDev;
}

//Device operations
static uint32_t sdudcGetFrame(void *pD, uint32_t *numOfFrame) {
    UDC_Device * privateData = (UDC_Device *) pD;

    if (!pD || !numOfFrame)
        return EINVAL;
// The CUSB2 copies the frame number into the frmnrl and frmnrh registers at every Start-Of-Frame packet. 
// The mfr[2:0] value is incremented by the CUSB2 hardware every microframe. These registers are read-only.
    *numOfFrame = CPS_UncachedRead16(&privateData->regs->frmnr);
    return 0;
}

static uint32_t sdudcWakeUp(void *pD) {
    if (!pD)
        return EINVAL;
    return ENOTSUP;
}

static uint32_t sdudcSetSelfPowered(void *pD) {
    UDC_Device * udcDev = (UDC_Device*) pD;

    if (!pD)
        return EINVAL;

    udcDev->isSelfPowered = 1;
    return 0;
}

static uint32_t sdudcClearSelfPowered(void *pD) {
    UDC_Device * udcDev = (UDC_Device*) pD;

    if (!pD)
        return EINVAL;
    udcDev->isSelfPowered = 0;
    return 0;
}

static uint32_t sdudcVbusSession(void *pD, uint8_t isActive) {
    /*For OTG device*/
    if (!pD) {
        return EINVAL;
    }
    return ENOTSUP;
}

static uint32_t sdudcVbusDraw(void *pD, uint8_t mA) {
    /*For OTG device*/
    if (!pD) {
        return EINVAL;
    }
    return ENOTSUP;
}

static uint32_t sdudcPullUp(void *pD, uint8_t isOn) {
    /*For OTG device*/
    if (!pD) {
        return EINVAL;
    }
    return ENOTSUP;
}

static uint32_t sdudcIoctl(void *pD, uint32_t code, uint32_t param) {
    if (!pD) {
        return EINVAL;
    }
    return ENOTSUP;
}

static void sdudcGetConfigParams(void *pD, CH9_ConfigParams *configParams) {
    /*Only for USB3 controller*/
    if (!pD) {
        return;
    }
    return;
}

static void sdudc_print_reg(void *pD)
{
    UDC_Device * udcDev = (UDC_Device*) pD;
    CPS_UncachedWrite8(&udcDev->regs->clkgate, 0x1 );
    // uint8_t *preg = udcDev->regs;
    // if (!pD)
    //     return EINVAL;
    // for(int i=0; i<sizeof(UCRegs); i++)
    // {
    //     printf("dev reg[0x%x]=0x%x \n", i, preg[i]);
    // }
}

static void sdudc_suspend(void* pD, uint8_t methord) {
    UDC_Device * udcDev = (UDC_Device*) pD;

    uint8_t *preg = (uint8_t *)udcDev->regs;
    printf("pre otgstate=0x%x \n", udcDev->regs->otgstate);
    printf("=================0x%x\n", *(uint32_t *)MAILBOX_WAKEUP);
    printf("after otgstate=0x%x \n", udcDev->regs->otgstate);
}

static void sdudc_resume(void* pD, uint8_t methord) {
    UDC_Device * udcDev = (UDC_Device*) pD;

    uint8_t *preg = (uint8_t *)udcDev->regs;
    printf("pre otgstate=0x%x \n", udcDev->regs->otgstate);

    printf("=================0x%x\n", *(uint32_t *)MAILBOX_WAKEUP);
    *(uint32_t *)MAILBOX_WAKEUP = 1;

    printf("after otgstate=0x%x \n", udcDev->regs->otgstate);
}

static void sdudc_reset(void* pD, uint8_t methord) {
    UDC_Device * udcDev = (UDC_Device*) pD;

    uint8_t *preg = (uint8_t *)udcDev->regs;
    printf("pre otgstate=0x%x \n", udcDev->regs->otgstate);

    printf("after otgstate=0x%x \n", udcDev->regs->otgstate);
}

static struct CUSBD_epOps sdudcEpOps = {
    .epEnable = sdudcEpEnable,
    .epDisable = sdudcEpDisable,
    .reqQueue = sdudcEpQueue,
    .reqDequeue = sdudcEpDequeue,
    .epSetHalt = sdudcEpSetHalt,
    .epSetWedge = sdudcEpSetWedge,
    .epFifoStatus = sdudcFifoStatus,
    .reqAlloc = sdudcEpAllocRequest,
    .reqFree = sdudcFreeRequest
};

static CUSBD_OBJ sdudcDrv = {
    .probe = sdudcProbe,
    .init = sdudcInit,
    .destroy = sdudcDestroy,
    .start = sdudcStart,
    .stop = sdudcStop,
    .isr = sdudcIsr,
    //endpoint operation
    .epEnable = sdudcEpEnable,
    .epDisable = sdudcEpDisable,
    .epSetHalt = sdudcEpSetHalt,
    .epSetWedge = sdudcEpSetWedge,
    .epFifoStatus = sdudcFifoStatus,
    .epFifoFlush = sdudcFifoFlush,
    .reqQueue = sdudcEpQueue,
    .reqDequeue = sdudcEpDequeue,
    .reqAlloc = sdudcEpAllocRequest,
    .reqFree = sdudcFreeRequest,

    //Device operations
    .getDevInstance = sdudcGetDevInstance,
    .dGetFrame = sdudcGetFrame,
    .dWakeUp = sdudcWakeUp,
    .dSetSelfpowered = sdudcSetSelfPowered,
    .dClearSelfpowered = sdudcClearSelfPowered,
    .dVbusSession = sdudcVbusSession,
    .dVbusDraw = sdudcVbusDraw,
    .dPullUp = sdudcPullUp,
    .dExecDebug = sdudcIoctl,
    .dGetConfigParams = sdudcGetConfigParams,
    .print_reg = sdudc_print_reg,
    .suspend  = sdudc_suspend,
    .resume  = sdudc_resume,
    .reset  = sdudc_reset,
};

CUSBD_OBJ * CUSBD_GetInstance(void) {
    return &sdudcDrv;
}

