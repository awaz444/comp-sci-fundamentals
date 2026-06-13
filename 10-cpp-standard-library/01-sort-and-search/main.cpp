#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void printVector(const std::vector<int>& v) {
    for (int n : v) std::cout << n << ' ';
    std::cout << '\n';
}

int main() {
    std::vector<int> v = {5, 2, 4, 1, 3, 2};

    // sort: ascending
    std::sort(v.begin(), v.end());
    std::cout << "Ascending: ";
    printVector(v);

    // sort: descending using std::greater
    std::sort(v.begin(), v.end(), std::greater<int>());
    std::cout << "Descending: ";
    printVector(v);

    // sort: custom lambda comparator (back to ascending)
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });

    // find
    auto it = std::find(v.begin(), v.end(), 3);
    if (it != v.end()) {
        std::cout << "Found 3 at index " << (it - v.begin()) << '\n';
    }

    // find_if: first even number
    auto evenIt = std::find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    if (evenIt != v.end()) {
        std::cout << "First even number: " << *evenIt << '\n';
    }

    // find_if_not: first odd number
    auto oddIt = std::find_if_not(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    if (oddIt != v.end()) {
        std::cout << "First odd number: " << *oddIt << '\n';
    }

    // count and count_if
    int countOf2 = std::count(v.begin(), v.end(), 2);
    int evenCount = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    std::cout << "Count of 2: " << countOf2 << '\n';
    std::cout << "Count of evens: " << evenCount << '\n';

    return 0;
}
