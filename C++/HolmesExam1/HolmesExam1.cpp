//Landon Holmes
//CS451
//HolmesExam1.cpp

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("Summer21Exam1_Numbers.txt");  // File Handling

    if (!inputFile) {  // Can the file be read?
        cout << "Error: Could not read the file." << endl;
        return 1;
    }

    double sum = 0;
    double number; //Does the file  accept decimals?

    // Read the 14 Numbers
    for (int i = 0; i < 14; i++) {
        if (!(inputFile >> number)) {  // Is the input valid?
            cout << "Error: Invalid input." << endl;
            return 1;
        }
        sum += number;
    }

    // Read the 15th number
    double divisor;
    if (!(inputFile >> divisor)) {  // Does the file have 15 entries?
        cout << "Error: 15th number missing." << endl;
        return 1;
    }

    // Is the 15th number 0?
    if (divisor == 0) {
        cout << "Error: Division by 0." << endl;
        return 1;
    }

    // Calculate
    double result = sum / divisor;
    cout << "The result is: " << result << endl; // Output

    inputFile.close();
    return 0;
}