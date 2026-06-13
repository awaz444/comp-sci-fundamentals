#include <iostream>
#include <limits>
#include <string>

int main() {
    // Basic input
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;

    // Leftover '\n' from the line above will mess up getline unless ignored
    std::cin.ignore();

    // Reading a full line (with spaces)
    std::string fullName;
    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Hello " << fullName << ", you are " << age << " years old.\n";

    // Robust numeric input with error recovery
    int number;
    std::cout << "Enter a number: ";
    while (!(std::cin >> number)) {
        std::cout << "Invalid input. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "You entered: " << number << '\n';

    return 0;
}
