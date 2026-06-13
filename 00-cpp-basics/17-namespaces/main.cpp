#include <iostream>

namespace math_utils {
    const double PI = 3.14159;

    int square(int x) {
        return x * x;
    }
}

namespace string_utils {
    // Same function name as another namespace — no collision
    int square(int x) {
        std::cout << "(string_utils::square called) ";
        return x * x;
    }
}

// Anonymous namespace: internal to this file only
namespace {
    int internalCounter = 0;
}

int main() {
    // Fully qualified access
    std::cout << "math_utils::square(5) = " << math_utils::square(5) << '\n';
    std::cout << "string_utils::square(5) = " << string_utils::square(5) << '\n';
    std::cout << "PI = " << math_utils::PI << '\n';

    // Targeted using declaration
    using math_utils::PI;
    std::cout << "PI via using declaration = " << PI << '\n';

    // Anonymous namespace member, accessible without qualification in this file
    internalCounter++;
    std::cout << "internalCounter = " << internalCounter << '\n';

    return 0;
}
