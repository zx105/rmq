#include <cstdlib>
#include <chrono>
#include <cstring>
#include <fstream>
#include <utility>
#include <vector>
#include <random>
#include "RMQ_triv.hpp"
#include "RMQ_big.hpp"
#include "RMQ_fast.hpp"
#include "RMQ_fast2.hpp"
#include "RMQ_segu.hpp"
#include "RMQ_seg.hpp"
#include "RMQ_segA.hpp"
#include "RMQ_segB.hpp"
using namespace std;

#define FOR(i,n) for(int i=0;i<n;++i)

RMQ* get_algorithm(char *s,int* data,int n) {
	if(strcmp(s,"TRIV")==0) {
		return new RMQ_triv(data);
	} else if(strcmp(s,"BIG")==0) {
		return new RMQ_big(data,n);
	} else if(strcmp(s,"FAST")==0) {
		return new RMQ_fast(data,n);
	} else if(strcmp(s,"FAST2")==0) {
		return new RMQ_fast2(data,n);
	} else if(strcmp(s,"SEG")==0) {
		return new RMQ_seg(data,n);
	} else if(strcmp(s,"SEGU")==0) {
		return new RMQ_segu(data,n);
	} else if(strcmp(s,"SEGA")==0) {
		return new RMQ_segA(data,n);
	} else if(strcmp(s,"SEGB")==0) {
		return new RMQ_segB(data,n);
	}
	else return NULL;
}

main(int argc, char* argv[]) {
	if(argc<2) {
		printf("Usage: %s SHOW ALG datafile queryfile \n",argv[0]); // 5
		printf("Usage: %s TEST ALG datafile queryfile query_rounds\n",argv[0]); // 6
		printf("Usage: %s SHOW ALG n m k seed\n",argv[0]); // 7
		printf("Usage: %s TEST ALG n m k seed query_rounds\n",argv[0]); // 8
		return 0;
	}
	vector<int> data;
	vector<pair<int,int> > queries;
	int rounds = -1;

	if((strcmp(argv[1],"SHOW")==0 && argc==5) ||(strcmp(argv[1],"TEST")==0 && argc==6)) {
		ifstream ifs(argv[3]);
		if(!ifs.is_open()) {
			printf("Wrong data file %s\n",argv[3]);
			return 0;
		}
		int x,y;
		while(ifs >> x) {
			data.push_back(x);
		}
		ifs.close();
		ifs.open(argv[4]);
		if(!ifs.is_open()) {
			printf("Wrong queries file %s\n",argv[4]);
			return 0;
		}
		while(ifs >> x >> y) queries.push_back(make_pair(x,y));
		ifs.close();
		if(strcmp(argv[1],"TEST")==0) {
			rounds = atoi(argv[5]);
		}
	}
	else {
		if(!((strcmp(argv[1],"SHOW")==0 && argc==7) ||(strcmp(argv[1],"TEST")==0 && argc==8))) {
			printf("Usage: %s SHOW ALG datafile queryfile \n",argv[0]); // 5
			printf("Usage: %s TEST ALG datafile queryfile query_rounds\n",argv[0]); // 6
			printf("Usage: %s SHOW ALG n m k seed\n",argv[0]); // 6
			printf("Usage: %s TEST ALG n m k seed query_rounds\n",argv[0]); // 7
			return 0;
		}
		
		mt19937 g(atoi(argv[6]));
		int n = atoi(argv[3]);
		int m = atoi(argv[4]);
		int k = atoi(argv[5]);
		FOR(i,n) {
			data.push_back(g());
		}
		FOR(i,m) {
			int a = g()%(n-k);
			queries.push_back(make_pair(a,a+k));
		}
		if(strcmp(argv[1],"TEST")==0) {
			rounds = atoi(argv[7]);
		}
	}
	

	RMQ *r;
	
	auto start = std::chrono::high_resolution_clock::now();
	r = get_algorithm(argv[2],data.data(),data.size());
	auto end = std::chrono::high_resolution_clock::now();
	
	if(r==NULL) {
		printf("Wrong algorithm\n");
		printf("Try: TRIV BIG FAST FAST2 SEG SEGU SEGA SEGB FH NLOGN\n");
		return 0;
	}
	
	if(strcmp(argv[1],"TEST")==0) printf("%12s %lldms\n","preprocess:",chrono::duration_cast<chrono::milliseconds>(end-start).count());
	
	
	if(strcmp(argv[1],"SHOW")==0) {
		FOR(i,queries.size()) {
			printf("%d\n",r->query(queries[i].first,queries[i].second));
		}
	}
	else {
		auto start = std::chrono::high_resolution_clock::now();
		FOR(j,rounds) {
			FOR(i,queries.size()) {
				volatile int x = r->query(queries[i].first,queries[i].second);
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		printf("%12s %lfms\n","query:",((double)chrono::duration_cast<chrono::milliseconds>(end-start).count())/rounds);
	}
	delete r;
	

		
}
