
//This class adds functions to automate the testing
//of quantum algorithms and the computer simulation
#ifndef TESTHELPER_H
#define TESTHELPER_H

//include files
#include <functional>
#include <iostream>
#include <vector>
#include "QuantumRegister.h"

//typedef declerations
using vecInt = std::vector<int>;
using vecBool = std::vector<bool>;

//Class definition
class TestHelper
{

public:
    //test: test to run on the quantum register,
    //reg: the quantum register to perform test on,
    //n: number of times to make measurements of the test,
    //verbose: flag for printing out each state
    static void runTest(std::function<void (QuantumRegister&)> test,
			QuantumRegister& reg, int n = 1,
			bool verbose = false);

    static void printState(const vecBool& state);
    static void printState(int state, int N);
    
    //Runs test n times making a measurement after each
    //run. Differs from runTest in that runTest only executes
    //the test once and then makes numerous measurements
    //void runTest2(std::function<void ()> test, int n = 1);

private:
    //This function prints a summary of the results
    //of a test.
    static void printResults(const vecInt& results);

};
#endif
