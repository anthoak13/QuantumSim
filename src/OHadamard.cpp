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


//implimentation of Hadamard gate for an N bit system


#include "OHadamard.h"

OHadamard::OHadamard(ubyte qbit, ubyte N)
{
    //Initialize the 2X2 operator
    U =	{{1,1},
	 {1,-1}};
    for(auto&& vec : U)
	for(auto&& elem : vec)
	    elem *= 1/std::sqrt(2);
    
    //Set constructed to false
    constructed = false;

    this->N = N;
    this->qbit.push_back(qbit);
}


