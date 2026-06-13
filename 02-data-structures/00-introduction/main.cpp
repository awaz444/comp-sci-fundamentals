#include <iostream>
#include <vector>
#include <list>
#include <chrono>

// Demonstrates the practical tradeoff: array (vector) vs linked list (list)
// for front-insertion vs random access.

int main() {
    const int N = 100000;

    // --- Random access: vector is O(1), list is O(n) ---
    std::vector<int> vec(N, 0);
    std::list<int> lst(N, 0);

    vec[N / 2] = 42; // O(1) direct access

    auto it = lst.begin();
    std::advance(it, N / 2); // O(n) traversal to reach the middle
    *it = 42;

    std::cout << "vec[N/2] = " << vec[N / 2] << '\n';
    std::cout << "*it (list middle) = " << *it << '\n';

    // --- Front insertion: list is O(1), vector is O(n) (must shift all elements) ---
    lst.push_front(-1);            // O(1)
    vec.insert(vec.begin(), -1);   // O(n) — every element shifts right

    std::cout << "lst.front() = " << lst.front() << '\n';
    std::cout << "vec.front() = " << vec.front() << '\n';

    // ADT idea: both support a "List" interface (ordered collection),
    // but their performance characteristics differ dramatically depending
    // on the access pattern.

    return 0;
}
