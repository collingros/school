/*
   collin gros
   10/30/2019
*/


#include <string>
#include <limits>
#include <cmath>


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


Node::Node()
{

}


Node::Node(const std::string& name, int id)
{
	m_name = name;
	m_id = id;
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


