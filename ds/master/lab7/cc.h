// collin gros
// 11/05/2019


#ifndef __CC_H_INCLUDED__
#define __CC_H_INCLUDED__


#include "graph.h"
#include "node.h"
#include "search.h"


#include <vector>
#include <algorithm>


std::vector<size_t> find_connected_components(Graph& G);

bool compare_nodes(Node& a, Node& b);
// return true if a's post is larger than b's post

std::vector<size_t> find_strongly_connected_components(Graph& G);


#endif
