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
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
        int fd, retval;
        struct rtc_time rtc_tm;

        unsigned long data;
        int year, month, day, hour, minute, second;

        if(argc !=3) {
                fprintf(stdout, "useage:\t ./rtc year-month-day hour:minute:second\n");
                fprintf(stdout, "example: ./rtc 2021-10-11 19:54:30\n");  
                return -1;    
        }

        sscanf(argv[1], "%d-%d-%d",  &year, &month, &day);
        sscanf(argv[2], "%d:%d:%d",  &hour, &minute, &second);  

        fprintf(stdout, "Input date/time: %02d/%02d/%d %02d:%02d:%02d\n", day, month, year,  hour, minute, second);

        rtc_tm.tm_year = year - 1900,
        rtc_tm.tm_mon   =  month - 1;
        rtc_tm.tm_mday  =  day;

        rtc_tm.tm_hour= hour; 
        rtc_tm.tm_min = minute;
        rtc_tm.tm_sec = second;

  	fd = open("/dev/rtc0", O_RDWR);
        if (fd == -1) {
                printf("RESULT:FAIL /dev/rtc0 %s",strerror(errno));
                exit(errno);
        }

         /* Write the RTC time/date */
        retval = ioctl(fd, RTC_SET_TIME, &rtc_tm);
        if (retval == -1) {
                printf("RESULT:FAIL ioctl %s",strerror(errno));
                exit(errno);
        }
        
        /* Read the RTC time/date */
        retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
        if (retval == -1) {
                printf("RESULT:FAIL ioctl %s",strerror(errno));
                exit(errno);
        }

        fprintf(stdout, "RTC date/time: %d/%d/%d %02d:%02d:%02d\n",
                rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
        fprintf(stdout, " Sleep 2s\n");

        sleep(2);

        retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
        if (retval == -1) {
                printf("RESULT:FAIL ioctl %s",strerror(errno));
                exit(errno);
        } 

        fprintf(stdout, "RTC date/time: %d/%d/%d %02d:%02d:%02d\n",
                rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        #if 0
        // Setting alarm time
        rtc_tm.tm_sec += 15;
        if (rtc_tm.tm_sec >= 60) {
                rtc_tm.tm_sec %= 60;
                rtc_tm.tm_min++;
        }
        if (rtc_tm.tm_min == 60) {
                rtc_tm.tm_min = 0;
                rtc_tm.tm_hour++;
        }
        if (rtc_tm.tm_hour == 24)
                rtc_tm.tm_hour = 0;

        // Setting alarm
        retval = ioctl(fd, RTC_ALM_SET, &rtc_tm);
        if (retval == -1) {
                perror("ioctl");
                exit(1);
        }
        fprintf(stdout,"RTC alarm time set to: %02d:%02d:%02d.\n",
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

        /* Enable alarm interrupts after setting*/
        retval = ioctl(fd, RTC_AIE_ON, 0);
        if (retval == -1) {
                perror("ioctl");
                exit(1);
        }
        // Wait alarm interrupt.
        retval = read(fd, &data, sizeof(unsigned long));
        if (retval == -1) {
                perror("read");
                exit(1);
        }

        fprintf(stdout, "alarm interrupt arrive (0x%lx) \n", data);

        retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
        if (retval == -1) {
                perror("ioctl");
                exit(errno);
        }

        fprintf(stdout, "\nRTC date/time: %d/%d/%d %02d:%02d:%02d\n",
                rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
                rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
        #endif

        close(fd);
        printf("RESULT:PASS\n");
        return 0;
}
