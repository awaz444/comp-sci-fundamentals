#include <iostream>

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // operator+ as a member function
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // operator== and operator!=
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
};

// operator<< must be a free function: left operand is std::ostream, not Vector2D
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os; // return stream so calls can be chained
}

class MyArray {
public:
    // Non-const version: allows modification
    int& operator[](int index) { return data[index]; }
    // Const version: read-only access for const objects
    const int& operator[](int index) const { return data[index]; }

private:
    int data[10] = {0};
};

int main() {
    Vector2D a(1, 2), b(3, 4);

    Vector2D c = a + b;
    std::cout << "a + b = " << c << '\n';

    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';

    // Chaining operator<<
    std::cout << "a = " << a << ", b = " << b << '\n';

    MyArray arr;
    arr[0] = 100; // uses non-const operator[]
    std::cout << "arr[0] = " << arr[0] << '\n';

    return 0;
}
