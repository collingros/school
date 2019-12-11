/*
   collin gros
   10/30/2019
*/


#ifndef __GRAPH_H_INCLUDED__
#define __GRAPH_H_INCLUDED__


#include "node.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>


class Graph {
public:
	Graph();
	Graph(const std::string& file);

	void addEdge(const Node& a, const Node& b);
	// insert an edge to adjList

	int node_exists(const std::string& s,
			const std::unordered_map<std::string, int>& node_map);
	// return 1 if node is found, 0 if node isn't found

	void addNode(const Node& a);
	// insert a node to nodes

	const Node& getNode(size_t i) const;
	// return node with id == i

	std::list<Node>& getAdjNodes(const Node& a);
	// return a reference of adj list of node a

	const std::list<Node>& getAdjNodes(const Node& a) const;
	// return const reference of adj list of node a

	size_t num_nodes() const;
	// return total number of nodes in the graph

	void scan(const std::string& file);
	// create a graph from tab-delimited text to adj lists

	void save(const std::string& file) const;
	// save a graph from adj lists to a tab-delimited file

	std::vector<Node>& get_nodes();
	// return a reference to m_nodes

	void step_clock();
	// set clock

	int get_clock();
	// return clock

	int get_cc();
	// return connected component count

	void step_cc();
	// step connected component count

	void set_cc(int x);
	// set connected component count

	void update_node(Node& n);
	// update node n in G, as well as its adjacency list nodes

	void reverse(Graph& G);
	// make current graph a reverse of G
	// Kosaraju's algorithm
private:
	std::vector<Node> m_nodes;
	std::vector<std::list<Node>> m_adjList;

	int clock;
	int cc;
};


#endif
