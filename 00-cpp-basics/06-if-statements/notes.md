# If Statements & Switch

Control flow constructs for branching based on conditions.

## if / else if / else

```cpp
if (score >= 90) {
    grade = 'A';
} else if (score >= 80) {
    grade = 'B';
} else {
    grade = 'C';
}
```

- Conditions must evaluate to something convertible to `bool`.
- `0`, `0.0`, `nullptr`, and `false` are "falsy"; everything else is "truthy".

## Comparison & logical operators

| Operator | Meaning              |
|----------|----------------------|
| `==`     | equal to             |
| `!=`     | not equal to         |
| `<` `>`  | less / greater than  |
| `<=` `>=`| less/greater or equal|
| `&&`     | logical AND          |
| `\|\|`   | logical OR           |
| `!`      | logical NOT          |

`&&` and `||` **short-circuit** — the right operand is only evaluated if
needed.

## switch statements

```cpp
switch (day) {
    case 1:
        std::cout << "Monday";
        break;
    case 2:
        std::cout << "Tuesday";
        break;
    default:
        std::cout << "Unknown";
}
```

- `switch` only works with integral/enum types (and values known at
  compile time for `case` labels).
- Without `break`, execution **falls through** to the next case — a common
  bug, but occasionally used intentionally to group cases.
- `default` is optional but recommended for catching unexpected values.

## Key interview points

- Prefer `switch` over a long `if/else if` chain when comparing one
  variable against many constant values — clearer and can be optimized
  into a jump table.
- `=` vs `==` is a classic bug: `if (x = 5)` assigns 5 to `x` (and is
  truthy), instead of comparing. Many compilers warn about this.
