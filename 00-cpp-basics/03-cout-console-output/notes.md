# Console Output with `std::cout`

`std::cout` ("character output") is the standard output stream, declared in
`<iostream>`. The `<<` operator is the **stream insertion operator** — it
sends data into the stream.

## Basics

```cpp
std::cout << "Hello";          // string literal
std::cout << 42;               // int
std::cout << 3.14;             // double
std::cout << '\n';             // newline character
std::cout << std::endl;        // newline + flush
```

## Chaining

`<<` returns a reference to the stream, so calls can be chained:

```cpp
std::cout << "x = " << x << ", y = " << y << '\n';
```

## `\n` vs `std::endl`

- `'\n'` just inserts a newline character.
- `std::endl` inserts a newline **and flushes** the output buffer.
- `'\n'` is generally preferred in tight loops/performance-sensitive code
  because flushing has overhead.

## Key interview points

- `std::cout` is buffered; output may not appear immediately unless flushed
  (via `std::endl`, `std::flush`, or program exit).
- Formatting (width, precision, base) is controlled with stream
  manipulators — see [Stream Manipulators](../16-stream-manipulators/notes.md).
- `std::cerr` is the standard error stream (unbuffered, for error messages).
