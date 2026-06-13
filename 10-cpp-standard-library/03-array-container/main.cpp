#include <iostream>
#include <array>
#include <algorithm>
#include <stdexcept>

std::array<int, 3> makeArray() {
    return {10, 20, 30}; // returning by value works — unlike a C array
}

int main() {
    std::array<int, 5> arr = {5, 3, 1, 4, 2};

    // size() is known, unlike a decayed C array
    std::cout << "size = " << arr.size() << '\n';

    // front/back
    std::cout << "front = " << arr.front() << ", back = " << arr.back() << '\n';

    // Works with STL algorithms via begin()/end()
    std::sort(arr.begin(), arr.end());
    std::cout << "sorted: ";
    for (int x : arr) std::cout << x << ' ';
    std::cout << '\n';

    // Bounds-checked access with at()
    try {
        std::cout << arr.at(10) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught out_of_range: " << e.what() << '\n';
    }

    // fill
    arr.fill(0);
    std::cout << "after fill(0): ";
    for (int x : arr) std::cout << x << ' ';
    std::cout << '\n';

    // Can be returned from a function and assigned
    std::array<int, 3> returned = makeArray();
    std::cout << "returned: ";
    for (int x : returned) std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}
