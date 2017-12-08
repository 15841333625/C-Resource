#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <math.h>
using namespace std;

template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode{
    friend class BinaryTree<T>;
private:
    T element;                                  //����������
    BinaryTreeNode<T> *leftChild;               //�������ӽ��
    BinaryTreeNode<T> *rightChild;              //�����Һ��ӽ��
public:
    BinaryTreeNode(){                           //Ĭ�Ϲ��캯��
        leftChild = NULL;
        rightChild = NULL;
    }
    //��������ֵ�����Һ��ӽ��Ĺ��캯��
    BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l = NULL, BinaryTreeNode<T> *r = NULL){
        element = ele;
        leftChild = l;
        rightChild = r;
    }
    BinaryTreeNode<T>* getLeftChild() const{    //���ظý������ӽ��
        return leftChild;
    }
    BinaryTreeNode<T>* getRightChild() const{   //���ظý����Һ��ӽ��
        return rightChild;
    }
    void setLeftChild(BinaryTreeNode<T> *l){    //���øý������ӽ��
        leftChild = l;
    }
    void setRightChild(BinaryTreeNode<T> *r){   //���øý����Һ��ӽ��
        rightChild = r;
    }
    T getValue() const{                         //���ظý�������ֵ
        return element;
    }
    void setValue(const T& val){                //���øý�������ֵ
        element = val;
    }
    bool isLeaf() const{                        //�жϸý���Ƿ�ΪҶ�ӽ��
        return (!leftChild && !rightChild);
    }
};

template <class T>
class BinaryTree{
private:
    BinaryTreeNode<T> *root;                                                 //���������ڵ�
public:
    BinaryTree(){                                                            //Ĭ�Ϲ��캯��
        root = NULL;
    }
    ~BinaryTree(){                                                           //��������
        destory(root);
    }
    BinaryTreeNode<T>* creatTree(vector<T> a, int size, int &i, T& invalid){ //����������
        BinaryTreeNode<T>* _root = NULL;
        if(i < size && a[i] != invalid){
            _root = new BinaryTreeNode<T>();
            _root->setValue(a[i]);
            if(i == 0)
                root = _root;
            _root->setLeftChild(creatTree(a, size, ++i, invalid));
            _root->setRightChild(creatTree(a, size, ++i, invalid));
        }
        return _root;
    }
    void destory(BinaryTreeNode<T>* node){                                   //���ٶ�����
        BinaryTreeNode<T>* temp = node;
        if(temp == NULL)
            return;
        destory(temp->leftChild);
        destory(temp->rightChild);
        delete temp;
        temp = NULL;
    }
    bool isEmpty() const{                                                    //�ж϶������Ƿ�Ϊ����
        return (root == NULL);
    }
    BinaryTreeNode<T>* getRoot() const{                                      //���ض������ĸ����
        return root;
    }
    void setRoot(BinaryTreeNode<T> *node){                                   //���ø��ڵ�
        root = node;
    }
    BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) const{          //����current���ĸ����
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* pointer = root;
        BinaryTreeNode<T>* parent = pointer;
        while(!s.empty() || pointer){                                        //ջ����ָ��ָ��NULLʱֹͣѭ��
            if(pointer){
                if(pointer != current){
                    if(pointer->rightChild != NULL)                          //�ǿ��Һ�����ջ
                        s.push(pointer->rightChild);
                    parent = pointer;
                    pointer = pointer->leftChild;
                }else if(pointer == current){
                    return parent;
                }
            }else{
                pointer = s.top();                                           //���ջ��Ԫ��
                s.pop();                                                     //��ջ
            }
        }
        return NULL;
    }
    void breadthFirstOrder(){                                                //������ȱ�����riitΪ����������
        queue<BinaryTreeNode<T> *> nodeQueue;
        BinaryTreeNode<T> *pointer = root;
        if(pointer)
            nodeQueue.push(pointer);
        while(!nodeQueue.empty()){
            pointer = nodeQueue.front();
            visit(pointer);
            nodeQueue.pop();
            if(pointer->leftChild)
                nodeQueue.push(pointer->leftChild);
            if(pointer->rightChild)
                nodeQueue.push(pointer->rightChild);
        }
        cout<<endl;
    }
    void getLength(BinaryTreeNode<T>* node, int &length){
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            ++length;
            getLength(pointer->leftChild, length);
            getLength(pointer->rightChild, length);
          }
    }
    void PreOrder (BinaryTreeNode<T>* node){                                 //ǰ��ݹ������������������
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            visit(pointer);		                                             // ���ʵ�ǰ���
            PreOrder(pointer->leftChild);	                                 // ǰ�����������
            PreOrder(pointer->rightChild);	                                 // ǰ�����������
          }
    }
    void MidOrder (BinaryTreeNode<T>* node){                                 //����ݹ������������������
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            MidOrder(pointer->leftChild);
            visit(pointer);
            MidOrder(pointer->rightChild);
          }
    }
    void AftOrder (BinaryTreeNode<T>* node){                                 //����ݹ������������������
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            AftOrder(pointer->leftChild);
            AftOrder(pointer->rightChild);
            visit(pointer);
          }
    }
    void visit(BinaryTreeNode<T>* current){                                  //���ʵ�ǰ���
        cout<<current->element<<'\t';
    }
    void preTraversal(BinaryTreeNode<T> *root){                              //���ǰ��ǵݹ�����
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* pointer = root;
        while(!s.empty() || pointer){                                        //ջ����ָ��ָ��NULLʱֹͣѭ��
            if(pointer){
                visit(pointer);
                if(pointer->rightChild != NULL)                              //�ǿ��Һ�����ջ
                    s.push(pointer->rightChild);
                pointer = pointer->leftChild;
            }else{
                pointer = s.top();                                           //���ջ��Ԫ��
                s.pop();                                                     //��ջ
            }
        }
    }
    void midTraversal(BinaryTreeNode<T> *root){                              //�������ǵݹ�����
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T> *pointer = root;
        while(!s.empty() || pointer){
            if(pointer){
                s.push(pointer);                                             //��ǰָ����ջ
                pointer = pointer->leftChild;                                //��·�½�
            }else{                                                           //������������ϣ�ת�����������
                pointer = s.top();                                           //���ջ��Ԫ��
                s.pop();                                                     //��ջ
                visit(pointer);                                              //���ʵ�ǰ���
                pointer = pointer->rightChild;                               //ָ��ָ���Һ���
            }
        }
    }
    void aftTraversal(BinaryTreeNode<T> *root){                              //��Ⱥ���ǵݹ�����
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T> *p = root,                                         //��ǰָ��
                          *q = root;                                         //��һ�����ʵ�ָ��
        while(p != NULL){
            for(; p->leftChild != NULL; p = p->leftChild)                    //�����µ�һ����㿪ʼѭ��
                s.push(p);
            while(p != NULL && (p->rightChild == NULL || p->rightChild == q)){     //��ǰ��㲻Ϊ�ղ������Һ���Ϊ�ջ���ʹ�����ʵ�ǰ���
                visit(p);
                q = p;
                if(s.empty())                                                //ջ���򷵻�
                    return;
                p = s.top();                                                 //��ջ
                s.pop();
            }
            s.push(p);                                                       //��ǰ��㲻Ϊ�����Һ���û�����ʹ���ǰ�����ջ
            p = p->rightChild;
        }
    }
    void countDegree(BinaryTreeNode<T>* pointer, int &count, int num){       //�����Ϊ0�Ľ�����
        if (pointer != NULL) {
            if(num == 0){
                if(!pointer->leftChild && !pointer->rightChild)              //���Һ��Ӷ�������
                    ++count;
            }
            else if(num == 1){
                if((pointer->leftChild || pointer->rightChild) && !(pointer->leftChild && pointer->rightChild))  //���Һ���ֻ��һ��
                    ++count;
            }
            else if(num == 2){
                if(pointer->leftChild && pointer->rightChild)                //���Һ��Ӷ�����
                    ++count;
            }
            countDegree(pointer->leftChild, count, num);
            countDegree(pointer->rightChild, count, num);
        }
    }
    int getDegree(int num){                                                  //���ض�Ϊnum�Ľ��ĸ���������ΪҪ��ѯ�Ķ�����count Ϊ��������
        int count = 0;
        BinaryTreeNode<T>* node = root;
        if(num == 0 || num == 1 || num == 2){
            countDegree(node, count, num);
            node = NULL;
        }
        else
            cout<<"����Υ��"<<endl;
        return count;
    }
    void countHeight(BinaryTreeNode<T>* pointer, int count, int &max){       //�������ĸ߶ȣ�count��¼ÿһ�������ĸ߶ȣ����ô洢���������ã�max��¼�����������߶ȣ������øı�ͬһ��ֵ
        if (pointer != NULL) {
            ++count;
            if(max <= count)
                max = count;
            countHeight(pointer->leftChild, count, max);
            countHeight(pointer->rightChild, count, max);
          }
    }
    int getHeight(){                                                         //�������ĸ߶�
        int count = 0, max = 0;
        BinaryTreeNode<T>* node = root;
        countHeight(node, count, max);
        return max;
    }
    void countWidth(BinaryTreeNode<T>* pointer, int width[], int index){     //��������ȣ�width���鴢��ÿ��Ŀ�ȣ�index��ʾ��index��
        if (pointer != NULL) {
            ++index;
            ++width[index];
            countWidth(pointer->leftChild, width, index);
            countWidth(pointer->rightChild, width, index);
        }
    }
    int getWidth(){                                                          //�������߶�
        int height = getHeight();
        int width[height + 1] = {0};
        BinaryTreeNode<T>* pointer = root;
        int index = 0;
        countWidth(pointer, width, index);
        int max = 0;                                                         //�������ֵ
        for(int i = 1; i < height + 1; i ++){
            if(max < width[i])
                max = width[i];
        }
        return max;
    }
    void swapChild(BinaryTreeNode<T>* node){                                 //����ÿ���ڵ�����Ӻ��Һ���
        BinaryTreeNode<T>* pointer = node;
        BinaryTreeNode<T>* temp;
        if (pointer != NULL) {
            swapChild(pointer->leftChild);                                   //��Ϊ�ݹ��л������ҽ���������ֻ�ݹ�������
            if(pointer != root){                                             //������Ǹ��ڵ�
                 BinaryTreeNode<T>* parent = getParent(pointer);
                if(parent->leftChild == pointer){                            //������������
                    temp = pointer;
                    parent->leftChild = parent->rightChild;
                    parent->rightChild = temp;
                    temp = NULL;
                }else{
                    temp = pointer;
                    parent->rightChild = parent->rightChild;
                    parent->leftChild = temp;
                    temp = NULL;
                }
            }
        }
    }
    void deleteLeaves(BinaryTreeNode<T>* node){                              //ɾ������Ҷ�ӽڵ�
        BinaryTreeNode<T>* pointer = node;
        if (pointer != NULL) {
            if(pointer->isLeaf()){                                           //�����Ҷ�ӽڵ㣬ɾ���˽ڵ㲢���õ�ǰ���Ϊ�丸�ڵ�
                BinaryTreeNode<T>* temp = getParent(pointer);
                if(temp->leftChild == pointer){
                    delete pointer;
                    pointer = temp;
                    temp->leftChild = NULL;
                }else{
                    delete pointer;
                    pointer = temp;
                    temp->rightChild = NULL;
                }
            }
            deleteLeaves(pointer->leftChild);
            deleteLeaves(pointer->rightChild);
        }
    }
    void countMax(BinaryTreeNode<T>* pointer, BinaryTreeNode<T>* &max){      //�������ֵ���
        if (pointer != NULL) {
            if(max->element < pointer->element){
                max = pointer;
            }
            countMax(pointer->leftChild, max);
            countMax(pointer->rightChild, max);
        }
    }
    BinaryTreeNode<T>* getMax(){                                             //�������ֵ���
        BinaryTreeNode<T>* pointer = root;
        BinaryTreeNode<T>* max = pointer;
        countMax(pointer, max);
        return max;
    }
    bool isComplete(){                                                       //�ж��Ƿ�Ϊ��ȫ������
        queue<BinaryTreeNode<T> *> nodeQueue;
        vector<BinaryTreeNode<T> *> nodevec;
        BinaryTreeNode<T> *pointer = root;
        int length = 0;
        int size = 0;
        nodeQueue.push(pointer);
        while(!nodeQueue.empty()){
            pointer = nodeQueue.front();
            nodevec.push_back(pointer);
            nodeQueue.pop();
            if(pointer->leftChild == NULL || pointer->rightChild == NULL){
                if(pointer->leftChild)
                    nodeQueue.push(pointer->leftChild);
                break;
            }
            if(pointer->leftChild)
                nodeQueue.push(pointer->leftChild);
            if(pointer->rightChild)
                nodeQueue.push(pointer->rightChild);
        }
        size = nodeQueue.size();
        for(int i = 0; i < size; i ++){
            pointer = nodeQueue.front();
            nodevec.push_back(pointer);
            nodeQueue.pop();
        }
        getLength(root, length);
        size = nodevec.size();
        return (length == size);
    }
};

#endif // BINARYTREE_H_INCLUDED
