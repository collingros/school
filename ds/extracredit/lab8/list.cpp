/*
   collin gros
   11/20/2019
*/


#include "node.h"
#include "graph.h"

#include <list>
#include <vector>


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


List::List(Graph& g) : graph(g)
{
	graph = g;
	make_queue();
}


const Node& List::at(size_t i)
{
	std::vector<Node> m_nodes = graph.get_nodes();
	const Node& n = graph.getNode(i); 

	return n;
}


void List::insert(Node& n)
// insert a node into the heap
{
	nodes.push_back(n);
}


void List::decrease_key(Node& n)
// notify queue of the decrease of a key of a node
{

}


Node& List::delete_min()
// return the node with the smallest key, and remove it from the list
{
	int min, first = 1;
	std::list<Node>::iterator it, tar_it;
	for (it = nodes.begin(); it != nodes.end(); ++it) {
		Node& node = *it;
		double dst = node.get_dst();
		if (first) {
			min = dst;
			tar_it = it;

			first = 0;
			continue;
		}

		if (dst < min) {
			min = dst;
			tar_it = it;
		}
	}


	Node& target = *tar_it;
	nodes.erase(tar_it);

	return target;
}


void List::make_queue()
// make a priority queue out of all nodes in graph
{
	std::vector<Node>& m_nodes = graph.get_nodes();
	for (auto& node : m_nodes) {
		insert(node);
	}
}


bool List::empty()
// return if nodes are empty
{
	return nodes.empty();
}


