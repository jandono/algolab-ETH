/*
	Create 10 different graphs, one for each specie.
	The minimum spanning tree of each graph represents 
	the private network for each specie.
	Create a new graph s.t. each edge weight is equal 
	to the minimum weight for that edge in all private networks.
	Run Dijkstra on the new graph.
*/

#include <iostream>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
							property<vertex_index_t, int,
								property<vertex_distance_t, int> >,
							property<edge_weight_t, int> > Graph;

typedef property_map<Graph, vertex_distance_t>::type DistanceMap;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

typedef pair<int, int> ii;

int hives[10], u, v, w, n, m, s, a, b;
Graph g, g_s[10];
Edge e, e1, e2; bool success, success1;
WeightMap weight_map_gs[10], weight_map_g;
Vertex start;

void read_test_case(){
	cin >> n >> m >> s >> a >> b;

	g = Graph(n);
	weight_map_g = get(edge_weight, g);
	
	for(int i=0;i<s;i++){
		g_s[i] = Graph(n);
		weight_map_gs[i] = get(edge_weight, g_s[i]);
	}

	for(int i=0;i<m;i++){
		cin >> u >> v;
		for(int j=0;j<s;j++){
			cin >> w;

			tie(e, success) = add_edge(u, v, g_s[j]);
			weight_map_gs[j][e] = w;
		}
		tie(e, success) = add_edge(u, v, g);
		weight_map_g[e] = INT_MAX;
	}

	for(int i=0;i<s;i++){
		cin >> hives[i];
	}
}

void test_case(){
	read_test_case();
	
	for(int i=0;i<s;i++){		
		vector<Vertex> pred_map(n);
		start = hives[i];
		prim_minimum_spanning_tree(
			g_s[i],
			make_iterator_property_map(pred_map.begin(), get(vertex_index, g_s[i])),
			root_vertex(start)
		);
 	
		for(int j=0;j<n;j++){
			tie(e1, success) = edge(pred_map[j], j, g_s[i]);
			tie(e2, success1) = edge(pred_map[j], j, g);
			if(success && success1)
				weight_map_g[e2] = min(weight_map_g[e2], weight_map_gs[i][e1]);
		}
	}

	start = a;
	DistanceMap distance_map_g = get(vertex_distance, g);
	vector<Vertex> pred_map(n);
	dijkstra_shortest_paths(
		g,
		start,
		distance_map(distance_map_g).
		predecessor_map(make_iterator_property_map(pred_map.begin(), get(vertex_index, g)))
	);

	cout << distance_map_g[Vertex(b)] << endl;
}

int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--) test_case();

	return 0;
}
