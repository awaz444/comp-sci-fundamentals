#include <iostream>

int main() {
    // Basic while loop
    int i = 0;
    while (i < 5) {
        std::cout << i << ' ';
        i++;
    }
    std::cout << '\n';

    // while loop with break and continue
    int n = 0;
    while (true) {
        n++;
        if (n % 2 == 0) {
            continue; // skip even numbers
        }
        if (n > 9) {
            break; // stop once we exceed 9
        }
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // do-while loop: body always runs at least once
    int choice;
    do {
        choice = 0; // simulate "user" choosing to quit immediately
        std::cout << "Menu shown once even though choice is 0\n";
    } while (choice != 0);

    return 0;
}
