// Name: Nadhirah Michael-Ho
// Class (CECS 325-02)
// Project Name (Prog 4 – Threads)
// Due Date (03/25/2025)
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program
// generate.cpp
// Generates a file with COUNT random numbers in the range [MIN, MAX]

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " COUNT MIN MAX" << endl;
        return 1;
    }

    int count = atoi(argv[1]);
    int minVal = atoi(argv[2]);
    int maxVal = atoi(argv[3]);

    if (minVal > maxVal) {
        cerr << "Error: MIN must be less than MAX." << endl;
        return 1;
    }

    ofstream outFile("numbers.dat");
    if (!outFile) {
        cerr << "Error opening numbers.dat" << endl;
        return 1;
    }

    srand(time(0));
    for (int i = 0; i < count; i++) {
        outFile << (rand() % (maxVal - minVal + 1)) + minVal << endl;
    }

    outFile.close();
    return 0;
}

