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

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stddef.h>
#include "../linux/k510isp.h"

#include "../media/mediactl-priv.h"
#include "isp_com.h"
#include "isp.h"
#include "vi.h"
#include "mipi_csi2.h"

#define calc_stride(x)  ((x+15)/16*16)

/**
 * @brief
 *
 * @param entity
 * @return int
 */
int sysctl_rst_mipicsi2(struct media_entity *entity)
{
    int ret = 0;

    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_CSI,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    v4l2_subdev_close(entity);
    return ret;
}
/**
 * @brief
 *
 * @param entity
 * @param mipi_csi2
 * @return int
 */
int mipicsi2_cfg(struct media_entity *entity,struct isp_csi2_info *mipi_csi2)
{
    int ret = 0;

    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_CSI,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd, VIDIOC_K510ISP_CSI2_CFG,mipi_csi2);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return 0;
}
/**
 * @brief
 *
 * @param entity
 * @return int
 */
int sysctl_rst_vi(struct media_entity *entity)
{
    int ret = 0;

    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_VI,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return 0;
}
/**
 * @brief
 *
 * @param entity
 * @param vi_cfg
 * @return int
 */
int isp_vi_cfg(struct media_entity *entity,struct vi_cfg_info *vi_cfg)
{
    int ret = 0;

    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_VI,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd, VIDIOC_K510ISP_VI_CFG,vi_cfg);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return 0;
}
/**
 * @brief
 *
 * @param entity
 * @return int
 */
int sysctl_rst_f2k(struct media_entity *entity)
{
    int ret = 0;
    //
    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_F2K,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return ret;
}
/**
 * @brief
 * @param entity
 * @param isp_cfg
 * @return int
 */
int isp_f2k_cfg(struct media_entity *entity,struct isp_cfg_info *isp_cfg,uint32_t phyAddr)
{
    int ret = 0;
    struct isp_wrap_cfg_info *isp_wrap_info = &isp_cfg->isp_wrap_cfg;
    struct isp_core_cfg_info *isp_core_info = &isp_cfg->isp_core_cfg;
    struct isp_ds_cfg_info *isp_ds_info = &isp_cfg->isp_ds_cfg;
    unsigned int width = 0,height = 0;
    unsigned int line_stride = 0;

    //
    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    width = isp_wrap_info->mainInfo.main_size.width;
    printf("%s:%d\n",__func__,isp_wrap_info->mainInfo.main_size.width);
    line_stride = calc_stride(width);
    isp_wrap_info->mainInfo.main_line_stride = line_stride;
    isp_wrap_info->mainInfo.main_y_buf0_base = phyAddr;
    isp_wrap_info->mainInfo.main_y_buf1_base = phyAddr;
    isp_wrap_info->mainInfo.main_uv_buf0_base = phyAddr + line_stride*height;
    isp_wrap_info->mainInfo.main_uv_buf1_base = phyAddr + line_stride*height;

    // 3dnr
    isp_wrap_info->nr3dInfo.nr3d_y_line_stride = line_stride;
    isp_wrap_info->nr3dInfo.nr3d_uv_line_stride = line_stride;
    isp_wrap_info->nr3dInfo.nr3d_y_buf_base = phyAddr + 4096 * 1024;
    isp_wrap_info->nr3dInfo.nr3d_uv_buf_base = phyAddr + 4096 * 1024 + line_stride * height;

    // ldc
    isp_wrap_info->ldcInfo.ldc_line_stride = line_stride;
    isp_wrap_info->ldcInfo.ldc_y_buf_base = phyAddr + 4096 * 1024 * 2;
    isp_wrap_info->ldcInfo.ldc_uv_buf_base = phyAddr + 4096 * 1024 * 5;

    //
    width = isp_wrap_info->ds0Info.ds0_size.width;
    height = isp_wrap_info->mainInfo.main_size.height;
    line_stride = calc_stride(width);
    //isp_wrap_info->ds0Info.ds0_out_en = 1;//must enable
    //isp_ds_info->dsInfo[0].scale_en = 1;
    //isp_ds_info->dsInfo[0].vscale_filter_en = 1;
    //isp_ds_info->dsInfo[0].hscale_filter_en = 1;
    isp_wrap_info->ds0Info.ds0_line_stride = line_stride;
    isp_wrap_info->ds0Info.ds0_y_buf0_base = phyAddr;
    isp_wrap_info->ds0Info.ds0_y_buf1_base = phyAddr;
    isp_wrap_info->ds0Info.ds0_uv_buf0_base = phyAddr+line_stride*height;
    isp_wrap_info->ds0Info.ds0_uv_buf1_base = phyAddr+line_stride*height;
    //
    width = isp_wrap_info->ds1Info.ds1_size.width;
    line_stride = calc_stride(width);
    isp_wrap_info->ds1Info.ds1_line_stride = line_stride;
    isp_wrap_info->ds1Info.ds1_y_buf0_base = phyAddr;
    isp_wrap_info->ds1Info.ds1_y_buf1_base = phyAddr;
    isp_wrap_info->ds1Info.ds1_uv_buf0_base = phyAddr+line_stride*height;
    isp_wrap_info->ds1Info.ds1_uv_buf1_base = phyAddr+line_stride*height;

    //
    //width = isp_wrap_info->ds2Info.ds2_size.width;
    width =  isp_wrap_info->ds2Info.ds2_size.pitch;                // add pitch
    line_stride = calc_stride(width);
    if( OUT_ARGB == isp_wrap_info->ds2Info.ds2_out_img_out_format)
    {
        isp_wrap_info->ds2Info.ds2_line_stride = line_stride*4;
        isp_wrap_info->ds2Info.ds2_r_buf0_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_r_buf1_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_g_buf0_base = phyAddr + line_stride*2;
        isp_wrap_info->ds2Info.ds2_g_buf1_base = phyAddr + line_stride*2;
        isp_wrap_info->ds2Info.ds2_b_buf0_base = phyAddr + line_stride*3;
        isp_wrap_info->ds2Info.ds2_b_buf1_base = phyAddr + line_stride*3;
    }
    else
    {
        isp_wrap_info->ds2Info.ds2_line_stride = line_stride;
        isp_wrap_info->ds2Info.ds2_r_buf0_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_r_buf1_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_g_buf0_base = phyAddr + line_stride*height;
        isp_wrap_info->ds2Info.ds2_g_buf1_base = phyAddr + line_stride*height;
        isp_wrap_info->ds2Info.ds2_b_buf0_base = phyAddr + line_stride*height*2;
        isp_wrap_info->ds2Info.ds2_b_buf1_base = phyAddr + line_stride*height*2;
    }

    // enable pixel remap
    isp_wrap_info->mainInfo.main_pix_remap_en = 1;
    isp_wrap_info->ds0Info.pix_remap_out0_en = 1;
    isp_wrap_info->ds1Info.pix_remap_out1_en = 1;

    ret = ioctl(entity->fd, VIDIOC_K510ISP_F2K_WRAP_CFG,isp_wrap_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    printf("%s:total_width =%d,total_height =%d\n",__func__,isp_core_info->itcInfo.total_size.width,isp_core_info->itcInfo.total_size.height);
    isp_core_info->otcInfo.otc_out_size.width_st = (isp_core_info->itcInfo.itc_size.width - isp_wrap_info->mainInfo.main_size.width)/2;
    if (isp_core_info->otcInfo.otc_out_size.width_st == 0)
        isp_core_info->otcInfo.otc_out_size.width_st = 4;
    isp_core_info->otcInfo.otc_out_size.width = isp_wrap_info->mainInfo.main_size.width;
    isp_core_info->otcInfo.otc_out_size.height_st= (isp_core_info->itcInfo.itc_size.height -isp_wrap_info->mainInfo.main_size.height)/2;
    if (isp_core_info->otcInfo.otc_out_size.height_st == 0)
        isp_core_info->otcInfo.otc_out_size.height_st = 4;
    isp_core_info->otcInfo.otc_out_size.height = isp_wrap_info->mainInfo.main_size.height;
    ret = ioctl(entity->fd, VIDIOC_K510ISP_F2K_CORE_CFG,isp_core_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd, VIDIOC_K510ISP_F2K_DS_CFG,isp_ds_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd,VIDIOC_K510ISP_F2K_CFG_SET,isp_cfg);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    v4l2_subdev_close(entity);
    return 0;
}
/**
 * @brief
 *
 * @param entity
 * @return int
 */
int sysctl_rst_r2k(struct media_entity *entity)
{
    int ret = 0;
    //
    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    unsigned int rst_en = 1;
    ret = ioctl(entity->fd,VIDIOC_K510ISP_SYSCTL_RST_R2K,&rst_en);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return ret;
}
/**
 * @brief
 * @param entity
 * @param isp_cfg
 * @return int
 */
int isp_r2k_cfg(struct media_entity *entity,struct isp_cfg_info *isp_cfg,uint32_t phyAddr)
{
    int ret = 0;
    struct isp_wrap_cfg_info *isp_wrap_info = &isp_cfg->isp_wrap_cfg;
    struct isp_core_cfg_info *isp_core_info = &isp_cfg->isp_core_cfg;
    struct isp_ds_cfg_info *isp_ds_info = &isp_cfg->isp_ds_cfg;
    unsigned int width = 0,height = 0;
    unsigned int line_stride = 0;
    //
    ret = v4l2_subdev_open(entity);
    if (ret < 0)
        return ret;
    //
    width = isp_wrap_info->mainInfo.main_size.width;
    height = isp_wrap_info->mainInfo.main_size.height;
    line_stride = calc_stride(width);
    isp_wrap_info->mainInfo.main_line_stride = line_stride;
    isp_wrap_info->mainInfo.main_y_buf0_base = phyAddr;
    isp_wrap_info->mainInfo.main_y_buf1_base = phyAddr;
    isp_wrap_info->mainInfo.main_uv_buf0_base = phyAddr + line_stride*height;
    isp_wrap_info->mainInfo.main_uv_buf1_base = phyAddr + line_stride*height;

    /*
    // 3dnr
    isp_wrap_info->nr3dInfo.nr3d_y_line_stride = line_stride;
    isp_wrap_info->nr3dInfo.nr3d_uv_line_stride = line_stride;
    isp_wrap_info->nr3dInfo.nr3d_y_buf_base = phyAddr + 4096 * 1024;
    isp_wrap_info->nr3dInfo.nr3d_uv_buf_base = phyAddr + 4096 * 1024 + line_stride * height;

    // ldc
    isp_wrap_info->ldcInfo.ldc_line_stride = line_stride;
    isp_wrap_info->ldcInfo.ldc_y_buf_base = phyAddr + 4096 * 1024 * 2;
    isp_wrap_info->ldcInfo.ldc_uv_buf_base = phyAddr + 4096 * 1024 * 2 + line_stride * height;
     */

    //
    width = isp_wrap_info->ds0Info.ds0_size.width;
    line_stride = calc_stride(width);
    isp_wrap_info->ds0Info.ds0_line_stride = line_stride;
    isp_wrap_info->ds0Info.ds0_out_en = 1;//must enable
    isp_ds_info->dsInfo[0].scale_en = 1;
    isp_ds_info->dsInfo[0].vscale_filter_en = 1;
    isp_ds_info->dsInfo[0].hscale_filter_en = 1;
    isp_wrap_info->ds0Info.ds0_y_buf0_base = phyAddr;
    isp_wrap_info->ds0Info.ds0_y_buf1_base = phyAddr;
    isp_wrap_info->ds0Info.ds0_uv_buf0_base = phyAddr+line_stride*height;
    isp_wrap_info->ds0Info.ds0_uv_buf1_base = phyAddr+line_stride*height;
    //
    width = isp_wrap_info->ds1Info.ds1_size.width;
    line_stride = calc_stride(width);
    isp_wrap_info->ds1Info.ds1_line_stride = line_stride;
    isp_wrap_info->ds1Info.ds1_y_buf0_base = phyAddr;
    isp_wrap_info->ds1Info.ds1_y_buf1_base = phyAddr;
    isp_wrap_info->ds1Info.ds1_uv_buf0_base = phyAddr+line_stride*height;
    isp_wrap_info->ds1Info.ds1_uv_buf1_base = phyAddr+line_stride*height;

    //
    //width = isp_wrap_info->ds2Info.ds2_size.width;
    width = isp_wrap_info->ds2Info.ds2_size.pitch;
    line_stride = calc_stride(width);
    if( OUT_ARGB == isp_wrap_info->ds2Info.ds2_out_img_out_format)
    {
        isp_wrap_info->ds2Info.ds2_line_stride = line_stride*4;
        isp_wrap_info->ds2Info.ds2_r_buf0_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_r_buf1_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_g_buf0_base = phyAddr + line_stride*2;
        isp_wrap_info->ds2Info.ds2_g_buf1_base = phyAddr + line_stride*2;
        isp_wrap_info->ds2Info.ds2_b_buf0_base = phyAddr + line_stride*3;
        isp_wrap_info->ds2Info.ds2_b_buf1_base = phyAddr + line_stride*3;
    }
    else
    {
        isp_wrap_info->ds2Info.ds2_line_stride = line_stride;
        isp_wrap_info->ds2Info.ds2_r_buf0_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_r_buf1_base = phyAddr;
        isp_wrap_info->ds2Info.ds2_g_buf0_base = phyAddr + line_stride*height;
        isp_wrap_info->ds2Info.ds2_g_buf1_base = phyAddr + line_stride*height;
        isp_wrap_info->ds2Info.ds2_b_buf0_base = phyAddr + line_stride*height*2;
        isp_wrap_info->ds2Info.ds2_b_buf1_base = phyAddr + line_stride*height*2;
    }

    // enable pixel remap
    isp_wrap_info->mainInfo.main_pix_remap_en = 1;
    isp_wrap_info->ds0Info.pix_remap_out0_en = 1;
    isp_wrap_info->ds1Info.pix_remap_out1_en = 1;

    ret = ioctl(entity->fd, VIDIOC_K510ISP_R2K_WRAP_CFG,isp_wrap_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    isp_core_info->otcInfo.otc_out_size.width_st = (isp_core_info->itcInfo.itc_size.width - isp_wrap_info->mainInfo.main_size.width)/2;
    if (isp_core_info->otcInfo.otc_out_size.width_st == 0)
        isp_core_info->otcInfo.otc_out_size.width_st = 4;
    isp_core_info->otcInfo.otc_out_size.width = isp_wrap_info->mainInfo.main_size.width;
    isp_core_info->otcInfo.otc_out_size.height_st= (isp_core_info->itcInfo.itc_size.height -isp_wrap_info->mainInfo.main_size.height)/2;
    if (isp_core_info->otcInfo.otc_out_size.height_st == 0)
        isp_core_info->otcInfo.otc_out_size.height_st = 4;
    isp_core_info->otcInfo.otc_out_size.height = isp_wrap_info->mainInfo.main_size.height;
    ret = ioctl(entity->fd, VIDIOC_K510ISP_R2K_CORE_CFG,isp_core_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd, VIDIOC_K510ISP_R2K_DS_CFG,isp_ds_info);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }
    //
    ret = ioctl(entity->fd,VIDIOC_K510ISP_R2K_CFG_SET,isp_cfg);
    if (ret < 0)
    {
        printf("%s: ioctl failed ret(%d)\n", __func__,
                ret);
        v4l2_subdev_close(entity);
        return -errno;
    }

    v4l2_subdev_close(entity);
    return 0;
}
/**
 * @brief
 *
 * @param mipi_csi2
 */
void print_csi2_info(struct isp_csi2_info *mipi_csi2)
{
    printf("%s:start\n",__func__);
    printf("csi0_used:%d\n",mipi_csi2->csi0_used);
    printf("csi0_sony_wdr:%d\n",mipi_csi2->csi0_sony_wdr);
    printf("csi0_lane_nb:%d\n",mipi_csi2->csi0_lane_nb);
    printf("csi0_dl0_map:%d\n",mipi_csi2->csi0_dl0_map);
    printf("csi0_dl1_map:%d\n",mipi_csi2->csi0_dl1_map);
    printf("csi0_dl2_map:%d\n",mipi_csi2->csi0_dl2_map);
    printf("csi0_dl3_map:%d\n",mipi_csi2->csi0_dl3_map);
    //
    printf("csi00_datatype_select0:%d\n",mipi_csi2->csi00_datatype_select0);
    printf("csi00_datatype_select1:%d\n",mipi_csi2->csi00_datatype_select1);
    printf("csi00_vc_select:%d\n",mipi_csi2->csi00_vc_select);
    //
    printf("csi01_datatype_select0:%d\n",mipi_csi2->csi01_datatype_select0);
    printf("csi01_datatype_select1:%d\n",mipi_csi2->csi01_datatype_select1);
    printf("csi01_vc_select:%d\n",mipi_csi2->csi01_vc_select);
    //
    printf("csi02_datatype_select0:%d\n",mipi_csi2->csi02_datatype_select0);
    printf("csi02_datatype_select1:%d\n",mipi_csi2->csi02_datatype_select1);
    printf("csi02_vc_select:%d\n",mipi_csi2->csi02_vc_select);
    //
    printf("csi1_used:%d\n",mipi_csi2->csi1_used);
    printf("csi1_sony_wdr:%d\n",mipi_csi2->csi1_sony_wdr);
    printf("csi1_lane_nb:%d\n",mipi_csi2->csi1_lane_nb);
    printf("csi1_dl0_map:%d\n",mipi_csi2->csi1_dl0_map);
    printf("csi1_dl1_map:%d\n",mipi_csi2->csi1_dl1_map);
    printf("csi1_dl2_map:%d\n",mipi_csi2->csi1_dl2_map);
    printf("csi1_dl3_map:%d\n",mipi_csi2->csi1_dl3_map);
    //
    printf("csi10_datatype_select0:%d\n",mipi_csi2->csi10_datatype_select0);
    printf("csi10_datatype_select1:%d\n",mipi_csi2->csi10_datatype_select1);
    printf("csi10_vc_select:%d\n",mipi_csi2->csi10_vc_select);
    printf("%s:end\n",__func__);
}
/**
 * @brief
 *
 * @param vi_cfg
 */
void print_vi_info(struct vi_cfg_info *vi_cfg)
{
    printf("%s:start\n",__func__);
    //
    struct vi_wrap_cfg_info *vi_wrap_cfg = &vi_cfg->vi_wrap_cfg;
    printf("dphy_mode:%d\n",vi_wrap_cfg->dphy_mode);
    printf("sony_mode:%d\n",vi_wrap_cfg->sony_mode);
    struct sensor_info_s *sensor_info= &vi_wrap_cfg->sensor_info[0];
    printf("0 sensor_interface_en:%d\n",sensor_info->sensor_interface_en);
    printf("0 tpg_w_en:%d\n",sensor_info->tpg_w_en);
    printf("0 tpg_r_en:%d\n",sensor_info->tpg_r_en);
    printf("0 wdr_sensor_vendor:%d\n",sensor_info->wdr_sensor_vendor);
    printf("0 wdr_mode:%d\n",sensor_info->wdr_mode);
    printf("0 mipi_mode:%d\n",sensor_info->mipi_mode);
    printf("0 isp_pipeline:%d\n",sensor_info->isp_pipeline);
    sensor_info = &vi_wrap_cfg->sensor_info[1];
    printf("1 sensor_interface_en:%d\n",sensor_info->sensor_interface_en);
    printf("1 tpg_w_en:%d\n",sensor_info->tpg_w_en);
    printf("1 tpg_r_en:%d\n",sensor_info->tpg_r_en);
    printf("1 wdr_sensor_vendor:%d\n",sensor_info->wdr_sensor_vendor);
    printf("1 wdr_mode:%d\n",sensor_info->wdr_mode);
    printf("1 mipi_mode:%d\n",sensor_info->mipi_mode);
    printf("1 isp_pipeline:%d\n",sensor_info->isp_pipeline);
    sensor_info = &vi_wrap_cfg->sensor_info[2];
    printf("2 sensor_interface_en:%d\n",sensor_info->sensor_interface_en);
    printf("2 tpg_w_en:%d\n",sensor_info->tpg_w_en);
    printf("2 tpg_r_en:%d\n",sensor_info->tpg_r_en);
    printf("2 wdr_sensor_vendor:%d\n",sensor_info->wdr_sensor_vendor);
    printf("2 wdr_mode:%d\n",sensor_info->wdr_mode);
    printf("2 mipi_mode:%d\n",sensor_info->mipi_mode);
    printf("2 isp_pipeline:%d\n",sensor_info->isp_pipeline);
    //
    struct vi_pipe_cfg_info  *vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[0];
    printf("p00 win_mode_en:%d\n",vi_pipe_cfg->win_mode_en);
    printf("p00 input_ch_sel:%d\n",vi_pipe_cfg->input_ch_sel);
    printf("p00 ch_mode_sel:%d\n",vi_pipe_cfg->ch_mode_sel);
    printf("p00 pixel_type:%d\n",vi_pipe_cfg->pixel_type);
    printf("p00 yuv_in_format:%d\n",vi_pipe_cfg->yuv_in_format);
    printf("p00 yuv_out_format:%d\n",vi_pipe_cfg->yuv_out_format);
    printf("p00 yuv422_order:%d\n",vi_pipe_cfg->yuv422_order);
    printf("p00 pixel_width:%d\n",vi_pipe_cfg->pixel_width);
    printf("p00 data_out_timming_ctrl:%d\n",vi_pipe_cfg->data_out_timming_ctrl);
    printf("p00 sync_pulse_mode:%d\n",vi_pipe_cfg->sync_pulse_mode);
    printf("p00 sen_mipi_clk_pol:%d\n",vi_pipe_cfg->sen_mipi_clk_pol);
    printf("p00 sen_mipi_vsync_pol:%d\n",vi_pipe_cfg->sen_mipi_vsync_pol);
    printf("p00 sen_mipi_hsync_pol:%d\n",vi_pipe_cfg->sen_mipi_hsync_pol);
    printf("p00 sen_mipi_field_pol:%d\n",vi_pipe_cfg->sen_mipi_field_pol);
    printf("p00 isp_clk_pol:%d\n",vi_pipe_cfg->isp_clk_pol);
    printf("p00 isp_vsync_pol:%d\n",vi_pipe_cfg->isp_vsync_pol);
    printf("p00 isp_hsync_pol:%d\n",vi_pipe_cfg->isp_hsync_pol);
    printf("p00 isp_field_pol:%d\n",vi_pipe_cfg->isp_field_pol);
    printf("p00 tpg_w_en:%d\n",vi_pipe_cfg->tpg_w_en);
    printf("p00 tpg_r_en:%d\n",vi_pipe_cfg->tpg_r_en);
    printf("p00 total_size.width:%d\n",vi_pipe_cfg->total_size.width);
    printf("p00 total_size.height:%d\n",vi_pipe_cfg->total_size.height);
    printf("p00 in_size.width:%d\n",vi_pipe_cfg->in_size.width);
    printf("p00 in_size.height:%d\n",vi_pipe_cfg->in_size.height);
    printf("p00 w_size_st.width:%d\n",vi_pipe_cfg->w_size_st.width);
    printf("p00 w_size_st.height:%d\n",vi_pipe_cfg->w_size_st.height);
    printf("p00 r_size_st.width:%d\n",vi_pipe_cfg->r_size_st.width);
    printf("p00 r_size_st.height:%d\n",vi_pipe_cfg->r_size_st.height);
    printf("p00 vi_pipe_w_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y0);
    printf("p00 vi_pipe_w_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y1);
    printf("p00 vi_pipe_w_addr_uv0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv0);
    printf("p00 vi_pipe_w_addr_uv1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv1);
    printf("p00 vi_pipe_r_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y0);
    printf("p00 vi_pipe_r_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y1);
    printf("p00 vi_pipe_addr_stride:%d\n",vi_pipe_cfg->vi_pipe_addr_stride);
    printf("p00 tof_mode_enable:%d\n",vi_pipe_cfg->tof_mode_enable);
    printf("p00 vi_pipe_tpg_tof_frm_num:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_num);
    printf("p00 vi_pipe_tpg_tof_frm_stride:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride);
    //p01
    vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[1];
    printf("p01 win_mode_en:%d\n",vi_pipe_cfg->win_mode_en);
    printf("p01 input_ch_sel:%d\n",vi_pipe_cfg->input_ch_sel);
    printf("p01 ch_mode_sel:%d\n",vi_pipe_cfg->ch_mode_sel);
    printf("p01 pixel_type:%d\n",vi_pipe_cfg->pixel_type);
    printf("p01 yuv_in_format:%d\n",vi_pipe_cfg->yuv_in_format);
    printf("p01 yuv_out_format:%d\n",vi_pipe_cfg->yuv_out_format);
    printf("p01 yuv422_order:%d\n",vi_pipe_cfg->yuv422_order);
    printf("p01 pixel_width:%d\n",vi_pipe_cfg->pixel_width);
    printf("p01 data_out_timming_ctrl:%d\n",vi_pipe_cfg->data_out_timming_ctrl);
    printf("p01 sync_pulse_mode:%d\n",vi_pipe_cfg->sync_pulse_mode);
    printf("p01 sen_mipi_clk_pol:%d\n",vi_pipe_cfg->sen_mipi_clk_pol);
    printf("p01 sen_mipi_vsync_pol:%d\n",vi_pipe_cfg->sen_mipi_vsync_pol);
    printf("p01 sen_mipi_hsync_pol:%d\n",vi_pipe_cfg->sen_mipi_hsync_pol);
    printf("p01 sen_mipi_field_pol:%d\n",vi_pipe_cfg->sen_mipi_field_pol);
    printf("p01 isp_clk_pol:%d\n",vi_pipe_cfg->isp_clk_pol);
    printf("p01 isp_vsync_pol:%d\n",vi_pipe_cfg->isp_vsync_pol);
    printf("p01 isp_hsync_pol:%d\n",vi_pipe_cfg->isp_hsync_pol);
    printf("p01 isp_field_pol:%d\n",vi_pipe_cfg->isp_field_pol);
    printf("p01 tpg_w_en:%d\n",vi_pipe_cfg->tpg_w_en);
    printf("p01 tpg_r_en:%d\n",vi_pipe_cfg->tpg_r_en);
    printf("p01 total_size.width:%d\n",vi_pipe_cfg->total_size.width);
    printf("p01 total_size.height:%d\n",vi_pipe_cfg->total_size.height);
    printf("p01 in_size.width:%d\n",vi_pipe_cfg->in_size.width);
    printf("p01 in_size.height:%d\n",vi_pipe_cfg->in_size.height);
    printf("p01 w_size_st.width:%d\n",vi_pipe_cfg->w_size_st.width);
    printf("p01 w_size_st.height:%d\n",vi_pipe_cfg->w_size_st.height);
    printf("p01 r_size_st.width:%d\n",vi_pipe_cfg->r_size_st.width);
    printf("p01 r_size_st.height:%d\n",vi_pipe_cfg->r_size_st.height);
    printf("p01 vi_pipe_w_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y0);
    printf("p01 vi_pipe_w_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y1);
    printf("p01 vi_pipe_w_addr_uv0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv0);
    printf("p01 vi_pipe_w_addr_uv1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv1);
    printf("p01 vi_pipe_r_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y0);
    printf("p01 vi_pipe_r_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y1);
    printf("p01 vi_pipe_addr_stride:%d\n",vi_pipe_cfg->vi_pipe_addr_stride);
    printf("p01 tof_mode_enable:%d\n",vi_pipe_cfg->tof_mode_enable);
    printf("p01 vi_pipe_tpg_tof_frm_num:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_num);
    printf("p01 vi_pipe_tpg_tof_frm_stride:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride);
    //p02
    vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[2];
    printf("p02 win_mode_en:%d\n",vi_pipe_cfg->win_mode_en);
    printf("p02 input_ch_sel:%d\n",vi_pipe_cfg->input_ch_sel);
    printf("p02 ch_mode_sel:%d\n",vi_pipe_cfg->ch_mode_sel);
    printf("p02 pixel_type:%d\n",vi_pipe_cfg->pixel_type);
    printf("p02 yuv_in_format:%d\n",vi_pipe_cfg->yuv_in_format);
    printf("p02 yuv_out_format:%d\n",vi_pipe_cfg->yuv_out_format);
    printf("p02 yuv422_order:%d\n",vi_pipe_cfg->yuv422_order);
    printf("p02 pixel_width:%d\n",vi_pipe_cfg->pixel_width);
    printf("p02 data_out_timming_ctrl:%d\n",vi_pipe_cfg->data_out_timming_ctrl);
    printf("p02 sync_pulse_mode:%d\n",vi_pipe_cfg->sync_pulse_mode);
    printf("p02 sen_mipi_clk_pol:%d\n",vi_pipe_cfg->sen_mipi_clk_pol);
    printf("p02 sen_mipi_vsync_pol:%d\n",vi_pipe_cfg->sen_mipi_vsync_pol);
    printf("p02 sen_mipi_hsync_pol:%d\n",vi_pipe_cfg->sen_mipi_hsync_pol);
    printf("p02 sen_mipi_field_pol:%d\n",vi_pipe_cfg->sen_mipi_field_pol);
    printf("p02 isp_clk_pol:%d\n",vi_pipe_cfg->isp_clk_pol);
    printf("p02 isp_vsync_pol:%d\n",vi_pipe_cfg->isp_vsync_pol);
    printf("p02 isp_hsync_pol:%d\n",vi_pipe_cfg->isp_hsync_pol);
    printf("p02 isp_field_pol:%d\n",vi_pipe_cfg->isp_field_pol);
    printf("p02 tpg_w_en:%d\n",vi_pipe_cfg->tpg_w_en);
    printf("p02 tpg_r_en:%d\n",vi_pipe_cfg->tpg_r_en);
    printf("p02 total_size.width:%d\n",vi_pipe_cfg->total_size.width);
    printf("p02 total_size.height:%d\n",vi_pipe_cfg->total_size.height);
    printf("p02 in_size.width:%d\n",vi_pipe_cfg->in_size.width);
    printf("p02 in_size.height:%d\n",vi_pipe_cfg->in_size.height);
    printf("p02 w_size_st.width:%d\n",vi_pipe_cfg->w_size_st.width);
    printf("p02 w_size_st.height:%d\n",vi_pipe_cfg->w_size_st.height);
    printf("p02 r_size_st.width:%d\n",vi_pipe_cfg->r_size_st.width);
    printf("p02 r_size_st.height:%d\n",vi_pipe_cfg->r_size_st.height);
    printf("p02 vi_pipe_w_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y0);
    printf("p02 vi_pipe_w_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y1);
    printf("p02 vi_pipe_w_addr_uv0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv0);
    printf("p02 vi_pipe_w_addr_uv1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv1);
    printf("p02 vi_pipe_r_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y0);
    printf("p02 vi_pipe_r_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y1);
    printf("p02 vi_pipe_addr_stride:%d\n",vi_pipe_cfg->vi_pipe_addr_stride);
    printf("p02 tof_mode_enable:%d\n",vi_pipe_cfg->tof_mode_enable);
    printf("p02 vi_pipe_tpg_tof_frm_num:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_num);
    printf("p02 vi_pipe_tpg_tof_frm_stride:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride);
    //p10
    vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[3];
    printf("p10 win_mode_en:%d\n",vi_pipe_cfg->win_mode_en);
    printf("p10 input_ch_sel:%d\n",vi_pipe_cfg->input_ch_sel);
    printf("p10 ch_mode_sel:%d\n",vi_pipe_cfg->ch_mode_sel);
    printf("p10 pixel_type:%d\n",vi_pipe_cfg->pixel_type);
    printf("p10 yuv_in_format:%d\n",vi_pipe_cfg->yuv_in_format);
    printf("p10 yuv_out_format:%d\n",vi_pipe_cfg->yuv_out_format);
    printf("p10 yuv422_order:%d\n",vi_pipe_cfg->yuv422_order);
    printf("p10 pixel_width:%d\n",vi_pipe_cfg->pixel_width);
    printf("p10 data_out_timming_ctrl:%d\n",vi_pipe_cfg->data_out_timming_ctrl);
    printf("p10 sync_pulse_mode:%d\n",vi_pipe_cfg->sync_pulse_mode);
    printf("p10 sen_mipi_clk_pol:%d\n",vi_pipe_cfg->sen_mipi_clk_pol);
    printf("p10 sen_mipi_vsync_pol:%d\n",vi_pipe_cfg->sen_mipi_vsync_pol);
    printf("p10 sen_mipi_hsync_pol:%d\n",vi_pipe_cfg->sen_mipi_hsync_pol);
    printf("p10 sen_mipi_field_pol:%d\n",vi_pipe_cfg->sen_mipi_field_pol);
    printf("p10 isp_clk_pol:%d\n",vi_pipe_cfg->isp_clk_pol);
    printf("p10 isp_vsync_pol:%d\n",vi_pipe_cfg->isp_vsync_pol);
    printf("p10 isp_hsync_pol:%d\n",vi_pipe_cfg->isp_hsync_pol);
    printf("p10 isp_field_pol:%d\n",vi_pipe_cfg->isp_field_pol);
    printf("p10 tpg_w_en:%d\n",vi_pipe_cfg->tpg_w_en);
    printf("p10 tpg_r_en:%d\n",vi_pipe_cfg->tpg_r_en);
    printf("p10 total_size.width:%d\n",vi_pipe_cfg->total_size.width);
    printf("p10 total_size.height:%d\n",vi_pipe_cfg->total_size.height);
    printf("p10 in_size.width:%d\n",vi_pipe_cfg->in_size.width);
    printf("p10 in_size.height:%d\n",vi_pipe_cfg->in_size.height);
    printf("p10 w_size_st.width:%d\n",vi_pipe_cfg->w_size_st.width);
    printf("p10 w_size_st.height:%d\n",vi_pipe_cfg->w_size_st.height);
    printf("p10 r_size_st.width:%d\n",vi_pipe_cfg->r_size_st.width);
    printf("p10 r_size_st.height:%d\n",vi_pipe_cfg->r_size_st.height);
    printf("p10 vi_pipe_w_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y0);
    printf("p10 vi_pipe_w_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y1);
    printf("p10 vi_pipe_w_addr_uv0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv0);
    printf("p10 vi_pipe_w_addr_uv1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv1);
    printf("p10 vi_pipe_r_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y0);
    printf("p10 vi_pipe_r_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y1);
    printf("p10 vi_pipe_addr_stride:%d\n",vi_pipe_cfg->vi_pipe_addr_stride);
    printf("p10 tof_mode_enable:%d\n",vi_pipe_cfg->tof_mode_enable);
    printf("p10 vi_pipe_tpg_tof_frm_num:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_num);
    printf("p10 vi_pipe_tpg_tof_frm_stride:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride);
    //dvp
    vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[6];
    printf("dvp00 win_mode_en:%d\n",vi_pipe_cfg->win_mode_en);
    printf("dvp00 input_ch_sel:%d\n",vi_pipe_cfg->input_ch_sel);
    printf("dvp00 ch_mode_sel:%d\n",vi_pipe_cfg->ch_mode_sel);
    printf("dvp00 pixel_type:%d\n",vi_pipe_cfg->pixel_type);
    printf("dvp00 yuv_in_format:%d\n",vi_pipe_cfg->yuv_in_format);
    printf("dvp00 yuv_out_format:%d\n",vi_pipe_cfg->yuv_out_format);
    printf("dvp00 yuv422_order:%d\n",vi_pipe_cfg->yuv422_order);
    printf("dvp00 pixel_width:%d\n",vi_pipe_cfg->pixel_width);
    printf("dvp00 data_out_timming_ctrl:%d\n",vi_pipe_cfg->data_out_timming_ctrl);
    printf("dvp00 sync_pulse_mode:%d\n",vi_pipe_cfg->sync_pulse_mode);
    printf("dvp00 sen_mipi_clk_pol:%d\n",vi_pipe_cfg->sen_mipi_clk_pol);
    printf("dvp00 sen_mipi_vsync_pol:%d\n",vi_pipe_cfg->sen_mipi_vsync_pol);
    printf("dvp00 sen_mipi_hsync_pol:%d\n",vi_pipe_cfg->sen_mipi_hsync_pol);
    printf("dvp00 sen_mipi_field_pol:%d\n",vi_pipe_cfg->sen_mipi_field_pol);
    printf("dvp00 isp_clk_pol:%d\n",vi_pipe_cfg->isp_clk_pol);
    printf("dvp00 isp_vsync_pol:%d\n",vi_pipe_cfg->isp_vsync_pol);
    printf("dvp00 isp_hsync_pol:%d\n",vi_pipe_cfg->isp_hsync_pol);
    printf("dvp00 isp_field_pol:%d\n",vi_pipe_cfg->isp_field_pol);
    printf("dvp00 tpg_w_en:%d\n",vi_pipe_cfg->tpg_w_en);
    printf("dvp00 tpg_r_en:%d\n",vi_pipe_cfg->tpg_r_en);
    printf("dvp00 total_size.width:%d\n",vi_pipe_cfg->total_size.width);
    printf("dvp00 total_size.height:%d\n",vi_pipe_cfg->total_size.height);
    printf("dvp00 in_size.width:%d\n",vi_pipe_cfg->in_size.width);
    printf("dvp00 in_size.height:%d\n",vi_pipe_cfg->in_size.height);
    printf("dvp00 w_size_st.width:%d\n",vi_pipe_cfg->w_size_st.width);
    printf("dvp00 w_size_st.height:%d\n",vi_pipe_cfg->w_size_st.height);
    printf("dvp00 r_size_st.width:%d\n",vi_pipe_cfg->r_size_st.width);
    printf("dvp00 r_size_st.height:%d\n",vi_pipe_cfg->r_size_st.height);
    printf("dvp00 vi_pipe_w_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y0);
    printf("dvp00 vi_pipe_w_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_y1);
    printf("dvp00 vi_pipe_w_addr_uv0:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv0);
    printf("dvp00 vi_pipe_w_addr_uv1:%d\n",vi_pipe_cfg->vi_pipe_w_addr_uv1);
    printf("dvp00 vi_pipe_r_addr_y0:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y0);
    printf("dvp00 vi_pipe_r_addr_y1:%d\n",vi_pipe_cfg->vi_pipe_r_addr_y1);
    printf("dvp00 vi_pipe_addr_stride:%d\n",vi_pipe_cfg->vi_pipe_addr_stride);
    printf("dvp00 tof_mode_enable:%d\n",vi_pipe_cfg->tof_mode_enable);
    printf("dvp00 vi_pipe_tpg_tof_frm_num:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_num);
    printf("dvp00 vi_pipe_tpg_tof_frm_stride:%d\n",vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride);

    printf("%s:end\n",__func__);
}
/**
 * @brief
 *
 * @param isp_cfg
 */
void print_isp_info(struct isp_cfg_info *isp_cfg)
{
    printf("%s:start\n",__func__);
    //
    struct isp_wrap_cfg_info  *isp_wrap_cfg = &isp_cfg->isp_wrap_cfg;
    printf("isp_out_sel:%d\n",isp_wrap_cfg->isp_out_sel);
    printf("dvp_ch_mode:%d\n",isp_wrap_cfg->dvp_ch_mode);
    printf("hist_3a_out_en:%d\n",isp_wrap_cfg->hist_3a_out_en);
    //
    struct isp_wrap_wdr_info   *wwdrInfo = &isp_wrap_cfg->wdrInfo;
    printf("wdr_mode:%d\n",wwdrInfo->wdr_mode);
    printf("wdr_long_ch_mode:%d\n",wwdrInfo->wdr_long_ch_mode);
    printf("wdr_long_l2_buf_en:%d\n",wwdrInfo->wdr_long_l2_buf_en);
    printf("wdr_short_s1_buf_en:%d\n",wwdrInfo->wdr_short_s1_buf_en);
    printf("wdr_dynamic_switch_en:%d\n",wwdrInfo->wdr_dynamic_switch_en);
    printf("wdr_long_l2_buf_depth:%d\n",wwdrInfo->wdr_long_l2_buf_depth);
    printf("wdr_long_img_format:%d\n",wwdrInfo->wdr_long_img_format);
    printf("wdr_long_yuv_in_format:%d\n",wwdrInfo->wdr_long_yuv_in_format);
    printf("wdr_long_img_out_format:%d\n",wwdrInfo->wdr_long_img_out_format);
    printf("wdr_long_yuv422_pxl_order:%d\n",wwdrInfo->wdr_long_yuv422_pxl_order);
    printf("wdr_long_pixel_width:%d\n",wwdrInfo->wdr_long_pixel_width);
    printf("wdr_buf_base:%d\n",wwdrInfo->wdr_buf_base);
    printf("wdr_line_stride:%d\n",wwdrInfo->wdr_line_stride);
    printf("wdr_frame_buf_size:%d\n",wwdrInfo->wdr_frame_buf_size);
    //
    struct isp_wrap_3dnr_info  *wnr3dInfo = &isp_wrap_cfg->nr3dInfo;
    printf("nr3d_en:%d\n",wnr3dInfo->nr3d_en );
    printf("nr3d_fbcd_en:%d\n",wnr3dInfo->nr3d_fbcd_en);
    printf("nr3d_mv_out_en:%d\n",wnr3dInfo->nr3d_mv_out_en);
    printf("nr3d_y_img_format:%d\n",wnr3dInfo->nr3d_y_img_format);
    printf("nr3d_y_yuv_in_format:%d\n",wnr3dInfo->nr3d_y_yuv_in_format);
    printf("nr3d_y_img_out_format:%d\n",wnr3dInfo->nr3d_y_img_out_format);
    printf("nr3d_y_yuv422_pxl_order:%d\n",wnr3dInfo->nr3d_y_yuv422_pxl_order);
    printf("nr3d_y_pixel_width:%d\n",wnr3dInfo->nr3d_y_pixel_width);
    printf("nr3d_uv_img_format:%d\n",wnr3dInfo->nr3d_uv_img_format);
    printf("nr3d_uv_yuv_in_format:%d\n",wnr3dInfo->nr3d_uv_yuv_in_format);
    printf("nr3d_uv_mig_out_format:%d\n",wnr3dInfo->nr3d_uv_mig_out_format);
    printf("nr3d_uv_yuv422_pxl_order:%d\n",wnr3dInfo->nr3d_uv_yuv422_pxl_order);
    printf("nr3d_uv_pixel_width:%d\n",wnr3dInfo->nr3d_uv_pixel_width);
    printf("nr3d_y_buf_base:%d\n",wnr3dInfo->nr3d_y_buf_base);
    printf("nr3d_uv_buf_base:%d\n",wnr3dInfo->nr3d_uv_buf_base);
    printf("nr3d_y_line_stride:%d\n",wnr3dInfo->nr3d_y_line_stride);
    printf("nr3d_uv_line_stride:%d\n",wnr3dInfo->nr3d_uv_line_stride);
    printf("nr3d_frame_buf_size:%d\n",wnr3dInfo->nr3d_frame_buf_size);
    //
    struct isp_wrap_ldc_info   *wldcInfo = &isp_wrap_cfg->ldcInfo;
    printf("ldc_en:%d\n",wldcInfo->ldc_en);
    printf("ldc_y_buf_base:%d\n",wldcInfo->ldc_y_buf_base);
    printf("ldc_uv_buf_base:%d\n",wldcInfo->ldc_uv_buf_base);
    printf("ldc_line_stride:%d\n",wldcInfo->ldc_line_stride);
    printf("ldc_frame_buf_size:%d\n",wldcInfo->ldc_frame_buf_size);
    //
    struct isp_wrap_main_info  *mainInfo = &isp_wrap_cfg->mainInfo;
    printf("main_out_en:%d\n",mainInfo->main_out_en);
    printf("main_size.width:%d\n",mainInfo->main_size.width);
    printf("main_size.height:%d\n",mainInfo->main_size.height);
    printf("main_pix_remap_en:%d\n",mainInfo->main_pix_remap_en);
    printf("main_out_img_format:%d\n",mainInfo->main_out_img_format);
    printf("main_out_yuv_in_format:%d\n",mainInfo->main_out_yuv_in_format);
    printf("main_out_img_out_format:%d\n",mainInfo->main_out_img_out_format);
    printf("main_out_yuv422_pxl_order:%d\n",mainInfo->main_out_yuv422_pxl_order);
    printf("main_out_pxl_width:%d\n",mainInfo->main_out_pxl_width);
    printf("main_y_buf0_base:%d\n",mainInfo->main_y_buf0_base);
    printf("main_y_buf1_base:%d\n",mainInfo->main_y_buf1_base);
    printf("main_uv_buf0_base:%d\n",mainInfo->main_uv_buf0_base);
    printf("main_uv_buf1_base:%d\n",mainInfo->main_uv_buf1_base);
    printf("main_line_stride:%d\n",mainInfo->main_line_stride);
    printf("main_frame_buf_size:%d\n",mainInfo->main_frame_buf_size);
    //
    struct isp_wrap_ds0_info   *ds0Info = &isp_wrap_cfg->ds0Info;
    printf("ds0_out_en:%d\n",ds0Info->ds0_out_en);
    printf("ds0_osd0_en:%d\n",ds0Info->ds0_osd0_en );
    printf("ds0_osd1_en:%d\n",ds0Info->ds0_osd1_en );
    printf("ds0_osd2_en:%d\n",ds0Info->ds0_osd2_en );
    printf("pix_remap_out0_en:%d\n",ds0Info->pix_remap_out0_en);
    printf("ds0_size.width:%d\n",ds0Info->ds0_size.width);
    printf("ds0_size.height:%d\n",ds0Info->ds0_size.height);
    printf("ds0_out_img_format:%d\n",ds0Info->ds0_out_img_format);
    printf("ds0_out_yuv_in_format:%d\n",ds0Info->ds0_out_yuv_in_format);
    printf("ds0_out_img_out_format:%d\n",ds0Info->ds0_out_img_out_format);
    printf("ds0_out_yuv422_pxl_order:%d\n",ds0Info->ds0_out_yuv422_pxl_order);
    printf("ds0_out_pxl_width:%d\n",ds0Info->ds0_out_pxl_width);
    printf("ds0_y_buf0_base:%d\n",ds0Info->ds0_y_buf0_base);
    printf("ds0_y_buf1_base:%d\n",ds0Info->ds0_y_buf1_base);
    printf("ds0_uv_buf0_base:%d\n",ds0Info->ds0_uv_buf0_base);
    printf("ds0_uv_buf1_base:%d\n",ds0Info->ds0_uv_buf1_base);
    printf("ds0_line_stride:%d\n",ds0Info->ds0_line_stride);
    printf("ds0_frame_buf_size:%d\n",ds0Info->ds0_frame_buf_size);
    //
    struct isp_wrap_ds1_info   *ds1Info = &isp_wrap_cfg->ds1Info;
    printf("ds1_out_en:%d\n",ds1Info->ds1_out_en);
    printf("ds1_osd0_en:%d\n",ds1Info->ds1_osd0_en );
    printf("ds1_osd1_en:%d\n",ds1Info->ds1_osd1_en );
    printf("ds1_osd2_en:%d\n",ds1Info->ds1_osd2_en );
    printf("pix_remap_out1_en:%d\n",ds1Info->pix_remap_out1_en);
    printf("ds1_size.width:%d\n",ds1Info->ds1_size.width);
    printf("ds1_size.height:%d\n",ds1Info->ds1_size.height);
    printf("ds1_out_img_format:%d\n",ds1Info->ds1_out_img_format);
    printf("ds1_out_yuv_in_format:%d\n",ds1Info->ds1_out_yuv_in_format);
    printf("ds1_out_img_out_format:%d\n",ds1Info->ds1_out_img_out_format);
    printf("ds1_out_yuv422_pxl_order:%d\n",ds1Info->ds1_out_yuv422_pxl_order);
    printf("ds1_out_pxl_width:%d\n",ds1Info->ds1_out_pxl_width);
    printf("ds1_y_buf0_base:%d\n",ds1Info->ds1_y_buf0_base);
    printf("ds1_y_buf1_base:%d\n",ds1Info->ds1_y_buf1_base);
    printf("ds1_uv_buf0_base:%d\n",ds1Info->ds1_uv_buf0_base);
    printf("ds1_uv_buf1_base:%d\n",ds1Info->ds1_uv_buf1_base);
    printf("ds1_line_stride:%d\n",ds1Info->ds1_line_stride);
    printf("ds1_frame_buf_size:%d\n",ds1Info->ds1_frame_buf_size);
    //
    struct isp_wrap_ds2_info   *ds2Info = &isp_wrap_cfg->ds2Info;
    printf("ds2_out_en:%d\n",ds2Info->ds2_out_en);
    printf("ds2_osd0_en:%d\n",ds2Info->ds2_osd0_en );
    printf("ds2_osd1_en:%d\n",ds2Info->ds2_osd1_en );
    printf("ds2_osd2_en:%d\n",ds2Info->ds2_osd2_en );
    printf("ds2_size.width:%d\n",ds2Info->ds2_size.width);
    printf("ds2_size.height:%d\n",ds2Info->ds2_size.height);
    printf("ds2_out_img_format:%d\n",ds2Info->ds2_out_img_format);
    printf("ds2_out_yuv_in_format:%d\n",ds2Info->ds2_out_yuv_in_format);
    printf("ds2_out_img_out_format:%d\n",ds2Info->ds2_out_img_out_format);
    printf("ds2_out_yuv422_pxl_order:%d\n",ds2Info->ds2_out_yuv422_pxl_order);
    printf("ds2_out_pxl_width:%d\n",ds2Info->ds2_out_pxl_width);
    printf("ds2_r_buf0_base:%d\n",ds2Info->ds2_r_buf0_base);
    printf("ds2_r_buf1_base:%d\n",ds2Info->ds2_r_buf1_base);
    printf("ds2_g_buf0_base:%d\n",ds2Info->ds2_g_buf0_base);
    printf("ds2_g_buf1_base:%d\n",ds2Info->ds2_g_buf1_base);
    printf("ds2_b_buf0_base:%d\n",ds2Info->ds2_b_buf0_base);
    printf("ds2_b_buf1_base:%d\n",ds2Info->ds2_b_buf1_base);
    printf("ds2_line_stride:%d\n",ds2Info->ds2_line_stride);
    printf("ds2_frame_buf_size:%d\n",ds2Info->ds2_frame_buf_size);
    //
    struct isp_core_cfg_info  *isp_core_cfg = &isp_cfg->isp_core_cfg;
    //itc
    struct itc_info_s    *itcInfo = &isp_core_cfg->itcInfo;
    printf("hsync_pol:%d\n",itcInfo->hsync_pol);
    printf("vsync_pol:%d\n",itcInfo->vsync_pol);
    printf("hsync_input_timing:%d\n",itcInfo->hsync_input_timing);
    printf("vsync_input_timing:%d\n",itcInfo->vsync_input_timing);
    printf("flip_ctl:%d\n",itcInfo->flip_ctl);
    printf("video_fmt_sel:%d\n",itcInfo->video_fmt_sel);
    printf("total_size.width:%d\n",itcInfo->total_size.width);
    printf("total_size.height:%d\n",itcInfo->total_size.height);
    printf("itc_size.width:%d\n",itcInfo->itc_size.width);
    printf("itc_size.width_st:%d\n",itcInfo->itc_size.width_st);
    printf("itc_size.height:%d\n",itcInfo->itc_size.height);
    printf("itc_size.height_st:%d\n",itcInfo->itc_size.height_st);
    //tpg    *
    struct tpg_info_s    *tpgInfo = &isp_core_cfg->tpgInfo;
    printf("tpg_en:%d\n",tpgInfo->tpg_en);
    printf("tpg_sel:%d\n",tpgInfo->tpg_sel);
    printf("bayer_mode_sel:%d\n",tpgInfo->bayer_mode_sel);
    printf("motion_mode_sel:%d\n",tpgInfo->motion_mode_sel);
    printf("wdr_l_mul_data:%d\n",tpgInfo->wdr_l_mul_data);
    printf("wdr_m_mul_data:%d\n",tpgInfo->wdr_m_mul_data);
    printf("wdr_s_mul_data:%d\n",tpgInfo->wdr_s_mul_data);
    //blc    *
    struct blc_info_s    *blcInfo = &isp_core_cfg->blcInfo;
    printf("blc_en:%d\n",blcInfo->blc_en);
    printf("blc_offset:%d\n",blcInfo->blc_offset);
    printf("blc_ratio:%d\n",blcInfo->blc_ratio);
    //lsc     *
    struct lsc_info_s    *lscInfo = &isp_core_cfg->lscInfo;
    printf("lsc_en:%d\n",lscInfo->lsc_en);
    printf("lsc_h_center:%d\n",lscInfo->lsc_h_center);
    printf("lsc_v_center:%d\n",lscInfo->lsc_v_center);
    printf("lsc_r_ratio:%d\n",lscInfo->lsc_r_ratio);
    printf("lsc_g_ratio:%d\n",lscInfo->lsc_g_ratio);
    printf("lsc_b_ratio:%d\n",lscInfo->lsc_b_ratio);
    printf("lsc_ir_ratio:%d\n",lscInfo->lsc_ir_ratio);
    //ae *
    struct ae_info_s     *aeInfo = &isp_core_cfg->aeInfo;
    printf("ae_as_en:%d\n",aeInfo->ae_as_en);
    printf("ae_ag_en:%d\n",aeInfo->ae_ag_en);
    printf("ae_airis_en:%d\n",aeInfo->ae_airis_en);
    printf("ae_enter_ls_sel:%d\n",aeInfo->ae_enter_ls_sel);
    printf("ae_exit_ls_sel:%d\n",aeInfo->ae_exit_ls_sel);
    printf("ae_win_mode_sel:%d\n",aeInfo->ae_win_mode_sel);
    printf("ae_back_light_mode_sel:%d\n",aeInfo->ae_back_light_mode_sel);
    printf("ae_day_change_en:%d\n",aeInfo->ae_day_change_en);
    printf("ae_day_change_sel:%d\n",aeInfo->ae_day_change_sel);
    printf("ae_win_size.v_start:%d\n",aeInfo->ae_win_size.v_start);
    printf("ae_win_size.h_start:%d\n",aeInfo->ae_win_size.h_start);
    printf("ae_win_size.v_end:%d\n",aeInfo->ae_win_size.v_end);
    printf("ae_win_size.h_end:%d\n",aeInfo->ae_win_size.h_end);
    printf("ae_tar_bright:%d\n",aeInfo->ae_tar_bright);
    printf("ae_tar_bright_range:%d\n",aeInfo->ae_tar_bright_range);
    printf("ae_l_ex_time:%d\n",aeInfo->ae_l_ex_time);
    printf("ae_m_ex_time:%d\n",aeInfo->ae_m_ex_time);
    printf("ae_s_ex_time:%d\n",aeInfo->ae_s_ex_time);
    printf("ae_agc:%d\n",aeInfo->ae_agc);
    printf("ae_ad_shuttle_freq:%d\n",aeInfo->ae_ad_shuttle_freq);
    printf("ae_ad_gain_freq:%d\n",aeInfo->ae_ad_gain_freq);
    printf("ae_adjust_step_max:%d\n",aeInfo->ae_adjust_step_max);
    printf("ae_ex_value_max:%d\n",aeInfo->ae_ex_value_max);
    printf("ae_ex_value_mid:%d\n",aeInfo->ae_ex_value_mid);
    printf("ae_ex_value_min:%d\n",aeInfo->ae_ex_value_min);
    printf("ae_gain_value_max:%d\n",aeInfo->ae_gain_value_max);
    printf("ae_gain_value_mid:%d\n",aeInfo->ae_gain_value_mid);
    printf("ae_gain_value_min:%d\n",aeInfo->ae_gain_value_min);
    printf("ae_dn_switch_ad_step_max:%d\n",aeInfo->ae_dn_switch_ad_step_max);
    printf("ae_dn_switch_wait_time:%d\n",aeInfo->ae_dn_switch_wait_time);
    printf("ape_max_diff:%d\n",aeInfo->ape_max_diff);
    printf("ape_drv_signal_max:%d\n",aeInfo->ape_drv_signal_max);
    printf("ape_coeff_distance:%d\n",aeInfo->ape_coeff_distance);
    printf("ape_coeff_speed:%d\n",aeInfo->ape_coeff_speed);
    printf("ape_coeff_acceleration:%d\n",aeInfo->ape_coeff_acceleration);
    printf("ape_drv_manual_value:%d\n",aeInfo->ape_drv_manual_value);
    printf("ape_damp_manual_value:%d\n",aeInfo->ape_damp_manual_value);
    //awb *
    struct awb_info_s    *awbInfo = &isp_core_cfg->awbInfo;
    printf("awb_d65_en:%d\n",awbInfo->awb_d65_en);
    printf("awb_ccm_en:%d\n",awbInfo->awb_ccm_en);
    printf("awb_en:%d\n",awbInfo->awb_en);
    printf("awb_mode_sel:%d\n",awbInfo->awb_mode_sel);
    printf("awb_hist_mode_sel:%d\n",awbInfo->awb_hist_mode_sel);
    printf("awb_veri_en:%d\n",awbInfo->awb_veri_en);
    printf("awb_fb_en:%d\n",awbInfo->awb_fb_en);
    printf("awb_value_save_en:%d\n",awbInfo->awb_value_save_en);
    printf("awb_ccm_adp_adjust_en:%d\n",awbInfo->awb_ccm_adp_adjust_en);
    printf("awb_stab_en:%d\n",awbInfo->awb_stab_en);
    printf("awb_d65_red_gain:%d\n",awbInfo->awb_d65_red_gain);
    printf("awb_d65_blue_gain:%d\n",awbInfo->awb_d65_blue_gain);
    printf("ccm_coff[0][0]:%d\n",awbInfo->ccm_coff[0][0]);
    printf("ccm_coff[0][1]:%d\n",awbInfo->ccm_coff[0][1]);
    printf("ccm_coff[0][2]:%d\n",awbInfo->ccm_coff[0][2]);
    printf("ccm_coff[1][0]:%d\n",awbInfo->ccm_coff[1][0]);
    printf("ccm_coff[1][1]:%d\n",awbInfo->ccm_coff[1][1]);
    printf("ccm_coff[1][2]:%d\n",awbInfo->ccm_coff[1][2]);
    printf("ccm_coff[2][0]:%d\n",awbInfo->ccm_coff[2][0]);
    printf("ccm_coff[2][1]:%d\n",awbInfo->ccm_coff[2][1]);
    printf("ccm_coff[2][2]:%d\n",awbInfo->ccm_coff[2][2]);
    printf("ccm_correct_coff:%d\n",awbInfo->ccm_correct_coff);
    printf("awb_win_size.v_start:%d\n",awbInfo->awb_win_size.v_start);
    printf("awb_win_size.h_start:%d\n",awbInfo->awb_win_size.h_start);
    printf("awb_win_size.v_end:%d\n",awbInfo->awb_win_size.v_end);
    printf("awb_win_size.h_end:%d\n",awbInfo->awb_win_size.h_end);
    printf("awb_correct_diff_th:%d\n",awbInfo->awb_correct_diff_th);
    printf("awb_color_changeres_time:%d\n",awbInfo->awb_color_changeres_time);
    printf("awb_historgram_th:%d\n",awbInfo->awb_historgram_th);
    printf("awb_red_gain_adjust:%d\n",awbInfo->awb_red_gain_adjust);
    printf("awb_green_gain_adjust:%d\n",awbInfo->awb_green_gain_adjust);
    printf("awb_blue_gain_adjust:%d\n",awbInfo->awb_blue_gain_adjust);
    printf("awb_red_max_value:%d\n",awbInfo->awb_red_max_value);
    printf("awb_blue_max_value:%d\n",awbInfo->awb_blue_max_value);
    printf("awb_red_min_value:%d\n",awbInfo->awb_red_min_value);
    printf("awb_blue_min_value:%d\n",awbInfo->awb_blue_min_value);
    printf("awb_red_obj_value:%d\n",awbInfo->awb_red_obj_value);
    printf("awb_blue_obj_value:%d\n",awbInfo->awb_blue_obj_value);
    //wdr *
    struct wdr_Info_s    *wdrInfo = &isp_core_cfg->wdrInfo;
    printf(" wdr_fusion_en:%d\n",wdrInfo->wdr_fusion_en);
    printf(" wdr_frame_sel:%d\n",wdrInfo->wdr_frame_sel);
    printf(" wdr_adp_adjust_en:%d\n",wdrInfo->wdr_adp_adjust_en);
    printf(" wdr_stab_en:%d\n",wdrInfo->wdr_stab_en);
    printf(" wdr_en:%d\n",wdrInfo->wdr_en);
    printf(" wdr_ghost_remove_en:%d\n",wdrInfo->wdr_ghost_remove_en);
    printf(" wdr_3frame_out_mode:%d\n",wdrInfo->wdr_3frame_out_mode);
    printf(" wdr_mode_sel:%d\n",wdrInfo->wdr_mode_sel);
    printf(" wdr_2frame_ex_ratio:%d\n",wdrInfo->wdr_2frame_ex_ratio);
    printf(" wdr_3frame_ex_ratio:%d\n",wdrInfo->wdr_3frame_ex_ratio);
    printf(" wdr_stat_img_sel:%d\n",wdrInfo->wdr_stat_img_sel);
    printf(" wdr_ltm_data_sel:%d\n",wdrInfo->wdr_ltm_data_sel);
    printf(" wdr_tz_data_sel:%d\n",wdrInfo->wdr_tz_data_sel);
    printf(" wdr_remove_purple_en:%d\n",wdrInfo->wdr_remove_purple_en);
    printf(" wdr_over_ex_ratio_th1:%d\n",wdrInfo->wdr_over_ex_ratio_th1);
    printf(" wdr_over_ex_ratio_th2:%d\n",wdrInfo->wdr_over_ex_ratio_th2);
    printf(" wdr_fusion_ratio_th:%d\n",wdrInfo->wdr_fusion_ratio_th);
    printf(" wdr_fusion_value1  :%d\n",wdrInfo->wdr_fusion_value1);
    printf(" wdr_fusion_value2:%d\n",wdrInfo->wdr_fusion_value2);
    //csc *
    struct csc_info_s    *cscInfo = &isp_core_cfg->cscInfo;
    printf("csc_r2y[0][0]:%d\n",cscInfo->csc_r2y[0][0]);
    printf("csc_r2y[0][1]:%d\n",cscInfo->csc_r2y[0][1]);
    printf("csc_r2y[0][2]:%d\n",cscInfo->csc_r2y[0][2]);
    printf("csc_r2y[1][0]:%d\n",cscInfo->csc_r2y[1][0]);
    printf("csc_r2y[1][1]:%d\n",cscInfo->csc_r2y[1][1]);
    printf("csc_r2y[1][2]:%d\n",cscInfo->csc_r2y[1][2]);
    printf("csc_r2y[2][0]:%d\n",cscInfo->csc_r2y[2][0]);
    printf("csc_r2y[2][1]:%d\n",cscInfo->csc_r2y[2][1]);
    printf("csc_r2y[2][2]:%d\n",cscInfo->csc_r2y[2][2]);
    //ada *
    struct ada_info_s    *adaInfo = &isp_core_cfg->adaInfo;
    printf("ada_rgb_gamma_en:\n",adaInfo->ada_rgb_gamma_en);
    printf("ada_yuv_gamma_en:\n",adaInfo->ada_yuv_gamma_en);
    printf("ada_adjust_en:\n",adaInfo->ada_adjust_en);
    printf("ada_img_stab_en:\n",adaInfo->ada_img_stab_en);
    printf("ada_ccr_en:\n",adaInfo->ada_ccr_en);
    printf("ada_adp_en:\n",adaInfo->ada_adp_en);
    printf("ada_adp_ccr_en:\n",adaInfo->ada_adp_ccr_en);
    printf("ada_stat_mode_sel:\n",adaInfo->ada_stat_mode_sel);
    printf("ada_enh_mode_sel:\n",adaInfo->ada_enh_mode_sel);
    printf("ada_stat_max_value:\n",adaInfo->ada_stat_max_value);
    printf("ada_ad_stren_max_value:\n",adaInfo->ada_ad_stren_max_value);
    printf("ada_win_size.v_start:\n",adaInfo->ada_win_size.v_start);
    printf("ada_win_size.h_start:\n",adaInfo->ada_win_size.h_start);
    printf("ada_win_size.v_end:\n",adaInfo->ada_win_size.v_end);
    printf("ada_win_size.h_end:\n",adaInfo->ada_win_size.h_end);
    //rgbir *
    struct rgbir_info_s  *rgbirInfo = &isp_core_cfg->rgbirInfo;
    printf("rgbir_en:%d\n",rgbirInfo->rgbir_en);
    printf("rgbir_rtf_en:%d\n",rgbirInfo->rgbir_rtf_en);
    printf("rgbir_rpc_en:%d\n",rgbirInfo->rgbir_rpc_en);
    printf("rgbir_fusion_en:%d\n",rgbirInfo->rgbir_fusion_en);
    printf("rgbir_output_sel:%d\n",rgbirInfo->rgbir_output_sel);
    printf("rgbir_rpc_max_value:%d\n",rgbirInfo->rgbir_rpc_max_value);
    printf("rgbir_rpc_color_coff:%d\n",rgbirInfo->rgbir_rpc_color_coff);
    printf("rgbir_rpc_luma_coff:%d\n",rgbirInfo->rgbir_rpc_luma_coff);
    printf("rgbir_rpc_th:%d\n",rgbirInfo->rgbir_rpc_th);
    printf("rgbir_rpc_th1:%d\n",rgbirInfo->rgbir_rpc_th1);
    //nr2d *
    struct nr2d_info_s   *nr2dInfo = &isp_core_cfg->nr2dInfo;
    printf("d2nr_pcf_en:%d\n",nr2dInfo->d2nr_pcf_en);
    printf("d2nr_raw_en:%d\n",nr2dInfo->d2nr_raw_en);
    printf("d2nr_edge_en:%d\n",nr2dInfo->d2nr_edge_en);
    printf("d2nr_bap_en:%d\n",nr2dInfo->d2nr_bap_en);
    printf("d2nr_luma_en:%d\n",nr2dInfo->d2nr_luma_en);
    printf("d2nr_chroma_en:%d\n",nr2dInfo->d2nr_chroma_en);
    printf("d2nr_pcf_adp_en:%d\n",nr2dInfo->d2nr_pcf_adp_en);
    printf("d2nr_raw_adp_en:%d\n",nr2dInfo->d2nr_raw_adp_en);
    printf("d2nr_luma_adp_en:%d\n",nr2dInfo->d2nr_luma_adp_en);
    printf("d2nr_chroma_adp_en:%d\n",nr2dInfo->d2nr_chroma_adp_en);
    printf("d2nr_raw_intensity:%d\n",nr2dInfo->d2nr_raw_intensity);
    printf("d2nr_bap_intensity:%d\n",nr2dInfo->d2nr_bap_intensity);
    printf("d2nr_edge_intensity:%d\n",nr2dInfo->d2nr_edge_intensity);
    printf("d2nr_luma_intensity:%d\n",nr2dInfo->d2nr_luma_intensity);
    printf("d2nr_chroma_intensity:%d\n",nr2dInfo->d2nr_chroma_intensity);
    //nr3d *
    struct nr3d_info_s   *nr3dInfo = &isp_core_cfg->nr3dInfo;
    printf("d3nr_en:%d\n",nr3dInfo->d3nr_en);
    printf("d3nr_pre_luma_en:%d\n",nr3dInfo->d3nr_pre_luma_en);
    printf("d3nr_pre_chroma_en:%d\n",nr3dInfo->d3nr_pre_chroma_en);
    printf("d3nr_main_luma_en:%d\n",nr3dInfo->d3nr_main_luma_en);
    printf("d3nr_main_chroma_en:%d\n",nr3dInfo->d3nr_main_chroma_en);
    printf("d3nr_post_luma_en:%d\n",nr3dInfo->d3nr_post_luma_en);
    printf("d3nr_post_chroma_en:%d\n",nr3dInfo->d3nr_post_chroma_en);
    printf("d3nr_2d_luma_en:%d\n",nr3dInfo->d3nr_2d_luma_en);
    printf("d3nr_2d_chroma_en:%d\n",nr3dInfo->d3nr_2d_chroma_en);
    printf("d3nr_wb_en:%d\n",nr3dInfo->d3nr_wb_en);
    printf("d3nr_wb_sel:%d\n",nr3dInfo->d3nr_wb_sel);
    printf("d3nr_adp_luma_en:%d\n",nr3dInfo->d3nr_adp_luma_en);
    printf("d3nr_adp_chroma_en:%d\n",nr3dInfo->d3nr_adp_chroma_en);
    printf("d3nr_pre_luma_th:%d\n",nr3dInfo->d3nr_pre_luma_th);
    printf("d3nr_pre_luma_intensity:%d\n",nr3dInfo->d3nr_pre_luma_intensity);
    printf("d3nr_pre_chroma_intensity:%d\n",nr3dInfo->d3nr_pre_chroma_intensity);
    printf("d3nr_mid_filter_th:%d\n",nr3dInfo->d3nr_mid_filter_th);
    printf("d3nr_pre_mid_filter_th:%d\n",nr3dInfo->d3nr_pre_mid_filter_th);
    printf("d3nr_cur_mid_filter_th:%d\n",nr3dInfo->d3nr_cur_mid_filter_th);
    printf("d3nr_low_pass_filter_th:%d\n",nr3dInfo->d3nr_low_pass_filter_th);
    printf("d3nr_luma_th:%d\n",nr3dInfo->d3nr_luma_th);
    printf("d3nr_min_value:%d\n",nr3dInfo->d3nr_min_value);
    printf("d3nr_luma_intensity:%d\n",nr3dInfo->d3nr_luma_intensity);
    printf("d3nr_chroma_intensity:%d\n",nr3dInfo->d3nr_chroma_intensity);
    printf("d3nr_post_edge_th:%d\n",nr3dInfo->d3nr_post_edge_th);
    printf("d3nr_post_luma_intensity:%d\n",nr3dInfo->d3nr_post_luma_intensity);
    printf("d3nr_post_chroma_intensity:%d\n",nr3dInfo->d3nr_post_chroma_intensity);
    //enh *
    struct enh_info_s    *enhInfo = &isp_core_cfg->enhInfo;
    printf("enh_ltm_en:\n",enhInfo->enh_ltm_en);
    printf("enh_sharp_en:\n",enhInfo->enh_sharp_en);
    printf("enh_cc_en:\n",enhInfo->enh_cc_en);
    printf("enh_adp_ltm_en:\n",enhInfo->enh_adp_ltm_en);
    printf("enh_adp_sharp_en:\n",enhInfo->enh_adp_sharp_en);
    printf("enh_adp_cc_en:\n",enhInfo->enh_adp_cc_en);
    printf("ltm_gain:\n",enhInfo->ltm_gain);
    printf("ltm_th:\n",enhInfo->ltm_th);
    printf("enh_nr_th:\n",enhInfo->enh_nr_th);
    printf("enh_th1:\n",enhInfo->enh_th1);
    printf("enh_th2:\n",enhInfo->enh_th2);
    printf("sharp_gain:\n",enhInfo->sharp_gain);
    //post ctrl *
    struct post_info_s   *postInfo = &isp_core_cfg->postInfo;
    printf("post_cont_ad_en:%d\n",postInfo->post_cont_ad_en);
    printf("post_luma_ad_en:%d\n",postInfo->post_luma_ad_en);
    printf("post_satu_ad_en:%d\n",postInfo->post_satu_ad_en);
    printf("cont_ad_intensity:%d\n",postInfo->cont_ad_intensity);
    printf("luma_ad_intensity:%d\n",postInfo->luma_ad_intensity);
    printf("satu_ad_intensity:%d\n",postInfo->satu_ad_intensity);
    //otc *
    struct otc_info_s    *otcInfo = &isp_core_cfg->otcInfo;
    printf("post_otc_en:%d\n",otcInfo->post_otc_en);
    printf("otc_yc_sel:%d\n",otcInfo->otc_yc_sel);
    printf("otc_uv_format_sel:%d\n",otcInfo->otc_uv_format_sel);
    printf("otc_hsync_pol_sel:%d\n",otcInfo->otc_hsync_pol_sel);
    printf("otc_vsync_pol_sel:%d\n",otcInfo->otc_vsync_pol_sel);
    printf("otc_out_size.width_st:%d\n",otcInfo->otc_out_size.width_st);
    printf("otc_out_size.height_st:%d\n",otcInfo->otc_out_size.height_st);
    printf("otc_out_size.width:%d\n",otcInfo->otc_out_size.width);
    printf("otc_out_size.height:%d\n",otcInfo->otc_out_size.height);
    //ldc *
    struct ldc_info_s    *ldcInfo = &isp_core_cfg->ldcInfo;
    printf("ldc_en:%d\n",ldcInfo->ldc_en);
    printf("ldc_arith_en:%d\n",ldcInfo->ldc_arith_en);
    printf("ldc_req_freq:%d\n",ldcInfo->ldc_req_freq);
    printf("ldc_stt_ln:%d\n",ldcInfo->ldc_stt_ln);
    printf("ldc_h_center_pos:%d\n",ldcInfo->ldc_h_center_pos);
    printf("ldc_v_center_pos:%d\n",ldcInfo->ldc_v_center_pos);
    printf("ldc_rectify_cr:%d\n",ldcInfo->ldc_rectify_cr);
    printf("ldc_rectify_cz:%d\n",ldcInfo->ldc_rectify_cz);
    //af *
    struct af_info_s     *afInfo = &isp_core_cfg->afInfo;
    printf("af_stat_en:%d\n",afInfo->af_stat_en);
    printf("af_stat_mode_sel:%d\n",afInfo->af_stat_mode_sel);
    printf("v_start:%d\n",afInfo->af_win_size.v_start);
    printf("h_start:%d\n",afInfo->af_win_size.h_start);
    printf("v_end:%d\n",afInfo->af_win_size.v_end);
    printf("h_end:%d\n",afInfo->af_win_size.h_end);
    //
    struct isp_ds_cfg_info      *isp_ds_cfg = &isp_cfg->isp_ds_cfg;
    printf("dsInSizeInfo.width:%d\n",isp_ds_cfg->dsInSizeInfo.width);
    printf("dsInSizeInfo.height:%d\n",isp_ds_cfg->dsInSizeInfo.height);
    //
    printf("osd_rgb2yuv_coeff[0][0]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][0]);
    printf("osd_rgb2yuv_coeff[0][1]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][1]);
    printf("osd_rgb2yuv_coeff[0][2]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][2]);
    printf("osd_rgb2yuv_coeff[0][3]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[0][3]);
    printf("osd_rgb2yuv_coeff[1][0]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][0]);
    printf("osd_rgb2yuv_coeff[1][1]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][1]);
    printf("osd_rgb2yuv_coeff[1][2]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][2]);
    printf("osd_rgb2yuv_coeff[1][3]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[1][3]);
    printf("osd_rgb2yuv_coeff[2][0]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][0]);
    printf("osd_rgb2yuv_coeff[2][1]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][1]);
    printf("osd_rgb2yuv_coeff[2][2]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][2]);
    printf("osd_rgb2yuv_coeff[2][3]:%d\n",isp_ds_cfg->osd_rgb2yuv_coeff[2][3]);
    //
    printf("osd_yuv2rgb_coeff[0][0]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][0]);
    printf("osd_yuv2rgb_coeff[0][1]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][1]);
    printf("osd_yuv2rgb_coeff[0][2]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][2]);
    printf("osd_yuv2rgb_coeff[0][3]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[0][3]);
    printf("osd_yuv2rgb_coeff[1][0]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][0]);
    printf("osd_yuv2rgb_coeff[1][1]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][1]);
    printf("osd_yuv2rgb_coeff[1][2]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][2]);
    printf("osd_yuv2rgb_coeff[1][3]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[1][3]);
    printf("osd_yuv2rgb_coeff[2][0]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][0]);
    printf("osd_yuv2rgb_coeff[2][1]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][1]);
    printf("osd_yuv2rgb_coeff[2][2]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][2]);
    printf("osd_yuv2rgb_coeff[2][3]:%d\n",isp_ds_cfg->osd_yuv2rgb_coeff[2][3]);
    //
    struct isp_ds_info_s    *dsInfo = &isp_ds_cfg->dsInfo[0]; //ISP_DS_CH_NUM
    printf("0 scale_en:%d\n",dsInfo->scale_en);
    printf("0 vscale_filter_en:%d\n",dsInfo->vscale_filter_en);
    printf("0 hscale_filter_en:%d\n",dsInfo->hscale_filter_en);
    printf("0 ds_out_size.width:%d\n",dsInfo->ds_out_size.width);
    printf("0 ds_out_size.height:%d\n",dsInfo->ds_out_size.height);
    printf("0 out_rgb_mode:%d\n",dsInfo->out_rgb_mode);
    printf("0 out_rgb_en:%d\n",dsInfo->out_rgb_en);
    printf("0 out_yuv_mode:%d\n",dsInfo->out_yuv_mode);
    printf("0 out_uv_swap:%d\n",dsInfo->out_uv_swap);
    //
    dsInfo = &isp_ds_cfg->dsInfo[1];
    printf("1 scale_en:%d\n",dsInfo->scale_en);
    printf("1 vscale_filter_en:%d\n",dsInfo->vscale_filter_en);
    printf("1 hscale_filter_en:%d\n",dsInfo->hscale_filter_en);
    printf("1 ds_out_size.width:%d\n",dsInfo->ds_out_size.width);
    printf("1 ds_out_size.height:%d\n",dsInfo->ds_out_size.height);
    printf("1 out_rgb_mode:%d\n",dsInfo->out_rgb_mode);
    printf("1 out_rgb_en:%d\n",dsInfo->out_rgb_en);
    printf("1 out_yuv_mode:%d\n",dsInfo->out_yuv_mode);
    printf("1 out_uv_swap:%d\n",dsInfo->out_uv_swap);
    //
    dsInfo = &isp_ds_cfg->dsInfo[2];
    printf("2 scale_en:%d\n",dsInfo->scale_en);
    printf("2 vscale_filter_en:%d\n",dsInfo->vscale_filter_en);
    printf("2 hscale_filter_en:%d\n",dsInfo->hscale_filter_en);
    printf("2 ds_out_size.width:%d\n",dsInfo->ds_out_size.width);
    printf("2 ds_out_size.height:%d\n",dsInfo->ds_out_size.height);
    printf("2 out_rgb_mode:%d\n",dsInfo->out_rgb_mode);
    printf("2 out_rgb_en:%d\n",dsInfo->out_rgb_en);
    printf("2 out_yuv_mode:%d\n",dsInfo->out_yuv_mode);
    printf("2 out_uv_swap:%d\n",dsInfo->out_uv_swap);
    printf("%s:end\n",__func__);
}

