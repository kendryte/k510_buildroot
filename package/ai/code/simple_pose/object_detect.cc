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
#include "object_detect.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

template <class T>
std::vector<T> read_binary_file(const char *file_name)
{
    std::ifstream ifs(file_name, std::ios::binary);
    ifs.seekg(0, ifs.end);
    size_t len = ifs.tellg();
    std::vector<T> vec(len / sizeof(T), 0);
    ifs.seekg(0, ifs.beg);
    ifs.read(reinterpret_cast<char *>(vec.data()), len);
    ifs.close();
    return vec;
}

void objectDetect::prepare_memory()
{
    input_size = ((net_len * net_len * (3 + 1) + 4095) & (~4095));
    output_size[0] = (FEATURE_LEN * (net_len / 8)  * (net_len / 8)  * sizeof(float));
    output_size[1] = (FEATURE_LEN * (net_len / 16)  * (net_len / 16)  * sizeof(float));
    output_size[2] = (FEATURE_LEN * (net_len / 32)  * (net_len / 32)  * sizeof(float));
    output_all_size = ((output_size[0] + output_size[1] + output_size[2] + 4095) & (~4095));

    allocAlignMemOdOutput.size = output_all_size;
    allocAlignMemOdOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemOdOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemOdOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemOdOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemOdOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemOdOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemOdOutput error" << std::endl;
        std::abort();
    }
    
    virtualAddrOdOutput[0] = virtual_addr_output;
    output_pa_addr[0] = allocAlignMemOdOutput.phyAddr;
    for(uint32_t i = 1; i < 3; i++)
    {
        virtualAddrOdOutput[i] = virtualAddrOdOutput[i - 1] + output_size[i - 1];
        output_pa_addr[i] = output_pa_addr[i - 1] + output_size[i - 1];
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemOdInput[i].size = input_size;
        allocAlignMemOdInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemOdInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemOdInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemOdInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemOdInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemOdInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemOdInput error" << std::endl;
            std::abort();
        }
    }
}

void objectDetect::set_input(uint32_t index)
{
    auto in_shape = interp_od.input_shape(0);

    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemOdInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_od.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void objectDetect::set_output()
{
    for (size_t i = 0; i < interp_od.outputs_size(); i++)
    {
        auto out_shape = interp_od.output_shape(i);
        auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
        { (gsl::byte *)virtualAddrOdOutput[i], output_size[i]},
        false, hrt::pool_shared, output_pa_addr[i])
                            .expect("cannot create output tensor");

        interp_od.output_tensor(i, output_tensor).expect("cannot set output tensor");
    }
}

void objectDetect::load_model(char *path)
{
    od_model = read_binary_file<unsigned char>(path);
    interp_od.load_model({ (const gsl::byte *)od_model.data(), od_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_od.load_model finished!" << std::endl;
}

void objectDetect::run()
{
    interp_od.run().expect("error occurred in running model");
}
void objectDetect::get_output()
{
    output_0 = reinterpret_cast<float *>(virtualAddrOdOutput[0]);
    output_1 = reinterpret_cast<float *>(virtualAddrOdOutput[1]);
    output_2 = reinterpret_cast<float *>(virtualAddrOdOutput[2]);
}

// 后处理
void objectDetect::post_process(std::vector<BoxInfo> &result)
{
    auto boxes0 = decode_infer(output_0, net_len, 8, classes_num, frame_size, anchors_0, obj_thresh);
    result.insert(result.begin(), boxes0.begin(), boxes0.end());
    auto boxes1 = decode_infer(output_1, net_len, 16, classes_num, frame_size, anchors_1, obj_thresh);
    result.insert(result.begin(), boxes1.begin(), boxes1.end());
    auto boxes2 = decode_infer(output_2, net_len, 32, classes_num, frame_size, anchors_2, obj_thresh);
    result.insert(result.begin(), boxes2.begin(), boxes2.end());
    nms(result, nms_thresh);
}

objectDetect::objectDetect(float obj_thresh, float nms_thresh, int net_len, Framesize frame_size)
:obj_thresh(obj_thresh), nms_thresh(nms_thresh), net_len(net_len), frame_size(frame_size)
{
    share_memory = open(SHARE_MEMORY_DEV, O_RDWR);
    if(share_memory < 0) 
    {
        std::cerr << "open /dev/k510-share-memory error" << std::endl;
        std::abort();
    }
    mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (mem_map < 0) 
    {
        std::cerr << "open /dev/mem error" << std::endl;
        std::abort();
    }
}


objectDetect::~objectDetect()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemOdInput[i].size);

        if(allocAlignMemOdInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemOdInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemOdInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemOdOutput.size);

    if(allocAlignMemOdOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemOdOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemOdOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
