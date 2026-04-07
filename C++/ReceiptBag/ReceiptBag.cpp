#include <iostream>
#include <vector>

template <typename T>
class ReceiptBag {
private:
    std::vector<T> items;
    std::vector<int> receipts;
    int nextReceipt = 1;

public:
    int insert(const T& item) {
        items.push_back(item);
        receipts.push_back(nextReceipt);
        return nextReceipt++;
    }

    T remove(int receipt) {
        for (size_t i = 0; i < receipts.size(); ++i) {
            if (receipts[i] == receipt) {
                T removed = items[i];
                items.erase(items.begin() + i);
                receipts.erase(receipts.begin() + i);
                return removed;
            }
        }
        std::cout << "Cant find receipt\n";
        exit(1);
    }

    void print() const {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "Receipt #" << receipts[i] << ": " << items[i] << '\n';
        }
    }

    size_t getSize() const {
        return items.size();
    }
};

int main() {
    ReceiptBag<std::string> bag;

    int r1 = bag.insert("item 1");
    int r2 = bag.insert("item 2");
    int r3 = bag.insert("item 3");

    std::cout << "Bag contents:\n";
    bag.print();

    std::string removed = bag.remove(r2);
    std::cout << "\nRemoved item: " << r2 << ": " << removed << '\n';

    std::cout << "\nBag post removal:\n";
    bag.print();

    return 0;
}