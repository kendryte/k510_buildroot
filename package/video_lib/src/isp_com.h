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
/******************************************************************************
  File Name     : isp_com.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _ISP_COM_H_
#define _ISP_COM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "video_subsystem.h"
#ifdef _USE_V4L2
#include <linux/clk-provider.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/wait.h>
#include <linux/types.h>
#include <media/media-entity.h>
#include <media/v4l2-async.h>
#include <media/v4l2-device.h>
#include <linux/videodev2.h>
#else
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#endif

#include "vi/vi_com.h"
#include "isp_2k/isp_f2k.h"
#include "isp_2k/isp_r2k.h"
#include "isp_3d/isp_3d.h"
#include "isp_fbc/isp_fbc.h"
#include "isp_2k/isp.h"
#include "mipi/mipi.h"
#include "bt1120/bt1120.h"
#include "vo/vo.h"
#include "isp_video.h"

struct isp_device;
#define msleep(x) usleep(1000*x)
#define FALSE       0
#define TRUE        1

#define DISABLE     0
#define ENABLE      1

#define ISP_CMD_READ_REG         _IOWR('q', 1, struct isp_reg)
#define ISP_CMD_WRITE_REG         _IOWR('q', 2, struct isp_reg)
#define ISP_CMD_ACT_SENSOR_RST   _IOWR('q', 3, unsigned long)
#define ISP_CMD_RLS_SENSOR_RST   _IOWR('q', 4, unsigned long)
#define ISP_CMD_SET_DMABUF_Y_FD    _IOWR('q', 5, unsigned long)
#define ISP_CMD_SET_DMABUF_UV_FD    _IOWR('q', 6, unsigned long)
#define ISP_CMD_MIPI_DSI_INIT    _IOWR('q', 7, unsigned long)

#define DVP_CMD_ACT_SENSOR_RST    _IOWR('q', 8, unsigned long)
#define DVP_CMD_RLS_SENSOR_RST    _IOWR('q', 9, unsigned long)
#define ISP_CMD_SET_DS2BUF        _IOWR('q', 10, unsigned long)
#define ISP_CMD_GET_DS2BUF        _IOWR('q', 11, unsigned long)
#define ISP_CMD_EN_DS2_INT        _IOWR('q', 12, unsigned long)

#define ISP_CMD_MIPI_DSI_ILI7807_INIT    _IOWR('q', 13, unsigned long)
#define ISP_CMD_MIPI_DSI_HX8399_INIT    _IOWR('q', 14, unsigned long)


#define ISP_CMD_DS1_ADDR               _IOWR('q', 15, unsigned long)
#define ISP_CMD_DS1_BUFF_COUNT        _IOWR('q', 16, unsigned long)

#define ISP_CMD_DS0_SRC_ADDR                _IOWR('q', 17, unsigned long)
#define ISP_CMD_DS1_DES_ADDR                _IOWR('q', 18, unsigned long)

#define ISP_CMD_TWOD_TEST_ADDR                _IOWR('q', 19, unsigned long)

#define ISP_CMD_ISP_RESET                _IOWR('q', 20, unsigned long)
#define ISP_CMD_SET_DS1_SIZE                _IOWR('q', 21, unsigned long)
#define ISP_CMD_SET_DS0_SIZE                _IOWR('q', 22, unsigned long)
#define I2C0_CMD_READ_REG         _IOWR('q', 1, struct i2c0_reg)
#define I2C0_CMD_WRITE_REG        _IOWR('q', 2, struct i2c0_reg)
#define I2C0_CMD_TEST              _IOWR('q', 3, unsigned long)

#define I2C1_CMD_READ_REG         _IOWR('q', 1, struct i2c1_reg)
#define I2C1_CMD_WRITE_REG        _IOWR('q', 2, struct i2c1_reg)
#define I2C1_CMD_TEST              _IOWR('q', 3, unsigned long)
#define VIDEO_CLOSE_ALL_LAYER                _IOWR('q', 25, unsigned long)

#define TWOD_ROTATION               0               // USE TWOD rotation 


#define DISPLAY_TEXT_WIDTH  640
#define DISPLAY_TEXT_HEIGHT 50
extern int fd_isp;
extern ISP_REG_S reg_isp;
extern unsigned int picture_addr;
extern int *ds_virtual_addr[];
extern int *virtual_addr[];
extern int *vo_osd_virtual_addr[];
extern struct memory_cache_sync_request OSD1layer5DisplayGnne;
//extern struct memory_cache_sync_request ispOutputForGnne;
extern struct memory_cache_sync_request ispOutputForDisplay;
extern struct memory_cache_sync_request OSD0layer4DisplayText;

int isp_init(DS2_INFO *ds2_info, DS1_INFO *ds1_info, VO_OSD_INFO *osd0_info, VO_OSD_INFO *osd1_info,unsigned int draw_demo_en,unsigned int debug_enable,SENSOR_TYPE sensor_type,LCD_TYPE lcd_type);
void isp_exit(void);

extern int draw_frame(unsigned int draw_en,unsigned int DrawAreaNum,frame_coordinate_info frame_coordinate);
unsigned int ai_get_buf_addr(void);

//void vo_change_laye1_addr(uint32_t y_addr, uint32_t uv_addr);

#define __LINUX__

typedef enum _VI_PIPE_ID
{
	VI_MIPI_CSI00_PIPE_ID,
	VI_MIPI_CSI01_PIPE_ID,
	VI_MIPI_CSI02_PIPE_ID,
	VI_MIPI_CSI10_PIPE_ID,
	VI_MIPI_CSI11_PIPE_ID,
	VI_MIPI_CSI12_PIPE_ID,
	VI_DVP_0_PIPE_ID,
	VI_DVP_1_PIPE_ID,
	VI_MAX_PIPE_NUM,
}VI_PIPE_ID;
#define ISP_MAX_SUBDEVS		5

#define ISP_DS_CH_NUM 3
#define ISP_DS_CH_OSD_NUM 3
#define VIDIOC_ISP_VI_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 1,VI_WRAP_ATRR_S)
#define VIDIOC_ISP_VI_PIPE0_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 2,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE1_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 3,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE2_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 4,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE3_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 5,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE4_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 6,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE5_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 7,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE6_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 8,VI_PIPE_ATRR_S)
#define VIDIOC_ISP_VI_PIPE7_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 9,VI_PIPE_ATRR_S)		
#define VIDIOC_ISP_F2K_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 10,ISP_WRAP_ATRR_S)
#define VIDIOC_ISP_F2K_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 11,ISP_CORE_ATRR_S)
#define VIDIOC_ISP_F2K_DS_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 12,ISP_DS_ATRR_S)
#define VIDIOC_ISP_F2K_MFBC_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 13,ISP_MFBC_ATRR_S)
#define VIDIOC_ISP_F2K_MFBD_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 14,ISP_MFBD_ATRR_S)
#define VIDIOC_ISP_F2K_REMAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 15,ISP_REMAP_ATRR_S)
#define VIDIOC_ISP_R2K_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 16,ISP_WRAP_ATRR_S)
#define VIDIOC_ISP_R2K_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 17,ISP_CORE_ATRR_S)
#define VIDIOC_ISP_R2K_DS_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 18,ISP_DS_ATRR_S)
#define VIDIOC_ISP_R2K_REMAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 18,ISP_REMAP_ATRR_S)
#define VIDIOC_ISP_TOF_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 19,TOF_WRAP_ATRR_S)
#define VIDIOC_ISP_TOF_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 20,TOF_CORE_ATRR_S)
#define VIDIOC_ISP_MFBC_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 21,ISP_MFBC_ATRR_S)
#define VIDIOC_ISP_MFBC_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 22,ISP_MFBC_ATRR_S)
enum SUBDEV_GRP_ID{
	MIPI0_PHY_SUBDEV,
	MIPI1_PHY_SUBDEV,
	VI_SUBDEV,
	ISP_F2K_SUBDEV,
	ISP_R2K_SUBDEV,
	ISP_TOF_SUBDEV,
	ISP_MFBC_SUBDEV,
};	
#define ISP_CHECK_POINTER(ptr)\
    do {\
        if (NULL == ptr)\
        {\
            printf("ISP Module: Null Pointer!\n");\
            return -1;\
        }\
    }while(0);
#define VI_CHECK_PIPE(pipe)\
	do {\
		if (((pipe) < VI_MIPI_CSI00_PIPE_ID) || ((pipe) >= VI_MAX_PIPE_NUM))\
		{\
			printf("VI Module: Err Vin Pipe Index!\n");\
			return -1;\
		}\
	}while(0);
#define VI_CHECK_POINTER(ptr)\
    do {\
        if (NULL == ptr)\
        {\
            printf("ISP Module: Null Pointer!\n");\
            return -1;\
        }\
    }while(0);
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
#ifndef container_of
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif
#define to_isp_device(ptr_module)				\
	container_of(ptr_module, struct isp_device, isp_##ptr_module)
#define to_device(ptr_module)	(to_isp_device(ptr_module)->dev)


struct isp_device {
#ifdef _USE_V4L2
	struct v4l2_device v4l2_dev;
	struct v4l2_async_notifier notifier;
	struct media_device media_dev;
	struct device *dev;
	unsigned int  revision;
	unsigned int irq_num;
	void __iomem *mmio_base[ISP_IOMEM_LAST];
	struct regmap *syscon;
	unsigned int  syscon_offset;
	unsigned int  phy_type;
	struct dma_iommu_mapping *mapping;
	spinlock_t 		stat_lock;	/* common lock for statistic drivers */
	struct mutex 	isp_mutex;	/* For handling ref_count field */
	bool 			stop_failure;
	unsigned int  			crashed;
	int 			has_context;
	int 			ref_count;
	unsigned int 	autoidle;
	unsigned int subclk_resources;
	struct v4l2_subdev *subdevs[ISP_MAX_SUBDEVS];
#endif
    unsigned int mmio_base[ISP_IOMEM_LAST];
    struct vi_device isp_vi;
    struct isp_f2k_device isp_f2k;
    struct isp_r2k_device isp_r2k;
    struct isp_tof_device isp_tof;
	struct isp_fbc_device isp_fbc;
	struct isp_mipi_device isp_mipi;
	struct isp_bt1120_device isp_bt1120;
	struct isp_vo_device isp_vo;
};
#ifdef _USE_V4L2
struct isp_async_subdev {
	struct v4l2_async_subdev asd;
	struct isp_bus_cfg bus;
};
enum isp_pad_def{
	ISP_PAD_SINK,
	ISP_PAD_SOURCE_OF,
	ISP_PAD_SOURCE_VP,
	ISP_PADS_NUM,
};
enum isp_input_entity {
	ISP_INPUT_NONE,
	ISP_INPUT_CSI1,
	ISP_INPUT_CSI2,
	ISP_INPUT_DVP,
};
#endif
struct isp_reg_t {
	enum isp_mem_resources mmio_range;
	unsigned int  reg;
	unsigned int  val;
};
static inline
unsigned int  isp_reg_readl(struct isp_device *isp, enum isp_mem_resources isp_mmio_range,
		  unsigned int  reg_offset)
{
#ifdef _USE_V4L2
	return __raw_readl(isp->mmio_base[isp_mmio_range] + reg_offset);
#else
    ISP_REG_S reg_isp={0,0};
    unsigned int  addr = isp->mmio_base[isp_mmio_range] + reg_offset;
    unsigned int  data = 0;
    reg_isp.id = addr - VIDEO_SUBSYSTEM_BASE_ADDR;
    reg_isp.value = 0;
    if (ioctl(fd_isp, ISP_CMD_READ_REG, &reg_isp) < 0)
    {
        printf("Call cmd ISP_CMD_READ_REG fail, reg %u\n", reg_isp.id);
        return -1;
    }
    return reg_isp.value;
#endif
}
static inline
void isp_reg_writel(struct isp_device *isp, unsigned int  reg_value,
		    enum isp_mem_resources isp_mmio_range, unsigned int  reg_offset)
{
#ifdef _USE_V4L2
	__raw_writel(reg_value, isp->mmio_base[isp_mmio_range] + reg_offset);
#else
    ISP_REG_S reg_isp={0,0};
    unsigned int  addr = isp->mmio_base[isp_mmio_range] + reg_offset;
    unsigned int  data = reg_value;
    reg_isp.id = addr - VIDEO_SUBSYSTEM_BASE_ADDR;
    reg_isp.value = data;
    //printf("isp_reg_writel:addr = 0x%x,data = 0x%x\n",addr,data);
    if (ioctl(fd_isp, ISP_CMD_WRITE_REG, &reg_isp) < 0)
    {
        printf("Call cmd ISP_CMD_WRITE_REG fail, reg addr = 0x%x\n", reg_isp.id);
        return ;
    }
#endif
}
static inline
void isp_reg_clr(struct isp_device *isp, enum isp_mem_resources mmio_range,
		 unsigned int  reg, unsigned int  clr_bits)
{
	unsigned int  v = isp_reg_readl(isp, mmio_range, reg);
	isp_reg_writel(isp, v & ~clr_bits, mmio_range, reg);
}
static inline
void isp_reg_set(struct isp_device *isp, enum isp_mem_resources mmio_range,
		 unsigned int  reg, unsigned int  set_bits)
{
	unsigned int  v = isp_reg_readl(isp, mmio_range, reg);
	isp_reg_writel(isp, v | set_bits, mmio_range, reg);
}
static inline
void isp_reg_clr_set(struct isp_device *isp, enum isp_mem_resources mmio_range,
		     unsigned int  reg, unsigned int  clr_bits, unsigned int  set_bits)
{
	unsigned int  v = isp_reg_readl(isp, mmio_range, reg);
	isp_reg_writel(isp, (v & ~clr_bits) | set_bits, mmio_range, reg);
}
//
void debug(unsigned int debug_en,ISP_PIPE_MODE_E pipe);
#ifdef __cplusplus
}
#endif

#endif /*_ISP_COM_H_*/
