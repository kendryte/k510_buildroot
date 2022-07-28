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
#include "cv2_utils.h"

box_t scale_coords(int net_len, box_t b, int valid_width, int valid_height)
{
	int height = valid_height;
	int width = valid_width;
	int long_side = width > height ? width : height;
	float gain = 1.0 * net_len / long_side;
	float pad_x = (net_len - width * gain) / 2;
	float pad_y = (net_len - height * gain) / 2;
	box_t new_b;
	new_b.x = (b.x - pad_x) / gain;
	new_b.y = (b.y - pad_y) / gain;
	new_b.w = (b.w) / gain;
	new_b.h = (b.h) / gain;
	return new_b;
}


float minf(float v1, float v2)
{
    return v1 < v2 ? v1 : v2;
}

float maxf(float v1, float v2)
{
    return v1 > v2 ? v1 : v2;
}

box_t get_enlarged_box(box_t b, int valid_width, int valid_height, cv::Mat mat, float enlarge_ratio)
{
    box_t dest;
    float x, y, w, h;
    x = b.x * mat.cols;
    y = b.y * valid_width / valid_height * mat.rows;
    w = b.w * mat.cols;
    h = b.h * valid_width / valid_height * mat.rows;
    float long_side = maxf(w, h);
    long_side = enlarge_ratio * long_side;
    dest.x = minf(maxf(0.0, x), (float)(mat.cols));
    dest.y = minf(maxf(0.0, y), (float)(mat.rows));
	dest.w = long_side;
    dest.h = long_side;
    return dest;
}

box_t get_box_from_landmarks(box_t valid_box, float *cur_pts, int fk_num, float enlarge_ratio)
{
	float xmin = cur_pts[0], xmax = cur_pts[0];
	float ymin = cur_pts[1], ymax = cur_pts[1];
	for(uint32_t kk = 1; kk < fk_num; kk++)
	{
		if(cur_pts[2 * kk + 0] < xmin)
		{
			xmin = cur_pts[2 * kk + 0];
		}
		if(cur_pts[2 * kk + 0] > xmax)
		{
			xmax = cur_pts[2 * kk + 0];
		}
		if(cur_pts[2 * kk + 1] < ymin)
		{
			ymin = cur_pts[2 * kk + 1];
		}
		if(cur_pts[2 * kk + 1] > ymax)
		{
			ymax = cur_pts[2 * kk + 1];
		}
	}
    xmin = xmin * valid_box.w + valid_box.x;
    ymin = ymin * valid_box.h + valid_box.y;
    xmax = xmax * valid_box.w + valid_box.x;
    ymax = ymax * valid_box.h + valid_box.y;
	float width, height, long_side; 
    width = xmax - xmin;
    height = ymax - ymin;
    long_side = width > height ? width : height;
    long_side = enlarge_ratio * long_side;
	box_t dest;
	dest.x = (xmin + width / 2);
	dest.y = (ymin + height / 2);
    dest.w = long_side;
    dest.h = long_side;
	return dest;
}

frame_coordinate_info get_frame_coord(box_t r, int valid_width, int valid_height, int display_width, int display_height)
{
    frame_coordinate_info frame_coordinate;
    int32_t x0 = (r.x - r.w / 2) / valid_width * display_width;
    int32_t y0 = (r.y - r.h / 2) / valid_height * display_height;
    int32_t x1 = (r.x + r.w / 2) / valid_width  * display_width;
    int32_t y1 = (r.y + r.h / 2) / valid_height * display_height;

    x0 = std::max(0, std::min(x0, display_width));
    y0 = std::max(0, std::min(y0, display_height));
    x1 = std::max(0, std::min(x1, display_width));
    y1 = std::max(0, std::min(y1, display_height));
    
    frame_coordinate.startx = x0;
    frame_coordinate.starty = y0;
    frame_coordinate.endx = x1;
    frame_coordinate.endy = y1;
    return frame_coordinate;
}