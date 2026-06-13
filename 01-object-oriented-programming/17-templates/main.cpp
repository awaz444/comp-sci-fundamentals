#include <iostream>
#include <string>

// Function template
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

// Class template
template <typename T>
class Box {
public:
    Box(T value) : value(value) {}

    T get() const; // declared here, defined outside below

    void set(T newValue) { value = newValue; }

private:
    T value;
};

// Member function defined outside the class template
template <typename T>
T Box<T>::get() const {
    return value;
}

// Class template with multiple parameters
template <typename K, typename V>
class Pair {
public:
    Pair(K key, V value) : key(key), value(value) {}

    void print() const {
        std::cout << key << " -> " << value << '\n';
    }

    K key;
    V value;
};

// Overloaded function templates
template <typename T>
void describe(T value) {
    std::cout << "generic value: " << value << '\n';
}

template <typename T>
void describe(T* value) { // more specific: pointer overload
    std::cout << "pointer to value: " << *value << '\n';
}

int main() {
    // Function template with deduced types
    std::cout << "maxOf(3, 5) = " << maxOf(3, 5) << '\n';
    std::cout << "maxOf(2.5, 1.5) = " << maxOf(2.5, 1.5) << '\n';
    std::cout << "maxOf<double>(3, 5.5) = " << maxOf<double>(3, 5.5) << '\n';

    // Class template instantiations
    Box<int> intBox(42);
    Box<std::string> strBox("hello");
    std::cout << "intBox = " << intBox.get() << ", strBox = " << strBox.get() << '\n';

    // Multiple template parameters
    Pair<std::string, int> p("age", 30);
    p.print();

    // Overloaded function templates
    int x = 10;
    describe(x);   // generic version
    describe(&x);  // pointer version (more specific)

    return 0;
}
