
#ifndef __STACK_H__
#define __STACK_H__

#include "../Common.h"

typedef struct  {
	int capacity;
	int top;
	DataType* array;
} Stack;

Stack* Stack_Create(int capacity);
void Stack_Destroy(Stack *s);
void Stack_Clear(Stack* s);
Status IsEmpty(Stack* s);
Status IsFull(Stack* s);

Status Stack_Push(Stack *s, DataType elem);
void Stack_Pop(Stack *s);
Status Stack_GetTop(Stack* s, DataType* container);
#endif // __STACK_H__