#include <iostream>
#include "SmartDelete.hpp"

using namespace std;

void printNumber(int number) {
    cout << number << ' ';
}

int main() {
    List<int> numberList;
    numberList.push_back(1);
    numberList.push_back(2);
    numberList.push_back(3);
    numberList.push_back(4);

    cout << "Before deletion: ";
    numberList.traverse(printNumber);  // Outputs: 1 2 3 4
    cout << "\n";

    numberList.pop_front();  // Marks 1 as deleted
    numberList.pop_back();   // Marks 4 as deleted

    cout << "After lazy deletions: ";
    numberList.traverse(printNumber);  // Outputs: 2 3
    cout << "\n";

    numberList.pop_front();  // Marks 2 as deleted
    numberList.pop_back();   // Marks 3 as deleted

    cout << "After cleanup: ";
    numberList.traverse(printNumber);  // Output: 
    cout << "\n";

    return 0;
}
