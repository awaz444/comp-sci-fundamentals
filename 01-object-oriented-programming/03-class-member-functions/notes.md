# Class Member Functions (Methods)

Member functions define the behavior of a class. They have implicit access
to the object's member variables via the [`this`](../09-this-keyword/notes.md)
pointer.

## Defining inside the class

```cpp
class Rectangle {
public:
    double width, height;

    double area() {
        return width * height; // implicitly this->width * this->height
    }
};
```

## Defining outside the class (`::`)

Declare the function signature inside the class, define the body outside
using the **scope resolution operator** `::`. Common when separating
declaration (header `.h`) from implementation (`.cpp`):

```cpp
// In the class definition:
class Rectangle {
public:
    double width, height;
    double area(); // declaration only
};

// Outside the class:
double Rectangle::area() {
    return width * height;
}
```

## const member functions

```cpp
double area() const { // promises not to modify member variables
    return width * height;
}
```

- A `const` member function can be called on `const` objects and
  `const&` parameters.
- Calling a non-`const` member function on a `const` object is a compile
  error.
- Mark every method that doesn't modify state as `const` — it documents
  intent and widens where the method can be used.

## Inline functions

Functions defined **inside** the class body are implicitly `inline` — the
compiler may substitute the function call with the function body directly,
avoiding call overhead for small functions. Functions defined outside the
class are not inline by default (unless marked `inline` explicitly).

## Key interview points

- Defining many/large member functions outside the class (in a `.cpp`
  file) keeps the class declaration (header) clean and reduces
  recompilation when implementation changes.
- `const`-correctness is heavily checked in interviews — getters should
  almost always be `const`.
- The `::` operator is also used for namespaces, nested classes, and
  enums — it generally means "look inside this scope".
