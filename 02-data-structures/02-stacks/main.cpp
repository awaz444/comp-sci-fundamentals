#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

// ============================================================
// Array-based Stack
// ============================================================
class ArrayStack {
public:
    explicit ArrayStack(int capacity) : capacity(capacity), top(-1) {
        data = new int[capacity];
    }
    ~ArrayStack() { delete[] data; }

    void push(int value) {
        if (top == capacity - 1) throw std::overflow_error("Stack is full");
        data[++top] = value;
    }

    int pop() {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return data[top--];
    }

    int peek() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return data[top];
    }

    bool isEmpty() const { return top == -1; }

private:
    int* data;
    int capacity;
    int top;
};

// ============================================================
// Linked-list-based Stack
// ============================================================
struct Node {
    int data;
    Node* next;
    Node(int data, Node* next) : data(data), next(next) {}
};

class LinkedListStack {
public:
    ~LinkedListStack() {
        while (!isEmpty()) pop();
    }

    void push(int value) { top = new Node(value, top); }

    int pop() {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        Node* node = top;
        int value = node->data;
        top = node->next;
        delete node;
        return value;
    }

    int peek() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }

private:
    Node* top = nullptr;
};

// ============================================================
// Reverse a string using a stack
// ============================================================
std::string reverseString(const std::string& str) {
    std::stack<char> s;
    for (char c : str) s.push(c);

    std::string reversed;
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    return reversed;
}

// ============================================================
// Balanced parentheses check
// ============================================================
bool isBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) return false;
            char open = s.top();
            s.pop();
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) {
                return false;
            }
        }
    }
    return s.empty();
}

// ============================================================
// Evaluate a postfix expression, e.g. "2 3 4 * +"
// ============================================================
int evaluatePostfix(const std::string& expr) {
    std::stack<int> s;
    std::string token;

    auto applyOp = [](int a, int b, char op) -> int {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: throw std::invalid_argument("Unknown operator");
        }
    };

    for (size_t i = 0; i <= expr.size(); i++) {
        if (i == expr.size() || expr[i] == ' ') {
            if (!token.empty()) {
                s.push(std::stoi(token));
                token.clear();
            }
        } else if (isdigit(expr[i])) {
            token += expr[i];
        } else {
            // operator
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            s.push(applyOp(a, b, expr[i]));
        }
    }
    return s.top();
}

int main() {
    // Array-based stack
    ArrayStack arrStack(5);
    arrStack.push(1);
    arrStack.push(2);
    arrStack.push(3);
    std::cout << "ArrayStack top: " << arrStack.peek() << '\n'; // 3
    std::cout << "ArrayStack pop: " << arrStack.pop() << '\n';  // 3

    // Linked-list-based stack
    LinkedListStack llStack;
    llStack.push(10);
    llStack.push(20);
    std::cout << "LinkedListStack top: " << llStack.peek() << '\n'; // 20
    std::cout << "LinkedListStack pop: " << llStack.pop() << '\n';  // 20

    // Reverse a string using a stack
    std::cout << "Reversed 'hello': " << reverseString("hello") << '\n'; // olleh

    // Balanced parentheses
    std::cout << "isBalanced(\"{[()]}\") = " << std::boolalpha << isBalanced("{[()]}") << '\n'; // true
    std::cout << "isBalanced(\"{[(])}\") = " << std::boolalpha << isBalanced("{[(])}") << '\n'; // false

    // Evaluate postfix: 2 3 4 * + = 2 + (3*4) = 14
    std::cout << "evaluatePostfix(\"2 3 4 * +\") = " << evaluatePostfix("2 3 4 * +") << '\n';

    return 0;
}
