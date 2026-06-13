#include <iostream>

class Buffer {
public:
    Buffer(int size) : size(size), data(new int[size]) {
        for (int i = 0; i < size; i++) data[i] = 0;
    }

    // Deep-copy constructor: allocates NEW memory and copies contents
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::cout << "Deep copy constructor called\n";
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~Buffer() {
        delete[] data;
    }

    void set(int index, int value) { data[index] = value; }
    int get(int index) const { return data[index]; }

    int size;
    int* data;
};

void printFirst(Buffer b) { // pass by value -> triggers copy constructor
    std::cout << "First element (copy): " << b.get(0) << '\n';
}

int main() {
    Buffer a(5);
    a.set(0, 42);

    // Copy construction
    Buffer b = a; // deep copy — separate memory from a

    // Prove the copy is independent
    b.set(0, 99);
    std::cout << "a[0] = " << a.get(0) << ", b[0] = " << b.get(0) << '\n';

    // Pass-by-value also triggers the copy constructor
    printFirst(a);

    return 0;
}
