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
#include "k510_drm.h"


extern std::vector<cv::Point> points_to_clear[DRM_BUFFERS_COUNT];
extern std::vector<std::string> strs_to_clear[DRM_BUFFERS_COUNT];
extern std::vector<std::vector<cv::Point>> first_lines_to_clear[DRM_BUFFERS_COUNT];
extern std::vector<std::vector<cv::Point>> second_lines_to_clear[DRM_BUFFERS_COUNT];

void rotationMatrixToEulerAngles(float (*R)[3], float* eular)
{
	float sy = sqrtf(powf(R[0][0], 2) + powf(R[1][0], 2));
	if (sy < 1e-6)
	{
		eular[0] = atan2f(-R[1][2], R[1][1]);
		eular[1] = atan2f(-R[2][0], sy);
		eular[2] = 0;
	}
	else
	{
		eular[0] = atan2f(R[2][1], R[2][2]);
		eular[1] = atan2f(-R[2][0], sy);
		eular[2] = atan2f(R[1][0], R[0][0]);
	}
	for (uint32_t ee = 0; ee < 3; ee++)
	{
		eular[ee] *= 180 / PI;
	}
}

void build_projection_matrix(float rear_size, float *projections)
{
	float rear_depth = 0;
	float factor = sqrtf(2.0);
	float front_size = factor * rear_size;
	float front_depth = factor * rear_size;
	float temp[8][3] = { {-rear_size, -rear_size, rear_depth},
				{-rear_size, rear_size, rear_depth},
				{rear_size, rear_size, rear_depth},
				{rear_size, -rear_size, rear_depth},
				{-front_size, -front_size, front_depth},
				{-front_size, front_size, front_depth},
				{front_size, front_size, front_depth},
				{front_size, -front_size, front_depth},
			};		
	memcpy(projections, temp, 8 * 3 * sizeof(float));
}

void draw_pose(box_t b, float *pdst, int valid_height, int valid_width, cv::Mat& frame, uint64_t index)
{
    float R[3][3] = { 0.0 };
	for(uint32_t hh = 0; hh < 3; hh++)
	{
		memcpy(&R[hh][0], pdst + hh * 4, 3 * sizeof(float));
	}
	float bbox[4] = {b.x - b.w / 2, b.y - b.h / 2, b.x + b.w / 2, b.y + b.h / 2};	
	int net_len = valid_height > valid_width ? valid_height : valid_width;
    bbox[0] = bbox[0] * net_len / valid_width * frame.cols;
    bbox[1] = bbox[1] * net_len / valid_height * frame.rows;
    bbox[2] = bbox[2] * net_len / valid_width * frame.cols;
    bbox[3] = bbox[3] * net_len / valid_height * frame.rows;   
	float height = bbox[3] - bbox[1];
	float width = bbox[2] - bbox[0];
	float center_x = (bbox[0] + bbox[2]) / 2.0;
	float center_y = (bbox[1] + bbox[3]) / 2.0;	
	float eular[3] = { 0.0 };
	float projections[8][3] = { 0.0 };
	float radius = 0.5 * (height > width ? height : width);
	build_projection_matrix(radius, &projections[0][0]);
	rotationMatrixToEulerAngles(R, eular);
	std::vector<cv::Point> first_points;
	first_points.clear();
	for (uint32_t pp = 0; pp < 4; pp++)
	{
		cv::Point point;
		float sum_x = 0.0, sum_y = 0.0;
		int x, y;
		for (uint32_t cc = 0; cc < 3; cc++)
		{
			sum_x += projections[pp][cc] * R[cc][0];
			sum_y += projections[pp][cc] * (-R[cc][1]);
		}
		x = static_cast<int>(sum_x + center_x);
		y = static_cast<int>(sum_y + center_y);
		point.x = std::max(0, std::min(x, frame.cols));
		point.y = std::max(0, std::min(y, frame.rows));
		first_points.push_back(point);
	}
	cv::polylines(frame, first_points, true, cv::Scalar(255, 0, 0, 255), 5, 8, 0);
	first_lines_to_clear[index].push_back(first_points);
	std::vector<cv::Point> second_points;
	second_points.clear();
	for (uint32_t pp = 4; pp < 8; pp++)
	{
		cv::Point point;
		float sum_x = 0.0, sum_y = 0.0;
		int x, y;
		for (uint32_t cc = 0; cc < 3; cc++)
		{
			sum_x += projections[pp][cc] * R[cc][0];
			sum_y += projections[pp][cc] * (-R[cc][1]);
		}
		x = static_cast<int>(sum_x + center_x);
		y = static_cast<int>(sum_y + center_y);
		point.x = std::max(0, std::min(x, frame.cols));
		point.y = std::max(0, std::min(y, frame.rows));
		second_points.push_back(point);
	}
	second_lines_to_clear[index].push_back(second_points);
	cv::polylines(frame, second_points, true, cv::Scalar(255, 0, 0, 255), 5, 8, 0);
	for (uint32_t ll = 0; ll < 4; ll++)
	{
		cv::line(frame, first_points[ll], second_points[ll], cv::Scalar(255, 0, 0, 255), 5, 8, 0);
	}
	std::string strs = "roll:" + std::to_string(eular[2]).substr(0, 6) + ";yaw:" + std::to_string(eular[1]).substr(0, 6) + ";pitch:" + std::to_string(eular[0]).substr(0, 6);
	cv::putText(frame, strs, cv::Point(int(bbox[0]), int(bbox[1])), cv::FONT_HERSHEY_COMPLEX, 1.2, cv::Scalar(0, 0, 255, 255), 2, 4, 0);
	strs_to_clear[index].push_back(strs);
	points_to_clear[index].push_back(cv::Point(int(bbox[0]), int(bbox[1])));
}