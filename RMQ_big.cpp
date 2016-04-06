#include "RMQ_big.hpp"

#include <cstdio>

RMQ_big::RMQ_big(DT* b,int n) {
	this->a = b;
	this->n = n;
	h = log2fast(n)+1;
	// allocate
	table = new int*[h];
	for(int i=0;i<h;++i) {
		table[i] = new int[n];
	}
	// create first for of the table
	for(int i=0;i<n;++i) table[0][i] = i;
	// table = i-th row, j-th colomn min <j,j+2^i)
	for(int i=0;i<h-1;++i) {
		int offset = 1<<i;
		for(int j=0;j<n;++j) {
			if(j+2*offset>n) break;
			table[i+1][j] = a[table[i][j+offset]] < a[table[i][j]]?table[i][j+offset]:table[i][j];
		}
	}
	
	
}
DTidx RMQ_big::query(DTidx i, DTidx j) {
	// compute larest power of 2
	int l = log2fast(j-i);
	int offset = (1<<l)-1;
	return a[table[l][j-offset]] < a[table[l][i]]?table[l][j-offset]:table[l][i];
}
RMQ_big::~RMQ_big() {
	for(int i=0;i<h;++i) {
		delete[] table[i];
	}
	delete[] table;
}

