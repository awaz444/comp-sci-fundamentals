#include <iostream>
#include <string>

// Pass by reference: modifies the caller's variable
void doubleIt(int& x) {
    x *= 2;
}

// const reference: efficient, read-only
void printName(const std::string& name) {
    std::cout << "Name: " << name << '\n';
}

int main() {
    int x = 10;
    int& ref = x; // ref is an alias for x

    ref = 20;
    std::cout << "x = " << x << '\n'; // 20, since ref IS x

    // Reference used as a function parameter
    doubleIt(x);
    std::cout << "x after doubleIt = " << x << '\n'; // 40

    // "Reassigning" a reference doesn't rebind it — it assigns through it
    int y = 99;
    ref = y; // this sets x to 99; ref still refers to x, not y
    std::cout << "x = " << x << ", y = " << y << '\n';

    printName("Alice");

    return 0;
}
