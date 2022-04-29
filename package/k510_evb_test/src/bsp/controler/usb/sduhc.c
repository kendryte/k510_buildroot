/**********************************************************************
 * Copyright (C) 2014-2017 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sduhc.c
 * USB Embedded Host driver.
 *
 ***********************************************************************/

#include "cdn_string.h"
#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "log.h"
#include "cps.h"
#include "cdn_assert.h"

#include "cusbh_if.h"
#include "cusb_ch9.h"
#include "cusb_ch11.h"
#include "cusb_dma_if.h"

#include "sduhc_if.h"
#include "sduc_regs.h"

#include "sduc_list.h"
#include  "cusbd_if.h"
#if 0
#include "pcal6416.h"
#endif
#define DBG_CUSBH_ISR_MSG       0x01000000
#define DBG_CUSBH_INIT_EP_MSG   0x02000000
#define DBG_CUSBH_OTG_MSG       0x04000000
#define DBG_CUSBH_BASIC_MSG     0x08000000
#define DBG_CUSBH_VERBOSE_MSG   0x10000000
#define DBG_CUSBH_ERR_MSG       0x20000000
#define DBG_NO_SILENT           0x00000004
#define DBG_DMA_IRQ_MSG             0x00002000
/**
 * Functions defined in sduhcVHub.c file.
 */
extern uint32_t sduhcVHubStatusChangeData(void * pD, uint8_t *status);
extern uint32_t sduhcVHubClearPortFeature(UHC_Controller * pD, CH9_UsbSetup * setup);

/*These functions from CUSBD driver is not placed in CUSBD interface
 *  because are used only internally by CUSBH driver*/
extern uint32_t udcGetPrivateSize(void);
extern void sdudcCallbackTransfer(void * privateData, uint8_t epNum, uint8_t epDir);
extern uint8_t getMQPTestSrpFlag(void * privateData);
extern void clearMQPTestSrpFlag(void * privateData);

static void sduhcEpProgram(UHC_Controller * pD, UhcEp * hwEp,
        CUSBH_Req * usbReq, uintptr_t dmaBuff, uint32_t length);


/******************************************************************************
 * Private Driver functions and macros - list management
 *****************************************************************************/
static inline CUSBH_Req * sduhcListGetUsbRequestEntry(ListHead * list) {
    return (CUSBH_Req *) ((uintptr_t) list
        - (uintptr_t) &(((CUSBH_Req *) 0)->list));
}

static inline UhcHostEpPriv * listGetUsbHEpPrivEntry(ListHead * list) {
    /*if list empty*/
    if (list->next == list)
        return NULL;

    return (UhcHostEpPriv *) ((uintptr_t) list
        - (uintptr_t) &(((UhcHostEpPriv *) 0)->node));
}

/******************************************************************************
 * Private Driver functions and macros - Generic functions
 *****************************************************************************/

/**
 * Function clear and  disable all USB and OTG interrupts except
 * OTG IDLE IRQ. Function does not clear IDLE IRQ because firmware
 * need information about this interrupt to properly starts Device mode.
 */
static void sduhcGenericIrqDisable(UHC_Controller * pD) {

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "Disable USB Interrupts%s\n", " ");

    /* disable interrupts */
    CPS_UncachedWrite8(&pD->regs->otgien, 0x0);
    CPS_UncachedWrite8(&pD->regs->usbien, 0x0);
    CPS_UncachedWrite16(&pD->regs->txerrien, 0x0000);
    CPS_UncachedWrite16(&pD->regs->rxerrien, 0x0000);

    /*clearing all interrupt except OTG IDLE irq*/
    CPS_UncachedWrite8(&pD->regs->otgirq, 0xFE);
    CPS_UncachedWrite8(&pD->regs->usbirq, 0xFF);
    CPS_UncachedWrite16(&pD->regs->txerrirq, 0xFF);
    CPS_UncachedWrite16(&pD->regs->rxerrirq, 0xFF);
}

/**
 * Function return actually detected speed for root port.
 * This speed has been read from spedctrl SFR.
 */
CH9_UsbSpeed sduhcGetActualSpeed(UHC_Controller * pD) {
    uint8_t speed = CPS_UncachedRead8(&pD->regs->speedctrl);
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
 * Function returns textual form describing OTG state.
 */
char * sduhcDecodeOtgState(OtgState state) {
    switch (state) {
    case OTG_STATE_A_IDLE:
        return "A_IDLE";
    case OTG_STATE_A_WAIT_VRISE:
        return "A_WAIT_VRISE";
    case OTG_STATE_A_WAIT_BCON:
        return "A_WAIT_BCON";
    case OTG_STATE_A_HOST:
        return "A_HOST";
    case OTG_STATE_A_SUSPEND:
        return "A_SUSPEND";
    case OTG_STATE_A_PERIPHERAL:
        return "A_PERIPHERAL";
    case OTG_STATE_A_VBUS_ERR:
        return "A_VBUS_ERR";
    case OTG_STATE_A_WAIT_VFALL:
        return "A_WAIT_VFALL";
    case OTG_STATE_B_IDLE:
        return "B_IDLE";
    case OTG_STATE_B_PERIPHERAL:
        return "B_PERIPHERAL";
    case OTG_STATE_B_WAIT_ACON:
        return "B_WAIT_ACON";
    case OTG_STATE_B_HOST:
        return "B_HOST";
    case OTG_STATE_B_SRP_INT1:
        return "B_SRP_INT1";
    case OTG_STATE_B_SRP_INT2:
        return "B_SRP_INT1";
    case OTG_STATE_B_DISCHRG1:
        return "B_DISCHRG1";
    case OTG_STATE_B_DISCHRG2:
        return "B_DISCHRG2";
    case OTG_STATE_UNKNOWN:
    default:
        return "UNKNOWN";
    }
}

/**
 * Function Switch On or Switch Off VBUS depending on isOn parameter.
 */
void sduhcSetVbus(UHC_Controller * pD, uint8_t isOn) {
    uint8_t reg =CPS_UncachedRead8(&pD->regs->otgctrl);
    uint8_t otgstate = CPS_UncachedRead8(&pD->regs->otgstate);

    if (isOn) {
        if(!(reg & UCHM_OTGCTRL_BUSREQ) || (reg & UCHM_OTGCTRL_ABUSDROP)) {
            vDbgMsg(DBG_CUSBH_OTG_MSG, 1, "VBUS switching on %s\n", " ");
#if 1
            pcal6416_set_gpio_vbus_en(1);
#endif
            reg = CPS_UncachedRead8(&pD->regs->otgctrl);
            reg &= ~UCHM_OTGCTRL_ABUSDROP;
            reg |= UCHM_OTGCTRL_BUSREQ;
            CPS_UncachedWrite8(&pD->regs->otgctrl, reg);
        }

        switch(otgstate) {
            default:
            pD->otgState = OTG_STATE_A_WAIT_BCON;
        }
    } else {
        if((reg & UCHM_OTGCTRL_BUSREQ) || !(reg & UCHM_OTGCTRL_ABUSDROP)) {
            vDbgMsg(DBG_CUSBH_OTG_MSG, 1, "VBUS switching off %s\n", " ");
#if 1
            pcal6416_set_gpio_vbus_en(0);
#endif
            reg |= UCHM_OTGCTRL_ABUSDROP;
            reg &= ~UCHM_OTGCTRL_BUSREQ;
            CPS_UncachedWrite8(&pD->regs->otgctrl, reg);
        }

        switch(otgstate) {
            default:
            pD->otgState = OTG_STATE_A_IDLE;
        }
    }
}

/**
 * Function displays basic information about hardware USB endpoint
 */
#ifdef DEBUG
static void sduhcEndpointInformation(UHC_Controller *pD, UhcEp * hwEp) {
    char * add = NULL;
    if (hwEp->state == EP_NOT_IMPLEMENTED) {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "Hardware  hcep-%d %s is not supported \n",
                hwEp->hwEpNum, (hwEp->isInEp ? "IN" : "OUT"));
        return;
    }

    switch (hwEp->hwEpNum) {
    case UHC_GENERIC_EP_CONTROLL:
        add = " - This endpoint is reserved only for CONTROLL transfer";
        break;
    case UHC_GENERIC_EP_BULK:
        add = " - This endpoint is reserved only for BULK transfer";
        break;
    case UHC_GENERIC_EP_INT:
        add = " - This endpoint is reserved only for INTERRUPT transfer";
        break;
    case UHC_GENERIC_EP_ISOC:
        add = " - This endpoint is reserved only for ISOC transfer";
        break;
    default:
        add = " ";
    }

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1,
            "Hardware hcep-%d %s (hwMaxPacet: %d, hwBuffers: %d) is supported %s\n",
            hwEp->hwEpNum, (hwEp->isInEp ? "IN" : "OUT"), hwEp->hwMaxPacketSize,
            hwEp->hwBuffers, add);
}

#else
 static void sduhcEndpointInformation(UHC_Controller *pD, UhcEp * hwEp) { return; }
#endif 

/**
 * Function initializes USB endpoints for USB controller
 */
static uint32_t sduhcCoreInitEndpoints(UHC_Controller * pD) {
    uint8_t epNum;

    pD->hwEpInCount = 0;
    pD->hwEpOutCount = 0;

    CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | 0);
    CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | UCM_FIFOCTRL_IO_TX | 0);

    /* discover endpoint configuration */
    for (epNum = 0; epNum < 16; epNum++) {
        UhcEp * hwEp = pD->in + epNum;
        hwEp->isInEp = 1;
        hwEp->hwEpNum = epNum;
        if (pD->usbHostCfg.epIN[epNum].bufferingValue) {
            hwEp->hwMaxPacketSize = pD->usbHostCfg.epIN[epNum].maxPacketSize;
            hwEp->hwBuffers = pD->usbHostCfg.epIN[epNum].bufferingValue;
            hwEp->state = EP_FREE;
            hwEp->channel = NULL;
            pD->hwEpInCount++;
            /*Maybe this should be moved to new function initializing endpoints*/
            if (epNum != 0) {
                CPS_UncachedWrite16(&pD->regs->rxstaddr[epNum - 1].addr,
                        le16ToCpu(pD->usbHostCfg.epIN[epNum].startBuf) );
                /*Disable endpoint*/
                CPS_UncachedWrite8(&pD->regs->ep[epNum - 1].rxcon, 0x08);
                CPS_UncachedWrite8(&pD->regs->fifoctrl,
                        UCM_FIFOCTRL_FIFOAUTO | epNum);
            }
        } else
            hwEp->state = EP_NOT_IMPLEMENTED;

        sduhcEndpointInformation(pD, hwEp);

        hwEp = pD->out + epNum;
        hwEp->isInEp = 0;

        hwEp->hwEpNum = epNum;
        if (pD->usbHostCfg.epOUT[epNum].bufferingValue) {
            hwEp->hwMaxPacketSize = pD->usbHostCfg.epOUT[epNum].maxPacketSize;
            hwEp->hwBuffers = pD->usbHostCfg.epOUT[epNum].bufferingValue;
            hwEp->state = EP_FREE;
            hwEp->channel = NULL;
            pD->hwEpOutCount++;
            /*Maybe this should be moved to new function initializing endpoints*/
            if (epNum != 0) {
                CPS_UncachedWrite16(&pD->regs->txstaddr[epNum - 1].addr,
                        le16ToCpu(pD->usbHostCfg.epIN[epNum].startBuf) );
                /*Disable endpoint*/
                CPS_UncachedWrite8(&pD->regs->ep[epNum - 1].txcon, 0x08);
                CPS_UncachedWrite8(&pD->regs->fifoctrl,
                        UCM_FIFOCTRL_FIFOAUTO | UCM_FIFOCTRL_IO_TX | epNum);
            }
        } else
            hwEp->state = EP_NOT_IMPLEMENTED;

        sduhcEndpointInformation(pD, hwEp);
    }
    return 0;
}

/**
 * Function initializes USB controller
 */
static uint32_t sduhcInitController(UHC_Controller * pD) {
    uint32_t retval;

    pD->vBusErrCnt =0;
    listInit(&pD->bulkInHEpQueue);
    listInit(&pD->bulkOutHEpQueue);
    listInit(&pD->ctrlHEpQueue);
    listInit(&pD->intInHEpQueue);
    listInit(&pD->intOutHEpQueue);
    listInit(&pD->isoInHEpQueue);
    listInit(&pD->isoOutHEpQueue);

    /*Disable VBUS*/
    CPS_UncachedWrite8(&pD->regs->otgctrl, UCHM_OTGCTRL_ABUSDROP);

    /*setting default maxpacket size for EP0*/
    CPS_UncachedWrite8(&pD->regs->ep0maxpack, 0x40);

    sduhcGenericIrqDisable(pD);

    /* In this place it is possible to change
       timeout settings used by OTG. Controller has set
       default values but this settings can be changed*/
#if 0
    CPS_UncachedWrite8(&pD->regs->taaidlbdis, 0x19);
    CPS_UncachedWrite8(&pD->regs->tbvbusdispls, 0x0);
    CPS_UncachedWrite8(&pD->regs->tawaitbcon, 0x80);
    CPS_UncachedWrite8(&pD->regs->tbvbuspls, 0x0A);
#else
    CPS_UncachedWrite8(&pD->regs->tawaitbcon, 0x80);  /*4,47s*/
#endif



    /* setup Cadence Controller parts of the core */
    retval = sduhcCoreInitEndpoints(pD);
    if (retval != 0) {
        return retval;
    }

    pD->otgState = OTG_STATE_B_IDLE;

    /*Reset all USB endpoints*/
    CPS_UncachedWrite8(&pD->regs->endprst, UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST
            | UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST);

    return retval;
}

/**
 * Based on CUSBH configuration function prepares configuration for initializing CUSBD component
 */
static void sduhcPrepareDeviceConfig(const CUSBH_Config * hostConfig,
        CUSBD_Config * deviceConfig) {
    uint8_t i = 0;

    /*Copy data from host*/
    deviceConfig->dmaSupport = hostConfig->dmaSupport;
    deviceConfig->dmultEnabled = hostConfig->dmultEnabled;
    deviceConfig->isOtg = hostConfig->isOtg;
    deviceConfig->isDevice = hostConfig->isDevice;
    deviceConfig->isEmbeddedHost = hostConfig->isEmbeddedHost;
    deviceConfig->regBase = hostConfig->regBase;
    deviceConfig->dmaInterfaceWidth = CUSBD_DMA_32_WIDTH;
    deviceConfig->trbAddr = hostConfig->trbAddr;
    deviceConfig->trbDmaAddr = hostConfig->trbDmaAddr;
    for (i = 0; i < 16; i++) {
        deviceConfig->epIN[i].bufferingValue =
                hostConfig->epOUT[i].bufferingValue;
        deviceConfig->epIN[i].maxPacketSize =
                hostConfig->epOUT[i].maxPacketSize;
        deviceConfig->epIN[i].startBuf = hostConfig->epOUT[i].startBuf;

        deviceConfig->epOUT[i].bufferingValue =
                hostConfig->epIN[i].bufferingValue;
        deviceConfig->epOUT[i].maxPacketSize =
                hostConfig->epIN[i].maxPacketSize;
        deviceConfig->epOUT[i].startBuf = hostConfig->epIN[i].startBuf;
    }
}

/**
 * Function is called when OTG FSM enter to PERIPHERAL state, and
 * call start() function from CUSBD component if device is not started yet
 */
static void sduhcDeviceStart(UHC_Controller * pD) {

    uint8_t regs = CPS_UncachedRead8(&pD->regs->otgstate);
    uint8_t speed;

    /*Disable VBUS*/
    if(regs == OTG_STATE_A_PERIPHERAL)
        sduhcSetVbus(pD, 1);
    else
        sduhcSetVbus(pD, 0);

    /*Reset USB Device*/
    if(pD->usbDeviceReadyToWork == 0) {
        pD->usbDevDrv->start(pD->usbDeviceController);
    }
    pD->isRemoteWakeup =0;
    pD->isSelfPowered =0;

    speed = sduhcGetActualSpeed(pD);
    pD->speed = (speed == CH9_USB_SPEED_HIGH) ? CH9_USB_SPEED_HIGH : CH9_USB_SPEED_FULL;

    pD->ep0State = UHC_EP0_STAGE_IDLE;

    switch(regs) {
        case OTG_STATE_B_PERIPHERAL:
            pD->otgState = OTG_STATE_B_PERIPHERAL;
            break;
        case OTG_STATE_A_PERIPHERAL:
            pD->otgState = OTG_STATE_A_PERIPHERAL;
            break;
        case OTG_STATE_A_IDLE:
        case OTG_STATE_A_WAIT_BCON:
            pD->otgState = OTG_STATE_A_IDLE;
            break;
        case OTG_STATE_B_IDLE:
            pD->otgState = OTG_STATE_B_IDLE;
            break;
        default:
            vDbgMsg(DBG_CUSBH_ERR_MSG,  1, "Not recognized state %s\n", " ");
    }
}
/******************************************************************************
 * Private Driver functions and macros - management transfers
 *****************************************************************************/
/**
 * Function gets next CUSBH_Req object queued for usbHEp object.
 */
static CUSBH_Req * sduhcGetNextReq(CUSBH_Ep * usbHEp) {
    ListHead *queue;

    if (!usbHEp)
        return NULL;
    queue = (ListHead*)&usbHEp->reqList;

    //if list empty
    if (queue == queue->next)
        return NULL;

    return sduhcListGetUsbRequestEntry(queue->next);
}

/**
 * Function inform upper layer (user application) about properly completion
 * USB transfer or about error.
 */
static void sduhcGivbackRequest(UHC_Controller *pD, CUSBH_Req *usbReq,
        uint32_t status) {

    /*delete usbReq entry from list*/
    listDelete((ListHead*)&usbReq->list);

    if (usbReq->status == EINPROGRESS) {
        /*Status for Ep0*/
        usbReq->status = status;
    }

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1,
            "Complete usbRequest: %p (status: %d/%d), dev%d ep%d%s, %d/%d\n",
            usbReq, usbReq->status, status, usbReq->faddress, usbReq->epNum,
            usbReq->epIsIn ? "in" : "out", usbReq->actualLength,
            usbReq->buffLength);

    if(pD->usbHostCallback.givbackRequest)
        pD->usbHostCallback.givbackRequest(pD, usbReq, status);
}

/**
 *  Function responsible for preparing SETUP Stage for Control Transfer
 */
static void sduchStartReqControl(UHC_Controller * pD, CUSBH_Ep * usbHEp) {
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;
    CUSBH_Req * usbReq = sduhcGetNextReq(usbHEp);
    UhcEp * hwEp = usbHEpPriv->genericHwEp;
    uintptr_t  dmaBuff = 0;
    uint32_t length;

    assert(usbReq);

    usbHEpPriv->currentHwEp = hwEp;
    hwEp->scheduledUsbHEp = usbHEp;

    /*For control transfer we also assign usbHEp for IN direction*/
    pD->in[UHC_GENERIC_EP_CONTROLL].scheduledUsbHEp = usbHEp;

    pD->ep0State = UHC_EP0_STAGE_SETUP;

    dmaBuff = usbReq->setupDma;

    length = 8;

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1,
        "CONTROL transfer (setup packet): %02x %02x %02x %02x %02x %02x %02x %02x \n ",
        ((uint8_t* )usbReq->setup)[0], ((uint8_t* )usbReq->setup)[1],
        ((uint8_t* )usbReq->setup)[2], ((uint8_t* )usbReq->setup)[3],
        ((uint8_t* )usbReq->setup)[4], ((uint8_t* )usbReq->setup)[5],
        ((uint8_t* )usbReq->setup)[6], ((uint8_t* )usbReq->setup)[7]);

    sduhcEpProgram(pD, hwEp, usbReq, dmaBuff, length);
}

/**
 * Function update time for all queued Interrupt transfer.
 */
static void sduhcUpdateTimeInterruptTransfer(ListHead * head, UhcHostEpPriv * lastFinished) {
    ListHead * listEntry = NULL;
    UhcHostEpPriv * usbHEpPriv = NULL;
    uint16_t time = lastFinished->frame;

    for (listEntry = head->next; listEntry != head; listEntry =
            listEntry->next) {
        usbHEpPriv = listGetUsbHEpPrivEntry(listEntry);

        assert(usbHEpPriv!=NULL);

        if(usbHEpPriv == lastFinished) {
            lastFinished->frame = lastFinished->interval;
            continue;
        }

        if(time ==0) {
            return;
        }

        if(usbHEpPriv->frame < time ) {
            usbHEpPriv->frame = 0; /*this will be send with high priority in next transfer*/
        } else
            usbHEpPriv->frame -= time;
    }

    return;
}

/**
 * Function find UhcHostEpPriv object for which Interrupt transfer should be
 * armed as the first.
 */
static UhcHostEpPriv * sduhcFindFirstInterruptTransfer(ListHead * head) {
    ListHead * listEntry = NULL;
    UhcHostEpPriv * usbHEpPrivTest = NULL;
    UhcHostEpPriv * usbHEpPrivActual = NULL;

    for (listEntry = head->next; listEntry != head; listEntry =
            listEntry->next) {
        usbHEpPrivTest = listGetUsbHEpPrivEntry(listEntry);

        assert(usbHEpPrivTest!=NULL);

        if (!usbHEpPrivActual) {
            usbHEpPrivActual = usbHEpPrivTest;
        }
        if (usbHEpPrivTest->frame < usbHEpPrivActual->frame) {
            usbHEpPrivActual = usbHEpPrivTest;
        }
    }

    if (usbHEpPrivActual) {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
            "Chosen usbHEpPri addr/epnum/addr/frame - %p//%x/%x/%x \n",
            usbHEpPrivTest, usbHEpPrivTest->epNum, usbHEpPrivTest->faddress,
            usbHEpPrivTest->frame);

    } else {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "Queue empty %s\n", " ");
    }
    return usbHEpPrivActual;
}

/**
 *  Function responsible for preparing Interrupt Transfer
 */
static void sduchStartReqInterrupt(UHC_Controller * pD, CUSBH_Ep * usbHEp) {
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;
    CUSBH_Req * usbReq = sduhcGetNextReq(usbHEp);
    UhcEp * hwEp = usbHEpPriv->genericHwEp;
    uintptr_t  dmaBuff = 0;
    uint32_t length = 0;

    assert(usbReq!=NULL);

    dmaBuff = usbReq->buffDma + usbReq->actualLength;
    length = usbReq->buffLength - usbReq->actualLength;

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
        "Queued usbReq %p usbDev%d ep%d%s-INTERRUPT, hwEp %d, DmaBuffer: 0x%lx DataLength: %d\n",
        usbReq, usbReq->usbDev->devnum, usbHEpPriv->epNum,
        usbHEpPriv->isIn ? "in" : "out", (usbHEpPriv->currentHwEp) ? usbHEpPriv->currentHwEp->hwEpNum : 0,
        dmaBuff, length);

    /*
     * If hardware endpoint has assigned host endpoint it indicate that transfer has been started
     */
    if (hwEp->scheduledUsbHEp) {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
            "Transmission already started usbHEpPriv %p faddress %x\n",
            usbHEpPriv, usbHEpPriv->faddress);
        return;
    }

    /*Firmware not reconfigure transfer which is scheduled for transfer.
     * It means that new added transfer will have been taken into consideration
     *  after finishing actually prepared transfer */

    /*Select the best transfer to starts */
    if (usbHEpPriv->isIn)
        usbHEpPriv = sduhcFindFirstInterruptTransfer(&pD->intInHEpQueue);
    else
        usbHEpPriv = sduhcFindFirstInterruptTransfer(&pD->intOutHEpQueue);

    /*retrieves USB host endpoint associated with usbHEpPriv*/
    usbHEp = usbHEpPriv->usbHEp;

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
        "chosen usbHEpPriv: %p frame 0x%x, epnum 0x%x faddress 0x%x, HwFrame 0x%x \n",
        usbHEpPriv, usbHEpPriv->frame, usbHEpPriv->epNum,
        usbHEpPriv->faddress, CPS_UncachedRead16(&pD->regs->frmnr));

    usbHEpPriv->currentHwEp = hwEp;
    hwEp->scheduledUsbHEp = usbHEp;

    usbReq = sduhcGetNextReq(usbHEp);
    dmaBuff = usbReq->buffDma + usbReq->actualLength;
    length = usbReq->buffLength - usbReq->actualLength;
    sduhcEpProgram(pD, hwEp, usbReq, dmaBuff, length);
    return;
}

/**
 *  Function responsible for preparing BULK Transfer
 */
static void sduchStartReqBulk(UHC_Controller * pD, CUSBH_Ep * usbHEp) {
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;
    CUSBH_Req * usbReq = sduhcGetNextReq(usbHEp);
    UhcEp * hwEp = usbHEpPriv->genericHwEp;
    uintptr_t dmaBuff = 0;
    uint32_t length;

    usbHEpPriv->currentHwEp = hwEp;
    hwEp->scheduledUsbHEp = usbHEp;

    assert(usbReq!=NULL);

    dmaBuff = usbReq->buffDma + usbReq->actualLength;
    length = usbReq->buffLength - usbReq->actualLength;

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
        "usbReq %p usbDev%d ep%d%s-BULK, hwEp %d, DmaBuffer: 0x%lx DataLength: %d\n",
        usbReq, usbReq->usbDev->devnum, usbHEpPriv->epNum,
        usbHEpPriv->isIn ? "in" : "out", usbHEpPriv->currentHwEp->hwEpNum,
        dmaBuff, length);

    sduhcEpProgram(pD, hwEp, usbReq, dmaBuff, length);
}

/**
 *  Function responsible for preparing isochronous Transfer
 */
static void sduhcStartReqIsoc(UHC_Controller * pD, CUSBH_Req * usbReq) {
    CUSBH_Ep *usbHEp = (CUSBH_Ep*)usbReq->hcPriv;
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;
    UhcEp * hwEp = usbHEpPriv->genericHwEp;
    uintptr_t dmaBuff = 0;
    uint32_t length = 0;

    dmaBuff = usbReq->buffDma + usbReq->actualLength;
    length = usbReq->buffLength - usbReq->actualLength;

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
        "usbReq %p usbDev%d ep%d%s-ISOC, hwEp %d, DmaBuffer: 0x%lx DataLength: %d\n",
        usbReq, usbReq->usbDev->devnum, usbHEpPriv->epNum,
        usbHEpPriv->isIn ? "in" : "out", (usbHEpPriv->currentHwEp) ? usbHEpPriv->currentHwEp->hwEpNum : 0,
        dmaBuff, length);

    usbHEpPriv->currentHwEp = hwEp;
    hwEp->scheduledUsbHEp = usbHEp;

    sduhcEpProgram(pD, hwEp, usbReq, dmaBuff, length);
    return;
}


/**
 * Function calls appropriately function for specific transfer type.
 */
static void sduhcStartReq(UHC_Controller * pD, CUSBH_Req * usbReq) {
    CUSBH_Ep *usbHEp = (CUSBH_Ep*)usbReq->hcPriv;
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;

    usbHEpPriv->genericHwEp->state = EP_BUSY;

    switch (usbHEpPriv->type) {
    case CH9_USB_EP_CONTROL:
        sduchStartReqControl(pD, usbHEp);
        break;
    case CH9_USB_EP_ISOCHRONOUS:
        sduhcStartReqIsoc(pD, usbReq);
        break;
    case CH9_USB_EP_BULK:
        sduchStartReqBulk(pD, usbHEp);
        break;
    case CH9_USB_EP_INTERRUPT:
        sduchStartReqInterrupt(pD, usbHEp);
        break;
    }
    return;
}

/**
 * Waits for clearing busy bit. Firmware has to has empty on-chip buffers
 * in order to could read or set toggle bit.
 */
static uint32_t sduhcWaitForBusyBit(UHC_Controller * pD, UhcEp *hwEp) {
    UCRegs *regs = pD->regs;
    volatile uint8_t *csReg = 0;
    uint8_t val = UCM_CS_BUSY;
    uint8_t buf =0;
    uint8_t bufflag = 0;
    uint8_t flag=UCM_CS_BUSY;
    uint8_t otgChangeDetection;

    if (!hwEp->isInEp) {
        if(hwEp->hwEpNum == 0) {
            csReg = &regs->ep0cs;
            flag = UCM_EP0CS_TXBSY_MSK;
            buf=0;
        } else {
            csReg = &regs->ep[hwEp->hwEpNum-1].txcs;
            buf= CPS_UncachedRead8(&regs->ep[hwEp->hwEpNum-1].txcon)  & UCM_CON_BUF;
        }
    } else {
        return 0;
    }

    while((val & flag) || (bufflag == 0) ) {
        otgChangeDetection = CPS_UncachedRead8(&regs->otgstate);
        val = CPS_UncachedRead8(csReg);

        if(((val & UCM_CS_NPAK) >>  UCO_CS_NPAK) == buf || buf == 0)
            bufflag =1;
        else
            bufflag =0;

        if(otgChangeDetection != OTG_STATE_B_HOST &&  otgChangeDetection != OTG_STATE_A_HOST) {
            pD->ep0State = UHC_EP0_STAGE_IDLE;
            return UHC_ESHUTDOWN;
        }
    }

    return 0;
}

/**
 * Function responsible for finishing previous USB transfer,
 * calls callback function to inform user application about finishing
 * and also prepare next USB queued transfer.
 */
static void sduhcScheduleNextTransfer(UHC_Controller *pD, CUSBH_Req *usbReq,
        UhcEp *hwEp) {
    CUSBH_Ep * usbHEp = hwEp->scheduledUsbHEp;
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv *) usbHEp->hcPriv;
    uint32_t status;

    status = (usbReq->status == EINPROGRESS) ? 0 : usbReq->status;

    switch (usbHEpPriv->type) {
    /*For Bulk and INT endpoints we have to save current Toggle Bit status*/
    case CH9_USB_EP_BULK:
    case CH9_USB_EP_INTERRUPT: {
        uint8_t toggle;
        uint8_t result;

        /*save toggle bit for finished transmission*/
        if (hwEp->isInEp) {
            CPS_UncachedWrite8(&pD->regs->endprst, hwEp->hwEpNum);
            toggle = (CPS_UncachedRead8(&pD->regs->endprst)
                    & UCM_ENDPRST_TOGSETQ) ? 1 : 0;
            if(pD->usbHostCallback.setEpToggle) {
                pD->usbHostCallback.setEpToggle(pD, usbReq->usbDev,
                    usbHEpPriv->epNum, usbHEpPriv->isIn, toggle);
            } else {
                vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function getEpToggle not assigned%s\n", "");
            }
        } else {
            result = sduhcWaitForBusyBit(pD, hwEp);
            if(result > 0) {
                usbReq->status = UHC_ESHUTDOWN;
                return;
            }

            CPS_UncachedWrite8(&pD->regs->endprst,
                    hwEp->hwEpNum | UCM_ENDPRST_IO_TX);
            toggle = (CPS_UncachedRead8(&pD->regs->endprst)
                    & UCM_ENDPRST_TOGSETQ) ? 1 : 0;
            if(pD->usbHostCallback.setEpToggle) {
                pD->usbHostCallback.setEpToggle(pD, usbReq->usbDev,
                    usbHEpPriv->epNum, usbHEpPriv->isIn, toggle);
            } else {
                vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function getEpToggle not assigned%s\n", "");
            }
        }
        break;
    }
    case CH9_USB_EP_ISOCHRONOUS:
        break;
    }

    /*Return information to upper layer if transfer has been finished */
    if(usbHEpPriv->transferFinished) {
        sduhcGivbackRequest(pD, usbReq, status);
    }

    /*check if all request for host endpoint was handled*/
    if (usbHEp->reqList.next == &usbHEp->reqList) {
        ListHead * next;

        /*Because EP0 has always two EP0In end Ep0Out endpoint dedicated so firmware
         * always should set EP_ALLOCATED state. For ep0 genericHwEp will be set to pD->out[0] but
         * hwEp can be equal pD->out[0] or pD->in[0] and both should be treated as genericHwEp */
        if(usbHEpPriv->type == CH9_USB_EP_CONTROL) {
            hwEp->state = EP_ALLOCATED;
        } else {
            /*If used hw endpoint is generic endpoint then it is dedicated
             * and should not be set as EP_FREE*/
            if (usbHEpPriv->genericHwEp == hwEp)
                hwEp->state = EP_ALLOCATED;
            else
                hwEp->state = EP_FREE;
        }

        usbHEpPriv->epIsReady = 0;
        usbHEpPriv->currentHwEp = NULL;
        hwEp->scheduledUsbHEp = NULL;

        /*Release DMA channel because all transfer for this hostEndpoint has been finished*/
        if(hwEp->channel) {
            pD->dmaDrv->channelRelease(pD->dmaController, hwEp->channel);
            hwEp->channel = NULL;
        }

        switch (usbHEpPriv->type) {
        case CH9_USB_EP_CONTROL:
        case CH9_USB_EP_BULK:
            next = usbHEpPriv->node.prev;
            listDelete(&usbHEpPriv->node);
            /*if list not empty*/
            usbHEpPriv = listGetUsbHEpPrivEntry(next);
            break;
        case CH9_USB_EP_ISOCHRONOUS:
            //usbHEpPriv->isocEpConfigured = 1;
            next = usbHEpPriv->node.prev;
            listDelete(&usbHEpPriv->node);
            /*if list not empty*/
            usbHEpPriv = listGetUsbHEpPrivEntry(next);
            break;
        case CH9_USB_EP_INTERRUPT:
            next = usbHEpPriv->node.prev;
            listDelete(&usbHEpPriv->node);
            /*if list not empty*/
            usbHEpPriv = listGetUsbHEpPrivEntry(next);
            break;
        }
    } else {
        if(usbHEpPriv->type == CH9_USB_EP_INTERRUPT) {
            /*Free endpoint assigned for previous HEpPriv*/
            /*It will be scheduled again*/
            usbHEpPriv->currentHwEp = NULL;
            hwEp->scheduledUsbHEp = NULL;
        }
        if(usbHEpPriv->type == CH9_USB_EP_ISOCHRONOUS) {
            /**
             * For ISOC transfers, requests are linked in DMA modules so firmware doesn't
             * have to arm next transfer for selected endpoint. Also assumption of
             * firmware is that one hardware endpoint can handles only one ISOC endpoint.
             * So if device has 3 ISOC endpoint then host has to reserved 3 separate
             * endpoints for handling device.
             */
            return;
        }
    }

    if (usbHEpPriv) {
        usbHEp =  usbHEpPriv->usbHEp;
        sduhcStartReq(pD, sduhcGetNextReq(usbHEp));
    } else {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "There are no more packet to send%s\n", " ");
    }
}

/**
 * Function prepare hardware endpoint to transfer data end call
 * DMA function responsible for arming DMA transfer
 */
static void sduhcEpProgram(UHC_Controller * pD, UhcEp * hwEp,
        CUSBH_Req * usbReq, uintptr_t dmaBuff, uint32_t length) {
    CUSBH_Ep * usbHEp = hwEp->scheduledUsbHEp;
    UhcHostEpPriv * usbEpPriv = (UhcHostEpPriv *) usbHEp->hcPriv;
    UCRegs * regs = pD->regs;
    uint8_t regCon = 0;
    uint32_t result;
    uint32_t errIrqEn = 0;
    uint32_t errIrqMask = 0;
    uint32_t chMaxLen =0;


    /* candidate for DMA */
    if (!hwEp->channel) {
        hwEp->channel = pD->dmaDrv->channelAlloc(pD->dmaController,
                !hwEp->isInEp, hwEp->hwEpNum, (usbEpPriv->type == CH9_USB_EP_ISOCHRONOUS)? 1 : 0);
    }

    chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController,
            hwEp->channel);

    if(usbReq->buffLength > chMaxLen)
        length =  chMaxLen;

    switch (usbEpPriv->type) {
    case CH9_USB_EP_CONTROL:
        regCon = 0;
        break;
    case CH9_USB_EP_BULK:
        regCon = UCM_CON_TYPE_BULK;
        break;
    case CH9_USB_EP_INTERRUPT:
        regCon = UCM_CON_TYPE_INT;
        break;
    case CH9_USB_EP_ISOCHRONOUS:
        /**
         * if epIsReady is set then endpoint was started early. In this case
         * firmware doesn't have to configure endpoint again.
         * In this case firmware just add next transfer for started DMA channel
         */
        if (usbEpPriv->isocEpConfigured ) {
            goto dma_program;
        }
        usbEpPriv->isocEpConfigured =1;
        regCon = UCM_CON_TYPE_ISOC;
        switch (le16ToCpu(usbHEp->epDesc.wMaxPacketSize) >> 11) {
        case 0:
            regCon |= UCM_CON_1_ISOD;
            pD->dmaDrv->setMaxLength(pD->dmaController,
                hwEp->channel, usbEpPriv->maxPacketSize);
            break;
        case 1:
            pD->dmaDrv->setMaxLength(pD->dmaController,
                hwEp->channel, 2*1024);
            regCon |= UCM_CON_2_ISOD;
            break;
        case 2:
            pD->dmaDrv->setMaxLength(pD->dmaController,
                hwEp->channel, 3*1024);
            regCon |= UCM_CON_3_ISOD;
            break;
        }
        break;
    }

    /*Wait for OUT BUSY*/
    if(usbEpPriv->type != CH9_USB_EP_ISOCHRONOUS) {
        result = sduhcWaitForBusyBit(pD, hwEp);
        if(result > 0) {
            usbReq->status = UHC_ESHUTDOWN;
            return;
        }
    }

    errIrqMask = 1 << hwEp->hwEpNum;
    /* OUT/transmit/EP0*/
    if (!hwEp->isInEp) {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
            "Initialize OUT endpoint - dev-ep: %d hw_ep: %d\n",
            usbEpPriv->epNum, hwEp->hwEpNum);

        if (hwEp->hwEpNum) {

            regCon |= hwEp->hwBuffers - 1;
            //buffering has to be set before fifo reset
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].txcon, regCon);

            if(usbEpPriv->type != CH9_USB_EP_ISOCHRONOUS) {
                if(pD->usbHostCallback.getEpToggle) {
                    if (pD->usbHostCallback.getEpToggle(pD, usbReq->usbDev,
                        usbEpPriv->epNum, 0)) {
                        CPS_UncachedWrite8(&regs->endprst,
                                hwEp->hwEpNum | UCM_ENDPRST_IO_TX);
                        CPS_UncachedWrite8(&regs->endprst,
                                hwEp->hwEpNum | UCM_ENDPRST_TOGSETQ
                                        | UCM_ENDPRST_IO_TX | UCM_ENDPRST_FIFORST);
                    } else {
                        CPS_UncachedWrite8(&regs->endprst,
                                hwEp->hwEpNum | UCM_ENDPRST_IO_TX);
                        CPS_UncachedWrite8(&regs->endprst,
                                hwEp->hwEpNum | UCM_ENDPRST_TOGRST
                                        | UCM_ENDPRST_IO_TX | UCM_ENDPRST_FIFORST);
                    }
                } else {
                    vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function getEpToggle not assigned%s\n", "");
                }
            }

            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].txcon,
                    regCon | UCM_CON_VAL);
            CPS_UncachedWrite16(&regs->txmaxpack[hwEp->hwEpNum - 1],
                    usbEpPriv->maxPacketSize);
            CPS_UncachedWrite8(&regs->epExt[hwEp->hwEpNum - 1].txctrl,
                    usbEpPriv->epNum);
            CPS_UncachedWrite8(&regs->fnaddr, usbEpPriv->faddress);

            /*Only for Interrupt transfer (for other kind of transfer this line is meaningless) */
            CPS_UncachedWrite32(&regs->txsoftimer[hwEp->hwEpNum], usbEpPriv->frame);

        } else {
            CPS_UncachedWrite8(&regs->fnaddr, usbEpPriv->faddress);
            CPS_UncachedWrite8(&regs->ep0maxpack, usbEpPriv->maxPacketSize);
            CPS_UncachedWrite8(&regs->ep0ctrl, usbEpPriv->epNum);
            if (pD->ep0State == UHC_EP0_STAGE_SETUP) {
                uint8_t ep0cs = CPS_UncachedRead8(&regs->ep0cs);
                ep0cs |= UCHM_EP0CS_HCSET;
                CPS_UncachedWrite8(&regs->ep0cs, ep0cs);
            }
        }

        CPS_UncachedWrite16(&regs->txerrirq, errIrqMask);
        errIrqEn = CPS_UncachedRead16(&regs->txerrien);
        errIrqEn |= errIrqMask;
        CPS_UncachedWrite16(&regs->txerrien, errIrqEn);

        /* IN/receive */
    } else {
        if (hwEp->hwEpNum) {
            /*Endpoint should be disabled VAL =0*/
            vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
                "Initialize IN endpoint - dev-ep: %d hw_ep: %d\n",
                usbEpPriv->epNum, hwEp->hwEpNum);

            regCon |= hwEp->hwBuffers - 1;
            //buffering has to be set before fifo reset
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcon,
                                regCon);
            /*Restore Toggle bit */
            if(usbEpPriv->type != CH9_USB_EP_ISOCHRONOUS) {
                if(pD->usbHostCallback.getEpToggle) {
                    if (pD->usbHostCallback.getEpToggle(pD, usbReq->usbDev,
                        usbEpPriv->epNum, 1)) {
                        CPS_UncachedWrite8(&regs->endprst, hwEp->hwEpNum);
                        CPS_UncachedWrite8(&regs->endprst,
                        hwEp->hwEpNum | UCM_ENDPRST_TOGSETQ
                                | UCM_ENDPRST_FIFORST);
                    } else {
                        CPS_UncachedWrite8(&regs->endprst, hwEp->hwEpNum);
                        CPS_UncachedWrite8(&regs->endprst,
                        hwEp->hwEpNum | UCM_ENDPRST_TOGRST
                                | UCM_ENDPRST_FIFORST);
                    }
                } else {
                    vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function getEpToggle not assigned%s\n", "");
                }

            }

            CPS_UncachedWrite16(&regs->rxmaxpack[hwEp->hwEpNum - 1],
                    usbEpPriv->maxPacketSize);
            CPS_UncachedWrite8(&regs->epExt[hwEp->hwEpNum - 1].rxctrl,
                    usbEpPriv->epNum);
            CPS_UncachedWrite8(&regs->fnaddr, usbEpPriv->faddress);

            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcs, 1);
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcs, 1);
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcs, 1);
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcs, 1);

            /*Enable endpoint*/
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcon,
                                regCon | UCM_CON_VAL);

            /*Only for Interrupt transfer (for other kind of transfer this line is meaningless) */
            CPS_UncachedWrite32(&regs->rxsoftimer[hwEp->hwEpNum], usbEpPriv->frame);
        } else {
            CPS_UncachedWrite8(&regs->fnaddr, usbEpPriv->faddress);
            CPS_UncachedWrite8(&regs->ep0maxpack, usbEpPriv->maxPacketSize);
            CPS_UncachedWrite8(&regs->ep0ctrl, usbEpPriv->epNum);
            if (pD->ep0State == UHC_EP0_STAGE_IN
                    || pD->ep0State == UHC_EP0_STAGE_STATUSIN) {
                CPS_UncachedWrite8(&regs->ep0cs, UCHM_EP0CS_HCSETTOGGLE);
            }
        }

        CPS_UncachedWrite16(&regs->rxerrirq, errIrqMask);
        errIrqEn = CPS_UncachedRead16(&regs->rxerrien);
        errIrqEn |= errIrqMask;
        CPS_UncachedWrite16(&regs->rxerrien, errIrqEn);
    }

dma_program:
    result = pD->dmaDrv->channelProgram(pD->dmaController, hwEp->channel,
            usbEpPriv->maxPacketSize, dmaBuff, length,
            (void*)usbReq->isoFramesDesc, usbReq->isoFramesNumber);
    if (result) {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Error: channelProgram %s\n", " ");
        /*Disable error interrupt for hwEp endpoint */
        errIrqEn &= ~errIrqMask;
        if (!hwEp->isInEp) {
            if(hwEp->hwEpNum)
                CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].txcon, 0x08);
            CPS_UncachedWrite16(&regs->txerrien, errIrqEn);
        } else {
            if(hwEp->hwEpNum)
                CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcon, 0x08);
            CPS_UncachedWrite16(&regs->rxerrien, errIrqEn);
        }

        pD->dmaDrv->channelRelease(pD->dmaController, hwEp->channel);
        hwEp->channel = NULL;

    }
}

/**
 * Function decode error to form used by CUSBH.
 * Parameter code is code error red from USB SFR
 */
static uint32_t sduhcDecodeErrorCode(uint8_t code) {
    uint32_t status =0;
    switch (code) {
    case UCHV_ERR_NONE:
        status = 0;
        break;
    case UCHV_ERR_CRC:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "CRC Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    case UCHV_ERR_DATA_TOGGLE_MISMATCH:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Toggle Mismatch Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    case UCHV_ERR_STALL:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Stall Error%s\n", " ");
        status = UHC_ESTALL;
        break;
    case UCHV_ERR_TIMEOUT:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Timeout Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    case UCHV_ERR_PID:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "PID Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    case UCHV_ERR_TOO_LONG_PACKET:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "TO_LONG_PACKET Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    case UCHV_ERR_DATA_UNDERRUN:
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "UNDERRUN Error%s\n", " ");
        status = UHC_ESHUTDOWN;
        break;
    }
    return status;
}

/**
 * Abort transfer that is actually doing by hardware
 */
static int sduhcAbortActuallyUsbRequest(UHC_Controller * pD, CUSBH_Req *usbReq,
        CUSBH_Ep * usbHEp) {

    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv *) usbHEp->hcPriv;
    UhcEp * hwEp = usbHEpPriv->currentHwEp;
    UCRegs * regs;
    int status = 0;

    /*Flag inform that driver should finish this request
     * and call GivebackRequest callback*/
    usbHEpPriv->transferFinished =1;

    if (!pD)
        return EINVAL;

    regs = pD->regs;
    /*Flush fifo and disable error interrupt*/
    if(hwEp->isInEp) {
        CPS_UncachedWrite16(&pD->regs->rxerrien, (1 << 0));
        CPS_UncachedWrite8(&regs->endprst, UCM_ENDPRST_IO_TX | 0);
        CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_IO_TX);
    } else {
        CPS_UncachedWrite16(&pD->regs->txerrien, (1 << 0));
        CPS_UncachedWrite8(&pD->regs->endprst, hwEp->hwEpNum);
        CPS_UncachedWrite8(&pD->regs->endprst, UCM_ENDPRST_FIFORST | 0);
    }

    status = pD->dmaDrv->channelAbort(pD->dmaController, hwEp->channel);

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1,
        "abort hwEp: %s%d DMA for usbReq %p --> status: %d\n",
        hwEp->isInEp ? "IN" : "OUT", hwEp->hwEpNum, usbReq, status);
    usbReq->actualLength += pD->dmaDrv->getActualLength(pD->dmaController,
            hwEp->channel);

    /**
     *Sometimes driver release DMA channel despite the fact that request is still
     *in queue, so driver should always call this function.
    */
    sduhcScheduleNextTransfer(pD, usbReq, hwEp);
    return status;
}




/******************************************************************************
 * Private Driver functions and macros - Interrupts functions
 *****************************************************************************/

/**
 * Function called when USB transfer has been finished for EP0.
 */
static uint32_t sduhcHostEp0Irq(UHC_Controller *pD, uint8_t isIn) {

    CUSBH_Req * usbReq;
    uint8_t usbError = 0;
    UCRegs *regs = pD->regs;
    UhcEp * hwEp;
    CUSBH_Ep * usbHEp;
    UhcHostEpPriv * usbHEpPriv;
    uint32_t length;
    uintptr_t  dmaBuff;
    uint32_t status;

    hwEp = (isIn) ?
            &pD->in[UHC_GENERIC_EP_CONTROLL] :
            &pD->out[UHC_GENERIC_EP_CONTROLL];
    ;
    usbHEp = hwEp->scheduledUsbHEp;
    usbHEpPriv = (UhcHostEpPriv *) usbHEp->hcPriv;

    /* ep0 only has one queue, "in" */
    usbReq = sduhcGetNextReq(usbHEp);

    assert(usbReq!=NULL);

    status = sduhcWaitForBusyBit(pD, hwEp);
    if(status > 0) {
        usbReq->status = UHC_ESHUTDOWN;
        return 0;
    }

    usbError = isIn ? CPS_UncachedRead8(&regs->rx0err) :
        CPS_UncachedRead8(&regs->tx0err);
    usbError = (usbError & UCHM_ERR_TYPE) >> 2;

    length = pD->dmaDrv->getActualLength(pD->dmaController, hwEp->channel);
    pD->dmaDrv->channelRelease(pD->dmaController, hwEp->channel);
    hwEp->channel = NULL;

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
        "<==  usbHEp %p, count %d, usbReq %p, stage %d\n", usbHEp, length,
        usbReq, pD->ep0State);

    status = sduhcDecodeErrorCode(usbError);
    if (status) {
        usbReq->status = status;
        /*Clearing error interrupts in order to avoid handling this request in err interrupt
          If error occurs firmware can arise  interrupt for transaction - first from DMA and
          second from USB*/
        CPS_UncachedWrite16(&pD->regs->rxerrirq, 0x0001);
        CPS_UncachedWrite16(&pD->regs->txerrirq, 0x0001);
        /*Clear fifo for EP0)*/
        CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | 0 | 0x04 );
        CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | UCM_FIFOCTRL_IO_TX | 0 | 0x04);
    }

    if (usbReq->status != EINPROGRESS)
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Aborting%s\n", " ");

    if (usbReq->status == EINPROGRESS
            && pD->ep0State < UHC_EP0_STAGE_STATUSIN) {
        /* call common logic and prepare response */
        uint8_t nextStage = 0;

        switch (pD->ep0State) {
        case UHC_EP0_STAGE_IN:
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "EP0 Data IN finished%s\n", " ");
            usbHEpPriv->currentHwEp = &pD->out[UHC_GENERIC_EP_CONTROLL];
            pD->ep0State = UHC_EP0_STAGE_STATUSOUT;
            usbReq->actualLength = length;
            break;
        case UHC_EP0_STAGE_OUT:
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "EP0 Data OUT finished%s\n", " ");
            usbHEpPriv->currentHwEp = &pD->in[UHC_GENERIC_EP_CONTROLL];
            usbReq->actualLength = length;
            pD->ep0State = UHC_EP0_STAGE_STATUSIN;
            break;
        case UHC_EP0_STAGE_SETUP:
            if (!le16ToCpu(usbReq->setup->wLength)) {
                pD->ep0State = UHC_EP0_STAGE_STATUSIN;
                usbHEpPriv->currentHwEp = &pD->in[UHC_GENERIC_EP_CONTROLL];
                break;
            } else if (usbReq->setup->bmRequestType
                    & CH9_USB_DIR_DEVICE_TO_HOST) {
                pD->ep0State = UHC_EP0_STAGE_IN;
                usbHEpPriv->currentHwEp = &pD->in[UHC_GENERIC_EP_CONTROLL];
                nextStage = 1;
                if(pD->hsetPid0106 == 1) {
                    if(pD->hsetPid0106wait)
                        pD->hsetPid0106wait(15000);
                    pD->hsetPid0106 = 0;
                }
                break;
            } else {
                pD->ep0State = UHC_EP0_STAGE_OUT;
                /*usbHEpPriv->currentHwEp is the same as for SETUP Stage*/
                nextStage = 1;
            }
            break;
        default:
            vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Error Ep0 Stage %d\n", pD->ep0State);
            break;
        }

        if (nextStage) {
            /* control transfers always start with SETUP */
            length = usbReq->buffLength;
            dmaBuff = usbReq->buffDma;

            sduhcEpProgram(pD, usbHEpPriv->currentHwEp, usbReq, dmaBuff, length);
        } else {
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Start status phase%s\n", " ");
            sduhcEpProgram(pD, usbHEpPriv->currentHwEp, usbReq,
                    usbReq->setupDma, 0);
        }
    } else
        pD->ep0State = UHC_EP0_STAGE_IDLE;

    /* call completion handler if done */
    if (pD->ep0State == UHC_EP0_STAGE_IDLE || usbReq->status != EINPROGRESS) {
        vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "COMPLETE CONTROL TRANSFER %x\n",
                usbReq->actualLength);
        usbHEpPriv->transferFinished =1;
        sduhcScheduleNextTransfer(pD, usbReq, hwEp);
    }

    return 0;
}


/**
 * Function called when USB transfer has been finished for EPX.
 */
static void sduhcHostEpXIrq(UHC_Controller *pD, uint8_t hwEpNum, uint8_t isIn) {

    UhcEp * hwEp = isIn ? &pD->in[hwEpNum] : &pD->out[hwEpNum];
    CUSBH_Ep * usbHEp = hwEp->scheduledUsbHEp;
    UhcHostEpPriv * usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;
    CUSBH_Req *usbReq;
    uint32_t chMaxLen=0;
    uint8_t usbError = 0;
    uint32_t status = 0;
    uint32_t length;
    UCRegs * regs = pD->regs;

    usbReq = sduhcGetNextReq(usbHEp);

    assert(usbReq!=NULL);

    if (isIn) {
        usbError = CPS_UncachedRead8(&regs->epExt[hwEpNum - 1].rxerr);
    } else
        usbError = CPS_UncachedRead8(&regs->epExt[hwEpNum - 1].txerr);

    usbError = (usbError & UCHM_ERR_TYPE) >> 2;

    status = sduhcDecodeErrorCode(usbError);

    length = pD->dmaDrv->getActualLength(pD->dmaController, hwEp->channel);

    chMaxLen = pD->dmaDrv->getMaxLength(pD->dmaController, hwEp->channel);

    vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1,
            "hwEP-%d-%s error %04x, usbReq actualLength %d (dmaLength: %d)\n",
            hwEpNum, isIn ? "IN" : "OUT", usbError, usbReq->actualLength+length,
            usbReq->buffLength);

    /*faults - aborting transfer*/
    if (status) {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Aborting%s\n", " ");

        /*Clear error interrupt in order to avoid handling this request in err interrupt
          If error occurs firmware can arise  interrupt for transaction - first from DMA and
          second from USB*/
        if(isIn) {
            CPS_UncachedWrite16(&pD->regs->rxerrirq, 1 << hwEpNum);
        } else {
            CPS_UncachedWrite16(&pD->regs->txerrirq, 1 << hwEpNum);
        }

        pD->dmaDrv->channelAbort(pD->dmaController, hwEp->channel);
    }

    if (status != 0) {
        usbReq->status = status;
    }

    usbReq->actualLength += length;
    if(length == chMaxLen) {
        if((usbReq->buffLength - usbReq->actualLength )== 0 )
            usbHEpPriv->transferFinished = 1;
        else
            usbHEpPriv->transferFinished =0;
    } else {
        /*Short packet has been received**/
        usbHEpPriv->transferFinished = 1;
    }

    if (usbHEpPriv->type != CH9_USB_EP_ISOCHRONOUS) {
        uint8_t reg;
        /*Disable only OUT endpoint.*/
        if (!hwEp->isInEp) {
            reg = CPS_UncachedRead8(&regs->ep[hwEp->hwEpNum - 1].rxcon);
            reg &= ~UCM_CON_VAL;
            CPS_UncachedWrite8(&regs->ep[hwEp->hwEpNum - 1].rxcon, reg);
        }

        pD->dmaDrv->channelRelease(pD->dmaController, hwEp->channel);
        hwEp->channel = NULL;
    }

    /*After finished previous interrupt transfer firmware have to update fields `frame` for rest interrupt transfers.
     * This frame indicate when interrupt should be should be started*/
    if(usbHEpPriv->type == CH9_USB_EP_INTERRUPT ) {
        /*Select the best transfer to starts */
        if (usbHEpPriv->isIn)
            sduhcUpdateTimeInterruptTransfer(&pD->intInHEpQueue, usbHEpPriv);
        else
            sduhcUpdateTimeInterruptTransfer(&pD->intOutHEpQueue, usbHEpPriv);
    }

    sduhcScheduleNextTransfer(pD, usbReq, hwEp);
}

/**
 * DMA Callback function.
 * Function is called from SGDMA driver when DMA transfer has been finished.
 * This function should be assigned to pD->dmaCallback.complete field.
 */
static void sduhcCallbackTransfer(void *pD, uint8_t epNum, uint8_t isDirTx) {
    UHC_Controller * priv = (UHC_Controller*)pD;
    if((priv->otgState == OTG_STATE_B_PERIPHERAL) || (priv->otgState == OTG_STATE_A_PERIPHERAL)) {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 2, "DMA Callback forwarded to CUSBD driver %s\n", " ");
        sdudcCallbackTransfer(priv->usbDeviceController, epNum, isDirTx);
        return;
    }
    /*Interrupt for EP0 endpoint (Control)*/
    if (!epNum) {
        sduhcHostEp0Irq(pD, !isDirTx);
    } else {
        /* endpoints 1..15 */
        sduhcHostEpXIrq(pD, epNum, !isDirTx);
    }

}

/**
 * Function called when USB Error occurs
 * Because SGDMA component can only detect properly DMA completion so
 * firmware has to informs SGDMA that error occurs on USB in order to
 * SGDMA could finish started DMA transfer.
 */
static void sduhcErrorIrq(UHC_Controller * pD) {
    uint16_t txErrIrq, txErrIrqEn;
    uint16_t rxErrIrq, rxErrIrqEn;
    UCRegs * usbRegs;
    uint8_t i;

    if (!pD)
        return;

    usbRegs = pD->regs;

    txErrIrq = CPS_UncachedRead16(&usbRegs->txerrirq);
    txErrIrqEn = CPS_UncachedRead16(&usbRegs->txerrien);
    txErrIrq &= txErrIrqEn;

    rxErrIrq = CPS_UncachedRead16(&usbRegs->rxerrirq);
    rxErrIrqEn = CPS_UncachedRead16(&usbRegs->rxerrien);
    rxErrIrq &= rxErrIrqEn;

    if (!txErrIrq && !rxErrIrq)
        return;

    printf("txErrIrq: 0x%x rxErrIrq: 0x%x\n",
                txErrIrq, rxErrIrq);
    for (i = 0; i < 16; i++) {
        uint16_t mask = 1 << i;
        if (rxErrIrq & mask) {
            /*Error for hcIn endpoint*/
            CPS_UncachedWrite16(&usbRegs->rxerrirq, mask);
            rxErrIrqEn &= ~mask;
            CPS_UncachedWrite16(&usbRegs->rxerrien, rxErrIrqEn);
            pD->dmaDrv->errIsr(pD->dmaController, i, 0);
        }

        if (txErrIrq & mask) {
            /*Error for hcOut endpoint*/
            CPS_UncachedWrite16(&usbRegs->txerrirq, mask);
            txErrIrqEn &= ~mask;
            CPS_UncachedWrite16(&usbRegs->txerrien, txErrIrqEn);
            pD->dmaDrv->errIsr(pD->dmaController, i, 1);
        }
    }
}

static void sduhcResetFinished(UHC_Controller * pD) {

    if (pD->otgState == OTG_STATE_A_WAIT_BCON || pD->otgState == OTG_STATE_B_WAIT_ACON) {
        /*Detect speed*/
        pD->speed = sduhcGetActualSpeed(pD);
        switch(pD->speed) {
            case CH9_USB_SPEED_HIGH:
                pD->portStatus |= CH11_USB_PS_HIGH_SPEED;
                vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Detected HS device\n%s", " ");
                break;
            case CH9_USB_SPEED_FULL:
                vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Detected FS device\n%s", " ");
                break;
            case CH9_USB_SPEED_LOW:
                pD->portStatus |= CH11_USB_PS_LOW_SPEED;
                vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Detected LS device\n%s", " ");
                break;
            default:
                break;
        }

        /*Inform DMA component that USB work in Host Mode*/
        pD->dmaDrv->setHostMode(pD->dmaController);

        /* Inform Application about port status change*/
        if (pD->usbHostCallback.portStatusChange) {
            pD->usbHostCallback.portStatusChange(pD);
        } else {
            vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function portStatusChange not assigned%s\n", "");
        }
        switch(CPS_UncachedRead8(&pD->regs->otgstate)) {
        case OTG_STATE_B_HOST:
            pD->otgState = OTG_STATE_B_HOST;
            break;
        case OTG_STATE_A_HOST:
            //go through
        default:
            pD->otgState = OTG_STATE_A_HOST;
            break;
        }

        if(pD->usbHostCallback.otgStateChange)
            pD->usbHostCallback.otgStateChange(pD, pD->otgState);
    }
}

void sduhcResetEndpoint(UHC_Controller *pD) {
    CPS_UncachedWrite8(&pD->regs->endprst, UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST
                    | UCM_ENDPRST_IO_TX);
    CPS_UncachedWrite8(&pD->regs->endprst,
            UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST);
    CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | 0 | 0x04 );
    CPS_UncachedWrite8(&pD->regs->ep0fifoctrl, UCM_FIFOCTRL_FIFOAUTO | UCM_FIFOCTRL_IO_TX | 0 | 0x04);
}

static inline void sduhcOtgDisconnectHostDetect(UHC_Controller * pD)
{
    UCRegs * usbRegs = pD->regs;
    uint8_t otgState = CPS_UncachedRead8(&usbRegs->otgstate);
    uint8_t reg;

    reg = CPS_UncachedRead8(&pD->regs->otgctrl);
    if((reg & UCHM_OTGCTRL_ASETBHNPEN) && pD->otgState == OTG_STATE_A_SUSPEND) {
        DbgMsg(DBG_NO_SILENT, 1, "Device no Response %s\n", " ");
    }

    vDbgMsg(DBG_CUSBH_OTG_MSG, 1,
        "IRQ OTG: DISCONNIRQ (Disconnected DEVICES)- previous OTG state is %s\n",
        sduhcDecodeOtgState(pD->otgState));
    CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_CONIRQ);

    if((otgState == OTG_STATE_A_HOST) || (otgState == OTG_STATE_B_HOST)) {
        /*DISCONNECT babble*/
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: DISCONNIRQ Babble%s\n", "");
        return;
    }

    /*Reset all USB endpoints*/
    sduhcResetEndpoint(pD);

    /*Root HUB port connection was changed*/
    pD->portStatus = CH11_USB_PS_POWER;
    pD->portStatus |= (CH11_USB_PSC_CONNECTION << 16);

    /* Inform Application about port status change*/;
    if (pD->usbHostCallback.portStatusChange) {
        pD->usbHostCallback.portStatusChange(pD);
    } else {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function portStatusChange not assigned%s\n", "");
    }

    if(pD->otgState == OTG_STATE_A_SUSPEND)
    	sduhcSetVbus(pD, 0);
    pD->otgState = OTG_STATE_A_IDLE;

    if(pD->usbHostCallback.otgStateChange)
        pD->usbHostCallback.otgStateChange(pD, OTG_STATE_B_IDLE);
    return;
}

static inline void sduhcOtgAIDLEDetect(UHC_Controller * pD, uint8_t otgState)
{
    UCRegs * usbRegs = pD->regs;
    uint8_t reg;

    vDbgMsg(DBG_CUSBH_OTG_MSG, 1,
            "IRQ OTG: A_IDLE IRQ - previous OTG state is %s\n",
            sduhcDecodeOtgState(pD->otgState));

    CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_IDLEIRQ);

    if(otgState != OTG_STATE_A_IDLE) {
        /*A_IDLE babble*/
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: A_IDLE Babble%s\n", "");
        return;
    }

    //Sometimes firmware may not detects B_IDLE and enter to A_IDLE so then we have to
    // stop Device first
    if((pD->otgState == OTG_STATE_A_PERIPHERAL) || (pD->otgState == OTG_STATE_B_PERIPHERAL)) {
        pD->usbDevDrv->stop(pD->usbDeviceController);
    }
    pD->portStatus = 0;

    reg = CPS_UncachedRead8(&pD->regs->otgctrl);
    reg &= ~UCHM_OTGCTRL_ASETBHNPEN;
    CPS_UncachedWrite8(&pD->regs->otgctrl, reg);

    sduhcSetVbus(pD, 1); /*Set VBUS */

    pD->otgState = OTG_STATE_A_IDLE;
    if(pD->usbHostCallback.otgStateChange)
        pD->usbHostCallback.otgStateChange(pD, OTG_STATE_A_IDLE);
    return;
}

static inline void sduhcOtgConnectHostDetect(UHC_Controller * pD, uint8_t otgState)
{
    UCRegs * usbRegs = pD->regs;

    vDbgMsg(DBG_CUSBH_OTG_MSG, 1,
        "IRQ OTG: CONIRQ (Connected DEVICES)- previous OTG state is %s\n",
        sduhcDecodeOtgState(pD->otgState));

    CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_CONIRQ);

    if((otgState != OTG_STATE_A_HOST) && (otgState != OTG_STATE_B_HOST)) {
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: CONNIRQ Babble%s\n", "");
        return;
    }

    //if previous state was PERIPHERAL then reset and disconnect device
    if( (pD->otgState == OTG_STATE_A_PERIPHERAL) || (pD->otgState == OTG_STATE_B_PERIPHERAL)) {
        /*Driver needs to inform higher layer that currently it works in Host mode*/
        pD->otgState = otgState;
        pD->usbDevDrv->stop(pD->usbDeviceController);
    }
    /*host has connected device*/
    pD->ep0State = UHC_EP0_STAGE_IDLE;

    /*Change port status. Clear Speed and set Port Connection Change bit*/
    pD->portStatus &= ~(CH11_USB_PS_LOW_SPEED | CH11_USB_PS_HIGH_SPEED
            | CH11_USB_PS_ENABLE);

    pD->portStatus |= CH11_USB_PS_CONNECTION
            | (CH11_USB_PSC_CONNECTION << 16);

    pD->dmaDrv->controllerReset(pD->dmaController);
    /*Firmware will finish entering to Host Mode after finishing Reseting
     * in sduhcResetFinished function*/
    pD->port_resetting =1;

    /*
     * During HNP (B_PERIPHERAL -> B_HOST) when driver doesn't go through
     * A_IDLE state VBUS will be disabled in this place so driver has to
     * switch on it
     */
    sduhcSetVbus(pD, 1);


    while(1) {
        uint8_t otgChangeDetection = CPS_UncachedRead8(&usbRegs->otgstate);
        if (CPS_UncachedRead8(&usbRegs->usbirq) & UCM_USBIR_URES) {
            CPS_UncachedWrite8(&usbRegs->usbirq, UCM_USBIR_URES);
            pD->port_resetting =0;
            break;
        }
        if(otgChangeDetection != OTG_STATE_B_HOST &&  otgChangeDetection != OTG_STATE_A_HOST) {
            break;
        }
    }

    /*Detect speed*/
    pD->speed = sduhcGetActualSpeed(pD);
    switch(pD->speed) {
        case CH9_USB_SPEED_HIGH:
            pD->portStatus |= CH11_USB_PS_HIGH_SPEED;
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 0, "Detected HS device\n%s", " ");
            break;
        case CH9_USB_SPEED_FULL:
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 0, "Detected FS device\n%s", " ");
            break;
        case CH9_USB_SPEED_LOW:
            pD->portStatus |= CH11_USB_PS_LOW_SPEED;
            vDbgMsg(DBG_CUSBH_BASIC_MSG, 0, "Detected LS device\n%s", " ");
            break;
        default:
            break;
    }

    pD->vBusErrCnt =0;
    /*Inform DMA component that USB work in Host Mode*/
    pD->dmaDrv->setHostMode(pD->dmaController);

    /* Inform Application about port status change*/
    if (pD->usbHostCallback.portStatusChange) {
        pD->usbHostCallback.portStatusChange(pD);
    } else {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function portStatusChange not assigned%s\n", "");
    }

    pD->otgState = otgState;
    if(pD->usbHostCallback.otgStateChange)
        pD->usbHostCallback.otgStateChange(pD, pD->otgState);
    return;
}

static inline void sduhcOtBIDLEDetect(UHC_Controller * pD, uint8_t otgState)
{
    UCRegs * usbRegs = pD->regs;
    uint8_t reg;
    uint8_t usbcs =0;

    vDbgMsg(DBG_CUSBH_OTG_MSG, 1,
        "IRQ OTG: IDLE IRQ (B_IDLE) - previous OTG state is %s\n",
        sduhcDecodeOtgState(pD->otgState));
    CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_IDLEIRQ);

    if(otgState != OTG_STATE_B_IDLE) {
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: B_IDLE Babble%s\n", "");
        return;
    }


    //if previous state was PERIPHERAL then reset and disconnect device
    if((pD->otgState == OTG_STATE_A_PERIPHERAL) || (pD->otgState == OTG_STATE_B_PERIPHERAL)) {
        pD->usbDevDrv->stop(pD->usbDeviceController);
    }
    /*Disable UCHM_OTGCTRL_ASETBHNPEN bit*/
    reg = CPS_UncachedRead8(&pD->regs->otgctrl);
    reg &= ~UCHM_OTGCTRL_ASETBHNPEN;
    CPS_UncachedWrite8(&pD->regs->otgctrl, reg);

    sduhcSetVbus(pD, 0); /*Clear VBUS */
    pD->otgState = OTG_STATE_B_IDLE;

    /*Set Connect USB controller*/
    usbcs = CPS_UncachedRead8(&pD->regs->usbcs);
    usbcs &= ~UCM_USBCS_DISCON;
    CPS_UncachedWrite8(&pD->regs->usbcs, usbcs);
    if(pD->usbHostCallback.otgStateChange)
        pD->usbHostCallback.otgStateChange(pD, OTG_STATE_B_IDLE);

    return;
}

/**
 * Function for handling interrupt reported by OTG FSM
 */
static void sduhcOtgIrq(UHC_Controller * pD) {
    UCRegs * usbRegs = pD->regs;
    uint8_t otgIrqV, otgIrqM;
    uint8_t otgStatus;
    uint8_t otgState;
    uint8_t reg;

    otgIrqV = CPS_UncachedRead8(&usbRegs->otgirq);
    otgIrqM = CPS_UncachedRead8(&usbRegs->otgien);
    otgStatus = CPS_UncachedRead8(&usbRegs->otgstatus);
    otgState = CPS_UncachedRead8(&usbRegs->otgstate);
    otgIrqV = otgIrqV & otgIrqM;

    vDbgMsg(DBG_CUSBH_OTG_MSG, 1, "OTG Interrupt %x %x\n", otgIrqV, usbRegs->otgirq);

    if(!otgIrqV)
        return;

    if (otgIrqV & UCHM_OTGIRQ_BSE0SRPIRQ) {
        otgIrqV &= ~UCHM_OTGIRQ_BSE0SRPIRQ;
        CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_BSE0SRPIRQ);

        reg = CPS_UncachedRead8(&pD->regs->otgctrl);
        reg &= ~UCHM_OTGCTRL_BUSREQ;
        CPS_UncachedWrite8(&pD->regs->otgctrl, reg);

        /*This part of code is used only by tester MQP*/
        if(getMQPTestSrpFlag(pD->usbDeviceController)) {
            clearMQPTestSrpFlag(pD->usbDeviceController);
            reg = CPS_UncachedRead8(&pD->regs->otgctrl);
            reg |= UCHM_OTGCTRL_BUSREQ;
            reg &= ~(UCHM_OTGCTRL_ABUSDROP);
            CPS_UncachedWrite8(&pD->regs->otgctrl, reg);
            if(pD->usbHostCallback.setTimer)
                pD->usbHostCallback.setTimer(pD, 5000, 0);
        }
    }

    if (otgIrqV & UCHM_OTGIRQ_SRPDETIRQ) {
        otgIrqV &= ~UCHM_OTGIRQ_SRPDETIRQ;
        CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_SRPDETIRQ);

        reg = CPS_UncachedRead8(&pD->regs->otgctrl);
        reg &= ~(UCHM_OTGCTRL_ABUSDROP);
        CPS_UncachedWrite8(&pD->regs->otgctrl, reg);
    }

    if (otgIrqV & UCHM_OTGIRQ_VBUSERRIRQ) {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1,
            "IRQ OTG: OTG_VBUSERRIRQ - previous OTG state is %s\n",
            sduhcDecodeOtgState(pD->otgState));
        otgIrqV &= ~UCHM_OTGIRQ_VBUSERRIRQ;
        CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_VBUSERRIRQ);

        if(otgState != OTG_STATE_A_VBUS_ERR) {
            /*VBUS babble*/
            vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: VBUSERROR Babble%s\n", "");
            return;
        }
        sduhcSetVbus(pD, 0);    /*Switch on again VBUS*/
        pD->otgState = OTG_STATE_A_VBUS_ERR;
        /*If device has been connected then firmware tray disconnect it */
        if(pD->portStatus & CH11_USB_PS_CONNECTION) {
            /*Root HUB port connection was changed*/
            pD->portStatus = CH11_USB_PS_POWER;
            pD->portStatus |= (CH11_USB_PSC_CONNECTION << 16);
            /* Inform Application about port status change*/;
            if (pD->usbHostCallback.portStatusChange) {
                pD->usbHostCallback.portStatusChange(pD);
            } else {
                vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Critical Error: Callback function portStatusChange not assigned%s\n", "");
            }
            return;
        }

        if(pD->vBusErrCnt >= 3) {
            pD->vBusErrCnt =0;
            DbgMsg(DBG_NO_SILENT, 1, "VBUS OVER CURRENT %d\n", pD->vBusErrCnt);
            pD->portStatus |= CH11_USB_PS_OVER_CURRENT
                | (CH11_USB_PSC_OVER_CURRENT << 16);
            CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_IDLEIRQ);
            if(pD->usbHostCallback.otgStateChange)
                pD->usbHostCallback.otgStateChange(pD, OTG_STATE_A_VBUS_ERR);
        } else  {
            pD->vBusErrCnt++;
            sduhcSetVbus(pD, 1);
            CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_IDLEIRQ);
        }
    }

    /*Disconnected devices from host*/
    if (otgIrqV & UCHM_OTGIRQ_CONIRQ && (pD->otgState == OTG_STATE_A_HOST
            || pD->otgState == OTG_STATE_B_HOST
            || pD->otgState == OTG_STATE_A_SUSPEND)) {
        otgIrqV &= ~UCHM_OTGIRQ_CONIRQ;
        sduhcOtgDisconnectHostDetect(pD);
    }

    /* handling A_IDLE event*/
    if (otgIrqV & UCHM_OTGIRQ_IDLEIRQ && !(otgStatus & UCHM_OTGSTATUS_ID)) {
        otgIrqV &= ~UCHM_OTGIRQ_IDLEIRQ;
        sduhcOtgAIDLEDetect(pD, otgState);
    }

    /*Only for isOTG configuration*/
    if (otgIrqV & UCHM_OTGIRQ_PERIPHIRQ) {
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1, "IRQ OTG: OTG_PERIPHIRQ - previous OTG state is %s\n", sduhcDecodeOtgState(pD->otgState));

        otgIrqV &= ~UCHM_OTGIRQ_PERIPHIRQ;
        CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_PERIPHIRQ);

        if((otgState != OTG_STATE_B_PERIPHERAL && otgState != OTG_STATE_A_PERIPHERAL)) {
            /*PERIPHERAL babble*/
            vDbgMsg(DBG_CUSBH_OTG_MSG, 1,"IRQ OTG: PERIPHERAL Babble%s\n", "");
            return;
        }

        if(otgState == OTG_STATE_A_PERIPHERAL || otgState == OTG_STATE_B_PERIPHERAL){
            sduhcDeviceStart(pD);
        }
    }

    /*Connected device to Host*/
    if (otgIrqV & UCHM_OTGIRQ_CONIRQ
            && (pD->otgState != OTG_STATE_A_HOST
                    && pD->otgState != OTG_STATE_B_HOST && pD->otgState != OTG_STATE_A_SUSPEND)) {
        otgIrqV &= ~UCHM_OTGIRQ_CONIRQ;
        sduhcOtgConnectHostDetect(pD, otgState);
    }

    /*Connected device to Host*/
    if (otgIrqV & UCHM_OTGIRQ_CONIRQ) {
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1, "IRQ OTG: BABLE CONIRQ %s\n",
            sduhcDecodeOtgState(pD->otgState));

        otgIrqV &= ~UCHM_OTGIRQ_CONIRQ;
        CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_CONIRQ);
    }

    /*Interrupt for A_IDLE was handled early so this code will be executed only
     * if IDLE interrupt arise and ID bit is set to 1 (B_IDLE)
     */
    if (otgIrqV & UCHM_OTGIRQ_IDLEIRQ) {
        vDbgMsg(DBG_CUSBH_OTG_MSG, 1,
            "IRQ OTG: IDLE IRQ (B_IDLE) - previous OTG state is %s\n",
            sduhcDecodeOtgState(pD->otgState));
        otgIrqV &= ~UCHM_OTGIRQ_IDLEIRQ;
        sduhcOtBIDLEDetect(pD, otgState);
    }
    CPS_UncachedWrite8(&usbRegs->otgirq, UCHM_OTGIRQ_IDCHANGEIRQ
                                         | UCHM_OTGIRQ_HOSTDISCON
                                         | UCHM_OTGIRQ_SRPDETIRQ);
    return;
}


/*****************************************************************************
 * Public Driver function
 *****************************************************************************/
/**
 * Function return number of memory required by CUSBH Driver.
 */
static uint32_t sduhcProbe(CUSBH_Config * config, CUSBH_SysReq * sysReq) {
    CUSBDMA_OBJ * dmaDrv = NULL;
    CUSBDMA_Config dmaConfig;
    CUSBDMA_SysReq dmaSysReq;
    uint32_t res; // keeps result of operation on driver

    if ((config == NULL) || (sysReq == NULL))
        return EINVAL;

    dmaConfig.regBase = config->regBase + 0x400;

    sysReq->privDataSize = sizeof(UHC_Controller);
    if (config->isEmbeddedHost) {
        dmaDrv = CUSBDMA_GetInstance();

        res = dmaDrv->probe(&dmaConfig, &dmaSysReq);
        if(res) return res;
        sysReq->trbMemSize = dmaSysReq.trbMemSize;
        sysReq->privDataSize += dmaSysReq.privDataSize;
    }

    if (config->isOtg || config->isDevice) {
        /*Support for Device too*/
        CUSBD_OBJ * usbDevDrv = CUSBD_GetInstance();
        CUSBD_Config usbDevConfig;
        CUSBD_SysReq usbDevSysReq;

        /*Copy data from host*/
        sduhcPrepareDeviceConfig(config, &usbDevConfig);

        res = usbDevDrv->probe(&usbDevConfig, &usbDevSysReq);
        if(res) return res;
        sysReq->trbMemSize = usbDevSysReq.trbMemSize;
        sysReq->privDataSize += usbDevSysReq.privDataSize;
    }
    return 0;
}

#ifdef USB_CONTROLLER_BYTE_SWAP
/**
 * Function set the correct endian byte order for SFRs access.
 * Little Endian byte order is a default value after reset.
 */
static void sduhcSetSFREndian(UCRegs * regs){
    volatile uint8_t test[4] = {1, 0, 0, 0 };
    volatile uint32_t volatile *test_ptr = (uint32_t*)test;

#define BIG_ENDIAN_MAGIC_NUMBER 0x01000000ul
    if(*test_ptr ==  BIG_ENDIAN_MAGIC_NUMBER) {
        CPS_UncachedWrite8(&regs->endian_sfr_cs,  UCRM_ENDIAN_SFR_CS_BENDIAN);
    }
}
#endif 

/**
 * Function initializes driver
 */
static uint32_t sduhcInit(void *privateData, const CUSBH_Config* config,
        CUSBH_Callbacks* callbacks) {
    CUSBD_Config devConfig;
    UHC_Controller * pD = (UHC_Controller*) privateData;

    if ((privateData == NULL) || (config == NULL) || (callbacks == NULL))
        return EINVAL;

    memset(privateData, 0, sizeof(UHC_Controller));

    pD->usbHostCallback = *callbacks;
    pD->usbHostCfg = *config;
    if(config->regBase == 0)
        return EINVAL;

    pD->regs = (UCRegs*) config->regBase;
    pD->uhcHostDrv = CUSBH_GetInstance();

    CPS_UncachedWrite8(&pD->regs->speedctrl, 0x80);

    /*Mapping memory for Controller*/
    pD->dmaDrv = CUSBDMA_GetInstance();
    pD->dmaCfg.regBase = config->regBase + 0x400;
    if(config->trbAddr == 0 || config->trbDmaAddr ==0)
        return EINVAL;
    pD->dmaCfg.trbAddr = config->trbAddr;
    pD->dmaCfg.trbDmaAddr = config->trbDmaAddr;
    pD->dmaCallback.complete = sduhcCallbackTransfer;

#ifdef USB_CONTROLLER_BYTE_SWAP
    sduhcSetSFREndian(pD->regs);
#endif 

    if (config->isEmbeddedHost) {
        if (config->dmultEnabled) {
            pD->dmaCfg.dmaModeRx = 0xFFFF;
            pD->dmaCfg.dmaModeTx = 0xFFFF;
        } else {
            pD->dmaCfg.dmaModeRx = 0x0000;
            pD->dmaCfg.dmaModeTx = 0x0000;
        }

        pD->usbDeviceReadyToWork = 0;
        pD->dmaController = (void*) ((uintptr_t) pD + sizeof(UHC_Controller));
        pD->dmaDrv->init(pD->dmaController, &pD->dmaCfg, &pD->dmaCallback);
        pD->dmaDrv->setParentPriv(pD->dmaController, pD);
        sduhcInitController(privateData);
    }

    if (config->isDevice) {
        pD->otgState = OTG_STATE_B_PERIPHERAL;
        pD->usbDevDrv = CUSBD_GetInstance();
        pD->usbDeviceController = (void*) ((uintptr_t) pD
                + sizeof(UHC_Controller));
        pD->usbDevCallback = *((CUSBD_Callbacks *)callbacks->usbDevCallbacks);
        sduhcPrepareDeviceConfig(config, &devConfig);
        pD->dmaController = (void*) ((uintptr_t) pD + sizeof(UHC_Controller)
                + udcGetPrivateSize());
        pD->usbDevDrv->init(pD->usbDeviceController, &devConfig,
                &pD->usbDevCallback);
        pD->usbDeviceReadyToWork =1;
    }

    if (config->isOtg) {
        if (config->dmultEnabled) {
            pD->dmaCfg.dmaModeRx = 0xFFFF;
            pD->dmaCfg.dmaModeTx = 0xFFFF;
        } else {
            pD->dmaCfg.dmaModeRx = 0x0000;
            pD->dmaCfg.dmaModeTx = 0x0000;
        }

        pD->usbDevDrv = CUSBD_GetInstance();
        pD->usbDeviceController = (void*) ((uintptr_t) pD
                + sizeof(UHC_Controller));
        pD->usbDevCallback = *((CUSBD_Callbacks *)callbacks->usbDevCallbacks);
        sduhcPrepareDeviceConfig(config, &devConfig);
        pD->dmaController = (void*) ((uintptr_t) pD + sizeof(UHC_Controller)
                + udcGetPrivateSize());

        /*This should be before  pD->usbDevDrv->init*/
        pD->dmaDrv->init(pD->dmaController, &pD->dmaCfg, &pD->dmaCallback);
        pD->dmaDrv->setParentPriv(pD->dmaController, pD);

        pD->usbDevDrv->init(pD->usbDeviceController, &devConfig,
                        &pD->usbDevCallback);
        pD->usbDevDrv->stop(pD->usbDeviceController);
        sduhcInitController(privateData);
        pD->usbDeviceReadyToWork =0;
    }
    return 0;
}

/**
 * Destroy driver.
 */
static void sduhcDestroy(void *privateData) {
    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Destroy Driver%s\n"," ");
    if (!privateData)
        return;
}

/**
 * This function can be called only if firmware configuration
 * supports OTG (isOtg) or Embedded Host (isEmbeddedHost) feature.
 * For only device mode (isDevice) this function should not be called
 */
void sduhcStart(void *privateData) {
    UHC_Controller * pD = (UHC_Controller*) privateData;
    UCRegs * regs;

    if (!privateData)
        return;

    regs = pD->regs;

    pD->dmaDrv->start(pD->dmaController);

    CPS_UncachedWrite8(&regs->usbien,
            UCM_USBIR_URES);

    /*Detect attached device to host. If device is already connected  We have to switch on VBUS to generate
     connection interrupt */
    if (CPS_UncachedRead8(&regs->otgstate) == OTG_STATE_A_IDLE) {
        vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Device is plugged to Host%s\n", "");
        pD->ep0State = UHC_EP0_STAGE_IDLE;
        pD->otgState = OTG_STATE_A_IDLE;
        if(!pD->usbHostCfg.isEmbeddedHost) {
            /*After usbDev->init device has allocated DMA channel for Ep0. In this moment controller is in A_IDLE state
              so firmware has to stop Device in order to free DMA channels.*/
            pD->usbDevDrv->stop(pD->usbDeviceController);
            pD->usbDeviceReadyToWork =0;
        }
        /*Clear A_IDLE interrupt because it was serviced above*/
        CPS_UncachedWrite8(&regs->otgirq, UCHM_OTGIRQ_IDLEIRQ);
        sduhcSetVbus(pD, 1);
    } else if (CPS_UncachedRead8(&regs->otgstate) == OTG_STATE_B_IDLE) {
    }
    else if (CPS_UncachedRead8(&regs->otgstate) == OTG_STATE_A_WAIT_VFALL) {
        vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "A_WAIT_VFALL %s\n", " ");
    }

    if(pD->usbHostCfg.isEmbeddedHost)
        CPS_UncachedWrite8(&regs->otgien,
                UCHM_OTGIRQ_IDLEIRQ | UCHM_OTGIRQ_CONIRQ | UCHM_OTGIRQ_VBUSERRIRQ |
                UCHM_OTGIRQ_SRPDETIRQ | UCHM_OTGIRQ_BSE0SRPIRQ);
    else
        CPS_UncachedWrite8(&regs->otgien,
                UCHM_OTGIRQ_IDLEIRQ | UCHM_OTGIRQ_CONIRQ | UCHM_OTGIRQ_VBUSERRIRQ | UCHM_OTGIRQ_PERIPHIRQ |
                UCHM_OTGIRQ_SRPDETIRQ | UCHM_OTGIRQ_BSE0SRPIRQ);
}


/**
 * Stop CUSBH driver and other drivers used by CUSBH
 */
static void sduhcStop(void *privateData) {
    UHC_Controller * pD = (UHC_Controller*) privateData;

    if (!privateData)
        return;

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Stop USB Controller%s\n", "");
    sduhcGenericIrqDisable(pD);
    sduhcSetVbus(pD, 0);
        pD->usbDevDrv->stop(pD->usbDeviceController);
    pD->dmaDrv->stop(pD->dmaController);
}

/**
 * Generic ISR
 * This function calls also ISR from CUSBD and SGDMA component.
 */
static void sduhcIsr(void *privateData) {
    UHC_Controller * pD = NULL;
    UCRegs * usbRegs = NULL;
    uint8_t usbIrqV, usbIrqM;

    if (!privateData)
        return;

    pD = (UHC_Controller*) privateData;
    usbRegs = pD->regs;

    /*If host driver is configured as Device only then firmware redirects
     * IRQ to Device driver and does nothing more*/
    if (pD->usbHostCfg.isDevice) {
        pD->usbDevDrv->isr(pD->usbDeviceController);
        return;
    } else if (pD->usbHostCfg.isOtg) {
        if((pD->otgState == OTG_STATE_B_PERIPHERAL) || (pD->otgState == OTG_STATE_A_PERIPHERAL))
            pD->usbDevDrv->isr(pD->usbDeviceController);
    }
    usbIrqV = CPS_UncachedRead8(&usbRegs->usbirq);
    usbIrqM = CPS_UncachedRead8(&usbRegs->usbien);

    usbIrqV = usbIrqV & usbIrqM;

    if (pD->usbHostCfg.dmaSupport && pD->dmaDrv->isr) {
        pD->dmaDrv->isr(pD->dmaController);
    } else {
        vDbgMsg(DBG_CUSBH_ERR_MSG, 1,
                "Error: Driver support only DMA transfer. Switch on this "
                "option in configuration%s\n", " ");
    }

    sduhcErrorIrq(pD);

    sduhcOtgIrq(pD);

    if (!usbIrqV) {
        return;
    } else
        vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "USB Interrupt %x\n", usbIrqV);

    /*Reset IRQ only when controller work in Host mode*/
    if (usbIrqV & UCM_USBIR_URES)   {
        vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "RESET IRQ%s\n", " ");
        /* Clearing interrupt bits */
        CPS_UncachedWrite8(&usbRegs->usbirq, UCM_USBIR_URES);
        pD->port_resetting = 0;
        sduhcResetFinished(pD);
    }

    if (usbIrqV & UCM_USBIR_HSPPED) {}

    /* SOF interrupt */
    if(pD->uhcHostDrv->isHostMode(pD)) {
        if (usbIrqV & UCM_USBIR_SOF) {
            vDbgMsg(DBG_CUSBH_VERBOSE_MSG, 1, "SOF IRQ%s\n", " ");
            CPS_UncachedWrite8(&usbRegs->usbirq, UCM_USBIR_SOF);
        }
    }
    return;
}


/**
 * Disable USB Host endpoint
 * This function releases all queued USB Requests and inform about this User application
 * by means of user callback. All deleted USB Requests will have status field
 * set to UHC_ESHUTDOWN
 */
static uint32_t sduhcEpDisable(void *pD, CUSBH_Ep * usbHEp) {
    UHC_Controller * ctrl = (UHC_Controller*) pD;
    UhcHostEpPriv * usbHEpPriv;
    CUSBH_Req * usbReq;

    if (!pD || !usbHEp) {
        return EINVAL;
    }

    usbHEpPriv = (UhcHostEpPriv*) usbHEp->hcPriv;

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1,
        "Disable Host ep address %x dir %x, usbHEpPriv: %p\n",
        usbHEp->epDesc.bEndpointAddress, 
         usbHEp->epDesc.bEndpointAddress & CH9_USB_DIR_DEVICE_TO_HOST,
        usbHEpPriv);

    /*endpoint have no scheduled any transfer*/
    if (!usbHEpPriv->epIsReady && !usbHEpPriv->isocEpConfigured)
        return 0;

    if(usbHEpPriv->isocEpConfigured) {
        UhcEp * hwEp = usbHEpPriv->genericHwEp;
        if (!hwEp->isInEp) {   /*Out direction*/
            CPS_UncachedWrite8(&ctrl->regs->ep[hwEp->hwEpNum - 1].txcon, UCM_CON_TYPE_ISOC);
        /*Reset fifo - this is important for ISOC endpoint*/
        CPS_UncachedWrite8(&ctrl->regs->endprst,hwEp->hwEpNum  | UCM_ENDPRST_IO_TX);
            CPS_UncachedWrite8(&ctrl->regs->endprst,
                     hwEp->hwEpNum  | UCM_ENDPRST_IO_TX |
                     UCM_ENDPRST_TOGRST | UCM_ENDPRST_FIFORST);

        } else {  /*IN direction*/
            CPS_UncachedWrite8(&ctrl->regs->ep[hwEp->hwEpNum - 1].rxcon, UCM_CON_TYPE_ISOC);

            /*Reset fifo - this is important for ISOC endpoint*/
            CPS_UncachedWrite8(&ctrl->regs->endprst,hwEp->hwEpNum);
            CPS_UncachedWrite8(&ctrl->regs->endprst,
                     hwEp->hwEpNum  | UCM_ENDPRST_FIFORST | UCM_ENDPRST_TOGRST);
        }
        usbHEpPriv->isocEpConfigured =0;
    }

    if (usbHEpPriv->currentHwEp) {
        usbReq = sduhcGetNextReq(usbHEp);

        assert(usbReq);
        /*Transfer can be in progress so we have to finish it and schedule
         * transfer for next usbHEp*/
        usbReq->status = UHC_ESHUTDOWN;
        /*cleanup*/
        sduhcAbortActuallyUsbRequest(pD, usbReq, usbHEp);
        while (!(&usbHEp->reqList == usbHEp->reqList.next)) {
            usbReq = sduhcGetNextReq(usbHEp);
            usbReq->status = UHC_ESHUTDOWN;
            sduhcScheduleNextTransfer(pD, usbReq, usbHEpPriv->currentHwEp);
        }
    } else {
        /* usbHEp is not actually scheduled so we can just empty the queue;
         */
        while (!(&usbHEp->reqList == usbHEp->reqList.next)) {
            sduhcGivbackRequest(pD, sduhcGetNextReq(usbHEp), UHC_ESHUTDOWN);
        }
        /**/
        usbHEpPriv->epIsReady = 0;
        listDelete(&usbHEpPriv->node);
    }
    return 0;
}

/**
 * Add usbReq to queue and prepare transmission if hardware is not busy.
 */
static uint32_t sduhcReqQueue(void *pD, CUSBH_Req * usbReq) {
    UHC_Controller * ctrl = (UHC_Controller*) pD;
    CUSBH_Ep * usbHostEp = NULL;
    UhcHostEpPriv * usbHEpPriv;
    ListHead * hEpQueue = NULL;
    uint32_t interval = 0;
    uint8_t hwEpNum;
    uint8_t idleQueue =0;
    CH9_UsbEndpointDescriptor * epDesc = NULL;

    if (!pD || !usbReq) {
        return EINVAL;
    }

    if(!ctrl->uhcHostDrv->isHostMode(pD)) {
        return ENODEV;
    }

    usbHostEp = usbReq->usbEp;
    epDesc = &usbHostEp->epDesc;

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Queue USB Request %p to usbHostEp: %p, buffAddress: %p,"
        "buffLength: %d, ep%d%s\n", usbReq, usbHostEp,
        usbReq->bufAddress, usbReq->buffLength, usbReq->epNum, (usbReq->epIsIn) ? "IN" : "OUT");


    usbHEpPriv = (UhcHostEpPriv*) usbHostEp->hcPriv;
    usbReq->hcPriv = (void*)usbHostEp;

    /*Add request to request list*/
    listAddTail((ListHead*)&usbReq->list, (ListHead*)&usbHostEp->reqList);

    /*if host endpoint is queued then only add request to usbHostEp->reqList*/
    if (usbHEpPriv->epIsReady) {
        if((epDesc->bmAttributes & CH9_USB_EP_TRANSFER_MASK) == CH9_USB_EP_ISOCHRONOUS) {
            /*Preparing transfer chain for next request and link it in DMA module.
             In this moment DMA probably has been already started.*/
            usbHEpPriv->isocEpConfigured =1;
            sduhcStartReq(pD, usbReq);
        }

        return 0;
    }

    /*Request for endpoint is send first time so we have to initialize private endpoint data*/
    usbHEpPriv->epIsReady = 1;
    usbHEpPriv->maxPacketSize = le16ToCpu(epDesc->wMaxPacketSize) & 0x07ff;
    usbHEpPriv->interval = usbReq->interval;
    usbHEpPriv->epNum = epDesc->bEndpointAddress & CH9_USB_EP_NUMBER_MASK;
    usbHEpPriv->faddress = usbReq->faddress;

    /*assign pointer to parent object*/
    usbHEpPriv->usbHEp = usbHostEp;

    switch (usbReq->usbDev->speed) {
    case CH9_USB_SPEED_LOW:
        usbHEpPriv->interval = usbReq->interval;
        break;
    case CH9_USB_SPEED_FULL:
        usbHEpPriv->interval = usbReq->interval;
        break;
    //fall through
    case CH9_USB_SPEED_UNKNOWN:
    case CH9_USB_SPEED_HIGH:
    default:
        break;
    }

    usbHEpPriv->isIn = usbReq->epIsIn;

    /*Interval calculation*/
    switch (epDesc->bmAttributes & CH9_USB_EP_TRANSFER_MASK) {
    case CH9_USB_EP_ISOCHRONOUS:
        if (epDesc->bInterval < 1)
            interval = 1;
        else if (epDesc->bInterval > 16)
            interval = 16;
        interval = 1 << (interval - 1);
        break;
    case CH9_USB_EP_INTERRUPT:
        if (usbReq->usbDev->speed <= CH9_USB_SPEED_FULL) {
            interval = (epDesc->bInterval < 1) ? 1 : epDesc->bInterval;
        } else {
            if (epDesc->bInterval < 1)
                interval = 1;
            else if (epDesc->bInterval > 16)
                interval = 16;
            interval = 1 << (interval - 1);
        }
        break;
    default:
        interval = 0;
    }

    switch (epDesc->bmAttributes & CH9_USB_EP_TRANSFER_MASK) {
    case CH9_USB_EP_CONTROL:
        /*For Control transfer first packet is always OUT (SETUP)*/
        usbHEpPriv->isIn = 0;
        hEpQueue = &ctrl->ctrlHEpQueue;
        hwEpNum = UHC_GENERIC_EP_CONTROLL;
        usbHEpPriv->type = CH9_USB_EP_CONTROL;
        break;
    case CH9_USB_EP_ISOCHRONOUS:
        hEpQueue =
                usbHEpPriv->isIn ? &ctrl->isoInHEpQueue : &ctrl->isoOutHEpQueue;
        hwEpNum = UHC_GENERIC_EP_ISOC;
        usbHEpPriv->type = CH9_USB_EP_ISOCHRONOUS;
        usbHEpPriv->frame = interval; /*for scheduler, can be changed*/
        usbHEpPriv->interval = interval;
        break;
    case CH9_USB_EP_BULK:
        hEpQueue =
                usbHEpPriv->isIn ?
                        &ctrl->bulkInHEpQueue : &ctrl->bulkOutHEpQueue;
        hwEpNum = UHC_GENERIC_EP_BULK;
        usbHEpPriv->type = CH9_USB_EP_BULK;
        break;
    case CH9_USB_EP_INTERRUPT:
        hEpQueue =
                usbHEpPriv->isIn ? &ctrl->intInHEpQueue : &ctrl->intOutHEpQueue;
        hwEpNum = UHC_GENERIC_EP_INT;
        usbHEpPriv->type = CH9_USB_EP_INTERRUPT;
        usbHEpPriv->frame = interval; /*For scheduler, can be changed*/
        usbHEpPriv->interval = interval;
        break;
    }

    if (usbHEpPriv->isIn) {
        usbHEpPriv->genericHwEp = &ctrl->in[hwEpNum];
    } else {
        usbHEpPriv->genericHwEp = &ctrl->out[hwEpNum];
    }

    usbHEpPriv->genericHwEp->state = EP_ALLOCATED;
    usbHEpPriv->genericHwEp->refCount++;

    /*if host endpoint queue is empty we can start transfer immediately */
    if (hEpQueue == hEpQueue->next) {
        if(usbHEpPriv->genericHwEp->state == EP_BUSY) {
            vDbgMsg(DBG_CUSBH_ERR_MSG, 1, "Error: Hardware endpoint %d is busy\n", usbHEpPriv->genericHwEp->hwEpNum);
            return EINVAL;
        }
        idleQueue = 1;
    }

    /*Add Host EP to queue */
    listAddTail(&usbHEpPriv->node, hEpQueue);

    if (idleQueue) {
        sduhcStartReq(pD, usbReq);
    }

    return 0;
}

/**
 * Remove request from queue.
 */
static uint32_t sduhcReqDequeue(void *privateData, CUSBH_Req * usbReq, uint32_t status) {
    UHC_Controller * pD = (UHC_Controller *) privateData;
    CUSBH_Ep * usbHostEp;
    UhcHostEpPriv * usbHEpPriv;
    int ret =0;

    if (!pD || !usbReq)
        return EINVAL;

    usbHostEp = (CUSBH_Ep *) usbReq->usbEp;
    usbHEpPriv = (UhcHostEpPriv *) usbHostEp->hcPriv;
    usbReq->status = UHC_ESHUTDOWN;

    vDbgMsg(DBG_CUSBH_BASIC_MSG, 1, "Dequeue usbReq=%p, dev%d usbHEp%d%s\n",
        usbReq, usbReq->faddress, usbReq->epNum,
        usbReq->epIsIn ? "in" : "out");

    if (!usbHEpPriv->epIsReady)
        return 0;

    if (!usbHEpPriv->currentHwEp || usbReq->list.prev != &usbHostEp->reqList) {

        sduhcGivbackRequest(pD, usbReq, 0);

        if (usbHostEp->reqList.next == &usbHostEp->reqList) {
            usbHEpPriv->epIsReady = 0;
            usbHEpPriv->currentHwEp = NULL;
            listDelete(&usbHEpPriv->node);

        }
    } else {
        ret = sduhcAbortActuallyUsbRequest(pD, usbReq, usbHostEp);
    }
    return ret;
}

/**
 * For special applications
 */
static uint32_t sduhcExecDbg(void *pD, uint8_t code, uintptr_t param) {
    UHC_Controller * ctrl = (UHC_Controller *) pD;

    /*Extension for electrical test SINGLE_STEP_GET_DEVICE_DESCRIPTOR_DATA*/
    #define HSET_DESCRIPTOR_DELAY 1
    if(!pD)
        return EINVAL;

    switch(code){
        case HSET_DESCRIPTOR_DELAY:
        ctrl->hsetPid0106 =1;
        ctrl->hsetPid0106wait = (HsetPid1060wait)param;
        break;
    }
    return 0;
}

/**
 * Return private data for CUSBD component.
 * Because CUSBD driver is created and initialized
 * inside CUSBH driver so user application need function
 * that make possible getting privateData pointer for
 * CUSBD component.
 */
static void * sduhcGetDevicePD(void * pD) {
    UHC_Controller * ctrl = (UHC_Controller*)pD;

    if (!ctrl)
        return NULL;

    if(ctrl->usbHostCfg.isDevice || ctrl->usbHostCfg.isOtg )
        return ctrl->usbDeviceController;
    return NULL;
}

/**
 * Returns number of memory needed for private data for every USB Host Endpoint
 * If user application crate CUSBH_Ep object it also has to allocated
 * private size for this endpoint.
 *
 */
static uint32_t sduhcGetPrivateDataSize(void *pD) {

    if(!pD)
        return EINVAL;
    return sizeof(UhcHostEpPriv);
}

/**
 * Checks if controller is in Device mode
 */
static uint8_t sduhcIsDeviceMode(void* pD) {
    UHC_Controller * ctrl = (UHC_Controller*)pD;

    if(!pD)
        return EINVAL;

    if((ctrl->otgState == OTG_STATE_A_PERIPHERAL) || (ctrl->otgState == OTG_STATE_B_PERIPHERAL))
        return 1;
    return 0;
}

/**
 * Checks if controller is in Host mode
 */
static uint8_t sduhcIsHostMode(void* pD) {
    UHC_Controller * ctrl = (UHC_Controller*)pD;

    if(!pD)
        return EINVAL;

    if((ctrl->otgState == OTG_STATE_A_HOST) || (ctrl->otgState == OTG_STATE_B_HOST))
        return 1;
    return 0;

}

static void sduhc_print_reg(void* pD)
{
    UHC_Controller * ctrl = (UHC_Controller*)pD;
    uint8_t *preg = (uint8_t *)ctrl->regs;
    for(int i=0; i<sizeof(UCRegs); i++)
    {
        printf("uhc regs[0x%x]=0x%x \n", i, preg[i]);
    }
    ctrl->usbDevDrv->print_reg(ctrl->usbDeviceController);
    ctrl->dmaDrv->print_reg(ctrl->dmaController);
}

uint8_t sduhcTimerEvents(void* pD, uint8_t id) {
    UHC_Controller * ctrl = (UHC_Controller*)pD;

    if(!pD)
        return EINVAL;

    if(ctrl->usbHostCallback.setTimer)
        ctrl->usbHostCallback.setTimer(pD, 0, id);
    DbgMsg(DBG_NO_SILENT, 1, "Device no Response %s\n", " ");

    return 0;
}

CUSBH_OBJ sduhcDrv = {
    .probe = sduhcProbe,
    .init = sduhcInit,
    .destroy = sduhcDestroy,
    .start = sduhcStart,
    .stop = sduhcStop,
    .isr = sduhcIsr,

    //endpoint operation
    .epDisable = sduhcEpDisable,
    .reqQueue = sduhcReqQueue,
    .reqDequeue = sduhcReqDequeue,
    .vhubStatusData = sduhcVHubStatusChangeData,
    .vhubControl = sduhcVHubControl,
    .execDebug = sduhcExecDbg,
    .epGetPirvateDataSize = sduhcGetPrivateDataSize,
    .getDevicePD = sduhcGetDevicePD,
    .isDeviceMode = sduhcIsDeviceMode,
    .isHostMode = sduhcIsHostMode,
    .timerEvents = sduhcTimerEvents,
    .print_reg  = sduhc_print_reg,
};

CUSBH_OBJ * CUSBH_GetInstance(void) {
    return &sduhcDrv;
}

