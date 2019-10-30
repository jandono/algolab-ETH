/*
    Weighted maximum matching in biparted graphs = Max-Cost Max-Flow in biparted graphs.
    Transform Max-Cost Max-Flow to Min-Cost Max-Flow by subtracting each cost from a MAX_COST.
    MAX_COST is 50 in our case.
    Connect all sailors to their respective boats with capacity = 1, cost = MAX_COST - cost.
    Connect all sailors to an artificial sink with capacty = 1, cost = MAX_COST, 
    to guarantee a path of length 3 everywhere.
    Connect all boats to the sink with capacity = 1, cost = MAX_COST.
    Connect source to all sailors with capacity = 1, cost = MAX_COST.
    Connect artificial sink to sink with capacity = S, cost = MAX_COST.
    Output |f| * MAX_COST * 3 - total_cost to go back to the primal problem.
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

int T, b, s, p, u, v, src, sink, artificial_sink, spectacle;
Graph G;
int MAX_COST = 50;

void read_build_graph(){
    // build Graph
    std::cin >> b >> s >> p;

    G = Graph(b + s + 3); 
    src = b + s; sink = src + 1; artificial_sink = sink + 1;

    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    for(int i=0;i<p;i++){
        std::cin >> v >> u >> spectacle;

        eaG.addEdge(u, s + v, 1, MAX_COST - spectacle);
    }

    for(int i=0;i<s;i++){
        eaG.addEdge(src, i, 1, MAX_COST);
        eaG.addEdge(i, artificial_sink, 1, MAX_COST);
    }

    for(int i=0;i<b;i++){
        eaG.addEdge(s + i, sink, 1, MAX_COST);
    }

    eaG.addEdge(artificial_sink, sink, s, MAX_COST);
}


void solve(){
    
    // long flow = push_relabel_max_flow(G, src, sink);
    boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    long cost = boost::find_flow_cost(G);
    std::cout << s * MAX_COST * 3 - cost << std::endl;
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