// Author: Nadhirah Michael-Ho
// CECS 325-02 Prog 5
// Project Name (Prog 5 – GoldRabbits)
// Due 04/22/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include <iostream>          // Include the standard input/output stream library
#include <iomanip>           // Include the I/O manipulator library for setting output format
#include <map>               // Include the map container from the standard library
#include <string>            // Include the string library
#include <stdexcept>         // Include the library for standard exceptions (e.g., overflow)
#include <limits>            // Include the library for numeric limits (e.g., max and min values)
#include <cstdlib>           // Include the library for general purpose functions (e.g., stoi)
#include <chrono>            // Include the chrono library for measuring time
#include <sys/time.h>        // Include the sys/time library for system resource usage
#include <sys/resource.h>    // Include the sys/resource library for system resource usage
#include <cctype>            // Include the cctype library for character handling (e.g., isdigit)
using namespace std;

// Define the integer type
//#define integer short        // for short testing
//#define integer int        // for int testing
#define integer long long  // for long long testing

// Global variable to store the original input for logging purposes
integer originalInput;

// Function to compute GoldRabbits using memoization and overflow check
integer goldRabbits(integer n) {
    // Static map to store previously computed Fibonacci values (memoization)
    static map<integer, integer> fiboMap;

    // Check for special case when input is -1
    if (n == -1) {
        // Log the contents of the Fibonacci map
        cout << "fibo(-1):" << endl;
        cout << "Fibo Map contents:" << endl;
        // Loop through the map and log each Fibonacci number and its result
        for (const auto& pair : fiboMap) {
            cout << pair.first << ":" << pair.second << endl;
        }
        cout << "end of Fibo map" << endl << endl;
        return -1;  // Return -1 to signal the special case
    }

    // Handle invalid input for negative n (except -1)
    if (n < 0) {
        throw string("fibo(" + to_string(n) + "):\tInvalid input");  // Throw an error with a message
    }

    // Check if the result for n is already computed and stored in the map
    if (fiboMap.count(n)) {
        return fiboMap[n];  // If so, return the stored result
    }

    integer result;  // Variable to store the Fibonacci result
    // Base case: if n is 0 or 1, the Fibonacci value is 1
    if (n == 0 || n == 1) {
        result = 1;
    } else {
        // Recursive call to calculate Fibonacci numbers for n-1 and n-2
        integer a = goldRabbits(n - 1);
        integer b = goldRabbits(n - 2);

        // Calculate the sum of the two previous Fibonacci numbers
        long long sum = static_cast<long long>(a) + static_cast<long long>(b);

        // Overflow detection: check if the sum exceeds the limits of int
        if (sum > numeric_limits<int>::max() || sum < numeric_limits<int>::min()) {
            int overflowed = static_cast<int>(sum);  // Cast to int to simulate overflow
            // Throw an overflow error with a detailed message
            throw string("fibo(" + to_string(originalInput) + "):\toverflow error at fib(" + to_string(n) + "):" + to_string(overflowed));
        }

        // Store the result as an integer (cast the sum back to integer)
        result = static_cast<integer>(sum);
    }

    // Store the computed result in the map for future reference
    fiboMap[n] = result;

    return result;  // Return the Fibonacci result
}

int main(int argc, char* argv[]) {
    // Loop through all arguments passed to the program
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];  // Get the current argument
        bool valid = true;  // Flag to check if the argument is valid

        // Check if the argument is empty
        if (arg.empty()) {
            valid = false;
        } else {
            // Start checking from index 1 if there's a negative sign
            size_t start = (arg[0] == '-') ? 1 : 0;
            // Loop through the string and check if every character is a digit
            for (size_t j = start; j < arg.length(); ++j) {
                if (!isdigit(arg[j])) {  // If a character is not a digit
                    valid = false;
                    break;
                }
            }
        }

        // If the argument is not valid, log the error and skip it
        if (!valid) {
            cout << arg << " is not an integer" << endl;
            continue;
        }

        // Convert the valid string argument to an integer
        integer val = stoi(arg);
        originalInput = val;  // Store the original input value for logging

        try {
            // Call the goldRabbits function to calculate the Fibonacci number
            integer result = goldRabbits(val);
            // If the value is not -1, log the result
            if (val != -1) {
                cout << "fibo(" << val << "): " << "\t" << result << endl;
            }
        } catch (const string& msg) {  // Catch any thrown exception
            cout << msg << endl;  // Log the error message
        }

        
    }

    return 0;  // Return success
}
