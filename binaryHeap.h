/*
 * binaryHeap.h
 * created by: Jaspreet Bajwa
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>

#include "hnode.h"

class binaryHeap{

	std::vector<hnode const*> 			_heap;

	void 								percolateup(int i);
	void 								percolatedown(int i);
	int 								lchild(int i);
	int 								rchild(int i);
	int 								parent(int i);

public:
									
										binaryHeap();
										~binaryHeap();
										binaryHeap(std::vector<hnode const *> &numbers);
	void 								insert(hnode const* ele);
	hnode const* 						getmin();
	void 								deletemin();
	int 								size();
	void								displayheap();

};

#endif /* BINARYHEAP_H_ */
