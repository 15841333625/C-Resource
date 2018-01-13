#include"AVL.h"

int main()
{
    AVL<int> avl;
    avl.insert(14);
    avl.insert(9);
    avl.insert(28);
    avl.insert(5);
    avl.insert(12);
    avl.insert(18);
    avl.insert(50);
    avl.insert(3);
    avl.insert(7);
    avl.insert(17);
    avl.insert(30);
    avl.insert(60);
    avl.insert(53);
    avl.insert(63);
    avl.insert(2);
    avl.print(avl.getRoot());
    cout<<endl;
    avl.print2(avl.getRoot());
    cout<<endl;
    avl.deleteX(17);
    avl.print(avl.getRoot());
    cout<<endl;
    avl.print2(avl.getRoot());
    cout<<endl;
    avl.insert(64);
    avl.print(avl.getRoot());
    cout<<endl;
    avl.print2(avl.getRoot());
    cout<<endl;
    avl.deleteX(2);
    avl.print(avl.getRoot());
    cout<<endl;
    avl.print2(avl.getRoot());
    cout<<endl;
    avl.deleteX(3);
    avl.print(avl.getRoot());
    cout<<endl;
    avl.print2(avl.getRoot());
    cout<<endl;
    return 0;
}
