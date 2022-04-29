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
#include "pfld.h"

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

void pfld::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = 2 * fk_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemFkOutput.size = output_size;
    allocAlignMemFkOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemFkOutput.phyAddr = 0;    

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFkOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemFkOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemFkOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFkOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemFkOutput error" << std::endl;
        std::abort();
    }


    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemFkInput[i].size = input_size;
        allocAlignMemFkInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemFkInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFkInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemFkInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemFkInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFkInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemFkInput error" << std::endl;
            std::abort();
        }
    }
}

void pfld::set_input(uint32_t index)
{
    auto in_shape = interp_fk.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemFkInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_fk.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void pfld::set_output()
{
    auto out_shape = interp_fk.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, 2 * fk_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemFkOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_fk.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void pfld::load_model(char *path)
{
    fk_model = read_binary_file<unsigned char>(path);
    interp_fk.load_model({ (const gsl::byte *)fk_model.data(), fk_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_fk.load_model finished!" << std::endl;
}

void pfld::run()
{
    interp_fk.run().expect("error occurred in running model");
}

void pfld::set_valid_box(box_t b, cv::Mat mat)
{    
    float xmin = b.x - b.w / 2;
    float xmax = b.x + b.w / 2;
    float ymin = b.y - b.h / 2;
    float ymax = b.y + b.h / 2;
    xmin = minf(maxf(0.0, xmin), (float)(mat.cols));
    xmax = minf(maxf(0.0, xmax), (float)(mat.cols));
    ymin = minf(maxf(0.0, ymin), (float)(mat.rows));
    ymax = minf(maxf(0.0, ymax), (float)(mat.rows));
    valid_box.x = xmin;
    valid_box.y = ymin;
    valid_box.w = xmax - xmin;
    valid_box.h = ymax - ymin;
}

cv::Mat pfld::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x) ,(int)(valid_box.y),(int)(valid_box.w),(int)(valid_box.h)));
    return cropped_image;
}

float pfld::cal_erros(float *lst_pts, float *cur_pts)
{
    int first_index = (fk_num == 68 ? 36: 35);
    int second_index = (fk_num == 68 ? 45 : 93);
    float lst_interocular_distance = sqrtf(powf(lst_pts[2 * first_index + 0] - lst_pts[2 * second_index + 0], 2.0) + powf(lst_pts[2 * first_index + 1] - lst_pts[2 * second_index + 1], 2.0));
	float cur_interocular_distance = sqrtf(powf(cur_pts[2 * first_index + 0] - cur_pts[2 * second_index + 0], 2.0) + powf(cur_pts[2 * first_index + 1] - cur_pts[2 * second_index + 1], 2.0));
	float interocular_distance = (lst_interocular_distance + cur_interocular_distance) / 2;
	float error_all_points = 0;
	for(uint32_t kk = 0; kk < fk_num; kk++)
	{
		error_all_points += sqrtf(powf(cur_pts[2 * kk + 0] - lst_pts[2 * kk + 0], 2.0) + powf(cur_pts[2 * kk + 1] - lst_pts[2 * kk + 1], 2.0));
	}
	float error_norm = error_all_points / (interocular_distance * fk_num);
	return error_norm;
}

pfld::pfld(int net_len, int fk_num):net_len(net_len), fk_num(fk_num)
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

pfld::~pfld()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemFkInput[i].size);

        if(allocAlignMemFkInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFkInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemFkInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemFkOutput.size);

    if(allocAlignMemFkOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFkOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemFkOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
