#include <iostream>

// Double List
template <typename T>
class List {
protected:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d, Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;

private:
    void clear() {
        while (head) {
            Node* cur = head;
            head = head->next;
            delete cur;
        }
        tail = nullptr;
    }

    void copyFrom(const List& other) {
        for (Node* p = other.head; p; p = p->next)
            push_back(p->data);
    }

public:
    // Rule of 5
    List() = default;
    List(const List& o) { copyFrom(o); }
    List(List&& o) noexcept : head(o.head), tail(o.tail) { o.head = o.tail = nullptr; }
    List& operator=(const List& o) {
        if (this != &o) {
            clear();
            copyFrom(o);
        }
        return *this;
    }
    List& operator=(List&& o) noexcept {
        if (this != &o) {
            clear();
            head = o.head; tail = o.tail;
            o.head = o.tail = nullptr;
        }
        return *this;
    }
    ~List() { clear(); }

    bool empty() const { return head == nullptr; }
    void push_front(const T& x) {
        head = new Node(x, nullptr, head);
        if (head->next) head->next->prev = head;
        else             tail = head;
    }
    void push_back(const T& x) {
        Node* n = new Node(x, tail, nullptr);
        if (tail) tail->next = n;
        else      head = n;
        tail = n;
    }
    void pop_front() {
        if (!head) return;
        Node* n = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else      tail = nullptr;
        delete n;
    }
    void pop_back() {
        if (!tail) return;
        Node* n = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else      head = nullptr;
        delete n;
    }
    T front() const { return head->data; }
    T back()  const { return tail->data; }

    template <typename Func>
    void traverse(Func doIt) const {
        for (Node* p = head; p; p = p->next)
            doIt(p->data);
    }
};

// Bag
template <typename T>
class Bag {
private:
    List<T> items;
public:
    void add(const T& x) {
        items.push_back(x);
    }
    bool remove(const T& x) {
        bool found = false;
        List<T> temp;
        items.traverse([&](const T& v) {
            if (!found && v == x) found = true;
            else                  temp.push_back(v);
            });
        items = std::move(temp);
        return found;
    }
    void show() const {
        items.traverse([](const T& v) { std::cout << v << ' '; });
        std::cout << '\n';
    }
};

// Circular List
template <typename T>
class CircularList : public List<T> {
public:
    void traverse_circular(const T& startVal, void (*doIt)(const T&)) const {
        if (this->empty()) return;
        auto* p = this->head;
        while (p && p->data != startVal) p = p->next;
        if (!p) return;
        auto* cur = p;
        do {
            doIt(cur->data);
            cur = cur->next ? cur->next : this->head;
        } while (cur != p);
    }
};

// Test
void printInt(const int& x) { std::cout << x << ' '; }

int main() {
    // List Check
    List<int> L;
    L.push_back(1); L.push_back(2); L.push_back(3);
    std::cout << "List: ";
    L.traverse(printInt);
    std::cout << "\nFront/Back: " << L.front() << ", " << L.back() << "\n\n";

    // Bag Check
    Bag<int> B;
    B.add(5); B.add(7); B.add(5);
    std::cout << "Bag before remove: "; B.show();
    B.remove(5);
    std::cout << "Bag after remove 5: ";  B.show();
    std::cout << '\n';

    // Circular Check
    CircularList<int> C;
    C.push_back(10); C.push_back(20); C.push_back(30);
    std::cout << "Circular from 20: ";
    C.traverse_circular(20, printInt);
    std::cout << "\n";

    return 0;
}
