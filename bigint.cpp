// Author: Nadhirah Michael-Ho
// CECS 325-02 Prog 6
// Project Name(Prog 6 - Big Integer)
// Due 05/08/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>              // For input/output stream operations
#include <vector>                // To use the vector container
#include <iomanip>               // For output formatting
#include <climits>               // For INT_MAX
#include <cstdlib>               // For system() function

using namespace std;            // Use the standard namespace

// Class to represent arbitrarily large integers
class BigInt {
private:
    vector<char> v;             // Vector to store each digit (as a char) of the number

public:
    BigInt() { v.push_back(0); } // Default constructor initializes BigInt to 0

    // Constructor to initialize BigInt from an int
    BigInt(int num) {
        if (num == 0) {
            v.push_back(0);      // If number is 0, just push back 0
        } else {
            while (num > 0) {    // Break number into digits
                v.insert(v.begin(), num % 10); // Insert digit at the beginning
                num /= 10;       // Remove last digit
            }
        }
    }

    // Constructor to initialize BigInt from a string
    BigInt(const string& s) {
        for (char c : s) {
            v.push_back(c - '0'); // Convert each char digit to int and store
        }
    }

    // Copy constructor
    BigInt(const BigInt& other) : v(other.v) {}

    // Returns size (number of digits)
    int size() const { return v.size(); }

    // Addition operator overloading
    BigInt operator+(const BigInt& b) const {
        BigInt result;               // Result BigInt
        result.v.clear();            // Clear initial 0
        int carry = 0;               // Carry for addition
        int i = v.size() - 1;        // Index for current object
        int j = b.v.size() - 1;      // Index for b

        while (i >= 0 || j >= 0 || carry) { // While digits or carry remain
            int x = (i >= 0) ? v[i] : 0;    // Get digit or 0
            int y = (j >= 0) ? b.v[j] : 0;  // Get digit or 0
            int sum = x + y + carry;       // Add digits and carry
            result.v.insert(result.v.begin(), sum % 10); // Insert digit
            carry = sum / 10;              // Update carry
            i--, j--;                      // Move to next digits
        }

        return result;
    }

    // Subtraction operator overloading, assuming *this >= b
    BigInt operator-(const BigInt& b) const {
        BigInt result;
        result.v.clear();
        int borrow = 0;                 // Borrow for subtraction
        int i = v.size() - 1;
        int j = b.v.size() - 1;

        while (i >= 0) {
            int x = v[i] - borrow;      // Subtract borrow
            int y = (j >= 0) ? b.v[j] : 0; // Get digit or 0
            if (x < y) {                // If borrow needed
                x += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.v.insert(result.v.begin(), x - y); // Insert result digit
            i--, j--;
        }

        while (result.v.size() > 1 && result.v[0] == 0) // Remove leading 0s
            result.v.erase(result.v.begin());

        return result;
    }

    // Multiplication operator overloading
    BigInt operator*(const BigInt& b) const {
        BigInt result;
        result.v = vector<char>(v.size() + b.v.size(), 0); // Preallocate with 0s

        for (int i = v.size() - 1; i >= 0; --i) {
            for (int j = b.v.size() - 1; j >= 0; --j) {
                int mul = v[i] * b.v[j] + result.v[i + j + 1]; // Multiply digits
                result.v[i + j + 1] = mul % 10;                // Store unit digit
                result.v[i + j] += mul / 10;                   // Carry to left
            }
        }

        while (result.v.size() > 1 && result.v[0] == 0) // Remove leading 0s
            result.v.erase(result.v.begin());

        return result;
    }

    // Division operator overloading
    BigInt operator/(const BigInt& b) const {
        BigInt quotient, remainder;
        for (int i = 0; i < v.size(); ++i) {
            remainder.v.push_back(v[i]); // Append digit to remainder
            while (remainder.v.size() > 1 && remainder.v[0] == 0) // Remove leading 0s
                remainder.v.erase(remainder.v.begin());
            int count = 0;
            while (remainder >= b) {    // Subtract b until remainder < b
                remainder = remainder - b;
                count++;
            }
            quotient.v.push_back(count); // Push quotient digit
        }

        while (quotient.v.size() > 1 && quotient.v[0] == 0) // Remove leading 0s
            quotient.v.erase(quotient.v.begin());

        return quotient;
    }

    // Modulus operator overloading
    BigInt operator%(const BigInt& b) const {
        BigInt remainder;
        for (int i = 0; i < v.size(); ++i) {
            remainder.v.push_back(v[i]); // Append digit
            while (remainder.v.size() > 1 && remainder.v[0] == 0)
                remainder.v.erase(remainder.v.begin());
            while (remainder >= b) {
                remainder = remainder - b;
            }
        }

        while (remainder.v.size() > 1 && remainder.v[0] == 0) // Remove leading 0s
            remainder.v.erase(remainder.v.begin());

        return remainder;
    }

    // Equality operator
    bool operator==(const BigInt& b) const {
        return v == b.v;
    }

    // Greater than or equal operator
    bool operator>=(const BigInt& b) const {
        if (v.size() > b.v.size()) return true;       // If more digits
        if (v.size() < b.v.size()) return false;      // If fewer digits
        for (int i = 0; i < v.size(); ++i) {          // Compare digit by digit
            if (v[i] > b.v[i]) return true;
            if (v[i] < b.v[i]) return false;
        }
        return true;
    }

    // Greater than operator for int
    bool operator>(const int& other) const {
        BigInt temp(other);             // Convert int to BigInt
        if (v.size() > temp.v.size()) return true;
        if (v.size() < temp.v.size()) return false;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] > temp.v[i]) return true;
            if (v[i] < temp.v[i]) return false;
        }
        return false;
    }

    // Post-increment operator
    BigInt operator++(int) { BigInt temp = *this; *this = *this + 1; return temp; }

    // Pre-increment operator
    BigInt operator++() { *this = *this + 1; return *this; }

    // Print function
    void print() const {
        for (char c : v) cout << (int)c; // Output each digit
        cout << endl;
    }

    // Public wrapper for Fibonacci
    BigInt fibo() const {
        return fiboHelper(BigInt(0), BigInt(1), *this);
    }

    // Recursive Fibonacci helper
    BigInt fiboHelper(const BigInt& a, const BigInt& b, const BigInt& n) const {
        if (n == BigInt(0)) return a;
        if (n == BigInt(1)) return b;
        return fiboHelper(b, a + b, n - BigInt(1));
    }

    // Public wrapper for factorial
    BigInt fact() const {
        return factHelper(*this, BigInt(1));
    }

    // Recursive factorial helper
    BigInt factHelper(const BigInt& n, const BigInt& acc) const {
        if (n == BigInt(0) || n == BigInt(1)) return acc;
        return factHelper(n - BigInt(1), acc * n);
    }

    // Friend function to support int + BigInt
    friend BigInt operator+(int lhs, const BigInt& rhs) {
        return BigInt(lhs) + rhs;
    }

    // Output stream operator
    friend ostream& operator<<(ostream& out, const BigInt& b) {
        if (b.v.size() > 12) {                                // If large, print scientific notation
            out << fixed << setprecision(6);
            out << (double)(b.v[0]) + (b.v[1]/10.0) + (b.v[2]/100.0) + (b.v[3]/1000.0)
                + (b.v[4]/10000.0) + (b.v[5]/100000.0) + (b.v[6]/1000000.0);
            out << 'e' << b.v.size() - 1;
        } else {
            for (char c : b.v) out << (int)c;                 // Otherwise, print normally
        }
        return out;
    }
};

// Function to test all BigInt operations
void testUnit() {
    int space = 10;                               // Set output width
    cout << "\a\nTestUnit:\n" << flush;           // Title and flush output buffer
    system("whoami");                             // Print current user
    system("date");                               // Print system date

    BigInt n1(25);                                // Test integer constructor
    BigInt s1("25");                              // Test string constructor
    BigInt n2(1234);                              // Another int
    BigInt s2("1234");                            // Another string
    BigInt n3(n2);                                // Copy constructor
    BigInt fibo(12345);                           // Test value for Fibonacci
    BigInt fact(50);                              // Test value for factorial
    BigInt imax = INT_MAX;                        // Max int
    BigInt big("9223372036854775807");            // Very large number

    cout << "n1(int)    :" << setw(space) << n1 << endl;
    cout << "s1(str)    :" << setw(space) << s1 << endl;
    cout << "n2(int)    :" << setw(space) << n2 << endl;
    cout << "s2(str)    :" << setw(space) << s2 << endl;
    cout << "n3(n2)     :" << setw(space) << n3 << endl;
    cout << "fibo(12345) :" << setw(space) << fibo << endl;
    cout << "fact(50)    :" << setw(space) << fact << endl;
    cout << "imax       :" << setw(space) << imax << endl;
    cout << "big         :" << setw(space) << big << endl;
    cout << "big.print() : "; big.print(); cout << endl;
    cout << n2 << "/" << n1 << " = " << n2/n1 << " rem " << n2%n1 << endl;
    cout << "fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;
    cout << "10 + n1 = " << 10+n1 << endl;
    cout << "n1 + 10 = " << n1+10 << endl;
    cout << "(n1 == s1)? --> " << ((n1==s1)?"true":"false") << endl;
    cout << "n1++ = ?  --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ?  --> before:" << ++s1 << " after:" << s1 << endl;
    cout << "s2 * big = ? --> " << s2*big << endl;
    cout << "big * s2 = ? --> " << big*s2 << endl;
}

// Main function
int main() {
    testUnit();   // Run test unit
    return 0;     // Exit program
}

