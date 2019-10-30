/*
	Maxflow with min capacities enforced.
	For every edge:
		Take the minimum out of the source vertex to the maxflow target.
		Take the minimum from to the maxflow source to the target vertex.

	Be carefull to account for all the additional flow introduced in the
	graph when checking if the flow satisfies the conditions or not.
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


// Functions
// =========

Graph G;
int T, l, p, source, target, sum_min_capacities, sum_demands, min_cap, max_cap, u, v, supply, demand;

void read_build_graph(){

	std::cin >> l >> p;

	G = Graph(l + 2);
	source = l;
	target = source + 1;
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	sum_demands = 0;
	for(int i=0;i<l;i++){

		std::cin >> supply >> demand;
		sum_demands += demand;
		eaG.addEdge(source, i, supply);
		eaG.addEdge(i, target, demand);
	}

	sum_min_capacities = 0;
	for(int i=0;i<p;i++){

		std::cin >> u >> v >> min_cap >> max_cap;
		sum_min_capacities += min_cap;
		eaG.addEdge(u, v, max_cap - min_cap);
		eaG.addEdge(source, v, min_cap);
		eaG.addEdge(u, target, min_cap);
	}
}

void solve(){

	long flow1 = push_relabel_max_flow(G, source, target);
	if(flow1 == sum_demands + sum_min_capacities)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
}


// Function for an individual testcase
void testcase() {
	read_build_graph();
	solve();
}

int main(){

	std::ios_base::sync_with_stdio(false);

	std::cin >> T;

	while(T--){
		testcase();
	}

	return 0;
}