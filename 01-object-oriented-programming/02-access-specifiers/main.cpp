#include <iostream>

class BankAccount {
public:
    // Public interface: controlled access to private data
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false; // insufficient funds
    }

    double getBalance() const {
        return balance;
    }

private:
    double balance = 0.0; // cannot be accessed directly from outside the class
};

class Person {
public:
    void setAge(int a) {
        if (a >= 0 && a <= 150) {
            age = a; // validation that direct field access couldn't enforce
        }
    }

    int getAge() const {
        return age;
    }

private:
    int age = 0;
};

int main() {
    BankAccount account;
    account.deposit(100);
    account.withdraw(30);
    // account.balance = 1000000; // would not compile: balance is private
    std::cout << "Balance: " << account.getBalance() << '\n';

    Person p;
    p.setAge(25);
    p.setAge(-5); // rejected by setter, age stays 25
    std::cout << "Age: " << p.getAge() << '\n';

    return 0;
}
