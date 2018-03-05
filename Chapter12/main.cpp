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

struct BtNode{
    bool isfirst;
    struct TreeNode *btnode;
};

// 先序遍历（递归）
void pre_order_tree_walk(struct TreeNode *x){
    if(0==x){
        return;
    }
    printf("%ld\n",x->data); // 根SS
    in_order_tree_walk(x->left); // 左
    in_order_tree_walk(x->right); // 右
}

// 先序遍历（非递归）
// 根据前序遍历访问的顺序，优先访问根结点，然后再分别访问左孩子和右孩子。
// 即对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其
// 左孩子不为空，按相同规则访问它的左子树；当访问其左子树时，再访问它的
// 右子树。因此其处理过程如下：
// 对于任一结点P：
// 1.访问结点P，并将结点P入栈;
// 2.判断结点P的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，
//   并将栈顶结点的右孩子置为当前的结点P，循环至1);
//   若不为空，则将P的左孩子置为当前的结点P;
// 3.直到P为NULL并且栈为空，则遍历结束。
void pre_order_tree_walk_2(struct TreeNode *x){
    stack<TreeNode*> s;
    TreeNode *p=x;
    while(p!=NULL||!s.empty()){ // 栈或指针非空
        while(p!=NULL){ // 访问左孩子
            // 打印根
            cout<<p->data<<" ";
            s.push(p);
            p=p->left;
        }
        if(!s.empty()){ // 栈非空 访问右孩子
            p=s.top();
            s.pop();
            p=p->right;
        }
    }  
}

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

// 后序遍历（递归）
void post_order_tree_walk(struct TreeNode *x){
    if(0==x){
        return;
    }
    in_order_tree_walk(x->left); // 左
    in_order_tree_walk(x->right); // 右
    printf("%ld\n",x->data); // 根
}

// 后序遍历（非递归）
// 后序遍历的非递归实现是三种遍历方式中最难的一种。因为在后序遍历中，
// 要保证左孩子和右孩子都已被访问并且左孩子在右孩子前访问才能访问根结点，
// 这就为流程的控制带来了难题。下面介绍两种思路。
// 第一种思路：对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，
// 直到搜索到没有左孩子的结点，此时该结点出现在栈顶，但是此时不能将
// 其出栈并访问， 因此其右孩子还为被访问。所以接下来按照相同的规则对
// 其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，
// 此时可以将其出栈并访问。这样就 保证了正确的访问顺序。可以看出，在
// 这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才
// 能访问它。因此需要多设置一个变量标识该结点是 否是第一次出现在栈顶。
void post_order_tree_walk_2(struct TreeNode *x){
    stack<BtNode*> s;
    TreeNode *p=x;
    BtNode *temp;
    while(p!=NULL||!s.empty()){
        while(p!=NULL){// 沿左子树一直往下搜索，直至出现没有左子树的结点
            BtNode *btn=(BtNode *)malloc(sizeof(BtNode));
            btn->btnode=p;
            btn->isfirst=true;
            s.push(btn);
            p=p->left;
        }
        if(!s.empty()){
            temp=s.top();
            s.pop();
            if(temp->isfirst==true){ //表示是第一次出现在栈顶 
                temp->isfirst=false;
                s.push(temp);
                p=temp->btnode->right;    
            }else{ //第二次出现在栈顶 
                cout<<temp->btnode->data<<" ";
                p=NULL;
            }
        }
    }    
}