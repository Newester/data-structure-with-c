
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

TreeNode* BST_FromArray(DataType* arr, int size) {
    if(NULL == arr) {
        perror("invalid arguments");
        return NULL;
    }
    TreeNode* root = NULL;
    for(int i = 0; i < size; i++) {
        if(OK != BST_Insert(&root, arr[i])) {
            BinaryTree_Destroy(&root);
            return NULL;
        }
    }
    return root;
}

void BinaryTree_Destroy(TreeNode* root) {
    if(NULL != root) {
        if(NULL != root->left) {
            BinaryTree_Destroy(root->left);
        }
        if(NULL != root->right) {
            BinaryTree_Destroy(root->right);
        }
        free(root);
    }
}

int BinaryTree_GetHeight(TreeNode* root) {
	int l = 0, r = 0;
	if(NULL == root) {
		return 0;
	}

	if(NULL == root->left) {
		l = 0;
	}
	else {
		l = BinaryTree_GetHeight(root->left);
	}
	if(NULL == root->right) {
		r = 0;
	}
	else {
		r = BinaryTree_GetHeight(root->right);
	}
	return l > r ? (l+1) : (r+1);
}

void BinaryTree_PreOrderTraverse(TreeNode* root) {
    if(NULL != root) {
        printf("visit: %d\n", root->data);
        BinaryTree_PreOrderTraverse(root->left);
        BinaryTree_PreOrderTraverse(root->right);
    }
}
void BinaryTree_InOrderTraverse(TreeNode* root) {
    if(NULL != root) {
        BinaryTree_InOrderTraverse(root->left);
        printf("visit: %d\n", root->data);
        BinaryTree_InOrderTraverse(root->right);
    }
}
void BinaryTree_PostOrderTraverse(TreeNode* root) {
    if(NULL != root) {
        BinaryTree_PostOrderTraverse(root->left);
        BinaryTree_PostOrderTraverse(root->right);
        printf("visit: %d\n", root->data);
    }
}
void BinaryTree_LevelOrderTraverse(TreeNode* root) {

}

TreeNode* BST_Find(TreeNode* root, DataType data) {
    if(NULL == root) {
        return NULL;
    }
    else if(data == root->data) {
        return root;
    } else if(data < root->data) {
        return BST_Find(root->left, data);
    } else {
        return BST_Find(root->right, data);
    }
}

TreeNode* BST_Insert(TreeNode* root, DataType data) {
    TreeNode* p = NULL;
    if(NULL == root || data == root->data) {
        p = (TreeNode* )malloc(sizeof(TreeNode));
        if(NULL == p) {
            perror("BST_Insert fail as malloc error");
            return NULL;
        }
        if (NULL == root) {
            return p;
        } else {
            return root;
        }
    } else if(data < root->data) {
        return BST_Insert(root->left, data);
    } else {
        return BST_Insert(root->right, data);
    }
}

TreeNode* BST_Delete(TreeNode* root, DataType data) {
    if(NULL == root) {
        return NULL;
    } else if(data < root->data) {
        return BST_Delete(root->left, data);
    } else if(data > root->data) {
        return BST_Delete(root->right, data);
    } else {
        if(NULL == root->left) {
            TreeNode* right = root->right;
            free(root);
            return right;
        } else if(NULL == root->right) {
            TreeNode* left = root->left;
            free(root);
            return left;
        } else {
            TreeNode* left_max = BST_FindMax(root->left);
            root->data = left_max->data;
            root->left = BST_Delete(left_max, left_max->data);
            return root;
        }
    }
}

TreeNode* BST_FindMin(TreeNode* root) {
    if(NULL == root) {
        return NULL;
    }
    while(NULL != root->left) {
        root = root->left;
    }
    return root;
}
TreeNode* BST_FindMax(TreeNode* root) {
    if(NULL == root) {
        return NULL;
    }
    while(NULL != root->right) {
        root = root->right;
    }
    return root;
}

TreeNode* AVL_LeftDown(TreeNode* ub) {
    TreeNode* p = ub->right;
    ub->right = p->left;
    p->left = ub;
    return p;
}

TreeNode* AVL_RightDown(TreeNode* ub) {
    TreeNode* p = ub->left;
    ub->left = p->left;
    p->right = ub;
    return p;
}

TreeNode* AVL_Insert(TreeNode* root, DataType data) {
    if(root == NULL || data == root->data) {
        if(root == NULL) {
            TreeNode* p = (TreeNode* )malloc(sizeof(TreeNode));
            if(NULL == p) {
                perror("AVL_Insert fail as malloc error");
                return NULL;
            }
            p->data = data;
            p->left = NULL;
            p->right = NULL;
            return p;
        } else {
            return root;
        }
    } else {
        if(data < root->data) {
            root = AVL_Insert(root->left, data);
        } else {
            root = AVL_Insert(root->right, data);
        }
        int minus = BinaryTree_GetHeight(root->left) - BinaryTree_GetHeight(root->right);
        if(minus > 1) {
            if(BinaryTree_GetHeight(root->left->left) < BinaryTree_GetHeight(root->left->right)) {
                root->right = AVL_LeftDown(root->right);
            }
            root = AVL_RightDown(root);
        } else if(minus < -1) {
            if(BinaryTree_GetHeight(root->right->left) > BinaryTree_GetHeight(root->right->right)) {
                root->left = AVL_RightDown(root->left);
            }
            root = AVL_LeftDown(root);
        }
        return root;
    }
}
TreeNode* AVL_Delete(TreeNode* root, DataType data) {
    if(NULL == root) {
        return NULL;
    }
    if(data == root->data) {
        if(NULL == root->left) {
            root = root->right;
        } else if(NULL == root->right) {
            root = root->left;
        }
        else {
            TreeNode* p = BST_FindMax(root->left);
            root->data = p->data;
            root->left = AVL_Delete(root->left, p->data);
        }
    } else if(data < root->data) {
        root->left = AVL_Delete(root->left, data);
    } else {
        root->right = AVL_Delete(root->right, data);
    }
    int minus = BinaryTree_GetHeight(root->left) - BinaryTree_GetHeight(root->right);
    if(minus > 1) {
        if(BinaryTree_GetHeight(root->left->left) < BinaryTree_GetHeight(root->left->right)) {
            root->right = AVL_LeftDown(root->right);
        }
        root = AVL_RightDown(root);
    } else if(minus < -1) {
        if(BinaryTree_GetHeight(root->right->left) > BinaryTree_GetHeight(root->right->right)) {
            root->left = AVL_RightDown(root->left);
        }
        root = AVL_LeftDown(root);
    } 
}

TreeNode* AVL_FromArray(DataType* arr, int size) {
    TreeNode* root = NULL;
    TreeNode* new_root = NULL;
    for(int i = 0; i < size; i++) {
        new_root = AVL_Insert(root, arr[i]);
        if(NULL == new_root) {
            BinaryTree_Destroy(root);
            return NULL;
        }
        root = new_root;
    }
    return root; 
}