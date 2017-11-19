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
    cout<<"��Ϊ0�Ľ�����"<<endl;
    cout<<b.getDegree(0)<<endl;
    cout<<"��Ϊ1�Ľ�����"<<endl;
    cout<<b.getDegree(1)<<endl;
    cout<<"��Ϊ2�Ľ�����"<<endl;
    cout<<b.getDegree(2)<<endl;
    cout<<"���ĸ߶�Ϊ"<<endl;
    cout<<b.getHeight()<<endl;
    cout<<"���Ŀ��Ϊ"<<endl;
    cout<<b.getWidth()<<endl;
    cout<<"���ֵ���"<<endl;
    cout<<b.getMax()->getValue()<<endl;
    cout<<"����ÿ���ڵ�����Һ���"<<endl;
    b.swapChild(b.getRoot());
    b.PreOrder(b.getRoot());
    cout<<endl;
//    cout<<"ɾ������Ҷ�ӽڵ�"<<endl;
//    b.deleteLeaves(b.getRoot());
//    b.PreOrder(b.getRoot());
//    cout<<endl;
      if(b.isComplete())
        cout<<"����ȫ������"<<endl;
      else
        cout<<"������ȫ������"<<endl;
    return 0;
}
