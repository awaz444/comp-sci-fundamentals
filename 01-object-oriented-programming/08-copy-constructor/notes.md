# Copy Constructor & Deep Copy

A **copy constructor** creates a new object as a copy of an existing one.
It's called when:

- An object is initialized from another: `Buffer b = a;` or `Buffer b(a);`
- An object is passed **by value** to a function.
- An object is returned **by value** from a function (in some cases —
  often elided by the compiler).

## The compiler-generated copy constructor

```cpp
class Point {
public:
    int x, y;
};

Point a{1, 2};
Point b = a; // compiler-generated copy constructor: b.x=1, b.y=2 (shallow copy)
```

Fine for simple value types.

## The shallow copy problem

```cpp
class Buffer {
public:
    Buffer(int size) : size(size), data(new int[size]) {}
    ~Buffer() { delete[] data; }

    int size;
    int* data;
};

Buffer a(10);
Buffer b = a; // default copy ctor: b.data == a.data (same pointer!)
```

Both objects now point to the same heap memory. When `a` and `b` are both
destroyed, `delete[]` runs twice on the same pointer — double free /
undefined behavior. Modifying `b.data[i]` also affects `a`.

## Defining a deep-copy constructor

```cpp
Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i]; // copy each element into NEW memory
    }
}
```

Now `a` and `b` own **independent** memory — modifying one doesn't affect
the other, and each destructor frees its own buffer safely.

## Signature

A copy constructor always takes a `const ClassName&` (a reference avoids
infinite recursion — passing by value would itself require a copy!).

## Key interview points

- "Shallow copy" = copies pointer values (both point to same memory).
  "Deep copy" = allocates new memory and copies the *pointed-to* data.
- Any class that manages a raw resource (heap memory, file handle, socket)
  needs a custom copy constructor (and assignment operator, and
  destructor) — see [Object Assignment](../07-object-assignment/notes.md)
  and the Rule of Three.
- Classes that only contain value types (`int`, `double`, `std::string`,
  `std::vector`, smart pointers) usually don't need a custom copy
  constructor — the members' own copy constructors handle deep-copying
  correctly already.
