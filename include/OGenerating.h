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

#ifndef OGENERATING_H
#define OGENERATING_H

//Abstract class for generating a gate of size N
#include <complex>
#include <cmath>
#include <iostream>
#include <vector>
#include "Operator.h"

class OGenerating : public Operator
{
public:
    complex at(int a, int b) override;
    void print() override;

    //Function that constructs the matrix if it hasn't been
    //already
    virtual void construct();
protected:
    //vector storing the small matrix operator (for one or more
    //q-bit gate)
    std::vector<vecComplex> U;
    //boolean to tell if the operator has been constructed yet
    bool constructed;
    //qbit(s) the gate is applied to
    std::vector<ubyte> qbit;
    //Function that constructs the matrix if it hasn't been
    //already

    
    //Kronecker deltas with only 1/0 as options
    //is just /delta_{1,b} = !(a xor b)
    bool notKDelta(bool a, bool b) { return (a ^ b); }
};

#endif
