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

## Practice Problems (LeetCode)

See `practice.cpp` for full working solutions.

1. **[Hard] Sliding Window Maximum** (LeetCode 239) — Given an array and
   a window size `k`, return the maximum of each sliding window.
   Approach: maintain a **monotonic deque** of indices with decreasing
   values. For each new element, pop smaller elements from the back
   (they can never be the max while the new element is in the window),
   and pop indices from the front that have fallen out of the window.
   The front of the deque is always the max. O(n).

2. **[Medium/Classic] Implement Stack using Queues** (LeetCode 225) —
   Build a LIFO stack using only queue operations. Approach: on `push`,
   enqueue the new element, then rotate the queue by dequeuing and
   re-enqueuing all the *previous* elements behind it — this makes the
   newest element always the front (O(n) push, O(1) pop/top).

3. **[Medium/Classic] Implement Queue using Stacks** (LeetCode 232) —
   Build a FIFO queue using only stack operations. Approach: use two
   stacks — `inStack` for pushes (O(1)) and `outStack` for pops/peeks.
   When `outStack` is empty, transfer all elements from `inStack` to
   `outStack` (reversing their order), then pop/peek from `outStack`.
   Amortized O(1) per operation.

4. **[Medium] First Unique Character in a Stream** — Given a stream of
   characters, find the first character that hasn't repeated, at any
   point. Approach: maintain a frequency count and a queue of
   candidates; when querying, pop from the front of the queue any
   characters whose count is now > 1, and the new front is the answer
   (or none if the queue is empty).
