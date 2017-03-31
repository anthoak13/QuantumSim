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


//implimentation for the N-bit J operator

#include "OJGrover.h"

OJGrover::OJGrover(ubyte N)
{
    this->N = N;
}

complex OJGrover::at(int a, int b)
{
    if( a == b)
	return a == 0 ? -1 : 1;
    return 0;
}
