#include "RedBlackTree.h"

#include <stdio.h>
#include <stdlib.h>

// https://blog.csdn.net/m0_62405272/article/details/122631653
// 红黑树：黑红，黑根，黑哨，黑子，黑高
// 插入删除：不出双红，不损黑高；先修树高，再修黑高

static RbTreeNode nilobj = {
    .color = RBT_BLACK,
    .parent = NULL,
    .left = NULL,
    .right = NULL,
};
static RbTreeNode* nil = &nilobj;

RbTreeNode* RBT_CreateNode(DataType data) {
    RbTreeNode* node = (RbTreeNode* )malloc(sizeof(RbTreeNode));
    if(NULL == node) {
        return NULL;
    }
    node->data = data;
    node->color = RBT_RED;
    node->parent = NULL;
    node->left = nil;
    node->right = nil;
    return node;
}

RbTreeNode* RBT_FromArray(DataType* arr, int size) {
    RbTreeNode* root = NULL;
    RbTreeNode* new_root= NULL;
    for(int i = 0; i < size; i++) {
        new_root = RBT_Insert(root, arr[i]);
        if(NULL == new_root) {
            RBT_Destory(root);
            return NULL;
        }
        root = new_root;
    }
    return root;
}

void RBT_Destory(RbTreeNode* root) {
    if(NULL != root && root != nil) {
        if(root->left != nil) {
            RBT_Destory(root->left);
        }
        if(root->right != nil) {
            RBT_Destory(root->right);
        }
        free(root);
    }
}
/*
 * 红黑树插入需将新节点标为红色，因此不会影响黑高，但是如果其父节点也是红色，可能出现双红，则需要配平
*/
RbTreeNode* RBT_Insert(RbTreeNode* root, DataType data) {
    if(NULL == root || root == nil) {
        root = RBT_CreateNode(data);
        if(NULL == root) {
            return NULL;
        }
        root->color = RBT_BLACK;
        return root;
    }
    RbTreeNode* curr = root;
    while(1) {
        if(data == curr->data) {
            return root;
        }
        else if(data < curr->data) {
            if(curr->left == nil) {
                break;
            } else {
                curr = curr->left;
            }
        } else /* data > curr->data */ {
            if(curr->right == nil) {
                break;
            } else {
                curr = curr->right;
            }
        }
    }
    RbTreeNode* node = RBT_CreateNode(data);
    if(NULL == node) {
        return NULL;
    }
    if(data < curr->data) {
        curr->left = data;
    } else {
        curr->right = data;
    }
    if(RBT_BLACK == curr->color) {
        return root;
    }
    RBT_InsertRebalance(node);
    return root;
}

/* 红黑树的删除，首先看待删节点是否有子树，待删节点是叶子节点没有子树；待删节点有子树，此时在子树中必有前驱或后继节点是叶子节点，可以转化为删前驱或后继节点
 * 转换为删叶子节点后，如果被删叶子节点是红色则可直接删除；最终归结为删除黑色叶子节点后的再平衡问题。
 * 删除黑色叶子节点后，被删节点所在分支的树高黑高都减小1，出现不平衡；要进行旋转和重绘，修复的顺序是，先修树高(AVL)，再修黑高，再修双红
 * 按照父节点、兄节点、侄子节点的颜色和形态分别进行讨论；要注意两种情况：
 * 1. 父黑兄黑无子的品字结构，父节点无法配平，先将兄弟节点涂红，再让爷爷节点去配平
 * 2. 父黑兄红侄黑侄孙红的情况，会出现双红形态，可按照插入节点出现双红的情况去配平
*/
void RBT_Delete(RbTreeNode** root, DataType data) {
    if(NULL == root || NULL == *root || *root == nil) {
        return;
    }
    if(data < (*root)->data) {
        RBT_Delete((*root)->left, data);
    } else if(data > (*root)->data) {
        RBT_Delete((*root)->right, data);
    } else {
        if((*root)->left != nil || (*root)->right != nil) {
            if((*root)->left != nil) {
                RbTreeNode* left_max = RBT_FindMax((*root)->left);
                (*root)->data = left_max->data;
                RBT_Delete(left_max, left_max->data);
                return root;
            } else {
                RbTreeNode* right_min = RBT_FindMin((*root)->right);
                (*root)->data = right_min->data;
                RBT_Delete(right_min, right_min->data);
                return root;
            }
        } else {
            RbTreeNode* parent = (*root)->parent;
            RbTreeNode* node = root;
            if(NULL == parent) {
                free(root);
                *root = NULL;
            }

            // --> NULL != parent
            Color parent_color = parent->color;
            Color delete_color = (*root)->color;
            int delete_left = 0;
            if(parent->left == root) {
                parent->left = nil;
                delete_left = 1;
            } else {
                parent->right = nil;
            }
            free(root);
            if(RBT_RED  == delete_color) {
            } else /* RBT_BLACK == root->color */ {
                RbTreeNode* brother = NULL;
                if(0 == delete_left) {
                    brother = parent->left;
                } else {
                    brother = parent->right;
                }
                // 先修树高，再修黑高; 先保证局部再寻求整体
                if(brother->left == nil && brother->right == nil) /* 兄弟节点没有孩子 */ {
                    // 兄弟节点没有孩子，删除节点后树高是平衡的
                    if(RBT_RED == parent_color) {
                        parent->color = RBT_RED;
                        brother->color = RBT_BLACK;
                    } else {
                        // 父亲节点是黑色，父亲节点不平衡，此时需看爷爷节点
                        brother->color = RBT_RED;
                        RBT_DeleteReblance(parent->parent);
                    }
                } else if(brother->left == nil) /* 兄弟节点只有右孩子 */ {
                    if(1 == delete_left) /* RR */ {
                        RBT_LeftDown(parent);
                        if(RBT_RED == parent->color) {
                        } else {
                            if(RBT_RED == brother->color) {
                                brother->color = RBT_BLACK;
                            } else {
                                brother->right->color = RBT_BLACK;
                            }
                        }
                    } else /* LR */ {
                        RBT_LeftDown(brother);
                        RBT_RightDown(parent);
                        if(RBT_RED == parent->color) {
                            parent->color = RBT_BLACK;
                        } else {
                            if(RBT_RED == brother->color) {
                                brother->color = RBT_BLACK;
                            } else {
                                brother->parent->color = RBT_BLACK;
                            }
                        }
                    }
                } else if(brother->right == nil) /* 兄弟节点只有左孩子 */ {
                    if(0 == delete_left) /* LL */ {
                        RBT_RightDown(parent);
                        if(RBT_RED == parent->color) {
                        } else {
                            if(RBT_RED == brother->color) {
                                brother->color = RBT_BLACK;
                            } else {
                                if(RBT_RED == brother->color) {
                                    brother->color = RBT_BLACK;
                                } else {
                                    brother->left->color = RBT_BLACK;
                                }
                            }
                        }
                    } else /* RL */ {
                        RBT_RightDown(brother);
                        RBT_LeftDown(parent);
                        if(RBT_RED == parent->color) {
                            parent->color = RBT_BLACK;
                        } else {
                            if(RBT_RED == brother->color) {
                                brother->color = RBT_BLACK;
                            } else {
                                brother->parent->color = RBT_BLACK;
                            }
                        }
                    }
                } else /* 兄弟节点有两个孩子 */ {
                    RbTreeNode* nephew = NULL;
                    if(1 == delete_left) {
                        RBT_LeftDown(parent);
                        nephew = brother->right;
                    } else {
                        RBT_RightDown(parent);
                        nephew = brother->left;
                    }
                    if(RBT_RED == parent_color) {
                        parent->color = RBT_BLACK;
                        brother->color = RBT_RED;
                        nephew->color = RBT_BLACK;
                    } else /* RBT_BLACK == parent_color */ {
                        if(RBT_BLACK == brother->color) {
                            // 父亲节点是黑色，被删叶子节点是黑色，兄弟节点是黑色，两个侄子节点必然是红色
                            nephew = RBT_BLACK;
                        } else {
                            // 父亲节点是黑色，被删叶子节点是黑色，兄弟节点是红色，两个侄子节点必然是黑色
                            RbTreeNode* parent_child = NULL;
                            if(1 == delete_left) {
                                RBT_LeftDown(parent);
                                parent_child = parent->right;
                            } else {
                                RBT_RightDown(parent);
                                parent_child = parent->left;
                            }
                            parent->color = RBT_RED;
                            if(RBT_RED == parent_child->color) {
                                RBT_InsertRebalance(parent_child);
                            }
                        }
                    }
                }
            }
        }
    }
}
RbTreeNode* RBT_Find(RbTreeNode* root, DataType data) {
    if(NULL == root || root == nil) {
        return NULL;
    }
    while(root != nil) {
        if(data == root->data) {
            return root;
        } else if(data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}
RbTreeNode* RBT_FindMin(RbTreeNode* root) {
    if(NULL == root || root == nil) {
        return NULL;
    }
    while(root->left != nil) {
        root = root->left;
    }
    return root;
}
RbTreeNode* RBT_FindMax(RbTreeNode* root) {
    if(NULL == root || root == nil) {
        return NULL;
    }
    while(root->right != nil) {
        root = root->right;
    }
    return root;
}

void RBT_LeftDown(RbTreeNode* node) {
    RbTreeNode* up = node->parent;

    RbTreeNode* tmp = node->right;

    node->right = tmp->left;
    node->right->parent = node;

    tmp->left = node;
    node->parent = tmp;

    tmp->parent = up;
    if(NULL != up) {
        if(up->left == node) {
            up->left = tmp;
        } else {
            up->right = tmp;
        }
    }
}
void RBT_RightDown(RbTreeNode* node) {
    RbTreeNode* up = node->parent;

    RbTreeNode* tmp = node->left;
    
    node->left = tmp->right;
    node->left->parent = node;

    tmp->right = node;
    node->parent = tmp;

    tmp->parent = up;
    if(NULL != up) {
        if(up->left == node) {
            up->left = tmp;
        } else {
            up->right = tmp;
        }
    }

}
void RBT_InsertRebalance(RbTreeNode* node) {
    if(NULL != node) {
        if(NULL == node->parent) {
            node->color = RBT_BLACK;
            return;
        }
        if(NULL == node->parent->parent) {
            return;
        }
        RbTreeNode* grandpa = node->parent->parent;
        RbTreeNode* parent = node->parent;
        RbTreeNode* uncle = NULL;
        int grandpa_left = 0;
        int iam_left = 0;

        if(grandpa->left == node->parent) {
            grandpa_left = 1;
            uncle = grandpa->right;
        } else {
            uncle = grandpa->left;
        }
        if(RBT_RED == uncle->color) {
            parent->color = RBT_BLACK;
            uncle->color = RBT_BLACK;
            grandpa->color = RBT_RED;
            RBT_InsertRebalance(grandpa);
        } else {
            if(parent->left == node) {
                iam_left = 1;
            }
            if(1 == grandpa_left && 1 == iam_left) {
                RBT_RightDown(grandpa);
                parent->color = RBT_BLACK;
                grandpa->color = RBT_RED;
            } else if(0 == grandpa_left && 0 == iam_left) {
                RBT_LeftDown(grandpa);
                parent->color = RBT_BLACK;
                grandpa->color = RBT_RED;
            } else if(1 == grandpa_left && 0 == iam_left) {
                RBT_RightDown(parent);
                RBT_LeftDown(grandpa);
                node->color = RBT_BLACK;
                grandpa->color = RBT_RED;
            } else {
                RBT_LeftDown(parent);
                RBT_RightDown(grandpa);
                node->color = RBT_BLACK;
                grandpa->color = RBT_RED;
            }
        }
    }
}
RbTreeNode* RBT_DeleteReblance(RbTreeNode* node) {
    return NULL;
}