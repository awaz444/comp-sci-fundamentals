#include <iostream>
#include <iomanip>
#include <string>

int main() {
    // setw: field width (applies to next item only)
    std::cout << std::setw(10) << "Name" << std::setw(5) << "Age" << '\n';
    std::cout << std::setw(10) << "Alice" << std::setw(5) << 30 << '\n';
    std::cout << std::setw(10) << "Bob" << std::setw(5) << 25 << '\n';

    // setw with setfill and alignment
    std::cout << std::setfill('-') << std::left
              << std::setw(10) << "Name" << std::setw(5) << "Age" << '\n';
    std::cout << std::setfill(' '); // reset fill character

    // setprecision
    double pi = 3.14159265;
    std::cout << "Default precision: " << pi << '\n';
    std::cout << "setprecision(3): " << std::setprecision(3) << pi << '\n';
    std::cout << "fixed + setprecision(2): " << std::fixed << std::setprecision(2) << pi << '\n';

    // reset formatting flags before base demo
    std::cout.unsetf(std::ios::fixed);

    // setbase / hex / oct / dec
    int n = 255;
    std::cout << std::setbase(16) << n << '\n'; // ff
    std::cout << std::setbase(8)  << n << '\n'; // 377
    std::cout << std::setbase(10) << n << '\n'; // 255

    std::cout << std::showbase << std::hex << n << '\n'; // 0xff
    std::cout << std::dec; // reset to decimal

    return 0;
}
