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


//implimentation for the N-bit J operator

#include "OGateArray.h"

OGateArray::OGateArray(ubyte N)
{
    this->N = N;
    this->empty = true;

    for(int i = 0; i < this->size(); i++)
#ifndef SPARSE
	O.push_back(vecComplex(this->size()));
#else
        O.push_back(vecComplexPair());
#endif
}

complex OGateArray::at(int a, int b)
{
#ifndef SPARSE
    return O.at(a).at(b);
#else
    for(auto&& elem : O.at(a))
	if(elem.first == b)
	    return elem.second;
    //If it wasn't found, just return
    return 0;
#endif
}

void OGateArray::addGate(Operator* G)
{
    if(empty)
    {
#ifndef SPARSE
	//Go through and copy the gate
	for(int i = 0; i < this->size(); i++)
	    for(int j = 0; j < this->size(); j++)
		O.at(i).at(j) = G->at(i,j);
#else
	//Loop through and copy the gate
	for(int i = 0; i < this->size(); i++)
	    for(auto& pair : G->getMatrix().at(i))
		O.at(i).push_back(complexPair(pair));
#endif
	empty = false;
    }
    else //Multiply in new gate
    {
	auto temp = O;

#ifndef SPARSE
	for(int i = 0; i < this->size(); i++)
	    for(int k = 0; i < this->size(); i++)
	    {
		O.at(i).at(k) = 0;
		for(int j = 0; i < this->size(); i++)
		    O.at(i).at(k) += temp.at(i).at(j) * G->at(j,k);
	    }
#else
	//Start by examining row i
	for(int i = 0; i < this->size(); i++)
	{
	    O.at(i) = vecComplexPair{};
	    for(int k = 0; k <this->size(); k++)
	    {
		auto newVal = complex(0,0);
		for(auto&& aPair : G->getMatrix().at(i))
		{
		    //Look to see of applied matrix has something
		    //to multiply by
		    for(auto&& bPair :
			    temp.at(aPair.first))
			if(bPair.first == k)
			    newVal += aPair.second * bPair.second;
		    
		    
		}
		//Push the new value back
		O.at(i).push_back(complexPair(k,newVal));
	    }
	}
#endif
    }
}
