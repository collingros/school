/*
   collin gros
   10/30/2019
*/


#ifndef __INCLUDED_NODE__
#define __INCLUDED_NODE__

#include "node_info.h" // struct for node info
#include "edge.h"

#include <string>


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


#endif
