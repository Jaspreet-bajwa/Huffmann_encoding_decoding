/*
 * pairheap.cpp
 *
 */

#include "hnode.h"
#include "pheap.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


pheap::pheap()
{
	_heapsize=0;
    root = NULL;
}

pheap::pheap(vector<hnode const*> &numbers){
	root=NULL;
	_heapsize=0;
	for(auto ele:numbers){
		//std::cout<<ele<<std::endl;
		Insert(ele);
	}
	std::cout<<"\n";
}


pheap::~pheap()
{
    //makeEmpty();
}

/*
 * Insert item x into the priority queue, maintaining heap order.
 * Return a pointer to the node containing the new item.
 */

pnode *pheap::Insert(hnode const* x)
{
   pnode *newNode = new pnode(x);
   //std::cout<<"Node allocated"<<std::endl;
    if (root == NULL){
	//std::cout<<"Root is null"<<std::endl;
        root = newNode;
    }else{
        compareAndLink(root, newNode);
    }

    //std::cout<<"["<<newNode->huff_node->data<<" : "<<newNode->huff_node->freq<<"]"<<std::endl;
    ++_heapsize;
    return newNode;
}

/*
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */
hnode const* pheap::findMin()
{
    return root->huff_node;
}

/*
 * Remove the smallest item from the priority queue.
 * Throws Underflow if empty.
 */
void pheap::deleteMin()
{
    pnode *oldRoot = root;
    if (root->leftChild == NULL)
        root = NULL;
    else
        root = combineSiblings(root->leftChild);
    --_heapsize;
    delete oldRoot;
}


/*
 * Test if the priority queue is logically empty.
 * Returns true if empty, false otherwise.
 */
bool pheap::isEmpty()
{
    return root == NULL;
}

/*
 * Test if the priority queue is logically full.
 * Returns false in this implementation.
 */
bool pheap::isFull()
{
    return false;
}

/*
 * Make the priority queue logically empty.
 */
void pheap::makeEmpty()
{
    reclaimMemory(root);
    root = NULL;
}


/*
 * Internal method to make the tree empty.
 */
void pheap::reclaimMemory(pnode * t)
{
    if (t != NULL)
    {
        reclaimMemory(t->leftChild);
        reclaimMemory(t->nextSibling);
        delete t;
    }
}


/*
 * Internal method that is the basic operation to maintain order.
 * Links first and second together to satisfy heap order.
 * first is root of tree 1, which may not be NULL.
 *    first->nextSibling MUST be NULL on entry.
 * second is root of tree 2, which may be NULL.
 * first becomes the result of the tree merge.
 */
void pheap::compareAndLink(pnode * &first, pnode *second)
{
    if (second == NULL)
    {
    	return;
    }
    if (*second->huff_node < *first->huff_node)
    {
        second->prev = first->prev;
        first->prev = second;
        first->nextSibling = second->leftChild;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->leftChild = first;
        first = second;
    }
    else
    {
        second->prev = first;
        first->nextSibling = second->nextSibling;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->nextSibling = first->leftChild;
        if (second->nextSibling != NULL)
            second->nextSibling->prev = second;
        first->leftChild = second;
    }
}

/*
 * Internal method that implements two-pass merging.
 * firstSibling the root of the conglomerate;
 *     assumed not NULL.
 */
pnode *pheap::combineSiblings(pnode *firstSibling)
{
    if (firstSibling->nextSibling == NULL)
        return firstSibling;
    static vector<pnode *> treeArray(5);
    int numSiblings = 0;
    for (; firstSibling != NULL; numSiblings++){
        if (numSiblings == treeArray.size())
            treeArray.resize(numSiblings * 2);
        treeArray[numSiblings] = firstSibling;
        firstSibling->prev->nextSibling = NULL;
        firstSibling = firstSibling->nextSibling;
    }
    if (numSiblings == treeArray.size())
        treeArray.resize(numSiblings + 1);
    treeArray[numSiblings] = NULL;
    int i = 0;
    for (; i + 1 < numSiblings; i += 2)
        compareAndLink(treeArray[i], treeArray[i + 1]);
    int j = i - 2;
    if (j == numSiblings - 3)
        compareAndLink (treeArray[j], treeArray[j + 2]);
    for (; j >= 2; j -= 2)
        compareAndLink(treeArray[j - 2], treeArray[j] );
    return treeArray[0];
}

void pheap::displayheap(){


}

long pheap::size(){
	return _heapsize;
}

