/*
 * Sample ISP camera application
 *
 * Copyright (C) 2020 zhudalei <zhudalei@canaan-creative.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#ifndef __MEDIACTL_H__
#define __MEDIACTL_H__

#if defined(__cplusplus)
extern "C" {
#endif

struct video_info
{
	unsigned int video_used;
	char *video_name[4];
	unsigned int enable[4];
	unsigned int video_width[4];
	unsigned int video_height[4];
	unsigned int video_out_format[4];
};

int mediactl_init(char *video_cfg_file,struct video_info *dev_info);
int mediactl_set_ae(void);
#if defined(__cplusplus)
}
#endif
#endif /*__MEDIACTL_H__*/
