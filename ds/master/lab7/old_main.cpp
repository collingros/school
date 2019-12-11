/*
   collin gros
   10/30/2019
   cs-372
   lab6
*/

// Enable C++11 via this plugin (Rcpp 0.10.3 or later)
// [[Rcpp::plugins(cpp11)]]

#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <algorithm>


class Node {
public:
        Node();
        Node(const std::string& name, int id);

        int id() const;
        // get id of node

        const std::string& name() const;
        // get name of node

        int get_pre() const;
        // return Node.pre

        void set_pre(int v);
        // set Node.pre to v

        void set_post(int v);
        // set Node.post to v

        int get_post() const;
        // return Node.post

        int get_visited() const;
        // return Node.visited

        void set_visited(int v);
        // set Node.visited to v

        void set_cc(int x);
        // set Node.cc to x

        int get_cc();
        // get Node.cc
private:
        std::string m_name;
        int m_id;

        int visited;
        int pre;
        int post;

        int cc;
        // id of connected component we belong to
};


Node::Node()
{

}


Node::Node(const std::string& name, int id) 
{
        m_name = name;
        m_id = id;
}


int Node::get_pre() const
// return Node.pre 
{
        return pre;
}


void Node::set_pre(int v)
// set Node.pre to v
{
        pre = v;
}


void Node::set_post(int v)
// set Node.post to v
{
        post = v;
}


int Node::get_post() const
// return Node.post
{
        return post;
}


int Node::get_visited() const
// return Node.visited
{
        return visited;
}


void Node::set_visited(int v)
// set Node.visited to v
{
        visited = v;
}


int Node::id() const
// get id of node
{
        return m_id;
}


const std::string& Node::name() const
// get name of node
{
        return m_name;
}


void Node::set_cc(int x)
// set Node.cc to x
{
        cc = x;
}


int Node::get_cc()
// get Node.cc
{
        return cc;
}


class Graph {
public:
        Graph();
        Graph(const std::string& file);

        void addEdge(const Node& a, const Node& b);
        // insert an edge to adjList

        int node_exists(const std::string& s, const std::unordered_map<std::string, int>& node_map);
        // return 1 if node is found, 0 if node isn't found

        void addNode(const Node& a);
        // insert a node to nodes

        const Node& getNode(size_t i) const;
        // return node with id == i

        std::list<Node>& getAdjNodes(const Node& a);
        // return reference of adjacency list of node a

        const std::list<Node>& getAdjNodes(const Node& a) const; 
        // return const reference of adjacency list of node a

        size_t num_nodes() const;
        // return total number of nodes in the graph

        void scan(const std::string& file);
        // create a graph from tab-delimited text edge list to
        // adjacency lists

        void save(const std::string& file) const;
        // save a graph from adjacency lists to a tab-delimited
        // text edge list

        std::vector<Node>& get_nodes();
        // return a reference to m_nodes

        void step_clock();
        // change value of Graph.clock to v

        int get_clock();
        // return value of Graph.clock

        void update_node(Node& n);
        // update node n in G, as well as its adjacency list nodes

        void update_adj(Node& n);
        // update the adjacency list of n

        int get_cc();
        // return connected component count

        void step_cc();
        // step connected component count

        void reverse(Graph& G);
        // make current graph a reverse of G 

        void set_cc(int x);
private:
        std::vector<Node> m_nodes;
        std::vector<std::list<Node>> m_adjList;
        int clock;

        int cc;
        // connected component count
};


Graph::Graph()
{
        clock = 0;
        cc = 0;
}


Graph::Graph(const std::string& file)
{
        scan(file);
        clock = 0;
        cc = 0;
}


void Graph::step_clock()
// inc value of clock by 1
{
        ++clock;
}


int Graph::get_clock()
// return value of Graph.clock
{
        return clock;
}


void Graph::addEdge(const Node& a, const Node& b)
// insert an edge to adjList of a
{
        const int& id = a.id();
        m_adjList[id].push_back(b); 
}


int Graph::node_exists(const std::string& s, const std::unordered_map<std::string, int>& node_map)
// return 1 if node is found, 0 if node isn't found
{
        auto got = node_map.find(s);
        if (got == node_map.end()) {
                return 0;
        }
        else {
                return 1;
        }
}


void Graph::addNode(const Node& a)
// insert a node to nodes
{
        const int& id = a.id();
        m_nodes[id] = a;
}


const Node& Graph::getNode(size_t i) const
// return node with id == i
{
        return m_nodes[i];
}


std::list<Node>& Graph::getAdjNodes(const Node& a)
// return reference of adjacency list of node a
{
        for (auto& list : m_adjList) {
                if (a.id() == list.front().id()) {
                        return list;
                }
        }
}


const std::list<Node>& Graph::getAdjNodes(const Node& a) const
// return const reference of adjacency list of node a
{
        for (const auto& list : m_adjList) {
                if (a.id() == list.front().id()) {
                        return list;
                }
        }
}


size_t Graph::num_nodes() const
// return total number of nodes in the graph
{
        return m_nodes.size();
}


void Graph::scan(const std::string& file)
// create a graph from tab-delimited text edge list to adjacency lists
{
        std::ifstream my_file;
        my_file.open(file);
        if (!my_file.is_open()) {
        // check if our file exists
                std::cout << "couldn't open file!\n";
                exit(-1);
        }

        std::unordered_map <std::string, int> node_map;
        int line_num = 0, node_id = 0;
        std::string line, s1, s2;
        while (std::getline(my_file, line)) {
                std::istringstream iss(line);
                ++line_num;

                std::getline(iss, s1, '\t');
                std::getline(iss, s2, '\t');
                // get strings on both sides of the tab

                if (!node_exists(s1, node_map)) {
                // adding s1 to node_map if it doesn't exist
                // also adding s1 as the "from" node in m_adjList
                        std::pair<std::string, int> p (s1, node_id);
                        node_map.insert(p);

                        ++node_id;
                }

                if (!node_exists(s2, node_map)) {
                // adding s2 to node_map if it doesn't exist
                // also adding s2 as the "from" node in m_adjList
                        std::pair<std::string, int> p (s2, node_id);
                        node_map.insert(p);

                        ++node_id;
                }
        }
        my_file.close();

        const int size = node_map.size();
        m_nodes.resize(size);
        for (auto& node_p : node_map) {
        // adding all nodes in node_map to nodes
                const std::string& s = node_p.first;
                const int& id = node_p.second;

                Node n (s, id);
                addNode(n);
        }

        m_adjList.resize(size);
        for (int i = 0; i < size; ++i) {
        // initialize all adjacency lists with heads
                Node& head = m_nodes[i];
                std::list<Node> head_list (1, head);

                m_adjList[i] = head_list;
        }

        my_file.open(file);
        while (std::getline(my_file, line)) {
        // adding all edges
                std::istringstream iss(line);

                std::getline(iss, s1, '\t');
                std::getline(iss, s2, '\t');
                // get strings on both sides of the tab
 
                const int& id1 = node_map.find(s1)->second;
                Node n1 = getNode(id1);
                const int& id2 = node_map.find(s2)->second;
                Node n2 = getNode(id2);

                addEdge(n1, n2);
        }
}


void Graph::save(const std::string& file) const
// save a graph from adjacency lists to a tab-delimited text edge list
{
        std::ofstream my_file;
        my_file.open(file);
        if (!my_file.is_open()) {
                std::cout << "couldn't open file!\n";
        }

        for (const auto& list : m_adjList) {
                const Node& from = list.front();
                const std::string& from_name = from.name();

                int first = 1;
                for (const auto& n : list) {
                        if (first) {
                                first = 0;
                                continue;
                        }

                        const std::string& to_name = n.name();
                        my_file << from_name << '\t' << to_name << '\n';
                }
        }
}

std::vector<Node>& Graph::get_nodes()
// return a reference to m_nodes
{
        return m_nodes;
}


void Graph::update_node(Node& n)
// update node n in G, as well as its adjacency list nodes
{
        addNode(n);
//        update_adj(n);
}


void Graph::update_adj(Node& n)
// update the adjacency list of n
{
        std::list<Node>& adj = getAdjNodes(n);
        for (Node& dst : adj) {
                int id = dst.id();
                const Node& replace = getNode(id);
                dst = replace;
        } 
}


int Graph::get_cc()
// return connected component count
{
        return cc;
}


void Graph::set_cc(int x)
{
        cc = x;
}


void Graph::step_cc()
// step connected component count
{
        cc += 1;
}


void Graph::reverse(Graph& G)
// make current graph a reverse of G
// Kosaraju's algorithm
{
        // copy m_nodes
        std::vector<Node>& G_m_nodes = G.get_nodes();
        int new_size = G_m_nodes.size();

        m_nodes.resize(new_size);
        std::copy(G_m_nodes.begin(), G_m_nodes.end(), m_nodes.begin());

        m_adjList.resize(new_size);
        for (int i = 0; i < new_size; ++i) {
        // initialize all adjacency lists with heads
                Node& head = m_nodes[i];
                std::list<Node> head_list (1, head);

                m_adjList[i] = head_list;
        }

        for (Node& s : m_nodes) {
                int id;

                std::list<Node>& adj = G.getAdjNodes(s);
                for (Node& k : adj) {
                        // insert s into adj list of k in reverse graph
                        id = k.id();
                        m_adjList[id].push_back(s);
                }
        }
}


void explore(Graph& G, Node& src)
// visited is set to true for all nodes reachable from n
{
        src.set_visited(1);

        // previsit
        int clock = G.get_clock();
        src.set_pre(clock);
        G.step_clock();

        // lab6: know which connected component we belong to 
        int cc = G.get_cc();
        src.set_cc(cc);

        G.update_node(src);

        std::list<Node>& init_adj = G.getAdjNodes(src);
        for (auto& dst : init_adj) {
        // for each edge in the source Node src
                dst = G.getNode(dst.id());
                // dst might have been updated from previous explore calls
                // and is different than when the loop started

                int visited = dst.get_visited();
                if (!visited) {
                        explore(G, dst);
                }
        }

        // postvisit
        clock = G.get_clock();
        src.set_post(clock);
        G.step_clock();
        G.update_node(src);
}

void DFS_recursive(Graph& G)
{
        G.set_cc(0);

        std::vector<Node>& m_nodes = G.get_nodes();
        for (Node& n : m_nodes) {
                n.set_visited(0);
        } 

        for (Node& n : m_nodes) {
                G.update_node(n);
        }

        for (Node& n : m_nodes) {
                int visited = n.get_visited();
                if (!visited) {
                        explore(G, n);

                        // lab6: increment number of cc
                        G.step_cc();
               }
        }
/*
        for (Node& n : m_nodes) {
                std::cout << "node: " << n.name() << "\n";
                std::cout << "\tpre/post: " << n.get_pre() << ":" << n.get_post() << "\n";
        }
*/
}


void DFS_iterative(Graph& G)
{
        std::vector<Node>& m_nodes = G.get_nodes();
        for (Node& n : m_nodes) {
                n.set_visited(0);
                n.set_post(0);
        } 

        for (Node& n : m_nodes) {
                G.update_node(n);
        }

        std::stack<Node> my_stack;
        for (Node& n : m_nodes) {
        // outer loop is for connected components
                my_stack.push(n);

                while (!my_stack.empty()) {
                        Node top = my_stack.top();
                        std::string top_name = top.name();

                        int top_id = top.id();
                        Node src = G.getNode(top_id); 

                        my_stack.pop();

                        int visited = src.get_visited();
                        if (!visited) {
                                // previsit
                                src.set_visited(1);
                                int clock = G.get_clock();
                                src.set_pre(clock);
                                G.step_clock();

                                G.update_node(src);
                        }

                        std::list<Node>& adj = G.getAdjNodes(src);
                        my_stack.push(adj.front());
                        // so we can trace our steps back to parent nodes
                        int count = 0;
                        for (auto rit = adj.rbegin(); rit != adj.rend(); ++rit) {
                        // reversed order so that pre/posts are same as recursive dfs
                                Node dst = G.getNode(rit->id());
                                // have to retrieve updated node info from G

                                visited = dst.get_visited();
                                if (!visited) {
                                        my_stack.push(dst);
                                        ++count;
                                }
                        }

                        if (count == 0) {
                        // done visiting when src's neighbors have all been visited 
                                if (src.get_post() == 0) {
                                // only do postvisit once (check if get_post is the initial value)
                                        // postvisit
                                        int clock = G.get_clock();
                                        src.set_post(clock);
                                        G.step_clock();

                                        G.update_node(src);
                                }

                                my_stack.pop();
                        }
                }
        }

/*
        for (Node& n : m_nodes) {
                std::cout << "node: " << n.name() << "\n";
                std::cout << "\tpre/post: " << n.get_pre() << ":" << n.get_post() << "\n";
        }
*/
}


void p_cc_ids(std::vector<size_t> vec)
// print cc_ids and their node names 
{
        int count = 0;
        for (auto& cc_id : vec) {
                std::cout << count << ":" << cc_id << "\n";
                ++count;
        }
}


std::vector<size_t> find_connected_components(Graph& G)
{
        // call dfs, in previsit ccnum[v] = cc
        DFS_recursive(G);

        std::vector<Node>& m_nodes = G.get_nodes();

        std::vector<size_t> cc_ids;
        int size = m_nodes.size();
        cc_ids.resize(size);

        int cc_id, count = 0;
        for (Node& n : m_nodes) {
                cc_id = n.get_cc();
                cc_ids[count] = cc_id;
                ++count;
        }

        return cc_ids;
}


bool compare_nodes(Node& a, Node& b)
// return true if a's post number is larger than b's post number
{
        int a_post = a.get_post();
        int b_post = b.get_post();

        if (a_post > b_post)
                return true;

        return false;
}


std::vector<size_t> find_strongly_connected_components(Graph& G)
{
        DFS_recursive(G);

        std::vector<Node>& G_m_nodes = G.get_nodes();
        std::vector<Node> sorted_nodes;

        int size = G_m_nodes.size();
        sorted_nodes.resize(size);

        std::copy(G_m_nodes.begin(), G_m_nodes.end(), sorted_nodes.begin());
        std::sort(sorted_nodes.begin(), sorted_nodes.end(), compare_nodes);
        // sort nodes with highest postorder at beginning

        Graph rev;
        rev.reverse(G); 

        DFS_recursive(rev);

        std::vector<Node>& rev_nodes = rev.get_nodes();
        std::vector<size_t> cc_ids;

        size = rev_nodes.size();
        cc_ids.resize(size);

        int cc_id, count = 0;
        for (Node& n : rev_nodes) {
                cc_id = n.get_cc();
                cc_ids[count] = cc_id;
                ++count;
        }

        return cc_ids;

}


void check(std::vector<size_t>& a, std::vector<size_t>& b)
{
        int size = a.size();
        for (int i = 0; i < size; ++i) {
                if (a[i] != b[i]) {
                        std::cout << "failed test!\n";
                        exit(1);
                }
        }
        std::cout << "passed test!\n";
}


// [[Rcpp::export]]
void test_cc_1()
{
        Graph g1("./graphs/func_edges/big_1.txt");
        find_connected_components(g1);
}


// [[Rcpp::export]]
void test_cc_2()
{
        Graph g1("./graphs/func_edges/big_2.txt");
        find_connected_components(g1);
}


// [[Rcpp::export]]
void test_cc_3()
{
        Graph g1("./graphs/func_edges/big_3.txt");
        find_connected_components(g1);
}


// [[Rcpp::export]]
void test_cc_4()
{
        Graph g1("./graphs/func_edges/big_4.txt");
        find_connected_components(g1);
}


// [[Rcpp::export]]
void test_scc_1()
{
        Graph g1("./graphs/func_edges/big_1.txt");
        find_strongly_connected_components(g1);
}


// [[Rcpp::export]]
void test_scc_2()
{
        Graph g1("./graphs/func_edges/big_2.txt");
        find_strongly_connected_components(g1);
}


// [[Rcpp::export]]
void test_scc_3()
{
        Graph g1("./graphs/func_edges/big_3.txt");
        find_strongly_connected_components(g1);
}


// [[Rcpp::export]]
void test_scc_4()
{
        Graph g1("./graphs/func_edges/big_4.txt");
        find_strongly_connected_components(g1);
}


void test_all()
{
        std::vector<std::string> bigs {"1", "2", "3"};
        for (std::string s : bigs) {
                Graph g(s);
        }
/*
        Graph g1 ("dir_ac_1.txt");
        std::vector<size_t> cc_ids_1 = find_connected_components(g1);
        std::vector<size_t> cc_ids_2 = find_strongly_connected_components(g1);

        //p_cc_ids(cc_ids_1);
        p_cc_ids(cc_ids_2);

//        std::vector<size_t> ans_dir_ac_1 {0, 0, 0, 0, 0, 0};
        //check(cc_ids_1, ans_dir_ac_1);
        check(cc_ids_2, ans_dir_ac_1);

        //std::vector<size_t> cc_ids_2 = find_strongly_connected_components(g1);
*/
        /*Graph g1 ("big_1.txt");
        find_connected_components(g1);
        Graph g2 ("big_2.txt");
        Graph g3 ("big_3.txt");
        Graph g4 ("big_4.txt");*/


/*        Graph g2 ("dir_ac_2.txt");
        Graph g3 ("dir_ac_3.txt");
        Graph g4 ("un_ac_1.txt");
        Graph g5 ("un_ac_2.txt");
        Graph g6 ("un_ac_3.txt");
        Graph g7 ("dir_c_1.txt");
        Graph g8 ("dir_c_2.txt");
        Graph g9 ("un_c_1.txt");
        Graph g10 ("un_c_2.txt");
*/

}


int main()
{
        test_cc_1();
}

/*** R
start.time <- Sys.time()
test_scc_1()
end.time <- Sys.time()
time.taken.1 <- end.time - start.time

start.time <- Sys.time()
test_scc_2()
end.time <- Sys.time()
time.taken.2 <- end.time - start.time

start.time <- Sys.time()
test_scc_3()
end.time <- Sys.time()
time.taken.3 <- end.time - start.time

start.time <- Sys.time()
test_scc_4()
end.time <- Sys.time()
time.taken.4 <- end.time - start.time

edges <- c(1000, 10000, 100000, 1000000)
runtime <- c(time.taken.1, time.taken.2, time.taken.3, time.taken.4)

plot(edges, runtime, type="b", xlab="edges", ylab="runtime (seconds)")
grid(col="blue")
*/

