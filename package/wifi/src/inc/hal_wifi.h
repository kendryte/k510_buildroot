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
#ifndef __HAL_WIFI__
#define __HAL_WIFI__

#ifdef _cplusplus
extern "C" {
#endif

typedef void (*callback_func_t)(char *msg, size_t len);

typedef enum 
{
    IFACE_REQUEST = 0,
    IFACE_MONITOR,
    IFACE_ENUM_END
} iface_type_e;

typedef struct
{
    const char *cmd;
    size_t cmd_len;
    char *reply;
    size_t *reply_len;
} wpa_request_t;

typedef struct
{
    char *reply;
    size_t *reply_len;
} wap_monitor_t;

typedef enum 
{
    ENC_WPA = 0,
    ENC_WEP,
    ENC_NONE,
    ENC_ENUM_END
} enc_type_e;

typedef struct 
{
    const char *ssid;
    size_t ssid_len;
    const char *psk;
    size_t psk_len;
    int enc_type;
    char res[32];
} wpa_connet_t;

typedef struct
{
    char *reply;
    size_t *reply_len;
} wpa_scan_t;

void *hal_wifi_open (const char* iface, int type, mode_t mode);
void hal_wifi_close (void *handle);
int hal_wifi_request (void *handle, wpa_request_t *request);
int hal_wifi_monitor (void *handle, wap_monitor_t *monitor, callback_func_t cb);
int hal_wifi_connect (void *handle, wpa_connet_t *connect);
int hal_wifi_scan (void *handle, wpa_scan_t *scan);

#ifdef _cplusplus
}
#endif

#endif /*__HAL_WIFI__*/