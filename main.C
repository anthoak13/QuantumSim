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
void ShorAlg(QuantumRegister& reg);
void test1(QuantumRegister& reg);

const double PI  =3.141592653589793238463;

using Clock = std::chrono::high_resolution_clock;
using uint = unsigned int;

int main(int argc, char **argv)
{
    //create register initially in |000>
    QuantumRegister reg(7);
    reg.prepareState(1);

    //run tests
    TestHelper::runTest(test1, reg, 1000, false);

    //rerun test, performing mod operations
    TestHelper::runTest(ShorAlg, reg, 1000, false);

    //re-run the test, should be 50/50 |000>/|100>
    //TestHelper::runTest(GroverAlg, reg, 1000, false);

    return 0;
}

void ShorAlg(QuantumRegister& reg)
{
    //Create gates to find f(x)
    std::vector<OfGate*> a;
    std::vector<Operator*> H;
    for(int i = 0; i < 3; i++)
    {
	a.push_back(new OfGate(15,3,4,7,i));
	H.push_back(new OHadamard(i+4,7));
    }

    std::cout << "Building operators..." << std::endl;
    for(int i = 0; i < 3; i++)
	a.at(i)->construct();

    std::cout << "Putting x in superposition..." << std::endl;
    //Put x-register into a superposition
    for(auto&& gate : H)
	reg.apply(gate);
    
    std::cout << "Doing multiplication..." << std::endl;
    //Perform multiplication on f-register
    for(auto&& gate : a)
	reg.apply(gate);
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
void test1(QuantumRegister& reg)
{

}
