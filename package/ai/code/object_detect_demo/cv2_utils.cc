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

#if NNCASE_SCOPEDTIMING
#include <nncase/runtime/runtime_module.h>
using nncase::runtime::ScopedTiming;
#endif

cv::Mat read_image(const char *img_name)
{
    cv::Mat img = cv::imread(img_name);
    return img;
}

cv::Mat get_isp_img(uint8_t *pimg, int valid_width, int valid_height)
{
    cv::Mat img = cv::Mat::zeros(valid_height, valid_width, CV_8UC3);
    int pimgc = 4;
    for (int r = 0; r < valid_height; r++)
    {
        for (int c = 0; c < valid_width; c++)
        {
            int index = (r * valid_width + c) * pimgc;
            img.at<cv::Vec3b>(r, c)[0] = *(pimg + index + 3); //blue
            img.at<cv::Vec3b>(r, c)[1] = *(pimg + index + 2); //green
            img.at<cv::Vec3b>(r, c)[2] = *(pimg + index + 1); //red
        }
    }
    return img;
}

cv::Mat letterbox(cv::Mat img, int width, int height)
{
    int ori_w = img.cols;
    int ori_h = img.rows;
    float ratiow = (float)width / ori_w;
    float ratioh = (float)height / ori_h;
    float ratio = ratiow < ratioh ? ratiow : ratioh;
    int new_w = (int)(ratio * ori_w);
    int new_h = (int)(ratio * ori_h);
    float dw = (float)(width - new_w) / 2;
    float dh = (float)(height - new_h) / 2;
    int top = (int)(roundf(dh - 0.1));
    int bottom = (int)(roundf(dh + 0.1));
    int left = (int)(roundf(dw - 0.1));
    int right = (int)(roundf(dw - 0.1));
    cv::Mat cropped_img;
    {
        if ((new_w != width) || (new_h != height))
        {
            cv::resize(img, cropped_img, cv::Size(new_w, new_h), cv::INTER_AREA);
        }
    }
    {
        cv::copyMakeBorder(cropped_img, cropped_img, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));
    }
    return cropped_img;
}

cv::Mat od_get_scaled_img(cv::Mat img)
{
    {
        ScopedTiming st("cvtColor");
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    }

    return img;
}

cv::Mat pad_img_to_square(uint8_t *pimg, int valid_width, int valid_height)
{
#define B_MEAN 104
#define G_MEAN 117
#define R_MEAN 123
    int long_side = valid_width > valid_height ? valid_width : valid_height;
    cv::Mat img = cv::Mat::zeros(long_side, long_side, CV_8UC3);
    int rows = img.rows;
    int cols = img.cols;
    int pimgc = 3;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            int index = (r * valid_width + c) * pimgc;
            if ((r < valid_height) && (c < valid_width))
            {
                img.at<cv::Vec3b>(r, c)[0] = *(pimg + index + 2); //blue
                img.at<cv::Vec3b>(r, c)[1] = *(pimg + index + 1); //green
                img.at<cv::Vec3b>(r, c)[2] = *(pimg + index + 0); //red
            }
            else
            {
                img.at<cv::Vec3b>(r, c)[0] = B_MEAN; //blue
                img.at<cv::Vec3b>(r, c)[1] = G_MEAN; //green
                img.at<cv::Vec3b>(r, c)[2] = R_MEAN; //red
            }
        }
    }
    return img;
}

static float sigmoid(float x)
{
    return 1.0f / (1.0f + expf(-x));
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
                for (int cls = 0; cls < num_classes; cls++)
                {
                    float score = sigmoid(cls_ptr[cls]) * sigmoid(record[4]);
                    if (score > threshold)
                    {
                        cx = (sigmoid(record[0]) * 2.f - 0.5f + (float)shift_x) * (float)stride;
                        cy = (sigmoid(record[1]) * 2.f - 0.5f + (float)shift_y) * (float)stride;
                        w = pow(sigmoid(record[2]) * 2.f, 2) * anchors[i][0];
                        h = pow(sigmoid(record[3]) * 2.f, 2) * anchors[i][1];
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
