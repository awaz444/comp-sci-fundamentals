# Abstract Classes & Pure Virtual Functions

## Pure virtual functions

A **pure virtual function** has no implementation in the base class — it
declares an interface that derived classes **must** implement:

```cpp
class Shape {
public:
    virtual double area() const = 0; // pure virtual: "= 0"
};
```

## Abstract classes

A class with at least one pure virtual function is an **abstract class**:

- It **cannot be instantiated** directly: `Shape s;` is a compile error.
- It can still have constructors, member variables, and regular (non-pure)
  member functions — these are inherited normally.
- Any derived class that doesn't implement **all** pure virtual functions
  is itself abstract.

```cpp
class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
private:
    double radius;
};

Shape* s = new Circle(5); // OK — Circle is concrete
// Shape s2;               // error — Shape is abstract
```

## Pure virtual destructors

A destructor can also be pure virtual — this is occasionally used to force
a class to be abstract even if it has no other pure virtual methods. A
pure virtual destructor still needs a **definition** (unlike other pure
virtual functions), because the base destructor is always called during
destruction of a derived object:

```cpp
class Base {
public:
    virtual ~Base() = 0; // pure virtual destructor
};

Base::~Base() {} // must still provide a definition, even though it's "pure"
```

## Hidden feature: implementing a pure virtual function within its own abstract class

You CAN provide a body for a pure virtual function in the same class that
declares it `= 0` — derived classes still cannot skip overriding it (the
class is still abstract), but they can explicitly call the base's
implementation via `Base::method()`:

```cpp
class Shape {
public:
    virtual double area() const = 0; // still pure — Shape remains abstract
};

// Out-of-class definition: a pure virtual function CAN have a body
double Shape::area() const {
    return 0.0; // a sensible default that derived classes can opt into
}

class Unknown : public Shape {
public:
    double area() const override {
        return Shape::area(); // explicitly calls the base's default implementation
    }
};
```

Note the syntax: `= 0 { ... }` inline is **not** valid C++. The body must
be a separate out-of-class definition (`Shape::area() const { ... }`),
exactly like the pure virtual destructor case below.

This is rarely used but demonstrates that `= 0` only enforces "must
override", not "must have no implementation".

## Abstract classes as interfaces

A class with **only** pure virtual functions (and no data members) acts
like an interface (similar to Java/C# `interface`):

```cpp
class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};
```

## Key interview points

- Abstract classes define a **contract** — "any subclass must provide
  these behaviors" — while still allowing shared code via non-pure virtual
  or regular methods.
- `= 0` means "no default implementation is *required*"; it does NOT mean
  "no implementation is *allowed*" (see the hidden-feature note above).
- A pure virtual destructor still requires a definition because
  destructors are always invoked as part of the destruction chain — unlike
  other pure virtual functions which may never be called if never
  overridden... but actually MUST be overridden to instantiate, so this is
  purely about destructor call semantics.
