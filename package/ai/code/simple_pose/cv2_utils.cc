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

float minf(float v1, float v2)
{
    return v1 < v2 ? v1 : v2;
}

float maxf(float v1, float v2)
{
    return v1 > v2 ? v1 : v2;
}

BoxInfo get_enlarged_box(BoxInfo b, cv::Mat mat)
{
    BoxInfo dest;
    float x, y, cx, cy, w, h;
    x = b.x1;
    y = b.y1;
    w = b.x2 - b.x1;
    h = b.y2 - b.y1;
    cx = x + 0.5 * w;
    cy = y + 0.5 * h;
    float x1, y1, x2, y2;
    x1 = cx - 0.7 * w;
    y1 = cy - 0.6 * h;
    x2 = cx + 0.7 * w;
    y2 = cy + 0.6 * h;
    dest.x1 = minf(maxf(0.0, x1), (float)(mat.cols));
    dest.y1 = minf(maxf(0.0, y1), (float)(mat.rows));
	dest.x2 = minf(maxf(0.0, x2), (float)(mat.cols));;
    dest.y2 = minf(maxf(0.0, y2), (float)(mat.rows));;
    return dest;
}

void nms(std::vector<BoxInfo> &input_boxes, float NMS_THRESH)
{
    std::sort(input_boxes.begin(), input_boxes.end(), [](BoxInfo a, BoxInfo b) { return a.score > b.score; });
    std::vector<float> vArea(input_boxes.size());
    for (int i = 0; i < int(input_boxes.size()); ++i)
    {
        vArea[i] = (input_boxes.at(i).x2 - input_boxes.at(i).x1 + 1)
            * (input_boxes.at(i).y2 - input_boxes.at(i).y1 + 1);
    }
    for (int i = 0; i < int(input_boxes.size()); ++i)
    {
        for (int j = i + 1; j < int(input_boxes.size());)
        {
            float xx1 = std::max(input_boxes[i].x1, input_boxes[j].x1);
            float yy1 = std::max(input_boxes[i].y1, input_boxes[j].y1);
            float xx2 = std::min(input_boxes[i].x2, input_boxes[j].x2);
            float yy2 = std::min(input_boxes[i].y2, input_boxes[j].y2);
            float w = std::max(float(0), xx2 - xx1 + 1);
            float h = std::max(float(0), yy2 - yy1 + 1);
            float inter = w * h;
            float ovr = inter / (vArea[i] + vArea[j] - inter);
            if (ovr >= NMS_THRESH)
            {
                input_boxes.erase(input_boxes.begin() + j);
                vArea.erase(vArea.begin() + j);
            }
            else
            {
                j++;
            }
        }
    }
}

std::vector<BoxInfo> decode_infer(float *data, int net_size, int stride, int num_classes, Framesize frame_size, float anchors[][2], float threshold)
{
    float ratiow = (float)net_size / frame_size.width;
    float ratioh = (float)net_size / frame_size.height;
    float gain = ratiow < ratioh ? ratiow : ratioh;
    std::vector<BoxInfo> result;
    int grid_size = net_size / stride;
    int one_rsize = num_classes + 5;
    float cx, cy, w, h;
    for (int shift_y = 0; shift_y < grid_size; shift_y++)
    {
        for (int shift_x = 0; shift_x < grid_size; shift_x++)
        {
            int loc = shift_x + shift_y * grid_size;
            for (int i = 0; i < 3; i++)
            {
                float *record = data + (loc * 3 + i) * one_rsize;
                float *cls_ptr = record + 5;
                for (int cls = 0; cls < 1; cls++)
                {
                    float score = (cls_ptr[cls]) * (record[4]);
                    if (score > threshold)
                    {
                        cx = ((record[0]) * 2.f - 0.5f + (float)shift_x) * (float)stride;
                        cy = ((record[1]) * 2.f - 0.5f + (float)shift_y) * (float)stride;
                        w = pow((record[2]) * 2.f, 2) * anchors[i][0];
                        h = pow((record[3]) * 2.f, 2) * anchors[i][1];
                        cx -= ((net_size - frame_size.width * gain) / 2);
                        cy -= ((net_size - frame_size.height * gain) / 2);
                        cx /= gain;
                        cy /= gain;
                        w /= gain;
                        h /= gain;
                        BoxInfo box;
                        box.x1 = std::max(0, std::min(frame_size.width, int(cx - w / 2.f)));
                        box.y1 = std::max(0, std::min(frame_size.height, int(cy - h / 2.f)));
                        box.x2 = std::max(0, std::min(frame_size.width, int(cx + w / 2.f)));
                        box.y2 = std::max(0, std::min(frame_size.height, int(cy + h / 2.f)));
                        box.score = score;
                        box.label = cls;
                        result.push_back(box);
                    }
                }
            }
        }
    }
    return result;
}

void draw_pose(int valid_height, int valid_width, cv::Mat& image, std::vector<KeyPoint> keypoints, float thresh)
{
    // draw bone
    static const int joint_pairs[16][2] = {
        {0, 1}, {1, 3}, {0, 2}, {2, 4}, {5, 6}, {5, 7}, {7, 9}, {6, 8}, {8, 10}, {5, 11}, {6, 12}, {11, 12}, {11, 13}, {12, 14}, {13, 15}, {14, 16}
    };
    for (int i = 0; i < 16; i++)
    {
        KeyPoint p1 = keypoints[joint_pairs[i][0]];
        KeyPoint p2 = keypoints[joint_pairs[i][1]];
        if (p1.prob < thresh || p2.prob < thresh)
            continue;
        int32_t x1 = p1.p.x / valid_width * image.cols;
        int32_t y1 = p1.p.y / valid_height * image.rows;

        int32_t x2 = p2.p.x / valid_width * image.cols;
        int32_t y2 = p2.p.y / valid_height * image.rows;    

        cv::line(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255, 0, 0, 127), 4);
    }
    // draw joint
    // printf("joints:\n");
    for (size_t i = 0; i < keypoints.size(); i++)
    {
        KeyPoint keypoint = keypoints[i];
        if (keypoint.prob < thresh)
            continue;
        int32_t x1 = keypoint.p.x / valid_width * image.cols;
        int32_t y1 = keypoint.p.y / valid_height * image.rows;
        // printf("%.2f %.2f = %.5f\n", keypoint.p.x, keypoint.p.y, keypoint.prob);
        cv::circle(image, cv::Point(x1, y1), 8, cv::Scalar(0, 255, 0, 127), -1);
    }
}