/*
    Max-Cost Max-Flow problem, flip profit to be cost - revenue instead of revenue - cost to go to the dual Min-Cost Max-Flow.
    Add MAX_COST where needed, while keeping track of how many time you are gonna calculate it in the cost at the end.
    Each meal is a unit of flow through the graph.
    Model days as graph nodes.
    Production modeled as an edge from src to i-th day with capacity = a_i, cost = c_i.
    Selling modeled as an edge from i-th day to sink with capacity = s_i, cost = MAX_COST - pi.
    Things staying in the fridge modeled as an edge from day i to day i + 1 with capacity = v_i, cost = e_i.
    Run min-cost max-flow with nonnegative weights.
    Output flow * MAX_COST - cost at the end.
*/

// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
#include <queue>
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
typedef boost::graph_traits<Graph>::edge_iterator              EdgeIt;
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
int T, n, src, sink, a_i, c_i, s_i, p_i, v_i, e_i, sum;
int MAX_COST = 20;

void testcase(){
    // build Graph
    std::cin >> n;

    G = Graph(n + 2); 
    src = n; sink = n + 1;

    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);


    for(int i=0;i<n;i++){

        std::cin >> a_i >> c_i;
        eaG.addEdge(src, i, a_i, c_i);
    }

    sum = 0;
    for(int i=0;i<n;i++){

        std::cin >> s_i >> p_i; 
        sum += s_i;
        eaG.addEdge(i, sink, s_i, MAX_COST - p_i);
    }

    for(int i=0;i<n-1;i++){

        std::cin >> v_i >> e_i;
        eaG.addEdge(i, i+1, v_i,  e_i); 
    }
    
    // long flow = boost::push_relabel_max_flow(G, src, sink);
    boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    // boost::cycle_canceling(G);
    long cost = boost::find_flow_cost(G);

    long flow = 0;
    OutEdgeIt e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(src, G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }

    // long flow1 = boost::push_relabel_max_flow(G, src, sink);

    // // Iterate over all the edges to print the flow along them
    // long cost_bound = 0;
    // EdgeIt ebeg, e_end;
    // for (boost::tie(ebeg, e_end) = boost::edges(G); ebeg != e_end; ++ebeg){
       
    //     if(weightmap[*ebeg] >= 0)
    //         cost_bound += (capacitymap[*ebeg] - rescapacitymap[*ebeg]) * MAX_COST;
    // }

    std::cout << ((flow < sum) ? "impossible " : "possible ") << flow << " " << flow * MAX_COST - cost << std::endl;
    // std::cout << ((flow < sum) ? "impossible " : "possible ") << flow << " " << cost_bound - cost << std::endl;
}

// Main
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin >> T;
    while(T--) testcase();
    return 0;
}