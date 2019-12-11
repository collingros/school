// collin gros
// 11/05/2019


#include "graph.h"
#include "node.h"
#include "search.h"


#include <vector>
#include <algorithm>


std::vector<size_t> find_connected_components(Graph& G)
{
	// call dfs, in previsit ccnum[v] = cc
	DFS_recursive(G);

	std::vector<Node>& m_nodes = G.get_nodes();

	std::vector<size_t> cc_ids;
	int size = m_nodes.size();
	cc_ids.resize(size);

	int cc_id, count = 0;
	for (Node& n : m_nodes) {
		cc_id = n.get_cc();
		cc_ids[count] = cc_id;
		++count;
	}

	return cc_ids;
}


bool compare_nodes(Node& a, Node& b)
// return true if a's post number is larger than b's post number
{
	int a_post = a.get_post();
	int b_post = b.get_post();

	if (a_post > b_post)
		return true;

	return false;
}

std::vector<size_t> find_strongly_connected_components(Graph& G)
{
	DFS_recursive(G);

	std::vector<Node>& G_m_nodes = G.get_nodes();
	std::vector<Node> sorted_nodes;

	int size = G_m_nodes.size();
	sorted_nodes.resize(size);

	std::copy(G_m_nodes.begin(), G_m_nodes.end(), sorted_nodes.begin());
	std::sort(sorted_nodes.begin(), sorted_nodes.end(), compare_nodes);
	// sort nodes with highest postorder at beginning

	Graph rev;
	rev.reverse(G); 

	DFS_recursive(rev);

	std::vector<Node>& rev_nodes = rev.get_nodes();
	std::vector<size_t> cc_ids;

	size = rev_nodes.size();
	cc_ids.resize(size);

	int cc_id, count = 0;
	for (Node& n : rev_nodes) {
		cc_id = n.get_cc();
		cc_ids[count] = cc_id;
		++count;
	}

	return cc_ids;

}

