# Environment Setup

To compile and run C++ you need a **compiler/toolchain** and, optionally, an
**IDE**. The language itself doesn't care which OS or editor you use.

## Options

- **Windows**: Visual Studio (MSVC compiler) is the most common choice.
  Install the "Desktop development with C++" workload, create a new
  "Console App" project, and build/run with `Ctrl+F5`.
- **macOS**: Xcode Command Line Tools provide `clang++`. Any text editor +
  terminal works.
- **Linux**: `g++` or `clang++` via your package manager.
- **Cross-platform**: VS Code with the C/C++ extension + a compiler
  (g++/clang) is a lightweight alternative to a full IDE.

## Compiling from the command line

```bash
g++ -std=c++17 -Wall -o main main.cpp
./main
```

- `-std=c++17` selects the language standard.
- `-Wall` enables helpful warnings — always compile with warnings on.
- `-o main` names the output executable.

## Key interview points

- A C++ program goes through **preprocessing → compilation → assembly →
  linking** to produce an executable.
- The **compiler** translates source code to machine code; the **linker**
  combines object files and libraries into the final binary.
- Source files: `.cpp` (implementation), `.h`/`.hpp` (declarations/headers).
