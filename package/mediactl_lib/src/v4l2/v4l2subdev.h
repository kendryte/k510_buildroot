/*
 * V4L2 subdev interface library
 *
 * Copyright (C) 2010-2011 Ideas on board SPRL
 *
 * Contact: Laurent Pinchart <laurent.pinchart@ideasonboard.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SUBDEV_H__
#define __SUBDEV_H__

#include <linux/v4l2-subdev.h>

struct media_entity;
/**
 * @brief Open a sub-device.
 * @param entity - sub-device media entity.
 *
 * Open the V4L2 subdev device node associated with @a entity. The file
 * descriptor is stored in the media_entity structure.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int v4l2_subdev_open(struct media_entity *entity);

/**
 * @brief Close a sub-device.
 * @param entity - sub-device media entity.
 *
 * Close the V4L2 subdev device node associated with the @a entity and opened by
 * a previous call to v4l2_subdev_open() (either explicit or implicit).
 */
void v4l2_subdev_close(struct media_entity *entity);

/**
 * @brief Retrieve the format on a pad.
 * @param entity - subdev-device media entity.
 * @param format - format to be filled.
 * @param pad - pad number.
 * @param which - identifier of the format to get.
 *
 * Retrieve the current format on the @a entity @a pad and store it in the
 * @a format structure.
 *
 * @a which is set to V4L2_SUBDEV_FORMAT_TRY to retrieve the try format stored
 * in the file handle, of V4L2_SUBDEV_FORMAT_ACTIVE to retrieve the current
 * active format.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int v4l2_subdev_get_format(struct media_entity *entity,
	struct v4l2_mbus_framefmt *format, unsigned int pad,
	enum v4l2_subdev_format_whence which);

/**
 * @brief Set the format on a pad.
 * @param entity - subdev-device media entity.
 * @param format - format.
 * @param pad - pad number.
 * @param which - identifier of the format to set.
 *
 * Set the format on the @a entity @a pad to @a format. The driver is allowed to
 * modify the requested format, in which case @a format is updated with the
 * modifications.
 *
 * @a which is set to V4L2_SUBDEV_FORMAT_TRY to set the try format stored in the
 * file handle, of V4L2_SUBDEV_FORMAT_ACTIVE to configure the device with an
 * active format.
 *
 * @return 0 on success, or a negative error code on failure.
 */
int v4l2_subdev_set_format(struct media_entity *entity,
	struct v4l2_mbus_framefmt *format, unsigned int pad,
	enum v4l2_subdev_format_whence which);

int v4l2_set_sensor_gain(struct media_entity *pipe,struct media_entity *sensor);    
#endif /*__SUBDEV_H__*/