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
    T element;                                  //结点的数据域
    BinaryTreeNode<T> *leftChild;               //结点的左孩子结点
    BinaryTreeNode<T> *rightChild;              //结点的右孩子结点
public:
    BinaryTreeNode(){                           //默认构造函数
        leftChild = NULL;
        rightChild = NULL;
    }
    //给定数据值和左右孩子结点的构造函数
    BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l = NULL, BinaryTreeNode<T> *r = NULL){
        element = ele;
        leftChild = l;
        rightChild = r;
    }
    BinaryTreeNode<T>* getLeftChild() const{    //返回该结点的左孩子结点
        return leftChild;
    }
    BinaryTreeNode<T>* getRightChild() const{   //返回该结点的右孩子结点
        return rightChild;
    }
    void setLeftChild(BinaryTreeNode<T> *l){    //设置该结点的左孩子结点
        leftChild = l;
    }
    void setRightChild(BinaryTreeNode<T> *r){   //设置该结点的右孩子结点
        rightChild = r;
    }
    T getValue() const{                         //返回该结点的数据值
        return element;
    }
    void setValue(const T& val){                //设置该结点的数据值
        element = val;
    }
    bool isLeaf() const{                        //判断该结点是否为叶子结点
        return (!leftChild && !rightChild);
    }
};

template <class T>
class BinaryTree{
private:
    BinaryTreeNode<T> *root;                                                 //二叉树根节点
public:
    BinaryTree(){                                                            //默认构造函数
        root = NULL;
    }
    ~BinaryTree(){                                                           //析构函数
        destory(root);
    }
    BinaryTreeNode<T>* creatTree(vector<T> a, int size, int &i, T& invalid){ //创建二叉树
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
    void destory(BinaryTreeNode<T>* node){                                   //销毁二叉树
        BinaryTreeNode<T>* temp = node;
        if(temp == NULL)
            return;
        destory(temp->leftChild);
        destory(temp->rightChild);
        delete temp;
        temp = NULL;
    }
    bool isEmpty() const{                                                    //判断二叉树是否为空树
        return (root == NULL);
    }
    BinaryTreeNode<T>* getRoot() const{                                      //返回二叉树的根结点
        return root;
    }
    void setRoot(BinaryTreeNode<T> *node){
        root = node;
    }
    BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) const{          //返回current结点的父结点
    }
    BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>* current) const{     //返回current结点的左兄弟
        return current->leftChild;
    }
    BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>* current) const{    //返回current结点的右兄弟
        return current->rightChild;
    }
    void breadthFirstOrder(){                                                //广度优先遍历以riit为根结点的子树
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
    void PreOrder (BinaryTreeNode<T>* node){                                 //前序递归遍历二叉树或其子树
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            visit(pointer);		                                             // 访问当前结点
            PreOrder(pointer->leftChild);	                                 // 前序遍历左子树
            PreOrder(pointer->rightChild);	                                 // 前序遍历右子树
          }
    }
    void MidOrder (BinaryTreeNode<T>* node){                                 //中序递归遍历二叉树或其子树
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            MidOrder(pointer->leftChild);
            visit(pointer);
            MidOrder(pointer->rightChild);
          }
    }
    void AftOrder (BinaryTreeNode<T>* node){                                 //后序递归遍历二叉树或其子树
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            AftOrder(pointer->leftChild);
            AftOrder(pointer->rightChild);
            visit(pointer);
          }
    }
    void visit(BinaryTreeNode<T>* current){                                  //访问当前结点
        cout<<current->element<<'\t';
    }
    void preTraversal(BinaryTreeNode<T> *root){                              //深度前序非递归周游
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* pointer = root;
        while(!s.empty() || pointer){                                        //栈空且指针指向NULL时停止循环
            if(pointer){
                visit(pointer);
                if(pointer->rightChild != NULL)                              //非空右孩子入栈
                    s.push(pointer->rightChild);
                pointer = pointer->leftChild;
            }else{
                pointer = s.top();                                           //获得栈顶元素
                s.pop();                                                     //弹栈
            }
        }
    }
    void midTraversal(BinaryTreeNode<T> *root){                              //深度中序非递归周游
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T> *pointer = root;
        while(!s.empty() || pointer){
            if(pointer){
                s.push(pointer);                                             //当前指针入栈
                pointer = pointer->leftChild;                                //左路下降
            }else{                                                           //左子树访问完毕，转向访问右子树
                pointer = s.top();                                           //获得栈顶元素
                s.pop();                                                     //弹栈
                visit(pointer);                                              //访问当前结点
                pointer = pointer->rightChild;                               //指针指向右孩子
            }
        }
    }
    void aftTraversal(BinaryTreeNode<T> *root){                              //深度后序非递归周游
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T> *p = root,                                         //当前指针
                          *q = root;                                         //上一个访问的指针
        while(p != NULL){
            for(; p->leftChild != NULL; p = p->leftChild)                    //从左下第一个结点开始循环
                s.push(p);
            while(p != NULL && (p->rightChild == NULL || p->rightChild == q)){     //当前结点不为空并且其右孩子为空或访问过则访问当前结点
                visit(p);
                q = p;
                if(s.empty())                                                //栈空则返回
                    return;
                p = s.top();                                                 //弹栈
                s.pop();
            }
            s.push(p);                                                       //当前结点不为空且右孩子没被访问过则当前结点入栈
            p = p->rightChild;
        }
    }
};

#endif // BINARYTREE_H_INCLUDED
