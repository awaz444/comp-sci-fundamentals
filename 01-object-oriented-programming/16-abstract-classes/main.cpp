#include <iostream>
#include <vector>

// Abstract class: has a pure virtual function, cannot be instantiated
class Shape {
public:
    // Pure virtual function with a default body ("hidden feature")
    virtual double area() const = 0 {
        return 0.0; // default that derived classes can opt into via Shape::area()
    }

    // Pure virtual destructor — still needs a definition (see below)
    virtual ~Shape() = 0;
};

// Pure virtual destructor definition (required even though it's "pure")
Shape::~Shape() {
    std::cout << "~Shape\n";
}

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    ~Circle() override {
        std::cout << "~Circle\n";
    }

private:
    double radius;
};

class UnknownShape : public Shape {
public:
    double area() const override {
        // Explicitly calls the base class's default pure-virtual implementation
        return Shape::area();
    }

    ~UnknownShape() override {
        std::cout << "~UnknownShape\n";
    }
};

int main() {
    // Shape s;       // compile error: Shape is abstract

    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(2.0));
    shapes.push_back(new UnknownShape());

    for (Shape* s : shapes) {
        std::cout << "area = " << s->area() << '\n';
    }

    for (Shape* s : shapes) {
        delete s; // virtual destructor ensures correct cleanup
    }

    return 0;
}
