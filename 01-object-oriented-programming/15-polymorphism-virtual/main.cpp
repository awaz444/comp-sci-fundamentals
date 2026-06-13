#include <iostream>

// Base class with virtual functions
class Animal {
public:
    Animal(const std::string& name) : name(name) {}

    // virtual: enables dynamic binding for derived overrides
    virtual void speak() const {
        std::cout << name << " makes a sound\n";
    }

    // virtual destructor: ensures derived destructors run when deleted via base pointer
    virtual ~Animal() {
        std::cout << "~Animal (" << name << ")\n";
    }

protected:
    std::string name;
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}

    void speak() const override { // override: compiler checks this matches a virtual base method
        std::cout << name << " says Woof!\n";
    }

    ~Dog() override {
        std::cout << "~Dog (" << name << ")\n";
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& name) : Animal(name) {}

    void speak() const override {
        std::cout << name << " says Meow!\n";
    }

    ~Cat() override {
        std::cout << "~Cat (" << name << ")\n";
    }
};

int main() {
    // Dynamic binding: speak() resolves based on actual object type at runtime
    Animal* animals[] = { new Dog("Rex"), new Cat("Whiskers") };

    for (Animal* a : animals) {
        a->speak(); // calls Dog::speak or Cat::speak, not Animal::speak
    }

    // Virtual destructor ensures correct cleanup through base pointers
    for (Animal* a : animals) {
        delete a; // prints derived destructor then base destructor
    }

    return 0;
}
