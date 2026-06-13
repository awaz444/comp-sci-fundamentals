#include <iostream>
#include <string>

class Point {
public:
    // Parameter shadows member name — 'this' disambiguates
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }

private:
    int x = 0;
    int y = 0;
};

// Method chaining via returning *this
class TextBuilder {
public:
    TextBuilder& append(const std::string& s) {
        text += s;
        return *this; // return reference to the current object
    }

    TextBuilder& appendLine(const std::string& s) {
        text += s + "\n";
        return *this;
    }

    std::string text;
};

int main() {
    Point p;
    p.setX(10);
    p.setY(20);
    p.print();

    // Method chaining
    TextBuilder tb;
    tb.append("Hello").append(", ").append("World!").appendLine("!");
    std::cout << tb.text;

    return 0;
}
