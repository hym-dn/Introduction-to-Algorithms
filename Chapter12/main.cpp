#include<stdio.h>

// 二叉树结构
struct TreeNode{
    unsigned int data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
};

// 中序遍历(递归)
void in_order_tree_walk(struct TreeNode *x){
    if(0==x){
        return;
    }
    in_order_tree_walk(x->left); // 左
    printf("%ld\n",x->data); // 根
    in_order_tree_walk(x->right); // 右
}

