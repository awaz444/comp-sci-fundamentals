# Hello World

The smallest complete C++ program, and a tour of what every line does.

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

## Breakdown

- `#include <iostream>` — a **preprocessor directive** that pulls in the
  standard input/output stream library, giving us access to `std::cout`
  and `std::cin`.
- `int main()` — every C++ program must have exactly one `main` function.
  This is the **entry point** — execution starts here.
- `std::cout << "..."` — writes to standard output. `std` is the standard
  library **namespace**; `::` is the scope resolution operator.
- `std::endl` — outputs a newline and flushes the output buffer.
- `return 0;` — returns an exit status to the operating system. `0`
  conventionally means "success"; non-zero indicates an error.

## Key interview points

- `main` can return `int`. If you omit `return 0;`, the compiler implicitly
  returns 0 for you (but it's good practice to write it explicitly).
- `using namespace std;` lets you drop the `std::` prefix, but it's
  considered poor practice in headers/large projects because it pollutes
  the global namespace (see [Namespaces](../17-namespaces/notes.md)).
