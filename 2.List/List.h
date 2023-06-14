#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
#include "../Common.h"

typedef int DataType;

/**
 * 普通链表节点
 * @data 数据域
 * @next 指向下一个节点
 */
typedef struct node {
	DataType data;
	struct node* next;
} ListNode;

/**
 * 链表头节点，当前实现的链表没有加入此节点
 * @first 指向链表的第一个节点
 * @length 链表的长度，链表数据节点的个数
 */
typedef struct {
	ListNode* first;
	int length;
} List;

/**
 * 双向链表节点
 * @prev 指向前驱节点
 * @next 指向后继节点
 * @data 数据域
 */
typedef struct Node {
	DataType data;
	struct Node* prev;
	struct Node* next;
} DoubleListNode;

//用数组初始化一个链表
ListNode* List_FromArray(DataType* arr, size_t size);

//插入元素，前插法
ListNode* List_ForeInsert(ListNode* head, DataType data);

//插入元素，尾插法
ListNode* List_BackInsert(ListNode* head, DataType data);

//查找特定的元素
Status List_FindElem(ListNode* head, DataType data, DataType* container);

//遍历链表
void List_Traverse(ListNode* head);

//删除特定的元素
Status List_DeleteElem(ListNode** phead, DataType data);

//链表反转，面试常考
ListNode* List_Reverse(ListNode* head);

//销毁链表
void List_Destory(ListNode* head);
#endif //! __LIST_H__