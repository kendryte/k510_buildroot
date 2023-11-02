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
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#include "wpa_ctrl.h"
#include "hal_comm.h"
#include "hal_wifi.h"

#define dbgmsg(fmt, ...) printf("%s:%s[%d]: " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

typedef struct
{
    struct wpa_ctrl *wpa_ctrlp;
    mutex_t mutex;
    int type;
    char res[16];
} wpa_handle_t;

void *hal_wifi_open (const char* iface, int type, mode_t mode)
{
    int ret = -1;

    int num = 1;
    wpa_handle_t *handle = (wpa_handle_t *) calloc (num, sizeof(wpa_handle_t));
    if (NULL == handle)
    {
        dbgmsg ("calloc memory %lu bytes failed\n", num * sizeof(wpa_handle_t));
        goto EXIT;
    }

    handle->wpa_ctrlp = wpa_ctrl_open (iface);
    if (NULL == handle->wpa_ctrlp)
    {
        dbgmsg ("open %s failed: %s\n", iface, strerror(errno));
        free_mem (handle);
        goto EXIT;
    }

    if (IFACE_MONITOR == type)
    {
        ret = wpa_ctrl_attach (handle->wpa_ctrlp);
        if (0 != ret)
        {
            dbgmsg ("attach %s failed: %s\n", iface, strerror(errno));
            wpa_ctrl_close (handle->wpa_ctrlp);
            handle->wpa_ctrlp = NULL;
            free_mem (handle);
            goto EXIT;
        }
    }

    handle->type = type;
    mutex_init (handle->mutex);
EXIT:
    return (void *)handle;
}

void hal_wifi_close (void *handle)
{
    if (NULL == handle)
    {
        dbgmsg ("handle is NULL\n");
        return;
    }

    wpa_handle_t *_handle = (wpa_handle_t *) handle;
 
    if (IFACE_MONITOR == _handle->type)
    {
        if (0 != wpa_ctrl_detach (_handle->wpa_ctrlp))
        {
            dbgmsg ("attach failed: %s\n", strerror(errno));
        }
    }

    wpa_ctrl_close (_handle->wpa_ctrlp);
    _handle->wpa_ctrlp = NULL;
    mutex_deinit (_handle->mutex);
    free_mem (_handle);
    return;
}

int hal_wifi_request (void *handle, wpa_request_t *request)
{
    int ret = HAL_FAILURE;
    

    if (NULL == handle || NULL == request)
    {
        dbgmsg ("handle or request is NULL\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    if (NULL == request->cmd || 0 >= request->cmd_len 
        || NULL == request->reply || 0 >= *request->reply_len)
    {
        dbgmsg ("parameter is invalid, pointer is NULL or length less than zero\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    wpa_handle_t *_handle = (wpa_handle_t *) handle;
    mutex_lock (_handle->mutex);
    ret = wpa_ctrl_request (_handle->wpa_ctrlp, request->cmd, request->cmd_len, 
            request->reply, request->reply_len, NULL);
    if (0 != ret)
    {
        mutex_unlock (_handle->mutex);
        dbgmsg ("%s failed: %s\n", request->cmd, strerror(errno));
        ret = HAL_FAILURE;
        goto EXIT;
    }
    mutex_unlock (_handle->mutex);

    ret = HAL_SUCCESS;
EXIT:
    return ret;
}

int hal_wifi_monitor (void *handle, wap_monitor_t *monitor, callback_func_t cb)
{
    int ret = HAL_FAILURE;

    if (NULL == handle || NULL == monitor)
    {
        dbgmsg ("handle or monitor is NULL\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    if (NULL == monitor->reply || 0 >= *monitor->reply_len)
    {
        dbgmsg ("parameter is invalid, pointer is NULL or length less than zero\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    wpa_handle_t *_handle = (wpa_handle_t *) handle;

    if (wpa_ctrl_pending (_handle->wpa_ctrlp) > 0)
    {
        mutex_lock (_handle->mutex);
        ret = wpa_ctrl_recv (_handle->wpa_ctrlp, monitor->reply, monitor->reply_len);
        if (0 == ret)
        {
            if (NULL != cb)
            {
                cb (monitor->reply, *monitor->reply_len);
            }
        }
        else
        {
            mutex_unlock (_handle->mutex);
            dbgmsg ("recv wpa failed: %s\n", strerror(errno));
            ret = HAL_FAILURE;
        }
        mutex_unlock (_handle->mutex);
    }

    ret = HAL_SUCCESS;
EXIT:
    return ret;
}

int hal_wifi_connect (void *handle, wpa_connet_t *connect)
{
    int ret = HAL_FAILURE;
    char *cmd = NULL;

    if (NULL == handle || NULL == connect)
    {
        dbgmsg ("handle or connect is NULL\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    size_t max_cmd_len = ((connect->psk_len > connect->ssid_len)?(connect->psk_len):(connect->ssid_len)) + 128;
    cmd = (char *) calloc (max_cmd_len, sizeof(char));
    if (NULL == cmd)
    {
        dbgmsg ("malloc memory length %lu failed: %s\n", max_cmd_len, strerror(errno));
        ret = HAL_FAILURE;
        goto EXIT;
    }

    char reply[2048];
    size_t reply_len = sizeof(reply) - 1;

    size_t cmd_len = 0;
    char *cmd_sequence[] = {
        "ADD_NETWORK",
        "SET_NETWORK %d ssid \"%s\"",
        "SET_NETWORK %d key_mgmt NONE",
        "SET_NETWORK %d psk \"%s\"",
        "ENABLE_NETWORK %d",
        /*"SAVE_CONFIG"*/
    };

    int net_id = 0;
    int i = 0;

    for (i = 0; i < sizeof(cmd_sequence) / sizeof(char *); i++)
    {
        memset (cmd, 0x00, max_cmd_len);
        memset (reply, 0x00, sizeof(reply));
        reply_len = sizeof(reply) - 1;

        switch (i)
        {
            case 0:
                cmd_len = sprintf (cmd, cmd_sequence[i]);
                break;
            case 1:
                cmd_len = sprintf (cmd, cmd_sequence[i], net_id, connect->ssid);
                break;
            case 2:
                if (ENC_WPA == connect->enc_type)
                {
                    continue;
                }
                cmd_len = sprintf (cmd, cmd_sequence[i], net_id);
                break;
            case 3:
                if (ENC_NONE == connect->enc_type)
                {
                    continue;
                }
                cmd_len = sprintf (cmd, cmd_sequence[i], net_id, connect->psk);
                break;
            case 4:
                cmd_len = sprintf (cmd, cmd_sequence[i], net_id);
                break;
            case 5:
                cmd_len = sprintf (cmd, cmd_sequence[i]);
                break;
            default:
                dbgmsg ("cmd index %d overrange\n", i);
                ret = HAL_FAILURE;
                goto EXIT;
                break;
        }

        wpa_handle_t *_handle = (wpa_handle_t *) handle;
        wpa_request_t request;
        memset (&request, 0x00, sizeof(wpa_request_t));
        request.cmd = cmd;
        request.cmd_len = cmd_len;
        request.reply = reply;
        request.reply_len = &reply_len;
        
        ret = hal_wifi_request (_handle, &request);
        if (HAL_SUCCESS != ret)
        {
            dbgmsg ("cmd %s failed\n", cmd);
            ret = HAL_FAILURE;
            goto EXIT;
        }
        printf ("%s %s\n", cmd, reply);

        if (!strcmp(cmd, "ADD_NETWORK"))
        {
            net_id = atoi (reply);
        }
    }

    ret = HAL_SUCCESS;
EXIT:
    free_mem (cmd);
    return ret;
}

int hal_wifi_scan (void *handle, wpa_scan_t *scan)
{
    int ret = HAL_FAILURE;

    if (NULL == handle || NULL == scan)
    {
        dbgmsg ("handle or scan is NULL\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }
    
    char cmd[128];
    size_t cmd_len = sizeof(cmd) - 1;
    size_t _reply_len = *scan->reply_len;

    char *cmd_sequence[] = {
        "SCAN",
        "SCAN_RESULTS"
    };

    wpa_handle_t *_handle = (wpa_handle_t *) handle;
    wpa_request_t request;
    memset (&request, 0x00, sizeof(wpa_request_t));

    int i = 0;
    for (i = 0; i < sizeof(cmd_sequence) / sizeof(char *); i++)
    {
        memset (cmd, 0x00, sizeof(cmd));
        cmd_len = sprintf (cmd, cmd_sequence[i]);
        memset (scan->reply, 0x00, _reply_len);
        *scan->reply_len = _reply_len;

        request.cmd = cmd;
        request.cmd_len = cmd_len;
        request.reply = scan->reply;
        request.reply_len = scan->reply_len;
 
        ret = hal_wifi_request (_handle, &request);
        if (HAL_SUCCESS != ret)
        {
            dbgmsg ("cmd %s failed\n", cmd);
            ret = HAL_FAILURE;
            goto EXIT;
        }

        if (!strcmp(cmd_sequence[i], "SCAN"))
        {
            sleep (2);
        }
    }

    ret = HAL_SUCCESS;
EXIT:
    return ret;
}
