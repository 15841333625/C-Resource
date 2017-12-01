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
    TreeNode* parent;           //父结点
    TreeNode* leftChild;        //左孩子
    TreeNode* rightChild;       //右孩子
    T data;                     //关键码
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
    TreeNode<T>* root;                      //根结点
public:
    BinarySearchTree(){
        root = NULL;
    }
    ~BinarySearchTree(){
        destory(root);
    }
    void destory(TreeNode<T>* node){        //销毁二叉树
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
    void insert(T data){                   //插入新结点
        TreeNode<T>* node = new TreeNode<T>(data);
        if(!root){                         //如果树为空则设为根节点
            root = node;
        }else{
            TreeNode<T>* pointer = root;
            while(pointer){
                if(pointer->data == data)  //如果已存在相同关键码，则返回
                    return;
                else if(pointer->data > data){  //如果要插入结点关键码比当前结点关键码小且左孩子指针为空，则设置为左孩子
                    if(!pointer->leftChild){
                        pointer->leftChild = node;
                        node->parent = pointer;
                        return;
                    }else{                 //否则当前指针向左移动
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
    void print(TreeNode<T>* node){                  //打印二叉树，前序递归遍历
         TreeNode<T>* pointer = node;
         if (pointer != NULL) {
            cout<<pointer->data<<" ";
            print(pointer->leftChild);
            print(pointer->rightChild);
          }
    }
    TreeNode<T>* search(T data){                    //查找
        TreeNode<T>* pointer = root;
        while(pointer){
            if(pointer->data > data)                //如果当前结点关键码大于要查找的关键码，继续查找其左子树
                pointer = pointer->leftChild;
            else if(pointer->data < data)           //如果当前结点关键码小于要查找的关键码，继续查找其右子树
                pointer = pointer->rightChild;
            else if(pointer->data == data){         //等于则返回当前结点
                return pointer;
            }
        }
        return NULL;                                //没找到返回NULL
    }
    void del(T data){
        TreeNode<T>* pointer;
        pointer = search(data);
        if(pointer){
            if(pointer->isLeaf()){                  //要删除的结点为叶子结点时，直接删除此节点
                delete pointer;
                pointer = NULL;
                return;
            }else if(pointer->leftChild){           //如果不是叶子节点用复制删除法删除，默认选左子树中的最大值做替身，否则选右子树的最小值做替身
                TreeNode<T>* node = pointer->leftChild;
                while(node->rightChild)             //找到左子树的最大值
                    node = node->rightChild;
                if(node->leftChild){                //如果替身有左孩子，则用左孩子代替替身，否则将其父结点的右孩子指针置为空
                    node->parent->rightChild = node->leftChild;
                    node->leftChild->parent = node->parent;
                }else{
                    node->parent->rightChild = NULL;
                }
                pointer->data = node->data;         //用替身的关键码代替要删除元素的关键码
                delete node;                        //销毁替身
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
