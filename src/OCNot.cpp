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


#include "OCNot.h"


OCNot::OCNot(ubyte controlBit, ubyte notBit, ubyte N)
{
    U = {{1, 0, 0, 0},
	 {0, 1, 0, 0},
	 {0, 0, 0, 1},
	 {0, 0, 1, 0}};

    constructed = false;

    this->N = N;
    qbit.push_back(controlBit);
    qbit.push_back(notBit);
}
