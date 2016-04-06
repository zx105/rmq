#ifndef _RMQ_segB_
#define _RMQ_segB_

#include "RMQ.hpp"
#include "log.hpp"
using namespace std;

struct tup{
	int index;
	int add;
	int value;
	tup(int min,int value,int a) : index(min), value(value), add(a) {}
	tup() {}
};

class RMQ_segB : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_segB(DT* a,int n);
	void add(int i,int j,int x);
	int value(int i);
	~RMQ_segB();


protected:
	// array
	tup* a;
	
	int n;
	int h;
	
	static const int MAX = (1ll<<31)-1;
	

};

#endif
