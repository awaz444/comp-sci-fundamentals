#include <iostream>

class Point {
public:
    // Default constructor required for array declarations without initializers
    Point(int x = 0, int y = 0) : x(x), y(y) {
        std::cout << "Constructing Point(" << x << ", " << y << ")\n";
    }

    int x, y;
};

int main() {
    // Array using default constructor for each element
    Point points[3];
    points[0].x = 1; points[0].y = 1;
    points[1].x = 2; points[1].y = 2;
    points[2].x = 3; points[2].y = 3;

    std::cout << "--- points ---\n";
    for (const auto& p : points) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    // Array with explicit initializers
    Point pts2[3] = {
        Point(1, 2),
        Point(3, 4),
        Point(5, 6)
    };

    std::cout << "--- pts2 ---\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "(" << pts2[i].x << ", " << pts2[i].y << ")\n";
    }

    // Dynamic array of objects
    Point* dynamicPoints = new Point[2]; // default constructor called twice
    delete[] dynamicPoints;

    return 0;
}
