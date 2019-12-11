// collin gros
// 11/05/2019


#include "graph.h"
#include "node.h"


#include <stack>
#include <list>
#include <deque>
#include <iostream>
#include <string>


void explore(Graph& G, Node& src)
	// visited is set to true for all nodes reachable from n
{
	src.set_visited(1);

	// previsit
	int clock = G.get_clock();
	src.set_pre(clock);
	G.step_clock();

	// lab6: know which connected component we belong to 
	int cc = G.get_cc();
	src.set_cc(cc);

	G.update_node(src);

	std::list<Node>& init_adj = G.getAdjNodes(src);
	for (auto& dst : init_adj) {
		// for each edge in the source Node src
		dst = G.getNode(dst.id());
		// dst might have been updated from previous explore calls
		// and is different than when the loop started

		int visited = dst.get_visited();
		if (!visited) {
			explore(G, dst);
		}
	}

	// postvisit
	clock = G.get_clock();
	src.set_post(clock);
	G.step_clock();
	G.update_node(src);
}


void DFS_recursive(Graph& G)
{
	G.set_cc(0);

	std::vector<Node>& m_nodes = G.get_nodes();
	for (Node& n : m_nodes) {
		n.set_visited(0);
	} 

	for (Node& n : m_nodes) {
		G.update_node(n);
	}

	for (Node& n : m_nodes) {
		int visited = n.get_visited();
		if (!visited) {
			explore(G, n);

			// lab6: increment number of cc
			G.step_cc();
		}
	}
/*
	   for (Node& n : m_nodes) {
	   std::cout << "node: " << n.name() << "\n";
	   std::cout << "\tpre/post: " << n.get_pre() << ":" << n.get_post() << "\n";
	   }
*/
}


void DFS_iterative(Graph& G)
{
	std::vector<Node>& m_nodes = G.get_nodes();
	for (Node& n : m_nodes) {
		n.set_visited(0);
		n.set_post(0);
	} 

	for (Node& n : m_nodes) {
		G.update_node(n);
	}

	std::stack<Node> my_stack;
	for (Node& n : m_nodes) {
	// outer loop is for connected components
		my_stack.push(n);

		while (!my_stack.empty()) {
			Node top = my_stack.top();
			std::string top_name = top.name();

			int top_id = top.id();
			Node src = G.getNode(top_id); 

			my_stack.pop();

			int visited = src.get_visited();
			if (!visited) {
				// previsit
				src.set_visited(1);
				int clock = G.get_clock();
				src.set_pre(clock);
				G.step_clock();

				G.update_node(src);
			}

			std::list<Node>& adj = G.getAdjNodes(src);
			my_stack.push(adj.front());
			// so we can trace our steps back to parent nodes
			int count = 0;
			for (auto rit = adj.rbegin(); rit != adj.rend(); ++rit) {
			// reversed order so that pre/posts are same as recursive dfs
				Node dst = G.getNode(rit->id());
				// have to retrieve updated node info from G

				visited = dst.get_visited();
				if (!visited) {
					my_stack.push(dst);
					++count;
				}
			}

			if (count == 0) {
			// done visiting when src's neighbors have all been visited 
				if (src.get_post() == 0) {
				// only do postvisit once (check if get_post is the initial value)
					// postvisit
					int clock = G.get_clock();
					src.set_post(clock);
					G.step_clock();

					G.update_node(src);
				}

				my_stack.pop();
			}
		}
	}

/*
	for (Node& n : m_nodes) {
		std::cout << "node: " << n.name() << "\n";
		std::cout << "\tpre/post: " << n.get_pre() << ":" << n.get_post() << "\n";
	}
*/
}


void BFS(Graph& G, Node& s)
{
	//std::string name = s.name();
	//std::cout << "source: " << name << "\n";
	s.set_dst(0);
	G.update_node(s);

        std::deque<Node> my_deque;
	my_deque.push_back(s);

	while (!my_deque.empty()) {
		Node& old_u = my_deque.front();
		my_deque.pop_front();

		std::list<Node>& adj = G.getAdjNodes(old_u);
		// safe to use old_u, adj list didn't change in terms
		// of nodes or edges, just dst

		int first = 1;
		for (Node& old_v : adj) {
			Node v = G.getNode(old_v.id());
			// in the adj list of u, outdated dst info is
			// used.. need to graph newest version of v
			// from G
			Node u = G.getNode(old_u.id());
			// same thing here..

			if (first) {
			// skip first node in adj list, which is u
				first = 0;
				continue;
			}
			if (!v.get_inf()) {
				continue;
			}

			//name = v.name();
			//std::cout << "v: " << name << "\n";

			my_deque.push_back(v);

			double u_dst = u.get_dst();
			double sum = u_dst + 1;

			v.set_dst(sum);
			G.update_node(v);
		}
	}

/*
	for (Node& n : m_nodes) {
		std::cout << "node: " << n.name() << "\n";
		std::cout << "\tpre/post: " << n.get_pre() << ":" << n.get_post() << "\n";
	}
*/
}


void complete_BFS(Graph &G)
// for dealing with connected components
{
	std::vector<Node>& m_nodes = G.get_nodes();
	for (Node& n : m_nodes) {
		n.set_inf();
		G.update_node(n);
	} 

        for (Node& n : m_nodes) {
                if (!n.get_inf()) {
                // connected component is already explored
                        continue;
                }

                BFS(G, n);
        }
}

