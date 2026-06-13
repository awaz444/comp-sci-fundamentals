#include <iostream>

int main() {
    // Allocating a single int on the heap
    int* p = new int(42);
    std::cout << "*p = " << *p << '\n';
    delete p; // must free single-object allocations with delete

    // Allocating an array on the heap
    int n = 5;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    delete[] arr; // must free array allocations with delete[]

    // Stack vs heap lifetime illustration
    {
        int stackVar = 10;   // destroyed automatically at end of this scope
        int* heapVar = new int(20); // survives until delete is called
        std::cout << "stackVar = " << stackVar << ", *heapVar = " << *heapVar << '\n';
        delete heapVar;
    }
    // stackVar no longer exists here; heapVar's memory has been freed

    return 0;
}
