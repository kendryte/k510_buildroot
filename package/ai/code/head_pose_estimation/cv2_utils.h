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
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <stdint.h>


#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)
#define SHARE_MEMORY_INVAL_RANGE    _IOWR('m', 5, unsigned long)
#define SHARE_MEMORY_WB_RANGE       _IOWR('m', 6, unsigned long)
#define MEMORY_TEST_BLOCK_SIZE      4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN     4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */
#define SHARE_MEMORY_DEV            "/dev/k510-share-memory"
#define MAP_MEMORY_DEV              "/dev/mem"


#define PADDING_R 123
#define PADDING_G 117
#define PADDING_B 104
#define PI              3.1415926

struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};


typedef struct
{
    int index;
    float *probs;
} sortable_obj_t;

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} box_t;

typedef struct
{
    float points[10];
} landmarks_t;

typedef struct ai_worker_args
{
    char* fd_kmodel_path;
    int fd_net_len;
    int valid_width;
    int valid_height;
    float obj_thresh;
    float nms_thresh;
    char* hpe_kmodel_path;
    int hpe_net_len;
    int hpe_out_height;
    int hpe_out_width;
    int is_rgb;
    int enable_profile;
    std::string dump_img_dir;
}ai_worker_args;

void rotationMatrixToEulerAngles(float (*R)[3], float* eular);
void build_projection_matrix(float rear_size, float *projections);
void draw_pose(box_t b, float *pdst, int valid_height, int valid_width, cv::Mat& frame, uint64_t index);
class ScopedTiming
{
public:
    ScopedTiming(std::string info = "ScopedTiming", int enable_profile = 1)
        : m_info(info), enable_profile(enable_profile)
    {
        if(enable_profile)
        {
            m_start = std::chrono::steady_clock::now();
        }
    }

    ~ScopedTiming()
    {
        if(enable_profile)
        {
            m_stop = std::chrono::steady_clock::now();
            double elapsed_ms = std::chrono::duration<double, std::milli>(m_stop - m_start).count();
            std::cout << m_info << " took " << elapsed_ms << " ms" << std::endl;
        }
    }

private:
    int enable_profile;
    std::string m_info;
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_stop;
};
#endif
