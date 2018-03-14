/**
 * 平衡二叉树定义(AVL)：它或者是一颗空树，或者具有以下性质的二叉树：
 * 它的左子树和右子树的深度之差(平衡因子)的绝对值不超过1，且它的左子
 * 树和右子树都是一颗平衡二叉树。
 * 平衡因子(bf)：结点的左子树的深度减去右子树的深度，那么显然-1<=
 * bf<=1。
 */
/**
 * 在平衡二叉树进行插入操作时遇到的不平衡情况有多种，但是这么多种情况
 * 都可以分解为一下四中基础情景：把它叫做：左左、左右、右右、右左。
 * 在解释这四种情景之前需要先明白一个定义：最小不平衡节点—插入一个节点之后，
 * 距离这个插入节点最近的不平衡节点就是最小不平衡节点（如上图左树的10节点）。
 * 所有的旋转都是在最小不平衡节点的基础上进行的。
 * 继续解释四种情景命名意义：
 * 左左：节点插入在最小不平衡节点的左子树的左子树上。   右旋
 * 左右：节点插入在最小不平衡节点的左子树的右子树上面   左右
 * 右右：节点插入在最小不平衡树的右子树的右子树上面。   左旋
 * 右左：节点插入在最小不平衡树的右子树的左子树上面。   右左
 */

#include<stdlib.h>
#include<stdio.h>

// 树的节点
typedef struct TreeNode{
    int data;
    int height;//平衡因子
    struct TreeNode *left;
    struct TreeNode *right;
}TREENODE,*PTREENODE;

// 创建一个新节点
PTREENODE createNode(int data,int height,PTREENODE left,PTREENODE right){
    PTREENODE node=nullptr;
    if((node=(PTREENODE)malloc(sizeof(TREENODE)))==nullptr){
        return(node);
    }
    node->data=data;
    node->height=height;
    node->left=left;
    node->right=right;
    return(node);
}

// 获取节点高度
int nodeHeight(PTREENODE node){
    return(nullptr==node?-1:node->height);
}

//比较大小宏
#define MAX(a,b) ((a)>(b)?(a):(b))

// 左左：节点插入在最小不平衡节点的左子树的左子树上。
// 右旋
void rightRotate(PTREENODE root){
    PTREENODE node;
    node=root->left; // 获取‘根’的左孩子
    root->left=node->right; // 将‘根’的左孩子这是为空
    node->right=root; // 设置原‘根’的左孩子的右孩子为‘根’。
    root=node; // 树的‘根’节点发生变化
}

// 右右：节点插入在最小不平衡树的右子树的右子树上面。
// 左旋
void leftRotate(PTREENODE root){
    PTREENODE node;
    node=root->right; // 获取'根'的右孩子
    root->right=node->left; // 清空‘根’的右孩子
    node->left=root; // 重置原‘根’的有孩子的左孩子为‘根’
    root=node; // 树的'根'节点发生变化
}

// 左右：节点插入在最小不平衡节点的左子树的右子树上面
// 先左旋再右旋
void leftRightRotate(PTREENODE root){
    // 记录左儿子
    PTREENODE node=root->left;
    // 左旋
    leftRotate(node);
    // 左儿子更新
    root->left=node;
    // 右旋
    rightRotate(root);
}

// 右左：节点插入在最小不平衡树的右子树的左子树上面。
// 先右旋再左旋
void rightLeftRotate(PTREENODE root){
    // 记录右儿子
    PTREENODE node=root->right;
    // 右旋
    rightRotate(node);
    // 右儿子更新
    root->right=node;
    // 左旋
    leftRotate(root);
}

// 向指定树中插入新数据
// 返回新插入后树的根
PTREENODE insertData(PTREENODE root,int data){
    // 当前树为空
    if(nullptr==root){
        // 新节点
        root=createNode(data,0,nullptr,nullptr);
        if(nullptr==root) // 创建失败
            printf("ERROR: create avltree node failed!\n");
        // 返回
        return root;
    }
    // 应插入左子树
    if(data<root->data){
        // 递归插入
        root->left=insertData(root->left,data);
        // 失衡检测
        if(2==nodeHeight(root->left)-nodeHeight(root->right)){ // 失衡
            if(data<root->left->data) // 左左
                rightRotate(root);
            else // 左右
                leftRightRotate(root);
        }
    }
    // 应插入右子树
    else if(data>root->data){
        // 递归插入
        root->right=insertData(root->right,data);
        // 失衡检测
        if(2==nodeHeight(root->right)-nodeHeight(root->left)){
            if(data>root->right->data) // 右右
                leftRotate(root);
            else // 右左
                rightLeftRotate(root);
        }
    }
    // 无法插入
    else{
        printf("添加失败：不允许添加相同的节点！\n");
        return(nullptr);
    }
    // 更新高度
    root->height=MAX(nodeHeight(root->left),nodeHeight(root->right))+1;
    // 返回
    return root;
}