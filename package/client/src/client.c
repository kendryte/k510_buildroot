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
#include "client.h"

char* server_ip = NULL; 
int main(int argc, char **argv)
{
	//define var for thread
	if(argc < 2)
	{
		printf("please input server ip\n");
	}
	server_ip = argv[1];
	pthread_t thread_receive_id[CLIENT_MAX_NUM];
	
	printf("Creating thread..\n");
	for(int id_num = 0; id_num < CLIENT_MAX_NUM; ++id_num) {
		if(pthread_create(&thread_receive_id[id_num], NULL, thread_receive, (void *)&id_num) != 0) {
			perror("Thread create failed");
			exit(EXIT_FAILURE);
		}
	}

	printf("Thread create finished. Test running...\n");
	while(1) {
		sleep(10);
		printf("Main process.\n");
	}

	printf("Client process exit.\n");
	exit(EXIT_SUCCESS);
}

void *thread_receive(void *arg)
{
	int seq_num = *(int *)arg;
	int local_sockfd = 0, local_len = 0;
	struct sockaddr_in local_address;

	int rd_res = 0;
	char *recv_buff = NULL;

	if((local_sockfd = socket(AF_INET, SOCK_STREAM, 0 )) < 0) {
		perror("Create socket failed:");
		exit(EXIT_FAILURE);
	}

	local_address.sin_family = AF_INET;
	local_address.sin_addr.s_addr = inet_addr(server_ip);
	local_address.sin_port = htons(TEST_PORT);
	local_len = sizeof(local_address);

	if((recv_buff = malloc_packet()) == NULL) {
		printf("Malloc receive buff error.\n");
		pthread_exit("");
	}
	memset(recv_buff, 0, MTU_NUM);

	if(connect(local_sockfd, (struct sockaddr *)&local_address, local_len) < 0) {
		perror("Connect error");
		free(recv_buff);
		pthread_exit("");
	}

	printf("Connect successfully,seq_num:%d, id:%ld\n", seq_num, pthread_self());

	while(1) {
		rd_res = recv(local_sockfd, recv_buff, MTU_NUM, 0);
		if(rd_res == 0) {
			printf("Disconnected, thread seq:%d", seq_num);
			break;
		}
		else if(rd_res < 0) {
			perror("Receive error");
			break;
		}
	}

	free(recv_buff);
	printf("Thread exit, seq:%d\n", seq_num);
	pthread_exit("");
}

char *malloc_packet()
{
	char *malloc_res = NULL;

	malloc_res = (char *)malloc(MTU_NUM * sizeof(char));
	if(malloc_res == NULL) {
		return (char *)NULL;
	}

	memset(malloc_res, 0, MTU_NUM);
	return malloc_res;
}
