#include "relatedFun.h"
#include "BinaryTree.h"
#include"stdio.h"

int main()
{
    vector<char> arr;
    char temp = '*';
    while(temp != '\n'){
        scanf("%c",&temp);
        arr.push_back(temp);
    }
    BinaryTree<char> b;
    int i = 0;
    char invalid = '#';
    b.creatTree(arr, arr.size(), i, invalid);
    cout<<"度为0的结点个数"<<endl;
    cout<<b.getDegree(0)<<endl;
    cout<<"度为1的结点个数"<<endl;
    cout<<b.getDegree(1)<<endl;
    cout<<"度为2的结点个数"<<endl;
    cout<<b.getDegree(2)<<endl;
    cout<<"树的高度为"<<endl;
    cout<<b.getHeight()<<endl;
    cout<<"树的宽度为"<<endl;
    cout<<b.getWidth()<<endl;
    cout<<"最大值结点"<<endl;
    cout<<b.getMax()->getValue()<<endl;
    cout<<"交换每个节点的左右孩子"<<endl;
    b.swapChild(b.getRoot());
    b.PreOrder(b.getRoot());
    cout<<endl;
//    cout<<"删除所有叶子节点"<<endl;
//    b.deleteLeaves(b.getRoot());
//    b.PreOrder(b.getRoot());
//    cout<<endl;
      if(b.isComplete())
        cout<<"是完全二叉树"<<endl;
      else
        cout<<"不是完全二叉树"<<endl;
    return 0;
}
