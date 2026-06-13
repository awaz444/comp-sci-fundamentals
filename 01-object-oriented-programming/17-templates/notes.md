# Templates (Function & Class)

Templates let you write code that works with **any type**, with the
compiler generating type-specific versions as needed — C++'s mechanism for
generic programming.

## Function templates

```cpp
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

maxOf(3, 5);       // T = int
maxOf(2.5, 1.5);   // T = double
maxOf<double>(3, 5.5); // explicit instantiation
```

- `typename T` (or `class T` — equivalent) introduces a placeholder type.
- The compiler **instantiates** a separate version of the function for
  each type `T` it's called with — this happens at compile time
  ("template instantiation").
- Type is usually **deduced** from the arguments; rarely needs to be
  specified explicitly.

## Class templates

```cpp
template <typename T>
class Box {
public:
    Box(T value) : value(value) {}
    T get() const { return value; }
private:
    T value;
};

Box<int> intBox(42);
Box<std::string> strBox("hello");
```

- `Box<int>` and `Box<std::string>` are distinct, compiler-generated
  classes — templates aren't "one class that handles all types" at
  runtime, they're a blueprint for generating multiple classes.
- Member function definitions outside the class need the `template`
  prefix and `Box<T>::` qualifier:

```cpp
template <typename T>
T Box<T>::get() const { return value; }
```

## Multiple template parameters

```cpp
template <typename K, typename V>
class Pair {
public:
    Pair(K key, V value) : key(key), value(value) {}
    K key; V value;
};

Pair<std::string, int> p("age", 30);
```

This is essentially how `std::pair`, `std::map<K, V>`, etc. are
implemented.

## Overloading function templates

Templates can be overloaded with each other, and with non-template
functions. Resolution order (most to least preferred):

1. A non-template function that's an exact match.
2. A template specialization that's a better/more specific match.
3. A more general template.

```cpp
template <typename T>
void print(T value) { std::cout << "generic: " << value << '\n'; }

template <typename T>
void print(T* value) { std::cout << "pointer: " << *value << '\n'; } // more specific

void print(int value) { std::cout << "non-template int: " << value << '\n'; } // preferred for int
```

## Key interview points

- Templates achieve **compile-time** polymorphism (vs. virtual functions'
  **runtime** polymorphism) — zero runtime overhead, but can increase
  compile time and binary size ("code bloat") since each instantiation
  generates separate code.
- Template errors can be notoriously verbose/cryptic since they reference
  generated code, not your source directly.
- `std::vector<T>`, `std::map<K,V>`, `std::unique_ptr<T>` — essentially all
  of the STL is built on class templates.
