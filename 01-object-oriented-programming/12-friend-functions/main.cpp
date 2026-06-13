#include <iostream>

class Box {
public:
    Box(double w) : width(w) {}

    // Friend declaration: grants access to private members
    friend void printWidth(const Box& b);

private:
    double width;
};

// Defined as an ordinary free function (no Box:: prefix)
void printWidth(const Box& b) {
    std::cout << "Width: " << b.width << '\n'; // accesses private member
}

class Vector2D {
public:
    Vector2D(double x, double y) : x(x), y(y) {}

    // operator<< needs access to private x, y but can't be a member
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

private:
    double x, y;
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")"; // accesses private members via friendship
    return os;
}

// Friend class example
class Car {
    friend class Engine; // Engine can access Car's private members
public:
    Car() : horsepower(300) {}
    int getHorsepower() const { return horsepower; }
private:
    int horsepower;
};

class Engine {
public:
    void tune(Car& car) {
        car.horsepower += 50; // allowed because Engine is a friend of Car
    }
};

int main() {
    Box box(10.5);
    printWidth(box);

    Vector2D v(3, 4);
    std::cout << "v = " << v << '\n'; // uses friend operator<<

    Car car;
    Engine engine;
    engine.tune(car);
    std::cout << "Tuned horsepower: " << car.getHorsepower() << '\n';

    return 0;
}
