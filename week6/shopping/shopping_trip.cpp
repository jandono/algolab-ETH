/*
	Maximum disjoint paths from source to target in an undirected graph.
	Replace each undirected edge with two directed edges in reverse directions.
*/

// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
// using namespace std;
// using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	boost::property_map<Graph, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph>::edge_descriptor			Edge;
typedef	boost::graph_traits<Graph>::edge_iterator			EdgeIt;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

Graph g;
// EdgeAdder eaG;
int n, m, s, from, to, T, s_i, source, target;

void read_testcase(){

	std::cin >> n >> m >> s;
	g = Graph(n + 2);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, g);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, g);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, g);
	EdgeAdder eaG(g, capacitymap, revedgemap);

	source = n;
	eaG.addEdge(source, 0, s);
	target = n + 1;
	for(int i=0;i<s;i++){
		std::cin >> s_i;
		eaG.addEdge(s_i, target, 1);
	}

	for(int i=0;i<m;i++){
		std::cin >> from >> to;
		eaG.addEdge(from, to, 1);
		eaG.addEdge(to, from, 1);
	}
}

void solve(){

	long flow = boost::push_relabel_max_flow(g, source, target);
	if(flow != s)
		std::cout << "no" << std::endl;
	else
		std::cout << "yes" << std::endl;
}

void testcase(){
	read_testcase();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin >> T;
	while(T--) testcase();
	return 0;
}