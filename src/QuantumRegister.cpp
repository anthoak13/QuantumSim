
#include "QuantumRegister.h"

QuantumRegister::QuantumRegister()
{
    init();
}

QuantumRegister::QuantumRegister(const vecBool& state)
{
    init();
    prepareState(state);
}

QuantumRegister::QuantumRegister(const vecDouble& state)
{
    init();
    prepareState(state);
}

void QuantumRegister::prepareState(const vecDouble& state)
{
    for(int i = 0; i < reg.size(); i++)
	reg.at(i) = state.at(i);
}

void QuantumRegister::prepareState(const vecBool& state)
{
    for(int i = 0; i < reg.size(); i++)
	reg.at(i) = state.at(i);
}

int QuantumRegister::measure()
{
    int result = 0;

    //Get a randum number between 0 and 1;
    double r = dist(rnd);
    //q tracks the current value to compare our rnd
    //number against. when r < q then we have found
    //our state.
    long q = 0;

    std::cout << "Value to compare to is " << r << std::endl;
    
    //Loop through every possible state and figure out which
    //state is valid.
    for(result = 0; result < reg.size(); result++)
    {
	q += reg.at(result);
	if( r <= q)
	    break;
    }

    return result;
}

int QuantumRegister::measure(vecBool& state)
{
    int result = measure();
    int temp = result;

    //populate the passed state
    for( int i = 0; i < N; i++)
    {
    std::cout << "Filling " << i << " with " <<
    (temp & 1) << std::endl;
	if(state.size() > i)
	    state.at(i) = (temp & 1);
	else
	    state.push_back(temp & 1);
	temp >>= 1;
    }

    return result;
}

void QuantumRegister::collapse()
{
    int result = measure();
    for(int i = 0; i < reg.size(); i++)
	reg.at(i) = ( i == result) ? 1 : 0;
}
    

void QuantumRegister::init()
{
    rnd = std::mt19937_64{rd()};
    dist = std::uniform_real_distribution<>(0,1);
    reg = vecDouble(std::pow(2,N),0);
    reg[0] = 1;
}
