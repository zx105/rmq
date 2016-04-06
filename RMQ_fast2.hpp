#ifndef _RMQ_fast2_
#define _RMQ_fast2_

#include "RMQ.hpp"
#include "log.hpp"
using namespace std;


class RMQ_fast2 : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_fast2(DT* a,int n);
	~RMQ_fast2();


protected:
	// array
	int** table;
	DT* a;
	int* prefix;
	int* suffix;
	
	int n;
	int h;
	int block_size;
	

};

#endif
