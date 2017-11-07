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
    cout<<"广度遍历"<<endl;
    b.breadthFirstOrder();
    cout<<"深度前序递归遍历"<<endl;
    b.PreOrder(b.getRoot());
    cout<<endl;
    cout<<"深度中序递归遍历"<<endl;
    b.MidOrder(b.getRoot());
    cout<<endl;
    cout<<"深度后序递归遍历"<<endl;
    b.AftOrder(b.getRoot());
    cout<<endl;
    return 0;
}
