#include <iostream>

int main() {
    // if / else if / else
    int score = 85;
    char grade;
    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80) {
        grade = 'B';
    } else {
        grade = 'C';
    }
    std::cout << "Grade: " << grade << '\n';

    // Logical operators with short-circuiting
    int age = 25;
    bool hasLicense = true;
    if (age >= 18 && hasLicense) {
        std::cout << "Can drive\n";
    }

    // switch statement
    int day = 3;
    switch (day) {
        case 1:
            std::cout << "Monday\n";
            break;
        case 2:
            std::cout << "Tuesday\n";
            break;
        case 3:
            std::cout << "Wednesday\n";
            break;
        default:
            std::cout << "Some other day\n";
            break;
    }

    return 0;
}
