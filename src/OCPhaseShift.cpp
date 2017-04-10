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


//implimentation of phase shift gate for an N bit system


#include "OCPhaseShift.h"

OCPhaseShift::OCPhaseShift(double theta, ubyte controlbit,
			   ubyte qbit, ubyte N)
{
    complex i(0,1);
    //Initialize the 4x4 operator
    U =	{{1,0,0,0},
	 {0,1,0,0},
	 {0,0,1,0},
	 {0,0,0,std::exp(i*theta)}};

    //Set constructed to false
    constructed = false;

    this->N = N;
    this->qbit.push_back(controlbit);
    this->qbit.push_back(qbit);
}


