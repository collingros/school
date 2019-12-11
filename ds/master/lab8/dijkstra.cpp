/*
   collin gros
   11/24/2019
*/


#include "graph.h"
#include "node.h"
#include "list.h"
#include "heap.h"


#include <vector>
#include <list>
#include <iostream>


void Dijkstra_list(Graph& G, Node& s)
{
	std::vector<Node>& nodes = G.get_nodes();
	for (auto& node : nodes) {
		node.set_inf();
		G.update_node(node);
	}

	s.set_dst(0);
	G.update_node(s);

	List lq (G);
	while (!lq.empty()) {
		Node& old_u = lq.delete_min();

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

			std::string name_1 = v.name();
			std::string name_2 = u.name();

			if (first) {
			// skip first node in adj list, which is u
				first = 0;
				continue;
			}

			double dst_u = u.get_dst();
			double dst_v = v.get_dst();
			double new_dst = dst_u + G.getEdge(u, v); 

			if (dst_v > new_dst) {
				v.set_dst(new_dst);
				G.update_node(v);
			}
		}
	}


/*
	for (Node& n : nodes) {
		std::cout << "node: " << n.name() << "\tdst: " << n.get_dst() << "\n";
	}
*/
}


void Dijkstra_heap(Graph& G, Node& s)
{
	std::vector<Node>& nodes = G.get_nodes();
	for (auto& node : nodes) {
		node.set_inf();
		G.update_node(node);
	}

	s.set_dst(0);
	G.update_node(s);

	Heap h (G);
	while (!h.empty()) {
		Node old_u = h.deletemin();

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

			std::string name_1 = v.name();
			std::string name_2 = u.name();

			if (first) {
			// skip first node in adj list, which is u
				first = 0;
				continue;
			}

			double dst_u = u.get_dst();
			double dst_v = v.get_dst();
			double new_dst = dst_u + G.getEdge(u, v); 

			if (dst_v > new_dst) {
				v.set_dst(new_dst);
				G.update_node(v);

				std::cout << "v: " << v.name() << "\n";

				h.decreasekey(v);
			}
		}
	}



	for (Node& n : nodes) {
		std::cout << "node: " << n.name() << "\tdst: " << n.get_dst() << "\n";
	}

}



