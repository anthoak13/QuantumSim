
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

//Class definition
class TestHelper
{

public:
    //test is the test to run on the computer, n is the number
    //of times to make measurements of the test.
    static void runTest(std::function<void (QuantumRegister&)> test,
		 QuantumRegister& reg, int n = 1);

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
