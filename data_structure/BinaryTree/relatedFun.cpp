#include "relatedFun.h"

void preMidCreate(string pre, string mid, BinaryTreeNode<char> *node){  //已知前序中序生成树
    int ssize = pre.size();
    node->setValue(pre[0]);                                             //设定当前结点值为前序字符串第一个字符
    if(ssize == 1)                                                      //字符串长度为1时停止递归
        return;
    else{
        for(int i = 0; i < ssize; i ++){
            if(mid[i] == pre[0]){                                       //中序字符等于前序第一个字符时
                if(i != 0){                                             //如果不在中序字符串首，则有左孩子
                    BinaryTreeNode<char> *left;
                    left = new BinaryTreeNode<char>();                  //创建新结点
                    node->setLeftChild(left);
                    string p (pre.substr(1, i));                        //以当前字符为界分割字符串
                    string m (mid.substr(0, i));
                    preMidCreate(p, m, left);                           //递归调用
                }
                if(i != ssize - 1){                                     //如果不在中序字符串尾，则有右孩子
                    BinaryTreeNode<char> *right;
                    right = new BinaryTreeNode<char>();
                    node->setRightChild(right);
                    string p (pre.substr(i + 1));
                    string m (mid.substr(i + 1));
                    preMidCreate(p, m, right);
                }
            }
        }
    }
}

void midAftCreate(string mid, string aft, BinaryTreeNode<char> *node){  //已知中序后序生成树
    int ssize = mid.size();
    node->setValue(aft[ssize - 1]);                                     //当前字符为后序字符串最后一个字符
    if(ssize == 1)
        return;
    else{
        for(int i = 0; i < ssize; i ++){
            if(mid[i] == aft[ssize - 1]){
                if(i != 0){
                    BinaryTreeNode<char> *left;
                    left = new BinaryTreeNode<char>();
                    node->setLeftChild(left);
                    string a (aft.substr(0, i));
                    string m (mid.substr(0, i));
                    midAftCreate(m, a, left);
                }
                if(i != ssize - 1){
                    BinaryTreeNode<char> *right;
                    right = new BinaryTreeNode<char>();
                    node->setRightChild(right);
                    string a (aft.substr(i, ssize-1));
                    string m (mid.substr(i + 1));
                    midAftCreate(m, a, right);
                }
            }
        }
    }
}

void createTree(string s1, string s2, string type){
    BinaryTree<char> tree;
    BinaryTreeNode<char> *node = new BinaryTreeNode<char>();
    tree.setRoot(node);
    if(type == "premid")
        preMidCreate(s1, s2, node);
    else if(type == "midaft")
        midAftCreate(s1, s2, node);
    tree.preTraversal(tree.getRoot());                   //前序周游二叉树
    cout<<endl;
    tree.midTraversal(tree.getRoot());                   //中序周游二叉树
    cout<<endl;
    tree.aftTraversal(tree.getRoot());                   //后序周游二叉树
    cout<<endl;
}
