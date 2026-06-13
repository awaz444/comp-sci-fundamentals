# Linked Lists (Singly & Doubly)

A linked list is a sequence of **nodes**, each holding data and a pointer
to the next node (and, for doubly linked lists, the previous node too).
Unlike arrays, elements are **not** contiguous in memory.

## Singly Linked List

```cpp
struct Node {
    int data;
    Node* next;
};
```

A list is represented by a pointer to the `head` node; the last node's
`next` is `nullptr`.

### Insert at the beginning — O(1)

```cpp
Node* newNode = new Node{value, head};
head = newNode;
```

### Insert at the nth position — O(n)

Traverse to the (n-1)th node, then relink:

```cpp
Node* prev = head;
for (int i = 0; i < n - 1; i++) prev = prev->next;
Node* newNode = new Node{value, prev->next};
prev->next = newNode;
```

### Delete at the nth position — O(n)

Traverse to the (n-1)th node, bypass the target node, free its memory:

```cpp
Node* prev = head;
for (int i = 0; i < n - 1; i++) prev = prev->next;
Node* toDelete = prev->next;
prev->next = toDelete->next;
delete toDelete;
```

### Reversing — iterative (O(n), O(1) extra space)

Walk through the list, redirecting each node's `next` pointer to point
backward, tracking `prev`, `curr`, `next`:

```cpp
Node* prev = nullptr;
Node* curr = head;
while (curr != nullptr) {
    Node* nextNode = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextNode;
}
head = prev;
```

### Reversing — recursive

```cpp
Node* reverseRecursive(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}
```

### Printing forward and backward using recursion

```cpp
// Forward: process current, then recurse
void printForward(Node* node) {
    if (!node) return;
    std::cout << node->data << ' ';
    printForward(node->next);
}

// Backward: recurse first, then process (unwinds in reverse order)
void printBackward(Node* node) {
    if (!node) return;
    printBackward(node->next);
    std::cout << node->data << ' ';
}
```

## Doubly Linked List

Each node also stores a pointer to the **previous** node:

```cpp
struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};
```

- Allows O(1) backward traversal and O(1) deletion of a node given just
  its pointer (no need to find the predecessor by traversal).
- Costs extra memory (one more pointer per node) and more bookkeeping on
  insert/delete (must update two sets of links).

## Key interview points

- Always handle **edge cases**: empty list (`head == nullptr`), single
  node, deleting the head, inserting at position 0.
- Singly linked list reversal (iterative, O(1) space) is one of the most
  commonly asked interview questions — know it cold.
- Doubly linked lists trade memory for bidirectional traversal and O(1)
  removal given a node pointer — used internally by `std::list`.
- Remember to `delete` removed nodes to avoid memory leaks (raw pointers
  require manual management — see
  [Dynamic Memory Allocation](../../00-cpp-basics/13-dynamic-memory-allocation/notes.md)).

## Practice Problems (LeetCode)

See `practice.cpp` for full working solutions.

1. **[Hard] Merge k Sorted Lists** (LeetCode 23) — Merge `k` sorted
   linked lists into one sorted list. Approach: push all list heads into
   a min-heap (`priority_queue`) keyed by node value; repeatedly pop the
   smallest, append it to the result, and push its `next` if non-null.
   O(N log k) where N is the total number of nodes.

2. **[Hard] Reverse Nodes in k-Group** (LeetCode 25) — Reverse the nodes
   of a linked list `k` at a time. Approach: reverse each group of `k`
   nodes iteratively (same technique as the basic reversal), then relink
   the reversed group between the previous group's tail and the next
   group's head. If fewer than `k` nodes remain, leave them as-is.

3. **[Medium/Classic] Linked List Cycle II** (LeetCode 142) — Detect
   whether a linked list has a cycle, and if so, return the node where
   the cycle begins. Approach: **Floyd's Cycle Detection** (tortoise and
   hare) — a slow pointer moves 1 step, a fast pointer moves 2 steps; if
   they meet, a cycle exists. To find the cycle's start, reset one
   pointer to `head` and advance both one step at a time until they meet
   again — that node is the cycle's start.

4. **[Medium] Copy List with Random Pointer** (LeetCode 138) — Each node
   has an extra `random` pointer to any node in the list (or null). Deep
   copy the list. Approach: use a hash map from original node ->
   cloned node, built in one pass; in a second pass, wire up `next` and
   `random` pointers on the clones using the map.
