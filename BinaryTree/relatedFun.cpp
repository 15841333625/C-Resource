#include "relatedFun.h"

void preMidCreate(string pre, string mid, BinaryTreeNode<char> *node){  //��֪ǰ������������
    int ssize = pre.size();
    node->setValue(pre[0]);                                             //�趨��ǰ���ֵΪǰ���ַ�����һ���ַ�
    if(ssize == 1)                                                      //�ַ�������Ϊ1ʱֹͣ�ݹ�
        return;
    else{
        for(int i = 0; i < ssize; i ++){
            if(mid[i] == pre[0]){                                       //�����ַ�����ǰ���һ���ַ�ʱ
                if(i != 0){                                             //������������ַ����ף���������
                    BinaryTreeNode<char> *left;
                    left = new BinaryTreeNode<char>();                  //�����½��
                    node->setLeftChild(left);
                    string p (pre.substr(1, i));                        //�Ե�ǰ�ַ�Ϊ��ָ��ַ���
                    string m (mid.substr(0, i));
                    preMidCreate(p, m, left);                           //�ݹ����
                }
                if(i != ssize - 1){                                     //������������ַ���β�������Һ���
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

void midAftCreate(string mid, string aft, BinaryTreeNode<char> *node){  //��֪�������������
    int ssize = mid.size();
    node->setValue(aft[ssize - 1]);                                     //��ǰ�ַ�Ϊ�����ַ������һ���ַ�
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
    tree.preTraversal(tree.getRoot());                   //ǰ�����ζ�����
    cout<<endl;
    tree.midTraversal(tree.getRoot());                   //�������ζ�����
    cout<<endl;
    tree.aftTraversal(tree.getRoot());                   //�������ζ�����
    cout<<endl;
}
