/*
	Approach 1: 
		Create a full graph and perform maxflow on it.

	Approach 2: 
		Create a graph from the missing games and participants only and perform maxflow on it.

	For both cases see if the max flow is equal to the missing points
	and if such a configuration is possible(see conditions below).
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

int n, m, s, t, u, v, c, scoreboard, score, T;

void testcase(){
	Graph G;
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);


	std::cin >> n >> m;

	s = m + n;
	t = m + n + 1;

	std::vector<int> scores(n, 0);
	for(int i=0;i<m;i++){
		std::cin >> u >> v >> c;

		// edge from game to player
		if(c==1){
			scores[u]++;
			// eaG.addEdge(i, m + u, 1);
		}else
		if(c==2){
			scores[v]++;
			// eaG.addEdge(i, m + v, 1);
		}else{
			eaG.addEdge(i, m + u, 1);
			eaG.addEdge(i, m + v, 1);
		}

		// edge from source to game
		eaG.addEdge(s, i, 1);
	}

	scoreboard = 0;
	int missing = 0;
	bool success = true;
	for(int i=0;i<n;i++){
		std::cin >> score;
		scoreboard += score;

		int missing_score = score - scores[i];

		if(missing_score < 0){
			success = false;
		}
		missing += missing_score;

		// edge from player to target
		eaG.addEdge(m + i, t, missing_score);
	}


	if(!success){
		std::cout << "no" << std::endl;
	}else{

		int flow = push_relabel_max_flow(G, s, t);
		if(flow == missing && scoreboard == m)
			std::cout << "yes" << std::endl;
		else
			std::cout << "no" << std::endl;
	}

	// if(scoreboard != m || flow != scoreboard)
	// 	std::cout << "no" << std::endl;
	// else
	// 	std::cout << "yes" << std::endl;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin >> T;
	while(T--) testcase();
	return 0;
}