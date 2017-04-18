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



#ifndef OGATEARRAY_H
#define OGATEARRAY_H

//definition of J operator for grover's algorithm
#include "Operator.h"

class OGateArray : public Operator
{
public:
    OGateArray(ubyte N);
    void addGate(Operator* G);

    complex at(int a, int b) override;
private:
    bool empty;
};



#endif
