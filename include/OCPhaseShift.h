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

#ifndef OCPHASESHIFT_H
#define OCPHASESHIFT_H

//Class for Hadamard gate for N bit system
#include <cmath>
#include "OGenerating.h"

class OCPhaseShift : public OGenerating
{
public:
    //qbit is the bit to be operated on, N is the size of
    //the register
    OCPhaseShift(double theta, ubyte controlbit, ubyte qbit, ubyte N);

};

#endif
