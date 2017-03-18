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


//This class simulates and stores a 3-bit quantum register

#ifndef QUANTUMREGISTER_H
#define QUANTUMREGISTER_H


#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "Operator.h"

using vecDouble = std::vector<double>;
using vecBool = std::vector<bool>;
using ubyte = unsigned char;

class QuantumRegister
{
public:
    //Default constucor. Prepares the system in the |0> state.
    QuantumRegister();
    //Constructor that prepares the system in the |state> state.
    QuantumRegister(const vecDouble& state);
    QuantumRegister(const vecBool& state);
    
    //Sets the state of the system to |state>.
    void prepareState(const vecDouble& state);
    void prepareState(const vecBool& state);

    //Collapses the wavefunction
    void collapse();

    //Measures the system w/o collapsing the wavefunction
    //returns the state in base 10 (5=>|011>, 7=>|111>, 2=>|010>) 
    int measure();

    //Applys the passed operator to the register
    void apply(Operator* O);
    
    int getSize() { return N; }

private:
    //function to setup the rnd number generator and
    //register
    void init();
    
    const ubyte N = 3;
    vecDouble reg;

    //classes for rnd number generator
    std::random_device rd;
    std::mt19937_64 rnd;
    std::uniform_real_distribution<> dist;
};

#endif
