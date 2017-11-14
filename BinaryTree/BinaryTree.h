#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
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
    void setRoot(BinaryTreeNode<T> *node){
        root = node;
    }
    BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) const{          //����current���ĸ����
    }
    BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>* current) const{     //����current�������ֵ�
        return current->leftChild;
    }
    BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>* current) const{    //����current�������ֵ�
        return current->rightChild;
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
};

#endif // BINARYTREE_H_INCLUDED
