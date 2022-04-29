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
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include "hal_comm.h"
#include "hal_wifi.h"

#define EN_MONITOR_FUNC     (0)
#define WIFI_CTRL_IFACE     "/var/run/wpa_supplicant/wlan0"

#define SOCKET_PORT         (8080)
#define LOCAL_WIFI_ETH      "wlan0"
#define LOCAL_WIFI_IP       "192.168.137.103"
#define TARGET_AP_IP        "192.168.137.1"
#define K510_CRB_STR        "I am k510 crb"

static int wifi_connect_to_ap (const char *ssid, size_t ssid_len, 
            const char *psk, size_t psk_len, enc_type_e type);
static int wifi_talk_to_svr (char *server_ip, char *local_ip);

static void usage (char *cmd)
{
    printf ("%s <AP name> <password> <local ip> <server ip (if need talk to svr)> \n", cmd);
    printf ("example:\n");
    printf ("\t%s mywifi 123456 192.168.137.103 192.168.137.1\n", cmd);
}

int main (int argc, char **argv)
{
    int ret = -1;
    char *server_ip = NULL;

    if (4 > argc)
    {
        usage (*argv);
        goto EXIT;
    }

    char *ssid = *(argv + 1);
    int ssid_len = strnlen(ssid, 64);
    char *psk = *(argv + 2);
    int psk_len = strnlen(psk, 64);
    char *local_ip = *(argv + 3);
    if(argc > 4)
        server_ip = *(argv + 4);

    printf ("AP name:\t%s\n"
            "password:\t%s\n"
            "server ip:\t%s\n"
            "local ip:\t%s\n",
            ssid, psk, server_ip, local_ip);
    
    ret = wifi_connect_to_ap (ssid, ssid_len, psk, psk_len, ENC_WPA);
    if (0 != ret)
    {
        ret = -1;
        goto EXIT;
    }
    else if(NULL == server_ip)
    {
        goto EXIT;
    }

    ret = wifi_talk_to_svr (server_ip, local_ip);
    if (0 != ret)
    {
        ret = -1;
        goto EXIT;
    } 

    ret = 0;

EXIT:
    if(ret == 0)
        printf("RESULT:PASS\n");
    else
        printf("RESULT:FAIL\n");
    return ret;
}

static int g_exit = 0;
static int wifi_connect_to_ap (const char *ssid, size_t ssid_len, 
            const char *psk, size_t psk_len, enc_type_e type)
{
    int ret = -1;



#if (EN_MONITOR_FUNC == 1)
    pthread_t id_monitor;
    ret = pthread_create (&id_monitor, NULL, wifi_monitor_thr, NULL);
    if (0 != ret)
    {
        dbgmsg ("create wifi_monitor_thr thread failed: %s\n", strerror(errno));
        goto EXIT;
    }
#endif

    void *handle = NULL;

    handle = hal_wifi_open (WIFI_CTRL_IFACE, IFACE_REQUEST, 0666);
    if (NULL == handle)
    {
        dbgmsg ("RESULT:FAIL:open %s failed\n", WIFI_CTRL_IFACE);
        ret = HAL_FAILURE;
        goto EXIT;
    }

    char reply[4096];
    size_t reply_len = sizeof(reply);
    wpa_scan_t scan;
    wpa_connet_t connect;

    do
    {
        memset (reply, 0x00, sizeof(reply));
        reply_len = sizeof(reply) - 1;

        memset (&scan, 0x00, sizeof(wpa_scan_t));
        scan.reply = reply;
        scan.reply_len = &reply_len;

        ret = hal_wifi_scan (handle, &scan);
        if (0 == ret)
        {
            printf ("------ scan result ------\n");
            printf ("%s\n", reply);
        }
        else
        {
            dbgmsg ("RESULT:FAIL:scan wifi failed\n");
            ret = HAL_FAILURE;
            continue;
        }

        memset (&connect, 0x00, sizeof(wpa_connet_t));
        connect.ssid = ssid;
        connect.ssid_len = ssid_len;
        connect.psk = psk;
        connect.psk_len = psk_len;
        connect.enc_type = type;
        
        ret = hal_wifi_connect (handle, &connect);
        if (HAL_SUCCESS != ret)
        {
            dbgmsg ("RESULT:FAIL:connect wifi failed\n");
            ret = HAL_FAILURE;
            continue;
        }
    } while (0);

EXIT:
    hal_wifi_close (handle);
    g_exit = 1;
#if (EN_MONITOR_FUNC == 1)
    printf ("wait thread exit ...\n");
    pthread_join (id_monitor, NULL);
    printf ("wifi_monitor_thr exit\n");
#endif
    return ret;
}

#if (EN_MONITOR_FUNC == 1)
static void *wifi_monitor_thr (void *param)
{
    int ret = -1;
    char reply[2048];
    size_t reply_len = sizeof(reply);

    ret = hal_wifi_open (WIFI_CTRL_IFACE, IFACE_MONITOR);
    if (HAL_SUCCESS != ret)
    {
        dbgmsg ("open %s failed\n", WIFI_CTRL_IFACE);
        ret = HAL_FAILURE;
        goto EXIT;
    }

    while (!g_exit)
    {
        memset (reply, 0x00, sizeof(reply));
        reply_len = sizeof(reply);

        ret = hal_wifi_monitor (reply, &reply_len, NULL);
        if (0 == ret)
        {
            printf ("%s\n", reply);
        }
        else
        {
            dbgmsg ("monitor wifi failed\n");
            ret = HAL_FAILURE;
            continue;
        }
    }

EXIT:
    hal_wifi_close (WIFI_CTRL_IFACE, IFACE_MONITOR);
    pthread_exit (NULL);
}
#endif

static int is_valid_ip (const char *ipaddr)  
{  
    char str[31], temp[31];  
    int a, b, c, d;  
    memset (&temp, 0x00, sizeof(temp));
    memset (&str, 0x00, sizeof(str));
    if (sscanf (ipaddr, "%d.%d.%d.%d ", &a, &b, &c, &d) == 4 
        && a >= 0 && a <= 255 && b >= 0 && b <= 255 
        && c >= 0 && c <= 255 && d >= 0 && d <= 255)  
    {  
        sprintf (temp, "%d.%d.%d.%d", a, b, c, d ); //把格式化的数据写入字符串temp  
        if (strcmp (temp, ipaddr) == 0)  
        {  
            return 1; //success  
        }  
        else  
        {  
            return -1;  
        }
    }
    else  
    {  
        return -1;  
    }  

    return -1;  
}   

static int set_local_ip (const char* eth, char *ip)
{
	int ret = -1;
	int sock = -1;
	struct sockaddr_in *sin = NULL;
	struct ifreq ifr;

	if (eth == NULL || ip == NULL)
	{
		dbgmsg ("eth or ip is NULL\n");
		ret = -1;
		goto EXIT;
	}
	
	sock = socket (AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		dbgmsg ("socket error: %s\n", strerror(errno));
		ret = -1;
		goto EXIT;
	}

	memset(&ifr, 0x00, sizeof(ifr));
	strncpy(ifr.ifr_name, eth, IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ-1] = '\0';

	sin = (struct sockaddr_in *)(&ifr.ifr_addr);
	sin->sin_family = AF_INET;

	ret = inet_aton (ip, &(sin->sin_addr));
	if(ret < 0)
	{
		ret = -1;
		dbgmsg ("inet_aton error\n");
		goto EXIT;
	}

	ret = ioctl (sock, SIOCSIFADDR, &ifr);
	if(ret < 0)
	{
		dbgmsg ("ioctl error: %s\n", strerror(errno));
		ret = -1;
		goto EXIT;
	}

EXIT:
	if(sock > 0)
		close(sock);
	return ret;
}

static int wifi_talk_to_svr (char *server_ip, char *local_ip)
{
    int ret = -1;
    int sock = -1;

    if (!is_valid_ip (server_ip))
    {
        dbgmsg ("invalid ip %s\n", server_ip);
        ret = -1;
        goto EXIT;
    }

    if (!is_valid_ip (local_ip))
    {
        dbgmsg ("invalid ip %s\n", local_ip);
        ret = -1;
        goto EXIT;
    }

    ret = set_local_ip (LOCAL_WIFI_ETH, local_ip);
    if (0 != ret)
    {
        dbgmsg ("set %s ip to %s failed\n", LOCAL_WIFI_ETH, local_ip);
        goto EXIT;
    }

	struct sockaddr_in svr_addr;
    socklen_t svr_addrlen;

	svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr (server_ip);
	svr_addr.sin_port = htons (SOCKET_PORT);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        dbgmsg ("Ceate sock failed: %s\n", strerror(errno));
        ret = -1;
        goto EXIT;
    }

    int enable = 1; 
    ret = setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)); 
    if (ret != 0)
    {
        dbgmsg ("setsockopt sock SO_REUSEADDR failed: %s\n", strerror(errno));
        ret = -1;
        goto EXIT;
    }

    svr_addrlen = sizeof(struct sockaddr_in);
    int try_num = 5;
    while (try_num-- > 0)
    {
        sleep (1);
        ret = connect (sock, (struct sockaddr *)&svr_addr, svr_addrlen);
        if (0 != ret)
        {
            dbgmsg ("connect to server %s failed\n", server_ip);
            ret = -1;
            continue;
        }
        else
            break;
    }
    if (0 != ret)
        goto EXIT;

    char recv_msg[2048];
    char send_msg[2048];
    
    memset (send_msg, 0x00, sizeof(send_msg));
    sprintf (send_msg, "%s", K510_CRB_STR);
    while (1)
    {
        ret = send (sock, send_msg, sizeof(send_msg), 0);
        if (0 > ret)
        {
            dbgmsg ("send failed: %s\n", strerror(errno));
            sleep (1);
            continue;
        }

        memset (recv_msg, 0x00, sizeof(recv_msg));
        ret = recv (sock, recv_msg, sizeof(recv_msg), 0);
        if (0 > ret)
        {
            dbgmsg ("recvfrom failed: %s\n", strerror(errno));
            continue;
        }
        else if (sizeof(recv_msg) < ret)
        {
            dbgmsg ("the recv message length (%d) is greater than buffer length(%ld)\n", ret, sizeof(recv_msg));
            recv_msg[sizeof(recv_msg) - 1] = 0x00;
        }

        printf ("%s\n", recv_msg);
        memset (send_msg, 0x00, sizeof(send_msg));
        sprintf (send_msg, "%s %s", recv_msg, K510_CRB_STR);
    }

    ret = 0;
EXIT:
    if (0 < sock)
    {
        shutdown(sock, SHUT_RDWR);
	    close(sock);
        sock = -1;
    }

    return ret;
}