# Operator Overloading

C++ lets you define how operators (`+`, `==`, `<<`, `[]`, etc.) behave for
your own types, making custom classes feel like built-in types.

## Basic example: `operator+`

```cpp
class Vector2D {
public:
    double x, y;

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D{x + other.x, y + other.y};
    }
};

Vector2D a{1, 2}, b{3, 4};
Vector2D c = a + b; // calls a.operator+(b) -> {4, 6}
```

## Overloading comparison operators

```cpp
bool operator==(const Vector2D& other) const {
    return x == other.x && y == other.y;
}
bool operator!=(const Vector2D& other) const {
    return !(*this == other); // reuse == to avoid duplication
}
```

## Overloading `<<` for printing (must be a free function)

`std::cout << obj` calls `operator<<(ostream&, const T&)`. Since the left
operand is `std::ostream`, not your class, this **cannot** be a member
function — it must be a free function (often a `friend`, see
[Friend Functions](../12-friend-functions/notes.md)):

```cpp
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os; // return stream to allow chaining: cout << a << b
}
```

## Overloading `[]` (subscript operator)

```cpp
class MyArray {
public:
    int& operator[](int index) { return data[index]; }
    const int& operator[](int index) const { return data[index]; }
private:
    int data[10];
};
```

Providing both `const` and non-`const` versions allows read/write access
on mutable objects and read-only access on `const` objects.

## What can and can't be overloaded

- Most operators can be overloaded: `+ - * / == != < > [] () << >> = += ...`
- Cannot overload: `.`, `::`, `?:`, `sizeof`.
- Cannot change an operator's **precedence**, **associativity**, or
  **arity** (e.g. `+` always takes operands on both sides).

## Key interview points

- Operator overloading is just **syntactic sugar** for a function call —
  `a + b` becomes `a.operator+(b)` (or `operator+(a, b)` if free).
- For symmetry (e.g. `int + Vector2D` as well as `Vector2D + int`), define
  `operator+` as a **free function**, not a member — member functions only
  handle the case where the class is the left operand.
- Method chaining ([this-keyword](../09-this-keyword/notes.md)) and
  operator overloading both rely on returning references for fluent APIs.
