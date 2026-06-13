#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main() {
    // Basic queue (FIFO)
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "front = " << q.front() << ", back = " << q.back() << '\n';

    // pop() returns void — read front() before popping
    int removed = q.front();
    q.pop();
    std::cout << "popped = " << removed << ", new front = " << q.front() << '\n';

    while (!q.empty()) {
        std::cout << "popping " << q.front() << '\n';
        q.pop();
    }

    // priority_queue: max-heap by default
    std::priority_queue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(2);
    std::cout << "max-heap top = " << maxHeap.top() << '\n'; // 3

    // min-heap via std::greater
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(2);
    std::cout << "min-heap top = " << minHeap.top() << '\n'; // 1

    std::cout << "min-heap order: ";
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << ' ';
        minHeap.pop();
    }
    std::cout << '\n';

    return 0;
}
