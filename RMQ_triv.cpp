#include "RMQ_triv.hpp"

RMQ_triv::RMQ_triv(DT* a) {
	this->a = a;
}
DTidx RMQ_triv::query(DTidx i, DTidx j) {
	DTidx min = i;
	for(int k=i+1;k<=j;++k) {
		min = a[k]<a[min]?k:min;
	}
	return min;
}
