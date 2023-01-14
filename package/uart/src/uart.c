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
#include "uart.h"

void SetOpt(int fd)
{
    static struct termios termold, termnew;
    tcgetattr(fd, &termold);
    bzero(&termnew, sizeof(termnew));

    termnew.c_iflag &= ~(ICRNL | IGNCR);
    termnew.c_cflag |= CLOCAL | CREAD;
    termnew.c_cflag &= ~CSIZE;
    termnew.c_cflag |= CS8;
    termnew.c_cflag &= ~PARENB;

    cfsetispeed(&termnew, B115200);
    cfsetospeed(&termnew, B115200);

    termnew.c_cflag &= ~CSTOPB;
    termnew.c_cc[VTIME] = 1; 
    termnew.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &termnew);
}

int OpenUart(char *UART_DEV)
{
    int fd = 0;
    fd = open(UART_DEV, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        return -1;
    }
    // SetOpt(fd);
    return fd;
}

int UartSend(int fd, uint8_t *SenBuff, long len)
{
    int TxLen;
    TxLen = write(fd, SenBuff, len);
    return TxLen;
}

int UartRead(int fd, uint8_t *RxBuff, long RxLen)
{
    int GetRxLen = 0;
    while (RxLen)
    {
        GetRxLen += read(fd, RxBuff + GetRxLen, 1);
        RxLen--;
    }
    // GetRxLen = read(fd, RxBuff, RxLen);
    return GetRxLen;
}

void UartClose(int fd)
{
    close(fd);
}

/*END*/

void main(int argc, char **argv)
{
    int fd = 0;
    int RxLen = 0;
    int flag = 0;

    uint8_t RxBuff[100];
    uint8_t send_str[50];
    char str_dev[30];
     if (argc != 2)
    {
      printf("Please input uart number 0、1\n");
      return 0;
    }
    printf("请输入要发送的内容:");
    scanf("%[^\n]", &send_str);
    if(strlen(send_str) >= 50)
    {
        printf("输入字符长度不得高于50字节\n");
        return;
    }
    int num = atoi(argv[1]);
    sprintf(str_dev, "/dev/ttyS%d", num);
    fd = open(str_dev, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        printf(" COM Open Fail !");
        return;
    }
    // SetOpt(fd);
    int TxLen = UartSend(fd, send_str, strlen(send_str));
    printf("\nTxLen = %d\n", TxLen);
    if (TxLen < 0)
    {
        printf("send error\n");
        goto exit;
    }
    while (1)
    {
        while (((RxLen = UartRead(fd, RxBuff, TxLen)) > 0))
        {
            printf("Rbuff = %s\n", (char *)RxBuff);
            flag = 1;
            break;
        }
        if (flag == 1)
            break;
    }
exit:
    tcflush(fd, TCIFLUSH);
    UartClose(fd);
}
