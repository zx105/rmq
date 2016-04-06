#ifndef _RMQ_hpp_
#define _RMQ_hpp_

#include <math.h>
#include <cstdlib>
typedef int DT;                 // use long for 64bit-version (but take care of fast log!)
typedef unsigned int DTidx;     // for indexing in arrays



/* Abstract class for RMQ-queries. Proprocessing is done
   in constructor. */
class RMQ {
public:
	// returns index of RMQ[i,j]
	virtual DTidx query(DTidx, DTidx) = 0;
	virtual ~RMQ() {}
};

#endif
