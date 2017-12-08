#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include<iostream>
using namespace std;
int const MAX = 100;

template<class T>
class MaxHeap{
private:
    T compTree[MAX];                       //堆中用来存完全二叉树的数组，MAX 为最多能存的结点数
    int num;                               //实际存放数据的完全二叉树的结点数
public:
    MaxHeap(T arr[], int length){          //参数为一个数组，在堆中存放为完全二叉树
        num = length;
        for(int i = 0; i < num; i ++){
            compTree[i] = arr[i];
        }
//        print();
        init();                            //初始化最大堆
    }
    void init(){
        int i = (num - 2) / 2;             //完全二叉树中最后一个不是叶子结点的结点的下标
        int index = i;
        for(; i >= 0; i --){               //从最后一个不是叶子结点的结点开始向前调整大小顺序，直到根结点
            int j = i;
            while(j <= index){             //当前结点若有孩子就一直向下调整
                int temp = adjust(j);
                if(temp == -1)
                    break;
                j = temp;
            }
        }
    }
    int adjust(int j){                     //调整一个结点和它的两个孩子的位置，若不需改变返回-1，否则返回与父节点交换值得孩子结点的下标
        T temp;
        int index;                         //记录值较大的孩子结点的下标
        if(isLeaf(j))                      //如果是叶子结点则不需要调整
            return -1;
        if(2*j+2 >= num)                   //如果当前结点没有右孩子，index等于左孩子下标
            index = 2*j+1;
        else                               //完全二叉树不是叶子结点，有右孩子一定有左孩子，比较大小
            index = (compTree[2*j+1] > compTree[2*j+2])? 2*j+1 : 2*j+2;
        if(compTree[j] < compTree[index]){ //如果当前结点的值小于其孩子结点的值，则交换，返回此孩子结点的下标
            temp = compTree[j];
            compTree[j] = compTree[index];
            compTree[index] = temp;
            return index;
        }
        return -1;
    }
    bool isLeaf(int index){                //判断是否为叶子结点
        return (index > (num - 2) / 2);
    }
    void print(){                          //打印最大堆
        for(int i = 0; i < num; i ++){
            cout<<compTree[i]<<" ";
        }
        cout<<endl;
    }
    void insert(T item){                   //插入，直接插到数组结尾保证是完全二叉树，再向上比较，一层一层调整
        int index = (num - 1) / 2;         //最后一个不是叶子结点的结点的下标
        int i = 0;
        compTree[num] = item;
        ++num;
        while(index >= 0){                 //向上调整
            i = adjust(index);
            if(i == -1)
                break;
            index = (index - 1) / 2;
        }
    }
    void del(T item){                      //删除结点，把最末尾的值填入要删除的位置，删除最末位，再向下调整
        int index;                         //记录要删除结点的下标
        for(int i = 0; i < num; i ++){     //查找要删除的结点
            if(item == compTree[i])
                index = i;
        }
        --num;
        compTree[index] = compTree[num];   //用尾结点的值替换当前结点
        while(index <= (num - 2) / 2){     //当前结点若有孩子就一直向下调整
            int temp = adjust(index);
            if(temp == -1)
                break;
            index = temp;
        }
    }
    void delTop(T &x){                     //删除堆顶结点，存在x中
        if(num > 0){
            x = compTree[0];
            del(compTree[0]);
        }else{
            cout<<"无法删除"<<endl;
        }
    }
};

#endif // HEAP_H_INCLUDED
