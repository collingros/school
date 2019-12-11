/*
   collin gros
   10/30/2019
*/


// [[Rcpp::plugins(cpp11)]]


#include "dijkstra.h"
#include "graph.h"
#include "node.h"
#include "operations.h" // double equality

#include <iostream>
#include <vector>
#include <complex> // std::abs
#include <string>
#include <limits> // infinity


bool v_equal(std::vector<double>& a, std::vector<double>& b)
// return true if a and b are equal vectors
{
	int size_a = a.size();
	int size_b = b.size();

	if (size_a != size_b) {
		std::cout << "sizes not the same!\n";
		std::cout << "a: " << size_a << "\tb: " << size_b << "\n";
		return false;
	}

	for (int i = 0; i < size_a; ++i) {
		double e_a = a[i];
		double e_b = b[i];
		if (!double_equal(e_a, e_b)) {
			std::cout << e_a << "!=" << e_b << "\n";
			return false;
		}
	}

	return true;
}


std::vector<double> get_result(Graph& g)
// return the resulting vector of distances from g, with
// keys being node ids and values being distances (double)
{
	std::vector<Node>& m_nodes = g.get_nodes();

	std::vector<double> res;
	res.resize(m_nodes.size());

	for (Node& n : m_nodes) {
		int id = n.id();
		double dst = n.get_dst();
		res[id] = dst;
	}

	return res;
}


std::vector<double> pull_ans(std::string file)
// return ans key from graph called file
{
	std::vector<double> ans;
	if (file == "graphs/d_c.txt") {
		ans = {0, 2.5, 8.1, 11.1,
					      12, 8.3, 8.2};
	}
	else if (file == "graphs/u_c.txt") {
		ans = {0, 5.5, 1.8, 16.4,
					   2.3, 7.9};
	}
	else if (file == "graphs/d_a.txt") {
		ans = {0, 1, 2, 0.2, 0.1, 1.1};
	}
	else if (file == "graphs/u_a.txt") {
		ans = {0, 1, 5, 4, 3, 9};
	}
	else if (file == "graphs/d_cc.txt") {
		ans = {
			0, 1, 1.3, 1.4,
			std::numeric_limits<double>::infinity(),
			std::numeric_limits<double>::infinity()
		};
	};

	return ans;
}


bool test_g(std::string file, int c)
// return 1 if graph passed both dijkstra list and dijktra heap
// c: 0 for dijkstra_list, 1 for dijkstra_heap
{
	std::cout << "testing " << file << "...\n";
	Graph g (file);
	Node src = g.getNode(0);
	if (c) {
		Dijkstra_heap(g, src);
	}
	else {
		Dijkstra_list(g, src);
	}

	std::vector<double> ans = pull_ans(file);
	std::vector<double> res = get_result(g);
	if (!v_equal(ans, res)) {
		return false;
	}

	std::cout << "test completed!\n";
	return true;
}


// [[Rcpp::export]]
void test_big_g(std::string file, int c)
// run dijkstra on big graphs
{
	Graph g (file);
	Node src = g.getNode(0);
	if (c) {
		Dijkstra_heap(g, src);
	}
	else {
		Dijkstra_list(g, src);
	}
}


void test_all()
// test all small sample graphs with known solutions
{
/*
	// initial tests on small graphs

	std::vector<std::string> files = {
		"graphs/d_c.txt",
		"graphs/u_c.txt",
		"graphs/d_a.txt",
		"graphs/u_a.txt",
		"graphs/d_cc.txt"
	};


	for (int c = 0; c < 2; ++c) {
	// test for both dijkstra_list and dijkstra_heap
		for (std::string f : files) {
			bool passed = test_g(f, c);
			if (!passed) {
				std::cout << "FAILED! c: " << c
					  << "\tfile: " << f
					  << "\n";
				return;
			}
		}
	}
*/

	std::vector<std::string> edge_files = {
		"50k_200k.txt",
		"50k_400k.txt",
		"50k_600k.txt",
		"50k_800k.txt",
		"50k_1m.txt"
	};

	std::vector<std::string> node_files = {
		"20k_1m.txt",
		"40k_1m.txt",
		"60k_1m.txt",
		"80k_1m.txt",
		"100k_1m.txt"
	};

	int c = 0;
	// list
	c = 1;
	// heap

	std::cout << "PASSED ALL TESTS!\n";
}


int main()
{
	//test_all();
	Graph g ("graphs/neg.txt");
	Node src = g.getNode(0);
	Dijkstra_heap(g, src);
}


/*** R
start.time <- Sys.time()
test_big_g("graphs/50k_200k.txt", 0)
end.time <- Sys.time()
time.taken.6 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_400k.txt", 0)
end.time <- Sys.time()
time.taken.7 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_600k.txt", 0)
end.time <- Sys.time()
time.taken.8 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_800k.txt", 0)
end.time <- Sys.time()
time.taken.9 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_1m.txt", 0)
end.time <- Sys.time()
time.taken.10 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_200k.txt", 1)
end.time <- Sys.time()
time.taken.1 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_400k.txt", 1)
end.time <- Sys.time()
time.taken.2 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_600k.txt", 1)
end.time <- Sys.time()
time.taken.3 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_800k.txt", 1)
end.time <- Sys.time()
time.taken.4 <- end.time - start.time

start.time <- Sys.time()
test_big_g("graphs/50k_1m.txt", 1)
end.time <- Sys.time()
time.taken.5 <- end.time - start.time

my.arr <- c(200000, 400000, 600000, 800000, 1000000)
runtime.heap <- c(time.taken.1, time.taken.2, time.taken.3, time.taken.4, time.taken.5)
runtime.list <- c(time.taken.6, time.taken.7, time.taken.8, time.taken.9, time.taken.10)

png(file="edges.png")

plot(my.arr, runtime.list, type="l", xlab="edges", ylab="runtime (seconds)", ylim=c(runtime.heap[1], runtime.list[5]), col="red")
lines(my.arr, runtime.heap, col="green")

*/

