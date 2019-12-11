/*
   collin gros
   10/30/2019
*/


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


Graph::Graph()
{
	clock = 0;
	cc = 0;
}


Graph::Graph(const std::string& file)
{
	scan(file);

	clock = 0;
	cc = 0;
}


void Graph::addEdge(const Node& a, const Node& b)
// insert an edge to adjList
{
	int id = a.id();
	m_adjList[id].push_back(b);
}


int Graph::node_exists(const std::string& s,
		       const std::unordered_map<std::string, int>& node_map)
// return 1 if node is found, 0 if node isn't found
{
	auto got = node_map.find(s);
	if (got == node_map.end()) {
		return 0;
	}
	else {
		return 1;
	}
}


void Graph::addNode(const Node& a)
// insert a node to nodes
{
	int id = a.id();
	m_nodes[id] = a;
}


const Node& Graph::getNode(size_t i) const
// return node with id == i
{
	return m_nodes[i];
}


std::list<Node>& Graph::getAdjNodes(const Node& a)
// return a reference of adj list of node a
{
	for (auto& list : m_adjList) {
		if (a.id() == list.front().id()) {
			return list;
		}
	}
}

const std::list<Node>& Graph::getAdjNodes(const Node& a) const
// return const reference of adj list of node a
{
	for (const auto& list : m_adjList) {
		if (a.id() == list.front().id()) {
			return list;
		}
	}
}

size_t Graph::num_nodes() const
// return total number of nodes in the graph
{
	return m_nodes.size();
}


void Graph::scan(const std::string& file)
// create a graph from tab-delimited text to adj lists
{
	std::ifstream my_file;
	my_file.open(file);
	if (!my_file.is_open()) {
	// check if our file exists
		std::cout << "couldn't open file!\n";
		exit(-1);
	}

	std::unordered_map <std::string, int> node_map;
	int line_num = 0, node_id = 0;
	std::string line, s1, s2;
	while (std::getline(my_file, line)) {
		std::istringstream iss(line);
		++line_num;

		std::getline(iss, s1, '\t');
		std::getline(iss, s2, '\t');
		// get strings on both sides of the tab

		if (!node_exists(s1, node_map)) {
		// adding s1 to node_map if it doesn't exist
		// also adding s1 as the "from" node in m_adjList
			std::pair<std::string, int> p (s1, node_id);
			node_map.insert(p);

			++node_id;
		}

		if (!node_exists(s2, node_map)) {
		// adding s2 to node_map if it doesn't exist
		// also adding s2 as the "from" node in m_adjList
			std::pair<std::string, int> p (s2, node_id);
			node_map.insert(p);

			++node_id;
		}
	}
	my_file.close();

	const int size = node_map.size();
	m_nodes.resize(size);
	for (auto& node_p : node_map) {
	// adding all nodes in node_map to nodes
		const std::string& s = node_p.first;
		const int& id = node_p.second;

		Node n (s, id);
		addNode(n);
	}

	m_adjList.resize(size);
	for (int i = 0; i < size; ++i) {
	// init all adj lists with heads
		Node& head = m_nodes[i];
		std::list<Node> head_list (1, head);

		m_adjList[i] = head_list;
	}

	my_file.open(file);
	while (std::getline(my_file, line)) {
	// adding all edges
		std::istringstream iss(line);

		std::getline(iss, s1, '\t');
		std::getline(iss, s2, '\t');
		// get strings on both sides of tab

		const int& id1 = node_map.find(s1)->second;
		Node n1 = getNode(id1);
		const int& id2 = node_map.find(s2)->second;
		Node n2 = getNode(id2);

		addEdge(n1, n2);
	}
}

void Graph::save(const std::string& file) const
// save a graph from adj lists to a tab-delimited file
{
	std::ofstream my_file;
	my_file.open(file);
	if (!my_file.is_open()) {
		std::cout << "couldn't open file!\n";
	}

	for (const auto& list : m_adjList) {
		const Node& from = list.front();
		const std::string& from_name = from.name();

		int first = 1;
		for (const auto& n : list) {
			if (first) {
				first = 0;
				continue;
			}

			const std::string& to_name = n.name();
			my_file << from_name << '\t' << to_name << '\n';
		}
	}
}


std::vector<Node>& Graph::get_nodes()
// return a reference to m_nodes
{
	return m_nodes;
}


void Graph::step_clock()
// set clock
{
	++clock;
}


int Graph::get_clock()
// return clock
{
	return clock;
}


int Graph::get_cc()
// return connected component count
{
	return cc;
}


void Graph::step_cc()
// step connected component count
{
	cc += 1;
}


void Graph::set_cc(int x)
// set connected component count
{
	cc = x;
}


void Graph::update_node(Node& n)
// update node n in G 
{
	addNode(n);
}


void Graph::reverse(Graph& G)
// make current graph a reverse of G
// Kosaraju's algorithm
{
	// copy m_nodes
	std::vector<Node>& G_m_nodes = G.get_nodes();
	int new_size = G_m_nodes.size();

	m_nodes.resize(new_size);
	std::copy(G_m_nodes.begin(), G_m_nodes.end(), m_nodes.begin());

	m_adjList.resize(new_size);
	for (int i = 0; i < new_size; ++i) {
	// initialize all adjacency lists with heads
		Node& head = m_nodes[i];
		std::list<Node> head_list (1, head);

		m_adjList[i] = head_list;
	}

	for (Node& s : m_nodes) {
		int id;

		std::list<Node>& adj = G.getAdjNodes(s);
		for (Node& k : adj) {
			// insert s into adj list of k in reverse graph
			id = k.id();
			m_adjList[id].push_back(s);
		}
	}
}

