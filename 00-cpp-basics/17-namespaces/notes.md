# Namespaces

A namespace groups related names (functions, classes, variables) under a
common prefix to avoid naming collisions.

## Declaring and using a namespace

```cpp
namespace math_utils {
    int square(int x) { return x * x; }
    const double PI = 3.14159;
}

int main() {
    int s = math_utils::square(5); // fully qualified name
}
```

## `using` declarations and directives

```cpp
using math_utils::square;     // bring one name into scope
using namespace math_utils;    // bring ALL names into scope
```

- `using namespace std;` is common in tutorials but discouraged in real
  code (especially in headers) — it can cause name collisions as projects
  grow.
- Prefer qualifying names (`std::cout`) or using targeted `using`
  declarations for just the names you need.

## The global/anonymous namespace

- Code not inside any `namespace` block lives in the **global
  namespace**.
- An **anonymous namespace** (`namespace { ... }`) gives names internal
  linkage — they're only visible within that file. Useful for helper
  functions you don't want to expose.

## Nested namespaces

```cpp
namespace company::project::utils { // C++17 nested namespace syntax
    void helper();
}
```

## Key interview points

- Namespaces solve the same problem as Java packages or Python modules:
  avoiding name collisions in large codebases.
- `std` is the namespace for the entire C++ standard library.
- Two different libraries can each define a `utils::log()` — without
  namespaces, this would be a compile error (redefinition).
