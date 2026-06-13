# For Loops (Classic & Range-Based)

## Classic for loop

```cpp
for (int i = 0; i < 10; i++) {
    std::cout << i << ' ';
}
```

Three parts separated by `;`:
1. **Initialization** — runs once before the loop starts (`int i = 0`).
2. **Condition** — checked before each iteration; loop ends when false.
3. **Update** — runs after each iteration (`i++`).

Any of the three parts can be empty: `for (;;) { ... }` is an infinite loop.

## Range-based for loop (C++11)

Iterates directly over the elements of a container/array — no index
bookkeeping:

```cpp
std::vector<int> nums = {1, 2, 3, 4};
for (int n : nums) {
    std::cout << n << ' ';
}
```

- Use `for (auto& x : container)` to modify elements in place (reference,
  avoids copying).
- Use `for (const auto& x : container)` to read large elements without
  copying.
- Use `for (auto x : container)` (by value) only for small/cheap types.

## Key interview points

- Range-based for loops don't give you the index directly — if you need
  it, either use a classic loop or track it manually.
- Modifying a container's size while iterating with range-based for is
  undefined behavior (iterator invalidation).
- `for (auto& x : container)` vs `for (auto x : container)` is a frequent
  interview gotcha — by-value silently copies and won't affect the
  original container.
