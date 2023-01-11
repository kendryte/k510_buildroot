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
#include "face_expression.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

static int argmax(float* x, uint32_t len)
{
	float max_value = x[0];
	int max_index = 0;
	for (uint32_t ll = 1; ll < len; ll++)
	{
		if (max_value < x[ll])
		{
			max_value = x[ll];
			max_index = ll;
		}
	}
	return max_index;
}

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

void face_expression::prepare_memory()
{
    input_size = ((net_len * net_len * 3 + 4095) & (~4095));
    output_size = fe_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemFeOutput.size = output_size;
    allocAlignMemFeOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemFeOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFeOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemFeOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemFeOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFeOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemFeOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemFeInput[i].size = input_size;
        allocAlignMemFeInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemFeInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFeInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemFeInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemFeInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFeInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemFeInput error" << std::endl;
            std::abort();
        }
    }
}

void face_expression::set_input(uint32_t index)
{
    auto in_shape = interp_fe.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemFeInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_fe.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void face_expression::set_output()
{
    auto out_shape = interp_fe.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, fe_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemFeOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_fe.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void face_expression::load_model(char *path)
{
    fe_model = read_binary_file<unsigned char>(path);
    interp_fe.load_model({ (const gsl::byte *)fe_model.data(), fe_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_fe.load_model finished!" << std::endl;
}

void face_expression::run()
{
    interp_fe.run().expect("error occurred in running model");
}

void face_expression::get_affine_matrix(landmarks_t l, cv::Mat image, int valid_width, int valid_height)
{
    for (uint32_t ll = 0; ll < 5; ll++)
    {
        srcTri[ll] = cv::Point2f(l.points[2 * ll + 0] * image.cols, l.points[2 * ll + 1] * image.rows);
    }
    warp_mat = cv::getAffineTransform(srcTri, dstTri);
}

void face_expression::affine_image(cv::Mat image, cv::Mat warp_dst)
{   
    cv::warpAffine(image, warp_dst, warp_mat, warp_dst.size());
}

void face_expression::local_softmax(float *x, float *dx, uint32_t len)
{
    float max_value = x[0];
    for (uint32_t i = 0; i < len; i++)
    {
        if (max_value < x[i])
        {
            max_value = x[i];
        }
    }
    for (uint32_t i = 0; i < len; i++)
    {
        x[i] -= max_value;
        x[i] = expf(x[i]);
    }
    float sum_value = 0.0f;
    for (uint32_t i = 0; i < len; i++)
    {
        sum_value += x[i];
    }
    for (uint32_t i = 0; i < len; i++)
    {
        dx[i] = x[i] / sum_value;
    }
}

int face_expression::post_process()
{
    int max_index = -1;
    max_index = argmax(pred_probs, fe_num);
    return max_index;
}

face_expression::face_expression(int net_len, int fe_num, float thresh):net_len(net_len), fe_num(fe_num), thresh(thresh)
{    
	dstTri[0] = cv::Point2f(38.2946 * 2, 51.6963 * 2);
	dstTri[1] = cv::Point2f(73.5318 * 2, 51.5014 * 2);
	dstTri[2] = cv::Point2f(56.0252 * 2, 71.7366 * 2);
	dstTri[3] = cv::Point2f(41.5493 * 2, 92.3655 * 2);
	dstTri[4] = cv::Point2f(70.7299 * 2, 92.2041 * 2);
    pred_probs = new float[fe_num];
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

face_expression::~face_expression()
{
    delete[] pred_probs;
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemFeInput[i].size);

        if(allocAlignMemFeInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFeInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemFeInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemFeOutput.size);
    if(allocAlignMemFeOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFeOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemFeOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
