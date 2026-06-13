# While & Do-While Loops

## while loop

Checks the condition **before** each iteration. May execute zero times.

```cpp
int i = 0;
while (i < 5) {
    std::cout << i << ' ';
    i++;
}
```

## do-while loop

Checks the condition **after** each iteration, so the body always runs at
least once.

```cpp
int choice;
do {
    std::cout << "Enter 1 to continue, 0 to quit: ";
    std::cin >> choice;
} while (choice != 0);
```

## Loop control

- `break` — exits the loop immediately.
- `continue` — skips to the next iteration's condition check.

## Infinite loops

```cpp
while (true) {
    // ... must contain a break or return somewhere
}
```

Common for event loops / servers that run until an explicit exit condition.

## Key interview points

- Use `do-while` when the loop body must run at least once regardless of
  the condition (e.g. menu prompts).
- Off-by-one and infinite-loop bugs are the most common mistakes — always
  verify the loop variable is updated and the exit condition is reachable.
- `while (true)` with `break` is often clearer than convoluted condition
  logic for "loop until some event happens".
