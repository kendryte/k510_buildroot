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
#ifndef _LPRNET
#define _LPRNET

#include "cv2_utils.h"
#include <nncase/runtime/host_runtime_tensor.h>
#include <nncase/runtime/interpreter.h>
#include <nncase/runtime/runtime_tensor.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

using namespace nncase;
using namespace nncase::runtime;
using namespace nncase::runtime::detail;
using namespace std;

#define GNNE_BUFFERS_COUNT  1

class lprnet
{
public:
    lprnet(int net_height, int net_width, int char_num, int lpr_num);
    void prepare_memory();
    void set_input(uint32_t index);
    void set_output();
    void load_model(char *path);
    void run();
    std::string postprocess();
    void set_valid_box(box_t b, cv::Mat mat);
    cv::Mat crop_image(cv::Mat image);    
    void get_perspective_matrix(landmarks_t l, cv::Mat image, int valid_width, int valid_height);
    void perspective_image(cv::Mat image, cv::Mat warp_dst);
    ~lprnet();

    char *virtual_addr_output;
    char *virtual_addr_input[GNNE_BUFFERS_COUNT];
    struct share_memory_alloc_align_args allocAlignMemLprOutput;
    struct share_memory_alloc_align_args allocAlignMemLprInput[GNNE_BUFFERS_COUNT];
    int share_memory;
    int mem_map;
    box_t valid_box;


    // std::vector<std::string> labels
	// { 
    //      "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑",
	// 	 "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤",
	// 	 "桂", "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁",
	// 	 "新",
	// 	 "港", "澳", "台",
	// 	 "学", "使", "领", "警",
	// 	 "挂",
	// 	 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	// 	 "A", "B", "C", "D", "E", "F", "G", "H", "J", "K",
	// 	 "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V",
	// 	 "W", "X", "Y", "Z",
	// 	 "I", "O", "-"
	// };
    std::vector<std::string> labels
	{ 
         "beijing", "shanghai", "tianjian", "chongqing", "hebei", "shanxi", "neimenggu", "liaoning", "jilin", "heilongjiang",
		 "jiangsu", "zhejiang", "anhui", "fujian", "jiangxi", "shandong", "henan", "hubei", "hunan", "guangdong",
		 "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu", "qinghai", "ningxia",
		 "xinjiang",
		 "xianggang", "aomen", "taiwan",
		 "xue", "shi", "ling", "jing",
		 "gua",
		 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		 "A", "B", "C", "D", "E", "F", "G", "H", "J", "K",
		 "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V",
		 "W", "X", "Y", "Z",
		 "I", "O", "-"
	};

private:
    int net_height;
    int net_width;
    int input_size;
    int char_num;
    int lpr_num;
    int output_size;
    cv::Point2f srcTri[4];
	cv::Point2f dstTri[4];
    cv::Mat warp_mat;
    float *lpr_probs_trans;
    interpreter interp_lpr;
    vector<unsigned char> lpr_model;
};

#endif