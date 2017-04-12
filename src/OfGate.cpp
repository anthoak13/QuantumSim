
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
    	O.push_back(vecComplex(kMax, 0));

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
		O.at(k).at(k) = 1;
	    else
	    {
		uint j = (A*f) % C;
		//std::cout << "New f' is " << j;
		//add the l half to j to get index
		for(int l = sizeM; l < N; l++)
		    j += (k & (1 << l));


		//std::cout << " and new j is " << j << std::endl;
		O.at(j).at(k) = 1;
		
	    }
	
	}
	else //if controlL is zero
	{
	    //std::cout << "Control l is zero" << std::endl;
	    O.at(k).at(k) = 1;
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

complex OfGate::at(int i, int j)
{
    return O.at(i).at(j);
}
