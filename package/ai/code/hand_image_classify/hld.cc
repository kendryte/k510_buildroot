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
#include "hld.h"

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

void hld::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = 2 * hk_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemHkOutput.size = output_size;
    allocAlignMemHkOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemHkOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHkOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemHkOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemHkOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHkOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemHkOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemHkInput[i].size = input_size;
        allocAlignMemHkInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemHkInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHkInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemHkInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemHkInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHkInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemHkInput error" << std::endl;
            std::abort();
        }
    }

}

void hld::set_input(uint32_t index)
{
    auto in_shape = interp_hk.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemHkInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_hk.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void hld::set_output()
{
    auto out_shape = interp_hk.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, 2 * hk_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemHkOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_hk.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void hld::load_model(char *path)
{
    hk_model = read_binary_file<unsigned char>(path);
    interp_hk.load_model({ (const gsl::byte *)hk_model.data(), hk_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_hk.load_model finished!" << std::endl;
}

void hld::run()
{
    interp_hk.run().expect("error occurred in running model");
}

void hld::set_valid_box(box_t b, cv::Mat mat)
{    
    float long_side = b.w > b.h ? b.w : b.h;
    long_side *= 1.26;
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


cv::Mat hld::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x) ,(int)(valid_box.y),(int)(valid_box.w),(int)(valid_box.h)));
    return cropped_image;
}

hld::hld(int net_len, int hk_num):net_len(net_len), hk_num(hk_num)
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

hld::~hld()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemHkInput[i].size);

        if(allocAlignMemHkInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHkInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemHkInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemHkOutput.size);

    if(allocAlignMemHkOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHkOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemHkOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
