# Queues

A **queue** is a FIFO (First-In, First-Out) data structure supporting:

- `enqueue(x)` — add `x` to the back.
- `dequeue()` — remove the element from the front.
- `front()` — view the front element without removing it.
- `isEmpty()` — check if the queue has no elements.

All operations are O(1) (with the right implementation).

## Array-based implementation

A naive array queue (incrementing a `front` index on dequeue and a
`back` index on enqueue) wastes space as `front` advances — the
"used" portion of the array drifts forward without being reclaimed.

The standard fix is a **circular buffer**: indices wrap around using
modulo arithmetic, so freed space at the front of the array is reused.

```cpp
back = (back + 1) % capacity;
front = (front + 1) % capacity;
```

A `count` variable tracks the number of elements so you can
distinguish "empty" from "full" (both would otherwise have
`front == back`).

## Linked-list-based implementation

Keep both a `head` (front) and `tail` (back) pointer:

- `enqueue`: append a new node after `tail`, update `tail`. O(1).
- `dequeue`: remove `head`, advance `head` to `head->next`. O(1).

This avoids the fixed-capacity problem of arrays entirely, at the cost
of per-node pointer overhead.

## Key interview points

- Queue = FIFO; the circular buffer trick is the key insight for an
  efficient array-based implementation — without it, naive
  implementations degrade to O(n) or waste memory.
- Linked-list implementation needs **both** head and tail pointers to
  keep enqueue O(1) (otherwise you'd have to traverse to the end).
- Queues are the foundation of BFS (breadth-first search) in trees and
  graphs, task scheduling, and producer-consumer buffers.
- `std::queue` is a container adapter — by default backed by
  `std::deque` (see [Queue STL](../../10-cpp-standard-library/05-queue-container/notes.md)).
