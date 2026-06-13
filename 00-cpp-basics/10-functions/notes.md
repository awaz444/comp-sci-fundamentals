# Functions

A function packages a block of code under a name so it can be reused and
called with different inputs.

## Basic syntax

```cpp
int add(int a, int b) {
    return a + b;
}

int result = add(2, 3); // 5
```

- **Return type**, **name**, **parameter list**, and **body**.
- A function declared `void` returns nothing.
- Functions must be **declared** (prototype) before use if defined later
  in the file — otherwise the compiler doesn't know they exist yet.

## Pass by value vs pass by reference

```cpp
void incrementByValue(int x) { x++; }      // copy — caller's value unchanged
void incrementByRef(int& x)  { x++; }      // reference — modifies caller's value
```

- **Pass by value** copies the argument — cheap for small types (`int`,
  `double`), wasteful for large objects.
- **Pass by reference** (`&`) lets the function operate on (and modify)
  the caller's variable directly — no copy.
- **Pass by const reference** (`const T&`) avoids the copy *and* prevents
  modification — the standard way to pass large objects you don't need to
  change.

## Default arguments

```cpp
void greet(std::string name, std::string greeting = "Hello") {
    std::cout << greeting << ", " << name << "!\n";
}

greet("Alice");           // "Hello, Alice!"
greet("Bob", "Hi");        // "Hi, Bob!"
```

- Default arguments must be the **rightmost** parameters (you can't have a
  default before a non-default parameter).
- Defaults are specified in the declaration, not necessarily the
  definition.

## Function overloading

Multiple functions with the **same name** but **different parameter
lists** (different types and/or number of parameters):

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
```

- The compiler picks the best match at **compile time** based on argument
  types (this is called "overload resolution").
- Return type alone is **not** enough to distinguish overloads.

## Returning multiple values

C++ functions return one value, but you can bundle multiple values:

```cpp
#include <tuple>
std::tuple<int, int> minMax(const std::vector<int>& v) {
    return {*std::min_element(v.begin(), v.end()),
            *std::max_element(v.begin(), v.end())};
}

auto [lo, hi] = minMax(data); // C++17 structured bindings
```

Alternatives: `std::pair` (for exactly two values), output parameters
(reference/pointer parameters), or a `struct`.

## Command line arguments

```cpp
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
}
```

- `argc` — argument count (always ≥ 1; `argv[0]` is the program name).
- `argv` — array of C-strings, the actual arguments.

## Key interview points

- Prefer `const T&` for large/non-trivial parameter types you don't need
  to modify.
- Overload resolution ambiguity (e.g. calling `add(1, 2.0)` when both
  `add(int,int)` and `add(double,double)` exist) is a common gotcha.
- `std::tuple` + structured bindings is the idiomatic modern C++ way to
  return multiple values.
