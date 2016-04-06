#include "RMQ_segB.hpp"

#include <cstdio>

RMQ_segB::RMQ_segB(DT* b,int c) {
	// we need 2 extra nodes
	int k = log2fast(c+1)+1;
	this->n = 1<<k;
	a = new tup[2*n];
	a[n] = tup(n,MAX,0);
	for(int i=1;i<=c;++i) a[i+n] = tup(i+n,b[i-1],0);
	for(int i=c+1;i<n;++i) a[i+n] = tup(i+n,MAX,0);
	for(int i=n-1;i>=1;--i) {
		if(a[2*i+1].value<a[2*i].value) {
			a[i] = a[2*i+1];
		}
		else a[i] = a[2*i];
	}
}
DTidx RMQ_segB::query(DTidx i, DTidx j) {
	if(i==j) return i;
	int new_i = i+n;
	int new_j = j+n+2;
	int prefix_i = 0;
	int prefix_j = 0;
	int x = new_i;
	int y = new_j;
	// compute prefix sum of offsets
	while(x!=y) {
		prefix_i+= a[x].add;
		prefix_j+= a[y].add;
		x>>=1; y>>=1;
	}
	int left_min_value=MAX,left_min_index;
	int right_min_value=MAX,right_min_index;
	while(new_j-new_i>1) {
		// left son
		prefix_i-=a[new_i].add;
		if(new_i%2==0) {
			int r = a[new_i+1].value+a[new_i+1].add+prefix_i;
			if(r<left_min_value) {
				left_min_value = r;
				left_min_index = a[new_i+1].index;
			}
		}
		//right son
		prefix_j-=a[new_j].add;
		if(new_j%2==1) {
			int l = a[new_j-1].value+a[new_j-1].add+prefix_j;
			if(l<=right_min_value) {
				right_min_value = l;
				right_min_index = a[new_j-1].index;
			}
		}
		new_i>>=1;
		new_j>>=1;
	}
	return right_min_value<left_min_value?right_min_index-n-1:left_min_index-n-1;
}
void RMQ_segB::add(int i,int j,int x) {
	if(i==j) a[n+i+1].value+=x;
	else {
		int new_i = n+i;
		int new_j = n+j+2;
		while(new_j-new_i>1) {
			if(new_i%2==0) {
				a[new_i+1].add+=x;
				int l = a[new_i].add+a[new_i].value;
				int r = a[new_i+1].add+a[new_i+1].value;
				if(r<l) {
					a[new_i/2].value = r;
					a[new_i/2].index = a[new_i+1].index;
				}
				else {
					a[new_i/2].value = l;
					a[new_i/2].index = a[new_i].index;
				}
			}
			if(new_j%2==1) {
				a[new_j-1].add+=x;
				int l = a[new_j-1].add+a[new_j-1].value;
				int r = a[new_j].add+a[new_j].value;
				if(r<l) {
					a[new_j/2].value = r;
					a[new_j/2].index = a[new_j].index;
				}
				else {
					a[new_j/2].value = l;
					a[new_j/2].index = a[new_j-1].index;
				}
			}
			new_i>>=1;
			new_j>>=1;
		}
	}
}

int RMQ_segB::value(int i) {
	int index = i+n+1;
	int value = a[index].value;
	while(index!=1) {
		value+=a[index].add;
		index>>=1;
	}
	return value;
}

RMQ_segB::~RMQ_segB() {
	delete[] a;
}

