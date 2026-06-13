// Practice problems: Binary Trees
//
// 1. Serialize and Deserialize Binary Tree (LeetCode 297, Hard)
// 2. Binary Tree Maximum Path Sum          (LeetCode 124, Hard)
// 3. Vertical Order Traversal              (LeetCode 987, Hard)
// 4. Lowest Common Ancestor of a Binary Tree (LeetCode 236, Medium/Classic)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
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

// ============================================================
// 1. Serialize and Deserialize Binary Tree (LeetCode 297, Hard)
//    Approach: preorder traversal with "null" markers.
// ============================================================
void serializeHelper(TreeNode* node, std::ostringstream& out) {
    if (!node) {
        out << "null,";
        return;
    }
    out << node->val << ',';
    serializeHelper(node->left, out);
    serializeHelper(node->right, out);
}

std::string serialize(TreeNode* root) {
    std::ostringstream out;
    serializeHelper(root, out);
    return out.str();
}

TreeNode* deserializeHelper(std::vector<std::string>& tokens, size_t& pos) {
    const std::string& token = tokens[pos++];
    if (token == "null") return nullptr;

    TreeNode* node = new TreeNode(std::stoi(token));
    node->left = deserializeHelper(tokens, pos);
    node->right = deserializeHelper(tokens, pos);
    return node;
}

TreeNode* deserialize(const std::string& data) {
    std::vector<std::string> tokens;
    std::stringstream ss(data);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) tokens.push_back(token);
    }
    size_t pos = 0;
    return deserializeHelper(tokens, pos);
}

// ============================================================
// 2. Binary Tree Maximum Path Sum (LeetCode 124, Hard)
//    Approach: recursive helper returns best downward path sum
//    from a node (clamped to >= 0); track the global "bend" max.
// ============================================================
int maxPathSumHelper(TreeNode* node, int& globalMax) {
    if (!node) return 0;

    int left = std::max(maxPathSumHelper(node->left, globalMax), 0);
    int right = std::max(maxPathSumHelper(node->right, globalMax), 0);

    // Best path that "bends" through this node (candidate for global answer)
    globalMax = std::max(globalMax, node->val + left + right);

    // Best path extending downward through this node to its parent
    return node->val + std::max(left, right);
}

int maxPathSum(TreeNode* root) {
    int globalMax = INT_MIN;
    maxPathSumHelper(root, globalMax);
    return globalMax;
}

// ============================================================
// 3. Vertical Order Traversal (LeetCode 987, Hard)
//    Approach: DFS tracking (column, row, value); sort and group.
// ============================================================
void verticalOrderHelper(TreeNode* node, int col, int row,
                          std::vector<std::tuple<int,int,int>>& items) {
    if (!node) return;
    items.push_back({col, row, node->val});
    verticalOrderHelper(node->left, col - 1, row + 1, items);
    verticalOrderHelper(node->right, col + 1, row + 1, items);
}

std::vector<std::vector<int>> verticalOrder(TreeNode* root) {
    std::vector<std::tuple<int,int,int>> items; // (col, row, val)
    verticalOrderHelper(root, 0, 0, items);

    std::sort(items.begin(), items.end()); // sorts by col, then row, then val

    std::vector<std::vector<int>> result;
    int prevCol = INT_MIN;
    for (const auto& [col, row, val] : items) {
        if (col != prevCol) {
            result.push_back({});
            prevCol = col;
        }
        result.back().push_back(val);
    }
    return result;
}

// ============================================================
// 4. Lowest Common Ancestor of a Binary Tree (LeetCode 236)
//    Approach: recursive search; current node is LCA if both
//    subtrees report finding one of the targets.
// ============================================================
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root; // p and q found in different subtrees
    return left ? left : right;
}

int main() {
    // --- 1. Serialize / Deserialize ---
    //      1
    //     / \
    //    2   3
    //       / \
    //      4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    std::string data = serialize(root);
    std::cout << "Serialized: " << data << '\n';

    TreeNode* restored = deserialize(data);
    std::cout << "Re-serialized (should match): " << serialize(restored) << '\n';

    // --- 2. Binary Tree Maximum Path Sum ---
    //   -10
    //   /  \
    //  9    20
    //      /  \
    //     15   7
    TreeNode* mpRoot = new TreeNode(-10);
    mpRoot->left = new TreeNode(9);
    mpRoot->right = new TreeNode(20);
    mpRoot->right->left = new TreeNode(15);
    mpRoot->right->right = new TreeNode(7);
    std::cout << "Max path sum: " << maxPathSum(mpRoot) << '\n'; // 42 (15 + 20 + 7)

    // --- 3. Vertical Order Traversal ---
    auto columns = verticalOrder(root);
    std::cout << "Vertical order:\n";
    for (const auto& col : columns) {
        for (int v : col) std::cout << v << ' ';
        std::cout << '\n';
    }
    // Expected columns (left to right): [2], [1, 4], [3, 5] -- wait, 5 is col+1
    // Tree layout: 1(col0), 2(col-1), 3(col1), 4(col0,row2), 5(col2,row2)
    // col -1: [2]; col 0: [1, 4]; col 1: [3]; col 2: [5]

    // --- 4. Lowest Common Ancestor ---
    TreeNode* p = root->left;              // node 2
    TreeNode* q = root->right->left;       // node 4
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    std::cout << "LCA(2, 4) = " << lca->val << '\n'; // 1

    TreeNode* p2 = root->right->left;  // node 4
    TreeNode* q2 = root->right->right; // node 5
    TreeNode* lca2 = lowestCommonAncestor(root, p2, q2);
    std::cout << "LCA(4, 5) = " << lca2->val << '\n'; // 3

    deleteTree(root);
    deleteTree(restored);
    deleteTree(mpRoot);

    return 0;
}
