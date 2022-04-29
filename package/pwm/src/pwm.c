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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>

#define dbmsg(fmt, args ...) printf("%s[%d]: "fmt"\n", __FUNCTION__, __LINE__,##args)	//__FILE__,

int fd_period = 0,fd_duty = 0,fd_enable = 0,duty_m = 0;

int pwm_setup(char *period,char *duty_ratio,char num)
{
  int fd,ret;
  char pwm_num[64];
  char pwm_chip[64];
  char pwm_period[64];
  char pwm_duty[64];
  char pwm_enable[64];
  if(0 == num)
  {
    sprintf(pwm_num, "/sys/class/pwm/pwmchip%d/export", num);
    sprintf(pwm_chip, "/sys/class/pwm/pwmchip0/pwm0%d", num);
    sprintf(pwm_period, "/sys/class/pwm/pwm0%d/period", num);
    sprintf(pwm_duty, "/sys/class/pwm/pwm0%d/duty_cycle", num);
    sprintf(pwm_enable, "/sys/class/pwm/pwm0%d/enable", num);
  }
  else if(1 == num)
  {
    sprintf(pwm_num, "/sys/class/pwm/pwmchip%d/export", num + 2);
    sprintf(pwm_chip, "/sys/class/pwm/pwmchip3/pwm%d0", num + 2);
    sprintf(pwm_period, "/sys/class/pwm/pwm%d0/period", num + 2);
    sprintf(pwm_duty, "/sys/class/pwm/pwm%d0/duty_cycle", num + 2);
    sprintf(pwm_enable, "/sys/class/pwm/pwm%d0/enable", num + 2);
  }
  else
  {
    printf("输入的pwm标号不支持\n");
    return -1;
  }
  fd = open(pwm_num, O_WRONLY);
  if(fd < 0)
  {
      dbmsg("open export error\n");
      return -1;
  }
  if((access(pwm_chip,F_OK))==-1)
  {
    ret = write(fd, "0", strlen("0"));
    if(ret < 0)
    {
        dbmsg("creat pwm error\n");
        return -1;
    }else
      dbmsg("export pwm ok\n");
  }

  fd_period = open(pwm_period, O_RDWR);
  fd_duty = open(pwm_duty, O_RDWR);
  fd_enable = open(pwm_enable, O_RDWR);

  if((fd_period < 0)||(fd_duty < 0)||(fd_enable < 0))
  {
      dbmsg("open error\n");
      return -1;
  }

  ret = write(fd_period, period,strlen(period));
  if(ret < 0)
  {
      dbmsg("change period error\n");
      return -1;
  }else
    dbmsg("change period ok\n");

  ret = write(fd_duty, duty_ratio, strlen(duty_ratio));
  if(ret < 0)
  {
      dbmsg("change duty_cycle error\n");
      return -1;
  }else
    dbmsg("change duty_cycle ok\n");

  ret = write(fd_enable, "1", strlen("1"));
  if(ret < 0)
  {
      dbmsg("enable pwm error\n");
      return -1;
  }else
    dbmsg("enable pwm ok\n");

  return 0;
}

int main ( int argc, char *argv[] )
{
  if(argc != 4)
  {
    printf("请输入周期、正采样（单位为ns）\n");
    return -1;
  }
  int num = atoi(argv[3]);
  printf("%s---%s\n",argv[1],argv[2]);
  pwm_setup(argv[1],argv[2],num);
  return 0;
}
