/*
	Use biconnected_components to assign each edge to a biconnected component.
	Find all biconnected components that contain only one edge.
	Return all edges sorted.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;
using namespace std;

struct edge_component_t{
	enum{
		num=666
	};
	typedef edge_property_tag kind;
} edge_component;

typedef pair<int, int> ii;
typedef adjacency_list<vecS, vecS, undirectedS,
						property<vertex_index_t, int>,
						property<edge_component_t, int> > Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

// typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef property_map<Graph, edge_component_t>::type ComponentMap;

int n, m, u, v;
map<int, vector<ii> > edges_in_component;
vector<ii> critical_edges;

void test_case(){
	// cout << "####################" << endl;
	critical_edges.clear();

	cin >> n >> m;
	Graph g(n);
	Edge e; bool success;
	for(int i=0;i<m;i++){
		cin >> u >> v;
		tie(e, success) = add_edge(u, v, g);
	}

	ComponentMap component_map = get(edge_component, g);
	int nbcc = biconnected_components(g, component_map);
	for(int i=0;i<m;i++)
		edges_in_component[i].clear();

	graph_traits<Graph>::edge_iterator  e_i, e_end;
	for(tie(e_i, e_end) = edges(g);e_i!=e_end;e_i++){

		u = source(*e_i, g); v = target(*e_i, g);
		edges_in_component[component_map[*e_i]].push_back({u, v});
	}

	for(int i=0;i<nbcc;i++){
		auto el = edges_in_component[i];
		if(el.size()>1)
			continue;

		ii critical_edge = *(el.begin());
		if(critical_edge.first > critical_edge.second){
			int t = critical_edge.first;
			critical_edge.first = critical_edge.second;
			critical_edge.second = t;
		}
		critical_edges.push_back(critical_edge);
	}

	sort(critical_edges.begin(), critical_edges.end());

	cout << critical_edges.size() << endl;
	for(auto e : critical_edges){
		cout << e.first << " " << e.second << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--){test_case();}

	return 0;
}