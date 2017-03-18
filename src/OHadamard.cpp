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

OHadamard::OHadamard(int qbit)
{
    //Initialize the operator
    if (qbit == 1)
	O = {{1,0,0,0,1,0,0,0},
	     { 0,1,0,0,0,1,0,0},
	     { 0,0,1,0,0,0,1,0},
	     { 0,0,0,1,0,0,0,1},
	     { 1,0,0,0,-1,0,0,0},
	     { 0,1,0,0,0,-1,0,0},
	     { 0,0,1,0,0,0,-1,0},
	     { 0,0,0,1,0,0,0,-1}};
    if ( qbit == 2)
	O = {{1,0,1,0,0,0,0,0},
	     { 0,1,0,1,0,0,0,0},
	     { 1,0,-1,0,0,0,0,0},
	     { 0,1,0,-1,0,0,0,0},
	     { 0,0,0,0,1,0,1,0},
	     { 0,0,0,0,0,1,0,1},
	     { 0,0,0,0,1,0,-1,0},
	     { 0,0,0,0,0,1,0,-1}};
    if (qbit == 3)
	O = {{ 1,1,0,0,0,0,0,0},
	     { 1,-1,0,0,0,0,0,0},
	     { 0,0,1,1,0,0,0,0},
	     { 0,0,1,-1,0,0,0,0},
	     { 0,0,0,0,1,1,0,0},
	     { 0,0,0,0,1,-1,0,0},
	     { 0,0,0,0,0,0,1,1},
	     { 0,0,0,0,0,0,1,-1}};

    //Normalize the operator
    for(auto&& vec : O)
	for(auto&& elem : vec)
	    elem *= 1/std::sqrt(2);
}

double OHadamard::at(int a, int b)
{
    return O.at(a).at(b);
}
