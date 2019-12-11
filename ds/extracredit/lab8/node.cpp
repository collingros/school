/*
   collin gros
   10/30/2019
*/

#include "node_info.h" // struct for node info
#include "edge.h"

#include <string>
#include <limits>
#include <cmath>

class Node {
public:
	Node();
	Node(const std::string& name, node_info info);
	// create a new node with an name, id, lattitude,
	// and longitude.
	//
	// arr:
	// 	{id, lat, lon} (all doubles, but id can be
	// 	casted to an integer

	int id() const;
	// get id of node

	const std::string& name() const;
	// get name of node

	int get_pre() const;
	// return pre time

	void set_pre(int v);
	// set pre time

	int get_post() const;
	// get post time

	void set_post(int v);
	// set post time

	int get_visited() const;
	// return visited

	void set_visited(int v);
	// set visited

	int get_cc() const;
	// get connected component id

	void set_cc(int x);
	// set connected component id to x

	int get_inf() const;
	void set_inf();

	double get_dst() const;
	void set_dst(double x);

	double get_lat() const;
	double get_lon() const;

	void set_prev_node(int id);
	int get_prev_node();

	void set_prev_edge(std::string name);
	std::string get_prev_edge();
private:
	std::string m_name;
	int m_id;
	double lat;
	double lon;

	int visited;
	int pre;
	int post;

	int cc;

	double dst;
	int prev_node;
	std::string prev_edge;
};


Node::Node()
{
}


Node::Node(const std::string& name, node_info info)
// create a new node with an name, id, lattitude,
// and longitude.
//
// arr:
// 	{id, lat, lon} (all doubles, but id can be
// 	casted to an integer
{
	m_name = name;

	m_id = info.id;
	lat = info.lat;
	lon = info.lon;
}



int Node::id() const
// get id of node
{
	return m_id;
}


const std::string& Node::name() const
// get name of node
{
	return m_name;
}


int Node::get_pre() const
// return pre time
{
	return pre;
}


void Node::set_pre(int v)
// set pre time
{
	pre = v;
}


int Node::get_post() const
// get post time
{
	return post;
}


void Node::set_post(int v)
// set post time
{
	post = v;
}


int Node::get_visited() const
// return visited
{
	return visited;
}


void Node::set_visited(int v)
// set visited
{
	visited = v;
}


int Node::get_cc() const
// get connected component id
{
	return cc;
}


void Node::set_cc(int x)
// set connected component id to x
{
	cc = x;
}


int Node::get_inf() const
{
	if (std::isinf(dst))
		return 1;

	return 0;
}


void Node::set_inf()
{
	dst = std::numeric_limits<double>::infinity();
}


double Node::get_dst() const
{
	return dst;
}

void Node::set_dst(double x)
{
	dst = x;
}


double Node::get_lat() const
{
	return lat;
}

double Node::get_lon() const
{
	return lon;
}


void Node::set_prev_node(int id)
{
	prev_node = id;
}

int Node::get_prev_node()
{
	return prev_node;
}


void Node::set_prev_edge(std::string name)
{
	prev_edge = name;
}

std::string Node::get_prev_edge()
{
	return prev_edge;
}
