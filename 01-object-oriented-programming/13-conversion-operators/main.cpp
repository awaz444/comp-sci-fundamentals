#include <iostream>

class Fraction {
public:
    Fraction(int num, int den) : numerator(num), denominator(den) {}

    // Implicit conversion operator: Fraction -> double
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

private:
    int numerator, denominator;
};

class Optional {
public:
    Optional() : hasValue(false), value(0) {}
    Optional(int v) : hasValue(true), value(v) {}

    // explicit operator bool: usable in conditions, but not implicit int conversions
    explicit operator bool() const {
        return hasValue;
    }

    int get() const { return value; }

private:
    bool hasValue;
    int value;
};

int main() {
    Fraction half(1, 2);

    // Implicit conversion to double
    double d = half;
    std::cout << "half as double = " << d << '\n';
    std::cout << "half + 0.5 = " << (half + 0.5) << '\n';

    // explicit operator bool usage
    Optional empty;
    Optional present(42);

    if (!empty) {
        std::cout << "empty has no value\n";
    }
    if (present) {
        std::cout << "present has value: " << present.get() << '\n';
    }

    // bool b = present; // would be a compile error: explicit required
    bool b = static_cast<bool>(present); // explicit cast works
    std::cout << "b = " << b << '\n';

    return 0;
}
