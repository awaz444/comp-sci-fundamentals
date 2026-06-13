# Object Assignment

Assigning one object to another (`b = a;`) copies each member variable
from `a` into `b` — this is handled by the **copy assignment operator**.

## The compiler-generated assignment operator

If you don't define one, the compiler generates a default
`operator=` that performs a **member-wise copy** (shallow copy):

```cpp
class Point {
public:
    int x, y;
};

Point a{1, 2};
Point b;
b = a; // b.x = 1, b.y = 2 — member-wise copy
```

This is fine for simple types with no owned resources (raw pointers,
manually-managed memory).

## The problem: shallow copy of owned resources

```cpp
class Buffer {
public:
    Buffer(int size) : size(size), data(new int[size]) {}
    ~Buffer() { delete[] data; }

    int size;
    int* data;
};

Buffer a(10);
Buffer b(5);
b = a; // default operator=: b.data now points to the SAME memory as a.data!
```

Now both `a` and `b` think they own `data`. When both destructors run,
`delete[] data` is called **twice on the same pointer** — undefined
behavior (double free).

## Defining a custom assignment operator (deep copy)

```cpp
Buffer& operator=(const Buffer& other) {
    if (this == &other) return *this; // self-assignment check

    delete[] data;                 // free existing resource
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];

    return *this; // enables chaining: a = b = c;
}
```

## Assignment vs construction

```cpp
Buffer a(10);
Buffer b = a;   // COPY CONSTRUCTION (b doesn't exist yet)
Buffer c(5);
c = a;          // ASSIGNMENT (c already exists, gets overwritten)
```

These call **different** functions: the copy constructor vs the copy
assignment operator. Both need to handle deep copies for resource-owning
classes.

## Key interview points

- The compiler auto-generates `operator=`, copy constructor, and
  destructor if you don't provide them — but only the **shallow** versions.
- The **"Rule of Three"** (also "Rule of Five" in C++11+): if a class
  defines a destructor, copy constructor, or copy assignment operator that
  does something non-trivial, it likely needs to define **all three**
  (plus move constructor/assignment for Five).
- Always check `this == &other` in `operator=` to handle self-assignment
  safely (`a = a;`).
