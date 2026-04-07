//Landon Holmes
//Software Engineering Assignment 1

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("number.txt");  //used the following as a refresher: https://www.w3schools.com/cpp/cpp_files.asp
    ofstream outputFile("average.txt");  

    double number, total = 0;
    int count = 0;

    // input
    while (inputFile >> number) {
        total += number;
        count++;
    }

    //output
    if (count == 0) {
        outputFile << "Empty file." << endl;
    }
    else {
        double average = total / count;
        outputFile << "Average = " << average;
        cout << "Output file success. (Check file)";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}