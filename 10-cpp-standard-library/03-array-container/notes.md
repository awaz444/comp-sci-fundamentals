# `std::array`

`std::array<T, N>` (from `<array>`) is a fixed-size array that wraps a
C-style array with a modern container interface — combines the
performance of a raw array with the safety/convenience of the STL.

## Declaration

```cpp
#include <array>

std::array<int, 5> arr = {1, 2, 3, 4, 5};
```

- Size `N` is part of the **type** and fixed at compile time — like
  `int[5]`, but `std::array<int, 5>` and `std::array<int, 10>` are
  different types.

## Why prefer `std::array` over a C-style array

| Feature | C array | `std::array` |
|---|---|---|
| Knows its own size | no (decays to pointer) | yes: `.size()` |
| Bounds-checked access | no | `.at(i)` throws on out-of-range |
| Works with STL algorithms | yes (via pointers) | yes (has `.begin()`/`.end()`) |
| Copyable/assignable | no (must loop manually) | yes (`=` works) |
| Can be returned from a function | no (decays) | yes |

## Common operations

```cpp
arr.size();          // 5
arr.at(2);           // bounds-checked access (throws std::out_of_range)
arr[2];              // unchecked access (like a raw array)
arr.front();         // first element
arr.back();          // last element
arr.fill(0);         // set all elements to 0

for (int x : arr) { ... }                          // range-based for
std::sort(arr.begin(), arr.end());                  // works with <algorithm>
```

## Key interview points

- `std::array` has **zero overhead** compared to a C array — same memory
  layout, no heap allocation, no extra bookkeeping at runtime.
- Unlike `std::vector`, `std::array` **cannot be resized** — size is fixed
  at compile time as a template parameter.
- Use `std::array` when the size is known and fixed at compile time; use
  `std::vector` when the size varies at runtime.
