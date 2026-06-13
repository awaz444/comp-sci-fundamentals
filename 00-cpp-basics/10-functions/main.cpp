#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

// Pass by value: x is a copy, caller's variable is unaffected
void incrementByValue(int x) {
    x++;
}

// Pass by reference: modifies the caller's variable directly
void incrementByRef(int& x) {
    x++;
}

// Pass by const reference: avoids copying a large object, can't modify it
void printVector(const std::vector<int>& v) {
    for (int n : v) std::cout << n << ' ';
    std::cout << '\n';
}

// Default argument
void greet(const std::string& name, const std::string& greeting = "Hello") {
    std::cout << greeting << ", " << name << "!\n";
}

// Function overloading
int add(int a, int b) {
    return a + b;
}
double add(double a, double b) {
    return a + b;
}

// Returning multiple values via std::tuple
std::tuple<int, int> minMax(const std::vector<int>& v) {
    return {*std::min_element(v.begin(), v.end()),
            *std::max_element(v.begin(), v.end())};
}

int main(int argc, char* argv[]) {
    // Pass by value vs reference
    int n = 5;
    incrementByValue(n);
    std::cout << "After incrementByValue: " << n << '\n'; // still 5
    incrementByRef(n);
    std::cout << "After incrementByRef: " << n << '\n';   // 6

    // const reference
    std::vector<int> data = {3, 1, 4, 1, 5, 9};
    printVector(data);

    // Default arguments
    greet("Alice");
    greet("Bob", "Hi");

    // Overloading
    std::cout << "add(2, 3) = " << add(2, 3) << '\n';
    std::cout << "add(2.5, 3.5) = " << add(2.5, 3.5) << '\n';

    // Returning multiple values with structured bindings
    auto [lo, hi] = minMax(data);
    std::cout << "min = " << lo << ", max = " << hi << '\n';

    // Command line arguments
    std::cout << "Program received " << argc << " argument(s):\n";
    for (int i = 0; i < argc; i++) {
        std::cout << "  argv[" << i << "] = " << argv[i] << '\n';
    }

    return 0;
}
