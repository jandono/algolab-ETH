/*
	Calculate Dijkstra twice. 
	Once from the start vertex and once from the finish vertex.
	Then use the distances to build a graph consisting of only edges
	that belong to the shortest path.
	Run maximum flow on the newly created graph.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace boost;
// using namespace std;

typedef adjacency_list<vecS, vecS, directedS,
								property<vertex_index_t, int,
									property<vertex_distance_t, int> >,
								property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex1;
typedef graph_traits<Graph>::edge_descriptor Edge1;

typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, vertex_distance_t>::type DistanceMap;

// FLOW SHIT
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph1;
// Interior Property Maps
typedef	boost::property_map<Graph1, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph1, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph1, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph1>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph1>::edge_descriptor			Edge;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph1 &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph1 & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
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

//==================================================================

typedef long long ll;

ll n, m, s, f, u, v, w, d;
Graph g;
Graph1 g1;

std::tuple<ll,ll,ll,ll> eds[5001];
std::vector<ll> distancesS, distancesF;

void preprocess_dijkstra()
{
	std::cin >> n >> m >> s >> f;
	g = Graph(n);

	WeightMap weight_map = get(edge_weight, g);
	Edge e; bool success;
	for(int i=0;i<m;i++){
		std::cin >> u >> v >> w >> d;
		tie(e, success) = add_edge(u, v, g);
		weight_map[e] = d;
		tie(e, success) = add_edge(v, u, g);
		weight_map[e] = d;
		get<0>(eds[i]) = u;
		get<1>(eds[i]) = v;
		get<2>(eds[i]) = w;
		get<3>(eds[i]) = d;
	}

	distancesS = std::vector<ll>(n);
	std::vector<int> pred_map1(n);
	dijkstra_shortest_paths(
		g,
		s,
		predecessor_map(make_iterator_property_map(pred_map1.begin(), get(vertex_index, g))).
		distance_map(make_iterator_property_map(distancesS.begin(), get(vertex_index, g)))
	);

	distancesF = std::vector<ll>(n);
	std::vector<int> pred_map2(n);
	dijkstra_shortest_paths(
		g,
		f,
		predecessor_map(make_iterator_property_map(pred_map2.begin(), get(vertex_index, g))).
		distance_map(make_iterator_property_map(distancesF.begin(), get(vertex_index, g)))
	);
}

ll max_flow_graph()
{
	g1 = Graph1(n);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, g1);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, g1);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, g1);
	EdgeAdder eaG(g1, capacitymap, revedgemap);

	for(int i=0;i<m;i++){
		u = get<0>(eds[i]); v = get<1>(eds[i]); w = get<2>(eds[i]); d = get<3>(eds[i]);
		
		if(distancesS[u] + distancesF[v] + d == distancesS[f]){
			eaG.addEdge(u, v, w);
		}else
		if(distancesS[v] + distancesF[u] + d == distancesS[f]){
			eaG.addEdge(v, u, w);
		}
	}

	ll flow1 = boost::push_relabel_max_flow(g1, s, f);
	return flow1;
}

void test_case()
{
	preprocess_dijkstra();
	long long flow = max_flow_graph();
	std::cout << flow << std::endl;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int T;
	std::cin >> T;
	while(T--) test_case();
	return 0;
}