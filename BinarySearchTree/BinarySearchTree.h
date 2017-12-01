#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include<iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template<class T>
class TreeNode{
private:
    friend class BinarySearchTree<T>;
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
class BinarySearchTree{
private:
    TreeNode<T>* root;                      //�����
public:
    BinarySearchTree(){
        root = NULL;
    }
    ~BinarySearchTree(){
        destory(root);
    }
    void destory(TreeNode<T>* node){        //���ٶ�����
        TreeNode<T>* temp = node;
        if(temp == NULL)
            return;
        destory(temp->leftChild);
        destory(temp->rightChild);
        delete temp;
        temp = NULL;
    }
    TreeNode<T>* getRoot(){
        return root;
    }
    void insert(T data){                   //�����½��
        TreeNode<T>* node = new TreeNode<T>(data);
        if(!root){                         //�����Ϊ������Ϊ���ڵ�
            root = node;
        }else{
            TreeNode<T>* pointer = root;
            while(pointer){
                if(pointer->data == data)  //����Ѵ�����ͬ�ؼ��룬�򷵻�
                    return;
                else if(pointer->data > data){  //���Ҫ������ؼ���ȵ�ǰ���ؼ���С������ָ��Ϊ�գ�������Ϊ����
                    if(!pointer->leftChild){
                        pointer->leftChild = node;
                        node->parent = pointer;
                        return;
                    }else{                 //����ǰָ�������ƶ�
                        pointer = pointer->leftChild;
                    }
                }else if(pointer->data < data){
                    if(!pointer->rightChild){
                        pointer->rightChild = node;
                        node->parent = pointer;
                        return;
                    }else{
                        pointer = pointer->rightChild;
                    }
                }
            }
        }
    }
    void print(TreeNode<T>* node){                  //��ӡ��������ǰ��ݹ����
         TreeNode<T>* pointer = node;
         if (pointer != NULL) {
            cout<<pointer->data<<" ";
            print(pointer->leftChild);
            print(pointer->rightChild);
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
    void del(T data){
        TreeNode<T>* pointer;
        pointer = search(data);
        if(pointer){
            if(pointer->isLeaf()){                  //Ҫɾ���Ľ��ΪҶ�ӽ��ʱ��ֱ��ɾ���˽ڵ�
                delete pointer;
                pointer = NULL;
                return;
            }else if(pointer->leftChild){           //�������Ҷ�ӽڵ��ø���ɾ����ɾ����Ĭ��ѡ�������е����ֵ����������ѡ����������Сֵ������
                TreeNode<T>* node = pointer->leftChild;
                while(node->rightChild)             //�ҵ������������ֵ
                    node = node->rightChild;
                if(node->leftChild){                //������������ӣ��������Ӵ������������丸�����Һ���ָ����Ϊ��
                    node->parent->rightChild = node->leftChild;
                    node->leftChild->parent = node->parent;
                }else{
                    node->parent->rightChild = NULL;
                }
                pointer->data = node->data;         //������Ĺؼ������Ҫɾ��Ԫ�صĹؼ���
                delete node;                        //��������
                node = NULL;
            }else{
                TreeNode<T>* node = pointer->rightChild;
                while(node->leftChild)
                    node = node->leftChild;
                if(node->rightChild){
                    node->parent->leftChild = node->rightChild;
                    node->rightChild->parent = node->parent;
                }else{
                    node->parent->leftChild = NULL;
                }
                pointer->data = node->data;
                delete node;
                node = NULL;
            }
        }
    }
};

#endif // BINARYSEARCHTREE_H_INCLUDED
