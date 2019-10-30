
/* 
	Model each crack from 1 to W-1 as a node with capacity 1 (splitting the vertex into in and out vertex with an edge of capacity 1 in between)
	For each block not starting at 0 add an edge from start_index_out to end_index_in with capacity 1.
	For each block starting with 0 add an edge from 0 to end_index_in with capacity 1.
	For each crack add an egde from index_in to index_out with capacity 1.
	Connect source to 0 with capacity N.
	Connect W to target with capacity N.
	Output max flow from source to target.
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

int T, w, n, l, r, source, target;

// Functions
// =========
Graph G;

void read_testcase(){

	std::cin >> w >> n;

	G = Graph(2*w + 2);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	source = 2*w; target = source + 1;

	for(int i=0;i<n;i++){
		std::cin >> l >> r;
		if(l > r){
			int t = r;
			r = l;
			l = t;
		}

		if(l != 0)
			eaG.addEdge(l + w, r, 1);
		else
			eaG.addEdge(l , r, 1);
	}

	for(int i=1;i<w;i++){
		eaG.addEdge(i, i+w, 1);
	}

	eaG.addEdge(source, 0, n);
	eaG.addEdge(w, target, n);
}

void solve(){
	long flow = push_relabel_max_flow(G, source, target);

	std::cout << flow << std::endl;
}

// Function for an individual testcase
void testcase() {
	read_testcase();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin >> T;
	while(T--) testcase();
	return 0;
}