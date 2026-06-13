# Member Initializer Lists

The member initializer list is the `: member1(value1), member2(value2)`
syntax between a constructor's parameter list and its body.

```cpp
class Person {
public:
    Person(std::string name, int age) : name(name), age(age) {
        // body
    }
private:
    std::string name;
    int age;
};
```

## Initializer list vs assignment in the body

```cpp
// Initializer list — members are INITIALIZED directly
Person(std::string name, int age) : name(name), age(age) {}

// Assignment in body — members are first DEFAULT-constructed, then ASSIGNED
Person(std::string name, int age) {
    this->name = name; // name was already default-constructed (empty string)
    this->age = age;   // age was already default-initialized
}
```

For types like `std::string` or any class type, assignment-in-body does
extra work: default-construct, then assign — versus initializer lists
which construct with the final value directly. For simple types (`int`)
the difference is negligible, but for non-trivial members it's a real
performance difference.

## When the initializer list is REQUIRED

1. **`const` member variables** — can only be set once, at initialization.
2. **Reference members** — must be bound at initialization, can't be
   reassigned.
3. **Members without a default constructor** — if a member type has no
   default constructor, it MUST be initialized in the list.
4. **Base class constructors with arguments** — calling a base class
   constructor (other than the default) must happen in the initializer
   list (see [Inheritance](../14-inheritance/notes.md)).

```cpp
class Example {
public:
    Example(int val, int& ref) : CONST_VAL(val), refMember(ref) {}
private:
    const int CONST_VAL;
    int& refMember;
};
```

## Initialization order

Members are initialized in the **order they are declared in the class**,
NOT the order they appear in the initializer list. If one member's
initialization depends on another, declaration order matters — mismatched
order can cause subtle bugs (and most compilers warn about it with
`-Wreorder`).

## Key interview points

- Initializer lists avoid the "default construct then assign" overhead for
  class-type members.
- `const` members and reference members **cannot** be initialized any
  other way — this is a frequent interview question.
- Always match the initializer list order to the declaration order to
  avoid `-Wreorder` warnings and surprises with interdependent members.
