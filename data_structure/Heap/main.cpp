#include"Heap.h"

int main()
{
    int arr[10] = {20, 12, 35, 15, 10, 80, 30, 17, 2, 1};
    MaxHeap<int> heap(arr, 10);
    heap.print();
    heap.insert(100);
    heap.print();
    heap.del(80);
    heap.print();
    return 0;
}
