// Practice problems: Binary Search Trees
//
// 1. Recover Binary Search Tree         (LeetCode 99, Hard)
// 2. Kth Smallest Element in a BST       (LeetCode 230, Medium/Classic)
// 3. BST Iterator                       (LeetCode 173, Medium/Classic)
// 4. Construct BST from Preorder Traversal (LeetCode 1008, Hard)

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void printInorder(TreeNode* node) {
    if (!node) return;
    printInorder(node->left);
    std::cout << node->val << ' ';
    printInorder(node->right);
}

// ============================================================
// 1. Recover Binary Search Tree (LeetCode 99, Hard)
//    Approach: inorder traversal; track the previous node and
//    record the two nodes that violate sorted order.
// ============================================================
void recoverTreeHelper(TreeNode* node, TreeNode*& prev, TreeNode*& first, TreeNode*& second) {
    if (!node) return;

    recoverTreeHelper(node->left, prev, first, second);

    if (prev && prev->val > node->val) {
        if (!first) {
            first = prev;
            second = node;
        } else {
            second = node; // second violation: nodes are non-adjacent
        }
    }
    prev = node;

    recoverTreeHelper(node->right, prev, first, second);
}

void recoverTree(TreeNode* root) {
    TreeNode* prev = nullptr;
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    recoverTreeHelper(root, prev, first, second);
    if (first && second) std::swap(first->val, second->val);
}

// ============================================================
// 2. Kth Smallest Element in a BST (LeetCode 230)
//    Approach: iterative inorder traversal with an explicit stack.
// ============================================================
int kthSmallest(TreeNode* root, int k) {
    std::stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (true) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        if (--k == 0) return curr->val;
        curr = curr->right;
    }
}

// ============================================================
// 3. BST Iterator (LeetCode 173)
//    Approach: explicit stack initialized with the leftmost path.
// ============================================================
class BSTIterator {
public:
    explicit BSTIterator(TreeNode* root) {
        pushLeftPath(root);
    }

    int next() {
        TreeNode* node = stk.top();
        stk.pop();
        pushLeftPath(node->right);
        return node->val;
    }

    bool hasNext() const { return !stk.empty(); }

private:
    void pushLeftPath(TreeNode* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }

    std::stack<TreeNode*> stk;
};

// ============================================================
// 4. Construct BST from Preorder Traversal (LeetCode 1008, Hard)
//    Approach: recursive partitioning with (min, max) bounds.
// ============================================================
TreeNode* bstFromPreorderHelper(const std::vector<int>& preorder, size_t& idx, int bound) {
    if (idx == preorder.size() || preorder[idx] > bound) return nullptr;

    TreeNode* node = new TreeNode(preorder[idx++]);
    node->left = bstFromPreorderHelper(preorder, idx, node->val);
    node->right = bstFromPreorderHelper(preorder, idx, bound);
    return node;
}

TreeNode* bstFromPreorder(const std::vector<int>& preorder) {
    size_t idx = 0;
    return bstFromPreorderHelper(preorder, idx, INT_MAX);
}

int main() {
    // --- 1. Recover Binary Search Tree ---
    // Correct BST:    3        Swapped (1 and 3):    1
    //                / \                            / \
    //               1   4                          3   4
    // Build the "swapped" version directly:
    TreeNode* recRoot = new TreeNode(1);
    recRoot->left = new TreeNode(3);
    recRoot->right = new TreeNode(4);

    std::cout << "Before recovery (inorder): ";
    printInorder(recRoot);
    std::cout << '\n'; // 3 1 4 (not sorted)

    recoverTree(recRoot);

    std::cout << "After recovery (inorder):  ";
    printInorder(recRoot);
    std::cout << '\n'; // 1 3 4 (sorted)

    // --- 2. Kth Smallest Element in a BST ---
    //        5
    //       / \
    //      3   6
    //     / \
    //    2   4
    //   /
    //  1
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->left->left->left = new TreeNode(1);

    std::cout << "3rd smallest: " << kthSmallest(root, 3) << '\n'; // 3
    std::cout << "1st smallest: " << kthSmallest(root, 1) << '\n'; // 1

    // --- 3. BST Iterator ---
    BSTIterator it(root);
    std::cout << "BSTIterator order: ";
    while (it.hasNext()) std::cout << it.next() << ' ';
    std::cout << '\n'; // 1 2 3 4 5 6

    // --- 4. Construct BST from Preorder Traversal ---
    std::vector<int> preorder = {8, 5, 1, 7, 10, 12};
    TreeNode* built = bstFromPreorder(preorder);
    std::cout << "Built BST inorder (sorted): ";
    printInorder(built);
    std::cout << '\n'; // 1 5 7 8 10 12

    deleteTree(recRoot);
    deleteTree(root);
    deleteTree(built);

    return 0;
}
