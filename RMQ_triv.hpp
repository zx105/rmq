#ifndef _RMQ_triv_
#define _RMQ_triv_

#include "RMQ.hpp"
using namespace std;


class RMQ_triv : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_triv(DT* a);


protected:
	// array
	DT* a;

};

#endif
