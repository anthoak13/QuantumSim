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

#ifndef OHADAMARD_H
#define OHADAMARD_H

//Class for Hadamard gate for 3 bit system
#include <cmath>
#include <iostream>
#include <vector>
#include "OGenerating.h"

class OHadamard : public OGenerating
{
public:
    //qbit is the bit to be operated on, N is the size of
    //the register
    OHadamard(ubyte qbit, ubyte N);
    double at(int a, int b) override;
};

#endif
