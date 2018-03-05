#include<stdio.h>
#include<stack>
#include<iostream>
using namespace std;

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

// 中序遍历（非递归）
// 根据中序遍历的顺序，对于任一结点，优先访问其左孩子，而左孩子结点又可以看做一根结点，
// 然后继续访问其左孩子结点，直到遇到左孩子结点为空的结点才进行访问，然后按相同的规则访
// 问其右子树。因此其处理过程如下：
// 1.若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对当前结点P再进行相同的处理；
// 2.若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的P置为栈顶结点的右孩子；
// 3.直到P为NULL并且栈为空则遍历结束
void in_order_tree_walk_2(struct TreeNode *x){
    stack<TreeNode*> s;
    TreeNode *p=x;
    while(p!=NULL||!s.empty()){ // 栈或指针非空
        //1.若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对当前结点P再进行相同的处理；
        while(p!=NULL){ // 访问左孩子
            s.push(p);
            p=p->left;
        }
        //2.若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的P置为栈顶结点的右孩子；
        if(!s.empty()){ // 栈非空 访问右孩子
            p=s.top();
            cout<<p->data<<" ";
            s.pop();
            p=p->right;
        }
    }    
}