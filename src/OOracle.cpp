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



//implimentation for the N-bit oracle operator

#include "OOracle.h"

OOracle::OOracle(uint answer, ubyte N)
{
    this->N = N;
    for(uint i = 0; i < this->size(); i++)
    {
	O.push_back(vecDouble{});
	for(uint j = 0; j < this->size(); j++)
	    if(j == i)
		O.at(i).push_back( j == answer ? -1 : 1);
	    else
		O.at(i).push_back(0);
    }
}

double OOracle::at(int a, int b)
{
    return O.at(a).at(b);
}
