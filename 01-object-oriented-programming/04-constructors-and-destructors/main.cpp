#include <iostream>
#include <string>

class Person {
public:
    // Delegating constructors: avoid duplicating initialization logic
    Person() : Person("Unknown", 0) {
        std::cout << "Default constructor body\n";
    }

    Person(const std::string& name) : Person(name, 0) {
        std::cout << "Name-only constructor body\n";
    }

    Person(const std::string& name, int age) : name(name), age(age) {
        std::cout << "Constructing " << name << " (age " << age << ")\n";
    }

    ~Person() {
        std::cout << "Destroying " << name << '\n';
    }

    void introduce() const {
        std::cout << name << " is " << age << " years old\n";
    }

private:
    std::string name;
    int age;
};

int main() {
    {
        Person p1("Alice", 30);
        Person p2("Bob");      // delegates to Person(name, 0)
        Person p3;             // delegates to Person("Unknown", 0)

        p1.introduce();
        p2.introduce();
        p3.introduce();
    } // destructors run here, in reverse order of construction: p3, p2, p1

    std::cout << "End of main\n";
    return 0;
}
