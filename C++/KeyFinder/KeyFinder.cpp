#include <iostream>
#include <string>
#include <cassert>

template <class RecordType>
class Table {
public:
    static const std::size_t CAPACITY = 16; 

    Table() : used(0) {
        for (std::size_t i = 0; i < CAPACITY; ++i) {
            data[i].key = NEVERUSED;
        }
    }

    void insert(const RecordType& record) {
        bool alreadyPresent;
        std::size_t index;
        assert(record.key >= 0);
        findIndex(record.key, alreadyPresent, index);
        if (!alreadyPresent) {
            assert(size() < CAPACITY);
            index = hash(record.key);
            quadProbe(index);
            ++used;
        }
        data[index].key = record.key;
        data[index].value = record.value;
    }

    void remove(int key) {
        bool found;
        std::size_t index;
        assert(key >= 0);
        findIndex(key, found, index);
        if (found) {
            data[index].key = PREVIOUSLYUSED;
            --used;
        }
    }

    bool isPresent(int key) const {
        bool found;
        std::size_t index;
        findIndex(key, found, index);
        return found;
    }

    void find(int key, bool& found, RecordType& result) const {
        std::size_t index;
        findIndex(key, found, index);
        if (found) {
            result.key = data[index].key;
            result.value = data[index].value;
        }
    }

    std::size_t size() const { return used; }

private:
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;

    struct InternalRecord {
        int key;
        std::string value;
    };

    InternalRecord data[CAPACITY];
    std::size_t used;

    std::size_t hash(int key) const {
        return key % CAPACITY;
    }

    void quadProbe(std::size_t& index) const {
        std::size_t original = index;
        int i = 1;
        while (data[index].key != NEVERUSED && data[index].key != PREVIOUSLYUSED) {
            index = (original + i * i) % CAPACITY;
            if (index == original) break; 
            ++i;
        }
    }

    void findIndex(int key, bool& found, std::size_t& index) const {
        std::size_t count = 0;
        index = hash(key);
        std::size_t original = index;
        int i = 0;

        while (count < CAPACITY) {
            if (data[index].key == key) {
                found = true;
                return;
            }
            if (data[index].key == NEVERUSED) {
                found = false;
                return;
            }
            ++count;
            ++i;
            index = (original + i * i) % CAPACITY;
        }
        found = false;
    }
};

struct Record {
    int key;
    std::string value;
};

int main() {
    Table<Record> table;

    Record r1{ 5, "five" };
    Record r2{ 21, "twenty-one" };
    Record r3{ 37, "thirty-seven" };
    Record r4{ 5, "five updated" }; 

    table.insert(r1);
    table.insert(r2);
    table.insert(r3);

    std::cout << "Table size after inserts: " << table.size() << "\n";

    bool found;
    Record result;

    table.find(21, found, result);
    if (found) std::cout << "Found key 21: " << result.value << "\n";

    table.insert(r4); 

    table.find(5, found, result);
    if (found) std::cout << "Found key 5 after update: " << result.value << "\n";

    table.remove(21);
    std::cout << "Table size after removing key 21: " << table.size() << "\n";

    found = table.isPresent(21);
    std::cout << "Is key 21 present? " << (found ? "Yes" : "No") << "\n";

    return 0;
}
