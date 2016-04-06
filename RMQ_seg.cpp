#include "RMQ_seg.hpp"
#include "RMQ_segu.hpp"

#include "log.hpp"
#include <cstdlib>

#define min(x,y) a[y]<a[x]?y:x

node* RMQ_seg::construct_tree(int b,int e) {
	if(e-b<3) return new node(NULL,NULL,min(b,e-1));
	node* r = new node(construct_tree(b,(b+e)/2),construct_tree((b+e)/2,e),0);
	r->index = min(r->left->index,r->right->index);
	return r;
}

RMQ_seg::RMQ_seg(DT* a,int c) {
	this->a = a;
	this->n = c;
	root = construct_tree(0,c);
}
// root, subtree begin, subtree end, interval begin, interval end  interval: <x,y)
int RMQ_seg::sup_query(node *root,int b,int e,int ib,int ie) {
	if(e<=ib || ie<b) return ib; // dont overleap? return left most element
	if(root==NULL) return b; // obvious
	if(b>=ib && e<ie) return root->index; // subinterval?
	int l = sup_query(root->left,b,(b+e)/2,ib,ie);
	int r = sup_query(root->right,(b+e)/2,e,ib,ie);
	return min(l,r);
}
	
DTidx RMQ_seg::query(DTidx i, DTidx j) {
	return sup_query(root,0,n,i,j);
}

void delete_node2(node* x) {
	if(x==NULL) return;
	delete_node2(x->left);
	delete_node2(x->right);
	delete x;
}

RMQ_seg::~RMQ_seg() {
	delete_node2(root);
}
	
