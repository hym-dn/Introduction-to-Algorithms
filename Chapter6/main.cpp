#include<iostream>
#include<assert.h>

/**
 * 堆的父节点、左儿子、右儿子的下标可以简单的计算出来
 * PARENT(i)
 *   return  i/2 向下取整
 * LEFT(i)
 *   return 2i
 * RIGHT(i)
 *   return 2i+1
 * i以1为起始下标
 * 在大多数计算机上，LEFT过程可以在一条指令内计算出2i，
 * 方法是将i的二进制表示左移1位。类似地RIGHT过程也可以
 * 将i的二进制标识左移1位并在低位中加1。PARENT过程则可
 * 以通过把i右移1位而得到。
 */

// 换算左儿子节点下标
int left_child(const int i){
    return(((i+1)<<1)-1);
}

// 换算右儿子节点下标
int right_child(const int i){
    return((((i+1)<<1)+1)-1);
}

// 换算父亲节点下标
int parent(const int i){
    return(((i+1)>>1)-1);
}

// 保持堆的性质
// heap_array 输入的堆数组
// node_index 输入期望保持堆序的开始节点下标
// size 堆占用尺寸
// capacity 堆空间实际尺寸
// 如果函数执行成功返回值大于等于0,否则返回值小于0
// 注意：其它书中，这个被命名为堆的下滤
int max_heapify(int *heap_array,const int node_index,
    const int size,const int capacity){
    //参数非法
    if(0==heap_array||node_index<0||node_index>=size||
        size<=0||size>capacity||capacity<=0){
        return(-1);
    }
    //左儿子下标
    const int left_child_index=left_child(node_index);
    //右儿子下标
    const int right_child_index=right_child(node_index);
    //记录最大元素下标
    int largest_index=node_index;
    //如果左儿子下标有效，且左儿子大于父亲节点
    if(left_child_index<size&&heap_array[left_child_index]>
        heap_array[node_index]){
        largest_index=left_child_index;
    }
    //如果右儿子下标有效，且右儿子最大
    if(right_child_index<size&&heap_array[right_child_index]>
        heap_array[largest_index]){
        largest_index=right_child_index;
    }
    //如果最大元素已经不是父亲
    if(largest_index!=node_index){
        //交换父亲与最大节点
        const int temp=heap_array[node_index];
        heap_array[node_index]=heap_array[largest_index];
        heap_array[largest_index]=temp;
        //递归保持最大儿子堆序
        max_heapify(heap_array,largest_index,size,capacity);
    }
}

// 构建一个最大堆
// heap_array 待构建堆的数组
// size 待构建堆数组的尺寸
// 如果函数执行成功返回值大于等于0,否则返回值小于0
int bulid_max_heap(int *heap_array,const int size){
    //参数非法
    if(0==heap_array||size<=0){
        return(-1);
    }
    //只有一个元素
    if(1==size){
        return(0);
    }
    //获取数组中间位置
    const int mid_index=size/2-1;
    //循环建堆
    for(int i=mid_index;i>=0;--i){
        max_heapify(heap_array,i,size,size);
    }
    //程序运行到此成功返回
    return(0);
}

/**
 * 堆排序
 */

// 堆排序
// array - 指向数组
// size - 数组尺寸
// 如果函数执行成功返回值大于等于0,否则返回值小于0
int heap_sort(int *array,const int size){
    //建堆
    if(bulid_max_heap(array,size)<0){
        return(-1);
    }
    //循环堆排序
    for(int i=size-1;i>=1;--i){
        //交换数组中首、尾
        const int val=array[i];
        array[i]=array[0];
        array[0]=val;
        //保持堆序
        if(max_heapify(array,0,i,i)<0){
            return(-2);
        }
    }
    //返回
    return(0);
}

/**
 * 优先级队列 
 */

// 获取指定堆中最大元素
int heap_maximum(int *heap_array,const int size){
    assert(0!=heap_array&&size>0);
    return(heap_array[0]);
}

// 弹出堆中最大值
int heap_extract_max(int *heap_array,int &size){
    //断言
    assert(0!=heap_array&&size>0);
    //唯一元素
    if(1==size){
        //更新尺寸
        --size;
        //返回
        return(heap_array[0]);
    }
    //获取根节点
    const int max=heap_array[0];
    //交换首尾
    heap_array[0]=heap_array[size-1];
    //更新尺寸
    --size;
    //下滤
    max_heapify(heap_array,0,size,size);
    //返回
    return(max);
}

// 增加指定元素键值
int heap_increase_key(
    int *heap_array,int size,int i,int key){
    //参数检测
    if(0==heap_array||0==size){
        return(-1);
    }
    if(i<0||i>=size){
        return(-2);
    }
    if(key<heap_array[i]){
        return(-3);
    }
    //存储新的键值
    heap_array[i]=key;
    //上滤
    while(i>1&&heap_array[parent(i)]<heap_array[i]){
        const int val=heap_array[i];
        heap_array[i]=heap_array[parent(i)];
        heap_array[parent(i)]=val;
        i=parent(i);
    }
    //返回
    return(0);
}

#define MaxN  0x3f3f3f3f
#define MinN  0xc0c0c0c0

// 最大堆插入
int max_heap_insert(int *heap_array,int &size,const int capacity,const int key){
    //检验
    if(0==heap_array||0==capacity||size>=capacity){
        return(-1);
    }
    //空间增加
    ++size;
    //插入无穷小
    heap_array[size-1]=MinN;
    //提升键值
    if(heap_increase_key(heap_array,size,size-1,key)<0){
        return(-2);
    }
    //返回
    return(0);
}

/**
 * 测试
 */

int main(void){
    int array[]={4,1,3,2,16,9,10,14,8,7};
    heap_sort(array,10);
    for(int i=0;i!=10;++i)
        std::cout<<array[i]<<std::endl;
    return(0);
}