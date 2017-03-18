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

//forward decl
void printState(const vecBool& state);


int main(int argc, char **argv)
{
    QuantumRegister reg;
    vecBool measurment;
    std::vector<vecDouble> psi(3);
    psi[0] = vecDouble{0,0,0,1,0,0,0,0};
    
    psi[1] = vecDouble{1,0,0,0,0,0,0,1};
    
    psi[2] = vecDouble{1,1,1,1,1,1,1,1};

    //For each initial psi, print out 10 measurments
    for(int j = 0; j < 3; j++)
    {
	std::cout << "Initial state " << j+1 << ":" << std::endl;
	//prepare system
	reg.prepareState(psi[j]);
	for(int i = 0; i < 10; i++)
	{
	    std::cout << reg.measure(measurment) << "=>";
	    printState(measurment);
	}
	std::cout << std::endl;
    }
    
    return 0;
}

void printState(const vecBool& state)
{
    std::cout << "|";
    for(int i = 2; i>=0;i--)
	std::cout << state[i];
    std::cout << ">" << std::endl;
}
