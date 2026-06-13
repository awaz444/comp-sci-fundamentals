#include <iostream>
#include <stdexcept>

// ============================================================
// Array-based Queue (circular buffer)
// ============================================================
class ArrayQueue {
public:
    explicit ArrayQueue(int capacity)
        : capacity(capacity), front(0), back(-1), count(0) {
        data = new int[capacity];
    }
    ~ArrayQueue() { delete[] data; }

    void enqueue(int value) {
        if (count == capacity) throw std::overflow_error("Queue is full");
        back = (back + 1) % capacity;
        data[back] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue is empty");
        int value = data[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    int peekFront() const {
        if (isEmpty()) throw std::underflow_error("Queue is empty");
        return data[front];
    }

    bool isEmpty() const { return count == 0; }

private:
    int* data;
    int capacity;
    int front;
    int back;
    int count;
};

// ============================================================
// Linked-list-based Queue
// ============================================================
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

class LinkedListQueue {
public:
    ~LinkedListQueue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(int value) {
        Node* node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    int dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue is empty");
        Node* node = head;
        int value = node->data;
        head = head->next;
        if (!head) tail = nullptr; // queue became empty
        delete node;
        return value;
    }

    int peekFront() const {
        if (isEmpty()) throw std::underflow_error("Queue is empty");
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
};

int main() {
    // Array-based queue (circular buffer)
    ArrayQueue arrQueue(3);
    arrQueue.enqueue(1);
    arrQueue.enqueue(2);
    arrQueue.enqueue(3);
    std::cout << "ArrayQueue front: " << arrQueue.peekFront() << '\n'; // 1
    std::cout << "ArrayQueue dequeue: " << arrQueue.dequeue() << '\n'; // 1

    // Now there's room again thanks to the circular buffer
    arrQueue.enqueue(4);
    std::cout << "After enqueue(4), front: " << arrQueue.peekFront() << '\n'; // 2
    while (!arrQueue.isEmpty()) {
        std::cout << "dequeue: " << arrQueue.dequeue() << '\n'; // 2, 3, 4
    }

    // Linked-list-based queue
    LinkedListQueue llQueue;
    llQueue.enqueue(10);
    llQueue.enqueue(20);
    llQueue.enqueue(30);
    std::cout << "\nLinkedListQueue front: " << llQueue.peekFront() << '\n'; // 10
    while (!llQueue.isEmpty()) {
        std::cout << "dequeue: " << llQueue.dequeue() << '\n'; // 10, 20, 30
    }

    return 0;
}
