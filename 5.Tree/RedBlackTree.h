#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

#include "../Common.h"

#define RBT_RED 0
#define RBT_BLACK 1

typedef int Color;

typedef struct rbtree_node {
    DataType data;
    Color color;
    struct rbtree_node* left;
    struct rbtree_node* right;
    struct rbtree_node* parent;
} RbTreeNode;

RbTreeNode* RBT_FromArray(DataType* arr, int size);
void RBT_Destory(RbTreeNode* root);
RbTreeNode* RBT_Insert(RbTreeNode* root, DataType data);
void RBT_Delete(RbTreeNode** root, DataType data);
RbTreeNode* RBT_Find(RbTreeNode* root, DataType data);
RbTreeNode* RBT_FindMin(RbTreeNode* root);
RbTreeNode* RBT_FindMax(RbTreeNode* root);
void RBT_LeftDown(RbTreeNode* node);
void RBT_RightDown(RbTreeNode* node);
void RBT_InsertRebalance(RbTreeNode* node);
RbTreeNode* RBT_DeleteReblance(RbTreeNode* node);
RbTreeNode* RBT_CreateNode(DataType data);
#endif // !__RED_BLACK_TREE_H__