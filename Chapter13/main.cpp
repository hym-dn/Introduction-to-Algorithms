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

// 将指定节点插入到红黑树中
void insertNode(PTREENODE root,PTREENODE node){
    PTREENODE y=NILTREENODE;
    PTREENODE x=root;
    // 利用插入节点的键值，初步确定其处于树中的位置
    while(NILTREENODE!=x){ // x非空
        y=x; // x赋值给y
        if(z->m_key<x->m_key){ // 待插入节点的键值小于当前节点的键值
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
        if(z->m_key<y->m_key){
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
}