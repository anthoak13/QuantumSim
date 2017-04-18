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


//Class that holds logic for generating N-sized gatesx
//H is the small matrix that the tensor products
//are applied to.

#include "OGenerating.h"

void OGenerating::print()
{
    construct();
    Operator::print();
}
complex OGenerating::at(int a, int b)
{
    if(!constructed)
	construct();
    //Code for sparce matrix
#ifdef SPARSE
    for(auto&& elem : O.at(a))
	if(elem.first == b)
	    return elem.second;
    //If it wasn't found, just return
    return 0;
#else
    //Code for full matrix
    return O.at(a).at(b);
#endif
}

void OGenerating::construct()
{
    //if the operator has already been created, skip
    if(constructed)
	return;
    // std::cout << "Constructing the operator " << (int)qbit.at(0)
    //<< "..." << std::endl;

    //The matrix is a 2^N square matrix
    uint size = 1 << N;
    
    //locOfBit is the bit that determines
    //the H matrix.
    //ie for H^(1) locOfBit is 2^2.
    uint locOfBit = 0;
    for(uint i = 0; i < qbit.size(); i++)
	locOfBit |= 1 << (qbit.at(i));
    

    //Loop through each row of the matrix
    for(uint i = 0; i < size; i++)
    {
        //Add a blank vector representing the row
#ifndef SPARSE
	O.push_back(vecComplex{});
#else
	O.push_back(vecComplexPair{});
#endif

	//Loop through each column
	//(i,j) are matrix element being calculated
	for(uint j = 0; j < size; j++)
	{
	    bool zero = false;
	   
            //Extract the individual bits
	    //Loop through and check to see if any delta
	    //is zero, if it is break the loop
	    for(uint k = 1;!zero && k < size; k <<= 1)
	    {
		//if k is locOfBit then skip, it isn't a delta
		if(!(k & locOfBit))
		    zero |= notKDelta(i & k, j & k);
	    }

	    //double negation fixes the result at 1 or 0,
	    //otherwise you can get any power of 2 (4 & 4 = 4).
#ifndef SPARSE
	    if(zero)
		O.at(i).push_back(0);
	    else
#endif
	    if(!zero)
	    {
                //Loop to calulate indices
		//std::cout << "Filling (" << i << "," << j << ") ";

		//i' and j' are the indices to pull the value from
		//H.
		uint iPrime = 0;
		uint jPrime = 0;

		//This calculates the indices
		for(uint k = 0; k < qbit.size(); k++)
		{
		    iPrime +=
			( !!(i & (1 << qbit.at(k))))
			<< (qbit.size() - 1 - k);
		    jPrime +=
			( !!(j & (1 << qbit.at(k))))
			<< (qbit.size() - 1 - k);
		}
		
		//std::cout << "jPrime = " << jPrime <<
		//    " iPrime = " << iPrime << std::endl;

		//Push back the proper term
#ifndef SPARSE
		O.at(i).push_back(U.at(iPrime)
				  .at(jPrime));
#else
	    O.at(i).push_back(complexPair(j, U.at(iPrime)
					  .at(jPrime)));
#endif
	    } //end else statement  
	} //Endl loop thorugh j
    } //end loop though i

    constructed = true;

    //std::cout << "Finish construciton";
    //print out the operator
    /*for(auto&& vec : O)
    {
	for(auto elem : vec)
	    std::cout << elem << " ";
	std::cout << std::endl;
    }*/
}
