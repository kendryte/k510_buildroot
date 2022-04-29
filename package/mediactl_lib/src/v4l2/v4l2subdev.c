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

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../media/mediactl.h"
#include "../media/mediactl-priv.h"
#include "../linux/k510isp.h"
#include "tools.h"
#include "v4l2subdev.h"
/**
 * @brief 
 * 
 * @param entity 
 * @return int 
 */
int v4l2_subdev_open(struct media_entity *entity)
{
	//printf("%s: start %d,%s\n", __func__,entity->fd,entity->devname);
	if (entity->fd != -1)
		return 0;

	entity->fd = open(entity->devname, O_RDWR);
	if (entity->fd == -1) {
		int ret = -errno;
		printf("%s: Failed to open subdev device node %s\n", __func__,
			  entity->devname);
		return ret;
	}
	//printf("%s: end %d\n", __func__, entity->fd);
	return 0;
}
/**
 * @brief 
 * 
 * @param entity 
 */
void v4l2_subdev_close(struct media_entity *entity)
{
	//printf("%s: start \n", __func__);
	close(entity->fd);
	entity->fd = -1;
}
/**
 * @brief 
 * 
 * @param entity 
 * @param format 
 * @param pad 
 * @param which 
 * @return int 
 */
int v4l2_subdev_get_format(struct media_entity *entity,
	struct v4l2_mbus_framefmt *format, unsigned int pad,
	enum v4l2_subdev_format_whence which)
{
	struct v4l2_subdev_format fmt;
	int ret;

	//printf("%s: start pad %d,which %d \n", __func__,pad,which);
	ret = v4l2_subdev_open(entity);
	if (ret < 0)
		return ret;

	memset(&fmt, 0, sizeof(fmt));
	fmt.pad = pad;
	fmt.which = which;

	ret = ioctl(entity->fd, VIDIOC_SUBDEV_G_FMT, &fmt);
	if (ret < 0)
	{
		printf("%s: start %d\n", __func__,
			  ret);
		v4l2_subdev_close(entity);
		return -errno;
	}

	*format = fmt.format;
	v4l2_subdev_close(entity);
	return 0;
}
/**
 * @brief 
 * 
 * @param entity 
 * @param format 
 * @param pad 
 * @param which 
 * @return int 
 */
int v4l2_subdev_set_format(struct media_entity *entity,
	struct v4l2_mbus_framefmt *format, unsigned int pad,
	enum v4l2_subdev_format_whence which)
{
	struct v4l2_subdev_format fmt;
	int ret;

	//printf("%s: start pad %d which %d\n", __func__,pad,which);

	ret = v4l2_subdev_open(entity);
	if (ret < 0)
		return ret;

	memset(&fmt, 0, sizeof(fmt));
	fmt.pad = pad;
	fmt.which = which;
	fmt.format = *format;

	ret = ioctl(entity->fd, VIDIOC_SUBDEV_S_FMT, &fmt);
	if (ret < 0)
	{
		printf("%s: ioctl failed ret(%d)\n", __func__,
			  ret);
		v4l2_subdev_close(entity);
		return -errno;
	}

	*format = fmt.format;
	v4l2_subdev_close(entity);
	return 0;
}
/**
 * @brief 
 * 
 * @param pipe 
 * @param sensor 
 * @return int 
 */
int v4l2_set_sensor_gain(struct media_entity *pipe,struct media_entity *sensor)
{
	int ret;
	struct k510isp_ae_stats ae_stats;
	ret = v4l2_subdev_open(pipe);
	if (ret < 0)
		return ret;

	ret = ioctl(pipe->fd,VIDIOC_K510ISP_F2K_AE_STAT_REQ,&ae_stats);
	if (ret < 0)
	{
		printf("%s: ioctl(VIDIOC_K510ISP_F2K_AE_STAT_REQ) failed ret(%d)\n", __func__,
			  ret);
		v4l2_subdev_close(pipe);
		return ret;
	}
	//printf("%s:ae_wren(%d),ae_expl(%d),ae_agco(%d)\n",__func__,ae_stats.ae_wren,ae_stats.ae_expl,ae_stats.ae_agco);
	v4l2_subdev_close(pipe);
	//
	if( ae_stats.ae_wren == 1)
	{
		ret = v4l2_subdev_open(sensor);
		if (ret < 0)
			return ret;

		struct v4l2_control  control_s;
		control_s.id = V4L2_CID_GAIN;
		control_s.value = ae_stats.ae_expl;//val;//300;
		ret = ioctl(sensor->fd,VIDIOC_S_CTRL,&control_s);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_GAIN)failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(sensor);
			return ret;
		} 
		
		control_s.id = V4L2_CID_EXPOSURE;
		control_s.value = ae_stats.ae_agco;//val;//300;
		ret = ioctl(sensor->fd,VIDIOC_S_CTRL,&control_s);
		if (ret < 0)
		{
			printf("%s: ioctl(VIDIOC_S_CTRL-V4L2_CID_EXPOSURE)failed ret(%d)\n", __func__,
				  ret);
			v4l2_subdev_close(sensor);
			return ret;
		} 		
		v4l2_subdev_close(sensor);
	}

	return 0;
}