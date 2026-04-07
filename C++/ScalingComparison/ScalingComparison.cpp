#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>

class Vector {
protected:
    int* data;
    size_t sz;
    size_t cap;

    virtual void grow() {
        size_t newCap = cap * 2;
        int* newData = new int[newCap];
        for (size_t i = 0; i < sz; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    Vector() : sz(0), cap(1) {
        data = new int[cap];
    }

    virtual ~Vector() {
        delete[] data;
    }

    virtual void push_back(int value) {
        if (sz == cap) {
            grow();
        }
        data[sz++] = value;
    }

    virtual void reset() {
        delete[] data;
        sz = 0;
        cap = 1;
        data = new int[cap];
    }
};

class VectorCopy : public Vector {
protected:
    void grow() override {
        size_t newCap = cap * 2;
        int* newData = new int[newCap];
        std::copy(data, data + sz, newData);
        delete[] data;
        data = newData;
        cap = newCap;
    }
};

class VectorFastGrow : public Vector {
protected:
    void grow() override {
        size_t newCap = cap * 4;
        int* newData = new int[newCap];
        for (size_t i = 0; i < sz; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    VectorFastGrow() {
        delete[] data;
        cap = 128;
        data = new int[cap];
    }

    void reset() override {
        delete[] data;
        sz = 0;
        cap = 128;
        data = new int[cap];
    }
};

void runTest(const std::string& label, Vector* v) {
    std::cout << "== " << label << " ==\n";
    for (int size = 2; size <= 16384; size *= 2) {
        v->reset();
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; ++i) {
            v->push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << size << " elements: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms\n";
    }
}

int main() {
    Vector base;
    VectorCopy copy;
    VectorFastGrow fast;

    runTest("Base Vector (manual copy, ×2)", &base);
    runTest("VectorCopy (std::copy, ×2)", &copy);
    runTest("VectorFastGrow (manual copy, ×4, start=128)", &fast);

    return 0;
}