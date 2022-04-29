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
#include "lprnet.h"

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

void lprnet::prepare_memory()
{
    input_size = ((net_height * net_width * 3 + 4095) & (~4095));
    output_size = lpr_num * char_num * sizeof(float);
    output_size = ((output_size + 4095) & (~4095));

    allocAlignMemLprOutput.size = output_size;
    allocAlignMemLprOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemLprOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemLprOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemLprOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemLprOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemLprOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemLprOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemLprInput[i].size = input_size;
        allocAlignMemLprInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemLprInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemLprInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemLprInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemLprInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemLprInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemLprInput error" << std::endl;
            std::abort();
        }
    }

}

void lprnet::set_input(uint32_t index)
{
    auto in_shape = interp_lpr.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_height * net_width * 3},
        false, hrt::pool_shared, allocAlignMemLprInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_lpr.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void lprnet::set_output()
{
    auto out_shape = interp_lpr.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, lpr_num * char_num * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemLprOutput.phyAddr)
                        .expect("cannot create output tensor");
    interp_lpr.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void lprnet::load_model(char *path)
{
    lpr_model = read_binary_file<unsigned char>(path);
    interp_lpr.load_model({ (const gsl::byte *)lpr_model.data(), lpr_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_lpr.load_model finished!" << std::endl;
}

void lprnet::run()
{
    interp_lpr.run().expect("error occurred in running model");
}

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

std::string lprnet::postprocess()
{
    float *lpr_probs = reinterpret_cast<float *>(virtual_addr_output);
    std::vector<int> pred_label;
    std::vector<int> pred_index;
	for (uint32_t ll = 0; ll < lpr_num; ll++)
	{
		for (uint32_t pp = 0; pp < char_num; pp++)
		{
			lpr_probs_trans[ll * char_num + pp] = lpr_probs[pp * lpr_num + ll];
		}
	}
	for (uint32_t ll = 0; ll < lpr_num; ll++)
	{
		int max_index = argmax(lpr_probs_trans + ll * char_num, char_num);
		pred_label.push_back(max_index);
	}
	int pre_index = pred_label[0];
	if (pre_index != char_num - 1)
	{
		pred_index.push_back(pre_index);
	}
	for (auto p : pred_label)
	{
		if (p == char_num - 1)
		{
			pre_index = p;
			continue;
		}
		if (pre_index == p)
		{
			continue;
		}
		pred_index.push_back(p);
		pre_index = p;
	}
	std::string pred_str = "";
	for (auto p : pred_index)
	{
		pred_str += labels[p];
	}
    return pred_str;
}

void lprnet::set_valid_box(box_t b, cv::Mat mat)
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

cv::Mat lprnet::crop_image(cv::Mat image)
{
    cv::Mat cropped_image = image(cv::Rect((int)(valid_box.x) ,(int)(valid_box.y),(int)(valid_box.w),(int)(valid_box.h)));
    return cropped_image;
}

void lprnet::get_perspective_matrix(landmarks_t l, cv::Mat image, int valid_width, int valid_height)
{
    for (uint32_t ll = 0; ll < 4; ll++)
    {
        srcTri[ll] = cv::Point2f(l.points[2 * ll + 0] * image.cols - valid_box.x, l.points[2 * ll + 1] * valid_width / valid_height * image.rows - valid_box.y);
        // printf("x:%f, y:%f\n", l.points[2 * ll + 0] * image.cols - valid_box.x, l.points[2 * ll + 1] * valid_width / valid_height * image.rows - valid_box.y);
    }
    // for (uint32_t ll = 0; ll < 4; ll++)
    // {
    //     srcTri[ll] = cv::Point2f(valid_box.x + valid_box.w - l.points[2 * ll + 0] * image.cols, l.points[2 * ll + 1] * valid_width / valid_height * image.rows - valid_box.y);
    //     // printf("x:%f, y:%f\n", l.points[2 * ll + 0] * image.cols - valid_box.x, l.points[2 * ll + 1] * valid_width / valid_height * image.rows - valid_box.y);
    // }
    warp_mat = cv::getPerspectiveTransform(srcTri, dstTri);
}

void lprnet::perspective_image(cv::Mat image, cv::Mat warp_dst)
{   
    cv::warpPerspective(image, warp_dst, warp_mat, warp_dst.size());
}

lprnet::lprnet(int net_height, int net_width, int char_num, int lpr_num):net_height(net_height), net_width(net_width), char_num(char_num), lpr_num(lpr_num)
{
    dstTri[2] = cv::Point2f(0, 0);
	dstTri[3] = cv::Point2f(94, 0);
	dstTri[1] = cv::Point2f(0, 24);
	dstTri[0] = cv::Point2f(94, 24);
	// dstTri[3] = cv::Point2f(0, 0);
	// dstTri[2] = cv::Point2f(94, 0);
	// dstTri[0] = cv::Point2f(0, 24);
	// dstTri[1] = cv::Point2f(94, 24);
    lpr_probs_trans = new float[lpr_num * char_num];
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

lprnet::~lprnet()
{
    delete[] lpr_probs_trans;
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemLprInput[i].size);

        if(allocAlignMemLprInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemLprInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemLprInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemLprOutput.size);
    if(allocAlignMemLprOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemLprOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemLprOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
