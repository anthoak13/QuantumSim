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
    //Check if state is normalized, and if it isn't calculate
    //normalization parameter to adjust the state.
    double mag = 0;
    for(double elem : state)
	mag += elem * elem;
    if(mag != 1)
	mag = 1/std::sqrt(mag);
    
    for(int i = 0; i < reg.size(); i++)
    {
	reg.at(i) = mag * state.at(i);
    }
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
    double q = 0;

    //std::cout << "Value to compare to is " << r << std::endl;
    
    //Loop through every possible state and figure out which
    //state is valid.
    for(result = 0; result < reg.size(); result++)
    {
	double prob = reg.at(result) * reg.at(result);
	q += prob;
	//std::cout << "state,prob,reg:" << result << " "
	//	  << prob << " "<< reg.at(result)
	//	  << std::endl;
	if( r <= q)
	    break;
    }

    return result;
}

/*int QuantumRegister::measure(vecBool& state)
{
    int result = measure();
    int temp = result;

    //populate the passed state. state is in little-endian
    //format.
    for( int i = 0; i < N; i++)
    {
	if(state.size() > i)
	    state.at(i) = (temp & 1);
	else
	    state.push_back(temp & 1);
	temp >>= 1;
    }

    return result;
    }*/

void QuantumRegister::collapse()
{
    int result = measure();
    for(int i = 0; i < reg.size(); i++)
	reg.at(i) = ( i == result) ? 1 : 0;
}

void QuantumRegister::apply(Operator* O)
{
    auto temp = reg;

    //usig new_i = O_{i,j}old_j
    for(int i = 0; i < reg.size(); i++)
    {
	reg.at(i) = 0;
	for(int j = 0; j < reg.size(); j++)
	    reg.at(i) += O->at(i,j)*temp.at(j);
    }
}
    

void QuantumRegister::init()
{
    rnd = std::mt19937_64{rd()};
    dist = std::uniform_real_distribution<>(0,1);
    reg = vecDouble(std::pow(2,N),0);
    reg[0] = 1;
}

