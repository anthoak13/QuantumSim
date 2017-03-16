
//This class simulates and stores a 3-bit quantum register

#ifndef QUANTUMREGISTER_H
#define QUANTUMREGISTER_H


#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

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
    //returns the state and base 10 and populates the
    //vector that is passed by reference.
    int measure(vecBool& state);

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
