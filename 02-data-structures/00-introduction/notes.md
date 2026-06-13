# Introduction to Data Structures

A **data structure** is a way of organizing and storing data so it can be
accessed and modified efficiently. Choosing the right one is often the
crux of solving a problem efficiently.

## Abstract Data Types (ADTs)

An ADT defines a data structure purely by its **behavior** (operations and
their semantics) without specifying the implementation. Examples:

- **List**: an ordered collection supporting insert/remove/access by
  position.
- **Stack**: insert/remove from one end only (LIFO).
- **Queue**: insert at one end, remove from the other (FIFO).
- **Map**: key-value associations.

A `List` ADT could be implemented as an **array** or a **linked list** —
both satisfy the same interface but with different performance
characteristics.

## List as an ADT: array vs linked list implementations

| Operation | Array | Linked List |
|---|---|---|
| Access by index | O(1) | O(n) |
| Insert/delete at front | O(n) (shift elements) | O(1) |
| Insert/delete at end | O(1) amortized (if dynamic array) | O(1) if tail pointer kept, else O(n) |
| Insert/delete in middle | O(n) | O(n) to find position, O(1) to link |
| Memory layout | contiguous | scattered, linked via pointers |
| Memory overhead | none extra | extra pointer(s) per element |
| Cache locality | excellent | poor |

## Arrays vs Linked Lists — when to use which

**Arrays** win when:
- You need fast random access (`arr[i]`).
- The size is known or changes infrequently.
- Cache performance matters (contiguous memory is much faster to iterate).

**Linked Lists** win when:
- You frequently insert/delete at the front or middle without shifting.
- You don't need random access.
- Size is highly dynamic and unpredictable.

In practice, dynamic arrays (`std::vector`) are preferred for most
general-purpose use due to cache locality — linked lists are mostly useful
for specific patterns (e.g. implementing other structures like queues, or
when iterator stability across insertions matters).

## Key interview points

- "Which data structure should I use?" almost always comes down to: what
  operations are most frequent, and what are their required time
  complexities?
- Big-O analysis is the language used to compare data structures —
  always be ready to state the complexity of each operation for a given
  structure.
- Many real-world data structures (hash maps, trees, heaps) are built by
  combining or extending these fundamental ones.
