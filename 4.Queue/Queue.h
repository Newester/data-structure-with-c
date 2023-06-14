#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../Common.h"


typedef struct node {
	DataType data;
	struct node* next;
} QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
	unsigned int size;
} Queue;

Queue* Queue_New(void);

void Queue_Destory(Queue* queue);

void Queue_Clear(Queue* queue);

Status Queue_IsEmpty(Queue* queue);

int Queue_GetSize(Queue* queue);

Status Queue_EnQueue(Queue* queue,DataType elem);

Status Queue_DeQueue(Queue* queue, DataType* container);

void Queue_Traverse(Queue* queue);

#endif // __QUEUE_H__