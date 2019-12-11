/*
   collin gros
   12/02/2019
*/


#ifndef __INCLUDED_HEAP__
#define __INCLUDED_HEAP__


#include "graph.h"
#include "node.h"

#include <vector>


class Heap {
public:
	Heap(Graph& graph);

	Node at_node(Node x);
	// return node reference to node x in heap

	Node at_index(int i);
	// return node reference to node at i

	void set_num(int x);
	// set the number of nodes in the heap to x

	void inc_num();
	// incremement the number of nodes in the heap

	void dec_num();
	// decrement the number of nodes in the heap

	int get_num();
	// return the number of nodes in the heap

	int empty();
	// return 1 if there aren't any nodes in our heap

	int get_size();
	// return the size of the heap

	void set_node(Node x, int i);
	// put x in i'th position of the heap, and update
	// the position in heap_pos
	// checks bounds, if we need to extend vector by one

	void set_pos(Node x, int i);
	// set x's position in heap

	int get_pos(Node x);
	// return x's position in heap

	void swap_nodes(Node x, Node y);
	// swap two nodes in heap

	void insert(Node x);
	// insert a node into the heap

	void decreasekey(Node x);
	// decrease a node's key in the heap

	Node deletemin();
	// delete the node with the min key in the heap, then
	// siftdown all nodes affected in heap

	void print_heap();
	// print the heap

	void makeheap();
	// make heap with the size of g, indexed starting at 1!

	void bubbleup(Node node_x, int i);
	// place a node x in position i of the heap, and let it
	// bubble up

	void siftdown(Node node_x, int i);
	// place a node x in position i of the heap, and let it
	// sift down

	int minchild(int i);
	// return the index of the smallest child of the node at i
private:
	int num;
	// number of nodes currently in heap

	std::vector<int> heap_pos;
	// for recording the positions of nodes in the heap
	// key:val = node.id():heap_pos

	std::vector<Node> heap_nodes;
	Graph& g;
};


#endif
