# `std::queue`

`std::queue<T>` (from `<queue>`) is a **FIFO** (First In, First Out)
container adapter — wraps another container (default `std::deque<T>`) and
restricts access to "front" and "back".

## Operations

```cpp
#include <queue>

std::queue<int> q;
q.push(1);     // add to back
q.push(2);
q.push(3);

q.front();     // 1 — the next element to be removed
q.back();      // 3 — the most recently added element
q.pop();       // removes the FRONT element — returns void!
q.size();      // 2
q.empty();     // false
```

| Operation | Complexity |
|---|---|
| `push` | O(1) |
| `pop` | O(1) |
| `front`/`back` | O(1) |
| `empty`/`size` | O(1) |

## `std::queue` vs `std::stack`

Both are container adapters with the same core operations (`push`, `pop`,
`empty`, `size`), but differ in **which end** `pop` removes from:

- `std::stack`: `pop()` removes from the same end as `push()` (LIFO —
  "top").
- `std::queue`: `pop()` removes from the **opposite** end from `push()`
  (FIFO — "front" vs "back").

## `std::priority_queue`

A related adapter that always keeps the **largest** (by default) element
accessible via `top()`:

```cpp
#include <queue>
std::priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(2);
pq.top();  // 3 (largest)
pq.pop();  // removes 3

// min-heap variant:
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
```

## Typical use cases

- BFS (breadth-first search) — process nodes level by level.
- Task scheduling / job queues (FIFO order).
- Producer-consumer patterns (see
  [Parallel Computing](../../04-parallel-computing/README.md)).
- `priority_queue` for algorithms like Dijkstra's shortest path, heap
  sort, "find k largest elements".

## Key interview points

- `std::queue` (FIFO) is the natural fit for BFS; `std::stack` (LIFO) for
  DFS — a very common interview distinction.
- Like `std::stack`, `pop()` returns nothing — read `front()`/`top()`
  before popping.
- `std::priority_queue` is a **max-heap** by default; pass
  `std::greater<T>` as the comparator for a min-heap.
