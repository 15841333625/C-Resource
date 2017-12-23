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
    void destory(TreeNode<T>* node){                //销毁二叉树
        TreeNode<T>* temp = node;
        if(temp == NULL)
            return;
        destory(temp->leftChild);
        destory(temp->rightChild);
        delete temp;
        temp = NULL;
    }
    TreeNode<T>* getRoot(){                         //获得根节点
        return root;
    }
    void getHeight(TreeNode<T>* pointer, int count, int &max){  //获得树的高度
        if (pointer != NULL) {
            ++count;
            if(max <= count)
                max = count;
            getHeight(pointer->leftChild, count, max);
            getHeight(pointer->rightChild, count, max);
          }
    }
    int countBal(TreeNode<T>* node){                //计算一个结点的平衡因子，平衡因子为右子树高度 - 左子树高度，在 -1 ~ 1 之间则平衡
        int leftHeight = 0;                         //存储左子树的高度
        int rightHeight = 0;                        //存储右子树的高度
        if(node->isLeaf()){                         //叶子结点返回0
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
    void revolve(TreeNode<T>* pointer, TreeNode<T>* last){      //改变要旋转子数的根结点
        if(pointer->parent){
            if(pointer == pointer->parent->leftChild)
                pointer->parent->leftChild = last;
            else
                pointer->parent->rightChild = last;
        }
        last->parent = pointer->parent;
        pointer->parent = last;
    }
    void LLrevolve(TreeNode<T>* pointer, TreeNode<T>* last1){   //左单旋
        revolve(pointer, last1);
        pointer->leftChild = last1->rightChild;
        last1->rightChild->parent = pointer;
        last1->rightChild = pointer;
    }
    void RRrevolve(TreeNode<T>* pointer, TreeNode<T>* last1){   //右单旋
        revolve(pointer, last1);
        pointer->rightChild = last1->leftChild;
        last1->leftChild->parent = pointer;
        last1->leftChild = pointer;
    }
    void LRrevolve(TreeNode<T>* pointer, TreeNode<T>* last1, TreeNode<T>* last2){  //左右双旋
        revolve(pointer, last2);
        last1->rightChild = last2->leftChild;
        last2->leftChild->parent = last1;
        pointer->leftChild = last2->rightChild;
        last2->rightChild->parent = pointer;
        last2->leftChild = last1;
        last1->parent = last2;
        last2->rightChild = pointer;
    }
    void RLrevolve(TreeNode<T>* pointer, TreeNode<T>* last1, TreeNode<T>* last2){  //右左双旋
        revolve(pointer, last2);
        last1->leftChild = last2->rightChild;
        last2->rightChild->parent = last1;
        pointer->rightChild = last2->leftChild;
        last2->leftChild->parent = pointer;
        last2->rightChild = last1;
        last1->parent = last2;
        last2->leftChild = pointer;
    }
    void adjust(TreeNode<T>* pointer, int type){    //调整二叉树至平衡，pointer 为开始调整的节点，type为调整的类型，INSERT 或 DELETE
        while(pointer){                             //当前结点存在时，向上计算平衡因子，直到第一个不平衡的结点，调整至平衡
            int balance = countBal(pointer);        //计算当前结点的平衡因子，如果平衡当前结点等于当前结点的父结点，如果不平衡调整当前结点及其子树
            int height = 0;
            TreeNode<T>* item = NULL;
            getHeight(pointer, 0, height);          //获得高度
            if(balance < -1 || balance > 1){
                if(balance == -2){                  //左重
                    int lastBal = countBal(pointer->leftChild);
                    if(lastBal == -1 || lastBal == 0){//LL型
                        TreeNode<T>* last1 = pointer->leftChild;
                        LLrevolve(pointer, last1);
                        item = last1;
                        if(type == INSERT)          //插入的话调整到第一个不平衡结点
                            return;
                    }else if(lastBal == 1){         //LR型
                        TreeNode<T>* last1 = pointer->leftChild;
                        TreeNode<T>* last2 = pointer->leftChild->rightChild;
                        LRrevolve(pointer, last1, last2);
                        item = last2;
                        if(type == INSERT)
                            return;
                    }
                }else if(balance == 2){             //右重
                    int lastBal = countBal(pointer->rightChild);
                    if(lastBal == 1 || lastBal == 0){//RR型
                        TreeNode<T>* last1 = pointer->rightChild;
                        RRrevolve(pointer, last1);
                        item = last1;
                        if(type == INSERT)
                            return;
                    }else if(lastBal == -1){        //RL型
                        TreeNode<T>* last1 = pointer->rightChild;
                        TreeNode<T>* last2 = pointer->rightChild->leftChild;
                        RLrevolve(pointer, last1, last2);
                        item = last2;
                        if(type == INSERT)
                            return;
                    }
                }
                if(type == DELETE){                 //删除的话一直调整到旋转后子树高度不变
                    int height2 = 0;
                    getHeight(item, 0, height2);
                    if(height == height2)
                        return;
                }
            }
            pointer = pointer->parent;
        }
    }
    void insert(T data){                            //插入新结点
        TreeNode<T>* node = new TreeNode<T>(data);
        if(!root){                                  //如果树为空则设为根节点
            root = node;
        }else{
            TreeNode<T>* pointer = root;
            while(pointer){
                if(pointer->data == data)           //如果已存在相同关键码，则返回
                    break;
                else if(pointer->data > data){      //如果要插入结点关键码比当前结点关键码小且左孩子指针为空，则设置为左孩子
                    if(!pointer->leftChild){
                        pointer->leftChild = node;
                        node->parent = pointer;
                        break;
                    }else{                          //否则当前指针向左移动
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
        adjust(pointer, INSERT);                    //调整到第一个不平衡的结点至平衡
    }
    void print(TreeNode<T>* node){                  //打印二叉树，前序递归遍历
        TreeNode<T>* pointer = node;
        if (pointer != NULL) {
            cout<<pointer->data<<" ";
            print(pointer->leftChild);
            print(pointer->rightChild);
        }
    }
    void print2(TreeNode<T>* node){                 //打印二叉树，中序递归遍历
        TreeNode<T>* pointer = node;
        if (pointer != NULL) {
            print2(pointer->leftChild);
            cout<<pointer->data<<" ";
            print2(pointer->rightChild);
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
    void emptyNode(TreeNode<T>* pointer){
        if(pointer->parent->leftChild == pointer)   //父结点对应指针置为空
            pointer->parent->leftChild = NULL;
        else
            pointer->parent->rightChild = NULL;
    }
    TreeNode<T>* del(T data){                       //复制删除结点，返回实际被删除的替身结点的父结点
        TreeNode<T>* pointer;                       //要删除的结点
        TreeNode<T>* item;
        pointer = search(data);
        if(pointer){
            if(pointer->isLeaf()){                  //要删除的结点为叶子结点时，直接删除此节点
                if(pointer == root){
                    root = NULL;
                    return NULL;                    //若删除后是空树则返回空指针
                }
                item =  pointer->parent;
                emptyNode(pointer);
                delete pointer;
                pointer = NULL;
                return item;                        //返回父结点
            }else if(pointer->leftChild){           //如果不是叶子节点用复制删除法删除，默认选左子树中的最大值做替身，否则选右子树的最小值做替身
                TreeNode<T>* node = pointer->leftChild;
                while(node->rightChild)             //找到左子树的最大值
                    node = node->rightChild;
                item = node->parent;                //item设为替身的父结点
                if(node->leftChild){                //如果替身有左孩子，则用左孩子代替替身，否则将其父结点的右孩子指针置为空
                    item->rightChild = node->leftChild;
                    node->leftChild->parent = item;
                }else{
                    emptyNode(node);
                }
                pointer->data = node->data;         //用替身的关键码代替要删除元素的关键码
                delete node;                        //销毁替身
                node = NULL;
                return item;                        //返回替身父结点
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
        return NULL;                                //未找到返回空指针
    }
    void deleteX(T data){                           //删除指定结点，并调整二叉树至平衡
        TreeNode<T>* pointer = del(data);           //复制删除指定结点，并获得实际删除结点的父结点，从此结点开始向上调整二叉树至旋转后高度不变
        adjust(pointer, DELETE);
    }
};

#endif // AVL_H_INCLUDED
