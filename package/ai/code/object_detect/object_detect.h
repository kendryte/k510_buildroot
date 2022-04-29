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

#define GNNE_BUFFERS_COUNT          1
#define ANCHOR_NUM                  3
#define CLASS_NUM                   80
#define INPUT_CHANNELS              3
#define FEATURE_LEN                 (CLASS_NUM + 5) * ANCHOR_NUM

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

    char *virtualAddrOdOutput[3];
    uint32_t output_pa_addr[3];

    char *virtual_addr_output;
    char *virtual_addr_input[GNNE_BUFFERS_COUNT];
    struct share_memory_alloc_align_args allocAlignMemOdOutput;
    struct share_memory_alloc_align_args allocAlignMemOdInput[GNNE_BUFFERS_COUNT];

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
    int net_len;
    uint32_t input_size;
    uint32_t output_size[3];
    uint32_t output_all_size;
    interpreter interp_od;
    vector<unsigned char> od_model;
    int anchors_num = ANCHOR_NUM;
    int classes_num = CLASS_NUM;
    int channels = FEATURE_LEN;
    float anchors_0[ANCHOR_NUM][2] = { { 10, 13 }, { 16, 30 }, { 33, 23 } };
    float anchors_1[ANCHOR_NUM][2] = { { 30, 61 }, { 62, 45 }, { 59, 119 } };
    float anchors_2[ANCHOR_NUM][2] = { { 116, 90 }, { 156, 198 }, { 373, 326 } };
    float *output_0;
    float *output_1;
    float *output_2;
};
#endif
