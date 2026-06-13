#include <iostream>

// ============================================================
// Singly Linked List
// ============================================================
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

class SinglyLinkedList {
public:
    ~SinglyLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Insert at the beginning - O(1)
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert at the nth position (0-indexed) - O(n)
    void insertAtNth(int value, int n) {
        if (n == 0) {
            insertAtBeginning(value);
            return;
        }
        Node* prev = head;
        for (int i = 0; i < n - 1 && prev; i++) prev = prev->next;
        if (!prev) return; // position out of range

        Node* newNode = new Node(value);
        newNode->next = prev->next;
        prev->next = newNode;
    }

    // Delete the node at the nth position (0-indexed) - O(n)
    void deleteAtNth(int n) {
        if (!head) return;

        if (n == 0) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node* prev = head;
        for (int i = 0; i < n - 1 && prev->next; i++) prev = prev->next;
        if (!prev->next) return; // position out of range

        Node* toDelete = prev->next;
        prev->next = toDelete->next;
        delete toDelete;
    }

    // Reverse the list iteratively - O(n), O(1) extra space
    void reverseIterative() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // Reverse the list recursively - O(n)
    void reverseRecursive() {
        head = reverseRecursiveHelper(head);
    }

    void printForward() const {
        printForwardHelper(head);
        std::cout << '\n';
    }

    void printBackward() const {
        printBackwardHelper(head);
        std::cout << '\n';
    }

    void print() const {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }

private:
    Node* head = nullptr;

    static Node* reverseRecursiveHelper(Node* node) {
        if (!node || !node->next) return node;
        Node* newHead = reverseRecursiveHelper(node->next);
        node->next->next = node;
        node->next = nullptr;
        return newHead;
    }

    static void printForwardHelper(Node* node) {
        if (!node) return;
        std::cout << node->data << ' ';
        printForwardHelper(node->next);
    }

    static void printBackwardHelper(Node* node) {
        if (!node) return;
        printBackwardHelper(node->next);
        std::cout << node->data << ' ';
    }
};

// ============================================================
// Doubly Linked List
// ============================================================
struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    ~DoublyLinkedList() {
        DNode* curr = head;
        while (curr) {
            DNode* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void pushBack(int value) {
        DNode* newNode = new DNode(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void printForward() const {
        DNode* curr = head;
        while (curr) {
            std::cout << curr->data << " <-> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }

    void printBackward() const {
        DNode* curr = tail;
        while (curr) {
            std::cout << curr->data << " <-> ";
            curr = curr->prev;
        }
        std::cout << "nullptr\n";
    }

private:
    DNode* head = nullptr;
    DNode* tail = nullptr;
};

int main() {
    // --- Singly Linked List ---
    SinglyLinkedList list;
    list.insertAtBeginning(3);
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);
    std::cout << "After inserting 1,2,3 at beginning: ";
    list.print(); // 1 -> 2 -> 3 -> nullptr

    list.insertAtNth(10, 1);
    std::cout << "After inserting 10 at position 1: ";
    list.print(); // 1 -> 10 -> 2 -> 3 -> nullptr

    list.deleteAtNth(1);
    std::cout << "After deleting position 1: ";
    list.print(); // 1 -> 2 -> 3 -> nullptr

    std::cout << "Print forward (recursive):  ";
    list.printForward(); // 1 2 3

    std::cout << "Print backward (recursive): ";
    list.printBackward(); // 3 2 1

    list.reverseIterative();
    std::cout << "After iterative reverse: ";
    list.print(); // 3 -> 2 -> 1 -> nullptr

    list.reverseRecursive();
    std::cout << "After recursive reverse:  ";
    list.print(); // 1 -> 2 -> 3 -> nullptr

    // --- Doubly Linked List ---
    DoublyLinkedList dlist;
    dlist.pushBack(1);
    dlist.pushBack(2);
    dlist.pushBack(3);

    std::cout << "\nDoubly linked list forward:  ";
    dlist.printForward(); // 1 <-> 2 <-> 3 <-> nullptr

    std::cout << "Doubly linked list backward: ";
    dlist.printBackward(); // 3 <-> 2 <-> 1 <-> nullptr

    return 0;
}
