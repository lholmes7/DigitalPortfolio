//Landon Holmes

#include <iostream>
#include <chrono>
using namespace std;

void moveDisks(int, int, int, int);
void printIt(int, int, int);

int main() {
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;
    const int NUMDISKS = 3;

    for (auto numdisks : { 5,10,15}) {
        auto start=chrono::high_resolution_clock::now();
        cout << "Numdisks: " << numdisks << endl;
        moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);
        cout << "Moved " << numdisks << " pegs"
            << " from peg " << FROMPEG
            << " to peg " << TOPEG << endl;
        auto end = chrono::high_resolution_clock::now(); // Calculates start time and end time while the tower is solved

        chrono::duration<double> elapsed = end - start; //Calculates time spent and displays it
        cout << "Recursive - Disks: " << numdisks
            << " | Time: " << elapsed.count() << " seconds" << endl;
    }
    return 0;
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg) {
    if (num > 0) {
        moveDisks(num - 1, fromPeg, tempPeg, toPeg);
        printIt(num, fromPeg, toPeg);
        moveDisks(num - 1, tempPeg, toPeg, fromPeg);
    }
}

void printIt(int disk, int fromPeg, int toPeg) {
    cout << "Move disk " << disk
        << " from peg " << fromPeg
        << " to peg " << toPeg << endl;
}