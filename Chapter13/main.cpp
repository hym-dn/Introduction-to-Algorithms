#include<assert.h>
#include<stdio.h>

// 红黑树颜色
enum Color{
    COLOR_RED=1,
    COLOR_BLACK=2
};

// 红黑树节点
struct TreeNode{
    int m_key;
    Color m_color;
    struct TreeNode *m_left;
    struct TreeNode *m_right;
    struct TreeNode *m_parent;
};

// 自定义
#define COLOR Color
#define TREENODE struct TreeNode
#define PTREENODE struct TreeNode *
static TREENODE g_nil={0,COLOR_BLACK,0,0,0}; 
#define NILTREENODE &g_nil

// 左旋转
void leftRotate(PTREENODE root,PTREENODE node){
    // 断言node的右孩子存在
    assert(NULL==node->m_right);
    // 记录node的右孩子
    PTREENODE tempNode=node->m_right;
    // 将node的右儿子设置为tempNode的左儿子
    node->m_right=tempNode->m_left;
    // 如果tempNode的左儿子存在，则为其更新父亲
    if(NILTREENODE!=tempNode->m_left){
        tempNode->m_left->m_parent=node;
    }
    // 将tempNode的父亲节点设置为node的父亲节点
    tempNode->m_parent=node->m_parent;
    // 如果node为根节点
    if(NILTREENODE==node){
        root=tempNode; // 重置树的根
    }
    // 如果node为左孩子
    else if(node==node->m_parent->m_left){
        // 重置父亲节点左孩子
        node->m_parent->m_left=tempNode;
    }
    // 如果node为右孩子
    else{
        // 重置父亲节点右孩子
        node->m_parent->m_right=tempNode;
    }
    // 设置tempNode左孩子
    tempNode->m_left=node;
    // 设置node的父亲节点
    node->m_parent=tempNode;
}

// 右旋转
void rightRotate(PTREENODE root,PTREENODE node){
    // 断言node的左孩子存在
    assert(NULL==node->m_left);
    // 记录node的左孩子
    PTREENODE tempNode=node->m_left;
    // 将node的左儿子设置为tempNode的右儿子
    node->m_left=tempNode->m_right;
    // 如果tempNode的右儿子存在，则为其更新父亲
    if(NILTREENODE!=tempNode->m_right){
        tempNode->m_right->m_parent=node;
    }
    // 将tempNode的父亲节点设置为node的父亲节点
    tempNode->m_parent=node->m_parent;
    // 如果node为根节点
    if(NILTREENODE==node){
        root=tempNode; // 重置树的根
    }
    // 如果node为左孩子
    else if(node==node->m_parent->m_left){
        // 重置父亲节点左孩子
        node->m_parent->m_left=tempNode;
    }
    // 如果node为右孩子
    else{
        // 重置父亲节点右孩子
        node->m_parent->m_right=tempNode;
    }
    // 设置tempNode右孩子
    tempNode->m_right=node;
    // 设置node的父亲节点
    node->m_parent=tempNode;
}

// 修复插入
void fixupInsert(PTREENODE root,PTREENODE z){
    // 待插入节点的父亲为红色
    while(COLOR_RED==z->m_parent->m_color){ // 违反了性质4
        // 如果父亲节点为红色，则祖父节点一定存在
        // 如果z的父亲是z祖父的左儿子
        if(z->m_parent==z->m_parent->m_parent->m_left){
            // 获取叔父
            PTREENODE uncle=z->m_parent->m_parent->m_right;
            // 情况1,叔叔是红色的
            if(COLOR_RED==uncle->m_color){
                // 父亲置为黑色
                z->m_parent->m_color=COLOR_BLACK;
                // 叔叔置为黑色
                uncle->m_color=COLOR_BLACK;
                // 祖父置为红色
                z->m_parent->m_parent->m_color=COLOR_RED;
                // z节点上移
                z=z->m_parent->m_parent;
            }
            // 情况2,叔叔是黑色的，且z是右孩子
            else if(z==z->m_parent->m_right){
                // z节点上移
                z=z->m_parent;
                // 左旋
                leftRotate(root,z);
            }
            // 情况3,叔叔是黑色的，且z是左孩子
            // 设置z父亲的颜色
            z->m_parent->m_color=COLOR_BLACK;
            // 设置z祖父的颜色
            z->m_parent->m_parent->m_color=COLOR_RED;
            // 右旋
            rightRotate(root,z->m_parent->m_parent);
        }
        // 如果z的父亲是z祖父的右儿子
        else{
            // 获取叔父
            PTREENODE uncle=z->m_parent->m_parent->m_left;
            // 情况1,叔叔是红色的
            if(COLOR_RED==uncle->m_color){
                // 父亲置为黑色
                z->m_parent->m_color=COLOR_BLACK;
                // 叔叔置为黑色
                uncle->m_color=COLOR_BLACK;
                // 祖父置为红色
                z->m_parent->m_parent->m_color=COLOR_RED;
                // z节点上移
                z=z->m_parent->m_parent;
            }
            // 情况2,叔叔是黑色的，且z是右孩子
            else if(z==z->m_parent->m_right){
                // z节点上移
                z=z->m_parent;
                // 左旋
                leftRotate(root,z);
            }
            // 情况3,叔叔是黑色的，且z是左孩子
            // 设置z父亲的颜色
            z->m_parent->m_color=COLOR_BLACK;
            // 设置z祖父的颜色
            z->m_parent->m_parent->m_color=COLOR_RED;
            // 右旋
            rightRotate(root,z->m_parent->m_parent);
        }
    }
    // 设置根节点为黑色
    root->m_color=COLOR_BLACK;
}

// 将指定节点插入到红黑树中
void insertNode(PTREENODE root,PTREENODE node){
    PTREENODE y=NILTREENODE;
    PTREENODE x=root;
    // 利用插入节点的键值，初步确定其处于树中的位置
    while(NILTREENODE!=x){ // x非空
        y=x; // x赋值给y
        if(node->m_key<x->m_key){ // 待插入节点的键值小于当前节点的键值
            x=x->m_left; // 将x赋值为其左孩子
        }else{ // 待插入节点的键值不小于当前节点的键值
            x=x->m_right; // 将x赋值为其有孩子
        }
    }
    // 设置插入节点的父亲
    node->m_parent=y;
    // 如果y节点为空
    if(NILTREENODE==y){
        root=node; // 更新根
    }
    // 如果y节点非空
    else{
        // 如果z的键值小于y
        if(node->m_key<y->m_key){
            y->m_left=node;
        }
        // 如果z的键值不小于y
        else{
            y->m_right=node;
        }
    }
    // 设置新结点
    node->m_left=NILTREENODE;
    node->m_right=NILTREENODE;
    node->m_color=COLOR_RED;
    // 修复红黑树
    fixupInsert(root,node);
}

// 最小元素
PTREENODE minimumNode(PTREENODE x){
    while(0!=x->m_left)
        x=x->m_left;
    return x;
}

// 中序后继
//（a）若一个结点有右子树，那么该结点的后继节点是其右子树中val值最小的结点（即右子树中最左边的结点）
//（b）若一个结点没有右子树
//  1、若该结点是其父结点的左孩子，那么该节点的后继结点即为其父节点。
//  2、若该结点是其父结点的右孩子，那么需要沿着其父结点一直向树的顶端寻找，直到找到一个结点P，
//     P结点是其父结点Q的左孩子，那么Q就是该结点的前后继结点。
PTREENODE successorNode(PTREENODE x){
    if(0==x)
        return x;
    // 右子树非空
    if(0!=x->m_right)
        // 后继是大于x的最小值
        return tree_minimum(x->m_right);
    // 右子树为空
    else{ // x 有一个后继 y，y 是 x 的最低祖先结点，且 y 的左儿子也是x的祖先
        PTREENODE y=x->m_parent;
        while(0!=y&&x==y->m_right){
            x=y;
            y=y->m_parent;
        }
        return y;
    }
}

//修复删除
void fixupDelete(PTREENODE root,PTREENODE node){

}

// 从指定树中，删除指定节点
PTREENODE deleteNode(PTREENODE root,PTREENODE node){
    PTREENODE y=0;
    if(NILTREENODE==node->m_left||NILTREENODE==node->m_right){ // 如果节点无左或右孩子
        y=node; // 当前节点
    }else{ // 如果当前节点有左、右孩子
        y=successorNode(node); // 后继节点
    }
    PTREENODE x=0;
    if(NILTREENODE!=y->m_left){ // 如果左孩子存在
        x=y->m_left;
    }else{ // 如果左孩子不存在
        x=y->m_right;
    }
    x->m_parent=y->m_parent; // 如果x是哨兵，其父指针就被指向被删除的节点的父亲
    if(NILTREENODE==y->m_parent){ // 如果y的父亲为空
        root=x; // x设为树的根
    }else{ // 如果y的父亲非空
        if(y==y->m_parent->m_left){ // 如果y是父亲的左孩子
            y->m_parent->m_left=x;
        }else{ // 如果y不是父亲的左孩子
            y->m_parent->m_right=x;
        }
    }
    if(y!=node){ // 如果y不是删除目标节点
        node->m_key=y->m_key;
    }
    if(COLOR_BLACK==y->m_color){ // 如果删除的节点是黑的
        // 删除修复
        fixupDelete(root,x);
    }
    return(y); // 返回删除的节点
}