/*
 * Media controller interface library
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

//#include "config.h"

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
#include <sys/sysmacros.h>

#include <linux/media.h>
#include <linux/videodev2.h>
#include <linux/fs.h>

#include "mediactl.h"
#include "mediactl-priv.h"
#include "../v4l2/tools.h"

/* -----------------------------------------------------------------------------
 * media open/close
 -----------------------------------------------------------------------------*/
struct media_device *media_open(const char *device_name, int flags)
{
	struct media_device *mdev;
	int ret;
	int fd = 0;

	printf("%s:start\n",__func__);
	mdev = malloc(sizeof(struct media_device));
	if (mdev == NULL) {
        printf("%s: unable to allocate memory\n", __func__);
        return NULL;
    }
	memset(mdev, 0, sizeof(*mdev));

	if (flags)
        printf("Opening media device %s\n", device_name);

	fd = open(device_name,O_RDWR);
	if(fd < 0)
	{
		printf("%s: Can't open media device %s\n", __func__, device_name);
		media_close(mdev);
		return NULL;
	}
	mdev->fd = fd;

    //MEDIA_IOC_DEVICE_INFO。
    ret = ioctl(mdev->fd, MEDIA_IOC_DEVICE_INFO, &mdev->info);
    if (ret < 0) {
        printf("%s: Unable to retrieve media device information for "
               "device %s (%s)\n", __func__, device_name, strerror(errno));
        media_close(mdev);
        return NULL;
    }
	//printf("media_device_info:%s,%s,%s,%s,%d,%d,%d\n",mdev->info.driver,mdev->info.model,mdev->info.serial,mdev->info.bus_info,mdev->info.media_version,mdev->info.hw_revision,mdev->info.driver_version);
//

    if (flags)
        printf("Enumerating entities\n");
//
    ////enum entity,saved。
    ret = media_enum_entities(mdev);
    if (ret < 0) {
        printf("%s: Unable to enumerate entities for device %s (%s)\n",
                __func__, device_name, strerror(-ret));
        media_close(mdev);
        return NULL;
    }
//
    if (flags) {
        printf("Found %u entities\n", mdev->entities_count);
        printf("Enumerating pads and links\n");
    }

//
    ////enum link，saved。
	//printf("%s:media_enum_links\n",__func__);
    ret = media_enum_links(mdev);
    if (ret < 0) {
            printf("%s: Unable to enumerate pads and linksfor device %s\n",
                    __func__, device_name);
            media_close(mdev);
            return NULL;
    }

	//printf("%s:end\n",__func__);
	return mdev;
}
/**
 * @brief 
 * 
 * @param mdev 
 */
void media_close(struct media_device *mdev)
{
	close(mdev->fd);
	free(mdev);
}
/* -----------------------------------------------------------------------------
 * Graph access
 -----------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 * @param pad 
 * @return struct media_pad* 
 */
struct media_pad *media_entity_remote_source(struct media_pad *pad)
{
	unsigned int i;

	if (!(pad->flags & MEDIA_PAD_FL_SINK))
		return NULL;

	for (i = 0; i < pad->entity->num_links; ++i) {
		struct media_link *link = &pad->entity->links[i];

		if (!(link->flags & MEDIA_LNK_FL_ENABLED))
			continue;

		if (link->sink == pad)
			return link->source;
	}

	return NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @param name 
 * @param length 
 * @return struct media_entity* 
 */
struct media_entity *media_get_entity_by_name(struct media_device *media,
					      const char *name, size_t length)
{
	unsigned int i;

	/* A match is impossible if the entity name is longer than the maximum
	 * size we can get from the kernel.
	 */
	if (length >= FIELD_SIZEOF(struct media_entity_desc, name))
		return NULL;

	for (i = 0; i < media->entities_count; ++i) {
		struct media_entity *entity = &media->entities[i];
		//printf("%s:entity->info.name(%s),name(%s)\n",__func__,entity->info.name,name);		
		if (strncmp(entity->info.name, name, length) == 0 &&
		    entity->info.name[length] == '\0')
			return entity;
	}

	return NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @param id 
 * @return struct media_entity* 
 */
struct media_entity *media_get_entity_by_id(struct media_device *media,
					    __u32 id)
{
	bool next = id & MEDIA_ENT_ID_FLAG_NEXT;
	unsigned int i;

	id &= ~MEDIA_ENT_ID_FLAG_NEXT;

	for (i = 0; i < media->entities_count; ++i) {
		struct media_entity *entity = &media->entities[i];

		if ((entity->info.id == id && !next) ||
		    (entity->info.id > id && next))
			return entity;
	}

	return NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @return unsigned int 
 */
unsigned int media_get_entities_count(struct media_device *media)
{
	return media->entities_count;
}
/**
 * @brief 
 * 
 * @param media 
 * @param index 
 * @return struct media_entity* 
 */
struct media_entity *media_get_entity(struct media_device *media, unsigned int index)
{
	if (index >= media->entities_count)
		return NULL;

	return &media->entities[index];
}
/**
 * @brief 
 * 
 * @param entity 
 * @param index 
 * @return const struct media_pad* 
 */
const struct media_pad *media_entity_get_pad(struct media_entity *entity, unsigned int index)
{
	if (index >= entity->info.pads)
		return NULL;

	return &entity->pads[index];
}
/**
 * @brief 
 * 
 * @param entity 
 * @return unsigned int 
 */
unsigned int media_entity_get_links_count(struct media_entity *entity)
{
	return entity->num_links;
}
/**
 * @brief 
 * 
 * @param entity 
 * @param index 
 * @return const struct media_link* 
 */
const struct media_link *media_entity_get_link(struct media_entity *entity, unsigned int index)
{
	if (index >= entity->num_links)
		return NULL;

	return &entity->links[index];
}
/**
 * @brief 
 * 
 * @param entity 
 * @return const char* 
 */
const char *media_entity_get_devname(struct media_entity *entity)
{
	return entity->devname[0] ? entity->devname : NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @param type 
 * @return struct media_entity* 
 */
struct media_entity *media_get_default_entity(struct media_device *media,
					      unsigned int type)
{
	switch (type) {
	case MEDIA_ENT_T_DEVNODE_V4L:
		return media->def.v4l;
	case MEDIA_ENT_T_DEVNODE_FB:
		return media->def.fb;
	case MEDIA_ENT_T_DEVNODE_ALSA:
		return media->def.alsa;
	case MEDIA_ENT_T_DEVNODE_DVB:
		return media->def.dvb;
	}

	return NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @return const struct media_device_info* 
 */
const struct media_device_info *media_get_info(struct media_device *media)
{
	return &media->info;
}
/**
 * @brief 
 * 
 * @param media 
 * @return const char* 
 */
const char *media_get_devnode(struct media_device *media)
{
	return media->devnode;
}
/**
 * @brief 
 * 
 * @param entity 
 * @return const struct media_entity_desc* 
 */
const struct media_entity_desc *media_entity_get_info(struct media_entity *entity)
{
	return &entity->info;
}

/* -----------------------------------------------------------------------------
 * Open/close
 -----------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 * @param media 
 * @return int 
 */
static int media_device_open(struct media_device *media)
{
	int ret;

	if (media->fd != -1)
	{
		printf("media_device_open:media->fd %d\n",media->fd);
		return 0;
	}	

	media_dbg(media, "Opening media device %s\n", media->devnode);

	media->fd = open(media->devnode, O_RDWR);
	if (media->fd < 0) {
		ret = -errno;
		media_dbg(media, "%s: Can't open media device %s\n",
			  __func__, media->devnode);
		return ret;
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param media 
 */
static void media_device_close(struct media_device *media)
{
	printf("%s:fd = %d\n",__func__,media->fd);
	if (media->fd != -1) {
	//	close(media->fd);
	//	media->fd = -1;
	}
}

/* -----------------------------------------------------------------------------
 * Link setup
 -----------------------------------------------------------------------------*/
 /**
  * @brief 
  * 
  * @param media 
  * @param source 
  * @param sink 
  * @param flags 
  * @return int 
  */
int media_setup_link(struct media_device *media,
		     struct media_pad *source,
		     struct media_pad *sink,
		     __u32 flags)
{
	struct media_link *link;
	struct media_link_desc ulink;
	unsigned int i;
	int ret;

	for (i = 0; i < source->entity->num_links; i++) {
		link = &source->entity->links[i];
		//printf("%s:%d,source->entity:0x%x,0x%x\n",__func__,i,link->source->entity,source->entity);
		//printf("%s:%d,source->index:%d,%d\n",__func__,i,link->source->index,source->index);
		//printf("%s:%d,sink->entity:0x%x,0x%x\n",__func__,i,link->sink->entity,sink->entity);
		//printf("%s:%d,sink->index:%d,%d\n",__func__,i,link->sink->index,sink->index);
		if (link->source->entity == source->entity &&
		    link->source->index == source->index &&
		    link->sink->entity == sink->entity &&
		    link->sink->index == sink->index)
		{
			break;
		}	
	}
	//printf("%s:num_links:%d,%d flags(0x%x)\n",__func__,source->entity->num_links,i,flags);

	if (i == source->entity->num_links) {
		printf("%s: Link not found\n", __func__);
		ret = -ENOENT;
		goto done;
	}

	/* source pad */
	ulink.source.entity = source->entity->info.id;
	ulink.source.index = source->index;
	ulink.source.flags = MEDIA_PAD_FL_SOURCE;

	/* sink pad */
	ulink.sink.entity = sink->entity->info.id;
	ulink.sink.index = sink->index;
	ulink.sink.flags = MEDIA_PAD_FL_SINK;

	ulink.flags = flags | (link->flags & MEDIA_LNK_FL_IMMUTABLE);
	ret = ioctl(media->fd, MEDIA_IOC_SETUP_LINK, &ulink);
	//printf("%s:flags(0x%x),ulink.flags(0x%x)\n",__func__,flags,ulink.flags);
	if (ret == -1) {
		ret = -errno;
		printf("%s: Unable to setup link (%s)\n",
			  __func__, strerror(errno));
		goto done;
	}

	link->flags = ulink.flags;
	link->twin->flags = ulink.flags;

	ret = 0;

done:
	//media_device_close(media);
	//printf("%s:end ret:%d\n",__func__,ret);
	return ret;
}
/**
 * @brief 
 * 
 * @param media 
 * @return int 
 */
int media_reset_links(struct media_device *media)
{
	unsigned int i, j;
	int ret;
	printf("%s:start\n",__func__);

	for (i = 0; i < media->entities_count; ++i) {
		struct media_entity *entity = &media->entities[i];
		//printf("%s:entity(0x%x)\n",__func__,entity);
		for (j = 0; j < entity->num_links; j++) {
			struct media_link *link = &entity->links[j];
			//printf("%s:link->flags(0x%x)\n",__func__,link->flags);
			if (link->flags & MEDIA_LNK_FL_IMMUTABLE ||
			    link->source->entity != entity)
				continue;

			ret = media_setup_link(media, link->source, link->sink,
					       link->flags & ~MEDIA_LNK_FL_ENABLED);
			if (ret < 0)
				return ret;

		}

	}

	return 0;
}

/* -----------------------------------------------------------------------------
 * Entities, pads and links enumeration
 -----------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 * @param entity 
 * @return struct media_link* 
 */
struct media_link *media_entity_add_link(struct media_entity *entity)
{
	if (entity->num_links >= entity->max_links) {
		struct media_link *links = entity->links;
		unsigned int max_links = entity->max_links * 2;
		unsigned int i;

		links = realloc(links, max_links * sizeof *links);
		if (links == NULL)
			return NULL;

		for (i = 0; i < entity->num_links; ++i)
			links[i].twin->twin = &links[i];

		entity->max_links = max_links;
		entity->links = links;
	}

	return &entity->links[entity->num_links++];
}
/**
 * @brief 
 * 
 * @param media 
 * @return int 
 */
int media_enum_links(struct media_device *media)
{
	__u32 id;
	int ret = 0;
	printf("%s:start!entities_count %d\n",__func__,media->entities_count);

	for (id = 1; id <= media->entities_count; id++) {
		struct media_entity *entity = &media->entities[id - 1];
		struct media_links_enum links;
		unsigned int i;		

		links.entity = entity->info.id;
		links.pads = calloc(entity->info.pads, sizeof(struct media_pad_desc));
		links.links = calloc(entity->info.links, sizeof(struct media_link_desc));
		//printf("%s:entity (0x%x),entity->info.id(0x%x) entity->info.pads(%d) entity->info.links(%d)\n",__func__,entity,entity->info.id,entity->info.pads,entity->info.links);
		
		if (ioctl(media->fd, MEDIA_IOC_ENUM_LINKS, &links) < 0) {
			ret = -errno;
			media_dbg(media,
				  "%s: Unable to enumerate pads and links (%s).\n",
				  __func__, strerror(errno));
			free(links.pads);
			free(links.links);
			return ret;
		}

		for (i = 0; i < entity->info.pads; ++i) {
			entity->pads[i].entity = entity;
			entity->pads[i].index = links.pads[i].index;
			entity->pads[i].flags = links.pads[i].flags;
			//printf("%s:entity(0x%x),index(%d,flags(0x%x)\n",__func__,entity,entity->pads[i].index,entity->pads[i].flags);
		}

		for (i = 0; i < entity->info.links; ++i) {
			struct media_link_desc *link = &links.links[i];
			struct media_link *fwdlink;
			struct media_link *backlink;
			struct media_entity *source;
			struct media_entity *sink;

			source = media_get_entity_by_id(media, link->source.entity);
			sink = media_get_entity_by_id(media, link->sink.entity);
			//printf("%s:entity(0x%x),source(0x%x),sink(0x%x)\n",__func__,entity,source,sink);
			if (source == NULL || sink == NULL) {
				media_dbg(media,
					  "WARNING entity %u link %u from %u/%u to %u/%u is invalid!\n",
					  id, i, link->source.entity,
					  link->source.index,
					  link->sink.entity,
					  link->sink.index);
				ret = -EINVAL;
			} else {
			
				fwdlink = media_entity_add_link(source);
				fwdlink->source = &source->pads[link->source.index];
				fwdlink->sink = &sink->pads[link->sink.index];
				fwdlink->flags = link->flags;
			
				backlink = media_entity_add_link(sink);
				backlink->source = &source->pads[link->source.index];
				backlink->sink = &sink->pads[link->sink.index];
				backlink->flags = link->flags;

				fwdlink->twin = backlink;
				backlink->twin = fwdlink;
			
			}

		}

		free(links.pads);
		free(links.links);
	}

	return ret;
}
/**
 * @brief 
 * 
 * @param entity 
 * @return int 
 */
static int media_get_devname_sysfs(struct media_entity *entity)
{
	struct stat devstat;
	char devname[32];
	char sysname[32];
	char target[1024];
	char *p;
	int ret;
	//printf("%s:start\n",__func__);
	sprintf(sysname, "/sys/dev/char/%u:%u", entity->info.v4l.major,
		entity->info.v4l.minor);
	ret = readlink(sysname, target, sizeof(target));
	if (ret < 0)
		return -errno;

	target[ret] = '\0';
	p = strrchr(target, '/');
	if (p == NULL)
		return -EINVAL;

	sprintf(devname, "/dev/%s", p + 1);
	ret = stat(devname, &devstat);
	if (ret < 0)
		return -errno;

	/* Sanity check: udev might have reordered the device nodes.
	 * Make sure the major/minor match. We should really use
	 * libudev.
	 */
	//printf("%s:major(devstat.st_rdev)%d,minor(devstat.st_rdev)%d,major %d,minor %d,devname %s\n",__func__,major(devstat.st_rdev),minor(devstat.st_rdev),entity->info.v4l.major,entity->info.v4l.minor,devname);
	if (major(devstat.st_rdev) == entity->info.v4l.major &&
	    minor(devstat.st_rdev) == entity->info.v4l.minor)
		strcpy(entity->devname, devname);

	return 0;
}
/**
 * @brief 
 * 
 * @param media 
 * @return int 
 */
int media_enum_entities(struct media_device *media)
{       
        struct media_entity *entity;
        struct stat devstat;
        unsigned int size;
        char devname[32];
        char sysname[32];
        char target[1024];
        char *p;        
        __u32 id;
        int ret;

        for (id = 0; ; id = entity->info.id) {
                size = (media->entities_count + 1) * sizeof(*media->entities);
                media->entities = realloc(media->entities, size);//entities存放所有entity
                
                entity = &media->entities[media->entities_count];
                memset(entity, 0, sizeof(*entity));
                entity->fd = -1;
                entity->info.id = id | MEDIA_ENT_ID_FLAG_NEXT;//希望获得NEXT id

                /*
                   entity->info结构体是内核标准结构体：
                   struct media_entity_desc info;
                   其中有两个成员容易误会，所以将这两个成员的驱动赋值贴出来，其意思一目了然：
                   u_ent.pads = ent->num_pads;//entity pad数
                   u_ent.links = ent->num_links - ent->num_backlinks;//entity的link数
                 */
                ret = ioctl(media->fd, MEDIA_IOC_ENUM_ENTITIES, &entity->info);
                if (ret < 0) {
                        if (errno == EINVAL)
                                break;
                        return -errno;
                }

                /* Number of links (for outbound links) plus number of pads (for
                 * inbound links) is a good safe initial estimate of the total
                 * number of links.
                 */
                 //未能理解透彻？
                entity->max_links = entity->info.pads + entity->info.links;

                //以下的pads和links都是应用程序自定义的结构体，不是内核的。
                entity->pads = malloc(entity->info.pads * sizeof(*entity->pads));//将会记录此entity所有pad
                entity->links = malloc(entity->max_links * sizeof(*entity->links));//将会记录此entity所有link
                if (entity->pads == NULL || entity->links == NULL)
                        return -ENOMEM;

                media->entities_count++;

				//printf("%s:entity(0x%x),media_entity_type(0x%x),links(%d),pdas(%d)\n",__func__,entity,media_entity_type(entity),entity->info.links,entity->info.pads);
                /* Find the corresponding device name. */
                //只查找videoX或者v4l-subdevX这些节点的entity，其他类型的entity不填充devname。
                if (media_entity_type(entity) != MEDIA_ENT_T_DEVNODE &&
                    media_entity_type(entity) != MEDIA_ENT_T_V4L2_SUBDEV)
                        continue;

                sprintf(sysname, "/sys/dev/char/%u:%u", entity->info.v4l.major,
                        entity->info.v4l.minor);
                ret = readlink(sysname, target, sizeof(target));
                if (ret < 0)
                        continue;

                target[ret] = '\0';
                p = strrchr(target, '/');
                if (p == NULL)
                        continue;

                sprintf(devname, "/dev/%s", p + 1);
                ret = stat(devname, &devstat);
                if (ret < 0)
                        continue;

                /* Sanity check: udev might have reordered the device nodes.
                 * Make sure the major/minor match. We should really use
                 * libudev.
                 */
                if (major(devstat.st_rdev) == entity->info.v4l.major &&
                    minor(devstat.st_rdev) == entity->info.v4l.minor)
                        strcpy(entity->devname, devname);
                //最后devname应该是：videoX、v4l-subdevX这些名称。
        }

        return 0;
}

/**
 * @brief 
 * 
 * @param media 
 * @return int 
 */
int media_device_enumerate(struct media_device *media)
{
	int ret;

	if (media->entities)
		return 0;

	ret = media_device_open(media);
	if (ret < 0)
		return ret;

	ret = ioctl(media->fd, MEDIA_IOC_DEVICE_INFO, &media->info);
	if (ret < 0) {
		ret = -errno;
		media_dbg(media, "%s: Unable to retrieve media device "
			  "information for device %s (%s)\n", __func__,
			  media->devnode, strerror(errno));
		goto done;
	}

	media_dbg(media, "Enumerating entities\n");

	ret = media_enum_entities(media);
	if (ret < 0) {
		media_dbg(media,
			  "%s: Unable to enumerate entities for device %s (%s)\n",
			  __func__, media->devnode, strerror(-ret));
		goto done;
	}

	media_dbg(media, "Found %u entities\n", media->entities_count);
	media_dbg(media, "Enumerating pads and links\n");

	ret = media_enum_links(media);
	if (ret < 0) {
		media_dbg(media,
			  "%s: Unable to enumerate pads and linksfor device %s\n",
			  __func__, media->devnode);
		goto done;
	}

	ret = 0;

done:
	media_device_close(media);
	return ret;
}
/* -----------------------------------------------------------------------------
 * Create/destroy
 -----------------------------------------------------------------------------*/
static void media_debug_default(void *ptr, ...)
{
}
/**
 * @brief 
 * 
 * @param media 
 * @param debug_handler 
 * @param debug_priv 
 */
void media_debug_set_handler(struct media_device *media,
			     void (*debug_handler)(void *, ...),
			     void *debug_priv)
{
	if (debug_handler) {
		media->debug_handler = debug_handler;
		media->debug_priv = debug_priv;
	} else {
		media->debug_handler = media_debug_default;
		media->debug_priv = NULL;
	}
}
/**
 * @brief 
 * 
 * @return struct media_device* 
 */
static struct media_device *__media_device_new(void)
{
	struct media_device *media;

	media = calloc(1, sizeof(*media));
	if (media == NULL)
		return NULL;

	media->fd = -1;
	media->refcount = 1;

	media_debug_set_handler(media, NULL, NULL);

	return media;
}
/**
 * @brief 
 * 
 * @param devnode 
 * @return struct media_device* 
 */
struct media_device *media_device_new(const char *devnode)
{
	struct media_device *media;

	media = __media_device_new();
	if (media == NULL)
		return NULL;

	media->devnode = strdup(devnode);
	if (media->devnode == NULL) {
		media_device_unref(media);
		return NULL;
	}

	return media;
}
/**
 * @brief 
 * 
 * @param info 
 * @return struct media_device* 
 */
struct media_device *media_device_new_emulated(struct media_device_info *info)
{
	struct media_device *media;

	media = __media_device_new();
	if (media == NULL)
		return NULL;

	media->info = *info;

	return media;
}
/**
 * @brief 
 * 
 * @param media 
 * @return struct media_device* 
 */
struct media_device *media_device_ref(struct media_device *media)
{
	media->refcount++;
	return media;
}
/**
 * @brief 
 * 
 * @param media 
 */
void media_device_unref(struct media_device *media)
{
	unsigned int i;

	media->refcount--;
	if (media->refcount > 0)
		return;

	for (i = 0; i < media->entities_count; ++i) {
		struct media_entity *entity = &media->entities[i];

		free(entity->pads);
		free(entity->links);
		if (entity->fd != -1)
			close(entity->fd);
	}

	free(media->entities);
	free(media->devnode);
	free(media);
}
/**
 * @brief 
 * 
 * @param media 
 * @param desc 
 * @param devnode 
 * @return int 
 */
int media_device_add_entity(struct media_device *media,
			    const struct media_entity_desc *desc,
			    const char *devnode)
{
	struct media_entity **defent = NULL;
	struct media_entity *entity;
	unsigned int size;

	size = (media->entities_count + 1) * sizeof(*media->entities);
	entity = realloc(media->entities, size);
	if (entity == NULL)
		return -ENOMEM;

	media->entities = entity;
	media->entities_count++;

	entity = &media->entities[media->entities_count - 1];
	memset(entity, 0, sizeof *entity);

	entity->fd = -1;
	entity->media = media;
	strncpy(entity->devname, devnode, sizeof entity->devname);
	entity->devname[sizeof entity->devname - 1] = '\0';

	entity->info.id = 0;
	entity->info.type = desc->type;
	entity->info.flags = 0;
	memcpy(entity->info.name, desc->name, sizeof entity->info.name);

	switch (entity->info.type) {
	case MEDIA_ENT_T_DEVNODE_V4L:
		defent = &media->def.v4l;
		entity->info.v4l = desc->v4l;
		break;
	case MEDIA_ENT_T_DEVNODE_FB:
		defent = &media->def.fb;
		entity->info.fb = desc->fb;
		break;
	case MEDIA_ENT_T_DEVNODE_ALSA:
		defent = &media->def.alsa;
		entity->info.alsa = desc->alsa;
		break;
	case MEDIA_ENT_T_DEVNODE_DVB:
		defent = &media->def.dvb;
		entity->info.dvb = desc->dvb;
		break;
	}

	if (desc->flags & MEDIA_ENT_FL_DEFAULT) {
		entity->info.flags |= MEDIA_ENT_FL_DEFAULT;
		if (defent)
			*defent = entity;
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param media 
 * @param p 
 * @param endp 
 * @return struct media_pad* 
 */
struct media_pad *media_parse_pad(struct media_device *media,
				  const char *p, char **endp)
{
	unsigned int entity_id, pad;
	struct media_entity *entity;
	char *end;

	/* endp can be NULL. To avoid spreading NULL checks across the function,
	 * set endp to &end in that case.
	 */
	if (endp == NULL)
		endp = &end;

	for (; isspace(*p); ++p);

	if (*p == '"' || *p == '\'') {
		for (end = (char *)p + 1; *end && *end != '"' && *end != '\''; ++end);
		if (*end != '"' && *end != '\'') {
			media_dbg(media, "missing matching '\"'\n");
			*endp = end;
			return NULL;
		}

		entity = media_get_entity_by_name(media, p + 1, end - p - 1);
		if (entity == NULL) {
			media_dbg(media, "no such entity \"%.*s\"\n", end - p - 1, p + 1);
			*endp = (char *)p + 1;
			return NULL;
		}

		++end;
	} else {
		entity_id = strtoul(p, &end, 10);
		entity = media_get_entity_by_id(media, entity_id);
		if (entity == NULL) {
			media_dbg(media, "no such entity %d\n", entity_id);
			*endp = (char *)p;
			return NULL;
		}
	}
	for (; isspace(*end); ++end);

	if (*end != ':') {
		media_dbg(media, "Expected ':'\n", *end);
		*endp = end;
		return NULL;
	}

	for (p = end + 1; isspace(*p); ++p);

	pad = strtoul(p, &end, 10);

	if (pad >= entity->info.pads) {
		media_dbg(media, "No pad '%d' on entity \"%s\". Maximum pad number is %d\n",
				pad, entity->info.name, entity->info.pads - 1);
		*endp = (char *)p;
		return NULL;
	}

	for (p = end; isspace(*p); ++p);
	*endp = (char *)p;

	return &entity->pads[pad];
}
/**
 * @brief 
 * 
 * @param media 
 * @param p 
 * @param endp 
 * @return struct media_link* 
 */
struct media_link *media_parse_link(struct media_device *media,
				    const char *p, char **endp)
{
	struct media_link *link;
	struct media_pad *source;
	struct media_pad *sink;
	unsigned int i;
	char *end;

	source = media_parse_pad(media, p, &end);
	if (source == NULL) {
		*endp = end;
		return NULL;
	}

	if (end[0] != '-' || end[1] != '>') {
		*endp = end;
		media_dbg(media, "Expected '->'\n");
		return NULL;
	}

	p = end + 2;

	sink = media_parse_pad(media, p, &end);
	if (sink == NULL) {
		*endp = end;
		return NULL;
	}

	*endp = end;

	for (i = 0; i < source->entity->num_links; i++) {
		link = &source->entity->links[i];

		if (link->source == source && link->sink == sink)
			return link;
	}

	media_dbg(media, "No link between \"%s\":%d and \"%s\":%d\n",
			source->entity->info.name, source->index,
			sink->entity->info.name, sink->index);
	return NULL;
}
/**
 * @brief 
 * 
 * @param media 
 * @param p 
 * @param endp 
 * @return int 
 */
int media_parse_setup_link(struct media_device *media,
			   const char *p, char **endp)
{
	struct media_link *link;
	__u32 flags;
	char *end;

	link = media_parse_link(media, p, &end);
	if (link == NULL) {
		media_dbg(media,
			  "%s: Unable to parse link\n", __func__);
		*endp = end;
		return -EINVAL;
	}

	p = end;
	if (*p++ != '[') {
		media_dbg(media, "Unable to parse link flags: expected '['.\n");
		*endp = (char *)p - 1;
		return -EINVAL;
	}

	flags = strtoul(p, &end, 10);
	for (p = end; isspace(*p); p++);
	if (*p++ != ']') {
		media_dbg(media, "Unable to parse link flags: expected ']'.\n");
		*endp = (char *)p - 1;
		return -EINVAL;
	}

	for (; isspace(*p); p++);
	*endp = (char *)p;

	media_dbg(media,
		  "Setting up link %u:%u -> %u:%u [%u]\n",
		  link->source->entity->info.id, link->source->index,
		  link->sink->entity->info.id, link->sink->index,
		  flags);

	return media_setup_link(media, link->source, link->sink, flags);
}
/**
 * @brief 
 * 
 * @param media 
 * @param p 
 * @param end 
 */
void media_print_streampos(struct media_device *media, const char *p,
			   const char *end)
{
	int pos;

	pos = end - p + 1;

	if (pos < 0)
		pos = 0;
	if (pos > strlen(p))
		pos = strlen(p);

	media_dbg(media, "\n");
	media_dbg(media, " %s\n", p);
	media_dbg(media, " %*s\n", pos, "^");
}
/**
 * @brief 
 * 
 * @param media 
 * @param p 
 * @return int 
 */
int media_parse_setup_links(struct media_device *media, const char *p)
{
	char *end;
	int ret;

	do {
		ret = media_parse_setup_link(media, p, &end);
		if (ret < 0) {
			media_print_streampos(media, p, end);
			return ret;
		}

		p = end + 1;
	} while (*end == ',');

	return *end ? -EINVAL : 0;
}
