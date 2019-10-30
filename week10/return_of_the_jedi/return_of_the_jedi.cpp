#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;
using namespace std;

struct edge_component_t{
	enum{
		num=666
	};
	typedef edge_property_tag kind;
} edge_component;

typedef adjacency_list<vecS, vecS, undirectedS,
						property<vertex_index_t, int>,
						property<edge_weight_t, int,
							property<edge_component_t, int> > > Graph;

typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, edge_component_t>::type ComponentMap;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

Graph g;
int T, n, start_planet, w;
bool success;
Edge e;
map<int, vector<Edge> > edges_in_component;

void read_testcasse(){

	cin >> n >> start_planet;
	start_planet; // work in 0 based indexing;

	g = Graph(n);
	WeightMap weight_map = get(edge_weight, g);

	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){

			cin >> w;
			tie(e, success) = add_edge(i, i+j+1, g);
			if(success){
				weight_map[e] = w;
			}
		}
	}
}

void solve(){
	// Calculate the MST
	vector<Vertex> pred_map(n);
	prim_minimum_spanning_tree(g,
		make_iterator_property_map(pred_map.begin(), get(vertex_index, g)),
		root_vertex(start_planet)
	);

	// Create a second graph representing the MST
	Graph MST(n);
	WeightMap weight_map_MST = get(edge_weight, MST);
	for(int v = 0; v < pred_map.size(); v++){
		if(pred_map[v] == v)
			continue;

		tie(e, success) = add_edge(pred_map[v], v, MST);
		if(success){
			// Does this work, or do I need to get the original edge from g?
			weight_map_MST[e] = weight_map[e];
		}
	}

	graph_traits<Graph>::edge_iterator e_i, e_end;

	for(tie(e_i, e_end) = edges(g); e_i != e_end; e_i++){

		// if the edge is already in the MST ignore it
		u = source(*e_i, g); v = target(*e_i, g);
		if(pred_map[u] == v || pred_map[v] == u)
			continue;

		// add a candidate edge that will build a cycle in the MST
		tie(e, success) = add_edge(u, v, MST);

		// get the biconnected_components so that you can find the cycle
		ComponentMap component_map = get(edge_component, MST);
		int nbcc = biconnected_components(g, component_map);

		// calculate the size of each components and store edges in components
		for(tie(mst_e_i, mst_e_end) = edges(MST); mst_e_i != mst_e_end; mst_e_i++){

			u = source(*mst_e_i, MST); v = target(*mst_e_i, MST);
			edges_in_component[component_map[*mst_e_i]].push_back(*mst_e_i);
		}
	}
}

void testcase(){

}

int main(){
	ios_base::sync_with_stdio(false);
	cin >> T;
	while(T--) testcase();
	return 0;
}