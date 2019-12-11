/*
   collin gros
   12/02/2019
*/


#include "graph.h"
#include "node.h"
#include "operations.h" // double equality

#include <vector>
#include <cmath>
#include <limits> // inf
#include <complex> // abs
#include <iostream>


class Heap {
public:
	Heap(Graph& graph);

	Node at_node(Node x);
	// return node to node x in heap

	Node at_index(int i);
	// return node to node at i

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


Heap::Heap(Graph& graph) : g(graph)
{
	makeheap();
}


Node Heap::at_node(Node x)
// return the to node x in heap
{
	int x_id = x.id();
	int pos = heap_pos[x_id];

	return heap_nodes[pos]; 
}


Node Heap::at_index(int i)
// return node reference to node at i
{
	return heap_nodes[i];
}


void Heap::set_num(int x)
// set the number of nodes in the heap to x
{
	num = x;
}


void Heap::inc_num()
// incremement the number of nodes in the heap
{
	num += 1;
}


void Heap::dec_num()
// decrement the number of nodes in the heap
{
	num -= 1;
}


int Heap::get_num()
// return the number of nodes in the heap
{
	return num;
}


int Heap::empty()
// return 1 if there aren't any nodes in our heap
{
	if (get_num() == 0) {
		return 1;
	}

	return 0;
}


int Heap::get_size()
// return the size of the heap
{
	return heap_nodes.size();
}


void Heap::set_node(Node x, int i)
// put x in i'th position of the heap, and update
// the position in heap_pos
// checks bounds, if we need to extend vector by one
{
	heap_nodes[i] = x;
	set_pos(x, i);
	// preserve location data of node in heap
}


void Heap::set_pos(Node x, int i)
// set x's position in heap
{
	int x_id = x.id();
	heap_pos[x_id] = i;
}


int Heap::get_pos(Node x)
// return x's position in heap
{
	int x_id = x.id();
	int x_pos = heap_pos[x_id];

	return x_pos;
}


void Heap::swap_nodes(Node x, Node y)
// swap two nodes in heap
{
	// actually swap nodes in heap
	int x_pos = get_pos(x);
	int y_pos = get_pos(y);

	Node tmp_node = heap_nodes[x_pos];
	heap_nodes[x_pos] = heap_nodes[y_pos];
	heap_nodes[y_pos] = tmp_node;

	// swap position values in heap_pos
	set_pos(x, y_pos);
	set_pos(y, x_pos);
}


void Heap::insert(Node x)
// insert a node into the heap
{
	bubbleup(x, get_num() + 1);
}


void Heap::decreasekey(Node x)
// decrease a node's key in the heap
{
	bubbleup(x, get_pos(x));
}


Node Heap::deletemin()
// delete the node with the min key in the heap, then
// siftdown all nodes affected in heap
// XXX ASSUMES THE HEAP IS NOT EMPTY!
// FIXME: x refers to f instead of a, the last elm instead of first
//        by the end of the function...
{
	Node x = at_index(1);
	Node last = at_index(get_num());
	siftdown(last, 1);

	dec_num();

	return x;
}


void Heap::print_heap()
// print the heap
{
	for (int i = 1; i < heap_nodes.size(); ++i) {
		std::cout << heap_nodes[i].name() << "\t";
	}
	std::cout << "\n";

	for (int i = 1; i < heap_nodes.size(); ++i) {
		std::cout << heap_nodes[i].get_dst() << "\t";
	}
	std::cout << "\n\n";
}


void Heap::makeheap()
// make heap with the size of g, indexed starting at 1!
{
	std::vector<Node>& m_nodes = g.get_nodes();
	int size = m_nodes.size();
	heap_pos.resize(size);

	++size;
	// + 1 to accomodate for empty index 0 in heap

	set_num(0);
	heap_nodes.resize(size);
	for (Node x : m_nodes) {
		int cur_pos = get_num() + 1;

		set_node(x, cur_pos);
		inc_num();
	}

	for (int i = num; i > 0; --i) {
		siftdown(at_index(i), i);
	}
}


void Heap::bubbleup(Node node_x, int i)
// place a node x in position i of the heap, and let it
// bubble up
{
	int p = i / 2;
	while (1) {
		if (i == 1) {
			break;
		}

		Node node_p = at_index(p);
		double dst_p = node_p.get_dst();
		double dst_x = node_x.get_dst();

		if (!(dst_p > dst_x)) {
			break;
		}
		if (double_equal(dst_p, dst_x)) {
		// for dealing with infinity
			break;
		}

		set_node(node_p, i);
		i = p;
		p = i / 2;
	}

	set_node(node_x, i);
}


void Heap::siftdown(Node node_x, int i)
// place a node x in position i of the heap, and let it
// sift down
{
	int c = minchild(i);
	while (1) {
		if (c == 0) {
			break;
		}

		Node node_c = at_index(c);

		double dst_c = node_c.get_dst();
		double dst_x = node_x.get_dst();

		if (dst_c > dst_x) {
			break;
		}
		if (double_equal(dst_c, dst_x)) {
		// for dealing with infinity; might not be
		// necessary, but was necessary when comparing vectors
		// of doubles with numeric_limits<double>::infinity
			break;
		}

		set_node(node_c, i);
		i = c;
		c = minchild(i); 
	}

	set_node(node_x, i);
}


int Heap::minchild(int i)
// return the index of the smallest child of the node at i
{
	int lc = i * 2;
	int rc = lc + 1;
	// index of right and left children

	if (lc > num) {
		return 0;
	}

	if (rc > num) {
		return lc;
	}

	else {
		Node node_i = at_index(i);
		Node left = at_index(lc);
		Node right = at_index(rc);

		double dst_left = left.get_dst();
		double dst_right = right.get_dst();

		if (dst_left < dst_right) {
			return lc;
		}
		else {
			return rc;
		}
	}
}








