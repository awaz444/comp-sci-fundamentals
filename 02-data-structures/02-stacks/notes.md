# Stacks

A **stack** is a LIFO (Last-In, First-Out) data structure supporting:

- `push(x)` — add `x` to the top.
- `pop()` — remove the top element.
- `top()` / `peek()` — view the top element without removing it.
- `isEmpty()` — check if the stack has no elements.

All operations are O(1).

## Implementations

### Array-based

Keep an array and a `top` index. `push` increments `top` and writes;
`pop` reads and decrements `top`. Simple and cache-friendly, but has a
fixed capacity unless you use a dynamic array (`std::vector`).

### Linked-list-based

Push/pop at the **head** of a singly linked list — both O(1), and no
fixed capacity. Slightly more memory overhead per element (pointer +
allocation).

## Reversing using a stack

To reverse a string or a linked list:

1. Push every character/element onto a stack.
2. Pop everything back off — they come out in reverse order.

```cpp
std::stack<char> s;
for (char c : str) s.push(c);
std::string reversed;
while (!s.empty()) { reversed += s.top(); s.pop(); }
```

## Balanced Parentheses

Classic stack application — check whether `(){}[]` are balanced:

- On an opening bracket, push it.
- On a closing bracket, pop and check it matches the corresponding
  opening bracket. If the stack is empty or it doesn't match, the
  string is unbalanced.
- At the end, the stack must be empty.

## Infix, Prefix, and Postfix Notation

- **Infix**: operator between operands — `a + b` (what humans normally write).
- **Prefix** (Polish notation): operator before operands — `+ a b`.
- **Postfix** (Reverse Polish notation): operator after operands — `a b +`.

Postfix/prefix notation removes the need for parentheses and operator
precedence rules — this is why calculators and compilers often convert
expressions to postfix/prefix internally.

### Evaluating Postfix expressions (using a stack)

Scan left to right:
- If the token is an operand, push it.
- If the token is an operator, pop two operands (`b` then `a`), compute
  `a OP b`, and push the result back.

```
Postfix: 2 3 4 * +
  push 2, push 3, push 4
  '*': pop 4, pop 3 -> push 3*4=12   stack: [2, 12]
  '+': pop 12, pop 2 -> push 2+12=14 stack: [14]
Result: 14   (equivalent to 2 + 3*4)
```

### Evaluating Prefix expressions (using a stack)

Scan **right to left**:
- If the token is an operand, push it.
- If the token is an operator, pop two operands (`a` then `b`), compute
  `a OP b`, and push the result back.

### Infix to Postfix conversion (Shunting-yard algorithm, simplified)

Use a stack to hold operators:
- Operands go directly to the output.
- An operator is pushed after popping (to output) any operators on the
  stack with greater or equal precedence.
- `(` is pushed onto the stack; on `)`, pop operators to output until
  `(` is found (and discard both parentheses).
- At the end, pop all remaining operators to output.

## Key interview points

- Stack = LIFO; know both array-based and linked-list-based implementations
  and their tradeoffs (fixed capacity vs pointer overhead).
- Balanced parentheses and postfix/prefix evaluation are extremely common
  interview questions built directly on the stack ADT.
- Function call stacks, undo/redo, and DFS (graph/tree traversal) are all
  real-world applications of stacks.
- `std::stack` is a container *adapter* — by default backed by
  `std::deque` (see [Stack STL](../../10-cpp-standard-library/04-stack-container/notes.md)).
