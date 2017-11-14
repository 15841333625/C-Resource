#include "relatedFun.h"
#include "BinaryTree.h"
#include"stdio.h"

int main()
{
    string pre;
    string mid;
    string aft;
    cout<<"请输入先序序列："<<endl;
    cin>>pre;
    cout<<"请输入中序序列："<<endl;
    cin>>mid;
    cout<<"请输入后序序列："<<endl;
    cin>>aft;
    createTree(pre, mid, "premid");
    createTree(mid, aft, "midaft");
    return 0;
}
