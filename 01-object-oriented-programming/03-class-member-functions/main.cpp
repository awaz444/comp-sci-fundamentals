#include <iostream>

class Rectangle {
public:
    double width;
    double height;

    // Defined inside the class -> implicitly inline
    double area() const {
        return width * height;
    }

    // Declared here, defined outside the class using ::
    double perimeter() const;

    void scale(double factor) {
        width *= factor;
        height *= factor;
    }
};

// Definition outside the class
double Rectangle::perimeter() const {
    return 2 * (width + height);
}

void printArea(const Rectangle& r) {
    // Only callable because area() is const — r is a const reference
    std::cout << "Area: " << r.area() << '\n';
}

int main() {
    Rectangle rect{4.0, 5.0};

    std::cout << "Area: " << rect.area() << '\n';
    std::cout << "Perimeter: " << rect.perimeter() << '\n';

    rect.scale(2.0); // non-const method, modifies width/height
    std::cout << "After scale, area: " << rect.area() << '\n';

    printArea(rect); // works because area() is const

    return 0;
}
