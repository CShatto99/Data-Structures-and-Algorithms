/*
    Name: Cameron Shatto
    Course Section: CSCE 3110.021
    Date: 5/21/2020
    Description: This program will compare the running time complexity of two multiplication functions.
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

int getOperand();
bool withinRange(int op);
void getTimeComplexity(bool flag, int op1, int op2);
int multiply(int operand1, int operand2);
int bitMultiply(int operand1, int operand2);

int main() {
    // flag to determine which multiplication function is executed
    bool flag = false;

    // store the operands
    int op1 = getOperand();
    int op2 = getOperand();

    // check if the product of the two operands causes integer overflow
    if (op1 > 0 && op2 > 0 && op1 * op2 < 0) {
        cout << "Error: Product results in integer overflow.\n";
        exit(-1);
    }
    
    // get experimental running time complexity for the "multiply" function
    cout << "Multiplication using only ADDITION:\n";
    getTimeComplexity(flag, op1, op2);

    flag = true;

    // get experimental running time complexity for the "bitMultiply" function
    cout << "Multiplication using only ADDITION and BIT SHIFTS:\n";
    getTimeComplexity(flag, op1, op2);
    
}

int getOperand() {
    int op;

    // get the operand from user input
    cout << "Enter a positive integer: ";
    cin >> op;

    // check for integer overflow
    if (!withinRange(op)) {
        cout << "Error: Product results in integer overflow.\n";
        exit(-1);
    }

    // re-prompt until a postive integer is entered
    while (op <= 0) {
        cout << "Enter a positive integer: ";
        cin >> op;
        if (!withinRange(op)) {
            cout << "Error: Product results in integer overflow.\n";
            exit(-1);
        }
    }
    return op;
}

void getTimeComplexity(bool flag, int op1, int op2) {
    // "start" and "end" act as timestamps and "exec_time" holds the elapsed time
    time_point<high_resolution_clock> start, end;
    duration<double> exec_time;

    // "iter" is how many calls are made to the multiply functions
    int iter = 10, avg_sec = 0, avg_nanosec = 0;

    for (int i = 0; i < iter; i++) {
        // get elapsed time using timestamps
        start = high_resolution_clock::now();
        if(!flag) cout << "Product: " << multiply(op1, op2) << endl;
        else cout << "Product: " << bitMultiply(op1, op2) << endl;
        end = high_resolution_clock::now();

        // record elapsed time and add it to both averages
        exec_time = end - start;
        avg_sec += int(exec_time.count());
        avg_nanosec += int(exec_time.count() * 1e9);

        cout << "Pass " << (i + 1) << ": " << int(exec_time.count()) << " seconds " << int(exec_time.count() * 1000000000) << " nanoseconds\n";
    }

    // display the average execution time in seconds and nanoseconds
    cout << "Average: " << (avg_sec / iter) << " seconds " << (avg_nanosec / iter) << " nanoseconds\n\n";
}

// check for integer overflow on "op"
bool withinRange(int op) {
    return (numeric_limits<int>::min() < op && op < numeric_limits<int>::max());
}

int multiply(int operand1, int operand2) {
    // variables to determine the multiplier and multiplicand based on input values
    int multiplier   = (operand1 < operand2) ? operand1 : operand2;
    int multiplicand = (operand1 > operand2) ? operand1 : operand2;

    // variable to hold the final product
    int product = 0;

    // adds "multiplicand" to "product" "multiplier" times.
    for (int i = 0; i < multiplier; i++) {
        product += multiplicand;
    }
    return product;
}

int bitMultiply(int operand1, int operand2) {
    // variables to determine the multiplier and multiplicand based on input values
    int multiplier   = (operand1 < operand2) ? operand1 : operand2;
    int multiplicand = (operand1 > operand2) ? operand1 : operand2;

    // variable to hold the final product
    int product = 0;
    
    // while there are still SET bits to shift right
    while (multiplier > 0) {
        // if the current multiplier is odd add the multiplicand to the product
        if (multiplier & 1)
            product += multiplicand;

        // shift the multiplicand right one and the muliplier left one (<<=1 equals *=2 and >>=1 equals /=2)
        multiplicand <<= 1;
        multiplier >>= 1;
    }
    return product;
}
