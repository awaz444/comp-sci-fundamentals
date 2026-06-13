# Reference Variables

A reference is an **alias** for an existing variable — another name for
the same memory location.

## Declaration

```cpp
int x = 10;
int& ref = x; // ref is now another name for x

ref = 20;
std::cout << x << '\n'; // 20 — modifying ref modifies x
```

## Rules

- A reference **must** be initialized when declared — there's no such
  thing as a "null" or uninitialized reference.
- Once bound, a reference **cannot be rebound** to refer to a different
  variable — `ref = y;` assigns `y`'s value to `x` (via `ref`), it does
  **not** make `ref` an alias for `y`.
- References are most commonly used as **function parameters** (pass by
  reference) and **return types**.

## References vs pointers

| | Reference | Pointer |
|---|---|---|
| Syntax | `int& r = x;` | `int* p = &x;` |
| Must be initialized | yes | no (can be `nullptr`) |
| Can be reseated | no | yes (`p = &otherVar;`) |
| Dereference syntax | use directly: `r` | needs `*p` |
| Can be null | no | yes |

## const references

```cpp
void printName(const std::string& name) { // no copy, can't modify
    std::cout << name << '\n';
}
```

`const T&` is the standard way to pass large objects efficiently without
allowing the function to modify the caller's data.

## Key interview points

- References provide pointer-like aliasing with value-like syntax — no
  `*`/`&` needed at the use site.
- A function returning a reference to a local variable is a bug — the
  local is destroyed when the function returns, leaving a **dangling
  reference**.
- "Reference" and "alias" are the same concept — under the hood, most
  compilers implement references using pointers, but the language
  guarantees they're never null and never reseated.
