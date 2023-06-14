
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

Queue* Queue_New(void) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if(NULL == queue) {
		perror("Queue_Init() failed as malloc failed");
		return NULL;
	}
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}

void Queue_Destory(Queue* queue) {
	if(NULL == queue) {
		return;
	}
	if(0 == queue->size) {
		free(queue);
		queue = NULL;
		return;
	}
	QueueNode* node = queue->front;
	QueueNode* next = NULL;
	while(NULL != node) {
		next = node->next;
		free(node);
		node = next;
	}
	queue->size = 0;
	free(queue);
	queue = NULL;

}

void Queue_Clear(Queue* queue) {
	if(NULL == queue) {
		return;
	}
	if(0 == queue->size) {
		return;
	}
	QueueNode* node = queue->front;
	QueueNode* next = NULL;
	while(NULL != node) {
		next = node->next;
		free(node);
		node = next;
	}
	queue->size = 0;
}

Status Queue_IsEmpty(Queue* queue) {
	if(NULL == queue) {
		return ERROR;
	}
	if( 0 == queue->size) {
		return TRUE;
	}
	return FALSE;
}

int Queue_GetSize(Queue* queue) {
	if(NULL == queue) {
		perror("QUeue_GetSize() failed as queue is empty");
		return -1;
	}
	return queue->size;
}

Status Queue_EnQueue(Queue* queue, DataType elem) {
	if(NULL == queue) {
		perror("Queue_EnQueue() failed as queue is empty");
		return ERROR;
	}
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	if(NULL == node) {
		perror("Queue_EnQueue() failed as malloc failed");
		return ERROR;
	}
	if(0 == queue->size) 
	{
		queue->front = queue->rear = node;
	}
	else {
		queue->rear->next = node;
		queue->rear = node;		
	}
	queue->size++;
	return OK;
}

Status Queue_DeQueue(Queue* queue, DataType* container) {
	if(NULL == queue || NULL == container) {
		perror("Queue_DeQueue failed as illegal parameters");
		return ERROR;
	}
	if(0 == queue->size) {
		perror("Queue_DeQueue failed as queue is empty");
		return ERROR;
	}
	*container = queue->front->data;
	if(1 == queue->size) {
		free(queue->front);
		queue->front = queue->rear = NULL;
	}
	else {
		QueueNode* node = queue->front;
		queue->front = node->next;
		node->next = NULL;
		free(node);
		node = NULL;
	}
	queue->size--;

}

void Queue_Traverse(Queue* queue) {
	if(NULL != queue) {
		QueueNode* node = queue->front;
		while(node) {
			printf("%d\t",node->data);
		}
		printf("\n");
	}
}