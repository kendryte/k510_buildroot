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
#include "scrpd.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

extern float anchors_0[][2];
extern float anchors_1[][2];
extern float anchors_2[][2];
extern float anchors_3[][2];
extern float anchors_4[][2];
static int output_size0 = 4800;
static int output_size1 = 1200;
static int output_size2 = 300;
static int output_size3 = 80;
static int output_size4 = 20;

static void get_real_index(int obj_cnt, int& p_index, int& index)
{
	index = obj_cnt;
	if (obj_cnt >= (output_size0 + output_size1 + output_size2 + output_size3))
	{
		index = obj_cnt - (output_size0 + output_size1 + output_size2 + output_size3);
		p_index = 4;
	}
	else
	{
		if (obj_cnt >= (output_size0 + output_size1 + output_size2))
		{
			index = obj_cnt - (output_size0 + output_size1 + output_size2);
			p_index = 3;
		}
		else
		{
			if (obj_cnt >= (output_size0 + output_size1))
			{
				index = obj_cnt - (output_size0 + output_size1);
				p_index = 2;
			}
			else
			{
				if (obj_cnt >= output_size0)
				{
					index = obj_cnt - output_size0;
					p_index = 1;
				}
				else
				{
					index = obj_cnt;
					p_index = 0;
				}
			}
		}
	}
}

static float get_coord(float coord, int boader)
{
	if (coord < 0)
	{
		return 0;
	}
	else
	{
		if (coord >= boader)
		{
			return boader - 1.0;
		}
	}
	return coord;
}

box_t scrpd::get_box(float* boxes, float anchors[][2], int obj_index, int stride, int xmax, int ymax)
{
	float x1, y1, x2, y2;
	x1 = anchors[obj_index][0] - boxes[obj_index * 4 + 0] * stride;
	y1 = anchors[obj_index][1] - boxes[obj_index * 4 + 1] * stride;
	x2 = anchors[obj_index][0] + boxes[obj_index * 4 + 2] * stride;
	y2 = anchors[obj_index][1] + boxes[obj_index * 4 + 3] * stride;
	x1 = get_coord(x1, xmax);
	x2 = get_coord(x2, xmax);
	y1 = get_coord(y1, ymax);
	y2 = get_coord(y2, ymax);
	box_t box;
	box.x = (x1 + x2) / 2;
	box.y = (y1 + y2) / 2;
	box.w = x2 - x1 + 1;
	box.h = y2 - y1 + 1;
	return box;
}


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

void scrpd::prepare_memory()
{
    input_size = ((net_height * net_width * (INPUT_CHANNELS + 1) + 4095) & (~4095));
    output_size[0] = output_size0 * 1 * sizeof(float);
    output_size[1] = output_size1 * 1 * sizeof(float);
    output_size[2] = output_size2 * 1 * sizeof(float);
    output_size[3] = output_size3 * 1 * sizeof(float);
    output_size[4] = output_size4 * 1 * sizeof(float);
    output_size[5] = output_size0 * 4 * sizeof(float);
    output_size[6] = output_size1 * 4 * sizeof(float);
    output_size[7] = output_size2 * 4 * sizeof(float);
    output_size[8] = output_size3 * 4 * sizeof(float);
    output_size[9] = output_size4 * 4 * sizeof(float);
    output_size[10] = output_size0 * 10 * sizeof(float);
    output_size[11] = output_size1 * 10 * sizeof(float);
    output_size[12] = output_size2 * 10 * sizeof(float);
    output_size[13] = output_size3 * 10 * sizeof(float);
    output_size[14] = output_size4 * 10 * sizeof(float);
    output_all_size = 0;
    for(uint32_t i=0; i<15; i++)
    {
        output_all_size += output_size[i];
    }
    output_all_size = ((output_all_size + 4095) & (~4095));

    allocAlignMemPdOutput.size = output_all_size;
    allocAlignMemPdOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemPdOutput.phyAddr = 0;    

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemPdOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemPdOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemPdOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemPdOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemPdOutput error" << std::endl;
        std::abort();
    }
    
    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemPdInput[i].size = input_size;
        allocAlignMemPdInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemPdInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemPdInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemPdInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemPdInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemPdInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemPdInput error" << std::endl;
            std::abort();
        }
    }


    virtualAddrPdOutput[0] = virtual_addr_output;
    output_pa_addr[0] = allocAlignMemPdOutput.phyAddr;

    output_pa_addr[1] = output_pa_addr[0] + output_size[0];
    output_pa_addr[2] = output_pa_addr[1] + output_size[1];
    output_pa_addr[3] = output_pa_addr[2] + output_size[2];
    output_pa_addr[4] = output_pa_addr[3] + output_size[3];
    output_pa_addr[5] = output_pa_addr[4] + output_size[4];
    output_pa_addr[6] = output_pa_addr[5] + output_size[5];
    output_pa_addr[7] = output_pa_addr[6] + output_size[6];
    output_pa_addr[8] = output_pa_addr[7] + output_size[7];
    output_pa_addr[9] = output_pa_addr[8] + output_size[8];
    output_pa_addr[10] = output_pa_addr[9] + output_size[9];
    output_pa_addr[11] = output_pa_addr[10] + output_size[10];
    output_pa_addr[12] = output_pa_addr[11] + output_size[11];
    output_pa_addr[13] = output_pa_addr[12] + output_size[12];
    output_pa_addr[14] = output_pa_addr[13] + output_size[13];

    virtualAddrPdOutput[1] = virtualAddrPdOutput[0] + output_size[0];
    virtualAddrPdOutput[2] = virtualAddrPdOutput[1] + output_size[1];
    virtualAddrPdOutput[3] = virtualAddrPdOutput[2] + output_size[2];
    virtualAddrPdOutput[4] = virtualAddrPdOutput[3] + output_size[3];
    virtualAddrPdOutput[5] = virtualAddrPdOutput[4] + output_size[4];
    virtualAddrPdOutput[6] = virtualAddrPdOutput[5] + output_size[5];
    virtualAddrPdOutput[7] = virtualAddrPdOutput[6] + output_size[6];
    virtualAddrPdOutput[8] = virtualAddrPdOutput[7] + output_size[7];
    virtualAddrPdOutput[9] = virtualAddrPdOutput[8] + output_size[8];
    virtualAddrPdOutput[10] = virtualAddrPdOutput[9] + output_size[9];
    virtualAddrPdOutput[11] = virtualAddrPdOutput[10] + output_size[10];
    virtualAddrPdOutput[12] = virtualAddrPdOutput[11] + output_size[11];
    virtualAddrPdOutput[13] = virtualAddrPdOutput[12] + output_size[12];
    virtualAddrPdOutput[14] = virtualAddrPdOutput[13] + output_size[13];
}

void scrpd::set_input(uint32_t index)
{
    auto in_shape = interp_pd.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_height * net_width * INPUT_CHANNELS},
        false, hrt::pool_shared, allocAlignMemPdInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_pd.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void scrpd::set_output()
{
    for (size_t i = 0; i < interp_pd.outputs_size(); i++)
    {
        auto out_shape = interp_pd.output_shape(i);
        auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
        { (gsl::byte *)virtualAddrPdOutput[i], output_size[i]},
        false, hrt::pool_shared, output_pa_addr[i])
                            .expect("cannot create output tensor");

        interp_pd.output_tensor(i, output_tensor).expect("cannot set output tensor");
    }
}

void scrpd::load_model(char *path)
{
    pd_model = read_binary_file<unsigned char>(path);
    interp_pd.load_model({ (const gsl::byte *)pd_model.data(), pd_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_pd.load_model finished!" << std::endl;
}

void scrpd::run()
{
    interp_pd.run().expect("error occurred in running model");
}

void scrpd::post_process()
{
    bbox_vector.clear();
    score_vector.clear();
    for(uint32_t oo = 0; oo < 5; oo++)
    {
        float *pscore = reinterpret_cast<float *>(virtualAddrPdOutput[oo]);
        float *pbox = reinterpret_cast<float *>(virtualAddrPdOutput[oo + 5]);
        score_vector.push_back(pscore);
        bbox_vector.push_back(pbox);
    }
    for (uint32_t obj_cnt = 0; obj_cnt < objs_num; obj_cnt++)
	{
		so[obj_cnt].index = obj_cnt;
		get_real_index(obj_cnt, p_index, index);
		float* score = score_vector[p_index];
		s_probs[obj_cnt] = score[index];
	}
    for (uint32_t oo = 0; oo < objs_num; oo++)
	{
		so[oo].probs = s_probs;
	}
    qsort(so, objs_num, sizeof(sortable_obj_t), (__compar_fn_t)nms_comparator);
}

void scrpd::get_final_box(vector<box_t> &valid_box)
{
    int i, j, k, obj_index;
	for (i = 0; i < objs_num; ++i)
	{
		obj_index = so[i].index;
		if (s_probs[obj_index] < obj_thresh)
			continue;
		get_real_index(obj_index, p_index, index);
		box_t a = get_box(bbox_vector[p_index], anchors_vector[p_index], index, strides[p_index], net_width, net_height);
		valid_box.push_back(a);
		for (j = i + 1; j < objs_num; ++j)
		{
			obj_index = so[j].index;
			if (s_probs[obj_index] < obj_thresh)
				continue; 
			get_real_index(obj_index, p_index, index);
			box_t b = get_box(bbox_vector[p_index], anchors_vector[p_index], index, strides[p_index], net_width, net_height);
			if (box_iou(a, b) >= nms_thresh)
				s_probs[obj_index] = 0;
		}
	}
}

scrpd::scrpd(int net_height, int net_width, float obj_thresh, float nms_thresh)
:net_height(net_height), net_width(net_width), obj_thresh(obj_thresh), nms_thresh(nms_thresh)
{
    anchors_vector.push_back(anchors_0);
	anchors_vector.push_back(anchors_1);
	anchors_vector.push_back(anchors_2);
	anchors_vector.push_back(anchors_3);
	anchors_vector.push_back(anchors_4);
    strides.push_back(8);
	strides.push_back(16);
	strides.push_back(32);
	strides.push_back(64);
	strides.push_back(128);
    objs_num = output_size0 + output_size1 + output_size2 + output_size3 + output_size4;
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

float scrpd::overlap(float x1, float w1, float x2, float w2)
{
    float l1 = x1 - w1 / 2;
    float l2 = x2 - w2 / 2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1 / 2;
    float r2 = x2 + w2 / 2;
    float right = r1 < r2 ? r1 : r2;
    return right - left;
}

float scrpd::box_intersection(box_t a, box_t b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);

    if (w < 0 || h < 0)
        return 0;
    return w * h;
}

float scrpd::box_union(box_t a, box_t b)
{
    float i = box_intersection(a, b);
    float u = a.w * a.h + b.w * b.h - i;

    return u;
}

float scrpd::box_iou(box_t a, box_t b)
{
    return box_intersection(a, b) / box_union(a, b);
}

scrpd::~scrpd()
{
    delete[] so;
    delete[] s_probs;

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemPdInput[i].size);

        if(allocAlignMemPdInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemPdInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemPdInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemPdOutput.size);
        
    if(allocAlignMemPdOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemPdOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemPdOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
