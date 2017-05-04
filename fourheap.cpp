/*
 * fourheap.cpp
 * created by: Jaspreet Bajwa
 */
#include "fourheap.h"

#include <iostream>
#include <algorithm>

//function to find the kth child
int fourheap::kthChild(int i, int k){
		return (4 * (i-2) + (k-1));
}

//function to find the parent of the node at i
int fourheap::parent(int i){
	return i/4+2;
}

//function to delete the minimum element
void fourheap::deletemin(){
	int length=_heap.size()-1;
	if(length >=3){
		_heap[3]=_heap[length];
		_heap.pop_back();
		percolatedown(3);
	}
}

//function to find the value of the smallest child
int fourheap::smallestChild(int i)
{
    int smallest_child = kthChild(i, 1);
    int k = 2;
    int candidate_child = kthChild(i, k);
    while ((k <= 4) && (candidate_child < _heap.size()))
    {
        if (*(_heap[candidate_child]) < *(_heap[smallest_child]))
        	smallest_child = candidate_child;
        k++;
        candidate_child = kthChild(i, k);
    }
    return smallest_child;
}

//function that rearranges the heap after a deletion to ensure min four way heap
void fourheap::percolatedown(int i){

	int ch;
	hnode const* tmp = _heap[i];
	for ( ; kthChild(i, 1) < _heap.size(); i = ch)
	{
		ch = smallestChild( i );
		if (*(_heap[ch]) < *tmp)
			_heap[i] = _heap[ch];
		else
			break;
	}
	_heap[i] = tmp;

}


//function to insert the node
void fourheap::insert(hnode const* ele){
	_heap.push_back(ele);
	percolateup(_heap.size()-1);
}

//function to get the minimum element in the heap
hnode const* fourheap::getmin(){
	if(_heap.size()==3){
		return NULL;
	}

	return _heap[3];
}

//function to display the heap
void fourheap::displayheap(){
	for(hnode const* ele:_heap){
		if(ele){
			std::cout<<"["<<ele->freq<<" : "<<ele->data<<"]\n";
		}
	}
	std::cout<<std::endl;
}

//function to find the size of the heap
size_t fourheap::size(){
	return _heap.size();
}

//function to insert the numbers
fourheap::fourheap(std::vector<hnode const*> &hnodes){
	for(int i=0;i<3;i++){
		insert(NULL);
	}
	for(hnode const * huff_node:hnodes){
		insert(huff_node);
	}
}

//function to perform re-arranging during insertion to ensure min heap property
void fourheap::percolateup(int i){

    hnode const* tmp = _heap[i];
    for (; i > 3 && *tmp < *(_heap[parent(i)]); i = parent(i))
        _heap[i] = _heap[parent(i)];
    _heap[i] = tmp;
}

//constructor
fourheap::~fourheap(){
}
