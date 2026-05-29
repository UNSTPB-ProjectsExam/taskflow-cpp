#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* topNode;
    int sz;

public:
    Stack() : topNode(nullptr), sz(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
        sz++;
    }

    T pop() {
        T val = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        sz--;
        return val;
    }

    T top() const {
        return topNode->data;
    }

    bool isEmpty() const {
        return sz == 0;
    }

    int size() const {
        return sz;
    }

    // for displaying history 
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
        return Iterator(topNode);
    }
};

#endif
