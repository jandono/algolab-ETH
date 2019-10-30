/*
	Modify the graph than do a regular max flow.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

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

typedef long long ll;
typedef std::pair<int, int> ii;

int n, m, k, l, x, u, v;
std::vector<int> intersections_with_photographs, police_stations;
Vertex source, target;
Graph G;

void init_test_case(){
	intersections_with_photographs.clear();
	police_stations.clear();
}

void read_test_case(){
	std::cin >> n >> m >> k >> l;

	G = Graph(2*n + 2);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	for(int i=0;i<k;i++){
		std::cin >> x;
		police_stations.push_back(x);
	}

	for(int i=0;i<l;i++){
		std::cin >> x;
		intersections_with_photographs.push_back(x);
	}

	for(int i=0;i<m;i++){
		std::cin >> u >> v;
		eaG.addEdge(u, v, k);
		eaG.addEdge(u+n, v+n, 1);
	}

	for(auto in : intersections_with_photographs){
		eaG.addEdge(in, in+n, 1);	
	}

	source = boost::add_vertex(G);
	target = boost::add_vertex(G);
	for(auto ps : police_stations){
		eaG.addEdge(source, ps, 1);
		eaG.addEdge(ps+n, target, 1);
	}
}

void solve(){
	long flow = boost::push_relabel_max_flow(G, source, target);
	std::cout << flow << std::endl;
}

void test_case(){

	init_test_case();
	read_test_case();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);

	int T;
	std::cin >> T;
	while(T--) test_case();
	return 0;
}