Different implementations of Range minimum query

	RMQ_triv			
		preprocess: O(1)
		query: O(n)
		idea: linear search
		
	RMQ_big				
		preprocess: O(nlogn)
		query: O(1)
		idea: compute minimum for every 2^i interval 
	RMQ_fast			
		preprocess: O(n)
		query: O(logn)
		idea: devide into blocks of n/logn length
	RMQ_fast2			
		preprocess: O(n)
		query: O(logn)
		idea: similiar to fast but includes prefix / sufix minimum of each block
	RMQ_seg				
		preprocess: O(n)
		query: O(logn)
		idea: segment tree
	RMG_segu			
		preprocess: O(n)
		query: O(logn)
		idea: different segment tree
	RMQ_segA			
		preprocess: O(n)
		query: O(logn)
		idea: segment tree in array
	RMQ_segB			
		preprocess: O(n)
		query: O(logn)
		idea: segment tree in array with other operations
