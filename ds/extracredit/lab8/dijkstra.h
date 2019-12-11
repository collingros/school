/*
   collin gros
   11/24/2019
*/


#ifndef __INCLUDED_DIJKSTRA__
#define __INCLUDED_DIJKSTRA__


#include "graph.h"
#include "node.h"
#include "edge.h"

#include <vector>
#include <string>


void dijkstra_route(Graph& G, std::string src_name,
			      std::string dst_name);
// preform dijkstra's algorithm using a binary heap


#endif
