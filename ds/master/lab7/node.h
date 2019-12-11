/*
   collin gros
   10/30/2019
*/

#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__


#include <string>
#include <limits>


class Node {
public:
	Node();
	Node(const std::string& name, int id);

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
private:
	std::string m_name;
	int m_id;

	int visited;
	int pre;
	int post;

	int cc;

	double dst;
};


#endif
