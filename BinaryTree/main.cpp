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
    cout<<"��ȱ���"<<endl;
    b.breadthFirstOrder();
    cout<<"���ǰ��ݹ����"<<endl;
    b.PreOrder(b.getRoot());
    cout<<endl;
    cout<<"�������ݹ����"<<endl;
    b.MidOrder(b.getRoot());
    cout<<endl;
    cout<<"��Ⱥ���ݹ����"<<endl;
    b.AftOrder(b.getRoot());
    cout<<endl;
    return 0;
}
