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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/watchdog.h>

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
int main(int argc, char **argv)
{
    int ret = 0;
    char *interupt = malloc(sizeof(char) * 10);
    char str_dev[30];
    int timeout;
    if (argc != 3)
    {
      printf("Please input watchdog number and timeout,watchdog0、watchdog1 or watchdog2\n");
      return 0;
    }
    int num = atoi(argv[1]);
    sprintf(str_dev, "/dev/watchdog%d", num);
    int Set_TimeOut = atoi(argv[2]);
    if(Set_TimeOut < 2 || Set_TimeOut > 60)
    {
      printf("SetTimeOut is Between 2 and 60\n");
      return 0;
    }
    printf("SetTimeOut is : %d \n",Set_TimeOut);
    int fd_watchdog = open(str_dev, O_WRONLY);
    if (fd_watchdog == -1)
    {
      printf("\n!!! FAILED to open /dev/watchdog\n");
    }

    
    ioctl(fd_watchdog, WDIOC_SETTIMEOUT, &Set_TimeOut );
    sleep(1);
    ioctl(fd_watchdog, WDIOC_GETTIMEOUT, &timeout);
    printf("timeout = %d\n",timeout);
    printf("Stop Watchdog Please Input stop : \n");
    while (1)
    {
      if (kbhit())
      {
        scanf("%4s", interupt);
      }
      if (strcmp("stop", interupt) != 0)
      {
        ret = write(fd_watchdog, "\0", 1);
        if (ret != 1)
        {
          ret = -1;
          break;
        }
        sleep(1);
      }
      else
      {
        return 0;
      }
    }

    close(fd_watchdog);
    return 0;
}
