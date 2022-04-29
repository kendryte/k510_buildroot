
#ifndef __JSON_PARSE_H__
#define __JSON_PARSE_H__

#include "isp.h"
#include "../media_ctl.h"

struct sensor_info{
	char sensor_name[50];
	char sensor_cfg_file[50];
	struct isp_cfg_info isp_cfg;
};

void dofile_video_cfg(char *filename,struct vi_cfg_info *vi_cfg,struct sensor_info *sensor0,struct sensor_info *sensor1,struct video_info *dev_info);
void dofile_csi2(char *filename,struct isp_csi2_info *mipi_csi2);
void dofile_vi(char *filename,struct vi_cfg_info *vi_cfg);
void dofile_isp(char *filename,struct sensor_info *sensor);
#endif /*__JSON_PARSE_H__*/