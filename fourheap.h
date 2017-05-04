/*
 * FourHeap.h
 * created by: Jaspreet Bajwa
 */

#ifndef FOURHEAP_H_
#define FOURHEAP_H_

#include <vector>
#include "hnode.h"

class fourheap{

	std::vector<hnode const*> 			_heap;

	void 								percolateup(int i);
	void 								percolatedown(int i);
	int 								smallestChild(int i);
	int 								kthChild(int i, int k);
	int 								parent(int i);

public:

										fourheap();
										~fourheap();
										fourheap(std::vector<hnode const *> &numbers);
	void 								insert(hnode const* ele);
	hnode const* 						getmin();
	void 								deletemin();
	size_t 								size();
	void								displayheap();
		
};
#endif /*fourheap_H_*/
