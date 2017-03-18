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

//forward decl
void printState(const vecBool& state);
void test1(QuantumRegister& reg);


int main(int argc, char **argv)
{
    QuantumRegister reg;

    //run tests
    TestHelper::runTest(test1, reg, 10, true);
   
    return 0;
}

void test1(QuantumRegister& reg)
{
    reg.prepareState(vecDouble{1,1,1,1,1,1,1,1});
}
