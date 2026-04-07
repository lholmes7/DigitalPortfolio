#pragma once 

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        bool deleted;

        Node(T d, Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n), deleted(false) {
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int deletedCount = 0;
    int notDeletedCount = 0;

    void cleanupDeleted() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            if (curr->deleted) {
                if (curr->prev) curr->prev->next = curr->next;
                else head = curr->next;

                if (curr->next) curr->next->prev = curr->prev;
                else tail = curr->prev;

                delete curr;
                deletedCount--;
            }
            curr = next;
        }
    }

    void checkCleanup() {
        if (deletedCount >= notDeletedCount)
            cleanupDeleted();
    }

public:
    List() = default;

    List(T newData) {
        push_back(newData);
    }

    List(const List& rhs) {
        Node* curr = rhs.head;
        while (curr) {
            if (!curr->deleted)
                push_back(curr->data);
            curr = curr->next;
        }
    }

    ~List() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    bool empty() {
        return notDeletedCount == 0;
    }

    void push_front(T data) {
        Node* n = new Node(data, nullptr, head);
        if (head) head->prev = n;
        else tail = n;
        head = n;
        notDeletedCount++;
    }

    void push_back(T data) {
        Node* n = new Node(data, tail, nullptr);
        if (tail) tail->next = n;
        else head = n;
        tail = n;
        notDeletedCount++;
    }

    T front() {
        Node* curr = head;
        while (curr && curr->deleted) curr = curr->next;
        if (!curr) throw "No items";
        return curr->data;
    }

    T back() {
        Node* curr = tail;
        while (curr && curr->deleted) curr = curr->prev;
        if (!curr) throw "No items";
        return curr->data;
    }

    void pop_front() {
        Node* curr = head;
        while (curr && curr->deleted) curr = curr->next;
        if (!curr) return;

        curr->deleted = true;
        deletedCount++;
        notDeletedCount--;
        checkCleanup();
    }

    void pop_back() {
        Node* curr = tail;
        while (curr && curr->deleted) curr = curr->prev;
        if (!curr) return;

        curr->deleted = true;
        deletedCount++;
        notDeletedCount--;
        checkCleanup();
    }

    void traverse(void (*doIt)(T)) {
        Node* curr = head;
        while (curr) {
            if (!curr->deleted)
                doIt(curr->data);
            curr = curr->next;
        }
    }
};