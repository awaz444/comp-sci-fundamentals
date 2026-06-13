#include <iostream>
#include <string>

// Base class
class Animal {
public:
    Animal(const std::string& name) : name(name) {
        std::cout << "Animal constructor: " << name << '\n';
    }
    ~Animal() {
        std::cout << "Animal destructor: " << name << '\n';
    }

    void eat() const {
        std::cout << name << " is eating\n";
    }

protected:
    std::string name; // accessible to derived classes
};

// Single inheritance with public access
class Dog : public Animal {
public:
    Dog(const std::string& name, const std::string& breed)
        : Animal(name), breed(breed) { // base constructor called explicitly
        std::cout << "Dog constructor: " << breed << '\n';
    }
    ~Dog() {
        std::cout << "Dog destructor: " << breed << '\n';
    }

    void bark() const {
        // 'name' is protected in Animal, accessible here
        std::cout << name << " says Woof!\n";
    }

private:
    std::string breed;
};

// Multilevel inheritance: Puppy -> Dog -> Animal
class Puppy : public Dog {
public:
    Puppy(const std::string& name, const std::string& breed)
        : Dog(name, breed) {}

    void play() const {
        std::cout << name << " is playing\n"; // 'name' accessible via Dog -> Animal
    }
};

// Multiple inheritance
class Swimmer {
public:
    void swim() const { std::cout << "Swimming\n"; }
};

class Flyer {
public:
    void fly() const { std::cout << "Flying\n"; }
};

class Duck : public Swimmer, public Flyer {
public:
    void quack() const { std::cout << "Quack!\n"; }
};

int main() {
    std::cout << "--- Single inheritance ---\n";
    {
        Dog d("Rex", "Labrador");
        d.eat();  // inherited from Animal
        d.bark(); // Dog's own method
    } // destruction order: Dog destructor, then Animal destructor

    std::cout << "\n--- Multilevel inheritance ---\n";
    {
        Puppy p("Buddy", "Poodle");
        p.eat();
        p.bark();
        p.play();
    }

    std::cout << "\n--- Multiple inheritance ---\n";
    {
        Duck duck;
        duck.swim(); // from Swimmer
        duck.fly();  // from Flyer
        duck.quack();
    }

    return 0;
}
