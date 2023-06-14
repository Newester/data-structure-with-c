#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DynamicArray.h"

DynamicArray* DynamicArray_Init() {
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	if(NULL == arr) {
		perror("DynamicArray_Init failed as malloc failed");
		exit(OVERFLOW);
	}

	arr->array = (ElementType*)calloc(DEFAULT_SIZE, sizeof(ElementType));
	if(NULL == arr->array) {
		perror("DynamicArray_Init failed as calloc failed");
		exit(OVERFLOW);
	}
	arr->size = 0;
	arr->capacity = DEFAULT_SIZE;
	return arr;
}

Status DynamicArray_IsEmpty(DynamicArray* arr) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(0 == arr->size) {
		return TRUE;
	}
	return FALSE;
}

Status DynamicArray_IsFull(DynamicArray* arr) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(arr->capacity == arr->size) {
		return TRUE;
	}
	return FALSE;
}

Status DynamicArray_Enlarge(DynamicArray* arr) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(arr->size < arr->capacity) {
		printf("DynamicArray is not full yet\n");
		return ERROR;
	}
	ElementType* newArray = (ElementType* )calloc((arr->capacity)*2, sizeof(ElementType));
	if(NULL == newArray) {
		perror("DynamicArray_Enlarge failed as calloc failed");
		return ERROR;
	}
	memcpy(newArray, arr->array, (arr->size) * sizeof(ElementType));
	free(arr->array);
	arr->array = newArray;
	arr->capacity *= 2;
	return OK;
}

Status DynamicArray_AddElem(DynamicArray* arr, ElementType elem) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(TRUE == DynamicArray_IsFull(arr)) {
		int ret = DynamicArray_Enlarge(arr);
		if(ERROR == ret) {
			perror("DynamicArray_AddElem failed as DynamicArray_Enlarge failed");
			return ERROR;
		}
	}
	arr->array[arr->size] = elem;
	arr->size++;
	return OK;
}

Status DynamicArray_GetElemByIndex(DynamicArray* arr, unsigned int index, ElementType* container) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(0 == arr->size) {
		perror("DynamicArray is empty");
		return ERROR;
	}
	if(NULL == container) {
		perror("Container does not exist");
		return ERROR;
	}
	if(index > arr->size -1) {
		perror("index does not exist");
		return ERROR;
	}
	// ! ElementType需要是基本数据类型，如不是此处需memcpy
	*container = arr->array[index];
	return OK;
}

Status DynamicArray_DeleteElemByIndex(DynamicArray* arr, unsigned int index) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return ERROR;
	}
	if(0 == arr->size) {
		perror("DynamicArray is empty");
		return ERROR;
	}
	if(index > arr->size -1) {
		perror("index does not exist");
		return ERROR;
	}
	// ! ElementType需要是基本数据类型，如不是此处需memcpy
	if(index != arr->size -1) {
		int i = index;
		while(i != arr->size -1) {
			arr->array[i] = arr->array[i+1];
			i++;
		}
		arr->size--;
	}
	return OK;
}

void DynamicArray_Traverse(DynamicArray* arr) {
	if(NULL == arr) {
		perror("DynamicArray does not exist");
		return;
	}
	int i = arr->size;
	while(0 != i) {
		// ! 此处由于ElementType被定义为int，故可以这样输出，如为其他情况需要另外实现
		printf("%d\t",arr->array[i-1]);
		i--;
	}
	printf("\n");
}

void DynamicArray_Destory(DynamicArray* arr){
	if(NULL == arr) {
		return;
	}
	if(0 != arr->capacity) {
		free(arr->array);
		arr->array = NULL;
	}
	free(arr);
}


int main(int argc, char* argv[]) {
	DynamicArray* arr = DynamicArray_Init();
	for(ElementType i = 0; i < 20; i++) {
		if (OK != DynamicArray_AddElem(arr, i)) {
			break;
		}
	}
	DynamicArray_Traverse(arr);
}