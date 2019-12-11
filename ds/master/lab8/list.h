/*
   collin gros
   11/20/2019
*/


#ifndef __INCLUDED_LIST__
#define __INCLUDED_LIST__


#include "node.h"
#include "graph.h"

#include <list>


class List {
public:
	List(Graph& g);

	const Node& at(size_t i);
	// get node at i

	void insert(Node& n);
	// insert a node into the heap
	
	void decrease_key(Node& n);
	// decrease the key of a node

	Node& delete_min();
	// return the node with the smallest key, and remove it from the list

	void make_queue();
	// make a priority queue out of all nodes in graph

	bool empty();
	// return if nodes are empty
private:
	std::list<Node> nodes;
	Graph& graph;
};


#endif
