# Trees & Binary Trees

A **tree** is a hierarchical structure of nodes where each node has a
value and pointers to **child** nodes. The topmost node is the **root**;
nodes with no children are **leaves**.

A **binary tree** restricts each node to at most two children, commonly
called `left` and `right`.

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};
```

## Height of a tree

The height of a node is the number of edges on the longest path from
that node down to a leaf. Computed recursively:

```cpp
int height(TreeNode* node) {
    if (!node) return -1; // height of empty tree = -1 (or 0, depending on convention)
    return 1 + std::max(height(node->left), height(node->right));
}
```

## Traversal strategies: BFS vs DFS

- **BFS (Breadth-First Search)** — visit nodes level by level, using a
  **queue**. Also called **level-order traversal**.
- **DFS (Depth-First Search)** — go as deep as possible before
  backtracking, using a **stack** (explicit or via recursion's call
  stack). DFS on binary trees comes in three flavors:
  - **Preorder**: root, left, right
  - **Inorder**: left, root, right
  - **Postorder**: left, right, root

## Level-order traversal (BFS)

```cpp
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
}
```

## Preorder, Inorder, Postorder (DFS, recursive)

```cpp
void preorder(TreeNode* node) {   // root, left, right
    if (!node) return;
    std::cout << node->data << ' ';
    preorder(node->left);
    preorder(node->right);
}

void inorder(TreeNode* node) {    // left, root, right
    if (!node) return;
    inorder(node->left);
    std::cout << node->data << ' ';
    inorder(node->right);
}

void postorder(TreeNode* node) {  // left, right, root
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data << ' ';
}
```

For a **binary search tree**, inorder traversal visits nodes in sorted
order — a fact used heavily in BST problems (see
[Binary Search Trees](../05-binary-search-trees/notes.md)).

## Key interview points

- BFS = queue, level by level; DFS = stack/recursion, depth first.
- Know all three DFS orderings and when each is useful:
  - **Preorder** — useful for copying/serializing a tree (root info
    comes first).
  - **Inorder** — gives sorted order for a BST.
  - **Postorder** — useful for deleting a tree (children before
    parent) or evaluating expression trees.
- Height/depth calculations and traversals are the building blocks for
  almost every tree interview question (balance checks, diameter,
  path sums, etc.).
- An empty tree has height -1 (or 0, by convention — be explicit about
  which convention you're using).

## Practice Problems (LeetCode)

See `practice.cpp` for full working solutions.

1. **[Hard] Serialize and Deserialize Binary Tree** (LeetCode 297) —
   Convert a tree to a string and back. Approach: preorder traversal,
   recording `"null"` for empty children, separated by commas. To
   deserialize, recursively consume tokens from the front of the
   serialized list in the same preorder order.

2. **[Hard] Binary Tree Maximum Path Sum** (LeetCode 124) — Find the
   maximum sum of any downward path (the path can start and end at any
   node, doesn't have to pass through the root). Approach: a recursive
   helper returns the best **single-direction** path sum extending
   downward from a node (clamped to >= 0, since a negative branch is
   never worth including). At each node, separately consider the "bend"
   path `left + node + right` for the global answer, but return only
   `node + max(left, right, 0)` to the parent.

3. **[Hard] Vertical Order Traversal** (LeetCode 987) — Group node
   values by their horizontal distance ("column") from the root, top to
   bottom, left to right, breaking ties by value. Approach: DFS or BFS
   tracking `(column, row, value)` for each node; sort by column, then
   row, then value, then group by column.

4. **[Medium/Classic] Lowest Common Ancestor of a Binary Tree**
   (LeetCode 236) — Find the LCA of two nodes in a general binary tree
   (not necessarily a BST). Approach: recursively search left and right
   subtrees; if both return non-null, the current node is the LCA;
   otherwise propagate up whichever side found a match.
