#include <iostream>
#include <climits>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

// Insert a value into the BST, returning the (possibly new) root of this subtree.
TreeNode* insert(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    return node; // duplicates ignored
}

// Find the minimum value node (leftmost node)
TreeNode* findMin(TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

// Find the maximum value node (rightmost node)
TreeNode* findMax(TreeNode* node) {
    while (node->right) node = node->right;
    return node;
}

// Check whether a binary tree satisfies the BST property using a valid range
bool isBST(TreeNode* node, long minVal, long maxVal) {
    if (!node) return true;
    if (node->data <= minVal || node->data >= maxVal) return false;
    return isBST(node->left, minVal, node->data) &&
           isBST(node->right, node->data, maxVal);
}

// Delete a node with the given value from the BST
TreeNode* deleteNode(TreeNode* node, int value) {
    if (!node) return nullptr;

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        // two children: replace with inorder successor (min of right subtree)
        TreeNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }
    return node;
}

void inorder(TreeNode* node) {
    if (!node) return;
    inorder(node->left);
    std::cout << node->data << ' ';
    inorder(node->right);
}

void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    // Build a BST by inserting values:
    //        50
    //      /    \
    //    30      70
    //   /  \    /  \
    //  20  40  60  80
    TreeNode* root = nullptr;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) {
        root = insert(root, v);
    }

    std::cout << "Inorder (sorted): ";
    inorder(root);
    std::cout << '\n'; // 20 30 40 50 60 70 80

    std::cout << "Min: " << findMin(root)->data << '\n'; // 20
    std::cout << "Max: " << findMax(root)->data << '\n'; // 80

    std::cout << "isBST: " << std::boolalpha
              << isBST(root, LONG_MIN, LONG_MAX) << '\n'; // true

    // Delete a node with two children (30)
    root = deleteNode(root, 30);
    std::cout << "Inorder after deleting 30: ";
    inorder(root);
    std::cout << '\n'; // 20 40 50 60 70 80

    // Delete a leaf node (20)
    root = deleteNode(root, 20);
    std::cout << "Inorder after deleting 20: ";
    inorder(root);
    std::cout << '\n'; // 40 50 60 70 80

    deleteTree(root);
    return 0;
}
