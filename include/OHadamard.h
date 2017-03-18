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
#include <vector>
#include <cmath>
#include "Operator.h"

using vecDouble = std::vector<double>;

class OHadamard : public Operator
{
public:
     OHadamard(int qbit);
     double at(int a, int b) override;

private:
     //vector to store the matrix operator
     std::vector<vecDouble> O;
};

#endif
