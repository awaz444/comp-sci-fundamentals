# Arrays (incl. const Array Parameters)

A C-style array is a fixed-size, contiguous block of elements of the same
type.

## Declaration & initialization

```cpp
int nums[5];                        // uninitialized
int nums[5] = {1, 2, 3, 4, 5};      // initialized
int nums[] = {1, 2, 3};             // size inferred (3)
```

- Indexing is zero-based: `nums[0]` is the first element.
- Array size must be known at compile time (unless using dynamic
  allocation — see [Dynamic Memory Allocation](../13-dynamic-memory-allocation/notes.md)).
- No bounds checking — accessing `nums[5]` on a 5-element array is
  undefined behavior.

## Arrays decay to pointers

When passed to a function, an array "decays" to a pointer to its first
element — the function doesn't know its size:

```cpp
void printArray(int arr[], int size) {  // arr is really int*
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
}
```

You must pass the size separately (or use `std::array`/`std::vector`,
which know their own size).

## Const array parameters

If a function shouldn't modify the array's contents, mark the parameter
`const`:

```cpp
void printArray(const int arr[], int size) {
    // arr[0] = 99; // compile error — arr is read-only here
    for (int i = 0; i < size; i++) std::cout << arr[i] << ' ';
}
```

This documents intent and lets the compiler catch accidental writes.

## Key interview points

- `sizeof(arr) / sizeof(arr[0])` gives element count — but **only** within
  the scope where `arr` is still an array, not after it has decayed to a
  pointer (e.g. inside a function that received it as a parameter).
- Prefer `std::array<T, N>` (fixed-size) or `std::vector<T>` (dynamic)
  over raw C arrays in modern C++ — see
  [array Container](../../10-cpp-standard-library/03-array-container/notes.md).
- Multidimensional arrays (`int grid[3][4]`) are stored in row-major order
  — contiguous memory, row by row.
