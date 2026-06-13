#include <iostream>
#include <vector>

int main() {
    // Classic for loop
    for (int i = 0; i < 5; i++) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Range-based for loop (read-only, by value since ints are cheap)
    for (int n : nums) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // Range-based for loop with reference to modify elements in place
    for (int& n : nums) {
        n *= 2;
    }
    for (const int& n : nums) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // Infinite for loop with break
    for (;;) {
        std::cout << "Runs once then breaks\n";
        break;
    }

    return 0;
}
