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
#include "simple_pose.h"

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

void spose::prepare_memory()
{
    input_size = ((net_height * net_width * 3 + 4095) & (~4095));
    output_size = POSE_NUM * net_height / 4 * net_width / 4 * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemSposeOutput.size = output_size;
    allocAlignMemSposeOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemSposeOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemSposeOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemSposeOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemSposeOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemSposeOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemSposeOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemSposeInput[i].size = input_size;
        allocAlignMemSposeInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemSposeInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemSposeInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemSposeInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemSposeInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemSposeInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemSposeInput error" << std::endl;
            std::abort();
        }
    }
}

void spose::set_input(uint32_t index)
{
    auto in_shape = interp_spose.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_height * net_width * 3},
        false, hrt::pool_shared, allocAlignMemSposeInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_spose.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void spose::set_output()
{
    auto out_shape = interp_spose.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, POSE_NUM * net_height / 4 * net_width / 4 * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemSposeOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_spose.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void spose::load_model(char *path)
{
    spose_model = read_binary_file<unsigned char>(path);
    interp_spose.load_model({ (const gsl::byte *)spose_model.data(), spose_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_spose.load_model finished!" << std::endl;
}

void spose::run()
{
    interp_spose.run().expect("error occurred in running model");
}

void spose::set_valid_box(BoxInfo b, cv::Mat mat)
{    
    float xmin = b.x1;
    float xmax = b.x2;
    float ymin = b.y1;
    float ymax = b.y2;
    xmin = minf(maxf(0.0, xmin), (float)(mat.cols));
    xmax = minf(maxf(0.0, xmax), (float)(mat.cols));
    ymin = minf(maxf(0.0, ymin), (float)(mat.rows));
    ymax = minf(maxf(0.0, ymax), (float)(mat.rows));
    valid_box.x1 = xmin;
    valid_box.y1 = ymin;
    valid_box.x2 = xmax;
    valid_box.y2 = ymax;
}

cv::Mat spose::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x1) ,(int)(valid_box.y1),(int)(valid_box.x2 - valid_box.x1),(int)(valid_box.y2 - valid_box.y1)));
    return cropped_image;
}

void spose::post_process()
{
    float x1 = valid_box.x1;
    float y1 = valid_box.y1;
    float w = valid_box.x2 - valid_box.x1;
    float h = valid_box.y2 - valid_box.y1;
    int out_height = net_height / 4;
    int out_width = net_width / 4;
    keypoints.clear();
    float *p_all = reinterpret_cast<float *>(virtual_addr_output);
    for (int p = 0; p < POSE_NUM; p++)
    {
        float max_prob = 0.f;
        int max_x = 0;
        int max_y = 0;
        for (int y = 0; y < out_height; y++)
        {
            float* ptr = p_all + (p * out_height + y) * out_width;
            for (int x = 0; x < out_width; x++)
            {
                float prob = ptr[x];
                if (prob > max_prob)
                {
                    max_prob = prob;
                    max_x = x;
                    max_y = y;
                }
            }
        }
        KeyPoint keypoint;
        keypoint.p = cv::Point2f(max_x * w / (float)(out_width) + x1, max_y * h / (float)(out_height) + y1);
        keypoint.prob = max_prob;
        keypoints.push_back(keypoint);
    }        
}

spose::spose(int net_height, int net_width, float thresh):net_height(net_height), net_width(net_width), thresh(thresh)
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

spose::~spose()
{
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemSposeInput[i].size);

        if(allocAlignMemSposeInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemSposeInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemSposeInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemSposeOutput.size);

    if(allocAlignMemSposeOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemSposeOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemSposeOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
