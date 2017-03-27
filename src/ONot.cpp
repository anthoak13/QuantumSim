
#include "ONot.h"


ONot::ONot(ubyte controlBit, ubyte notBit, ubyte N)
{
    H = {{1, 0, 0, 0},
	 {0, 1, 0, 0},
	 {0, 0, 0, 1},
	 {0, 0, 1, 0}};

    constructed = false;

    this->N = N;
    qbit.push_back(controlBit);
    qbit.push_back(notBit);
}
