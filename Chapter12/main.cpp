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

// 后序遍历（非递归）
// 后序遍历的非递归实现是三种遍历方式中最难的一种。因为在后序遍历中，
// 要保证左孩子和右孩子都已被访问并且左孩子在右孩子前访问才能访问根结点，
// 这就为流程的控制带来了难题。下面介绍两种思路。
// 第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任
// 一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或
// 者P存 在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样
// 可以直接访问该结点。若非上述两种情况，则将P的右孩子和左孩子依次入栈，
// 这样就保证了 每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和
// 右孩子都在根结点前面被访问。
void post_order_tree_walk_3(struct TreeNode *x){
    stack<TreeNode*> s;
    TreeNode *cur;                      //当前结点 
    TreeNode *pre=NULL;                 //前一次访问的结点 
    s.push(x);
    while(!s.empty()){ // 栈非空
        cur=s.top(); // 栈顶
        if((cur->left==NULL&&cur->right==NULL)||
           (pre!=NULL&&(pre==cur->left||pre==cur->right))){
            cout<<cur->data<<" ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
            s.pop();
            pre=cur; 
        }else{
            if(cur->right!=NULL)
                s.push(cur->right);
            if(cur->left!=NULL)    
                s.push(cur->left);
        }
    }    
}

// 查找(利用递归方式)
struct TreeNode *tree_search(struct TreeNode *x,const unsigned int key){
    // 如果x便是查找的节点
    if(0==x||key==x->data){
        return x;
    }
    // 如果key小于x中的数据值
    if(key<x->data) 
        return tree_search(x->left,key); // 遍历左子树
    // 如果key不小于x中的数据值
    else 
        return tree_search(x->right,key); // 遍历右子树
}

// 查找（非递归方式）
struct TreeNode *tree_search_2(struct TreeNode *x,const unsigned int key){
    while(0!=x&&key!=x->data){
        if(key<x->data)
            x=x->left;
        else
            x=x->right;
    }
    return x;
}

// 最小元素
struct TreeNode *tree_minimum(struct TreeNode *x){
    while(0!=x->left)
        x=x->left;
    return x;
}

// 最大元素
struct TreeNode *tree_maxinum(struct TreeNode *x){
    while(0!=x->right)
        x=x->right;
    return x;
}

// 中序后继
//（a）若一个结点有右子树，那么该结点的后继节点是其右子树中val值最小的结点（即右子树中最左边的结点）
//（b）若一个结点没有右子树
//  1、若该结点是其父结点的左孩子，那么该节点的后继结点即为其父节点。
//  2、若该结点是其父结点的右孩子，那么需要沿着其父结点一直向树的顶端寻找，直到找到一个结点P，
//     P结点是其父结点Q的左孩子，那么Q就是该结点的前后继结点。
struct TreeNode *tree_successor(struct TreeNode *x){
    if(0==x)
        return x;
    // 右子树非空
    if(0!=x->right)
        // 后继是大于x的最小值
        return tree_minimum(x->right);
    // 右子树为空
    else{ // x 有一个后继 y，y 是 x 的最低祖先结点，且 y 的左儿子也是x的祖先
        struct TreeNode *y=x->parent;
        while(0!=y&&x==y->right){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

// 中序前驱
//（a）若一个结点有左子树，那么该结点的前驱节点是其左子树中val值最大的结点（即左子树中最右边的结点）
//（b）若一个结点没有左子树
//    1、若该结点是其父结点的右孩子，那么该结点的前驱结点即为其父结点。
//    2、若该结点是其父结点的左孩子，那么需要沿着其父结点一直向树的顶端寻找，直到找到一个结点P，
//    P结点是其父结点Q的右孩子，那么Q就是该结点的前驱结点。
struct TreeNode *tree_successor(struct TreeNode *x){
    if(0==x)
        return x;
    // 左子树非空
    if(0!=x->left)
        // 后继是大于x的最小值
        return tree_maximum(x->left);
    // 左子树为空
    else{ // x 有一个后继 y，y 是 x 的最低祖先结点，且 y 的左儿子也是x的祖先
        struct TreeNode *y=x->parent;
        while(0!=y&&x==y->left){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

// 将node节点插入到根为root的树上
void tree_insert(struct TreeNode *root,struct TreeNode *node){
    struct TreeNode *y=0;
    struct TreeNode *x=root;
    // 下滤找到合适的插入位置（小于当前节点向左否则向右）
    while(x!=0){
        y=x;
        if(node->data<x->data)
            x=x->left;
        else
            x=x->right;
    }
    // 整理树中相关节点指针
    node->parent=y;
    if(0==y){ // 树为空
        root=node;
    }else{ // 树非空
        if(node->data<y->data)
            y->left=node;
        else
            y->right=node;
    }
}

// 删除根为root树中的节点node
// 1.如果node没有子女，则修改其父结点，使NIL为其子女
// 2.如果node只有一个子女，则可以通过在其子结点于父结点间建立一条链来删除z
// 3.如果node有两个子女，先删除node的后继（它没有左子女），再用后继内容来
//   代替node的内容
void tree_delete(struct TreeNode *root,struct TreeNode *node){
    // 算法确定要删除的节点y，该节点y或者是输入结点node（如果
    // node至多只有一个子女），或者是noe的后继（如果node有两个子女）
    struct TreeNode *y=0;
    if(0==node->left||0==node->right) // 单子女
        y=node; // 自身
    else // 双子女
        y=tree_successor(node); // 后继 
    // x被置为y的非NIL子女，或当y无子女时被置为NIL
    struct TreeNode *x=0;
    if(0!=y->left) // 左子树存在
        x=y->left;
    else // 左子树不存在
        x=y->right;
    // 通过修改y->parent和x中的指针将y删除。在考虑到边界条件，即
    // x=NIL或y为根结点时，对y的删除就有点复杂了
    if(0!=x) // 如果y有一个或两个孩子
        x->parent=y->parent; // 连接孩子与父结点
    // 如果y为根结点（node为根）,且至少有一子
    if(0==y->parent)
        root=x;
    // 如果y为父节点的左儿子
    else if(y==y->parent->left)
        y->parent->left=x; // 链接父结点于x
    else
        y->parent->right=x; // 链接父结点于x
    // 如果y不是node
    if(y!=node)
        node->data=y->data;
    // 释放y
}