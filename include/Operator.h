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


//Abstract base class for all operators
#ifndef OPERATOR_H
#define OPERATOR_H

#include <complex>
#include <iostream>
#include <vector>

using ubyte = unsigned char;
using complex = std::complex<double>;
using vecComplex = std::vector<complex>;

class Operator
{
public:
    virtual complex at(int a, int b) =0;
    uint size() {return 1 << N;};
    void print() {
	for(auto&& vec : O)
	{
	    for(auto&& elem : vec)
		std::cout << elem << " ";
	    std::cout << std::endl;
	}
    };
protected:
    //The size of the register this gate can be applied to
    ubyte N;
    //vector to store the matrix operator
    std::vector<vecComplex> O;

};
#endif
