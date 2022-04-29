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

#include "sequeue.h"

sequeue_t *CreateEmptySequeue(void)
{
	sequeue_t *queue;
	queue = (sequeue_t *)malloc(sizeof(sequeue_t));
	if (NULL == queue) return NULL;
	
	queue->front = queue->rear = 0;
 
	return queue;
}

void DestroySequeue(sequeue_t *queue)
{
	if (NULL != queue) 
	{
		free(queue);
	}
}

int EmptySequeue(sequeue_t *queue)
{
	if (NULL == queue) 
		return -1;
 
	return (queue->front == queue->rear ? 1 : 0);
}

int FullSequeue(sequeue_t *queue)
{
	if (NULL == queue) return -1;
 
	return ((queue->rear + 1) % N == queue->front ? 1 : 0);
}

void ClearSequeue(sequeue_t *queue)
{
	if (NULL == queue) return;
	
	queue->front = queue->rear = 0;
 
	return;
}

int EnQueue(sequeue_t *queue, data_t x)
{
	if (NULL == queue) return - 1;
 
	if (1 == FullSequeue(queue)) return -1; /* full */
 
	queue->rear = (queue->rear + 1) % N;
	queue->data[queue->rear] = x;
 
	return 0;
}

int DeQueue(sequeue_t *queue, data_t *x)
{
	if (NULL == queue) return -1;
 
	if (1 == EmptySequeue(queue)) return -1; /* empty */
 
	queue->front = (queue->front + 1) % N;
 
	if (NULL != x) {
		*x = queue->data[queue->front];
	}
 
	return 0;
}