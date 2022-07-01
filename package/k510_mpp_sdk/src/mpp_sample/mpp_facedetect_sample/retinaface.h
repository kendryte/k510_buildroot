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
#ifndef _RETINAFACE
#define _RETINAFACE

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

#define GNNE_BUFFERS_COUNT  1
#define INPUT_CHANNELS      3
#define LOC_SIZE            4
#define CONF_SIZE           2
#define LAND_SIZE           10

class retinaface
{
public:
    retinaface(int net_len, float obj_thresh, float nms_thresh);
    void prepare_memory();
    void set_input(uint32_t index);
    void set_output();
    void load_model(char *path);
    void run();
    void post_process();
    void get_final_box(vector<box_t> &valid_box, vector<landmarks_t> &valid_landmarks);
    ~retinaface();

    char *virtualAddrFdOutput[9];
    char *virtual_addr_output;
    char *virtual_addr_input[GNNE_BUFFERS_COUNT];
    struct share_memory_alloc_align_args allocAlignMemFdOutput;
    struct share_memory_alloc_align_args allocAlignMemFdInput[GNNE_BUFFERS_COUNT];
    int share_memory;
    int mem_map;

private:
    void local_softmax(float *x, float *dx, uint32_t len);
    void deal_conf(float *conf, float *s_probs, sortable_obj_t *so, int size, int &obj_cnt);
    void deal_loc(float *loc, float *boxes, int size, int &obj_cnt);
    void deal_landms(float *landms, float *landmarks, int size, int &obj_cnt);
    box_t get_box(float *boxes, int obj_index);
    landmarks_t get_landmark(float *landmarks, int obj_index);
    float overlap(float x1, float w1, float x2, float w2);
    float box_intersection(box_t a, box_t b);
    float box_union(box_t a, box_t b);
    float box_iou(box_t a, box_t b);

    int net_len;
    int min_size;
    int input_size;
    float obj_thresh;
    float nms_thresh;
    int objs_num;
    uint32_t output_pa_addr[9];
    uint32_t output_size[9];
    uint32_t output_all_size;

    sortable_obj_t *so;
    float *s_probs;
    float *boxes;
    float *landmarks;

    interpreter interp_fd;
    vector<unsigned char> fd_model;
};

#endif