#ifndef _RMQ_seg_
#define _RMQ_seg_

#include "RMQ_segu.hpp"

#include "RMQ.hpp"
using namespace std;


/*
struct node{
	node *left,*right;
	int index;
	node(node *l,node *r,int i) : left(l),right(r),index(i) {}
};*/

class RMQ_seg : public RMQ {
public:
	
	virtual DTidx query(DTidx, DTidx);

	RMQ_seg(DT* a,int c);
	int sup_query(node* root,int b,int e,int ib,int ie);
	node* construct_tree(int b,int e);
	~RMQ_seg();

protected:
	// array
	DT* a;
	node* root;
	int n;
};

#endif
