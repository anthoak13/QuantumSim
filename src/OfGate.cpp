
#include "OfGate.h"

OfGate::OfGate(uint numToFactor, ubyte numL, ubyte numM,
	   uint a, ubyte controlL)
{
    //Set constructed to false
    constructed = false;

    sizeL = numL;
    sizeM = numM;
    C = numToFactor;
    this->a = a;
    this->N = numL + numM;
    this->controlL = controlL;
}

void OfGate::construct()
{
    int kMax = 1 << N;
   
    //Initialize an empty kXk matrix
    for(int i = 0; i < kMax; i++)
#ifndef SPARSE
    	O.push_back(vecComplex(kMax, 0));
#else
        O.push_back(vecComplexPair{});
#endif

   //Calcualte the A val to use and measure the quantum reg
    uint A;
    if(controlL == 0)
	A = a % C;
    else
	A = (uint)std::pow(a, 2*controlL) % C;

    //std::cout << "A is " << A << std::endl;
    //Loop through every column and place a 1 somewhere in
    //the column
    for(int k = 0; k < kMax; k++)
    {
	//std::cout << "K is " << k << std::endl;
	//If the control L is not zero
	if(k & (1 << (controlL + sizeM)) )
	{

	    //caulculate the f value
	    uint f = 0;
	    for(int m = 0; m <sizeM; m++)
		f += (k & (1 << m));

	    //std::cout << "control L is not zero and f is "
	    //	      << f << std::endl;
            //if f reg is >= C, put on the diagonal, otherwise
	    //calulate a new f val.
	    if(f >= C)
#ifndef SPARSE
		O.at(k).at(k) = 1;
#else
	        O.at(k).push_back(complexPair(k,1));
#endif
	    else
	    {
		uint j = (A*f) % C;
		//std::cout << "New f' is " << j;
		//add the l half to j to get index
		for(int l = sizeM; l < N; l++)
		    j += (k & (1 << l));


		//std::cout << " and new j is " << j << std::endl;
#ifndef SPARSE
		O.at(j).at(k) = 1;
#else
		O.at(j).push_back(complexPair(k,1));
#endif
		
	    }
	
	}
	else //if controlL is zero
	{
	    //std::cout << "Control l is zero" << std::endl;
#ifndef SPARSE
	    O.at(k).at(k) = 1;
#else
	    O.at(k).push_back(complexPair(k,1));
#endif
	}

    }//End loop through columns
/*
    for(auto&& row : O)
    {
	int sum = 0;
	for(auto&& elem : row)
	    std::cout << elem ;
        // sum += std::abs(elem);
	//std::cout << sum << std::endl;
	std::cout << std::endl;
	} */
    
    constructed = true;
}

complex OfGate::at(int a, int b)
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
