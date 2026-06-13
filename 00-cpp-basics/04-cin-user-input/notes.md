# User Input with `std::cin`

`std::cin` ("character input") is the standard input stream. The `>>`
operator is the **stream extraction operator** — it reads data out of the
stream into a variable.

## Basics

```cpp
int age;
std::cout << "Enter your age: ";
std::cin >> age;
```

- `>>` skips leading whitespace and reads until the next whitespace.
- Multiple reads can be chained: `std::cin >> a >> b;`

## Reading strings with spaces

`std::cin >> myString` stops at the first whitespace, so it can't read a
full line like "John Smith". Use `std::getline` instead:

```cpp
std::string fullName;
std::getline(std::cin, fullName);
```

## Mixing `>>` and `getline`

A common gotcha: `std::cin >> age` leaves the trailing `'\n'` in the input
buffer. A subsequent `std::getline` will then read an **empty line**
immediately. Fix by discarding leftover input:

```cpp
std::cin >> age;
std::cin.ignore();              // discard one character (the leftover '\n')
std::getline(std::cin, fullName);
```

## Clearing the input buffer after a failed read

If extraction fails (e.g. user types "abc" for an `int`), `cin` enters a
**fail state** and the bad input stays in the buffer, causing an infinite
loop if you retry naively. Recover with:

```cpp
std::cin.clear();                                        // reset error flags
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard rest of line
```

## Key interview points

- `cin.clear()` resets stream state flags (`failbit`, etc.) but does **not**
  remove bad data from the buffer — you still need `ignore()`.
- `std::cin.ignore(n, delim)` discards up to `n` characters or until
  `delim` is found, whichever comes first.
- Always check `if (std::cin.fail())` or `if (!(std::cin >> x))` when
  robustness matters.
