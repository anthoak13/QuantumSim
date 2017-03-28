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



#ifndef OORACLE_H
#define OORACLE_H

//Class that implements the oracle for grover's algorithm
#include "Operator.h"

class OOracle : public Operator
{
public:
    OOracle(uint answer, ubyte N);
    
    double at(int a, int b) override;
};

#endif
