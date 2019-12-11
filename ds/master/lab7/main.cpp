/*
   collin gros
   10/30/2019
*/


// [[Rcpp::plugins(cpp11)]]


#include "node.h"
#include "graph.h"
#include "search.h"


#include <vector>
#include <string>
#include <iostream>


std::vector<double> get_res(Graph& G)
// return BFS result where key = id, val = dst
{
	std::vector<double> res;
	std::vector<Node>& m_nodes = G.get_nodes();

	int c = 0;
	for (Node& n : m_nodes) {
		double dst = n.get_dst();
		res.push_back(dst);
		//std::cout << "id:dst\n";
		//std::cout << c << ":" << dst << "\n\n";

		++c;
	}

	return res;
}


void check_BFS(std::string name, std::vector<double> ans)
{
	Graph g (name);

	complete_BFS(g);
	std::vector<double> res = get_res(g); 

	if (ans != res) {
		std::cout << "didn't pass! graph: \"" << name << "\"\n";
		exit(1);
	}

	std::cout << "passed! graph: \"" << name << "\"\n";
}


void test_BFS()
{
	std::vector<double> ans_dir_ac_3 {0, 1, 2, 2, 2};
	check_BFS("graphs/dir_ac_3.txt", ans_dir_ac_3);

	std::vector<double> ans_dir_c_2 {0, 1, 2, 0, 1, 1, 1};
	check_BFS("graphs/dir_c_2.txt", ans_dir_c_2);

	std::vector<double> ans_un_ac_1 {0, 1, 2, 3, 2};
	check_BFS("graphs/un_ac_1.txt", ans_un_ac_1);

	std::vector<double> ans_un_ac_2 {0, 1, 2, 3, 4, 4, 0, 1, 0, 1, 2, 2};
	check_BFS("graphs/un_ac_2.txt", ans_un_ac_2);

	std::vector<double> ans_un_c_2 {0, 1, 2, 2, 3, 0, 1, 1};
	check_BFS("graphs/un_c_2.txt", ans_un_c_2);
}


// [[Rcpp::export]]
void test_1()
{
	Graph g1("graphs/func_edges/big_1.txt");
	complete_BFS(g1);
}


// [[Rcpp::export]]
void test_2()
{
	Graph g2("graphs/func_edges/big_2.txt");
	complete_BFS(g2);
}


// [[Rcpp::export]]
void test_3()
{
	Graph g3("graphs/func_edges/big_3.txt");
	complete_BFS(g3);
}


// [[Rcpp::export]]
void test_4()
{
	Graph g4("graphs/func_edges/big_4.txt");
	complete_BFS(g4);
}


int main()
{
	test_BFS();
	//test_nodes();
}


/*** R
start.time <- Sys.time()
test_1()
end.time <- Sys.time()
time.taken.1 <- end.time - start.time

start.time <- Sys.time()
test_2()
end.time <- Sys.time()
time.taken.2 <- end.time - start.time

start.time <- Sys.time()
test_3()
end.time <- Sys.time()
time.taken.3 <- end.time - start.time

start.time <- Sys.time()
test_4()
end.time <- Sys.time()
time.taken.4 <- end.time - start.time

my.arr <- c(50000, 100000, 150000, 200000)
runtime <- c(time.taken.1, time.taken.2, time.taken.3, time.taken.4)

png(file="nodes.png")

plot(my.arr, runtime, type="b", xlab="edges", ylab="runtime (seconds)")
grid(col="blue")

dev.off()
*/

