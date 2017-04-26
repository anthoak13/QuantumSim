
#include "QFourierTrans.h"

QFourierTrans::QFourierTrans(const ubyte Nin, const ubyte Lin) :
    N(Nin), L(Lin)
{
    ubyte M = N-L;
    //Construct the transform based on L

    //Add the base case first
    //transform.push_back(new OHadamard(L-1 + M, N));

    //Loop though the rest of the cases
    for(int k = 0; k < L; k++)
    {
	//First figure out which qbit is controlling all of
	//the phase shift gates
	int ctrBit =  k + M;
    
	//loop though and add the controlled gates to the
	//transform
	double phase = PI/(1 << (k));
	for(int i = 0; i < k; i++)
	{
	    transform.push_back(
		new OCPhaseShift(phase, ctrBit, i+k+M, N));
	    transform.back()->construct();

	    //std::cout << "Creating phase gate: " << phase << " "
	    //<< ctrBit << " " << M + i << " " << N
	    //<< std::endl;
	    
	    phase *= 2;
	}

	//Add the Hadamard gate
	transform.push_back(new OHadamard(k + M, N));
	transform.back()->construct();
	//std::cout << "Creating OHad at " << k+M << std::endl;
    }
}

QFourierTrans::~QFourierTrans()
{
    for(auto&& gate : transform)
	delete gate;
    
}

void QFourierTrans::apply(QuantumRegister& reg)
{
    for(auto it = transform.begin(); it != transform.end(); it++)
	reg.apply(*it);
}

void QFourierTrans::applyInverse(QuantumRegister& reg)
{
    for(auto it = transform.rbegin(); it != transform.rend(); it++)
	reg.apply(*it);
}
