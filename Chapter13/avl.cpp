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

// 树的节点
typedef struct TreeNode{
    int m_data;
    int m_bf;//平衡因子
    struct TreeNode *left;
    struct TreeNode *right;
}TREENODE,*PTREENODE;

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

// 插入
//void insert(PTREENODE root,PTREENODE node){
    // 递归终止提交条件
    
//}

/*
// 私有方法进行递归插入，返回插入节点
Node<T> insert(T data, Node<T> node) {
        // 递归终止条件
        if (node == null)
            return new Node<T>(null, null, data);
        // 比较插入数据和待插入节点的大小
        int compareResult = data.compareTo(node.data);
        if (compareResult > 0) {// 插入node的右子树
            node.right = insert(data, node.right);
            // 回调时判断是否平衡
            if (getHeight(node.right) - getHeight(node.left) == 2) {// 不平衡进行旋转
                // 判断是需要进行两次旋转还是需要进行一次旋转
                int compareResult02 = data.compareTo(node.right.data);
                if (compareResult02 > 0)// 进行一次左旋(右右)
                    node = rotateSingleLeft(node);
                else
                    // 进行两次旋转，先右旋，再左旋
                    node = rotateDoubleLeft(node);
            }
        } else if (compareResult < 0) {// 插入node的左子树
            node.left = insert(data, node.left);
            // 回调时进行判断是否平衡
            if (getHeight(node.left) - getHeight(node.right) == 2) {// 进行旋转
                // 判断是需要进行两次旋转还是需要进行一次旋转
                int intcompareResult02 = data.compareTo(node.left.data);
                if (intcompareResult02 < 0)// 进行一次左旋(左左)
                    node = rotateSingleRight(node);
                else
                    // 进行两次旋转，先左旋，再右旋
                    node = rotateDoubleRight(node);
            }
        }
        // 重新计算该节点的树高
        node.height = Math.max(getHeight(node.left), getHeight(node.right)) + 1;
        return node;
    }
*/