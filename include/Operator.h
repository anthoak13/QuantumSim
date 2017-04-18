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
using complexPair = std::pair<uint, complex>;
using vecComplex = std::vector<complex>;
using vecComplexPair = std::vector< complexPair>;
using matrix = std::vector< std::vector< complex > >;
using sparseMatrix = std::vector< vecComplexPair >;


class Operator
{
public:
#ifdef SPARSE
    const sparseMatrix& getMatrix() { return O; }
#else
    const matrix& getMatrix() {return O;}
#endif
    virtual complex at(int a, int b) =0;

    uint size() {return 1 << N;};

    virtual void print() {
	//get row in vec
	for(auto&& row : O)
	{
	    //get either elem or pair in each row.
	    for(auto&& elem : row)
#ifndef SPARSE
		std::cout << elem << " ";
#else
	    {
		std::cout << "( " << elem.first << " "
			  << elem.second << ")" << std::endl;
	    }
#endif
	    std::cout << std::endl;
	}
    };
protected:
    //The size of the register this gate can be applied to
    ubyte N;
    
    //vector to store the matrix operator
#ifndef SPARSE
    matrix O;
#else
    sparseMatrix O;
#endif
    //Sparce matrix representation
    //sparseMatrix O;

};
#endif
