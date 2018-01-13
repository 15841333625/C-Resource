#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include<iostream>
using namespace std;
int const BAL = 0;
int const RWE = 1;
int const LWE = -1;
int const INSERT = 2;
int const DELETE = 3;

template <class T>
class AVL;

template<class T>
class TreeNode{
private:
    friend class AVL<T>;
    TreeNode* parent;           //�����
    TreeNode* leftChild;        //����
    TreeNode* rightChild;       //�Һ���
    T data;                     //�ؼ���
public:
    TreeNode(T data):data(data){
        parent = leftChild = rightChild = NULL;
    }
    bool isLeaf(){
        return (!leftChild && !rightChild);
    }
};

template<class T>
class AVL{
private:
    TreeNode<T>* root;
public:
    AVL(){
        root = NULL;
    }
    ~AVL(){
        destory(root);
    }
    void destory(TreeNode<T>* node){                //���ٶ�����
        TreeNode<T>* temp = node;
        if(temp == NULL)
            return;
        destory(temp->leftChild);
        destory(temp->rightChild);
        delete temp;
        temp = NULL;
    }
    TreeNode<T>* getRoot(){                         //��ø��ڵ�
        return root;
    }
    void getHeight(TreeNode<T>* pointer, int count, int &max){  //������ĸ߶�
        if (pointer != NULL) {
            ++count;
            if(max <= count)
                max = count;
            getHeight(pointer->leftChild, count, max);
            getHeight(pointer->rightChild, count, max);
          }
    }
    int countBal(TreeNode<T>* node){                //����һ������ƽ�����ӣ�ƽ������Ϊ�������߶� - �������߶ȣ��� -1 ~ 1 ֮����ƽ��
        int leftHeight = 0;                         //�洢�������ĸ߶�
        int rightHeight = 0;                        //�洢�������ĸ߶�
        if(node->isLeaf()){                         //Ҷ�ӽ�㷵��0
            return BAL;
        }else if(node->leftChild && node->rightChild){
            getHeight(node->leftChild, 0, leftHeight);
            getHeight(node->rightChild, 0, rightHeight);
            return rightHeight - leftHeight;
        }else if(node->leftChild){
            getHeight(node->leftChild, 0, leftHeight);
            return 0 - leftHeight;
        }else{
            getHeight(node->rightChild, 0, rightHeight);
            return rightHeight;
        }
    }
    void revolve(TreeNode<T>* pointer, TreeNode<T>* last){      //�ı�Ҫ��ת�����ĸ����
        if(pointer->parent){
            if(pointer == pointer->parent->leftChild)
                pointer->parent->leftChild = last;
            else
                pointer->parent->rightChild = last;
        }
        last->parent = pointer->parent;
        pointer->parent = last;
    }
    void LLrevolve(TreeNode<T>* pointer, TreeNode<T>* last1){   //����
        revolve(pointer, last1);
        pointer->leftChild = last1->rightChild;
        last1->rightChild->parent = pointer;
        last1->rightChild = pointer;
    }
    void RRrevolve(TreeNode<T>* pointer, TreeNode<T>* last1){   //�ҵ���
        revolve(pointer, last1);
        pointer->rightChild = last1->leftChild;
        last1->leftChild->parent = pointer;
        last1->leftChild = pointer;
    }
    void LRrevolve(TreeNode<T>* pointer, TreeNode<T>* last1, TreeNode<T>* last2){  //����˫��
        revolve(pointer, last2);
        last1->rightChild = last2->leftChild;
        last2->leftChild->parent = last1;
        pointer->leftChild = last2->rightChild;
        last2->rightChild->parent = pointer;
        last2->leftChild = last1;
        last1->parent = last2;
        last2->rightChild = pointer;
    }
    void RLrevolve(TreeNode<T>* pointer, TreeNode<T>* last1, TreeNode<T>* last2){  //����˫��
        revolve(pointer, last2);
        last1->leftChild = last2->rightChild;
        last2->rightChild->parent = last1;
        pointer->rightChild = last2->leftChild;
        last2->leftChild->parent = pointer;
        last2->rightChild = last1;
        last1->parent = last2;
        last2->leftChild = pointer;
    }
    void adjust(TreeNode<T>* pointer, int type){    //������������ƽ�⣬pointer Ϊ��ʼ�����Ľڵ㣬typeΪ���������ͣ�INSERT �� DELETE
        while(pointer){                             //��ǰ������ʱ�����ϼ���ƽ�����ӣ�ֱ����һ����ƽ��Ľ�㣬������ƽ��
            int balance = countBal(pointer);        //���㵱ǰ����ƽ�����ӣ����ƽ�⵱ǰ�����ڵ�ǰ���ĸ���㣬�����ƽ�������ǰ��㼰������
            int height = 0;
            TreeNode<T>* item = NULL;
            getHeight(pointer, 0, height);          //��ø߶�
            if(balance < -1 || balance > 1){
                if(balance == -2){                  //����
                    int lastBal = countBal(pointer->leftChild);
                    if(lastBal == -1 || lastBal == 0){//LL��
                        TreeNode<T>* last1 = pointer->leftChild;
                        LLrevolve(pointer, last1);
                        item = last1;
                        if(type == INSERT)          //����Ļ���������һ����ƽ����
                            return;
                    }else if(lastBal == 1){         //LR��
                        TreeNode<T>* last1 = pointer->leftChild;
                        TreeNode<T>* last2 = pointer->leftChild->rightChild;
                        LRrevolve(pointer, last1, last2);
                        item = last2;
                        if(type == INSERT)
                            return;
                    }
                }else if(balance == 2){             //����
                    int lastBal = countBal(pointer->rightChild);
                    if(lastBal == 1 || lastBal == 0){//RR��
                        TreeNode<T>* last1 = pointer->rightChild;
                        RRrevolve(pointer, last1);
                        item = last1;
                        if(type == INSERT)
                            return;
                    }else if(lastBal == -1){        //RL��
                        TreeNode<T>* last1 = pointer->rightChild;
                        TreeNode<T>* last2 = pointer->rightChild->leftChild;
                        RLrevolve(pointer, last1, last2);
                        item = last2;
                        if(type == INSERT)
                            return;
                    }
                }
                if(type == DELETE){                 //ɾ���Ļ�һֱ��������ת�������߶Ȳ���
                    int height2 = 0;
                    getHeight(item, 0, height2);
                    if(height == height2)
                        return;
                }
            }
            pointer = pointer->parent;
        }
    }
    void insert(T data){                            //�����½��
        TreeNode<T>* node = new TreeNode<T>(data);
        if(!root){                                  //�����Ϊ������Ϊ���ڵ�
            root = node;
        }else{
            TreeNode<T>* pointer = root;
            while(pointer){
                if(pointer->data == data)           //����Ѵ�����ͬ�ؼ��룬�򷵻�
                    break;
                else if(pointer->data > data){      //���Ҫ������ؼ���ȵ�ǰ���ؼ���С������ָ��Ϊ�գ�������Ϊ����
                    if(!pointer->leftChild){
                        pointer->leftChild = node;
                        node->parent = pointer;
                        break;
                    }else{                          //����ǰָ�������ƶ�
                        pointer = pointer->leftChild;
                    }
                }else if(pointer->data < data){
                    if(!pointer->rightChild){
                        pointer->rightChild = node;
                        node->parent = pointer;
                        break;
                    }else{
                        pointer = pointer->rightChild;
                    }
                }
            }
        }
        TreeNode<T>* pointer = node->parent;
        adjust(pointer, INSERT);                    //��������һ����ƽ��Ľ����ƽ��
    }
    void print(TreeNode<T>* node){                  //��ӡ��������ǰ��ݹ����
        TreeNode<T>* pointer = node;
        if (pointer != NULL) {
            cout<<pointer->data<<" ";
            print(pointer->leftChild);
            print(pointer->rightChild);
        }
    }
    void print2(TreeNode<T>* node){                 //��ӡ������������ݹ����
        TreeNode<T>* pointer = node;
        if (pointer != NULL) {
            print2(pointer->leftChild);
            cout<<pointer->data<<" ";
            print2(pointer->rightChild);
        }
    }
    TreeNode<T>* search(T data){                    //����
        TreeNode<T>* pointer = root;
        while(pointer){
            if(pointer->data > data)                //�����ǰ���ؼ������Ҫ���ҵĹؼ��룬����������������
                pointer = pointer->leftChild;
            else if(pointer->data < data)           //�����ǰ���ؼ���С��Ҫ���ҵĹؼ��룬����������������
                pointer = pointer->rightChild;
            else if(pointer->data == data){         //�����򷵻ص�ǰ���
                return pointer;
            }
        }
        return NULL;                                //û�ҵ�����NULL
    }
    void emptyNode(TreeNode<T>* pointer){
        if(pointer->parent->leftChild == pointer)   //������Ӧָ����Ϊ��
            pointer->parent->leftChild = NULL;
        else
            pointer->parent->rightChild = NULL;
    }
    TreeNode<T>* del(T data){                       //����ɾ����㣬����ʵ�ʱ�ɾ����������ĸ����
        TreeNode<T>* pointer;                       //Ҫɾ���Ľ��
        TreeNode<T>* item;
        pointer = search(data);
        if(pointer){
            if(pointer->isLeaf()){                  //Ҫɾ���Ľ��ΪҶ�ӽ��ʱ��ֱ��ɾ���˽ڵ�
                if(pointer == root){
                    root = NULL;
                    return NULL;                    //��ɾ�����ǿ����򷵻ؿ�ָ��
                }
                item =  pointer->parent;
                emptyNode(pointer);
                delete pointer;
                pointer = NULL;
                return item;                        //���ظ����
            }else if(pointer->leftChild){           //�������Ҷ�ӽڵ��ø���ɾ����ɾ����Ĭ��ѡ�������е����ֵ����������ѡ����������Сֵ������
                TreeNode<T>* node = pointer->leftChild;
                while(node->rightChild)             //�ҵ������������ֵ
                    node = node->rightChild;
                item = node->parent;                //item��Ϊ����ĸ����
                if(node->leftChild){                //������������ӣ��������Ӵ������������丸�����Һ���ָ����Ϊ��
                    item->rightChild = node->leftChild;
                    node->leftChild->parent = item;
                }else{
                    emptyNode(node);
                }
                pointer->data = node->data;         //������Ĺؼ������Ҫɾ��Ԫ�صĹؼ���
                delete node;                        //��������
                node = NULL;
                return item;                        //�����������
            }else{
                TreeNode<T>* node = pointer->rightChild;
                while(node->leftChild)
                    node = node->leftChild;
                item = node->parent;
                if(node->rightChild){
                    item->leftChild = node->rightChild;
                    node->rightChild->parent = item;
                }else{
                    emptyNode(node);
                }
                pointer->data = node->data;
                delete node;
                node = NULL;
                return item;
            }
        }
        return NULL;                                //δ�ҵ����ؿ�ָ��
    }
    void deleteX(T data){                           //ɾ��ָ����㣬��������������ƽ��
        TreeNode<T>* pointer = del(data);           //����ɾ��ָ����㣬�����ʵ��ɾ�����ĸ���㣬�Ӵ˽�㿪ʼ���ϵ�������������ת��߶Ȳ���
        adjust(pointer, DELETE);
    }
};

#endif // AVL_H_INCLUDED
