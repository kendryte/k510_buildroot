/**********************************************************************
 * Copyright (C) 2014-2016 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * cusb_dma_if.h
 * Interface for Cadence DMA controllers family drivers dedicated for
 * Cadence USB controllers.
 * This header file lists the API providing a HAL (hardware abstraction
 * layer) interface for the Cadence USB device controller's family.
 * This interface is used by Cadence USB device controllers and rather
 * should be used internally by tese drivers
 ***********************************************************************/
#ifndef CUSB_DMA_IF_H
#define CUSB_DMA_IF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cdn_stdtypes.h"


/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification, and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**
 * structure helpful when object are organized in  linked list
*/
typedef struct CUSBDMA_ListHead
{
    /** pointer to next element in list */
    struct CUSBDMA_ListHead* next;
    /** pointer to previous element in list */
    struct CUSBDMA_ListHead* prev;
}  CUSBDMA_ListHead;

/**DMA Channel Status available values*/
typedef enum {
    /**channel unallocated*/
    CUSBDMA_STATUS_UNKNOW,
    /**channel allocated but not busy, no errors*/
    CUSBDMA_STATUS_FREE,
    /**DMA error or USB error - transfer aborted*/
    CUSBDMA_STATUS_ABORT,
    /**channel busy - transfer in progress*/
    CUSBDMA_STATUS_BUSY,
    /**DMA has been armed and Dorbell or DMA BUSY bit is still set.
       If those bits are set it indicate that DMA is armed and data
       has not been transfered yet
    */
    CUSBDMA_STATUS_ARMED
} CUSBDMA_Status;

/** Configuration of DMA.
 *  Object of this type is used for probe and init functions when checking
 *  memory requirements of device object and for hardware controller configuration.
 *  Size of device object in bytes is returned on probe function call in
 *  CUSBDMA_SysReq.privDataSize field.
 */
typedef struct {
    /** base address of DMA special function register */
    uintptr_t regBase;
    /* field holds information about DMA mode.
     * DMA mode can be programmed globally for all channels or individually for particular channels.
     * Each bit of dmaModeTx field is responsible for one DMA channel. If this field will be set to
     * 0xFFFF  or 0xFFFF for both dmaModeTx and dmaModeRx then DMA mode will be programmed globally,
     * elsewhere each DMA channel will be programmed individually in channelAlloc function.
     * Meanings of bits:  0 DMA Single Mode
     *                    1 DMA DMULT Mode
     */
    uint16_t dmaModeTx;
    /* field holds information about DMA mode.
     * DMA mode can be programmed globally for all channels or individually for particular channels.
     * Each bit of dmaModeTx field is responsible for one DMA channel. If this field will be set to
     * 0xFFFF  or 0xFFFF for both dmaModeTx and dmaModeRx then DMA mode will be programmed globally,
     * elsewhere each DMA channel will be programmed individually in channelAlloc function.
     * Meanings of bits:  0 DMA Single Mode
     *                    1 DMA DMULT Mode
     */
    uint16_t dmaModeRx;
    /** pointer to virtual memory for TRBs buffer */
    void * trbAddr;
    /** Address of to physical memory for TRBs buffer */
    uintptr_t trbDmaAddr;
} CUSBDMA_Config;

/** System requirements returned by probe */
typedef struct {
    /** size of memory required for driver's private data*/
    uint32_t privDataSize;
    /** size of memory required for USB Transfer Request Descriptors.
     * This memory will be used by DMA controller,
     *  so it should be suitable for DMA operation.*/
    uint32_t trbMemSize;
} CUSBDMA_SysReq;

/******************************************************************************
 * Client-defined Driver Callback Functions
 *****************************************************************************/

/**
 * Callback called when DMA request transfer has been finished.
 * Params:
 * pD - private data for parent driver
 * epNum - number of USB endpoint for which transfer has been finished
 * dir - endpoint direction for finished DMA request

 */
typedef void (*CUSBDMA_CbDmaComplete)(void *pD, uint8_t epNum, uint8_t dir);

/**
 * struct containing function pointers for event notification callbacks issued
 * by isr().
 * Each call passes the driver's privateData pointer for instance
 * identification if necessary, and may also pass data related to the event.
 */
typedef struct {
    // gadget events
    CUSBDMA_CbDmaComplete complete;
} CUSBDMA_Callbacks;

/**
 *  @}
 */

/** @defgroup DriverObject Driver API Object
 * API listing for the DMA Driver. The API is contained in the object as
 * function pointers in the object structure. As the actual functions
 * resides in the Driver Object, the client software must first
 * use the global GetInstance function to obtain the Driver Object Pointer.
 * The actual APIs then can be invoked using obj->(api name)( ) syntax.
 * These functions are defined in the header file of the core driver
 * and utilized by the API.
 * @{
 */
typedef struct {
    /**
     * Obtain the private memory size required by the driver
     * @param[in] config driver/hardware configuration required
     * @param[out] sysReq returns the size of memory allocations required
     * @return 0 on success (requirements structure filled)
     * @return ENOTSUP if configuration cannot be supported due to
     *    driver/hardware constraints
     */
    uint32_t (*probe)(CUSBDMA_Config* config, CUSBDMA_SysReq * sysReq);

    /**
     * Initialize the driver instance and state, configure the USB device
     * as specified in the 'config' settings, initialize locks used by the
     * driver.
     * @param[in] pD driver state info specific to this instance
     * @param[in,out] config specifies driver/hardware configuration
     * @param[in] callbacks client-supplied callback functions
     * @return 0 on success
     * @return EINVAL if config or callbacks is NULL
     * @return EINVAL if illegal/inconsistent values in 'config'
     * @return EIO if driver encountered an error accessing hardware
     * @return ENOTSUP if hardware has an inconsistent configuration or
     *    doesn't support feature(s) required by 'config' parameters
     * @return ENOENT if insufficient locks were available (i.e. something
     *    allocated locks between probe and init)
     * $VALIDFAIL if (config.regBase==0) $EXPECT_RETURN EINVAL $
     */

    uint32_t (*init)(void *pD, const CUSBDMA_Config* config,
            CUSBDMA_Callbacks * callbacks);

    /**
     * Destroy the driver (automatically performs a stop)
     * @param[in] pD driver state info specific to this instance
     */
    void (*destroy)(void *pD);

    /**
     * Start the DMA driver, enabling interrupts.
     * @param[in] pD driver state info specific to this instance
     */
    uint32_t (*start)(void * pD);

    /**
     * Stop the driver.
     * This should disable the hardware, including its interrupt at the source,
     * and make a best-effort to cancel any pending transactions.
     * @param[in] pD driver state info specific to this instance
     */
    uint32_t (*stop)(void * pD);

    /**
     * Driver ISR.  Platform-specific code is responsible for ensuring this
     * gets called when the corresponding hardware's interrupt is asserted.
     * Registering the ISR should be done after calling init, and before calling
     * start. The driver's ISR will not attempt to lock any locks,
     * but will perform client callbacks.
     * If the client wishes to defer processing to non-interrupt time,
     * it is responsible for doing so.
     * @param[in] pD driver state info specific to this instance
     */
    void (*isr)(void *pD);

    /* DMA specific functions */

    /**
     * Error interrupt handling function. This is additional interrupt handling function used only by
     * USB Host controller.
     * Registering the ISR should be done after calling init, and before calling
     * start. The driver's ISR will not attempt to lock any locks,
     * but will perform client callbacks.
     * If the client wishes to defer processing to non-interrupt time,
     * it is responsible for doing so.
     * @param[in] pD driver state info specific to this instance
     * @param[in] epNum raised interrupt number
     * @param[in] isDirTx direction for raised interrupt.
     */
    void (*errIsr)(void * pD, uint8_t irqNr, uint8_t isDirTx);

    /**
     * Allocation the DMA channel.
     * @param[in] pD driver state info specific to this instance
     * @param[in] isDirTx direction for allocated channel
     * @param[in] hwEpNum USB endpoint number for allocated channel
     * @param[in] isIso allocate channel for Isochronous transfer
     * @return pointer to DMA channel on success
     * @return NULL if illegal/inconsistent values in parameters
     */
    void * (*channelAlloc)(void * pD, uint8_t isDirTx, uint8_t hwEpNum, uint8_t isIso);

    /**
     * Release the DMA channel.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel
     * @return 0 on success
     * @return EINVAL if illegal/inconsistent values in parameters
     */
    uint32_t (*channelRelease)(void * pD, void *channel);
    /**
     *
     */

    /**
     * Prepare transfer and starts it.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which transfer will be started
     * @param[in] packetSize Maximal Packet Size for USB endpoint
     * @param[in] dmaAddr address of buffer data prepared for DMA transfer
     * @param[in] len  data length in bytes to transfer by DMA
     * @param[in] framesDesc pointer to array describing transaction frames.
     *           Each element of this array should contain from two fields:
     *           packetLength that indicates length of packet that  will be
     *           transfered/received by ADMA module and offset that indicates
     *           offset in data buffer where data packet should starts.
     *           Both field shall be uint32_t type.
     *           framesDesc and framesNumber parameters are only intended for
     *           Isoc transfer working in DMULT mode and should not be used
     *           for other transfer types. For other transfer then Isoc in DMULT
     *           mode this parameter shoudl be set to NULL.
     * @param[in] framesNumber the Number of packet in frameDesc array.
     *           framesDesc and framesNumber parameters are only intended for
     *           Isoc transfer working in DMULT mode and should not be used
     *           for other transfer types. For other transfer then Isoc in DMULT
     *           mode parameter shoudl be set to 0.
     * @return 0 on success
     * @return EINVAL if illegal/inconsistent values in parameters
     * @return ENOMEM if DMA channel has no free memory for TRB
     */
    uint32_t (*channelProgram)(void * pD, void *channel, uint16_t packetSize,
            uintptr_t dmaAddr, uint32_t len, void * framesDesc, uint32_t framesNumber);

    /**
     * Abort DMA transfer for given DMA channel.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which transfer will be aborted
     * @return 0 on success
     * @return EINVAL if illegal/inconsistent values in parameters
     */
    uint32_t (*channelAbort)(void * pD, void *channel);

    /**
     * Get status for given channel.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which channel status is requested
     * @return DMA_STATUS_UNKNOW if channel is unallocated
     * @return DMA_STATUS_FREE if channel is allocated but not busy
     * @return DMA_STATUS_BUSY if DMA transfer is in progress
     * @return DMA_STATUS_ABORT if DMA or USB errror - transfer aborted
     * @return EINVAL if illegal/inconsistent values in parameters
     */
    CUSBDMA_Status (*getChannelStatus)(void * pD, void * channel);

    /**
     * Get status for given channel.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which actual length is requested
     * @return number of actual transmitted bytes by given DMA channel
     */
    uint32_t (*getActualLength)(void * pD, void * channel);

    /**
     * Get maximum number of bytes that can be prepared for single TD.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which maximum number of bytes is requested
     * @return  maximum number bytes that can be transmitted for single TD
     */
    uint32_t (*getMaxLength)(void * pD, void * channel);

    /**
     * Set maximum number of bytes that can be prepared for single TD.
     * @param[in] pD driver state info specific to this instance
     * @param[in] channel pointer to DMA channel for which maximum number of bytes is requested
     * @param[in] val number of bytest for single TD
     * @return EINVAL if illegal/inconsistent values in parameters
     */
    uint32_t (*setMaxLength)(void * pD, void * channel, uint32_t val);

    /**
     * Set private data for parent driver which will be used this DMA driver.
     * This private data will be passed as first parameter in callback functions.
     * @param[in] pD driver state info specific to this instance
     * @param[in] parent pointer to private data for parent of DMA driver.
     * @return 0 on success
     * @return EINVAL if illegal/inconsistent values in parameters
     */
    void (*setParentPriv)(void * pD, void * parent);

    /**
     * Reset DMA Controller.
     * This function should be called after disconnecting USB Device and before first using
     * DMA transfer.
     * @param[in] pD driver state info specific to this instance
     */
    void (*controllerReset)(void * pD);

    /**
     * Inform DMA driver that controller work in Host mode. By default after initialization and
     * after controllerReset()  DMA will assume that controller works in Device Mode.
     * @param[in] pD driver state info specific to this instance
     */
    void (*setHostMode)(void * pD);
    void (*print_reg)(void * pD);
} CUSBDMA_OBJ;

extern CUSBDMA_OBJ * CUSBDMA_GetInstance(void);

#endif
