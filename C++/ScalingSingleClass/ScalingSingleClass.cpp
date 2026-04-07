#include <iostream>
#include <chrono>
#include <algorithm>

class SimpleVector {
private:
    int* data;
    size_t size;
    size_t capacity;
    int growthFactor;

public:
    SimpleVector(int startCapacity = 1, int growBy = 2)
        : size(0), capacity(startCapacity), growthFactor(growBy) {
        data = new int[capacity];
    }

    ~SimpleVector() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void reset() {
        delete[] data;
        size = 0;
        capacity = (growthFactor == 4) ? 128 : 1;
        data = new int[capacity];
    }

    void resize() {
        size_t newCap = capacity * growthFactor;
        int* newData = new int[newCap];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCap;
    }
};

void runTest(const std::string& label, SimpleVector& v) {
    std::cout << "== " << label << " ==\n";
    for (int n = 2; n <= 33554432; n *= 2) { //2^25
        v.reset();
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            v.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << n << " elements: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms\n";
    }
}

int main() {
    SimpleVector baseVector(1, 2);
    SimpleVector fastVector(128, 4);

    runTest("Base Vector (starts at 1, grows x2)", baseVector);
    runTest("Fast Vector (starts at 128, grows x4)", fastVector);

    return 0;
}