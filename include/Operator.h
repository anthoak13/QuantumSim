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


//Abstract base class for all operators
#ifndef OPERATOR_H
#define OPERATOR_H

class Operator
{
public:
    virtual double at(int a, int b) =0;

private:
    //Kronecker deltas with only 1/0 as options
    //is just /delta_{1,b} = !(a xor b)
    bool kDelta(bool a, bool b) { return !(a ^ b); }
};
#endif
