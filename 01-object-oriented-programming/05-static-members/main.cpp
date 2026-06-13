#include <iostream>
#include <string>

class Employee {
public:
    Employee(const std::string& name) : name(name) {
        totalEmployees++; // shared across all instances
    }

    ~Employee() {
        totalEmployees--;
    }

    // Static member function: callable without an object, no 'this'
    static int getTotalEmployees() {
        return totalEmployees;
    }

private:
    std::string name;
    static int totalEmployees; // declaration only
};

// Definition + initialization of the static member (required exactly once)
int Employee::totalEmployees = 0;

int main() {
    std::cout << "Before creating employees: "
              << Employee::getTotalEmployees() << '\n';

    {
        Employee alice("Alice");
        Employee bob("Bob");

        // Accessible via class name (preferred) or via an instance
        std::cout << "During scope: " << Employee::getTotalEmployees() << '\n';
        std::cout << "Via instance: " << alice.getTotalEmployees() << '\n';
    } // destructors decrement totalEmployees

    std::cout << "After scope ends: " << Employee::getTotalEmployees() << '\n';

    return 0;
}
