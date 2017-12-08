#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include<iostream>
using namespace std;
int const MAX = 100;

template<class T>
class MaxHeap{
private:
    T compTree[MAX];                       //������������ȫ�����������飬MAX Ϊ����ܴ�Ľ����
    int num;                               //ʵ�ʴ�����ݵ���ȫ�������Ľ����
public:
    MaxHeap(T arr[], int length){          //����Ϊһ�����飬�ڶ��д��Ϊ��ȫ������
        num = length;
        for(int i = 0; i < num; i ++){
            compTree[i] = arr[i];
        }
//        print();
        init();                            //��ʼ������
    }
    void init(){
        int i = (num - 2) / 2;             //��ȫ�����������һ������Ҷ�ӽ��Ľ����±�
        int index = i;
        for(; i >= 0; i --){               //�����һ������Ҷ�ӽ��Ľ�㿪ʼ��ǰ������С˳��ֱ�������
            int j = i;
            while(j <= index){             //��ǰ������к��Ӿ�һֱ���µ���
                int temp = adjust(j);
                if(temp == -1)
                    break;
                j = temp;
            }
        }
    }
    int adjust(int j){                     //����һ�����������������ӵ�λ�ã�������ı䷵��-1�����򷵻��븸�ڵ㽻��ֵ�ú��ӽ����±�
        T temp;
        int index;                         //��¼ֵ�ϴ�ĺ��ӽ����±�
        if(isLeaf(j))                      //�����Ҷ�ӽ������Ҫ����
            return -1;
        if(2*j+2 >= num)                   //�����ǰ���û���Һ��ӣ�index���������±�
            index = 2*j+1;
        else                               //��ȫ����������Ҷ�ӽ�㣬���Һ���һ�������ӣ��Ƚϴ�С
            index = (compTree[2*j+1] > compTree[2*j+2])? 2*j+1 : 2*j+2;
        if(compTree[j] < compTree[index]){ //�����ǰ����ֵС���亢�ӽ���ֵ���򽻻������ش˺��ӽ����±�
            temp = compTree[j];
            compTree[j] = compTree[index];
            compTree[index] = temp;
            return index;
        }
        return -1;
    }
    bool isLeaf(int index){                //�ж��Ƿ�ΪҶ�ӽ��
        return (index > (num - 2) / 2);
    }
    void print(){                          //��ӡ����
        for(int i = 0; i < num; i ++){
            cout<<compTree[i]<<" ";
        }
        cout<<endl;
    }
    void insert(T item){                   //���룬ֱ�Ӳ嵽�����β��֤����ȫ�������������ϱȽϣ�һ��һ�����
        int index = (num - 1) / 2;         //���һ������Ҷ�ӽ��Ľ����±�
        int i = 0;
        compTree[num] = item;
        ++num;
        while(index >= 0){                 //���ϵ���
            i = adjust(index);
            if(i == -1)
                break;
            index = (index - 1) / 2;
        }
    }
    void del(T item){                      //ɾ����㣬����ĩβ��ֵ����Ҫɾ����λ�ã�ɾ����ĩλ�������µ���
        int index;                         //��¼Ҫɾ�������±�
        for(int i = 0; i < num; i ++){     //����Ҫɾ���Ľ��
            if(item == compTree[i])
                index = i;
        }
        --num;
        compTree[index] = compTree[num];   //��β����ֵ�滻��ǰ���
        while(index <= (num - 2) / 2){     //��ǰ������к��Ӿ�һֱ���µ���
            int temp = adjust(index);
            if(temp == -1)
                break;
            index = temp;
        }
    }
    void delTop(T &x){                     //ɾ���Ѷ���㣬����x��
        if(num > 0){
            x = compTree[0];
            del(compTree[0]);
        }else{
            cout<<"�޷�ɾ��"<<endl;
        }
    }
};

#endif // HEAP_H_INCLUDED
