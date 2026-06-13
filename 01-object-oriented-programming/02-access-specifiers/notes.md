# Access Specifiers

Access specifiers control which code can access a class's members —
the core mechanism behind **encapsulation**.

## The three levels

| Specifier | Accessible from |
|---|---|
| `public` | anywhere |
| `private` | only member functions of the same class (and friends) |
| `protected` | member functions of the same class, friends, **and derived classes** |

```cpp
class BankAccount {
public:
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
    double getBalance() const { return balance; }

private:
    double balance = 0.0; // can't be touched directly from outside
};
```

## Default access

- `class` members are **private** by default.
- `struct` members are **public** by default.

## Getters and setters

Private data is typically exposed through public **accessor** (`getX()`)
and **mutator** (`setX()`) methods, which can validate input or compute
derived values — direct field access can't do that.

```cpp
class Person {
public:
    void setAge(int a) {
        if (a >= 0) age = a; // validation the caller can't bypass
    }
    int getAge() const { return age; }

private:
    int age = 0;
};
```

## `protected` and inheritance

`protected` members are invisible to outside code but visible to derived
classes — a middle ground between "fully hidden" and "fully exposed".
Covered further in [Inheritance](../14-inheritance/notes.md).

## Key interview points

- Access specifiers are a **compile-time** concept — they don't affect the
  binary layout or runtime behavior, only what the compiler allows you to
  write.
- Encapsulation (hiding internal representation behind `private` +
  controlled `public` accessors) lets you change internal implementation
  without breaking code that uses the class.
- A `class`'s default of `private` nudges you toward encapsulation by
  default — you must explicitly opt members into the public interface.
