#include <iostream>
#include <stack>
#include <string>

// Example use case: check for balanced parentheses using std::stack
bool isBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) return false;
            char top = s.top();
            s.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return s.empty();
}

int main() {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << "size = " << s.size() << '\n';
    std::cout << "top = " << s.top() << '\n';

    // pop() returns void — must read top() before popping
    int removed = s.top();
    s.pop();
    std::cout << "popped = " << removed << ", new top = " << s.top() << '\n';

    while (!s.empty()) {
        std::cout << "popping " << s.top() << '\n';
        s.pop();
    }
    std::cout << "empty = " << s.empty() << '\n';

    // Balanced parentheses example
    std::cout << "isBalanced('(a[b]{c})') = " << isBalanced("(a[b]{c})") << '\n';
    std::cout << "isBalanced('(a[b)]') = " << isBalanced("(a[b)]") << '\n';

    return 0;
}
