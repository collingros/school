/*
   collin gros
   10/30/2019
*/


#include "dijkstra.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "operations.h" // double equality

#include <iostream>
#include <vector>
#include <string>


int main()
{
	//Graph g ("world/tm-master-simple.tmg");
	//Graph g ("world/tm-small.tmg");
	Graph g ("world/tm-master-simple.tmg");
	//dijkstra_route(g, "", "SanDiego");
	//dijkstra_route(g, "US54/US70@AlaSt", "TXLp289@19thSt");
	//dijkstra_route(g, "NM271@+X478507", "A39@+X09|ENG");
	dijkstra_route(g, "NM271@+X478507", "NY11C_N/US11_N");
}

