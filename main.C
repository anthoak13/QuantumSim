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

#include <chrono>
#include <iostream>
#include "QuantumRegister.h"
#include "TestHelper.h"
#include "Operators.h"


//forward decl
void printState(const vecBool& state);
void GroverAlg(QuantumRegister& reg);
void ShorAlg(uint C, uint a, QuantumRegister& reg,
	     uint fRegSize = 0);
void empty(QuantumRegister& reg);

const double PI  =3.141592653589793238463;

using Clock = std::chrono::high_resolution_clock;
using uint = unsigned int;

int main(int argc, char **argv)
{
    //create register initially in |000>
    QuantumRegister reg(7);
    reg.prepareState(1);

    //run tests
    TestHelper::runTest(empty, reg, 1000, false);

    ShorAlg(15,7,reg, 4);
    
    //rerun test, performing mod operations
    TestHelper::runTest(empty, reg, 1000, false);

    //re-run the test, should be 50/50 |000>/|100>
    //TestHelper::runTest(GroverAlg, reg, 1000, false);

    return 0;
}

void ShorAlg(uint C, uint a, QuantumRegister& reg, uint fRegSize)
{
    //Setup constants
    //If fReg wasn't definied, select it to be greater than the theoretical minimum required
    //2^fReg >= C
    fRegSize = (fRegSize == 0) ? std::ceil(std::log(C)/std::log(2)) : fRegSize;
    uint xRegSize = reg.size() - fRegSize;
    
    //Create gates for Shor
    std::vector<OfGate*> aGates;
    std::vector<OGenerating*> H;
    std::vector<OGenerating*> RGates;
    for(int i = 0; i < xRegSize; i++)
    {
	//std::cout << C << " " << xRegSize << " " << fRegSize
	//	  << " " << a << " " << i << std::endl;
	aGates.push_back(new OfGate(C,xRegSize,fRegSize,a,i));
	H.push_back(new OHadamard(i+fRegSize,reg.size()));
    }
    
    //Create controlled R gates
    RGates.push_back(new OCPhaseShift(PI/2, 6, 5, 7));
    RGates.push_back(new OCPhaseShift(PI/4, 6, 4, 7));
    RGates.push_back(new OCPhaseShift(PI/2, 5, 4, 7));

    //Construct the operators
    std::cout << "Building gates..." << std::endl;
    for(int i = 0; i < xRegSize; i++)
    {
	aGates.at(i)->construct();
	H.at(i)->construct();
    }
    for(auto&& gate : RGates)
	gate->construct();

    //Actually begin the calculation
    std::cout << "Putting x in superposition..." << std::endl;
    for(auto&& gate : H)
	reg.apply(gate);
    
    std::cout << "Doing multiplication..." << std::endl;
    for(auto&& gate : aGates)
	reg.apply(gate);

    //Apply IQFT
    std::cout << "Applying IQFT..." << std::endl;
    reg.apply(H.at(2));
    reg.apply(RGates[0]);
    reg.apply(RGates[1]);
    reg.apply(H[1]);
    reg.apply(RGates[2]);
    reg.apply(H[0]);

    //Cleanup gates
    for(auto&& gate : aGates)
	delete gate;
    for(auto&& gate : H)
	delete gate;
    for(auto&& gate : RGates)
	delete gate;
}

void GroverAlg(QuantumRegister& reg)
{
    
    const ubyte N = reg.size();
    const uint soln = 41;
    uint numRep = std::floor(PI/4*std::sqrt(1 << N));
    numRep += 0;
    std::cout << "Running Grover's " << numRep << " times."
	      << std::endl;
    
    auto start = Clock::now();
    //Create operators
    std::vector<Operator*> HOpps;
    for(int i = 0; i < N; i++)
	HOpps.push_back(new OHadamard(i+1,N));

    //2 is the correct answer
    Operator* Oracle = new OOracle(soln,N);
    Operator* J = new OJGrover(N);

    //Setup the system in a complete mixed state
    for(int i = 0; i < N; i++)
	reg.apply(HOpps.at(i));

    //Repeat grover's numRep times
    for(uint i = 0; i < numRep; i++)
    {
	//apply the oracale opp
	reg.apply(Oracle);

	//Apply all of the Hadamard gates
	for(int i = 0; i < N; i++)
	    reg.apply(HOpps.at(i));

	//Apply diffusion operator
	reg.apply(J);

	//Apply Hadamard gates again
	for(int i = 0; i < N; i++)
	    reg.apply(HOpps.at(i));
    }

    auto stop = Clock::now();
    std::cout << "Algorithm took "<<
	std::chrono::duration_cast<std::chrono::milliseconds>(
	    stop - start).count() << " ms" << std::endl;

    delete J;
    delete Oracle;
    for(int i = 0; i < N; i++)
	delete HOpps.at(i);

}
void empty(QuantumRegister& reg)
{

}
