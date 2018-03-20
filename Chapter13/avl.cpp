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
/**
 * 对于平衡二叉树的删除操作，只要明白一点就可以了：
 * 如果该节点没有左右子树（该节点为叶子节点）或者只有其中一个子树则可以直接进行删除
 * 否则需要继续进行判定该节点：如果该节点的外部（内外：以根节点做对称轴，靠近对称轴
 * 的子树为内部子树）子树树高低于内部子树树高，则找到该节点内部子树的最值（最值：如
 * 果内部子树是该节点的右子树则数值为右子树的最小值；如果内部节点是该节点的左子树则
 * 数值为该节点左子树的最大值）进行数值交换，交换之后删除该节点即可。删除之后进行回
 * 溯的时候要更新节点的树高，然后判断节点是否平衡，不平衡进行旋转。这时对旋转次数的
 * 判定就不同于插入时的判定。
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

// 删除指定数据  
// 删除当前接点: 1）当前结点的左孩子为空，右孩子移到当前接点的位置。
//             2）当前结点的右孩为空，左孩子移到当前接点的位置。
//             3）当前结点左右孩子都为空，当前位置改为空。
//             4）当前结点左右孩子都不为空，左子树接点是小于父接点，
//                所有的右子树大于父接点，现在删除的正好是左右子树的
//                父接点，那么左子树中，肯定是左自树的最右孩子排在右子树
//                的根前面，那么先把左子树的根连接到当前删除的接点位置，
//                再找到左子树的最右孩子，把当前接点的右子树的根连接上去就
//                是这些了
PTREENODE deleteData(PTREENODE root,int data){
    // 树空  
    if(nullptr==root){
        return nullptr;
    }
    // 目标节点在左子树中
    if(data<root->data) 
        root->left=deleteData(root->left,data); // 递归删除
    // 目标节点在右子树中   
    else if(data>root->data)  
        root->right=deleteData(root->right,data); // 递归删除
    // 目标节点便是当前节点  
    else{
        // 含有两棵子树都不为空
        if(nullptr!=root->left&&nullptr!=root->right){
            // 查找后继（前驱也可以）          
            PTREENODE tmp=root->right;  
            while(nullptr!=tmp->left)
                tmp=tmp->left;
            // 交换节点数据
            root->data=tmp->data;
            // 删除交换后的节点
            root->right=deleteData(root->right,tmp->data);
            // 平衡已被破坏
            if(2==nodeHeight(root->left)-nodeHeight(root->right)){  
                // 将root看做根结点，删除的元素在右子树，此时判断左子树与右
                // 子树的高度差是不是>=2,若是，则判断左子树是左单旋还是左-
                // 右双旋，若root->left的右子树比左子树长，则为左-右双旋  
                // 若root->left的左子树比右子树长，则为左单旋  
                //              A  
                //             /            A为root， B为root->Left  
                //            B             若C分支长(T->left->left)，则为左单旋  
                //           / \            若D分支长(T->left->right)，则为左右双旋  
                //          C   D  
                //          :   :  
                if((nullptr!=root->left->right)&&nodeHeight(root->left->right)>
                    nodeHeight(root->left->left))  
                    leftRightRotate(root); // 左右
                else  
                    leftRotate(root);  // 左  
            }  
        }
        // 含有一个或零个子树
        else{
            // 记录当前根
            PTREENODE tmp=root;
            // 左子树为空  
            if(nullptr==root->left)  
                root=root->right;
            // 右子树为空
            else if(nullptr==root->right)  
                root=root->left;
            // 释放当前根
            free(tmp);  
        }  
    }
    // 更新高度
    root->height=MAX(nodeHeight(root->left),nodeHeight(root->right));
    // 返回根
    return root;  
}  