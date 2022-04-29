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
#include "openpose.h"

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

void openpose::prepare_memory()
{
    input_size = ((net_height * net_width * (INPUT_CHANNELS + 1) + 4095) & (~4095));
    output_size[0] = net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0 * 4;
    output_size[1] = net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_1 * 4;
    output_size[2] = net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0 * 4;
    output_size[3] = net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0 * 4;
    output_all_size = 0;
    for(uint32_t i=0; i<4; i++)
    {
        output_all_size += output_size[i];
    }
    output_all_size = ((output_all_size + 4095) & (~4095));

    allocAlignMemOpOutput.size = output_all_size;
    allocAlignMemOpOutput.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMemOpOutput.phyAddr = 0;    

    if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemOpOutput) < 0) 
    {
        std::cerr << "alloc allocAlignMemOpOutput error" << std::endl;
        std::abort();
    }

    virtual_addr_output = (char *)mmap(NULL, allocAlignMemOpOutput.size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemOpOutput.phyAddr);
    if(virtual_addr_output == MAP_FAILED) 
    {
        std::cerr << "map allocAlignMemOpOutput error" << std::endl;
        std::abort();
    }

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        allocAlignMemOpInput[i].size = input_size;
        allocAlignMemOpInput[i].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMemOpInput[i].phyAddr = 0;

        if(ioctl(share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMemOpInput[i]) < 0) 
        {
            std::cerr << "alloc allocAlignMemOpInput error" << std::endl;
            std::abort();
        }
        virtual_addr_input[i] = (char *)mmap(NULL, allocAlignMemOpInput[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_map, allocAlignMemOpInput[i].phyAddr);
        if(virtual_addr_input[i] == MAP_FAILED) 
        {
            std::cerr << "map allocAlignMemOpInput error" << std::endl;
            std::abort();
        }
    }

    virtualAddrOpOutput[0] = virtual_addr_output;
    output_pa_addr[0] = allocAlignMemOpOutput.phyAddr;

    output_pa_addr[1] = output_pa_addr[0] + output_size[0];
    output_pa_addr[2] = output_pa_addr[1] + output_size[1];
    output_pa_addr[3] = output_pa_addr[2] + output_size[2];

    virtualAddrOpOutput[1] = virtualAddrOpOutput[0] + output_size[0];
    virtualAddrOpOutput[2] = virtualAddrOpOutput[1] + output_size[1];
    virtualAddrOpOutput[3] = virtualAddrOpOutput[2] + output_size[2];
}

void openpose::set_input(uint32_t index)
{
    auto in_shape = interp_op.input_shape(0);
    auto input_tensor = host_runtime_tensor::create(dt_uint8, in_shape,
        { (gsl::byte *)virtual_addr_input[index], net_height * net_width * INPUT_CHANNELS},
        false, hrt::pool_shared, allocAlignMemOpInput[index].phyAddr)
                            .expect("cannot create input tensor");
    interp_op.input_tensor(0, input_tensor).expect("cannot set input tensor");
}

void openpose::set_output()
{
    for (size_t i = 0; i < interp_op.outputs_size(); i++)
    {
        auto out_shape = interp_op.output_shape(i);
        auto output_tensor = host_runtime_tensor::create(dt_float32, out_shape,
        { (gsl::byte *)virtualAddrOpOutput[i], output_size[i]},
        false, hrt::pool_shared, output_pa_addr[i])
                            .expect("cannot create output tensor");

        interp_op.output_tensor(i, output_tensor).expect("cannot set output tensor");
    }
}

void openpose::load_model(char *path)
{
    op_model = read_binary_file<unsigned char>(path);
    interp_op.load_model({ (const gsl::byte *)op_model.data(), op_model.size() }).expect("cannot load model.");
    std::cout << "============> interp_op.load_model finished!" << std::endl;
}

void openpose::run()
{
    interp_op.run().expect("error occurred in running model");
}

void openpose::get_output()
{
    output_0 = reinterpret_cast<float *>(virtualAddrOpOutput[0]);
    output_1 = reinterpret_cast<float *>(virtualAddrOpOutput[1]);
    output_2 = reinterpret_cast<float *>(virtualAddrOpOutput[2]);
    output_3 = reinterpret_cast<float *>(virtualAddrOpOutput[3]);
}

void openpose::post_process()
{
    memcpy(foutput, output_2, net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0 * sizeof(float));
    for(uint32_t i = 0; i < net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0; i++)
    {
        if(output_2[i] < output_3[i])
        {
            foutput[i] = 0.0;
        }
    }
}

openpose::openpose(int net_height, int net_width)
:net_height(net_height), net_width(net_width)
{
    foutput = new float[net_height / 2 * net_width / 2 * OUTPUT_CHANNELS_0];

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


openpose::~openpose()
{
    delete[] foutput;

    for(uint32_t i = 0; i < GNNE_BUFFERS_COUNT; i++) 
    {
        if(virtual_addr_input[i])
            munmap(virtual_addr_input[i], allocAlignMemOpInput[i].size);

        if(allocAlignMemOpInput[i].phyAddr != 0)
        {
            if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemOpInput[i].phyAddr) < 0) 
            {
                std::cerr << "free allocAlignMemOpInput error" << std::endl;
                std::abort();
            }
        }
    }
    if(virtual_addr_output)
        munmap(virtual_addr_output, allocAlignMemOpOutput.size);
        
    if(allocAlignMemOpOutput.phyAddr != 0)
    {
        if(ioctl(share_memory, SHARE_MEMORY_FREE, &allocAlignMemOpOutput.phyAddr) < 0) 
        {
            std::cerr << "free allocAlignMemOpOutput error" << std::endl;
            std::abort();
        }
    }
    close(share_memory);
    close(mem_map);
}
