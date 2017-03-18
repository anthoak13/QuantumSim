
//Implimentation of the TestHelper class

#include "TestHelper.h"

void TestHelper::runTest(std::function<void(QuantumRegister&)> test,
			 QuantumRegister& reg, int n)
{
    test(reg);

    //Create vector to store the number of times
    //each state is measured
    vecInt results;
    
    //make n measurements and record t
    for(int i = 0; i < n; i++)
    {
	//make measurement
	int r = reg.measure();
	//make sure array is large enough to store the measurement
	while( results.size() <= r)
	    results.push_back(0);

	//Actually record the measurement
	results.at(r)++;
    }

    printResults(results);
}

void TestHelper::printResults(const vecInt& results)
{
    //figure out the total number of measurements
    //performed
    int totalM = 0;
    for(auto elem : results)
	totalM += elem;

    //Print out header
    std::cout << "State : Probability" << std::endl;
    for(int i = 0; i < results.size(); i++)
    {
	std::cout << i << ": " << results.at(i)/(double) totalM
		  << std::endl;
    }
    
}
