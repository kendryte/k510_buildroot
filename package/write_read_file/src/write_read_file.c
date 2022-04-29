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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#define LEN 1024*1024*5

//返回当前距离1970年的毫秒数
int64_t Get_Systime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t t = ((int64_t)tv.tv_sec)*1000 + tv.tv_usec / 1000;
  // t = time(NULL);
  return t;
}

int main(int argc,char** argv)
{
  int ret = 0;
  int interupt = 0;
  char str_file[40];
  char write_str[LEN];
  long write_len = 512*1024;
  time_t t1,t2;
  int count = 200;
  int i = 0,k = 0;
  float write_speed = 0.0,read_speed = 0.0;
  FILE *fp_write,*fp_read;
  if(argc != 2)
  {
    printf("RESULT:FAIL:Please input test file egg. /root/data/test.txt \n");
    return 0;
  }
  if(strlen(argv[1]) > 39)
  {
    printf("file name is too long\n");
    return 0;
  }
  sprintf(str_file,"%s",argv[1]);

  printf("str_file = %s\n",str_file);

  fp_write=fopen(str_file, "wb");
  if(NULL==fp_write)
  {
    printf("RESULT:FAIL:Can't open file\n");
    return -1;
  }    
  while(i++)
  {
    if(i = write_len - 1)
    {
      write_str[write_len - 1] = '\0';
      break;
    }
    write_str[i] = rand() % 100 + 1;
  }

  printf("Begin test write file speed\n");

  t1 = Get_Systime();

  while(i++ < count){
    fwrite(write_str, sizeof(char), LEN, fp_write);
  }  
  t2 = Get_Systime();

  write_speed = (float)(count*LEN/1024/1024)*1000/(t2-t1);
  printf("write spped is %0.3f m/s\n",write_speed);
  fclose(fp_write);


  fp_read=fopen(str_file, "rb");
  if(NULL==fp_read)
  {
    printf("RESULT:FAIL:Can't open file\n");
    return -1;
  }

  printf("Begin test read file speed\n");

  t1 = Get_Systime();
  char *read_str = malloc(1024*sizeof(char));

  while(k++ < count*1024){
    if(fread(read_str, sizeof(char), 1024, fp_read)!=1024)
    {
      if(feof(fp_read))
        printf("End of file");
      else
        printf("Read error");                         
    }
  } 
  t2 = Get_Systime();

  read_speed = (float)(count*1024*1024/1024/1024)*1000/(t2-t1);
  printf("read speed is %0.3f m/s\n",read_speed);
  fclose(fp_read);
  printf("RESULT:PASS:read speed is %0.3f m/s and write speed is %0.3f\n",read_speed,write_speed);
  return 0;
}
