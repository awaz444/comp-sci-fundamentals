# Static Members

`static` members belong to the **class itself**, not to any individual
object — there is exactly one copy shared by all instances.

## Static member variables ("class variables")

```cpp
class Employee {
public:
    Employee() { totalEmployees++; }
    ~Employee() { totalEmployees--; }

    static int totalEmployees; // declaration only
};

// Definition (and initialization) — required in exactly one .cpp file
int Employee::totalEmployees = 0;
```

- Every `Employee` object shares the same `totalEmployees` variable.
- Useful for counters, shared configuration, caches, or constants shared
  across all instances.
- Must be **defined** (with storage allocated) outside the class, in
  addition to being declared inside it — unless it's a `static constexpr`
  (which can be defined inline).

## Static member functions

```cpp
class Employee {
public:
    static int getTotalEmployees() { return totalEmployees; }
private:
    static int totalEmployees;
};
```

- Can be called **without an object**: `Employee::getTotalEmployees()`.
- Have **no `this` pointer** — they can only access `static` members
  (other non-static members don't exist without an object context).

## Accessing static members

```cpp
Employee e1, e2;
std::cout << Employee::totalEmployees;   // via class name (preferred)
std::cout << e1.totalEmployees;          // via an object (also legal, less clear)
```

## Key interview points

- Think of `static` members as belonging to the **class**, while regular
  (instance) members belong to each **object**.
- A static member variable exists even if **zero** objects of the class
  have been created (as long as the program has loaded the class's
  definition).
- Common use cases: instance counters, singletons (a static instance
  pointer), shared constants/configuration, factory ID generators.
