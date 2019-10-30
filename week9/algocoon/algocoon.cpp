/*
	Check which to vertices can be separated most easily by doing a flow.
	There has to be two verticies i, i + 1 such that i belongs in one group and i + 1 in the other.
	Use them as source and sink, calculate a max-flow which is actually equal to the min-cut.
	To obtain the set of verteces connected to the source, use BFS on the residual graph starting from source.
	To obtain the set of verteces connected to the sink, use BFS on the residual graph starting from the sink.
*/

// Includes
// ========
// STL includes
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

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
typedef	boost::graph_traits<Graph>::out_edge_iterator			OutEdgeIt;

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
		capacitymap[rev_e] = 0;
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

int T, n, m, u, v, cost, src, sink, min_flow, flow;
Graph G;

void read_build_graph(){
	// build Graph
	std::cin >> n >> m;

	G = Graph(n);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	// ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	for(int i=0;i<m;i++){
		std::cin >> u >> v >> cost; //cost = capacity in the max flow
		eaG.addEdge(u, v, cost);
	}
}

void solve(){

	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);

	min_flow = INT_MAX;
	for(int i=0;i<n;i++){

		flow = push_relabel_max_flow(G, i, (i+1) % n);
		if(flow < min_flow){

			min_flow = flow;
			src = i;
			sink = (i + 1) % n;
		}
	}

	flow = push_relabel_max_flow(G, src, sink);
	std::cout << flow << std::endl;

	std::vector<int> myparts;
	myparts.push_back(src);

	int N = n;
	// BFS to find vertex set S
	std::vector<int> vis(N, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
	Q.push(src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		OutEdgeIt ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rescapacitymap[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);

			myparts.push_back(v);
		}
	}

	std::cout << myparts.size() << " ";
	for (auto part : myparts) {
		std::cout << part << " ";
	}
	std::cout << std::endl;
}

void testcase(){
	read_build_graph();
	solve();
}

// Main
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin >> T;
	while(T--) testcase();
	return 0;
}
	