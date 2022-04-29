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
#include "server.h"

sem_t sem_send_data;

int main(int argc, char **argv)
{
	//defien var for socket connection
	int listen_sockfd = 0, client_sockfd = 0;
	int listen_len = 0, client_len = 0;
	struct sockaddr_in listen_address, client_address;
	//define for response thread
	thread_args *response_args, *response_head;
	pthread_t thread_id;

	listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sockfd <= 0) {
		perror("Create socketfd error");
		exit(EXIT_FAILURE);
	}

	listen_address.sin_family = AF_INET;
	listen_address.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_address.sin_port = htons(TEST_PORT);
	listen_len = sizeof(listen_address);

	if(bind(listen_sockfd, (struct sockaddr *)&listen_address, listen_len) < 0) {
		perror("Bind error");
		exit(EXIT_FAILURE);
	}

	if(listen(listen_sockfd, 10) < 0) {
		perror("Listen error");
		exit(EXIT_FAILURE);
	}

	char *send_buff = malloc_packet();
	if(send_buff == NULL) {
		printf("Malloc error\n");
		exit(EXIT_FAILURE);
	}

	//init the link list head
	if((response_head = (thread_args *)malloc(sizeof(thread_args))) == NULL) {
		printf("Thread args malloc failed.\n");
		close(listen_sockfd);
		exit(EXIT_FAILURE);
	}

	response_head->data_pointer = NULL;
	response_head->client_sockfd = -1;
	response_head->packet_count = -1;
	response_head->thread_seq = -1;
	response_head->next = NULL;

	if(sem_init(&sem_send_data, 0, 0) != 0) {
		printf("Init semaphore failed\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&(response_head->thread_id), NULL, thread_count, (void *)response_head) != 0) {
		perror("Thread count create failed");
		close(listen_sockfd);
		free(response_head);
		exit(EXIT_FAILURE);
	}

	int thread_seq = 0;
	client_len = sizeof(client_address);
	while(1) {
		printf("Server waiting.\n");
		client_sockfd = accept(listen_sockfd, (struct sockaddr *)&client_address, &client_len);
		if((response_args = (thread_args *)malloc(sizeof(thread_args))) == NULL) {
			printf("Thread args malloc failed.\n");
			close(listen_sockfd);
			break;
		}

		response_args->thread_seq = thread_seq++;
		response_args->client_sockfd = client_sockfd;
		response_args->packet_count = 0;
		response_args->data_pointer = send_buff;
		response_args->next = response_head->next;
		response_head->next = response_args;

		//create thread for send data to client_sockfd
		if(pthread_create(&(response_args->thread_id), NULL, thread_response, (void *)response_args) != 0) {
			perror("Thread response create failed");
			break;
		}
	}
	close(listen_sockfd);
//start free all source used in program
	response_args = response_head->next;
	while(response_args != NULL) {
		response_head->next = response_args->next;
		free(response_args);
		response_args->next = response_head->next;
	}
	free(response_head);
	free(send_buff);

	exit(EXIT_SUCCESS);
}

float calculate_speed(thread_args *list_head)
{
	float speed = 0.0;
	thread_args *cnt_p = list_head->next;
	long total_cnt = 0;
	int client_num = 0;

	while(cnt_p != NULL) {
		total_cnt += cnt_p->packet_count;
		printf("No.%d client count packet:%ld.\n", cnt_p->thread_seq, cnt_p->packet_count);
		cnt_p->packet_count = 0;
		cnt_p = cnt_p->next;
	}

	printf("Total length:%ldbytes. ", total_cnt);
	speed = ((float)(total_cnt * MTU_NUM) / (1024*1024)) / (float)COUNT_CYCLE;

	return speed;
}

void *thread_response(void *arg)
{
	thread_args *internal_args = (thread_args *)arg;
	internal_args->packet_count = 0;
	int sem_status = 0;

	pthread_detach(pthread_self());
	printf("Server the client,fd:%d. Thread No.%d.\n", internal_args->client_sockfd, internal_args->thread_seq);
	while(1) {
		sem_getvalue(&sem_send_data, &sem_status);
		if(sem_status == 0) {
			continue;
		}
		else {
			int wr_res = send(internal_args->client_sockfd, internal_args->data_pointer, MTU_NUM, 0);
			if(wr_res == 0) {
				printf("Disconnected!\n");
				break;
			}
			else if(wr_res < 0) {
				perror("Error in connection");
				break;
			}
			(internal_args->packet_count)++;
		}
	}

	close(internal_args->client_sockfd);
	pthread_exit("");
}

inline int timer_cmp(struct timeval start, struct timeval end)
{
	if((end.tv_sec - start.tv_sec) >= COUNT_CYCLE)
		return 1;
	else return 0;
}

char *malloc_packet()
{
	char *malloc_res = NULL;

	malloc_res = (char *)malloc(MTU_NUM * sizeof(char));
	if(malloc_res == NULL)
		return (char *)NULL;
	memset(malloc_res, '0', MTU_NUM);
	return malloc_res;
}

void *thread_count(void *arg)
{
	thread_args *internal_args = (thread_args *)arg;
	long packet_count = 0;
	//define var for timing
	struct timeval start_time, sample_time;
	float tran_speed = 0.0;

	pthread_detach(pthread_self());
	sem_post(&sem_send_data);
	gettimeofday(&start_time, NULL);//start timing
	
	while(1) {
		gettimeofday(&sample_time, NULL);
		if(timer_cmp(start_time, sample_time)) {
			sem_wait(&sem_send_data);
			if((tran_speed = calculate_speed(internal_args)) > 0) {
				printf("Sample timing:%ds, Transmittion speed:%.2fMb/s\n", COUNT_CYCLE, tran_speed);
			}
			else {
				printf("Speed count error.\n");
			}
			packet_count = 0;
			gettimeofday(&start_time, NULL);
			sem_post(&sem_send_data);
		}
	}
	pthread_exit("");
}
