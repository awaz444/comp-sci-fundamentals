# Ternary Operator

The conditional operator `?:` is a compact, expression-form `if/else`.

## Syntax

```cpp
condition ? value_if_true : value_if_false
```

```cpp
int a = 5, b = 10;
int max = (a > b) ? a : b;
```

Equivalent to:

```cpp
int max;
if (a > b) max = a;
else max = b;
```

## Chaining

```cpp
std::string category = (score >= 90) ? "A"
                      : (score >= 80) ? "B"
                      : "C";
```

Readable for 2-3 cases; beyond that, prefer `if/else if` or `switch`.

## Ternary operator as an lvalue

The ternary expression can itself be assigned to, **if both branches are
lvalues of the same type** (e.g. references to variables):

```cpp
int a = 1, b = 2;
bool useA = true;
(useA ? a : b) = 100; // assigns 100 to 'a'
```

This works because `a` and `b` are both `int` lvalues, so `useA ? a : b`
is itself an `int&` — something you can assign to.

## Key interview points

- The ternary operator is an **expression** (produces a value), unlike
  `if`, which is a **statement**.
- Both branches' types must be compatible — the compiler determines a
  common type for the result.
- Using it as an lvalue is a niche but real C++ feature, often used to
  show depth of language knowledge.
