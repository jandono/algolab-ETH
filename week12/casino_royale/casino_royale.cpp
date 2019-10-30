/*
	Transform max cost max flow to a min cost max flow algorithm by subtracting costs from maximum cost.
	Maximum cost per edge, per unit of flow is 2^7 = 128.
	Model one line from 0 to n-1 representing agents not doing a mission with capacity L.
		The cost in the original max cost max flow problem would be 0, s
		o we just flip it to MAX_COST in order to obtain the dual min cost max flow problem.
	For each mission from U to V branch an edge from U to V with capacity 1.
		The transformation cost is calculated as (U - V)*MAX_COST - cost.
		The first part represents the cost if we don't take the mission which is length of the path * MAX_COST.
		And by substracting each cost from the upper limit we obtain the dual min cost max flow.
	Calculate the flow and the cost of the dual problem.
	To go back to the primal subtract the obtained cost from the maximal possible one (no missions seleceted).
		Solution = l*(n-1)*MAX_COST - min_cost
*/


// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e; 
    }
};

Graph G;
int T, n, m, l, u, v, cost, source, target;
int MAX_COST = 128;

void read_testcase(){

	std::cin >> n >> m >> l;

	G = Graph(n + 2);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    source = n; target = n + 1;
    for(int i=0;i<m;i++){

    	std::cin >> u >> v >> cost;
    	eaG.addEdge(u, v, 1, (v-u)*MAX_COST - cost);
    }

    for(int i=0;i<n-1;i++){
    	eaG.addEdge(i, i+1, l, MAX_COST);
    }

    eaG.addEdge(source, 0, l, 0);
    eaG.addEdge(n-1, target, l, 0);
}

void solve(){
	boost::successive_shortest_path_nonnegative_weights(G, source, target);
    long long cost = l*(n-1)*MAX_COST - boost::find_flow_cost(G);

    std::cout << cost << std::endl;
}

void testcase(){
	read_testcase();
	solve();
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin >> T;
	while(T--) testcase();
	return 0;
}