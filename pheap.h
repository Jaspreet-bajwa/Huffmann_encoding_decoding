/*
 * pairheap.h
 */

#ifndef PHEAP_H_
#define PHEAP_H_

#include <vector>
#include <cstddef>

class pnode
{
    public:
        hnode const *huff_node;
        pnode *leftChild;
        pnode *nextSibling;
        pnode *prev;
        pnode(hnode const* huff_node):
		huff_node(huff_node),
		leftChild(NULL),
		nextSibling(NULL),
		prev(NULL)
		{ }
};

class pheap
{
    private:
		long _heapsize;
        pnode *root;
        std::vector<pnode*> pnode_list;
        void reclaimMemory(pnode *t);
        void compareAndLink(pnode * &first, pnode *second);
        pnode *combineSiblings(pnode *firstSibling);

    public:
        pheap();
        pheap(std::vector<hnode const*> & numbers);
        ~pheap();
        bool isEmpty();
        bool isFull();
        hnode const *findMin();
        pnode *Insert(hnode const* x);
        void deleteMin();
        void makeEmpty();
        void displayheap();
        long size();

};



#endif /* PHEAP_H_ */
