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
    void setRoot(BinaryTreeNode<T> *node){                                   //设置根节点
        root = node;
    }
    BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) const{          //返回current结点的父结点
        stack<BinaryTreeNode<T>*> s;
        BinaryTreeNode<T>* pointer = root;
        BinaryTreeNode<T>* parent = pointer;
        while(!s.empty() || pointer){                                        //栈空且指针指向NULL时停止循环
            if(pointer){
                if(pointer != current){
                    if(pointer->rightChild != NULL)                          //非空右孩子入栈
                        s.push(pointer->rightChild);
                    parent = pointer;
                    pointer = pointer->leftChild;
                }else if(pointer == current){
                    return parent;
                }
            }else{
                pointer = s.top();                                           //获得栈顶元素
                s.pop();                                                     //弹栈
            }
        }
        return NULL;
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
    void getLength(BinaryTreeNode<T>* node, int &length){
        BinaryTreeNode<T>* pointer = node;
         if (pointer != NULL) {
            ++length;
            getLength(pointer->leftChild, length);
            getLength(pointer->rightChild, length);
          }
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
    void countDegree(BinaryTreeNode<T>* pointer, int &count, int num){       //计算度为0的结点个数
        if (pointer != NULL) {
            if(num == 0){
                if(!pointer->leftChild && !pointer->rightChild)              //左右孩子都不存在
                    ++count;
            }
            else if(num == 1){
                if((pointer->leftChild || pointer->rightChild) && !(pointer->leftChild && pointer->rightChild))  //左右孩子只有一个
                    ++count;
            }
            else if(num == 2){
                if(pointer->leftChild && pointer->rightChild)                //左右孩子都存在
                    ++count;
            }
            countDegree(pointer->leftChild, count, num);
            countDegree(pointer->rightChild, count, num);
        }
    }
    int getDegree(int num){                                                  //返回度为num的结点的个数，参数为要查询的度数，count 为计数变量
        int count = 0;
        BinaryTreeNode<T>* node = root;
        if(num == 0 || num == 1 || num == 2){
            countDegree(node, count, num);
            node = NULL;
        }
        else
            cout<<"参数违法"<<endl;
        return count;
    }
    void countHeight(BinaryTreeNode<T>* pointer, int count, int &max){       //计算树的高度，count记录每一棵子树的高度，不用存储，不用引用，max记录整棵树的最大高度，用引用改变同一个值
        if (pointer != NULL) {
            ++count;
            if(max <= count)
                max = count;
            countHeight(pointer->leftChild, count, max);
            countHeight(pointer->rightChild, count, max);
          }
    }
    int getHeight(){                                                         //返回树的高度
        int count = 0, max = 0;
        BinaryTreeNode<T>* node = root;
        countHeight(node, count, max);
        return max;
    }
    void countWidth(BinaryTreeNode<T>* pointer, int width[], int index){     //计算最大宽度，width数组储存每层的宽度，index表示第index层
        if (pointer != NULL) {
            ++index;
            ++width[index];
            countWidth(pointer->leftChild, width, index);
            countWidth(pointer->rightChild, width, index);
        }
    }
    int getWidth(){                                                          //返回最大高度
        int height = getHeight();
        int width[height + 1] = {0};
        BinaryTreeNode<T>* pointer = root;
        int index = 0;
        countWidth(pointer, width, index);
        int max = 0;                                                         //返回最大值
        for(int i = 1; i < height + 1; i ++){
            if(max < width[i])
                max = width[i];
        }
        return max;
    }
    void swapChild(BinaryTreeNode<T>* node){                                 //交换每个节点的左孩子和右孩子
        BinaryTreeNode<T>* pointer = node;
        BinaryTreeNode<T>* temp;
        if (pointer != NULL) {
            swapChild(pointer->leftChild);                                   //因为递归中会有左右交换，所以只递归左子树
            if(pointer != root){                                             //如果不是根节点
                 BinaryTreeNode<T>* parent = getParent(pointer);
                if(parent->leftChild == pointer){                            //左右子树交换
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
    void deleteLeaves(BinaryTreeNode<T>* node){                              //删除所有叶子节点
        BinaryTreeNode<T>* pointer = node;
        if (pointer != NULL) {
            if(pointer->isLeaf()){                                           //如果是叶子节点，删除此节点并设置当前结点为其父节点
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
    void countMax(BinaryTreeNode<T>* pointer, BinaryTreeNode<T>* &max){      //计算最大值结点
        if (pointer != NULL) {
            if(max->element < pointer->element){
                max = pointer;
            }
            countMax(pointer->leftChild, max);
            countMax(pointer->rightChild, max);
        }
    }
    BinaryTreeNode<T>* getMax(){                                             //返回最大值结点
        BinaryTreeNode<T>* pointer = root;
        BinaryTreeNode<T>* max = pointer;
        countMax(pointer, max);
        return max;
    }
    bool isComplete(){                                                       //判断是否为完全二叉树
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
