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

#ifndef OFGATE_H
#define OFGATE_H

//Class for Hadamard gate for N bit system
#include <cmath>
#include "Operator.h"
#include "QuantumRegister.h"

class OfGate : public Operator
{
public:
    //qbit is the bit to be operated on, N is the size of
    //the register
    OfGate(uint numToFactor, ubyte numL, ubyte numM,
	   uint a, ubyte controlbit);

    void construct();
    complex at(int i, int j) override;

    
private:
    bool constructed;
    ubyte controlL;
    ubyte sizeL;
    ubyte sizeM;
    uint C;
    uint a;

};

#endif
