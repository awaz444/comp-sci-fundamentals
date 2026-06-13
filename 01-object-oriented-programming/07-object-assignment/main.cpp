#include <iostream>

class Buffer {
public:
    Buffer(int size) : size(size), data(new int[size]) {
        for (int i = 0; i < size; i++) data[i] = 0;
        std::cout << "Constructed Buffer of size " << size << '\n';
    }

    ~Buffer() {
        std::cout << "Destroying Buffer of size " << size << '\n';
        delete[] data;
    }

    // Custom copy assignment operator: performs a deep copy
    Buffer& operator=(const Buffer& other) {
        std::cout << "operator= called\n";
        if (this == &other) return *this; // self-assignment guard

        delete[] data; // free existing resource before replacing it

        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this; // allows chaining: a = b = c;
    }

    void set(int index, int value) { data[index] = value; }
    int get(int index) const { return data[index]; }

    int size;
    int* data;
};

int main() {
    Buffer a(5);
    a.set(0, 42);

    Buffer b(3);
    b = a; // calls our custom operator=, deep copy

    // Modifying a doesn't affect b — they have separate memory
    a.set(0, 100);
    std::cout << "a[0] = " << a.get(0) << ", b[0] = " << b.get(0) << '\n';

    // Self-assignment is safe due to the guard
    a = a;

    return 0;
}
