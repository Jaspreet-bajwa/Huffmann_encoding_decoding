/*
 * binaryHeap.cpp
 * created by: Jaspreet Bajwa
 */
#include "binaryHeap.h"

#include <iostream>
#include <algorithm>

/*
 * returns the size
 */
int binaryHeap::size(){
	return _heap.size();
}

/*
 * returns the left child
 */
int binaryHeap::lchild(int i){
	return 2*i+1;
}

/*
 * returns the right child
 */
int binaryHeap::rchild(int i){
	return 2*i+2;
}

/*
 * returns the parent node
 */
int binaryHeap::parent(int i){
	return (i-1)/2;
}

/*
 * rearranges the tree while insertion
 */
void binaryHeap::percolateup(int i){
	int pr=parent(i);
	if(i<_heap.size() && pr>=0 && (*_heap[i]< *_heap[pr])){
		std::swap(_heap[pr],_heap[i]);
		percolateup(pr);
	}
}

/*
 * inserts the node in the binary heap
 */
void binaryHeap::insert(hnode const* ele){

	_heap.push_back(ele);
	percolateup(_heap.size()-1);
}

/*
 * deletes the minimum element in the heap
 */
void binaryHeap::deletemin(){
	int length=_heap.size()-1;
	if(length>=0){
		_heap[0]=_heap[length];
		_heap.pop_back();
		percolatedown(0);
	}
}

/*
 * returns the minimum element in the heap
 */
hnode const* binaryHeap::getmin(){
	if(_heap.size()==0){
		return NULL;
	}

	return _heap[0];
}

/*
 * prints the values in the heap
 */
void binaryHeap::displayheap(){
	std::cout<<"Binary Heap [frequency: value]\n";
	for(hnode const* ele:_heap){
		std::cout<<"["<<ele->freq<<" : "<<ele->data<<"]\n";
	}
	std::cout<<std::endl;
}

/*
 * inserts the nodes in the heap
 */
binaryHeap::binaryHeap(std::vector<hnode const*> &hnodes){
	for(hnode const * huff_node:hnodes){
		insert(huff_node);
	}
}

/*
 * performs rearranging in the heap after deletion
 */
void binaryHeap::percolatedown(int i){
	int l=lchild(i);
	int r=rchild(i);
	int small=i;
	if(l<_heap.size() && (*(_heap[l])< *(_heap[small]))){
		small=l;
	}
	if(r<_heap.size() && (*(_heap[r]) < *(_heap[small]))){
		small=r;
	}
	if(small!=i){
		std::swap(_heap[i],_heap[small]);
		percolatedown(small);
	}

}

binaryHeap::~binaryHeap(){
}
