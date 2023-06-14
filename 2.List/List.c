#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

ListNode* List_FromArray(DataType* arr, size_t size) {
	if (NULL == arr) {
		perror("array is empty");
		return NULL;
	}
	ListNode* head = NULL;
	ListNode* new_head = NULL;
	for(size_t i = 0; i < size; i++) {
		new_head = List_BackInsert(head, arr[i]);
		if (NULL == new_head) {
			printf("List_BackInsert error: %d\n", arr[i]);
			List_Destory(head);
			return NULL;
		}
		head = new_head;
	}
	return head;
}

ListNode* List_ForeInsert(ListNode* head, DataType data) {

	ListNode* p = (ListNode*)malloc(sizeof(*p));
	if(NULL == p) {
		perror("List_ForeInsert fail as malloc fail");
		return NULL;
	}
	p->data = data;
	p->next = NULL;
    
	p->next = head;
	return p;
}

ListNode* List_BackInsert(ListNode* head, DataType data) {

	ListNode* p = (ListNode*)malloc(sizeof(*p));
	if(NULL == p) {
		perror("List_ForeInsert fail as malloc fail");
		return NULL;
	}
	p->data = data;
	p->next = NULL;

	if(NULL == head)
		return p;
	
	ListNode* q = head;
	while(NULL != q->next)
		q = q->next;
	q->next = p;
	
	return head;
}

Status List_FindElem(ListNode* head, DataType data, DataType* container) {
	if(NULL == container) {
		perror("Container does not exist");
		return ERROR;
	}
	while(NULL != head && data != head->data)
		head = head->next;
	if(NULL == head) {
		container = NULL;
		return FALSE;
	}
	else {
		*container = head->data;
		return TRUE;
	}
}

void List_Traverse(ListNode* head) {
	while(NULL != head) {
		printf("%d\t", head->data);
		head = head->next;
	}
	printf("\n");
}

Status List_DeleteElem(ListNode** phead, DataType data) {
	ListNode* p = *phead;
	ListNode* prev = NULL;
	while( p != NULL && p->data != data) {
		prev = p;
		p = p->next;
	}

	if(NULL == p)
		return FALSE;
	if(*phead == p) {
		*phead = (*phead)->next;
		free(p);
	}
	else {
		prev->next = p->next;
		free(p);
	}

	return TRUE;
}
ListNode* List_Reverse(ListNode* head) {
	ListNode* prev = NULL;
	ListNode *curr = head;
	ListNode* next = NULL;

	while(NULL != curr && NULL != curr->next) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	curr->next = prev;

	return curr;
}

void List_Destory(ListNode* head) {
	ListNode* next = NULL;
	ListNode* p = head;
	if(NULL != p) {
		next = p->next;
		free(p);
		p = p->next;
	}
}

int main(int argc, char* argv[]) {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	ListNode* list = List_FromArray(arr, 8);
	list = List_ForeInsert(list, 0);
	list = List_BackInsert(list, 9);
	List_Traverse(list);
	int c = -1;
	if (TRUE == List_FindElem(list, 5, &c)) {
		printf("element found: %d\n", c);
		List_DeleteElem(&list, 5);
		List_Traverse(list);
	}
	list = List_Reverse(list);
	List_Traverse(list);
}

