# Binary Search Trees (BSTs)

A **binary search tree** is a binary tree with the ordering property:
for every node, all values in its **left** subtree are less than the
node's value, and all values in its **right** subtree are greater.

This property makes search, insert, and delete O(log n) on a balanced
tree (O(n) worst case on a degenerate/skewed tree).

## Memory allocation: stack vs heap

- The `TreeNode` objects themselves are allocated on the **heap** via
  `new` — the tree persists beyond any single function call and has a
  size determined at runtime.
- Pointers/references to nodes (`TreeNode* curr`, function parameters)
  live on the **stack** — they're just local variables pointing at heap
  memory.
- Recursive functions (insert, search, traversals) each push a new stack
  frame; very deep/skewed trees can risk stack overflow on deep
  recursion — a consideration for production code.

## Insertion

Recursively (or iteratively) walk left/right based on comparisons until
finding an empty spot:

```cpp
TreeNode* insert(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    // duplicates ignored
    return node;
}
```

## Find min / max

The minimum is the **leftmost** node; the maximum is the **rightmost**
node — just follow `left`/`right` pointers until `nullptr`.

```cpp
TreeNode* findMin(TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}
```

## Checking if a binary tree is a valid BST

A common mistake is checking only `node->left->data < node->data <
node->right->data` locally — this misses violations from deeper
descendants. The correct approach passes down a valid `(min, max)`
range:

```cpp
bool isBST(TreeNode* node, long min, long max) {
    if (!node) return true;
    if (node->data <= min || node->data >= max) return false;
    return isBST(node->left, min, node->data) &&
           isBST(node->right, node->data, max);
}
```

## Deleting a node from a BST

Three cases:

1. **Leaf node** — simply remove it.
2. **One child** — replace the node with its child.
3. **Two children** — replace the node's value with its **inorder
   successor** (the minimum of the right subtree), then delete that
   successor from the right subtree.

```cpp
TreeNode* deleteNode(TreeNode* node, int value) {
    if (!node) return nullptr;
    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        // found the node to delete
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
        // two children: replace with inorder successor
        TreeNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }
    return node;
}
```

## Inorder Successor

The inorder successor of a node is the next value in sorted order:

- If the node has a right subtree, the successor is the **minimum of
  the right subtree**.
- Otherwise, it's the nearest ancestor for which the node is in the
  left subtree (requires walking from the root, tracking the last
  ancestor where you went left).

## Key interview points

- BST property must hold **globally**, not just for immediate children
  — always validate with a min/max range, not local comparisons.
- Deletion's two-children case (replace with inorder successor — or
  symmetric: inorder predecessor, the max of the left subtree) is the
  trickiest part — memorize it.
- Inorder traversal of a BST yields sorted order — this is the
  fundamental link between BSTs and sorting (see
  [Binary Trees](../04-binary-trees/notes.md)).
- Balanced BSTs (AVL, Red-Black trees) guarantee O(log n); a plain BST
  can degrade to a linked list (O(n)) if values are inserted in sorted
  order.

## Practice Problems (LeetCode)

See `practice.cpp` for full working solutions.

1. **[Hard] Recover Binary Search Tree** (LeetCode 99) — Exactly two
   nodes of a BST were swapped by mistake; fix the tree in-place
   without changing its structure. Approach: do an inorder traversal
   (which should be sorted); track the previous node, and whenever
   `prev->val > curr->val` is found, record the offending node(s). Two
   such violations mean two non-adjacent swapped nodes; one violation
   spanning consecutive nodes means they're adjacent. Swap the values
   of the two recorded nodes at the end. (Can be done in O(1) space
   with Morris traversal, or O(h) with a stack-based iterative inorder.)

2. **[Medium/Classic] Kth Smallest Element in a BST** (LeetCode 230) —
   Find the k-th smallest value. Approach: inorder traversal visits
   nodes in sorted order — stop after the k-th visited node. Use an
   iterative inorder traversal with an explicit stack to avoid
   recursion overhead and to allow early exit.

3. **[Medium/Classic] BST Iterator** (LeetCode 173) — Design an
   iterator over a BST that returns `next()` (the next smallest value)
   and `hasNext()` in O(1) amortized time and O(h) space. Approach:
   maintain an explicit stack initialized with the leftmost path from
   the root. `next()` pops a node, then pushes the leftmost path of its
   right subtree.

4. **[Hard] Construct BST from Preorder Traversal** (LeetCode 1008) —
   Given a preorder traversal of a BST, reconstruct the tree. Approach:
   recursively partition the array using a `(min, max)` bound — the
   first element is the root; everything less than it (up to the first
   element >= it) forms the left subtree, the rest forms the right
   subtree. O(n) using bounds, or O(n log n) with naive partitioning.
