#include <iostream>
#include <string>

class Example {
public:
    // const and reference members MUST be set via the initializer list
    Example(int val, int& ref, std::string label)
        : CONST_VAL(val), refMember(ref), label(label) {
    }

    void show() const {
        std::cout << "CONST_VAL=" << CONST_VAL
                  << ", refMember=" << refMember
                  << ", label=" << label << '\n';
    }

private:
    const int CONST_VAL; // must be initialized, never reassigned
    int& refMember;       // must be bound at construction
    std::string label;    // initialized directly, avoiding default-construct + assign
};

class Inefficient {
public:
    // Anti-pattern: default-constructs 'name' (empty string), then assigns
    Inefficient(std::string n) {
        name = n;
    }
private:
    std::string name;
};

class Efficient {
public:
    // Preferred: 'name' is constructed directly with its final value
    Efficient(std::string n) : name(std::move(n)) {}
private:
    std::string name;
};

int main() {
    int x = 42;
    Example ex(10, x, "demo");
    ex.show();

    x = 100; // refMember inside ex reflects this change too
    ex.show();

    Inefficient a("Alice");
    Efficient b("Bob");

    return 0;
}
