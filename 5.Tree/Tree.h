#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__
#include "../Common.h"

typedef struct node {
    struct node* left;
    struct node* right;
    DataType data;
} TreeNode;

#define RED 0
#define BLACK 1
typedef int NodeColor;

typedef struct rb {
    struct rb* parent;
    struct rb* left;
    struct rb* right;
    NodeColor color;
    DataType data;
} RbTreeNode;

int BinaryTree_GetHeight(TreeNode* root);
void BinaryTree_PreOrderTraverse(TreeNode* root);
void BinaryTree_InOrderTraverse(TreeNode* root);
void BinaryTree_PostOrderTraverse(TreeNode* root);
void BinaryTree_LevelOrderTraverse(TreeNode* root);
void BinaryTree_Destroy(TreeNode* root);

TreeNode* BST_FromArray(DataType* arr, int size);
TreeNode* BST_Insert(TreeNode* root, DataType data);
TreeNode* BST_Delete(TreeNode* root, DataType data);
TreeNode* BST_Find(TreeNode* root, DataType data);
TreeNode* BST_FindMin(TreeNode* root);
TreeNode* BST_FindMax(TreeNode* root);

TreeNode* AVL_FromArray(DataType* arr, int size);
TreeNode* AVL_Insert(TreeNode* root, DataType data);
TreeNode* AVL_Delete(TreeNode* root, DataType data);
TreeNode* AVL_LeftDown(TreeNode* ub);
TreeNode* AVL_RightRown(TreeNode* ub);

#endif // !__BINARY_SEARCH_TREE_H__