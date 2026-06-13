# Comments

Comments are ignored by the compiler — they exist purely for humans.

## Single-line comments

```cpp
// This is a single-line comment
int x = 5; // can also follow code on the same line
```

## Multi-line comments

```cpp
/*
 * This is a multi-line comment.
 * Useful for longer explanations or temporarily disabling
 * a block of code.
 */
```

## Best practices

- Comment **why**, not **what** — the code already shows what it does.
- Avoid commenting out large blocks of code long-term; delete it (version
  control remembers it for you).
- Use comments to explain non-obvious constraints, edge cases, or
  workarounds.
- Multi-line comments (`/* */`) cannot be nested.

## Key interview points

- Comments have zero runtime cost — they're stripped during preprocessing.
- Doc-comment styles (e.g. `///` or `/** */`) are conventions used by tools
  like Doxygen to auto-generate documentation.
