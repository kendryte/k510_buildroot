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
#ifndef _CV2_UTILS
#define _CV2_UTILS

#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

// /* nncase runtime 里面已经添加了打印 */
// #define NNCASE_SCOPEDTIMING     0

// /* 使用uint8 模型 */
// #define USE_UINT8_MODEL         0

typedef struct BoxInfo
{
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    int label;
} BoxInfo;

typedef struct Framesize
{
    int width;
    int height;
} Framesize;

#define INTPUT_CHANNELS 3

cv::Mat read_image(const char *img_name);
cv::Mat get_isp_img(uint8_t *pimg, int valid_width, int valid_height);
cv::Mat pad_img_to_square(uint8_t *pimg, int valid_width, int valid_height);
cv::Mat letterbox(cv::Mat img, int width, int height);
cv::Mat od_get_scaled_img(cv::Mat img);
std::vector<BoxInfo> decode_infer(float *data, int net_size, int stride, int num_classes, Framesize frame_size, float anchors[][2], float threshold);
void nms(std::vector<BoxInfo> &input_boxes, float NMS_THRESH);
typedef struct
{
    float x;
    float y;
    float prob;
} point_t;

#if !NNCASE_SCOPEDTIMING
class ScopedTiming
{
public:
    ScopedTiming(std::string info = "ScopedTiming")
        : m_info(info)
    {
        m_start = std::chrono::steady_clock::now();
    }

    ~ScopedTiming()
    {
        m_stop = std::chrono::steady_clock::now();
        double elapsed_ms = std::chrono::duration<double, std::milli>(m_stop - m_start).count();
        std::cout << m_info << " took " << elapsed_ms << " ms" << std::endl;
    }

private:
    std::string m_info;
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_stop;
};
#endif
#endif