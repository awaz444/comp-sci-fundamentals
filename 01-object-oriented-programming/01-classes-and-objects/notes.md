# Classes & Objects

A **class** is a blueprint that bundles data (member variables) and
behavior (member functions) together. An **object** is an instance of a
class.

## Defining a class

```cpp
class Person {
public:
    std::string name;
    int age;

    void introduce() {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old.\n";
    }
};
```

## Creating objects

```cpp
Person alice;          // stack-allocated object
alice.name = "Alice";
alice.age = 30;
alice.introduce();

Person* bob = new Person(); // heap-allocated (remember to delete)
bob->name = "Bob";
delete bob;
```

- `.` accesses members of an object (or reference).
- `->` accesses members through a pointer (`bob->name` is shorthand for
  `(*bob).name`).

## class vs struct

```cpp
struct Point { int x, y; };  // members default to public
class Point2 { int x, y; };  // members default to private
```

The **only** difference between `class` and `struct` in C++ is the default
access level (private vs public) and default inheritance type. By
convention, `struct` is used for simple data aggregates with no/minimal
behavior, `class` for types with invariants and behavior.

## Key interview points

- A class defines a **type**; an object is a **value** of that type.
- Member variables live inside each object instance; member functions are
  shared (the compiled code exists once, called with an implicit `this`
  pointer to the object).
- `sizeof(SomeClass)` is determined by its member variables (plus
  padding/alignment) — member functions don't add to an object's size.
