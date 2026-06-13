# File I/O: `ofstream` and `ifstream`

`<fstream>` provides stream classes for reading and writing files, used the
same way as `cin`/`cout`.

## Writing with `ofstream`

```cpp
#include <fstream>

std::ofstream outFile("data.txt");
if (outFile.is_open()) {
    outFile << "Hello, file!\n";
    outFile << 42 << '\n';
    outFile.close();
}
```

- By default, `ofstream` **truncates** (overwrites) the file if it exists.
- Open with `std::ios::app` to append instead:
  `std::ofstream outFile("data.txt", std::ios::app);`

## Reading with `ifstream`

```cpp
std::ifstream inFile("data.txt");
std::string line;
while (std::getline(inFile, line)) {
    std::cout << line << '\n';
}
inFile.close();
```

- `std::getline(inFile, line)` returns the stream, which is `false`
  (falsy) at end-of-file — perfect as a loop condition.
- You can also use `inFile >> word` to read whitespace-separated tokens.

## Writing to a specific line (shifting remaining lines down)

There's no direct "insert into the middle of a file" operation — files are
sequential. The standard approach:

1. Read the entire file into memory (e.g. `std::vector<std::string>`,
   one entry per line).
2. Insert the new line at the desired index in the vector.
3. Re-write the whole file from the vector (truncate + write all lines).

```cpp
std::vector<std::string> lines;
std::string line;
std::ifstream in("data.txt");
while (std::getline(in, line)) lines.push_back(line);
in.close();

lines.insert(lines.begin() + targetIndex, "New line");

std::ofstream out("data.txt"); // truncates
for (const auto& l : lines) out << l << '\n';
```

## Key interview points

- Always check `is_open()` (or use the stream in a boolean context) before
  reading/writing.
- RAII: `ofstream`/`ifstream` destructors automatically close the file, but
  explicit `close()` is good practice when you need to reuse the handle.
- Modifying file contents in place generally requires read-all → modify →
  write-all, since file systems don't support "shifting" bytes cheaply.
