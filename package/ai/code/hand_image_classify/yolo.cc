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
#include "yolo.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

int nms_comparator(void *pa, void *pb)
{
    sortable_obj_t a = *(sortable_obj_t *)pa;
    sortable_obj_t b = *(sortable_obj_t *)pb;
    float diff = a.probs[a.index] - b.probs[b.index];

    if (diff < 0)
        return 1;
    else if (diff > 0)
        return -1;
    return 0;
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

void yolo::prepare_memory()
{
    input_size = ((net_len * net_len * (3 + 1) + 4095) & (~4095));
    output_size = ((objs_num * (4 + 1 + 1) * sizeof(float) + 4095) & (~4095));

    allocAlignMemHdOutput.size = output_size;
    allocAlignMemHdOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemHdOutput.phyAddr = 0;

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHdOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemHdOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemHdOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHdOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemHdOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemHdInput[i].size = input_size;
        allocAlignMemHdInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemHdInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemHdInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemHdInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemHdInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemHdInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemHdInput error" << std::endl;
            std::abort();
        }
    }
}

void yolo::set_input(uint32_t index)
{
    auto in_shape = interp_hd.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_len * net_len * 3},
        false, hrt::pool_shared, allocAlignMemHdInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_hd.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void yolo::set_output()
{
    auto out_shape = interp_hd.output_shape(0);
    auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
    { (gsl::byte *)virtual_addr_output, objs_num * (4 + 1 + 1) * sizeof(float)},
    false, hrt::pool_shared, allocAlignMemHdOutput.phyAddr)
                        .expect("cannot create output tensor");

    interp_hd.output_tensor(0, output_tensor).expect("cannot set output tensor");
}

void yolo::load_model(char *path)
{
    hd_model = read_binary_file<unsigned char>(path);
    interp_hd.load_model({ (const gsl::byte *)hd_model.data(), hd_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_hd.load_model finished!" << std::endl;
}

void yolo::run()
{
    interp_hd.run().expect("error occurred in running model");
}

void yolo::get_output()
{
    boxes = reinterpret_cast<float *>(virtual_addr_output);
}

void yolo::post_process()
{
    for (uint32_t oo = 0; oo < objs_num; oo++)
	{
		s_probs[oo] = boxes[oo * (1 + 4 + 1) + 4];
	}
    for (uint32_t oo = 0; oo < objs_num; oo++)
    {
		so[oo].index = oo;
        so[oo].probs = s_probs;
    }
    qsort(so, objs_num, sizeof(sortable_obj_t), (__compar_fn_t)nms_comparator);
}

void yolo::get_final_box(vector<box_t> &valid_box)
{
	int i, j, k, obj_index;
	for (i = 0; i < objs_num; ++i)
	{
		obj_index = so[i].index;
		if (s_probs[obj_index] < obj_thresh)
			continue;
		box_t a = get_box(boxes, obj_index);
		valid_box.push_back(a);

		for (j = i + 1; j < objs_num; ++j)
		{
			obj_index = so[j].index;
			if (s_probs[obj_index] < obj_thresh)
				continue;
			box_t b = get_box(boxes, obj_index);
			if (box_iou(a, b) >= obj_thresh)
				s_probs[obj_index] = 0;
		}
	}
}

yolo::yolo(int net_len, float obj_thresh, float nms_thresh)
:net_len(net_len), obj_thresh(obj_thresh), nms_thresh(nms_thresh)
{
    int anchor_num = 3;
    objs_num = (net_len / 32 * net_len / 32) * (1 + 4) * anchor_num;
    so = new sortable_obj_t[objs_num];
    s_probs = new float[objs_num];

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

box_t yolo::get_box(float *boxes, int obj_index)
{
	float x, y, w, h;
	x = boxes[obj_index * (1 + 4 + 1) + 0];
	y = boxes[obj_index * (1 + 4 + 1) + 1];
	w = boxes[obj_index * (1 + 4 + 1) + 2];
	h = boxes[obj_index * (1 + 4 + 1) + 3];
	box_t box;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	return box;
}

float yolo::overlap(float x1, float w1, float x2, float w2)
{
    float l1 = x1 - w1 / 2;
    float l2 = x2 - w2 / 2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1 / 2;
    float r2 = x2 + w2 / 2;
    float right = r1 < r2 ? r1 : r2;
    return right - left;
}

float yolo::box_intersection(box_t a, box_t b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);

    if (w < 0 || h < 0)
        return 0;
    return w * h;
}

float yolo::box_union(box_t a, box_t b)
{
    float i = box_intersection(a, b);
    float u = a.w * a.h + b.w * b.h - i;

    return u;
}

float yolo::box_iou(box_t a, box_t b)
{
    return box_intersection(a, b) / box_union(a, b);
}

yolo::~yolo()
{
    delete[] so;
    delete[] s_probs;

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemHdInput[i].size);

        if(allocAlignMemHdInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHdInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemHdInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemHdOutput.size);
        
    if(allocAlignMemHdOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemHdOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemHdOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
