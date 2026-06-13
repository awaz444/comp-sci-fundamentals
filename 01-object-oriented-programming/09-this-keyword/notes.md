# `this` Keyword & Method Chaining

## What is `this`?

Inside a non-static member function, `this` is a pointer to the object the
function was called on. Its type is `ClassName*` (or `const ClassName*` in
a `const` member function).

```cpp
class Counter {
public:
    void increment() {
        this->count++; // explicit — same as just "count++"
    }
private:
    int count = 0;
};
```

Member access (`count`) is implicitly `this->count` — you usually don't
need to write `this->` explicitly.

## When `this` is necessary

1. **Disambiguating a parameter from a member with the same name:**

```cpp
class Point {
public:
    void setX(int x) {
        this->x = x; // this->x is the member, x is the parameter
    }
private:
    int x;
};
```

2. **Returning the current object** (e.g. for method chaining).

3. **Comparing object identity:** `if (this == &other)` — used in
   `operator=` to guard against self-assignment.

## Method chaining

Returning `*this` (a reference to the current object) from a method lets
you chain multiple calls together:

```cpp
class TextBuilder {
public:
    TextBuilder& append(const std::string& s) {
        text += s;
        return *this; // return reference to current object
    }
    std::string text;
};

TextBuilder tb;
tb.append("Hello").append(", ").append("World!"); // chained calls
```

Each call to `append` returns a reference to `tb`, so `.append(...)` can
be called again on the result — this is how `std::cout << a << b << c`
and the builder pattern work.

## Key interview points

- `*this` dereferences the pointer to produce a reference/value of type
  `ClassName`; `this` itself is a pointer (`ClassName*`).
- `this` is **not** available in `static` member functions — there's no
  object to point to.
- Method chaining requires returning `ClassName&` (reference), not
  `ClassName` (which would return a copy and break the chain's connection
  to the original object).
