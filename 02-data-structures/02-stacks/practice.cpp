// Practice problems: Stacks
//
// 1. Largest Rectangle in Histogram (LeetCode 84, Hard)
// 2. Trapping Rain Water           (LeetCode 42, Hard)
// 3. Basic Calculator               (LeetCode 224, Hard)
// 4. Min Stack                      (LeetCode 155, Easy/Classic)

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <climits>

// ============================================================
// 1. Largest Rectangle in Histogram (LeetCode 84, Hard)
//    Approach: stack of indices with increasing bar heights.
// ============================================================
int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> indices; // indices of bars with increasing heights
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        // Use height 0 as a sentinel at the end to flush the stack
        int currHeight = (i == n) ? 0 : heights[i];

        while (!indices.empty() && heights[indices.top()] >= currHeight) {
            int height = heights[indices.top()];
            indices.pop();
            // width spans from the element below the popped one (exclusive)
            // to the current index (exclusive)
            int width = indices.empty() ? i : i - indices.top() - 1;
            maxArea = std::max(maxArea, height * width);
        }
        indices.push(i);
    }
    return maxArea;
}

// ============================================================
// 2. Trapping Rain Water (LeetCode 42, Hard)
//    Approach: stack of indices with decreasing heights.
// ============================================================
int trap(const std::vector<int>& height) {
    std::stack<int> indices;
    int water = 0;

    for (int i = 0; i < (int)height.size(); i++) {
        while (!indices.empty() && height[indices.top()] < height[i]) {
            int bottom = indices.top();
            indices.pop();
            if (indices.empty()) break; // no left wall

            int left = indices.top();
            int boundedHeight = std::min(height[left], height[i]) - height[bottom];
            int width = i - left - 1;
            water += boundedHeight * width;
        }
        indices.push(i);
    }
    return water;
}

// ============================================================
// 3. Basic Calculator (LeetCode 224, Hard)
//    Handles +, -, parentheses, and whitespace.
//    Approach: track running result/sign; use stacks to save
//    state across parentheses.
// ============================================================
int calculate(const std::string& s) {
    std::stack<int> results;
    std::stack<int> signs;

    int result = 0;
    int sign = 1;
    int num = 0;

    for (size_t i = 0; i <= s.size(); i++) {
        char c = (i < s.size()) ? s[i] : '\0';

        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '+' || c == '-' || c == '\0' || c == ')') {
            result += sign * num;
            num = 0;

            if (c == '+') sign = 1;
            else if (c == '-') sign = -1;
            else if (c == ')') {
                result *= signs.top(); signs.pop();
                result += results.top(); results.pop();
            }
        } else if (c == '(') {
            results.push(result);
            signs.push(sign);
            result = 0;
            sign = 1;
        }
        // ignore whitespace
    }
    return result;
}

// ============================================================
// 4. Min Stack (LeetCode 155, Easy/Classic)
//    Approach: a second stack tracks the running minimum.
// ============================================================
class MinStack {
public:
    void push(int value) {
        data.push(value);
        if (mins.empty()) mins.push(value);
        else mins.push(std::min(value, mins.top()));
    }

    void pop() {
        data.pop();
        mins.pop();
    }

    int top() const { return data.top(); }
    int getMin() const { return mins.top(); }

private:
    std::stack<int> data;
    std::stack<int> mins;
};

int main() {
    // --- 1. Largest Rectangle in Histogram ---
    std::vector<int> hist = {2, 1, 5, 6, 2, 3};
    std::cout << "Largest rectangle area: " << largestRectangleArea(hist) << '\n'; // 10

    // --- 2. Trapping Rain Water ---
    std::vector<int> elevation = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "Trapped rain water: " << trap(elevation) << '\n'; // 6

    // --- 3. Basic Calculator ---
    std::cout << "calculate(\"(1+(4+5+2)-3)+(6+8)\") = "
              << calculate("(1+(4+5+2)-3)+(6+8)") << '\n'; // 23
    std::cout << "calculate(\" 2-1 + 2 \") = " << calculate(" 2-1 + 2 ") << '\n'; // 3

    // --- 4. Min Stack ---
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    std::cout << "MinStack getMin: " << minStack.getMin() << '\n'; // -3
    minStack.pop();
    std::cout << "MinStack top: " << minStack.top() << '\n';       // 0
    std::cout << "MinStack getMin: " << minStack.getMin() << '\n'; // -2

    return 0;
}
