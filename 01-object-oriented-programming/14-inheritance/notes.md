# Inheritance

Inheritance lets a class (**derived**/**child**) reuse and extend the
members of another class (**base**/**parent**).

## Basic syntax

```cpp
class Animal {
public:
    void eat() { std::cout << "Eating...\n"; }
protected:
    std::string name;
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof!\n"; }
};

Dog d;
d.eat();  // inherited from Animal
d.bark(); // Dog's own method
```

## Base class access specifiers (`public`/`protected`/`private` inheritance)

The keyword before the base class name controls how inherited members'
access levels are adjusted in the derived class:

| Inheritance type | `public` base member becomes | `protected` base member becomes |
|---|---|---|
| `class D : public B`    | `public`    | `protected` |
| `class D : protected B` | `protected` | `protected` |
| `class D : private B`   | `private`   | `private`   |

- `public` inheritance ("is-a" relationship) is by far the most common —
  `private`/`protected` inheritance is rare and usually replaced by
  composition in modern code.
- Regardless of inheritance type, **`private` members of the base are
  never accessible** in the derived class.

## Protected members

`protected` exists specifically for inheritance: a base class can expose
data/methods to its derived classes (for use in their implementation)
without making them part of the **public** interface. See
[Access Specifiers](../02-access-specifiers/notes.md).

```cpp
class Animal {
protected:
    std::string name; // derived classes can access this directly
};

class Dog : public Animal {
public:
    void setName(std::string n) { name = n; } // OK: protected, accessible here
};
```

## Constructors with inheritance

A derived class constructor must initialize its base class — call the base
constructor explicitly in the initializer list (or the base's default
constructor is called implicitly):

```cpp
class Animal {
public:
    Animal(std::string name) : name(name) {}
protected:
    std::string name;
};

class Dog : public Animal {
public:
    Dog(std::string name, std::string breed) : Animal(name), breed(breed) {}
private:
    std::string breed;
};
```

**Construction order**: base class constructor runs **first**, then
derived class members are initialized, then the derived constructor body
runs.

## Destructors with inheritance

**Destruction order is the reverse of construction**: derived destructor
body runs first, then derived members are destroyed, then the base
destructor runs.

```cpp
~Dog()    { std::cout << "Dog destroyed\n"; }    // runs first
~Animal() { std::cout << "Animal destroyed\n"; } // runs second
```

(See [Polymorphism & Virtual Functions](../15-polymorphism-virtual/notes.md)
for why base destructors usually need to be `virtual`.)

## Multilevel inheritance

A chain: `C : B`, `B : A` — `C` inherits from `B`, which inherits from `A`.
`C` has access to members of both `B` and `A` (subject to access rules).
Construction order: `A` → `B` → `C`. Destruction: `C` → `B` → `A`.

```cpp
class Animal { /* ... */ };
class Mammal : public Animal { /* ... */ };
class Dog : public Mammal { /* ... */ };
```

## Multiple inheritance

A class can inherit from more than one base class:

```cpp
class Swimmer { public: void swim() { ... } };
class Flyer   { public: void fly()  { ... } };

class Duck : public Swimmer, public Flyer {
    // has both swim() and fly()
};
```

### The diamond problem

If `B` and `C` both inherit from `A`, and `D` inherits from both `B` and
`C`, `D` ends up with **two copies** of `A`'s members — ambiguous to
access.

```
    A
   / \
  B   C
   \ /
    D
```

Fixed with **virtual inheritance**:

```cpp
class B : public virtual A { ... };
class C : public virtual A { ... };
class D : public B, public C { ... }; // D has only ONE A
```

## Key interview points

- Construction: base → derived. Destruction: derived → base (always the
  reverse).
- `protected` is the access level designed for the base/derived
  relationship — `private` base members are invisible to derived classes
  entirely.
- Multiple inheritance is powerful but can introduce the diamond problem;
  `virtual` inheritance solves it by ensuring a single shared base
  instance.
- Prefer composition ("has-a") over inheritance ("is-a") when the
  relationship isn't a true specialization — inheritance creates tight
  coupling.
