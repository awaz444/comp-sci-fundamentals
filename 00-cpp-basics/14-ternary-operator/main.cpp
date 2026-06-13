#include <iostream>
#include <string>

int main() {
    // Basic ternary
    int a = 5, b = 10;
    int maxVal = (a > b) ? a : b;
    std::cout << "max = " << maxVal << '\n';

    // Chained ternary
    int score = 85;
    std::string category = (score >= 90) ? "A"
                          : (score >= 80) ? "B"
                          : "C";
    std::cout << "category = " << category << '\n';

    // Ternary as an lvalue: choose which variable to assign to
    bool useA = true;
    (useA ? a : b) = 100;
    std::cout << "a = " << a << ", b = " << b << '\n'; // a becomes 100

    useA = false;
    (useA ? a : b) = 200;
    std::cout << "a = " << a << ", b = " << b << '\n'; // b becomes 200

    return 0;
}
