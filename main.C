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

#include <iostream>
#include "QuantumRegister.h"
#include "TestHelper.h"
#include "OHadamard.h"
#include "ONot.h"
#include "OOracle.h"
#include "OJGrover.h"

//forward decl
void printState(const vecBool& state);
void test1(QuantumRegister& reg);


int main(int argc, char **argv)
{
    //create register initially in |000>
    QuantumRegister reg(4);

    //run tests
    TestHelper::runTest(test1, reg, 1000, false);

    //Create H_1 operator and apply it to reg
    Operator* O = new OHadamard(4,reg.size());
    reg.apply(O);
    std::cout << "Applying H operator..." << std::endl;

    //re-run the test, should be 50/50 |000>/|100>
    TestHelper::runTest(test1, reg, 1000, false);

    reg.apply(O);
    std::cout << "Applying H operator..." << std::endl;

    //rerun the test, should return to |000> state
    TestHelper::runTest(test1, reg, 1000, false);

    return 0;
}

void test1(QuantumRegister& reg)
{

}
