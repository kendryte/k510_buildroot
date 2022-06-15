/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _V4L2_H_
#define _V4L2_H_

#include <stdbool.h>
#include <linux/videodev2.h>

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * struct v4l2_video_buffer - Video buffer information
 * @index: Zero-based buffer index, limited to the number of buffers minus one
 * @size: Size of the video memory, in bytes
 * @bytesused: Number of bytes used by video data, smaller or equal to @size
 * @error: True if an error occured while capturing video data for the buffer
 * @mem: Video data memory
 */
struct v4l2_video_buffer
{
	unsigned int index;
	unsigned int size;
	unsigned int bytesused;
	bool error;
	void *mem;
};

struct v4l2_device
{
	int fd;

	enum v4l2_buf_type type;
	enum v4l2_memory memtype;

	struct list_entry formats;
	struct v4l2_pix_format format;

	unsigned int nbufs;
	struct v4l2_video_buffer *buffers;
};

/*
 * v4l2_open - Open a V4L2 device
 * @devname: Name (including path) of the device node
 *
 * Open the V4L2 device referenced by @devname for video capture or display in
 * non-blocking mode.
 *
 * If the device can be opened, query its capabilities and enumerates frame
 * formats, sizes and intervals.
 *
 * Return a pointer to a newly allocated v4l2_device structure instance on
 * success and NULL on failure. The returned pointer must be freed with
 * v4l2_close when the device isn't needed anymore.
 */
struct v4l2_device *v4l2_open(const char *devname);

/*
 * v4l2_close - Close a V4L2 device
 * @dev: Device instance
 *
 * Close the device instance given as argument and free allocated resources.
 * Access to the device instance is forbidden after this function returns.
 */
void v4l2_close(struct v4l2_device *dev);
/*
 * v4l2_get_format - Retrieve the current pixel format
 * @dev: Device instance
 * @format: Pixel format structure to be filled
 *
 * Query the device to retrieve the current pixel format and frame size and fill
 * the @format structure.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_get_format(struct v4l2_device *dev, struct v4l2_pix_format *format);

/*
 * v4l2_set_format - Set the pixel format
 * @dev: Device instance
 * @format: Pixel format structure to be set
 *
 * Set the pixel format and frame size stored in @format. The device can modify
 * the requested format and size, in which case the @format structure will be
 * updated to reflect the modified settings.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_set_format(struct v4l2_device *dev, struct v4l2_pix_format *format);

/*
 * v4l2_alloc_buffers - Allocate buffers for video frames
 * @dev: Device instance
 * @memtype: Type of buffers
 * @nbufs: Requested number of buffers
 *
 * Allocate @nbufs buffers to store video frames. The device can modify the
 * number of buffers depending on its needs. The number of allocated buffers
 * will be stored in the @dev::nbufs field.
 *
 * When @memtype is set to V4L2_MEMORY_MMAP the buffers are allocated by the
 * driver and mapped to userspace. When @memtype is set to V4L2_MEMORY_USERPTR
 * the driver only allocates buffer objects and relies on the application to
 * provide memory storage for video frames.
 *
 * Upon successful allocation the @dev::buffers field points to an array of
 * allocated buffers.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_alloc_buffers(struct v4l2_device *dev, enum v4l2_memory memtype,
		       unsigned int nbufs);

/*
 * v4l2_free_buffers - Free buffers
 * @dev: Device instance
 *
 * Free buffers previously allocated by v4l2_alloc_buffers(). If the buffers
 * have been allocated with the V4L2_MEMORY_USERPTR memory type only the buffer
 * objects are freed, and the caller is responsible for freeing the video frames
 * memory if required.
 *
 * When successful this function sets the @dev::nbufs field to zero and the
 * @dev::buffers field to NULL.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_free_buffers(struct v4l2_device *dev);

/*
 * v4l2_queue_buffer - Queue a buffer for video capture/output
 * @dev: Device instance
 * @buffer: Buffer to be queued
 *
 * Queue the buffer identified by @buffer for video capture or output, depending
 * on the device type.
 *
 * The caller must initialize the @buffer::index field with the index of the
 * buffer to be queued. The index is zero-based and must be lower than the
 * number of allocated buffers.
 *
 * For V4L2_MEMORY_USERPTR buffers, the caller must initialize the @buffer::mem
 * field with the address of the video frame memory, and the @buffer:length
 * field with its size in bytes. For optimal performances the address and length
 * should be identical between v4l2_queue_buffer() calls for a given buffer
 * index.
 *
 * For video output, the caller must initialize the @buffer::bytesused field
 * with the size of video data. The value should differ from the buffer length
 * for variable-size video formats only.
 *
 * Upon successful return the buffer ownership is transferred to the driver. The
 * caller must not touch video memory for that buffer before calling
 * v4l2_dequeue_buffer(). Attempting to queue an already queued buffer will
 * fail.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_queue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer);

/*
 * v4l2_dequeue_buffer - Dequeue the next buffer
 * @dev: Device instance
 * @buffer: Dequeued buffer data to be filled
 *
 * Dequeue the next buffer processed by the driver and fill all fields in
 * @buffer. 
 *
 * This function does not block. If no buffer is ready it will return
 * immediately with -EAGAIN.
 *
 * If an error occured during video capture or display, the @buffer::error field
 * is set to true. Depending on the device the video data can be partly
 * corrupted or complete garbage.
 *
 * Once dequeued the buffer ownership is transferred to the caller. Video memory
 * for that buffer can be safely read from and written to.
 *
 * Return 0 on success or a negative error code on failure. An error that
 * results in @buffer:error being set is not considered as a failure condition
 * for the purpose of the return value.
 */
int v4l2_dequeue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer);

/*
 * v4l2_stream_on - Start video streaming
 * @dev: Device instance
 *
 * Start video capture or output on the device. For video output devices at
 * least one buffer must be queued before starting the stream.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_stream_on(struct v4l2_device *dev);

/*
 * v4l2_stream_off - Stop video streaming
 * @dev: Device instance
 *
 * Stop video capture or output on the device. Upon successful return ownership
 * of all buffers is returned to the caller.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_stream_off(struct v4l2_device *dev);

/*
 * v4l2_get_control - Read the value of a control
 * @dev: Device instance
 * @id: Control ID
 * @value: Control value to be filled
 *
 * Retrieve the current value of control @id and store it in @value.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_get_control(struct v4l2_device *dev, unsigned int id, int32_t *value);

/*
 * v4l2_set_control - Write the value of a control
 * @dev: Device instance
 * @id: Control ID
 * @value: Control value
 *
 * Set control @id to @value. The device is allowed to modify the requested
 * value, in which case @value is updated to the modified value.
 *
 * Return 0 on success or a negative error code on failure.
 */
int v4l2_set_control(struct v4l2_device *dev, unsigned int id, int32_t *value);
#if defined(__cplusplus)
}
#endif
#endif /*__V4L2_H*/
