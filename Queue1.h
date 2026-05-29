#ifndef QUEUE_H
#define QUEUE_H

// Used for the waiting tasks that means:FIFO

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    int sz;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), sz(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T val) {
        Node* newNode = new Node(val);
        if (backNode == nullptr) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        sz++;
    }

    T dequeue() {
        T val = frontNode->data;
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            backNode = nullptr;
        }
        delete temp;
        sz--;
        return val;
    }

    T front() const {
        return frontNode->data;
    }

    bool isEmpty() const {
        return sz == 0;
    }

    int size() const {
        return sz;
    }

 
    Node* getfront() const {
        return frontNode;
    }

 
    struct Iterator {
        Node* current;
        Iterator(Node* n) : current(n) {}
        bool hasNext() const { return current != nullptr; }
        T next() {
            T val = current->data;
            current = current->next;
            return val;
        }
    };

    Iterator iterator() const {
        return Iterator(frontNode);
    }
};

#endif
