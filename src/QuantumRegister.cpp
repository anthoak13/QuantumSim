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

QuantumRegister::QuantumRegister(const ubyte Nin) :
    N(Nin) 
{
    init();
}

void QuantumRegister::prepareState(const vecComplex& state)
{
    //Check if state is normalized, and if it isn't calculate
    //normalization parameter to adjust the state.
    double mag = 0;
    for(auto&& elem : state)
	mag += std::abs(elem) * std::abs(elem);
    if(mag != 1)
	mag = 1/std::sqrt(mag);
    
    for(int i = 0; i < reg.size(); i++)
    {
	reg.at(i) = mag * state.at(i);
    }
}
void QuantumRegister::prepareState(const uint state)
{
    for(uint i = 0; i < reg.size(); i++)
	reg.at(i) = (i == state);
}

uint QuantumRegister::measure()
{
    uint result = 0;

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
	double prob = std::pow(std::abs(reg.at(result)),2);
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
    uint result = measure();
    for(uint i = 0; i < reg.size(); i++)
	reg.at(i) = (i == result);
}

void QuantumRegister::apply(Operator* O)
{
    auto temp = reg;
    auto Opp = O->getMatrix();
    //usig new_i = O_{i,j}old_j
    //std::cout << "Reg size is " << reg.size() << std::endl;

    for(uint i = 0; i < reg.size(); i++)
    {
	reg.at(i) = 0;
	
#ifndef SPARSE
	//Do full matrix mult
	for(uint j = 0; j < reg.size(); j++)
	    if(O->at(i,j) != complex(0,0) &&
	       temp.at(j) != complex(0,0))
		reg.at(i) += O->at(i,j)*temp.at(j);
#else
	//get row from the vector of pairs
	for(auto& row : Opp.at(i))
	    //DO multiplication if register isn't zero
	    if(temp.at(row.first) != complex(0,0))
		reg.at(i) += row.second * temp.at(row.first);
	    
#endif
    }
}
    

void QuantumRegister::init()
{
    rnd = std::mt19937_64{rd()};
    dist = std::uniform_real_distribution<>(0,1);
    reg = vecComplex(std::pow(2,N),0);
    reg[0] = 1;
}

