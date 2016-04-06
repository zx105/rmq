#ifndef _RMQ_segA_
#define _RMQ_segA_

#include "RMQ.hpp"
using namespace std;


class RMQ_segA : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_segA(DT* a,int c);
	~RMQ_segA();


protected:
	// array
	DT* a;
	int* tree;
	int n;
	int l;

};

#endif
