/*
	Ground stations are one set of vertices.
	Satellites are a second one.
	Create a biparted graph and add src and sink.
	Obtain the maximum matching using Max-Flow on bi-parted graphs.
	Perform BFS/DFS to mark visited vertices in the residual graph.
	All unvisited stations and all visited satellites create the Minimum Vertex Cover.
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

int T, g, s, l, src, sink, g_station, s_station;
Graph G;

void read_testcase(){

	std::cin >> g >> s >> l;

	G = Graph(g + s + 2); 
	src = g + s; sink = src + 1;

	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	// ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	for(int i=0;i<l;i++){
		std::cin >> g_station >> s_station;
		eaG.addEdge(g_station, s_station + g, 1);
	}

	for(int i=0;i<g;i++){
		eaG.addEdge(src, i, 1);
	}

	for(int i=0;i<s;i++){
		eaG.addEdge(i + g, sink, 1);
	}
}

void solve(){

	long flow = push_relabel_max_flow(G, src, sink);
	int N = g + s + 2;
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);

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
		}
	}

	int g_visited = 0, s_visited = 0;
	std::vector<int> g_stations;
	std::vector<int> s_stations;
	for (int i = 0; i < N - 2; ++i) {

		if(i < g && !vis[i]){
			g_visited++;
			g_stations.push_back(i);
		}
		else
		if(i >= g && i < g + s && vis[i]){
			s_visited++;
			s_stations.push_back(i - g);
		}	
	}

	std::cout << g_visited << " " << s_visited << std::endl;

	for(auto station : g_stations)
		std::cout << station << " ";
	for(auto station : s_stations)
		std::cout << station << " ";

	std::cout << std::endl;
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