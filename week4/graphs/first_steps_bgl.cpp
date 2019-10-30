#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
						property<vertex_distance_t, int>,
						property<edge_weight_t, int> > Graph;

typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, vertex_distance_t>::type DistanceMap;
typedef property_map<Graph, vertex_index_t>::type IndexMap;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;


void test_case(){
	int n, m, u, v, w;
	cin >> n >> m;

	Graph g(n);
	
	DistanceMap distance_map = get(vertex_distance, g);
	WeightMap weight_map = get(edge_weight, g);
	// IndexMap index_map_g = get(vertex_index, g);
	
	Edge e; bool success;
	for(int i=0;i<m;i++){
		cin >> u >> v >> w;
		tie(e, success) = add_edge(u, v, g);
		if(success){
			weight_map[e] = w;
		}
	}

	int sum = 0, maxi = -1;
	Vertex start = 0;

	vector<Vertex> pred_map(n);
	prim_minimum_spanning_tree(g,
		make_iterator_property_map(pred_map.begin(), get(vertex_index, g)),
		root_vertex(start)
	);

	vector<Vertex> predecessors(n);
	dijkstra_shortest_paths(
		g, 
		start,
		predecessor_map(make_iterator_property_map(predecessors.begin(), get(vertex_index, g))).
		distance_map(distance_map)
	);

	for(int i=0;i<n;i++){
		tie(e, success) = edge(pred_map[i], i, g);
		if(success){
			sum += weight_map[e];
		}

		if(distance_map[i] > maxi)
			maxi = distance_map[i];
	}

	cout << sum << " " << maxi << endl;
}

int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--){
		test_case();
	}

	return 0;
}