/*
   collin gros
   11/24/2019
*/


#ifndef __INCLUDED_DIJKSTRA__
#define __INCLUDED_DIJKSRTA__


#include "graph.h"
#include "node.h"


void Dijkstra_list(Graph& G, Node& s);
// perform dijkstra's algorithm using STL list

void Dijkstra_heap(Graph& G, Node& s);
// preform dijkstra's algorithm using a binary heap


#endif
