#include "RMQ_fast.hpp"

#include <cstdio>
RMQ_fast::RMQ_fast(DT* b,int n) {
	this->a = b;
	this->n = n;
	block_size = log2fast(n)/2;
	if(block_size<1) block_size=1;
	int block_count = round_up(n,block_size);
	h = log2fast(block_count)+1;
	// allocate
	table = new int*[h];
	for(int i=0;i<h;++i) {
		table[i] = new int[block_count];
	}
	// process blocks (create first row of the table)
	for(int i=0;i<block_count;++i) {
		int min = i*block_size;
		for(int j=i*block_size+1;(j<(i+1)*block_size) && (j<n);++j) {
			min = a[j] < a[min]?j:min;
		}
		table[0][i] = min;
	}
	
	// create table = i-th row j-th colomn = min <j*block_size,j+2^i*block_size)
	for(int i=0;i<h-1;++i) {
		int offset = 1<<i;
		for(int j=0;j<block_count;++j) {
			if(j+2*offset>block_count) break;
			table[i+1][j] = a[table[i][j+offset]] < a[table[i][j]]?table[i][j+offset]:table[i][j];
		}
	}
}
DTidx RMQ_fast::query(DTidx i, DTidx j) {
	int block_i = i/block_size;
	int block_j = j/block_size;
	int min;
	// same block case
	if(block_i==block_j) {
		min=i;
		for(int k=i+1;k<=j;++k) min = a[k]<a[min]?k:min;
		return min;
	}
	min = i;
	// handle left-most incomplete block
	for(int k=i+1;k<(block_i+1)*block_size;++k) min = a[k]<a[min]?k:min;
	// compute minimum of full blocks
	if(block_j-block_i>1) {
		int l = log2fast(block_j-block_i-2);
		int offset = (1<<l)-1;
		int min2 = a[table[l][block_j-1-offset]] < a[table[l][block_i+1]]?table[l][block_j-1-offset]:table[l][block_i+1];
		min = a[min2]<a[min]?min2:min;
	}
	// handle right-most incomplete block
	for(int k=block_j*block_size;k<=j;++k) min = a[k]<a[min]?k:min;
	
	return min;
}
RMQ_fast::~RMQ_fast() {
	for(int i=0;i<h;++i) {
		delete[] table[i];
	}
	delete[] table;
}

