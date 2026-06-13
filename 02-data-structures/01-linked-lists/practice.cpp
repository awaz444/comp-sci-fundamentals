// Practice problems: Linked Lists
//
// 1. Merge k Sorted Lists          (LeetCode 23, Hard)
// 2. Reverse Nodes in k-Group      (LeetCode 25, Hard)
// 3. Linked List Cycle II          (LeetCode 142, Medium/Classic)
// 4. Copy List with Random Pointer (LeetCode 138, Medium)

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
};

// ------------------------------------------------------------
// Helpers for building/printing/freeing simple lists
// ------------------------------------------------------------
ListNode* buildList(const std::vector<int>& values) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : values) {
        ListNode* node = new ListNode(v);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << '\n';
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

// ============================================================
// 1. Merge k Sorted Lists (LeetCode 23, Hard)
//    Approach: min-heap of (value, node*), O(N log k)
// ============================================================
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> heap(cmp);

    for (ListNode* node : lists) {
        if (node) heap.push(node);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!heap.empty()) {
        ListNode* smallest = heap.top();
        heap.pop();
        tail->next = smallest;
        tail = tail->next;
        if (smallest->next) heap.push(smallest->next);
    }
    return dummy.next;
}

// ============================================================
// 2. Reverse Nodes in k-Group (LeetCode 25, Hard)
//    Approach: reverse each group of k iteratively, relink groups.
//    If fewer than k nodes remain, leave them unchanged.
// ============================================================
ListNode* reverseKGroup(ListNode* head, int k) {
    // Check there are at least k nodes left
    ListNode* node = head;
    for (int i = 0; i < k; i++) {
        if (!node) return head; // fewer than k nodes remain
        node = node->next;
    }

    // Reverse the first k nodes
    ListNode* prev = nullptr;
    ListNode* curr = head;
    for (int i = 0; i < k; i++) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // `curr` is the start of the remaining list (group k+1 onward).
    // Recursively reverse the rest and attach it to the tail of this group
    // (which is the original `head`, now at the end after reversal).
    head->next = reverseKGroup(curr, k);

    return prev; // new head of this reversed group
}

// ============================================================
// 3. Linked List Cycle II (LeetCode 142, Medium/Classic)
//    Approach: Floyd's tortoise and hare.
// ============================================================
ListNode* detectCycleStart(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Phase 1: detect whether a cycle exists
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Phase 2: find the cycle's start
            ListNode* ptr = head;
            while (ptr != slow) {
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr;
        }
    }
    return nullptr; // no cycle
}

// ============================================================
// 4. Copy List with Random Pointer (LeetCode 138, Medium)
//    Approach: hash map original -> clone, built in one pass,
//    then a second pass wires up next/random on the clones.
// ============================================================
struct RandomListNode {
    int val;
    RandomListNode* next;
    RandomListNode* random;
    RandomListNode(int val) : val(val), next(nullptr), random(nullptr) {}
};

RandomListNode* copyRandomList(RandomListNode* head) {
    if (!head) return nullptr;

    std::unordered_map<RandomListNode*, RandomListNode*> clones;

    for (RandomListNode* node = head; node; node = node->next) {
        clones[node] = new RandomListNode(node->val);
    }

    for (RandomListNode* node = head; node; node = node->next) {
        clones[node]->next = clones[node->next];     // nullptr maps to nullptr
        clones[node]->random = clones[node->random]; // nullptr maps to nullptr
    }

    return clones[head];
}

int main() {
    // --- 1. Merge k Sorted Lists ---
    ListNode* l1 = buildList({1, 4, 5});
    ListNode* l2 = buildList({1, 3, 4});
    ListNode* l3 = buildList({2, 6});
    std::vector<ListNode*> lists = {l1, l2, l3};

    ListNode* merged = mergeKLists(lists);
    std::cout << "Merged k sorted lists: ";
    printList(merged); // 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
    freeList(merged);

    // --- 2. Reverse Nodes in k-Group ---
    ListNode* kgroup = buildList({1, 2, 3, 4, 5});
    kgroup = reverseKGroup(kgroup, 2);
    std::cout << "Reverse in groups of 2: ";
    printList(kgroup); // 2 -> 1 -> 4 -> 3 -> 5
    freeList(kgroup);

    kgroup = buildList({1, 2, 3, 4, 5});
    kgroup = reverseKGroup(kgroup, 3);
    std::cout << "Reverse in groups of 3: ";
    printList(kgroup); // 3 -> 2 -> 1 -> 4 -> 5
    freeList(kgroup);

    // --- 3. Linked List Cycle II ---
    ListNode* cyc = buildList({3, 2, 0, -4});
    // Create a cycle: tail (-4) points back to node with value 2 (index 1)
    ListNode* tail = cyc;
    while (tail->next) tail = tail->next;
    ListNode* cycleEntry = cyc->next; // value 2
    tail->next = cycleEntry;

    ListNode* start = detectCycleStart(cyc);
    std::cout << "Cycle starts at node with value: "
              << (start ? std::to_string(start->val) : "no cycle") << '\n'; // 2

    // Break the cycle before freeing memory
    tail->next = nullptr;
    freeList(cyc);

    // --- 4. Copy List with Random Pointer ---
    RandomListNode* a = new RandomListNode(1);
    RandomListNode* b = new RandomListNode(2);
    RandomListNode* c = new RandomListNode(3);
    a->next = b; b->next = c;
    a->random = c; b->random = b; c->random = a;

    RandomListNode* copyHead = copyRandomList(a);
    std::cout << "Copied list values: ";
    for (RandomListNode* n = copyHead; n; n = n->next) std::cout << n->val << ' ';
    std::cout << '\n'; // 1 2 3
    std::cout << "Copy is a distinct deep copy: " << std::boolalpha << (copyHead != a) << '\n'; // true
    std::cout << "copyHead->random->val (should be 3): " << copyHead->random->val << '\n';

    // Free original and copy
    for (RandomListNode* n = a; n;) { RandomListNode* next = n->next; delete n; n = next; }
    for (RandomListNode* n = copyHead; n;) { RandomListNode* next = n->next; delete n; n = next; }

    return 0;
}
