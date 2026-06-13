# Stream Manipulators: `setw`, `setprecision`, `setbase`

Stream manipulators (from `<iomanip>`) control how `std::cout` formats
output.

## `setw` — field width

Sets the minimum width of the **next** output item only (must be repeated
for each item):

```cpp
#include <iomanip>
std::cout << std::setw(10) << "Name" << std::setw(5) << "Age" << '\n';
std::cout << std::setw(10) << "Alice" << std::setw(5) << 30 << '\n';
```

- Default fill character is a space; change it with `std::setfill('-')`.
- Combine with `std::left` / `std::right` to control alignment (default is
  right-aligned).

## `setprecision` — decimal precision

Controls how many digits are shown for floating-point numbers:

```cpp
double pi = 3.14159265;
std::cout << std::setprecision(3) << pi << '\n';        // 3.14
std::cout << std::fixed << std::setprecision(2) << pi << '\n'; // 3.14
```

- Without `std::fixed`, `setprecision(n)` sets the **total number of
  significant digits**.
- With `std::fixed`, it sets the number of digits **after the decimal
  point**.

## `setbase` — number base

Outputs integers in a different base:

```cpp
int n = 255;
std::cout << std::setbase(16) << n << '\n'; // ff (hex)
std::cout << std::setbase(8)  << n << '\n'; // 377 (octal)
std::cout << std::setbase(10) << n << '\n'; // 255 (back to decimal)
```

Equivalent manipulators: `std::hex`, `std::oct`, `std::dec`. Add
`std::showbase` to print the `0x`/`0` prefix.

## Key interview points

- Most manipulators (except `setw`) are **sticky** — they affect all
  subsequent output until changed again. `setw` applies to only the next
  item.
- `setprecision`'s behavior changes depending on whether `std::fixed` or
  `std::scientific` is also set — a common source of confusion.
- These manipulators only affect formatting; they don't change the
  underlying value being printed.
