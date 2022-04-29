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
#include "imagenet.h"

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

void imagenet::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = imnt_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemImntOutput.size = output_size;
    allocAlignMemImntOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemImntOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemImntOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemImntOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemImntOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemImntOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemImntOutput error" << std::endl;
        std::abort();
    }
    
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemImntInput[i].size = input_size;
        allocAlignMemImntInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemImntInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemImntInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemImntInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemImntInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemImntInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemImntInput error" << std::endl;
            std::abort();
        }
    }
}

void imagenet::set_input(uint32_t index)
{
    auto in_shape = interp_imnt.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemImntInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_imnt.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void imagenet::set_output()
{
    auto out_shape = interp_imnt.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, imnt_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemImntOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_imnt.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void imagenet::load_model(char *path)
{
    imnt_model = read_binary_file<unsigned char>(path);
    interp_imnt.load_model({ (const gsl::byte *)imnt_model.data(), imnt_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_imnt.load_model finished!" << std::endl;
}

void imagenet::run()
{
    interp_imnt.run().expect("error occurred in running model");
}

void imagenet::set_valid_box(box_t b, cv::Mat mat)
{    
    float xmin = b.x;
    float xmax = b.w;
    float ymin = b.y;
    float ymax = b.h;
    xmin = minf(maxf(0.0, xmin), (float)(mat.cols));
    xmax = minf(maxf(0.0, xmax), (float)(mat.cols));
    ymin = minf(maxf(0.0, ymin), (float)(mat.rows));
    ymax = minf(maxf(0.0, ymax), (float)(mat.rows));
    valid_box.x = xmin;
    valid_box.y = ymin;
    valid_box.w = xmax - xmin;
    valid_box.h = ymax - ymin;
}


cv::Mat imagenet::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x) ,(int)(valid_box.y),(int)(valid_box.w),(int)(valid_box.h)));
    return cropped_image;
}

void imagenet::post_process()
{
    float* output_data = reinterpret_cast<float *>(virtual_addr_output); 
    auto it = std::max_element(output_data, output_data + imnt_num);
    size_t index = it - output_data;
    idx = static_cast<int>(index);
    prob = output_data[idx];
}

std::vector<std::string> imagenet::get_label(char *label_name)
{
    std::ifstream fp(label_name);
    std::string label;
    while (getline(fp, label))
    {
        labels.push_back(label);
    }
    return labels;
}

imagenet::imagenet(int net_len, int imnt_num):net_len(net_len), imnt_num(imnt_num)
{   
    labels.reserve(imnt_num);
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

imagenet::~imagenet()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemImntInput[i].size);

        if(allocAlignMemImntInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemImntInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemImntInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemImntOutput.size);

    if(allocAlignMemImntOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemImntOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemImntOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
