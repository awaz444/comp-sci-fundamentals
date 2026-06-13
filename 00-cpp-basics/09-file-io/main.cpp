#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    const std::string filename = "data.txt";

    // Writing to a file (truncates if it exists)
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Line 1\n";
        outFile << "Line 2\n";
        outFile << "Line 3\n";
        outFile.close();
    }

    // Appending to a file
    std::ofstream appendFile(filename, std::ios::app);
    if (appendFile.is_open()) {
        appendFile << "Line 4 (appended)\n";
        appendFile.close();
    }

    // Reading a file line by line
    std::ifstream inFile(filename);
    std::string line;
    std::cout << "--- File contents ---\n";
    while (std::getline(inFile, line)) {
        std::cout << line << '\n';
    }
    inFile.close();

    // Write to a specific line by reading all lines, inserting, and rewriting
    std::vector<std::string> lines;
    std::ifstream readAll(filename);
    while (std::getline(readAll, line)) {
        lines.push_back(line);
    }
    readAll.close();

    size_t targetIndex = 1; // insert before "Line 2"
    lines.insert(lines.begin() + targetIndex, "Inserted Line");

    std::ofstream rewrite(filename); // truncates
    for (const auto& l : lines) {
        rewrite << l << '\n';
    }
    rewrite.close();

    std::cout << "--- After insert ---\n";
    std::ifstream finalRead(filename);
    while (std::getline(finalRead, line)) {
        std::cout << line << '\n';
    }

    return 0;
}
