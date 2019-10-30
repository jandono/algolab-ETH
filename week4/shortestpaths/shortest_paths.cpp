#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, directedS,
								property<vertex_index_t, int,
									property<vertex_distance_t, int> >,
								property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, vertex_distance_t>::type DistanceMap;

int main(){
	int n, m, q, lat, lon, u, v, w, s, t;
	cin >> n >> m >> q;

	Graph g(n);

	for(int i=0;i<n;i++){
		cin >> lat >> lon;
	}

	WeightMap weight_map = get(edge_weight, g);
	Edge e; bool success;
	for(int i=0;i<m;i++){
		cin >> u >> v >> w;
		tie(e, success) = add_edge(u, v, g);
		weight_map[e] = w;
	}

	DistanceMap distance_map = get(vertex_distance, g);
	for(int i=0;i<q;i++){
		cin >> s >> t;

		vector<int> pred_map(n);
		dijkstra_shortest_paths(
			g,
			s,
			predecessor_map(make_iterator_property_map(pred_map.begin(), get(vertex_index, g))).
			distance_map(distance_map)
		);

		if(distance_map[Vertex(t)]!=numeric_limits<int>::max())
			cout << distance_map[Vertex(t)] << endl;
		else
			cout << "unreachable" << endl;
	}
}