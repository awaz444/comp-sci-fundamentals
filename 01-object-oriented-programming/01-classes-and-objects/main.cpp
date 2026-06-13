#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    void introduce() const {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old.\n";
    }
};

// struct: members public by default, used here as a plain data aggregate
struct Point {
    int x;
    int y;
};

int main() {
    // Stack-allocated object
    Person alice;
    alice.name = "Alice";
    alice.age = 30;
    alice.introduce();

    // Heap-allocated object, accessed via pointer
    Person* bob = new Person();
    bob->name = "Bob";
    bob->age = 25;
    bob->introduce();
    delete bob;

    // struct usage
    Point p1{3, 4};
    std::cout << "Point: (" << p1.x << ", " << p1.y << ")\n";

    // sizeof reflects member variables, not member functions
    std::cout << "sizeof(Person) = " << sizeof(Person) << '\n';

    return 0;
}
