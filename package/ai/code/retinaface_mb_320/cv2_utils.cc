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

cv::Mat get_isp_img(uint8_t *pimg, int valid_width, int valid_height) {

  cv::Mat img = cv::Mat(valid_height, valid_width, CV_8UC3);
  int pimgc = 4;
  for (int r = 0; r < valid_height; r++) {
    for (int c = 0; c < valid_width; c++) {
      int index = (r * valid_width + c) * pimgc;
      img.at<cv::Vec3b>(r, c)[0] = *(pimg + index + 3); // blue
      img.at<cv::Vec3b>(r, c)[1] = *(pimg + index + 2); // green
      img.at<cv::Vec3b>(r, c)[2] = *(pimg + index + 1); // red
    }
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

cv::Mat get_img(cv::Mat img)
{
#define B_MEAN 104
#define G_MEAN 117
#define R_MEAN 123
    {
        ScopedTiming st("resize");
        cv::resize(img, img, cv::Size(FD_FIX_SIZE, FD_FIX_SIZE), cv::INTER_LINEAR);
    }
#if !USE_UINT8_MODEL
    std::vector<cv::Mat> imgpart(img.channels());
    {
        ScopedTiming st("split");
        cv::split(img, imgpart);
    }


    {
        ScopedTiming st("convertTo");
        imgpart[0].convertTo(imgpart[0], CV_32FC1, 1.0, -1.0 * B_MEAN);
        imgpart[1].convertTo(imgpart[1], CV_32FC1, 1.0, -1.0 * G_MEAN);
        imgpart[2].convertTo(imgpart[2], CV_32FC1, 1.0, -1.0 * R_MEAN);
    }

    {
        ScopedTiming st("merge");
        cv::merge(imgpart, img);
    }
#endif
    return img;
}