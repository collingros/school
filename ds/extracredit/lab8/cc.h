// collin gros
// 11/05/2019


#ifndef __INCLUDED_CC__
#define __INCLUDED_CC__


#include "graph.h"
#include "node.h"


#include <vector>


std::vector<size_t> find_connected_components(Graph& G);

bool compare_nodes(Node& a, Node& b);
// return true if a's post number is larger than b's post number

std::vector<size_t> find_strongly_connected_components(Graph& G);


#endif
