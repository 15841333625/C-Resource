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
void print(T arr[], int n){                                     //��ӡ����
    for(int i = 0; i < n; i ++){
        cout<<arr[i]<<'\t';
    }
    cout<<endl;
}


void createArry(int arr[], int n, int startint, int endint){     //������������飬��һ�������������ɶ����ͬ�����������
    LARGE_INTEGER seed;                                          //��ʾ64λ�ṹ������
    QueryPerformanceFrequency(&seed);                            //��û����ڲ���ʱ����ʱ��Ƶ��
    QueryPerformanceCounter(&seed);                              //����
    srand(seed.QuadPart);                                        //��ʼ��һ����΢��Ϊ��λ��ʱ������
    for(int i = 0; i < n; i ++){
        arr[i] = (rand() % endint) + startint;                   //����һ��startint��endint֮��������
    }
    print(arr, n);
}

template <class T>
void insertSort(T arr[], int n){                                 //ֱ�Ӳ�������
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
void binaryInsertSort(T arr[], int n){                           //�۰��������
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
void ShellSort(T arr[], int n){                                  //ϣ������
    T temp;
    int gap = n / 2;                                             //gap�������м��
    while(gap != 0){                                             //ѭ����ֱ��gapΪ��
        for(int i = gap; i < n; i ++){                           //ֱ�Ӳ�������
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
void BubbleSort(T arr[], int n){                                 //ð������
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
int Partition(T arr[], int low, int high){                       //�ָ��㷨���������λ��
    T pivot = arr[low];                                          //pivot��¼�ᴦ��ֵ
    while(low < high){                                           //���high����low��һֱ���м�ɨ��
        while(low < high && arr[high] >= pivot)                  //���ҿ�ʼɨ���ҵ���һ��ֵС���������
            high --;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot)                   //����ʼɨ���ҵ���һ��ֵ�����������
            low ++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;                                            //���ʹ�ı������ֵ����ԭ�ȵ�ֵ
    return low;
}

template <class T>
void QuikSort(T arr[], int low, int high){                       //��������
    int pivotLocation;
    if(low < high){
        pivotLocation = Partition(arr, low, high);
        QuikSort(arr, low, pivotLocation - 1);
        QuikSort(arr, pivotLocation + 1, high);
    }
}

template <class T>
void selectSort(T arr[], int n){                                 //ֱ��ѡ������
    T temp;
    for(int i = 0; i < n - 1; i ++){                             //����ѡ����iС�ļ�¼����ʣ���¼����С���Ǹ�
        int minn = i;                                            //���ȼ����¼i������С��
        for(int j = i + 1; j < n; j ++){                         //��ʼ���ɨ������ʣ���¼
            if(arr[j] < arr[minn])                               //������ָ�С�ļ�¼����¼����λ��
                minn = j;
        }
        temp = arr[i];                                           //����iС�ļ�¼���������е�i��λ��
        arr[i] = arr[minn];
        arr[minn] = temp;
    }
    cout<<"SelectSort: "<<endl;
    print(arr, n);
}

template <class T>                                               //������
void heapSort(T arr[], int n){
    MaxHeap<T> max_heap(arr, n);                                 //����
    for(int i = 0; i < n; i ++){                                 //�㷨����n�Σ���СԪ�ز���Ҫ����
        max_heap.delTop(arr[n - i - 1]);                         //һ���ҳ�ʣ���¼�е�����¼����������ĩβ
    }
    cout<<"HeapSort: "<<endl;
    print(arr, n);
}

template <class T>
void merge(T arr[], int start, int mid, int end){                //arr�Ǵ��鲢���飬��arr[start, mid]��arr[mid + 1, end]֮������ݽ��й鲢
    int len1 = mid - start + 1, len2 = end - mid;                //�ֱ��ʾ�����鲢����ĳ���
    int i, j, k;
    T* left = new T[len1];                                       //��ʱ�����������arr[start, mid]
    T* right = new T[len2];                                      //��ʱ�����������arr[mid + 1, end]
    for(i = 0; i < len1; i ++)                                   //ִ�����ݸ��Ʋ���
        left[i] = arr[i + start];
    for(i = 0; i < len2; i ++)                                   //ִ�����ݸ��Ʋ���
        right[i] = arr[i + mid + 1];
    i = j = 0;
    for(k = start; k < end; k ++){                               //ִ�й鲢
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
    while(i < len1){                                             //��arr[start, mid]���д��鲢���ݣ���ŵ�arr����
        arr[k] = left[i];
        ++k;
        ++i;
    }
    while(j < len2){                                             //��arr[mid + 1, end]�������ִ��ͬ���Ĳ���
        arr[k] = right[j];
        ++k;
        ++j;
    }
    delete[] left;                                               //�ͷ��ڴ�
    delete[] right;
}
template <class T>
void mergeSort(T arr[], int left, int right){                    //��arr[left, right]֮������н��й鲢����
    int middle;
    if(left < right){
        middle = (left + right) / 2;                             //�����м�λ��
        mergeSort(arr, left, middle);                            //����������й鲢����
        mergeSort(arr, middle + 1, right);                       //���ұ������й鲢����
        merge(arr, left,  middle, right);                        //�鲢�������ߵ���������
    }
}

int digitInt(int num){                                           //����һ��������λ��
    int icount = 0;
    while(num){
        num = num / 10;
        ++ icount;
    }
    return icount;
}
void distribute(int arr[], int n, queue<int> q[], int icount){   //���亯����arrΪ���������飬nΪarr�ĳ��ȣ�qΪ0-9�Ķ������飬��arr�еĸ������ݰ��յ�icountλ��1-9����
    for(int i = 0; i < n; i ++){                                 //��arr�е��������η����Ӧ����
        int unit = (arr[i] / (int)(pow(10, icount))) % 10;       //�����Ӧλ�����ִ�С
        q[unit].push(arr[i]);                                    //�����
    }
}
void collect(int arr[], queue<int> q[]){                         //�ռ�����
    int j = 0;
    for(int i = 0; i < 10; i ++){                                //��q�в�Ϊ�յĶ������γ����У��Ż�arr��
        while(!q[i].empty()){
            arr[j] = q[i].front();
            q[i].pop();
            ++ j;
        }
    }
}
void radixSort(int arr[], int n){                                //��������
    int maxnum = arr[0];
    queue<int> q[10];                                            //һ����0-9�����Ӧ���ֵĶ�������
    for(int i = 1; i < n; i ++)                                  //�ҳ������е����ֵ���ж����λ��
        maxnum = (arr[i] > maxnum) ? arr[i] : maxnum;
    for(int i = 0; i < digitInt(maxnum); i ++){                  //������λ�ͽ��ж��ٴη����ռ���i��Ϊ���������յڼ�λ����
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
