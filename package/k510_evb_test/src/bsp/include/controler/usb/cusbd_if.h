/**********************************************************************
 * Copyright (C) 2015-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          Do not edit it manually.
 **********************************************************************
 * Layer interface for the Cadence USB device controller's family
 **********************************************************************/

#ifndef _CUSBD_H_
#define _CUSBD_H_

#include "cusb_ch9.h"

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Forward declarations
 **********************************************************************/
struct CUSBD_EpConfig;
struct CUSBD_Config;
struct CUSBD_SysReq;
struct CUSBD_ListHead;
struct CUSBD_SgList;
struct CUSBD_Req;
struct CUSBD_Ep;
struct CUSBD_Dev;
struct CUSBD_epOps;
struct CUSBD_Callbacks;

/**********************************************************************
 * Enumerations
 **********************************************************************/
/** DMA BUS width available values */
typedef enum
{
    CUSBD_DMA_32_WIDTH = 4,
    CUSBD_DMA_64_WIDTH = 8,
} CUSBD_DMAInterfaceWidth;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/**
 * Reports request complete callback.
 * Params:
 * ep - endpoint associated with the request
 * req - request which has been completed
 * Note that request received in completion routine may be used again
*/
typedef void (*CUSBD_reqComplete)(struct CUSBD_Ep* ep, struct CUSBD_Req* req);

/**
 * Enable Endpoint.  This function should be called within
 * SET_CONFIGURATION(configNum > 0) request context. It configures
 * required hardware controller endpoint with parameters given in desc.
*/
typedef uint32_t (*CUSBD_epEnable)(void* pD, struct CUSBD_Ep* ep, const struct CH9_UsbEndpointDescriptor* desc);

/**
 * Disable Endpoint. Functions unconfigures hardware endpoint.
 * Endpoint will not respond to any host packets. This function
 * should be called within SET_CONFIGURATION(configNum = 0) request
 * context or on disconnect event. All queued requests on endpoint
 * are completed with ECANCELED status.
*/
typedef uint32_t (*CUSBD_epDisable)(void* pD, struct CUSBD_Ep* ep);

/**
 * Set halt or clear halt state on endpoint. When setting halt, device
 * will respond with STALL packet to each host packet. When clearing
 * halt, endpoint returns to normal operating.
*/
typedef uint32_t (*CUSBD_epSetHalt)(void* pD, struct CUSBD_Ep* ep, uint8_t value);

/**
 * Set halt on endpoint. Function sets endpoint to permanent halt
 * state. State can not be changed even with epSetHalt(pD, ep, 0) function.
 * Endpoint returns automatically to its normal state on disconnect
 * event.
*/
typedef uint32_t (*CUSBD_epSetWedge)(void* pD, struct CUSBD_Ep* ep);

/**
 * Returns number of bytes in hardware endpoint FIFO. Function useful in
 * application where exact number of data bytes is required. In some
 * situation software higher layers must be aware of number of data
 * bytes issued but not transfered by hardware because of aborted
 * transfers, for example on disconnect event.
*/
typedef uint32_t (*CUSBD_epFifoStatus)(void* pD, struct CUSBD_Ep* ep);

/** Flush hardware endpoint FIFO. */
typedef void (*CUSBD_epFifoFlush)(void* pD, struct CUSBD_Ep* ep);

/** Submits IN/OUT transfer request to an endpoint. */
typedef uint32_t (*CUSBD_reqQueue)(void* pD, struct CUSBD_Ep* ep, struct CUSBD_Req* req);

/**
 * Dequeues IN/OUT transfer request from an endpoint. Function completes
 * all queued request with ECANCELED status.
*/
typedef uint32_t (*CUSBD_reqDequeue)(void* pD, struct CUSBD_Ep* ep, struct CUSBD_Req* req);

/**
 * Allocates transfer request object. Function returns address to memory
 * where request is casted.
*/
typedef uint32_t (*CUSBD_reqAlloc)(void* pD, struct CUSBD_Ep* ep, struct CUSBD_Req** req);

/**
 * Frees memory occupied by request. While operating, when request
 * object will be no longer used, use reqFree function to free system
 * memory
*/
typedef void (*CUSBD_reqFree)(void* pD, struct CUSBD_Ep* ep, struct CUSBD_Req* req);

/**
 * Callback called on disconnect from host event. All queued transfer on all
 * active endpoints are completed by driver with ECANCELED status.
*/
typedef void (*CUSBD_CbDisconnect)(void* pD);

/**
 * Callback called on connection to host event. To check speed at which
 * device has connected to host read speed flag of CUSBD object
*/
typedef void (*CUSBD_CbConnect)(void* pD);

/**
 * Callback called on setup request received event
 * Params: ctrl contains usb setup request in little endian order
*/
typedef uint32_t (*CUSBD_CbSetup)(void* pD, struct CH9_UsbSetup* ctrl);

/** Called when device controller goes into suspend state. */
typedef void (*CUSBD_CdSuspend)(void* pD);

/** Called when device returns from suspend state. */
typedef void (*CUSBD_CbResume)(void* pD);

/** Called when device needs allocation memory for CUSBD_Req object. */
typedef void* (*CUSBD_CbUsbRequestMemAlloc)(void* pD, uint32_t requiredSize);

/** Called when device needs free memory for CUSBD_Req object. */
typedef void (*CUSBD_CbUsbRequestMemFree)(void* pD, void* usbRequest);

/** Called on bus interval event only if any isochronous endpoint used. */
typedef void (*CUSBD_CbbusInterval)(void* pD);

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/**
 * Configuration structure for single endpoint.
 * Single endpoint configuration structure object is a part of CUSBD_Config
 * object used for configuration of whole USB device
*/
typedef struct CUSBD_EpConfig
{
    /**
     * buffering value
     * It is a number of hardware (on-chip) memory buffer used for queuing
     * USB packets. Setting bufferingValue to 0 means that endpoint is disabled
     * Setting bufferingValue to 1 it sets number of on-chip buffer to 1 and
     * so on.
    */
    uint8_t bufferingValue;
    /** On-chip buffer address for Endpoint */
    uint16_t startBuf;
    /** Maximum size of single USB packet */
    uint16_t maxPacketSize;
}  CUSBD_EpConfig;

/**
 * Configuration of device.
 * Object of this type is used for probe and init functions when checking
 * memory requirements of device object and for hardware controller configuration.
 * Size of device object in bytes is returned on probe function call in
 * CUSBD_SysReq.privDataSize field. Remember that privDataSize returns size
 * of device object only - it doesn't endpoints vector object size.
 * It means that whole memory requirements = device size + (number of endpoints
 * x single endpoint size)
*/
typedef struct CUSBD_Config
{
    /** base address of device controller registers */
    uintptr_t regBase;
    /** table of endpoint configuration objects for IN direction */
    struct CUSBD_EpConfig epIN[16];
    /** table of endpoint configuration objects for OUT direction */
    struct CUSBD_EpConfig epOUT[16];
    /**
     * hardware feature enabling DMA operation in scatter/gather mode
     * 1 - enabled, 0 disabled
    */
    uint8_t dmultEnabled;
    /** DMA interface width, available values: DMA_32_WIDTH, DMA_64_WIDTH */
    CUSBD_DMAInterfaceWidth dmaInterfaceWidth;
    /**
     * Feature enabling support for DMA or Fifo mode
     * 1- DMA enabled, 0 Fifo enabled. At this moment USB driver has
     * implemented only DMA
    */
    uint8_t dmaSupport;
    /**
     * Feature enabling OTG (Host + device). If this option is set then
     * host driver additional configures and initializes CUSBD component
    */
    uint8_t isOtg;
    /** Feature enabling only Embedded Host */
    uint8_t isEmbeddedHost;
    /** Feature enabling only Device mode */
    uint8_t isDevice;
    /** Pointer to virtual memory for TRBs pool */
    void* trbAddr;
    /** Address of physical memory for TRBs pool */
    uintptr_t trbDmaAddr;
}  CUSBD_Config;

/** System requirements returned by probe */
typedef struct CUSBD_SysReq
{
    /** size of memory required for driver's private data */
    uint32_t privDataSize;
    /**
     * size of memory required for USB Transfer Request Descriptors.
     * This memory will be used by DMA controller,
     * so it should be suitable for DMA operation.
    */
    uint32_t trbMemSize;
}  CUSBD_SysReq;

/**
 * structure helpful when object are organized in  linked list
 * Device contains list of endpoints, in turn: endpoint contains request list
*/
typedef struct CUSBD_ListHead
{
    /** pointer to next element in list */
    struct CUSBD_ListHead* next;
    /** pointer to previous element in list */
    struct CUSBD_ListHead* prev;
}  CUSBD_ListHead;

/**
 * structure contains information about memory slices for scatter/gather
 * transfer
*/
typedef struct CUSBD_SgList
{
    /** link to the next elemen */
    uintptr_t link;
    /** offset within memory page */
    uint32_t offset;
    /** data length of this transfer slice */
    uint32_t length;
    /** physical address of buffer to read/write */
    uintptr_t dmaAddress;
}  CUSBD_SgList;

/**
 * Transfer request structure.
 * I/O transfers of higher layers are realized with the help of CUSBD_Req
 * objects. CUSBD_Req is associated with endpoints and should be created
 * and removed with reqAlloc i reqFree functions
*/
typedef struct CUSBD_Req
{
    /** request can be organized in linked list */
    struct CUSBD_ListHead list;
    /** buffer with data to transfer - virtual address */
    void* buf;
    /** This transfer data length */
    uint32_t length;
    /** physical address of buf buffer */
    uintptr_t dma;
    /** scatter/gather list */
    struct CUSBD_SgList* sg;
    /** number of scatter/gather entries */
    uint32_t numOfSgs;
    /** number of scatter/gather entries mapped for hardware controller */
    uint32_t numMappedSgs;
    /** stream id - used only in Super Speed mode */
    uint16_t streamId;
    /** Setting this flag to 1 disables generating of transfer completion interrupt */
    uint8_t noInterrupt;
    /**
     * Setting this flag to 1 causes adding zero length data packet at the
     * end of data transfer when data transfer length is a multiple of
     * MaxPacketSize for endpoint
    */
    uint8_t zero;
    /**
     * Setting this flag causes all reading transfers with short packet as
     * erroneous
    */
    uint8_t shortNotOk;
    /** Callback function called on the transfer completion event */
    CUSBD_reqComplete complete;
    /**
     * general-use data hook
     * driver doesn't make use of this field. May be dsed in complete
     * callback function
    */
    void* context;
    /** keeps actual status of request */
    uint32_t status;
    /** number of actually processed bytes */
    uint32_t actual;
    uint32_t maxpacket;
}  CUSBD_Req;

/** Structure represents device USB endpoint */
typedef struct CUSBD_Ep
{
    /** enables organization of endpoints in linked list */
    struct CUSBD_ListHead epList;
    /** not used by CUSBD, used by higher layers */
    void* driverData;
    /** keeps name of endpoint */
    char name[100];
    /**
     * endpoint driver, contains methods for all operation required on
     * endpoint
    */
    const struct CUSBD_epOps* ops;
    /** Maximal packet size for endpoint */
    uint16_t maxPacket;
    /** Maximal number of streams used by endpoint, useful only in SS mode */
    uint16_t maxStreams;
    /**
     * packet multiplication, it enables to multiplicate number of packet
     * per service interval, useful in HS and SS mode only for isochronous
     * endpoint, mult value range from 0 to 2 - it multiplicate packets by
     * 1 to 3
    */
    uint8_t mult;
    /**
     * Maximal number of packets in burst transfer, useful only in SS mode
     * maxburst value range from 0 to 15 giving number of packets 1 to 16
    */
    uint8_t maxburst;
    /**
     * Endpoint address, the oldest bit refers to endpoint direction.
     * For example:
     * address = 0x82 refers to endpoint 2 IN
     * address = 0x03 refers to endpoint 3 OUT
    */
    uint8_t address;
    /**
     * pointer to user defined endpoint descriptor,
     * CH9_UsbEndpointDescriptor is defined in cusb_ch9.h
    */
    const struct CH9_UsbEndpointDescriptor* desc;
    /**
     * pointer to user defined endpoint companion descriptor, useful only
     * in SS mode, CH9_UsbSSEndpointCompanionDescriptor is defined in
     * cusb_ch9.h
    */
    const struct CH9_UsbSSEndpointCompanionDescriptor* compDesc;
}  CUSBD_Ep;

/** Structure represents USB device */
typedef struct CUSBD_Dev
{
    /** allows for manipulation on endpoints organized as linked list */
    struct CUSBD_ListHead epList;
    /**
     * pointer to bidirectional default endpoint, this endpoint should
     * be always available after driver start
    */
    struct CUSBD_Ep* ep0;
    /** speed value in which device actually works */
    CH9_UsbSpeed speed;
    /** maximal speed the device is able to work */
    CH9_UsbSpeed maxSpeed;
    /** actual state in which device actually works */
    CH9_UsbState state;
    /** Flags informs if device is scatter/gather transfer capable */
    uint8_t sgSupported;
    /** Informs if device is OTG type */
    uint8_t isOtg;
    /** Informs if device is A peripheral type */
    uint8_t isAPeripheral;
    /** Informs if device is HNP capable */
    uint8_t bHnpEnable;
    /** informs if OTG device in host mode supports HNP on this port */
    uint8_t aHnpSupport;
    /** Full name of USB device controller */
    char name[100];
}  CUSBD_Dev;

/** Set of functions allowing to operate on endpoints */
typedef struct CUSBD_epOps
{
    CUSBD_epEnable epEnable;
    CUSBD_epDisable epDisable;
    CUSBD_epSetHalt epSetHalt;
    CUSBD_epSetWedge epSetWedge;
    CUSBD_epFifoStatus epFifoStatus;
    CUSBD_epFifoFlush epFifoFlush;
    CUSBD_reqQueue reqQueue;
    CUSBD_reqDequeue reqDequeue;
    CUSBD_reqAlloc reqAlloc;
    CUSBD_reqFree reqFree;
}  CUSBD_epOps;

/**
 * struct containing function pointers for event notification callbacks issued
 * by isr().
 * Each call passes the driver's privateData pointer for instance
 * identification if necessary, and may also pass data related to the event.
*/
typedef struct CUSBD_Callbacks
{
    CUSBD_CbDisconnect disconnect;
    CUSBD_CbConnect connect;
    CUSBD_CbSetup setup;
    CUSBD_CdSuspend suspend;
    CUSBD_CbResume resume;
    CUSBD_CbUsbRequestMemAlloc usbRequestMemAlloc;
    CUSBD_CbUsbRequestMemFree usbRequestMemFree;
    CUSBD_CbbusInterval busInterval;
}  CUSBD_Callbacks;

/**
 *  @}
 */

/** @defgroup DriverObject Driver API Object
 *  API listing for the driver. The API is contained in the object as
 *  function pointers in the object structure. As the actual functions
 *  resides in the Driver Object, the client software must first use the
 *  global GetInstance function to obtain the Driver Object Pointer.
 *  The actual APIs then can be invoked using obj->(api_name)() syntax.
 *  These functions are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * API methods
 **********************************************************************/
typedef struct CUSBD_OBJ
{
    /**
     * Obtain the private memory size required by the driver
     * @param[out] sysReq returns the size of memory allocations required
     * @param[in] config driver/hardware configuration required
     * @return 0 on success (requirements structure filled)
     * @return ENOTSUP if configuration cannot be supported due to driver/hardware constraints
     */
    uint32_t (*probe)(CUSBD_Config* config, CUSBD_SysReq* sysReq);

    /**
     * Initialize the driver instance and state, configure the USB device
     * as specified in the 'config' settings, initialize locks used by
     * the driver.
     * @param[in] callbacks client-supplied callback functions
     * @param[in,out] config specifies driver/hardware configuration
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return ENOTSUP if hardware has an inconsistent configuration or doesn't support feature(s) required by 'config' parameters
     * @return ENOENT if insufficient locks were available (i.e. something allocated locks between probe and init)
     * @return EIO if driver encountered an error accessing hardware
     * @return EINVAL if illegal/inconsistent values in 'config'
     */
    uint32_t (*init)(void* pD, const CUSBD_Config* config, CUSBD_Callbacks* callbacks);

    /**
     * Destroy the driver (automatically performs a stop)
     * @param[in] pD driver state info specific to this instance
     */
    void (*destroy)(void* pD);

    /**
     * Start the GEM driver, enabling interrupts and PCS auto-
     * negotiation.
     * @param[in] pD driver state info specific to this instance
     */
    void (*start)(void* pD);

    /**
     * Stop the driver. This should disable the hardware, including its
     * interrupt at the source, and make a best-effort to cancel any
     * pending transactions.
     * @param[in] pD driver state info specific to this instance
     */
    void (*stop)(void* pD);

    /**
     * Driver ISR.  Platform-specific code is responsible for ensuring
     * this gets called when the corresponding hardware's interrupt is
     * asserted. Registering the ISR should be done after calling init,
     * and before calling start. The driver's ISR will not attempt to
     * lock any locks, but will perform client callbacks. If the client
     * wishes to defer processing to non-interrupt time, it is
     * responsible for doing so.
     * @param[in] pD driver state info specific to this instance
     */
    void (*isr)(void* pD);

    /**
     * Enable Endpoint.  This function should be called within
     * SET_CONFIGURATION(configNum > 0) request context. It configures
     * required hardware controller endpoint with parameters given in
     * desc.
     * @param[in] ep endpoint being configured
     * @param[in] pD driver state info specific to this instance
     * @param[in] desc endpoint descriptor
     * @return 0 on success
     * @return EINVAL if pD, ep or desc is NULL or desc is not a endpoint descriptor
     */
    uint32_t (*epEnable)(void* pD, CUSBD_Ep* ep, const CH9_UsbEndpointDescriptor* desc);

    /**
     * Disable Endpoint. Functions unconfigures hardware endpoint.
     * Endpoint will not respond to any host packets. This function
     * should be called within SET_CONFIGURATION(configNum = 0) request
     * context or on disconnect event. All queued requests on endpoint
     * are completed with ECANCELED status.
     * @param[in] ep endpoint being unconfigured
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*epDisable)(void* pD, CUSBD_Ep* ep);

    /**
     * Set halt or clear halt state on endpoint. When setting halt,
     * device will respond with STALL packet to each host packet. When
     * clearing halt, endpoint returns to normal operating.
     * @param[in] value if 1 sets halt, if 0 clears halt on endpoint
     * @param[in] ep endpoint being setting or clearing halt state
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EPERM if endpoint is disabled (has not been configured yet)
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*epSetHalt)(void* pD, CUSBD_Ep* ep, uint8_t value);

    /**
     * Set halt on endpoint. Function sets endpoint to permanent halt
     * state. State can not be changed even with epSetHalt(pD, ep, 0)
     * function. Endpoint returns automatically to its normal state on
     * disconnect event.
     * @param[in] ep endpoint being setting halt state
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EPERM if endpoint is disabled (has not been configured yet)
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*epSetWedge)(void* pD, CUSBD_Ep* ep);

    /**
     * Returns number of bytes in hardware endpoint FIFO. Function useful
     * in application where exact number of data bytes is required. In
     * some situation software higher layers must be aware of number of
     * data bytes issued but not transfered by hardware because of
     * aborted transfers, for example on disconnect event. *
     * @param[in] ep endpoint which status is to be returned
     * @param[in] pD driver state info specific to this instance
     * @return number of bytes in hardware endpoint FIFO
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*epFifoStatus)(void* pD, CUSBD_Ep* ep);

    /**
     * Flush hardware endpoint FIFO.
     * @param[in] ep endpoint which FIFO is to be flushed
     * @param[in] pD driver state info specific to this instance
     */
    void (*epFifoFlush)(void* pD, CUSBD_Ep* ep);

    /**
     * Submits IN/OUT transfer request to an endpoint.
     * @param[in] req request being submitted
     * @param[in] ep endpoint associated with the request
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD, ep, or req is NULL
     * @return EPERM if endpoint is not enabled
     * @return EPROTO only on default endpoint if endpoint is not in data stage phase
     */
    uint32_t (*reqQueue)(void* pD, CUSBD_Ep* ep, CUSBD_Req* req);

    /**
     * Dequeues IN/OUT transfer request from an endpoint. Function
     * completes all queued request with ECANCELED status.
     * @param[in] req request being dequeued
     * @param[in] ep endpoint associated with the request
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*reqDequeue)(void* pD, CUSBD_Ep* ep, CUSBD_Req* req);

    /**
     * Allocates transfer request object. Function returns address to
     * memory where request is casted.
     * @param[out] req memory space where request will be allocated
     * @param[in] ep endpoint for which request is being allocated
     * @param[in] pD driver state info specific to this instance
     * @return NULL if no available memory space
     * @return request pointer to CUSBD_Req empty object
     */
    uint32_t (*reqAlloc)(void* pD, CUSBD_Ep* ep, CUSBD_Req** req);

    /**
     * Frees memory occupied by request. While operating, when request
     * object will be no longer used, use reqFree function to free system
     * memory *
     * @param[in] req request being freed
     * @param[in] ep endpoint associated with the request
     * @param[in] pD driver state info specific to this instance
     */
    void (*reqFree)(void* pD, CUSBD_Ep* ep, CUSBD_Req* req);

    /**
     * Returns pointer to CUSBD object. CUSBD object is a logical
     * representation of USB device. CUSBD contains endpoint collection
     * accessed through epList field. Endpoints collection is organized
     * as double linked list.
     * @param[out] dev returns pointer to CUSBD instance
     * @param[in] pD driver state info specific to this instance
     */
    void (*getDevInstance)(void* pD, CUSBD_Dev** dev);

    /**
     * Returns number of frame. Some controllers have counter of SOF
     * packets or ITP packets in the Super Speed case. Function returns
     * value of this counter. This counter can be used for time
     * measurement. Single FS frame is 1 ms measured, for HS and SS is
     * 125us.
     * @param[out] numOfFrame returns number of USB frame
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD or numOfFrame is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dGetFrame)(void* pD, uint32_t* numOfFrame);

    /**
     * Wakes up host connected to this device.
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dWakeUp)(void* pD);

    /**
     * Sets the device self powered feature.
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dSetSelfpowered)(void* pD);

    /**
     * Clear the device self powered feature.
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dClearSelfpowered)(void* pD);

    /**
     * Switch VBUS ON or OFF.
     * @param[in] isActive if = 1 VBUS is ON, if = 0 VBUS is OFF
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dVbusSession)(void* pD, uint8_t isActive);

    /**
     * Draw VBUS with given current, real VBUS current should be twice
     * the value given in mA.
     * @param[in] mA VBUS maximal current
     * @param[in] pD driver state info specific to this instance.
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dVbusDraw)(void* pD, uint8_t mA);

    /**
     * Disables or enables pullups, which the host may see as disconnect
     * or connect *
     * @param[in] pD driver state info specific to this instance
     * @param[in] isOn if 1 device connected, if 0 device is disconnected from host
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dPullUp)(void* pD, uint8_t isOn);

    /**
     * Enables to add any specific extended commands for controlling
     * device. These command can be invoked from user application.
     * @param[in] code selected command's code
     * @param[in] param parameter associated with command
     * @param[in] pD driver state info specific to this instance.
     * @return 0 on success
     * @return EINVAL if pD is NULL
     * @return EOPNOTSUPP if feature is not supported
     */
    uint32_t (*dExecDebug)(void* pD, uint32_t code, uint32_t param);

    /**
     * Returns configuration parameters: U1 exit latency and U2 exit
     * latency Function useful only in Super Speed mode.
     * @param[out] configParams pointer to CH9_ConfigParams structure
     * @param[in] pD driver state info specific to this instance
     */
    void (*dGetConfigParams)(void* pD, CH9_ConfigParams* configParams);
    void (*print_reg)(void* pD);
    void (*suspend)(void* pD, uint8_t methord);
    void (*resume)(void* pD, uint8_t methord);
    void (*reset)(void* pD, uint8_t methord);
} CUSBD_OBJ;

/**
 * In order to access the CUSBD APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CUSBD_OBJ* Driver Object Pointer
 */
extern CUSBD_OBJ *CUSBD_GetInstance(void);

/**
 *  @}
 */


#endif	/* _CUSBD_H_ */
