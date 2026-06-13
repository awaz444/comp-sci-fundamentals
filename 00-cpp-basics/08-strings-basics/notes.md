# Strings Basics

`std::string` (from `<string>`) is the standard mutable, dynamically-sized
string type in C++ — prefer it over C-style `char*` arrays.

## Declaration & basic operations

```cpp
std::string name = "Alice";
std::cout << name.length() << '\n';   // 5 (also: name.size())
std::cout << name[0] << '\n';          // 'A' — indexable like an array
```

## Concatenation

```cpp
std::string first = "Hello";
std::string second = "World";
std::string result = first + ", " + second + "!"; // "Hello, World!"
result += " Goodbye.";                              // append in place
```

## Comparison

`==`, `!=`, `<`, `>` compare strings lexicographically.

## Converting between strings and numbers

```cpp
// string -> int
int n = std::stoi("42");
double d = std::stod("3.14");

// number -> string
std::string s = std::to_string(123);
```

## Useful member functions

```cpp
str.substr(pos, len);   // extract substring
str.find("lo");         // returns index of first match, or std::string::npos
str.erase(pos, len);    // remove len chars starting at pos
```

## Reversing a string

```cpp
#include <algorithm>
std::reverse(str.begin(), str.end()); // reverses in place
```

## Key interview points

- `std::string::npos` is a special value (max possible `size_t`) returned
  by `find()` when no match is found — always check against it, not `-1`.
- `substr`/`erase`/`find` take `(position, length)` — easy to mix up order
  with other languages.
- `std::string` manages its own memory (RAII) — no manual `new`/`delete`
  needed, unlike C-style strings.
