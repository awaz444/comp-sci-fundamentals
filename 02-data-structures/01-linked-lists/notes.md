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
