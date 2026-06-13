#include <iostream>
#include <stdexcept>
#include <string>

// Custom exception type
class InvalidAgeException : public std::runtime_error {
public:
    explicit InvalidAgeException(const std::string& msg)
        : std::runtime_error(msg) {}
};

double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    return numerator / denominator;
}

void setAge(int age) {
    if (age < 0 || age > 150) {
        throw InvalidAgeException("Age must be between 0 and 150, got " + std::to_string(age));
    }
    std::cout << "Age set to " << age << '\n';
}

int main() {
    // Basic try/catch
    try {
        std::cout << divide(10, 2) << '\n';
        std::cout << divide(10, 0) << '\n';
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught runtime_error: " << e.what() << '\n';
    }

    // Custom exception type, caught via base class reference
    try {
        setAge(200);
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    // std::out_of_range from standard library
    try {
        std::string s = "hello";
        std::cout << s.at(10) << '\n'; // throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught out_of_range: " << e.what() << '\n';
    }

    // Catch-all
    try {
        throw 42; // not a std::exception subclass
    } catch (...) {
        std::cerr << "Caught unknown exception\n";
    }

    return 0;
}
