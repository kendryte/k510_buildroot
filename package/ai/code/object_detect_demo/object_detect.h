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
#ifndef _OBJECT_DETECT
#define _OBJECT_DETECT

#include "cv2_utils.h"
#include <nncase/runtime/host_runtime_tensor.h>
#include <nncase/runtime/interpreter.h>
#include <nncase/runtime/runtime_tensor.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

using namespace nncase;
using namespace nncase::runtime;
using namespace nncase::runtime::detail;
using namespace std;

#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)
#define SHARE_MEMORY_INVAL_RANGE    _IOWR('m', 5, unsigned long)
#define SHARE_MEMORY_WB_RANGE       _IOWR('m', 6, unsigned long)
#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"
#define MAP_MEMORY_DEV      "/dev/mem"

#define YOLOV5_FIX_SIZE 320
#define GNNE_BUFFERS_COUNT 1
#ifdef FULL_SCREEN
#define GNNE_INPUT_WIDTH 192
#define GNNE_INPUT_HEIGHT 320
#else
#define GNNE_INPUT_WIDTH 320
#define GNNE_INPUT_HEIGHT 240
#endif
#define INPUT_SIZE       (YOLOV5_FIX_SIZE * YOLOV5_FIX_SIZE * 4)

#define OUTPUT_SIZE0     (255*40*40*4)
#define OUTPUT_SIZE1     (255*20*20*4)
#define OUTPUT_SIZE2     (255*10*10*4)
#define OUTPUT_ALL_SIZE  ((OUTPUT_SIZE0 + OUTPUT_SIZE1 + OUTPUT_SIZE2 + 4095)&(~4095))

struct share_memory_alloc_args {
    uint32_t size;
    uint32_t phyAddr;
};

struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};

class objectDetect
{
public:
    objectDetect(float obj_thresh, float nms_thresh, int net_len, Framesize frame_size);
    void prepare_memory();
    void set_input(uint32_t index);
    void set_output();
    void load_model(char *path);
    void run();
    void get_output();
    void post_process(std::vector<BoxInfo> &result);
    ~objectDetect();

    char *virtualAddrFdOutput[3];
    uint32_t output_pa_addr[3];

    char *virtual_addr_output;
    char *virtual_addr_input[GNNE_BUFFERS_COUNT];
    struct share_memory_alloc_align_args allocAlignMemFdOutput;
    struct share_memory_alloc_align_args allocAlignMemFdInput[GNNE_BUFFERS_COUNT];

    int share_memory;
    int mem_map;
    std::vector<std::string> labels
    {
        "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck",
        "boat", "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
        "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe",
        "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard",
        "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle",
        "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
        "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake",
        "chair", "couch", "potted plant", "bed", "dining table", "toilet", "tv", "laptop",
        "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink",
        "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"
    };

private:
    float obj_thresh;
    float nms_thresh;
    Framesize frame_size;
    uint32_t output_size[3] = {
        OUTPUT_SIZE0,
        OUTPUT_SIZE1,
        OUTPUT_SIZE2
    };

    interpreter interp_od;
    vector<unsigned char> od_model;

    int net_len;
    int anchors_num = 3;
    int classes_num = 80;
    int channels = anchors_num * (5 + classes_num);
    int first_size;
    int second_size;
    int third_size;
    float anchors_0[3][2] = { { 10, 13 }, { 16, 30 }, { 33, 23 } };
    float anchors_1[3][2] = { { 30, 61 }, { 62, 45 }, { 59, 119 } };
    float anchors_2[3][2] = { { 116, 90 }, { 156, 198 }, { 373, 326 } };

    float *foutput_0;
    float *foutput_1;
    float *foutput_2;
};
#endif
