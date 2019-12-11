/*
   collin gros
   11/24/2019
*/


#include "graph.h"
#include "node.h"
#include "list.h"
#include "heap.h"
#include "edge.h" // edge struct


#include <vector>
#include <list>
#include <iostream>
#include <string>


void dijkstra_route(Graph& G, std::string src_name,
			      std::string dst_name)
{
	std::vector<Node>& nodes = G.get_nodes();
	for (auto& node : nodes) {
		node.set_inf();
		G.update_node(node);
	}

	int s_id = G.search_node_names(src_name);
	Node s = G.getNode(s_id);

	s.set_dst(0);

	G.update_node(s);

	bool target_found = false;
	Heap h (G);
	//std::cout << "latitude,longitude,name,color,note\n";
	// for csv
	while (!h.empty() and !target_found) {
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

			if (first) {
			// skip first node in adj list, which is u
				first = 0;
				continue;
			}

			double dst_u = u.get_dst();
			double dst_v = v.get_dst();

			edge my_edge = G.getEdge(u, v);
			double weight = my_edge.weight;

			double new_dst = dst_u + weight; 

			if (dst_v > new_dst) {
				v.set_dst(new_dst);

				int id = u.id();
				std::string name = my_edge.name;
				v.set_prev_node(id);
				v.set_prev_edge(name);
				G.update_node(v);

				h.decreasekey(v);
			}

			if (v.name() == dst_name) {
				target_found = true;
				if (v.get_inf()) {
				// target is unreachable; checked all paths
				// from src, and dst is still inf..
					target_found = false;
				}

				break;
			}
		}
	}

	if (!target_found) {
		std::cout << dst_name << " is unreachable from "
			  << src_name << "!\n";
		exit(1);
	}

	std::list<Node> waypoints;
	std::list<std::string> roads;

	int dst_id = G.search_node_names(dst_name);
	Node dst = G.getNode(dst_id);

	int prev_node = dst.get_prev_node();
	std::string prev_edge = dst.get_prev_edge();
	Node prev = G.getNode(prev_node);

	prev_node = prev.get_prev_node();
	prev = G.getNode(prev_node);
	while (prev.name() != s.name()) {
	// following our path
		waypoints.push_front(prev);
		roads.push_front(prev_edge);

		prev = G.getNode(prev_node);
		prev_node = prev.get_prev_node(); 
		prev_edge = prev.get_prev_edge();

	}
	waypoints.push_front(s);

	std::list<std::string>::iterator it = roads.begin();
	for (Node& w : waypoints) {
		std::cout << w.name() << "[waypoint]\n";
		std::cout << *it << "[road]\n";

		++it;
	}
}








