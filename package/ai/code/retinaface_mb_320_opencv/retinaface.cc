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
#include "retinaface.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

extern float anchors320[4200][4];

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

void retinaface::prepare_memory()
{
    allocAlignMemFdOutput.size = OUTPUT_ALL_SIZE;
    allocAlignMemFdOutput.alignment = 4096;
    allocAlignMemFdOutput.phyAddr = 0;
    
    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFdOutput) < 0) {
        std::cerr << "alloc allocAlignMemFdOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemFdOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFdOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) {
        std::cerr << "map allocAlignMemFdOutput error" << std::endl;
        std::abort();
    }

    for(int i=0; i<GNNE_BUFFERS_COUNT; i++) {
        allocAlignMemFdInput[i].size = INPUT_SIZE;
        allocAlignMemFdInput[i].alignment = 4096;
        allocAlignMemFdInput[i].phyAddr = 0;
        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemFdInput[i]) < 0) {
            std::cerr << "alloc allocAlignMemFdInput error:" << i << std::endl;
            std::abort();
        }

        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemFdInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemFdInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) {
            std::cerr << "map allocAlignMemFdInput error:" << i << std::endl;
            std::abort();
        }
        memset(virtual_addr_input[i], R_MEAN, RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE);
        memset(virtual_addr_input[i] + RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE, G_MEAN, RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE);
        memset(virtual_addr_input[i] + RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE *2, B_MEAN, RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE);
    }
    virtualAddrFdOutput[0] = virtual_addr_output;
    output_pa_addr[0] = allocAlignMemFdOutput.phyAddr;

    output_pa_addr[3] = output_pa_addr[0] + output_size[0];
    output_pa_addr[6] = output_pa_addr[3] + output_size[3];
    output_pa_addr[1] = output_pa_addr[6] + output_size[6];
    output_pa_addr[4] = output_pa_addr[1] + output_size[1];
    output_pa_addr[7] = output_pa_addr[4] + output_size[4];
    output_pa_addr[2] = output_pa_addr[7] + output_size[7];
    output_pa_addr[5] = output_pa_addr[2] + output_size[2];
    output_pa_addr[8] = output_pa_addr[5] + output_size[5];

    virtualAddrFdOutput[3] = virtualAddrFdOutput[0] + output_size[0];
    virtualAddrFdOutput[6] = virtualAddrFdOutput[3] + output_size[3];
    virtualAddrFdOutput[1] = virtualAddrFdOutput[6] + output_size[6];
    virtualAddrFdOutput[4] = virtualAddrFdOutput[1] + output_size[1];
    virtualAddrFdOutput[7] = virtualAddrFdOutput[4] + output_size[4];
    virtualAddrFdOutput[2] = virtualAddrFdOutput[7] + output_size[7];
    virtualAddrFdOutput[5] = virtualAddrFdOutput[2] + output_size[2];
    virtualAddrFdOutput[8] = virtualAddrFdOutput[5] + output_size[5];
}

void retinaface::set_input(uint32_t index)
{
    auto in_shape = interp_fd.input_shape(0);

    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], RETINAFACE_FIX_SIZE * RETINAFACE_FIX_SIZE * 3},
        false, hrt::pool_shared, allocAlignMemFdInput[index].phyAddr)
                            .expect("cannot create input tensor");

    interp_fd.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void retinaface::set_output()
{
    for (size_t i = 0; i < interp_fd.outputs_size(); i++)
    {
        auto out_shape = interp_fd.output_shape(i);
        auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
        { (gsl::byte *)virtualAddrFdOutput[i], output_size[i]},
        false, hrt::pool_shared, output_pa_addr[i])
                            .expect("cannot create output tensor");

        interp_fd.output_tensor(i, output_tensor).expect("cannot set output tensor");
    }
}

void retinaface::load_model(char *path)
{
    fd_model = read_binary_file<unsigned char>(path);
    interp_fd.load_model({ (const gsl::byte *)fd_model.data(), fd_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_fd.load_model finished!" << std::endl;
}

void retinaface::run()
{
    interp_fd.run().expect("error occurred in running model");
}

void retinaface::post_process()
{
    int obj_cnt = 0;
    deal_conf(reinterpret_cast<float *>(virtualAddrFdOutput[3]), s_probs, so, 16 * MIN_SIZE / 2, obj_cnt);
    deal_conf(reinterpret_cast<float *>(virtualAddrFdOutput[4]), s_probs, so, 4 * MIN_SIZE / 2, obj_cnt);
    deal_conf(reinterpret_cast<float *>(virtualAddrFdOutput[5]), s_probs, so, 1 * MIN_SIZE / 2, obj_cnt);
    obj_cnt = 0;
    deal_loc(reinterpret_cast<float *>(virtualAddrFdOutput[0]), boxes, 16 * MIN_SIZE / 2, obj_cnt);
    deal_loc(reinterpret_cast<float *>(virtualAddrFdOutput[1]), boxes, 4 * MIN_SIZE / 2, obj_cnt);
    deal_loc(reinterpret_cast<float *>(virtualAddrFdOutput[2]), boxes, 1 * MIN_SIZE / 2, obj_cnt);
    obj_cnt = 0;
    deal_landms(reinterpret_cast<float *>(virtualAddrFdOutput[6]), landmarks, 16 * MIN_SIZE / 2, obj_cnt);
    deal_landms(reinterpret_cast<float *>(virtualAddrFdOutput[7]), landmarks, 4 * MIN_SIZE / 2, obj_cnt);
    deal_landms(reinterpret_cast<float *>(virtualAddrFdOutput[8]), landmarks, 1 * MIN_SIZE / 2, obj_cnt);

    for (uint32_t oo = 0; oo < objs_num; oo++)
    {
        so[oo].probs = s_probs;
    }
    qsort(so, objs_num, sizeof(sortable_obj_t), (__compar_fn_t)nms_comparator);
}

void retinaface::get_final_box(vector<box_t> &valid_box, vector<landmarks_t> &valid_landmarks)
{
    int iou_cal_times = 0;
    int i, j, obj_index;
    for (i = 0; i < objs_num; ++i)
    {
        obj_index = so[i].index;
        if (s_probs[obj_index] < obj_thresh)
            continue;
        box_t a = get_box(boxes, obj_index);
        landmarks_t l = get_landmark(landmarks, obj_index);
        valid_box.push_back(a);
        valid_landmarks.push_back(l);

        for (j = i + 1; j < objs_num; ++j)
        {
            obj_index = so[j].index;
            if (s_probs[obj_index] < obj_thresh)
                continue;
            box_t b = get_box(boxes, obj_index);
            iou_cal_times += 1;
            if (box_iou(a, b) >= nms_thresh)
                s_probs[obj_index] = 0;
        }
    }
}

retinaface::retinaface(float obj_thresh, float nms_thresh)
:obj_thresh(obj_thresh), nms_thresh(nms_thresh)
{
    std::cout << "-------------------------retinaface-------------------------------- \n";
    objs_num = MIN_SIZE * (1 + 4 + 16);
    so = new sortable_obj_t[objs_num];
    s_probs = new float[objs_num * LOC_SIZE];
    boxes = new float[objs_num * LOC_SIZE];
    landmarks = new float[objs_num * LAND_SIZE];

    share_memory = open(SHARE_MEMORY_DEV, O_RDWR);
    if(share_memory < 0) {
        std::cerr << "open /dev/k510-share-memory error" << std::endl;
        std::abort();
    }
    mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (mem_map < 0) {
        std::cerr << "open /dev/mem error" << std::endl;
        std::abort();
    }
}

void retinaface::local_softmax(float *x, float *dx, uint32_t len)
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

void retinaface::deal_conf(float *conf, float *s_probs, sortable_obj_t *so, int size, int &obj_cnt)
{
    float prob[CONF_SIZE] = { 0.0 };
    for (uint32_t ww = 0; ww < size; ww++)
    {
        for (uint32_t hh = 0; hh < 2; hh++)
        {
            for (uint32_t cc = 0; cc < CONF_SIZE; cc++)
            {
                prob[cc] = conf[(hh * CONF_SIZE + cc) * size + ww];
            }
            local_softmax(prob, prob, 2);
            so[obj_cnt].index = obj_cnt;
            s_probs[obj_cnt] = prob[1];
            obj_cnt += 1;
        }
    }
}

void retinaface::deal_loc(float *loc, float *boxes, int size, int &obj_cnt)
{
    for (uint32_t ww = 0; ww < size; ww++)
    {
        for (uint32_t hh = 0; hh < 2; hh++)
        {
            for (uint32_t cc = 0; cc < LOC_SIZE; cc++)
            {
                boxes[obj_cnt * LOC_SIZE + cc] = loc[(hh * LOC_SIZE + cc) * size + ww];
            }
            obj_cnt += 1;
        }
    }
}

void retinaface::deal_landms(float *landms, float *landmarks, int size, int &obj_cnt)
{
    for (uint32_t ww = 0; ww < size; ww++)
    {
        for (uint32_t hh = 0; hh < 2; hh++)
        {
            for (uint32_t cc = 0; cc < LAND_SIZE; cc++)
            {
                landmarks[obj_cnt * LAND_SIZE + cc] = landms[(hh * LAND_SIZE + cc) * size + ww];
            }
            obj_cnt += 1;
        }
    }
}

box_t retinaface::get_box(float *boxes, int obj_index)
{
    float x, y, w, h;
    x = boxes[obj_index * LOC_SIZE + 0];
    y = boxes[obj_index * LOC_SIZE + 1];
    w = boxes[obj_index * LOC_SIZE + 2];
    h = boxes[obj_index * LOC_SIZE + 3];
    x = anchors320[obj_index][0] + x * 0.1 * anchors320[obj_index][2];
    y = anchors320[obj_index][1] + y * 0.1 * anchors320[obj_index][3];
    w = anchors320[obj_index][2] * expf(w * 0.2);
    h = anchors320[obj_index][3] * expf(h * 0.2);
    box_t box;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    return box;
}

landmarks_t retinaface::get_landmark(float *landmarks, int obj_index)
{
    landmarks_t landmark;
    for (uint32_t ll = 0; ll < 5; ll++)
    {
        landmark.points[2 * ll + 0] = anchors320[obj_index][0] + landmarks[obj_index * LAND_SIZE + 2 * ll + 0] * 0.1 * anchors320[obj_index][2];
        landmark.points[2 * ll + 1] = anchors320[obj_index][1] + landmarks[obj_index * LAND_SIZE + 2 * ll + 1] * 0.1 * anchors320[obj_index][3];
    }
    return landmark;
}

float retinaface::overlap(float x1, float w1, float x2, float w2)
{
    float l1 = x1 - w1 / 2;
    float l2 = x2 - w2 / 2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1 / 2;
    float r2 = x2 + w2 / 2;
    float right = r1 < r2 ? r1 : r2;

    return right - left;
}

float retinaface::box_intersection(box_t a, box_t b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);

    if (w < 0 || h < 0)
        return 0;
    return w * h;
}

float retinaface::box_union(box_t a, box_t b)
{
    float i = box_intersection(a, b);
    float u = a.w * a.h + b.w * b.h - i;

    return u;
}

float retinaface::box_iou(box_t a, box_t b)
{
    return box_intersection(a, b) / box_union(a, b);
}

retinaface::~retinaface()
{
    delete[] so;
    delete[] s_probs;
    delete[] landmarks;

    for(int i=0; i<GNNE_BUFFERS_COUNT; i++) {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemFdInput[i].size);

        if(allocAlignMemFdInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFdInput[i].phyAddr) < 0) {
                std::cerr << "free allocAlignMemFdInput error:" << i << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemFdOutput.size);

    if(allocAlignMemFdOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemFdOutput.phyAddr) < 0) {
            std::cerr << "free allocAlignMemFdOutput error" << std::endl;
            std::abort();
        }
    }
    std::cout << "-------------------------~retinaface-------------------------------- \n";
    close(share_memory);
    close(mem_map);
}
