#ifndef _RMQ_fast_
#define _RMQ_fast_

#include "RMQ.hpp"
#include "log.hpp"
using namespace std;


class RMQ_fast : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_fast(DT* a,int n);
	~RMQ_fast();


protected:
	// array
	int** table;
	DT* a;
	
	int n;
	int h;
	int block_size;
	

};

#endif
