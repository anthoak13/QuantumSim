///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                            Copyright (C) 2017                             //
//                    Adam Anthony : All rights reserved                     //
//                                                                           //
//     This source code is licensed under the GNU GPL v3.0.You have the      //
//     right to modify and/or redistribute this source code under the terms  //
//     specified in the license, which may be found online at                //
//     http://www.gnu.org/licenses.                                          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


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
using uint = unsigned int;
using ubyte = unsigned char;
using vecUint = std::vector<uint>;
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

    
    //Runs test n times making a measurement after each
    //run. Differs from runTest in that runTest only executes
    //the test once and then makes numerous measurements
    //void runTest2(std::function<void ()> test, int n = 1);


private:
    static void printState(uint state, ubyte N);
    static void printState(const vecBool& state);
    
    //This function prints a summary of the results
   //of a test.
    static void printResults(const vecUint& results, const ubyte N);

};
#endif
