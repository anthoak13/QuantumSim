//This class simulates and stores a N-bit quantum register

#ifndef QUANTUMFOURIERTRANSFORM_H
#define QUANTUMFOURIERTRANSFORM_H


#include <algorithm>
#include <complex>
#include <iostream>
#include <random>
#include <vector>
#include "Operator.h"
#include "Operators.h"

using complex = std::complex<double>;
using vecComplex = std::vector<complex>;
using ubyte = unsigned char;
using uint = unsigned int;

class QFourierTrans
{
public:
    //Default constructor.
    QFourierTrans(const ubyte Nin, const ubyte L);

    ~QFourierTrans();
    
    //Applys the passed operator to the register
    void apply(QuantumRegister& reg);
    void applyInverse(QuantumRegister& reg);
    

private:
    const ubyte N;
    const ubyte L;
    const double PI  =3.141592653589793238463;
    
    std::vector<OGenerating*> transform;
};

#endif
