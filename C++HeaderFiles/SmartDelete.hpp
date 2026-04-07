#pragma once
#include <memory>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;
        bool deleted;

        Node(T d) : data(d), deleted(false) {}
    };
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;
    int deletedCount = 0;
    int notDeletedCount = 0;
    void cleanupDeleted() {
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            if (curr->deleted) {
                auto prevNode = curr->prev.lock();
                if (prevNode) prevNode->next = curr->next;
                else head = curr->next;

                if (curr->next) curr->next->prev = curr->prev;
                else tail = prevNode;

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
        auto curr = rhs.head;
        while (curr) {
            if (!curr->deleted)
                push_back(curr->data);
            curr = curr->next;
        }
    }
    ~List() = default;
    bool empty() {
        return notDeletedCount == 0;
    }
    void push_front(T data) {
        auto n = std::make_shared<Node>(data);
        n->next = head;
        if (head) head->prev = n;
        else tail = n;
        head = n;
        notDeletedCount++;
    }
    void push_back(T data) {
        auto n = std::make_shared<Node>(data);
        n->prev = tail;
        if (tail) tail->next = n;
        else head = n;
        tail = n;
        notDeletedCount++;
    }
    T front() {
        auto curr = head;
        while (curr && curr->deleted) curr = curr->next;
        if (!curr) throw "No items";
        return curr->data;
    }
    T back() {
        auto curr = tail;
        while (curr && curr->deleted) curr = curr->prev.lock();
        if (!curr) throw "No items";
        return curr->data;
    }
    void pop_front() {
        auto curr = head;
        while (curr && curr->deleted) curr = curr->next;
        if (!curr) return;

        curr->deleted = true;
        deletedCount++;
        notDeletedCount--;
        checkCleanup();
    }
    void pop_back() {
        auto curr = tail;
        while (curr && curr->deleted) curr = curr->prev.lock();
        if (!curr) return;

        curr->deleted = true;
        deletedCount++;
        notDeletedCount--;
        checkCleanup();
    }
    void traverse(void (*doIt)(T)) {
        auto curr = head;
        while (curr) {
            if (!curr->deleted)
                doIt(curr->data);
            curr = curr->next;
        }
    }
};