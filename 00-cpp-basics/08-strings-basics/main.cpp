#include <iostream>
#include <string>
#include <algorithm>

int main() {
    // Declaration and basic access
    std::string name = "Alice";
    std::cout << "Length: " << name.length() << '\n';
    std::cout << "First char: " << name[0] << '\n';

    // Concatenation
    std::string greeting = "Hello, " + name + "!";
    greeting += " Welcome.";
    std::cout << greeting << '\n';

    // Comparison
    std::string a = "apple", b = "banana";
    std::cout << "a < b: " << (a < b) << '\n';

    // substr, find, erase
    std::string sentence = "The quick brown fox";
    std::cout << "substr(4, 5): " << sentence.substr(4, 5) << '\n'; // "quick"

    size_t pos = sentence.find("brown");
    if (pos != std::string::npos) {
        std::cout << "'brown' found at index " << pos << '\n';
    }

    sentence.erase(0, 4); // remove "The "
    std::cout << "After erase: " << sentence << '\n';

    // Reverse a string
    std::string rev = "hello";
    std::reverse(rev.begin(), rev.end());
    std::cout << "Reversed: " << rev << '\n';

    // String <-> number conversions
    int num = std::stoi("42");
    double d = std::stod("3.14");
    std::string numStr = std::to_string(123);
    std::cout << "stoi: " << num << ", stod: " << d << ", to_string: " << numStr << '\n';

    return 0;
}
