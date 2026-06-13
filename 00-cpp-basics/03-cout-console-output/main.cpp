#include <iostream>

int main() {
    // Basic output of different types
    std::cout << "Hello" << '\n';
    std::cout << 42 << '\n';
    std::cout << 3.14 << '\n';

    // Chaining multiple values
    int x = 5, y = 10;
    std::cout << "x = " << x << ", y = " << y << '\n';

    // '\n' vs std::endl
    std::cout << "Line without flush" << '\n';
    std::cout << "Line with flush" << std::endl;

    // std::cerr for error messages
    std::cerr << "This is an error message" << '\n';

    return 0;
}
