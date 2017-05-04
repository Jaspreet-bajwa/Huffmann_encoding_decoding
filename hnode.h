#ifndef HNODE_H_
#define HNODE_H_

#include<cstddef>

struct hnode{
	int 				data;
	unsigned int		freq;
	hnode const			*left;
	hnode const			*right;
	
	hnode(  int const &data,
			unsigned int const &freq,
			hnode const* left,
			hnode const* right):
		data(data),
		freq(freq),
		left(left),
		right(right){}
	
	//the node comparision will always be determined by it's frequency thus overloading the < operator..
	bool operator<(const hnode& rhs) const{
		return freq < rhs.freq;
	}
};

#endif /* HNODE_H_ */
