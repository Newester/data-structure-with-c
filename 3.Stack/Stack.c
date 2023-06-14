#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack* Stack_Create(int capacity) {
	if (capacity <= 0) {
		perror("stack capacity should be a positive integer");
		return NULL;
	}
	Stack *s = (Stack*)malloc(sizeof(Stack));
	if(NULL == s) {
		perror("Stack_Create failed as malloc failed");
		return NULL;
	}
	s->array = (DataType*)calloc(capacity,sizeof(DataType));
	if(NULL == s->array) {
		free(s);
		s = NULL;
		perror("Stack_Create failed as calloc failed");
		return NULL;
	}
	s->capacity = capacity;
	s->top = -1;
	return s;
}

void Stack_Destroy(Stack *s) {
	if (NULL != s) {
		if (NULL != s->array) {
			free(s->array);
		}
		free(s);
	}
}

void Stack_Clear(Stack* s) {
	if(NULL != s) {
		s->top = -1;
	}
}

Status IsEmpty(Stack* s) {
	if(NULL == s) {
		return ERROR;
	}
	if(-1 == s->top) {
		return TRUE;
	}
	return FALSE;
}

Status IsFull(Stack* s) {
	if(NULL == s) {
		return ERROR;
	}
	if(s->top == s->capacity - 1) {
		return TRUE;
	}
	return FALSE;
}

Status Stack_Push(Stack *s, DataType elem) {
	if(NULL == s) {
		return ERROR;
	}
	if(TRUE == IsFull(s)) {
		perror("Push failed because stack is full");
		return ERROR;
	}
	s->top++;
	s->array[s->top] = elem;
	return OK;
}

void Stack_Pop(Stack *s)
{
	if(NULL == s || IsEmpty(s) == TRUE)
	{
		s->top--;
	}

}

Status Stack_GetTop(Stack* s, DataType* container) {
	if(NULL == s || NULL == container) {
		return ERROR;
	}
	*container = s->array[s->top];
	for(int i = 0; i <= s->top; i++) {
		printf("%d\t", s->array[i]);
	}
	printf("\n");
	return OK;
}

int main(int argc, char* argv[]) {
	Stack* s = Stack_Create(3);
	Stack_Push(s, 1);
	Stack_Push(s, 2);
	Stack_Push(s, 3);
	DataType d = 4;
	Stack_GetTop(s, &d);
	printf("stack top is %d\n", d);
	if(TRUE == IsFull(s)) {
		printf("stack is full\n");
		Stack_Clear(s);
		if (TRUE == IsEmpty(s)) {
			printf("stack is empty\n");
		}
	}
}