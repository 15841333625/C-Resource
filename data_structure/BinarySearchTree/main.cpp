#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> bin;
    bin.insert(50);
    bin.insert(60);
    bin.insert(20);
    bin.insert(10);
    bin.insert(25);
    bin.insert(23);
    bin.insert(15);
    bin.insert(16);
    bin.print(bin.getRoot());
    cout<<endl;
    bin.del(50);
    bin.print(bin.getRoot());
    cout<<endl;
    bin.del(20);
    bin.print(bin.getRoot());
    cout<<endl;
    return 0;
}
