# Constructors & Destructors

## Constructors

A **constructor** is a special member function called automatically when
an object is created. It has the same name as the class and no return
type.

```cpp
class Person {
public:
    Person(std::string name, int age) : name(name), age(age) {
        std::cout << "Constructing " << name << '\n';
    }

private:
    std::string name;
    int age;
};

Person p("Alice", 30); // constructor runs automatically
```

### Default constructor

A constructor with no parameters (or all-default parameters). If you
define **any** constructor, the compiler stops generating the default one
automatically — define it explicitly if you still need it.

```cpp
Person() : name("Unknown"), age(0) {}
```

### Parameterized constructors & overloading

Constructors can be overloaded like any function — different parameter
lists for different initialization scenarios.

## Destructors

A **destructor** runs automatically when an object is destroyed (goes out
of scope, or `delete`d). Named `~ClassName()`, takes no parameters, no
return type, and a class has **exactly one**.

```cpp
class FileHandle {
public:
    ~FileHandle() {
        std::cout << "Closing resource\n";
        // release resources: close files, free memory, etc.
    }
};
```

This is the basis of **RAII** (Resource Acquisition Is Initialization) —
tie resource lifetime to object lifetime.

## Constructor delegation (C++11)

A constructor can call another constructor of the same class to avoid
duplicating initialization logic:

```cpp
class Person {
public:
    Person() : Person("Unknown", 0) {}              // delegates to the other ctor
    Person(std::string name) : Person(name, 0) {}    // delegates too
    Person(std::string name, int age) : name(name), age(age) {}

private:
    std::string name;
    int age;
};
```

- The delegating constructor's body runs **after** the target
  constructor completes.
- A constructor that delegates cannot also have its own member
  initializer list entries for the same members (the target constructor
  handles them).

## Key interview points

- Order of operations: constructors of **members and base classes** run
  before the constructor body executes; destructors run in the **reverse**
  order of construction.
- If a class manages a resource (memory, file handle, lock), the
  destructor is where it must be released — this is the foundation of
  smart pointers (`unique_ptr`, etc.).
- Constructor delegation reduces duplicated initialization code but adds a
  small amount of indirection — useful for "default-value" constructor
  overloads.
