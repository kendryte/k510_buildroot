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
#include <fstream>
#include <assert.h>
#include <string.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include"depth_estimated.h"
#include"constant.h"
#include"rasterize.h"

float *bfm_u = nullptr;
float *bfm_w = nullptr;
int *bfm_tri = nullptr;
float *ncc_code = nullptr;

void constant_init(const char* bin_path)
{
    bfm_u = new float[3 * bfm_u_dim];
    bfm_w = new float[3 * bfm_u_dim * bfm_w_dim3];
    bfm_tri = new int[bfm_tri_dim * 3];
    ncc_code = new float[3 * bfm_u_dim];
    std::ifstream constant_f(bin_path, std::ios::binary);
    constant_f.read((char *)bfm_u, sizeof(float) * (3 * bfm_u_dim));
    constant_f.read((char *)bfm_w, sizeof(float) * (3 * bfm_u_dim * bfm_w_dim3));
    constant_f.read((char *)bfm_tri, sizeof(int) * (bfm_tri_dim * 3));
    constant_f.read((char *)ncc_code, sizeof(float) * (3 * bfm_u_dim));
    constant_f.close();
}

void constant_destroy()
{
    if (bfm_u != nullptr)
        delete[] bfm_u;
    if (bfm_w != nullptr)
        delete[] bfm_w;
    if (bfm_tri != nullptr)
        delete[] bfm_tri;
    if (ncc_code != nullptr)
        delete[] ncc_code;
}

void param_normalized(vector<float *> param_lst)
{
    for (auto &param : param_lst)
    {
        for (int param_index = 0; param_index < tddfa_output_size; ++param_index)
        {
            param[param_index] = param[param_index] * param_std[param_index] + param_mean[param_index];
        }
    }
}

void _similar_transform(float *pts3d, double *roi_box)
{
    double scale_x = (roi_box[2] - roi_box[0]) / tddfa_input_size;
    double scale_y = (roi_box[3] - roi_box[1]) / tddfa_input_size;
    double s = (scale_x + scale_y) / 2;

    for (int row_index = 0; row_index < 3; ++row_index)
    {
        if (row_index == 0)
        {
            int index = 0;
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                index = row_index * bfm_u_dim + col_index;
                pts3d[index] -= 1;
                pts3d[index] = pts3d[index] * scale_x + roi_box[0];
            }
        }
        else if (row_index == 2)
        {
            int index = 0;
            float min_dim2 = 0;
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                index = row_index * bfm_u_dim + col_index;
                pts3d[index] -= 1;
                pts3d[index] *= s;
                if (col_index == 0)
                    min_dim2 = pts3d[index];
                else
                {
                    if (pts3d[index] < min_dim2)
                        min_dim2 = pts3d[index];
                }
            }
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                pts3d[row_index * bfm_u_dim + col_index] -= min_dim2;
            }
        }
        else
        {
            int index = 0;
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                index = row_index * bfm_u_dim + col_index;
                pts3d[index] = tddfa_input_size - pts3d[index];
                pts3d[index] = pts3d[index] * scale_y + roi_box[1];
            }
        }
    }
}

void recon_vers(vector<float *> ver_lst, vector<float *> param_lst, vector<double *> roi_box_lst)
{
    for (int index = 0; index < param_lst.size(); ++index)
    {
        float *param = param_lst[index];
        float R[3][3] = {0};
        float offset[3] = {0};
        for (int trans_index = 0; trans_index < bfm_trans_dim; ++trans_index)
        {
            if ((trans_index + 1) % 4 == 0)
            {
                offset[trans_index / 4] = param[trans_index];
                continue;
            }
            R[trans_index / 4][trans_index % 4] = param[trans_index];
        }

        float *w_matmul_alpha_add_u = new float[3 * bfm_u_dim];
        for (int row_index = 0; row_index < 3; ++row_index)
        {
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                int index = row_index * bfm_u_dim + col_index;
                int start_w = index * (bfm_shape_dim + bfm_exp_dim);
                int end_w = start_w + bfm_shape_dim + bfm_exp_dim;
                float sum = 0;
                for (int w_index = start_w, alpha_index = bfm_trans_dim; w_index < end_w; ++w_index, ++alpha_index)
                {
                    sum += bfm_w[w_index] * param[alpha_index];
                }
                w_matmul_alpha_add_u[index] = sum + bfm_u[index];
            }
        }

        for (int row_index = 0; row_index < 3; ++row_index)
        {
            int tmp_index = 0;
            for (int col_index = 0; col_index < bfm_u_dim; ++col_index)
            {
                tmp_index = row_index * bfm_u_dim + col_index;
                float sum = 0;
                for (int r_index = 0; r_index < 3; ++r_index)
                {
                    sum += R[row_index][r_index] * w_matmul_alpha_add_u[r_index * bfm_u_dim + col_index];
                }
                ver_lst[index][tmp_index] = sum + offset[row_index];
            }
        }
        delete[] w_matmul_alpha_add_u;
        _similar_transform(ver_lst[index], roi_box_lst[index]);
    }
}

void rasterize(uint8_t *bg, float *vertices, float *colors, int height, int width, int channel, float alpha , bool reverse)
{
    if (bg == nullptr)
    {
        assert(height != 0 && width != 0 && channel != 0);
        bg = new uint8_t[height * width * channel];
    }
    float *buffer = new float[height * width];
    for (int buf_index = 0; buf_index < height * width; ++buf_index)
        buffer[buf_index] = -1e8;

    _rasterize(bg, vertices, bfm_tri, colors, buffer, bfm_tri_dim, height, width, channel, alpha, reverse);

    delete[] buffer;
}

void get_depth(uint8_t *img, float* ver, float *z, int height, int width, int channel, vector<float *> ver_lst)
{
    uint8_t *overlap = img;

    for (auto ver_ : ver_lst)
    {
        int row = 0, col = 0;
        int start_ver = 2 * bfm_u_dim, end_ver = 3 * bfm_u_dim;
        float z_min = 0, z_max = 0;

        if (start_ver < end_ver)
            z_min = z_max = ver_[start_ver];
		for (int vi = 0; vi < end_ver; ++vi)
		{
			row = vi / bfm_u_dim;
			col = vi % bfm_u_dim;
			ver[col * 3 + row] = ver_[vi];
			if (vi > start_ver)
			{
				if (ver_[vi] > z_max)
					z_max = ver_[vi];
				else if (ver_[vi] < z_min)
					z_min = ver_[vi];
			}
		}

        float tmp_z = 0;
        for (int ver_index = start_ver; ver_index < end_ver; ++ver_index)
        {
            tmp_z = (ver_[ver_index] - z_min) / (z_max - z_min);
            for (int z_index = (ver_index - start_ver) * 3; z_index < (ver_index - start_ver + 1) * 3; ++z_index)
                z[z_index] = tmp_z;
        }

        rasterize(overlap, ver, z, height, width, channel);
    }
}

void get_pncc(uint8_t *img, float* ver, int height, int width, int channel, vector<float *> ver_lst)
{
    uint8_t *overlap = img;
    //rendering pncc
    for (auto ver_ : ver_lst)
    {
        //transpose
        int row = 0, col = 0, end_ver = 3 * bfm_u_dim;

        for (int ver_index = 0; ver_index < end_ver; ++ver_index)
        {
            row = ver_index / bfm_u_dim;
            col = ver_index % bfm_u_dim;
            ver[col * 3 + row] = ver_[ver_index];
        }
        rasterize(overlap, ver, ncc_code, height, width, channel); //m x 3
    }
}