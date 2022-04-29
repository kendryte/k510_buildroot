/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems, Inc. 
 * All rights reserved worldwide.
 ***********************************************************************
 * cusb_Ch11.h
 * File defines constants, types and structures defined in chapter 11 of:
 *  USB 2.0 specification
 *
 ***********************************************************************/
#ifndef CUSB_USB_CH11_H
#define CUSB_USB_CH11_H

#include "cdn_stdtypes.h"

#define CH11_USB_MAX_CHILDREN 0x7

/*
 *  Hub Descriptor (chapter 11.23.2.1 of USB 2.0 spec)
 */
typedef struct __attribute__((packed)){ /* Link Power Management */
    uint8_t bDescLength;  /*Number of bytes in tis descriptor*/
    uint8_t bDescriptorType; /*Descriptor type: value 29H for hub descriptor*/
    uint8_t bNbrPorts; /*Number of downstream facing ports*/
    uint16_t wHubCharacteristics;
    uint8_t bPwrOn2PwrGood; /*Time (in 2 ms intervals)*/
    uint8_t bHubContrCurrent; /*Maximum current requirements*/
    uint8_t DeviceRemovable[(CH11_USB_MAX_CHILDREN + 1 + 7) / 8];
    uint8_t PortPwrCtrlMask[(CH11_USB_MAX_CHILDREN + 1 + 7) / 8];
} CH11_UsbHubDescriptor;


/*
 * Specific Hub Class Request Codes (see table 11-16 of USB2.0 spec)
 */
#define CH11_USB_REQ_CLEAR_TT_BUFFER    0x08
#define CH11_USB_REQ_RESET_TT           0x09
#define CH11_USB_REQ_GET_TT_STATE       0x10
#define CH11_USB_REQ_STOP_TT            0x11

/*
 *  Hub Class Request (see Table 11-15 of USB 2.0 spec)
 */
#define  CH11_UsbClearHubFeature    (0x2000 | CH9_USB_REQ_CLEAR_FEATURE)
#define  CH11_UsbClearPortFeature   (0x2300 | CH9_USB_REQ_CLEAR_FEATURE)
#define  CH11_UsbClearTTBuffer      (0x2300 | CH11_USB_REQ_CLEAR_TT_BUFFER)
#define  CH11_UsbGetHubDescriptor   (0xa000 | CH9_USB_REQ_GET_DESCRIPTOR)
#define  CH11_UsbGetHubStatus       (0xa000 | CH9_USB_REQ_GET_STATUS)
#define  CH11_UsbGetPortStatus      (0xa300 | CH9_USB_REQ_GET_STATUS)
#define  CH11_UsbResetTT            (0x2300 | CH11_USB_REQ_RESET_TT)
#define  CH11_UsbSetHubDesciptor    (0x2000 | CH9_USB_REQ_SET_DESCRIPTOR)
#define  CH11_UsbSetHubFeature      (0x2000 | CH9_USB_REQ_SET_FEATURE)
#define  CH11_UsbSetPortFeature     (0x2300 | CH9_USB_REQ_SET_FEATURE)
#define  CH11_UsbGetTTState         (0xA200 | CH11_USB_REQ_GET_TT_STATE)
#define  CH11_UsbStopTT             (0x3200 | CH11_USB_REQ_STOP_TT)

#define ClearHubFeature     (0x2000 | USB_REQ_CLEAR_FEATURE)
#define ClearPortFeature    (0x2300 | USB_REQ_CLEAR_FEATURE)
#define GetHubDescriptor    (0xa000 | USB_REQ_GET_DESCRIPTOR)
#define GetHubStatus        (0xa000 | USB_REQ_GET_STATUS)
#define GetPortStatus       (0xa300 | USB_REQ_GET_STATUS)
#define SetHubFeature       (0x2000 | USB_REQ_SET_FEATURE)
#define SetPortFeature      (0x2300 | USB_REQ_SET_FEATURE)

/*
 *  Hub Class Feature Selectors (see ch 11.24.2 table 11-17 of USB 2.0 spec)
 */
#define CH11_USB_FS_C_HUB_LOCAL_POWER   0x00
#define CH11_USB_FS_C_HUB_OVER_CURRENT  0x01
#define CH11_USB_FS_PORT_CONNECTION     0x00
#define CH11_USB_FS_PORT_ENABLE         0x01
#define CH11_USB_FS_PORT_SUSPEND        0x02
#define CH11_USB_FS_PORT_OVER_CURRENT   0x03
#define CH11_USB_FS_PORT_RESET          0x04
#define CH11_USB_FS_PORT_POWER          0x08
#define CH11_USB_FS_PORT_LOW_SPEED      0x09
#define CH11_USB_FS_C_PORT_CONNECTION   0x10
#define CH11_USB_FS_C_PORT_ENABLE       0x11
#define CH11_USB_FS_C_PORT_SUSPEND      0x12
#define CH11_USB_FS_C_PORT_OVER_CURRENT 0x13
#define CH11_USB_FS_C_PORT_RESET        0x14
#define CH11_USB_FS_PORT_TEST           0x15
#define CH11_USB_FS_PORT_INDICATOR      0x16

/*
 *  Port Status Bits  (see ch 11.24.2.7.1 of USB 2.0 spec)
 */
#define CH11_USB_PS_CONNECTION      0x0001
#define CH11_USB_PS_ENABLE          0x0002
#define CH11_USB_PS_SUSPEND         0x0004
#define CH11_USB_PS_OVER_CURRENT    0x0008
#define CH11_USB_PS_RESET           0x0010
#define CH11_USB_PS_POWER           0x0100
#define CH11_USB_PS_LOW_SPEED       0x0200
#define CH11_USB_PS_HIGH_SPEED      0x0400
#define CH11_USB_PS_TEST            0x0800
#define CH11_USB_PS_INDICATOR       0x1000


/*
 *  Port Status Change Bits  (see ch 11.24.2.7.1 of USB 2.0 spec)
 */
#define CH11_USB_PSC_CONNECTION     0x0001
#define CH11_USB_PSC_ENABLE         0x0002
#define CH11_USB_PSC_SUSPEND        0x0004
#define CH11_USB_PSC_OVER_CURRENT   0x0008
#define CH11_USB_PSC_RESET          0x0010

#endif  /* CUSBD_USB_CH9_H */

