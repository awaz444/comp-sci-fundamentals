#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printVector(const std::vector<int>& v) {
    for (int n : v) std::cout << n << ' ';
    std::cout << '\n';
}

int main() {
    // fill
    std::vector<int> v(5);
    std::fill(v.begin(), v.end(), 7);
    std::cout << "After fill(7): ";
    printVector(v);

    std::fill(v.begin(), v.begin() + 2, 0);
    std::cout << "After partial fill(0): ";
    printVector(v);

    // swap
    int a = 1, b = 2;
    std::swap(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << '\n';

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6, 7};
    std::swap(v1, v2); // O(1) — swaps internal representations
    std::cout << "v1: "; printVector(v1);
    std::cout << "v2: "; printVector(v2);

    // reverse
    std::vector<int> nums = {1, 2, 3, 4};
    std::reverse(nums.begin(), nums.end());
    std::cout << "Reversed nums: ";
    printVector(nums);

    std::string s = "hello";
    std::reverse(s.begin(), s.end());
    std::cout << "Reversed string: " << s << '\n';

    // unique: only removes CONSECUTIVE duplicates
    std::vector<int> dupes = {1, 1, 2, 2, 3, 1, 1};
    auto last = std::unique(dupes.begin(), dupes.end());
    dupes.erase(last, dupes.end());
    std::cout << "After unique (unsorted input): ";
    printVector(dupes); // {1, 2, 3, 1} - trailing 1 remains

    // To remove ALL duplicates, sort first
    std::vector<int> dupes2 = {1, 1, 2, 2, 3, 1, 1};
    std::sort(dupes2.begin(), dupes2.end());
    auto last2 = std::unique(dupes2.begin(), dupes2.end());
    dupes2.erase(last2, dupes2.end());
    std::cout << "After sort + unique: ";
    printVector(dupes2); // {1, 2, 3}

    return 0;
}
