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
#include "tddfa.h"

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

void tddfa::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = fa_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemFaOutput.size = output_size;
    allocAlignMemFaOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemFaOutput.phyAddr = 0;    

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFaOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemFaOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemFaOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFaOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemFaOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemFaInput[i].size = input_size;
        allocAlignMemFaInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemFaInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFaInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemFaInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemFaInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFaInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemFaInput error" << std::endl;
            std::abort();
        }
    }
}

void tddfa::set_input(uint32_t index)
{
    auto in_shape = interp_fa.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemFaInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_fa.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void tddfa::set_output()
{
    auto out_shape = interp_fa.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, fa_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemFaOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_fa.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void tddfa::load_model(char *path)
{
    fa_model = read_binary_file<unsigned char>(path);
    interp_fa.load_model({ (const gsl::byte *)fa_model.data(), fa_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_fa.load_model finished!" << std::endl;
}

void tddfa::run()
{
    interp_fa.run().expect("error occurred in running model");
}

void tddfa::set_valid_box(box_t b, cv::Mat mat)
{    
    float long_side = sqrtf(powf(b.w, 2) + powf(b.h, 2));
    float xmin = b.x - long_side / 2;
    float xmax = b.x + long_side / 2;
    float ymin = b.y - long_side / 2;
    float ymax = b.y + long_side / 2;
    xmin = minf(maxf(0.0, xmin), (float)(mat.cols));
    xmax = minf(maxf(0.0, xmax), (float)(mat.cols));
    ymin = minf(maxf(0.0, ymin), (float)(mat.rows));
    ymax = minf(maxf(0.0, ymax), (float)(mat.rows));
    valid_box.x = xmin;
    valid_box.y = ymin;
    valid_box.w = xmax - xmin;
    valid_box.h = ymax - ymin;
}

cv::Mat tddfa::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x) ,(int)(valid_box.y),(int)(valid_box.w),(int)(valid_box.h)));
    return cropped_image;
}

tddfa::tddfa(int net_len, int fa_num):net_len(net_len), fa_num(fa_num)
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

tddfa::~tddfa()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemFaInput[i].size);

        if(allocAlignMemFaInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFaInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemFaInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemFaOutput.size);
        
    if(allocAlignMemFaOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFaOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemFaOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
