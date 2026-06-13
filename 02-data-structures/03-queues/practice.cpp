// Practice problems: Queues
//
// 1. Sliding Window Maximum       (LeetCode 239, Hard)
// 2. Implement Stack using Queues (LeetCode 225, Medium/Classic)
// 3. Implement Queue using Stacks (LeetCode 232, Medium/Classic)
// 4. First Unique Character in a Stream

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>

// ============================================================
// 1. Sliding Window Maximum (LeetCode 239, Hard)
//    Approach: monotonic deque of indices with decreasing values.
// ============================================================
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    std::deque<int> dq; // stores indices, values decreasing front-to-back
    std::vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove indices outside the window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // Remove smaller values from the back - they can't be the max anymore
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

// ============================================================
// 2. Implement Stack using Queues (LeetCode 225)
//    Approach: rotate the queue on push so the newest element is at front.
// ============================================================
class StackUsingQueues {
public:
    void push(int x) {
        q.push(x);
        // rotate: move everything before x to behind it
        for (size_t i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int value = q.front();
        q.pop();
        return value;
    }

    int top() const { return q.front(); }
    bool empty() const { return q.empty(); }

private:
    std::queue<int> q;
};

// ============================================================
// 3. Implement Queue using Stacks (LeetCode 232)
//    Approach: inStack for push, outStack for pop/peek (amortized O(1)).
// ============================================================
class QueueUsingStacks {
public:
    void push(int x) { inStack.push(x); }

    int pop() {
        moveIfNeeded();
        int value = outStack.top();
        outStack.pop();
        return value;
    }

    int peek() {
        moveIfNeeded();
        return outStack.top();
    }

    bool empty() const { return inStack.empty() && outStack.empty(); }

private:
    void moveIfNeeded() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }

    std::stack<int> inStack;
    std::stack<int> outStack;
};

// ============================================================
// 4. First Unique Character in a Stream
//    Approach: frequency map + queue of candidates.
// ============================================================
class FirstUniqueCharStream {
public:
    void add(char c) {
        counts[c]++;
        candidates.push(c);
        while (!candidates.empty() && counts[candidates.front()] > 1) {
            candidates.pop();
        }
    }

    // Returns the first character seen that currently has count == 1,
    // or '\0' if none exists.
    char firstUnique() const {
        return candidates.empty() ? '\0' : candidates.front();
    }

private:
    std::unordered_map<char, int> counts;
    std::queue<char> candidates;
};

int main() {
    // --- 1. Sliding Window Maximum ---
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<int> maxima = maxSlidingWindow(nums, 3);
    std::cout << "Sliding window maxima (k=3): ";
    for (int v : maxima) std::cout << v << ' ';
    std::cout << '\n'; // 3 3 5 5 6 7

    // --- 2. Implement Stack using Queues ---
    StackUsingQueues stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    std::cout << "StackUsingQueues top: " << stk.top() << '\n'; // 3
    std::cout << "StackUsingQueues pop: " << stk.pop() << '\n'; // 3
    std::cout << "StackUsingQueues top: " << stk.top() << '\n'; // 2

    // --- 3. Implement Queue using Stacks ---
    QueueUsingStacks q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout << "QueueUsingStacks peek: " << q.peek() << '\n'; // 1
    std::cout << "QueueUsingStacks pop:  " << q.pop() << '\n';  // 1
    std::cout << "QueueUsingStacks peek: " << q.peek() << '\n'; // 2

    // --- 4. First Unique Character in a Stream ---
    FirstUniqueCharStream stream;
    std::string s = "teeter";
    for (char c : s) {
        stream.add(c);
        char unique = stream.firstUnique();
        std::cout << "After '" << c << "': first unique = "
                  << (unique ? std::string(1, unique) : "none") << '\n';
    }
    // t -> 't'
    // e -> 't'
    // e -> 't'
    // t -> none (both t's seen twice)
    // e -> none
    // r -> 'r'

    return 0;
}
