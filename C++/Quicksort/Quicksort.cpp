#include <iostream>
#include <list>
#include <string>

// Partition function: splits a list based on a pivot value
template <typename T>
void partition(
    const T& pivot,
    const std::list<T>& original,
    std::list<T>* less,
    std::list<T>* greater
) {
    for (const T& value : original) {
        if (value < pivot) {
            less->push_back(value);
        }
        else if (value > pivot) {
            greater->push_back(value);
        }
    }
}

// Quicksort function: recursively sorts a list and returns a new sorted list
template <typename T>
std::list<T>* quicksort(const std::list<T>& input) {
    if (input.empty() || input.size() == 1)
        return new std::list<T>(input);  

    T pivot = input.front();
    std::list<T> less;
    std::list<T> greater;

    std::list<T> rest(++input.begin(), input.end());  
    partition(pivot, rest, &less, &greater);

    std::list<T>* sortedLess = quicksort(less);
    std::list<T>* sortedGreater = quicksort(greater);

    std::list<T>* result = new std::list<T>();
    result->splice(result->end(), *sortedLess);
    result->push_back(pivot);
    result->splice(result->end(), *sortedGreater);

    delete sortedLess;
    delete sortedGreater;

    return result;
}

int main() {
    std::list<int> nums = { 4, 1, 7, 3, 5, 2, 6 };

    std::cout << "Original list: ";
    for (int x : nums) std::cout << x << " ";
    std::cout << "\n";

    std::list<int>* sorted = quicksort(nums);

    std::cout << "Sorted list: ";
    for (int x : *sorted) std::cout << x << " ";
    std::cout << "\n";

    delete sorted;
    return 0;
}
