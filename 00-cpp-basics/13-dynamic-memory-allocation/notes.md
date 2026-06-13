# Dynamic Memory Allocation: `new` & `delete`

`new` and `delete` allocate/free memory on the **heap** at runtime —
needed when the size isn't known until the program runs, or when data must
outlive the function that created it.

## Single objects

```cpp
int* p = new int(42);   // allocate one int on the heap, initialized to 42
std::cout << *p << '\n';
delete p;                // free it — required, or it leaks
```

## Arrays

```cpp
int n = 10;
int* arr = new int[n];  // heap array of n ints
// ... use arr[0] .. arr[n-1] ...
delete[] arr;            // note the [] — must match new[]
```

## Stack vs heap

| | Stack | Heap |
|---|---|---|
| Allocation | automatic (scope-based) | manual (`new`/`delete`) |
| Lifetime | ends when scope exits | until explicitly `delete`d |
| Speed | fast | slower (allocator overhead) |
| Size | fixed/limited | large, limited by available memory |

## Common pitfalls

- **Memory leak**: forgetting `delete`/`delete[]` — memory is never freed.
- **Dangling pointer**: using a pointer after `delete` — undefined
  behavior.
- **Double free**: calling `delete` twice on the same pointer.
- **Mismatched new/delete**: using `delete` on memory from `new[]` (or
  vice versa) — undefined behavior.

## Modern alternative: smart pointers

Modern C++ favors `std::unique_ptr`/`std::shared_ptr` (from `<memory>`),
which automatically call `delete` via RAII when they go out of scope —
eliminating most manual memory management bugs. Covered in more depth in
[Object-Oriented Programming](../../01-object-oriented-programming/README.md).

## Key interview points

- Every `new` needs exactly one matching `delete`; every `new[]` needs
  exactly one `delete[]`.
- `delete` on a `nullptr` is safe (no-op) — you don't need to check for
  null before deleting.
- Heap allocation is significantly slower than stack allocation due to
  bookkeeping — avoid unnecessary `new` in hot loops.
