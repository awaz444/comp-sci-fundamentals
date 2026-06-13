# Conversion Operators

A **conversion operator** lets an object of your class be implicitly (or
explicitly) converted to another type — most commonly a primitive type.

## Syntax

```cpp
class Fraction {
public:
    Fraction(int num, int den) : numerator(num), denominator(den) {}

    // Conversion operator: allows Fraction -> double
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

private:
    int numerator, denominator;
};

Fraction half(1, 2);
double d = half;              // implicit conversion via operator double()
std::cout << half + 0.5;       // half is converted to double, then added
```

- No return type is written (it's implied by the operator name, e.g.
  `operator double`, `operator int`, `operator bool`).
- Takes no parameters.

## `explicit` conversion operators (C++11)

Implicit conversions can cause surprising behavior (e.g. an object
silently becoming a `bool` in an `if` and matching unintended overloads).
Mark the operator `explicit` to require a cast:

```cpp
explicit operator double() const { return ...; }

double d = static_cast<double>(half); // OK — explicit cast required
double d2 = half;                      // compile error — no implicit conversion
```

## `operator bool`

A common pattern for "does this object represent something valid?" — e.g.
smart pointers and optional-like types:

```cpp
class Optional {
public:
    explicit operator bool() const { return hasValue; }
private:
    bool hasValue;
};

Optional opt = ...;
if (opt) { /* ... */ } // explicit operator bool still allowed in boolean contexts
```

`explicit operator bool()` is special-cased by the language: it's still
usable in conditions (`if`, `while`, `!`, `&&`, `||`) even though it's
explicit — this avoids accidental conversions to `int` while still
supporting the common "truthiness" idiom.

## Key interview points

- Conversion operators are the mechanism behind "a class that acts like a
  primitive" (e.g. smart pointers behaving like raw pointers in `if`
  checks).
- Implicit conversion operators can lead to surprising, hard-to-debug
  overload resolution — prefer `explicit` unless the conversion is truly
  "lossless and obvious" (like a wrapper type converting to its underlying
  type).
- This is the inverse of a **converting constructor** (a constructor
  taking one argument, which allows implicit conversion *into* the class
  type) — both directions can be marked `explicit`.
