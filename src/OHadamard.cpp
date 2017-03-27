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


//implimentation of Hadamard gate for a 3 bit system


#include "OHadamard.h"

OHadamard::OHadamard(ubyte qbit, ubyte N)
{
    //Initialize the 2X2 operator
    H =	{{1,1},
	 {1,-1}};
    for(auto&& vec : H)
	for(auto&& elem : vec)
	    elem *= 1/std::sqrt(2);
    
    //Set constructed to false
    constructed = false;

    this->N = N;
    this->qbit = qbit;
}

double OHadamard::at(int a, int b)
{
    construct();
    return O.at(a).at(b);
}

void OHadamard::construct()
{
    //if the operator has already been created, skip
    if(constructed)
	return;
    std::cout << "Constructing the operator..." << std::endl;

    //The matrix is a 2^N square matrix
    uint size = 1 << N;
    //locOfBit is the bit that determines
    //the H matrix.
    //ie for H^(1) locOfBit is 2^2.
    uint locOfBit = 1 << (N - qbit);
    
    //Loop through each row of the matrix
    for(uint i = 0; i < size; i++)
    {
	//Add a blank vector representing the row
	O.push_back(vecDouble{});
	//Loop through each column
	//(i,j) are matrix element being calculated
	for(uint j = 0; j < size; j++)
	{
	    bool zero = false;
	   
            //Extract the individual bits
	    //Loop through and check to see if any delta
	    //is zero, if it is break the loop
	    for(uint k = 1;!zero && k < size; k <<= 1)
	    {
		//if k is locOfBit then skip, it isn't a delta
		if(k != locOfBit)
		    zero |= notKDelta(i & k, j & k);
	    }

	    //double negation fixes the result at 1 or 0,
	    //otherwise you can get any power of 2 (4 & 4 = 4).
	    O.at(i).push_back(zero ? 0 :
			      H.at(!!(i & locOfBit))
			      .at(!!(j & locOfBit)));
	}
    }

    constructed = true;

    
    //print out the operator
/*    for(auto&& vec : O)
    {
	for(auto elem : vec)
	    std::cout << elem << " ";
	std::cout << std::endl;
	}*/
}
