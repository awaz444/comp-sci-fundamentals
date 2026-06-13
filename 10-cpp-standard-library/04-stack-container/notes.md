# `std::stack`

`std::stack<T>` (from `<stack>`) is a **LIFO** (Last In, First Out)
container adapter — it wraps another container (default
`std::deque<T>`) and restricts access to only the "top".

## Operations

```cpp
#include <stack>

std::stack<int> s;
s.push(1);     // add to top
s.push(2);
s.push(3);

s.top();       // 3 — view the top element (doesn't remove)
s.pop();       // removes the top element (3) — returns void!
s.size();      // 2
s.empty();     // false
```

| Operation | Complexity |
|---|---|
| `push` | O(1) |
| `pop` | O(1) |
| `top` | O(1) |
| `empty`/`size` | O(1) |

## Important: `pop()` returns nothing

Unlike some languages, `pop()` does **not** return the removed value —
you must `top()` then `pop()` separately:

```cpp
int value = s.top();
s.pop();
```

## Underlying container

By default backed by `std::deque`, but can be changed:

```cpp
std::stack<int, std::vector<int>> s; // backed by a vector instead
```

## Typical use cases

- Expression evaluation (infix/postfix/prefix) — see
  [Data Structures: Stacks](../../02-data-structures/02-stacks/notes.md)
  for from-scratch implementations and applications.
- Undo/redo functionality.
- DFS (depth-first search) using an explicit stack instead of recursion.
- Balanced parentheses / matching brackets checking.

## Key interview points

- `std::stack` is a **container adapter** — it doesn't implement its own
  storage, just restricts the interface of an underlying container
  (`deque` by default, also works with `vector` or `list`).
- No iteration, no random access — by design, you can only interact with
  the top. This is the "interface restriction" that makes it a stack.
- Recursion implicitly uses a call stack — an explicit `std::stack` is
  often used to convert a recursive algorithm to an iterative one
  (avoiding stack-overflow risk on deep recursion).
