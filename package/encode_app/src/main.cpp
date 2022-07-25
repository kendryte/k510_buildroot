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

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <linux/videodev2.h>
#include <semaphore.h>
#include<vector>
using namespace std;
#include "cJSON.h"

#include "types.h"
#include "enc_interface.h"
#include "isp_video.h"
#include "VideoStreamer.hh"
#include "video_app.h"
#include "media_ctl.h"
#include "IRtspServer.h"
#include "alsa/asoundlib.h"
#include "G711Codec.h"

//#define ISP_OUTPUT_DUMP 1
#define TEST_ISP        1

#define ISP_ADDR_BUFFER_CNT  22
#define V4L2_INVALID_INDEX 0xffff
#define V4L2_REPEAT_FLAG 0x80000000

#define SHARE_MEMORY_DEV "/dev/k510-share-memory"
#define DEV_NAME_DDR "/dev/mem"
#define DEV_NAME_ISP "/dev/test-isp"
#define DEV_NAME_V4L2 "/dev/video3"
#define REAL_CONF_FILENAME "video_real.conf"
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* align 4k for mmap */
#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)

#define ISP_CMD_ISP_RESET           _IOWR('q', 20, unsigned long)

#define DDR_CTRL_REG_BASE 0x198000000
#define NOC_QOS_REG_BASE  0x199900000
#define MAILBOX_REG_BASE  0x1970E0000

#define ALSA_BUFFER_SIZE_MAX (131072) //(0x20000)
#define MIN(a,b) ((a) > (b) ? (b) : (a))

static int received_sigterm = 0;
typedef std::vector<EncROICfg>    ENC_ROI_CFG_ARRAY;


struct share_memory_alloc_align_args {
    unsigned int size;
    unsigned int alignment;
    unsigned int phyAddr;
};

typedef struct
{
    void *vaddr;
    long paddr;
    unsigned int length;
}V4L2_BUF;

typedef struct
{
  int addr;
}V4L2_REV;

typedef struct
{
  int fd_isp;
  int fd_ddr;
  int fd_share_memory;
  int *fd_v4l2;
  int *isp_rp;
  int *isp_wp;
  long (*isp_addr)[ISP_ADDR_BUFFER_CNT];
  int *isp_pic_cnt;
  V4L2_BUF **v4l2_buf;
  V4L2_REV **v4l2_rev;
  sem_t *    pSemGetData;
  int *v4l2_rp;
  int *v4l2_wp;
  int *v4l2_pic_cnt;
  int *total_out_size;
  int *rtsp_buf_wp;
  void **isp_buf_vaddr;
  unsigned int *isp_buf_paddr;
  unsigned int *isp_buf_size;
  int *enable_isp;
  int *enable_rtsp;
  int *enable_v4l2;
  long *yuv_phyAddr;
  void **yuv_vAddr;
  unsigned int *yuv_size;
  unsigned long int *start_time;
  void **out_buffer;
  unsigned int *stream_size;
  unsigned int *out_pic;
  unsigned char *framerate;
  long *stream_phyAddr;
  FILE **in_file;
  FILE **out_file;
  EncoderHandle **hEnc;
  unsigned int reg_QoS_ctrl0;
  unsigned int reg_QoS_ctrl1;
  unsigned int reg_QoS_ctrl2;
  unsigned int reg_h264_bw;
  unsigned int reg_h264_mode;
  unsigned int reg_isp_pri;
  unsigned int reg_isp_bw;
  unsigned int reg_isp_mode;
  unsigned int reg_ddr_cli;

  long *shared_phyAddr;
  void **shared_vAddr;
  unsigned int *shared_size;
  unsigned int *exp;
  unsigned int *agc;
  int *stride;
  int *width;
  int *height;
  int *input_frames;
  pthread_t *isp_thread;
  pthread_t *v4l2_thread;
  pthread_t *encode_thread;
  int start;
  int end_encode;
  char *conf_filename;
  struct video_info dev_info[2];
  IRtspServerEX **pRtspServer;
  char **roi_filename;
  ENC_ROI_CFG_ARRAY*   aryEncRoiCfg;
  int*                 nLTRFreq;//Specifies the Long Term reference picture refresh frequency in number of frames
  EncSettings *Cfg;
  int *ch_en;
  char **infilename;
  char **outfilename;
  int thread_rtsp_en;
  int thread_isp_en;
  int thread_v4l2_en;
  char **dev_name;
  int *output_frames;
  int *encoding;
  int *ch;
  int ch_cnt;
  int isp_enabled;
  int v4l2_enabled;
  uint32_t *repeat;
  uint32_t *repeat_en;
  uint32_t *drop;
  uint32_t *drop_en;
  uint32_t *framerate_mod;
  int *set_ae;
  unsigned char *out_framerate;
  int video_enabled;
  int ae_enable;

  /* audio */
  snd_pcm_t *pcmp;
  int audio_ch_cnt;
  int audio_sample_rate;
  snd_pcm_uframes_t period_size;
  snd_pcm_format_t audio_format;
  int audioEncType;
  char *audio_buffer;
  int audio_frame_size;
  int audio_size;
  char *audio_device;
  int audio_processing;
  int audio_enabled;
  pthread_t audio_thread;
}MainContext;

MainContext Ctx;
MainContext *pCtx=&Ctx;

static unsigned int alloc_memory(int fd_share_memory, unsigned int size);
static int get_yuv(MainContext *pCtx, char *infilename, int channel);
static void write_output(MainContext *pCtx, FILE *out_file, EncOutputStream *src);
static unsigned long int get_time();
static void *isp_output(void *arg);
static void enqueue_buf(unsigned char index, int channel);
static void *v4l2_output(void *arg);
static void *encode_ch(void *arg);
int free_context(void *arg);
static void endof_encode();
static void exit_handler(int sig);
static void set_QoS();
#if TEST_ISP
static int init_isp();
#endif
int init_v4l2();
int init_audio(int nSampleRate);
static void *audio_process(void *arg);
int parse_conf();
int alloc_context(void *arg);
int parse_cmd(int argc, char *argv[]);

static unsigned int alloc_memory(int fd_share_memory, unsigned int size)
{
  struct share_memory_alloc_align_args  allocAlignMem;
  
  allocAlignMem.size = (size + 0xfff) & (~0xfff);
  allocAlignMem.alignment = MEMORY_TEST_BLOCK_ALIGN;
  allocAlignMem.phyAddr = 0;

  if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem) < 0)
  {
    printf("alloc_memory Error!\n");
    return -1;
  }
  //printf("%s>phy_addr 0x%x, size %d\n", __FUNCTION__, allocAlignMem.phyAddr, allocAlignMem.size);
  
  return allocAlignMem.phyAddr;
}

static int get_yuv(MainContext *pCtx, char *infilename, int channel)
{
  FILE *fp;
  char ch;
  unsigned int cnt = 0,i = 0, j;
  unsigned int filesize, size;
  void* map_src_pic;
  unsigned char *pic_vaddr;
  errno = 0;
  unsigned int phyAddr;

  if( (fp=fopen(infilename,"r+b")) == NULL ){
      printf("Cannot open yuv file!\n");
      return -1;
  }

  fseek(fp,0L,SEEK_END);
  filesize = ftell(fp);

  fseek(fp,0,SEEK_SET);

  size = pCtx->width[channel]*pCtx->height[channel]*3/2;

  if(filesize >= pCtx->input_frames[channel]*size)
    size = pCtx->input_frames[channel]*pCtx->stride[channel]*pCtx->height[channel]*3/2;
  else
    size = filesize;
    
  size = (size + 0xfff) & (~0xfff);

  phyAddr = alloc_memory(pCtx->fd_share_memory, size);
  if(phyAddr == -1)
  {
    printf("Not enough memory for input data.\n");
    return -1;
  }
 
  map_src_pic = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, (uint64_t)phyAddr|0x100000000);

  pic_vaddr = (unsigned char *)map_src_pic;  

  for(j=0; j<pCtx->input_frames[channel]; j++)
  {
    //read Y
    for(i=0; i<pCtx->height[channel]; i++)
    {
      fread(pic_vaddr, 1, pCtx->width[channel], fp);
      pic_vaddr += pCtx->stride[channel];
    }
    //read UV
    for(i=0; i<pCtx->height[channel]/2; i++)
    {
      fread(pic_vaddr, 1, pCtx->width[channel], fp);
      pic_vaddr += pCtx->stride[channel];
    }
  }

  fclose(fp);

  pCtx->yuv_phyAddr[channel] = phyAddr;
  pCtx->yuv_vAddr[channel] = map_src_pic;
  pCtx->yuv_size[channel] = size;
  printf("%s>yuv paddr = 0x%x, vaddr 0x%x, yuv_size %d, filesize %d\n", __FUNCTION__, pCtx->yuv_phyAddr, pCtx->yuv_vAddr, pCtx->yuv_size, filesize);
  return 0;
}

static void write_output(MainContext *pCtx, FILE *out_file, EncOutputStream *src)
{  
  if(out_file)
  {
    fwrite(src->bufAddr, 1, src->bufSize, out_file);
  }
  else
    printf("write nothing\n");
}

static unsigned long int get_time()
{
  struct timespec time;
        
  clock_gettime(CLOCK_REALTIME, &time);
  
  return time.tv_sec * 1000LL * 1000LL * 1000LL + time.tv_nsec;
}

#if TEST_ISP
static void *isp_output(void *arg)
{
  int ret = -1;
  struct pollfd isp_fds;
  struct ds_data isp;
  int channel = *(int*)arg;
  // printf("%s>channel:%d\n",__FUNCTION__, channel);
  unsigned long int time = 0;
  unsigned long int start_time = 0;
  unsigned long int check_time = 0;
  
  isp_fds.fd  = pCtx->fd_isp;
  isp_fds.events = POLLIN;

  pCtx->isp_pic_cnt[channel] = 1;

  while(pCtx->start)
  {
    poll(&isp_fds, 1, -1);

    if(pCtx->start == 0) break;
    
    if(isp_fds.events==POLLIN)
    {
      ret = read(pCtx->fd_isp, &isp, sizeof(isp));
      if(ret < 0)
      {
          printf("read fd error \n");
      }  
      
      if(time > 0)
      {
        //printf("isp out time interval %.4f ms\n", (get_time()-time)/1000000.0);
      }
      time = get_time();
      
      if(start_time == 0)
      {
        start_time = time;
      }
      
      if(check_time == 0)
      {
        check_time = time;
      }     
      
      if(pCtx->isp_addr[channel][pCtx->isp_wp[channel]] != 0)
      {
          printf("isp buffer overflow\n");
      }
      else
      {
        int drop=0, repeat=0;
        
        if(time - check_time >= 1000000000)
        {
          unsigned long int cap_time, elasp_time, delta=0, duration;
          
          check_time = 0;

          duration = 1000000.0/pCtx->framerate[channel];
          elasp_time = (time - start_time)/1000.0;
          cap_time = pCtx->isp_pic_cnt[channel]*duration;
          if(cap_time < elasp_time)
          {
            delta = elasp_time - cap_time;
            if(delta > duration/2)
            {
              repeat = 1;
              //printf("repeat: cnt %d, elasp_time %.4f ms, cap_time %.4f ms\n", pCtx->isp_pic_cnt, elasp_time/1000.0, cap_time/1000.0);
            }
          }
          else
          {
            delta = cap_time - elasp_time;
            if(delta > duration/2)
            {
              drop = 1;
              //printf("drop: cnt %d, elasp_time %.4f ms, cap_time %.4f ms\n", pCtx->isp_pic_cnt, elasp_time/1000.0, cap_time/1000.0);
            }
          }
        }
        
        if(drop == 0)
        {
          pCtx->isp_addr[channel][pCtx->isp_wp[channel]] = isp.addr;
          pCtx->isp_wp[channel]++;
          pCtx->isp_wp[channel] %= ISP_ADDR_BUFFER_CNT;
          pCtx->isp_pic_cnt[channel]++;
        }
        
        if(repeat == 1)
        {
          pCtx->isp_addr[channel][pCtx->isp_wp[channel]] = isp.addr;
          pCtx->isp_wp[channel]++;
          pCtx->isp_wp[channel] %= ISP_ADDR_BUFFER_CNT;
          pCtx->isp_pic_cnt[channel]++;
        }
        //printf("isp output buffer 0x%x, isp_irq_id %d\n", isp.addr, isp.isp_irq_id);
      }
    }
  } 
}
#endif

static void enqueue_buf(unsigned char index, int channel)
{
    struct v4l2_buffer buf = { 0 };

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_USERPTR;
    buf.index = index;
    buf.length = pCtx->v4l2_buf[channel][index].length;
    buf.m.userptr = (unsigned long)pCtx->v4l2_buf[channel][index].vaddr;

    if(ioctl(pCtx->fd_v4l2[channel], VIDIOC_QBUF, &buf) < 0)
    {
        printf("ioctl(VIDIOC_QBUF) fail: index %d, channel: %d\n", index, channel);
    }
}

static void set_ae(char* dev_name, int ae_enable)
{
  if((dev_name[10] >= '2') && (dev_name[10] <= '5') && (ae_enable & 0x1))
  {
    mediactl_set_ae(ISP_F2K_PIPELINE);
  }
  else if((dev_name[10] >= '6') && (dev_name[10] <= '9') && (ae_enable & 0x1))
  {
    mediactl_set_ae(ISP_R2K_PIPELINE);
  }
  return;
}

static void *v4l2_output(void *arg)
{
  printf("%s\n", __FUNCTION__);
  int channel = *(int*)arg;
  // printf("%s>channel: %d\n", __FUNCTION__, channel);
  unsigned long int time = 0;
  unsigned long int start_time = 0;
  unsigned long int check_time = 0;

  int iRet = -1;
  struct pollfd tFds[1];
 
  while(pCtx->start)
  {
	 	/* poll */
  	tFds[0].fd = pCtx->fd_v4l2[channel];
  	tFds[0].events = POLLIN;
  	iRet = poll(tFds, 1, /*-1*/3000);//3000ms
  	if (iRet <= 0)
    {
      printf("poll error!\n");
      continue;
    }
  
    struct v4l2_buffer buf;
    int res;

    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_USERPTR;
        
    res = ioctl(pCtx->fd_v4l2[channel], VIDIOC_DQBUF, &buf);

    set_ae(pCtx->dev_name[channel], pCtx->ae_enable);
    
    if (res < 0 || errno == EINTR)
    {
      continue;
    }
    else  
    {
      time = get_time();
      
      if(start_time == 0)
      {
        start_time = time;
      }
      
      if(check_time == 0)
      {
        check_time = time;
      }   
      
      if(pCtx->v4l2_rev[channel][pCtx->v4l2_wp[channel]].addr != V4L2_INVALID_INDEX)
      {
          printf("v4l2 buffer overflow\n");
          enqueue_buf(buf.index, channel);
      }
      else if(time - start_time < 100000000)
      {
          if(pCtx->v4l2_pic_cnt[channel] == 0)
          {
            enqueue_buf(buf.index, channel);
          }
      }
      else
      {
        int drop=0, repeat=0;
        
        if(time - check_time >= 1000000000)
        {
          unsigned long int cap_time, elasp_time, delta=0, duration;
          
          check_time = 0;

          duration = 1000000.0/pCtx->framerate[channel];
          elasp_time = (time - start_time)/1000.0;
          cap_time = pCtx->v4l2_pic_cnt[channel]*duration;
          if(cap_time < elasp_time)
          {
            delta = elasp_time - cap_time;
            if(delta > duration/2)
            {
              repeat = 1;
              //printf("repeat: cnt %d, elasp_time %.4f ms, cap_time %.4f ms\n", pCtx->isp_pic_cnt, elasp_time/1000.0, cap_time/1000.0);
            }
          }
          else
          {
            delta = cap_time - elasp_time;
            if(delta > duration/2)
            {
              drop = 1;
              enqueue_buf(buf.index, channel);
              //printf("drop: cnt %d, elasp_time %.4f ms, cap_time %.4f ms\n", pCtx->isp_pic_cnt, elasp_time/1000.0, cap_time/1000.0);
            }
          }
        }
        
        if(drop == 0)
        {
          if(repeat == 1)
          {
            pCtx->v4l2_rev[channel][pCtx->v4l2_wp[channel]].addr = buf.index|V4L2_REPEAT_FLAG;
          }
          else
          {
            pCtx->v4l2_rev[channel][pCtx->v4l2_wp[channel]].addr = buf.index;
          }
          pCtx->v4l2_wp[channel]++;
          pCtx->v4l2_wp[channel] %= ISP_ADDR_BUFFER_CNT;
          pCtx->v4l2_pic_cnt[channel]++;
          sem_post(&pCtx->pSemGetData[channel]);
        }
        
        if(repeat == 1)
        {
          pCtx->v4l2_rev[channel][pCtx->v4l2_wp[channel]].addr = buf.index;
          pCtx->v4l2_wp[channel]++;
          pCtx->v4l2_wp[channel] %= ISP_ADDR_BUFFER_CNT;
          pCtx->v4l2_pic_cnt[channel]++;
          sem_post(&pCtx->pSemGetData[channel]);
        }
      }
    }
  }
}

uint32_t queue_frame(int channel)
{
  if((pCtx->v4l2_rev[channel][pCtx->v4l2_rp[channel]].addr & V4L2_REPEAT_FLAG) == 0)
  {
    enqueue_buf(pCtx->v4l2_rev[channel][pCtx->v4l2_rp[channel]].addr, channel);
  }
  pCtx->v4l2_rev[channel][pCtx->v4l2_rp[channel]].addr = V4L2_INVALID_INDEX;
  pCtx->v4l2_rp[channel]++;
  pCtx->v4l2_rp[channel] %= ISP_ADDR_BUFFER_CNT; 

  return 0;
}

static void *encode_ch(void *arg)
{
  // printf("%s\n", __FUNCTION__);
  int channel = *(int*)arg;
  // printf("%s>channel: %d\n", __FUNCTION__, channel);
  EncInputFrame input;
  EncOutputStream output;
  int src_index = 0;

  int stride = ((pCtx->Cfg[channel].width + 0x1F) & (~0x1F));
  int frame_size = stride*pCtx->Cfg[channel].height*3/2;

  uint32_t repeated = 0;
  int32_t droped = 0;
  uint32_t framerate_tail = 0;
  uint32_t framerate_tail_cnt = 0;
  uint32_t framerate_tail_gap = 0;
  uint32_t in_framecnt = 0;
  uint32_t out_framecnt = 0;
  int tail_flag = 0;
  int common_drop_flag = 0;

  if(pCtx->framerate_mod[channel])
  {
    if(pCtx->drop_en[channel])
    {
      framerate_tail = (pCtx->framerate[channel]/(pCtx->drop[channel]+1))%pCtx->out_framerate[channel];
      framerate_tail_cnt = framerate_tail;
      framerate_tail_gap = (pCtx->framerate[channel]/framerate_tail) - 1;
    }
    else if(pCtx->repeat_en[channel])
    {
      framerate_tail = pCtx->framerate_mod[channel];
      framerate_tail_cnt = framerate_tail;
      framerate_tail_gap = pCtx->framerate[channel]/framerate_tail;
    }
  }

  pCtx->encoding[channel] = 1;
  while(pCtx->start)
  {
    memset(&input, 0, sizeof(EncInputFrame));
    memset(&output, 0, sizeof(EncOutputStream));
    
    if(pCtx->yuv_phyAddr[channel])
    {
      //input from file
      input.width = pCtx->width[channel];
      input.height = pCtx->height[channel];
      input.stride = stride;
      input.data = (unsigned char *)pCtx->yuv_phyAddr[channel] + frame_size*(src_index % pCtx->input_frames[channel]);
      //printf("%s>src_index %d, addr 0x%x\n", __FUNCTION__, src_index, input.data);
      src_index++;
    }

    if(pCtx->enable_isp[channel] == 1 && pCtx->isp_addr[channel][pCtx->isp_rp[channel]] != 0)
    {
      //input from isp
      input.width = pCtx->width[channel];
      input.height = pCtx->height[channel];
      input.stride = stride;
      input.data = (unsigned char *)pCtx->isp_addr[channel][pCtx->isp_rp[channel]];
      //printf("%s>input addr %p\n", __FUNCTION__, input.data);
    }

    if(pCtx->enable_v4l2[channel] == 1 && pCtx->v4l2_rev[channel][pCtx->v4l2_rp[channel]].addr != V4L2_INVALID_INDEX)
    {
      int index;
      
      //input from v4l2
      input.width = pCtx->width[channel];
      input.height = pCtx->height[channel];
      input.stride = stride;
      index = pCtx->v4l2_rev[channel][pCtx->v4l2_rp[channel]].addr & V4L2_INVALID_INDEX;
      input.data = (unsigned char *)pCtx->v4l2_buf[channel][index].paddr;
    }
    else
    {
      if (1 == pCtx->enable_v4l2[channel])
        sem_wait(&pCtx->pSemGetData[channel]);
    }

    if(input.data)
    {
      unsigned long int time;

      time = get_time();

      if(pCtx->out_pic[channel] == 0)
      {
        pCtx->start_time[channel] = time;
      }

      if(pCtx->drop_en[channel])
      {
        if(pCtx->framerate_mod[channel]) //with framerate tail
        {
          if((in_framecnt % (framerate_tail_gap+1) == 0)  || tail_flag)
          {
              tail_flag = 1;
              queue_frame(channel);
              in_framecnt++;
              framerate_tail_cnt--;
              if(in_framecnt >= pCtx->framerate[channel])
              {
                in_framecnt = 0;
                framerate_tail_cnt = framerate_tail;
              }
              droped++;
              if(droped >= pCtx->drop[channel] + 1)
              {
                droped = 0;
                tail_flag = 0;
              }
              continue;
          }
          else if((pCtx->drop[channel] && (in_framecnt % (pCtx->drop[channel]+1) == 0)) || common_drop_flag)
          {
            common_drop_flag = 1;
            queue_frame(channel);
            in_framecnt++;
            if(in_framecnt >= pCtx->framerate[channel])
            {
              in_framecnt = 0;
              framerate_tail_cnt = framerate_tail;
            }
            droped++;
            if(droped >= pCtx->drop[channel])
            {
              droped = 0;
              common_drop_flag = 0;
            }
            continue;
          }
          else
          {
            in_framecnt++;
            if(in_framecnt >= pCtx->framerate[channel])
            {
              in_framecnt = 0;
              framerate_tail_cnt = framerate_tail;
            }
            droped = 0;
          }
          
        }
        else //without framerate tail
        {
          if(droped < pCtx->drop[channel])
          {
            queue_frame(channel);
            droped++;
            continue;
          }
          else
          {
            droped = 0;
          }
        }
      }
      //set LTR
      if (pCtx->Cfg[channel].bEnableLTR && pCtx->nLTRFreq[channel] > 0)
      {
        if (0 == (pCtx->out_pic[channel] % pCtx->nLTRFreq[channel]))
        {
          VideoEncoder_SetLongTerm(pCtx->hEnc[channel]);
        }
        //next frame use ltr
        else if (0 == ((pCtx->out_pic[channel]-1) % pCtx->nLTRFreq[channel]))
        {
          VideoEncoder_UseLongTerm(pCtx->hEnc[channel]);
          //printf("==========VideoEncoder_UseLongTerm\n");
        }
      }
      
      VideoEncoder_EncodeOneFrame(pCtx->hEnc[channel], &input);

      VideoEncoder_GetStream(pCtx->hEnc[channel], &output);

      if (1 == pCtx->enable_rtsp[channel])
      {
         if (NULL != pCtx->pRtspServer[channel])
         {
           pCtx->pRtspServer[channel]->PushVideoData(output.bufAddr, output.bufSize,0);
         }
      }
	
      // printf("%s>bufAddr %p, bufSize %d\n", __FUNCTION__, output.bufAddr, output.bufSize);
	  	// printf("=========encode one frame take %d ms\n",(get_time()-time)/1000000LL);

      if(output.bufSize != 0)
      {
        if((get_time()-time)/1000000.0 >= (1000.0/pCtx->Cfg[channel].FrameRate))
        {
          printf("warning: channel[%d]-encode one frame %.4f ms\n", channel, (get_time()-time)/1000000.0);
        }

        if(pCtx->enable_isp[channel] == 1)
        {
          pCtx->isp_addr[channel][pCtx->isp_rp[channel]] = 0;
          pCtx->isp_rp[channel]++;
          pCtx->isp_rp[channel] %= ISP_ADDR_BUFFER_CNT;  
        }

        if(pCtx->enable_v4l2[channel] == 1)
        {
          if(pCtx->repeat_en[channel])
          {
            if(framerate_tail) // with framerate tail 
            {
              if(((in_framecnt % framerate_tail_gap) == 0) && framerate_tail_cnt)
              {

                if(repeated < pCtx->repeat[channel] + 1)
                {
                  repeated++;
                }
                else
                {
                  repeated = 0;
                  framerate_tail_cnt--;
                  queue_frame(channel);
                  in_framecnt++;
                  if(in_framecnt >= pCtx->framerate[channel])
                  {
                    in_framecnt = 0;
                    framerate_tail_cnt = framerate_tail;
                  }
                  
                }
              }
              else
              {
                if(repeated < pCtx->repeat[channel])
                {
                  repeated++;
                }
                else
                {
                  repeated = 0;
                  queue_frame(channel);
                  in_framecnt++;
                  if(in_framecnt >= pCtx->framerate[channel])
                  {
                    in_framecnt = 0;
                    framerate_tail_cnt = framerate_tail;
                  }
                }
              }
            }
            else //without framerate tail
            {
              if(repeated < pCtx->repeat[channel])
              {
                repeated++;
              }
              else
              {
                repeated = 0;
                queue_frame(channel);
                in_framecnt++;
                in_framecnt %= pCtx->framerate[channel];
              }
            }
          }
          else if(pCtx->drop_en[channel])
          {
            queue_frame(channel);
          }
          else if(!pCtx->drop_en[channel])// without repeate and drop
          {
            queue_frame(channel);
            in_framecnt++;
            in_framecnt %= pCtx->framerate[channel];
          }
        }

        //printf("%s>output addr %p, total_out_size = %d, encoder time = %.4f ms\n", __FUNCTION__, pCtx->pDst, pCtx->total_out_size, get_time()/1000000.0);
        // write_output(pCtx, pCtx->out_file[channel], &output, pCtx->out_buffer[channel]);
        if(pCtx->enable_rtsp[channel])
        {
          pCtx->total_out_size[channel] += output.bufSize;
        }
        else
        {
          pCtx->total_out_size[channel] += output.bufSize;
          write_output(pCtx, pCtx->out_file[channel], &output);
        }

        VideoEncoder_ReleaseStream(pCtx->hEnc[channel], &output);

        pCtx->out_pic[channel]++;   
        printf("\r  Encoding picture #%-6d - size %d", pCtx->out_pic[channel], pCtx->total_out_size[channel]);        
      }     
    }
    
    if(received_sigterm == 1)
       break;
    if(pCtx->output_frames[channel] > 0 && pCtx->out_pic[channel] >= pCtx->output_frames[channel])
       break;
  }
  pCtx->encoding[channel] = 0;
  
  return 0;
}

int free_context(void *arg)
{
  MainContext *pCtx = (MainContext *)arg;

  free(pCtx->fd_v4l2         );
  free(pCtx->isp_rp          );
  free(pCtx->isp_wp          );
  free(pCtx->isp_addr        );
  free(pCtx->isp_pic_cnt     );

  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    free(pCtx->v4l2_buf[i]);
  }
  free(pCtx->v4l2_buf        );

  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    free(pCtx->v4l2_rev[i]);
  }
  free(pCtx->v4l2_rev        );
  if(pCtx->pSemGetData != NULL)
  {
    free(pCtx->pSemGetData   );
    pCtx->pSemGetData = NULL;
  }

  free(pCtx->v4l2_rp         );
  free(pCtx->v4l2_wp         );
  free(pCtx->v4l2_pic_cnt    );
  free(pCtx->total_out_size  );
  free(pCtx->rtsp_buf_wp     );
  free(pCtx->isp_buf_vaddr   );
  free(pCtx->isp_buf_paddr   );
  free(pCtx->isp_buf_size    );
  free(pCtx->enable_isp      );
  free(pCtx->enable_rtsp     );
  free(pCtx->enable_v4l2     );
  free(pCtx->yuv_phyAddr     );
  free(pCtx->yuv_vAddr       );
  free(pCtx->yuv_size        );
  free(pCtx->start_time      );
  free(pCtx->out_buffer      );
  free(pCtx->stream_size     );
  free(pCtx->out_pic         );
  free(pCtx->framerate       );
  free(pCtx->stream_phyAddr  );
  free(pCtx->in_file         );
  free(pCtx->out_file        );
  free(pCtx->hEnc            );
  free(pCtx->shared_phyAddr  );
  free(pCtx->shared_vAddr    );
  free(pCtx->shared_size     );
  free(pCtx->exp             );
  free(pCtx->agc             );
  free(pCtx->stride          );
  free(pCtx->width           );
  free(pCtx->height          );
  free(pCtx->input_frames    );
  free(pCtx->isp_thread      );
  free(pCtx->v4l2_thread     );
  free(pCtx->encode_thread   );
  free(pCtx->pRtspServer     );
  free(pCtx->roi_filename    );
  free(pCtx->aryEncRoiCfg    );
  free(pCtx->nLTRFreq        );
  free(pCtx->Cfg             );
  free(pCtx->ch_en           );
  free(pCtx->infilename      );
  free(pCtx->outfilename     );
  free(pCtx->dev_name        );
  free(pCtx->output_frames   );
  free(pCtx->encoding        );
  free(pCtx->ch              );
  free(pCtx->repeat          );
  free(pCtx->repeat_en       );
  free(pCtx->drop            );
  free(pCtx->drop_en         );
  free(pCtx->out_framerate   );
  free(pCtx->set_ae   );

  return 0;
}

static void endof_encode()
{
  printf("endof_encode\n");
  // pCtx->start = 0;
  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    if(!pCtx->ch_en[i])
    {
      continue;
    }
    pCtx->encoding[i] = 0;
    printf("%d pictures encoded. Average FrameRate = %.4f Fps\n",
            pCtx->out_pic[i], (pCtx->out_pic[i] * 1000.0) / ((get_time()-pCtx->start_time[i])/1000000.0));
  
    printf("total_out_size %d\n", pCtx->total_out_size[i]);

    if(pCtx->out_file[i])
      fclose(pCtx->out_file[i]);
    if(pCtx->in_file[i])
      fclose(pCtx->in_file[i]);
    printf("fclose\n");

    VideoEncoder_Destroy(pCtx->hEnc[i]);
    printf("VideoEncoder_Destroy\n");
  }

#if TEST_ISP
  if(pCtx->isp_enabled)
  {  
    pthread_join(pCtx->isp_thread[0], NULL);
    struct isp_int_info intinfo;
    memset(&intinfo, 0, sizeof(isp_int_info));
    intinfo.ds1_en = 0;
    video_set_ispf2kint(&intinfo); 
    isp_video_exit();   
    if (ioctl(pCtx->fd_isp, ISP_CMD_ISP_RESET, 0) < 0)
    {
      printf("Call cmd ISP_CMD_ISP_RESET fail\n");
    }
  }
#endif
  
  for(int j = 0; j < pCtx->ch_cnt; j++)
  {
    if(pCtx->enable_v4l2[j])
    {
      enum v4l2_buf_type type;
      int i;

      pthread_join(pCtx->v4l2_thread[j], NULL);
      type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      ioctl(pCtx->fd_v4l2[j], VIDIOC_STREAMOFF, &type);
      
      for (int i=0; i<ISP_ADDR_BUFFER_CNT; i++)
      {
        munmap(pCtx->v4l2_buf[j][i].vaddr, pCtx->v4l2_buf[j][i].length);
        
        if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->v4l2_buf[j][i].paddr) < 0)
        {
          printf("%s>Error!\n", __FUNCTION__);
        }        
      }
      // mediactl_exit();
      close(pCtx->fd_v4l2[j]);    
    }

    if(pCtx->yuv_phyAddr[j] != 0)
    {
      munmap((void*)pCtx->yuv_vAddr[j], pCtx->yuv_size[j]);
      if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->yuv_phyAddr[j]) < 0)
      {
        printf("%s>Error!\n", __FUNCTION__);
      }
    } 
  }

  if (pCtx->pSemGetData != NULL)
  {
    for(int i = 0; i < pCtx->ch_cnt; i++)
    {
      sem_destroy(&pCtx->pSemGetData[i]);
    }
  }

  if(pCtx->video_enabled)
  {
    unsigned char *reg;
    
    reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, MAILBOX_REG_BASE);
  	*(volatile unsigned int *)(reg+0xf4) = pCtx->reg_QoS_ctrl0;
  	*(volatile unsigned int *)(reg+0xf8) = pCtx->reg_QoS_ctrl1;
  	*(volatile unsigned int *)(reg+0xfc) = pCtx->reg_QoS_ctrl2;
  	munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
  	reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, NOC_QOS_REG_BASE);
  	*(volatile unsigned int *)(reg+0x290) = pCtx->reg_h264_bw;
  	*(volatile unsigned int *)(reg+0x28c) = pCtx->reg_h264_mode;
  	*(volatile unsigned int *)(reg+0x388) = pCtx->reg_isp_pri;
  	*(volatile unsigned int *)(reg+0x38c) = pCtx->reg_isp_mode;
  	*(volatile unsigned int *)(reg+0x390) = pCtx->reg_isp_bw;
  	munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
  	reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, DDR_CTRL_REG_BASE);
  	*(volatile unsigned int *)(reg+0x504) = pCtx->reg_ddr_cli;
    munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
    printf("QoS restore\n");
  }

#if TEST_ISP
  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    if(pCtx->isp_buf_paddr[i] != 0)
    {
      munmap((void*)pCtx->isp_buf_vaddr[i], pCtx->isp_buf_size[i]);
      if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->isp_buf_paddr[i]) < 0)
      {
        printf("%s>Error!\n", __FUNCTION__);
      }
    }
  }
#endif

  free_context(pCtx);
  close(pCtx->fd_share_memory);
  close(pCtx->fd_ddr);
  if(pCtx->v4l2_enabled)
  {
    mediactl_exit();
  }
  printf("encode app exits successfully\n");
}

static void exit_handler(int sig)
{
  if(SIGINT == sig)
  {
    received_sigterm = 1;
  }
  return;
}

static void set_QoS()
{
  unsigned char *reg;

  //QoS setting for memory bandwidth
  reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, MAILBOX_REG_BASE);
  pCtx->reg_QoS_ctrl0 = *(volatile unsigned int *)(reg+0xf4);
  *(volatile unsigned int *)(reg+0xf4) = 0x00110000;
  printf("0x970E00f4: from 0x%08x to 0x%08x\n", pCtx->reg_QoS_ctrl0, *(volatile unsigned int *)(reg+0xf4));
  pCtx->reg_QoS_ctrl1 = *(volatile unsigned int *)(reg+0xf8);
  *(volatile unsigned int *)(reg+0xf8) = 0x00770000;
  printf("0x970E00f8: from 0x%08x to 0x%08x\n", pCtx->reg_QoS_ctrl1, *(volatile unsigned int *)(reg+0xf8));
  pCtx->reg_QoS_ctrl2 = *(volatile unsigned int *)(reg+0xfc);
  *(volatile unsigned int *)(reg+0xfc) = 0x0fffff00;
  printf("0x970E00fc: from 0x%08x to 0x%08x\n", pCtx->reg_QoS_ctrl2, *(volatile unsigned int *)(reg+0xfc));
  munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
  reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, NOC_QOS_REG_BASE);
  pCtx->reg_h264_bw = *(volatile unsigned int *)(reg+0x290);
  *(volatile unsigned int *)(reg+0x290) = 0x110;
  printf("0x99900290: from 0x%08x to 0x%08x\n", pCtx->reg_h264_bw, *(volatile unsigned int *)(reg+0x290));
  pCtx->reg_h264_mode = *(volatile unsigned int *)(reg+0x28c);
  *(volatile unsigned int *)(reg+0x28c) = 0;
  printf("0x9990028c: from 0x%08x to 0x%08x\n", pCtx->reg_h264_mode, *(volatile unsigned int *)(reg+0x28c));
  pCtx->reg_isp_mode = *(volatile unsigned int *)(reg+0x38c);
  *(volatile unsigned int *)(reg+0x38c) = 0;
  printf("0x9990038c: from 0x%08x to 0x%08x\n", pCtx->reg_isp_mode, *(volatile unsigned int *)(reg+0x38c));
  pCtx->reg_isp_pri = *(volatile unsigned int *)(reg+0x388);
  *(volatile unsigned int *)(reg+0x388) = 0x80000707;
  printf("0x99900388: from 0x%08x to 0x%08x\n", pCtx->reg_isp_pri, *(volatile unsigned int *)(reg+0x388));
  pCtx->reg_isp_bw = *(volatile unsigned int *)(reg+0x390);
  *(volatile unsigned int *)(reg+0x390) = 0x00000300;
  printf("0x99900388: from 0x%08x to 0x%08x\n", pCtx->reg_isp_bw, *(volatile unsigned int *)(reg+0x390));
  munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
  reg=(unsigned char * )mmap(NULL, MEMORY_TEST_BLOCK_ALIGN, PROT_READ | PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, DDR_CTRL_REG_BASE);
  pCtx->reg_ddr_cli = *(volatile unsigned int *)(reg+0x504);
  *(volatile unsigned int *)(reg+0x504) = 0x00010303;
  printf("0x98000504: from 0x%08x to 0x%08x\n", pCtx->reg_ddr_cli, *(volatile unsigned int *)(reg+0x504));
  munmap(reg, MEMORY_TEST_BLOCK_ALIGN);
}

#if TEST_ISP
static int init_isp()
{
    int src_index=0;
    
#ifdef ISP_OUTPUT_DUMP
    pCtx->yuv_size = frame_size*pCtx->input_frames;
    pCtx->yuv_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->yuv_size);  
    if(pCtx->yuv_phyAddr)
    {
      printf("Not enough memory for isp init.\n");
      return -1;
    }
    pCtx->yuv_vAddr = mmap(NULL, pCtx->yuv_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->yuv_phyAddr); 
    printf("%s>yuv_vAddr 0x%x, yuv_phyAddr 0x%x, yuv_size %d\n", __FUNCTION__, pCtx->yuv_vAddr, pCtx->yuv_phyAddr, pCtx->yuv_size);
#endif  

    DS1_INFO ds1_info;
    ds1_info.ds1_en = 1;
    ds1_info.ds1_width = pCtx->width[0];
    ds1_info.ds1_height = pCtx->height[0];
    ds1_info.stride = pCtx->stride[0];
    printf("ds1_info.stride = %d\n",ds1_info.stride);

    SENSOR_TYPE sensor_type;
    if(strcmp(TARGET_BOARD_TYPE_def, "crb") == 0)
    {
      printf("crb\n");
      sensor_type = IMX219_SENSOR;
    }
    else if(strcmp(TARGET_BOARD_TYPE_def, "evb") == 0)
    {
      printf("evb\n");
      sensor_type = JFX23S_SENSOR;
    }
    else
    {
      printf("board type error!\n");
    }
    LCD_TYPE lcd_type = HX8399;//HX8399;//ITI7807_LCD; //AML550_LCD; //BT1120_DISPALY

    pCtx->isp_buf_size[0] =(1920 *1080 *3 /2) * ISP_ADDR_BUFFER_CNT;// frame_size * 22;
    ds1_info.y_addr = alloc_memory(pCtx->fd_share_memory, pCtx->isp_buf_size[0]);
    if(ds1_info.y_addr == -1)
    {
      printf("Not enough memory for ds1 info.\n");
      return -1;
    }

    pCtx->isp_buf_vaddr[0] = mmap(NULL, pCtx->isp_buf_size[0], PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, ds1_info.y_addr);
    pCtx->isp_buf_paddr[0] = ds1_info.y_addr;
    printf("%s>isp_buf_paddr 0x%x, isp_buf_vaddr 0x%x, isp_buf_size %d\n", __FUNCTION__, ds1_info.y_addr, pCtx->isp_buf_vaddr, pCtx->isp_buf_size);

    pCtx->fd_isp = isp_video(&ds1_info, sensor_type, lcd_type);

    if(pCtx->exp[0] > 0)
    {
      printf("isp exp = %d\n", pCtx->exp[0]);
      video_set_ae_dgain_cfg(pCtx->exp[0]);
    }
    if(pCtx->agc[0] > 0)
    {
      printf("isp agc = %d\n", pCtx->agc[0]);
      video_set_ae_again_cfg(pCtx->agc[0]);
    }

    printf("%s>fd_isp: 0x%x\n", __FUNCTION__, pCtx->fd_isp);

    sleep(1);  //It seems ISP output is not stable at the beginning

    //create isp_output thread to get isp output
    pthread_create(&pCtx->isp_thread[0], NULL, isp_output, &pCtx->ch[0]);

#ifdef ISP_OUTPUT_DUMP
    unsigned char *pSrc = (unsigned char *)pCtx->yuv_vAddr[0];
    FILE *dump_file;
    
    while(src_index < pCtx->input_frames[0])
    {
      if(pCtx->isp_addr[0][pCtx->isp_rp][0] != 0)
      {
        unsigned char *pIsp;
        unsigned int offset;

        offset = (unsigned int)pCtx->isp_addr[0][pCtx->isp_rp[0]] - pCtx->isp_buf_paddr[0];
        pIsp = (unsigned char *)pCtx->isp_buf_vaddr[0] + offset;

        printf("%d: offset 0x%x, isp_addr 0x%x, Copy 0x%x to 0x%x\n", src_index, offset, pCtx->isp_addr[0][pCtx->isp_rp[0]], pIsp, pSrc);
        memcpy(pSrc, pIsp, frame_size);

        pSrc += frame_size;//1920 * 1080 * 3 / 2;//frame_size;     
        
        pCtx->isp_addr[0][pCtx->isp_rp][0] = 0;
        pCtx->isp_rp[0]++;
        pCtx->isp_rp[0] %= ISP_ADDR_BUFFER_CNT;
        src_index++;
      }
    }

    src_index = 0;
    
    pSrc = (unsigned char *)pCtx->yuv_vAddr[0];
    
    if((dump_file=fopen("isp_dump.yuv","w+b")) == NULL )
    {
      printf("Cannot open output file!\n");
    } 
    fwrite(pSrc, 1, pCtx->yuv_size[0], dump_file);
    fclose(dump_file);
    return 0;
#endif    
}
#endif

int init_v4l2()
{
    // struct mediactl_info m_info;
    struct v4l2_capability cap;
    enum v4l2_buf_type type;
    struct v4l2_requestbuffers req;
    struct v4l2_format fmt;
    int i;
    int f2k=0, r2k=0;

    for(int j = 0; j < pCtx->ch_cnt; j++)
    {
      for(i=0; i<ISP_ADDR_BUFFER_CNT; i++)
      {
        pCtx->v4l2_rev[j][i].addr  = V4L2_INVALID_INDEX;
      }
      
    }

    for(int i = 0; i < pCtx->ch_cnt; i++)
    {
      sem_init(&pCtx->pSemGetData[i],0,0);
    }

    if(mediactl_init(REAL_CONF_FILENAME, &(pCtx->dev_info[0])) < 0)
    {
        printf("mediactl_init error!\n");
        return -1;
    }

    for(int j = 0; j < pCtx->ch_cnt; j++)
    {
      if(!pCtx->enable_v4l2[j])
      {
        continue;
      }
    
      pCtx->fd_v4l2[j] = open(pCtx->dev_name[j], O_RDWR|O_NONBLOCK, 0);

      if(pCtx->fd_v4l2[j] < 0)
      {
        printf("open v4l2 fail\n");
        close(pCtx->fd_v4l2[j]);
        return -1;
      }

      if(ioctl(pCtx->fd_v4l2[j], VIDIOC_QUERYCAP, &cap) < 0) 
      {
        printf("ioctl(VIDIOC_QUERYCAP): fail\n");
        close(pCtx->fd_v4l2[j]);
        return 0;
      }

      if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
      {
        printf("Not a video capture device.\n");
        close(pCtx->fd_v4l2[j]);
        return 0;
      }

      if (!(cap.capabilities & V4L2_CAP_STREAMING))
      {
        printf("The device does not support the streaming I/O method.\n");
        close(pCtx->fd_v4l2[j]);
        return 0;
      }

      memset(&fmt, 0, sizeof(fmt));
      fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      fmt.fmt.pix.width = pCtx->width[j];
      fmt.fmt.pix.height = pCtx->height[j];
      fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
      fmt.fmt.pix.field = V4L2_FIELD_ANY;

      if (ioctl(pCtx->fd_v4l2[j], VIDIOC_S_FMT, &fmt) < 0)
      {
        printf("ioctl(VIDIOC_S_FMT): fail\n");
        close(pCtx->fd_v4l2[j]);
        return 0;
      }

      req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      req.count  = ISP_ADDR_BUFFER_CNT;
      req.memory = V4L2_MEMORY_USERPTR;

      if (ioctl(pCtx->fd_v4l2[j], VIDIOC_REQBUFS, &req) < 0)
      {
          printf("ioctl(VIDIOC_REQBUFS): fail\n");
          close(pCtx->fd_v4l2[j]);
          return 0;
      }
      printf("req.count %d\n", req.count);

      for (i = 0; i<ISP_ADDR_BUFFER_CNT; i++) 
      {
          struct v4l2_buffer buf;

          buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
          buf.index  = i;
          buf.memory = V4L2_MEMORY_USERPTR;
          
          if (ioctl(pCtx->fd_v4l2[j], VIDIOC_QUERYBUF, &buf) < 0)
          {
              printf("ioctl(VIDIOC_QUERYBUF) fail: index %d\n", buf.index);
              close(pCtx->fd_v4l2[j]);
              return 0;
          }

          pCtx->v4l2_buf[j][i].length = (buf.length + 0xfff) & (~0xfff);
          pCtx->v4l2_buf[j][i].paddr = alloc_memory(pCtx->fd_share_memory, pCtx->v4l2_buf[j][i].length);
          if(pCtx->v4l2_buf[j][i].paddr == -1)
          {
            printf("Not enough memory for v4l2 buf.\n");
            return -1;
          }
          pCtx->v4l2_buf[j][i].vaddr = mmap(NULL, pCtx->v4l2_buf[j][i].length, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->v4l2_buf[j][i].paddr);

          if(pCtx->v4l2_buf[j][i].vaddr == MAP_FAILED)
          {
              printf("v4l2 mmap fail\n");
              close(pCtx->fd_v4l2[j]);
              return 0;
          }
          
      }

      for (i = 0; i<ISP_ADDR_BUFFER_CNT; i++) 
      {
          struct v4l2_buffer buf;

          buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
          buf.index  = i;
          buf.memory = V4L2_MEMORY_USERPTR;

          buf.length = pCtx->v4l2_buf[j][i].length;
          buf.m.userptr = (unsigned long)pCtx->v4l2_buf[j][i].vaddr;

          if (ioctl(pCtx->fd_v4l2[j], VIDIOC_QBUF, &buf) < 0)
          {
              printf("ioctl(VIDIOC_QBUF) fail: index %d\n", buf.index);
              close(pCtx->fd_v4l2[j]);
              return 0;
          }
      }

      type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      if (ioctl(pCtx->fd_v4l2[j], VIDIOC_STREAMON, &type) < 0) 
      {
          printf("ioctl(VIDIOC_STREAMON): fail\n");
          close(pCtx->fd_v4l2[j]);
          return 0;
      }      
      
      pthread_create(&pCtx->v4l2_thread[j], NULL, v4l2_output, &pCtx->ch[j]);

    }
}

int init_audio(int nSampleRate)
{
  int ret;
  int flags;
  flags = SND_PCM_NONBLOCK;
  int frame_byte;

  snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
  snd_pcm_t *h;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_uframes_t buffer_size, period_size;

  ret = snd_pcm_open(&h, pCtx->audio_device, SND_PCM_STREAM_CAPTURE, flags);
  if(ret < 0)
  {
    printf("Cannot open audio device: %s\n", pCtx->audio_device);
    return -1;
  }

  ret = snd_pcm_hw_params_malloc(&hw_params);
  if(ret < 0)
  {
    printf("Cannot alloc hardware parameter structure\n");
    goto fail1;
  }

  ret = snd_pcm_hw_params_any(h, hw_params);
  if(ret < 0)
  {
    printf("Cannot initialize hardware parameter structure\n");
    goto fail;
  }

  ret = snd_pcm_hw_params_set_access(h, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
  if(ret < 0)
  {
    printf("Cannot set access type\n");
    goto fail;
  }

  ret = snd_pcm_hw_params_set_format(h, hw_params, format);
  if (ret < 0) {
      printf("Cannot set sample format %s\n", format);
      goto fail;
  }

  ret = snd_pcm_hw_params_set_rate_near(h, hw_params, (unsigned int*)(&pCtx->audio_sample_rate), 0);
  if (ret < 0) {
      printf("cannot set sample rate");
        goto fail;
  }

  ret = snd_pcm_hw_params_set_channels(h, hw_params, pCtx->audio_ch_cnt);
  if (ret < 0) {
      printf("Cannot set channel count to %d\n", pCtx->audio_ch_cnt);
      goto fail;
  }
#if 0
  snd_pcm_hw_params_get_buffer_size_max(hw_params, &buffer_size);
  buffer_size = MIN(buffer_size, ALSA_BUFFER_SIZE_MAX);
  printf("========snd_pcm_hw_params_set_buffer_size_near buffersize:%d\n",buffer_size);

  ret = snd_pcm_hw_params_set_buffer_size_near(h, hw_params, &buffer_size);
  if (ret < 0) {
    printf("Cannot set ALSA buffer size\n");
    goto fail;
  }


  snd_pcm_hw_params_get_period_size_min(hw_params, &period_size, NULL);
  if (!period_size)
    period_size = buffer_size / 4;
#else
  period_size = nSampleRate/25;
#endif
  ret = snd_pcm_hw_params_set_period_size_near(h, hw_params, &period_size, NULL);
  if (ret < 0) {
    printf("Cannot set ALSA period size\n");
    goto fail;
  }
  pCtx->period_size = period_size;

  ret = snd_pcm_hw_params(h, hw_params);
  if (ret < 0) {
    printf("Cannot set parameters\n");
    goto fail;
  }

  snd_pcm_hw_params_free(hw_params);

  pCtx->audio_frame_size = snd_pcm_format_width(pCtx->audio_format)/8 * pCtx->audio_ch_cnt; 
  pCtx->audio_buffer = (char*)malloc(sizeof(char) * pCtx->period_size * pCtx->audio_frame_size * pCtx->audio_ch_cnt);
  pthread_create(&pCtx->audio_thread, NULL, audio_process, pCtx);
  pCtx->audio_processing = 1;

  pCtx->pcmp = h;
  return 0;

fail:
    snd_pcm_hw_params_free(hw_params);
fail1:
    snd_pcm_close(h);
    return -EIO;
}

int alsa_xrun_recover(MainContext *pCtx, int err)
{
  snd_pcm_t *handle = pCtx->pcmp;
  if(err == -EPIPE)
  {
    err = snd_pcm_prepare(handle);
    if(err < 0)
    {
      printf("cannot recover from underrun (snd_pcm_prepare failed)\n");
      return -EIO;
    }
  }
  else if(err == -ESTRPIPE)
  {
      printf("-ESTRPIPE... Unsupported!\n");
      return -1;
  }
  return err;
}

static void *audio_process(void *arg)
{
  MainContext *pCtx = (MainContext *)arg;
  int ret = 0;
  int audio_out_frames = 0;
  unsigned char sEncAudioBuf[5000] = {0};
  int nG711Len = 0;
  while(pCtx->start)
  {
    pCtx->audio_size = 0;
    do
    {
read_pcm:
      while((ret = snd_pcm_readi(pCtx->pcmp, pCtx->audio_buffer, pCtx->audio_sample_rate)) < 0)
      {
        if(ret == -EAGAIN)
        {
          goto read_pcm; 
        }
        pCtx->audio_size = 0;
        if(alsa_xrun_recover(pCtx, ret) < 0)
        {
          printf("ALSA read error %s\n", snd_strerror(ret));
          goto read_pcm;
        }
      }
      pCtx->audio_size += ret * pCtx->audio_frame_size;
    }while (pCtx->audio_size < pCtx->period_size * pCtx->audio_frame_size);

    nG711Len = encode(pCtx->audio_buffer,(char*)sEncAudioBuf,pCtx->audio_size,G711_A_LAW);
    if(nG711Len > 0)
    {
      //printf("=========audio g711 size:%d\n",nG711Len);
      pCtx->pRtspServer[0]->PushAudioData(sEncAudioBuf, nG711Len, 0);
    }

    if(received_sigterm == 1)
      break;
  }
  pCtx->audio_processing = 0;

  return 0;
}

static int roi_parse_conf(const char* filename,ENC_ROI_CFG_ARRAY&aryEncRoiCfg, ROICtrlMode& nRoiCtrMode)
{
  FILE *fp = NULL;
  int len = 0;
  char* data = NULL;
  char* out = NULL;
  int roiCtrlTmp = 0;
  cJSON *root;
  cJSON *jsonCtrlMode;
  cJSON *jsonRoiRegion;
  cJSON*jsonRoiRegionArray;
  cJSON*jsonRoiRect;
  cJSON*jsonRoiRegionEnable;

  fp=fopen(filename,"rb");
  if(NULL == fp)
  {
    printf("read %s:file %s no exist!\n",__func__,filename);
    return -1;
  }
  fseek(fp,0,SEEK_END);
  len=ftell(fp);
  fseek(fp,0,SEEK_SET);
  data=(char*)malloc(len+1);
  fread(data,1,len,fp);
  fclose(fp);


  root=cJSON_Parse(data);
  if (!root) 
  {
    printf("cJSON_Parse Error:%s [%s]\n",filename,cJSON_GetErrorPtr());
    return -1;
  }
  else
  {

    jsonCtrlMode = cJSON_GetObjectItem(root,"roiCtrMode");
    if(NULL == jsonCtrlMode)
    {
      printf("not find roiCtrMode node\n");
      return -1;
    }
    if(jsonCtrlMode->type==cJSON_Number)
    {
      roiCtrlTmp = jsonCtrlMode->valueint;
      if (roiCtrlTmp != ROI_QP_TABLE_RELATIVE && roiCtrlTmp != ROI_QP_TABLE_ABSOLUTE)
      {
        printf("roiCtrMode type invalid\n");
        return -1;      
      }
    }
    else
    {
      return -1;
    }

    jsonRoiRegionArray = cJSON_GetObjectItem(root,"roiRegion");
    if(NULL == jsonRoiRegionArray)
    {
      printf("not find roiRegion node\n");
      return -1;
    }
    int nSize = cJSON_GetArraySize(jsonRoiRegionArray);
    if (nSize <= 0)
    {
      printf("roiRegion array is empty\n");
      return -1;
    }

    EncROICfg   encRoiCfg;
    int nIndex = 0;
    for (int i = 0;i < nSize;i ++)
    {
      jsonRoiRegion = cJSON_GetArrayItem(jsonRoiRegionArray,i);
      jsonRoiRegionEnable = cJSON_GetObjectItem(jsonRoiRegion,"enable");
      //filter unenable item
      if (NULL != jsonRoiRegionEnable)
      {
        if(jsonRoiRegionEnable->type==cJSON_Number)
        {
          if (0 == jsonRoiRegionEnable->valueint)
          {
            printf("roi_parse_conf pass an iterm\n");
            continue;
          }
        }
      }

      encRoiCfg.uIndex = nIndex++;
      encRoiCfg.bEnable = true;
      encRoiCfg.uQpValue = cJSON_GetObjectItem(jsonRoiRegion,"qpValue")->valueint;
      jsonRoiRect = cJSON_GetObjectItem(jsonRoiRegion,"qpRegion");

      encRoiCfg.stRect.s32X = cJSON_GetObjectItem(jsonRoiRect,"left")->valueint;
      encRoiCfg.stRect.s32Y = cJSON_GetObjectItem(jsonRoiRect,"top")->valueint;
      encRoiCfg.stRect.u32Width = cJSON_GetObjectItem(jsonRoiRect,"width")->valueint;
      encRoiCfg.stRect.u32Height = cJSON_GetObjectItem(jsonRoiRect,"heigth")->valueint;
      
      printf("roi cfg info: index:%d,qpvalue:%d,rect(%d,%d,%d,%d)\n",
        encRoiCfg.uIndex,encRoiCfg.uQpValue,encRoiCfg.stRect.s32X,
        encRoiCfg.stRect.s32Y,encRoiCfg.stRect.u32Width,encRoiCfg.stRect.u32Height);

      aryEncRoiCfg.push_back(encRoiCfg);
    }

    
  }
  cJSON_Delete(root);
  nRoiCtrMode = (ROICtrlMode)roiCtrlTmp ;
 
  return 0;	
}


int parse_conf()
{
  printf("%s\n", __FUNCTION__);
  FILE *fp;
  long len;
  char* data;
  char* out;

  cJSON *root;
  cJSON *arrayItem;
  cJSON *item;
  cJSON *newitem;
  cJSON *object;
  cJSON *sensor0;
  cJSON *sensor1;
  cJSON *video;

  char video_used_name[20];
  char video_width_name[20];
  char video_height_name[20];
  int i = 0;

  fp=fopen(pCtx->conf_filename,"rb");
  if(NULL == fp)
  {
    printf("read %s:file no exist!\n",__func__);
    return -1;
  }
  fseek(fp,0,SEEK_END);
  len=ftell(fp);
  fseek(fp,0,SEEK_SET);
  data=(char*)malloc(len+1);
  fread(data,1,len,fp);
  fclose(fp);
  // doit_video_cfg(data,vi_cfg,sensor0,sensor1,dev_info);

  root=cJSON_Parse(data);
  if (!root) 
  {
      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
  }
  else
  {
    out=cJSON_Print(root);

    sensor0 = cJSON_GetObjectItem(root,"sensor0");
    sensor1 = cJSON_GetObjectItem(root,"sensor1");
    if(sensor0 != NULL && sensor1 != NULL)
    {
      for(i = 0; i < pCtx->ch_cnt; i++)
      {
        if(!pCtx->enable_v4l2[i])
        {
          continue;
        }
        snprintf(video_used_name, sizeof(video_used_name), "video%c_used", pCtx->dev_name[i][10]);
        snprintf(video_width_name, sizeof(video_width_name), "video%c_width", pCtx->dev_name[i][10]);
        snprintf(video_height_name, sizeof(video_height_name), "video%c_height", pCtx->dev_name[i][10]);
        printf("pCtx->dev_name: %s\n", pCtx->dev_name[i]);
        printf("video_used_name: %s\n", video_used_name);
        printf("video_width_name: %s\n", video_width_name);
        printf("video_height_name: %s\n", video_height_name);

        if((pCtx->dev_name[i][10] >= '2') && (pCtx->dev_name[i][10] <= '5'))
        {
          video = cJSON_GetObjectItem(sensor0,pCtx->dev_name[i]);
        }
        else if((pCtx->dev_name[i][10] >= '6') && (pCtx->dev_name[i][10] <= '9'))
        {
          video = cJSON_GetObjectItem(sensor1,pCtx->dev_name[i]);
        }
        else
        {
          printf("dev name error!\n");
          return -1;
        }
        item = cJSON_GetObjectItem(video, video_used_name);
        cJSON_SetIntValue(item, 1);

        item = cJSON_GetObjectItem(video, video_width_name);
        cJSON_SetIntValue(item, pCtx->width[i]);

        item = cJSON_GetObjectItem(video, video_height_name);
        cJSON_SetIntValue(item, pCtx->height[i]);
      }      
    }
  }

  printf("%s>modified\n", __FUNCTION__);
  fp=fopen(REAL_CONF_FILENAME,"wt");
  if(NULL == fp)
  {
    printf("write %s:file no exist!\n",__func__);
    return -1;
  }

  out = cJSON_Print(root);
  fprintf(fp,"%s",out);

  fclose(fp);
  free(out);

  free(data);
  printf("parse conf done\n");
  return 0;
}

static void DoEncRoi(EncoderHandle *hEnc,const ENC_ROI_CFG_ARRAY& aryEncRoiCfg)
{
  for(int i =0;i < aryEncRoiCfg.size();i ++)
  {
    VideoEncoder_SetRoiCfg(hEnc,&aryEncRoiCfg[i]);
  }
}

int alloc_context(void *arg)
{
  MainContext *pCtx = (MainContext *)arg;

  pCtx->fd_v4l2         = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->isp_rp          = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->isp_wp          = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->isp_addr        = (long(*)[ISP_ADDR_BUFFER_CNT])malloc(sizeof(long) * ISP_ADDR_BUFFER_CNT * pCtx->ch_cnt);
  pCtx->isp_pic_cnt     = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->v4l2_buf        = (V4L2_BUF**)malloc(sizeof(V4L2_BUF*) *  pCtx->ch_cnt);
  
  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    pCtx->v4l2_buf[i]   = (V4L2_BUF*)malloc(sizeof(V4L2_BUF) * ISP_ADDR_BUFFER_CNT);
  }
  pCtx->v4l2_rev        = (V4L2_REV**)malloc(sizeof(V4L2_REV*) * pCtx->ch_cnt);
  
  for(int i = 0; i < pCtx->ch_cnt; i++)
  {
    pCtx->v4l2_rev[i]   = (V4L2_REV*)malloc(sizeof(V4L2_REV) * ISP_ADDR_BUFFER_CNT);
  }
  pCtx->pSemGetData         = (sem_t*)malloc(sizeof(sem_t) * pCtx->ch_cnt);
  pCtx->v4l2_rp         = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->v4l2_wp         = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->v4l2_pic_cnt    = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->total_out_size  = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->rtsp_buf_wp     = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->isp_buf_vaddr   = (void**)malloc(sizeof(void*) * pCtx->ch_cnt);
  pCtx->isp_buf_paddr   = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->isp_buf_size    = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->enable_isp      = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->enable_rtsp     = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->enable_v4l2     = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->yuv_phyAddr     = (long*)malloc(sizeof(long) * pCtx->ch_cnt);
  pCtx->yuv_vAddr       = (void**)malloc(sizeof(void*) * pCtx->ch_cnt);
  pCtx->yuv_size        = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->start_time      = (unsigned long int*)malloc(sizeof(unsigned long int) * pCtx->ch_cnt);
  pCtx->out_buffer      = (void**)malloc(sizeof(void*) * pCtx->ch_cnt);
  pCtx->stream_size     = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->out_pic         = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->framerate       = (unsigned char*)malloc(sizeof(unsigned char) * pCtx->ch_cnt);
  pCtx->stream_phyAddr  = (long*)malloc(sizeof(long) * pCtx->ch_cnt);
  pCtx->in_file         = (FILE**)malloc(sizeof(FILE*) * pCtx->ch_cnt);
  pCtx->out_file        = (FILE**)malloc(sizeof(FILE*) * pCtx->ch_cnt);
  pCtx->hEnc            = (EncoderHandle**)malloc(sizeof(EncoderHandle *) * pCtx->ch_cnt);
  pCtx->shared_phyAddr  = (long*)malloc(sizeof(long) * pCtx->ch_cnt);
  pCtx->shared_vAddr    = (void**)malloc(sizeof(void*) * pCtx->ch_cnt);
  pCtx->shared_size     = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->exp             = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->agc             = (unsigned int*)malloc(sizeof(unsigned int) * pCtx->ch_cnt);
  pCtx->stride          = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->width           = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->height          = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->input_frames    = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->isp_thread      = (pthread_t*)malloc(sizeof(pthread_t) * pCtx->ch_cnt);
  pCtx->v4l2_thread     = (pthread_t*)malloc(sizeof(pthread_t) * pCtx->ch_cnt);
  pCtx->encode_thread   = (pthread_t*)malloc(sizeof(pthread_t) * pCtx->ch_cnt);
  pCtx->pRtspServer     = (IRtspServerEX**)malloc(sizeof(IRtspServerEX*) * pCtx->ch_cnt);
  pCtx->roi_filename    = (char**)malloc(sizeof(char*) * pCtx->ch_cnt);
  pCtx->aryEncRoiCfg    = (ENC_ROI_CFG_ARRAY*)malloc(sizeof(ENC_ROI_CFG_ARRAY) * pCtx->ch_cnt);
  pCtx->nLTRFreq        = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->Cfg             = (EncSettings*)malloc(sizeof(EncSettings) * pCtx->ch_cnt);
  pCtx->ch_en           = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->infilename      = (char**)malloc(sizeof(char*) * pCtx->ch_cnt);
  pCtx->outfilename     = (char**)malloc(sizeof(char*) * pCtx->ch_cnt);
  pCtx->dev_name        = (char**)malloc(sizeof(char*) * pCtx->ch_cnt);
  pCtx->output_frames   = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->encoding        = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->ch              = (int*)malloc(sizeof(int) * pCtx->ch_cnt);
  pCtx->repeat          = (uint32_t*)malloc(sizeof(uint32_t) * pCtx->ch_cnt);
  pCtx->repeat_en       = (uint32_t*)malloc(sizeof(uint32_t) * pCtx->ch_cnt);
  pCtx->drop            = (uint32_t*)malloc(sizeof(uint32_t) * pCtx->ch_cnt);
  pCtx->drop_en         = (uint32_t*)malloc(sizeof(uint32_t) * pCtx->ch_cnt);
  pCtx->framerate_mod   = (uint32_t*)malloc(sizeof(uint32_t) * pCtx->ch_cnt);
  pCtx->out_framerate   = (unsigned char*)malloc(sizeof(unsigned char) * pCtx->ch_cnt);
  pCtx->set_ae          = (int*)malloc(sizeof(int) * pCtx->ch_cnt);

  memset(pCtx->Cfg,0,sizeof(EncSettings));

  return 0;
}


int parse_cmd(int argc, char *argv[])
{
  int i = 0;
  int j = 0;
  int cur_ch = 0;
  for(i=1; i<argc; i+=2)
  {
    if(strcmp(argv[i], "-help") == 0)
    {
      printf("Please input:\n");
      printf("-split: sensor channel count\n");
      printf("-ch: sensor channel\n");
      printf("-i: input file name or isp\n");
      printf("-dev: v4l2 device name\n");
      printf("-o: output file name or rtsp\n");
      printf("-w: width\n");
      printf("-h: height\n");
      printf("-e: set sensor exposure rate\n");
      printf("-ag: analog gain\n");
      printf("-fps: sensor input framerate\n");
      printf("-r: encoder output framrate\n");
      printf("-inframes: input frames for input file\n");
      printf("-outframes: output frames for output file\n");
      printf("-gop: gop length in frames including the I picture,use in IDR\n");
      printf("-rcmode: 0:CONST_QP  1:CBR  2:VBR 3:jpg\n");
      printf("-bitrate: bitrate(Kb)\n");
      printf("-maxbitrate: max bitrate(Kb),use in vbr\n");
      printf("-profile: 0: base  1:main 2:high\n");
      printf("-level: from 10 to 42\n");
      printf("-sliceqp: auto:-1,from 0 to 51 for AVC,from 1 to 100 for JPEG\n");
      printf("-minqp: from 0 to sliceqp\n");
      printf("-maxqp: from sliceqp to 51\n");
      printf("-enableGDR: enbale intra refresh and specifies intra refresh peroid\n");
      printf("-GDRMode: GDR mode 0:GDR_VERTICAL 1:GDR_HORIZONTAL\n");
      printf("-enableLTR: enbale long term reference picture and specifies LTR refresh frequency in number of frames,0 to disable use refresh frequency\n");
      printf("-roi: roi config file\n");
      printf("-ae: enable ae\n");
      printf("-conf: v4l2 config file\n");
      /* audio */
      printf("-alsa: enable audio\n");
      printf("-ac: audio channel count\n");
      printf("-ar: audio sample rate\n");
      printf("-af: auido sample format\n");
      printf("-ad: audio device");
      printf("-lossless: enable jpeg lossless encode");
      // printf("-aof: audio output frames\n");
      return 1;
    }
    else if(strcmp(argv[i], "-split") == 0)
    {
      pCtx->ch_cnt = atoi(argv[i+1]);
      printf("-split: %d\n", pCtx->ch_cnt);
      alloc_context(pCtx);
    }
    else if(strcmp(argv[i], "-ch") == 0)
    {
      cur_ch = atoi(argv[i+1]);
      if(cur_ch >= pCtx->ch_cnt)
      {
        printf("Channel set error: %d", cur_ch);
      }
      pCtx->ch_en[cur_ch] = 1;
      printf("-ch%d: %d\n", cur_ch, pCtx->ch_en[cur_ch]);
      memset(&pCtx->Cfg[cur_ch],0,sizeof(EncSettings));
    }
    else if(strcmp(argv[i], "-i") == 0)
    {      
      pCtx->video_enabled = 1;
      if(strcmp(argv[i+1], "isp") == 0)
      {
        if(pCtx->ch_cnt != 1)
        {
          printf("split prarm error!\n");
          return -1;
        }
        pCtx->enable_isp[cur_ch] = 1;
      }
      else if(strcmp(argv[i+1], "v4l2") == 0)
      {
        pCtx->enable_v4l2[cur_ch] = 1;
      }
      else
      {
        pCtx->enable_isp[cur_ch] = 0;    
        pCtx->enable_v4l2[cur_ch] = 0;
        printf("infilename: %s\n", argv[i+1]);
        if( (pCtx->in_file[cur_ch] = fopen(argv[i+1],"r+b")) == NULL )
        {
          printf("Cannot open input file!!!\n");
          return -1;
        } 
        pCtx->infilename[cur_ch] = argv[i+1];
      }
    }
    else if(strcmp(argv[i], "-dev") == 0)
    {
      pCtx->dev_name[cur_ch] = (char*)malloc(strlen(argv[i+1])+1);
      memcpy(pCtx->dev_name[cur_ch], argv[i+1], strlen(argv[i+1])+1);
      printf("ch%d: %s\n", cur_ch, pCtx->dev_name[cur_ch]);
    }
    else if(strcmp(argv[i], "-o") == 0)
    {
      if(strcmp(argv[i+1], "rtsp") == 0)
      {
        pCtx->enable_rtsp[cur_ch] = 1;
      }
      else
      {
        pCtx->enable_rtsp[cur_ch] = 0;
        printf("outfilename: %s\n", argv[i+1]);
        if( (pCtx->out_file[cur_ch]=fopen(argv[i+1],"w+b")) == NULL )
        {
          printf("Cannot open output file!\n");
          return -1;
        }
        pCtx->outfilename[cur_ch] = argv[i+1];
#if 0
        char *ptr=strchr(pCtx->outfilename[cur_ch], '.');
        if(strcmp(ptr, ".jpg") == 0 || strcmp(ptr, ".mjpeg") == 0)
        {
          pCtx->Cfg[cur_ch].profile = JPEG;
          pCtx->Cfg[cur_ch].rcMode = CONST_QP; 
          printf("JPEG encode\n");
        }
#endif 
      }
    }
    else if(strcmp(argv[i], "-w") == 0)
    {
      pCtx->Cfg[cur_ch].width = atoi(argv[i+1]);
      printf("width %d\n", pCtx->Cfg[cur_ch].width);
    }
    else if(strcmp(argv[i], "-h") == 0)
    {
      pCtx->Cfg[cur_ch].height = atoi(argv[i+1]);
      printf("height %d\n", pCtx->Cfg[cur_ch].height);
    }
    else if(strcmp(argv[i], "-e") == 0)
    {
      pCtx->exp[cur_ch] = atoi(argv[i+1]);
      printf("exp = %d\n", pCtx->exp[cur_ch]);
      if(pCtx->exp[cur_ch] <= 0 || pCtx->exp[cur_ch] > 128)
      {
        printf("wrong exp = %d\n", pCtx->exp[cur_ch]);
        return -1;
      }
      pCtx->exp[cur_ch] *= 8;
    }
    else if(strcmp(argv[i], "-ag") == 0)
    {
      pCtx->agc[cur_ch] = atoi(argv[i+1]);
      printf("agc = %d\n", pCtx->agc[cur_ch]);
      if(pCtx->agc[cur_ch] < 0 || pCtx->agc[cur_ch] > 232)
      {
        printf("wrong agc = %d\n", pCtx->agc[cur_ch]);
        return -1;
      }
    }
    else if(strcmp(argv[i], "-fps") == 0)
    {
      pCtx->framerate[cur_ch] = atoi(argv[i+1]);
      printf("framerate %d\n", pCtx->framerate[cur_ch]);
    }
    else if(strcmp(argv[i], "-r") == 0)
    {
      pCtx->out_framerate[cur_ch] = atoi(argv[i+1]);
      printf("out_framerate %d\n", pCtx->out_framerate[cur_ch]);
    }
    else if(strcmp(argv[i], "-inframes") == 0)
    {
      pCtx->input_frames[cur_ch] = atoi(argv[i+1]);
      printf("input_frames %d\n", pCtx->input_frames[cur_ch]);
    }
    else if(strcmp(argv[i], "-outframes") == 0)
    {
      pCtx->output_frames[cur_ch] = atoi(argv[i+1]);
      printf("output_frames %d\n", pCtx->output_frames[cur_ch]);
    }
    else if(strcmp(argv[i], "-gop") == 0)
    {
      pCtx->Cfg[cur_ch].gopLen = atoi(argv[i+1]);
      if (pCtx->Cfg[cur_ch].gopLen <= 0)
      {
        printf("gop len error\n");
        return -1;
      }
      pCtx->Cfg[cur_ch].FreqIDR = pCtx->Cfg[cur_ch].gopLen;
      printf("gop length %d\n", pCtx->Cfg[cur_ch].gopLen);
    }
    else if(strcmp(argv[i], "-bitrate") == 0)
    {
      pCtx->Cfg[cur_ch].BitRate = atoi(argv[i+1])*1000;
      printf("bitrate %d\n", pCtx->Cfg[cur_ch].BitRate);
    }
    else if (strcmp(argv[i],"-maxbitrate") == 0 )
    {
      pCtx->Cfg[cur_ch].MaxBitRate = atoi(argv[i+1])*1000;
      printf("maxbitrate %d\n", pCtx->Cfg[cur_ch].MaxBitRate);
    }
    else if (strcmp(argv[i],"-profile") == 0 )
    {
      int nProfile = atoi(argv[i+1]);
      if (nProfile > 2 || nProfile < 0)
      {
        printf("profile:%d error\n",nProfile);
        return -1;
      }
      pCtx->Cfg[cur_ch].profile = (AVC_Profile)nProfile;
      printf("profile %d\n", pCtx->Cfg[cur_ch].profile);
    }
    else if (strcmp(argv[i],"-level") == 0 )
    {
      int nLevel = atoi(argv[i+1]);
      if (nLevel < 10 || nLevel > 42)
      {
        printf("level:%d error\n",nLevel);
        return -1;
      }
      pCtx->Cfg[cur_ch].level = nLevel;
      printf("level:%d\n",nLevel);
    }
    else if (strcmp(argv[i],"-sliceqp") == 0 )
    {
      int nqp = atoi(argv[i+1]);
      pCtx->Cfg[cur_ch].SliceQP = nqp;
      printf("sliceqp %d\n", nqp);
    }
    else if (strcmp(argv[i],"-lossless") == 0 )
    {
      int lossless = atoi(argv[i+1]);
      pCtx->Cfg[cur_ch].lossless = lossless;
      printf("lossless %d\n", lossless);
    }
    else if (strcmp(argv[i],"-minqp") == 0 )
    {
      int nqp = atoi(argv[i+1]);
      pCtx->Cfg[cur_ch].MinQP = nqp;
      printf("minqp %d\n", nqp);
    }
    else if (strcmp(argv[i],"-maxqp") == 0 )
    {
      int nqp = atoi(argv[i+1]);
      pCtx->Cfg[cur_ch].MaxQP = nqp;
      printf("maxqp %d\n", nqp);
    }
    else if (strcmp(argv[i],"-rcmode") == 0)
    {
      int nRcMode = atoi(argv[i+1]);
      if (nRcMode > 2 || nRcMode < 0)
      {
        printf("rcmode error,must be 0-2\n");
        return -1;
      }
      pCtx->Cfg[cur_ch].rcMode = (RateCtrlMode)nRcMode;
      printf("rcmode %d(0:CONST_QP 1:CBR 2:VBR)\n", pCtx->Cfg[cur_ch].rcMode);
    }
    else if(strcmp(argv[i], "-enableGDR") == 0)
    {
      pCtx->Cfg[cur_ch].bEnableGDR = true;
      pCtx->Cfg[cur_ch].FreqIDR = atoi(argv[i+1]);
      if (pCtx->Cfg[cur_ch].FreqIDR <= 0)
      {
        printf("gdr fresh period error\n");
        return -1;
      }

      printf("enable gdr and fresh peroid %d\n", pCtx->Cfg[cur_ch].FreqIDR);
    }
    else if (strcmp(argv[i], "-GDRMode") == 0)
    {
      int nGdrMode = atoi(argv[i+1]);
      if (nGdrMode < 0 || nGdrMode >= GDR_CTRLMAX)
      {
        printf("gdr mode set error\n");
        return -1;
      }
      pCtx->Cfg[cur_ch].gdrMode = (GDRCtrlMode)nGdrMode;
    }
    else if(strcmp(argv[i], "-enableLTR") == 0)
    {
      pCtx->Cfg[cur_ch].bEnableLTR = true;
      pCtx->nLTRFreq[cur_ch] = atoi(argv[i+1]);
      printf("enable LTR and  refresh frequency %d\n", pCtx->nLTRFreq[cur_ch]);
    }
    else if (strcmp(argv[i], "-roi") == 0)
    {
      pCtx->roi_filename[cur_ch] = (char*)malloc(strlen(argv[i+1])+1);
      memcpy(pCtx->roi_filename[cur_ch], argv[i+1], strlen(argv[i+1])+1);
      printf("roi_filename %s\n",pCtx->roi_filename[cur_ch]);
      if (0 != roi_parse_conf(pCtx->roi_filename[cur_ch],pCtx->aryEncRoiCfg[cur_ch],pCtx->Cfg[cur_ch].roiCtrlMode))
      {
        printf("roi_parse_conf failed\n");
        //endof_encode();
        return -1;
      }
      else
      {
        printf("roi_parse_conf ok\n");
      }
    }
    else if(strcmp(argv[i], "-ae") == 0)
    {
      pCtx->ae_enable = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-conf") == 0)
    {
      pCtx->conf_filename = (char*)malloc(strlen(argv[i+1])+1);
      memcpy(pCtx->conf_filename, argv[i+1], strlen(argv[i+1])+1);
      printf("conf_filename %s\n",pCtx->conf_filename);
    }
    /* audio parameters */
    else if(strcmp(argv[i], "-alsa") == 0)
    {
      pCtx->audio_enabled = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-ac") == 0)
    {
      pCtx->audio_ch_cnt = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-ar") == 0)
    {
      pCtx->audio_sample_rate = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-af") == 0)
    {
      pCtx->audio_format = (snd_pcm_format_t)(atoi(argv[i+1]));
    }
    else if(strcmp(argv[i], "-ad") == 0)
    {
      pCtx->audio_device = (char*)malloc(strlen(argv[i+1])+1);
      memcpy(pCtx->audio_device, argv[i+1], strlen(argv[i+1])+1);
    }
    else
    {
      printf("Error :Invalid arguments %s\n", argv[i]);      
      return -1;
    }
  }  
  return 0;
}

int main(int argc, char *argv[])
{
  EncSettings Cfg;
  int i;
  int src_index=0;
  EncInputFrame input;
  EncOutputStream output;
  int size;
  unsigned int frame_size=0;
  unsigned int output_frames=0;
  unsigned int input_frames=0;
  int stride;    

  memset(pCtx, 0, sizeof(MainContext));
  pCtx->start = 1;

  if(parse_cmd(argc, argv) < 0)
  {
    return -1;
  }

  for(i = 0; i < pCtx->ch_cnt; i++)
  {
    if(pCtx->enable_isp[i] == 1)
    {
      pCtx->isp_enabled = 1;
      break;
    }
  }

  for(i = 0; i < pCtx->ch_cnt; i++)
  {
    if(pCtx->enable_v4l2[i] == 1)
    {
      pCtx->v4l2_enabled = 1;
      break;
    }
  }

  if(pCtx->video_enabled)
  {
  
    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      pCtx->ch[i] = i;
      pCtx->Cfg[i].channel     = i;
      if(!pCtx->framerate[i])             pCtx->framerate[i]       = 30;
      if(!pCtx->out_framerate[i])         pCtx->out_framerate[i]   = 30;
      if(!pCtx->Cfg[i].width)             pCtx->Cfg[i].width       = 1920;
      if(!pCtx->Cfg[i].height)            pCtx->Cfg[i].height      = 1080;
      if(!pCtx->Cfg[i].BitRate)           pCtx->Cfg[i].BitRate     = 4000000;
      if(!pCtx->Cfg[i].MaxBitRate)        pCtx->Cfg[i].MaxBitRate  = 4000000;
      if(!pCtx->Cfg[i].level)             pCtx->Cfg[i].level       = 42;
      if(!pCtx->Cfg[i].profile)           pCtx->Cfg[i].profile     = AVC_HIGH;
      if(!pCtx->Cfg[i].rcMode)            pCtx->Cfg[i].rcMode      = CBR; 
      if(!pCtx->Cfg[i].SliceQP)           pCtx->Cfg[i].SliceQP     = 25;
      if(!pCtx->Cfg[i].FreqIDR)           pCtx->Cfg[i].FreqIDR     = 25;
      if(!pCtx->Cfg[i].gopLen)            pCtx->Cfg[i].gopLen      = 25;
      if(!pCtx->Cfg[i].AspectRatio)       pCtx->Cfg[i].AspectRatio = ASPECT_RATIO_AUTO;
      if(!pCtx->Cfg[i].MinQP)             pCtx->Cfg[i].MinQP       = 0;//from 0 to SliceQP
      if(!pCtx->Cfg[i].MaxQP)             pCtx->Cfg[i].MaxQP       = 51;//from SliceQP to 51
      if(!pCtx->Cfg[i].roiCtrlMode)       pCtx->Cfg[i].roiCtrlMode = ROI_QP_TABLE_NONE;

      pCtx->Cfg[i].encDblkCfg.disable_deblocking_filter_idc        = 0;
      pCtx->Cfg[i].encDblkCfg.slice_beta_offset_div2               = 1;
      pCtx->Cfg[i].encDblkCfg.slice_alpha_c0_offset_div2           = 1;
      pCtx->Cfg[i].entropyMode                                     = ENTROPY_MODE_CAVLC;
      pCtx->Cfg[i].sliceSplitCfg.bSplitEnable                      = false;

      
    }

    for(int i =0;i < pCtx->ch_cnt; i++)
    {
      if (pCtx->outfilename[i] != NULL)
      {
        char *ptr=strchr(pCtx->outfilename[i], '.');
        if(strcmp(ptr, ".jpg") == 0 || strcmp(ptr, ".mjpeg") == 0)
        {
          pCtx->Cfg[i].profile = JPEG;
          pCtx->Cfg[i].rcMode = CONST_QP;          
          printf("JPEG encode\n");
        }
      }

      if(CBR == pCtx->Cfg[i].rcMode)
      {
        if (pCtx->Cfg[i].MaxBitRate != pCtx->Cfg[i].BitRate)
        {
          pCtx->Cfg[i].MaxBitRate = pCtx->Cfg[i].BitRate;
          printf("modify MaxBitRate  to BitRate:%d in cbr mode\n",pCtx->Cfg[i].BitRate);
        }
      }

      if (JPEG == pCtx->Cfg[i].profile)
      {
        if (pCtx->Cfg[i].SliceQP < 1 || pCtx->Cfg[i].SliceQP > 100)
        {
          printf("slice qp error\n");
          return -1;
        }
      }
      else
      {
        if (pCtx->Cfg[i].SliceQP < -1 || pCtx->Cfg[i].SliceQP > 51)
        {
          printf("slice qp error\n");
          return -1;
        }
      }
    }

    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      printf("ch%d: enable_isp %d, enable_v4l2 %d, enable_rtsp %d\n", i, pCtx->enable_isp[i], pCtx->enable_v4l2[i], pCtx->enable_rtsp[i]);
      printf("cur_ch:%d,roiCtrlMode:%d(0:NONE,1:RELATIVE,2:ABSOLUTE),sliceqp:%d,minqp:%d,maxqp:%d,rcMode:%d(0:CONST_QP, 1:CBR, 2:VBR),bitrate:%dkbps,maxbitrate:%dkbps,profile:%d,gop:%d,gdr:%d(freq:%d,mode:%d(0:VERTICAL 1:HORIZONTAL)),LTR:%d(%d)\n",
        i,pCtx->Cfg[i].roiCtrlMode,pCtx->Cfg[i].SliceQP,pCtx->Cfg[i].MinQP,pCtx->Cfg[i].MaxQP,pCtx->Cfg[i].rcMode,pCtx->Cfg[i].BitRate/1000,pCtx->Cfg[i].MaxBitRate/1000,pCtx->Cfg[i].profile,
        pCtx->Cfg[i].gopLen,pCtx->Cfg[i].bEnableGDR,pCtx->Cfg[i].FreqIDR,pCtx->Cfg[i].gdrMode,pCtx->Cfg[i].bEnableLTR,pCtx->nLTRFreq[i]);
    }

    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      if(pCtx->ch_en[i])
      {
        pCtx->Cfg[i].FrameRate = pCtx->out_framerate[i];
        printf("ch%d-Cfg.Framerate: %d\n", i, pCtx->Cfg[i].FrameRate);
        pCtx->hEnc[i] = VideoEncoder_Create(&pCtx->Cfg[i]);
        if (NULL == pCtx->hEnc[i])
        {
          printf("[%s] VideoEncoder_Create failed\n",__FUNCTION__);
          return -1;
        }

        if (ROI_QP_TABLE_NONE != pCtx->Cfg[i].roiCtrlMode)
        {
          DoEncRoi(pCtx->hEnc[i],pCtx->aryEncRoiCfg[i]);
        }

        if((JPEG == pCtx->Cfg[i].profile) && (pCtx->out_framerate[i] != pCtx->framerate[i]))
        {
          pCtx->repeat_en[i] = 0;
          pCtx->drop_en[i] = 0;
          printf("WARNING: NOT SUPPORT RC CONTROL IN JPEG MODE, OUTPUT WITH INPUT FRAMERATE.\n");
          pCtx->out_framerate[i] = pCtx->framerate[i];
        }
        else
        {
          if(pCtx->out_framerate[i] > pCtx->framerate[i])
          {
            pCtx->repeat_en[i] = 1;
            pCtx->repeat[i] = pCtx->out_framerate[i]/pCtx->framerate[i] - 1;
            printf("ch%d: repeat %d\n", i, pCtx->repeat[i]);
            pCtx->framerate_mod[i] = pCtx->out_framerate[i]%pCtx->framerate[i];
            printf("ch%d: framerate_mod %d\n", i, pCtx->framerate_mod[i]);
          }
          else if(pCtx->out_framerate[i] < pCtx->framerate[i])
          {
            pCtx->drop_en[i] = 1;
            pCtx->drop[i] = pCtx->framerate[i]/pCtx->out_framerate[i] - 1;
            printf("ch%d: drop %d\n", i, pCtx->drop[i]);
            pCtx->framerate_mod[i] = pCtx->framerate[i]%pCtx->out_framerate[i];
            // pCtx->framerate_mod[i] = pCtx->out_framerate[i]%pCtx->framerate[i];
            printf("ch%d: framerate_mod %d\n", i, pCtx->framerate_mod[i]);
          }
        }
      }
    }
  }

  if(pCtx->audio_enabled)
  {
    /* audio */
    if(!pCtx->audio_ch_cnt)               pCtx->audio_ch_cnt       = 2;
    if(!pCtx->audio_sample_rate)          pCtx->audio_sample_rate  = 44100;
    if(!pCtx->audio_format)               pCtx->audio_format       = SND_PCM_FORMAT_S16_LE;
    if (!pCtx->audioEncType)              pCtx->audioEncType       = (RTSP_AUDIO_TYPE)em_audio_type_g711a;
  }

  //create rtsp server
  for(int cur_ch = 0; cur_ch < pCtx->ch_cnt; cur_ch++)
  {
    if (1 == pCtx->enable_rtsp[cur_ch])
    {
      pCtx->pRtspServer[cur_ch] = IRtspServerEX::CreateRTSPServerEX();
      if(pCtx->audio_enabled)
      {
        pCtx->pRtspServer[cur_ch]->Init(8554 + cur_ch*2,true);
        RTSP_AUDIO_INFO audioInfo;
        audioInfo.audioType              = (RTSP_AUDIO_TYPE)pCtx->audioEncType;
        audioInfo.nBitsPerSample        = 16;
        audioInfo.nSamplingFrequency    = pCtx->audio_sample_rate;
        audioInfo.nNumChannels              = pCtx->audio_ch_cnt;
        pCtx->pRtspServer[cur_ch]->SetAudioInfo(audioInfo);	
        
      }
      else
      {
        pCtx->pRtspServer[cur_ch]->Init(8554 + cur_ch*2,false);
      }
      pCtx->pRtspServer[cur_ch]->CreateStreamUrl("testStream");
    }
  }

  
  
  pCtx->fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR | O_SYNC);
  if(pCtx->fd_share_memory < 0)
  {
     printf("Open %s Error!\n", SHARE_MEMORY_DEV);
  }

  pCtx->fd_ddr = open(DEV_NAME_DDR,O_RDWR|O_SYNC); 
  if(pCtx->fd_ddr < 0)
  {
    printf("Open %s Error!\n", DEV_NAME_DDR);
  } 
  
  if(pCtx->video_enabled)
  {
    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      if(!pCtx->ch_en[i])
      {
        continue;
      }
      stride = ((pCtx->Cfg[i].width + 0x1F) & (~0x1F));
      frame_size = stride*pCtx->Cfg[i].height*3/2;
      pCtx->stride[i] = stride;
      pCtx->width[i] = pCtx->Cfg[i].width;
      pCtx->height[i] = pCtx->Cfg[i].height;
    }
    
    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      if(pCtx->ch_en[i] && (pCtx->enable_isp[i] == 0) && (pCtx->enable_v4l2[i] == 0))
      {
        if(get_yuv(pCtx, pCtx->infilename[i], i) < 0)
        {
          endof_encode();
          return -1;
        }
      }
    }
  }

#if TEST_ISP
  if(pCtx->isp_enabled == 1)
  { 
    set_QoS();  
    if(init_isp() < 0)
    {
      endof_encode();
      return -1;
    }
  }
#endif
  if(pCtx->v4l2_enabled == 1)
  {   
    set_QoS();
    if(parse_conf() < 0)
    {
      printf("parse_conf error\n");
      return -1;
    }
    if(init_v4l2() < 0)
    {
      endof_encode();
      return -1;
    }
  }

  if(pCtx->audio_enabled == 1)
  {
    init_audio(pCtx->audio_sample_rate);
  }

  signal(SIGINT, exit_handler);
  
  if(pCtx->video_enabled)
  {
    for(i = 0; i < pCtx->ch_cnt; i++)
    {
      if(pCtx->ch_en[i])
      {
        pCtx->encoding[i] = 1;
        pthread_create(&pCtx->encode_thread[i], NULL, encode_ch, &pCtx->ch[i]);
      }
    }
  }
  
  while(1)
  {
    int encoding = 0;
    if(pCtx->video_enabled)
    {
      for(i = 0;i < pCtx->ch_cnt; i++)
      {
        if(pCtx->encoding[i])
        {
          encoding = 1;
          break;
        }
      }
      if(encoding)
      {
        usleep(1000*100);
        continue;
      }
    }
    

    if(pCtx->audio_enabled)
    { 
      if(pCtx->audio_processing)
      {
        usleep(1000*100);
        continue;
      }
    }

    if(encoding || pCtx->audio_processing)
    {
      usleep(1000*100);
      continue;
    }
    else
    {
      break;
    }

    if(received_sigterm == 1)
          break;
  }

  pCtx->start = 0;
  endof_encode();
}

