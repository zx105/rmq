#ifndef _RMQ_segu_
#define _RMQ_segu_

#include "RMQ.hpp"
using namespace std;


struct node{
	node *left,*right;
	int index;
	node(node *l,node *r,int i) : left(l),right(r),index(i) {}
};

class RMQ_segu : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_segu(DT* a,int c);
	~RMQ_segu();


protected:
	// array
	DT* a;
	node* root;
	int n;
	int h;

};

#endif
