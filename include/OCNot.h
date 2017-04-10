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

#ifndef OCNOT_H
#define OCNOT_H

//Class for a controlled not gate
#include <cmath>
#include <iostream>
#include <vector>
#include "OGenerating.h"

class OCNot : public OGenerating
{
public:
    //controlBit is the bit to control on,
    //notBit is the bit to flip,
    //N is the size of the register
    OCNot(ubyte controlBit, ubyte notBit, ubyte N);

};

#endif
