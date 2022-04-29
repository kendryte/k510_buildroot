/**********************************************************************
 * Copyright (C) 2014-2017 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sduhcVHub.c
 * USB Embedded Host driver - implementation of  Virtual Hub (root hub)
 *
 ***********************************************************************/
#include "cdn_string.h"
#include "cdn_stdtypes.h"
#include "cdn_errno.h"
#include "log.h"
#include "cps.h"

#include "cusbh_if.h"
#include "cusb_ch9.h"
#include "cusb_ch11.h"
#include "cusb_dma_if.h"

#include "sduhc_if.h"
#include "sduc_regs.h"
#include "sduc_list.h"

#define DBG_USB_VHUB_MSG  0x40000000
#define DBG_USB_NO_SILENT 0x00000004

/*
 *  Function start suspending or resuming hub port depending on "on" value
 */
static void sduhcVHubPortSuspend(UHC_Controller * pD, uint8_t on) {
    UCRegs * regs = pD->regs;
    uint8_t otgctrl = 0;

    otgctrl = CPS_UncachedRead8(&regs->otgctrl);

    if (on) {
        /*Start suspend procedure*/
        otgctrl &= ~UCHM_OTGCTRL_BUSREQ; /*clear bus request*/
        otgctrl &= ~UCHM_OTGCTRL_BHNPEN;
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "VHub Port suspended%s\n", " ");
        pD->portStatus |= CH11_USB_PS_SUSPEND;
        switch (CPS_UncachedRead8(&regs->otgstate)) {
            case OTG_STATE_A_HOST:
                pD->otgState = OTG_STATE_A_SUSPEND;
                otgctrl |= UCHM_OTGCTRL_ASETBHNPEN; //HNP for A
                vDbgMsg(DBG_USB_VHUB_MSG, 1 , "OTG state -old: OTG_STATE_A_HOST, -new: %x\n", pD->otgState);
            break;
            case OTG_STATE_B_HOST:
                vDbgMsg(DBG_USB_VHUB_MSG, 1 , "OTG state -old: OTG_STATE_B_HOST, -new: %x\n", pD->otgState);
                pD->otgState = OTG_STATE_B_HOST_2;
            break;
            default:
                vDbgMsg(DBG_USB_VHUB_MSG, 1 ,"bogus VHub Port suspend? %s\n", sduhcDecodeOtgState(pD->otgState));
        }

        vDbgMsg(DBG_USB_NO_SILENT, 1 ,"HNP %s\n", "");
        CPS_UncachedWrite8(&regs->otgctrl, otgctrl);
    } else if (CPS_UncachedRead8(&regs->otgstate) == OTG_STATE_A_SUSPEND ) {
        otgctrl |= UCHM_OTGCTRL_BUSREQ;
        CPS_UncachedWrite8(&regs->otgctrl, otgctrl);

        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "WARMING: Resuming not Implemented Yet%s\n", "");
        vDbgMsg(DBG_USB_VHUB_MSG, 1 ,  "Root port resuming, otgctrl %02x\n", otgctrl);
        pD->portStatus |= UHC_VHUB_PORT_STAT_RESUME;
    }
}


static void sduhcVHubPortReset(UHC_Controller *pD, uint8_t on) {
    UCRegs * regs = pD->regs;
        
    vDbgMsg(DBG_USB_VHUB_MSG, 1 , "VHub Port Reset %s\n", on ? "Start" : "End");


    if (on) {
        /*clearing all interrupt*/
        CPS_UncachedWrite16(&regs->txerrirq, 0xFFFF);
        CPS_UncachedWrite16(&regs->rxerrirq, 0xFFFF);
        CPS_UncachedWrite16(&regs->txirq, 0xFFFF);
        CPS_UncachedWrite16(&regs->rxirq, 0xFFFF);

        /*Reset all USB endpoints*/
        sduhcResetEndpoint(pD);

        pD->portStatus |= CH11_USB_PS_RESET;
        pD->portStatus &= ~CH11_USB_PS_ENABLE;

        pD->port_resetting = 0;
    } else {
        uint8_t speed = sduhcGetActualSpeed(pD);

        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "Port reset finished - speed %x\n",speed);

        if (speed == CH9_USB_SPEED_HIGH) {
            vDbgMsg(DBG_USB_VHUB_MSG, 1 ,"high-speed device connected%s\n", " ");
            pD->portStatus |= CH11_USB_PS_HIGH_SPEED;
        } else if (speed == CH9_USB_SPEED_FULL) {
            vDbgMsg(DBG_USB_VHUB_MSG, 1 ,"fs-speed device connected%s\n", " ");
            pD->portStatus &= ~(CH11_USB_PS_LOW_SPEED
                    | CH11_USB_PS_HIGH_SPEED);
        } else {
            vDbgMsg(DBG_USB_VHUB_MSG, 1 , "ls-speed device connected %s\n", " ");
                pD->portStatus |= CH11_USB_PS_LOW_SPEED;
        }

        pD->portStatus &= ~CH11_USB_PS_RESET;
        pD->portStatus |= CH11_USB_PS_ENABLE | (CH11_USB_PSC_RESET
                << 16) | (CH11_USB_PSC_ENABLE << 16);
        pD->usbHostCallback.portStatusChange(pD);
    }
}

/**
 *  Check if USB port detect any changes
 */
uint32_t sduhcVHubStatusChangeData(void * pD, uint8_t *status) {
    UHC_Controller * ctrl = (UHC_Controller*) pD;

    if(!pD || !status)
        return EINVAL;

    if (ctrl->portStatus & 0xffff0000) {
        *status = 0x02;
    }
    return 0;
}

uint32_t sduhcVHubGetHubDesc(UHC_Controller * pD, CH9_UsbSetup * setup,
        uint8_t * buff) {
    CH11_UsbHubDescriptor *desc = (void *) buff;
    vDbgMsg(DBG_USB_VHUB_MSG, 1 , "Get Virtual Hub Descriptor%s\n", " ");
    desc->bDescLength = 9;
    desc->bDescriptorType = 0x29;
    desc->bNbrPorts = 1;
    desc->wHubCharacteristics = cpuToLe16(
            0x0001 /* per-port power switching */
            | 0x0010 /* no overcurrent reporting */
            );
    desc->bPwrOn2PwrGood = 5; /* msec/2 */
    desc->bHubContrCurrent = 0;

    desc->DeviceRemovable[0] = 0x02; /* port 1 */
    //  desc->DeviceRemovable[1] = 0xff;
    return 0;
}

uint32_t sduhcVHubClearPortFeature(UHC_Controller * pD, CH9_UsbSetup * setup) {

    vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CLearPortFeature Selector: %08x, actual port status: %x ", setup->wValue, pD->portStatus);

    /*At now driver support only one hub port */
    if ((le16ToCpu(setup->wIndex) & 0xff) != 1)
        return UHC_ESTALL;

    switch (le16ToCpu(setup->wValue)) {
    case CH11_USB_FS_PORT_ENABLE:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_PORT_ENABLE%s\n", " ");
        break;
    case CH11_USB_FS_PORT_SUSPEND:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_PORT_SUSPEND%s\n", " ");
        sduhcVHubPortSuspend(pD, 0);
        break;
    case CH11_USB_FS_PORT_POWER:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "USB_PORT_FEAT_POWER%s\n", " ");
        sduhcSetVbus(pD, 0);
        break;
    case CH11_USB_FS_PORT_INDICATOR:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_PORT_INDICATOR%s\n", " ");
        break;
    case CH11_USB_FS_C_PORT_CONNECTION:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_C_PORT_CONNECTION%s\n", " ");
        break;
    case CH11_USB_FS_C_PORT_RESET:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_C_PORT_RESET%s\n", " ");
        break;
    case CH11_USB_FS_C_PORT_ENABLE:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_C_PORT_ENABLE%s\n", " ");
        break;
    case CH11_USB_FS_C_PORT_SUSPEND:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_C_PORT_SUSPEND%s\n", " ");
        break;
    case CH11_USB_FS_C_PORT_OVER_CURRENT:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "CH11_USB_FS_C_PORT_OVER_CURRENT%s\n", " ");
        break;
    default:
        return UHC_ESTALL;
    }
    pD->portStatus &= ~(1 << le16ToCpu(setup->wValue));
    vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CLearPortFeature port status after clearing: %08x\n ", pD->portStatus);
    return 0;

}

uint32_t sduhcVHubGetPortStatus(UHC_Controller * pD, CH9_UsbSetup * setup,
        uint8_t * buff) {
    uint32_t temp =0;
    /*Driver support only one port*/
    if (le16ToCpu(setup->wIndex) != 1) {
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "Error port %d is not supported\n", le16ToCpu(setup->wIndex));
        return UHC_ESTALL;
    }

    /* finish RESET signaling*/
    vDbgMsg(DBG_USB_VHUB_MSG, 1, "Port status %x\n", pD->portStatus);
    if (pD->portStatus & CH11_USB_PS_RESET) {
        if(!pD->port_resetting)
            sduhcVHubPortReset(pD, 0);
    }

    /* finish RESUME signaling */
    if (pD->portStatus & UHC_VHUB_PORT_STAT_RESUME) {
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "finish Port resuming signaling%s\n", " ");

        pD->portStatus &= ~(CH11_USB_PS_SUSPEND | UHC_VHUB_PORT_STAT_RESUME);
        pD->portStatus |= CH11_USB_PSC_SUSPEND << 16;
        pD->usbHostCallback.portStatusChange(pD);
        pD->otgState = OTG_STATE_A_HOST;
    }

    temp =cpuToLe32(pD->portStatus & ~UHC_VHUB_PORT_STAT_RESUME);
    /*This buffer can be unaligned so firmware has to copy data byte by byte */
    buff[0] = temp;
    buff[1] = temp >> 8;
    buff[2] = temp >> 16;
    buff[3] = temp >> 24;

    vDbgMsg(DBG_USB_VHUB_MSG, 1, "End Port status %x\n", pD->portStatus);
    return 0;
}

uint32_t sduhcVHubSetPortFeature(UHC_Controller * pD, CH9_UsbSetup * setup) {
    UCRegs * regs = pD->regs;
    /*Driver support only one port*/
    if (le16ToCpu(setup->wIndex & 0x00FF) != 1) {
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "Error port %d is not supported\n", le16ToCpu(setup->wIndex));
        return UHC_ESTALL;
    }
    vDbgMsg(DBG_USB_VHUB_MSG, 1, "SET Port Feature value: %d\n", le16ToCpu(setup->wValue));

    switch (le16ToCpu(setup->wValue)) {
    case CH11_USB_FS_PORT_POWER:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "VHub Set Port Feature - PORT POWER %s\n", " ");
        sduhcStart(pD);
        break;
    case CH11_USB_FS_PORT_RESET:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "VHub Set Port Feature - PORT RESET%s\n", " " );
        sduhcVHubPortReset(pD, 1);
        break;
    case CH11_USB_FS_PORT_SUSPEND:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "VHub Set Port Feature - PORT SUSPEND%s\n", " ");
        sduhcVHubPortSuspend(pD, 1);
        break;
    case CH11_USB_FS_PORT_TEST: {
        uint8_t portctrl = CPS_UncachedRead8(&regs->portctrl);
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "VHub Set Port Feature - PORT TEST%s\n", " ");

        switch (le16ToCpu(setup->wIndex) >> 8) {
        case 0:
            break;
        case CH9_TEST_J :
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "Test Mode: TEST_J %s\n", " ");
            portctrl |= UCRV_PORTCTRL_TESTM_TEST_J;
            break;
        case CH9_TEST_K:
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "Test Mode: TEST_K %s\n", " ");
            portctrl |= UCRV_PORTCTRL_TESTM_TEST_K;
            break;
        case CH9_TEST_SE0_NAK :
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "Test Mode: TEST_SE0_NAK %s\n", " ");
            portctrl |= UCRV_PORTCTRL_TESTM_TEST_SE0_NAK;
            break;
        case CH9_TEST_PACKET:
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "Test Mode: TEST_PACKET %s\n", " ");
            portctrl |= UCRV_PORTCTRL_TESTM_TEST_PACKET;
            break;
        case CH9_TEST_FORCE_EN:
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "Test Mode: TEST_FORCE_EN %s\n", " ");
            portctrl |= UCRV_PORTCTRL_TESTM_TEST_FORCE_ENABLE;
            break;
        default:
            vDbgMsg(DBG_USB_VHUB_MSG, 1, "This test is not supported%s\n", " ");
            return UHC_ESTALL;
        }
        CPS_UncachedWrite8(&regs->portctrl, portctrl);
        break;
    }
    default:
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "VHub Set Port Feature - NOT SUPPORTED%s\n", " ");
        return UHC_ESTALL;
    }

    pD->portStatus|= 1 << le16ToCpu(setup->wValue);
    return 0;
}

uint32_t sduhcVHubControl(void *pD, CH9_UsbSetup * setup, uint8_t * buff) {
    uint32_t retval = UHC_ESTALL;
    uint16_t request;
    uint32_t temp = 0;

    vDbgMsg(DBG_USB_VHUB_MSG, 1 , "Virtual hub Control request %s\n", " ");

    if(!pD || !setup || !buff)
        return EINVAL;

    request =  setup->bmRequestType << 0x08 | setup->bRequest;

    switch (request) {
    case CH11_UsbClearHubFeature:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "ClearHubFeature %s\n", " ");
        goto set_clear_feature;
    case CH11_UsbSetHubFeature: {
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "SetHubFeature %s\n", " ");
        set_clear_feature:
        switch (le16ToCpu(setup->wValue)) {
        case CH11_USB_FS_C_HUB_LOCAL_POWER:
            vDbgMsg(DBG_USB_VHUB_MSG, 1 , " CH11_USB_FS_C_HUB_LOCAL_POWER %s\n", " ");
	    break;
        case CH11_USB_FS_C_HUB_OVER_CURRENT:
            vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_USB_FS_C_HUB_OVER_CURRENT %s\n", " ");
            break;
        default:
            vDbgMsg(DBG_USB_VHUB_MSG, 1 , " ENOTSUP %s\n", " ");
            return ENOTSUP; /*UHC_ESTALL*/
        }
        break;
    }
    case CH11_UsbClearPortFeature:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_UsbClearPortFeature %s\n", " ");
        retval = sduhcVHubClearPortFeature(pD, setup);
        break;
    case CH11_UsbGetHubDescriptor:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_UsbGetHubDescriptor %s\n", " ");
        retval = sduhcVHubGetHubDesc(pD, setup, buff);
        break;
    case CH11_UsbGetHubStatus:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_UsbGetHubStatus %s\n", " ");
        temp = 0;
        vDbgMsg(DBG_USB_VHUB_MSG, 1, "Get Hub Status 0x%x\n", temp);

        /*This buffer can be unaligned so firmware has to copy data byte by byte */
        buff[0] = temp;
        buff[1] = temp >> 8;
        buff[2] = temp >> 16;
        buff[3] = temp >> 24;

        retval =0;
        break;
    case CH11_UsbGetPortStatus:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_UsbGetPortStatus %s\n", " ");
        retval = sduhcVHubGetPortStatus(pD, setup, buff);
        break;
    case CH11_UsbSetPortFeature:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "CH11_UsbSetPortFeature %s\n", " ");
        retval = sduhcVHubSetPortFeature(pD, setup);
        break;
    default:
        vDbgMsg(DBG_USB_VHUB_MSG, 1 , "ERROR: ENOTSUP %s\n", " ");
        retval = ENOTSUP;

    }
    if(retval == UHC_ESTALL)
        return ENOTSUP;

    return retval;
}

