/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "json_parse.h"

/***************************************************************************
*video cfg
****************************************************************************/
/**
 * @brief 
 * 
 * @param text 
 * @param vi_cfg 
 * @param sensor0 
 * @param sensor1 
 */
void doit_video_cfg(char *text,struct vi_cfg_info *vi_cfg,struct sensor_info *sensor0,struct sensor_info *sensor1,struct video_info *dev_info)
{
	char *out;
   cJSON *root;
   cJSON *arrayItem;
   cJSON *item;
   cJSON *object;
   int i = 0;

	struct isp_wrap_cfg_info *f2k_isp_wrap = &sensor0->isp_cfg.isp_wrap_cfg;
	struct isp_core_cfg_info *f2k_isp_core = &sensor0->isp_cfg.isp_core_cfg;
	struct isp_ds_cfg_info	 *f2k_isp_ds = &sensor0->isp_cfg.isp_ds_cfg; 
	struct isp_wrap_cfg_info *r2k_isp_wrap = &sensor1->isp_cfg.isp_wrap_cfg;
	struct isp_core_cfg_info *r2k_isp_core = &sensor1->isp_cfg.isp_core_cfg;
	struct isp_ds_cfg_info	 *r2k_isp_ds = &sensor1->isp_cfg.isp_ds_cfg; 
	printf("%s:start\n",__func__);
	root=cJSON_Parse(text);
	if (!root) 
   {
       printf("Error before: [%s]\n",cJSON_GetErrorPtr());
   }
	else
	{
		out=cJSON_Print(root);
      //sensor0
      arrayItem = cJSON_GetObjectItem(root,"sensor0");
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	//printf("%s:sensor0 cJSON_GetArraySize: size=%d\n",__func__,size);

         i = 0;
         //sensor0_name
         object=cJSON_GetArrayItem(arrayItem,i++);
         if(object != NULL)
         {
           sprintf(&sensor0->sensor_name[0],"%s",object->valuestring);
           //printf("cJSON_GetArrayItem: type=%d, string is %s, valuestring is %s,%s,%d\n",object->type,object->string,object->valuestring,&sensor0->sensor_name[0],sizeof(object->valuestring));
         }
         //sensor0_cfg_file
         object=cJSON_GetArrayItem(arrayItem,i++);
         if(object != NULL)
         {
           sprintf(&sensor0->sensor_cfg_file[0],"%s",object->valuestring);
           //printf("cJSON_GetArrayItem: type=%d, string is %s, valuestring is %s,%s,%d\n",object->type,object->string,object->valuestring,&sensor0->sensor_cfg_file[0],sizeof(object->valuestring));
         }
    
         //sensor0_total_size
         struct itc_info_s *itcInfo = &f2k_isp_core->itcInfo;
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"sensor0_total_width");
         //printf("%s:total_width %p\n",__func__,item);
         if(item != NULL)
         {
            itcInfo->total_size.width = item->valueint;
            vi_cfg->vi_pipe_cfg[0].total_size.width = item->valueint;
            vi_cfg->vi_pipe_cfg[1].total_size.width = item->valueint;
            vi_cfg->vi_pipe_cfg[2].total_size.width = item->valueint;
            //printf("(sensor0_total_width): type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"sensor0_total_height");
         //printf("%s:total_height %p\n",__func__,item);
         if(item != NULL)
         {
            itcInfo->total_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[0].total_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[1].total_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[2].total_size.height = item->valueint;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }
         //sensor0_active_size
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"sensor0_active_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            itcInfo->itc_size.width = (item->valueint + 15) / 16 * 16;
            vi_cfg->vi_pipe_cfg[0].in_size.width = (item->valueint + 15) / 16 * 16;
            vi_cfg->vi_pipe_cfg[1].in_size.width = (item->valueint + 15) / 16 * 16;
            vi_cfg->vi_pipe_cfg[2].in_size.width = (item->valueint + 15) / 16 * 16;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"sensor0_active_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            itcInfo->itc_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[0].in_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[1].in_size.height = item->valueint;
            vi_cfg->vi_pipe_cfg[2].in_size.height = item->valueint;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
        // /dev/video2
		   dev_info[0].video_name[0] = "/dev/video2";
         struct isp_wrap_main_info *mainInfo = &f2k_isp_wrap->mainInfo;
         struct otc_info_s *otcInfo = &f2k_isp_core->otcInfo; 
         struct image_size_s *dsInSizeInfo = &f2k_isp_ds->dsInSizeInfo;
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video2_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].enable[0] = item->valueint;
            mainInfo->main_out_en = item->valueint;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video2_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_width[0] = item->valueint;
            mainInfo->main_size.width = (item->valueint + 15) / 16 * 16;
            otcInfo->otc_out_size.width = mainInfo->main_size.width;
            dsInSizeInfo->width = mainInfo->main_size.width;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video2_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_height[0] = item->valueint;
            mainInfo->main_size.height = item->valueint;
            otcInfo->otc_out_size.height = mainInfo->main_size.height;
            dsInSizeInfo->height = mainInfo->main_size.height;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video2_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_out_format[0] = item->valueint;
            mainInfo->main_out_img_out_format = item->valueint;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video3
         dev_info[0].video_name[1] = "/dev/video3";
         struct isp_wrap_ds0_info	*wds0Info = &f2k_isp_wrap->ds0Info;
         struct isp_ds_info_s *ds0Info = &f2k_isp_ds->dsInfo[0];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video3_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].enable[1] = item->valueint;
            wds0Info->ds0_out_en = item->valueint; //must enable
            ds0Info->scale_en = wds0Info->ds0_out_en;
            ds0Info->vscale_filter_en = wds0Info->ds0_out_en;
            ds0Info->hscale_filter_en = wds0Info->ds0_out_en;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video3_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_width[1] = item->valueint;
            wds0Info->ds0_size.width = (item->valueint + 15) / 16 * 16;
            ds0Info->ds_out_size.width = wds0Info->ds0_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video3_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_height[1] = item->valueint;
            wds0Info->ds0_size.height = item->valueint;
            ds0Info->ds_out_size.height = wds0Info->ds0_size.height;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"video3_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
           dev_info[0].video_out_format[1] = item->valueint;
           wds0Info->ds0_out_img_out_format = item->valueint;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video4
	      dev_info[0].video_name[2] = "/dev/video4";
         struct isp_wrap_ds1_info	*wds1Info = &f2k_isp_wrap->ds1Info;
         struct isp_ds_info_s *ds1Info = &f2k_isp_ds->dsInfo[1];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video4_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].enable[2] = item->valueint;
            wds1Info->ds1_out_en = item->valueint;
            ds1Info->scale_en = wds1Info->ds1_out_en;
            ds1Info->vscale_filter_en = wds1Info->ds1_out_en;
            ds1Info->hscale_filter_en = wds1Info->ds1_out_en;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video4_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_width[2] = item->valueint;
            wds1Info->ds1_size.width = (item->valueint + 15) / 16 * 16;
            ds1Info->ds_out_size.width = wds1Info->ds1_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video4_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            	dev_info[0].video_height[2] = item->valueint;
            wds1Info->ds1_size.height = item->valueint;
            ds1Info->ds_out_size.height = wds1Info->ds1_size.height;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"video4_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_out_format[2] = item->valueint;
            wds1Info->ds1_out_img_out_format = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video5
         dev_info[0].video_name[3] = "/dev/video5";
         struct isp_wrap_ds2_info	*wds2Info = &f2k_isp_wrap->ds2Info;
         struct isp_ds_info_s *ds2Info = &f2k_isp_ds->dsInfo[2];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video5_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
           dev_info[0].enable[3] = item->valueint;
           wds2Info->ds2_out_en = item->valueint;
           ds2Info->scale_en = wds2Info->ds2_out_en;
           ds2Info->vscale_filter_en = wds2Info->ds2_out_en;
           ds2Info->hscale_filter_en = wds2Info->ds2_out_en;
            //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video5_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_width[3] = item->valueint;
            wds2Info->ds2_size.width = (item->valueint + 15) / 16 * 16;
            ds2Info->ds_out_size.width = wds2Info->ds2_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video5_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_height[3] = item->valueint;
            wds2Info->ds2_video_height = item->valueint;
            //wds2Info->ds2_size.height = item->valueint;
            //ds2Info->ds_out_size.height = wds2Info->ds2_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video5_height_r");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            //dev_info[0].video_height[3] = item->valueint;
            wds2Info->ds2_size.height = item->valueint;
            ds2Info->ds_out_size.height = wds2Info->ds2_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video5_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_out_format[3] = item->valueint;
            wds2Info->ds2_out_img_out_format = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video5_pitch");
         printf("%s:video5_pitch %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[0].video_width[3] = item->valueint;
            wds2Info->ds2_size.pitch = item->valueint;
            ds2Info->ds_out_size.pitch = wds2Info->ds2_size.pitch;
             printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d pitch is %d \n",item->type,item->string,item->valueint,ds2Info->ds_out_size.pitch);
         } 


		   dev_info[0].video_used = 0;
		   if((dev_info[0].enable[0] == 1)||(dev_info[0].enable[1] == 1)||(dev_info[0].enable[2] == 1)||(dev_info[0].enable[3] == 1)) 
		   {
		   	dev_info[0].video_used = 1;
		   } 
      }
      //sensor1
      arrayItem = cJSON_GetObjectItem(root,"sensor1");
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	printf("%s:sensor1 cJSON_GetArraySize: size=%d\n",__func__,size);
         i = 0;
         //sensor1_name
         object=cJSON_GetArrayItem(arrayItem,i++);
         if(object != NULL)
         {
            sprintf(&sensor1->sensor_name[0],"%s",object->valuestring);
            printf("cJSON_GetArrayItem: type=%d, string is %s, valuestring is %s,%s,%d\n",object->type,object->string,object->valuestring,&sensor1->sensor_name[0],sizeof(object->valuestring));
         }  
 
         object=cJSON_GetArrayItem(arrayItem,i++);
         if(object != NULL)
         {
            sprintf(&sensor1->sensor_cfg_file[0],"%s",object->valuestring);
            printf("cJSON_GetArrayItem: type=%d, string is %s, valuestring is %s,%s,%d\n",object->type,object->string,object->valuestring,&sensor1->sensor_cfg_file[0],sizeof(object->valuestring));
         } 

         //sensor1_total_size
         struct itc_info_s *itcInfo = &r2k_isp_core->itcInfo;
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"sensor1_total_width");
         //printf("%s:total_width %p\n",__func__,item);
         if(item != NULL)
         {
             itcInfo->total_size.width = item->valueint;
             vi_cfg->vi_pipe_cfg[3].total_size.width = item->valueint;
             printf("cJSON_GetObjectItem(sensor1_total_width): type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"sensor1_total_height");
         //printf("%s:total_height %p\n",__func__,item);
         if(item != NULL)
         {
             itcInfo->total_size.height = item->valueint;
             vi_cfg->vi_pipe_cfg[3].total_size.height = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }
         //sensor1_active_size
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"sensor1_active_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
             itcInfo->itc_size.width = (item->valueint + 15) / 16 * 16;
             vi_cfg->vi_pipe_cfg[3].in_size.width = (item->valueint + 15) / 16 * 16;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"sensor1_active_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
             itcInfo->itc_size.height = item->valueint;
             vi_cfg->vi_pipe_cfg[3].in_size.height = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video6
		   dev_info[1].video_name[0] = "/dev/video6";
         struct isp_wrap_main_info *mainInfo = &r2k_isp_wrap->mainInfo;
         struct otc_info_s *otcInfo = &r2k_isp_core->otcInfo; 
         struct image_size_s *dsInSizeInfo = &r2k_isp_ds->dsInSizeInfo;
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video6_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].enable[0] = item->valueint;
             mainInfo->main_out_en = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video6_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_width[0] = item->valueint;
            mainInfo->main_size.width = (item->valueint + 15) / 16 * 16;
            otcInfo->otc_out_size.width = mainInfo->main_size.width;
            dsInSizeInfo->width = mainInfo->main_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video6_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_height[0] = item->valueint;
            mainInfo->main_size.height = item->valueint;
            otcInfo->otc_out_size.height = mainInfo->main_size.height;
            dsInSizeInfo->height = mainInfo->main_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video6_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_out_format[0] = item->valueint;
            mainInfo->main_out_img_out_format = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video7
		   dev_info[1].video_name[1] = "/dev/video7";
         struct isp_wrap_ds0_info	*wds0Info = &r2k_isp_wrap->ds0Info;
         struct isp_ds_info_s *ds0Info = &r2k_isp_ds->dsInfo[0];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video7_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
             dev_info[1].enable[1] = item->valueint;
             wds0Info->ds0_out_en = item->valueint;
             ds0Info->scale_en = wds0Info->ds0_out_en;
             ds0Info->vscale_filter_en = wds0Info->ds0_out_en;
             ds0Info->hscale_filter_en = wds0Info->ds0_out_en;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video7_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_width[1] = item->valueint;
            wds0Info->ds0_size.width = (item->valueint + 15) / 16 * 16;
            ds0Info->ds_out_size.width = wds0Info->ds0_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video7_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
             dev_info[1].video_height[1] = item->valueint;
             wds0Info->ds0_size.height = item->valueint;
             ds0Info->ds_out_size.height = wds0Info->ds0_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video7_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_out_format[1] = item->valueint;
            wds0Info->ds0_out_img_out_format = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video8
		   dev_info[1].video_name[2] = "/dev/video8";
         struct isp_wrap_ds1_info	*wds1Info = &r2k_isp_wrap->ds1Info;
         struct isp_ds_info_s *ds1Info = &r2k_isp_ds->dsInfo[1];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video8_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].enable[2] = item->valueint;
            wds1Info->ds1_out_en = item->valueint;
            ds1Info->scale_en = wds1Info->ds1_out_en;
            ds1Info->vscale_filter_en = wds1Info->ds1_out_en;
            ds1Info->hscale_filter_en = wds1Info->ds1_out_en;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video8_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_width[2] = item->valueint;
            wds1Info->ds1_size.width = (item->valueint + 15) / 16 * 16;
            ds1Info->ds_out_size.width = wds1Info->ds1_size.width;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video8_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_height[2] = item->valueint;
            wds1Info->ds1_size.height = item->valueint;
            ds1Info->ds_out_size.height = wds1Info->ds1_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"video8_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            dev_info[1].video_out_format[2] = item->valueint;
            wds1Info->ds1_out_img_out_format = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 
         // /dev/video9
		   dev_info[1].video_name[3] = "/dev/video9";
         struct isp_wrap_ds2_info	*wds2Info = &r2k_isp_wrap->ds2Info;
         struct isp_ds_info_s *ds2Info = &r2k_isp_ds->dsInfo[2];
         object=cJSON_GetArrayItem(arrayItem,i++);
         item=cJSON_GetObjectItem(object,"video9_used");
         //printf("%s:active_width %p\n",__func__,item);
         if(item != NULL)
         {
            wds2Info->ds2_out_en = item->valueint;
            ds2Info->scale_en = wds2Info->ds2_out_en;
            ds2Info->vscale_filter_en = wds2Info->ds2_out_en;
            ds2Info->hscale_filter_en = wds2Info->ds2_out_en;
	         dev_info[1].enable[3] = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video9_width");
         // item->valueint = (item->valueint + 15) / 16 * 16;
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            wds2Info->ds2_size.width = (item->valueint + 15) / 16 * 16;
            ds2Info->ds_out_size.width = wds2Info->ds2_size.width;
	         dev_info[1].video_width[3] = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         } 

         item=cJSON_GetObjectItem(object,"video9_height");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            wds2Info->ds2_video_height = item->valueint;
	         dev_info[1].video_height[3] = item->valueint;
            //wds2Info->ds2_size.height = item->valueint;
            //ds2Info->ds_out_size.height = wds2Info->ds2_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"video9_height_r");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            //dev_info[1].video_height[3] = item->valueint;
            wds2Info->ds2_size.height = item->valueint;
            ds2Info->ds_out_size.height = wds2Info->ds2_size.height;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }

         item=cJSON_GetObjectItem(object,"video9_out_format");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            wds2Info->ds2_out_img_out_format = item->valueint;
	         dev_info[1].video_out_format[3] = item->valueint;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }  

         item=cJSON_GetObjectItem(object,"video9_pitch");
         //printf("%s:active_height %p\n",__func__,item);
         if(item != NULL)
         {
            //dev_info[1].video_height[3] = item->valueint;
            wds2Info->ds2_size.pitch = item->valueint;
            ds2Info->ds_out_size.pitch = wds2Info->ds2_size.pitch;
             //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
         }


		   dev_info[1].video_used = 0;
		   if((dev_info[1].enable[0] == 1)||(dev_info[1].enable[1] == 1)||(dev_info[1].enable[2] == 1)||(dev_info[1].enable[3] == 1)) 
		   {
		   	dev_info[1].video_used = 1;
		   }
      } 
   }
}
/***************************************************************************
*csi2
****************************************************************************/
/* Parse text to JSON, then render back to text, and print! */
void doit_csi2(char *text,struct isp_csi2_info *mipi_csi2)
{
   cJSON *root;
   cJSON *arrayItem;
   cJSON *item;
   cJSON *object;

	printf("%s:start\n",__func__);
	root=cJSON_Parse(text);
	if (!root) 
   {
       printf("Error before: [%s]\n",cJSON_GetErrorPtr());
   }
	else
	{
      //mipi_csi2
      arrayItem = cJSON_GetObjectItem(root,"mipi_csi2");
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	//printf("%s:mipi_csi2 cJSON_GetArraySize: size=%d\n",__func__,size);
        //csi0_used
        int i = 0;
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_used = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 

        //csi0_sony_wdr
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_sony_wdr = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi0_lane_nb
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_lane_nb = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi0_dl0_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_dl0_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi0_dl1_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_dl1_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi0_dl2_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_dl2_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi0_dl3_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi0_dl3_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi00_datatype_select0
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi00_datatype_select0 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi00_datatype_select1
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi00_datatype_select1 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi00_vc_select
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi00_vc_select = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi01_datatype_select0
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi01_datatype_select0 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi01_datatype_select1
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi01_datatype_select1 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi01_vc_select
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi01_vc_select = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi02_datatype_select0
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi02_datatype_select0 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi02_datatype_select1
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi02_datatype_select1 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi02_vc_select
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi02_vc_select = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_used = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi1_sony_wdr
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_sony_wdr = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi1_lane_nb
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_lane_nb = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi1_dl0_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_dl0_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi1_dl1_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_dl1_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi1_dl2_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_dl2_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi1_dl3_map
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi1_dl3_map = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi10_datatype_select0
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi10_datatype_select0 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //csi10_datatype_select1
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi10_datatype_select1 = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }
        //csi10_vc_select
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           mipi_csi2->csi10_vc_select = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 

      }
  
   }
}
/***************************************************************************
*vi
****************************************************************************/
/**
 * @brief 
 * 
 * @param object 
 * @param s 
 */
void parse_vi_wrap(cJSON *object,struct vi_wrap_cfg_info *vi_wrap_cfg)
{
   cJSON *item;

   item=cJSON_GetObjectItem(object,"dphy_mode");
   //printf("%s:dphy_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->dphy_mode = item->valueint;
       //printf("cJSON_GetObjectItem: dphy_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sony_mode");
   //printf("%s:sony_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sony_mode = item->valueint;
       //printf("cJSON_GetObjectItem: sony_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //sensor0
   item=cJSON_GetObjectItem(object,"sensor0_interface_en");
   //printf("%s:sensor0_interface_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].sensor_interface_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_interface_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_tpg_w_en");
   //printf("%s:sensor0_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_tpg_w_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_tpg_r_en");
   //printf("%s:sensor0_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_tpg_r_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_wdr_sensor_vendor");
   //printf("%s:sensor0_wdr_sensor_vendor %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].wdr_sensor_vendor = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_wdr_sensor_vendor type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_wdr_mode");
   //printf("%s:sensor0_wdr_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].wdr_mode = item->valueint;
      //printf("cJSON_GetObjectItem: sensor0_wdr_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_mipi_mode");
   //printf("%s:sensor0_mipi_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].mipi_mode = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_mipi_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor0_isp_pipeline");
   //printf("%s:sensor0_isp_pipeline %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[0].isp_pipeline = item->valueint;
       //printf("cJSON_GetObjectItem: sensor0_isp_pipeline type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //sensor1
   item=cJSON_GetObjectItem(object,"sensor1_interface_en");
   //printf("%s:sensor1_interface_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].sensor_interface_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_interface_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_tpg_w_en");
   //printf("%s:sensor1_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_tpg_w_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_tpg_r_en");
   //printf("%s:sensor1_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_tpg_r_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_wdr_sensor_vendor");
   //printf("%s:sensor1_wdr_sensor_vendor %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].wdr_sensor_vendor = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_wdr_sensor_vendor type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_wdr_mode");
   //printf("%s:sensor1_wdr_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].wdr_mode = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_wdr_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_mipi_mode");
   //printf("%s:sensor1_mipi_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].mipi_mode = item->valueint;
       //printf("cJSON_GetObjectItem:sensor1_mipi_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor1_isp_pipeline");
   //printf("%s:sensor1_isp_pipeline %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[1].isp_pipeline = item->valueint;
       //printf("cJSON_GetObjectItem: sensor1_isp_pipeline type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   } 
   //sensor2
   item=cJSON_GetObjectItem(object,"sensor2_interface_en");
   //printf("%s:sensor2_interface_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].sensor_interface_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_interface_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_tpg_w_en");
   //printf("%s:sensor2_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_tpg_w_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_tpg_r_en");
   //printf("%s:sensor2_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_tpg_r_en type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_wdr_sensor_vendor");
   //printf("%s:sensor2_wdr_sensor_vendor %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].wdr_sensor_vendor = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_wdr_sensor_vendor type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_wdr_mode");
   //printf("%s:sensor2_wdr_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].wdr_mode = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_wdr_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_mipi_mode");
   //printf("%s:sensor2_mipi_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].mipi_mode = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_mipi_mode type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"sensor2_isp_pipeline");
   //printf("%s:sensor2_isp_pipeline %p\n",__func__,item);
   if(item != NULL)
   {
       vi_wrap_cfg->sensor_info[2].isp_pipeline = item->valueint;
       //printf("cJSON_GetObjectItem: sensor2_isp_pipeline type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }  
} 
//
void parse_vi_pipe00(cJSON *object,struct vi_pipe_cfg_info *vi_pipe_cfg)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"p00_win_mode_en");
   //printf("%s:p00_win_mode_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->win_mode_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_input_ch_sel");
   //printf("%s:p00_input_ch_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->input_ch_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_ch_mode_sel");
   //printf("%s:p00_ch_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->ch_mode_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_pixel_type");
   //printf("%s:p00_pixel_type %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_type = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_yuv_in_format");
   //printf("%s:p00_yuv_in_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_in_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_yuv_out_format");
   //printf("%s:p00_yuv_out_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_out_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_yuv422_order");
   //printf("%s:p00_yuv422_order %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv422_order = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_pixel_width");
   //printf("%s:p00_pixel_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_data_out_timming_ctrl");
   //printf("%s:p00_data_out_timming_ctrl %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->data_out_timming_ctrl = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_sync_pulse_mode");
   //printf("%s:p00_sync_pulse_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sync_pulse_mode = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_sen_mipi_clk_pol");
   //printf("%s:p00_sen_mipi_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_sen_mipi_vsync_pol");
   //printf("%s:p00_sen_mipi_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_sen_mipi_hsync_pol");
   //printf("%s:p00_sen_mipi_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_sen_mipi_field_pol");
   //printf("%s:p00_sen_mipi_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_isp_clk_pol");
   //printf("%s:p00_isp_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_isp_vsync_pol");
   //printf("%s:p00_isp_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_isp_hsync_pol");
   //printf("%s:p00_isp_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_isp_field_pol");
   //printf("%s:p00_isp_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_tpg_w_en");
   //printf("%s:p00_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_tpg_r_en");
   //printf("%s:p00_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_w_st_width");
   //printf("%s:p00_w_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_w_st_height");
   //printf("%s:p00_w_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_r_st_width");
   //printf("%s:p00_r_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_r_st_height");
   //printf("%s:p00_r_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_tof_mode_enable");
   //printf("%s:p00_tof_mode_enable %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tof_mode_enable = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_vi_pipe_tpg_tof_frm_num");
   //printf("%s:p00_vi_pipe_tpg_tof_frm_num %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_num = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p00_vi_pipe_tpg_tof_frm_stride");
   //printf("%s:p00_vi_pipe_tpg_tof_frm_stride %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void parse_vi_pipe01(cJSON *object,struct vi_pipe_cfg_info *vi_pipe_cfg)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"p01_win_mode_en");
   //printf("%s:p01_win_mode_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->win_mode_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_input_ch_sel");
   //printf("%s:p01_input_ch_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->input_ch_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_ch_mode_sel");
   //printf("%s:p01_ch_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->ch_mode_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_pixel_type");
   //printf("%s:p01_pixel_type %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_type = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_yuv_in_format");
   //printf("%s:p01_yuv_in_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_in_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_yuv_out_format");
   //printf("%s:p01_yuv_out_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_out_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_yuv422_order");
   //printf("%s:p01_yuv422_order %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv422_order = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_pixel_width");
   //printf("%s:p01_pixel_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_data_out_timming_ctrl");
   //printf("%s:p01_data_out_timming_ctrl %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->data_out_timming_ctrl = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_sync_pulse_mode");
   //printf("%s:p01_sync_pulse_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sync_pulse_mode = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_sen_mipi_clk_pol");
   //printf("%s:p01_sen_mipi_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_sen_mipi_vsync_pol");
   //printf("%s:p01_sen_mipi_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_sen_mipi_hsync_pol");
   //printf("%s:p01_sen_mipi_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_sen_mipi_field_pol");
   //printf("%s:p01_sen_mipi_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_isp_clk_pol");
   //printf("%s:p01_isp_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_isp_vsync_pol");
   //printf("%s:p01_isp_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_isp_hsync_pol");
   //printf("%s:p01_isp_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_isp_field_pol");
   //printf("%s:p01_isp_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_tpg_w_en");
   //printf("%s:p01_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_tpg_r_en");
   //printf("%s:p01_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_w_st_width");
   //printf("%s:p01_w_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_w_st_height");
   //printf("%s:p01_w_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_r_st_width");
   //printf("%s:p01_r_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_r_st_height");
   //printf("%s:p01_r_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_tof_mode_enable");
   //printf("%s:p01_tof_mode_enable %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tof_mode_enable = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_vi_pipe_tpg_tof_frm_num");
   //printf("%s:p01_vi_pipe_tpg_tof_frm_num %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_num = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p01_vi_pipe_tpg_tof_frm_stride");
   //printf("%s:p01_vi_pipe_tpg_tof_frm_stride %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void parse_vi_pipe02(cJSON *object,struct vi_pipe_cfg_info *vi_pipe_cfg)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"p02_win_mode_en");
   //printf("%s:p02_win_mode_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->win_mode_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_input_ch_sel");
   //printf("%s:p02_input_ch_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->input_ch_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_ch_mode_sel");
   //printf("%s:p02_ch_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->ch_mode_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_pixel_type");
   //printf("%s:p02_pixel_type %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_type = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_yuv_in_format");
   //printf("%s:p02_yuv_in_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_in_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_yuv_out_format");
   //printf("%s:p02_yuv_out_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_out_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_yuv422_order");
   //printf("%s:p02_yuv422_order %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv422_order = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_pixel_width");
   //printf("%s:p02_pixel_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_data_out_timming_ctrl");
   //printf("%s:p02_data_out_timming_ctrl %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->data_out_timming_ctrl = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_sync_pulse_mode");
   //printf("%s:p02_sync_pulse_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sync_pulse_mode = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_sen_mipi_clk_pol");
   //printf("%s:p02_sen_mipi_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_sen_mipi_vsync_pol");
   //printf("%s:p02_sen_mipi_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_sen_mipi_hsync_pol");
   //printf("%s:p02_sen_mipi_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_sen_mipi_field_pol");
   //printf("%s:p02_sen_mipi_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_isp_clk_pol");
   //printf("%s:p02_isp_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_isp_vsync_pol");
   //printf("%s:p02_isp_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_isp_hsync_pol");
   //printf("%s:p02_isp_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_isp_field_pol");
   //printf("%s:p02_isp_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_tpg_w_en");
   //printf("%s:p02_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_tpg_r_en");
   //printf("%s:p02_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_w_st_width");
   //printf("%s:p02_w_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_w_st_height");
   //printf("%s:p02_w_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_r_st_width");
   //printf("%s:p02_r_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_r_st_height");
   //printf("%s:p02_r_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_tof_mode_enable");
   //printf("%s:p02_tof_mode_enable %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tof_mode_enable = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_vi_pipe_tpg_tof_frm_num");
   //printf("%s:p02_vi_pipe_tpg_tof_frm_num %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_num = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p02_vi_pipe_tpg_tof_frm_stride");
   //printf("%s:p02_vi_pipe_tpg_tof_frm_stride %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void parse_vi_pipe10(cJSON *object,struct vi_pipe_cfg_info *vi_pipe_cfg)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"p10_win_mode_en");
   //printf("%s:p10_win_mode_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->win_mode_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_input_ch_sel");
   //printf("%s:p10_input_ch_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->input_ch_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_ch_mode_sel");
   //printf("%s:p10_ch_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->ch_mode_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_pixel_type");
   //printf("%s:p10_pixel_type %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_type = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_yuv_in_format");
   //printf("%s:p10_yuv_in_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_in_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_yuv_out_format");
   //printf("%s:p10_yuv_out_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_out_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_yuv422_order");
   //printf("%s:p10_yuv422_order %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv422_order = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_pixel_width");
   //printf("%s:p10_pixel_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_data_out_timming_ctrl");
   //printf("%s:p10_data_out_timming_ctrl %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->data_out_timming_ctrl = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_sync_pulse_mode");
   //printf("%s:p10_sync_pulse_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sync_pulse_mode = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_sen_mipi_clk_pol");
   //printf("%s:p10_sen_mipi_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_sen_mipi_vsync_pol");
   //printf("%s:p10_sen_mipi_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_sen_mipi_hsync_pol");
   //printf("%s:p10_sen_mipi_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_sen_mipi_field_pol");
   //printf("%s:p10_sen_mipi_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_isp_clk_pol");
   //printf("%s:p10_isp_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_isp_vsync_pol");
   //printf("%s:p10_isp_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_isp_hsync_pol");
   //printf("%s:p10_isp_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_isp_field_pol");
   //printf("%s:p10_isp_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_tpg_w_en");
   //printf("%s:p10_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_tpg_r_en");
   //printf("%s:p10_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_w_st_width");
   //printf("%s:p10_w_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_w_st_height");
   //printf("%s:p10_w_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_r_st_width");
   //printf("%s:p10_r_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_r_st_height");
   //printf("%s:p10_r_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_tof_mode_enable");
   //printf("%s:p10_tof_mode_enable %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tof_mode_enable = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_vi_pipe_tpg_tof_frm_num");
   //printf("%s:p10_vi_pipe_tpg_tof_frm_num %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_num = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"p10_vi_pipe_tpg_tof_frm_stride");
   //printf("%s:p10_vi_pipe_tpg_tof_frm_stride %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void parse_vi_dvp00(cJSON *object,struct vi_pipe_cfg_info *vi_pipe_cfg)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"dvp00_win_mode_en");
   //printf("%s:dvp00_win_mode_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->win_mode_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_input_ch_sel");
   //printf("%s:dvp00_input_ch_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->input_ch_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_ch_mode_sel");
   //printf("%s:dvp00_ch_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->ch_mode_sel = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_pixel_type");
   //printf("%s:dvp00_pixel_type %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_type = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_yuv_in_format");
   //printf("%s:dvp00_yuv_in_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_in_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_yuv_out_format");
   //printf("%s:dvp00_yuv_out_format %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv_out_format = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_yuv422_order");
   //printf("%s:dvp00_yuv422_order %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->yuv422_order = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_pixel_width");
   //printf("%s:dvp00_pixel_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->pixel_width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_data_out_timming_ctrl");
   //printf("%s:dvp00_data_out_timming_ctrl %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->data_out_timming_ctrl = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_sync_pulse_mode");
   //printf("%s:dvp00_sync_pulse_mode %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sync_pulse_mode = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_sen_mipi_clk_pol");
   //printf("%s:dvp00_sen_mipi_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_sen_mipi_vsync_pol");
   //printf("%s:dvp00_sen_mipi_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_sen_mipi_hsync_pol");
   //printf("%s:dvp00_sen_mipi_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_sen_mipi_field_pol");
   //printf("%s:dvp00_sen_mipi_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->sen_mipi_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_isp_clk_pol");
   //printf("%s:dvp00_isp_clk_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_clk_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_isp_vsync_pol");
   //printf("%s:dvp00_isp_vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_vsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_isp_hsync_pol");
   //printf("%s:dvp00_isp_hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_hsync_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_isp_field_pol");
   //printf("%s:dvp00_isp_field_pol %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->isp_field_pol = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_tpg_w_en");
   //printf("%s:dvp00_tpg_w_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_w_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_tpg_r_en");
   //printf("%s:dvp00_tpg_r_en %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tpg_r_en = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_w_st_width");
   //printf("%s:dvp00_w_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_w_st_height");
   //printf("%s:dvp00_w_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->w_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_r_st_width");
   //printf("%s:dvp00_r_st_width %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.width = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_r_st_height");
   //printf("%s:dvp00_r_st_height %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->r_size_st.height = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_tof_mode_enable");
   //printf("%s:dvp00_tof_mode_enable %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->tof_mode_enable = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_vi_pipe_tpg_tof_frm_num");
   //printf("%s:dvp00_vi_pipe_tpg_tof_frm_num %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_num = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dvp00_vi_pipe_tpg_tof_frm_stride");
   //printf("%s:dvp00_vi_pipe_tpg_tof_frm_stride %p\n",__func__,item);
   if(item != NULL)
   {
       vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride = item->valueint;
       //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void doit_vi(char *text,struct vi_cfg_info *vi_cfg)
{
   cJSON *root;
   cJSON *arrayItem;
   cJSON *item;
   cJSON *object;

	printf("%s:start\n",__func__);
	root=cJSON_Parse(text);
	if (!root) 
   {
       printf("Error before: [%s]\n",cJSON_GetErrorPtr());
   }
	else
	{
      //isp_vi
      arrayItem = cJSON_GetObjectItem(root,"isp_vi");
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	//printf("%s:isp_general cJSON_GetArraySize: size=%d\n",__func__,size);
         //vi_wrap
         int i = 0;
         struct vi_wrap_cfg_info *vi_wrap_cfg = &vi_cfg->vi_wrap_cfg;
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_wrap(object,vi_wrap_cfg);
         //pipi00
         struct vi_pipe_cfg_info  *vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[0];
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_pipe00(object,vi_pipe_cfg);
         //pipi01
         vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[1];
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_pipe01(object,vi_pipe_cfg);
         //pipi02
         vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[2];
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_pipe02(object,vi_pipe_cfg);
         //pipi10
         vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[3];
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_pipe10(object,vi_pipe_cfg);
         //dvp00
         vi_pipe_cfg = &vi_cfg->vi_pipe_cfg[6];
         object=cJSON_GetArrayItem(arrayItem,i++);
         parse_vi_dvp00(object,vi_pipe_cfg);
      }         
   }
} 
/***************************************************************************
*isp
****************************************************************************/
/**
 * @brief 
 * 
 * @param object 
 * @param itcInfo 
 */
//itc
void parse_itc(cJSON *object,struct itc_info_s *itcInfo)
{   
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"hsync_pol");
   //printf("%s:hsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->hsync_pol = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"vsync_pol");
   //printf("%s:vsync_pol %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->vsync_pol = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"hsync_input_timing");
   //printf("%s:hsync_input_timing %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->hsync_input_timing = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   item=cJSON_GetObjectItem(object,"vsync_input_timing");
   //printf("%s:vsync_input_timing %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->vsync_input_timing = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"flip_ctl");
   //printf("%s:flip_ctl %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->flip_ctl = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"video_fmt_sl");
   //printf("%s:video_fmt_sl %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->video_fmt_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"itc_ttl_h");
   //printf("%s:itc_ttl_h %p\n",__func__,item);
   if(item != NULL)
   {
      //itcInfo->total_size.width = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"itc_ttl_v");
   //printf("%s:itc_ttl_v %p\n",__func__,item);
   if(item != NULL)
   {
      //itcInfo->total_size.height = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"itc_stt_hr");
   //printf("%s:itc_stt_hr %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->itc_size.width_st = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"itc_stt_vr");
   //printf("%s:itc_stt_vr %p\n",__func__,item);
   if(item != NULL)
   {
      itcInfo->itc_size.height_st = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//tpg
void parse_tpg(cJSON *object,struct tpg_info_s *tpgInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"bayer_mode_sel");
   //printf("%s:bayer_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->bayer_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"motion_mode_sel");
   //printf("%s:motion_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->motion_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"tpg_sel");
   //printf("%s:tpg_sel %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->tpg_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"tpg_en");
   //printf("%s:tpg_en %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->tpg_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_l_mul_data");
   //printf("%s:wdr_l_mul_data %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->wdr_l_mul_data = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_m_mul_data");
   //printf("%s:wdr_m_mul_data %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->wdr_m_mul_data = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_s_mul_data");
   //printf("%s:wdr_s_mul_data %p\n",__func__,item);
   if(item != NULL)
   {
      tpgInfo->wdr_s_mul_data = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }   
}
//blc
void parse_blc(cJSON *object,struct blc_info_s *blcInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"blc_en");
   //printf("%s:blc_en %p\n",__func__,item);
   if(item != NULL)
   {
      blcInfo->blc_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"blc_offset");
   //printf("%s:blc_offset %p\n",__func__,item);
   if(item != NULL)
   {
      blcInfo->blc_offset = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"blc_ratio");
   //printf("%s:blc_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      blcInfo->blc_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//lsc
void parse_lsc(cJSON *object,struct lsc_info_s *lscInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"lsc_en");
   //printf("%s:lsc_en %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_h_center");
   //printf("%s:lsc_h_center %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_h_center = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_v_center");
   //printf("%s:lsc_v_center %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_v_center = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_r_ratio");
   //printf("%s:lsc_r_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_r_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_g_ratio");
   //printf("%s:lsc_g_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_g_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_b_ratio");
   //printf("%s:lsc_b_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_b_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"lsc_ir_ratio");
   //printf("%s:lsc_ir_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      lscInfo->lsc_ir_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//ae
void parse_ae(cJSON *object,struct ae_info_s *aeInfo)
{
   cJSON *item;     
   //
   item=cJSON_GetObjectItem(object,"ae_as_en");
   //printf("%s:ae_as_en %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_as_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ag_en");
   //printf("%s:ae_ag_en %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ag_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_airis_en");
   //printf("%s:ae_airis_en %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_airis_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_enter_ls_sel");
   //printf("%s:ae_enter_ls_sel %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_enter_ls_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_exit_ls_sel");
   //printf("%s:ae_exit_ls_sel %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_exit_ls_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_win_mode_sel");
   //printf("%s:ae_win_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_win_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_back_light_mode_sel");
   //printf("%s:ae_back_light_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_back_light_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_day_change_en");
   //printf("%s:ae_day_change_en %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_day_change_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_day_change_sel");
   //printf("%s:ae_day_change_sel %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_day_change_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_win_stth");
   //printf("%s:ae_win_stth %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_win_size.h_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_win_sttv");
   //printf("%s:ae_win_sttv %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_win_size.v_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_win_endh");
   //printf("%s:ae_win_endh %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_win_size.h_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_win_endv");
   //printf("%s:ae_win_endv %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_win_size.v_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_yobj");
   //printf("%s:ae_yobj %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_tar_bright = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_av_rg");
   //printf("%s:ae_av_rg %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_tar_bright_range = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_l_ex_time");
   //printf("%s:ae_l_ex_time %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_l_ex_time = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_m_ex_time");
   //printf("%s:ae_m_ex_time %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_m_ex_time = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_s_ex_time");
   //printf("%s:ae_s_ex_time %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_s_ex_time = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_agc");
   //printf("%s:ae_agc %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_agc = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ad_shuttle_freq");
   //printf("%s:ae_ad_shuttle_freq %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ad_shuttle_freq = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ad_gain_freq");
   //printf("%s:ae_ad_gain_freq %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ad_gain_freq = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_adjust_step_max");
   //printf("%s:ae_adjust_step_max %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_adjust_step_max = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ex_value_max");
   //printf("%s:ae_ex_value_max %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ex_value_max = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ex_value_mid");
   //printf("%s:ae_ex_value_mid %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ex_value_mid = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_ex_value_min");
   //printf("%s:ae_ex_value_min %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_ex_value_min = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   // 
   item=cJSON_GetObjectItem(object,"ae_gain_value_max");
   //printf("%s:ae_gain_value_max %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_gain_value_max = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_gain_value_mid");
   //printf("%s:ae_gain_value_mid %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_gain_value_mid = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_gain_value_min");
   //printf("%s:ae_gain_value_min %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_gain_value_min = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_dn_switch_ad_step_max");
   //printf("%s:ae_dn_switch_ad_step_max %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_dn_switch_ad_step_max = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ae_dn_switch_wait_time");
   //printf("%s:ae_dn_switch_wait_time %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ae_dn_switch_wait_time = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_max_diff");
   //printf("%s:ape_max_diff %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_max_diff = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //   
   item=cJSON_GetObjectItem(object,"ape_drv_signal_max");
   //printf("%s:ape_drv_signal_max %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_drv_signal_max = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_coeff_distance");
   //printf("%s:ape_coeff_distance %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_coeff_distance = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_coeff_speed");
   //printf("%s:ape_coeff_speed %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_coeff_speed = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_coeff_acceleration");
   //printf("%s:ape_coeff_acceleration %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_coeff_acceleration = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_drv_manual_value");
   //printf("%s:ape_drv_manual_value %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_drv_manual_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ape_damp_manual_value");
   //printf("%s:ape_damp_manual_value %p\n",__func__,item);
   if(item != NULL)
   {
      aeInfo->ape_damp_manual_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//awb
void parse_awb(cJSON *object,struct awb_info_s *awbInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"awb_d65_en");
   //printf("%s:awb_d65_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_d65_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_ccm_en" 	);
   //printf("%s:awb_ccm_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_ccm_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_en" 	);
   //printf("%s:awb_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_mode_sel" 	);
   //printf("%s:awb_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_hist_mode_sel" 	);
   //printf("%s:awb_hist_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_hist_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_veri_en" 	);
   //printf("%s:awb_veri_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_veri_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_fb_en" 	);
   //printf("%s:awb_fb_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_fb_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_value_save_en" 	);
   //printf("%s:awb_value_save_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_value_save_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_ccm_adp_adjust_en" 	);
   //printf("%s:awb_ccm_adp_adjust_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_ccm_adp_adjust_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_stab_en" 	);
   //printf("%s:awb_stab_en %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_stab_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_d65_red_gain" 	);
   //printf("%s:awb_d65_red_gain %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_d65_red_gain = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_d65_blue_gain" 	);
   //printf("%s:awb_d65_blue_gain %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_d65_blue_gain = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_rr" 		);
   //printf("%s:ccm_rr %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[0][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_rg" 		);
   //printf("%s:ccm_rg %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[0][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_rb" 		);
   //printf("%s:ccm_rb %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[0][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_gr" 		);
   //printf("%s:ccm_gr %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[1][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_gg" 		);
   //printf("%s:ccm_gg %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[1][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_gb" 		);
   //printf("%s:ccm_gb %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[1][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_br" 		);
   //printf("%s:ccm_br %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[2][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_bg" 		);
   //printf("%s:ccm_bg %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[2][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_bb" 		);
   //printf("%s:ccm_bb %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_coff[2][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ccm_correct_coff" 		);
   //printf("%s:ccm_correct_coff %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->ccm_correct_coff = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_win_stth" 	);
   //printf("%s:awb_win_stth %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_win_size.h_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_win_sttv" 	);
   //printf("%s:awb_win_sttv %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_win_size.v_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_win_endh" 	);
   //printf("%s:awb_win_endh %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_win_size.h_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_win_endv" 	);
   //printf("%s:awb_win_endv %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_win_size.v_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_correct_diff_th" 	);
   //printf("%s:awb_correct_diff_th %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_correct_diff_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_color_changeres_time");
   //printf("%s:awb_color_changeres_time %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_color_changeres_time = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_historgram_th" 	);
   //printf("%s:awb_historgram_th %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_historgram_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_red_gain_adjust" 		);
   //printf("%s:awb_red_gain_adjust %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_red_gain_adjust = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_green_gain_adjust" 		);
   //printf("%s:awb_green_gain_adjust %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_green_gain_adjust = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_blue_gain_adjust" 		);
   //printf("%s:awb_blue_gain_adjust %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_blue_gain_adjust = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_red_max_value" 		);
   //printf("%s:awb_red_max_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_red_max_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_blue_max_value" 		);
   //printf("%s:awb_blue_max_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_blue_max_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_red_min_value" 		);
   //printf("%s:awb_red_min_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_red_min_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_blue_min_value" 		);
   //printf("%s:awb_blue_min_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_blue_min_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_red_obj_value" 	);
   //printf("%s:awb_red_obj_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_red_obj_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"awb_blue_obj_value" 	);
   //printf("%s:awb_blue_obj_value %p\n",__func__,item);
   if(item != NULL)
   {
      awbInfo->awb_blue_obj_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }

}
//wdr
void parse_wdr(cJSON *object,struct wdr_Info_s *wdrInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"wdr_fusion_en" 		);
   //printf("%s:wdr_fusion_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_fusion_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_frame_sel" 		);
   //printf("%s:wdr_frame_sel %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_frame_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_adp_adjust_en" 		);
   //printf("%s:wdr_adp_adjust_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_adp_adjust_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_stab_en" 		);	
   //printf("%s:wdr_stab_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_stab_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_en" 		);
   //printf("%s:wdr_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_ghost_remove_en"); 
   //printf("%s:wdr_ghost_remove_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_ghost_remove_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //	
   item=cJSON_GetObjectItem(object,"wdr_3frame_out_mode" 			);
   //printf("%s:wdr_3frame_out_mode %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_3frame_out_mode = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_mode_sel" 		);
   //printf("%s:wdr_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_2frame_ex_ratio" 		);
   //printf("%s:wdr_2frame_ex_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_2frame_ex_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_3frame_ex_ratio" 		);
   //printf("%s:wdr_3frame_ex_ratio %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_3frame_ex_ratio = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_stat_img_sel" 	);	
   //printf("%s:wdr_stat_img_sel %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_stat_img_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_ltm_data_sel" 	);
   //printf("%s:wdr_ltm_data_sel %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_ltm_data_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //	
   item=cJSON_GetObjectItem(object,"wdr_tz_data_sel" 		);
   //printf("%s:wdr_tz_data_sel %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_tz_data_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_remove_purple_en" 		);
   //printf("%s:wdr_remove_purple_en %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_remove_purple_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_over_ex_ratio_th1" 		);
   //printf("%s:wdr_over_ex_ratio_th1 %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_over_ex_ratio_th1 = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_over_ex_ratio_th2" 		);
   //printf("%s:wdr_over_ex_ratio_th2 %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_over_ex_ratio_th2 = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_fusion_ratio_th" 		);
   //printf("%s:wdr_fusion_ratio_th %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_fusion_ratio_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_fusion_value1" 		);
   //printf("%s:wdr_fusion_value1 %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_fusion_value1 = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"wdr_fusion_value2" 		);
   //printf("%s:wdr_fusion_value2 %p\n",__func__,item);
   if(item != NULL)
   {
      wdrInfo->wdr_fusion_value2 = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//csc
void parse_csc(cJSON *object,struct csc_info_s *cscInfo)
{
   cJSON *item;
   item=cJSON_GetObjectItem(object,"rgb2yuv_00");
   //printf("%s:rgb2yuv_00 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[0][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_01");
   //printf("%s:rgb2yuv_01 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[0][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_02");
   //printf("%s:rgb2yuv_02 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[0][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_10");
   //printf("%s:rgb2yuv_10 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[1][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_11");
   //printf("%s:rgb2yuv_11 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[1][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_12");
   //printf("%s:rgb2yuv_12 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[1][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_20");
   //printf("%s:rgb2yuv_20 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[2][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_21");
   //printf("%s:rgb2yuv_21 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[2][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgb2yuv_22");
   //printf("%s:rgb2yuv_22 %p\n",__func__,item);
   if(item != NULL)
   {
      cscInfo->csc_r2y[2][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//ada
void parse_ada(cJSON *object,struct ada_info_s *adaInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"gm_rgb_en" 		);
   //printf("%s:gm_rgb_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_rgb_gamma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"gm_yuv_en" 		);
   //printf("%s:gm_yuv_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_yuv_gamma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_en" 			);
   //printf("%s:ada_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_adjust_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_sbz_en" 		);
   //printf("%s:ada_sbz_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_img_stab_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_ccr_en" 		);
   //printf("%s:ada_ccr_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_ccr_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_adp_en" 		);
   //printf("%s:ada_adp_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_adp_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_adp_ccr_en" 	);
   //printf("%s:ada_adp_ccr_en %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_adp_ccr_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_stat_mode_sel"); 
   //printf("%s:ada_stat_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_stat_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_enh_mode_sel" );
   //printf("%s:ada_enh_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_enh_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //	
   item=cJSON_GetObjectItem(object,"ada_hist_max" 		);
   //printf("%s:ada_hist_max %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_stat_max_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_ttl_max" 		);
   //printf("%s:ada_ttl_max %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_ad_stren_max_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_win_stth" 		);
   //printf("%s:ada_win_stth %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_win_size.h_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_win_sttv" 		);
   //printf("%s:ada_win_sttv %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_win_size.v_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_win_endh" 		);
   //printf("%s:ada_win_endh %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_win_size.h_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ada_win_endv" 		);
   //printf("%s:ada_win_endv %p\n",__func__,item);
   if(item != NULL)
   {
      adaInfo->ada_win_size.v_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//rgbir
void parse_rgbir(cJSON *object,struct rgbir_info_s *rgbirInfo)
{
   cJSON *item;

   item=cJSON_GetObjectItem(object,"raw_fmt" 		);
   //printf("%s:raw_fmt %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgbir_rct_en");
   //printf("%s:rgbir_rct_en %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rtf_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   // 	
   item=cJSON_GetObjectItem(object,"dfc_en" 		);
   //printf("%s:dfc_en %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgbir_fs_en" );	
   //printf("%s:rgbir_fs_en %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_fusion_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"rgbir_ot_sl" );
   //printf("%s:rgbir_ot_sl %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_output_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //	
   item=cJSON_GetObjectItem(object,"rgbir_fs_max");
   //printf("%s:rgbir_fs_max %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_max_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   // 	
   item=cJSON_GetObjectItem(object,"dfc_krb" 		);
   //printf("%s:dfc_krb %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_color_coff = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dfc_ky" 		);
   //printf("%s:dfc_ky %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_luma_coff = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dfc_th" 		);
   //printf("%s:dfc_th %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dfc_th_1" 	);	
   //printf("%s:dfc_th_1 %p\n",__func__,item);
   if(item != NULL)
   {
      rgbirInfo->rgbir_rpc_th1 = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//2dnr
void parse_2dnr(cJSON *object,struct nr2d_info_s *nr2dInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"dpeak_en" 		);
   //printf("%s:dpeak_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_pcf_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_raw_en" 	);
   //printf("%s:nr2d_raw_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_raw_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_eg_en" 	);
   //printf("%s:nr2d_eg_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_edge_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_jl_en" 	);
   //printf("%s:nr2d_jl_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_bap_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_av_en" 	);
   //printf("%s:nr2d_av_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_c_en"  	);
   //printf("%s:nr2d_c_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"dpeak_adp_en" 	);
   //printf("%s:dpeak_adp_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_pcf_adp_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_raw_adp_en");
   //printf("%s:nr2d_raw_adp_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_raw_adp_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_y_adp_en" );
   //printf("%s:nr2d_y_adp_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_luma_adp_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_c_adp_en" );
   //printf("%s:nr2d_c_adp_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_chroma_adp_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_raw_kl" 	);
   //printf("%s:nr2d_raw_kl %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_raw_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_jl_th" 	);
   //printf("%s:nr2d_jl_th %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_bap_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_eg_k" 	);
   //printf("%s:nr2d_eg_k %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_edge_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_y_k" 		);
   //printf("%s:nr2d_y_k %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_luma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr2d_c_k" 		);
   //printf("%s:nr2d_c_k %p\n",__func__,item);
   if(item != NULL)
   {
      nr2dInfo->d2nr_chroma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//3ndr
void parse_3dnr(cJSON *object,struct nr3d_info_s *nr3dInfo)
{
   cJSON *item;

   item=cJSON_GetObjectItem(object,"nr3d_en" 					);
   //printf("%s:nr3d_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dp_y_en" 				);
   //printf("%s:nr3dp_y_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dp_c_en" 				);
   //printf("%s:nr3dp_c_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_y_en" 				);
   //printf("%s:nr3dm_y_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_main_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_c_en" 				);
   //printf("%s:nr3dm_c_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_main_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3db_y_en" 				);
   //printf("%s:nr3db_y_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_post_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3db_c_en" 				);
   //printf("%s:nr3db_c_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_post_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_nr2d_y_en" 			);
   //printf("%s:nr3dm_nr2d_y_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_2d_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_nr2d_c_en" 			);
   //printf("%s:nr3dm_nr2d_c_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_2d_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"core_3dnr_wb_en" 			);
   //printf("%s:core_3dnr_wb_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_wb_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"core_3dnr_wb_sel" 			);
   //printf("%s:core_3dnr_wb_sel %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_wb_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"core_3dnr_adp_luma_en" 	);
   //printf("%s:core_3dnr_adp_luma_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_adp_luma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"core_3dnr_adp_chroma_en" 	);
   //printf("%s:core_3dnr_adp_chroma_en %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_adp_chroma_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dp_thy" 				);
   //printf("%s:nr3dp_thy %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_luma_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dp_thyp" 				);
   //printf("%s:nr3dp_thyp %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_luma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dp_thcp" 				);
   //printf("%s:nr3dp_thcp %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_chroma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_mid_th" 				);
   //printf("%s:nr3dm_mid_th %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_mid_filter_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_mtp_th" 				);
   //printf("%s:nr3dm_mtp_th %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_pre_mid_filter_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_mtc_th" 				);
   //printf("%s:nr3dm_mtc_th %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_cur_mid_filter_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_ym_k" 				);
   //printf("%s:nr3dm_ym_k %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_low_pass_filter_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_thy" 				);
   //printf("%s:nr3dm_thy %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_luma_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_min" 				);
   //printf("%s:nr3dm_min %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_min_value = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3dm_thw0" 				);
   //printf("%s:nr3dm_thw0 %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_luma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"core_3dnr_chroma_intensity");
   //printf("%s:core_3dnr_chroma_intensity %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_chroma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3db_nr2d_eg_th" 			);
   //printf("%s:nr3db_nr2d_eg_th %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_post_edge_th = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3db_thyp" 				);
   //printf("%s:nr3db_thyp %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_post_luma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"nr3db_thcp" 				);
   //printf("%s:nr3db_thcp %p\n",__func__,item);
   if(item != NULL)
   {
      nr3dInfo->d3nr_post_chroma_intensity = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//enh
void parse_enh(cJSON *object,struct enh_info_s *enhInfo)
{
   cJSON *item;
   cJSON *object1;
   cJSON *arrayItem1 = object;
   //
   if(arrayItem1 != NULL)
   {
  		int size=cJSON_GetArraySize(arrayItem1);
		//printf("%s:enh cJSON_GetArraySize: size=%d\n",__func__,size);
      //ltm
      object1=cJSON_GetArrayItem(arrayItem1,0);
      item=cJSON_GetObjectItem(object1,"enh_ltm_en");
      //printf("%s:enh_ltm_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_ltm_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"enh_adp_ltm_en"); 
      //printf("%s:enh_adp_ltm_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_adp_ltm_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"ltm_gain" 		);
      //printf("%s:ltm_gain %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->ltm_gain = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"ltm_mm_th" 		);
      //printf("%s:ltm_mm_th %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->ltm_th = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //sharp
      object1=cJSON_GetArrayItem(arrayItem1,1);
      item=cJSON_GetObjectItem(object1,"enh_sharp_en" 		);
      //printf("%s:enh_sharp_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_sharp_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"enh_adp_sharp_en"); 
      //printf("%s:enh_adp_sharp_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_adp_sharp_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"shp_core" 			);
      //printf("%s:shp_core %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_nr_th = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"shp_th1" 			);
      //printf("%s:shp_th1 %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_th1 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"shp_th2" 			);
      //printf("%s:shp_th2 %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_th2 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"shp_gain" 			);
      //printf("%s:shp_gain %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->sharp_gain = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //cc
      object1=cJSON_GetArrayItem(arrayItem1,2);
      item=cJSON_GetObjectItem(object1,"enh_cc_en" 		);
      //printf("%s:enh_cc_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_cc_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"enh_adp_cc_en"); 
      //printf("%s:enh_adp_cc_en %p\n",__func__,item);
      if(item != NULL)
      {
         enhInfo->enh_adp_cc_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      } 
   }
   else
   {
      //printf("%s:get enh failed!\n",__func__);
   }
}
//post ctl
void parse_postctl(cJSON *object,struct post_info_s *postInfo,struct otc_info_s *otcInfo)
{
   cJSON *item;
   cJSON *object1;
   cJSON *arrayItem1 = object;
   //

	  struct crop_info_s 		  ; 
   //
   if(arrayItem1 != NULL)
   {
  		int size=cJSON_GetArraySize(arrayItem1);
		//printf("%s:enh cJSON_GetArraySize: size=%d\n",__func__,size);
      //otc_ctl
      object1=cJSON_GetArrayItem(arrayItem1,0);
	   item=cJSON_GetObjectItem(object1,"otc_en" 		);
      //printf("%s:otc_en %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->post_otc_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      // 
      item=cJSON_GetObjectItem(object1,"otc_yc_sl" 	); 
      //printf("%s:otc_yc_sl %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_yc_sel = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"otc_uv_sl" 	); 
      //printf("%s:otc_uv_sl %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_uv_format_sel = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"otc_hs_plt_sl");
      //printf("%s:otc_hs_plt_sl %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_hsync_pol_sel = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //  
      item=cJSON_GetObjectItem(object1,"otc_vs_plt_sl"); 
      //printf("%s:otc_vs_plt_sl %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_vsync_pol_sel = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      // 
      item=cJSON_GetObjectItem(object1,"otc_stt_vr" 	); 
      //printf("%s:otc_stt_vr %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_out_size.height_st = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"otc_stt_hr" 	); 
      //printf("%s:otc_stt_hr %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_out_size.width_st = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      #if 0
      //
      item=cJSON_GetObjectItem(object1,"width_ot" 		); 
      //printf("%s:width_ot %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_out_size.width = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"height_ot" 	); 
      //printf("%s:height_ot %p\n",__func__,item);
      if(item != NULL)
      {
         otcInfo->otc_out_size.height = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      #endif
      //ctrst
      object1=cJSON_GetArrayItem(arrayItem1,1);
      item=cJSON_GetObjectItem(object1,"ctrst_en");
      //printf("%s:ctrst_en %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->post_cont_ad_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"ctrst_gain");
      //printf("%s:ctrst_gain %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->cont_ad_intensity = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //luma
      object1=cJSON_GetArrayItem(arrayItem1,2);
      item=cJSON_GetObjectItem(object1,"luma_en"  );
      //printf("%s:luma_en %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->post_luma_ad_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"luma_gain");
      //printf("%s:luma_gain %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->luma_ad_intensity = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //strt
      object1=cJSON_GetArrayItem(arrayItem1,3);
      item=cJSON_GetObjectItem(object1,"strt_en");
      //printf("%s:strt_en %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->post_satu_ad_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
      item=cJSON_GetObjectItem(object1,"strt_gain");
      //printf("%s:strt_gain %p\n",__func__,item);
      if(item != NULL)
      {
         postInfo->satu_ad_intensity = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
   }
   else
   {
      //printf("%s:get post_ctl failed!\n",__func__);
   }
}
//ldc
void parse_ldc(cJSON *object,struct ldc_info_s *ldcInfo)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"ldc_en" 	);
   //printf("%s:ldc_en %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_rct_en");
   //printf("%s:ldc_rct_en %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_arith_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_rq_frq");
   //printf("%s:ldc_rq_frq %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_req_freq = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_stt_ln");
   //printf("%s:ldc_rq_frq %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_stt_ln = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_ch" 	);
   //printf("%s:ldc_ch %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_h_center_pos = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_cv" 	);
   //printf("%s:ldc_cv %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_v_center_pos = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_cr");
   //printf("%s:ldc_cr %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_rectify_cr = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"ldc_cz" 	);
   //printf("%s:ldc_cz %p\n",__func__,item);
   if(item != NULL)
   {
      ldcInfo->ldc_rectify_cz = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//af
void parse_af(cJSON *object,struct af_info_s *afInfo)
{
   cJSON *item;
   //  
   item=cJSON_GetObjectItem(object,"af_stat_en"         );
   //printf("%s:af_stat_en %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_stat_en = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"af_stat_mode_sel"   );
   //printf("%s:af_stat_mode_sel %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_stat_mode_sel = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"af_stat_win_h_start");
   //printf("%s:af_stat_win_h_start %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_win_size.h_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"af_stat_win_v_start");
   //printf("%s:af_stat_win_v_start %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_win_size.v_start = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"af_stat_win_h_end"  );
   //printf("%s:af_stat_win_h_end %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_win_size.h_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"af_stat_win_v_end"  );
   //printf("%s:af_stat_win_v_end %p\n",__func__,item);
   if(item != NULL)
   {
      afInfo->af_win_size.v_end = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   } 
}
//rgb2yuv
void parse_rgb2yuv(cJSON *object,struct isp_ds_cfg_info *ds_info)
{
   cJSON *item;
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff00");
   //printf("%s:osd_rgb2yuv_coeff00 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[0][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff01");
   //printf("%s:osd_rgb2yuv_coeff01 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[0][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff02");
   //printf("%s:osd_rgb2yuv_coeff02 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[0][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff03");
   //printf("%s:osd_rgb2yuv_coeff03 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[0][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff10");
   //printf("%s:osd_rgb2yuv_coeff10 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[1][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff11");
   //printf("%s:osd_rgb2yuv_coeff11 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[1][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff12");
   //printf("%s:osd_rgb2yuv_coeff12 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[1][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff13");
   //printf("%s:osd_rgb2yuv_coeff13 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[1][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff20");
   //printf("%s:osd_rgb2yuv_coeff20 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[2][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff21");
   //printf("%s:osd_rgb2yuv_coeff21 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[2][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff22");
   //printf("%s:osd_rgb2yuv_coeff22 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[2][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"osd_rgb2yuv_coeff23");
   //printf("%s:osd_rgb2yuv_coeff23 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_rgb2yuv_coeff[2][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//yuv2rgb
void parse_yuv2rgb(cJSON *object,struct isp_ds_cfg_info *ds_info)
{
   cJSON *item;

   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff00");
   //printf("%s:out_yuv2rgb_coeff00 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[0][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff01");
   //printf("%s:out_yuv2rgb_coeff01 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[0][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff02");
   //printf("%s:out_yuv2rgb_coeff02 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[0][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff03");
   //printf("%s:out_yuv2rgb_coeff03 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[0][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff10");
   //printf("%s:out_yuv2rgb_coeff10 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[1][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff11");
   //printf("%s:out_yuv2rgb_coeff11 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[1][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff12");
   //printf("%s:out_yuv2rgb_coeff12 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[1][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff13");
   //printf("%s:out_yuv2rgb_coeff13 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[1][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff20");
   //printf("%s:out_yuv2rgb_coeff20 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[2][0] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff21");
   //printf("%s:out_yuv2rgb_coeff21 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[2][1] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff22");
   //printf("%s:out_yuv2rgb_coeff22 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[2][2] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
   //
   item=cJSON_GetObjectItem(object,"out_yuv2rgb_coeff23");
   //printf("%s:out_yuv2rgb_coeff23 %p\n",__func__,item);
   if(item != NULL)
   {
      ds_info->osd_yuv2rgb_coeff[2][3] = item->valueint;
      //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
   }
}
//
void parse_ds0(cJSON *object,struct isp_ds_info_s *dsInfo)
{
   cJSON *item;
   cJSON *object1;
   cJSON *arrayItem1 = object;
   //
   if(arrayItem1 != NULL)
   {
  		int size=cJSON_GetArraySize(arrayItem1);
		//printf("%s:cJSON_GetArraySize: size=%d\n",__func__,size);
      //ds0_out_rgb_mode
      object1=cJSON_GetArrayItem(arrayItem1,0);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds0_out_rgb_en
      object1=cJSON_GetArrayItem(arrayItem1,1);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_en = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds0_out_yuv_mode
      object1=cJSON_GetArrayItem(arrayItem1,2);
      if(object1 != NULL)
      {
         dsInfo->out_yuv_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds0_out_uv_swap
      object1=cJSON_GetArrayItem(arrayItem1,3);
      if(object1 != NULL)
      {
         dsInfo->out_uv_swap = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds0_osd0
      //ds0_osd0_enable
      struct isp_osd_info_s *osdInfo = &dsInfo->osdInfo[0];
      object1=cJSON_GetArrayItem(arrayItem1,4);
	   item=cJSON_GetObjectItem(object1,"ds0_osd0_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_type");
      //printf("%s:ds0_osd0_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_alpha_tpye");
      //printf("%s:ds0_osd0_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_vst");
      //printf("%s:ds0_osd0_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_hst");
      //printf("%s:ds0_osd0_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_vend");
      //printf("%s:ds0_osd0_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_hend");
      //printf("%s:ds0_osd0_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_dma_request_length");
      //printf("%s:ds0_osd0_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_dma_map");
      //printf("%s:ds0_osd0_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_rgb_rev");
      //printf("%s:ds0_osd0_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_global_alpha");
      //printf("%s:ds0_osd0_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_swap_64");
      //printf("%s:ds0_osd0_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_outstanding_num");
      //printf("%s:ds0_osd0_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd0_bd_limit_en"      );
      //printf("%s:ds0_osd0_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //ds0_osd1
      osdInfo = &dsInfo->osdInfo[1];
      object1=cJSON_GetArrayItem(arrayItem1,5);
	   item=cJSON_GetObjectItem(object1,"ds0_osd1_enable");
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_type");
      //printf("%s:ds0_osd1_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_alpha_tpye");
      //printf("%s:ds0_osd1_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_vst");
      //printf("%s:ds0_osd1_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_hst");
      //printf("%s:ds0_osd1_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_vend");
      //printf("%s:ds0_osd1_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_hend");
      //printf("%s:ds0_osd1_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_dma_request_length");
      //printf("%s:ds0_osd1_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_dma_map");
      //printf("%s:ds0_osd1_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_rgb_rev");
      //printf("%s:ds0_osd1_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_global_alpha");
      //printf("%s:ds0_osd1_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_swap_64");
      //printf("%s:ds0_osd1_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_outstanding_num");
      //printf("%s:ds0_osd1_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd1_bd_limit_en"      );
      //printf("%s:ds0_osd1_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //ds0_osd2
      osdInfo = &dsInfo->osdInfo[2];
      object1=cJSON_GetArrayItem(arrayItem1,6);
	   item=cJSON_GetObjectItem(object1,"ds0_osd2_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_type");
      //printf("%s:ds0_osd2_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_alpha_tpye");
      //printf("%s:ds0_osd2_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_vst");
      //printf("%s:ds0_osd2_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_hst");
      //printf("%s:ds0_osd2_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_vend");
      //printf("%s:ds0_osd2_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_hend");
      //printf("%s:ds0_osd2_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_dma_request_length");
      //printf("%s:ds0_osd2_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_dma_map");
      //printf("%s:ds0_osd2_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_rgb_rev");
      //printf("%s:ds0_osd2_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_global_alpha");
      //printf("%s:ds0_osd2_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_swap_64");
      //printf("%s:ds0_osd2_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_outstanding_num");
      //printf("%s:ds0_osd2_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds0_osd2_bd_limit_en"      );
      //printf("%s:ds0_osd2_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
   }
   else
   {
      //printf("%s:get ds1 failed!\n",__func__);
   }
}
//
void parse_ds1(cJSON *object,struct isp_ds_info_s *dsInfo)
{
   cJSON *item;
   cJSON *object1;
   cJSON *arrayItem1 = object;
   //
   if(arrayItem1 != NULL)
   {
  		int size=cJSON_GetArraySize(arrayItem1);
		//printf("%s:enh cJSON_GetArraySize: size=%d\n",__func__,size);
      //ds1_out_rgb_mode
      object1=cJSON_GetArrayItem(arrayItem1,0);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds1_out_rgb_en
      object1=cJSON_GetArrayItem(arrayItem1,1);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_en = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds1_out_yuv_mode
      object1=cJSON_GetArrayItem(arrayItem1,2);
      if(object1 != NULL)
      {
         dsInfo->out_yuv_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds1_out_uv_swap
      object1=cJSON_GetArrayItem(arrayItem1,3);
      if(object1 != NULL)
      {
         dsInfo->out_uv_swap = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds1_osd0
      //ds1_osd0_enable
      struct isp_osd_info_s *osdInfo = &dsInfo->osdInfo[0];
      object1=cJSON_GetArrayItem(arrayItem1,4);
	   item=cJSON_GetObjectItem(object1,"ds1_osd0_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_type");
      //printf("%s:ds1_osd0_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_alpha_tpye");
      //printf("%s:ds1_osd0_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_vst");
      //printf("%s:ds1_osd0_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_hst");
      //printf("%s:ds1_osd0_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_vend");
      //printf("%s:ds1_osd0_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_hend");
      //printf("%s:ds1_osd0_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_dma_request_length");
      //printf("%s:ds1_osd0_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_dma_map");
      //printf("%s:ds1_osd0_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_rgb_rev");
      //printf("%s:ds1_osd0_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_global_alpha");
      //printf("%s:ds1_osd0_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_swap_64");
      //printf("%s:ds1_osd0_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_outstanding_num");
      //printf("%s:ds1_osd0_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd0_bd_limit_en"      );
      //printf("%s:ds1_osd0_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //ds1_osd1
      osdInfo = &dsInfo->osdInfo[1];
      object1=cJSON_GetArrayItem(arrayItem1,5);
	   item=cJSON_GetObjectItem(object1,"ds1_osd1_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_type");
      //printf("%s:ds1_osd1_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_alpha_tpye");
      //printf("%s:ds1_osd1_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_vst");
      //printf("%s:ds1_osd1_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_hst");
      //printf("%s:ds1_osd1_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_vend");
      //printf("%s:ds1_osd1_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_hend");
      //printf("%s:ds1_osd1_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_dma_request_length");
      //printf("%s:ds1_osd1_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_dma_map");
      //printf("%s:ds1_osd1_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_rgb_rev");
      //printf("%s:ds1_osd1_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_global_alpha");
      //printf("%s:ds1_osd1_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_swap_64");
      //printf("%s:ds1_osd1_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_outstanding_num");
      //printf("%s:ds1_osd1_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd1_bd_limit_en"      );
      //printf("%s:ds1_osd1_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //ds1_osd2
      osdInfo = &dsInfo->osdInfo[2];
      object1=cJSON_GetArrayItem(arrayItem1,6);
	   item=cJSON_GetObjectItem(object1,"ds1_osd2_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_type");
      //printf("%s:ds1_osd2_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_alpha_tpye");
      //printf("%s:ds1_osd2_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_vst");
      //printf("%s:ds1_osd2_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_hst");
      //printf("%s:ds1_osd2_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_vend");
      //printf("%s:ds1_osd2_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_hend");
      //printf("%s:ds1_osd2_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_dma_request_length");
      //printf("%s:ds1_osd2_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_dma_map");
      //printf("%s:ds1_osd2_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_rgb_rev");
      //printf("%s:ds1_osd2_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_global_alpha");
      //printf("%s:ds1_osd2_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_swap_64");
      //printf("%s:ds1_osd2_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_outstanding_num");
      //printf("%s:ds1_osd2_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds1_osd2_bd_limit_en"      );
      //printf("%s:ds1_osd2_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
   }
   else
   {
      //printf("%s:get ds1 failed!\n",__func__);
   }
}
//ds2
void parse_ds2(cJSON *object,struct isp_ds_info_s *dsInfo)
{
   cJSON *item;
   cJSON *object1;
   cJSON *arrayItem1 = object;
   //
   if(arrayItem1 != NULL)
   {
  		int size=cJSON_GetArraySize(arrayItem1);
		//printf("%s:enh cJSON_GetArraySize: size=%d\n",__func__,size);
      //ds2_out_rgb_mode
      object1=cJSON_GetArrayItem(arrayItem1,0);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds2_out_rgb_en
      object1=cJSON_GetArrayItem(arrayItem1,1);
      if(object1 != NULL)
      {
         dsInfo->out_rgb_en = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds2_out_yuv_mode
      object1=cJSON_GetArrayItem(arrayItem1,2);
      if(object1 != NULL)
      {
         dsInfo->out_yuv_mode = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds2_out_uv_swap
      object1=cJSON_GetArrayItem(arrayItem1,3);
      if(object1 != NULL)
      {
         dsInfo->out_uv_swap = object1->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object1->type,object1->string,object1->valueint);
      }
      //ds2_osd0
      //ds2_osd0_enable
      struct isp_osd_info_s *osdInfo = &dsInfo->osdInfo[0];
      object1=cJSON_GetArrayItem(arrayItem1,4);
	   item=cJSON_GetObjectItem(object1,"ds2_osd0_enable");
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_type");
      //printf("%s:ds2_osd0_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_alpha_tpye");
      //printf("%s:ds2_osd0_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_vst");
      //printf("%s:ds2_osd0_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_hst");
      //printf("%s:ds2_osd0_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_vend");
      //printf("%s:ds2_osd0_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_hend");
      //printf("%s:ds2_osd0_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_dma_request_length");
      //printf("%s:ds2_osd0_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_dma_map");
      //printf("%s:ds2_osd0_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_rgb_rev");
      //printf("%s:ds2_osd0_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_global_alpha");
      //printf("%s:ds2_osd0_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_swap_64");
      //printf("%s:ds2_osd0_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_outstanding_num");
      //printf("%s:ds2_osd0_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd0_bd_limit_en"      );
      //printf("%s:ds2_osd0_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //ds2_osd1
      osdInfo = &dsInfo->osdInfo[1];
      object1=cJSON_GetArrayItem(arrayItem1,5);
	   item=cJSON_GetObjectItem(object1,"ds2_osd1_enable" 		);
      if(item != NULL)
      {
         osdInfo->osd_enable = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_type");
      //printf("%s:ds2_osd1_type %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_type = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_alpha_tpye");
      //printf("%s:ds2_osd1_alpha_tpye %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_alpha_tpye = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_vst");
      //printf("%s:ds2_osd1_vst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_hst");
      //printf("%s:ds2_osd1_hst %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_start = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_vend");
      //printf("%s:ds2_osd1_vend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.v_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_hend");
      //printf("%s:ds2_osd1_hend %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_position_win.h_end = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_dma_request_length");
      //printf("%s:ds2_osd1_dma_request_length %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_request_length = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_dma_map");
      //printf("%s:ds2_osd1_dma_map %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_dma_map = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_rgb_rev");
      //printf("%s:ds2_osd1_rgb_rev %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_rgb_rev = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_global_alpha");
      //printf("%s:ds2_osd1_global_alpha %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_global_alpha = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_swap_64");
      //printf("%s:ds2_osd1_swap_64 %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_swap_64 = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_outstanding_num");
      //printf("%s:ds2_osd1_outstanding_num %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_outstanding_num = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
      //
		item=cJSON_GetObjectItem(object1,"ds2_osd1_bd_limit_en"      );
      //printf("%s:ds2_osd1_bd_limit_en %p\n",__func__,item);
      if(item != NULL)
      {
         osdInfo->osd_bd_limit_en = item->valueint;
         //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
      }
   }
   else
   {
      //printf("%s:get ds1 failed!\n",__func__);
   }
}
//
//void doit_isp(char *text,struct isp_cfg_info *isp_cfg,char *sensor_name)
void doit_isp(char *text,struct isp_cfg_info *isp_cfg)
{
	char *out;
   cJSON *root;
   cJSON *arrayItem;
   cJSON *item;
   cJSON *object;
   int i = 0;

	struct isp_wrap_cfg_info *isp_wrap_cfg = &isp_cfg->isp_wrap_cfg;
	struct isp_core_cfg_info *isp_core_cfg = &isp_cfg->isp_core_cfg;
	struct isp_ds_cfg_info	 *isp_ds_cfg = &isp_cfg->isp_ds_cfg;   
	printf("%s:start\n",__func__);
	root=cJSON_Parse(text);
	if (!root) 
   {
       printf("Error before: [%s]\n",cJSON_GetErrorPtr());
   }
	else
	{
		out=cJSON_Print(root);
      //isp_general
      arrayItem = cJSON_GetObjectItem(root,"isp_general");
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	//printf("%s:isp_general cJSON_GetArraySize: size=%d\n",__func__,size);
        //sensor_name
        i = 0;
        //isp_out_sel
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           isp_wrap_cfg->isp_out_sel = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        }  
        //dvp_ch_mode
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           isp_wrap_cfg->dvp_ch_mode = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        //hist_3a_out_en
        object=cJSON_GetArrayItem(arrayItem,i++);
        if(object != NULL)
        {
           isp_wrap_cfg->hist_3a_out_en = object->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",object->type,object->string,object->valueint);
        } 
        struct isp_wrap_main_info *mainInfo = &isp_wrap_cfg->mainInfo;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"out_img_format");
        //printf("%s:out_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           mainInfo->main_out_img_format = item->valueint;
           printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);           
        }

        item=cJSON_GetObjectItem(object,"out_yuv_in_format");
        //printf("%s:out_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           mainInfo->main_out_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        //item=cJSON_GetObjectItem(object,"out_img_out_format");
        ////printf("%s:out_img_out_format %p\n",__func__,item);
        //if(item != NULL)
        //{
        //   mainInfo->main_out_img_out_format = item->valueint;
        //   //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        //}

        item=cJSON_GetObjectItem(object,"out_yuv422_pxl_order");
        //printf("%s:out_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           mainInfo->main_out_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"out_pxl_width");
        //printf("%s:out_pxl_width %p\n",__func__,item);
        if(item != NULL)
        {
           mainInfo->main_out_pxl_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"out_frame_buf_size");
        //printf("%s:out_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           mainInfo->main_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }    
        //out0
        struct isp_wrap_ds0_info	*wds0Info = &isp_wrap_cfg->ds0Info;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"ds0_out_img_format");
        //printf("%s:ds0_out_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds0Info->ds0_out_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds0_out_yuv_in_format");
        //printf("%s:ds0_out_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds0Info->ds0_out_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        //item=cJSON_GetObjectItem(object,"ds0_out_img_out_format");
        ////printf("%s:ds0_out_img_out_format %p\n",__func__,item);
        //if(item != NULL)
        //{
        //   wds0Info->ds0_out_img_out_format = item->valueint;
        //   //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        //}

        item=cJSON_GetObjectItem(object,"ds0_out_yuv422_pxl_order");
        //printf("%s:ds0_out_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           wds0Info->ds0_out_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds0_out_pxl_width");
        //printf("%s:ds0_out_pxl_width %p\n",__func__,item);
        if(item != NULL)
        {
           wds0Info->ds0_out_pxl_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds0_frame_buf_size");
        //printf("%s:ds0_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           wds0Info->ds0_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }  
        //out1
        struct isp_wrap_ds1_info	*wds1Info = &isp_wrap_cfg->ds1Info;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"ds1_out_img_format");
        //printf("%s:ds1_out_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds1Info->ds1_out_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds1_out_yuv_in_format");
        //printf("%s:ds1_out_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds1Info->ds1_out_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        //item=cJSON_GetObjectItem(object,"ds1_out_img_out_format");
        ////printf("%s:ds1_out_img_out_format %p\n",__func__,item);
        //if(item != NULL)
        //{
        //   wds1Info->ds1_out_img_out_format = item->valueint;
        //   //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        //}

        item=cJSON_GetObjectItem(object,"ds1_out_yuv422_pxl_order");
        //printf("%s:ds1_out_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           wds1Info->ds1_out_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds1_out_pxl_width");
        //printf("%s:ds1_out_pxl_width %p\n",__func__,item);
        if(item != NULL)
        {
           wds1Info->ds1_out_pxl_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds1_frame_buf_size");
        //printf("%s:ds1_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           wds1Info->ds1_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }  
        //out2
        struct isp_wrap_ds2_info	*wds2Info = &isp_wrap_cfg->ds2Info;

        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"ds2_out_img_format");
        //printf("%s:ds2_out_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds2Info->ds2_out_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds2_out_yuv_in_format");
        //printf("%s:ds2_out_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           wds2Info->ds2_out_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        //item=cJSON_GetObjectItem(object,"ds2_out_img_out_format");
        ////printf("%s:ds2_out_img_out_format %p\n",__func__,item);
        //if(item != NULL)
        //{
        //   wds2Info->ds2_out_img_out_format = item->valueint;
        //   //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        //}

        item=cJSON_GetObjectItem(object,"ds2_out_yuv422_pxl_order");
        //printf("%s:ds2_out_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           wds2Info->ds2_out_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds2_out_pxl_width");
        //printf("%s:ds2_out_pxl_width %p\n",__func__,item);
        if(item != NULL)
        {
           wds2Info->ds2_out_pxl_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ds2_frame_buf_size");
        //printf("%s:ds2_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           wds2Info->ds2_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 
        //wdr
        struct isp_wrap_wdr_info *wwdr_info = &isp_wrap_cfg->wdrInfo;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"wdr_mode");
        //printf("%s:wdr_mode %p\n",__func__,item);
        if(item != NULL)
        {
            wwdr_info->wdr_mode = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"wdr_long_ch_mode");
        //printf("%s:wdr_long_ch_mode %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_ch_mode = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"wdr_long_l2_buf_en");
        //printf("%s:wdr_long_l2_buf_en %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_l2_buf_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"wdr_short_s1_buf_en");
        //printf("%s:wdr_short_s1_buf_en %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_short_s1_buf_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_dynamic_switch_en");
        //printf("%s:wdr_dynamic_switch_en %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_dynamic_switch_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"wdr_long_l2_buf_depth");
        //printf("%s:wdr_long_l2_buf_depth %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_l2_buf_depth = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_long_img_format");
        //printf("%s:wdr_long_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_long_yuv_in_format");
        //printf("%s:wdr_long_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_long_img_out_format");
        //printf("%s:wdr_long_img_out_format %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_img_out_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_long_yuv422_pxl_order");
        //printf("%s:wdr_long_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_long_pixel_width");
        //printf("%s:wdr_long_pixel_width %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_long_pixel_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_buf_base");
        //printf("%s:wdr_buf_base %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_buf_base = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_line_stride");
        //printf("%s:wdr_line_stride %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_line_stride = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"wdr_frame_buf_size");
        //printf("%s:wdr_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           wwdr_info->wdr_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }
        //nr3d 
        struct isp_wrap_3dnr_info *w3dnr_info = &isp_wrap_cfg->nr3dInfo;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"nr3d_en");
        //printf("%s:nr3d_en %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"nr3d_fbcd_en");
        //printf("%s:nr3d_fbcd_en %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_fbcd_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_mv_out_en");
        //printf("%s:nr3d_mv_out_en %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_mv_out_en = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_y_img_format");
        //printf("%s:nr3d_y_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_y_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_y_yuv_in_format");
        //printf("%s:nr3d_y_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_y_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"nr3d_y_img_out_format");
        //printf("%s:nr3d_y_img_out_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_y_img_out_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_y_yuv422_pxl_order");
        //printf("%s:nr3d_y_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_y_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"nr3d_y_pixel_width");
        //printf("%s:nr3d_y_pixel_width %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_y_pixel_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"nr3d_uv_img_format");
        //printf("%s:nr3d_uv_img_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_uv_img_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_uv_yuv_in_format");
        //printf("%s:nr3d_uv_yuv_in_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_uv_yuv_in_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 

        item=cJSON_GetObjectItem(object,"nr3d_uv_mig_out_format");
        //printf("%s:nr3d_uv_mig_out_format %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_uv_mig_out_format = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }  

        item=cJSON_GetObjectItem(object,"nr3d_uv_yuv422_pxl_order");
        //printf("%s:nr3d_uv_yuv422_pxl_order %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_uv_yuv422_pxl_order = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"nr3d_uv_pixel_width");
        //printf("%s:nr3d_uv_pixel_width %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_uv_pixel_width = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }  

        item=cJSON_GetObjectItem(object,"nr3d_frame_buf_size");
        //printf("%s:nr3d_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           w3dnr_info->nr3d_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        } 
        //ldc 
        struct isp_wrap_ldc_info *wldc_info = &isp_wrap_cfg->ldcInfo;
        object=cJSON_GetArrayItem(arrayItem,i++);
        item=cJSON_GetObjectItem(object,"ldc_line_stride"); 
        //printf("%s:ldc_line_stride %p\n",__func__,item);
        if(item != NULL)
        {
           wldc_info->ldc_line_stride = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }

        item=cJSON_GetObjectItem(object,"ldc_frame_buf_size"); 
        //printf("%s:ldc_frame_buf_size %p\n",__func__,item);
        if(item != NULL)
        {
           wldc_info->ldc_frame_buf_size = item->valueint;
           //printf("cJSON_GetObjectItem: type=%d, string is %s, valueint is %d\n",item->type,item->string,item->valueint);
        }  
      }
      //isp_core
      arrayItem = cJSON_GetObjectItem(root,"isp_core");
      if(arrayItem != NULL)
      {
  	   	int size = cJSON_GetArraySize(arrayItem);
	   	//printf("%s:isp_core cJSON_GetArraySize: size=%d\n",__func__,size);
         //itc
         object=cJSON_GetArrayItem(arrayItem,0);
         parse_itc(object,&isp_core_cfg->itcInfo);
         //tpg
         object=cJSON_GetArrayItem(arrayItem,1);
         parse_tpg(object,&isp_core_cfg->tpgInfo);
         //blc
         object=cJSON_GetArrayItem(arrayItem,2);
         parse_blc(object,&isp_core_cfg->blcInfo);
         //lsc
         object=cJSON_GetArrayItem(arrayItem,3);
         parse_lsc(object,&isp_core_cfg->lscInfo);
         //ae
         object=cJSON_GetArrayItem(arrayItem,4);
         parse_ae(object,&isp_core_cfg->aeInfo);
         //awb
         object=cJSON_GetArrayItem(arrayItem,5);
         parse_awb(object,&isp_core_cfg->awbInfo);
         //wdr
         object=cJSON_GetArrayItem(arrayItem,6);
         parse_wdr(object,&isp_core_cfg->wdrInfo);
         //csc
         object=cJSON_GetArrayItem(arrayItem,7);
         parse_csc(object,&isp_core_cfg->cscInfo);
         //ada
         object=cJSON_GetArrayItem(arrayItem,8);
         parse_ada(object,&isp_core_cfg->adaInfo);
         //rgb-ir
         object=cJSON_GetArrayItem(arrayItem,9);
         parse_rgbir(object,&isp_core_cfg->rgbirInfo);
         //2dnr
         object=cJSON_GetArrayItem(arrayItem,10);
         parse_2dnr(object,&isp_core_cfg->nr2dInfo);
         //3dnr
         object=cJSON_GetArrayItem(arrayItem,11);
         parse_3dnr(object,&isp_core_cfg->nr3dInfo);
         //enh
         object=cJSON_GetArrayItem(arrayItem,12);
         parse_enh(object,&isp_core_cfg->enhInfo);
         //post_ctl
         object=cJSON_GetArrayItem(arrayItem,13);
         parse_postctl(object,&isp_core_cfg->postInfo,&isp_core_cfg->otcInfo);
         //ldc
         object=cJSON_GetArrayItem(arrayItem,14);
         parse_ldc(object,&isp_core_cfg->ldcInfo);
         isp_wrap_cfg->ldcInfo.ldc_en = isp_core_cfg->ldcInfo.ldc_en;
         //af
         object=cJSON_GetArrayItem(arrayItem,15);
         parse_af(object,&isp_core_cfg->afInfo);
      }
      //isp_post
      arrayItem = cJSON_GetObjectItem(root,"isp_post");    
      if(arrayItem != NULL)
      {
  	   	int size=cJSON_GetArraySize(arrayItem);
	   	//printf("%s:isp_post cJSON_GetArraySize: size=%d\n",__func__,size);
         object=cJSON_GetArrayItem(arrayItem,0);
         parse_rgb2yuv(object,isp_ds_cfg);
         //
         object=cJSON_GetArrayItem(arrayItem,1);
         parse_yuv2rgb(object,isp_ds_cfg);
         //
         object=cJSON_GetArrayItem(arrayItem,2);
         parse_ds0(object,&isp_ds_cfg->dsInfo[0]);  
         //
         object=cJSON_GetArrayItem(arrayItem,3);
         parse_ds1(object,&isp_ds_cfg->dsInfo[1]);
         //
         object=cJSON_GetArrayItem(arrayItem,4);
         parse_ds2(object,&isp_ds_cfg->dsInfo[2]);               
      }
      ////printf("%s:%s\n",__func__,item->valueint);
		cJSON_Delete(root);
		//printf("%s\n",out);
		free(out);
	}
}

/***************************************************************************
*Read a file, parse, render back, etc.
****************************************************************************/
void dofile_video_cfg(char *filename,struct vi_cfg_info *vi_cfg,struct sensor_info *sensor0,struct sensor_info *sensor1,struct video_info *dev_info)
{
	FILE *fp;
   long len;
   char *data;

	printf("%s:%s\n",__func__,filename);
	fp=fopen(filename,"rb");
   if(NULL == fp)
   {
     printf("%s:file no exist!\n",__func__);
     return;
   }
   fseek(fp,0,SEEK_END);
   len=ftell(fp);
   fseek(fp,0,SEEK_SET);
	data=(char*)malloc(len+1);
   fread(data,1,len,fp);
   fclose(fp);
	doit_video_cfg(data,vi_cfg,sensor0,sensor1,dev_info);
	free(data);
}
/**
 * @brief 
 * 
 * @param filename 
 * @param mipi_csi2 
 */
void dofile_csi2(char *filename,struct isp_csi2_info *mipi_csi2)
{
	FILE *fp;
   long len;
   char *data;

	printf("%s:%s\n",__func__,filename);
	fp=fopen(filename,"rb");
   if(NULL == fp)
   {
     printf("%s:file no exist!\n",__func__);
     return;
   }
   fseek(fp,0,SEEK_END);
   len=ftell(fp);
   fseek(fp,0,SEEK_SET);
	data=(char*)malloc(len+1);
   fread(data,1,len,fp);
   fclose(fp);
	doit_csi2(data,mipi_csi2);
	free(data);
}
/**
 * @brief 
 * 
 * @param filename 
 * @param vi_cfg 
 */
void dofile_vi(char *filename,struct vi_cfg_info *vi_cfg)
{
	FILE *fp;
   long len;
   char *data;

	printf("%s:%s\n",__func__,filename);
	fp=fopen(filename,"rb");
   if(NULL == fp)
   {
     printf("%s:file no exist!\n",__func__);
     return;
   }
   fseek(fp,0,SEEK_END);
   len=ftell(fp);
   fseek(fp,0,SEEK_SET);
	data=(char*)malloc(len+1);
   fread(data,1,len,fp);
   fclose(fp);
   doit_vi(data,vi_cfg);
	free(data);
}
/**
 * @brief 
 * 
 * @param filename 
 * @param sensor 
 */
void dofile_isp(char *filename,struct sensor_info *sensor)
{
	FILE *fp;
   long len;
   char *data;

	printf("%s:%s\n",__func__,filename);
	fp=fopen(filename,"rb");
   if(NULL == fp)
   {
     printf("%s:file no exist!\n",__func__);
     return;
   }
   fseek(fp,0,SEEK_END);
   len=ftell(fp);
   fseek(fp,0,SEEK_SET);
	data=(char*)malloc(len+1);
   fread(data,1,len,fp);
   fclose(fp);
   //doit_isp(data,&sensor->isp_cfg,&sensor->sensor_name[0]);
   doit_isp(data,&sensor->isp_cfg);
	free(data);
}

