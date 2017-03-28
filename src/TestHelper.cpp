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


//Implimentation of the TestHelper class

#include "TestHelper.h"

void TestHelper::runTest(std::function<void(QuantumRegister&)> test,
			 QuantumRegister& reg, int n, bool verbose)
{
    //run the test
    test(reg);

    //Create vector to store the number of times
    //each state is measured
    vecUint results;
    
    //make n measurements and record the number of times
    //each result occurs
    for(int i = 0; i < n; i++)
    {
	//make measurement
	uint r = reg.measure();
	//make sure array is large enough to store the measurement
	while( results.size() <= r)
	    results.push_back(0);

	//Actually record the measurement
	results.at(r)++;

	//if verbose print out state
	if(verbose)
	{
	    std::cout << r << ":";
	    printState(r, reg.size());
	    std::cout << std::endl;
	}
    }

    //Print out a summary of the results
    printResults(results, reg.size());
}

void TestHelper::printResults(const vecUint& results, const ubyte N)
{
    //figure out the total number of measurements
    //performed
    int totalM = 0;
    for(auto elem : results)
	totalM += elem;

    //Print out header
    std::cout << "State : Probability" << std::endl;

    //Print out the summary of the results
    for(uint i = 0; i < results.size(); i++)
    {
	if(results.at(i) == 0)
	    continue;
	
	printState(i, N);
	std::cout << ": " << results.at(i)/(double) totalM
		  << std::endl;
    }
    
}

void TestHelper::printState(const vecBool& state)
{
    std::cout << "|";
    for(int i = state.size() - 1; i>=0; i--)
	std::cout << state[i];
    std::cout << ">";
}

void TestHelper::printState(uint state, ubyte N)
{
    vecBool temp(N,0);

    //get binary representation of state
    for( int i = 0; i < N; i++)
    {
	temp.at(i) = (state & 1);
	state >>= 1;
    }

    //actually print the state
    printState(temp);
}

