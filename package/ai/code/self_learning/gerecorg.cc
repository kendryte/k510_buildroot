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
#include "gerecorg.h"

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

void gerecorg::prepare_memory()
{
    input_size = ((net_len * net_len * (3 + 1) + 4095) & (~4095));
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

void gerecorg::set_input(uint32_t index)
{
    auto in_shape = interp_fe.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemFeInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_fe.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void gerecorg::set_output()
{
    auto out_shape = interp_fe.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, fe_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemFeOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_fe.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void gerecorg::load_model(char *path)
{
    fe_model = read_binary_file<unsigned char>(path);
    interp_fe.load_model({ (const gsl::byte *)fe_model.data(), fe_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_fe.load_model finished!" << std::endl;
}

cv::Mat gerecorg::crop_image(cv::Mat image)
{
    int smaller = image.cols < image.rows ? image.cols : image.rows;
    int wh = (1 - 2 * MARGIN) * smaller;
    int32_t x0 = image.cols / 2 - wh/ 2;
    int32_t y0 = image.rows / 2 - wh/ 2;
    cv::Mat cropped_image = image(cv::Rect((int)(x0) ,(int)(y0),(int)(wh),(int)(wh)));
    return cropped_image;
}

void gerecorg::run()
{
    interp_fe.run().expect("error occurred in running model");
}

void gerecorg::l2normalize(float* x, float* dx, int len)
{
	int f;
	float sum = 0;
	for (f = 0; f < len; ++f)
	{
		sum += x[f] * x[f];
	}
	sum = sqrtf(sum);
	for (f = 0; f < len; ++f)
	{
		dx[f] = x[f] / sum;
	}
}

float gerecorg::calCosinDistance(float* objFeature0P, float* objFeature1P, int featureLen)
{
	float coorFeature = 0;
	// calculate the sum square
	for (int fIdx = 0; fIdx < featureLen; fIdx++)
	{
		float featureVal0 = *(objFeature0P + fIdx);
		float featureVal1 = *(objFeature1P + fIdx);
		coorFeature += featureVal0 * featureVal1;
	}
	// cosin distance
	return (0.5 + 0.5 * coorFeature) * 100;
}

uint32_t gerecorg::calulate_score(float* features, float* saved_features, uint32_t saved_len, float* score)
{
	int i;
	int v_id = -1;
	float v_score;
	float v_score_max = 0.0;
	float basef[fe_num], testf[fe_num];
	l2normalize(features, testf, fe_num);
	for (i = 0; i < saved_len; i++)
	{
		l2normalize(saved_features + i * fe_num, basef, fe_num);
		v_score = calCosinDistance(testf, basef, fe_num);
		if (v_score > v_score_max)
		{
			v_score_max = v_score;
			v_id = i;
		}
	}
	*score = v_score_max;
	return v_id;
}

gerecorg::gerecorg(int net_len, int fe_num, int max_register_obj, float thresh):net_len(net_len), fe_num(fe_num), max_register_obj(max_register_obj), thresh(thresh)
{    
    embs = new float[max_register_obj * fe_num];
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

gerecorg::~gerecorg()
{
    delete[] embs;
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
