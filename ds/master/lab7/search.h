// collin gros
// 11/05/2019


#ifndef __SEARCH_H_INCLUDED__
#define __SEARCH_H_INCLUDED__


#include "graph.h"
#include "node.h"


#include <deque>
#include <list>
#include <cmath>


void explore(Graph& G, Node& src);
// visited is set to true for all nodes reachable from n

void DFS_recursive(Graph& G);

void DFS_iterative(Graph& G);

void BFS(Graph& G, Node& s);

void complete_BFS(Graph &G);
// for dealing with connected components

#endif
