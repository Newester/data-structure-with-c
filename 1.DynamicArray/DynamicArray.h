#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include "../Common.h"

#define DEFAULT_SIZE 10

typedef int ElementType;
typedef struct {
	ElementType* array;
	int size;
	int capacity;
} DynamicArray;

DynamicArray* DynamicArray_Init(void);

void DynamicArray_Destory(DynamicArray* arr);


Status DynamicArray_IsEmpty(DynamicArray* arr);

Status DynamicArray_IsFull(DynamicArray* arr);

Status DynamicArray_AddElem(DynamicArray* arr,ElementType elem);

Status DynamicArray_GetElemByIndex(DynamicArray* arr, unsigned int index,ElementType* container);

Status DynamicArray_DeleteElemByIndex(DynamicArray* arr, unsigned int index);

void DynamicArray_Traverse(DynamicArray* arr);

Status DynamicArray_Enlarge(DynamicArray* arr);


#endif // __DYNAMICARRAY_H__

