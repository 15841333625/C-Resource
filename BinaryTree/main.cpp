#include "relatedFun.h"
#include "BinaryTree.h"
#include"stdio.h"

int main()
{
    string pre;
    string mid;
    string aft;
    cout<<"�������������У�"<<endl;
    cin>>pre;
    cout<<"�������������У�"<<endl;
    cin>>mid;
    cout<<"������������У�"<<endl;
    cin>>aft;
    createTree(pre, mid, "premid");
    createTree(mid, aft, "midaft");
    return 0;
}
