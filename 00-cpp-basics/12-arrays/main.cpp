#include <iostream>

// Function receiving a const array — guarantees it won't modify the contents
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

// Function that does modify the array
void doubleValues(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    // Declaration and initialization
    int nums[5] = {1, 2, 3, 4, 5};

    // sizeof trick works here because nums is still a real array
    int count = sizeof(nums) / sizeof(nums[0]);
    std::cout << "Element count: " << count << '\n';

    printArray(nums, count);
    doubleValues(nums, count);
    printArray(nums, count);

    // 2D array (row-major order)
    int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 3; c++) {
            std::cout << grid[r][c] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
