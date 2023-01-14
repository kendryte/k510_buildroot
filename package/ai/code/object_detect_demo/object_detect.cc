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
    allocAlignMemFdOutput.size = OUTPUT_ALL_SIZE;
    allocAlignMemFdOutput.alignment = 4096;
    allocAlignMemFdOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFdOutput) < 0) {
        std::cerr << "alloc allocAlignMemFdOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemFdOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFdOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) {
        std::cerr << "map allocAlignMemFdOutput error" << std::endl;
        std::abort();
    }

    virtualAddrFdOutput[0] = virtual_addr_output;
    output_pa_addr[0] = allocAlignMemFdOutput.phyAddr;
    for(uint32_t i = 1; i < 3; i++)
    {
        virtualAddrFdOutput[i] = virtualAddrFdOutput[i - 1] + output_size[i - 1];
        output_pa_addr[i] = output_pa_addr[i - 1] + output_size[i - 1];
    }

    for(int i=0; i<GNNE_BUFFERS_COUNT; i++) {
        allocAlignMemFdInput[i].size = INPUT_SIZE+4096;
        allocAlignMemFdInput[i].alignment = 4096;
        allocAlignMemFdInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFdInput[i]) < 0) {
            std::cerr << "alloc allocAlignMemFdInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemFdInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFdInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) {
            std::cerr << "map allocAlignMemFdInput error" << std::endl;
            std::abort();
        }
        memset(virtual_addr_input[i], 114, allocAlignMemFdInput[i].size);
    }
}

void objectDetect::set_input(uint32_t index)
{
    auto in_shape = interp_od.input_shape(0);

    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], YOLOV5_FIX_SIZE * YOLOV5_FIX_SIZE * INTPUT_CHANNELS },
        false, hrt::pool_shared, allocAlignMemFdInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_od.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void objectDetect::set_output()
{
    for (size_t i = 0; i < interp_od.outputs_size(); i++)
    {
        auto out_shape = interp_od.output_shape(i);
        auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
        { (gsl::byte *)virtualAddrFdOutput[i], output_size[i]},
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
    float *output_0 = reinterpret_cast<float *>(virtualAddrFdOutput[0]);
    float *output_1 = reinterpret_cast<float *>(virtualAddrFdOutput[1]);
    float *output_2 = reinterpret_cast<float *>(virtualAddrFdOutput[2]);

    int first_len = net_len / 8;
    int first_size = first_len * first_len;
    int second_len = net_len / 16;
    int second_size = second_len * second_len;
    int third_len = net_len / 32;
    int third_size = third_len * third_len;

    for (size_t j = 0; j < first_size; j++)
    {
        for (size_t c = 0; c < channels; c++)
        {
            foutput_0[j * channels + c] = output_0[c * first_size + j];
        }
    }
    for (size_t j = 0; j < second_size; j++)
    {
        for (size_t c = 0; c < channels; c++)
        {
            foutput_1[j * channels + c] = output_1[c * second_size + j];
        }
    }
    for (size_t j = 0; j < third_size; j++)
    {
        for (size_t c = 0; c < channels; c++)
        {
            foutput_2[j * channels + c] = output_2[c * third_size + j];
        }
    }
}

void objectDetect::post_process(std::vector<BoxInfo> &result)
{
    auto boxes0 = decode_infer(foutput_0, net_len, 8, classes_num, frame_size, anchors_0, obj_thresh);
    result.insert(result.begin(), boxes0.begin(), boxes0.end());
    auto boxes1 = decode_infer(foutput_1, net_len, 16, classes_num, frame_size, anchors_1, obj_thresh);
    result.insert(result.begin(), boxes1.begin(), boxes1.end());
    auto boxes2 = decode_infer(foutput_2, net_len, 32, classes_num, frame_size, anchors_2, obj_thresh);
    result.insert(result.begin(), boxes2.begin(), boxes2.end());
    nms(result, nms_thresh);
}

objectDetect::objectDetect(float obj_thresh, float nms_thresh, int net_len, Framesize frame_size)
:obj_thresh(obj_thresh), nms_thresh(nms_thresh), net_len(net_len), frame_size(frame_size)
{
    int first_len = net_len / 8;
    first_size = first_len * first_len;
    int second_len = net_len / 16;
    second_size = second_len * second_len;
    int third_len = net_len / 32;
    third_size = third_len * third_len;

    foutput_0 = new float[channels * first_size];
    foutput_1 = new float[channels * second_size];
    foutput_2 = new float[channels * third_size];

    share_memory = open(SHARE_MEMORY_DEV, O_RDWR);
    if(share_memory < 0) {
        std::cerr << "open /dev/k510-share-memory error" << std::endl;
        std::abort();
    }
    mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (mem_map < 0) {
        std::cerr << "open /dev/mem error" << std::endl;
        std::abort();
    }

    printf("---------------------------start ---------------------------------------- \n");
}


objectDetect::~objectDetect()
{
    delete[] foutput_0;
    delete[] foutput_1;
    delete[] foutput_2;

    for(int i=0; i<GNNE_BUFFERS_COUNT; i++) {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemFdInput[i].size);

        if(allocAlignMemFdInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFdInput[i].phyAddr) < 0) {
                std::cerr << "free allocAlignMemFdInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemFdOutput.size);

    if(allocAlignMemFdOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFdOutput.phyAddr) < 0) {
            std::cerr << "free allocAlignMemFdOutput error" << std::endl;
            std::abort();
        }
    }
    std::cout << "------------------------------------------------------------------- \n";
    close(share_memory);
    close(mem_map);
}
