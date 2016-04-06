#ifndef _RMQ_big_
#define _RMQ_big_

#include "RMQ.hpp"
#include "log.hpp"
using namespace std;


class RMQ_big : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_big(DT* a,int n);
	~RMQ_big();


protected:
	// array
	int** table;
	DT* a;
	
	int n;
	int h;
	

};

#endif
