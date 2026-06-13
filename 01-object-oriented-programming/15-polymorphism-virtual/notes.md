# Polymorphism & Virtual Functions

**Polymorphism** ("many forms") lets code work with objects of different
derived types through a common base type interface, with the correct
derived behavior selected automatically.

## Without `virtual`: static binding

```cpp
class Animal {
public:
    void speak() { std::cout << "Animal sound\n"; }
};
class Dog : public Animal {
public:
    void speak() { std::cout << "Woof!\n"; } // hides, doesn't override
};

Animal* a = new Dog();
a->speak(); // prints "Animal sound" — decided at COMPILE TIME based on pointer's type
```

The compiler picks `Animal::speak` because `a` is declared as `Animal*`,
regardless of what it actually points to. This is **static (compile-time)
binding**.

## With `virtual`: dynamic binding

```cpp
class Animal {
public:
    virtual void speak() { std::cout << "Animal sound\n"; }
};
class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof!\n"; } // overrides
};

Animal* a = new Dog();
a->speak(); // prints "Woof!" — decided at RUNTIME based on actual object type
```

Marking the base method `virtual` makes the call resolve based on the
**actual (dynamic) type** of the object at runtime, not the static type of
the pointer/reference. This is **dynamic binding**, implemented via a
**vtable** (virtual function table) — a hidden per-class table of function
pointers that the object's vptr points to.

## `override` keyword (C++11)

```cpp
void speak() override { ... }
```

Tells the compiler "this is meant to override a virtual base method" —
the compiler errors if no matching virtual function exists in the base
(e.g. due to a typo or signature mismatch). Always use it.

## Virtual destructors

If a class might be deleted through a **base class pointer**, its
destructor must be `virtual` — otherwise only the base class's destructor
runs, leaking any derived class resources.

```cpp
class Animal {
public:
    virtual ~Animal() { std::cout << "~Animal\n"; }
};
class Dog : public Animal {
public:
    ~Dog() override { std::cout << "~Dog\n"; }
};

Animal* a = new Dog();
delete a; // with virtual ~Animal(): prints ~Dog then ~Animal (correct)
          // without virtual: prints only ~Animal — Dog's resources leak!
```

**Rule of thumb**: if a class has ANY virtual function, give it a virtual
destructor too.

## Key interview points

- Virtual functions enable **runtime polymorphism** — the classic
  interview example is `Shape* shapes[] = {new Circle(), new Square()};`
  and calling `shapes[i]->area()` getting the correct derived `area()`.
- The vtable mechanism adds a small memory overhead (one vptr per object)
  and a small runtime indirection cost (one extra pointer lookup per
  virtual call) — the tradeoff for flexibility.
- Forgetting `virtual` on a destructor when deleting via a base pointer is
  a classic memory-leak bug, frequently asked about in interviews.
