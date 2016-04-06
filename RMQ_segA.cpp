#include "RMQ_segA.hpp"
#include "log.hpp"

#include <cstdio>
RMQ_segA::RMQ_segA(DT* a,int c) {
	this->a = a;
	this->n = c;
	this->l = 1<<(log2fast(n-1)+1);
	tree = new int[l];
	for(int i=0;i<n/2;++i) tree[l/2+i] = a[2*i+1] < a[2*i]?2*i+1:2*i;
	if(n%2==1) tree[l/2+n/2] = n-1;
	for(int i=l/2+(n+1)/2;i<l;++i) tree[i] = -1;
	for(int i=l/2-1;i>=1;--i) tree[i] = tree[2*i+1]==-1 || a[tree[2*i]]<=a[tree[2*i+1]]?tree[2*i]:tree[2*i+1];
	
	//for(int i=1;i<l;++i) printf("%d ",tree[i]);
	//printf("\n");
}
// bottom-up

DTidx RMQ_segA::query(DTidx i, DTidx j) {
	if(i==j) return i;
	// move begin and end "1 layer up" and open the interval // <x,y> -> (x,y)
	int new_i = l/2+i/2,new_j = l/2+j/2;
	int left_min=-1,right_min=-1;
	// while left subtree and rightsubtree dont have common parent
	while(new_j-new_i>1) {
		// left subtree case -> process right subtree to answer
		if(new_i%2==0) left_min = left_min==-1 || a[tree[new_i+1]]<a[left_min]?tree[new_i+1]:left_min;
		// right subtree case -> process left subtree to answer
		if(new_j%2==1) right_min = right_min==-1 || a[tree[new_j-1]]<=a[right_min]?tree[new_j-1]:right_min;
		new_i>>=1;
		new_j>>=1;
	}
	// merge answer from subtrees
	int min = left_min==-1 || right_min==-1?left_min==-1?right_min:left_min:a[right_min]<a[left_min]?right_min:left_min;
	int left = i%2==0?tree[i/2+l/2]:i; // process left interval boundary
	int right = j%2==1?tree[j/2+l/2]:j; // process right interval boundary 
	min = min==-1 || a[left]<=a[min]?left:min; // merge answers
	return a[right]<a[min]?right:min;
}
// top-down
/*
DTidx RMQ_segA::query(DTidx i,DTidx j) {
	if(i==j) return i;
	if(j-i==1) return a[j]<a[i]?j:i;
	// delete "half" intervals
	int n_i = i%2==1?i+1:i;
	int n_j = j%2==1?j:j-1;
	int x = log2fast((~n_i)&n_j);
	int lca = (n_i+l)>>(x+1);
	// if LCA is on the bottom layer
	if(lca>=l/2) {
		int min = tree[lca];
		if(i%2==1) min = a[i]<=a[min]?i:min;
		if(j%2==0) min = a[j]<a[min]?j:min;
		return min;
	}
	// travers left subtree
	int left_min = -1,index = 2*lca;
	int offset=1<<(x-1);
	while(index<l/2) {
		index*=2;
		// check if begining of the interval is on the left
		if((n_i&offset)==0) {
			// process right subtree
			left_min = left_min==-1 || a[tree[index+1]]<=a[left_min]?tree[index+1]:left_min;
		} else index+=1;
		offset>>=1;
	}
	// process last element
	left_min = left_min==-1 || a[tree[index]]<=a[left_min]?tree[index]:left_min;
	
	int right_min = -1;
	index = 2*lca+1;
	offset=1<<(x-1);
	// travers right subtree
	while(index<l/2) {
		index*=2;
		// check is end of the interval is on the right
		if((n_j&offset)>0) {
			// process left subtree
			right_min = right_min==-1 || a[tree[index]]<a[right_min]?tree[index]:right_min;
			index+=1;
		}
		offset>>=1;
	}
	// merge answers from "half" intervals and subtrees
	right_min = right_min==-1 || a[tree[index]]<a[right_min]?tree[index]:right_min;
	int min = a[left_min]<=a[right_min]?left_min:right_min;
	if(i%2==1) min = a[i]<=a[min]?i:min;
	if(j%2==0) min = a[j]<a[min]?j:min;
	return min;
}*/

RMQ_segA::~RMQ_segA() {
	delete[] tree;
}