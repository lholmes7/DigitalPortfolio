#include <iostream>
#include <cassert>

template <class RecordType>
class Table {
public:
    static const std::size_t CAPACITY = 1024; 

    Table() : used(0) {
        for (std::size_t i = 0; i < CAPACITY; ++i)
            data[i].key = NEVERUSED;
    }

    void insert(const RecordType& entry) {
        bool alreadyPresent;
        std::size_t index;
        assert(entry.key >= 0);
        findIndex(entry.key, alreadyPresent, index);

        if (!alreadyPresent) {
            assert(size() < CAPACITY);
            std::size_t attempt = 1;
            index = hash(entry.key);
            while (!isVacant(index) && data[index].key != NEVERUSED) {
                index = quadProbe(hash(entry.key), attempt++);
            }
            ++used;
        }
        data[index] = entry;
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
        if (found) result = data[index];
    }

    std::size_t size() const { return used; }

private:
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;

    struct InternalRecord {
        int key;
        
    };

    InternalRecord data[CAPACITY];
    std::size_t used;

    std::size_t hash(int key) const {
        return key % CAPACITY;
    }

    std::size_t quadProbe(std::size_t baseIndex, std::size_t attempt) const {
        return (baseIndex + attempt * attempt) % CAPACITY;
    }

    void findIndex(int key, bool& found, std::size_t& index) const {
        std::size_t count = 0;
        std::size_t attempt = 1;
        index = hash(key);

        while (count < CAPACITY && data[index].key != NEVERUSED && data[index].key != key) {
            ++count;
            index = quadProbe(hash(key), attempt++);
        }

        found = (data[index].key == key);
    }

    bool isVacant(std::size_t index) const {
        return data[index].key == NEVERUSED || data[index].key == PREVIOUSLYUSED;
    }
};
