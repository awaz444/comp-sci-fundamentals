# Exception Handling

Exceptions provide a way to signal and handle errors that occur during
program execution, separating error-handling code from normal logic flow.

## try / throw / catch

```cpp
try {
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    result = numerator / denominator;
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << '\n';
}
```

- `throw` raises an exception, immediately unwinding the stack until a
  matching `catch` is found.
- `catch` blocks are checked in order — the first matching type handles
  the exception.
- If no `catch` matches, the program terminates via `std::terminate`.

## Standard exception types

`<stdexcept>` provides a hierarchy rooted at `std::exception`:

- `std::runtime_error` — errors detectable only at runtime
- `std::logic_error` — errors from violated preconditions
  (`std::invalid_argument`, `std::out_of_range`, ...)
- All have a `.what()` method returning a `const char*` description.

## Catching by reference vs value

```cpp
catch (const std::exception& e) // preferred: avoids copying, supports polymorphism
```

Catching by value copies the exception object and loses derived-type
information when caught as a base type.

## Catch-all

```cpp
catch (...) {
    std::cerr << "Unknown exception caught\n";
}
```

## Custom exceptions

```cpp
class InvalidAgeException : public std::runtime_error {
public:
    InvalidAgeException(const std::string& msg) : std::runtime_error(msg) {}
};
```

## `finally`-equivalent: RAII

C++ has no `finally` block. Instead, cleanup code goes in **destructors**
— objects are destroyed during stack unwinding regardless of whether an
exception was thrown (RAII).

## Key interview points

- Exceptions should be used for **exceptional, unrecoverable-in-place**
  situations, not routine control flow (which has performance overhead
  when thrown).
- Always catch by `const reference` to avoid copies and preserve
  polymorphic behavior.
- An exception thrown from a destructor during stack unwinding (while
  handling another exception) causes `std::terminate` — destructors should
  not throw.
