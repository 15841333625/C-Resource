#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "MaxHeap.h"
#include <queue>
#include <math.h>

using namespace std;
int const NUM = 10;

template <class T>
void print(T arr[], int n){                                     //打印数组
    for(int i = 0; i < n; i ++){
        cout<<arr[i]<<'\t';
    }
    cout<<endl;
}


void createArry(int arr[], int n, int startint, int endint){     //生成随机数数组，在一个程序中能生成多个不同的随机数数组
    LARGE_INTEGER seed;                                          //表示64位结构的数据
    QueryPerformanceFrequency(&seed);                            //获得机器内部计时器的时钟频率
    QueryPerformanceCounter(&seed);                              //计数
    srand(seed.QuadPart);                                        //初始化一个以微妙为单位的时间种子
    for(int i = 0; i < n; i ++){
        arr[i] = (rand() % endint) + startint;                   //生成一个startint到endint之间的随机数
    }
    print(arr, n);
}

template <class T>
void insertSort(T arr[], int n){                                 //直接插入排序
    T temp;
    for(int i = 1; i < n; i ++){
        temp = arr[i];
        int j = i - 1;
        while((j >= 0) && (temp < arr[j])){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = temp;
    }
    cout<<"insertSort: "<<endl;
    print(arr, n);
}

template <class T>
void binaryInsertSort(T arr[], int n){                           //折半插入排序
    for(int i = 1; i < n; i ++){
        int left = 0, right = i - 1;
        T temp = arr[i];
        while(left <= right){
            int middle = (left + right) / 2;
            if(temp < arr[middle])
                right = middle - 1;
            else
                left = middle + 1;
        }
        for(int j = i - 1; j >= left; j --)
            arr[j + 1] = arr[j];
        arr[left] = temp;
    }
    cout<<"BinaryInsertSort: "<<endl;
    print(arr, n);
}

template <class T>
void ShellSort(T arr[], int n){                                  //希尔排序
    T temp;
    int gap = n / 2;                                             //gap是子序列间隔
    while(gap != 0){                                             //循环，直到gap为零
        for(int i = gap; i < n; i ++){                           //直接插入排序
            temp = arr[i];
            for(int j = i; j >= gap; j -= gap){
                if(temp < arr[j - gap])
                    arr[j] = arr[j - gap];
                else
                    break;
                arr[j - gap] = temp;
            }
        }
        gap = gap / 2;
    }
    cout<<"ShellSort: "<<endl;
    print(arr, n);
}

template <class T>
void BubbleSort(T arr[], int n){                                 //冒泡排序
    bool noSwap;
    T temp;
    for(int i = 0; i < n - 1; i ++){
        for(int j = n - 1; j > i; j --){
            noSwap = true;
            if(arr[j] < arr[j - 1]){
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                noSwap = false;
            }
        }
        if(noSwap){
            cout<<"BubbleSort: "<<endl;
            print(arr, n);
            return;
        }
    }
}

template <class T>
int Partition(T arr[], int low, int high){                       //分割算法，返回轴的位置
    T pivot = arr[low];                                          //pivot记录轴处的值
    while(low < high){                                           //如果high大于low就一直向中间扫描
        while(low < high && arr[high] >= pivot)                  //从右开始扫描找到第一个值小于轴的数据
            high --;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot)                   //从左开始扫描找到第一个值大于轴的数据
            low ++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;                                            //最后使改变后的轴的值等于原先的值
    return low;
}

template <class T>
void QuikSort(T arr[], int low, int high){                       //快速排序
    int pivotLocation;
    if(low < high){
        pivotLocation = Partition(arr, low, high);
        QuikSort(arr, low, pivotLocation - 1);
        QuikSort(arr, pivotLocation + 1, high);
    }
}

template <class T>
void selectSort(T arr[], int n){                                 //直接选择排序
    T temp;
    for(int i = 0; i < n - 1; i ++){                             //依次选出第i小的记录，即剩余记录中最小的那个
        int minn = i;                                            //首先假设记录i就是最小的
        for(int j = i + 1; j < n; j ++){                         //开始向后扫描所有剩余记录
            if(arr[j] < arr[minn])                               //如果发现更小的记录，记录它的位置
                minn = j;
        }
        temp = arr[i];                                           //将第i小的记录放在数组中第i个位置
        arr[i] = arr[minn];
        arr[minn] = temp;
    }
    cout<<"SelectSort: "<<endl;
    print(arr, n);
}

template <class T>                                               //堆排序
void heapSort(T arr[], int n){
    MaxHeap<T> max_heap(arr, n);                                 //建堆
    for(int i = 0; i < n; i ++){                                 //算法操作n次，最小元素不需要出堆
        max_heap.delTop(arr[n - i - 1]);                         //一次找出剩余记录中的最大记录，放在数组末尾
    }
    cout<<"HeapSort: "<<endl;
    print(arr, n);
}

template <class T>
void merge(T arr[], int start, int mid, int end){                //arr是待归并数组，对arr[start, mid]和arr[mid + 1, end]之间的数据进行归并
    int len1 = mid - start + 1, len2 = end - mid;                //分别表示两个归并区间的长度
    int i, j, k;
    T* left = new T[len1];                                       //临时数组用来存放arr[start, mid]
    T* right = new T[len2];                                      //临时数组用来存放arr[mid + 1, end]
    for(i = 0; i < len1; i ++)                                   //执行数据复制操作
        left[i] = arr[i + start];
    for(i = 0; i < len2; i ++)                                   //执行数据复制操作
        right[i] = arr[i + mid + 1];
    i = j = 0;
    for(k = start; k < end; k ++){                               //执行归并
        if(i == len1 || j == len2)
            break;
        if(left[i] <= right[j]){
            arr[k] = left[i];
            ++ i;
        }else{
            arr[k] = right[j];
            ++j;
        }
    }
    while(i < len1){                                             //若arr[start, mid]还有待归并数据，则放到arr后面
        arr[k] = left[i];
        ++k;
        ++i;
    }
    while(j < len2){                                             //对arr[mid + 1, end]间的数据执行同样的操作
        arr[k] = right[j];
        ++k;
        ++j;
    }
    delete[] left;                                               //释放内存
    delete[] right;
}
template <class T>
void mergeSort(T arr[], int left, int right){                    //对arr[left, right]之间的序列进行归并排序
    int middle;
    if(left < right){
        middle = (left + right) / 2;                             //计算中间位置
        mergeSort(arr, left, middle);                            //对左边子序列归并排序
        mergeSort(arr, middle + 1, right);                       //对右边子序列归并排序
        merge(arr, left,  middle, right);                        //归并左、右两边的有序序列
    }
}

int digitInt(int num){                                           //计算一个整数的位数
    int icount = 0;
    while(num){
        num = num / 10;
        ++ icount;
    }
    return icount;
}
void distribute(int arr[], int n, queue<int> q[], int icount){   //分配函数，arr为待分配数组，n为arr的长度，q为0-9的队列数组，将arr中的各个数据按照第icount位的1-9分配
    for(int i = 0; i < n; i ++){                                 //将arr中的数据依次放入对应队列
        int unit = (arr[i] / (int)(pow(10, icount))) % 10;       //计算对应位的数字大小
        q[unit].push(arr[i]);                                    //入队列
    }
}
void collect(int arr[], queue<int> q[]){                         //收集函数
    int j = 0;
    for(int i = 0; i < 10; i ++){                                //将q中不为空的队列依次出队列，放回arr中
        while(!q[i].empty()){
            arr[j] = q[i].front();
            q[i].pop();
            ++ j;
        }
    }
}
void radixSort(int arr[], int n){                                //基数排序
    int maxnum = arr[0];
    queue<int> q[10];                                            //一个从0-9代表对应数字的队列数组
    for(int i = 1; i < n; i ++)                                  //找出数组中的最大值，判断最大位数
        maxnum = (arr[i] > maxnum) ? arr[i] : maxnum;
    for(int i = 0; i < digitInt(maxnum); i ++){                  //最大多少位就进行多少次分配收集，i作为参数代表按照第几位分配
        distribute(arr, n, q, i);
        collect(arr, q);
    }
    cout<<"RadixSort: "<<endl;
    print(arr, n);
}

int main()
{
    int arr[NUM];
//    createArry(arr, NUM, 1, 100);
//    insertSort(arr, NUM);
//    cout<<endl;
//    createArry(arr, NUM, 1, 100);
//    binaryInsertSort(arr, NUM);
//    cout<<endl;
//    createArry(arr, NUM, 1, 100);
//    ShellSort(arr, NUM);
//    cout<<endl;

    createArry(arr, NUM, 1, 100);
    BubbleSort(arr, NUM);
    cout<<endl;
    createArry(arr, NUM, 1, 100);
    cout<<"QuikSort: "<<endl;
    QuikSort(arr, 0, NUM - 1);
    print(arr, NUM);
    cout<<endl;
    createArry(arr, NUM, 1, 100);
    selectSort(arr, NUM);
    cout<<endl;

    createArry(arr, NUM, 1, 100);
    heapSort(arr, NUM);
    cout<<endl;
    createArry(arr, NUM, 1, 100);
    cout<<"MergeSort: "<<endl;
    mergeSort(arr, 0, NUM - 1);
    print(arr, NUM);
    cout<<endl;
    createArry(arr, NUM, 1, 10000);
    radixSort(arr, NUM);
    cout<<endl;

    return 0;
}
