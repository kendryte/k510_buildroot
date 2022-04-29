/**********************************************************************
 * Copyright (C) 2015-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          Do not edit it manually.
 **********************************************************************
 * cusbh_if.h
 * Interface for Cadence USB Embedded Host and USB OTG controllers
 * family drivers This header file lists the API providing a HAL
 * (hardware abstraction layer) interface for the Cadence USB
 * controller's family. If driver supports support
 **********************************************************************/

#ifndef _CUSBH_H_
#define _CUSBH_H_

#include "cdn_stdtypes.h"
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
struct CUSBH_ListHead;
struct CUSBH_EpConfig;
struct CUSBH_Config;
struct CUSBH_SysReq;
struct CUSBH_Device;
struct CUSBH_Ep;
struct CUSBH_IsoFramsDesc;
struct CUSBH_Req;
struct CUSBH_Callbacks;

/**********************************************************************
 * Enumerations
 **********************************************************************/
typedef enum
{
    CUSBH_ESTALL = 1,
    CUSBH_EUNHANDLED = 2,
    CUSBH_ESHUTDOWN = 4,
} CUSBH_ErrorCodes;

typedef enum
{
    CUSBH_OTG_STATE_A_IDLE = 0,
    CUSBH_OTG_STATE_A_WAIT_VRISE = 1,
    CUSBH_OTG_STATE_A_WAIT_BCON = 2,
    CUSBH_OTG_STATE_A_HOST = 3,
    CUSBH_OTG_STATE_A_SUSPEND = 4,
    CUSBH_OTG_STATE_A_PERIPHERAL = 5,
    CUSBH_OTG_STATE_A_VBUS_ERR = 6,
    CUSBH_OTG_STATE_A_WAIT_VFALL = 7,
    CUSBH_OTG_STATE_B_IDLE = 8,
    CUSBH_OTG_STATE_B_PERIPHERAL = 9,
    CUSBH_OTG_STATE_B_WAIT_ACON = 10,
    CUSBH_OTG_STATE_B_HOST = 11,
} CUSBH_OtgState;

/**********************************************************************
 * Callbacks
 **********************************************************************/
/**
 * Callback called when status port for Virtual Hub will be changed.
 * This callback informs host application that some changes has occurred on
 * USB port, but not define any detailed information.
 * To gets detailed information about port status application should send
 * request to Virtual Hub by means of vhubControl function.
*/
typedef void (*CUSBH_PortStatusChange)(void* pD);

/**
 * Callback called by CUSBH driver to gets information about toggle bit for
 * device connected to host that is described by usbDev object and endpoint
 * number and direction. For host mode information about toggle bits has to
 * be held by host application for all connected USB devices.
*/
typedef uint8_t (*CUSBH_UsbGetEpToggle)(void* pD, struct CUSBH_Device* usbDev, uint8_t epNum, uint8_t isIn);

/**
 * Callback called by CUSBH driver to informs user application about new value of toggle bit for
 * attached device described by usbDev object. Parameters epNum and isIn informs about endpoint number
 * and direction for that toggle bit should be updated. Last parameter toggle hold new value.
*/
typedef void (*CUSBH_UsbSetEpToggle)(void* pD, struct CUSBH_Device* usbDev, uint8_t epNum, uint8_t isIn, uint8_t toggle);

/**
 * Reports request complete callback.
 * Params:
 * pD - driver state info specific to this instance
 * usbReq - request which has been completed
 * status - status of the completed request
*/
typedef void (*CUSBH_UsbGivbackRequest)(void* pD, struct CUSBH_Req* usbReq, uint32_t status);

/**
 * Reports changing state of OTG machine. Function is called from interrupt context so have to
 * be used carefully and can be used as a means for communication messages to the user about actual
 * state of OTG state machine.
 * Params:
 * pD - driver state info specific to this instance
 * otgSate - actually state of OTG machine
*/
typedef void (*CUSBH_UsbOtgStateChange)(void* pD, CUSBH_OtgState otgSate);

/**
 * Function starts or stops timer. If timer already has been started then it should be restarted.
 * Params:
 * pD - driver state info specific to this instance
 * time - required time in millisceconds. If time is different then 0 then timer should be starterd else should be stoped.
 * id - timer identifier
*/
typedef void (*CUSBH_UsbSetTimer)(void* pD, uint32_t time, uint8_t id);

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** structure helpful when object are organized in linked list */
typedef struct CUSBH_ListHead
{
    /** Pointer to next element in List */
    struct CUSBH_ListHead* next;
    /** Pointer to previous element in list */
    struct CUSBH_ListHead* prev;
}  CUSBH_ListHead;

/**
 * Configuration structure for single endpoint.
 * Single endpoint configuration structure object is a part of CUSBH_Config
 * object used for configuration of whole USB device
*/
typedef struct CUSBH_EpConfig
{
    /**
     * buffering value
     * It is a number of hardware (on-chip) memory buffer used for queuing
     * USB packets. Setting bufferingValue to 0 means that endpoint is disabled
     * Setting bufferingValue to 1 it sets number of on-chip buffer to 1 and
     * so on.
    */
    uint8_t bufferingValue;
    /** On chip buffer address for hardware Endpoint. Only for USBHS-OTG-SD */
    uint16_t startBuf;
    /** Maximum USB packet size for hardware endpoint. */
    uint16_t maxPacketSize;
}  CUSBH_EpConfig;

/**
 * Configuration of device.
 * Object of this type is used for probe and init functions when checking
 * memory requirements of device object and for hardware controller configuration.
 * Size of device object in bytes is returned on probe function call in
 * CUSBD_SysReq.privDataSize field.
*/
typedef struct CUSBH_Config
{
    /** base address of device controller registers */
    uintptr_t regBase;
    /** table of endpoint configuration objects for IN direction */
    struct CUSBH_EpConfig epIN[16];
    /** table of endpoint configuration objects for OUT direction */
    struct CUSBH_EpConfig epOUT[16];
    /**
     * hardware feature enabling DMA operation in scatter/gather mode
     * 1 - enabled, 0 disabled. At this moment driver supports only
     * DMULT mode.
    */
    uint8_t dmultEnabled;
    /**
     * memory buffers alignment required by hardware controller
     * for 64 bit of controller's DMA version set this to 8
     * for 32 bit set this to 4
     * USB DMA is capable of transferring data starting only at
     * aligned address. Otherwise an TRB_ERROR interrupt will be generated
     * by DMA core
    */
    uint8_t memoryAlignment;
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
    /** pointer to physical memory for TRBs buffer */
    void* trbAddr;
    /** pointer to virtual memory for TRBs buffer */
    uintptr_t trbDmaAddr;
}  CUSBH_Config;

/** System requirements returned by probe */
typedef struct CUSBH_SysReq
{
    /** size of memory required for driver's private data */
    uint32_t privDataSize;
    /**
     * size of memory required for USB Transfer Request Descriptors.
     * This memory will be used by DMA controller,
     * so it should be suitable for DMA operation.
    */
    uint32_t trbMemSize;
}  CUSBH_SysReq;

/**
 * Structure represents single USB device connected to host.
 * If host supports hubs then Host can have connected many USB devices
 * through USB hubs.
 * CUSBH_Device structure holds only fields necessary in CUSBH driver and one field
 * that makes possible extend this structure to more complex.This additional field
 * is userExt.
*/
typedef struct CUSBH_Device
{
    /** USB Device address connected to Host */
    uint8_t devnum;
    /** Current speed of USB device */
    CH9_UsbSpeed speed;
    /** Hub port to which this device is connected */
    uint8_t hubPort;
    /** Parent device object. */
    struct CUSBH_Device* parrent;
    /**
     * Fields used for holding private data for USB Host controller.
     * This field should not be changed by higher layers
    */
    void* hcPriv;
    /**
     * private data for user application. In this field higher layer can hold
     * other, more complex request structure. By mans of this field higher
     * layer can extend this object and makes possible connect driver to OS
    */
    void* userExt;
}  CUSBH_Device;

/**
 * Structure represents single USB Endpoint associated with Interface
 * belonging to USB device connected to host.
 * CUSBH_Device structure holds only fields necessary in CUSBH driver and one field
 * that makes possible extend this structure to more complex.This additional field
 * is userExt.
*/
typedef struct CUSBH_Ep
{
    /**
     * USB_ENDPOINT_DESCRIPTOR hold information about endpoint.
     * This information is part of whole USB Configuration Descriptor
    */
    struct CH9_UsbEndpointDescriptor epDesc;
    /** This is head of queue holding all requests directed for this endpoint */
    struct CUSBH_ListHead reqList;
    /**
     * private data for user application. In this field higher layer can hold
     * other, more complex request structure. By mans of this field higher
     * layer can extend this object and makes possible connect driver to OS
    */
    void* userExt;
    /**
     * Fields used for holding private data for USB Host controller.
     * This field should not be modified by higher layers. Host driver needs
     * some memory for this private field so higher layers are responsible
     * for allocation of this memory. This allocation was delegated to upper
     * layers in order to eliminates the need allocate memory by CUSBH component.
     * The size of memory required for private data can be obtained by means
     * of epGetPirvateDataSize API function. This memory can't be reserved during
     * initialization process because driver has no knowledge about memory that
     * will be needed for this purpose.
    */
    uint8_t* hcPriv;
}  CUSBH_Ep;

/**
 * Describes information about Isochronous packet that will be sent or received.
 * In ISOC transfer each packet can have different legnth so it need special
 * treatment.
*/
typedef struct CUSBH_IsoFramsDesc
{
    /**
     * For IN (RX) isochronous transfer this field holds information about received length of packet,
     * and for OUT (TX) direction this field inicate length of submiting frame
    */
    uint32_t length;
    /**
     * For IN (RX) direction this field indicates inital address in buffer where received packet should
     * be placed and for OUT (TX) direction this field indicates starting address in buffer for sending
     * packet
    */
    uint32_t offset;
}  CUSBH_IsoFramsDesc;

/**
 * Transfer request structure.
 * I/O transfers of higher layers are realized with the help of CUSBH_Req
 * objects. CUSBH_Req is associated with software endpoints, and software
 * endpoint is associated with connected USB device. If host support hubs
 * then host can have connected many USB device through hubs. Each connected
 * device can have many configuration which in turn can support many interfaces.
 * Each USB interface can consist many endpoints.
 * CUSBH_Req structure holds only fields necessary in CUSBH driver and one field
 * that makes possible extend this structure to more complex.This additional field
 * is userExt.
 * This structure is only structure that can be used to sends or receives data from
 * USB bus. It can be for CONTROL, BULK, INTERRUPT and ISOCHRONOUS transfer.
*/
typedef struct CUSBH_Req
{
    /**
     * This field is used to link request to queue of requests associated with
     * host endpoint
    */
    struct CUSBH_ListHead list;
    /**
     * Pointer to object representing endpoint associated with this transfer.
     * This structure represents single USB endpoint belonging to USB device
     * connected to host
    */
    struct CUSBH_Ep* usbEp;
    /**
     * private data for user application. In this field higher layer can hold
     * other, more complex request structure. By mans of this field higher
     * layer can extend this object and makes possible connect driver to OS
    */
    void* userExt;
    /**
     * Fields used for holding private data for USB Host controller.
     * This field should not be changed by higher layers
    */
    void* hcPriv;
    /** Pointer to object representing USB device which is associated with this request */
    struct CUSBH_Device* usbDev;
    /** Pointer to Setup packet for CONTROL transfer */
    struct CH9_UsbSetup* setup;
    /**
     * Physical address of Setup buffer prepared for DMA transfer.
     * This address should be aligned to 8 bytes
    */
    uintptr_t setupDma;
    /** buffer with/on data to transfer */
    void* bufAddress;
    /**
     * Physical address of Data buffer prepared for DMA transfer.
     * This address should be aligned to 8 bytes
    */
    uintptr_t buffDma;
    /** The transfer data length */
    uint32_t buffLength;
    /** Actually transfered data */
    uint32_t actualLength;
    /**
     * //Pipe Information
     * Direction:
     * 1 - host get data from device
     * 0 - host send data to device
    */
    uint8_t epIsIn;
    /** Endpoint type */
    uint8_t epType;
    /** Endpoint number - valid values are 0 - 15 */
    uint8_t epNum;
    /** function address - valid values are 0 - 127 */
    uint8_t faddress;
    /** Interval between packets. Only for INTERRUPT and ISOCHRONOUS transfers */
    uint8_t interval;
    /** Status of this request. */
    uint8_t status;
    /** CUSBH_Req was unlinked from queue */
    uint8_t reqUnlinked;
    /**
     * Pointer to array of CUSBH_IsoFramsDesc that describes Iso packets.
     * This table has to be allocated by user application.
    */
    struct CUSBH_IsoFramsDesc* isoFramesDesc;
    /** Number of Iso frames in isoFramesDesc array that will be send by CoreDriver. */
    uint32_t isoFramesNumber;
}  CUSBH_Req;

/**
 * struct containing function pointers for communication CUSBH driver with higher layers.
 * Each call passes the driver's privateData pointer for instance
 * identification if necessary, and may also pass data related to the event.
*/
typedef struct CUSBH_Callbacks
{
    CUSBH_PortStatusChange portStatusChange;
    CUSBH_UsbGetEpToggle getEpToggle;
    CUSBH_UsbSetEpToggle setEpToggle;
    CUSBH_UsbGivbackRequest givbackRequest;
    CUSBH_UsbOtgStateChange otgStateChange;
    CUSBH_UsbSetTimer setTimer;
    /**
     * Callbacks for Device mode if it is supported
     * This field is needed in order to configures and initializes CUSBD driver
     * For more information see API for CUSBD component.
    */
    void* usbDevCallbacks;
}  CUSBH_Callbacks;

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
typedef struct CUSBH_OBJ
{
    /**
     * Obtain the private memory size required by the driver
     * @param[out] sysReq returns the size of memory allocations required
     * @param[in] config driver/hardware configuration required
     * @return 0 on success (requirements structure filled)
     * @return ENOTSUP if configuration cannot be supported due to driver/hardware constraints
     */
    uint32_t (*probe)(CUSBH_Config* config, CUSBH_SysReq* sysReq);

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
    uint32_t (*init)(void* pD, const CUSBH_Config* config, CUSBH_Callbacks* callbacks);

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
     * Disables software USB endpoint and abort any request queued for
     * this endpoint. CUSBH_Ep object represent software endpoint so,
     * after disabling it hardware endpoint can be also used by other
     * software endpoints. In host mode one hardware endpoint can
     * handling transfer for many software endpoints. During disabling
     * endpoint for all requests queued for this endpoint will be called
     * callback function with request->status field set to  UHC_ESHUTDOWN
     * *
     * @param[in] ep pointer to software endpoint being disable
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD or ep is NULL
     */
    uint32_t (*epDisable)(void* pD, CUSBH_Ep* ep);

    /**
     * Submits IN/OUT transfer request to driver. Driver queue this
     * request and will schedule transfer for it. *
     * @param[in] req sending USB request.
     * @param[in] pD driver state info specific to this instance
     * @return 0 if request will be queued successfully
     * @return ENODEV if controler not work in Host mode
     * @return EINVAL if pD or req is NULL
     */
    uint32_t (*reqQueue)(void* pD, CUSBH_Req* req);

    /**
     * Dequeues IN/OUT transfer request from driver. Function completes
     * all queued request with ECANCELED status *
     * @param[in] status Status for dequeued USB request
     * @param[in] req Sending USB request.
     * @param[in] pD driver state info specific to this instance
     * @return 0 if request will be queued successfully
     * @return EINVAL if pD or req is NULL
     */
    uint32_t (*reqDequeue)(void* pD, CUSBH_Req* req, uint32_t status);

    /**
     * Get information about changing status for USB port for Virtual
     * Hub. User application can request this information in order to
     * check if something has happened on USB ports. *
     * @param[out] status hold information about changes for particular supported ports.
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EINVAL if pD or status is NULL
     */
    uint32_t (*vhubStatusData)(void* pD, uint8_t* status);

    /**
     * @param[in] setup
     * @param[in] pD
     * @param[in] buff
     */
    uint32_t (*vhubControl)(void* pD, CH9_UsbSetup* setup, uint8_t* buff);

    /**
     * Enables to add any specific extended commands for controlling
     * device. These command can be invoked from user application. *
     * @param[in] code selected command's code
     * @param[in] param parameter associated with command
     * @param[in] pD driver state info specific to this instance
     * @return 0 on success
     * @return EOPNOTSUPP if feature is not supported
     * @return EINVAL if pD is NULL
     */
    uint32_t (*execDebug)(void* pD, uint8_t code, uintptr_t param);

    /**
     * Gets private data pointer to CUSBD driver if it is supported. For
     * dual role USB controllers CUSBH driver is responsible for creating
     * and initializing CUSBD driver. In this case User application do
     * not have direct access to private data for CUSBD driver, so
     * application can obtain this pointer by means of getDevicePD
     * function. *
     * @param[in] pD driver state info specific to this instance
     * @return NULL if pD is NULL or when CUSBH driver not support device mode.
     * @return pointer to CUSBD private data on success
     */
    void* (*getDevicePD)(void* pD);

    /**
     * Gets size of memory needed internally by driver to CUSBH_Ep
     * object. Higher layer are responsible for allocating this memory
     * for every created CUSBH_Ep object. This additional memory should
     * be assigned to hcPriv field of CUSBH_Ep object. IF this filed will
     * not be properly initialized it can lead to unexpected and hard to
     * debugging bugs. *
     * @param[in] pD driver state info specific to this instance
     * @return number of memory bytes required for CUSBH_Ep->hcPriv field.
     */
    uint32_t (*epGetPirvateDataSize)(void* pD);

    /**
     * Checks if CUSBH driver works in Device mode
     * @param[in] pD driver state info specific to this instance
     * @return 1 if device works in Device mode
     */
    uint8_t (*isDeviceMode)(void* pD);

    /**
     * Checks if CUSBH driver works in Host mode
     * @param[in] pD driver state info specific to this instance
     * @return 1 if device works in Host mode
     */
    uint8_t (*isHostMode)(void* pD);

    /**
     * Function for handling timer events. Function should be called from
     * timer interrupt context.  Some functionality of CUSBH driver need
     * timer measurement. Initialization  and handling of timer is
     * platform specifc and may be different  on different platforms.
     * Driver callback function setTimer allows CUSBH driver  to start
     * and stop timer. *
     * @param[in] id timer identification number
     * @param[in] pD
     * @return 0 on success
     * @return EINVAL if timer events was not handled by CUSBH Driver
     */
    uint8_t (*timerEvents)(void* pD, uint8_t id);
    void (*print_reg)(void* pD);
} CUSBH_OBJ;

/**
 * In order to access the CUSBH APIs, the upper layer software must call
 * this global function to obtain the pointer to the driver object.
 * @return CUSBH_OBJ* Driver Object Pointer
 */
extern CUSBH_OBJ *CUSBH_GetInstance(void);

/**
 *  @}
 */


#endif	/* _CUSBH_H_ */
