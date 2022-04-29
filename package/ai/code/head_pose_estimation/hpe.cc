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
#include "hpe.h"

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

void hpe::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = out_height * out_width * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemHpeOutput.size = output_size;
    allocAlignMemHpeOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemHpeOutput.phyAddr = 0;
    
    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHpeOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemHpeOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemHpeOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHpeOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemHpeOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemHpeInput[i].size = input_size;
        allocAlignMemHpeInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemHpeInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHpeInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemHpeInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemHpeInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHpeInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemHpeInput error" << std::endl;
            std::abort();
        }
    }
}

void hpe::set_input(uint32_t index)
{
    auto in_shape = interp_hpe.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemHpeInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_hpe.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void hpe::set_output()
{
    auto out_shape = interp_hpe.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, out_height * out_width * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemHpeOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_hpe.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void hpe::load_model(char *path)
{
    hpe_model = read_binary_file<unsigned char>(path);
    interp_hpe.load_model({ (const gsl::byte *)hpe_model.data(), hpe_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_hpe.load_model finished!" << std::endl;
}

void hpe::run()
{
    interp_hpe.run().expect("error occurred in running model");
}

void hpe::get_warp_mtr(box_t b, int valid_width)
{
    float factor = 2.7;
    float bbox[4] = {b.x - b.w / 2, b.y - b.h / 2, b.x + b.w / 2, b.y + b.h / 2};
    bbox[0] = bbox[0] * valid_width;
    bbox[1] = bbox[1] * valid_width;
    bbox[2] = bbox[2] * valid_width;
    bbox[3] = bbox[3] * valid_width;    
    float _edge_size = net_len;
	float _trans_distance = _edge_size / 2.0;
	float height = bbox[3] - bbox[1];
	float width = bbox[2] - bbox[0];
	float center_x = (bbox[0] + bbox[2]) / 2.0;
	float center_y = (bbox[1] + bbox[3]) / 2.0;
	float maximum_edge = factor * (height > width ? height : width);
	float scale = _edge_size * 2.0 / maximum_edge;
	float cx = _trans_distance - scale * center_x;
	float cy = _trans_distance - scale * center_y;
	float warp_arr_temp[2][3] = { {scale, 0, cx}, {0, scale, cy} };
    memcpy(warp_arr, warp_arr_temp, 2 * 3 * sizeof(float));
}

void hpe::affine_image(cv::Mat image, cv::Mat warp_dst)
{   
    cv::Mat warp_mat(2, 3, CV_32FC1, warp_arr);
    cv::warpAffine(image, warp_dst, warp_mat, warp_dst.size());
}

hpe::hpe(int net_len, int out_height, int out_width):net_len(net_len), out_height(out_height), out_width(out_width)
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

hpe::~hpe()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemHpeInput[i].size);

        if(allocAlignMemHpeInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHpeInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemHpeInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemHpeOutput.size);

    if(allocAlignMemHpeOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHpeOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemHpeOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
