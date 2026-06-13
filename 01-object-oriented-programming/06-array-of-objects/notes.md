# Array of Objects

Just like arrays of `int` or `double`, you can declare arrays where each
element is an object of a class.

## Declaring and initializing

```cpp
class Point {
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    int x, y;
};

Point points[3]; // calls the default constructor 3 times

Point pts2[3] = {
    Point(1, 2),
    Point(3, 4),
    Point(5, 6)
}; // each element initialized explicitly
```

## Requirements

- If you declare an array of objects **without** initializers
  (`Point points[3];`), the class **must** have a default constructor
  (no required arguments) — it's called once per element.
- Accessing/modifying elements works like any array: `points[0].x = 10;`.

## Iterating

```cpp
for (int i = 0; i < 3; i++) {
    std::cout << points[i].x << ", " << points[i].y << '\n';
}

// or with range-based for:
for (const auto& p : pts2) {
    std::cout << p.x << ", " << p.y << '\n';
}
```

## Dynamic arrays of objects

```cpp
Point* dynamicPoints = new Point[5]; // default constructor called 5 times
delete[] dynamicPoints;               // destructor called 5 times
```

## Key interview points

- Construction order for an array of objects is element 0, 1, 2, ... in
  order; destruction happens in **reverse** order when the array goes out
  of scope.
- `new Point[5]` requires a default constructor for the same reason as
  `Point points[5];` — there's no way to pass different constructor
  arguments to each element with this syntax.
- Prefer `std::vector<Point>` over raw arrays of objects in modern C++ —
  it manages memory automatically and supports dynamic resizing.
