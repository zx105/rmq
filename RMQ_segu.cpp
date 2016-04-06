#include "RMQ_segu.hpp"

#include "log.hpp"
#include <vector>
#include <cstdlib>
#include <cstdio>

RMQ_segu::RMQ_segu(DT* a,int c) {
	this->a = a;
	this->n = c;
	this->h = log2fast(n-1);
	vector<node*> v;
	for(int i=0;i<c/2;++i) {
		v.push_back(new node(NULL,NULL,a[2*i+1]<a[2*i]?2*i+1:2*i));
	}
	if(c%2==1) v.push_back(new node(NULL,NULL,c-1));
	while(v.size()>1) {
		vector<node*> b;
		for(int i=0;i<v.size()/2;++i) {
			b.push_back(new node(v[2*i],v[2*i+1],a[v[2*i+1]->index] < a[v[2*i]->index]?v[2*i+1]->index:v[2*i]->index));
		}
		if(v.size()%2==1) {
			b.push_back(v[v.size()-1]);
		}
		v.swap(b);
		b.clear();
	}
	root = v[0];
}
DTidx RMQ_segu::query(DTidx i, DTidx j) {
	if(i==j) return i;
	node* temp = root;
	int left = 0;
	int right = n;
	int mid = left + (1<<log2fast(right-left-1));
	while(j<mid || i>=mid) {
		// end of interval is in left subtree
		if(j<mid) {
			temp = temp->left;
			right = mid;
		}
		// begin of interval is in right subtree
		if(i>=mid) {
			temp = temp->right;
			left = mid;
		}
		mid = left + (1<<log2fast(right-left-1));
		
		
	}
	// leaf case
	if(temp->left==NULL) return temp->index;
	// not leaf, continue traversal
	int left_min = -1;
	int left_begin = left;
	int left_end = left + (1<<log2fast(right-left-1));
	node* left_subtree = temp->left;
	while(left_subtree->right!=NULL) {
		// begin is in the left subtree
		int left_mid = left_begin + (1<<log2fast(left_end-left_begin-1));
		if(i<left_mid) {
			// count right subtree and move left
			left_min = left_min==-1 || a[left_subtree->right->index] <= a[left_min]?left_subtree->right->index:left_min;
			left_subtree = left_subtree->left;
			left_end = left_mid;
		}
		else {
			// mvoe right
			left_begin=left_mid;
			left_subtree = left_subtree->right;
		}
	}
	// bottom layer case, handle interval of length 2
	int index = i%2==0?left_subtree->index:i;
	left_min = left_min==-1 || a[index]<=a[left_min]?index:left_min;
	
	int right_min = -1;
	int right_begin = left + (1<<log2fast(right-left-1));
	int right_end = right;
	node* right_subtree = temp->right;
	while(right_subtree->left!=NULL) {
		// end is in the right subtree
		int right_mid = right_begin + (1<<log2fast(right_end-right_begin-1));
		if(j>=right_mid) {
			// count left subtree
			// move to the right
			right_min = right_min==-1 || a[right_subtree->left->index]<a[right_min]?right_subtree->left->index:right_min;
			right_begin = right_mid;
			right_subtree = right_subtree->right;
		}
		else {
			// move to the left
			right_subtree = right_subtree->left;
			right_end = right_mid;
		}
	}
	// bottom layer case, handle interval of length 2
	index = j%2==0?j:right_subtree->index;
	right_min = right_min==-1 || a[index]<a[right_min]?index:right_min;
	return a[left_min]<=a[right_min]?left_min:right_min;
}

void delete_node(node* x) {
	if(x==NULL) return;
	delete_node(x->left);
	delete_node(x->right);
	delete x;
}


RMQ_segu::~RMQ_segu() {
	delete_node(root);
}
	
