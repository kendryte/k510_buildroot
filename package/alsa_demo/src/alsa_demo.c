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

/*!
 *****************************************************************************
 * \file    alsa_demo.c
 * \author  Jiangxb
 * \version 1.0
 * \date    2021/11/03
 * \brief   基于alsalib的测试程序，实现录音播放功能,
 *			捕获的音频数据为原始的数据，即没有任何头信息的。可以Autacity软件打开分析
 *			文件->导入->原始数据
 *
 * change history:
 *  <date>      | <version> | <author>   | <discription>
 *----------------------------------------------------------------------------
 * 2021/11/03   | 1.0       | Jiangxb     | creat file
 *----------------------------------------------------------------------------
 *
 *****************************************************************************
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <signal.h>
 
#define TEST_FORMAT SND_PCM_FORMAT_S16_LE  //pcm.h:SND_PCM_FORMAT_U32_LE
#define TEST_CHANNEL_SET   2  //K510只有I2S接口，支持2声道，如果需要单声道，可以从用户层对双声道做分离，或复制单声道为双声道。
#define TEST_RATE_SET 44100   //音频采样率,常用的采样频率: 44100Hz 、16000HZ、8000HZ、48000HZ、22050HZ
#define TEST_DEV "hw:0"		//K510默认只有一个声卡设备，为0设备
#define TEST_FILE "capture.pcm"

FILE *pcm_data_file=NULL;
int run_flag=0;

void exit_sighandler(int sig)
{
	run_flag=1;
}

snd_pcm_t *open_sound_dev(snd_pcm_stream_t type)
{
	int err;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *hw_params;
	unsigned int rate = TEST_RATE_SET;

	if ((err = snd_pcm_open (&handle, TEST_DEV, type, 0)) < 0) {
		return NULL;
	}

	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
			 snd_strerror (err));
		return NULL;
	}
			 
	if ((err = snd_pcm_hw_params_any (handle, hw_params)) < 0) {
		fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	if ((err = snd_pcm_hw_params_set_access (handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf (stderr, "cannot set access type (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	if ((err = snd_pcm_hw_params_set_format (handle, hw_params, TEST_FORMAT)) < 0) {
		fprintf (stderr, "cannot set sample format (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	if ((err = snd_pcm_hw_params_set_rate_near (handle, hw_params, &rate, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	if ((err = snd_pcm_hw_params_set_channels (handle, hw_params, TEST_CHANNEL_SET)) < 0) {
		fprintf (stderr, "cannot set channel count (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	if ((err = snd_pcm_hw_params (handle, hw_params)) < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
			 snd_strerror (err));
		return NULL;
	}

	snd_pcm_hw_params_free (hw_params);

	return handle;
}

void close_sound_dev(snd_pcm_t *handle)
{
	snd_pcm_close (handle);
}

snd_pcm_t *open_playback(void)
{
    return open_sound_dev(SND_PCM_STREAM_PLAYBACK);
}

snd_pcm_t *open_capture(void)
{
    return open_sound_dev(SND_PCM_STREAM_CAPTURE);
}

int main(int argc, char *argv[])
{
	int i;
	int err;
	char *buffer;
	int buffer_frames = TEST_RATE_SET;//buffer大小为采集1s钟的数据量
	unsigned int rate = TEST_RATE_SET;
	snd_pcm_t *capture_handle;
	snd_pcm_t *playback_handle;
	snd_pcm_hw_params_t *hw_params;

	if(argc!=2)
	{
		printf("test pcm capture:./alsa_demo c \n");
		printf("test pcm playback:./alsa_demo p \n");
		exit(1);
	}
	signal(2,exit_sighandler);
	int frame_byte=snd_pcm_format_width(TEST_FORMAT)/8;

	buffer=(char *)malloc(buffer_frames*frame_byte*TEST_CHANNEL_SET);

	if(!strncmp(argv[1], "c", 1))
	{
		if((pcm_data_file = fopen(TEST_FILE, "wb")) == NULL)
		{
			printf("open %s error.\n", TEST_FILE);
			exit(1);
		}

		capture_handle = open_capture();
		if (!capture_handle)
		{
			fprintf (stderr, "cannot open for capture\n");
			return -1;
		}

		if ((err = snd_pcm_prepare (capture_handle)) < 0) {
			fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
				snd_strerror (err));
			return -1;
		}

		printf("capture start...\n");
		int actual;
		while(1) 
		{
			if((err=snd_pcm_readi(capture_handle,buffer,buffer_frames))!=buffer_frames) 
			{
				printf("pcm readi(%s)\n",snd_strerror(err));
				exit(1);
			}

			fwrite(buffer,(buffer_frames*TEST_CHANNEL_SET), frame_byte, pcm_data_file);	
			if(run_flag)
			{
				printf("capture stop.\n");
				break;
			}
		}
		snd_pcm_drain(capture_handle);
		snd_pcm_close(capture_handle);
		fclose(pcm_data_file);
	}
	else if(!strncmp(argv[1], "p", 1))
	{
		run_flag = 0;
		if((pcm_data_file = fopen(TEST_FILE, "rb")) == NULL)
		{
			printf("open %s error.\n", TEST_FILE);
			exit(1);
		}

		playback_handle = open_playback();
		if (!playback_handle)
		{
			fprintf (stderr, "cannot open for playback\n");
			return -1;
		}

		if ((err = snd_pcm_prepare (playback_handle)) < 0) {
			fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
				snd_strerror (err));
			return -1;
		}

		printf("playback start...\n");
		int read_cnt;
		while(1) 
		{
			read_cnt=fread(buffer,1,frame_byte*(buffer_frames*TEST_CHANNEL_SET), pcm_data_file);
			if(read_cnt<=0) break;

			if((err=snd_pcm_writei(playback_handle,buffer,buffer_frames))!=buffer_frames) 
			{
				printf("pcm writei(%s)\n",snd_strerror(err));
				exit(1);
			}
			if(run_flag)
			{
				break;
			}
		}
		printf("playback stop.\n");
		
		snd_pcm_drain(playback_handle);
		snd_pcm_close(playback_handle);
		
		fclose(pcm_data_file);
		free(buffer);
	}
	else
	{
		printf("test pcm capture:./alsa_demo c \n");
		printf("test pcm playback:./alsa_demo p \n");
	}
	return 0;
}
 