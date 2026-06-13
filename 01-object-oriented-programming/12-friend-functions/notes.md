# Friend Functions

A `friend` declaration grants a function (or another class) access to a
class's `private` and `protected` members, even though it isn't a member
of that class.

## Declaring a friend function

```cpp
class Box {
public:
    Box(double w) : width(w) {}

    friend void printWidth(const Box& b); // declared INSIDE the class

private:
    double width;
};

// Defined OUTSIDE the class, like a normal free function
void printWidth(const Box& b) {
    std::cout << "Width: " << b.width << '\n'; // can access private member
}
```

- The `friend` declaration goes inside the class (any access section —
  it's not itself a member, so `public`/`private` placement doesn't
  matter).
- The function itself is defined as an ordinary free function, **not**
  with `ClassName::`.

## Operator overloading using friend functions

The classic use case: `operator<<` for printing needs access to private
members but can't be a member function (the left-hand operand is
`ostream`, not the class):

```cpp
class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

private:
    double x, y; // private — friend can still access these
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")"; // accesses private x, y
    return os;
}
```

Without `friend`, `x` and `y` would need to be `public`, breaking
encapsulation.

## Friend classes

An entire class can be made a friend, giving all of its member functions
access:

```cpp
class Engine; // forward declaration

class Car {
    friend class Engine; // Engine can access Car's private members
private:
    int horsepower = 300;
};

class Engine {
public:
    void tune(Car& car) {
        car.horsepower += 50; // allowed: Engine is a friend of Car
    }
};
```

## Key interview points

- `friend` is a **deliberate exception to encapsulation** — use sparingly,
  typically for operator overloading or tightly-coupled helper
  classes/functions.
- Friendship is **not mutual** and **not inherited**: if `A` is a friend of
  `B`, `B` is not automatically a friend of `A`, and subclasses of `A`
  don't inherit the friendship.
- A `friend` function is **not** a member function — it has no `this`
  pointer and isn't called with `obj.func()` syntax (unless it also
  happens to take the object as a parameter, as with `operator<<`).
