#include <iostream>
#include "LazyDelete.hpp"

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
    numberList.traverse(printNumber);  //Outputs 1 2 3 4
    cout << "\n";

    numberList.pop_front();  //Sets 1 to delete
    numberList.pop_back();   //Sets 4 to delete

    cout << "After lazy deletions: ";
    numberList.traverse(printNumber);  //Outputs: 2 3
    cout << "\n";

    numberList.pop_front();  //Sets 2 to delete
    numberList.pop_back();   //Sets 3 to delete

    cout << "After deletion: ";
    numberList.traverse(printNumber);  //Output: 
    cout << "\n";

    return 0;
}
