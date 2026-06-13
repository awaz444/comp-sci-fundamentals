#include <iostream>
#include <queue>
#include <algorithm>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

// Recursively compute the height of the tree.
// Convention: empty tree has height -1, single node has height 0.
int height(TreeNode* node) {
    if (!node) return -1;
    return 1 + std::max(height(node->left), height(node->right));
}

// BFS: level-order traversal using a queue
void levelOrder(TreeNode* root) {
    if (!root) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        std::cout << node->data << ' ';
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    std::cout << '\n';
}

// DFS: preorder (root, left, right)
void preorder(TreeNode* node) {
    if (!node) return;
    std::cout << node->data << ' ';
    preorder(node->left);
    preorder(node->right);
}

// DFS: inorder (left, root, right)
void inorder(TreeNode* node) {
    if (!node) return;
    inorder(node->left);
    std::cout << node->data << ' ';
    inorder(node->right);
}

// DFS: postorder (left, right, root)
void postorder(TreeNode* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data << ' ';
}

void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    //        1
    //      /   \
    //     2     3
    //    / \   /
    //   4   5 6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    std::cout << "Height: " << height(root) << '\n'; // 2

    std::cout << "Level order:  ";
    levelOrder(root); // 1 2 3 4 5 6

    std::cout << "Preorder:     ";
    preorder(root);
    std::cout << '\n'; // 1 2 4 5 3 6

    std::cout << "Inorder:      ";
    inorder(root);
    std::cout << '\n'; // 4 2 5 1 6 3

    std::cout << "Postorder:    ";
    postorder(root);
    std::cout << '\n'; // 4 5 2 6 3 1

    deleteTree(root);
    return 0;
}
